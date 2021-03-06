/*
 * WebServer.cpp
 *
 *  Created on: 18 de mar. de 2016
 *      Author: jonathan
 */

#include <iostream>
#include "WebServer.h"

#include <string>
#include "mongoose/mongoose.h"
#include "log/Logger.h"
#include "RestRequest.h"
#include "RestResponse.h"
#include "Constants.h"
#include "WebServerException.h"

using namespace std;



static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

WebServer::WebServer(RequestDispatcher & dispatcher) {
	this->dispatcher = &dispatcher;
    connection = 0;
}

WebServer::~WebServer() {
	// TODO Auto-generated destructor stub
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  WebServer * server = (WebServer *) nc->user_data;
  RequestDispatcher * dispatcher = server->getDispatcher();
  struct http_message *hm = (struct http_message *) ev_data;
  if (ev == MG_EV_HTTP_REQUEST) {
	  RestRequest request(hm);
	  RestResponse response;
	  response.setStatus(STATUS_200_OK);
	  dispatcher->handle(request, response);
	  response.render(nc);
  }

}

void WebServer::start() {

	  struct mg_mgr mgr;

	  mg_mgr_init(&mgr, NULL);
	  connection = mg_bind(&mgr, s_http_port, ev_handler);
	  if(connection == 0) throw WebServerException("Port already in use");
	  mg_enable_multithreading(connection);
	  // Set up HTTP server parameters
	  mg_set_protocol_http_websocket(connection);
	  s_http_server_opts.document_root = ".";  // Serve current directory
	  s_http_server_opts.dav_document_root = ".";  // Allow access via WebDav
	  s_http_server_opts.enable_directory_listing = "yes";
	  connection->user_data = this;

	  string message = "Web server is now listening on port ";
	  message = message +s_http_port;

	  LOG_INFO << message;
	  for (;;) {
	    mg_mgr_poll(&mgr, 1000);
	  }
	  mg_mgr_free(&mgr);
}

RequestDispatcher * WebServer::getDispatcher() {
	return this->dispatcher;
}

