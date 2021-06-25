<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2020-2021 Intel Corporation
 */
#अगर_अघोषित __iwl_trans_queue_tx_h__
#घोषणा __iwl_trans_queue_tx_h__
#समावेश "iwl-fh.h"
#समावेश "fw/api/tx.h"

काष्ठा iwl_tso_hdr_page अणु
	काष्ठा page *page;
	u8 *pos;
पूर्ण;

अटल अंतरभूत dma_addr_t
iwl_txq_get_first_tb_dma(काष्ठा iwl_txq *txq, पूर्णांक idx)
अणु
	वापस txq->first_tb_dma +
	       माप(काष्ठा iwl_pcie_first_tb_buf) * idx;
पूर्ण

अटल अंतरभूत u16 iwl_txq_get_cmd_index(स्थिर काष्ठा iwl_txq *q, u32 index)
अणु
	वापस index & (q->n_winकरोw - 1);
पूर्ण

व्योम iwl_txq_gen2_unmap(काष्ठा iwl_trans *trans, पूर्णांक txq_id);

अटल अंतरभूत व्योम iwl_wake_queue(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_txq *txq)
अणु
	अगर (test_and_clear_bit(txq->id, trans->txqs.queue_stopped)) अणु
		IWL_DEBUG_TX_QUEUES(trans, "Wake hwq %d\n", txq->id);
		iwl_op_mode_queue_not_full(trans->op_mode, txq->id);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *iwl_txq_get_tfd(काष्ठा iwl_trans *trans,
				    काष्ठा iwl_txq *txq, पूर्णांक idx)
अणु
	अगर (trans->trans_cfg->use_tfh)
		idx = iwl_txq_get_cmd_index(txq, idx);

	वापस txq->tfds + trans->txqs.tfd.size * idx;
पूर्ण

पूर्णांक iwl_txq_alloc(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq, पूर्णांक slots_num,
		  bool cmd_queue);
/*
 * We need this अंतरभूत in हाल dma_addr_t is only 32-bits - since the
 * hardware is always 64-bit, the issue can still occur in that हाल,
 * so use u64 क्रम 'phys' here to क्रमce the addition in 64-bit.
 */
अटल अंतरभूत bool iwl_txq_crosses_4g_boundary(u64 phys, u16 len)
अणु
	वापस upper_32_bits(phys) != upper_32_bits(phys + len);
पूर्ण

पूर्णांक iwl_txq_space(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_txq *q);

अटल अंतरभूत व्योम iwl_txq_stop(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq)
अणु
	अगर (!test_and_set_bit(txq->id, trans->txqs.queue_stopped)) अणु
		iwl_op_mode_queue_full(trans->op_mode, txq->id);
		IWL_DEBUG_TX_QUEUES(trans, "Stop hwq %d\n", txq->id);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_TX_QUEUES(trans, "hwq %d already stopped\n",
				    txq->id);
	पूर्ण
पूर्ण

/**
 * iwl_txq_inc_wrap - increment queue index, wrap back to beginning
 * @index -- current index
 */
अटल अंतरभूत पूर्णांक iwl_txq_inc_wrap(काष्ठा iwl_trans *trans, पूर्णांक index)
अणु
	वापस ++index &
		(trans->trans_cfg->base_params->max_tfd_queue_size - 1);
पूर्ण

/**
 * iwl_txq_dec_wrap - decrement queue index, wrap back to end
 * @index -- current index
 */
अटल अंतरभूत पूर्णांक iwl_txq_dec_wrap(काष्ठा iwl_trans *trans, पूर्णांक index)
अणु
	वापस --index &
		(trans->trans_cfg->base_params->max_tfd_queue_size - 1);
पूर्ण

अटल अंतरभूत bool iwl_txq_used(स्थिर काष्ठा iwl_txq *q, पूर्णांक i)
अणु
	पूर्णांक index = iwl_txq_get_cmd_index(q, i);
	पूर्णांक r = iwl_txq_get_cmd_index(q, q->पढ़ो_ptr);
	पूर्णांक w = iwl_txq_get_cmd_index(q, q->ग_लिखो_ptr);

	वापस w >= r ?
		(index >= r && index < w) :
		!(index < r && index >= w);
पूर्ण

व्योम iwl_txq_मुक्त_tso_page(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb);

व्योम iwl_txq_log_scd_error(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq);

पूर्णांक iwl_txq_gen2_set_tb(काष्ठा iwl_trans *trans,
			काष्ठा iwl_tfh_tfd *tfd, dma_addr_t addr,
			u16 len);

व्योम iwl_txq_gen2_tfd_unmap(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_cmd_meta *meta,
			    काष्ठा iwl_tfh_tfd *tfd);

पूर्णांक iwl_txq_dyn_alloc(काष्ठा iwl_trans *trans,
		      __le16 flags, u8 sta_id, u8 tid,
		      पूर्णांक cmd_id, पूर्णांक size,
		      अचिन्हित पूर्णांक समयout);

पूर्णांक iwl_txq_gen2_tx(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
		    काष्ठा iwl_device_tx_cmd *dev_cmd, पूर्णांक txq_id);

व्योम iwl_txq_dyn_मुक्त(काष्ठा iwl_trans *trans, पूर्णांक queue);
व्योम iwl_txq_gen2_मुक्त_tfd(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq);
व्योम iwl_txq_inc_wr_ptr(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq);
व्योम iwl_txq_gen2_tx_मुक्त(काष्ठा iwl_trans *trans);
पूर्णांक iwl_txq_init(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq, पूर्णांक slots_num,
		 bool cmd_queue);
पूर्णांक iwl_txq_gen2_init(काष्ठा iwl_trans *trans, पूर्णांक txq_id, पूर्णांक queue_size);
#अगर_घोषित CONFIG_INET
काष्ठा iwl_tso_hdr_page *get_page_hdr(काष्ठा iwl_trans *trans, माप_प्रकार len,
				      काष्ठा sk_buff *skb);
#पूर्ण_अगर
अटल अंतरभूत u8 iwl_txq_gen1_tfd_get_num_tbs(काष्ठा iwl_trans *trans,
					      व्योम *_tfd)
अणु
	काष्ठा iwl_tfd *tfd;

	अगर (trans->trans_cfg->use_tfh) अणु
		काष्ठा iwl_tfh_tfd *tfd = _tfd;

		वापस le16_to_cpu(tfd->num_tbs) & 0x1f;
	पूर्ण

	tfd = (काष्ठा iwl_tfd *)_tfd;
	वापस tfd->num_tbs & 0x1f;
पूर्ण

अटल अंतरभूत u16 iwl_txq_gen1_tfd_tb_get_len(काष्ठा iwl_trans *trans,
					      व्योम *_tfd, u8 idx)
अणु
	काष्ठा iwl_tfd *tfd;
	काष्ठा iwl_tfd_tb *tb;

	अगर (trans->trans_cfg->use_tfh) अणु
		काष्ठा iwl_tfh_tfd *tfd = _tfd;
		काष्ठा iwl_tfh_tb *tb = &tfd->tbs[idx];

		वापस le16_to_cpu(tb->tb_len);
	पूर्ण

	tfd = (काष्ठा iwl_tfd *)_tfd;
	tb = &tfd->tbs[idx];

	वापस le16_to_cpu(tb->hi_n_len) >> 4;
पूर्ण

व्योम iwl_txq_gen1_tfd_unmap(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_cmd_meta *meta,
			    काष्ठा iwl_txq *txq, पूर्णांक index);
व्योम iwl_txq_gen1_inval_byte_cnt_tbl(काष्ठा iwl_trans *trans,
				     काष्ठा iwl_txq *txq);
व्योम iwl_txq_gen1_update_byte_cnt_tbl(काष्ठा iwl_trans *trans,
				      काष्ठा iwl_txq *txq, u16 byte_cnt,
				      पूर्णांक num_tbs);
व्योम iwl_txq_reclaim(काष्ठा iwl_trans *trans, पूर्णांक txq_id, पूर्णांक ssn,
		     काष्ठा sk_buff_head *skbs);
व्योम iwl_txq_set_q_ptrs(काष्ठा iwl_trans *trans, पूर्णांक txq_id, पूर्णांक ptr);
व्योम iwl_trans_txq_मुक्तze_समयr(काष्ठा iwl_trans *trans, अचिन्हित दीर्घ txqs,
				bool मुक्तze);
व्योम iwl_txq_progress(काष्ठा iwl_txq *txq);
व्योम iwl_txq_मुक्त_tfd(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq);
पूर्णांक iwl_trans_txq_send_hcmd(काष्ठा iwl_trans *trans, काष्ठा iwl_host_cmd *cmd);
#पूर्ण_अगर /* __iwl_trans_queue_tx_h__ */
