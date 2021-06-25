<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/ata/pata_palmld.c
 *
 * Driver क्रम IDE channel in Palm LअगरeDrive
 *
 * Based on research of:
 *		Alex Osborne <ato@meshy.org>
 *
 * Reग_लिखो क्रम मुख्यline:
 *		Marek Vasut <marek.vasut@gmail.com>
 *
 * Rewritten version based on pata_ixp4xx_cf.c:
 * ixp4xx PATA/Compact Flash driver
 * Copyright (C) 2006-07 Tower Technologies
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/libata.h>
#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <scsi/scsi_host.h>
#समावेश <mach/palmld.h>

#घोषणा DRV_NAME "pata_palmld"

काष्ठा palmld_pata अणु
	काष्ठा ata_host *host;
	काष्ठा gpio_desc *घातer;
	काष्ठा gpio_desc *reset;
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा palmld_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations palmld_port_ops = अणु
	.inherits		= &ata_sff_port_ops,
	.sff_data_xfer		= ata_sff_data_xfer32,
	.cable_detect		= ata_cable_40wire,
पूर्ण;

अटल पूर्णांक palmld_pata_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmld_pata *lda;
	काष्ठा ata_port *ap;
	व्योम __iomem *mem;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	lda = devm_kzalloc(dev, माप(*lda), GFP_KERNEL);
	अगर (!lda)
		वापस -ENOMEM;

	/* allocate host */
	lda->host = ata_host_alloc(dev, 1);
	अगर (!lda->host)
		वापस -ENOMEM;

	/* remap drive's physical memory address */
	mem = devm_ioremap(dev, PALMLD_IDE_PHYS, 0x1000);
	अगर (!mem)
		वापस -ENOMEM;

	/* request and activate घातer and reset GPIOs */
	lda->घातer = devm_gpiod_get(dev, "power", GPIOD_OUT_HIGH);
	अगर (IS_ERR(lda->घातer))
		वापस PTR_ERR(lda->घातer);
	lda->reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(lda->reset)) अणु
		gpiod_set_value(lda->घातer, 0);
		वापस PTR_ERR(lda->reset);
	पूर्ण

	/* Assert reset to reset the drive */
	gpiod_set_value(lda->reset, 1);
	msleep(30);
	gpiod_set_value(lda->reset, 0);
	msleep(30);

	/* setup the ata port */
	ap = lda->host->ports[0];
	ap->ops	= &palmld_port_ops;
	ap->pio_mask = ATA_PIO4;
	ap->flags |= ATA_FLAG_PIO_POLLING;

	/* memory mapping vooकरोo */
	ap->ioaddr.cmd_addr = mem + 0x10;
	ap->ioaddr.altstatus_addr = mem + 0xe;
	ap->ioaddr.ctl_addr = mem + 0xe;

	/* start the port */
	ata_sff_std_ports(&ap->ioaddr);

	/* activate host */
	ret = ata_host_activate(lda->host, 0, शून्य, IRQF_TRIGGER_RISING,
				&palmld_sht);
	/* घातer करोwn on failure */
	अगर (ret) अणु
		gpiod_set_value(lda->घातer, 0);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lda);
	वापस 0;
पूर्ण

अटल पूर्णांक palmld_pata_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmld_pata *lda = platक्रमm_get_drvdata(pdev);

	ata_platक्रमm_हटाओ_one(pdev);

	/* घातer करोwn the HDD */
	gpiod_set_value(lda->घातer, 0);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver palmld_pata_platक्रमm_driver = अणु
	.driver	 = अणु
		.name   = DRV_NAME,
	पूर्ण,
	.probe		= palmld_pata_probe,
	.हटाओ		= palmld_pata_हटाओ,
पूर्ण;

module_platक्रमm_driver(palmld_pata_platक्रमm_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("PalmLD PATA driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
