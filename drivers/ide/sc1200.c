<शैली गुरु>
/*
 * Copyright (C) 2000-2002		Mark Lord <mlord@pobox.com>
 * Copyright (C)      2007		Bartlomiej Zolnierkiewicz
 *
 * May be copied or modअगरied under the terms of the GNU General Public License
 *
 * Development of this chipset driver was funded
 * by the nice folks at National Semiconductor.
 *
 * Documentation:
 *	Available from National Semiconductor
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "sc1200"

#घोषणा SC1200_REV_A	0x00
#घोषणा SC1200_REV_B1	0x01
#घोषणा SC1200_REV_B3	0x02
#घोषणा SC1200_REV_C1	0x03
#घोषणा SC1200_REV_D1	0x04

#घोषणा PCI_CLK_33	0x00
#घोषणा PCI_CLK_48	0x01
#घोषणा PCI_CLK_66	0x02
#घोषणा PCI_CLK_33A	0x03

अटल अचिन्हित लघु sc1200_get_pci_घड़ी (व्योम)
अणु
	अचिन्हित अक्षर chip_id, silicon_revision;
	अचिन्हित पूर्णांक pci_घड़ी;
	/*
	 * Check the silicon revision, as not all versions of the chip
	 * have the रेजिस्टर with the fast PCI bus timings.
	 */
	chip_id = inb (0x903c);
	silicon_revision = inb (0x903d);

	// Read the fast pci घड़ी frequency
	अगर (chip_id == 0x04 && silicon_revision < SC1200_REV_B1) अणु
		pci_घड़ी = PCI_CLK_33;
	पूर्ण अन्यथा अणु
		// check घड़ी generator configuration (cfcc)
		// the घड़ी is in bits 8 and 9 of this word

		pci_घड़ी = inw (0x901e);
		pci_घड़ी >>= 8;
		pci_घड़ी &= 0x03;
		अगर (pci_घड़ी == PCI_CLK_33A)
			pci_घड़ी = PCI_CLK_33;
	पूर्ण
	वापस pci_घड़ी;
पूर्ण

/*
 * Here are the standard PIO mode 0-4 timings क्रम each "format".
 * Format-0 uses fast data reg timings, with slower command reg timings.
 * Format-1 uses fast timings क्रम all रेजिस्टरs, but won't work with all drives.
 */
अटल स्थिर अचिन्हित पूर्णांक sc1200_pio_timings[4][5] =
	अणुअणु0x00009172, 0x00012171, 0x00020080, 0x00032010, 0x00040010पूर्ण,	// क्रमmat0  33Mhz
	 अणु0xd1329172, 0x71212171, 0x30200080, 0x20102010, 0x00100010पूर्ण,	// क्रमmat1, 33Mhz
	 अणु0xfaa3f4f3, 0xc23232b2, 0x513101c1, 0x31213121, 0x10211021पूर्ण,	// क्रमmat1, 48Mhz
	 अणु0xfff4fff4, 0xf35353d3, 0x814102f1, 0x42314231, 0x11311131पूर्णपूर्ण;	// क्रमmat1, 66Mhz

/*
 * After chip reset, the PIO timings are set to 0x00009172, which is not valid.
 */
//#घोषणा SC1200_BAD_PIO(timings) (((timings)&~0x80000000)==0x00009172)

अटल व्योम sc1200_tunepio(ide_drive_t *drive, u8 pio)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	अचिन्हित पूर्णांक basereg = hwअगर->channel ? 0x50 : 0x40, क्रमmat = 0;

	pci_पढ़ो_config_dword(pdev, basereg + 4, &क्रमmat);
	क्रमmat = (क्रमmat >> 31) & 1;
	अगर (क्रमmat)
		क्रमmat += sc1200_get_pci_घड़ी();
	pci_ग_लिखो_config_dword(pdev, basereg + ((drive->dn & 1) << 3),
			       sc1200_pio_timings[क्रमmat][pio]);
पूर्ण

/*
 *	The SC1200 specअगरies that two drives sharing a cable cannot mix
 *	UDMA/MDMA.  It has to be one or the other, क्रम the pair, though
 *	dअगरferent timings can still be chosen क्रम each drive.  We could
 *	set the appropriate timing bits on the fly, but that might be
 *	a bit confusing.  So, क्रम now we अटलally handle this requirement
 *	by looking at our mate drive to see what it is capable of, beक्रमe
 *	choosing a mode क्रम our own drive.
 */
अटल u8 sc1200_udma_filter(ide_drive_t *drive)
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

अटल व्योम sc1200_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev		*dev = to_pci_dev(hwअगर->dev);
	अचिन्हित पूर्णांक		reg, timings;
	अचिन्हित लघु		pci_घड़ी;
	अचिन्हित पूर्णांक		basereg = hwअगर->channel ? 0x50 : 0x40;
	स्थिर u8		mode = drive->dma_mode;

	अटल स्थिर u32 udma_timing[3][3] = अणु
		अणु 0x00921250, 0x00911140, 0x00911030 पूर्ण,
		अणु 0x00932470, 0x00922260, 0x00922140 पूर्ण,
		अणु 0x009436a1, 0x00933481, 0x00923261 पूर्ण,
	पूर्ण;

	अटल स्थिर u32 mwdma_timing[3][3] = अणु
		अणु 0x00077771, 0x00012121, 0x00002020 पूर्ण,
		अणु 0x000bbbb2, 0x00024241, 0x00013131 पूर्ण,
		अणु 0x000ffff3, 0x00035352, 0x00015151 पूर्ण,
	पूर्ण;

	pci_घड़ी = sc1200_get_pci_घड़ी();

	/*
	 * Note that each DMA mode has several timings associated with it.
	 * The correct timing depends on the fast PCI घड़ी freq.
	 */

	अगर (mode >= XFER_UDMA_0)
		timings =  udma_timing[pci_घड़ी][mode - XFER_UDMA_0];
	अन्यथा
		timings = mwdma_timing[pci_घड़ी][mode - XFER_MW_DMA_0];

	अगर ((drive->dn & 1) == 0) अणु
		pci_पढ़ो_config_dword(dev, basereg + 4, &reg);
		timings |= reg & 0x80000000;	/* preserve PIO क्रमmat bit */
		pci_ग_लिखो_config_dword(dev, basereg + 4, timings);
	पूर्ण अन्यथा
		pci_ग_लिखो_config_dword(dev, basereg + 12, timings);
पूर्ण

/*  Replacement क्रम the standard ide_dma_end action in
 *  dma_proc.
 *
 *  वापसs 1 on error, 0 otherwise
 */
अटल पूर्णांक sc1200_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित दीर्घ dma_base = hwअगर->dma_base;
	u8 dma_stat;

	dma_stat = inb(dma_base+2);		/* get DMA status */

	अगर (!(dma_stat & 4))
		prपूर्णांकk(" ide_dma_end dma_stat=%0x err=%x newerr=%x\n",
		  dma_stat, ((dma_stat&7)!=4), ((dma_stat&2)==2));

	outb(dma_stat|0x1b, dma_base+2);	/* clear the INTR & ERROR bits */
	outb(inb(dma_base)&~1, dma_base);	/* !! DO THIS HERE !! stop DMA */

	वापस (dma_stat & 7) != 4;		/* verअगरy good DMA status */
पूर्ण

/*
 * sc1200_set_pio_mode() handles setting of PIO modes
 * क्रम both the chipset and drive.
 *
 * All existing BIOSs क्रम this chipset guarantee that all drives
 * will have valid शेष PIO timings set up beक्रमe we get here.
 */

अटल व्योम sc1200_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	पूर्णांक		mode = -1;
	स्थिर u8	pio = drive->pio_mode - XFER_PIO_0;

	/*
	 * bad abuse of ->set_pio_mode पूर्णांकerface
	 */
	चयन (pio) अणु
		हाल 200: mode = XFER_UDMA_0;	अवरोध;
		हाल 201: mode = XFER_UDMA_1;	अवरोध;
		हाल 202: mode = XFER_UDMA_2;	अवरोध;
		हाल 100: mode = XFER_MW_DMA_0;	अवरोध;
		हाल 101: mode = XFER_MW_DMA_1;	अवरोध;
		हाल 102: mode = XFER_MW_DMA_2;	अवरोध;
	पूर्ण
	अगर (mode != -1) अणु
		prपूर्णांकk("SC1200: %s: changing (U)DMA mode\n", drive->name);
		ide_dma_off_quietly(drive);
		अगर (ide_set_dma_mode(drive, mode) == 0 &&
		    (drive->dev_flags & IDE_DFLAG_USING_DMA))
			hwअगर->dma_ops->dma_host_set(drive, 1);
		वापस;
	पूर्ण

	sc1200_tunepio(drive, pio);
पूर्ण

#अगर_घोषित CONFIG_PM
काष्ठा sc1200_saved_state अणु
	u32 regs[8];
पूर्ण;

अटल पूर्णांक sc1200_suspend (काष्ठा pci_dev *dev, pm_message_t state)
अणु
	prपूर्णांकk("SC1200: suspend(%u)\n", state.event);

	/*
	 * we only save state when going from full घातer to less
	 */
	अगर (state.event == PM_EVENT_ON) अणु
		काष्ठा ide_host *host = pci_get_drvdata(dev);
		काष्ठा sc1200_saved_state *ss = host->host_priv;
		अचिन्हित पूर्णांक r;

		/*
		 * save timing रेजिस्टरs
		 * (this may be unnecessary अगर BIOS also करोes it)
		 */
		क्रम (r = 0; r < 8; r++)
			pci_पढ़ो_config_dword(dev, 0x40 + r * 4, &ss->regs[r]);
	पूर्ण

	pci_disable_device(dev);
	pci_set_घातer_state(dev, pci_choose_state(dev, state));
	वापस 0;
पूर्ण

अटल पूर्णांक sc1200_resume (काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा sc1200_saved_state *ss = host->host_priv;
	अचिन्हित पूर्णांक r;
	पूर्णांक i;

	i = pci_enable_device(dev);
	अगर (i)
		वापस i;

	/*
	 * restore timing रेजिस्टरs
	 * (this may be unnecessary अगर BIOS also करोes it)
	 */
	क्रम (r = 0; r < 8; r++)
		pci_ग_लिखो_config_dword(dev, 0x40 + r * 4, ss->regs[r]);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा ide_port_ops sc1200_port_ops = अणु
	.set_pio_mode		= sc1200_set_pio_mode,
	.set_dma_mode		= sc1200_set_dma_mode,
	.udma_filter		= sc1200_udma_filter,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops sc1200_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= sc1200_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info sc1200_chipset = अणु
	.name		= DRV_NAME,
	.port_ops	= &sc1200_port_ops,
	.dma_ops	= &sc1200_dma_ops,
	.host_flags	= IDE_HFLAG_SERIALIZE |
			  IDE_HFLAG_POST_SET_MODE |
			  IDE_HFLAG_ABUSE_DMA_MODES,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA2,
पूर्ण;

अटल पूर्णांक sc1200_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा sc1200_saved_state *ss = शून्य;
	पूर्णांक rc;

#अगर_घोषित CONFIG_PM
	ss = kदो_स्मृति(माप(*ss), GFP_KERNEL);
	अगर (ss == शून्य)
		वापस -ENOMEM;
#पूर्ण_अगर
	rc = ide_pci_init_one(dev, &sc1200_chipset, ss);
	अगर (rc)
		kमुक्त(ss);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा pci_device_id sc1200_pci_tbl[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_SCx200_IDE), 0पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, sc1200_pci_tbl);

अटल काष्ठा pci_driver sc1200_pci_driver = अणु
	.name		= "SC1200_IDE",
	.id_table	= sc1200_pci_tbl,
	.probe		= sc1200_init_one,
	.हटाओ		= ide_pci_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= sc1200_suspend,
	.resume		= sc1200_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init sc1200_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&sc1200_pci_driver);
पूर्ण

अटल व्योम __निकास sc1200_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&sc1200_pci_driver);
पूर्ण

module_init(sc1200_ide_init);
module_निकास(sc1200_ide_निकास);

MODULE_AUTHOR("Mark Lord");
MODULE_DESCRIPTION("PCI driver module for NS SC1200 IDE");
MODULE_LICENSE("GPL");
