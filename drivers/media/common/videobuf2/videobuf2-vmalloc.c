<शैली गुरु>
/*
 * videobuf2-vदो_स्मृति.c - vदो_स्मृति memory allocator क्रम videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/refcount.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/videobuf2-memops.h>

काष्ठा vb2_vदो_स्मृति_buf अणु
	व्योम				*vaddr;
	काष्ठा frame_vector		*vec;
	क्रमागत dma_data_direction		dma_dir;
	अचिन्हित दीर्घ			size;
	refcount_t			refcount;
	काष्ठा vb2_vmarea_handler	handler;
	काष्ठा dma_buf			*dbuf;
पूर्ण;

अटल व्योम vb2_vदो_स्मृति_put(व्योम *buf_priv);

अटल व्योम *vb2_vदो_स्मृति_alloc(काष्ठा device *dev, अचिन्हित दीर्घ attrs,
			       अचिन्हित दीर्घ size, क्रमागत dma_data_direction dma_dir,
			       gfp_t gfp_flags)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf;

	buf = kzalloc(माप(*buf), GFP_KERNEL | gfp_flags);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->size = size;
	buf->vaddr = vदो_स्मृति_user(buf->size);
	अगर (!buf->vaddr) अणु
		pr_debug("vmalloc of size %ld failed\n", buf->size);
		kमुक्त(buf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	buf->dma_dir = dma_dir;
	buf->handler.refcount = &buf->refcount;
	buf->handler.put = vb2_vदो_स्मृति_put;
	buf->handler.arg = buf;

	refcount_set(&buf->refcount, 1);
	वापस buf;
पूर्ण

अटल व्योम vb2_vदो_स्मृति_put(व्योम *buf_priv)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = buf_priv;

	अगर (refcount_dec_and_test(&buf->refcount)) अणु
		vमुक्त(buf->vaddr);
		kमुक्त(buf);
	पूर्ण
पूर्ण

अटल व्योम *vb2_vदो_स्मृति_get_userptr(काष्ठा device *dev, अचिन्हित दीर्घ vaddr,
				     अचिन्हित दीर्घ size,
				     क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf;
	काष्ठा frame_vector *vec;
	पूर्णांक n_pages, offset, i;
	पूर्णांक ret = -ENOMEM;

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->dma_dir = dma_dir;
	offset = vaddr & ~PAGE_MASK;
	buf->size = size;
	vec = vb2_create_framevec(vaddr, size);
	अगर (IS_ERR(vec)) अणु
		ret = PTR_ERR(vec);
		जाओ fail_pfnvec_create;
	पूर्ण
	buf->vec = vec;
	n_pages = frame_vector_count(vec);
	अगर (frame_vector_to_pages(vec) < 0) अणु
		अचिन्हित दीर्घ *nums = frame_vector_pfns(vec);

		/*
		 * We cannot get page poपूर्णांकers क्रम these pfns. Check memory is
		 * physically contiguous and use direct mapping.
		 */
		क्रम (i = 1; i < n_pages; i++)
			अगर (nums[i-1] + 1 != nums[i])
				जाओ fail_map;
		buf->vaddr = (__क्रमce व्योम *)
			ioremap(__pfn_to_phys(nums[0]), size + offset);
	पूर्ण अन्यथा अणु
		buf->vaddr = vm_map_ram(frame_vector_pages(vec), n_pages, -1);
	पूर्ण

	अगर (!buf->vaddr)
		जाओ fail_map;
	buf->vaddr += offset;
	वापस buf;

fail_map:
	vb2_destroy_framevec(vec);
fail_pfnvec_create:
	kमुक्त(buf);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम vb2_vदो_स्मृति_put_userptr(व्योम *buf_priv)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = buf_priv;
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)buf->vaddr & PAGE_MASK;
	अचिन्हित पूर्णांक i;
	काष्ठा page **pages;
	अचिन्हित पूर्णांक n_pages;

	अगर (!buf->vec->is_pfns) अणु
		n_pages = frame_vector_count(buf->vec);
		pages = frame_vector_pages(buf->vec);
		अगर (vaddr)
			vm_unmap_ram((व्योम *)vaddr, n_pages);
		अगर (buf->dma_dir == DMA_FROM_DEVICE ||
		    buf->dma_dir == DMA_BIसूचीECTIONAL)
			क्रम (i = 0; i < n_pages; i++)
				set_page_dirty_lock(pages[i]);
	पूर्ण अन्यथा अणु
		iounmap((__क्रमce व्योम __iomem *)buf->vaddr);
	पूर्ण
	vb2_destroy_framevec(buf->vec);
	kमुक्त(buf);
पूर्ण

अटल व्योम *vb2_vदो_स्मृति_vaddr(व्योम *buf_priv)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = buf_priv;

	अगर (!buf->vaddr) अणु
		pr_err("Address of an unallocated plane requested or cannot map user pointer\n");
		वापस शून्य;
	पूर्ण

	वापस buf->vaddr;
पूर्ण

अटल अचिन्हित पूर्णांक vb2_vदो_स्मृति_num_users(व्योम *buf_priv)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = buf_priv;
	वापस refcount_पढ़ो(&buf->refcount);
पूर्ण

अटल पूर्णांक vb2_vदो_स्मृति_mmap(व्योम *buf_priv, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = buf_priv;
	पूर्णांक ret;

	अगर (!buf) अणु
		pr_err("No memory to map\n");
		वापस -EINVAL;
	पूर्ण

	ret = remap_vदो_स्मृति_range(vma, buf->vaddr, 0);
	अगर (ret) अणु
		pr_err("Remapping vmalloc memory, error: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Make sure that vm_areas क्रम 2 buffers won't be merged together
	 */
	vma->vm_flags		|= VM_DONTEXPAND;

	/*
	 * Use common vm_area operations to track buffer refcount.
	 */
	vma->vm_निजी_data	= &buf->handler;
	vma->vm_ops		= &vb2_common_vm_ops;

	vma->vm_ops->खोलो(vma);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HAS_DMA
/*********************************************/
/*         DMABUF ops क्रम exporters          */
/*********************************************/

काष्ठा vb2_vदो_स्मृति_attachment अणु
	काष्ठा sg_table sgt;
	क्रमागत dma_data_direction dma_dir;
पूर्ण;

अटल पूर्णांक vb2_vदो_स्मृति_dmabuf_ops_attach(काष्ठा dma_buf *dbuf,
	काष्ठा dma_buf_attachment *dbuf_attach)
अणु
	काष्ठा vb2_vदो_स्मृति_attachment *attach;
	काष्ठा vb2_vदो_स्मृति_buf *buf = dbuf->priv;
	पूर्णांक num_pages = PAGE_ALIGN(buf->size) / PAGE_SIZE;
	काष्ठा sg_table *sgt;
	काष्ठा scatterlist *sg;
	व्योम *vaddr = buf->vaddr;
	पूर्णांक ret;
	पूर्णांक i;

	attach = kzalloc(माप(*attach), GFP_KERNEL);
	अगर (!attach)
		वापस -ENOMEM;

	sgt = &attach->sgt;
	ret = sg_alloc_table(sgt, num_pages, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(attach);
		वापस ret;
	पूर्ण
	क्रम_each_sgtable_sg(sgt, sg, i) अणु
		काष्ठा page *page = vदो_स्मृति_to_page(vaddr);

		अगर (!page) अणु
			sg_मुक्त_table(sgt);
			kमुक्त(attach);
			वापस -ENOMEM;
		पूर्ण
		sg_set_page(sg, page, PAGE_SIZE, 0);
		vaddr += PAGE_SIZE;
	पूर्ण

	attach->dma_dir = DMA_NONE;
	dbuf_attach->priv = attach;
	वापस 0;
पूर्ण

अटल व्योम vb2_vदो_स्मृति_dmabuf_ops_detach(काष्ठा dma_buf *dbuf,
	काष्ठा dma_buf_attachment *db_attach)
अणु
	काष्ठा vb2_vदो_स्मृति_attachment *attach = db_attach->priv;
	काष्ठा sg_table *sgt;

	अगर (!attach)
		वापस;

	sgt = &attach->sgt;

	/* release the scatterlist cache */
	अगर (attach->dma_dir != DMA_NONE)
		dma_unmap_sgtable(db_attach->dev, sgt, attach->dma_dir, 0);
	sg_मुक्त_table(sgt);
	kमुक्त(attach);
	db_attach->priv = शून्य;
पूर्ण

अटल काष्ठा sg_table *vb2_vदो_स्मृति_dmabuf_ops_map(
	काष्ठा dma_buf_attachment *db_attach, क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_vदो_स्मृति_attachment *attach = db_attach->priv;
	/* stealing dmabuf mutex to serialize map/unmap operations */
	काष्ठा mutex *lock = &db_attach->dmabuf->lock;
	काष्ठा sg_table *sgt;

	mutex_lock(lock);

	sgt = &attach->sgt;
	/* वापस previously mapped sg table */
	अगर (attach->dma_dir == dma_dir) अणु
		mutex_unlock(lock);
		वापस sgt;
	पूर्ण

	/* release any previous cache */
	अगर (attach->dma_dir != DMA_NONE) अणु
		dma_unmap_sgtable(db_attach->dev, sgt, attach->dma_dir, 0);
		attach->dma_dir = DMA_NONE;
	पूर्ण

	/* mapping to the client with new direction */
	अगर (dma_map_sgtable(db_attach->dev, sgt, dma_dir, 0)) अणु
		pr_err("failed to map scatterlist\n");
		mutex_unlock(lock);
		वापस ERR_PTR(-EIO);
	पूर्ण

	attach->dma_dir = dma_dir;

	mutex_unlock(lock);

	वापस sgt;
पूर्ण

अटल व्योम vb2_vदो_स्मृति_dmabuf_ops_unmap(काष्ठा dma_buf_attachment *db_attach,
	काष्ठा sg_table *sgt, क्रमागत dma_data_direction dma_dir)
अणु
	/* nothing to be करोne here */
पूर्ण

अटल व्योम vb2_vदो_स्मृति_dmabuf_ops_release(काष्ठा dma_buf *dbuf)
अणु
	/* drop reference obtained in vb2_vदो_स्मृति_get_dmabuf */
	vb2_vदो_स्मृति_put(dbuf->priv);
पूर्ण

अटल पूर्णांक vb2_vदो_स्मृति_dmabuf_ops_vmap(काष्ठा dma_buf *dbuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = dbuf->priv;

	dma_buf_map_set_vaddr(map, buf->vaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक vb2_vदो_स्मृति_dmabuf_ops_mmap(काष्ठा dma_buf *dbuf,
	काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vb2_vदो_स्मृति_mmap(dbuf->priv, vma);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops vb2_vदो_स्मृति_dmabuf_ops = अणु
	.attach = vb2_vदो_स्मृति_dmabuf_ops_attach,
	.detach = vb2_vदो_स्मृति_dmabuf_ops_detach,
	.map_dma_buf = vb2_vदो_स्मृति_dmabuf_ops_map,
	.unmap_dma_buf = vb2_vदो_स्मृति_dmabuf_ops_unmap,
	.vmap = vb2_vदो_स्मृति_dmabuf_ops_vmap,
	.mmap = vb2_vदो_स्मृति_dmabuf_ops_mmap,
	.release = vb2_vदो_स्मृति_dmabuf_ops_release,
पूर्ण;

अटल काष्ठा dma_buf *vb2_vदो_स्मृति_get_dmabuf(व्योम *buf_priv, अचिन्हित दीर्घ flags)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = buf_priv;
	काष्ठा dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &vb2_vदो_स्मृति_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.flags = flags;
	exp_info.priv = buf;

	अगर (WARN_ON(!buf->vaddr))
		वापस शून्य;

	dbuf = dma_buf_export(&exp_info);
	अगर (IS_ERR(dbuf))
		वापस शून्य;

	/* dmabuf keeps reference to vb2 buffer */
	refcount_inc(&buf->refcount);

	वापस dbuf;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAS_DMA */


/*********************************************/
/*       callbacks क्रम DMABUF buffers        */
/*********************************************/

अटल पूर्णांक vb2_vदो_स्मृति_map_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = mem_priv;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	ret = dma_buf_vmap(buf->dbuf, &map);
	अगर (ret)
		वापस -EFAULT;
	buf->vaddr = map.vaddr;

	वापस 0;
पूर्ण

अटल व्योम vb2_vदो_स्मृति_unmap_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = mem_priv;
	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(buf->vaddr);

	dma_buf_vunmap(buf->dbuf, &map);
	buf->vaddr = शून्य;
पूर्ण

अटल व्योम vb2_vदो_स्मृति_detach_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf = mem_priv;
	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(buf->vaddr);

	अगर (buf->vaddr)
		dma_buf_vunmap(buf->dbuf, &map);

	kमुक्त(buf);
पूर्ण

अटल व्योम *vb2_vदो_स्मृति_attach_dmabuf(काष्ठा device *dev, काष्ठा dma_buf *dbuf,
	अचिन्हित दीर्घ size, क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_vदो_स्मृति_buf *buf;

	अगर (dbuf->size < size)
		वापस ERR_PTR(-EFAULT);

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->dbuf = dbuf;
	buf->dma_dir = dma_dir;
	buf->size = size;

	वापस buf;
पूर्ण


स्थिर काष्ठा vb2_mem_ops vb2_vदो_स्मृति_memops = अणु
	.alloc		= vb2_vदो_स्मृति_alloc,
	.put		= vb2_vदो_स्मृति_put,
	.get_userptr	= vb2_vदो_स्मृति_get_userptr,
	.put_userptr	= vb2_vदो_स्मृति_put_userptr,
#अगर_घोषित CONFIG_HAS_DMA
	.get_dmabuf	= vb2_vदो_स्मृति_get_dmabuf,
#पूर्ण_अगर
	.map_dmabuf	= vb2_vदो_स्मृति_map_dmabuf,
	.unmap_dmabuf	= vb2_vदो_स्मृति_unmap_dmabuf,
	.attach_dmabuf	= vb2_vदो_स्मृति_attach_dmabuf,
	.detach_dmabuf	= vb2_vदो_स्मृति_detach_dmabuf,
	.vaddr		= vb2_vदो_स्मृति_vaddr,
	.mmap		= vb2_vदो_स्मृति_mmap,
	.num_users	= vb2_vदो_स्मृति_num_users,
पूर्ण;
EXPORT_SYMBOL_GPL(vb2_vदो_स्मृति_memops);

MODULE_DESCRIPTION("vmalloc memory handling routines for videobuf2");
MODULE_AUTHOR("Pawel Osciak <pawel@osciak.com>");
MODULE_LICENSE("GPL");
