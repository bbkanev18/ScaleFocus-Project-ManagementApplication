#pragma once

#include<iostream>
#include <conio.h>
#include <nanodbc.h>

void adminMenu(nanodbc::connection conn);

void subMenuListUser(nanodbc::connection conn);

void getListOfAllUsers(nanodbc::connection conn);

void getUserListById(nanodbc::connection conn);

void printUser(nanodbc::connection conn, nanodbc::result& result);