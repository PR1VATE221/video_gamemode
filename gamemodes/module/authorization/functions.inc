stock check_player_account(playerid) {
	mysql_format(
		dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
		"SELECT * FROM `video_accounts` WHERE `account_name` = '%e'",
		player_name[playerid]
	);

	mysql_tquery(dbHandle, sqlSmallQuery, "sql_check_account", "i", playerid);
	return true;
}

stock registration_player(playerid) {
	Dialog_Show(playerid, Dialog:registration_password);
	return true;
}

stock login_player(playerid) {
	Dialog_Show(playerid, Dialog:login_password);
	return true;
}

stock clear_player_chat(playerid) {
	for(new i = 0; i < 30; i++) {
		SendClientMessage(playerid, -1, "");
	}
	return true;
}

stock check_player_banned(playerid, account_id) {
	mysql_format(
		dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
		"SELECT * FROM `video_ban` WHERE `ban_player_id` = '%i'",
		account_id
	);
	mysql_tquery(dbHandle, sqlSmallQuery, "check_account_ban_sql", "i", playerid);
	return true;
}