#pragma once
#include<string>
#include <iostream>
#include <string>

#include "sha256.h"

class User
{
public:
	User();
	int& getId();
	std::string& getUserName();
	std::string& getPassword();
	std::string getFirstName();
	std::string getLastName();
	bool& getRole(); //1 - for admin, 0 for user
	int& getIdOfCreator();
	int& getIdOfUserLastChange();
private:
	int m_id;
	std::string m_UserName;
	std::string m_Password;
	std::string m_FirstName;
	std::string m_LastName;
	bool m_role;
	int m_IdOfCreator;
	int m_IdOfUserLastChange;
};

