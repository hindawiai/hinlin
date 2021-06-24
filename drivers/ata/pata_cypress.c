<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_cypress.c 	- Cypress PATA क्रम new ATA layer
 *			  (C) 2006 Red Hat Inc
 *			  Alan Cox
 *
 * Based heavily on
 * linux/drivers/ide/pci/cy82c693.c		Version 0.40	Sep. 10, 2002
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_cypress"
#घोषणा DRV_VERSION "0.1.5"

/* here are the offset definitions क्रम the रेजिस्टरs */

क्रमागत अणु
	CY82_IDE_CMDREG		= 0x04,
	CY82_IDE_ADDRSETUP	= 0x48,
	CY82_IDE_MASTER_IOR	= 0x4C,
	CY82_IDE_MASTER_IOW	= 0x4D,
	CY82_IDE_SLAVE_IOR	= 0x4E,
	CY82_IDE_SLAVE_IOW	= 0x4F,
	CY82_IDE_MASTER_8BIT	= 0x50,
	CY82_IDE_SLAVE_8BIT	= 0x51,

	CY82_INDEX_PORT		= 0x22,
	CY82_DATA_PORT		= 0x23,

	CY82_INDEX_CTRLREG1	= 0x01,
	CY82_INDEX_CHANNEL0	= 0x30,
	CY82_INDEX_CHANNEL1	= 0x31,
	CY82_INDEX_TIMEOUT	= 0x32
पूर्ण;

/**
 *	cy82c693_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup.
 */

अटल व्योम cy82c693_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा ata_timing t;
	स्थिर अचिन्हित दीर्घ T = 1000000 / 33;
	लघु समय_16, समय_8;
	u32 addr;

	अगर (ata_timing_compute(adev, adev->pio_mode, &t, T, 1) < 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": mome computation failed.\n");
		वापस;
	पूर्ण

	समय_16 = clamp_val(t.recover - 1, 0, 15) |
		  (clamp_val(t.active - 1, 0, 15) << 4);
	समय_8 = clamp_val(t.act8b - 1, 0, 15) |
		 (clamp_val(t.rec8b - 1, 0, 15) << 4);

	अगर (adev->devno == 0) अणु
		pci_पढ़ो_config_dword(pdev, CY82_IDE_ADDRSETUP, &addr);

		addr &= ~0x0F;	/* Mask bits */
		addr |= clamp_val(t.setup - 1, 0, 15);

		pci_ग_लिखो_config_dword(pdev, CY82_IDE_ADDRSETUP, addr);
		pci_ग_लिखो_config_byte(pdev, CY82_IDE_MASTER_IOR, समय_16);
		pci_ग_लिखो_config_byte(pdev, CY82_IDE_MASTER_IOW, समय_16);
		pci_ग_लिखो_config_byte(pdev, CY82_IDE_MASTER_8BIT, समय_8);
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_dword(pdev, CY82_IDE_ADDRSETUP, &addr);

		addr &= ~0xF0;	/* Mask bits */
		addr |= (clamp_val(t.setup - 1, 0, 15) << 4);

		pci_ग_लिखो_config_dword(pdev, CY82_IDE_ADDRSETUP, addr);
		pci_ग_लिखो_config_byte(pdev, CY82_IDE_SLAVE_IOR, समय_16);
		pci_ग_लिखो_config_byte(pdev, CY82_IDE_SLAVE_IOW, समय_16);
		pci_ग_लिखो_config_byte(pdev, CY82_IDE_SLAVE_8BIT, समय_8);
	पूर्ण
पूर्ण

/**
 *	cy82c693_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the DMA mode setup.
 */

अटल व्योम cy82c693_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	पूर्णांक reg = CY82_INDEX_CHANNEL0 + ap->port_no;

	/* Be afraid, be very afraid. Magic रेजिस्टरs  in low I/O space */
	outb(reg, 0x22);
	outb(adev->dma_mode - XFER_MW_DMA_0, 0x23);

	/* 0x50 gives the best behaviour on the Alpha's using this chip */
	outb(CY82_INDEX_TIMEOUT, 0x22);
	outb(0x50, 0x23);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cy82c693_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations cy82c693_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= cy82c693_set_piomode,
	.set_dmamode	= cy82c693_set_dmamode,
पूर्ण;

अटल पूर्णांक cy82c693_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.port_ops = &cy82c693_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, &ata_dummy_port_info पूर्ण;

	/* Devfn 1 is the ATA primary. The secondary is magic and on devfn2.
	   For the moment we करोn't handle the secondary. FIXME */

	अगर (PCI_FUNC(pdev->devfn) != 1)
		वापस -ENODEV;

	वापस ata_pci_bmdma_init_one(pdev, ppi, &cy82c693_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id cy82c693[] = अणु
	अणु PCI_VDEVICE(CONTAQ, PCI_DEVICE_ID_CONTAQ_82C693), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cy82c693_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= cy82c693,
	.probe 		= cy82c693_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cy82c693_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for the CY82C693 PATA controller");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cy82c693);
MODULE_VERSION(DRV_VERSION);
