<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */
#अगर_अघोषित _LINUX_DM_ARRAY_H
#घोषणा _LINUX_DM_ARRAY_H

#समावेश "dm-btree.h"

/*----------------------------------------------------------------*/

/*
 * The dm-array is a persistent version of an array.  It packs the data
 * more efficiently than a btree which will result in less disk space use,
 * and a perक्रमmance boost.  The element get and set operations are still
 * O(ln(n)), but with a much smaller स्थिरant.
 *
 * The value type काष्ठाure is reused from the btree type to support proper
 * reference counting of values.
 *
 * The arrays implicitly know their length, and bounds are checked क्रम
 * lookups and updated.  It करोesn't store this in an accessible place
 * because it would waste a whole metadata block.  Make sure you store the
 * size aदीर्घ with the array root in your encompassing data.
 *
 * Array entries are indexed via an अचिन्हित पूर्णांकeger starting from zero.
 * Arrays are not sparse; अगर you resize an array to have 'n' entries then
 * 'n - 1' will be the last valid index.
 *
 * Typical use:
 *
 * a) initialise a dm_array_info काष्ठाure.  This describes the array
 *    values and ties it पूर्णांकo a specअगरic transaction manager.  It holds no
 *    instance data; the same info can be used क्रम many similar arrays अगर
 *    you wish.
 *
 * b) Get yourself a root.  The root is the index of a block of data on the
 *    disk that holds a particular instance of an array.  You may have a
 *    pre existing root in your metadata that you wish to use, or you may
 *    want to create a bअक्रम new, empty array with dm_array_empty().
 *
 * Like the other data काष्ठाures in this library, dm_array objects are
 * immutable between transactions.  Update functions will वापस you the
 * root क्रम a _new_ array.  If you've incremented the old root, via
 * dm_पंचांग_inc(), beक्रमe calling the update function you may जारी to use
 * it in parallel with the new root.
 *
 * c) resize an array with dm_array_resize().
 *
 * d) Get a value from the array with dm_array_get_value().
 *
 * e) Set a value in the array with dm_array_set_value().
 *
 * f) Walk an array of values in index order with dm_array_walk().  More
 *    efficient than making many calls to dm_array_get_value().
 *
 * g) Destroy the array with dm_array_del().  This tells the transaction
 *    manager that you're no दीर्घer using this data काष्ठाure so it can
 *    recycle it's blocks.  (dm_array_dec() would be a better name क्रम it,
 *    but del is in keeping with dm_btree_del()).
 */

/*
 * Describes an array.  Don't initialise this काष्ठाure yourself, use the
 * init function below.
 */
काष्ठा dm_array_info अणु
	काष्ठा dm_transaction_manager *पंचांग;
	काष्ठा dm_btree_value_type value_type;
	काष्ठा dm_btree_info btree_info;
पूर्ण;

/*
 * Sets up a dm_array_info काष्ठाure.  You करोn't need to करो anything with
 * this काष्ठाure when you finish using it.
 *
 * info - the काष्ठाure being filled in.
 * पंचांग   - the transaction manager that should supervise this काष्ठाure.
 * vt   - describes the leaf values.
 */
व्योम dm_array_info_init(काष्ठा dm_array_info *info,
			काष्ठा dm_transaction_manager *पंचांग,
			काष्ठा dm_btree_value_type *vt);

/*
 * Create an empty, zero length array.
 *
 * info - describes the array
 * root - on success this will be filled out with the root block
 */
पूर्णांक dm_array_empty(काष्ठा dm_array_info *info, dm_block_t *root);

/*
 * Resizes the array.
 *
 * info - describes the array
 * root - the root block of the array on disk
 * old_size - the caller is responsible क्रम remembering the size of
 *            the array
 * new_size - can be bigger or smaller than old_size
 * value - अगर we're growing the array the new entries will have this value
 * new_root - on success, poपूर्णांकs to the new root block
 *
 * If growing the inc function क्रम 'value' will be called the appropriate
 * number of बार.  So अगर the caller is holding a reference they may want
 * to drop it.
 */
पूर्णांक dm_array_resize(काष्ठा dm_array_info *info, dm_block_t root,
		    uपूर्णांक32_t old_size, uपूर्णांक32_t new_size,
		    स्थिर व्योम *value, dm_block_t *new_root)
	__dm_written_to_disk(value);

/*
 * Creates a new array populated with values provided by a callback
 * function.  This is more efficient than creating an empty array,
 * resizing, and then setting values since that process incurs a lot of
 * copying.
 *
 * Assumes 32bit values क्रम now since it's only used by the cache hपूर्णांक
 * array.
 *
 * info - describes the array
 * root - the root block of the array on disk
 * size - the number of entries in the array
 * fn - the callback
 * context - passed to the callback
 */
प्रकार पूर्णांक (*value_fn)(uपूर्णांक32_t index, व्योम *value_le, व्योम *context);
पूर्णांक dm_array_new(काष्ठा dm_array_info *info, dm_block_t *root,
		 uपूर्णांक32_t size, value_fn fn, व्योम *context);

/*
 * Frees a whole array.  The value_type's decrement operation will be called
 * क्रम all values in the array
 */
पूर्णांक dm_array_del(काष्ठा dm_array_info *info, dm_block_t root);

/*
 * Lookup a value in the array
 *
 * info - describes the array
 * root - root block of the array
 * index - array index
 * value - the value to be पढ़ो.  Will be in on-disk क्रमmat of course.
 *
 * -ENODATA will be वापसed अगर the index is out of bounds.
 */
पूर्णांक dm_array_get_value(काष्ठा dm_array_info *info, dm_block_t root,
		       uपूर्णांक32_t index, व्योम *value);

/*
 * Set an entry in the array.
 *
 * info - describes the array
 * root - root block of the array
 * index - array index
 * value - value to be written to disk.  Make sure you confirm the value is
 *         in on-disk क्रमmat with__dm_bless_क्रम_disk() beक्रमe calling.
 * new_root - the new root block
 *
 * The old value being overwritten will be decremented, the new value
 * incremented.
 *
 * -ENODATA will be वापसed अगर the index is out of bounds.
 */
पूर्णांक dm_array_set_value(काष्ठा dm_array_info *info, dm_block_t root,
		       uपूर्णांक32_t index, स्थिर व्योम *value, dm_block_t *new_root)
	__dm_written_to_disk(value);

/*
 * Walk through all the entries in an array.
 *
 * info - describes the array
 * root - root block of the array
 * fn - called back क्रम every element
 * context - passed to the callback
 */
पूर्णांक dm_array_walk(काष्ठा dm_array_info *info, dm_block_t root,
		  पूर्णांक (*fn)(व्योम *context, uपूर्णांक64_t key, व्योम *leaf),
		  व्योम *context);

/*----------------------------------------------------------------*/

/*
 * Cursor api.
 *
 * This lets you iterate through all the entries in an array efficiently
 * (it will preload metadata).
 *
 * I'm using a cursor, rather than a walk function with a callback because
 * the cache target needs to iterate both the mapping and hपूर्णांक arrays in
 * unison.
 */
काष्ठा dm_array_cursor अणु
	काष्ठा dm_array_info *info;
	काष्ठा dm_btree_cursor cursor;

	काष्ठा dm_block *block;
	काष्ठा array_block *ab;
	अचिन्हित index;
पूर्ण;

पूर्णांक dm_array_cursor_begin(काष्ठा dm_array_info *info,
			  dm_block_t root, काष्ठा dm_array_cursor *c);
व्योम dm_array_cursor_end(काष्ठा dm_array_cursor *c);

uपूर्णांक32_t dm_array_cursor_index(काष्ठा dm_array_cursor *c);
पूर्णांक dm_array_cursor_next(काष्ठा dm_array_cursor *c);
पूर्णांक dm_array_cursor_skip(काष्ठा dm_array_cursor *c, uपूर्णांक32_t count);

/*
 * value_le is only valid जबतक the cursor poपूर्णांकs at the current value.
 */
व्योम dm_array_cursor_get_value(काष्ठा dm_array_cursor *c, व्योम **value_le);

/*----------------------------------------------------------------*/

#पूर्ण_अगर	/* _LINUX_DM_ARRAY_H */
