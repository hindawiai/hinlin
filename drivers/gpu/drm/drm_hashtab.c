<शैली गुरु>
/**************************************************************************
 *
 * Copyright 2006 Tungsten Graphics, Inc., Bismarck, ND. USA.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 **************************************************************************/
/*
 * Simple खोलो hash tab implementation.
 *
 * Authors:
 * Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 */

#समावेश <linux/export.h>
#समावेश <linux/hash.h>
#समावेश <linux/mm.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm_hashtab.h>
#समावेश <drm/drm_prपूर्णांक.h>

पूर्णांक drm_ht_create(काष्ठा drm_खोलो_hash *ht, अचिन्हित पूर्णांक order)
अणु
	अचिन्हित पूर्णांक size = 1 << order;

	ht->order = order;
	ht->table = शून्य;
	अगर (size <= PAGE_SIZE / माप(*ht->table))
		ht->table = kसुस्मृति(size, माप(*ht->table), GFP_KERNEL);
	अन्यथा
		ht->table = vzalloc(array_size(size, माप(*ht->table)));
	अगर (!ht->table) अणु
		DRM_ERROR("Out of memory for hash table\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_ht_create);

व्योम drm_ht_verbose_list(काष्ठा drm_खोलो_hash *ht, अचिन्हित दीर्घ key)
अणु
	काष्ठा drm_hash_item *entry;
	काष्ठा hlist_head *h_list;
	अचिन्हित पूर्णांक hashed_key;
	पूर्णांक count = 0;

	hashed_key = hash_दीर्घ(key, ht->order);
	DRM_DEBUG("Key is 0x%08lx, Hashed key is 0x%08x\n", key, hashed_key);
	h_list = &ht->table[hashed_key];
	hlist_क्रम_each_entry(entry, h_list, head)
		DRM_DEBUG("count %d, key: 0x%08lx\n", count++, entry->key);
पूर्ण

अटल काष्ठा hlist_node *drm_ht_find_key(काष्ठा drm_खोलो_hash *ht,
					  अचिन्हित दीर्घ key)
अणु
	काष्ठा drm_hash_item *entry;
	काष्ठा hlist_head *h_list;
	अचिन्हित पूर्णांक hashed_key;

	hashed_key = hash_दीर्घ(key, ht->order);
	h_list = &ht->table[hashed_key];
	hlist_क्रम_each_entry(entry, h_list, head) अणु
		अगर (entry->key == key)
			वापस &entry->head;
		अगर (entry->key > key)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा hlist_node *drm_ht_find_key_rcu(काष्ठा drm_खोलो_hash *ht,
					      अचिन्हित दीर्घ key)
अणु
	काष्ठा drm_hash_item *entry;
	काष्ठा hlist_head *h_list;
	अचिन्हित पूर्णांक hashed_key;

	hashed_key = hash_दीर्घ(key, ht->order);
	h_list = &ht->table[hashed_key];
	hlist_क्रम_each_entry_rcu(entry, h_list, head) अणु
		अगर (entry->key == key)
			वापस &entry->head;
		अगर (entry->key > key)
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक drm_ht_insert_item(काष्ठा drm_खोलो_hash *ht, काष्ठा drm_hash_item *item)
अणु
	काष्ठा drm_hash_item *entry;
	काष्ठा hlist_head *h_list;
	काष्ठा hlist_node *parent;
	अचिन्हित पूर्णांक hashed_key;
	अचिन्हित दीर्घ key = item->key;

	hashed_key = hash_दीर्घ(key, ht->order);
	h_list = &ht->table[hashed_key];
	parent = शून्य;
	hlist_क्रम_each_entry(entry, h_list, head) अणु
		अगर (entry->key == key)
			वापस -EINVAL;
		अगर (entry->key > key)
			अवरोध;
		parent = &entry->head;
	पूर्ण
	अगर (parent) अणु
		hlist_add_behind_rcu(&item->head, parent);
	पूर्ण अन्यथा अणु
		hlist_add_head_rcu(&item->head, h_list);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_ht_insert_item);

/*
 * Just insert an item and वापस any "bits" bit key that hasn't been
 * used beक्रमe.
 */
पूर्णांक drm_ht_just_insert_please(काष्ठा drm_खोलो_hash *ht, काष्ठा drm_hash_item *item,
			      अचिन्हित दीर्घ seed, पूर्णांक bits, पूर्णांक shअगरt,
			      अचिन्हित दीर्घ add)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ mask = (1UL << bits) - 1;
	अचिन्हित दीर्घ first, unshअगरted_key;

	unshअगरted_key = hash_दीर्घ(seed, bits);
	first = unshअगरted_key;
	करो अणु
		item->key = (unshअगरted_key << shअगरt) + add;
		ret = drm_ht_insert_item(ht, item);
		अगर (ret)
			unshअगरted_key = (unshअगरted_key + 1) & mask;
	पूर्ण जबतक(ret && (unshअगरted_key != first));

	अगर (ret) अणु
		DRM_ERROR("Available key bit space exhausted\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_ht_just_insert_please);

पूर्णांक drm_ht_find_item(काष्ठा drm_खोलो_hash *ht, अचिन्हित दीर्घ key,
		     काष्ठा drm_hash_item **item)
अणु
	काष्ठा hlist_node *list;

	list = drm_ht_find_key_rcu(ht, key);
	अगर (!list)
		वापस -EINVAL;

	*item = hlist_entry(list, काष्ठा drm_hash_item, head);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_ht_find_item);

पूर्णांक drm_ht_हटाओ_key(काष्ठा drm_खोलो_hash *ht, अचिन्हित दीर्घ key)
अणु
	काष्ठा hlist_node *list;

	list = drm_ht_find_key(ht, key);
	अगर (list) अणु
		hlist_del_init_rcu(list);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक drm_ht_हटाओ_item(काष्ठा drm_खोलो_hash *ht, काष्ठा drm_hash_item *item)
अणु
	hlist_del_init_rcu(&item->head);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_ht_हटाओ_item);

व्योम drm_ht_हटाओ(काष्ठा drm_खोलो_hash *ht)
अणु
	अगर (ht->table) अणु
		kvमुक्त(ht->table);
		ht->table = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_ht_हटाओ);
