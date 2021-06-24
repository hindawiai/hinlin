<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_mpiix.c 	- Intel MPIIX PATA क्रम new ATA layer
 *			  (C) 2005-2006 Red Hat Inc
 *			  Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * The MPIIX is dअगरferent enough to the PIIX4 and मित्रs that we give it
 * a separate driver. The old ide/pci code handles this by just not tuning
 * MPIIX at all.
 *
 * The MPIIX also dअगरfers in another important way from the majority of PIIX
 * devices. The chip is a bridge (parकरोn the pun) between the old world of
 * ISA IDE and PCI IDE. Although the ATA timings are PCI configured the actual
 * IDE controller is not decoded in PCI space and the chip करोes not claim to
 * be IDE class PCI. This requires slightly non-standard probe logic compared
 * with PCI IDE and also that we करो not disable the device when our driver is
 * unloaded (as it has many other functions).
 *
 * The driver consciously keeps this logic पूर्णांकernally to aव्योम pushing quirky
 * PATA history पूर्णांकo the clean libata layer.
 *
 * Thinkpad specअगरic note: If you boot an MPIIX using a thinkpad with a PCMCIA
 * hard disk present this driver will not detect it. This is not a bug. In this
 * configuration the secondary port of the MPIIX is disabled and the addresses
 * are decoded by the PCMCIA bridge and thereक्रमe are क्रम a generic IDE driver
 * to operate.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_mpiix"
#घोषणा DRV_VERSION "0.7.7"

क्रमागत अणु
	IDETIM = 0x6C,		/* IDE control रेजिस्टर */
	IORDY = (1 << 1),
	PPE = (1 << 2),
	FTIM = (1 << 0),
	ENABLED = (1 << 15),
	SECONDARY = (1 << 14)
पूर्ण;

अटल पूर्णांक mpiix_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर काष्ठा pci_bits mpiix_enable_bits = अणु 0x6D, 1, 0x80, 0x80 पूर्ण;

	अगर (!pci_test_config_bits(pdev, &mpiix_enable_bits))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	mpiix_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup. The MPIIX allows us to program the
 *	IORDY sample poपूर्णांक (2-5 घड़ीs), recovery (1-4 घड़ीs) and whether
 *	prefetching or IORDY are used.
 *
 *	This would get very ugly because we can only program timing क्रम one
 *	device at a समय, the other माला_लो PIO0. Fortunately libata calls
 *	our qc_issue command beक्रमe a command is issued so we can flip the
 *	timings back and क्रमth to reduce the pain.
 */

अटल व्योम mpiix_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	पूर्णांक control = 0;
	पूर्णांक pio = adev->pio_mode - XFER_PIO_0;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 idetim;
	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	pci_पढ़ो_config_word(pdev, IDETIM, &idetim);

	/* Mask the IORDY/TIME/PPE क्रम this device */
	अगर (adev->class == ATA_DEV_ATA)
		control |= PPE;		/* Enable prefetch/posting क्रम disk */
	अगर (ata_pio_need_iordy(adev))
		control |= IORDY;
	अगर (pio > 1)
		control |= FTIM;	/* This drive is on the fast timing bank */

	/* Mask out timing and clear both TIME bank selects */
	idetim &= 0xCCEE;
	idetim &= ~(0x07  << (4 * adev->devno));
	idetim |= control << (4 * adev->devno);

	idetim |= (timings[pio][0] << 12) | (timings[pio][1] << 8);
	pci_ग_लिखो_config_word(pdev, IDETIM, idetim);

	/* We use ap->निजी_data as a poपूर्णांकer to the device currently
	   loaded क्रम timing */
	ap->निजी_data = adev;
पूर्ण

/**
 *	mpiix_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Called when the libata layer is about to issue a command. We wrap
 *	this पूर्णांकerface so that we can load the correct ATA timings अगर
 *	necessary. Our logic also clears TIME0/TIME1 क्रम the other device so
 *	that, even अगर we get this wrong, cycles to the other device will
 *	be made PIO0.
 */

अटल अचिन्हित पूर्णांक mpiix_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;

	/* If modes have been configured and the channel data is not loaded
	   then load it. We have to check अगर pio_mode is set as the core code
	   करोes not set adev->pio_mode to XFER_PIO_0 जबतक probing as would be
	   logical */

	अगर (adev->pio_mode && adev != ap->निजी_data)
		mpiix_set_piomode(ap, adev);

	वापस ata_sff_qc_issue(qc);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा mpiix_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations mpiix_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	.qc_issue	= mpiix_qc_issue,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= mpiix_set_piomode,
	.prereset	= mpiix_pre_reset,
	.sff_data_xfer	= ata_sff_data_xfer32,
पूर्ण;

अटल पूर्णांक mpiix_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	/* Single thपढ़ोed by the PCI probe logic */
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	व्योम __iomem *cmd_addr, *ctl_addr;
	u16 idetim;
	पूर्णांक cmd, ctl, irq;

	ata_prपूर्णांक_version_once(&dev->dev, DRV_VERSION);

	host = ata_host_alloc(&dev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;
	ap = host->ports[0];

	/* MPIIX has many functions which can be turned on or off according
	   to other devices present. Make sure IDE is enabled beक्रमe we try
	   and use it */

	pci_पढ़ो_config_word(dev, IDETIM, &idetim);
	अगर (!(idetim & ENABLED))
		वापस -ENODEV;

	/* See अगर it's primary or secondary channel... */
	अगर (!(idetim & SECONDARY)) अणु
		cmd = 0x1F0;
		ctl = 0x3F6;
		irq = 14;
	पूर्ण अन्यथा अणु
		cmd = 0x170;
		ctl = 0x376;
		irq = 15;
	पूर्ण

	cmd_addr = devm_ioport_map(&dev->dev, cmd, 8);
	ctl_addr = devm_ioport_map(&dev->dev, ctl, 1);
	अगर (!cmd_addr || !ctl_addr)
		वापस -ENOMEM;

	ata_port_desc(ap, "cmd 0x%x ctl 0x%x", cmd, ctl);

	/* We करो our own plumbing to aव्योम leaking special हालs क्रम whacko
	   ancient hardware पूर्णांकo the core code. There are two issues to
	   worry about.  #1 The chip is a bridge so अगर in legacy mode and
	   without BARs set fools the setup.  #2 If you pci_disable_device
	   the MPIIX your box goes castors up */

	ap->ops = &mpiix_port_ops;
	ap->pio_mask = ATA_PIO4;
	ap->flags |= ATA_FLAG_SLAVE_POSS;

	ap->ioaddr.cmd_addr = cmd_addr;
	ap->ioaddr.ctl_addr = ctl_addr;
	ap->ioaddr.altstatus_addr = ctl_addr;

	/* Let libata fill in the port details */
	ata_sff_std_ports(&ap->ioaddr);

	/* activate host */
	वापस ata_host_activate(host, irq, ata_sff_पूर्णांकerrupt, IRQF_SHARED,
				 &mpiix_sht);
पूर्ण

अटल स्थिर काष्ठा pci_device_id mpiix[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_82371MX), पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver mpiix_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= mpiix,
	.probe 		= mpiix_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(mpiix_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for Intel MPIIX");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, mpiix);
MODULE_VERSION(DRV_VERSION);
