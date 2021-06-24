<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित __RDMA_COMMON__
#घोषणा __RDMA_COMMON__

/************************/
/* RDMA FW CONSTANTS */
/************************/

#घोषणा RDMA_RESERVED_LKEY		(0)
#घोषणा RDMA_RING_PAGE_SIZE		(0x1000)

#घोषणा RDMA_MAX_SGE_PER_SQ_WQE		(4)
#घोषणा RDMA_MAX_SGE_PER_RQ_WQE		(4)

#घोषणा RDMA_MAX_DATA_SIZE_IN_WQE	(0x80000000)

#घोषणा RDMA_REQ_RD_ATOMIC_ELM_SIZE	(0x50)
#घोषणा RDMA_RESP_RD_ATOMIC_ELM_SIZE	(0x20)

#घोषणा RDMA_MAX_CQS			(64 * 1024)
#घोषणा RDMA_MAX_TIDS			(128 * 1024 - 1)
#घोषणा RDMA_MAX_PDS			(64 * 1024)
#घोषणा RDMA_MAX_XRC_SRQS                       (1024)
#घोषणा RDMA_MAX_SRQS                           (32 * 1024)

#घोषणा RDMA_NUM_STATISTIC_COUNTERS	MAX_NUM_VPORTS
#घोषणा RDMA_NUM_STATISTIC_COUNTERS_K2	MAX_NUM_VPORTS_K2
#घोषणा RDMA_NUM_STATISTIC_COUNTERS_BB	MAX_NUM_VPORTS_BB

#घोषणा RDMA_TASK_TYPE (PROTOCOLID_ROCE)

काष्ठा rdma_srq_id अणु
	__le16 srq_idx;
	__le16 opaque_fid;
पूर्ण;

काष्ठा rdma_srq_producers अणु
	__le32 sge_prod;
	__le32 wqe_prod;
पूर्ण;

#पूर्ण_अगर /* __RDMA_COMMON__ */
