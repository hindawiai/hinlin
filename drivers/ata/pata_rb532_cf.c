<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  A low-level PATA driver to handle a Compact Flash connected on the
 *  Mikrotik's RouterBoard 532 board.
 *
 *  Copyright (C) 2007 Gabor Juhos <juhosg at खोलोwrt.org>
 *  Copyright (C) 2008 Florian Fainelli <florian@खोलोwrt.org>
 *
 *  This file was based on: drivers/ata/pata_ixp4xx_cf.c
 *	Copyright (C) 2006-07 Tower Technologies
 *	Author: Alessandro Zummo <a.zummo@towertech.it>
 *
 *  Also was based on the driver क्रम Linux 2.4.xx published by Mikrotik क्रम
 *  their RouterBoard 1xx and 5xx series devices. The original Mikrotik code
 *  seems not to have a license.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <linux/libata.h>
#समावेश <scsi/scsi_host.h>

#समावेश <यंत्र/mach-rc32434/rb.h>

#घोषणा DRV_NAME	"pata-rb532-cf"
#घोषणा DRV_VERSION	"0.1.0"
#घोषणा DRV_DESC	"PATA driver for RouterBOARD 532 Compact Flash"

#घोषणा RB500_CF_MAXPORTS	1
#घोषणा RB500_CF_IO_DELAY	400

#घोषणा RB500_CF_REG_BASE	0x0800
#घोषणा RB500_CF_REG_ERR	0x080D
#घोषणा RB500_CF_REG_CTRL	0x080E
/* 32bit buffered data रेजिस्टर offset */
#घोषणा RB500_CF_REG_DBUF32	0x0C00

काष्ठा rb532_cf_info अणु
	व्योम __iomem	*iobase;
	काष्ठा gpio_desc *gpio_line;
	अचिन्हित पूर्णांक	irq;
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल irqवापस_t rb532_pata_irq_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *ah = dev_instance;
	काष्ठा rb532_cf_info *info = ah->निजी_data;

	अगर (gpiod_get_value(info->gpio_line)) अणु
		irq_set_irq_type(info->irq, IRQ_TYPE_LEVEL_LOW);
		ata_sff_पूर्णांकerrupt(info->irq, dev_instance);
	पूर्ण अन्यथा अणु
		irq_set_irq_type(info->irq, IRQ_TYPE_LEVEL_HIGH);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा ata_port_operations rb532_pata_port_ops = अणु
	.inherits		= &ata_sff_port_ops,
	.sff_data_xfer		= ata_sff_data_xfer32,
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल काष्ठा scsi_host_ढाँचा rb532_pata_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

/* ------------------------------------------------------------------------ */

अटल व्योम rb532_pata_setup_ports(काष्ठा ata_host *ah)
अणु
	काष्ठा rb532_cf_info *info = ah->निजी_data;
	काष्ठा ata_port *ap;

	ap = ah->ports[0];

	ap->ops		= &rb532_pata_port_ops;
	ap->pio_mask	= ATA_PIO4;

	ap->ioaddr.cmd_addr	= info->iobase + RB500_CF_REG_BASE;
	ap->ioaddr.ctl_addr	= info->iobase + RB500_CF_REG_CTRL;
	ap->ioaddr.altstatus_addr = info->iobase + RB500_CF_REG_CTRL;

	ata_sff_std_ports(&ap->ioaddr);

	ap->ioaddr.data_addr	= info->iobase + RB500_CF_REG_DBUF32;
	ap->ioaddr.error_addr	= info->iobase + RB500_CF_REG_ERR;
पूर्ण

अटल पूर्णांक rb532_pata_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq;
	काष्ठा gpio_desc *gpiod;
	काष्ठा resource *res;
	काष्ठा ata_host *ah;
	काष्ठा rb532_cf_info *info;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no IOMEM resource found\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		dev_err(&pdev->dev, "no IRQ resource found\n");
		वापस -ENOENT;
	पूर्ण

	gpiod = devm_gpiod_get(&pdev->dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(gpiod)) अणु
		dev_err(&pdev->dev, "no GPIO found for irq%d\n", irq);
		वापस PTR_ERR(gpiod);
	पूर्ण
	gpiod_set_consumer_name(gpiod, DRV_NAME);

	/* allocate host */
	ah = ata_host_alloc(&pdev->dev, RB500_CF_MAXPORTS);
	अगर (!ah)
		वापस -ENOMEM;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	ah->निजी_data = info;
	info->gpio_line = gpiod;
	info->irq = irq;

	info->iobase = devm_ioremap(&pdev->dev, res->start,
				resource_size(res));
	अगर (!info->iobase)
		वापस -ENOMEM;

	rb532_pata_setup_ports(ah);

	ret = ata_host_activate(ah, irq, rb532_pata_irq_handler,
				IRQF_TRIGGER_LOW, &rb532_pata_sht);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rb532_pata_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *ah = platक्रमm_get_drvdata(pdev);

	ata_host_detach(ah);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rb532_pata_platक्रमm_driver = अणु
	.probe		= rb532_pata_driver_probe,
	.हटाओ		= rb532_pata_driver_हटाओ,
	.driver	 = अणु
		.name   = DRV_NAME,
	पूर्ण,
पूर्ण;

#घोषणा DRV_INFO DRV_DESC " version " DRV_VERSION

module_platक्रमm_driver(rb532_pata_platक्रमm_driver);

MODULE_AUTHOR("Gabor Juhos <juhosg at openwrt.org>");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_DESCRIPTION(DRV_DESC);
MODULE_VERSION(DRV_VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
