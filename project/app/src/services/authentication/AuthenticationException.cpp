//
// Created by matias on 4/24/16.
//

#include "AuthenticationException.h"


ChatException::ChatException(const string msg) : runtime_error(msg) {

}

ChatException::~ChatException() {

}

