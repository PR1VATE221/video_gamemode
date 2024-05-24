#include 					<a_samp>
#include					<a_mysql>
#include					<sscanf2>
#include					<mdialog>
#include					<pawn.cmd>
#include 					<YSI_Data\y_iterate>
#include 					<YSI_Coding\y_hooks>

new MySQL:dbHandle;

#define publics:%0(%1)			forward %0(%1); public %0(%1)

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
	mysql_tquery(dbHandle, "SET NAMES utf8");
	mysql_tquery(dbHandle, "SET CHARACTER SET 'cp1251'");
	SetGameModeText("VideoServer");
	SetTimerEx("fresh", 1000, true, "");

	LoadInventoryItems();

	return true;
}

public OnPlayerRequestClass(playerid, classid) {
	
	return true;
}

public OnPlayerConnect(playerid) {

	GetPlayerName(playerid, player_name[playerid], MAX_PLAYER_NAME);
	return true;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	return true;
}

#include "module\player\main.inc" // Подключение модулей игрока
#include "module\authorization\main.inc" // Подключение модуля регистрации
#include "module\admin\main.inc" // Подключение системы администрирования

stock KickEx(playerid) {
	SetTimerEx("kick_timer", 200, false, "i", playerid);
	return true;
}

publics: kick_timer(playerid) {
	Kick(playerid);
	return true;
}

public OnPlayerText(playerid, text[]) {
	if(User[playerid][p_MuteTime] != 0) {
		SendClientMessage(playerid, 0xDE5555FF, "У Вас бан чата.");
		return false;
	}
	format(
		sqlSmallQuery, sizeof(sqlSmallQuery),
		"%s[%i] сказал: %s",
		player_name[playerid], playerid, text
	);
	SendBeside(playerid, 20.0, 0xAFAFAFFF, sqlSmallQuery);
	return false;
}

stock SendBeside(playerid, Float:range, color, const string[]) {
	new
		Float:lPlayerPos[3];
	
	GetPlayerPos(playerid, lPlayerPos[0], lPlayerPos[1], lPlayerPos[2]);

	foreach(new i : Player) {
		if(IsPlayerInRangeOfPoint(playerid, range, lPlayerPos[0], lPlayerPos[1], lPlayerPos[2])) {
			SendClientMessage(playerid, color, string);
		}
	}
	return true;
}

publics: fresh() {
	foreach(new i : Player) {
		if(gettime() > User[i][p_MuteTime] && User[i][p_MuteTime] != 0) {
			SendClientMessage(i, -1, "Ваш бан чата был снят, больше не нарушайте пожалуйста.");
			User[i][p_MuteTime] = 0;
		}
	}
	return true;
}