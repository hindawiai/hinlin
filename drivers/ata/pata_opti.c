<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_opti.c 	- ATI PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *
 * Based on
 *  linux/drivers/ide/pci/opti621.c		Version 0.7	Sept 10, 2002
 *
 *  Copyright (C) 1996-1998  Linus Torvalds & authors (see below)
 *
 * Authors:
 * Jaromir Koutek <miri@punknet.cz>,
 * Jan Harkes <jaharkes@cwi.nl>,
 * Mark Lord <mlord@pobox.com>
 * Some parts of code are from ali14xx.c and from rz1000.c.
 *
 * Also consulted the FreeBSD prototype driver by Kevin Day to try
 * and resolve some confusions. Further करोcumentation can be found in
 * Ralf Brown's पूर्णांकerrupt list
 *
 * If you have other variants of the Opti range (Viper/Vendetta) please
 * try this driver with those PCI idents and report back. For the later
 * chips see the pata_optidma driver
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_opti"
#घोषणा DRV_VERSION "0.2.9"

क्रमागत अणु
	READ_REG	= 0,	/* index of Read cycle timing रेजिस्टर */
	WRITE_REG 	= 1,	/* index of Write cycle timing रेजिस्टर */
	CNTRL_REG 	= 3,	/* index of Control रेजिस्टर */
	STRAP_REG 	= 5,	/* index of Strap रेजिस्टर */
	MISC_REG 	= 6	/* index of Miscellaneous रेजिस्टर */
पूर्ण;

/**
 *	opti_pre_reset		-	probe begin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Set up cable type and use generic probe init
 */

अटल पूर्णांक opti_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर काष्ठा pci_bits opti_enable_bits[] = अणु
		अणु 0x45, 1, 0x80, 0x00 पूर्ण,
		अणु 0x40, 1, 0x08, 0x00 पूर्ण
	पूर्ण;

	अगर (!pci_test_config_bits(pdev, &opti_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	opti_ग_लिखो_reg		-	control रेजिस्टर setup
 *	@ap: ATA port
 *	@val: value
 *	@reg: control रेजिस्टर number
 *
 *	The Opti uses magic 'trapdoor' रेजिस्टर accesses to करो configuration
 *	rather than using PCI space as other controllers करो. The द्विगुन inw
 *	on the error रेजिस्टर activates configuration mode. We can then ग_लिखो
 *	the control रेजिस्टर
 */

अटल व्योम opti_ग_लिखो_reg(काष्ठा ata_port *ap, u8 val, पूर्णांक reg)
अणु
	व्योम __iomem *regio = ap->ioaddr.cmd_addr;

	/* These 3 unlock the control रेजिस्टर access */
	ioपढ़ो16(regio + 1);
	ioपढ़ो16(regio + 1);
	ioग_लिखो8(3, regio + 2);

	/* Do the I/O */
	ioग_लिखो8(val, regio + reg);

	/* Relock */
	ioग_लिखो8(0x83, regio + 2);
पूर्ण

/**
 *	opti_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup. Timing numbers are taken from
 *	the FreeBSD driver then pre computed to keep the code clean. There
 *	are two tables depending on the hardware घड़ी speed.
 */

अटल व्योम opti_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	पूर्णांक घड़ी;
	पूर्णांक pio = adev->pio_mode - XFER_PIO_0;
	व्योम __iomem *regio = ap->ioaddr.cmd_addr;
	u8 addr;

	/* Address table precomputed with prefetch off and a DCLK of 2 */
	अटल स्थिर u8 addr_timing[2][5] = अणु
		अणु 0x30, 0x20, 0x20, 0x10, 0x10 पूर्ण,
		अणु 0x20, 0x20, 0x10, 0x10, 0x10 पूर्ण
	पूर्ण;
	अटल स्थिर u8 data_rec_timing[2][5] = अणु
		अणु 0x6B, 0x56, 0x42, 0x32, 0x31 पूर्ण,
		अणु 0x58, 0x44, 0x32, 0x22, 0x21 पूर्ण
	पूर्ण;

	ioग_लिखो8(0xff, regio + 5);
	घड़ी = ioपढ़ो16(regio + 5) & 1;

	/*
 	 *	As with many controllers the address setup समय is shared
 	 *	and must suit both devices अगर present.
	 */

	addr = addr_timing[घड़ी][pio];
	अगर (pair) अणु
		/* Hardware स्थिरraपूर्णांक */
		u8 pair_addr = addr_timing[घड़ी][pair->pio_mode - XFER_PIO_0];
		अगर (pair_addr > addr)
			addr = pair_addr;
	पूर्ण

	/* Commence primary programming sequence */
	opti_ग_लिखो_reg(ap, adev->devno, MISC_REG);
	opti_ग_लिखो_reg(ap, data_rec_timing[घड़ी][pio], READ_REG);
	opti_ग_लिखो_reg(ap, data_rec_timing[घड़ी][pio], WRITE_REG);
	opti_ग_लिखो_reg(ap, addr, MISC_REG);

	/* Programming sequence complete, override strapping */
	opti_ग_लिखो_reg(ap, 0x85, CNTRL_REG);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा opti_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations opti_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= opti_set_piomode,
	.prereset	= opti_pre_reset,
पूर्ण;

अटल पूर्णांक opti_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.port_ops = &opti_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	ata_prपूर्णांक_version_once(&dev->dev, DRV_VERSION);

	वापस ata_pci_sff_init_one(dev, ppi, &opti_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id opti[] = अणु
	अणु PCI_VDEVICE(OPTI, PCI_DEVICE_ID_OPTI_82C621), 0 पूर्ण,
	अणु PCI_VDEVICE(OPTI, PCI_DEVICE_ID_OPTI_82C825), 1 पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver opti_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= opti,
	.probe 		= opti_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(opti_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Opti 621/621X");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, opti);
MODULE_VERSION(DRV_VERSION);
