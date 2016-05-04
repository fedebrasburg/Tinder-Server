/*
 * UserResource.cpp
 *
 *  Created on: 7 de abr. de 2016
 *      Author: jonathan
 */

#include <api/UserResource.h>
#include "webserver/RestRequest.h"
#include <functional>
#include <UserNotFoundException.h>
#include "log/Logger.h"
#include "json/json/json.h"
#include "json/ParameterReader.h"
#include "ApiConstants.h"

using namespace std;

UserResource::UserResource(ProfileServices & services): service(services)  {

}

void UserResource::setup(ApiDispatcher& dispatcher) {
    using placeholders::_1;
	dispatcher.registerEndPoint(RestRequest::GET, "/user", (function<void (WebContext&)>)bind( &UserResource::getUser, this, _1 ));
	dispatcher.registerEndPoint(RestRequest::POST, "/user", (function<void (WebContext&)>)bind( &UserResource::putUser, this, _1 ));

}

void UserResource::getUser(WebContext& context) {
	try {
		User * user = service.getUserByID(context.getUserid());
		Json::Value result = user->toJson();
		delete user;
		Json::FastWriter writer;
		context.getResponse().setContent(writer.write(result));
	} catch (UserNotFoundException & e) {
		Json::Value result;
		result[STATUS_CODE_PARAM] = STATUS_CODE_AUTH_PROFILE_CREATION_REQUIRED;
		this->writeJson(context, result);
	}

}

void UserResource::putUser(WebContext& context) {
	Json::Value json;

	RestResource::readJson(context, json);
	User user(json);
	user.setId(context.getUserid());
	/*service.saveNewUser()*/
}

UserResource::~UserResource() {
}

