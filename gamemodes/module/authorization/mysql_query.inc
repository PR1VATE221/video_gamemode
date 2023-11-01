forward sql_check_account(playerid);
public sql_check_account(playerid) {
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

forward registration_final(playerid);
public registration_final(playerid) {
	check_player_account(playerid);
	return true;
}

forward check_password(playerid);
public check_password(playerid) {
	new
		rows_count;

	cache_get_row_count(rows_count);

	if(!rows_count) {
		SendClientMessage(playerid, -1, "Неверный пароль");
		login_player(playerid);
		return true;
	} else {
		clear_player_chat(playerid);
		SpawnPlayer(playerid);
		check_player_admin(playerid);
		return true;
	}	
}