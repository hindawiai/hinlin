<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Amiga Gayle PATA controller driver
 *
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Based on gayle.c:
 *
 *     Created 12 Jul 1997 by Geert Uytterhoeven
 */

#समावेश <linux/ata.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/libata.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/zorro.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_host.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigayle.h>
#समावेश <यंत्र/ide.h>
#समावेश <यंत्र/setup.h>

#घोषणा DRV_NAME "pata_gayle"
#घोषणा DRV_VERSION "0.1.0"

#घोषणा GAYLE_CONTROL	0x101a

अटल काष्ठा scsi_host_ढाँचा pata_gayle_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

/* FIXME: is this needed? */
अटल अचिन्हित पूर्णांक pata_gayle_data_xfer(काष्ठा ata_queued_cmd *qc,
					 अचिन्हित अक्षर *buf,
					 अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_port *ap = dev->link->ap;
	व्योम __iomem *data_addr = ap->ioaddr.data_addr;
	अचिन्हित पूर्णांक words = buflen >> 1;

	/* Transfer multiple of 2 bytes */
	अगर (rw == READ)
		raw_insw((u16 *)data_addr, (u16 *)buf, words);
	अन्यथा
		raw_outsw((u16 *)data_addr, (u16 *)buf, words);

	/* Transfer trailing byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		अचिन्हित अक्षर pad[2] = अणु पूर्ण;

		/* Poपूर्णांक buf to the tail of buffer */
		buf += buflen - 1;

		अगर (rw == READ) अणु
			raw_insw((u16 *)data_addr, (u16 *)pad, 1);
			*buf = pad[0];
		पूर्ण अन्यथा अणु
			pad[0] = *buf;
			raw_outsw((u16 *)data_addr, (u16 *)pad, 1);
		पूर्ण
		words++;
	पूर्ण

	वापस words << 1;
पूर्ण

/*
 * Provide our own set_mode() as we करोn't want to change anything that has
 * alपढ़ोy been configured..
 */
अटल पूर्णांक pata_gayle_set_mode(काष्ठा ata_link *link,
			       काष्ठा ata_device **unused)
अणु
	काष्ठा ata_device *dev;

	ata_क्रम_each_dev(dev, link, ENABLED) अणु
		/* We करोn't really care */
		dev->pio_mode = dev->xfer_mode = XFER_PIO_0;
		dev->xfer_shअगरt = ATA_SHIFT_PIO;
		dev->flags |= ATA_DFLAG_PIO;
		ata_dev_info(dev, "configured for PIO\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल bool pata_gayle_irq_check(काष्ठा ata_port *ap)
अणु
	u8 ch;

	ch = z_पढ़ोb((अचिन्हित दीर्घ)ap->निजी_data);

	वापस !!(ch & GAYLE_IRQ_IDE);
पूर्ण

अटल व्योम pata_gayle_irq_clear(काष्ठा ata_port *ap)
अणु
	(व्योम)z_पढ़ोb((अचिन्हित दीर्घ)ap->ioaddr.status_addr);
	z_ग_लिखोb(0x7c, (अचिन्हित दीर्घ)ap->निजी_data);
पूर्ण

अटल काष्ठा ata_port_operations pata_gayle_a1200_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.sff_data_xfer	= pata_gayle_data_xfer,
	.sff_irq_check	= pata_gayle_irq_check,
	.sff_irq_clear	= pata_gayle_irq_clear,
	.cable_detect	= ata_cable_unknown,
	.set_mode	= pata_gayle_set_mode,
पूर्ण;

अटल काष्ठा ata_port_operations pata_gayle_a4000_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.sff_data_xfer	= pata_gayle_data_xfer,
	.cable_detect	= ata_cable_unknown,
	.set_mode	= pata_gayle_set_mode,
पूर्ण;

अटल पूर्णांक __init pata_gayle_init_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा gayle_ide_platक्रमm_data *pdata;
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	व्योम __iomem *base;
	पूर्णांक ret;

	pdata = dev_get_platdata(&pdev->dev);

	dev_info(&pdev->dev, "Amiga Gayle IDE controller (A%u style)\n",
		pdata->explicit_ack ? 1200 : 4000);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), DRV_NAME)) अणु
		pr_err(DRV_NAME ": resources busy\n");
		वापस -EBUSY;
	पूर्ण

	/* allocate host */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;

	ap = host->ports[0];

	अगर (pdata->explicit_ack)
		ap->ops = &pata_gayle_a1200_ops;
	अन्यथा
		ap->ops = &pata_gayle_a4000_ops;

	ap->pio_mask = ATA_PIO4;
	ap->flags |= ATA_FLAG_SLAVE_POSS | ATA_FLAG_NO_IORDY;

	base = ZTWO_VADDR(pdata->base);
	ap->ioaddr.data_addr		= base;
	ap->ioaddr.error_addr		= base + 2 + 1 * 4;
	ap->ioaddr.feature_addr		= base + 2 + 1 * 4;
	ap->ioaddr.nsect_addr		= base + 2 + 2 * 4;
	ap->ioaddr.lbal_addr		= base + 2 + 3 * 4;
	ap->ioaddr.lbam_addr		= base + 2 + 4 * 4;
	ap->ioaddr.lbah_addr		= base + 2 + 5 * 4;
	ap->ioaddr.device_addr		= base + 2 + 6 * 4;
	ap->ioaddr.status_addr		= base + 2 + 7 * 4;
	ap->ioaddr.command_addr		= base + 2 + 7 * 4;

	ap->ioaddr.altstatus_addr	= base + GAYLE_CONTROL;
	ap->ioaddr.ctl_addr		= base + GAYLE_CONTROL;

	ap->निजी_data = (व्योम *)ZTWO_VADDR(pdata->irqport);

	ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx", pdata->base,
		      pdata->base + GAYLE_CONTROL);

	ret = ata_host_activate(host, IRQ_AMIGA_PORTS, ata_sff_पूर्णांकerrupt,
				IRQF_SHARED, &pata_gayle_sht);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, host);

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास pata_gayle_हटाओ_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);

	ata_host_detach(host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pata_gayle_driver = अणु
	.हटाओ = __निकास_p(pata_gayle_हटाओ_one),
	.driver   = अणु
		.name	= "amiga-gayle-ide",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(pata_gayle_driver, pata_gayle_init_one);

MODULE_AUTHOR("Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("low-level driver for Amiga Gayle PATA");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:amiga-gayle-ide");
MODULE_VERSION(DRV_VERSION);
