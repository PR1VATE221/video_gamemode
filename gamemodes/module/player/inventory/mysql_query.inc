publics: callback@main_inventory(playerid, idx, slot_id) {
    new
        row_count;

    cache_get_row_count(row_count);

    switch(idx) {
        case 1: {
            if(!row_count) {
                for(new i = 0; i < MAX_SLOTS; i++) {
                    mysql_format(
                        dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
                        "INSERT INTO `video_player_inventory` (`account_id`, `slot_id`) VALUES \
                        ('%i', '%i')",
                        User[playerid][p_ID], i
                    );
                    mysql_tquery(
                        dbHandle, sqlSmallQuery, "", ""
                    );
                }
                GetPlayerInventory(playerid);
                return true;
            } else {
                new
                    lSlotID;

                for(new i = 0; i < row_count; i ++) {
                    cache_get_value_name_int(i, "slot_id", lSlotID);
                    cache_get_value_name_int(i, "item_id", UserInventory[playerid][pItem][lSlotID]);
                    cache_get_value_name_int(i, "amount", UserInventory[playerid][pAmount][lSlotID]);
                }
            }
            return true;
        }
        case 2: {
            if(!row_count) {
                printf("[Ошибка] В базе нет данных о предметах");
                return true;
            } else {
                new iSlotID;
                for(new i = 0; i < row_count; i++) {
                    cache_get_value_name_int(i, "id", iSlotID);
                    cache_get_value_name(i, "name", Items[iSlotID][iName], 100);
                    cache_get_value_name_int(i, "model_id", Items[iSlotID][iModelID]);
                    cache_get_value_name_int(i, "max_slot", Items[iSlotID][iMaxSlot]);

                    cache_get_value_name_float(i, "x", Items[iSlotID][iRotation][0]);
                    cache_get_value_name_float(i, "y", Items[iSlotID][iRotation][1]);
                    cache_get_value_name_float(i, "z", Items[iSlotID][iRotation][2]);
                    cache_get_value_name_float(i, "size", Items[iSlotID][iRotation][3]);
                    printf("ID = %i | name = %s | max_slot = %i", iSlotID, Items[iSlotID][iName], Items[iSlotID][iMaxSlot]);
                }
                return true;
            }
        }
    }
    return true;
}