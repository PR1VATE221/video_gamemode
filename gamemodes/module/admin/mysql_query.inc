forward check_admin(playerid);
public check_admin(playerid) {
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

forward check_admin_pwd(playerid);
public check_admin_pwd(playerid) {
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

forward makeadmin_check(playerid, level, const admin_name[]);
public makeadmin_check(playerid, level, const admin_name[]) {
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