<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-array.h"
#समावेश "dm-space-map.h"
#समावेश "dm-transaction-manager.h"

#समावेश <linux/export.h>
#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "array"

/*----------------------------------------------------------------*/

/*
 * The array is implemented as a fully populated btree, which poपूर्णांकs to
 * blocks that contain the packed values.  This is more space efficient
 * than just using a btree since we करोn't store 1 key per value.
 */
काष्ठा array_block अणु
	__le32 csum;
	__le32 max_entries;
	__le32 nr_entries;
	__le32 value_size;
	__le64 blocknr; /* Block this node is supposed to live in. */
पूर्ण __packed;

/*----------------------------------------------------------------*/

/*
 * Validator methods.  As usual we calculate a checksum, and also ग_लिखो the
 * block location पूर्णांकo the header (paranoia about ssds remapping areas by
 * mistake).
 */
#घोषणा CSUM_XOR 595846735

अटल व्योम array_block_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
					  काष्ठा dm_block *b,
					  माप_प्रकार size_of_block)
अणु
	काष्ठा array_block *bh_le = dm_block_data(b);

	bh_le->blocknr = cpu_to_le64(dm_block_location(b));
	bh_le->csum = cpu_to_le32(dm_bm_checksum(&bh_le->max_entries,
						 size_of_block - माप(__le32),
						 CSUM_XOR));
पूर्ण

अटल पूर्णांक array_block_check(काष्ठा dm_block_validator *v,
			     काष्ठा dm_block *b,
			     माप_प्रकार size_of_block)
अणु
	काष्ठा array_block *bh_le = dm_block_data(b);
	__le32 csum_disk;

	अगर (dm_block_location(b) != le64_to_cpu(bh_le->blocknr)) अणु
		DMERR_LIMIT("array_block_check failed: blocknr %llu != wanted %llu",
			    (अचिन्हित दीर्घ दीर्घ) le64_to_cpu(bh_le->blocknr),
			    (अचिन्हित दीर्घ दीर्घ) dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	csum_disk = cpu_to_le32(dm_bm_checksum(&bh_le->max_entries,
					       size_of_block - माप(__le32),
					       CSUM_XOR));
	अगर (csum_disk != bh_le->csum) अणु
		DMERR_LIMIT("array_block_check failed: csum %u != wanted %u",
			    (अचिन्हित) le32_to_cpu(csum_disk),
			    (अचिन्हित) le32_to_cpu(bh_le->csum));
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dm_block_validator array_validator = अणु
	.name = "array",
	.prepare_क्रम_ग_लिखो = array_block_prepare_क्रम_ग_लिखो,
	.check = array_block_check
पूर्ण;

/*----------------------------------------------------------------*/

/*
 * Functions क्रम manipulating the array blocks.
 */

/*
 * Returns a poपूर्णांकer to a value within an array block.
 *
 * index - The index पूर्णांकo _this_ specअगरic block.
 */
अटल व्योम *element_at(काष्ठा dm_array_info *info, काष्ठा array_block *ab,
			अचिन्हित index)
अणु
	अचिन्हित अक्षर *entry = (अचिन्हित अक्षर *) (ab + 1);

	entry += index * info->value_type.size;

	वापस entry;
पूर्ण

/*
 * Utility function that calls one of the value_type methods on every value
 * in an array block.
 */
अटल व्योम on_entries(काष्ठा dm_array_info *info, काष्ठा array_block *ab,
		       व्योम (*fn)(व्योम *, स्थिर व्योम *))
अणु
	अचिन्हित i, nr_entries = le32_to_cpu(ab->nr_entries);

	क्रम (i = 0; i < nr_entries; i++)
		fn(info->value_type.context, element_at(info, ab, i));
पूर्ण

/*
 * Increment every value in an array block.
 */
अटल व्योम inc_ablock_entries(काष्ठा dm_array_info *info, काष्ठा array_block *ab)
अणु
	काष्ठा dm_btree_value_type *vt = &info->value_type;

	अगर (vt->inc)
		on_entries(info, ab, vt->inc);
पूर्ण

/*
 * Decrement every value in an array block.
 */
अटल व्योम dec_ablock_entries(काष्ठा dm_array_info *info, काष्ठा array_block *ab)
अणु
	काष्ठा dm_btree_value_type *vt = &info->value_type;

	अगर (vt->dec)
		on_entries(info, ab, vt->dec);
पूर्ण

/*
 * Each array block can hold this many values.
 */
अटल uपूर्णांक32_t calc_max_entries(माप_प्रकार value_size, माप_प्रकार size_of_block)
अणु
	वापस (size_of_block - माप(काष्ठा array_block)) / value_size;
पूर्ण

/*
 * Allocate a new array block.  The caller will need to unlock block.
 */
अटल पूर्णांक alloc_ablock(काष्ठा dm_array_info *info, माप_प्रकार size_of_block,
			uपूर्णांक32_t max_entries,
			काष्ठा dm_block **block, काष्ठा array_block **ab)
अणु
	पूर्णांक r;

	r = dm_पंचांग_new_block(info->btree_info.पंचांग, &array_validator, block);
	अगर (r)
		वापस r;

	(*ab) = dm_block_data(*block);
	(*ab)->max_entries = cpu_to_le32(max_entries);
	(*ab)->nr_entries = cpu_to_le32(0);
	(*ab)->value_size = cpu_to_le32(info->value_type.size);

	वापस 0;
पूर्ण

/*
 * Pad an array block out with a particular value.  Every instance will
 * cause an increment of the value_type.  new_nr must always be more than
 * the current number of entries.
 */
अटल व्योम fill_ablock(काष्ठा dm_array_info *info, काष्ठा array_block *ab,
			स्थिर व्योम *value, अचिन्हित new_nr)
अणु
	अचिन्हित i;
	uपूर्णांक32_t nr_entries;
	काष्ठा dm_btree_value_type *vt = &info->value_type;

	BUG_ON(new_nr > le32_to_cpu(ab->max_entries));
	BUG_ON(new_nr < le32_to_cpu(ab->nr_entries));

	nr_entries = le32_to_cpu(ab->nr_entries);
	क्रम (i = nr_entries; i < new_nr; i++) अणु
		अगर (vt->inc)
			vt->inc(vt->context, value);
		स_नकल(element_at(info, ab, i), value, vt->size);
	पूर्ण
	ab->nr_entries = cpu_to_le32(new_nr);
पूर्ण

/*
 * Remove some entries from the back of an array block.  Every value
 * हटाओd will be decremented.  new_nr must be <= the current number of
 * entries.
 */
अटल व्योम trim_ablock(काष्ठा dm_array_info *info, काष्ठा array_block *ab,
			अचिन्हित new_nr)
अणु
	अचिन्हित i;
	uपूर्णांक32_t nr_entries;
	काष्ठा dm_btree_value_type *vt = &info->value_type;

	BUG_ON(new_nr > le32_to_cpu(ab->max_entries));
	BUG_ON(new_nr > le32_to_cpu(ab->nr_entries));

	nr_entries = le32_to_cpu(ab->nr_entries);
	क्रम (i = nr_entries; i > new_nr; i--)
		अगर (vt->dec)
			vt->dec(vt->context, element_at(info, ab, i - 1));
	ab->nr_entries = cpu_to_le32(new_nr);
पूर्ण

/*
 * Read locks a block, and coerces it to an array block.  The caller must
 * unlock 'block' when finished.
 */
अटल पूर्णांक get_ablock(काष्ठा dm_array_info *info, dm_block_t b,
		      काष्ठा dm_block **block, काष्ठा array_block **ab)
अणु
	पूर्णांक r;

	r = dm_पंचांग_पढ़ो_lock(info->btree_info.पंचांग, b, &array_validator, block);
	अगर (r)
		वापस r;

	*ab = dm_block_data(*block);
	वापस 0;
पूर्ण

/*
 * Unlocks an array block.
 */
अटल व्योम unlock_ablock(काष्ठा dm_array_info *info, काष्ठा dm_block *block)
अणु
	dm_पंचांग_unlock(info->btree_info.पंचांग, block);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * Btree manipulation.
 */

/*
 * Looks up an array block in the btree, and then पढ़ो locks it.
 *
 * index is the index of the index of the array_block, (ie. the array index
 * / max_entries).
 */
अटल पूर्णांक lookup_ablock(काष्ठा dm_array_info *info, dm_block_t root,
			 अचिन्हित index, काष्ठा dm_block **block,
			 काष्ठा array_block **ab)
अणु
	पूर्णांक r;
	uपूर्णांक64_t key = index;
	__le64 block_le;

	r = dm_btree_lookup(&info->btree_info, root, &key, &block_le);
	अगर (r)
		वापस r;

	वापस get_ablock(info, le64_to_cpu(block_le), block, ab);
पूर्ण

/*
 * Insert an array block पूर्णांकo the btree.  The block is _not_ unlocked.
 */
अटल पूर्णांक insert_ablock(काष्ठा dm_array_info *info, uपूर्णांक64_t index,
			 काष्ठा dm_block *block, dm_block_t *root)
अणु
	__le64 block_le = cpu_to_le64(dm_block_location(block));

	__dm_bless_क्रम_disk(block_le);
	वापस dm_btree_insert(&info->btree_info, *root, &index, &block_le, root);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक __shaकरोw_ablock(काष्ठा dm_array_info *info, dm_block_t b,
			   काष्ठा dm_block **block, काष्ठा array_block **ab)
अणु
	पूर्णांक inc;
	पूर्णांक r = dm_पंचांग_shaकरोw_block(info->btree_info.पंचांग, b,
				   &array_validator, block, &inc);
	अगर (r)
		वापस r;

	*ab = dm_block_data(*block);
	अगर (inc)
		inc_ablock_entries(info, *ab);

	वापस 0;
पूर्ण

/*
 * The shaकरोw op will often be a noop.  Only insert अगर it really
 * copied data.
 */
अटल पूर्णांक __reinsert_ablock(काष्ठा dm_array_info *info, अचिन्हित index,
			     काष्ठा dm_block *block, dm_block_t b,
			     dm_block_t *root)
अणु
	पूर्णांक r = 0;

	अगर (dm_block_location(block) != b) अणु
		/*
		 * dm_पंचांग_shaकरोw_block will have alपढ़ोy decremented the old
		 * block, but it is still referenced by the btree.  We
		 * increment to stop the insert decrementing it below zero
		 * when overwriting the old value.
		 */
		dm_पंचांग_inc(info->btree_info.पंचांग, b);
		r = insert_ablock(info, index, block, root);
	पूर्ण

	वापस r;
पूर्ण

/*
 * Looks up an array block in the btree.  Then shaकरोws it, and updates the
 * btree to poपूर्णांक to this new shaकरोw.  'root' is an input/output parameter
 * क्रम both the current root block, and the new one.
 */
अटल पूर्णांक shaकरोw_ablock(काष्ठा dm_array_info *info, dm_block_t *root,
			 अचिन्हित index, काष्ठा dm_block **block,
			 काष्ठा array_block **ab)
अणु
	पूर्णांक r;
	uपूर्णांक64_t key = index;
	dm_block_t b;
	__le64 block_le;

	r = dm_btree_lookup(&info->btree_info, *root, &key, &block_le);
	अगर (r)
		वापस r;
	b = le64_to_cpu(block_le);

	r = __shaकरोw_ablock(info, b, block, ab);
	अगर (r)
		वापस r;

	वापस __reinsert_ablock(info, index, *block, b, root);
पूर्ण

/*
 * Allocate an new array block, and fill it with some values.
 */
अटल पूर्णांक insert_new_ablock(काष्ठा dm_array_info *info, माप_प्रकार size_of_block,
			     uपूर्णांक32_t max_entries,
			     अचिन्हित block_index, uपूर्णांक32_t nr,
			     स्थिर व्योम *value, dm_block_t *root)
अणु
	पूर्णांक r;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;

	r = alloc_ablock(info, size_of_block, max_entries, &block, &ab);
	अगर (r)
		वापस r;

	fill_ablock(info, ab, value, nr);
	r = insert_ablock(info, block_index, block, root);
	unlock_ablock(info, block);

	वापस r;
पूर्ण

अटल पूर्णांक insert_full_ablocks(काष्ठा dm_array_info *info, माप_प्रकार size_of_block,
			       अचिन्हित begin_block, अचिन्हित end_block,
			       अचिन्हित max_entries, स्थिर व्योम *value,
			       dm_block_t *root)
अणु
	पूर्णांक r = 0;

	क्रम (; !r && begin_block != end_block; begin_block++)
		r = insert_new_ablock(info, size_of_block, max_entries, begin_block, max_entries, value, root);

	वापस r;
पूर्ण

/*
 * There are a bunch of functions involved with resizing an array.  This
 * काष्ठाure holds inक्रमmation that commonly needed by them.  Purely here
 * to reduce parameter count.
 */
काष्ठा resize अणु
	/*
	 * Describes the array.
	 */
	काष्ठा dm_array_info *info;

	/*
	 * The current root of the array.  This माला_लो updated.
	 */
	dm_block_t root;

	/*
	 * Metadata block size.  Used to calculate the nr entries in an
	 * array block.
	 */
	माप_प्रकार size_of_block;

	/*
	 * Maximum nr entries in an array block.
	 */
	अचिन्हित max_entries;

	/*
	 * nr of completely full blocks in the array.
	 *
	 * 'old' refers to before the resize, 'new' after.
	 */
	अचिन्हित old_nr_full_blocks, new_nr_full_blocks;

	/*
	 * Number of entries in the final block.  0 अगरf only full blocks in
	 * the array.
	 */
	अचिन्हित old_nr_entries_in_last_block, new_nr_entries_in_last_block;

	/*
	 * The शेष value used when growing the array.
	 */
	स्थिर व्योम *value;
पूर्ण;

/*
 * Removes a consecutive set of array blocks from the btree.  The values
 * in block are decremented as a side effect of the btree हटाओ.
 *
 * begin_index - the index of the first array block to हटाओ.
 * end_index - the one-past-the-end value.  ie. this block is not हटाओd.
 */
अटल पूर्णांक drop_blocks(काष्ठा resize *resize, अचिन्हित begin_index,
		       अचिन्हित end_index)
अणु
	पूर्णांक r;

	जबतक (begin_index != end_index) अणु
		uपूर्णांक64_t key = begin_index++;
		r = dm_btree_हटाओ(&resize->info->btree_info, resize->root,
				    &key, &resize->root);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Calculates how many blocks are needed क्रम the array.
 */
अटल अचिन्हित total_nr_blocks_needed(अचिन्हित nr_full_blocks,
				       अचिन्हित nr_entries_in_last_block)
अणु
	वापस nr_full_blocks + (nr_entries_in_last_block ? 1 : 0);
पूर्ण

/*
 * Shrink an array.
 */
अटल पूर्णांक shrink(काष्ठा resize *resize)
अणु
	पूर्णांक r;
	अचिन्हित begin, end;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;

	/*
	 * Lose some blocks from the back?
	 */
	अगर (resize->new_nr_full_blocks < resize->old_nr_full_blocks) अणु
		begin = total_nr_blocks_needed(resize->new_nr_full_blocks,
					       resize->new_nr_entries_in_last_block);
		end = total_nr_blocks_needed(resize->old_nr_full_blocks,
					     resize->old_nr_entries_in_last_block);

		r = drop_blocks(resize, begin, end);
		अगर (r)
			वापस r;
	पूर्ण

	/*
	 * Trim the new tail block
	 */
	अगर (resize->new_nr_entries_in_last_block) अणु
		r = shaकरोw_ablock(resize->info, &resize->root,
				  resize->new_nr_full_blocks, &block, &ab);
		अगर (r)
			वापस r;

		trim_ablock(resize->info, ab, resize->new_nr_entries_in_last_block);
		unlock_ablock(resize->info, block);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Grow an array.
 */
अटल पूर्णांक grow_extend_tail_block(काष्ठा resize *resize, uपूर्णांक32_t new_nr_entries)
अणु
	पूर्णांक r;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;

	r = shaकरोw_ablock(resize->info, &resize->root,
			  resize->old_nr_full_blocks, &block, &ab);
	अगर (r)
		वापस r;

	fill_ablock(resize->info, ab, resize->value, new_nr_entries);
	unlock_ablock(resize->info, block);

	वापस r;
पूर्ण

अटल पूर्णांक grow_add_tail_block(काष्ठा resize *resize)
अणु
	वापस insert_new_ablock(resize->info, resize->size_of_block,
				 resize->max_entries,
				 resize->new_nr_full_blocks,
				 resize->new_nr_entries_in_last_block,
				 resize->value, &resize->root);
पूर्ण

अटल पूर्णांक grow_needs_more_blocks(काष्ठा resize *resize)
अणु
	पूर्णांक r;
	अचिन्हित old_nr_blocks = resize->old_nr_full_blocks;

	अगर (resize->old_nr_entries_in_last_block > 0) अणु
		old_nr_blocks++;

		r = grow_extend_tail_block(resize, resize->max_entries);
		अगर (r)
			वापस r;
	पूर्ण

	r = insert_full_ablocks(resize->info, resize->size_of_block,
				old_nr_blocks,
				resize->new_nr_full_blocks,
				resize->max_entries, resize->value,
				&resize->root);
	अगर (r)
		वापस r;

	अगर (resize->new_nr_entries_in_last_block)
		r = grow_add_tail_block(resize);

	वापस r;
पूर्ण

अटल पूर्णांक grow(काष्ठा resize *resize)
अणु
	अगर (resize->new_nr_full_blocks > resize->old_nr_full_blocks)
		वापस grow_needs_more_blocks(resize);

	अन्यथा अगर (resize->old_nr_entries_in_last_block)
		वापस grow_extend_tail_block(resize, resize->new_nr_entries_in_last_block);

	अन्यथा
		वापस grow_add_tail_block(resize);
पूर्ण

/*----------------------------------------------------------------*/

/*
 * These are the value_type functions क्रम the btree elements, which poपूर्णांक
 * to array blocks.
 */
अटल व्योम block_inc(व्योम *context, स्थिर व्योम *value)
अणु
	__le64 block_le;
	काष्ठा dm_array_info *info = context;

	स_नकल(&block_le, value, माप(block_le));
	dm_पंचांग_inc(info->btree_info.पंचांग, le64_to_cpu(block_le));
पूर्ण

अटल व्योम block_dec(व्योम *context, स्थिर व्योम *value)
अणु
	पूर्णांक r;
	uपूर्णांक64_t b;
	__le64 block_le;
	uपूर्णांक32_t ref_count;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;
	काष्ठा dm_array_info *info = context;

	स_नकल(&block_le, value, माप(block_le));
	b = le64_to_cpu(block_le);

	r = dm_पंचांग_ref(info->btree_info.पंचांग, b, &ref_count);
	अगर (r) अणु
		DMERR_LIMIT("couldn't get reference count for block %llu",
			    (अचिन्हित दीर्घ दीर्घ) b);
		वापस;
	पूर्ण

	अगर (ref_count == 1) अणु
		/*
		 * We're about to drop the last reference to this ablock.
		 * So we need to decrement the ref count of the contents.
		 */
		r = get_ablock(info, b, &block, &ab);
		अगर (r) अणु
			DMERR_LIMIT("couldn't get array block %llu",
				    (अचिन्हित दीर्घ दीर्घ) b);
			वापस;
		पूर्ण

		dec_ablock_entries(info, ab);
		unlock_ablock(info, block);
	पूर्ण

	dm_पंचांग_dec(info->btree_info.पंचांग, b);
पूर्ण

अटल पूर्णांक block_equal(व्योम *context, स्थिर व्योम *value1, स्थिर व्योम *value2)
अणु
	वापस !स_भेद(value1, value2, माप(__le64));
पूर्ण

/*----------------------------------------------------------------*/

व्योम dm_array_info_init(काष्ठा dm_array_info *info,
			काष्ठा dm_transaction_manager *पंचांग,
			काष्ठा dm_btree_value_type *vt)
अणु
	काष्ठा dm_btree_value_type *bvt = &info->btree_info.value_type;

	स_नकल(&info->value_type, vt, माप(info->value_type));
	info->btree_info.पंचांग = पंचांग;
	info->btree_info.levels = 1;

	bvt->context = info;
	bvt->size = माप(__le64);
	bvt->inc = block_inc;
	bvt->dec = block_dec;
	bvt->equal = block_equal;
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_info_init);

पूर्णांक dm_array_empty(काष्ठा dm_array_info *info, dm_block_t *root)
अणु
	वापस dm_btree_empty(&info->btree_info, root);
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_empty);

अटल पूर्णांक array_resize(काष्ठा dm_array_info *info, dm_block_t root,
			uपूर्णांक32_t old_size, uपूर्णांक32_t new_size,
			स्थिर व्योम *value, dm_block_t *new_root)
अणु
	पूर्णांक r;
	काष्ठा resize resize;

	अगर (old_size == new_size) अणु
		*new_root = root;
		वापस 0;
	पूर्ण

	resize.info = info;
	resize.root = root;
	resize.size_of_block = dm_bm_block_size(dm_पंचांग_get_bm(info->btree_info.पंचांग));
	resize.max_entries = calc_max_entries(info->value_type.size,
					      resize.size_of_block);

	resize.old_nr_full_blocks = old_size / resize.max_entries;
	resize.old_nr_entries_in_last_block = old_size % resize.max_entries;
	resize.new_nr_full_blocks = new_size / resize.max_entries;
	resize.new_nr_entries_in_last_block = new_size % resize.max_entries;
	resize.value = value;

	r = ((new_size > old_size) ? grow : shrink)(&resize);
	अगर (r)
		वापस r;

	*new_root = resize.root;
	वापस 0;
पूर्ण

पूर्णांक dm_array_resize(काष्ठा dm_array_info *info, dm_block_t root,
		    uपूर्णांक32_t old_size, uपूर्णांक32_t new_size,
		    स्थिर व्योम *value, dm_block_t *new_root)
		    __dm_written_to_disk(value)
अणु
	पूर्णांक r = array_resize(info, root, old_size, new_size, value, new_root);
	__dm_unbless_क्रम_disk(value);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_resize);

अटल पूर्णांक populate_ablock_with_values(काष्ठा dm_array_info *info, काष्ठा array_block *ab,
				       value_fn fn, व्योम *context, अचिन्हित base, अचिन्हित new_nr)
अणु
	पूर्णांक r;
	अचिन्हित i;
	काष्ठा dm_btree_value_type *vt = &info->value_type;

	BUG_ON(le32_to_cpu(ab->nr_entries));
	BUG_ON(new_nr > le32_to_cpu(ab->max_entries));

	क्रम (i = 0; i < new_nr; i++) अणु
		r = fn(base + i, element_at(info, ab, i), context);
		अगर (r)
			वापस r;

		अगर (vt->inc)
			vt->inc(vt->context, element_at(info, ab, i));
	पूर्ण

	ab->nr_entries = cpu_to_le32(new_nr);
	वापस 0;
पूर्ण

पूर्णांक dm_array_new(काष्ठा dm_array_info *info, dm_block_t *root,
		 uपूर्णांक32_t size, value_fn fn, व्योम *context)
अणु
	पूर्णांक r;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;
	अचिन्हित block_index, end_block, size_of_block, max_entries;

	r = dm_array_empty(info, root);
	अगर (r)
		वापस r;

	size_of_block = dm_bm_block_size(dm_पंचांग_get_bm(info->btree_info.पंचांग));
	max_entries = calc_max_entries(info->value_type.size, size_of_block);
	end_block = dm_भाग_up(size, max_entries);

	क्रम (block_index = 0; block_index != end_block; block_index++) अणु
		r = alloc_ablock(info, size_of_block, max_entries, &block, &ab);
		अगर (r)
			अवरोध;

		r = populate_ablock_with_values(info, ab, fn, context,
						block_index * max_entries,
						min(max_entries, size));
		अगर (r) अणु
			unlock_ablock(info, block);
			अवरोध;
		पूर्ण

		r = insert_ablock(info, block_index, block, root);
		unlock_ablock(info, block);
		अगर (r)
			अवरोध;

		size -= max_entries;
	पूर्ण

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_new);

पूर्णांक dm_array_del(काष्ठा dm_array_info *info, dm_block_t root)
अणु
	वापस dm_btree_del(&info->btree_info, root);
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_del);

पूर्णांक dm_array_get_value(काष्ठा dm_array_info *info, dm_block_t root,
		       uपूर्णांक32_t index, व्योम *value_le)
अणु
	पूर्णांक r;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;
	माप_प्रकार size_of_block;
	अचिन्हित entry, max_entries;

	size_of_block = dm_bm_block_size(dm_पंचांग_get_bm(info->btree_info.पंचांग));
	max_entries = calc_max_entries(info->value_type.size, size_of_block);

	r = lookup_ablock(info, root, index / max_entries, &block, &ab);
	अगर (r)
		वापस r;

	entry = index % max_entries;
	अगर (entry >= le32_to_cpu(ab->nr_entries))
		r = -ENODATA;
	अन्यथा
		स_नकल(value_le, element_at(info, ab, entry),
		       info->value_type.size);

	unlock_ablock(info, block);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_get_value);

अटल पूर्णांक array_set_value(काष्ठा dm_array_info *info, dm_block_t root,
			   uपूर्णांक32_t index, स्थिर व्योम *value, dm_block_t *new_root)
अणु
	पूर्णांक r;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;
	माप_प्रकार size_of_block;
	अचिन्हित max_entries;
	अचिन्हित entry;
	व्योम *old_value;
	काष्ठा dm_btree_value_type *vt = &info->value_type;

	size_of_block = dm_bm_block_size(dm_पंचांग_get_bm(info->btree_info.पंचांग));
	max_entries = calc_max_entries(info->value_type.size, size_of_block);

	r = shaकरोw_ablock(info, &root, index / max_entries, &block, &ab);
	अगर (r)
		वापस r;
	*new_root = root;

	entry = index % max_entries;
	अगर (entry >= le32_to_cpu(ab->nr_entries)) अणु
		r = -ENODATA;
		जाओ out;
	पूर्ण

	old_value = element_at(info, ab, entry);
	अगर (vt->dec &&
	    (!vt->equal || !vt->equal(vt->context, old_value, value))) अणु
		vt->dec(vt->context, old_value);
		अगर (vt->inc)
			vt->inc(vt->context, value);
	पूर्ण

	स_नकल(old_value, value, info->value_type.size);

out:
	unlock_ablock(info, block);
	वापस r;
पूर्ण

पूर्णांक dm_array_set_value(काष्ठा dm_array_info *info, dm_block_t root,
		 uपूर्णांक32_t index, स्थिर व्योम *value, dm_block_t *new_root)
		 __dm_written_to_disk(value)
अणु
	पूर्णांक r;

	r = array_set_value(info, root, index, value, new_root);
	__dm_unbless_क्रम_disk(value);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_set_value);

काष्ठा walk_info अणु
	काष्ठा dm_array_info *info;
	पूर्णांक (*fn)(व्योम *context, uपूर्णांक64_t key, व्योम *leaf);
	व्योम *context;
पूर्ण;

अटल पूर्णांक walk_ablock(व्योम *context, uपूर्णांक64_t *keys, व्योम *leaf)
अणु
	काष्ठा walk_info *wi = context;

	पूर्णांक r;
	अचिन्हित i;
	__le64 block_le;
	अचिन्हित nr_entries, max_entries;
	काष्ठा dm_block *block;
	काष्ठा array_block *ab;

	स_नकल(&block_le, leaf, माप(block_le));
	r = get_ablock(wi->info, le64_to_cpu(block_le), &block, &ab);
	अगर (r)
		वापस r;

	max_entries = le32_to_cpu(ab->max_entries);
	nr_entries = le32_to_cpu(ab->nr_entries);
	क्रम (i = 0; i < nr_entries; i++) अणु
		r = wi->fn(wi->context, keys[0] * max_entries + i,
			   element_at(wi->info, ab, i));

		अगर (r)
			अवरोध;
	पूर्ण

	unlock_ablock(wi->info, block);
	वापस r;
पूर्ण

पूर्णांक dm_array_walk(काष्ठा dm_array_info *info, dm_block_t root,
		  पूर्णांक (*fn)(व्योम *, uपूर्णांक64_t key, व्योम *leaf),
		  व्योम *context)
अणु
	काष्ठा walk_info wi;

	wi.info = info;
	wi.fn = fn;
	wi.context = context;

	वापस dm_btree_walk(&info->btree_info, root, walk_ablock, &wi);
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_walk);

/*----------------------------------------------------------------*/

अटल पूर्णांक load_ablock(काष्ठा dm_array_cursor *c)
अणु
	पूर्णांक r;
	__le64 value_le;
	uपूर्णांक64_t key;

	अगर (c->block)
		unlock_ablock(c->info, c->block);

	c->block = शून्य;
	c->ab = शून्य;
	c->index = 0;

	r = dm_btree_cursor_get_value(&c->cursor, &key, &value_le);
	अगर (r) अणु
		DMERR("dm_btree_cursor_get_value failed");
		dm_btree_cursor_end(&c->cursor);

	पूर्ण अन्यथा अणु
		r = get_ablock(c->info, le64_to_cpu(value_le), &c->block, &c->ab);
		अगर (r) अणु
			DMERR("get_ablock failed");
			dm_btree_cursor_end(&c->cursor);
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक dm_array_cursor_begin(काष्ठा dm_array_info *info, dm_block_t root,
			  काष्ठा dm_array_cursor *c)
अणु
	पूर्णांक r;

	स_रखो(c, 0, माप(*c));
	c->info = info;
	r = dm_btree_cursor_begin(&info->btree_info, root, true, &c->cursor);
	अगर (r) अणु
		DMERR("couldn't create btree cursor");
		वापस r;
	पूर्ण

	वापस load_ablock(c);
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_cursor_begin);

व्योम dm_array_cursor_end(काष्ठा dm_array_cursor *c)
अणु
	अगर (c->block) अणु
		unlock_ablock(c->info, c->block);
		dm_btree_cursor_end(&c->cursor);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_cursor_end);

पूर्णांक dm_array_cursor_next(काष्ठा dm_array_cursor *c)
अणु
	पूर्णांक r;

	अगर (!c->block)
		वापस -ENODATA;

	c->index++;

	अगर (c->index >= le32_to_cpu(c->ab->nr_entries)) अणु
		r = dm_btree_cursor_next(&c->cursor);
		अगर (r)
			वापस r;

		r = load_ablock(c);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_cursor_next);

पूर्णांक dm_array_cursor_skip(काष्ठा dm_array_cursor *c, uपूर्णांक32_t count)
अणु
	पूर्णांक r;

	करो अणु
		uपूर्णांक32_t reमुख्यing = le32_to_cpu(c->ab->nr_entries) - c->index;

		अगर (count < reमुख्यing) अणु
			c->index += count;
			वापस 0;
		पूर्ण

		count -= reमुख्यing;
		r = dm_array_cursor_next(c);

	पूर्ण जबतक (!r);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_cursor_skip);

व्योम dm_array_cursor_get_value(काष्ठा dm_array_cursor *c, व्योम **value_le)
अणु
	*value_le = element_at(c->info, c->ab, c->index);
पूर्ण
EXPORT_SYMBOL_GPL(dm_array_cursor_get_value);

/*----------------------------------------------------------------*/
