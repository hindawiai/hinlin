<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Atari Falcon PATA controller driver
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Based on falconide.c:
 *
 *     Created 12 Jul 1997 by Geert Uytterhoeven
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/atarihw.h>
#समावेश <यंत्र/atariपूर्णांकs.h>
#समावेश <यंत्र/atari_stdma.h>
#समावेश <यंत्र/ide.h>

#घोषणा DRV_NAME "pata_falcon"
#घोषणा DRV_VERSION "0.1.0"

#घोषणा ATA_HD_CONTROL	0x39

अटल काष्ठा scsi_host_ढाँचा pata_falcon_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल अचिन्हित पूर्णांक pata_falcon_data_xfer(काष्ठा ata_queued_cmd *qc,
					  अचिन्हित अक्षर *buf,
					  अचिन्हित पूर्णांक buflen, पूर्णांक rw)
अणु
	काष्ठा ata_device *dev = qc->dev;
	काष्ठा ata_port *ap = dev->link->ap;
	व्योम __iomem *data_addr = ap->ioaddr.data_addr;
	अचिन्हित पूर्णांक words = buflen >> 1;
	काष्ठा scsi_cmnd *cmd = qc->scsicmd;
	bool swap = 1;

	अगर (dev->class == ATA_DEV_ATA && cmd && cmd->request &&
	    !blk_rq_is_passthrough(cmd->request))
		swap = 0;

	/* Transfer multiple of 2 bytes */
	अगर (rw == READ) अणु
		अगर (swap)
			raw_insw_swapw((u16 *)data_addr, (u16 *)buf, words);
		अन्यथा
			raw_insw((u16 *)data_addr, (u16 *)buf, words);
	पूर्ण अन्यथा अणु
		अगर (swap)
			raw_outsw_swapw((u16 *)data_addr, (u16 *)buf, words);
		अन्यथा
			raw_outsw((u16 *)data_addr, (u16 *)buf, words);
	पूर्ण

	/* Transfer trailing byte, अगर any. */
	अगर (unlikely(buflen & 0x01)) अणु
		अचिन्हित अक्षर pad[2] = अणु पूर्ण;

		/* Poपूर्णांक buf to the tail of buffer */
		buf += buflen - 1;

		अगर (rw == READ) अणु
			अगर (swap)
				raw_insw_swapw((u16 *)data_addr, (u16 *)pad, 1);
			अन्यथा
				raw_insw((u16 *)data_addr, (u16 *)pad, 1);
			*buf = pad[0];
		पूर्ण अन्यथा अणु
			pad[0] = *buf;
			अगर (swap)
				raw_outsw_swapw((u16 *)data_addr, (u16 *)pad, 1);
			अन्यथा
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
अटल पूर्णांक pata_falcon_set_mode(काष्ठा ata_link *link,
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

अटल काष्ठा ata_port_operations pata_falcon_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.sff_data_xfer	= pata_falcon_data_xfer,
	.cable_detect	= ata_cable_unknown,
	.set_mode	= pata_falcon_set_mode,
पूर्ण;

अटल पूर्णांक __init pata_falcon_init_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	व्योम __iomem *base;

	dev_info(&pdev->dev, "Atari Falcon PATA controller\n");

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), DRV_NAME)) अणु
		dev_err(&pdev->dev, "resources busy\n");
		वापस -EBUSY;
	पूर्ण

	/* allocate host */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;
	ap = host->ports[0];

	ap->ops = &pata_falcon_ops;
	ap->pio_mask = ATA_PIO4;
	ap->flags |= ATA_FLAG_SLAVE_POSS | ATA_FLAG_NO_IORDY;
	ap->flags |= ATA_FLAG_PIO_POLLING;

	base = (व्योम __iomem *)res->start;
	ap->ioaddr.data_addr		= base;
	ap->ioaddr.error_addr		= base + 1 + 1 * 4;
	ap->ioaddr.feature_addr		= base + 1 + 1 * 4;
	ap->ioaddr.nsect_addr		= base + 1 + 2 * 4;
	ap->ioaddr.lbal_addr		= base + 1 + 3 * 4;
	ap->ioaddr.lbam_addr		= base + 1 + 4 * 4;
	ap->ioaddr.lbah_addr		= base + 1 + 5 * 4;
	ap->ioaddr.device_addr		= base + 1 + 6 * 4;
	ap->ioaddr.status_addr		= base + 1 + 7 * 4;
	ap->ioaddr.command_addr		= base + 1 + 7 * 4;

	ap->ioaddr.altstatus_addr	= base + ATA_HD_CONTROL;
	ap->ioaddr.ctl_addr		= base + ATA_HD_CONTROL;

	ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx", (अचिन्हित दीर्घ)base,
		      (अचिन्हित दीर्घ)base + ATA_HD_CONTROL);

	/* activate */
	वापस ata_host_activate(host, 0, शून्य, 0, &pata_falcon_sht);
पूर्ण

अटल पूर्णांक __निकास pata_falcon_हटाओ_one(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);

	ata_host_detach(host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pata_falcon_driver = अणु
	.हटाओ = __निकास_p(pata_falcon_हटाओ_one),
	.driver   = अणु
		.name	= "atari-falcon-ide",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(pata_falcon_driver, pata_falcon_init_one);

MODULE_AUTHOR("Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("low-level driver for Atari Falcon PATA");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:atari-falcon-ide");
MODULE_VERSION(DRV_VERSION);
