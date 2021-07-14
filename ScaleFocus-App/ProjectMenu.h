#pragma once

#include <iostream>
#include <nanodbc.h>

#include "AdminMenu.h"
#include "TeamMenu.h"

// Project and task menu options:
// -> Print project and task (in progress)
// -> Create project and tesk (in progress)
// -> Edit prohect and tesk (in progress)
// -> Delete project and task (in progress)
void subProjectMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print menu options:
// Print all project and task
// Print project by id (in progress)
void subPrintProjectMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print all project
void printAllProject(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print project
void printOneProject(nanodbc::connection conn, nanodbc::result& result);