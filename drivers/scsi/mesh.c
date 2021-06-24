<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCSI low-level driver क्रम the MESH (Macपूर्णांकosh Enhanced SCSI Hardware)
 * bus adaptor found on Power Macपूर्णांकosh computers.
 * We assume the MESH is connected to a DBDMA (descriptor-based DMA)
 * controller.
 *
 * Paul Mackerras, August 1996.
 * Copyright (C) 1996 Paul Mackerras.
 *
 * Apr. 21 2002  - BenH		Rework bus reset code क्रम new error handler
 *                              Add delay after initial bus reset
 *                              Add module parameters
 *
 * Sep. 27 2003  - BenH		Move to new driver model, fix some ग_लिखो posting
 *				issues
 * To करो:
 * - handle पातs correctly
 * - retry arbitration अगर lost (unless higher levels करो this क्रम us)
 * - घातer करोwn the chip when no device is detected
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hydra.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/macपन.स>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश "mesh.h"

#अगर 1
#अघोषित KERN_DEBUG
#घोषणा KERN_DEBUG KERN_WARNING
#पूर्ण_अगर

MODULE_AUTHOR("Paul Mackerras (paulus@samba.org)");
MODULE_DESCRIPTION("PowerMac MESH SCSI driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक sync_rate = CONFIG_SCSI_MESH_SYNC_RATE;
अटल पूर्णांक sync_tarमाला_लो = 0xff;
अटल पूर्णांक resel_tarमाला_लो = 0xff;
अटल पूर्णांक debug_tarमाला_लो = 0;	/* prपूर्णांक debug क्रम these tarमाला_लो */
अटल पूर्णांक init_reset_delay = CONFIG_SCSI_MESH_RESET_DELAY_MS;

module_param(sync_rate, पूर्णांक, 0);
MODULE_PARM_DESC(sync_rate, "Synchronous rate (0..10, 0=async)");
module_param(sync_tarमाला_लो, पूर्णांक, 0);
MODULE_PARM_DESC(sync_tarमाला_लो, "Bitmask of targets allowed to set synchronous");
module_param(resel_tarमाला_लो, पूर्णांक, 0);
MODULE_PARM_DESC(resel_tarमाला_लो, "Bitmask of targets allowed to set disconnect");
module_param(debug_tarमाला_लो, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_tarमाला_लो, "Bitmask of debugged targets");
module_param(init_reset_delay, पूर्णांक, 0);
MODULE_PARM_DESC(init_reset_delay, "Initial bus reset delay (0=no reset)");

अटल पूर्णांक mesh_sync_period = 100;
अटल पूर्णांक mesh_sync_offset = 0;
अटल अचिन्हित अक्षर use_active_neg = 0;  /* bit mask क्रम SEQ_ACTIVE_NEG अगर used */

#घोषणा ALLOW_SYNC(tgt)		((sync_tarमाला_लो >> (tgt)) & 1)
#घोषणा ALLOW_RESEL(tgt)	((resel_tarमाला_लो >> (tgt)) & 1)
#घोषणा ALLOW_DEBUG(tgt)	((debug_tarमाला_लो >> (tgt)) & 1)
#घोषणा DEBUG_TARGET(cmd)	((cmd) && ALLOW_DEBUG((cmd)->device->id))

#अघोषित MESH_DBG
#घोषणा N_DBG_LOG	50
#घोषणा N_DBG_SLOG	20
#घोषणा NUM_DBG_EVENTS	13
#अघोषित	DBG_USE_TB		/* bombs on 601 */

काष्ठा dbglog अणु
	अक्षर	*fmt;
	u32	tb;
	u8	phase;
	u8	bs0;
	u8	bs1;
	u8	tgt;
	पूर्णांक	d;
पूर्ण;

क्रमागत mesh_phase अणु
	idle,
	arbitrating,
	selecting,
	commanding,
	dataing,
	statusing,
	busमुक्तing,
	disconnecting,
	reselecting,
	sleeping
पूर्ण;

क्रमागत msg_phase अणु
	msg_none,
	msg_out,
	msg_out_xxx,
	msg_out_last,
	msg_in,
	msg_in_bad,
पूर्ण;

क्रमागत sdtr_phase अणु
	करो_sdtr,
	sdtr_sent,
	sdtr_करोne
पूर्ण;

काष्ठा mesh_target अणु
	क्रमागत sdtr_phase sdtr_state;
	पूर्णांक	sync_params;
	पूर्णांक	data_goes_out;		/* guess as to data direction */
	काष्ठा scsi_cmnd *current_req;
	u32	saved_ptr;
#अगर_घोषित MESH_DBG
	पूर्णांक	log_ix;
	पूर्णांक	n_log;
	काष्ठा dbglog log[N_DBG_LOG];
#पूर्ण_अगर
पूर्ण;

काष्ठा mesh_state अणु
	अस्थिर काष्ठा	mesh_regs __iomem *mesh;
	पूर्णांक	meshपूर्णांकr;
	अस्थिर काष्ठा	dbdma_regs __iomem *dma;
	पूर्णांक	dमुख्यtr;
	काष्ठा	Scsi_Host *host;
	काष्ठा	mesh_state *next;
	काष्ठा scsi_cmnd *request_q;
	काष्ठा scsi_cmnd *request_qtail;
	क्रमागत mesh_phase phase;		/* what we're currently trying to करो */
	क्रमागत msg_phase msgphase;
	पूर्णांक	conn_tgt;		/* target we're connected to */
	काष्ठा scsi_cmnd *current_req;		/* req we're currently working on */
	पूर्णांक	data_ptr;
	पूर्णांक	dma_started;
	पूर्णांक	dma_count;
	पूर्णांक	stat;
	पूर्णांक	पातing;
	पूर्णांक	expect_reply;
	पूर्णांक	n_msgin;
	u8	msgin[16];
	पूर्णांक	n_msgout;
	पूर्णांक	last_n_msgout;
	u8	msgout[16];
	काष्ठा dbdma_cmd *dma_cmds;	/* space क्रम dbdma commands, aligned */
	dma_addr_t dma_cmd_bus;
	व्योम	*dma_cmd_space;
	पूर्णांक	dma_cmd_size;
	पूर्णांक	clk_freq;
	काष्ठा mesh_target tgts[8];
	काष्ठा macio_dev *mdev;
	काष्ठा pci_dev* pdev;
#अगर_घोषित MESH_DBG
	पूर्णांक	log_ix;
	पूर्णांक	n_log;
	काष्ठा dbglog log[N_DBG_SLOG];
#पूर्ण_अगर
पूर्ण;

/*
 * Driver is too messy, we need a few prototypes...
 */
अटल व्योम mesh_करोne(काष्ठा mesh_state *ms, पूर्णांक start_next);
अटल व्योम mesh_पूर्णांकerrupt(काष्ठा mesh_state *ms);
अटल व्योम cmd_complete(काष्ठा mesh_state *ms);
अटल व्योम set_dma_cmds(काष्ठा mesh_state *ms, काष्ठा scsi_cmnd *cmd);
अटल व्योम halt_dma(काष्ठा mesh_state *ms);
अटल व्योम phase_mismatch(काष्ठा mesh_state *ms);


/*
 * Some debugging & logging routines
 */

#अगर_घोषित MESH_DBG

अटल अंतरभूत u32 पढ़ोtb(व्योम)
अणु
	u32 tb;

#अगर_घोषित DBG_USE_TB
	/* Beware: अगर you enable this, it will crash on 601s. */
	यंत्र ("mftb %0" : "=r" (tb) : );
#अन्यथा
	tb = 0;
#पूर्ण_अगर
	वापस tb;
पूर्ण

अटल व्योम dlog(काष्ठा mesh_state *ms, अक्षर *fmt, पूर्णांक a)
अणु
	काष्ठा mesh_target *tp = &ms->tgts[ms->conn_tgt];
	काष्ठा dbglog *tlp, *slp;

	tlp = &tp->log[tp->log_ix];
	slp = &ms->log[ms->log_ix];
	tlp->fmt = fmt;
	tlp->tb = पढ़ोtb();
	tlp->phase = (ms->msgphase << 4) + ms->phase;
	tlp->bs0 = ms->mesh->bus_status0;
	tlp->bs1 = ms->mesh->bus_status1;
	tlp->tgt = ms->conn_tgt;
	tlp->d = a;
	*slp = *tlp;
	अगर (++tp->log_ix >= N_DBG_LOG)
		tp->log_ix = 0;
	अगर (tp->n_log < N_DBG_LOG)
		++tp->n_log;
	अगर (++ms->log_ix >= N_DBG_SLOG)
		ms->log_ix = 0;
	अगर (ms->n_log < N_DBG_SLOG)
		++ms->n_log;
पूर्ण

अटल व्योम dumplog(काष्ठा mesh_state *ms, पूर्णांक t)
अणु
	काष्ठा mesh_target *tp = &ms->tgts[t];
	काष्ठा dbglog *lp;
	पूर्णांक i;

	अगर (tp->n_log == 0)
		वापस;
	i = tp->log_ix - tp->n_log;
	अगर (i < 0)
		i += N_DBG_LOG;
	tp->n_log = 0;
	करो अणु
		lp = &tp->log[i];
		prपूर्णांकk(KERN_DEBUG "mesh log %d: bs=%.2x%.2x ph=%.2x ",
		       t, lp->bs1, lp->bs0, lp->phase);
#अगर_घोषित DBG_USE_TB
		prपूर्णांकk("tb=%10u ", lp->tb);
#पूर्ण_अगर
		prपूर्णांकk(lp->fmt, lp->d);
		prपूर्णांकk("\n");
		अगर (++i >= N_DBG_LOG)
			i = 0;
	पूर्ण जबतक (i != tp->log_ix);
पूर्ण

अटल व्योम dumpslog(काष्ठा mesh_state *ms)
अणु
	काष्ठा dbglog *lp;
	पूर्णांक i;

	अगर (ms->n_log == 0)
		वापस;
	i = ms->log_ix - ms->n_log;
	अगर (i < 0)
		i += N_DBG_SLOG;
	ms->n_log = 0;
	करो अणु
		lp = &ms->log[i];
		prपूर्णांकk(KERN_DEBUG "mesh log: bs=%.2x%.2x ph=%.2x t%d ",
		       lp->bs1, lp->bs0, lp->phase, lp->tgt);
#अगर_घोषित DBG_USE_TB
		prपूर्णांकk("tb=%10u ", lp->tb);
#पूर्ण_अगर
		prपूर्णांकk(lp->fmt, lp->d);
		prपूर्णांकk("\n");
		अगर (++i >= N_DBG_SLOG)
			i = 0;
	पूर्ण जबतक (i != ms->log_ix);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम dlog(काष्ठा mesh_state *ms, अक्षर *fmt, पूर्णांक a)
अणुपूर्ण
अटल अंतरभूत व्योम dumplog(काष्ठा mesh_state *ms, पूर्णांक tgt)
अणुपूर्ण
अटल अंतरभूत व्योम dumpslog(काष्ठा mesh_state *ms)
अणुपूर्ण

#पूर्ण_अगर /* MESH_DBG */

#घोषणा MKWORD(a, b, c, d)	(((a) << 24) + ((b) << 16) + ((c) << 8) + (d))

अटल व्योम
mesh_dump_regs(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	अस्थिर काष्ठा dbdma_regs __iomem *md = ms->dma;
	पूर्णांक t;
	काष्ठा mesh_target *tp;

	prपूर्णांकk(KERN_DEBUG "mesh: state at %p, regs at %p, dma at %p\n",
	       ms, mr, md);
	prपूर्णांकk(KERN_DEBUG "    ct=%4x seq=%2x bs=%4x fc=%2x "
	       "exc=%2x err=%2x im=%2x int=%2x sp=%2x\n",
	       (mr->count_hi << 8) + mr->count_lo, mr->sequence,
	       (mr->bus_status1 << 8) + mr->bus_status0, mr->fअगरo_count,
	       mr->exception, mr->error, mr->पूर्णांकr_mask, mr->पूर्णांकerrupt,
	       mr->sync_params);
	जबतक(in_8(&mr->fअगरo_count))
		prपूर्णांकk(KERN_DEBUG " fifo data=%.2x\n",in_8(&mr->fअगरo));
	prपूर्णांकk(KERN_DEBUG "    dma stat=%x cmdptr=%x\n",
	       in_le32(&md->status), in_le32(&md->cmdptr));
	prपूर्णांकk(KERN_DEBUG "    phase=%d msgphase=%d conn_tgt=%d data_ptr=%d\n",
	       ms->phase, ms->msgphase, ms->conn_tgt, ms->data_ptr);
	prपूर्णांकk(KERN_DEBUG "    dma_st=%d dma_ct=%d n_msgout=%d\n",
	       ms->dma_started, ms->dma_count, ms->n_msgout);
	क्रम (t = 0; t < 8; ++t) अणु
		tp = &ms->tgts[t];
		अगर (tp->current_req == शून्य)
			जारी;
		prपूर्णांकk(KERN_DEBUG "    target %d: req=%p goes_out=%d saved_ptr=%d\n",
		       t, tp->current_req, tp->data_goes_out, tp->saved_ptr);
	पूर्ण
पूर्ण


/*
 * Flush ग_लिखो buffers on the bus path to the mesh
 */
अटल अंतरभूत व्योम mesh_flush_io(अस्थिर काष्ठा mesh_regs __iomem *mr)
अणु
	(व्योम)in_8(&mr->mesh_id);
पूर्ण


/*
 * Complete a SCSI command
 */
अटल व्योम mesh_completed(काष्ठा mesh_state *ms, काष्ठा scsi_cmnd *cmd)
अणु
	(*cmd->scsi_करोne)(cmd);
पूर्ण


/* Called with  meshपूर्णांकerrupt disabled, initialize the chipset
 * and eventually करो the initial bus reset. The lock must not be
 * held since we can schedule.
 */
अटल व्योम mesh_init(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	अस्थिर काष्ठा dbdma_regs __iomem *md = ms->dma;

	mesh_flush_io(mr);
	udelay(100);

	/* Reset controller */
	out_le32(&md->control, (RUN|PAUSE|FLUSH|WAKE) << 16);	/* stop dma */
	out_8(&mr->exception, 0xff);	/* clear all exception bits */
	out_8(&mr->error, 0xff);	/* clear all error bits */
	out_8(&mr->sequence, SEQ_RESETMESH);
	mesh_flush_io(mr);
	udelay(10);
	out_8(&mr->पूर्णांकr_mask, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
	out_8(&mr->source_id, ms->host->this_id);
	out_8(&mr->sel_समयout, 25);	/* 250ms */
	out_8(&mr->sync_params, ASYNC_PARAMS);

	अगर (init_reset_delay) अणु
		prपूर्णांकk(KERN_INFO "mesh: performing initial bus reset...\n");
		
		/* Reset bus */
		out_8(&mr->bus_status1, BS1_RST);	/* निश्चित RST */
		mesh_flush_io(mr);
		udelay(30);			/* leave it on क्रम >= 25us */
		out_8(&mr->bus_status1, 0);	/* negate RST */
		mesh_flush_io(mr);

		/* Wait क्रम bus to come back */
		msleep(init_reset_delay);
	पूर्ण
	
	/* Reconfigure controller */
	out_8(&mr->पूर्णांकerrupt, 0xff);	/* clear all पूर्णांकerrupt bits */
	out_8(&mr->sequence, SEQ_FLUSHFIFO);
	mesh_flush_io(mr);
	udelay(1);
	out_8(&mr->sync_params, ASYNC_PARAMS);
	out_8(&mr->sequence, SEQ_ENBRESEL);

	ms->phase = idle;
	ms->msgphase = msg_none;
पूर्ण


अटल व्योम mesh_start_cmd(काष्ठा mesh_state *ms, काष्ठा scsi_cmnd *cmd)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	पूर्णांक t, id;

	id = cmd->device->id;
	ms->current_req = cmd;
	ms->tgts[id].data_goes_out = cmd->sc_data_direction == DMA_TO_DEVICE;
	ms->tgts[id].current_req = cmd;

#अगर 1
	अगर (DEBUG_TARGET(cmd)) अणु
		पूर्णांक i;
		prपूर्णांकk(KERN_DEBUG "mesh_start: %p tgt=%d cmd=", cmd, id);
		क्रम (i = 0; i < cmd->cmd_len; ++i)
			prपूर्णांकk(" %x", cmd->cmnd[i]);
		prपूर्णांकk(" use_sg=%d buffer=%p bufflen=%u\n",
		       scsi_sg_count(cmd), scsi_sglist(cmd), scsi_bufflen(cmd));
	पूर्ण
#पूर्ण_अगर
	अगर (ms->dma_started)
		panic("mesh: double DMA start !\n");

	ms->phase = arbitrating;
	ms->msgphase = msg_none;
	ms->data_ptr = 0;
	ms->dma_started = 0;
	ms->n_msgout = 0;
	ms->last_n_msgout = 0;
	ms->expect_reply = 0;
	ms->conn_tgt = id;
	ms->tgts[id].saved_ptr = 0;
	ms->stat = DID_OK;
	ms->पातing = 0;
#अगर_घोषित MESH_DBG
	ms->tgts[id].n_log = 0;
	dlog(ms, "start cmd=%x", (पूर्णांक) cmd);
#पूर्ण_अगर

	/* Off we go */
	dlog(ms, "about to arb, intr/exc/err/fc=%.8x",
	     MKWORD(mr->पूर्णांकerrupt, mr->exception, mr->error, mr->fअगरo_count));
	out_8(&mr->पूर्णांकerrupt, INT_CMDDONE);
	out_8(&mr->sequence, SEQ_ENBRESEL);
	mesh_flush_io(mr);
	udelay(1);

	अगर (in_8(&mr->bus_status1) & (BS1_BSY | BS1_SEL)) अणु
		/*
		 * Some other device has the bus or is arbitrating क्रम it -
		 * probably a target which is about to reselect us.
		 */
		dlog(ms, "busy b4 arb, intr/exc/err/fc=%.8x",
		     MKWORD(mr->पूर्णांकerrupt, mr->exception,
			    mr->error, mr->fअगरo_count));
		क्रम (t = 100; t > 0; --t) अणु
			अगर ((in_8(&mr->bus_status1) & (BS1_BSY | BS1_SEL)) == 0)
				अवरोध;
			अगर (in_8(&mr->पूर्णांकerrupt) != 0) अणु
				dlog(ms, "intr b4 arb, intr/exc/err/fc=%.8x",
				     MKWORD(mr->पूर्णांकerrupt, mr->exception,
					    mr->error, mr->fअगरo_count));
				mesh_पूर्णांकerrupt(ms);
				अगर (ms->phase != arbitrating)
					वापस;
			पूर्ण
			udelay(1);
		पूर्ण
		अगर (in_8(&mr->bus_status1) & (BS1_BSY | BS1_SEL)) अणु
			/* XXX should try again in a little जबतक */
			ms->stat = DID_BUS_BUSY;
			ms->phase = idle;
			mesh_करोne(ms, 0);
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Apparently the mesh has a bug where it will निश्चित both its
	 * own bit and the target's bit on the bus during arbitration.
	 */
	out_8(&mr->dest_id, mr->source_id);

	/*
	 * There appears to be a race with reselection someबार,
	 * where a target reselects us just as we issue the
	 * arbitrate command.  It seems that then the arbitrate
	 * command just hangs रुकोing क्रम the bus to be मुक्त
	 * without giving us a reselection exception.
	 * The only way I have found to get it to respond correctly
	 * is this: disable reselection beक्रमe issuing the arbitrate
	 * command, then after issuing it, अगर it looks like a target
	 * is trying to reselect us, reset the mesh and then enable
	 * reselection.
	 */
	out_8(&mr->sequence, SEQ_DISRESEL);
	अगर (in_8(&mr->पूर्णांकerrupt) != 0) अणु
		dlog(ms, "intr after disresel, intr/exc/err/fc=%.8x",
		     MKWORD(mr->पूर्णांकerrupt, mr->exception,
			    mr->error, mr->fअगरo_count));
		mesh_पूर्णांकerrupt(ms);
		अगर (ms->phase != arbitrating)
			वापस;
		dlog(ms, "after intr after disresel, intr/exc/err/fc=%.8x",
		     MKWORD(mr->पूर्णांकerrupt, mr->exception,
			    mr->error, mr->fअगरo_count));
	पूर्ण

	out_8(&mr->sequence, SEQ_ARBITRATE);

	क्रम (t = 230; t > 0; --t) अणु
		अगर (in_8(&mr->पूर्णांकerrupt) != 0)
			अवरोध;
		udelay(1);
	पूर्ण
	dlog(ms, "after arb, intr/exc/err/fc=%.8x",
	     MKWORD(mr->पूर्णांकerrupt, mr->exception, mr->error, mr->fअगरo_count));
	अगर (in_8(&mr->पूर्णांकerrupt) == 0 && (in_8(&mr->bus_status1) & BS1_SEL)
	    && (in_8(&mr->bus_status0) & BS0_IO)) अणु
		/* looks like a reselection - try resetting the mesh */
		dlog(ms, "resel? after arb, intr/exc/err/fc=%.8x",
		     MKWORD(mr->पूर्णांकerrupt, mr->exception, mr->error, mr->fअगरo_count));
		out_8(&mr->sequence, SEQ_RESETMESH);
		mesh_flush_io(mr);
		udelay(10);
		out_8(&mr->पूर्णांकerrupt, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
		out_8(&mr->पूर्णांकr_mask, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
		out_8(&mr->sequence, SEQ_ENBRESEL);
		mesh_flush_io(mr);
		क्रम (t = 10; t > 0 && in_8(&mr->पूर्णांकerrupt) == 0; --t)
			udelay(1);
		dlog(ms, "tried reset after arb, intr/exc/err/fc=%.8x",
		     MKWORD(mr->पूर्णांकerrupt, mr->exception, mr->error, mr->fअगरo_count));
#अगर_अघोषित MESH_MULTIPLE_HOSTS
		अगर (in_8(&mr->पूर्णांकerrupt) == 0 && (in_8(&mr->bus_status1) & BS1_SEL)
		    && (in_8(&mr->bus_status0) & BS0_IO)) अणु
			prपूर्णांकk(KERN_ERR "mesh: controller not responding"
			       " to reselection!\n");
			/*
			 * If this is a target reselecting us, and the
			 * mesh isn't responding, the higher levels of
			 * the scsi code will eventually समय out and
			 * reset the bus.
			 */
		पूर्ण
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * Start the next command क्रम a MESH.
 * Should be called with पूर्णांकerrupts disabled.
 */
अटल व्योम mesh_start(काष्ठा mesh_state *ms)
अणु
	काष्ठा scsi_cmnd *cmd, *prev, *next;

	अगर (ms->phase != idle || ms->current_req != शून्य) अणु
		prपूर्णांकk(KERN_ERR "inappropriate mesh_start (phase=%d, ms=%p)",
		       ms->phase, ms);
		वापस;
	पूर्ण

	जबतक (ms->phase == idle) अणु
		prev = शून्य;
		क्रम (cmd = ms->request_q; ; cmd = (काष्ठा scsi_cmnd *) cmd->host_scribble) अणु
			अगर (cmd == शून्य)
				वापस;
			अगर (ms->tgts[cmd->device->id].current_req == शून्य)
				अवरोध;
			prev = cmd;
		पूर्ण
		next = (काष्ठा scsi_cmnd *) cmd->host_scribble;
		अगर (prev == शून्य)
			ms->request_q = next;
		अन्यथा
			prev->host_scribble = (व्योम *) next;
		अगर (next == शून्य)
			ms->request_qtail = prev;

		mesh_start_cmd(ms, cmd);
	पूर्ण
पूर्ण

अटल व्योम mesh_करोne(काष्ठा mesh_state *ms, पूर्णांक start_next)
अणु
	काष्ठा scsi_cmnd *cmd;
	काष्ठा mesh_target *tp = &ms->tgts[ms->conn_tgt];

	cmd = ms->current_req;
	ms->current_req = शून्य;
	tp->current_req = शून्य;
	अगर (cmd) अणु
		cmd->result = (ms->stat << 16) | cmd->SCp.Status;
		अगर (ms->stat == DID_OK)
			cmd->result |= cmd->SCp.Message << 8;
		अगर (DEBUG_TARGET(cmd)) अणु
			prपूर्णांकk(KERN_DEBUG "mesh_done: result = %x, data_ptr=%d, buflen=%d\n",
			       cmd->result, ms->data_ptr, scsi_bufflen(cmd));
#अगर 0
			/* needs to use sg? */
			अगर ((cmd->cmnd[0] == 0 || cmd->cmnd[0] == 0x12 || cmd->cmnd[0] == 3)
			    && cmd->request_buffer != 0) अणु
				अचिन्हित अक्षर *b = cmd->request_buffer;
				prपूर्णांकk(KERN_DEBUG "buffer = %x %x %x %x %x %x %x %x\n",
				       b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
			पूर्ण
#पूर्ण_अगर
		पूर्ण
		cmd->SCp.this_residual -= ms->data_ptr;
		mesh_completed(ms, cmd);
	पूर्ण
	अगर (start_next) अणु
		out_8(&ms->mesh->sequence, SEQ_ENBRESEL);
		mesh_flush_io(ms->mesh);
		udelay(1);
		ms->phase = idle;
		mesh_start(ms);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम add_sdtr_msg(काष्ठा mesh_state *ms)
अणु
	पूर्णांक i = ms->n_msgout;

	ms->msgout[i] = EXTENDED_MESSAGE;
	ms->msgout[i+1] = 3;
	ms->msgout[i+2] = EXTENDED_SDTR;
	ms->msgout[i+3] = mesh_sync_period/4;
	ms->msgout[i+4] = (ALLOW_SYNC(ms->conn_tgt)? mesh_sync_offset: 0);
	ms->n_msgout = i + 5;
पूर्ण

अटल व्योम set_sdtr(काष्ठा mesh_state *ms, पूर्णांक period, पूर्णांक offset)
अणु
	काष्ठा mesh_target *tp = &ms->tgts[ms->conn_tgt];
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	पूर्णांक v, tr;

	tp->sdtr_state = sdtr_करोne;
	अगर (offset == 0) अणु
		/* asynchronous */
		अगर (SYNC_OFF(tp->sync_params))
			prपूर्णांकk(KERN_INFO "mesh: target %d now asynchronous\n",
			       ms->conn_tgt);
		tp->sync_params = ASYNC_PARAMS;
		out_8(&mr->sync_params, ASYNC_PARAMS);
		वापस;
	पूर्ण
	/*
	 * We need to compute उच्चमान(clk_freq * period / 500e6) - 2
	 * without incurring overflow.
	 */
	v = (ms->clk_freq / 5000) * period;
	अगर (v <= 250000) अणु
		/* special हाल: sync_period == 5 * clk_period */
		v = 0;
		/* units of tr are 100kB/s */
		tr = (ms->clk_freq + 250000) / 500000;
	पूर्ण अन्यथा अणु
		/* sync_period == (v + 2) * 2 * clk_period */
		v = (v + 99999) / 100000 - 2;
		अगर (v > 15)
			v = 15;	/* oops */
		tr = ((ms->clk_freq / (v + 2)) + 199999) / 200000;
	पूर्ण
	अगर (offset > 15)
		offset = 15;	/* can't happen */
	tp->sync_params = SYNC_PARAMS(offset, v);
	out_8(&mr->sync_params, tp->sync_params);
	prपूर्णांकk(KERN_INFO "mesh: target %d synchronous at %d.%d MB/s\n",
	       ms->conn_tgt, tr/10, tr%10);
पूर्ण

अटल व्योम start_phase(काष्ठा mesh_state *ms)
अणु
	पूर्णांक i, seq, nb;
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	अस्थिर काष्ठा dbdma_regs __iomem *md = ms->dma;
	काष्ठा scsi_cmnd *cmd = ms->current_req;
	काष्ठा mesh_target *tp = &ms->tgts[ms->conn_tgt];

	dlog(ms, "start_phase nmo/exc/fc/seq = %.8x",
	     MKWORD(ms->n_msgout, mr->exception, mr->fअगरo_count, mr->sequence));
	out_8(&mr->पूर्णांकerrupt, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
	seq = use_active_neg + (ms->n_msgout? SEQ_ATN: 0);
	चयन (ms->msgphase) अणु
	हाल msg_none:
		अवरोध;

	हाल msg_in:
		out_8(&mr->count_hi, 0);
		out_8(&mr->count_lo, 1);
		out_8(&mr->sequence, SEQ_MSGIN + seq);
		ms->n_msgin = 0;
		वापस;

	हाल msg_out:
		/*
		 * To make sure ATN drops beक्रमe we निश्चित ACK क्रम
		 * the last byte of the message, we have to करो the
		 * last byte specially.
		 */
		अगर (ms->n_msgout <= 0) अणु
			prपूर्णांकk(KERN_ERR "mesh: msg_out but n_msgout=%d\n",
			       ms->n_msgout);
			mesh_dump_regs(ms);
			ms->msgphase = msg_none;
			अवरोध;
		पूर्ण
		अगर (ALLOW_DEBUG(ms->conn_tgt)) अणु
			prपूर्णांकk(KERN_DEBUG "mesh: sending %d msg bytes:",
			       ms->n_msgout);
			क्रम (i = 0; i < ms->n_msgout; ++i)
				prपूर्णांकk(" %x", ms->msgout[i]);
			prपूर्णांकk("\n");
		पूर्ण
		dlog(ms, "msgout msg=%.8x", MKWORD(ms->n_msgout, ms->msgout[0],
						ms->msgout[1], ms->msgout[2]));
		out_8(&mr->count_hi, 0);
		out_8(&mr->sequence, SEQ_FLUSHFIFO);
		mesh_flush_io(mr);
		udelay(1);
		/*
		 * If ATN is not alपढ़ोy निश्चितed, we निश्चित it, then
		 * issue a SEQ_MSGOUT to get the mesh to drop ACK.
		 */
		अगर ((in_8(&mr->bus_status0) & BS0_ATN) == 0) अणु
			dlog(ms, "bus0 was %.2x explicitly asserting ATN", mr->bus_status0);
			out_8(&mr->bus_status0, BS0_ATN); /* explicit ATN */
			mesh_flush_io(mr);
			udelay(1);
			out_8(&mr->count_lo, 1);
			out_8(&mr->sequence, SEQ_MSGOUT + seq);
			out_8(&mr->bus_status0, 0); /* release explicit ATN */
			dlog(ms,"hace: after explicit ATN bus0=%.2x",mr->bus_status0);
		पूर्ण
		अगर (ms->n_msgout == 1) अणु
			/*
			 * We can't issue the SEQ_MSGOUT without ATN
			 * until the target has निश्चितed REQ.  The logic
			 * in cmd_complete handles both situations:
			 * REQ alपढ़ोy निश्चितed or not.
			 */
			cmd_complete(ms);
		पूर्ण अन्यथा अणु
			out_8(&mr->count_lo, ms->n_msgout - 1);
			out_8(&mr->sequence, SEQ_MSGOUT + seq);
			क्रम (i = 0; i < ms->n_msgout - 1; ++i)
				out_8(&mr->fअगरo, ms->msgout[i]);
		पूर्ण
		वापस;

	शेष:
		prपूर्णांकk(KERN_ERR "mesh bug: start_phase msgphase=%d\n",
		       ms->msgphase);
	पूर्ण

	चयन (ms->phase) अणु
	हाल selecting:
		out_8(&mr->dest_id, ms->conn_tgt);
		out_8(&mr->sequence, SEQ_SELECT + SEQ_ATN);
		अवरोध;
	हाल commanding:
		out_8(&mr->sync_params, tp->sync_params);
		out_8(&mr->count_hi, 0);
		अगर (cmd) अणु
			out_8(&mr->count_lo, cmd->cmd_len);
			out_8(&mr->sequence, SEQ_COMMAND + seq);
			क्रम (i = 0; i < cmd->cmd_len; ++i)
				out_8(&mr->fअगरo, cmd->cmnd[i]);
		पूर्ण अन्यथा अणु
			out_8(&mr->count_lo, 6);
			out_8(&mr->sequence, SEQ_COMMAND + seq);
			क्रम (i = 0; i < 6; ++i)
				out_8(&mr->fअगरo, 0);
		पूर्ण
		अवरोध;
	हाल dataing:
		/* transfer data, अगर any */
		अगर (!ms->dma_started) अणु
			set_dma_cmds(ms, cmd);
			out_le32(&md->cmdptr, virt_to_phys(ms->dma_cmds));
			out_le32(&md->control, (RUN << 16) | RUN);
			ms->dma_started = 1;
		पूर्ण
		nb = ms->dma_count;
		अगर (nb > 0xfff0)
			nb = 0xfff0;
		ms->dma_count -= nb;
		ms->data_ptr += nb;
		out_8(&mr->count_lo, nb);
		out_8(&mr->count_hi, nb >> 8);
		out_8(&mr->sequence, (tp->data_goes_out?
				SEQ_DATAOUT: SEQ_DATAIN) + SEQ_DMA_MODE + seq);
		अवरोध;
	हाल statusing:
		out_8(&mr->count_hi, 0);
		out_8(&mr->count_lo, 1);
		out_8(&mr->sequence, SEQ_STATUS + seq);
		अवरोध;
	हाल busमुक्तing:
	हाल disconnecting:
		out_8(&mr->sequence, SEQ_ENBRESEL);
		mesh_flush_io(mr);
		udelay(1);
		dlog(ms, "enbresel intr/exc/err/fc=%.8x",
		     MKWORD(mr->पूर्णांकerrupt, mr->exception, mr->error,
			    mr->fअगरo_count));
		out_8(&mr->sequence, SEQ_BUSFREE);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "mesh: start_phase called with phase=%d\n",
		       ms->phase);
		dumpslog(ms);
	पूर्ण

पूर्ण

अटल अंतरभूत व्योम get_msgin(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	पूर्णांक i, n;

	n = mr->fअगरo_count;
	अगर (n != 0) अणु
		i = ms->n_msgin;
		ms->n_msgin = i + n;
		क्रम (; n > 0; --n)
			ms->msgin[i++] = in_8(&mr->fअगरo);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक msgin_length(काष्ठा mesh_state *ms)
अणु
	पूर्णांक b, n;

	n = 1;
	अगर (ms->n_msgin > 0) अणु
		b = ms->msgin[0];
		अगर (b == 1) अणु
			/* extended message */
			n = ms->n_msgin < 2? 2: ms->msgin[1] + 2;
		पूर्ण अन्यथा अगर (0x20 <= b && b <= 0x2f) अणु
			/* 2-byte message */
			n = 2;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

अटल व्योम reselected(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा mesh_target *tp;
	पूर्णांक b, t, prev;

	चयन (ms->phase) अणु
	हाल idle:
		अवरोध;
	हाल arbitrating:
		अगर ((cmd = ms->current_req) != शून्य) अणु
			/* put the command back on the queue */
			cmd->host_scribble = (व्योम *) ms->request_q;
			अगर (ms->request_q == शून्य)
				ms->request_qtail = cmd;
			ms->request_q = cmd;
			tp = &ms->tgts[cmd->device->id];
			tp->current_req = शून्य;
		पूर्ण
		अवरोध;
	हाल busमुक्तing:
		ms->phase = reselecting;
		mesh_करोne(ms, 0);
		अवरोध;
	हाल disconnecting:
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "mesh: reselected in phase %d/%d tgt %d\n",
		       ms->msgphase, ms->phase, ms->conn_tgt);
		dumplog(ms, ms->conn_tgt);
		dumpslog(ms);
	पूर्ण

	अगर (ms->dma_started) अणु
		prपूर्णांकk(KERN_ERR "mesh: reselected with DMA started !\n");
		halt_dma(ms);
	पूर्ण
	ms->current_req = शून्य;
	ms->phase = dataing;
	ms->msgphase = msg_in;
	ms->n_msgout = 0;
	ms->last_n_msgout = 0;
	prev = ms->conn_tgt;

	/*
	 * We seem to get पातive reselections someबार.
	 */
	जबतक ((in_8(&mr->bus_status1) & BS1_BSY) == 0) अणु
		अटल पूर्णांक mesh_पातed_resels;
		mesh_पातed_resels++;
		out_8(&mr->पूर्णांकerrupt, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
		mesh_flush_io(mr);
		udelay(1);
		out_8(&mr->sequence, SEQ_ENBRESEL);
		mesh_flush_io(mr);
		udelay(5);
		dlog(ms, "extra resel err/exc/fc = %.6x",
		     MKWORD(0, mr->error, mr->exception, mr->fअगरo_count));
	पूर्ण
	out_8(&mr->पूर्णांकerrupt, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
       	mesh_flush_io(mr);
	udelay(1);
	out_8(&mr->sequence, SEQ_ENBRESEL);
       	mesh_flush_io(mr);
	udelay(1);
	out_8(&mr->sync_params, ASYNC_PARAMS);

	/*
	 * Find out who reselected us.
	 */
	अगर (in_8(&mr->fअगरo_count) == 0) अणु
		prपूर्णांकk(KERN_ERR "mesh: reselection but nothing in fifo?\n");
		ms->conn_tgt = ms->host->this_id;
		जाओ bogus;
	पूर्ण
	/* get the last byte in the fअगरo */
	करो अणु
		b = in_8(&mr->fअगरo);
		dlog(ms, "reseldata %x", b);
	पूर्ण जबतक (in_8(&mr->fअगरo_count));
	क्रम (t = 0; t < 8; ++t)
		अगर ((b & (1 << t)) != 0 && t != ms->host->this_id)
			अवरोध;
	अगर (b != (1 << t) + (1 << ms->host->this_id)) अणु
		prपूर्णांकk(KERN_ERR "mesh: bad reselection data %x\n", b);
		ms->conn_tgt = ms->host->this_id;
		जाओ bogus;
	पूर्ण


	/*
	 * Set up to जारी with that target's transfer.
	 */
	ms->conn_tgt = t;
	tp = &ms->tgts[t];
	out_8(&mr->sync_params, tp->sync_params);
	अगर (ALLOW_DEBUG(t)) अणु
		prपूर्णांकk(KERN_DEBUG "mesh: reselected by target %d\n", t);
		prपूर्णांकk(KERN_DEBUG "mesh: saved_ptr=%x goes_out=%d cmd=%p\n",
		       tp->saved_ptr, tp->data_goes_out, tp->current_req);
	पूर्ण
	ms->current_req = tp->current_req;
	अगर (tp->current_req == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mesh: reselected by tgt %d but no cmd!\n", t);
		जाओ bogus;
	पूर्ण
	ms->data_ptr = tp->saved_ptr;
	dlog(ms, "resel prev tgt=%d", prev);
	dlog(ms, "resel err/exc=%.4x", MKWORD(0, 0, mr->error, mr->exception));
	start_phase(ms);
	वापस;

bogus:
	dumplog(ms, ms->conn_tgt);
	dumpslog(ms);
	ms->data_ptr = 0;
	ms->पातing = 1;
	start_phase(ms);
पूर्ण

अटल व्योम करो_पात(काष्ठा mesh_state *ms)
अणु
	ms->msgout[0] = ABORT;
	ms->n_msgout = 1;
	ms->पातing = 1;
	ms->stat = DID_ABORT;
	dlog(ms, "abort", 0);
पूर्ण

अटल व्योम handle_reset(काष्ठा mesh_state *ms)
अणु
	पूर्णांक tgt;
	काष्ठा mesh_target *tp;
	काष्ठा scsi_cmnd *cmd;
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;

	क्रम (tgt = 0; tgt < 8; ++tgt) अणु
		tp = &ms->tgts[tgt];
		अगर ((cmd = tp->current_req) != शून्य) अणु
			cmd->result = DID_RESET << 16;
			tp->current_req = शून्य;
			mesh_completed(ms, cmd);
		पूर्ण
		ms->tgts[tgt].sdtr_state = करो_sdtr;
		ms->tgts[tgt].sync_params = ASYNC_PARAMS;
	पूर्ण
	ms->current_req = शून्य;
	जबतक ((cmd = ms->request_q) != शून्य) अणु
		ms->request_q = (काष्ठा scsi_cmnd *) cmd->host_scribble;
		cmd->result = DID_RESET << 16;
		mesh_completed(ms, cmd);
	पूर्ण
	ms->phase = idle;
	ms->msgphase = msg_none;
	out_8(&mr->पूर्णांकerrupt, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
	out_8(&mr->sequence, SEQ_FLUSHFIFO);
       	mesh_flush_io(mr);
	udelay(1);
	out_8(&mr->sync_params, ASYNC_PARAMS);
	out_8(&mr->sequence, SEQ_ENBRESEL);
पूर्ण

अटल irqवापस_t करो_mesh_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mesh_state *ms = dev_id;
	काष्ठा Scsi_Host *dev = ms->host;
	
	spin_lock_irqsave(dev->host_lock, flags);
	mesh_पूर्णांकerrupt(ms);
	spin_unlock_irqrestore(dev->host_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम handle_error(काष्ठा mesh_state *ms)
अणु
	पूर्णांक err, exc, count;
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;

	err = in_8(&mr->error);
	exc = in_8(&mr->exception);
	out_8(&mr->पूर्णांकerrupt, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
	dlog(ms, "error err/exc/fc/cl=%.8x",
	     MKWORD(err, exc, mr->fअगरo_count, mr->count_lo));
	अगर (err & ERR_SCSIRESET) अणु
		/* SCSI bus was reset */
		prपूर्णांकk(KERN_INFO "mesh: SCSI bus reset detected: "
		       "waiting for end...");
		जबतक ((in_8(&mr->bus_status1) & BS1_RST) != 0)
			udelay(1);
		prपूर्णांकk("done\n");
		अगर (ms->dma_started)
			halt_dma(ms);
		handle_reset(ms);
		/* request_q is empty, no poपूर्णांक in mesh_start() */
		वापस;
	पूर्ण
	अगर (err & ERR_UNEXPDISC) अणु
		/* Unexpected disconnect */
		अगर (exc & EXC_RESELECTED) अणु
			reselected(ms);
			वापस;
		पूर्ण
		अगर (!ms->पातing) अणु
			prपूर्णांकk(KERN_WARNING "mesh: target %d aborted\n",
			       ms->conn_tgt);
			dumplog(ms, ms->conn_tgt);
			dumpslog(ms);
		पूर्ण
		out_8(&mr->पूर्णांकerrupt, INT_CMDDONE);
		ms->stat = DID_ABORT;
		mesh_करोne(ms, 1);
		वापस;
	पूर्ण
	अगर (err & ERR_PARITY) अणु
		अगर (ms->msgphase == msg_in) अणु
			prपूर्णांकk(KERN_ERR "mesh: msg parity error, target %d\n",
			       ms->conn_tgt);
			ms->msgout[0] = MSG_PARITY_ERROR;
			ms->n_msgout = 1;
			ms->msgphase = msg_in_bad;
			cmd_complete(ms);
			वापस;
		पूर्ण
		अगर (ms->stat == DID_OK) अणु
			prपूर्णांकk(KERN_ERR "mesh: parity error, target %d\n",
			       ms->conn_tgt);
			ms->stat = DID_PARITY;
		पूर्ण
		count = (mr->count_hi << 8) + mr->count_lo;
		अगर (count == 0) अणु
			cmd_complete(ms);
		पूर्ण अन्यथा अणु
			/* reissue the data transfer command */
			out_8(&mr->sequence, mr->sequence);
		पूर्ण
		वापस;
	पूर्ण
	अगर (err & ERR_SEQERR) अणु
		अगर (exc & EXC_RESELECTED) अणु
			/* This can happen अगर we issue a command to
			   get the bus just after the target reselects us. */
			अटल पूर्णांक mesh_resel_seqerr;
			mesh_resel_seqerr++;
			reselected(ms);
			वापस;
		पूर्ण
		अगर (exc == EXC_PHASEMM) अणु
			अटल पूर्णांक mesh_phasemm_seqerr;
			mesh_phasemm_seqerr++;
			phase_mismatch(ms);
			वापस;
		पूर्ण
		prपूर्णांकk(KERN_ERR "mesh: sequence error (err=%x exc=%x)\n",
		       err, exc);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "mesh: unknown error %x (exc=%x)\n", err, exc);
	पूर्ण
	mesh_dump_regs(ms);
	dumplog(ms, ms->conn_tgt);
	अगर (ms->phase > selecting && (in_8(&mr->bus_status1) & BS1_BSY)) अणु
		/* try to करो what the target wants */
		करो_पात(ms);
		phase_mismatch(ms);
		वापस;
	पूर्ण
	ms->stat = DID_ERROR;
	mesh_करोne(ms, 1);
पूर्ण

अटल व्योम handle_exception(काष्ठा mesh_state *ms)
अणु
	पूर्णांक exc;
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;

	exc = in_8(&mr->exception);
	out_8(&mr->पूर्णांकerrupt, INT_EXCEPTION | INT_CMDDONE);
	अगर (exc & EXC_RESELECTED) अणु
		अटल पूर्णांक mesh_resel_exc;
		mesh_resel_exc++;
		reselected(ms);
	पूर्ण अन्यथा अगर (exc == EXC_ARBLOST) अणु
		prपूर्णांकk(KERN_DEBUG "mesh: lost arbitration\n");
		ms->stat = DID_BUS_BUSY;
		mesh_करोne(ms, 1);
	पूर्ण अन्यथा अगर (exc == EXC_SELTO) अणु
		/* selection समयd out */
		ms->stat = DID_BAD_TARGET;
		mesh_करोne(ms, 1);
	पूर्ण अन्यथा अगर (exc == EXC_PHASEMM) अणु
		/* target wants to करो something dअगरferent:
		   find out what it wants and करो it. */
		phase_mismatch(ms);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "mesh: can't cope with exception %x\n", exc);
		mesh_dump_regs(ms);
		dumplog(ms, ms->conn_tgt);
		करो_पात(ms);
		phase_mismatch(ms);
	पूर्ण
पूर्ण

अटल व्योम handle_msgin(काष्ठा mesh_state *ms)
अणु
	पूर्णांक i, code;
	काष्ठा scsi_cmnd *cmd = ms->current_req;
	काष्ठा mesh_target *tp = &ms->tgts[ms->conn_tgt];

	अगर (ms->n_msgin == 0)
		वापस;
	code = ms->msgin[0];
	अगर (ALLOW_DEBUG(ms->conn_tgt)) अणु
		prपूर्णांकk(KERN_DEBUG "got %d message bytes:", ms->n_msgin);
		क्रम (i = 0; i < ms->n_msgin; ++i)
			prपूर्णांकk(" %x", ms->msgin[i]);
		prपूर्णांकk("\n");
	पूर्ण
	dlog(ms, "msgin msg=%.8x",
	     MKWORD(ms->n_msgin, code, ms->msgin[1], ms->msgin[2]));

	ms->expect_reply = 0;
	ms->n_msgout = 0;
	अगर (ms->n_msgin < msgin_length(ms))
		जाओ reject;
	अगर (cmd)
		cmd->SCp.Message = code;
	चयन (code) अणु
	हाल COMMAND_COMPLETE:
		अवरोध;
	हाल EXTENDED_MESSAGE:
		चयन (ms->msgin[2]) अणु
		हाल EXTENDED_MODIFY_DATA_POINTER:
			ms->data_ptr += (ms->msgin[3] << 24) + ms->msgin[6]
				+ (ms->msgin[4] << 16) + (ms->msgin[5] << 8);
			अवरोध;
		हाल EXTENDED_SDTR:
			अगर (tp->sdtr_state != sdtr_sent) अणु
				/* reply with an SDTR */
				add_sdtr_msg(ms);
				/* limit period to at least his value,
				   offset to no more than his */
				अगर (ms->msgout[3] < ms->msgin[3])
					ms->msgout[3] = ms->msgin[3];
				अगर (ms->msgout[4] > ms->msgin[4])
					ms->msgout[4] = ms->msgin[4];
				set_sdtr(ms, ms->msgout[3], ms->msgout[4]);
				ms->msgphase = msg_out;
			पूर्ण अन्यथा अणु
				set_sdtr(ms, ms->msgin[3], ms->msgin[4]);
			पूर्ण
			अवरोध;
		शेष:
			जाओ reject;
		पूर्ण
		अवरोध;
	हाल SAVE_POINTERS:
		tp->saved_ptr = ms->data_ptr;
		अवरोध;
	हाल RESTORE_POINTERS:
		ms->data_ptr = tp->saved_ptr;
		अवरोध;
	हाल DISCONNECT:
		ms->phase = disconnecting;
		अवरोध;
	हाल ABORT:
		अवरोध;
	हाल MESSAGE_REJECT:
		अगर (tp->sdtr_state == sdtr_sent)
			set_sdtr(ms, 0, 0);
		अवरोध;
	हाल NOP:
		अवरोध;
	शेष:
		अगर (IDENTIFY_BASE <= code && code <= IDENTIFY_BASE + 7) अणु
			अगर (cmd == शून्य) अणु
				करो_पात(ms);
				ms->msgphase = msg_out;
			पूर्ण अन्यथा अगर (code != cmd->device->lun + IDENTIFY_BASE) अणु
				prपूर्णांकk(KERN_WARNING "mesh: lun mismatch "
				       "(%d != %llu) on reselection from "
				       "target %d\n", code - IDENTIFY_BASE,
				       cmd->device->lun, ms->conn_tgt);
			पूर्ण
			अवरोध;
		पूर्ण
		जाओ reject;
	पूर्ण
	वापस;

 reject:
	prपूर्णांकk(KERN_WARNING "mesh: rejecting message from target %d:",
	       ms->conn_tgt);
	क्रम (i = 0; i < ms->n_msgin; ++i)
		prपूर्णांकk(" %x", ms->msgin[i]);
	prपूर्णांकk("\n");
	ms->msgout[0] = MESSAGE_REJECT;
	ms->n_msgout = 1;
	ms->msgphase = msg_out;
पूर्ण

/*
 * Set up DMA commands क्रम transferring data.
 */
अटल व्योम set_dma_cmds(काष्ठा mesh_state *ms, काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक i, dma_cmd, total, off, dtot;
	काष्ठा scatterlist *scl;
	काष्ठा dbdma_cmd *dcmds;

	dma_cmd = ms->tgts[ms->conn_tgt].data_goes_out?
		OUTPUT_MORE: INPUT_MORE;
	dcmds = ms->dma_cmds;
	dtot = 0;
	अगर (cmd) अणु
		पूर्णांक nseg;

		cmd->SCp.this_residual = scsi_bufflen(cmd);

		nseg = scsi_dma_map(cmd);
		BUG_ON(nseg < 0);

		अगर (nseg) अणु
			total = 0;
			off = ms->data_ptr;

			scsi_क्रम_each_sg(cmd, scl, nseg, i) अणु
				u32 dma_addr = sg_dma_address(scl);
				u32 dma_len = sg_dma_len(scl);
				
				total += scl->length;
				अगर (off >= dma_len) अणु
					off -= dma_len;
					जारी;
				पूर्ण
				अगर (dma_len > 0xffff)
					panic("mesh: scatterlist element >= 64k");
				dcmds->req_count = cpu_to_le16(dma_len - off);
				dcmds->command = cpu_to_le16(dma_cmd);
				dcmds->phy_addr = cpu_to_le32(dma_addr + off);
				dcmds->xfer_status = 0;
				++dcmds;
				dtot += dma_len - off;
				off = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (dtot == 0) अणु
		/* Either the target has overrun our buffer,
		   or the caller didn't provide a buffer. */
		अटल अक्षर mesh_extra_buf[64];

		dtot = माप(mesh_extra_buf);
		dcmds->req_count = cpu_to_le16(dtot);
		dcmds->phy_addr = cpu_to_le32(virt_to_phys(mesh_extra_buf));
		dcmds->xfer_status = 0;
		++dcmds;
	पूर्ण
	dma_cmd += OUTPUT_LAST - OUTPUT_MORE;
	dcmds[-1].command = cpu_to_le16(dma_cmd);
	स_रखो(dcmds, 0, माप(*dcmds));
	dcmds->command = cpu_to_le16(DBDMA_STOP);
	ms->dma_count = dtot;
पूर्ण

अटल व्योम halt_dma(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा dbdma_regs __iomem *md = ms->dma;
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	काष्ठा scsi_cmnd *cmd = ms->current_req;
	पूर्णांक t, nb;

	अगर (!ms->tgts[ms->conn_tgt].data_goes_out) अणु
		/* रुको a little जबतक until the fअगरo drains */
		t = 50;
		जबतक (t > 0 && in_8(&mr->fअगरo_count) != 0
		       && (in_le32(&md->status) & ACTIVE) != 0) अणु
			--t;
			udelay(1);
		पूर्ण
	पूर्ण
	out_le32(&md->control, RUN << 16);	/* turn off RUN bit */
	nb = (mr->count_hi << 8) + mr->count_lo;
	dlog(ms, "halt_dma fc/count=%.6x",
	     MKWORD(0, mr->fअगरo_count, 0, nb));
	अगर (ms->tgts[ms->conn_tgt].data_goes_out)
		nb += mr->fअगरo_count;
	/* nb is the number of bytes not yet transferred
	   to/from the target. */
	ms->data_ptr -= nb;
	dlog(ms, "data_ptr %x", ms->data_ptr);
	अगर (ms->data_ptr < 0) अणु
		prपूर्णांकk(KERN_ERR "mesh: halt_dma: data_ptr=%d (nb=%d, ms=%p)\n",
		       ms->data_ptr, nb, ms);
		ms->data_ptr = 0;
#अगर_घोषित MESH_DBG
		dumplog(ms, ms->conn_tgt);
		dumpslog(ms);
#पूर्ण_अगर /* MESH_DBG */
	पूर्ण अन्यथा अगर (cmd && scsi_bufflen(cmd) &&
		   ms->data_ptr > scsi_bufflen(cmd)) अणु
		prपूर्णांकk(KERN_DEBUG "mesh: target %d overrun, "
		       "data_ptr=%x total=%x goes_out=%d\n",
		       ms->conn_tgt, ms->data_ptr, scsi_bufflen(cmd),
		       ms->tgts[ms->conn_tgt].data_goes_out);
	पूर्ण
	अगर (cmd)
		scsi_dma_unmap(cmd);
	ms->dma_started = 0;
पूर्ण

अटल व्योम phase_mismatch(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	पूर्णांक phase;

	dlog(ms, "phasemm ch/cl/seq/fc=%.8x",
	     MKWORD(mr->count_hi, mr->count_lo, mr->sequence, mr->fअगरo_count));
	phase = in_8(&mr->bus_status0) & BS0_PHASE;
	अगर (ms->msgphase == msg_out_xxx && phase == BP_MSGOUT) अणु
		/* output the last byte of the message, without ATN */
		out_8(&mr->count_lo, 1);
		out_8(&mr->sequence, SEQ_MSGOUT + use_active_neg);
		mesh_flush_io(mr);
		udelay(1);
		out_8(&mr->fअगरo, ms->msgout[ms->n_msgout-1]);
		ms->msgphase = msg_out_last;
		वापस;
	पूर्ण

	अगर (ms->msgphase == msg_in) अणु
		get_msgin(ms);
		अगर (ms->n_msgin)
			handle_msgin(ms);
	पूर्ण

	अगर (ms->dma_started)
		halt_dma(ms);
	अगर (mr->fअगरo_count) अणु
		out_8(&mr->sequence, SEQ_FLUSHFIFO);
		mesh_flush_io(mr);
		udelay(1);
	पूर्ण

	ms->msgphase = msg_none;
	चयन (phase) अणु
	हाल BP_DATAIN:
		ms->tgts[ms->conn_tgt].data_goes_out = 0;
		ms->phase = dataing;
		अवरोध;
	हाल BP_DATAOUT:
		ms->tgts[ms->conn_tgt].data_goes_out = 1;
		ms->phase = dataing;
		अवरोध;
	हाल BP_COMMAND:
		ms->phase = commanding;
		अवरोध;
	हाल BP_STATUS:
		ms->phase = statusing;
		अवरोध;
	हाल BP_MSGIN:
		ms->msgphase = msg_in;
		ms->n_msgin = 0;
		अवरोध;
	हाल BP_MSGOUT:
		ms->msgphase = msg_out;
		अगर (ms->n_msgout == 0) अणु
			अगर (ms->पातing) अणु
				करो_पात(ms);
			पूर्ण अन्यथा अणु
				अगर (ms->last_n_msgout == 0) अणु
					prपूर्णांकk(KERN_DEBUG
					       "mesh: no msg to repeat\n");
					ms->msgout[0] = NOP;
					ms->last_n_msgout = 1;
				पूर्ण
				ms->n_msgout = ms->last_n_msgout;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "mesh: unknown scsi phase %x\n", phase);
		ms->stat = DID_ERROR;
		mesh_करोne(ms, 1);
		वापस;
	पूर्ण

	start_phase(ms);
पूर्ण

अटल व्योम cmd_complete(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	काष्ठा scsi_cmnd *cmd = ms->current_req;
	काष्ठा mesh_target *tp = &ms->tgts[ms->conn_tgt];
	पूर्णांक seq, n, t;

	dlog(ms, "cmd_complete fc=%x", mr->fअगरo_count);
	seq = use_active_neg + (ms->n_msgout? SEQ_ATN: 0);
	चयन (ms->msgphase) अणु
	हाल msg_out_xxx:
		/* huh?  we expected a phase mismatch */
		ms->n_msgin = 0;
		ms->msgphase = msg_in;
		fallthrough;

	हाल msg_in:
		/* should have some message bytes in fअगरo */
		get_msgin(ms);
		n = msgin_length(ms);
		अगर (ms->n_msgin < n) अणु
			out_8(&mr->count_lo, n - ms->n_msgin);
			out_8(&mr->sequence, SEQ_MSGIN + seq);
		पूर्ण अन्यथा अणु
			ms->msgphase = msg_none;
			handle_msgin(ms);
			start_phase(ms);
		पूर्ण
		अवरोध;

	हाल msg_in_bad:
		out_8(&mr->sequence, SEQ_FLUSHFIFO);
		mesh_flush_io(mr);
		udelay(1);
		out_8(&mr->count_lo, 1);
		out_8(&mr->sequence, SEQ_MSGIN + SEQ_ATN + use_active_neg);
		अवरोध;

	हाल msg_out:
		/*
		 * To get the right timing on ATN wrt ACK, we have
		 * to get the MESH to drop ACK, रुको until REQ माला_लो
		 * निश्चितed, then drop ATN.  To करो this we first
		 * issue a SEQ_MSGOUT with ATN and रुको क्रम REQ,
		 * then change the command to a SEQ_MSGOUT w/o ATN.
		 * If we करोn't see REQ in a reasonable समय, we
		 * change the command to SEQ_MSGIN with ATN,
		 * रुको क्रम the phase mismatch पूर्णांकerrupt, then
		 * issue the SEQ_MSGOUT without ATN.
		 */
		out_8(&mr->count_lo, 1);
		out_8(&mr->sequence, SEQ_MSGOUT + use_active_neg + SEQ_ATN);
		t = 30;		/* रुको up to 30us */
		जबतक ((in_8(&mr->bus_status0) & BS0_REQ) == 0 && --t >= 0)
			udelay(1);
		dlog(ms, "last_mbyte err/exc/fc/cl=%.8x",
		     MKWORD(mr->error, mr->exception,
			    mr->fअगरo_count, mr->count_lo));
		अगर (in_8(&mr->पूर्णांकerrupt) & (INT_ERROR | INT_EXCEPTION)) अणु
			/* whoops, target didn't करो what we expected */
			ms->last_n_msgout = ms->n_msgout;
			ms->n_msgout = 0;
			अगर (in_8(&mr->पूर्णांकerrupt) & INT_ERROR) अणु
				prपूर्णांकk(KERN_ERR "mesh: error %x in msg_out\n",
				       in_8(&mr->error));
				handle_error(ms);
				वापस;
			पूर्ण
			अगर (in_8(&mr->exception) != EXC_PHASEMM)
				prपूर्णांकk(KERN_ERR "mesh: exc %x in msg_out\n",
				       in_8(&mr->exception));
			अन्यथा
				prपूर्णांकk(KERN_DEBUG "mesh: bs0=%x in msg_out\n",
				       in_8(&mr->bus_status0));
			handle_exception(ms);
			वापस;
		पूर्ण
		अगर (in_8(&mr->bus_status0) & BS0_REQ) अणु
			out_8(&mr->sequence, SEQ_MSGOUT + use_active_neg);
			mesh_flush_io(mr);
			udelay(1);
			out_8(&mr->fअगरo, ms->msgout[ms->n_msgout-1]);
			ms->msgphase = msg_out_last;
		पूर्ण अन्यथा अणु
			out_8(&mr->sequence, SEQ_MSGIN + use_active_neg + SEQ_ATN);
			ms->msgphase = msg_out_xxx;
		पूर्ण
		अवरोध;

	हाल msg_out_last:
		ms->last_n_msgout = ms->n_msgout;
		ms->n_msgout = 0;
		ms->msgphase = ms->expect_reply? msg_in: msg_none;
		start_phase(ms);
		अवरोध;

	हाल msg_none:
		चयन (ms->phase) अणु
		हाल idle:
			prपूर्णांकk(KERN_ERR "mesh: interrupt in idle phase?\n");
			dumpslog(ms);
			वापस;
		हाल selecting:
			dlog(ms, "Selecting phase at command completion",0);
			ms->msgout[0] = IDENTIFY(ALLOW_RESEL(ms->conn_tgt),
						 (cmd? cmd->device->lun: 0));
			ms->n_msgout = 1;
			ms->expect_reply = 0;
			अगर (ms->पातing) अणु
				ms->msgout[0] = ABORT;
				ms->n_msgout++;
			पूर्ण अन्यथा अगर (tp->sdtr_state == करो_sdtr) अणु
				/* add SDTR message */
				add_sdtr_msg(ms);
				ms->expect_reply = 1;
				tp->sdtr_state = sdtr_sent;
			पूर्ण
			ms->msgphase = msg_out;
			/*
			 * We need to रुको क्रम REQ beक्रमe dropping ATN.
			 * We रुको क्रम at most 30us, then fall back to
			 * a scheme where we issue a SEQ_COMMAND with ATN,
			 * which will give us a phase mismatch पूर्णांकerrupt
			 * when REQ करोes come, and then we send the message.
			 */
			t = 230;		/* रुको up to 230us */
			जबतक ((in_8(&mr->bus_status0) & BS0_REQ) == 0) अणु
				अगर (--t < 0) अणु
					dlog(ms, "impatient for req", ms->n_msgout);
					ms->msgphase = msg_none;
					अवरोध;
				पूर्ण
				udelay(1);
			पूर्ण
			अवरोध;
		हाल dataing:
			अगर (ms->dma_count != 0) अणु
				start_phase(ms);
				वापस;
			पूर्ण
			/*
			 * We can get a phase mismatch here अगर the target
			 * changes to the status phase, even though we have
			 * had a command complete पूर्णांकerrupt.  Then, अगर we
			 * issue the SEQ_STATUS command, we'll get a sequence
			 * error पूर्णांकerrupt.  Which isn't so bad except that
			 * occasionally the mesh actually executes the
			 * SEQ_STATUS *as well as* giving us the sequence
			 * error and phase mismatch exception.
			 */
			out_8(&mr->sequence, 0);
			out_8(&mr->पूर्णांकerrupt,
			      INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
			halt_dma(ms);
			अवरोध;
		हाल statusing:
			अगर (cmd) अणु
				cmd->SCp.Status = mr->fअगरo;
				अगर (DEBUG_TARGET(cmd))
					prपूर्णांकk(KERN_DEBUG "mesh: status is %x\n",
					       cmd->SCp.Status);
			पूर्ण
			ms->msgphase = msg_in;
			अवरोध;
		हाल busमुक्तing:
			mesh_करोne(ms, 1);
			वापस;
		हाल disconnecting:
			ms->current_req = शून्य;
			ms->phase = idle;
			mesh_start(ms);
			वापस;
		शेष:
			अवरोध;
		पूर्ण
		++ms->phase;
		start_phase(ms);
		अवरोध;
	पूर्ण
पूर्ण


/*
 * Called by midlayer with host locked to queue a new
 * request
 */
अटल पूर्णांक mesh_queue_lck(काष्ठा scsi_cmnd *cmd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा mesh_state *ms;

	cmd->scsi_करोne = करोne;
	cmd->host_scribble = शून्य;

	ms = (काष्ठा mesh_state *) cmd->device->host->hostdata;

	अगर (ms->request_q == शून्य)
		ms->request_q = cmd;
	अन्यथा
		ms->request_qtail->host_scribble = (व्योम *) cmd;
	ms->request_qtail = cmd;

	अगर (ms->phase == idle)
		mesh_start(ms);

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(mesh_queue)

/*
 * Called to handle पूर्णांकerrupts, either call by the पूर्णांकerrupt
 * handler (करो_mesh_पूर्णांकerrupt) or by other functions in
 * exceptional circumstances
 */
अटल व्योम mesh_पूर्णांकerrupt(काष्ठा mesh_state *ms)
अणु
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	पूर्णांक पूर्णांकr;

#अगर 0
	अगर (ALLOW_DEBUG(ms->conn_tgt))
		prपूर्णांकk(KERN_DEBUG "mesh_intr, bs0=%x int=%x exc=%x err=%x "
		       "phase=%d msgphase=%d\n", mr->bus_status0,
		       mr->पूर्णांकerrupt, mr->exception, mr->error,
		       ms->phase, ms->msgphase);
#पूर्ण_अगर
	जबतक ((पूर्णांकr = in_8(&mr->पूर्णांकerrupt)) != 0) अणु
		dlog(ms, "interrupt intr/err/exc/seq=%.8x", 
		     MKWORD(पूर्णांकr, mr->error, mr->exception, mr->sequence));
		अगर (पूर्णांकr & INT_ERROR) अणु
			handle_error(ms);
		पूर्ण अन्यथा अगर (पूर्णांकr & INT_EXCEPTION) अणु
			handle_exception(ms);
		पूर्ण अन्यथा अगर (पूर्णांकr & INT_CMDDONE) अणु
			out_8(&mr->पूर्णांकerrupt, INT_CMDDONE);
			cmd_complete(ms);
		पूर्ण
	पूर्ण
पूर्ण

/* Toकरो: here we can at least try to हटाओ the command from the
 * queue अगर it isn't connected yet, and क्रम pending command, निश्चित
 * ATN until the bus माला_लो मुक्तd.
 */
अटल पूर्णांक mesh_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा mesh_state *ms = (काष्ठा mesh_state *) cmd->device->host->hostdata;

	prपूर्णांकk(KERN_DEBUG "mesh_abort(%p)\n", cmd);
	mesh_dump_regs(ms);
	dumplog(ms, cmd->device->id);
	dumpslog(ms);
	वापस FAILED;
पूर्ण

/*
 * Called by the midlayer with the lock held to reset the
 * SCSI host and bus.
 * The midlayer will रुको क्रम devices to come back, we करोn't need
 * to करो that ourselves
 */
अटल पूर्णांक mesh_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा mesh_state *ms = (काष्ठा mesh_state *) cmd->device->host->hostdata;
	अस्थिर काष्ठा mesh_regs __iomem *mr = ms->mesh;
	अस्थिर काष्ठा dbdma_regs __iomem *md = ms->dma;
	अचिन्हित दीर्घ flags;

	prपूर्णांकk(KERN_DEBUG "mesh_host_reset\n");

	spin_lock_irqsave(ms->host->host_lock, flags);

	अगर (ms->dma_started)
		halt_dma(ms);

	/* Reset the controller & dbdma channel */
	out_le32(&md->control, (RUN|PAUSE|FLUSH|WAKE) << 16);	/* stop dma */
	out_8(&mr->exception, 0xff);	/* clear all exception bits */
	out_8(&mr->error, 0xff);	/* clear all error bits */
	out_8(&mr->sequence, SEQ_RESETMESH);
       	mesh_flush_io(mr);
	udelay(1);
	out_8(&mr->पूर्णांकr_mask, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
	out_8(&mr->source_id, ms->host->this_id);
	out_8(&mr->sel_समयout, 25);	/* 250ms */
	out_8(&mr->sync_params, ASYNC_PARAMS);

	/* Reset the bus */
	out_8(&mr->bus_status1, BS1_RST);	/* निश्चित RST */
       	mesh_flush_io(mr);
	udelay(30);			/* leave it on क्रम >= 25us */
	out_8(&mr->bus_status1, 0);	/* negate RST */

	/* Complete pending commands */
	handle_reset(ms);
	
	spin_unlock_irqrestore(ms->host->host_lock, flags);
	वापस SUCCESS;
पूर्ण

अटल व्योम set_mesh_घातer(काष्ठा mesh_state *ms, पूर्णांक state)
अणु
	अगर (!machine_is(घातermac))
		वापस;
	अगर (state) अणु
		pmac_call_feature(PMAC_FTR_MESH_ENABLE, macio_get_of_node(ms->mdev), 0, 1);
		msleep(200);
	पूर्ण अन्यथा अणु
		pmac_call_feature(PMAC_FTR_MESH_ENABLE, macio_get_of_node(ms->mdev), 0, 0);
		msleep(10);
	पूर्ण
पूर्ण


#अगर_घोषित CONFIG_PM
अटल पूर्णांक mesh_suspend(काष्ठा macio_dev *mdev, pm_message_t mesg)
अणु
	काष्ठा mesh_state *ms = (काष्ठा mesh_state *)macio_get_drvdata(mdev);
	अचिन्हित दीर्घ flags;

	चयन (mesg.event) अणु
	हाल PM_EVENT_SUSPEND:
	हाल PM_EVENT_HIBERNATE:
	हाल PM_EVENT_FREEZE:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	अगर (ms->phase == sleeping)
		वापस 0;

	scsi_block_requests(ms->host);
	spin_lock_irqsave(ms->host->host_lock, flags);
	जबतक(ms->phase != idle) अणु
		spin_unlock_irqrestore(ms->host->host_lock, flags);
		msleep(10);
		spin_lock_irqsave(ms->host->host_lock, flags);
	पूर्ण
	ms->phase = sleeping;
	spin_unlock_irqrestore(ms->host->host_lock, flags);
	disable_irq(ms->meshपूर्णांकr);
	set_mesh_घातer(ms, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mesh_resume(काष्ठा macio_dev *mdev)
अणु
	काष्ठा mesh_state *ms = (काष्ठा mesh_state *)macio_get_drvdata(mdev);
	अचिन्हित दीर्घ flags;

	अगर (ms->phase != sleeping)
		वापस 0;

	set_mesh_घातer(ms, 1);
	mesh_init(ms);
	spin_lock_irqsave(ms->host->host_lock, flags);
	mesh_start(ms);
	spin_unlock_irqrestore(ms->host->host_lock, flags);
	enable_irq(ms->meshपूर्णांकr);
	scsi_unblock_requests(ms->host);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

/*
 * If we leave drives set क्रम synchronous transfers (especially
 * CDROMs), and reboot to MacOS, it माला_लो confused, poor thing.
 * So, on reboot we reset the SCSI bus.
 */
अटल पूर्णांक mesh_shutकरोwn(काष्ठा macio_dev *mdev)
अणु
	काष्ठा mesh_state *ms = (काष्ठा mesh_state *)macio_get_drvdata(mdev);
	अस्थिर काष्ठा mesh_regs __iomem *mr;
	अचिन्हित दीर्घ flags;

       	prपूर्णांकk(KERN_INFO "resetting MESH scsi bus(es)\n");
	spin_lock_irqsave(ms->host->host_lock, flags);
       	mr = ms->mesh;
	out_8(&mr->पूर्णांकr_mask, 0);
	out_8(&mr->पूर्णांकerrupt, INT_ERROR | INT_EXCEPTION | INT_CMDDONE);
	out_8(&mr->bus_status1, BS1_RST);
	mesh_flush_io(mr);
	udelay(30);
	out_8(&mr->bus_status1, 0);
	spin_unlock_irqrestore(ms->host->host_lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा mesh_ढाँचा = अणु
	.proc_name			= "mesh",
	.name				= "MESH",
	.queuecommand			= mesh_queue,
	.eh_पात_handler		= mesh_पात,
	.eh_host_reset_handler		= mesh_host_reset,
	.can_queue			= 20,
	.this_id			= 7,
	.sg_tablesize			= SG_ALL,
	.cmd_per_lun			= 2,
	.max_segment_size		= 65535,
पूर्ण;

अटल पूर्णांक mesh_probe(काष्ठा macio_dev *mdev, स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा device_node *mesh = macio_get_of_node(mdev);
	काष्ठा pci_dev* pdev = macio_get_pci_dev(mdev);
	पूर्णांक tgt, minper;
	स्थिर पूर्णांक *cfp;
	काष्ठा mesh_state *ms;
	काष्ठा Scsi_Host *mesh_host;
	व्योम *dma_cmd_space;
	dma_addr_t dma_cmd_bus;

	चयन (mdev->bus->chip->type) अणु
	हाल macio_heathrow:
	हाल macio_gatwick:
	हाल macio_paddington:
		use_active_neg = 0;
		अवरोध;
	शेष:
		use_active_neg = SEQ_ACTIVE_NEG;
	पूर्ण

	अगर (macio_resource_count(mdev) != 2 || macio_irq_count(mdev) != 2) अणु
       		prपूर्णांकk(KERN_ERR "mesh: expected 2 addrs and 2 intrs"
	       	       " (got %d,%d)\n", macio_resource_count(mdev),
		       macio_irq_count(mdev));
		वापस -ENODEV;
	पूर्ण

	अगर (macio_request_resources(mdev, "mesh") != 0) अणु
       		prपूर्णांकk(KERN_ERR "mesh: unable to request memory resources");
		वापस -EBUSY;
	पूर्ण
       	mesh_host = scsi_host_alloc(&mesh_ढाँचा, माप(काष्ठा mesh_state));
	अगर (mesh_host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mesh: couldn't register host");
		जाओ out_release;
	पूर्ण
	
	/* Old junk क्रम root discovery, that will die ultimately */
#अगर !defined(MODULE)
       	note_scsi_host(mesh, mesh_host);
#पूर्ण_अगर

	mesh_host->base = macio_resource_start(mdev, 0);
	mesh_host->irq = macio_irq(mdev, 0);
       	ms = (काष्ठा mesh_state *) mesh_host->hostdata;
	macio_set_drvdata(mdev, ms);
	ms->host = mesh_host;
	ms->mdev = mdev;
	ms->pdev = pdev;
	
	ms->mesh = ioremap(macio_resource_start(mdev, 0), 0x1000);
	अगर (ms->mesh == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mesh: can't map registers\n");
		जाओ out_मुक्त;
	पूर्ण		
	ms->dma = ioremap(macio_resource_start(mdev, 1), 0x1000);
	अगर (ms->dma == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mesh: can't map registers\n");
		iounmap(ms->mesh);
		जाओ out_मुक्त;
	पूर्ण

       	ms->meshपूर्णांकr = macio_irq(mdev, 0);
       	ms->dमुख्यtr = macio_irq(mdev, 1);

       	/* Space क्रम dma command list: +1 क्रम stop command,
       	 * +1 to allow क्रम aligning.
	 */
	ms->dma_cmd_size = (mesh_host->sg_tablesize + 2) * माप(काष्ठा dbdma_cmd);

	/* We use the PCI APIs क्रम now until the generic one माला_लो fixed
	 * enough or until we get some macio-specअगरic versions
	 */
	dma_cmd_space = dma_alloc_coherent(&macio_get_pci_dev(mdev)->dev,
					   ms->dma_cmd_size, &dma_cmd_bus,
					   GFP_KERNEL);
	अगर (dma_cmd_space == शून्य) अणु
		prपूर्णांकk(KERN_ERR "mesh: can't allocate DMA table\n");
		जाओ out_unmap;
	पूर्ण

	ms->dma_cmds = (काष्ठा dbdma_cmd *) DBDMA_ALIGN(dma_cmd_space);
       	ms->dma_cmd_space = dma_cmd_space;
	ms->dma_cmd_bus = dma_cmd_bus + ((अचिन्हित दीर्घ)ms->dma_cmds)
		- (अचिन्हित दीर्घ)dma_cmd_space;
	ms->current_req = शून्य;
       	क्रम (tgt = 0; tgt < 8; ++tgt) अणु
	       	ms->tgts[tgt].sdtr_state = करो_sdtr;
	       	ms->tgts[tgt].sync_params = ASYNC_PARAMS;
	       	ms->tgts[tgt].current_req = शून्य;
       	पूर्ण

	अगर ((cfp = of_get_property(mesh, "clock-frequency", शून्य)))
       		ms->clk_freq = *cfp;
	अन्यथा अणु
       		prपूर्णांकk(KERN_INFO "mesh: assuming 50MHz clock frequency\n");
	       	ms->clk_freq = 50000000;
       	पूर्ण

       	/* The maximum sync rate is घड़ी / 5; increase
       	 * mesh_sync_period अगर necessary.
	 */
	minper = 1000000000 / (ms->clk_freq / 5); /* ns */
	अगर (mesh_sync_period < minper)
		mesh_sync_period = minper;

	/* Power up the chip */
	set_mesh_घातer(ms, 1);

	/* Set it up */
       	mesh_init(ms);

	/* Request पूर्णांकerrupt */
       	अगर (request_irq(ms->meshपूर्णांकr, करो_mesh_पूर्णांकerrupt, 0, "MESH", ms)) अणु
	       	prपूर्णांकk(KERN_ERR "MESH: can't get irq %d\n", ms->meshपूर्णांकr);
		जाओ out_shutकरोwn;
	पूर्ण

	/* Add scsi host & scan */
	अगर (scsi_add_host(mesh_host, &mdev->ofdev.dev))
		जाओ out_release_irq;
	scsi_scan_host(mesh_host);

	वापस 0;

 out_release_irq:
	मुक्त_irq(ms->meshपूर्णांकr, ms);
 out_shutकरोwn:
	/* shutकरोwn & reset bus in हाल of error or macos can be confused
	 * at reboot अगर the bus was set to synchronous mode alपढ़ोy
	 */
	mesh_shutकरोwn(mdev);
	set_mesh_घातer(ms, 0);
	dma_मुक्त_coherent(&macio_get_pci_dev(mdev)->dev, ms->dma_cmd_size,
			    ms->dma_cmd_space, ms->dma_cmd_bus);
 out_unmap:
	iounmap(ms->dma);
	iounmap(ms->mesh);
 out_मुक्त:
	scsi_host_put(mesh_host);
 out_release:
	macio_release_resources(mdev);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक mesh_हटाओ(काष्ठा macio_dev *mdev)
अणु
	काष्ठा mesh_state *ms = (काष्ठा mesh_state *)macio_get_drvdata(mdev);
	काष्ठा Scsi_Host *mesh_host = ms->host;

	scsi_हटाओ_host(mesh_host);

	मुक्त_irq(ms->meshपूर्णांकr, ms);

	/* Reset scsi bus */
	mesh_shutकरोwn(mdev);

	/* Shut करोwn chip & termination */
	set_mesh_घातer(ms, 0);

	/* Unmap रेजिस्टरs & dma controller */
	iounmap(ms->mesh);
       	iounmap(ms->dma);

	/* Free DMA commands memory */
	dma_मुक्त_coherent(&macio_get_pci_dev(mdev)->dev, ms->dma_cmd_size,
			    ms->dma_cmd_space, ms->dma_cmd_bus);

	/* Release memory resources */
	macio_release_resources(mdev);

	scsi_host_put(mesh_host);

	वापस 0;
पूर्ण


अटल काष्ठा of_device_id mesh_match[] = 
अणु
	अणु
	.name 		= "mesh",
	पूर्ण,
	अणु
	.type		= "scsi",
	.compatible	= "chrp,mesh0"
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE (of, mesh_match);

अटल काष्ठा macio_driver mesh_driver = 
अणु
	.driver = अणु
		.name 		= "mesh",
		.owner		= THIS_MODULE,
		.of_match_table	= mesh_match,
	पूर्ण,
	.probe		= mesh_probe,
	.हटाओ		= mesh_हटाओ,
	.shutकरोwn	= mesh_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.suspend	= mesh_suspend,
	.resume		= mesh_resume,
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक __init init_mesh(व्योम)
अणु

	/* Calculate sync rate from module parameters */
	अगर (sync_rate > 10)
		sync_rate = 10;
	अगर (sync_rate > 0) अणु
		prपूर्णांकk(KERN_INFO "mesh: configured for synchronous %d MB/s\n", sync_rate);
		mesh_sync_period = 1000 / sync_rate;	/* ns */
		mesh_sync_offset = 15;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO "mesh: configured for asynchronous\n");

	वापस macio_रेजिस्टर_driver(&mesh_driver);
पूर्ण

अटल व्योम __निकास निकास_mesh(व्योम)
अणु
	वापस macio_unरेजिस्टर_driver(&mesh_driver);
पूर्ण

module_init(init_mesh);
module_निकास(निकास_mesh);
