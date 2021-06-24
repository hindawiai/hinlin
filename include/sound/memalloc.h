<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Takashi Iwai <tiwai@suse.de>
 * 
 *  Generic memory allocators
 */

#अगर_अघोषित __SOUND_MEMALLOC_H
#घोषणा __SOUND_MEMALLOC_H

#समावेश <यंत्र/page.h>

काष्ठा device;

/*
 * buffer device info
 */
काष्ठा snd_dma_device अणु
	पूर्णांक type;			/* SNDRV_DMA_TYPE_XXX */
	काष्ठा device *dev;		/* generic device */
पूर्ण;

#घोषणा snd_dma_continuous_data(x)	((काष्ठा device *)(__क्रमce अचिन्हित दीर्घ)(x))


/*
 * buffer types
 */
#घोषणा SNDRV_DMA_TYPE_UNKNOWN		0	/* not defined */
#घोषणा SNDRV_DMA_TYPE_CONTINUOUS	1	/* continuous no-DMA memory */
#घोषणा SNDRV_DMA_TYPE_DEV		2	/* generic device continuous */
#घोषणा SNDRV_DMA_TYPE_DEV_UC		5	/* continuous non-cahced */
#अगर_घोषित CONFIG_SND_DMA_SGBUF
#घोषणा SNDRV_DMA_TYPE_DEV_SG		3	/* generic device SG-buffer */
#घोषणा SNDRV_DMA_TYPE_DEV_UC_SG	6	/* SG non-cached */
#अन्यथा
#घोषणा SNDRV_DMA_TYPE_DEV_SG	SNDRV_DMA_TYPE_DEV /* no SG-buf support */
#घोषणा SNDRV_DMA_TYPE_DEV_UC_SG	SNDRV_DMA_TYPE_DEV_UC
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_ALLOCATOR
#घोषणा SNDRV_DMA_TYPE_DEV_IRAM		4	/* generic device iram-buffer */
#अन्यथा
#घोषणा SNDRV_DMA_TYPE_DEV_IRAM	SNDRV_DMA_TYPE_DEV
#पूर्ण_अगर
#घोषणा SNDRV_DMA_TYPE_VMALLOC		7	/* vदो_स्मृति'ed buffer */

/*
 * info क्रम buffer allocation
 */
काष्ठा snd_dma_buffer अणु
	काष्ठा snd_dma_device dev;	/* device type */
	अचिन्हित अक्षर *area;	/* भव poपूर्णांकer */
	dma_addr_t addr;	/* physical address */
	माप_प्रकार bytes;		/* buffer size in bytes */
	व्योम *निजी_data;	/* निजी क्रम allocator; करोn't touch */
पूर्ण;

/*
 * वापस the pages matching with the given byte size
 */
अटल अंतरभूत अचिन्हित पूर्णांक snd_sgbuf_aligned_pages(माप_प्रकार size)
अणु
	वापस (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
पूर्ण

#अगर_घोषित CONFIG_SND_DMA_SGBUF
/*
 * Scatter-Gather generic device pages
 */
व्योम *snd_दो_स्मृति_sgbuf_pages(काष्ठा device *device,
			     माप_प्रकार size, काष्ठा snd_dma_buffer *dmab,
			     माप_प्रकार *res_size);
पूर्णांक snd_मुक्त_sgbuf_pages(काष्ठा snd_dma_buffer *dmab);

काष्ठा snd_sg_page अणु
	व्योम *buf;
	dma_addr_t addr;
पूर्ण;

काष्ठा snd_sg_buf अणु
	पूर्णांक size;	/* allocated byte size */
	पूर्णांक pages;	/* allocated pages */
	पूर्णांक tblsize;	/* allocated table size */
	काष्ठा snd_sg_page *table;	/* address table */
	काष्ठा page **page_table;	/* page table (क्रम vmap/vunmap) */
	काष्ठा device *dev;
पूर्ण;

/*
 * वापस the physical address at the corresponding offset
 */
अटल अंतरभूत dma_addr_t snd_sgbuf_get_addr(काष्ठा snd_dma_buffer *dmab,
					   माप_प्रकार offset)
अणु
	काष्ठा snd_sg_buf *sgbuf = dmab->निजी_data;
	dma_addr_t addr;

	अगर (!sgbuf)
		वापस dmab->addr + offset;
	addr = sgbuf->table[offset >> PAGE_SHIFT].addr;
	addr &= ~((dma_addr_t)PAGE_SIZE - 1);
	वापस addr + offset % PAGE_SIZE;
पूर्ण

/*
 * वापस the भव address at the corresponding offset
 */
अटल अंतरभूत व्योम *snd_sgbuf_get_ptr(काष्ठा snd_dma_buffer *dmab,
				     माप_प्रकार offset)
अणु
	काष्ठा snd_sg_buf *sgbuf = dmab->निजी_data;

	अगर (!sgbuf)
		वापस dmab->area + offset;
	वापस sgbuf->table[offset >> PAGE_SHIFT].buf + offset % PAGE_SIZE;
पूर्ण

अचिन्हित पूर्णांक snd_sgbuf_get_chunk_size(काष्ठा snd_dma_buffer *dmab,
				      अचिन्हित पूर्णांक ofs, अचिन्हित पूर्णांक size);
#अन्यथा
/* non-SG versions */
अटल अंतरभूत dma_addr_t snd_sgbuf_get_addr(काष्ठा snd_dma_buffer *dmab,
					    माप_प्रकार offset)
अणु
	वापस dmab->addr + offset;
पूर्ण

अटल अंतरभूत व्योम *snd_sgbuf_get_ptr(काष्ठा snd_dma_buffer *dmab,
				      माप_प्रकार offset)
अणु
	वापस dmab->area + offset;
पूर्ण

#घोषणा snd_sgbuf_get_chunk_size(dmab, ofs, size)	(size)

#पूर्ण_अगर /* CONFIG_SND_DMA_SGBUF */

/* allocate/release a buffer */
पूर्णांक snd_dma_alloc_pages(पूर्णांक type, काष्ठा device *dev, माप_प्रकार size,
			काष्ठा snd_dma_buffer *dmab);
पूर्णांक snd_dma_alloc_pages_fallback(पूर्णांक type, काष्ठा device *dev, माप_प्रकार size,
                                 काष्ठा snd_dma_buffer *dmab);
व्योम snd_dma_मुक्त_pages(काष्ठा snd_dma_buffer *dmab);

#पूर्ण_अगर /* __SOUND_MEMALLOC_H */

