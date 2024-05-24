publics: sql_check_account(playerid) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		registration_player(playerid);
		return true;
	} else {
		login_player(playerid);
		return true;
	}
}

publics: registration_final(playerid) {
	check_player_account(playerid);
	return true;
}

publics: check_password(playerid) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		SendClientMessage(playerid, -1, "Неверный пароль");
		login_player(playerid);
		return true;
	} else {
		new 
			account_id;
		cache_get_value_name_int(0, "account_id", User[playerid][p_ID]);
		cache_get_value_name(0, "account_pame", User[playerid][p_PAme], 128);
		cache_get_value_name_int(0, "account_level", User[playerid][p_Level]);
		cache_get_value_name_int(0, "account_cash", User[playerid][p_Cash]);
		cache_get_value_name_int(0, "mutetime", User[playerid][p_MuteTime]);

		clear_player_chat(playerid);		
		check_player_banned(playerid, account_id);		
		return true;
	}	
}

publics: check_account_ban_sql(playerid) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		GetPlayerInventory(playerid);

		SpawnPlayer(playerid);
		check_player_admin(playerid);
		return true;
	} else {

		new
			ban_reason[100],
			ban_admin_name[MAX_PLAYER_NAME],
			ban_unban_time;

		cache_get_value_name_int(0, "ban_unban_time", ban_unban_time);
		cache_get_value_name(0, "ban_reason", ban_reason, 100);
		cache_get_value_name(0, "ban_admin_name", ban_admin_name, MAX_PLAYER_NAME);

		if(gettime() >= ban_unban_time) {
			new sql_ban_id;
			cache_get_value_name_int(0, "ban_id", sql_ban_id);
			mysql_format(
				dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
				"DELETE FROM `video_ban` WHERE `ban_id` = '%i'",
				sql_ban_id
			);
			mysql_tquery(dbHandle, sqlSmallQuery, "", "");
			SendClientMessage(playerid, -1, "Ваш аккаунт был разблокирован");
			SpawnPlayer(playerid);
			check_player_admin(playerid);
			return true;
		}

		format(
			sqlMediumQuery, sizeof(sqlMediumQuery),
			"{FFFFFF}\\cВаш игровой аккаунт заблокирован.\n\
			Никнейм аккаунта: {AFAFAF}%s\n\
			{FFFFFF}Причина блокировки: {AFAFAF}%s\n\
			{FFFFFF}Заблокировал аккаунт: {AFAFAF}%s\n\
			{FFFFFF}До разблокировки осталось: {AFAFAF}%i секунд",
			player_name[playerid],
			ban_reason,
			ban_admin_name,
			ban_unban_time - gettime()
		);

		Dialog_Open(
			playerid,
			Dialog:ban_dialog,
			DIALOG_STYLE_MSGBOX,
			"{FF0000}ВАШ АККАУНТ ЗАБЛОКИРОВАН",
			sqlMediumQuery,
			"Закрыть", ""
		);

		KickEx(playerid);
		return true;
	}
}