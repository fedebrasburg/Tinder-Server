/*
 * WebContext.cpp
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#include <WebContext.h>

WebContext::WebContext(RestRequest& rq, RestResponse& rp, PathVariableExtractor & pv) {
	this->pv = &pv;
	this->request = &rq;
	this->response = &rp;

}

string WebContext::getParam(string name) {
	pv->get(name);
}

RestRequest& WebContext::getRequest() {
	return *request;
}

RestResponse& WebContext::getResponse() {
	return *response;
}

WebContext::~WebContext() {
	// TODO Auto-generated destructor stub
}

