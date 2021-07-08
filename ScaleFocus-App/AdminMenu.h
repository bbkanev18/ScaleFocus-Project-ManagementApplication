#pragma once

#include<iostream>
#include <conio.h>
#include <nanodbc.h>

#include "Login.h"
#include "sha256.h"

void adminMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subAdminUserMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subMenuListUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void getListOfAllUsers(nanodbc::connection conn);

void getUserListById(nanodbc::connection conn, int failToEnterId, int& idOfLoginUser, bool& RoleOfLoginUser);

void printUser(nanodbc::connection conn, nanodbc::result& result);

void createUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subEditMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void editUserName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

int getUserByIdForEdit(nanodbc::connection conn, int failToEnterId, int& idOfLoginUser, bool& RoleOfLoginUser);