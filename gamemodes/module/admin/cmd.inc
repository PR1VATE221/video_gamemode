cmd:a(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	if(sscanf(params, "s[90]", params[0])) {
		SendClientMessage(playerid, -1, "�����������: /a [�����]");
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
		SendClientMessage(playerid, -1, "�����������: /makeadmin [�������] [��� ����]");
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
		SendClientMessage(playerid, -1, "�����������: /ban [id] [���-�� ����] [�������]");
		return true;
	}

	if(!IsPlayerConnected(banned_playerid)) {
		SendClientMessage(playerid, -1, "������ � ����� ID ��� �� �������.");
		return true;
	}

	if(banned_days < 1 || banned_days > 31) {
		SendClientMessage(playerid, -1, "���������� ���� �� 1 �� 31.");
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

cmd:setlevel(playerid, params[]) {
	if(!is_player_admin(playerid)) {
		return true;
	}
	new
		target_id,
		target_level;

	if(sscanf(params, "ii", target_id, target_level)) {
		SendClientMessage(playerid, -1, "�����������: /setlevel [id] [�������]");
		return true;
	}

	if(!IsPlayerConnected(target_id)) {
		SendClientMessage(playerid, -1, "����� � ��������� ID �� � ����.");
		return true;
	}

	if(target_level < 1 || target_level > 1000) {
		SendClientMessage(playerid, -1, "������� �� 1 �� 1000.");
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
		SendClientMessage(playerid, -1, "�����������: /setmoney [id] [������]");
		return true;
	}

	if(!IsPlayerConnected(target_id)) {
		SendClientMessage(playerid, -1, "����� � ��������� ID �� � ����.");
		return true;
	}

	if(target_cash < 1 || target_cash > 500000) {
		SendClientMessage(playerid, -1, "������ �� 1 �� 500000.");
		return true;
	}

	User[target_id][p_Cash] = target_cash;

	save_player_int(target_id, "account_cash", User[target_id][p_Cash]);

	return true;
}