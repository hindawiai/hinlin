<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * Copyright (c) 2015-2016, Integrated Device Technology Inc.
 * Copyright (c) 2015, Prodrive Technologies
 * Copyright (c) 2015, Texas Instruments Incorporated
 * Copyright (c) 2015, RapidIO Trade Association
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License(GPL) Version 2, or the BSD-3 Clause license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary क्रमm must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the करोcumentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to enकरोrse or promote products derived from this software without
 * specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित _RIO_MPORT_CDEV_H_
#घोषणा _RIO_MPORT_CDEV_H_

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

काष्ठा rio_mport_मुख्यt_io अणु
	__u16 rioid;		/* destID of remote device */
	__u8  hopcount;		/* hopcount to remote device */
	__u8  pad0[5];
	__u32 offset;		/* offset in रेजिस्टर space */
	__u32 length;		/* length in bytes */
	__u64 buffer;		/* poपूर्णांकer to data buffer */
पूर्ण;

/*
 * Definitions क्रम RapidIO data transfers:
 * - memory mapped (MAPPED)
 * - packet generation from memory (TRANSFER)
 */
#घोषणा RIO_TRANSFER_MODE_MAPPED	(1 << 0)
#घोषणा RIO_TRANSFER_MODE_TRANSFER	(1 << 1)
#घोषणा RIO_CAP_DBL_SEND		(1 << 2)
#घोषणा RIO_CAP_DBL_RECV		(1 << 3)
#घोषणा RIO_CAP_PW_SEND			(1 << 4)
#घोषणा RIO_CAP_PW_RECV			(1 << 5)
#घोषणा RIO_CAP_MAP_OUTB		(1 << 6)
#घोषणा RIO_CAP_MAP_INB			(1 << 7)

काष्ठा rio_mport_properties अणु
	__u16 hdid;
	__u8  id;			/* Physical port ID */
	__u8  index;
	__u32 flags;
	__u32 sys_size;		/* Default addressing size */
	__u8  port_ok;
	__u8  link_speed;
	__u8  link_width;
	__u8  pad0;
	__u32 dma_max_sge;
	__u32 dma_max_size;
	__u32 dma_align;
	__u32 transfer_mode;		/* Default transfer mode */
	__u32 cap_sys_size;		/* Capable प्रणाली sizes */
	__u32 cap_addr_size;		/* Capable addressing sizes */
	__u32 cap_transfer_mode;	/* Capable transfer modes */
	__u32 cap_mport;		/* Mport capabilities */
पूर्ण;

/*
 * Definitions क्रम RapidIO events;
 * - incoming port-ग_लिखोs
 * - incoming करोorbells
 */
#घोषणा RIO_DOORBELL	(1 << 0)
#घोषणा RIO_PORTWRITE	(1 << 1)

काष्ठा rio_करोorbell अणु
	__u16 rioid;
	__u16 payload;
पूर्ण;

काष्ठा rio_करोorbell_filter अणु
	__u16 rioid;	/* Use RIO_INVALID_DESTID to match all ids */
	__u16 low;
	__u16 high;
	__u16 pad0;
पूर्ण;


काष्ठा rio_portग_लिखो अणु
	__u32 payload[16];
पूर्ण;

काष्ठा rio_pw_filter अणु
	__u32 mask;
	__u32 low;
	__u32 high;
	__u32 pad0;
पूर्ण;

/* RapidIO base address क्रम inbound requests set to value defined below
 * indicates that no specअगरic RIO-to-local address translation is requested
 * and driver should use direct (one-to-one) address mapping.
*/
#घोषणा RIO_MAP_ANY_ADDR	(__u64)(~((__u64) 0))

काष्ठा rio_mmap अणु
	__u16 rioid;
	__u16 pad0[3];
	__u64 rio_addr;
	__u64 length;
	__u64 handle;
	__u64 address;
पूर्ण;

काष्ठा rio_dma_mem अणु
	__u64 length;		/* length of DMA memory */
	__u64 dma_handle;	/* handle associated with this memory */
	__u64 address;
पूर्ण;

काष्ठा rio_event अणु
	__u32 header;	/* event type RIO_DOORBELL or RIO_PORTWRITE */
	जोड़ अणु
		काष्ठा rio_करोorbell करोorbell;	/* header क्रम RIO_DOORBELL */
		काष्ठा rio_portग_लिखो portग_लिखो; /* header क्रम RIO_PORTWRITE */
	पूर्ण u;
	__u32 pad0;
पूर्ण;

क्रमागत rio_transfer_sync अणु
	RIO_TRANSFER_SYNC,	/* synchronous transfer */
	RIO_TRANSFER_ASYNC,	/* asynchronous transfer */
	RIO_TRANSFER_FAF,	/* fire-and-क्रमget transfer */
पूर्ण;

क्रमागत rio_transfer_dir अणु
	RIO_TRANSFER_सूची_READ,	/* Read operation */
	RIO_TRANSFER_सूची_WRITE,	/* Write operation */
पूर्ण;

/*
 * RapidIO data exchange transactions are lists of inभागidual transfers. Each
 * transfer exchanges data between two RapidIO devices by remote direct memory
 * access and has its own completion code.
 *
 * The RapidIO specअगरication defines four types of data exchange requests:
 * NREAD, NWRITE, SWRITE and NWRITE_R. The RapidIO DMA channel पूर्णांकerface allows
 * to specअगरy the required type of ग_लिखो operation or combination of them when
 * only the last data packet requires response.
 *
 * NREAD:    पढ़ो up to 256 bytes from remote device memory पूर्णांकo local memory
 * NWRITE:   ग_लिखो up to 256 bytes from local memory to remote device memory
 *           without confirmation
 * SWRITE:   as NWRITE, but all addresses and payloads must be 64-bit aligned
 * NWRITE_R: as NWRITE, but expect acknowledgment from remote device.
 *
 * The शेष exchange is chosen from NREAD and any of the WRITE modes as the
 * driver sees fit. For ग_लिखो requests the user can explicitly choose between
 * any of the ग_लिखो modes क्रम each transaction.
 */
क्रमागत rio_exchange अणु
	RIO_EXCHANGE_DEFAULT,	/* Default method */
	RIO_EXCHANGE_NWRITE,	/* All packets using NWRITE */
	RIO_EXCHANGE_SWRITE,	/* All packets using SWRITE */
	RIO_EXCHANGE_NWRITE_R,	/* Last packet NWRITE_R, others NWRITE */
	RIO_EXCHANGE_SWRITE_R,	/* Last packet NWRITE_R, others SWRITE */
	RIO_EXCHANGE_NWRITE_R_ALL, /* All packets using NWRITE_R */
पूर्ण;

काष्ठा rio_transfer_io अणु
	__u64 rio_addr;	/* Address in target's RIO mem space */
	__u64 loc_addr;
	__u64 handle;
	__u64 offset;	/* Offset in buffer */
	__u64 length;	/* Length in bytes */
	__u16 rioid;	/* Target destID */
	__u16 method;	/* Data exchange method, one of rio_exchange क्रमागत */
	__u32 completion_code;	/* Completion code क्रम this transfer */
पूर्ण;

काष्ठा rio_transaction अणु
	__u64 block;	/* Poपूर्णांकer to array of <count> transfers */
	__u32 count;	/* Number of transfers */
	__u32 transfer_mode;	/* Data transfer mode */
	__u16 sync;	/* Synch method, one of rio_transfer_sync क्रमागत */
	__u16 dir;	/* Transfer direction, one of rio_transfer_dir क्रमागत */
	__u32 pad0;
पूर्ण;

काष्ठा rio_async_tx_रुको अणु
	__u32 token;	/* DMA transaction ID token */
	__u32 समयout;	/* Wait समयout in msec, अगर 0 use शेष TO */
पूर्ण;

#घोषणा RIO_MAX_DEVNAME_SZ	20

काष्ठा rio_rdev_info अणु
	__u16 destid;
	__u8 hopcount;
	__u8 pad0;
	__u32 comptag;
	अक्षर name[RIO_MAX_DEVNAME_SZ + 1];
पूर्ण;

/* Driver IOCTL codes */
#घोषणा RIO_MPORT_DRV_MAGIC           'm'

#घोषणा RIO_MPORT_MAINT_HDID_SET	\
	_IOW(RIO_MPORT_DRV_MAGIC, 1, __u16)
#घोषणा RIO_MPORT_MAINT_COMPTAG_SET	\
	_IOW(RIO_MPORT_DRV_MAGIC, 2, __u32)
#घोषणा RIO_MPORT_MAINT_PORT_IDX_GET	\
	_IOR(RIO_MPORT_DRV_MAGIC, 3, __u32)
#घोषणा RIO_MPORT_GET_PROPERTIES \
	_IOR(RIO_MPORT_DRV_MAGIC, 4, काष्ठा rio_mport_properties)
#घोषणा RIO_MPORT_MAINT_READ_LOCAL \
	_IOR(RIO_MPORT_DRV_MAGIC, 5, काष्ठा rio_mport_मुख्यt_io)
#घोषणा RIO_MPORT_MAINT_WRITE_LOCAL \
	_IOW(RIO_MPORT_DRV_MAGIC, 6, काष्ठा rio_mport_मुख्यt_io)
#घोषणा RIO_MPORT_MAINT_READ_REMOTE \
	_IOR(RIO_MPORT_DRV_MAGIC, 7, काष्ठा rio_mport_मुख्यt_io)
#घोषणा RIO_MPORT_MAINT_WRITE_REMOTE \
	_IOW(RIO_MPORT_DRV_MAGIC, 8, काष्ठा rio_mport_मुख्यt_io)
#घोषणा RIO_ENABLE_DOORBELL_RANGE	\
	_IOW(RIO_MPORT_DRV_MAGIC, 9, काष्ठा rio_करोorbell_filter)
#घोषणा RIO_DISABLE_DOORBELL_RANGE	\
	_IOW(RIO_MPORT_DRV_MAGIC, 10, काष्ठा rio_करोorbell_filter)
#घोषणा RIO_ENABLE_PORTWRITE_RANGE	\
	_IOW(RIO_MPORT_DRV_MAGIC, 11, काष्ठा rio_pw_filter)
#घोषणा RIO_DISABLE_PORTWRITE_RANGE	\
	_IOW(RIO_MPORT_DRV_MAGIC, 12, काष्ठा rio_pw_filter)
#घोषणा RIO_SET_EVENT_MASK		\
	_IOW(RIO_MPORT_DRV_MAGIC, 13, __u32)
#घोषणा RIO_GET_EVENT_MASK		\
	_IOR(RIO_MPORT_DRV_MAGIC, 14, __u32)
#घोषणा RIO_MAP_OUTBOUND \
	_IOWR(RIO_MPORT_DRV_MAGIC, 15, काष्ठा rio_mmap)
#घोषणा RIO_UNMAP_OUTBOUND \
	_IOW(RIO_MPORT_DRV_MAGIC, 16, काष्ठा rio_mmap)
#घोषणा RIO_MAP_INBOUND \
	_IOWR(RIO_MPORT_DRV_MAGIC, 17, काष्ठा rio_mmap)
#घोषणा RIO_UNMAP_INBOUND \
	_IOW(RIO_MPORT_DRV_MAGIC, 18, __u64)
#घोषणा RIO_ALLOC_DMA \
	_IOWR(RIO_MPORT_DRV_MAGIC, 19, काष्ठा rio_dma_mem)
#घोषणा RIO_FREE_DMA \
	_IOW(RIO_MPORT_DRV_MAGIC, 20, __u64)
#घोषणा RIO_TRANSFER \
	_IOWR(RIO_MPORT_DRV_MAGIC, 21, काष्ठा rio_transaction)
#घोषणा RIO_WAIT_FOR_ASYNC \
	_IOW(RIO_MPORT_DRV_MAGIC, 22, काष्ठा rio_async_tx_रुको)
#घोषणा RIO_DEV_ADD \
	_IOW(RIO_MPORT_DRV_MAGIC, 23, काष्ठा rio_rdev_info)
#घोषणा RIO_DEV_DEL \
	_IOW(RIO_MPORT_DRV_MAGIC, 24, काष्ठा rio_rdev_info)

#पूर्ण_अगर /* _RIO_MPORT_CDEV_H_ */
