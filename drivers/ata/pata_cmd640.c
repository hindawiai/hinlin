<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_cmd640.c 	- CMD640 PCI PATA क्रम new ATA layer
 *			  (C) 2007 Red Hat Inc
 *
 * Based upon
 *  linux/drivers/ide/pci/cmd640.c		Version 1.02  Sep 01, 1996
 *
 *  Copyright (C) 1995-1996  Linus Torvalds & authors (see driver)
 *
 *	This drives only the PCI version of the controller. If you have a
 *	VLB one then we have enough करोcs to support it but you can ग_लिखो
 *	your own code.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_cmd640"
#घोषणा DRV_VERSION "0.0.5"

काष्ठा cmd640_reg अणु
	पूर्णांक last;
	u8 reg58[ATA_MAX_DEVICES];
पूर्ण;

क्रमागत अणु
	CFR = 0x50,
	CNTRL = 0x51,
	CMDTIM = 0x52,
	ARTIM0 = 0x53,
	DRWTIM0 = 0x54,
	ARTIM23 = 0x57,
	DRWTIM23 = 0x58,
	BRST = 0x59
पूर्ण;

/**
 *	cmd640_set_piomode	-	set initial PIO mode data
 *	@ap: ATA port
 *	@adev: ATA device
 *
 *	Called to करो the PIO mode setup.
 */

अटल व्योम cmd640_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा cmd640_reg *timing = ap->निजी_data;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा ata_timing t;
	स्थिर अचिन्हित दीर्घ T = 1000000 / 33;
	स्थिर u8 setup_data[] = अणु 0x40, 0x40, 0x40, 0x80, 0x00 पूर्ण;
	u8 reg;
	पूर्णांक arttim = ARTIM0 + 2 * adev->devno;
	काष्ठा ata_device *pair = ata_dev_pair(adev);

	अगर (ata_timing_compute(adev, adev->pio_mode, &t, T, 0) < 0) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": mode computation failed.\n");
		वापस;
	पूर्ण

	/* The second channel has shared timings and the setup timing is
	   messy to चयन to merge it क्रम worst हाल */
	अगर (ap->port_no && pair) अणु
		काष्ठा ata_timing p;
		ata_timing_compute(pair, pair->pio_mode, &p, T, 1);
		ata_timing_merge(&p, &t, &t, ATA_TIMING_SETUP);
	पूर्ण

	/* Make the timings fit */
	अगर (t.recover > 16) अणु
		t.active += t.recover - 16;
		t.recover = 16;
	पूर्ण
	अगर (t.active > 16)
		t.active = 16;

	/* Now convert the घड़ीs पूर्णांकo values we can actually stuff पूर्णांकo
	   the chip */

	अगर (t.recover > 1)
		t.recover--;	/* 640B only */
	अन्यथा
		t.recover = 15;

	अगर (t.setup > 4)
		t.setup = 0xC0;
	अन्यथा
		t.setup = setup_data[t.setup];

	अगर (ap->port_no == 0) अणु
		t.active &= 0x0F;	/* 0 = 16 */

		/* Load setup timing */
		pci_पढ़ो_config_byte(pdev, arttim, &reg);
		reg &= 0x3F;
		reg |= t.setup;
		pci_ग_लिखो_config_byte(pdev, arttim, reg);

		/* Load active/recovery */
		pci_ग_लिखो_config_byte(pdev, arttim + 1, (t.active << 4) | t.recover);
	पूर्ण अन्यथा अणु
		/* Save the shared timings क्रम channel, they will be loaded
		   by qc_issue. Reloading the setup समय is expensive so we
		   keep a merged one loaded */
		pci_पढ़ो_config_byte(pdev, ARTIM23, &reg);
		reg &= 0x3F;
		reg |= t.setup;
		pci_ग_लिखो_config_byte(pdev, ARTIM23, reg);
		timing->reg58[adev->devno] = (t.active << 4) | t.recover;
	पूर्ण
पूर्ण


/**
 *	cmd640_qc_issue	-	command preparation hook
 *	@qc: Command to be issued
 *
 *	Channel 1 has shared timings. We must reprogram the
 *	घड़ी each drive 2/3 चयन we करो.
 */

अटल अचिन्हित पूर्णांक cmd640_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा cmd640_reg *timing = ap->निजी_data;

	अगर (ap->port_no != 0 && adev->devno != timing->last) अणु
		pci_ग_लिखो_config_byte(pdev, DRWTIM23, timing->reg58[adev->devno]);
		timing->last = adev->devno;
	पूर्ण
	वापस ata_sff_qc_issue(qc);
पूर्ण

/**
 *	cmd640_port_start	-	port setup
 *	@ap: ATA port being set up
 *
 *	The CMD640 needs to मुख्यtain निजी data काष्ठाures so we
 *	allocate space here.
 */

अटल पूर्णांक cmd640_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा cmd640_reg *timing;

	timing = devm_kzalloc(&pdev->dev, माप(काष्ठा cmd640_reg), GFP_KERNEL);
	अगर (timing == शून्य)
		वापस -ENOMEM;
	timing->last = -1;	/* Force a load */
	ap->निजी_data = timing;
	वापस 0;
पूर्ण

अटल bool cmd640_sff_irq_check(काष्ठा ata_port *ap)
अणु
	काष्ठा pci_dev *pdev	= to_pci_dev(ap->host->dev);
	पूर्णांक irq_reg		= ap->port_no ? ARTIM23 : CFR;
	u8  irq_stat, irq_mask	= ap->port_no ? 0x10 : 0x04;

	pci_पढ़ो_config_byte(pdev, irq_reg, &irq_stat);

	वापस irq_stat & irq_mask;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा cmd640_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations cmd640_port_ops = अणु
	.inherits	= &ata_sff_port_ops,
	/* In theory xfer_noirq is not needed once we समाप्त the prefetcher */
	.sff_data_xfer	= ata_sff_data_xfer32,
	.sff_irq_check	= cmd640_sff_irq_check,
	.qc_issue	= cmd640_qc_issue,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= cmd640_set_piomode,
	.port_start	= cmd640_port_start,
पूर्ण;

अटल व्योम cmd640_hardware_init(काष्ठा pci_dev *pdev)
अणु
	u8 ctrl;

	/* CMD640 detected, commiserations */
	pci_ग_लिखो_config_byte(pdev, 0x5B, 0x00);
	/* PIO0 command cycles */
	pci_ग_लिखो_config_byte(pdev, CMDTIM, 0);
	/* 512 byte bursts (sector) */
	pci_ग_लिखो_config_byte(pdev, BRST, 0x40);
	/*
	 * A reporter a दीर्घ समय ago
	 * Had problems with the data fअगरo
	 * So करोn't run the risk
	 * Of putting crap on the disk
	 * For its better just to go slow
	 */
	/* Do channel 0 */
	pci_पढ़ो_config_byte(pdev, CNTRL, &ctrl);
	pci_ग_लिखो_config_byte(pdev, CNTRL, ctrl | 0xC0);
	/* Ditto क्रम channel 1 */
	pci_पढ़ो_config_byte(pdev, ARTIM23, &ctrl);
	ctrl |= 0x0C;
	pci_ग_लिखो_config_byte(pdev, ARTIM23, ctrl);
पूर्ण

अटल पूर्णांक cmd640_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info = अणु
		.flags = ATA_FLAG_SLAVE_POSS,
		.pio_mask = ATA_PIO4,
		.port_ops = &cmd640_port_ops
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &info, शून्य पूर्ण;
	पूर्णांक rc;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	cmd640_hardware_init(pdev);

	वापस ata_pci_sff_init_one(pdev, ppi, &cmd640_sht, शून्य, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cmd640_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;
	cmd640_hardware_init(pdev);
	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id cmd640[] = अणु
	अणु PCI_VDEVICE(CMD, 0x640), 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver cmd640_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= cmd640,
	.probe 		= cmd640_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= cmd640_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(cmd640_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for CMD640 PATA controllers");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, cmd640);
MODULE_VERSION(DRV_VERSION);
