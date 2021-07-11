#pragma once

#include <iostream>
#include <nanodbc.h>

#include "AdminMenu.h"

void subTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subPrintTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void subEditTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void getAllTeams(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

int getTeamById(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

int printOneTeam(nanodbc::connection conn, nanodbc::result& result);

void printUserNameByIdOfCreatorOnTeam(nanodbc::connection conn, int id);

void printUserNameByIdOfLastChangeOnTeam(nanodbc::connection conn, int id);

int printUserAssignInTeam(nanodbc::connection conn, nanodbc::result& result);

void createTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

void insertAssignUser(nanodbc::connection conn, int idOfTeam, int idOfUser, int& numberOfUser, int insertUserAlready[], int& counter);

void editTeamTitle(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);