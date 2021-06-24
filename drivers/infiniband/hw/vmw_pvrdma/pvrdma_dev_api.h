<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __PVRDMA_DEV_API_H__
#घोषणा __PVRDMA_DEV_API_H__

#समावेश <linux/types.h>

#समावेश "pvrdma_verbs.h"

/*
 * PVRDMA version macros. Some new features require updates to PVRDMA_VERSION.
 * These macros allow us to check क्रम dअगरferent features अगर necessary.
 */

#घोषणा PVRDMA_ROCEV1_VERSION		17
#घोषणा PVRDMA_ROCEV2_VERSION		18
#घोषणा PVRDMA_PPN64_VERSION		19
#घोषणा PVRDMA_QPHANDLE_VERSION		20
#घोषणा PVRDMA_VERSION			PVRDMA_QPHANDLE_VERSION

#घोषणा PVRDMA_BOARD_ID			1
#घोषणा PVRDMA_REV_ID			1

/*
 * Masks and accessors क्रम page directory, which is a two-level lookup:
 * page directory -> page table -> page. Only one directory क्रम now, but we
 * could expand that easily. 9 bits क्रम tables, 9 bits क्रम pages, gives one
 * gigabyte क्रम memory regions and so क्रमth.
 */

#घोषणा PVRDMA_Pसूची_SHIFT		18
#घोषणा PVRDMA_PTABLE_SHIFT		9
#घोषणा PVRDMA_PAGE_सूची_सूची(x)		(((x) >> PVRDMA_Pसूची_SHIFT) & 0x1)
#घोषणा PVRDMA_PAGE_सूची_TABLE(x)	(((x) >> PVRDMA_PTABLE_SHIFT) & 0x1ff)
#घोषणा PVRDMA_PAGE_सूची_PAGE(x)		((x) & 0x1ff)
#घोषणा PVRDMA_PAGE_सूची_MAX_PAGES	(1 * 512 * 512)
#घोषणा PVRDMA_MAX_FAST_REG_PAGES	128

/*
 * Max MSI-X vectors.
 */

#घोषणा PVRDMA_MAX_INTERRUPTS	3

/* Register offsets within PCI resource on BAR1. */
#घोषणा PVRDMA_REG_VERSION	0x00	/* R: Version of device. */
#घोषणा PVRDMA_REG_DSRLOW	0x04	/* W: Device shared region low PA. */
#घोषणा PVRDMA_REG_DSRHIGH	0x08	/* W: Device shared region high PA. */
#घोषणा PVRDMA_REG_CTL		0x0c	/* W: PVRDMA_DEVICE_CTL */
#घोषणा PVRDMA_REG_REQUEST	0x10	/* W: Indicate device request. */
#घोषणा PVRDMA_REG_ERR		0x14	/* R: Device error. */
#घोषणा PVRDMA_REG_ICR		0x18	/* R: Interrupt cause. */
#घोषणा PVRDMA_REG_IMR		0x1c	/* R/W: Interrupt mask. */
#घोषणा PVRDMA_REG_MACL		0x20	/* R/W: MAC address low. */
#घोषणा PVRDMA_REG_MACH		0x24	/* R/W: MAC address high. */

/* Object flags. */
#घोषणा PVRDMA_CQ_FLAG_ARMED_SOL	BIT(0)	/* Armed क्रम solicited-only. */
#घोषणा PVRDMA_CQ_FLAG_ARMED		BIT(1)	/* Armed. */
#घोषणा PVRDMA_MR_FLAG_DMA		BIT(0)	/* DMA region. */
#घोषणा PVRDMA_MR_FLAG_FRMR		BIT(1)	/* Fast reg memory region. */

/*
 * Atomic operation capability (masked versions are extended atomic
 * operations.
 */

#घोषणा PVRDMA_ATOMIC_OP_COMP_SWAP	BIT(0)	/* Compare and swap. */
#घोषणा PVRDMA_ATOMIC_OP_FETCH_ADD	BIT(1)	/* Fetch and add. */
#घोषणा PVRDMA_ATOMIC_OP_MASK_COMP_SWAP	BIT(2)	/* Masked compare and swap. */
#घोषणा PVRDMA_ATOMIC_OP_MASK_FETCH_ADD	BIT(3)	/* Masked fetch and add. */

/*
 * Base Memory Management Extension flags to support Fast Reg Memory Regions
 * and Fast Reg Work Requests. Each flag represents a verb operation and we
 * must support all of them to qualअगरy क्रम the BMME device cap.
 */

#घोषणा PVRDMA_BMME_FLAG_LOCAL_INV	BIT(0)	/* Local Invalidate. */
#घोषणा PVRDMA_BMME_FLAG_REMOTE_INV	BIT(1)	/* Remote Invalidate. */
#घोषणा PVRDMA_BMME_FLAG_FAST_REG_WR	BIT(2)	/* Fast Reg Work Request. */

/*
 * GID types. The पूर्णांकerpretation of the gid_types bit field in the device
 * capabilities will depend on the device mode. For now, the device only
 * supports RoCE as mode, so only the dअगरferent GID types क्रम RoCE are
 * defined.
 */

#घोषणा PVRDMA_GID_TYPE_FLAG_ROCE_V1	BIT(0)
#घोषणा PVRDMA_GID_TYPE_FLAG_ROCE_V2	BIT(1)

/*
 * Version checks. This checks whether each version supports specअगरic
 * capabilities from the device.
 */

#घोषणा PVRDMA_IS_VERSION17(_dev)					\
	(_dev->dsr_version == PVRDMA_ROCEV1_VERSION &&			\
	 _dev->dsr->caps.gid_types == PVRDMA_GID_TYPE_FLAG_ROCE_V1)

#घोषणा PVRDMA_IS_VERSION18(_dev)					\
	(_dev->dsr_version >= PVRDMA_ROCEV2_VERSION &&			\
	 (_dev->dsr->caps.gid_types == PVRDMA_GID_TYPE_FLAG_ROCE_V1 ||  \
	  _dev->dsr->caps.gid_types == PVRDMA_GID_TYPE_FLAG_ROCE_V2))	\

#घोषणा PVRDMA_SUPPORTED(_dev)						\
	((_dev->dsr->caps.mode == PVRDMA_DEVICE_MODE_ROCE) &&		\
	 (PVRDMA_IS_VERSION17(_dev) || PVRDMA_IS_VERSION18(_dev)))

/*
 * Get capability values based on device version.
 */

#घोषणा PVRDMA_GET_CAP(_dev, _old_val, _val) \
	((PVRDMA_IS_VERSION18(_dev)) ? _val : _old_val)

क्रमागत pvrdma_pci_resource अणु
	PVRDMA_PCI_RESOURCE_MSIX,	/* BAR0: MSI-X, MMIO. */
	PVRDMA_PCI_RESOURCE_REG,	/* BAR1: Registers, MMIO. */
	PVRDMA_PCI_RESOURCE_UAR,	/* BAR2: UAR pages, MMIO, 64-bit. */
	PVRDMA_PCI_RESOURCE_LAST,	/* Last. */
पूर्ण;

क्रमागत pvrdma_device_ctl अणु
	PVRDMA_DEVICE_CTL_ACTIVATE,	/* Activate device. */
	PVRDMA_DEVICE_CTL_UNQUIESCE,	/* Unquiesce device. */
	PVRDMA_DEVICE_CTL_RESET,	/* Reset device. */
पूर्ण;

क्रमागत pvrdma_पूर्णांकr_vector अणु
	PVRDMA_INTR_VECTOR_RESPONSE,	/* Command response. */
	PVRDMA_INTR_VECTOR_ASYNC,	/* Async events. */
	PVRDMA_INTR_VECTOR_CQ,		/* CQ notअगरication. */
	/* Additional CQ notअगरication vectors. */
पूर्ण;

क्रमागत pvrdma_पूर्णांकr_cause अणु
	PVRDMA_INTR_CAUSE_RESPONSE	= (1 << PVRDMA_INTR_VECTOR_RESPONSE),
	PVRDMA_INTR_CAUSE_ASYNC		= (1 << PVRDMA_INTR_VECTOR_ASYNC),
	PVRDMA_INTR_CAUSE_CQ		= (1 << PVRDMA_INTR_VECTOR_CQ),
पूर्ण;

क्रमागत pvrdma_gos_bits अणु
	PVRDMA_GOS_BITS_UNK,		/* Unknown. */
	PVRDMA_GOS_BITS_32,		/* 32-bit. */
	PVRDMA_GOS_BITS_64,		/* 64-bit. */
पूर्ण;

क्रमागत pvrdma_gos_type अणु
	PVRDMA_GOS_TYPE_UNK,		/* Unknown. */
	PVRDMA_GOS_TYPE_LINUX,		/* Linux. */
पूर्ण;

क्रमागत pvrdma_device_mode अणु
	PVRDMA_DEVICE_MODE_ROCE,	/* RoCE. */
	PVRDMA_DEVICE_MODE_IWARP,	/* iWarp. */
	PVRDMA_DEVICE_MODE_IB,		/* InfiniBand. */
पूर्ण;

काष्ठा pvrdma_gos_info अणु
	u32 gos_bits:2;			/* W: PVRDMA_GOS_BITS_ */
	u32 gos_type:4;			/* W: PVRDMA_GOS_TYPE_ */
	u32 gos_ver:16;			/* W: Guest OS version. */
	u32 gos_misc:10;		/* W: Other. */
	u32 pad;			/* Pad to 8-byte alignment. */
पूर्ण;

काष्ठा pvrdma_device_caps अणु
	u64 fw_ver;				/* R: Query device. */
	__be64 node_guid;
	__be64 sys_image_guid;
	u64 max_mr_size;
	u64 page_size_cap;
	u64 atomic_arg_sizes;			/* EX verbs. */
	u32 ex_comp_mask;			/* EX verbs. */
	u32 device_cap_flags2;			/* EX verbs. */
	u32 max_fa_bit_boundary;		/* EX verbs. */
	u32 log_max_atomic_अंतरभूत_arg;		/* EX verbs. */
	u32 venकरोr_id;
	u32 venकरोr_part_id;
	u32 hw_ver;
	u32 max_qp;
	u32 max_qp_wr;
	u32 device_cap_flags;
	u32 max_sge;
	u32 max_sge_rd;
	u32 max_cq;
	u32 max_cqe;
	u32 max_mr;
	u32 max_pd;
	u32 max_qp_rd_atom;
	u32 max_ee_rd_atom;
	u32 max_res_rd_atom;
	u32 max_qp_init_rd_atom;
	u32 max_ee_init_rd_atom;
	u32 max_ee;
	u32 max_rdd;
	u32 max_mw;
	u32 max_raw_ipv6_qp;
	u32 max_raw_ethy_qp;
	u32 max_mcast_grp;
	u32 max_mcast_qp_attach;
	u32 max_total_mcast_qp_attach;
	u32 max_ah;
	u32 max_fmr;
	u32 max_map_per_fmr;
	u32 max_srq;
	u32 max_srq_wr;
	u32 max_srq_sge;
	u32 max_uar;
	u32 gid_tbl_len;
	u16 max_pkeys;
	u8  local_ca_ack_delay;
	u8  phys_port_cnt;
	u8  mode;				/* PVRDMA_DEVICE_MODE_ */
	u8  atomic_ops;				/* PVRDMA_ATOMIC_OP_* bits */
	u8  bmme_flags;				/* FRWR Mem Mgmt Extensions */
	u8  gid_types;				/* PVRDMA_GID_TYPE_FLAG_ */
	u32 max_fast_reg_page_list_len;
पूर्ण;

काष्ठा pvrdma_ring_page_info अणु
	u32 num_pages;				/* Num pages incl. header. */
	u32 reserved;				/* Reserved. */
	u64 pdir_dma;				/* Page directory PA. */
पूर्ण;

#आशय pack(push, 1)

काष्ठा pvrdma_device_shared_region अणु
	u32 driver_version;			/* W: Driver version. */
	u32 pad;				/* Pad to 8-byte align. */
	काष्ठा pvrdma_gos_info gos_info;	/* W: Guest OS inक्रमmation. */
	u64 cmd_slot_dma;			/* W: Command slot address. */
	u64 resp_slot_dma;			/* W: Response slot address. */
	काष्ठा pvrdma_ring_page_info async_ring_pages;
						/* W: Async ring page info. */
	काष्ठा pvrdma_ring_page_info cq_ring_pages;
						/* W: CQ ring page info. */
	जोड़ अणु
		u32 uar_pfn;			/* W: UAR pageframe. */
		u64 uar_pfn64;			/* W: 64-bit UAR page frame. */
	पूर्ण;
	काष्ठा pvrdma_device_caps caps;		/* R: Device capabilities. */
पूर्ण;

#आशय pack(pop)

/* Event types. Currently a 1:1 mapping with क्रमागत ib_event. */
क्रमागत pvrdma_eqe_type अणु
	PVRDMA_EVENT_CQ_ERR,
	PVRDMA_EVENT_QP_FATAL,
	PVRDMA_EVENT_QP_REQ_ERR,
	PVRDMA_EVENT_QP_ACCESS_ERR,
	PVRDMA_EVENT_COMM_EST,
	PVRDMA_EVENT_SQ_DRAINED,
	PVRDMA_EVENT_PATH_MIG,
	PVRDMA_EVENT_PATH_MIG_ERR,
	PVRDMA_EVENT_DEVICE_FATAL,
	PVRDMA_EVENT_PORT_ACTIVE,
	PVRDMA_EVENT_PORT_ERR,
	PVRDMA_EVENT_LID_CHANGE,
	PVRDMA_EVENT_PKEY_CHANGE,
	PVRDMA_EVENT_SM_CHANGE,
	PVRDMA_EVENT_SRQ_ERR,
	PVRDMA_EVENT_SRQ_LIMIT_REACHED,
	PVRDMA_EVENT_QP_LAST_WQE_REACHED,
	PVRDMA_EVENT_CLIENT_REREGISTER,
	PVRDMA_EVENT_GID_CHANGE,
पूर्ण;

/* Event queue element. */
काष्ठा pvrdma_eqe अणु
	u32 type;	/* Event type. */
	u32 info;	/* Handle, other. */
पूर्ण;

/* CQ notअगरication queue element. */
काष्ठा pvrdma_cqne अणु
	u32 info;	/* Handle */
पूर्ण;

क्रमागत अणु
	PVRDMA_CMD_FIRST,
	PVRDMA_CMD_QUERY_PORT = PVRDMA_CMD_FIRST,
	PVRDMA_CMD_QUERY_PKEY,
	PVRDMA_CMD_CREATE_PD,
	PVRDMA_CMD_DESTROY_PD,
	PVRDMA_CMD_CREATE_MR,
	PVRDMA_CMD_DESTROY_MR,
	PVRDMA_CMD_CREATE_CQ,
	PVRDMA_CMD_RESIZE_CQ,
	PVRDMA_CMD_DESTROY_CQ,
	PVRDMA_CMD_CREATE_QP,
	PVRDMA_CMD_MODIFY_QP,
	PVRDMA_CMD_QUERY_QP,
	PVRDMA_CMD_DESTROY_QP,
	PVRDMA_CMD_CREATE_UC,
	PVRDMA_CMD_DESTROY_UC,
	PVRDMA_CMD_CREATE_BIND,
	PVRDMA_CMD_DESTROY_BIND,
	PVRDMA_CMD_CREATE_SRQ,
	PVRDMA_CMD_MODIFY_SRQ,
	PVRDMA_CMD_QUERY_SRQ,
	PVRDMA_CMD_DESTROY_SRQ,
	PVRDMA_CMD_MAX,
पूर्ण;

क्रमागत अणु
	PVRDMA_CMD_FIRST_RESP = (1 << 31),
	PVRDMA_CMD_QUERY_PORT_RESP = PVRDMA_CMD_FIRST_RESP,
	PVRDMA_CMD_QUERY_PKEY_RESP,
	PVRDMA_CMD_CREATE_PD_RESP,
	PVRDMA_CMD_DESTROY_PD_RESP_NOOP,
	PVRDMA_CMD_CREATE_MR_RESP,
	PVRDMA_CMD_DESTROY_MR_RESP_NOOP,
	PVRDMA_CMD_CREATE_CQ_RESP,
	PVRDMA_CMD_RESIZE_CQ_RESP,
	PVRDMA_CMD_DESTROY_CQ_RESP_NOOP,
	PVRDMA_CMD_CREATE_QP_RESP,
	PVRDMA_CMD_MODIFY_QP_RESP,
	PVRDMA_CMD_QUERY_QP_RESP,
	PVRDMA_CMD_DESTROY_QP_RESP,
	PVRDMA_CMD_CREATE_UC_RESP,
	PVRDMA_CMD_DESTROY_UC_RESP_NOOP,
	PVRDMA_CMD_CREATE_BIND_RESP_NOOP,
	PVRDMA_CMD_DESTROY_BIND_RESP_NOOP,
	PVRDMA_CMD_CREATE_SRQ_RESP,
	PVRDMA_CMD_MODIFY_SRQ_RESP,
	PVRDMA_CMD_QUERY_SRQ_RESP,
	PVRDMA_CMD_DESTROY_SRQ_RESP,
	PVRDMA_CMD_MAX_RESP,
पूर्ण;

काष्ठा pvrdma_cmd_hdr अणु
	u64 response;		/* Key क्रम response lookup. */
	u32 cmd;		/* PVRDMA_CMD_ */
	u32 reserved;		/* Reserved. */
पूर्ण;

काष्ठा pvrdma_cmd_resp_hdr अणु
	u64 response;		/* From cmd hdr. */
	u32 ack;		/* PVRDMA_CMD_XXX_RESP */
	u8 err;			/* Error. */
	u8 reserved[3];		/* Reserved. */
पूर्ण;

काष्ठा pvrdma_cmd_query_port अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u8 port_num;
	u8 reserved[7];
पूर्ण;

काष्ठा pvrdma_cmd_query_port_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	काष्ठा pvrdma_port_attr attrs;
पूर्ण;

काष्ठा pvrdma_cmd_query_pkey अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u8 port_num;
	u8 index;
	u8 reserved[6];
पूर्ण;

काष्ठा pvrdma_cmd_query_pkey_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u16 pkey;
	u8 reserved[6];
पूर्ण;

काष्ठा pvrdma_cmd_create_uc अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	जोड़ अणु
		u32 pfn; /* UAR page frame number */
		u64 pfn64; /* 64-bit UAR page frame number */
	पूर्ण;
पूर्ण;

काष्ठा pvrdma_cmd_create_uc_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 ctx_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_destroy_uc अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 ctx_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_pd अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 ctx_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_pd_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 pd_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_destroy_pd अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 pd_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_mr अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u64 start;
	u64 length;
	u64 pdir_dma;
	u32 pd_handle;
	u32 access_flags;
	u32 flags;
	u32 nchunks;
पूर्ण;

काष्ठा pvrdma_cmd_create_mr_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 mr_handle;
	u32 lkey;
	u32 rkey;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_destroy_mr अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 mr_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_cq अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u64 pdir_dma;
	u32 ctx_handle;
	u32 cqe;
	u32 nchunks;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_cq_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 cq_handle;
	u32 cqe;
पूर्ण;

काष्ठा pvrdma_cmd_resize_cq अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 cq_handle;
	u32 cqe;
पूर्ण;

काष्ठा pvrdma_cmd_resize_cq_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 cqe;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_destroy_cq अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 cq_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_srq अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u64 pdir_dma;
	u32 pd_handle;
	u32 nchunks;
	काष्ठा pvrdma_srq_attr attrs;
	u8 srq_type;
	u8 reserved[7];
पूर्ण;

काष्ठा pvrdma_cmd_create_srq_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 srqn;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_modअगरy_srq अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 srq_handle;
	u32 attr_mask;
	काष्ठा pvrdma_srq_attr attrs;
पूर्ण;

काष्ठा pvrdma_cmd_query_srq अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 srq_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_query_srq_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	काष्ठा pvrdma_srq_attr attrs;
पूर्ण;

काष्ठा pvrdma_cmd_destroy_srq अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 srq_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_qp अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u64 pdir_dma;
	u32 pd_handle;
	u32 send_cq_handle;
	u32 recv_cq_handle;
	u32 srq_handle;
	u32 max_send_wr;
	u32 max_recv_wr;
	u32 max_send_sge;
	u32 max_recv_sge;
	u32 max_अंतरभूत_data;
	u32 lkey;
	u32 access_flags;
	u16 total_chunks;
	u16 send_chunks;
	u16 max_atomic_arg;
	u8 sq_sig_all;
	u8 qp_type;
	u8 is_srq;
	u8 reserved[3];
पूर्ण;

काष्ठा pvrdma_cmd_create_qp_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 qpn;
	u32 max_send_wr;
	u32 max_recv_wr;
	u32 max_send_sge;
	u32 max_recv_sge;
	u32 max_अंतरभूत_data;
पूर्ण;

काष्ठा pvrdma_cmd_create_qp_resp_v2 अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 qpn;
	u32 qp_handle;
	u32 max_send_wr;
	u32 max_recv_wr;
	u32 max_send_sge;
	u32 max_recv_sge;
	u32 max_अंतरभूत_data;
पूर्ण;

काष्ठा pvrdma_cmd_modअगरy_qp अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 qp_handle;
	u32 attr_mask;
	काष्ठा pvrdma_qp_attr attrs;
पूर्ण;

काष्ठा pvrdma_cmd_query_qp अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 qp_handle;
	u32 attr_mask;
पूर्ण;

काष्ठा pvrdma_cmd_query_qp_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	काष्ठा pvrdma_qp_attr attrs;
पूर्ण;

काष्ठा pvrdma_cmd_destroy_qp अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 qp_handle;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_destroy_qp_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	u32 events_reported;
	u8 reserved[4];
पूर्ण;

काष्ठा pvrdma_cmd_create_bind अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 mtu;
	u32 vlan;
	u32 index;
	u8 new_gid[16];
	u8 gid_type;
	u8 reserved[3];
पूर्ण;

काष्ठा pvrdma_cmd_destroy_bind अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	u32 index;
	u8 dest_gid[16];
	u8 reserved[4];
पूर्ण;

जोड़ pvrdma_cmd_req अणु
	काष्ठा pvrdma_cmd_hdr hdr;
	काष्ठा pvrdma_cmd_query_port query_port;
	काष्ठा pvrdma_cmd_query_pkey query_pkey;
	काष्ठा pvrdma_cmd_create_uc create_uc;
	काष्ठा pvrdma_cmd_destroy_uc destroy_uc;
	काष्ठा pvrdma_cmd_create_pd create_pd;
	काष्ठा pvrdma_cmd_destroy_pd destroy_pd;
	काष्ठा pvrdma_cmd_create_mr create_mr;
	काष्ठा pvrdma_cmd_destroy_mr destroy_mr;
	काष्ठा pvrdma_cmd_create_cq create_cq;
	काष्ठा pvrdma_cmd_resize_cq resize_cq;
	काष्ठा pvrdma_cmd_destroy_cq destroy_cq;
	काष्ठा pvrdma_cmd_create_qp create_qp;
	काष्ठा pvrdma_cmd_modअगरy_qp modअगरy_qp;
	काष्ठा pvrdma_cmd_query_qp query_qp;
	काष्ठा pvrdma_cmd_destroy_qp destroy_qp;
	काष्ठा pvrdma_cmd_create_bind create_bind;
	काष्ठा pvrdma_cmd_destroy_bind destroy_bind;
	काष्ठा pvrdma_cmd_create_srq create_srq;
	काष्ठा pvrdma_cmd_modअगरy_srq modअगरy_srq;
	काष्ठा pvrdma_cmd_query_srq query_srq;
	काष्ठा pvrdma_cmd_destroy_srq destroy_srq;
पूर्ण;

जोड़ pvrdma_cmd_resp अणु
	काष्ठा pvrdma_cmd_resp_hdr hdr;
	काष्ठा pvrdma_cmd_query_port_resp query_port_resp;
	काष्ठा pvrdma_cmd_query_pkey_resp query_pkey_resp;
	काष्ठा pvrdma_cmd_create_uc_resp create_uc_resp;
	काष्ठा pvrdma_cmd_create_pd_resp create_pd_resp;
	काष्ठा pvrdma_cmd_create_mr_resp create_mr_resp;
	काष्ठा pvrdma_cmd_create_cq_resp create_cq_resp;
	काष्ठा pvrdma_cmd_resize_cq_resp resize_cq_resp;
	काष्ठा pvrdma_cmd_create_qp_resp create_qp_resp;
	काष्ठा pvrdma_cmd_create_qp_resp_v2 create_qp_resp_v2;
	काष्ठा pvrdma_cmd_query_qp_resp query_qp_resp;
	काष्ठा pvrdma_cmd_destroy_qp_resp destroy_qp_resp;
	काष्ठा pvrdma_cmd_create_srq_resp create_srq_resp;
	काष्ठा pvrdma_cmd_query_srq_resp query_srq_resp;
पूर्ण;

#पूर्ण_अगर /* __PVRDMA_DEV_API_H__ */
