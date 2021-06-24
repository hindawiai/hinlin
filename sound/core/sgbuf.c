<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Scatter-Gather buffer
 *
 *  Copyright (c) by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <sound/meदो_स्मृति.h>


/* table entries are align to 32 */
#घोषणा SGBUF_TBL_ALIGN		32
#घोषणा sgbuf_align_table(tbl)	ALIGN((tbl), SGBUF_TBL_ALIGN)

पूर्णांक snd_मुक्त_sgbuf_pages(काष्ठा snd_dma_buffer *dmab)
अणु
	काष्ठा snd_sg_buf *sgbuf = dmab->निजी_data;
	काष्ठा snd_dma_buffer पंचांगpb;
	पूर्णांक i;

	अगर (! sgbuf)
		वापस -EINVAL;

	vunmap(dmab->area);
	dmab->area = शून्य;

	पंचांगpb.dev.type = SNDRV_DMA_TYPE_DEV;
	अगर (dmab->dev.type == SNDRV_DMA_TYPE_DEV_UC_SG)
		पंचांगpb.dev.type = SNDRV_DMA_TYPE_DEV_UC;
	पंचांगpb.dev.dev = sgbuf->dev;
	क्रम (i = 0; i < sgbuf->pages; i++) अणु
		अगर (!(sgbuf->table[i].addr & ~PAGE_MASK))
			जारी; /* continuous pages */
		पंचांगpb.area = sgbuf->table[i].buf;
		पंचांगpb.addr = sgbuf->table[i].addr & PAGE_MASK;
		पंचांगpb.bytes = (sgbuf->table[i].addr & ~PAGE_MASK) << PAGE_SHIFT;
		snd_dma_मुक्त_pages(&पंचांगpb);
	पूर्ण

	kमुक्त(sgbuf->table);
	kमुक्त(sgbuf->page_table);
	kमुक्त(sgbuf);
	dmab->निजी_data = शून्य;
	
	वापस 0;
पूर्ण

#घोषणा MAX_ALLOC_PAGES		32

व्योम *snd_दो_स्मृति_sgbuf_pages(काष्ठा device *device,
			     माप_प्रकार size, काष्ठा snd_dma_buffer *dmab,
			     माप_प्रकार *res_size)
अणु
	काष्ठा snd_sg_buf *sgbuf;
	अचिन्हित पूर्णांक i, pages, chunk, maxpages;
	काष्ठा snd_dma_buffer पंचांगpb;
	काष्ठा snd_sg_page *table;
	काष्ठा page **pgtable;
	पूर्णांक type = SNDRV_DMA_TYPE_DEV;
	pgprot_t prot = PAGE_KERNEL;

	dmab->area = शून्य;
	dmab->addr = 0;
	dmab->निजी_data = sgbuf = kzalloc(माप(*sgbuf), GFP_KERNEL);
	अगर (! sgbuf)
		वापस शून्य;
	अगर (dmab->dev.type == SNDRV_DMA_TYPE_DEV_UC_SG) अणु
		type = SNDRV_DMA_TYPE_DEV_UC;
#अगर_घोषित pgprot_noncached
		prot = pgprot_noncached(PAGE_KERNEL);
#पूर्ण_अगर
	पूर्ण
	sgbuf->dev = device;
	pages = snd_sgbuf_aligned_pages(size);
	sgbuf->tblsize = sgbuf_align_table(pages);
	table = kसुस्मृति(sgbuf->tblsize, माप(*table), GFP_KERNEL);
	अगर (!table)
		जाओ _failed;
	sgbuf->table = table;
	pgtable = kसुस्मृति(sgbuf->tblsize, माप(*pgtable), GFP_KERNEL);
	अगर (!pgtable)
		जाओ _failed;
	sgbuf->page_table = pgtable;

	/* allocate pages */
	maxpages = MAX_ALLOC_PAGES;
	जबतक (pages > 0) अणु
		chunk = pages;
		/* करोn't be too eager to take a huge chunk */
		अगर (chunk > maxpages)
			chunk = maxpages;
		chunk <<= PAGE_SHIFT;
		अगर (snd_dma_alloc_pages_fallback(type, device,
						 chunk, &पंचांगpb) < 0) अणु
			अगर (!sgbuf->pages)
				जाओ _failed;
			अगर (!res_size)
				जाओ _failed;
			size = sgbuf->pages * PAGE_SIZE;
			अवरोध;
		पूर्ण
		chunk = पंचांगpb.bytes >> PAGE_SHIFT;
		क्रम (i = 0; i < chunk; i++) अणु
			table->buf = पंचांगpb.area;
			table->addr = पंचांगpb.addr;
			अगर (!i)
				table->addr |= chunk; /* mark head */
			table++;
			*pgtable++ = virt_to_page(पंचांगpb.area);
			पंचांगpb.area += PAGE_SIZE;
			पंचांगpb.addr += PAGE_SIZE;
		पूर्ण
		sgbuf->pages += chunk;
		pages -= chunk;
		अगर (chunk < maxpages)
			maxpages = chunk;
	पूर्ण

	sgbuf->size = size;
	dmab->area = vmap(sgbuf->page_table, sgbuf->pages, VM_MAP, prot);
	अगर (! dmab->area)
		जाओ _failed;
	अगर (res_size)
		*res_size = sgbuf->size;
	वापस dmab->area;

 _failed:
	snd_मुक्त_sgbuf_pages(dmab); /* मुक्त the table */
	वापस शून्य;
पूर्ण

/*
 * compute the max chunk size with continuous pages on sg-buffer
 */
अचिन्हित पूर्णांक snd_sgbuf_get_chunk_size(काष्ठा snd_dma_buffer *dmab,
				      अचिन्हित पूर्णांक ofs, अचिन्हित पूर्णांक size)
अणु
	काष्ठा snd_sg_buf *sg = dmab->निजी_data;
	अचिन्हित पूर्णांक start, end, pg;

	अगर (!sg)
		वापस size;

	start = ofs >> PAGE_SHIFT;
	end = (ofs + size - 1) >> PAGE_SHIFT;
	/* check page continuity */
	pg = sg->table[start].addr >> PAGE_SHIFT;
	क्रम (;;) अणु
		start++;
		अगर (start > end)
			अवरोध;
		pg++;
		अगर ((sg->table[start].addr >> PAGE_SHIFT) != pg)
			वापस (start << PAGE_SHIFT) - ofs;
	पूर्ण
	/* ok, all on continuous pages */
	वापस size;
पूर्ण
EXPORT_SYMBOL(snd_sgbuf_get_chunk_size);
