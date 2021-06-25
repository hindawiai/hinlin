<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_BTREE_INTERNAL_H
#घोषणा DM_BTREE_INTERNAL_H

#समावेश "dm-btree.h"

/*----------------------------------------------------------------*/

/*
 * We'll need 2 accessor functions क्रम n->csum and n->blocknr
 * to support dm-btree-spine.c in that हाल.
 */

क्रमागत node_flags अणु
	INTERNAL_NODE = 1,
	LEAF_NODE = 1 << 1
पूर्ण;

/*
 * Every btree node begins with this काष्ठाure.  Make sure it's a multiple
 * of 8-bytes in size, otherwise the 64bit keys will be mis-aligned.
 */
काष्ठा node_header अणु
	__le32 csum;
	__le32 flags;
	__le64 blocknr; /* Block this node is supposed to live in. */

	__le32 nr_entries;
	__le32 max_entries;
	__le32 value_size;
	__le32 padding;
पूर्ण __attribute__((packed, aligned(8)));

काष्ठा btree_node अणु
	काष्ठा node_header header;
	__le64 keys[];
पूर्ण __attribute__((packed, aligned(8)));


/*
 * Locks a block using the btree node validator.
 */
पूर्णांक bn_पढ़ो_lock(काष्ठा dm_btree_info *info, dm_block_t b,
		 काष्ठा dm_block **result);

व्योम inc_children(काष्ठा dm_transaction_manager *पंचांग, काष्ठा btree_node *n,
		  काष्ठा dm_btree_value_type *vt);

पूर्णांक new_block(काष्ठा dm_btree_info *info, काष्ठा dm_block **result);
व्योम unlock_block(काष्ठा dm_btree_info *info, काष्ठा dm_block *b);

/*
 * Spines keep track of the rolling locks.  There are 2 variants, पढ़ो-only
 * and one that uses shaकरोwing.  These are separate काष्ठाs to allow the
 * type checker to spot misuse, क्रम example accidentally calling पढ़ो_lock
 * on a shaकरोw spine.
 */
काष्ठा ro_spine अणु
	काष्ठा dm_btree_info *info;

	पूर्णांक count;
	काष्ठा dm_block *nodes[2];
पूर्ण;

व्योम init_ro_spine(काष्ठा ro_spine *s, काष्ठा dm_btree_info *info);
व्योम निकास_ro_spine(काष्ठा ro_spine *s);
पूर्णांक ro_step(काष्ठा ro_spine *s, dm_block_t new_child);
व्योम ro_pop(काष्ठा ro_spine *s);
काष्ठा btree_node *ro_node(काष्ठा ro_spine *s);

काष्ठा shaकरोw_spine अणु
	काष्ठा dm_btree_info *info;

	पूर्णांक count;
	काष्ठा dm_block *nodes[2];

	dm_block_t root;
पूर्ण;

व्योम init_shaकरोw_spine(काष्ठा shaकरोw_spine *s, काष्ठा dm_btree_info *info);
व्योम निकास_shaकरोw_spine(काष्ठा shaकरोw_spine *s);

पूर्णांक shaकरोw_step(काष्ठा shaकरोw_spine *s, dm_block_t b,
		काष्ठा dm_btree_value_type *vt);

/*
 * The spine must have at least one entry beक्रमe calling this.
 */
काष्ठा dm_block *shaकरोw_current(काष्ठा shaकरोw_spine *s);

/*
 * The spine must have at least two entries beक्रमe calling this.
 */
काष्ठा dm_block *shaकरोw_parent(काष्ठा shaकरोw_spine *s);

पूर्णांक shaकरोw_has_parent(काष्ठा shaकरोw_spine *s);

dm_block_t shaकरोw_root(काष्ठा shaकरोw_spine *s);

/*
 * Some अंतरभूतs.
 */
अटल अंतरभूत __le64 *key_ptr(काष्ठा btree_node *n, uपूर्णांक32_t index)
अणु
	वापस n->keys + index;
पूर्ण

अटल अंतरभूत व्योम *value_base(काष्ठा btree_node *n)
अणु
	वापस &n->keys[le32_to_cpu(n->header.max_entries)];
पूर्ण

अटल अंतरभूत व्योम *value_ptr(काष्ठा btree_node *n, uपूर्णांक32_t index)
अणु
	uपूर्णांक32_t value_size = le32_to_cpu(n->header.value_size);
	वापस value_base(n) + (value_size * index);
पूर्ण

/*
 * Assumes the values are suitably-aligned and converts to core क्रमmat.
 */
अटल अंतरभूत uपूर्णांक64_t value64(काष्ठा btree_node *n, uपूर्णांक32_t index)
अणु
	__le64 *values_le = value_base(n);

	वापस le64_to_cpu(values_le[index]);
पूर्ण

/*
 * Searching क्रम a key within a single node.
 */
पूर्णांक lower_bound(काष्ठा btree_node *n, uपूर्णांक64_t key);

बाह्य काष्ठा dm_block_validator btree_node_validator;

/*
 * Value type क्रम upper levels of multi-level btrees.
 */
बाह्य व्योम init_le64_type(काष्ठा dm_transaction_manager *पंचांग,
			   काष्ठा dm_btree_value_type *vt);

#पूर्ण_अगर	/* DM_BTREE_INTERNAL_H */
