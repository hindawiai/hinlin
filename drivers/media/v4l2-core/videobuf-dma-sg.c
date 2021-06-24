<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * helper functions क्रम SG DMA video4linux capture buffers
 *
 * The functions expect the hardware being able to scatter gather
 * (i.e. the buffers are not linear in physical memory, but fragmented
 * पूर्णांकo PAGE_SIZE chunks).  They also assume the driver करोes not need
 * to touch the video data.
 *
 * (c) 2007 Mauro Carvalho Chehab, <mchehab@kernel.org>
 *
 * Highly based on video-buf written originally by:
 * (c) 2001,02 Gerd Knorr <kraxel@bytesex.org>
 * (c) 2006 Mauro Carvalho Chehab, <mchehab@kernel.org>
 * (c) 2006 Ted Walther and John Sokol
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/scatterlist.h>
#समावेश <यंत्र/page.h>

#समावेश <media/videobuf-dma-sg.h>

#घोषणा MAGIC_DMABUF 0x19721112
#घोषणा MAGIC_SG_MEM 0x17890714

#घोषणा MAGIC_CHECK(is, should)						\
	अगर (unlikely((is) != (should))) अणु				\
		prपूर्णांकk(KERN_ERR "magic mismatch: %x (expected %x)\n",	\
				is, should);				\
		BUG();							\
	पूर्ण

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

MODULE_DESCRIPTION("helper module to manage video4linux dma sg buffers");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL");

#घोषणा dprपूर्णांकk(level, fmt, arg...)					\
	अगर (debug >= level)						\
		prपूर्णांकk(KERN_DEBUG "vbuf-sg: " fmt , ## arg)

/* --------------------------------------------------------------------- */

/*
 * Return a scatterlist क्रम some page-aligned vदो_स्मृति()'ed memory
 * block (शून्य on errors).  Memory क्रम the scatterlist is allocated
 * using kदो_स्मृति.  The caller must मुक्त the memory.
 */
अटल काष्ठा scatterlist *videobuf_vदो_स्मृति_to_sg(अचिन्हित अक्षर *virt,
						  पूर्णांक nr_pages)
अणु
	काष्ठा scatterlist *sglist;
	काष्ठा page *pg;
	पूर्णांक i;

	sglist = vzalloc(array_size(nr_pages, माप(*sglist)));
	अगर (शून्य == sglist)
		वापस शून्य;
	sg_init_table(sglist, nr_pages);
	क्रम (i = 0; i < nr_pages; i++, virt += PAGE_SIZE) अणु
		pg = vदो_स्मृति_to_page(virt);
		अगर (शून्य == pg)
			जाओ err;
		BUG_ON(PageHighMem(pg));
		sg_set_page(&sglist[i], pg, PAGE_SIZE, 0);
	पूर्ण
	वापस sglist;

err:
	vमुक्त(sglist);
	वापस शून्य;
पूर्ण

/*
 * Return a scatterlist क्रम a an array of userpages (शून्य on errors).
 * Memory क्रम the scatterlist is allocated using kदो_स्मृति.  The caller
 * must मुक्त the memory.
 */
अटल काष्ठा scatterlist *videobuf_pages_to_sg(काष्ठा page **pages,
					पूर्णांक nr_pages, पूर्णांक offset, माप_प्रकार size)
अणु
	काष्ठा scatterlist *sglist;
	पूर्णांक i;

	अगर (शून्य == pages[0])
		वापस शून्य;
	sglist = vदो_स्मृति(array_size(nr_pages, माप(*sglist)));
	अगर (शून्य == sglist)
		वापस शून्य;
	sg_init_table(sglist, nr_pages);

	अगर (PageHighMem(pages[0]))
		/* DMA to highmem pages might not work */
		जाओ highmem;
	sg_set_page(&sglist[0], pages[0],
			min_t(माप_प्रकार, PAGE_SIZE - offset, size), offset);
	size -= min_t(माप_प्रकार, PAGE_SIZE - offset, size);
	क्रम (i = 1; i < nr_pages; i++) अणु
		अगर (शून्य == pages[i])
			जाओ nopage;
		अगर (PageHighMem(pages[i]))
			जाओ highmem;
		sg_set_page(&sglist[i], pages[i], min_t(माप_प्रकार, PAGE_SIZE, size), 0);
		size -= min_t(माप_प्रकार, PAGE_SIZE, size);
	पूर्ण
	वापस sglist;

nopage:
	dprपूर्णांकk(2, "sgl: oops - no page\n");
	vमुक्त(sglist);
	वापस शून्य;

highmem:
	dprपूर्णांकk(2, "sgl: oops - highmem page\n");
	vमुक्त(sglist);
	वापस शून्य;
पूर्ण

/* --------------------------------------------------------------------- */

काष्ठा videobuf_dmabuf *videobuf_to_dma(काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_dma_sg_memory *mem = buf->priv;
	BUG_ON(!mem);

	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

	वापस &mem->dma;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_to_dma);

अटल व्योम videobuf_dma_init(काष्ठा videobuf_dmabuf *dma)
अणु
	स_रखो(dma, 0, माप(*dma));
	dma->magic = MAGIC_DMABUF;
पूर्ण

अटल पूर्णांक videobuf_dma_init_user_locked(काष्ठा videobuf_dmabuf *dma,
			पूर्णांक direction, अचिन्हित दीर्घ data, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ first, last;
	पूर्णांक err, rw = 0;
	अचिन्हित पूर्णांक flags = FOLL_FORCE;

	dma->direction = direction;
	चयन (dma->direction) अणु
	हाल DMA_FROM_DEVICE:
		rw = READ;
		अवरोध;
	हाल DMA_TO_DEVICE:
		rw = WRITE;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	first = (data          & PAGE_MASK) >> PAGE_SHIFT;
	last  = ((data+size-1) & PAGE_MASK) >> PAGE_SHIFT;
	dma->offset = data & ~PAGE_MASK;
	dma->size = size;
	dma->nr_pages = last-first+1;
	dma->pages = kदो_स्मृति_array(dma->nr_pages, माप(काष्ठा page *),
				   GFP_KERNEL);
	अगर (शून्य == dma->pages)
		वापस -ENOMEM;

	अगर (rw == READ)
		flags |= FOLL_WRITE;

	dprपूर्णांकk(1, "init user [0x%lx+0x%lx => %lu pages]\n",
		data, size, dma->nr_pages);

	err = pin_user_pages(data & PAGE_MASK, dma->nr_pages,
			     flags | FOLL_LONGTERM, dma->pages, शून्य);

	अगर (err != dma->nr_pages) अणु
		dma->nr_pages = (err >= 0) ? err : 0;
		dprपूर्णांकk(1, "pin_user_pages: err=%d [%lu]\n", err,
			dma->nr_pages);
		वापस err < 0 ? err : -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक videobuf_dma_init_user(काष्ठा videobuf_dmabuf *dma, पूर्णांक direction,
			   अचिन्हित दीर्घ data, अचिन्हित दीर्घ size)
अणु
	पूर्णांक ret;

	mmap_पढ़ो_lock(current->mm);
	ret = videobuf_dma_init_user_locked(dma, direction, data, size);
	mmap_पढ़ो_unlock(current->mm);

	वापस ret;
पूर्ण

अटल पूर्णांक videobuf_dma_init_kernel(काष्ठा videobuf_dmabuf *dma, पूर्णांक direction,
				    अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक i;

	dprपूर्णांकk(1, "init kernel [%lu pages]\n", nr_pages);

	dma->direction = direction;
	dma->vaddr_pages = kसुस्मृति(nr_pages, माप(*dma->vaddr_pages),
				   GFP_KERNEL);
	अगर (!dma->vaddr_pages)
		वापस -ENOMEM;

	dma->dma_addr = kसुस्मृति(nr_pages, माप(*dma->dma_addr), GFP_KERNEL);
	अगर (!dma->dma_addr) अणु
		kमुक्त(dma->vaddr_pages);
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < nr_pages; i++) अणु
		व्योम *addr;

		addr = dma_alloc_coherent(dma->dev, PAGE_SIZE,
					  &(dma->dma_addr[i]), GFP_KERNEL);
		अगर (addr == शून्य)
			जाओ out_मुक्त_pages;

		dma->vaddr_pages[i] = virt_to_page(addr);
	पूर्ण
	dma->vaddr = vmap(dma->vaddr_pages, nr_pages, VM_MAP | VM_IOREMAP,
			  PAGE_KERNEL);
	अगर (शून्य == dma->vaddr) अणु
		dprपूर्णांकk(1, "vmalloc_32(%lu pages) failed\n", nr_pages);
		जाओ out_मुक्त_pages;
	पूर्ण

	dprपूर्णांकk(1, "vmalloc is at addr %p, size=%lu\n",
		dma->vaddr, nr_pages << PAGE_SHIFT);

	स_रखो(dma->vaddr, 0, nr_pages << PAGE_SHIFT);
	dma->nr_pages = nr_pages;

	वापस 0;
out_मुक्त_pages:
	जबतक (i > 0) अणु
		व्योम *addr;

		i--;
		addr = page_address(dma->vaddr_pages[i]);
		dma_मुक्त_coherent(dma->dev, PAGE_SIZE, addr, dma->dma_addr[i]);
	पूर्ण
	kमुक्त(dma->dma_addr);
	dma->dma_addr = शून्य;
	kमुक्त(dma->vaddr_pages);
	dma->vaddr_pages = शून्य;

	वापस -ENOMEM;

पूर्ण

अटल पूर्णांक videobuf_dma_init_overlay(काष्ठा videobuf_dmabuf *dma, पूर्णांक direction,
			      dma_addr_t addr, अचिन्हित दीर्घ nr_pages)
अणु
	dprपूर्णांकk(1, "init overlay [%lu pages @ bus 0x%lx]\n",
		nr_pages, (अचिन्हित दीर्घ)addr);
	dma->direction = direction;

	अगर (0 == addr)
		वापस -EINVAL;

	dma->bus_addr = addr;
	dma->nr_pages = nr_pages;

	वापस 0;
पूर्ण

अटल पूर्णांक videobuf_dma_map(काष्ठा device *dev, काष्ठा videobuf_dmabuf *dma)
अणु
	MAGIC_CHECK(dma->magic, MAGIC_DMABUF);
	BUG_ON(0 == dma->nr_pages);

	अगर (dma->pages) अणु
		dma->sglist = videobuf_pages_to_sg(dma->pages, dma->nr_pages,
						   dma->offset, dma->size);
	पूर्ण
	अगर (dma->vaddr) अणु
		dma->sglist = videobuf_vदो_स्मृति_to_sg(dma->vaddr,
						     dma->nr_pages);
	पूर्ण
	अगर (dma->bus_addr) अणु
		dma->sglist = vदो_स्मृति(माप(*dma->sglist));
		अगर (शून्य != dma->sglist) अणु
			dma->sglen = 1;
			sg_dma_address(&dma->sglist[0])	= dma->bus_addr
							& PAGE_MASK;
			dma->sglist[0].offset = dma->bus_addr & ~PAGE_MASK;
			sg_dma_len(&dma->sglist[0]) = dma->nr_pages * PAGE_SIZE;
		पूर्ण
	पूर्ण
	अगर (शून्य == dma->sglist) अणु
		dprपूर्णांकk(1, "scatterlist is NULL\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (!dma->bus_addr) अणु
		dma->sglen = dma_map_sg(dev, dma->sglist,
					dma->nr_pages, dma->direction);
		अगर (0 == dma->sglen) अणु
			prपूर्णांकk(KERN_WARNING
			       "%s: videobuf_map_sg failed\n", __func__);
			vमुक्त(dma->sglist);
			dma->sglist = शून्य;
			dma->sglen = 0;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक videobuf_dma_unmap(काष्ठा device *dev, काष्ठा videobuf_dmabuf *dma)
अणु
	MAGIC_CHECK(dma->magic, MAGIC_DMABUF);

	अगर (!dma->sglen)
		वापस 0;

	dma_unmap_sg(dev, dma->sglist, dma->nr_pages, dma->direction);

	vमुक्त(dma->sglist);
	dma->sglist = शून्य;
	dma->sglen = 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_dma_unmap);

पूर्णांक videobuf_dma_मुक्त(काष्ठा videobuf_dmabuf *dma)
अणु
	पूर्णांक i;
	MAGIC_CHECK(dma->magic, MAGIC_DMABUF);
	BUG_ON(dma->sglen);

	अगर (dma->pages) अणु
		unpin_user_pages_dirty_lock(dma->pages, dma->nr_pages,
					    dma->direction == DMA_FROM_DEVICE);
		kमुक्त(dma->pages);
		dma->pages = शून्य;
	पूर्ण

	अगर (dma->dma_addr) अणु
		क्रम (i = 0; i < dma->nr_pages; i++) अणु
			व्योम *addr;

			addr = page_address(dma->vaddr_pages[i]);
			dma_मुक्त_coherent(dma->dev, PAGE_SIZE, addr,
					  dma->dma_addr[i]);
		पूर्ण
		kमुक्त(dma->dma_addr);
		dma->dma_addr = शून्य;
		kमुक्त(dma->vaddr_pages);
		dma->vaddr_pages = शून्य;
		vunmap(dma->vaddr);
		dma->vaddr = शून्य;
	पूर्ण

	अगर (dma->bus_addr)
		dma->bus_addr = 0;
	dma->direction = DMA_NONE;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_dma_मुक्त);

/* --------------------------------------------------------------------- */

अटल व्योम videobuf_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_mapping *map = vma->vm_निजी_data;

	dprपूर्णांकk(2, "vm_open %p [count=%d,vma=%08lx-%08lx]\n", map,
		map->count, vma->vm_start, vma->vm_end);

	map->count++;
पूर्ण

अटल व्योम videobuf_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_mapping *map = vma->vm_निजी_data;
	काष्ठा videobuf_queue *q = map->q;
	काष्ठा videobuf_dma_sg_memory *mem;
	पूर्णांक i;

	dprपूर्णांकk(2, "vm_close %p [count=%d,vma=%08lx-%08lx]\n", map,
		map->count, vma->vm_start, vma->vm_end);

	map->count--;
	अगर (0 == map->count) अणु
		dprपूर्णांकk(1, "munmap %p q=%p\n", map, q);
		videobuf_queue_lock(q);
		क्रम (i = 0; i < VIDEO_MAX_FRAME; i++) अणु
			अगर (शून्य == q->bufs[i])
				जारी;
			mem = q->bufs[i]->priv;
			अगर (!mem)
				जारी;

			MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

			अगर (q->bufs[i]->map != map)
				जारी;
			q->bufs[i]->map   = शून्य;
			q->bufs[i]->baddr = 0;
			q->ops->buf_release(q, q->bufs[i]);
		पूर्ण
		videobuf_queue_unlock(q);
		kमुक्त(map);
	पूर्ण
	वापस;
पूर्ण

/*
 * Get a anonymous page क्रम the mapping.  Make sure we can DMA to that
 * memory location with 32bit PCI devices (i.e. करोn't use highmem क्रम
 * now ...).  Bounce buffers करोn't work very well क्रम the data rates
 * video capture has.
 */
अटल vm_fault_t videobuf_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page;

	dprपूर्णांकk(3, "fault: fault @ %08lx [vma %08lx-%08lx]\n",
		vmf->address, vma->vm_start, vma->vm_end);

	page = alloc_page(GFP_USER | __GFP_DMA32);
	अगर (!page)
		वापस VM_FAULT_OOM;
	clear_user_highpage(page, vmf->address);
	vmf->page = page;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा videobuf_vm_ops = अणु
	.खोलो	= videobuf_vm_खोलो,
	.बंद	= videobuf_vm_बंद,
	.fault	= videobuf_vm_fault,
पूर्ण;

/* ---------------------------------------------------------------------
 * SG handlers क्रम the generic methods
 */

/* Allocated area consists on 3 parts:
	काष्ठा video_buffer
	काष्ठा <driver>_buffer (cx88_buffer, saa7134_buf, ...)
	काष्ठा videobuf_dma_sg_memory
 */

अटल काष्ठा videobuf_buffer *__videobuf_alloc_vb(माप_प्रकार size)
अणु
	काष्ठा videobuf_dma_sg_memory *mem;
	काष्ठा videobuf_buffer *vb;

	vb = kzalloc(size + माप(*mem), GFP_KERNEL);
	अगर (!vb)
		वापस vb;

	mem = vb->priv = ((अक्षर *)vb) + size;
	mem->magic = MAGIC_SG_MEM;

	videobuf_dma_init(&mem->dma);

	dprपूर्णांकk(1, "%s: allocated at %p(%ld+%ld) & %p(%ld)\n",
		__func__, vb, (दीर्घ)माप(*vb), (दीर्घ)size - माप(*vb),
		mem, (दीर्घ)माप(*mem));

	वापस vb;
पूर्ण

अटल व्योम *__videobuf_to_vaddr(काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_dma_sg_memory *mem = buf->priv;
	BUG_ON(!mem);

	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

	वापस mem->dma.vaddr;
पूर्ण

अटल पूर्णांक __videobuf_iolock(काष्ठा videobuf_queue *q,
			     काष्ठा videobuf_buffer *vb,
			     काष्ठा v4l2_framebuffer *fbuf)
अणु
	काष्ठा videobuf_dma_sg_memory *mem = vb->priv;
	अचिन्हित दीर्घ pages;
	dma_addr_t bus;
	पूर्णांक err;

	BUG_ON(!mem);

	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

	अगर (!mem->dma.dev)
		mem->dma.dev = q->dev;
	अन्यथा
		WARN_ON(mem->dma.dev != q->dev);

	चयन (vb->memory) अणु
	हाल V4L2_MEMORY_MMAP:
	हाल V4L2_MEMORY_USERPTR:
		अगर (0 == vb->baddr) अणु
			/* no userspace addr -- kernel bounce buffer */
			pages = PAGE_ALIGN(vb->size) >> PAGE_SHIFT;
			err = videobuf_dma_init_kernel(&mem->dma,
						       DMA_FROM_DEVICE,
						       pages);
			अगर (0 != err)
				वापस err;
		पूर्ण अन्यथा अगर (vb->memory == V4L2_MEMORY_USERPTR) अणु
			/* dma directly to userspace */
			err = videobuf_dma_init_user(&mem->dma,
						     DMA_FROM_DEVICE,
						     vb->baddr, vb->bsize);
			अगर (0 != err)
				वापस err;
		पूर्ण अन्यथा अणु
			/* NOTE: HACK: videobuf_iolock on V4L2_MEMORY_MMAP
			buffers can only be called from videobuf_qbuf
			we take current->mm->mmap_lock there, to prevent
			locking inversion, so करोn't take it here */

			err = videobuf_dma_init_user_locked(&mem->dma,
						      DMA_FROM_DEVICE,
						      vb->baddr, vb->bsize);
			अगर (0 != err)
				वापस err;
		पूर्ण
		अवरोध;
	हाल V4L2_MEMORY_OVERLAY:
		अगर (शून्य == fbuf)
			वापस -EINVAL;
		/* FIXME: need sanity checks क्रम vb->boff */
		/*
		 * Using a द्विगुन cast to aव्योम compiler warnings when
		 * building क्रम PAE. Compiler करोesn't like direct casting
		 * of a 32 bit ptr to 64 bit पूर्णांकeger.
		 */
		bus   = (dma_addr_t)(अचिन्हित दीर्घ)fbuf->base + vb->boff;
		pages = PAGE_ALIGN(vb->size) >> PAGE_SHIFT;
		err = videobuf_dma_init_overlay(&mem->dma, DMA_FROM_DEVICE,
						bus, pages);
		अगर (0 != err)
			वापस err;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	err = videobuf_dma_map(q->dev, &mem->dma);
	अगर (0 != err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक __videobuf_sync(काष्ठा videobuf_queue *q,
			   काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_dma_sg_memory *mem = buf->priv;
	BUG_ON(!mem || !mem->dma.sglen);

	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);
	MAGIC_CHECK(mem->dma.magic, MAGIC_DMABUF);

	dma_sync_sg_क्रम_cpu(q->dev, mem->dma.sglist,
			    mem->dma.nr_pages, mem->dma.direction);

	वापस 0;
पूर्ण

अटल पूर्णांक __videobuf_mmap_mapper(काष्ठा videobuf_queue *q,
				  काष्ठा videobuf_buffer *buf,
				  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_dma_sg_memory *mem = buf->priv;
	काष्ठा videobuf_mapping *map;
	अचिन्हित पूर्णांक first, last, size = 0, i;
	पूर्णांक retval;

	retval = -EINVAL;

	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_SG_MEM);

	/* look क्रम first buffer to map */
	क्रम (first = 0; first < VIDEO_MAX_FRAME; first++) अणु
		अगर (buf == q->bufs[first]) अणु
			size = PAGE_ALIGN(q->bufs[first]->bsize);
			अवरोध;
		पूर्ण
	पूर्ण

	/* paranoia, should never happen since buf is always valid. */
	अगर (!size) अणु
		dprपूर्णांकk(1, "mmap app bug: offset invalid [offset=0x%lx]\n",
				(vma->vm_pgoff << PAGE_SHIFT));
		जाओ करोne;
	पूर्ण

	last = first;

	/* create mapping + update buffer list */
	retval = -ENOMEM;
	map = kदो_स्मृति(माप(काष्ठा videobuf_mapping), GFP_KERNEL);
	अगर (शून्य == map)
		जाओ करोne;

	size = 0;
	क्रम (i = first; i <= last; i++) अणु
		अगर (शून्य == q->bufs[i])
			जारी;
		q->bufs[i]->map   = map;
		q->bufs[i]->baddr = vma->vm_start + size;
		size += PAGE_ALIGN(q->bufs[i]->bsize);
	पूर्ण

	map->count    = 1;
	map->q        = q;
	vma->vm_ops   = &videobuf_vm_ops;
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_flags &= ~VM_IO; /* using shared anonymous pages */
	vma->vm_निजी_data = map;
	dprपूर्णांकk(1, "mmap %p: q=%p %08lx-%08lx pgoff %08lx bufs %d-%d\n",
		map, q, vma->vm_start, vma->vm_end, vma->vm_pgoff, first, last);
	retval = 0;

करोne:
	वापस retval;
पूर्ण

अटल काष्ठा videobuf_qtype_ops sg_ops = अणु
	.magic        = MAGIC_QTYPE_OPS,

	.alloc_vb     = __videobuf_alloc_vb,
	.iolock       = __videobuf_iolock,
	.sync         = __videobuf_sync,
	.mmap_mapper  = __videobuf_mmap_mapper,
	.vaddr        = __videobuf_to_vaddr,
पूर्ण;

व्योम *videobuf_sg_alloc(माप_प्रकार size)
अणु
	काष्ठा videobuf_queue q;

	/* Required to make generic handler to call __videobuf_alloc */
	q.पूर्णांक_ops = &sg_ops;

	q.msize = size;

	वापस videobuf_alloc_vb(&q);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_sg_alloc);

व्योम videobuf_queue_sg_init(काष्ठा videobuf_queue *q,
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
				 priv, &sg_ops, ext_lock);
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_queue_sg_init);

