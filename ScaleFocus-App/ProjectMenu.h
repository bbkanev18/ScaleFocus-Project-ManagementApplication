#pragma once

#include <iostream>
#include <nanodbc.h>

#include "AdminMenu.h"
#include "TeamMenu.h"

void subProjectMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subPrintProjectMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void printAllProject(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void printOneProject(nanodbc::connection conn, nanodbc::result& result);