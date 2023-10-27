#include 					<YSI_Coding\y_hooks>

#include 					"define.inc"
#include					"functions.inc"
#include					"dialog.inc"
#include					"mysql_query.inc"

hook OnPlayerRequestClass(playerid, classid) {
	check_player_account(playerid);
	return Y_HOOKS_CONTINUE_RETURN_1;
}