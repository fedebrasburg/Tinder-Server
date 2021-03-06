/*
 * RestResponse.cpp
 *
 *  Created on: 30 de mar. de 2016
 *      Author: jonathan
 */

#include <RestResponse.h>
#include "Constants.h"
#include <climits>
RestResponse::RestResponse() {
	this->status = STATUS_200_OK;
	this->contentType = CONTENT_TYPE_JSON;
}

RestResponse::~RestResponse() {
}

void RestResponse::setStatus(string status) {
	this->status = status;
}

string RestResponse::getStatus() {
	return status;
}

void RestResponse::setContent(string body) {
	this->body = body;
}

void RestResponse::setContentType(string contentyType) {
	this->contentType = contentyType;
}

void RestResponse::render(mg_connection* nc) {
	unsigned long int size = this->body.size();
	mg_printf(nc, "HTTP/1.1 %s\r\n"
			"Content-Length: %i\r\n"
			"Content-Type: %s; charset=UTF-8\r\n\r\n",
			status.c_str(), (int)size, contentType.c_str());
	mg_printf(nc, "%s", body.c_str());
}

