<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Copyright (c) by Takashi Iwai <tiwai@suse.de>
 *
 *  EMU10K1 memory page allocation (PTB area)
 */

#समावेश <linux/pci.h>
#समावेश <linux/gfp.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>

#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>

/* page arguments of these two macros are Emu page (4096 bytes), not like
 * aligned pages in others
 */
#घोषणा __set_ptb_entry(emu,page,addr) \
	(((__le32 *)(emu)->ptb_pages.area)[page] = \
	 cpu_to_le32(((addr) << (emu->address_mode)) | (page)))
#घोषणा __get_ptb_entry(emu, page) \
	(le32_to_cpu(((__le32 *)(emu)->ptb_pages.area)[page]))

#घोषणा UNIT_PAGES		(PAGE_SIZE / EMUPAGESIZE)
#घोषणा MAX_ALIGN_PAGES0		(MAXPAGES0 / UNIT_PAGES)
#घोषणा MAX_ALIGN_PAGES1		(MAXPAGES1 / UNIT_PAGES)
/* get aligned page from offset address */
#घोषणा get_aligned_page(offset)	((offset) >> PAGE_SHIFT)
/* get offset address from aligned page */
#घोषणा aligned_page_offset(page)	((page) << PAGE_SHIFT)

#अगर PAGE_SIZE == EMUPAGESIZE && !IS_ENABLED(CONFIG_DYNAMIC_DEBUG)
/* fill PTB entrie(s) corresponding to page with addr */
#घोषणा set_ptb_entry(emu,page,addr)	__set_ptb_entry(emu,page,addr)
/* fill PTB entrie(s) corresponding to page with silence poपूर्णांकer */
#घोषणा set_silent_ptb(emu,page)	__set_ptb_entry(emu,page,emu->silent_page.addr)
#अन्यथा
/* fill PTB entries -- we need to fill UNIT_PAGES entries */
अटल अंतरभूत व्योम set_ptb_entry(काष्ठा snd_emu10k1 *emu, पूर्णांक page, dma_addr_t addr)
अणु
	पूर्णांक i;
	page *= UNIT_PAGES;
	क्रम (i = 0; i < UNIT_PAGES; i++, page++) अणु
		__set_ptb_entry(emu, page, addr);
		dev_dbg(emu->card->dev, "mapped page %d to entry %.8x\n", page,
			(अचिन्हित पूर्णांक)__get_ptb_entry(emu, page));
		addr += EMUPAGESIZE;
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम set_silent_ptb(काष्ठा snd_emu10k1 *emu, पूर्णांक page)
अणु
	पूर्णांक i;
	page *= UNIT_PAGES;
	क्रम (i = 0; i < UNIT_PAGES; i++, page++) अणु
		/* करो not increment ptr */
		__set_ptb_entry(emu, page, emu->silent_page.addr);
		dev_dbg(emu->card->dev, "mapped silent page %d to entry %.8x\n",
			page, (अचिन्हित पूर्णांक)__get_ptb_entry(emu, page));
	पूर्ण
पूर्ण
#पूर्ण_अगर /* PAGE_SIZE */


/*
 */
अटल पूर्णांक synth_alloc_pages(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emu10k1_memblk *blk);
अटल पूर्णांक synth_मुक्त_pages(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emu10k1_memblk *blk);

#घोषणा get_emu10k1_memblk(l,member)	list_entry(l, काष्ठा snd_emu10k1_memblk, member)


/* initialize emu10k1 part */
अटल व्योम emu10k1_memblk_init(काष्ठा snd_emu10k1_memblk *blk)
अणु
	blk->mapped_page = -1;
	INIT_LIST_HEAD(&blk->mapped_link);
	INIT_LIST_HEAD(&blk->mapped_order_link);
	blk->map_locked = 0;

	blk->first_page = get_aligned_page(blk->mem.offset);
	blk->last_page = get_aligned_page(blk->mem.offset + blk->mem.size - 1);
	blk->pages = blk->last_page - blk->first_page + 1;
पूर्ण

/*
 * search empty region on PTB with the given size
 *
 * अगर an empty region is found, वापस the page and store the next mapped block
 * in nextp
 * अगर not found, वापस a negative error code.
 */
अटल पूर्णांक search_empty_map_area(काष्ठा snd_emu10k1 *emu, पूर्णांक npages, काष्ठा list_head **nextp)
अणु
	पूर्णांक page = 1, found_page = -ENOMEM;
	पूर्णांक max_size = npages;
	पूर्णांक size;
	काष्ठा list_head *candidate = &emu->mapped_link_head;
	काष्ठा list_head *pos;

	list_क्रम_each (pos, &emu->mapped_link_head) अणु
		काष्ठा snd_emu10k1_memblk *blk = get_emu10k1_memblk(pos, mapped_link);
		अगर (blk->mapped_page < 0)
			जारी;
		size = blk->mapped_page - page;
		अगर (size == npages) अणु
			*nextp = pos;
			वापस page;
		पूर्ण
		अन्यथा अगर (size > max_size) अणु
			/* we look क्रम the maximum empty hole */
			max_size = size;
			candidate = pos;
			found_page = page;
		पूर्ण
		page = blk->mapped_page + blk->pages;
	पूर्ण
	size = (emu->address_mode ? MAX_ALIGN_PAGES1 : MAX_ALIGN_PAGES0) - page;
	अगर (size >= max_size) अणु
		*nextp = pos;
		वापस page;
	पूर्ण
	*nextp = candidate;
	वापस found_page;
पूर्ण

/*
 * map a memory block onto emu10k1's PTB
 *
 * call with memblk_lock held
 */
अटल पूर्णांक map_memblk(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_memblk *blk)
अणु
	पूर्णांक page, pg;
	काष्ठा list_head *next;

	page = search_empty_map_area(emu, blk->pages, &next);
	अगर (page < 0) /* not found */
		वापस page;
	अगर (page == 0) अणु
		dev_err(emu->card->dev, "trying to map zero (reserved) page\n");
		वापस -EINVAL;
	पूर्ण
	/* insert this block in the proper position of mapped list */
	list_add_tail(&blk->mapped_link, next);
	/* append this as a newest block in order list */
	list_add_tail(&blk->mapped_order_link, &emu->mapped_order_link_head);
	blk->mapped_page = page;
	/* fill PTB */
	क्रम (pg = blk->first_page; pg <= blk->last_page; pg++) अणु
		set_ptb_entry(emu, page, emu->page_addr_table[pg]);
		page++;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * unmap the block
 * वापस the size of resultant empty pages
 *
 * call with memblk_lock held
 */
अटल पूर्णांक unmap_memblk(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_memblk *blk)
अणु
	पूर्णांक start_page, end_page, mpage, pg;
	काष्ठा list_head *p;
	काष्ठा snd_emu10k1_memblk *q;

	/* calculate the expected size of empty region */
	अगर ((p = blk->mapped_link.prev) != &emu->mapped_link_head) अणु
		q = get_emu10k1_memblk(p, mapped_link);
		start_page = q->mapped_page + q->pages;
	पूर्ण अन्यथा
		start_page = 1;
	अगर ((p = blk->mapped_link.next) != &emu->mapped_link_head) अणु
		q = get_emu10k1_memblk(p, mapped_link);
		end_page = q->mapped_page;
	पूर्ण अन्यथा
		end_page = (emu->address_mode ? MAX_ALIGN_PAGES1 : MAX_ALIGN_PAGES0);

	/* हटाओ links */
	list_del(&blk->mapped_link);
	list_del(&blk->mapped_order_link);
	/* clear PTB */
	mpage = blk->mapped_page;
	क्रम (pg = blk->first_page; pg <= blk->last_page; pg++) अणु
		set_silent_ptb(emu, mpage);
		mpage++;
	पूर्ण
	blk->mapped_page = -1;
	वापस end_page - start_page; /* वापस the new empty size */
पूर्ण

/*
 * search empty pages with the given size, and create a memory block
 *
 * unlike synth_alloc the memory block is aligned to the page start
 */
अटल काष्ठा snd_emu10k1_memblk *
search_empty(काष्ठा snd_emu10k1 *emu, पूर्णांक size)
अणु
	काष्ठा list_head *p;
	काष्ठा snd_emu10k1_memblk *blk;
	पूर्णांक page, psize;

	psize = get_aligned_page(size + PAGE_SIZE -1);
	page = 0;
	list_क्रम_each(p, &emu->memhdr->block) अणु
		blk = get_emu10k1_memblk(p, mem.list);
		अगर (page + psize <= blk->first_page)
			जाओ __found_pages;
		page = blk->last_page + 1;
	पूर्ण
	अगर (page + psize > emu->max_cache_pages)
		वापस शून्य;

__found_pages:
	/* create a new memory block */
	blk = (काष्ठा snd_emu10k1_memblk *)__snd_util_memblk_new(emu->memhdr, psize << PAGE_SHIFT, p->prev);
	अगर (blk == शून्य)
		वापस शून्य;
	blk->mem.offset = aligned_page_offset(page); /* set aligned offset */
	emu10k1_memblk_init(blk);
	वापस blk;
पूर्ण


/*
 * check अगर the given poपूर्णांकer is valid क्रम pages
 */
अटल पूर्णांक is_valid_page(काष्ठा snd_emu10k1 *emu, dma_addr_t addr)
अणु
	अगर (addr & ~emu->dma_mask) अणु
		dev_err_ratelimited(emu->card->dev,
			"max memory size is 0x%lx (addr = 0x%lx)!!\n",
			emu->dma_mask, (अचिन्हित दीर्घ)addr);
		वापस 0;
	पूर्ण
	अगर (addr & (EMUPAGESIZE-1)) अणु
		dev_err_ratelimited(emu->card->dev, "page is not aligned\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * map the given memory block on PTB.
 * अगर the block is alपढ़ोy mapped, update the link order.
 * अगर no empty pages are found, tries to release unused memory blocks
 * and retry the mapping.
 */
पूर्णांक snd_emu10k1_memblk_map(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_memblk *blk)
अणु
	पूर्णांक err;
	पूर्णांक size;
	काष्ठा list_head *p, *nextp;
	काष्ठा snd_emu10k1_memblk *deleted;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->memblk_lock, flags);
	अगर (blk->mapped_page >= 0) अणु
		/* update order link */
		list_move_tail(&blk->mapped_order_link,
			       &emu->mapped_order_link_head);
		spin_unlock_irqrestore(&emu->memblk_lock, flags);
		वापस 0;
	पूर्ण
	अगर ((err = map_memblk(emu, blk)) < 0) अणु
		/* no enough page - try to unmap some blocks */
		/* starting from the oldest block */
		p = emu->mapped_order_link_head.next;
		क्रम (; p != &emu->mapped_order_link_head; p = nextp) अणु
			nextp = p->next;
			deleted = get_emu10k1_memblk(p, mapped_order_link);
			अगर (deleted->map_locked)
				जारी;
			size = unmap_memblk(emu, deleted);
			अगर (size >= blk->pages) अणु
				/* ok the empty region is enough large */
				err = map_memblk(emu, blk);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->memblk_lock, flags);
	वापस err;
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_memblk_map);

/*
 * page allocation क्रम DMA
 */
काष्ठा snd_util_memblk *
snd_emu10k1_alloc_pages(काष्ठा snd_emu10k1 *emu, काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_util_memhdr *hdr;
	काष्ठा snd_emu10k1_memblk *blk;
	पूर्णांक page, err, idx;

	अगर (snd_BUG_ON(!emu))
		वापस शून्य;
	अगर (snd_BUG_ON(runसमय->dma_bytes <= 0 ||
		       runसमय->dma_bytes >= (emu->address_mode ? MAXPAGES1 : MAXPAGES0) * EMUPAGESIZE))
		वापस शून्य;
	hdr = emu->memhdr;
	अगर (snd_BUG_ON(!hdr))
		वापस शून्य;

	idx = runसमय->period_size >= runसमय->buffer_size ?
					(emu->delay_pcm_irq * 2) : 0;
	mutex_lock(&hdr->block_mutex);
	blk = search_empty(emu, runसमय->dma_bytes + idx);
	अगर (blk == शून्य) अणु
		mutex_unlock(&hdr->block_mutex);
		वापस शून्य;
	पूर्ण
	/* fill buffer addresses but poपूर्णांकers are not stored so that
	 * snd_मुक्त_pci_page() is not called in in synth_मुक्त()
	 */
	idx = 0;
	क्रम (page = blk->first_page; page <= blk->last_page; page++, idx++) अणु
		अचिन्हित दीर्घ ofs = idx << PAGE_SHIFT;
		dma_addr_t addr;
		अगर (ofs >= runसमय->dma_bytes)
			addr = emu->silent_page.addr;
		अन्यथा
			addr = snd_pcm_sgbuf_get_addr(substream, ofs);
		अगर (! is_valid_page(emu, addr)) अणु
			dev_err_ratelimited(emu->card->dev,
				"emu: failure page = %d\n", idx);
			mutex_unlock(&hdr->block_mutex);
			वापस शून्य;
		पूर्ण
		emu->page_addr_table[page] = addr;
		emu->page_ptr_table[page] = शून्य;
	पूर्ण

	/* set PTB entries */
	blk->map_locked = 1; /* करो not unmap this block! */
	err = snd_emu10k1_memblk_map(emu, blk);
	अगर (err < 0) अणु
		__snd_util_mem_मुक्त(hdr, (काष्ठा snd_util_memblk *)blk);
		mutex_unlock(&hdr->block_mutex);
		वापस शून्य;
	पूर्ण
	mutex_unlock(&hdr->block_mutex);
	वापस (काष्ठा snd_util_memblk *)blk;
पूर्ण


/*
 * release DMA buffer from page table
 */
पूर्णांक snd_emu10k1_मुक्त_pages(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *blk)
अणु
	अगर (snd_BUG_ON(!emu || !blk))
		वापस -EINVAL;
	वापस snd_emu10k1_synth_मुक्त(emu, blk);
पूर्ण

/*
 * allocate DMA pages, widening the allocation अगर necessary
 *
 * See the comment above snd_emu10k1_detect_iommu() in emu10k1_मुख्य.c why
 * this might be needed.
 *
 * If you modअगरy this function check whether __synth_मुक्त_pages() also needs
 * changes.
 */
पूर्णांक snd_emu10k1_alloc_pages_maybe_wider(काष्ठा snd_emu10k1 *emu, माप_प्रकार size,
					काष्ठा snd_dma_buffer *dmab)
अणु
	अगर (emu->iommu_workaround) अणु
		माप_प्रकार npages = DIV_ROUND_UP(size, PAGE_SIZE);
		माप_प्रकार size_real = npages * PAGE_SIZE;

		/*
		 * The device has been observed to accesses up to 256 extra
		 * bytes, but use 1k to be safe.
		 */
		अगर (size_real < size + 1024)
			size += PAGE_SIZE;
	पूर्ण

	वापस snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
				   &emu->pci->dev, size, dmab);
पूर्ण

/*
 * memory allocation using multiple pages (क्रम synth)
 * Unlike the DMA allocation above, non-contiguous pages are assined.
 */

/*
 * allocate a synth sample area
 */
काष्ठा snd_util_memblk *
snd_emu10k1_synth_alloc(काष्ठा snd_emu10k1 *hw, अचिन्हित पूर्णांक size)
अणु
	काष्ठा snd_emu10k1_memblk *blk;
	काष्ठा snd_util_memhdr *hdr = hw->memhdr; 

	mutex_lock(&hdr->block_mutex);
	blk = (काष्ठा snd_emu10k1_memblk *)__snd_util_mem_alloc(hdr, size);
	अगर (blk == शून्य) अणु
		mutex_unlock(&hdr->block_mutex);
		वापस शून्य;
	पूर्ण
	अगर (synth_alloc_pages(hw, blk)) अणु
		__snd_util_mem_मुक्त(hdr, (काष्ठा snd_util_memblk *)blk);
		mutex_unlock(&hdr->block_mutex);
		वापस शून्य;
	पूर्ण
	snd_emu10k1_memblk_map(hw, blk);
	mutex_unlock(&hdr->block_mutex);
	वापस (काष्ठा snd_util_memblk *)blk;
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_synth_alloc);

/*
 * मुक्त a synth sample area
 */
पूर्णांक
snd_emu10k1_synth_मुक्त(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *memblk)
अणु
	काष्ठा snd_util_memhdr *hdr = emu->memhdr; 
	काष्ठा snd_emu10k1_memblk *blk = (काष्ठा snd_emu10k1_memblk *)memblk;
	अचिन्हित दीर्घ flags;

	mutex_lock(&hdr->block_mutex);
	spin_lock_irqsave(&emu->memblk_lock, flags);
	अगर (blk->mapped_page >= 0)
		unmap_memblk(emu, blk);
	spin_unlock_irqrestore(&emu->memblk_lock, flags);
	synth_मुक्त_pages(emu, blk);
	 __snd_util_mem_मुक्त(hdr, memblk);
	mutex_unlock(&hdr->block_mutex);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_synth_मुक्त);

/* check new allocation range */
अटल व्योम get_single_page_range(काष्ठा snd_util_memhdr *hdr,
				  काष्ठा snd_emu10k1_memblk *blk,
				  पूर्णांक *first_page_ret, पूर्णांक *last_page_ret)
अणु
	काष्ठा list_head *p;
	काष्ठा snd_emu10k1_memblk *q;
	पूर्णांक first_page, last_page;
	first_page = blk->first_page;
	अगर ((p = blk->mem.list.prev) != &hdr->block) अणु
		q = get_emu10k1_memblk(p, mem.list);
		अगर (q->last_page == first_page)
			first_page++;  /* first page was alपढ़ोy allocated */
	पूर्ण
	last_page = blk->last_page;
	अगर ((p = blk->mem.list.next) != &hdr->block) अणु
		q = get_emu10k1_memblk(p, mem.list);
		अगर (q->first_page == last_page)
			last_page--; /* last page was alपढ़ोy allocated */
	पूर्ण
	*first_page_ret = first_page;
	*last_page_ret = last_page;
पूर्ण

/* release allocated pages */
अटल व्योम __synth_मुक्त_pages(काष्ठा snd_emu10k1 *emu, पूर्णांक first_page,
			       पूर्णांक last_page)
अणु
	काष्ठा snd_dma_buffer dmab;
	पूर्णांक page;

	dmab.dev.type = SNDRV_DMA_TYPE_DEV;
	dmab.dev.dev = &emu->pci->dev;

	क्रम (page = first_page; page <= last_page; page++) अणु
		अगर (emu->page_ptr_table[page] == शून्य)
			जारी;
		dmab.area = emu->page_ptr_table[page];
		dmab.addr = emu->page_addr_table[page];

		/*
		 * please keep me in sync with logic in
		 * snd_emu10k1_alloc_pages_maybe_wider()
		 */
		dmab.bytes = PAGE_SIZE;
		अगर (emu->iommu_workaround)
			dmab.bytes *= 2;

		snd_dma_मुक्त_pages(&dmab);
		emu->page_addr_table[page] = 0;
		emu->page_ptr_table[page] = शून्य;
	पूर्ण
पूर्ण

/*
 * allocate kernel pages
 */
अटल पूर्णांक synth_alloc_pages(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_memblk *blk)
अणु
	पूर्णांक page, first_page, last_page;
	काष्ठा snd_dma_buffer dmab;

	emu10k1_memblk_init(blk);
	get_single_page_range(emu->memhdr, blk, &first_page, &last_page);
	/* allocate kernel pages */
	क्रम (page = first_page; page <= last_page; page++) अणु
		अगर (snd_emu10k1_alloc_pages_maybe_wider(emu, PAGE_SIZE,
							&dmab) < 0)
			जाओ __fail;
		अगर (!is_valid_page(emu, dmab.addr)) अणु
			snd_dma_मुक्त_pages(&dmab);
			जाओ __fail;
		पूर्ण
		emu->page_addr_table[page] = dmab.addr;
		emu->page_ptr_table[page] = dmab.area;
	पूर्ण
	वापस 0;

__fail:
	/* release allocated pages */
	last_page = page - 1;
	__synth_मुक्त_pages(emu, first_page, last_page);

	वापस -ENOMEM;
पूर्ण

/*
 * मुक्त pages
 */
अटल पूर्णांक synth_मुक्त_pages(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_memblk *blk)
अणु
	पूर्णांक first_page, last_page;

	get_single_page_range(emu->memhdr, blk, &first_page, &last_page);
	__synth_मुक्त_pages(emu, first_page, last_page);
	वापस 0;
पूर्ण

/* calculate buffer poपूर्णांकer from offset address */
अटल अंतरभूत व्योम *offset_ptr(काष्ठा snd_emu10k1 *emu, पूर्णांक page, पूर्णांक offset)
अणु
	अक्षर *ptr;
	अगर (snd_BUG_ON(page < 0 || page >= emu->max_cache_pages))
		वापस शून्य;
	ptr = emu->page_ptr_table[page];
	अगर (! ptr) अणु
		dev_err(emu->card->dev,
			"access to NULL ptr: page = %d\n", page);
		वापस शून्य;
	पूर्ण
	ptr += offset & (PAGE_SIZE - 1);
	वापस (व्योम*)ptr;
पूर्ण

/*
 * bzero(blk + offset, size)
 */
पूर्णांक snd_emu10k1_synth_bzero(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *blk,
			    पूर्णांक offset, पूर्णांक size)
अणु
	पूर्णांक page, nextofs, end_offset, temp, temp1;
	व्योम *ptr;
	काष्ठा snd_emu10k1_memblk *p = (काष्ठा snd_emu10k1_memblk *)blk;

	offset += blk->offset & (PAGE_SIZE - 1);
	end_offset = offset + size;
	page = get_aligned_page(offset);
	करो अणु
		nextofs = aligned_page_offset(page + 1);
		temp = nextofs - offset;
		temp1 = end_offset - offset;
		अगर (temp1 < temp)
			temp = temp1;
		ptr = offset_ptr(emu, page + p->first_page, offset);
		अगर (ptr)
			स_रखो(ptr, 0, temp);
		offset = nextofs;
		page++;
	पूर्ण जबतक (offset < end_offset);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_synth_bzero);

/*
 * copy_from_user(blk + offset, data, size)
 */
पूर्णांक snd_emu10k1_synth_copy_from_user(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *blk,
				     पूर्णांक offset, स्थिर अक्षर __user *data, पूर्णांक size)
अणु
	पूर्णांक page, nextofs, end_offset, temp, temp1;
	व्योम *ptr;
	काष्ठा snd_emu10k1_memblk *p = (काष्ठा snd_emu10k1_memblk *)blk;

	offset += blk->offset & (PAGE_SIZE - 1);
	end_offset = offset + size;
	page = get_aligned_page(offset);
	करो अणु
		nextofs = aligned_page_offset(page + 1);
		temp = nextofs - offset;
		temp1 = end_offset - offset;
		अगर (temp1 < temp)
			temp = temp1;
		ptr = offset_ptr(emu, page + p->first_page, offset);
		अगर (ptr && copy_from_user(ptr, data, temp))
			वापस -EFAULT;
		offset = nextofs;
		data += temp;
		page++;
	पूर्ण जबतक (offset < end_offset);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_emu10k1_synth_copy_from_user);
