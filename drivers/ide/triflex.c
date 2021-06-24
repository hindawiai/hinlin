<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IDE Chipset driver क्रम the Compaq TriFlex IDE controller.
 * 
 * Known to work with the Compaq Workstation 5x00 series.
 *
 * Copyright (C) 2002 Hewlett-Packard Development Group, L.P.
 * Author: Torben Mathiasen <torben.mathiasen@hp.com>
 * 
 * Loosely based on the piix & svwks drivers.
 *
 * Documentation:
 *	Not खुलाly available.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "triflex"

अटल व्योम trअगरlex_set_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u32 trअगरlex_timings = 0;
	u16 timing = 0;
	u8 channel_offset = hwअगर->channel ? 0x74 : 0x70, unit = drive->dn & 1;

	pci_पढ़ो_config_dword(dev, channel_offset, &trअगरlex_timings);

	चयन (drive->dma_mode) अणु
		हाल XFER_MW_DMA_2:
			timing = 0x0103; 
			अवरोध;
		हाल XFER_MW_DMA_1:
			timing = 0x0203;
			अवरोध;
		हाल XFER_MW_DMA_0:
			timing = 0x0808;
			अवरोध;
		हाल XFER_SW_DMA_2:
		हाल XFER_SW_DMA_1:
		हाल XFER_SW_DMA_0:
			timing = 0x0f0f;
			अवरोध;
		हाल XFER_PIO_4:
			timing = 0x0202;
			अवरोध;
		हाल XFER_PIO_3:
			timing = 0x0204;
			अवरोध;
		हाल XFER_PIO_2:
			timing = 0x0404;
			अवरोध;
		हाल XFER_PIO_1:
			timing = 0x0508;
			अवरोध;
		हाल XFER_PIO_0:
			timing = 0x0808;
			अवरोध;
	पूर्ण

	trअगरlex_timings &= ~(0xFFFF << (16 * unit));
	trअगरlex_timings |= (timing << (16 * unit));
	
	pci_ग_लिखो_config_dword(dev, channel_offset, trअगरlex_timings);
पूर्ण

अटल व्योम trअगरlex_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	drive->dma_mode = drive->pio_mode;
	trअगरlex_set_mode(hwअगर, drive);
पूर्ण

अटल स्थिर काष्ठा ide_port_ops trअगरlex_port_ops = अणु
	.set_pio_mode		= trअगरlex_set_pio_mode,
	.set_dma_mode		= trअगरlex_set_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info trअगरlex_device = अणु
	.name		= DRV_NAME,
	.enablebits	= अणुअणु0x80, 0x01, 0x01पूर्ण, अणु0x80, 0x02, 0x02पूर्णपूर्ण,
	.port_ops	= &trअगरlex_port_ops,
	.pio_mask	= ATA_PIO4,
	.swdma_mask	= ATA_SWDMA2,
	.mwdma_mask	= ATA_MWDMA2,
पूर्ण;

अटल पूर्णांक trअगरlex_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &trअगरlex_device, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id trअगरlex_pci_tbl[] = अणु
	अणु PCI_VDEVICE(COMPAQ, PCI_DEVICE_ID_COMPAQ_TRIFLEX_IDE), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, trअगरlex_pci_tbl);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक trअगरlex_ide_pci_suspend(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	/*
	 * We must not disable or घातerकरोwn the device.
	 * APM bios refuses to suspend अगर IDE is not accessible.
	 */
	pci_save_state(dev);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा trअगरlex_ide_pci_suspend शून्य
#पूर्ण_अगर

अटल काष्ठा pci_driver trअगरlex_pci_driver = अणु
	.name		= "TRIFLEX_IDE",
	.id_table	= trअगरlex_pci_tbl,
	.probe		= trअगरlex_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= trअगरlex_ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init trअगरlex_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&trअगरlex_pci_driver);
पूर्ण

अटल व्योम __निकास trअगरlex_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&trअगरlex_pci_driver);
पूर्ण

module_init(trअगरlex_ide_init);
module_निकास(trअगरlex_ide_निकास);

MODULE_AUTHOR("Torben Mathiasen");
MODULE_DESCRIPTION("PCI driver module for Compaq Triflex IDE");
MODULE_LICENSE("GPL");


