/*
 * ApiDispatcher.cpp
 *
 *  Created on: 19 de mar. de 2016
 *      Author: jonathan
 */

#include "ApiDispatcher.h"
#include "NoSuchMethodHandlerException.h"
#include "log/Logger.h"

static string LOGGER_PREFIX = "DISPATCHER: ";
ApiDispatcher::ApiDispatcher() {
	this->defFunction = [](WebContext & wb){
		throw NoSuchMethodHandlerException(wb.getRequest().toString());
	};
	this->endpoints.insert(std::make_pair(RestRequest::GET, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::DELETE, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::POST, new EndPoint("/////", this->defFunction)));
	this->endpoints.insert(std::make_pair(RestRequest::PUT, new EndPoint("/////", this->defFunction)));

}

ApiDispatcher::~ApiDispatcher() {
}

void ApiDispatcher::registerEndPoint(RestRequest::Method method, string uri, function<void(WebContext&)> & handler) {
	EndPoint * ep = this->endpoints[method];
	ep->setNext(new EndPoint(uri,handler));

}

void ApiDispatcher::handle(RestRequest& request, RestResponse& response) {
	RestRequest::Method method = request.getMethod();
	if (this->endpoints.count(method) > 0) {
		EndPoint * ep = this->endpoints[method];
		try {
			ep->handle(request,response);
		} catch (NoSuchMethodHandlerException const & err) {
			LOG_INFO << LOGGER_PREFIX << err.what();
			response.setStatus("403");
		}

	}
	else {
		NoSuchMethodHandlerException err (request.toString());
		LOG_INFO << LOGGER_PREFIX << err.what();
		response.setStatus("403");
	}
}
