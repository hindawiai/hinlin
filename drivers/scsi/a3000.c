<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>

#समावेश "scsi.h"
#समावेश "wd33c93.h"
#समावेश "a3000.h"


काष्ठा a3000_hostdata अणु
	काष्ठा WD33C93_hostdata wh;
	काष्ठा a3000_scsiregs *regs;
पूर्ण;

अटल irqवापस_t a3000_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा Scsi_Host *instance = data;
	काष्ठा a3000_hostdata *hdata = shost_priv(instance);
	अचिन्हित पूर्णांक status = hdata->regs->ISTR;
	अचिन्हित दीर्घ flags;

	अगर (!(status & ISTR_INT_P))
		वापस IRQ_NONE;
	अगर (status & ISTR_INTS) अणु
		spin_lock_irqsave(instance->host_lock, flags);
		wd33c93_पूर्णांकr(instance);
		spin_unlock_irqrestore(instance->host_lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण
	pr_warn("Non-serviced A3000 SCSI-interrupt? ISTR = %02x\n", status);
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक dma_setup(काष्ठा scsi_cmnd *cmd, पूर्णांक dir_in)
अणु
	काष्ठा Scsi_Host *instance = cmd->device->host;
	काष्ठा a3000_hostdata *hdata = shost_priv(instance);
	काष्ठा WD33C93_hostdata *wh = &hdata->wh;
	काष्ठा a3000_scsiregs *regs = hdata->regs;
	अचिन्हित लघु cntr = CNTR_PDMD | CNTR_INTEN;
	अचिन्हित दीर्घ addr = virt_to_bus(cmd->SCp.ptr);

	/*
	 * अगर the physical address has the wrong alignment, or अगर
	 * physical address is bad, or अगर it is a ग_लिखो and at the
	 * end of a physical memory chunk, then allocate a bounce
	 * buffer
	 */
	अगर (addr & A3000_XFER_MASK) अणु
		wh->dma_bounce_len = (cmd->SCp.this_residual + 511) & ~0x1ff;
		wh->dma_bounce_buffer = kदो_स्मृति(wh->dma_bounce_len,
						GFP_KERNEL);

		/* can't allocate memory; use PIO */
		अगर (!wh->dma_bounce_buffer) अणु
			wh->dma_bounce_len = 0;
			वापस 1;
		पूर्ण

		अगर (!dir_in) अणु
			/* copy to bounce buffer क्रम a ग_लिखो */
			स_नकल(wh->dma_bounce_buffer, cmd->SCp.ptr,
			       cmd->SCp.this_residual);
		पूर्ण

		addr = virt_to_bus(wh->dma_bounce_buffer);
	पूर्ण

	/* setup dma direction */
	अगर (!dir_in)
		cntr |= CNTR_Dसूची;

	/* remember direction */
	wh->dma_dir = dir_in;

	regs->CNTR = cntr;

	/* setup DMA *physical* address */
	regs->ACR = addr;

	अगर (dir_in) अणु
		/* invalidate any cache */
		cache_clear(addr, cmd->SCp.this_residual);
	पूर्ण अन्यथा अणु
		/* push any dirty cache */
		cache_push(addr, cmd->SCp.this_residual);
	पूर्ण

	/* start DMA */
	mb();			/* make sure setup is completed */
	regs->ST_DMA = 1;
	mb();			/* make sure DMA has started beक्रमe next IO */

	/* वापस success */
	वापस 0;
पूर्ण

अटल व्योम dma_stop(काष्ठा Scsi_Host *instance, काष्ठा scsi_cmnd *SCpnt,
		     पूर्णांक status)
अणु
	काष्ठा a3000_hostdata *hdata = shost_priv(instance);
	काष्ठा WD33C93_hostdata *wh = &hdata->wh;
	काष्ठा a3000_scsiregs *regs = hdata->regs;

	/* disable SCSI पूर्णांकerrupts */
	अचिन्हित लघु cntr = CNTR_PDMD;

	अगर (!wh->dma_dir)
		cntr |= CNTR_Dसूची;

	regs->CNTR = cntr;
	mb();			/* make sure CNTR is updated beक्रमe next IO */

	/* flush अगर we were पढ़ोing */
	अगर (wh->dma_dir) अणु
		regs->FLUSH = 1;
		mb();		/* करोn't allow prefetch */
		जबतक (!(regs->ISTR & ISTR_FE_FLG))
			barrier();
		mb();		/* no IO until FLUSH is करोne */
	पूर्ण

	/* clear a possible पूर्णांकerrupt */
	/* I think that this CINT is only necessary अगर you are
	 * using the terminal count features.   HM 7 Mar 1994
	 */
	regs->CINT = 1;

	/* stop DMA */
	regs->SP_DMA = 1;
	mb();			/* make sure DMA is stopped beक्रमe next IO */

	/* restore the CONTROL bits (minus the direction flag) */
	regs->CNTR = CNTR_PDMD | CNTR_INTEN;
	mb();			/* make sure CNTR is updated beक्रमe next IO */

	/* copy from a bounce buffer, अगर necessary */
	अगर (status && wh->dma_bounce_buffer) अणु
		अगर (SCpnt) अणु
			अगर (wh->dma_dir && SCpnt)
				स_नकल(SCpnt->SCp.ptr, wh->dma_bounce_buffer,
				       SCpnt->SCp.this_residual);
			kमुक्त(wh->dma_bounce_buffer);
			wh->dma_bounce_buffer = शून्य;
			wh->dma_bounce_len = 0;
		पूर्ण अन्यथा अणु
			kमुक्त(wh->dma_bounce_buffer);
			wh->dma_bounce_buffer = शून्य;
			wh->dma_bounce_len = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा scsi_host_ढाँचा amiga_a3000_scsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "Amiga 3000 built-in SCSI",
	.show_info		= wd33c93_show_info,
	.ग_लिखो_info		= wd33c93_ग_लिखो_info,
	.proc_name		= "A3000",
	.queuecommand		= wd33c93_queuecommand,
	.eh_पात_handler	= wd33c93_पात,
	.eh_host_reset_handler	= wd33c93_host_reset,
	.can_queue		= CAN_QUEUE,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= CMD_PER_LUN,
पूर्ण;

अटल पूर्णांक __init amiga_a3000_scsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा Scsi_Host *instance;
	पूर्णांक error;
	काष्ठा a3000_scsiregs *regs;
	wd33c93_regs wdregs;
	काष्ठा a3000_hostdata *hdata;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!request_mem_region(res->start, resource_size(res), "wd33c93"))
		वापस -EBUSY;

	instance = scsi_host_alloc(&amiga_a3000_scsi_ढाँचा,
				   माप(काष्ठा a3000_hostdata));
	अगर (!instance) अणु
		error = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	instance->irq = IRQ_AMIGA_PORTS;

	regs = ZTWO_VADDR(res->start);
	regs->DAWR = DAWR_A3000;

	wdregs.SASR = &regs->SASR;
	wdregs.SCMD = &regs->SCMD;

	hdata = shost_priv(instance);
	hdata->wh.no_sync = 0xff;
	hdata->wh.fast = 0;
	hdata->wh.dma_mode = CTRL_DMA;
	hdata->regs = regs;

	wd33c93_init(instance, wdregs, dma_setup, dma_stop, WD33C93_FS_12_15);
	error = request_irq(IRQ_AMIGA_PORTS, a3000_पूर्णांकr, IRQF_SHARED,
			    "A3000 SCSI", instance);
	अगर (error)
		जाओ fail_irq;

	regs->CNTR = CNTR_PDMD | CNTR_INTEN;

	error = scsi_add_host(instance, शून्य);
	अगर (error)
		जाओ fail_host;

	platक्रमm_set_drvdata(pdev, instance);

	scsi_scan_host(instance);
	वापस 0;

fail_host:
	मुक्त_irq(IRQ_AMIGA_PORTS, instance);
fail_irq:
	scsi_host_put(instance);
fail_alloc:
	release_mem_region(res->start, resource_size(res));
	वापस error;
पूर्ण

अटल पूर्णांक __निकास amiga_a3000_scsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *instance = platक्रमm_get_drvdata(pdev);
	काष्ठा a3000_hostdata *hdata = shost_priv(instance);
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	hdata->regs->CNTR = 0;
	scsi_हटाओ_host(instance);
	मुक्त_irq(IRQ_AMIGA_PORTS, instance);
	scsi_host_put(instance);
	release_mem_region(res->start, resource_size(res));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver amiga_a3000_scsi_driver = अणु
	.हटाओ = __निकास_p(amiga_a3000_scsi_हटाओ),
	.driver   = अणु
		.name	= "amiga-a3000-scsi",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(amiga_a3000_scsi_driver, amiga_a3000_scsi_probe);

MODULE_DESCRIPTION("Amiga 3000 built-in SCSI");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:amiga-a3000-scsi");
