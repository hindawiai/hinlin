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

#समावेश <rdma/ib_addr.h>
#समावेश <rdma/ib_pma.h>
#समावेश "ocrdma_stats.h"

अटल काष्ठा dentry *ocrdma_dbgfs_dir;

अटल पूर्णांक ocrdma_add_stat(अक्षर *start, अक्षर *pcur,
				अक्षर *name, u64 count)
अणु
	अक्षर buff[128] = अणु0पूर्ण;
	पूर्णांक cpy_len = 0;

	snम_लिखो(buff, 128, "%s: %llu\n", name, count);
	cpy_len = म_माप(buff);

	अगर (pcur + cpy_len > start + OCRDMA_MAX_DBGFS_MEM) अणु
		pr_err("%s: No space in stats buff\n", __func__);
		वापस 0;
	पूर्ण

	स_नकल(pcur, buff, cpy_len);
	वापस cpy_len;
पूर्ण

bool ocrdma_alloc_stats_resources(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा stats_mem *mem = &dev->stats_mem;

	mutex_init(&dev->stats_lock);
	/* Alloc mbox command mem*/
	mem->size = max_t(u32, माप(काष्ठा ocrdma_rdma_stats_req),
			माप(काष्ठा ocrdma_rdma_stats_resp));

	mem->va = dma_alloc_coherent(&dev->nic_info.pdev->dev, mem->size,
				     &mem->pa, GFP_KERNEL);
	अगर (!mem->va) अणु
		pr_err("%s: stats mbox allocation failed\n", __func__);
		वापस false;
	पूर्ण

	/* Alloc debugfs mem */
	mem->debugfs_mem = kzalloc(OCRDMA_MAX_DBGFS_MEM, GFP_KERNEL);
	अगर (!mem->debugfs_mem)
		वापस false;

	वापस true;
पूर्ण

व्योम ocrdma_release_stats_resources(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा stats_mem *mem = &dev->stats_mem;

	अगर (mem->va)
		dma_मुक्त_coherent(&dev->nic_info.pdev->dev, mem->size,
				  mem->va, mem->pa);
	mem->va = शून्य;
	kमुक्त(mem->debugfs_mem);
पूर्ण

अटल अक्षर *ocrdma_resource_stats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
			(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_rsrc_stats *rsrc_stats = &rdma_stats->act_rsrc_stats;

	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "active_dpp_pds",
				(u64)rsrc_stats->dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "active_non_dpp_pds",
				(u64)rsrc_stats->non_dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "active_rc_dpp_qps",
				(u64)rsrc_stats->rc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_uc_dpp_qps",
				(u64)rsrc_stats->uc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_ud_dpp_qps",
				(u64)rsrc_stats->ud_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_rc_non_dpp_qps",
				(u64)rsrc_stats->rc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_uc_non_dpp_qps",
				(u64)rsrc_stats->uc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_ud_non_dpp_qps",
				(u64)rsrc_stats->ud_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_srqs",
				(u64)rsrc_stats->srqs);
	pcur += ocrdma_add_stat(stats, pcur, "active_rbqs",
				(u64)rsrc_stats->rbqs);
	pcur += ocrdma_add_stat(stats, pcur, "active_64K_nsmr",
				(u64)rsrc_stats->r64K_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_64K_to_2M_nsmr",
				(u64)rsrc_stats->r64K_to_2M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_2M_to_44M_nsmr",
				(u64)rsrc_stats->r2M_to_44M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_44M_to_1G_nsmr",
				(u64)rsrc_stats->r44M_to_1G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_1G_to_4G_nsmr",
				(u64)rsrc_stats->r1G_to_4G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_nsmr_count_4G_to_32G",
				(u64)rsrc_stats->nsmr_count_4G_to_32G);
	pcur += ocrdma_add_stat(stats, pcur, "active_32G_to_64G_nsmr",
				(u64)rsrc_stats->r32G_to_64G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_64G_to_128G_nsmr",
				(u64)rsrc_stats->r64G_to_128G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_128G_to_higher_nsmr",
				(u64)rsrc_stats->r128G_to_higher_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_embedded_nsmr",
				(u64)rsrc_stats->embedded_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_frmr",
				(u64)rsrc_stats->frmr);
	pcur += ocrdma_add_stat(stats, pcur, "active_prefetch_qps",
				(u64)rsrc_stats->prefetch_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_ondemand_qps",
				(u64)rsrc_stats->ondemand_qps);
	pcur += ocrdma_add_stat(stats, pcur, "active_phy_mr",
				(u64)rsrc_stats->phy_mr);
	pcur += ocrdma_add_stat(stats, pcur, "active_mw",
				(u64)rsrc_stats->mw);

	/* Prपूर्णांक the threshold stats */
	rsrc_stats = &rdma_stats->th_rsrc_stats;

	pcur += ocrdma_add_stat(stats, pcur, "threshold_dpp_pds",
				(u64)rsrc_stats->dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_non_dpp_pds",
				(u64)rsrc_stats->non_dpp_pds);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_rc_dpp_qps",
				(u64)rsrc_stats->rc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_uc_dpp_qps",
				(u64)rsrc_stats->uc_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_ud_dpp_qps",
				(u64)rsrc_stats->ud_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_rc_non_dpp_qps",
				(u64)rsrc_stats->rc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_uc_non_dpp_qps",
				(u64)rsrc_stats->uc_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_ud_non_dpp_qps",
				(u64)rsrc_stats->ud_non_dpp_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_srqs",
				(u64)rsrc_stats->srqs);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_rbqs",
				(u64)rsrc_stats->rbqs);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_64K_nsmr",
				(u64)rsrc_stats->r64K_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_64K_to_2M_nsmr",
				(u64)rsrc_stats->r64K_to_2M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_2M_to_44M_nsmr",
				(u64)rsrc_stats->r2M_to_44M_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_44M_to_1G_nsmr",
				(u64)rsrc_stats->r44M_to_1G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_1G_to_4G_nsmr",
				(u64)rsrc_stats->r1G_to_4G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_nsmr_count_4G_to_32G",
				(u64)rsrc_stats->nsmr_count_4G_to_32G);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_32G_to_64G_nsmr",
				(u64)rsrc_stats->r32G_to_64G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_64G_to_128G_nsmr",
				(u64)rsrc_stats->r64G_to_128G_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_128G_to_higher_nsmr",
				(u64)rsrc_stats->r128G_to_higher_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_embedded_nsmr",
				(u64)rsrc_stats->embedded_nsmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_frmr",
				(u64)rsrc_stats->frmr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_prefetch_qps",
				(u64)rsrc_stats->prefetch_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_ondemand_qps",
				(u64)rsrc_stats->ondemand_qps);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_phy_mr",
				(u64)rsrc_stats->phy_mr);
	pcur += ocrdma_add_stat(stats, pcur, "threshold_mw",
				(u64)rsrc_stats->mw);
	वापस stats;
पूर्ण

अटल अक्षर *ocrdma_rx_stats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_rx_stats *rx_stats = &rdma_stats->rx_stats;

	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat
		(stats, pcur, "roce_frame_bytes",
		 convert_to_64bit(rx_stats->roce_frame_bytes_lo,
		 rx_stats->roce_frame_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "roce_frame_icrc_drops",
				(u64)rx_stats->roce_frame_icrc_drops);
	pcur += ocrdma_add_stat(stats, pcur, "roce_frame_payload_len_drops",
				(u64)rx_stats->roce_frame_payload_len_drops);
	pcur += ocrdma_add_stat(stats, pcur, "ud_drops",
				(u64)rx_stats->ud_drops);
	pcur += ocrdma_add_stat(stats, pcur, "qp1_drops",
				(u64)rx_stats->qp1_drops);
	pcur += ocrdma_add_stat(stats, pcur, "psn_error_request_packets",
				(u64)rx_stats->psn_error_request_packets);
	pcur += ocrdma_add_stat(stats, pcur, "psn_error_resp_packets",
				(u64)rx_stats->psn_error_resp_packets);
	pcur += ocrdma_add_stat(stats, pcur, "rnr_nak_timeouts",
				(u64)rx_stats->rnr_nak_समयouts);
	pcur += ocrdma_add_stat(stats, pcur, "rnr_nak_receives",
				(u64)rx_stats->rnr_nak_receives);
	pcur += ocrdma_add_stat(stats, pcur, "roce_frame_rxmt_drops",
				(u64)rx_stats->roce_frame_rxmt_drops);
	pcur += ocrdma_add_stat(stats, pcur, "nak_count_psn_sequence_errors",
				(u64)rx_stats->nak_count_psn_sequence_errors);
	pcur += ocrdma_add_stat(stats, pcur, "rc_drop_count_lookup_errors",
				(u64)rx_stats->rc_drop_count_lookup_errors);
	pcur += ocrdma_add_stat(stats, pcur, "rq_rnr_naks",
				(u64)rx_stats->rq_rnr_naks);
	pcur += ocrdma_add_stat(stats, pcur, "srq_rnr_naks",
				(u64)rx_stats->srq_rnr_naks);
	pcur += ocrdma_add_stat(stats, pcur, "roce_frames",
				convert_to_64bit(rx_stats->roce_frames_lo,
						 rx_stats->roce_frames_hi));

	वापस stats;
पूर्ण

अटल u64 ocrdma_sysfs_rcv_pkts(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_rx_stats *rx_stats = &rdma_stats->rx_stats;

	वापस convert_to_64bit(rx_stats->roce_frames_lo,
		rx_stats->roce_frames_hi) + (u64)rx_stats->roce_frame_icrc_drops
		+ (u64)rx_stats->roce_frame_payload_len_drops;
पूर्ण

अटल u64 ocrdma_sysfs_rcv_data(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_rx_stats *rx_stats = &rdma_stats->rx_stats;

	वापस (convert_to_64bit(rx_stats->roce_frame_bytes_lo,
		rx_stats->roce_frame_bytes_hi))/4;
पूर्ण

अटल अक्षर *ocrdma_tx_stats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_tx_stats *tx_stats = &rdma_stats->tx_stats;

	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "send_pkts",
				convert_to_64bit(tx_stats->send_pkts_lo,
						 tx_stats->send_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "write_pkts",
				convert_to_64bit(tx_stats->ग_लिखो_pkts_lo,
						 tx_stats->ग_लिखो_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_pkts",
				convert_to_64bit(tx_stats->पढ़ो_pkts_lo,
						 tx_stats->पढ़ो_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_rsp_pkts",
				convert_to_64bit(tx_stats->पढ़ो_rsp_pkts_lo,
						 tx_stats->पढ़ो_rsp_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "ack_pkts",
				convert_to_64bit(tx_stats->ack_pkts_lo,
						 tx_stats->ack_pkts_hi));
	pcur += ocrdma_add_stat(stats, pcur, "send_bytes",
				convert_to_64bit(tx_stats->send_bytes_lo,
						 tx_stats->send_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "write_bytes",
				convert_to_64bit(tx_stats->ग_लिखो_bytes_lo,
						 tx_stats->ग_लिखो_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_req_bytes",
				convert_to_64bit(tx_stats->पढ़ो_req_bytes_lo,
						 tx_stats->पढ़ो_req_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_rsp_bytes",
				convert_to_64bit(tx_stats->पढ़ो_rsp_bytes_lo,
						 tx_stats->पढ़ो_rsp_bytes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "ack_timeouts",
				(u64)tx_stats->ack_समयouts);

	वापस stats;
पूर्ण

अटल u64 ocrdma_sysfs_xmit_pkts(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_tx_stats *tx_stats = &rdma_stats->tx_stats;

	वापस (convert_to_64bit(tx_stats->send_pkts_lo,
				 tx_stats->send_pkts_hi) +
	convert_to_64bit(tx_stats->ग_लिखो_pkts_lo, tx_stats->ग_लिखो_pkts_hi) +
	convert_to_64bit(tx_stats->पढ़ो_pkts_lo, tx_stats->पढ़ो_pkts_hi) +
	convert_to_64bit(tx_stats->पढ़ो_rsp_pkts_lo,
			 tx_stats->पढ़ो_rsp_pkts_hi) +
	convert_to_64bit(tx_stats->ack_pkts_lo, tx_stats->ack_pkts_hi));
पूर्ण

अटल u64 ocrdma_sysfs_xmit_data(काष्ठा ocrdma_dev *dev)
अणु
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_tx_stats *tx_stats = &rdma_stats->tx_stats;

	वापस (convert_to_64bit(tx_stats->send_bytes_lo,
				 tx_stats->send_bytes_hi) +
		convert_to_64bit(tx_stats->ग_लिखो_bytes_lo,
				 tx_stats->ग_लिखो_bytes_hi) +
		convert_to_64bit(tx_stats->पढ़ो_req_bytes_lo,
				 tx_stats->पढ़ो_req_bytes_hi) +
		convert_to_64bit(tx_stats->पढ़ो_rsp_bytes_lo,
				 tx_stats->पढ़ो_rsp_bytes_hi))/4;
पूर्ण

अटल अक्षर *ocrdma_wqe_stats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_wqe_stats	*wqe_stats = &rdma_stats->wqe_stats;

	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "large_send_rc_wqes",
		convert_to_64bit(wqe_stats->large_send_rc_wqes_lo,
				 wqe_stats->large_send_rc_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "large_write_rc_wqes",
		convert_to_64bit(wqe_stats->large_ग_लिखो_rc_wqes_lo,
				 wqe_stats->large_ग_लिखो_rc_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "read_wqes",
				convert_to_64bit(wqe_stats->पढ़ो_wqes_lo,
						 wqe_stats->पढ़ो_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "frmr_wqes",
				convert_to_64bit(wqe_stats->frmr_wqes_lo,
						 wqe_stats->frmr_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "mw_bind_wqes",
				convert_to_64bit(wqe_stats->mw_bind_wqes_lo,
						 wqe_stats->mw_bind_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "invalidate_wqes",
		convert_to_64bit(wqe_stats->invalidate_wqes_lo,
				 wqe_stats->invalidate_wqes_hi));
	pcur += ocrdma_add_stat(stats, pcur, "dpp_wqe_drops",
				(u64)wqe_stats->dpp_wqe_drops);
	वापस stats;
पूर्ण

अटल अक्षर *ocrdma_db_errstats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_db_err_stats *db_err_stats = &rdma_stats->db_err_stats;

	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "sq_doorbell_errors",
				(u64)db_err_stats->sq_करोorbell_errors);
	pcur += ocrdma_add_stat(stats, pcur, "cq_doorbell_errors",
				(u64)db_err_stats->cq_करोorbell_errors);
	pcur += ocrdma_add_stat(stats, pcur, "rq_srq_doorbell_errors",
				(u64)db_err_stats->rq_srq_करोorbell_errors);
	pcur += ocrdma_add_stat(stats, pcur, "cq_overflow_errors",
				(u64)db_err_stats->cq_overflow_errors);
	वापस stats;
पूर्ण

अटल अक्षर *ocrdma_rxqp_errstats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_rx_qp_err_stats *rx_qp_err_stats =
		 &rdma_stats->rx_qp_err_stats;

	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "nak_invalid_request_errors",
			(u64)rx_qp_err_stats->nak_invalid_request_errors);
	pcur += ocrdma_add_stat(stats, pcur, "nak_remote_operation_errors",
			(u64)rx_qp_err_stats->nak_remote_operation_errors);
	pcur += ocrdma_add_stat(stats, pcur, "nak_count_remote_access_errors",
			(u64)rx_qp_err_stats->nak_count_remote_access_errors);
	pcur += ocrdma_add_stat(stats, pcur, "local_length_errors",
			(u64)rx_qp_err_stats->local_length_errors);
	pcur += ocrdma_add_stat(stats, pcur, "local_protection_errors",
			(u64)rx_qp_err_stats->local_protection_errors);
	pcur += ocrdma_add_stat(stats, pcur, "local_qp_operation_errors",
			(u64)rx_qp_err_stats->local_qp_operation_errors);
	वापस stats;
पूर्ण

अटल अक्षर *ocrdma_txqp_errstats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_tx_qp_err_stats *tx_qp_err_stats =
		&rdma_stats->tx_qp_err_stats;

	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "local_length_errors",
			(u64)tx_qp_err_stats->local_length_errors);
	pcur += ocrdma_add_stat(stats, pcur, "local_protection_errors",
			(u64)tx_qp_err_stats->local_protection_errors);
	pcur += ocrdma_add_stat(stats, pcur, "local_qp_operation_errors",
			(u64)tx_qp_err_stats->local_qp_operation_errors);
	pcur += ocrdma_add_stat(stats, pcur, "retry_count_exceeded_errors",
			(u64)tx_qp_err_stats->retry_count_exceeded_errors);
	pcur += ocrdma_add_stat(stats, pcur, "rnr_retry_count_exceeded_errors",
			(u64)tx_qp_err_stats->rnr_retry_count_exceeded_errors);
	वापस stats;
पूर्ण

अटल अक्षर *ocrdma_tx_dbg_stats(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक i;
	अक्षर *pstats = dev->stats_mem.debugfs_mem;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_tx_dbg_stats *tx_dbg_stats =
		&rdma_stats->tx_dbg_stats;

	स_रखो(pstats, 0, (OCRDMA_MAX_DBGFS_MEM));

	क्रम (i = 0; i < 100; i++)
		pstats += snम_लिखो(pstats, 80, "DW[%d] = 0x%x\n", i,
				 tx_dbg_stats->data[i]);

	वापस dev->stats_mem.debugfs_mem;
पूर्ण

अटल अक्षर *ocrdma_rx_dbg_stats(काष्ठा ocrdma_dev *dev)
अणु
	पूर्णांक i;
	अक्षर *pstats = dev->stats_mem.debugfs_mem;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		(काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_rx_dbg_stats *rx_dbg_stats =
		&rdma_stats->rx_dbg_stats;

	स_रखो(pstats, 0, (OCRDMA_MAX_DBGFS_MEM));

	क्रम (i = 0; i < 200; i++)
		pstats += snम_लिखो(pstats, 80, "DW[%d] = 0x%x\n", i,
				 rx_dbg_stats->data[i]);

	वापस dev->stats_mem.debugfs_mem;
पूर्ण

अटल अक्षर *ocrdma_driver_dbg_stats(काष्ठा ocrdma_dev *dev)
अणु
	अक्षर *stats = dev->stats_mem.debugfs_mem, *pcur;


	स_रखो(stats, 0, (OCRDMA_MAX_DBGFS_MEM));

	pcur = stats;
	pcur += ocrdma_add_stat(stats, pcur, "async_cq_err",
				(u64)(dev->async_err_stats
				[OCRDMA_CQ_ERROR].counter));
	pcur += ocrdma_add_stat(stats, pcur, "async_cq_overrun_err",
				(u64)dev->async_err_stats
				[OCRDMA_CQ_OVERRUN_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_cq_qpcat_err",
				(u64)dev->async_err_stats
				[OCRDMA_CQ_QPCAT_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_qp_access_err",
				(u64)dev->async_err_stats
				[OCRDMA_QP_ACCESS_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_qp_commm_est_evt",
				(u64)dev->async_err_stats
				[OCRDMA_QP_COMM_EST_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_sq_drained_evt",
				(u64)dev->async_err_stats
				[OCRDMA_SQ_DRAINED_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_dev_fatal_evt",
				(u64)dev->async_err_stats
				[OCRDMA_DEVICE_FATAL_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_srqcat_err",
				(u64)dev->async_err_stats
				[OCRDMA_SRQCAT_ERROR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_srq_limit_evt",
				(u64)dev->async_err_stats
				[OCRDMA_SRQ_LIMIT_EVENT].counter);
	pcur += ocrdma_add_stat(stats, pcur, "async_qp_last_wqe_evt",
				(u64)dev->async_err_stats
				[OCRDMA_QP_LAST_WQE_EVENT].counter);

	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_len_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_LEN_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_qp_op_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_QP_OP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_eec_op_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_EEC_OP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_prot_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_PROT_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_wr_flush_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_WR_FLUSH_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_mw_bind_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_MW_BIND_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_bad_resp_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_BAD_RESP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_access_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_ACCESS_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_inv_req_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_INV_REQ_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_access_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_ACCESS_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_op_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_OP_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_retry_exc_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_RETRY_EXC_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rnr_retry_exc_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_RNR_RETRY_EXC_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_loc_rdd_viol_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_LOC_RDD_VIOL_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_inv_rd_req_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_INV_RD_REQ_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_rem_abort_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_REM_ABORT_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_inv_eecn_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_INV_EECN_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_inv_eec_state_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_INV_EEC_STATE_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_fatal_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_FATAL_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_resp_timeout_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_RESP_TIMEOUT_ERR].counter);
	pcur += ocrdma_add_stat(stats, pcur, "cqe_general_err",
				(u64)dev->cqe_err_stats
				[OCRDMA_CQE_GENERAL_ERR].counter);
	वापस stats;
पूर्ण

अटल व्योम ocrdma_update_stats(काष्ठा ocrdma_dev *dev)
अणु
	uदीर्घ now = jअगरfies, secs;
	पूर्णांक status;
	काष्ठा ocrdma_rdma_stats_resp *rdma_stats =
		      (काष्ठा ocrdma_rdma_stats_resp *)dev->stats_mem.va;
	काष्ठा ocrdma_rsrc_stats *rsrc_stats = &rdma_stats->act_rsrc_stats;

	secs = jअगरfies_to_msecs(now - dev->last_stats_समय) / 1000U;
	अगर (secs) अणु
		/* update */
		status = ocrdma_mbx_rdma_stats(dev, false);
		अगर (status)
			pr_err("%s: stats mbox failed with status = %d\n",
			       __func__, status);
		/* Update PD counters from PD resource manager */
		अगर (dev->pd_mgr->pd_pपुनः_स्मृति_valid) अणु
			rsrc_stats->dpp_pds = dev->pd_mgr->pd_dpp_count;
			rsrc_stats->non_dpp_pds = dev->pd_mgr->pd_norm_count;
			/* Threshold stata*/
			rsrc_stats = &rdma_stats->th_rsrc_stats;
			rsrc_stats->dpp_pds = dev->pd_mgr->pd_dpp_thrsh;
			rsrc_stats->non_dpp_pds = dev->pd_mgr->pd_norm_thrsh;
		पूर्ण
		dev->last_stats_समय = jअगरfies;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ocrdma_dbgfs_ops_ग_लिखो(काष्ठा file *filp,
					स्थिर अक्षर __user *buffer,
					माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर पंचांगp_str[32];
	दीर्घ reset;
	पूर्णांक status;
	काष्ठा ocrdma_stats *pstats = filp->निजी_data;
	काष्ठा ocrdma_dev *dev = pstats->dev;

	अगर (*ppos != 0 || count == 0 || count > माप(पंचांगp_str))
		जाओ err;

	अगर (copy_from_user(पंचांगp_str, buffer, count))
		जाओ err;

	पंचांगp_str[count-1] = '\0';
	अगर (kम_से_दीर्घ(पंचांगp_str, 10, &reset))
		जाओ err;

	चयन (pstats->type) अणु
	हाल OCRDMA_RESET_STATS:
		अगर (reset) अणु
			status = ocrdma_mbx_rdma_stats(dev, true);
			अगर (status) अणु
				pr_err("Failed to reset stats = %d\n", status);
				जाओ err;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		जाओ err;
	पूर्ण

	वापस count;
err:
	वापस -EFAULT;
पूर्ण

व्योम ocrdma_pma_counters(काष्ठा ocrdma_dev *dev, काष्ठा ib_mad *out_mad)
अणु
	काष्ठा ib_pma_portcounters *pma_cnt;

	pma_cnt = (व्योम *)(out_mad->data + 40);
	ocrdma_update_stats(dev);

	pma_cnt->port_xmit_data    = cpu_to_be32(ocrdma_sysfs_xmit_data(dev));
	pma_cnt->port_rcv_data     = cpu_to_be32(ocrdma_sysfs_rcv_data(dev));
	pma_cnt->port_xmit_packets = cpu_to_be32(ocrdma_sysfs_xmit_pkts(dev));
	pma_cnt->port_rcv_packets  = cpu_to_be32(ocrdma_sysfs_rcv_pkts(dev));
पूर्ण

अटल sमाप_प्रकार ocrdma_dbgfs_ops_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
					माप_प्रकार usr_buf_len, loff_t *ppos)
अणु
	काष्ठा ocrdma_stats *pstats = filp->निजी_data;
	काष्ठा ocrdma_dev *dev = pstats->dev;
	sमाप_प्रकार status = 0;
	अक्षर *data = शून्य;

	/* No partial पढ़ोs */
	अगर (*ppos != 0)
		वापस 0;

	mutex_lock(&dev->stats_lock);

	ocrdma_update_stats(dev);

	चयन (pstats->type) अणु
	हाल OCRDMA_RSRC_STATS:
		data = ocrdma_resource_stats(dev);
		अवरोध;
	हाल OCRDMA_RXSTATS:
		data = ocrdma_rx_stats(dev);
		अवरोध;
	हाल OCRDMA_WQESTATS:
		data = ocrdma_wqe_stats(dev);
		अवरोध;
	हाल OCRDMA_TXSTATS:
		data = ocrdma_tx_stats(dev);
		अवरोध;
	हाल OCRDMA_DB_ERRSTATS:
		data = ocrdma_db_errstats(dev);
		अवरोध;
	हाल OCRDMA_RXQP_ERRSTATS:
		data = ocrdma_rxqp_errstats(dev);
		अवरोध;
	हाल OCRDMA_TXQP_ERRSTATS:
		data = ocrdma_txqp_errstats(dev);
		अवरोध;
	हाल OCRDMA_TX_DBG_STATS:
		data = ocrdma_tx_dbg_stats(dev);
		अवरोध;
	हाल OCRDMA_RX_DBG_STATS:
		data = ocrdma_rx_dbg_stats(dev);
		अवरोध;
	हाल OCRDMA_DRV_STATS:
		data = ocrdma_driver_dbg_stats(dev);
		अवरोध;

	शेष:
		status = -EFAULT;
		जाओ निकास;
	पूर्ण

	अगर (usr_buf_len < म_माप(data)) अणु
		status = -ENOSPC;
		जाओ निकास;
	पूर्ण

	status = simple_पढ़ो_from_buffer(buffer, usr_buf_len, ppos, data,
					 म_माप(data));
निकास:
	mutex_unlock(&dev->stats_lock);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा file_operations ocrdma_dbg_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = ocrdma_dbgfs_ops_पढ़ो,
	.ग_लिखो = ocrdma_dbgfs_ops_ग_लिखो,
पूर्ण;

व्योम ocrdma_add_port_stats(काष्ठा ocrdma_dev *dev)
अणु
	स्थिर काष्ठा pci_dev *pdev = dev->nic_info.pdev;

	अगर (!ocrdma_dbgfs_dir)
		वापस;

	/* Create post stats base dir */
	dev->dir = debugfs_create_dir(pci_name(pdev), ocrdma_dbgfs_dir);

	dev->rsrc_stats.type = OCRDMA_RSRC_STATS;
	dev->rsrc_stats.dev = dev;
	debugfs_create_file("resource_stats", S_IRUSR, dev->dir,
			    &dev->rsrc_stats, &ocrdma_dbg_ops);

	dev->rx_stats.type = OCRDMA_RXSTATS;
	dev->rx_stats.dev = dev;
	debugfs_create_file("rx_stats", S_IRUSR, dev->dir, &dev->rx_stats,
			    &ocrdma_dbg_ops);

	dev->wqe_stats.type = OCRDMA_WQESTATS;
	dev->wqe_stats.dev = dev;
	debugfs_create_file("wqe_stats", S_IRUSR, dev->dir, &dev->wqe_stats,
			    &ocrdma_dbg_ops);

	dev->tx_stats.type = OCRDMA_TXSTATS;
	dev->tx_stats.dev = dev;
	debugfs_create_file("tx_stats", S_IRUSR, dev->dir, &dev->tx_stats,
			    &ocrdma_dbg_ops);

	dev->db_err_stats.type = OCRDMA_DB_ERRSTATS;
	dev->db_err_stats.dev = dev;
	debugfs_create_file("db_err_stats", S_IRUSR, dev->dir,
			    &dev->db_err_stats, &ocrdma_dbg_ops);

	dev->tx_qp_err_stats.type = OCRDMA_TXQP_ERRSTATS;
	dev->tx_qp_err_stats.dev = dev;
	debugfs_create_file("tx_qp_err_stats", S_IRUSR, dev->dir,
			    &dev->tx_qp_err_stats, &ocrdma_dbg_ops);

	dev->rx_qp_err_stats.type = OCRDMA_RXQP_ERRSTATS;
	dev->rx_qp_err_stats.dev = dev;
	debugfs_create_file("rx_qp_err_stats", S_IRUSR, dev->dir,
			    &dev->rx_qp_err_stats, &ocrdma_dbg_ops);

	dev->tx_dbg_stats.type = OCRDMA_TX_DBG_STATS;
	dev->tx_dbg_stats.dev = dev;
	debugfs_create_file("tx_dbg_stats", S_IRUSR, dev->dir,
			    &dev->tx_dbg_stats, &ocrdma_dbg_ops);

	dev->rx_dbg_stats.type = OCRDMA_RX_DBG_STATS;
	dev->rx_dbg_stats.dev = dev;
	debugfs_create_file("rx_dbg_stats", S_IRUSR, dev->dir,
			    &dev->rx_dbg_stats, &ocrdma_dbg_ops);

	dev->driver_stats.type = OCRDMA_DRV_STATS;
	dev->driver_stats.dev = dev;
	debugfs_create_file("driver_dbg_stats", S_IRUSR, dev->dir,
			    &dev->driver_stats, &ocrdma_dbg_ops);

	dev->reset_stats.type = OCRDMA_RESET_STATS;
	dev->reset_stats.dev = dev;
	debugfs_create_file("reset_stats", 0200, dev->dir, &dev->reset_stats,
			    &ocrdma_dbg_ops);
पूर्ण

व्योम ocrdma_rem_port_stats(काष्ठा ocrdma_dev *dev)
अणु
	debugfs_हटाओ_recursive(dev->dir);
पूर्ण

व्योम ocrdma_init_debugfs(व्योम)
अणु
	/* Create base dir in debugfs root dir */
	ocrdma_dbgfs_dir = debugfs_create_dir("ocrdma", शून्य);
पूर्ण

व्योम ocrdma_rem_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(ocrdma_dbgfs_dir);
पूर्ण
