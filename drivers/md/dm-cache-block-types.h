<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_CACHE_BLOCK_TYPES_H
#घोषणा DM_CACHE_BLOCK_TYPES_H

#समावेश "persistent-data/dm-block-manager.h"

/*----------------------------------------------------------------*/

/*
 * It's helpful to get sparse to dअगरferentiate between indexes पूर्णांकo the
 * origin device, indexes पूर्णांकo the cache device, and indexes पूर्णांकo the
 * discard bitset.
 */

प्रकार dm_block_t __bitwise dm_oblock_t;
प्रकार uपूर्णांक32_t __bitwise dm_cblock_t;
प्रकार dm_block_t __bitwise dm_dblock_t;

अटल अंतरभूत dm_oblock_t to_oblock(dm_block_t b)
अणु
	वापस (__क्रमce dm_oblock_t) b;
पूर्ण

अटल अंतरभूत dm_block_t from_oblock(dm_oblock_t b)
अणु
	वापस (__क्रमce dm_block_t) b;
पूर्ण

अटल अंतरभूत dm_cblock_t to_cblock(uपूर्णांक32_t b)
अणु
	वापस (__क्रमce dm_cblock_t) b;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t from_cblock(dm_cblock_t b)
अणु
	वापस (__क्रमce uपूर्णांक32_t) b;
पूर्ण

अटल अंतरभूत dm_dblock_t to_dblock(dm_block_t b)
अणु
	वापस (__क्रमce dm_dblock_t) b;
पूर्ण

अटल अंतरभूत dm_block_t from_dblock(dm_dblock_t b)
अणु
	वापस (__क्रमce dm_block_t) b;
पूर्ण

#पूर्ण_अगर /* DM_CACHE_BLOCK_TYPES_H */
