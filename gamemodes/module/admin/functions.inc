stock check_player_admin(playerid) {
	mysql_format(
		dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
		"SELECT * FROM `video_admin` WHERE `admin_name` = '%e'",
		player_name[playerid]
	);
	mysql_tquery(dbHandle, sqlSmallQuery, "check_admin", "i", playerid);
	return true;
}

stock is_player_admin(playerid) {
	if(Iter_Contains(admin, playerid)) {
		return true;
	} else {
		return false;
	}
}

stock send_admin_message(color, const string[]) {
	foreach(new i : admin) {
		SendClientMessage(i, color, string);
	}
	return true;
}