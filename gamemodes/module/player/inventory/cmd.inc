cmd:get_my_item(playerid) {
    format(
        sqlBiggestQuery, sizeof(sqlBiggestQuery),
        "����� �����\t�������\t����������\n"
    );

    for(new i = 0; i < MAX_SLOTS; i++) {
        format(
            sqlSmallQuery, sizeof(sqlSmallQuery),
            "���� �%i\t%s {AFAFAF}(model: %i)\t%i ��.\n",
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
        "�������� ���������",
        sqlBiggestQuery,
        "�������", ""
    );

    return true;
}