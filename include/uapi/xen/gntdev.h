<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR MIT) */
/******************************************************************************
 * gntdev.h
 * 
 * Interface to /dev/xen/gntdev.
 * 
 * Copyright (c) 2007, D G Murray
 * Copyright (c) 2018, Oleksandr Andrushchenko, EPAM Systems Inc.
 * 
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 * 
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित __LINUX_PUBLIC_GNTDEV_H__
#घोषणा __LINUX_PUBLIC_GNTDEV_H__

#समावेश <linux/types.h>

काष्ठा ioctl_gntdev_grant_ref अणु
	/* The करोमुख्य ID of the grant to be mapped. */
	__u32 करोmid;
	/* The grant reference of the grant to be mapped. */
	__u32 ref;
पूर्ण;

/*
 * Inserts the grant references पूर्णांकo the mapping table of an instance
 * of gntdev. N.B. This करोes not perक्रमm the mapping, which is deferred
 * until mmap() is called with @index as the offset.
 */
#घोषणा IOCTL_GNTDEV_MAP_GRANT_REF \
_IOC(_IOC_NONE, 'G', 0, माप(काष्ठा ioctl_gntdev_map_grant_ref))
काष्ठा ioctl_gntdev_map_grant_ref अणु
	/* IN parameters */
	/* The number of grants to be mapped. */
	__u32 count;
	__u32 pad;
	/* OUT parameters */
	/* The offset to be used on a subsequent call to mmap(). */
	__u64 index;
	/* Variable IN parameter. */
	/* Array of grant references, of size @count. */
	काष्ठा ioctl_gntdev_grant_ref refs[1];
पूर्ण;

/*
 * Removes the grant references from the mapping table of an instance of
 * gntdev. N.B. munmap() must be called on the relevant भव address(es)
 * beक्रमe this ioctl is called, or an error will result.
 */
#घोषणा IOCTL_GNTDEV_UNMAP_GRANT_REF \
_IOC(_IOC_NONE, 'G', 1, माप(काष्ठा ioctl_gntdev_unmap_grant_ref))
काष्ठा ioctl_gntdev_unmap_grant_ref अणु
	/* IN parameters */
	/* The offset was वापसed by the corresponding map operation. */
	__u64 index;
	/* The number of pages to be unmapped. */
	__u32 count;
	__u32 pad;
पूर्ण;

/*
 * Returns the offset in the driver's address space that corresponds
 * to @vaddr. This can be used to perक्रमm a munmap(), followed by an
 * UNMAP_GRANT_REF ioctl, where no state about the offset is retained by
 * the caller. The number of pages that were allocated at the same समय as
 * @vaddr is वापसed in @count.
 *
 * N.B. Where more than one page has been mapped पूर्णांकo a contiguous range, the
 *      supplied @vaddr must correspond to the start of the range; otherwise
 *      an error will result. It is only possible to munmap() the entire
 *      contiguously-allocated range at once, and not any subrange thereof.
 */
#घोषणा IOCTL_GNTDEV_GET_OFFSET_FOR_VADDR \
_IOC(_IOC_NONE, 'G', 2, माप(काष्ठा ioctl_gntdev_get_offset_क्रम_vaddr))
काष्ठा ioctl_gntdev_get_offset_क्रम_vaddr अणु
	/* IN parameters */
	/* The भव address of the first mapped page in a range. */
	__u64 vaddr;
	/* OUT parameters */
	/* The offset that was used in the initial mmap() operation. */
	__u64 offset;
	/* The number of pages mapped in the VM area that begins at @vaddr. */
	__u32 count;
	__u32 pad;
पूर्ण;

/*
 * Sets the maximum number of grants that may mapped at once by this gntdev
 * instance.
 *
 * N.B. This must be called beक्रमe any other ioctl is perक्रमmed on the device.
 */
#घोषणा IOCTL_GNTDEV_SET_MAX_GRANTS \
_IOC(_IOC_NONE, 'G', 3, माप(काष्ठा ioctl_gntdev_set_max_grants))
काष्ठा ioctl_gntdev_set_max_grants अणु
	/* IN parameter */
	/* The maximum number of grants that may be mapped at once. */
	__u32 count;
पूर्ण;

/*
 * Sets up an unmap notअगरication within the page, so that the other side can करो
 * cleanup अगर this side crashes. Required to implement cross-करोमुख्य robust
 * mutexes or बंद notअगरication on communication channels.
 *
 * Each mapped page only supports one notअगरication; multiple calls referring to
 * the same page overग_लिखो the previous notअगरication. You must clear the
 * notअगरication prior to the IOCTL_GNTALLOC_DEALLOC_GREF अगर you करो not want it
 * to occur.
 */
#घोषणा IOCTL_GNTDEV_SET_UNMAP_NOTIFY \
_IOC(_IOC_NONE, 'G', 7, माप(काष्ठा ioctl_gntdev_unmap_notअगरy))
काष्ठा ioctl_gntdev_unmap_notअगरy अणु
	/* IN parameters */
	/* Offset in the file descriptor क्रम a byte within the page (same as
	 * used in mmap). If using UNMAP_NOTIFY_CLEAR_BYTE, this is the byte to
	 * be cleared. Otherwise, it can be any byte in the page whose
	 * notअगरication we are adjusting.
	 */
	__u64 index;
	/* Action(s) to take on unmap */
	__u32 action;
	/* Event channel to notअगरy */
	__u32 event_channel_port;
पूर्ण;

काष्ठा gntdev_grant_copy_segment अणु
	जोड़ अणु
		व्योम __user *virt;
		काष्ठा अणु
			grant_ref_t ref;
			__u16 offset;
			करोmid_t करोmid;
		पूर्ण क्रमeign;
	पूर्ण source, dest;
	__u16 len;

	__u16 flags;  /* GNTCOPY_* */
	__s16 status; /* GNTST_* */
पूर्ण;

/*
 * Copy between grant references and local buffers.
 *
 * The copy is split पूर्णांकo @count @segments, each of which can copy
 * to/from one grant reference.
 *
 * Each segment is similar to काष्ठा gnttab_copy in the hypervisor ABI
 * except the local buffer is specअगरied using a भव address
 * (instead of a GFN and offset).
 *
 * The local buffer may cross a Xen page boundary -- the driver will
 * split segments पूर्णांकo multiple ops अगर required.
 *
 * Returns 0 अगर all segments have been processed and @status in each
 * segment is valid.  Note that one or more segments may have failed
 * (status != GNTST_okay).
 *
 * If the driver had to split a segment पूर्णांकo two or more ops, @status
 * includes the status of the first failed op क्रम that segment (or
 * GNTST_okay अगर all ops were successful).
 *
 * If -1 is वापसed, the status of all segments is undefined.
 *
 * EINVAL: A segment has local buffers क्रम both source and
 *         destination.
 * EINVAL: A segment crosses the boundary of a क्रमeign page.
 * EFAULT: A segment's local buffer is not accessible.
 */
#घोषणा IOCTL_GNTDEV_GRANT_COPY \
	_IOC(_IOC_NONE, 'G', 8, माप(काष्ठा ioctl_gntdev_grant_copy))
काष्ठा ioctl_gntdev_grant_copy अणु
	अचिन्हित पूर्णांक count;
	काष्ठा gntdev_grant_copy_segment __user *segments;
पूर्ण;

/* Clear (set to zero) the byte specअगरied by index */
#घोषणा UNMAP_NOTIFY_CLEAR_BYTE 0x1
/* Send an पूर्णांकerrupt on the indicated event channel */
#घोषणा UNMAP_NOTIFY_SEND_EVENT 0x2

/*
 * Flags to be used जबतक requesting memory mapping's backing storage
 * to be allocated with DMA API.
 */

/*
 * The buffer is backed with memory allocated with dma_alloc_wc.
 */
#घोषणा GNTDEV_DMA_FLAG_WC		(1 << 0)

/*
 * The buffer is backed with memory allocated with dma_alloc_coherent.
 */
#घोषणा GNTDEV_DMA_FLAG_COHERENT	(1 << 1)

/*
 * Create a dma-buf [1] from grant references @refs of count @count provided
 * by the क्रमeign करोमुख्य @करोmid with flags @flags.
 *
 * By शेष dma-buf is backed by प्रणाली memory pages, but by providing
 * one of the GNTDEV_DMA_FLAG_XXX flags it can also be created as
 * a DMA ग_लिखो-combine or coherent buffer, e.g. allocated with dma_alloc_wc/
 * dma_alloc_coherent.
 *
 * Returns 0 अगर dma-buf was successfully created and the corresponding
 * dma-buf's file descriptor is वापसed in @fd.
 *
 * [1] Documentation/driver-api/dma-buf.rst
 */

#घोषणा IOCTL_GNTDEV_DMABUF_EXP_FROM_REFS \
	_IOC(_IOC_NONE, 'G', 9, \
	     माप(काष्ठा ioctl_gntdev_dmabuf_exp_from_refs))
काष्ठा ioctl_gntdev_dmabuf_exp_from_refs अणु
	/* IN parameters. */
	/* Specअगरic options क्रम this dma-buf: see GNTDEV_DMA_FLAG_XXX. */
	__u32 flags;
	/* Number of grant references in @refs array. */
	__u32 count;
	/* OUT parameters. */
	/* File descriptor of the dma-buf. */
	__u32 fd;
	/* The करोमुख्य ID of the grant references to be mapped. */
	__u32 करोmid;
	/* Variable IN parameter. */
	/* Array of grant references of size @count. */
	__u32 refs[1];
पूर्ण;

/*
 * This will block until the dma-buf with the file descriptor @fd is
 * released. This is only valid क्रम buffers created with
 * IOCTL_GNTDEV_DMABUF_EXP_FROM_REFS.
 *
 * If within @रुको_to_ms milliseconds the buffer is not released
 * then -ETIMEDOUT error is वापसed.
 * If the buffer with the file descriptor @fd करोes not exist or has alपढ़ोy
 * been released, then -ENOENT is वापसed. For valid file descriptors
 * this must not be treated as error.
 */
#घोषणा IOCTL_GNTDEV_DMABUF_EXP_WAIT_RELEASED \
	_IOC(_IOC_NONE, 'G', 10, \
	     माप(काष्ठा ioctl_gntdev_dmabuf_exp_रुको_released))
काष्ठा ioctl_gntdev_dmabuf_exp_रुको_released अणु
	/* IN parameters */
	__u32 fd;
	__u32 रुको_to_ms;
पूर्ण;

/*
 * Import a dma-buf with file descriptor @fd and export granted references
 * to the pages of that dma-buf पूर्णांकo array @refs of size @count.
 */
#घोषणा IOCTL_GNTDEV_DMABUF_IMP_TO_REFS \
	_IOC(_IOC_NONE, 'G', 11, \
	     माप(काष्ठा ioctl_gntdev_dmabuf_imp_to_refs))
काष्ठा ioctl_gntdev_dmabuf_imp_to_refs अणु
	/* IN parameters. */
	/* File descriptor of the dma-buf. */
	__u32 fd;
	/* Number of grant references in @refs array. */
	__u32 count;
	/* The करोमुख्य ID क्रम which references to be granted. */
	__u32 करोmid;
	/* Reserved - must be zero. */
	__u32 reserved;
	/* OUT parameters. */
	/* Array of grant references of size @count. */
	__u32 refs[1];
पूर्ण;

/*
 * This will बंद all references to the imported buffer with file descriptor
 * @fd, so it can be released by the owner. This is only valid क्रम buffers
 * created with IOCTL_GNTDEV_DMABUF_IMP_TO_REFS.
 */
#घोषणा IOCTL_GNTDEV_DMABUF_IMP_RELEASE \
	_IOC(_IOC_NONE, 'G', 12, \
	     माप(काष्ठा ioctl_gntdev_dmabuf_imp_release))
काष्ठा ioctl_gntdev_dmabuf_imp_release अणु
	/* IN parameters */
	__u32 fd;
	__u32 reserved;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PUBLIC_GNTDEV_H__ */
