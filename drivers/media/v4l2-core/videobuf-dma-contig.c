<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * helper functions क्रम physically contiguous capture buffers
 *
 * The functions support hardware lacking scatter gather support
 * (i.e. the buffers must be linear in physical memory)
 *
 * Copyright (c) 2008 Magnus Damm
 *
 * Based on videobuf-vदो_स्मृति.c,
 * (c) 2007 Mauro Carvalho Chehab, <mchehab@kernel.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <media/videobuf-dma-contig.h>

काष्ठा videobuf_dma_contig_memory अणु
	u32 magic;
	व्योम *vaddr;
	dma_addr_t dma_handle;
	अचिन्हित दीर्घ size;
पूर्ण;

#घोषणा MAGIC_DC_MEM 0x0733ac61
#घोषणा MAGIC_CHECK(is, should)						    \
	अगर (unlikely((is) != (should)))	अणु				    \
		pr_err("magic mismatch: %x expected %x\n", (is), (should)); \
		BUG();							    \
	पूर्ण

अटल पूर्णांक __videobuf_dc_alloc(काष्ठा device *dev,
			       काष्ठा videobuf_dma_contig_memory *mem,
			       अचिन्हित दीर्घ size, gfp_t flags)
अणु
	mem->size = size;
	mem->vaddr = dma_alloc_coherent(dev, mem->size,
					&mem->dma_handle, flags);

	अगर (!mem->vaddr) अणु
		dev_err(dev, "memory alloc size %ld failed\n", mem->size);
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(dev, "dma mapped data is at %p (%ld)\n", mem->vaddr, mem->size);

	वापस 0;
पूर्ण

अटल व्योम __videobuf_dc_मुक्त(काष्ठा device *dev,
			       काष्ठा videobuf_dma_contig_memory *mem)
अणु
	dma_मुक्त_coherent(dev, mem->size, mem->vaddr, mem->dma_handle);

	mem->vaddr = शून्य;
पूर्ण

अटल व्योम videobuf_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_mapping *map = vma->vm_निजी_data;

	dev_dbg(map->q->dev, "vm_open %p [count=%u,vma=%08lx-%08lx]\n",
		map, map->count, vma->vm_start, vma->vm_end);

	map->count++;
पूर्ण

अटल व्योम videobuf_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_mapping *map = vma->vm_निजी_data;
	काष्ठा videobuf_queue *q = map->q;
	पूर्णांक i;

	dev_dbg(q->dev, "vm_close %p [count=%u,vma=%08lx-%08lx]\n",
		map, map->count, vma->vm_start, vma->vm_end);

	map->count--;
	अगर (0 == map->count) अणु
		काष्ठा videobuf_dma_contig_memory *mem;

		dev_dbg(q->dev, "munmap %p q=%p\n", map, q);
		videobuf_queue_lock(q);

		/* We need first to cancel streams, beक्रमe unmapping */
		अगर (q->streaming)
			videobuf_queue_cancel(q);

		क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
			अगर (शून्य == q->bufs[i])
				जारी;

			अगर (q->bufs[i]->map != map)
				जारी;

			mem = q->bufs[i]->priv;
			अगर (mem) अणु
				/* This callback is called only अगर kernel has
				   allocated memory and this memory is mmapped.
				   In this हाल, memory should be मुक्तd,
				   in order to करो memory unmap.
				 */

				MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

				/* vमुक्त is not atomic - can't be
				   called with IRQ's disabled
				 */
				dev_dbg(q->dev, "buf[%d] freeing %p\n",
					i, mem->vaddr);

				__videobuf_dc_मुक्त(q->dev, mem);
				mem->vaddr = शून्य;
			पूर्ण

			q->bufs[i]->map = शून्य;
			q->bufs[i]->baddr = 0;
		पूर्ण

		kमुक्त(map);

		videobuf_queue_unlock(q);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा videobuf_vm_ops = अणु
	.खोलो	= videobuf_vm_खोलो,
	.बंद	= videobuf_vm_बंद,
पूर्ण;

/**
 * videobuf_dma_contig_user_put() - reset poपूर्णांकer to user space buffer
 * @mem: per-buffer निजी videobuf-dma-contig data
 *
 * This function resets the user space poपूर्णांकer
 */
अटल व्योम videobuf_dma_contig_user_put(काष्ठा videobuf_dma_contig_memory *mem)
अणु
	mem->dma_handle = 0;
	mem->size = 0;
पूर्ण

/**
 * videobuf_dma_contig_user_get() - setup user space memory poपूर्णांकer
 * @mem: per-buffer निजी videobuf-dma-contig data
 * @vb: video buffer to map
 *
 * This function validates and sets up a poपूर्णांकer to user space memory.
 * Only physically contiguous pfn-mapped memory is accepted.
 *
 * Returns 0 अगर successful.
 */
अटल पूर्णांक videobuf_dma_contig_user_get(काष्ठा videobuf_dma_contig_memory *mem,
					काष्ठा videobuf_buffer *vb)
अणु
	अचिन्हित दीर्घ untagged_baddr = untagged_addr(vb->baddr);
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ prev_pfn, this_pfn;
	अचिन्हित दीर्घ pages_करोne, user_address;
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret;

	offset = untagged_baddr & ~PAGE_MASK;
	mem->size = PAGE_ALIGN(vb->size + offset);
	ret = -EINVAL;

	mmap_पढ़ो_lock(mm);

	vma = find_vma(mm, untagged_baddr);
	अगर (!vma)
		जाओ out_up;

	अगर ((untagged_baddr + mem->size) > vma->vm_end)
		जाओ out_up;

	pages_करोne = 0;
	prev_pfn = 0; /* समाप्त warning */
	user_address = untagged_baddr;

	जबतक (pages_करोne < (mem->size >> PAGE_SHIFT)) अणु
		ret = follow_pfn(vma, user_address, &this_pfn);
		अगर (ret)
			अवरोध;

		अगर (pages_करोne == 0)
			mem->dma_handle = (this_pfn << PAGE_SHIFT) + offset;
		अन्यथा अगर (this_pfn != (prev_pfn + 1))
			ret = -EFAULT;

		अगर (ret)
			अवरोध;

		prev_pfn = this_pfn;
		user_address += PAGE_SIZE;
		pages_करोne++;
	पूर्ण

out_up:
	mmap_पढ़ो_unlock(current->mm);

	वापस ret;
पूर्ण

अटल काष्ठा videobuf_buffer *__videobuf_alloc(माप_प्रकार size)
अणु
	काष्ठा videobuf_dma_contig_memory *mem;
	काष्ठा videobuf_buffer *vb;

	vb = kzalloc(size + माप(*mem), GFP_KERNEL);
	अगर (vb) अणु
		vb->priv = ((अक्षर *)vb) + size;
		mem = vb->priv;
		mem->magic = MAGIC_DC_MEM;
	पूर्ण

	वापस vb;
पूर्ण

अटल व्योम *__videobuf_to_vaddr(काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_dma_contig_memory *mem = buf->priv;

	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

	वापस mem->vaddr;
पूर्ण

अटल पूर्णांक __videobuf_iolock(काष्ठा videobuf_queue *q,
			     काष्ठा videobuf_buffer *vb,
			     काष्ठा v4l2_framebuffer *fbuf)
अणु
	काष्ठा videobuf_dma_contig_memory *mem = vb->priv;

	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

	चयन (vb->memory) अणु
	हाल V4L2_MEMORY_MMAP:
		dev_dbg(q->dev, "%s memory method MMAP\n", __func__);

		/* All handling should be करोne by __videobuf_mmap_mapper() */
		अगर (!mem->vaddr) अणु
			dev_err(q->dev, "memory is not allocated/mmapped.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		dev_dbg(q->dev, "%s memory method USERPTR\n", __func__);

		/* handle poपूर्णांकer from user space */
		अगर (vb->baddr)
			वापस videobuf_dma_contig_user_get(mem, vb);

		/* allocate memory क्रम the पढ़ो() method */
		अगर (__videobuf_dc_alloc(q->dev, mem, PAGE_ALIGN(vb->size),
					GFP_KERNEL))
			वापस -ENOMEM;
		अवरोध;
	हाल V4L2_MEMORY_OVERLAY:
	शेष:
		dev_dbg(q->dev, "%s memory method OVERLAY/unknown\n", __func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __videobuf_mmap_mapper(काष्ठा videobuf_queue *q,
				  काष्ठा videobuf_buffer *buf,
				  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_dma_contig_memory *mem;
	काष्ठा videobuf_mapping *map;
	पूर्णांक retval;

	dev_dbg(q->dev, "%s\n", __func__);

	/* create mapping + update buffer list */
	map = kzalloc(माप(काष्ठा videobuf_mapping), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	buf->map = map;
	map->q = q;

	buf->baddr = vma->vm_start;

	mem = buf->priv;
	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

	अगर (__videobuf_dc_alloc(q->dev, mem, PAGE_ALIGN(buf->bsize),
				GFP_KERNEL | __GFP_COMP))
		जाओ error;

	/* Try to remap memory */
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/* the "vm_pgoff" is just used in v4l2 to find the
	 * corresponding buffer data काष्ठाure which is allocated
	 * earlier and it करोes not mean the offset from the physical
	 * buffer start address as usual. So set it to 0 to pass
	 * the sanity check in vm_iomap_memory().
	 */
	vma->vm_pgoff = 0;

	retval = vm_iomap_memory(vma, mem->dma_handle, mem->size);
	अगर (retval) अणु
		dev_err(q->dev, "mmap: remap failed with error %d. ",
			retval);
		dma_मुक्त_coherent(q->dev, mem->size,
				  mem->vaddr, mem->dma_handle);
		जाओ error;
	पूर्ण

	vma->vm_ops = &videobuf_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_निजी_data = map;

	dev_dbg(q->dev, "mmap %p: q=%p %08lx-%08lx (%lx) pgoff %08lx buf %d\n",
		map, q, vma->vm_start, vma->vm_end,
		(दीर्घ पूर्णांक)buf->bsize, vma->vm_pgoff, buf->i);

	videobuf_vm_खोलो(vma);

	वापस 0;

error:
	kमुक्त(map);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा videobuf_qtype_ops qops = अणु
	.magic		= MAGIC_QTYPE_OPS,
	.alloc_vb	= __videobuf_alloc,
	.iolock		= __videobuf_iolock,
	.mmap_mapper	= __videobuf_mmap_mapper,
	.vaddr		= __videobuf_to_vaddr,
पूर्ण;

व्योम videobuf_queue_dma_contig_init(काष्ठा videobuf_queue *q,
				    स्थिर काष्ठा videobuf_queue_ops *ops,
				    काष्ठा device *dev,
				    spinlock_t *irqlock,
				    क्रमागत v4l2_buf_type type,
				    क्रमागत v4l2_field field,
				    अचिन्हित पूर्णांक msize,
				    व्योम *priv,
				    काष्ठा mutex *ext_lock)
अणु
	videobuf_queue_core_init(q, ops, dev, irqlock, type, field, msize,
				 priv, &qops, ext_lock);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_queue_dma_contig_init);

dma_addr_t videobuf_to_dma_contig(काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_dma_contig_memory *mem = buf->priv;

	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

	वापस mem->dma_handle;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_to_dma_contig);

व्योम videobuf_dma_contig_मुक्त(काष्ठा videobuf_queue *q,
			      काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_dma_contig_memory *mem = buf->priv;

	/* mmapped memory can't be मुक्तd here, otherwise mmapped region
	   would be released, जबतक still needed. In this हाल, the memory
	   release should happen inside videobuf_vm_बंद().
	   So, it should मुक्त memory only अगर the memory were allocated क्रम
	   पढ़ो() operation.
	 */
	अगर (buf->memory != V4L2_MEMORY_USERPTR)
		वापस;

	अगर (!mem)
		वापस;

	MAGIC_CHECK(mem->magic, MAGIC_DC_MEM);

	/* handle user space poपूर्णांकer हाल */
	अगर (buf->baddr) अणु
		videobuf_dma_contig_user_put(mem);
		वापस;
	पूर्ण

	/* पढ़ो() method */
	अगर (mem->vaddr) अणु
		__videobuf_dc_मुक्त(q->dev, mem);
		mem->vaddr = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_dma_contig_मुक्त);

MODULE_DESCRIPTION("helper module to manage video4linux dma contig buffers");
MODULE_AUTHOR("Magnus Damm");
MODULE_LICENSE("GPL");
