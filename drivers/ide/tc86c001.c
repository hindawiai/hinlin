<शैली गुरु>
/*
 * Copyright (C) 2002 Toshiba Corporation
 * Copyright (C) 2005-2006 MontaVista Software, Inc. <source@mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/module.h>

#घोषणा DRV_NAME "tc86c001"

अटल व्योम tc86c001_set_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ scr_port	= hwअगर->config_data + (drive->dn ? 0x02 : 0x00);
	u16 mode, scr		= inw(scr_port);
	स्थिर u8 speed		= drive->dma_mode;

	चयन (speed) अणु
	हाल XFER_UDMA_4:	mode = 0x00c0; अवरोध;
	हाल XFER_UDMA_3:	mode = 0x00b0; अवरोध;
	हाल XFER_UDMA_2:	mode = 0x00a0; अवरोध;
	हाल XFER_UDMA_1:	mode = 0x0090; अवरोध;
	हाल XFER_UDMA_0:	mode = 0x0080; अवरोध;
	हाल XFER_MW_DMA_2:	mode = 0x0070; अवरोध;
	हाल XFER_MW_DMA_1:	mode = 0x0060; अवरोध;
	हाल XFER_MW_DMA_0:	mode = 0x0050; अवरोध;
	हाल XFER_PIO_4:	mode = 0x0400; अवरोध;
	हाल XFER_PIO_3:	mode = 0x0300; अवरोध;
	हाल XFER_PIO_2:	mode = 0x0200; अवरोध;
	हाल XFER_PIO_1:	mode = 0x0100; अवरोध;
	हाल XFER_PIO_0:
	शेष:		mode = 0x0000; अवरोध;
	पूर्ण

	scr &= (speed < XFER_MW_DMA_0) ? 0xf8ff : 0xff0f;
	scr |= mode;
	outw(scr, scr_port);
पूर्ण

अटल व्योम tc86c001_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	drive->dma_mode = drive->pio_mode;
	tc86c001_set_mode(hwअगर, drive);
पूर्ण

/*
 * HACKITY HACK
 *
 * This is a workaround क्रम the limitation 5 of the TC86C001 IDE controller:
 * अगर a DMA transfer terminates prematurely, the controller leaves the device's
 * पूर्णांकerrupt request (INTRQ) pending and करोes not generate a PCI पूर्णांकerrupt (or
 * set the पूर्णांकerrupt bit in the DMA status रेजिस्टर), thus no PCI पूर्णांकerrupt
 * will occur until a DMA transfer has been successfully completed.
 *
 * We work around this by initiating dummy, zero-length DMA transfer on
 * a DMA समयout expiration. I found no better way to करो this with the current
 * IDE core than to temporarily replace a higher level driver's समयr expiry
 * handler with our own backing up to that handler in हाल our recovery fails.
 */
अटल पूर्णांक tc86c001_समयr_expiry(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	ide_expiry_t *expiry	= ide_get_hwअगरdata(hwअगर);
	u8 dma_stat		= inb(hwअगर->dma_base + ATA_DMA_STATUS);

	/* Restore a higher level driver's expiry handler first. */
	hwअगर->expiry = expiry;

	अगर ((dma_stat & 5) == 1) अणु	/* DMA active and no पूर्णांकerrupt */
		अचिन्हित दीर्घ sc_base	= hwअगर->config_data;
		अचिन्हित दीर्घ twcr_port	= sc_base + (drive->dn ? 0x06 : 0x04);
		u8 dma_cmd		= inb(hwअगर->dma_base + ATA_DMA_CMD);

		prपूर्णांकk(KERN_WARNING "%s: DMA interrupt possibly stuck, "
		       "attempting recovery...\n", drive->name);

		/* Stop DMA */
		outb(dma_cmd & ~0x01, hwअगर->dma_base + ATA_DMA_CMD);

		/* Setup the dummy DMA transfer */
		outw(0, sc_base + 0x0a);	/* Sector Count */
		outw(0, twcr_port);	/* Transfer Word Count 1 or 2 */

		/* Start the dummy DMA transfer */

		/* clear R_OR_WCTR क्रम ग_लिखो */
		outb(0x00, hwअगर->dma_base + ATA_DMA_CMD);
		/* set START_STOPBM */
		outb(0x01, hwअगर->dma_base + ATA_DMA_CMD);

		/*
		 * If an पूर्णांकerrupt was pending, it should come thru लघुly.
		 * If not, a higher level driver's expiry handler should
		 * eventually cause some kind of recovery from the DMA stall.
		 */
		वापस WAIT_MIN_SLEEP;
	पूर्ण

	/* Chain to the restored expiry handler अगर DMA wasn't active. */
	अगर (likely(expiry != शून्य))
		वापस expiry(drive);

	/* If there was no handler, "emulate" that क्रम ide_समयr_expiry()... */
	वापस -1;
पूर्ण

अटल व्योम tc86c001_dma_start(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर	= drive->hwअगर;
	अचिन्हित दीर्घ sc_base	= hwअगर->config_data;
	अचिन्हित दीर्घ twcr_port	= sc_base + (drive->dn ? 0x06 : 0x04);
	अचिन्हित दीर्घ nsectors	= blk_rq_sectors(hwअगर->rq);

	/*
	 * We have to manually load the sector count and size पूर्णांकo
	 * the appropriate प्रणाली control रेजिस्टरs क्रम DMA to work
	 * with LBA48 and ATAPI devices...
	 */
	outw(nsectors, sc_base + 0x0a);	/* Sector Count */
	outw(SECTOR_SIZE / 2, twcr_port); /* Transfer Word Count 1/2 */

	/* Install our समयout expiry hook, saving the current handler... */
	ide_set_hwअगरdata(hwअगर, hwअगर->expiry);
	hwअगर->expiry = &tc86c001_समयr_expiry;

	ide_dma_start(drive);
पूर्ण

अटल u8 tc86c001_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ sc_base = pci_resource_start(dev, 5);
	u16 scr1 = inw(sc_base + 0x00);

	/*
	 * System Control  1 Register bit 13 (PDIAGN):
	 * 0=80-pin cable, 1=40-pin cable
	 */
	वापस (scr1 & 0x2000) ? ATA_CBL_PATA40 : ATA_CBL_PATA80;
पूर्ण

अटल व्योम init_hwअगर_tc86c001(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ sc_base	= pci_resource_start(dev, 5);
	u16 scr1		= inw(sc_base + 0x00);

	/* System Control 1 Register bit 15 (Soft Reset) set */
	outw(scr1 |  0x8000, sc_base + 0x00);

	/* System Control 1 Register bit 14 (FIFO Reset) set */
	outw(scr1 |  0x4000, sc_base + 0x00);

	/* System Control 1 Register: reset clear */
	outw(scr1 & ~0xc000, sc_base + 0x00);

	/* Store the प्रणाली control रेजिस्टर base क्रम convenience... */
	hwअगर->config_data = sc_base;

	अगर (!hwअगर->dma_base)
		वापस;

	/*
	 * Sector Count Control Register bits 0 and 1 set:
	 * software sets Sector Count Register क्रम master and slave device
	 */
	outw(0x0003, sc_base + 0x0c);

	/* Sector Count Register limit */
	hwअगर->rqsize	 = 0xffff;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops tc86c001_port_ops = अणु
	.set_pio_mode		= tc86c001_set_pio_mode,
	.set_dma_mode		= tc86c001_set_mode,
	.cable_detect		= tc86c001_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops tc86c001_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= tc86c001_dma_start,
	.dma_end		= ide_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info tc86c001_chipset = अणु
	.name		= DRV_NAME,
	.init_hwअगर	= init_hwअगर_tc86c001,
	.port_ops	= &tc86c001_port_ops,
	.dma_ops	= &tc86c001_dma_ops,
	.host_flags	= IDE_HFLAG_SINGLE | IDE_HFLAG_OFF_BOARD,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA4,
पूर्ण;

अटल पूर्णांक tc86c001_init_one(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc;

	rc = pci_enable_device(dev);
	अगर (rc)
		जाओ out;

	rc = pci_request_region(dev, 5, DRV_NAME);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": system control regs already in use");
		जाओ out_disable;
	पूर्ण

	rc = ide_pci_init_one(dev, &tc86c001_chipset, शून्य);
	अगर (rc)
		जाओ out_release;

	जाओ out;

out_release:
	pci_release_region(dev, 5);
out_disable:
	pci_disable_device(dev);
out:
	वापस rc;
पूर्ण

अटल व्योम tc86c001_हटाओ(काष्ठा pci_dev *dev)
अणु
	ide_pci_हटाओ(dev);
	pci_release_region(dev, 5);
	pci_disable_device(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id tc86c001_pci_tbl[] = अणु
	अणु PCI_VDEVICE(TOSHIBA_2, PCI_DEVICE_ID_TOSHIBA_TC86C001_IDE), 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, tc86c001_pci_tbl);

अटल काष्ठा pci_driver tc86c001_pci_driver = अणु
	.name		= "TC86C001",
	.id_table	= tc86c001_pci_tbl,
	.probe		= tc86c001_init_one,
	.हटाओ		= tc86c001_हटाओ,
पूर्ण;

अटल पूर्णांक __init tc86c001_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&tc86c001_pci_driver);
पूर्ण

अटल व्योम __निकास tc86c001_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&tc86c001_pci_driver);
पूर्ण

module_init(tc86c001_ide_init);
module_निकास(tc86c001_ide_निकास);

MODULE_AUTHOR("MontaVista Software, Inc. <source@mvista.com>");
MODULE_DESCRIPTION("PCI driver module for TC86C001 IDE");
MODULE_LICENSE("GPL");
