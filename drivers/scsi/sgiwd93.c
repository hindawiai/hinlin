<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1999 Andrew R. Baker (andrewb@uab.edu)
 * Copyright (C) 2001 Florian Lohoff (flo@rfc822.org)
 * Copyright (C) 2003, 07 Ralf Baechle (ralf@linux-mips.org)
 * 
 * (In all truth, Jed Schimmel wrote all this code.)
 */

#अघोषित DEBUG

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>
#समावेश <यंत्र/sgi/wd.h>

#समावेश "scsi.h"
#समावेश "wd33c93.h"

काष्ठा ip22_hostdata अणु
	काष्ठा WD33C93_hostdata wh;
	dma_addr_t dma;
	व्योम *cpu;
	काष्ठा device *dev;
पूर्ण;

#घोषणा host_to_hostdata(host) ((काष्ठा ip22_hostdata *)((host)->hostdata))

काष्ठा hpc_chunk अणु
	काष्ठा hpc_dma_desc desc;
	u32 _padding;	/* align to quadword boundary */
पूर्ण;

/* space क्रम hpc dma descriptors */
#घोषणा HPC_DMA_SIZE   PAGE_SIZE

#घोषणा DMA_सूची(d)   ((d == DATA_OUT_सूची) ? DMA_TO_DEVICE : DMA_FROM_DEVICE)

अटल irqवापस_t sgiwd93_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host * host = dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(host->host_lock, flags);
	wd33c93_पूर्णांकr(host);
	spin_unlock_irqrestore(host->host_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत
व्योम fill_hpc_entries(काष्ठा ip22_hostdata *hd, काष्ठा scsi_cmnd *cmd, पूर्णांक din)
अणु
	अचिन्हित दीर्घ len = cmd->SCp.this_residual;
	व्योम *addr = cmd->SCp.ptr;
	dma_addr_t physaddr;
	अचिन्हित दीर्घ count;
	काष्ठा hpc_chunk *hcp;

	physaddr = dma_map_single(hd->dev, addr, len, DMA_सूची(din));
	cmd->SCp.dma_handle = physaddr;
	hcp = hd->cpu;

	जबतक (len) अणु
		/*
		 * even cntinfo could be up to 16383, without
		 * magic only 8192 works correctly
		 */
		count = len > 8192 ? 8192 : len;
		hcp->desc.pbuf = physaddr;
		hcp->desc.cntinfo = count;
		hcp++;
		len -= count;
		physaddr += count;
	पूर्ण

	/*
	 * To make sure, अगर we trip an HPC bug, that we transfer every single
	 * byte, we tag on an extra zero length dma descriptor at the end of
	 * the chain.
	 */
	hcp->desc.pbuf = 0;
	hcp->desc.cntinfo = HPCDMA_EOX;
	dma_sync_single_क्रम_device(hd->dev, hd->dma,
		       (अचिन्हित दीर्घ)(hcp + 1) - (अचिन्हित दीर्घ)hd->cpu,
		       DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक dma_setup(काष्ठा scsi_cmnd *cmd, पूर्णांक datainp)
अणु
	काष्ठा ip22_hostdata *hdata = host_to_hostdata(cmd->device->host);
	काष्ठा hpc3_scsiregs *hregs =
		(काष्ठा hpc3_scsiregs *) cmd->device->host->base;

	pr_debug("dma_setup: datainp<%d> hcp<%p> ", datainp, hdata->cpu);

	hdata->wh.dma_dir = datainp;

	/*
	 * wd33c93 shouldn't pass us bogus dma_setups, but it करोes:-(  The
	 * other wd33c93 drivers deal with it the same way (which isn't that
	 * obvious).  IMHO a better fix would be, not to करो these dma setups
	 * in the first place.
	 */
	अगर (cmd->SCp.ptr == शून्य || cmd->SCp.this_residual == 0)
		वापस 1;

	fill_hpc_entries(hdata, cmd, datainp);

	pr_debug(" HPCGO\n");

	/* Start up the HPC. */
	hregs->ndptr = hdata->dma;
	अगर (datainp)
		hregs->ctrl = HPC3_SCTRL_ACTIVE;
	अन्यथा
		hregs->ctrl = HPC3_SCTRL_ACTIVE | HPC3_SCTRL_सूची;

	वापस 0;
पूर्ण

अटल व्योम dma_stop(काष्ठा Scsi_Host *instance, काष्ठा scsi_cmnd *SCpnt,
		     पूर्णांक status)
अणु
	काष्ठा ip22_hostdata *hdata = host_to_hostdata(instance);
	काष्ठा hpc3_scsiregs *hregs;

	अगर (!SCpnt)
		वापस;

	अगर (SCpnt->SCp.ptr == शून्य || SCpnt->SCp.this_residual == 0)
		वापस;

	hregs = (काष्ठा hpc3_scsiregs *) SCpnt->device->host->base;

	pr_debug("dma_stop: status<%d> ", status);

	/* First stop the HPC and flush it's FIFO. */
	अगर (hdata->wh.dma_dir) अणु
		hregs->ctrl |= HPC3_SCTRL_FLUSH;
		जबतक (hregs->ctrl & HPC3_SCTRL_ACTIVE)
			barrier();
	पूर्ण
	hregs->ctrl = 0;
	dma_unmap_single(hdata->dev, SCpnt->SCp.dma_handle,
			 SCpnt->SCp.this_residual,
			 DMA_सूची(hdata->wh.dma_dir));

	pr_debug("\n");
पूर्ण

व्योम sgiwd93_reset(अचिन्हित दीर्घ base)
अणु
	काष्ठा hpc3_scsiregs *hregs = (काष्ठा hpc3_scsiregs *) base;

	hregs->ctrl = HPC3_SCTRL_CRESET;
	udelay(50);
	hregs->ctrl = 0;
पूर्ण
EXPORT_SYMBOL_GPL(sgiwd93_reset);

अटल अंतरभूत व्योम init_hpc_chain(काष्ठा ip22_hostdata *hdata)
अणु
	काष्ठा hpc_chunk *hcp = (काष्ठा hpc_chunk *)hdata->cpu;
	dma_addr_t dma = hdata->dma;
	अचिन्हित दीर्घ start, end;

	start = (अचिन्हित दीर्घ) hcp;
	end = start + HPC_DMA_SIZE;
	जबतक (start < end) अणु
		hcp->desc.pnext = (u32) (dma + माप(काष्ठा hpc_chunk));
		hcp->desc.cntinfo = HPCDMA_EOX;
		hcp++;
		dma += माप(काष्ठा hpc_chunk);
		start += माप(काष्ठा hpc_chunk);
	पूर्ण
	hcp--;
	hcp->desc.pnext = hdata->dma;
पूर्ण

/*
 * Kludge alert - the SCSI code calls the पात and reset method with पूर्णांक
 * arguments not with poपूर्णांकers.  So this is going to blow up beautyfully
 * on 64-bit प्रणालीs with memory outside the compat address spaces.
 */
अटल काष्ठा scsi_host_ढाँचा sgiwd93_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= "SGIWD93",
	.name			= "SGI WD93",
	.queuecommand		= wd33c93_queuecommand,
	.eh_पात_handler	= wd33c93_पात,
	.eh_host_reset_handler	= wd33c93_host_reset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= 8,
	.dma_boundary		= PAGE_SIZE - 1,
पूर्ण;

अटल पूर्णांक sgiwd93_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sgiwd93_platक्रमm_data *pd = pdev->dev.platक्रमm_data;
	अचिन्हित अक्षर *wdregs = pd->wdregs;
	काष्ठा hpc3_scsiregs *hregs = pd->hregs;
	काष्ठा ip22_hostdata *hdata;
	काष्ठा Scsi_Host *host;
	wd33c93_regs regs;
	अचिन्हित पूर्णांक unit = pd->unit;
	अचिन्हित पूर्णांक irq = pd->irq;
	पूर्णांक err;

	host = scsi_host_alloc(&sgiwd93_ढाँचा, माप(काष्ठा ip22_hostdata));
	अगर (!host) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	host->base = (अचिन्हित दीर्घ) hregs;
	host->irq = irq;

	hdata = host_to_hostdata(host);
	hdata->dev = &pdev->dev;
	hdata->cpu = dma_alloc_noncoherent(&pdev->dev, HPC_DMA_SIZE,
				&hdata->dma, DMA_TO_DEVICE, GFP_KERNEL);
	अगर (!hdata->cpu) अणु
		prपूर्णांकk(KERN_WARNING "sgiwd93: Could not allocate memory for "
		       "host %d buffer.\n", unit);
		err = -ENOMEM;
		जाओ out_put;
	पूर्ण

	init_hpc_chain(hdata);

	regs.SASR = wdregs + 3;
	regs.SCMD = wdregs + 7;

	hdata->wh.no_sync = 0;
	hdata->wh.fast = 1;
	hdata->wh.dma_mode = CTRL_BURST;

	wd33c93_init(host, regs, dma_setup, dma_stop, WD33C93_FS_MHZ(20));

	err = request_irq(irq, sgiwd93_पूर्णांकr, 0, "SGI WD93", host);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "sgiwd93: Could not register irq %d "
		       "for host %d.\n", irq, unit);
		जाओ out_मुक्त;
	पूर्ण

	platक्रमm_set_drvdata(pdev, host);

	err = scsi_add_host(host, शून्य);
	अगर (err)
		जाओ out_irq;

	scsi_scan_host(host);

	वापस 0;

out_irq:
	मुक्त_irq(irq, host);
out_मुक्त:
	dma_मुक्त_noncoherent(&pdev->dev, HPC_DMA_SIZE, hdata->cpu, hdata->dma,
			DMA_TO_DEVICE);
out_put:
	scsi_host_put(host);
out:

	वापस err;
पूर्ण

अटल पूर्णांक sgiwd93_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा ip22_hostdata *hdata = (काष्ठा ip22_hostdata *) host->hostdata;
	काष्ठा sgiwd93_platक्रमm_data *pd = pdev->dev.platक्रमm_data;

	scsi_हटाओ_host(host);
	मुक्त_irq(pd->irq, host);
	dma_मुक्त_noncoherent(&pdev->dev, HPC_DMA_SIZE, hdata->cpu, hdata->dma,
			DMA_TO_DEVICE);
	scsi_host_put(host);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sgiwd93_driver = अणु
	.probe  = sgiwd93_probe,
	.हटाओ = sgiwd93_हटाओ,
	.driver = अणु
		.name   = "sgiwd93",
	पूर्ण
पूर्ण;

अटल पूर्णांक __init sgiwd93_module_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sgiwd93_driver);
पूर्ण

अटल व्योम __निकास sgiwd93_module_निकास(व्योम)
अणु
	वापस platक्रमm_driver_unरेजिस्टर(&sgiwd93_driver);
पूर्ण

module_init(sgiwd93_module_init);
module_निकास(sgiwd93_module_निकास);

MODULE_DESCRIPTION("SGI WD33C93 driver");
MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sgiwd93");
