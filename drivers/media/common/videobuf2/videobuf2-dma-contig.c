<शैली गुरु>
/*
 * videobuf2-dma-contig.c - DMA contig memory allocator क्रम videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/module.h>
#समावेश <linux/refcount.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>

#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>
#समावेश <media/videobuf2-memops.h>

काष्ठा vb2_dc_buf अणु
	काष्ठा device			*dev;
	व्योम				*vaddr;
	अचिन्हित दीर्घ			size;
	व्योम				*cookie;
	dma_addr_t			dma_addr;
	अचिन्हित दीर्घ			attrs;
	क्रमागत dma_data_direction		dma_dir;
	काष्ठा sg_table			*dma_sgt;
	काष्ठा frame_vector		*vec;

	/* MMAP related */
	काष्ठा vb2_vmarea_handler	handler;
	refcount_t			refcount;
	काष्ठा sg_table			*sgt_base;

	/* DMABUF related */
	काष्ठा dma_buf_attachment	*db_attach;
पूर्ण;

/*********************************************/
/*        scatterlist table functions        */
/*********************************************/

अटल अचिन्हित दीर्घ vb2_dc_get_contiguous_size(काष्ठा sg_table *sgt)
अणु
	काष्ठा scatterlist *s;
	dma_addr_t expected = sg_dma_address(sgt->sgl);
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ size = 0;

	क्रम_each_sgtable_dma_sg(sgt, s, i) अणु
		अगर (sg_dma_address(s) != expected)
			अवरोध;
		expected += sg_dma_len(s);
		size += sg_dma_len(s);
	पूर्ण
	वापस size;
पूर्ण

/*********************************************/
/*         callbacks क्रम all buffers         */
/*********************************************/

अटल व्योम *vb2_dc_cookie(व्योम *buf_priv)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;

	वापस &buf->dma_addr;
पूर्ण

अटल व्योम *vb2_dc_vaddr(व्योम *buf_priv)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	अगर (!buf->vaddr && buf->db_attach) अणु
		ret = dma_buf_vmap(buf->db_attach->dmabuf, &map);
		buf->vaddr = ret ? शून्य : map.vaddr;
	पूर्ण

	वापस buf->vaddr;
पूर्ण

अटल अचिन्हित पूर्णांक vb2_dc_num_users(व्योम *buf_priv)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;

	वापस refcount_पढ़ो(&buf->refcount);
पूर्ण

अटल व्योम vb2_dc_prepare(व्योम *buf_priv)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;

	अगर (!sgt)
		वापस;

	dma_sync_sgtable_क्रम_device(buf->dev, sgt, buf->dma_dir);
पूर्ण

अटल व्योम vb2_dc_finish(व्योम *buf_priv)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;

	अगर (!sgt)
		वापस;

	dma_sync_sgtable_क्रम_cpu(buf->dev, sgt, buf->dma_dir);
पूर्ण

/*********************************************/
/*        callbacks क्रम MMAP buffers         */
/*********************************************/

अटल व्योम vb2_dc_put(व्योम *buf_priv)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;

	अगर (!refcount_dec_and_test(&buf->refcount))
		वापस;

	अगर (buf->sgt_base) अणु
		sg_मुक्त_table(buf->sgt_base);
		kमुक्त(buf->sgt_base);
	पूर्ण
	dma_मुक्त_attrs(buf->dev, buf->size, buf->cookie, buf->dma_addr,
		       buf->attrs);
	put_device(buf->dev);
	kमुक्त(buf);
पूर्ण

अटल व्योम *vb2_dc_alloc(काष्ठा device *dev, अचिन्हित दीर्घ attrs,
			  अचिन्हित दीर्घ size, क्रमागत dma_data_direction dma_dir,
			  gfp_t gfp_flags)
अणु
	काष्ठा vb2_dc_buf *buf;

	अगर (WARN_ON(!dev))
		वापस ERR_PTR(-EINVAL);

	buf = kzalloc(माप *buf, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->attrs = attrs;
	buf->cookie = dma_alloc_attrs(dev, size, &buf->dma_addr,
					GFP_KERNEL | gfp_flags, buf->attrs);
	अगर (!buf->cookie) अणु
		dev_err(dev, "dma_alloc_coherent of size %ld failed\n", size);
		kमुक्त(buf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर ((buf->attrs & DMA_ATTR_NO_KERNEL_MAPPING) == 0)
		buf->vaddr = buf->cookie;

	/* Prevent the device from being released जबतक the buffer is used */
	buf->dev = get_device(dev);
	buf->size = size;
	buf->dma_dir = dma_dir;

	buf->handler.refcount = &buf->refcount;
	buf->handler.put = vb2_dc_put;
	buf->handler.arg = buf;

	refcount_set(&buf->refcount, 1);

	वापस buf;
पूर्ण

अटल पूर्णांक vb2_dc_mmap(व्योम *buf_priv, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;
	पूर्णांक ret;

	अगर (!buf) अणु
		prपूर्णांकk(KERN_ERR "No buffer to map\n");
		वापस -EINVAL;
	पूर्ण

	ret = dma_mmap_attrs(buf->dev, vma, buf->cookie,
		buf->dma_addr, buf->size, buf->attrs);

	अगर (ret) अणु
		pr_err("Remapping memory failed, error: %d\n", ret);
		वापस ret;
	पूर्ण

	vma->vm_flags		|= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_निजी_data	= &buf->handler;
	vma->vm_ops		= &vb2_common_vm_ops;

	vma->vm_ops->खोलो(vma);

	pr_debug("%s: mapped dma addr 0x%08lx at 0x%08lx, size %ld\n",
		__func__, (अचिन्हित दीर्घ)buf->dma_addr, vma->vm_start,
		buf->size);

	वापस 0;
पूर्ण

/*********************************************/
/*         DMABUF ops क्रम exporters          */
/*********************************************/

काष्ठा vb2_dc_attachment अणु
	काष्ठा sg_table sgt;
	क्रमागत dma_data_direction dma_dir;
पूर्ण;

अटल पूर्णांक vb2_dc_dmabuf_ops_attach(काष्ठा dma_buf *dbuf,
	काष्ठा dma_buf_attachment *dbuf_attach)
अणु
	काष्ठा vb2_dc_attachment *attach;
	अचिन्हित पूर्णांक i;
	काष्ठा scatterlist *rd, *wr;
	काष्ठा sg_table *sgt;
	काष्ठा vb2_dc_buf *buf = dbuf->priv;
	पूर्णांक ret;

	attach = kzalloc(माप(*attach), GFP_KERNEL);
	अगर (!attach)
		वापस -ENOMEM;

	sgt = &attach->sgt;
	/* Copy the buf->base_sgt scatter list to the attachment, as we can't
	 * map the same scatter list to multiple attachments at the same समय.
	 */
	ret = sg_alloc_table(sgt, buf->sgt_base->orig_nents, GFP_KERNEL);
	अगर (ret) अणु
		kमुक्त(attach);
		वापस -ENOMEM;
	पूर्ण

	rd = buf->sgt_base->sgl;
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

अटल व्योम vb2_dc_dmabuf_ops_detach(काष्ठा dma_buf *dbuf,
	काष्ठा dma_buf_attachment *db_attach)
अणु
	काष्ठा vb2_dc_attachment *attach = db_attach->priv;
	काष्ठा sg_table *sgt;

	अगर (!attach)
		वापस;

	sgt = &attach->sgt;

	/* release the scatterlist cache */
	अगर (attach->dma_dir != DMA_NONE)
		/*
		 * Cache sync can be skipped here, as the vb2_dc memory is
		 * allocated from device coherent memory, which means the
		 * memory locations करो not require any explicit cache
		 * मुख्यtenance prior or after being used by the device.
		 */
		dma_unmap_sgtable(db_attach->dev, sgt, attach->dma_dir,
				  DMA_ATTR_SKIP_CPU_SYNC);
	sg_मुक्त_table(sgt);
	kमुक्त(attach);
	db_attach->priv = शून्य;
पूर्ण

अटल काष्ठा sg_table *vb2_dc_dmabuf_ops_map(
	काष्ठा dma_buf_attachment *db_attach, क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_dc_attachment *attach = db_attach->priv;
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
		dma_unmap_sgtable(db_attach->dev, sgt, attach->dma_dir,
				  DMA_ATTR_SKIP_CPU_SYNC);
		attach->dma_dir = DMA_NONE;
	पूर्ण

	/*
	 * mapping to the client with new direction, no cache sync
	 * required see comment in vb2_dc_dmabuf_ops_detach()
	 */
	अगर (dma_map_sgtable(db_attach->dev, sgt, dma_dir,
			    DMA_ATTR_SKIP_CPU_SYNC)) अणु
		pr_err("failed to map scatterlist\n");
		mutex_unlock(lock);
		वापस ERR_PTR(-EIO);
	पूर्ण

	attach->dma_dir = dma_dir;

	mutex_unlock(lock);

	वापस sgt;
पूर्ण

अटल व्योम vb2_dc_dmabuf_ops_unmap(काष्ठा dma_buf_attachment *db_attach,
	काष्ठा sg_table *sgt, क्रमागत dma_data_direction dma_dir)
अणु
	/* nothing to be करोne here */
पूर्ण

अटल व्योम vb2_dc_dmabuf_ops_release(काष्ठा dma_buf *dbuf)
अणु
	/* drop reference obtained in vb2_dc_get_dmabuf */
	vb2_dc_put(dbuf->priv);
पूर्ण

अटल पूर्णांक
vb2_dc_dmabuf_ops_begin_cpu_access(काष्ठा dma_buf *dbuf,
				   क्रमागत dma_data_direction direction)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
vb2_dc_dmabuf_ops_end_cpu_access(काष्ठा dma_buf *dbuf,
				 क्रमागत dma_data_direction direction)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vb2_dc_dmabuf_ops_vmap(काष्ठा dma_buf *dbuf, काष्ठा dma_buf_map *map)
अणु
	काष्ठा vb2_dc_buf *buf = dbuf->priv;

	dma_buf_map_set_vaddr(map, buf->vaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक vb2_dc_dmabuf_ops_mmap(काष्ठा dma_buf *dbuf,
	काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vb2_dc_mmap(dbuf->priv, vma);
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops vb2_dc_dmabuf_ops = अणु
	.attach = vb2_dc_dmabuf_ops_attach,
	.detach = vb2_dc_dmabuf_ops_detach,
	.map_dma_buf = vb2_dc_dmabuf_ops_map,
	.unmap_dma_buf = vb2_dc_dmabuf_ops_unmap,
	.begin_cpu_access = vb2_dc_dmabuf_ops_begin_cpu_access,
	.end_cpu_access = vb2_dc_dmabuf_ops_end_cpu_access,
	.vmap = vb2_dc_dmabuf_ops_vmap,
	.mmap = vb2_dc_dmabuf_ops_mmap,
	.release = vb2_dc_dmabuf_ops_release,
पूर्ण;

अटल काष्ठा sg_table *vb2_dc_get_base_sgt(काष्ठा vb2_dc_buf *buf)
अणु
	पूर्णांक ret;
	काष्ठा sg_table *sgt;

	sgt = kदो_स्मृति(माप(*sgt), GFP_KERNEL);
	अगर (!sgt) अणु
		dev_err(buf->dev, "failed to alloc sg table\n");
		वापस शून्य;
	पूर्ण

	ret = dma_get_sgtable_attrs(buf->dev, sgt, buf->cookie, buf->dma_addr,
		buf->size, buf->attrs);
	अगर (ret < 0) अणु
		dev_err(buf->dev, "failed to get scatterlist from DMA API\n");
		kमुक्त(sgt);
		वापस शून्य;
	पूर्ण

	वापस sgt;
पूर्ण

अटल काष्ठा dma_buf *vb2_dc_get_dmabuf(व्योम *buf_priv, अचिन्हित दीर्घ flags)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;
	काष्ठा dma_buf *dbuf;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &vb2_dc_dmabuf_ops;
	exp_info.size = buf->size;
	exp_info.flags = flags;
	exp_info.priv = buf;

	अगर (!buf->sgt_base)
		buf->sgt_base = vb2_dc_get_base_sgt(buf);

	अगर (WARN_ON(!buf->sgt_base))
		वापस शून्य;

	dbuf = dma_buf_export(&exp_info);
	अगर (IS_ERR(dbuf))
		वापस शून्य;

	/* dmabuf keeps reference to vb2 buffer */
	refcount_inc(&buf->refcount);

	वापस dbuf;
पूर्ण

/*********************************************/
/*       callbacks क्रम USERPTR buffers       */
/*********************************************/

अटल व्योम vb2_dc_put_userptr(व्योम *buf_priv)
अणु
	काष्ठा vb2_dc_buf *buf = buf_priv;
	काष्ठा sg_table *sgt = buf->dma_sgt;
	पूर्णांक i;
	काष्ठा page **pages;

	अगर (sgt) अणु
		/*
		 * No need to sync to CPU, it's alपढ़ोy synced to the CPU
		 * since the finish() memop will have been called beक्रमe this.
		 */
		dma_unmap_sgtable(buf->dev, sgt, buf->dma_dir,
				  DMA_ATTR_SKIP_CPU_SYNC);
		pages = frame_vector_pages(buf->vec);
		/* sgt should exist only अगर vector contains pages... */
		BUG_ON(IS_ERR(pages));
		अगर (buf->dma_dir == DMA_FROM_DEVICE ||
		    buf->dma_dir == DMA_BIसूचीECTIONAL)
			क्रम (i = 0; i < frame_vector_count(buf->vec); i++)
				set_page_dirty_lock(pages[i]);
		sg_मुक्त_table(sgt);
		kमुक्त(sgt);
	पूर्ण अन्यथा अणु
		dma_unmap_resource(buf->dev, buf->dma_addr, buf->size,
				   buf->dma_dir, 0);
	पूर्ण
	vb2_destroy_framevec(buf->vec);
	kमुक्त(buf);
पूर्ण

अटल व्योम *vb2_dc_get_userptr(काष्ठा device *dev, अचिन्हित दीर्घ vaddr,
	अचिन्हित दीर्घ size, क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_dc_buf *buf;
	काष्ठा frame_vector *vec;
	अचिन्हित पूर्णांक offset;
	पूर्णांक n_pages, i;
	पूर्णांक ret = 0;
	काष्ठा sg_table *sgt;
	अचिन्हित दीर्घ contig_size;
	अचिन्हित दीर्घ dma_align = dma_get_cache_alignment();

	/* Only cache aligned DMA transfers are reliable */
	अगर (!IS_ALIGNED(vaddr | size, dma_align)) अणु
		pr_debug("user data must be aligned to %lu bytes\n", dma_align);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!size) अणु
		pr_debug("size is zero\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (WARN_ON(!dev))
		वापस ERR_PTR(-EINVAL);

	buf = kzalloc(माप *buf, GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	buf->dev = dev;
	buf->dma_dir = dma_dir;

	offset = lower_32_bits(offset_in_page(vaddr));
	vec = vb2_create_framevec(vaddr, size);
	अगर (IS_ERR(vec)) अणु
		ret = PTR_ERR(vec);
		जाओ fail_buf;
	पूर्ण
	buf->vec = vec;
	n_pages = frame_vector_count(vec);
	ret = frame_vector_to_pages(vec);
	अगर (ret < 0) अणु
		अचिन्हित दीर्घ *nums = frame_vector_pfns(vec);

		/*
		 * Failed to convert to pages... Check the memory is physically
		 * contiguous and use direct mapping
		 */
		क्रम (i = 1; i < n_pages; i++)
			अगर (nums[i-1] + 1 != nums[i])
				जाओ fail_pfnvec;
		buf->dma_addr = dma_map_resource(buf->dev,
				__pfn_to_phys(nums[0]), size, buf->dma_dir, 0);
		अगर (dma_mapping_error(buf->dev, buf->dma_addr)) अणु
			ret = -ENOMEM;
			जाओ fail_pfnvec;
		पूर्ण
		जाओ out;
	पूर्ण

	sgt = kzalloc(माप(*sgt), GFP_KERNEL);
	अगर (!sgt) अणु
		pr_err("failed to allocate sg table\n");
		ret = -ENOMEM;
		जाओ fail_pfnvec;
	पूर्ण

	ret = sg_alloc_table_from_pages(sgt, frame_vector_pages(vec), n_pages,
		offset, size, GFP_KERNEL);
	अगर (ret) अणु
		pr_err("failed to initialize sg table\n");
		जाओ fail_sgt;
	पूर्ण

	/*
	 * No need to sync to the device, this will happen later when the
	 * prepare() memop is called.
	 */
	अगर (dma_map_sgtable(buf->dev, sgt, buf->dma_dir,
			    DMA_ATTR_SKIP_CPU_SYNC)) अणु
		pr_err("failed to map scatterlist\n");
		ret = -EIO;
		जाओ fail_sgt_init;
	पूर्ण

	contig_size = vb2_dc_get_contiguous_size(sgt);
	अगर (contig_size < size) अणु
		pr_err("contiguous mapping is too small %lu/%lu\n",
			contig_size, size);
		ret = -EFAULT;
		जाओ fail_map_sg;
	पूर्ण

	buf->dma_addr = sg_dma_address(sgt->sgl);
	buf->dma_sgt = sgt;
out:
	buf->size = size;

	वापस buf;

fail_map_sg:
	dma_unmap_sgtable(buf->dev, sgt, buf->dma_dir, DMA_ATTR_SKIP_CPU_SYNC);

fail_sgt_init:
	sg_मुक्त_table(sgt);

fail_sgt:
	kमुक्त(sgt);

fail_pfnvec:
	vb2_destroy_framevec(vec);

fail_buf:
	kमुक्त(buf);

	वापस ERR_PTR(ret);
पूर्ण

/*********************************************/
/*       callbacks क्रम DMABUF buffers        */
/*********************************************/

अटल पूर्णांक vb2_dc_map_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_dc_buf *buf = mem_priv;
	काष्ठा sg_table *sgt;
	अचिन्हित दीर्घ contig_size;

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

	/* checking अगर dmabuf is big enough to store contiguous chunk */
	contig_size = vb2_dc_get_contiguous_size(sgt);
	अगर (contig_size < buf->size) अणु
		pr_err("contiguous chunk is too small %lu/%lu\n",
		       contig_size, buf->size);
		dma_buf_unmap_attachment(buf->db_attach, sgt, buf->dma_dir);
		वापस -EFAULT;
	पूर्ण

	buf->dma_addr = sg_dma_address(sgt->sgl);
	buf->dma_sgt = sgt;
	buf->vaddr = शून्य;

	वापस 0;
पूर्ण

अटल व्योम vb2_dc_unmap_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_dc_buf *buf = mem_priv;
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

	buf->dma_addr = 0;
	buf->dma_sgt = शून्य;
पूर्ण

अटल व्योम vb2_dc_detach_dmabuf(व्योम *mem_priv)
अणु
	काष्ठा vb2_dc_buf *buf = mem_priv;

	/* अगर vb2 works correctly you should never detach mapped buffer */
	अगर (WARN_ON(buf->dma_addr))
		vb2_dc_unmap_dmabuf(buf);

	/* detach this attachment */
	dma_buf_detach(buf->db_attach->dmabuf, buf->db_attach);
	kमुक्त(buf);
पूर्ण

अटल व्योम *vb2_dc_attach_dmabuf(काष्ठा device *dev, काष्ठा dma_buf *dbuf,
	अचिन्हित दीर्घ size, क्रमागत dma_data_direction dma_dir)
अणु
	काष्ठा vb2_dc_buf *buf;
	काष्ठा dma_buf_attachment *dba;

	अगर (dbuf->size < size)
		वापस ERR_PTR(-EFAULT);

	अगर (WARN_ON(!dev))
		वापस ERR_PTR(-EINVAL);

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

/*********************************************/
/*       DMA CONTIG exported functions       */
/*********************************************/

स्थिर काष्ठा vb2_mem_ops vb2_dma_contig_memops = अणु
	.alloc		= vb2_dc_alloc,
	.put		= vb2_dc_put,
	.get_dmabuf	= vb2_dc_get_dmabuf,
	.cookie		= vb2_dc_cookie,
	.vaddr		= vb2_dc_vaddr,
	.mmap		= vb2_dc_mmap,
	.get_userptr	= vb2_dc_get_userptr,
	.put_userptr	= vb2_dc_put_userptr,
	.prepare	= vb2_dc_prepare,
	.finish		= vb2_dc_finish,
	.map_dmabuf	= vb2_dc_map_dmabuf,
	.unmap_dmabuf	= vb2_dc_unmap_dmabuf,
	.attach_dmabuf	= vb2_dc_attach_dmabuf,
	.detach_dmabuf	= vb2_dc_detach_dmabuf,
	.num_users	= vb2_dc_num_users,
पूर्ण;
EXPORT_SYMBOL_GPL(vb2_dma_contig_memops);

/**
 * vb2_dma_contig_set_max_seg_size() - configure DMA max segment size
 * @dev:	device क्रम configuring DMA parameters
 * @size:	size of DMA max segment size to set
 *
 * To allow mapping the scatter-list पूर्णांकo a single chunk in the DMA
 * address space, the device is required to have the DMA max segment
 * size parameter set to a value larger than the buffer size. Otherwise,
 * the DMA-mapping subप्रणाली will split the mapping पूर्णांकo max segment
 * size chunks. This function sets the DMA max segment size
 * parameter to let DMA-mapping map a buffer as a single chunk in DMA
 * address space.
 * This code assumes that the DMA-mapping subप्रणाली will merge all
 * scatterlist segments अगर this is really possible (क्रम example when
 * an IOMMU is available and enabled).
 * Ideally, this parameter should be set by the generic bus code, but it
 * is left with the शेष 64KiB value due to historical liपंचांगiations in
 * other subप्रणालीs (like limited USB host drivers) and there no good
 * place to set it to the proper value.
 * This function should be called from the drivers, which are known to
 * operate on platक्रमms with IOMMU and provide access to shared buffers
 * (either USERPTR or DMABUF). This should be करोne beक्रमe initializing
 * videobuf2 queue.
 */
पूर्णांक vb2_dma_contig_set_max_seg_size(काष्ठा device *dev, अचिन्हित पूर्णांक size)
अणु
	अगर (!dev->dma_parms) अणु
		dev_err(dev, "Failed to set max_seg_size: dma_parms is NULL\n");
		वापस -ENODEV;
	पूर्ण
	अगर (dma_get_max_seg_size(dev) < size)
		वापस dma_set_max_seg_size(dev, size);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vb2_dma_contig_set_max_seg_size);

MODULE_DESCRIPTION("DMA-contig memory handling routines for videobuf2");
MODULE_AUTHOR("Pawel Osciak <pawel@osciak.com>");
MODULE_LICENSE("GPL");
