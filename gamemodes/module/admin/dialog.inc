// =========================== [ Create ] ===========================

DialogCreate:admin_pwd(playerid) {
	Dialog_Open(
		playerid,
		Dialog:admin_pwd,
		DIALOG_STYLE_PASSWORD,
		"{AFAFAF}����������� � ����� ������",
		"{FFFFFF}������� ������ �� ������ �����. ��������:",
		"����", "�������"
	);
	return true;
}

// =========================== [ Response] ===========================

DialogResponse:admin_pwd(playerid, response, listitem, const inputtext[]) {
	if(!response) {
		return true;
	} else {
		mysql_format(
			dbHandle, sqlMediumQuery, sizeof(sqlMediumQuery),
			"SELECT * FROM `video_admin` WHERE `admin_name` = '%e' AND `admin_password` = '%e'",
			player_name[playerid], inputtext
		);
		mysql_tquery(dbHandle, sqlMediumQuery, "check_admin_pwd", "i", playerid);
		return true;
	}
}