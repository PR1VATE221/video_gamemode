stock check_player_account(playerid) {
	new player_name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, player_name, MAX_PLAYER_NAME);

	mysql_format(
		dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
		"SELECT * FROM `video_accounts` WHERE `account_name` = '%e'",
		player_name	
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