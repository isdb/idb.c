path=require('path')
fse=require('fs-extra')
fs=require('graceful-fs')
chance = new require('chance')()
idb = require('../index')
utils = require('./utils')

dataDir = path.join(__dirname, 'tmp')
gKey    = path.join(dataDir, 'u'+utils.getRandomStr(5))
gKey2   = path.join(dataDir, 'u'+utils.getRandomStr(5))
fse.remove(dataDir)

describe 'Create a Key Alias from a directory', ->

    it 'try to create an alias from a non-exists key synchronous', ->
        key    = utils.getRandomStr(5)
        alias  = utils.getRandomStr(5)
        utils.testCreateKeyAliasSync(dataDir, key, alias, idb.IDB_ERR_KEY_NOT_EXISTS)

    it 'create an alias from a key synchronous', ->
        key    = utils.getRandomStr(5)
        value  = utils.getRandomStr(5)
        utils.testPutInFileSync(path.join(dataDir, key), value)
        alias  = utils.getRandomStr(5)
        utils.testCreateKeyAliasSync(dataDir, key, alias)

    it 'create an alias from a key with child path synchronous', ->
        p      = "mykey"
        key    = path.join p, "other",utils.getRandomStr(5)
        value  = utils.getRandomStr(5)
        utils.testPutInFileSync(path.join(dataDir, key), value)
        alias  = path.join p, "another", utils.getRandomStr(5)
        utils.testCreateKeyAliasSync(dataDir, key, alias)

