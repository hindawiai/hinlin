<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_SPACE_MAP_DISK_H
#घोषणा _LINUX_DM_SPACE_MAP_DISK_H

#समावेश "dm-block-manager.h"

काष्ठा dm_space_map;
काष्ठा dm_transaction_manager;

/*
 * Unक्रमtunately we have to use two-phase स्थिरruction due to the cycle
 * between the पंचांग and sm.
 */
काष्ठा dm_space_map *dm_sm_disk_create(काष्ठा dm_transaction_manager *पंचांग,
				       dm_block_t nr_blocks);

काष्ठा dm_space_map *dm_sm_disk_खोलो(काष्ठा dm_transaction_manager *पंचांग,
				     व्योम *root, माप_प्रकार len);

#पूर्ण_अगर /* _LINUX_DM_SPACE_MAP_DISK_H */
