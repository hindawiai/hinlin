<शैली गुरु>
/*
 * Copyright (c) 2007-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#समावेश "hif.h"

#समावेश <linux/export.h>

#समावेश "core.h"
#समावेश "target.h"
#समावेश "hif-ops.h"
#समावेश "debug.h"
#समावेश "trace.h"

#घोषणा MAILBOX_FOR_BLOCK_SIZE          1

#घोषणा ATH6KL_TIME_QUANTUM	10  /* in ms */

अटल पूर्णांक ath6kl_hअगर_cp_scat_dma_buf(काष्ठा hअगर_scatter_req *req,
				      bool from_dma)
अणु
	u8 *buf;
	पूर्णांक i;

	buf = req->virt_dma_buf;

	क्रम (i = 0; i < req->scat_entries; i++) अणु
		अगर (from_dma)
			स_नकल(req->scat_list[i].buf, buf,
			       req->scat_list[i].len);
		अन्यथा
			स_नकल(buf, req->scat_list[i].buf,
			       req->scat_list[i].len);

		buf += req->scat_list[i].len;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath6kl_hअगर_rw_comp_handler(व्योम *context, पूर्णांक status)
अणु
	काष्ठा htc_packet *packet = context;

	ath6kl_dbg(ATH6KL_DBG_HIF, "hif rw completion pkt 0x%p status %d\n",
		   packet, status);

	packet->status = status;
	packet->completion(packet->context, packet);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath6kl_hअगर_rw_comp_handler);

#घोषणा REGISTER_DUMP_COUNT     60
#घोषणा REGISTER_DUMP_LEN_MAX   60

अटल व्योम ath6kl_hअगर_dump_fw_crash(काष्ठा ath6kl *ar)
अणु
	__le32 regdump_val[REGISTER_DUMP_LEN_MAX];
	u32 i, address, regdump_addr = 0;
	पूर्णांक ret;

	/* the reg dump poपूर्णांकer is copied to the host पूर्णांकerest area */
	address = ath6kl_get_hi_item_addr(ar, HI_ITEM(hi_failure_state));
	address = TARG_VTOP(ar->target_type, address);

	/* पढ़ो RAM location through diagnostic winकरोw */
	ret = ath6kl_diag_पढ़ो32(ar, address, &regdump_addr);

	अगर (ret || !regdump_addr) अणु
		ath6kl_warn("failed to get ptr to register dump area: %d\n",
			    ret);
		वापस;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_IRQ, "register dump data address 0x%x\n",
		   regdump_addr);
	regdump_addr = TARG_VTOP(ar->target_type, regdump_addr);

	/* fetch रेजिस्टर dump data */
	ret = ath6kl_diag_पढ़ो(ar, regdump_addr, (u8 *)&regdump_val[0],
				  REGISTER_DUMP_COUNT * (माप(u32)));
	अगर (ret) अणु
		ath6kl_warn("failed to get register dump: %d\n", ret);
		वापस;
	पूर्ण

	ath6kl_info("crash dump:\n");
	ath6kl_info("hw 0x%x fw %s\n", ar->wiphy->hw_version,
		    ar->wiphy->fw_version);

	BUILD_BUG_ON(REGISTER_DUMP_COUNT % 4);

	क्रम (i = 0; i < REGISTER_DUMP_COUNT; i += 4) अणु
		ath6kl_info("%d: 0x%8.8x 0x%8.8x 0x%8.8x 0x%8.8x\n",
			    i,
			    le32_to_cpu(regdump_val[i]),
			    le32_to_cpu(regdump_val[i + 1]),
			    le32_to_cpu(regdump_val[i + 2]),
			    le32_to_cpu(regdump_val[i + 3]));
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_hअगर_proc_dbg_पूर्णांकr(काष्ठा ath6kl_device *dev)
अणु
	u32 dummy;
	पूर्णांक ret;

	ath6kl_warn("firmware crashed\n");

	/*
	 * पढ़ो counter to clear the पूर्णांकerrupt, the debug error पूर्णांकerrupt is
	 * counter 0.
	 */
	ret = hअगर_पढ़ो_ग_लिखो_sync(dev->ar, COUNT_DEC_ADDRESS,
				     (u8 *)&dummy, 4, HIF_RD_SYNC_BYTE_INC);
	अगर (ret)
		ath6kl_warn("Failed to clear debug interrupt: %d\n", ret);

	ath6kl_hअगर_dump_fw_crash(dev->ar);
	ath6kl_पढ़ो_fwlogs(dev->ar);
	ath6kl_recovery_err_notअगरy(dev->ar, ATH6KL_FW_ASSERT);

	वापस ret;
पूर्ण

/* mailbox recv message polling */
पूर्णांक ath6kl_hअगर_poll_mboxmsg_rx(काष्ठा ath6kl_device *dev, u32 *lk_ahd,
			      पूर्णांक समयout)
अणु
	काष्ठा ath6kl_irq_proc_रेजिस्टरs *rg;
	पूर्णांक status = 0, i;
	u8 htc_mbox = 1 << HTC_MAILBOX;

	क्रम (i = समयout / ATH6KL_TIME_QUANTUM; i > 0; i--) अणु
		/* this is the standard HIF way, load the reg table */
		status = hअगर_पढ़ो_ग_लिखो_sync(dev->ar, HOST_INT_STATUS_ADDRESS,
					     (u8 *) &dev->irq_proc_reg,
					     माप(dev->irq_proc_reg),
					     HIF_RD_SYNC_BYTE_INC);

		अगर (status) अणु
			ath6kl_err("failed to read reg table\n");
			वापस status;
		पूर्ण

		/* check क्रम MBOX data and valid lookahead */
		अगर (dev->irq_proc_reg.host_पूर्णांक_status & htc_mbox) अणु
			अगर (dev->irq_proc_reg.rx_lkahd_valid &
			    htc_mbox) अणु
				/*
				 * Mailbox has a message and the look ahead
				 * is valid.
				 */
				rg = &dev->irq_proc_reg;
				*lk_ahd =
					le32_to_cpu(rg->rx_lkahd[HTC_MAILBOX]);
				अवरोध;
			पूर्ण
		पूर्ण

		/* delay a little  */
		mdelay(ATH6KL_TIME_QUANTUM);
		ath6kl_dbg(ATH6KL_DBG_HIF, "hif retry mbox poll try %d\n", i);
	पूर्ण

	अगर (i == 0) अणु
		ath6kl_err("timeout waiting for recv message\n");
		status = -ETIME;
		/* check अगर the target निश्चितed */
		अगर (dev->irq_proc_reg.counter_पूर्णांक_status &
		    ATH6KL_TARGET_DEBUG_INTR_MASK)
			/*
			 * Target failure handler will be called in हाल of
			 * an निश्चित.
			 */
			ath6kl_hअगर_proc_dbg_पूर्णांकr(dev);
	पूर्ण

	वापस status;
पूर्ण

/*
 * Disable packet reception (used in हाल the host runs out of buffers)
 * using the पूर्णांकerrupt enable रेजिस्टरs through the host I/F
 */
पूर्णांक ath6kl_hअगर_rx_control(काष्ठा ath6kl_device *dev, bool enable_rx)
अणु
	काष्ठा ath6kl_irq_enable_reg regs;
	पूर्णांक status = 0;

	ath6kl_dbg(ATH6KL_DBG_HIF, "hif rx %s\n",
		   enable_rx ? "enable" : "disable");

	/* take the lock to protect पूर्णांकerrupt enable shaकरोws */
	spin_lock_bh(&dev->lock);

	अगर (enable_rx)
		dev->irq_en_reg.पूर्णांक_status_en |=
			SM(INT_STATUS_ENABLE_MBOX_DATA, 0x01);
	अन्यथा
		dev->irq_en_reg.पूर्णांक_status_en &=
		    ~SM(INT_STATUS_ENABLE_MBOX_DATA, 0x01);

	स_नकल(&regs, &dev->irq_en_reg, माप(regs));

	spin_unlock_bh(&dev->lock);

	status = hअगर_पढ़ो_ग_लिखो_sync(dev->ar, INT_STATUS_ENABLE_ADDRESS,
				     &regs.पूर्णांक_status_en,
				     माप(काष्ठा ath6kl_irq_enable_reg),
				     HIF_WR_SYNC_BYTE_INC);

	वापस status;
पूर्ण

पूर्णांक ath6kl_hअगर_submit_scat_req(काष्ठा ath6kl_device *dev,
			      काष्ठा hअगर_scatter_req *scat_req, bool पढ़ो)
अणु
	पूर्णांक status = 0;

	अगर (पढ़ो) अणु
		scat_req->req = HIF_RD_SYNC_BLOCK_FIX;
		scat_req->addr = dev->ar->mbox_info.htc_addr;
	पूर्ण अन्यथा अणु
		scat_req->req = HIF_WR_ASYNC_BLOCK_INC;

		scat_req->addr =
			(scat_req->len > HIF_MBOX_WIDTH) ?
			dev->ar->mbox_info.htc_ext_addr :
			dev->ar->mbox_info.htc_addr;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_HIF,
		   "hif submit scatter request entries %d len %d mbox 0x%x %s %s\n",
		   scat_req->scat_entries, scat_req->len,
		   scat_req->addr, !पढ़ो ? "async" : "sync",
		   (पढ़ो) ? "rd" : "wr");

	अगर (!पढ़ो && scat_req->virt_scat) अणु
		status = ath6kl_hअगर_cp_scat_dma_buf(scat_req, false);
		अगर (status) अणु
			scat_req->status = status;
			scat_req->complete(dev->ar->htc_target, scat_req);
			वापस 0;
		पूर्ण
	पूर्ण

	status = ath6kl_hअगर_scat_req_rw(dev->ar, scat_req);

	अगर (पढ़ो) अणु
		/* in sync mode, we can touch the scatter request */
		scat_req->status = status;
		अगर (!status && scat_req->virt_scat)
			scat_req->status =
				ath6kl_hअगर_cp_scat_dma_buf(scat_req, true);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_hअगर_proc_counter_पूर्णांकr(काष्ठा ath6kl_device *dev)
अणु
	u8 counter_पूर्णांक_status;

	ath6kl_dbg(ATH6KL_DBG_IRQ, "counter interrupt\n");

	counter_पूर्णांक_status = dev->irq_proc_reg.counter_पूर्णांक_status &
			     dev->irq_en_reg.cntr_पूर्णांक_status_en;

	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "valid interrupt source(s) in COUNTER_INT_STATUS: 0x%x\n",
		counter_पूर्णांक_status);

	/*
	 * NOTE: other modules like GMBOX may use the counter पूर्णांकerrupt क्रम
	 * credit flow control on other counters, we only need to check क्रम
	 * the debug निश्चितion counter पूर्णांकerrupt.
	 */
	अगर (counter_पूर्णांक_status & ATH6KL_TARGET_DEBUG_INTR_MASK)
		वापस ath6kl_hअगर_proc_dbg_पूर्णांकr(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_hअगर_proc_err_पूर्णांकr(काष्ठा ath6kl_device *dev)
अणु
	पूर्णांक status;
	u8 error_पूर्णांक_status;
	u8 reg_buf[4];

	ath6kl_dbg(ATH6KL_DBG_IRQ, "error interrupt\n");

	error_पूर्णांक_status = dev->irq_proc_reg.error_पूर्णांक_status & 0x0F;
	अगर (!error_पूर्णांक_status) अणु
		WARN_ON(1);
		वापस -EIO;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "valid interrupt source(s) in ERROR_INT_STATUS: 0x%x\n",
		   error_पूर्णांक_status);

	अगर (MS(ERROR_INT_STATUS_WAKEUP, error_पूर्णांक_status))
		ath6kl_dbg(ATH6KL_DBG_IRQ, "error : wakeup\n");

	अगर (MS(ERROR_INT_STATUS_RX_UNDERFLOW, error_पूर्णांक_status))
		ath6kl_err("rx underflow\n");

	अगर (MS(ERROR_INT_STATUS_TX_OVERFLOW, error_पूर्णांक_status))
		ath6kl_err("tx overflow\n");

	/* Clear the पूर्णांकerrupt */
	dev->irq_proc_reg.error_पूर्णांक_status &= ~error_पूर्णांक_status;

	/* set W1C value to clear the पूर्णांकerrupt, this hits the रेजिस्टर first */
	reg_buf[0] = error_पूर्णांक_status;
	reg_buf[1] = 0;
	reg_buf[2] = 0;
	reg_buf[3] = 0;

	status = hअगर_पढ़ो_ग_लिखो_sync(dev->ar, ERROR_INT_STATUS_ADDRESS,
				     reg_buf, 4, HIF_WR_SYNC_BYTE_FIX);

	WARN_ON(status);

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_hअगर_proc_cpu_पूर्णांकr(काष्ठा ath6kl_device *dev)
अणु
	पूर्णांक status;
	u8 cpu_पूर्णांक_status;
	u8 reg_buf[4];

	ath6kl_dbg(ATH6KL_DBG_IRQ, "cpu interrupt\n");

	cpu_पूर्णांक_status = dev->irq_proc_reg.cpu_पूर्णांक_status &
			 dev->irq_en_reg.cpu_पूर्णांक_status_en;
	अगर (!cpu_पूर्णांक_status) अणु
		WARN_ON(1);
		वापस -EIO;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "valid interrupt source(s) in CPU_INT_STATUS: 0x%x\n",
		cpu_पूर्णांक_status);

	/* Clear the पूर्णांकerrupt */
	dev->irq_proc_reg.cpu_पूर्णांक_status &= ~cpu_पूर्णांक_status;

	/*
	 * Set up the रेजिस्टर transfer buffer to hit the रेजिस्टर 4 बार ,
	 * this is करोne to make the access 4-byte aligned to mitigate issues
	 * with host bus पूर्णांकerconnects that restrict bus transfer lengths to
	 * be a multiple of 4-bytes.
	 */

	/* set W1C value to clear the पूर्णांकerrupt, this hits the रेजिस्टर first */
	reg_buf[0] = cpu_पूर्णांक_status;
	/* the reमुख्यing are set to zero which have no-effect  */
	reg_buf[1] = 0;
	reg_buf[2] = 0;
	reg_buf[3] = 0;

	status = hअगर_पढ़ो_ग_लिखो_sync(dev->ar, CPU_INT_STATUS_ADDRESS,
				     reg_buf, 4, HIF_WR_SYNC_BYTE_FIX);

	WARN_ON(status);

	वापस status;
पूर्ण

/* process pending पूर्णांकerrupts synchronously */
अटल पूर्णांक proc_pending_irqs(काष्ठा ath6kl_device *dev, bool *करोne)
अणु
	काष्ठा ath6kl_irq_proc_रेजिस्टरs *rg;
	पूर्णांक status = 0;
	u8 host_पूर्णांक_status = 0;
	u32 lk_ahd = 0;
	u8 htc_mbox = 1 << HTC_MAILBOX;

	ath6kl_dbg(ATH6KL_DBG_IRQ, "proc_pending_irqs: (dev: 0x%p)\n", dev);

	/*
	 * NOTE: HIF implementation guarantees that the context of this
	 * call allows us to perक्रमm SYNCHRONOUS I/O, that is we can block,
	 * sleep or call any API that can block or चयन thपढ़ो/task
	 * contexts. This is a fully schedulable context.
	 */

	/*
	 * Process pending पूर्णांकr only when पूर्णांक_status_en is clear, it may
	 * result in unnecessary bus transaction otherwise. Target may be
	 * unresponsive at the समय.
	 */
	अगर (dev->irq_en_reg.पूर्णांक_status_en) अणु
		/*
		 * Read the first 28 bytes of the HTC रेजिस्टर table. This
		 * will yield us the value of dअगरferent पूर्णांक status
		 * रेजिस्टरs and the lookahead रेजिस्टरs.
		 *
		 *    length = माप(पूर्णांक_status) + माप(cpu_पूर्णांक_status)
		 *             + माप(error_पूर्णांक_status) +
		 *             माप(counter_पूर्णांक_status) +
		 *             माप(mbox_frame) + माप(rx_lkahd_valid)
		 *             + माप(hole) + माप(rx_lkahd) +
		 *             माप(पूर्णांक_status_en) +
		 *             माप(cpu_पूर्णांक_status_en) +
		 *             माप(err_पूर्णांक_status_en) +
		 *             माप(cntr_पूर्णांक_status_en);
		 */
		status = hअगर_पढ़ो_ग_लिखो_sync(dev->ar, HOST_INT_STATUS_ADDRESS,
					     (u8 *) &dev->irq_proc_reg,
					     माप(dev->irq_proc_reg),
					     HIF_RD_SYNC_BYTE_INC);
		अगर (status)
			जाओ out;

		ath6kl_dump_रेजिस्टरs(dev, &dev->irq_proc_reg,
				      &dev->irq_en_reg);
		trace_ath6kl_sdio_irq(&dev->irq_en_reg,
				      माप(dev->irq_en_reg));

		/* Update only those रेजिस्टरs that are enabled */
		host_पूर्णांक_status = dev->irq_proc_reg.host_पूर्णांक_status &
				  dev->irq_en_reg.पूर्णांक_status_en;

		/* Look at mbox status */
		अगर (host_पूर्णांक_status & htc_mbox) अणु
			/*
			 * Mask out pending mbox value, we use "lookAhead as
			 * the real flag क्रम mbox processing.
			 */
			host_पूर्णांक_status &= ~htc_mbox;
			अगर (dev->irq_proc_reg.rx_lkahd_valid &
			    htc_mbox) अणु
				rg = &dev->irq_proc_reg;
				lk_ahd = le32_to_cpu(rg->rx_lkahd[HTC_MAILBOX]);
				अगर (!lk_ahd)
					ath6kl_err("lookAhead is zero!\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!host_पूर्णांक_status && !lk_ahd) अणु
		*करोne = true;
		जाओ out;
	पूर्ण

	अगर (lk_ahd) अणु
		पूर्णांक fetched = 0;

		ath6kl_dbg(ATH6KL_DBG_IRQ,
			   "pending mailbox msg, lk_ahd: 0x%X\n", lk_ahd);
		/*
		 * Mailbox Interrupt, the HTC layer may issue async
		 * requests to empty the mailbox. When emptying the recv
		 * mailbox we use the async handler above called from the
		 * completion routine of the callers पढ़ो request. This can
		 * improve perक्रमmance by reducing context चयनing when
		 * we rapidly pull packets.
		 */
		status = ath6kl_htc_rxmsg_pending_handler(dev->htc_cnxt,
							  lk_ahd, &fetched);
		अगर (status)
			जाओ out;

		अगर (!fetched)
			/*
			 * HTC could not pull any messages out due to lack
			 * of resources.
			 */
			dev->htc_cnxt->chk_irq_status_cnt = 0;
	पूर्ण

	/* now handle the rest of them */
	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "valid interrupt source(s) for other interrupts: 0x%x\n",
		   host_पूर्णांक_status);

	अगर (MS(HOST_INT_STATUS_CPU, host_पूर्णांक_status)) अणु
		/* CPU Interrupt */
		status = ath6kl_hअगर_proc_cpu_पूर्णांकr(dev);
		अगर (status)
			जाओ out;
	पूर्ण

	अगर (MS(HOST_INT_STATUS_ERROR, host_पूर्णांक_status)) अणु
		/* Error Interrupt */
		status = ath6kl_hअगर_proc_err_पूर्णांकr(dev);
		अगर (status)
			जाओ out;
	पूर्ण

	अगर (MS(HOST_INT_STATUS_COUNTER, host_पूर्णांक_status))
		/* Counter Interrupt */
		status = ath6kl_hअगर_proc_counter_पूर्णांकr(dev);

out:
	/*
	 * An optimization to bypass पढ़ोing the IRQ status रेजिस्टरs
	 * unecessarily which can re-wake the target, अगर upper layers
	 * determine that we are in a low-throughput mode, we can rely on
	 * taking another पूर्णांकerrupt rather than re-checking the status
	 * रेजिस्टरs which can re-wake the target.
	 *
	 * NOTE : क्रम host पूर्णांकerfaces that makes use of detecting pending
	 * mbox messages at hअगर can not use this optimization due to
	 * possible side effects, SPI requires the host to drain all
	 * messages from the mailbox beक्रमe निकासing the ISR routine.
	 */

	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "bypassing irq status re-check, forcing done\n");

	अगर (!dev->htc_cnxt->chk_irq_status_cnt)
		*करोne = true;

	ath6kl_dbg(ATH6KL_DBG_IRQ,
		   "proc_pending_irqs: (done:%d, status=%d\n", *करोne, status);

	वापस status;
पूर्ण

/* पूर्णांकerrupt handler, kicks off all पूर्णांकerrupt processing */
पूर्णांक ath6kl_hअगर_पूर्णांकr_bh_handler(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_device *dev = ar->htc_target->dev;
	अचिन्हित दीर्घ समयout;
	पूर्णांक status = 0;
	bool करोne = false;

	/*
	 * Reset counter used to flag a re-scan of IRQ status रेजिस्टरs on
	 * the target.
	 */
	dev->htc_cnxt->chk_irq_status_cnt = 0;

	/*
	 * IRQ processing is synchronous, पूर्णांकerrupt status रेजिस्टरs can be
	 * re-पढ़ो.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(ATH6KL_HIF_COMMUNICATION_TIMEOUT);
	जबतक (समय_beक्रमe(jअगरfies, समयout) && !करोne) अणु
		status = proc_pending_irqs(dev, &करोne);
		अगर (status)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL(ath6kl_hअगर_पूर्णांकr_bh_handler);

अटल पूर्णांक ath6kl_hअगर_enable_पूर्णांकrs(काष्ठा ath6kl_device *dev)
अणु
	काष्ठा ath6kl_irq_enable_reg regs;
	पूर्णांक status;

	spin_lock_bh(&dev->lock);

	/* Enable all but ATH6KL CPU पूर्णांकerrupts */
	dev->irq_en_reg.पूर्णांक_status_en =
			SM(INT_STATUS_ENABLE_ERROR, 0x01) |
			SM(INT_STATUS_ENABLE_CPU, 0x01) |
			SM(INT_STATUS_ENABLE_COUNTER, 0x01);

	/*
	 * NOTE: There are some हालs where HIF can करो detection of
	 * pending mbox messages which is disabled now.
	 */
	dev->irq_en_reg.पूर्णांक_status_en |= SM(INT_STATUS_ENABLE_MBOX_DATA, 0x01);

	/* Set up the CPU Interrupt status Register */
	dev->irq_en_reg.cpu_पूर्णांक_status_en = 0;

	/* Set up the Error Interrupt status Register */
	dev->irq_en_reg.err_पूर्णांक_status_en =
		SM(ERROR_STATUS_ENABLE_RX_UNDERFLOW, 0x01) |
		SM(ERROR_STATUS_ENABLE_TX_OVERFLOW, 0x1);

	/*
	 * Enable Counter पूर्णांकerrupt status रेजिस्टर to get fatal errors क्रम
	 * debugging.
	 */
	dev->irq_en_reg.cntr_पूर्णांक_status_en = SM(COUNTER_INT_STATUS_ENABLE_BIT,
						ATH6KL_TARGET_DEBUG_INTR_MASK);
	स_नकल(&regs, &dev->irq_en_reg, माप(regs));

	spin_unlock_bh(&dev->lock);

	status = hअगर_पढ़ो_ग_लिखो_sync(dev->ar, INT_STATUS_ENABLE_ADDRESS,
				     &regs.पूर्णांक_status_en, माप(regs),
				     HIF_WR_SYNC_BYTE_INC);

	अगर (status)
		ath6kl_err("failed to update interrupt ctl reg err: %d\n",
			   status);

	वापस status;
पूर्ण

पूर्णांक ath6kl_hअगर_disable_पूर्णांकrs(काष्ठा ath6kl_device *dev)
अणु
	काष्ठा ath6kl_irq_enable_reg regs;

	spin_lock_bh(&dev->lock);
	/* Disable all पूर्णांकerrupts */
	dev->irq_en_reg.पूर्णांक_status_en = 0;
	dev->irq_en_reg.cpu_पूर्णांक_status_en = 0;
	dev->irq_en_reg.err_पूर्णांक_status_en = 0;
	dev->irq_en_reg.cntr_पूर्णांक_status_en = 0;
	स_नकल(&regs, &dev->irq_en_reg, माप(regs));
	spin_unlock_bh(&dev->lock);

	वापस hअगर_पढ़ो_ग_लिखो_sync(dev->ar, INT_STATUS_ENABLE_ADDRESS,
				   &regs.पूर्णांक_status_en, माप(regs),
				   HIF_WR_SYNC_BYTE_INC);
पूर्ण

/* enable device पूर्णांकerrupts */
पूर्णांक ath6kl_hअगर_unmask_पूर्णांकrs(काष्ठा ath6kl_device *dev)
अणु
	पूर्णांक status = 0;

	/*
	 * Make sure पूर्णांकerrupt are disabled beक्रमe unmasking at the HIF
	 * layer. The rationale here is that between device insertion
	 * (where we clear the पूर्णांकerrupts the first समय) and when HTC
	 * is finally पढ़ोy to handle पूर्णांकerrupts, other software can perक्रमm
	 * target "soft" resets. The ATH6KL पूर्णांकerrupt enables reset back to an
	 * "enabled" state when this happens.
	 */
	ath6kl_hअगर_disable_पूर्णांकrs(dev);

	/* unmask the host controller पूर्णांकerrupts */
	ath6kl_hअगर_irq_enable(dev->ar);
	status = ath6kl_hअगर_enable_पूर्णांकrs(dev);

	वापस status;
पूर्ण

/* disable all device पूर्णांकerrupts */
पूर्णांक ath6kl_hअगर_mask_पूर्णांकrs(काष्ठा ath6kl_device *dev)
अणु
	/*
	 * Mask the पूर्णांकerrupt at the HIF layer to aव्योम any stray पूर्णांकerrupt
	 * taken जबतक we zero out our shaकरोw रेजिस्टरs in
	 * ath6kl_hअगर_disable_पूर्णांकrs().
	 */
	ath6kl_hअगर_irq_disable(dev->ar);

	वापस ath6kl_hअगर_disable_पूर्णांकrs(dev);
पूर्ण

पूर्णांक ath6kl_hअगर_setup(काष्ठा ath6kl_device *dev)
अणु
	पूर्णांक status = 0;

	spin_lock_init(&dev->lock);

	/*
	 * NOTE: we actually get the block size of a mailbox other than 0,
	 * क्रम SDIO the block size on mailbox 0 is artअगरicially set to 1.
	 * So we use the block size that is set क्रम the other 3 mailboxes.
	 */
	dev->htc_cnxt->block_sz = dev->ar->mbox_info.block_size;

	/* must be a घातer of 2 */
	अगर ((dev->htc_cnxt->block_sz & (dev->htc_cnxt->block_sz - 1)) != 0) अणु
		WARN_ON(1);
		status = -EINVAL;
		जाओ fail_setup;
	पूर्ण

	/* assemble mask, used क्रम padding to a block */
	dev->htc_cnxt->block_mask = dev->htc_cnxt->block_sz - 1;

	ath6kl_dbg(ATH6KL_DBG_HIF, "hif block size %d mbox addr 0x%x\n",
		   dev->htc_cnxt->block_sz, dev->ar->mbox_info.htc_addr);

	status = ath6kl_hअगर_disable_पूर्णांकrs(dev);

fail_setup:
	वापस status;
पूर्ण
