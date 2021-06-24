<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DMABUF CMA heap exporter
 *
 * Copyright (C) 2012, 2019, 2020 Linaro Ltd.
 * Author: <benjamin.gaignard@linaro.org> क्रम ST-Ericsson.
 *
 * Also utilizing parts of Andrew Davis' SRAM heap:
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */
#समावेश <linux/cma.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-heap.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/err.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>


काष्ठा cma_heap अणु
	काष्ठा dma_heap *heap;
	काष्ठा cma *cma;
पूर्ण;

काष्ठा cma_heap_buffer अणु
	काष्ठा cma_heap *heap;
	काष्ठा list_head attachments;
	काष्ठा mutex lock;
	अचिन्हित दीर्घ len;
	काष्ठा page *cma_pages;
	काष्ठा page **pages;
	pgoff_t pagecount;
	पूर्णांक vmap_cnt;
	व्योम *vaddr;
पूर्ण;

काष्ठा dma_heap_attachment अणु
	काष्ठा device *dev;
	काष्ठा sg_table table;
	काष्ठा list_head list;
	bool mapped;
पूर्ण;

अटल पूर्णांक cma_heap_attach(काष्ठा dma_buf *dmabuf,
			   काष्ठा dma_buf_attachment *attachment)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a;
	पूर्णांक ret;

	a = kzalloc(माप(*a), GFP_KERNEL);
	अगर (!a)
		वापस -ENOMEM;

	ret = sg_alloc_table_from_pages(&a->table, buffer->pages,
					buffer->pagecount, 0,
					buffer->pagecount << PAGE_SHIFT,
					GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(a);
		वापस ret;
	पूर्ण

	a->dev = attachment->dev;
	INIT_LIST_HEAD(&a->list);
	a->mapped = false;

	attachment->priv = a;

	mutex_lock(&buffer->lock);
	list_add(&a->list, &buffer->attachments);
	mutex_unlock(&buffer->lock);

	वापस 0;
पूर्ण

अटल व्योम cma_heap_detach(काष्ठा dma_buf *dmabuf,
			    काष्ठा dma_buf_attachment *attachment)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a = attachment->priv;

	mutex_lock(&buffer->lock);
	list_del(&a->list);
	mutex_unlock(&buffer->lock);

	sg_मुक्त_table(&a->table);
	kमुक्त(a);
पूर्ण

अटल काष्ठा sg_table *cma_heap_map_dma_buf(काष्ठा dma_buf_attachment *attachment,
					     क्रमागत dma_data_direction direction)
अणु
	काष्ठा dma_heap_attachment *a = attachment->priv;
	काष्ठा sg_table *table = &a->table;
	पूर्णांक ret;

	ret = dma_map_sgtable(attachment->dev, table, direction, 0);
	अगर (ret)
		वापस ERR_PTR(-ENOMEM);
	a->mapped = true;
	वापस table;
पूर्ण

अटल व्योम cma_heap_unmap_dma_buf(काष्ठा dma_buf_attachment *attachment,
				   काष्ठा sg_table *table,
				   क्रमागत dma_data_direction direction)
अणु
	काष्ठा dma_heap_attachment *a = attachment->priv;

	a->mapped = false;
	dma_unmap_sgtable(attachment->dev, table, direction, 0);
पूर्ण

अटल पूर्णांक cma_heap_dma_buf_begin_cpu_access(काष्ठा dma_buf *dmabuf,
					     क्रमागत dma_data_direction direction)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a;

	अगर (buffer->vmap_cnt)
		invalidate_kernel_vmap_range(buffer->vaddr, buffer->len);

	mutex_lock(&buffer->lock);
	list_क्रम_each_entry(a, &buffer->attachments, list) अणु
		अगर (!a->mapped)
			जारी;
		dma_sync_sgtable_क्रम_cpu(a->dev, &a->table, direction);
	पूर्ण
	mutex_unlock(&buffer->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक cma_heap_dma_buf_end_cpu_access(काष्ठा dma_buf *dmabuf,
					   क्रमागत dma_data_direction direction)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;
	काष्ठा dma_heap_attachment *a;

	अगर (buffer->vmap_cnt)
		flush_kernel_vmap_range(buffer->vaddr, buffer->len);

	mutex_lock(&buffer->lock);
	list_क्रम_each_entry(a, &buffer->attachments, list) अणु
		अगर (!a->mapped)
			जारी;
		dma_sync_sgtable_क्रम_device(a->dev, &a->table, direction);
	पूर्ण
	mutex_unlock(&buffer->lock);

	वापस 0;
पूर्ण

अटल vm_fault_t cma_heap_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा cma_heap_buffer *buffer = vma->vm_निजी_data;

	अगर (vmf->pgoff > buffer->pagecount)
		वापस VM_FAULT_SIGBUS;

	vmf->page = buffer->pages[vmf->pgoff];
	get_page(vmf->page);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा dma_heap_vm_ops = अणु
	.fault = cma_heap_vm_fault,
पूर्ण;

अटल पूर्णांक cma_heap_mmap(काष्ठा dma_buf *dmabuf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;

	अगर ((vma->vm_flags & (VM_SHARED | VM_MAYSHARE)) == 0)
		वापस -EINVAL;

	vma->vm_ops = &dma_heap_vm_ops;
	vma->vm_निजी_data = buffer;

	वापस 0;
पूर्ण

अटल व्योम *cma_heap_करो_vmap(काष्ठा cma_heap_buffer *buffer)
अणु
	व्योम *vaddr;

	vaddr = vmap(buffer->pages, buffer->pagecount, VM_MAP, PAGE_KERNEL);
	अगर (!vaddr)
		वापस ERR_PTR(-ENOMEM);

	वापस vaddr;
पूर्ण

अटल पूर्णांक cma_heap_vmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;
	व्योम *vaddr;
	पूर्णांक ret = 0;

	mutex_lock(&buffer->lock);
	अगर (buffer->vmap_cnt) अणु
		buffer->vmap_cnt++;
		dma_buf_map_set_vaddr(map, buffer->vaddr);
		जाओ out;
	पूर्ण

	vaddr = cma_heap_करो_vmap(buffer);
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

अटल व्योम cma_heap_vunmap(काष्ठा dma_buf *dmabuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;

	mutex_lock(&buffer->lock);
	अगर (!--buffer->vmap_cnt) अणु
		vunmap(buffer->vaddr);
		buffer->vaddr = शून्य;
	पूर्ण
	mutex_unlock(&buffer->lock);
	dma_buf_map_clear(map);
पूर्ण

अटल व्योम cma_heap_dma_buf_release(काष्ठा dma_buf *dmabuf)
अणु
	काष्ठा cma_heap_buffer *buffer = dmabuf->priv;
	काष्ठा cma_heap *cma_heap = buffer->heap;

	अगर (buffer->vmap_cnt > 0) अणु
		WARN(1, "%s: buffer still mapped in the kernel\n", __func__);
		vunmap(buffer->vaddr);
		buffer->vaddr = शून्य;
	पूर्ण

	/* मुक्त page list */
	kमुक्त(buffer->pages);
	/* release memory */
	cma_release(cma_heap->cma, buffer->cma_pages, buffer->pagecount);
	kमुक्त(buffer);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops cma_heap_buf_ops = अणु
	.attach = cma_heap_attach,
	.detach = cma_heap_detach,
	.map_dma_buf = cma_heap_map_dma_buf,
	.unmap_dma_buf = cma_heap_unmap_dma_buf,
	.begin_cpu_access = cma_heap_dma_buf_begin_cpu_access,
	.end_cpu_access = cma_heap_dma_buf_end_cpu_access,
	.mmap = cma_heap_mmap,
	.vmap = cma_heap_vmap,
	.vunmap = cma_heap_vunmap,
	.release = cma_heap_dma_buf_release,
पूर्ण;

अटल काष्ठा dma_buf *cma_heap_allocate(काष्ठा dma_heap *heap,
					 अचिन्हित दीर्घ len,
					 अचिन्हित दीर्घ fd_flags,
					 अचिन्हित दीर्घ heap_flags)
अणु
	काष्ठा cma_heap *cma_heap = dma_heap_get_drvdata(heap);
	काष्ठा cma_heap_buffer *buffer;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	माप_प्रकार size = PAGE_ALIGN(len);
	pgoff_t pagecount = size >> PAGE_SHIFT;
	अचिन्हित दीर्घ align = get_order(size);
	काष्ठा page *cma_pages;
	काष्ठा dma_buf *dmabuf;
	पूर्णांक ret = -ENOMEM;
	pgoff_t pg;

	buffer = kzalloc(माप(*buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&buffer->attachments);
	mutex_init(&buffer->lock);
	buffer->len = size;

	अगर (align > CONFIG_CMA_ALIGNMENT)
		align = CONFIG_CMA_ALIGNMENT;

	cma_pages = cma_alloc(cma_heap->cma, pagecount, align, false);
	अगर (!cma_pages)
		जाओ मुक्त_buffer;

	/* Clear the cma pages */
	अगर (PageHighMem(cma_pages)) अणु
		अचिन्हित दीर्घ nr_clear_pages = pagecount;
		काष्ठा page *page = cma_pages;

		जबतक (nr_clear_pages > 0) अणु
			व्योम *vaddr = kmap_atomic(page);

			स_रखो(vaddr, 0, PAGE_SIZE);
			kunmap_atomic(vaddr);
			/*
			 * Aव्योम wasting समय zeroing memory अगर the process
			 * has been समाप्तed by by SIGKILL
			 */
			अगर (fatal_संकेत_pending(current))
				जाओ मुक्त_cma;
			page++;
			nr_clear_pages--;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(page_address(cma_pages), 0, size);
	पूर्ण

	buffer->pages = kदो_स्मृति_array(pagecount, माप(*buffer->pages), GFP_KERNEL);
	अगर (!buffer->pages) अणु
		ret = -ENOMEM;
		जाओ मुक्त_cma;
	पूर्ण

	क्रम (pg = 0; pg < pagecount; pg++)
		buffer->pages[pg] = &cma_pages[pg];

	buffer->cma_pages = cma_pages;
	buffer->heap = cma_heap;
	buffer->pagecount = pagecount;

	/* create the dmabuf */
	exp_info.exp_name = dma_heap_get_name(heap);
	exp_info.ops = &cma_heap_buf_ops;
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
	kमुक्त(buffer->pages);
मुक्त_cma:
	cma_release(cma_heap->cma, cma_pages, pagecount);
मुक्त_buffer:
	kमुक्त(buffer);

	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा dma_heap_ops cma_heap_ops = अणु
	.allocate = cma_heap_allocate,
पूर्ण;

अटल पूर्णांक __add_cma_heap(काष्ठा cma *cma, व्योम *data)
अणु
	काष्ठा cma_heap *cma_heap;
	काष्ठा dma_heap_export_info exp_info;

	cma_heap = kzalloc(माप(*cma_heap), GFP_KERNEL);
	अगर (!cma_heap)
		वापस -ENOMEM;
	cma_heap->cma = cma;

	exp_info.name = cma_get_name(cma);
	exp_info.ops = &cma_heap_ops;
	exp_info.priv = cma_heap;

	cma_heap->heap = dma_heap_add(&exp_info);
	अगर (IS_ERR(cma_heap->heap)) अणु
		पूर्णांक ret = PTR_ERR(cma_heap->heap);

		kमुक्त(cma_heap);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक add_शेष_cma_heap(व्योम)
अणु
	काष्ठा cma *शेष_cma = dev_get_cma_area(शून्य);
	पूर्णांक ret = 0;

	अगर (शेष_cma)
		ret = __add_cma_heap(शेष_cma, शून्य);

	वापस ret;
पूर्ण
module_init(add_शेष_cma_heap);
MODULE_DESCRIPTION("DMA-BUF CMA Heap");
MODULE_LICENSE("GPL v2");
