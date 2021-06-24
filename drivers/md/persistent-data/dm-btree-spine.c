<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-btree-internal.h"
#समावेश "dm-transaction-manager.h"

#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "btree spine"

/*----------------------------------------------------------------*/

#घोषणा BTREE_CSUM_XOR 121107

अटल पूर्णांक node_check(काष्ठा dm_block_validator *v,
		      काष्ठा dm_block *b,
		      माप_प्रकार block_size);

अटल व्योम node_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
				   काष्ठा dm_block *b,
				   माप_प्रकार block_size)
अणु
	काष्ठा btree_node *n = dm_block_data(b);
	काष्ठा node_header *h = &n->header;

	h->blocknr = cpu_to_le64(dm_block_location(b));
	h->csum = cpu_to_le32(dm_bm_checksum(&h->flags,
					     block_size - माप(__le32),
					     BTREE_CSUM_XOR));
पूर्ण

अटल पूर्णांक node_check(काष्ठा dm_block_validator *v,
		      काष्ठा dm_block *b,
		      माप_प्रकार block_size)
अणु
	काष्ठा btree_node *n = dm_block_data(b);
	काष्ठा node_header *h = &n->header;
	माप_प्रकार value_size;
	__le32 csum_disk;
	uपूर्णांक32_t flags;

	अगर (dm_block_location(b) != le64_to_cpu(h->blocknr)) अणु
		DMERR_LIMIT("node_check failed: blocknr %llu != wanted %llu",
			    le64_to_cpu(h->blocknr), dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	csum_disk = cpu_to_le32(dm_bm_checksum(&h->flags,
					       block_size - माप(__le32),
					       BTREE_CSUM_XOR));
	अगर (csum_disk != h->csum) अणु
		DMERR_LIMIT("node_check failed: csum %u != wanted %u",
			    le32_to_cpu(csum_disk), le32_to_cpu(h->csum));
		वापस -EILSEQ;
	पूर्ण

	value_size = le32_to_cpu(h->value_size);

	अगर (माप(काष्ठा node_header) +
	    (माप(__le64) + value_size) * le32_to_cpu(h->max_entries) > block_size) अणु
		DMERR_LIMIT("node_check failed: max_entries too large");
		वापस -EILSEQ;
	पूर्ण

	अगर (le32_to_cpu(h->nr_entries) > le32_to_cpu(h->max_entries)) अणु
		DMERR_LIMIT("node_check failed: too many entries");
		वापस -EILSEQ;
	पूर्ण

	/*
	 * The node must be either INTERNAL or LEAF.
	 */
	flags = le32_to_cpu(h->flags);
	अगर (!(flags & INTERNAL_NODE) && !(flags & LEAF_NODE)) अणु
		DMERR_LIMIT("node_check failed: node is neither INTERNAL or LEAF");
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा dm_block_validator btree_node_validator = अणु
	.name = "btree_node",
	.prepare_क्रम_ग_लिखो = node_prepare_क्रम_ग_लिखो,
	.check = node_check
पूर्ण;

/*----------------------------------------------------------------*/

पूर्णांक bn_पढ़ो_lock(काष्ठा dm_btree_info *info, dm_block_t b,
		 काष्ठा dm_block **result)
अणु
	वापस dm_पंचांग_पढ़ो_lock(info->पंचांग, b, &btree_node_validator, result);
पूर्ण

अटल पूर्णांक bn_shaकरोw(काष्ठा dm_btree_info *info, dm_block_t orig,
	      काष्ठा dm_btree_value_type *vt,
	      काष्ठा dm_block **result)
अणु
	पूर्णांक r, inc;

	r = dm_पंचांग_shaकरोw_block(info->पंचांग, orig, &btree_node_validator,
			       result, &inc);
	अगर (!r && inc)
		inc_children(info->पंचांग, dm_block_data(*result), vt);

	वापस r;
पूर्ण

पूर्णांक new_block(काष्ठा dm_btree_info *info, काष्ठा dm_block **result)
अणु
	वापस dm_पंचांग_new_block(info->पंचांग, &btree_node_validator, result);
पूर्ण

व्योम unlock_block(काष्ठा dm_btree_info *info, काष्ठा dm_block *b)
अणु
	dm_पंचांग_unlock(info->पंचांग, b);
पूर्ण

/*----------------------------------------------------------------*/

व्योम init_ro_spine(काष्ठा ro_spine *s, काष्ठा dm_btree_info *info)
अणु
	s->info = info;
	s->count = 0;
	s->nodes[0] = शून्य;
	s->nodes[1] = शून्य;
पूर्ण

व्योम निकास_ro_spine(काष्ठा ro_spine *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < s->count; i++) अणु
		unlock_block(s->info, s->nodes[i]);
	पूर्ण
पूर्ण

पूर्णांक ro_step(काष्ठा ro_spine *s, dm_block_t new_child)
अणु
	पूर्णांक r;

	अगर (s->count == 2) अणु
		unlock_block(s->info, s->nodes[0]);
		s->nodes[0] = s->nodes[1];
		s->count--;
	पूर्ण

	r = bn_पढ़ो_lock(s->info, new_child, s->nodes + s->count);
	अगर (!r)
		s->count++;

	वापस r;
पूर्ण

व्योम ro_pop(काष्ठा ro_spine *s)
अणु
	BUG_ON(!s->count);
	--s->count;
	unlock_block(s->info, s->nodes[s->count]);
पूर्ण

काष्ठा btree_node *ro_node(काष्ठा ro_spine *s)
अणु
	काष्ठा dm_block *block;

	BUG_ON(!s->count);
	block = s->nodes[s->count - 1];

	वापस dm_block_data(block);
पूर्ण

/*----------------------------------------------------------------*/

व्योम init_shaकरोw_spine(काष्ठा shaकरोw_spine *s, काष्ठा dm_btree_info *info)
अणु
	s->info = info;
	s->count = 0;
पूर्ण

व्योम निकास_shaकरोw_spine(काष्ठा shaकरोw_spine *s)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < s->count; i++) अणु
		unlock_block(s->info, s->nodes[i]);
	पूर्ण
पूर्ण

पूर्णांक shaकरोw_step(काष्ठा shaकरोw_spine *s, dm_block_t b,
		काष्ठा dm_btree_value_type *vt)
अणु
	पूर्णांक r;

	अगर (s->count == 2) अणु
		unlock_block(s->info, s->nodes[0]);
		s->nodes[0] = s->nodes[1];
		s->count--;
	पूर्ण

	r = bn_shaकरोw(s->info, b, vt, s->nodes + s->count);
	अगर (!r) अणु
		अगर (!s->count)
			s->root = dm_block_location(s->nodes[0]);

		s->count++;
	पूर्ण

	वापस r;
पूर्ण

काष्ठा dm_block *shaकरोw_current(काष्ठा shaकरोw_spine *s)
अणु
	BUG_ON(!s->count);

	वापस s->nodes[s->count - 1];
पूर्ण

काष्ठा dm_block *shaकरोw_parent(काष्ठा shaकरोw_spine *s)
अणु
	BUG_ON(s->count != 2);

	वापस s->count == 2 ? s->nodes[0] : शून्य;
पूर्ण

पूर्णांक shaकरोw_has_parent(काष्ठा shaकरोw_spine *s)
अणु
	वापस s->count >= 2;
पूर्ण

dm_block_t shaकरोw_root(काष्ठा shaकरोw_spine *s)
अणु
	वापस s->root;
पूर्ण

अटल व्योम le64_inc(व्योम *context, स्थिर व्योम *value_le)
अणु
	काष्ठा dm_transaction_manager *पंचांग = context;
	__le64 v_le;

	स_नकल(&v_le, value_le, माप(v_le));
	dm_पंचांग_inc(पंचांग, le64_to_cpu(v_le));
पूर्ण

अटल व्योम le64_dec(व्योम *context, स्थिर व्योम *value_le)
अणु
	काष्ठा dm_transaction_manager *पंचांग = context;
	__le64 v_le;

	स_नकल(&v_le, value_le, माप(v_le));
	dm_पंचांग_dec(पंचांग, le64_to_cpu(v_le));
पूर्ण

अटल पूर्णांक le64_equal(व्योम *context, स्थिर व्योम *value1_le, स्थिर व्योम *value2_le)
अणु
	__le64 v1_le, v2_le;

	स_नकल(&v1_le, value1_le, माप(v1_le));
	स_नकल(&v2_le, value2_le, माप(v2_le));
	वापस v1_le == v2_le;
पूर्ण

व्योम init_le64_type(काष्ठा dm_transaction_manager *पंचांग,
		    काष्ठा dm_btree_value_type *vt)
अणु
	vt->context = पंचांग;
	vt->size = माप(__le64);
	vt->inc = le64_inc;
	vt->dec = le64_dec;
	vt->equal = le64_equal;
पूर्ण
