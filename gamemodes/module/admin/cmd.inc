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

cmd:ban(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	
	new 
		banned_playerid,
		banned_days,
		banned_reason[100];

	if(sscanf(params, "dds[100]", banned_playerid, banned_days, banned_reason)) {
		SendClientMessage(playerid, -1, "Используйте: /ban [id] [кол-во дней] [причина]");
		return true;
	}

	if(!IsPlayerConnected(banned_playerid)) {
		SendClientMessage(playerid, -1, "Игрока с таким ID нет на сервере.");
		return true;
	}

	if(banned_days < 1 || banned_days > 31) {
		SendClientMessage(playerid, -1, "Количество дней от 1 до 31.");
		return true;
	}

	mysql_format(
		dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
		"SELECT `account_id` FROM `video_accounts` WHERE `account_name` = '%e' LIMIT 1",
		player_name[banned_playerid]
	);
	mysql_tquery(dbHandle, sqlSmallQuery, "check_ban_account_id", "iiis", playerid, banned_playerid, banned_days, banned_reason);
	return true;
}

cmd:mute(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	
	new 
		muted_playerid,
		mute_minutes,
		mute_reason[100];

	if(sscanf(params, "dds[100]", muted_playerid, mute_minutes, mute_reason)) {
		SendClientMessage(playerid, -1, "Используйте: /mute [id] [минуты] [причина]");
		return true;
	}

	if(!IsPlayerConnected(muted_playerid)) {
		SendClientMessage(playerid, -1, "Игрока с таким ID нет на сервере.");
		return true;
	}

	if(mute_minutes < 1 || mute_minutes > 120) {
		SendClientMessage(playerid, -1, "Время мута от 1 минуты до 120.");
		return true;
	}
	if(User[muted_playerid][p_MuteTime] != 0) {
		SendClientMessage(playerid, -1, "У игрока уже есть бан чата, используйте /unmute.");
		return true;
	}
	// TODO! Сделать проверку на то, есть ли уже мут
	User[muted_playerid][p_MuteTime] = (gettime() + (mute_minutes * 60));
	format(
		sqlSmallQuery, sizeof(sqlSmallQuery),
		"Администратор %s выдал бан чата игроку %s. Причина: %s",
		player_name[playerid], player_name[muted_playerid], mute_reason
	);
	SendClientMessageToAll(0xDE5555FF, sqlSmallQuery);
	save_player_int(muted_playerid, "account_mute", User[muted_playerid][p_MuteTime]);
	return true;
}

cmd:unmute(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	
	new 
		unmuted_playerid;

	if(sscanf(params, "d", unmuted_playerid)) {
		SendClientMessage(playerid, -1, "Используйте: /unmute [id]");
		return true;
	}

	if(!IsPlayerConnected(unmuted_playerid)) {
		SendClientMessage(playerid, -1, "Игрока с таким ID нет на сервере.");
		return true;
	}
	if(User[unmuted_playerid][p_MuteTime] == 0) {
		SendClientMessage(playerid, -1, "У этого игрока нет бана чата.");
		return true;
	}
	User[unmuted_playerid][p_MuteTime] = 0;

	format(
		sqlSmallQuery, sizeof(sqlSmallQuery),
		"Администратор %s снял бан чата у игрока %s.",
		player_name[playerid], player_name[unmuted_playerid]
	);
	SendClientMessageToAll(0xDE5555FF, sqlSmallQuery);
	save_player_int(unmuted_playerid, "account_mute", User[unmuted_playerid][p_MuteTime]);
	return true;
}

cmd:setlevel(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	new
		target_id,
		target_level;

	if(sscanf(params, "ii", target_id, target_level)) {
		SendClientMessage(playerid, -1, "Используйте: /setlevel [id] [уровень]");
		return true;
	}

	if(!IsPlayerConnected(target_id)) {
		SendClientMessage(playerid, -1, "Игрок с указанным ID не в сети.");
		return true;
	}

	if(target_level < 1 || target_level > 1000) {
		SendClientMessage(playerid, -1, "Уровень от 1 до 1000.");
		return true;
	}

	User[target_id][p_Level] = target_level;

	save_player_int(target_id, "account_level", User[target_id][p_Level]);

	return true;
}

cmd:setmoney(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	new
		target_id,
		target_cash;

	if(sscanf(params, "ii", target_id, target_cash)) {
		SendClientMessage(playerid, -1, "Используйте: /setmoney [id] [деньги]");
		return true;
	}

	if(!IsPlayerConnected(target_id)) {
		SendClientMessage(playerid, -1, "Игрок с указанным ID не в сети.");
		return true;
	}

	if(target_cash < 1 || target_cash > 500000) {
		SendClientMessage(playerid, -1, "Деньги от 1 до 500000.");
		return true;
	}

	User[target_id][p_Cash] = target_cash;

	save_player_int(target_id, "account_cash", User[target_id][p_Cash]);

	return true;
}