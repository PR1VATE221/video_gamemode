stock save_player_int(playerid, const var[], value) {
    mysql_format(
        dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
        "UPDATE `video_accounts` SET `%s` = '%i' WHERE `account_name` = '%s'",
        var, value, player_name[playerid]
    );
    mysql_pquery(dbHandle, sqlSmallQuery, "", "");
    printf(sqlSmallQuery);
    return true;
}

stock save_player_string(playerid, const var[], const value[]) {
    mysql_format(
        dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
        "UPDATE `video_accounts` SET `%s` = '%s' WHERE `account_name` = '%s'",
        var, value, player_name[playerid]
    );
    mysql_pquery(dbHandle, sqlSmallQuery, "", "");
    printf(sqlSmallQuery);
    return true;
}

stock save_player_float(playerid, const var[], Float:value) {
    mysql_format(
        dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
        "UPDATE `video_accounts` SET `%s` = '%f' WHERE `account_name` = '%s'",
        var, value, player_name[playerid]
    );
    mysql_pquery(dbHandle, sqlSmallQuery, "", "");
    printf(sqlSmallQuery);
    return true;
}

stock save_all_player_data(playerid) {
    save_player_int(playerid, "account_level", User[playerid][p_Level]);
    save_player_int(playerid, "account_cash", User[playerid][p_Cash]);
    save_player_string(playerid, "account_pame", User[playerid][p_PAme]);
    return true;
}