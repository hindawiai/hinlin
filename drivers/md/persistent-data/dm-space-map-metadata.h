<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_SPACE_MAP_METADATA_H
#घोषणा DM_SPACE_MAP_METADATA_H

#समावेश "dm-transaction-manager.h"

#घोषणा DM_SM_METADATA_BLOCK_SIZE (4096 >> SECTOR_SHIFT)

/*
 * The metadata device is currently limited in size.
 *
 * We have one block of index, which can hold 255 index entries.  Each
 * index entry contains allocation info about ~16k metadata blocks.
 */
#घोषणा DM_SM_METADATA_MAX_BLOCKS (255 * ((1 << 14) - 64))
#घोषणा DM_SM_METADATA_MAX_SECTORS (DM_SM_METADATA_MAX_BLOCKS * DM_SM_METADATA_BLOCK_SIZE)

/*
 * Unक्रमtunately we have to use two-phase स्थिरruction due to the cycle
 * between the पंचांग and sm.
 */
काष्ठा dm_space_map *dm_sm_metadata_init(व्योम);

/*
 * Create a fresh space map.
 */
पूर्णांक dm_sm_metadata_create(काष्ठा dm_space_map *sm,
			  काष्ठा dm_transaction_manager *पंचांग,
			  dm_block_t nr_blocks,
			  dm_block_t superblock);

/*
 * Open from a previously-recorded root.
 */
पूर्णांक dm_sm_metadata_खोलो(काष्ठा dm_space_map *sm,
			काष्ठा dm_transaction_manager *पंचांग,
			व्योम *root_le, माप_प्रकार len);

#पूर्ण_अगर	/* DM_SPACE_MAP_METADATA_H */
