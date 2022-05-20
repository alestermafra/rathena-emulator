// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Script Commands
 * Place the body of custom script commands in this file.
 * Format:
 *	BUILDIN_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//BUILDIN_FUNC(example)
//{
//	ShowInfo("buildin_example: It works!\n");
//	script_pushint(st,1);
//	return 0;
//}

/*==========================================
* Costume Items
*------------------------------------------*/
BUILDIN_FUNC(costume)
{
	int i = -1, num, ep;
	TBL_PC *sd;

	num = script_getnum(st, 2); // Equip Slot

	if (!script_rid2sd(sd))
		return SCRIPT_CMD_FAILURE;

	if (equip_index_check(num))
		i = pc_checkequip(sd, equip_bitmask[num]);
	if (i < 0)
		return SCRIPT_CMD_FAILURE;

	ep = sd->inventory.u.items_inventory[i].equip;
	if (!(ep&EQP_HEAD_LOW) && !(ep&EQP_HEAD_MID) && !(ep&EQP_HEAD_TOP) && !(ep&EQP_GARMENT)) {
		ShowError("buildin_costume: Attempted to convert non-cosmetic item to costume.");
		return SCRIPT_CMD_FAILURE;
	}
	log_pick_pc(sd, LOG_TYPE_SCRIPT, -1, &sd->inventory.u.items_inventory[i]);
	pc_unequipitem(sd, i, 2);
	clif_delitem(sd, i, 1, 3);
	// --------------------------------------------------------------------
	sd->inventory.u.items_inventory[i].refine = 0;
	sd->inventory.u.items_inventory[i].attribute = 0;
	sd->inventory.u.items_inventory[i].card[0] = CARD0_CREATE;
	sd->inventory.u.items_inventory[i].card[1] = 0;
	sd->inventory.u.items_inventory[i].card[2] = GetWord(battle_config.reserved_costume_id, 0);
	sd->inventory.u.items_inventory[i].card[3] = GetWord(battle_config.reserved_costume_id, 1);

	if (ep&EQP_HEAD_TOP) { ep &= ~EQP_HEAD_TOP; ep |= EQP_COSTUME_HEAD_TOP; }
	if (ep&EQP_HEAD_LOW) { ep &= ~EQP_HEAD_LOW; ep |= EQP_COSTUME_HEAD_LOW; }
	if (ep&EQP_HEAD_MID) { ep &= ~EQP_HEAD_MID; ep |= EQP_COSTUME_HEAD_MID; }
	if (ep&EQP_GARMENT) { ep &= EQP_GARMENT; ep |= EQP_COSTUME_GARMENT; }
	// --------------------------------------------------------------------
	log_pick_pc(sd, LOG_TYPE_SCRIPT, 1, &sd->inventory.u.items_inventory[i]);

	clif_additem(sd, i, 1, 0);
	pc_equipitem(sd, i, ep);
	clif_misceffect(&sd->bl, 3);

	return SCRIPT_CMD_SUCCESS;
}
