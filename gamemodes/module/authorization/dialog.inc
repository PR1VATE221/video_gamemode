// =========================== [ Create ] ===========================
DialogCreate:registration_password(playerid) {

	format(
		sqlSmallQuery, sizeof(sqlSmallQuery),
		"Здравствуйте, %s, введите ваш будующий пароль:",
		player_name[playerid]
	);

	Dialog_Open(
		playerid,
		Dialog:registration_password,
		DIALOG_STYLE_INPUT,
		"{AFAFAF}Регистрация",
		sqlSmallQuery,
		"Ввод", "Выход"
	);
	return true;
}

DialogCreate:login_password(playerid) {
	format(
		sqlSmallQuery, sizeof(sqlSmallQuery),
		"{FFFFFF}Здравствуйте, {AFAFAF}%s{FFFFFF}, аккаунт уже зарегистрирован, введите пароль:",
		player_name[playerid]
	);

	Dialog_Open(
		playerid,
		Dialog:login_password,
		DIALOG_STYLE_INPUT,
		"{AFAFAF}Регистрация",
		sqlSmallQuery,
		"Ввод", "Выход"
	);
	return true;
}

// =========================== [ Response] ===========================

DialogResponse:registration_password(playerid, response, listitem, const inputtext[]) {
	if(!response) {
		Kick(playerid);
		return true;
	} else {
		if(strlen(inputtext) < 3 || strlen(inputtext) > 36) {
			SendClientMessage(playerid, -1, "Неверная длина пароля");
			Dialog_Show(playerid, Dialog:registration_password);
			return true;
		}
		mysql_format(
			dbHandle, sqlSmallQuery, sizeof(sqlSmallQuery),
			"INSERT INTO `video_accounts` (`account_name`, `account_password`) VALUES ('%e', '%e')",
			player_name[playerid], inputtext
		);
		mysql_tquery(dbHandle, sqlSmallQuery, "registration_final", "i", playerid);
		return true;
	}
}

DialogResponse:login_password(playerid, response, listitem, const inputtext[]) {
	if(!response) {
		Kick(playerid);
		return true;
	} else {
		if(!strlen(inputtext)) {
			SendClientMessage(playerid, -1, "Вы ничего не ввели");
			Dialog_Show(playerid, Dialog:login_password);
			return true;
		}
		mysql_format(
			dbHandle, sqlMediumQuery, sizeof(sqlMediumQuery),
			"SELECT * FROM `video_accounts` WHERE `account_name` = '%e' AND `account_password` = '%e'",
			player_name[playerid], inputtext
		);
		mysql_tquery(dbHandle, sqlMediumQuery, "check_password", "i", playerid);
		return true;
	}
}