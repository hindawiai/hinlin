<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Slow Path Operators (header)
 *
 */

#अगर_अघोषित __BNXT_RE_H__
#घोषणा __BNXT_RE_H__
#घोषणा ROCE_DRV_MODULE_NAME		"bnxt_re"

#घोषणा BNXT_RE_DESC	"Broadcom NetXtreme-C/E RoCE Driver"
#घोषणा BNXT_RE_PAGE_SHIFT_4K		(12)
#घोषणा BNXT_RE_PAGE_SHIFT_8K		(13)
#घोषणा BNXT_RE_PAGE_SHIFT_64K		(16)
#घोषणा BNXT_RE_PAGE_SHIFT_2M		(21)
#घोषणा BNXT_RE_PAGE_SHIFT_8M		(23)
#घोषणा BNXT_RE_PAGE_SHIFT_1G		(30)

#घोषणा BNXT_RE_PAGE_SIZE_4K		BIT(BNXT_RE_PAGE_SHIFT_4K)
#घोषणा BNXT_RE_PAGE_SIZE_8K		BIT(BNXT_RE_PAGE_SHIFT_8K)
#घोषणा BNXT_RE_PAGE_SIZE_64K		BIT(BNXT_RE_PAGE_SHIFT_64K)
#घोषणा BNXT_RE_PAGE_SIZE_2M		BIT(BNXT_RE_PAGE_SHIFT_2M)
#घोषणा BNXT_RE_PAGE_SIZE_8M		BIT(BNXT_RE_PAGE_SHIFT_8M)
#घोषणा BNXT_RE_PAGE_SIZE_1G		BIT(BNXT_RE_PAGE_SHIFT_1G)

#घोषणा BNXT_RE_MAX_MR_SIZE_LOW		BIT_ULL(BNXT_RE_PAGE_SHIFT_1G)
#घोषणा BNXT_RE_MAX_MR_SIZE_HIGH	BIT_ULL(39)
#घोषणा BNXT_RE_MAX_MR_SIZE		BNXT_RE_MAX_MR_SIZE_HIGH

#घोषणा BNXT_RE_MAX_QPC_COUNT		(64 * 1024)
#घोषणा BNXT_RE_MAX_MRW_COUNT		(64 * 1024)
#घोषणा BNXT_RE_MAX_SRQC_COUNT		(64 * 1024)
#घोषणा BNXT_RE_MAX_CQ_COUNT		(64 * 1024)
#घोषणा BNXT_RE_MAX_MRW_COUNT_64K	(64 * 1024)
#घोषणा BNXT_RE_MAX_MRW_COUNT_256K	(256 * 1024)

/* Number of MRs to reserve क्रम PF, leaving reमुख्यder क्रम VFs */
#घोषणा BNXT_RE_RESVD_MR_FOR_PF         (32 * 1024)
#घोषणा BNXT_RE_MAX_GID_PER_VF          128

/*
 * Percentage of resources of each type reserved क्रम PF.
 * Reमुख्यing resources are भागided equally among VFs.
 * [0, 100]
 */
#घोषणा BNXT_RE_PCT_RSVD_FOR_PF         50

#घोषणा BNXT_RE_UD_QP_HW_STALL		0x400000

#घोषणा BNXT_RE_RQ_WQE_THRESHOLD	32

/*
 * Setting the शेष ack delay value to 16, which means
 * the शेष समयout is approx. 260ms(4 usec * 2 ^(समयout))
 */

#घोषणा BNXT_RE_DEFAULT_ACK_DELAY	16

काष्ठा bnxt_re_ring_attr अणु
	dma_addr_t	*dma_arr;
	पूर्णांक		pages;
	पूर्णांक		type;
	u32		depth;
	u32		lrid; /* Logical ring id */
	u8		mode;
पूर्ण;

काष्ठा bnxt_re_work अणु
	काष्ठा work_काष्ठा	work;
	अचिन्हित दीर्घ		event;
	काष्ठा bnxt_re_dev      *rdev;
	काष्ठा net_device	*vlan_dev;
पूर्ण;

काष्ठा bnxt_re_sqp_entries अणु
	काष्ठा bnxt_qplib_sge sge;
	u64 wrid;
	/* For storing the actual qp1 cqe */
	काष्ठा bnxt_qplib_cqe cqe;
	काष्ठा bnxt_re_qp *qp1_qp;
पूर्ण;

#घोषणा BNXT_RE_MAX_GSI_SQP_ENTRIES	1024
काष्ठा bnxt_re_gsi_context अणु
	काष्ठा	bnxt_re_qp *gsi_qp;
	काष्ठा	bnxt_re_qp *gsi_sqp;
	काष्ठा	bnxt_re_ah *gsi_sah;
	काष्ठा	bnxt_re_sqp_entries *sqp_tbl;
पूर्ण;

#घोषणा BNXT_RE_MIN_MSIX		2
#घोषणा BNXT_RE_MAX_MSIX		9
#घोषणा BNXT_RE_AEQ_IDX			0
#घोषणा BNXT_RE_NQ_IDX			1
#घोषणा BNXT_RE_GEN_P5_MAX_VF		64

काष्ठा bnxt_re_dev अणु
	काष्ठा ib_device		ibdev;
	काष्ठा list_head		list;
	अचिन्हित दीर्घ			flags;
#घोषणा BNXT_RE_FLAG_NETDEV_REGISTERED		0
#घोषणा BNXT_RE_FLAG_GOT_MSIX			2
#घोषणा BNXT_RE_FLAG_HAVE_L2_REF		3
#घोषणा BNXT_RE_FLAG_RCFW_CHANNEL_EN		4
#घोषणा BNXT_RE_FLAG_QOS_WORK_REG		5
#घोषणा BNXT_RE_FLAG_RESOURCES_ALLOCATED	7
#घोषणा BNXT_RE_FLAG_RESOURCES_INITIALIZED	8
#घोषणा BNXT_RE_FLAG_ERR_DEVICE_DETACHED       17
#घोषणा BNXT_RE_FLAG_ISSUE_ROCE_STATS          29
	काष्ठा net_device		*netdev;
	अचिन्हित पूर्णांक			version, major, minor;
	काष्ठा bnxt_qplib_chip_ctx	*chip_ctx;
	काष्ठा bnxt_en_dev		*en_dev;
	काष्ठा bnxt_msix_entry		msix_entries[BNXT_RE_MAX_MSIX];
	पूर्णांक				num_msix;

	पूर्णांक				id;

	काष्ठा delayed_work		worker;
	u8				cur_prio_map;
	u16				active_speed;
	u8				active_width;

	/* FP Notअगरication Queue (CQ & SRQ) */
	काष्ठा tasklet_काष्ठा		nq_task;

	/* RCFW Channel */
	काष्ठा bnxt_qplib_rcfw		rcfw;

	/* NQ */
	काष्ठा bnxt_qplib_nq		nq[BNXT_RE_MAX_MSIX];

	/* Device Resources */
	काष्ठा bnxt_qplib_dev_attr	dev_attr;
	काष्ठा bnxt_qplib_ctx		qplib_ctx;
	काष्ठा bnxt_qplib_res		qplib_res;
	काष्ठा bnxt_qplib_dpi		dpi_privileged;

	atomic_t			qp_count;
	काष्ठा mutex			qp_lock;	/* protect qp list */
	काष्ठा list_head		qp_list;

	atomic_t			cq_count;
	atomic_t			srq_count;
	atomic_t			mr_count;
	atomic_t			mw_count;
	/* Max of 2 lossless traffic class supported per port */
	u16				cosq[2];

	/* QP क्रम क्रम handling QP1 packets */
	काष्ठा bnxt_re_gsi_context	gsi_ctx;
	atomic_t nq_alloc_cnt;
	u32 is_virtfn;
	u32 num_vfs;
	काष्ठा bnxt_qplib_roce_stats	stats;
पूर्ण;

#घोषणा to_bnxt_re_dev(ptr, member)	\
	container_of((ptr), काष्ठा bnxt_re_dev, member)

#घोषणा BNXT_RE_ROCE_V1_PACKET		0
#घोषणा BNXT_RE_ROCEV2_IPV4_PACKET	2
#घोषणा BNXT_RE_ROCEV2_IPV6_PACKET	3

अटल अंतरभूत काष्ठा device *rdev_to_dev(काष्ठा bnxt_re_dev *rdev)
अणु
	अगर (rdev)
		वापस  &rdev->ibdev.dev;
	वापस शून्य;
पूर्ण

#पूर्ण_अगर
