<शैली गुरु>
/*
 *	IDE tuning and bus mastering support क्रम the CS5510/CS5520
 *	chipsets
 *
 *	The CS5510/CS5520 are slightly unusual devices. Unlike the 
 *	typical IDE controllers they करो bus mastering with the drive in
 *	PIO mode and smarter silicon.
 *
 *	The practical upshot of this is that we must always tune the
 *	drive क्रम the right PIO mode. We must also ignore all the blacklists
 *	and the drive bus mastering DMA inक्रमmation.
 *
 *	*** This driver is strictly experimental ***
 *
 *	(c) Copyright Red Hat Inc 2002
 * 
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * For the aव्योमance of करोubt the "preferred form" of this code is one which
 * is in an खोलो non patent encumbered क्रमmat. Where cryptographic key signing
 * क्रमms part of the process of creating an executable the inक्रमmation
 * including keys needed to generate an equivalently functional executable
 * are deemed to be part of the source code.
 *
 */
 
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/dma-mapping.h>

#घोषणा DRV_NAME "cs5520"

काष्ठा pio_घड़ीs
अणु
	पूर्णांक address;
	पूर्णांक निश्चित;
	पूर्णांक recovery;
पूर्ण;

अटल काष्ठा pio_घड़ीs cs5520_pio_घड़ीs[]=अणु
	अणु3, 6, 11पूर्ण,
	अणु2, 5, 6पूर्ण,
	अणु1, 4, 3पूर्ण,
	अणु1, 3, 2पूर्ण,
	अणु1, 2, 1पूर्ण
पूर्ण;

अटल व्योम cs5520_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	पूर्णांक controller = drive->dn > 1 ? 1 : 0;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	/* 8bit CAT/CRT - 8bit command timing क्रम channel */
	pci_ग_लिखो_config_byte(pdev, 0x62 + controller, 
		(cs5520_pio_घड़ीs[pio].recovery << 4) |
		(cs5520_pio_घड़ीs[pio].निश्चित));

	/* 0x64 - 16bit Primary, 0x68 - 16bit Secondary */

	/* FIXME: should these use address ? */
	/* Data पढ़ो timing */
	pci_ग_लिखो_config_byte(pdev, 0x64 + 4*controller + (drive->dn&1),
		(cs5520_pio_घड़ीs[pio].recovery << 4) |
		(cs5520_pio_घड़ीs[pio].निश्चित));
	/* Write command timing */
	pci_ग_लिखो_config_byte(pdev, 0x66 + 4*controller + (drive->dn&1),
		(cs5520_pio_घड़ीs[pio].recovery << 4) |
		(cs5520_pio_घड़ीs[pio].निश्चित));
पूर्ण

अटल व्योम cs5520_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	prपूर्णांकk(KERN_ERR "cs55x0: bad ide timing.\n");

	drive->pio_mode = XFER_PIO_0 + 0;
	cs5520_set_pio_mode(hwअगर, drive);
पूर्ण

अटल स्थिर काष्ठा ide_port_ops cs5520_port_ops = अणु
	.set_pio_mode		= cs5520_set_pio_mode,
	.set_dma_mode		= cs5520_set_dma_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info cyrix_chipset = अणु
	.name		= DRV_NAME,
	.enablebits	= अणु अणु 0x60, 0x01, 0x01 पूर्ण, अणु 0x60, 0x02, 0x02 पूर्ण पूर्ण,
	.port_ops	= &cs5520_port_ops,
	.host_flags	= IDE_HFLAG_ISA_PORTS | IDE_HFLAG_CS5520,
	.pio_mask	= ATA_PIO4,
पूर्ण;

/*
 *	The 5510/5520 are a bit weird. They करोn't quite set up the way
 *	the PCI helper layer expects so we must करो much of the set up 
 *	work दीर्घhand.
 */
 
अटल पूर्णांक cs5520_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा ide_port_info *d = &cyrix_chipset;
	काष्ठा ide_hw hw[2], *hws[] = अणु शून्य, शून्य पूर्ण;

	ide_setup_pci_noise(dev, d);

	/* We must not grab the entire device, it has 'ISA' space in its
	 * BARS too and we will freak out other bits of the kernel
	 */
	अगर (pci_enable_device_io(dev)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Unable to enable 55x0.\n", d->name);
		वापस -ENODEV;
	पूर्ण
	pci_set_master(dev);
	अगर (dma_set_mask(&dev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_WARNING "%s: No suitable DMA available.\n",
			d->name);
		वापस -ENODEV;
	पूर्ण

	/*
	 *	Now the chipset is configured we can let the core
	 *	करो all the device setup क्रम us
	 */

	ide_pci_setup_ports(dev, d, &hw[0], &hws[0]);
	hw[0].irq = 14;
	hw[1].irq = 15;

	वापस ide_host_add(d, hws, 2, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cs5520_pci_tbl[] = अणु
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5510), 0 पूर्ण,
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5520), 1 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, cs5520_pci_tbl);

अटल काष्ठा pci_driver cs5520_pci_driver = अणु
	.name		= "Cyrix_IDE",
	.id_table	= cs5520_pci_tbl,
	.probe		= cs5520_init_one,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init cs5520_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&cs5520_pci_driver);
पूर्ण

module_init(cs5520_ide_init);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("PCI driver module for Cyrix 5510/5520 IDE");
MODULE_LICENSE("GPL");
