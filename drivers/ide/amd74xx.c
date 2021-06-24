<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD 755/756/766/8111 and nVidia nForce/2/2s/3/3s/CK804/MCP04
 * IDE driver क्रम Linux.
 *
 * Copyright (c) 2000-2002 Vojtech Pavlik
 * Copyright (c) 2007-2010 Bartlomiej Zolnierkiewicz
 *
 * Based on the work of:
 *      Andre Hedrick
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>

#घोषणा DRV_NAME "amd74xx"

क्रमागत अणु
	AMD_IDE_CONFIG		= 0x41,
	AMD_CABLE_DETECT	= 0x42,
	AMD_DRIVE_TIMING	= 0x48,
	AMD_8BIT_TIMING		= 0x4e,
	AMD_ADDRESS_SETUP	= 0x4c,
	AMD_UDMA_TIMING		= 0x50,
पूर्ण;

अटल अचिन्हित पूर्णांक amd_80w;
अटल अचिन्हित पूर्णांक amd_घड़ी;

अटल अक्षर *amd_dma[] = अणु "16", "25", "33", "44", "66", "100", "133" पूर्ण;
अटल अचिन्हित अक्षर amd_cyc2udma[] = अणु 6, 6, 5, 4, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 7 पूर्ण;

अटल अंतरभूत u8 amd_offset(काष्ठा pci_dev *dev)
अणु
	वापस (dev->venकरोr == PCI_VENDOR_ID_NVIDIA) ? 0x10 : 0;
पूर्ण

/*
 * amd_set_speed() ग_लिखोs timing values to the chipset रेजिस्टरs
 */

अटल व्योम amd_set_speed(काष्ठा pci_dev *dev, u8 dn, u8 udma_mask,
			  काष्ठा ide_timing *timing)
अणु
	u8 t = 0, offset = amd_offset(dev);

	pci_पढ़ो_config_byte(dev, AMD_ADDRESS_SETUP + offset, &t);
	t = (t & ~(3 << ((3 - dn) << 1))) | ((clamp_val(timing->setup, 1, 4) - 1) << ((3 - dn) << 1));
	pci_ग_लिखो_config_byte(dev, AMD_ADDRESS_SETUP + offset, t);

	pci_ग_लिखो_config_byte(dev, AMD_8BIT_TIMING + offset + (1 - (dn >> 1)),
		((clamp_val(timing->act8b, 1, 16) - 1) << 4) | (clamp_val(timing->rec8b, 1, 16) - 1));

	pci_ग_लिखो_config_byte(dev, AMD_DRIVE_TIMING + offset + (3 - dn),
		((clamp_val(timing->active, 1, 16) - 1) << 4) | (clamp_val(timing->recover, 1, 16) - 1));

	चयन (udma_mask) अणु
	हाल ATA_UDMA2: t = timing->udma ? (0xc0 | (clamp_val(timing->udma, 2, 5) - 2)) : 0x03; अवरोध;
	हाल ATA_UDMA4: t = timing->udma ? (0xc0 | amd_cyc2udma[clamp_val(timing->udma, 2, 10)]) : 0x03; अवरोध;
	हाल ATA_UDMA5: t = timing->udma ? (0xc0 | amd_cyc2udma[clamp_val(timing->udma, 1, 10)]) : 0x03; अवरोध;
	हाल ATA_UDMA6: t = timing->udma ? (0xc0 | amd_cyc2udma[clamp_val(timing->udma, 1, 15)]) : 0x03; अवरोध;
	शेष: वापस;
	पूर्ण

	अगर (timing->udma)
		pci_ग_लिखो_config_byte(dev, AMD_UDMA_TIMING + offset + 3 - dn, t);
पूर्ण

/*
 * amd_set_drive() computes timing values and configures the chipset
 * to a desired transfer mode.  It also can be called by upper layers.
 */

अटल व्योम amd_set_drive(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	ide_drive_t *peer = ide_get_pair_dev(drive);
	काष्ठा ide_timing t, p;
	पूर्णांक T, UT;
	u8 udma_mask = hwअगर->ultra_mask;
	स्थिर u8 speed = drive->dma_mode;

	T = 1000000000 / amd_घड़ी;
	UT = (udma_mask == ATA_UDMA2) ? T : (T / 2);

	ide_timing_compute(drive, speed, &t, T, UT);

	अगर (peer) अणु
		ide_timing_compute(peer, peer->pio_mode, &p, T, UT);
		ide_timing_merge(&p, &t, &t, IDE_TIMING_8BIT);
	पूर्ण

	अगर (speed == XFER_UDMA_5 && amd_घड़ी <= 33333) t.udma = 1;
	अगर (speed == XFER_UDMA_6 && amd_घड़ी <= 33333) t.udma = 15;

	amd_set_speed(dev, drive->dn, udma_mask, &t);
पूर्ण

/*
 * amd_set_pio_mode() is a callback from upper layers क्रम PIO-only tuning.
 */

अटल व्योम amd_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	drive->dma_mode = drive->pio_mode;
	amd_set_drive(hwअगर, drive);
पूर्ण

अटल व्योम amd7409_cable_detect(काष्ठा pci_dev *dev)
अणु
	/* no host side cable detection */
	amd_80w = 0x03;
पूर्ण

अटल व्योम amd7411_cable_detect(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	u32 u = 0;
	u8 t = 0, offset = amd_offset(dev);

	pci_पढ़ो_config_byte(dev, AMD_CABLE_DETECT + offset, &t);
	pci_पढ़ो_config_dword(dev, AMD_UDMA_TIMING + offset, &u);
	amd_80w = ((t & 0x3) ? 1 : 0) | ((t & 0xc) ? 2 : 0);
	क्रम (i = 24; i >= 0; i -= 8)
		अगर (((u >> i) & 4) && !(amd_80w & (1 << (1 - (i >> 4))))) अणु
			prपूर्णांकk(KERN_WARNING DRV_NAME " %s: BIOS didn't set "
				"cable bits correctly. Enabling workaround.\n",
				pci_name(dev));
			amd_80w |= (1 << (1 - (i >> 4)));
		पूर्ण
पूर्ण

/*
 * The initialization callback.  Initialize drive independent रेजिस्टरs.
 */

अटल पूर्णांक init_chipset_amd74xx(काष्ठा pci_dev *dev)
अणु
	u8 t = 0, offset = amd_offset(dev);

/*
 * Check 80-wire cable presence.
 */

	अगर (dev->venकरोr == PCI_VENDOR_ID_AMD &&
	    dev->device == PCI_DEVICE_ID_AMD_COBRA_7401)
		; /* no UDMA > 2 */
	अन्यथा अगर (dev->venकरोr == PCI_VENDOR_ID_AMD &&
		 dev->device == PCI_DEVICE_ID_AMD_VIPER_7409)
		amd7409_cable_detect(dev);
	अन्यथा
		amd7411_cable_detect(dev);

/*
 * Take care of prefetch & postग_लिखो.
 */

	pci_पढ़ो_config_byte(dev, AMD_IDE_CONFIG + offset, &t);
	/*
	 * Check क्रम broken FIFO support.
	 */
	अगर (dev->venकरोr == PCI_VENDOR_ID_AMD &&
	    dev->device == PCI_DEVICE_ID_AMD_VIPER_7411)
		t &= 0x0f;
	अन्यथा
		t |= 0xf0;
	pci_ग_लिखो_config_byte(dev, AMD_IDE_CONFIG + offset, t);

	वापस 0;
पूर्ण

अटल u8 amd_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	अगर ((amd_80w >> hwअगर->channel) & 1)
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops amd_port_ops = अणु
	.set_pio_mode		= amd_set_pio_mode,
	.set_dma_mode		= amd_set_drive,
	.cable_detect		= amd_cable_detect,
पूर्ण;

#घोषणा IDE_HFLAGS_AMD \
	(IDE_HFLAG_PIO_NO_BLACKLIST | \
	 IDE_HFLAG_POST_SET_MODE | \
	 IDE_HFLAG_IO_32BIT | \
	 IDE_HFLAG_UNMASK_IRQS)

#घोषणा DECLARE_AMD_DEV(swdma, udma)				\
	अणु								\
		.name		= DRV_NAME,				\
		.init_chipset	= init_chipset_amd74xx,			\
		.enablebits	= अणुअणु0x40,0x02,0x02पूर्ण, अणु0x40,0x01,0x01पूर्णपूर्ण,	\
		.port_ops	= &amd_port_ops,			\
		.host_flags	= IDE_HFLAGS_AMD,			\
		.pio_mask	= ATA_PIO5,				\
		.swdma_mask	= swdma,				\
		.mwdma_mask	= ATA_MWDMA2,				\
		.udma_mask	= udma,					\
	पूर्ण

#घोषणा DECLARE_NV_DEV(udma)					\
	अणु								\
		.name		= DRV_NAME,				\
		.init_chipset	= init_chipset_amd74xx,			\
		.enablebits	= अणुअणु0x50,0x02,0x02पूर्ण, अणु0x50,0x01,0x01पूर्णपूर्ण,	\
		.port_ops	= &amd_port_ops,			\
		.host_flags	= IDE_HFLAGS_AMD,			\
		.pio_mask	= ATA_PIO5,				\
		.swdma_mask	= ATA_SWDMA2,				\
		.mwdma_mask	= ATA_MWDMA2,				\
		.udma_mask	= udma,					\
	पूर्ण

अटल स्थिर काष्ठा ide_port_info amd74xx_chipsets[] = अणु
	/* 0: AMD7401 */	DECLARE_AMD_DEV(0x00, ATA_UDMA2),
	/* 1: AMD7409 */	DECLARE_AMD_DEV(ATA_SWDMA2, ATA_UDMA4),
	/* 2: AMD7411/7441 */	DECLARE_AMD_DEV(ATA_SWDMA2, ATA_UDMA5),
	/* 3: AMD8111 */	DECLARE_AMD_DEV(ATA_SWDMA2, ATA_UDMA6),

	/* 4: NFORCE */		DECLARE_NV_DEV(ATA_UDMA5),
	/* 5: >= NFORCE2 */	DECLARE_NV_DEV(ATA_UDMA6),

	/* 6: AMD5536 */	DECLARE_AMD_DEV(ATA_SWDMA2, ATA_UDMA5),
पूर्ण;

अटल पूर्णांक amd74xx_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ide_port_info d;
	u8 idx = id->driver_data;

	d = amd74xx_chipsets[idx];

	/*
	 * Check क्रम bad SWDMA and incorrectly wired Serenade मुख्यboards.
	 */
	अगर (idx == 1) अणु
		अगर (dev->revision <= 7)
			d.swdma_mask = 0;
		d.host_flags |= IDE_HFLAG_CLEAR_SIMPLEX;
	पूर्ण अन्यथा अगर (idx == 3) अणु
		अगर (dev->subप्रणाली_venकरोr == PCI_VENDOR_ID_AMD &&
		    dev->subप्रणाली_device == PCI_DEVICE_ID_AMD_SERENADE)
			d.udma_mask = ATA_UDMA5;
	पूर्ण

	/*
	 * It seems that on some nVidia controllers using AltStatus
	 * रेजिस्टर can be unreliable so शेष to Status रेजिस्टर
	 * अगर the device is in Compatibility Mode.
	 */
	अगर (dev->venकरोr == PCI_VENDOR_ID_NVIDIA &&
	    ide_pci_is_in_compatibility_mode(dev))
		d.host_flags |= IDE_HFLAG_BROKEN_ALTSTATUS;

	prपूर्णांकk(KERN_INFO "%s %s: UDMA%s controller\n",
		d.name, pci_name(dev), amd_dma[fls(d.udma_mask) - 1]);

	/*
	* Determine the प्रणाली bus घड़ी.
	*/
	amd_घड़ी = (ide_pci_clk ? ide_pci_clk : 33) * 1000;

	चयन (amd_घड़ी) अणु
	हाल 33000: amd_घड़ी = 33333; अवरोध;
	हाल 37000: amd_घड़ी = 37500; अवरोध;
	हाल 41000: amd_घड़ी = 41666; अवरोध;
	पूर्ण

	अगर (amd_घड़ी < 20000 || amd_घड़ी > 50000) अणु
		prपूर्णांकk(KERN_WARNING "%s: User given PCI clock speed impossible"
				    " (%d), using 33 MHz instead.\n",
				    d.name, amd_घड़ी);
		amd_घड़ी = 33333;
	पूर्ण

	वापस ide_pci_init_one(dev, &d, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id amd74xx_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_COBRA_7401),		 0 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_VIPER_7409),		 1 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_VIPER_7411),		 2 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_OPUS_7441),		 2 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_8111_IDE),		 3 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_IDE),	 4 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE2_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE2S_IDE),	 5 पूर्ण,
#अगर_घोषित CONFIG_BLK_DEV_IDE_SATA
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE2S_SATA),	 5 पूर्ण,
#पूर्ण_अगर
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE3_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE3S_IDE),	 5 पूर्ण,
#अगर_घोषित CONFIG_BLK_DEV_IDE_SATA
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE3S_SATA2),	 5 पूर्ण,
#पूर्ण_अगर
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_CK804_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP04_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP61_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP65_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP67_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP73_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP77_IDE),	 5 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_IDE),		 6 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, amd74xx_pci_tbl);

अटल काष्ठा pci_driver amd74xx_pci_driver = अणु
	.name		= "AMD_IDE",
	.id_table	= amd74xx_pci_tbl,
	.probe		= amd74xx_probe,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init amd74xx_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&amd74xx_pci_driver);
पूर्ण

अटल व्योम __निकास amd74xx_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&amd74xx_pci_driver);
पूर्ण

module_init(amd74xx_ide_init);
module_निकास(amd74xx_ide_निकास);

MODULE_AUTHOR("Vojtech Pavlik, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("AMD PCI IDE driver");
MODULE_LICENSE("GPL");
