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

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	if(Iter_Contains(admin, playerid)) {
		SetPlayerPos(
			playerid,
			fX, fY, fZ
		);
		SendClientMessage(playerid, 0x6F81E7FF, "¬ы были телепортированы на указанные координаты.");
		return Y_HOOKS_CONTINUE_RETURN_1;
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}