<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * xdp_diag: पूर्णांकerface क्रम query/monitor XDP sockets
 * Copyright(c) 2019 Intel Corporation.
 */

#अगर_अघोषित _LINUX_XDP_DIAG_H
#घोषणा _LINUX_XDP_DIAG_H

#समावेश <linux/types.h>

काष्ठा xdp_diag_req अणु
	__u8	sdiag_family;
	__u8	sdiag_protocol;
	__u16	pad;
	__u32	xdiag_ino;
	__u32	xdiag_show;
	__u32	xdiag_cookie[2];
पूर्ण;

काष्ठा xdp_diag_msg अणु
	__u8	xdiag_family;
	__u8	xdiag_type;
	__u16	pad;
	__u32	xdiag_ino;
	__u32	xdiag_cookie[2];
पूर्ण;

#घोषणा XDP_SHOW_INFO		(1 << 0) /* Basic inक्रमmation */
#घोषणा XDP_SHOW_RING_CFG	(1 << 1)
#घोषणा XDP_SHOW_UMEM		(1 << 2)
#घोषणा XDP_SHOW_MEMINFO	(1 << 3)
#घोषणा XDP_SHOW_STATS		(1 << 4)

क्रमागत अणु
	XDP_DIAG_NONE,
	XDP_DIAG_INFO,
	XDP_DIAG_UID,
	XDP_DIAG_RX_RING,
	XDP_DIAG_TX_RING,
	XDP_DIAG_UMEM,
	XDP_DIAG_UMEM_FILL_RING,
	XDP_DIAG_UMEM_COMPLETION_RING,
	XDP_DIAG_MEMINFO,
	XDP_DIAG_STATS,
	__XDP_DIAG_MAX,
पूर्ण;

#घोषणा XDP_DIAG_MAX (__XDP_DIAG_MAX - 1)

काष्ठा xdp_diag_info अणु
	__u32	अगरindex;
	__u32	queue_id;
पूर्ण;

काष्ठा xdp_diag_ring अणु
	__u32	entries; /*num descs */
पूर्ण;

#घोषणा XDP_DU_F_ZEROCOPY (1 << 0)

काष्ठा xdp_diag_umem अणु
	__u64	size;
	__u32	id;
	__u32	num_pages;
	__u32	chunk_size;
	__u32	headroom;
	__u32	अगरindex;
	__u32	queue_id;
	__u32	flags;
	__u32	refs;
पूर्ण;

काष्ठा xdp_diag_stats अणु
	__u64	n_rx_dropped;
	__u64	n_rx_invalid;
	__u64	n_rx_full;
	__u64	n_fill_ring_empty;
	__u64	n_tx_invalid;
	__u64	n_tx_ring_empty;
पूर्ण;

#पूर्ण_अगर /* _LINUX_XDP_DIAG_H */
