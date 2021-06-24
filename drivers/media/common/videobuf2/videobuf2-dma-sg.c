<शैली गुरु>
/*
 * videobuf2-dma-sg.c - dma scatter/gather memory allocator क्रम videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/refcount.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-memops.h>
#समावेश <media/videobuf2-dma-sg.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

#घोषणा dprपूर्णांकk(level, fmt, arg...)					\
	करो अणु								\
		अगर (debug >= level)					\
			prपूर्णांकk(KERN_DEBUG "vb2-dma-sg: " fmt, ## arg);	\
	पूर्ण जबतक (0)

काष्ठा vb2_dma_sg_buf अणु
	काष्ठा device			*dev;
	व्योम				*vaddr;
	काष्ठा page			**pages;
	काष्ठा frame_vector		*vec;
	पूर्णांक				offset;
	क्रमागत dma_data_direction		dma_dir;
	काष्ठा sg_table			sg_table;
	/*
	 * This will poपूर्णांक to sg_table when used with the MMAP or USERPTR
	 * memory model, and to the dma_buf sglist when used with the
	 * DMABUF memory model.
	 */
	काष्ठा sg_table			*dma_sgt;
	माप_प्रकार				size;
	अचिन्हित पूर्णांक			num_pages;
	refcount_t			refcount;
	काष्ठा vb2_vmarea_handler	handler;

	काष्ठा dma_buf_attachment	*db_attach;
पूर्ण;

अटल व्योम vb2_dma_sg_put(व्योम *buf_priv);

अटल पूर्णांक vb2_dma_sg_alloc_compacted(काष्ठा vb2_dma_sg_buf *buf,
		gfp_t gfp_flags)
अणु
	अचिन्हित पूर्णांक last_page = 0;
	अचिन्हित दीर्घ size = buf->size;

	जबतक (size > 0) अणु
		काष्ठा page *pages;
		पूर्णांक order;
		पूर्णांक i;

		order = get_order(size);
		/* Don't over allocate*/
		अगर ((PAGE_SIZE << order) > size)
			order--;

		pages = शून्य;
		जबतक (!pages) अणु
			pages = alloc_pages(GFP_KERNEL | __GFP_ZERO |
					__GFP_NOWARN | gfp_flags, order);
			अगर (pages)
				अवरोध;

			अगर (order == 0) अणु
				जबतक (last_page--)
					__मुक्त_page(buf->pages[last_page]);
				वापस -ENOMEM;
			पूर्ण
			order--;
		पूर्ण

		split_page(pages, order);
		क्रम (i = 0; i < (1 << order); i++)
			buf->pages[last_page++] = &pages[i];

		size -= PAGE_SIZE << order;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *vb2_dma_sg_alloc(काष्ठा device *dev, अचिन्हित दीर्घ dma_attrs,
			      अचिन्हित दीर्घ size, क्रमागत dma_data_direction dma_dir,
			      gfp_t gfp_flags)
अणु
	काष्ठा vb2_dma_sg_buf *buf;
	काष्ठा sg_table *sgt;
	पूर्णांक ret;
	पूर्णांक num_pages;

	अगर (WARN_ON(!dev) || WARN_ON(!size))
		वापस ERR_PTR(-EINVAL);

	buf = kzalloc(माप *buf, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->vaddr = शून्य;
	buf->dma_dir = dma_dir;
	buf->offset = 0;
	buf->size = size;
	/* size is alपढ़ोy page aligned */
	buf->num_pages = size >> PAGE_SHIFT;
	buf->dma_sgt = &buf->sg_table;

	/*
	 * NOTE: dma-sg allocates memory using the page allocator directly, so
	 * there is no memory consistency guarantee, hence dma-sg ignores DMA
	 * attributes passed from the upper layer.
	 */
	buf->pages = kvदो_स्मृति_array(buf->num_pages, माप(काष्ठा page *),
				    GFP_KERNEL | __GFP_ZERO);
	अगर (!buf->pages)
		जाओ fail_pages_array_alloc;

	ret = vb2_dma_sg_alloc_compacted(buf, gfp_flags);
	अगर (ret)
		जाओ fail_pages_alloc;

	ret = sg_alloc_table_from_pages(buf->dma_sgt, buf->pages,
			buf->num_pages, 0, size, GFP_KERNEL);
	अगर (ret)
		जाओ fail_table_alloc;

	/* Prevent the device from being released जबतक the buffer is used */
	buf->dev = get_device(dev);

	sgt = &buf->sg_table;
	/*
	 * No need to sync to the device, this will happen later when the
	 * prepare() memop is called.
	 */
	अगर (dma_map_sgtable(buf->dev, sgt, buf->dma_dir,
			    DMA_ATTR_SKIP_CPU_SYNC))
		जाओ fail_map;

	buf->handler.refcount = &buf->refcount;
	buf->handler.put = vb2_dma_sg_put;
	buf->handler.arg = buf;

	refcount_set(&buf->refcount, 1);

	dprपूर्णांकk(1, "%s: Allocated buffer of %d pages\n",
		__func__, buf->num_pages);
	वापस buf;

fail_map:
	put_device(buf->dev);
	sg_मुक्त_table(buf->dma_sgt);
fail_table_alloc:
	num_pages = buf->num_pages;
	जबतक (num_pages--)
		__मुक्त_page(buf->pages[num_pages]);
fail_pages_alloc:
	kvमुक्त(buf->pages);
fail_pages_array_alloc:
	kमुक्त(buf);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम vb2_dma_sg_put(व्योम *buf_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;
	काष्ठा sg_table *sgt = &buf->sg_table;
	पूर्णांक i = buf->num_pages;

	अगर (refcount_dec_and_test(&buf->refcount)) अणु
		dprपूर्णांकk(1, "%s: Freeing buffer of %d pages\n", __func__,
			buf->num_pages);
		dma_unmap_sgtable(buf->dev, sgt, buf->dma_dir,
				  DMA_ATTR_SKIP_CPU_SYNC);
		अगर (buf->vaddr)
			vm_unmap_ram(buf->vaddr, buf->num_pages);
		sg_मुक्त_table(buf->dma_sgt);
		जबतक (--i >= 0)
			__मुक्त_page(buf->pages[i]);
		kvमुक्त(buf->pages);
		put_device(buf->dev);
		kमुक्त(buf);
	पूर्ण
पूर्ण

अटल व्योम vb2_dma_sg_prepare(व्योम *buf_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;

	dma_sync_sgtable_क्रम_device(buf->dev, sgt, buf->dma_dir);
पूर्ण

अटल व्योम vb2_dma_sg_finish(व्योम *buf_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;

	dma_sync_sgtable_क्रम_cpu(buf->dev, sgt, buf->dma_dir);
पूर्ण

अटल व्योम *vb2_dma_sg_get_userptr(काष्ठा device *dev, अचिन्हित दीर्घ vaddr,
				    अचिन्हित दीर्घ size,
				    क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_dma_sg_buf *buf;
	काष्ठा sg_table *sgt;
	काष्ठा frame_vector *vec;

	अगर (WARN_ON(!dev))
		वापस ERR_PTR(-EINVAL);

	buf = kzalloc(माप *buf, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->vaddr = शून्य;
	buf->dev = dev;
	buf->dma_dir = dma_dir;
	buf->offset = vaddr & ~PAGE_MASK;
	buf->size = size;
	buf->dma_sgt = &buf->sg_table;
	vec = vb2_create_framevec(vaddr, size);
	अगर (IS_ERR(vec))
		जाओ userptr_fail_pfnvec;
	buf->vec = vec;

	buf->pages = frame_vector_pages(vec);
	अगर (IS_ERR(buf->pages))
		जाओ userptr_fail_sgtable;
	buf->num_pages = frame_vector_count(vec);

	अगर (sg_alloc_table_from_pages(buf->dma_sgt, buf->pages,
			buf->num_pages, buf->offset, size, 0))
		जाओ userptr_fail_sgtable;

	sgt = &buf->sg_table;
	/*
	 * No need to sync to the device, this will happen later when the
	 * prepare() memop is called.
	 */
	अगर (dma_map_sgtable(buf->dev, sgt, buf->dma_dir,
			    DMA_ATTR_SKIP_CPU_SYNC))
		जाओ userptr_fail_map;

	वापस buf;

userptr_fail_map:
	sg_मुक्त_table(&buf->sg_table);
userptr_fail_sgtable:
	vb2_destroy_framevec(vec);
userptr_fail_pfnvec:
	kमुक्त(buf);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/*
 * @put_userptr: inक्रमm the allocator that a USERPTR buffer will no दीर्घer
 *		 be used
 */
अटल व्योम vb2_dma_sg_put_userptr(व्योम *buf_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;
	काष्ठा sg_table *sgt = &buf->sg_table;
	पूर्णांक i = buf->num_pages;

	dprपूर्णांकk(1, "%s: Releasing userspace buffer of %d pages\n",
	       __func__, buf->num_pages);
	dma_unmap_sgtable(buf->dev, sgt, buf->dma_dir, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (buf->vaddr)
		vm_unmap_ram(buf->vaddr, buf->num_pages);
	sg_मुक्त_table(buf->dma_sgt);
	अगर (buf->dma_dir == DMA_FROM_DEVICE ||
	    buf->dma_dir == DMA_BIसूचीECTIONAL)
		जबतक (--i >= 0)
			set_page_dirty_lock(buf->pages[i]);
	vb2_destroy_framevec(buf->vec);
	kमुक्त(buf);
पूर्ण

अटल व्योम *vb2_dma_sg_vaddr(व्योम *buf_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	BUG_ON(!buf);

	अगर (!buf->vaddr) अणु
		अगर (buf->db_attach) अणु
			ret = dma_buf_vmap(buf->db_attach->dmabuf, &map);
			buf->vaddr = ret ? शून्य : map.vaddr;
		पूर्ण अन्यथा अणु
			buf->vaddr = vm_map_ram(buf->pages, buf->num_pages, -1);
		पूर्ण
	पूर्ण

	/* add offset in हाल userptr is not page-aligned */
	वापस buf->vaddr ? buf->vaddr + buf->offset : शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक vb2_dma_sg_num_users(व्योम *buf_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;

	वापस refcount_पढ़ो(&buf->refcount);
पूर्ण

अटल पूर्णांक vb2_dma_sg_mmap(व्योम *buf_priv, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;
	पूर्णांक err;

	अगर (!buf) अणु
		prपूर्णांकk(KERN_ERR "No memory to map\n");
		वापस -EINVAL;
	पूर्ण

	err = vm_map_pages(vma, buf->pages, buf->num_pages);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Remapping memory, error: %d\n", err);
		वापस err;
	पूर्ण

	/*
	 * Use common vm_area operations to track buffer refcount.
	 */
	vma->vm_निजी_data	= &buf->handler;
	vma->vm_ops		= &vb2_common_vm_ops;

	vma->vm_ops->खोलो(vma);

	वापस 0;
पूर्ण

/*********************************************/
/*         DMABUF ops क्रम exporters          */
/*********************************************/

काष्ठा vb2_dma_sg_attachment अणु
	काष्ठा sg_table sgt;
	क्रमागत dma_data_direction dma_dir;
पूर्ण;

अटल पूर्णांक vb2_dma_sg_dmabuf_ops_attach(काष्ठा dma_buf *dbuf,
	काष्ठा dma_buf_attachment *dbuf_attach)
अणु
	काष्ठा vb2_dma_sg_attachment *attach;
	अचिन्हित पूर्णांक i;
	काष्ठा scatterlist *rd, *wr;
	काष्ठा sg_table *sgt;
	काष्ठा vb2_dma_sg_buf *buf = dbuf->priv;
	पूर्णांक ret;

	attach = kzalloc(माप(*attach), GFP_KERNEL);
	अगर (!attach)
		वापस -ENOMEM;

	sgt = &attach->sgt;
	/* Copy the buf->base_sgt scatter list to the attachment, as we can't
	 * map the same scatter list to multiple attachments at the same समय.
	 */
	ret = sg_alloc_table(sgt, buf->dma_sgt->orig_nents, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(attach);
		वापस -ENOMEM;
	पूर्ण

	rd = buf->dma_sgt->sgl;
	wr = sgt->sgl;
	क्रम (i = 0; i < sgt->orig_nents; ++i) अणु
		sg_set_page(wr, sg_page(rd), rd->length, rd->offset);
		rd = sg_next(rd);
		wr = sg_next(wr);
	पूर्ण

	attach->dma_dir = DMA_NONE;
	dbuf_attach->priv = attach;

	वापस 0;
पूर्ण

अटल व्योम vb2_dma_sg_dmabuf_ops_detach(काष्ठा dma_buf *dbuf,
	काष्ठा dma_buf_attachment *db_attach)
अणु
	काष्ठा vb2_dma_sg_attachment *attach = db_attach->priv;
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

अटल काष्ठा sg_table *vb2_dma_sg_dmabuf_ops_map(
	काष्ठा dma_buf_attachment *db_attach, क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_dma_sg_attachment *attach = db_attach->priv;
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

अटल व्योम vb2_dma_sg_dmabuf_ops_unmap(काष्ठा dma_buf_attachment *db_attach,
	काष्ठा sg_table *sgt, क्रमागत dma_data_direction dma_dir)
अणु
	/* nothing to be करोne here */
पूर्ण

अटल व्योम vb2_dma_sg_dmabuf_ops_release(काष्ठा dma_buf *dbuf)
अणु
	/* drop reference obtained in vb2_dma_sg_get_dmabuf */
	vb2_dma_sg_put(dbuf->priv);
पूर्ण

अटल पूर्णांक
vb2_dma_sg_dmabuf_ops_begin_cpu_access(काष्ठा dma_buf *dbuf,
				       क्रमागत dma_data_direction direction)
अणु
	काष्ठा vb2_dma_sg_buf *buf = dbuf->priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;

	dma_sync_sg_क्रम_cpu(buf->dev, sgt->sgl, sgt->nents, buf->dma_dir);
	वापस 0;
पूर्ण

अटल पूर्णांक
vb2_dma_sg_dmabuf_ops_end_cpu_access(काष्ठा dma_buf *dbuf,
				     क्रमागत dma_data_direction direction)
अणु
	काष्ठा vb2_dma_sg_buf *buf = dbuf->priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;

	dma_sync_sg_क्रम_device(buf->dev, sgt->sgl, sgt->nents, buf->dma_dir);
	वापस 0;
पूर्ण

अटल पूर्णांक vb2_dma_sg_dmabuf_ops_vmap(काष्ठा dma_buf *dbuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा vb2_dma_sg_buf *buf = dbuf->priv;

	dma_buf_map_set_vaddr(map, buf->vaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक vb2_dma_sg_dmabuf_ops_mmap(काष्ठा dma_buf *dbuf,
	काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vb2_dma_sg_mmap(dbuf->priv, vma);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops vb2_dma_sg_dmabuf_ops = अणु
	.attach = vb2_dma_sg_dmabuf_ops_attach,
	.detach = vb2_dma_sg_dmabuf_ops_detach,
	.map_dma_buf = vb2_dma_sg_dmabuf_ops_map,
	.unmap_dma_buf = vb2_dma_sg_dmabuf_ops_unmap,
	.begin_cpu_access = vb2_dma_sg_dmabuf_ops_begin_cpu_access,
	.end_cpu_access = vb2_dma_sg_dmabuf_ops_end_cpu_access,
	.vmap = vb2_dma_sg_dmabuf_ops_vmap,
	.mmap = vb2_dma_sg_dmabuf_ops_mmap,
	.release = vb2_dma_sg_dmabuf_ops_release,
पूर्ण;

अटल काष्ठा dma_buf *vb2_dma_sg_get_dmabuf(व्योम *buf_priv, अचिन्हित दीर्घ flags)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;
	काष्ठा dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &vb2_dma_sg_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.flags = flags;
	exp_info.priv = buf;

	अगर (WARN_ON(!buf->dma_sgt))
		वापस शून्य;

	dbuf = dma_buf_export(&exp_info);
	अगर (IS_ERR(dbuf))
		वापस शून्य;

	/* dmabuf keeps reference to vb2 buffer */
	refcount_inc(&buf->refcount);

	वापस dbuf;
पूर्ण

/*********************************************/
/*       callbacks क्रम DMABUF buffers        */
/*********************************************/

अटल पूर्णांक vb2_dma_sg_map_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = mem_priv;
	काष्ठा sg_table *sgt;

	अगर (WARN_ON(!buf->db_attach)) अणु
		pr_err("trying to pin a non attached buffer\n");
		वापस -EINVAL;
	पूर्ण

	अगर (WARN_ON(buf->dma_sgt)) अणु
		pr_err("dmabuf buffer is already pinned\n");
		वापस 0;
	पूर्ण

	/* get the associated scatterlist क्रम this buffer */
	sgt = dma_buf_map_attachment(buf->db_attach, buf->dma_dir);
	अगर (IS_ERR(sgt)) अणु
		pr_err("Error getting dmabuf scatterlist\n");
		वापस -EINVAL;
	पूर्ण

	buf->dma_sgt = sgt;
	buf->vaddr = शून्य;

	वापस 0;
पूर्ण

अटल व्योम vb2_dma_sg_unmap_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = mem_priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;
	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(buf->vaddr);

	अगर (WARN_ON(!buf->db_attach)) अणु
		pr_err("trying to unpin a not attached buffer\n");
		वापस;
	पूर्ण

	अगर (WARN_ON(!sgt)) अणु
		pr_err("dmabuf buffer is already unpinned\n");
		वापस;
	पूर्ण

	अगर (buf->vaddr) अणु
		dma_buf_vunmap(buf->db_attach->dmabuf, &map);
		buf->vaddr = शून्य;
	पूर्ण
	dma_buf_unmap_attachment(buf->db_attach, sgt, buf->dma_dir);

	buf->dma_sgt = शून्य;
पूर्ण

अटल व्योम vb2_dma_sg_detach_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = mem_priv;

	/* अगर vb2 works correctly you should never detach mapped buffer */
	अगर (WARN_ON(buf->dma_sgt))
		vb2_dma_sg_unmap_dmabuf(buf);

	/* detach this attachment */
	dma_buf_detach(buf->db_attach->dmabuf, buf->db_attach);
	kमुक्त(buf);
पूर्ण

अटल व्योम *vb2_dma_sg_attach_dmabuf(काष्ठा device *dev, काष्ठा dma_buf *dbuf,
	अचिन्हित दीर्घ size, क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_dma_sg_buf *buf;
	काष्ठा dma_buf_attachment *dba;

	अगर (WARN_ON(!dev))
		वापस ERR_PTR(-EINVAL);

	अगर (dbuf->size < size)
		वापस ERR_PTR(-EFAULT);

	buf = kzalloc(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->dev = dev;
	/* create attachment क्रम the dmabuf with the user device */
	dba = dma_buf_attach(dbuf, buf->dev);
	अगर (IS_ERR(dba)) अणु
		pr_err("failed to attach dmabuf\n");
		kमुक्त(buf);
		वापस dba;
	पूर्ण

	buf->dma_dir = dma_dir;
	buf->size = size;
	buf->db_attach = dba;

	वापस buf;
पूर्ण

अटल व्योम *vb2_dma_sg_cookie(व्योम *buf_priv)
अणु
	काष्ठा vb2_dma_sg_buf *buf = buf_priv;

	वापस buf->dma_sgt;
पूर्ण

स्थिर काष्ठा vb2_mem_ops vb2_dma_sg_memops = अणु
	.alloc		= vb2_dma_sg_alloc,
	.put		= vb2_dma_sg_put,
	.get_userptr	= vb2_dma_sg_get_userptr,
	.put_userptr	= vb2_dma_sg_put_userptr,
	.prepare	= vb2_dma_sg_prepare,
	.finish		= vb2_dma_sg_finish,
	.vaddr		= vb2_dma_sg_vaddr,
	.mmap		= vb2_dma_sg_mmap,
	.num_users	= vb2_dma_sg_num_users,
	.get_dmabuf	= vb2_dma_sg_get_dmabuf,
	.map_dmabuf	= vb2_dma_sg_map_dmabuf,
	.unmap_dmabuf	= vb2_dma_sg_unmap_dmabuf,
	.attach_dmabuf	= vb2_dma_sg_attach_dmabuf,
	.detach_dmabuf	= vb2_dma_sg_detach_dmabuf,
	.cookie		= vb2_dma_sg_cookie,
पूर्ण;
EXPORT_SYMBOL_GPL(vb2_dma_sg_memops);

MODULE_DESCRIPTION("dma scatter/gather memory handling routines for videobuf2");
MODULE_AUTHOR("Andrzej Pietrasiewicz");
MODULE_LICENSE("GPL");
