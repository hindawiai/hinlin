<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale MPC85xx, MPC83xx DMA Engine support
 *
 * Copyright (C) 2007-2010 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author:
 *   Zhang Wei <wei.zhang@मुक्तscale.com>, Jul 2007
 *   Ebony Zhu <ebony.zhu@मुक्तscale.com>, May 2007
 *
 * Description:
 *   DMA engine driver क्रम Freescale MPC8540 DMA controller, which is
 *   also fit क्रम MPC8560, MPC8555, MPC8548, MPC8641, and etc.
 *   The support क्रम MPC8349 DMA controller is also added.
 *
 * This driver inकाष्ठाs the DMA controller to issue the PCI Read Multiple
 * command क्रम PCI पढ़ो operations, instead of using the शेष PCI Read Line
 * command. Please be aware that this setting may result in पढ़ो pre-fetching
 * on some platक्रमms.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/fsldma.h>
#समावेश "dmaengine.h"
#समावेश "fsldma.h"

#घोषणा chan_dbg(chan, fmt, arg...)					\
	dev_dbg(chan->dev, "%s: " fmt, chan->name, ##arg)
#घोषणा chan_err(chan, fmt, arg...)					\
	dev_err(chan->dev, "%s: " fmt, chan->name, ##arg)

अटल स्थिर अक्षर msg_ld_oom[] = "No free memory for link descriptor";

/*
 * Register Helpers
 */

अटल व्योम set_sr(काष्ठा fsldma_chan *chan, u32 val)
अणु
	FSL_DMA_OUT(chan, &chan->regs->sr, val, 32);
पूर्ण

अटल u32 get_sr(काष्ठा fsldma_chan *chan)
अणु
	वापस FSL_DMA_IN(chan, &chan->regs->sr, 32);
पूर्ण

अटल व्योम set_mr(काष्ठा fsldma_chan *chan, u32 val)
अणु
	FSL_DMA_OUT(chan, &chan->regs->mr, val, 32);
पूर्ण

अटल u32 get_mr(काष्ठा fsldma_chan *chan)
अणु
	वापस FSL_DMA_IN(chan, &chan->regs->mr, 32);
पूर्ण

अटल व्योम set_cdar(काष्ठा fsldma_chan *chan, dma_addr_t addr)
अणु
	FSL_DMA_OUT(chan, &chan->regs->cdar, addr | FSL_DMA_SNEN, 64);
पूर्ण

अटल dma_addr_t get_cdar(काष्ठा fsldma_chan *chan)
अणु
	वापस FSL_DMA_IN(chan, &chan->regs->cdar, 64) & ~FSL_DMA_SNEN;
पूर्ण

अटल व्योम set_bcr(काष्ठा fsldma_chan *chan, u32 val)
अणु
	FSL_DMA_OUT(chan, &chan->regs->bcr, val, 32);
पूर्ण

अटल u32 get_bcr(काष्ठा fsldma_chan *chan)
अणु
	वापस FSL_DMA_IN(chan, &chan->regs->bcr, 32);
पूर्ण

/*
 * Descriptor Helpers
 */

अटल व्योम set_desc_cnt(काष्ठा fsldma_chan *chan,
				काष्ठा fsl_dma_ld_hw *hw, u32 count)
अणु
	hw->count = CPU_TO_DMA(chan, count, 32);
पूर्ण

अटल व्योम set_desc_src(काष्ठा fsldma_chan *chan,
			 काष्ठा fsl_dma_ld_hw *hw, dma_addr_t src)
अणु
	u64 snoop_bits;

	snoop_bits = ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_85XX)
		? ((u64)FSL_DMA_SATR_SREADTYPE_SNOOP_READ << 32) : 0;
	hw->src_addr = CPU_TO_DMA(chan, snoop_bits | src, 64);
पूर्ण

अटल व्योम set_desc_dst(काष्ठा fsldma_chan *chan,
			 काष्ठा fsl_dma_ld_hw *hw, dma_addr_t dst)
अणु
	u64 snoop_bits;

	snoop_bits = ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_85XX)
		? ((u64)FSL_DMA_DATR_DWRITETYPE_SNOOP_WRITE << 32) : 0;
	hw->dst_addr = CPU_TO_DMA(chan, snoop_bits | dst, 64);
पूर्ण

अटल व्योम set_desc_next(काष्ठा fsldma_chan *chan,
			  काष्ठा fsl_dma_ld_hw *hw, dma_addr_t next)
अणु
	u64 snoop_bits;

	snoop_bits = ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_83XX)
		? FSL_DMA_SNEN : 0;
	hw->next_ln_addr = CPU_TO_DMA(chan, snoop_bits | next, 64);
पूर्ण

अटल व्योम set_ld_eol(काष्ठा fsldma_chan *chan, काष्ठा fsl_desc_sw *desc)
अणु
	u64 snoop_bits;

	snoop_bits = ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_83XX)
		? FSL_DMA_SNEN : 0;

	desc->hw.next_ln_addr = CPU_TO_DMA(chan,
		DMA_TO_CPU(chan, desc->hw.next_ln_addr, 64) | FSL_DMA_EOL
			| snoop_bits, 64);
पूर्ण

/*
 * DMA Engine Hardware Control Helpers
 */

अटल व्योम dma_init(काष्ठा fsldma_chan *chan)
अणु
	/* Reset the channel */
	set_mr(chan, 0);

	चयन (chan->feature & FSL_DMA_IP_MASK) अणु
	हाल FSL_DMA_IP_85XX:
		/* Set the channel to below modes:
		 * EIE - Error पूर्णांकerrupt enable
		 * EOLNIE - End of links पूर्णांकerrupt enable
		 * BWC - Bandwidth sharing among channels
		 */
		set_mr(chan, FSL_DMA_MR_BWC | FSL_DMA_MR_EIE
			| FSL_DMA_MR_EOLNIE);
		अवरोध;
	हाल FSL_DMA_IP_83XX:
		/* Set the channel to below modes:
		 * EOTIE - End-of-transfer पूर्णांकerrupt enable
		 * PRC_RM - PCI पढ़ो multiple
		 */
		set_mr(chan, FSL_DMA_MR_EOTIE | FSL_DMA_MR_PRC_RM);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dma_is_idle(काष्ठा fsldma_chan *chan)
अणु
	u32 sr = get_sr(chan);
	वापस (!(sr & FSL_DMA_SR_CB)) || (sr & FSL_DMA_SR_CH);
पूर्ण

/*
 * Start the DMA controller
 *
 * Preconditions:
 * - the CDAR रेजिस्टर must poपूर्णांक to the start descriptor
 * - the MRn[CS] bit must be cleared
 */
अटल व्योम dma_start(काष्ठा fsldma_chan *chan)
अणु
	u32 mode;

	mode = get_mr(chan);

	अगर (chan->feature & FSL_DMA_CHAN_PAUSE_EXT) अणु
		set_bcr(chan, 0);
		mode |= FSL_DMA_MR_EMP_EN;
	पूर्ण अन्यथा अणु
		mode &= ~FSL_DMA_MR_EMP_EN;
	पूर्ण

	अगर (chan->feature & FSL_DMA_CHAN_START_EXT) अणु
		mode |= FSL_DMA_MR_EMS_EN;
	पूर्ण अन्यथा अणु
		mode &= ~FSL_DMA_MR_EMS_EN;
		mode |= FSL_DMA_MR_CS;
	पूर्ण

	set_mr(chan, mode);
पूर्ण

अटल व्योम dma_halt(काष्ठा fsldma_chan *chan)
अणु
	u32 mode;
	पूर्णांक i;

	/* पढ़ो the mode रेजिस्टर */
	mode = get_mr(chan);

	/*
	 * The 85xx controller supports channel पात, which will stop
	 * the current transfer. On 83xx, this bit is the transfer error
	 * mask bit, which should not be changed.
	 */
	अगर ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_85XX) अणु
		mode |= FSL_DMA_MR_CA;
		set_mr(chan, mode);

		mode &= ~FSL_DMA_MR_CA;
	पूर्ण

	/* stop the DMA controller */
	mode &= ~(FSL_DMA_MR_CS | FSL_DMA_MR_EMS_EN);
	set_mr(chan, mode);

	/* रुको क्रम the DMA controller to become idle */
	क्रम (i = 0; i < 100; i++) अणु
		अगर (dma_is_idle(chan))
			वापस;

		udelay(10);
	पूर्ण

	अगर (!dma_is_idle(chan))
		chan_err(chan, "DMA halt timeout!\n");
पूर्ण

/**
 * fsl_chan_set_src_loop_size - Set source address hold transfer size
 * @chan : Freescale DMA channel
 * @size     : Address loop size, 0 क्रम disable loop
 *
 * The set source address hold transfer size. The source
 * address hold or loop transfer size is when the DMA transfer
 * data from source address (SA), अगर the loop size is 4, the DMA will
 * पढ़ो data from SA, SA + 1, SA + 2, SA + 3, then loop back to SA,
 * SA + 1 ... and so on.
 */
अटल व्योम fsl_chan_set_src_loop_size(काष्ठा fsldma_chan *chan, पूर्णांक size)
अणु
	u32 mode;

	mode = get_mr(chan);

	चयन (size) अणु
	हाल 0:
		mode &= ~FSL_DMA_MR_SAHE;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		mode &= ~FSL_DMA_MR_SAHTS_MASK;
		mode |= FSL_DMA_MR_SAHE | (__ilog2(size) << 14);
		अवरोध;
	पूर्ण

	set_mr(chan, mode);
पूर्ण

/**
 * fsl_chan_set_dst_loop_size - Set destination address hold transfer size
 * @chan : Freescale DMA channel
 * @size     : Address loop size, 0 क्रम disable loop
 *
 * The set destination address hold transfer size. The destination
 * address hold or loop transfer size is when the DMA transfer
 * data to destination address (TA), अगर the loop size is 4, the DMA will
 * ग_लिखो data to TA, TA + 1, TA + 2, TA + 3, then loop back to TA,
 * TA + 1 ... and so on.
 */
अटल व्योम fsl_chan_set_dst_loop_size(काष्ठा fsldma_chan *chan, पूर्णांक size)
अणु
	u32 mode;

	mode = get_mr(chan);

	चयन (size) अणु
	हाल 0:
		mode &= ~FSL_DMA_MR_DAHE;
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		mode &= ~FSL_DMA_MR_DAHTS_MASK;
		mode |= FSL_DMA_MR_DAHE | (__ilog2(size) << 16);
		अवरोध;
	पूर्ण

	set_mr(chan, mode);
पूर्ण

/**
 * fsl_chan_set_request_count - Set DMA Request Count क्रम बाह्यal control
 * @chan : Freescale DMA channel
 * @size     : Number of bytes to transfer in a single request
 *
 * The Freescale DMA channel can be controlled by the बाह्यal संकेत DREQ#.
 * The DMA request count is how many bytes are allowed to transfer beक्रमe
 * pausing the channel, after which a new निश्चितion of DREQ# resumes channel
 * operation.
 *
 * A size of 0 disables बाह्यal छोड़ो control. The maximum size is 1024.
 */
अटल व्योम fsl_chan_set_request_count(काष्ठा fsldma_chan *chan, पूर्णांक size)
अणु
	u32 mode;

	BUG_ON(size > 1024);

	mode = get_mr(chan);
	mode &= ~FSL_DMA_MR_BWC_MASK;
	mode |= (__ilog2(size) << 24) & FSL_DMA_MR_BWC_MASK;

	set_mr(chan, mode);
पूर्ण

/**
 * fsl_chan_toggle_ext_छोड़ो - Toggle channel बाह्यal छोड़ो status
 * @chan : Freescale DMA channel
 * @enable   : 0 is disabled, 1 is enabled.
 *
 * The Freescale DMA channel can be controlled by the बाह्यal संकेत DREQ#.
 * The DMA Request Count feature should be used in addition to this feature
 * to set the number of bytes to transfer beक्रमe pausing the channel.
 */
अटल व्योम fsl_chan_toggle_ext_छोड़ो(काष्ठा fsldma_chan *chan, पूर्णांक enable)
अणु
	अगर (enable)
		chan->feature |= FSL_DMA_CHAN_PAUSE_EXT;
	अन्यथा
		chan->feature &= ~FSL_DMA_CHAN_PAUSE_EXT;
पूर्ण

/**
 * fsl_chan_toggle_ext_start - Toggle channel बाह्यal start status
 * @chan : Freescale DMA channel
 * @enable   : 0 is disabled, 1 is enabled.
 *
 * If enable the बाह्यal start, the channel can be started by an
 * बाह्यal DMA start pin. So the dma_start() करोes not start the
 * transfer immediately. The DMA channel will रुको क्रम the
 * control pin निश्चितed.
 */
अटल व्योम fsl_chan_toggle_ext_start(काष्ठा fsldma_chan *chan, पूर्णांक enable)
अणु
	अगर (enable)
		chan->feature |= FSL_DMA_CHAN_START_EXT;
	अन्यथा
		chan->feature &= ~FSL_DMA_CHAN_START_EXT;
पूर्ण

पूर्णांक fsl_dma_बाह्यal_start(काष्ठा dma_chan *dchan, पूर्णांक enable)
अणु
	काष्ठा fsldma_chan *chan;

	अगर (!dchan)
		वापस -EINVAL;

	chan = to_fsl_chan(dchan);

	fsl_chan_toggle_ext_start(chan, enable);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_dma_बाह्यal_start);

अटल व्योम append_ld_queue(काष्ठा fsldma_chan *chan, काष्ठा fsl_desc_sw *desc)
अणु
	काष्ठा fsl_desc_sw *tail = to_fsl_desc(chan->ld_pending.prev);

	अगर (list_empty(&chan->ld_pending))
		जाओ out_splice;

	/*
	 * Add the hardware descriptor to the chain of hardware descriptors
	 * that alपढ़ोy exists in memory.
	 *
	 * This will un-set the EOL bit of the existing transaction, and the
	 * last link in this transaction will become the EOL descriptor.
	 */
	set_desc_next(chan, &tail->hw, desc->async_tx.phys);

	/*
	 * Add the software descriptor and all children to the list
	 * of pending transactions
	 */
out_splice:
	list_splice_tail_init(&desc->tx_list, &chan->ld_pending);
पूर्ण

अटल dma_cookie_t fsl_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा fsldma_chan *chan = to_fsl_chan(tx->chan);
	काष्ठा fsl_desc_sw *desc = tx_to_fsl_desc(tx);
	काष्ठा fsl_desc_sw *child;
	dma_cookie_t cookie = -EINVAL;

	spin_lock_bh(&chan->desc_lock);

#अगर_घोषित CONFIG_PM
	अगर (unlikely(chan->pm_state != RUNNING)) अणु
		chan_dbg(chan, "cannot submit due to suspend\n");
		spin_unlock_bh(&chan->desc_lock);
		वापस -1;
	पूर्ण
#पूर्ण_अगर

	/*
	 * assign cookies to all of the software descriptors
	 * that make up this transaction
	 */
	list_क्रम_each_entry(child, &desc->tx_list, node) अणु
		cookie = dma_cookie_assign(&child->async_tx);
	पूर्ण

	/* put this transaction onto the tail of the pending queue */
	append_ld_queue(chan, desc);

	spin_unlock_bh(&chan->desc_lock);

	वापस cookie;
पूर्ण

/**
 * fsl_dma_मुक्त_descriptor - Free descriptor from channel's DMA pool.
 * @chan : Freescale DMA channel
 * @desc: descriptor to be मुक्तd
 */
अटल व्योम fsl_dma_मुक्त_descriptor(काष्ठा fsldma_chan *chan,
		काष्ठा fsl_desc_sw *desc)
अणु
	list_del(&desc->node);
	chan_dbg(chan, "LD %p free\n", desc);
	dma_pool_मुक्त(chan->desc_pool, desc, desc->async_tx.phys);
पूर्ण

/**
 * fsl_dma_alloc_descriptor - Allocate descriptor from channel's DMA pool.
 * @chan : Freescale DMA channel
 *
 * Return - The descriptor allocated. शून्य क्रम failed.
 */
अटल काष्ठा fsl_desc_sw *fsl_dma_alloc_descriptor(काष्ठा fsldma_chan *chan)
अणु
	काष्ठा fsl_desc_sw *desc;
	dma_addr_t pdesc;

	desc = dma_pool_zalloc(chan->desc_pool, GFP_ATOMIC, &pdesc);
	अगर (!desc) अणु
		chan_dbg(chan, "out of memory for link descriptor\n");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&desc->tx_list);
	dma_async_tx_descriptor_init(&desc->async_tx, &chan->common);
	desc->async_tx.tx_submit = fsl_dma_tx_submit;
	desc->async_tx.phys = pdesc;

	chan_dbg(chan, "LD %p allocated\n", desc);

	वापस desc;
पूर्ण

/**
 * fsldma_clean_completed_descriptor - मुक्त all descriptors which
 * has been completed and acked
 * @chan: Freescale DMA channel
 *
 * This function is used on all completed and acked descriptors.
 * All descriptors should only be मुक्तd in this function.
 */
अटल व्योम fsldma_clean_completed_descriptor(काष्ठा fsldma_chan *chan)
अणु
	काष्ठा fsl_desc_sw *desc, *_desc;

	/* Run the callback क्रम each descriptor, in order */
	list_क्रम_each_entry_safe(desc, _desc, &chan->ld_completed, node)
		अगर (async_tx_test_ack(&desc->async_tx))
			fsl_dma_मुक्त_descriptor(chan, desc);
पूर्ण

/**
 * fsldma_run_tx_complete_actions - cleanup a single link descriptor
 * @chan: Freescale DMA channel
 * @desc: descriptor to cleanup and मुक्त
 * @cookie: Freescale DMA transaction identअगरier
 *
 * This function is used on a descriptor which has been executed by the DMA
 * controller. It will run any callbacks, submit any dependencies.
 */
अटल dma_cookie_t fsldma_run_tx_complete_actions(काष्ठा fsldma_chan *chan,
		काष्ठा fsl_desc_sw *desc, dma_cookie_t cookie)
अणु
	काष्ठा dma_async_tx_descriptor *txd = &desc->async_tx;
	dma_cookie_t ret = cookie;

	BUG_ON(txd->cookie < 0);

	अगर (txd->cookie > 0) अणु
		ret = txd->cookie;

		dma_descriptor_unmap(txd);
		/* Run the link descriptor callback function */
		dmaengine_desc_get_callback_invoke(txd, शून्य);
	पूर्ण

	/* Run any dependencies */
	dma_run_dependencies(txd);

	वापस ret;
पूर्ण

/**
 * fsldma_clean_running_descriptor - move the completed descriptor from
 * ld_running to ld_completed
 * @chan: Freescale DMA channel
 * @desc: the descriptor which is completed
 *
 * Free the descriptor directly अगर acked by async_tx api, or move it to
 * queue ld_completed.
 */
अटल व्योम fsldma_clean_running_descriptor(काष्ठा fsldma_chan *chan,
		काष्ठा fsl_desc_sw *desc)
अणु
	/* Remove from the list of transactions */
	list_del(&desc->node);

	/*
	 * the client is allowed to attach dependent operations
	 * until 'ack' is set
	 */
	अगर (!async_tx_test_ack(&desc->async_tx)) अणु
		/*
		 * Move this descriptor to the list of descriptors which is
		 * completed, but still aरुकोing the 'ack' bit to be set.
		 */
		list_add_tail(&desc->node, &chan->ld_completed);
		वापस;
	पूर्ण

	dma_pool_मुक्त(chan->desc_pool, desc, desc->async_tx.phys);
पूर्ण

/**
 * fsl_chan_xfer_ld_queue - transfer any pending transactions
 * @chan : Freescale DMA channel
 *
 * HARDWARE STATE: idle
 * LOCKING: must hold chan->desc_lock
 */
अटल व्योम fsl_chan_xfer_ld_queue(काष्ठा fsldma_chan *chan)
अणु
	काष्ठा fsl_desc_sw *desc;

	/*
	 * If the list of pending descriptors is empty, then we
	 * करोn't need to करो any work at all
	 */
	अगर (list_empty(&chan->ld_pending)) अणु
		chan_dbg(chan, "no pending LDs\n");
		वापस;
	पूर्ण

	/*
	 * The DMA controller is not idle, which means that the पूर्णांकerrupt
	 * handler will start any queued transactions when it runs after
	 * this transaction finishes
	 */
	अगर (!chan->idle) अणु
		chan_dbg(chan, "DMA controller still busy\n");
		वापस;
	पूर्ण

	/*
	 * If there are some link descriptors which have not been
	 * transferred, we need to start the controller
	 */

	/*
	 * Move all elements from the queue of pending transactions
	 * onto the list of running transactions
	 */
	chan_dbg(chan, "idle, starting controller\n");
	desc = list_first_entry(&chan->ld_pending, काष्ठा fsl_desc_sw, node);
	list_splice_tail_init(&chan->ld_pending, &chan->ld_running);

	/*
	 * The 85xx DMA controller करोesn't clear the channel start bit
	 * स्वतःmatically at the end of a transfer. Thereक्रमe we must clear
	 * it in software beक्रमe starting the transfer.
	 */
	अगर ((chan->feature & FSL_DMA_IP_MASK) == FSL_DMA_IP_85XX) अणु
		u32 mode;

		mode = get_mr(chan);
		mode &= ~FSL_DMA_MR_CS;
		set_mr(chan, mode);
	पूर्ण

	/*
	 * Program the descriptor's address पूर्णांकo the DMA controller,
	 * then start the DMA transaction
	 */
	set_cdar(chan, desc->async_tx.phys);
	get_cdar(chan);

	dma_start(chan);
	chan->idle = false;
पूर्ण

/**
 * fsldma_cleanup_descriptors - cleanup link descriptors which are completed
 * and move them to ld_completed to मुक्त until flag 'ack' is set
 * @chan: Freescale DMA channel
 *
 * This function is used on descriptors which have been executed by the DMA
 * controller. It will run any callbacks, submit any dependencies, then
 * मुक्त these descriptors अगर flag 'ack' is set.
 */
अटल व्योम fsldma_cleanup_descriptors(काष्ठा fsldma_chan *chan)
अणु
	काष्ठा fsl_desc_sw *desc, *_desc;
	dma_cookie_t cookie = 0;
	dma_addr_t curr_phys = get_cdar(chan);
	पूर्णांक seen_current = 0;

	fsldma_clean_completed_descriptor(chan);

	/* Run the callback क्रम each descriptor, in order */
	list_क्रम_each_entry_safe(desc, _desc, &chan->ld_running, node) अणु
		/*
		 * करो not advance past the current descriptor loaded पूर्णांकo the
		 * hardware channel, subsequent descriptors are either in
		 * process or have not been submitted
		 */
		अगर (seen_current)
			अवरोध;

		/*
		 * stop the search अगर we reach the current descriptor and the
		 * channel is busy
		 */
		अगर (desc->async_tx.phys == curr_phys) अणु
			seen_current = 1;
			अगर (!dma_is_idle(chan))
				अवरोध;
		पूर्ण

		cookie = fsldma_run_tx_complete_actions(chan, desc, cookie);

		fsldma_clean_running_descriptor(chan, desc);
	पूर्ण

	/*
	 * Start any pending transactions स्वतःmatically
	 *
	 * In the ideal हाल, we keep the DMA controller busy जबतक we go
	 * ahead and मुक्त the descriptors below.
	 */
	fsl_chan_xfer_ld_queue(chan);

	अगर (cookie > 0)
		chan->common.completed_cookie = cookie;
पूर्ण

/**
 * fsl_dma_alloc_chan_resources - Allocate resources क्रम DMA channel.
 * @chan : Freescale DMA channel
 *
 * This function will create a dma pool क्रम descriptor allocation.
 *
 * Return - The number of descriptors allocated.
 */
अटल पूर्णांक fsl_dma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा fsldma_chan *chan = to_fsl_chan(dchan);

	/* Has this channel alपढ़ोy been allocated? */
	अगर (chan->desc_pool)
		वापस 1;

	/*
	 * We need the descriptor to be aligned to 32bytes
	 * क्रम meeting FSL DMA specअगरication requirement.
	 */
	chan->desc_pool = dma_pool_create(chan->name, chan->dev,
					  माप(काष्ठा fsl_desc_sw),
					  __alignof__(काष्ठा fsl_desc_sw), 0);
	अगर (!chan->desc_pool) अणु
		chan_err(chan, "unable to allocate descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	/* there is at least one descriptor मुक्त to be allocated */
	वापस 1;
पूर्ण

/**
 * fsldma_मुक्त_desc_list - Free all descriptors in a queue
 * @chan: Freescae DMA channel
 * @list: the list to मुक्त
 *
 * LOCKING: must hold chan->desc_lock
 */
अटल व्योम fsldma_मुक्त_desc_list(काष्ठा fsldma_chan *chan,
				  काष्ठा list_head *list)
अणु
	काष्ठा fsl_desc_sw *desc, *_desc;

	list_क्रम_each_entry_safe(desc, _desc, list, node)
		fsl_dma_मुक्त_descriptor(chan, desc);
पूर्ण

अटल व्योम fsldma_मुक्त_desc_list_reverse(काष्ठा fsldma_chan *chan,
					  काष्ठा list_head *list)
अणु
	काष्ठा fsl_desc_sw *desc, *_desc;

	list_क्रम_each_entry_safe_reverse(desc, _desc, list, node)
		fsl_dma_मुक्त_descriptor(chan, desc);
पूर्ण

/**
 * fsl_dma_मुक्त_chan_resources - Free all resources of the channel.
 * @chan : Freescale DMA channel
 */
अटल व्योम fsl_dma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा fsldma_chan *chan = to_fsl_chan(dchan);

	chan_dbg(chan, "free all channel resources\n");
	spin_lock_bh(&chan->desc_lock);
	fsldma_cleanup_descriptors(chan);
	fsldma_मुक्त_desc_list(chan, &chan->ld_pending);
	fsldma_मुक्त_desc_list(chan, &chan->ld_running);
	fsldma_मुक्त_desc_list(chan, &chan->ld_completed);
	spin_unlock_bh(&chan->desc_lock);

	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
fsl_dma_prep_स_नकल(काष्ठा dma_chan *dchan,
	dma_addr_t dma_dst, dma_addr_t dma_src,
	माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा fsldma_chan *chan;
	काष्ठा fsl_desc_sw *first = शून्य, *prev = शून्य, *new;
	माप_प्रकार copy;

	अगर (!dchan)
		वापस शून्य;

	अगर (!len)
		वापस शून्य;

	chan = to_fsl_chan(dchan);

	करो अणु

		/* Allocate the link descriptor from DMA pool */
		new = fsl_dma_alloc_descriptor(chan);
		अगर (!new) अणु
			chan_err(chan, "%s\n", msg_ld_oom);
			जाओ fail;
		पूर्ण

		copy = min(len, (माप_प्रकार)FSL_DMA_BCR_MAX_CNT);

		set_desc_cnt(chan, &new->hw, copy);
		set_desc_src(chan, &new->hw, dma_src);
		set_desc_dst(chan, &new->hw, dma_dst);

		अगर (!first)
			first = new;
		अन्यथा
			set_desc_next(chan, &prev->hw, new->async_tx.phys);

		new->async_tx.cookie = 0;
		async_tx_ack(&new->async_tx);

		prev = new;
		len -= copy;
		dma_src += copy;
		dma_dst += copy;

		/* Insert the link descriptor to the LD ring */
		list_add_tail(&new->node, &first->tx_list);
	पूर्ण जबतक (len);

	new->async_tx.flags = flags; /* client is in control of this ack */
	new->async_tx.cookie = -EBUSY;

	/* Set End-of-link to the last link descriptor of new list */
	set_ld_eol(chan, new);

	वापस &first->async_tx;

fail:
	अगर (!first)
		वापस शून्य;

	fsldma_मुक्त_desc_list_reverse(chan, &first->tx_list);
	वापस शून्य;
पूर्ण

अटल पूर्णांक fsl_dma_device_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा fsldma_chan *chan;

	अगर (!dchan)
		वापस -EINVAL;

	chan = to_fsl_chan(dchan);

	spin_lock_bh(&chan->desc_lock);

	/* Halt the DMA engine */
	dma_halt(chan);

	/* Remove and मुक्त all of the descriptors in the LD queue */
	fsldma_मुक्त_desc_list(chan, &chan->ld_pending);
	fsldma_मुक्त_desc_list(chan, &chan->ld_running);
	fsldma_मुक्त_desc_list(chan, &chan->ld_completed);
	chan->idle = true;

	spin_unlock_bh(&chan->desc_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_dma_device_config(काष्ठा dma_chan *dchan,
				 काष्ठा dma_slave_config *config)
अणु
	काष्ठा fsldma_chan *chan;
	पूर्णांक size;

	अगर (!dchan)
		वापस -EINVAL;

	chan = to_fsl_chan(dchan);

	/* make sure the channel supports setting burst size */
	अगर (!chan->set_request_count)
		वापस -ENXIO;

	/* we set the controller burst size depending on direction */
	अगर (config->direction == DMA_MEM_TO_DEV)
		size = config->dst_addr_width * config->dst_maxburst;
	अन्यथा
		size = config->src_addr_width * config->src_maxburst;

	chan->set_request_count(chan, size);
	वापस 0;
पूर्ण


/**
 * fsl_dma_स_नकल_issue_pending - Issue the DMA start command
 * @chan : Freescale DMA channel
 */
अटल व्योम fsl_dma_स_नकल_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा fsldma_chan *chan = to_fsl_chan(dchan);

	spin_lock_bh(&chan->desc_lock);
	fsl_chan_xfer_ld_queue(chan);
	spin_unlock_bh(&chan->desc_lock);
पूर्ण

/**
 * fsl_tx_status - Determine the DMA status
 * @chan : Freescale DMA channel
 */
अटल क्रमागत dma_status fsl_tx_status(काष्ठा dma_chan *dchan,
					dma_cookie_t cookie,
					काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा fsldma_chan *chan = to_fsl_chan(dchan);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(dchan, cookie, txstate);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	spin_lock_bh(&chan->desc_lock);
	fsldma_cleanup_descriptors(chan);
	spin_unlock_bh(&chan->desc_lock);

	वापस dma_cookie_status(dchan, cookie, txstate);
पूर्ण

/*----------------------------------------------------------------------------*/
/* Interrupt Handling                                                         */
/*----------------------------------------------------------------------------*/

अटल irqवापस_t fsldma_chan_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fsldma_chan *chan = data;
	u32 stat;

	/* save and clear the status रेजिस्टर */
	stat = get_sr(chan);
	set_sr(chan, stat);
	chan_dbg(chan, "irq: stat = 0x%x\n", stat);

	/* check that this was really our device */
	stat &= ~(FSL_DMA_SR_CB | FSL_DMA_SR_CH);
	अगर (!stat)
		वापस IRQ_NONE;

	अगर (stat & FSL_DMA_SR_TE)
		chan_err(chan, "Transfer Error!\n");

	/*
	 * Programming Error
	 * The DMA_INTERRUPT async_tx is a शून्य transfer, which will
	 * trigger a PE पूर्णांकerrupt.
	 */
	अगर (stat & FSL_DMA_SR_PE) अणु
		chan_dbg(chan, "irq: Programming Error INT\n");
		stat &= ~FSL_DMA_SR_PE;
		अगर (get_bcr(chan) != 0)
			chan_err(chan, "Programming Error!\n");
	पूर्ण

	/*
	 * For MPC8349, EOCDI event need to update cookie
	 * and start the next transfer अगर it exist.
	 */
	अगर (stat & FSL_DMA_SR_EOCDI) अणु
		chan_dbg(chan, "irq: End-of-Chain link INT\n");
		stat &= ~FSL_DMA_SR_EOCDI;
	पूर्ण

	/*
	 * If it current transfer is the end-of-transfer,
	 * we should clear the Channel Start bit क्रम
	 * prepare next transfer.
	 */
	अगर (stat & FSL_DMA_SR_EOLNI) अणु
		chan_dbg(chan, "irq: End-of-link INT\n");
		stat &= ~FSL_DMA_SR_EOLNI;
	पूर्ण

	/* check that the DMA controller is really idle */
	अगर (!dma_is_idle(chan))
		chan_err(chan, "irq: controller not idle!\n");

	/* check that we handled all of the bits */
	अगर (stat)
		chan_err(chan, "irq: unhandled sr 0x%08x\n", stat);

	/*
	 * Schedule the tasklet to handle all cleanup of the current
	 * transaction. It will start a new transaction अगर there is
	 * one pending.
	 */
	tasklet_schedule(&chan->tasklet);
	chan_dbg(chan, "irq: Exit\n");
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dma_करो_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा fsldma_chan *chan = from_tasklet(chan, t, tasklet);

	chan_dbg(chan, "tasklet entry\n");

	spin_lock(&chan->desc_lock);

	/* the hardware is now idle and पढ़ोy क्रम more */
	chan->idle = true;

	/* Run all cleanup क्रम descriptors which have been completed */
	fsldma_cleanup_descriptors(chan);

	spin_unlock(&chan->desc_lock);

	chan_dbg(chan, "tasklet exit\n");
पूर्ण

अटल irqवापस_t fsldma_ctrl_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा fsldma_device *fdev = data;
	काष्ठा fsldma_chan *chan;
	अचिन्हित पूर्णांक handled = 0;
	u32 gsr, mask;
	पूर्णांक i;

	gsr = (fdev->feature & FSL_DMA_BIG_ENDIAN) ? in_be32(fdev->regs)
						   : in_le32(fdev->regs);
	mask = 0xff000000;
	dev_dbg(fdev->dev, "IRQ: gsr 0x%.8x\n", gsr);

	क्रम (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) अणु
		chan = fdev->chan[i];
		अगर (!chan)
			जारी;

		अगर (gsr & mask) अणु
			dev_dbg(fdev->dev, "IRQ: chan %d\n", chan->id);
			fsldma_chan_irq(irq, chan);
			handled++;
		पूर्ण

		gsr &= ~mask;
		mask >>= 8;
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम fsldma_मुक्त_irqs(काष्ठा fsldma_device *fdev)
अणु
	काष्ठा fsldma_chan *chan;
	पूर्णांक i;

	अगर (fdev->irq) अणु
		dev_dbg(fdev->dev, "free per-controller IRQ\n");
		मुक्त_irq(fdev->irq, fdev);
		वापस;
	पूर्ण

	क्रम (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) अणु
		chan = fdev->chan[i];
		अगर (chan && chan->irq) अणु
			chan_dbg(chan, "free per-channel IRQ\n");
			मुक्त_irq(chan->irq, chan);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक fsldma_request_irqs(काष्ठा fsldma_device *fdev)
अणु
	काष्ठा fsldma_chan *chan;
	पूर्णांक ret;
	पूर्णांक i;

	/* अगर we have a per-controller IRQ, use that */
	अगर (fdev->irq) अणु
		dev_dbg(fdev->dev, "request per-controller IRQ\n");
		ret = request_irq(fdev->irq, fsldma_ctrl_irq, IRQF_SHARED,
				  "fsldma-controller", fdev);
		वापस ret;
	पूर्ण

	/* no per-controller IRQ, use the per-channel IRQs */
	क्रम (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) अणु
		chan = fdev->chan[i];
		अगर (!chan)
			जारी;

		अगर (!chan->irq) अणु
			chan_err(chan, "interrupts property missing in device tree\n");
			ret = -ENODEV;
			जाओ out_unwind;
		पूर्ण

		chan_dbg(chan, "request per-channel IRQ\n");
		ret = request_irq(chan->irq, fsldma_chan_irq, IRQF_SHARED,
				  "fsldma-chan", chan);
		अगर (ret) अणु
			chan_err(chan, "unable to request per-channel IRQ\n");
			जाओ out_unwind;
		पूर्ण
	पूर्ण

	वापस 0;

out_unwind:
	क्रम (/* none */; i >= 0; i--) अणु
		chan = fdev->chan[i];
		अगर (!chan)
			जारी;

		अगर (!chan->irq)
			जारी;

		मुक्त_irq(chan->irq, chan);
	पूर्ण

	वापस ret;
पूर्ण

/*----------------------------------------------------------------------------*/
/* OpenFirmware Subप्रणाली                                                     */
/*----------------------------------------------------------------------------*/

अटल पूर्णांक fsl_dma_chan_probe(काष्ठा fsldma_device *fdev,
	काष्ठा device_node *node, u32 feature, स्थिर अक्षर *compatible)
अणु
	काष्ठा fsldma_chan *chan;
	काष्ठा resource res;
	पूर्णांक err;

	/* alloc channel */
	chan = kzalloc(माप(*chan), GFP_KERNEL);
	अगर (!chan) अणु
		err = -ENOMEM;
		जाओ out_वापस;
	पूर्ण

	/* ioremap रेजिस्टरs क्रम use */
	chan->regs = of_iomap(node, 0);
	अगर (!chan->regs) अणु
		dev_err(fdev->dev, "unable to ioremap registers\n");
		err = -ENOMEM;
		जाओ out_मुक्त_chan;
	पूर्ण

	err = of_address_to_resource(node, 0, &res);
	अगर (err) अणु
		dev_err(fdev->dev, "unable to find 'reg' property\n");
		जाओ out_iounmap_regs;
	पूर्ण

	chan->feature = feature;
	अगर (!fdev->feature)
		fdev->feature = chan->feature;

	/*
	 * If the DMA device's feature is dअगरferent than the feature
	 * of its channels, report the bug
	 */
	WARN_ON(fdev->feature != chan->feature);

	chan->dev = fdev->dev;
	chan->id = (res.start & 0xfff) < 0x300 ?
		   ((res.start - 0x100) & 0xfff) >> 7 :
		   ((res.start - 0x200) & 0xfff) >> 7;
	अगर (chan->id >= FSL_DMA_MAX_CHANS_PER_DEVICE) अणु
		dev_err(fdev->dev, "too many channels for device\n");
		err = -EINVAL;
		जाओ out_iounmap_regs;
	पूर्ण

	fdev->chan[chan->id] = chan;
	tasklet_setup(&chan->tasklet, dma_करो_tasklet);
	snम_लिखो(chan->name, माप(chan->name), "chan%d", chan->id);

	/* Initialize the channel */
	dma_init(chan);

	/* Clear cdar रेजिस्टरs */
	set_cdar(chan, 0);

	चयन (chan->feature & FSL_DMA_IP_MASK) अणु
	हाल FSL_DMA_IP_85XX:
		chan->toggle_ext_छोड़ो = fsl_chan_toggle_ext_छोड़ो;
		fallthrough;
	हाल FSL_DMA_IP_83XX:
		chan->toggle_ext_start = fsl_chan_toggle_ext_start;
		chan->set_src_loop_size = fsl_chan_set_src_loop_size;
		chan->set_dst_loop_size = fsl_chan_set_dst_loop_size;
		chan->set_request_count = fsl_chan_set_request_count;
	पूर्ण

	spin_lock_init(&chan->desc_lock);
	INIT_LIST_HEAD(&chan->ld_pending);
	INIT_LIST_HEAD(&chan->ld_running);
	INIT_LIST_HEAD(&chan->ld_completed);
	chan->idle = true;
#अगर_घोषित CONFIG_PM
	chan->pm_state = RUNNING;
#पूर्ण_अगर

	chan->common.device = &fdev->common;
	dma_cookie_init(&chan->common);

	/* find the IRQ line, अगर it exists in the device tree */
	chan->irq = irq_of_parse_and_map(node, 0);

	/* Add the channel to DMA device channel list */
	list_add_tail(&chan->common.device_node, &fdev->common.channels);

	dev_info(fdev->dev, "#%d (%s), irq %d\n", chan->id, compatible,
		 chan->irq ? chan->irq : fdev->irq);

	वापस 0;

out_iounmap_regs:
	iounmap(chan->regs);
out_मुक्त_chan:
	kमुक्त(chan);
out_वापस:
	वापस err;
पूर्ण

अटल व्योम fsl_dma_chan_हटाओ(काष्ठा fsldma_chan *chan)
अणु
	irq_dispose_mapping(chan->irq);
	list_del(&chan->common.device_node);
	iounmap(chan->regs);
	kमुक्त(chan);
पूर्ण

अटल पूर्णांक fsldma_of_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fsldma_device *fdev;
	काष्ठा device_node *child;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	fdev = kzalloc(माप(*fdev), GFP_KERNEL);
	अगर (!fdev) अणु
		err = -ENOMEM;
		जाओ out_वापस;
	पूर्ण

	fdev->dev = &op->dev;
	INIT_LIST_HEAD(&fdev->common.channels);

	/* ioremap the रेजिस्टरs क्रम use */
	fdev->regs = of_iomap(op->dev.of_node, 0);
	अगर (!fdev->regs) अणु
		dev_err(&op->dev, "unable to ioremap registers\n");
		err = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	/* map the channel IRQ अगर it exists, but करोn't hookup the handler yet */
	fdev->irq = irq_of_parse_and_map(op->dev.of_node, 0);

	dma_cap_set(DMA_MEMCPY, fdev->common.cap_mask);
	dma_cap_set(DMA_SLAVE, fdev->common.cap_mask);
	fdev->common.device_alloc_chan_resources = fsl_dma_alloc_chan_resources;
	fdev->common.device_मुक्त_chan_resources = fsl_dma_मुक्त_chan_resources;
	fdev->common.device_prep_dma_स_नकल = fsl_dma_prep_स_नकल;
	fdev->common.device_tx_status = fsl_tx_status;
	fdev->common.device_issue_pending = fsl_dma_स_नकल_issue_pending;
	fdev->common.device_config = fsl_dma_device_config;
	fdev->common.device_terminate_all = fsl_dma_device_terminate_all;
	fdev->common.dev = &op->dev;

	fdev->common.src_addr_widths = FSL_DMA_BUSWIDTHS;
	fdev->common.dst_addr_widths = FSL_DMA_BUSWIDTHS;
	fdev->common.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	fdev->common.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;

	dma_set_mask(&(op->dev), DMA_BIT_MASK(36));

	platक्रमm_set_drvdata(op, fdev);

	/*
	 * We cannot use of_platक्रमm_bus_probe() because there is no
	 * of_platक्रमm_bus_हटाओ(). Instead, we manually instantiate every DMA
	 * channel object.
	 */
	क्रम_each_child_of_node(op->dev.of_node, child) अणु
		अगर (of_device_is_compatible(child, "fsl,eloplus-dma-channel")) अणु
			fsl_dma_chan_probe(fdev, child,
				FSL_DMA_IP_85XX | FSL_DMA_BIG_ENDIAN,
				"fsl,eloplus-dma-channel");
		पूर्ण

		अगर (of_device_is_compatible(child, "fsl,elo-dma-channel")) अणु
			fsl_dma_chan_probe(fdev, child,
				FSL_DMA_IP_83XX | FSL_DMA_LITTLE_ENDIAN,
				"fsl,elo-dma-channel");
		पूर्ण
	पूर्ण

	/*
	 * Hookup the IRQ handler(s)
	 *
	 * If we have a per-controller पूर्णांकerrupt, we prefer that to the
	 * per-channel पूर्णांकerrupts to reduce the number of shared पूर्णांकerrupt
	 * handlers on the same IRQ line
	 */
	err = fsldma_request_irqs(fdev);
	अगर (err) अणु
		dev_err(fdev->dev, "unable to request IRQs\n");
		जाओ out_मुक्त_fdev;
	पूर्ण

	dma_async_device_रेजिस्टर(&fdev->common);
	वापस 0;

out_मुक्त_fdev:
	क्रम (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) अणु
		अगर (fdev->chan[i])
			fsl_dma_chan_हटाओ(fdev->chan[i]);
	पूर्ण
	irq_dispose_mapping(fdev->irq);
	iounmap(fdev->regs);
out_मुक्त:
	kमुक्त(fdev);
out_वापस:
	वापस err;
पूर्ण

अटल पूर्णांक fsldma_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fsldma_device *fdev;
	अचिन्हित पूर्णांक i;

	fdev = platक्रमm_get_drvdata(op);
	dma_async_device_unरेजिस्टर(&fdev->common);

	fsldma_मुक्त_irqs(fdev);

	क्रम (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) अणु
		अगर (fdev->chan[i])
			fsl_dma_chan_हटाओ(fdev->chan[i]);
	पूर्ण
	irq_dispose_mapping(fdev->irq);

	iounmap(fdev->regs);
	kमुक्त(fdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fsldma_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा fsldma_device *fdev = dev_get_drvdata(dev);
	काष्ठा fsldma_chan *chan;
	पूर्णांक i;

	क्रम (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) अणु
		chan = fdev->chan[i];
		अगर (!chan)
			जारी;

		spin_lock_bh(&chan->desc_lock);
		अगर (unlikely(!chan->idle))
			जाओ out;
		chan->regs_save.mr = get_mr(chan);
		chan->pm_state = SUSPENDED;
		spin_unlock_bh(&chan->desc_lock);
	पूर्ण
	वापस 0;

out:
	क्रम (; i >= 0; i--) अणु
		chan = fdev->chan[i];
		अगर (!chan)
			जारी;
		chan->pm_state = RUNNING;
		spin_unlock_bh(&chan->desc_lock);
	पूर्ण
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक fsldma_resume_early(काष्ठा device *dev)
अणु
	काष्ठा fsldma_device *fdev = dev_get_drvdata(dev);
	काष्ठा fsldma_chan *chan;
	u32 mode;
	पूर्णांक i;

	क्रम (i = 0; i < FSL_DMA_MAX_CHANS_PER_DEVICE; i++) अणु
		chan = fdev->chan[i];
		अगर (!chan)
			जारी;

		spin_lock_bh(&chan->desc_lock);
		mode = chan->regs_save.mr
			& ~FSL_DMA_MR_CS & ~FSL_DMA_MR_CC & ~FSL_DMA_MR_CA;
		set_mr(chan, mode);
		chan->pm_state = RUNNING;
		spin_unlock_bh(&chan->desc_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsldma_pm_ops = अणु
	.suspend_late	= fsldma_suspend_late,
	.resume_early	= fsldma_resume_early,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id fsldma_of_ids[] = अणु
	अणु .compatible = "fsl,elo3-dma", पूर्ण,
	अणु .compatible = "fsl,eloplus-dma", पूर्ण,
	अणु .compatible = "fsl,elo-dma", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsldma_of_ids);

अटल काष्ठा platक्रमm_driver fsldma_of_driver = अणु
	.driver = अणु
		.name = "fsl-elo-dma",
		.of_match_table = fsldma_of_ids,
#अगर_घोषित CONFIG_PM
		.pm = &fsldma_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = fsldma_of_probe,
	.हटाओ = fsldma_of_हटाओ,
पूर्ण;

/*----------------------------------------------------------------------------*/
/* Module Init / Exit                                                         */
/*----------------------------------------------------------------------------*/

अटल __init पूर्णांक fsldma_init(व्योम)
अणु
	pr_info("Freescale Elo series DMA driver\n");
	वापस platक्रमm_driver_रेजिस्टर(&fsldma_of_driver);
पूर्ण

अटल व्योम __निकास fsldma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fsldma_of_driver);
पूर्ण

subsys_initcall(fsldma_init);
module_निकास(fsldma_निकास);

MODULE_DESCRIPTION("Freescale Elo series DMA driver");
MODULE_LICENSE("GPL");
