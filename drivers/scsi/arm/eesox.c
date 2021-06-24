<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/scsi/eesox.c
 *
 *  Copyright (C) 1997-2005 Russell King
 *
 *  This driver is based on experimentation.  Hence, it may have made
 *  assumptions about the particular card that I have available, and
 *  may not be reliable!
 *
 *  Changelog:
 *   01-10-1997	RMK		Created, READONLY version
 *   15-02-1998	RMK		READ/WRITE version
 *				added DMA support and hardware definitions
 *   14-03-1998	RMK		Updated DMA support
 *				Added terminator control
 *   15-04-1998	RMK		Only करो PIO अगर FAS216 will allow it.
 *   27-06-1998	RMK		Changed यंत्र/delay.h to linux/delay.h
 *   02-04-2000	RMK	0.0.3	Fixed NO_IRQ/NO_DMA problem, updated क्रम new
 *				error handling code.
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

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/ecard.h>

#समावेश "../scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "fas216.h"
#समावेश "scsi.h"

#समावेश <scsi/scsicam.h>

#घोषणा EESOX_FAS216_OFFSET	0x3000
#घोषणा EESOX_FAS216_SHIFT	5

#घोषणा EESOX_DMASTAT		0x2800
#घोषणा EESOX_STAT_INTR		0x01
#घोषणा EESOX_STAT_DMA		0x02

#घोषणा EESOX_CONTROL		0x2800
#घोषणा EESOX_INTR_ENABLE	0x04
#घोषणा EESOX_TERM_ENABLE	0x02
#घोषणा EESOX_RESET		0x01

#घोषणा EESOX_DMADATA		0x3800

#घोषणा VERSION "1.10 (17/01/2003 2.5.59)"

/*
 * Use term=0,1,0,0,0 to turn terminators on/off
 */
अटल पूर्णांक term[MAX_ECARDS] = अणु 1, 1, 1, 1, 1, 1, 1, 1 पूर्ण;

#घोषणा NR_SG	256

काष्ठा eesoxscsi_info अणु
	FAS216_Info		info;
	काष्ठा expansion_card	*ec;
	व्योम __iomem		*base;
	व्योम __iomem		*ctl_port;
	अचिन्हित पूर्णांक		control;
	काष्ठा scatterlist	sg[NR_SG];	/* Scatter DMA list	*/
पूर्ण;

/* Prototype: व्योम eesoxscsi_irqenable(ec, irqnr)
 * Purpose  : Enable पूर्णांकerrupts on EESOX SCSI card
 * Params   : ec    - expansion card काष्ठाure
 *          : irqnr - पूर्णांकerrupt number
 */
अटल व्योम
eesoxscsi_irqenable(काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)ec->irq_data;

	info->control |= EESOX_INTR_ENABLE;

	ग_लिखोb(info->control, info->ctl_port);
पूर्ण

/* Prototype: व्योम eesoxscsi_irqdisable(ec, irqnr)
 * Purpose  : Disable पूर्णांकerrupts on EESOX SCSI card
 * Params   : ec    - expansion card काष्ठाure
 *          : irqnr - पूर्णांकerrupt number
 */
अटल व्योम
eesoxscsi_irqdisable(काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)ec->irq_data;

	info->control &= ~EESOX_INTR_ENABLE;

	ग_लिखोb(info->control, info->ctl_port);
पूर्ण

अटल स्थिर expansioncard_ops_t eesoxscsi_ops = अणु
	.irqenable	= eesoxscsi_irqenable,
	.irqdisable	= eesoxscsi_irqdisable,
पूर्ण;

/* Prototype: व्योम eesoxscsi_terminator_ctl(*host, on_off)
 * Purpose  : Turn the EESOX SCSI terminators on or off
 * Params   : host   - card to turn on/off
 *          : on_off - !0 to turn on, 0 to turn off
 */
अटल व्योम
eesoxscsi_terminator_ctl(काष्ठा Scsi_Host *host, पूर्णांक on_off)
अणु
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(host->host_lock, flags);
	अगर (on_off)
		info->control |= EESOX_TERM_ENABLE;
	अन्यथा
		info->control &= ~EESOX_TERM_ENABLE;

	ग_लिखोb(info->control, info->ctl_port);
	spin_unlock_irqrestore(host->host_lock, flags);
पूर्ण

/* Prototype: व्योम eesoxscsi_पूर्णांकr(irq, *dev_id, *regs)
 * Purpose  : handle पूर्णांकerrupts from EESOX SCSI card
 * Params   : irq    - पूर्णांकerrupt number
 *	      dev_id - user-defined (Scsi_Host काष्ठाure)
 */
अटल irqवापस_t
eesoxscsi_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा eesoxscsi_info *info = dev_id;

	वापस fas216_पूर्णांकr(&info->info);
पूर्ण

/* Prototype: fasdmatype_t eesoxscsi_dma_setup(host, SCpnt, direction, min_type)
 * Purpose  : initialises DMA/PIO
 * Params   : host      - host
 *	      SCpnt     - command
 *	      direction - DMA on to/off of card
 *	      min_type  - minimum DMA support that we must have क्रम this transfer
 * Returns  : type of transfer to be perक्रमmed
 */
अटल fasdmatype_t
eesoxscsi_dma_setup(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp,
		       fasdmadir_t direction, fasdmatype_t min_type)
अणु
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;
	काष्ठा device *dev = scsi_get_device(host);
	पूर्णांक dmach = info->info.scsi.dma;

	अगर (dmach != NO_DMA &&
	    (min_type == fasdma_real_all || SCp->this_residual >= 512)) अणु
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
	 * We करोn't करो DMA, we only करो slow PIO
	 *
	 * Some day, we will करो Pseuकरो DMA
	 */
	वापस fasdma_pseuकरो;
पूर्ण

अटल व्योम eesoxscsi_buffer_in(व्योम *buf, पूर्णांक length, व्योम __iomem *base)
अणु
	स्थिर व्योम __iomem *reg_fas = base + EESOX_FAS216_OFFSET;
	स्थिर व्योम __iomem *reg_dmastat = base + EESOX_DMASTAT;
	स्थिर व्योम __iomem *reg_dmadata = base + EESOX_DMADATA;
	रेजिस्टर स्थिर अचिन्हित दीर्घ mask = 0xffff;

	करो अणु
		अचिन्हित पूर्णांक status;

		/*
		 * Interrupt request?
		 */
		status = पढ़ोb(reg_fas + (REG_STAT << EESOX_FAS216_SHIFT));
		अगर (status & STAT_INT)
			अवरोध;

		/*
		 * DMA request active?
		 */
		status = पढ़ोb(reg_dmastat);
		अगर (!(status & EESOX_STAT_DMA))
			जारी;

		/*
		 * Get number of bytes in FIFO
		 */
		status = पढ़ोb(reg_fas + (REG_CFIS << EESOX_FAS216_SHIFT)) & CFIS_CF;
		अगर (status > 16)
			status = 16;
		अगर (status > length)
			status = length;

		/*
		 * Align buffer.
		 */
		अगर (((u32)buf) & 2 && status >= 2) अणु
			*(u16 *)buf = पढ़ोl(reg_dmadata);
			buf += 2;
			status -= 2;
			length -= 2;
		पूर्ण

		अगर (status >= 8) अणु
			अचिन्हित दीर्घ l1, l2;

			l1 = पढ़ोl(reg_dmadata) & mask;
			l1 |= पढ़ोl(reg_dmadata) << 16;
			l2 = पढ़ोl(reg_dmadata) & mask;
			l2 |= पढ़ोl(reg_dmadata) << 16;
			*(u32 *)buf = l1;
			buf += 4;
			*(u32 *)buf = l2;
			buf += 4;
			length -= 8;
			जारी;
		पूर्ण

		अगर (status >= 4) अणु
			अचिन्हित दीर्घ l1;

			l1 = पढ़ोl(reg_dmadata) & mask;
			l1 |= पढ़ोl(reg_dmadata) << 16;

			*(u32 *)buf = l1;
			buf += 4;
			length -= 4;
			जारी;
		पूर्ण

		अगर (status >= 2) अणु
			*(u16 *)buf = पढ़ोl(reg_dmadata);
			buf += 2;
			length -= 2;
		पूर्ण
	पूर्ण जबतक (length);
पूर्ण

अटल व्योम eesoxscsi_buffer_out(व्योम *buf, पूर्णांक length, व्योम __iomem *base)
अणु
	स्थिर व्योम __iomem *reg_fas = base + EESOX_FAS216_OFFSET;
	स्थिर व्योम __iomem *reg_dmastat = base + EESOX_DMASTAT;
	व्योम __iomem *reg_dmadata = base + EESOX_DMADATA;

	करो अणु
		अचिन्हित पूर्णांक status;

		/*
		 * Interrupt request?
		 */
		status = पढ़ोb(reg_fas + (REG_STAT << EESOX_FAS216_SHIFT));
		अगर (status & STAT_INT)
			अवरोध;

		/*
		 * DMA request active?
		 */
		status = पढ़ोb(reg_dmastat);
		अगर (!(status & EESOX_STAT_DMA))
			जारी;

		/*
		 * Get number of bytes in FIFO
		 */
		status = पढ़ोb(reg_fas + (REG_CFIS << EESOX_FAS216_SHIFT)) & CFIS_CF;
		अगर (status > 16)
			status = 16;
		status = 16 - status;
		अगर (status > length)
			status = length;
		status &= ~1;

		/*
		 * Align buffer.
		 */
		अगर (((u32)buf) & 2 && status >= 2) अणु
			ग_लिखोl(*(u16 *)buf << 16, reg_dmadata);
			buf += 2;
			status -= 2;
			length -= 2;
		पूर्ण

		अगर (status >= 8) अणु
			अचिन्हित दीर्घ l1, l2;

			l1 = *(u32 *)buf;
			buf += 4;
			l2 = *(u32 *)buf;
			buf += 4;

			ग_लिखोl(l1 << 16, reg_dmadata);
			ग_लिखोl(l1, reg_dmadata);
			ग_लिखोl(l2 << 16, reg_dmadata);
			ग_लिखोl(l2, reg_dmadata);
			length -= 8;
			जारी;
		पूर्ण

		अगर (status >= 4) अणु
			अचिन्हित दीर्घ l1;

			l1 = *(u32 *)buf;
			buf += 4;

			ग_लिखोl(l1 << 16, reg_dmadata);
			ग_लिखोl(l1, reg_dmadata);
			length -= 4;
			जारी;
		पूर्ण

		अगर (status >= 2) अणु
			ग_लिखोl(*(u16 *)buf << 16, reg_dmadata);
			buf += 2;
			length -= 2;
		पूर्ण
	पूर्ण जबतक (length);
पूर्ण

अटल व्योम
eesoxscsi_dma_pseuकरो(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp,
		     fasdmadir_t dir, पूर्णांक transfer_size)
अणु
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;
	अगर (dir == DMA_IN) अणु
		eesoxscsi_buffer_in(SCp->ptr, SCp->this_residual, info->base);
	पूर्ण अन्यथा अणु
		eesoxscsi_buffer_out(SCp->ptr, SCp->this_residual, info->base);
	पूर्ण
पूर्ण

/* Prototype: पूर्णांक eesoxscsi_dma_stop(host, SCpnt)
 * Purpose  : stops DMA/PIO
 * Params   : host  - host
 *	      SCpnt - command
 */
अटल व्योम
eesoxscsi_dma_stop(काष्ठा Scsi_Host *host, काष्ठा scsi_poपूर्णांकer *SCp)
अणु
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;
	अगर (info->info.scsi.dma != NO_DMA)
		disable_dma(info->info.scsi.dma);
पूर्ण

/* Prototype: स्थिर अक्षर *eesoxscsi_info(काष्ठा Scsi_Host * host)
 * Purpose  : वापसs a descriptive string about this पूर्णांकerface,
 * Params   : host - driver host काष्ठाure to वापस info क्रम.
 * Returns  : poपूर्णांकer to a अटल buffer containing null terminated string.
 */
स्थिर अक्षर *eesoxscsi_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;
	अटल अक्षर string[150];

	प्र_लिखो(string, "%s (%s) in slot %d v%s terminators o%s",
		host->hostt->name, info->info.scsi.type, info->ec->slot_no,
		VERSION, info->control & EESOX_TERM_ENABLE ? "n" : "ff");

	वापस string;
पूर्ण

/* Prototype: पूर्णांक eesoxscsi_set_proc_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
 * Purpose  : Set a driver specअगरic function
 * Params   : host   - host to setup
 *          : buffer - buffer containing string describing operation
 *          : length - length of string
 * Returns  : -EINVAL, or 0
 */
अटल पूर्णांक
eesoxscsi_set_proc_info(काष्ठा Scsi_Host *host, अक्षर *buffer, पूर्णांक length)
अणु
	पूर्णांक ret = length;

	अगर (length >= 9 && म_भेदन(buffer, "EESOXSCSI", 9) == 0) अणु
		buffer += 9;
		length -= 9;

		अगर (length >= 5 && म_भेदन(buffer, "term=", 5) == 0) अणु
			अगर (buffer[5] == '1')
				eesoxscsi_terminator_ctl(host, 1);
			अन्यथा अगर (buffer[5] == '0')
				eesoxscsi_terminator_ctl(host, 0);
			अन्यथा
				ret = -EINVAL;
		पूर्ण अन्यथा
			ret = -EINVAL;
	पूर्ण अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक eesoxscsi_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	काष्ठा eesoxscsi_info *info;

	info = (काष्ठा eesoxscsi_info *)host->hostdata;

	seq_म_लिखो(m, "EESOX SCSI driver v%s\n", VERSION);
	fas216_prपूर्णांक_host(&info->info, m);
	seq_म_लिखो(m, "Term    : o%s\n",
			info->control & EESOX_TERM_ENABLE ? "n" : "ff");

	fas216_prपूर्णांक_stats(&info->info, m);
	fas216_prपूर्णांक_devices(&info->info, m);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार eesoxscsi_show_term(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;

	वापस प्र_लिखो(buf, "%d\n", info->control & EESOX_TERM_ENABLE ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार eesoxscsi_store_term(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;
	अचिन्हित दीर्घ flags;

	अगर (len > 1) अणु
		spin_lock_irqsave(host->host_lock, flags);
		अगर (buf[0] != '0') अणु
			info->control |= EESOX_TERM_ENABLE;
		पूर्ण अन्यथा अणु
			info->control &= ~EESOX_TERM_ENABLE;
		पूर्ण
		ग_लिखोb(info->control, info->ctl_port);
		spin_unlock_irqrestore(host->host_lock, flags);
	पूर्ण

	वापस len;
पूर्ण

अटल DEVICE_ATTR(bus_term, S_IRUGO | S_IWUSR,
		   eesoxscsi_show_term, eesoxscsi_store_term);

अटल काष्ठा scsi_host_ढाँचा eesox_ढाँचा = अणु
	.module				= THIS_MODULE,
	.show_info			= eesoxscsi_show_info,
	.ग_लिखो_info			= eesoxscsi_set_proc_info,
	.name				= "EESOX SCSI",
	.info				= eesoxscsi_info,
	.queuecommand			= fas216_queue_command,
	.eh_host_reset_handler		= fas216_eh_host_reset,
	.eh_bus_reset_handler		= fas216_eh_bus_reset,
	.eh_device_reset_handler	= fas216_eh_device_reset,
	.eh_पात_handler		= fas216_eh_पात,
	.can_queue			= 1,
	.this_id			= 7,
	.sg_tablesize			= SG_MAX_SEGMENTS,
	.dma_boundary			= IOMD_DMA_BOUNDARY,
	.proc_name			= "eesox",
पूर्ण;

अटल पूर्णांक eesoxscsi_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा eesoxscsi_info *info;
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

	host = scsi_host_alloc(&eesox_ढाँचा,
			       माप(काष्ठा eesoxscsi_info));
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ out_region;
	पूर्ण

	ecard_set_drvdata(ec, host);

	info = (काष्ठा eesoxscsi_info *)host->hostdata;
	info->ec	= ec;
	info->base	= base;
	info->ctl_port	= base + EESOX_CONTROL;
	info->control	= term[ec->slot_no] ? EESOX_TERM_ENABLE : 0;
	ग_लिखोb(info->control, info->ctl_port);

	info->info.scsi.io_base		= base + EESOX_FAS216_OFFSET;
	info->info.scsi.io_shअगरt	= EESOX_FAS216_SHIFT;
	info->info.scsi.irq		= ec->irq;
	info->info.scsi.dma		= ec->dma;
	info->info.अगरcfg.घड़ीrate	= 40; /* MHz */
	info->info.अगरcfg.select_समयout	= 255;
	info->info.अगरcfg.asyncperiod	= 200; /* ns */
	info->info.अगरcfg.sync_max_depth	= 7;
	info->info.अगरcfg.cntl3		= CNTL3_FASTSCSI | CNTL3_FASTCLK;
	info->info.अगरcfg.disconnect_ok	= 1;
	info->info.अगरcfg.wide_max_size	= 0;
	info->info.अगरcfg.capabilities	= FASCAP_PSEUDODMA;
	info->info.dma.setup		= eesoxscsi_dma_setup;
	info->info.dma.pseuकरो		= eesoxscsi_dma_pseuकरो;
	info->info.dma.stop		= eesoxscsi_dma_stop;

	ec->irqaddr	= base + EESOX_DMASTAT;
	ec->irqmask	= EESOX_STAT_INTR;

	ecard_setirq(ec, &eesoxscsi_ops, info);

	device_create_file(&ec->dev, &dev_attr_bus_term);

	ret = fas216_init(host);
	अगर (ret)
		जाओ out_मुक्त;

	ret = request_irq(ec->irq, eesoxscsi_पूर्णांकr, 0, "eesoxscsi", info);
	अगर (ret) अणु
		prपूर्णांकk("scsi%d: IRQ%d not free: %d\n",
		       host->host_no, ec->irq, ret);
		जाओ out_हटाओ;
	पूर्ण

	अगर (info->info.scsi.dma != NO_DMA) अणु
		अगर (request_dma(info->info.scsi.dma, "eesox")) अणु
			prपूर्णांकk("scsi%d: DMA%d not free, DMA disabled\n",
			       host->host_no, info->info.scsi.dma);
			info->info.scsi.dma = NO_DMA;
		पूर्ण अन्यथा अणु
			set_dma_speed(info->info.scsi.dma, 180);
			info->info.अगरcfg.capabilities |= FASCAP_DMA;
			info->info.अगरcfg.cntl3 |= CNTL3_BS8;
		पूर्ण
	पूर्ण

	ret = fas216_add(host, &ec->dev);
	अगर (ret == 0)
		जाओ out;

	अगर (info->info.scsi.dma != NO_DMA)
		मुक्त_dma(info->info.scsi.dma);
	मुक्त_irq(ec->irq, info);

 out_हटाओ:
	fas216_हटाओ(host);

 out_मुक्त:
	device_हटाओ_file(&ec->dev, &dev_attr_bus_term);
	scsi_host_put(host);

 out_region:
	ecard_release_resources(ec);

 out:
	वापस ret;
पूर्ण

अटल व्योम eesoxscsi_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा Scsi_Host *host = ecard_get_drvdata(ec);
	काष्ठा eesoxscsi_info *info = (काष्ठा eesoxscsi_info *)host->hostdata;

	ecard_set_drvdata(ec, शून्य);
	fas216_हटाओ(host);

	अगर (info->info.scsi.dma != NO_DMA)
		मुक्त_dma(info->info.scsi.dma);
	मुक्त_irq(ec->irq, info);

	device_हटाओ_file(&ec->dev, &dev_attr_bus_term);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id eesoxscsi_cids[] = अणु
	अणु MANU_EESOX, PROD_EESOX_SCSI2 पूर्ण,
	अणु 0xffff, 0xffff पूर्ण,
पूर्ण;

अटल काष्ठा ecard_driver eesoxscsi_driver = अणु
	.probe		= eesoxscsi_probe,
	.हटाओ		= eesoxscsi_हटाओ,
	.id_table	= eesoxscsi_cids,
	.drv = अणु
		.name		= "eesoxscsi",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init eesox_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&eesoxscsi_driver);
पूर्ण

अटल व्योम __निकास eesox_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&eesoxscsi_driver);
पूर्ण

module_init(eesox_init);
module_निकास(eesox_निकास);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("EESOX 'Fast' SCSI driver for Acorn machines");
module_param_array(term, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(term, "SCSI bus termination");
MODULE_LICENSE("GPL");
