#pragma once

#include <string>
#include <conio.h>
#include <nanodbc.h>
#include<iostream>


bool CheckUserInputForUserName(std::string UserName, nanodbc::connection conn);

bool CheckUserInputForPassword(std::string Password, nanodbc::connection conn);

bool LogMenu(nanodbc::connection conn);