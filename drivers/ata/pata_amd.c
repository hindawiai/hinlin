<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pata_amd.c 	- AMD PATA क्रम new ATA layer
 *			  (C) 2005-2006 Red Hat Inc
 *
 *  Based on pata-sil680. Errata inक्रमmation is taken from data sheets
 *  and the amd74xx.c driver by Vojtech Pavlik. Nvidia SATA devices are
 *  claimed by sata-nv.c.
 *
 *  TODO:
 *	Variable प्रणाली घड़ी when/अगर it makes sense
 *	Power management on ports
 *
 *
 *  Documentation खुलाly available.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME "pata_amd"
#घोषणा DRV_VERSION "0.4.1"

/**
 *	timing_setup		-	shared timing computation and load
 *	@ap: ATA port being set up
 *	@adev: drive being configured
 *	@offset: port offset
 *	@speed: target speed
 *	@घड़ी: घड़ी multiplier (number of बार 33MHz क्रम this part)
 *
 *	Perक्रमm the actual timing set up क्रम Nvidia or AMD PATA devices.
 *	The actual devices vary so they all call पूर्णांकo this helper function
 *	providing the घड़ी multipler and offset (because AMD and Nvidia put
 *	the ports at dअगरferent locations).
 */

अटल व्योम timing_setup(काष्ठा ata_port *ap, काष्ठा ata_device *adev, पूर्णांक offset, पूर्णांक speed, पूर्णांक घड़ी)
अणु
	अटल स्थिर अचिन्हित अक्षर amd_cyc2udma[] = अणु
		6, 6, 5, 4, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 7
	पूर्ण;

	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	काष्ठा ata_device *peer = ata_dev_pair(adev);
	पूर्णांक dn = ap->port_no * 2 + adev->devno;
	काष्ठा ata_timing at, apeer;
	पूर्णांक T, UT;
	स्थिर पूर्णांक amd_घड़ी = 33333;	/* KHz. */
	u8 t;

	T = 1000000000 / amd_घड़ी;
	UT = T;
	अगर (घड़ी >= 2)
		UT = T / 2;

	अगर (ata_timing_compute(adev, speed, &at, T, UT) < 0) अणु
		dev_err(&pdev->dev, "unknown mode %d\n", speed);
		वापस;
	पूर्ण

	अगर (peer) अणु
		/* This may be over conservative */
		अगर (peer->dma_mode) अणु
			ata_timing_compute(peer, peer->dma_mode, &apeer, T, UT);
			ata_timing_merge(&apeer, &at, &at, ATA_TIMING_8BIT);
		पूर्ण
		ata_timing_compute(peer, peer->pio_mode, &apeer, T, UT);
		ata_timing_merge(&apeer, &at, &at, ATA_TIMING_8BIT);
	पूर्ण

	अगर (speed == XFER_UDMA_5 && amd_घड़ी <= 33333) at.udma = 1;
	अगर (speed == XFER_UDMA_6 && amd_घड़ी <= 33333) at.udma = 15;

	/*
	 *	Now करो the setup work
	 */

	/* Configure the address set up timing */
	pci_पढ़ो_config_byte(pdev, offset + 0x0C, &t);
	t = (t & ~(3 << ((3 - dn) << 1))) | ((clamp_val(at.setup, 1, 4) - 1) << ((3 - dn) << 1));
	pci_ग_लिखो_config_byte(pdev, offset + 0x0C , t);

	/* Configure the 8bit I/O timing */
	pci_ग_लिखो_config_byte(pdev, offset + 0x0E + (1 - (dn >> 1)),
		((clamp_val(at.act8b, 1, 16) - 1) << 4) | (clamp_val(at.rec8b, 1, 16) - 1));

	/* Drive timing */
	pci_ग_लिखो_config_byte(pdev, offset + 0x08 + (3 - dn),
		((clamp_val(at.active, 1, 16) - 1) << 4) | (clamp_val(at.recover, 1, 16) - 1));

	चयन (घड़ी) अणु
		हाल 1:
		t = at.udma ? (0xc0 | (clamp_val(at.udma, 2, 5) - 2)) : 0x03;
		अवरोध;

		हाल 2:
		t = at.udma ? (0xc0 | amd_cyc2udma[clamp_val(at.udma, 2, 10)]) : 0x03;
		अवरोध;

		हाल 3:
		t = at.udma ? (0xc0 | amd_cyc2udma[clamp_val(at.udma, 1, 10)]) : 0x03;
		अवरोध;

		हाल 4:
		t = at.udma ? (0xc0 | amd_cyc2udma[clamp_val(at.udma, 1, 15)]) : 0x03;
		अवरोध;

		शेष:
			वापस;
	पूर्ण

	/* UDMA timing */
	अगर (at.udma)
		pci_ग_लिखो_config_byte(pdev, offset + 0x10 + (3 - dn), t);
पूर्ण

/**
 *	amd_pre_reset		-	perक्रमm reset handling
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Reset sequence checking enable bits to see which ports are
 *	active.
 */

अटल पूर्णांक amd_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits amd_enable_bits[] = अणु
		अणु 0x40, 1, 0x02, 0x02 पूर्ण,
		अणु 0x40, 1, 0x01, 0x01 पूर्ण
	पूर्ण;

	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (!pci_test_config_bits(pdev, &amd_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	amd_cable_detect	-	report cable type
 *	@ap: port
 *
 *	AMD controller/BIOS setups record the cable type in word 0x42
 */

अटल पूर्णांक amd_cable_detect(काष्ठा ata_port *ap)
अणु
	अटल स्थिर u32 biपंचांगask[2] = अणु0x03, 0x0Cपूर्ण;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 ata66;

	pci_पढ़ो_config_byte(pdev, 0x42, &ata66);
	अगर (ata66 & biपंचांगask[ap->port_no])
		वापस ATA_CBL_PATA80;
	वापस ATA_CBL_PATA40;
पूर्ण

/**
 *	amd_fअगरo_setup		-	set the PIO FIFO क्रम ATA/ATAPI
 *	@ap: ATA पूर्णांकerface
 *
 *	Set the PCI fअगरo क्रम this device according to the devices present
 *	on the bus at this poपूर्णांक in समय. We need to turn the post ग_लिखो buffer
 *	off क्रम ATAPI devices as we may need to issue a word sized ग_लिखो to the
 *	device as the final I/O
 */

अटल व्योम amd_fअगरo_setup(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_device *adev;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);
	अटल स्थिर u8 fअगरobit[2] = अणु 0xC0, 0x30पूर्ण;
	u8 fअगरo = fअगरobit[ap->port_no];
	u8 r;


	ata_क्रम_each_dev(adev, &ap->link, ENABLED) अणु
		अगर (adev->class == ATA_DEV_ATAPI)
			fअगरo = 0;
	पूर्ण
	अगर (pdev->device == PCI_DEVICE_ID_AMD_VIPER_7411) /* FIFO is broken */
		fअगरo = 0;

	/* On the later chips the पढ़ो prefetch bits become no-op bits */
	pci_पढ़ो_config_byte(pdev, 0x41, &r);
	r &= ~fअगरobit[ap->port_no];
	r |= fअगरo;
	pci_ग_लिखो_config_byte(pdev, 0x41, r);
पूर्ण

/**
 *	amd33_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the AMD रेजिस्टरs क्रम PIO mode.
 */

अटल व्योम amd33_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	amd_fअगरo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 1);
पूर्ण

अटल व्योम amd66_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	amd_fअगरo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 2);
पूर्ण

अटल व्योम amd100_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	amd_fअगरo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 3);
पूर्ण

अटल व्योम amd133_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	amd_fअगरo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 4);
पूर्ण

/**
 *	amd33_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the MWDMA/UDMA modes क्रम the AMD and Nvidia
 *	chipset.
 */

अटल व्योम amd33_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x40, adev->dma_mode, 1);
पूर्ण

अटल व्योम amd66_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x40, adev->dma_mode, 2);
पूर्ण

अटल व्योम amd100_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x40, adev->dma_mode, 3);
पूर्ण

अटल व्योम amd133_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x40, adev->dma_mode, 4);
पूर्ण

/* Both host-side and drive-side detection results are worthless on NV
 * PATAs.  Ignore them and just follow what BIOS configured.  Both the
 * current configuration in PCI config reg and ACPI GTM result are
 * cached during driver attach and are consulted to select transfer
 * mode.
 */
अटल अचिन्हित दीर्घ nv_mode_filter(काष्ठा ata_device *dev,
				    अचिन्हित दीर्घ xfer_mask)
अणु
	अटल स्थिर अचिन्हित पूर्णांक udma_mask_map[] =
		अणु ATA_UDMA2, ATA_UDMA1, ATA_UDMA0, 0,
		  ATA_UDMA3, ATA_UDMA4, ATA_UDMA5, ATA_UDMA6 पूर्ण;
	काष्ठा ata_port *ap = dev->link->ap;
	अक्षर acpi_str[32] = "";
	u32 saved_udma, udma;
	स्थिर काष्ठा ata_acpi_gपंचांग *gपंचांग;
	अचिन्हित दीर्घ bios_limit = 0, acpi_limit = 0, limit;

	/* find out what BIOS configured */
	udma = saved_udma = (अचिन्हित दीर्घ)ap->host->निजी_data;

	अगर (ap->port_no == 0)
		udma >>= 16;
	अगर (dev->devno == 0)
		udma >>= 8;

	अगर ((udma & 0xc0) == 0xc0)
		bios_limit = ata_pack_xfermask(0, 0, udma_mask_map[udma & 0x7]);

	/* consult ACPI GTM too */
	gपंचांग = ata_acpi_init_gपंचांग(ap);
	अगर (gपंचांग) अणु
		acpi_limit = ata_acpi_gपंचांग_xfermask(dev, gपंचांग);

		snम_लिखो(acpi_str, माप(acpi_str), " (%u:%u:0x%x)",
			 gपंचांग->drive[0].dma, gपंचांग->drive[1].dma, gपंचांग->flags);
	पूर्ण

	/* be optimistic, EH can take care of things अगर something goes wrong */
	limit = bios_limit | acpi_limit;

	/* If PIO or DMA isn't configured at all, don't limit.  Let EH
	 * handle it.
	 */
	अगर (!(limit & ATA_MASK_PIO))
		limit |= ATA_MASK_PIO;
	अगर (!(limit & (ATA_MASK_MWDMA | ATA_MASK_UDMA)))
		limit |= ATA_MASK_MWDMA | ATA_MASK_UDMA;
	/* PIO4, MWDMA2, UDMA2 should always be supported regardless of
	   cable detection result */
	limit |= ata_pack_xfermask(ATA_PIO4, ATA_MWDMA2, ATA_UDMA2);

	ata_port_dbg(ap, "nv_mode_filter: 0x%lx&0x%lx->0x%lx, "
			"BIOS=0x%lx (0x%x) ACPI=0x%lx%s\n",
			xfer_mask, limit, xfer_mask & limit, bios_limit,
			saved_udma, acpi_limit, acpi_str);

	वापस xfer_mask & limit;
पूर्ण

/**
 *	nv_pre_reset	-	cable detection
 *	@link: ATA link
 *	@deadline: deadline jअगरfies क्रम the operation
 *
 *	Perक्रमm cable detection. The BIOS stores this in PCI config
 *	space क्रम us.
 */

अटल पूर्णांक nv_pre_reset(काष्ठा ata_link *link, अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर काष्ठा pci_bits nv_enable_bits[] = अणु
		अणु 0x50, 1, 0x02, 0x02 पूर्ण,
		अणु 0x50, 1, 0x01, 0x01 पूर्ण
	पूर्ण;

	काष्ठा ata_port *ap = link->ap;
	काष्ठा pci_dev *pdev = to_pci_dev(ap->host->dev);

	अगर (!pci_test_config_bits(pdev, &nv_enable_bits[ap->port_no]))
		वापस -ENOENT;

	वापस ata_sff_prereset(link, deadline);
पूर्ण

/**
 *	nv100_set_piomode	-	set initial PIO mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the AMD रेजिस्टरs क्रम PIO mode.
 */

अटल व्योम nv100_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x50, adev->pio_mode, 3);
पूर्ण

अटल व्योम nv133_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x50, adev->pio_mode, 4);
पूर्ण

/**
 *	nv100_set_dmamode	-	set initial DMA mode data
 *	@ap: ATA पूर्णांकerface
 *	@adev: ATA device
 *
 *	Program the MWDMA/UDMA modes क्रम the AMD and Nvidia
 *	chipset.
 */

अटल व्योम nv100_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x50, adev->dma_mode, 3);
पूर्ण

अटल व्योम nv133_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	timing_setup(ap, adev, 0x50, adev->dma_mode, 4);
पूर्ण

अटल व्योम nv_host_stop(काष्ठा ata_host *host)
अणु
	u32 udma = (अचिन्हित दीर्घ)host->निजी_data;

	/* restore PCI config रेजिस्टर 0x60 */
	pci_ग_लिखो_config_dword(to_pci_dev(host->dev), 0x60, udma);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा amd_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल स्थिर काष्ठा ata_port_operations amd_base_port_ops = अणु
	.inherits	= &ata_bmdma32_port_ops,
	.prereset	= amd_pre_reset,
पूर्ण;

अटल काष्ठा ata_port_operations amd33_port_ops = अणु
	.inherits	= &amd_base_port_ops,
	.cable_detect	= ata_cable_40wire,
	.set_piomode	= amd33_set_piomode,
	.set_dmamode	= amd33_set_dmamode,
पूर्ण;

अटल काष्ठा ata_port_operations amd66_port_ops = अणु
	.inherits	= &amd_base_port_ops,
	.cable_detect	= ata_cable_unknown,
	.set_piomode	= amd66_set_piomode,
	.set_dmamode	= amd66_set_dmamode,
पूर्ण;

अटल काष्ठा ata_port_operations amd100_port_ops = अणु
	.inherits	= &amd_base_port_ops,
	.cable_detect	= ata_cable_unknown,
	.set_piomode	= amd100_set_piomode,
	.set_dmamode	= amd100_set_dmamode,
पूर्ण;

अटल काष्ठा ata_port_operations amd133_port_ops = अणु
	.inherits	= &amd_base_port_ops,
	.cable_detect	= amd_cable_detect,
	.set_piomode	= amd133_set_piomode,
	.set_dmamode	= amd133_set_dmamode,
पूर्ण;

अटल स्थिर काष्ठा ata_port_operations nv_base_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.cable_detect	= ata_cable_ignore,
	.mode_filter	= nv_mode_filter,
	.prereset	= nv_pre_reset,
	.host_stop	= nv_host_stop,
पूर्ण;

अटल काष्ठा ata_port_operations nv100_port_ops = अणु
	.inherits	= &nv_base_port_ops,
	.set_piomode	= nv100_set_piomode,
	.set_dmamode	= nv100_set_dmamode,
पूर्ण;

अटल काष्ठा ata_port_operations nv133_port_ops = अणु
	.inherits	= &nv_base_port_ops,
	.set_piomode	= nv133_set_piomode,
	.set_dmamode	= nv133_set_dmamode,
पूर्ण;

अटल व्योम amd_clear_fअगरo(काष्ठा pci_dev *pdev)
अणु
	u8 fअगरo;
	/* Disable the FIFO, the FIFO logic will re-enable it as
	   appropriate */
	pci_पढ़ो_config_byte(pdev, 0x41, &fअगरo);
	fअगरo &= 0x0F;
	pci_ग_लिखो_config_byte(pdev, 0x41, fअगरo);
पूर्ण

अटल पूर्णांक amd_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा ata_port_info info[10] = अणु
		अणु	/* 0: AMD 7401 - no swdma */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.port_ops = &amd33_port_ops
		पूर्ण,
		अणु	/* 1: Early AMD7409 - no swdma */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.port_ops = &amd66_port_ops
		पूर्ण,
		अणु	/* 2: AMD 7409 */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.port_ops = &amd66_port_ops
		पूर्ण,
		अणु	/* 3: AMD 7411 */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &amd100_port_ops
		पूर्ण,
		अणु	/* 4: AMD 7441 */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &amd100_port_ops
		पूर्ण,
		अणु	/* 5: AMD 8111 - no swdma */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA6,
			.port_ops = &amd133_port_ops
		पूर्ण,
		अणु	/* 6: AMD 8111 UDMA 100 (Serenade) - no swdma */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &amd133_port_ops
		पूर्ण,
		अणु	/* 7: Nvidia Nक्रमce */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &nv100_port_ops
		पूर्ण,
		अणु	/* 8: Nvidia Nक्रमce2 and later - no swdma */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA6,
			.port_ops = &nv133_port_ops
		पूर्ण,
		अणु	/* 9: AMD CS5536 (Geode companion) */
			.flags = ATA_FLAG_SLAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.port_ops = &amd100_port_ops
		पूर्ण
	पूर्ण;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु शून्य, शून्य पूर्ण;
	पूर्णांक type = id->driver_data;
	व्योम *hpriv = शून्य;
	u8 fअगरo;
	पूर्णांक rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	pci_पढ़ो_config_byte(pdev, 0x41, &fअगरo);

	/* Check क्रम AMD7409 without swdma errata and अगर found adjust type */
	अगर (type == 1 && pdev->revision > 0x7)
		type = 2;

	/* Serenade ? */
	अगर (type == 5 && pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_AMD &&
			 pdev->subप्रणाली_device == PCI_DEVICE_ID_AMD_SERENADE)
		type = 6;	/* UDMA 100 only */

	/*
	 * Okay, type is determined now.  Apply type-specअगरic workarounds.
	 */
	ppi[0] = &info[type];

	अगर (type < 3)
		ata_pci_bmdma_clear_simplex(pdev);
	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD)
		amd_clear_fअगरo(pdev);
	/* Cable detection on Nvidia chips करोesn't work too well,
	 * cache BIOS programmed UDMA mode.
	 */
	अगर (type == 7 || type == 8) अणु
		u32 udma;

		pci_पढ़ो_config_dword(pdev, 0x60, &udma);
		hpriv = (व्योम *)(अचिन्हित दीर्घ)udma;
	पूर्ण

	/* And fire it up */
	वापस ata_pci_bmdma_init_one(pdev, ppi, &amd_sht, hpriv, 0);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक amd_reinit_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD) अणु
		amd_clear_fअगरo(pdev);
		अगर (pdev->device == PCI_DEVICE_ID_AMD_VIPER_7409 ||
		    pdev->device == PCI_DEVICE_ID_AMD_COBRA_7401)
			ata_pci_bmdma_clear_simplex(pdev);
	पूर्ण
	ata_host_resume(host);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id amd[] = अणु
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_COBRA_7401),		0 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_VIPER_7409),		1 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_VIPER_7411),		3 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_OPUS_7441),		4 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_8111_IDE),		5 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_IDE),	7 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE2_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE2S_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE3_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE3S_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_CK804_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP04_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP51_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP55_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP61_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP65_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP67_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP73_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFORCE_MCP77_IDE),	8 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_IDE),		9 पूर्ण,
	अणु PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_DEV_IDE),	9 पूर्ण,

	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver amd_pci_driver = अणु
	.name 		= DRV_NAME,
	.id_table	= amd,
	.probe 		= amd_init_one,
	.हटाओ		= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend	= ata_pci_device_suspend,
	.resume		= amd_reinit_one,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(amd_pci_driver);

MODULE_AUTHOR("Alan Cox");
MODULE_DESCRIPTION("low-level driver for AMD and Nvidia PATA IDE");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, amd);
MODULE_VERSION(DRV_VERSION);
