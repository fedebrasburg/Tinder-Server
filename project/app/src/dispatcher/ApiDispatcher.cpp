/*
 * ApiDispatcher.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include "ApiDispatcher.h"



ApiDispatcher::ApiDispatcher() {


}

ApiDispatcher::~ApiDispatcher() {
	// TODO Auto-generated destructor stub
}

void ApiDispatcher::registerEndPoint(methods method, string uri,
		function<void(WebContext&)> func) {


}
