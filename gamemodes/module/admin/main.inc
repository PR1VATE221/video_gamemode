#include 					<YSI_Coding\y_hooks>

#include 					"define.inc"
#include					"functions.inc"
#include					"dialog.inc"
#include					"cmd.inc"
#include					"mysql_query.inc"

hook OnPlayerDisconnect(playerid) {
	if(Iter_Contains(admin, playerid)) {
		Iter_Remove(admin, playerid);
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}