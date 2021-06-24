<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ceph/pagelist.h>

काष्ठा ceph_pagelist *ceph_pagelist_alloc(gfp_t gfp_flags)
अणु
	काष्ठा ceph_pagelist *pl;

	pl = kदो_स्मृति(माप(*pl), gfp_flags);
	अगर (!pl)
		वापस शून्य;

	INIT_LIST_HEAD(&pl->head);
	pl->mapped_tail = शून्य;
	pl->length = 0;
	pl->room = 0;
	INIT_LIST_HEAD(&pl->मुक्त_list);
	pl->num_pages_मुक्त = 0;
	refcount_set(&pl->refcnt, 1);

	वापस pl;
पूर्ण
EXPORT_SYMBOL(ceph_pagelist_alloc);

अटल व्योम ceph_pagelist_unmap_tail(काष्ठा ceph_pagelist *pl)
अणु
	अगर (pl->mapped_tail) अणु
		काष्ठा page *page = list_entry(pl->head.prev, काष्ठा page, lru);
		kunmap(page);
		pl->mapped_tail = शून्य;
	पूर्ण
पूर्ण

व्योम ceph_pagelist_release(काष्ठा ceph_pagelist *pl)
अणु
	अगर (!refcount_dec_and_test(&pl->refcnt))
		वापस;
	ceph_pagelist_unmap_tail(pl);
	जबतक (!list_empty(&pl->head)) अणु
		काष्ठा page *page = list_first_entry(&pl->head, काष्ठा page,
						     lru);
		list_del(&page->lru);
		__मुक्त_page(page);
	पूर्ण
	ceph_pagelist_मुक्त_reserve(pl);
	kमुक्त(pl);
पूर्ण
EXPORT_SYMBOL(ceph_pagelist_release);

अटल पूर्णांक ceph_pagelist_addpage(काष्ठा ceph_pagelist *pl)
अणु
	काष्ठा page *page;

	अगर (!pl->num_pages_मुक्त) अणु
		page = __page_cache_alloc(GFP_NOFS);
	पूर्ण अन्यथा अणु
		page = list_first_entry(&pl->मुक्त_list, काष्ठा page, lru);
		list_del(&page->lru);
		--pl->num_pages_मुक्त;
	पूर्ण
	अगर (!page)
		वापस -ENOMEM;
	pl->room += PAGE_SIZE;
	ceph_pagelist_unmap_tail(pl);
	list_add_tail(&page->lru, &pl->head);
	pl->mapped_tail = kmap(page);
	वापस 0;
पूर्ण

पूर्णांक ceph_pagelist_append(काष्ठा ceph_pagelist *pl, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	जबतक (pl->room < len) अणु
		माप_प्रकार bit = pl->room;
		पूर्णांक ret;

		स_नकल(pl->mapped_tail + (pl->length & ~PAGE_MASK),
		       buf, bit);
		pl->length += bit;
		pl->room -= bit;
		buf += bit;
		len -= bit;
		ret = ceph_pagelist_addpage(pl);
		अगर (ret)
			वापस ret;
	पूर्ण

	स_नकल(pl->mapped_tail + (pl->length & ~PAGE_MASK), buf, len);
	pl->length += len;
	pl->room -= len;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_pagelist_append);

/* Allocate enough pages क्रम a pagelist to append the given amount
 * of data without without allocating.
 * Returns: 0 on success, -ENOMEM on error.
 */
पूर्णांक ceph_pagelist_reserve(काष्ठा ceph_pagelist *pl, माप_प्रकार space)
अणु
	अगर (space <= pl->room)
		वापस 0;
	space -= pl->room;
	space = (space + PAGE_SIZE - 1) >> PAGE_SHIFT;   /* conv to num pages */

	जबतक (space > pl->num_pages_मुक्त) अणु
		काष्ठा page *page = __page_cache_alloc(GFP_NOFS);
		अगर (!page)
			वापस -ENOMEM;
		list_add_tail(&page->lru, &pl->मुक्त_list);
		++pl->num_pages_मुक्त;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_pagelist_reserve);

/* Free any pages that have been pपुनः_स्मृतिated. */
पूर्णांक ceph_pagelist_मुक्त_reserve(काष्ठा ceph_pagelist *pl)
अणु
	जबतक (!list_empty(&pl->मुक्त_list)) अणु
		काष्ठा page *page = list_first_entry(&pl->मुक्त_list,
						     काष्ठा page, lru);
		list_del(&page->lru);
		__मुक्त_page(page);
		--pl->num_pages_मुक्त;
	पूर्ण
	BUG_ON(pl->num_pages_मुक्त);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_pagelist_मुक्त_reserve);

/* Create a truncation poपूर्णांक. */
व्योम ceph_pagelist_set_cursor(काष्ठा ceph_pagelist *pl,
			      काष्ठा ceph_pagelist_cursor *c)
अणु
	c->pl = pl;
	c->page_lru = pl->head.prev;
	c->room = pl->room;
पूर्ण
EXPORT_SYMBOL(ceph_pagelist_set_cursor);

/* Truncate a pagelist to the given poपूर्णांक. Move extra pages to reserve.
 * This won't sleep.
 * Returns: 0 on success,
 *          -EINVAL अगर the pagelist करोesn't match the trunc poपूर्णांक pagelist
 */
पूर्णांक ceph_pagelist_truncate(काष्ठा ceph_pagelist *pl,
			   काष्ठा ceph_pagelist_cursor *c)
अणु
	काष्ठा page *page;

	अगर (pl != c->pl)
		वापस -EINVAL;
	ceph_pagelist_unmap_tail(pl);
	जबतक (pl->head.prev != c->page_lru) अणु
		page = list_entry(pl->head.prev, काष्ठा page, lru);
		/* move from pagelist to reserve */
		list_move_tail(&page->lru, &pl->मुक्त_list);
		++pl->num_pages_मुक्त;
	पूर्ण
	pl->room = c->room;
	अगर (!list_empty(&pl->head)) अणु
		page = list_entry(pl->head.prev, काष्ठा page, lru);
		pl->mapped_tail = kmap(page);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_pagelist_truncate);
