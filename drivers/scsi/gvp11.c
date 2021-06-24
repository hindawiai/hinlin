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
#समावेश "gvp11.h"


#घोषणा CHECK_WD33C93

काष्ठा gvp11_hostdata अणु
	काष्ठा WD33C93_hostdata wh;
	काष्ठा gvp11_scsiregs *regs;
पूर्ण;

अटल irqवापस_t gvp11_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा Scsi_Host *instance = data;
	काष्ठा gvp11_hostdata *hdata = shost_priv(instance);
	अचिन्हित पूर्णांक status = hdata->regs->CNTR;
	अचिन्हित दीर्घ flags;

	अगर (!(status & GVP11_DMAC_INT_PENDING))
		वापस IRQ_NONE;

	spin_lock_irqsave(instance->host_lock, flags);
	wd33c93_पूर्णांकr(instance);
	spin_unlock_irqrestore(instance->host_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gvp11_xfer_mask = 0;

व्योम gvp11_setup(अक्षर *str, पूर्णांक *पूर्णांकs)
अणु
	gvp11_xfer_mask = पूर्णांकs[1];
पूर्ण

अटल पूर्णांक dma_setup(काष्ठा scsi_cmnd *cmd, पूर्णांक dir_in)
अणु
	काष्ठा Scsi_Host *instance = cmd->device->host;
	काष्ठा gvp11_hostdata *hdata = shost_priv(instance);
	काष्ठा WD33C93_hostdata *wh = &hdata->wh;
	काष्ठा gvp11_scsiregs *regs = hdata->regs;
	अचिन्हित लघु cntr = GVP11_DMAC_INT_ENABLE;
	अचिन्हित दीर्घ addr = virt_to_bus(cmd->SCp.ptr);
	पूर्णांक bank_mask;
	अटल पूर्णांक scsi_alloc_out_of_range = 0;

	/* use bounce buffer अगर the physical address is bad */
	अगर (addr & wh->dma_xfer_mask) अणु
		wh->dma_bounce_len = (cmd->SCp.this_residual + 511) & ~0x1ff;

		अगर (!scsi_alloc_out_of_range) अणु
			wh->dma_bounce_buffer =
				kदो_स्मृति(wh->dma_bounce_len, GFP_KERNEL);
			wh->dma_buffer_pool = BUF_SCSI_ALLOCED;
		पूर्ण

		अगर (scsi_alloc_out_of_range ||
		    !wh->dma_bounce_buffer) अणु
			wh->dma_bounce_buffer =
				amiga_chip_alloc(wh->dma_bounce_len,
						 "GVP II SCSI Bounce Buffer");

			अगर (!wh->dma_bounce_buffer) अणु
				wh->dma_bounce_len = 0;
				वापस 1;
			पूर्ण

			wh->dma_buffer_pool = BUF_CHIP_ALLOCED;
		पूर्ण

		/* check अगर the address of the bounce buffer is OK */
		addr = virt_to_bus(wh->dma_bounce_buffer);

		अगर (addr & wh->dma_xfer_mask) अणु
			/* fall back to Chip RAM अगर address out of range */
			अगर (wh->dma_buffer_pool == BUF_SCSI_ALLOCED) अणु
				kमुक्त(wh->dma_bounce_buffer);
				scsi_alloc_out_of_range = 1;
			पूर्ण अन्यथा अणु
				amiga_chip_मुक्त(wh->dma_bounce_buffer);
			पूर्ण

			wh->dma_bounce_buffer =
				amiga_chip_alloc(wh->dma_bounce_len,
						 "GVP II SCSI Bounce Buffer");

			अगर (!wh->dma_bounce_buffer) अणु
				wh->dma_bounce_len = 0;
				वापस 1;
			पूर्ण

			addr = virt_to_bus(wh->dma_bounce_buffer);
			wh->dma_buffer_pool = BUF_CHIP_ALLOCED;
		पूर्ण

		अगर (!dir_in) अणु
			/* copy to bounce buffer क्रम a ग_लिखो */
			स_नकल(wh->dma_bounce_buffer, cmd->SCp.ptr,
			       cmd->SCp.this_residual);
		पूर्ण
	पूर्ण

	/* setup dma direction */
	अगर (!dir_in)
		cntr |= GVP11_DMAC_सूची_WRITE;

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

	bank_mask = (~wh->dma_xfer_mask >> 18) & 0x01c0;
	अगर (bank_mask)
		regs->BANK = bank_mask & (addr >> 18);

	/* start DMA */
	regs->ST_DMA = 1;

	/* वापस success */
	वापस 0;
पूर्ण

अटल व्योम dma_stop(काष्ठा Scsi_Host *instance, काष्ठा scsi_cmnd *SCpnt,
		     पूर्णांक status)
अणु
	काष्ठा gvp11_hostdata *hdata = shost_priv(instance);
	काष्ठा WD33C93_hostdata *wh = &hdata->wh;
	काष्ठा gvp11_scsiregs *regs = hdata->regs;

	/* stop DMA */
	regs->SP_DMA = 1;
	/* हटाओ ग_लिखो bit from CONTROL bits */
	regs->CNTR = GVP11_DMAC_INT_ENABLE;

	/* copy from a bounce buffer, अगर necessary */
	अगर (status && wh->dma_bounce_buffer) अणु
		अगर (wh->dma_dir && SCpnt)
			स_नकल(SCpnt->SCp.ptr, wh->dma_bounce_buffer,
			       SCpnt->SCp.this_residual);

		अगर (wh->dma_buffer_pool == BUF_SCSI_ALLOCED)
			kमुक्त(wh->dma_bounce_buffer);
		अन्यथा
			amiga_chip_मुक्त(wh->dma_bounce_buffer);

		wh->dma_bounce_buffer = शून्य;
		wh->dma_bounce_len = 0;
	पूर्ण
पूर्ण

अटल काष्ठा scsi_host_ढाँचा gvp11_scsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "GVP Series II SCSI",
	.show_info		= wd33c93_show_info,
	.ग_लिखो_info		= wd33c93_ग_लिखो_info,
	.proc_name		= "GVP11",
	.queuecommand		= wd33c93_queuecommand,
	.eh_पात_handler	= wd33c93_पात,
	.eh_host_reset_handler	= wd33c93_host_reset,
	.can_queue		= CAN_QUEUE,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= CMD_PER_LUN,
	.dma_boundary		= PAGE_SIZE - 1,
पूर्ण;

अटल पूर्णांक check_wd33c93(काष्ठा gvp11_scsiregs *regs)
अणु
#अगर_घोषित CHECK_WD33C93
	अस्थिर अचिन्हित अक्षर *sasr_3393, *scmd_3393;
	अचिन्हित अक्षर save_sasr;
	अचिन्हित अक्षर q, qq;

	/*
	 * These darn GVP boards are a problem - it can be tough to tell
	 * whether or not they include a SCSI controller. This is the
	 * ultimate Yet-Another-GVP-Detection-Hack in that it actually
	 * probes क्रम a WD33c93 chip: If we find one, it's extremely
	 * likely that this card supports SCSI, regardless of Product_
	 * Code, Board_Size, etc.
	 */

	/* Get poपूर्णांकers to the presumed रेजिस्टर locations and save contents */

	sasr_3393 = &regs->SASR;
	scmd_3393 = &regs->SCMD;
	save_sasr = *sasr_3393;

	/* First test the AuxStatus Reg */

	q = *sasr_3393;	/* पढ़ो it */
	अगर (q & 0x08)	/* bit 3 should always be clear */
		वापस -ENODEV;
	*sasr_3393 = WD_AUXILIARY_STATUS;	/* setup indirect address */
	अगर (*sasr_3393 == WD_AUXILIARY_STATUS) अणु	/* shouldn't retain the ग_लिखो */
		*sasr_3393 = save_sasr;	/* Oops - restore this byte */
		वापस -ENODEV;
	पूर्ण
	अगर (*sasr_3393 != q) अणु	/* should still पढ़ो the same */
		*sasr_3393 = save_sasr;	/* Oops - restore this byte */
		वापस -ENODEV;
	पूर्ण
	अगर (*scmd_3393 != q)	/* and so should the image at 0x1f */
		वापस -ENODEV;

	/*
	 * Ok, we probably have a wd33c93, but let's check a few other places
	 * क्रम good measure. Make sure that this works क्रम both 'A and 'B
	 * chip versions.
	 */

	*sasr_3393 = WD_SCSI_STATUS;
	q = *scmd_3393;
	*sasr_3393 = WD_SCSI_STATUS;
	*scmd_3393 = ~q;
	*sasr_3393 = WD_SCSI_STATUS;
	qq = *scmd_3393;
	*sasr_3393 = WD_SCSI_STATUS;
	*scmd_3393 = q;
	अगर (qq != q)	/* should be पढ़ो only */
		वापस -ENODEV;
	*sasr_3393 = 0x1e;	/* this रेजिस्टर is unimplemented */
	q = *scmd_3393;
	*sasr_3393 = 0x1e;
	*scmd_3393 = ~q;
	*sasr_3393 = 0x1e;
	qq = *scmd_3393;
	*sasr_3393 = 0x1e;
	*scmd_3393 = q;
	अगर (qq != q || qq != 0xff)	/* should be पढ़ो only, all 1's */
		वापस -ENODEV;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	q = *scmd_3393;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	*scmd_3393 = ~q;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	qq = *scmd_3393;
	*sasr_3393 = WD_TIMEOUT_PERIOD;
	*scmd_3393 = q;
	अगर (qq != (~q & 0xff))	/* should be पढ़ो/ग_लिखो */
		वापस -ENODEV;
#पूर्ण_अगर /* CHECK_WD33C93 */

	वापस 0;
पूर्ण

अटल पूर्णांक gvp11_probe(काष्ठा zorro_dev *z, स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा Scsi_Host *instance;
	अचिन्हित दीर्घ address;
	पूर्णांक error;
	अचिन्हित पूर्णांक epc;
	अचिन्हित पूर्णांक शेष_dma_xfer_mask;
	काष्ठा gvp11_hostdata *hdata;
	काष्ठा gvp11_scsiregs *regs;
	wd33c93_regs wdregs;

	शेष_dma_xfer_mask = ent->driver_data;

	/*
	 * Rumors state that some GVP ram boards use the same product
	 * code as the SCSI controllers. Thereक्रमe अगर the board-size
	 * is not 64KB we assume it is a ram board and bail out.
	 */
	अगर (zorro_resource_len(z) != 0x10000)
		वापस -ENODEV;

	address = z->resource.start;
	अगर (!request_mem_region(address, 256, "wd33c93"))
		वापस -EBUSY;

	regs = ZTWO_VADDR(address);

	error = check_wd33c93(regs);
	अगर (error)
		जाओ fail_check_or_alloc;

	instance = scsi_host_alloc(&gvp11_scsi_ढाँचा,
				   माप(काष्ठा gvp11_hostdata));
	अगर (!instance) अणु
		error = -ENOMEM;
		जाओ fail_check_or_alloc;
	पूर्ण

	instance->irq = IRQ_AMIGA_PORTS;
	instance->unique_id = z->slotaddr;

	regs->secret2 = 1;
	regs->secret1 = 0;
	regs->secret3 = 15;
	जबतक (regs->CNTR & GVP11_DMAC_BUSY)
		;
	regs->CNTR = 0;
	regs->BANK = 0;

	wdregs.SASR = &regs->SASR;
	wdregs.SCMD = &regs->SCMD;

	hdata = shost_priv(instance);
	अगर (gvp11_xfer_mask)
		hdata->wh.dma_xfer_mask = gvp11_xfer_mask;
	अन्यथा
		hdata->wh.dma_xfer_mask = शेष_dma_xfer_mask;

	hdata->wh.no_sync = 0xff;
	hdata->wh.fast = 0;
	hdata->wh.dma_mode = CTRL_DMA;
	hdata->regs = regs;

	/*
	 * Check क्रम 14MHz SCSI घड़ी
	 */
	epc = *(अचिन्हित लघु *)(ZTWO_VADDR(address) + 0x8000);
	wd33c93_init(instance, wdregs, dma_setup, dma_stop,
		     (epc & GVP_SCSICLKMASK) ? WD33C93_FS_8_10
					     : WD33C93_FS_12_15);

	error = request_irq(IRQ_AMIGA_PORTS, gvp11_पूर्णांकr, IRQF_SHARED,
			    "GVP11 SCSI", instance);
	अगर (error)
		जाओ fail_irq;

	regs->CNTR = GVP11_DMAC_INT_ENABLE;

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
fail_check_or_alloc:
	release_mem_region(address, 256);
	वापस error;
पूर्ण

अटल व्योम gvp11_हटाओ(काष्ठा zorro_dev *z)
अणु
	काष्ठा Scsi_Host *instance = zorro_get_drvdata(z);
	काष्ठा gvp11_hostdata *hdata = shost_priv(instance);

	hdata->regs->CNTR = 0;
	scsi_हटाओ_host(instance);
	मुक्त_irq(IRQ_AMIGA_PORTS, instance);
	scsi_host_put(instance);
	release_mem_region(z->resource.start, 256);
पूर्ण

	/*
	 * This should (hopefully) be the correct way to identअगरy
	 * all the dअगरferent GVP SCSI controllers (except क्रम the
	 * SERIES I though).
	 */

अटल काष्ठा zorro_device_id gvp11_zorro_tbl[] = अणु
	अणु ZORRO_PROD_GVP_COMBO_030_R3_SCSI,	~0x00ffffff पूर्ण,
	अणु ZORRO_PROD_GVP_SERIES_II,		~0x00ffffff पूर्ण,
	अणु ZORRO_PROD_GVP_GFORCE_030_SCSI,	~0x01ffffff पूर्ण,
	अणु ZORRO_PROD_GVP_A530_SCSI,		~0x01ffffff पूर्ण,
	अणु ZORRO_PROD_GVP_COMBO_030_R4_SCSI,	~0x01ffffff पूर्ण,
	अणु ZORRO_PROD_GVP_A1291,			~0x07ffffff पूर्ण,
	अणु ZORRO_PROD_GVP_GFORCE_040_SCSI_1,	~0x07ffffff पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, gvp11_zorro_tbl);

अटल काष्ठा zorro_driver gvp11_driver = अणु
	.name		= "gvp11",
	.id_table	= gvp11_zorro_tbl,
	.probe		= gvp11_probe,
	.हटाओ		= gvp11_हटाओ,
पूर्ण;

अटल पूर्णांक __init gvp11_init(व्योम)
अणु
	वापस zorro_रेजिस्टर_driver(&gvp11_driver);
पूर्ण
module_init(gvp11_init);

अटल व्योम __निकास gvp11_निकास(व्योम)
अणु
	zorro_unरेजिस्टर_driver(&gvp11_driver);
पूर्ण
module_निकास(gvp11_निकास);

MODULE_DESCRIPTION("GVP Series II SCSI");
MODULE_LICENSE("GPL");
