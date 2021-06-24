<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018-2020 Broadcom.
 */

#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/hash.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/sizes.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>

#समावेश "bcm_vk.h"
#समावेश "bcm_vk_msg.h"
#समावेश "bcm_vk_sg.h"

/* functions to manipulate the transport id in msg block */
#घोषणा BCM_VK_MSG_Q_SHIFT	 4
#घोषणा BCM_VK_MSG_Q_MASK	 0xF
#घोषणा BCM_VK_MSG_ID_MASK	 0xFFF

#घोषणा BCM_VK_DMA_DRAIN_MAX_MS	  2000

/* number x q_size will be the max number of msg processed per loop */
#घोषणा BCM_VK_MSG_PROC_MAX_LOOP 2

/* module parameter */
अटल bool hb_mon = true;
module_param(hb_mon, bool, 0444);
MODULE_PARM_DESC(hb_mon, "Monitoring heartbeat continuously.\n");
अटल पूर्णांक batch_log = 1;
module_param(batch_log, पूर्णांक, 0444);
MODULE_PARM_DESC(batch_log, "Max num of logs per batch operation.\n");

अटल bool hb_mon_is_on(व्योम)
अणु
	वापस hb_mon;
पूर्ण

अटल u32 get_q_num(स्थिर काष्ठा vk_msg_blk *msg)
अणु
	u32 q_num = msg->trans_id & BCM_VK_MSG_Q_MASK;

	अगर (q_num >= VK_MSGQ_PER_CHAN_MAX)
		q_num = VK_MSGQ_NUM_DEFAULT;
	वापस q_num;
पूर्ण

अटल व्योम set_q_num(काष्ठा vk_msg_blk *msg, u32 q_num)
अणु
	u32 trans_q;

	अगर (q_num >= VK_MSGQ_PER_CHAN_MAX)
		trans_q = VK_MSGQ_NUM_DEFAULT;
	अन्यथा
		trans_q = q_num;

	msg->trans_id = (msg->trans_id & ~BCM_VK_MSG_Q_MASK) | trans_q;
पूर्ण

अटल u32 get_msg_id(स्थिर काष्ठा vk_msg_blk *msg)
अणु
	वापस ((msg->trans_id >> BCM_VK_MSG_Q_SHIFT) & BCM_VK_MSG_ID_MASK);
पूर्ण

अटल व्योम set_msg_id(काष्ठा vk_msg_blk *msg, u32 val)
अणु
	msg->trans_id = (val << BCM_VK_MSG_Q_SHIFT) | get_q_num(msg);
पूर्ण

अटल u32 msgq_inc(स्थिर काष्ठा bcm_vk_sync_qinfo *qinfo, u32 idx, u32 inc)
अणु
	वापस ((idx + inc) & qinfo->q_mask);
पूर्ण

अटल
काष्ठा vk_msg_blk __iomem *msgq_blk_addr(स्थिर काष्ठा bcm_vk_sync_qinfo *qinfo,
					 u32 idx)
अणु
	वापस qinfo->q_start + (VK_MSGQ_BLK_SIZE * idx);
पूर्ण

अटल u32 msgq_occupied(स्थिर काष्ठा bcm_vk_msgq __iomem *msgq,
			 स्थिर काष्ठा bcm_vk_sync_qinfo *qinfo)
अणु
	u32 wr_idx, rd_idx;

	wr_idx = पढ़ोl_relaxed(&msgq->wr_idx);
	rd_idx = पढ़ोl_relaxed(&msgq->rd_idx);

	वापस ((wr_idx - rd_idx) & qinfo->q_mask);
पूर्ण

अटल
u32 msgq_avail_space(स्थिर काष्ठा bcm_vk_msgq __iomem *msgq,
		     स्थिर काष्ठा bcm_vk_sync_qinfo *qinfo)
अणु
	वापस (qinfo->q_size - msgq_occupied(msgq, qinfo) - 1);
पूर्ण

/* number of retries when enqueue message fails beक्रमe वापसing EAGAIN */
#घोषणा BCM_VK_H2VK_ENQ_RETRY 10
#घोषणा BCM_VK_H2VK_ENQ_RETRY_DELAY_MS 50

bool bcm_vk_drv_access_ok(काष्ठा bcm_vk *vk)
अणु
	वापस (!!atomic_पढ़ो(&vk->msgq_inited));
पूर्ण

व्योम bcm_vk_set_host_alert(काष्ठा bcm_vk *vk, u32 bit_mask)
अणु
	काष्ठा bcm_vk_alert *alert = &vk->host_alert;
	अचिन्हित दीर्घ flags;

	/* use irqsave version as this maybe called inside समयr पूर्णांकerrupt */
	spin_lock_irqsave(&vk->host_alert_lock, flags);
	alert->notfs |= bit_mask;
	spin_unlock_irqrestore(&vk->host_alert_lock, flags);

	अगर (test_and_set_bit(BCM_VK_WQ_NOTF_PEND, vk->wq_offload) == 0)
		queue_work(vk->wq_thपढ़ो, &vk->wq_work);
पूर्ण

/*
 * Heartbeat related defines
 * The heartbeat from host is a last resort.  If stuck condition happens
 * on the card, firmware is supposed to detect it.  Thereक्रमe, the heartbeat
 * values used will be more relaxed on the driver, which need to be bigger
 * than the watchकरोg समयout on the card.  The watchकरोg समयout on the card
 * is 20s, with a jitter of 2s => 22s.  We use a value of 27s here.
 */
#घोषणा BCM_VK_HB_TIMER_S 3
#घोषणा BCM_VK_HB_TIMER_VALUE (BCM_VK_HB_TIMER_S * HZ)
#घोषणा BCM_VK_HB_LOST_MAX (27 / BCM_VK_HB_TIMER_S)

अटल व्योम bcm_vk_hb_poll(काष्ठा समयr_list *t)
अणु
	u32 upसमय_s;
	काष्ठा bcm_vk_hb_ctrl *hb = container_of(t, काष्ठा bcm_vk_hb_ctrl,
						 समयr);
	काष्ठा bcm_vk *vk = container_of(hb, काष्ठा bcm_vk, hb_ctrl);

	अगर (bcm_vk_drv_access_ok(vk) && hb_mon_is_on()) अणु
		/* पढ़ो upसमय from रेजिस्टर and compare */
		upसमय_s = vkपढ़ो32(vk, BAR_0, BAR_OS_UPTIME);

		अगर (upसमय_s == hb->last_upसमय)
			hb->lost_cnt++;
		अन्यथा /* reset to aव्योम accumulation */
			hb->lost_cnt = 0;

		dev_dbg(&vk->pdev->dev, "Last uptime %d current %d, lost %d\n",
			hb->last_upसमय, upसमय_s, hb->lost_cnt);

		/*
		 * अगर the पूर्णांकerface goes करोwn without any activity, a value
		 * of 0xFFFFFFFF will be continuously पढ़ो, and the detection
		 * will be happened eventually.
		 */
		hb->last_upसमय = upसमय_s;
	पूर्ण अन्यथा अणु
		/* reset heart beat lost cnt */
		hb->lost_cnt = 0;
	पूर्ण

	/* next, check अगर heartbeat exceeds limit */
	अगर (hb->lost_cnt > BCM_VK_HB_LOST_MAX) अणु
		dev_err(&vk->pdev->dev, "Heartbeat Misses %d times, %d s!\n",
			BCM_VK_HB_LOST_MAX,
			BCM_VK_HB_LOST_MAX * BCM_VK_HB_TIMER_S);

		bcm_vk_blk_drv_access(vk);
		bcm_vk_set_host_alert(vk, ERR_LOG_HOST_HB_FAIL);
	पूर्ण
	/* re-arm समयr */
	mod_समयr(&hb->समयr, jअगरfies + BCM_VK_HB_TIMER_VALUE);
पूर्ण

व्योम bcm_vk_hb_init(काष्ठा bcm_vk *vk)
अणु
	काष्ठा bcm_vk_hb_ctrl *hb = &vk->hb_ctrl;

	समयr_setup(&hb->समयr, bcm_vk_hb_poll, 0);
	mod_समयr(&hb->समयr, jअगरfies + BCM_VK_HB_TIMER_VALUE);
पूर्ण

व्योम bcm_vk_hb_deinit(काष्ठा bcm_vk *vk)
अणु
	काष्ठा bcm_vk_hb_ctrl *hb = &vk->hb_ctrl;

	del_समयr(&hb->समयr);
पूर्ण

अटल व्योम bcm_vk_msgid_biपंचांगap_clear(काष्ठा bcm_vk *vk,
				      अचिन्हित पूर्णांक start,
				      अचिन्हित पूर्णांक nbits)
अणु
	spin_lock(&vk->msg_id_lock);
	biपंचांगap_clear(vk->bmap, start, nbits);
	spin_unlock(&vk->msg_id_lock);
पूर्ण

/*
 * allocate a ctx per file काष्ठा
 */
अटल काष्ठा bcm_vk_ctx *bcm_vk_get_ctx(काष्ठा bcm_vk *vk, स्थिर pid_t pid)
अणु
	u32 i;
	काष्ठा bcm_vk_ctx *ctx = शून्य;
	u32 hash_idx = hash_32(pid, VK_PID_HT_SHIFT_BIT);

	spin_lock(&vk->ctx_lock);

	/* check अगर it is in reset, अगर so, करोn't allow */
	अगर (vk->reset_pid) अणु
		dev_err(&vk->pdev->dev,
			"No context allowed during reset by pid %d\n",
			vk->reset_pid);

		जाओ in_reset_निकास;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vk->ctx); i++) अणु
		अगर (!vk->ctx[i].in_use) अणु
			vk->ctx[i].in_use = true;
			ctx = &vk->ctx[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!ctx) अणु
		dev_err(&vk->pdev->dev, "All context in use\n");

		जाओ all_in_use_निकास;
	पूर्ण

	/* set the pid and insert it to hash table */
	ctx->pid = pid;
	ctx->hash_idx = hash_idx;
	list_add_tail(&ctx->node, &vk->pid_ht[hash_idx].head);

	/* increase kref */
	kref_get(&vk->kref);

	/* clear counter */
	atomic_set(&ctx->pend_cnt, 0);
	atomic_set(&ctx->dma_cnt, 0);
	init_रुकोqueue_head(&ctx->rd_wq);

all_in_use_निकास:
in_reset_निकास:
	spin_unlock(&vk->ctx_lock);

	वापस ctx;
पूर्ण

अटल u16 bcm_vk_get_msg_id(काष्ठा bcm_vk *vk)
अणु
	u16 rc = VK_MSG_ID_OVERFLOW;
	u16 test_bit_count = 0;

	spin_lock(&vk->msg_id_lock);
	जबतक (test_bit_count < (VK_MSG_ID_BITMAP_SIZE - 1)) अणु
		/*
		 * first समय come in this loop, msg_id will be 0
		 * and the first one tested will be 1.  We skip
		 * VK_SIMPLEX_MSG_ID (0) क्रम one way host2vk
		 * communication
		 */
		vk->msg_id++;
		अगर (vk->msg_id == VK_MSG_ID_BITMAP_SIZE)
			vk->msg_id = 1;

		अगर (test_bit(vk->msg_id, vk->bmap)) अणु
			test_bit_count++;
			जारी;
		पूर्ण
		rc = vk->msg_id;
		biपंचांगap_set(vk->bmap, vk->msg_id, 1);
		अवरोध;
	पूर्ण
	spin_unlock(&vk->msg_id_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक bcm_vk_मुक्त_ctx(काष्ठा bcm_vk *vk, काष्ठा bcm_vk_ctx *ctx)
अणु
	u32 idx;
	u32 hash_idx;
	pid_t pid;
	काष्ठा bcm_vk_ctx *entry;
	पूर्णांक count = 0;

	अगर (!ctx) अणु
		dev_err(&vk->pdev->dev, "NULL context detected\n");
		वापस -EINVAL;
	पूर्ण
	idx = ctx->idx;
	pid = ctx->pid;

	spin_lock(&vk->ctx_lock);

	अगर (!vk->ctx[idx].in_use) अणु
		dev_err(&vk->pdev->dev, "context[%d] not in use!\n", idx);
	पूर्ण अन्यथा अणु
		vk->ctx[idx].in_use = false;
		vk->ctx[idx].miscdev = शून्य;

		/* Remove it from hash list and see अगर it is the last one. */
		list_del(&ctx->node);
		hash_idx = ctx->hash_idx;
		list_क्रम_each_entry(entry, &vk->pid_ht[hash_idx].head, node) अणु
			अगर (entry->pid == pid)
				count++;
		पूर्ण
	पूर्ण

	spin_unlock(&vk->ctx_lock);

	वापस count;
पूर्ण

अटल व्योम bcm_vk_मुक्त_wkent(काष्ठा device *dev, काष्ठा bcm_vk_wkent *entry)
अणु
	पूर्णांक proc_cnt;

	bcm_vk_sg_मुक्त(dev, entry->dma, VK_DMA_MAX_ADDRS, &proc_cnt);
	अगर (proc_cnt)
		atomic_dec(&entry->ctx->dma_cnt);

	kमुक्त(entry->to_h_msg);
	kमुक्त(entry);
पूर्ण

अटल व्योम bcm_vk_drain_all_pend(काष्ठा device *dev,
				  काष्ठा bcm_vk_msg_chan *chan,
				  काष्ठा bcm_vk_ctx *ctx)
अणु
	u32 num;
	काष्ठा bcm_vk_wkent *entry, *पंचांगp;
	काष्ठा bcm_vk *vk;
	काष्ठा list_head del_q;

	अगर (ctx)
		vk = container_of(ctx->miscdev, काष्ठा bcm_vk, miscdev);

	INIT_LIST_HEAD(&del_q);
	spin_lock(&chan->pendq_lock);
	क्रम (num = 0; num < chan->q_nr; num++) अणु
		list_क्रम_each_entry_safe(entry, पंचांगp, &chan->pendq[num], node) अणु
			अगर ((!ctx) || (entry->ctx->idx == ctx->idx)) अणु
				list_del(&entry->node);
				list_add_tail(&entry->node, &del_q);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&chan->pendq_lock);

	/* batch clean up */
	num = 0;
	list_क्रम_each_entry_safe(entry, पंचांगp, &del_q, node) अणु
		list_del(&entry->node);
		num++;
		अगर (ctx) अणु
			काष्ठा vk_msg_blk *msg;
			पूर्णांक bit_set;
			bool responded;
			u32 msg_id;

			/* अगर it is specअगरic ctx, log क्रम any stuck */
			msg = entry->to_v_msg;
			msg_id = get_msg_id(msg);
			bit_set = test_bit(msg_id, vk->bmap);
			responded = entry->to_h_msg ? true : false;
			अगर (num <= batch_log)
				dev_info(dev,
					 "Drained: fid %u size %u msg 0x%x(seq-%x) ctx 0x%x[fd-%d] args:[0x%x 0x%x] resp %s, bmap %d\n",
					 msg->function_id, msg->size,
					 msg_id, entry->seq_num,
					 msg->context_id, entry->ctx->idx,
					 msg->cmd, msg->arg,
					 responded ? "T" : "F", bit_set);
			अगर (responded)
				atomic_dec(&ctx->pend_cnt);
			अन्यथा अगर (bit_set)
				bcm_vk_msgid_biपंचांगap_clear(vk, msg_id, 1);
		पूर्ण
		bcm_vk_मुक्त_wkent(dev, entry);
	पूर्ण
	अगर (num && ctx)
		dev_info(dev, "Total drained items %d [fd-%d]\n",
			 num, ctx->idx);
पूर्ण

व्योम bcm_vk_drain_msg_on_reset(काष्ठा bcm_vk *vk)
अणु
	bcm_vk_drain_all_pend(&vk->pdev->dev, &vk->to_v_msg_chan, शून्य);
	bcm_vk_drain_all_pend(&vk->pdev->dev, &vk->to_h_msg_chan, शून्य);
पूर्ण

/*
 * Function to sync up the messages queue info that is provided by BAR1
 */
पूर्णांक bcm_vk_sync_msgq(काष्ठा bcm_vk *vk, bool क्रमce_sync)
अणु
	काष्ठा bcm_vk_msgq __iomem *msgq;
	काष्ठा device *dev = &vk->pdev->dev;
	u32 msgq_off;
	u32 num_q;
	काष्ठा bcm_vk_msg_chan *chan_list[] = अणु&vk->to_v_msg_chan,
					       &vk->to_h_msg_chanपूर्ण;
	काष्ठा bcm_vk_msg_chan *chan;
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	/*
	 * If the driver is loaded at startup where vk OS is not up yet,
	 * the msgq-info may not be available until a later समय.  In
	 * this हाल, we skip and the sync function is supposed to be
	 * called again.
	 */
	अगर (!bcm_vk_msgq_marker_valid(vk)) अणु
		dev_info(dev, "BAR1 msgq marker not initialized.\n");
		वापस -EAGAIN;
	पूर्ण

	msgq_off = vkपढ़ो32(vk, BAR_1, VK_BAR1_MSGQ_CTRL_OFF);

	/* each side is always half the total  */
	num_q = vkपढ़ो32(vk, BAR_1, VK_BAR1_MSGQ_NR) / 2;
	अगर (!num_q || (num_q > VK_MSGQ_PER_CHAN_MAX)) अणु
		dev_err(dev,
			"Advertised msgq %d error - max %d allowed\n",
			num_q, VK_MSGQ_PER_CHAN_MAX);
		वापस -EINVAL;
	पूर्ण

	vk->to_v_msg_chan.q_nr = num_q;
	vk->to_h_msg_chan.q_nr = num_q;

	/* first msgq location */
	msgq = vk->bar[BAR_1] + msgq_off;

	/*
	 * अगर this function is called when it is alपढ़ोy inited,
	 * something is wrong
	 */
	अगर (bcm_vk_drv_access_ok(vk) && !क्रमce_sync) अणु
		dev_err(dev, "Msgq info already in sync\n");
		वापस -EPERM;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(chan_list); i++) अणु
		chan = chan_list[i];
		स_रखो(chan->sync_qinfo, 0, माप(chan->sync_qinfo));

		क्रम (j = 0; j < num_q; j++) अणु
			काष्ठा bcm_vk_sync_qinfo *qinfo;
			u32 msgq_start;
			u32 msgq_size;
			u32 msgq_nxt;
			u32 msgq_db_offset, q_db_offset;

			chan->msgq[j] = msgq;
			msgq_start = पढ़ोl_relaxed(&msgq->start);
			msgq_size = पढ़ोl_relaxed(&msgq->size);
			msgq_nxt = पढ़ोl_relaxed(&msgq->nxt);
			msgq_db_offset = पढ़ोl_relaxed(&msgq->db_offset);
			q_db_offset = (msgq_db_offset & ((1 << DB_SHIFT) - 1));
			अगर (q_db_offset  == (~msgq_db_offset >> DB_SHIFT))
				msgq_db_offset = q_db_offset;
			अन्यथा
				/* fall back to शेष */
				msgq_db_offset = VK_BAR0_Q_DB_BASE(j);

			dev_info(dev,
				 "MsgQ[%d] type %d num %d, @ 0x%x, db_offset 0x%x rd_idx %d wr_idx %d, size %d, nxt 0x%x\n",
				 j,
				 पढ़ोw_relaxed(&msgq->type),
				 पढ़ोw_relaxed(&msgq->num),
				 msgq_start,
				 msgq_db_offset,
				 पढ़ोl_relaxed(&msgq->rd_idx),
				 पढ़ोl_relaxed(&msgq->wr_idx),
				 msgq_size,
				 msgq_nxt);

			qinfo = &chan->sync_qinfo[j];
			/* क्रमmulate and record अटल info */
			qinfo->q_start = vk->bar[BAR_1] + msgq_start;
			qinfo->q_size = msgq_size;
			/* set low threshold as 50% or 1/2 */
			qinfo->q_low = qinfo->q_size >> 1;
			qinfo->q_mask = qinfo->q_size - 1;
			qinfo->q_db_offset = msgq_db_offset;

			msgq++;
		पूर्ण
	पूर्ण
	atomic_set(&vk->msgq_inited, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_vk_msg_chan_init(काष्ठा bcm_vk_msg_chan *chan)
अणु
	u32 i;

	mutex_init(&chan->msgq_mutex);
	spin_lock_init(&chan->pendq_lock);
	क्रम (i = 0; i < VK_MSGQ_MAX_NR; i++)
		INIT_LIST_HEAD(&chan->pendq[i]);

	वापस 0;
पूर्ण

अटल व्योम bcm_vk_append_pendq(काष्ठा bcm_vk_msg_chan *chan, u16 q_num,
				काष्ठा bcm_vk_wkent *entry)
अणु
	काष्ठा bcm_vk_ctx *ctx;

	spin_lock(&chan->pendq_lock);
	list_add_tail(&entry->node, &chan->pendq[q_num]);
	अगर (entry->to_h_msg) अणु
		ctx = entry->ctx;
		atomic_inc(&ctx->pend_cnt);
		wake_up_पूर्णांकerruptible(&ctx->rd_wq);
	पूर्ण
	spin_unlock(&chan->pendq_lock);
पूर्ण

अटल u32 bcm_vk_append_ib_sgl(काष्ठा bcm_vk *vk,
				काष्ठा bcm_vk_wkent *entry,
				काष्ठा _vk_data *data,
				अचिन्हित पूर्णांक num_planes)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक item_cnt = 0;
	काष्ठा device *dev = &vk->pdev->dev;
	काष्ठा bcm_vk_msg_chan *chan = &vk->to_v_msg_chan;
	काष्ठा vk_msg_blk *msg = &entry->to_v_msg[0];
	काष्ठा bcm_vk_msgq __iomem *msgq;
	काष्ठा bcm_vk_sync_qinfo *qinfo;
	u32 ib_sgl_size = 0;
	u8 *buf = (u8 *)&entry->to_v_msg[entry->to_v_blks];
	u32 avail;
	u32 q_num;

	/* check अगर high watermark is hit, and अगर so, skip */
	q_num = get_q_num(msg);
	msgq = chan->msgq[q_num];
	qinfo = &chan->sync_qinfo[q_num];
	avail = msgq_avail_space(msgq, qinfo);
	अगर (avail < qinfo->q_low) अणु
		dev_dbg(dev, "Skip inserting inband SGL, [0x%x/0x%x]\n",
			avail, qinfo->q_size);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < num_planes; i++) अणु
		अगर (data[i].address &&
		    (ib_sgl_size + data[i].size) <= vk->ib_sgl_size) अणु
			item_cnt++;
			स_नकल(buf, entry->dma[i].sglist, data[i].size);
			ib_sgl_size += data[i].size;
			buf += data[i].size;
		पूर्ण
	पूर्ण

	dev_dbg(dev, "Num %u sgl items appended, size 0x%x, room 0x%x\n",
		item_cnt, ib_sgl_size, vk->ib_sgl_size);

	/* round up size */
	ib_sgl_size = (ib_sgl_size + VK_MSGQ_BLK_SIZE - 1)
		       >> VK_MSGQ_BLK_SZ_SHIFT;

	वापस ib_sgl_size;
पूर्ण

व्योम bcm_to_v_q_करोorbell(काष्ठा bcm_vk *vk, u32 q_num, u32 db_val)
अणु
	काष्ठा bcm_vk_msg_chan *chan = &vk->to_v_msg_chan;
	काष्ठा bcm_vk_sync_qinfo *qinfo = &chan->sync_qinfo[q_num];

	vkग_लिखो32(vk, db_val, BAR_0, qinfo->q_db_offset);
पूर्ण

अटल पूर्णांक bcm_to_v_msg_enqueue(काष्ठा bcm_vk *vk, काष्ठा bcm_vk_wkent *entry)
अणु
	अटल u32 seq_num;
	काष्ठा bcm_vk_msg_chan *chan = &vk->to_v_msg_chan;
	काष्ठा device *dev = &vk->pdev->dev;
	काष्ठा vk_msg_blk *src = &entry->to_v_msg[0];

	काष्ठा vk_msg_blk __iomem *dst;
	काष्ठा bcm_vk_msgq __iomem *msgq;
	काष्ठा bcm_vk_sync_qinfo *qinfo;
	u32 q_num = get_q_num(src);
	u32 wr_idx; /* local copy */
	u32 i;
	u32 avail;
	u32 retry;

	अगर (entry->to_v_blks != src->size + 1) अणु
		dev_err(dev, "number of blks %d not matching %d MsgId[0x%x]: func %d ctx 0x%x\n",
			entry->to_v_blks,
			src->size + 1,
			get_msg_id(src),
			src->function_id,
			src->context_id);
		वापस -EMSGSIZE;
	पूर्ण

	msgq = chan->msgq[q_num];
	qinfo = &chan->sync_qinfo[q_num];

	mutex_lock(&chan->msgq_mutex);

	avail = msgq_avail_space(msgq, qinfo);

	/* अगर not enough space, वापस EAGAIN and let app handles it */
	retry = 0;
	जबतक ((avail < entry->to_v_blks) &&
	       (retry++ < BCM_VK_H2VK_ENQ_RETRY)) अणु
		mutex_unlock(&chan->msgq_mutex);

		msleep(BCM_VK_H2VK_ENQ_RETRY_DELAY_MS);
		mutex_lock(&chan->msgq_mutex);
		avail = msgq_avail_space(msgq, qinfo);
	पूर्ण
	अगर (retry > BCM_VK_H2VK_ENQ_RETRY) अणु
		mutex_unlock(&chan->msgq_mutex);
		वापस -EAGAIN;
	पूर्ण

	/* at this poपूर्णांक, mutex is taken and there is enough space */
	entry->seq_num = seq_num++; /* update debug seq number */
	wr_idx = पढ़ोl_relaxed(&msgq->wr_idx);

	अगर (wr_idx >= qinfo->q_size) अणु
		dev_crit(dev, "Invalid wr_idx 0x%x => max 0x%x!",
			 wr_idx, qinfo->q_size);
		bcm_vk_blk_drv_access(vk);
		bcm_vk_set_host_alert(vk, ERR_LOG_HOST_PCIE_DWN);
		जाओ idx_err;
	पूर्ण

	dst = msgq_blk_addr(qinfo, wr_idx);
	क्रम (i = 0; i < entry->to_v_blks; i++) अणु
		स_नकल_toio(dst, src, माप(*dst));

		src++;
		wr_idx = msgq_inc(qinfo, wr_idx, 1);
		dst = msgq_blk_addr(qinfo, wr_idx);
	पूर्ण

	/* flush the ग_लिखो poपूर्णांकer */
	ग_लिखोl(wr_idx, &msgq->wr_idx);

	/* log new info क्रम debugging */
	dev_dbg(dev,
		"MsgQ[%d] [Rd Wr] = [%d %d] blks inserted %d - Q = [u-%d a-%d]/%d\n",
		पढ़ोl_relaxed(&msgq->num),
		पढ़ोl_relaxed(&msgq->rd_idx),
		wr_idx,
		entry->to_v_blks,
		msgq_occupied(msgq, qinfo),
		msgq_avail_space(msgq, qinfo),
		पढ़ोl_relaxed(&msgq->size));
	/*
	 * press करोor bell based on queue number. 1 is added to the wr_idx
	 * to aव्योम the value of 0 appearing on the VK side to distinguish
	 * from initial value.
	 */
	bcm_to_v_q_करोorbell(vk, q_num, wr_idx + 1);
idx_err:
	mutex_unlock(&chan->msgq_mutex);
	वापस 0;
पूर्ण

पूर्णांक bcm_vk_send_shutकरोwn_msg(काष्ठा bcm_vk *vk, u32 shut_type,
			     स्थिर pid_t pid, स्थिर u32 q_num)
अणु
	पूर्णांक rc = 0;
	काष्ठा bcm_vk_wkent *entry;
	काष्ठा device *dev = &vk->pdev->dev;

	/*
	 * check अगर the marker is still good.  Someबार, the PCIe पूर्णांकerface may
	 * have gone करोne, and अगर so and we ship करोwn thing based on broken
	 * values, kernel may panic.
	 */
	अगर (!bcm_vk_msgq_marker_valid(vk)) अणु
		dev_info(dev, "PCIe comm chan - invalid marker (0x%x)!\n",
			 vkपढ़ो32(vk, BAR_1, VK_BAR1_MSGQ_DEF_RDY));
		वापस -EINVAL;
	पूर्ण

	entry = kzalloc(माप(*entry) +
			माप(काष्ठा vk_msg_blk), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	/* fill up necessary data */
	entry->to_v_msg[0].function_id = VK_FID_SHUTDOWN;
	set_q_num(&entry->to_v_msg[0], q_num);
	set_msg_id(&entry->to_v_msg[0], VK_SIMPLEX_MSG_ID);
	entry->to_v_blks = 1; /* always 1 block */

	entry->to_v_msg[0].cmd = shut_type;
	entry->to_v_msg[0].arg = pid;

	rc = bcm_to_v_msg_enqueue(vk, entry);
	अगर (rc)
		dev_err(dev,
			"Sending shutdown message to q %d for pid %d fails.\n",
			get_q_num(&entry->to_v_msg[0]), pid);

	kमुक्त(entry);

	वापस rc;
पूर्ण

अटल पूर्णांक bcm_vk_handle_last_sess(काष्ठा bcm_vk *vk, स्थिर pid_t pid,
				   स्थिर u32 q_num)
अणु
	पूर्णांक rc = 0;
	काष्ठा device *dev = &vk->pdev->dev;

	/*
	 * करोn't send करोwn or करो anything अगर message queue is not initialized
	 * and अगर it is the reset session, clear it.
	 */
	अगर (!bcm_vk_drv_access_ok(vk)) अणु
		अगर (vk->reset_pid == pid)
			vk->reset_pid = 0;
		वापस -EPERM;
	पूर्ण

	dev_dbg(dev, "No more sessions, shut down pid %d\n", pid);

	/* only need to करो it अगर it is not the reset process */
	अगर (vk->reset_pid != pid)
		rc = bcm_vk_send_shutकरोwn_msg(vk, VK_SHUTDOWN_PID, pid, q_num);
	अन्यथा
		/* put reset_pid to 0 अगर it is निकासing last session */
		vk->reset_pid = 0;

	वापस rc;
पूर्ण

अटल काष्ठा bcm_vk_wkent *bcm_vk_dequeue_pending(काष्ठा bcm_vk *vk,
						   काष्ठा bcm_vk_msg_chan *chan,
						   u16 q_num,
						   u16 msg_id)
अणु
	bool found = false;
	काष्ठा bcm_vk_wkent *entry;

	spin_lock(&chan->pendq_lock);
	list_क्रम_each_entry(entry, &chan->pendq[q_num], node) अणु
		अगर (get_msg_id(&entry->to_v_msg[0]) == msg_id) अणु
			list_del(&entry->node);
			found = true;
			bcm_vk_msgid_biपंचांगap_clear(vk, msg_id, 1);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&chan->pendq_lock);
	वापस ((found) ? entry : शून्य);
पूर्ण

s32 bcm_to_h_msg_dequeue(काष्ठा bcm_vk *vk)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	काष्ठा bcm_vk_msg_chan *chan = &vk->to_h_msg_chan;
	काष्ठा vk_msg_blk *data;
	काष्ठा vk_msg_blk __iomem *src;
	काष्ठा vk_msg_blk *dst;
	काष्ठा bcm_vk_msgq __iomem *msgq;
	काष्ठा bcm_vk_sync_qinfo *qinfo;
	काष्ठा bcm_vk_wkent *entry;
	u32 rd_idx, wr_idx;
	u32 q_num, msg_id, j;
	u32 num_blks;
	s32 total = 0;
	पूर्णांक cnt = 0;
	पूर्णांक msg_processed = 0;
	पूर्णांक max_msg_to_process;
	bool निकास_loop;

	/*
	 * drain all the messages from the queues, and find its pending
	 * entry in the to_v queue, based on msg_id & q_num, and move the
	 * entry to the to_h pending queue, रुकोing क्रम user space
	 * program to extract
	 */
	mutex_lock(&chan->msgq_mutex);

	क्रम (q_num = 0; q_num < chan->q_nr; q_num++) अणु
		msgq = chan->msgq[q_num];
		qinfo = &chan->sync_qinfo[q_num];
		max_msg_to_process = BCM_VK_MSG_PROC_MAX_LOOP * qinfo->q_size;

		rd_idx = पढ़ोl_relaxed(&msgq->rd_idx);
		wr_idx = पढ़ोl_relaxed(&msgq->wr_idx);
		msg_processed = 0;
		निकास_loop = false;
		जबतक ((rd_idx != wr_idx) && !निकास_loop) अणु
			u8 src_size;

			/*
			 * Make a local copy and get poपूर्णांकer to src blk
			 * The rd_idx is masked beक्रमe getting the poपूर्णांकer to
			 * aव्योम out of bound access in हाल the पूर्णांकerface goes
			 * करोwn.  It will end up poपूर्णांकing to the last block in
			 * the buffer, but subsequent src->size check would be
			 * able to catch this.
			 */
			src = msgq_blk_addr(qinfo, rd_idx & qinfo->q_mask);
			src_size = पढ़ोb(&src->size);

			अगर ((rd_idx >= qinfo->q_size) ||
			    (src_size > (qinfo->q_size - 1))) अणु
				dev_crit(dev,
					 "Invalid rd_idx 0x%x or size 0x%x => max 0x%x!",
					 rd_idx, src_size, qinfo->q_size);
				bcm_vk_blk_drv_access(vk);
				bcm_vk_set_host_alert(vk,
						      ERR_LOG_HOST_PCIE_DWN);
				जाओ idx_err;
			पूर्ण

			num_blks = src_size + 1;
			data = kzalloc(num_blks * VK_MSGQ_BLK_SIZE, GFP_KERNEL);
			अगर (data) अणु
				/* copy messages and linearize it */
				dst = data;
				क्रम (j = 0; j < num_blks; j++) अणु
					स_नकल_fromio(dst, src, माप(*dst));

					dst++;
					rd_idx = msgq_inc(qinfo, rd_idx, 1);
					src = msgq_blk_addr(qinfo, rd_idx);
				पूर्ण
				total++;
			पूर्ण अन्यथा अणु
				/*
				 * अगर we could not allocate memory in kernel,
				 * that is fatal.
				 */
				dev_crit(dev, "Kernel mem allocation failure.\n");
				total = -ENOMEM;
				जाओ idx_err;
			पूर्ण

			/* flush rd poपूर्णांकer after a message is dequeued */
			ग_लिखोl(rd_idx, &msgq->rd_idx);

			/* log new info क्रम debugging */
			dev_dbg(dev,
				"MsgQ[%d] [Rd Wr] = [%d %d] blks extracted %d - Q = [u-%d a-%d]/%d\n",
				पढ़ोl_relaxed(&msgq->num),
				rd_idx,
				wr_idx,
				num_blks,
				msgq_occupied(msgq, qinfo),
				msgq_avail_space(msgq, qinfo),
				पढ़ोl_relaxed(&msgq->size));

			/*
			 * No need to search अगर it is an स्वतःnomous one-way
			 * message from driver, as these messages करो not bear
			 * a to_v pending item. Currently, only the shutकरोwn
			 * message falls पूर्णांकo this category.
			 */
			अगर (data->function_id == VK_FID_SHUTDOWN) अणु
				kमुक्त(data);
				जारी;
			पूर्ण

			msg_id = get_msg_id(data);
			/* lookup original message in to_v direction */
			entry = bcm_vk_dequeue_pending(vk,
						       &vk->to_v_msg_chan,
						       q_num,
						       msg_id);

			/*
			 * अगर there is message to करोes not have prior send,
			 * this is the location to add here
			 */
			अगर (entry) अणु
				entry->to_h_blks = num_blks;
				entry->to_h_msg = data;
				bcm_vk_append_pendq(&vk->to_h_msg_chan,
						    q_num, entry);

			पूर्ण अन्यथा अणु
				अगर (cnt++ < batch_log)
					dev_info(dev,
						 "Could not find MsgId[0x%x] for resp func %d bmap %d\n",
						 msg_id, data->function_id,
						 test_bit(msg_id, vk->bmap));
				kमुक्त(data);
			पूर्ण
			/* Fetch wr_idx to handle more back-to-back events */
			wr_idx = पढ़ोl(&msgq->wr_idx);

			/*
			 * cap the max so that even we try to handle more back-to-back events,
			 * so that it won't hold CPU too दीर्घ or in हाल rd/wr idexes are
			 * corrupted which triggers infinite looping.
			 */
			अगर (++msg_processed >= max_msg_to_process) अणु
				dev_warn(dev, "Q[%d] Per loop processing exceeds %d\n",
					 q_num, max_msg_to_process);
				निकास_loop = true;
			पूर्ण
		पूर्ण
	पूर्ण
idx_err:
	mutex_unlock(&chan->msgq_mutex);
	dev_dbg(dev, "total %d drained from queues\n", total);

	वापस total;
पूर्ण

/*
 * init routine क्रम all required data काष्ठाures
 */
अटल पूर्णांक bcm_vk_data_init(काष्ठा bcm_vk *vk)
अणु
	पूर्णांक i;

	spin_lock_init(&vk->ctx_lock);
	क्रम (i = 0; i < ARRAY_SIZE(vk->ctx); i++) अणु
		vk->ctx[i].in_use = false;
		vk->ctx[i].idx = i;	/* self identity */
		vk->ctx[i].miscdev = शून्य;
	पूर्ण
	spin_lock_init(&vk->msg_id_lock);
	spin_lock_init(&vk->host_alert_lock);
	vk->msg_id = 0;

	/* initialize hash table */
	क्रम (i = 0; i < VK_PID_HT_SZ; i++)
		INIT_LIST_HEAD(&vk->pid_ht[i].head);

	वापस 0;
पूर्ण

irqवापस_t bcm_vk_msgq_irqhandler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_vk *vk = dev_id;

	अगर (!bcm_vk_drv_access_ok(vk)) अणु
		dev_err(&vk->pdev->dev,
			"Interrupt %d received when msgq not inited\n", irq);
		जाओ skip_schedule_work;
	पूर्ण

	queue_work(vk->wq_thपढ़ो, &vk->wq_work);

skip_schedule_work:
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक bcm_vk_खोलो(काष्ठा inode *inode, काष्ठा file *p_file)
अणु
	काष्ठा bcm_vk_ctx *ctx;
	काष्ठा miscdevice *miscdev = (काष्ठा miscdevice *)p_file->निजी_data;
	काष्ठा bcm_vk *vk = container_of(miscdev, काष्ठा bcm_vk, miscdev);
	काष्ठा device *dev = &vk->pdev->dev;
	पूर्णांक rc = 0;

	/* get a context and set it up क्रम file */
	ctx = bcm_vk_get_ctx(vk, task_tgid_nr(current));
	अगर (!ctx) अणु
		dev_err(dev, "Error allocating context\n");
		rc = -ENOMEM;
	पूर्ण अन्यथा अणु
		/*
		 * set up context and replace निजी data with context क्रम
		 * other methods to use.  Reason क्रम the context is because
		 * it is allowed क्रम multiple sessions to खोलो the sysfs, and
		 * क्रम each file खोलो, when upper layer query the response,
		 * only those that are tied to a specअगरic खोलो should be
		 * वापसed.  The context->idx will be used क्रम such binding
		 */
		ctx->miscdev = miscdev;
		p_file->निजी_data = ctx;
		dev_dbg(dev, "ctx_returned with idx %d, pid %d\n",
			ctx->idx, ctx->pid);
	पूर्ण
	वापस rc;
पूर्ण

sमाप_प्रकार bcm_vk_पढ़ो(काष्ठा file *p_file,
		    अक्षर __user *buf,
		    माप_प्रकार count,
		    loff_t *f_pos)
अणु
	sमाप_प्रकार rc = -ENOMSG;
	काष्ठा bcm_vk_ctx *ctx = p_file->निजी_data;
	काष्ठा bcm_vk *vk = container_of(ctx->miscdev, काष्ठा bcm_vk,
					 miscdev);
	काष्ठा device *dev = &vk->pdev->dev;
	काष्ठा bcm_vk_msg_chan *chan = &vk->to_h_msg_chan;
	काष्ठा bcm_vk_wkent *entry = शून्य;
	u32 q_num;
	u32 rsp_length;
	bool found = false;

	अगर (!bcm_vk_drv_access_ok(vk))
		वापस -EPERM;

	dev_dbg(dev, "Buf count %zu\n", count);
	found = false;

	/*
	 * search through the pendq on the to_h chan, and वापस only those
	 * that beदीर्घs to the same context.  Search is always from the high to
	 * the low priority queues
	 */
	spin_lock(&chan->pendq_lock);
	क्रम (q_num = 0; q_num < chan->q_nr; q_num++) अणु
		list_क्रम_each_entry(entry, &chan->pendq[q_num], node) अणु
			अगर (entry->ctx->idx == ctx->idx) अणु
				अगर (count >=
				    (entry->to_h_blks * VK_MSGQ_BLK_SIZE)) अणु
					list_del(&entry->node);
					atomic_dec(&ctx->pend_cnt);
					found = true;
				पूर्ण अन्यथा अणु
					/* buffer not big enough */
					rc = -EMSGSIZE;
				पूर्ण
				जाओ पढ़ो_loop_निकास;
			पूर्ण
		पूर्ण
	पूर्ण
पढ़ो_loop_निकास:
	spin_unlock(&chan->pendq_lock);

	अगर (found) अणु
		/* retrieve the passed करोwn msg_id */
		set_msg_id(&entry->to_h_msg[0], entry->usr_msg_id);
		rsp_length = entry->to_h_blks * VK_MSGQ_BLK_SIZE;
		अगर (copy_to_user(buf, entry->to_h_msg, rsp_length) == 0)
			rc = rsp_length;

		bcm_vk_मुक्त_wkent(dev, entry);
	पूर्ण अन्यथा अगर (rc == -EMSGSIZE) अणु
		काष्ठा vk_msg_blk पंचांगp_msg = entry->to_h_msg[0];

		/*
		 * in this हाल, वापस just the first block, so
		 * that app knows what size it is looking क्रम.
		 */
		set_msg_id(&पंचांगp_msg, entry->usr_msg_id);
		पंचांगp_msg.size = entry->to_h_blks - 1;
		अगर (copy_to_user(buf, &पंचांगp_msg, VK_MSGQ_BLK_SIZE) != 0) अणु
			dev_err(dev, "Error return 1st block in -EMSGSIZE\n");
			rc = -EFAULT;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

sमाप_प्रकार bcm_vk_ग_लिखो(काष्ठा file *p_file,
		     स्थिर अक्षर __user *buf,
		     माप_प्रकार count,
		     loff_t *f_pos)
अणु
	sमाप_प्रकार rc;
	काष्ठा bcm_vk_ctx *ctx = p_file->निजी_data;
	काष्ठा bcm_vk *vk = container_of(ctx->miscdev, काष्ठा bcm_vk,
					 miscdev);
	काष्ठा bcm_vk_msgq __iomem *msgq;
	काष्ठा device *dev = &vk->pdev->dev;
	काष्ठा bcm_vk_wkent *entry;
	u32 sgl_extra_blks;
	u32 q_num;
	u32 msg_size;
	u32 msgq_size;

	अगर (!bcm_vk_drv_access_ok(vk))
		वापस -EPERM;

	dev_dbg(dev, "Msg count %zu\n", count);

	/* first, करो sanity check where count should be multiple of basic blk */
	अगर (count & (VK_MSGQ_BLK_SIZE - 1)) अणु
		dev_err(dev, "Failure with size %zu not multiple of %zu\n",
			count, VK_MSGQ_BLK_SIZE);
		rc = -EINVAL;
		जाओ ग_लिखो_err;
	पूर्ण

	/* allocate the work entry + buffer क्रम size count and inband sgl */
	entry = kzalloc(माप(*entry) + count + vk->ib_sgl_size,
			GFP_KERNEL);
	अगर (!entry) अणु
		rc = -ENOMEM;
		जाओ ग_लिखो_err;
	पूर्ण

	/* now copy msg from user space, and then क्रमmulate the work entry */
	अगर (copy_from_user(&entry->to_v_msg[0], buf, count)) अणु
		rc = -EFAULT;
		जाओ ग_लिखो_मुक्त_ent;
	पूर्ण

	entry->to_v_blks = count >> VK_MSGQ_BLK_SZ_SHIFT;
	entry->ctx = ctx;

	/* करो a check on the blk size which could not exceed queue space */
	q_num = get_q_num(&entry->to_v_msg[0]);
	msgq = vk->to_v_msg_chan.msgq[q_num];
	msgq_size = पढ़ोl_relaxed(&msgq->size);
	अगर (entry->to_v_blks + (vk->ib_sgl_size >> VK_MSGQ_BLK_SZ_SHIFT)
	    > (msgq_size - 1)) अणु
		dev_err(dev, "Blk size %d exceed max queue size allowed %d\n",
			entry->to_v_blks, msgq_size - 1);
		rc = -EINVAL;
		जाओ ग_लिखो_मुक्त_ent;
	पूर्ण

	/* Use पूर्णांकernal message id */
	entry->usr_msg_id = get_msg_id(&entry->to_v_msg[0]);
	rc = bcm_vk_get_msg_id(vk);
	अगर (rc == VK_MSG_ID_OVERFLOW) अणु
		dev_err(dev, "msg_id overflow\n");
		rc = -EOVERFLOW;
		जाओ ग_लिखो_मुक्त_ent;
	पूर्ण
	set_msg_id(&entry->to_v_msg[0], rc);
	ctx->q_num = q_num;

	dev_dbg(dev,
		"[Q-%d]Message ctx id %d, usr_msg_id 0x%x sent msg_id 0x%x\n",
		ctx->q_num, ctx->idx, entry->usr_msg_id,
		get_msg_id(&entry->to_v_msg[0]));

	अगर (entry->to_v_msg[0].function_id == VK_FID_TRANS_BUF) अणु
		/* Convert any poपूर्णांकers to sg list */
		अचिन्हित पूर्णांक num_planes;
		पूर्णांक dir;
		काष्ठा _vk_data *data;

		/*
		 * check अगर we are in reset, अगर so, no buffer transfer is
		 * allowed and वापस error.
		 */
		अगर (vk->reset_pid) अणु
			dev_dbg(dev, "No Transfer allowed during reset, pid %d.\n",
				ctx->pid);
			rc = -EACCES;
			जाओ ग_लिखो_मुक्त_msgid;
		पूर्ण

		num_planes = entry->to_v_msg[0].cmd & VK_CMD_PLANES_MASK;
		अगर ((entry->to_v_msg[0].cmd & VK_CMD_MASK) == VK_CMD_DOWNLOAD)
			dir = DMA_FROM_DEVICE;
		अन्यथा
			dir = DMA_TO_DEVICE;

		/* Calculate vk_data location */
		/* Go to end of the message */
		msg_size = entry->to_v_msg[0].size;
		अगर (msg_size > entry->to_v_blks) अणु
			rc = -EMSGSIZE;
			जाओ ग_लिखो_मुक्त_msgid;
		पूर्ण

		data = (काष्ठा _vk_data *)&entry->to_v_msg[msg_size + 1];

		/* Now back up to the start of the poपूर्णांकers */
		data -= num_planes;

		/* Convert user addresses to DMA SG List */
		rc = bcm_vk_sg_alloc(dev, entry->dma, dir, data, num_planes);
		अगर (rc)
			जाओ ग_लिखो_मुक्त_msgid;

		atomic_inc(&ctx->dma_cnt);
		/* try to embed inband sgl */
		sgl_extra_blks = bcm_vk_append_ib_sgl(vk, entry, data,
						      num_planes);
		entry->to_v_blks += sgl_extra_blks;
		entry->to_v_msg[0].size += sgl_extra_blks;
	पूर्ण अन्यथा अगर (entry->to_v_msg[0].function_id == VK_FID_INIT &&
		   entry->to_v_msg[0].context_id == VK_NEW_CTX) अणु
		/*
		 * Init happens in 2 stages, only the first stage contains the
		 * pid that needs translating.
		 */
		pid_t org_pid, pid;

		/*
		 * translate the pid पूर्णांकo the unique host space as user
		 * may run sessions inside containers or process
		 * namespaces.
		 */
#घोषणा VK_MSG_PID_MASK 0xffffff00
#घोषणा VK_MSG_PID_SH   8
		org_pid = (entry->to_v_msg[0].arg & VK_MSG_PID_MASK)
			   >> VK_MSG_PID_SH;

		pid = task_tgid_nr(current);
		entry->to_v_msg[0].arg =
			(entry->to_v_msg[0].arg & ~VK_MSG_PID_MASK) |
			(pid << VK_MSG_PID_SH);
		अगर (org_pid != pid)
			dev_dbg(dev, "In PID 0x%x(%d), converted PID 0x%x(%d)\n",
				org_pid, org_pid, pid, pid);
	पूर्ण

	/*
	 * store work entry to pending queue until a response is received.
	 * This needs to be करोne beक्रमe enqueuing the message
	 */
	bcm_vk_append_pendq(&vk->to_v_msg_chan, q_num, entry);

	rc = bcm_to_v_msg_enqueue(vk, entry);
	अगर (rc) अणु
		dev_err(dev, "Fail to enqueue msg to to_v queue\n");

		/* हटाओ message from pending list */
		entry = bcm_vk_dequeue_pending
			       (vk,
				&vk->to_v_msg_chan,
				q_num,
				get_msg_id(&entry->to_v_msg[0]));
		जाओ ग_लिखो_मुक्त_ent;
	पूर्ण

	वापस count;

ग_लिखो_मुक्त_msgid:
	bcm_vk_msgid_biपंचांगap_clear(vk, get_msg_id(&entry->to_v_msg[0]), 1);
ग_लिखो_मुक्त_ent:
	kमुक्त(entry);
ग_लिखो_err:
	वापस rc;
पूर्ण

__poll_t bcm_vk_poll(काष्ठा file *p_file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	__poll_t ret = 0;
	पूर्णांक cnt;
	काष्ठा bcm_vk_ctx *ctx = p_file->निजी_data;
	काष्ठा bcm_vk *vk = container_of(ctx->miscdev, काष्ठा bcm_vk, miscdev);
	काष्ठा device *dev = &vk->pdev->dev;

	poll_रुको(p_file, &ctx->rd_wq, रुको);

	cnt = atomic_पढ़ो(&ctx->pend_cnt);
	अगर (cnt) अणु
		ret = (__क्रमce __poll_t)(POLLIN | POLLRDNORM);
		अगर (cnt < 0) अणु
			dev_err(dev, "Error cnt %d, setting back to 0", cnt);
			atomic_set(&ctx->pend_cnt, 0);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक bcm_vk_release(काष्ठा inode *inode, काष्ठा file *p_file)
अणु
	पूर्णांक ret;
	काष्ठा bcm_vk_ctx *ctx = p_file->निजी_data;
	काष्ठा bcm_vk *vk = container_of(ctx->miscdev, काष्ठा bcm_vk, miscdev);
	काष्ठा device *dev = &vk->pdev->dev;
	pid_t pid = ctx->pid;
	पूर्णांक dma_cnt;
	अचिन्हित दीर्घ समयout, start_समय;

	/*
	 * अगर there are outstanding DMA transactions, need to delay दीर्घ enough
	 * to ensure that the card side would have stopped touching the host buffer
	 * and its SGL list.  A race condition could happen अगर the host app is समाप्तed
	 * abruptly, eg समाप्त -9, जबतक some DMA transfer orders are still inflight.
	 * Nothing could be करोne except क्रम a delay as host side is running in a
	 * completely async fashion.
	 */
	start_समय = jअगरfies;
	समयout = start_समय + msecs_to_jअगरfies(BCM_VK_DMA_DRAIN_MAX_MS);
	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			dev_warn(dev, "%d dma still pending for [fd-%d] pid %d\n",
				 dma_cnt, ctx->idx, pid);
			अवरोध;
		पूर्ण
		dma_cnt = atomic_पढ़ो(&ctx->dma_cnt);
		cpu_relax();
		cond_resched();
	पूर्ण जबतक (dma_cnt);
	dev_dbg(dev, "Draining for [fd-%d] pid %d - delay %d ms\n",
		ctx->idx, pid, jअगरfies_to_msecs(jअगरfies - start_समय));

	bcm_vk_drain_all_pend(&vk->pdev->dev, &vk->to_v_msg_chan, ctx);
	bcm_vk_drain_all_pend(&vk->pdev->dev, &vk->to_h_msg_chan, ctx);

	ret = bcm_vk_मुक्त_ctx(vk, ctx);
	अगर (ret == 0)
		ret = bcm_vk_handle_last_sess(vk, pid, ctx->q_num);
	अन्यथा
		ret = 0;

	kref_put(&vk->kref, bcm_vk_release_data);

	वापस ret;
पूर्ण

पूर्णांक bcm_vk_msg_init(काष्ठा bcm_vk *vk)
अणु
	काष्ठा device *dev = &vk->pdev->dev;
	पूर्णांक ret;

	अगर (bcm_vk_data_init(vk)) अणु
		dev_err(dev, "Error initializing internal data structures\n");
		वापस -EINVAL;
	पूर्ण

	अगर (bcm_vk_msg_chan_init(&vk->to_v_msg_chan) ||
	    bcm_vk_msg_chan_init(&vk->to_h_msg_chan)) अणु
		dev_err(dev, "Error initializing communication channel\n");
		वापस -EIO;
	पूर्ण

	/* पढ़ो msgq info अगर पढ़ोy */
	ret = bcm_vk_sync_msgq(vk, false);
	अगर (ret && (ret != -EAGAIN)) अणु
		dev_err(dev, "Error reading comm msg Q info\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bcm_vk_msg_हटाओ(काष्ठा bcm_vk *vk)
अणु
	bcm_vk_blk_drv_access(vk);

	/* drain all pending items */
	bcm_vk_drain_all_pend(&vk->pdev->dev, &vk->to_v_msg_chan, शून्य);
	bcm_vk_drain_all_pend(&vk->pdev->dev, &vk->to_h_msg_chan, शून्य);
पूर्ण

