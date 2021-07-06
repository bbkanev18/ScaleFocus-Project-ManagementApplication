#pragma once

#include<iostream>
#include <string>
#include <conio.h>
#include <nanodbc.h>



bool CheckUserInputForUserName(std::string UserName, nanodbc::connection conn);

bool CheckUserInputForPassword(std::string Password, nanodbc::connection conn);

bool LogMenu(nanodbc::connection conn);

void HidePassword(std::string& Password);