#console.log("IncrBy")

path=require('path')
fse=require('fs-extra')
fs=require('graceful-fs')
chance = new require('chance')()
idb = require('../index')
utils = require('./utils')

gKey    = utils.getRandomKey()
gKey2   = utils.getRandomKey()


describe 'IncrBy a key/value from a directory', ->

    utils.clearDataDir()
    it 'should increment 1 for a new key with default param synchronous', ->
        utils.testIncrByInFileSync(gKey)
        utils.testGetInFileSync(gKey, "1")

    it 'should increment 1 for an exists key with default param synchronous', ->
        utils.testIncrByInFileSync(gKey)
        utils.testGetInFileSync(gKey, "2")

        utils.testPutInFileSync(gKey, "-1")
        utils.testIncrByInFileSync(gKey)
        utils.testGetInFileSync(gKey, "0")

        utils.testPutInFileSync(gKey, utils.getRandomStr(33))
        utils.testIncrByInFileSync(gKey, 2)
        utils.testGetInFileSync(gKey, "2")

        utils.testIncrByInFileSync(gKey, 22)
        utils.testGetInFileSync(gKey, "24")

    it 'should increment 1 for a new key with default param asynchronous', ->
        utils.testPutInFileSync(gKey, "")
        utils.testIncrByInFileAsync(gKey)

    it 'should increment 1 for an exists key with default param asynchronous', ->
        utils.testIncrByInFileAsync(gKey)

    it 'should increment 1 for an exists key(-1) with default param asynchronous', ->
        utils.testPutInFileSync(gKey, "-1")
        utils.testIncrByInFileAsync(gKey)

    it 'should increment 1 for an exists key(not a number) with default param asynchronous', ->
        utils.testPutInFileSync(gKey, utils.getRandomStr(33))
        utils.testIncrByInFileAsync(gKey, 2)

    it 'should increment 22 for an exists key with default param asynchronous', ->
        utils.testIncrByInFileAsync(gKey, 22)
