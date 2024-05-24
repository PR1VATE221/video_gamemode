#define MAX_SLOTS   15
#define MAX_ITEMS   100

enum pINV {
    pItem[MAX_SLOTS],
    pAmount[MAX_SLOTS]
}

new UserInventory[MAX_PLAYERS][pINV];

enum gITM {
    iName[100],
    iModelID,
    Float:iRotation[4],
    iMaxSlot
}

new Items[MAX_ITEMS][gITM];