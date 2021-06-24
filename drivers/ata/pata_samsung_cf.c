<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * PATA driver क्रम Samsung SoCs.
 * Supports CF Interface in True IDE mode. Currently only PIO mode has been
 * implemented; UDMA support has to be added.
 *
 * Based on:
 *	PATA driver क्रम AT91SAM9260 Static Memory Controller
 *	PATA driver क्रम Toshiba SCC controller
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/libata.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/ata-samsung_cf.h>

#घोषणा DRV_NAME "pata_samsung_cf"
#घोषणा DRV_VERSION "0.1"

#घोषणा S3C_CFATA_REG(x)	(x)
#घोषणा S3C_CFATA_MUX		S3C_CFATA_REG(0x0)
#घोषणा S3C_ATA_CTRL		S3C_CFATA_REG(0x0)
#घोषणा S3C_ATA_CMD		S3C_CFATA_REG(0x8)
#घोषणा S3C_ATA_IRQ		S3C_CFATA_REG(0x10)
#घोषणा S3C_ATA_IRQ_MSK		S3C_CFATA_REG(0x14)
#घोषणा S3C_ATA_CFG		S3C_CFATA_REG(0x18)

#घोषणा S3C_ATA_PIO_TIME	S3C_CFATA_REG(0x2c)
#घोषणा S3C_ATA_PIO_DTR		S3C_CFATA_REG(0x54)
#घोषणा S3C_ATA_PIO_FED		S3C_CFATA_REG(0x58)
#घोषणा S3C_ATA_PIO_SCR		S3C_CFATA_REG(0x5c)
#घोषणा S3C_ATA_PIO_LLR		S3C_CFATA_REG(0x60)
#घोषणा S3C_ATA_PIO_LMR		S3C_CFATA_REG(0x64)
#घोषणा S3C_ATA_PIO_LHR		S3C_CFATA_REG(0x68)
#घोषणा S3C_ATA_PIO_DVR		S3C_CFATA_REG(0x6c)
#घोषणा S3C_ATA_PIO_CSD		S3C_CFATA_REG(0x70)
#घोषणा S3C_ATA_PIO_DAD		S3C_CFATA_REG(0x74)
#घोषणा S3C_ATA_PIO_RDATA	S3C_CFATA_REG(0x7c)

#घोषणा S3C_CFATA_MUX_TRUEIDE	0x01
#घोषणा S3C_ATA_CFG_SWAP	0x40
#घोषणा S3C_ATA_CFG_IORDYEN	0x02

क्रमागत s3c_cpu_type अणु
	TYPE_S3C64XX,
	TYPE_S5PV210,
पूर्ण;

/*
 * काष्ठा s3c_ide_info - S3C PATA instance.
 * @clk: The घड़ी resource क्रम this controller.
 * @ide_addr: The area mapped क्रम the hardware रेजिस्टरs.
 * @sfr_addr: The area mapped क्रम the special function रेजिस्टरs.
 * @irq: The IRQ number we are using.
 * @cpu_type: The exact type of this controller.
 * @fअगरo_status_reg: The ATA_FIFO_STATUS रेजिस्टर offset.
 */
काष्ठा s3c_ide_info अणु
	काष्ठा clk *clk;
	व्योम __iomem *ide_addr;
	व्योम __iomem *sfr_addr;
	पूर्णांक irq;
	क्रमागत s3c_cpu_type cpu_type;
	अचिन्हित पूर्णांक fअगरo_status_reg;
पूर्ण;

अटल व्योम pata_s3c_set_endian(व्योम __iomem *s3c_ide_regbase, u8 mode)
अणु
	u32 reg = पढ़ोl(s3c_ide_regbase + S3C_ATA_CFG);
	reg = mode ? (reg & ~S3C_ATA_CFG_SWAP) : (reg | S3C_ATA_CFG_SWAP);
	ग_लिखोl(reg, s3c_ide_regbase + S3C_ATA_CFG);
पूर्ण

अटल व्योम pata_s3c_cfg_mode(व्योम __iomem *s3c_ide_sfrbase)
अणु
	/* Select true-ide as the पूर्णांकernal operating mode */
	ग_लिखोl(पढ़ोl(s3c_ide_sfrbase + S3C_CFATA_MUX) | S3C_CFATA_MUX_TRUEIDE,
		s3c_ide_sfrbase + S3C_CFATA_MUX);
पूर्ण

अटल अचिन्हित दीर्घ
pata_s3c_setup_timing(काष्ठा s3c_ide_info *info, स्थिर काष्ठा ata_timing *ata)
अणु
	पूर्णांक t1 = ata->setup;
	पूर्णांक t2 = ata->act8b;
	पूर्णांक t2i = ata->rec8b;
	uदीर्घ pioसमय;

	pioसमय = ((t2i & 0xff) << 12) | ((t2 & 0xff) << 4) | (t1 & 0xf);

	वापस pioसमय;
पूर्ण

अटल व्योम pata_s3c_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा s3c_ide_info *info = ap->host->निजी_data;
	काष्ठा ata_timing timing;
	पूर्णांक cycle_समय;
	uदीर्घ ata_cfg = पढ़ोl(info->ide_addr + S3C_ATA_CFG);
	uदीर्घ pioसमय;

	/* Enables IORDY अगर mode requires it */
	अगर (ata_pio_need_iordy(adev))
		ata_cfg |= S3C_ATA_CFG_IORDYEN;
	अन्यथा
		ata_cfg &= ~S3C_ATA_CFG_IORDYEN;

	cycle_समय = (पूर्णांक)(1000000000UL / clk_get_rate(info->clk));

	ata_timing_compute(adev, adev->pio_mode, &timing,
					cycle_समय * 1000, 0);

	pioसमय = pata_s3c_setup_timing(info, &timing);

	ग_लिखोl(ata_cfg, info->ide_addr + S3C_ATA_CFG);
	ग_लिखोl(pioसमय, info->ide_addr + S3C_ATA_PIO_TIME);
पूर्ण

/*
 * Waits until the IDE controller is able to perक्रमm next पढ़ो/ग_लिखो
 * operation to the disk. Needed क्रम 64XX series boards only.
 */
अटल पूर्णांक रुको_क्रम_host_पढ़ोy(काष्ठा s3c_ide_info *info)
अणु
	uदीर्घ समयout;
	व्योम __iomem *fअगरo_reg = info->ide_addr + info->fअगरo_status_reg;

	/* रुको क्रम maximum of 20 msec */
	समयout = jअगरfies + msecs_to_jअगरfies(20);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर ((पढ़ोl(fअगरo_reg) >> 28) == 0)
			वापस 0;
	पूर्ण
	वापस -EBUSY;
पूर्ण

/*
 * Writes to one of the task file रेजिस्टरs.
 */
अटल व्योम ata_outb(काष्ठा ata_host *host, u8 addr, व्योम __iomem *reg)
अणु
	काष्ठा s3c_ide_info *info = host->निजी_data;

	रुको_क्रम_host_पढ़ोy(info);
	ग_लिखोb(addr, reg);
पूर्ण

/*
 * Reads from one of the task file रेजिस्टरs.
 */
अटल u8 ata_inb(काष्ठा ata_host *host, व्योम __iomem *reg)
अणु
	काष्ठा s3c_ide_info *info = host->निजी_data;
	u8 temp;

	रुको_क्रम_host_पढ़ोy(info);
	(व्योम) पढ़ोb(reg);
	रुको_क्रम_host_पढ़ोy(info);
	temp = पढ़ोb(info->ide_addr + S3C_ATA_PIO_RDATA);
	वापस temp;
पूर्ण

/*
 * pata_s3c_tf_load - send taskfile रेजिस्टरs to host controller
 */
अटल व्योम pata_s3c_tf_load(काष्ठा ata_port *ap,
				स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;

	अगर (tf->ctl != ap->last_ctl) अणु
		ata_outb(ap->host, tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
		ata_रुको_idle(ap);
	पूर्ण

	अगर (is_addr && (tf->flags & ATA_TFLAG_LBA48)) अणु
		ata_outb(ap->host, tf->hob_feature, ioaddr->feature_addr);
		ata_outb(ap->host, tf->hob_nsect, ioaddr->nsect_addr);
		ata_outb(ap->host, tf->hob_lbal, ioaddr->lbal_addr);
		ata_outb(ap->host, tf->hob_lbam, ioaddr->lbam_addr);
		ata_outb(ap->host, tf->hob_lbah, ioaddr->lbah_addr);
	पूर्ण

	अगर (is_addr) अणु
		ata_outb(ap->host, tf->feature, ioaddr->feature_addr);
		ata_outb(ap->host, tf->nsect, ioaddr->nsect_addr);
		ata_outb(ap->host, tf->lbal, ioaddr->lbal_addr);
		ata_outb(ap->host, tf->lbam, ioaddr->lbam_addr);
		ata_outb(ap->host, tf->lbah, ioaddr->lbah_addr);
	पूर्ण

	अगर (tf->flags & ATA_TFLAG_DEVICE)
		ata_outb(ap->host, tf->device, ioaddr->device_addr);

	ata_रुको_idle(ap);
पूर्ण

/*
 * pata_s3c_tf_पढ़ो - input device's ATA taskfile shaकरोw रेजिस्टरs
 */
अटल व्योम pata_s3c_tf_पढ़ो(काष्ठा ata_port *ap, काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	tf->feature = ata_inb(ap->host, ioaddr->error_addr);
	tf->nsect = ata_inb(ap->host, ioaddr->nsect_addr);
	tf->lbal = ata_inb(ap->host, ioaddr->lbal_addr);
	tf->lbam = ata_inb(ap->host, ioaddr->lbam_addr);
	tf->lbah = ata_inb(ap->host, ioaddr->lbah_addr);
	tf->device = ata_inb(ap->host, ioaddr->device_addr);

	अगर (tf->flags & ATA_TFLAG_LBA48) अणु
		ata_outb(ap->host, tf->ctl | ATA_HOB, ioaddr->ctl_addr);
		tf->hob_feature = ata_inb(ap->host, ioaddr->error_addr);
		tf->hob_nsect = ata_inb(ap->host, ioaddr->nsect_addr);
		tf->hob_lbal = ata_inb(ap->host, ioaddr->lbal_addr);
		tf->hob_lbam = ata_inb(ap->host, ioaddr->lbam_addr);
		tf->hob_lbah = ata_inb(ap->host, ioaddr->lbah_addr);
		ata_outb(ap->host, tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
	पूर्ण
पूर्ण

/*
 * pata_s3c_exec_command - issue ATA command to host controller
 */
अटल व्योम pata_s3c_exec_command(काष्ठा ata_port *ap,
				स्थिर काष्ठा ata_taskfile *tf)
अणु
	ata_outb(ap->host, tf->command, ap->ioaddr.command_addr);
	ata_sff_छोड़ो(ap);
पूर्ण

/*
 * pata_s3c_check_status - Read device status रेजिस्टर
 */
अटल u8 pata_s3c_check_status(काष्ठा ata_port *ap)
अणु
	वापस ata_inb(ap->host, ap->ioaddr.status_addr);
पूर्ण

/*
 * pata_s3c_check_altstatus - Read alternate device status रेजिस्टर
 */
अटल u8 pata_s3c_check_altstatus(काष्ठा ata_port *ap)
अणु
	वापस ata_inb(ap->host, ap->ioaddr.altstatus_addr);
पूर्ण

/*
 * pata_s3c_data_xfer - Transfer data by PIO
 */
अटल अचिन्हित पूर्णांक pata_s3c_data_xfer(काष्ठा ata_queued_cmd *qc,
				अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_port *ap = qc->dev->link->ap;
	काष्ठा s3c_ide_info *info = ap->host->निजी_data;
	व्योम __iomem *data_addr = ap->ioaddr.data_addr;
	अचिन्हित पूर्णांक words = buflen >> 1, i;
	u16 *data_ptr = (u16 *)buf;

	/* Requires रुको same as in ata_inb/ata_outb */
	अगर (rw == READ)
		क्रम (i = 0; i < words; i++, data_ptr++) अणु
			रुको_क्रम_host_पढ़ोy(info);
			(व्योम) पढ़ोw(data_addr);
			रुको_क्रम_host_पढ़ोy(info);
			*data_ptr = पढ़ोw(info->ide_addr
					+ S3C_ATA_PIO_RDATA);
		पूर्ण
	अन्यथा
		क्रम (i = 0; i < words; i++, data_ptr++) अणु
			रुको_क्रम_host_पढ़ोy(info);
			ग_लिखोw(*data_ptr, data_addr);
		पूर्ण

	अगर (buflen & 0x01)
		dev_err(ap->dev, "unexpected trailing data\n");

	वापस words << 1;
पूर्ण

/*
 * pata_s3c_dev_select - Select device on ATA bus
 */
अटल व्योम pata_s3c_dev_select(काष्ठा ata_port *ap, अचिन्हित पूर्णांक device)
अणु
	u8 पंचांगp = ATA_DEVICE_OBS;

	अगर (device != 0)
		पंचांगp |= ATA_DEV1;

	ata_outb(ap->host, पंचांगp, ap->ioaddr.device_addr);
	ata_sff_छोड़ो(ap);
पूर्ण

/*
 * pata_s3c_devchk - PATA device presence detection
 */
अटल अचिन्हित पूर्णांक pata_s3c_devchk(काष्ठा ata_port *ap,
				अचिन्हित पूर्णांक device)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	u8 nsect, lbal;

	pata_s3c_dev_select(ap, device);

	ata_outb(ap->host, 0x55, ioaddr->nsect_addr);
	ata_outb(ap->host, 0xaa, ioaddr->lbal_addr);

	ata_outb(ap->host, 0xaa, ioaddr->nsect_addr);
	ata_outb(ap->host, 0x55, ioaddr->lbal_addr);

	ata_outb(ap->host, 0x55, ioaddr->nsect_addr);
	ata_outb(ap->host, 0xaa, ioaddr->lbal_addr);

	nsect = ata_inb(ap->host, ioaddr->nsect_addr);
	lbal = ata_inb(ap->host, ioaddr->lbal_addr);

	अगर ((nsect == 0x55) && (lbal == 0xaa))
		वापस 1;	/* we found a device */

	वापस 0;		/* nothing found */
पूर्ण

/*
 * pata_s3c_रुको_after_reset - रुको क्रम devices to become पढ़ोy after reset
 */
अटल पूर्णांक pata_s3c_रुको_after_reset(काष्ठा ata_link *link,
		अचिन्हित दीर्घ deadline)
अणु
	पूर्णांक rc;

	ata_msleep(link->ap, ATA_WAIT_AFTER_RESET);

	/* always check पढ़ोiness of the master device */
	rc = ata_sff_रुको_पढ़ोy(link, deadline);
	/* -ENODEV means the odd clown क्रमgot the D7 pullकरोwn resistor
	 * and TF status is 0xff, bail out on it too.
	 */
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

/*
 * pata_s3c_bus_softreset - PATA device software reset
 */
अटल पूर्णांक pata_s3c_bus_softreset(काष्ठा ata_port *ap,
		अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

	/* software reset.  causes dev0 to be selected */
	ata_outb(ap->host, ap->ctl, ioaddr->ctl_addr);
	udelay(20);
	ata_outb(ap->host, ap->ctl | ATA_SRST, ioaddr->ctl_addr);
	udelay(20);
	ata_outb(ap->host, ap->ctl, ioaddr->ctl_addr);
	ap->last_ctl = ap->ctl;

	वापस pata_s3c_रुको_after_reset(&ap->link, deadline);
पूर्ण

/*
 * pata_s3c_softreset - reset host port via ATA SRST
 */
अटल पूर्णांक pata_s3c_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes,
			 अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	अचिन्हित पूर्णांक devmask = 0;
	पूर्णांक rc;
	u8 err;

	/* determine अगर device 0 is present */
	अगर (pata_s3c_devchk(ap, 0))
		devmask |= (1 << 0);

	/* select device 0 again */
	pata_s3c_dev_select(ap, 0);

	/* issue bus reset */
	rc = pata_s3c_bus_softreset(ap, deadline);
	/* अगर link is occupied, -ENODEV too is an error */
	अगर (rc && rc != -ENODEV) अणु
		ata_link_err(link, "SRST failed (errno=%d)\n", rc);
		वापस rc;
	पूर्ण

	/* determine by signature whether we have ATA or ATAPI devices */
	classes[0] = ata_sff_dev_classअगरy(&ap->link.device[0],
					  devmask & (1 << 0), &err);

	वापस 0;
पूर्ण

/*
 * pata_s3c_set_devctl - Write device control रेजिस्टर
 */
अटल व्योम pata_s3c_set_devctl(काष्ठा ata_port *ap, u8 ctl)
अणु
	ata_outb(ap->host, ctl, ap->ioaddr.ctl_addr);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा pata_s3c_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations pata_s3c_port_ops = अणु
	.inherits		= &ata_sff_port_ops,
	.sff_check_status	= pata_s3c_check_status,
	.sff_check_altstatus    = pata_s3c_check_altstatus,
	.sff_tf_load		= pata_s3c_tf_load,
	.sff_tf_पढ़ो		= pata_s3c_tf_पढ़ो,
	.sff_data_xfer		= pata_s3c_data_xfer,
	.sff_exec_command	= pata_s3c_exec_command,
	.sff_dev_select         = pata_s3c_dev_select,
	.sff_set_devctl         = pata_s3c_set_devctl,
	.softreset		= pata_s3c_softreset,
	.set_piomode		= pata_s3c_set_piomode,
पूर्ण;

अटल काष्ठा ata_port_operations pata_s5p_port_ops = अणु
	.inherits		= &ata_sff_port_ops,
	.set_piomode		= pata_s3c_set_piomode,
पूर्ण;

अटल व्योम pata_s3c_enable(व्योम __iomem *s3c_ide_regbase, bool state)
अणु
	u32 temp = पढ़ोl(s3c_ide_regbase + S3C_ATA_CTRL);
	temp = state ? (temp | 1) : (temp & ~1);
	ग_लिखोl(temp, s3c_ide_regbase + S3C_ATA_CTRL);
पूर्ण

अटल irqवापस_t pata_s3c_irq(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा s3c_ide_info *info = host->निजी_data;
	u32 reg;

	reg = पढ़ोl(info->ide_addr + S3C_ATA_IRQ);
	ग_लिखोl(reg, info->ide_addr + S3C_ATA_IRQ);

	वापस ata_sff_पूर्णांकerrupt(irq, dev_instance);
पूर्ण

अटल व्योम pata_s3c_hwinit(काष्ठा s3c_ide_info *info,
				काष्ठा s3c_ide_platdata *pdata)
अणु
	चयन (info->cpu_type) अणु
	हाल TYPE_S3C64XX:
		/* Configure as big endian */
		pata_s3c_cfg_mode(info->sfr_addr);
		pata_s3c_set_endian(info->ide_addr, 1);
		pata_s3c_enable(info->ide_addr, true);
		msleep(100);

		/* Remove IRQ Status */
		ग_लिखोl(0x1f, info->ide_addr + S3C_ATA_IRQ);
		ग_लिखोl(0x1b, info->ide_addr + S3C_ATA_IRQ_MSK);
		अवरोध;

	हाल TYPE_S5PV210:
		/* Configure as little endian */
		pata_s3c_set_endian(info->ide_addr, 0);
		pata_s3c_enable(info->ide_addr, true);
		msleep(100);

		/* Remove IRQ Status */
		ग_लिखोl(0x3f, info->ide_addr + S3C_ATA_IRQ);
		ग_लिखोl(0x3f, info->ide_addr + S3C_ATA_IRQ_MSK);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक __init pata_s3c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_ide_platdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा s3c_ide_info *info;
	काष्ठा resource *res;
	काष्ठा ata_port *ap;
	काष्ठा ata_host *host;
	क्रमागत s3c_cpu_type cpu_type;
	पूर्णांक ret;

	cpu_type = platक्रमm_get_device_id(pdev)->driver_data;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->irq = platक्रमm_get_irq(pdev, 0);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	info->ide_addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(info->ide_addr))
		वापस PTR_ERR(info->ide_addr);

	info->clk = devm_clk_get(&pdev->dev, "cfcon");
	अगर (IS_ERR(info->clk)) अणु
		dev_err(dev, "failed to get access to cf controller clock\n");
		ret = PTR_ERR(info->clk);
		info->clk = शून्य;
		वापस ret;
	पूर्ण

	clk_enable(info->clk);

	/* init ata host */
	host = ata_host_alloc(dev, 1);
	अगर (!host) अणु
		dev_err(dev, "failed to allocate ide host\n");
		ret = -ENOMEM;
		जाओ stop_clk;
	पूर्ण

	ap = host->ports[0];
	ap->pio_mask = ATA_PIO4;

	अगर (cpu_type == TYPE_S3C64XX) अणु
		ap->ops = &pata_s3c_port_ops;
		info->sfr_addr = info->ide_addr + 0x1800;
		info->ide_addr += 0x1900;
		info->fअगरo_status_reg = 0x94;
	पूर्ण अन्यथा अणु
		ap->ops = &pata_s5p_port_ops;
		info->fअगरo_status_reg = 0x84;
	पूर्ण

	info->cpu_type = cpu_type;

	अगर (info->irq <= 0) अणु
		ap->flags |= ATA_FLAG_PIO_POLLING;
		info->irq = 0;
		ata_port_desc(ap, "no IRQ, using PIO polling\n");
	पूर्ण

	ap->ioaddr.cmd_addr =  info->ide_addr + S3C_ATA_CMD;
	ap->ioaddr.data_addr = info->ide_addr + S3C_ATA_PIO_DTR;
	ap->ioaddr.error_addr = info->ide_addr + S3C_ATA_PIO_FED;
	ap->ioaddr.feature_addr = info->ide_addr + S3C_ATA_PIO_FED;
	ap->ioaddr.nsect_addr = info->ide_addr + S3C_ATA_PIO_SCR;
	ap->ioaddr.lbal_addr = info->ide_addr + S3C_ATA_PIO_LLR;
	ap->ioaddr.lbam_addr = info->ide_addr + S3C_ATA_PIO_LMR;
	ap->ioaddr.lbah_addr = info->ide_addr + S3C_ATA_PIO_LHR;
	ap->ioaddr.device_addr = info->ide_addr + S3C_ATA_PIO_DVR;
	ap->ioaddr.status_addr = info->ide_addr + S3C_ATA_PIO_CSD;
	ap->ioaddr.command_addr = info->ide_addr + S3C_ATA_PIO_CSD;
	ap->ioaddr.altstatus_addr = info->ide_addr + S3C_ATA_PIO_DAD;
	ap->ioaddr.ctl_addr = info->ide_addr + S3C_ATA_PIO_DAD;

	ata_port_desc(ap, "mmio cmd 0x%llx ",
			(अचिन्हित दीर्घ दीर्घ)res->start);

	host->निजी_data = info;

	अगर (pdata && pdata->setup_gpio)
		pdata->setup_gpio();

	/* Set endianness and enable the पूर्णांकerface */
	pata_s3c_hwinit(info, pdata);

	ret = ata_host_activate(host, info->irq,
				info->irq ? pata_s3c_irq : शून्य,
				0, &pata_s3c_sht);
	अगर (ret)
		जाओ stop_clk;

	वापस 0;

stop_clk:
	clk_disable(info->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक __निकास pata_s3c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा s3c_ide_info *info = host->निजी_data;

	ata_host_detach(host);

	clk_disable(info->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pata_s3c_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);

	वापस ata_host_suspend(host, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक pata_s3c_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा s3c_ide_platdata *pdata = dev_get_platdata(dev);
	काष्ठा s3c_ide_info *info = host->निजी_data;

	pata_s3c_hwinit(info, pdata);
	ata_host_resume(host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops pata_s3c_pm_ops = अणु
	.suspend	= pata_s3c_suspend,
	.resume		= pata_s3c_resume,
पूर्ण;
#पूर्ण_अगर

/* driver device registration */
अटल स्थिर काष्ठा platक्रमm_device_id pata_s3c_driver_ids[] = अणु
	अणु
		.name		= "s3c64xx-pata",
		.driver_data	= TYPE_S3C64XX,
	पूर्ण, अणु
		.name		= "s5pv210-pata",
		.driver_data	= TYPE_S5PV210,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, pata_s3c_driver_ids);

अटल काष्ठा platक्रमm_driver pata_s3c_driver = अणु
	.हटाओ		= __निकास_p(pata_s3c_हटाओ),
	.id_table	= pata_s3c_driver_ids,
	.driver		= अणु
		.name	= DRV_NAME,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &pata_s3c_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(pata_s3c_driver, pata_s3c_probe);

MODULE_AUTHOR("Abhilash Kesavan, <a.kesavan@samsung.com>");
MODULE_DESCRIPTION("low-level driver for Samsung PATA controller");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
