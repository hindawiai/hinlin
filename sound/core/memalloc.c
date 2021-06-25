<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Takashi Iwai <tiwai@suse.de>
 * 
 *  Generic memory allocators
 */

#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/vदो_स्मृति.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/set_memory.h>
#पूर्ण_अगर
#समावेश <sound/meदो_स्मृति.h>

/*
 *
 *  Bus-specअगरic memory allocators
 *
 */

#अगर_घोषित CONFIG_HAS_DMA
/* allocate the coherent DMA pages */
अटल व्योम snd_दो_स्मृति_dev_pages(काष्ठा snd_dma_buffer *dmab, माप_प्रकार size)
अणु
	gfp_t gfp_flags;

	gfp_flags = GFP_KERNEL
		| __GFP_COMP	/* compound page lets parts be mapped */
		| __GFP_NORETRY /* करोn't trigger OOM-समाप्तer */
		| __GFP_NOWARN; /* no stack trace prपूर्णांक - this call is non-critical */
	dmab->area = dma_alloc_coherent(dmab->dev.dev, size, &dmab->addr,
					gfp_flags);
#अगर_घोषित CONFIG_X86
	अगर (dmab->area && dmab->dev.type == SNDRV_DMA_TYPE_DEV_UC)
		set_memory_wc((अचिन्हित दीर्घ)dmab->area,
			      PAGE_ALIGN(size) >> PAGE_SHIFT);
#पूर्ण_अगर
पूर्ण

/* मुक्त the coherent DMA pages */
अटल व्योम snd_मुक्त_dev_pages(काष्ठा snd_dma_buffer *dmab)
अणु
#अगर_घोषित CONFIG_X86
	अगर (dmab->dev.type == SNDRV_DMA_TYPE_DEV_UC)
		set_memory_wb((अचिन्हित दीर्घ)dmab->area,
			      PAGE_ALIGN(dmab->bytes) >> PAGE_SHIFT);
#पूर्ण_अगर
	dma_मुक्त_coherent(dmab->dev.dev, dmab->bytes, dmab->area, dmab->addr);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_ALLOCATOR
/**
 * snd_दो_स्मृति_dev_iram - allocate memory from on-chip पूर्णांकernal ram
 * @dmab: buffer allocation record to store the allocated data
 * @size: number of bytes to allocate from the iram
 *
 * This function requires iram phandle provided via of_node
 */
अटल व्योम snd_दो_स्मृति_dev_iram(काष्ठा snd_dma_buffer *dmab, माप_प्रकार size)
अणु
	काष्ठा device *dev = dmab->dev.dev;
	काष्ठा gen_pool *pool = शून्य;

	dmab->area = शून्य;
	dmab->addr = 0;

	अगर (dev->of_node)
		pool = of_gen_pool_get(dev->of_node, "iram", 0);

	अगर (!pool)
		वापस;

	/* Assign the pool पूर्णांकo निजी_data field */
	dmab->निजी_data = pool;

	dmab->area = gen_pool_dma_alloc_align(pool, size, &dmab->addr,
					PAGE_SIZE);
पूर्ण

/**
 * snd_मुक्त_dev_iram - मुक्त allocated specअगरic memory from on-chip पूर्णांकernal ram
 * @dmab: buffer allocation record to store the allocated data
 */
अटल व्योम snd_मुक्त_dev_iram(काष्ठा snd_dma_buffer *dmab)
अणु
	काष्ठा gen_pool *pool = dmab->निजी_data;

	अगर (pool && dmab->area)
		gen_pool_मुक्त(pool, (अचिन्हित दीर्घ)dmab->area, dmab->bytes);
पूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_ALLOCATOR */
#पूर्ण_अगर /* CONFIG_HAS_DMA */

/*
 *
 *  ALSA generic memory management
 *
 */

अटल अंतरभूत gfp_t snd_mem_get_gfp_flags(स्थिर काष्ठा device *dev,
					  gfp_t शेष_gfp)
अणु
	अगर (!dev)
		वापस शेष_gfp;
	अन्यथा
		वापस (__क्रमce gfp_t)(अचिन्हित दीर्घ)dev;
पूर्ण

/**
 * snd_dma_alloc_pages - allocate the buffer area according to the given type
 * @type: the DMA buffer type
 * @device: the device poपूर्णांकer
 * @size: the buffer size to allocate
 * @dmab: buffer allocation record to store the allocated data
 *
 * Calls the memory-allocator function क्रम the corresponding
 * buffer type.
 *
 * Return: Zero अगर the buffer with the given size is allocated successfully,
 * otherwise a negative value on error.
 */
पूर्णांक snd_dma_alloc_pages(पूर्णांक type, काष्ठा device *device, माप_प्रकार size,
			काष्ठा snd_dma_buffer *dmab)
अणु
	gfp_t gfp;

	अगर (WARN_ON(!size))
		वापस -ENXIO;
	अगर (WARN_ON(!dmab))
		वापस -ENXIO;

	size = PAGE_ALIGN(size);
	dmab->dev.type = type;
	dmab->dev.dev = device;
	dmab->bytes = 0;
	dmab->area = शून्य;
	dmab->addr = 0;
	dmab->निजी_data = शून्य;
	चयन (type) अणु
	हाल SNDRV_DMA_TYPE_CONTINUOUS:
		gfp = snd_mem_get_gfp_flags(device, GFP_KERNEL);
		dmab->area = alloc_pages_exact(size, gfp);
		अवरोध;
	हाल SNDRV_DMA_TYPE_VMALLOC:
		gfp = snd_mem_get_gfp_flags(device, GFP_KERNEL | __GFP_HIGHMEM);
		dmab->area = __vदो_स्मृति(size, gfp);
		अवरोध;
#अगर_घोषित CONFIG_HAS_DMA
#अगर_घोषित CONFIG_GENERIC_ALLOCATOR
	हाल SNDRV_DMA_TYPE_DEV_IRAM:
		snd_दो_स्मृति_dev_iram(dmab, size);
		अगर (dmab->area)
			अवरोध;
		/* Internal memory might have limited size and no enough space,
		 * so अगर we fail to दो_स्मृति, try to fetch memory traditionally.
		 */
		dmab->dev.type = SNDRV_DMA_TYPE_DEV;
		fallthrough;
#पूर्ण_अगर /* CONFIG_GENERIC_ALLOCATOR */
	हाल SNDRV_DMA_TYPE_DEV:
	हाल SNDRV_DMA_TYPE_DEV_UC:
		snd_दो_स्मृति_dev_pages(dmab, size);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_DMA_SGBUF
	हाल SNDRV_DMA_TYPE_DEV_SG:
	हाल SNDRV_DMA_TYPE_DEV_UC_SG:
		snd_दो_स्मृति_sgbuf_pages(device, size, dmab, शून्य);
		अवरोध;
#पूर्ण_अगर
	शेष:
		pr_err("snd-malloc: invalid device type %d\n", type);
		वापस -ENXIO;
	पूर्ण
	अगर (! dmab->area)
		वापस -ENOMEM;
	dmab->bytes = size;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_dma_alloc_pages);

/**
 * snd_dma_alloc_pages_fallback - allocate the buffer area according to the given type with fallback
 * @type: the DMA buffer type
 * @device: the device poपूर्णांकer
 * @size: the buffer size to allocate
 * @dmab: buffer allocation record to store the allocated data
 *
 * Calls the memory-allocator function क्रम the corresponding
 * buffer type.  When no space is left, this function reduces the size and
 * tries to allocate again.  The size actually allocated is stored in
 * res_size argument.
 *
 * Return: Zero अगर the buffer with the given size is allocated successfully,
 * otherwise a negative value on error.
 */
पूर्णांक snd_dma_alloc_pages_fallback(पूर्णांक type, काष्ठा device *device, माप_प्रकार size,
				 काष्ठा snd_dma_buffer *dmab)
अणु
	पूर्णांक err;

	जबतक ((err = snd_dma_alloc_pages(type, device, size, dmab)) < 0) अणु
		अगर (err != -ENOMEM)
			वापस err;
		अगर (size <= PAGE_SIZE)
			वापस -ENOMEM;
		size >>= 1;
		size = PAGE_SIZE << get_order(size);
	पूर्ण
	अगर (! dmab->area)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_dma_alloc_pages_fallback);


/**
 * snd_dma_मुक्त_pages - release the allocated buffer
 * @dmab: the buffer allocation record to release
 *
 * Releases the allocated buffer via snd_dma_alloc_pages().
 */
व्योम snd_dma_मुक्त_pages(काष्ठा snd_dma_buffer *dmab)
अणु
	चयन (dmab->dev.type) अणु
	हाल SNDRV_DMA_TYPE_CONTINUOUS:
		मुक्त_pages_exact(dmab->area, dmab->bytes);
		अवरोध;
	हाल SNDRV_DMA_TYPE_VMALLOC:
		vमुक्त(dmab->area);
		अवरोध;
#अगर_घोषित CONFIG_HAS_DMA
#अगर_घोषित CONFIG_GENERIC_ALLOCATOR
	हाल SNDRV_DMA_TYPE_DEV_IRAM:
		snd_मुक्त_dev_iram(dmab);
		अवरोध;
#पूर्ण_अगर /* CONFIG_GENERIC_ALLOCATOR */
	हाल SNDRV_DMA_TYPE_DEV:
	हाल SNDRV_DMA_TYPE_DEV_UC:
		snd_मुक्त_dev_pages(dmab);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SND_DMA_SGBUF
	हाल SNDRV_DMA_TYPE_DEV_SG:
	हाल SNDRV_DMA_TYPE_DEV_UC_SG:
		snd_मुक्त_sgbuf_pages(dmab);
		अवरोध;
#पूर्ण_अगर
	शेष:
		pr_err("snd-malloc: invalid device type %d\n", dmab->dev.type);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_dma_मुक्त_pages);
