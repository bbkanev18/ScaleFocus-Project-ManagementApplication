#pragma once

#include <iostream>
#include <nanodbc.h>

#include "AdminMenu.h"

// Team menu options:
// -> Print team
// -> Create team
// -> Edit Team
// -> Delete team
void subTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print menu options:
// -> Print all teams
// -> Print team by id
void subPrintTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Edit menu options:
// -> Edit team title
// -> Add user in team
// -> Remove user from a team
void subEditTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print all teams + assign users
void getAllTeams(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Get id of team and printed
int getTeamById(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print team
int printOneTeam(nanodbc::connection conn, nanodbc::result& result);

// Print username of the creator of the team
void printUserNameByIdOfCreatorOnTeam(nanodbc::connection conn, int id);

// Print username of user that last change the team
void printUserNameByIdOfLastChangeOnTeam(nanodbc::connection conn, int id);

// Get assign user in team and print (firstname , lastname)
int printUserAssignInTeam(nanodbc::connection conn, nanodbc::result& result);

// Creating team
void createTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Add users to team
void insertAssignUser(nanodbc::connection conn, int idOfTeam, int idOfUser, int& numberOfUser, int insertUserAlready[], int& counter, int& idOfLoginUser, bool& RoleOfLoginUser);

// Edit team title
void editTeamTitle(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Add user to team (in edit menu)
void addUserInTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Remove user from team (menu)
void removeUserFromTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Remove user from team (real remove)
void removeAssignUser(nanodbc::connection conn, int idOfTeam, int idOfUser, int& numberOfUser, int insertUserAlready[], int& counter, int& idOfLoginUser, bool& RoleOfLoginUser);

// Delete team from db
void deleteTeam(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Checking title
// -> already exist in database
void checkTitleInput(nanodbc::connection conn, std::string& checkString);
