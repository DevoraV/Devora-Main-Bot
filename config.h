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


#ifndef MAIN_BOT_CONFIG_H
#define MAIN_BOT_CONFIG_H


#pragma once

#include <iostream>
#include <memory.h>
#include <dpp/dpp.h>

class config {
public:
    std::string token();
    std::string prefix();
    std::string pastebin();
    std::string pastebinApiToken();

    dpp::snowflake logChannel();
    dpp::snowflake ticketParent();
    dpp::snowflake userRole();
    dpp::snowflake ticketLogs();
};

inline std::unique_ptr<config>Config;

#endif //MAIN_BOT_CONFIG_H
