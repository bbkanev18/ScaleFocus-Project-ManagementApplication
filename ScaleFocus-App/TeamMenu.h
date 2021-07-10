#pragma once

#include <iostream>
#include <nanodbc.h>

#include "AdminMenu.h"

void subTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subPrintTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void getAllTeams(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

int printOneTeam(nanodbc::connection conn, nanodbc::result& result);

void printUserNameByIdOfCreatorOnTeam(nanodbc::connection conn, int id);

void printUserNameByIdOfLastChangeOnTeam(nanodbc::connection conn, int id);

void printUserAssignInTeam(nanodbc::connection conn, nanodbc::result& result);