// Created by matias on 4/19/16.
//

#include <ChatDAO.h>
#include <MatchDAO.h>
#include <ChatServices.h>
#include "ChatServicesTest.h"
#include <boost/filesystem.hpp>
#include <AuthenticationException.h>
#include <ChatException.h>

ChatServicesTest::ChatServicesTest() { }

ChatServicesTest::~ChatServicesTest() { }

void ChatServicesTest::SetUp() {
	this->matchDbConnector = new DBConnector(MATCH_DB_FILE);
	this->matchDao = new MatchDAO(this->matchDbConnector);
	this->chatDbConnector = new DBConnector(CHAT_DB_FILE);
	this->chatDao = new ChatDAO(this->chatDbConnector);
	this->matchServices = new MatchServices(this->matchDao, NULL); //Aca no hace falta el UserDAO*
};

void ChatServicesTest::TearDown() {
	delete this->matchDbConnector;
	delete this->chatDbConnector;
	delete this->chatDao;
	delete this->matchDao;
	boost::filesystem::remove_all(MATCH_DB_FILE);
	boost::filesystem::remove_all(CHAT_DB_FILE);

};
TEST_F(ChatServicesTest, sendMessageToNotLikedPerson) {
	ChatServices service(chatDao, matchDao);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "hola",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "chau", 2 , "", "F", 18,"", intereses, location);
	Message msg("prueba", &userA, &userB);
	try {
		service.sendMessageFromTo(&msg);
		FAIL();
	} catch (ChatException & ex) {
		ASSERT_EQ("Not match found", string(ex.what()));
	}

}

TEST_F(ChatServicesTest, sendMessageToLikedPerson) {
	ChatServices service(chatDao, matchDao);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "foo",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "foo", 2 , "", "F", 18,"", intereses, location);
	Message msg("prueba", &userA, &userB);
	this->matchServices->likeAUser(&userA, &userB);
	this->matchServices->likeAUser(&userB, &userA);
	service.sendMessageFromTo(&msg);
}


TEST_F(ChatServicesTest, getConversation) {
	ChatServices service(chatDao, matchDao);
	Location location;
	unordered_map<string, set<string>> intereses;
	User userA("matias", "foo",1 , "", "M", 18,"", intereses, location);
	User userB("maria", "foo", 2 , "", "F", 18,"", intereses, location);
	Message msg("prueba", &userA, &userB);
	this->matchServices->likeAUser(&userA, &userB);
	this->matchServices->likeAUser(&userB, &userA);
	service.sendMessageFromTo(&msg);
	std::list<Message*>* messages = service.getConversationBetweenUsers(&userA, &userB);
	ASSERT_EQ(1, messages->size());
}


