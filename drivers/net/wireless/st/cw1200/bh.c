<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Device handling thपढ़ो implementation क्रम mac80211 ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on:
 * ST-Ericsson UMAC CW1200 driver, which is
 * Copyright (c) 2010, ST-Ericsson
 * Author: Ajitpal Singh <ajitpal.singh@stericsson.com>
 */

#समावेश <linux/module.h>
#समावेश <net/mac80211.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/समयr.h>

#समावेश "cw1200.h"
#समावेश "bh.h"
#समावेश "hwio.h"
#समावेश "wsm.h"
#समावेश "hwbus.h"
#समावेश "debug.h"
#समावेश "fwio.h"

अटल पूर्णांक cw1200_bh(व्योम *arg);

#घोषणा DOWNLOAD_BLOCK_SIZE_WR	(0x1000 - 4)
/* an SPI message cannot be bigger than (2"12-1)*2 bytes
 * "*2" to cvt to bytes
 */
#घोषणा MAX_SZ_RD_WR_BUFFERS	(DOWNLOAD_BLOCK_SIZE_WR*2)
#घोषणा PIGGYBACK_CTRL_REG	(2)
#घोषणा EFFECTIVE_BUF_SIZE	(MAX_SZ_RD_WR_BUFFERS - PIGGYBACK_CTRL_REG)

/* Suspend state निजीs */
क्रमागत cw1200_bh_pm_state अणु
	CW1200_BH_RESUMED = 0,
	CW1200_BH_SUSPEND,
	CW1200_BH_SUSPENDED,
	CW1200_BH_RESUME,
पूर्ण;

अटल व्योम cw1200_bh_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cw1200_common *priv =
	container_of(work, काष्ठा cw1200_common, bh_work);
	cw1200_bh(priv);
पूर्ण

पूर्णांक cw1200_रेजिस्टर_bh(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक err = 0;
	/* Realसमय workqueue */
	priv->bh_workqueue = alloc_workqueue("cw1200_bh",
				WQ_MEM_RECLAIM | WQ_HIGHPRI
				| WQ_CPU_INTENSIVE, 1);

	अगर (!priv->bh_workqueue)
		वापस -ENOMEM;

	INIT_WORK(&priv->bh_work, cw1200_bh_work);

	pr_debug("[BH] register.\n");

	atomic_set(&priv->bh_rx, 0);
	atomic_set(&priv->bh_tx, 0);
	atomic_set(&priv->bh_term, 0);
	atomic_set(&priv->bh_suspend, CW1200_BH_RESUMED);
	priv->bh_error = 0;
	priv->hw_bufs_used = 0;
	priv->buf_id_tx = 0;
	priv->buf_id_rx = 0;
	init_रुकोqueue_head(&priv->bh_wq);
	init_रुकोqueue_head(&priv->bh_evt_wq);

	err = !queue_work(priv->bh_workqueue, &priv->bh_work);
	WARN_ON(err);
	वापस err;
पूर्ण

व्योम cw1200_unरेजिस्टर_bh(काष्ठा cw1200_common *priv)
अणु
	atomic_inc(&priv->bh_term);
	wake_up(&priv->bh_wq);

	flush_workqueue(priv->bh_workqueue);

	destroy_workqueue(priv->bh_workqueue);
	priv->bh_workqueue = शून्य;

	pr_debug("[BH] unregistered.\n");
पूर्ण

व्योम cw1200_irq_handler(काष्ठा cw1200_common *priv)
अणु
	pr_debug("[BH] irq.\n");

	/* Disable Interrupts! */
	/* NOTE:  hwbus_ops->lock alपढ़ोy held */
	__cw1200_irq_enable(priv, 0);

	अगर (/* WARN_ON */(priv->bh_error))
		वापस;

	अगर (atomic_inc_वापस(&priv->bh_rx) == 1)
		wake_up(&priv->bh_wq);
पूर्ण
EXPORT_SYMBOL_GPL(cw1200_irq_handler);

व्योम cw1200_bh_wakeup(काष्ठा cw1200_common *priv)
अणु
	pr_debug("[BH] wakeup.\n");
	अगर (priv->bh_error) अणु
		pr_err("[BH] wakeup failed (BH error)\n");
		वापस;
	पूर्ण

	अगर (atomic_inc_वापस(&priv->bh_tx) == 1)
		wake_up(&priv->bh_wq);
पूर्ण

पूर्णांक cw1200_bh_suspend(काष्ठा cw1200_common *priv)
अणु
	pr_debug("[BH] suspend.\n");
	अगर (priv->bh_error) अणु
		wiphy_warn(priv->hw->wiphy, "BH error -- can't suspend\n");
		वापस -EINVAL;
	पूर्ण

	atomic_set(&priv->bh_suspend, CW1200_BH_SUSPEND);
	wake_up(&priv->bh_wq);
	वापस रुको_event_समयout(priv->bh_evt_wq, priv->bh_error ||
		(CW1200_BH_SUSPENDED == atomic_पढ़ो(&priv->bh_suspend)),
		 1 * HZ) ? 0 : -ETIMEDOUT;
पूर्ण

पूर्णांक cw1200_bh_resume(काष्ठा cw1200_common *priv)
अणु
	pr_debug("[BH] resume.\n");
	अगर (priv->bh_error) अणु
		wiphy_warn(priv->hw->wiphy, "BH error -- can't resume\n");
		वापस -EINVAL;
	पूर्ण

	atomic_set(&priv->bh_suspend, CW1200_BH_RESUME);
	wake_up(&priv->bh_wq);
	वापस रुको_event_समयout(priv->bh_evt_wq, priv->bh_error ||
		(CW1200_BH_RESUMED == atomic_पढ़ो(&priv->bh_suspend)),
		1 * HZ) ? 0 : -ETIMEDOUT;
पूर्ण

अटल अंतरभूत व्योम wsm_alloc_tx_buffer(काष्ठा cw1200_common *priv)
अणु
	++priv->hw_bufs_used;
पूर्ण

पूर्णांक wsm_release_tx_buffer(काष्ठा cw1200_common *priv, पूर्णांक count)
अणु
	पूर्णांक ret = 0;
	पूर्णांक hw_bufs_used = priv->hw_bufs_used;

	priv->hw_bufs_used -= count;
	अगर (WARN_ON(priv->hw_bufs_used < 0))
		ret = -1;
	अन्यथा अगर (hw_bufs_used >= priv->wsm_caps.input_buffers)
		ret = 1;
	अगर (!priv->hw_bufs_used)
		wake_up(&priv->bh_evt_wq);
	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_bh_पढ़ो_ctrl_reg(काष्ठा cw1200_common *priv,
					  u16 *ctrl_reg)
अणु
	पूर्णांक ret;

	ret = cw1200_reg_पढ़ो_16(priv,
			ST90TDS_CONTROL_REG_ID, ctrl_reg);
	अगर (ret) अणु
		ret = cw1200_reg_पढ़ो_16(priv,
				ST90TDS_CONTROL_REG_ID, ctrl_reg);
		अगर (ret)
			pr_err("[BH] Failed to read control register.\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cw1200_device_wakeup(काष्ठा cw1200_common *priv)
अणु
	u16 ctrl_reg;
	पूर्णांक ret;

	pr_debug("[BH] Device wakeup.\n");

	/* First, set the dpll रेजिस्टर */
	ret = cw1200_reg_ग_लिखो_32(priv, ST90TDS_TSET_GEN_R_W_REG_ID,
				  cw1200_dpll_from_clk(priv->hw_refclk));
	अगर (WARN_ON(ret))
		वापस ret;

	/* To क्रमce the device to be always-on, the host sets WLAN_UP to 1 */
	ret = cw1200_reg_ग_लिखो_16(priv, ST90TDS_CONTROL_REG_ID,
			ST90TDS_CONT_WUP_BIT);
	अगर (WARN_ON(ret))
		वापस ret;

	ret = cw1200_bh_पढ़ो_ctrl_reg(priv, &ctrl_reg);
	अगर (WARN_ON(ret))
		वापस ret;

	/* If the device वापसs WLAN_RDY as 1, the device is active and will
	 * reमुख्य active.
	 */
	अगर (ctrl_reg & ST90TDS_CONT_RDY_BIT) अणु
		pr_debug("[BH] Device awake.\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Must be called from BH thraed. */
व्योम cw1200_enable_घातersave(काष्ठा cw1200_common *priv,
			     bool enable)
अणु
	pr_debug("[BH] Powerave is %s.\n",
		 enable ? "enabled" : "disabled");
	priv->घातersave_enabled = enable;
पूर्ण

अटल पूर्णांक cw1200_bh_rx_helper(काष्ठा cw1200_common *priv,
			       uपूर्णांक16_t *ctrl_reg,
			       पूर्णांक *tx)
अणु
	माप_प्रकार पढ़ो_len = 0;
	काष्ठा sk_buff *skb_rx = शून्य;
	काष्ठा wsm_hdr *wsm;
	माप_प्रकार wsm_len;
	u16 wsm_id;
	u8 wsm_seq;
	पूर्णांक rx_resync = 1;

	माप_प्रकार alloc_len;
	u8 *data;

	पढ़ो_len = (*ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK) * 2;
	अगर (!पढ़ो_len)
		वापस 0; /* No more work */

	अगर (WARN_ON((पढ़ो_len < माप(काष्ठा wsm_hdr)) ||
		    (पढ़ो_len > EFFECTIVE_BUF_SIZE))) अणु
		pr_debug("Invalid read len: %zu (%04x)",
			 पढ़ो_len, *ctrl_reg);
		जाओ err;
	पूर्ण

	/* Add SIZE of PIGGYBACK reg (CONTROL Reg)
	 * to the NEXT Message length + 2 Bytes क्रम SKB
	 */
	पढ़ो_len = पढ़ो_len + 2;

	alloc_len = priv->hwbus_ops->align_size(
		priv->hwbus_priv, पढ़ो_len);

	/* Check अगर not exceeding CW1200 capabilities */
	अगर (WARN_ON_ONCE(alloc_len > EFFECTIVE_BUF_SIZE)) अणु
		pr_debug("Read aligned len: %zu\n",
			 alloc_len);
	पूर्ण

	skb_rx = dev_alloc_skb(alloc_len);
	अगर (WARN_ON(!skb_rx))
		जाओ err;

	skb_trim(skb_rx, 0);
	skb_put(skb_rx, पढ़ो_len);
	data = skb_rx->data;
	अगर (WARN_ON(!data))
		जाओ err;

	अगर (WARN_ON(cw1200_data_पढ़ो(priv, data, alloc_len))) अणु
		pr_err("rx blew up, len %zu\n", alloc_len);
		जाओ err;
	पूर्ण

	/* Piggyback */
	*ctrl_reg = __le16_to_cpu(
		((__le16 *)data)[alloc_len / 2 - 1]);

	wsm = (काष्ठा wsm_hdr *)data;
	wsm_len = __le16_to_cpu(wsm->len);
	अगर (WARN_ON(wsm_len > पढ़ो_len))
		जाओ err;

	अगर (priv->wsm_enable_wsm_dumps)
		prपूर्णांक_hex_dump_bytes("<-- ",
				     DUMP_PREFIX_NONE,
				     data, wsm_len);

	wsm_id  = __le16_to_cpu(wsm->id) & 0xFFF;
	wsm_seq = (__le16_to_cpu(wsm->id) >> 13) & 7;

	skb_trim(skb_rx, wsm_len);

	अगर (wsm_id == 0x0800) अणु
		wsm_handle_exception(priv,
				     &data[माप(*wsm)],
				     wsm_len - माप(*wsm));
		जाओ err;
	पूर्ण अन्यथा अगर (!rx_resync) अणु
		अगर (WARN_ON(wsm_seq != priv->wsm_rx_seq))
			जाओ err;
	पूर्ण
	priv->wsm_rx_seq = (wsm_seq + 1) & 7;
	rx_resync = 0;

	अगर (wsm_id & 0x0400) अणु
		पूर्णांक rc = wsm_release_tx_buffer(priv, 1);
		अगर (WARN_ON(rc < 0))
			वापस rc;
		अन्यथा अगर (rc > 0)
			*tx = 1;
	पूर्ण

	/* cw1200_wsm_rx takes care on SKB liveसमय */
	अगर (WARN_ON(wsm_handle_rx(priv, wsm_id, wsm, &skb_rx)))
		जाओ err;

	अगर (skb_rx) अणु
		dev_kमुक्त_skb(skb_rx);
		skb_rx = शून्य;
	पूर्ण

	वापस 0;

err:
	अगर (skb_rx) अणु
		dev_kमुक्त_skb(skb_rx);
		skb_rx = शून्य;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक cw1200_bh_tx_helper(काष्ठा cw1200_common *priv,
			       पूर्णांक *pending_tx,
			       पूर्णांक *tx_burst)
अणु
	माप_प्रकार tx_len;
	u8 *data;
	पूर्णांक ret;
	काष्ठा wsm_hdr *wsm;

	अगर (priv->device_can_sleep) अणु
		ret = cw1200_device_wakeup(priv);
		अगर (WARN_ON(ret < 0)) अणु /* Error in wakeup */
			*pending_tx = 1;
			वापस 0;
		पूर्ण अन्यथा अगर (ret) अणु /* Woke up */
			priv->device_can_sleep = false;
		पूर्ण अन्यथा अणु /* Did not awake */
			*pending_tx = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	wsm_alloc_tx_buffer(priv);
	ret = wsm_get_tx(priv, &data, &tx_len, tx_burst);
	अगर (ret <= 0) अणु
		wsm_release_tx_buffer(priv, 1);
		अगर (WARN_ON(ret < 0))
			वापस ret; /* Error */
		वापस 0; /* No work */
	पूर्ण

	wsm = (काष्ठा wsm_hdr *)data;
	BUG_ON(tx_len < माप(*wsm));
	BUG_ON(__le16_to_cpu(wsm->len) != tx_len);

	atomic_inc(&priv->bh_tx);

	tx_len = priv->hwbus_ops->align_size(
		priv->hwbus_priv, tx_len);

	/* Check अगर not exceeding CW1200 capabilities */
	अगर (WARN_ON_ONCE(tx_len > EFFECTIVE_BUF_SIZE))
		pr_debug("Write aligned len: %zu\n", tx_len);

	wsm->id &= __cpu_to_le16(0xffff ^ WSM_TX_SEQ(WSM_TX_SEQ_MAX));
	wsm->id |= __cpu_to_le16(WSM_TX_SEQ(priv->wsm_tx_seq));

	अगर (WARN_ON(cw1200_data_ग_लिखो(priv, data, tx_len))) अणु
		pr_err("tx blew up, len %zu\n", tx_len);
		wsm_release_tx_buffer(priv, 1);
		वापस -1; /* Error */
	पूर्ण

	अगर (priv->wsm_enable_wsm_dumps)
		prपूर्णांक_hex_dump_bytes("--> ",
				     DUMP_PREFIX_NONE,
				     data,
				     __le16_to_cpu(wsm->len));

	wsm_txed(priv, data);
	priv->wsm_tx_seq = (priv->wsm_tx_seq + 1) & WSM_TX_SEQ_MAX;

	अगर (*tx_burst > 1) अणु
		cw1200_debug_tx_burst(priv);
		वापस 1; /* Work reमुख्यs */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cw1200_bh(व्योम *arg)
अणु
	काष्ठा cw1200_common *priv = arg;
	पूर्णांक rx, tx, term, suspend;
	u16 ctrl_reg = 0;
	पूर्णांक tx_allowed;
	पूर्णांक pending_tx = 0;
	पूर्णांक tx_burst;
	दीर्घ status;
	u32 dummy;
	पूर्णांक ret;

	क्रम (;;) अणु
		अगर (!priv->hw_bufs_used &&
		    priv->घातersave_enabled &&
		    !priv->device_can_sleep &&
		    !atomic_पढ़ो(&priv->recent_scan)) अणु
			status = 1 * HZ;
			pr_debug("[BH] Device wakedown. No data.\n");
			cw1200_reg_ग_लिखो_16(priv, ST90TDS_CONTROL_REG_ID, 0);
			priv->device_can_sleep = true;
		पूर्ण अन्यथा अगर (priv->hw_bufs_used) अणु
			/* Interrupt loss detection */
			status = 1 * HZ;
		पूर्ण अन्यथा अणु
			status = MAX_SCHEDULE_TIMEOUT;
		पूर्ण

		/* Dummy Read क्रम SDIO retry mechanism*/
		अगर ((priv->hw_type != -1) &&
		    (atomic_पढ़ो(&priv->bh_rx) == 0) &&
		    (atomic_पढ़ो(&priv->bh_tx) == 0))
			cw1200_reg_पढ़ो(priv, ST90TDS_CONFIG_REG_ID,
					&dummy, माप(dummy));

		pr_debug("[BH] waiting ...\n");
		status = रुको_event_पूर्णांकerruptible_समयout(priv->bh_wq, (अणु
				rx = atomic_xchg(&priv->bh_rx, 0);
				tx = atomic_xchg(&priv->bh_tx, 0);
				term = atomic_xchg(&priv->bh_term, 0);
				suspend = pending_tx ?
					0 : atomic_पढ़ो(&priv->bh_suspend);
				(rx || tx || term || suspend || priv->bh_error);
			पूर्ण), status);

		pr_debug("[BH] - rx: %d, tx: %d, term: %d, bh_err: %d, suspend: %d, status: %ld\n",
			 rx, tx, term, suspend, priv->bh_error, status);

		/* Did an error occur? */
		अगर ((status < 0 && status != -ERESTARTSYS) ||
		    term || priv->bh_error) अणु
			अवरोध;
		पूर्ण
		अगर (!status) अणु  /* रुको_event समयd out */
			अचिन्हित दीर्घ बारtamp = jअगरfies;
			दीर्घ समयout;
			पूर्णांक pending = 0;
			पूर्णांक i;

			/* Check to see अगर we have any outstanding frames */
			अगर (priv->hw_bufs_used && (!rx || !tx)) अणु
				wiphy_warn(priv->hw->wiphy,
					   "Missed interrupt? (%d frames outstanding)\n",
					   priv->hw_bufs_used);
				rx = 1;

				/* Get a बारtamp of "oldest" frame */
				क्रम (i = 0; i < 4; ++i)
					pending += cw1200_queue_get_xmit_बारtamp(
						&priv->tx_queue[i],
						&बारtamp,
						priv->pending_frame_id);

				/* Check अगर frame transmission is समयd out.
				 * Add an extra second with respect to possible
				 * पूर्णांकerrupt loss.
				 */
				समयout = बारtamp +
					WSM_CMD_LAST_CHANCE_TIMEOUT +
					1 * HZ  -
					jअगरfies;

				/* And terminate BH thपढ़ो अगर the frame is "stuck" */
				अगर (pending && समयout < 0) अणु
					wiphy_warn(priv->hw->wiphy,
						   "Timeout waiting for TX confirm (%d/%d pending, %ld vs %lu).\n",
						   priv->hw_bufs_used, pending,
						   बारtamp, jअगरfies);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (!priv->device_can_sleep &&
				   !atomic_पढ़ो(&priv->recent_scan)) अणु
				pr_debug("[BH] Device wakedown. Timeout.\n");
				cw1200_reg_ग_लिखो_16(priv,
						    ST90TDS_CONTROL_REG_ID, 0);
				priv->device_can_sleep = true;
			पूर्ण
			जाओ करोne;
		पूर्ण अन्यथा अगर (suspend) अणु
			pr_debug("[BH] Device suspend.\n");
			अगर (priv->घातersave_enabled) अणु
				pr_debug("[BH] Device wakedown. Suspend.\n");
				cw1200_reg_ग_लिखो_16(priv,
						    ST90TDS_CONTROL_REG_ID, 0);
				priv->device_can_sleep = true;
			पूर्ण

			atomic_set(&priv->bh_suspend, CW1200_BH_SUSPENDED);
			wake_up(&priv->bh_evt_wq);
			status = रुको_event_पूर्णांकerruptible(priv->bh_wq,
							  CW1200_BH_RESUME == atomic_पढ़ो(&priv->bh_suspend));
			अगर (status < 0) अणु
				wiphy_err(priv->hw->wiphy,
					  "Failed to wait for resume: %ld.\n",
					  status);
				अवरोध;
			पूर्ण
			pr_debug("[BH] Device resume.\n");
			atomic_set(&priv->bh_suspend, CW1200_BH_RESUMED);
			wake_up(&priv->bh_evt_wq);
			atomic_inc(&priv->bh_rx);
			जाओ करोne;
		पूर्ण

	rx:
		tx += pending_tx;
		pending_tx = 0;

		अगर (cw1200_bh_पढ़ो_ctrl_reg(priv, &ctrl_reg))
			अवरोध;

		/* Don't bother trying to rx unless we have data to पढ़ो */
		अगर (ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK) अणु
			ret = cw1200_bh_rx_helper(priv, &ctrl_reg, &tx);
			अगर (ret < 0)
				अवरोध;
			/* Double up here अगर there's more data.. */
			अगर (ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK) अणु
				ret = cw1200_bh_rx_helper(priv, &ctrl_reg, &tx);
				अगर (ret < 0)
					अवरोध;
			पूर्ण
		पूर्ण

	tx:
		अगर (tx) अणु
			tx = 0;

			BUG_ON(priv->hw_bufs_used > priv->wsm_caps.input_buffers);
			tx_burst = priv->wsm_caps.input_buffers - priv->hw_bufs_used;
			tx_allowed = tx_burst > 0;

			अगर (!tx_allowed) अणु
				/* Buffers full.  Ensure we process tx
				 * after we handle rx..
				 */
				pending_tx = tx;
				जाओ करोne_rx;
			पूर्ण
			ret = cw1200_bh_tx_helper(priv, &pending_tx, &tx_burst);
			अगर (ret < 0)
				अवरोध;
			अगर (ret > 0) /* More to transmit */
				tx = ret;

			/* Re-पढ़ो ctrl reg */
			अगर (cw1200_bh_पढ़ो_ctrl_reg(priv, &ctrl_reg))
				अवरोध;
		पूर्ण

	करोne_rx:
		अगर (priv->bh_error)
			अवरोध;
		अगर (ctrl_reg & ST90TDS_CONT_NEXT_LEN_MASK)
			जाओ rx;
		अगर (tx)
			जाओ tx;

	करोne:
		/* Re-enable device पूर्णांकerrupts */
		priv->hwbus_ops->lock(priv->hwbus_priv);
		__cw1200_irq_enable(priv, 1);
		priv->hwbus_ops->unlock(priv->hwbus_priv);
	पूर्ण

	/* Explicitly disable device पूर्णांकerrupts */
	priv->hwbus_ops->lock(priv->hwbus_priv);
	__cw1200_irq_enable(priv, 0);
	priv->hwbus_ops->unlock(priv->hwbus_priv);

	अगर (!term) अणु
		pr_err("[BH] Fatal error, exiting.\n");
		priv->bh_error = 1;
		/* TODO: schedule_work(recovery) */
	पूर्ण
	वापस 0;
पूर्ण
