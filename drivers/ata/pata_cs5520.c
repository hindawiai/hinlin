<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IDE tuning and bus mastering support क्रम the CS5510/CS5520
 *	chipsets
 *
 *	The CS5510/CS5520 are slightly unusual devices. Unlike the
 *	typical IDE controllers they करो bus mastering with the drive in
 *	PIO mode and smarter silicon.
 *
 *	The practical upshot of this is that we must always tune the
 *	drive क्रम the right PIO mode. We must also ignore all the blacklists
 *	and the drive bus mastering DMA inक्रमmation. Also to confuse matters
 *	further we can करो DMA on PIO only drives.
 *
 *	DMA on the 5510 also requires we disable_hlt() during DMA on early
 *	revisions.
 *
 *	*** This driver is strictly experimental ***
 *
 *	(c) Copyright Red Hat Inc 2002
 *
 * Documentation:
 *	Not खुलाly available.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"pata_cs5520"
#घोषणा DRV_VERSION	"0.6.6"

काष्ठा pio_घड़ीs
अणु
	पूर्णांक address;
	पूर्णांक निश्चित;
	पूर्णांक recovery;
पूर्ण;

अटल स्थिर काष्ठा pio_घड़ीs cs5520_pio_घड़ीs[]=अणु
	अणु3, 6, 11पूर्ण,
	अणु2, 5, 6पूर्ण,
	अणु1, 4, 3पूर्ण,
	अणु1, 3, 2पूर्ण,
	अणु1, 2, 1पूर्ण
पूर्ण;

/**
 *	cs5520_set_timings	-	program PIO timings
 *	@ap: ATA port
 *	@adev: ATA device
 *	@pio: PIO ID
 *
 *	Program the PIO mode timings क्रम the controller according to the pio
 *	घड़ीing table.
 */

अटल व्योम cs5520_set_timings(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक pio)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक slave = adev->devno;

	pio -= XFER_PIO_0;

	/* Channel command timing */
	pci_ग_लिखो_config_byte(pdev, 0x62 + ap->port_no,
				(cs5520_pio_घड़ीs[pio].recovery << 4) |
				(cs5520_pio_घड़ीs[pio].निश्चित));
	/* FIXME: should these use address ? */
	/* Read command timing */
	pci_ग_लिखो_config_byte(pdev, 0x64 +  4*ap->port_no + slave,
				(cs5520_pio_घड़ीs[pio].recovery << 4) |
				(cs5520_pio_घड़ीs[pio].निश्चित));
	/* Write command timing */
	pci_ग_लिखो_config_byte(pdev, 0x66 +  4*ap->port_no + slave,
				(cs5520_pio_घड़ीs[pio].recovery << 4) |
				(cs5520_pio_घड़ीs[pio].निश्चित));
पूर्ण

/**
 *	cs5520_set_piomode	-	program PIO timings
 *	@ap: ATA port
 *	@adev: ATA device
 *
 *	Program the PIO mode timings क्रम the controller according to the pio
 *	घड़ीing table.
 */

अटल व्योम cs5520_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	cs5520_set_timings(ap, adev, adev->pio_mode);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cs5520_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
	.sg_tablesize		= LIBATA_DUMB_MAX_PRD,
पूर्ण;

अटल काष्ठा ata_port_operations cs5520_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.qc_prep		= ata_bmdma_dumb_qc_prep,
	.cable_detect		= ata_cable_40wire,
	.set_piomode		= cs5520_set_piomode,
पूर्ण;

अटल पूर्णांक cs5520_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर अचिन्हित पूर्णांक cmd_port[] = अणु 0x1F0, 0x170 पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक ctl_port[] = अणु 0x3F6, 0x376 पूर्ण;
	काष्ठा ata_port_info pi = अणु
		.flags		= ATA_FLAG_SLAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.port_ops	= &cs5520_port_ops,
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[2];
	u8 pcicfg;
	व्योम __iomem *iomap[5];
	काष्ठा ata_host *host;
	काष्ठा ata_ioports *ioaddr;
	पूर्णांक i, rc;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	/* IDE port enable bits */
	pci_पढ़ो_config_byte(pdev, 0x60, &pcicfg);

	/* Check अगर the ATA ports are enabled */
	अगर ((pcicfg & 3) == 0)
		वापस -ENODEV;

	ppi[0] = ppi[1] = &ata_dummy_port_info;
	अगर (pcicfg & 1)
		ppi[0] = &pi;
	अगर (pcicfg & 2)
		ppi[1] = &pi;

	अगर ((pcicfg & 0x40) == 0) अणु
		dev_warn(&pdev->dev, "DMA mode disabled. Enabling.\n");
		pci_ग_लिखो_config_byte(pdev, 0x60, pcicfg | 0x40);
	पूर्ण

	pi.mwdma_mask = id->driver_data;

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, 2);
	अगर (!host)
		वापस -ENOMEM;

	/* Perक्रमm set up क्रम DMA */
	अगर (pci_enable_device_io(pdev)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": unable to configure BAR2.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": unable to configure DMA mask.\n");
		वापस -ENODEV;
	पूर्ण

	/* Map IO ports and initialize host accordingly */
	iomap[0] = devm_ioport_map(&pdev->dev, cmd_port[0], 8);
	iomap[1] = devm_ioport_map(&pdev->dev, ctl_port[0], 1);
	iomap[2] = devm_ioport_map(&pdev->dev, cmd_port[1], 8);
	iomap[3] = devm_ioport_map(&pdev->dev, ctl_port[1], 1);
	iomap[4] = pcim_iomap(pdev, 2, 0);

	अगर (!iomap[0] || !iomap[1] || !iomap[2] || !iomap[3] || !iomap[4])
		वापस -ENOMEM;

	ioaddr = &host->ports[0]->ioaddr;
	ioaddr->cmd_addr = iomap[0];
	ioaddr->ctl_addr = iomap[1];
	ioaddr->altstatus_addr = iomap[1];
	ioaddr->bmdma_addr = iomap[4];
	ata_sff_std_ports(ioaddr);

	ata_port_desc(host->ports[0],
		      "cmd 0x%x ctl 0x%x", cmd_port[0], ctl_port[0]);
	ata_port_pbar_desc(host->ports[0], 4, 0, "bmdma");

	ioaddr = &host->ports[1]->ioaddr;
	ioaddr->cmd_addr = iomap[2];
	ioaddr->ctl_addr = iomap[3];
	ioaddr->altstatus_addr = iomap[3];
	ioaddr->bmdma_addr = iomap[4] + 8;
	ata_sff_std_ports(ioaddr);

	ata_port_desc(host->ports[1],
		      "cmd 0x%x ctl 0x%x", cmd_port[1], ctl_port[1]);
	ata_port_pbar_desc(host->ports[1], 4, 8, "bmdma");

	/* activate the host */
	pci_set_master(pdev);
	rc = ata_host_start(host);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < 2; i++) अणु
		अटल स्थिर पूर्णांक irq[] = अणु 14, 15 पूर्ण;
		काष्ठा ata_port *ap = host->ports[i];

		अगर (ata_port_is_dummy(ap))
			जारी;

		rc = devm_request_irq(&pdev->dev, irq[ap->port_no],
				      ata_bmdma_पूर्णांकerrupt, 0, DRV_NAME, host);
		अगर (rc)
			वापस rc;

		ata_port_desc(ap, "irq %d", irq[i]);
	पूर्ण

	वापस ata_host_रेजिस्टर(host, &cs5520_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
/**
 *	cs5520_reinit_one	-	device resume
 *	@pdev: PCI device
 *
 *	Do any reconfiguration work needed by a resume from RAM. We need
 *	to restore DMA mode support on BIOSen which disabled it
 */

अटल पूर्णांक cs5520_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	u8 pcicfg;
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	pci_पढ़ो_config_byte(pdev, 0x60, &pcicfg);
	अगर ((pcicfg & 0x40) == 0)
		pci_ग_लिखो_config_byte(pdev, 0x60, pcicfg | 0x40);

	ata_host_resume(host);
	वापस 0;
पूर्ण

/**
 *	cs5520_pci_device_suspend	-	device suspend
 *	@pdev: PCI device
 *	@mesg: PM event message
 *
 *	We have to cut and waste bits from the standard method because
 *	the 5520 is a bit odd and not just a pure ATA device. As a result
 *	we must not disable it. The needed code is लघु and this aव्योमs
 *	chip specअगरic mess in the core code.
 */

अटल पूर्णांक cs5520_pci_device_suspend(काष्ठा pci_dev *pdev, pm_message_t mesg)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc = 0;

	rc = ata_host_suspend(host, mesg);
	अगर (rc)
		वापस rc;

	pci_save_state(pdev);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/* For now keep DMA off. We can set it क्रम all but A rev CS5510 once the
   core ATA code can handle it */

अटल स्थिर काष्ठा pci_device_id pata_cs5520[] = अणु
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5510), पूर्ण,
	अणु PCI_VDEVICE(CYRIX, PCI_DEVICE_ID_CYRIX_5520), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cs5520_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= pata_cs5520,
	.probe 		= cs5520_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= cs5520_pci_device_suspend,
	.resume		= cs5520_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cs5520_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Cyrix CS5510/5520");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, pata_cs5520);
MODULE_VERSION(DRV_VERSION);
