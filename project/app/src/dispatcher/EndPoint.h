/*
  @file EndPoint.h
 
   Created on: 19 de mar. de 2016
       @Author: jonathan
 */

#ifndef SRC_DISPATCHER_ENDPOINT_H_
#define SRC_DISPATCHER_ENDPOINT_H_
#include <string>

#include "../mongoose/mongoose.h"

using namespace std;


class EndPoint {
private:
	EndPoint * next;
	string expression;
	string uri;
public:
	EndPoint(string u);

/** \brief getAccounts - inputs accounts from the keyboard
 * \details This function reads input from the keyboard.
 * For every S or C entered, the function creates a new
 * Savings or Checking account object and adds it to the
 * account list. An X terminates the entry. Any other
 * input is assumed to be a deposit (numbers greater than
 * 0) or a withdrawal (numbers less than 0).
 *
 * \param accList list<AccountPtr>& the list of account
 *                objects created by getAccounts()
 * \return void
 */
	void setNext(EndPoint *);
	void handle(string & uri);
	virtual ~EndPoint();
};

#endif /* SRC_DISPATCHER_ENDPOINT_H_ */
