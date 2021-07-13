#pragma once

#include<iostream>
#include <string>
#include <conio.h>
#include <nanodbc.h>

#include "sha256.h"
#include "AdminMenu.h"

// Checking username is in database from user input
bool CheckUserInputForUserName(std::string UserName, nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Checking password is in database from user input
bool CheckUserInputForPassword(std::string Password, nanodbc::connection conn);

// LogMenu
void LogMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Hide password wiht '*'
void HidePassword(std::string& Password);