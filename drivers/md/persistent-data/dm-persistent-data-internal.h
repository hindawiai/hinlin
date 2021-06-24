<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _DM_PERSISTENT_DATA_INTERNAL_H
#घोषणा _DM_PERSISTENT_DATA_INTERNAL_H

#समावेश "dm-block-manager.h"

अटल अंतरभूत अचिन्हित dm_hash_block(dm_block_t b, अचिन्हित hash_mask)
अणु
	स्थिर अचिन्हित BIG_PRIME = 4294967291UL;

	वापस (((अचिन्हित) b) * BIG_PRIME) & hash_mask;
पूर्ण

#पूर्ण_अगर	/* _PERSISTENT_DATA_INTERNAL_H */
