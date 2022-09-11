// /*
//  * Copyright (c) Tommy31
//  * All rights reserved.
//  * Only people with the explicit permission from Tommy31 are allowed to modify, share or distribute this code.
//  *
//  * You are NOT allowed to do any kind of modification to this software.
//  * You are NOT allowed to share this software with others without the explicit permission from Tommy31.
//  * You MUST acquire this software from official sources.
//  * You MUST run this software on your device as compiled file from our releases.
//  *

//
// Created by tommy31 on 12.09.22.
//


#ifndef MAIN_BOT_ROLES_H
#define MAIN_BOT_ROLES_H


#pragma once

#include <dpp/dpp.h>
#include <memory.h>
#include <iostream>

class roles {
public:
    dpp::snowflake csgo();
    dpp::snowflake valorant();
    dpp::snowflake genshin();
    dpp::snowflake cod();
    dpp::snowflake battlefield();
    dpp::snowflake darksouls();
    dpp::snowflake minecraft();
    dpp::snowflake fallguys();
    dpp::snowflake roblox();
    dpp::snowflake terraria();
};

inline std::unique_ptr<roles>Roles;

#endif //MAIN_BOT_ROLES_H
