<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013
 * Phillip Lougher <phillip@squashfs.org.uk>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश "page_actor.h"

/*
 * This file contains implementations of page_actor क्रम decompressing पूर्णांकo
 * an पूर्णांकermediate buffer, and क्रम decompressing directly पूर्णांकo the
 * page cache.
 *
 * Calling code should aव्योम sleeping between calls to squashfs_first_page()
 * and squashfs_finish_page().
 */

/* Implementation of page_actor क्रम decompressing पूर्णांकo पूर्णांकermediate buffer */
अटल व्योम *cache_first_page(काष्ठा squashfs_page_actor *actor)
अणु
	actor->next_page = 1;
	वापस actor->buffer[0];
पूर्ण

अटल व्योम *cache_next_page(काष्ठा squashfs_page_actor *actor)
अणु
	अगर (actor->next_page == actor->pages)
		वापस शून्य;

	वापस actor->buffer[actor->next_page++];
पूर्ण

अटल व्योम cache_finish_page(काष्ठा squashfs_page_actor *actor)
अणु
	/* empty */
पूर्ण

काष्ठा squashfs_page_actor *squashfs_page_actor_init(व्योम **buffer,
	पूर्णांक pages, पूर्णांक length)
अणु
	काष्ठा squashfs_page_actor *actor = kदो_स्मृति(माप(*actor), GFP_KERNEL);

	अगर (actor == शून्य)
		वापस शून्य;

	actor->length = length ? : pages * PAGE_SIZE;
	actor->buffer = buffer;
	actor->pages = pages;
	actor->next_page = 0;
	actor->squashfs_first_page = cache_first_page;
	actor->squashfs_next_page = cache_next_page;
	actor->squashfs_finish_page = cache_finish_page;
	वापस actor;
पूर्ण

/* Implementation of page_actor क्रम decompressing directly पूर्णांकo page cache. */
अटल व्योम *direct_first_page(काष्ठा squashfs_page_actor *actor)
अणु
	actor->next_page = 1;
	वापस actor->pageaddr = kmap_atomic(actor->page[0]);
पूर्ण

अटल व्योम *direct_next_page(काष्ठा squashfs_page_actor *actor)
अणु
	अगर (actor->pageaddr)
		kunmap_atomic(actor->pageaddr);

	वापस actor->pageaddr = actor->next_page == actor->pages ? शून्य :
		kmap_atomic(actor->page[actor->next_page++]);
पूर्ण

अटल व्योम direct_finish_page(काष्ठा squashfs_page_actor *actor)
अणु
	अगर (actor->pageaddr)
		kunmap_atomic(actor->pageaddr);
पूर्ण

काष्ठा squashfs_page_actor *squashfs_page_actor_init_special(काष्ठा page **page,
	पूर्णांक pages, पूर्णांक length)
अणु
	काष्ठा squashfs_page_actor *actor = kदो_स्मृति(माप(*actor), GFP_KERNEL);

	अगर (actor == शून्य)
		वापस शून्य;

	actor->length = length ? : pages * PAGE_SIZE;
	actor->page = page;
	actor->pages = pages;
	actor->next_page = 0;
	actor->pageaddr = शून्य;
	actor->squashfs_first_page = direct_first_page;
	actor->squashfs_next_page = direct_next_page;
	actor->squashfs_finish_page = direct_finish_page;
	वापस actor;
पूर्ण
