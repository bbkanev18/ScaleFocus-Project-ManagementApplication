#pragma once

#include<iostream>
#include <conio.h>
#include <nanodbc.h>

#include "Login.h"
#include "TeamMenu.h"
#include "ProjectMenu.h"
#include "sha256.h"

// Main Admin menu options:
// -> User Management
// -> Team Management
// -> Projects and Task Management
// -> Work log (in progess)
void adminMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// User management menu options:
// -> Print user
// -> Create user
// -> Edit user
// -> Delete user
void subAdminUserMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print menu options:
// -> Print all users
// -> Print user by id
void subMenuListUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Print all user
void getListOfAllUsers(nanodbc::connection conn);

// Print one user
int printUser(nanodbc::connection conn, nanodbc::result& result);

// Create user
void createUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Edit menu options:
// -> Chenge username
// -> Chenge password
// -> Chenge firstname
// -> Chenge lastname
void subEditMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Delete menu options:
// -> Delete user by id
// -> Delete all user (delete all user in db and back default admin)
void subDeleteMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Editn username
void editUserName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Edit password
void editPassword(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Edit firstname
void editFirstName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Edit lastname
void editLastName(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Get user by id
int getUserById(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Delete user by id
void deleteOneUser(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Delete all user and reset defauld user
void delteAllUsers(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Reseting default admin if there are changes in:
// -> Username
// -> Password
// -> Firstname
// -> Lastname
void resetDefaultAdmin(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);

// Get id of creator and print username
void printUserNameByIdOfCreator(nanodbc::connection conn, int id);

// Get id of last edit user and print username
void printUserNameByIdOfLastChange(nanodbc::connection conn, int id);

// Checking username
// -> already exist in database
void checkUserNameInput(nanodbc::connection conn, std::string& checkString);

// Checking password
// -> must 8 character long
// -> already exist in database
void checkPasswordInput(nanodbc::connection conn, std::string& checkString);

// Error cout name of problem and what is the proble
void errorMassage(std::string name, std::string problem);
