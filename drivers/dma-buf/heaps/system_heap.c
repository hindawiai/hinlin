<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DMABUF System heap exporter
 *
 * Copyright (C) 2011 Google, Inc.
 * Copyright (C) 2019, 2020 Linaro Ltd.
 *
 * Portions based off of Andrew Davis' SRAM heap:
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma-heap.h>
#समावेश <linux/err.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

अटल काष्ठा dma_heap *sys_heap;

काष्ठा प्रणाली_heap_buffer अणु
	काष्ठा dma_heap *heap;
	काष्ठा list_head attachments;
	काष्ठा mutex lock;
	अचिन्हित दीर्घ len;
	काष्ठा sg_table sg_table;
	पूर्णांक vmap_cnt;
	व्योम *vaddr;
पूर्ण;

काष्ठा dma_heap_attachment अणु
	काष्ठा device *dev;
	काष्ठा sg_table *table;
	काष्ठा list_head list;
	bool mapped;
पूर्ण;

#घोषणा HIGH_ORDER_GFP  (((GFP_HIGHUSER | __GFP_ZERO | __GFP_NOWARN \
				| __GFP_NORETRY) & ~__GFP_RECLAIM) \
				| __GFP_COMP)
#घोषणा LOW_ORDER_GFP (GFP_HIGHUSER | __GFP_ZERO | __GFP_COMP)
अटल gfp_t order_flags[] = अणुHIGH_ORDER_GFP, LOW_ORDER_GFP, LOW_ORDER_GFPपूर्ण;
/*
 * The selection of the orders used क्रम allocation (1MB, 64K, 4K) is deचिन्हित
 * to match with the sizes often found in IOMMUs. Using order 4 pages instead
 * of order 0 pages can signअगरicantly improve the perक्रमmance of many IOMMUs
 * by reducing TLB pressure and समय spent updating page tables.
 */
अटल स्थिर अचिन्हित पूर्णांक orders[] = अणु8, 4, 0पूर्ण;
#घोषणा NUM_ORDERS ARRAY_SIZE(orders)

अटल काष्ठा sg_table *dup_sg_table(काष्ठा sg_table *table)
अणु
	काष्ठा sg_table *new_table;
	पूर्णांक ret, i;
	काष्ठा scatterlist *sg, *new_sg;

	new_table = kzalloc(माप(*new_table), GFP_KERNEL);
	अगर (!new_table)
		वापस ERR_PTR(-ENOMEM);

	ret = sg_alloc_table(new_table, table->orig_nents, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(new_table);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	new_sg = new_table->sgl;
	क्रम_each_sgtable_sg(table, sg, i) अणु
		sg_set_page(new_sg, sg_page(sg), sg->length, sg->offset);
		new_sg = sg_next(new_sg);
	पूर्ण

	वापस new_table;
पूर्ण

अटल पूर्णांक प्रणाली_heap_attach(काष्ठा dma_buf *dmabuf,
			      काष्ठा dma_buf_attachment *attachment)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a;
	काष्ठा sg_table *table;

	a = kzalloc(माप(*a), GFP_KERNEL);
	अगर (!a)
		वापस -ENOMEM;

	table = dup_sg_table(&buffer->sg_table);
	अगर (IS_ERR(table)) अणु
		kमुक्त(a);
		वापस -ENOMEM;
	पूर्ण

	a->table = table;
	a->dev = attachment->dev;
	INIT_LIST_HEAD(&a->list);
	a->mapped = false;

	attachment->priv = a;

	mutex_lock(&buffer->lock);
	list_add(&a->list, &buffer->attachments);
	mutex_unlock(&buffer->lock);

	वापस 0;
पूर्ण

अटल व्योम प्रणाली_heap_detach(काष्ठा dma_buf *dmabuf,
			       काष्ठा dma_buf_attachment *attachment)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a = attachment->priv;

	mutex_lock(&buffer->lock);
	list_del(&a->list);
	mutex_unlock(&buffer->lock);

	sg_मुक्त_table(a->table);
	kमुक्त(a->table);
	kमुक्त(a);
पूर्ण

अटल काष्ठा sg_table *प्रणाली_heap_map_dma_buf(काष्ठा dma_buf_attachment *attachment,
						क्रमागत dma_data_direction direction)
अणु
	काष्ठा dma_heap_attachment *a = attachment->priv;
	काष्ठा sg_table *table = a->table;
	पूर्णांक ret;

	ret = dma_map_sgtable(attachment->dev, table, direction, 0);
	अगर (ret)
		वापस ERR_PTR(ret);

	a->mapped = true;
	वापस table;
पूर्ण

अटल व्योम प्रणाली_heap_unmap_dma_buf(काष्ठा dma_buf_attachment *attachment,
				      काष्ठा sg_table *table,
				      क्रमागत dma_data_direction direction)
अणु
	काष्ठा dma_heap_attachment *a = attachment->priv;

	a->mapped = false;
	dma_unmap_sgtable(attachment->dev, table, direction, 0);
पूर्ण

अटल पूर्णांक प्रणाली_heap_dma_buf_begin_cpu_access(काष्ठा dma_buf *dmabuf,
						क्रमागत dma_data_direction direction)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a;

	mutex_lock(&buffer->lock);

	अगर (buffer->vmap_cnt)
		invalidate_kernel_vmap_range(buffer->vaddr, buffer->len);

	list_क्रम_each_entry(a, &buffer->attachments, list) अणु
		अगर (!a->mapped)
			जारी;
		dma_sync_sgtable_क्रम_cpu(a->dev, a->table, direction);
	पूर्ण
	mutex_unlock(&buffer->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक प्रणाली_heap_dma_buf_end_cpu_access(काष्ठा dma_buf *dmabuf,
					      क्रमागत dma_data_direction direction)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a;

	mutex_lock(&buffer->lock);

	अगर (buffer->vmap_cnt)
		flush_kernel_vmap_range(buffer->vaddr, buffer->len);

	list_क्रम_each_entry(a, &buffer->attachments, list) अणु
		अगर (!a->mapped)
			जारी;
		dma_sync_sgtable_क्रम_device(a->dev, a->table, direction);
	पूर्ण
	mutex_unlock(&buffer->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक प्रणाली_heap_mmap(काष्ठा dma_buf *dmabuf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;
	काष्ठा sg_table *table = &buffer->sg_table;
	अचिन्हित दीर्घ addr = vma->vm_start;
	काष्ठा sg_page_iter piter;
	पूर्णांक ret;

	क्रम_each_sgtable_page(table, &piter, vma->vm_pgoff) अणु
		काष्ठा page *page = sg_page_iter_page(&piter);

		ret = remap_pfn_range(vma, addr, page_to_pfn(page), PAGE_SIZE,
				      vma->vm_page_prot);
		अगर (ret)
			वापस ret;
		addr += PAGE_SIZE;
		अगर (addr >= vma->vm_end)
			वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *प्रणाली_heap_करो_vmap(काष्ठा प्रणाली_heap_buffer *buffer)
अणु
	काष्ठा sg_table *table = &buffer->sg_table;
	पूर्णांक npages = PAGE_ALIGN(buffer->len) / PAGE_SIZE;
	काष्ठा page **pages = vदो_स्मृति(माप(काष्ठा page *) * npages);
	काष्ठा page **पंचांगp = pages;
	काष्ठा sg_page_iter piter;
	व्योम *vaddr;

	अगर (!pages)
		वापस ERR_PTR(-ENOMEM);

	क्रम_each_sgtable_page(table, &piter, 0) अणु
		WARN_ON(पंचांगp - pages >= npages);
		*पंचांगp++ = sg_page_iter_page(&piter);
	पूर्ण

	vaddr = vmap(pages, npages, VM_MAP, PAGE_KERNEL);
	vमुक्त(pages);

	अगर (!vaddr)
		वापस ERR_PTR(-ENOMEM);

	वापस vaddr;
पूर्ण

अटल पूर्णांक प्रणाली_heap_vmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;
	व्योम *vaddr;
	पूर्णांक ret = 0;

	mutex_lock(&buffer->lock);
	अगर (buffer->vmap_cnt) अणु
		buffer->vmap_cnt++;
		dma_buf_map_set_vaddr(map, buffer->vaddr);
		जाओ out;
	पूर्ण

	vaddr = प्रणाली_heap_करो_vmap(buffer);
	अगर (IS_ERR(vaddr)) अणु
		ret = PTR_ERR(vaddr);
		जाओ out;
	पूर्ण

	buffer->vaddr = vaddr;
	buffer->vmap_cnt++;
	dma_buf_map_set_vaddr(map, buffer->vaddr);
out:
	mutex_unlock(&buffer->lock);

	वापस ret;
पूर्ण

अटल व्योम प्रणाली_heap_vunmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;

	mutex_lock(&buffer->lock);
	अगर (!--buffer->vmap_cnt) अणु
		vunmap(buffer->vaddr);
		buffer->vaddr = शून्य;
	पूर्ण
	mutex_unlock(&buffer->lock);
	dma_buf_map_clear(map);
पूर्ण

अटल व्योम प्रणाली_heap_dma_buf_release(काष्ठा dma_buf *dmabuf)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer = dmabuf->priv;
	काष्ठा sg_table *table;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	table = &buffer->sg_table;
	क्रम_each_sg(table->sgl, sg, table->nents, i) अणु
		काष्ठा page *page = sg_page(sg);

		__मुक्त_pages(page, compound_order(page));
	पूर्ण
	sg_मुक्त_table(table);
	kमुक्त(buffer);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops प्रणाली_heap_buf_ops = अणु
	.attach = प्रणाली_heap_attach,
	.detach = प्रणाली_heap_detach,
	.map_dma_buf = प्रणाली_heap_map_dma_buf,
	.unmap_dma_buf = प्रणाली_heap_unmap_dma_buf,
	.begin_cpu_access = प्रणाली_heap_dma_buf_begin_cpu_access,
	.end_cpu_access = प्रणाली_heap_dma_buf_end_cpu_access,
	.mmap = प्रणाली_heap_mmap,
	.vmap = प्रणाली_heap_vmap,
	.vunmap = प्रणाली_heap_vunmap,
	.release = प्रणाली_heap_dma_buf_release,
पूर्ण;

अटल काष्ठा page *alloc_largest_available(अचिन्हित दीर्घ size,
					    अचिन्हित पूर्णांक max_order)
अणु
	काष्ठा page *page;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_ORDERS; i++) अणु
		अगर (size <  (PAGE_SIZE << orders[i]))
			जारी;
		अगर (max_order < orders[i])
			जारी;

		page = alloc_pages(order_flags[i], orders[i]);
		अगर (!page)
			जारी;
		वापस page;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_buf *प्रणाली_heap_allocate(काष्ठा dma_heap *heap,
					    अचिन्हित दीर्घ len,
					    अचिन्हित दीर्घ fd_flags,
					    अचिन्हित दीर्घ heap_flags)
अणु
	काष्ठा प्रणाली_heap_buffer *buffer;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	अचिन्हित दीर्घ size_reमुख्यing = len;
	अचिन्हित पूर्णांक max_order = orders[0];
	काष्ठा dma_buf *dmabuf;
	काष्ठा sg_table *table;
	काष्ठा scatterlist *sg;
	काष्ठा list_head pages;
	काष्ठा page *page, *पंचांगp_page;
	पूर्णांक i, ret = -ENOMEM;

	buffer = kzalloc(माप(*buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&buffer->attachments);
	mutex_init(&buffer->lock);
	buffer->heap = heap;
	buffer->len = len;

	INIT_LIST_HEAD(&pages);
	i = 0;
	जबतक (size_reमुख्यing > 0) अणु
		/*
		 * Aव्योम trying to allocate memory अगर the process
		 * has been समाप्तed by SIGKILL
		 */
		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			जाओ मुक्त_buffer;
		पूर्ण

		page = alloc_largest_available(size_reमुख्यing, max_order);
		अगर (!page)
			जाओ मुक्त_buffer;

		list_add_tail(&page->lru, &pages);
		size_reमुख्यing -= page_size(page);
		max_order = compound_order(page);
		i++;
	पूर्ण

	table = &buffer->sg_table;
	अगर (sg_alloc_table(table, i, GFP_KERNEL))
		जाओ मुक्त_buffer;

	sg = table->sgl;
	list_क्रम_each_entry_safe(page, पंचांगp_page, &pages, lru) अणु
		sg_set_page(sg, page, page_size(page), 0);
		sg = sg_next(sg);
		list_del(&page->lru);
	पूर्ण

	/* create the dmabuf */
	exp_info.exp_name = dma_heap_get_name(heap);
	exp_info.ops = &प्रणाली_heap_buf_ops;
	exp_info.size = buffer->len;
	exp_info.flags = fd_flags;
	exp_info.priv = buffer;
	dmabuf = dma_buf_export(&exp_info);
	अगर (IS_ERR(dmabuf)) अणु
		ret = PTR_ERR(dmabuf);
		जाओ मुक्त_pages;
	पूर्ण
	वापस dmabuf;

मुक्त_pages:
	क्रम_each_sgtable_sg(table, sg, i) अणु
		काष्ठा page *p = sg_page(sg);

		__मुक्त_pages(p, compound_order(p));
	पूर्ण
	sg_मुक्त_table(table);
मुक्त_buffer:
	list_क्रम_each_entry_safe(page, पंचांगp_page, &pages, lru)
		__मुक्त_pages(page, compound_order(page));
	kमुक्त(buffer);

	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा dma_heap_ops प्रणाली_heap_ops = अणु
	.allocate = प्रणाली_heap_allocate,
पूर्ण;

अटल पूर्णांक प्रणाली_heap_create(व्योम)
अणु
	काष्ठा dma_heap_export_info exp_info;

	exp_info.name = "system";
	exp_info.ops = &प्रणाली_heap_ops;
	exp_info.priv = शून्य;

	sys_heap = dma_heap_add(&exp_info);
	अगर (IS_ERR(sys_heap))
		वापस PTR_ERR(sys_heap);

	वापस 0;
पूर्ण
module_init(प्रणाली_heap_create);
MODULE_LICENSE("GPL v2");
