<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_via.c 	- VIA PATA क्रम new ATA layer
 *			  (C) 2005-2006 Red Hat Inc
 *
 *  Documentation
 *	Most chipset करोcumentation available under NDA only
 *
 *  VIA version guide
 *	VIA VT82C561	-	early design, uses ata_generic currently
 *	VIA VT82C576	-	MWDMA, 33Mhz
 *	VIA VT82C586	-	MWDMA, 33Mhz
 *	VIA VT82C586a	-	Added UDMA to 33Mhz
 *	VIA VT82C586b	-	UDMA33
 *	VIA VT82C596a	-	Nonfunctional UDMA66
 *	VIA VT82C596b	-	Working UDMA66
 *	VIA VT82C686	-	Nonfunctional UDMA66
 *	VIA VT82C686a	-	Working UDMA66
 *	VIA VT82C686b	-	Updated to UDMA100
 *	VIA VT8231	-	UDMA100
 *	VIA VT8233	-	UDMA100
 *	VIA VT8233a	-	UDMA133
 *	VIA VT8233c	-	UDMA100
 *	VIA VT8235	-	UDMA133
 *	VIA VT8237	-	UDMA133
 *	VIA VT8237A	-	UDMA133
 *	VIA VT8237S	-	UDMA133
 *	VIA VT8251	-	UDMA133
 *
 *	Most रेजिस्टरs reमुख्य compatible across chips. Others start reserved
 *	and acquire sensible semantics अगर set to 1 (eg cable detect). A few
 *	exceptions exist, notably around the FIFO settings.
 *
 *	One additional quirk of the VIA design is that like ALi they use few
 *	PCI IDs क्रम a lot of chips.
 *
 *	Based heavily on:
 *
 * Version 3.38
 *
 * VIA IDE driver क्रम Linux. Supported southbridges:
 *
 *   vt82c576, vt82c586, vt82c586a, vt82c586b, vt82c596a, vt82c596b,
 *   vt82c686, vt82c686a, vt82c686b, vt8231, vt8233, vt8233c, vt8233a,
 *   vt8235, vt8237
 *
 * Copyright (c) 2000-2002 Vojtech Pavlik
 *
 * Based on the work of:
 *	Michel Aubry
 *	Jeff Garzik
 *	Andre Hedrick

 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME "pata_via"
#घोषणा DRV_VERSION "0.3.4"

क्रमागत अणु
	VIA_BAD_PREQ	= 0x01, /* Crashes अगर PREQ# till DDACK# set */
	VIA_BAD_CLK66	= 0x02, /* 66 MHz घड़ी करोesn't work correctly */
	VIA_SET_FIFO	= 0x04, /* Needs to have FIFO split set */
	VIA_NO_UNMASK	= 0x08, /* Doesn't work with IRQ unmasking on */
	VIA_BAD_ID	= 0x10, /* Has wrong venकरोr ID (0x1107) */
	VIA_BAD_AST	= 0x20, /* Don't touch Address Setup Timing */
	VIA_NO_ENABLES	= 0x40, /* Has no enablebits */
	VIA_SATA_PATA	= 0x80, /* SATA/PATA combined configuration */
पूर्ण;

क्रमागत अणु
	VIA_IDFLAG_SINGLE = (1 << 0), /* single channel controller) */
पूर्ण;

/*
 * VIA SouthBridge chips.
 */

अटल स्थिर काष्ठा via_isa_bridge अणु
	स्थिर अक्षर *name;
	u16 id;
	u8 rev_min;
	u8 rev_max;
	u8 udma_mask;
	u8 flags;
पूर्ण via_isa_bridges[] = अणु
	अणु "vx855",	PCI_DEVICE_ID_VIA_VX855,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA पूर्ण,
	अणु "vx800",	PCI_DEVICE_ID_VIA_VX800,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA पूर्ण,
	अणु "vt8261",	PCI_DEVICE_ID_VIA_8261,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8237s",	PCI_DEVICE_ID_VIA_8237S,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8251",	PCI_DEVICE_ID_VIA_8251,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "cx700",	PCI_DEVICE_ID_VIA_CX700,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA पूर्ण,
	अणु "vt6410",	PCI_DEVICE_ID_VIA_6410,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_NO_ENABLES पूर्ण,
	अणु "vt6415",	PCI_DEVICE_ID_VIA_6415,     0x00, 0xff, ATA_UDMA6, VIA_BAD_AST | VIA_NO_ENABLES पूर्ण,
	अणु "vt8237a",	PCI_DEVICE_ID_VIA_8237A,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
	अणु "vt8237",	PCI_DEVICE_ID_VIA_8237,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST पूर्ण,
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

अटल स्थिर काष्ठा dmi_प्रणाली_id no_atapi_dma_dmi_table[] = अणु
	अणु
		.ident = "AVERATEC 3200",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AVERATEC"),
			DMI_MATCH(DMI_BOARD_NAME, "3200"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा via_port अणु
	u8 cached_device;
पूर्ण;

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
	अगर (pdev->subप्रणाली_venकरोr == 0x161F && pdev->subप्रणाली_device == 0x2032)
		वापस 1;
	वापस 0;
पूर्ण


/**
 *	via_cable_detect	-	cable detection
 *	@ap: ATA port
 *
 *	Perक्रमm cable detection. Actually क्रम the VIA हाल the BIOS
 *	alपढ़ोy did this क्रम us. We पढ़ो the values provided by the
 *	BIOS. If you are using an 8235 in a non-PC configuration you
 *	may need to update this code.
 *
 *	Hotplug also impacts on this.
 */

अटल पूर्णांक via_cable_detect(काष्ठा ata_port *ap) अणु
	स्थिर काष्ठा via_isa_bridge *config = ap->host->निजी_data;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 ata66;

	अगर (via_cable_override(pdev))
		वापस ATA_CBL_PATA40_SHORT;

	अगर ((config->flags & VIA_SATA_PATA) && ap->port_no == 0)
		वापस ATA_CBL_SATA;

	/* Early chips are 40 wire */
	अगर (config->udma_mask < ATA_UDMA4)
		वापस ATA_CBL_PATA40;
	/* UDMA 66 chips have only drive side logic */
	अन्यथा अगर (config->udma_mask < ATA_UDMA5)
		वापस ATA_CBL_PATA_UNK;
	/* UDMA 100 or later */
	pci_पढ़ो_config_dword(pdev, 0x50, &ata66);
	/* Check both the drive cable reporting bits, we might not have
	   two drives */
	अगर (ata66 & (0x10100000 >> (16 * ap->port_no)))
		वापस ATA_CBL_PATA80;
	/* Check with ACPI so we can spot BIOS reported SATA bridges */
	अगर (ata_acpi_init_gपंचांग(ap) &&
	    ata_acpi_cbl_80wire(ap, ata_acpi_init_gपंचांग(ap)))
		वापस ATA_CBL_PATA80;
	वापस ATA_CBL_PATA40;
पूर्ण

अटल पूर्णांक via_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	स्थिर काष्ठा via_isa_bridge *config = ap->host->निजी_data;

	अगर (!(config->flags & VIA_NO_ENABLES)) अणु
		अटल स्थिर काष्ठा pci_bits via_enable_bits[] = अणु
			अणु 0x40, 1, 0x02, 0x02 पूर्ण,
			अणु 0x40, 1, 0x01, 0x01 पूर्ण
		पूर्ण;
		काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
		अगर (!pci_test_config_bits(pdev, &via_enable_bits[ap->port_no]))
			वापस -ENOENT;
	पूर्ण

	वापस ata_sff_prereset(link, deadline);
पूर्ण


/**
 *	via_करो_set_mode	-	set transfer mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *	@mode: ATA mode being programmed
 *	@set_ast: Set to program address setup
 *	@udma_type: UDMA mode/क्रमmat of रेजिस्टरs
 *
 *	Program the VIA रेजिस्टरs क्रम DMA and PIO modes. Uses the ata timing
 *	support in order to compute modes.
 *
 *	FIXME: Hotplug will require we serialize multiple mode changes
 *	on the two channels.
 */

अटल व्योम via_करो_set_mode(काष्ठा ata_port *ap, काष्ठा ata_device *adev,
			    पूर्णांक mode, पूर्णांक set_ast, पूर्णांक udma_type)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा ata_device *peer = ata_dev_pair(adev);
	काष्ठा ata_timing t, p;
	अटल पूर्णांक via_घड़ी = 33333;	/* Bus घड़ी in kHZ */
	अचिन्हित दीर्घ T =  1000000000 / via_घड़ी;
	अचिन्हित दीर्घ UT = T;
	पूर्णांक ut;
	पूर्णांक offset = 3 - (2*ap->port_no) - adev->devno;

	चयन (udma_type) अणु
	हाल ATA_UDMA4:
		UT = T / 2; अवरोध;
	हाल ATA_UDMA5:
		UT = T / 3; अवरोध;
	हाल ATA_UDMA6:
		UT = T / 4; अवरोध;
	पूर्ण

	/* Calculate the timing values we require */
	ata_timing_compute(adev, mode, &t, T, UT);

	/* We share 8bit timing so we must merge the स्थिरraपूर्णांकs */
	अगर (peer) अणु
		अगर (peer->pio_mode) अणु
			ata_timing_compute(peer, peer->pio_mode, &p, T, UT);
			ata_timing_merge(&p, &t, &t, ATA_TIMING_8BIT);
		पूर्ण
	पूर्ण

	/* Address setup is programmable but अवरोधs on UDMA133 setups */
	अगर (set_ast) अणु
		u8 setup;	/* 2 bits per drive */
		पूर्णांक shअगरt = 2 * offset;

		pci_पढ़ो_config_byte(pdev, 0x4C, &setup);
		setup &= ~(3 << shअगरt);
		setup |= (clamp_val(t.setup, 1, 4) - 1) << shअगरt;
		pci_ग_लिखो_config_byte(pdev, 0x4C, setup);
	पूर्ण

	/* Load the PIO mode bits */
	pci_ग_लिखो_config_byte(pdev, 0x4F - ap->port_no,
		((clamp_val(t.act8b, 1, 16) - 1) << 4) | (clamp_val(t.rec8b, 1, 16) - 1));
	pci_ग_लिखो_config_byte(pdev, 0x48 + offset,
		((clamp_val(t.active, 1, 16) - 1) << 4) | (clamp_val(t.recover, 1, 16) - 1));

	/* Load the UDMA bits according to type */
	चयन (udma_type) अणु
	हाल ATA_UDMA2:
	शेष:
		ut = t.udma ? (0xe0 | (clamp_val(t.udma, 2, 5) - 2)) : 0x03;
		अवरोध;
	हाल ATA_UDMA4:
		ut = t.udma ? (0xe8 | (clamp_val(t.udma, 2, 9) - 2)) : 0x0f;
		अवरोध;
	हाल ATA_UDMA5:
		ut = t.udma ? (0xe0 | (clamp_val(t.udma, 2, 9) - 2)) : 0x07;
		अवरोध;
	हाल ATA_UDMA6:
		ut = t.udma ? (0xe0 | (clamp_val(t.udma, 2, 9) - 2)) : 0x07;
		अवरोध;
	पूर्ण

	/* Set UDMA unless device is not UDMA capable */
	अगर (udma_type) अणु
		u8 udma_etc;

		pci_पढ़ो_config_byte(pdev, 0x50 + offset, &udma_etc);

		/* clear transfer mode bit */
		udma_etc &= ~0x20;

		अगर (t.udma) अणु
			/* preserve 80-wire cable detection bit */
			udma_etc &= 0x10;
			udma_etc |= ut;
		पूर्ण

		pci_ग_लिखो_config_byte(pdev, 0x50 + offset, udma_etc);
	पूर्ण
पूर्ण

अटल व्योम via_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	स्थिर काष्ठा via_isa_bridge *config = ap->host->निजी_data;
	पूर्णांक set_ast = (config->flags & VIA_BAD_AST) ? 0 : 1;

	via_करो_set_mode(ap, adev, adev->pio_mode, set_ast, config->udma_mask);
पूर्ण

अटल व्योम via_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	स्थिर काष्ठा via_isa_bridge *config = ap->host->निजी_data;
	पूर्णांक set_ast = (config->flags & VIA_BAD_AST) ? 0 : 1;

	via_करो_set_mode(ap, adev, adev->dma_mode, set_ast, config->udma_mask);
पूर्ण

/**
 *	via_mode_filter		-	filter buggy device/mode pairs
 *	@dev: ATA device
 *	@mask: Mode biपंचांगask
 *
 *	We need to apply some minimal filtering क्रम old controllers and at least
 *	one breed of Transcend SSD. Return the updated mask.
 */

अटल अचिन्हित दीर्घ via_mode_filter(काष्ठा ata_device *dev, अचिन्हित दीर्घ mask)
अणु
	काष्ठा ata_host *host = dev->link->ap->host;
	स्थिर काष्ठा via_isa_bridge *config = host->निजी_data;
	अचिन्हित अक्षर model_num[ATA_ID_PROD_LEN + 1];

	अगर (config->id == PCI_DEVICE_ID_VIA_82C586_0) अणु
		ata_id_c_string(dev->id, model_num, ATA_ID_PROD, माप(model_num));
		अगर (म_भेद(model_num, "TS64GSSD25-M") == 0) अणु
			ata_dev_warn(dev,
	"disabling UDMA mode due to reported lockups with this device\n");
			mask &= ~ ATA_MASK_UDMA;
		पूर्ण
	पूर्ण

	अगर (dev->class == ATA_DEV_ATAPI &&
	    dmi_check_प्रणाली(no_atapi_dma_dmi_table)) अणु
		ata_dev_warn(dev, "controller locks up on ATAPI DMA, forcing PIO\n");
		mask &= ATA_MASK_PIO;
	पूर्ण

	वापस mask;
पूर्ण

/**
 *	via_tf_load - send taskfile रेजिस्टरs to host controller
 *	@ap: Port to which output is sent
 *	@tf: ATA taskfile रेजिस्टर set
 *
 *	Outमाला_दो ATA taskfile to standard ATA host controller.
 *
 *	Note: This is to fix the पूर्णांकernal bug of via chipsets, which
 *	will reset the device रेजिस्टर after changing the IEN bit on
 *	ctl रेजिस्टर
 */
अटल व्योम via_tf_load(काष्ठा ata_port *ap, स्थिर काष्ठा ata_taskfile *tf)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	काष्ठा via_port *vp = ap->निजी_data;
	अचिन्हित पूर्णांक is_addr = tf->flags & ATA_TFLAG_ISADDR;
	पूर्णांक newctl = 0;

	अगर (tf->ctl != ap->last_ctl) अणु
		ioग_लिखो8(tf->ctl, ioaddr->ctl_addr);
		ap->last_ctl = tf->ctl;
		ata_रुको_idle(ap);
		newctl = 1;
	पूर्ण

	अगर (tf->flags & ATA_TFLAG_DEVICE) अणु
		ioग_लिखो8(tf->device, ioaddr->device_addr);
		vp->cached_device = tf->device;
	पूर्ण अन्यथा अगर (newctl)
		ioग_लिखो8(vp->cached_device, ioaddr->device_addr);

	अगर (is_addr && (tf->flags & ATA_TFLAG_LBA48)) अणु
		WARN_ON_ONCE(!ioaddr->ctl_addr);
		ioग_लिखो8(tf->hob_feature, ioaddr->feature_addr);
		ioग_लिखो8(tf->hob_nsect, ioaddr->nsect_addr);
		ioग_लिखो8(tf->hob_lbal, ioaddr->lbal_addr);
		ioग_लिखो8(tf->hob_lbam, ioaddr->lbam_addr);
		ioग_लिखो8(tf->hob_lbah, ioaddr->lbah_addr);
		VPRINTK("hob: feat 0x%X nsect 0x%X, lba 0x%X 0x%X 0x%X\n",
			tf->hob_feature,
			tf->hob_nsect,
			tf->hob_lbal,
			tf->hob_lbam,
			tf->hob_lbah);
	पूर्ण

	अगर (is_addr) अणु
		ioग_लिखो8(tf->feature, ioaddr->feature_addr);
		ioग_लिखो8(tf->nsect, ioaddr->nsect_addr);
		ioग_लिखो8(tf->lbal, ioaddr->lbal_addr);
		ioग_लिखो8(tf->lbam, ioaddr->lbam_addr);
		ioग_लिखो8(tf->lbah, ioaddr->lbah_addr);
		VPRINTK("feat 0x%X nsect 0x%X lba 0x%X 0x%X 0x%X\n",
			tf->feature,
			tf->nsect,
			tf->lbal,
			tf->lbam,
			tf->lbah);
	पूर्ण

	ata_रुको_idle(ap);
पूर्ण

अटल पूर्णांक via_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा via_port *vp;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	पूर्णांक ret = ata_bmdma_port_start(ap);
	अगर (ret < 0)
		वापस ret;

	vp = devm_kzalloc(&pdev->dev, माप(काष्ठा via_port), GFP_KERNEL);
	अगर (vp == शून्य)
		वापस -ENOMEM;
	ap->निजी_data = vp;
	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा via_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations via_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= via_cable_detect,
	.set_piomode	= via_set_piomode,
	.set_dmamode	= via_set_dmamode,
	.prereset	= via_pre_reset,
	.sff_tf_load	= via_tf_load,
	.port_start	= via_port_start,
	.mode_filter	= via_mode_filter,
पूर्ण;

अटल काष्ठा ata_port_operations via_port_ops_noirq = अणु
	.inherits	= &via_port_ops,
	.sff_data_xfer	= ata_sff_data_xfer32,
पूर्ण;

/**
 *	via_config_fअगरo		-	set up the FIFO
 *	@pdev: PCI device
 *	@flags: configuration flags
 *
 *	Set the FIFO properties क्रम this device अगर necessary. Used both on
 *	set up and on and the resume path
 */

अटल व्योम via_config_fअगरo(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक flags)
अणु
	u8 enable;

	/* 0x40 low bits indicate enabled channels */
	pci_पढ़ो_config_byte(pdev, 0x40 , &enable);
	enable &= 3;

	अगर (flags & VIA_SET_FIFO) अणु
		अटल स्थिर u8 fअगरo_setting[4] = अणु0x00, 0x60, 0x00, 0x20पूर्ण;
		u8 fअगरo;

		pci_पढ़ो_config_byte(pdev, 0x43, &fअगरo);

		/* Clear PREQ# until DDACK# क्रम errata */
		अगर (flags & VIA_BAD_PREQ)
			fअगरo &= 0x7F;
		अन्यथा
			fअगरo &= 0x9f;
		/* Turn on FIFO क्रम enabled channels */
		fअगरo |= fअगरo_setting[enable];
		pci_ग_लिखो_config_byte(pdev, 0x43, fअगरo);
	पूर्ण
पूर्ण

अटल व्योम via_fixup(काष्ठा pci_dev *pdev, स्थिर काष्ठा via_isa_bridge *config)
अणु
	u32 timing;

	/* Initialise the FIFO क्रम the enabled channels. */
	via_config_fअगरo(pdev, config->flags);

	अगर (config->udma_mask == ATA_UDMA4) अणु
		/* The 66 MHz devices require we enable the घड़ी */
		pci_पढ़ो_config_dword(pdev, 0x50, &timing);
		timing |= 0x80008;
		pci_ग_लिखो_config_dword(pdev, 0x50, timing);
	पूर्ण
	अगर (config->flags & VIA_BAD_CLK66) अणु
		/* Disable the 66MHz घड़ी on problem devices */
		pci_पढ़ो_config_dword(pdev, 0x50, &timing);
		timing &= ~0x80008;
		pci_ग_लिखो_config_dword(pdev, 0x50, timing);
	पूर्ण
पूर्ण

/**
 *	via_init_one		-	discovery callback
 *	@pdev: PCI device
 *	@id: PCI table info
 *
 *	A VIA IDE पूर्णांकerface has been discovered. Figure out what revision
 *	and perक्रमm configuration work beक्रमe handing it to the ATA layer
 */

अटल पूर्णांक via_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	/* Early VIA without UDMA support */
	अटल स्थिर काष्ठा ata_port_info via_mwdma_info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.port_ops = &via_port_ops
	पूर्ण;
	/* Ditto with IRQ masking required */
	अटल स्थिर काष्ठा ata_port_info via_mwdma_info_borked = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.port_ops = &via_port_ops_noirq,
	पूर्ण;
	/* VIA UDMA 33 devices (and borked 66) */
	अटल स्थिर काष्ठा ata_port_info via_udma33_info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.port_ops = &via_port_ops
	पूर्ण;
	/* VIA UDMA 66 devices */
	अटल स्थिर काष्ठा ata_port_info via_udma66_info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &via_port_ops
	पूर्ण;
	/* VIA UDMA 100 devices */
	अटल स्थिर काष्ठा ata_port_info via_udma100_info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &via_port_ops
	पूर्ण;
	/* UDMA133 with bad AST (All current 133) */
	अटल स्थिर काष्ठा ata_port_info via_udma133_info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,	/* FIXME: should check north bridge */
		.port_ops = &via_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	काष्ठा pci_dev *isa;
	स्थिर काष्ठा via_isa_bridge *config;
	u8 enable;
	अचिन्हित दीर्घ flags = id->driver_data;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर (flags & VIA_IDFLAG_SINGLE)
		ppi[1] = &ata_dummy_port_info;

	/* To find out how the IDE will behave and what features we
	   actually have to look at the bridge not the IDE controller */
	क्रम (config = via_isa_bridges; config->id != PCI_DEVICE_ID_VIA_ANON;
	     config++)
		अगर ((isa = pci_get_device(PCI_VENDOR_ID_VIA +
			!!(config->flags & VIA_BAD_ID),
			config->id, शून्य))) अणु
			u8 rev = isa->revision;
			pci_dev_put(isa);

			अगर ((id->device == 0x0415 || id->device == 0x3164) &&
			    (config->id != id->device))
				जारी;

			अगर (rev >= config->rev_min && rev <= config->rev_max)
				अवरोध;
		पूर्ण

	अगर (!(config->flags & VIA_NO_ENABLES)) अणु
		/* 0x40 low bits indicate enabled channels */
		pci_पढ़ो_config_byte(pdev, 0x40 , &enable);
		enable &= 3;
		अगर (enable == 0)
			वापस -ENODEV;
	पूर्ण

	/* Clock set up */
	चयन (config->udma_mask) अणु
	हाल 0x00:
		अगर (config->flags & VIA_NO_UNMASK)
			ppi[0] = &via_mwdma_info_borked;
		अन्यथा
			ppi[0] = &via_mwdma_info;
		अवरोध;
	हाल ATA_UDMA2:
		ppi[0] = &via_udma33_info;
		अवरोध;
	हाल ATA_UDMA4:
		ppi[0] = &via_udma66_info;
		अवरोध;
	हाल ATA_UDMA5:
		ppi[0] = &via_udma100_info;
		अवरोध;
	हाल ATA_UDMA6:
		ppi[0] = &via_udma133_info;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -ENODEV;
 	पूर्ण

	via_fixup(pdev, config);

	/* We have established the device type, now fire it up */
	वापस ata_pci_bmdma_init_one(pdev, ppi, &via_sht, (व्योम *)config, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/**
 *	via_reinit_one		-	reinit after resume
 *	@pdev: PCI device
 *
 *	Called when the VIA PATA device is resumed. We must then
 *	reconfigure the fअगरo and other setup we may have altered. In
 *	addition the kernel needs to have the resume methods on PCI
 *	quirk supported.
 */

अटल पूर्णांक via_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	via_fixup(pdev, host->निजी_data);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id via[] = अणु
	अणु PCI_VDEVICE(VIA, 0x0415), पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x0571), पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x0581), पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x1571), पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x3164), पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x5324), पूर्ण,
	अणु PCI_VDEVICE(VIA, 0xC409), VIA_IDFLAG_SINGLE पूर्ण,
	अणु PCI_VDEVICE(VIA, 0x9001), VIA_IDFLAG_SINGLE पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver via_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= via,
	.probe 		= via_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= via_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(via_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for VIA PATA");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, via);
MODULE_VERSION(DRV_VERSION);
