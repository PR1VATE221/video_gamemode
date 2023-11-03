publics: check_admin(playerid) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		return true;
	} else {
		Dialog_Show(playerid, Dialog:admin_pwd);
		return true;
	}
}

publics: check_admin_pwd(playerid) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		SendClientMessage(playerid, -1, "Вы ввели неверный админ пароль.");
		check_player_admin(playerid);
		return true;
	} else {
		SendClientMessage(playerid, -1, "Вы успешно авторизовались в админ панель.");
		Iter_Add(admin, playerid);
		foreach(new i : admin) {
			format(sqlSmallQuery, sizeof(sqlSmallQuery), "%s авторизовался в админ. панель", player_name[playerid]);
			SendClientMessage(i, -1, sqlSmallQuery);
		}
		return true;
	}
}

publics: makeadmin_check(playerid, level, const admin_name[]) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		if(level <= 0) {
			SendClientMessage(playerid, -1, "Игрок с таким никнеймом не админ.");
			return true;
		} else {
			mysql_format(
				dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
				"INSERT INTO `video_admin` (`admin_name`, `admin_level`, `admin_password`) VALUE \
				('%e', '%i', '123123')",
				admin_name, level
			);

			mysql_tquery(dbHandle, sqlSmallQuery, "", "");

			format(
				sqlSmallQuery, sizeof(sqlSmallQuery),
				"Вы назначили %s на пост администратора %i уровня",
				admin_name, level
			);
			SendClientMessage(playerid, -1, sqlSmallQuery);
			return true;
		}
	} else {
		if(level <= 0) {
			mysql_format(
				dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
				"DELETE FROM `video_admin` WHERE `admin_name` = '%e'",
				admin_name
			);
			mysql_tquery(dbHandle, sqlSmallQuery, "", "");
			SendClientMessage(playerid, -1, "Игрок снят с админки");
			return true;
		} else {
			mysql_format(
				dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
				"UPDATE `video_admin` SET `admin_level` = '%i' WHERE `admin_name` = '%e'",
				level, admin_name
			);
			mysql_tquery(dbHandle, sqlSmallQuery, "", "");
			return true;
		}
	}
}

publics: check_ban_account_id(playerid, banned_playerid, banned_days, const banned_reason[]) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		SendClientMessage(playerid, -1, "Аккаунта этого игрока нет в базе данных.");
		return true;
	} else {
		new ban_sql_id;

		cache_get_value_name_int(0, "account_id", ban_sql_id);

		mysql_format(
			dbHandle, sqlMediumQuery, sizeof(sqlMediumQuery),
			"INSERT INTO `video_ban` (`ban_player_id`, `ban_unban_time`, `ban_reason`, `ban_admin_name`) VALUES \
			('%i', '%i', '%s', '%s')",
			ban_sql_id,
			gettime() + (((60 * 60) * 24) * banned_days),
			banned_reason,
			player_name[playerid]
		);
		mysql_tquery(dbHandle, sqlMediumQuery, "", "");

		format(
			sqlSmallQuery, sizeof(sqlSmallQuery),
			"Администратор %s заблокировал игрока %s на %i дней. Причина: %s",
			player_name[playerid],
			player_name[banned_playerid],
			banned_days,
			banned_reason
		);
		SendClientMessageToAll(0xFF0000FF, sqlSmallQuery);
		KickEx(banned_playerid);
	}
	return true; 
}