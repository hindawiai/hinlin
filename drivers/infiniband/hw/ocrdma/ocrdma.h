<शैली गुरु>
/* This file is part of the Emulex RoCE Device Driver क्रम
 * RoCE (RDMA over Converged Ethernet) adapters.
 * Copyright (C) 2012-2015 Emulex. All rights reserved.
 * EMULEX and SLI are trademarks of Emulex.
 * www.emulex.com
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the मुख्य
 * directory of this source tree, or the BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary क्रमm must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

#अगर_अघोषित __OCRDMA_H__
#घोषणा __OCRDMA_H__

#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_addr.h>

#समावेश <be_roce.h>
#समावेश "ocrdma_sli.h"

#घोषणा OCRDMA_ROCE_DRV_VERSION "11.0.0.0"

#घोषणा OCRDMA_ROCE_DRV_DESC "Emulex OneConnect RoCE Driver"
#घोषणा OCRDMA_NODE_DESC "Emulex OneConnect RoCE HCA"

#घोषणा OC_NAME_SH	OCRDMA_NODE_DESC "(Skyhawk)"
#घोषणा OC_NAME_UNKNOWN OCRDMA_NODE_DESC "(Unknown)"

#घोषणा OC_SKH_DEVICE_PF 0x720
#घोषणा OC_SKH_DEVICE_VF 0x728
#घोषणा OCRDMA_MAX_AH 512

#घोषणा OCRDMA_UVERBS(CMD_NAME) (1ull << IB_USER_VERBS_CMD_##CMD_NAME)

#घोषणा convert_to_64bit(lo, hi) ((u64)hi << 32 | (u64)lo)
#घोषणा EQ_INTR_PER_SEC_THRSH_HI 150000
#घोषणा EQ_INTR_PER_SEC_THRSH_LOW 100000
#घोषणा EQ_AIC_MAX_EQD 20
#घोषणा EQ_AIC_MIN_EQD 0

व्योम ocrdma_eqd_set_task(काष्ठा work_काष्ठा *work);

काष्ठा ocrdma_dev_attr अणु
	u8 fw_ver[32];
	u32 venकरोr_id;
	u32 device_id;
	u16 max_pd;
	u16 max_dpp_pds;
	u16 max_cq;
	u16 max_cqe;
	u16 max_qp;
	u16 max_wqe;
	u16 max_rqe;
	u16 max_srq;
	u32 max_अंतरभूत_data;
	पूर्णांक max_send_sge;
	पूर्णांक max_recv_sge;
	पूर्णांक max_srq_sge;
	पूर्णांक max_rdma_sge;
	पूर्णांक max_mr;
	u64 max_mr_size;
	u32 max_num_mr_pbl;
	पूर्णांक max_mw;
	पूर्णांक max_map_per_fmr;
	पूर्णांक max_pages_per_frmr;
	u16 max_ord_per_qp;
	u16 max_ird_per_qp;

	पूर्णांक device_cap_flags;
	u8 cq_overflow_detect;
	u8 srq_supported;

	u32 wqe_size;
	u32 rqe_size;
	u32 ird_page_size;
	u8 local_ca_ack_delay;
	u8 ird;
	u8 num_ird_pages;
	u8 udp_encap;
पूर्ण;

काष्ठा ocrdma_dma_mem अणु
	व्योम *va;
	dma_addr_t pa;
	u32 size;
पूर्ण;

काष्ठा ocrdma_pbl अणु
	व्योम *va;
	dma_addr_t pa;
पूर्ण;

काष्ठा ocrdma_queue_info अणु
	व्योम *va;
	dma_addr_t dma;
	u32 size;
	u16 len;
	u16 entry_size;		/* Size of an element in the queue */
	u16 id;			/* qid, where to ring the करोorbell. */
	u16 head, tail;
	bool created;
पूर्ण;

काष्ठा ocrdma_aic_obj अणु         /* Adaptive पूर्णांकerrupt coalescing (AIC) info */
	u32 prev_eqd;
	u64 eq_पूर्णांकr_cnt;
	u64 prev_eq_पूर्णांकr_cnt;
पूर्ण;

काष्ठा ocrdma_eq अणु
	काष्ठा ocrdma_queue_info q;
	u32 vector;
	पूर्णांक cq_cnt;
	काष्ठा ocrdma_dev *dev;
	अक्षर irq_name[32];
	काष्ठा ocrdma_aic_obj aic_obj;
पूर्ण;

काष्ठा ocrdma_mq अणु
	काष्ठा ocrdma_queue_info sq;
	काष्ठा ocrdma_queue_info cq;
	bool rearm_cq;
पूर्ण;

काष्ठा mqe_ctx अणु
	काष्ठा mutex lock; /* क्रम serializing mailbox commands on MQ */
	रुको_queue_head_t cmd_रुको;
	u32 tag;
	u16 cqe_status;
	u16 ext_status;
	bool cmd_करोne;
	bool fw_error_state;
पूर्ण;

काष्ठा ocrdma_hw_mr अणु
	u32 lkey;
	u8 fr_mr;
	u8 remote_atomic;
	u8 remote_rd;
	u8 remote_wr;
	u8 local_rd;
	u8 local_wr;
	u8 mw_bind;
	u8 rsvd;
	u64 len;
	काष्ठा ocrdma_pbl *pbl_table;
	u32 num_pbls;
	u32 num_pbes;
	u32 pbl_size;
	u32 pbe_size;
	u64 va;
पूर्ण;

काष्ठा ocrdma_mr अणु
	काष्ठा ib_mr ibmr;
	काष्ठा ib_umem *umem;
	काष्ठा ocrdma_hw_mr hwmr;
	u64 *pages;
	u32 npages;
पूर्ण;

काष्ठा ocrdma_stats अणु
	u8 type;
	काष्ठा ocrdma_dev *dev;
पूर्ण;

काष्ठा ocrdma_pd_resource_mgr अणु
	u32 pd_norm_start;
	u16 pd_norm_count;
	u16 pd_norm_thrsh;
	u16 max_normal_pd;
	u32 pd_dpp_start;
	u16 pd_dpp_count;
	u16 pd_dpp_thrsh;
	u16 max_dpp_pd;
	u16 dpp_page_index;
	अचिन्हित दीर्घ *pd_norm_biपंचांगap;
	अचिन्हित दीर्घ *pd_dpp_biपंचांगap;
	bool pd_pपुनः_स्मृति_valid;
पूर्ण;

काष्ठा stats_mem अणु
	काष्ठा ocrdma_mqe mqe;
	व्योम *va;
	dma_addr_t pa;
	u32 size;
	अक्षर *debugfs_mem;
पूर्ण;

काष्ठा phy_info अणु
	u16 स्वतः_speeds_supported;
	u16 fixed_speeds_supported;
	u16 phy_type;
	u16 पूर्णांकerface_type;
पूर्ण;

क्रमागत ocrdma_flags अणु
	OCRDMA_FLAGS_LINK_STATUS_INIT = 0x01
पूर्ण;

काष्ठा ocrdma_dev अणु
	काष्ठा ib_device ibdev;
	काष्ठा ocrdma_dev_attr attr;

	काष्ठा mutex dev_lock; /* provides syncronise access to device data */
	spinlock_t flush_q_lock ____cacheline_aligned;

	काष्ठा ocrdma_cq **cq_tbl;
	काष्ठा ocrdma_qp **qp_tbl;

	काष्ठा ocrdma_eq *eq_tbl;
	पूर्णांक eq_cnt;
	काष्ठा delayed_work eqd_work;
	u16 base_eqid;
	u16 max_eq;

	/* provided synchronization to sgid table क्रम
	 * updating gid entries triggered by notअगरier.
	 */
	spinlock_t sgid_lock;

	पूर्णांक gsi_qp_created;
	काष्ठा ocrdma_cq *gsi_sqcq;
	काष्ठा ocrdma_cq *gsi_rqcq;

	काष्ठा अणु
		काष्ठा ocrdma_av *va;
		dma_addr_t pa;
		u32 size;
		u32 num_ah;
		/* provide synchronization क्रम av
		 * entry allocations.
		 */
		spinlock_t lock;
		u32 ahid;
		काष्ठा ocrdma_pbl pbl;
	पूर्ण av_tbl;

	व्योम *mbx_cmd;
	काष्ठा ocrdma_mq mq;
	काष्ठा mqe_ctx mqe_ctx;

	काष्ठा be_dev_info nic_info;
	काष्ठा phy_info phy;
	अक्षर model_number[32];
	u32 hba_port_num;

	काष्ठा list_head entry;
	पूर्णांक id;
	u64 *stag_arr;
	u8 sl; /* service level */
	bool pfc_state;
	atomic_t update_sl;
	u16 pvid;
	u32 asic_id;
	u32 flags;

	uदीर्घ last_stats_समय;
	काष्ठा mutex stats_lock; /* provide synch क्रम debugfs operations */
	काष्ठा stats_mem stats_mem;
	काष्ठा ocrdma_stats rsrc_stats;
	काष्ठा ocrdma_stats rx_stats;
	काष्ठा ocrdma_stats wqe_stats;
	काष्ठा ocrdma_stats tx_stats;
	काष्ठा ocrdma_stats db_err_stats;
	काष्ठा ocrdma_stats tx_qp_err_stats;
	काष्ठा ocrdma_stats rx_qp_err_stats;
	काष्ठा ocrdma_stats tx_dbg_stats;
	काष्ठा ocrdma_stats rx_dbg_stats;
	काष्ठा ocrdma_stats driver_stats;
	काष्ठा ocrdma_stats reset_stats;
	काष्ठा dentry *dir;
	atomic_t async_err_stats[OCRDMA_MAX_ASYNC_ERRORS];
	atomic_t cqe_err_stats[OCRDMA_MAX_CQE_ERR];
	काष्ठा ocrdma_pd_resource_mgr *pd_mgr;
पूर्ण;

काष्ठा ocrdma_cq अणु
	काष्ठा ib_cq ibcq;
	काष्ठा ocrdma_cqe *va;
	u32 phase;
	u32 getp;	/* poपूर्णांकer to pending wrs to
			 * वापस to stack, wrap arounds
			 * at max_hw_cqe
			 */
	u32 max_hw_cqe;
	bool phase_change;
	spinlock_t cq_lock ____cacheline_aligned; /* provide synchronization
						   * to cq polling
						   */
	/* syncronizes cq completion handler invoked from multiple context */
	spinlock_t comp_handler_lock ____cacheline_aligned;
	u16 id;
	u16 eqn;

	काष्ठा ocrdma_ucontext *ucontext;
	dma_addr_t pa;
	u32 len;
	u32 cqe_cnt;

	/* head of all qp's sq and rq क्रम which cqes need to be flushed
	 * by the software.
	 */
	काष्ठा list_head sq_head, rq_head;
पूर्ण;

काष्ठा ocrdma_pd अणु
	काष्ठा ib_pd ibpd;
	काष्ठा ocrdma_ucontext *uctx;
	u32 id;
	पूर्णांक num_dpp_qp;
	u32 dpp_page;
	bool dpp_enabled;
पूर्ण;

काष्ठा ocrdma_ah अणु
	काष्ठा ib_ah ibah;
	काष्ठा ocrdma_av *av;
	u16 sgid_index;
	u32 id;
	u8 hdr_type;
पूर्ण;

काष्ठा ocrdma_qp_hwq_info अणु
	u8 *va;			/* भव address */
	u32 max_sges;
	u32 head, tail;
	u32 entry_size;
	u32 max_cnt;
	u32 max_wqe_idx;
	u16 dbid;		/* qid, where to ring the करोorbell. */
	u32 len;
	dma_addr_t pa;
पूर्ण;

काष्ठा ocrdma_srq अणु
	काष्ठा ib_srq ibsrq;
	u8 __iomem *db;
	काष्ठा ocrdma_qp_hwq_info rq;
	u64 *rqe_wr_id_tbl;
	u32 *idx_bit_fields;
	u32 bit_fields_len;

	/* provide synchronization to multiple context(s) posting rqe */
	spinlock_t q_lock ____cacheline_aligned;

	काष्ठा ocrdma_pd *pd;
	u32 id;
पूर्ण;

काष्ठा ocrdma_qp अणु
	काष्ठा ib_qp ibqp;

	u8 __iomem *sq_db;
	काष्ठा ocrdma_qp_hwq_info sq;
	काष्ठा अणु
		uपूर्णांक64_t wrid;
		uपूर्णांक16_t dpp_wqe_idx;
		uपूर्णांक16_t dpp_wqe;
		uपूर्णांक8_t  संकेतed;
		uपूर्णांक8_t  rsvd[3];
	पूर्ण *wqe_wr_id_tbl;
	u32 max_अंतरभूत_data;

	/* provide synchronization to multiple context(s) posting wqe, rqe */
	spinlock_t q_lock ____cacheline_aligned;
	काष्ठा ocrdma_cq *sq_cq;
	/* list मुख्यtained per CQ to flush SQ errors */
	काष्ठा list_head sq_entry;

	u8 __iomem *rq_db;
	काष्ठा ocrdma_qp_hwq_info rq;
	u64 *rqe_wr_id_tbl;
	काष्ठा ocrdma_cq *rq_cq;
	काष्ठा ocrdma_srq *srq;
	/* list मुख्यtained per CQ to flush RQ errors */
	काष्ठा list_head rq_entry;

	क्रमागत ocrdma_qp_state state;	/*  QP state */
	पूर्णांक cap_flags;
	u32 max_ord, max_ird;

	u32 id;
	काष्ठा ocrdma_pd *pd;

	क्रमागत ib_qp_type qp_type;

	पूर्णांक sgid_idx;
	u32 qkey;
	bool dpp_enabled;
	u8 *ird_q_va;
	bool संकेतed;
पूर्ण;

काष्ठा ocrdma_ucontext अणु
	काष्ठा ib_ucontext ibucontext;

	काष्ठा list_head mm_head;
	काष्ठा mutex mm_list_lock; /* protects list entries of mm type */
	काष्ठा ocrdma_pd *cntxt_pd;
	पूर्णांक pd_in_use;

	काष्ठा अणु
		u32 *va;
		dma_addr_t pa;
		u32 len;
	पूर्ण ah_tbl;
पूर्ण;

काष्ठा ocrdma_mm अणु
	काष्ठा अणु
		u64 phy_addr;
		अचिन्हित दीर्घ len;
	पूर्ण key;
	काष्ठा list_head entry;
पूर्ण;

अटल अंतरभूत काष्ठा ocrdma_dev *get_ocrdma_dev(काष्ठा ib_device *ibdev)
अणु
	वापस container_of(ibdev, काष्ठा ocrdma_dev, ibdev);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_ucontext *get_ocrdma_ucontext(काष्ठा ib_ucontext
							  *ibucontext)
अणु
	वापस container_of(ibucontext, काष्ठा ocrdma_ucontext, ibucontext);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_pd *get_ocrdma_pd(काष्ठा ib_pd *ibpd)
अणु
	वापस container_of(ibpd, काष्ठा ocrdma_pd, ibpd);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_cq *get_ocrdma_cq(काष्ठा ib_cq *ibcq)
अणु
	वापस container_of(ibcq, काष्ठा ocrdma_cq, ibcq);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_qp *get_ocrdma_qp(काष्ठा ib_qp *ibqp)
अणु
	वापस container_of(ibqp, काष्ठा ocrdma_qp, ibqp);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_mr *get_ocrdma_mr(काष्ठा ib_mr *ibmr)
अणु
	वापस container_of(ibmr, काष्ठा ocrdma_mr, ibmr);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_ah *get_ocrdma_ah(काष्ठा ib_ah *ibah)
अणु
	वापस container_of(ibah, काष्ठा ocrdma_ah, ibah);
पूर्ण

अटल अंतरभूत काष्ठा ocrdma_srq *get_ocrdma_srq(काष्ठा ib_srq *ibsrq)
अणु
	वापस container_of(ibsrq, काष्ठा ocrdma_srq, ibsrq);
पूर्ण

अटल अंतरभूत पूर्णांक is_cqe_valid(काष्ठा ocrdma_cq *cq, काष्ठा ocrdma_cqe *cqe)
अणु
	पूर्णांक cqe_valid;
	cqe_valid = le32_to_cpu(cqe->flags_status_srcqpn) & OCRDMA_CQE_VALID;
	वापस (cqe_valid == cq->phase);
पूर्ण

अटल अंतरभूत पूर्णांक is_cqe_क्रम_sq(काष्ठा ocrdma_cqe *cqe)
अणु
	वापस (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_QTYPE) ? 0 : 1;
पूर्ण

अटल अंतरभूत पूर्णांक is_cqe_invalidated(काष्ठा ocrdma_cqe *cqe)
अणु
	वापस (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_INVALIDATE) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_cqe_imm(काष्ठा ocrdma_cqe *cqe)
अणु
	वापस (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_IMM) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_cqe_wr_imm(काष्ठा ocrdma_cqe *cqe)
अणु
	वापस (le32_to_cpu(cqe->flags_status_srcqpn) &
		OCRDMA_CQE_WRITE_IMM) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocrdma_resolve_dmac(काष्ठा ocrdma_dev *dev,
		काष्ठा rdma_ah_attr *ah_attr, u8 *mac_addr)
अणु
	काष्ठा in6_addr in6;

	स_नकल(&in6, rdma_ah_पढ़ो_grh(ah_attr)->dgid.raw, माप(in6));
	अगर (rdma_is_multicast_addr(&in6))
		rdma_get_mcast_mac(&in6, mac_addr);
	अन्यथा अगर (rdma_link_local_addr(&in6))
		rdma_get_ll_mac(&in6, mac_addr);
	अन्यथा
		स_नकल(mac_addr, ah_attr->roce.dmac, ETH_ALEN);
	वापस 0;
पूर्ण

अटल अंतरभूत अक्षर *hca_name(काष्ठा ocrdma_dev *dev)
अणु
	चयन (dev->nic_info.pdev->device) अणु
	हाल OC_SKH_DEVICE_PF:
	हाल OC_SKH_DEVICE_VF:
		वापस OC_NAME_SH;
	शेष:
		वापस OC_NAME_UNKNOWN;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ocrdma_get_eq_table_index(काष्ठा ocrdma_dev *dev,
		पूर्णांक eqid)
अणु
	पूर्णांक indx;

	क्रम (indx = 0; indx < dev->eq_cnt; indx++) अणु
		अगर (dev->eq_tbl[indx].q.id == eqid)
			वापस indx;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत u8 ocrdma_get_asic_type(काष्ठा ocrdma_dev *dev)
अणु
	अगर (dev->nic_info.dev_family == 0xF && !dev->asic_id) अणु
		pci_पढ़ो_config_dword(
			dev->nic_info.pdev,
			OCRDMA_SLI_ASIC_ID_OFFSET, &dev->asic_id);
	पूर्ण

	वापस (dev->asic_id & OCRDMA_SLI_ASIC_GEN_NUM_MASK) >>
				OCRDMA_SLI_ASIC_GEN_NUM_SHIFT;
पूर्ण

अटल अंतरभूत u8 ocrdma_get_pfc_prio(u8 *pfc, u8 prio)
अणु
	वापस *(pfc + prio);
पूर्ण

अटल अंतरभूत u8 ocrdma_get_app_prio(u8 *app_prio, u8 prio)
अणु
	वापस *(app_prio + prio);
पूर्ण

अटल अंतरभूत u8 ocrdma_is_enabled_and_synced(u32 state)
अणु	/* May also be used to पूर्णांकerpret TC-state, QCN-state
	 * Appl-state and Logical-link-state in future.
	 */
	वापस (state & OCRDMA_STATE_FLAG_ENABLED) &&
		(state & OCRDMA_STATE_FLAG_SYNC);
पूर्ण

अटल अंतरभूत u8 ocrdma_get_ae_link_state(u32 ae_state)
अणु
	वापस ((ae_state & OCRDMA_AE_LSC_LS_MASK) >> OCRDMA_AE_LSC_LS_SHIFT);
पूर्ण

अटल अंतरभूत bool ocrdma_is_udp_encap_supported(काष्ठा ocrdma_dev *dev)
अणु
	वापस (dev->attr.udp_encap & OCRDMA_L3_TYPE_IPV4) ||
	       (dev->attr.udp_encap & OCRDMA_L3_TYPE_IPV6);
पूर्ण

#पूर्ण_अगर
