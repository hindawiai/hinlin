<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * helper functions क्रम vदो_स्मृति video4linux capture buffers
 *
 * The functions expect the hardware being able to scatter gather
 * (i.e. the buffers are not linear in physical memory, but fragmented
 * पूर्णांकo PAGE_SIZE chunks).  They also assume the driver करोes not need
 * to touch the video data.
 *
 * (c) 2007 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <यंत्र/page.h>

#समावेश <media/videobuf-vदो_स्मृति.h>

#घोषणा MAGIC_DMABUF   0x17760309
#घोषणा MAGIC_VMAL_MEM 0x18221223

#घोषणा MAGIC_CHECK(is, should)						\
	अगर (unlikely((is) != (should))) अणु				\
		prपूर्णांकk(KERN_ERR "magic mismatch: %x (expected %x)\n",	\
				is, should);				\
		BUG();							\
	पूर्ण

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);

MODULE_DESCRIPTION("helper module to manage video4linux vmalloc buffers");
MODULE_AUTHOR("Mauro Carvalho Chehab <mchehab@kernel.org>");
MODULE_LICENSE("GPL");

#घोषणा dprपूर्णांकk(level, fmt, arg...)					\
	अगर (debug >= level)						\
		prपूर्णांकk(KERN_DEBUG "vbuf-vmalloc: " fmt , ## arg)


/***************************************************************************/

अटल व्योम videobuf_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_mapping *map = vma->vm_निजी_data;

	dprपूर्णांकk(2, "vm_open %p [count=%u,vma=%08lx-%08lx]\n", map,
		map->count, vma->vm_start, vma->vm_end);

	map->count++;
पूर्ण

अटल व्योम videobuf_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_mapping *map = vma->vm_निजी_data;
	काष्ठा videobuf_queue *q = map->q;
	पूर्णांक i;

	dprपूर्णांकk(2, "vm_close %p [count=%u,vma=%08lx-%08lx]\n", map,
		map->count, vma->vm_start, vma->vm_end);

	map->count--;
	अगर (0 == map->count) अणु
		काष्ठा videobuf_vदो_स्मृति_memory *mem;

		dprपूर्णांकk(1, "munmap %p q=%p\n", map, q);
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

				MAGIC_CHECK(mem->magic, MAGIC_VMAL_MEM);

				/* vमुक्त is not atomic - can't be
				   called with IRQ's disabled
				 */
				dprपूर्णांकk(1, "%s: buf[%d] freeing (%p)\n",
					__func__, i, mem->vaddr);

				vमुक्त(mem->vaddr);
				mem->vaddr = शून्य;
			पूर्ण

			q->bufs[i]->map   = शून्य;
			q->bufs[i]->baddr = 0;
		पूर्ण

		kमुक्त(map);

		videobuf_queue_unlock(q);
	पूर्ण

	वापस;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा videobuf_vm_ops = अणु
	.खोलो     = videobuf_vm_खोलो,
	.बंद    = videobuf_vm_बंद,
पूर्ण;

/* ---------------------------------------------------------------------
 * vदो_स्मृति handlers क्रम the generic methods
 */

/* Allocated area consists on 3 parts:
	काष्ठा video_buffer
	काष्ठा <driver>_buffer (cx88_buffer, saa7134_buf, ...)
	काष्ठा videobuf_dma_sg_memory
 */

अटल काष्ठा videobuf_buffer *__videobuf_alloc_vb(माप_प्रकार size)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *mem;
	काष्ठा videobuf_buffer *vb;

	vb = kzalloc(size + माप(*mem), GFP_KERNEL);
	अगर (!vb)
		वापस vb;

	mem = vb->priv = ((अक्षर *)vb) + size;
	mem->magic = MAGIC_VMAL_MEM;

	dprपूर्णांकk(1, "%s: allocated at %p(%ld+%ld) & %p(%ld)\n",
		__func__, vb, (दीर्घ)माप(*vb), (दीर्घ)size - माप(*vb),
		mem, (दीर्घ)माप(*mem));

	वापस vb;
पूर्ण

अटल पूर्णांक __videobuf_iolock(काष्ठा videobuf_queue *q,
			     काष्ठा videobuf_buffer *vb,
			     काष्ठा v4l2_framebuffer *fbuf)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *mem = vb->priv;
	पूर्णांक pages;

	BUG_ON(!mem);

	MAGIC_CHECK(mem->magic, MAGIC_VMAL_MEM);

	चयन (vb->memory) अणु
	हाल V4L2_MEMORY_MMAP:
		dprपूर्णांकk(1, "%s memory method MMAP\n", __func__);

		/* All handling should be करोne by __videobuf_mmap_mapper() */
		अगर (!mem->vaddr) अणु
			prपूर्णांकk(KERN_ERR "memory is not allocated/mmapped.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल V4L2_MEMORY_USERPTR:
		pages = PAGE_ALIGN(vb->size);

		dprपूर्णांकk(1, "%s memory method USERPTR\n", __func__);

		अगर (vb->baddr) अणु
			prपूर्णांकk(KERN_ERR "USERPTR is currently not supported\n");
			वापस -EINVAL;
		पूर्ण

		/* The only USERPTR currently supported is the one needed क्रम
		 * पढ़ो() method.
		 */

		mem->vaddr = vदो_स्मृति_user(pages);
		अगर (!mem->vaddr) अणु
			prपूर्णांकk(KERN_ERR "vmalloc (%d pages) failed\n", pages);
			वापस -ENOMEM;
		पूर्ण
		dprपूर्णांकk(1, "vmalloc is at addr %p (%d pages)\n",
			mem->vaddr, pages);
		अवरोध;
	हाल V4L2_MEMORY_OVERLAY:
	शेष:
		dprपूर्णांकk(1, "%s memory method OVERLAY/unknown\n", __func__);

		/* Currently, करोesn't support V4L2_MEMORY_OVERLAY */
		prपूर्णांकk(KERN_ERR "Memory method currently unsupported.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __videobuf_mmap_mapper(काष्ठा videobuf_queue *q,
				  काष्ठा videobuf_buffer *buf,
				  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *mem;
	काष्ठा videobuf_mapping *map;
	पूर्णांक retval, pages;

	dprपूर्णांकk(1, "%s\n", __func__);

	/* create mapping + update buffer list */
	map = kzalloc(माप(काष्ठा videobuf_mapping), GFP_KERNEL);
	अगर (शून्य == map)
		वापस -ENOMEM;

	buf->map = map;
	map->q     = q;

	buf->baddr = vma->vm_start;

	mem = buf->priv;
	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_VMAL_MEM);

	pages = PAGE_ALIGN(vma->vm_end - vma->vm_start);
	mem->vaddr = vदो_स्मृति_user(pages);
	अगर (!mem->vaddr) अणु
		prपूर्णांकk(KERN_ERR "vmalloc (%d pages) failed\n", pages);
		जाओ error;
	पूर्ण
	dprपूर्णांकk(1, "vmalloc is at addr %p (%d pages)\n", mem->vaddr, pages);

	/* Try to remap memory */
	retval = remap_vदो_स्मृति_range(vma, mem->vaddr, 0);
	अगर (retval < 0) अणु
		prपूर्णांकk(KERN_ERR "mmap: remap failed with error %d. ", retval);
		vमुक्त(mem->vaddr);
		जाओ error;
	पूर्ण

	vma->vm_ops          = &videobuf_vm_ops;
	vma->vm_flags       |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_निजी_data = map;

	dprपूर्णांकk(1, "mmap %p: q=%p %08lx-%08lx (%lx) pgoff %08lx buf %d\n",
		map, q, vma->vm_start, vma->vm_end,
		(दीर्घ पूर्णांक)buf->bsize,
		vma->vm_pgoff, buf->i);

	videobuf_vm_खोलो(vma);

	वापस 0;

error:
	mem = शून्य;
	kमुक्त(map);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा videobuf_qtype_ops qops = अणु
	.magic        = MAGIC_QTYPE_OPS,

	.alloc_vb     = __videobuf_alloc_vb,
	.iolock       = __videobuf_iolock,
	.mmap_mapper  = __videobuf_mmap_mapper,
	.vaddr        = videobuf_to_vदो_स्मृति,
पूर्ण;

व्योम videobuf_queue_vदो_स्मृति_init(काष्ठा videobuf_queue *q,
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
EXPORT_SYMBOL_GPL(videobuf_queue_vदो_स्मृति_init);

व्योम *videobuf_to_vदो_स्मृति(काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *mem = buf->priv;
	BUG_ON(!mem);
	MAGIC_CHECK(mem->magic, MAGIC_VMAL_MEM);

	वापस mem->vaddr;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_to_vदो_स्मृति);

व्योम videobuf_vदो_स्मृति_मुक्त(काष्ठा videobuf_buffer *buf)
अणु
	काष्ठा videobuf_vदो_स्मृति_memory *mem = buf->priv;

	/* mmapped memory can't be मुक्तd here, otherwise mmapped region
	   would be released, जबतक still needed. In this हाल, the memory
	   release should happen inside videobuf_vm_बंद().
	   So, it should मुक्त memory only अगर the memory were allocated क्रम
	   पढ़ो() operation.
	 */
	अगर ((buf->memory != V4L2_MEMORY_USERPTR) || buf->baddr)
		वापस;

	अगर (!mem)
		वापस;

	MAGIC_CHECK(mem->magic, MAGIC_VMAL_MEM);

	vमुक्त(mem->vaddr);
	mem->vaddr = शून्य;

	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(videobuf_vदो_स्मृति_मुक्त);

