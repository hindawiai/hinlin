<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999-2002	Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2007		MontaVista Software, Inc. <source@mvista.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "aec62xx"

काष्ठा chipset_bus_घड़ी_list_entry अणु
	u8 xfer_speed;
	u8 chipset_settings;
	u8 ultra_settings;
पूर्ण;

अटल स्थिर काष्ठा chipset_bus_घड़ी_list_entry aec6xxx_33_base [] = अणु
	अणु	XFER_UDMA_6,	0x31,	0x07	पूर्ण,
	अणु	XFER_UDMA_5,	0x31,	0x06	पूर्ण,
	अणु	XFER_UDMA_4,	0x31,	0x05	पूर्ण,
	अणु	XFER_UDMA_3,	0x31,	0x04	पूर्ण,
	अणु	XFER_UDMA_2,	0x31,	0x03	पूर्ण,
	अणु	XFER_UDMA_1,	0x31,	0x02	पूर्ण,
	अणु	XFER_UDMA_0,	0x31,	0x01	पूर्ण,

	अणु	XFER_MW_DMA_2,	0x31,	0x00	पूर्ण,
	अणु	XFER_MW_DMA_1,	0x31,	0x00	पूर्ण,
	अणु	XFER_MW_DMA_0,	0x0a,	0x00	पूर्ण,
	अणु	XFER_PIO_4,	0x31,	0x00	पूर्ण,
	अणु	XFER_PIO_3,	0x33,	0x00	पूर्ण,
	अणु	XFER_PIO_2,	0x08,	0x00	पूर्ण,
	अणु	XFER_PIO_1,	0x0a,	0x00	पूर्ण,
	अणु	XFER_PIO_0,	0x00,	0x00	पूर्ण,
	अणु	0,		0x00,	0x00	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा chipset_bus_घड़ी_list_entry aec6xxx_34_base [] = अणु
	अणु	XFER_UDMA_6,	0x41,	0x06	पूर्ण,
	अणु	XFER_UDMA_5,	0x41,	0x05	पूर्ण,
	अणु	XFER_UDMA_4,	0x41,	0x04	पूर्ण,
	अणु	XFER_UDMA_3,	0x41,	0x03	पूर्ण,
	अणु	XFER_UDMA_2,	0x41,	0x02	पूर्ण,
	अणु	XFER_UDMA_1,	0x41,	0x01	पूर्ण,
	अणु	XFER_UDMA_0,	0x41,	0x01	पूर्ण,

	अणु	XFER_MW_DMA_2,	0x41,	0x00	पूर्ण,
	अणु	XFER_MW_DMA_1,	0x42,	0x00	पूर्ण,
	अणु	XFER_MW_DMA_0,	0x7a,	0x00	पूर्ण,
	अणु	XFER_PIO_4,	0x41,	0x00	पूर्ण,
	अणु	XFER_PIO_3,	0x43,	0x00	पूर्ण,
	अणु	XFER_PIO_2,	0x78,	0x00	पूर्ण,
	अणु	XFER_PIO_1,	0x7a,	0x00	पूर्ण,
	अणु	XFER_PIO_0,	0x70,	0x00	पूर्ण,
	अणु	0,		0x00,	0x00	पूर्ण
पूर्ण;

/*
 * TO DO: active tuning and correction of cards without a bios.
 */
अटल u8 pci_bus_घड़ी_list (u8 speed, काष्ठा chipset_bus_घड़ी_list_entry * chipset_table)
अणु
	क्रम ( ; chipset_table->xfer_speed ; chipset_table++)
		अगर (chipset_table->xfer_speed == speed) अणु
			वापस chipset_table->chipset_settings;
		पूर्ण
	वापस chipset_table->chipset_settings;
पूर्ण

अटल u8 pci_bus_घड़ी_list_ultra (u8 speed, काष्ठा chipset_bus_घड़ी_list_entry * chipset_table)
अणु
	क्रम ( ; chipset_table->xfer_speed ; chipset_table++)
		अगर (chipset_table->xfer_speed == speed) अणु
			वापस chipset_table->ultra_settings;
		पूर्ण
	वापस chipset_table->ultra_settings;
पूर्ण

अटल व्योम aec6210_set_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	काष्ठा ide_host *host	= pci_get_drvdata(dev);
	काष्ठा chipset_bus_घड़ी_list_entry *bus_घड़ी = host->host_priv;
	u16 d_conf		= 0;
	u8 ultra = 0, ultra_conf = 0;
	u8 पंचांगp0 = 0, पंचांगp1 = 0, पंचांगp2 = 0;
	स्थिर u8 speed = drive->dma_mode;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/* 0x40|(2*drive->dn): Active, 0x41|(2*drive->dn): Recovery */
	pci_पढ़ो_config_word(dev, 0x40|(2*drive->dn), &d_conf);
	पंचांगp0 = pci_bus_घड़ी_list(speed, bus_घड़ी);
	d_conf = ((पंचांगp0 & 0xf0) << 4) | (पंचांगp0 & 0xf);
	pci_ग_लिखो_config_word(dev, 0x40|(2*drive->dn), d_conf);

	पंचांगp1 = 0x00;
	पंचांगp2 = 0x00;
	pci_पढ़ो_config_byte(dev, 0x54, &ultra);
	पंचांगp1 = ((0x00 << (2*drive->dn)) | (ultra & ~(3 << (2*drive->dn))));
	ultra_conf = pci_bus_घड़ी_list_ultra(speed, bus_घड़ी);
	पंचांगp2 = ((ultra_conf << (2*drive->dn)) | (पंचांगp1 & ~(3 << (2*drive->dn))));
	pci_ग_लिखो_config_byte(dev, 0x54, पंचांगp2);
	local_irq_restore(flags);
पूर्ण

अटल व्योम aec6260_set_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	काष्ठा ide_host *host	= pci_get_drvdata(dev);
	काष्ठा chipset_bus_घड़ी_list_entry *bus_घड़ी = host->host_priv;
	u8 unit			= drive->dn & 1;
	u8 पंचांगp1 = 0, पंचांगp2 = 0;
	u8 ultra = 0, drive_conf = 0, ultra_conf = 0;
	स्थिर u8 speed = drive->dma_mode;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/* high 4-bits: Active, low 4-bits: Recovery */
	pci_पढ़ो_config_byte(dev, 0x40|drive->dn, &drive_conf);
	drive_conf = pci_bus_घड़ी_list(speed, bus_घड़ी);
	pci_ग_लिखो_config_byte(dev, 0x40|drive->dn, drive_conf);

	pci_पढ़ो_config_byte(dev, (0x44|hwअगर->channel), &ultra);
	पंचांगp1 = ((0x00 << (4*unit)) | (ultra & ~(7 << (4*unit))));
	ultra_conf = pci_bus_घड़ी_list_ultra(speed, bus_घड़ी);
	पंचांगp2 = ((ultra_conf << (4*unit)) | (पंचांगp1 & ~(7 << (4*unit))));
	pci_ग_लिखो_config_byte(dev, (0x44|hwअगर->channel), पंचांगp2);
	local_irq_restore(flags);
पूर्ण

अटल व्योम aec_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	drive->dma_mode = drive->pio_mode;
	hwअगर->port_ops->set_dma_mode(hwअगर, drive);
पूर्ण

अटल पूर्णांक init_chipset_aec62xx(काष्ठा pci_dev *dev)
अणु
	/* These are necessary to get AEC6280 Macपूर्णांकosh cards to work */
	अगर ((dev->device == PCI_DEVICE_ID_ARTOP_ATP865) ||
	    (dev->device == PCI_DEVICE_ID_ARTOP_ATP865R)) अणु
		u8 reg49h = 0, reg4ah = 0;
		/* Clear reset and test bits.  */
		pci_पढ़ो_config_byte(dev, 0x49, &reg49h);
		pci_ग_लिखो_config_byte(dev, 0x49, reg49h & ~0x30);
		/* Enable chip पूर्णांकerrupt output.  */
		pci_पढ़ो_config_byte(dev, 0x4a, &reg4ah);
		pci_ग_लिखो_config_byte(dev, 0x4a, reg4ah & ~0x01);
		/* Enable burst mode. */
		pci_पढ़ो_config_byte(dev, 0x4a, &reg4ah);
		pci_ग_लिखो_config_byte(dev, 0x4a, reg4ah | 0x80);
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 atp86x_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u8 ata66 = 0, mask = hwअगर->channel ? 0x02 : 0x01;

	pci_पढ़ो_config_byte(dev, 0x49, &ata66);

	वापस (ata66 & mask) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops atp850_port_ops = अणु
	.set_pio_mode		= aec_set_pio_mode,
	.set_dma_mode		= aec6210_set_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops atp86x_port_ops = अणु
	.set_pio_mode		= aec_set_pio_mode,
	.set_dma_mode		= aec6260_set_mode,
	.cable_detect		= atp86x_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info aec62xx_chipsets[] = अणु
	अणु	/* 0: AEC6210 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_aec62xx,
		.enablebits	= अणुअणु0x4a,0x02,0x02पूर्ण, अणु0x4a,0x04,0x04पूर्णपूर्ण,
		.port_ops	= &atp850_port_ops,
		.host_flags	= IDE_HFLAG_SERIALIZE |
				  IDE_HFLAG_NO_ATAPI_DMA |
				  IDE_HFLAG_NO_DSC |
				  IDE_HFLAG_OFF_BOARD,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA2,
	पूर्ण,
	अणु	/* 1: AEC6260 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_aec62xx,
		.port_ops	= &atp86x_port_ops,
		.host_flags	= IDE_HFLAG_NO_ATAPI_DMA | IDE_HFLAG_NO_AUTODMA |
				  IDE_HFLAG_OFF_BOARD,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA4,
	पूर्ण,
	अणु	/* 2: AEC6260R */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_aec62xx,
		.enablebits	= अणुअणु0x4a,0x02,0x02पूर्ण, अणु0x4a,0x04,0x04पूर्णपूर्ण,
		.port_ops	= &atp86x_port_ops,
		.host_flags	= IDE_HFLAG_NO_ATAPI_DMA |
				  IDE_HFLAG_NON_BOOTABLE,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA4,
	पूर्ण,
	अणु	/* 3: AEC6280 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_aec62xx,
		.port_ops	= &atp86x_port_ops,
		.host_flags	= IDE_HFLAG_NO_ATAPI_DMA |
				  IDE_HFLAG_OFF_BOARD,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण,
	अणु	/* 4: AEC6280R */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_aec62xx,
		.enablebits	= अणुअणु0x4a,0x02,0x02पूर्ण, अणु0x4a,0x04,0x04पूर्णपूर्ण,
		.port_ops	= &atp86x_port_ops,
		.host_flags	= IDE_HFLAG_NO_ATAPI_DMA |
				  IDE_HFLAG_OFF_BOARD,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण
पूर्ण;

/**
 *	aec62xx_init_one	-	called when a AEC is found
 *	@dev: the aec62xx device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 *
 *	NOTE: since we're going to modify the 'name' field क्रम AEC-6[26]80[R]
 *	chips, pass a local copy of 'struct ide_port_info' करोwn the call chain.
 */

अटल पूर्णांक aec62xx_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा chipset_bus_घड़ी_list_entry *bus_घड़ी;
	काष्ठा ide_port_info d;
	u8 idx = id->driver_data;
	पूर्णांक bus_speed = ide_pci_clk ? ide_pci_clk : 33;
	पूर्णांक err;

	अगर (bus_speed <= 33)
		bus_घड़ी = aec6xxx_33_base;
	अन्यथा
		bus_घड़ी = aec6xxx_34_base;

	err = pci_enable_device(dev);
	अगर (err)
		वापस err;

	d = aec62xx_chipsets[idx];

	अगर (idx == 3 || idx == 4) अणु
		अचिन्हित दीर्घ dma_base = pci_resource_start(dev, 4);

		अगर (inb(dma_base + 2) & 0x10) अणु
			prपूर्णांकk(KERN_INFO DRV_NAME " %s: AEC6880%s card detected"
				"\n", pci_name(dev), (idx == 4) ? "R" : "");
			d.udma_mask = ATA_UDMA6;
		पूर्ण
	पूर्ण

	err = ide_pci_init_one(dev, &d, (व्योम *)bus_घड़ी);
	अगर (err)
		pci_disable_device(dev);

	वापस err;
पूर्ण

अटल व्योम aec62xx_हटाओ(काष्ठा pci_dev *dev)
अणु
	ide_pci_हटाओ(dev);
	pci_disable_device(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id aec62xx_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ARTOP, PCI_DEVICE_ID_ARTOP_ATP850UF), 0 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, PCI_DEVICE_ID_ARTOP_ATP860),   1 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, PCI_DEVICE_ID_ARTOP_ATP860R),  2 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, PCI_DEVICE_ID_ARTOP_ATP865),   3 पूर्ण,
	अणु PCI_VDEVICE(ARTOP, PCI_DEVICE_ID_ARTOP_ATP865R),  4 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, aec62xx_pci_tbl);

अटल काष्ठा pci_driver aec62xx_pci_driver = अणु
	.name		= "AEC62xx_IDE",
	.id_table	= aec62xx_pci_tbl,
	.probe		= aec62xx_init_one,
	.हटाओ		= aec62xx_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init aec62xx_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&aec62xx_pci_driver);
पूर्ण

अटल व्योम __निकास aec62xx_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&aec62xx_pci_driver);
पूर्ण

module_init(aec62xx_ide_init);
module_निकास(aec62xx_ide_निकास);

MODULE_AUTHOR("Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for ARTOP AEC62xx IDE");
MODULE_LICENSE("GPL");
