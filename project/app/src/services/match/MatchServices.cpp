//
// Created by matias on 4/24/16.
//

#include <ctime>
#include <iomanip>
#include "MatchServices.h"
#include "NoMoreCandidatesException.h"

using namespace std;

MatchServices::MatchServices(MatchDAO *matchDAO, ProfileServices *profile) {
	this->matchDao = matchDAO;
	this->profileServices = profile;
}

MatchServices::~MatchServices() { }

void MatchServices::likeAUser(User *userA, User *userB) {
	if (this->matchDao->checkForLike(userA, userB)) return;
	this->matchDao->saveLike(userA, userB);
	if (this->matchDao->checkForLike(userB, userA)) this->matchDao->addMatch(userA, userB);
}


int MatchServices::getNumberOfLikes(User *user) {
	return this->matchDao->getNumberOfLikes(user);
}

int MatchServices::getNumberOfMatches(User *user) {
	return this->matchDao->getNumberOfMatches(user);
}


list<User *> MatchServices::getMatchesForUser(User *user) {
	list<string> listaIDs = this->matchDao->getMatches(user);
	return this->getUsersFromIDs(listaIDs);
}


list<User *> MatchServices::getLikesForUser(User *user) {
	list<string> listaIDs = this->matchDao->getLikes(user);
	return this->getUsersFromIDs(listaIDs);
}

list<User *> MatchServices::getCandidatesForUser(User *user) {
	if (!this->hasRemainingCandidates(user)) throw NoMoreCandidatesException("Already requested candidates today.");
	auto candidates = this->profileServices->getAllUsers();
	//TODO Necesito los matches
	return candidates;
}


bool MatchServices::hasRemainingCandidates(User* user) {
	tm* lastDateStruct = this->matchDao->getLastRequestTime(user);
	std::time_t seconds = std::mktime( lastDateStruct );
	time_t currentDay = time(NULL);
	struct tm* timeStruct = localtime(&currentDay);
	string timeStamp(to_string(timeStruct->tm_mday) + "/" + to_string(timeStruct->tm_mon + 1) + "/" +
	                 to_string(timeStruct->tm_year + 1970));
	std::istringstream today(timeStamp);
	struct tm todayStruct;
	today >> std::get_time( &todayStruct, "%d/%m/%Y" );
	std::time_t secondsToday = std::mktime( & todayStruct );
	free(lastDateStruct);
	return seconds < secondsToday;
}

list<User*> MatchServices::getUsersFromIDs(list<string> &ids) {
	std::list<User*> listaUsers;
	for (auto itr = ids.begin(); itr != ids.end(); ++itr) {
		listaUsers.push_back(this->profileServices->getUserByID(*itr));
	}
	return listaUsers;
}


