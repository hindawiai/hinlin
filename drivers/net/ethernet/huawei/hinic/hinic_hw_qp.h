<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_QP_H
#घोषणा HINIC_HW_QP_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sizes.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>

#समावेश "hinic_common.h"
#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_wqe.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_qp_ctxt.h"

#घोषणा HINIC_SQ_DB_INFO_PI_HI_SHIFT            0
#घोषणा HINIC_SQ_DB_INFO_QID_SHIFT              8
#घोषणा HINIC_SQ_DB_INFO_PATH_SHIFT             23
#घोषणा HINIC_SQ_DB_INFO_COS_SHIFT              24
#घोषणा HINIC_SQ_DB_INFO_TYPE_SHIFT             27

#घोषणा HINIC_SQ_DB_INFO_PI_HI_MASK             0xFF
#घोषणा HINIC_SQ_DB_INFO_QID_MASK               0x3FF
#घोषणा HINIC_SQ_DB_INFO_PATH_MASK              0x1
#घोषणा HINIC_SQ_DB_INFO_COS_MASK               0x7
#घोषणा HINIC_SQ_DB_INFO_TYPE_MASK              0x1F

#घोषणा HINIC_SQ_DB_INFO_SET(val, member)       \
		(((u32)(val) & HINIC_SQ_DB_INFO_##member##_MASK) \
		 << HINIC_SQ_DB_INFO_##member##_SHIFT)

#घोषणा HINIC_SQ_WQEBB_SIZE                     64
#घोषणा HINIC_RQ_WQEBB_SIZE                     32

#घोषणा HINIC_SQ_PAGE_SIZE                      SZ_256K
#घोषणा HINIC_RQ_PAGE_SIZE                      SZ_256K

#घोषणा HINIC_SQ_DEPTH                          SZ_4K
#घोषणा HINIC_RQ_DEPTH                          SZ_4K

#घोषणा HINIC_MAX_QUEUE_DEPTH			SZ_4K
#घोषणा HINIC_MIN_QUEUE_DEPTH			128

/* In any change to HINIC_RX_BUF_SZ, HINIC_RX_BUF_SZ_IDX must be changed */
#घोषणा HINIC_RX_BUF_SZ                         2048
#घोषणा HINIC_RX_BUF_SZ_IDX			HINIC_RX_BUF_SZ_2048_IDX

#घोषणा HINIC_MIN_TX_WQE_SIZE(wq)               \
		ALIGN(HINIC_SQ_WQE_SIZE(1), (wq)->wqebb_size)

#घोषणा HINIC_MIN_TX_NUM_WQEBBS(sq)             \
		(HINIC_MIN_TX_WQE_SIZE((sq)->wq) / (sq)->wq->wqebb_size)

क्रमागत hinic_rx_buf_sz_idx अणु
	HINIC_RX_BUF_SZ_32_IDX,
	HINIC_RX_BUF_SZ_64_IDX,
	HINIC_RX_BUF_SZ_96_IDX,
	HINIC_RX_BUF_SZ_128_IDX,
	HINIC_RX_BUF_SZ_192_IDX,
	HINIC_RX_BUF_SZ_256_IDX,
	HINIC_RX_BUF_SZ_384_IDX,
	HINIC_RX_BUF_SZ_512_IDX,
	HINIC_RX_BUF_SZ_768_IDX,
	HINIC_RX_BUF_SZ_1024_IDX,
	HINIC_RX_BUF_SZ_1536_IDX,
	HINIC_RX_BUF_SZ_2048_IDX,
	HINIC_RX_BUF_SZ_3072_IDX,
	HINIC_RX_BUF_SZ_4096_IDX,
	HINIC_RX_BUF_SZ_8192_IDX,
	HINIC_RX_BUF_SZ_16384_IDX,
पूर्ण;

काष्ठा hinic_sq अणु
	काष्ठा hinic_hwअगर       *hwअगर;

	काष्ठा hinic_wq         *wq;

	u16			qid;

	u32                     irq;
	u16                     msix_entry;

	व्योम                    *hw_ci_addr;
	dma_addr_t              hw_ci_dma_addr;

	व्योम __iomem            *db_base;

	काष्ठा sk_buff          **saved_skb;
	काष्ठा hinic_debug_priv	*dbg;
पूर्ण;

काष्ठा hinic_rq अणु
	काष्ठा hinic_hwअगर       *hwअगर;

	काष्ठा hinic_wq         *wq;

	u16			qid;

	काष्ठा cpumask		affinity_mask;
	u32                     irq;
	u16                     msix_entry;

	माप_प्रकार                  buf_sz;

	काष्ठा sk_buff          **saved_skb;

	काष्ठा hinic_rq_cqe     **cqe;
	dma_addr_t              *cqe_dma;

	u16                     *pi_virt_addr;
	dma_addr_t              pi_dma_addr;
	काष्ठा hinic_debug_priv	*dbg;
पूर्ण;

काष्ठा hinic_qp अणु
	काष्ठा hinic_sq         sq;
	काष्ठा hinic_rq         rq;

	u16     q_id;
पूर्ण;

व्योम hinic_qp_prepare_header(काष्ठा hinic_qp_ctxt_header *qp_ctxt_hdr,
			     क्रमागत hinic_qp_ctxt_type ctxt_type,
			     u16 num_queues, u16 max_queues);

व्योम hinic_sq_prepare_ctxt(काष्ठा hinic_sq_ctxt *sq_ctxt,
			   काष्ठा hinic_sq *sq, u16 global_qid);

व्योम hinic_rq_prepare_ctxt(काष्ठा hinic_rq_ctxt *rq_ctxt,
			   काष्ठा hinic_rq *rq, u16 global_qid);

पूर्णांक hinic_init_sq(काष्ठा hinic_sq *sq, काष्ठा hinic_hwअगर *hwअगर,
		  काष्ठा hinic_wq *wq, काष्ठा msix_entry *entry, व्योम *ci_addr,
		  dma_addr_t ci_dma_addr, व्योम __iomem *db_base);

व्योम hinic_clean_sq(काष्ठा hinic_sq *sq);

पूर्णांक hinic_init_rq(काष्ठा hinic_rq *rq, काष्ठा hinic_hwअगर *hwअगर,
		  काष्ठा hinic_wq *wq, काष्ठा msix_entry *entry);

व्योम hinic_clean_rq(काष्ठा hinic_rq *rq);

पूर्णांक hinic_get_sq_मुक्त_wqebbs(काष्ठा hinic_sq *sq);

पूर्णांक hinic_get_rq_मुक्त_wqebbs(काष्ठा hinic_rq *rq);

व्योम hinic_task_set_l2hdr(काष्ठा hinic_sq_task *task, u32 len);

व्योम hinic_task_set_outter_l3(काष्ठा hinic_sq_task *task,
			      क्रमागत hinic_l3_offload_type l3_type,
			      u32 network_len);

व्योम hinic_task_set_inner_l3(काष्ठा hinic_sq_task *task,
			     क्रमागत hinic_l3_offload_type l3_type,
			     u32 network_len);

व्योम hinic_task_set_tunnel_l4(काष्ठा hinic_sq_task *task,
			      क्रमागत hinic_l4_tunnel_type l4_type,
			      u32 tunnel_len);

व्योम hinic_set_cs_inner_l4(काष्ठा hinic_sq_task *task,
			   u32 *queue_info,
			   क्रमागत hinic_l4_offload_type l4_offload,
			   u32 l4_len, u32 offset);

व्योम hinic_set_tso_inner_l4(काष्ठा hinic_sq_task *task,
			    u32 *queue_info,
			    क्रमागत hinic_l4_offload_type l4_offload,
			    u32 l4_len,
			    u32 offset, u32 ip_ident, u32 mss);

व्योम hinic_sq_prepare_wqe(काष्ठा hinic_sq *sq, u16 prod_idx,
			  काष्ठा hinic_sq_wqe *wqe, काष्ठा hinic_sge *sges,
			  पूर्णांक nr_sges);

व्योम hinic_sq_ग_लिखो_db(काष्ठा hinic_sq *sq, u16 prod_idx, अचिन्हित पूर्णांक wqe_size,
		       अचिन्हित पूर्णांक cos);

काष्ठा hinic_sq_wqe *hinic_sq_get_wqe(काष्ठा hinic_sq *sq,
				      अचिन्हित पूर्णांक wqe_size, u16 *prod_idx);

व्योम hinic_sq_वापस_wqe(काष्ठा hinic_sq *sq, अचिन्हित पूर्णांक wqe_size);

व्योम hinic_sq_ग_लिखो_wqe(काष्ठा hinic_sq *sq, u16 prod_idx,
			काष्ठा hinic_sq_wqe *wqe, काष्ठा sk_buff *skb,
			अचिन्हित पूर्णांक wqe_size);

काष्ठा hinic_sq_wqe *hinic_sq_पढ़ो_wqe(काष्ठा hinic_sq *sq,
				       काष्ठा sk_buff **skb,
				       अचिन्हित पूर्णांक wqe_size, u16 *cons_idx);

काष्ठा hinic_sq_wqe *hinic_sq_पढ़ो_wqebb(काष्ठा hinic_sq *sq,
					 काष्ठा sk_buff **skb,
					 अचिन्हित पूर्णांक *wqe_size, u16 *cons_idx);

व्योम hinic_sq_put_wqe(काष्ठा hinic_sq *sq, अचिन्हित पूर्णांक wqe_size);

व्योम hinic_sq_get_sges(काष्ठा hinic_sq_wqe *wqe, काष्ठा hinic_sge *sges,
		       पूर्णांक nr_sges);

काष्ठा hinic_rq_wqe *hinic_rq_get_wqe(काष्ठा hinic_rq *rq,
				      अचिन्हित पूर्णांक wqe_size, u16 *prod_idx);

व्योम hinic_rq_ग_लिखो_wqe(काष्ठा hinic_rq *rq, u16 prod_idx,
			काष्ठा hinic_rq_wqe *wqe, काष्ठा sk_buff *skb);

काष्ठा hinic_rq_wqe *hinic_rq_पढ़ो_wqe(काष्ठा hinic_rq *rq,
				       अचिन्हित पूर्णांक wqe_size,
				       काष्ठा sk_buff **skb, u16 *cons_idx);

काष्ठा hinic_rq_wqe *hinic_rq_पढ़ो_next_wqe(काष्ठा hinic_rq *rq,
					    अचिन्हित पूर्णांक wqe_size,
					    काष्ठा sk_buff **skb,
					    u16 *cons_idx);

व्योम hinic_rq_put_wqe(काष्ठा hinic_rq *rq, u16 cons_idx,
		      अचिन्हित पूर्णांक wqe_size);

व्योम hinic_rq_get_sge(काष्ठा hinic_rq *rq, काष्ठा hinic_rq_wqe *wqe,
		      u16 cons_idx, काष्ठा hinic_sge *sge);

व्योम hinic_rq_prepare_wqe(काष्ठा hinic_rq *rq, u16 prod_idx,
			  काष्ठा hinic_rq_wqe *wqe, काष्ठा hinic_sge *sge);

व्योम hinic_rq_update(काष्ठा hinic_rq *rq, u16 prod_idx);

#पूर्ण_अगर
