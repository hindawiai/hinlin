<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata-cs5535.c 	- CS5535 PATA क्रम new ATA layer
 *			  (C) 2005-2006 Red Hat Inc
 *			  Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * based upon cs5535.c from AMD <Jens.Alपंचांगann@amd.com> as cleaned up and
 * made पढ़ोable and Linux style by Wolfgang Zuleger <wolfgang.zuleger@gmx.de>
 * and Alexander Kiausch <alex.kiausch@t-online.de>
 *
 * Loosely based on the piix & svwks drivers.
 *
 * Documentation:
 *	Available from AMD web site.
 * TODO
 *	Review errata to see अगर serializing is necessary
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <यंत्र/msr.h>

#घोषणा DRV_NAME	"pata_cs5535"
#घोषणा DRV_VERSION	"0.2.12"

/*
 *	The Geode (Aka Athlon GX now) uses an पूर्णांकernal MSR based
 *	bus प्रणाली क्रम control. Demented but there you go.
 */

#घोषणा MSR_ATAC_BASE    	0x51300000
#घोषणा ATAC_GLD_MSR_CAP 	(MSR_ATAC_BASE+0)
#घोषणा ATAC_GLD_MSR_CONFIG    (MSR_ATAC_BASE+0x01)
#घोषणा ATAC_GLD_MSR_SMI       (MSR_ATAC_BASE+0x02)
#घोषणा ATAC_GLD_MSR_ERROR     (MSR_ATAC_BASE+0x03)
#घोषणा ATAC_GLD_MSR_PM        (MSR_ATAC_BASE+0x04)
#घोषणा ATAC_GLD_MSR_DIAG      (MSR_ATAC_BASE+0x05)
#घोषणा ATAC_IO_BAR            (MSR_ATAC_BASE+0x08)
#घोषणा ATAC_RESET             (MSR_ATAC_BASE+0x10)
#घोषणा ATAC_CH0D0_PIO         (MSR_ATAC_BASE+0x20)
#घोषणा ATAC_CH0D0_DMA         (MSR_ATAC_BASE+0x21)
#घोषणा ATAC_CH0D1_PIO         (MSR_ATAC_BASE+0x22)
#घोषणा ATAC_CH0D1_DMA         (MSR_ATAC_BASE+0x23)
#घोषणा ATAC_PCI_ABRTERR       (MSR_ATAC_BASE+0x24)

#घोषणा ATAC_BM0_CMD_PRIM      0x00
#घोषणा ATAC_BM0_STS_PRIM      0x02
#घोषणा ATAC_BM0_PRD           0x04

#घोषणा CS5535_CABLE_DETECT    0x48

/**
 *	cs5535_cable_detect	-	detect cable type
 *	@ap: Port to detect on
 *
 *	Perक्रमm cable detection क्रम ATA66 capable cable. Return a libata
 *	cable type.
 */

अटल पूर्णांक cs5535_cable_detect(काष्ठा ata_port *ap)
अणु
	u8 cable;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	pci_पढ़ो_config_byte(pdev, CS5535_CABLE_DETECT, &cable);
	अगर (cable & 1)
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

/**
 *	cs5535_set_piomode		-	PIO setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: device on the पूर्णांकerface
 *
 *	Set our PIO requirements. The CS5535 is pretty clean about all this
 */

अटल व्योम cs5535_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u16 pio_timings[5] = अणु
		0xF7F4, 0xF173, 0x8141, 0x5131, 0x1131
	पूर्ण;
	अटल स्थिर u16 pio_cmd_timings[5] = अणु
		0xF7F4, 0x53F3, 0x13F1, 0x5131, 0x1131
	पूर्ण;
	u32 reg, dummy;
	काष्ठा ata_device *pair = ata_dev_pair(adev);

	पूर्णांक mode = adev->pio_mode - XFER_PIO_0;
	पूर्णांक cmdmode = mode;

	/* Command timing has to be क्रम the lowest of the pair of devices */
	अगर (pair) अणु
		पूर्णांक pairmode = pair->pio_mode - XFER_PIO_0;
		cmdmode = min(mode, pairmode);
		/* Write the other drive timing रेजिस्टर अगर it changed */
		अगर (cmdmode < pairmode)
			wrmsr(ATAC_CH0D0_PIO + 2 * pair->devno,
				pio_cmd_timings[cmdmode] << 16 | pio_timings[pairmode], 0);
	पूर्ण
	/* Write the drive timing रेजिस्टर */
	wrmsr(ATAC_CH0D0_PIO + 2 * adev->devno,
		pio_cmd_timings[cmdmode] << 16 | pio_timings[mode], 0);

	/* Set the PIO "format 1" bit in the DMA timing रेजिस्टर */
	rdmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg, dummy);
	wrmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg | 0x80000000UL, 0);
पूर्ण

/**
 *	cs5535_set_dmamode		-	DMA timing setup
 *	@ap: ATA पूर्णांकerface
 *	@adev: Device being configured
 *
 */

अटल व्योम cs5535_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u32 udma_timings[5] = अणु
		0x7F7436A1, 0x7F733481, 0x7F723261, 0x7F713161, 0x7F703061
	पूर्ण;
	अटल स्थिर u32 mwdma_timings[3] = अणु
		0x7F0FFFF3, 0x7F035352, 0x7F024241
	पूर्ण;
	u32 reg, dummy;
	पूर्णांक mode = adev->dma_mode;

	rdmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg, dummy);
	reg &= 0x80000000UL;
	अगर (mode >= XFER_UDMA_0)
		reg |= udma_timings[mode - XFER_UDMA_0];
	अन्यथा
		reg |= mwdma_timings[mode - XFER_MW_DMA_0];
	wrmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg, 0);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cs5535_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations cs5535_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= cs5535_cable_detect,
	.set_piomode	= cs5535_set_piomode,
	.set_dmamode	= cs5535_set_dmamode,
पूर्ण;

/**
 *	cs5535_init_one		-	Initialise a CS5530
 *	@dev: PCI device
 *	@id: Entry in match table
 *
 *	Install a driver क्रम the newly found CS5530 companion chip. Most of
 *	this is just housekeeping. We have to set the chip up correctly and
 *	turn off various bits of emulation magic.
 */

अटल पूर्णांक cs5535_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.port_ops = &cs5535_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, &ata_dummy_port_info पूर्ण;

	वापस ata_pci_bmdma_init_one(dev, ppi, &cs5535_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cs5535[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_CS5535_IDE), पूर्ण,
	अणु PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_CS5535_IDE), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cs5535_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= cs5535,
	.probe 		= cs5535_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cs5535_pci_driver);

MODULE_AUTHOR("Alan Cox, Jens Altmann, Wolfgan Zuleger, Alexander Kiausch");
MODULE_DESCRIPTION("low-level driver for the NS/AMD 5535");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cs5535);
MODULE_VERSION(DRV_VERSION);
