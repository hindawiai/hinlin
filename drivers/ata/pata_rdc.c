<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  pata_rdc		-	Driver क्रम later RDC PATA controllers
 *
 *  This is actually a driver क्रम hardware meeting
 *  INCITS 370-2004 (1510D): ATA Host Adapter Standards
 *
 *  Based on ata_piix.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>
#समावेश <linux/dmi.h>

#घोषणा DRV_NAME	"pata_rdc"
#घोषणा DRV_VERSION	"0.01"

काष्ठा rdc_host_priv अणु
	u32 saved_iocfg;
पूर्ण;

/**
 *	rdc_pata_cable_detect - Probe host controller cable detect info
 *	@ap: Port क्रम which cable detect info is desired
 *
 *	Read 80c cable indicator from ATA PCI device's PCI config
 *	रेजिस्टर.  This रेजिस्टर is normally set by firmware (BIOS).
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल पूर्णांक rdc_pata_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा rdc_host_priv *hpriv = ap->host->निजी_data;
	u8 mask;

	/* check BIOS cable detect results */
	mask = 0x30 << (2 * ap->port_no);
	अगर ((hpriv->saved_iocfg & mask) == 0)
		वापस ATA_CBL_PATA40;
	वापस ATA_CBL_PATA80;
पूर्ण

/**
 *	rdc_pata_prereset - prereset क्रम PATA host controller
 *	@link: Target link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	LOCKING:
 *	None (inherited from caller).
 */
अटल पूर्णांक rdc_pata_prereset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अटल स्थिर काष्ठा pci_bits rdc_enable_bits[] = अणु
		अणु 0x41U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 0 */
		अणु 0x43U, 1U, 0x80UL, 0x80UL पूर्ण,	/* port 1 */
	पूर्ण;

	अगर (!pci_test_config_bits(pdev, &rdc_enable_bits[ap->port_no]))
		वापस -ENOENT;
	वापस ata_sff_prereset(link, deadline);
पूर्ण

अटल DEFINE_SPINLOCK(rdc_lock);

/**
 *	rdc_set_piomode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: um
 *
 *	Set PIO mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम rdc_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अचिन्हित पूर्णांक pio	= adev->pio_mode - XFER_PIO_0;
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक is_slave	= (adev->devno != 0);
	अचिन्हित पूर्णांक master_port= ap->port_no ? 0x42 : 0x40;
	अचिन्हित पूर्णांक slave_port	= 0x44;
	u16 master_data;
	u8 slave_data;
	u8 udma_enable;
	पूर्णांक control = 0;

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	अगर (pio >= 2)
		control |= 1;	/* TIME1 enable */
	अगर (ata_pio_need_iordy(adev))
		control |= 2;	/* IE enable */

	अगर (adev->class == ATA_DEV_ATA)
		control |= 4;	/* PPE enable */

	spin_lock_irqsave(&rdc_lock, flags);

	/* PIO configuration clears DTE unconditionally.  It will be
	 * programmed in set_dmamode which is guaranteed to be called
	 * after set_piomode अगर any DMA mode is available.
	 */
	pci_पढ़ो_config_word(dev, master_port, &master_data);
	अगर (is_slave) अणु
		/* clear TIME1|IE1|PPE1|DTE1 */
		master_data &= 0xff0f;
		/* Enable SITRE (separate slave timing रेजिस्टर) */
		master_data |= 0x4000;
		/* enable PPE1, IE1 and TIME1 as needed */
		master_data |= (control << 4);
		pci_पढ़ो_config_byte(dev, slave_port, &slave_data);
		slave_data &= (ap->port_no ? 0x0f : 0xf0);
		/* Load the timing nibble क्रम this slave */
		slave_data |= ((timings[pio][0] << 2) | timings[pio][1])
						<< (ap->port_no ? 4 : 0);
	पूर्ण अन्यथा अणु
		/* clear ISP|RCT|TIME0|IE0|PPE0|DTE0 */
		master_data &= 0xccf0;
		/* Enable PPE, IE and TIME as appropriate */
		master_data |= control;
		/* load ISP and RCT */
		master_data |=
			(timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	पूर्ण
	pci_ग_लिखो_config_word(dev, master_port, master_data);
	अगर (is_slave)
		pci_ग_लिखो_config_byte(dev, slave_port, slave_data);

	/* Ensure the UDMA bit is off - it will be turned back on अगर
	   UDMA is selected */

	pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);
	udma_enable &= ~(1 << (2 * ap->port_no + adev->devno));
	pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);

	spin_unlock_irqrestore(&rdc_lock, flags);
पूर्ण

/**
 *	rdc_set_dmamode - Initialize host controller PATA PIO timings
 *	@ap: Port whose timings we are configuring
 *	@adev: Drive in question
 *
 *	Set UDMA mode क्रम device, in host controller PCI config space.
 *
 *	LOCKING:
 *	None (inherited from caller).
 */

अटल व्योम rdc_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ flags;
	u8 master_port		= ap->port_no ? 0x42 : 0x40;
	u16 master_data;
	u8 speed		= adev->dma_mode;
	पूर्णांक devid		= adev->devno + 2 * ap->port_no;
	u8 udma_enable		= 0;

	अटल स्थिर	 /* ISP  RTC */
	u8 timings[][2]	= अणु अणु 0, 0 पूर्ण,
			    अणु 0, 0 पूर्ण,
			    अणु 1, 0 पूर्ण,
			    अणु 2, 1 पूर्ण,
			    अणु 2, 3 पूर्ण, पूर्ण;

	spin_lock_irqsave(&rdc_lock, flags);

	pci_पढ़ो_config_word(dev, master_port, &master_data);
	pci_पढ़ो_config_byte(dev, 0x48, &udma_enable);

	अगर (speed >= XFER_UDMA_0) अणु
		अचिन्हित पूर्णांक udma = adev->dma_mode - XFER_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		पूर्णांक u_घड़ी, u_speed;

		/*
		 * UDMA is handled by a combination of घड़ी चयनing and
		 * selection of भागiders
		 *
		 * Handy rule: Odd modes are UDMATIMx 01, even are 02
		 *	       except UDMA0 which is 00
		 */
		u_speed = min(2 - (udma & 1), udma);
		अगर (udma == 5)
			u_घड़ी = 0x1000;	/* 100Mhz */
		अन्यथा अगर (udma > 2)
			u_घड़ी = 1;		/* 66Mhz */
		अन्यथा
			u_घड़ी = 0;		/* 33Mhz */

		udma_enable |= (1 << devid);

		/* Load the CT/RP selection */
		pci_पढ़ो_config_word(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_ग_लिखो_config_word(dev, 0x4A, udma_timing);

		/* Select a 33/66/100Mhz घड़ी */
		pci_पढ़ो_config_word(dev, 0x54, &ideconf);
		ideconf &= ~(0x1001 << devid);
		ideconf |= u_घड़ी << devid;
		pci_ग_लिखो_config_word(dev, 0x54, ideconf);
	पूर्ण अन्यथा अणु
		/*
		 * MWDMA is driven by the PIO timings. We must also enable
		 * IORDY unconditionally aदीर्घ with TIME1. PPE has alपढ़ोy
		 * been set when the PIO timing was set.
		 */
		अचिन्हित पूर्णांक mwdma	= adev->dma_mode - XFER_MW_DMA_0;
		अचिन्हित पूर्णांक control;
		u8 slave_data;
		स्थिर अचिन्हित पूर्णांक needed_pio[3] = अणु
			XFER_PIO_0, XFER_PIO_3, XFER_PIO_4
		पूर्ण;
		पूर्णांक pio = needed_pio[mwdma] - XFER_PIO_0;

		control = 3;	/* IORDY|TIME1 */

		/* If the drive MWDMA is faster than it can करो PIO then
		   we must क्रमce PIO पूर्णांकo PIO0 */

		अगर (adev->pio_mode < needed_pio[mwdma])
			/* Enable DMA timing only */
			control |= 8;	/* PIO cycles in PIO0 */

		अगर (adev->devno) अणु	/* Slave */
			master_data &= 0xFF4F;  /* Mask out IORDY|TIME1|DMAONLY */
			master_data |= control << 4;
			pci_पढ़ो_config_byte(dev, 0x44, &slave_data);
			slave_data &= (ap->port_no ? 0x0f : 0xf0);
			/* Load the matching timing */
			slave_data |= ((timings[pio][0] << 2) | timings[pio][1]) << (ap->port_no ? 4 : 0);
			pci_ग_लिखो_config_byte(dev, 0x44, slave_data);
		पूर्ण अन्यथा अणु 	/* Master */
			master_data &= 0xCCF4;	/* Mask out IORDY|TIME1|DMAONLY
						   and master timing bits */
			master_data |= control;
			master_data |=
				(timings[pio][0] << 12) |
				(timings[pio][1] << 8);
		पूर्ण

		udma_enable &= ~(1 << devid);
		pci_ग_लिखो_config_word(dev, master_port, master_data);
	पूर्ण
	pci_ग_लिखो_config_byte(dev, 0x48, udma_enable);

	spin_unlock_irqrestore(&rdc_lock, flags);
पूर्ण

अटल काष्ठा ata_port_operations rdc_pata_ops = अणु
	.inherits		= &ata_bmdma32_port_ops,
	.cable_detect		= rdc_pata_cable_detect,
	.set_piomode		= rdc_set_piomode,
	.set_dmamode		= rdc_set_dmamode,
	.prereset		= rdc_pata_prereset,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info rdc_port_info = अणु

	.flags		= ATA_FLAG_SLAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA12_ONLY,
	.udma_mask	= ATA_UDMA5,
	.port_ops	= &rdc_pata_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा rdc_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

/**
 *	rdc_init_one - Register PIIX ATA PCI device with kernel services
 *	@pdev: PCI device to रेजिस्टर
 *	@ent: Entry in rdc_pci_tbl matching with @pdev
 *
 *	Called from kernel PCI layer.  We probe क्रम combined mode (sigh),
 *	and then hand over control to libata, क्रम it to करो the rest.
 *
 *	LOCKING:
 *	Inherited from PCI layer (may sleep).
 *
 *	RETURNS:
 *	Zero on success, or -ERRNO value.
 */

अटल पूर्णांक rdc_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ata_port_info port_info[2];
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &port_info[0], &port_info[1] पूर्ण;
	काष्ठा ata_host *host;
	काष्ठा rdc_host_priv *hpriv;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	port_info[0] = rdc_port_info;
	port_info[1] = rdc_port_info;

	/* enable device and prepare host */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	hpriv = devm_kzalloc(dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv)
		वापस -ENOMEM;

	/* Save IOCFG, this will be used क्रम cable detection, quirk
	 * detection and restoration on detach.
	 */
	pci_पढ़ो_config_dword(pdev, 0x54, &hpriv->saved_iocfg);

	rc = ata_pci_bmdma_prepare_host(pdev, ppi, &host);
	अगर (rc)
		वापस rc;
	host->निजी_data = hpriv;

	pci_पूर्णांकx(pdev, 1);

	host->flags |= ATA_HOST_PARALLEL_SCAN;

	pci_set_master(pdev);
	वापस ata_pci_sff_activate_host(host, ata_bmdma_पूर्णांकerrupt, &rdc_sht);
पूर्ण

अटल व्योम rdc_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	काष्ठा rdc_host_priv *hpriv = host->निजी_data;

	pci_ग_लिखो_config_dword(pdev, 0x54, hpriv->saved_iocfg);

	ata_pci_हटाओ_one(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id rdc_pci_tbl[] = अणु
	अणु PCI_DEVICE(0x17F3, 0x1011), पूर्ण,
	अणु PCI_DEVICE(0x17F3, 0x1012), पूर्ण,
	अणु पूर्ण	/* terminate list */
पूर्ण;

अटल काष्ठा pci_driver rdc_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= rdc_pci_tbl,
	.probe			= rdc_init_one,
	.हटाओ			= rdc_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= ata_pci_device_resume,
#पूर्ण_अगर
पूर्ण;


module_pci_driver(rdc_pci_driver);

MODULE_AUTHOR("Alan Cox (based on ata_piix)");
MODULE_DESCRIPTION("SCSI low-level driver for RDC PATA controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, rdc_pci_tbl);
MODULE_VERSION(DRV_VERSION);
