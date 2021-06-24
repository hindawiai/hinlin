<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BTREE_H
#घोषणा BTREE_H

#समावेश <linux/kernel.h>
#समावेश <linux/mempool.h>

/**
 * DOC: B+Tree basics
 *
 * A B+Tree is a data काष्ठाure क्रम looking up arbitrary (currently allowing
 * अचिन्हित दीर्घ, u32, u64 and 2 * u64) keys पूर्णांकo poपूर्णांकers. The data काष्ठाure
 * is described at https://en.wikipedia.org/wiki/B-tree, we currently करो not
 * use binary search to find the key on lookups.
 *
 * Each B+Tree consists of a head, that contains bookkeeping inक्रमmation and
 * a variable number (starting with zero) nodes. Each node contains the keys
 * and poपूर्णांकers to sub-nodes, or, क्रम leaf nodes, the keys and values क्रम the
 * tree entries.
 *
 * Each node in this implementation has the following layout:
 * [key1, key2, ..., keyN] [val1, val2, ..., valN]
 *
 * Each key here is an array of अचिन्हित दीर्घs, geo->no_दीर्घs in total. The
 * number of keys and values (N) is geo->no_pairs.
 */

/**
 * काष्ठा btree_head - btree head
 *
 * @node: the first node in the tree
 * @mempool: mempool used क्रम node allocations
 * @height: current of the tree
 */
काष्ठा btree_head अणु
	अचिन्हित दीर्घ *node;
	mempool_t *mempool;
	पूर्णांक height;
पूर्ण;

/* btree geometry */
काष्ठा btree_geo;

/**
 * btree_alloc - allocate function क्रम the mempool
 * @gfp_mask: gfp mask क्रम the allocation
 * @pool_data: unused
 */
व्योम *btree_alloc(gfp_t gfp_mask, व्योम *pool_data);

/**
 * btree_मुक्त - मुक्त function क्रम the mempool
 * @element: the element to मुक्त
 * @pool_data: unused
 */
व्योम btree_मुक्त(व्योम *element, व्योम *pool_data);

/**
 * btree_init_mempool - initialise a btree with given mempool
 *
 * @head: the btree head to initialise
 * @mempool: the mempool to use
 *
 * When this function is used, there is no need to destroy
 * the mempool.
 */
व्योम btree_init_mempool(काष्ठा btree_head *head, mempool_t *mempool);

/**
 * btree_init - initialise a btree
 *
 * @head: the btree head to initialise
 *
 * This function allocates the memory pool that the
 * btree needs. Returns zero or a negative error code
 * (-%ENOMEM) when memory allocation fails.
 *
 */
पूर्णांक __must_check btree_init(काष्ठा btree_head *head);

/**
 * btree_destroy - destroy mempool
 *
 * @head: the btree head to destroy
 *
 * This function destroys the पूर्णांकernal memory pool, use only
 * when using btree_init(), not with btree_init_mempool().
 */
व्योम btree_destroy(काष्ठा btree_head *head);

/**
 * btree_lookup - look up a key in the btree
 *
 * @head: the btree to look in
 * @geo: the btree geometry
 * @key: the key to look up
 *
 * This function वापसs the value क्रम the given key, or %शून्य.
 */
व्योम *btree_lookup(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		   अचिन्हित दीर्घ *key);

/**
 * btree_insert - insert an entry पूर्णांकo the btree
 *
 * @head: the btree to add to
 * @geo: the btree geometry
 * @key: the key to add (must not alपढ़ोy be present)
 * @val: the value to add (must not be %शून्य)
 * @gfp: allocation flags क्रम node allocations
 *
 * This function वापसs 0 अगर the item could be added, or an
 * error code अगर it failed (may fail due to memory pressure).
 */
पूर्णांक __must_check btree_insert(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
			      अचिन्हित दीर्घ *key, व्योम *val, gfp_t gfp);
/**
 * btree_update - update an entry in the btree
 *
 * @head: the btree to update
 * @geo: the btree geometry
 * @key: the key to update
 * @val: the value to change it to (must not be %शून्य)
 *
 * This function वापसs 0 अगर the update was successful, or
 * -%ENOENT अगर the key could not be found.
 */
पूर्णांक btree_update(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		 अचिन्हित दीर्घ *key, व्योम *val);
/**
 * btree_हटाओ - हटाओ an entry from the btree
 *
 * @head: the btree to update
 * @geo: the btree geometry
 * @key: the key to हटाओ
 *
 * This function वापसs the हटाओd entry, or %शून्य अगर the key
 * could not be found.
 */
व्योम *btree_हटाओ(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		   अचिन्हित दीर्घ *key);

/**
 * btree_merge - merge two btrees
 *
 * @target: the tree that माला_लो all the entries
 * @victim: the tree that माला_लो merged पूर्णांकo @target
 * @geo: the btree geometry
 * @gfp: allocation flags
 *
 * The two trees @target and @victim may not contain the same keys,
 * that is a bug and triggers a BUG(). This function वापसs zero
 * अगर the trees were merged successfully, and may वापस a failure
 * when memory allocation fails, in which हाल both trees might have
 * been partially merged, i.e. some entries have been moved from
 * @victim to @target.
 */
पूर्णांक btree_merge(काष्ठा btree_head *target, काष्ठा btree_head *victim,
		काष्ठा btree_geo *geo, gfp_t gfp);

/**
 * btree_last - get last entry in btree
 *
 * @head: btree head
 * @geo: btree geometry
 * @key: last key
 *
 * Returns the last entry in the btree, and sets @key to the key
 * of that entry; वापसs शून्य अगर the tree is empty, in that हाल
 * key is not changed.
 */
व्योम *btree_last(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		 अचिन्हित दीर्घ *key);

/**
 * btree_get_prev - get previous entry
 *
 * @head: btree head
 * @geo: btree geometry
 * @key: poपूर्णांकer to key
 *
 * The function वापसs the next item right beक्रमe the value poपूर्णांकed to by
 * @key, and updates @key with its key, or वापसs %शून्य when there is no
 * entry with a key smaller than the given key.
 */
व्योम *btree_get_prev(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		     अचिन्हित दीर्घ *key);


/* पूर्णांकernal use, use btree_visitorअणुl,32,64,128पूर्ण */
माप_प्रकार btree_visitor(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
		     अचिन्हित दीर्घ opaque,
		     व्योम (*func)(व्योम *elem, अचिन्हित दीर्घ opaque,
				  अचिन्हित दीर्घ *key, माप_प्रकार index,
				  व्योम *func2),
		     व्योम *func2);

/* पूर्णांकernal use, use btree_grim_visitorअणुl,32,64,128पूर्ण */
माप_प्रकार btree_grim_visitor(काष्ठा btree_head *head, काष्ठा btree_geo *geo,
			  अचिन्हित दीर्घ opaque,
			  व्योम (*func)(व्योम *elem, अचिन्हित दीर्घ opaque,
				       अचिन्हित दीर्घ *key,
				       माप_प्रकार index, व्योम *func2),
			  व्योम *func2);


#समावेश <linux/btree-128.h>

बाह्य काष्ठा btree_geo btree_geo32;
#घोषणा BTREE_TYPE_SUFFIX l
#घोषणा BTREE_TYPE_BITS BITS_PER_LONG
#घोषणा BTREE_TYPE_GEO &btree_geo32
#घोषणा BTREE_KEYTYPE अचिन्हित दीर्घ
#समावेश <linux/btree-type.h>

#घोषणा btree_क्रम_each_safel(head, key, val)	\
	क्रम (val = btree_lastl(head, &key);	\
	     val;				\
	     val = btree_get_prevl(head, &key))

#घोषणा BTREE_TYPE_SUFFIX 32
#घोषणा BTREE_TYPE_BITS 32
#घोषणा BTREE_TYPE_GEO &btree_geo32
#घोषणा BTREE_KEYTYPE u32
#समावेश <linux/btree-type.h>

#घोषणा btree_क्रम_each_safe32(head, key, val)	\
	क्रम (val = btree_last32(head, &key);	\
	     val;				\
	     val = btree_get_prev32(head, &key))

बाह्य काष्ठा btree_geo btree_geo64;
#घोषणा BTREE_TYPE_SUFFIX 64
#घोषणा BTREE_TYPE_BITS 64
#घोषणा BTREE_TYPE_GEO &btree_geo64
#घोषणा BTREE_KEYTYPE u64
#समावेश <linux/btree-type.h>

#घोषणा btree_क्रम_each_safe64(head, key, val)	\
	क्रम (val = btree_last64(head, &key);	\
	     val;				\
	     val = btree_get_prev64(head, &key))

#पूर्ण_अगर
