#pragma once

#include<iostream>
#include <string>
#include <conio.h>
#include <nanodbc.h>

#include "sha256.h"



bool CheckUserInputForUserName(std::string UserName, nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

bool CheckUserInputForPassword(std::string Password, nanodbc::connection conn);

bool LogMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void HidePassword(std::string& Password);