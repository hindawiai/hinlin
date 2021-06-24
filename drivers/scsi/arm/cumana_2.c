<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/scsi/cumana_2.c
 *
 *  Copyright (C) 1997-2005 Russell King
 *
 *  Changelog:
 *   30-08-1997	RMK	0.0.0	Created, READONLY version.
 *   22-01-1998	RMK	0.0.1	Updated to 2.1.80.
 *   15-04-1998	RMK	0.0.1	Only करो PIO अगर FAS216 will allow it.
 *   02-05-1998	RMK	0.0.2	Updated & added DMA support.
 *   27-06-1998	RMK		Changed यंत्र/delay.h to linux/delay.h
 *   18-08-1998	RMK	0.0.3	Fixed synchronous transfer depth.
 *   02-04-2000	RMK	0.0.4	Updated क्रम new error handling code.
 */
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/ecard.h>
#समावेश <यंत्र/पन.स>

#समावेश "../scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "fas216.h"
#समावेश "scsi.h"

#समावेश <scsi/scsicam.h>

#घोषणा CUMANASCSI2_STATUS		(0x0000)
#घोषणा STATUS_INT			(1 << 0)
#घोषणा STATUS_DRQ			(1 << 1)
#घोषणा STATUS_LATCHED			(1 << 3)

#घोषणा CUMANASCSI2_ALATCH		(0x0014)
#घोषणा ALATCH_ENA_INT			(3)
#घोषणा ALATCH_DIS_INT			(2)
#घोषणा ALATCH_ENA_TERM			(5)
#घोषणा ALATCH_DIS_TERM			(4)
#घोषणा ALATCH_ENA_BIT32		(11)
#घोषणा ALATCH_DIS_BIT32		(10)
#घोषणा ALATCH_ENA_DMA			(13)
#घोषणा ALATCH_DIS_DMA			(12)
#घोषणा ALATCH_DMA_OUT			(15)
#घोषणा ALATCH_DMA_IN			(14)

#घोषणा CUMANASCSI2_PSEUDODMA		(0x0200)

#घोषणा CUMANASCSI2_FAS216_OFFSET	(0x0300)
#घोषणा CUMANASCSI2_FAS216_SHIFT	2

/*
 * Version
 */
#घोषणा VERSION "1.00 (13/11/2002 2.5.47)"

/*
 * Use term=0,1,0,0,0 to turn terminators on/off
 */
अटल पूर्णांक term[MAX_ECARDS] = अणु 1, 1, 1, 1, 1, 1, 1, 1 पूर्ण;

#घोषणा NR_SG	256

काष्ठा cumanascsi2_info अणु
	FAS216_Info		info;
	काष्ठा expansion_card	*ec;
	व्योम __iomem		*base;
	अचिन्हित पूर्णांक		terms;		/* Terminator state	*/
	काष्ठा scatterlist	sg[NR_SG];	/* Scatter DMA list	*/
पूर्ण;

#घोषणा CSTATUS_IRQ	(1 << 0)
#घोषणा CSTATUS_DRQ	(1 << 1)

/* Prototype: व्योम cumanascsi_2_irqenable(ec, irqnr)
 * Purpose  : Enable पूर्णांकerrupts on Cumana SCSI 2 card
 * Params   : ec    - expansion card काष्ठाure
 *          : irqnr - पूर्णांकerrupt number
 */
अटल व्योम
cumanascsi_2_irqenable(काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा cumanascsi2_info *info = ec->irq_data;
	ग_लिखोb(ALATCH_ENA_INT, info->base + CUMANASCSI2_ALATCH);
पूर्ण

/* Prototype: व्योम cumanascsi_2_irqdisable(ec, irqnr)
 * Purpose  : Disable पूर्णांकerrupts on Cumana SCSI 2 card
 * Params   : ec    - expansion card काष्ठाure
 *          : irqnr - पूर्णांकerrupt number
 */
अटल व्योम
cumanascsi_2_irqdisable(काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा cumanascsi2_info *info = ec->irq_data;
	ग_लिखोb(ALATCH_DIS_INT, info->base + CUMANASCSI2_ALATCH);
पूर्ण

अटल स्थिर expansioncard_ops_t cumanascsi_2_ops = अणु
	.irqenable	= cumanascsi_2_irqenable,
	.irqdisable	= cumanascsi_2_irqdisable,
पूर्ण;

/* Prototype: व्योम cumanascsi_2_terminator_ctl(host, on_off)
 * Purpose  : Turn the Cumana SCSI 2 terminators on or off
 * Params   : host   - card to turn on/off
 *          : on_off - !0 to turn on, 0 to turn off
 */
अटल व्योम
cumanascsi_2_terminator_ctl(काष्ठा Scsi_Host *host, पूर्णांक on_off)
अणु
	काष्ठा cumanascsi2_info *info = (काष्ठा cumanascsi2_info *)host->hostdata;

	अगर (on_off) अणु
		info->terms = 1;
		ग_लिखोb(ALATCH_ENA_TERM, info->base + CUMANASCSI2_ALATCH);
	पूर्ण अन्यथा अणु
		info->terms = 0;
		ग_लिखोb(ALATCH_DIS_TERM, info->base + CUMANASCSI2_ALATCH);
	पूर्ण
पूर्ण

/* Prototype: व्योम cumanascsi_2_पूर्णांकr(irq, *dev_id, *regs)
 * Purpose  : handle पूर्णांकerrupts from Cumana SCSI 2 card
 * Params   : irq    - पूर्णांकerrupt number
 *	      dev_id - user-defined (Scsi_Host काष्ठाure)
 */
अटल irqवापस_t
cumanascsi_2_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cumanascsi2_info *info = dev_id;

	वापस fas216_पूर्णांकr(&info->info);
पूर्ण

/* Prototype: fasdmatype_t cumanascsi_2_dma_setup(host, SCpnt, direction, min_type)
 * Purpose  : initialises DMA/PIO
 * Params   : host      - host
 *	      SCpnt     - command
 *	      direction - DMA on to/off of card
 *	      min_type  - minimum DMA support that we must have क्रम this transfer
 * Returns  : type of transfer to be perक्रमmed
 */
अटल fasdmatype_t
cumanascsi_2_dma_setup(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp,
		       fasdmadir_t direction, fasdmatype_t min_type)
अणु
	काष्ठा cumanascsi2_info *info = (काष्ठा cumanascsi2_info *)host->hostdata;
	काष्ठा device *dev = scsi_get_device(host);
	पूर्णांक dmach = info->info.scsi.dma;

	ग_लिखोb(ALATCH_DIS_DMA, info->base + CUMANASCSI2_ALATCH);

	अगर (dmach != NO_DMA &&
	    (min_type == fasdma_real_all || SCp->this_residual >= 512)) अणु
		पूर्णांक bufs, map_dir, dma_dir, alatch_dir;

		bufs = copy_SCp_to_sg(&info->sg[0], SCp, NR_SG);

		अगर (direction == DMA_OUT) अणु
			map_dir = DMA_TO_DEVICE;
			dma_dir = DMA_MODE_WRITE;
			alatch_dir = ALATCH_DMA_OUT;
		पूर्ण अन्यथा अणु
			map_dir = DMA_FROM_DEVICE;
			dma_dir = DMA_MODE_READ;
			alatch_dir = ALATCH_DMA_IN;
		पूर्ण

		dma_map_sg(dev, info->sg, bufs, map_dir);

		disable_dma(dmach);
		set_dma_sg(dmach, info->sg, bufs);
		ग_लिखोb(alatch_dir, info->base + CUMANASCSI2_ALATCH);
		set_dma_mode(dmach, dma_dir);
		enable_dma(dmach);
		ग_लिखोb(ALATCH_ENA_DMA, info->base + CUMANASCSI2_ALATCH);
		ग_लिखोb(ALATCH_DIS_BIT32, info->base + CUMANASCSI2_ALATCH);
		वापस fasdma_real_all;
	पूर्ण

	/*
	 * If we're not करोing DMA,
	 *  we'll करो pseuकरो DMA
	 */
	वापस fasdma_pio;
पूर्ण

/*
 * Prototype: व्योम cumanascsi_2_dma_pseuकरो(host, SCpnt, direction, transfer)
 * Purpose  : handles pseuकरो DMA
 * Params   : host      - host
 *	      SCpnt     - command
 *	      direction - DMA on to/off of card
 *	      transfer  - minimum number of bytes we expect to transfer
 */
अटल व्योम
cumanascsi_2_dma_pseuकरो(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp,
			fasdmadir_t direction, पूर्णांक transfer)
अणु
	काष्ठा cumanascsi2_info *info = (काष्ठा cumanascsi2_info *)host->hostdata;
	अचिन्हित पूर्णांक length;
	अचिन्हित अक्षर *addr;

	length = SCp->this_residual;
	addr = SCp->ptr;

	अगर (direction == DMA_OUT)
#अगर 0
		जबतक (length > 1) अणु
			अचिन्हित दीर्घ word;
			अचिन्हित पूर्णांक status = पढ़ोb(info->base + CUMANASCSI2_STATUS);

			अगर (status & STATUS_INT)
				जाओ end;

			अगर (!(status & STATUS_DRQ))
				जारी;

			word = *addr | *(addr + 1) << 8;
			ग_लिखोw(word, info->base + CUMANASCSI2_PSEUDODMA);
			addr += 2;
			length -= 2;
		पूर्ण
#अन्यथा
		prपूर्णांकk ("PSEUDO_OUT???\n");
#पूर्ण_अगर
	अन्यथा अणु
		अगर (transfer && (transfer & 255)) अणु
			जबतक (length >= 256) अणु
				अचिन्हित पूर्णांक status = पढ़ोb(info->base + CUMANASCSI2_STATUS);

				अगर (status & STATUS_INT)
					वापस;
	    
				अगर (!(status & STATUS_DRQ))
					जारी;

				पढ़ोsw(info->base + CUMANASCSI2_PSEUDODMA,
				       addr, 256 >> 1);
				addr += 256;
				length -= 256;
			पूर्ण
		पूर्ण

		जबतक (length > 0) अणु
			अचिन्हित दीर्घ word;
			अचिन्हित पूर्णांक status = पढ़ोb(info->base + CUMANASCSI2_STATUS);

			अगर (status & STATUS_INT)
				वापस;

			अगर (!(status & STATUS_DRQ))
				जारी;

			word = पढ़ोw(info->base + CUMANASCSI2_PSEUDODMA);
			*addr++ = word;
			अगर (--length > 0) अणु
				*addr++ = word >> 8;
				length --;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Prototype: पूर्णांक cumanascsi_2_dma_stop(host, SCpnt)
 * Purpose  : stops DMA/PIO
 * Params   : host  - host
 *	      SCpnt - command
 */
अटल व्योम
cumanascsi_2_dma_stop(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp)
अणु
	काष्ठा cumanascsi2_info *info = (काष्ठा cumanascsi2_info *)host->hostdata;
	अगर (info->info.scsi.dma != NO_DMA) अणु
		ग_लिखोb(ALATCH_DIS_DMA, info->base + CUMANASCSI2_ALATCH);
		disable_dma(info->info.scsi.dma);
	पूर्ण
पूर्ण

/* Prototype: स्थिर अक्षर *cumanascsi_2_info(काष्ठा Scsi_Host * host)
 * Purpose  : वापसs a descriptive string about this पूर्णांकerface,
 * Params   : host - driver host काष्ठाure to वापस info क्रम.
 * Returns  : poपूर्णांकer to a अटल buffer containing null terminated string.
 */
स्थिर अक्षर *cumanascsi_2_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा cumanascsi2_info *info = (काष्ठा cumanascsi2_info *)host->hostdata;
	अटल अक्षर string[150];

	प्र_लिखो(string, "%s (%s) in slot %d v%s terminators o%s",
		host->hostt->name, info->info.scsi.type, info->ec->slot_no,
		VERSION, info->terms ? "n" : "ff");

	वापस string;
पूर्ण

/* Prototype: पूर्णांक cumanascsi_2_set_proc_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
 * Purpose  : Set a driver specअगरic function
 * Params   : host   - host to setup
 *          : buffer - buffer containing string describing operation
 *          : length - length of string
 * Returns  : -EINVAL, or 0
 */
अटल पूर्णांक
cumanascsi_2_set_proc_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
अणु
	पूर्णांक ret = length;

	अगर (length >= 11 && म_भेदन(buffer, "CUMANASCSI2", 11) == 0) अणु
		buffer += 11;
		length -= 11;

		अगर (length >= 5 && म_भेदन(buffer, "term=", 5) == 0) अणु
			अगर (buffer[5] == '1')
				cumanascsi_2_terminator_ctl(host, 1);
			अन्यथा अगर (buffer[5] == '0')
				cumanascsi_2_terminator_ctl(host, 0);
			अन्यथा
				ret = -EINVAL;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cumanascsi_2_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	काष्ठा cumanascsi2_info *info;
	info = (काष्ठा cumanascsi2_info *)host->hostdata;

	seq_म_लिखो(m, "Cumana SCSI II driver v%s\n", VERSION);
	fas216_prपूर्णांक_host(&info->info, m);
	seq_म_लिखो(m, "Term    : o%s\n",
			info->terms ? "n" : "ff");

	fas216_prपूर्णांक_stats(&info->info, m);
	fas216_prपूर्णांक_devices(&info->info, m);
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cumanascsi2_ढाँचा = अणु
	.module				= THIS_MODULE,
	.show_info			= cumanascsi_2_show_info,
	.ग_लिखो_info			= cumanascsi_2_set_proc_info,
	.name				= "Cumana SCSI II",
	.info				= cumanascsi_2_info,
	.queuecommand			= fas216_queue_command,
	.eh_host_reset_handler		= fas216_eh_host_reset,
	.eh_bus_reset_handler		= fas216_eh_bus_reset,
	.eh_device_reset_handler	= fas216_eh_device_reset,
	.eh_पात_handler		= fas216_eh_पात,
	.can_queue			= 1,
	.this_id			= 7,
	.sg_tablesize			= SG_MAX_SEGMENTS,
	.dma_boundary			= IOMD_DMA_BOUNDARY,
	.proc_name			= "cumanascsi2",
पूर्ण;

अटल पूर्णांक cumanascsi2_probe(काष्ठा expansion_card *ec,
			     स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा cumanascsi2_info *info;
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

	host = scsi_host_alloc(&cumanascsi2_ढाँचा,
			       माप(काष्ठा cumanascsi2_info));
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ out_region;
	पूर्ण

	ecard_set_drvdata(ec, host);

	info = (काष्ठा cumanascsi2_info *)host->hostdata;
	info->ec	= ec;
	info->base	= base;

	cumanascsi_2_terminator_ctl(host, term[ec->slot_no]);

	info->info.scsi.io_base		= base + CUMANASCSI2_FAS216_OFFSET;
	info->info.scsi.io_shअगरt	= CUMANASCSI2_FAS216_SHIFT;
	info->info.scsi.irq		= ec->irq;
	info->info.scsi.dma		= ec->dma;
	info->info.अगरcfg.घड़ीrate	= 40; /* MHz */
	info->info.अगरcfg.select_समयout	= 255;
	info->info.अगरcfg.asyncperiod	= 200; /* ns */
	info->info.अगरcfg.sync_max_depth	= 7;
	info->info.अगरcfg.cntl3		= CNTL3_BS8 | CNTL3_FASTSCSI | CNTL3_FASTCLK;
	info->info.अगरcfg.disconnect_ok	= 1;
	info->info.अगरcfg.wide_max_size	= 0;
	info->info.अगरcfg.capabilities	= FASCAP_PSEUDODMA;
	info->info.dma.setup		= cumanascsi_2_dma_setup;
	info->info.dma.pseuकरो		= cumanascsi_2_dma_pseuकरो;
	info->info.dma.stop		= cumanascsi_2_dma_stop;

	ec->irqaddr	= info->base + CUMANASCSI2_STATUS;
	ec->irqmask	= STATUS_INT;

	ecard_setirq(ec, &cumanascsi_2_ops, info);

	ret = fas216_init(host);
	अगर (ret)
		जाओ out_मुक्त;

	ret = request_irq(ec->irq, cumanascsi_2_पूर्णांकr,
			  0, "cumanascsi2", info);
	अगर (ret) अणु
		prपूर्णांकk("scsi%d: IRQ%d not free: %d\n",
		       host->host_no, ec->irq, ret);
		जाओ out_release;
	पूर्ण

	अगर (info->info.scsi.dma != NO_DMA) अणु
		अगर (request_dma(info->info.scsi.dma, "cumanascsi2")) अणु
			prपूर्णांकk("scsi%d: DMA%d not free, using PIO\n",
			       host->host_no, info->info.scsi.dma);
			info->info.scsi.dma = NO_DMA;
		पूर्ण अन्यथा अणु
			set_dma_speed(info->info.scsi.dma, 180);
			info->info.अगरcfg.capabilities |= FASCAP_DMA;
		पूर्ण
	पूर्ण

	ret = fas216_add(host, &ec->dev);
	अगर (ret == 0)
		जाओ out;

	अगर (info->info.scsi.dma != NO_DMA)
		मुक्त_dma(info->info.scsi.dma);
	मुक्त_irq(ec->irq, info);

 out_release:
	fas216_release(host);

 out_मुक्त:
	scsi_host_put(host);

 out_region:
	ecard_release_resources(ec);

 out:
	वापस ret;
पूर्ण

अटल व्योम cumanascsi2_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	काष्ठा cumanascsi2_info *info = (काष्ठा cumanascsi2_info *)host->hostdata;

	ecard_set_drvdata(ec, शून्य);
	fas216_हटाओ(host);

	अगर (info->info.scsi.dma != NO_DMA)
		मुक्त_dma(info->info.scsi.dma);
	मुक्त_irq(ec->irq, info);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id cumanascsi2_cids[] = अणु
	अणु MANU_CUMANA, PROD_CUMANA_SCSI_2 पूर्ण,
	अणु 0xffff, 0xffff पूर्ण,
पूर्ण;

अटल काष्ठा ecard_driver cumanascsi2_driver = अणु
	.probe		= cumanascsi2_probe,
	.हटाओ		= cumanascsi2_हटाओ,
	.id_table	= cumanascsi2_cids,
	.drv = अणु
		.name		= "cumanascsi2",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init cumanascsi2_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&cumanascsi2_driver);
पूर्ण

अटल व्योम __निकास cumanascsi2_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&cumanascsi2_driver);
पूर्ण

module_init(cumanascsi2_init);
module_निकास(cumanascsi2_निकास);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("Cumana SCSI-2 driver for Acorn machines");
module_param_array(term, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(term, "SCSI bus termination");
MODULE_LICENSE("GPL");
