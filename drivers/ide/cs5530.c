<शैली गुरु>
/*
 * Copyright (C) 2000			Andre Hedrick <andre@linux-ide.org>
 * Copyright (C) 2000			Mark Lord <mlord@pobox.com>
 * Copyright (C) 2007			Bartlomiej Zolnierkiewicz
 *
 * May be copied or modअगरied under the terms of the GNU General Public License
 *
 * Development of this chipset driver was funded
 * by the nice folks at National Semiconductor.
 *
 * Documentation:
 *	CS5530 करोcumentation available from National Semiconductor.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "cs5530"

/*
 * Here are the standard PIO mode 0-4 timings क्रम each "format".
 * Format-0 uses fast data reg timings, with slower command reg timings.
 * Format-1 uses fast timings क्रम all रेजिस्टरs, but won't work with all drives.
 */
अटल अचिन्हित पूर्णांक cs5530_pio_timings[2][5] = अणु
	अणु0x00009172, 0x00012171, 0x00020080, 0x00032010, 0x00040010पूर्ण,
	अणु0xd1329172, 0x71212171, 0x30200080, 0x20102010, 0x00100010पूर्ण
पूर्ण;

/*
 * After chip reset, the PIO timings are set to 0x0000e132, which is not valid.
 */
#घोषणा CS5530_BAD_PIO(timings) (((timings)&~0x80000000)==0x0000e132)
#घोषणा CS5530_BASEREG(hwअगर)	(((hwअगर)->dma_base & ~0xf) + ((hwअगर)->channel ? 0x30 : 0x20))

/**
 *	cs5530_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	Handles setting of PIO mode क्रम the chipset.
 *
 *	The init_hwअगर_cs5530() routine guarantees that all drives
 *	will have valid शेष PIO timings set up beक्रमe we get here.
 */

अटल व्योम cs5530_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ basereg = CS5530_BASEREG(hwअगर);
	अचिन्हित पूर्णांक क्रमmat = (inl(basereg + 4) >> 31) & 1;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	outl(cs5530_pio_timings[क्रमmat][pio], basereg + ((drive->dn & 1)<<3));
पूर्ण

/**
 *	cs5530_udma_filter	-	UDMA filter
 *	@drive: drive
 *
 *	cs5530_udma_filter() करोes UDMA mask filtering क्रम the given drive
 *	taking पूर्णांकo the consideration capabilities of the mate device.
 *
 *	The CS5530 specअगरies that two drives sharing a cable cannot mix
 *	UDMA/MDMA.  It has to be one or the other, क्रम the pair, though
 *	dअगरferent timings can still be chosen क्रम each drive.  We could
 *	set the appropriate timing bits on the fly, but that might be
 *	a bit confusing.  So, क्रम now we अटलally handle this requirement
 *	by looking at our mate drive to see what it is capable of, beक्रमe
 *	choosing a mode क्रम our own drive.
 *
 *	Note: This relies on the fact we never fail from UDMA to MWDMA2
 *	but instead drop to PIO.
 */

अटल u8 cs5530_udma_filter(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	ide_drive_t *mate = ide_get_pair_dev(drive);
	u16 *mateid;
	u8 mask = hwअगर->ultra_mask;

	अगर (mate == शून्य)
		जाओ out;
	mateid = mate->id;

	अगर (ata_id_has_dma(mateid) && __ide_dma_bad_drive(mate) == 0) अणु
		अगर ((mateid[ATA_ID_FIELD_VALID] & 4) &&
		    (mateid[ATA_ID_UDMA_MODES] & 7))
			जाओ out;
		अगर (mateid[ATA_ID_MWDMA_MODES] & 7)
			mask = 0;
	पूर्ण
out:
	वापस mask;
पूर्ण

अटल व्योम cs5530_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ basereg;
	अचिन्हित पूर्णांक reg, timings = 0;

	चयन (drive->dma_mode) अणु
		हाल XFER_UDMA_0:	timings = 0x00921250; अवरोध;
		हाल XFER_UDMA_1:	timings = 0x00911140; अवरोध;
		हाल XFER_UDMA_2:	timings = 0x00911030; अवरोध;
		हाल XFER_MW_DMA_0:	timings = 0x00077771; अवरोध;
		हाल XFER_MW_DMA_1:	timings = 0x00012121; अवरोध;
		हाल XFER_MW_DMA_2:	timings = 0x00002020; अवरोध;
	पूर्ण
	basereg = CS5530_BASEREG(hwअगर);
	reg = inl(basereg + 4);			/* get drive0 config रेजिस्टर */
	timings |= reg & 0x80000000;		/* preserve PIO क्रमmat bit */
	अगर ((drive-> dn & 1) == 0) अणु		/* are we configuring drive0? */
		outl(timings, basereg + 4);	/* ग_लिखो drive0 config रेजिस्टर */
	पूर्ण अन्यथा अणु
		अगर (timings & 0x00100000)
			reg |=  0x00100000;	/* enable UDMA timings क्रम both drives */
		अन्यथा
			reg &= ~0x00100000;	/* disable UDMA timings क्रम both drives */
		outl(reg, basereg + 4);		/* ग_लिखो drive0 config रेजिस्टर */
		outl(timings, basereg + 12);	/* ग_लिखो drive1 config रेजिस्टर */
	पूर्ण
पूर्ण

/**
 *	init_chipset_5530	-	set up 5530 bridge
 *	@dev: PCI device
 *
 *	Initialize the cs5530 bridge क्रम reliable IDE DMA operation.
 */

अटल पूर्णांक init_chipset_cs5530(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *master_0 = शून्य, *cs5530_0 = शून्य;

	अगर (pci_resource_start(dev, 4) == 0)
		वापस -EFAULT;

	dev = शून्य;
	जबतक ((dev = pci_get_device(PCI_VENDOR_ID_CYRIX, PCI_ANY_ID, dev)) != शून्य) अणु
		चयन (dev->device) अणु
			हाल PCI_DEVICE_ID_CYRIX_PCI_MASTER:
				master_0 = pci_dev_get(dev);
				अवरोध;
			हाल PCI_DEVICE_ID_CYRIX_5530_LEGACY:
				cs5530_0 = pci_dev_get(dev);
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (!master_0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": unable to locate PCI MASTER function\n");
		जाओ out;
	पूर्ण
	अगर (!cs5530_0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": unable to locate CS5530 LEGACY function\n");
		जाओ out;
	पूर्ण

	/*
	 * Enable BusMaster and MemoryWriteAndInvalidate क्रम the cs5530:
	 * -->  OR 0x14 पूर्णांकo 16-bit PCI COMMAND reg of function 0 of the cs5530
	 */

	pci_set_master(cs5530_0);
	pci_try_set_mwi(cs5530_0);

	/*
	 * Set PCI CacheLineSize to 16-bytes:
	 * --> Write 0x04 पूर्णांकo 8-bit PCI CACHELINESIZE reg of function 0 of the cs5530
	 */

	pci_ग_लिखो_config_byte(cs5530_0, PCI_CACHE_LINE_SIZE, 0x04);

	/*
	 * Disable trapping of UDMA रेजिस्टर accesses (Win98 hack):
	 * --> Write 0x5006 पूर्णांकo 16-bit reg at offset 0xd0 of function 0 of the cs5530
	 */

	pci_ग_लिखो_config_word(cs5530_0, 0xd0, 0x5006);

	/*
	 * Bit-1 at 0x40 enables MemoryWriteAndInvalidate on पूर्णांकernal X-bus:
	 * The other settings are what is necessary to get the रेजिस्टर
	 * पूर्णांकo a sane state क्रम IDE DMA operation.
	 */

	pci_ग_लिखो_config_byte(master_0, 0x40, 0x1e);

	/* 
	 * Set max PCI burst size (16-bytes seems to work best):
	 *	   16bytes: set bit-1 at 0x41 (reg value of 0x16)
	 *	all others: clear bit-1 at 0x41, and करो:
	 *	  128bytes: OR 0x00 at 0x41
	 *	  256bytes: OR 0x04 at 0x41
	 *	  512bytes: OR 0x08 at 0x41
	 *	 1024bytes: OR 0x0c at 0x41
	 */

	pci_ग_लिखो_config_byte(master_0, 0x41, 0x14);

	/*
	 * These settings are necessary to get the chip
	 * पूर्णांकo a sane state क्रम IDE DMA operation.
	 */

	pci_ग_लिखो_config_byte(master_0, 0x42, 0x00);
	pci_ग_लिखो_config_byte(master_0, 0x43, 0xc1);

out:
	pci_dev_put(master_0);
	pci_dev_put(cs5530_0);
	वापस 0;
पूर्ण

/**
 *	init_hwअगर_cs5530	-	initialise an IDE channel
 *	@hwअगर: IDE to initialize
 *
 *	This माला_लो invoked by the IDE driver once क्रम each channel. It
 *	perक्रमms channel-specअगरic pre-initialization beक्रमe drive probing.
 */

अटल व्योम init_hwअगर_cs5530 (ide_hwअगर_t *hwअगर)
अणु
	अचिन्हित दीर्घ basereg;
	u32 d0_timings;

	basereg = CS5530_BASEREG(hwअगर);
	d0_timings = inl(basereg + 0);
	अगर (CS5530_BAD_PIO(d0_timings))
		outl(cs5530_pio_timings[(d0_timings >> 31) & 1][0], basereg + 0);
	अगर (CS5530_BAD_PIO(inl(basereg + 8)))
		outl(cs5530_pio_timings[(d0_timings >> 31) & 1][0], basereg + 8);
पूर्ण

अटल स्थिर काष्ठा ide_port_ops cs5530_port_ops = अणु
	.set_pio_mode		= cs5530_set_pio_mode,
	.set_dma_mode		= cs5530_set_dma_mode,
	.udma_filter		= cs5530_udma_filter,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info cs5530_chipset = अणु
	.name		= DRV_NAME,
	.init_chipset	= init_chipset_cs5530,
	.init_hwअगर	= init_hwअगर_cs5530,
	.port_ops	= &cs5530_port_ops,
	.host_flags	= IDE_HFLAG_SERIALIZE |
			  IDE_HFLAG_POST_SET_MODE,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA2,
पूर्ण;

अटल पूर्णांक cs5530_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस ide_pci_init_one(dev, &cs5530_chipset, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cs5530_pci_tbl[] = अणु
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5530_IDE), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, cs5530_pci_tbl);

अटल काष्ठा pci_driver cs5530_pci_driver = अणु
	.name		= "CS5530 IDE",
	.id_table	= cs5530_pci_tbl,
	.probe		= cs5530_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init cs5530_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&cs5530_pci_driver);
पूर्ण

अटल व्योम __निकास cs5530_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&cs5530_pci_driver);
पूर्ण

module_init(cs5530_ide_init);
module_निकास(cs5530_ide_निकास);

MODULE_AUTHOR("Mark Lord");
MODULE_DESCRIPTION("PCI driver module for Cyrix/NS 5530 IDE");
MODULE_LICENSE("GPL");
