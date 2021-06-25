<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017 Christoph Hellwig.
 */

#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trace.h"

/*
 * In-core extent record layout:
 *
 * +-------+----------------------------+
 * | 00:53 | all 54 bits of startoff    |
 * | 54:63 | low 10 bits of startblock  |
 * +-------+----------------------------+
 * | 00:20 | all 21 bits of length      |
 * |    21 | unwritten extent bit       |
 * | 22:63 | high 42 bits of startblock |
 * +-------+----------------------------+
 */
#घोषणा XFS_IEXT_STARTOFF_MASK		xfs_mask64lo(BMBT_STARTOFF_BITLEN)
#घोषणा XFS_IEXT_LENGTH_MASK		xfs_mask64lo(BMBT_BLOCKCOUNT_BITLEN)
#घोषणा XFS_IEXT_STARTBLOCK_MASK	xfs_mask64lo(BMBT_STARTBLOCK_BITLEN)

काष्ठा xfs_iext_rec अणु
	uपूर्णांक64_t			lo;
	uपूर्णांक64_t			hi;
पूर्ण;

/*
 * Given that the length can't be a zero, only an empty hi value indicates an
 * unused record.
 */
अटल bool xfs_iext_rec_is_empty(काष्ठा xfs_iext_rec *rec)
अणु
	वापस rec->hi == 0;
पूर्ण

अटल अंतरभूत व्योम xfs_iext_rec_clear(काष्ठा xfs_iext_rec *rec)
अणु
	rec->lo = 0;
	rec->hi = 0;
पूर्ण

अटल व्योम
xfs_iext_set(
	काष्ठा xfs_iext_rec	*rec,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	ASSERT((irec->br_startoff & ~XFS_IEXT_STARTOFF_MASK) == 0);
	ASSERT((irec->br_blockcount & ~XFS_IEXT_LENGTH_MASK) == 0);
	ASSERT((irec->br_startblock & ~XFS_IEXT_STARTBLOCK_MASK) == 0);

	rec->lo = irec->br_startoff & XFS_IEXT_STARTOFF_MASK;
	rec->hi = irec->br_blockcount & XFS_IEXT_LENGTH_MASK;

	rec->lo |= (irec->br_startblock << 54);
	rec->hi |= ((irec->br_startblock & ~xfs_mask64lo(10)) << (22 - 10));

	अगर (irec->br_state == XFS_EXT_UNWRITTEN)
		rec->hi |= (1 << 21);
पूर्ण

अटल व्योम
xfs_iext_get(
	काष्ठा xfs_bmbt_irec	*irec,
	काष्ठा xfs_iext_rec	*rec)
अणु
	irec->br_startoff = rec->lo & XFS_IEXT_STARTOFF_MASK;
	irec->br_blockcount = rec->hi & XFS_IEXT_LENGTH_MASK;

	irec->br_startblock = rec->lo >> 54;
	irec->br_startblock |= (rec->hi & xfs_mask64hi(42)) >> (22 - 10);

	अगर (rec->hi & (1 << 21))
		irec->br_state = XFS_EXT_UNWRITTEN;
	अन्यथा
		irec->br_state = XFS_EXT_NORM;
पूर्ण

क्रमागत अणु
	NODE_SIZE	= 256,
	KEYS_PER_NODE	= NODE_SIZE / (माप(uपूर्णांक64_t) + माप(व्योम *)),
	RECS_PER_LEAF	= (NODE_SIZE - (2 * माप(काष्ठा xfs_iext_leaf *))) /
				माप(काष्ठा xfs_iext_rec),
पूर्ण;

/*
 * In-core extent btree block layout:
 *
 * There are two types of blocks in the btree: leaf and inner (non-leaf) blocks.
 *
 * The leaf blocks are made up by %KEYS_PER_NODE extent records, which each
 * contain the startoffset, blockcount, startblock and unwritten extent flag.
 * See above क्रम the exact क्रमmat, followed by poपूर्णांकers to the previous and next
 * leaf blocks (अगर there are any).
 *
 * The inner (non-leaf) blocks first contain KEYS_PER_NODE lookup keys, followed
 * by an equal number of poपूर्णांकers to the btree blocks at the next lower level.
 *
 *		+-------+-------+-------+-------+-------+----------+----------+
 * Leaf:	| rec 1 | rec 2 | rec 3 | rec 4 | rec N | prev-ptr | next-ptr |
 *		+-------+-------+-------+-------+-------+----------+----------+
 *
 *		+-------+-------+-------+-------+-------+-------+------+-------+
 * Inner:	| key 1 | key 2 | key 3 | key N | ptr 1 | ptr 2 | ptr3 | ptr N |
 *		+-------+-------+-------+-------+-------+-------+------+-------+
 */
काष्ठा xfs_iext_node अणु
	uपूर्णांक64_t		keys[KEYS_PER_NODE];
#घोषणा XFS_IEXT_KEY_INVALID	(1ULL << 63)
	व्योम			*ptrs[KEYS_PER_NODE];
पूर्ण;

काष्ठा xfs_iext_leaf अणु
	काष्ठा xfs_iext_rec	recs[RECS_PER_LEAF];
	काष्ठा xfs_iext_leaf	*prev;
	काष्ठा xfs_iext_leaf	*next;
पूर्ण;

अंतरभूत xfs_extnum_t xfs_iext_count(काष्ठा xfs_अगरork *अगरp)
अणु
	वापस अगरp->अगर_bytes / माप(काष्ठा xfs_iext_rec);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_iext_max_recs(काष्ठा xfs_अगरork *अगरp)
अणु
	अगर (अगरp->अगर_height == 1)
		वापस xfs_iext_count(अगरp);
	वापस RECS_PER_LEAF;
पूर्ण

अटल अंतरभूत काष्ठा xfs_iext_rec *cur_rec(काष्ठा xfs_iext_cursor *cur)
अणु
	वापस &cur->leaf->recs[cur->pos];
पूर्ण

अटल अंतरभूत bool xfs_iext_valid(काष्ठा xfs_अगरork *अगरp,
		काष्ठा xfs_iext_cursor *cur)
अणु
	अगर (!cur->leaf)
		वापस false;
	अगर (cur->pos < 0 || cur->pos >= xfs_iext_max_recs(अगरp))
		वापस false;
	अगर (xfs_iext_rec_is_empty(cur_rec(cur)))
		वापस false;
	वापस true;
पूर्ण

अटल व्योम *
xfs_iext_find_first_leaf(
	काष्ठा xfs_अगरork	*अगरp)
अणु
	काष्ठा xfs_iext_node	*node = अगरp->अगर_u1.अगर_root;
	पूर्णांक			height;

	अगर (!अगरp->अगर_height)
		वापस शून्य;

	क्रम (height = अगरp->अगर_height; height > 1; height--) अणु
		node = node->ptrs[0];
		ASSERT(node);
	पूर्ण

	वापस node;
पूर्ण

अटल व्योम *
xfs_iext_find_last_leaf(
	काष्ठा xfs_अगरork	*अगरp)
अणु
	काष्ठा xfs_iext_node	*node = अगरp->अगर_u1.अगर_root;
	पूर्णांक			height, i;

	अगर (!अगरp->अगर_height)
		वापस शून्य;

	क्रम (height = अगरp->अगर_height; height > 1; height--) अणु
		क्रम (i = 1; i < KEYS_PER_NODE; i++)
			अगर (!node->ptrs[i])
				अवरोध;
		node = node->ptrs[i - 1];
		ASSERT(node);
	पूर्ण

	वापस node;
पूर्ण

व्योम
xfs_iext_first(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur)
अणु
	cur->pos = 0;
	cur->leaf = xfs_iext_find_first_leaf(अगरp);
पूर्ण

व्योम
xfs_iext_last(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur)
अणु
	पूर्णांक			i;

	cur->leaf = xfs_iext_find_last_leaf(अगरp);
	अगर (!cur->leaf) अणु
		cur->pos = 0;
		वापस;
	पूर्ण

	क्रम (i = 1; i < xfs_iext_max_recs(अगरp); i++) अणु
		अगर (xfs_iext_rec_is_empty(&cur->leaf->recs[i]))
			अवरोध;
	पूर्ण
	cur->pos = i - 1;
पूर्ण

व्योम
xfs_iext_next(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur)
अणु
	अगर (!cur->leaf) अणु
		ASSERT(cur->pos <= 0 || cur->pos >= RECS_PER_LEAF);
		xfs_iext_first(अगरp, cur);
		वापस;
	पूर्ण

	ASSERT(cur->pos >= 0);
	ASSERT(cur->pos < xfs_iext_max_recs(अगरp));

	cur->pos++;
	अगर (अगरp->अगर_height > 1 && !xfs_iext_valid(अगरp, cur) &&
	    cur->leaf->next) अणु
		cur->leaf = cur->leaf->next;
		cur->pos = 0;
	पूर्ण
पूर्ण

व्योम
xfs_iext_prev(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur)
अणु
	अगर (!cur->leaf) अणु
		ASSERT(cur->pos <= 0 || cur->pos >= RECS_PER_LEAF);
		xfs_iext_last(अगरp, cur);
		वापस;
	पूर्ण

	ASSERT(cur->pos >= 0);
	ASSERT(cur->pos <= RECS_PER_LEAF);

recurse:
	करो अणु
		cur->pos--;
		अगर (xfs_iext_valid(अगरp, cur))
			वापस;
	पूर्ण जबतक (cur->pos > 0);

	अगर (अगरp->अगर_height > 1 && cur->leaf->prev) अणु
		cur->leaf = cur->leaf->prev;
		cur->pos = RECS_PER_LEAF;
		जाओ recurse;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_iext_key_cmp(
	काष्ठा xfs_iext_node	*node,
	पूर्णांक			n,
	xfs_fileoff_t		offset)
अणु
	अगर (node->keys[n] > offset)
		वापस 1;
	अगर (node->keys[n] < offset)
		वापस -1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
xfs_iext_rec_cmp(
	काष्ठा xfs_iext_rec	*rec,
	xfs_fileoff_t		offset)
अणु
	uपूर्णांक64_t		rec_offset = rec->lo & XFS_IEXT_STARTOFF_MASK;
	uपूर्णांक32_t		rec_len = rec->hi & XFS_IEXT_LENGTH_MASK;

	अगर (rec_offset > offset)
		वापस 1;
	अगर (rec_offset + rec_len <= offset)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम *
xfs_iext_find_level(
	काष्ठा xfs_अगरork	*अगरp,
	xfs_fileoff_t		offset,
	पूर्णांक			level)
अणु
	काष्ठा xfs_iext_node	*node = अगरp->अगर_u1.अगर_root;
	पूर्णांक			height, i;

	अगर (!अगरp->अगर_height)
		वापस शून्य;

	क्रम (height = अगरp->अगर_height; height > level; height--) अणु
		क्रम (i = 1; i < KEYS_PER_NODE; i++)
			अगर (xfs_iext_key_cmp(node, i, offset) > 0)
				अवरोध;

		node = node->ptrs[i - 1];
		अगर (!node)
			अवरोध;
	पूर्ण

	वापस node;
पूर्ण

अटल पूर्णांक
xfs_iext_node_pos(
	काष्ठा xfs_iext_node	*node,
	xfs_fileoff_t		offset)
अणु
	पूर्णांक			i;

	क्रम (i = 1; i < KEYS_PER_NODE; i++) अणु
		अगर (xfs_iext_key_cmp(node, i, offset) > 0)
			अवरोध;
	पूर्ण

	वापस i - 1;
पूर्ण

अटल पूर्णांक
xfs_iext_node_insert_pos(
	काष्ठा xfs_iext_node	*node,
	xfs_fileoff_t		offset)
अणु
	पूर्णांक			i;

	क्रम (i = 0; i < KEYS_PER_NODE; i++) अणु
		अगर (xfs_iext_key_cmp(node, i, offset) > 0)
			वापस i;
	पूर्ण

	वापस KEYS_PER_NODE;
पूर्ण

अटल पूर्णांक
xfs_iext_node_nr_entries(
	काष्ठा xfs_iext_node	*node,
	पूर्णांक			start)
अणु
	पूर्णांक			i;

	क्रम (i = start; i < KEYS_PER_NODE; i++) अणु
		अगर (node->keys[i] == XFS_IEXT_KEY_INVALID)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक
xfs_iext_leaf_nr_entries(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_leaf	*leaf,
	पूर्णांक			start)
अणु
	पूर्णांक			i;

	क्रम (i = start; i < xfs_iext_max_recs(अगरp); i++) अणु
		अगर (xfs_iext_rec_is_empty(&leaf->recs[i]))
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t
xfs_iext_leaf_key(
	काष्ठा xfs_iext_leaf	*leaf,
	पूर्णांक			n)
अणु
	वापस leaf->recs[n].lo & XFS_IEXT_STARTOFF_MASK;
पूर्ण

अटल व्योम
xfs_iext_grow(
	काष्ठा xfs_अगरork	*अगरp)
अणु
	काष्ठा xfs_iext_node	*node = kmem_zalloc(NODE_SIZE, KM_NOFS);
	पूर्णांक			i;

	अगर (अगरp->अगर_height == 1) अणु
		काष्ठा xfs_iext_leaf *prev = अगरp->अगर_u1.अगर_root;

		node->keys[0] = xfs_iext_leaf_key(prev, 0);
		node->ptrs[0] = prev;
	पूर्ण अन्यथा  अणु
		काष्ठा xfs_iext_node *prev = अगरp->अगर_u1.अगर_root;

		ASSERT(अगरp->अगर_height > 1);

		node->keys[0] = prev->keys[0];
		node->ptrs[0] = prev;
	पूर्ण

	क्रम (i = 1; i < KEYS_PER_NODE; i++)
		node->keys[i] = XFS_IEXT_KEY_INVALID;

	अगरp->अगर_u1.अगर_root = node;
	अगरp->अगर_height++;
पूर्ण

अटल व्योम
xfs_iext_update_node(
	काष्ठा xfs_अगरork	*अगरp,
	xfs_fileoff_t		old_offset,
	xfs_fileoff_t		new_offset,
	पूर्णांक			level,
	व्योम			*ptr)
अणु
	काष्ठा xfs_iext_node	*node = अगरp->अगर_u1.अगर_root;
	पूर्णांक			height, i;

	क्रम (height = अगरp->अगर_height; height > level; height--) अणु
		क्रम (i = 0; i < KEYS_PER_NODE; i++) अणु
			अगर (i > 0 && xfs_iext_key_cmp(node, i, old_offset) > 0)
				अवरोध;
			अगर (node->keys[i] == old_offset)
				node->keys[i] = new_offset;
		पूर्ण
		node = node->ptrs[i - 1];
		ASSERT(node);
	पूर्ण

	ASSERT(node == ptr);
पूर्ण

अटल काष्ठा xfs_iext_node *
xfs_iext_split_node(
	काष्ठा xfs_iext_node	**nodep,
	पूर्णांक			*pos,
	पूर्णांक			*nr_entries)
अणु
	काष्ठा xfs_iext_node	*node = *nodep;
	काष्ठा xfs_iext_node	*new = kmem_zalloc(NODE_SIZE, KM_NOFS);
	स्थिर पूर्णांक		nr_move = KEYS_PER_NODE / 2;
	पूर्णांक			nr_keep = nr_move + (KEYS_PER_NODE & 1);
	पूर्णांक			i = 0;

	/* क्रम sequential append operations just spill over पूर्णांकo the new node */
	अगर (*pos == KEYS_PER_NODE) अणु
		*nodep = new;
		*pos = 0;
		*nr_entries = 0;
		जाओ करोne;
	पूर्ण


	क्रम (i = 0; i < nr_move; i++) अणु
		new->keys[i] = node->keys[nr_keep + i];
		new->ptrs[i] = node->ptrs[nr_keep + i];

		node->keys[nr_keep + i] = XFS_IEXT_KEY_INVALID;
		node->ptrs[nr_keep + i] = शून्य;
	पूर्ण

	अगर (*pos >= nr_keep) अणु
		*nodep = new;
		*pos -= nr_keep;
		*nr_entries = nr_move;
	पूर्ण अन्यथा अणु
		*nr_entries = nr_keep;
	पूर्ण
करोne:
	क्रम (; i < KEYS_PER_NODE; i++)
		new->keys[i] = XFS_IEXT_KEY_INVALID;
	वापस new;
पूर्ण

अटल व्योम
xfs_iext_insert_node(
	काष्ठा xfs_अगरork	*अगरp,
	uपूर्णांक64_t		offset,
	व्योम			*ptr,
	पूर्णांक			level)
अणु
	काष्ठा xfs_iext_node	*node, *new;
	पूर्णांक			i, pos, nr_entries;

again:
	अगर (अगरp->अगर_height < level)
		xfs_iext_grow(अगरp);

	new = शून्य;
	node = xfs_iext_find_level(अगरp, offset, level);
	pos = xfs_iext_node_insert_pos(node, offset);
	nr_entries = xfs_iext_node_nr_entries(node, pos);

	ASSERT(pos >= nr_entries || xfs_iext_key_cmp(node, pos, offset) != 0);
	ASSERT(nr_entries <= KEYS_PER_NODE);

	अगर (nr_entries == KEYS_PER_NODE)
		new = xfs_iext_split_node(&node, &pos, &nr_entries);

	/*
	 * Update the poपूर्णांकers in higher levels अगर the first entry changes
	 * in an existing node.
	 */
	अगर (node != new && pos == 0 && nr_entries > 0)
		xfs_iext_update_node(अगरp, node->keys[0], offset, level, node);

	क्रम (i = nr_entries; i > pos; i--) अणु
		node->keys[i] = node->keys[i - 1];
		node->ptrs[i] = node->ptrs[i - 1];
	पूर्ण
	node->keys[pos] = offset;
	node->ptrs[pos] = ptr;

	अगर (new) अणु
		offset = new->keys[0];
		ptr = new;
		level++;
		जाओ again;
	पूर्ण
पूर्ण

अटल काष्ठा xfs_iext_leaf *
xfs_iext_split_leaf(
	काष्ठा xfs_iext_cursor	*cur,
	पूर्णांक			*nr_entries)
अणु
	काष्ठा xfs_iext_leaf	*leaf = cur->leaf;
	काष्ठा xfs_iext_leaf	*new = kmem_zalloc(NODE_SIZE, KM_NOFS);
	स्थिर पूर्णांक		nr_move = RECS_PER_LEAF / 2;
	पूर्णांक			nr_keep = nr_move + (RECS_PER_LEAF & 1);
	पूर्णांक			i;

	/* क्रम sequential append operations just spill over पूर्णांकo the new node */
	अगर (cur->pos == RECS_PER_LEAF) अणु
		cur->leaf = new;
		cur->pos = 0;
		*nr_entries = 0;
		जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < nr_move; i++) अणु
		new->recs[i] = leaf->recs[nr_keep + i];
		xfs_iext_rec_clear(&leaf->recs[nr_keep + i]);
	पूर्ण

	अगर (cur->pos >= nr_keep) अणु
		cur->leaf = new;
		cur->pos -= nr_keep;
		*nr_entries = nr_move;
	पूर्ण अन्यथा अणु
		*nr_entries = nr_keep;
	पूर्ण
करोne:
	अगर (leaf->next)
		leaf->next->prev = new;
	new->next = leaf->next;
	new->prev = leaf;
	leaf->next = new;
	वापस new;
पूर्ण

अटल व्योम
xfs_iext_alloc_root(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur)
अणु
	ASSERT(अगरp->अगर_bytes == 0);

	अगरp->अगर_u1.अगर_root = kmem_zalloc(माप(काष्ठा xfs_iext_rec), KM_NOFS);
	अगरp->अगर_height = 1;

	/* now that we have a node step पूर्णांकo it */
	cur->leaf = अगरp->अगर_u1.अगर_root;
	cur->pos = 0;
पूर्ण

अटल व्योम
xfs_iext_पुनः_स्मृति_root(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur)
अणु
	पूर्णांक64_t new_size = अगरp->अगर_bytes + माप(काष्ठा xfs_iext_rec);
	व्योम *new;

	/* account क्रम the prev/next poपूर्णांकers */
	अगर (new_size / माप(काष्ठा xfs_iext_rec) == RECS_PER_LEAF)
		new_size = NODE_SIZE;

	new = kपुनः_स्मृति(अगरp->अगर_u1.अगर_root, new_size, GFP_NOFS | __GFP_NOFAIL);
	स_रखो(new + अगरp->अगर_bytes, 0, new_size - अगरp->अगर_bytes);
	अगरp->अगर_u1.अगर_root = new;
	cur->leaf = new;
पूर्ण

/*
 * Increment the sequence counter on extent tree changes. If we are on a COW
 * विभाजन, this allows the ग_लिखोback code to skip looking क्रम a COW extent अगर the
 * COW विभाजन hasn't changed. We use WRITE_ONCE here to ensure the update to the
 * sequence counter is seen beक्रमe the modअगरications to the extent tree itself
 * take effect.
 */
अटल अंतरभूत व्योम xfs_iext_inc_seq(काष्ठा xfs_अगरork *अगरp)
अणु
	WRITE_ONCE(अगरp->अगर_seq, READ_ONCE(अगरp->अगर_seq) + 1);
पूर्ण

व्योम
xfs_iext_insert(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_iext_cursor	*cur,
	काष्ठा xfs_bmbt_irec	*irec,
	पूर्णांक			state)
अणु
	काष्ठा xfs_अगरork	*अगरp = xfs_iext_state_to_विभाजन(ip, state);
	xfs_fileoff_t		offset = irec->br_startoff;
	काष्ठा xfs_iext_leaf	*new = शून्य;
	पूर्णांक			nr_entries, i;

	xfs_iext_inc_seq(अगरp);

	अगर (अगरp->अगर_height == 0)
		xfs_iext_alloc_root(अगरp, cur);
	अन्यथा अगर (अगरp->अगर_height == 1)
		xfs_iext_पुनः_स्मृति_root(अगरp, cur);

	nr_entries = xfs_iext_leaf_nr_entries(अगरp, cur->leaf, cur->pos);
	ASSERT(nr_entries <= RECS_PER_LEAF);
	ASSERT(cur->pos >= nr_entries ||
	       xfs_iext_rec_cmp(cur_rec(cur), irec->br_startoff) != 0);

	अगर (nr_entries == RECS_PER_LEAF)
		new = xfs_iext_split_leaf(cur, &nr_entries);

	/*
	 * Update the poपूर्णांकers in higher levels अगर the first entry changes
	 * in an existing node.
	 */
	अगर (cur->leaf != new && cur->pos == 0 && nr_entries > 0) अणु
		xfs_iext_update_node(अगरp, xfs_iext_leaf_key(cur->leaf, 0),
				offset, 1, cur->leaf);
	पूर्ण

	क्रम (i = nr_entries; i > cur->pos; i--)
		cur->leaf->recs[i] = cur->leaf->recs[i - 1];
	xfs_iext_set(cur_rec(cur), irec);
	अगरp->अगर_bytes += माप(काष्ठा xfs_iext_rec);

	trace_xfs_iext_insert(ip, cur, state, _RET_IP_);

	अगर (new)
		xfs_iext_insert_node(अगरp, xfs_iext_leaf_key(new, 0), new, 2);
पूर्ण

अटल काष्ठा xfs_iext_node *
xfs_iext_rebalance_node(
	काष्ठा xfs_iext_node	*parent,
	पूर्णांक			*pos,
	काष्ठा xfs_iext_node	*node,
	पूर्णांक			nr_entries)
अणु
	/*
	 * If the neighbouring nodes are completely full, or have dअगरferent
	 * parents, we might never be able to merge our node, and will only
	 * delete it once the number of entries hits zero.
	 */
	अगर (nr_entries == 0)
		वापस node;

	अगर (*pos > 0) अणु
		काष्ठा xfs_iext_node *prev = parent->ptrs[*pos - 1];
		पूर्णांक nr_prev = xfs_iext_node_nr_entries(prev, 0), i;

		अगर (nr_prev + nr_entries <= KEYS_PER_NODE) अणु
			क्रम (i = 0; i < nr_entries; i++) अणु
				prev->keys[nr_prev + i] = node->keys[i];
				prev->ptrs[nr_prev + i] = node->ptrs[i];
			पूर्ण
			वापस node;
		पूर्ण
	पूर्ण

	अगर (*pos + 1 < xfs_iext_node_nr_entries(parent, *pos)) अणु
		काष्ठा xfs_iext_node *next = parent->ptrs[*pos + 1];
		पूर्णांक nr_next = xfs_iext_node_nr_entries(next, 0), i;

		अगर (nr_entries + nr_next <= KEYS_PER_NODE) अणु
			/*
			 * Merge the next node पूर्णांकo this node so that we करोn't
			 * have to करो an additional update of the keys in the
			 * higher levels.
			 */
			क्रम (i = 0; i < nr_next; i++) अणु
				node->keys[nr_entries + i] = next->keys[i];
				node->ptrs[nr_entries + i] = next->ptrs[i];
			पूर्ण

			++*pos;
			वापस next;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
xfs_iext_हटाओ_node(
	काष्ठा xfs_अगरork	*अगरp,
	xfs_fileoff_t		offset,
	व्योम			*victim)
अणु
	काष्ठा xfs_iext_node	*node, *parent;
	पूर्णांक			level = 2, pos, nr_entries, i;

	ASSERT(level <= अगरp->अगर_height);
	node = xfs_iext_find_level(अगरp, offset, level);
	pos = xfs_iext_node_pos(node, offset);
again:
	ASSERT(node->ptrs[pos]);
	ASSERT(node->ptrs[pos] == victim);
	kmem_मुक्त(victim);

	nr_entries = xfs_iext_node_nr_entries(node, pos) - 1;
	offset = node->keys[0];
	क्रम (i = pos; i < nr_entries; i++) अणु
		node->keys[i] = node->keys[i + 1];
		node->ptrs[i] = node->ptrs[i + 1];
	पूर्ण
	node->keys[nr_entries] = XFS_IEXT_KEY_INVALID;
	node->ptrs[nr_entries] = शून्य;

	अगर (pos == 0 && nr_entries > 0) अणु
		xfs_iext_update_node(अगरp, offset, node->keys[0], level, node);
		offset = node->keys[0];
	पूर्ण

	अगर (nr_entries >= KEYS_PER_NODE / 2)
		वापस;

	अगर (level < अगरp->अगर_height) अणु
		/*
		 * If we aren't at the root yet try to find a neighbour node to
		 * merge with (or delete the node अगर it is empty), and then
		 * recurse up to the next level.
		 */
		level++;
		parent = xfs_iext_find_level(अगरp, offset, level);
		pos = xfs_iext_node_pos(parent, offset);

		ASSERT(pos != KEYS_PER_NODE);
		ASSERT(parent->ptrs[pos] == node);

		node = xfs_iext_rebalance_node(parent, &pos, node, nr_entries);
		अगर (node) अणु
			victim = node;
			node = parent;
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अगर (nr_entries == 1) अणु
		/*
		 * If we are at the root and only one entry is left we can just
		 * मुक्त this node and update the root poपूर्णांकer.
		 */
		ASSERT(node == अगरp->अगर_u1.अगर_root);
		अगरp->अगर_u1.अगर_root = node->ptrs[0];
		अगरp->अगर_height--;
		kmem_मुक्त(node);
	पूर्ण
पूर्ण

अटल व्योम
xfs_iext_rebalance_leaf(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur,
	काष्ठा xfs_iext_leaf	*leaf,
	xfs_fileoff_t		offset,
	पूर्णांक			nr_entries)
अणु
	/*
	 * If the neighbouring nodes are completely full we might never be able
	 * to merge our node, and will only delete it once the number of
	 * entries hits zero.
	 */
	अगर (nr_entries == 0)
		जाओ हटाओ_node;

	अगर (leaf->prev) अणु
		पूर्णांक nr_prev = xfs_iext_leaf_nr_entries(अगरp, leaf->prev, 0), i;

		अगर (nr_prev + nr_entries <= RECS_PER_LEAF) अणु
			क्रम (i = 0; i < nr_entries; i++)
				leaf->prev->recs[nr_prev + i] = leaf->recs[i];

			अगर (cur->leaf == leaf) अणु
				cur->leaf = leaf->prev;
				cur->pos += nr_prev;
			पूर्ण
			जाओ हटाओ_node;
		पूर्ण
	पूर्ण

	अगर (leaf->next) अणु
		पूर्णांक nr_next = xfs_iext_leaf_nr_entries(अगरp, leaf->next, 0), i;

		अगर (nr_entries + nr_next <= RECS_PER_LEAF) अणु
			/*
			 * Merge the next node पूर्णांकo this node so that we करोn't
			 * have to करो an additional update of the keys in the
			 * higher levels.
			 */
			क्रम (i = 0; i < nr_next; i++) अणु
				leaf->recs[nr_entries + i] =
					leaf->next->recs[i];
			पूर्ण

			अगर (cur->leaf == leaf->next) अणु
				cur->leaf = leaf;
				cur->pos += nr_entries;
			पूर्ण

			offset = xfs_iext_leaf_key(leaf->next, 0);
			leaf = leaf->next;
			जाओ हटाओ_node;
		पूर्ण
	पूर्ण

	वापस;
हटाओ_node:
	अगर (leaf->prev)
		leaf->prev->next = leaf->next;
	अगर (leaf->next)
		leaf->next->prev = leaf->prev;
	xfs_iext_हटाओ_node(अगरp, offset, leaf);
पूर्ण

अटल व्योम
xfs_iext_मुक्त_last_leaf(
	काष्ठा xfs_अगरork	*अगरp)
अणु
	अगरp->अगर_height--;
	kmem_मुक्त(अगरp->अगर_u1.अगर_root);
	अगरp->अगर_u1.अगर_root = शून्य;
पूर्ण

व्योम
xfs_iext_हटाओ(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_iext_cursor	*cur,
	पूर्णांक			state)
अणु
	काष्ठा xfs_अगरork	*अगरp = xfs_iext_state_to_विभाजन(ip, state);
	काष्ठा xfs_iext_leaf	*leaf = cur->leaf;
	xfs_fileoff_t		offset = xfs_iext_leaf_key(leaf, 0);
	पूर्णांक			i, nr_entries;

	trace_xfs_iext_हटाओ(ip, cur, state, _RET_IP_);

	ASSERT(अगरp->अगर_height > 0);
	ASSERT(अगरp->अगर_u1.अगर_root != शून्य);
	ASSERT(xfs_iext_valid(अगरp, cur));

	xfs_iext_inc_seq(अगरp);

	nr_entries = xfs_iext_leaf_nr_entries(अगरp, leaf, cur->pos) - 1;
	क्रम (i = cur->pos; i < nr_entries; i++)
		leaf->recs[i] = leaf->recs[i + 1];
	xfs_iext_rec_clear(&leaf->recs[nr_entries]);
	अगरp->अगर_bytes -= माप(काष्ठा xfs_iext_rec);

	अगर (cur->pos == 0 && nr_entries > 0) अणु
		xfs_iext_update_node(अगरp, offset, xfs_iext_leaf_key(leaf, 0), 1,
				leaf);
		offset = xfs_iext_leaf_key(leaf, 0);
	पूर्ण अन्यथा अगर (cur->pos == nr_entries) अणु
		अगर (अगरp->अगर_height > 1 && leaf->next)
			cur->leaf = leaf->next;
		अन्यथा
			cur->leaf = शून्य;
		cur->pos = 0;
	पूर्ण

	अगर (nr_entries >= RECS_PER_LEAF / 2)
		वापस;

	अगर (अगरp->अगर_height > 1)
		xfs_iext_rebalance_leaf(अगरp, cur, leaf, offset, nr_entries);
	अन्यथा अगर (nr_entries == 0)
		xfs_iext_मुक्त_last_leaf(अगरp);
पूर्ण

/*
 * Lookup the extent covering bno.
 *
 * If there is an extent covering bno वापस the extent index, and store the
 * expanded extent काष्ठाure in *gotp, and the extent cursor in *cur.
 * If there is no extent covering bno, but there is an extent after it (e.g.
 * it lies in a hole) वापस that extent in *gotp and its cursor in *cur
 * instead.
 * If bno is beyond the last extent वापस false, and वापस an invalid
 * cursor value.
 */
bool
xfs_iext_lookup_extent(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_अगरork	*अगरp,
	xfs_fileoff_t		offset,
	काष्ठा xfs_iext_cursor	*cur,
	काष्ठा xfs_bmbt_irec	*gotp)
अणु
	XFS_STATS_INC(ip->i_mount, xs_look_exlist);

	cur->leaf = xfs_iext_find_level(अगरp, offset, 1);
	अगर (!cur->leaf) अणु
		cur->pos = 0;
		वापस false;
	पूर्ण

	क्रम (cur->pos = 0; cur->pos < xfs_iext_max_recs(अगरp); cur->pos++) अणु
		काष्ठा xfs_iext_rec *rec = cur_rec(cur);

		अगर (xfs_iext_rec_is_empty(rec))
			अवरोध;
		अगर (xfs_iext_rec_cmp(rec, offset) >= 0)
			जाओ found;
	पूर्ण

	/* Try looking in the next node क्रम an entry > offset */
	अगर (अगरp->अगर_height == 1 || !cur->leaf->next)
		वापस false;
	cur->leaf = cur->leaf->next;
	cur->pos = 0;
	अगर (!xfs_iext_valid(अगरp, cur))
		वापस false;
found:
	xfs_iext_get(gotp, cur_rec(cur));
	वापस true;
पूर्ण

/*
 * Returns the last extent beक्रमe end, and अगर this extent करोesn't cover
 * end, update end to the end of the extent.
 */
bool
xfs_iext_lookup_extent_beक्रमe(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_अगरork	*अगरp,
	xfs_fileoff_t		*end,
	काष्ठा xfs_iext_cursor	*cur,
	काष्ठा xfs_bmbt_irec	*gotp)
अणु
	/* could be optimized to not even look up the next on a match.. */
	अगर (xfs_iext_lookup_extent(ip, अगरp, *end - 1, cur, gotp) &&
	    gotp->br_startoff <= *end - 1)
		वापस true;
	अगर (!xfs_iext_prev_extent(अगरp, cur, gotp))
		वापस false;
	*end = gotp->br_startoff + gotp->br_blockcount;
	वापस true;
पूर्ण

व्योम
xfs_iext_update_extent(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			state,
	काष्ठा xfs_iext_cursor	*cur,
	काष्ठा xfs_bmbt_irec	*new)
अणु
	काष्ठा xfs_अगरork	*अगरp = xfs_iext_state_to_विभाजन(ip, state);

	xfs_iext_inc_seq(अगरp);

	अगर (cur->pos == 0) अणु
		काष्ठा xfs_bmbt_irec	old;

		xfs_iext_get(&old, cur_rec(cur));
		अगर (new->br_startoff != old.br_startoff) अणु
			xfs_iext_update_node(अगरp, old.br_startoff,
					new->br_startoff, 1, cur->leaf);
		पूर्ण
	पूर्ण

	trace_xfs_bmap_pre_update(ip, cur, state, _RET_IP_);
	xfs_iext_set(cur_rec(cur), new);
	trace_xfs_bmap_post_update(ip, cur, state, _RET_IP_);
पूर्ण

/*
 * Return true अगर the cursor poपूर्णांकs at an extent and वापस the extent काष्ठाure
 * in gotp.  Else वापस false.
 */
bool
xfs_iext_get_extent(
	काष्ठा xfs_अगरork	*अगरp,
	काष्ठा xfs_iext_cursor	*cur,
	काष्ठा xfs_bmbt_irec	*gotp)
अणु
	अगर (!xfs_iext_valid(अगरp, cur))
		वापस false;
	xfs_iext_get(gotp, cur_rec(cur));
	वापस true;
पूर्ण

/*
 * This is a recursive function, because of that we need to be extremely
 * careful with stack usage.
 */
अटल व्योम
xfs_iext_destroy_node(
	काष्ठा xfs_iext_node	*node,
	पूर्णांक			level)
अणु
	पूर्णांक			i;

	अगर (level > 1) अणु
		क्रम (i = 0; i < KEYS_PER_NODE; i++) अणु
			अगर (node->keys[i] == XFS_IEXT_KEY_INVALID)
				अवरोध;
			xfs_iext_destroy_node(node->ptrs[i], level - 1);
		पूर्ण
	पूर्ण

	kmem_मुक्त(node);
पूर्ण

व्योम
xfs_iext_destroy(
	काष्ठा xfs_अगरork	*अगरp)
अणु
	xfs_iext_destroy_node(अगरp->अगर_u1.अगर_root, अगरp->अगर_height);

	अगरp->अगर_bytes = 0;
	अगरp->अगर_height = 0;
	अगरp->अगर_u1.अगर_root = शून्य;
पूर्ण
