<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/scsi/arm/arxescsi.c
 *
 * Copyright (C) 1997-2000 Russell King, Stefan Hanske
 *
 * This driver is based on experimentation.  Hence, it may have made
 * assumptions about the particular card that I have available, and
 * may not be reliable!
 *
 * Changelog:
 *  30-08-1997	RMK	0.0.0	Created, READONLY version as cumana_2.c
 *  22-01-1998	RMK	0.0.1	Updated to 2.1.80
 *  15-04-1998	RMK	0.0.1	Only करो PIO अगर FAS216 will allow it.
 *  11-06-1998 	SH	0.0.2   Changed to support ARXE 16-bit SCSI card
 *				enabled writing
 *  01-01-2000	SH	0.1.0   Added *real* pseuकरो dma writing
 *				(arxescsi_pseuकरो_dma_ग_लिखो)
 *  02-04-2000	RMK	0.1.1	Updated क्रम new error handling code.
 *  22-10-2000  SH		Updated क्रम new रेजिस्टरing scheme.
 */
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/unistd.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ecard.h>

#समावेश "../scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "fas216.h"

काष्ठा arxescsi_info अणु
	FAS216_Info		info;
	काष्ठा expansion_card	*ec;
	व्योम __iomem		*base;
पूर्ण;

#घोषणा DMADATA_OFFSET	(0x200)

#घोषणा DMASTAT_OFFSET	(0x600)
#घोषणा DMASTAT_DRQ	(1 << 0)

#घोषणा CSTATUS_IRQ	(1 << 0)

#घोषणा VERSION "1.10 (23/01/2003 2.5.57)"

/*
 * Function: पूर्णांक arxescsi_dma_setup(host, SCpnt, direction, min_type)
 * Purpose : initialises DMA/PIO
 * Params  : host      - host
 *	     SCpnt     - command
 *	     direction - DMA on to/off of card
 *	     min_type  - minimum DMA support that we must have क्रम this transfer
 * Returns : 0 अगर we should not set CMD_WITHDMA क्रम transfer info command
 */
अटल fasdmatype_t
arxescsi_dma_setup(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp,
		       fasdmadir_t direction, fasdmatype_t min_type)
अणु
	/*
	 * We करोn't करो real DMA
	 */
	वापस fasdma_pseuकरो;
पूर्ण

अटल व्योम arxescsi_pseuकरो_dma_ग_लिखो(अचिन्हित अक्षर *addr, व्योम __iomem *base)
अणु
       __यंत्र__ __अस्थिर__(
       "               stmdb   sp!, {r0-r12}\n"
       "               mov     r3, %0\n"
       "               mov     r1, %1\n"
       "               add     r2, r1, #512\n"
       "               mov     r4, #256\n"
       ".loop_1:       ldmia   r3!, {r6, r8, r10, r12}\n"
       "               mov     r5, r6, lsl #16\n"
       "               mov     r7, r8, lsl #16\n"
       ".loop_2:       ldrb    r0, [r1, #1536]\n"
       "               tst     r0, #1\n"
       "               beq     .loop_2\n"
       "               stmia   r2, {r5-r8}\n\t"
       "               mov     r9, r10, lsl #16\n"
       "               mov     r11, r12, lsl #16\n"
       ".loop_3:       ldrb    r0, [r1, #1536]\n"
       "               tst     r0, #1\n"
       "               beq     .loop_3\n"
       "               stmia   r2, {r9-r12}\n"
       "               subs    r4, r4, #16\n"
       "               bne     .loop_1\n"
       "               ldmia   sp!, {r0-r12}\n"
       :
       : "r" (addr), "r" (base));
पूर्ण

/*
 * Function: पूर्णांक arxescsi_dma_pseuकरो(host, SCpnt, direction, transfer)
 * Purpose : handles pseuकरो DMA
 * Params  : host      - host
 *	     SCpnt     - command
 *	     direction - DMA on to/off of card
 *	     transfer  - minimum number of bytes we expect to transfer
 */
अटल व्योम
arxescsi_dma_pseuकरो(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp,
		    fasdmadir_t direction, पूर्णांक transfer)
अणु
	काष्ठा arxescsi_info *info = (काष्ठा arxescsi_info *)host->hostdata;
	अचिन्हित पूर्णांक length, error = 0;
	व्योम __iomem *base = info->info.scsi.io_base;
	अचिन्हित अक्षर *addr;

	length = SCp->this_residual;
	addr = SCp->ptr;

	अगर (direction == DMA_OUT) अणु
		अचिन्हित पूर्णांक word;
		जबतक (length > 256) अणु
			अगर (पढ़ोb(base + 0x80) & STAT_INT) अणु
				error = 1;
				अवरोध;
			पूर्ण
			arxescsi_pseuकरो_dma_ग_लिखो(addr, base);
			addr += 256;
			length -= 256;
		पूर्ण

		अगर (!error)
			जबतक (length > 0) अणु
				अगर (पढ़ोb(base + 0x80) & STAT_INT)
					अवरोध;
	 
				अगर (!(पढ़ोb(base + DMASTAT_OFFSET) & DMASTAT_DRQ))
					जारी;

				word = *addr | *(addr + 1) << 8;

				ग_लिखोw(word, base + DMADATA_OFFSET);
				अगर (length > 1) अणु
					addr += 2;
					length -= 2;
				पूर्ण अन्यथा अणु
					addr += 1;
					length -= 1;
				पूर्ण
			पूर्ण
	पूर्ण
	अन्यथा अणु
		अगर (transfer && (transfer & 255)) अणु
			जबतक (length >= 256) अणु
				अगर (पढ़ोb(base + 0x80) & STAT_INT) अणु
					error = 1;
					अवरोध;
				पूर्ण
	    
				अगर (!(पढ़ोb(base + DMASTAT_OFFSET) & DMASTAT_DRQ))
					जारी;

				पढ़ोsw(base + DMADATA_OFFSET, addr, 256 >> 1);
				addr += 256;
				length -= 256;
			पूर्ण
		पूर्ण

		अगर (!(error))
			जबतक (length > 0) अणु
				अचिन्हित दीर्घ word;

				अगर (पढ़ोb(base + 0x80) & STAT_INT)
					अवरोध;

				अगर (!(पढ़ोb(base + DMASTAT_OFFSET) & DMASTAT_DRQ))
					जारी;

				word = पढ़ोw(base + DMADATA_OFFSET);
				*addr++ = word;
				अगर (--length > 0) अणु
					*addr++ = word >> 8;
					length --;
				पूर्ण
			पूर्ण
	पूर्ण
पूर्ण

/*
 * Function: पूर्णांक arxescsi_dma_stop(host, SCpnt)
 * Purpose : stops DMA/PIO
 * Params  : host  - host
 *	     SCpnt - command
 */
अटल व्योम arxescsi_dma_stop(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp)
अणु
	/*
	 * no DMA to stop
	 */
पूर्ण

/*
 * Function: स्थिर अक्षर *arxescsi_info(काष्ठा Scsi_Host * host)
 * Purpose : वापसs a descriptive string about this पूर्णांकerface,
 * Params  : host - driver host काष्ठाure to वापस info क्रम.
 * Returns : poपूर्णांकer to a अटल buffer containing null terminated string.
 */
अटल स्थिर अक्षर *arxescsi_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा arxescsi_info *info = (काष्ठा arxescsi_info *)host->hostdata;
	अटल अक्षर string[150];

	प्र_लिखो(string, "%s (%s) in slot %d v%s",
		host->hostt->name, info->info.scsi.type, info->ec->slot_no,
		VERSION);

	वापस string;
पूर्ण

अटल पूर्णांक
arxescsi_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	काष्ठा arxescsi_info *info;
	info = (काष्ठा arxescsi_info *)host->hostdata;

	seq_म_लिखो(m, "ARXE 16-bit SCSI driver v%s\n", VERSION);
	fas216_prपूर्णांक_host(&info->info, m);
	fas216_prपूर्णांक_stats(&info->info, m);
	fas216_prपूर्णांक_devices(&info->info, m);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा arxescsi_ढाँचा = अणु
	.show_info			= arxescsi_show_info,
	.name				= "ARXE SCSI card",
	.info				= arxescsi_info,
	.queuecommand			= fas216_noqueue_command,
	.eh_host_reset_handler		= fas216_eh_host_reset,
	.eh_bus_reset_handler		= fas216_eh_bus_reset,
	.eh_device_reset_handler	= fas216_eh_device_reset,
	.eh_पात_handler		= fas216_eh_पात,
	.can_queue			= 0,
	.this_id			= 7,
	.sg_tablesize			= SG_ALL,
	.dma_boundary			= PAGE_SIZE - 1,
	.proc_name			= "arxescsi",
पूर्ण;

अटल पूर्णांक arxescsi_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा arxescsi_info *info;
	व्योम __iomem *base;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	base = ecardm_iomap(ec, ECARD_RES_MEMC, 0, 0);
	अगर (!base) अणु
		ret = -ENOMEM;
		जाओ out_region;
	पूर्ण

	host = scsi_host_alloc(&arxescsi_ढाँचा, माप(काष्ठा arxescsi_info));
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ out_region;
	पूर्ण

	info = (काष्ठा arxescsi_info *)host->hostdata;
	info->ec = ec;
	info->base = base;

	info->info.scsi.io_base		= base + 0x2000;
	info->info.scsi.irq		= 0;
	info->info.scsi.dma		= NO_DMA;
	info->info.scsi.io_shअगरt	= 5;
	info->info.अगरcfg.घड़ीrate	= 24; /* MHz */
	info->info.अगरcfg.select_समयout = 255;
	info->info.अगरcfg.asyncperiod	= 200; /* ns */
	info->info.अगरcfg.sync_max_depth	= 0;
	info->info.अगरcfg.cntl3		= CNTL3_FASTSCSI | CNTL3_FASTCLK;
	info->info.अगरcfg.disconnect_ok	= 0;
	info->info.अगरcfg.wide_max_size	= 0;
	info->info.अगरcfg.capabilities	= FASCAP_PSEUDODMA;
	info->info.dma.setup		= arxescsi_dma_setup;
	info->info.dma.pseuकरो		= arxescsi_dma_pseuकरो;
	info->info.dma.stop		= arxescsi_dma_stop;
		
	ec->irqaddr = base;
	ec->irqmask = CSTATUS_IRQ;

	ret = fas216_init(host);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	ret = fas216_add(host, &ec->dev);
	अगर (ret == 0)
		जाओ out;

	fas216_release(host);
 out_unरेजिस्टर:
	scsi_host_put(host);
 out_region:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम arxescsi_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, शून्य);
	fas216_हटाओ(host);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id arxescsi_cids[] = अणु
	अणु MANU_ARXE, PROD_ARXE_SCSI पूर्ण,
	अणु 0xffff, 0xffff पूर्ण,
पूर्ण;

अटल काष्ठा ecard_driver arxescsi_driver = अणु
	.probe		= arxescsi_probe,
	.हटाओ		= arxescsi_हटाओ,
	.id_table	= arxescsi_cids,
	.drv = अणु
		.name		= "arxescsi",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init init_arxe_scsi_driver(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&arxescsi_driver);
पूर्ण

अटल व्योम __निकास निकास_arxe_scsi_driver(व्योम)
अणु
	ecard_हटाओ_driver(&arxescsi_driver);
पूर्ण

module_init(init_arxe_scsi_driver);
module_निकास(निकास_arxe_scsi_driver);

MODULE_AUTHOR("Stefan Hanske");
MODULE_DESCRIPTION("ARXESCSI driver for Acorn machines");
MODULE_LICENSE("GPL");

