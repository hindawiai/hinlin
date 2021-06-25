<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Copyright (c) by Takashi Iwai <tiwai@suse.de>
 *  Copyright (c) by Scott McNab <sdm@fractalgraphics.com.au>
 *
 *  Trident 4DWave-NX memory page allocation (TLB area)
 *  Trident chip can handle only 16MByte of the memory at the same समय.
 */

#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/समय.स>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश "trident.h"

/* page arguments of these two macros are Trident page (4096 bytes), not like
 * aligned pages in others
 */
#घोषणा __set_tlb_bus(trident,page,ptr,addr) \
	करो अणु (trident)->tlb.entries[page] = cpu_to_le32((addr) & ~(SNDRV_TRIDENT_PAGE_SIZE-1)); \
	     (trident)->tlb.shaकरोw_entries[page] = (ptr); पूर्ण जबतक (0)
#घोषणा __tlb_to_ptr(trident,page) \
	(व्योम*)((trident)->tlb.shaकरोw_entries[page])
#घोषणा __tlb_to_addr(trident,page) \
	(dma_addr_t)le32_to_cpu((trident->tlb.entries[page]) & ~(SNDRV_TRIDENT_PAGE_SIZE - 1))

#अगर PAGE_SIZE == 4096
/* page size == SNDRV_TRIDENT_PAGE_SIZE */
#घोषणा ALIGN_PAGE_SIZE		PAGE_SIZE	/* minimum page size क्रम allocation */
#घोषणा MAX_ALIGN_PAGES		SNDRV_TRIDENT_MAX_PAGES	/* maxmium aligned pages */
/* fill TLB entrie(s) corresponding to page with ptr */
#घोषणा set_tlb_bus(trident,page,ptr,addr) __set_tlb_bus(trident,page,ptr,addr)
/* fill TLB entrie(s) corresponding to page with silence poपूर्णांकer */
#घोषणा set_silent_tlb(trident,page)	__set_tlb_bus(trident, page, (अचिन्हित दीर्घ)trident->tlb.silent_page.area, trident->tlb.silent_page.addr)
/* get aligned page from offset address */
#घोषणा get_aligned_page(offset)	((offset) >> 12)
/* get offset address from aligned page */
#घोषणा aligned_page_offset(page)	((page) << 12)
/* get buffer address from aligned page */
#घोषणा page_to_ptr(trident,page)	__tlb_to_ptr(trident, page)
/* get PCI physical address from aligned page */
#घोषणा page_to_addr(trident,page)	__tlb_to_addr(trident, page)

#या_अगर PAGE_SIZE == 8192
/* page size == SNDRV_TRIDENT_PAGE_SIZE x 2*/
#घोषणा ALIGN_PAGE_SIZE		PAGE_SIZE
#घोषणा MAX_ALIGN_PAGES		(SNDRV_TRIDENT_MAX_PAGES / 2)
#घोषणा get_aligned_page(offset)	((offset) >> 13)
#घोषणा aligned_page_offset(page)	((page) << 13)
#घोषणा page_to_ptr(trident,page)	__tlb_to_ptr(trident, (page) << 1)
#घोषणा page_to_addr(trident,page)	__tlb_to_addr(trident, (page) << 1)

/* fill TLB entries -- we need to fill two entries */
अटल अंतरभूत व्योम set_tlb_bus(काष्ठा snd_trident *trident, पूर्णांक page,
			       अचिन्हित दीर्घ ptr, dma_addr_t addr)
अणु
	page <<= 1;
	__set_tlb_bus(trident, page, ptr, addr);
	__set_tlb_bus(trident, page+1, ptr + SNDRV_TRIDENT_PAGE_SIZE, addr + SNDRV_TRIDENT_PAGE_SIZE);
पूर्ण
अटल अंतरभूत व्योम set_silent_tlb(काष्ठा snd_trident *trident, पूर्णांक page)
अणु
	page <<= 1;
	__set_tlb_bus(trident, page, (अचिन्हित दीर्घ)trident->tlb.silent_page.area, trident->tlb.silent_page.addr);
	__set_tlb_bus(trident, page+1, (अचिन्हित दीर्घ)trident->tlb.silent_page.area, trident->tlb.silent_page.addr);
पूर्ण

#अन्यथा
/* arbitrary size */
#घोषणा UNIT_PAGES		(PAGE_SIZE / SNDRV_TRIDENT_PAGE_SIZE)
#घोषणा ALIGN_PAGE_SIZE		(SNDRV_TRIDENT_PAGE_SIZE * UNIT_PAGES)
#घोषणा MAX_ALIGN_PAGES		(SNDRV_TRIDENT_MAX_PAGES / UNIT_PAGES)
/* Note: अगर alignment करोesn't match to the maximum size, the last few blocks
 * become unusable.  To use such blocks, you'll need to check the validity
 * of accessing page in set_tlb_bus and set_silent_tlb.  search_empty()
 * should also check it, too.
 */
#घोषणा get_aligned_page(offset)	((offset) / ALIGN_PAGE_SIZE)
#घोषणा aligned_page_offset(page)	((page) * ALIGN_PAGE_SIZE)
#घोषणा page_to_ptr(trident,page)	__tlb_to_ptr(trident, (page) * UNIT_PAGES)
#घोषणा page_to_addr(trident,page)	__tlb_to_addr(trident, (page) * UNIT_PAGES)

/* fill TLB entries -- UNIT_PAGES entries must be filled */
अटल अंतरभूत व्योम set_tlb_bus(काष्ठा snd_trident *trident, पूर्णांक page,
			       अचिन्हित दीर्घ ptr, dma_addr_t addr)
अणु
	पूर्णांक i;
	page *= UNIT_PAGES;
	क्रम (i = 0; i < UNIT_PAGES; i++, page++) अणु
		__set_tlb_bus(trident, page, ptr, addr);
		ptr += SNDRV_TRIDENT_PAGE_SIZE;
		addr += SNDRV_TRIDENT_PAGE_SIZE;
	पूर्ण
पूर्ण
अटल अंतरभूत व्योम set_silent_tlb(काष्ठा snd_trident *trident, पूर्णांक page)
अणु
	पूर्णांक i;
	page *= UNIT_PAGES;
	क्रम (i = 0; i < UNIT_PAGES; i++, page++)
		__set_tlb_bus(trident, page, (अचिन्हित दीर्घ)trident->tlb.silent_page.area, trident->tlb.silent_page.addr);
पूर्ण

#पूर्ण_अगर /* PAGE_SIZE */

/* calculate buffer poपूर्णांकer from offset address */
अटल अंतरभूत व्योम *offset_ptr(काष्ठा snd_trident *trident, पूर्णांक offset)
अणु
	अक्षर *ptr;
	ptr = page_to_ptr(trident, get_aligned_page(offset));
	ptr += offset % ALIGN_PAGE_SIZE;
	वापस (व्योम*)ptr;
पूर्ण

/* first and last (aligned) pages of memory block */
#घोषणा firstpg(blk)	(((काष्ठा snd_trident_memblk_arg *)snd_util_memblk_argptr(blk))->first_page)
#घोषणा lastpg(blk)	(((काष्ठा snd_trident_memblk_arg *)snd_util_memblk_argptr(blk))->last_page)

/*
 * search empty pages which may contain given size
 */
अटल काष्ठा snd_util_memblk *
search_empty(काष्ठा snd_util_memhdr *hdr, पूर्णांक size)
अणु
	काष्ठा snd_util_memblk *blk;
	पूर्णांक page, psize;
	काष्ठा list_head *p;

	psize = get_aligned_page(size + ALIGN_PAGE_SIZE -1);
	page = 0;
	list_क्रम_each(p, &hdr->block) अणु
		blk = list_entry(p, काष्ठा snd_util_memblk, list);
		अगर (page + psize <= firstpg(blk))
			जाओ __found_pages;
		page = lastpg(blk) + 1;
	पूर्ण
	अगर (page + psize > MAX_ALIGN_PAGES)
		वापस शून्य;

__found_pages:
	/* create a new memory block */
	blk = __snd_util_memblk_new(hdr, psize * ALIGN_PAGE_SIZE, p->prev);
	अगर (blk == शून्य)
		वापस शून्य;
	blk->offset = aligned_page_offset(page); /* set aligned offset */
	firstpg(blk) = page;
	lastpg(blk) = page + psize - 1;
	वापस blk;
पूर्ण


/*
 * check अगर the given poपूर्णांकer is valid क्रम pages
 */
अटल पूर्णांक is_valid_page(अचिन्हित दीर्घ ptr)
अणु
	अगर (ptr & ~0x3fffffffUL) अणु
		snd_prपूर्णांकk(KERN_ERR "max memory size is 1GB!!\n");
		वापस 0;
	पूर्ण
	अगर (ptr & (SNDRV_TRIDENT_PAGE_SIZE-1)) अणु
		snd_prपूर्णांकk(KERN_ERR "page is not aligned\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * page allocation क्रम DMA (Scatter-Gather version)
 */
अटल काष्ठा snd_util_memblk *
snd_trident_alloc_sg_pages(काष्ठा snd_trident *trident,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_util_memhdr *hdr;
	काष्ठा snd_util_memblk *blk;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक idx, page;

	अगर (snd_BUG_ON(runसमय->dma_bytes <= 0 ||
		       runसमय->dma_bytes > SNDRV_TRIDENT_MAX_PAGES *
					SNDRV_TRIDENT_PAGE_SIZE))
		वापस शून्य;
	hdr = trident->tlb.memhdr;
	अगर (snd_BUG_ON(!hdr))
		वापस शून्य;

	

	mutex_lock(&hdr->block_mutex);
	blk = search_empty(hdr, runसमय->dma_bytes);
	अगर (blk == शून्य) अणु
		mutex_unlock(&hdr->block_mutex);
		वापस शून्य;
	पूर्ण
			   
	/* set TLB entries */
	idx = 0;
	क्रम (page = firstpg(blk); page <= lastpg(blk); page++, idx++) अणु
		अचिन्हित दीर्घ ofs = idx << PAGE_SHIFT;
		dma_addr_t addr = snd_pcm_sgbuf_get_addr(substream, ofs);
		अचिन्हित दीर्घ ptr = (अचिन्हित दीर्घ)
			snd_pcm_sgbuf_get_ptr(substream, ofs);
		अगर (! is_valid_page(addr)) अणु
			__snd_util_mem_मुक्त(hdr, blk);
			mutex_unlock(&hdr->block_mutex);
			वापस शून्य;
		पूर्ण
		set_tlb_bus(trident, page, ptr, addr);
	पूर्ण
	mutex_unlock(&hdr->block_mutex);
	वापस blk;
पूर्ण

/*
 * page allocation क्रम DMA (contiguous version)
 */
अटल काष्ठा snd_util_memblk *
snd_trident_alloc_cont_pages(काष्ठा snd_trident *trident,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_util_memhdr *hdr;
	काष्ठा snd_util_memblk *blk;
	पूर्णांक page;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	dma_addr_t addr;
	अचिन्हित दीर्घ ptr;

	अगर (snd_BUG_ON(runसमय->dma_bytes <= 0 ||
		       runसमय->dma_bytes > SNDRV_TRIDENT_MAX_PAGES *
					SNDRV_TRIDENT_PAGE_SIZE))
		वापस शून्य;
	hdr = trident->tlb.memhdr;
	अगर (snd_BUG_ON(!hdr))
		वापस शून्य;

	mutex_lock(&hdr->block_mutex);
	blk = search_empty(hdr, runसमय->dma_bytes);
	अगर (blk == शून्य) अणु
		mutex_unlock(&hdr->block_mutex);
		वापस शून्य;
	पूर्ण
			   
	/* set TLB entries */
	addr = runसमय->dma_addr;
	ptr = (अचिन्हित दीर्घ)runसमय->dma_area;
	क्रम (page = firstpg(blk); page <= lastpg(blk); page++,
	     ptr += SNDRV_TRIDENT_PAGE_SIZE, addr += SNDRV_TRIDENT_PAGE_SIZE) अणु
		अगर (! is_valid_page(addr)) अणु
			__snd_util_mem_मुक्त(hdr, blk);
			mutex_unlock(&hdr->block_mutex);
			वापस शून्य;
		पूर्ण
		set_tlb_bus(trident, page, ptr, addr);
	पूर्ण
	mutex_unlock(&hdr->block_mutex);
	वापस blk;
पूर्ण

/*
 * page allocation क्रम DMA
 */
काष्ठा snd_util_memblk *
snd_trident_alloc_pages(काष्ठा snd_trident *trident,
			काष्ठा snd_pcm_substream *substream)
अणु
	अगर (snd_BUG_ON(!trident || !substream))
		वापस शून्य;
	अगर (substream->dma_buffer.dev.type == SNDRV_DMA_TYPE_DEV_SG)
		वापस snd_trident_alloc_sg_pages(trident, substream);
	अन्यथा
		वापस snd_trident_alloc_cont_pages(trident, substream);
पूर्ण


/*
 * release DMA buffer from page table
 */
पूर्णांक snd_trident_मुक्त_pages(काष्ठा snd_trident *trident,
			   काष्ठा snd_util_memblk *blk)
अणु
	काष्ठा snd_util_memhdr *hdr;
	पूर्णांक page;

	अगर (snd_BUG_ON(!trident || !blk))
		वापस -EINVAL;

	hdr = trident->tlb.memhdr;
	mutex_lock(&hdr->block_mutex);
	/* reset TLB entries */
	क्रम (page = firstpg(blk); page <= lastpg(blk); page++)
		set_silent_tlb(trident, page);
	/* मुक्त memory block */
	__snd_util_mem_मुक्त(hdr, blk);
	mutex_unlock(&hdr->block_mutex);
	वापस 0;
पूर्ण
