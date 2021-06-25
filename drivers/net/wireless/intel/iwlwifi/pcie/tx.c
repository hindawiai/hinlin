<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2003-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/tso.h>

#समावेश "iwl-debug.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-io.h"
#समावेश "iwl-scd.h"
#समावेश "iwl-op-mode.h"
#समावेश "internal.h"
#समावेश "fw/api/tx.h"

/*************** DMA-QUEUE-GENERAL-FUNCTIONS  *****
 * DMA services
 *
 * Theory of operation
 *
 * A Tx or Rx queue resides in host DRAM, and is comprised of a circular buffer
 * of buffer descriptors, each of which poपूर्णांकs to one or more data buffers क्रम
 * the device to पढ़ो from or fill.  Driver and device exchange status of each
 * queue via "read" and "write" poपूर्णांकers.  Driver keeps minimum of 2 empty
 * entries in each circular buffer, to protect against confusing empty and full
 * queue states.
 *
 * The device पढ़ोs or ग_लिखोs the data in the queues via the device's several
 * DMA/FIFO channels.  Each queue is mapped to a single DMA channel.
 *
 * For Tx queue, there are low mark and high mark limits. If, after queuing
 * the packet क्रम Tx, मुक्त space become < low mark, Tx queue stopped. When
 * reclaiming packets (on 'tx करोne IRQ), अगर मुक्त space become > high mark,
 * Tx queue resumed.
 *
 ***************************************************/


पूर्णांक iwl_pcie_alloc_dma_ptr(काष्ठा iwl_trans *trans,
			   काष्ठा iwl_dma_ptr *ptr, माप_प्रकार size)
अणु
	अगर (WARN_ON(ptr->addr))
		वापस -EINVAL;

	ptr->addr = dma_alloc_coherent(trans->dev, size,
				       &ptr->dma, GFP_KERNEL);
	अगर (!ptr->addr)
		वापस -ENOMEM;
	ptr->size = size;
	वापस 0;
पूर्ण

व्योम iwl_pcie_मुक्त_dma_ptr(काष्ठा iwl_trans *trans, काष्ठा iwl_dma_ptr *ptr)
अणु
	अगर (unlikely(!ptr->addr))
		वापस;

	dma_मुक्त_coherent(trans->dev, ptr->size, ptr->addr, ptr->dma);
	स_रखो(ptr, 0, माप(*ptr));
पूर्ण

/*
 * iwl_pcie_txq_inc_wr_ptr - Send new ग_लिखो index to hardware
 */
अटल व्योम iwl_pcie_txq_inc_wr_ptr(काष्ठा iwl_trans *trans,
				    काष्ठा iwl_txq *txq)
अणु
	u32 reg = 0;
	पूर्णांक txq_id = txq->id;

	lockdep_निश्चित_held(&txq->lock);

	/*
	 * explicitly wake up the NIC अगर:
	 * 1. shaकरोw रेजिस्टरs aren't enabled
	 * 2. NIC is woken up क्रम CMD regardless of shaकरोw outside this function
	 * 3. there is a chance that the NIC is asleep
	 */
	अगर (!trans->trans_cfg->base_params->shaकरोw_reg_enable &&
	    txq_id != trans->txqs.cmd.q_id &&
	    test_bit(STATUS_TPOWER_PMI, &trans->status)) अणु
		/*
		 * wake up nic अगर it's घातered करोwn ...
		 * uCode will wake up, and पूर्णांकerrupt us again, so next
		 * समय we'll skip this part.
		 */
		reg = iwl_पढ़ो32(trans, CSR_UCODE_DRV_GP1);

		अगर (reg & CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP) अणु
			IWL_DEBUG_INFO(trans, "Tx queue %d requesting wakeup, GP1 = 0x%x\n",
				       txq_id, reg);
			iwl_set_bit(trans, CSR_GP_CNTRL,
				    CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
			txq->need_update = true;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * अगर not in घातer-save mode, uCode will never sleep when we're
	 * trying to tx (during RFKILL, we're not trying to tx).
	 */
	IWL_DEBUG_TX(trans, "Q:%d WR: 0x%x\n", txq_id, txq->ग_लिखो_ptr);
	अगर (!txq->block)
		iwl_ग_लिखो32(trans, HBUS_TARG_WRPTR,
			    txq->ग_लिखो_ptr | (txq_id << 8));
पूर्ण

व्योम iwl_pcie_txq_check_wrptrs(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < trans->trans_cfg->base_params->num_of_queues; i++) अणु
		काष्ठा iwl_txq *txq = trans->txqs.txq[i];

		अगर (!test_bit(i, trans->txqs.queue_used))
			जारी;

		spin_lock_bh(&txq->lock);
		अगर (txq->need_update) अणु
			iwl_pcie_txq_inc_wr_ptr(trans, txq);
			txq->need_update = false;
		पूर्ण
		spin_unlock_bh(&txq->lock);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम iwl_pcie_tfd_set_tb(काष्ठा iwl_trans *trans, व्योम *tfd,
				       u8 idx, dma_addr_t addr, u16 len)
अणु
	काष्ठा iwl_tfd *tfd_fh = (व्योम *)tfd;
	काष्ठा iwl_tfd_tb *tb = &tfd_fh->tbs[idx];

	u16 hi_n_len = len << 4;

	put_unaligned_le32(addr, &tb->lo);
	hi_n_len |= iwl_get_dma_hi_addr(addr);

	tb->hi_n_len = cpu_to_le16(hi_n_len);

	tfd_fh->num_tbs = idx + 1;
पूर्ण

अटल पूर्णांक iwl_pcie_txq_build_tfd(काष्ठा iwl_trans *trans, काष्ठा iwl_txq *txq,
				  dma_addr_t addr, u16 len, bool reset)
अणु
	व्योम *tfd;
	u32 num_tbs;

	tfd = txq->tfds + trans->txqs.tfd.size * txq->ग_लिखो_ptr;

	अगर (reset)
		स_रखो(tfd, 0, trans->txqs.tfd.size);

	num_tbs = iwl_txq_gen1_tfd_get_num_tbs(trans, tfd);

	/* Each TFD can poपूर्णांक to a maximum max_tbs Tx buffers */
	अगर (num_tbs >= trans->txqs.tfd.max_tbs) अणु
		IWL_ERR(trans, "Error can not send more than %d chunks\n",
			trans->txqs.tfd.max_tbs);
		वापस -EINVAL;
	पूर्ण

	अगर (WARN(addr & ~IWL_TX_DMA_MASK,
		 "Unaligned address = %llx\n", (अचिन्हित दीर्घ दीर्घ)addr))
		वापस -EINVAL;

	iwl_pcie_tfd_set_tb(trans, tfd, num_tbs, addr, len);

	वापस num_tbs;
पूर्ण

अटल व्योम iwl_pcie_clear_cmd_in_flight(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (!trans->trans_cfg->base_params->apmg_wake_up_wa)
		वापस;

	spin_lock(&trans_pcie->reg_lock);

	अगर (WARN_ON(!trans_pcie->cmd_hold_nic_awake)) अणु
		spin_unlock(&trans_pcie->reg_lock);
		वापस;
	पूर्ण

	trans_pcie->cmd_hold_nic_awake = false;
	__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	spin_unlock(&trans_pcie->reg_lock);
पूर्ण

/*
 * iwl_pcie_txq_unmap -  Unmap any reमुख्यing DMA mappings and मुक्त skb's
 */
अटल व्योम iwl_pcie_txq_unmap(काष्ठा iwl_trans *trans, पूर्णांक txq_id)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];

	अगर (!txq) अणु
		IWL_ERR(trans, "Trying to free a queue that wasn't allocated?\n");
		वापस;
	पूर्ण

	spin_lock_bh(&txq->lock);
	जबतक (txq->ग_लिखो_ptr != txq->पढ़ो_ptr) अणु
		IWL_DEBUG_TX_REPLY(trans, "Q %d Free %d\n",
				   txq_id, txq->पढ़ो_ptr);

		अगर (txq_id != trans->txqs.cmd.q_id) अणु
			काष्ठा sk_buff *skb = txq->entries[txq->पढ़ो_ptr].skb;

			अगर (WARN_ON_ONCE(!skb))
				जारी;

			iwl_txq_मुक्त_tso_page(trans, skb);
		पूर्ण
		iwl_txq_मुक्त_tfd(trans, txq);
		txq->पढ़ो_ptr = iwl_txq_inc_wrap(trans, txq->पढ़ो_ptr);

		अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr &&
		    txq_id == trans->txqs.cmd.q_id)
			iwl_pcie_clear_cmd_in_flight(trans);
	पूर्ण

	जबतक (!skb_queue_empty(&txq->overflow_q)) अणु
		काष्ठा sk_buff *skb = __skb_dequeue(&txq->overflow_q);

		iwl_op_mode_मुक्त_skb(trans->op_mode, skb);
	पूर्ण

	spin_unlock_bh(&txq->lock);

	/* just in हाल - this queue may have been stopped */
	iwl_wake_queue(trans, txq);
पूर्ण

/*
 * iwl_pcie_txq_मुक्त - Deallocate DMA queue.
 * @txq: Transmit queue to deallocate.
 *
 * Empty queue by removing and destroying all BD's.
 * Free all buffers.
 * 0-fill, but करो not मुक्त "txq" descriptor काष्ठाure.
 */
अटल व्योम iwl_pcie_txq_मुक्त(काष्ठा iwl_trans *trans, पूर्णांक txq_id)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];
	काष्ठा device *dev = trans->dev;
	पूर्णांक i;

	अगर (WARN_ON(!txq))
		वापस;

	iwl_pcie_txq_unmap(trans, txq_id);

	/* De-alloc array of command/tx buffers */
	अगर (txq_id == trans->txqs.cmd.q_id)
		क्रम (i = 0; i < txq->n_winकरोw; i++) अणु
			kमुक्त_sensitive(txq->entries[i].cmd);
			kमुक्त_sensitive(txq->entries[i].मुक्त_buf);
		पूर्ण

	/* De-alloc circular buffer of TFDs */
	अगर (txq->tfds) अणु
		dma_मुक्त_coherent(dev,
				  trans->txqs.tfd.size *
				  trans->trans_cfg->base_params->max_tfd_queue_size,
				  txq->tfds, txq->dma_addr);
		txq->dma_addr = 0;
		txq->tfds = शून्य;

		dma_मुक्त_coherent(dev,
				  माप(*txq->first_tb_bufs) * txq->n_winकरोw,
				  txq->first_tb_bufs, txq->first_tb_dma);
	पूर्ण

	kमुक्त(txq->entries);
	txq->entries = शून्य;

	del_समयr_sync(&txq->stuck_समयr);

	/* 0-fill queue descriptor काष्ठाure */
	स_रखो(txq, 0, माप(*txq));
पूर्ण

व्योम iwl_pcie_tx_start(काष्ठा iwl_trans *trans, u32 scd_base_addr)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक nq = trans->trans_cfg->base_params->num_of_queues;
	पूर्णांक chan;
	u32 reg_val;
	पूर्णांक clear_dwords = (SCD_TRANS_TBL_OFFSET_QUEUE(nq) -
				SCD_CONTEXT_MEM_LOWER_BOUND) / माप(u32);

	/* make sure all queue are not stopped/used */
	स_रखो(trans->txqs.queue_stopped, 0,
	       माप(trans->txqs.queue_stopped));
	स_रखो(trans->txqs.queue_used, 0, माप(trans->txqs.queue_used));

	trans_pcie->scd_base_addr =
		iwl_पढ़ो_prph(trans, SCD_SRAM_BASE_ADDR);

	WARN_ON(scd_base_addr != 0 &&
		scd_base_addr != trans_pcie->scd_base_addr);

	/* reset context data, TX status and translation data */
	iwl_trans_ग_लिखो_mem(trans, trans_pcie->scd_base_addr +
				   SCD_CONTEXT_MEM_LOWER_BOUND,
			    शून्य, clear_dwords);

	iwl_ग_लिखो_prph(trans, SCD_DRAM_BASE_ADDR,
		       trans->txqs.scd_bc_tbls.dma >> 10);

	/* The chain extension of the SCD करोesn't work well. This feature is
	 * enabled by शेष by the HW, so we need to disable it manually.
	 */
	अगर (trans->trans_cfg->base_params->scd_chain_ext_wa)
		iwl_ग_लिखो_prph(trans, SCD_CHAINEXT_EN, 0);

	iwl_trans_ac_txq_enable(trans, trans->txqs.cmd.q_id,
				trans->txqs.cmd.fअगरo,
				trans->txqs.cmd.wdg_समयout);

	/* Activate all Tx DMA/FIFO channels */
	iwl_scd_activate_fअगरos(trans);

	/* Enable DMA channel */
	क्रम (chan = 0; chan < FH_TCSR_CHNL_NUM; chan++)
		iwl_ग_लिखो_direct32(trans, FH_TCSR_CHNL_TX_CONFIG_REG(chan),
				   FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE |
				   FH_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE);

	/* Update FH chicken bits */
	reg_val = iwl_पढ़ो_direct32(trans, FH_TX_CHICKEN_BITS_REG);
	iwl_ग_लिखो_direct32(trans, FH_TX_CHICKEN_BITS_REG,
			   reg_val | FH_TX_CHICKEN_BITS_SCD_AUTO_RETRY_EN);

	/* Enable L1-Active */
	अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_8000)
		iwl_clear_bits_prph(trans, APMG_PCIDEV_STT_REG,
				    APMG_PCIDEV_STT_VAL_L1_ACT_DIS);
पूर्ण

व्योम iwl_trans_pcie_tx_reset(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक txq_id;

	/*
	 * we should never get here in gen2 trans mode वापस early to aव्योम
	 * having invalid accesses
	 */
	अगर (WARN_ON_ONCE(trans->trans_cfg->gen2))
		वापस;

	क्रम (txq_id = 0; txq_id < trans->trans_cfg->base_params->num_of_queues;
	     txq_id++) अणु
		काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];
		अगर (trans->trans_cfg->use_tfh)
			iwl_ग_लिखो_direct64(trans,
					   FH_MEM_CBBC_QUEUE(trans, txq_id),
					   txq->dma_addr);
		अन्यथा
			iwl_ग_लिखो_direct32(trans,
					   FH_MEM_CBBC_QUEUE(trans, txq_id),
					   txq->dma_addr >> 8);
		iwl_pcie_txq_unmap(trans, txq_id);
		txq->पढ़ो_ptr = 0;
		txq->ग_लिखो_ptr = 0;
	पूर्ण

	/* Tell NIC where to find the "keep warm" buffer */
	iwl_ग_लिखो_direct32(trans, FH_KW_MEM_ADDR_REG,
			   trans_pcie->kw.dma >> 4);

	/*
	 * Send 0 as the scd_base_addr since the device may have be reset
	 * जबतक we were in WoWLAN in which हाल SCD_SRAM_BASE_ADDR will
	 * contain garbage.
	 */
	iwl_pcie_tx_start(trans, 0);
पूर्ण

अटल व्योम iwl_pcie_tx_stop_fh(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक ch, ret;
	u32 mask = 0;

	spin_lock_bh(&trans_pcie->irq_lock);

	अगर (!iwl_trans_grab_nic_access(trans))
		जाओ out;

	/* Stop each Tx DMA channel */
	क्रम (ch = 0; ch < FH_TCSR_CHNL_NUM; ch++) अणु
		iwl_ग_लिखो32(trans, FH_TCSR_CHNL_TX_CONFIG_REG(ch), 0x0);
		mask |= FH_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(ch);
	पूर्ण

	/* Wait क्रम DMA channels to be idle */
	ret = iwl_poll_bit(trans, FH_TSSR_TX_STATUS_REG, mask, mask, 5000);
	अगर (ret < 0)
		IWL_ERR(trans,
			"Failing on timeout while stopping DMA channel %d [0x%08x]\n",
			ch, iwl_पढ़ो32(trans, FH_TSSR_TX_STATUS_REG));

	iwl_trans_release_nic_access(trans);

out:
	spin_unlock_bh(&trans_pcie->irq_lock);
पूर्ण

/*
 * iwl_pcie_tx_stop - Stop all Tx DMA channels
 */
पूर्णांक iwl_pcie_tx_stop(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक txq_id;

	/* Turn off all Tx DMA fअगरos */
	iwl_scd_deactivate_fअगरos(trans);

	/* Turn off all Tx DMA channels */
	iwl_pcie_tx_stop_fh(trans);

	/*
	 * This function can be called beक्रमe the op_mode disabled the
	 * queues. This happens when we have an rfसमाप्त पूर्णांकerrupt.
	 * Since we stop Tx altogether - mark the queues as stopped.
	 */
	स_रखो(trans->txqs.queue_stopped, 0,
	       माप(trans->txqs.queue_stopped));
	स_रखो(trans->txqs.queue_used, 0, माप(trans->txqs.queue_used));

	/* This can happen: start_hw, stop_device */
	अगर (!trans_pcie->txq_memory)
		वापस 0;

	/* Unmap DMA from host प्रणाली and मुक्त skb's */
	क्रम (txq_id = 0; txq_id < trans->trans_cfg->base_params->num_of_queues;
	     txq_id++)
		iwl_pcie_txq_unmap(trans, txq_id);

	वापस 0;
पूर्ण

/*
 * iwl_trans_tx_मुक्त - Free TXQ Context
 *
 * Destroy all TX DMA queues and काष्ठाures
 */
व्योम iwl_pcie_tx_मुक्त(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक txq_id;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	स_रखो(trans->txqs.queue_used, 0, माप(trans->txqs.queue_used));

	/* Tx queues */
	अगर (trans_pcie->txq_memory) अणु
		क्रम (txq_id = 0;
		     txq_id < trans->trans_cfg->base_params->num_of_queues;
		     txq_id++) अणु
			iwl_pcie_txq_मुक्त(trans, txq_id);
			trans->txqs.txq[txq_id] = शून्य;
		पूर्ण
	पूर्ण

	kमुक्त(trans_pcie->txq_memory);
	trans_pcie->txq_memory = शून्य;

	iwl_pcie_मुक्त_dma_ptr(trans, &trans_pcie->kw);

	iwl_pcie_मुक्त_dma_ptr(trans, &trans->txqs.scd_bc_tbls);
पूर्ण

/*
 * iwl_pcie_tx_alloc - allocate TX context
 * Allocate all Tx DMA काष्ठाures and initialize them
 */
अटल पूर्णांक iwl_pcie_tx_alloc(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक ret;
	पूर्णांक txq_id, slots_num;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u16 bc_tbls_size = trans->trans_cfg->base_params->num_of_queues;

	अगर (WARN_ON(trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210))
		वापस -EINVAL;

	bc_tbls_size *= माप(काष्ठा iwlagn_scd_bc_tbl);

	/*It is not allowed to alloc twice, so warn when this happens.
	 * We cannot rely on the previous allocation, so मुक्त and fail */
	अगर (WARN_ON(trans_pcie->txq_memory)) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = iwl_pcie_alloc_dma_ptr(trans, &trans->txqs.scd_bc_tbls,
				     bc_tbls_size);
	अगर (ret) अणु
		IWL_ERR(trans, "Scheduler BC Table allocation failed\n");
		जाओ error;
	पूर्ण

	/* Alloc keep-warm buffer */
	ret = iwl_pcie_alloc_dma_ptr(trans, &trans_pcie->kw, IWL_KW_SIZE);
	अगर (ret) अणु
		IWL_ERR(trans, "Keep Warm allocation failed\n");
		जाओ error;
	पूर्ण

	trans_pcie->txq_memory =
		kसुस्मृति(trans->trans_cfg->base_params->num_of_queues,
			माप(काष्ठा iwl_txq), GFP_KERNEL);
	अगर (!trans_pcie->txq_memory) अणु
		IWL_ERR(trans, "Not enough memory for txq\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* Alloc and init all Tx queues, including the command queue (#4/#9) */
	क्रम (txq_id = 0; txq_id < trans->trans_cfg->base_params->num_of_queues;
	     txq_id++) अणु
		bool cmd_queue = (txq_id == trans->txqs.cmd.q_id);

		अगर (cmd_queue)
			slots_num = max_t(u32, IWL_CMD_QUEUE_SIZE,
					  trans->cfg->min_txq_size);
		अन्यथा
			slots_num = max_t(u32, IWL_DEFAULT_QUEUE_SIZE,
					  trans->cfg->min_256_ba_txq_size);
		trans->txqs.txq[txq_id] = &trans_pcie->txq_memory[txq_id];
		ret = iwl_txq_alloc(trans, trans->txqs.txq[txq_id], slots_num,
				    cmd_queue);
		अगर (ret) अणु
			IWL_ERR(trans, "Tx %d queue alloc failed\n", txq_id);
			जाओ error;
		पूर्ण
		trans->txqs.txq[txq_id]->id = txq_id;
	पूर्ण

	वापस 0;

error:
	iwl_pcie_tx_मुक्त(trans);

	वापस ret;
पूर्ण

पूर्णांक iwl_pcie_tx_init(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक ret;
	पूर्णांक txq_id, slots_num;
	bool alloc = false;

	अगर (!trans_pcie->txq_memory) अणु
		ret = iwl_pcie_tx_alloc(trans);
		अगर (ret)
			जाओ error;
		alloc = true;
	पूर्ण

	spin_lock_bh(&trans_pcie->irq_lock);

	/* Turn off all Tx DMA fअगरos */
	iwl_scd_deactivate_fअगरos(trans);

	/* Tell NIC where to find the "keep warm" buffer */
	iwl_ग_लिखो_direct32(trans, FH_KW_MEM_ADDR_REG,
			   trans_pcie->kw.dma >> 4);

	spin_unlock_bh(&trans_pcie->irq_lock);

	/* Alloc and init all Tx queues, including the command queue (#4/#9) */
	क्रम (txq_id = 0; txq_id < trans->trans_cfg->base_params->num_of_queues;
	     txq_id++) अणु
		bool cmd_queue = (txq_id == trans->txqs.cmd.q_id);

		अगर (cmd_queue)
			slots_num = max_t(u32, IWL_CMD_QUEUE_SIZE,
					  trans->cfg->min_txq_size);
		अन्यथा
			slots_num = max_t(u32, IWL_DEFAULT_QUEUE_SIZE,
					  trans->cfg->min_256_ba_txq_size);
		ret = iwl_txq_init(trans, trans->txqs.txq[txq_id], slots_num,
				   cmd_queue);
		अगर (ret) अणु
			IWL_ERR(trans, "Tx %d queue init failed\n", txq_id);
			जाओ error;
		पूर्ण

		/*
		 * Tell nic where to find circular buffer of TFDs क्रम a
		 * given Tx queue, and enable the DMA channel used क्रम that
		 * queue.
		 * Circular buffer (TFD queue in DRAM) physical base address
		 */
		iwl_ग_लिखो_direct32(trans, FH_MEM_CBBC_QUEUE(trans, txq_id),
				   trans->txqs.txq[txq_id]->dma_addr >> 8);
	पूर्ण

	iwl_set_bits_prph(trans, SCD_GP_CTRL, SCD_GP_CTRL_AUTO_ACTIVE_MODE);
	अगर (trans->trans_cfg->base_params->num_of_queues > 20)
		iwl_set_bits_prph(trans, SCD_GP_CTRL,
				  SCD_GP_CTRL_ENABLE_31_QUEUES);

	वापस 0;
error:
	/*Upon error, मुक्त only अगर we allocated something */
	अगर (alloc)
		iwl_pcie_tx_मुक्त(trans);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_pcie_set_cmd_in_flight(काष्ठा iwl_trans *trans,
				      स्थिर काष्ठा iwl_host_cmd *cmd)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	/* Make sure the NIC is still alive in the bus */
	अगर (test_bit(STATUS_TRANS_DEAD, &trans->status))
		वापस -ENODEV;

	अगर (!trans->trans_cfg->base_params->apmg_wake_up_wa)
		वापस 0;

	/*
	 * wake up the NIC to make sure that the firmware will see the host
	 * command - we will let the NIC sleep once all the host commands
	 * वापसed. This needs to be करोne only on NICs that have
	 * apmg_wake_up_wa set (see above.)
	 */
	अगर (!_iwl_trans_pcie_grab_nic_access(trans))
		वापस -EIO;

	/*
	 * In iwl_trans_grab_nic_access(), we've acquired the reg_lock.
	 * There, we also वापसed immediately अगर cmd_hold_nic_awake is
	 * alपढ़ोy true, so it's OK to unconditionally set it to true.
	 */
	trans_pcie->cmd_hold_nic_awake = true;
	spin_unlock(&trans_pcie->reg_lock);

	वापस 0;
पूर्ण

/*
 * iwl_pcie_cmdq_reclaim - Reclaim TX command queue entries alपढ़ोy Tx'd
 *
 * When FW advances 'R' index, all entries between old and new 'R' index
 * need to be reclaimed. As result, some मुक्त space क्रमms.  If there is
 * enough मुक्त space (> low mark), wake the stack that feeds us.
 */
अटल व्योम iwl_pcie_cmdq_reclaim(काष्ठा iwl_trans *trans, पूर्णांक txq_id, पूर्णांक idx)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];
	पूर्णांक nमुक्तd = 0;
	u16 r;

	lockdep_निश्चित_held(&txq->lock);

	idx = iwl_txq_get_cmd_index(txq, idx);
	r = iwl_txq_get_cmd_index(txq, txq->पढ़ो_ptr);

	अगर (idx >= trans->trans_cfg->base_params->max_tfd_queue_size ||
	    (!iwl_txq_used(txq, idx))) अणु
		WARN_ONCE(test_bit(txq_id, trans->txqs.queue_used),
			  "%s: Read index for DMA queue txq id (%d), index %d is out of range [0-%d] %d %d.\n",
			  __func__, txq_id, idx,
			  trans->trans_cfg->base_params->max_tfd_queue_size,
			  txq->ग_लिखो_ptr, txq->पढ़ो_ptr);
		वापस;
	पूर्ण

	क्रम (idx = iwl_txq_inc_wrap(trans, idx); r != idx;
	     r = iwl_txq_inc_wrap(trans, r)) अणु
		txq->पढ़ो_ptr = iwl_txq_inc_wrap(trans, txq->पढ़ो_ptr);

		अगर (nमुक्तd++ > 0) अणु
			IWL_ERR(trans, "HCMD skipped: index (%d) %d %d\n",
				idx, txq->ग_लिखो_ptr, r);
			iwl_क्रमce_nmi(trans);
		पूर्ण
	पूर्ण

	अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr)
		iwl_pcie_clear_cmd_in_flight(trans);

	iwl_txq_progress(txq);
पूर्ण

अटल पूर्णांक iwl_pcie_txq_set_ratid_map(काष्ठा iwl_trans *trans, u16 ra_tid,
				 u16 txq_id)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 tbl_dw_addr;
	u32 tbl_dw;
	u16 scd_q2ratid;

	scd_q2ratid = ra_tid & SCD_QUEUE_RA_TID_MAP_RATID_MSK;

	tbl_dw_addr = trans_pcie->scd_base_addr +
			SCD_TRANS_TBL_OFFSET_QUEUE(txq_id);

	tbl_dw = iwl_trans_पढ़ो_mem32(trans, tbl_dw_addr);

	अगर (txq_id & 0x1)
		tbl_dw = (scd_q2ratid << 16) | (tbl_dw & 0x0000FFFF);
	अन्यथा
		tbl_dw = scd_q2ratid | (tbl_dw & 0xFFFF0000);

	iwl_trans_ग_लिखो_mem32(trans, tbl_dw_addr, tbl_dw);

	वापस 0;
पूर्ण

/* Receiver address (actually, Rx station's index पूर्णांकo station table),
 * combined with Traffic ID (QOS priority), in क्रमmat used by Tx Scheduler */
#घोषणा BUILD_RAxTID(sta_id, tid)	(((sta_id) << 4) + (tid))

bool iwl_trans_pcie_txq_enable(काष्ठा iwl_trans *trans, पूर्णांक txq_id, u16 ssn,
			       स्थिर काष्ठा iwl_trans_txq_scd_cfg *cfg,
			       अचिन्हित पूर्णांक wdg_समयout)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];
	पूर्णांक fअगरo = -1;
	bool scd_bug = false;

	अगर (test_and_set_bit(txq_id, trans->txqs.queue_used))
		WARN_ONCE(1, "queue %d already used - expect issues", txq_id);

	txq->wd_समयout = msecs_to_jअगरfies(wdg_समयout);

	अगर (cfg) अणु
		fअगरo = cfg->fअगरo;

		/* Disable the scheduler prior configuring the cmd queue */
		अगर (txq_id == trans->txqs.cmd.q_id &&
		    trans_pcie->scd_set_active)
			iwl_scd_enable_set_active(trans, 0);

		/* Stop this Tx queue beक्रमe configuring it */
		iwl_scd_txq_set_inactive(trans, txq_id);

		/* Set this queue as a chain-building queue unless it is CMD */
		अगर (txq_id != trans->txqs.cmd.q_id)
			iwl_scd_txq_set_chain(trans, txq_id);

		अगर (cfg->aggregate) अणु
			u16 ra_tid = BUILD_RAxTID(cfg->sta_id, cfg->tid);

			/* Map receiver-address / traffic-ID to this queue */
			iwl_pcie_txq_set_ratid_map(trans, ra_tid, txq_id);

			/* enable aggregations क्रम the queue */
			iwl_scd_txq_enable_agg(trans, txq_id);
			txq->ampdu = true;
		पूर्ण अन्यथा अणु
			/*
			 * disable aggregations क्रम the queue, this will also
			 * make the ra_tid mapping configuration irrelevant
			 * since it is now a non-AGG queue.
			 */
			iwl_scd_txq_disable_agg(trans, txq_id);

			ssn = txq->पढ़ो_ptr;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If we need to move the SCD ग_लिखो poपूर्णांकer by steps of
		 * 0x40, 0x80 or 0xc0, it माला_लो stuck. Aव्योमs this and let
		 * the op_mode know by वापसing true later.
		 * Do this only in हाल cfg is शून्य since this trick can
		 * be करोne only अगर we have DQA enabled which is true क्रम mvm
		 * only. And mvm never sets a cfg poपूर्णांकer.
		 * This is really ugly, but this is the easiest way out क्रम
		 * this sad hardware issue.
		 * This bug has been fixed on devices 9000 and up.
		 */
		scd_bug = !trans->trans_cfg->mq_rx_supported &&
			!((ssn - txq->ग_लिखो_ptr) & 0x3f) &&
			(ssn != txq->ग_लिखो_ptr);
		अगर (scd_bug)
			ssn++;
	पूर्ण

	/* Place first TFD at index corresponding to start sequence number.
	 * Assumes that ssn_idx is valid (!= 0xFFF) */
	txq->पढ़ो_ptr = (ssn & 0xff);
	txq->ग_लिखो_ptr = (ssn & 0xff);
	iwl_ग_लिखो_direct32(trans, HBUS_TARG_WRPTR,
			   (ssn & 0xff) | (txq_id << 8));

	अगर (cfg) अणु
		u8 frame_limit = cfg->frame_limit;

		iwl_ग_लिखो_prph(trans, SCD_QUEUE_RDPTR(txq_id), ssn);

		/* Set up Tx winकरोw size and frame limit क्रम this queue */
		iwl_trans_ग_लिखो_mem32(trans, trans_pcie->scd_base_addr +
				SCD_CONTEXT_QUEUE_OFFSET(txq_id), 0);
		iwl_trans_ग_लिखो_mem32(trans,
			trans_pcie->scd_base_addr +
			SCD_CONTEXT_QUEUE_OFFSET(txq_id) + माप(u32),
			SCD_QUEUE_CTX_REG2_VAL(WIN_SIZE, frame_limit) |
			SCD_QUEUE_CTX_REG2_VAL(FRAME_LIMIT, frame_limit));

		/* Set up status area in SRAM, map to Tx DMA/FIFO, activate */
		iwl_ग_लिखो_prph(trans, SCD_QUEUE_STATUS_BITS(txq_id),
			       (1 << SCD_QUEUE_STTS_REG_POS_ACTIVE) |
			       (cfg->fअगरo << SCD_QUEUE_STTS_REG_POS_TXF) |
			       (1 << SCD_QUEUE_STTS_REG_POS_WSL) |
			       SCD_QUEUE_STTS_REG_MSK);

		/* enable the scheduler क्रम this queue (only) */
		अगर (txq_id == trans->txqs.cmd.q_id &&
		    trans_pcie->scd_set_active)
			iwl_scd_enable_set_active(trans, BIT(txq_id));

		IWL_DEBUG_TX_QUEUES(trans,
				    "Activate queue %d on FIFO %d WrPtr: %d\n",
				    txq_id, fअगरo, ssn & 0xff);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_TX_QUEUES(trans,
				    "Activate queue %d WrPtr: %d\n",
				    txq_id, ssn & 0xff);
	पूर्ण

	वापस scd_bug;
पूर्ण

व्योम iwl_trans_pcie_txq_set_shared_mode(काष्ठा iwl_trans *trans, u32 txq_id,
					bool shared_mode)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[txq_id];

	txq->ampdu = !shared_mode;
पूर्ण

व्योम iwl_trans_pcie_txq_disable(काष्ठा iwl_trans *trans, पूर्णांक txq_id,
				bool configure_scd)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 stts_addr = trans_pcie->scd_base_addr +
			SCD_TX_STTS_QUEUE_OFFSET(txq_id);
	अटल स्थिर u32 zero_val[4] = अणुपूर्ण;

	trans->txqs.txq[txq_id]->frozen_expiry_reमुख्यder = 0;
	trans->txqs.txq[txq_id]->frozen = false;

	/*
	 * Upon HW Rfसमाप्त - we stop the device, and then stop the queues
	 * in the op_mode. Just क्रम the sake of the simplicity of the op_mode,
	 * allow the op_mode to call txq_disable after it alपढ़ोy called
	 * stop_device.
	 */
	अगर (!test_and_clear_bit(txq_id, trans->txqs.queue_used)) अणु
		WARN_ONCE(test_bit(STATUS_DEVICE_ENABLED, &trans->status),
			  "queue %d not used", txq_id);
		वापस;
	पूर्ण

	अगर (configure_scd) अणु
		iwl_scd_txq_set_inactive(trans, txq_id);

		iwl_trans_ग_लिखो_mem(trans, stts_addr, (व्योम *)zero_val,
				    ARRAY_SIZE(zero_val));
	पूर्ण

	iwl_pcie_txq_unmap(trans, txq_id);
	trans->txqs.txq[txq_id]->ampdu = false;

	IWL_DEBUG_TX_QUEUES(trans, "Deactivate queue %d\n", txq_id);
पूर्ण

/*************** HOST COMMAND QUEUE FUNCTIONS   *****/

/*
 * iwl_pcie_enqueue_hcmd - enqueue a uCode command
 * @priv: device निजी data poपूर्णांक
 * @cmd: a poपूर्णांकer to the ucode command काष्ठाure
 *
 * The function वापसs < 0 values to indicate the operation
 * failed. On success, it वापसs the index (>= 0) of command in the
 * command queue.
 */
पूर्णांक iwl_pcie_enqueue_hcmd(काष्ठा iwl_trans *trans,
			  काष्ठा iwl_host_cmd *cmd)
अणु
	काष्ठा iwl_txq *txq = trans->txqs.txq[trans->txqs.cmd.q_id];
	काष्ठा iwl_device_cmd *out_cmd;
	काष्ठा iwl_cmd_meta *out_meta;
	व्योम *dup_buf = शून्य;
	dma_addr_t phys_addr;
	पूर्णांक idx;
	u16 copy_size, cmd_size, tb0_size;
	bool had_nocopy = false;
	u8 group_id = iwl_cmd_groupid(cmd->id);
	पूर्णांक i, ret;
	u32 cmd_pos;
	स्थिर u8 *cmddata[IWL_MAX_CMD_TBS_PER_TFD];
	u16 cmdlen[IWL_MAX_CMD_TBS_PER_TFD];
	अचिन्हित दीर्घ flags;

	अगर (WARN(!trans->wide_cmd_header &&
		 group_id > IWL_ALWAYS_LONG_GROUP,
		 "unsupported wide command %#x\n", cmd->id))
		वापस -EINVAL;

	अगर (group_id != 0) अणु
		copy_size = माप(काष्ठा iwl_cmd_header_wide);
		cmd_size = माप(काष्ठा iwl_cmd_header_wide);
	पूर्ण अन्यथा अणु
		copy_size = माप(काष्ठा iwl_cmd_header);
		cmd_size = माप(काष्ठा iwl_cmd_header);
	पूर्ण

	/* need one क्रम the header अगर the first is NOCOPY */
	BUILD_BUG_ON(IWL_MAX_CMD_TBS_PER_TFD > IWL_NUM_OF_TBS - 1);

	क्रम (i = 0; i < IWL_MAX_CMD_TBS_PER_TFD; i++) अणु
		cmddata[i] = cmd->data[i];
		cmdlen[i] = cmd->len[i];

		अगर (!cmd->len[i])
			जारी;

		/* need at least IWL_FIRST_TB_SIZE copied */
		अगर (copy_size < IWL_FIRST_TB_SIZE) अणु
			पूर्णांक copy = IWL_FIRST_TB_SIZE - copy_size;

			अगर (copy > cmdlen[i])
				copy = cmdlen[i];
			cmdlen[i] -= copy;
			cmddata[i] += copy;
			copy_size += copy;
		पूर्ण

		अगर (cmd->dataflags[i] & IWL_HCMD_DFL_NOCOPY) अणु
			had_nocopy = true;
			अगर (WARN_ON(cmd->dataflags[i] & IWL_HCMD_DFL_DUP)) अणु
				idx = -EINVAL;
				जाओ मुक्त_dup_buf;
			पूर्ण
		पूर्ण अन्यथा अगर (cmd->dataflags[i] & IWL_HCMD_DFL_DUP) अणु
			/*
			 * This is also a chunk that isn't copied
			 * to the अटल buffer so set had_nocopy.
			 */
			had_nocopy = true;

			/* only allowed once */
			अगर (WARN_ON(dup_buf)) अणु
				idx = -EINVAL;
				जाओ मुक्त_dup_buf;
			पूर्ण

			dup_buf = kmemdup(cmddata[i], cmdlen[i],
					  GFP_ATOMIC);
			अगर (!dup_buf)
				वापस -ENOMEM;
		पूर्ण अन्यथा अणु
			/* NOCOPY must not be followed by normal! */
			अगर (WARN_ON(had_nocopy)) अणु
				idx = -EINVAL;
				जाओ मुक्त_dup_buf;
			पूर्ण
			copy_size += cmdlen[i];
		पूर्ण
		cmd_size += cmd->len[i];
	पूर्ण

	/*
	 * If any of the command काष्ठाures end up being larger than
	 * the TFD_MAX_PAYLOAD_SIZE and they aren't dynamically
	 * allocated पूर्णांकo separate TFDs, then we will need to
	 * increase the size of the buffers.
	 */
	अगर (WARN(copy_size > TFD_MAX_PAYLOAD_SIZE,
		 "Command %s (%#x) is too large (%d bytes)\n",
		 iwl_get_cmd_string(trans, cmd->id),
		 cmd->id, copy_size)) अणु
		idx = -EINVAL;
		जाओ मुक्त_dup_buf;
	पूर्ण

	spin_lock_irqsave(&txq->lock, flags);

	अगर (iwl_txq_space(trans, txq) < ((cmd->flags & CMD_ASYNC) ? 2 : 1)) अणु
		spin_unlock_irqrestore(&txq->lock, flags);

		IWL_ERR(trans, "No space in command queue\n");
		iwl_op_mode_cmd_queue_full(trans->op_mode);
		idx = -ENOSPC;
		जाओ मुक्त_dup_buf;
	पूर्ण

	idx = iwl_txq_get_cmd_index(txq, txq->ग_लिखो_ptr);
	out_cmd = txq->entries[idx].cmd;
	out_meta = &txq->entries[idx].meta;

	स_रखो(out_meta, 0, माप(*out_meta));	/* re-initialize to शून्य */
	अगर (cmd->flags & CMD_WANT_SKB)
		out_meta->source = cmd;

	/* set up the header */
	अगर (group_id != 0) अणु
		out_cmd->hdr_wide.cmd = iwl_cmd_opcode(cmd->id);
		out_cmd->hdr_wide.group_id = group_id;
		out_cmd->hdr_wide.version = iwl_cmd_version(cmd->id);
		out_cmd->hdr_wide.length =
			cpu_to_le16(cmd_size -
				    माप(काष्ठा iwl_cmd_header_wide));
		out_cmd->hdr_wide.reserved = 0;
		out_cmd->hdr_wide.sequence =
			cpu_to_le16(QUEUE_TO_SEQ(trans->txqs.cmd.q_id) |
						 INDEX_TO_SEQ(txq->ग_लिखो_ptr));

		cmd_pos = माप(काष्ठा iwl_cmd_header_wide);
		copy_size = माप(काष्ठा iwl_cmd_header_wide);
	पूर्ण अन्यथा अणु
		out_cmd->hdr.cmd = iwl_cmd_opcode(cmd->id);
		out_cmd->hdr.sequence =
			cpu_to_le16(QUEUE_TO_SEQ(trans->txqs.cmd.q_id) |
						 INDEX_TO_SEQ(txq->ग_लिखो_ptr));
		out_cmd->hdr.group_id = 0;

		cmd_pos = माप(काष्ठा iwl_cmd_header);
		copy_size = माप(काष्ठा iwl_cmd_header);
	पूर्ण

	/* and copy the data that needs to be copied */
	क्रम (i = 0; i < IWL_MAX_CMD_TBS_PER_TFD; i++) अणु
		पूर्णांक copy;

		अगर (!cmd->len[i])
			जारी;

		/* copy everything अगर not nocopy/dup */
		अगर (!(cmd->dataflags[i] & (IWL_HCMD_DFL_NOCOPY |
					   IWL_HCMD_DFL_DUP))) अणु
			copy = cmd->len[i];

			स_नकल((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
			cmd_pos += copy;
			copy_size += copy;
			जारी;
		पूर्ण

		/*
		 * Otherwise we need at least IWL_FIRST_TB_SIZE copied
		 * in total (क्रम bi-directional DMA), but copy up to what
		 * we can fit पूर्णांकo the payload क्रम debug dump purposes.
		 */
		copy = min_t(पूर्णांक, TFD_MAX_PAYLOAD_SIZE - cmd_pos, cmd->len[i]);

		स_नकल((u8 *)out_cmd + cmd_pos, cmd->data[i], copy);
		cmd_pos += copy;

		/* However, treat copy_size the proper way, we need it below */
		अगर (copy_size < IWL_FIRST_TB_SIZE) अणु
			copy = IWL_FIRST_TB_SIZE - copy_size;

			अगर (copy > cmd->len[i])
				copy = cmd->len[i];
			copy_size += copy;
		पूर्ण
	पूर्ण

	IWL_DEBUG_HC(trans,
		     "Sending command %s (%.2x.%.2x), seq: 0x%04X, %d bytes at %d[%d]:%d\n",
		     iwl_get_cmd_string(trans, cmd->id),
		     group_id, out_cmd->hdr.cmd,
		     le16_to_cpu(out_cmd->hdr.sequence),
		     cmd_size, txq->ग_लिखो_ptr, idx, trans->txqs.cmd.q_id);

	/* start the TFD with the minimum copy bytes */
	tb0_size = min_t(पूर्णांक, copy_size, IWL_FIRST_TB_SIZE);
	स_नकल(&txq->first_tb_bufs[idx], &out_cmd->hdr, tb0_size);
	iwl_pcie_txq_build_tfd(trans, txq,
			       iwl_txq_get_first_tb_dma(txq, idx),
			       tb0_size, true);

	/* map first command fragment, अगर any reमुख्यs */
	अगर (copy_size > tb0_size) अणु
		phys_addr = dma_map_single(trans->dev,
					   ((u8 *)&out_cmd->hdr) + tb0_size,
					   copy_size - tb0_size,
					   DMA_TO_DEVICE);
		अगर (dma_mapping_error(trans->dev, phys_addr)) अणु
			iwl_txq_gen1_tfd_unmap(trans, out_meta, txq,
					       txq->ग_लिखो_ptr);
			idx = -ENOMEM;
			जाओ out;
		पूर्ण

		iwl_pcie_txq_build_tfd(trans, txq, phys_addr,
				       copy_size - tb0_size, false);
	पूर्ण

	/* map the reमुख्यing (adjusted) nocopy/dup fragments */
	क्रम (i = 0; i < IWL_MAX_CMD_TBS_PER_TFD; i++) अणु
		स्थिर व्योम *data = cmddata[i];

		अगर (!cmdlen[i])
			जारी;
		अगर (!(cmd->dataflags[i] & (IWL_HCMD_DFL_NOCOPY |
					   IWL_HCMD_DFL_DUP)))
			जारी;
		अगर (cmd->dataflags[i] & IWL_HCMD_DFL_DUP)
			data = dup_buf;
		phys_addr = dma_map_single(trans->dev, (व्योम *)data,
					   cmdlen[i], DMA_TO_DEVICE);
		अगर (dma_mapping_error(trans->dev, phys_addr)) अणु
			iwl_txq_gen1_tfd_unmap(trans, out_meta, txq,
					       txq->ग_लिखो_ptr);
			idx = -ENOMEM;
			जाओ out;
		पूर्ण

		iwl_pcie_txq_build_tfd(trans, txq, phys_addr, cmdlen[i], false);
	पूर्ण

	BUILD_BUG_ON(IWL_TFH_NUM_TBS > माप(out_meta->tbs) * BITS_PER_BYTE);
	out_meta->flags = cmd->flags;
	अगर (WARN_ON_ONCE(txq->entries[idx].मुक्त_buf))
		kमुक्त_sensitive(txq->entries[idx].मुक्त_buf);
	txq->entries[idx].मुक्त_buf = dup_buf;

	trace_iwlwअगरi_dev_hcmd(trans->dev, cmd, cmd_size, &out_cmd->hdr_wide);

	/* start समयr अगर queue currently empty */
	अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr && txq->wd_समयout)
		mod_समयr(&txq->stuck_समयr, jअगरfies + txq->wd_समयout);

	ret = iwl_pcie_set_cmd_in_flight(trans, cmd);
	अगर (ret < 0) अणु
		idx = ret;
		जाओ out;
	पूर्ण

	/* Increment and update queue's ग_लिखो index */
	txq->ग_लिखो_ptr = iwl_txq_inc_wrap(trans, txq->ग_लिखो_ptr);
	iwl_pcie_txq_inc_wr_ptr(trans, txq);

 out:
	spin_unlock_irqrestore(&txq->lock, flags);
 मुक्त_dup_buf:
	अगर (idx < 0)
		kमुक्त(dup_buf);
	वापस idx;
पूर्ण

/*
 * iwl_pcie_hcmd_complete - Pull unused buffers off the queue and reclaim them
 * @rxb: Rx buffer to reclaim
 */
व्योम iwl_pcie_hcmd_complete(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	u8 group_id;
	u32 cmd_id;
	पूर्णांक txq_id = SEQ_TO_QUEUE(sequence);
	पूर्णांक index = SEQ_TO_INDEX(sequence);
	पूर्णांक cmd_index;
	काष्ठा iwl_device_cmd *cmd;
	काष्ठा iwl_cmd_meta *meta;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_txq *txq = trans->txqs.txq[trans->txqs.cmd.q_id];

	/* If a Tx command is being handled and it isn't in the actual
	 * command queue then there a command routing bug has been पूर्णांकroduced
	 * in the queue management code. */
	अगर (WARN(txq_id != trans->txqs.cmd.q_id,
		 "wrong command queue %d (should be %d), sequence 0x%X readp=%d writep=%d\n",
		 txq_id, trans->txqs.cmd.q_id, sequence, txq->पढ़ो_ptr,
		 txq->ग_लिखो_ptr)) अणु
		iwl_prपूर्णांक_hex_error(trans, pkt, 32);
		वापस;
	पूर्ण

	spin_lock_bh(&txq->lock);

	cmd_index = iwl_txq_get_cmd_index(txq, index);
	cmd = txq->entries[cmd_index].cmd;
	meta = &txq->entries[cmd_index].meta;
	group_id = cmd->hdr.group_id;
	cmd_id = iwl_cmd_id(cmd->hdr.cmd, group_id, 0);

	iwl_txq_gen1_tfd_unmap(trans, meta, txq, index);

	/* Input error checking is करोne when commands are added to queue. */
	अगर (meta->flags & CMD_WANT_SKB) अणु
		काष्ठा page *p = rxb_steal_page(rxb);

		meta->source->resp_pkt = pkt;
		meta->source->_rx_page_addr = (अचिन्हित दीर्घ)page_address(p);
		meta->source->_rx_page_order = trans_pcie->rx_page_order;
	पूर्ण

	अगर (meta->flags & CMD_WANT_ASYNC_CALLBACK)
		iwl_op_mode_async_cb(trans->op_mode, cmd);

	iwl_pcie_cmdq_reclaim(trans, txq_id, index);

	अगर (!(meta->flags & CMD_ASYNC)) अणु
		अगर (!test_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status)) अणु
			IWL_WARN(trans,
				 "HCMD_ACTIVE already clear for command %s\n",
				 iwl_get_cmd_string(trans, cmd_id));
		पूर्ण
		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		IWL_DEBUG_INFO(trans, "Clearing HCMD_ACTIVE for command %s\n",
			       iwl_get_cmd_string(trans, cmd_id));
		wake_up(&trans->रुको_command_queue);
	पूर्ण

	meta->flags = 0;

	spin_unlock_bh(&txq->lock);
पूर्ण

अटल पूर्णांक iwl_fill_data_tbs(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
			     काष्ठा iwl_txq *txq, u8 hdr_len,
			     काष्ठा iwl_cmd_meta *out_meta)
अणु
	u16 head_tb_len;
	पूर्णांक i;

	/*
	 * Set up TFD's third entry to poपूर्णांक directly to reमुख्यder
	 * of skb's head, अगर any
	 */
	head_tb_len = skb_headlen(skb) - hdr_len;

	अगर (head_tb_len > 0) अणु
		dma_addr_t tb_phys = dma_map_single(trans->dev,
						    skb->data + hdr_len,
						    head_tb_len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(trans->dev, tb_phys)))
			वापस -EINVAL;
		trace_iwlwअगरi_dev_tx_tb(trans->dev, skb, skb->data + hdr_len,
					tb_phys, head_tb_len);
		iwl_pcie_txq_build_tfd(trans, txq, tb_phys, head_tb_len, false);
	पूर्ण

	/* set up the reमुख्यing entries to poपूर्णांक to the data */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		dma_addr_t tb_phys;
		पूर्णांक tb_idx;

		अगर (!skb_frag_size(frag))
			जारी;

		tb_phys = skb_frag_dma_map(trans->dev, frag, 0,
					   skb_frag_size(frag), DMA_TO_DEVICE);

		अगर (unlikely(dma_mapping_error(trans->dev, tb_phys)))
			वापस -EINVAL;
		trace_iwlwअगरi_dev_tx_tb(trans->dev, skb, skb_frag_address(frag),
					tb_phys, skb_frag_size(frag));
		tb_idx = iwl_pcie_txq_build_tfd(trans, txq, tb_phys,
						skb_frag_size(frag), false);
		अगर (tb_idx < 0)
			वापस tb_idx;

		out_meta->tbs |= BIT(tb_idx);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_INET
अटल पूर्णांक iwl_fill_data_tbs_amsdu(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
				   काष्ठा iwl_txq *txq, u8 hdr_len,
				   काष्ठा iwl_cmd_meta *out_meta,
				   काष्ठा iwl_device_tx_cmd *dev_cmd,
				   u16 tb1_len)
अणु
	काष्ठा iwl_tx_cmd *tx_cmd = (व्योम *)dev_cmd->payload;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	अचिन्हित पूर्णांक snap_ip_tcp_hdrlen, ip_hdrlen, total_len, hdr_room;
	अचिन्हित पूर्णांक mss = skb_shinfo(skb)->gso_size;
	u16 length, iv_len, amsdu_pad;
	u8 *start_hdr;
	काष्ठा iwl_tso_hdr_page *hdr_page;
	काष्ठा tso_t tso;

	/* अगर the packet is रक्षित, then it must be CCMP or GCMP */
	BUILD_BUG_ON(IEEE80211_CCMP_HDR_LEN != IEEE80211_GCMP_HDR_LEN);
	iv_len = ieee80211_has_रक्षित(hdr->frame_control) ?
		IEEE80211_CCMP_HDR_LEN : 0;

	trace_iwlwअगरi_dev_tx(trans->dev, skb,
			     iwl_txq_get_tfd(trans, txq, txq->ग_लिखो_ptr),
			     trans->txqs.tfd.size,
			     &dev_cmd->hdr, IWL_FIRST_TB_SIZE + tb1_len, 0);

	ip_hdrlen = skb_transport_header(skb) - skb_network_header(skb);
	snap_ip_tcp_hdrlen = 8 + ip_hdrlen + tcp_hdrlen(skb);
	total_len = skb->len - snap_ip_tcp_hdrlen - hdr_len - iv_len;
	amsdu_pad = 0;

	/* total amount of header we may need क्रम this A-MSDU */
	hdr_room = DIV_ROUND_UP(total_len, mss) *
		(3 + snap_ip_tcp_hdrlen + माप(काष्ठा ethhdr)) + iv_len;

	/* Our device supports 9 segments at most, it will fit in 1 page */
	hdr_page = get_page_hdr(trans, hdr_room, skb);
	अगर (!hdr_page)
		वापस -ENOMEM;

	start_hdr = hdr_page->pos;
	स_नकल(hdr_page->pos, skb->data + hdr_len, iv_len);
	hdr_page->pos += iv_len;

	/*
	 * Pull the ieee80211 header + IV to be able to use TSO core,
	 * we will restore it क्रम the tx_status flow.
	 */
	skb_pull(skb, hdr_len + iv_len);

	/*
	 * Remove the length of all the headers that we करोn't actually
	 * have in the MPDU by themselves, but that we duplicate पूर्णांकo
	 * all the dअगरferent MSDUs inside the A-MSDU.
	 */
	le16_add_cpu(&tx_cmd->len, -snap_ip_tcp_hdrlen);

	tso_start(skb, &tso);

	जबतक (total_len) अणु
		/* this is the data left क्रम this subframe */
		अचिन्हित पूर्णांक data_left =
			min_t(अचिन्हित पूर्णांक, mss, total_len);
		अचिन्हित पूर्णांक hdr_tb_len;
		dma_addr_t hdr_tb_phys;
		u8 *subf_hdrs_start = hdr_page->pos;

		total_len -= data_left;

		स_रखो(hdr_page->pos, 0, amsdu_pad);
		hdr_page->pos += amsdu_pad;
		amsdu_pad = (4 - (माप(काष्ठा ethhdr) + snap_ip_tcp_hdrlen +
				  data_left)) & 0x3;
		ether_addr_copy(hdr_page->pos, ieee80211_get_DA(hdr));
		hdr_page->pos += ETH_ALEN;
		ether_addr_copy(hdr_page->pos, ieee80211_get_SA(hdr));
		hdr_page->pos += ETH_ALEN;

		length = snap_ip_tcp_hdrlen + data_left;
		*((__be16 *)hdr_page->pos) = cpu_to_be16(length);
		hdr_page->pos += माप(length);

		/*
		 * This will copy the SNAP as well which will be considered
		 * as MAC header.
		 */
		tso_build_hdr(skb, hdr_page->pos, &tso, data_left, !total_len);

		hdr_page->pos += snap_ip_tcp_hdrlen;

		hdr_tb_len = hdr_page->pos - start_hdr;
		hdr_tb_phys = dma_map_single(trans->dev, start_hdr,
					     hdr_tb_len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(trans->dev, hdr_tb_phys)))
			वापस -EINVAL;
		iwl_pcie_txq_build_tfd(trans, txq, hdr_tb_phys,
				       hdr_tb_len, false);
		trace_iwlwअगरi_dev_tx_tb(trans->dev, skb, start_hdr,
					hdr_tb_phys, hdr_tb_len);
		/* add this subframe's headers' length to the tx_cmd */
		le16_add_cpu(&tx_cmd->len, hdr_page->pos - subf_hdrs_start);

		/* prepare the start_hdr क्रम the next subframe */
		start_hdr = hdr_page->pos;

		/* put the payload */
		जबतक (data_left) अणु
			अचिन्हित पूर्णांक size = min_t(अचिन्हित पूर्णांक, tso.size,
						  data_left);
			dma_addr_t tb_phys;

			tb_phys = dma_map_single(trans->dev, tso.data,
						 size, DMA_TO_DEVICE);
			अगर (unlikely(dma_mapping_error(trans->dev, tb_phys)))
				वापस -EINVAL;

			iwl_pcie_txq_build_tfd(trans, txq, tb_phys,
					       size, false);
			trace_iwlwअगरi_dev_tx_tb(trans->dev, skb, tso.data,
						tb_phys, size);

			data_left -= size;
			tso_build_data(skb, &tso, size);
		पूर्ण
	पूर्ण

	/* re -add the WiFi header and IV */
	skb_push(skb, hdr_len + iv_len);

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_INET */
अटल पूर्णांक iwl_fill_data_tbs_amsdu(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
				   काष्ठा iwl_txq *txq, u8 hdr_len,
				   काष्ठा iwl_cmd_meta *out_meta,
				   काष्ठा iwl_device_tx_cmd *dev_cmd,
				   u16 tb1_len)
अणु
	/* No A-MSDU without CONFIG_INET */
	WARN_ON(1);

	वापस -1;
पूर्ण
#पूर्ण_अगर /* CONFIG_INET */

पूर्णांक iwl_trans_pcie_tx(काष्ठा iwl_trans *trans, काष्ठा sk_buff *skb,
		      काष्ठा iwl_device_tx_cmd *dev_cmd, पूर्णांक txq_id)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा iwl_tx_cmd *tx_cmd = (काष्ठा iwl_tx_cmd *)dev_cmd->payload;
	काष्ठा iwl_cmd_meta *out_meta;
	काष्ठा iwl_txq *txq;
	dma_addr_t tb0_phys, tb1_phys, scratch_phys;
	व्योम *tb1_addr;
	व्योम *tfd;
	u16 len, tb1_len;
	bool रुको_ग_लिखो_ptr;
	__le16 fc;
	u8 hdr_len;
	u16 wअगरi_seq;
	bool amsdu;

	txq = trans->txqs.txq[txq_id];

	अगर (WARN_ONCE(!test_bit(txq_id, trans->txqs.queue_used),
		      "TX on unused queue %d\n", txq_id))
		वापस -EINVAL;

	अगर (skb_is_nonlinear(skb) &&
	    skb_shinfo(skb)->nr_frags > IWL_TRANS_MAX_FRAGS(trans) &&
	    __skb_linearize(skb))
		वापस -ENOMEM;

	/* mac80211 always माला_दो the full header पूर्णांकo the SKB's head,
	 * so there's no need to check if it's पढ़ोable there
	 */
	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	fc = hdr->frame_control;
	hdr_len = ieee80211_hdrlen(fc);

	spin_lock(&txq->lock);

	अगर (iwl_txq_space(trans, txq) < txq->high_mark) अणु
		iwl_txq_stop(trans, txq);

		/* करोn't put the packet on the ring, अगर there is no room */
		अगर (unlikely(iwl_txq_space(trans, txq) < 3)) अणु
			काष्ठा iwl_device_tx_cmd **dev_cmd_ptr;

			dev_cmd_ptr = (व्योम *)((u8 *)skb->cb +
					       trans->txqs.dev_cmd_offs);

			*dev_cmd_ptr = dev_cmd;
			__skb_queue_tail(&txq->overflow_q, skb);

			spin_unlock(&txq->lock);
			वापस 0;
		पूर्ण
	पूर्ण

	/* In AGG mode, the index in the ring must correspond to the WiFi
	 * sequence number. This is a HW requirements to help the SCD to parse
	 * the BA.
	 * Check here that the packets are in the right place on the ring.
	 */
	wअगरi_seq = IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));
	WARN_ONCE(txq->ampdu &&
		  (wअगरi_seq & 0xff) != txq->ग_लिखो_ptr,
		  "Q: %d WiFi Seq %d tfdNum %d",
		  txq_id, wअगरi_seq, txq->ग_लिखो_ptr);

	/* Set up driver data क्रम this TFD */
	txq->entries[txq->ग_लिखो_ptr].skb = skb;
	txq->entries[txq->ग_लिखो_ptr].cmd = dev_cmd;

	dev_cmd->hdr.sequence =
		cpu_to_le16((u16)(QUEUE_TO_SEQ(txq_id) |
			    INDEX_TO_SEQ(txq->ग_लिखो_ptr)));

	tb0_phys = iwl_txq_get_first_tb_dma(txq, txq->ग_लिखो_ptr);
	scratch_phys = tb0_phys + माप(काष्ठा iwl_cmd_header) +
		       दुरत्व(काष्ठा iwl_tx_cmd, scratch);

	tx_cmd->dram_lsb_ptr = cpu_to_le32(scratch_phys);
	tx_cmd->dram_msb_ptr = iwl_get_dma_hi_addr(scratch_phys);

	/* Set up first empty entry in queue's array of Tx/cmd buffers */
	out_meta = &txq->entries[txq->ग_लिखो_ptr].meta;
	out_meta->flags = 0;

	/*
	 * The second TB (tb1) poपूर्णांकs to the reमुख्यder of the TX command
	 * and the 802.11 header - dword aligned size
	 * (This calculation modअगरies the TX command, so करो it beक्रमe the
	 * setup of the first TB)
	 */
	len = माप(काष्ठा iwl_tx_cmd) + माप(काष्ठा iwl_cmd_header) +
	      hdr_len - IWL_FIRST_TB_SIZE;
	/* करो not align A-MSDU to dword as the subframe header aligns it */
	amsdu = ieee80211_is_data_qos(fc) &&
		(*ieee80211_get_qos_ctl(hdr) &
		 IEEE80211_QOS_CTL_A_MSDU_PRESENT);
	अगर (!amsdu) अणु
		tb1_len = ALIGN(len, 4);
		/* Tell NIC about any 2-byte padding after MAC header */
		अगर (tb1_len != len)
			tx_cmd->tx_flags |= cpu_to_le32(TX_CMD_FLG_MH_PAD);
	पूर्ण अन्यथा अणु
		tb1_len = len;
	पूर्ण

	/*
	 * The first TB poपूर्णांकs to bi-directional DMA data, we'll
	 * स_नकल the data पूर्णांकo it later.
	 */
	iwl_pcie_txq_build_tfd(trans, txq, tb0_phys,
			       IWL_FIRST_TB_SIZE, true);

	/* there must be data left over क्रम TB1 or this code must be changed */
	BUILD_BUG_ON(माप(काष्ठा iwl_tx_cmd) < IWL_FIRST_TB_SIZE);

	/* map the data क्रम TB1 */
	tb1_addr = ((u8 *)&dev_cmd->hdr) + IWL_FIRST_TB_SIZE;
	tb1_phys = dma_map_single(trans->dev, tb1_addr, tb1_len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(trans->dev, tb1_phys)))
		जाओ out_err;
	iwl_pcie_txq_build_tfd(trans, txq, tb1_phys, tb1_len, false);

	trace_iwlwअगरi_dev_tx(trans->dev, skb,
			     iwl_txq_get_tfd(trans, txq, txq->ग_लिखो_ptr),
			     trans->txqs.tfd.size,
			     &dev_cmd->hdr, IWL_FIRST_TB_SIZE + tb1_len,
			     hdr_len);

	/*
	 * If gso_size wasn't set, don't give the frame "amsdu treatment"
	 * (adding subframes, etc.).
	 * This can happen in some testing flows when the amsdu was alपढ़ोy
	 * pre-built, and we just need to send the resulting skb.
	 */
	अगर (amsdu && skb_shinfo(skb)->gso_size) अणु
		अगर (unlikely(iwl_fill_data_tbs_amsdu(trans, skb, txq, hdr_len,
						     out_meta, dev_cmd,
						     tb1_len)))
			जाओ out_err;
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *frag;

		अगर (unlikely(iwl_fill_data_tbs(trans, skb, txq, hdr_len,
					       out_meta)))
			जाओ out_err;

		skb_walk_frags(skb, frag) अणु
			अगर (unlikely(iwl_fill_data_tbs(trans, frag, txq, 0,
						       out_meta)))
				जाओ out_err;
		पूर्ण
	पूर्ण

	/* building the A-MSDU might have changed this data, so स_नकल it now */
	स_नकल(&txq->first_tb_bufs[txq->ग_लिखो_ptr], dev_cmd, IWL_FIRST_TB_SIZE);

	tfd = iwl_txq_get_tfd(trans, txq, txq->ग_लिखो_ptr);
	/* Set up entry क्रम this TFD in Tx byte-count array */
	iwl_txq_gen1_update_byte_cnt_tbl(trans, txq, le16_to_cpu(tx_cmd->len),
					 iwl_txq_gen1_tfd_get_num_tbs(trans,
								      tfd));

	रुको_ग_लिखो_ptr = ieee80211_has_morefrags(fc);

	/* start समयr अगर queue currently empty */
	अगर (txq->पढ़ो_ptr == txq->ग_लिखो_ptr && txq->wd_समयout) अणु
		/*
		 * If the TXQ is active, then set the समयr, अगर not,
		 * set the समयr in reमुख्यder so that the समयr will
		 * be armed with the right value when the station will
		 * wake up.
		 */
		अगर (!txq->frozen)
			mod_समयr(&txq->stuck_समयr,
				  jअगरfies + txq->wd_समयout);
		अन्यथा
			txq->frozen_expiry_reमुख्यder = txq->wd_समयout;
	पूर्ण

	/* Tell device the ग_लिखो index *just past* this latest filled TFD */
	txq->ग_लिखो_ptr = iwl_txq_inc_wrap(trans, txq->ग_लिखो_ptr);
	अगर (!रुको_ग_लिखो_ptr)
		iwl_pcie_txq_inc_wr_ptr(trans, txq);

	/*
	 * At this poपूर्णांक the frame is "transmitted" successfully
	 * and we will get a TX status notअगरication eventually.
	 */
	spin_unlock(&txq->lock);
	वापस 0;
out_err:
	iwl_txq_gen1_tfd_unmap(trans, out_meta, txq, txq->ग_लिखो_ptr);
	spin_unlock(&txq->lock);
	वापस -1;
पूर्ण
