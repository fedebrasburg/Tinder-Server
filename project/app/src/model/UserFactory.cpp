#include "UserFactory.h"
#include "json/json/json.h"
#include "log/Logger.h"
#include "Location.h"

User* UserFactory::getUserByID(int id, SharedConnector connector){
	Json::Value root;
	if (!connector.getUserByID(id, root)) {
		Logger log;
		log.error("Error obteniendo user con id " + std::to_string(id));
		return NULL;
	}

	unordered_map<string, set<string>> interests;
	Location location(0.0, 0.0);
	string userid = root[0].get("id", "ERROR").asString();
	string name = root[0].get("name", "ERROR").asString();
	string alias = root[0].get("alias", "ERROR").asString();
	string email = root[0].get("email", "ERROR").asString();
	string photo = root[0].get("photo_profile", "ERROR").asString();
	User* newUser = new User(userid, name, alias, email, photo, interests, location);
	return newUser;
}
