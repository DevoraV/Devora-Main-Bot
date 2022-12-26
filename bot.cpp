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

/*Features I want to add
    Admin Ticket in select menu
*/

#include "bot.h"

/// Project
#include "config.h"
#include "roles.h"

/// Libraries
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <stdio.h>

/// SQL
#include <SQLiteCpp/SQLiteCpp.h>

/// DPP
#include <dpp/dpp.h>
#include <dpp/message.h>
#include <dpp/nlohmann/json.hpp>
#include <dpp/restrequest.h>


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool checkPerms(dpp::interaction i, dpp::snowflake roleId) {
    auto roles = i.member.roles;
    for (auto snowflake : roles){
        if (dpp::find_role(snowflake)->id == roleId)
            return true;
    }
    return false;
}


void bot::run(std::string token, std::string prefix) {
    dpp::cluster bot(token, dpp::intents::i_all_intents);

    dpp::cache<dpp::message> message_cache;

    bot.on_slashcommand([&](const dpp::slashcommand_t& event){

        if (event.command.get_command_name() == "ticket"){
            dpp::embed ticketEmbed = dpp::embed().
                    set_color(dpp::colors::blue).
                    set_title("Ticket").
                    set_description("If you want to create a ticket, press the button below!").
                    set_author(bot.me.username, "https://tommy31.social/", bot.me.get_avatar_url()).
                    set_timestamp(event.command.get_creation_time());
            bot.message_create(dpp::message(event.command.channel_id, ticketEmbed).add_component(
                    dpp::component().add_component(
                            dpp::component().set_label("Create Ticket").
                                    set_type(dpp::cot_button).
                                    set_emoji("📩").
                                    set_style(dpp::cos_primary).
                                    set_id("createTicket")
                    )
            ));
        } else if (event.command.get_command_name() == "rules"){
            dpp::embed rulesEmbed = dpp::embed().
                    set_title("Rules of Devora").
                    set_color(dpp::colors::blue).
                    set_author(bot.me.username, "https://tommy31.social", bot.me.get_avatar_url()).
                    set_timestamp(event.command.get_creation_time());
            bot.message_create(dpp::message(event.command.channel_id, rulesEmbed).add_component(
                    dpp::component().add_component(
                            dpp::component().set_label("Verify").
                                    set_type(dpp::cot_button).
                                    set_emoji("✅").
                                    set_style(dpp::cos_primary).
                                    set_id("acceptedRules")
                    )
            ));
        } else if (event.command.get_command_name() == "selfroles") {
            dpp::embed favGames = dpp::embed().
                    set_timestamp(event.command.get_creation_time()).
                    set_author(bot.me.username, "https://tommy31.social/", bot.me.get_avatar_url()).
                    set_title("Your favourite games").
                    set_description("Select your favourite games!").
                    set_color(dpp::colors::blue);
            bot.message_create(dpp::message(event.command.channel_id, favGames).add_component(
                    dpp::component().add_component(
                            dpp::component().set_label("CSGO").
                                    set_type(dpp::cot_button).
                                    set_emoji("🔫").
                                    set_style(dpp::cos_primary).
                                    set_id("csgo")
                    ).add_component(
                            dpp::component().set_label("Valorant").
                                    set_type(dpp::cot_button).
                                    set_emoji("🛡").
                                    set_style(dpp::cos_primary).
                                    set_id("valorant")
                    ).add_component(
                            dpp::component().set_label("Genshin Impact").
                                    set_type(dpp::cot_button).
                                    set_emoji("⚖️").
                                    set_style(dpp::cos_primary).
                                    set_id("genshin")
                    ).add_component(
                            dpp::component().set_label("Call of Duty").
                                    set_type(dpp::cot_button).
                                    set_emoji("⚰️").
                                    set_style(dpp::cos_primary).
                                    set_id("cod")
                    ).add_component(
                            dpp::component().set_label("Battlefield").
                                    set_type(dpp::cot_button).
                                    set_emoji("🔦").
                                    set_style(dpp::cos_primary).
                                    set_id("battlefield")
                    )
            ).add_component(
                    dpp::component().add_component(
                            dpp::component().set_label("Dark Souls").
                                    set_type(dpp::cot_button).
                                    set_emoji("⚔️").
                                    set_style(dpp::cos_primary).
                                    set_id("darksouls")
                    ).add_component(
                            dpp::component().set_label("Minecraft").
                                    set_type(dpp::cot_button).
                                    set_emoji("⛏").
                                    set_style(dpp::cos_primary).
                                    set_id("mc")
                    ).add_component(
                            dpp::component().set_label("Fall Guys").
                                    set_type(dpp::cot_button).
                                    set_emoji("🎮").
                                    set_style(dpp::cos_primary).
                                    set_id("fallguys")
                    ).add_component(
                            dpp::component().set_label("Roblox").
                                    set_type(dpp::cot_button).
                                    set_emoji("🟥").
                                    set_style(dpp::cos_primary).
                                    set_id("roblox")
                    ).add_component(
                            dpp::component().set_label("Terraria").
                                    set_type(dpp::cot_button).
                                    set_emoji("🪓").
                                    set_style(dpp::cos_primary).
                                    set_id("terraria")
                    )
            ));
        }else if(event.command.get_command_name() == "level"){
            SQLite::Database    db("../levelsystem.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement   query(db, "SELECT xp, level FROM level WHERE user_id IN (" + std::to_string(event.command.usr.id) + ");");

            while (query.executeStep()) {
                int xp = query.getColumn(0).getInt();
                int level = query.getColumn(1).getInt();
                dpp::embed emb = dpp::embed()
                        .set_color(dpp::colors::blue)
                        .set_title("Your current Level")
                        .add_field(
                                "Current Level",
                                std::to_string(level)
                                )
                                .add_field(
                                        "Current XP",
                                        std::to_string(xp) + "/500"
                                        );
                event.reply(dpp::message(event.command.channel_id, emb).set_flags(dpp::m_ephemeral));
            }
        }
    });
    bot.on_button_click([&bot](const dpp::button_click_t& event){
        if (event.custom_id == "createTicket"){

            dpp::interaction_modal_response modal("tckt", "Erstelle ein Ticket");
            modal.add_component(
                    dpp::component().
                            set_label("Ticket Grund").
                            set_id("modla_id").
                            set_type(dpp::cot_text).
                            set_placeholder("Ich möchte etwas melden!").
                            set_text_style(dpp::text_paragraph).
                            set_min_length(1).
                            set_max_length(200)
            );
            event.dialog(modal);


        }else if (event.custom_id == "delTicket"){
            event.reply(dpp::message(event.command.channel_id, "Ticket wird gelöscht!").set_flags(dpp::m_ephemeral));
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            dpp::snowflake cid = event.command.channel_id;
            bot.channel_delete(cid);

        }else if(event.custom_id == "createTranscript"){
            std::string msgs;
            bot.messages_get(event.command.channel_id, 0, 0, 0, 100, [&bot, &msgs, &event](const dpp::confirmation_callback_t &callback){
                if (!callback.is_error()){
                    auto messages = std::get<dpp::message_map>(callback.value);

                    std::string msg;
                    for (auto it{messages.cbegin()}; it != messages.cend(); ++it) {
                        std::cout << (it->second.content) << std::endl;
                        msg.append(it->second.content + "\n");
                    }

                    /*
                    auto command = "api_dev_key=rqICb8hqI9pKPqqrgF5hYNcSXGwQUehN&api_paste_code=" + msg + "&api_option=paste";
                    std::string readBuffer;
                    CURLcode ret;
                    CURL *hnd;

                    hnd = curl_easy_init();
                    curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
                    curl_easy_setopt(hnd, CURLOPT_URL, "https://pastebin.com/api/api_post.php");
                    curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
                    curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, "api_dev_key=rqICb8hqI9pKPqqrgF5hYNcSXGwQUehN&api_paste_code=test&api_option=paste");
                    curl_easy_setopt(hnd, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)81);
                    curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.79.1");
                    curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
                    curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
                    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
                    curl_easy_setopt(hnd, CURLOPT_FTP_SKIP_PASV_IP, 1L);
                    curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
                    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
                    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &readBuffer);


                    CURLOPT_WRITEDATA set to a objectpointer
                    CURLOPT_INTERLEAVEDATA set to a objectpointer
                    CURLOPT_WRITEFUNCTION set to a functionpointer
                    CURLOPT_READDATA set to a objectpointer
                    CURLOPT_READFUNCTION set to a functionpointer
                    CURLOPT_SEEKDATA set to a objectpointer
                    CURLOPT_SEEKFUNCTION set to a functionpointer
                    CURLOPT_ERRORBUFFER set to a objectpointer
                    CURLOPT_STDERR set to a objectpointer
                    CURLOPT_HEADERFUNCTION set to a functionpointer
                    CURLOPT_HEADERDATA set to a objectpointer



                    ret = curl_easy_perform(hnd);

                    curl_easy_cleanup(hnd);
                    hnd = NULL;
                    event.reply(dpp::message(event.command.channel_id, readBuffer));
                    return int(ret);
                    */
                } else {
                    bot.log(dpp::ll_error, "couldnt request messages" + callback.http_info.body);
                }
            });


        }else if(event.custom_id == "acceptedRules"){
            bot.guild_member_add_role(event.command.guild_id, event.command.usr.id, Config->userRole());
            event.reply(dpp::message(event.command.channel_id, "Du hast die Regeln akzeptiert!").set_flags(dpp::m_ephemeral));
        }else if(event.custom_id == "csgo"){
            if (checkPerms(event.command, Roles->csgo())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->csgo());
                event.reply(dpp::message(event.command.channel_id, "Ich habe ``CSGO`` aus deinen Rollen enfernt!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->csgo());
                event.reply(dpp::message(event.command.channel_id, "Ich habe ``CSGO`` deinen Rollen hinzugefügt!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "valorant"){
            if (checkPerms(event.command, Roles->valorant())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->valorant());
                event.reply(dpp::message(event.command.channel_id, "Ich habe ``Valorant`` aus deinen Rollen entfernt!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->valorant());
                event.reply(dpp::message(event.command.channel_id, "Ich habe ``Valorant`` deinen Rollen hinzugefügt!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "genshin"){
            if (checkPerms(event.command, Roles->genshin())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->genshin());
                event.reply(dpp::message(event.command.channel_id, "Ich habe ``Genshin Impact`` aus deinen Rollen entfernt!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->genshin());
                event.reply(dpp::message(event.command.channel_id, "Ich habe ``Genshin Impact`` deinen Rollen hinzugefügt!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "cod"){
            if (checkPerms(event.command, Roles->cod())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->cod());
                event.reply(dpp::message(event.command.channel_id, "Removed ``Call of Duty`` role from you!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->cod());
                event.reply(dpp::message(event.command.channel_id, "Added ``Call of Duty`` role to you!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "battlefield"){
            if (checkPerms(event.command, Roles->battlefield())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->battlefield());
                event.reply(dpp::message(event.command.channel_id, "Removed ``Battlefield`` role from you!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->battlefield());
                event.reply(dpp::message(event.command.channel_id, "Added ``Battlefield`` role to you!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "darksouls"){
            if (checkPerms(event.command, Roles->darksouls())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->darksouls());
                event.reply(dpp::message(event.command.channel_id, "Removed ``Darksouls``role from you!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->darksouls());
                event.reply(dpp::message(event.command.channel_id, "Added ``Darksouls`` role to you!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "mc"){
            if (checkPerms(event.command, Roles->minecraft())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->minecraft());
                event.reply(dpp::message(event.command.channel_id, "Removed ``Minecraft`` role from you!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->minecraft());
                event.reply(dpp::message(event.command.channel_id, "Added ``Minecraft`` role to you!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "fallguys"){
            if (checkPerms(event.command, Roles->fallguys())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->fallguys());
                event.reply(dpp::message(event.command.channel_id, "Removed ``Fall Guys`` role from you!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->fallguys());
                event.reply(dpp::message(event.command.channel_id, "Added ``Fall Guys`` role to you!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "roblox"){
            if (checkPerms(event.command, Roles->roblox())){
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->roblox());
                event.reply(dpp::message(event.command.channel_id, "Removed ``Roblox`` role from you!").set_flags(dpp::m_ephemeral));
            }else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->roblox());
                event.reply(dpp::message(event.command.channel_id, "Added ``Roblox`` role to you!").set_flags(dpp::m_ephemeral));
            }
        }else if(event.custom_id == "terraria") {
            if (checkPerms(event.command, Roles->terraria())) {
                bot.guild_member_remove_role(event.command.guild_id, event.command.member.user_id, Roles->terraria());
                event.reply(dpp::message(event.command.channel_id, "Removed ``Terraria`` role from you!").set_flags(
                        dpp::m_ephemeral));
            } else {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, Roles->terraria());
                event.reply(dpp::message(event.command.channel_id, "Added ``Terraria`` role to you!").set_flags(
                        dpp::m_ephemeral));
            }
        }
    });

    bot.on_form_submit([&](const dpp::form_submit_t & event) {

        dpp::channel ticketChannel = dpp::channel().
                set_name("ticket-" + event.command.usr.username).
                set_guild_id(event.command.guild_id).
                set_parent_id(Config->ticketParent()
                );

        dpp::permission_overwrite perm;

        perm.id = event.command.usr.id;
        perm.type = dpp::ot_member;
        perm.allow = dpp::p_view_channel +
                dpp::p_read_message_history +
                dpp::p_send_messages +
                dpp::p_attach_files;
        perm.deny = 0;

        ticketChannel.permission_overwrites.push_back(perm);

        dpp::embed emb = dpp::embed().
                set_author(bot.me.username, "https://x54x6fx6d.me/", bot.me.get_avatar_url()).
                set_color(dpp::colors::blue).
                set_title("Ticket created").
                set_description("Ticket was created by " + event.command.usr.get_mention()).
                add_field(
                "Reason",
                "test"
        );
        std::string v = std::get<std::string>(event.components[0].components[0].value);
        dpp::message m;
        dpp::snowflake tChId;
        dpp::snowflake ch;
        bot.channel_create(ticketChannel, [event, &bot, v, &tChId, &ticketChannel, &ch](const dpp::confirmation_callback_t &callback){
            if (callback.is_error()){
                std::cerr << "Error : Cannot create channels!";
                return;
            }else{
                auto channel = std::get<dpp::channel>(callback.value);
                ch = channel.id;
                dpp::embed embo = dpp::embed().
                        set_title("Ticket").
                        set_description("Created by " + event.command.usr.get_mention()).
                        set_color(dpp::colors::blue).
                        add_field(
                        "Reason",
                        v
                ).
                        set_footer("Devora x Main by Tommy31", bot.me.get_avatar_url()).
                        set_timestamp(event.command.get_creation_time()
                );

                bot.message_create(dpp::message(ch, embo).add_component(
                        dpp::component().add_component(
                                dpp::component().set_label("Delete Ticket").
                                        set_type(dpp::cot_button).
                                        set_emoji("❌").
                                        set_style(dpp::cos_danger).
                                        set_id("delTicket")
                        )
                )/*.add_component(
                                dpp::component().add_component(
                                        dpp::component().set_label("Create Transcript").
                                                set_type(dpp::cot_button).
                                                set_emoji("📥").
                                                set_style(dpp::cos_primary).
                                                set_id("createTranscript")
                                )
                        )*/);


                dpp::embed embLog = dpp::embed().
                        set_author(bot.me.username, "https://x54x6fx6d.me/", bot.me.get_avatar_url()).
                        set_color(dpp::colors::blue).
                        set_title("Ticket created").
                        set_description("Ticket was created by " + event.command.usr.get_mention() + "\n<#" + std::to_string(ch) + ">").
                        add_field(
                        "Reason",
                        v
                );
                bot.message_create(dpp::message(Config->ticketLogs(), embLog));
            }


        });

        m.set_content("You reason was: `" + v + "`").set_flags(dpp::m_ephemeral);
        event.reply(m);

    });

    bot.on_ready([&bot](const dpp::ready_t& event){
        std::cout << "Logged in as " << bot.me.username << "#" << bot.me.discriminator << std::endl;

        if (dpp::run_once<struct register_bot_commands>()) {
            dpp::slashcommand ticket("ticket", "creates a ticket", bot.me.id);
            dpp::slashcommand rules("rules", "sends rules", bot.me.id);
            dpp::slashcommand selfroles("selfroles", "sends selfroles embeds", bot.me.id);
            dpp::slashcommand lockVC("lockVC", "locks your vc", bot.me.id);
            dpp::slashcommand viewXP("level", "displays your level", bot.me.id);
            dpp::slashcommand setMaxUsers("setMaxUsers", "sets the maximum of users in your vc", bot.me.id);
            setMaxUsers.add_option(
                    dpp::command_option(dpp::co_integer, "maximum", "maximum users")
            );
            dpp::slashcommand kickUser("kickUser", "kicks the user out of your vc", bot.me.id);
            kickUser.add_option(
                    dpp::command_option(dpp::co_user, "user", "user to kick")
            );
            bot.global_command_create(ticket);
            bot.global_command_create(rules);
            bot.global_command_create(selfroles);
            bot.global_command_create(lockVC);
            bot.global_command_create(setMaxUsers);
            bot.global_command_create(kickUser);
            bot.global_command_create(viewXP);
        }
    });

    bot.on_guild_member_add([&bot](const dpp::guild_member_add_t& event){
        std::cout << "User joined : " << event.added.get_mention() << std::endl;
        dpp::embed emb = dpp::embed().
                set_color(dpp::colors::cyan).
                set_title("Willkommen!").
                set_author(bot.me.username, "https://tommy31.social/", bot.me.get_avatar_url()).
                set_image("").
                set_timestamp(event.added.joined_at).
                set_description(event.added.get_mention() + " Willkommen auf Devora!");
        bot.message_create(dpp::message(Config->welcomeChannel(), emb));

        try
        {
            SQLite::Database    db("../levelsystem.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement   query(db, "INSERT INTO level (user_id, xp, level) VALUES (" + std::to_string(event.added.user_id) + ", 0, 0);");

            while (query.executeStep())
            {
                std::cout << "Added " << event.added.get_mention() << " as " << event.added.user_id << " to levelsystem" << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cout << "exception: " << e.what() << std::endl;
        }

    });

    bot.on_guild_role_create([&bot](const dpp::guild_role_create_t& event){
        std::cout << "Role created : " << event.created->name << std::endl;
        std::string roleId = std::to_string(event.created->id);

        dpp::embed embedRoleCr = dpp::embed().
                set_title("Role Created!").
                set_author(bot.me.username, "https://tommy31.social/", bot.me.get_avatar_url()).
                set_color(dpp::colors::green).
                add_field(
                "Role name",
                event.created->name
        ).
                add_field(
                "Role ID",
                roleId
        );
        bot.message_create(dpp::message(Config->logChannel(), embedRoleCr));

    });


    bot.on_message_update([&](const dpp::message_update_t& event){
        std::string afterMessage = event.msg.content;
        dpp::message* beforeMessage = message_cache.find(event.msg.id);

        dpp::embed emb1 = dpp::embed().
                set_author(bot.me.username, "https://tommy31.social/", bot.me.get_avatar_url()).
                set_title("Message edited!").
                add_field(
                "Message before",
                beforeMessage->content
        ).
                add_field(
                "Message after",
                afterMessage
        ).
                set_color(dpp::colors::orange);

        dpp::snowflake log = 998029607812997181;

        bot.message_create(dpp::message(log, emb1));
    });

    bot.on_message_create([&](const dpp::message_create_t& event){
        try
        {
            SQLite::Database    db("../levelsystem.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
            SQLite::Statement   query(db, "SELECT xp, level FROM level WHERE user_id IN (" + std::to_string(event.msg.author.id) + ");");

            while (query.executeStep())
            {
                int xp = query.getColumn(0).getInt() + 20;
                int level = query.getColumn(1).getInt();
                if (xp >= 500){
                    SQLite::Statement qr(db, "UPDATE level SET xp = 0, level = " + std::to_string(level + 1) + " WHERE user_id = " + std::to_string(event.msg.author.id) + ";");
                    while (qr.executeStep()){
                        std::cout << "reached new level!";

                    }
                    dpp::embed levelemb = dpp::embed()
                            .set_color(dpp::colors::blue)
                            .set_description("Du bist ein Level aufgestiegen!")
                            .set_title("Level Up!")
                            .add_field(
                                    "Level",
                                    std::to_string(level + 1)
                                    )
                                    .add_field(
                                            "XP",
                                            std::to_string(0)
                                            );
                    bot.message_create(dpp::message(1032291491533570108, levelemb));
                }else {
                    SQLite::Statement qr(db, "UPDATE level SET xp = " + std::to_string(xp) + " WHERE user_id = " + std::to_string(event.msg.author.id) + ";");
                    while (qr.executeStep()){
                        std::cout << "more xp!";
                    }
                }
            }
        }
        catch (std::exception& e)
        {
            std::cout << "exception: " << e.what() << std::endl;
        }
    });

    bot.on_channel_create([&](const dpp::channel_create_t& event){
        if (event.created->name.find("ticket")){
            std::cout << "ticket opened!";
        }
    });
    bot.start(false);
}
