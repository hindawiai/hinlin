<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LocalPlus Bus FIFO driver क्रम the Freescale MPC52xx.
 *
 * Copyright (C) 2009 Secret Lab Technologies Ltd.
 *
 * Toकरो:
 * - Add support क्रम multiple requests to be queued.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/समय.स>

#समावेश <linux/fsl/bestcomm/bestcomm.h>
#समावेश <linux/fsl/bestcomm/bestcomm_priv.h>
#समावेश <linux/fsl/bestcomm/gen_bd.h>

MODULE_AUTHOR("Grant Likely <grant.likely@secretlab.ca>");
MODULE_DESCRIPTION("MPC5200 LocalPlus FIFO device driver");
MODULE_LICENSE("GPL");

#घोषणा LPBFIFO_REG_PACKET_SIZE		(0x00)
#घोषणा LPBFIFO_REG_START_ADDRESS	(0x04)
#घोषणा LPBFIFO_REG_CONTROL		(0x08)
#घोषणा LPBFIFO_REG_ENABLE		(0x0C)
#घोषणा LPBFIFO_REG_BYTES_DONE_STATUS	(0x14)
#घोषणा LPBFIFO_REG_FIFO_DATA		(0x40)
#घोषणा LPBFIFO_REG_FIFO_STATUS		(0x44)
#घोषणा LPBFIFO_REG_FIFO_CONTROL	(0x48)
#घोषणा LPBFIFO_REG_FIFO_ALARM		(0x4C)

काष्ठा mpc52xx_lpbfअगरo अणु
	काष्ठा device *dev;
	phys_addr_t regs_phys;
	व्योम __iomem *regs;
	पूर्णांक irq;
	spinlock_t lock;

	काष्ठा bcom_task *bcom_tx_task;
	काष्ठा bcom_task *bcom_rx_task;
	काष्ठा bcom_task *bcom_cur_task;

	/* Current state data */
	काष्ठा mpc52xx_lpbfअगरo_request *req;
	पूर्णांक dma_irqs_enabled;
पूर्ण;

/* The MPC5200 has only one fअगरo, so only need one instance काष्ठाure */
अटल काष्ठा mpc52xx_lpbfअगरo lpbfअगरo;

/**
 * mpc52xx_lpbfअगरo_kick - Trigger the next block of data to be transferred
 */
अटल व्योम mpc52xx_lpbfअगरo_kick(काष्ठा mpc52xx_lpbfअगरo_request *req)
अणु
	माप_प्रकार transfer_size = req->size - req->pos;
	काष्ठा bcom_bd *bd;
	व्योम __iomem *reg;
	u32 *data;
	पूर्णांक i;
	पूर्णांक bit_fields;
	पूर्णांक dma = !(req->flags & MPC52XX_LPBFIFO_FLAG_NO_DMA);
	पूर्णांक ग_लिखो = req->flags & MPC52XX_LPBFIFO_FLAG_WRITE;
	पूर्णांक poll_dma = req->flags & MPC52XX_LPBFIFO_FLAG_POLL_DMA;

	/* Set and clear the reset bits; is good practice in User Manual */
	out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, 0x01010000);

	/* set master enable bit */
	out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, 0x00000001);
	अगर (!dma) अणु
		/* While the FIFO can be setup क्रम transfer sizes as large as
		 * 16M-1, the FIFO itself is only 512 bytes deep and it करोes
		 * not generate पूर्णांकerrupts क्रम FIFO full events (only transfer
		 * complete will उठाओ an IRQ).  Thereक्रमe when not using
		 * Bestcomm to drive the FIFO it needs to either be polled, or
		 * transfers need to स्थिरrained to the size of the fअगरo.
		 *
		 * This driver restricts the size of the transfer
		 */
		अगर (transfer_size > 512)
			transfer_size = 512;

		/* Load the FIFO with data */
		अगर (ग_लिखो) अणु
			reg = lpbfअगरo.regs + LPBFIFO_REG_FIFO_DATA;
			data = req->data + req->pos;
			क्रम (i = 0; i < transfer_size; i += 4)
				out_be32(reg, *data++);
		पूर्ण

		/* Unmask both error and completion irqs */
		out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, 0x00000301);
	पूर्ण अन्यथा अणु
		/* Choose the correct direction
		 *
		 * Configure the watermarks so DMA will always complete correctly.
		 * It may be worth experimenting with the ALARM value to see अगर
		 * there is a perक्रमmance impacit.  However, अगर it is wrong there
		 * is a risk of DMA not transferring the last chunk of data
		 */
		अगर (ग_लिखो) अणु
			out_be32(lpbfअगरo.regs + LPBFIFO_REG_FIFO_ALARM, 0x1e4);
			out_8(lpbfअगरo.regs + LPBFIFO_REG_FIFO_CONTROL, 7);
			lpbfअगरo.bcom_cur_task = lpbfअगरo.bcom_tx_task;
		पूर्ण अन्यथा अणु
			out_be32(lpbfअगरo.regs + LPBFIFO_REG_FIFO_ALARM, 0x1ff);
			out_8(lpbfअगरo.regs + LPBFIFO_REG_FIFO_CONTROL, 0);
			lpbfअगरo.bcom_cur_task = lpbfअगरo.bcom_rx_task;

			अगर (poll_dma) अणु
				अगर (lpbfअगरo.dma_irqs_enabled) अणु
					disable_irq(bcom_get_task_irq(lpbfअगरo.bcom_rx_task));
					lpbfअगरo.dma_irqs_enabled = 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!lpbfअगरo.dma_irqs_enabled) अणु
					enable_irq(bcom_get_task_irq(lpbfअगरo.bcom_rx_task));
					lpbfअगरo.dma_irqs_enabled = 1;
				पूर्ण
			पूर्ण
		पूर्ण

		bd = bcom_prepare_next_buffer(lpbfअगरo.bcom_cur_task);
		bd->status = transfer_size;
		अगर (!ग_लिखो) अणु
			/*
			 * In the DMA पढ़ो हाल, the DMA करोesn't complete,
			 * possibly due to incorrect watermarks in the ALARM
			 * and CONTROL regs. For now instead of trying to
			 * determine the right watermarks that will make this
			 * work, just increase the number of bytes the FIFO is
			 * expecting.
			 *
			 * When submitting another operation, the FIFO will get
			 * reset, so the condition of the FIFO रुकोing क्रम a
			 * non-existent 4 bytes will get cleared.
			 */
			transfer_size += 4; /* BLECH! */
		पूर्ण
		bd->data[0] = req->data_phys + req->pos;
		bcom_submit_next_buffer(lpbfअगरo.bcom_cur_task, शून्य);

		/* error irq & master enabled bit */
		bit_fields = 0x00000201;

		/* Unmask irqs */
		अगर (ग_लिखो && (!poll_dma))
			bit_fields |= 0x00000100; /* completion irq too */
		out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, bit_fields);
	पूर्ण

	/* Set transfer size, width, chip select and READ mode */
	out_be32(lpbfअगरo.regs + LPBFIFO_REG_START_ADDRESS,
		 req->offset + req->pos);
	out_be32(lpbfअगरo.regs + LPBFIFO_REG_PACKET_SIZE, transfer_size);

	bit_fields = req->cs << 24 | 0x000008;
	अगर (!ग_लिखो)
		bit_fields |= 0x010000; /* पढ़ो mode */
	out_be32(lpbfअगरo.regs + LPBFIFO_REG_CONTROL, bit_fields);

	/* Kick it off */
	अगर (!lpbfअगरo.req->defer_xfer_start)
		out_8(lpbfअगरo.regs + LPBFIFO_REG_PACKET_SIZE, 0x01);
	अगर (dma)
		bcom_enable(lpbfअगरo.bcom_cur_task);
पूर्ण

/**
 * mpc52xx_lpbfअगरo_irq - IRQ handler क्रम LPB FIFO
 *
 * On transmit, the dma completion irq triggers beक्रमe the fअगरo completion
 * triggers.  Handle the dma completion here instead of the LPB FIFO Bestcomm
 * task completion irq because everything is not really करोne until the LPB FIFO
 * completion irq triggers.
 *
 * In other words:
 * For DMA, on receive, the "Fat Lady" is the bestcom completion irq. on
 * transmit, the fअगरo completion irq is the "Fat Lady". The opera (or in this
 * हाल the DMA/FIFO operation) is not finished until the "Fat Lady" sings.
 *
 * Reasons क्रम entering this routine:
 * 1) PIO mode rx and tx completion irq
 * 2) DMA पूर्णांकerrupt mode tx completion irq
 * 3) DMA polled mode tx
 *
 * Exit conditions:
 * 1) Transfer पातed
 * 2) FIFO complete without DMA; more data to करो
 * 3) FIFO complete without DMA; all data transferred
 * 4) FIFO complete using DMA
 *
 * Condition 1 can occur regardless of whether or not DMA is used.
 * It requires executing the callback to report the error and निकासing
 * immediately.
 *
 * Condition 2 requires programming the FIFO with the next block of data
 *
 * Condition 3 requires executing the callback to report completion
 *
 * Condition 4 means the same as 3, except that we also retrieve the bcom
 * buffer so DMA करोesn't get clogged up.
 *
 * To make things trickier, the spinlock must be dropped beक्रमe
 * executing the callback, otherwise we could end up with a deadlock
 * or nested spinlock condition.  The out path is non-trivial, so
 * extra fiddling is करोne to make sure all paths lead to the same
 * outbound code.
 */
अटल irqवापस_t mpc52xx_lpbfअगरo_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mpc52xx_lpbfअगरo_request *req;
	u32 status = in_8(lpbfअगरo.regs + LPBFIFO_REG_BYTES_DONE_STATUS);
	व्योम __iomem *reg;
	u32 *data;
	पूर्णांक count, i;
	पूर्णांक करो_callback = 0;
	u32 ts;
	अचिन्हित दीर्घ flags;
	पूर्णांक dma, ग_लिखो, poll_dma;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);
	ts = mftb();

	req = lpbfअगरo.req;
	अगर (!req) अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
		pr_err("bogus LPBFIFO IRQ\n");
		वापस IRQ_HANDLED;
	पूर्ण

	dma = !(req->flags & MPC52XX_LPBFIFO_FLAG_NO_DMA);
	ग_लिखो = req->flags & MPC52XX_LPBFIFO_FLAG_WRITE;
	poll_dma = req->flags & MPC52XX_LPBFIFO_FLAG_POLL_DMA;

	अगर (dma && !ग_लिखो) अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
		pr_err("bogus LPBFIFO IRQ (dma and not writing)\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर ((status & 0x01) == 0) अणु
		जाओ out;
	पूर्ण

	/* check पात bit */
	अगर (status & 0x10) अणु
		out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, 0x01010000);
		करो_callback = 1;
		जाओ out;
	पूर्ण

	/* Read result from hardware */
	count = in_be32(lpbfअगरo.regs + LPBFIFO_REG_BYTES_DONE_STATUS);
	count &= 0x00ffffff;

	अगर (!dma && !ग_लिखो) अणु
		/* copy the data out of the FIFO */
		reg = lpbfअगरo.regs + LPBFIFO_REG_FIFO_DATA;
		data = req->data + req->pos;
		क्रम (i = 0; i < count; i += 4)
			*data++ = in_be32(reg);
	पूर्ण

	/* Update transfer position and count */
	req->pos += count;

	/* Decide what to करो next */
	अगर (req->size - req->pos)
		mpc52xx_lpbfअगरo_kick(req); /* more work to करो */
	अन्यथा
		करो_callback = 1;

 out:
	/* Clear the IRQ */
	out_8(lpbfअगरo.regs + LPBFIFO_REG_BYTES_DONE_STATUS, 0x01);

	अगर (dma && (status & 0x11)) अणु
		/*
		 * Count the DMA as complete only when the FIFO completion
		 * status or पात bits are set.
		 *
		 * (status & 0x01) should always be the हाल except someबार
		 * when using polled DMA.
		 *
		 * (status & 0x10) अणुtransfer पातedपूर्ण: This हाल needs more
		 * testing.
		 */
		bcom_retrieve_buffer(lpbfअगरo.bcom_cur_task, &status, शून्य);
	पूर्ण
	req->last_byte = ((u8 *)req->data)[req->size - 1];

	/* When the करो_callback flag is set; it means the transfer is finished
	 * so set the FIFO as idle */
	अगर (करो_callback)
		lpbfअगरo.req = शून्य;

	अगर (irq != 0) /* करोn't increment on polled हाल */
		req->irq_count++;

	req->irq_ticks += mftb() - ts;
	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);

	/* Spinlock is released; it is now safe to call the callback */
	अगर (करो_callback && req->callback)
		req->callback(req);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * mpc52xx_lpbfअगरo_bcom_irq - IRQ handler क्रम LPB FIFO Bestcomm task
 *
 * Only used when receiving data.
 */
अटल irqवापस_t mpc52xx_lpbfअगरo_bcom_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mpc52xx_lpbfअगरo_request *req;
	अचिन्हित दीर्घ flags;
	u32 status;
	u32 ts;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);
	ts = mftb();

	req = lpbfअगरo.req;
	अगर (!req || (req->flags & MPC52XX_LPBFIFO_FLAG_NO_DMA)) अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (irq != 0) /* करोn't increment on polled हाल */
		req->irq_count++;

	अगर (!bcom_buffer_करोne(lpbfअगरo.bcom_cur_task)) अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);

		req->buffer_not_करोne_cnt++;
		अगर ((req->buffer_not_करोne_cnt % 1000) == 0)
			pr_err("transfer stalled\n");

		वापस IRQ_HANDLED;
	पूर्ण

	bcom_retrieve_buffer(lpbfअगरo.bcom_cur_task, &status, शून्य);

	req->last_byte = ((u8 *)req->data)[req->size - 1];

	req->pos = status & 0x00ffffff;

	/* Mark the FIFO as idle */
	lpbfअगरo.req = शून्य;

	/* Release the lock beक्रमe calling out to the callback. */
	req->irq_ticks += mftb() - ts;
	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);

	अगर (req->callback)
		req->callback(req);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * mpc52xx_lpbfअगरo_bcom_poll - Poll क्रम DMA completion
 */
व्योम mpc52xx_lpbfअगरo_poll(व्योम)
अणु
	काष्ठा mpc52xx_lpbfअगरo_request *req = lpbfअगरo.req;
	पूर्णांक dma = !(req->flags & MPC52XX_LPBFIFO_FLAG_NO_DMA);
	पूर्णांक ग_लिखो = req->flags & MPC52XX_LPBFIFO_FLAG_WRITE;

	/*
	 * For more inक्रमmation, see comments on the "Fat Lady" 
	 */
	अगर (dma && ग_लिखो)
		mpc52xx_lpbfअगरo_irq(0, शून्य);
	अन्यथा 
		mpc52xx_lpbfअगरo_bcom_irq(0, शून्य);
पूर्ण
EXPORT_SYMBOL(mpc52xx_lpbfअगरo_poll);

/**
 * mpc52xx_lpbfअगरo_submit - Submit an LPB FIFO transfer request.
 * @req: Poपूर्णांकer to request काष्ठाure
 */
पूर्णांक mpc52xx_lpbfअगरo_submit(काष्ठा mpc52xx_lpbfअगरo_request *req)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!lpbfअगरo.regs)
		वापस -ENODEV;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);

	/* If the req poपूर्णांकer is alपढ़ोy set, then a transfer is in progress */
	अगर (lpbfअगरo.req) अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
		वापस -EBUSY;
	पूर्ण

	/* Setup the transfer */
	lpbfअगरo.req = req;
	req->irq_count = 0;
	req->irq_ticks = 0;
	req->buffer_not_करोne_cnt = 0;
	req->pos = 0;

	mpc52xx_lpbfअगरo_kick(req);
	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpc52xx_lpbfअगरo_submit);

पूर्णांक mpc52xx_lpbfअगरo_start_xfer(काष्ठा mpc52xx_lpbfअगरo_request *req)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!lpbfअगरo.regs)
		वापस -ENODEV;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);

	/*
	 * If the req poपूर्णांकer is alपढ़ोy set and a transfer was
	 * started on submit, then this transfer is in progress
	 */
	अगर (lpbfअगरo.req && !lpbfअगरo.req->defer_xfer_start) अणु
		spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
		वापस -EBUSY;
	पूर्ण

	/*
	 * If the req was previously submitted but not
	 * started, start it now
	 */
	अगर (lpbfअगरo.req && lpbfअगरo.req == req &&
	    lpbfअगरo.req->defer_xfer_start) अणु
		out_8(lpbfअगरo.regs + LPBFIFO_REG_PACKET_SIZE, 0x01);
	पूर्ण

	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mpc52xx_lpbfअगरo_start_xfer);

व्योम mpc52xx_lpbfअगरo_पात(काष्ठा mpc52xx_lpbfअगरo_request *req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lpbfअगरo.lock, flags);
	अगर (lpbfअगरo.req == req) अणु
		/* Put it पूर्णांकo reset and clear the state */
		bcom_gen_bd_rx_reset(lpbfअगरo.bcom_rx_task);
		bcom_gen_bd_tx_reset(lpbfअगरo.bcom_tx_task);
		out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, 0x01010000);
		lpbfअगरo.req = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&lpbfअगरo.lock, flags);
पूर्ण
EXPORT_SYMBOL(mpc52xx_lpbfअगरo_पात);

अटल पूर्णांक mpc52xx_lpbfअगरo_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा resource res;
	पूर्णांक rc = -ENOMEM;

	अगर (lpbfअगरo.dev != शून्य)
		वापस -ENOSPC;

	lpbfअगरo.irq = irq_of_parse_and_map(op->dev.of_node, 0);
	अगर (!lpbfअगरo.irq)
		वापस -ENODEV;

	अगर (of_address_to_resource(op->dev.of_node, 0, &res))
		वापस -ENODEV;
	lpbfअगरo.regs_phys = res.start;
	lpbfअगरo.regs = of_iomap(op->dev.of_node, 0);
	अगर (!lpbfअगरo.regs)
		वापस -ENOMEM;

	spin_lock_init(&lpbfअगरo.lock);

	/* Put FIFO पूर्णांकo reset */
	out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, 0x01010000);

	/* Register the पूर्णांकerrupt handler */
	rc = request_irq(lpbfअगरo.irq, mpc52xx_lpbfअगरo_irq, 0,
			 "mpc52xx-lpbfifo", &lpbfअगरo);
	अगर (rc)
		जाओ err_irq;

	/* Request the Bestcomm receive (fअगरo --> memory) task and IRQ */
	lpbfअगरo.bcom_rx_task =
		bcom_gen_bd_rx_init(2, res.start + LPBFIFO_REG_FIFO_DATA,
				    BCOM_INITIATOR_SCLPC, BCOM_IPR_SCLPC,
				    16*1024*1024);
	अगर (!lpbfअगरo.bcom_rx_task)
		जाओ err_bcom_rx;

	rc = request_irq(bcom_get_task_irq(lpbfअगरo.bcom_rx_task),
			 mpc52xx_lpbfअगरo_bcom_irq, 0,
			 "mpc52xx-lpbfifo-rx", &lpbfअगरo);
	अगर (rc)
		जाओ err_bcom_rx_irq;

	lpbfअगरo.dma_irqs_enabled = 1;

	/* Request the Bestcomm transmit (memory --> fअगरo) task and IRQ */
	lpbfअगरo.bcom_tx_task =
		bcom_gen_bd_tx_init(2, res.start + LPBFIFO_REG_FIFO_DATA,
				    BCOM_INITIATOR_SCLPC, BCOM_IPR_SCLPC);
	अगर (!lpbfअगरo.bcom_tx_task)
		जाओ err_bcom_tx;

	lpbfअगरo.dev = &op->dev;
	वापस 0;

 err_bcom_tx:
	मुक्त_irq(bcom_get_task_irq(lpbfअगरo.bcom_rx_task), &lpbfअगरo);
 err_bcom_rx_irq:
	bcom_gen_bd_rx_release(lpbfअगरo.bcom_rx_task);
 err_bcom_rx:
 err_irq:
	iounmap(lpbfअगरo.regs);
	lpbfअगरo.regs = शून्य;

	dev_err(&op->dev, "mpc52xx_lpbfifo_probe() failed\n");
	वापस -ENODEV;
पूर्ण


अटल पूर्णांक mpc52xx_lpbfअगरo_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	अगर (lpbfअगरo.dev != &op->dev)
		वापस 0;

	/* Put FIFO in reset */
	out_be32(lpbfअगरo.regs + LPBFIFO_REG_ENABLE, 0x01010000);

	/* Release the bestcomm transmit task */
	मुक्त_irq(bcom_get_task_irq(lpbfअगरo.bcom_tx_task), &lpbfअगरo);
	bcom_gen_bd_tx_release(lpbfअगरo.bcom_tx_task);
	
	/* Release the bestcomm receive task */
	मुक्त_irq(bcom_get_task_irq(lpbfअगरo.bcom_rx_task), &lpbfअगरo);
	bcom_gen_bd_rx_release(lpbfअगरo.bcom_rx_task);

	मुक्त_irq(lpbfअगरo.irq, &lpbfअगरo);
	iounmap(lpbfअगरo.regs);
	lpbfअगरo.regs = शून्य;
	lpbfअगरo.dev = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc52xx_lpbfअगरo_match[] = अणु
	अणु .compatible = "fsl,mpc5200-lpbfifo", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc52xx_lpbfअगरo_match);

अटल काष्ठा platक्रमm_driver mpc52xx_lpbfअगरo_driver = अणु
	.driver = अणु
		.name = "mpc52xx-lpbfifo",
		.of_match_table = mpc52xx_lpbfअगरo_match,
	पूर्ण,
	.probe = mpc52xx_lpbfअगरo_probe,
	.हटाओ = mpc52xx_lpbfअगरo_हटाओ,
पूर्ण;
module_platक्रमm_driver(mpc52xx_lpbfअगरo_driver);
