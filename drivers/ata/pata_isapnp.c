<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 *   pata-isapnp.c - ISA PnP PATA controller driver.
 *   Copyright 2005/2006 Red Hat Inc, all rights reserved.
 *
 *   Based in part on ide-pnp.c by Andrey Panin <pazke@करोnpac.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/isapnp.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_isapnp"
#घोषणा DRV_VERSION "0.2.5"

अटल काष्ठा scsi_host_ढाँचा isapnp_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations isapnp_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.cable_detect	= ata_cable_40wire,
पूर्ण;

अटल काष्ठा ata_port_operations isapnp_noalt_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.cable_detect	= ata_cable_40wire,
	/* No altstatus so we करोn't want to use the lost पूर्णांकerrupt poll */
	.lost_पूर्णांकerrupt = ATA_OP_शून्य,
पूर्ण;

/**
 *	isapnp_init_one		-	attach an isapnp पूर्णांकerface
 *	@idev: PnP device
 *	@dev_id: matching detect line
 *
 *	Register an ISA bus IDE पूर्णांकerface. Such पूर्णांकerfaces are PIO 0 and
 *	non shared IRQ.
 */

अटल पूर्णांक isapnp_init_one(काष्ठा pnp_dev *idev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	व्योम __iomem *cmd_addr, *ctl_addr;
	पूर्णांक irq = 0;
	irq_handler_t handler = शून्य;

	अगर (pnp_port_valid(idev, 0) == 0)
		वापस -ENODEV;

	अगर (pnp_irq_valid(idev, 0)) अणु
		irq = pnp_irq(idev, 0);
		handler = ata_sff_पूर्णांकerrupt;
	पूर्ण

	/* allocate host */
	host = ata_host_alloc(&idev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;

	/* acquire resources and fill host */
	cmd_addr = devm_ioport_map(&idev->dev, pnp_port_start(idev, 0), 8);
	अगर (!cmd_addr)
		वापस -ENOMEM;

	ap = host->ports[0];

	ap->ops = &isapnp_noalt_port_ops;
	ap->pio_mask = ATA_PIO0;
	ap->flags |= ATA_FLAG_SLAVE_POSS;

	ap->ioaddr.cmd_addr = cmd_addr;

	अगर (pnp_port_valid(idev, 1)) अणु
		ctl_addr = devm_ioport_map(&idev->dev,
					   pnp_port_start(idev, 1), 1);
		ap->ioaddr.altstatus_addr = ctl_addr;
		ap->ioaddr.ctl_addr = ctl_addr;
		ap->ops = &isapnp_port_ops;
	पूर्ण

	ata_sff_std_ports(&ap->ioaddr);

	ata_port_desc(ap, "cmd 0x%llx ctl 0x%llx",
		      (अचिन्हित दीर्घ दीर्घ)pnp_port_start(idev, 0),
		      (अचिन्हित दीर्घ दीर्घ)pnp_port_start(idev, 1));

	/* activate */
	वापस ata_host_activate(host, irq, handler, 0,
				 &isapnp_sht);
पूर्ण

/**
 *	isapnp_हटाओ_one	-	unplug an isapnp पूर्णांकerface
 *	@idev: PnP device
 *
 *	Remove a previously configured PnP ATA port. Called only on module
 *	unload events as the core करोes not currently deal with ISAPnP करोcking.
 */

अटल व्योम isapnp_हटाओ_one(काष्ठा pnp_dev *idev)
अणु
	काष्ठा device *dev = &idev->dev;
	काष्ठा ata_host *host = dev_get_drvdata(dev);

	ata_host_detach(host);
पूर्ण

अटल काष्ठा pnp_device_id isapnp_devices[] = अणु
  	/* Generic ESDI/IDE/ATA compatible hard disk controller */
	अणु.id = "PNP0600", .driver_data = 0पूर्ण,
	अणु.id = ""पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pnp, isapnp_devices);

अटल काष्ठा pnp_driver isapnp_driver = अणु
	.name		= DRV_NAME,
	.id_table	= isapnp_devices,
	.probe		= isapnp_init_one,
	.हटाओ		= isapnp_हटाओ_one,
पूर्ण;

module_pnp_driver(isapnp_driver);
MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for ISA PnP ATA");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
