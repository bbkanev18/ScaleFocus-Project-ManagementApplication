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

int printUser(nanodbc::connection conn, nanodbc::result& result);

void createUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subEditMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subDeleteMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void editUserName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void editPassword(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void editFirstName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void editLastName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

int getUserById(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);
