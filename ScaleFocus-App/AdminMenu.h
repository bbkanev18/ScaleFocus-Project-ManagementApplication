#pragma once

#include<iostream>
#include <conio.h>
#include <nanodbc.h>

#include "Login.h"

void adminMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subAdminUserMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subMenuListUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void getListOfAllUsers(nanodbc::connection conn);

void getUserListById(nanodbc::connection conn, int failToEnterId, int& idOfLoginUser, bool& RoleOfLoginUser);

void printUser(nanodbc::connection conn, nanodbc::result& result);