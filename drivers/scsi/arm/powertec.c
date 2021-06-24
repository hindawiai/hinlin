<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/scsi/घातertec.c
 *
 *  Copyright (C) 1997-2005 Russell King
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

#घोषणा POWERTEC_FAS216_OFFSET	0x3000
#घोषणा POWERTEC_FAS216_SHIFT	6

#घोषणा POWERTEC_INTR_STATUS	0x2000
#घोषणा POWERTEC_INTR_BIT	0x80

#घोषणा POWERTEC_RESET_CONTROL	0x1018
#घोषणा POWERTEC_RESET_BIT	1

#घोषणा POWERTEC_TERM_CONTROL	0x2018
#घोषणा POWERTEC_TERM_ENABLE	1

#घोषणा POWERTEC_INTR_CONTROL	0x101c
#घोषणा POWERTEC_INTR_ENABLE	1
#घोषणा POWERTEC_INTR_DISABLE	0

#घोषणा VERSION	"1.10 (19/01/2003 2.5.59)"

/*
 * Use term=0,1,0,0,0 to turn terminators on/off.
 * One entry per slot.
 */
अटल पूर्णांक term[MAX_ECARDS] = अणु 1, 1, 1, 1, 1, 1, 1, 1 पूर्ण;

#घोषणा NR_SG	256

काष्ठा घातertec_info अणु
	FAS216_Info		info;
	काष्ठा expansion_card	*ec;
	व्योम __iomem		*base;
	अचिन्हित पूर्णांक		term_ctl;
	काष्ठा scatterlist	sg[NR_SG];
पूर्ण;

/* Prototype: व्योम घातertecscsi_irqenable(ec, irqnr)
 * Purpose  : Enable पूर्णांकerrupts on Powertec SCSI card
 * Params   : ec    - expansion card काष्ठाure
 *          : irqnr - पूर्णांकerrupt number
 */
अटल व्योम
घातertecscsi_irqenable(काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा घातertec_info *info = ec->irq_data;
	ग_लिखोb(POWERTEC_INTR_ENABLE, info->base + POWERTEC_INTR_CONTROL);
पूर्ण

/* Prototype: व्योम घातertecscsi_irqdisable(ec, irqnr)
 * Purpose  : Disable पूर्णांकerrupts on Powertec SCSI card
 * Params   : ec    - expansion card काष्ठाure
 *          : irqnr - पूर्णांकerrupt number
 */
अटल व्योम
घातertecscsi_irqdisable(काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा घातertec_info *info = ec->irq_data;
	ग_लिखोb(POWERTEC_INTR_DISABLE, info->base + POWERTEC_INTR_CONTROL);
पूर्ण

अटल स्थिर expansioncard_ops_t घातertecscsi_ops = अणु
	.irqenable	= घातertecscsi_irqenable,
	.irqdisable	= घातertecscsi_irqdisable,
पूर्ण;

/* Prototype: व्योम घातertecscsi_terminator_ctl(host, on_off)
 * Purpose  : Turn the Powertec SCSI terminators on or off
 * Params   : host   - card to turn on/off
 *          : on_off - !0 to turn on, 0 to turn off
 */
अटल व्योम
घातertecscsi_terminator_ctl(काष्ठा Scsi_Host *host, पूर्णांक on_off)
अणु
	काष्ठा घातertec_info *info = (काष्ठा घातertec_info *)host->hostdata;

	info->term_ctl = on_off ? POWERTEC_TERM_ENABLE : 0;
	ग_लिखोb(info->term_ctl, info->base + POWERTEC_TERM_CONTROL);
पूर्ण

/* Prototype: व्योम घातertecscsi_पूर्णांकr(irq, *dev_id, *regs)
 * Purpose  : handle पूर्णांकerrupts from Powertec SCSI card
 * Params   : irq    - पूर्णांकerrupt number
 *	      dev_id - user-defined (Scsi_Host काष्ठाure)
 */
अटल irqवापस_t घातertecscsi_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घातertec_info *info = dev_id;

	वापस fas216_पूर्णांकr(&info->info);
पूर्ण

/* Prototype: fasdmatype_t घातertecscsi_dma_setup(host, SCpnt, direction, min_type)
 * Purpose  : initialises DMA/PIO
 * Params   : host      - host
 *	      SCpnt     - command
 *	      direction - DMA on to/off of card
 *	      min_type  - minimum DMA support that we must have क्रम this transfer
 * Returns  : type of transfer to be perक्रमmed
 */
अटल fasdmatype_t
घातertecscsi_dma_setup(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp,
		       fasdmadir_t direction, fasdmatype_t min_type)
अणु
	काष्ठा घातertec_info *info = (काष्ठा घातertec_info *)host->hostdata;
	काष्ठा device *dev = scsi_get_device(host);
	पूर्णांक dmach = info->info.scsi.dma;

	अगर (info->info.अगरcfg.capabilities & FASCAP_DMA &&
	    min_type == fasdma_real_all) अणु
		पूर्णांक bufs, map_dir, dma_dir;

		bufs = copy_SCp_to_sg(&info->sg[0], SCp, NR_SG);

		अगर (direction == DMA_OUT) अणु
			map_dir = DMA_TO_DEVICE;
			dma_dir = DMA_MODE_WRITE;
		पूर्ण अन्यथा अणु
			map_dir = DMA_FROM_DEVICE;
			dma_dir = DMA_MODE_READ;
		पूर्ण

		dma_map_sg(dev, info->sg, bufs, map_dir);

		disable_dma(dmach);
		set_dma_sg(dmach, info->sg, bufs);
		set_dma_mode(dmach, dma_dir);
		enable_dma(dmach);
		वापस fasdma_real_all;
	पूर्ण

	/*
	 * If we're not करोing DMA,
	 *  we'll करो slow PIO
	 */
	वापस fasdma_pio;
पूर्ण

/* Prototype: पूर्णांक घातertecscsi_dma_stop(host, SCpnt)
 * Purpose  : stops DMA/PIO
 * Params   : host  - host
 *	      SCpnt - command
 */
अटल व्योम
घातertecscsi_dma_stop(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp)
अणु
	काष्ठा घातertec_info *info = (काष्ठा घातertec_info *)host->hostdata;
	अगर (info->info.scsi.dma != NO_DMA)
		disable_dma(info->info.scsi.dma);
पूर्ण

/* Prototype: स्थिर अक्षर *घातertecscsi_info(काष्ठा Scsi_Host * host)
 * Purpose  : वापसs a descriptive string about this पूर्णांकerface,
 * Params   : host - driver host काष्ठाure to वापस info क्रम.
 * Returns  : poपूर्णांकer to a अटल buffer containing null terminated string.
 */
स्थिर अक्षर *घातertecscsi_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा घातertec_info *info = (काष्ठा घातertec_info *)host->hostdata;
	अटल अक्षर string[150];

	प्र_लिखो(string, "%s (%s) in slot %d v%s terminators o%s",
		host->hostt->name, info->info.scsi.type, info->ec->slot_no,
		VERSION, info->term_ctl ? "n" : "ff");

	वापस string;
पूर्ण

/* Prototype: पूर्णांक घातertecscsi_set_proc_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
 * Purpose  : Set a driver specअगरic function
 * Params   : host   - host to setup
 *          : buffer - buffer containing string describing operation
 *          : length - length of string
 * Returns  : -EINVAL, or 0
 */
अटल पूर्णांक
घातertecscsi_set_proc_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
अणु
	पूर्णांक ret = length;

	अगर (length >= 12 && म_भेदन(buffer, "POWERTECSCSI", 12) == 0) अणु
		buffer += 12;
		length -= 12;

		अगर (length >= 5 && म_भेदन(buffer, "term=", 5) == 0) अणु
			अगर (buffer[5] == '1')
				घातertecscsi_terminator_ctl(host, 1);
			अन्यथा अगर (buffer[5] == '0')
				घातertecscsi_terminator_ctl(host, 0);
			अन्यथा
				ret = -EINVAL;
		पूर्ण अन्यथा
			ret = -EINVAL;
	पूर्ण अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

/* Prototype: पूर्णांक घातertecscsi_proc_info(अक्षर *buffer, अक्षर **start, off_t offset,
 *					पूर्णांक length, पूर्णांक host_no, पूर्णांक inout)
 * Purpose  : Return inक्रमmation about the driver to a user process accessing
 *	      the /proc fileप्रणाली.
 * Params   : buffer  - a buffer to ग_लिखो inक्रमmation to
 *	      start   - a poपूर्णांकer पूर्णांकo this buffer set by this routine to the start
 *		        of the required inक्रमmation.
 *	      offset  - offset पूर्णांकo inक्रमmation that we have पढ़ो up to.
 *	      length  - length of buffer
 *	      inout   - 0 क्रम पढ़ोing, 1 क्रम writing.
 * Returns  : length of data written to buffer.
 */
अटल पूर्णांक घातertecscsi_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	काष्ठा घातertec_info *info;

	info = (काष्ठा घातertec_info *)host->hostdata;

	seq_म_लिखो(m, "PowerTec SCSI driver v%s\n", VERSION);
	fas216_prपूर्णांक_host(&info->info, m);
	seq_म_लिखो(m, "Term    : o%s\n",
			info->term_ctl ? "n" : "ff");

	fas216_prपूर्णांक_stats(&info->info, m);
	fas216_prपूर्णांक_devices(&info->info, m);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार घातertecscsi_show_term(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	काष्ठा घातertec_info *info = (काष्ठा घातertec_info *)host->hostdata;

	वापस प्र_लिखो(buf, "%d\n", info->term_ctl ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार
घातertecscsi_store_term(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);

	अगर (len > 1)
		घातertecscsi_terminator_ctl(host, buf[0] != '0');

	वापस len;
पूर्ण

अटल DEVICE_ATTR(bus_term, S_IRUGO | S_IWUSR,
		   घातertecscsi_show_term, घातertecscsi_store_term);

अटल काष्ठा scsi_host_ढाँचा घातertecscsi_ढाँचा = अणु
	.module				= THIS_MODULE,
	.show_info			= घातertecscsi_show_info,
	.ग_लिखो_info			= घातertecscsi_set_proc_info,
	.name				= "PowerTec SCSI",
	.info				= घातertecscsi_info,
	.queuecommand			= fas216_queue_command,
	.eh_host_reset_handler		= fas216_eh_host_reset,
	.eh_bus_reset_handler		= fas216_eh_bus_reset,
	.eh_device_reset_handler	= fas216_eh_device_reset,
	.eh_पात_handler		= fas216_eh_पात,

	.can_queue			= 8,
	.this_id			= 7,
	.sg_tablesize			= SG_MAX_SEGMENTS,
	.dma_boundary			= IOMD_DMA_BOUNDARY,
	.cmd_per_lun			= 2,
	.proc_name			= "powertec",
पूर्ण;

अटल पूर्णांक घातertecscsi_probe(काष्ठा expansion_card *ec,
			      स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा घातertec_info *info;
	व्योम __iomem *base;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	base = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, 0);
	अगर (!base) अणु
		ret = -ENOMEM;
		जाओ out_region;
	पूर्ण

	host = scsi_host_alloc(&घातertecscsi_ढाँचा,
			       माप (काष्ठा घातertec_info));
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ out_region;
	पूर्ण

	ecard_set_drvdata(ec, host);

	info = (काष्ठा घातertec_info *)host->hostdata;
	info->base = base;
	घातertecscsi_terminator_ctl(host, term[ec->slot_no]);

	info->ec = ec;
	info->info.scsi.io_base		= base + POWERTEC_FAS216_OFFSET;
	info->info.scsi.io_shअगरt	= POWERTEC_FAS216_SHIFT;
	info->info.scsi.irq		= ec->irq;
	info->info.scsi.dma		= ec->dma;
	info->info.अगरcfg.घड़ीrate	= 40; /* MHz */
	info->info.अगरcfg.select_समयout	= 255;
	info->info.अगरcfg.asyncperiod	= 200; /* ns */
	info->info.अगरcfg.sync_max_depth	= 7;
	info->info.अगरcfg.cntl3		= CNTL3_BS8 | CNTL3_FASTSCSI | CNTL3_FASTCLK;
	info->info.अगरcfg.disconnect_ok	= 1;
	info->info.अगरcfg.wide_max_size	= 0;
	info->info.अगरcfg.capabilities	= 0;
	info->info.dma.setup		= घातertecscsi_dma_setup;
	info->info.dma.pseuकरो		= शून्य;
	info->info.dma.stop		= घातertecscsi_dma_stop;

	ec->irqaddr	= base + POWERTEC_INTR_STATUS;
	ec->irqmask	= POWERTEC_INTR_BIT;

	ecard_setirq(ec, &घातertecscsi_ops, info);

	device_create_file(&ec->dev, &dev_attr_bus_term);

	ret = fas216_init(host);
	अगर (ret)
		जाओ out_मुक्त;

	ret = request_irq(ec->irq, घातertecscsi_पूर्णांकr,
			  0, "powertec", info);
	अगर (ret) अणु
		prपूर्णांकk("scsi%d: IRQ%d not free: %d\n",
		       host->host_no, ec->irq, ret);
		जाओ out_release;
	पूर्ण

	अगर (info->info.scsi.dma != NO_DMA) अणु
		अगर (request_dma(info->info.scsi.dma, "powertec")) अणु
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
	device_हटाओ_file(&ec->dev, &dev_attr_bus_term);
	scsi_host_put(host);

 out_region:
	ecard_release_resources(ec);

 out:
	वापस ret;
पूर्ण

अटल व्योम घातertecscsi_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	काष्ठा घातertec_info *info = (काष्ठा घातertec_info *)host->hostdata;

	ecard_set_drvdata(ec, शून्य);
	fas216_हटाओ(host);

	device_हटाओ_file(&ec->dev, &dev_attr_bus_term);

	अगर (info->info.scsi.dma != NO_DMA)
		मुक्त_dma(info->info.scsi.dma);
	मुक्त_irq(ec->irq, info);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id घातertecscsi_cids[] = अणु
	अणु MANU_ALSYSTEMS, PROD_ALSYS_SCSIATAPI पूर्ण,
	अणु 0xffff, 0xffff पूर्ण,
पूर्ण;

अटल काष्ठा ecard_driver घातertecscsi_driver = अणु
	.probe		= घातertecscsi_probe,
	.हटाओ		= घातertecscsi_हटाओ,
	.id_table	= घातertecscsi_cids,
	.drv = अणु
		.name		= "powertecscsi",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init घातertecscsi_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&घातertecscsi_driver);
पूर्ण

अटल व्योम __निकास घातertecscsi_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&घातertecscsi_driver);
पूर्ण

module_init(घातertecscsi_init);
module_निकास(घातertecscsi_निकास);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("Powertec SCSI driver");
module_param_array(term, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(term, "SCSI bus termination");
MODULE_LICENSE("GPL");
