/*********************************************************************
 * iDB - Key/Value NOSQL Data Storage for Node.js
 *
 * Copyright (c) 2014 Riceball LEE
 *
 * MIT License
 ********************************************************************/

#ifndef IDB_HELPERS_SYNC_H_
#define IDB_HELPERS_SYNC_H_

#include <node.h>
#include <nan.h>

NAN_METHOD(ErrorStrSync);
NAN_METHOD(SetMaxPageSizeSync);
NAN_METHOD(PutInFileSync);
NAN_METHOD(GetInFileSync);

#endif  // IDB_HELPERS_SYNC_H_
