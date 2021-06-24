<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2003-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/gfp.h>

#समावेश "iwl-prph.h"
#समावेश "iwl-io.h"
#समावेश "internal.h"
#समावेश "iwl-op-mode.h"
#समावेश "iwl-context-info-gen3.h"

/******************************************************************************
 *
 * RX path functions
 *
 ******************************************************************************/

/*
 * Rx theory of operation
 *
 * Driver allocates a circular buffer of Receive Buffer Descriptors (RBDs),
 * each of which poपूर्णांक to Receive Buffers to be filled by the NIC.  These get
 * used not only क्रम Rx frames, but क्रम any command response or notअगरication
 * from the NIC.  The driver and NIC manage the Rx buffers by means
 * of indexes पूर्णांकo the circular buffer.
 *
 * Rx Queue Indexes
 * The host/firmware share two index रेजिस्टरs क्रम managing the Rx buffers.
 *
 * The READ index maps to the first position that the firmware may be writing
 * to -- the driver can पढ़ो up to (but not including) this position and get
 * good data.
 * The READ index is managed by the firmware once the card is enabled.
 *
 * The WRITE index maps to the last position the driver has पढ़ो from -- the
 * position preceding WRITE is the last slot the firmware can place a packet.
 *
 * The queue is empty (no good data) अगर WRITE = READ - 1, and is full अगर
 * WRITE = READ.
 *
 * During initialization, the host sets up the READ queue position to the first
 * INDEX position, and WRITE to the last (READ - 1 wrapped)
 *
 * When the firmware places a packet in a buffer, it will advance the READ index
 * and fire the RX पूर्णांकerrupt.  The driver can then query the READ index and
 * process as many packets as possible, moving the WRITE index क्रमward as it
 * resets the Rx queue buffers with new memory.
 *
 * The management in the driver is as follows:
 * + A list of pre-allocated RBDs is stored in iwl->rxq->rx_मुक्त.
 *   When the पूर्णांकerrupt handler is called, the request is processed.
 *   The page is either stolen - transferred to the upper layer
 *   or reused - added immediately to the iwl->rxq->rx_मुक्त list.
 * + When the page is stolen - the driver updates the matching queue's used
 *   count, detaches the RBD and transfers it to the queue used list.
 *   When there are two used RBDs - they are transferred to the allocator empty
 *   list. Work is then scheduled क्रम the allocator to start allocating
 *   eight buffers.
 *   When there are another 6 used RBDs - they are transferred to the allocator
 *   empty list and the driver tries to claim the pre-allocated buffers and
 *   add them to iwl->rxq->rx_मुक्त. If it fails - it जारीs to claim them
 *   until पढ़ोy.
 *   When there are 8+ buffers in the मुक्त list - either from allocation or from
 *   8 reused unstolen pages - restock is called to update the FW and indexes.
 * + In order to make sure the allocator always has RBDs to use क्रम allocation
 *   the allocator has initial pool in the size of num_queues*(8-2) - the
 *   maximum missing RBDs per allocation request (request posted with 2
 *    empty RBDs, there is no guarantee when the other 6 RBDs are supplied).
 *   The queues supplies the recycle of the rest of the RBDs.
 * + A received packet is processed and handed to the kernel network stack,
 *   detached from the iwl->rxq.  The driver 'processed' index is updated.
 * + If there are no allocated buffers in iwl->rxq->rx_मुक्त,
 *   the READ INDEX is not incremented and iwl->status(RX_STALLED) is set.
 *   If there were enough मुक्त buffers and RX_STALLED is set it is cleared.
 *
 *
 * Driver sequence:
 *
 * iwl_rxq_alloc()            Allocates rx_मुक्त
 * iwl_pcie_rx_replenish()    Replenishes rx_मुक्त list from rx_used, and calls
 *                            iwl_pcie_rxq_restock.
 *                            Used only during initialization.
 * iwl_pcie_rxq_restock()     Moves available buffers from rx_मुक्त पूर्णांकo Rx
 *                            queue, updates firmware poपूर्णांकers, and updates
 *                            the WRITE index.
 * iwl_pcie_rx_allocator()     Background work क्रम allocating pages.
 *
 * -- enable पूर्णांकerrupts --
 * ISR - iwl_rx()             Detach iwl_rx_mem_buffers from pool up to the
 *                            READ INDEX, detaching the SKB from the pool.
 *                            Moves the packet buffer from queue to rx_used.
 *                            Posts and claims requests to the allocator.
 *                            Calls iwl_pcie_rxq_restock to refill any empty
 *                            slots.
 *
 * RBD lअगरe-cycle:
 *
 * Init:
 * rxq.pool -> rxq.rx_used -> rxq.rx_मुक्त -> rxq.queue
 *
 * Regular Receive पूर्णांकerrupt:
 * Page Stolen:
 * rxq.queue -> rxq.rx_used -> allocator.rbd_empty ->
 * allocator.rbd_allocated -> rxq.rx_मुक्त -> rxq.queue
 * Page not Stolen:
 * rxq.queue -> rxq.rx_मुक्त -> rxq.queue
 * ...
 *
 */

/*
 * iwl_rxq_space - Return number of मुक्त slots available in queue.
 */
अटल पूर्णांक iwl_rxq_space(स्थिर काष्ठा iwl_rxq *rxq)
अणु
	/* Make sure rx queue size is a घातer of 2 */
	WARN_ON(rxq->queue_size & (rxq->queue_size - 1));

	/*
	 * There can be up to (RX_QUEUE_SIZE - 1) मुक्त slots, to aव्योम ambiguity
	 * between empty and completely full queues.
	 * The following is equivalent to modulo by RX_QUEUE_SIZE and is well
	 * defined क्रम negative भागidends.
	 */
	वापस (rxq->पढ़ो - rxq->ग_लिखो - 1) & (rxq->queue_size - 1);
पूर्ण

/*
 * iwl_dma_addr2rbd_ptr - convert a DMA address to a uCode पढ़ो buffer ptr
 */
अटल अंतरभूत __le32 iwl_pcie_dma_addr2rbd_ptr(dma_addr_t dma_addr)
अणु
	वापस cpu_to_le32((u32)(dma_addr >> 8));
पूर्ण

/*
 * iwl_pcie_rx_stop - stops the Rx DMA
 */
पूर्णांक iwl_pcie_rx_stop(काष्ठा iwl_trans *trans)
अणु
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		/* TODO: हटाओ this once fw करोes it */
		iwl_ग_लिखो_umac_prph(trans, RFH_RXF_DMA_CFG_GEN3, 0);
		वापस iwl_poll_umac_prph_bit(trans, RFH_GEN_STATUS_GEN3,
					      RXF_DMA_IDLE, RXF_DMA_IDLE, 1000);
	पूर्ण अन्यथा अगर (trans->trans_cfg->mq_rx_supported) अणु
		iwl_ग_लिखो_prph(trans, RFH_RXF_DMA_CFG, 0);
		वापस iwl_poll_prph_bit(trans, RFH_GEN_STATUS,
					   RXF_DMA_IDLE, RXF_DMA_IDLE, 1000);
	पूर्ण अन्यथा अणु
		iwl_ग_लिखो_direct32(trans, FH_MEM_RCSR_CHNL0_CONFIG_REG, 0);
		वापस iwl_poll_direct_bit(trans, FH_MEM_RSSR_RX_STATUS_REG,
					   FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
					   1000);
	पूर्ण
पूर्ण

/*
 * iwl_pcie_rxq_inc_wr_ptr - Update the ग_लिखो poपूर्णांकer क्रम the RX queue
 */
अटल व्योम iwl_pcie_rxq_inc_wr_ptr(काष्ठा iwl_trans *trans,
				    काष्ठा iwl_rxq *rxq)
अणु
	u32 reg;

	lockdep_निश्चित_held(&rxq->lock);

	/*
	 * explicitly wake up the NIC अगर:
	 * 1. shaकरोw रेजिस्टरs aren't enabled
	 * 2. there is a chance that the NIC is asleep
	 */
	अगर (!trans->trans_cfg->base_params->shaकरोw_reg_enable &&
	    test_bit(STATUS_TPOWER_PMI, &trans->status)) अणु
		reg = iwl_पढ़ो32(trans, CSR_UCODE_DRV_GP1);

		अगर (reg & CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP) अणु
			IWL_DEBUG_INFO(trans, "Rx queue requesting wakeup, GP1 = 0x%x\n",
				       reg);
			iwl_set_bit(trans, CSR_GP_CNTRL,
				    CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
			rxq->need_update = true;
			वापस;
		पूर्ण
	पूर्ण

	rxq->ग_लिखो_actual = round_करोwn(rxq->ग_लिखो, 8);
	अगर (trans->trans_cfg->mq_rx_supported)
		iwl_ग_लिखो32(trans, RFH_Q_FRBDCB_WIDX_TRG(rxq->id),
			    rxq->ग_लिखो_actual);
	अन्यथा
		iwl_ग_लिखो32(trans, FH_RSCSR_CHNL0_WPTR, rxq->ग_लिखो_actual);
पूर्ण

अटल व्योम iwl_pcie_rxq_check_wrptr(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक i;

	क्रम (i = 0; i < trans->num_rx_queues; i++) अणु
		काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[i];

		अगर (!rxq->need_update)
			जारी;
		spin_lock_bh(&rxq->lock);
		iwl_pcie_rxq_inc_wr_ptr(trans, rxq);
		rxq->need_update = false;
		spin_unlock_bh(&rxq->lock);
	पूर्ण
पूर्ण

अटल व्योम iwl_pcie_restock_bd(काष्ठा iwl_trans *trans,
				काष्ठा iwl_rxq *rxq,
				काष्ठा iwl_rx_mem_buffer *rxb)
अणु
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		काष्ठा iwl_rx_transfer_desc *bd = rxq->bd;

		BUILD_BUG_ON(माप(*bd) != 2 * माप(u64));

		bd[rxq->ग_लिखो].addr = cpu_to_le64(rxb->page_dma);
		bd[rxq->ग_लिखो].rbid = cpu_to_le16(rxb->vid);
	पूर्ण अन्यथा अणु
		__le64 *bd = rxq->bd;

		bd[rxq->ग_लिखो] = cpu_to_le64(rxb->page_dma | rxb->vid);
	पूर्ण

	IWL_DEBUG_RX(trans, "Assigned virtual RB ID %u to queue %d index %d\n",
		     (u32)rxb->vid, rxq->id, rxq->ग_लिखो);
पूर्ण

/*
 * iwl_pcie_rxmq_restock - restock implementation क्रम multi-queue rx
 */
अटल व्योम iwl_pcie_rxmq_restock(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_rxq *rxq)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rx_mem_buffer *rxb;

	/*
	 * If the device isn't enabled - no need to try to add buffers...
	 * This can happen when we stop the device and still have an पूर्णांकerrupt
	 * pending. We stop the APM beक्रमe we sync the पूर्णांकerrupts because we
	 * have to (see comment there). On the other hand, since the APM is
	 * stopped, we cannot access the HW (in particular not prph).
	 * So करोn't try to restock अगर the APM has been alपढ़ोy stopped.
	 */
	अगर (!test_bit(STATUS_DEVICE_ENABLED, &trans->status))
		वापस;

	spin_lock_bh(&rxq->lock);
	जबतक (rxq->मुक्त_count) अणु
		/* Get next मुक्त Rx buffer, हटाओ from मुक्त list */
		rxb = list_first_entry(&rxq->rx_मुक्त, काष्ठा iwl_rx_mem_buffer,
				       list);
		list_del(&rxb->list);
		rxb->invalid = false;
		/* some low bits are expected to be unset (depending on hw) */
		WARN_ON(rxb->page_dma & trans_pcie->supported_dma_mask);
		/* Poपूर्णांक to Rx buffer via next RBD in circular buffer */
		iwl_pcie_restock_bd(trans, rxq, rxb);
		rxq->ग_लिखो = (rxq->ग_लिखो + 1) & (rxq->queue_size - 1);
		rxq->मुक्त_count--;
	पूर्ण
	spin_unlock_bh(&rxq->lock);

	/*
	 * If we've added more space क्रम the firmware to place data, tell it.
	 * Increment device's ग_लिखो poपूर्णांकer in multiples of 8.
	 */
	अगर (rxq->ग_लिखो_actual != (rxq->ग_लिखो & ~0x7)) अणु
		spin_lock_bh(&rxq->lock);
		iwl_pcie_rxq_inc_wr_ptr(trans, rxq);
		spin_unlock_bh(&rxq->lock);
	पूर्ण
पूर्ण

/*
 * iwl_pcie_rxsq_restock - restock implementation क्रम single queue rx
 */
अटल व्योम iwl_pcie_rxsq_restock(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_rxq *rxq)
अणु
	काष्ठा iwl_rx_mem_buffer *rxb;

	/*
	 * If the device isn't enabled - not need to try to add buffers...
	 * This can happen when we stop the device and still have an पूर्णांकerrupt
	 * pending. We stop the APM beक्रमe we sync the पूर्णांकerrupts because we
	 * have to (see comment there). On the other hand, since the APM is
	 * stopped, we cannot access the HW (in particular not prph).
	 * So करोn't try to restock अगर the APM has been alपढ़ोy stopped.
	 */
	अगर (!test_bit(STATUS_DEVICE_ENABLED, &trans->status))
		वापस;

	spin_lock_bh(&rxq->lock);
	जबतक ((iwl_rxq_space(rxq) > 0) && (rxq->मुक्त_count)) अणु
		__le32 *bd = (__le32 *)rxq->bd;
		/* The overwritten rxb must be a used one */
		rxb = rxq->queue[rxq->ग_लिखो];
		BUG_ON(rxb && rxb->page);

		/* Get next मुक्त Rx buffer, हटाओ from मुक्त list */
		rxb = list_first_entry(&rxq->rx_मुक्त, काष्ठा iwl_rx_mem_buffer,
				       list);
		list_del(&rxb->list);
		rxb->invalid = false;

		/* Poपूर्णांक to Rx buffer via next RBD in circular buffer */
		bd[rxq->ग_लिखो] = iwl_pcie_dma_addr2rbd_ptr(rxb->page_dma);
		rxq->queue[rxq->ग_लिखो] = rxb;
		rxq->ग_लिखो = (rxq->ग_लिखो + 1) & RX_QUEUE_MASK;
		rxq->मुक्त_count--;
	पूर्ण
	spin_unlock_bh(&rxq->lock);

	/* If we've added more space क्रम the firmware to place data, tell it.
	 * Increment device's ग_लिखो poपूर्णांकer in multiples of 8. */
	अगर (rxq->ग_लिखो_actual != (rxq->ग_लिखो & ~0x7)) अणु
		spin_lock_bh(&rxq->lock);
		iwl_pcie_rxq_inc_wr_ptr(trans, rxq);
		spin_unlock_bh(&rxq->lock);
	पूर्ण
पूर्ण

/*
 * iwl_pcie_rxq_restock - refill RX queue from pre-allocated pool
 *
 * If there are slots in the RX queue that need to be restocked,
 * and we have मुक्त pre-allocated buffers, fill the ranks as much
 * as we can, pulling from rx_मुक्त.
 *
 * This moves the 'write' index forward to catch up with 'processed', and
 * also updates the memory address in the firmware to reference the new
 * target buffer.
 */
अटल
व्योम iwl_pcie_rxq_restock(काष्ठा iwl_trans *trans, काष्ठा iwl_rxq *rxq)
अणु
	अगर (trans->trans_cfg->mq_rx_supported)
		iwl_pcie_rxmq_restock(trans, rxq);
	अन्यथा
		iwl_pcie_rxsq_restock(trans, rxq);
पूर्ण

/*
 * iwl_pcie_rx_alloc_page - allocates and वापसs a page.
 *
 */
अटल काष्ठा page *iwl_pcie_rx_alloc_page(काष्ठा iwl_trans *trans,
					   u32 *offset, gfp_t priority)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	अचिन्हित पूर्णांक rbsize = iwl_trans_get_rb_size(trans_pcie->rx_buf_size);
	अचिन्हित पूर्णांक allocsize = PAGE_SIZE << trans_pcie->rx_page_order;
	काष्ठा page *page;
	gfp_t gfp_mask = priority;

	अगर (trans_pcie->rx_page_order > 0)
		gfp_mask |= __GFP_COMP;

	अगर (trans_pcie->alloc_page) अणु
		spin_lock_bh(&trans_pcie->alloc_page_lock);
		/* recheck */
		अगर (trans_pcie->alloc_page) अणु
			*offset = trans_pcie->alloc_page_used;
			page = trans_pcie->alloc_page;
			trans_pcie->alloc_page_used += rbsize;
			अगर (trans_pcie->alloc_page_used >= allocsize)
				trans_pcie->alloc_page = शून्य;
			अन्यथा
				get_page(page);
			spin_unlock_bh(&trans_pcie->alloc_page_lock);
			वापस page;
		पूर्ण
		spin_unlock_bh(&trans_pcie->alloc_page_lock);
	पूर्ण

	/* Alloc a new receive buffer */
	page = alloc_pages(gfp_mask, trans_pcie->rx_page_order);
	अगर (!page) अणु
		अगर (net_ratelimit())
			IWL_DEBUG_INFO(trans, "alloc_pages failed, order: %d\n",
				       trans_pcie->rx_page_order);
		/*
		 * Issue an error अगर we करोn't have enough pre-allocated
		  * buffers.
		 */
		अगर (!(gfp_mask & __GFP_NOWARN) && net_ratelimit())
			IWL_CRIT(trans,
				 "Failed to alloc_pages\n");
		वापस शून्य;
	पूर्ण

	अगर (2 * rbsize <= allocsize) अणु
		spin_lock_bh(&trans_pcie->alloc_page_lock);
		अगर (!trans_pcie->alloc_page) अणु
			get_page(page);
			trans_pcie->alloc_page = page;
			trans_pcie->alloc_page_used = rbsize;
		पूर्ण
		spin_unlock_bh(&trans_pcie->alloc_page_lock);
	पूर्ण

	*offset = 0;
	वापस page;
पूर्ण

/*
 * iwl_pcie_rxq_alloc_rbs - allocate a page क्रम each used RBD
 *
 * A used RBD is an Rx buffer that has been given to the stack. To use it again
 * a page must be allocated and the RBD must poपूर्णांक to the page. This function
 * करोesn't change the HW poपूर्णांकer but handles the list of pages that is used by
 * iwl_pcie_rxq_restock. The latter function will update the HW to use the newly
 * allocated buffers.
 */
व्योम iwl_pcie_rxq_alloc_rbs(काष्ठा iwl_trans *trans, gfp_t priority,
			    काष्ठा iwl_rxq *rxq)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rx_mem_buffer *rxb;
	काष्ठा page *page;

	जबतक (1) अणु
		अचिन्हित पूर्णांक offset;

		spin_lock_bh(&rxq->lock);
		अगर (list_empty(&rxq->rx_used)) अणु
			spin_unlock_bh(&rxq->lock);
			वापस;
		पूर्ण
		spin_unlock_bh(&rxq->lock);

		page = iwl_pcie_rx_alloc_page(trans, &offset, priority);
		अगर (!page)
			वापस;

		spin_lock_bh(&rxq->lock);

		अगर (list_empty(&rxq->rx_used)) अणु
			spin_unlock_bh(&rxq->lock);
			__मुक्त_pages(page, trans_pcie->rx_page_order);
			वापस;
		पूर्ण
		rxb = list_first_entry(&rxq->rx_used, काष्ठा iwl_rx_mem_buffer,
				       list);
		list_del(&rxb->list);
		spin_unlock_bh(&rxq->lock);

		BUG_ON(rxb->page);
		rxb->page = page;
		rxb->offset = offset;
		/* Get physical address of the RB */
		rxb->page_dma =
			dma_map_page(trans->dev, page, rxb->offset,
				     trans_pcie->rx_buf_bytes,
				     DMA_FROM_DEVICE);
		अगर (dma_mapping_error(trans->dev, rxb->page_dma)) अणु
			rxb->page = शून्य;
			spin_lock_bh(&rxq->lock);
			list_add(&rxb->list, &rxq->rx_used);
			spin_unlock_bh(&rxq->lock);
			__मुक्त_pages(page, trans_pcie->rx_page_order);
			वापस;
		पूर्ण

		spin_lock_bh(&rxq->lock);

		list_add_tail(&rxb->list, &rxq->rx_मुक्त);
		rxq->मुक्त_count++;

		spin_unlock_bh(&rxq->lock);
	पूर्ण
पूर्ण

व्योम iwl_pcie_मुक्त_rbs_pool(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक i;

	क्रम (i = 0; i < RX_POOL_SIZE(trans_pcie->num_rx_bufs); i++) अणु
		अगर (!trans_pcie->rx_pool[i].page)
			जारी;
		dma_unmap_page(trans->dev, trans_pcie->rx_pool[i].page_dma,
			       trans_pcie->rx_buf_bytes, DMA_FROM_DEVICE);
		__मुक्त_pages(trans_pcie->rx_pool[i].page,
			     trans_pcie->rx_page_order);
		trans_pcie->rx_pool[i].page = शून्य;
	पूर्ण
पूर्ण

/*
 * iwl_pcie_rx_allocator - Allocates pages in the background क्रम RX queues
 *
 * Allocates क्रम each received request 8 pages
 * Called as a scheduled work item.
 */
अटल व्योम iwl_pcie_rx_allocator(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rb_allocator *rba = &trans_pcie->rba;
	काष्ठा list_head local_empty;
	पूर्णांक pending = atomic_पढ़ो(&rba->req_pending);

	IWL_DEBUG_TPT(trans, "Pending allocation requests = %d\n", pending);

	/* If we were scheduled - there is at least one request */
	spin_lock_bh(&rba->lock);
	/* swap out the rba->rbd_empty to a local list */
	list_replace_init(&rba->rbd_empty, &local_empty);
	spin_unlock_bh(&rba->lock);

	जबतक (pending) अणु
		पूर्णांक i;
		LIST_HEAD(local_allocated);
		gfp_t gfp_mask = GFP_KERNEL;

		/* Do not post a warning अगर there are only a few requests */
		अगर (pending < RX_PENDING_WATERMARK)
			gfp_mask |= __GFP_NOWARN;

		क्रम (i = 0; i < RX_CLAIM_REQ_ALLOC;) अणु
			काष्ठा iwl_rx_mem_buffer *rxb;
			काष्ठा page *page;

			/* List should never be empty - each reused RBD is
			 * वापसed to the list, and initial pool covers any
			 * possible gap between the समय the page is allocated
			 * to the समय the RBD is added.
			 */
			BUG_ON(list_empty(&local_empty));
			/* Get the first rxb from the rbd list */
			rxb = list_first_entry(&local_empty,
					       काष्ठा iwl_rx_mem_buffer, list);
			BUG_ON(rxb->page);

			/* Alloc a new receive buffer */
			page = iwl_pcie_rx_alloc_page(trans, &rxb->offset,
						      gfp_mask);
			अगर (!page)
				जारी;
			rxb->page = page;

			/* Get physical address of the RB */
			rxb->page_dma = dma_map_page(trans->dev, page,
						     rxb->offset,
						     trans_pcie->rx_buf_bytes,
						     DMA_FROM_DEVICE);
			अगर (dma_mapping_error(trans->dev, rxb->page_dma)) अणु
				rxb->page = शून्य;
				__मुक्त_pages(page, trans_pcie->rx_page_order);
				जारी;
			पूर्ण

			/* move the allocated entry to the out list */
			list_move(&rxb->list, &local_allocated);
			i++;
		पूर्ण

		atomic_dec(&rba->req_pending);
		pending--;

		अगर (!pending) अणु
			pending = atomic_पढ़ो(&rba->req_pending);
			अगर (pending)
				IWL_DEBUG_TPT(trans,
					      "Got more pending allocation requests = %d\n",
					      pending);
		पूर्ण

		spin_lock_bh(&rba->lock);
		/* add the allocated rbds to the allocator allocated list */
		list_splice_tail(&local_allocated, &rba->rbd_allocated);
		/* get more empty RBDs क्रम current pending requests */
		list_splice_tail_init(&rba->rbd_empty, &local_empty);
		spin_unlock_bh(&rba->lock);

		atomic_inc(&rba->req_पढ़ोy);

	पूर्ण

	spin_lock_bh(&rba->lock);
	/* वापस unused rbds to the allocator empty list */
	list_splice_tail(&local_empty, &rba->rbd_empty);
	spin_unlock_bh(&rba->lock);

	IWL_DEBUG_TPT(trans, "%s, exit.\n", __func__);
पूर्ण

/*
 * iwl_pcie_rx_allocator_get - वापसs the pre-allocated pages
.*
.* Called by queue when the queue posted allocation request and
 * has मुक्तd 8 RBDs in order to restock itself.
 * This function directly moves the allocated RBs to the queue's ownership
 * and updates the relevant counters.
 */
अटल व्योम iwl_pcie_rx_allocator_get(काष्ठा iwl_trans *trans,
				      काष्ठा iwl_rxq *rxq)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rb_allocator *rba = &trans_pcie->rba;
	पूर्णांक i;

	lockdep_निश्चित_held(&rxq->lock);

	/*
	 * atomic_dec_अगर_positive वापसs req_पढ़ोy - 1 क्रम any scenario.
	 * If req_पढ़ोy is 0 atomic_dec_अगर_positive will वापस -1 and this
	 * function will वापस early, as there are no पढ़ोy requests.
	 * atomic_dec_अगर_positive will perofrm the *actual* decrement only अगर
	 * req_पढ़ोy > 0, i.e. - there are पढ़ोy requests and the function
	 * hands one request to the caller.
	 */
	अगर (atomic_dec_अगर_positive(&rba->req_पढ़ोy) < 0)
		वापस;

	spin_lock(&rba->lock);
	क्रम (i = 0; i < RX_CLAIM_REQ_ALLOC; i++) अणु
		/* Get next मुक्त Rx buffer, हटाओ it from मुक्त list */
		काष्ठा iwl_rx_mem_buffer *rxb =
			list_first_entry(&rba->rbd_allocated,
					 काष्ठा iwl_rx_mem_buffer, list);

		list_move(&rxb->list, &rxq->rx_मुक्त);
	पूर्ण
	spin_unlock(&rba->lock);

	rxq->used_count -= RX_CLAIM_REQ_ALLOC;
	rxq->मुक्त_count += RX_CLAIM_REQ_ALLOC;
पूर्ण

व्योम iwl_pcie_rx_allocator_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा iwl_rb_allocator *rba_p =
		container_of(data, काष्ठा iwl_rb_allocator, rx_alloc);
	काष्ठा iwl_trans_pcie *trans_pcie =
		container_of(rba_p, काष्ठा iwl_trans_pcie, rba);

	iwl_pcie_rx_allocator(trans_pcie->trans);
पूर्ण

अटल पूर्णांक iwl_pcie_मुक्त_bd_size(काष्ठा iwl_trans *trans, bool use_rx_td)
अणु
	काष्ठा iwl_rx_transfer_desc *rx_td;

	अगर (use_rx_td)
		वापस माप(*rx_td);
	अन्यथा
		वापस trans->trans_cfg->mq_rx_supported ? माप(__le64) :
			माप(__le32);
पूर्ण

अटल व्योम iwl_pcie_मुक्त_rxq_dma(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_rxq *rxq)
अणु
	काष्ठा device *dev = trans->dev;
	bool use_rx_td = (trans->trans_cfg->device_family >=
			  IWL_DEVICE_FAMILY_AX210);
	पूर्णांक मुक्त_size = iwl_pcie_मुक्त_bd_size(trans, use_rx_td);

	अगर (rxq->bd)
		dma_मुक्त_coherent(trans->dev,
				  मुक्त_size * rxq->queue_size,
				  rxq->bd, rxq->bd_dma);
	rxq->bd_dma = 0;
	rxq->bd = शून्य;

	rxq->rb_stts_dma = 0;
	rxq->rb_stts = शून्य;

	अगर (rxq->used_bd)
		dma_मुक्त_coherent(trans->dev,
				  (use_rx_td ? माप(*rxq->cd) :
				   माप(__le32)) * rxq->queue_size,
				  rxq->used_bd, rxq->used_bd_dma);
	rxq->used_bd_dma = 0;
	rxq->used_bd = शून्य;

	अगर (trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_AX210)
		वापस;

	अगर (rxq->tr_tail)
		dma_मुक्त_coherent(dev, माप(__le16),
				  rxq->tr_tail, rxq->tr_tail_dma);
	rxq->tr_tail_dma = 0;
	rxq->tr_tail = शून्य;

	अगर (rxq->cr_tail)
		dma_मुक्त_coherent(dev, माप(__le16),
				  rxq->cr_tail, rxq->cr_tail_dma);
	rxq->cr_tail_dma = 0;
	rxq->cr_tail = शून्य;
पूर्ण

अटल पूर्णांक iwl_pcie_alloc_rxq_dma(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_rxq *rxq)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा device *dev = trans->dev;
	पूर्णांक i;
	पूर्णांक मुक्त_size;
	bool use_rx_td = (trans->trans_cfg->device_family >=
			  IWL_DEVICE_FAMILY_AX210);
	माप_प्रकार rb_stts_size = use_rx_td ? माप(__le16) :
			      माप(काष्ठा iwl_rb_status);

	spin_lock_init(&rxq->lock);
	अगर (trans->trans_cfg->mq_rx_supported)
		rxq->queue_size = trans->cfg->num_rbds;
	अन्यथा
		rxq->queue_size = RX_QUEUE_SIZE;

	मुक्त_size = iwl_pcie_मुक्त_bd_size(trans, use_rx_td);

	/*
	 * Allocate the circular buffer of Read Buffer Descriptors
	 * (RBDs)
	 */
	rxq->bd = dma_alloc_coherent(dev, मुक्त_size * rxq->queue_size,
				     &rxq->bd_dma, GFP_KERNEL);
	अगर (!rxq->bd)
		जाओ err;

	अगर (trans->trans_cfg->mq_rx_supported) अणु
		rxq->used_bd = dma_alloc_coherent(dev,
						  (use_rx_td ? माप(*rxq->cd) : माप(__le32)) * rxq->queue_size,
						  &rxq->used_bd_dma,
						  GFP_KERNEL);
		अगर (!rxq->used_bd)
			जाओ err;
	पूर्ण

	rxq->rb_stts = trans_pcie->base_rb_stts + rxq->id * rb_stts_size;
	rxq->rb_stts_dma =
		trans_pcie->base_rb_stts_dma + rxq->id * rb_stts_size;

	अगर (!use_rx_td)
		वापस 0;

	/* Allocate the driver's poपूर्णांकer to TR tail */
	rxq->tr_tail = dma_alloc_coherent(dev, माप(__le16),
					  &rxq->tr_tail_dma, GFP_KERNEL);
	अगर (!rxq->tr_tail)
		जाओ err;

	/* Allocate the driver's poपूर्णांकer to CR tail */
	rxq->cr_tail = dma_alloc_coherent(dev, माप(__le16),
					  &rxq->cr_tail_dma, GFP_KERNEL);
	अगर (!rxq->cr_tail)
		जाओ err;

	वापस 0;

err:
	क्रम (i = 0; i < trans->num_rx_queues; i++) अणु
		काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[i];

		iwl_pcie_मुक्त_rxq_dma(trans, rxq);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक iwl_pcie_rx_alloc(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rb_allocator *rba = &trans_pcie->rba;
	पूर्णांक i, ret;
	माप_प्रकार rb_stts_size = trans->trans_cfg->device_family >=
				IWL_DEVICE_FAMILY_AX210 ?
			      माप(__le16) : माप(काष्ठा iwl_rb_status);

	अगर (WARN_ON(trans_pcie->rxq))
		वापस -EINVAL;

	trans_pcie->rxq = kसुस्मृति(trans->num_rx_queues, माप(काष्ठा iwl_rxq),
				  GFP_KERNEL);
	trans_pcie->rx_pool = kसुस्मृति(RX_POOL_SIZE(trans_pcie->num_rx_bufs),
				      माप(trans_pcie->rx_pool[0]),
				      GFP_KERNEL);
	trans_pcie->global_table =
		kसुस्मृति(RX_POOL_SIZE(trans_pcie->num_rx_bufs),
			माप(trans_pcie->global_table[0]),
			GFP_KERNEL);
	अगर (!trans_pcie->rxq || !trans_pcie->rx_pool ||
	    !trans_pcie->global_table) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	spin_lock_init(&rba->lock);

	/*
	 * Allocate the driver's poपूर्णांकer to receive buffer status.
	 * Allocate क्रम all queues continuously (HW requirement).
	 */
	trans_pcie->base_rb_stts =
			dma_alloc_coherent(trans->dev,
					   rb_stts_size * trans->num_rx_queues,
					   &trans_pcie->base_rb_stts_dma,
					   GFP_KERNEL);
	अगर (!trans_pcie->base_rb_stts) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < trans->num_rx_queues; i++) अणु
		काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[i];

		rxq->id = i;
		ret = iwl_pcie_alloc_rxq_dma(trans, rxq);
		अगर (ret)
			जाओ err;
	पूर्ण
	वापस 0;

err:
	अगर (trans_pcie->base_rb_stts) अणु
		dma_मुक्त_coherent(trans->dev,
				  rb_stts_size * trans->num_rx_queues,
				  trans_pcie->base_rb_stts,
				  trans_pcie->base_rb_stts_dma);
		trans_pcie->base_rb_stts = शून्य;
		trans_pcie->base_rb_stts_dma = 0;
	पूर्ण
	kमुक्त(trans_pcie->rx_pool);
	trans_pcie->rx_pool = शून्य;
	kमुक्त(trans_pcie->global_table);
	trans_pcie->global_table = शून्य;
	kमुक्त(trans_pcie->rxq);
	trans_pcie->rxq = शून्य;

	वापस ret;
पूर्ण

अटल व्योम iwl_pcie_rx_hw_init(काष्ठा iwl_trans *trans, काष्ठा iwl_rxq *rxq)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 rb_size;
	स्थिर u32 rfdnlog = RX_QUEUE_SIZE_LOG; /* 256 RBDs */

	चयन (trans_pcie->rx_buf_size) अणु
	हाल IWL_AMSDU_4K:
		rb_size = FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_4K;
		अवरोध;
	हाल IWL_AMSDU_8K:
		rb_size = FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_8K;
		अवरोध;
	हाल IWL_AMSDU_12K:
		rb_size = FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_12K;
		अवरोध;
	शेष:
		WARN_ON(1);
		rb_size = FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_4K;
	पूर्ण

	अगर (!iwl_trans_grab_nic_access(trans))
		वापस;

	/* Stop Rx DMA */
	iwl_ग_लिखो32(trans, FH_MEM_RCSR_CHNL0_CONFIG_REG, 0);
	/* reset and flush poपूर्णांकers */
	iwl_ग_लिखो32(trans, FH_MEM_RCSR_CHNL0_RBDCB_WPTR, 0);
	iwl_ग_लिखो32(trans, FH_MEM_RCSR_CHNL0_FLUSH_RB_REQ, 0);
	iwl_ग_लिखो32(trans, FH_RSCSR_CHNL0_RDPTR, 0);

	/* Reset driver's Rx queue ग_लिखो index */
	iwl_ग_लिखो32(trans, FH_RSCSR_CHNL0_RBDCB_WPTR_REG, 0);

	/* Tell device where to find RBD circular buffer in DRAM */
	iwl_ग_लिखो32(trans, FH_RSCSR_CHNL0_RBDCB_BASE_REG,
		    (u32)(rxq->bd_dma >> 8));

	/* Tell device where in DRAM to update its Rx status */
	iwl_ग_लिखो32(trans, FH_RSCSR_CHNL0_STTS_WPTR_REG,
		    rxq->rb_stts_dma >> 4);

	/* Enable Rx DMA
	 * FH_RCSR_CHNL0_RX_IGNORE_RXF_EMPTY is set because of HW bug in
	 *      the credit mechanism in 5000 HW RX FIFO
	 * Direct rx पूर्णांकerrupts to hosts
	 * Rx buffer size 4 or 8k or 12k
	 * RB समयout 0x10
	 * 256 RBDs
	 */
	iwl_ग_लिखो32(trans, FH_MEM_RCSR_CHNL0_CONFIG_REG,
		    FH_RCSR_RX_CONFIG_CHNL_EN_ENABLE_VAL |
		    FH_RCSR_CHNL0_RX_IGNORE_RXF_EMPTY |
		    FH_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_INT_HOST_VAL |
		    rb_size |
		    (RX_RB_TIMEOUT << FH_RCSR_RX_CONFIG_REG_IRQ_RBTH_POS) |
		    (rfdnlog << FH_RCSR_RX_CONFIG_RBDCB_SIZE_POS));

	iwl_trans_release_nic_access(trans);

	/* Set पूर्णांकerrupt coalescing समयr to शेष (2048 usecs) */
	iwl_ग_लिखो8(trans, CSR_INT_COALESCING, IWL_HOST_INT_TIMEOUT_DEF);

	/* W/A क्रम पूर्णांकerrupt coalescing bug in 7260 and 3160 */
	अगर (trans->cfg->host_पूर्णांकerrupt_operation_mode)
		iwl_set_bit(trans, CSR_INT_COALESCING, IWL_HOST_INT_OPER_MODE);
पूर्ण

अटल व्योम iwl_pcie_rx_mq_hw_init(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 rb_size, enabled = 0;
	पूर्णांक i;

	चयन (trans_pcie->rx_buf_size) अणु
	हाल IWL_AMSDU_2K:
		rb_size = RFH_RXF_DMA_RB_SIZE_2K;
		अवरोध;
	हाल IWL_AMSDU_4K:
		rb_size = RFH_RXF_DMA_RB_SIZE_4K;
		अवरोध;
	हाल IWL_AMSDU_8K:
		rb_size = RFH_RXF_DMA_RB_SIZE_8K;
		अवरोध;
	हाल IWL_AMSDU_12K:
		rb_size = RFH_RXF_DMA_RB_SIZE_12K;
		अवरोध;
	शेष:
		WARN_ON(1);
		rb_size = RFH_RXF_DMA_RB_SIZE_4K;
	पूर्ण

	अगर (!iwl_trans_grab_nic_access(trans))
		वापस;

	/* Stop Rx DMA */
	iwl_ग_लिखो_prph_no_grab(trans, RFH_RXF_DMA_CFG, 0);
	/* disable मुक्त amd used rx queue operation */
	iwl_ग_लिखो_prph_no_grab(trans, RFH_RXF_RXQ_ACTIVE, 0);

	क्रम (i = 0; i < trans->num_rx_queues; i++) अणु
		/* Tell device where to find RBD मुक्त table in DRAM */
		iwl_ग_लिखो_prph64_no_grab(trans,
					 RFH_Q_FRBDCB_BA_LSB(i),
					 trans_pcie->rxq[i].bd_dma);
		/* Tell device where to find RBD used table in DRAM */
		iwl_ग_लिखो_prph64_no_grab(trans,
					 RFH_Q_URBDCB_BA_LSB(i),
					 trans_pcie->rxq[i].used_bd_dma);
		/* Tell device where in DRAM to update its Rx status */
		iwl_ग_लिखो_prph64_no_grab(trans,
					 RFH_Q_URBD_STTS_WPTR_LSB(i),
					 trans_pcie->rxq[i].rb_stts_dma);
		/* Reset device indice tables */
		iwl_ग_लिखो_prph_no_grab(trans, RFH_Q_FRBDCB_WIDX(i), 0);
		iwl_ग_लिखो_prph_no_grab(trans, RFH_Q_FRBDCB_RIDX(i), 0);
		iwl_ग_लिखो_prph_no_grab(trans, RFH_Q_URBDCB_WIDX(i), 0);

		enabled |= BIT(i) | BIT(i + 16);
	पूर्ण

	/*
	 * Enable Rx DMA
	 * Rx buffer size 4 or 8k or 12k
	 * Min RB size 4 or 8
	 * Drop frames that exceed RB size
	 * 512 RBDs
	 */
	iwl_ग_लिखो_prph_no_grab(trans, RFH_RXF_DMA_CFG,
			       RFH_DMA_EN_ENABLE_VAL | rb_size |
			       RFH_RXF_DMA_MIN_RB_4_8 |
			       RFH_RXF_DMA_DROP_TOO_LARGE_MASK |
			       RFH_RXF_DMA_RBDCB_SIZE_512);

	/*
	 * Activate DMA snooping.
	 * Set RX DMA chunk size to 64B क्रम IOSF and 128B क्रम PCIe
	 * Default queue is 0
	 */
	iwl_ग_लिखो_prph_no_grab(trans, RFH_GEN_CFG,
			       RFH_GEN_CFG_RFH_DMA_SNOOP |
			       RFH_GEN_CFG_VAL(DEFAULT_RXQ_NUM, 0) |
			       RFH_GEN_CFG_SERVICE_DMA_SNOOP |
			       RFH_GEN_CFG_VAL(RB_CHUNK_SIZE,
					       trans->trans_cfg->पूर्णांकegrated ?
					       RFH_GEN_CFG_RB_CHUNK_SIZE_64 :
					       RFH_GEN_CFG_RB_CHUNK_SIZE_128));
	/* Enable the relevant rx queues */
	iwl_ग_लिखो_prph_no_grab(trans, RFH_RXF_RXQ_ACTIVE, enabled);

	iwl_trans_release_nic_access(trans);

	/* Set पूर्णांकerrupt coalescing समयr to शेष (2048 usecs) */
	iwl_ग_लिखो8(trans, CSR_INT_COALESCING, IWL_HOST_INT_TIMEOUT_DEF);
पूर्ण

व्योम iwl_pcie_rx_init_rxb_lists(काष्ठा iwl_rxq *rxq)
अणु
	lockdep_निश्चित_held(&rxq->lock);

	INIT_LIST_HEAD(&rxq->rx_मुक्त);
	INIT_LIST_HEAD(&rxq->rx_used);
	rxq->मुक्त_count = 0;
	rxq->used_count = 0;
पूर्ण

अटल पूर्णांक iwl_pcie_rx_handle(काष्ठा iwl_trans *trans, पूर्णांक queue, पूर्णांक budget);

अटल पूर्णांक iwl_pcie_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा iwl_rxq *rxq = container_of(napi, काष्ठा iwl_rxq, napi);
	काष्ठा iwl_trans_pcie *trans_pcie;
	काष्ठा iwl_trans *trans;
	पूर्णांक ret;

	trans_pcie = container_of(napi->dev, काष्ठा iwl_trans_pcie, napi_dev);
	trans = trans_pcie->trans;

	ret = iwl_pcie_rx_handle(trans, rxq->id, budget);

	IWL_DEBUG_ISR(trans, "[%d] handled %d, budget %d\n",
		      rxq->id, ret, budget);

	अगर (ret < budget) अणु
		spin_lock(&trans_pcie->irq_lock);
		अगर (test_bit(STATUS_INT_ENABLED, &trans->status))
			_iwl_enable_पूर्णांकerrupts(trans);
		spin_unlock(&trans_pcie->irq_lock);

		napi_complete_करोne(&rxq->napi, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_pcie_napi_poll_msix(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा iwl_rxq *rxq = container_of(napi, काष्ठा iwl_rxq, napi);
	काष्ठा iwl_trans_pcie *trans_pcie;
	काष्ठा iwl_trans *trans;
	पूर्णांक ret;

	trans_pcie = container_of(napi->dev, काष्ठा iwl_trans_pcie, napi_dev);
	trans = trans_pcie->trans;

	ret = iwl_pcie_rx_handle(trans, rxq->id, budget);
	IWL_DEBUG_ISR(trans, "[%d] handled %d, budget %d\n", rxq->id, ret,
		      budget);

	अगर (ret < budget) अणु
		पूर्णांक irq_line = rxq->id;

		/* FIRST_RSS is shared with line 0 */
		अगर (trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_FIRST_RSS &&
		    rxq->id == 1)
			irq_line = 0;

		spin_lock(&trans_pcie->irq_lock);
		iwl_pcie_clear_irq(trans, irq_line);
		spin_unlock(&trans_pcie->irq_lock);

		napi_complete_करोne(&rxq->napi, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _iwl_pcie_rx_init(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rxq *def_rxq;
	काष्ठा iwl_rb_allocator *rba = &trans_pcie->rba;
	पूर्णांक i, err, queue_size, allocator_pool_size, num_alloc;

	अगर (!trans_pcie->rxq) अणु
		err = iwl_pcie_rx_alloc(trans);
		अगर (err)
			वापस err;
	पूर्ण
	def_rxq = trans_pcie->rxq;

	cancel_work_sync(&rba->rx_alloc);

	spin_lock_bh(&rba->lock);
	atomic_set(&rba->req_pending, 0);
	atomic_set(&rba->req_पढ़ोy, 0);
	INIT_LIST_HEAD(&rba->rbd_allocated);
	INIT_LIST_HEAD(&rba->rbd_empty);
	spin_unlock_bh(&rba->lock);

	/* मुक्त all first - we might be reconfigured क्रम a dअगरferent size */
	iwl_pcie_मुक्त_rbs_pool(trans);

	क्रम (i = 0; i < RX_QUEUE_SIZE; i++)
		def_rxq->queue[i] = शून्य;

	क्रम (i = 0; i < trans->num_rx_queues; i++) अणु
		काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[i];

		spin_lock_bh(&rxq->lock);
		/*
		 * Set पढ़ो ग_लिखो poपूर्णांकer to reflect that we have processed
		 * and used all buffers, but have not restocked the Rx queue
		 * with fresh buffers
		 */
		rxq->पढ़ो = 0;
		rxq->ग_लिखो = 0;
		rxq->ग_लिखो_actual = 0;
		स_रखो(rxq->rb_stts, 0,
		       (trans->trans_cfg->device_family >=
			IWL_DEVICE_FAMILY_AX210) ?
		       माप(__le16) : माप(काष्ठा iwl_rb_status));

		iwl_pcie_rx_init_rxb_lists(rxq);

		spin_unlock_bh(&rxq->lock);

		अगर (!rxq->napi.poll) अणु
			पूर्णांक (*poll)(काष्ठा napi_काष्ठा *, पूर्णांक) = iwl_pcie_napi_poll;

			अगर (trans_pcie->msix_enabled)
				poll = iwl_pcie_napi_poll_msix;

			netअगर_napi_add(&trans_pcie->napi_dev, &rxq->napi,
				       poll, NAPI_POLL_WEIGHT);
			napi_enable(&rxq->napi);
		पूर्ण

	पूर्ण

	/* move the pool to the शेष queue and allocator ownerships */
	queue_size = trans->trans_cfg->mq_rx_supported ?
			trans_pcie->num_rx_bufs - 1 : RX_QUEUE_SIZE;
	allocator_pool_size = trans->num_rx_queues *
		(RX_CLAIM_REQ_ALLOC - RX_POST_REQ_ALLOC);
	num_alloc = queue_size + allocator_pool_size;

	क्रम (i = 0; i < num_alloc; i++) अणु
		काष्ठा iwl_rx_mem_buffer *rxb = &trans_pcie->rx_pool[i];

		अगर (i < allocator_pool_size)
			list_add(&rxb->list, &rba->rbd_empty);
		अन्यथा
			list_add(&rxb->list, &def_rxq->rx_used);
		trans_pcie->global_table[i] = rxb;
		rxb->vid = (u16)(i + 1);
		rxb->invalid = true;
	पूर्ण

	iwl_pcie_rxq_alloc_rbs(trans, GFP_KERNEL, def_rxq);

	वापस 0;
पूर्ण

पूर्णांक iwl_pcie_rx_init(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	पूर्णांक ret = _iwl_pcie_rx_init(trans);

	अगर (ret)
		वापस ret;

	अगर (trans->trans_cfg->mq_rx_supported)
		iwl_pcie_rx_mq_hw_init(trans);
	अन्यथा
		iwl_pcie_rx_hw_init(trans, trans_pcie->rxq);

	iwl_pcie_rxq_restock(trans, trans_pcie->rxq);

	spin_lock_bh(&trans_pcie->rxq->lock);
	iwl_pcie_rxq_inc_wr_ptr(trans, trans_pcie->rxq);
	spin_unlock_bh(&trans_pcie->rxq->lock);

	वापस 0;
पूर्ण

पूर्णांक iwl_pcie_gen2_rx_init(काष्ठा iwl_trans *trans)
अणु
	/* Set पूर्णांकerrupt coalescing समयr to शेष (2048 usecs) */
	iwl_ग_लिखो8(trans, CSR_INT_COALESCING, IWL_HOST_INT_TIMEOUT_DEF);

	/*
	 * We करोn't configure the RFH.
	 * Restock will be करोne at alive, after firmware configured the RFH.
	 */
	वापस _iwl_pcie_rx_init(trans);
पूर्ण

व्योम iwl_pcie_rx_मुक्त(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rb_allocator *rba = &trans_pcie->rba;
	पूर्णांक i;
	माप_प्रकार rb_stts_size = trans->trans_cfg->device_family >=
				IWL_DEVICE_FAMILY_AX210 ?
			      माप(__le16) : माप(काष्ठा iwl_rb_status);

	/*
	 * अगर rxq is शून्य, it means that nothing has been allocated,
	 * निकास now
	 */
	अगर (!trans_pcie->rxq) अणु
		IWL_DEBUG_INFO(trans, "Free NULL rx context\n");
		वापस;
	पूर्ण

	cancel_work_sync(&rba->rx_alloc);

	iwl_pcie_मुक्त_rbs_pool(trans);

	अगर (trans_pcie->base_rb_stts) अणु
		dma_मुक्त_coherent(trans->dev,
				  rb_stts_size * trans->num_rx_queues,
				  trans_pcie->base_rb_stts,
				  trans_pcie->base_rb_stts_dma);
		trans_pcie->base_rb_stts = शून्य;
		trans_pcie->base_rb_stts_dma = 0;
	पूर्ण

	क्रम (i = 0; i < trans->num_rx_queues; i++) अणु
		काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[i];

		iwl_pcie_मुक्त_rxq_dma(trans, rxq);

		अगर (rxq->napi.poll) अणु
			napi_disable(&rxq->napi);
			netअगर_napi_del(&rxq->napi);
		पूर्ण
	पूर्ण
	kमुक्त(trans_pcie->rx_pool);
	kमुक्त(trans_pcie->global_table);
	kमुक्त(trans_pcie->rxq);

	अगर (trans_pcie->alloc_page)
		__मुक्त_pages(trans_pcie->alloc_page, trans_pcie->rx_page_order);
पूर्ण

अटल व्योम iwl_pcie_rx_move_to_allocator(काष्ठा iwl_rxq *rxq,
					  काष्ठा iwl_rb_allocator *rba)
अणु
	spin_lock(&rba->lock);
	list_splice_tail_init(&rxq->rx_used, &rba->rbd_empty);
	spin_unlock(&rba->lock);
पूर्ण

/*
 * iwl_pcie_rx_reuse_rbd - Recycle used RBDs
 *
 * Called when a RBD can be reused. The RBD is transferred to the allocator.
 * When there are 2 empty RBDs - a request क्रम allocation is posted
 */
अटल व्योम iwl_pcie_rx_reuse_rbd(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_rx_mem_buffer *rxb,
				  काष्ठा iwl_rxq *rxq, bool emergency)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rb_allocator *rba = &trans_pcie->rba;

	/* Move the RBD to the used list, will be moved to allocator in batches
	 * beक्रमe claiming or posting a request*/
	list_add_tail(&rxb->list, &rxq->rx_used);

	अगर (unlikely(emergency))
		वापस;

	/* Count the allocator owned RBDs */
	rxq->used_count++;

	/* If we have RX_POST_REQ_ALLOC new released rx buffers -
	 * issue a request क्रम allocator. Modulo RX_CLAIM_REQ_ALLOC is
	 * used क्रम the हाल we failed to claim RX_CLAIM_REQ_ALLOC,
	 * after but we still need to post another request.
	 */
	अगर ((rxq->used_count % RX_CLAIM_REQ_ALLOC) == RX_POST_REQ_ALLOC) अणु
		/* Move the 2 RBDs to the allocator ownership.
		 Allocator has another 6 from pool क्रम the request completion*/
		iwl_pcie_rx_move_to_allocator(rxq, rba);

		atomic_inc(&rba->req_pending);
		queue_work(rba->alloc_wq, &rba->rx_alloc);
	पूर्ण
पूर्ण

अटल व्योम iwl_pcie_rx_handle_rb(काष्ठा iwl_trans *trans,
				काष्ठा iwl_rxq *rxq,
				काष्ठा iwl_rx_mem_buffer *rxb,
				bool emergency,
				पूर्णांक i)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_txq *txq = trans->txqs.txq[trans->txqs.cmd.q_id];
	bool page_stolen = false;
	पूर्णांक max_len = trans_pcie->rx_buf_bytes;
	u32 offset = 0;

	अगर (WARN_ON(!rxb))
		वापस;

	dma_unmap_page(trans->dev, rxb->page_dma, max_len, DMA_FROM_DEVICE);

	जबतक (offset + माप(u32) + माप(काष्ठा iwl_cmd_header) < max_len) अणु
		काष्ठा iwl_rx_packet *pkt;
		bool reclaim;
		पूर्णांक len;
		काष्ठा iwl_rx_cmd_buffer rxcb = अणु
			._offset = rxb->offset + offset,
			._rx_page_order = trans_pcie->rx_page_order,
			._page = rxb->page,
			._page_stolen = false,
			.truesize = max_len,
		पूर्ण;

		pkt = rxb_addr(&rxcb);

		अगर (pkt->len_n_flags == cpu_to_le32(FH_RSCSR_FRAME_INVALID)) अणु
			IWL_DEBUG_RX(trans,
				     "Q %d: RB end marker at offset %d\n",
				     rxq->id, offset);
			अवरोध;
		पूर्ण

		WARN((le32_to_cpu(pkt->len_n_flags) & FH_RSCSR_RXQ_MASK) >>
			FH_RSCSR_RXQ_POS != rxq->id,
		     "frame on invalid queue - is on %d and indicates %d\n",
		     rxq->id,
		     (le32_to_cpu(pkt->len_n_flags) & FH_RSCSR_RXQ_MASK) >>
			FH_RSCSR_RXQ_POS);

		IWL_DEBUG_RX(trans,
			     "Q %d: cmd at offset %d: %s (%.2x.%2x, seq 0x%x)\n",
			     rxq->id, offset,
			     iwl_get_cmd_string(trans,
						iwl_cmd_id(pkt->hdr.cmd,
							   pkt->hdr.group_id,
							   0)),
			     pkt->hdr.group_id, pkt->hdr.cmd,
			     le16_to_cpu(pkt->hdr.sequence));

		len = iwl_rx_packet_len(pkt);
		len += माप(u32); /* account क्रम status word */

		offset += ALIGN(len, FH_RSCSR_FRAME_ALIGN);

		/* check that what the device tells us made sense */
		अगर (offset > max_len)
			अवरोध;

		trace_iwlwअगरi_dev_rx(trans->dev, trans, pkt, len);
		trace_iwlwअगरi_dev_rx_data(trans->dev, trans, pkt, len);

		/* Reclaim a command buffer only अगर this packet is a response
		 *   to a (driver-originated) command.
		 * If the packet (e.g. Rx frame) originated from uCode,
		 *   there is no command buffer to reclaim.
		 * Ucode should set SEQ_RX_FRAME bit अगर ucode-originated,
		 *   but apparently a few करोn't get set; catch them here. */
		reclaim = !(pkt->hdr.sequence & SEQ_RX_FRAME);
		अगर (reclaim && !pkt->hdr.group_id) अणु
			पूर्णांक i;

			क्रम (i = 0; i < trans_pcie->n_no_reclaim_cmds; i++) अणु
				अगर (trans_pcie->no_reclaim_cmds[i] ==
							pkt->hdr.cmd) अणु
					reclaim = false;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (rxq->id == trans_pcie->def_rx_queue)
			iwl_op_mode_rx(trans->op_mode, &rxq->napi,
				       &rxcb);
		अन्यथा
			iwl_op_mode_rx_rss(trans->op_mode, &rxq->napi,
					   &rxcb, rxq->id);

		/*
		 * After here, we should always check rxcb._page_stolen,
		 * अगर it is true then one of the handlers took the page.
		 */

		अगर (reclaim) अणु
			u16 sequence = le16_to_cpu(pkt->hdr.sequence);
			पूर्णांक index = SEQ_TO_INDEX(sequence);
			पूर्णांक cmd_index = iwl_txq_get_cmd_index(txq, index);

			kमुक्त_sensitive(txq->entries[cmd_index].मुक्त_buf);
			txq->entries[cmd_index].मुक्त_buf = शून्य;

			/* Invoke any callbacks, transfer the buffer to caller,
			 * and fire off the (possibly) blocking
			 * iwl_trans_send_cmd()
			 * as we reclaim the driver command queue */
			अगर (!rxcb._page_stolen)
				iwl_pcie_hcmd_complete(trans, &rxcb);
			अन्यथा
				IWL_WARN(trans, "Claim null rxb?\n");
		पूर्ण

		page_stolen |= rxcb._page_stolen;
		अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
			अवरोध;
	पूर्ण

	/* page was stolen from us -- मुक्त our reference */
	अगर (page_stolen) अणु
		__मुक्त_pages(rxb->page, trans_pcie->rx_page_order);
		rxb->page = शून्य;
	पूर्ण

	/* Reuse the page अगर possible. For notअगरication packets and
	 * SKBs that fail to Rx correctly, add them back पूर्णांकo the
	 * rx_मुक्त list क्रम reuse later. */
	अगर (rxb->page != शून्य) अणु
		rxb->page_dma =
			dma_map_page(trans->dev, rxb->page, rxb->offset,
				     trans_pcie->rx_buf_bytes,
				     DMA_FROM_DEVICE);
		अगर (dma_mapping_error(trans->dev, rxb->page_dma)) अणु
			/*
			 * मुक्त the page(s) as well to not अवरोध
			 * the invariant that the items on the used
			 * list have no page(s)
			 */
			__मुक्त_pages(rxb->page, trans_pcie->rx_page_order);
			rxb->page = शून्य;
			iwl_pcie_rx_reuse_rbd(trans, rxb, rxq, emergency);
		पूर्ण अन्यथा अणु
			list_add_tail(&rxb->list, &rxq->rx_मुक्त);
			rxq->मुक्त_count++;
		पूर्ण
	पूर्ण अन्यथा
		iwl_pcie_rx_reuse_rbd(trans, rxb, rxq, emergency);
पूर्ण

अटल काष्ठा iwl_rx_mem_buffer *iwl_pcie_get_rxb(काष्ठा iwl_trans *trans,
						  काष्ठा iwl_rxq *rxq, पूर्णांक i,
						  bool *join)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rx_mem_buffer *rxb;
	u16 vid;

	BUILD_BUG_ON(माप(काष्ठा iwl_rx_completion_desc) != 32);

	अगर (!trans->trans_cfg->mq_rx_supported) अणु
		rxb = rxq->queue[i];
		rxq->queue[i] = शून्य;
		वापस rxb;
	पूर्ण

	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		vid = le16_to_cpu(rxq->cd[i].rbid);
		*join = rxq->cd[i].flags & IWL_RX_CD_FLAGS_FRAGMENTED;
	पूर्ण अन्यथा अणु
		vid = le32_to_cpu(rxq->bd_32[i]) & 0x0FFF; /* 12-bit VID */
	पूर्ण

	अगर (!vid || vid > RX_POOL_SIZE(trans_pcie->num_rx_bufs))
		जाओ out_err;

	rxb = trans_pcie->global_table[vid - 1];
	अगर (rxb->invalid)
		जाओ out_err;

	IWL_DEBUG_RX(trans, "Got virtual RB ID %u\n", (u32)rxb->vid);

	rxb->invalid = true;

	वापस rxb;

out_err:
	WARN(1, "Invalid rxb from HW %u\n", (u32)vid);
	iwl_क्रमce_nmi(trans);
	वापस शून्य;
पूर्ण

/*
 * iwl_pcie_rx_handle - Main entry function क्रम receiving responses from fw
 */
अटल पूर्णांक iwl_pcie_rx_handle(काष्ठा iwl_trans *trans, पूर्णांक queue, पूर्णांक budget)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा iwl_rxq *rxq;
	u32 r, i, count = 0, handled = 0;
	bool emergency = false;

	अगर (WARN_ON_ONCE(!trans_pcie->rxq || !trans_pcie->rxq[queue].bd))
		वापस budget;

	rxq = &trans_pcie->rxq[queue];

restart:
	spin_lock(&rxq->lock);
	/* uCode's पढ़ो index (stored in shared DRAM) indicates the last Rx
	 * buffer that the driver may process (last buffer filled by ucode). */
	r = le16_to_cpu(iwl_get_बंदd_rb_stts(trans, rxq)) & 0x0FFF;
	i = rxq->पढ़ो;

	/* W/A 9000 device step A0 wrap-around bug */
	r &= (rxq->queue_size - 1);

	/* Rx पूर्णांकerrupt, but nothing sent from uCode */
	अगर (i == r)
		IWL_DEBUG_RX(trans, "Q %d: HW = SW = %d\n", rxq->id, r);

	जबतक (i != r && ++handled < budget) अणु
		काष्ठा iwl_rb_allocator *rba = &trans_pcie->rba;
		काष्ठा iwl_rx_mem_buffer *rxb;
		/* number of RBDs still रुकोing क्रम page allocation */
		u32 rb_pending_alloc =
			atomic_पढ़ो(&trans_pcie->rba.req_pending) *
			RX_CLAIM_REQ_ALLOC;
		bool join = false;

		अगर (unlikely(rb_pending_alloc >= rxq->queue_size / 2 &&
			     !emergency)) अणु
			iwl_pcie_rx_move_to_allocator(rxq, rba);
			emergency = true;
			IWL_DEBUG_TPT(trans,
				      "RX path is in emergency. Pending allocations %d\n",
				      rb_pending_alloc);
		पूर्ण

		IWL_DEBUG_RX(trans, "Q %d: HW = %d, SW = %d\n", rxq->id, r, i);

		rxb = iwl_pcie_get_rxb(trans, rxq, i, &join);
		अगर (!rxb)
			जाओ out;

		अगर (unlikely(join || rxq->next_rb_is_fragment)) अणु
			rxq->next_rb_is_fragment = join;
			/*
			 * We can only get a multi-RB in the following हालs:
			 *  - firmware issue, sending a too big notअगरication
			 *  - snअगरfer mode with a large A-MSDU
			 *  - large MTU frames (>2k)
			 * since the multi-RB functionality is limited to newer
			 * hardware that cannot put multiple entries पूर्णांकo a
			 * single RB.
			 *
			 * Right now, the higher layers aren't set up to deal
			 * with that, so discard all of these.
			 */
			list_add_tail(&rxb->list, &rxq->rx_मुक्त);
			rxq->मुक्त_count++;
		पूर्ण अन्यथा अणु
			iwl_pcie_rx_handle_rb(trans, rxq, rxb, emergency, i);
		पूर्ण

		i = (i + 1) & (rxq->queue_size - 1);

		/*
		 * If we have RX_CLAIM_REQ_ALLOC released rx buffers -
		 * try to claim the pre-allocated buffers from the allocator.
		 * If not पढ़ोy - will try to reclaim next समय.
		 * There is no need to reschedule work - allocator निकासs only
		 * on success
		 */
		अगर (rxq->used_count >= RX_CLAIM_REQ_ALLOC)
			iwl_pcie_rx_allocator_get(trans, rxq);

		अगर (rxq->used_count % RX_CLAIM_REQ_ALLOC == 0 && !emergency) अणु
			/* Add the reमुख्यing empty RBDs क्रम allocator use */
			iwl_pcie_rx_move_to_allocator(rxq, rba);
		पूर्ण अन्यथा अगर (emergency) अणु
			count++;
			अगर (count == 8) अणु
				count = 0;
				अगर (rb_pending_alloc < rxq->queue_size / 3) अणु
					IWL_DEBUG_TPT(trans,
						      "RX path exited emergency. Pending allocations %d\n",
						      rb_pending_alloc);
					emergency = false;
				पूर्ण

				rxq->पढ़ो = i;
				spin_unlock(&rxq->lock);
				iwl_pcie_rxq_alloc_rbs(trans, GFP_ATOMIC, rxq);
				iwl_pcie_rxq_restock(trans, rxq);
				जाओ restart;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	/* Backtrack one entry */
	rxq->पढ़ो = i;
	/* update cr tail with the rxq पढ़ो poपूर्णांकer */
	अगर (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		*rxq->cr_tail = cpu_to_le16(r);
	spin_unlock(&rxq->lock);

	/*
	 * handle a हाल where in emergency there are some unallocated RBDs.
	 * those RBDs are in the used list, but are not tracked by the queue's
	 * used_count which counts allocator owned RBDs.
	 * unallocated emergency RBDs must be allocated on निकास, otherwise
	 * when called again the function may not be in emergency mode and
	 * they will be handed to the allocator with no tracking in the RBD
	 * allocator counters, which will lead to them never being claimed back
	 * by the queue.
	 * by allocating them here, they are now in the queue मुक्त list, and
	 * will be restocked by the next call of iwl_pcie_rxq_restock.
	 */
	अगर (unlikely(emergency && count))
		iwl_pcie_rxq_alloc_rbs(trans, GFP_ATOMIC, rxq);

	iwl_pcie_rxq_restock(trans, rxq);

	वापस handled;
पूर्ण

अटल काष्ठा iwl_trans_pcie *iwl_pcie_get_trans_pcie(काष्ठा msix_entry *entry)
अणु
	u8 queue = entry->entry;
	काष्ठा msix_entry *entries = entry - queue;

	वापस container_of(entries, काष्ठा iwl_trans_pcie, msix_entries[0]);
पूर्ण

/*
 * iwl_pcie_rx_msix_handle - Main entry function क्रम receiving responses from fw
 * This पूर्णांकerrupt handler should be used with RSS queue only.
 */
irqवापस_t iwl_pcie_irq_rx_msix_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा msix_entry *entry = dev_id;
	काष्ठा iwl_trans_pcie *trans_pcie = iwl_pcie_get_trans_pcie(entry);
	काष्ठा iwl_trans *trans = trans_pcie->trans;
	काष्ठा iwl_rxq *rxq = &trans_pcie->rxq[entry->entry];

	trace_iwlwअगरi_dev_irq_msix(trans->dev, entry, false, 0, 0);

	अगर (WARN_ON(entry->entry >= trans->num_rx_queues))
		वापस IRQ_NONE;

	अगर (WARN_ONCE(!rxq,
		      "[%d] Got MSI-X interrupt before we have Rx queues",
		      entry->entry))
		वापस IRQ_NONE;

	lock_map_acquire(&trans->sync_cmd_lockdep_map);
	IWL_DEBUG_ISR(trans, "[%d] Got interrupt\n", entry->entry);

	local_bh_disable();
	अगर (napi_schedule_prep(&rxq->napi))
		__napi_schedule(&rxq->napi);
	अन्यथा
		iwl_pcie_clear_irq(trans, entry->entry);
	local_bh_enable();

	lock_map_release(&trans->sync_cmd_lockdep_map);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * iwl_pcie_irq_handle_error - called क्रम HW or SW error पूर्णांकerrupt from card
 */
अटल व्योम iwl_pcie_irq_handle_error(काष्ठा iwl_trans *trans)
अणु
	पूर्णांक i;

	/* W/A क्रम WiFi/WiMAX coex and WiMAX own the RF */
	अगर (trans->cfg->पूर्णांकernal_wimax_coex &&
	    !trans->cfg->apmg_not_supported &&
	    (!(iwl_पढ़ो_prph(trans, APMG_CLK_CTRL_REG) &
			     APMS_CLK_VAL_MRB_FUNC_MODE) ||
	     (iwl_पढ़ो_prph(trans, APMG_PS_CTRL_REG) &
			    APMG_PS_CTRL_VAL_RESET_REQ))) अणु
		clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
		iwl_op_mode_wimax_active(trans->op_mode);
		wake_up(&trans->रुको_command_queue);
		वापस;
	पूर्ण

	क्रम (i = 0; i < trans->trans_cfg->base_params->num_of_queues; i++) अणु
		अगर (!trans->txqs.txq[i])
			जारी;
		del_समयr(&trans->txqs.txq[i]->stuck_समयr);
	पूर्ण

	/* The STATUS_FW_ERROR bit is set in this function. This must happen
	 * beक्रमe we wake up the command caller, to ensure a proper cleanup. */
	iwl_trans_fw_error(trans);

	clear_bit(STATUS_SYNC_HCMD_ACTIVE, &trans->status);
	wake_up(&trans->रुको_command_queue);
पूर्ण

अटल u32 iwl_pcie_पूर्णांक_cause_non_ict(काष्ठा iwl_trans *trans)
अणु
	u32 पूर्णांकa;

	lockdep_निश्चित_held(&IWL_TRANS_GET_PCIE_TRANS(trans)->irq_lock);

	trace_iwlwअगरi_dev_irq(trans->dev);

	/* Discover which पूर्णांकerrupts are active/pending */
	पूर्णांकa = iwl_पढ़ो32(trans, CSR_INT);

	/* the thपढ़ो will service पूर्णांकerrupts and re-enable them */
	वापस पूर्णांकa;
पूर्ण

/* a device (PCI-E) page is 4096 bytes दीर्घ */
#घोषणा ICT_SHIFT	12
#घोषणा ICT_SIZE	(1 << ICT_SHIFT)
#घोषणा ICT_COUNT	(ICT_SIZE / माप(u32))

/* पूर्णांकerrupt handler using ict table, with this पूर्णांकerrupt driver will
 * stop using INTA रेजिस्टर to get device's पूर्णांकerrupt, पढ़ोing this रेजिस्टर
 * is expensive, device will ग_लिखो पूर्णांकerrupts in ICT dram table, increment
 * index then will fire पूर्णांकerrupt to driver, driver will OR all ICT table
 * entries from current index up to table entry with 0 value. the result is
 * the पूर्णांकerrupt we need to service, driver will set the entries back to 0 and
 * set index.
 */
अटल u32 iwl_pcie_पूर्णांक_cause_ict(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 पूर्णांकa;
	u32 val = 0;
	u32 पढ़ो;

	trace_iwlwअगरi_dev_irq(trans->dev);

	/* Ignore पूर्णांकerrupt अगर there's nothing in NIC to service.
	 * This may be due to IRQ shared with another device,
	 * or due to sporadic पूर्णांकerrupts thrown from our NIC. */
	पढ़ो = le32_to_cpu(trans_pcie->ict_tbl[trans_pcie->ict_index]);
	trace_iwlwअगरi_dev_ict_पढ़ो(trans->dev, trans_pcie->ict_index, पढ़ो);
	अगर (!पढ़ो)
		वापस 0;

	/*
	 * Collect all entries up to the first 0, starting from ict_index;
	 * note we alपढ़ोy पढ़ो at ict_index.
	 */
	करो अणु
		val |= पढ़ो;
		IWL_DEBUG_ISR(trans, "ICT index %d value 0x%08X\n",
				trans_pcie->ict_index, पढ़ो);
		trans_pcie->ict_tbl[trans_pcie->ict_index] = 0;
		trans_pcie->ict_index =
			((trans_pcie->ict_index + 1) & (ICT_COUNT - 1));

		पढ़ो = le32_to_cpu(trans_pcie->ict_tbl[trans_pcie->ict_index]);
		trace_iwlwअगरi_dev_ict_पढ़ो(trans->dev, trans_pcie->ict_index,
					   पढ़ो);
	पूर्ण जबतक (पढ़ो);

	/* We should not get this value, just ignore it. */
	अगर (val == 0xffffffff)
		val = 0;

	/*
	 * this is a w/a क्रम a h/w bug. the h/w bug may cause the Rx bit
	 * (bit 15 beक्रमe shअगरting it to 31) to clear when using पूर्णांकerrupt
	 * coalescing. क्रमtunately, bits 18 and 19 stay set when this happens
	 * so we use them to decide on the real state of the Rx bit.
	 * In order words, bit 15 is set अगर bit 18 or bit 19 are set.
	 */
	अगर (val & 0xC0000)
		val |= 0x8000;

	पूर्णांकa = (0xff & val) | ((0xff00 & val) << 16);
	वापस पूर्णांकa;
पूर्ण

व्योम iwl_pcie_handle_rfसमाप्त_irq(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा isr_statistics *isr_stats = &trans_pcie->isr_stats;
	bool hw_rfसमाप्त, prev, report;

	mutex_lock(&trans_pcie->mutex);
	prev = test_bit(STATUS_RFKILL_OPMODE, &trans->status);
	hw_rfसमाप्त = iwl_is_rfसमाप्त_set(trans);
	अगर (hw_rfसमाप्त) अणु
		set_bit(STATUS_RFKILL_OPMODE, &trans->status);
		set_bit(STATUS_RFKILL_HW, &trans->status);
	पूर्ण
	अगर (trans_pcie->opmode_करोwn)
		report = hw_rfसमाप्त;
	अन्यथा
		report = test_bit(STATUS_RFKILL_OPMODE, &trans->status);

	IWL_WARN(trans, "RF_KILL bit toggled to %s.\n",
		 hw_rfसमाप्त ? "disable radio" : "enable radio");

	isr_stats->rfसमाप्त++;

	अगर (prev != report)
		iwl_trans_pcie_rf_समाप्त(trans, report);
	mutex_unlock(&trans_pcie->mutex);

	अगर (hw_rfसमाप्त) अणु
		अगर (test_and_clear_bit(STATUS_SYNC_HCMD_ACTIVE,
				       &trans->status))
			IWL_DEBUG_RF_KILL(trans,
					  "Rfkill while SYNC HCMD in flight\n");
		wake_up(&trans->रुको_command_queue);
	पूर्ण अन्यथा अणु
		clear_bit(STATUS_RFKILL_HW, &trans->status);
		अगर (trans_pcie->opmode_करोwn)
			clear_bit(STATUS_RFKILL_OPMODE, &trans->status);
	पूर्ण
पूर्ण

irqवापस_t iwl_pcie_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iwl_trans *trans = dev_id;
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	काष्ठा isr_statistics *isr_stats = &trans_pcie->isr_stats;
	u32 पूर्णांकa = 0;
	u32 handled = 0;
	bool polling = false;

	lock_map_acquire(&trans->sync_cmd_lockdep_map);

	spin_lock_bh(&trans_pcie->irq_lock);

	/* dram पूर्णांकerrupt table not set yet,
	 * use legacy पूर्णांकerrupt.
	 */
	अगर (likely(trans_pcie->use_ict))
		पूर्णांकa = iwl_pcie_पूर्णांक_cause_ict(trans);
	अन्यथा
		पूर्णांकa = iwl_pcie_पूर्णांक_cause_non_ict(trans);

	अगर (iwl_have_debug_level(IWL_DL_ISR)) अणु
		IWL_DEBUG_ISR(trans,
			      "ISR inta 0x%08x, enabled 0x%08x(sw), enabled(hw) 0x%08x, fh 0x%08x\n",
			      पूर्णांकa, trans_pcie->पूर्णांकa_mask,
			      iwl_पढ़ो32(trans, CSR_INT_MASK),
			      iwl_पढ़ो32(trans, CSR_FH_INT_STATUS));
		अगर (पूर्णांकa & (~trans_pcie->पूर्णांकa_mask))
			IWL_DEBUG_ISR(trans,
				      "We got a masked interrupt (0x%08x)\n",
				      पूर्णांकa & (~trans_pcie->पूर्णांकa_mask));
	पूर्ण

	पूर्णांकa &= trans_pcie->पूर्णांकa_mask;

	/*
	 * Ignore पूर्णांकerrupt अगर there's nothing in NIC to service.
	 * This may be due to IRQ shared with another device,
	 * or due to sporadic पूर्णांकerrupts thrown from our NIC.
	 */
	अगर (unlikely(!पूर्णांकa)) अणु
		IWL_DEBUG_ISR(trans, "Ignore interrupt, inta == 0\n");
		/*
		 * Re-enable पूर्णांकerrupts here since we करोn't
		 * have anything to service
		 */
		अगर (test_bit(STATUS_INT_ENABLED, &trans->status))
			_iwl_enable_पूर्णांकerrupts(trans);
		spin_unlock_bh(&trans_pcie->irq_lock);
		lock_map_release(&trans->sync_cmd_lockdep_map);
		वापस IRQ_NONE;
	पूर्ण

	अगर (unlikely(पूर्णांकa == 0xFFFFFFFF || (पूर्णांकa & 0xFFFFFFF0) == 0xa5a5a5a0)) अणु
		/*
		 * Hardware disappeared. It might have
		 * alपढ़ोy उठाओd an पूर्णांकerrupt.
		 */
		IWL_WARN(trans, "HARDWARE GONE?? INTA == 0x%08x\n", पूर्णांकa);
		spin_unlock_bh(&trans_pcie->irq_lock);
		जाओ out;
	पूर्ण

	/* Ack/clear/reset pending uCode पूर्णांकerrupts.
	 * Note:  Some bits in CSR_INT are "OR" of bits in CSR_FH_INT_STATUS,
	 */
	/* There is a hardware bug in the पूर्णांकerrupt mask function that some
	 * पूर्णांकerrupts (i.e. CSR_INT_BIT_SCD) can still be generated even अगर
	 * they are disabled in the CSR_INT_MASK रेजिस्टर. Furthermore the
	 * ICT पूर्णांकerrupt handling mechanism has another bug that might cause
	 * these unmasked पूर्णांकerrupts fail to be detected. We workaround the
	 * hardware bugs here by ACKing all the possible पूर्णांकerrupts so that
	 * पूर्णांकerrupt coalescing can still be achieved.
	 */
	iwl_ग_लिखो32(trans, CSR_INT, पूर्णांकa | ~trans_pcie->पूर्णांकa_mask);

	अगर (iwl_have_debug_level(IWL_DL_ISR))
		IWL_DEBUG_ISR(trans, "inta 0x%08x, enabled 0x%08x\n",
			      पूर्णांकa, iwl_पढ़ो32(trans, CSR_INT_MASK));

	spin_unlock_bh(&trans_pcie->irq_lock);

	/* Now service all पूर्णांकerrupt bits discovered above. */
	अगर (पूर्णांकa & CSR_INT_BIT_HW_ERR) अणु
		IWL_ERR(trans, "Hardware error detected.  Restarting.\n");

		/* Tell the device to stop sending पूर्णांकerrupts */
		iwl_disable_पूर्णांकerrupts(trans);

		isr_stats->hw++;
		iwl_pcie_irq_handle_error(trans);

		handled |= CSR_INT_BIT_HW_ERR;

		जाओ out;
	पूर्ण

	/* NIC fires this, but we करोn't use it, redundant with WAKEUP */
	अगर (पूर्णांकa & CSR_INT_BIT_SCD) अणु
		IWL_DEBUG_ISR(trans,
			      "Scheduler finished to transmit the frame/frames.\n");
		isr_stats->sch++;
	पूर्ण

	/* Alive notअगरication via Rx पूर्णांकerrupt will करो the real work */
	अगर (पूर्णांकa & CSR_INT_BIT_ALIVE) अणु
		IWL_DEBUG_ISR(trans, "Alive interrupt\n");
		isr_stats->alive++;
		अगर (trans->trans_cfg->gen2) अणु
			/*
			 * We can restock, since firmware configured
			 * the RFH
			 */
			iwl_pcie_rxmq_restock(trans, trans_pcie->rxq);
		पूर्ण

		handled |= CSR_INT_BIT_ALIVE;
	पूर्ण

	/* Safely ignore these bits क्रम debug checks below */
	पूर्णांकa &= ~(CSR_INT_BIT_SCD | CSR_INT_BIT_ALIVE);

	/* HW RF KILL चयन toggled */
	अगर (पूर्णांकa & CSR_INT_BIT_RF_KILL) अणु
		iwl_pcie_handle_rfसमाप्त_irq(trans);
		handled |= CSR_INT_BIT_RF_KILL;
	पूर्ण

	/* Chip got too hot and stopped itself */
	अगर (पूर्णांकa & CSR_INT_BIT_CT_KILL) अणु
		IWL_ERR(trans, "Microcode CT kill error detected.\n");
		isr_stats->ctसमाप्त++;
		handled |= CSR_INT_BIT_CT_KILL;
	पूर्ण

	/* Error detected by uCode */
	अगर (पूर्णांकa & CSR_INT_BIT_SW_ERR) अणु
		IWL_ERR(trans, "Microcode SW error detected. "
			" Restarting 0x%X.\n", पूर्णांकa);
		isr_stats->sw++;
		iwl_pcie_irq_handle_error(trans);
		handled |= CSR_INT_BIT_SW_ERR;
	पूर्ण

	/* uCode wakes up after घातer-करोwn sleep */
	अगर (पूर्णांकa & CSR_INT_BIT_WAKEUP) अणु
		IWL_DEBUG_ISR(trans, "Wakeup interrupt\n");
		iwl_pcie_rxq_check_wrptr(trans);
		iwl_pcie_txq_check_wrptrs(trans);

		isr_stats->wakeup++;

		handled |= CSR_INT_BIT_WAKEUP;
	पूर्ण

	/* All uCode command responses, including Tx command responses,
	 * Rx "responses" (frame-received notअगरication), and other
	 * notअगरications from uCode come through here*/
	अगर (पूर्णांकa & (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX |
		    CSR_INT_BIT_RX_PERIODIC)) अणु
		IWL_DEBUG_ISR(trans, "Rx interrupt\n");
		अगर (पूर्णांकa & (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX)) अणु
			handled |= (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX);
			iwl_ग_लिखो32(trans, CSR_FH_INT_STATUS,
					CSR_FH_INT_RX_MASK);
		पूर्ण
		अगर (पूर्णांकa & CSR_INT_BIT_RX_PERIODIC) अणु
			handled |= CSR_INT_BIT_RX_PERIODIC;
			iwl_ग_लिखो32(trans,
				CSR_INT, CSR_INT_BIT_RX_PERIODIC);
		पूर्ण
		/* Sending RX पूर्णांकerrupt require many steps to be करोne in the
		 * the device:
		 * 1- ग_लिखो पूर्णांकerrupt to current index in ICT table.
		 * 2- dma RX frame.
		 * 3- update RX shared data to indicate last ग_लिखो index.
		 * 4- send पूर्णांकerrupt.
		 * This could lead to RX race, driver could receive RX पूर्णांकerrupt
		 * but the shared data changes करोes not reflect this;
		 * periodic पूर्णांकerrupt will detect any dangling Rx activity.
		 */

		/* Disable periodic पूर्णांकerrupt; we use it as just a one-shot. */
		iwl_ग_लिखो8(trans, CSR_INT_PERIODIC_REG,
			    CSR_INT_PERIODIC_DIS);

		/*
		 * Enable periodic पूर्णांकerrupt in 8 msec only अगर we received
		 * real RX पूर्णांकerrupt (instead of just periodic पूर्णांक), to catch
		 * any dangling Rx पूर्णांकerrupt.  If it was just the periodic
		 * पूर्णांकerrupt, there was no dangling Rx activity, and no need
		 * to extend the periodic पूर्णांकerrupt; one-shot is enough.
		 */
		अगर (पूर्णांकa & (CSR_INT_BIT_FH_RX | CSR_INT_BIT_SW_RX))
			iwl_ग_लिखो8(trans, CSR_INT_PERIODIC_REG,
				   CSR_INT_PERIODIC_ENA);

		isr_stats->rx++;

		local_bh_disable();
		अगर (napi_schedule_prep(&trans_pcie->rxq[0].napi)) अणु
			polling = true;
			__napi_schedule(&trans_pcie->rxq[0].napi);
		पूर्ण
		local_bh_enable();
	पूर्ण

	/* This "Tx" DMA channel is used only क्रम loading uCode */
	अगर (पूर्णांकa & CSR_INT_BIT_FH_TX) अणु
		iwl_ग_लिखो32(trans, CSR_FH_INT_STATUS, CSR_FH_INT_TX_MASK);
		IWL_DEBUG_ISR(trans, "uCode load interrupt\n");
		isr_stats->tx++;
		handled |= CSR_INT_BIT_FH_TX;
		/* Wake up uCode load routine, now that load is complete */
		trans_pcie->ucode_ग_लिखो_complete = true;
		wake_up(&trans_pcie->ucode_ग_लिखो_रुकोq);
	पूर्ण

	अगर (पूर्णांकa & ~handled) अणु
		IWL_ERR(trans, "Unhandled INTA bits 0x%08x\n", पूर्णांकa & ~handled);
		isr_stats->unhandled++;
	पूर्ण

	अगर (पूर्णांकa & ~(trans_pcie->पूर्णांकa_mask)) अणु
		IWL_WARN(trans, "Disabled INTA bits 0x%08x were pending\n",
			 पूर्णांकa & ~trans_pcie->पूर्णांकa_mask);
	पूर्ण

	अगर (!polling) अणु
		spin_lock_bh(&trans_pcie->irq_lock);
		/* only Re-enable all पूर्णांकerrupt अगर disabled by irq */
		अगर (test_bit(STATUS_INT_ENABLED, &trans->status))
			_iwl_enable_पूर्णांकerrupts(trans);
		/* we are loading the firmware, enable FH_TX पूर्णांकerrupt only */
		अन्यथा अगर (handled & CSR_INT_BIT_FH_TX)
			iwl_enable_fw_load_पूर्णांक(trans);
		/* Re-enable RF_KILL अगर it occurred */
		अन्यथा अगर (handled & CSR_INT_BIT_RF_KILL)
			iwl_enable_rfसमाप्त_पूर्णांक(trans);
		/* Re-enable the ALIVE / Rx पूर्णांकerrupt अगर it occurred */
		अन्यथा अगर (handled & (CSR_INT_BIT_ALIVE | CSR_INT_BIT_FH_RX))
			iwl_enable_fw_load_पूर्णांक_ctx_info(trans);
		spin_unlock_bh(&trans_pcie->irq_lock);
	पूर्ण

out:
	lock_map_release(&trans->sync_cmd_lockdep_map);
	वापस IRQ_HANDLED;
पूर्ण

/******************************************************************************
 *
 * ICT functions
 *
 ******************************************************************************/

/* Free dram table */
व्योम iwl_pcie_मुक्त_ict(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	अगर (trans_pcie->ict_tbl) अणु
		dma_मुक्त_coherent(trans->dev, ICT_SIZE,
				  trans_pcie->ict_tbl,
				  trans_pcie->ict_tbl_dma);
		trans_pcie->ict_tbl = शून्य;
		trans_pcie->ict_tbl_dma = 0;
	पूर्ण
पूर्ण

/*
 * allocate dram shared table, it is an aligned memory
 * block of ICT_SIZE.
 * also reset all data related to ICT table पूर्णांकerrupt.
 */
पूर्णांक iwl_pcie_alloc_ict(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	trans_pcie->ict_tbl =
		dma_alloc_coherent(trans->dev, ICT_SIZE,
				   &trans_pcie->ict_tbl_dma, GFP_KERNEL);
	अगर (!trans_pcie->ict_tbl)
		वापस -ENOMEM;

	/* just an API sanity check ... it is guaranteed to be aligned */
	अगर (WARN_ON(trans_pcie->ict_tbl_dma & (ICT_SIZE - 1))) अणु
		iwl_pcie_मुक्त_ict(trans);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Device is going up inक्रमm it about using ICT पूर्णांकerrupt table,
 * also we need to tell the driver to start using ICT पूर्णांकerrupt.
 */
व्योम iwl_pcie_reset_ict(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 val;

	अगर (!trans_pcie->ict_tbl)
		वापस;

	spin_lock_bh(&trans_pcie->irq_lock);
	_iwl_disable_पूर्णांकerrupts(trans);

	स_रखो(trans_pcie->ict_tbl, 0, ICT_SIZE);

	val = trans_pcie->ict_tbl_dma >> ICT_SHIFT;

	val |= CSR_DRAM_INT_TBL_ENABLE |
	       CSR_DRAM_INIT_TBL_WRAP_CHECK |
	       CSR_DRAM_INIT_TBL_WRITE_POINTER;

	IWL_DEBUG_ISR(trans, "CSR_DRAM_INT_TBL_REG =0x%x\n", val);

	iwl_ग_लिखो32(trans, CSR_DRAM_INT_TBL_REG, val);
	trans_pcie->use_ict = true;
	trans_pcie->ict_index = 0;
	iwl_ग_लिखो32(trans, CSR_INT, trans_pcie->पूर्णांकa_mask);
	_iwl_enable_पूर्णांकerrupts(trans);
	spin_unlock_bh(&trans_pcie->irq_lock);
पूर्ण

/* Device is going करोwn disable ict पूर्णांकerrupt usage */
व्योम iwl_pcie_disable_ict(काष्ठा iwl_trans *trans)
अणु
	काष्ठा iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	spin_lock_bh(&trans_pcie->irq_lock);
	trans_pcie->use_ict = false;
	spin_unlock_bh(&trans_pcie->irq_lock);
पूर्ण

irqवापस_t iwl_pcie_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iwl_trans *trans = data;

	अगर (!trans)
		वापस IRQ_NONE;

	/* Disable (but करोn't clear!) पूर्णांकerrupts here to aव्योम
	 * back-to-back ISRs and sporadic पूर्णांकerrupts from our NIC.
	 * If we have something to service, the tasklet will re-enable पूर्णांकs.
	 * If we *करोn't* have something, we'll re-enable beक्रमe leaving here.
	 */
	iwl_ग_लिखो32(trans, CSR_INT_MASK, 0x00000000);

	वापस IRQ_WAKE_THREAD;
पूर्ण

irqवापस_t iwl_pcie_msix_isr(पूर्णांक irq, व्योम *data)
अणु
	वापस IRQ_WAKE_THREAD;
पूर्ण

irqवापस_t iwl_pcie_irq_msix_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा msix_entry *entry = dev_id;
	काष्ठा iwl_trans_pcie *trans_pcie = iwl_pcie_get_trans_pcie(entry);
	काष्ठा iwl_trans *trans = trans_pcie->trans;
	काष्ठा isr_statistics *isr_stats = &trans_pcie->isr_stats;
	u32 पूर्णांकa_fh_msk = ~MSIX_FH_INT_CAUSES_DATA_QUEUE;
	u32 पूर्णांकa_fh, पूर्णांकa_hw;
	bool polling = false;

	अगर (trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_NON_RX)
		पूर्णांकa_fh_msk |= MSIX_FH_INT_CAUSES_Q0;

	अगर (trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_FIRST_RSS)
		पूर्णांकa_fh_msk |= MSIX_FH_INT_CAUSES_Q1;

	lock_map_acquire(&trans->sync_cmd_lockdep_map);

	spin_lock_bh(&trans_pcie->irq_lock);
	पूर्णांकa_fh = iwl_पढ़ो32(trans, CSR_MSIX_FH_INT_CAUSES_AD);
	पूर्णांकa_hw = iwl_पढ़ो32(trans, CSR_MSIX_HW_INT_CAUSES_AD);
	/*
	 * Clear causes रेजिस्टरs to aव्योम being handling the same cause.
	 */
	iwl_ग_लिखो32(trans, CSR_MSIX_FH_INT_CAUSES_AD, पूर्णांकa_fh & पूर्णांकa_fh_msk);
	iwl_ग_लिखो32(trans, CSR_MSIX_HW_INT_CAUSES_AD, पूर्णांकa_hw);
	spin_unlock_bh(&trans_pcie->irq_lock);

	trace_iwlwअगरi_dev_irq_msix(trans->dev, entry, true, पूर्णांकa_fh, पूर्णांकa_hw);

	अगर (unlikely(!(पूर्णांकa_fh | पूर्णांकa_hw))) अणु
		IWL_DEBUG_ISR(trans, "Ignore interrupt, inta == 0\n");
		lock_map_release(&trans->sync_cmd_lockdep_map);
		वापस IRQ_NONE;
	पूर्ण

	अगर (iwl_have_debug_level(IWL_DL_ISR)) अणु
		IWL_DEBUG_ISR(trans,
			      "ISR[%d] inta_fh 0x%08x, enabled (sw) 0x%08x (hw) 0x%08x\n",
			      entry->entry, पूर्णांकa_fh, trans_pcie->fh_mask,
			      iwl_पढ़ो32(trans, CSR_MSIX_FH_INT_MASK_AD));
		अगर (पूर्णांकa_fh & ~trans_pcie->fh_mask)
			IWL_DEBUG_ISR(trans,
				      "We got a masked interrupt (0x%08x)\n",
				      पूर्णांकa_fh & ~trans_pcie->fh_mask);
	पूर्ण

	पूर्णांकa_fh &= trans_pcie->fh_mask;

	अगर ((trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_NON_RX) &&
	    पूर्णांकa_fh & MSIX_FH_INT_CAUSES_Q0) अणु
		local_bh_disable();
		अगर (napi_schedule_prep(&trans_pcie->rxq[0].napi)) अणु
			polling = true;
			__napi_schedule(&trans_pcie->rxq[0].napi);
		पूर्ण
		local_bh_enable();
	पूर्ण

	अगर ((trans_pcie->shared_vec_mask & IWL_SHARED_IRQ_FIRST_RSS) &&
	    पूर्णांकa_fh & MSIX_FH_INT_CAUSES_Q1) अणु
		local_bh_disable();
		अगर (napi_schedule_prep(&trans_pcie->rxq[1].napi)) अणु
			polling = true;
			__napi_schedule(&trans_pcie->rxq[1].napi);
		पूर्ण
		local_bh_enable();
	पूर्ण

	/* This "Tx" DMA channel is used only क्रम loading uCode */
	अगर (पूर्णांकa_fh & MSIX_FH_INT_CAUSES_D2S_CH0_NUM) अणु
		IWL_DEBUG_ISR(trans, "uCode load interrupt\n");
		isr_stats->tx++;
		/*
		 * Wake up uCode load routine,
		 * now that load is complete
		 */
		trans_pcie->ucode_ग_लिखो_complete = true;
		wake_up(&trans_pcie->ucode_ग_लिखो_रुकोq);
	पूर्ण

	/* Error detected by uCode */
	अगर ((पूर्णांकa_fh & MSIX_FH_INT_CAUSES_FH_ERR) ||
	    (पूर्णांकa_hw & MSIX_HW_INT_CAUSES_REG_SW_ERR)) अणु
		IWL_ERR(trans,
			"Microcode SW error detected. Restarting 0x%X.\n",
			पूर्णांकa_fh);
		isr_stats->sw++;
		iwl_pcie_irq_handle_error(trans);
	पूर्ण

	/* After checking FH रेजिस्टर check HW रेजिस्टर */
	अगर (iwl_have_debug_level(IWL_DL_ISR)) अणु
		IWL_DEBUG_ISR(trans,
			      "ISR[%d] inta_hw 0x%08x, enabled (sw) 0x%08x (hw) 0x%08x\n",
			      entry->entry, पूर्णांकa_hw, trans_pcie->hw_mask,
			      iwl_पढ़ो32(trans, CSR_MSIX_HW_INT_MASK_AD));
		अगर (पूर्णांकa_hw & ~trans_pcie->hw_mask)
			IWL_DEBUG_ISR(trans,
				      "We got a masked interrupt 0x%08x\n",
				      पूर्णांकa_hw & ~trans_pcie->hw_mask);
	पूर्ण

	पूर्णांकa_hw &= trans_pcie->hw_mask;

	/* Alive notअगरication via Rx पूर्णांकerrupt will करो the real work */
	अगर (पूर्णांकa_hw & MSIX_HW_INT_CAUSES_REG_ALIVE) अणु
		IWL_DEBUG_ISR(trans, "Alive interrupt\n");
		isr_stats->alive++;
		अगर (trans->trans_cfg->gen2) अणु
			/* We can restock, since firmware configured the RFH */
			iwl_pcie_rxmq_restock(trans, trans_pcie->rxq);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकa_hw & MSIX_HW_INT_CAUSES_REG_WAKEUP) अणु
		u32 sleep_notअगर =
			le32_to_cpu(trans_pcie->prph_info->sleep_notअगर);
		अगर (sleep_notअगर == IWL_D3_SLEEP_STATUS_SUSPEND ||
		    sleep_notअगर == IWL_D3_SLEEP_STATUS_RESUME) अणु
			IWL_DEBUG_ISR(trans,
				      "Sx interrupt: sleep notification = 0x%x\n",
				      sleep_notअगर);
			trans_pcie->sx_complete = true;
			wake_up(&trans_pcie->sx_रुकोq);
		पूर्ण अन्यथा अणु
			/* uCode wakes up after घातer-करोwn sleep */
			IWL_DEBUG_ISR(trans, "Wakeup interrupt\n");
			iwl_pcie_rxq_check_wrptr(trans);
			iwl_pcie_txq_check_wrptrs(trans);

			isr_stats->wakeup++;
		पूर्ण
	पूर्ण

	/* Chip got too hot and stopped itself */
	अगर (पूर्णांकa_hw & MSIX_HW_INT_CAUSES_REG_CT_KILL) अणु
		IWL_ERR(trans, "Microcode CT kill error detected.\n");
		isr_stats->ctसमाप्त++;
	पूर्ण

	/* HW RF KILL चयन toggled */
	अगर (पूर्णांकa_hw & MSIX_HW_INT_CAUSES_REG_RF_KILL)
		iwl_pcie_handle_rfसमाप्त_irq(trans);

	अगर (पूर्णांकa_hw & MSIX_HW_INT_CAUSES_REG_HW_ERR) अणु
		IWL_ERR(trans,
			"Hardware error detected. Restarting.\n");

		isr_stats->hw++;
		trans->dbg.hw_error = true;
		iwl_pcie_irq_handle_error(trans);
	पूर्ण

	अगर (पूर्णांकa_hw & MSIX_HW_INT_CAUSES_REG_RESET_DONE) अणु
		IWL_DEBUG_ISR(trans, "Reset flow completed\n");
		trans_pcie->fw_reset_करोne = true;
		wake_up(&trans_pcie->fw_reset_रुकोq);
	पूर्ण

	अगर (!polling)
		iwl_pcie_clear_irq(trans, entry->entry);

	lock_map_release(&trans->sync_cmd_lockdep_map);

	वापस IRQ_HANDLED;
पूर्ण
