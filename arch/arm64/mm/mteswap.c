<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/pagemap.h>
#समावेश <linux/xarray.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <यंत्र/mte.h>

अटल DEFINE_XARRAY(mte_pages);

व्योम *mte_allocate_tag_storage(व्योम)
अणु
	/* tags granule is 16 bytes, 2 tags stored per byte */
	वापस kदो_स्मृति(PAGE_SIZE / 16 / 2, GFP_KERNEL);
पूर्ण

व्योम mte_मुक्त_tag_storage(अक्षर *storage)
अणु
	kमुक्त(storage);
पूर्ण

पूर्णांक mte_save_tags(काष्ठा page *page)
अणु
	व्योम *tag_storage, *ret;

	अगर (!test_bit(PG_mte_tagged, &page->flags))
		वापस 0;

	tag_storage = mte_allocate_tag_storage();
	अगर (!tag_storage)
		वापस -ENOMEM;

	mte_save_page_tags(page_address(page), tag_storage);

	/* page_निजी contains the swap entry.val set in करो_swap_page */
	ret = xa_store(&mte_pages, page_निजी(page), tag_storage, GFP_KERNEL);
	अगर (WARN(xa_is_err(ret), "Failed to store MTE tags")) अणु
		mte_मुक्त_tag_storage(tag_storage);
		वापस xa_err(ret);
	पूर्ण अन्यथा अगर (ret) अणु
		/* Entry is being replaced, मुक्त the old entry */
		mte_मुक्त_tag_storage(ret);
	पूर्ण

	वापस 0;
पूर्ण

bool mte_restore_tags(swp_entry_t entry, काष्ठा page *page)
अणु
	व्योम *tags = xa_load(&mte_pages, entry.val);

	अगर (!tags)
		वापस false;

	page_kasan_tag_reset(page);
	/*
	 * We need smp_wmb() in between setting the flags and clearing the
	 * tags because अगर another thपढ़ो पढ़ोs page->flags and builds a
	 * tagged address out of it, there is an actual dependency to the
	 * memory access, but on the current thपढ़ो we करो not guarantee that
	 * the new page->flags are visible beक्रमe the tags were updated.
	 */
	smp_wmb();
	mte_restore_page_tags(page_address(page), tags);

	वापस true;
पूर्ण

व्योम mte_invalidate_tags(पूर्णांक type, pgoff_t offset)
अणु
	swp_entry_t entry = swp_entry(type, offset);
	व्योम *tags = xa_erase(&mte_pages, entry.val);

	mte_मुक्त_tag_storage(tags);
पूर्ण

व्योम mte_invalidate_tags_area(पूर्णांक type)
अणु
	swp_entry_t entry = swp_entry(type, 0);
	swp_entry_t last_entry = swp_entry(type + 1, 0);
	व्योम *tags;

	XA_STATE(xa_state, &mte_pages, entry.val);

	xa_lock(&mte_pages);
	xas_क्रम_each(&xa_state, tags, last_entry.val - 1) अणु
		__xa_erase(&mte_pages, xa_state.xa_index);
		mte_मुक्त_tag_storage(tags);
	पूर्ण
	xa_unlock(&mte_pages);
पूर्ण
