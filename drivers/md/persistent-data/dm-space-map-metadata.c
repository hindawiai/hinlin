<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-space-map.h"
#समावेश "dm-space-map-common.h"
#समावेश "dm-space-map-metadata.h"

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/device-mapper.h>
#समावेश <linux/kernel.h>

#घोषणा DM_MSG_PREFIX "space map metadata"

/*----------------------------------------------------------------*/

/*
 * An edge triggered threshold.
 */
काष्ठा threshold अणु
	bool threshold_set;
	bool value_set;
	dm_block_t threshold;
	dm_block_t current_value;
	dm_sm_threshold_fn fn;
	व्योम *context;
पूर्ण;

अटल व्योम threshold_init(काष्ठा threshold *t)
अणु
	t->threshold_set = false;
	t->value_set = false;
पूर्ण

अटल व्योम set_threshold(काष्ठा threshold *t, dm_block_t value,
			  dm_sm_threshold_fn fn, व्योम *context)
अणु
	t->threshold_set = true;
	t->threshold = value;
	t->fn = fn;
	t->context = context;
पूर्ण

अटल bool below_threshold(काष्ठा threshold *t, dm_block_t value)
अणु
	वापस t->threshold_set && value <= t->threshold;
पूर्ण

अटल bool threshold_alपढ़ोy_triggered(काष्ठा threshold *t)
अणु
	वापस t->value_set && below_threshold(t, t->current_value);
पूर्ण

अटल व्योम check_threshold(काष्ठा threshold *t, dm_block_t value)
अणु
	अगर (below_threshold(t, value) &&
	    !threshold_alपढ़ोy_triggered(t))
		t->fn(t->context);

	t->value_set = true;
	t->current_value = value;
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Space map पूर्णांकerface.
 *
 * The low level disk क्रमmat is written using the standard btree and
 * transaction manager.  This means that perक्रमming disk operations may
 * cause us to recurse पूर्णांकo the space map in order to allocate new blocks.
 * For this reason we have a pool of pre-allocated blocks large enough to
 * service any metadata_ll_disk operation.
 */

/*
 * FIXME: we should calculate this based on the size of the device.
 * Only the metadata space map needs this functionality.
 */
#घोषणा MAX_RECURSIVE_ALLOCATIONS 1024

क्रमागत block_op_type अणु
	BOP_INC,
	BOP_DEC
पूर्ण;

काष्ठा block_op अणु
	क्रमागत block_op_type type;
	dm_block_t block;
पूर्ण;

काष्ठा bop_ring_buffer अणु
	अचिन्हित begin;
	अचिन्हित end;
	काष्ठा block_op bops[MAX_RECURSIVE_ALLOCATIONS + 1];
पूर्ण;

अटल व्योम brb_init(काष्ठा bop_ring_buffer *brb)
अणु
	brb->begin = 0;
	brb->end = 0;
पूर्ण

अटल bool brb_empty(काष्ठा bop_ring_buffer *brb)
अणु
	वापस brb->begin == brb->end;
पूर्ण

अटल अचिन्हित brb_next(काष्ठा bop_ring_buffer *brb, अचिन्हित old)
अणु
	अचिन्हित r = old + 1;
	वापस r >= ARRAY_SIZE(brb->bops) ? 0 : r;
पूर्ण

अटल पूर्णांक brb_push(काष्ठा bop_ring_buffer *brb,
		    क्रमागत block_op_type type, dm_block_t b)
अणु
	काष्ठा block_op *bop;
	अचिन्हित next = brb_next(brb, brb->end);

	/*
	 * We करोn't allow the last bop to be filled, this way we can
	 * dअगरferentiate between full and empty.
	 */
	अगर (next == brb->begin)
		वापस -ENOMEM;

	bop = brb->bops + brb->end;
	bop->type = type;
	bop->block = b;

	brb->end = next;

	वापस 0;
पूर्ण

अटल पूर्णांक brb_peek(काष्ठा bop_ring_buffer *brb, काष्ठा block_op *result)
अणु
	काष्ठा block_op *bop;

	अगर (brb_empty(brb))
		वापस -ENODATA;

	bop = brb->bops + brb->begin;
	result->type = bop->type;
	result->block = bop->block;

	वापस 0;
पूर्ण

अटल पूर्णांक brb_pop(काष्ठा bop_ring_buffer *brb)
अणु
	अगर (brb_empty(brb))
		वापस -ENODATA;

	brb->begin = brb_next(brb, brb->begin);

	वापस 0;
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा sm_metadata अणु
	काष्ठा dm_space_map sm;

	काष्ठा ll_disk ll;
	काष्ठा ll_disk old_ll;

	dm_block_t begin;

	अचिन्हित recursion_count;
	अचिन्हित allocated_this_transaction;
	काष्ठा bop_ring_buffer uncommitted;

	काष्ठा threshold threshold;
पूर्ण;

अटल पूर्णांक add_bop(काष्ठा sm_metadata *smm, क्रमागत block_op_type type, dm_block_t b)
अणु
	पूर्णांक r = brb_push(&smm->uncommitted, type, b);

	अगर (r) अणु
		DMERR("too many recursive allocations");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक commit_bop(काष्ठा sm_metadata *smm, काष्ठा block_op *op)
अणु
	पूर्णांक r = 0;
	क्रमागत allocation_event ev;

	चयन (op->type) अणु
	हाल BOP_INC:
		r = sm_ll_inc(&smm->ll, op->block, &ev);
		अवरोध;

	हाल BOP_DEC:
		r = sm_ll_dec(&smm->ll, op->block, &ev);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम in(काष्ठा sm_metadata *smm)
अणु
	smm->recursion_count++;
पूर्ण

अटल पूर्णांक apply_bops(काष्ठा sm_metadata *smm)
अणु
	पूर्णांक r = 0;

	जबतक (!brb_empty(&smm->uncommitted)) अणु
		काष्ठा block_op bop;

		r = brb_peek(&smm->uncommitted, &bop);
		अगर (r) अणु
			DMERR("bug in bop ring buffer");
			अवरोध;
		पूर्ण

		r = commit_bop(smm, &bop);
		अगर (r)
			अवरोध;

		brb_pop(&smm->uncommitted);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक out(काष्ठा sm_metadata *smm)
अणु
	पूर्णांक r = 0;

	/*
	 * If we're not recursing then very bad things are happening.
	 */
	अगर (!smm->recursion_count) अणु
		DMERR("lost track of recursion depth");
		वापस -ENOMEM;
	पूर्ण

	अगर (smm->recursion_count == 1)
		r = apply_bops(smm);

	smm->recursion_count--;

	वापस r;
पूर्ण

/*
 * When using the out() function above, we often want to combine an error
 * code क्रम the operation run in the recursive context with that from
 * out().
 */
अटल पूर्णांक combine_errors(पूर्णांक r1, पूर्णांक r2)
अणु
	वापस r1 ? r1 : r2;
पूर्ण

अटल पूर्णांक recursing(काष्ठा sm_metadata *smm)
अणु
	वापस smm->recursion_count;
पूर्ण

अटल व्योम sm_metadata_destroy(काष्ठा dm_space_map *sm)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	kमुक्त(smm);
पूर्ण

अटल पूर्णांक sm_metadata_get_nr_blocks(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	*count = smm->ll.nr_blocks;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_get_nr_मुक्त(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	*count = smm->old_ll.nr_blocks - smm->old_ll.nr_allocated -
		 smm->allocated_this_transaction;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_get_count(काष्ठा dm_space_map *sm, dm_block_t b,
				 uपूर्णांक32_t *result)
अणु
	पूर्णांक r;
	अचिन्हित i;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);
	अचिन्हित adjusपंचांगent = 0;

	/*
	 * We may have some uncommitted adjusपंचांगents to add.  This list
	 * should always be really लघु.
	 */
	क्रम (i = smm->uncommitted.begin;
	     i != smm->uncommitted.end;
	     i = brb_next(&smm->uncommitted, i)) अणु
		काष्ठा block_op *op = smm->uncommitted.bops + i;

		अगर (op->block != b)
			जारी;

		चयन (op->type) अणु
		हाल BOP_INC:
			adjusपंचांगent++;
			अवरोध;

		हाल BOP_DEC:
			adjusपंचांगent--;
			अवरोध;
		पूर्ण
	पूर्ण

	r = sm_ll_lookup(&smm->ll, b, result);
	अगर (r)
		वापस r;

	*result += adjusपंचांगent;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_count_is_more_than_one(काष्ठा dm_space_map *sm,
					      dm_block_t b, पूर्णांक *result)
अणु
	पूर्णांक r, adjusपंचांगent = 0;
	अचिन्हित i;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);
	uपूर्णांक32_t rc;

	/*
	 * We may have some uncommitted adjusपंचांगents to add.  This list
	 * should always be really लघु.
	 */
	क्रम (i = smm->uncommitted.begin;
	     i != smm->uncommitted.end;
	     i = brb_next(&smm->uncommitted, i)) अणु

		काष्ठा block_op *op = smm->uncommitted.bops + i;

		अगर (op->block != b)
			जारी;

		चयन (op->type) अणु
		हाल BOP_INC:
			adjusपंचांगent++;
			अवरोध;

		हाल BOP_DEC:
			adjusपंचांगent--;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (adjusपंचांगent > 1) अणु
		*result = 1;
		वापस 0;
	पूर्ण

	r = sm_ll_lookup_biपंचांगap(&smm->ll, b, &rc);
	अगर (r)
		वापस r;

	अगर (rc == 3)
		/*
		 * We err on the side of caution, and always वापस true.
		 */
		*result = 1;
	अन्यथा
		*result = rc + adjusपंचांगent > 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_set_count(काष्ठा dm_space_map *sm, dm_block_t b,
				 uपूर्णांक32_t count)
अणु
	पूर्णांक r, r2;
	क्रमागत allocation_event ev;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	अगर (smm->recursion_count) अणु
		DMERR("cannot recurse set_count()");
		वापस -EINVAL;
	पूर्ण

	in(smm);
	r = sm_ll_insert(&smm->ll, b, count, &ev);
	r2 = out(smm);

	वापस combine_errors(r, r2);
पूर्ण

अटल पूर्णांक sm_metadata_inc_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	पूर्णांक r, r2 = 0;
	क्रमागत allocation_event ev;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	अगर (recursing(smm))
		r = add_bop(smm, BOP_INC, b);
	अन्यथा अणु
		in(smm);
		r = sm_ll_inc(&smm->ll, b, &ev);
		r2 = out(smm);
	पूर्ण

	वापस combine_errors(r, r2);
पूर्ण

अटल पूर्णांक sm_metadata_dec_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	पूर्णांक r, r2 = 0;
	क्रमागत allocation_event ev;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	अगर (recursing(smm))
		r = add_bop(smm, BOP_DEC, b);
	अन्यथा अणु
		in(smm);
		r = sm_ll_dec(&smm->ll, b, &ev);
		r2 = out(smm);
	पूर्ण

	वापस combine_errors(r, r2);
पूर्ण

अटल पूर्णांक sm_metadata_new_block_(काष्ठा dm_space_map *sm, dm_block_t *b)
अणु
	पूर्णांक r, r2 = 0;
	क्रमागत allocation_event ev;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	/*
	 * Any block we allocate has to be मुक्त in both the old and current ll.
	 */
	r = sm_ll_find_common_मुक्त_block(&smm->old_ll, &smm->ll, smm->begin, smm->ll.nr_blocks, b);
	अगर (r)
		वापस r;

	smm->begin = *b + 1;

	अगर (recursing(smm))
		r = add_bop(smm, BOP_INC, *b);
	अन्यथा अणु
		in(smm);
		r = sm_ll_inc(&smm->ll, *b, &ev);
		r2 = out(smm);
	पूर्ण

	अगर (!r)
		smm->allocated_this_transaction++;

	वापस combine_errors(r, r2);
पूर्ण

अटल पूर्णांक sm_metadata_new_block(काष्ठा dm_space_map *sm, dm_block_t *b)
अणु
	dm_block_t count;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	पूर्णांक r = sm_metadata_new_block_(sm, b);
	अगर (r) अणु
		DMERR_LIMIT("unable to allocate new metadata block");
		वापस r;
	पूर्ण

	r = sm_metadata_get_nr_मुक्त(sm, &count);
	अगर (r) अणु
		DMERR_LIMIT("couldn't get free block count");
		वापस r;
	पूर्ण

	check_threshold(&smm->threshold, count);

	वापस r;
पूर्ण

अटल पूर्णांक sm_metadata_commit(काष्ठा dm_space_map *sm)
अणु
	पूर्णांक r;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	r = sm_ll_commit(&smm->ll);
	अगर (r)
		वापस r;

	स_नकल(&smm->old_ll, &smm->ll, माप(smm->old_ll));
	smm->begin = 0;
	smm->allocated_this_transaction = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_रेजिस्टर_threshold_callback(काष्ठा dm_space_map *sm,
						   dm_block_t threshold,
						   dm_sm_threshold_fn fn,
						   व्योम *context)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	set_threshold(&smm->threshold, threshold, fn, context);

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_root_size(काष्ठा dm_space_map *sm, माप_प्रकार *result)
अणु
	*result = माप(काष्ठा disk_sm_root);

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_copy_root(काष्ठा dm_space_map *sm, व्योम *where_le, माप_प्रकार max)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);
	काष्ठा disk_sm_root root_le;

	root_le.nr_blocks = cpu_to_le64(smm->ll.nr_blocks);
	root_le.nr_allocated = cpu_to_le64(smm->ll.nr_allocated);
	root_le.biपंचांगap_root = cpu_to_le64(smm->ll.biपंचांगap_root);
	root_le.ref_count_root = cpu_to_le64(smm->ll.ref_count_root);

	अगर (max < माप(root_le))
		वापस -ENOSPC;

	स_नकल(where_le, &root_le, माप(root_le));

	वापस 0;
पूर्ण

अटल पूर्णांक sm_metadata_extend(काष्ठा dm_space_map *sm, dm_block_t extra_blocks);

अटल स्थिर काष्ठा dm_space_map ops = अणु
	.destroy = sm_metadata_destroy,
	.extend = sm_metadata_extend,
	.get_nr_blocks = sm_metadata_get_nr_blocks,
	.get_nr_मुक्त = sm_metadata_get_nr_मुक्त,
	.get_count = sm_metadata_get_count,
	.count_is_more_than_one = sm_metadata_count_is_more_than_one,
	.set_count = sm_metadata_set_count,
	.inc_block = sm_metadata_inc_block,
	.dec_block = sm_metadata_dec_block,
	.new_block = sm_metadata_new_block,
	.commit = sm_metadata_commit,
	.root_size = sm_metadata_root_size,
	.copy_root = sm_metadata_copy_root,
	.रेजिस्टर_threshold_callback = sm_metadata_रेजिस्टर_threshold_callback
पूर्ण;

/*----------------------------------------------------------------*/

/*
 * When a new space map is created that manages its own space.  We use
 * this tiny bootstrap allocator.
 */
अटल व्योम sm_bootstrap_destroy(काष्ठा dm_space_map *sm)
अणु
पूर्ण

अटल पूर्णांक sm_bootstrap_extend(काष्ठा dm_space_map *sm, dm_block_t extra_blocks)
अणु
	DMERR("bootstrap doesn't support extend");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sm_bootstrap_get_nr_blocks(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	*count = smm->ll.nr_blocks;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_bootstrap_get_nr_मुक्त(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	*count = smm->ll.nr_blocks - smm->begin;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_bootstrap_get_count(काष्ठा dm_space_map *sm, dm_block_t b,
				  uपूर्णांक32_t *result)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	*result = (b < smm->begin) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_bootstrap_count_is_more_than_one(काष्ठा dm_space_map *sm,
					       dm_block_t b, पूर्णांक *result)
अणु
	*result = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_bootstrap_set_count(काष्ठा dm_space_map *sm, dm_block_t b,
				  uपूर्णांक32_t count)
अणु
	DMERR("bootstrap doesn't support set_count");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sm_bootstrap_new_block(काष्ठा dm_space_map *sm, dm_block_t *b)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	/*
	 * We know the entire device is unused.
	 */
	अगर (smm->begin == smm->ll.nr_blocks)
		वापस -ENOSPC;

	*b = smm->begin++;

	वापस 0;
पूर्ण

अटल पूर्णांक sm_bootstrap_inc_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	वापस add_bop(smm, BOP_INC, b);
पूर्ण

अटल पूर्णांक sm_bootstrap_dec_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	वापस add_bop(smm, BOP_DEC, b);
पूर्ण

अटल पूर्णांक sm_bootstrap_commit(काष्ठा dm_space_map *sm)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sm_bootstrap_root_size(काष्ठा dm_space_map *sm, माप_प्रकार *result)
अणु
	DMERR("bootstrap doesn't support root_size");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sm_bootstrap_copy_root(काष्ठा dm_space_map *sm, व्योम *where,
				  माप_प्रकार max)
अणु
	DMERR("bootstrap doesn't support copy_root");

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा dm_space_map bootstrap_ops = अणु
	.destroy = sm_bootstrap_destroy,
	.extend = sm_bootstrap_extend,
	.get_nr_blocks = sm_bootstrap_get_nr_blocks,
	.get_nr_मुक्त = sm_bootstrap_get_nr_मुक्त,
	.get_count = sm_bootstrap_get_count,
	.count_is_more_than_one = sm_bootstrap_count_is_more_than_one,
	.set_count = sm_bootstrap_set_count,
	.inc_block = sm_bootstrap_inc_block,
	.dec_block = sm_bootstrap_dec_block,
	.new_block = sm_bootstrap_new_block,
	.commit = sm_bootstrap_commit,
	.root_size = sm_bootstrap_root_size,
	.copy_root = sm_bootstrap_copy_root,
	.रेजिस्टर_threshold_callback = शून्य
पूर्ण;

/*----------------------------------------------------------------*/

अटल पूर्णांक sm_metadata_extend(काष्ठा dm_space_map *sm, dm_block_t extra_blocks)
अणु
	पूर्णांक r, i;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);
	dm_block_t old_len = smm->ll.nr_blocks;

	/*
	 * Flick पूर्णांकo a mode where all blocks get allocated in the new area.
	 */
	smm->begin = old_len;
	स_नकल(sm, &bootstrap_ops, माप(*sm));

	/*
	 * Extend.
	 */
	r = sm_ll_extend(&smm->ll, extra_blocks);
	अगर (r)
		जाओ out;

	/*
	 * We repeatedly increment then commit until the commit करोesn't
	 * allocate any new blocks.
	 */
	करो अणु
		क्रम (i = old_len; !r && i < smm->begin; i++)
			r = add_bop(smm, BOP_INC, i);

		अगर (r)
			जाओ out;

		old_len = smm->begin;

		r = apply_bops(smm);
		अगर (r) अणु
			DMERR("%s: apply_bops failed", __func__);
			जाओ out;
		पूर्ण

		r = sm_ll_commit(&smm->ll);
		अगर (r)
			जाओ out;

	पूर्ण जबतक (old_len != smm->begin);

out:
	/*
	 * Switch back to normal behaviour.
	 */
	स_नकल(sm, &ops, माप(*sm));
	वापस r;
पूर्ण

/*----------------------------------------------------------------*/

काष्ठा dm_space_map *dm_sm_metadata_init(व्योम)
अणु
	काष्ठा sm_metadata *smm;

	smm = kदो_स्मृति(माप(*smm), GFP_KERNEL);
	अगर (!smm)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(&smm->sm, &ops, माप(smm->sm));

	वापस &smm->sm;
पूर्ण

पूर्णांक dm_sm_metadata_create(काष्ठा dm_space_map *sm,
			  काष्ठा dm_transaction_manager *पंचांग,
			  dm_block_t nr_blocks,
			  dm_block_t superblock)
अणु
	पूर्णांक r;
	dm_block_t i;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	smm->begin = superblock + 1;
	smm->recursion_count = 0;
	smm->allocated_this_transaction = 0;
	brb_init(&smm->uncommitted);
	threshold_init(&smm->threshold);

	स_नकल(&smm->sm, &bootstrap_ops, माप(smm->sm));

	r = sm_ll_new_metadata(&smm->ll, पंचांग);
	अगर (!r) अणु
		अगर (nr_blocks > DM_SM_METADATA_MAX_BLOCKS)
			nr_blocks = DM_SM_METADATA_MAX_BLOCKS;
		r = sm_ll_extend(&smm->ll, nr_blocks);
	पूर्ण
	स_नकल(&smm->sm, &ops, माप(smm->sm));
	अगर (r)
		वापस r;

	/*
	 * Now we need to update the newly created data काष्ठाures with the
	 * allocated blocks that they were built from.
	 */
	क्रम (i = superblock; !r && i < smm->begin; i++)
		r = add_bop(smm, BOP_INC, i);

	अगर (r)
		वापस r;

	r = apply_bops(smm);
	अगर (r) अणु
		DMERR("%s: apply_bops failed", __func__);
		वापस r;
	पूर्ण

	वापस sm_metadata_commit(sm);
पूर्ण

पूर्णांक dm_sm_metadata_खोलो(काष्ठा dm_space_map *sm,
			काष्ठा dm_transaction_manager *पंचांग,
			व्योम *root_le, माप_प्रकार len)
अणु
	पूर्णांक r;
	काष्ठा sm_metadata *smm = container_of(sm, काष्ठा sm_metadata, sm);

	r = sm_ll_खोलो_metadata(&smm->ll, पंचांग, root_le, len);
	अगर (r)
		वापस r;

	smm->begin = 0;
	smm->recursion_count = 0;
	smm->allocated_this_transaction = 0;
	brb_init(&smm->uncommitted);
	threshold_init(&smm->threshold);

	स_नकल(&smm->old_ll, &smm->ll, माप(smm->old_ll));
	वापस 0;
पूर्ण
