<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 */

#अगर_अघोषित __CUDBG_LIB_H__
#घोषणा __CUDBG_LIB_H__

पूर्णांक cudbg_collect_reg_dump(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_fw_devlog(काष्ठा cudbg_init *pdbg_init,
			    काष्ठा cudbg_buffer *dbg_buff,
			    काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_la(काष्ठा cudbg_init *pdbg_init,
			 काष्ठा cudbg_buffer *dbg_buff,
			 काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_ma_la(काष्ठा cudbg_init *pdbg_init,
			    काष्ठा cudbg_buffer *dbg_buff,
			    काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_qcfg(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_ibq_tp0(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_ibq_tp1(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_ibq_ulp(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_ibq_sge0(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_ibq_sge1(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_ibq_ncsi(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_obq_ulp0(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_obq_ulp1(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_obq_ulp2(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_obq_ulp3(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_obq_sge(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_obq_ncsi(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_edc0_meminfo(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_edc1_meminfo(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_mc0_meminfo(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_mc1_meminfo(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_rss(काष्ठा cudbg_init *pdbg_init,
		      काष्ठा cudbg_buffer *dbg_buff,
		      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_rss_vf_config(काष्ठा cudbg_init *pdbg_init,
				काष्ठा cudbg_buffer *dbg_buff,
				काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_tp_indirect(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_path_mtu(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_pm_stats(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_hw_sched(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_sge_indirect(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_ulprx_la(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_tp_la(काष्ठा cudbg_init *pdbg_init,
			काष्ठा cudbg_buffer *dbg_buff,
			काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_meminfo(काष्ठा cudbg_init *pdbg_init,
			  काष्ठा cudbg_buffer *dbg_buff,
			  काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cim_pअगर_la(काष्ठा cudbg_init *pdbg_init,
			     काष्ठा cudbg_buffer *dbg_buff,
			     काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_clk_info(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_obq_sge_rx_q0(काष्ठा cudbg_init *pdbg_init,
				काष्ठा cudbg_buffer *dbg_buff,
				काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_obq_sge_rx_q1(काष्ठा cudbg_init *pdbg_init,
				काष्ठा cudbg_buffer *dbg_buff,
				काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_pcie_indirect(काष्ठा cudbg_init *pdbg_init,
				काष्ठा cudbg_buffer *dbg_buff,
				काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_pm_indirect(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_tid(काष्ठा cudbg_init *pdbg_init,
		      काष्ठा cudbg_buffer *dbg_buff,
		      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_pcie_config(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_dump_context(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_mps_tcam(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_vpd_data(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_le_tcam(काष्ठा cudbg_init *pdbg_init,
			  काष्ठा cudbg_buffer *dbg_buff,
			  काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_cctrl(काष्ठा cudbg_init *pdbg_init,
			काष्ठा cudbg_buffer *dbg_buff,
			काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_ma_indirect(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_ulptx_la(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_up_cim_indirect(काष्ठा cudbg_init *pdbg_init,
				  काष्ठा cudbg_buffer *dbg_buff,
				  काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_pbt_tables(काष्ठा cudbg_init *pdbg_init,
			     काष्ठा cudbg_buffer *dbg_buff,
			     काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_mbox_log(काष्ठा cudbg_init *pdbg_init,
			   काष्ठा cudbg_buffer *dbg_buff,
			   काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_hma_indirect(काष्ठा cudbg_init *pdbg_init,
			       काष्ठा cudbg_buffer *dbg_buff,
			       काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_hma_meminfo(काष्ठा cudbg_init *pdbg_init,
			      काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_qdesc(काष्ठा cudbg_init *pdbg_init,
			काष्ठा cudbg_buffer *dbg_buff,
			काष्ठा cudbg_error *cudbg_err);
पूर्णांक cudbg_collect_flash(काष्ठा cudbg_init *pdbg_init,
			काष्ठा cudbg_buffer *dbg_buff,
			काष्ठा cudbg_error *cudbg_err);

u32 cudbg_get_entity_length(काष्ठा adapter *adap, u32 entity);
काष्ठा cudbg_entity_hdr *cudbg_get_entity_hdr(व्योम *outbuf, पूर्णांक i);
व्योम cudbg_align_debug_buffer(काष्ठा cudbg_buffer *dbg_buff,
			      काष्ठा cudbg_entity_hdr *entity_hdr);
u32 cudbg_cim_obq_size(काष्ठा adapter *padap, पूर्णांक qid);
पूर्णांक cudbg_dump_context_size(काष्ठा adapter *padap);

पूर्णांक cudbg_fill_meminfo(काष्ठा adapter *padap,
		       काष्ठा cudbg_meminfo *meminfo_buff);
व्योम cudbg_fill_le_tcam_info(काष्ठा adapter *padap,
			     काष्ठा cudbg_tcam *tcam_region);
व्योम cudbg_fill_qdesc_num_and_size(स्थिर काष्ठा adapter *padap,
				   u32 *num, u32 *size);

अटल अंतरभूत u32 cudbg_uld_txq_to_qtype(u32 uld)
अणु
	चयन (uld) अणु
	हाल CXGB4_TX_OFLD:
		वापस CUDBG_QTYPE_OFLD_TXQ;
	हाल CXGB4_TX_CRYPTO:
		वापस CUDBG_QTYPE_CRYPTO_TXQ;
	पूर्ण

	वापस CUDBG_QTYPE_UNKNOWN;
पूर्ण

अटल अंतरभूत u32 cudbg_uld_rxq_to_qtype(u32 uld)
अणु
	चयन (uld) अणु
	हाल CXGB4_ULD_RDMA:
		वापस CUDBG_QTYPE_RDMA_RXQ;
	हाल CXGB4_ULD_ISCSI:
		वापस CUDBG_QTYPE_ISCSI_RXQ;
	हाल CXGB4_ULD_ISCSIT:
		वापस CUDBG_QTYPE_ISCSIT_RXQ;
	हाल CXGB4_ULD_CRYPTO:
		वापस CUDBG_QTYPE_CRYPTO_RXQ;
	हाल CXGB4_ULD_TLS:
		वापस CUDBG_QTYPE_TLS_RXQ;
	पूर्ण

	वापस CUDBG_QTYPE_UNKNOWN;
पूर्ण

अटल अंतरभूत u32 cudbg_uld_flq_to_qtype(u32 uld)
अणु
	चयन (uld) अणु
	हाल CXGB4_ULD_RDMA:
		वापस CUDBG_QTYPE_RDMA_FLQ;
	हाल CXGB4_ULD_ISCSI:
		वापस CUDBG_QTYPE_ISCSI_FLQ;
	हाल CXGB4_ULD_ISCSIT:
		वापस CUDBG_QTYPE_ISCSIT_FLQ;
	हाल CXGB4_ULD_CRYPTO:
		वापस CUDBG_QTYPE_CRYPTO_FLQ;
	हाल CXGB4_ULD_TLS:
		वापस CUDBG_QTYPE_TLS_FLQ;
	पूर्ण

	वापस CUDBG_QTYPE_UNKNOWN;
पूर्ण

अटल अंतरभूत u32 cudbg_uld_ciq_to_qtype(u32 uld)
अणु
	चयन (uld) अणु
	हाल CXGB4_ULD_RDMA:
		वापस CUDBG_QTYPE_RDMA_CIQ;
	पूर्ण

	वापस CUDBG_QTYPE_UNKNOWN;
पूर्ण

अटल अंतरभूत व्योम cudbg_fill_qdesc_txq(स्थिर काष्ठा sge_txq *txq,
					क्रमागत cudbg_qdesc_qtype type,
					काष्ठा cudbg_qdesc_entry *entry)
अणु
	entry->qtype = type;
	entry->qid = txq->cntxt_id;
	entry->desc_size = माप(काष्ठा tx_desc);
	entry->num_desc = txq->size;
	entry->data_size = txq->size * माप(काष्ठा tx_desc);
	स_नकल(entry->data, txq->desc, entry->data_size);
पूर्ण

अटल अंतरभूत व्योम cudbg_fill_qdesc_rxq(स्थिर काष्ठा sge_rspq *rxq,
					क्रमागत cudbg_qdesc_qtype type,
					काष्ठा cudbg_qdesc_entry *entry)
अणु
	entry->qtype = type;
	entry->qid = rxq->cntxt_id;
	entry->desc_size = rxq->iqe_len;
	entry->num_desc = rxq->size;
	entry->data_size = rxq->size * rxq->iqe_len;
	स_नकल(entry->data, rxq->desc, entry->data_size);
पूर्ण

अटल अंतरभूत व्योम cudbg_fill_qdesc_flq(स्थिर काष्ठा sge_fl *flq,
					क्रमागत cudbg_qdesc_qtype type,
					काष्ठा cudbg_qdesc_entry *entry)
अणु
	entry->qtype = type;
	entry->qid = flq->cntxt_id;
	entry->desc_size = माप(__be64);
	entry->num_desc = flq->size;
	entry->data_size = flq->size * माप(__be64);
	स_नकल(entry->data, flq->desc, entry->data_size);
पूर्ण

अटल अंतरभूत
काष्ठा cudbg_qdesc_entry *cudbg_next_qdesc(काष्ठा cudbg_qdesc_entry *e)
अणु
	वापस (काष्ठा cudbg_qdesc_entry *)
	       ((u8 *)e + माप(*e) + e->data_size);
पूर्ण
#पूर्ण_अगर /* __CUDBG_LIB_H__ */
