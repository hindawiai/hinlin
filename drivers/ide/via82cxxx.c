<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VIA IDE driver क्रम Linux. Supported southbridges:
 *
 *   vt82c576, vt82c586, vt82c586a, vt82c586b, vt82c596a, vt82c596b,
 *   vt82c686, vt82c686a, vt82c686b, vt8231, vt8233, vt8233c, vt8233a,
 *   vt8235, vt8237, vt8237a
 *
 * Copyright (c) 2000-2002 Vojtech Pavlik
 * Copyright (c) 2007-2010 Bartlomiej Zolnierkiewicz
 *
 * Based on the work of:
 *	Michel Aubry
 *	Jeff Garzik
 *	Andre Hedrick
 *
 * Documentation:
 *	Obsolete device करोcumentation खुलाly available from via.com.tw
 *	Current device करोcumentation available under NDA only
 */


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>
#समावेश <linux/dmi.h>

#अगर_घोषित CONFIG_PPC_CHRP
#समावेश <यंत्र/processor.h>
#पूर्ण_अगर

#घोषणा DRV_NAME "via82cxxx"

#घोषणा VIA_IDE_ENABLE		0x40
#घोषणा VIA_IDE_CONFIG		0x41
#घोषणा VIA_FIFO_CONFIG		0x43
#घोषणा VIA_MISC_1		0x44
#घोषणा VIA_MISC_2		0x45
#घोषणा VIA_MISC_3		0x46
#घोषणा VIA_DRIVE_TIMING	0x48
#घोषणा VIA_8BIT_TIMING		0x4e
#घोषणा VIA_ADDRESS_SETUP	0x4c
#घोषणा VIA_UDMA_TIMING		0x50

#घोषणा VIA_BAD_PREQ		0x01 /* Crashes अगर PREQ# till DDACK# set */
#घोषणा VIA_BAD_CLK66		0x02 /* 66 MHz घड़ी करोesn't work correctly */
#घोषणा VIA_SET_FIFO		0x04 /* Needs to have FIFO split set */
#घोषणा VIA_NO_UNMASK		0x08 /* Doesn't work with IRQ unmasking on */
#घोषणा VIA_BAD_ID		0x10 /* Has wrong venकरोr ID (0x1107) */
#घोषणा VIA_BAD_AST		0x20 /* Don't touch Address Setup Timing */
#घोषणा VIA_SATA_PATA		0x80 /* SATA/PATA combined configuration */

क्रमागत अणु
	VIA_IDFLAG_SINGLE = (1 << 1), /* single channel controller */
पूर्ण;

/*
 * VIA SouthBridge chips.
 */

अटल काष्ठा via_isa_bridge अणु
	अक्षर *name;
	u16 id;
	u8 rev_min;
	u8 rev_max;
	u8 udma_mask;
	u8 flags;
पूर्ण via_isa_bridges[] = अणु
	अणु "vx855",	PCI_DEVICE_ID_VIA_VX855,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA पूर्ण,
	अणु "vx800",	PCI_DEVICE_ID_VIA_VX800,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA पूर्ण,
	अणु "cx700",	PCI_DEVICE_ID_VIA_CX700,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA पूर्ण,
	अणु "vt8261",	PCI_DEVICE_ID_VIA_8261,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8237s",	PCI_DEVICE_ID_VIA_8237S,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt6410",	PCI_DEVICE_ID_VIA_6410,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt6415",	PCI_DEVICE_ID_VIA_6415,     0x00, 0xff, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8251",	PCI_DEVICE_ID_VIA_8251,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8237",	PCI_DEVICE_ID_VIA_8237,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8237a",	PCI_DEVICE_ID_VIA_8237A,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8235",	PCI_DEVICE_ID_VIA_8235,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8233a",	PCI_DEVICE_ID_VIA_8233A,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8233c",	PCI_DEVICE_ID_VIA_8233C_0,  0x00, 0x2f, ATA_UDMA5, पूर्ण,
	अणु "vt8233",	PCI_DEVICE_ID_VIA_8233_0,   0x00, 0x2f, ATA_UDMA5, पूर्ण,
	अणु "vt8231",	PCI_DEVICE_ID_VIA_8231,     0x00, 0x2f, ATA_UDMA5, पूर्ण,
	अणु "vt82c686b",	PCI_DEVICE_ID_VIA_82C686,   0x40, 0x4f, ATA_UDMA5, पूर्ण,
	अणु "vt82c686a",	PCI_DEVICE_ID_VIA_82C686,   0x10, 0x2f, ATA_UDMA4, पूर्ण,
	अणु "vt82c686",	PCI_DEVICE_ID_VIA_82C686,   0x00, 0x0f, ATA_UDMA2, VIA_BAD_CLK66 पूर्ण,
	अणु "vt82c596b",	PCI_DEVICE_ID_VIA_82C596,   0x10, 0x2f, ATA_UDMA4, पूर्ण,
	अणु "vt82c596a",	PCI_DEVICE_ID_VIA_82C596,   0x00, 0x0f, ATA_UDMA2, VIA_BAD_CLK66 पूर्ण,
	अणु "vt82c586b",	PCI_DEVICE_ID_VIA_82C586_0, 0x47, 0x4f, ATA_UDMA2, VIA_SET_FIFO पूर्ण,
	अणु "vt82c586b",	PCI_DEVICE_ID_VIA_82C586_0, 0x40, 0x46, ATA_UDMA2, VIA_SET_FIFO | VIA_BAD_PREQ पूर्ण,
	अणु "vt82c586b",	PCI_DEVICE_ID_VIA_82C586_0, 0x30, 0x3f, ATA_UDMA2, VIA_SET_FIFO पूर्ण,
	अणु "vt82c586a",	PCI_DEVICE_ID_VIA_82C586_0, 0x20, 0x2f, ATA_UDMA2, VIA_SET_FIFO पूर्ण,
	अणु "vt82c586",	PCI_DEVICE_ID_VIA_82C586_0, 0x00, 0x0f,      0x00, VIA_SET_FIFO पूर्ण,
	अणु "vt82c576",	PCI_DEVICE_ID_VIA_82C576,   0x00, 0x2f,      0x00, VIA_SET_FIFO | VIA_NO_UNMASK पूर्ण,
	अणु "vt82c576",	PCI_DEVICE_ID_VIA_82C576,   0x00, 0x2f,      0x00, VIA_SET_FIFO | VIA_NO_UNMASK | VIA_BAD_ID पूर्ण,
	अणु "vtxxxx",	PCI_DEVICE_ID_VIA_ANON,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक via_घड़ी;
अटल अक्षर *via_dma[] = अणु "16", "25", "33", "44", "66", "100", "133" पूर्ण;

काष्ठा via82cxxx_dev
अणु
	काष्ठा via_isa_bridge *via_config;
	अचिन्हित पूर्णांक via_80w;
पूर्ण;

/**
 *	via_set_speed			-	ग_लिखो timing रेजिस्टरs
 *	@dev: PCI device
 *	@dn: device
 *	@timing: IDE timing data to use
 *
 *	via_set_speed ग_लिखोs timing values to the chipset रेजिस्टरs
 */

अटल व्योम via_set_speed(ide_hwअगर_t *hwअगर, u8 dn, काष्ठा ide_timing *timing)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा via82cxxx_dev *vdev = host->host_priv;
	u8 t;

	अगर (~vdev->via_config->flags & VIA_BAD_AST) अणु
		pci_पढ़ो_config_byte(dev, VIA_ADDRESS_SETUP, &t);
		t = (t & ~(3 << ((3 - dn) << 1))) | ((clamp_val(timing->setup, 1, 4) - 1) << ((3 - dn) << 1));
		pci_ग_लिखो_config_byte(dev, VIA_ADDRESS_SETUP, t);
	पूर्ण

	pci_ग_लिखो_config_byte(dev, VIA_8BIT_TIMING + (1 - (dn >> 1)),
		((clamp_val(timing->act8b, 1, 16) - 1) << 4) | (clamp_val(timing->rec8b, 1, 16) - 1));

	pci_ग_लिखो_config_byte(dev, VIA_DRIVE_TIMING + (3 - dn),
		((clamp_val(timing->active, 1, 16) - 1) << 4) | (clamp_val(timing->recover, 1, 16) - 1));

	चयन (vdev->via_config->udma_mask) अणु
	हाल ATA_UDMA2: t = timing->udma ? (0xe0 | (clamp_val(timing->udma, 2, 5) - 2)) : 0x03; अवरोध;
	हाल ATA_UDMA4: t = timing->udma ? (0xe8 | (clamp_val(timing->udma, 2, 9) - 2)) : 0x0f; अवरोध;
	हाल ATA_UDMA5: t = timing->udma ? (0xe0 | (clamp_val(timing->udma, 2, 9) - 2)) : 0x07; अवरोध;
	हाल ATA_UDMA6: t = timing->udma ? (0xe0 | (clamp_val(timing->udma, 2, 9) - 2)) : 0x07; अवरोध;
	पूर्ण

	/* Set UDMA unless device is not UDMA capable */
	अगर (vdev->via_config->udma_mask) अणु
		u8 udma_etc;

		pci_पढ़ो_config_byte(dev, VIA_UDMA_TIMING + 3 - dn, &udma_etc);

		/* clear transfer mode bit */
		udma_etc &= ~0x20;

		अगर (timing->udma) अणु
			/* preserve 80-wire cable detection bit */
			udma_etc &= 0x10;
			udma_etc |= t;
		पूर्ण

		pci_ग_लिखो_config_byte(dev, VIA_UDMA_TIMING + 3 - dn, udma_etc);
	पूर्ण
पूर्ण

/**
 *	via_set_drive		-	configure transfer mode
 *	@hwअगर: port
 *	@drive: Drive to set up
 *
 *	via_set_drive() computes timing values configures the chipset to
 *	a desired transfer mode.  It also can be called by upper layers.
 */

अटल व्योम via_set_drive(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	ide_drive_t *peer = ide_get_pair_dev(drive);
	काष्ठा ide_host *host = dev_get_drvdata(hwअगर->dev);
	काष्ठा via82cxxx_dev *vdev = host->host_priv;
	काष्ठा ide_timing t, p;
	अचिन्हित पूर्णांक T, UT;
	स्थिर u8 speed = drive->dma_mode;

	T = 1000000000 / via_घड़ी;

	चयन (vdev->via_config->udma_mask) अणु
	हाल ATA_UDMA2: UT = T;   अवरोध;
	हाल ATA_UDMA4: UT = T/2; अवरोध;
	हाल ATA_UDMA5: UT = T/3; अवरोध;
	हाल ATA_UDMA6: UT = T/4; अवरोध;
	शेष:	UT = T;
	पूर्ण

	ide_timing_compute(drive, speed, &t, T, UT);

	अगर (peer) अणु
		ide_timing_compute(peer, peer->pio_mode, &p, T, UT);
		ide_timing_merge(&p, &t, &t, IDE_TIMING_8BIT);
	पूर्ण

	via_set_speed(hwअगर, drive->dn, &t);
पूर्ण

/**
 *	via_set_pio_mode	-	set host controller क्रम PIO mode
 *	@hwअगर: port
 *	@drive: drive
 *
 *	A callback from the upper layers क्रम PIO-only tuning.
 */

अटल व्योम via_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	drive->dma_mode = drive->pio_mode;
	via_set_drive(hwअगर, drive);
पूर्ण

अटल काष्ठा via_isa_bridge *via_config_find(काष्ठा pci_dev **isa)
अणु
	काष्ठा via_isa_bridge *via_config;

	क्रम (via_config = via_isa_bridges;
	     via_config->id != PCI_DEVICE_ID_VIA_ANON; via_config++)
		अगर ((*isa = pci_get_device(PCI_VENDOR_ID_VIA +
			!!(via_config->flags & VIA_BAD_ID),
			via_config->id, शून्य))) अणु

			अगर ((*isa)->revision >= via_config->rev_min &&
			    (*isa)->revision <= via_config->rev_max)
				अवरोध;
			pci_dev_put(*isa);
		पूर्ण

	वापस via_config;
पूर्ण

/*
 * Check and handle 80-wire cable presence
 */
अटल व्योम via_cable_detect(काष्ठा via82cxxx_dev *vdev, u32 u)
अणु
	पूर्णांक i;

	चयन (vdev->via_config->udma_mask) अणु
		हाल ATA_UDMA4:
			क्रम (i = 24; i >= 0; i -= 8)
				अगर (((u >> (i & 16)) & 8) &&
				    ((u >> i) & 0x20) &&
				     (((u >> i) & 7) < 2)) अणु
					/*
					 * 2x PCI घड़ी and
					 * UDMA w/ < 3T/cycle
					 */
					vdev->via_80w |= (1 << (1 - (i >> 4)));
				पूर्ण
			अवरोध;

		हाल ATA_UDMA5:
			क्रम (i = 24; i >= 0; i -= 8)
				अगर (((u >> i) & 0x10) ||
				    (((u >> i) & 0x20) &&
				     (((u >> i) & 7) < 4))) अणु
					/* BIOS 80-wire bit or
					 * UDMA w/ < 60ns/cycle
					 */
					vdev->via_80w |= (1 << (1 - (i >> 4)));
				पूर्ण
			अवरोध;

		हाल ATA_UDMA6:
			क्रम (i = 24; i >= 0; i -= 8)
				अगर (((u >> i) & 0x10) ||
				    (((u >> i) & 0x20) &&
				     (((u >> i) & 7) < 6))) अणु
					/* BIOS 80-wire bit or
					 * UDMA w/ < 60ns/cycle
					 */
					vdev->via_80w |= (1 << (1 - (i >> 4)));
				पूर्ण
			अवरोध;
	पूर्ण
पूर्ण

/**
 *	init_chipset_via82cxxx	-	initialization handler
 *	@dev: PCI device
 *
 *	The initialization callback. Here we determine the IDE chip type
 *	and initialize its drive independent रेजिस्टरs.
 */

अटल पूर्णांक init_chipset_via82cxxx(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा via82cxxx_dev *vdev = host->host_priv;
	काष्ठा via_isa_bridge *via_config = vdev->via_config;
	u8 t, v;
	u32 u;

	/*
	 * Detect cable and configure Clk66
	 */
	pci_पढ़ो_config_dword(dev, VIA_UDMA_TIMING, &u);

	via_cable_detect(vdev, u);

	अगर (via_config->udma_mask == ATA_UDMA4) अणु
		/* Enable Clk66 */
		pci_ग_लिखो_config_dword(dev, VIA_UDMA_TIMING, u|0x80008);
	पूर्ण अन्यथा अगर (via_config->flags & VIA_BAD_CLK66) अणु
		/* Would cause trouble on 596a and 686 */
		pci_ग_लिखो_config_dword(dev, VIA_UDMA_TIMING, u & ~0x80008);
	पूर्ण

	/*
	 * Check whether पूर्णांकerfaces are enabled.
	 */

	pci_पढ़ो_config_byte(dev, VIA_IDE_ENABLE, &v);

	/*
	 * Set up FIFO sizes and thresholds.
	 */

	pci_पढ़ो_config_byte(dev, VIA_FIFO_CONFIG, &t);

	/* Disable PREQ# till DDACK# */
	अगर (via_config->flags & VIA_BAD_PREQ) अणु
		/* Would crash on 586b rev 41 */
		t &= 0x7f;
	पूर्ण

	/* Fix FIFO split between channels */
	अगर (via_config->flags & VIA_SET_FIFO) अणु
		t &= (t & 0x9f);
		चयन (v & 3) अणु
			हाल 2: t |= 0x00; अवरोध;	/* 16 on primary */
			हाल 1: t |= 0x60; अवरोध;	/* 16 on secondary */
			हाल 3: t |= 0x20; अवरोध;	/* 8 pri 8 sec */
		पूर्ण
	पूर्ण

	pci_ग_लिखो_config_byte(dev, VIA_FIFO_CONFIG, t);

	वापस 0;
पूर्ण

/*
 *	Cable special हालs
 */

अटल स्थिर काष्ठा dmi_प्रणाली_id cable_dmi_table[] = अणु
	अणु
		.ident = "Acer Ferrari 3400",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Acer,Inc."),
			DMI_MATCH(DMI_BOARD_NAME, "Ferrari 3400"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक via_cable_override(काष्ठा pci_dev *pdev)
अणु
	/* Systems by DMI */
	अगर (dmi_check_प्रणाली(cable_dmi_table))
		वापस 1;

	/* Arima W730-K8/Targa Visionary 811/... */
	अगर (pdev->subप्रणाली_venकरोr == 0x161F &&
	    pdev->subप्रणाली_device == 0x2032)
		वापस 1;

	वापस 0;
पूर्ण

अटल u8 via82cxxx_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	काष्ठा ide_host *host = pci_get_drvdata(pdev);
	काष्ठा via82cxxx_dev *vdev = host->host_priv;

	अगर (via_cable_override(pdev))
		वापस ATA_CBL_PATA40_SHORT;

	अगर ((vdev->via_config->flags & VIA_SATA_PATA) && hwअगर->channel == 0)
		वापस ATA_CBL_SATA;

	अगर ((vdev->via_80w >> hwअगर->channel) & 1)
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops via_port_ops = अणु
	.set_pio_mode		= via_set_pio_mode,
	.set_dma_mode		= via_set_drive,
	.cable_detect		= via82cxxx_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info via82cxxx_chipset = अणु
	.name		= DRV_NAME,
	.init_chipset	= init_chipset_via82cxxx,
	.enablebits	= अणु अणु 0x40, 0x02, 0x02 पूर्ण, अणु 0x40, 0x01, 0x01 पूर्ण पूर्ण,
	.port_ops	= &via_port_ops,
	.host_flags	= IDE_HFLAG_PIO_NO_BLACKLIST |
			  IDE_HFLAG_POST_SET_MODE |
			  IDE_HFLAG_IO_32BIT,
	.pio_mask	= ATA_PIO5,
	.swdma_mask	= ATA_SWDMA2,
	.mwdma_mask	= ATA_MWDMA2,
पूर्ण;

अटल पूर्णांक via_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा pci_dev *isa = शून्य;
	काष्ठा via_isa_bridge *via_config;
	काष्ठा via82cxxx_dev *vdev;
	पूर्णांक rc;
	u8 idx = id->driver_data;
	काष्ठा ide_port_info d;

	d = via82cxxx_chipset;

	/*
	 * Find the ISA bridge and check we know what it is.
	 */
	via_config = via_config_find(&isa);

	/*
	 * Prपूर्णांक the boot message.
	 */
	prपूर्णांकk(KERN_INFO DRV_NAME " %s: VIA %s (rev %02x) IDE %sDMA%s\n",
		pci_name(dev), via_config->name, isa->revision,
		via_config->udma_mask ? "U" : "MW",
		via_dma[via_config->udma_mask ?
			(fls(via_config->udma_mask) - 1) : 0]);

	pci_dev_put(isa);

	/*
	 * Determine प्रणाली bus घड़ी.
	 */
	via_घड़ी = (ide_pci_clk ? ide_pci_clk : 33) * 1000;

	चयन (via_घड़ी) अणु
	हाल 33000: via_घड़ी = 33333; अवरोध;
	हाल 37000: via_घड़ी = 37500; अवरोध;
	हाल 41000: via_घड़ी = 41666; अवरोध;
	पूर्ण

	अगर (via_घड़ी < 20000 || via_घड़ी > 50000) अणु
		prपूर्णांकk(KERN_WARNING DRV_NAME ": User given PCI clock speed "
			"impossible (%d), using 33 MHz instead.\n", via_घड़ी);
		via_घड़ी = 33333;
	पूर्ण

	अगर (idx == 1)
		d.enablebits[1].reg = d.enablebits[0].reg = 0;
	अन्यथा
		d.host_flags |= IDE_HFLAG_NO_AUTODMA;

	अगर (idx == VIA_IDFLAG_SINGLE)
		d.host_flags |= IDE_HFLAG_SINGLE;

	अगर ((via_config->flags & VIA_NO_UNMASK) == 0)
		d.host_flags |= IDE_HFLAG_UNMASK_IRQS;

	d.udma_mask = via_config->udma_mask;

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME " %s: out of memory :(\n",
			pci_name(dev));
		वापस -ENOMEM;
	पूर्ण

	vdev->via_config = via_config;

	rc = ide_pci_init_one(dev, &d, vdev);
	अगर (rc)
		kमुक्त(vdev);

	वापस rc;
पूर्ण

अटल व्योम via_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा via82cxxx_dev *vdev = host->host_priv;

	ide_pci_हटाओ(dev);
	kमुक्त(vdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id via_pci_tbl[] = अणु
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_82C576_1),  0 पूर्ण,
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_82C586_1),  0 पूर्ण,
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_CX700_IDE), 0 पूर्ण,
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_VX855_IDE), VIA_IDFLAG_SINGLE पूर्ण,
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_6410),      1 पूर्ण,
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_6415),      1 पूर्ण,
	अणु PCI_VDEVICE(VIA, PCI_DEVICE_ID_VIA_SATA_EIDE), 1 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, via_pci_tbl);

अटल काष्ठा pci_driver via_pci_driver = अणु
	.name 		= "VIA_IDE",
	.id_table 	= via_pci_tbl,
	.probe 		= via_init_one,
	.हटाओ		= via_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init via_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&via_pci_driver);
पूर्ण

अटल व्योम __निकास via_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&via_pci_driver);
पूर्ण

module_init(via_ide_init);
module_निकास(via_ide_निकास);

MODULE_AUTHOR("Vojtech Pavlik, Bartlomiej Zolnierkiewicz, Michel Aubry, Jeff Garzik, Andre Hedrick");
MODULE_DESCRIPTION("PCI driver module for VIA IDE");
MODULE_LICENSE("GPL");
