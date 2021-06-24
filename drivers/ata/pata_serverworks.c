<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_serverworks.c 	- Serverworks PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *			  (C) 2010 Bartlomiej Zolnierkiewicz
 *
 * based upon
 *
 * serverworks.c
 *
 * Copyright (C) 1998-2000 Michel Aubry
 * Copyright (C) 1998-2000 Andrzej Krzysztofowicz
 * Copyright (C) 1998-2000 Andre Hedrick <andre@linux-ide.org>
 * Portions copyright (c) 2001 Sun Microप्रणालीs
 *
 *
 * RCC/ServerWorks IDE driver क्रम Linux
 *
 *   OSB4: `Open South Bridge' IDE Interface (fn 1)
 *         supports UDMA mode 2 (33 MB/s)
 *
 *   CSB5: `Champion South Bridge' IDE Interface (fn 1)
 *         all revisions support UDMA mode 4 (66 MB/s)
 *         revision A2.0 and up support UDMA mode 5 (100 MB/s)
 *
 *         *** The CSB5 करोes not provide ANY रेजिस्टर ***
 *         *** to detect 80-conductor cable presence. ***
 *
 *   CSB6: `Champion South Bridge' IDE Interface (optional: third channel)
 *
 * Documentation:
 *	Available under NDA only. Errata info very hard to get.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_serverworks"
#घोषणा DRV_VERSION "0.4.3"

#घोषणा SVWKS_CSB5_REVISION_NEW	0x92 /* min PCI_REVISION_ID क्रम UDMA5 (A2.0) */
#घोषणा SVWKS_CSB6_REVISION	0xa0 /* min PCI_REVISION_ID क्रम UDMA4 (A1.0) */

/* Seagate Barracuda ATA IV Family drives in UDMA mode 5
 * can overrun their FIFOs when used with the CSB5 */

अटल स्थिर अक्षर *csb_bad_ata100[] = अणु
	"ST320011A",
	"ST340016A",
	"ST360021A",
	"ST380021A",
	शून्य
पूर्ण;

/**
 *	oem_cable	-	Dell/Sun serverworks cable detection
 *	@ap: ATA port to करो cable detect
 *
 *	Dell PowerEdge and Sun Cobalt 'Alpine' hide the 40/80 pin select
 *	क्रम their पूर्णांकerfaces in the top two bits of the subप्रणाली ID.
 */

अटल पूर्णांक oem_cable(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (pdev->subप्रणाली_device & (1 << (ap->port_no + 14)))
		वापस ATA_CBL_PATA80;
	वापस ATA_CBL_PATA40;
पूर्ण

काष्ठा sv_cable_table अणु
	पूर्णांक device;
	पूर्णांक subvenकरोr;
	पूर्णांक (*cable_detect)(काष्ठा ata_port *ap);
पूर्ण;

अटल काष्ठा sv_cable_table cable_detect[] = अणु
	अणु PCI_DEVICE_ID_SERVERWORKS_CSB5IDE,   PCI_VENDOR_ID_DELL, oem_cable पूर्ण,
	अणु PCI_DEVICE_ID_SERVERWORKS_CSB6IDE,   PCI_VENDOR_ID_DELL, oem_cable पूर्ण,
	अणु PCI_DEVICE_ID_SERVERWORKS_CSB5IDE,   PCI_VENDOR_ID_SUN,  oem_cable पूर्ण,
	अणु PCI_DEVICE_ID_SERVERWORKS_OSB4IDE,   PCI_ANY_ID, ata_cable_40wire  पूर्ण,
	अणु PCI_DEVICE_ID_SERVERWORKS_CSB5IDE,   PCI_ANY_ID, ata_cable_unknown पूर्ण,
	अणु PCI_DEVICE_ID_SERVERWORKS_CSB6IDE,   PCI_ANY_ID, ata_cable_unknown पूर्ण,
	अणु PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2,  PCI_ANY_ID, ata_cable_unknown पूर्ण,
	अणु PCI_DEVICE_ID_SERVERWORKS_HT1000IDE, PCI_ANY_ID, ata_cable_unknown पूर्ण,
	अणु पूर्ण
पूर्ण;

/**
 *	serverworks_cable_detect	-	cable detection
 *	@ap: ATA port
 *
 *	Perक्रमm cable detection according to the device and subvenकरोr
 *	identअगरications
 */

अटल पूर्णांक serverworks_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा sv_cable_table *cb = cable_detect;

	जबतक(cb->device) अणु
		अगर (cb->device == pdev->device &&
		    (cb->subvenकरोr == pdev->subप्रणाली_venकरोr ||
		      cb->subvenकरोr == PCI_ANY_ID)) अणु
			वापस cb->cable_detect(ap);
		पूर्ण
		cb++;
	पूर्ण

	BUG();
	वापस -1;	/* समाप्त compiler warning */
पूर्ण

/**
 *	serverworks_is_csb	-	Check क्रम CSB or OSB
 *	@pdev: PCI device to check
 *
 *	Returns true अगर the device being checked is known to be a CSB
 *	series device.
 */

अटल u8 serverworks_is_csb(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_SERVERWORKS_CSB5IDE:
		हाल PCI_DEVICE_ID_SERVERWORKS_CSB6IDE:
		हाल PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2:
		हाल PCI_DEVICE_ID_SERVERWORKS_HT1000IDE:
			वापस 1;
		शेष:
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	serverworks_osb4_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: Mask of proposed modes
 *
 *	Filter the offered modes क्रम the device to apply controller
 *	specअगरic rules. OSB4 requires no UDMA क्रम disks due to a FIFO
 *	bug we hit.
 */

अटल अचिन्हित दीर्घ serverworks_osb4_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	अगर (adev->class == ATA_DEV_ATA)
		mask &= ~ATA_MASK_UDMA;
	वापस mask;
पूर्ण


/**
 *	serverworks_csb_filter	-	mode selection filter
 *	@adev: ATA device
 *	@mask: Mask of proposed modes
 *
 *	Check the blacklist and disable UDMA5 अगर matched
 */

अटल अचिन्हित दीर्घ serverworks_csb_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	स्थिर अक्षर *p;
	अक्षर model_num[ATA_ID_PROD_LEN + 1];
	पूर्णांक i;

	/* Disk, UDMA */
	अगर (adev->class != ATA_DEV_ATA)
		वापस mask;

	/* Actually करो need to check */
	ata_id_c_string(adev->id, model_num, ATA_ID_PROD, माप(model_num));

	क्रम (i = 0; (p = csb_bad_ata100[i]) != शून्य; i++) अणु
		अगर (!म_भेद(p, model_num))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	पूर्ण
	वापस mask;
पूर्ण

/**
 *	serverworks_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the OSB4/CSB5 timing रेजिस्टरs क्रम PIO. The PIO रेजिस्टर
 *	load is करोne as a simple lookup.
 */
अटल व्योम serverworks_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u8 pio_mode[] = अणु 0x5d, 0x47, 0x34, 0x22, 0x20 पूर्ण;
	पूर्णांक offset = 1 + 2 * ap->port_no - adev->devno;
	पूर्णांक devbits = (2 * ap->port_no + adev->devno) * 4;
	u16 csb5_pio;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक pio = adev->pio_mode - XFER_PIO_0;

	pci_ग_लिखो_config_byte(pdev, 0x40 + offset, pio_mode[pio]);

	/* The OSB4 just requires the timing but the CSB series want the
	   mode number as well */
	अगर (serverworks_is_csb(pdev)) अणु
		pci_पढ़ो_config_word(pdev, 0x4A, &csb5_pio);
		csb5_pio &= ~(0x0F << devbits);
		pci_ग_लिखो_config_word(pdev, 0x4A, csb5_pio | (pio << devbits));
	पूर्ण
पूर्ण

/**
 *	serverworks_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the MWDMA/UDMA modes क्रम the serverworks OSB4/CSB5
 *	chipset. The MWDMA mode values are pulled from a lookup table
 *	जबतक the chipset uses mode number क्रम UDMA.
 */

अटल व्योम serverworks_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u8 dma_mode[] = अणु 0x77, 0x21, 0x20 पूर्ण;
	पूर्णांक offset = 1 + 2 * ap->port_no - adev->devno;
	पूर्णांक devbits = 2 * ap->port_no + adev->devno;
	u8 ultra;
	u8 ultra_cfg;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	pci_पढ़ो_config_byte(pdev, 0x54, &ultra_cfg);
	pci_पढ़ो_config_byte(pdev, 0x56 + ap->port_no, &ultra);
	ultra &= ~(0x0F << (adev->devno * 4));

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		pci_ग_लिखो_config_byte(pdev, 0x44 + offset,  0x20);

		ultra |= (adev->dma_mode - XFER_UDMA_0)
					<< (adev->devno * 4);
		ultra_cfg |=  (1 << devbits);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_byte(pdev, 0x44 + offset,
			dma_mode[adev->dma_mode - XFER_MW_DMA_0]);
		ultra_cfg &= ~(1 << devbits);
	पूर्ण
	pci_ग_लिखो_config_byte(pdev, 0x56 + ap->port_no, ultra);
	pci_ग_लिखो_config_byte(pdev, 0x54, ultra_cfg);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा serverworks_osb4_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
	.sg_tablesize	= LIBATA_DUMB_MAX_PRD,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा serverworks_csb_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations serverworks_osb4_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.qc_prep	= ata_bmdma_dumb_qc_prep,
	.cable_detect	= serverworks_cable_detect,
	.mode_filter	= serverworks_osb4_filter,
	.set_piomode	= serverworks_set_piomode,
	.set_dmamode	= serverworks_set_dmamode,
पूर्ण;

अटल काष्ठा ata_port_operations serverworks_csb_port_ops = अणु
	.inherits	= &serverworks_osb4_port_ops,
	.qc_prep	= ata_bmdma_qc_prep,
	.mode_filter	= serverworks_csb_filter,
पूर्ण;

अटल पूर्णांक serverworks_fixup_osb4(काष्ठा pci_dev *pdev)
अणु
	u32 reg;
	काष्ठा pci_dev *isa_dev = pci_get_device(PCI_VENDOR_ID_SERVERWORKS,
		  PCI_DEVICE_ID_SERVERWORKS_OSB4, शून्य);
	अगर (isa_dev) अणु
		pci_पढ़ो_config_dword(isa_dev, 0x64, &reg);
		reg &= ~0x00002000; /* disable 600ns पूर्णांकerrupt mask */
		अगर (!(reg & 0x00004000))
			prपूर्णांकk(KERN_DEBUG DRV_NAME ": UDMA not BIOS enabled.\n");
		reg |=  0x00004000; /* enable UDMA/33 support */
		pci_ग_लिखो_config_dword(isa_dev, 0x64, reg);
		pci_dev_put(isa_dev);
		वापस 0;
	पूर्ण
	prपूर्णांकk(KERN_WARNING DRV_NAME ": Unable to find bridge.\n");
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक serverworks_fixup_csb(काष्ठा pci_dev *pdev)
अणु
	u8 btr;

	/* Third Channel Test */
	अगर (!(PCI_FUNC(pdev->devfn) & 1)) अणु
		काष्ठा pci_dev * findev = शून्य;
		u32 reg4c = 0;
		findev = pci_get_device(PCI_VENDOR_ID_SERVERWORKS,
			PCI_DEVICE_ID_SERVERWORKS_CSB5, शून्य);
		अगर (findev) अणु
			pci_पढ़ो_config_dword(findev, 0x4C, &reg4c);
			reg4c &= ~0x000007FF;
			reg4c |=  0x00000040;
			reg4c |=  0x00000020;
			pci_ग_लिखो_config_dword(findev, 0x4C, reg4c);
			pci_dev_put(findev);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा pci_dev * findev = शून्य;
		u8 reg41 = 0;

		findev = pci_get_device(PCI_VENDOR_ID_SERVERWORKS,
				PCI_DEVICE_ID_SERVERWORKS_CSB6, शून्य);
		अगर (findev) अणु
			pci_पढ़ो_config_byte(findev, 0x41, &reg41);
			reg41 &= ~0x40;
			pci_ग_लिखो_config_byte(findev, 0x41, reg41);
			pci_dev_put(findev);
		पूर्ण
	पूर्ण
	/* setup the UDMA Control रेजिस्टर
	 *
	 * 1. clear bit 6 to enable DMA
	 * 2. enable DMA modes with bits 0-1
	 * 	00 : legacy
	 * 	01 : udma2
	 * 	10 : udma2/udma4
	 * 	11 : udma2/udma4/udma5
	 */
	pci_पढ़ो_config_byte(pdev, 0x5A, &btr);
	btr &= ~0x40;
	अगर (!(PCI_FUNC(pdev->devfn) & 1))
		btr |= 0x2;
	अन्यथा
		btr |= (pdev->revision >= SVWKS_CSB5_REVISION_NEW) ? 0x3 : 0x2;
	pci_ग_लिखो_config_byte(pdev, 0x5A, btr);

	वापस btr;
पूर्ण

अटल व्योम serverworks_fixup_ht1000(काष्ठा pci_dev *pdev)
अणु
	u8 btr;
	/* Setup HT1000 SouthBridge Controller - Single Channel Only */
	pci_पढ़ो_config_byte(pdev, 0x5A, &btr);
	btr &= ~0x40;
	btr |= 0x3;
	pci_ग_लिखो_config_byte(pdev, 0x5A, btr);
पूर्ण

अटल पूर्णांक serverworks_fixup(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc = 0;

	/* Force master latency समयr to 64 PCI घड़ीs */
	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 0x40);

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_SERVERWORKS_OSB4IDE:
		rc = serverworks_fixup_osb4(pdev);
		अवरोध;
	हाल PCI_DEVICE_ID_SERVERWORKS_CSB5IDE:
		ata_pci_bmdma_clear_simplex(pdev);
		fallthrough;
	हाल PCI_DEVICE_ID_SERVERWORKS_CSB6IDE:
	हाल PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2:
		rc = serverworks_fixup_csb(pdev);
		अवरोध;
	हाल PCI_DEVICE_ID_SERVERWORKS_HT1000IDE:
		serverworks_fixup_ht1000(pdev);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक serverworks_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info[4] = अणु
		अणु /* OSB4 */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.port_ops = &serverworks_osb4_port_ops
		पूर्ण, अणु /* OSB4 no UDMA */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			/* No UDMA */
			.port_ops = &serverworks_osb4_port_ops
		पूर्ण, अणु /* CSB5 */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.port_ops = &serverworks_csb_port_ops
		पूर्ण, अणु /* CSB5 - later revisions*/
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &serverworks_csb_port_ops
		पूर्ण
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info[id->driver_data], शून्य पूर्ण;
	काष्ठा scsi_host_ढाँचा *sht = &serverworks_csb_sht;
	पूर्णांक rc;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = serverworks_fixup(pdev);

	/* OSB4 : South Bridge and IDE */
	अगर (pdev->device == PCI_DEVICE_ID_SERVERWORKS_OSB4IDE) अणु
		/* Select non UDMA capable OSB4 अगर we can't करो fixups */
		अगर (rc < 0)
			ppi[0] = &info[1];
		sht = &serverworks_osb4_sht;
	पूर्ण
	/* setup CSB5/CSB6 : South Bridge and IDE option RAID */
	अन्यथा अगर ((pdev->device == PCI_DEVICE_ID_SERVERWORKS_CSB5IDE) ||
		 (pdev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE) ||
		 (pdev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2)) अणु

		 /* If the वापसed btr is the newer revision then
		    select the right info block */
		 अगर (rc == 3)
		 	ppi[0] = &info[3];

		/* Is this the 3rd channel CSB6 IDE ? */
		अगर (pdev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2)
			ppi[1] = &ata_dummy_port_info;
	पूर्ण

	वापस ata_pci_bmdma_init_one(pdev, ppi, sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक serverworks_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	(व्योम)serverworks_fixup(pdev);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id serverworks[] = अणु
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_OSB4IDE), 0पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_CSB5IDE), 2पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_CSB6IDE), 2पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2), 2पूर्ण,
	अणु PCI_VDEVICE(SERVERWORKS, PCI_DEVICE_ID_SERVERWORKS_HT1000IDE), 2पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver serverworks_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= serverworks,
	.probe 		= serverworks_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= serverworks_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(serverworks_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Serverworks OSB4/CSB5/CSB6");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, serverworks);
MODULE_VERSION(DRV_VERSION);
