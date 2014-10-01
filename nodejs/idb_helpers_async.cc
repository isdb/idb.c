/*********************************************************************
 * iDB - Key/Value NOSQL Data Storage for Node.js
 *
 * Copyright (c) 2014 Riceball LEE
 *
 * MIT License
 ********************************************************************/

#include <node.h>
#include <nan.h>
#include "idb_helpers.h"
#include "./idb_helpers_async.h"

using v8::Function;
using v8::Local;
using v8::Null;
using v8::Number;
using v8::Value;

class PutInFileWorker : public NanAsyncWorker {
 public:
  PutInFileWorker(NanCallback *callback, sds key,
      sds value,
      sds attr,
      TIDBProcesses partitionKeyWay)
    : NanAsyncWorker(callback), key(key), value(value), attr(attr), partitionKeyWay(partitionKeyWay), result(0) {}
  ~PutInFileWorker() {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute () {
    int l = value ? sdslen(value) : 0;
    result = iPutInFile(key, value, l, attr, partitionKeyWay);
    sdsfree(key);sdsfree(value);sdsfree(attr);
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    NanScope();

    Local<Value> error;
    //String error = NULL; 
    
    if (result == 0) {
        error = NanNull();
    }
    else if (result == -1) {
        error = NanError("The same filename is exists, can not create folder to keep value", result);
    }
    else
        error = NanError(strerror(result), result);
    
    Local<Value> argv[] = {
        error
      //, NanNew<Number>(result)
    };

    //callback->Call(2, argv);
    callback->Call(1, argv);
  }

 private:
  sds key;
  sds attr;
  sds value;
  TIDBProcesses partitionKeyWay;
  int result;
};

// Asynchronous access to the function
NAN_METHOD(PutInFileAsync) {
  NanScope();

  int l = args.Length();
  TIDBProcesses partitionKeyWay = dkFixed;
  sds attr  = NULL;
  sds key   = NULL;
  sds value = NULL;
  if (l >= 5) partitionKeyWay = (TIDBProcesses) args[3]->Uint32Value();
  if (l >= 4) {
      attr  = *NanUtf8String(args[2]);
      if (attr) attr = sdsnew(attr);
  }
  if (l >= 3) {
      value = *NanUtf8String(args[1]);
      if (value) value = sdsnew(value);
  }
  if (l >= 2) {
      key   = *NanUtf8String(args[0]);
      if (key) key = sdsnew(key);
  }
  else {
      NanThrowTypeError("where my key argument? u type nothing?");
      NanReturnUndefined();
  }

  NanCallback *callback = new NanCallback(args[l-1].As<Function>());

  NanAsyncQueueWorker(new PutInFileWorker(callback, key, value, attr, partitionKeyWay));
  NanReturnUndefined();
}
