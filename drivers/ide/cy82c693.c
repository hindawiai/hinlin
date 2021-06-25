<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1998-2000 Andreas S. Krebs (akrebs@altavista.net), Maपूर्णांकainer
 *  Copyright (C) 1998-2002 Andre Hedrick <andre@linux-ide.org>, Integrator
 *  Copyright (C) 2007-2011 Bartlomiej Zolnierkiewicz
 *
 * CYPRESS CY82C693 chipset IDE controller
 *
 * The CY82C693 chipset is used on Digital's PC-Alpha 164SX boards.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "cy82c693"

/*
 *	NOTE: the value क्रम busmaster समयout is tricky and I got it by
 *	trial and error!  By using a to low value will cause DMA समयouts
 *	and drop IDE perक्रमmance, and by using a to high value will cause
 *	audio playback to scatter.
 *	If you know a better value or how to calc it, please let me know.
 */

/* twice the value written in cy82c693ub datasheet */
#घोषणा BUSMASTER_TIMEOUT	0x50
/*
 * the value above was tested on my machine and it seems to work okay
 */

/* here are the offset definitions क्रम the रेजिस्टरs */
#घोषणा CY82_IDE_CMDREG		0x04
#घोषणा CY82_IDE_ADDRSETUP	0x48
#घोषणा CY82_IDE_MASTER_IOR	0x4C
#घोषणा CY82_IDE_MASTER_IOW	0x4D
#घोषणा CY82_IDE_SLAVE_IOR	0x4E
#घोषणा CY82_IDE_SLAVE_IOW	0x4F
#घोषणा CY82_IDE_MASTER_8BIT	0x50
#घोषणा CY82_IDE_SLAVE_8BIT	0x51

#घोषणा CY82_INDEX_PORT		0x22
#घोषणा CY82_DATA_PORT		0x23

#घोषणा CY82_INDEX_CHANNEL0	0x30
#घोषणा CY82_INDEX_CHANNEL1	0x31
#घोषणा CY82_INDEX_TIMEOUT	0x32

/*
 * set DMA mode a specअगरic channel क्रम CY82C693
 */

अटल व्योम cy82c693_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	स्थिर u8 mode = drive->dma_mode;
	u8 single = (mode & 0x10) >> 4, index = 0, data = 0;

	index = hwअगर->channel ? CY82_INDEX_CHANNEL1 : CY82_INDEX_CHANNEL0;

	data = (mode & 3) | (single << 2);

	outb(index, CY82_INDEX_PORT);
	outb(data, CY82_DATA_PORT);

	/*
	 * note: below we set the value क्रम Bus Master IDE TimeOut Register
	 * I'm not असलolutely sure what this करोes, but it solved my problem
	 * with IDE DMA and sound, so I now can play sound and work with
	 * my IDE driver at the same समय :-)
	 *
	 * If you know the correct (best) value क्रम this रेजिस्टर please
	 * let me know - ASK
	 */

	data = BUSMASTER_TIMEOUT;
	outb(CY82_INDEX_TIMEOUT, CY82_INDEX_PORT);
	outb(data, CY82_DATA_PORT);
पूर्ण

अटल व्योम cy82c693_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	पूर्णांक bus_speed = ide_pci_clk ? ide_pci_clk : 33;
	स्थिर अचिन्हित दीर्घ T = 1000000 / bus_speed;
	अचिन्हित पूर्णांक addrCtrl;
	काष्ठा ide_timing t;
	u8 समय_16, समय_8;

	/* select primary or secondary channel */
	अगर (drive->dn > 1) अणु  /* drive is on the secondary channel */
		dev = pci_get_slot(dev->bus, dev->devfn+1);
		अगर (!dev) अणु
			prपूर्णांकk(KERN_ERR "%s: tune_drive: "
				"Cannot find secondary interface!\n",
				drive->name);
			वापस;
		पूर्ण
	पूर्ण

	ide_timing_compute(drive, drive->pio_mode, &t, T, 1);

	समय_16 = clamp_val(t.recover - 1, 0, 15) |
		  (clamp_val(t.active - 1, 0, 15) << 4);
	समय_8 = clamp_val(t.act8b - 1, 0, 15) |
		 (clamp_val(t.rec8b - 1, 0, 15) << 4);

	/* now let's ग_लिखो  the घड़ीs रेजिस्टरs */
	अगर ((drive->dn & 1) == 0) अणु
		/*
		 * set master drive
		 * address setup control रेजिस्टर
		 * is 32 bit !!!
		 */
		pci_पढ़ो_config_dword(dev, CY82_IDE_ADDRSETUP, &addrCtrl);

		addrCtrl &= (~0xF);
		addrCtrl |= clamp_val(t.setup - 1, 0, 15);
		pci_ग_लिखो_config_dword(dev, CY82_IDE_ADDRSETUP, addrCtrl);

		/* now let's set the reमुख्यing रेजिस्टरs */
		pci_ग_लिखो_config_byte(dev, CY82_IDE_MASTER_IOR, समय_16);
		pci_ग_लिखो_config_byte(dev, CY82_IDE_MASTER_IOW, समय_16);
		pci_ग_लिखो_config_byte(dev, CY82_IDE_MASTER_8BIT, समय_8);
	पूर्ण अन्यथा अणु
		/*
		 * set slave drive
		 * address setup control रेजिस्टर
		 * is 32 bit !!!
		 */
		pci_पढ़ो_config_dword(dev, CY82_IDE_ADDRSETUP, &addrCtrl);

		addrCtrl &= (~0xF0);
		addrCtrl |= (clamp_val(t.setup - 1, 0, 15) << 4);
		pci_ग_लिखो_config_dword(dev, CY82_IDE_ADDRSETUP, addrCtrl);

		/* now let's set the reमुख्यing रेजिस्टरs */
		pci_ग_लिखो_config_byte(dev, CY82_IDE_SLAVE_IOR, समय_16);
		pci_ग_लिखो_config_byte(dev, CY82_IDE_SLAVE_IOW, समय_16);
		pci_ग_लिखो_config_byte(dev, CY82_IDE_SLAVE_8BIT, समय_8);
	पूर्ण
	अगर (drive->dn > 1)
		pci_dev_put(dev);
पूर्ण

अटल व्योम init_iops_cy82c693(ide_hwअगर_t *hwअगर)
अणु
	अटल ide_hwअगर_t *primary;
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);

	अगर (PCI_FUNC(dev->devfn) == 1)
		primary = hwअगर;
	अन्यथा अणु
		hwअगर->mate = primary;
		hwअगर->channel = 1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ide_port_ops cy82c693_port_ops = अणु
	.set_pio_mode		= cy82c693_set_pio_mode,
	.set_dma_mode		= cy82c693_set_dma_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info cy82c693_chipset = अणु
	.name		= DRV_NAME,
	.init_iops	= init_iops_cy82c693,
	.port_ops	= &cy82c693_port_ops,
	.host_flags	= IDE_HFLAG_SINGLE,
	.pio_mask	= ATA_PIO4,
	.swdma_mask	= ATA_SWDMA2,
	.mwdma_mask	= ATA_MWDMA2,
पूर्ण;

अटल पूर्णांक cy82c693_init_one(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pci_dev *dev2;
	पूर्णांक ret = -ENODEV;

	/* CY82C693 is more than only a IDE controller.
	   Function 1 is primary IDE channel, function 2 - secondary. */
	अगर ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE &&
	    PCI_FUNC(dev->devfn) == 1) अणु
		dev2 = pci_get_slot(dev->bus, dev->devfn + 1);
		ret = ide_pci_init_two(dev, dev2, &cy82c693_chipset, शून्य);
		अगर (ret)
			pci_dev_put(dev2);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cy82c693_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा pci_dev *dev2 = host->dev[1] ? to_pci_dev(host->dev[1]) : शून्य;

	ide_pci_हटाओ(dev);
	pci_dev_put(dev2);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cy82c693_pci_tbl[] = अणु
	अणु PCI_VDEVICE(CONTAQ, PCI_DEVICE_ID_CONTAQ_82C693), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, cy82c693_pci_tbl);

अटल काष्ठा pci_driver cy82c693_pci_driver = अणु
	.name		= "Cypress_IDE",
	.id_table	= cy82c693_pci_tbl,
	.probe		= cy82c693_init_one,
	.हटाओ		= cy82c693_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init cy82c693_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&cy82c693_pci_driver);
पूर्ण

अटल व्योम __निकास cy82c693_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cy82c693_pci_driver);
पूर्ण

module_init(cy82c693_ide_init);
module_निकास(cy82c693_ide_निकास);

MODULE_AUTHOR("Andreas Krebs, Andre Hedrick, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("PCI driver module for the Cypress CY82C693 IDE");
MODULE_LICENSE("GPL");
