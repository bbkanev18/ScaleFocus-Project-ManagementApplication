#pragma once

#include <iostream>
#include <nanodbc.h>

#include "AdminMenu.h"

void subTeamMenu(nanodbc::connection conn, int& idOfLoginUser, bool& RoleOfLoginUser);