#include "ClassUser.h"
#include <iostream>

User::User() {
	m_id = 0;
	m_UserName = "";
	m_Password = "Adminpass";
	m_role = 1;
	m_IdOfCreator = 0;
	m_IdOfUserLastChange = 0;

	std::cout << m_UserName << " !" << m_UserName.c_str() << std::endl;
}

int& User::getId() { return m_id; }

std::string& User::getUserName() { return m_UserName; }

std::string User::getPassword() { return m_Password; }

std::string User::getFirstName() { return m_FirstName; }

std::string User::getLastName() { return m_LastName; }

bool& User::getRole() { return m_role; }

int& User::getIdOfCreator() { return m_IdOfCreator; }

int& User::getIdOfUserLastChange() { return m_IdOfUserLastChange; }