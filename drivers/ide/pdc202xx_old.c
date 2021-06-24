<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1998-2002		Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2006-2007, 2009	MontaVista Software, Inc.
 *  Copyright (C) 2007-2010		Bartlomiej Zolnierkiewicz
 *
 *  Portions Copyright (C) 1999 Promise Technology, Inc.
 *  Author: Frank Tiernan (frankt@promise.com)
 *  Released under terms of General Public License
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "pdc202xx_old"

अटल व्योम pdc202xx_set_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 drive_pci		= 0x60 + (drive->dn << 2);
	स्थिर u8 speed		= drive->dma_mode;

	u8			AP = 0, BP = 0, CP = 0;
	u8			TA = 0, TB = 0, TC = 0;

	pci_पढ़ो_config_byte(dev, drive_pci,     &AP);
	pci_पढ़ो_config_byte(dev, drive_pci + 1, &BP);
	pci_पढ़ो_config_byte(dev, drive_pci + 2, &CP);

	चयन(speed) अणु
		हाल XFER_UDMA_5:
		हाल XFER_UDMA_4:	TB = 0x20; TC = 0x01; अवरोध;
		हाल XFER_UDMA_2:	TB = 0x20; TC = 0x01; अवरोध;
		हाल XFER_UDMA_3:
		हाल XFER_UDMA_1:	TB = 0x40; TC = 0x02; अवरोध;
		हाल XFER_UDMA_0:
		हाल XFER_MW_DMA_2:	TB = 0x60; TC = 0x03; अवरोध;
		हाल XFER_MW_DMA_1:	TB = 0x60; TC = 0x04; अवरोध;
		हाल XFER_MW_DMA_0:	TB = 0xE0; TC = 0x0F; अवरोध;
		हाल XFER_PIO_4:	TA = 0x01; TB = 0x04; अवरोध;
		हाल XFER_PIO_3:	TA = 0x02; TB = 0x06; अवरोध;
		हाल XFER_PIO_2:	TA = 0x03; TB = 0x08; अवरोध;
		हाल XFER_PIO_1:	TA = 0x05; TB = 0x0C; अवरोध;
		हाल XFER_PIO_0:
		शेष:		TA = 0x09; TB = 0x13; अवरोध;
	पूर्ण

	अगर (speed < XFER_SW_DMA_0) अणु
		/*
		 * preserve SYNC_INT / ERDDY_EN bits जबतक clearing
		 * Prefetch_EN / IORDY_EN / PA[3:0] bits of रेजिस्टर A
		 */
		AP &= ~0x3f;
		अगर (ide_pio_need_iordy(drive, speed - XFER_PIO_0))
			AP |= 0x20;	/* set IORDY_EN bit */
		अगर (drive->media == ide_disk)
			AP |= 0x10;	/* set Prefetch_EN bit */
		/* clear PB[4:0] bits of रेजिस्टर B */
		BP &= ~0x1f;
		pci_ग_लिखो_config_byte(dev, drive_pci,     AP | TA);
		pci_ग_लिखो_config_byte(dev, drive_pci + 1, BP | TB);
	पूर्ण अन्यथा अणु
		/* clear MB[2:0] bits of रेजिस्टर B */
		BP &= ~0xe0;
		/* clear MC[3:0] bits of रेजिस्टर C */
		CP &= ~0x0f;
		pci_ग_लिखो_config_byte(dev, drive_pci + 1, BP | TB);
		pci_ग_लिखो_config_byte(dev, drive_pci + 2, CP | TC);
	पूर्ण
पूर्ण

अटल व्योम pdc202xx_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	drive->dma_mode = drive->pio_mode;
	pdc202xx_set_mode(hwअगर, drive);
पूर्ण

अटल पूर्णांक pdc202xx_test_irq(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ high_16	= pci_resource_start(dev, 4);
	u8 sc1d			= inb(high_16 + 0x1d);

	अगर (hwअगर->channel) अणु
		/*
		 * bit 7: error, bit 6: पूर्णांकerrupting,
		 * bit 5: FIFO full, bit 4: FIFO empty
		 */
		वापस (sc1d & 0x40) ? 1 : 0;
	पूर्ण अन्यथा	अणु
		/*
		 * bit 3: error, bit 2: पूर्णांकerrupting,
		 * bit 1: FIFO full, bit 0: FIFO empty
		 */
		वापस (sc1d & 0x04) ? 1 : 0;
	पूर्ण
पूर्ण

अटल u8 pdc2026x_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u16 CIS, mask = hwअगर->channel ? (1 << 11) : (1 << 10);

	pci_पढ़ो_config_word(dev, 0x50, &CIS);

	वापस (CIS & mask) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
पूर्ण

/*
 * Set the control रेजिस्टर to use the 66MHz प्रणाली
 * घड़ी क्रम UDMA 3/4/5 mode operation when necessary.
 *
 * FIXME: this रेजिस्टर is shared by both channels, some locking is needed
 *
 * It may also be possible to leave the 66MHz घड़ी on
 * and पढ़ोjust the timing parameters.
 */
अटल व्योम pdc_old_enable_66MHz_घड़ी(ide_hwअगर_t *hwअगर)
अणु
	अचिन्हित दीर्घ घड़ी_reg = hwअगर->extra_base + 0x01;
	u8 घड़ी = inb(घड़ी_reg);

	outb(घड़ी | (hwअगर->channel ? 0x08 : 0x02), घड़ी_reg);
पूर्ण

अटल व्योम pdc_old_disable_66MHz_घड़ी(ide_hwअगर_t *hwअगर)
अणु
	अचिन्हित दीर्घ घड़ी_reg = hwअगर->extra_base + 0x01;
	u8 घड़ी = inb(घड़ी_reg);

	outb(घड़ी & ~(hwअगर->channel ? 0x08 : 0x02), घड़ी_reg);
पूर्ण

अटल व्योम pdc2026x_init_hwअगर(ide_hwअगर_t *hwअगर)
अणु
	pdc_old_disable_66MHz_घड़ी(hwअगर);
पूर्ण

अटल व्योम pdc202xx_dma_start(ide_drive_t *drive)
अणु
	अगर (drive->current_speed > XFER_UDMA_2)
		pdc_old_enable_66MHz_घड़ी(drive->hwअगर);
	अगर (drive->media != ide_disk || (drive->dev_flags & IDE_DFLAG_LBA48)) अणु
		ide_hwअगर_t *hwअगर	= drive->hwअगर;
		काष्ठा request *rq	= hwअगर->rq;
		अचिन्हित दीर्घ high_16	= hwअगर->extra_base - 16;
		अचिन्हित दीर्घ atapi_reg	= high_16 + (hwअगर->channel ? 0x24 : 0x20);
		u32 word_count	= 0;
		u8 घड़ी = inb(high_16 + 0x11);

		outb(घड़ी | (hwअगर->channel ? 0x08 : 0x02), high_16 + 0x11);
		word_count = (blk_rq_sectors(rq) << 8);
		word_count = (rq_data_dir(rq) == READ) ?
					word_count | 0x05000000 :
					word_count | 0x06000000;
		outl(word_count, atapi_reg);
	पूर्ण
	ide_dma_start(drive);
पूर्ण

अटल पूर्णांक pdc202xx_dma_end(ide_drive_t *drive)
अणु
	अगर (drive->media != ide_disk || (drive->dev_flags & IDE_DFLAG_LBA48)) अणु
		ide_hwअगर_t *hwअगर	= drive->hwअगर;
		अचिन्हित दीर्घ high_16	= hwअगर->extra_base - 16;
		अचिन्हित दीर्घ atapi_reg	= high_16 + (hwअगर->channel ? 0x24 : 0x20);
		u8 घड़ी		= 0;

		outl(0, atapi_reg); /* zero out extra */
		घड़ी = inb(high_16 + 0x11);
		outb(घड़ी & ~(hwअगर->channel ? 0x08:0x02), high_16 + 0x11);
	पूर्ण
	अगर (drive->current_speed > XFER_UDMA_2)
		pdc_old_disable_66MHz_घड़ी(drive->hwअगर);
	वापस ide_dma_end(drive);
पूर्ण

अटल पूर्णांक init_chipset_pdc202xx(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ dmabase = pci_resource_start(dev, 4);
	u8 udma_speed_flag = 0, primary_mode = 0, secondary_mode = 0;

	अगर (dmabase == 0)
		जाओ out;

	udma_speed_flag	= inb(dmabase | 0x1f);
	primary_mode	= inb(dmabase | 0x1a);
	secondary_mode	= inb(dmabase | 0x1b);
	prपूर्णांकk(KERN_INFO "%s: (U)DMA Burst Bit %sABLED " \
		"Primary %s Mode " \
		"Secondary %s Mode.\n", pci_name(dev),
		(udma_speed_flag & 1) ? "EN" : "DIS",
		(primary_mode & 1) ? "MASTER" : "PCI",
		(secondary_mode & 1) ? "MASTER" : "PCI" );

	अगर (!(udma_speed_flag & 1)) अणु
		prपूर्णांकk(KERN_INFO "%s: FORCING BURST BIT 0x%02x->0x%02x ",
			pci_name(dev), udma_speed_flag,
			(udma_speed_flag|1));
		outb(udma_speed_flag | 1, dmabase | 0x1f);
		prपूर्णांकk("%sACTIVE\n", (inb(dmabase | 0x1f) & 1) ? "" : "IN");
	पूर्ण
out:
	वापस 0;
पूर्ण

अटल व्योम pdc202ata4_fixup_irq(काष्ठा pci_dev *dev, स्थिर अक्षर *name)
अणु
	अगर ((dev->class >> 8) != PCI_CLASS_STORAGE_IDE) अणु
		u8 irq = 0, irq2 = 0;
		pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &irq);
		/* 0xbc */
		pci_पढ़ो_config_byte(dev, (PCI_INTERRUPT_LINE)|0x80, &irq2);
		अगर (irq != irq2) अणु
			pci_ग_लिखो_config_byte(dev,
				(PCI_INTERRUPT_LINE)|0x80, irq);     /* 0xbc */
			prपूर्णांकk(KERN_INFO "%s %s: PCI config space interrupt "
				"mirror fixed\n", name, pci_name(dev));
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा IDE_HFLAGS_PDC202XX \
	(IDE_HFLAG_ERROR_STOPS_FIFO | \
	 IDE_HFLAG_OFF_BOARD)

अटल स्थिर काष्ठा ide_port_ops pdc20246_port_ops = अणु
	.set_pio_mode		= pdc202xx_set_pio_mode,
	.set_dma_mode		= pdc202xx_set_mode,
	.test_irq		= pdc202xx_test_irq,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops pdc2026x_port_ops = अणु
	.set_pio_mode		= pdc202xx_set_pio_mode,
	.set_dma_mode		= pdc202xx_set_mode,
	.test_irq		= pdc202xx_test_irq,
	.cable_detect		= pdc2026x_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops pdc2026x_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= pdc202xx_dma_start,
	.dma_end		= pdc202xx_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

#घोषणा DECLARE_PDC2026X_DEV(udma, sectors) \
	अणु \
		.name		= DRV_NAME, \
		.init_chipset	= init_chipset_pdc202xx, \
		.init_hwअगर	= pdc2026x_init_hwअगर, \
		.port_ops	= &pdc2026x_port_ops, \
		.dma_ops	= &pdc2026x_dma_ops, \
		.host_flags	= IDE_HFLAGS_PDC202XX, \
		.pio_mask	= ATA_PIO4, \
		.mwdma_mask	= ATA_MWDMA2, \
		.udma_mask	= udma, \
		.max_sectors	= sectors, \
	पूर्ण

अटल स्थिर काष्ठा ide_port_info pdc202xx_chipsets[] = अणु
	अणु	/* 0: PDC20246 */
		.name		= DRV_NAME,
		.init_chipset	= init_chipset_pdc202xx,
		.port_ops	= &pdc20246_port_ops,
		.dma_ops	= &sff_dma_ops,
		.host_flags	= IDE_HFLAGS_PDC202XX,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask	= ATA_UDMA2,
	पूर्ण,

	/* 1: PDC2026अणु2,3पूर्ण */
	DECLARE_PDC2026X_DEV(ATA_UDMA4, 0),
	/* 2: PDC2026अणु5,7पूर्ण: UDMA5, limit LBA48 requests to 256 sectors */
	DECLARE_PDC2026X_DEV(ATA_UDMA5, 256),
पूर्ण;

/**
 *	pdc202xx_init_one	-	called when a PDC202xx is found
 *	@dev: the pdc202xx device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 */
 
अटल पूर्णांक pdc202xx_init_one(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा ide_port_info *d;
	u8 idx = id->driver_data;

	d = &pdc202xx_chipsets[idx];

	अगर (idx < 2)
		pdc202ata4_fixup_irq(dev, d->name);

	अगर (dev->venकरोr == PCI_DEVICE_ID_PROMISE_20265) अणु
		काष्ठा pci_dev *bridge = dev->bus->self;

		अगर (bridge &&
		    bridge->venकरोr == PCI_VENDOR_ID_INTEL &&
		    (bridge->device == PCI_DEVICE_ID_INTEL_I960 ||
		     bridge->device == PCI_DEVICE_ID_INTEL_I960RM)) अणु
			prपूर्णांकk(KERN_INFO DRV_NAME " %s: skipping Promise "
				"PDC20265 attached to I2O RAID controller\n",
				pci_name(dev));
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस ide_pci_init_one(dev, d, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pdc202xx_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20246), 0 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20262), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20263), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20265), 2 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20267), 2 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pdc202xx_pci_tbl);

अटल काष्ठा pci_driver pdc202xx_pci_driver = अणु
	.name		= "Promise_Old_IDE",
	.id_table	= pdc202xx_pci_tbl,
	.probe		= pdc202xx_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init pdc202xx_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&pdc202xx_pci_driver);
पूर्ण

अटल व्योम __निकास pdc202xx_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pdc202xx_pci_driver);
पूर्ण

module_init(pdc202xx_ide_init);
module_निकास(pdc202xx_ide_निकास);

MODULE_AUTHOR("Andre Hedrick, Frank Tiernan, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("PCI driver module for older Promise IDE");
MODULE_LICENSE("GPL");
