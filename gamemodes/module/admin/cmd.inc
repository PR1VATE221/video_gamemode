cmd:a(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	if(sscanf(params, "s[90]", params[0])) {
		SendClientMessage(playerid, -1, "Используйте: /a [текст]");
		return true;
	}
	format(
		sqlSmallQuery, sizeof(sqlSmallQuery),
		"[A] %s[%i]: {FFFFFF}%s",
		player_name[playerid], playerid, params[0]
	);
	send_admin_message(0xFF0000FF, sqlSmallQuery);
	return true;
}

cmd:makeadmin(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	new
		cmd_admin_level,
		cmd_admin_name[MAX_PLAYER_NAME];
	
	if(sscanf(params, "ds[32]", cmd_admin_level, cmd_admin_name)) {
		SendClientMessage(playerid, -1, "Используйте: /makeadmin [уровень] [ник нейм]");
		return true;
	}

	mysql_format(
		dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
		"SELECT * FROM `video_admin` WHERE `admin_name` = '%e'",
		cmd_admin_name
	);
	mysql_tquery(dbHandle, sqlSmallQuery, "makeadmin_check", "iis", playerid, cmd_admin_level, cmd_admin_name);
	return true;
}