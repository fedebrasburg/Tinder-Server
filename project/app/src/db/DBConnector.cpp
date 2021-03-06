/*
 * DBConnector.cpp
 *
 *  Created on: Mar 21, 2016
 *      Author: matias
 */

#include "DBConnector.h"
#include "DBException.h"

DBConnector::DBConnector(std::string dbName) {
    rocksdb::Options options;
    options.create_if_missing = true;
    this->openedDB = dbName;
    this->status = rocksdb::DB::Open(options, this->openedDB, &this->db);
}

std::string DBConnector::getValueForKey(std::string key) {
    std::string value;
    rocksdb::Status s = db->Get(rocksdb::ReadOptions(), key, &value);
    if (s.ok()) return value;
    if(s.IsNotFound()) return "";
    throw DBException(s.ToString());
}

void DBConnector::putValueInKey(std::string key, std::string value) {
    rocksdb::Status s = db->Put(rocksdb::WriteOptions(), key, value);
    if (!s.ok())
    throw DBException(s.ToString());
}

void DBConnector::deleteKey(std::string key) {
    rocksdb::Status s = db->Delete(rocksdb::WriteOptions(), key);
    if (!s.ok())
    throw DBException(s.ToString());
}

DBConnector::~DBConnector() {
    delete this->db;
}

bool DBConnector::isOk() {
    if (this->status.ok()) {
        return true;
    }
    return false;
}

bool DBConnector::exist(std::string key) {
    string value;
    rocksdb::Status s = db->Get(rocksdb::ReadOptions(), key, &value);
    return !s.IsNotFound();
}



