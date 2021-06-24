<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Faraday Technology FTIDE010 driver
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * Includes portions of the SL2312/SL3516/Gemini PATA driver
 * Copyright (C) 2003 StorLine, Inc <jason@storlink.com.tw>
 * Copyright (C) 2009 Janos Laube <janos.dev@gmail.com>
 * Copyright (C) 2010 Frederic Pecourt <खोलोgemini@मुक्त.fr>
 * Copyright (C) 2011 Tobias Waldvogel <tobias.waldvogel@gmail.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/libata.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश "sata_gemini.h"

#घोषणा DRV_NAME "pata_ftide010"

/**
 * काष्ठा ftide010 - state container क्रम the Faraday FTIDE010
 * @dev: poपूर्णांकer back to the device representing this controller
 * @base: remapped I/O space address
 * @pclk: peripheral घड़ी क्रम the IDE block
 * @host: poपूर्णांकer to the ATA host क्रम this device
 * @master_cbl: master cable type
 * @slave_cbl: slave cable type
 * @sg: Gemini SATA bridge poपूर्णांकer, अगर running on the Gemini
 * @master_to_sata0: Gemini SATA bridge: the ATA master is connected
 * to the SATA0 bridge
 * @slave_to_sata0: Gemini SATA bridge: the ATA slave is connected
 * to the SATA0 bridge
 * @master_to_sata1: Gemini SATA bridge: the ATA master is connected
 * to the SATA1 bridge
 * @slave_to_sata1: Gemini SATA bridge: the ATA slave is connected
 * to the SATA1 bridge
 */
काष्ठा ftide010 अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *pclk;
	काष्ठा ata_host *host;
	अचिन्हित पूर्णांक master_cbl;
	अचिन्हित पूर्णांक slave_cbl;
	/* Gemini-specअगरic properties */
	काष्ठा sata_gemini *sg;
	bool master_to_sata0;
	bool slave_to_sata0;
	bool master_to_sata1;
	bool slave_to_sata1;
पूर्ण;

#घोषणा FTIDE010_DMA_REG	0x00
#घोषणा FTIDE010_DMA_STATUS	0x02
#घोषणा FTIDE010_IDE_BMDTPR	0x04
#घोषणा FTIDE010_IDE_DEVICE_ID	0x08
#घोषणा FTIDE010_PIO_TIMING	0x10
#घोषणा FTIDE010_MWDMA_TIMING	0x11
#घोषणा FTIDE010_UDMA_TIMING0	0x12 /* Master */
#घोषणा FTIDE010_UDMA_TIMING1	0x13 /* Slave */
#घोषणा FTIDE010_CLK_MOD	0x14
/* These रेजिस्टरs are mapped directly to the IDE रेजिस्टरs */
#घोषणा FTIDE010_CMD_DATA	0x20
#घोषणा FTIDE010_ERROR_FEATURES	0x21
#घोषणा FTIDE010_NSECT		0x22
#घोषणा FTIDE010_LBAL		0x23
#घोषणा FTIDE010_LBAM		0x24
#घोषणा FTIDE010_LBAH		0x25
#घोषणा FTIDE010_DEVICE		0x26
#घोषणा FTIDE010_STATUS_COMMAND	0x27
#घोषणा FTIDE010_ALTSTAT_CTRL	0x36

/* Set this bit क्रम UDMA mode 5 and 6 */
#घोषणा FTIDE010_UDMA_TIMING_MODE_56	BIT(7)

/* 0 = 50 MHz, 1 = 66 MHz */
#घोषणा FTIDE010_CLK_MOD_DEV0_CLK_SEL	BIT(0)
#घोषणा FTIDE010_CLK_MOD_DEV1_CLK_SEL	BIT(1)
/* Enable UDMA on a device */
#घोषणा FTIDE010_CLK_MOD_DEV0_UDMA_EN	BIT(4)
#घोषणा FTIDE010_CLK_MOD_DEV1_UDMA_EN	BIT(5)

अटल काष्ठा scsi_host_ढाँचा pata_ftide010_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

/*
 * Bus timings
 *
 * The unit of the below required timings is two घड़ी periods of the ATA
 * reference घड़ी which is 30 nanoseconds per unit at 66MHz and 20
 * nanoseconds per unit at 50 MHz. The PIO timings assume 33MHz speed क्रम
 * PIO.
 *
 * pio_active_समय: array of 5 elements क्रम T2 timing क्रम Mode 0,
 * 1, 2, 3 and 4. Range 0..15.
 * pio_recovery_समय: array of 5 elements क्रम T2l timing क्रम Mode 0,
 * 1, 2, 3 and 4. Range 0..15.
 * mdma_50_active_समय: array of 4 elements क्रम Td timing क्रम multi
 * word DMA, Mode 0, 1, and 2 at 50 MHz. Range 0..15.
 * mdma_50_recovery_समय: array of 4 elements क्रम Tk timing क्रम
 * multi word DMA, Mode 0, 1 and 2 at 50 MHz. Range 0..15.
 * mdma_66_active_समय: array of 4 elements क्रम Td timing क्रम multi
 * word DMA, Mode 0, 1 and 2 at 66 MHz. Range 0..15.
 * mdma_66_recovery_समय: array of 4 elements क्रम Tk timing क्रम
 * multi word DMA, Mode 0, 1 and 2 at 66 MHz. Range 0..15.
 * udma_50_setup_समय: array of 4 elements क्रम Tvds timing क्रम ultra
 * DMA, Mode 0, 1, 2, 3, 4 and 5 at 50 MHz. Range 0..7.
 * udma_50_hold_समय: array of 4 elements क्रम Tdvh timing क्रम
 * multi word DMA, Mode 0, 1, 2, 3, 4 and 5 at 50 MHz, Range 0..7.
 * udma_66_setup_समय: array of 4 elements क्रम Tvds timing क्रम multi
 * word DMA, Mode 0, 1, 2, 3, 4, 5 and 6 at 66 MHz. Range 0..7.
 * udma_66_hold_समय: array of 4 elements क्रम Tdvh timing क्रम
 * multi word DMA, Mode 0, 1, 2, 3, 4, 5 and 6 at 66 MHz. Range 0..7.
 */
अटल स्थिर u8 pio_active_समय[5] = अणु10, 10, 10, 3, 3पूर्ण;
अटल स्थिर u8 pio_recovery_समय[5] = अणु10, 3, 1, 3, 1पूर्ण;
अटल स्थिर u8 mwdma_50_active_समय[3] = अणु6, 2, 2पूर्ण;
अटल स्थिर u8 mwdma_50_recovery_समय[3] = अणु6, 2, 1पूर्ण;
अटल स्थिर u8 mwdma_66_active_समय[3] = अणु8, 3, 3पूर्ण;
अटल स्थिर u8 mwdma_66_recovery_समय[3] = अणु8, 2, 1पूर्ण;
अटल स्थिर u8 udma_50_setup_समय[6] = अणु3, 3, 2, 2, 1, 1पूर्ण;
अटल स्थिर u8 udma_50_hold_समय[6] = अणु3, 1, 1, 1, 1, 1पूर्ण;
अटल स्थिर u8 udma_66_setup_समय[7] = अणु4, 4, 3, 2, पूर्ण;
अटल स्थिर u8 udma_66_hold_समय[7] = अणुपूर्ण;

/*
 * We set 66 MHz क्रम all MWDMA modes
 */
अटल स्थिर bool set_mdma_66_mhz[] = अणु true, true, true, true पूर्ण;

/*
 * We set 66 MHz क्रम UDMA modes 3, 4 and 6 and no others
 */
अटल स्थिर bool set_udma_66_mhz[] = अणु false, false, false, true, true, false, true पूर्ण;

अटल व्योम ftide010_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा ftide010 *ftide = ap->host->निजी_data;
	u8 speed = adev->dma_mode;
	u8 devno = adev->devno & 1;
	u8 udma_en_mask;
	u8 f66m_en_mask;
	u8 clkreg;
	u8 timreg;
	u8 i;

	/* Target device 0 (master) or 1 (slave) */
	अगर (!devno) अणु
		udma_en_mask = FTIDE010_CLK_MOD_DEV0_UDMA_EN;
		f66m_en_mask = FTIDE010_CLK_MOD_DEV0_CLK_SEL;
	पूर्ण अन्यथा अणु
		udma_en_mask = FTIDE010_CLK_MOD_DEV1_UDMA_EN;
		f66m_en_mask = FTIDE010_CLK_MOD_DEV1_CLK_SEL;
	पूर्ण

	clkreg = पढ़ोb(ftide->base + FTIDE010_CLK_MOD);
	clkreg &= ~udma_en_mask;
	clkreg &= ~f66m_en_mask;

	अगर (speed & XFER_UDMA_0) अणु
		i = speed & ~XFER_UDMA_0;
		dev_dbg(ftide->dev, "set UDMA mode %02x, index %d\n",
			speed, i);

		clkreg |= udma_en_mask;
		अगर (set_udma_66_mhz[i]) अणु
			clkreg |= f66m_en_mask;
			timreg = udma_66_setup_समय[i] << 4 |
				udma_66_hold_समय[i];
		पूर्ण अन्यथा अणु
			timreg = udma_50_setup_समय[i] << 4 |
				udma_50_hold_समय[i];
		पूर्ण

		/* A special bit needs to be set क्रम modes 5 and 6 */
		अगर (i >= 5)
			timreg |= FTIDE010_UDMA_TIMING_MODE_56;

		dev_dbg(ftide->dev, "UDMA write clkreg = %02x, timreg = %02x\n",
			clkreg, timreg);

		ग_लिखोb(clkreg, ftide->base + FTIDE010_CLK_MOD);
		ग_लिखोb(timreg, ftide->base + FTIDE010_UDMA_TIMING0 + devno);
	पूर्ण अन्यथा अणु
		i = speed & ~XFER_MW_DMA_0;
		dev_dbg(ftide->dev, "set MWDMA mode %02x, index %d\n",
			speed, i);

		अगर (set_mdma_66_mhz[i]) अणु
			clkreg |= f66m_en_mask;
			timreg = mwdma_66_active_समय[i] << 4 |
				mwdma_66_recovery_समय[i];
		पूर्ण अन्यथा अणु
			timreg = mwdma_50_active_समय[i] << 4 |
				mwdma_50_recovery_समय[i];
		पूर्ण
		dev_dbg(ftide->dev,
			"MWDMA write clkreg = %02x, timreg = %02x\n",
			clkreg, timreg);
		/* This will affect all devices */
		ग_लिखोb(clkreg, ftide->base + FTIDE010_CLK_MOD);
		ग_लिखोb(timreg, ftide->base + FTIDE010_MWDMA_TIMING);
	पूर्ण

	/*
	 * Store the current device (master or slave) in ap->निजी_data
	 * so that .qc_issue() can detect अगर this changes and reprogram
	 * the DMA settings.
	 */
	ap->निजी_data = adev;

	वापस;
पूर्ण

अटल व्योम ftide010_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा ftide010 *ftide = ap->host->निजी_data;
	u8 pio = adev->pio_mode - XFER_PIO_0;

	dev_dbg(ftide->dev, "set PIO mode %02x, index %d\n",
		adev->pio_mode, pio);
	ग_लिखोb(pio_active_समय[pio] << 4 | pio_recovery_समय[pio],
	       ftide->base + FTIDE010_PIO_TIMING);
पूर्ण

/*
 * We implement our own qc_issue() callback since we may need to set up
 * the timings dअगरferently क्रम master and slave transfers: the CLK_MOD_REG
 * and MWDMA_TIMING_REG is shared between master and slave, so reprogramming
 * this may be necessary.
 */
अटल अचिन्हित पूर्णांक ftide010_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा ata_device *adev = qc->dev;

	/*
	 * If the device changed, i.e. slave->master, master->slave,
	 * then set up the DMA mode again so we are sure the timings
	 * are correct.
	 */
	अगर (adev != ap->निजी_data && ata_dma_enabled(adev))
		ftide010_set_dmamode(ap, adev);

	वापस ata_bmdma_qc_issue(qc);
पूर्ण

अटल काष्ठा ata_port_operations pata_ftide010_port_ops = अणु
	.inherits	= &ata_bmdma_port_ops,
	.set_dmamode	= ftide010_set_dmamode,
	.set_piomode	= ftide010_set_piomode,
	.qc_issue	= ftide010_qc_issue,
पूर्ण;

अटल काष्ठा ata_port_info ftide010_port_info = अणु
	.flags		= ATA_FLAG_SLAVE_POSS,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.pio_mask	= ATA_PIO4,
	.port_ops	= &pata_ftide010_port_ops,
पूर्ण;

#अगर IS_ENABLED(CONFIG_SATA_GEMINI)

अटल पूर्णांक pata_ftide010_gemini_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा ftide010 *ftide = ap->host->निजी_data;
	काष्ठा device *dev = ftide->dev;
	काष्ठा sata_gemini *sg = ftide->sg;
	पूर्णांक bridges = 0;
	पूर्णांक ret;

	ret = ata_bmdma_port_start(ap);
	अगर (ret)
		वापस ret;

	अगर (ftide->master_to_sata0) अणु
		dev_info(dev, "SATA0 (master) start\n");
		ret = gemini_sata_start_bridge(sg, 0);
		अगर (!ret)
			bridges++;
	पूर्ण
	अगर (ftide->master_to_sata1) अणु
		dev_info(dev, "SATA1 (master) start\n");
		ret = gemini_sata_start_bridge(sg, 1);
		अगर (!ret)
			bridges++;
	पूर्ण
	/* Aव्योम द्विगुन-starting */
	अगर (ftide->slave_to_sata0 && !ftide->master_to_sata0) अणु
		dev_info(dev, "SATA0 (slave) start\n");
		ret = gemini_sata_start_bridge(sg, 0);
		अगर (!ret)
			bridges++;
	पूर्ण
	/* Aव्योम द्विगुन-starting */
	अगर (ftide->slave_to_sata1 && !ftide->master_to_sata1) अणु
		dev_info(dev, "SATA1 (slave) start\n");
		ret = gemini_sata_start_bridge(sg, 1);
		अगर (!ret)
			bridges++;
	पूर्ण

	dev_info(dev, "brought %d bridges online\n", bridges);
	वापस (bridges > 0) ? 0 : -EINVAL; // -ENODEV;
पूर्ण

अटल व्योम pata_ftide010_gemini_port_stop(काष्ठा ata_port *ap)
अणु
	काष्ठा ftide010 *ftide = ap->host->निजी_data;
	काष्ठा device *dev = ftide->dev;
	काष्ठा sata_gemini *sg = ftide->sg;

	अगर (ftide->master_to_sata0) अणु
		dev_info(dev, "SATA0 (master) stop\n");
		gemini_sata_stop_bridge(sg, 0);
	पूर्ण
	अगर (ftide->master_to_sata1) अणु
		dev_info(dev, "SATA1 (master) stop\n");
		gemini_sata_stop_bridge(sg, 1);
	पूर्ण
	/* Aव्योम द्विगुन-stopping */
	अगर (ftide->slave_to_sata0 && !ftide->master_to_sata0) अणु
		dev_info(dev, "SATA0 (slave) stop\n");
		gemini_sata_stop_bridge(sg, 0);
	पूर्ण
	/* Aव्योम द्विगुन-stopping */
	अगर (ftide->slave_to_sata1 && !ftide->master_to_sata1) अणु
		dev_info(dev, "SATA1 (slave) stop\n");
		gemini_sata_stop_bridge(sg, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक pata_ftide010_gemini_cable_detect(काष्ठा ata_port *ap)
अणु
	काष्ठा ftide010 *ftide = ap->host->निजी_data;

	/*
	 * Return the master cable, I have no clue how to वापस a dअगरferent
	 * cable क्रम the slave than क्रम the master.
	 */
	वापस ftide->master_cbl;
पूर्ण

अटल पूर्णांक pata_ftide010_gemini_init(काष्ठा ftide010 *ftide,
				     काष्ठा ata_port_info *pi,
				     bool is_ata1)
अणु
	काष्ठा device *dev = ftide->dev;
	काष्ठा sata_gemini *sg;
	क्रमागत gemini_muxmode muxmode;

	/* Look up SATA bridge */
	sg = gemini_sata_bridge_get();
	अगर (IS_ERR(sg))
		वापस PTR_ERR(sg);
	ftide->sg = sg;

	muxmode = gemini_sata_get_muxmode(sg);

	/* Special ops */
	pata_ftide010_port_ops.port_start =
		pata_ftide010_gemini_port_start;
	pata_ftide010_port_ops.port_stop =
		pata_ftide010_gemini_port_stop;
	pata_ftide010_port_ops.cable_detect =
		pata_ftide010_gemini_cable_detect;

	/* Flag port as SATA-capable */
	अगर (gemini_sata_bridge_enabled(sg, is_ata1))
		pi->flags |= ATA_FLAG_SATA;

	/* This device has broken DMA, only PIO works */
	अगर (of_machine_is_compatible("itian,sq201")) अणु
		pi->mwdma_mask = 0;
		pi->udma_mask = 0;
	पूर्ण

	/*
	 * We assume that a simple 40-wire cable is used in the PATA mode.
	 * अगर you're adding a प्रणाली using the PATA पूर्णांकerface, make sure
	 * the right cable is set up here, it might be necessary to use
	 * special hardware detection or encode the cable type in the device
	 * tree with special properties.
	 */
	अगर (!is_ata1) अणु
		चयन (muxmode) अणु
		हाल GEMINI_MUXMODE_0:
			ftide->master_cbl = ATA_CBL_SATA;
			ftide->slave_cbl = ATA_CBL_PATA40;
			ftide->master_to_sata0 = true;
			अवरोध;
		हाल GEMINI_MUXMODE_1:
			ftide->master_cbl = ATA_CBL_SATA;
			ftide->slave_cbl = ATA_CBL_NONE;
			ftide->master_to_sata0 = true;
			अवरोध;
		हाल GEMINI_MUXMODE_2:
			ftide->master_cbl = ATA_CBL_PATA40;
			ftide->slave_cbl = ATA_CBL_PATA40;
			अवरोध;
		हाल GEMINI_MUXMODE_3:
			ftide->master_cbl = ATA_CBL_SATA;
			ftide->slave_cbl = ATA_CBL_SATA;
			ftide->master_to_sata0 = true;
			ftide->slave_to_sata1 = true;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (muxmode) अणु
		हाल GEMINI_MUXMODE_0:
			ftide->master_cbl = ATA_CBL_SATA;
			ftide->slave_cbl = ATA_CBL_NONE;
			ftide->master_to_sata1 = true;
			अवरोध;
		हाल GEMINI_MUXMODE_1:
			ftide->master_cbl = ATA_CBL_SATA;
			ftide->slave_cbl = ATA_CBL_PATA40;
			ftide->master_to_sata1 = true;
			अवरोध;
		हाल GEMINI_MUXMODE_2:
			ftide->master_cbl = ATA_CBL_SATA;
			ftide->slave_cbl = ATA_CBL_SATA;
			ftide->slave_to_sata0 = true;
			ftide->master_to_sata1 = true;
			अवरोध;
		हाल GEMINI_MUXMODE_3:
			ftide->master_cbl = ATA_CBL_PATA40;
			ftide->slave_cbl = ATA_CBL_PATA40;
			अवरोध;
		पूर्ण
	पूर्ण
	dev_info(dev, "set up Gemini PATA%d\n", is_ata1);

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक pata_ftide010_gemini_init(काष्ठा ftide010 *ftide,
				     काष्ठा ata_port_info *pi,
				     bool is_ata1)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक pata_ftide010_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा ata_port_info pi = ftide010_port_info;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;
	काष्ठा ftide010 *ftide;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;
	पूर्णांक i;

	ftide = devm_kzalloc(dev, माप(*ftide), GFP_KERNEL);
	अगर (!ftide)
		वापस -ENOMEM;
	ftide->dev = dev;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	ftide->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ftide->base))
		वापस PTR_ERR(ftide->base);

	ftide->pclk = devm_clk_get(dev, "PCLK");
	अगर (!IS_ERR(ftide->pclk)) अणु
		ret = clk_prepare_enable(ftide->pclk);
		अगर (ret) अणु
			dev_err(dev, "failed to enable PCLK\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Some special Cortina Gemini init, अगर needed */
	अगर (of_device_is_compatible(np, "cortina,gemini-pata")) अणु
		/*
		 * We need to know which instance is probing (the
		 * Gemini has two instances of FTIDE010) and we करो
		 * this simply by looking at the physical base
		 * address, which is 0x63400000 क्रम ATA1, अन्यथा we
		 * are ATA0. This will also set up the cable types.
		 */
		ret = pata_ftide010_gemini_init(ftide,
				&pi,
				(res->start == 0x63400000));
		अगर (ret)
			जाओ err_dis_clk;
	पूर्ण अन्यथा अणु
		/* Else assume we are connected using PATA40 */
		ftide->master_cbl = ATA_CBL_PATA40;
		ftide->slave_cbl = ATA_CBL_PATA40;
	पूर्ण

	ftide->host = ata_host_alloc_pinfo(dev, ppi, 1);
	अगर (!ftide->host) अणु
		ret = -ENOMEM;
		जाओ err_dis_clk;
	पूर्ण
	ftide->host->निजी_data = ftide;

	क्रम (i = 0; i < ftide->host->n_ports; i++) अणु
		काष्ठा ata_port *ap = ftide->host->ports[i];
		काष्ठा ata_ioports *ioaddr = &ap->ioaddr;

		ioaddr->bmdma_addr = ftide->base + FTIDE010_DMA_REG;
		ioaddr->cmd_addr = ftide->base + FTIDE010_CMD_DATA;
		ioaddr->ctl_addr = ftide->base + FTIDE010_ALTSTAT_CTRL;
		ioaddr->altstatus_addr = ftide->base + FTIDE010_ALTSTAT_CTRL;
		ata_sff_std_ports(ioaddr);
	पूर्ण

	dev_info(dev, "device ID %08x, irq %d, reg %pR\n",
		 पढ़ोl(ftide->base + FTIDE010_IDE_DEVICE_ID), irq, res);

	ret = ata_host_activate(ftide->host, irq, ata_bmdma_पूर्णांकerrupt,
				0, &pata_ftide010_sht);
	अगर (ret)
		जाओ err_dis_clk;

	वापस 0;

err_dis_clk:
	अगर (!IS_ERR(ftide->pclk))
		clk_disable_unprepare(ftide->pclk);
	वापस ret;
पूर्ण

अटल पूर्णांक pata_ftide010_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा ftide010 *ftide = host->निजी_data;

	ata_host_detach(ftide->host);
	अगर (!IS_ERR(ftide->pclk))
		clk_disable_unprepare(ftide->pclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pata_ftide010_of_match[] = अणु
	अणु
		.compatible = "faraday,ftide010",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pata_ftide010_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(pata_ftide010_of_match),
	पूर्ण,
	.probe = pata_ftide010_probe,
	.हटाओ = pata_ftide010_हटाओ,
पूर्ण;
module_platक्रमm_driver(pata_ftide010_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
