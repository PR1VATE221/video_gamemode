cmd:get_my_item(playerid) {
    format(
        sqlBiggestQuery, sizeof(sqlBiggestQuery),
        "Номер слота\tПредмет\tКоличество\n"
    );

    for(new i = 0; i < MAX_SLOTS; i++) {
        format(
            sqlSmallQuery, sizeof(sqlSmallQuery),
            "Слот №%i\t%s {AFAFAF}(model: %i)\t%i шт.\n",
            i, 
            Items[ UserInventory[playerid][pItem][i] ][iName],
            Items[ UserInventory[playerid][pItem][i] ][iModelID],
            UserInventory[playerid][pAmount][i]
        );
        strcat(sqlBiggestQuery, sqlSmallQuery);
    }

    Dialog_Open(
        playerid,
        Dialog:gInvTest,
        DIALOG_STYLE_TABLIST_HEADERS,
        "Проверка инвентаря",
        sqlBiggestQuery,
        "Закрыть", ""
    );

    return true;
}