<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-space-map-common.h"
#समावेश "dm-transaction-manager.h"

#समावेश <linux/bitops.h>
#समावेश <linux/device-mapper.h>

#घोषणा DM_MSG_PREFIX "space map common"

/*----------------------------------------------------------------*/

/*
 * Index validator.
 */
#घोषणा INDEX_CSUM_XOR 160478

अटल व्योम index_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
				    काष्ठा dm_block *b,
				    माप_प्रकार block_size)
अणु
	काष्ठा disk_metadata_index *mi_le = dm_block_data(b);

	mi_le->blocknr = cpu_to_le64(dm_block_location(b));
	mi_le->csum = cpu_to_le32(dm_bm_checksum(&mi_le->padding,
						 block_size - माप(__le32),
						 INDEX_CSUM_XOR));
पूर्ण

अटल पूर्णांक index_check(काष्ठा dm_block_validator *v,
		       काष्ठा dm_block *b,
		       माप_प्रकार block_size)
अणु
	काष्ठा disk_metadata_index *mi_le = dm_block_data(b);
	__le32 csum_disk;

	अगर (dm_block_location(b) != le64_to_cpu(mi_le->blocknr)) अणु
		DMERR_LIMIT("index_check failed: blocknr %llu != wanted %llu",
			    le64_to_cpu(mi_le->blocknr), dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	csum_disk = cpu_to_le32(dm_bm_checksum(&mi_le->padding,
					       block_size - माप(__le32),
					       INDEX_CSUM_XOR));
	अगर (csum_disk != mi_le->csum) अणु
		DMERR_LIMIT("index_check failed: csum %u != wanted %u",
			    le32_to_cpu(csum_disk), le32_to_cpu(mi_le->csum));
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dm_block_validator index_validator = अणु
	.name = "index",
	.prepare_क्रम_ग_लिखो = index_prepare_क्रम_ग_लिखो,
	.check = index_check
पूर्ण;

/*----------------------------------------------------------------*/

/*
 * Biपंचांगap validator
 */
#घोषणा BITMAP_CSUM_XOR 240779

अटल व्योम dm_biपंचांगap_prepare_क्रम_ग_लिखो(काष्ठा dm_block_validator *v,
					काष्ठा dm_block *b,
					माप_प्रकार block_size)
अणु
	काष्ठा disk_biपंचांगap_header *disk_header = dm_block_data(b);

	disk_header->blocknr = cpu_to_le64(dm_block_location(b));
	disk_header->csum = cpu_to_le32(dm_bm_checksum(&disk_header->not_used,
						       block_size - माप(__le32),
						       BITMAP_CSUM_XOR));
पूर्ण

अटल पूर्णांक dm_biपंचांगap_check(काष्ठा dm_block_validator *v,
			   काष्ठा dm_block *b,
			   माप_प्रकार block_size)
अणु
	काष्ठा disk_biपंचांगap_header *disk_header = dm_block_data(b);
	__le32 csum_disk;

	अगर (dm_block_location(b) != le64_to_cpu(disk_header->blocknr)) अणु
		DMERR_LIMIT("bitmap check failed: blocknr %llu != wanted %llu",
			    le64_to_cpu(disk_header->blocknr), dm_block_location(b));
		वापस -ENOTBLK;
	पूर्ण

	csum_disk = cpu_to_le32(dm_bm_checksum(&disk_header->not_used,
					       block_size - माप(__le32),
					       BITMAP_CSUM_XOR));
	अगर (csum_disk != disk_header->csum) अणु
		DMERR_LIMIT("bitmap check failed: csum %u != wanted %u",
			    le32_to_cpu(csum_disk), le32_to_cpu(disk_header->csum));
		वापस -EILSEQ;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dm_block_validator dm_sm_biपंचांगap_validator = अणु
	.name = "sm_bitmap",
	.prepare_क्रम_ग_लिखो = dm_biपंचांगap_prepare_क्रम_ग_लिखो,
	.check = dm_biपंचांगap_check,
पूर्ण;

/*----------------------------------------------------------------*/

#घोषणा ENTRIES_PER_WORD 32
#घोषणा ENTRIES_SHIFT	5

अटल व्योम *dm_biपंचांगap_data(काष्ठा dm_block *b)
अणु
	वापस dm_block_data(b) + माप(काष्ठा disk_biपंचांगap_header);
पूर्ण

#घोषणा WORD_MASK_HIGH 0xAAAAAAAAAAAAAAAAULL

अटल अचिन्हित dm_biपंचांगap_word_used(व्योम *addr, अचिन्हित b)
अणु
	__le64 *words_le = addr;
	__le64 *w_le = words_le + (b >> ENTRIES_SHIFT);

	uपूर्णांक64_t bits = le64_to_cpu(*w_le);
	uपूर्णांक64_t mask = (bits + WORD_MASK_HIGH + 1) & WORD_MASK_HIGH;

	वापस !(~bits & mask);
पूर्ण

अटल अचिन्हित sm_lookup_biपंचांगap(व्योम *addr, अचिन्हित b)
अणु
	__le64 *words_le = addr;
	__le64 *w_le = words_le + (b >> ENTRIES_SHIFT);
	अचिन्हित hi, lo;

	b = (b & (ENTRIES_PER_WORD - 1)) << 1;
	hi = !!test_bit_le(b, (व्योम *) w_le);
	lo = !!test_bit_le(b + 1, (व्योम *) w_le);
	वापस (hi << 1) | lo;
पूर्ण

अटल व्योम sm_set_biपंचांगap(व्योम *addr, अचिन्हित b, अचिन्हित val)
अणु
	__le64 *words_le = addr;
	__le64 *w_le = words_le + (b >> ENTRIES_SHIFT);

	b = (b & (ENTRIES_PER_WORD - 1)) << 1;

	अगर (val & 2)
		__set_bit_le(b, (व्योम *) w_le);
	अन्यथा
		__clear_bit_le(b, (व्योम *) w_le);

	अगर (val & 1)
		__set_bit_le(b + 1, (व्योम *) w_le);
	अन्यथा
		__clear_bit_le(b + 1, (व्योम *) w_le);
पूर्ण

अटल पूर्णांक sm_find_मुक्त(व्योम *addr, अचिन्हित begin, अचिन्हित end,
			अचिन्हित *result)
अणु
	जबतक (begin < end) अणु
		अगर (!(begin & (ENTRIES_PER_WORD - 1)) &&
		    dm_biपंचांगap_word_used(addr, begin)) अणु
			begin += ENTRIES_PER_WORD;
			जारी;
		पूर्ण

		अगर (!sm_lookup_biपंचांगap(addr, begin)) अणु
			*result = begin;
			वापस 0;
		पूर्ण

		begin++;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक sm_ll_init(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग)
अणु
	स_रखो(ll, 0, माप(काष्ठा ll_disk));

	ll->पंचांग = पंचांग;

	ll->biपंचांगap_info.पंचांग = पंचांग;
	ll->biपंचांगap_info.levels = 1;

	/*
	 * Because the new biपंचांगap blocks are created via a shaकरोw
	 * operation, the old entry has alपढ़ोy had its reference count
	 * decremented and we करोn't need the btree to करो any bookkeeping.
	 */
	ll->biपंचांगap_info.value_type.size = माप(काष्ठा disk_index_entry);
	ll->biपंचांगap_info.value_type.inc = शून्य;
	ll->biपंचांगap_info.value_type.dec = शून्य;
	ll->biपंचांगap_info.value_type.equal = शून्य;

	ll->ref_count_info.पंचांग = पंचांग;
	ll->ref_count_info.levels = 1;
	ll->ref_count_info.value_type.size = माप(uपूर्णांक32_t);
	ll->ref_count_info.value_type.inc = शून्य;
	ll->ref_count_info.value_type.dec = शून्य;
	ll->ref_count_info.value_type.equal = शून्य;

	ll->block_size = dm_bm_block_size(dm_पंचांग_get_bm(पंचांग));

	अगर (ll->block_size > (1 << 30)) अणु
		DMERR("block size too big to hold bitmaps");
		वापस -EINVAL;
	पूर्ण

	ll->entries_per_block = (ll->block_size - माप(काष्ठा disk_biपंचांगap_header)) *
		ENTRIES_PER_BYTE;
	ll->nr_blocks = 0;
	ll->biपंचांगap_root = 0;
	ll->ref_count_root = 0;
	ll->biपंचांगap_index_changed = false;

	वापस 0;
पूर्ण

पूर्णांक sm_ll_extend(काष्ठा ll_disk *ll, dm_block_t extra_blocks)
अणु
	पूर्णांक r;
	dm_block_t i, nr_blocks, nr_indexes;
	अचिन्हित old_blocks, blocks;

	nr_blocks = ll->nr_blocks + extra_blocks;
	old_blocks = dm_sector_भाग_up(ll->nr_blocks, ll->entries_per_block);
	blocks = dm_sector_भाग_up(nr_blocks, ll->entries_per_block);

	nr_indexes = dm_sector_भाग_up(nr_blocks, ll->entries_per_block);
	अगर (nr_indexes > ll->max_entries(ll)) अणु
		DMERR("space map too large");
		वापस -EINVAL;
	पूर्ण

	/*
	 * We need to set this beक्रमe the dm_पंचांग_new_block() call below.
	 */
	ll->nr_blocks = nr_blocks;
	क्रम (i = old_blocks; i < blocks; i++) अणु
		काष्ठा dm_block *b;
		काष्ठा disk_index_entry idx;

		r = dm_पंचांग_new_block(ll->पंचांग, &dm_sm_biपंचांगap_validator, &b);
		अगर (r < 0)
			वापस r;

		idx.blocknr = cpu_to_le64(dm_block_location(b));

		dm_पंचांग_unlock(ll->पंचांग, b);

		idx.nr_मुक्त = cpu_to_le32(ll->entries_per_block);
		idx.none_मुक्त_beक्रमe = 0;

		r = ll->save_ie(ll, i, &idx);
		अगर (r < 0)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sm_ll_lookup_biपंचांगap(काष्ठा ll_disk *ll, dm_block_t b, uपूर्णांक32_t *result)
अणु
	पूर्णांक r;
	dm_block_t index = b;
	काष्ठा disk_index_entry ie_disk;
	काष्ठा dm_block *blk;

	b = करो_भाग(index, ll->entries_per_block);
	r = ll->load_ie(ll, index, &ie_disk);
	अगर (r < 0)
		वापस r;

	r = dm_पंचांग_पढ़ो_lock(ll->पंचांग, le64_to_cpu(ie_disk.blocknr),
			    &dm_sm_biपंचांगap_validator, &blk);
	अगर (r < 0)
		वापस r;

	*result = sm_lookup_biपंचांगap(dm_biपंचांगap_data(blk), b);

	dm_पंचांग_unlock(ll->पंचांग, blk);

	वापस 0;
पूर्ण

अटल पूर्णांक sm_ll_lookup_big_ref_count(काष्ठा ll_disk *ll, dm_block_t b,
				      uपूर्णांक32_t *result)
अणु
	__le32 le_rc;
	पूर्णांक r;

	r = dm_btree_lookup(&ll->ref_count_info, ll->ref_count_root, &b, &le_rc);
	अगर (r < 0)
		वापस r;

	*result = le32_to_cpu(le_rc);

	वापस r;
पूर्ण

पूर्णांक sm_ll_lookup(काष्ठा ll_disk *ll, dm_block_t b, uपूर्णांक32_t *result)
अणु
	पूर्णांक r = sm_ll_lookup_biपंचांगap(ll, b, result);

	अगर (r)
		वापस r;

	अगर (*result != 3)
		वापस r;

	वापस sm_ll_lookup_big_ref_count(ll, b, result);
पूर्ण

पूर्णांक sm_ll_find_मुक्त_block(काष्ठा ll_disk *ll, dm_block_t begin,
			  dm_block_t end, dm_block_t *result)
अणु
	पूर्णांक r;
	काष्ठा disk_index_entry ie_disk;
	dm_block_t i, index_begin = begin;
	dm_block_t index_end = dm_sector_भाग_up(end, ll->entries_per_block);

	/*
	 * FIXME: Use shअगरts
	 */
	begin = करो_भाग(index_begin, ll->entries_per_block);
	end = करो_भाग(end, ll->entries_per_block);
	अगर (end == 0)
		end = ll->entries_per_block;

	क्रम (i = index_begin; i < index_end; i++, begin = 0) अणु
		काष्ठा dm_block *blk;
		अचिन्हित position;
		uपूर्णांक32_t bit_end;

		r = ll->load_ie(ll, i, &ie_disk);
		अगर (r < 0)
			वापस r;

		अगर (le32_to_cpu(ie_disk.nr_मुक्त) == 0)
			जारी;

		r = dm_पंचांग_पढ़ो_lock(ll->पंचांग, le64_to_cpu(ie_disk.blocknr),
				    &dm_sm_biपंचांगap_validator, &blk);
		अगर (r < 0)
			वापस r;

		bit_end = (i == index_end - 1) ?  end : ll->entries_per_block;

		r = sm_find_मुक्त(dm_biपंचांगap_data(blk),
				 max_t(अचिन्हित, begin, le32_to_cpu(ie_disk.none_मुक्त_beक्रमe)),
				 bit_end, &position);
		अगर (r == -ENOSPC) अणु
			/*
			 * This might happen because we started searching
			 * part way through the biपंचांगap.
			 */
			dm_पंचांग_unlock(ll->पंचांग, blk);
			जारी;
		पूर्ण

		dm_पंचांग_unlock(ll->पंचांग, blk);

		*result = i * ll->entries_per_block + (dm_block_t) position;
		वापस 0;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

पूर्णांक sm_ll_find_common_मुक्त_block(काष्ठा ll_disk *old_ll, काष्ठा ll_disk *new_ll,
	                         dm_block_t begin, dm_block_t end, dm_block_t *b)
अणु
	पूर्णांक r;
	uपूर्णांक32_t count;

	करो अणु
		r = sm_ll_find_मुक्त_block(new_ll, begin, new_ll->nr_blocks, b);
		अगर (r)
			अवरोध;

		/* द्विगुन check this block wasn't used in the old transaction */
		अगर (*b >= old_ll->nr_blocks)
			count = 0;
		अन्यथा अणु
			r = sm_ll_lookup(old_ll, *b, &count);
			अगर (r)
				अवरोध;

			अगर (count)
				begin = *b + 1;
		पूर्ण
	पूर्ण जबतक (count);

	वापस r;
पूर्ण

अटल पूर्णांक sm_ll_mutate(काष्ठा ll_disk *ll, dm_block_t b,
			पूर्णांक (*mutator)(व्योम *context, uपूर्णांक32_t old, uपूर्णांक32_t *new),
			व्योम *context, क्रमागत allocation_event *ev)
अणु
	पूर्णांक r;
	uपूर्णांक32_t bit, old, ref_count;
	काष्ठा dm_block *nb;
	dm_block_t index = b;
	काष्ठा disk_index_entry ie_disk;
	व्योम *bm_le;
	पूर्णांक inc;

	bit = करो_भाग(index, ll->entries_per_block);
	r = ll->load_ie(ll, index, &ie_disk);
	अगर (r < 0)
		वापस r;

	r = dm_पंचांग_shaकरोw_block(ll->पंचांग, le64_to_cpu(ie_disk.blocknr),
			       &dm_sm_biपंचांगap_validator, &nb, &inc);
	अगर (r < 0) अणु
		DMERR("dm_tm_shadow_block() failed");
		वापस r;
	पूर्ण
	ie_disk.blocknr = cpu_to_le64(dm_block_location(nb));

	bm_le = dm_biपंचांगap_data(nb);
	old = sm_lookup_biपंचांगap(bm_le, bit);

	अगर (old > 2) अणु
		r = sm_ll_lookup_big_ref_count(ll, b, &old);
		अगर (r < 0) अणु
			dm_पंचांग_unlock(ll->पंचांग, nb);
			वापस r;
		पूर्ण
	पूर्ण

	r = mutator(context, old, &ref_count);
	अगर (r) अणु
		dm_पंचांग_unlock(ll->पंचांग, nb);
		वापस r;
	पूर्ण

	अगर (ref_count <= 2) अणु
		sm_set_biपंचांगap(bm_le, bit, ref_count);

		dm_पंचांग_unlock(ll->पंचांग, nb);

		अगर (old > 2) अणु
			r = dm_btree_हटाओ(&ll->ref_count_info,
					    ll->ref_count_root,
					    &b, &ll->ref_count_root);
			अगर (r)
				वापस r;
		पूर्ण

	पूर्ण अन्यथा अणु
		__le32 le_rc = cpu_to_le32(ref_count);

		sm_set_biपंचांगap(bm_le, bit, 3);
		dm_पंचांग_unlock(ll->पंचांग, nb);

		__dm_bless_क्रम_disk(&le_rc);
		r = dm_btree_insert(&ll->ref_count_info, ll->ref_count_root,
				    &b, &le_rc, &ll->ref_count_root);
		अगर (r < 0) अणु
			DMERR("ref count insert failed");
			वापस r;
		पूर्ण
	पूर्ण

	अगर (ref_count && !old) अणु
		*ev = SM_ALLOC;
		ll->nr_allocated++;
		le32_add_cpu(&ie_disk.nr_मुक्त, -1);
		अगर (le32_to_cpu(ie_disk.none_मुक्त_beक्रमe) == bit)
			ie_disk.none_मुक्त_beक्रमe = cpu_to_le32(bit + 1);

	पूर्ण अन्यथा अगर (old && !ref_count) अणु
		*ev = SM_FREE;
		ll->nr_allocated--;
		le32_add_cpu(&ie_disk.nr_मुक्त, 1);
		ie_disk.none_मुक्त_beक्रमe = cpu_to_le32(min(le32_to_cpu(ie_disk.none_मुक्त_beक्रमe), bit));
	पूर्ण अन्यथा
		*ev = SM_NONE;

	वापस ll->save_ie(ll, index, &ie_disk);
पूर्ण

अटल पूर्णांक set_ref_count(व्योम *context, uपूर्णांक32_t old, uपूर्णांक32_t *new)
अणु
	*new = *((uपूर्णांक32_t *) context);
	वापस 0;
पूर्ण

पूर्णांक sm_ll_insert(काष्ठा ll_disk *ll, dm_block_t b,
		 uपूर्णांक32_t ref_count, क्रमागत allocation_event *ev)
अणु
	वापस sm_ll_mutate(ll, b, set_ref_count, &ref_count, ev);
पूर्ण

अटल पूर्णांक inc_ref_count(व्योम *context, uपूर्णांक32_t old, uपूर्णांक32_t *new)
अणु
	*new = old + 1;
	वापस 0;
पूर्ण

पूर्णांक sm_ll_inc(काष्ठा ll_disk *ll, dm_block_t b, क्रमागत allocation_event *ev)
अणु
	वापस sm_ll_mutate(ll, b, inc_ref_count, शून्य, ev);
पूर्ण

अटल पूर्णांक dec_ref_count(व्योम *context, uपूर्णांक32_t old, uपूर्णांक32_t *new)
अणु
	अगर (!old) अणु
		DMERR_LIMIT("unable to decrement a reference count below 0");
		वापस -EINVAL;
	पूर्ण

	*new = old - 1;
	वापस 0;
पूर्ण

पूर्णांक sm_ll_dec(काष्ठा ll_disk *ll, dm_block_t b, क्रमागत allocation_event *ev)
अणु
	वापस sm_ll_mutate(ll, b, dec_ref_count, शून्य, ev);
पूर्ण

पूर्णांक sm_ll_commit(काष्ठा ll_disk *ll)
अणु
	पूर्णांक r = 0;

	अगर (ll->biपंचांगap_index_changed) अणु
		r = ll->commit(ll);
		अगर (!r)
			ll->biपंचांगap_index_changed = false;
	पूर्ण

	वापस r;
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक metadata_ll_load_ie(काष्ठा ll_disk *ll, dm_block_t index,
			       काष्ठा disk_index_entry *ie)
अणु
	स_नकल(ie, ll->mi_le.index + index, माप(*ie));
	वापस 0;
पूर्ण

अटल पूर्णांक metadata_ll_save_ie(काष्ठा ll_disk *ll, dm_block_t index,
			       काष्ठा disk_index_entry *ie)
अणु
	ll->biपंचांगap_index_changed = true;
	स_नकल(ll->mi_le.index + index, ie, माप(*ie));
	वापस 0;
पूर्ण

अटल पूर्णांक metadata_ll_init_index(काष्ठा ll_disk *ll)
अणु
	पूर्णांक r;
	काष्ठा dm_block *b;

	r = dm_पंचांग_new_block(ll->पंचांग, &index_validator, &b);
	अगर (r < 0)
		वापस r;

	ll->biपंचांगap_root = dm_block_location(b);

	dm_पंचांग_unlock(ll->पंचांग, b);

	वापस 0;
पूर्ण

अटल पूर्णांक metadata_ll_खोलो(काष्ठा ll_disk *ll)
अणु
	पूर्णांक r;
	काष्ठा dm_block *block;

	r = dm_पंचांग_पढ़ो_lock(ll->पंचांग, ll->biपंचांगap_root,
			    &index_validator, &block);
	अगर (r)
		वापस r;

	स_नकल(&ll->mi_le, dm_block_data(block), माप(ll->mi_le));
	dm_पंचांग_unlock(ll->पंचांग, block);

	वापस 0;
पूर्ण

अटल dm_block_t metadata_ll_max_entries(काष्ठा ll_disk *ll)
अणु
	वापस MAX_METADATA_BITMAPS;
पूर्ण

अटल पूर्णांक metadata_ll_commit(काष्ठा ll_disk *ll)
अणु
	पूर्णांक r, inc;
	काष्ठा dm_block *b;

	r = dm_पंचांग_shaकरोw_block(ll->पंचांग, ll->biपंचांगap_root, &index_validator, &b, &inc);
	अगर (r)
		वापस r;

	स_नकल(dm_block_data(b), &ll->mi_le, माप(ll->mi_le));
	ll->biपंचांगap_root = dm_block_location(b);

	dm_पंचांग_unlock(ll->पंचांग, b);

	वापस 0;
पूर्ण

पूर्णांक sm_ll_new_metadata(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग)
अणु
	पूर्णांक r;

	r = sm_ll_init(ll, पंचांग);
	अगर (r < 0)
		वापस r;

	ll->load_ie = metadata_ll_load_ie;
	ll->save_ie = metadata_ll_save_ie;
	ll->init_index = metadata_ll_init_index;
	ll->खोलो_index = metadata_ll_खोलो;
	ll->max_entries = metadata_ll_max_entries;
	ll->commit = metadata_ll_commit;

	ll->nr_blocks = 0;
	ll->nr_allocated = 0;

	r = ll->init_index(ll);
	अगर (r < 0)
		वापस r;

	r = dm_btree_empty(&ll->ref_count_info, &ll->ref_count_root);
	अगर (r < 0)
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक sm_ll_खोलो_metadata(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग,
			व्योम *root_le, माप_प्रकार len)
अणु
	पूर्णांक r;
	काष्ठा disk_sm_root smr;

	अगर (len < माप(काष्ठा disk_sm_root)) अणु
		DMERR("sm_metadata root too small");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * We करोn't know the alignment of the root_le buffer, so need to
	 * copy पूर्णांकo a new काष्ठाure.
	 */
	स_नकल(&smr, root_le, माप(smr));

	r = sm_ll_init(ll, पंचांग);
	अगर (r < 0)
		वापस r;

	ll->load_ie = metadata_ll_load_ie;
	ll->save_ie = metadata_ll_save_ie;
	ll->init_index = metadata_ll_init_index;
	ll->खोलो_index = metadata_ll_खोलो;
	ll->max_entries = metadata_ll_max_entries;
	ll->commit = metadata_ll_commit;

	ll->nr_blocks = le64_to_cpu(smr.nr_blocks);
	ll->nr_allocated = le64_to_cpu(smr.nr_allocated);
	ll->biपंचांगap_root = le64_to_cpu(smr.biपंचांगap_root);
	ll->ref_count_root = le64_to_cpu(smr.ref_count_root);

	वापस ll->खोलो_index(ll);
पूर्ण

/*----------------------------------------------------------------*/

अटल पूर्णांक disk_ll_load_ie(काष्ठा ll_disk *ll, dm_block_t index,
			   काष्ठा disk_index_entry *ie)
अणु
	वापस dm_btree_lookup(&ll->biपंचांगap_info, ll->biपंचांगap_root, &index, ie);
पूर्ण

अटल पूर्णांक disk_ll_save_ie(काष्ठा ll_disk *ll, dm_block_t index,
			   काष्ठा disk_index_entry *ie)
अणु
	__dm_bless_क्रम_disk(ie);
	वापस dm_btree_insert(&ll->biपंचांगap_info, ll->biपंचांगap_root,
			       &index, ie, &ll->biपंचांगap_root);
पूर्ण

अटल पूर्णांक disk_ll_init_index(काष्ठा ll_disk *ll)
अणु
	वापस dm_btree_empty(&ll->biपंचांगap_info, &ll->biपंचांगap_root);
पूर्ण

अटल पूर्णांक disk_ll_खोलो(काष्ठा ll_disk *ll)
अणु
	/* nothing to करो */
	वापस 0;
पूर्ण

अटल dm_block_t disk_ll_max_entries(काष्ठा ll_disk *ll)
अणु
	वापस -1ULL;
पूर्ण

अटल पूर्णांक disk_ll_commit(काष्ठा ll_disk *ll)
अणु
	वापस 0;
पूर्ण

पूर्णांक sm_ll_new_disk(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग)
अणु
	पूर्णांक r;

	r = sm_ll_init(ll, पंचांग);
	अगर (r < 0)
		वापस r;

	ll->load_ie = disk_ll_load_ie;
	ll->save_ie = disk_ll_save_ie;
	ll->init_index = disk_ll_init_index;
	ll->खोलो_index = disk_ll_खोलो;
	ll->max_entries = disk_ll_max_entries;
	ll->commit = disk_ll_commit;

	ll->nr_blocks = 0;
	ll->nr_allocated = 0;

	r = ll->init_index(ll);
	अगर (r < 0)
		वापस r;

	r = dm_btree_empty(&ll->ref_count_info, &ll->ref_count_root);
	अगर (r < 0)
		वापस r;

	वापस 0;
पूर्ण

पूर्णांक sm_ll_खोलो_disk(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग,
		    व्योम *root_le, माप_प्रकार len)
अणु
	पूर्णांक r;
	काष्ठा disk_sm_root *smr = root_le;

	अगर (len < माप(काष्ठा disk_sm_root)) अणु
		DMERR("sm_metadata root too small");
		वापस -ENOMEM;
	पूर्ण

	r = sm_ll_init(ll, पंचांग);
	अगर (r < 0)
		वापस r;

	ll->load_ie = disk_ll_load_ie;
	ll->save_ie = disk_ll_save_ie;
	ll->init_index = disk_ll_init_index;
	ll->खोलो_index = disk_ll_खोलो;
	ll->max_entries = disk_ll_max_entries;
	ll->commit = disk_ll_commit;

	ll->nr_blocks = le64_to_cpu(smr->nr_blocks);
	ll->nr_allocated = le64_to_cpu(smr->nr_allocated);
	ll->biपंचांगap_root = le64_to_cpu(smr->biपंचांगap_root);
	ll->ref_count_root = le64_to_cpu(smr->ref_count_root);

	वापस ll->खोलो_index(ll);
पूर्ण

/*----------------------------------------------------------------*/
