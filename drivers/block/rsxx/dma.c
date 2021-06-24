<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
* Filename: dma.c
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#समावेश <linux/slab.h>
#समावेश "rsxx_priv.h"

काष्ठा rsxx_dma अणु
	काष्ठा list_head	 list;
	u8			 cmd;
	अचिन्हित पूर्णांक		 laddr;     /* Logical address */
	काष्ठा अणु
		u32		 off;
		u32		 cnt;
	पूर्ण sub_page;
	dma_addr_t		 dma_addr;
	काष्ठा page		 *page;
	अचिन्हित पूर्णांक		 pg_off;    /* Page Offset */
	rsxx_dma_cb		 cb;
	व्योम			 *cb_data;
पूर्ण;

/* This समयout is used to detect a stalled DMA channel */
#घोषणा DMA_ACTIVITY_TIMEOUT	msecs_to_jअगरfies(10000)

काष्ठा hw_status अणु
	u8	status;
	u8	tag;
	__le16	count;
	__le32	_rsvd2;
	__le64	_rsvd3;
पूर्ण __packed;

क्रमागत rsxx_dma_status अणु
	DMA_SW_ERR    = 0x1,
	DMA_HW_FAULT  = 0x2,
	DMA_CANCELLED = 0x4,
पूर्ण;

काष्ठा hw_cmd अणु
	u8	command;
	u8	tag;
	u8	_rsvd;
	u8	sub_page; /* Bit[0:2]: 512byte offset */
			  /* Bit[4:6]: 512byte count */
	__le32	device_addr;
	__le64	host_addr;
पूर्ण __packed;

क्रमागत rsxx_hw_cmd अणु
	HW_CMD_BLK_DISCARD	= 0x70,
	HW_CMD_BLK_WRITE	= 0x80,
	HW_CMD_BLK_READ		= 0xC0,
	HW_CMD_BLK_RECON_READ	= 0xE0,
पूर्ण;

क्रमागत rsxx_hw_status अणु
	HW_STATUS_CRC		= 0x01,
	HW_STATUS_HARD_ERR	= 0x02,
	HW_STATUS_SOFT_ERR	= 0x04,
	HW_STATUS_FAULT		= 0x08,
पूर्ण;

अटल काष्ठा kmem_cache *rsxx_dma_pool;

काष्ठा dma_tracker अणु
	पूर्णांक			next_tag;
	काष्ठा rsxx_dma	*dma;
पूर्ण;

#घोषणा DMA_TRACKER_LIST_SIZE8 (माप(काष्ठा dma_tracker_list) + \
		(माप(काष्ठा dma_tracker) * RSXX_MAX_OUTSTANDING_CMDS))

काष्ठा dma_tracker_list अणु
	spinlock_t		lock;
	पूर्णांक			head;
	काष्ठा dma_tracker	list[];
पूर्ण;


/*----------------- Misc Utility Functions -------------------*/
अटल अचिन्हित पूर्णांक rsxx_addr8_to_laddr(u64 addr8, काष्ठा rsxx_cardinfo *card)
अणु
	अचिन्हित दीर्घ दीर्घ tgt_addr8;

	tgt_addr8 = ((addr8 >> card->_stripe.upper_shअगरt) &
		      card->_stripe.upper_mask) |
		    ((addr8) & card->_stripe.lower_mask);
	करो_भाग(tgt_addr8, RSXX_HW_BLK_SIZE);
	वापस tgt_addr8;
पूर्ण

अटल अचिन्हित पूर्णांक rsxx_get_dma_tgt(काष्ठा rsxx_cardinfo *card, u64 addr8)
अणु
	अचिन्हित पूर्णांक tgt;

	tgt = (addr8 >> card->_stripe.target_shअगरt) & card->_stripe.target_mask;

	वापस tgt;
पूर्ण

व्योम rsxx_dma_queue_reset(काष्ठा rsxx_cardinfo *card)
अणु
	/* Reset all DMA Command/Status Queues */
	ioग_लिखो32(DMA_QUEUE_RESET, card->regmap + RESET);
पूर्ण

अटल अचिन्हित पूर्णांक get_dma_size(काष्ठा rsxx_dma *dma)
अणु
	अगर (dma->sub_page.cnt)
		वापस dma->sub_page.cnt << 9;
	अन्यथा
		वापस RSXX_HW_BLK_SIZE;
पूर्ण


/*----------------- DMA Tracker -------------------*/
अटल व्योम set_tracker_dma(काष्ठा dma_tracker_list *trackers,
			    पूर्णांक tag,
			    काष्ठा rsxx_dma *dma)
अणु
	trackers->list[tag].dma = dma;
पूर्ण

अटल काष्ठा rsxx_dma *get_tracker_dma(काष्ठा dma_tracker_list *trackers,
					    पूर्णांक tag)
अणु
	वापस trackers->list[tag].dma;
पूर्ण

अटल पूर्णांक pop_tracker(काष्ठा dma_tracker_list *trackers)
अणु
	पूर्णांक tag;

	spin_lock(&trackers->lock);
	tag = trackers->head;
	अगर (tag != -1) अणु
		trackers->head = trackers->list[tag].next_tag;
		trackers->list[tag].next_tag = -1;
	पूर्ण
	spin_unlock(&trackers->lock);

	वापस tag;
पूर्ण

अटल व्योम push_tracker(काष्ठा dma_tracker_list *trackers, पूर्णांक tag)
अणु
	spin_lock(&trackers->lock);
	trackers->list[tag].next_tag = trackers->head;
	trackers->head = tag;
	trackers->list[tag].dma = शून्य;
	spin_unlock(&trackers->lock);
पूर्ण


/*----------------- Interrupt Coalescing -------------*/
/*
 * Interrupt Coalescing Register Format:
 * Interrupt Timer (64ns units) [15:0]
 * Interrupt Count [24:16]
 * Reserved [31:25]
*/
#घोषणा INTR_COAL_LATENCY_MASK       (0x0000ffff)

#घोषणा INTR_COAL_COUNT_SHIFT        16
#घोषणा INTR_COAL_COUNT_BITS         9
#घोषणा INTR_COAL_COUNT_MASK         (((1 << INTR_COAL_COUNT_BITS) - 1) << \
					INTR_COAL_COUNT_SHIFT)
#घोषणा INTR_COAL_LATENCY_UNITS_NS   64


अटल u32 dma_पूर्णांकr_coal_val(u32 mode, u32 count, u32 latency)
अणु
	u32 latency_units = latency / INTR_COAL_LATENCY_UNITS_NS;

	अगर (mode == RSXX_INTR_COAL_DISABLED)
		वापस 0;

	वापस ((count << INTR_COAL_COUNT_SHIFT) & INTR_COAL_COUNT_MASK) |
			(latency_units & INTR_COAL_LATENCY_MASK);

पूर्ण

अटल व्योम dma_पूर्णांकr_coal_स्वतः_tune(काष्ठा rsxx_cardinfo *card)
अणु
	पूर्णांक i;
	u32 q_depth = 0;
	u32 पूर्णांकr_coal;

	अगर (card->config.data.पूर्णांकr_coal.mode != RSXX_INTR_COAL_AUTO_TUNE ||
	    unlikely(card->eeh_state))
		वापस;

	क्रम (i = 0; i < card->n_tarमाला_लो; i++)
		q_depth += atomic_पढ़ो(&card->ctrl[i].stats.hw_q_depth);

	पूर्णांकr_coal = dma_पूर्णांकr_coal_val(card->config.data.पूर्णांकr_coal.mode,
				      q_depth / 2,
				      card->config.data.पूर्णांकr_coal.latency);
	ioग_लिखो32(पूर्णांकr_coal, card->regmap + INTR_COAL);
पूर्ण

/*----------------- RSXX DMA Handling -------------------*/
अटल व्योम rsxx_मुक्त_dma(काष्ठा rsxx_dma_ctrl *ctrl, काष्ठा rsxx_dma *dma)
अणु
	अगर (dma->cmd != HW_CMD_BLK_DISCARD) अणु
		अगर (!dma_mapping_error(&ctrl->card->dev->dev, dma->dma_addr)) अणु
			dma_unmap_page(&ctrl->card->dev->dev, dma->dma_addr,
				       get_dma_size(dma),
				       dma->cmd == HW_CMD_BLK_WRITE ?
						   DMA_TO_DEVICE :
						   DMA_FROM_DEVICE);
		पूर्ण
	पूर्ण

	kmem_cache_मुक्त(rsxx_dma_pool, dma);
पूर्ण

अटल व्योम rsxx_complete_dma(काष्ठा rsxx_dma_ctrl *ctrl,
				  काष्ठा rsxx_dma *dma,
				  अचिन्हित पूर्णांक status)
अणु
	अगर (status & DMA_SW_ERR)
		ctrl->stats.dma_sw_err++;
	अगर (status & DMA_HW_FAULT)
		ctrl->stats.dma_hw_fault++;
	अगर (status & DMA_CANCELLED)
		ctrl->stats.dma_cancelled++;

	अगर (dma->cb)
		dma->cb(ctrl->card, dma->cb_data, status ? 1 : 0);

	rsxx_मुक्त_dma(ctrl, dma);
पूर्ण

पूर्णांक rsxx_cleanup_dma_queue(काष्ठा rsxx_dma_ctrl *ctrl,
			   काष्ठा list_head *q, अचिन्हित पूर्णांक करोne)
अणु
	काष्ठा rsxx_dma *dma;
	काष्ठा rsxx_dma *पंचांगp;
	पूर्णांक cnt = 0;

	list_क्रम_each_entry_safe(dma, पंचांगp, q, list) अणु
		list_del(&dma->list);
		अगर (करोne & COMPLETE_DMA)
			rsxx_complete_dma(ctrl, dma, DMA_CANCELLED);
		अन्यथा
			rsxx_मुक्त_dma(ctrl, dma);
		cnt++;
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम rsxx_requeue_dma(काष्ठा rsxx_dma_ctrl *ctrl,
				 काष्ठा rsxx_dma *dma)
अणु
	/*
	 * Requeued DMAs go to the front of the queue so they are issued
	 * first.
	 */
	spin_lock_bh(&ctrl->queue_lock);
	ctrl->stats.sw_q_depth++;
	list_add(&dma->list, &ctrl->queue);
	spin_unlock_bh(&ctrl->queue_lock);
पूर्ण

अटल व्योम rsxx_handle_dma_error(काष्ठा rsxx_dma_ctrl *ctrl,
				      काष्ठा rsxx_dma *dma,
				      u8 hw_st)
अणु
	अचिन्हित पूर्णांक status = 0;
	पूर्णांक requeue_cmd = 0;

	dev_dbg(CARD_TO_DEV(ctrl->card),
		"Handling DMA error(cmd x%02x, laddr x%08x st:x%02x)\n",
		dma->cmd, dma->laddr, hw_st);

	अगर (hw_st & HW_STATUS_CRC)
		ctrl->stats.crc_errors++;
	अगर (hw_st & HW_STATUS_HARD_ERR)
		ctrl->stats.hard_errors++;
	अगर (hw_st & HW_STATUS_SOFT_ERR)
		ctrl->stats.soft_errors++;

	चयन (dma->cmd) अणु
	हाल HW_CMD_BLK_READ:
		अगर (hw_st & (HW_STATUS_CRC | HW_STATUS_HARD_ERR)) अणु
			अगर (ctrl->card->scrub_hard) अणु
				dma->cmd = HW_CMD_BLK_RECON_READ;
				requeue_cmd = 1;
				ctrl->stats.पढ़ोs_retried++;
			पूर्ण अन्यथा अणु
				status |= DMA_HW_FAULT;
				ctrl->stats.पढ़ोs_failed++;
			पूर्ण
		पूर्ण अन्यथा अगर (hw_st & HW_STATUS_FAULT) अणु
			status |= DMA_HW_FAULT;
			ctrl->stats.पढ़ोs_failed++;
		पूर्ण

		अवरोध;
	हाल HW_CMD_BLK_RECON_READ:
		अगर (hw_st & (HW_STATUS_CRC | HW_STATUS_HARD_ERR)) अणु
			/* Data could not be reस्थिरructed. */
			status |= DMA_HW_FAULT;
			ctrl->stats.पढ़ोs_failed++;
		पूर्ण

		अवरोध;
	हाल HW_CMD_BLK_WRITE:
		status |= DMA_HW_FAULT;
		ctrl->stats.ग_लिखोs_failed++;

		अवरोध;
	हाल HW_CMD_BLK_DISCARD:
		status |= DMA_HW_FAULT;
		ctrl->stats.discards_failed++;

		अवरोध;
	शेष:
		dev_err(CARD_TO_DEV(ctrl->card),
			"Unknown command in DMA!(cmd: x%02x "
			   "laddr x%08x st: x%02x\n",
			   dma->cmd, dma->laddr, hw_st);
		status |= DMA_SW_ERR;

		अवरोध;
	पूर्ण

	अगर (requeue_cmd)
		rsxx_requeue_dma(ctrl, dma);
	अन्यथा
		rsxx_complete_dma(ctrl, dma, status);
पूर्ण

अटल व्योम dma_engine_stalled(काष्ठा समयr_list *t)
अणु
	काष्ठा rsxx_dma_ctrl *ctrl = from_समयr(ctrl, t, activity_समयr);
	पूर्णांक cnt;

	अगर (atomic_पढ़ो(&ctrl->stats.hw_q_depth) == 0 ||
	    unlikely(ctrl->card->eeh_state))
		वापस;

	अगर (ctrl->cmd.idx != ioपढ़ो32(ctrl->regmap + SW_CMD_IDX)) अणु
		/*
		 * The dma engine was stalled because the SW_CMD_IDX ग_लिखो
		 * was lost. Issue it again to recover.
		 */
		dev_warn(CARD_TO_DEV(ctrl->card),
			"SW_CMD_IDX write was lost, re-writing...\n");
		ioग_लिखो32(ctrl->cmd.idx, ctrl->regmap + SW_CMD_IDX);
		mod_समयr(&ctrl->activity_समयr,
			  jअगरfies + DMA_ACTIVITY_TIMEOUT);
	पूर्ण अन्यथा अणु
		dev_warn(CARD_TO_DEV(ctrl->card),
			"DMA channel %d has stalled, faulting interface.\n",
			ctrl->id);
		ctrl->card->dma_fault = 1;

		/* Clean up the DMA queue */
		spin_lock(&ctrl->queue_lock);
		cnt = rsxx_cleanup_dma_queue(ctrl, &ctrl->queue, COMPLETE_DMA);
		spin_unlock(&ctrl->queue_lock);

		cnt += rsxx_dma_cancel(ctrl);

		अगर (cnt)
			dev_info(CARD_TO_DEV(ctrl->card),
				"Freed %d queued DMAs on channel %d\n",
				cnt, ctrl->id);
	पूर्ण
पूर्ण

अटल व्योम rsxx_issue_dmas(काष्ठा rsxx_dma_ctrl *ctrl)
अणु
	काष्ठा rsxx_dma *dma;
	पूर्णांक tag;
	पूर्णांक cmds_pending = 0;
	काष्ठा hw_cmd *hw_cmd_buf;
	पूर्णांक dir;

	hw_cmd_buf = ctrl->cmd.buf;

	अगर (unlikely(ctrl->card->halt) ||
	    unlikely(ctrl->card->eeh_state))
		वापस;

	जबतक (1) अणु
		spin_lock_bh(&ctrl->queue_lock);
		अगर (list_empty(&ctrl->queue)) अणु
			spin_unlock_bh(&ctrl->queue_lock);
			अवरोध;
		पूर्ण
		spin_unlock_bh(&ctrl->queue_lock);

		tag = pop_tracker(ctrl->trackers);
		अगर (tag == -1)
			अवरोध;

		spin_lock_bh(&ctrl->queue_lock);
		dma = list_entry(ctrl->queue.next, काष्ठा rsxx_dma, list);
		list_del(&dma->list);
		ctrl->stats.sw_q_depth--;
		spin_unlock_bh(&ctrl->queue_lock);

		/*
		 * This will catch any DMAs that slipped in right beक्रमe the
		 * fault, but was queued after all the other DMAs were
		 * cancelled.
		 */
		अगर (unlikely(ctrl->card->dma_fault)) अणु
			push_tracker(ctrl->trackers, tag);
			rsxx_complete_dma(ctrl, dma, DMA_CANCELLED);
			जारी;
		पूर्ण

		अगर (dma->cmd != HW_CMD_BLK_DISCARD) अणु
			अगर (dma->cmd == HW_CMD_BLK_WRITE)
				dir = DMA_TO_DEVICE;
			अन्यथा
				dir = DMA_FROM_DEVICE;

			/*
			 * The function dma_map_page is placed here because we
			 * can only, by design, issue up to 255 commands to the
			 * hardware at one समय per DMA channel. So the maximum
			 * amount of mapped memory would be 255 * 4 channels *
			 * 4096 Bytes which is less than 2GB, the limit of a x8
			 * Non-HWWD PCIe slot. This way the dma_map_page
			 * function should never fail because of a lack of
			 * mappable memory.
			 */
			dma->dma_addr = dma_map_page(&ctrl->card->dev->dev, dma->page,
					dma->pg_off, dma->sub_page.cnt << 9, dir);
			अगर (dma_mapping_error(&ctrl->card->dev->dev, dma->dma_addr)) अणु
				push_tracker(ctrl->trackers, tag);
				rsxx_complete_dma(ctrl, dma, DMA_CANCELLED);
				जारी;
			पूर्ण
		पूर्ण

		set_tracker_dma(ctrl->trackers, tag, dma);
		hw_cmd_buf[ctrl->cmd.idx].command  = dma->cmd;
		hw_cmd_buf[ctrl->cmd.idx].tag      = tag;
		hw_cmd_buf[ctrl->cmd.idx]._rsvd    = 0;
		hw_cmd_buf[ctrl->cmd.idx].sub_page =
					((dma->sub_page.cnt & 0x7) << 4) |
					 (dma->sub_page.off & 0x7);

		hw_cmd_buf[ctrl->cmd.idx].device_addr =
					cpu_to_le32(dma->laddr);

		hw_cmd_buf[ctrl->cmd.idx].host_addr =
					cpu_to_le64(dma->dma_addr);

		dev_dbg(CARD_TO_DEV(ctrl->card),
			"Issue DMA%d(laddr %d tag %d) to idx %d\n",
			ctrl->id, dma->laddr, tag, ctrl->cmd.idx);

		ctrl->cmd.idx = (ctrl->cmd.idx + 1) & RSXX_CS_IDX_MASK;
		cmds_pending++;

		अगर (dma->cmd == HW_CMD_BLK_WRITE)
			ctrl->stats.ग_लिखोs_issued++;
		अन्यथा अगर (dma->cmd == HW_CMD_BLK_DISCARD)
			ctrl->stats.discards_issued++;
		अन्यथा
			ctrl->stats.पढ़ोs_issued++;
	पूर्ण

	/* Let HW know we've queued commands. */
	अगर (cmds_pending) अणु
		atomic_add(cmds_pending, &ctrl->stats.hw_q_depth);
		mod_समयr(&ctrl->activity_समयr,
			  jअगरfies + DMA_ACTIVITY_TIMEOUT);

		अगर (unlikely(ctrl->card->eeh_state)) अणु
			del_समयr_sync(&ctrl->activity_समयr);
			वापस;
		पूर्ण

		ioग_लिखो32(ctrl->cmd.idx, ctrl->regmap + SW_CMD_IDX);
	पूर्ण
पूर्ण

अटल व्योम rsxx_dma_करोne(काष्ठा rsxx_dma_ctrl *ctrl)
अणु
	काष्ठा rsxx_dma *dma;
	अचिन्हित दीर्घ flags;
	u16 count;
	u8 status;
	u8 tag;
	काष्ठा hw_status *hw_st_buf;

	hw_st_buf = ctrl->status.buf;

	अगर (unlikely(ctrl->card->halt) ||
	    unlikely(ctrl->card->dma_fault) ||
	    unlikely(ctrl->card->eeh_state))
		वापस;

	count = le16_to_cpu(hw_st_buf[ctrl->status.idx].count);

	जबतक (count == ctrl->e_cnt) अणु
		/*
		 * The पढ़ो memory-barrier is necessary to keep aggressive
		 * processors/optimizers (such as the PPC Apple G5) from
		 * reordering the following status-buffer tag & status पढ़ो
		 * *beक्रमe* the count पढ़ो on subsequent iterations of the
		 * loop!
		 */
		rmb();

		status = hw_st_buf[ctrl->status.idx].status;
		tag    = hw_st_buf[ctrl->status.idx].tag;

		dma = get_tracker_dma(ctrl->trackers, tag);
		अगर (dma == शून्य) अणु
			spin_lock_irqsave(&ctrl->card->irq_lock, flags);
			rsxx_disable_ier(ctrl->card, CR_INTR_DMA_ALL);
			spin_unlock_irqrestore(&ctrl->card->irq_lock, flags);

			dev_err(CARD_TO_DEV(ctrl->card),
				"No tracker for tag %d "
				"(idx %d id %d)\n",
				tag, ctrl->status.idx, ctrl->id);
			वापस;
		पूर्ण

		dev_dbg(CARD_TO_DEV(ctrl->card),
			"Completing DMA%d"
			"(laddr x%x tag %d st: x%x cnt: x%04x) from idx %d.\n",
			ctrl->id, dma->laddr, tag, status, count,
			ctrl->status.idx);

		atomic_dec(&ctrl->stats.hw_q_depth);

		mod_समयr(&ctrl->activity_समयr,
			  jअगरfies + DMA_ACTIVITY_TIMEOUT);

		अगर (status)
			rsxx_handle_dma_error(ctrl, dma, status);
		अन्यथा
			rsxx_complete_dma(ctrl, dma, 0);

		push_tracker(ctrl->trackers, tag);

		ctrl->status.idx = (ctrl->status.idx + 1) &
				   RSXX_CS_IDX_MASK;
		ctrl->e_cnt++;

		count = le16_to_cpu(hw_st_buf[ctrl->status.idx].count);
	पूर्ण

	dma_पूर्णांकr_coal_स्वतः_tune(ctrl->card);

	अगर (atomic_पढ़ो(&ctrl->stats.hw_q_depth) == 0)
		del_समयr_sync(&ctrl->activity_समयr);

	spin_lock_irqsave(&ctrl->card->irq_lock, flags);
	rsxx_enable_ier(ctrl->card, CR_INTR_DMA(ctrl->id));
	spin_unlock_irqrestore(&ctrl->card->irq_lock, flags);

	spin_lock_bh(&ctrl->queue_lock);
	अगर (ctrl->stats.sw_q_depth)
		queue_work(ctrl->issue_wq, &ctrl->issue_dma_work);
	spin_unlock_bh(&ctrl->queue_lock);
पूर्ण

अटल व्योम rsxx_schedule_issue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rsxx_dma_ctrl *ctrl;

	ctrl = container_of(work, काष्ठा rsxx_dma_ctrl, issue_dma_work);

	mutex_lock(&ctrl->work_lock);
	rsxx_issue_dmas(ctrl);
	mutex_unlock(&ctrl->work_lock);
पूर्ण

अटल व्योम rsxx_schedule_करोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rsxx_dma_ctrl *ctrl;

	ctrl = container_of(work, काष्ठा rsxx_dma_ctrl, dma_करोne_work);

	mutex_lock(&ctrl->work_lock);
	rsxx_dma_करोne(ctrl);
	mutex_unlock(&ctrl->work_lock);
पूर्ण

अटल blk_status_t rsxx_queue_discard(काष्ठा rsxx_cardinfo *card,
				  काष्ठा list_head *q,
				  अचिन्हित पूर्णांक laddr,
				  rsxx_dma_cb cb,
				  व्योम *cb_data)
अणु
	काष्ठा rsxx_dma *dma;

	dma = kmem_cache_alloc(rsxx_dma_pool, GFP_KERNEL);
	अगर (!dma)
		वापस BLK_STS_RESOURCE;

	dma->cmd          = HW_CMD_BLK_DISCARD;
	dma->laddr        = laddr;
	dma->dma_addr     = 0;
	dma->sub_page.off = 0;
	dma->sub_page.cnt = 0;
	dma->page         = शून्य;
	dma->pg_off       = 0;
	dma->cb	          = cb;
	dma->cb_data      = cb_data;

	dev_dbg(CARD_TO_DEV(card), "Queuing[D] laddr %x\n", dma->laddr);

	list_add_tail(&dma->list, q);

	वापस 0;
पूर्ण

अटल blk_status_t rsxx_queue_dma(काष्ठा rsxx_cardinfo *card,
			      काष्ठा list_head *q,
			      पूर्णांक dir,
			      अचिन्हित पूर्णांक dma_off,
			      अचिन्हित पूर्णांक dma_len,
			      अचिन्हित पूर्णांक laddr,
			      काष्ठा page *page,
			      अचिन्हित पूर्णांक pg_off,
			      rsxx_dma_cb cb,
			      व्योम *cb_data)
अणु
	काष्ठा rsxx_dma *dma;

	dma = kmem_cache_alloc(rsxx_dma_pool, GFP_KERNEL);
	अगर (!dma)
		वापस BLK_STS_RESOURCE;

	dma->cmd          = dir ? HW_CMD_BLK_WRITE : HW_CMD_BLK_READ;
	dma->laddr        = laddr;
	dma->sub_page.off = (dma_off >> 9);
	dma->sub_page.cnt = (dma_len >> 9);
	dma->page         = page;
	dma->pg_off       = pg_off;
	dma->cb	          = cb;
	dma->cb_data      = cb_data;

	dev_dbg(CARD_TO_DEV(card),
		"Queuing[%c] laddr %x off %d cnt %d page %p pg_off %d\n",
		dir ? 'W' : 'R', dma->laddr, dma->sub_page.off,
		dma->sub_page.cnt, dma->page, dma->pg_off);

	/* Queue the DMA */
	list_add_tail(&dma->list, q);

	वापस 0;
पूर्ण

blk_status_t rsxx_dma_queue_bio(काष्ठा rsxx_cardinfo *card,
			   काष्ठा bio *bio,
			   atomic_t *n_dmas,
			   rsxx_dma_cb cb,
			   व्योम *cb_data)
अणु
	काष्ठा list_head dma_list[RSXX_MAX_TARGETS];
	काष्ठा bio_vec bvec;
	काष्ठा bvec_iter iter;
	अचिन्हित दीर्घ दीर्घ addr8;
	अचिन्हित पूर्णांक laddr;
	अचिन्हित पूर्णांक bv_len;
	अचिन्हित पूर्णांक bv_off;
	अचिन्हित पूर्णांक dma_off;
	अचिन्हित पूर्णांक dma_len;
	पूर्णांक dma_cnt[RSXX_MAX_TARGETS];
	पूर्णांक tgt;
	blk_status_t st;
	पूर्णांक i;

	addr8 = bio->bi_iter.bi_sector << 9; /* sectors are 512 bytes */
	atomic_set(n_dmas, 0);

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		INIT_LIST_HEAD(&dma_list[i]);
		dma_cnt[i] = 0;
	पूर्ण

	अगर (bio_op(bio) == REQ_OP_DISCARD) अणु
		bv_len = bio->bi_iter.bi_size;

		जबतक (bv_len > 0) अणु
			tgt   = rsxx_get_dma_tgt(card, addr8);
			laddr = rsxx_addr8_to_laddr(addr8, card);

			st = rsxx_queue_discard(card, &dma_list[tgt], laddr,
						    cb, cb_data);
			अगर (st)
				जाओ bvec_err;

			dma_cnt[tgt]++;
			atomic_inc(n_dmas);
			addr8  += RSXX_HW_BLK_SIZE;
			bv_len -= RSXX_HW_BLK_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		bio_क्रम_each_segment(bvec, bio, iter) अणु
			bv_len = bvec.bv_len;
			bv_off = bvec.bv_offset;

			जबतक (bv_len > 0) अणु
				tgt   = rsxx_get_dma_tgt(card, addr8);
				laddr = rsxx_addr8_to_laddr(addr8, card);
				dma_off = addr8 & RSXX_HW_BLK_MASK;
				dma_len = min(bv_len,
					      RSXX_HW_BLK_SIZE - dma_off);

				st = rsxx_queue_dma(card, &dma_list[tgt],
							bio_data_dir(bio),
							dma_off, dma_len,
							laddr, bvec.bv_page,
							bv_off, cb, cb_data);
				अगर (st)
					जाओ bvec_err;

				dma_cnt[tgt]++;
				atomic_inc(n_dmas);
				addr8  += dma_len;
				bv_off += dma_len;
				bv_len -= dma_len;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		अगर (!list_empty(&dma_list[i])) अणु
			spin_lock_bh(&card->ctrl[i].queue_lock);
			card->ctrl[i].stats.sw_q_depth += dma_cnt[i];
			list_splice_tail(&dma_list[i], &card->ctrl[i].queue);
			spin_unlock_bh(&card->ctrl[i].queue_lock);

			queue_work(card->ctrl[i].issue_wq,
				   &card->ctrl[i].issue_dma_work);
		पूर्ण
	पूर्ण

	वापस 0;

bvec_err:
	क्रम (i = 0; i < card->n_tarमाला_लो; i++)
		rsxx_cleanup_dma_queue(&card->ctrl[i], &dma_list[i],
					FREE_DMA);
	वापस st;
पूर्ण


/*----------------- DMA Engine Initialization & Setup -------------------*/
पूर्णांक rsxx_hw_buffers_init(काष्ठा pci_dev *dev, काष्ठा rsxx_dma_ctrl *ctrl)
अणु
	ctrl->status.buf = dma_alloc_coherent(&dev->dev, STATUS_BUFFER_SIZE8,
				&ctrl->status.dma_addr, GFP_KERNEL);
	ctrl->cmd.buf = dma_alloc_coherent(&dev->dev, COMMAND_BUFFER_SIZE8,
				&ctrl->cmd.dma_addr, GFP_KERNEL);
	अगर (ctrl->status.buf == शून्य || ctrl->cmd.buf == शून्य)
		वापस -ENOMEM;

	स_रखो(ctrl->status.buf, 0xac, STATUS_BUFFER_SIZE8);
	ioग_लिखो32(lower_32_bits(ctrl->status.dma_addr),
		ctrl->regmap + SB_ADD_LO);
	ioग_लिखो32(upper_32_bits(ctrl->status.dma_addr),
		ctrl->regmap + SB_ADD_HI);

	स_रखो(ctrl->cmd.buf, 0x83, COMMAND_BUFFER_SIZE8);
	ioग_लिखो32(lower_32_bits(ctrl->cmd.dma_addr), ctrl->regmap + CB_ADD_LO);
	ioग_लिखो32(upper_32_bits(ctrl->cmd.dma_addr), ctrl->regmap + CB_ADD_HI);

	ctrl->status.idx = ioपढ़ो32(ctrl->regmap + HW_STATUS_CNT);
	अगर (ctrl->status.idx > RSXX_MAX_OUTSTANDING_CMDS) अणु
		dev_crit(&dev->dev, "Failed reading status cnt x%x\n",
			ctrl->status.idx);
		वापस -EINVAL;
	पूर्ण
	ioग_लिखो32(ctrl->status.idx, ctrl->regmap + HW_STATUS_CNT);
	ioग_लिखो32(ctrl->status.idx, ctrl->regmap + SW_STATUS_CNT);

	ctrl->cmd.idx = ioपढ़ो32(ctrl->regmap + HW_CMD_IDX);
	अगर (ctrl->cmd.idx > RSXX_MAX_OUTSTANDING_CMDS) अणु
		dev_crit(&dev->dev, "Failed reading cmd cnt x%x\n",
			ctrl->status.idx);
		वापस -EINVAL;
	पूर्ण
	ioग_लिखो32(ctrl->cmd.idx, ctrl->regmap + HW_CMD_IDX);
	ioग_लिखो32(ctrl->cmd.idx, ctrl->regmap + SW_CMD_IDX);

	वापस 0;
पूर्ण

अटल पूर्णांक rsxx_dma_ctrl_init(काष्ठा pci_dev *dev,
				  काष्ठा rsxx_dma_ctrl *ctrl)
अणु
	पूर्णांक i;
	पूर्णांक st;

	स_रखो(&ctrl->stats, 0, माप(ctrl->stats));

	ctrl->trackers = vदो_स्मृति(DMA_TRACKER_LIST_SIZE8);
	अगर (!ctrl->trackers)
		वापस -ENOMEM;

	ctrl->trackers->head = 0;
	क्रम (i = 0; i < RSXX_MAX_OUTSTANDING_CMDS; i++) अणु
		ctrl->trackers->list[i].next_tag = i + 1;
		ctrl->trackers->list[i].dma = शून्य;
	पूर्ण
	ctrl->trackers->list[RSXX_MAX_OUTSTANDING_CMDS-1].next_tag = -1;
	spin_lock_init(&ctrl->trackers->lock);

	spin_lock_init(&ctrl->queue_lock);
	mutex_init(&ctrl->work_lock);
	INIT_LIST_HEAD(&ctrl->queue);

	समयr_setup(&ctrl->activity_समयr, dma_engine_stalled, 0);

	ctrl->issue_wq = alloc_ordered_workqueue(DRIVER_NAME"_issue", 0);
	अगर (!ctrl->issue_wq)
		वापस -ENOMEM;

	ctrl->करोne_wq = alloc_ordered_workqueue(DRIVER_NAME"_done", 0);
	अगर (!ctrl->करोne_wq)
		वापस -ENOMEM;

	INIT_WORK(&ctrl->issue_dma_work, rsxx_schedule_issue);
	INIT_WORK(&ctrl->dma_करोne_work, rsxx_schedule_करोne);

	st = rsxx_hw_buffers_init(dev, ctrl);
	अगर (st)
		वापस st;

	वापस 0;
पूर्ण

अटल पूर्णांक rsxx_dma_stripe_setup(काष्ठा rsxx_cardinfo *card,
			      अचिन्हित पूर्णांक stripe_size8)
अणु
	अगर (!is_घातer_of_2(stripe_size8)) अणु
		dev_err(CARD_TO_DEV(card),
			"stripe_size is NOT a power of 2!\n");
		वापस -EINVAL;
	पूर्ण

	card->_stripe.lower_mask = stripe_size8 - 1;

	card->_stripe.upper_mask  = ~(card->_stripe.lower_mask);
	card->_stripe.upper_shअगरt = ffs(card->n_tarमाला_लो) - 1;

	card->_stripe.target_mask = card->n_tarमाला_लो - 1;
	card->_stripe.target_shअगरt = ffs(stripe_size8) - 1;

	dev_dbg(CARD_TO_DEV(card), "_stripe.lower_mask   = x%016llx\n",
		card->_stripe.lower_mask);
	dev_dbg(CARD_TO_DEV(card), "_stripe.upper_shift  = x%016llx\n",
		card->_stripe.upper_shअगरt);
	dev_dbg(CARD_TO_DEV(card), "_stripe.upper_mask   = x%016llx\n",
		card->_stripe.upper_mask);
	dev_dbg(CARD_TO_DEV(card), "_stripe.target_mask  = x%016llx\n",
		card->_stripe.target_mask);
	dev_dbg(CARD_TO_DEV(card), "_stripe.target_shift = x%016llx\n",
		card->_stripe.target_shअगरt);

	वापस 0;
पूर्ण

पूर्णांक rsxx_dma_configure(काष्ठा rsxx_cardinfo *card)
अणु
	u32 पूर्णांकr_coal;

	पूर्णांकr_coal = dma_पूर्णांकr_coal_val(card->config.data.पूर्णांकr_coal.mode,
				      card->config.data.पूर्णांकr_coal.count,
				      card->config.data.पूर्णांकr_coal.latency);
	ioग_लिखो32(पूर्णांकr_coal, card->regmap + INTR_COAL);

	वापस rsxx_dma_stripe_setup(card, card->config.data.stripe_size);
पूर्ण

पूर्णांक rsxx_dma_setup(काष्ठा rsxx_cardinfo *card)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक st;
	पूर्णांक i;

	dev_info(CARD_TO_DEV(card),
		"Initializing %d DMA targets\n",
		card->n_tarमाला_लो);

	/* Regmap is भागided up पूर्णांकo 4K chunks. One क्रम each DMA channel */
	क्रम (i = 0; i < card->n_tarमाला_लो; i++)
		card->ctrl[i].regmap = card->regmap + (i * 4096);

	card->dma_fault = 0;

	/* Reset the DMA queues */
	rsxx_dma_queue_reset(card);

	/************* Setup DMA Control *************/
	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		st = rsxx_dma_ctrl_init(card->dev, &card->ctrl[i]);
		अगर (st)
			जाओ failed_dma_setup;

		card->ctrl[i].card = card;
		card->ctrl[i].id = i;
	पूर्ण

	card->scrub_hard = 1;

	अगर (card->config_valid)
		rsxx_dma_configure(card);

	/* Enable the पूर्णांकerrupts after all setup has completed. */
	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		spin_lock_irqsave(&card->irq_lock, flags);
		rsxx_enable_ier_and_isr(card, CR_INTR_DMA(i));
		spin_unlock_irqrestore(&card->irq_lock, flags);
	पूर्ण

	वापस 0;

failed_dma_setup:
	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		काष्ठा rsxx_dma_ctrl *ctrl = &card->ctrl[i];

		अगर (ctrl->issue_wq) अणु
			destroy_workqueue(ctrl->issue_wq);
			ctrl->issue_wq = शून्य;
		पूर्ण

		अगर (ctrl->करोne_wq) अणु
			destroy_workqueue(ctrl->करोne_wq);
			ctrl->करोne_wq = शून्य;
		पूर्ण

		vमुक्त(ctrl->trackers);

		अगर (ctrl->status.buf)
			dma_मुक्त_coherent(&card->dev->dev, STATUS_BUFFER_SIZE8,
					  ctrl->status.buf,
					  ctrl->status.dma_addr);
		अगर (ctrl->cmd.buf)
			dma_मुक्त_coherent(&card->dev->dev, COMMAND_BUFFER_SIZE8,
					  ctrl->cmd.buf, ctrl->cmd.dma_addr);
	पूर्ण

	वापस st;
पूर्ण

पूर्णांक rsxx_dma_cancel(काष्ठा rsxx_dma_ctrl *ctrl)
अणु
	काष्ठा rsxx_dma *dma;
	पूर्णांक i;
	पूर्णांक cnt = 0;

	/* Clean up issued DMAs */
	क्रम (i = 0; i < RSXX_MAX_OUTSTANDING_CMDS; i++) अणु
		dma = get_tracker_dma(ctrl->trackers, i);
		अगर (dma) अणु
			atomic_dec(&ctrl->stats.hw_q_depth);
			rsxx_complete_dma(ctrl, dma, DMA_CANCELLED);
			push_tracker(ctrl->trackers, i);
			cnt++;
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

व्योम rsxx_dma_destroy(काष्ठा rsxx_cardinfo *card)
अणु
	काष्ठा rsxx_dma_ctrl *ctrl;
	पूर्णांक i;

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		ctrl = &card->ctrl[i];

		अगर (ctrl->issue_wq) अणु
			destroy_workqueue(ctrl->issue_wq);
			ctrl->issue_wq = शून्य;
		पूर्ण

		अगर (ctrl->करोne_wq) अणु
			destroy_workqueue(ctrl->करोne_wq);
			ctrl->करोne_wq = शून्य;
		पूर्ण

		अगर (समयr_pending(&ctrl->activity_समयr))
			del_समयr_sync(&ctrl->activity_समयr);

		/* Clean up the DMA queue */
		spin_lock_bh(&ctrl->queue_lock);
		rsxx_cleanup_dma_queue(ctrl, &ctrl->queue, COMPLETE_DMA);
		spin_unlock_bh(&ctrl->queue_lock);

		rsxx_dma_cancel(ctrl);

		vमुक्त(ctrl->trackers);

		dma_मुक्त_coherent(&card->dev->dev, STATUS_BUFFER_SIZE8,
				  ctrl->status.buf, ctrl->status.dma_addr);
		dma_मुक्त_coherent(&card->dev->dev, COMMAND_BUFFER_SIZE8,
				  ctrl->cmd.buf, ctrl->cmd.dma_addr);
	पूर्ण
पूर्ण

पूर्णांक rsxx_eeh_save_issued_dmas(काष्ठा rsxx_cardinfo *card)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक cnt;
	काष्ठा rsxx_dma *dma;
	काष्ठा list_head *issued_dmas;

	issued_dmas = kसुस्मृति(card->n_tarमाला_लो, माप(*issued_dmas),
			      GFP_KERNEL);
	अगर (!issued_dmas)
		वापस -ENOMEM;

	क्रम (i = 0; i < card->n_tarमाला_लो; i++) अणु
		INIT_LIST_HEAD(&issued_dmas[i]);
		cnt = 0;
		क्रम (j = 0; j < RSXX_MAX_OUTSTANDING_CMDS; j++) अणु
			dma = get_tracker_dma(card->ctrl[i].trackers, j);
			अगर (dma == शून्य)
				जारी;

			अगर (dma->cmd == HW_CMD_BLK_WRITE)
				card->ctrl[i].stats.ग_लिखोs_issued--;
			अन्यथा अगर (dma->cmd == HW_CMD_BLK_DISCARD)
				card->ctrl[i].stats.discards_issued--;
			अन्यथा
				card->ctrl[i].stats.पढ़ोs_issued--;

			अगर (dma->cmd != HW_CMD_BLK_DISCARD) अणु
				dma_unmap_page(&card->dev->dev, dma->dma_addr,
					       get_dma_size(dma),
					       dma->cmd == HW_CMD_BLK_WRITE ?
					       DMA_TO_DEVICE :
					       DMA_FROM_DEVICE);
			पूर्ण

			list_add_tail(&dma->list, &issued_dmas[i]);
			push_tracker(card->ctrl[i].trackers, j);
			cnt++;
		पूर्ण

		spin_lock_bh(&card->ctrl[i].queue_lock);
		list_splice(&issued_dmas[i], &card->ctrl[i].queue);

		atomic_sub(cnt, &card->ctrl[i].stats.hw_q_depth);
		card->ctrl[i].stats.sw_q_depth += cnt;
		card->ctrl[i].e_cnt = 0;
		spin_unlock_bh(&card->ctrl[i].queue_lock);
	पूर्ण

	kमुक्त(issued_dmas);

	वापस 0;
पूर्ण

पूर्णांक rsxx_dma_init(व्योम)
अणु
	rsxx_dma_pool = KMEM_CACHE(rsxx_dma, SLAB_HWCACHE_ALIGN);
	अगर (!rsxx_dma_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण


व्योम rsxx_dma_cleanup(व्योम)
अणु
	kmem_cache_destroy(rsxx_dma_pool);
पूर्ण

