<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pata_ns87410.c 	- National Semiconductor 87410 PATA क्रम new ATA layer
 *			  (C) 2006 Red Hat Inc
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_ns87410"
#घोषणा DRV_VERSION "0.4.6"

/**
 *	ns87410_pre_reset		-	probe begin
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Check enabled ports
 */

अटल पूर्णांक ns87410_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर काष्ठा pci_bits ns87410_enable_bits[] = अणु
		अणु 0x43, 1, 0x08, 0x08 पूर्ण,
		अणु 0x47, 1, 0x08, 0x08 पूर्ण
	पूर्ण;

	अगर (!pci_test_config_bits(pdev, &ns87410_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	ns87410_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program timing data. This is kept per channel not per device,
 *	and only affects the data port.
 */

अटल व्योम ns87410_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक port = 0x40 + 4 * ap->port_no;
	u8 idetcr, idefr;
	काष्ठा ata_timing at;

	अटल स्थिर u8 activebits[15] = अणु
		0, 1, 2, 3, 4,
		5, 5, 6, 6, 6,
		6, 7, 7, 7, 7
	पूर्ण;

	अटल स्थिर u8 recoverbits[12] = अणु
		0, 1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 7
	पूर्ण;

	pci_पढ़ो_config_byte(pdev, port + 3, &idefr);

	अगर (ata_pio_need_iordy(adev))
		idefr |= 0x04;	/* IORDY enable */
	अन्यथा
		idefr &= ~0x04;

	अगर (ata_timing_compute(adev, adev->pio_mode, &at, 30303, 1) < 0) अणु
		dev_err(&pdev->dev, "unknown mode %d\n", adev->pio_mode);
		वापस;
	पूर्ण

	at.active = clamp_val(at.active, 2, 16) - 2;
	at.setup = clamp_val(at.setup, 1, 4) - 1;
	at.recover = clamp_val(at.recover, 1, 12) - 1;

	idetcr = (at.setup << 6) | (recoverbits[at.recover] << 3) | activebits[at.active];

	pci_ग_लिखो_config_byte(pdev, port, idetcr);
	pci_ग_लिखो_config_byte(pdev, port + 3, idefr);
	/* We use ap->निजी_data as a poपूर्णांकer to the device currently
	   loaded क्रम timing */
	ap->निजी_data = adev;
पूर्ण

/**
 *	ns87410_qc_issue	-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings अगर
 *	necessary.
 */

अटल अचिन्हित पूर्णांक ns87410_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;

	/* If modes have been configured and the channel data is not loaded
	   then load it. We have to check अगर pio_mode is set as the core code
	   करोes not set adev->pio_mode to XFER_PIO_0 जबतक probing as would be
	   logical */

	अगर (adev->pio_mode && adev != ap->निजी_data)
		ns87410_set_piomode(ap, adev);

	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ns87410_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations ns87410_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.qc_issue	= ns87410_qc_issue,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= ns87410_set_piomode,
	.prereset	= ns87410_pre_reset,
पूर्ण;

अटल पूर्णांक ns87410_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO3,
		.port_ops = &ns87410_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;
	वापस ata_pci_sff_init_one(dev, ppi, &ns87410_sht, शून्य, 0);
पूर्ण

अटल स्थिर काष्ठा pci_device_id ns87410[] = अणु
	अणु PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_87410), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ns87410_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= ns87410,
	.probe 		= ns87410_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(ns87410_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Nat Semi 87410");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, ns87410);
MODULE_VERSION(DRV_VERSION);
