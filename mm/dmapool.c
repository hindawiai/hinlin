<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DMA Pool allocator
 *
 * Copyright 2001 David Brownell
 * Copyright 2007 Intel Corporation
 *   Author: Matthew Wilcox <willy@linux.पूर्णांकel.com>
 *
 * This allocator वापसs small blocks of a given size which are DMA-able by
 * the given device.  It uses the dma_alloc_coherent page allocator to get
 * new pages, then splits them up पूर्णांकo blocks of the required size.
 * Many older drivers still have their own code to करो this.
 *
 * The current design of this allocator is fairly simple.  The pool is
 * represented by the 'struct dma_pool' which keeps a करोubly-linked list of
 * allocated pages.  Each page in the page_list is split पूर्णांकo blocks of at
 * least 'size' bytes.  Free blocks are tracked in an unsorted singly-linked
 * list of मुक्त blocks within the page.  Used blocks aren't tracked, but we
 * keep a count of how many are currently allocated from each page.
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poison.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#अगर defined(CONFIG_DEBUG_SLAB) || defined(CONFIG_SLUB_DEBUG_ON)
#घोषणा DMAPOOL_DEBUG 1
#पूर्ण_अगर

काष्ठा dma_pool अणु		/* the pool */
	काष्ठा list_head page_list;
	spinlock_t lock;
	माप_प्रकार size;
	काष्ठा device *dev;
	माप_प्रकार allocation;
	माप_प्रकार boundary;
	अक्षर name[32];
	काष्ठा list_head pools;
पूर्ण;

काष्ठा dma_page अणु		/* cacheable header क्रम 'allocation' bytes */
	काष्ठा list_head page_list;
	व्योम *vaddr;
	dma_addr_t dma;
	अचिन्हित पूर्णांक in_use;
	अचिन्हित पूर्णांक offset;
पूर्ण;

अटल DEFINE_MUTEX(pools_lock);
अटल DEFINE_MUTEX(pools_reg_lock);

अटल sमाप_प्रकार
show_pools(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित temp;
	अचिन्हित size;
	अक्षर *next;
	काष्ठा dma_page *page;
	काष्ठा dma_pool *pool;

	next = buf;
	size = PAGE_SIZE;

	temp = scnम_लिखो(next, size, "poolinfo - 0.1\n");
	size -= temp;
	next += temp;

	mutex_lock(&pools_lock);
	list_क्रम_each_entry(pool, &dev->dma_pools, pools) अणु
		अचिन्हित pages = 0;
		अचिन्हित blocks = 0;

		spin_lock_irq(&pool->lock);
		list_क्रम_each_entry(page, &pool->page_list, page_list) अणु
			pages++;
			blocks += page->in_use;
		पूर्ण
		spin_unlock_irq(&pool->lock);

		/* per-pool info, no real statistics yet */
		temp = scnम_लिखो(next, size, "%-16s %4u %4zu %4zu %2u\n",
				 pool->name, blocks,
				 pages * (pool->allocation / pool->size),
				 pool->size, pages);
		size -= temp;
		next += temp;
	पूर्ण
	mutex_unlock(&pools_lock);

	वापस PAGE_SIZE - size;
पूर्ण

अटल DEVICE_ATTR(pools, 0444, show_pools, शून्य);

/**
 * dma_pool_create - Creates a pool of consistent memory blocks, क्रम dma.
 * @name: name of pool, क्रम diagnostics
 * @dev: device that will be करोing the DMA
 * @size: size of the blocks in this pool.
 * @align: alignment requirement क्रम blocks; must be a घातer of two
 * @boundary: वापसed blocks won't cross this घातer of two boundary
 * Context: not in_पूर्णांकerrupt()
 *
 * Given one of these pools, dma_pool_alloc()
 * may be used to allocate memory.  Such memory will all have "consistent"
 * DMA mappings, accessible by the device and its driver without using
 * cache flushing primitives.  The actual size of blocks allocated may be
 * larger than requested because of alignment.
 *
 * If @boundary is nonzero, objects वापसed from dma_pool_alloc() won't
 * cross that size boundary.  This is useful क्रम devices which have
 * addressing restrictions on inभागidual DMA transfers, such as not crossing
 * boundaries of 4KBytes.
 *
 * Return: a dma allocation pool with the requested अक्षरacteristics, or
 * %शून्य अगर one can't be created.
 */
काष्ठा dma_pool *dma_pool_create(स्थिर अक्षर *name, काष्ठा device *dev,
				 माप_प्रकार size, माप_प्रकार align, माप_प्रकार boundary)
अणु
	काष्ठा dma_pool *retval;
	माप_प्रकार allocation;
	bool empty = false;

	अगर (align == 0)
		align = 1;
	अन्यथा अगर (align & (align - 1))
		वापस शून्य;

	अगर (size == 0)
		वापस शून्य;
	अन्यथा अगर (size < 4)
		size = 4;

	size = ALIGN(size, align);
	allocation = max_t(माप_प्रकार, size, PAGE_SIZE);

	अगर (!boundary)
		boundary = allocation;
	अन्यथा अगर ((boundary < size) || (boundary & (boundary - 1)))
		वापस शून्य;

	retval = kदो_स्मृति_node(माप(*retval), GFP_KERNEL, dev_to_node(dev));
	अगर (!retval)
		वापस retval;

	strscpy(retval->name, name, माप(retval->name));

	retval->dev = dev;

	INIT_LIST_HEAD(&retval->page_list);
	spin_lock_init(&retval->lock);
	retval->size = size;
	retval->boundary = boundary;
	retval->allocation = allocation;

	INIT_LIST_HEAD(&retval->pools);

	/*
	 * pools_lock ensures that the ->dma_pools list करोes not get corrupted.
	 * pools_reg_lock ensures that there is not a race between
	 * dma_pool_create() and dma_pool_destroy() or within dma_pool_create()
	 * when the first invocation of dma_pool_create() failed on
	 * device_create_file() and the second assumes that it has been करोne (I
	 * know it is a लघु winकरोw).
	 */
	mutex_lock(&pools_reg_lock);
	mutex_lock(&pools_lock);
	अगर (list_empty(&dev->dma_pools))
		empty = true;
	list_add(&retval->pools, &dev->dma_pools);
	mutex_unlock(&pools_lock);
	अगर (empty) अणु
		पूर्णांक err;

		err = device_create_file(dev, &dev_attr_pools);
		अगर (err) अणु
			mutex_lock(&pools_lock);
			list_del(&retval->pools);
			mutex_unlock(&pools_lock);
			mutex_unlock(&pools_reg_lock);
			kमुक्त(retval);
			वापस शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&pools_reg_lock);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(dma_pool_create);

अटल व्योम pool_initialise_page(काष्ठा dma_pool *pool, काष्ठा dma_page *page)
अणु
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित पूर्णांक next_boundary = pool->boundary;

	करो अणु
		अचिन्हित पूर्णांक next = offset + pool->size;
		अगर (unlikely((next + pool->size) >= next_boundary)) अणु
			next = next_boundary;
			next_boundary += pool->boundary;
		पूर्ण
		*(पूर्णांक *)(page->vaddr + offset) = next;
		offset = next;
	पूर्ण जबतक (offset < pool->allocation);
पूर्ण

अटल काष्ठा dma_page *pool_alloc_page(काष्ठा dma_pool *pool, gfp_t mem_flags)
अणु
	काष्ठा dma_page *page;

	page = kदो_स्मृति(माप(*page), mem_flags);
	अगर (!page)
		वापस शून्य;
	page->vaddr = dma_alloc_coherent(pool->dev, pool->allocation,
					 &page->dma, mem_flags);
	अगर (page->vaddr) अणु
#अगर_घोषित	DMAPOOL_DEBUG
		स_रखो(page->vaddr, POOL_POISON_FREED, pool->allocation);
#पूर्ण_अगर
		pool_initialise_page(pool, page);
		page->in_use = 0;
		page->offset = 0;
	पूर्ण अन्यथा अणु
		kमुक्त(page);
		page = शून्य;
	पूर्ण
	वापस page;
पूर्ण

अटल अंतरभूत bool is_page_busy(काष्ठा dma_page *page)
अणु
	वापस page->in_use != 0;
पूर्ण

अटल व्योम pool_मुक्त_page(काष्ठा dma_pool *pool, काष्ठा dma_page *page)
अणु
	dma_addr_t dma = page->dma;

#अगर_घोषित	DMAPOOL_DEBUG
	स_रखो(page->vaddr, POOL_POISON_FREED, pool->allocation);
#पूर्ण_अगर
	dma_मुक्त_coherent(pool->dev, pool->allocation, page->vaddr, dma);
	list_del(&page->page_list);
	kमुक्त(page);
पूर्ण

/**
 * dma_pool_destroy - destroys a pool of dma memory blocks.
 * @pool: dma pool that will be destroyed
 * Context: !in_पूर्णांकerrupt()
 *
 * Caller guarantees that no more memory from the pool is in use,
 * and that nothing will try to use the pool after this call.
 */
व्योम dma_pool_destroy(काष्ठा dma_pool *pool)
अणु
	काष्ठा dma_page *page, *पंचांगp;
	bool empty = false;

	अगर (unlikely(!pool))
		वापस;

	mutex_lock(&pools_reg_lock);
	mutex_lock(&pools_lock);
	list_del(&pool->pools);
	अगर (pool->dev && list_empty(&pool->dev->dma_pools))
		empty = true;
	mutex_unlock(&pools_lock);
	अगर (empty)
		device_हटाओ_file(pool->dev, &dev_attr_pools);
	mutex_unlock(&pools_reg_lock);

	list_क्रम_each_entry_safe(page, पंचांगp, &pool->page_list, page_list) अणु
		अगर (is_page_busy(page)) अणु
			अगर (pool->dev)
				dev_err(pool->dev, "%s %s, %p busy\n", __func__,
					pool->name, page->vaddr);
			अन्यथा
				pr_err("%s %s, %p busy\n", __func__,
				       pool->name, page->vaddr);
			/* leak the still-in-use consistent memory */
			list_del(&page->page_list);
			kमुक्त(page);
		पूर्ण अन्यथा
			pool_मुक्त_page(pool, page);
	पूर्ण

	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL(dma_pool_destroy);

/**
 * dma_pool_alloc - get a block of consistent memory
 * @pool: dma pool that will produce the block
 * @mem_flags: GFP_* biपंचांगask
 * @handle: poपूर्णांकer to dma address of block
 *
 * Return: the kernel भव address of a currently unused block,
 * and reports its dma address through the handle.
 * If such a memory block can't be allocated, %शून्य is वापसed.
 */
व्योम *dma_pool_alloc(काष्ठा dma_pool *pool, gfp_t mem_flags,
		     dma_addr_t *handle)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_page *page;
	माप_प्रकार offset;
	व्योम *retval;

	might_alloc(mem_flags);

	spin_lock_irqsave(&pool->lock, flags);
	list_क्रम_each_entry(page, &pool->page_list, page_list) अणु
		अगर (page->offset < pool->allocation)
			जाओ पढ़ोy;
	पूर्ण

	/* pool_alloc_page() might sleep, so temporarily drop &pool->lock */
	spin_unlock_irqrestore(&pool->lock, flags);

	page = pool_alloc_page(pool, mem_flags & (~__GFP_ZERO));
	अगर (!page)
		वापस शून्य;

	spin_lock_irqsave(&pool->lock, flags);

	list_add(&page->page_list, &pool->page_list);
 पढ़ोy:
	page->in_use++;
	offset = page->offset;
	page->offset = *(पूर्णांक *)(page->vaddr + offset);
	retval = offset + page->vaddr;
	*handle = offset + page->dma;
#अगर_घोषित	DMAPOOL_DEBUG
	अणु
		पूर्णांक i;
		u8 *data = retval;
		/* page->offset is stored in first 4 bytes */
		क्रम (i = माप(page->offset); i < pool->size; i++) अणु
			अगर (data[i] == POOL_POISON_FREED)
				जारी;
			अगर (pool->dev)
				dev_err(pool->dev, "%s %s, %p (corrupted)\n",
					__func__, pool->name, retval);
			अन्यथा
				pr_err("%s %s, %p (corrupted)\n",
					__func__, pool->name, retval);

			/*
			 * Dump the first 4 bytes even अगर they are not
			 * POOL_POISON_FREED
			 */
			prपूर्णांक_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1,
					data, pool->size, 1);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!(mem_flags & __GFP_ZERO))
		स_रखो(retval, POOL_POISON_ALLOCATED, pool->size);
#पूर्ण_अगर
	spin_unlock_irqrestore(&pool->lock, flags);

	अगर (want_init_on_alloc(mem_flags))
		स_रखो(retval, 0, pool->size);

	वापस retval;
पूर्ण
EXPORT_SYMBOL(dma_pool_alloc);

अटल काष्ठा dma_page *pool_find_page(काष्ठा dma_pool *pool, dma_addr_t dma)
अणु
	काष्ठा dma_page *page;

	list_क्रम_each_entry(page, &pool->page_list, page_list) अणु
		अगर (dma < page->dma)
			जारी;
		अगर ((dma - page->dma) < pool->allocation)
			वापस page;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * dma_pool_मुक्त - put block back पूर्णांकo dma pool
 * @pool: the dma pool holding the block
 * @vaddr: भव address of block
 * @dma: dma address of block
 *
 * Caller promises neither device nor driver will again touch this block
 * unless it is first re-allocated.
 */
व्योम dma_pool_मुक्त(काष्ठा dma_pool *pool, व्योम *vaddr, dma_addr_t dma)
अणु
	काष्ठा dma_page *page;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset;

	spin_lock_irqsave(&pool->lock, flags);
	page = pool_find_page(pool, dma);
	अगर (!page) अणु
		spin_unlock_irqrestore(&pool->lock, flags);
		अगर (pool->dev)
			dev_err(pool->dev, "%s %s, %p/%pad (bad dma)\n",
				__func__, pool->name, vaddr, &dma);
		अन्यथा
			pr_err("%s %s, %p/%pad (bad dma)\n",
			       __func__, pool->name, vaddr, &dma);
		वापस;
	पूर्ण

	offset = vaddr - page->vaddr;
	अगर (want_init_on_मुक्त())
		स_रखो(vaddr, 0, pool->size);
#अगर_घोषित	DMAPOOL_DEBUG
	अगर ((dma - page->dma) != offset) अणु
		spin_unlock_irqrestore(&pool->lock, flags);
		अगर (pool->dev)
			dev_err(pool->dev, "%s %s, %p (bad vaddr)/%pad\n",
				__func__, pool->name, vaddr, &dma);
		अन्यथा
			pr_err("%s %s, %p (bad vaddr)/%pad\n",
			       __func__, pool->name, vaddr, &dma);
		वापस;
	पूर्ण
	अणु
		अचिन्हित पूर्णांक chain = page->offset;
		जबतक (chain < pool->allocation) अणु
			अगर (chain != offset) अणु
				chain = *(पूर्णांक *)(page->vaddr + chain);
				जारी;
			पूर्ण
			spin_unlock_irqrestore(&pool->lock, flags);
			अगर (pool->dev)
				dev_err(pool->dev, "%s %s, dma %pad already free\n",
					__func__, pool->name, &dma);
			अन्यथा
				pr_err("%s %s, dma %pad already free\n",
				       __func__, pool->name, &dma);
			वापस;
		पूर्ण
	पूर्ण
	स_रखो(vaddr, POOL_POISON_FREED, pool->size);
#पूर्ण_अगर

	page->in_use--;
	*(पूर्णांक *)vaddr = page->offset;
	page->offset = offset;
	/*
	 * Resist a temptation to करो
	 *    अगर (!is_page_busy(page)) pool_मुक्त_page(pool, page);
	 * Better have a few empty pages hang around.
	 */
	spin_unlock_irqrestore(&pool->lock, flags);
पूर्ण
EXPORT_SYMBOL(dma_pool_मुक्त);

/*
 * Managed DMA pool
 */
अटल व्योम dmam_pool_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा dma_pool *pool = *(काष्ठा dma_pool **)res;

	dma_pool_destroy(pool);
पूर्ण

अटल पूर्णांक dmam_pool_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	वापस *(काष्ठा dma_pool **)res == match_data;
पूर्ण

/**
 * dmam_pool_create - Managed dma_pool_create()
 * @name: name of pool, क्रम diagnostics
 * @dev: device that will be करोing the DMA
 * @size: size of the blocks in this pool.
 * @align: alignment requirement क्रम blocks; must be a घातer of two
 * @allocation: वापसed blocks won't cross this boundary (or zero)
 *
 * Managed dma_pool_create().  DMA pool created with this function is
 * स्वतःmatically destroyed on driver detach.
 *
 * Return: a managed dma allocation pool with the requested
 * अक्षरacteristics, or %शून्य अगर one can't be created.
 */
काष्ठा dma_pool *dmam_pool_create(स्थिर अक्षर *name, काष्ठा device *dev,
				  माप_प्रकार size, माप_प्रकार align, माप_प्रकार allocation)
अणु
	काष्ठा dma_pool **ptr, *pool;

	ptr = devres_alloc(dmam_pool_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	pool = *ptr = dma_pool_create(name, dev, size, align, allocation);
	अगर (pool)
		devres_add(dev, ptr);
	अन्यथा
		devres_मुक्त(ptr);

	वापस pool;
पूर्ण
EXPORT_SYMBOL(dmam_pool_create);

/**
 * dmam_pool_destroy - Managed dma_pool_destroy()
 * @pool: dma pool that will be destroyed
 *
 * Managed dma_pool_destroy().
 */
व्योम dmam_pool_destroy(काष्ठा dma_pool *pool)
अणु
	काष्ठा device *dev = pool->dev;

	WARN_ON(devres_release(dev, dmam_pool_release, dmam_pool_match, pool));
पूर्ण
EXPORT_SYMBOL(dmam_pool_destroy);
