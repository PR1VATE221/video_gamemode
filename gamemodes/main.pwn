#include 					<a_samp>
#include					<a_mysql>
#include					<sscanf2>
#include 					<YSI_Data\y_iterate>
#include 					<YSI_Coding\y_hooks>

new MySQL:dbHandle;

main() {}

public OnGameModeInit() {
	dbHandle = mysql_connect("localhost", "root", "123123", "main_server");
	return true;
}