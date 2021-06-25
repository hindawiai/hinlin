<शैली गुरु>
/*
 * Generic platक्रमm device PATA driver
 *
 * Copyright (C) 2006 - 2007  Paul Mundt
 *
 * Based on pata_pcmcia:
 *
 *   Copyright 2005-2006 Red Hat Inc, all rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>

#घोषणा DRV_NAME "pata_platform"
#घोषणा DRV_VERSION "1.2"

अटल पूर्णांक pio_mask = 1;
module_param(pio_mask, पूर्णांक, 0);
MODULE_PARM_DESC(pio_mask, "PIO modes supported, mode 0 only by default");

/*
 * Provide our own set_mode() as we करोn't want to change anything that has
 * alपढ़ोy been configured..
 */
अटल पूर्णांक pata_platक्रमm_set_mode(काष्ठा ata_link *link, काष्ठा ata_device **unused)
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

अटल काष्ठा scsi_host_ढाँचा pata_platक्रमm_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल व्योम pata_platक्रमm_setup_port(काष्ठा ata_ioports *ioaddr,
				     अचिन्हित पूर्णांक shअगरt)
अणु
	/* Fixup the port shअगरt क्रम platक्रमms that need it */
	ioaddr->data_addr	= ioaddr->cmd_addr + (ATA_REG_DATA    << shअगरt);
	ioaddr->error_addr	= ioaddr->cmd_addr + (ATA_REG_ERR     << shअगरt);
	ioaddr->feature_addr	= ioaddr->cmd_addr + (ATA_REG_FEATURE << shअगरt);
	ioaddr->nsect_addr	= ioaddr->cmd_addr + (ATA_REG_NSECT   << shअगरt);
	ioaddr->lbal_addr	= ioaddr->cmd_addr + (ATA_REG_LBAL    << shअगरt);
	ioaddr->lbam_addr	= ioaddr->cmd_addr + (ATA_REG_LBAM    << shअगरt);
	ioaddr->lbah_addr	= ioaddr->cmd_addr + (ATA_REG_LBAH    << shअगरt);
	ioaddr->device_addr	= ioaddr->cmd_addr + (ATA_REG_DEVICE  << shअगरt);
	ioaddr->status_addr	= ioaddr->cmd_addr + (ATA_REG_STATUS  << shअगरt);
	ioaddr->command_addr	= ioaddr->cmd_addr + (ATA_REG_CMD     << shअगरt);
पूर्ण

/**
 *	__pata_platक्रमm_probe		-	attach a platक्रमm पूर्णांकerface
 *	@dev: device
 *	@io_res: Resource representing I/O base
 *	@ctl_res: Resource representing CTL base
 *	@irq_res: Resource representing IRQ and its flags
 *	@ioport_shअगरt: I/O port shअगरt
 *	@__pio_mask: PIO mask
 *	@sht: scsi_host_ढाँचा to use when रेजिस्टरing
 *	@use16bit: Flag to indicate 16-bit IO instead of 32-bit
 *
 *	Register a platक्रमm bus IDE पूर्णांकerface. Such पूर्णांकerfaces are PIO and we
 *	assume करो not support IRQ sharing.
 *
 *	Platक्रमm devices are expected to contain at least 2 resources per port:
 *
 *		- I/O Base (IORESOURCE_IO or IORESOURCE_MEM)
 *		- CTL Base (IORESOURCE_IO or IORESOURCE_MEM)
 *
 *	and optionally:
 *
 *		- IRQ	   (IORESOURCE_IRQ)
 *
 *	If the base resources are both mem types, the ioremap() is handled
 *	here. For IORESOURCE_IO, it's assumed that there's no remapping
 *	necessary.
 *
 *	If no IRQ resource is present, PIO polling mode is used instead.
 */
पूर्णांक __pata_platक्रमm_probe(काष्ठा device *dev, काष्ठा resource *io_res,
			  काष्ठा resource *ctl_res, काष्ठा resource *irq_res,
			  अचिन्हित पूर्णांक ioport_shअगरt, पूर्णांक __pio_mask,
			  काष्ठा scsi_host_ढाँचा *sht, bool use16bit)
अणु
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	अचिन्हित पूर्णांक mmio;
	पूर्णांक irq = 0;
	पूर्णांक irq_flags = 0;

	/*
	 * Check क्रम MMIO
	 */
	mmio = (( io_res->flags == IORESOURCE_MEM) &&
		(ctl_res->flags == IORESOURCE_MEM));

	/*
	 * And the IRQ
	 */
	अगर (irq_res && irq_res->start > 0) अणु
		irq = irq_res->start;
		irq_flags = (irq_res->flags & IRQF_TRIGGER_MASK) | IRQF_SHARED;
	पूर्ण

	/*
	 * Now that that's out of the way, wire up the port..
	 */
	host = ata_host_alloc(dev, 1);
	अगर (!host)
		वापस -ENOMEM;
	ap = host->ports[0];

	ap->ops = devm_kzalloc(dev, माप(*ap->ops), GFP_KERNEL);
	ap->ops->inherits = &ata_sff_port_ops;
	ap->ops->cable_detect = ata_cable_unknown;
	ap->ops->set_mode = pata_platक्रमm_set_mode;
	अगर (use16bit)
		ap->ops->sff_data_xfer = ata_sff_data_xfer;
	अन्यथा
		ap->ops->sff_data_xfer = ata_sff_data_xfer32;

	ap->pio_mask = __pio_mask;
	ap->flags |= ATA_FLAG_SLAVE_POSS;

	/*
	 * Use polling mode अगर there's no IRQ
	 */
	अगर (!irq) अणु
		ap->flags |= ATA_FLAG_PIO_POLLING;
		ata_port_desc(ap, "no IRQ, using PIO polling");
	पूर्ण

	/*
	 * Handle the MMIO हाल
	 */
	अगर (mmio) अणु
		ap->ioaddr.cmd_addr = devm_ioremap(dev, io_res->start,
				resource_size(io_res));
		ap->ioaddr.ctl_addr = devm_ioremap(dev, ctl_res->start,
				resource_size(ctl_res));
	पूर्ण अन्यथा अणु
		ap->ioaddr.cmd_addr = devm_ioport_map(dev, io_res->start,
				resource_size(io_res));
		ap->ioaddr.ctl_addr = devm_ioport_map(dev, ctl_res->start,
				resource_size(ctl_res));
	पूर्ण
	अगर (!ap->ioaddr.cmd_addr || !ap->ioaddr.ctl_addr) अणु
		dev_err(dev, "failed to map IO/CTL base\n");
		वापस -ENOMEM;
	पूर्ण

	ap->ioaddr.altstatus_addr = ap->ioaddr.ctl_addr;

	pata_platक्रमm_setup_port(&ap->ioaddr, ioport_shअगरt);

	ata_port_desc(ap, "%s cmd 0x%llx ctl 0x%llx", mmio ? "mmio" : "ioport",
		      (अचिन्हित दीर्घ दीर्घ)io_res->start,
		      (अचिन्हित दीर्घ दीर्घ)ctl_res->start);

	/* activate */
	वापस ata_host_activate(host, irq, irq ? ata_sff_पूर्णांकerrupt : शून्य,
				 irq_flags, sht);
पूर्ण
EXPORT_SYMBOL_GPL(__pata_platक्रमm_probe);

अटल पूर्णांक pata_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *io_res;
	काष्ठा resource *ctl_res;
	काष्ठा resource *irq_res;
	काष्ठा pata_platक्रमm_info *pp_info = dev_get_platdata(&pdev->dev);

	/*
	 * Simple resource validation ..
	 */
	अगर ((pdev->num_resources != 3) && (pdev->num_resources != 2)) अणु
		dev_err(&pdev->dev, "invalid number of resources\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Get the I/O base first
	 */
	io_res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (io_res == शून्य) अणु
		io_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (unlikely(io_res == शून्य))
			वापस -EINVAL;
	पूर्ण

	/*
	 * Then the CTL base
	 */
	ctl_res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 1);
	अगर (ctl_res == शून्य) अणु
		ctl_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		अगर (unlikely(ctl_res == शून्य))
			वापस -EINVAL;
	पूर्ण

	/*
	 * And the IRQ
	 */
	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);

	वापस __pata_platक्रमm_probe(&pdev->dev, io_res, ctl_res, irq_res,
				     pp_info ? pp_info->ioport_shअगरt : 0,
				     pio_mask, &pata_platक्रमm_sht, false);
पूर्ण

अटल काष्ठा platक्रमm_driver pata_platक्रमm_driver = अणु
	.probe		= pata_platक्रमm_probe,
	.हटाओ		= ata_platक्रमm_हटाओ_one,
	.driver = अणु
		.name		= DRV_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pata_platक्रमm_driver);

MODULE_AUTHOR("Paul Mundt");
MODULE_DESCRIPTION("low-level driver for platform device ATA");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:" DRV_NAME);
