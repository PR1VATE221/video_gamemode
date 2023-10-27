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

main() {}

public OnGameModeInit() {
	dbHandle = mysql_connect("localhost", "root", "123123", "main_server");
	SetGameModeText("VideoServer");
	return true;
}

public OnPlayerRequestClass(playerid, classid) {
	
	return true;
}

#include "module\authorization\main.inc" // Подключение модуля регистрации