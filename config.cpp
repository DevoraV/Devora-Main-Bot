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


#include "config.h"


std::string config::token() {
    std::string tk = "YOUR TOKEN";
    return tk;
}

std::string config::prefix() {
    return "$";
}

std::string config::pastebinApiToken() {
    return "rqICb8hqI9pKPqqrgF5hYNcSXGwQUehN";
}

dpp::snowflake config::logChannel() {
    return 1018232570074370048;
}

dpp::snowflake config::ticketParent() {
    return 1018232108243767408;
}

dpp::snowflake config::userRole() {
    return 1018211247176548413;
}

dpp::snowflake config::ticketLogs() {
    return 1018232570074370048;
}

dpp::snowflake config::welcomeChannel() {
    return 1020603895040462888;
}

std::string config::pastebin() {
    return "https://pastebin.com/api/api_post.php";
}
