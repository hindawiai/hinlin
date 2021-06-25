<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_cs5536.c	- CS5536 PATA क्रम new ATA layer
 *			  (C) 2007 Martin K. Petersen <mkp@mkp.net>
 *			  (C) 2011 Bartlomiej Zolnierkiewicz
 *
 * Documentation:
 *	Available from AMD web site.
 *
 * The IDE timing रेजिस्टरs क्रम the CS5536 live in the Geode Machine
 * Specअगरic Register file and not PCI config space.  Most BIOSes
 * भवize the PCI रेजिस्टरs so the chip looks like a standard IDE
 * controller.	Unक्रमtunately not all implementations get this right.
 * In particular some have problems with unaligned accesses to the
 * भवized PCI रेजिस्टरs.  This driver always करोes full dword
 * ग_लिखोs to work around the issue.  Also, in हाल of a bad BIOS this
 * driver can be loaded with the "msr=1" parameter which क्रमces using
 * the Machine Specअगरic Registers to configure the device.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/libata.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/dmi.h>

#अगर_घोषित CONFIG_X86_32
#समावेश <यंत्र/msr.h>
अटल पूर्णांक use_msr;
module_param_named(msr, use_msr, पूर्णांक, 0644);
MODULE_PARM_DESC(msr, "Force using MSR to configure IDE function (Default: 0)");
#अन्यथा
#अघोषित rdmsr	/* aव्योम accidental MSR usage on, e.g. x86-64 */
#अघोषित wrmsr
#घोषणा rdmsr(x, y, z) करो अणु पूर्ण जबतक (0)
#घोषणा wrmsr(x, y, z) करो अणु पूर्ण जबतक (0)
#घोषणा use_msr 0
#पूर्ण_अगर

#घोषणा DRV_NAME	"pata_cs5536"
#घोषणा DRV_VERSION	"0.0.8"

क्रमागत अणु
	MSR_IDE_CFG		= 0x51300010,
	PCI_IDE_CFG		= 0x40,

	CFG			= 0,
	DTC			= 2,
	CAST			= 3,
	ETC			= 4,

	IDE_CFG_CHANEN		= (1 << 1),
	IDE_CFG_CABLE		= (1 << 17) | (1 << 16),

	IDE_D0_SHIFT		= 24,
	IDE_D1_SHIFT		= 16,
	IDE_DRV_MASK		= 0xff,

	IDE_CAST_D0_SHIFT	= 6,
	IDE_CAST_D1_SHIFT	= 4,
	IDE_CAST_DRV_MASK	= 0x3,
	IDE_CAST_CMD_MASK	= 0xff,
	IDE_CAST_CMD_SHIFT	= 24,

	IDE_ETC_UDMA_MASK	= 0xc0,
पूर्ण;

/* Some Bachmann OT200 devices have a non working UDMA support due a
 * missing resistor.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id udma_quirk_dmi_table[] = अणु
	अणु
		.ident = "Bachmann electronic OT200",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Bachmann electronic"),
			DMI_MATCH(DMI_PRODUCT_NAME, "OT200"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "1")
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक cs5536_पढ़ो(काष्ठा pci_dev *pdev, पूर्णांक reg, u32 *val)
अणु
	अगर (unlikely(use_msr)) अणु
		u32 dummy __maybe_unused;

		rdmsr(MSR_IDE_CFG + reg, *val, dummy);
		वापस 0;
	पूर्ण

	वापस pci_पढ़ो_config_dword(pdev, PCI_IDE_CFG + reg * 4, val);
पूर्ण

अटल पूर्णांक cs5536_ग_लिखो(काष्ठा pci_dev *pdev, पूर्णांक reg, पूर्णांक val)
अणु
	अगर (unlikely(use_msr)) अणु
		wrmsr(MSR_IDE_CFG + reg, val, 0);
		वापस 0;
	पूर्ण

	वापस pci_ग_लिखो_config_dword(pdev, PCI_IDE_CFG + reg * 4, val);
पूर्ण

अटल व्योम cs5536_program_dtc(काष्ठा ata_device *adev, u8 tim)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(adev->link->ap->host->dev);
	पूर्णांक dshअगरt = adev->devno ? IDE_D1_SHIFT : IDE_D0_SHIFT;
	u32 dtc;

	cs5536_पढ़ो(pdev, DTC, &dtc);
	dtc &= ~(IDE_DRV_MASK << dshअगरt);
	dtc |= tim << dshअगरt;
	cs5536_ग_लिखो(pdev, DTC, dtc);
पूर्ण

/**
 *	cs5536_cable_detect	-	detect cable type
 *	@ap: Port to detect on
 *
 *	Perक्रमm cable detection क्रम ATA66 capable cable.
 *
 *	Returns a cable type.
 */

अटल पूर्णांक cs5536_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 cfg;

	cs5536_पढ़ो(pdev, CFG, &cfg);

	अगर (cfg & IDE_CFG_CABLE)
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

/**
 *	cs5536_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 */

अटल व्योम cs5536_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u8 drv_timings[5] = अणु
		0x98, 0x55, 0x32, 0x21, 0x20,
	पूर्ण;

	अटल स्थिर u8 addr_timings[5] = अणु
		0x2, 0x1, 0x0, 0x0, 0x0,
	पूर्ण;

	अटल स्थिर u8 cmd_timings[5] = अणु
		0x99, 0x92, 0x90, 0x22, 0x20,
	पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा ata_device *pair = ata_dev_pair(adev);
	पूर्णांक mode = adev->pio_mode - XFER_PIO_0;
	पूर्णांक cmdmode = mode;
	पूर्णांक cshअगरt = adev->devno ? IDE_CAST_D1_SHIFT : IDE_CAST_D0_SHIFT;
	u32 cast;

	अगर (pair)
		cmdmode = min(mode, pair->pio_mode - XFER_PIO_0);

	cs5536_program_dtc(adev, drv_timings[mode]);

	cs5536_पढ़ो(pdev, CAST, &cast);

	cast &= ~(IDE_CAST_DRV_MASK << cshअगरt);
	cast |= addr_timings[mode] << cshअगरt;

	cast &= ~(IDE_CAST_CMD_MASK << IDE_CAST_CMD_SHIFT);
	cast |= cmd_timings[cmdmode] << IDE_CAST_CMD_SHIFT;

	cs5536_ग_लिखो(pdev, CAST, cast);
पूर्ण

/**
 *	cs5536_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 */

अटल व्योम cs5536_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u8 udma_timings[6] = अणु
		0xc2, 0xc1, 0xc0, 0xc4, 0xc5, 0xc6,
	पूर्ण;

	अटल स्थिर u8 mwdma_timings[3] = अणु
		0x67, 0x21, 0x20,
	पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 etc;
	पूर्णांक mode = adev->dma_mode;
	पूर्णांक dshअगरt = adev->devno ? IDE_D1_SHIFT : IDE_D0_SHIFT;

	cs5536_पढ़ो(pdev, ETC, &etc);

	अगर (mode >= XFER_UDMA_0) अणु
		etc &= ~(IDE_DRV_MASK << dshअगरt);
		etc |= udma_timings[mode - XFER_UDMA_0] << dshअगरt;
	पूर्ण अन्यथा अणु /* MWDMA */
		etc &= ~(IDE_ETC_UDMA_MASK << dshअगरt);
		cs5536_program_dtc(adev, mwdma_timings[mode - XFER_MW_DMA_0]);
	पूर्ण

	cs5536_ग_लिखो(pdev, ETC, etc);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cs5536_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations cs5536_port_ops = अणु
	.inherits		= &ata_bmdma32_port_ops,
	.cable_detect		= cs5536_cable_detect,
	.set_piomode		= cs5536_set_piomode,
	.set_dmamode		= cs5536_set_dmamode,
पूर्ण;

/**
 *	cs5536_init_one
 *	@dev: PCI device
 *	@id: Entry in match table
 *
 */

अटल पूर्णांक cs5536_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.port_ops = &cs5536_port_ops,
	पूर्ण;

	अटल स्थिर काष्ठा ata_port_info no_udma_info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.port_ops = &cs5536_port_ops,
	पूर्ण;


	स्थिर काष्ठा ata_port_info *ppi[2];
	u32 cfg;

	अगर (dmi_check_प्रणाली(udma_quirk_dmi_table))
		ppi[0] = &no_udma_info;
	अन्यथा
		ppi[0] = &info;

	ppi[1] = &ata_dummy_port_info;

	अगर (use_msr)
		prपूर्णांकk(KERN_ERR DRV_NAME ": Using MSR regs instead of PCI\n");

	cs5536_पढ़ो(dev, CFG, &cfg);

	अगर ((cfg & IDE_CFG_CHANEN) == 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": disabled by BIOS\n");
		वापस -ENODEV;
	पूर्ण

	वापस ata_pci_bmdma_init_one(dev, ppi, &cs5536_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cs5536[] = अणु
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_IDE), पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_DEV_IDE), पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cs5536_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= cs5536,
	.probe		= cs5536_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cs5536_pci_driver);

MODULE_AUTHOR("Martin K. Petersen");
MODULE_DESCRIPTION("low-level driver for the CS5536 IDE controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cs5536);
MODULE_VERSION(DRV_VERSION);
