<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2003 ATI Inc. <hyu@ati.com>
 *  Copyright (C) 2004,2007 Bartlomiej Zolnierkiewicz
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "atiixp"

#घोषणा ATIIXP_IDE_PIO_TIMING		0x40
#घोषणा ATIIXP_IDE_MDMA_TIMING		0x44
#घोषणा ATIIXP_IDE_PIO_CONTROL		0x48
#घोषणा ATIIXP_IDE_PIO_MODE		0x4a
#घोषणा ATIIXP_IDE_UDMA_CONTROL		0x54
#घोषणा ATIIXP_IDE_UDMA_MODE		0x56

काष्ठा atiixp_ide_timing अणु
	u8 command_width;
	u8 recover_width;
पूर्ण;

अटल काष्ठा atiixp_ide_timing pio_timing[] = अणु
	अणु 0x05, 0x0d पूर्ण,
	अणु 0x04, 0x07 पूर्ण,
	अणु 0x03, 0x04 पूर्ण,
	अणु 0x02, 0x02 पूर्ण,
	अणु 0x02, 0x00 पूर्ण,
पूर्ण;

अटल काष्ठा atiixp_ide_timing mdma_timing[] = अणु
	अणु 0x07, 0x07 पूर्ण,
	अणु 0x02, 0x01 पूर्ण,
	अणु 0x02, 0x00 पूर्ण,
पूर्ण;

अटल DEFINE_SPINLOCK(atiixp_lock);

/**
 *	atiixp_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Set the पूर्णांकerface PIO mode.
 */

अटल व्योम atiixp_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक timing_shअगरt = (drive->dn ^ 1) * 8;
	u32 pio_timing_data;
	u16 pio_mode_data;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	spin_lock_irqsave(&atiixp_lock, flags);

	pci_पढ़ो_config_word(dev, ATIIXP_IDE_PIO_MODE, &pio_mode_data);
	pio_mode_data &= ~(0x07 << (drive->dn * 4));
	pio_mode_data |= (pio << (drive->dn * 4));
	pci_ग_लिखो_config_word(dev, ATIIXP_IDE_PIO_MODE, pio_mode_data);

	pci_पढ़ो_config_dword(dev, ATIIXP_IDE_PIO_TIMING, &pio_timing_data);
	pio_timing_data &= ~(0xff << timing_shअगरt);
	pio_timing_data |= (pio_timing[pio].recover_width << timing_shअगरt) |
		 (pio_timing[pio].command_width << (timing_shअगरt + 4));
	pci_ग_लिखो_config_dword(dev, ATIIXP_IDE_PIO_TIMING, pio_timing_data);

	spin_unlock_irqrestore(&atiixp_lock, flags);
पूर्ण

/**
 *	atiixp_set_dma_mode	-	set host controller क्रम DMA mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Set a ATIIXP host controller to the desired DMA mode.  This involves
 *	programming the right timing data पूर्णांकo the PCI configuration space.
 */

अटल व्योम atiixp_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक timing_shअगरt = (drive->dn ^ 1) * 8;
	u32 पंचांगp32;
	u16 पंचांगp16;
	u16 udma_ctl = 0;
	स्थिर u8 speed = drive->dma_mode;

	spin_lock_irqsave(&atiixp_lock, flags);

	pci_पढ़ो_config_word(dev, ATIIXP_IDE_UDMA_CONTROL, &udma_ctl);

	अगर (speed >= XFER_UDMA_0) अणु
		pci_पढ़ो_config_word(dev, ATIIXP_IDE_UDMA_MODE, &पंचांगp16);
		पंचांगp16 &= ~(0x07 << (drive->dn * 4));
		पंचांगp16 |= ((speed & 0x07) << (drive->dn * 4));
		pci_ग_लिखो_config_word(dev, ATIIXP_IDE_UDMA_MODE, पंचांगp16);

		udma_ctl |= (1 << drive->dn);
	पूर्ण अन्यथा अगर (speed >= XFER_MW_DMA_0) अणु
		u8 i = speed & 0x03;

		pci_पढ़ो_config_dword(dev, ATIIXP_IDE_MDMA_TIMING, &पंचांगp32);
		पंचांगp32 &= ~(0xff << timing_shअगरt);
		पंचांगp32 |= (mdma_timing[i].recover_width << timing_shअगरt) |
			 (mdma_timing[i].command_width << (timing_shअगरt + 4));
		pci_ग_लिखो_config_dword(dev, ATIIXP_IDE_MDMA_TIMING, पंचांगp32);

		udma_ctl &= ~(1 << drive->dn);
	पूर्ण

	pci_ग_लिखो_config_word(dev, ATIIXP_IDE_UDMA_CONTROL, udma_ctl);

	spin_unlock_irqrestore(&atiixp_lock, flags);
पूर्ण

अटल u8 atiixp_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	u8 udma_mode = 0, ch = hwअगर->channel;

	pci_पढ़ो_config_byte(pdev, ATIIXP_IDE_UDMA_MODE + ch, &udma_mode);

	अगर ((udma_mode & 0x07) >= 0x04 || (udma_mode & 0x70) >= 0x40)
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops atiixp_port_ops = अणु
	.set_pio_mode		= atiixp_set_pio_mode,
	.set_dma_mode		= atiixp_set_dma_mode,
	.cable_detect		= atiixp_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info atiixp_pci_info[] = अणु
	अणु	/* 0: IXP200/300/400/700 */
		.name		= DRV_NAME,
		.enablebits	= अणुअणु0x48,0x01,0x00पूर्ण, अणु0x48,0x08,0x00पूर्णपूर्ण,
		.port_ops	= &atiixp_port_ops,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
	पूर्ण,
	अणु	/* 1: IXP600 */
		.name		= DRV_NAME,
		.enablebits	= अणुअणु0x48,0x01,0x00पूर्ण, अणु0x00,0x00,0x00पूर्णपूर्ण,
		.port_ops	= &atiixp_port_ops,
		.host_flags	= IDE_HFLAG_SINGLE,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA5,
 	पूर्ण,
पूर्ण;

/**
 *	atiixp_init_one	-	called when a ATIIXP is found
 *	@dev: the atiixp device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 */

अटल पूर्णांक atiixp_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &atiixp_pci_info[id->driver_data], शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id atiixp_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP200_IDE), 0 पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP300_IDE), 0 पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP400_IDE), 0 पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP600_IDE), 1 पूर्ण,
	अणु PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP700_IDE), 0 पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_HUDSON2_IDE), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, atiixp_pci_tbl);

अटल काष्ठा pci_driver atiixp_pci_driver = अणु
	.name		= "ATIIXP_IDE",
	.id_table	= atiixp_pci_tbl,
	.probe		= atiixp_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init atiixp_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&atiixp_pci_driver);
पूर्ण

अटल व्योम __निकास atiixp_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&atiixp_pci_driver);
पूर्ण

module_init(atiixp_ide_init);
module_निकास(atiixp_ide_निकास);

MODULE_AUTHOR("HUI YU");
MODULE_DESCRIPTION("PCI driver module for ATI IXP IDE");
MODULE_LICENSE("GPL");
