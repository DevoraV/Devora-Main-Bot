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


#ifndef MAIN_BOT_BOT_H
#define MAIN_BOT_BOT_H


#pragma once

#include <iostream>
#include <memory>

class bot {
public:
    void run(std::string token, std::string prefix);

};

inline std::unique_ptr<bot>Bot;



#endif //MAIN_BOT_BOT_H
