<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mvme147hw.h>
#समावेश <यंत्र/irq.h>

#समावेश "scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "wd33c93.h"
#समावेश "mvme147.h"

अटल irqवापस_t mvme147_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा Scsi_Host *instance = data;

	अगर (irq == MVME147_IRQ_SCSI_PORT)
		wd33c93_पूर्णांकr(instance);
	अन्यथा
		m147_pcc->dma_पूर्णांकr = 0x89;	/* Ack and enable पूर्णांकs */
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dma_setup(काष्ठा scsi_cmnd *cmd, पूर्णांक dir_in)
अणु
	काष्ठा Scsi_Host *instance = cmd->device->host;
	काष्ठा WD33C93_hostdata *hdata = shost_priv(instance);
	अचिन्हित अक्षर flags = 0x01;
	अचिन्हित दीर्घ addr = virt_to_bus(cmd->SCp.ptr);

	/* setup dma direction */
	अगर (!dir_in)
		flags |= 0x04;

	/* remember direction */
	hdata->dma_dir = dir_in;

	अगर (dir_in) अणु
		/* invalidate any cache */
		cache_clear(addr, cmd->SCp.this_residual);
	पूर्ण अन्यथा अणु
		/* push any dirty cache */
		cache_push(addr, cmd->SCp.this_residual);
	पूर्ण

	/* start DMA */
	m147_pcc->dma_bcr = cmd->SCp.this_residual | (1 << 24);
	m147_pcc->dma_dadr = addr;
	m147_pcc->dma_cntrl = flags;

	/* वापस success */
	वापस 0;
पूर्ण

अटल व्योम dma_stop(काष्ठा Scsi_Host *instance, काष्ठा scsi_cmnd *SCpnt,
		     पूर्णांक status)
अणु
	m147_pcc->dma_cntrl = 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा mvme147_host_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= "MVME147",
	.name			= "MVME147 built-in SCSI",
	.queuecommand		= wd33c93_queuecommand,
	.eh_पात_handler	= wd33c93_पात,
	.eh_host_reset_handler	= wd33c93_host_reset,
	.show_info		= wd33c93_show_info,
	.ग_लिखो_info		= wd33c93_ग_लिखो_info,
	.can_queue		= CAN_QUEUE,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= CMD_PER_LUN,
पूर्ण;

अटल काष्ठा Scsi_Host *mvme147_shost;

अटल पूर्णांक __init mvme147_init(व्योम)
अणु
	wd33c93_regs regs;
	काष्ठा WD33C93_hostdata *hdata;
	पूर्णांक error = -ENOMEM;

	अगर (!MACH_IS_MVME147)
		वापस 0;

	mvme147_shost = scsi_host_alloc(&mvme147_host_ढाँचा,
			माप(काष्ठा WD33C93_hostdata));
	अगर (!mvme147_shost)
		जाओ err_out;
	mvme147_shost->base = 0xfffe4000;
	mvme147_shost->irq = MVME147_IRQ_SCSI_PORT;

	regs.SASR = (अस्थिर अचिन्हित अक्षर *)0xfffe4000;
	regs.SCMD = (अस्थिर अचिन्हित अक्षर *)0xfffe4001;

	hdata = shost_priv(mvme147_shost);
	hdata->no_sync = 0xff;
	hdata->fast = 0;
	hdata->dma_mode = CTRL_DMA;

	wd33c93_init(mvme147_shost, regs, dma_setup, dma_stop, WD33C93_FS_8_10);

	error = request_irq(MVME147_IRQ_SCSI_PORT, mvme147_पूर्णांकr, 0,
			"MVME147 SCSI PORT", mvme147_shost);
	अगर (error)
		जाओ err_unरेजिस्टर;
	error = request_irq(MVME147_IRQ_SCSI_DMA, mvme147_पूर्णांकr, 0,
			"MVME147 SCSI DMA", mvme147_shost);
	अगर (error)
		जाओ err_मुक्त_irq;
#अगर 0	/* Disabled; causes problems booting */
	m147_pcc->scsi_पूर्णांकerrupt = 0x10;	/* Assert SCSI bus reset */
	udelay(100);
	m147_pcc->scsi_पूर्णांकerrupt = 0x00;	/* Negate SCSI bus reset */
	udelay(2000);
	m147_pcc->scsi_पूर्णांकerrupt = 0x40;	/* Clear bus reset पूर्णांकerrupt */
#पूर्ण_अगर
	m147_pcc->scsi_पूर्णांकerrupt = 0x09;	/* Enable पूर्णांकerrupt */

	m147_pcc->dma_cntrl = 0x00;	/* ensure DMA is stopped */
	m147_pcc->dma_पूर्णांकr = 0x89;	/* Ack and enable पूर्णांकs */

	error = scsi_add_host(mvme147_shost, शून्य);
	अगर (error)
		जाओ err_मुक्त_irq;
	scsi_scan_host(mvme147_shost);
	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(MVME147_IRQ_SCSI_PORT, mvme147_shost);
err_unरेजिस्टर:
	scsi_host_put(mvme147_shost);
err_out:
	वापस error;
पूर्ण

अटल व्योम __निकास mvme147_निकास(व्योम)
अणु
	scsi_हटाओ_host(mvme147_shost);

	/* XXX Make sure DMA is stopped! */
	मुक्त_irq(MVME147_IRQ_SCSI_PORT, mvme147_shost);
	मुक्त_irq(MVME147_IRQ_SCSI_DMA, mvme147_shost);

	scsi_host_put(mvme147_shost);
पूर्ण

module_init(mvme147_init);
module_निकास(mvme147_निकास);
