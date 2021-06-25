<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCSI low-level driver क्रम the 53c94 SCSI bus adaptor found
 * on Power Macपूर्णांकosh computers, controlling the बाह्यal SCSI chain.
 * We assume the 53c94 is connected to a DBDMA (descriptor-based DMA)
 * controller.
 *
 * Paul Mackerras, August 1996.
 * Copyright (C) 1996 Paul Mackerras.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/macपन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश "mac53c94.h"

क्रमागत fsc_phase अणु
	idle,
	selecting,
	dataing,
	completing,
	busमुक्तing,
पूर्ण;

काष्ठा fsc_state अणु
	काष्ठा	mac53c94_regs __iomem *regs;
	पूर्णांक	पूर्णांकr;
	काष्ठा	dbdma_regs __iomem *dma;
	पूर्णांक	dमुख्यtr;
	पूर्णांक	clk_freq;
	काष्ठा	Scsi_Host *host;
	काष्ठा scsi_cmnd *request_q;
	काष्ठा scsi_cmnd *request_qtail;
	काष्ठा scsi_cmnd *current_req;		/* req we're currently working on */
	क्रमागत fsc_phase phase;		/* what we're currently trying to करो */
	काष्ठा dbdma_cmd *dma_cmds;	/* space क्रम dbdma commands, aligned */
	व्योम	*dma_cmd_space;
	काष्ठा	pci_dev *pdev;
	dma_addr_t dma_addr;
	काष्ठा macio_dev *mdev;
पूर्ण;

अटल व्योम mac53c94_init(काष्ठा fsc_state *);
अटल व्योम mac53c94_start(काष्ठा fsc_state *);
अटल व्योम mac53c94_पूर्णांकerrupt(पूर्णांक, व्योम *);
अटल irqवापस_t करो_mac53c94_पूर्णांकerrupt(पूर्णांक, व्योम *);
अटल व्योम cmd_करोne(काष्ठा fsc_state *, पूर्णांक result);
अटल व्योम set_dma_cmds(काष्ठा fsc_state *, काष्ठा scsi_cmnd *);


अटल पूर्णांक mac53c94_queue_lck(काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा fsc_state *state;

#अगर 0
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG "mac53c94_queue %p: command is", cmd);
		क्रम (i = 0; i < cmd->cmd_len; ++i)
			prपूर्णांकk(KERN_CONT " %.2x", cmd->cmnd[i]);
		prपूर्णांकk(KERN_CONT "\n");
		prपूर्णांकk(KERN_DEBUG "use_sg=%d request_bufflen=%d request_buffer=%p\n",
		       scsi_sg_count(cmd), scsi_bufflen(cmd), scsi_sglist(cmd));
	पूर्ण
#पूर्ण_अगर

	cmd->scsi_करोne = करोne;
	cmd->host_scribble = शून्य;

	state = (काष्ठा fsc_state *) cmd->device->host->hostdata;

	अगर (state->request_q == शून्य)
		state->request_q = cmd;
	अन्यथा
		state->request_qtail->host_scribble = (व्योम *) cmd;
	state->request_qtail = cmd;

	अगर (state->phase == idle)
		mac53c94_start(state);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(mac53c94_queue)

अटल पूर्णांक mac53c94_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा fsc_state *state = (काष्ठा fsc_state *) cmd->device->host->hostdata;
	काष्ठा mac53c94_regs __iomem *regs = state->regs;
	काष्ठा dbdma_regs __iomem *dma = state->dma;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(cmd->device->host->host_lock, flags);

	ग_लिखोl((RUN|PAUSE|FLUSH|WAKE) << 16, &dma->control);
	ग_लिखोb(CMD_SCSI_RESET, &regs->command);	/* निश्चित RST */
	udelay(100);			/* leave it on क्रम a जबतक (>= 25us) */
	ग_लिखोb(CMD_RESET, &regs->command);
	udelay(20);
	mac53c94_init(state);
	ग_लिखोb(CMD_NOP, &regs->command);

	spin_unlock_irqrestore(cmd->device->host->host_lock, flags);
	वापस SUCCESS;
पूर्ण

अटल व्योम mac53c94_init(काष्ठा fsc_state *state)
अणु
	काष्ठा mac53c94_regs __iomem *regs = state->regs;
	काष्ठा dbdma_regs __iomem *dma = state->dma;
	पूर्णांक x;

	ग_लिखोb(state->host->this_id | CF1_PAR_ENABLE, &regs->config1);
	ग_लिखोb(TIMO_VAL(250), &regs->sel_समयout);	/* 250ms */
	ग_लिखोb(CLKF_VAL(state->clk_freq), &regs->clk_factor);
	ग_लिखोb(CF2_FEATURE_EN, &regs->config2);
	ग_लिखोb(0, &regs->config3);
	ग_लिखोb(0, &regs->sync_period);
	ग_लिखोb(0, &regs->sync_offset);
	x = पढ़ोb(&regs->पूर्णांकerrupt);
	ग_लिखोl((RUN|PAUSE|FLUSH|WAKE) << 16, &dma->control);
पूर्ण

/*
 * Start the next command क्रम a 53C94.
 * Should be called with पूर्णांकerrupts disabled.
 */
अटल व्योम mac53c94_start(काष्ठा fsc_state *state)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा mac53c94_regs __iomem *regs = state->regs;
	पूर्णांक i;

	अगर (state->phase != idle || state->current_req != शून्य)
		panic("inappropriate mac53c94_start (state=%p)", state);
	अगर (state->request_q == शून्य)
		वापस;
	state->current_req = cmd = state->request_q;
	state->request_q = (काष्ठा scsi_cmnd *) cmd->host_scribble;

	/* Off we go */
	ग_लिखोb(0, &regs->count_lo);
	ग_लिखोb(0, &regs->count_mid);
	ग_लिखोb(0, &regs->count_hi);
	ग_लिखोb(CMD_NOP + CMD_DMA_MODE, &regs->command);
	udelay(1);
	ग_लिखोb(CMD_FLUSH, &regs->command);
	udelay(1);
	ग_लिखोb(cmd->device->id, &regs->dest_id);
	ग_लिखोb(0, &regs->sync_period);
	ग_लिखोb(0, &regs->sync_offset);

	/* load the command पूर्णांकo the FIFO */
	क्रम (i = 0; i < cmd->cmd_len; ++i)
		ग_लिखोb(cmd->cmnd[i], &regs->fअगरo);

	/* करो select without ATN XXX */
	ग_लिखोb(CMD_SELECT, &regs->command);
	state->phase = selecting;

	set_dma_cmds(state, cmd);
पूर्ण

अटल irqवापस_t करो_mac53c94_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा Scsi_Host *dev = ((काष्ठा fsc_state *) dev_id)->current_req->device->host;
	
	spin_lock_irqsave(dev->host_lock, flags);
	mac53c94_पूर्णांकerrupt(irq, dev_id);
	spin_unlock_irqrestore(dev->host_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mac53c94_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsc_state *state = (काष्ठा fsc_state *) dev_id;
	काष्ठा mac53c94_regs __iomem *regs = state->regs;
	काष्ठा dbdma_regs __iomem *dma = state->dma;
	काष्ठा scsi_cmnd *cmd = state->current_req;
	पूर्णांक nb, stat, seq, पूर्णांकr;
	अटल पूर्णांक mac53c94_errors;

	/*
	 * Apparently, पढ़ोing the पूर्णांकerrupt रेजिस्टर unlatches
	 * the status and sequence step रेजिस्टरs.
	 */
	seq = पढ़ोb(&regs->seqstep);
	stat = पढ़ोb(&regs->status);
	पूर्णांकr = पढ़ोb(&regs->पूर्णांकerrupt);

#अगर 0
	prपूर्णांकk(KERN_DEBUG "mac53c94_intr, intr=%x stat=%x seq=%x phase=%d\n",
	       पूर्णांकr, stat, seq, state->phase);
#पूर्ण_अगर

	अगर (पूर्णांकr & INTR_RESET) अणु
		/* SCSI bus was reset */
		prपूर्णांकk(KERN_INFO "external SCSI bus reset detected\n");
		ग_लिखोb(CMD_NOP, &regs->command);
		ग_लिखोl(RUN << 16, &dma->control);	/* stop dma */
		cmd_करोne(state, DID_RESET << 16);
		वापस;
	पूर्ण
	अगर (पूर्णांकr & INTR_ILL_CMD) अणु
		prपूर्णांकk(KERN_ERR "53c94: invalid cmd, intr=%x stat=%x seq=%x phase=%d\n",
		       पूर्णांकr, stat, seq, state->phase);
		cmd_करोne(state, DID_ERROR << 16);
		वापस;
	पूर्ण
	अगर (stat & STAT_ERROR) अणु
#अगर 0
		/* XXX these seem to be harmless? */
		prपूर्णांकk("53c94: bad error, intr=%x stat=%x seq=%x phase=%d\n",
		       पूर्णांकr, stat, seq, state->phase);
#पूर्ण_अगर
		++mac53c94_errors;
		ग_लिखोb(CMD_NOP + CMD_DMA_MODE, &regs->command);
	पूर्ण
	अगर (cmd == 0) अणु
		prपूर्णांकk(KERN_DEBUG "53c94: interrupt with no command active?\n");
		वापस;
	पूर्ण
	अगर (stat & STAT_PARITY) अणु
		prपूर्णांकk(KERN_ERR "mac53c94: parity error\n");
		cmd_करोne(state, DID_PARITY << 16);
		वापस;
	पूर्ण
	चयन (state->phase) अणु
	हाल selecting:
		अगर (पूर्णांकr & INTR_DISCONNECT) अणु
			/* selection समयd out */
			cmd_करोne(state, DID_BAD_TARGET << 16);
			वापस;
		पूर्ण
		अगर (पूर्णांकr != INTR_BUS_SERV + INTR_DONE) अणु
			prपूर्णांकk(KERN_DEBUG "got intr %x during selection\n", पूर्णांकr);
			cmd_करोne(state, DID_ERROR << 16);
			वापस;
		पूर्ण
		अगर ((seq & SS_MASK) != SS_DONE) अणु
			prपूर्णांकk(KERN_DEBUG "seq step %x after command\n", seq);
			cmd_करोne(state, DID_ERROR << 16);
			वापस;
		पूर्ण
		ग_लिखोb(CMD_NOP, &regs->command);
		/* set DMA controller going अगर any data to transfer */
		अगर ((stat & (STAT_MSG|STAT_CD)) == 0
		    && (scsi_sg_count(cmd) > 0 || scsi_bufflen(cmd))) अणु
			nb = cmd->SCp.this_residual;
			अगर (nb > 0xfff0)
				nb = 0xfff0;
			cmd->SCp.this_residual -= nb;
			ग_लिखोb(nb, &regs->count_lo);
			ग_लिखोb(nb >> 8, &regs->count_mid);
			ग_लिखोb(CMD_DMA_MODE + CMD_NOP, &regs->command);
			ग_लिखोl(virt_to_phys(state->dma_cmds), &dma->cmdptr);
			ग_लिखोl((RUN << 16) | RUN, &dma->control);
			ग_लिखोb(CMD_DMA_MODE + CMD_XFER_DATA, &regs->command);
			state->phase = dataing;
			अवरोध;
		पूर्ण अन्यथा अगर ((stat & STAT_PHASE) == STAT_CD + STAT_IO) अणु
			/* up to status phase alपढ़ोy */
			ग_लिखोb(CMD_I_COMPLETE, &regs->command);
			state->phase = completing;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "in unexpected phase %x after cmd\n",
			       stat & STAT_PHASE);
			cmd_करोne(state, DID_ERROR << 16);
			वापस;
		पूर्ण
		अवरोध;

	हाल dataing:
		अगर (पूर्णांकr != INTR_BUS_SERV) अणु
			prपूर्णांकk(KERN_DEBUG "got intr %x before status\n", पूर्णांकr);
			cmd_करोne(state, DID_ERROR << 16);
			वापस;
		पूर्ण
		अगर (cmd->SCp.this_residual != 0
		    && (stat & (STAT_MSG|STAT_CD)) == 0) अणु
			/* Set up the count regs to transfer more */
			nb = cmd->SCp.this_residual;
			अगर (nb > 0xfff0)
				nb = 0xfff0;
			cmd->SCp.this_residual -= nb;
			ग_लिखोb(nb, &regs->count_lo);
			ग_लिखोb(nb >> 8, &regs->count_mid);
			ग_लिखोb(CMD_DMA_MODE + CMD_NOP, &regs->command);
			ग_लिखोb(CMD_DMA_MODE + CMD_XFER_DATA, &regs->command);
			अवरोध;
		पूर्ण
		अगर ((stat & STAT_PHASE) != STAT_CD + STAT_IO) अणु
			prपूर्णांकk(KERN_DEBUG "intr %x before data xfer complete\n", पूर्णांकr);
		पूर्ण
		ग_लिखोl(RUN << 16, &dma->control);	/* stop dma */
		scsi_dma_unmap(cmd);
		/* should check dma status */
		ग_लिखोb(CMD_I_COMPLETE, &regs->command);
		state->phase = completing;
		अवरोध;
	हाल completing:
		अगर (पूर्णांकr != INTR_DONE) अणु
			prपूर्णांकk(KERN_DEBUG "got intr %x on completion\n", पूर्णांकr);
			cmd_करोne(state, DID_ERROR << 16);
			वापस;
		पूर्ण
		cmd->SCp.Status = पढ़ोb(&regs->fअगरo);
		cmd->SCp.Message = पढ़ोb(&regs->fअगरo);
		ग_लिखोb(CMD_ACCEPT_MSG, &regs->command);
		state->phase = busमुक्तing;
		अवरोध;
	हाल busमुक्तing:
		अगर (पूर्णांकr != INTR_DISCONNECT) अणु
			prपूर्णांकk(KERN_DEBUG "got intr %x when expected disconnect\n", पूर्णांकr);
		पूर्ण
		cmd_करोne(state, (DID_OK << 16) + (cmd->SCp.Message << 8)
			 + cmd->SCp.Status);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "don't know about phase %d\n", state->phase);
	पूर्ण
पूर्ण

अटल व्योम cmd_करोne(काष्ठा fsc_state *state, पूर्णांक result)
अणु
	काष्ठा scsi_cmnd *cmd;

	cmd = state->current_req;
	अगर (cmd) अणु
		cmd->result = result;
		(*cmd->scsi_करोne)(cmd);
		state->current_req = शून्य;
	पूर्ण
	state->phase = idle;
	mac53c94_start(state);
पूर्ण

/*
 * Set up DMA commands क्रम transferring data.
 */
अटल व्योम set_dma_cmds(काष्ठा fsc_state *state, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक i, dma_cmd, total, nseg;
	काष्ठा scatterlist *scl;
	काष्ठा dbdma_cmd *dcmds;
	dma_addr_t dma_addr;
	u32 dma_len;

	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);
	अगर (!nseg)
		वापस;

	dma_cmd = cmd->sc_data_direction == DMA_TO_DEVICE ?
			OUTPUT_MORE : INPUT_MORE;
	dcmds = state->dma_cmds;
	total = 0;

	scsi_क्रम_each_sg(cmd, scl, nseg, i) अणु
		dma_addr = sg_dma_address(scl);
		dma_len = sg_dma_len(scl);
		अगर (dma_len > 0xffff)
			panic("mac53c94: scatterlist element >= 64k");
		total += dma_len;
		dcmds->req_count = cpu_to_le16(dma_len);
		dcmds->command = cpu_to_le16(dma_cmd);
		dcmds->phy_addr = cpu_to_le32(dma_addr);
		dcmds->xfer_status = 0;
		++dcmds;
	पूर्ण

	dma_cmd += OUTPUT_LAST - OUTPUT_MORE;
	dcmds[-1].command = cpu_to_le16(dma_cmd);
	dcmds->command = cpu_to_le16(DBDMA_STOP);
	cmd->SCp.this_residual = total;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा mac53c94_ढाँचा = अणु
	.proc_name	= "53c94",
	.name		= "53C94",
	.queuecommand	= mac53c94_queue,
	.eh_host_reset_handler = mac53c94_host_reset,
	.can_queue	= 1,
	.this_id	= 7,
	.sg_tablesize	= SG_ALL,
	.max_segment_size = 65535,
पूर्ण;

अटल पूर्णांक mac53c94_probe(काष्ठा macio_dev *mdev, स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा device_node *node = macio_get_of_node(mdev);
	काष्ठा pci_dev *pdev = macio_get_pci_dev(mdev);
	काष्ठा fsc_state *state;
	काष्ठा Scsi_Host *host;
	व्योम *dma_cmd_space;
	स्थिर अचिन्हित अक्षर *clkprop;
	पूर्णांक proplen, rc = -ENODEV;

	अगर (macio_resource_count(mdev) != 2 || macio_irq_count(mdev) != 2) अणु
		prपूर्णांकk(KERN_ERR "mac53c94: expected 2 addrs and intrs"
		       " (got %d/%d)\n",
		       macio_resource_count(mdev), macio_irq_count(mdev));
		वापस -ENODEV;
	पूर्ण

	अगर (macio_request_resources(mdev, "mac53c94") != 0) अणु
       		prपूर्णांकk(KERN_ERR "mac53c94: unable to request memory resources");
		वापस -EBUSY;
	पूर्ण

       	host = scsi_host_alloc(&mac53c94_ढाँचा, माप(काष्ठा fsc_state));
	अगर (host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mac53c94: couldn't register host");
		rc = -ENOMEM;
		जाओ out_release;
	पूर्ण

	state = (काष्ठा fsc_state *) host->hostdata;
	macio_set_drvdata(mdev, state);
	state->host = host;
	state->pdev = pdev;
	state->mdev = mdev;

	state->regs = (काष्ठा mac53c94_regs __iomem *)
		ioremap(macio_resource_start(mdev, 0), 0x1000);
	state->पूर्णांकr = macio_irq(mdev, 0);
	state->dma = (काष्ठा dbdma_regs __iomem *)
		ioremap(macio_resource_start(mdev, 1), 0x1000);
	state->dमुख्यtr = macio_irq(mdev, 1);
	अगर (state->regs == शून्य || state->dma == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mac53c94: ioremap failed for %pOF\n", node);
		जाओ out_मुक्त;
	पूर्ण

	clkprop = of_get_property(node, "clock-frequency", &proplen);
       	अगर (clkprop == शून्य || proplen != माप(पूर्णांक)) अणु
       		prपूर्णांकk(KERN_ERR "%pOF: can't get clock frequency, "
       		       "assuming 25MHz\n", node);
       		state->clk_freq = 25000000;
       	पूर्ण अन्यथा
       		state->clk_freq = *(पूर्णांक *)clkprop;

       	/* Space क्रम dma command list: +1 क्रम stop command,
       	 * +1 to allow क्रम aligning.
	 * XXX FIXME: Use DMA consistent routines
	 */
       	dma_cmd_space = kदो_स्मृति_array(host->sg_tablesize + 2,
					     माप(काष्ठा dbdma_cmd),
					     GFP_KERNEL);
	अगर (!dma_cmd_space) अणु
		prपूर्णांकk(KERN_ERR "mac53c94: couldn't allocate dma "
		       "command space for %pOF\n", node);
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	state->dma_cmds = (काष्ठा dbdma_cmd *)DBDMA_ALIGN(dma_cmd_space);
	स_रखो(state->dma_cmds, 0, (host->sg_tablesize + 1)
	       * माप(काष्ठा dbdma_cmd));
	state->dma_cmd_space = dma_cmd_space;

	mac53c94_init(state);

	अगर (request_irq(state->पूर्णांकr, करो_mac53c94_पूर्णांकerrupt, 0, "53C94",state)) अणु
		prपूर्णांकk(KERN_ERR "mac53C94: can't get irq %d for %pOF\n",
		       state->पूर्णांकr, node);
		जाओ out_मुक्त_dma;
	पूर्ण

	rc = scsi_add_host(host, &mdev->ofdev.dev);
	अगर (rc != 0)
		जाओ out_release_irq;

	scsi_scan_host(host);
	वापस 0;

 out_release_irq:
	मुक्त_irq(state->पूर्णांकr, state);
 out_मुक्त_dma:
	kमुक्त(state->dma_cmd_space);
 out_मुक्त:
	अगर (state->dma != शून्य)
		iounmap(state->dma);
	अगर (state->regs != शून्य)
		iounmap(state->regs);
	scsi_host_put(host);
 out_release:
	macio_release_resources(mdev);

	वापस rc;
पूर्ण

अटल पूर्णांक mac53c94_हटाओ(काष्ठा macio_dev *mdev)
अणु
	काष्ठा fsc_state *fp = (काष्ठा fsc_state *)macio_get_drvdata(mdev);
	काष्ठा Scsi_Host *host = fp->host;

	scsi_हटाओ_host(host);

	मुक्त_irq(fp->पूर्णांकr, fp);

	अगर (fp->regs)
		iounmap(fp->regs);
	अगर (fp->dma)
		iounmap(fp->dma);
	kमुक्त(fp->dma_cmd_space);

	scsi_host_put(host);

	macio_release_resources(mdev);

	वापस 0;
पूर्ण


अटल काष्ठा of_device_id mac53c94_match[] = 
अणु
	अणु
	.name 		= "53c94",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE (of, mac53c94_match);

अटल काष्ठा macio_driver mac53c94_driver = 
अणु
	.driver = अणु
		.name 		= "mac53c94",
		.owner		= THIS_MODULE,
		.of_match_table	= mac53c94_match,
	पूर्ण,
	.probe		= mac53c94_probe,
	.हटाओ		= mac53c94_हटाओ,
पूर्ण;


अटल पूर्णांक __init init_mac53c94(व्योम)
अणु
	वापस macio_रेजिस्टर_driver(&mac53c94_driver);
पूर्ण

अटल व्योम __निकास निकास_mac53c94(व्योम)
अणु
	वापस macio_unरेजिस्टर_driver(&mac53c94_driver);
पूर्ण

module_init(init_mac53c94);
module_निकास(निकास_mac53c94);

MODULE_DESCRIPTION("PowerMac 53c94 SCSI driver");
MODULE_AUTHOR("Paul Mackerras <paulus@samba.org>");
MODULE_LICENSE("GPL");
