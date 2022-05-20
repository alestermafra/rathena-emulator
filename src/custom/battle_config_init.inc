// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom battle config initializations
 * Place the definition of custom battle configuration initializations in this file.
 *
 * Do not forget to add a comma at the end of the line, if you want to add another config
 *
 * Format:
 *	 { "name", &battle_config.<variable name>, <default value>, <minimum value>, <maximum value> },
 **/

 {"auto_refine", &battle_config.auto_refine, 0, 0, MAX_REFINE},
 {"reserved_costume_id", &battle_config.reserved_costume_id, 999999998, 0, INT_MAX}
