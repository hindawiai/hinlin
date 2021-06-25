<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *    pata_jmicron.c - JMicron ATA driver क्रम non AHCI mode. This drives the
 *			PATA port of the controller. The SATA ports are
 *			driven by AHCI in the usual configuration although
 *			this driver can handle other setups अगर we need it.
 *
 *	(c) 2006 Red Hat
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/ata.h>

#घोषणा DRV_NAME	"pata_jmicron"
#घोषणा DRV_VERSION	"0.1.5"

प्रकार क्रमागत अणु
	PORT_PATA0 = 0,
	PORT_PATA1 = 1,
	PORT_SATA = 2,
पूर्ण port_type;

/**
 *	jmicron_pre_reset	-	check क्रम 40/80 pin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Perक्रमm the PATA port setup we need.
 *
 *	On the Jmicron 361/363 there is a single PATA port that can be mapped
 *	either as primary or secondary (or neither). We करोn't करो any policy
 *	and setup here. We assume that has been करोne by init_one and the
 *	BIOS.
 */
अटल पूर्णांक jmicron_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 control;
	u32 control5;
	पूर्णांक port_mask = 1<< (4 * ap->port_no);
	पूर्णांक port = ap->port_no;
	port_type port_map[2];

	/* Check अगर our port is enabled */
	pci_पढ़ो_config_dword(pdev, 0x40, &control);
	अगर ((control & port_mask) == 0)
		वापस -ENOENT;

	/* There are two basic mappings. One has the two SATA ports merged
	   as master/slave and the secondary as PATA, the other has only the
	   SATA port mapped */
	अगर (control & (1 << 23)) अणु
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_PATA0;
	पूर्ण अन्यथा अणु
		port_map[0] = PORT_SATA;
		port_map[1] = PORT_SATA;
	पूर्ण

	/* The 365/366 may have this bit set to map the second PATA port
	   as the पूर्णांकernal primary channel */
	pci_पढ़ो_config_dword(pdev, 0x80, &control5);
	अगर (control5 & (1<<24))
		port_map[0] = PORT_PATA1;

	/* The two ports may then be logically swapped by the firmware */
	अगर (control & (1 << 22))
		port = port ^ 1;

	/*
	 *	Now we know which physical port we are talking about we can
	 *	actually करो our cable checking etc. Thankfully we करोn't need
	 *	to करो the plumbing क्रम other हालs.
	 */
	चयन (port_map[port]) अणु
	हाल PORT_PATA0:
		अगर ((control & (1 << 5)) == 0)
			वापस -ENOENT;
		अगर (control & (1 << 3))	/* 40/80 pin primary */
			ap->cbl = ATA_CBL_PATA40;
		अन्यथा
			ap->cbl = ATA_CBL_PATA80;
		अवरोध;
	हाल PORT_PATA1:
		/* Bit 21 is set अगर the port is enabled */
		अगर ((control5 & (1 << 21)) == 0)
			वापस -ENOENT;
		अगर (control5 & (1 << 19))	/* 40/80 pin secondary */
			ap->cbl = ATA_CBL_PATA40;
		अन्यथा
			ap->cbl = ATA_CBL_PATA80;
		अवरोध;
	हाल PORT_SATA:
		ap->cbl = ATA_CBL_SATA;
		अवरोध;
	पूर्ण
	वापस ata_sff_prereset(link, deadline);
पूर्ण

/* No PIO or DMA methods needed क्रम this device */

अटल काष्ठा scsi_host_ढाँचा jmicron_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations jmicron_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.prereset		= jmicron_pre_reset,
पूर्ण;


/**
 *	jmicron_init_one - Register Jmicron ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@id: PCI device ID
 *
 *	Called from kernel PCI layer.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक jmicron_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags	= ATA_FLAG_SLAVE_POSS,

		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5,

		.port_ops	= &jmicron_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;

	वापस ata_pci_bmdma_init_one(pdev, ppi, &jmicron_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id jmicron_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_JMICRON, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CLASS_STORAGE_IDE << 8, 0xffff00, 0 पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver jmicron_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= jmicron_pci_tbl,
	.probe			= jmicron_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(jmicron_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for Jmicron PATA ports");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, jmicron_pci_tbl);
MODULE_VERSION(DRV_VERSION);

