<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_cmd64x.c 	- CMD64x PATA क्रम new ATA layer
 *			  (C) 2005 Red Hat Inc
 *			  Alan Cox <alan@lxorguk.ukuu.org.uk>
 *			  (C) 2009-2010 Bartlomiej Zolnierkiewicz
 *			  (C) 2012 MontaVista Software, LLC <source@mvista.com>
 *
 * Based upon
 * linux/drivers/ide/pci/cmd64x.c		Version 1.30	Sept 10, 2002
 *
 * cmd64x.c: Enable पूर्णांकerrupts at initialization समय on Ultra/PCI machines.
 *           Note, this driver is not used at all on other प्रणालीs because
 *           there the "BIOS" has करोne all of the following alपढ़ोy.
 *           Due to massive hardware bugs, UltraDMA is only supported
 *           on the 646U2 and not on the 646U.
 *
 * Copyright (C) 1998		Eddie C. Dost  (ecd@skynet.be)
 * Copyright (C) 1998		David S. Miller (davem@redhat.com)
 *
 * Copyright (C) 1999-2002	Andre Hedrick <andre@linux-ide.org>
 *
 * TODO
 *	Testing work
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_cmd64x"
#घोषणा DRV_VERSION "0.2.18"

/*
 * CMD64x specअगरic रेजिस्टरs definition.
 */

क्रमागत अणु
	CFR 		= 0x50,
		CFR_INTR_CH0  = 0x04,
	CNTRL		= 0x51,
		CNTRL_CH0     = 0x04,
		CNTRL_CH1     = 0x08,
	CMDTIM 		= 0x52,
	ARTTIM0 	= 0x53,
	DRWTIM0 	= 0x54,
	ARTTIM1 	= 0x55,
	DRWTIM1 	= 0x56,
	ARTTIM23 	= 0x57,
		ARTTIM23_DIS_RA2  = 0x04,
		ARTTIM23_DIS_RA3  = 0x08,
		ARTTIM23_INTR_CH1 = 0x10,
	DRWTIM2 	= 0x58,
	BRST 		= 0x59,
	DRWTIM3 	= 0x5b,
	BMIDECR0	= 0x70,
	MRDMODE		= 0x71,
		MRDMODE_INTR_CH0 = 0x04,
		MRDMODE_INTR_CH1 = 0x08,
	BMIDESR0	= 0x72,
	UDIDETCR0	= 0x73,
	DTPR0		= 0x74,
	BMIDECR1	= 0x78,
	BMIDECSR	= 0x79,
	UDIDETCR1	= 0x7B,
	DTPR1		= 0x7C
पूर्ण;

अटल पूर्णांक cmd648_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 r;

	/* Check cable detect bits */
	pci_पढ़ो_config_byte(pdev, BMIDECSR, &r);
	अगर (r & (1 << ap->port_no))
		वापस ATA_CBL_PATA80;
	वापस ATA_CBL_PATA40;
पूर्ण

/**
 *	cmd64x_set_timing	-	set PIO and MWDMA timing
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *	@mode: mode
 *
 *	Called to करो the PIO and MWDMA mode setup.
 */

अटल व्योम cmd64x_set_timing(काष्ठा ata_port *ap, काष्ठा ata_device *adev, u8 mode)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा ata_timing t;
	स्थिर अचिन्हित दीर्घ T = 1000000 / 33;
	स्थिर u8 setup_data[] = अणु 0x40, 0x40, 0x40, 0x80, 0x00 पूर्ण;

	u8 reg;

	/* Port layout is not logical so use a table */
	स्थिर u8 arttim_port[2][2] = अणु
		अणु ARTTIM0, ARTTIM1 पूर्ण,
		अणु ARTTIM23, ARTTIM23 पूर्ण
	पूर्ण;
	स्थिर u8 drwtim_port[2][2] = अणु
		अणु DRWTIM0, DRWTIM1 पूर्ण,
		अणु DRWTIM2, DRWTIM3 पूर्ण
	पूर्ण;

	पूर्णांक arttim = arttim_port[ap->port_no][adev->devno];
	पूर्णांक drwtim = drwtim_port[ap->port_no][adev->devno];

	/* ata_timing_compute is smart and will produce timings क्रम MWDMA
	   that करोn't violate the drives PIO capabilities. */
	अगर (ata_timing_compute(adev, mode, &t, T, 0) < 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": mode computation failed.\n");
		वापस;
	पूर्ण
	अगर (ap->port_no) अणु
		/* Slave has shared address setup */
		काष्ठा ata_device *pair = ata_dev_pair(adev);

		अगर (pair) अणु
			काष्ठा ata_timing tp;
			ata_timing_compute(pair, pair->pio_mode, &tp, T, 0);
			ata_timing_merge(&t, &tp, &t, ATA_TIMING_SETUP);
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_DEBUG DRV_NAME ": active %d recovery %d setup %d.\n",
		t.active, t.recover, t.setup);
	अगर (t.recover > 16) अणु
		t.active += t.recover - 16;
		t.recover = 16;
	पूर्ण
	अगर (t.active > 16)
		t.active = 16;

	/* Now convert the घड़ीs पूर्णांकo values we can actually stuff पूर्णांकo
	   the chip */

	अगर (t.recover == 16)
		t.recover = 0;
	अन्यथा अगर (t.recover > 1)
		t.recover--;
	अन्यथा
		t.recover = 15;

	अगर (t.setup > 4)
		t.setup = 0xC0;
	अन्यथा
		t.setup = setup_data[t.setup];

	t.active &= 0x0F;	/* 0 = 16 */

	/* Load setup timing */
	pci_पढ़ो_config_byte(pdev, arttim, &reg);
	reg &= 0x3F;
	reg |= t.setup;
	pci_ग_लिखो_config_byte(pdev, arttim, reg);

	/* Load active/recovery */
	pci_ग_लिखो_config_byte(pdev, drwtim, (t.active << 4) | t.recover);
पूर्ण

/**
 *	cmd64x_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Used when configuring the devices ot set the PIO timings. All the
 *	actual work is करोne by the PIO/MWDMA setting helper
 */

अटल व्योम cmd64x_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	cmd64x_set_timing(ap, adev, adev->pio_mode);
पूर्ण

/**
 *	cmd64x_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Called to करो the DMA mode setup.
 */

अटल व्योम cmd64x_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	अटल स्थिर u8 udma_data[] = अणु
		0x30, 0x20, 0x10, 0x20, 0x10, 0x00
	पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 regU, regD;

	पूर्णांक pciU = UDIDETCR0 + 8 * ap->port_no;
	पूर्णांक pciD = BMIDESR0 + 8 * ap->port_no;
	पूर्णांक shअगरt = 2 * adev->devno;

	pci_पढ़ो_config_byte(pdev, pciD, &regD);
	pci_पढ़ो_config_byte(pdev, pciU, &regU);

	/* DMA bits off */
	regD &= ~(0x20 << adev->devno);
	/* DMA control bits */
	regU &= ~(0x30 << shअगरt);
	/* DMA timing bits */
	regU &= ~(0x05 << adev->devno);

	अगर (adev->dma_mode >= XFER_UDMA_0) अणु
		/* Merge the timing value */
		regU |= udma_data[adev->dma_mode - XFER_UDMA_0] << shअगरt;
		/* Merge the control bits */
		regU |= 1 << adev->devno; /* UDMA on */
		अगर (adev->dma_mode > XFER_UDMA_2) /* 15nS timing */
			regU |= 4 << adev->devno;
	पूर्ण अन्यथा अणु
		regU &= ~ (1 << adev->devno);	/* UDMA off */
		cmd64x_set_timing(ap, adev, adev->dma_mode);
	पूर्ण

	regD |= 0x20 << adev->devno;

	pci_ग_लिखो_config_byte(pdev, pciU, regU);
	pci_ग_लिखो_config_byte(pdev, pciD, regD);
पूर्ण

/**
 *	cmd64x_sff_irq_check	-	check IDE पूर्णांकerrupt
 *	@ap: ATA पूर्णांकerface
 *
 *	Check IDE पूर्णांकerrupt in CFR/ARTTIM23 रेजिस्टरs.
 */

अटल bool cmd64x_sff_irq_check(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक irq_mask = ap->port_no ? ARTTIM23_INTR_CH1 : CFR_INTR_CH0;
	पूर्णांक irq_reg  = ap->port_no ? ARTTIM23 : CFR;
	u8 irq_stat;

	/* NOTE: पढ़ोing the रेजिस्टर should clear the पूर्णांकerrupt */
	pci_पढ़ो_config_byte(pdev, irq_reg, &irq_stat);

	वापस irq_stat & irq_mask;
पूर्ण

/**
 *	cmd64x_sff_irq_clear	-	clear IDE पूर्णांकerrupt
 *	@ap: ATA पूर्णांकerface
 *
 *	Clear IDE पूर्णांकerrupt in CFR/ARTTIM23 and DMA status रेजिस्टरs.
 */

अटल व्योम cmd64x_sff_irq_clear(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	पूर्णांक irq_reg = ap->port_no ? ARTTIM23 : CFR;
	u8 irq_stat;

	ata_bmdma_irq_clear(ap);

	/* Reading the रेजिस्टर should be enough to clear the पूर्णांकerrupt */
	pci_पढ़ो_config_byte(pdev, irq_reg, &irq_stat);
पूर्ण

/**
 *	cmd648_sff_irq_check	-	check IDE पूर्णांकerrupt
 *	@ap: ATA पूर्णांकerface
 *
 *	Check IDE पूर्णांकerrupt in MRDMODE रेजिस्टर.
 */

अटल bool cmd648_sff_irq_check(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ base = pci_resource_start(pdev, 4);
	पूर्णांक irq_mask = ap->port_no ? MRDMODE_INTR_CH1 : MRDMODE_INTR_CH0;
	u8 mrdmode = inb(base + 1);

	वापस mrdmode & irq_mask;
पूर्ण

/**
 *	cmd648_sff_irq_clear	-	clear IDE पूर्णांकerrupt
 *	@ap: ATA पूर्णांकerface
 *
 *	Clear IDE पूर्णांकerrupt in MRDMODE and DMA status रेजिस्टरs.
 */

अटल व्योम cmd648_sff_irq_clear(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अचिन्हित दीर्घ base = pci_resource_start(pdev, 4);
	पूर्णांक irq_mask = ap->port_no ? MRDMODE_INTR_CH1 : MRDMODE_INTR_CH0;
	u8 mrdmode;

	ata_bmdma_irq_clear(ap);

	/* Clear this port's पूर्णांकerrupt bit (leaving the other port alone) */
	mrdmode  = inb(base + 1);
	mrdmode &= ~(MRDMODE_INTR_CH0 | MRDMODE_INTR_CH1);
	outb(mrdmode | irq_mask, base + 1);
पूर्ण

/**
 *	cmd646r1_bmdma_stop	-	DMA stop callback
 *	@qc: Command in progress
 *
 *	Stub क्रम now जबतक investigating the r1 quirk in the old driver.
 */

अटल व्योम cmd646r1_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	ata_bmdma_stop(qc);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cmd64x_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल स्थिर काष्ठा ata_port_operations cmd64x_base_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.set_piomode	= cmd64x_set_piomode,
	.set_dmamode	= cmd64x_set_dmamode,
पूर्ण;

अटल काष्ठा ata_port_operations cmd64x_port_ops = अणु
	.inherits	= &cmd64x_base_ops,
	.sff_irq_check	= cmd64x_sff_irq_check,
	.sff_irq_clear	= cmd64x_sff_irq_clear,
	.cable_detect	= ata_cable_40wire,
पूर्ण;

अटल काष्ठा ata_port_operations cmd646r1_port_ops = अणु
	.inherits	= &cmd64x_base_ops,
	.sff_irq_check	= cmd64x_sff_irq_check,
	.sff_irq_clear	= cmd64x_sff_irq_clear,
	.bmdma_stop	= cmd646r1_bmdma_stop,
	.cable_detect	= ata_cable_40wire,
पूर्ण;

अटल काष्ठा ata_port_operations cmd646r3_port_ops = अणु
	.inherits	= &cmd64x_base_ops,
	.sff_irq_check	= cmd648_sff_irq_check,
	.sff_irq_clear	= cmd648_sff_irq_clear,
	.cable_detect	= ata_cable_40wire,
पूर्ण;

अटल काष्ठा ata_port_operations cmd648_port_ops = अणु
	.inherits	= &cmd64x_base_ops,
	.sff_irq_check	= cmd648_sff_irq_check,
	.sff_irq_clear	= cmd648_sff_irq_clear,
	.cable_detect	= cmd648_cable_detect,
पूर्ण;

अटल व्योम cmd64x_fixup(काष्ठा pci_dev *pdev)
अणु
	u8 mrdmode;

	pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, 64);
	pci_पढ़ो_config_byte(pdev, MRDMODE, &mrdmode);
	mrdmode &= ~0x30;	/* IRQ set up */
	mrdmode |= 0x02;	/* Memory पढ़ो line enable */
	pci_ग_लिखो_config_byte(pdev, MRDMODE, mrdmode);

	/* PPC specअगरic fixup copied from old driver */
#अगर_घोषित CONFIG_PPC
	pci_ग_लिखो_config_byte(pdev, UDIDETCR0, 0xF0);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक cmd64x_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info cmd_info[7] = अणु
		अणु	/* CMD 643 - no UDMA */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.port_ops = &cmd64x_port_ops
		पूर्ण,
		अणु	/* CMD 646 with broken UDMA */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.port_ops = &cmd64x_port_ops
		पूर्ण,
		अणु	/* CMD 646U with broken UDMA */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.port_ops = &cmd646r3_port_ops
		पूर्ण,
		अणु	/* CMD 646U2 with working UDMA */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.port_ops = &cmd646r3_port_ops
		पूर्ण,
		अणु	/* CMD 646 rev 1  */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.port_ops = &cmd646r1_port_ops
		पूर्ण,
		अणु	/* CMD 648 */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.port_ops = &cmd648_port_ops
		पूर्ण,
		अणु	/* CMD 649 */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &cmd648_port_ops
		पूर्ण
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु
		&cmd_info[id->driver_data],
		&cmd_info[id->driver_data],
		शून्य
	पूर्ण;
	u8 reg;
	पूर्णांक rc;
	काष्ठा pci_dev *bridge = pdev->bus->self;
	/* mobility split bridges करोn't report enabled ports correctly */
	पूर्णांक port_ok = !(bridge && bridge->venकरोr ==
			PCI_VENDOR_ID_MOBILITY_ELECTRONICS);
	/* all (with exceptions below) apart from 643 have CNTRL_CH0 bit */
	पूर्णांक cntrl_ch0_ok = (id->driver_data != 0);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	अगर (id->driver_data == 0)	/* 643 */
		ata_pci_bmdma_clear_simplex(pdev);

	अगर (pdev->device == PCI_DEVICE_ID_CMD_646)
		चयन (pdev->revision) अणु
		/* UDMA works since rev 5 */
		शेष:
			ppi[0] = &cmd_info[3];
			ppi[1] = &cmd_info[3];
			अवरोध;
		/* Interrupts in MRDMODE since rev 3 */
		हाल 3:
		हाल 4:
			ppi[0] = &cmd_info[2];
			ppi[1] = &cmd_info[2];
			अवरोध;
		/* Rev 1 with other problems? */
		हाल 1:
			ppi[0] = &cmd_info[4];
			ppi[1] = &cmd_info[4];
			fallthrough;
		/* Early revs have no CNTRL_CH0 */
		हाल 2:
		हाल 0:
			cntrl_ch0_ok = 0;
			अवरोध;
		पूर्ण

	cmd64x_fixup(pdev);

	/* check क्रम enabled ports */
	pci_पढ़ो_config_byte(pdev, CNTRL, &reg);
	अगर (!port_ok)
		dev_notice(&pdev->dev, "Mobility Bridge detected, ignoring CNTRL port enable/disable\n");
	अगर (port_ok && cntrl_ch0_ok && !(reg & CNTRL_CH0)) अणु
		dev_notice(&pdev->dev, "Primary port is disabled\n");
		ppi[0] = &ata_dummy_port_info;

	पूर्ण
	अगर (port_ok && !(reg & CNTRL_CH1)) अणु
		dev_notice(&pdev->dev, "Secondary port is disabled\n");
		ppi[1] = &ata_dummy_port_info;
	पूर्ण

	वापस ata_pci_bmdma_init_one(pdev, ppi, &cmd64x_sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cmd64x_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	cmd64x_fixup(pdev);

	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id cmd64x[] = अणु
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_643), 0 पूर्ण,
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_646), 1 पूर्ण,
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_648), 5 पूर्ण,
	अणु PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_649), 6 पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cmd64x_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= cmd64x,
	.probe 		= cmd64x_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= cmd64x_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cmd64x_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for CMD64x series PATA controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cmd64x);
MODULE_VERSION(DRV_VERSION);
