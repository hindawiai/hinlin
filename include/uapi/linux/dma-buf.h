<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Framework क्रम buffer objects that can be shared across devices/subप्रणालीs.
 *
 * Copyright(C) 2015 Intel Ltd
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#अगर_अघोषित _DMA_BUF_UAPI_H_
#घोषणा _DMA_BUF_UAPI_H_

#समावेश <linux/types.h>

/* begin/end dma-buf functions used क्रम userspace mmap. */
काष्ठा dma_buf_sync अणु
	__u64 flags;
पूर्ण;

#घोषणा DMA_BUF_SYNC_READ      (1 << 0)
#घोषणा DMA_BUF_SYNC_WRITE     (2 << 0)
#घोषणा DMA_BUF_SYNC_RW        (DMA_BUF_SYNC_READ | DMA_BUF_SYNC_WRITE)
#घोषणा DMA_BUF_SYNC_START     (0 << 2)
#घोषणा DMA_BUF_SYNC_END       (1 << 2)
#घोषणा DMA_BUF_SYNC_VALID_FLAGS_MASK \
	(DMA_BUF_SYNC_RW | DMA_BUF_SYNC_END)

#घोषणा DMA_BUF_NAME_LEN	32

#घोषणा DMA_BUF_BASE		'b'
#घोषणा DMA_BUF_IOCTL_SYNC	_IOW(DMA_BUF_BASE, 0, काष्ठा dma_buf_sync)

/* 32/64bitness of this uapi was botched in android, there's no dअगरference
 * between them in actual uapi, they're just dअगरferent numbers.
 */
#घोषणा DMA_BUF_SET_NAME	_IOW(DMA_BUF_BASE, 1, स्थिर अक्षर *)
#घोषणा DMA_BUF_SET_NAME_A	_IOW(DMA_BUF_BASE, 1, u32)
#घोषणा DMA_BUF_SET_NAME_B	_IOW(DMA_BUF_BASE, 1, u64)

#पूर्ण_अगर
