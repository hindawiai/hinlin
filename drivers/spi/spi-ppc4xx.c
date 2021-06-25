<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI_PPC4XX SPI controller driver.
 *
 * Copyright (C) 2007 Gary Jennejohn <garyj@denx.de>
 * Copyright 2008 Stefan Roese <sr@denx.de>, DENX Software Engineering
 * Copyright 2009 Harris Corporation, Steven A. Falco <sfalco@harris.com>
 *
 * Based in part on drivers/spi/spi_s3c24xx.c
 *
 * Copyright (c) 2006 Ben Dooks
 * Copyright (c) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 */

/*
 * The PPC4xx SPI controller has no FIFO so each sent/received byte will
 * generate an पूर्णांकerrupt to the CPU. This can cause high CPU utilization.
 * This driver allows platक्रमms to reduce the पूर्णांकerrupt load on the CPU
 * during SPI transfers by setting max_speed_hz via the device tree.
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>

/* bits in mode रेजिस्टर - bit 0 is MSb */

/*
 * SPI_PPC4XX_MODE_SCP = 0 means "data latched on trailing edge of clock"
 * SPI_PPC4XX_MODE_SCP = 1 means "data latched on leading edge of clock"
 * Note: This is the inverse of CPHA.
 */
#घोषणा SPI_PPC4XX_MODE_SCP	(0x80 >> 3)

/* SPI_PPC4XX_MODE_SPE = 1 means "port enabled" */
#घोषणा SPI_PPC4XX_MODE_SPE	(0x80 >> 4)

/*
 * SPI_PPC4XX_MODE_RD = 0 means "MSB first" - this is the normal mode
 * SPI_PPC4XX_MODE_RD = 1 means "LSB first" - this is bit-reversed mode
 * Note: This is identical to SPI_LSB_FIRST.
 */
#घोषणा SPI_PPC4XX_MODE_RD	(0x80 >> 5)

/*
 * SPI_PPC4XX_MODE_CI = 0 means "clock idles low"
 * SPI_PPC4XX_MODE_CI = 1 means "clock idles high"
 * Note: This is identical to CPOL.
 */
#घोषणा SPI_PPC4XX_MODE_CI	(0x80 >> 6)

/*
 * SPI_PPC4XX_MODE_IL = 0 means "loopback disable"
 * SPI_PPC4XX_MODE_IL = 1 means "loopback enable"
 */
#घोषणा SPI_PPC4XX_MODE_IL	(0x80 >> 7)

/* bits in control रेजिस्टर */
/* starts a transfer when set */
#घोषणा SPI_PPC4XX_CR_STR	(0x80 >> 7)

/* bits in status रेजिस्टर */
/* port is busy with a transfer */
#घोषणा SPI_PPC4XX_SR_BSY	(0x80 >> 6)
/* RxD पढ़ोy */
#घोषणा SPI_PPC4XX_SR_RBR	(0x80 >> 7)

/* घड़ी settings (SCP and CI) क्रम various SPI modes */
#घोषणा SPI_CLK_MODE0	(SPI_PPC4XX_MODE_SCP | 0)
#घोषणा SPI_CLK_MODE1	(0 | 0)
#घोषणा SPI_CLK_MODE2	(SPI_PPC4XX_MODE_SCP | SPI_PPC4XX_MODE_CI)
#घोषणा SPI_CLK_MODE3	(0 | SPI_PPC4XX_MODE_CI)

#घोषणा DRIVER_NAME	"spi_ppc4xx_of"

काष्ठा spi_ppc4xx_regs अणु
	u8 mode;
	u8 rxd;
	u8 txd;
	u8 cr;
	u8 sr;
	u8 dummy;
	/*
	 * Clock भागisor modulus रेजिस्टर
	 * This uses the following क्रमmula:
	 *    SCPClkOut = OPBCLK/(4(CDM + 1))
	 * or
	 *    CDM = (OPBCLK/4*SCPClkOut) - 1
	 * bit 0 is the MSb!
	 */
	u8 cdm;
पूर्ण;

/* SPI Controller driver's निजी data. */
काष्ठा ppc4xx_spi अणु
	/* bitbang has to be first */
	काष्ठा spi_bitbang bitbang;
	काष्ठा completion करोne;

	u64 mapbase;
	u64 mapsize;
	पूर्णांक irqnum;
	/* need this to set the SPI घड़ी */
	अचिन्हित पूर्णांक opb_freq;

	/* क्रम transfers */
	पूर्णांक len;
	पूर्णांक count;
	/* data buffers */
	स्थिर अचिन्हित अक्षर *tx;
	अचिन्हित अक्षर *rx;

	काष्ठा spi_ppc4xx_regs __iomem *regs; /* poपूर्णांकer to the रेजिस्टरs */
	काष्ठा spi_master *master;
	काष्ठा device *dev;
पूर्ण;

/* need this so we can set the घड़ी in the chipselect routine */
काष्ठा spi_ppc4xx_cs अणु
	u8 mode;
पूर्ण;

अटल पूर्णांक spi_ppc4xx_txrx(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा ppc4xx_spi *hw;
	u8 data;

	dev_dbg(&spi->dev, "txrx: tx %p, rx %p, len %d\n",
		t->tx_buf, t->rx_buf, t->len);

	hw = spi_master_get_devdata(spi->master);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->count = 0;

	/* send the first byte */
	data = hw->tx ? hw->tx[0] : 0;
	out_8(&hw->regs->txd, data);
	out_8(&hw->regs->cr, SPI_PPC4XX_CR_STR);
	रुको_क्रम_completion(&hw->करोne);

	वापस hw->count;
पूर्ण

अटल पूर्णांक spi_ppc4xx_setupxfer(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा ppc4xx_spi *hw = spi_master_get_devdata(spi->master);
	काष्ठा spi_ppc4xx_cs *cs = spi->controller_state;
	पूर्णांक scr;
	u8 cdm = 0;
	u32 speed;
	u8 bits_per_word;

	/* Start with the generic configuration क्रम this device. */
	bits_per_word = spi->bits_per_word;
	speed = spi->max_speed_hz;

	/*
	 * Modअगरy the configuration अगर the transfer overrides it.  Do not allow
	 * the transfer to overग_लिखो the generic configuration with zeros.
	 */
	अगर (t) अणु
		अगर (t->bits_per_word)
			bits_per_word = t->bits_per_word;

		अगर (t->speed_hz)
			speed = min(t->speed_hz, spi->max_speed_hz);
	पूर्ण

	अगर (!speed || (speed > spi->max_speed_hz)) अणु
		dev_err(&spi->dev, "invalid speed_hz (%d)\n", speed);
		वापस -EINVAL;
	पूर्ण

	/* Write new configuration */
	out_8(&hw->regs->mode, cs->mode);

	/* Set the घड़ी */
	/* opb_freq was alपढ़ोy भागided by 4 */
	scr = (hw->opb_freq / speed) - 1;
	अगर (scr > 0)
		cdm = min(scr, 0xff);

	dev_dbg(&spi->dev, "setting pre-scaler to %d (hz %d)\n", cdm, speed);

	अगर (in_8(&hw->regs->cdm) != cdm)
		out_8(&hw->regs->cdm, cdm);

	mutex_lock(&hw->bitbang.lock);
	अगर (!hw->bitbang.busy) अणु
		hw->bitbang.chipselect(spi, BITBANG_CS_INACTIVE);
		/* Need to ndelay here? */
	पूर्ण
	mutex_unlock(&hw->bitbang.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_ppc4xx_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_ppc4xx_cs *cs = spi->controller_state;

	अगर (!spi->max_speed_hz) अणु
		dev_err(&spi->dev, "invalid max_speed_hz (must be non-zero)\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cs == शून्य) अणु
		cs = kzalloc(माप *cs, GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		spi->controller_state = cs;
	पूर्ण

	/*
	 * We set all bits of the SPI0_MODE रेजिस्टर, so,
	 * no need to पढ़ो-modअगरy-ग_लिखो
	 */
	cs->mode = SPI_PPC4XX_MODE_SPE;

	चयन (spi->mode & (SPI_CPHA | SPI_CPOL)) अणु
	हाल SPI_MODE_0:
		cs->mode |= SPI_CLK_MODE0;
		अवरोध;
	हाल SPI_MODE_1:
		cs->mode |= SPI_CLK_MODE1;
		अवरोध;
	हाल SPI_MODE_2:
		cs->mode |= SPI_CLK_MODE2;
		अवरोध;
	हाल SPI_MODE_3:
		cs->mode |= SPI_CLK_MODE3;
		अवरोध;
	पूर्ण

	अगर (spi->mode & SPI_LSB_FIRST)
		cs->mode |= SPI_PPC4XX_MODE_RD;

	वापस 0;
पूर्ण

अटल irqवापस_t spi_ppc4xx_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ppc4xx_spi *hw;
	u8 status;
	u8 data;
	अचिन्हित पूर्णांक count;

	hw = (काष्ठा ppc4xx_spi *)dev_id;

	status = in_8(&hw->regs->sr);
	अगर (!status)
		वापस IRQ_NONE;

	/*
	 * BSY de-निश्चितs one cycle after the transfer is complete.  The
	 * पूर्णांकerrupt is निश्चितed after the transfer is complete.  The exact
	 * relationship is not करोcumented, hence this code.
	 */

	अगर (unlikely(status & SPI_PPC4XX_SR_BSY)) अणु
		u8 lstatus;
		पूर्णांक cnt = 0;

		dev_dbg(hw->dev, "got interrupt but spi still busy?\n");
		करो अणु
			ndelay(10);
			lstatus = in_8(&hw->regs->sr);
		पूर्ण जबतक (++cnt < 100 && lstatus & SPI_PPC4XX_SR_BSY);

		अगर (cnt >= 100) अणु
			dev_err(hw->dev, "busywait: too many loops!\n");
			complete(&hw->करोne);
			वापस IRQ_HANDLED;
		पूर्ण अन्यथा अणु
			/* status is always 1 (RBR) here */
			status = in_8(&hw->regs->sr);
			dev_dbg(hw->dev, "loops %d status %x\n", cnt, status);
		पूर्ण
	पूर्ण

	count = hw->count;
	hw->count++;

	/* RBR triggered this पूर्णांकerrupt.  Thereक्रमe, data must be पढ़ोy. */
	data = in_8(&hw->regs->rxd);
	अगर (hw->rx)
		hw->rx[count] = data;

	count++;

	अगर (count < hw->len) अणु
		data = hw->tx ? hw->tx[count] : 0;
		out_8(&hw->regs->txd, data);
		out_8(&hw->regs->cr, SPI_PPC4XX_CR_STR);
	पूर्ण अन्यथा अणु
		complete(&hw->करोne);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम spi_ppc4xx_cleanup(काष्ठा spi_device *spi)
अणु
	kमुक्त(spi->controller_state);
पूर्ण

अटल व्योम spi_ppc4xx_enable(काष्ठा ppc4xx_spi *hw)
अणु
	/*
	 * On all 4xx PPC's the SPI bus is shared/multiplexed with
	 * the 2nd I2C bus. We need to enable the the SPI bus beक्रमe
	 * using it.
	 */

	/* need to clear bit 14 to enable SPC */
	dcri_clrset(SDR0, SDR0_PFC1, 0x80000000 >> 14, 0);
पूर्ण

/*
 * platक्रमm_device layer stuff...
 */
अटल पूर्णांक spi_ppc4xx_of_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा ppc4xx_spi *hw;
	काष्ठा spi_master *master;
	काष्ठा spi_bitbang *bbp;
	काष्ठा resource resource;
	काष्ठा device_node *np = op->dev.of_node;
	काष्ठा device *dev = &op->dev;
	काष्ठा device_node *opbnp;
	पूर्णांक ret;
	स्थिर अचिन्हित पूर्णांक *clk;

	master = spi_alloc_master(dev, माप *hw);
	अगर (master == शून्य)
		वापस -ENOMEM;
	master->dev.of_node = np;
	platक्रमm_set_drvdata(op, master);
	hw = spi_master_get_devdata(master);
	hw->master = master;
	hw->dev = dev;

	init_completion(&hw->करोne);

	/* Setup the state क्रम the bitbang driver */
	bbp = &hw->bitbang;
	bbp->master = hw->master;
	bbp->setup_transfer = spi_ppc4xx_setupxfer;
	bbp->txrx_bufs = spi_ppc4xx_txrx;
	bbp->use_dma = 0;
	bbp->master->setup = spi_ppc4xx_setup;
	bbp->master->cleanup = spi_ppc4xx_cleanup;
	bbp->master->bits_per_word_mask = SPI_BPW_MASK(8);
	bbp->master->use_gpio_descriptors = true;
	/*
	 * The SPI core will count the number of GPIO descriptors to figure
	 * out the number of chip selects available on the platक्रमm.
	 */
	bbp->master->num_chipselect = 0;

	/* the spi->mode bits understood by this driver: */
	bbp->master->mode_bits =
		SPI_CPHA | SPI_CPOL | SPI_CS_HIGH | SPI_LSB_FIRST;

	/* Get the घड़ी क्रम the OPB */
	opbnp = of_find_compatible_node(शून्य, शून्य, "ibm,opb");
	अगर (opbnp == शून्य) अणु
		dev_err(dev, "OPB: cannot find node\n");
		ret = -ENODEV;
		जाओ मुक्त_master;
	पूर्ण
	/* Get the घड़ी (Hz) क्रम the OPB */
	clk = of_get_property(opbnp, "clock-frequency", शून्य);
	अगर (clk == शून्य) अणु
		dev_err(dev, "OPB: no clock-frequency property set\n");
		of_node_put(opbnp);
		ret = -ENODEV;
		जाओ मुक्त_master;
	पूर्ण
	hw->opb_freq = *clk;
	hw->opb_freq >>= 2;
	of_node_put(opbnp);

	ret = of_address_to_resource(np, 0, &resource);
	अगर (ret) अणु
		dev_err(dev, "error while parsing device node resource\n");
		जाओ मुक्त_master;
	पूर्ण
	hw->mapbase = resource.start;
	hw->mapsize = resource_size(&resource);

	/* Sanity check */
	अगर (hw->mapsize < माप(काष्ठा spi_ppc4xx_regs)) अणु
		dev_err(dev, "too small to map registers\n");
		ret = -EINVAL;
		जाओ मुक्त_master;
	पूर्ण

	/* Request IRQ */
	hw->irqnum = irq_of_parse_and_map(np, 0);
	ret = request_irq(hw->irqnum, spi_ppc4xx_पूर्णांक,
			  0, "spi_ppc4xx_of", (व्योम *)hw);
	अगर (ret) अणु
		dev_err(dev, "unable to allocate interrupt\n");
		जाओ मुक्त_master;
	पूर्ण

	अगर (!request_mem_region(hw->mapbase, hw->mapsize, DRIVER_NAME)) अणु
		dev_err(dev, "resource unavailable\n");
		ret = -EBUSY;
		जाओ request_mem_error;
	पूर्ण

	hw->regs = ioremap(hw->mapbase, माप(काष्ठा spi_ppc4xx_regs));

	अगर (!hw->regs) अणु
		dev_err(dev, "unable to memory map registers\n");
		ret = -ENXIO;
		जाओ map_io_error;
	पूर्ण

	spi_ppc4xx_enable(hw);

	/* Finally रेजिस्टर our spi controller */
	dev->dma_mask = 0;
	ret = spi_bitbang_start(bbp);
	अगर (ret) अणु
		dev_err(dev, "failed to register SPI master\n");
		जाओ unmap_regs;
	पूर्ण

	dev_info(dev, "driver initialized\n");

	वापस 0;

unmap_regs:
	iounmap(hw->regs);
map_io_error:
	release_mem_region(hw->mapbase, hw->mapsize);
request_mem_error:
	मुक्त_irq(hw->irqnum, hw);
मुक्त_master:
	spi_master_put(master);

	dev_err(dev, "initialization failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक spi_ppc4xx_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(op);
	काष्ठा ppc4xx_spi *hw = spi_master_get_devdata(master);

	spi_bitbang_stop(&hw->bitbang);
	release_mem_region(hw->mapbase, hw->mapsize);
	मुक्त_irq(hw->irqnum, hw);
	iounmap(hw->regs);
	spi_master_put(master);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id spi_ppc4xx_of_match[] = अणु
	अणु .compatible = "ibm,ppc4xx-spi", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, spi_ppc4xx_of_match);

अटल काष्ठा platक्रमm_driver spi_ppc4xx_of_driver = अणु
	.probe = spi_ppc4xx_of_probe,
	.हटाओ = spi_ppc4xx_of_हटाओ,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = spi_ppc4xx_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(spi_ppc4xx_of_driver);

MODULE_AUTHOR("Gary Jennejohn & Stefan Roese");
MODULE_DESCRIPTION("Simple PPC4xx SPI Driver");
MODULE_LICENSE("GPL");
