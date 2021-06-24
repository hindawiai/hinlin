<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  arch/arm/common/dmabounce.c
 *
 *  Special dma_अणुmap/unmap/dma_syncपूर्ण_* routines क्रम प्रणालीs that have
 *  limited DMA winकरोws. These functions utilize bounce buffers to
 *  copy data to/from buffers located outside the DMA region. This
 *  only works क्रम प्रणालीs in which DMA memory is at the bottom of
 *  RAM, the reमुख्यder of memory is at the top and the DMA memory
 *  can be marked as ZONE_DMA. Anything beyond that such as discontiguous
 *  DMA winकरोws will require custom implementations that reserve memory
 *  areas at early bootup.
 *
 *  Original version by Brad Parker (brad@heeltoe.com)
 *  Re-written by Christopher Hoover <ch@murgatroid.com>
 *  Made generic by Deepak Saxena <dsaxena@plनिकासy.net>
 *
 *  Copyright (C) 2002 Hewlett Packard Company.
 *  Copyright (C) 2004 MontaVista Software, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/list.h>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dma-iommu.h>

#अघोषित STATS

#अगर_घोषित STATS
#घोषणा DO_STATS(X) करो अणु X ; पूर्ण जबतक (0)
#अन्यथा
#घोषणा DO_STATS(X) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* ************************************************** */

काष्ठा safe_buffer अणु
	काष्ठा list_head node;

	/* original request */
	व्योम		*ptr;
	माप_प्रकार		size;
	पूर्णांक		direction;

	/* safe buffer info */
	काष्ठा dmabounce_pool *pool;
	व्योम		*safe;
	dma_addr_t	safe_dma_addr;
पूर्ण;

काष्ठा dmabounce_pool अणु
	अचिन्हित दीर्घ	size;
	काष्ठा dma_pool	*pool;
#अगर_घोषित STATS
	अचिन्हित दीर्घ	allocs;
#पूर्ण_अगर
पूर्ण;

काष्ठा dmabounce_device_info अणु
	काष्ठा device *dev;
	काष्ठा list_head safe_buffers;
#अगर_घोषित STATS
	अचिन्हित दीर्घ total_allocs;
	अचिन्हित दीर्घ map_op_count;
	अचिन्हित दीर्घ bounce_count;
	पूर्णांक attr_res;
#पूर्ण_अगर
	काष्ठा dmabounce_pool	small;
	काष्ठा dmabounce_pool	large;

	rwlock_t lock;

	पूर्णांक (*needs_bounce)(काष्ठा device *, dma_addr_t, माप_प्रकार);
पूर्ण;

#अगर_घोषित STATS
अटल sमाप_प्रकार dmabounce_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा dmabounce_device_info *device_info = dev->archdata.dmabounce;
	वापस प्र_लिखो(buf, "%lu %lu %lu %lu %lu %lu\n",
		device_info->small.allocs,
		device_info->large.allocs,
		device_info->total_allocs - device_info->small.allocs -
			device_info->large.allocs,
		device_info->total_allocs,
		device_info->map_op_count,
		device_info->bounce_count);
पूर्ण

अटल DEVICE_ATTR(dmabounce_stats, 0400, dmabounce_show, शून्य);
#पूर्ण_अगर


/* allocate a 'safe' buffer and keep track of it */
अटल अंतरभूत काष्ठा safe_buffer *
alloc_safe_buffer(काष्ठा dmabounce_device_info *device_info, व्योम *ptr,
		  माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	काष्ठा safe_buffer *buf;
	काष्ठा dmabounce_pool *pool;
	काष्ठा device *dev = device_info->dev;
	अचिन्हित दीर्घ flags;

	dev_dbg(dev, "%s(ptr=%p, size=%d, dir=%d)\n",
		__func__, ptr, size, dir);

	अगर (size <= device_info->small.size) अणु
		pool = &device_info->small;
	पूर्ण अन्यथा अगर (size <= device_info->large.size) अणु
		pool = &device_info->large;
	पूर्ण अन्यथा अणु
		pool = शून्य;
	पूर्ण

	buf = kदो_स्मृति(माप(काष्ठा safe_buffer), GFP_ATOMIC);
	अगर (buf == शून्य) अणु
		dev_warn(dev, "%s: kmalloc failed\n", __func__);
		वापस शून्य;
	पूर्ण

	buf->ptr = ptr;
	buf->size = size;
	buf->direction = dir;
	buf->pool = pool;

	अगर (pool) अणु
		buf->safe = dma_pool_alloc(pool->pool, GFP_ATOMIC,
					   &buf->safe_dma_addr);
	पूर्ण अन्यथा अणु
		buf->safe = dma_alloc_coherent(dev, size, &buf->safe_dma_addr,
					       GFP_ATOMIC);
	पूर्ण

	अगर (buf->safe == शून्य) अणु
		dev_warn(dev,
			 "%s: could not alloc dma memory (size=%d)\n",
			 __func__, size);
		kमुक्त(buf);
		वापस शून्य;
	पूर्ण

#अगर_घोषित STATS
	अगर (pool)
		pool->allocs++;
	device_info->total_allocs++;
#पूर्ण_अगर

	ग_लिखो_lock_irqsave(&device_info->lock, flags);
	list_add(&buf->node, &device_info->safe_buffers);
	ग_लिखो_unlock_irqrestore(&device_info->lock, flags);

	वापस buf;
पूर्ण

/* determine अगर a buffer is from our "safe" pool */
अटल अंतरभूत काष्ठा safe_buffer *
find_safe_buffer(काष्ठा dmabounce_device_info *device_info, dma_addr_t safe_dma_addr)
अणु
	काष्ठा safe_buffer *b, *rb = शून्य;
	अचिन्हित दीर्घ flags;

	पढ़ो_lock_irqsave(&device_info->lock, flags);

	list_क्रम_each_entry(b, &device_info->safe_buffers, node)
		अगर (b->safe_dma_addr <= safe_dma_addr &&
		    b->safe_dma_addr + b->size > safe_dma_addr) अणु
			rb = b;
			अवरोध;
		पूर्ण

	पढ़ो_unlock_irqrestore(&device_info->lock, flags);
	वापस rb;
पूर्ण

अटल अंतरभूत व्योम
मुक्त_safe_buffer(काष्ठा dmabounce_device_info *device_info, काष्ठा safe_buffer *buf)
अणु
	अचिन्हित दीर्घ flags;

	dev_dbg(device_info->dev, "%s(buf=%p)\n", __func__, buf);

	ग_लिखो_lock_irqsave(&device_info->lock, flags);

	list_del(&buf->node);

	ग_लिखो_unlock_irqrestore(&device_info->lock, flags);

	अगर (buf->pool)
		dma_pool_मुक्त(buf->pool->pool, buf->safe, buf->safe_dma_addr);
	अन्यथा
		dma_मुक्त_coherent(device_info->dev, buf->size, buf->safe,
				    buf->safe_dma_addr);

	kमुक्त(buf);
पूर्ण

/* ************************************************** */

अटल काष्ठा safe_buffer *find_safe_buffer_dev(काष्ठा device *dev,
		dma_addr_t dma_addr, स्थिर अक्षर *where)
अणु
	अगर (!dev || !dev->archdata.dmabounce)
		वापस शून्य;
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		dev_err(dev, "Trying to %s invalid mapping\n", where);
		वापस शून्य;
	पूर्ण
	वापस find_safe_buffer(dev->archdata.dmabounce, dma_addr);
पूर्ण

अटल पूर्णांक needs_bounce(काष्ठा device *dev, dma_addr_t dma_addr, माप_प्रकार size)
अणु
	अगर (!dev || !dev->archdata.dmabounce)
		वापस 0;

	अगर (dev->dma_mask) अणु
		अचिन्हित दीर्घ limit, mask = *dev->dma_mask;

		limit = (mask + 1) & ~mask;
		अगर (limit && size > limit) अणु
			dev_err(dev, "DMA mapping too big (requested %#x "
				"mask %#Lx)\n", size, *dev->dma_mask);
			वापस -E2BIG;
		पूर्ण

		/* Figure out अगर we need to bounce from the DMA mask. */
		अगर ((dma_addr | (dma_addr + size - 1)) & ~mask)
			वापस 1;
	पूर्ण

	वापस !!dev->archdata.dmabounce->needs_bounce(dev, dma_addr, size);
पूर्ण

अटल अंतरभूत dma_addr_t map_single(काष्ठा device *dev, व्योम *ptr, माप_प्रकार size,
				    क्रमागत dma_data_direction dir,
				    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dmabounce_device_info *device_info = dev->archdata.dmabounce;
	काष्ठा safe_buffer *buf;

	अगर (device_info)
		DO_STATS ( device_info->map_op_count++ );

	buf = alloc_safe_buffer(device_info, ptr, size, dir);
	अगर (buf == शून्य) अणु
		dev_err(dev, "%s: unable to map unsafe buffer %p!\n",
		       __func__, ptr);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	dev_dbg(dev, "%s: unsafe buffer %p (dma=%#x) mapped to %p (dma=%#x)\n",
		__func__, buf->ptr, virt_to_dma(dev, buf->ptr),
		buf->safe, buf->safe_dma_addr);

	अगर ((dir == DMA_TO_DEVICE || dir == DMA_BIसूचीECTIONAL) &&
	    !(attrs & DMA_ATTR_SKIP_CPU_SYNC)) अणु
		dev_dbg(dev, "%s: copy unsafe %p to safe %p, size %d\n",
			__func__, ptr, buf->safe, size);
		स_नकल(buf->safe, ptr, size);
	पूर्ण

	वापस buf->safe_dma_addr;
पूर्ण

अटल अंतरभूत व्योम unmap_single(काष्ठा device *dev, काष्ठा safe_buffer *buf,
				माप_प्रकार size, क्रमागत dma_data_direction dir,
				अचिन्हित दीर्घ attrs)
अणु
	BUG_ON(buf->size != size);
	BUG_ON(buf->direction != dir);

	dev_dbg(dev, "%s: unsafe buffer %p (dma=%#x) mapped to %p (dma=%#x)\n",
		__func__, buf->ptr, virt_to_dma(dev, buf->ptr),
		buf->safe, buf->safe_dma_addr);

	DO_STATS(dev->archdata.dmabounce->bounce_count++);

	अगर ((dir == DMA_FROM_DEVICE || dir == DMA_BIसूचीECTIONAL) &&
	    !(attrs & DMA_ATTR_SKIP_CPU_SYNC)) अणु
		व्योम *ptr = buf->ptr;

		dev_dbg(dev, "%s: copy back safe %p to unsafe %p size %d\n",
			__func__, buf->safe, ptr, size);
		स_नकल(ptr, buf->safe, size);

		/*
		 * Since we may have written to a page cache page,
		 * we need to ensure that the data will be coherent
		 * with user mappings.
		 */
		__cpuc_flush_dcache_area(ptr, size);
	पूर्ण
	मुक्त_safe_buffer(dev->archdata.dmabounce, buf);
पूर्ण

/* ************************************************** */

/*
 * see अगर a buffer address is in an 'unsafe' range.  अगर it is
 * allocate a 'safe' buffer and copy the unsafe buffer पूर्णांकo it.
 * substitute the safe buffer क्रम the unsafe one.
 * (basically move the buffer from an unsafe area to a safe one)
 */
अटल dma_addr_t dmabounce_map_page(काष्ठा device *dev, काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	dma_addr_t dma_addr;
	पूर्णांक ret;

	dev_dbg(dev, "%s(page=%p,off=%#lx,size=%zx,dir=%x)\n",
		__func__, page, offset, size, dir);

	dma_addr = pfn_to_dma(dev, page_to_pfn(page)) + offset;

	ret = needs_bounce(dev, dma_addr, size);
	अगर (ret < 0)
		वापस DMA_MAPPING_ERROR;

	अगर (ret == 0) अणु
		arm_dma_ops.sync_single_क्रम_device(dev, dma_addr, size, dir);
		वापस dma_addr;
	पूर्ण

	अगर (PageHighMem(page)) अणु
		dev_err(dev, "DMA buffer bouncing of HIGHMEM pages is not supported\n");
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	वापस map_single(dev, page_address(page) + offset, size, dir, attrs);
पूर्ण

/*
 * see अगर a mapped address was really a "safe" buffer and अगर so, copy
 * the data from the safe buffer back to the unsafe buffer and मुक्त up
 * the safe buffer.  (basically वापस things back to the way they
 * should be)
 */
अटल व्योम dmabounce_unmap_page(काष्ठा device *dev, dma_addr_t dma_addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा safe_buffer *buf;

	dev_dbg(dev, "%s(dma=%#x,size=%d,dir=%x)\n",
		__func__, dma_addr, size, dir);

	buf = find_safe_buffer_dev(dev, dma_addr, __func__);
	अगर (!buf) अणु
		arm_dma_ops.sync_single_क्रम_cpu(dev, dma_addr, size, dir);
		वापस;
	पूर्ण

	unmap_single(dev, buf, size, dir, attrs);
पूर्ण

अटल पूर्णांक __dmabounce_sync_क्रम_cpu(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार sz, क्रमागत dma_data_direction dir)
अणु
	काष्ठा safe_buffer *buf;
	अचिन्हित दीर्घ off;

	dev_dbg(dev, "%s(dma=%#x,sz=%zx,dir=%x)\n",
		__func__, addr, sz, dir);

	buf = find_safe_buffer_dev(dev, addr, __func__);
	अगर (!buf)
		वापस 1;

	off = addr - buf->safe_dma_addr;

	BUG_ON(buf->direction != dir);

	dev_dbg(dev, "%s: unsafe buffer %p (dma=%#x off=%#lx) mapped to %p (dma=%#x)\n",
		__func__, buf->ptr, virt_to_dma(dev, buf->ptr), off,
		buf->safe, buf->safe_dma_addr);

	DO_STATS(dev->archdata.dmabounce->bounce_count++);

	अगर (dir == DMA_FROM_DEVICE || dir == DMA_BIसूचीECTIONAL) अणु
		dev_dbg(dev, "%s: copy back safe %p to unsafe %p size %d\n",
			__func__, buf->safe + off, buf->ptr + off, sz);
		स_नकल(buf->ptr + off, buf->safe + off, sz);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dmabounce_sync_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अगर (!__dmabounce_sync_क्रम_cpu(dev, handle, size, dir))
		वापस;

	arm_dma_ops.sync_single_क्रम_cpu(dev, handle, size, dir);
पूर्ण

अटल पूर्णांक __dmabounce_sync_क्रम_device(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार sz, क्रमागत dma_data_direction dir)
अणु
	काष्ठा safe_buffer *buf;
	अचिन्हित दीर्घ off;

	dev_dbg(dev, "%s(dma=%#x,sz=%zx,dir=%x)\n",
		__func__, addr, sz, dir);

	buf = find_safe_buffer_dev(dev, addr, __func__);
	अगर (!buf)
		वापस 1;

	off = addr - buf->safe_dma_addr;

	BUG_ON(buf->direction != dir);

	dev_dbg(dev, "%s: unsafe buffer %p (dma=%#x off=%#lx) mapped to %p (dma=%#x)\n",
		__func__, buf->ptr, virt_to_dma(dev, buf->ptr), off,
		buf->safe, buf->safe_dma_addr);

	DO_STATS(dev->archdata.dmabounce->bounce_count++);

	अगर (dir == DMA_TO_DEVICE || dir == DMA_BIसूचीECTIONAL) अणु
		dev_dbg(dev, "%s: copy out unsafe %p to safe %p, size %d\n",
			__func__,buf->ptr + off, buf->safe + off, sz);
		स_नकल(buf->safe + off, buf->ptr + off, sz);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dmabounce_sync_क्रम_device(काष्ठा device *dev,
		dma_addr_t handle, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अगर (!__dmabounce_sync_क्रम_device(dev, handle, size, dir))
		वापस;

	arm_dma_ops.sync_single_क्रम_device(dev, handle, size, dir);
पूर्ण

अटल पूर्णांक dmabounce_dma_supported(काष्ठा device *dev, u64 dma_mask)
अणु
	अगर (dev->archdata.dmabounce)
		वापस 0;

	वापस arm_dma_ops.dma_supported(dev, dma_mask);
पूर्ण

अटल स्थिर काष्ठा dma_map_ops dmabounce_ops = अणु
	.alloc			= arm_dma_alloc,
	.मुक्त			= arm_dma_मुक्त,
	.mmap			= arm_dma_mmap,
	.get_sgtable		= arm_dma_get_sgtable,
	.map_page		= dmabounce_map_page,
	.unmap_page		= dmabounce_unmap_page,
	.sync_single_क्रम_cpu	= dmabounce_sync_क्रम_cpu,
	.sync_single_क्रम_device	= dmabounce_sync_क्रम_device,
	.map_sg			= arm_dma_map_sg,
	.unmap_sg		= arm_dma_unmap_sg,
	.sync_sg_क्रम_cpu	= arm_dma_sync_sg_क्रम_cpu,
	.sync_sg_क्रम_device	= arm_dma_sync_sg_क्रम_device,
	.dma_supported		= dmabounce_dma_supported,
पूर्ण;

अटल पूर्णांक dmabounce_init_pool(काष्ठा dmabounce_pool *pool, काष्ठा device *dev,
		स्थिर अक्षर *name, अचिन्हित दीर्घ size)
अणु
	pool->size = size;
	DO_STATS(pool->allocs = 0);
	pool->pool = dma_pool_create(name, dev, size,
				     0 /* byte alignment */,
				     0 /* no page-crossing issues */);

	वापस pool->pool ? 0 : -ENOMEM;
पूर्ण

पूर्णांक dmabounce_रेजिस्टर_dev(काष्ठा device *dev, अचिन्हित दीर्घ small_buffer_size,
		अचिन्हित दीर्घ large_buffer_size,
		पूर्णांक (*needs_bounce_fn)(काष्ठा device *, dma_addr_t, माप_प्रकार))
अणु
	काष्ठा dmabounce_device_info *device_info;
	पूर्णांक ret;

	device_info = kदो_स्मृति(माप(काष्ठा dmabounce_device_info), GFP_ATOMIC);
	अगर (!device_info) अणु
		dev_err(dev,
			"Could not allocated dmabounce_device_info\n");
		वापस -ENOMEM;
	पूर्ण

	ret = dmabounce_init_pool(&device_info->small, dev,
				  "small_dmabounce_pool", small_buffer_size);
	अगर (ret) अणु
		dev_err(dev,
			"dmabounce: could not allocate DMA pool for %ld byte objects\n",
			small_buffer_size);
		जाओ err_मुक्त;
	पूर्ण

	अगर (large_buffer_size) अणु
		ret = dmabounce_init_pool(&device_info->large, dev,
					  "large_dmabounce_pool",
					  large_buffer_size);
		अगर (ret) अणु
			dev_err(dev,
				"dmabounce: could not allocate DMA pool for %ld byte objects\n",
				large_buffer_size);
			जाओ err_destroy;
		पूर्ण
	पूर्ण

	device_info->dev = dev;
	INIT_LIST_HEAD(&device_info->safe_buffers);
	rwlock_init(&device_info->lock);
	device_info->needs_bounce = needs_bounce_fn;

#अगर_घोषित STATS
	device_info->total_allocs = 0;
	device_info->map_op_count = 0;
	device_info->bounce_count = 0;
	device_info->attr_res = device_create_file(dev, &dev_attr_dmabounce_stats);
#पूर्ण_अगर

	dev->archdata.dmabounce = device_info;
	set_dma_ops(dev, &dmabounce_ops);

	dev_info(dev, "dmabounce: registered device\n");

	वापस 0;

 err_destroy:
	dma_pool_destroy(device_info->small.pool);
 err_मुक्त:
	kमुक्त(device_info);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dmabounce_रेजिस्टर_dev);

व्योम dmabounce_unरेजिस्टर_dev(काष्ठा device *dev)
अणु
	काष्ठा dmabounce_device_info *device_info = dev->archdata.dmabounce;

	dev->archdata.dmabounce = शून्य;
	set_dma_ops(dev, शून्य);

	अगर (!device_info) अणु
		dev_warn(dev,
			 "Never registered with dmabounce but attempting"
			 "to unregister!\n");
		वापस;
	पूर्ण

	अगर (!list_empty(&device_info->safe_buffers)) अणु
		dev_err(dev,
			"Removing from dmabounce with pending buffers!\n");
		BUG();
	पूर्ण

	अगर (device_info->small.pool)
		dma_pool_destroy(device_info->small.pool);
	अगर (device_info->large.pool)
		dma_pool_destroy(device_info->large.pool);

#अगर_घोषित STATS
	अगर (device_info->attr_res == 0)
		device_हटाओ_file(dev, &dev_attr_dmabounce_stats);
#पूर्ण_अगर

	kमुक्त(device_info);

	dev_info(dev, "dmabounce: device unregistered\n");
पूर्ण
EXPORT_SYMBOL(dmabounce_unरेजिस्टर_dev);

MODULE_AUTHOR("Christopher Hoover <ch@hpl.hp.com>, Deepak Saxena <dsaxena@plexity.net>");
MODULE_DESCRIPTION("Special dma_{map/unmap/dma_sync}_* routines for systems with limited DMA windows");
MODULE_LICENSE("GPL");
