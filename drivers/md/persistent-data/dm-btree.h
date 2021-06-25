<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */
#अगर_अघोषित _LINUX_DM_BTREE_H
#घोषणा _LINUX_DM_BTREE_H

#समावेश "dm-block-manager.h"

काष्ठा dm_transaction_manager;

/*----------------------------------------------------------------*/

/*
 * Annotations used to check on-disk metadata is handled as little-endian.
 */
#अगर_घोषित __CHECKER__
#  define __dm_written_to_disk(x) __releases(x)
#  define __dm_पढ़ोs_from_disk(x) __acquires(x)
#  define __dm_bless_क्रम_disk(x) __acquire(x)
#  define __dm_unbless_क्रम_disk(x) __release(x)
#अन्यथा
#  define __dm_written_to_disk(x)
#  define __dm_पढ़ोs_from_disk(x)
#  define __dm_bless_क्रम_disk(x)
#  define __dm_unbless_क्रम_disk(x)
#पूर्ण_अगर

/*----------------------------------------------------------------*/

/*
 * Manipulates hierarchical B+ trees with 64-bit keys and arbitrary-sized
 * values.
 */

/*
 * Inक्रमmation about the values stored within the btree.
 */
काष्ठा dm_btree_value_type अणु
	व्योम *context;

	/*
	 * The size in bytes of each value.
	 */
	uपूर्णांक32_t size;

	/*
	 * Any of these methods can be safely set to शून्य अगर you करो not
	 * need the corresponding feature.
	 */

	/*
	 * The btree is making a duplicate of the value, क्रम instance
	 * because previously-shared btree nodes have now भागerged.
	 * @value argument is the new copy that the copy function may modअगरy.
	 * (Probably it just wants to increment a reference count
	 * somewhere.) This method is _not_ called क्रम insertion of a new
	 * value: It is assumed the ref count is alपढ़ोy 1.
	 */
	व्योम (*inc)(व्योम *context, स्थिर व्योम *value);

	/*
	 * This value is being deleted.  The btree takes care of मुक्तing
	 * the memory poपूर्णांकed to by @value.  Often the del function just
	 * needs to decrement a reference count somewhere.
	 */
	व्योम (*dec)(व्योम *context, स्थिर व्योम *value);

	/*
	 * A test क्रम equality between two values.  When a value is
	 * overwritten with a new one, the old one has the dec method
	 * called _unless_ the new and old value are deemed equal.
	 */
	पूर्णांक (*equal)(व्योम *context, स्थिर व्योम *value1, स्थिर व्योम *value2);
पूर्ण;

/*
 * The shape and contents of a btree.
 */
काष्ठा dm_btree_info अणु
	काष्ठा dm_transaction_manager *पंचांग;

	/*
	 * Number of nested btrees. (Not the depth of a single tree.)
	 */
	अचिन्हित levels;
	काष्ठा dm_btree_value_type value_type;
पूर्ण;

/*
 * Set up an empty tree.  O(1).
 */
पूर्णांक dm_btree_empty(काष्ठा dm_btree_info *info, dm_block_t *root);

/*
 * Delete a tree.  O(n) - this is the slow one!  It can also block, so
 * please करोn't call it on an IO path.
 */
पूर्णांक dm_btree_del(काष्ठा dm_btree_info *info, dm_block_t root);

/*
 * All the lookup functions वापस -ENODATA अगर the key cannot be found.
 */

/*
 * Tries to find a key that matches exactly.  O(ln(n))
 */
पूर्णांक dm_btree_lookup(काष्ठा dm_btree_info *info, dm_block_t root,
		    uपूर्णांक64_t *keys, व्योम *value_le);

/*
 * Tries to find the first key where the bottom level key is >= to that
 * given.  Useful क्रम skipping empty sections of the btree.
 */
पूर्णांक dm_btree_lookup_next(काष्ठा dm_btree_info *info, dm_block_t root,
			 uपूर्णांक64_t *keys, uपूर्णांक64_t *rkey, व्योम *value_le);

/*
 * Insertion (or overग_लिखो an existing value).  O(ln(n))
 */
पूर्णांक dm_btree_insert(काष्ठा dm_btree_info *info, dm_block_t root,
		    uपूर्णांक64_t *keys, व्योम *value, dm_block_t *new_root)
		    __dm_written_to_disk(value);

/*
 * A variant of insert that indicates whether it actually inserted or just
 * overwrote.  Useful अगर you're keeping track of the number of entries in a
 * tree.
 */
पूर्णांक dm_btree_insert_notअगरy(काष्ठा dm_btree_info *info, dm_block_t root,
			   uपूर्णांक64_t *keys, व्योम *value, dm_block_t *new_root,
			   पूर्णांक *inserted)
			   __dm_written_to_disk(value);

/*
 * Remove a key अगर present.  This करोesn't हटाओ empty sub trees.  Normally
 * subtrees represent a separate entity, like a snapshot map, so this is
 * correct behaviour.  O(ln(n)).
 */
पूर्णांक dm_btree_हटाओ(काष्ठा dm_btree_info *info, dm_block_t root,
		    uपूर्णांक64_t *keys, dm_block_t *new_root);

/*
 * Removes a _contiguous_ run of values starting from 'keys' and not
 * reaching keys2 (where keys2 is keys with the final key replaced with
 * 'end_key').  'end_key' is the one-past-the-end value.  'keys' may be
 * altered.
 */
पूर्णांक dm_btree_हटाओ_leaves(काष्ठा dm_btree_info *info, dm_block_t root,
			   uपूर्णांक64_t *keys, uपूर्णांक64_t end_key,
			   dm_block_t *new_root, अचिन्हित *nr_हटाओd);

/*
 * Returns < 0 on failure.  Otherwise the number of key entries that have
 * been filled out.  Remember trees can have zero entries, and as such have
 * no lowest key.
 */
पूर्णांक dm_btree_find_lowest_key(काष्ठा dm_btree_info *info, dm_block_t root,
			     uपूर्णांक64_t *result_keys);

/*
 * Returns < 0 on failure.  Otherwise the number of key entries that have
 * been filled out.  Remember trees can have zero entries, and as such have
 * no highest key.
 */
पूर्णांक dm_btree_find_highest_key(काष्ठा dm_btree_info *info, dm_block_t root,
			      uपूर्णांक64_t *result_keys);

/*
 * Iterate through the a btree, calling fn() on each entry.
 * It only works क्रम single level trees and is पूर्णांकernally recursive, so
 * monitor stack usage carefully.
 */
पूर्णांक dm_btree_walk(काष्ठा dm_btree_info *info, dm_block_t root,
		  पूर्णांक (*fn)(व्योम *context, uपूर्णांक64_t *keys, व्योम *leaf),
		  व्योम *context);


/*----------------------------------------------------------------*/

/*
 * Cursor API.  This करोes not follow the rolling lock convention.  Since we
 * know the order that values are required we can issue prefetches to speed
 * up iteration.  Use on a single level btree only.
 */
#घोषणा DM_BTREE_CURSOR_MAX_DEPTH 16

काष्ठा cursor_node अणु
	काष्ठा dm_block *b;
	अचिन्हित index;
पूर्ण;

काष्ठा dm_btree_cursor अणु
	काष्ठा dm_btree_info *info;
	dm_block_t root;

	bool prefetch_leaves;
	अचिन्हित depth;
	काष्ठा cursor_node nodes[DM_BTREE_CURSOR_MAX_DEPTH];
पूर्ण;

/*
 * Creates a fresh cursor.  If prefetch_leaves is set then it is assumed
 * the btree contains block indexes that will be prefetched.  The cursor is
 * quite large, so you probably करोn't want to put it on the stack.
 */
पूर्णांक dm_btree_cursor_begin(काष्ठा dm_btree_info *info, dm_block_t root,
			  bool prefetch_leaves, काष्ठा dm_btree_cursor *c);
व्योम dm_btree_cursor_end(काष्ठा dm_btree_cursor *c);
पूर्णांक dm_btree_cursor_next(काष्ठा dm_btree_cursor *c);
पूर्णांक dm_btree_cursor_skip(काष्ठा dm_btree_cursor *c, uपूर्णांक32_t count);
पूर्णांक dm_btree_cursor_get_value(काष्ठा dm_btree_cursor *c, uपूर्णांक64_t *key, व्योम *value_le);

#पूर्ण_अगर	/* _LINUX_DM_BTREE_H */
