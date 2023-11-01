#include 					<a_samp>
#include					<a_mysql>
#include					<sscanf2>
#include					<mdialog>
#include					<pawn.cmd>
#include 					<YSI_Data\y_iterate>
#include 					<YSI_Coding\y_hooks>

new MySQL:dbHandle;

new
	sqlSmallQuery[144],
	sqlMediumQuery[256],
	sqlBigQuery[516],
	sqlBiggestQuery[1024];

new player_name[MAX_PLAYERS][MAX_PLAYER_NAME];

main() {}

public OnGameModeInit() {
	AddPlayerClass(289, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	dbHandle = mysql_connect("localhost", "root", "123123", "main_server");
	SetGameModeText("VideoServer");
	return true;
}

public OnPlayerRequestClass(playerid, classid) {
	
	return true;
}

public OnPlayerConnect(playerid) {

	GetPlayerName(playerid, player_name[playerid], MAX_PLAYER_NAME);
	return true;
}

#include "module\authorization\main.inc" // Подключение модуля регистрации
#include "module\admin\main.inc" // Подключение системы администрирования