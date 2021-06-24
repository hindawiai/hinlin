<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	ACPI PATA driver
 *
 *	(c) 2007 Red Hat
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/acpi.h>
#समावेश <linux/libata.h>
#समावेश <linux/ata.h>
#समावेश <scsi/scsi_host.h>

#घोषणा DRV_NAME	"pata_acpi"
#घोषणा DRV_VERSION	"0.2.3"

काष्ठा pata_acpi अणु
	काष्ठा ata_acpi_gपंचांग gपंचांग;
	व्योम *last;
	अचिन्हित दीर्घ mask[2];
पूर्ण;

/**
 *	pacpi_pre_reset	-	check क्रम 40/80 pin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Perक्रमm the PATA port setup we need.
 */

अटल पूर्णांक pacpi_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pata_acpi *acpi = ap->निजी_data;
	अगर (ACPI_HANDLE(&ap->tdev) == शून्य || ata_acpi_gपंचांग(ap, &acpi->gपंचांग) < 0)
		वापस -ENODEV;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	pacpi_cable_detect	-	cable type detection
 *	@ap: port to detect
 *
 *	Perक्रमm device specअगरic cable detection
 */

अटल पूर्णांक pacpi_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pata_acpi *acpi = ap->निजी_data;

	अगर ((acpi->mask[0] | acpi->mask[1]) & (0xF8 << ATA_SHIFT_UDMA))
		वापस ATA_CBL_PATA80;
	अन्यथा
		वापस ATA_CBL_PATA40;
पूर्ण

/**
 *	pacpi_discover_modes	-	filter non ACPI modes
 *	@ap: ATA port
 *	@adev: ATA device
 *
 *	Try the modes available and see which ones the ACPI method will
 *	set up sensibly. From this we get a mask of ACPI modes we can use
 */

अटल अचिन्हित दीर्घ pacpi_discover_modes(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pata_acpi *acpi = ap->निजी_data;
	काष्ठा ata_acpi_gपंचांग probe;
	अचिन्हित पूर्णांक xfer_mask;

	probe = acpi->gपंचांग;

	ata_acpi_gपंचांग(ap, &probe);

	xfer_mask = ata_acpi_gपंचांग_xfermask(adev, &probe);

	अगर (xfer_mask & (0xF8 << ATA_SHIFT_UDMA))
		ap->cbl = ATA_CBL_PATA80;

	वापस xfer_mask;
पूर्ण

/**
 *	pacpi_mode_filter	-	mode filter क्रम ACPI
 *	@adev: device
 *	@mask: mask of valid modes
 *
 *	Filter the valid mode list according to our own specअगरic rules, in
 *	this हाल the list of discovered valid modes obtained by ACPI probing
 */

अटल अचिन्हित दीर्घ pacpi_mode_filter(काष्ठा ata_device *adev, अचिन्हित दीर्घ mask)
अणु
	काष्ठा pata_acpi *acpi = adev->link->ap->निजी_data;
	वापस mask & acpi->mask[adev->devno];
पूर्ण

/**
 *	pacpi_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 */

अटल व्योम pacpi_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	पूर्णांक unit = adev->devno;
	काष्ठा pata_acpi *acpi = ap->निजी_data;
	स्थिर काष्ठा ata_timing *t;

	अगर (!(acpi->gपंचांग.flags & 0x10))
		unit = 0;

	/* Now stuff the nS values पूर्णांकo the काष्ठाure */
	t = ata_timing_find_mode(adev->pio_mode);
	acpi->gपंचांग.drive[unit].pio = t->cycle;
	ata_acpi_sपंचांग(ap, &acpi->gपंचांग);
	/* See what mode we actually got */
	ata_acpi_gपंचांग(ap, &acpi->gपंचांग);
पूर्ण

/**
 *	pacpi_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 */

अटल व्योम pacpi_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	पूर्णांक unit = adev->devno;
	काष्ठा pata_acpi *acpi = ap->निजी_data;
	स्थिर काष्ठा ata_timing *t;

	अगर (!(acpi->gपंचांग.flags & 0x10))
		unit = 0;

	/* Now stuff the nS values पूर्णांकo the काष्ठाure */
	t = ata_timing_find_mode(adev->dma_mode);
	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		acpi->gपंचांग.drive[unit].dma = t->udma;
		acpi->gपंचांग.flags |= (1 << (2 * unit));
	पूर्ण अन्यथा अणु
		acpi->gपंचांग.drive[unit].dma = t->cycle;
		acpi->gपंचांग.flags &= ~(1 << (2 * unit));
	पूर्ण
	ata_acpi_sपंचांग(ap, &acpi->gपंचांग);
	/* See what mode we actually got */
	ata_acpi_gपंचांग(ap, &acpi->gपंचांग);
पूर्ण

/**
 *	pacpi_qc_issue	-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings अगर
 *	necessary.
 */

अटल अचिन्हित पूर्णांक pacpi_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा pata_acpi *acpi = ap->निजी_data;

	अगर (acpi->gपंचांग.flags & 0x10)
		वापस ata_bmdma_qc_issue(qc);

	अगर (adev != acpi->last) अणु
		pacpi_set_piomode(ap, adev);
		अगर (ata_dma_enabled(adev))
			pacpi_set_dmamode(ap, adev);
		acpi->last = adev;
	पूर्ण
	वापस ata_bmdma_qc_issue(qc);
पूर्ण

/**
 *	pacpi_port_start	-	port setup
 *	@ap: ATA port being set up
 *
 *	Use the port_start hook to मुख्यtain निजी control काष्ठाures
 */

अटल पूर्णांक pacpi_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा pata_acpi *acpi;

	अगर (ACPI_HANDLE(&ap->tdev) == शून्य)
		वापस -ENODEV;

	acpi = ap->निजी_data = devm_kzalloc(&pdev->dev, माप(काष्ठा pata_acpi), GFP_KERNEL);
	अगर (ap->निजी_data == शून्य)
		वापस -ENOMEM;
	acpi->mask[0] = pacpi_discover_modes(ap, &ap->link.device[0]);
	acpi->mask[1] = pacpi_discover_modes(ap, &ap->link.device[1]);
	वापस ata_bmdma_port_start(ap);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा pacpi_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations pacpi_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.qc_issue		= pacpi_qc_issue,
	.cable_detect		= pacpi_cable_detect,
	.mode_filter		= pacpi_mode_filter,
	.set_piomode		= pacpi_set_piomode,
	.set_dmamode		= pacpi_set_dmamode,
	.prereset		= pacpi_pre_reset,
	.port_start		= pacpi_port_start,
पूर्ण;


/**
 *	pacpi_init_one - Register ACPI ATA PCI device with kernel services
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

अटल पूर्णांक pacpi_init_one (काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,

		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA6,

		.port_ops	= &pacpi_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;
	अगर (pdev->venकरोr == PCI_VENDOR_ID_ATI) अणु
		पूर्णांक rc = pcim_enable_device(pdev);
		अगर (rc < 0)
			वापस rc;
		pcim_pin_device(pdev);
	पूर्ण
	वापस ata_pci_bmdma_init_one(pdev, ppi, &pacpi_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pacpi_pci_tbl[] = अणु
	अणु PCI_ANY_ID,		PCI_ANY_ID,			   PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_STORAGE_IDE << 8, 0xFFFFFF00UL, 1पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver pacpi_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= pacpi_pci_tbl,
	.probe			= pacpi_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(pacpi_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("SCSI low-level driver for ATA in ACPI mode");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pacpi_pci_tbl);
MODULE_VERSION(DRV_VERSION);
