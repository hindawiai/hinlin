<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_SPACE_MAP_COMMON_H
#घोषणा DM_SPACE_MAP_COMMON_H

#समावेश "dm-btree.h"

/*----------------------------------------------------------------*/

/*
 * Low level disk क्रमmat
 *
 * Biपंचांगap btree
 * ------------
 *
 * Each value stored in the btree is an index_entry.  This poपूर्णांकs to a
 * block that is used as a biपंचांगap.  Within the biपंचांगap hold 2 bits per
 * entry, which represent UNUSED = 0, REF_COUNT = 1, REF_COUNT = 2 and
 * REF_COUNT = many.
 *
 * Refcount btree
 * --------------
 *
 * Any entry that has a ref count higher than 2 माला_लो entered in the ref
 * count tree.  The leaf values क्रम this tree is the 32-bit ref count.
 */

काष्ठा disk_index_entry अणु
	__le64 blocknr;
	__le32 nr_मुक्त;
	__le32 none_मुक्त_beक्रमe;
पूर्ण __attribute__ ((packed, aligned(8)));


#घोषणा MAX_METADATA_BITMAPS 255
काष्ठा disk_metadata_index अणु
	__le32 csum;
	__le32 padding;
	__le64 blocknr;

	काष्ठा disk_index_entry index[MAX_METADATA_BITMAPS];
पूर्ण __attribute__ ((packed, aligned(8)));

काष्ठा ll_disk;

प्रकार पूर्णांक (*load_ie_fn)(काष्ठा ll_disk *ll, dm_block_t index, काष्ठा disk_index_entry *result);
प्रकार पूर्णांक (*save_ie_fn)(काष्ठा ll_disk *ll, dm_block_t index, काष्ठा disk_index_entry *ie);
प्रकार पूर्णांक (*init_index_fn)(काष्ठा ll_disk *ll);
प्रकार पूर्णांक (*खोलो_index_fn)(काष्ठा ll_disk *ll);
प्रकार dm_block_t (*max_index_entries_fn)(काष्ठा ll_disk *ll);
प्रकार पूर्णांक (*commit_fn)(काष्ठा ll_disk *ll);

काष्ठा ll_disk अणु
	काष्ठा dm_transaction_manager *पंचांग;
	काष्ठा dm_btree_info biपंचांगap_info;
	काष्ठा dm_btree_info ref_count_info;

	uपूर्णांक32_t block_size;
	uपूर्णांक32_t entries_per_block;
	dm_block_t nr_blocks;
	dm_block_t nr_allocated;

	/*
	 * biपंचांगap_root may be a btree root or a simple index.
	 */
	dm_block_t biपंचांगap_root;

	dm_block_t ref_count_root;

	काष्ठा disk_metadata_index mi_le;
	load_ie_fn load_ie;
	save_ie_fn save_ie;
	init_index_fn init_index;
	खोलो_index_fn खोलो_index;
	max_index_entries_fn max_entries;
	commit_fn commit;
	bool biपंचांगap_index_changed:1;
पूर्ण;

काष्ठा disk_sm_root अणु
	__le64 nr_blocks;
	__le64 nr_allocated;
	__le64 biपंचांगap_root;
	__le64 ref_count_root;
पूर्ण __attribute__ ((packed, aligned(8)));

#घोषणा ENTRIES_PER_BYTE 4

काष्ठा disk_biपंचांगap_header अणु
	__le32 csum;
	__le32 not_used;
	__le64 blocknr;
पूर्ण __attribute__ ((packed, aligned(8)));

क्रमागत allocation_event अणु
	SM_NONE,
	SM_ALLOC,
	SM_FREE,
पूर्ण;

/*----------------------------------------------------------------*/

पूर्णांक sm_ll_extend(काष्ठा ll_disk *ll, dm_block_t extra_blocks);
पूर्णांक sm_ll_lookup_biपंचांगap(काष्ठा ll_disk *ll, dm_block_t b, uपूर्णांक32_t *result);
पूर्णांक sm_ll_lookup(काष्ठा ll_disk *ll, dm_block_t b, uपूर्णांक32_t *result);
पूर्णांक sm_ll_find_मुक्त_block(काष्ठा ll_disk *ll, dm_block_t begin,
			  dm_block_t end, dm_block_t *result);
पूर्णांक sm_ll_find_common_मुक्त_block(काष्ठा ll_disk *old_ll, काष्ठा ll_disk *new_ll,
	                         dm_block_t begin, dm_block_t end, dm_block_t *result);
पूर्णांक sm_ll_insert(काष्ठा ll_disk *ll, dm_block_t b, uपूर्णांक32_t ref_count, क्रमागत allocation_event *ev);
पूर्णांक sm_ll_inc(काष्ठा ll_disk *ll, dm_block_t b, क्रमागत allocation_event *ev);
पूर्णांक sm_ll_dec(काष्ठा ll_disk *ll, dm_block_t b, क्रमागत allocation_event *ev);
पूर्णांक sm_ll_commit(काष्ठा ll_disk *ll);

पूर्णांक sm_ll_new_metadata(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग);
पूर्णांक sm_ll_खोलो_metadata(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग,
			व्योम *root_le, माप_प्रकार len);

पूर्णांक sm_ll_new_disk(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग);
पूर्णांक sm_ll_खोलो_disk(काष्ठा ll_disk *ll, काष्ठा dm_transaction_manager *पंचांग,
		    व्योम *root_le, माप_प्रकार len);

/*----------------------------------------------------------------*/

#पूर्ण_अगर	/* DM_SPACE_MAP_COMMON_H */
