<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/zorro.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>

#समावेश "scsi.h"
#समावेश "wd33c93.h"
#समावेश "a2091.h"


काष्ठा a2091_hostdata अणु
	काष्ठा WD33C93_hostdata wh;
	काष्ठा a2091_scsiregs *regs;
पूर्ण;

अटल irqवापस_t a2091_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा Scsi_Host *instance = data;
	काष्ठा a2091_hostdata *hdata = shost_priv(instance);
	अचिन्हित पूर्णांक status = hdata->regs->ISTR;
	अचिन्हित दीर्घ flags;

	अगर (!(status & (ISTR_INT_F | ISTR_INT_P)) || !(status & ISTR_INTS))
		वापस IRQ_NONE;

	spin_lock_irqsave(instance->host_lock, flags);
	wd33c93_पूर्णांकr(instance);
	spin_unlock_irqrestore(instance->host_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dma_setup(काष्ठा scsi_cmnd *cmd, पूर्णांक dir_in)
अणु
	काष्ठा Scsi_Host *instance = cmd->device->host;
	काष्ठा a2091_hostdata *hdata = shost_priv(instance);
	काष्ठा WD33C93_hostdata *wh = &hdata->wh;
	काष्ठा a2091_scsiregs *regs = hdata->regs;
	अचिन्हित लघु cntr = CNTR_PDMD | CNTR_INTEN;
	अचिन्हित दीर्घ addr = virt_to_bus(cmd->SCp.ptr);

	/* करोn't allow DMA अगर the physical address is bad */
	अगर (addr & A2091_XFER_MASK) अणु
		wh->dma_bounce_len = (cmd->SCp.this_residual + 511) & ~0x1ff;
		wh->dma_bounce_buffer = kदो_स्मृति(wh->dma_bounce_len,
						GFP_KERNEL);

		/* can't allocate memory; use PIO */
		अगर (!wh->dma_bounce_buffer) अणु
			wh->dma_bounce_len = 0;
			वापस 1;
		पूर्ण

		/* get the physical address of the bounce buffer */
		addr = virt_to_bus(wh->dma_bounce_buffer);

		/* the bounce buffer may not be in the first 16M of physmem */
		अगर (addr & A2091_XFER_MASK) अणु
			/* we could use chipmem... maybe later */
			kमुक्त(wh->dma_bounce_buffer);
			wh->dma_bounce_buffer = शून्य;
			wh->dma_bounce_len = 0;
			वापस 1;
		पूर्ण

		अगर (!dir_in) अणु
			/* copy to bounce buffer क्रम a ग_लिखो */
			स_नकल(wh->dma_bounce_buffer, cmd->SCp.ptr,
			       cmd->SCp.this_residual);
		पूर्ण
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
	regs->ST_DMA = 1;

	/* वापस success */
	वापस 0;
पूर्ण

अटल व्योम dma_stop(काष्ठा Scsi_Host *instance, काष्ठा scsi_cmnd *SCpnt,
		     पूर्णांक status)
अणु
	काष्ठा a2091_hostdata *hdata = shost_priv(instance);
	काष्ठा WD33C93_hostdata *wh = &hdata->wh;
	काष्ठा a2091_scsiregs *regs = hdata->regs;

	/* disable SCSI पूर्णांकerrupts */
	अचिन्हित लघु cntr = CNTR_PDMD;

	अगर (!wh->dma_dir)
		cntr |= CNTR_Dसूची;

	/* disable SCSI पूर्णांकerrupts */
	regs->CNTR = cntr;

	/* flush अगर we were पढ़ोing */
	अगर (wh->dma_dir) अणु
		regs->FLUSH = 1;
		जबतक (!(regs->ISTR & ISTR_FE_FLG))
			;
	पूर्ण

	/* clear a possible पूर्णांकerrupt */
	regs->CINT = 1;

	/* stop DMA */
	regs->SP_DMA = 1;

	/* restore the CONTROL bits (minus the direction flag) */
	regs->CNTR = CNTR_PDMD | CNTR_INTEN;

	/* copy from a bounce buffer, अगर necessary */
	अगर (status && wh->dma_bounce_buffer) अणु
		अगर (wh->dma_dir)
			स_नकल(SCpnt->SCp.ptr, wh->dma_bounce_buffer,
			       SCpnt->SCp.this_residual);
		kमुक्त(wh->dma_bounce_buffer);
		wh->dma_bounce_buffer = शून्य;
		wh->dma_bounce_len = 0;
	पूर्ण
पूर्ण

अटल काष्ठा scsi_host_ढाँचा a2091_scsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "Commodore A2091/A590 SCSI",
	.show_info		= wd33c93_show_info,
	.ग_लिखो_info		= wd33c93_ग_लिखो_info,
	.proc_name		= "A2901",
	.queuecommand		= wd33c93_queuecommand,
	.eh_पात_handler	= wd33c93_पात,
	.eh_host_reset_handler	= wd33c93_host_reset,
	.can_queue		= CAN_QUEUE,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= CMD_PER_LUN,
	.dma_boundary		= PAGE_SIZE - 1,
पूर्ण;

अटल पूर्णांक a2091_probe(काष्ठा zorro_dev *z, स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा Scsi_Host *instance;
	पूर्णांक error;
	काष्ठा a2091_scsiregs *regs;
	wd33c93_regs wdregs;
	काष्ठा a2091_hostdata *hdata;

	अगर (!request_mem_region(z->resource.start, 256, "wd33c93"))
		वापस -EBUSY;

	instance = scsi_host_alloc(&a2091_scsi_ढाँचा,
				   माप(काष्ठा a2091_hostdata));
	अगर (!instance) अणु
		error = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	instance->irq = IRQ_AMIGA_PORTS;
	instance->unique_id = z->slotaddr;

	regs = ZTWO_VADDR(z->resource.start);
	regs->DAWR = DAWR_A2091;

	wdregs.SASR = &regs->SASR;
	wdregs.SCMD = &regs->SCMD;

	hdata = shost_priv(instance);
	hdata->wh.no_sync = 0xff;
	hdata->wh.fast = 0;
	hdata->wh.dma_mode = CTRL_DMA;
	hdata->regs = regs;

	wd33c93_init(instance, wdregs, dma_setup, dma_stop, WD33C93_FS_8_10);
	error = request_irq(IRQ_AMIGA_PORTS, a2091_पूर्णांकr, IRQF_SHARED,
			    "A2091 SCSI", instance);
	अगर (error)
		जाओ fail_irq;

	regs->CNTR = CNTR_PDMD | CNTR_INTEN;

	error = scsi_add_host(instance, शून्य);
	अगर (error)
		जाओ fail_host;

	zorro_set_drvdata(z, instance);

	scsi_scan_host(instance);
	वापस 0;

fail_host:
	मुक्त_irq(IRQ_AMIGA_PORTS, instance);
fail_irq:
	scsi_host_put(instance);
fail_alloc:
	release_mem_region(z->resource.start, 256);
	वापस error;
पूर्ण

अटल व्योम a2091_हटाओ(काष्ठा zorro_dev *z)
अणु
	काष्ठा Scsi_Host *instance = zorro_get_drvdata(z);
	काष्ठा a2091_hostdata *hdata = shost_priv(instance);

	hdata->regs->CNTR = 0;
	scsi_हटाओ_host(instance);
	मुक्त_irq(IRQ_AMIGA_PORTS, instance);
	scsi_host_put(instance);
	release_mem_region(z->resource.start, 256);
पूर्ण

अटल काष्ठा zorro_device_id a2091_zorro_tbl[] = अणु
	अणु ZORRO_PROD_CBM_A590_A2091_1 पूर्ण,
	अणु ZORRO_PROD_CBM_A590_A2091_2 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, a2091_zorro_tbl);

अटल काष्ठा zorro_driver a2091_driver = अणु
	.name		= "a2091",
	.id_table	= a2091_zorro_tbl,
	.probe		= a2091_probe,
	.हटाओ		= a2091_हटाओ,
पूर्ण;

अटल पूर्णांक __init a2091_init(व्योम)
अणु
	वापस zorro_रेजिस्टर_driver(&a2091_driver);
पूर्ण
module_init(a2091_init);

अटल व्योम __निकास a2091_निकास(व्योम)
अणु
	zorro_unरेजिस्टर_driver(&a2091_driver);
पूर्ण
module_निकास(a2091_निकास);

MODULE_DESCRIPTION("Commodore A2091/A590 SCSI");
MODULE_LICENSE("GPL");
