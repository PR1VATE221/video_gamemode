stock GetPlayerInventory(playerid) {
    mysql_format(
        dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
        "SELECT * FROM `video_player_inventory` WHERE `account_id` = '%i'",
        User[playerid][p_ID]
    );
    mysql_tquery(
        dbHandle, sqlSmallQuery, "callback@main_inventory", "iii",
        playerid, 1, -1
    );
    return true;
}

stock LoadInventoryItems() {  
    mysql_tquery(
        dbHandle, "SELECT * FROM `video_items`", "callback@main_inventory", "iii", -1, 2, -1
    );
    return true;
}