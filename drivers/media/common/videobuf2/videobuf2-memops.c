<शैली गुरु>
/*
 * videobuf2-memops.c - generic memory handling routines क्रम videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *	   Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/file.h>

#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-memops.h>

/**
 * vb2_create_framevec() - map भव addresses to pfns
 * @start:	Virtual user address where we start mapping
 * @length:	Length of a range to map
 *
 * This function allocates and fills in a vector with pfns corresponding to
 * भव address range passed in arguments. If pfns have corresponding pages,
 * page references are also grabbed to pin pages in memory. The function
 * वापसs poपूर्णांकer to the vector on success and error poपूर्णांकer in हाल of
 * failure. Returned vector needs to be मुक्तd via vb2_destroy_pfnvec().
 */
काष्ठा frame_vector *vb2_create_framevec(अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ length)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ first, last;
	अचिन्हित दीर्घ nr;
	काष्ठा frame_vector *vec;

	first = start >> PAGE_SHIFT;
	last = (start + length - 1) >> PAGE_SHIFT;
	nr = last - first + 1;
	vec = frame_vector_create(nr);
	अगर (!vec)
		वापस ERR_PTR(-ENOMEM);
	ret = get_vaddr_frames(start & PAGE_MASK, nr, vec);
	अगर (ret < 0)
		जाओ out_destroy;
	/* We accept only complete set of PFNs */
	अगर (ret != nr) अणु
		ret = -EFAULT;
		जाओ out_release;
	पूर्ण
	वापस vec;
out_release:
	put_vaddr_frames(vec);
out_destroy:
	frame_vector_destroy(vec);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(vb2_create_framevec);

/**
 * vb2_destroy_framevec() - release vector of mapped pfns
 * @vec:	vector of pfns / pages to release
 *
 * This releases references to all pages in the vector @vec (अगर corresponding
 * pfns are backed by pages) and मुक्तs the passed vector.
 */
व्योम vb2_destroy_framevec(काष्ठा frame_vector *vec)
अणु
	put_vaddr_frames(vec);
	frame_vector_destroy(vec);
पूर्ण
EXPORT_SYMBOL(vb2_destroy_framevec);

/**
 * vb2_common_vm_खोलो() - increase refcount of the vma
 * @vma:	भव memory region क्रम the mapping
 *
 * This function adds another user to the provided vma. It expects
 * काष्ठा vb2_vmarea_handler poपूर्णांकer in vma->vm_निजी_data.
 */
अटल व्योम vb2_common_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vb2_vmarea_handler *h = vma->vm_निजी_data;

	pr_debug("%s: %p, refcount: %d, vma: %08lx-%08lx\n",
	       __func__, h, refcount_पढ़ो(h->refcount), vma->vm_start,
	       vma->vm_end);

	refcount_inc(h->refcount);
पूर्ण

/**
 * vb2_common_vm_बंद() - decrease refcount of the vma
 * @vma:	भव memory region क्रम the mapping
 *
 * This function releases the user from the provided vma. It expects
 * काष्ठा vb2_vmarea_handler poपूर्णांकer in vma->vm_निजी_data.
 */
अटल व्योम vb2_common_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vb2_vmarea_handler *h = vma->vm_निजी_data;

	pr_debug("%s: %p, refcount: %d, vma: %08lx-%08lx\n",
	       __func__, h, refcount_पढ़ो(h->refcount), vma->vm_start,
	       vma->vm_end);

	h->put(h->arg);
पूर्ण

/*
 * vb2_common_vm_ops - common vm_ops used क्रम tracking refcount of mmapped
 * video buffers
 */
स्थिर काष्ठा vm_operations_काष्ठा vb2_common_vm_ops = अणु
	.खोलो = vb2_common_vm_खोलो,
	.बंद = vb2_common_vm_बंद,
पूर्ण;
EXPORT_SYMBOL_GPL(vb2_common_vm_ops);

MODULE_DESCRIPTION("common memory handling routines for videobuf2");
MODULE_AUTHOR("Pawel Osciak <pawel@osciak.com>");
MODULE_LICENSE("GPL");
