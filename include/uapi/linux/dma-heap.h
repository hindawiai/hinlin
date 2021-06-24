<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * DMABUF Heaps Userspace API
 *
 * Copyright (C) 2011 Google, Inc.
 * Copyright (C) 2019 Linaro Ltd.
 */
#अगर_अघोषित _UAPI_LINUX_DMABUF_POOL_H
#घोषणा _UAPI_LINUX_DMABUF_POOL_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/**
 * DOC: DMABUF Heaps Userspace API
 */

/* Valid FD_FLAGS are O_CLOEXEC, O_RDONLY, O_WRONLY, O_RDWR */
#घोषणा DMA_HEAP_VALID_FD_FLAGS (O_CLOEXEC | O_ACCMODE)

/* Currently no heap flags */
#घोषणा DMA_HEAP_VALID_HEAP_FLAGS (0)

/**
 * काष्ठा dma_heap_allocation_data - metadata passed from userspace क्रम
 *                                      allocations
 * @len:		size of the allocation
 * @fd:			will be populated with a fd which provides the
 *			handle to the allocated dma-buf
 * @fd_flags:		file descriptor flags used when allocating
 * @heap_flags:		flags passed to heap
 *
 * Provided by userspace as an argument to the ioctl
 */
काष्ठा dma_heap_allocation_data अणु
	__u64 len;
	__u32 fd;
	__u32 fd_flags;
	__u64 heap_flags;
पूर्ण;

#घोषणा DMA_HEAP_IOC_MAGIC		'H'

/**
 * DOC: DMA_HEAP_IOCTL_ALLOC - allocate memory from pool
 *
 * Takes a dma_heap_allocation_data काष्ठा and वापसs it with the fd field
 * populated with the dmabuf handle of the allocation.
 */
#घोषणा DMA_HEAP_IOCTL_ALLOC	_IOWR(DMA_HEAP_IOC_MAGIC, 0x0,\
				      काष्ठा dma_heap_allocation_data)

#पूर्ण_अगर /* _UAPI_LINUX_DMABUF_POOL_H */
