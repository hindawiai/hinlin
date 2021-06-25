<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * अगर_xdp: XDP socket user-space पूर्णांकerface
 * Copyright(c) 2018 Intel Corporation.
 *
 * Author(s): Bjथघrn Tथघpel <bjorn.topel@पूर्णांकel.com>
 *	      Magnus Karlsson <magnus.karlsson@पूर्णांकel.com>
 */

#अगर_अघोषित _LINUX_IF_XDP_H
#घोषणा _LINUX_IF_XDP_H

#समावेश <linux/types.h>

/* Options क्रम the sxdp_flags field */
#घोषणा XDP_SHARED_UMEM	(1 << 0)
#घोषणा XDP_COPY	(1 << 1) /* Force copy-mode */
#घोषणा XDP_ZEROCOPY	(1 << 2) /* Force zero-copy mode */
/* If this option is set, the driver might go sleep and in that हाल
 * the XDP_RING_NEED_WAKEUP flag in the fill and/or Tx rings will be
 * set. If it is set, the application need to explicitly wake up the
 * driver with a poll() (Rx and Tx) or sendto() (Tx only). If you are
 * running the driver and the application on the same core, you should
 * use this option so that the kernel will yield to the user space
 * application.
 */
#घोषणा XDP_USE_NEED_WAKEUP (1 << 3)

/* Flags क्रम xsk_umem_config flags */
#घोषणा XDP_UMEM_UNALIGNED_CHUNK_FLAG (1 << 0)

काष्ठा sockaddr_xdp अणु
	__u16 sxdp_family;
	__u16 sxdp_flags;
	__u32 sxdp_अगरindex;
	__u32 sxdp_queue_id;
	__u32 sxdp_shared_umem_fd;
पूर्ण;

/* XDP_RING flags */
#घोषणा XDP_RING_NEED_WAKEUP (1 << 0)

काष्ठा xdp_ring_offset अणु
	__u64 producer;
	__u64 consumer;
	__u64 desc;
	__u64 flags;
पूर्ण;

काष्ठा xdp_mmap_offsets अणु
	काष्ठा xdp_ring_offset rx;
	काष्ठा xdp_ring_offset tx;
	काष्ठा xdp_ring_offset fr; /* Fill */
	काष्ठा xdp_ring_offset cr; /* Completion */
पूर्ण;

/* XDP socket options */
#घोषणा XDP_MMAP_OFFSETS		1
#घोषणा XDP_RX_RING			2
#घोषणा XDP_TX_RING			3
#घोषणा XDP_UMEM_REG			4
#घोषणा XDP_UMEM_FILL_RING		5
#घोषणा XDP_UMEM_COMPLETION_RING	6
#घोषणा XDP_STATISTICS			7
#घोषणा XDP_OPTIONS			8

काष्ठा xdp_umem_reg अणु
	__u64 addr; /* Start of packet data area */
	__u64 len; /* Length of packet data area */
	__u32 chunk_size;
	__u32 headroom;
	__u32 flags;
पूर्ण;

काष्ठा xdp_statistics अणु
	__u64 rx_dropped; /* Dropped क्रम other reasons */
	__u64 rx_invalid_descs; /* Dropped due to invalid descriptor */
	__u64 tx_invalid_descs; /* Dropped due to invalid descriptor */
	__u64 rx_ring_full; /* Dropped due to rx ring being full */
	__u64 rx_fill_ring_empty_descs; /* Failed to retrieve item from fill ring */
	__u64 tx_ring_empty_descs; /* Failed to retrieve item from tx ring */
पूर्ण;

काष्ठा xdp_options अणु
	__u32 flags;
पूर्ण;

/* Flags क्रम the flags field of काष्ठा xdp_options */
#घोषणा XDP_OPTIONS_ZEROCOPY (1 << 0)

/* Pgoff क्रम mmaping the rings */
#घोषणा XDP_PGOFF_RX_RING			  0
#घोषणा XDP_PGOFF_TX_RING		 0x80000000
#घोषणा XDP_UMEM_PGOFF_FILL_RING	0x100000000ULL
#घोषणा XDP_UMEM_PGOFF_COMPLETION_RING	0x180000000ULL

/* Masks क्रम unaligned chunks mode */
#घोषणा XSK_UNALIGNED_BUF_OFFSET_SHIFT 48
#घोषणा XSK_UNALIGNED_BUF_ADDR_MASK \
	((1ULL << XSK_UNALIGNED_BUF_OFFSET_SHIFT) - 1)

/* Rx/Tx descriptor */
काष्ठा xdp_desc अणु
	__u64 addr;
	__u32 len;
	__u32 options;
पूर्ण;

/* UMEM descriptor is __u64 */

#पूर्ण_अगर /* _LINUX_IF_XDP_H */
