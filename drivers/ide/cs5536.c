<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CS5536 PATA support
 * (C) 2007 Martin K. Petersen <mkp@mkp.net>
 * (C) 2009 Bartlomiej Zolnierkiewicz
 *
 * Documentation:
 *	Available from AMD web site.
 *
 * The IDE timing रेजिस्टरs क्रम the CS5536 live in the Geode Machine
 * Specअगरic Register file and not PCI config space.  Most BIOSes
 * भवize the PCI रेजिस्टरs so the chip looks like a standard IDE
 * controller.  Unक्रमtunately not all implementations get this right.
 * In particular some have problems with unaligned accesses to the
 * भवized PCI रेजिस्टरs.  This driver always करोes full dword
 * ग_लिखोs to work around the issue.  Also, in हाल of a bad BIOS this
 * driver can be loaded with the "msr=1" parameter which क्रमces using
 * the Machine Specअगरic Registers to configure the device.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>
#समावेश <यंत्र/msr.h>

#घोषणा DRV_NAME	"cs5536"

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

	IDE_CAST_CMD_SHIFT	= 24,
	IDE_CAST_CMD_MASK	= 0xff,

	IDE_ETC_UDMA_MASK	= 0xc0,
पूर्ण;

अटल पूर्णांक use_msr;

अटल पूर्णांक cs5536_पढ़ो(काष्ठा pci_dev *pdev, पूर्णांक reg, u32 *val)
अणु
	अगर (unlikely(use_msr)) अणु
		u32 dummy;

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

अटल व्योम cs5536_program_dtc(ide_drive_t *drive, u8 tim)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(drive->hwअगर->dev);
	पूर्णांक dshअगरt = (drive->dn & 1) ? IDE_D1_SHIFT : IDE_D0_SHIFT;
	u32 dtc;

	cs5536_पढ़ो(pdev, DTC, &dtc);
	dtc &= ~(IDE_DRV_MASK << dshअगरt);
	dtc |= tim << dshअगरt;
	cs5536_ग_लिखो(pdev, DTC, dtc);
पूर्ण

/**
 *	cs5536_cable_detect	-	detect cable type
 *	@hwअगर: Port to detect on
 *
 *	Perक्रमm cable detection क्रम ATA66 capable cable.
 *
 *	Returns a cable type.
 */

अटल u8 cs5536_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	u32 cfg;

	cs5536_पढ़ो(pdev, CFG, &cfg);

	अगर (cfg & IDE_CFG_CABLE)
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

/**
 *	cs5536_set_pio_mode		-	PIO timing setup
 *	@hwअगर: ATA port
 *	@drive: ATA device
 */

अटल व्योम cs5536_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
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

	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	ide_drive_t *pair = ide_get_pair_dev(drive);
	पूर्णांक cshअगरt = (drive->dn & 1) ? IDE_CAST_D1_SHIFT : IDE_CAST_D0_SHIFT;
	अचिन्हित दीर्घ timings = (अचिन्हित दीर्घ)ide_get_drivedata(drive);
	u32 cast;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	u8 cmd_pio = pio;

	अगर (pair)
		cmd_pio = min_t(u8, pio, pair->pio_mode - XFER_PIO_0);

	timings &= (IDE_DRV_MASK << 8);
	timings |= drv_timings[pio];
	ide_set_drivedata(drive, (व्योम *)timings);

	cs5536_program_dtc(drive, drv_timings[pio]);

	cs5536_पढ़ो(pdev, CAST, &cast);

	cast &= ~(IDE_CAST_DRV_MASK << cshअगरt);
	cast |= addr_timings[pio] << cshअगरt;

	cast &= ~(IDE_CAST_CMD_MASK << IDE_CAST_CMD_SHIFT);
	cast |= cmd_timings[cmd_pio] << IDE_CAST_CMD_SHIFT;

	cs5536_ग_लिखो(pdev, CAST, cast);
पूर्ण

/**
 *	cs5536_set_dma_mode		-	DMA timing setup
 *	@hwअगर: ATA port
 *	@drive: ATA device
 */

अटल व्योम cs5536_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अटल स्थिर u8 udma_timings[6] = अणु
		0xc2, 0xc1, 0xc0, 0xc4, 0xc5, 0xc6,
	पूर्ण;

	अटल स्थिर u8 mwdma_timings[3] = अणु
		0x67, 0x21, 0x20,
	पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(hwअगर->dev);
	पूर्णांक dshअगरt = (drive->dn & 1) ? IDE_D1_SHIFT : IDE_D0_SHIFT;
	अचिन्हित दीर्घ timings = (अचिन्हित दीर्घ)ide_get_drivedata(drive);
	u32 etc;
	स्थिर u8 mode = drive->dma_mode;

	cs5536_पढ़ो(pdev, ETC, &etc);

	अगर (mode >= XFER_UDMA_0) अणु
		etc &= ~(IDE_DRV_MASK << dshअगरt);
		etc |= udma_timings[mode - XFER_UDMA_0] << dshअगरt;
	पूर्ण अन्यथा अणु /* MWDMA */
		etc &= ~(IDE_ETC_UDMA_MASK << dshअगरt);
		timings &= IDE_DRV_MASK;
		timings |= mwdma_timings[mode - XFER_MW_DMA_0] << 8;
		ide_set_drivedata(drive, (व्योम *)timings);
	पूर्ण

	cs5536_ग_लिखो(pdev, ETC, etc);
पूर्ण

अटल व्योम cs5536_dma_start(ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ timings = (अचिन्हित दीर्घ)ide_get_drivedata(drive);

	अगर (drive->current_speed < XFER_UDMA_0 &&
	    (timings >> 8) != (timings & IDE_DRV_MASK))
		cs5536_program_dtc(drive, timings >> 8);

	ide_dma_start(drive);
पूर्ण

अटल पूर्णांक cs5536_dma_end(ide_drive_t *drive)
अणु
	पूर्णांक ret = ide_dma_end(drive);
	अचिन्हित दीर्घ timings = (अचिन्हित दीर्घ)ide_get_drivedata(drive);

	अगर (drive->current_speed < XFER_UDMA_0 &&
	    (timings >> 8) != (timings & IDE_DRV_MASK))
		cs5536_program_dtc(drive, timings & IDE_DRV_MASK);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops cs5536_port_ops = अणु
	.set_pio_mode		= cs5536_set_pio_mode,
	.set_dma_mode		= cs5536_set_dma_mode,
	.cable_detect		= cs5536_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops cs5536_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= cs5536_dma_start,
	.dma_end		= cs5536_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info cs5536_info = अणु
	.name		= DRV_NAME,
	.port_ops	= &cs5536_port_ops,
	.dma_ops	= &cs5536_dma_ops,
	.host_flags	= IDE_HFLAG_SINGLE,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA5,
पूर्ण;

/**
 *	cs5536_init_one
 *	@dev: PCI device
 *	@id: Entry in match table
 */

अटल पूर्णांक cs5536_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	u32 cfg;

	अगर (use_msr)
		prपूर्णांकk(KERN_INFO DRV_NAME ": Using MSR regs instead of PCI\n");

	cs5536_पढ़ो(dev, CFG, &cfg);

	अगर ((cfg & IDE_CFG_CHANEN) == 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": disabled by BIOS\n");
		वापस -ENODEV;
	पूर्ण

	वापस ide_pci_init_one(dev, &cs5536_info, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cs5536_pci_tbl[] = अणु
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_CS5536_IDE), पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cs5536_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= cs5536_pci_tbl,
	.probe		= cs5536_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

module_pci_driver(cs5536_pci_driver);

MODULE_AUTHOR("Martin K. Petersen, Bartlomiej Zolnierkiewicz");
MODULE_DESCRIPTION("low-level driver for the CS5536 IDE controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cs5536_pci_tbl);

module_param_named(msr, use_msr, पूर्णांक, 0644);
MODULE_PARM_DESC(msr, "Force using MSR to configure IDE function (Default: 0)");
