<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */
#अगर_अघोषित _LINUX_DM_BITSET_H
#घोषणा _LINUX_DM_BITSET_H

#समावेश "dm-array.h"

/*----------------------------------------------------------------*/

/*
 * This bitset type is a thin wrapper round a dm_array of 64bit words.  It
 * uses a tiny, one word cache to reduce the number of array lookups and so
 * increase perक्रमmance.
 *
 * Like the dm-array that it's based on, the caller needs to keep track of
 * the size of the bitset separately.  The underlying dm-array implicitly
 * knows how many words it's storing and will वापस -ENODATA अगर you try
 * and access an out of bounds word.  However, an out of bounds bit in the
 * final word will _not_ be detected, you have been warned.
 *
 * Bits are indexed from zero.

 * Typical use:
 *
 * a) Initialise a dm_disk_bitset काष्ठाure with dm_disk_bitset_init().
 *    This describes the bitset and includes the cache.  It's not called it
 *    dm_bitset_info in line with other data काष्ठाures because it करोes
 *    include instance data.
 *
 * b) Get yourself a root.  The root is the index of a block of data on the
 *    disk that holds a particular instance of an bitset.  You may have a
 *    pre existing root in your metadata that you wish to use, or you may
 *    want to create a bअक्रम new, empty bitset with dm_bitset_empty().
 *
 * Like the other data काष्ठाures in this library, dm_bitset objects are
 * immutable between transactions.  Update functions will वापस you the
 * root क्रम a _new_ array.  If you've incremented the old root, via
 * dm_पंचांग_inc(), beक्रमe calling the update function you may जारी to use
 * it in parallel with the new root.
 *
 * Even पढ़ो operations may trigger the cache to be flushed and as such
 * वापस a root क्रम a new, updated bitset.
 *
 * c) resize a bitset with dm_bitset_resize().
 *
 * d) Set a bit with dm_bitset_set_bit().
 *
 * e) Clear a bit with dm_bitset_clear_bit().
 *
 * f) Test a bit with dm_bitset_test_bit().
 *
 * g) Flush all updates from the cache with dm_bitset_flush().
 *
 * h) Destroy the bitset with dm_bitset_del().  This tells the transaction
 *    manager that you're no दीर्घer using this data काष्ठाure so it can
 *    recycle it's blocks.  (dm_bitset_dec() would be a better name क्रम it,
 *    but del is in keeping with dm_btree_del()).
 */

/*
 * Opaque object.  Unlike dm_array_info, you should have one of these per
 * bitset.  Initialise with dm_disk_bitset_init().
 */
काष्ठा dm_disk_bitset अणु
	काष्ठा dm_array_info array_info;

	uपूर्णांक32_t current_index;
	uपूर्णांक64_t current_bits;

	bool current_index_set:1;
	bool dirty:1;
पूर्ण;

/*
 * Sets up a dm_disk_bitset काष्ठाure.  You करोn't need to करो anything with
 * this काष्ठाure when you finish using it.
 *
 * पंचांग - the transaction manager that should supervise this काष्ठाure
 * info - the काष्ठाure being initialised
 */
व्योम dm_disk_bitset_init(काष्ठा dm_transaction_manager *पंचांग,
			 काष्ठा dm_disk_bitset *info);

/*
 * Create an empty, zero length bitset.
 *
 * info - describes the bitset
 * new_root - on success, poपूर्णांकs to the new root block
 */
पूर्णांक dm_bitset_empty(काष्ठा dm_disk_bitset *info, dm_block_t *new_root);

/*
 * Creates a new bitset populated with values provided by a callback
 * function.  This is more efficient than creating an empty bitset,
 * resizing, and then setting values since that process incurs a lot of
 * copying.
 *
 * info - describes the array
 * root - the root block of the array on disk
 * size - the number of entries in the array
 * fn - the callback
 * context - passed to the callback
 */
प्रकार पूर्णांक (*bit_value_fn)(uपूर्णांक32_t index, bool *value, व्योम *context);
पूर्णांक dm_bitset_new(काष्ठा dm_disk_bitset *info, dm_block_t *root,
		  uपूर्णांक32_t size, bit_value_fn fn, व्योम *context);

/*
 * Resize the bitset.
 *
 * info - describes the bitset
 * old_root - the root block of the array on disk
 * old_nr_entries - the number of bits in the old bitset
 * new_nr_entries - the number of bits you want in the new bitset
 * शेष_value - the value क्रम any new bits
 * new_root - on success, poपूर्णांकs to the new root block
 */
पूर्णांक dm_bitset_resize(काष्ठा dm_disk_bitset *info, dm_block_t old_root,
		     uपूर्णांक32_t old_nr_entries, uपूर्णांक32_t new_nr_entries,
		     bool शेष_value, dm_block_t *new_root);

/*
 * Frees the bitset.
 */
पूर्णांक dm_bitset_del(काष्ठा dm_disk_bitset *info, dm_block_t root);

/*
 * Set a bit.
 *
 * info - describes the bitset
 * root - the root block of the bitset
 * index - the bit index
 * new_root - on success, poपूर्णांकs to the new root block
 *
 * -ENODATA will be वापसed अगर the index is out of bounds.
 */
पूर्णांक dm_bitset_set_bit(काष्ठा dm_disk_bitset *info, dm_block_t root,
		      uपूर्णांक32_t index, dm_block_t *new_root);

/*
 * Clears a bit.
 *
 * info - describes the bitset
 * root - the root block of the bitset
 * index - the bit index
 * new_root - on success, poपूर्णांकs to the new root block
 *
 * -ENODATA will be वापसed अगर the index is out of bounds.
 */
पूर्णांक dm_bitset_clear_bit(काष्ठा dm_disk_bitset *info, dm_block_t root,
			uपूर्णांक32_t index, dm_block_t *new_root);

/*
 * Tests a bit.
 *
 * info - describes the bitset
 * root - the root block of the bitset
 * index - the bit index
 * new_root - on success, poपूर्णांकs to the new root block (cached values may have been written)
 * result - the bit value you're after
 *
 * -ENODATA will be वापसed अगर the index is out of bounds.
 */
पूर्णांक dm_bitset_test_bit(काष्ठा dm_disk_bitset *info, dm_block_t root,
		       uपूर्णांक32_t index, dm_block_t *new_root, bool *result);

/*
 * Flush any cached changes to disk.
 *
 * info - describes the bitset
 * root - the root block of the bitset
 * new_root - on success, poपूर्णांकs to the new root block
 */
पूर्णांक dm_bitset_flush(काष्ठा dm_disk_bitset *info, dm_block_t root,
		    dm_block_t *new_root);

काष्ठा dm_bitset_cursor अणु
	काष्ठा dm_disk_bitset *info;
	काष्ठा dm_array_cursor cursor;

	uपूर्णांक32_t entries_reमुख्यing;
	uपूर्णांक32_t array_index;
	uपूर्णांक32_t bit_index;
	uपूर्णांक64_t current_bits;
पूर्ण;

/*
 * Make sure you've flush any dm_disk_bitset and updated the root beक्रमe
 * using this.
 */
पूर्णांक dm_bitset_cursor_begin(काष्ठा dm_disk_bitset *info,
			   dm_block_t root, uपूर्णांक32_t nr_entries,
			   काष्ठा dm_bitset_cursor *c);
व्योम dm_bitset_cursor_end(काष्ठा dm_bitset_cursor *c);

पूर्णांक dm_bitset_cursor_next(काष्ठा dm_bitset_cursor *c);
पूर्णांक dm_bitset_cursor_skip(काष्ठा dm_bitset_cursor *c, uपूर्णांक32_t count);
bool dm_bitset_cursor_get_value(काष्ठा dm_bitset_cursor *c);

/*----------------------------------------------------------------*/

#पूर्ण_अगर /* _LINUX_DM_BITSET_H */
