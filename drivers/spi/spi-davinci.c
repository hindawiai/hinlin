<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Texas Instruments.
 * Copyright (C) 2010 EF Johnson Technologies
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/slab.h>

#समावेश <linux/platक्रमm_data/spi-davinci.h>

#घोषणा CS_DEFAULT	0xFF

#घोषणा SPIFMT_PHASE_MASK	BIT(16)
#घोषणा SPIFMT_POLARITY_MASK	BIT(17)
#घोषणा SPIFMT_DISTIMER_MASK	BIT(18)
#घोषणा SPIFMT_SHIFTसूची_MASK	BIT(20)
#घोषणा SPIFMT_WAITENA_MASK	BIT(21)
#घोषणा SPIFMT_PARITYENA_MASK	BIT(22)
#घोषणा SPIFMT_ODD_PARITY_MASK	BIT(23)
#घोषणा SPIFMT_WDELAY_MASK	0x3f000000u
#घोषणा SPIFMT_WDELAY_SHIFT	24
#घोषणा SPIFMT_PRESCALE_SHIFT	8

/* SPIPC0 */
#घोषणा SPIPC0_DIFUN_MASK	BIT(11)		/* MISO */
#घोषणा SPIPC0_DOFUN_MASK	BIT(10)		/* MOSI */
#घोषणा SPIPC0_CLKFUN_MASK	BIT(9)		/* CLK */
#घोषणा SPIPC0_SPIENA_MASK	BIT(8)		/* nREADY */

#घोषणा SPIINT_MASKALL		0x0101035F
#घोषणा SPIINT_MASKINT		0x0000015F
#घोषणा SPI_INTLVL_1		0x000001FF
#घोषणा SPI_INTLVL_0		0x00000000

/* SPIDAT1 (upper 16 bit defines) */
#घोषणा SPIDAT1_CSHOLD_MASK	BIT(12)
#घोषणा SPIDAT1_WDEL		BIT(10)

/* SPIGCR1 */
#घोषणा SPIGCR1_CLKMOD_MASK	BIT(1)
#घोषणा SPIGCR1_MASTER_MASK     BIT(0)
#घोषणा SPIGCR1_POWERDOWN_MASK	BIT(8)
#घोषणा SPIGCR1_LOOPBACK_MASK	BIT(16)
#घोषणा SPIGCR1_SPIENA_MASK	BIT(24)

/* SPIBUF */
#घोषणा SPIBUF_TXFULL_MASK	BIT(29)
#घोषणा SPIBUF_RXEMPTY_MASK	BIT(31)

/* SPIDELAY */
#घोषणा SPIDELAY_C2TDELAY_SHIFT 24
#घोषणा SPIDELAY_C2TDELAY_MASK  (0xFF << SPIDELAY_C2TDELAY_SHIFT)
#घोषणा SPIDELAY_T2CDELAY_SHIFT 16
#घोषणा SPIDELAY_T2CDELAY_MASK  (0xFF << SPIDELAY_T2CDELAY_SHIFT)
#घोषणा SPIDELAY_T2EDELAY_SHIFT 8
#घोषणा SPIDELAY_T2EDELAY_MASK  (0xFF << SPIDELAY_T2EDELAY_SHIFT)
#घोषणा SPIDELAY_C2EDELAY_SHIFT 0
#घोषणा SPIDELAY_C2EDELAY_MASK  0xFF

/* Error Masks */
#घोषणा SPIFLG_DLEN_ERR_MASK		BIT(0)
#घोषणा SPIFLG_TIMEOUT_MASK		BIT(1)
#घोषणा SPIFLG_PARERR_MASK		BIT(2)
#घोषणा SPIFLG_DESYNC_MASK		BIT(3)
#घोषणा SPIFLG_BITERR_MASK		BIT(4)
#घोषणा SPIFLG_OVRRUN_MASK		BIT(6)
#घोषणा SPIFLG_BUF_INIT_ACTIVE_MASK	BIT(24)
#घोषणा SPIFLG_ERROR_MASK		(SPIFLG_DLEN_ERR_MASK \
				| SPIFLG_TIMEOUT_MASK | SPIFLG_PARERR_MASK \
				| SPIFLG_DESYNC_MASK | SPIFLG_BITERR_MASK \
				| SPIFLG_OVRRUN_MASK)

#घोषणा SPIINT_DMA_REQ_EN	BIT(16)

/* SPI Controller रेजिस्टरs */
#घोषणा SPIGCR0		0x00
#घोषणा SPIGCR1		0x04
#घोषणा SPIINT		0x08
#घोषणा SPILVL		0x0c
#घोषणा SPIFLG		0x10
#घोषणा SPIPC0		0x14
#घोषणा SPIDAT1		0x3c
#घोषणा SPIBUF		0x40
#घोषणा SPIDELAY	0x48
#घोषणा SPIDEF		0x4c
#घोषणा SPIFMT0		0x50

#घोषणा DMA_MIN_BYTES	16

/* SPI Controller driver's निजी data. */
काष्ठा davinci_spi अणु
	काष्ठा spi_bitbang	bitbang;
	काष्ठा clk		*clk;

	u8			version;
	resource_माप_प्रकार		pbase;
	व्योम __iomem		*base;
	u32			irq;
	काष्ठा completion	करोne;

	स्थिर व्योम		*tx;
	व्योम			*rx;
	पूर्णांक			rcount;
	पूर्णांक			wcount;

	काष्ठा dma_chan		*dma_rx;
	काष्ठा dma_chan		*dma_tx;

	काष्ठा davinci_spi_platक्रमm_data pdata;

	व्योम			(*get_rx)(u32 rx_data, काष्ठा davinci_spi *);
	u32			(*get_tx)(काष्ठा davinci_spi *);

	u8			*bytes_per_word;

	u8			prescaler_limit;
पूर्ण;

अटल काष्ठा davinci_spi_config davinci_spi_शेष_cfg;

अटल व्योम davinci_spi_rx_buf_u8(u32 data, काष्ठा davinci_spi *dspi)
अणु
	अगर (dspi->rx) अणु
		u8 *rx = dspi->rx;
		*rx++ = (u8)data;
		dspi->rx = rx;
	पूर्ण
पूर्ण

अटल व्योम davinci_spi_rx_buf_u16(u32 data, काष्ठा davinci_spi *dspi)
अणु
	अगर (dspi->rx) अणु
		u16 *rx = dspi->rx;
		*rx++ = (u16)data;
		dspi->rx = rx;
	पूर्ण
पूर्ण

अटल u32 davinci_spi_tx_buf_u8(काष्ठा davinci_spi *dspi)
अणु
	u32 data = 0;

	अगर (dspi->tx) अणु
		स्थिर u8 *tx = dspi->tx;

		data = *tx++;
		dspi->tx = tx;
	पूर्ण
	वापस data;
पूर्ण

अटल u32 davinci_spi_tx_buf_u16(काष्ठा davinci_spi *dspi)
अणु
	u32 data = 0;

	अगर (dspi->tx) अणु
		स्थिर u16 *tx = dspi->tx;

		data = *tx++;
		dspi->tx = tx;
	पूर्ण
	वापस data;
पूर्ण

अटल अंतरभूत व्योम set_io_bits(व्योम __iomem *addr, u32 bits)
अणु
	u32 v = ioपढ़ो32(addr);

	v |= bits;
	ioग_लिखो32(v, addr);
पूर्ण

अटल अंतरभूत व्योम clear_io_bits(व्योम __iomem *addr, u32 bits)
अणु
	u32 v = ioपढ़ो32(addr);

	v &= ~bits;
	ioग_लिखो32(v, addr);
पूर्ण

/*
 * Interface to control the chip select संकेत
 */
अटल व्योम davinci_spi_chipselect(काष्ठा spi_device *spi, पूर्णांक value)
अणु
	काष्ठा davinci_spi *dspi;
	काष्ठा davinci_spi_config *spicfg = spi->controller_data;
	u8 chip_sel = spi->chip_select;
	u16 spidat1 = CS_DEFAULT;

	dspi = spi_master_get_devdata(spi->master);

	/* program delay transfers अगर tx_delay is non zero */
	अगर (spicfg && spicfg->wdelay)
		spidat1 |= SPIDAT1_WDEL;

	/*
	 * Board specअगरic chip select logic decides the polarity and cs
	 * line क्रम the controller
	 */
	अगर (spi->cs_gpiod) अणु
		/*
		 * FIXME: is this code ever executed? This host करोes not
		 * set SPI_MASTER_GPIO_SS so this chipselect callback should
		 * not get called from the SPI core when we are using
		 * GPIOs क्रम chip select.
		 */
		अगर (value == BITBANG_CS_ACTIVE)
			gpiod_set_value(spi->cs_gpiod, 1);
		अन्यथा
			gpiod_set_value(spi->cs_gpiod, 0);
	पूर्ण अन्यथा अणु
		अगर (value == BITBANG_CS_ACTIVE) अणु
			अगर (!(spi->mode & SPI_CS_WORD))
				spidat1 |= SPIDAT1_CSHOLD_MASK;
			spidat1 &= ~(0x1 << chip_sel);
		पूर्ण
	पूर्ण

	ioग_लिखो16(spidat1, dspi->base + SPIDAT1 + 2);
पूर्ण

/**
 * davinci_spi_get_prescale - Calculates the correct prescale value
 * @dspi: the controller data
 * @max_speed_hz: the maximum rate the SPI घड़ी can run at
 *
 * This function calculates the prescale value that generates a घड़ी rate
 * less than or equal to the specअगरied maximum.
 *
 * Returns: calculated prescale value क्रम easy programming पूर्णांकo SPI रेजिस्टरs
 * or negative error number अगर valid prescalar cannot be updated.
 */
अटल अंतरभूत पूर्णांक davinci_spi_get_prescale(काष्ठा davinci_spi *dspi,
							u32 max_speed_hz)
अणु
	पूर्णांक ret;

	/* Subtract 1 to match what will be programmed पूर्णांकo SPI रेजिस्टर. */
	ret = DIV_ROUND_UP(clk_get_rate(dspi->clk), max_speed_hz) - 1;

	अगर (ret < dspi->prescaler_limit || ret > 255)
		वापस -EINVAL;

	वापस ret;
पूर्ण

/**
 * davinci_spi_setup_transfer - This functions will determine transfer method
 * @spi: spi device on which data transfer to be करोne
 * @t: spi transfer in which transfer info is filled
 *
 * This function determines data transfer method (8/16/32 bit transfer).
 * It will also set the SPI Clock Control रेजिस्टर according to
 * SPI slave device freq.
 */
अटल पूर्णांक davinci_spi_setup_transfer(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t)
अणु

	काष्ठा davinci_spi *dspi;
	काष्ठा davinci_spi_config *spicfg;
	u8 bits_per_word = 0;
	u32 hz = 0, spअगरmt = 0;
	पूर्णांक prescale;

	dspi = spi_master_get_devdata(spi->master);
	spicfg = spi->controller_data;
	अगर (!spicfg)
		spicfg = &davinci_spi_शेष_cfg;

	अगर (t) अणु
		bits_per_word = t->bits_per_word;
		hz = t->speed_hz;
	पूर्ण

	/* अगर bits_per_word is not set then set it शेष */
	अगर (!bits_per_word)
		bits_per_word = spi->bits_per_word;

	/*
	 * Assign function poपूर्णांकer to appropriate transfer method
	 * 8bit, 16bit or 32bit transfer
	 */
	अगर (bits_per_word <= 8) अणु
		dspi->get_rx = davinci_spi_rx_buf_u8;
		dspi->get_tx = davinci_spi_tx_buf_u8;
		dspi->bytes_per_word[spi->chip_select] = 1;
	पूर्ण अन्यथा अणु
		dspi->get_rx = davinci_spi_rx_buf_u16;
		dspi->get_tx = davinci_spi_tx_buf_u16;
		dspi->bytes_per_word[spi->chip_select] = 2;
	पूर्ण

	अगर (!hz)
		hz = spi->max_speed_hz;

	/* Set up SPIFMTn रेजिस्टर, unique to this chipselect. */

	prescale = davinci_spi_get_prescale(dspi, hz);
	अगर (prescale < 0)
		वापस prescale;

	spअगरmt = (prescale << SPIFMT_PRESCALE_SHIFT) | (bits_per_word & 0x1f);

	अगर (spi->mode & SPI_LSB_FIRST)
		spअगरmt |= SPIFMT_SHIFTसूची_MASK;

	अगर (spi->mode & SPI_CPOL)
		spअगरmt |= SPIFMT_POLARITY_MASK;

	अगर (!(spi->mode & SPI_CPHA))
		spअगरmt |= SPIFMT_PHASE_MASK;

	/*
	* Assume wdelay is used only on SPI peripherals that has this field
	* in SPIFMTn रेजिस्टर and when it's configured from board file or DT.
	*/
	अगर (spicfg->wdelay)
		spअगरmt |= ((spicfg->wdelay << SPIFMT_WDELAY_SHIFT)
				& SPIFMT_WDELAY_MASK);

	/*
	 * Version 1 hardware supports two basic SPI modes:
	 *  - Standard SPI mode uses 4 pins, with chipselect
	 *  - 3 pin SPI is a 4 pin variant without CS (SPI_NO_CS)
	 *	(distinct from SPI_3WIRE, with just one data wire;
	 *	or similar variants without MOSI or without MISO)
	 *
	 * Version 2 hardware supports an optional handshaking संकेत,
	 * so it can support two more modes:
	 *  - 5 pin SPI variant is standard SPI plus SPI_READY
	 *  - 4 pin with enable is (SPI_READY | SPI_NO_CS)
	 */

	अगर (dspi->version == SPI_VERSION_2) अणु

		u32 delay = 0;

		अगर (spicfg->odd_parity)
			spअगरmt |= SPIFMT_ODD_PARITY_MASK;

		अगर (spicfg->parity_enable)
			spअगरmt |= SPIFMT_PARITYENA_MASK;

		अगर (spicfg->समयr_disable) अणु
			spअगरmt |= SPIFMT_DISTIMER_MASK;
		पूर्ण अन्यथा अणु
			delay |= (spicfg->c2tdelay << SPIDELAY_C2TDELAY_SHIFT)
						& SPIDELAY_C2TDELAY_MASK;
			delay |= (spicfg->t2cdelay << SPIDELAY_T2CDELAY_SHIFT)
						& SPIDELAY_T2CDELAY_MASK;
		पूर्ण

		अगर (spi->mode & SPI_READY) अणु
			spअगरmt |= SPIFMT_WAITENA_MASK;
			delay |= (spicfg->t2edelay << SPIDELAY_T2EDELAY_SHIFT)
						& SPIDELAY_T2EDELAY_MASK;
			delay |= (spicfg->c2edelay << SPIDELAY_C2EDELAY_SHIFT)
						& SPIDELAY_C2EDELAY_MASK;
		पूर्ण

		ioग_लिखो32(delay, dspi->base + SPIDELAY);
	पूर्ण

	ioग_लिखो32(spअगरmt, dspi->base + SPIFMT0);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_spi_of_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा davinci_spi_config *spicfg = spi->controller_data;
	काष्ठा device_node *np = spi->dev.of_node;
	काष्ठा davinci_spi *dspi = spi_master_get_devdata(spi->master);
	u32 prop;

	अगर (spicfg == शून्य && np) अणु
		spicfg = kzalloc(माप(*spicfg), GFP_KERNEL);
		अगर (!spicfg)
			वापस -ENOMEM;
		*spicfg = davinci_spi_शेष_cfg;
		/* override with dt configured values */
		अगर (!of_property_पढ़ो_u32(np, "ti,spi-wdelay", &prop))
			spicfg->wdelay = (u8)prop;
		spi->controller_data = spicfg;

		अगर (dspi->dma_rx && dspi->dma_tx)
			spicfg->io_type = SPI_IO_TYPE_DMA;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * davinci_spi_setup - This functions will set शेष transfer method
 * @spi: spi device on which data transfer to be करोne
 *
 * This functions sets the शेष transfer method.
 */
अटल पूर्णांक davinci_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा davinci_spi *dspi;
	काष्ठा device_node *np = spi->dev.of_node;
	bool पूर्णांकernal_cs = true;

	dspi = spi_master_get_devdata(spi->master);

	अगर (!(spi->mode & SPI_NO_CS)) अणु
		अगर (np && spi->cs_gpiod)
			पूर्णांकernal_cs = false;

		अगर (पूर्णांकernal_cs)
			set_io_bits(dspi->base + SPIPC0, 1 << spi->chip_select);
	पूर्ण

	अगर (spi->mode & SPI_READY)
		set_io_bits(dspi->base + SPIPC0, SPIPC0_SPIENA_MASK);

	अगर (spi->mode & SPI_LOOP)
		set_io_bits(dspi->base + SPIGCR1, SPIGCR1_LOOPBACK_MASK);
	अन्यथा
		clear_io_bits(dspi->base + SPIGCR1, SPIGCR1_LOOPBACK_MASK);

	वापस davinci_spi_of_setup(spi);
पूर्ण

अटल व्योम davinci_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा davinci_spi_config *spicfg = spi->controller_data;

	spi->controller_data = शून्य;
	अगर (spi->dev.of_node)
		kमुक्त(spicfg);
पूर्ण

अटल bool davinci_spi_can_dma(काष्ठा spi_master *master,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer)
अणु
	काष्ठा davinci_spi_config *spicfg = spi->controller_data;
	bool can_dma = false;

	अगर (spicfg)
		can_dma = (spicfg->io_type == SPI_IO_TYPE_DMA) &&
			(xfer->len >= DMA_MIN_BYTES) &&
			!is_vदो_स्मृति_addr(xfer->rx_buf) &&
			!is_vदो_स्मृति_addr(xfer->tx_buf);

	वापस can_dma;
पूर्ण

अटल पूर्णांक davinci_spi_check_error(काष्ठा davinci_spi *dspi, पूर्णांक पूर्णांक_status)
अणु
	काष्ठा device *sdev = dspi->bitbang.master->dev.parent;

	अगर (पूर्णांक_status & SPIFLG_TIMEOUT_MASK) अणु
		dev_err(sdev, "SPI Time-out Error\n");
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (पूर्णांक_status & SPIFLG_DESYNC_MASK) अणु
		dev_err(sdev, "SPI Desynchronization Error\n");
		वापस -EIO;
	पूर्ण
	अगर (पूर्णांक_status & SPIFLG_BITERR_MASK) अणु
		dev_err(sdev, "SPI Bit error\n");
		वापस -EIO;
	पूर्ण

	अगर (dspi->version == SPI_VERSION_2) अणु
		अगर (पूर्णांक_status & SPIFLG_DLEN_ERR_MASK) अणु
			dev_err(sdev, "SPI Data Length Error\n");
			वापस -EIO;
		पूर्ण
		अगर (पूर्णांक_status & SPIFLG_PARERR_MASK) अणु
			dev_err(sdev, "SPI Parity Error\n");
			वापस -EIO;
		पूर्ण
		अगर (पूर्णांक_status & SPIFLG_OVRRUN_MASK) अणु
			dev_err(sdev, "SPI Data Overrun error\n");
			वापस -EIO;
		पूर्ण
		अगर (पूर्णांक_status & SPIFLG_BUF_INIT_ACTIVE_MASK) अणु
			dev_err(sdev, "SPI Buffer Init Active\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * davinci_spi_process_events - check क्रम and handle any SPI controller events
 * @dspi: the controller data
 *
 * This function will check the SPIFLG रेजिस्टर and handle any events that are
 * detected there
 */
अटल पूर्णांक davinci_spi_process_events(काष्ठा davinci_spi *dspi)
अणु
	u32 buf, status, errors = 0, spidat1;

	buf = ioपढ़ो32(dspi->base + SPIBUF);

	अगर (dspi->rcount > 0 && !(buf & SPIBUF_RXEMPTY_MASK)) अणु
		dspi->get_rx(buf & 0xFFFF, dspi);
		dspi->rcount--;
	पूर्ण

	status = ioपढ़ो32(dspi->base + SPIFLG);

	अगर (unlikely(status & SPIFLG_ERROR_MASK)) अणु
		errors = status & SPIFLG_ERROR_MASK;
		जाओ out;
	पूर्ण

	अगर (dspi->wcount > 0 && !(buf & SPIBUF_TXFULL_MASK)) अणु
		spidat1 = ioपढ़ो32(dspi->base + SPIDAT1);
		dspi->wcount--;
		spidat1 &= ~0xFFFF;
		spidat1 |= 0xFFFF & dspi->get_tx(dspi);
		ioग_लिखो32(spidat1, dspi->base + SPIDAT1);
	पूर्ण

out:
	वापस errors;
पूर्ण

अटल व्योम davinci_spi_dma_rx_callback(व्योम *data)
अणु
	काष्ठा davinci_spi *dspi = (काष्ठा davinci_spi *)data;

	dspi->rcount = 0;

	अगर (!dspi->wcount && !dspi->rcount)
		complete(&dspi->करोne);
पूर्ण

अटल व्योम davinci_spi_dma_tx_callback(व्योम *data)
अणु
	काष्ठा davinci_spi *dspi = (काष्ठा davinci_spi *)data;

	dspi->wcount = 0;

	अगर (!dspi->wcount && !dspi->rcount)
		complete(&dspi->करोne);
पूर्ण

/**
 * davinci_spi_bufs - functions which will handle transfer data
 * @spi: spi device on which data transfer to be करोne
 * @t: spi transfer in which transfer info is filled
 *
 * This function will put data to be transferred पूर्णांकo data रेजिस्टर
 * of SPI controller and then रुको until the completion will be marked
 * by the IRQ Handler.
 */
अटल पूर्णांक davinci_spi_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा davinci_spi *dspi;
	पूर्णांक data_type, ret = -ENOMEM;
	u32 tx_data, spidat1;
	u32 errors = 0;
	काष्ठा davinci_spi_config *spicfg;
	काष्ठा davinci_spi_platक्रमm_data *pdata;

	dspi = spi_master_get_devdata(spi->master);
	pdata = &dspi->pdata;
	spicfg = (काष्ठा davinci_spi_config *)spi->controller_data;
	अगर (!spicfg)
		spicfg = &davinci_spi_शेष_cfg;

	/* convert len to words based on bits_per_word */
	data_type = dspi->bytes_per_word[spi->chip_select];

	dspi->tx = t->tx_buf;
	dspi->rx = t->rx_buf;
	dspi->wcount = t->len / data_type;
	dspi->rcount = dspi->wcount;

	spidat1 = ioपढ़ो32(dspi->base + SPIDAT1);

	clear_io_bits(dspi->base + SPIGCR1, SPIGCR1_POWERDOWN_MASK);
	set_io_bits(dspi->base + SPIGCR1, SPIGCR1_SPIENA_MASK);

	reinit_completion(&dspi->करोne);

	अगर (!davinci_spi_can_dma(spi->master, spi, t)) अणु
		अगर (spicfg->io_type != SPI_IO_TYPE_POLL)
			set_io_bits(dspi->base + SPIINT, SPIINT_MASKINT);
		/* start the transfer */
		dspi->wcount--;
		tx_data = dspi->get_tx(dspi);
		spidat1 &= 0xFFFF0000;
		spidat1 |= tx_data & 0xFFFF;
		ioग_लिखो32(spidat1, dspi->base + SPIDAT1);
	पूर्ण अन्यथा अणु
		काष्ठा dma_slave_config dma_rx_conf = अणु
			.direction = DMA_DEV_TO_MEM,
			.src_addr = (अचिन्हित दीर्घ)dspi->pbase + SPIBUF,
			.src_addr_width = data_type,
			.src_maxburst = 1,
		पूर्ण;
		काष्ठा dma_slave_config dma_tx_conf = अणु
			.direction = DMA_MEM_TO_DEV,
			.dst_addr = (अचिन्हित दीर्घ)dspi->pbase + SPIDAT1,
			.dst_addr_width = data_type,
			.dst_maxburst = 1,
		पूर्ण;
		काष्ठा dma_async_tx_descriptor *rxdesc;
		काष्ठा dma_async_tx_descriptor *txdesc;

		dmaengine_slave_config(dspi->dma_rx, &dma_rx_conf);
		dmaengine_slave_config(dspi->dma_tx, &dma_tx_conf);

		rxdesc = dmaengine_prep_slave_sg(dspi->dma_rx,
				t->rx_sg.sgl, t->rx_sg.nents, DMA_DEV_TO_MEM,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!rxdesc)
			जाओ err_desc;

		अगर (!t->tx_buf) अणु
			/* To aव्योम errors when करोing rx-only transfers with
			 * many SG entries (> 20), use the rx buffer as the
			 * dummy tx buffer so that dma reloads are करोne at the
			 * same समय क्रम rx and tx.
			 */
			t->tx_sg.sgl = t->rx_sg.sgl;
			t->tx_sg.nents = t->rx_sg.nents;
		पूर्ण

		txdesc = dmaengine_prep_slave_sg(dspi->dma_tx,
				t->tx_sg.sgl, t->tx_sg.nents, DMA_MEM_TO_DEV,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
		अगर (!txdesc)
			जाओ err_desc;

		rxdesc->callback = davinci_spi_dma_rx_callback;
		rxdesc->callback_param = (व्योम *)dspi;
		txdesc->callback = davinci_spi_dma_tx_callback;
		txdesc->callback_param = (व्योम *)dspi;

		अगर (pdata->cshold_bug)
			ioग_लिखो16(spidat1 >> 16, dspi->base + SPIDAT1 + 2);

		dmaengine_submit(rxdesc);
		dmaengine_submit(txdesc);

		dma_async_issue_pending(dspi->dma_rx);
		dma_async_issue_pending(dspi->dma_tx);

		set_io_bits(dspi->base + SPIINT, SPIINT_DMA_REQ_EN);
	पूर्ण

	/* Wait क्रम the transfer to complete */
	अगर (spicfg->io_type != SPI_IO_TYPE_POLL) अणु
		अगर (रुको_क्रम_completion_समयout(&dspi->करोne, HZ) == 0)
			errors = SPIFLG_TIMEOUT_MASK;
	पूर्ण अन्यथा अणु
		जबतक (dspi->rcount > 0 || dspi->wcount > 0) अणु
			errors = davinci_spi_process_events(dspi);
			अगर (errors)
				अवरोध;
			cpu_relax();
		पूर्ण
	पूर्ण

	clear_io_bits(dspi->base + SPIINT, SPIINT_MASKALL);
	अगर (davinci_spi_can_dma(spi->master, spi, t))
		clear_io_bits(dspi->base + SPIINT, SPIINT_DMA_REQ_EN);

	clear_io_bits(dspi->base + SPIGCR1, SPIGCR1_SPIENA_MASK);
	set_io_bits(dspi->base + SPIGCR1, SPIGCR1_POWERDOWN_MASK);

	/*
	 * Check क्रम bit error, desync error,parity error,समयout error and
	 * receive overflow errors
	 */
	अगर (errors) अणु
		ret = davinci_spi_check_error(dspi, errors);
		WARN(!ret, "%s: error reported but no error found!\n",
							dev_name(&spi->dev));
		वापस ret;
	पूर्ण

	अगर (dspi->rcount != 0 || dspi->wcount != 0) अणु
		dev_err(&spi->dev, "SPI data transfer error\n");
		वापस -EIO;
	पूर्ण

	वापस t->len;

err_desc:
	वापस ret;
पूर्ण

/**
 * dummy_thपढ़ो_fn - dummy thपढ़ो function
 * @irq: IRQ number क्रम this SPI Master
 * @data: काष्ठाure क्रम SPI Master controller davinci_spi
 *
 * This is to satisfy the request_thपढ़ोed_irq() API so that the irq
 * handler is called in पूर्णांकerrupt context.
 */
अटल irqवापस_t dummy_thपढ़ो_fn(s32 irq, व्योम *data)
अणु
	वापस IRQ_HANDLED;
पूर्ण

/**
 * davinci_spi_irq - Interrupt handler क्रम SPI Master Controller
 * @irq: IRQ number क्रम this SPI Master
 * @data: काष्ठाure क्रम SPI Master controller davinci_spi
 *
 * ISR will determine that पूर्णांकerrupt arrives either क्रम READ or WRITE command.
 * According to command it will करो the appropriate action. It will check
 * transfer length and अगर it is not zero then dispatch transfer command again.
 * If transfer length is zero then it will indicate the COMPLETION so that
 * davinci_spi_bufs function can go ahead.
 */
अटल irqवापस_t davinci_spi_irq(s32 irq, व्योम *data)
अणु
	काष्ठा davinci_spi *dspi = data;
	पूर्णांक status;

	status = davinci_spi_process_events(dspi);
	अगर (unlikely(status != 0))
		clear_io_bits(dspi->base + SPIINT, SPIINT_MASKINT);

	अगर ((!dspi->rcount && !dspi->wcount) || status)
		complete(&dspi->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक davinci_spi_request_dma(काष्ठा davinci_spi *dspi)
अणु
	काष्ठा device *sdev = dspi->bitbang.master->dev.parent;

	dspi->dma_rx = dma_request_chan(sdev, "rx");
	अगर (IS_ERR(dspi->dma_rx))
		वापस PTR_ERR(dspi->dma_rx);

	dspi->dma_tx = dma_request_chan(sdev, "tx");
	अगर (IS_ERR(dspi->dma_tx)) अणु
		dma_release_channel(dspi->dma_rx);
		वापस PTR_ERR(dspi->dma_tx);
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)

/* OF SPI data काष्ठाure */
काष्ठा davinci_spi_of_data अणु
	u8	version;
	u8	prescaler_limit;
पूर्ण;

अटल स्थिर काष्ठा davinci_spi_of_data dm6441_spi_data = अणु
	.version = SPI_VERSION_1,
	.prescaler_limit = 2,
पूर्ण;

अटल स्थिर काष्ठा davinci_spi_of_data da830_spi_data = अणु
	.version = SPI_VERSION_2,
	.prescaler_limit = 2,
पूर्ण;

अटल स्थिर काष्ठा davinci_spi_of_data keystone_spi_data = अणु
	.version = SPI_VERSION_1,
	.prescaler_limit = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id davinci_spi_of_match[] = अणु
	अणु
		.compatible = "ti,dm6441-spi",
		.data = &dm6441_spi_data,
	पूर्ण,
	अणु
		.compatible = "ti,da830-spi",
		.data = &da830_spi_data,
	पूर्ण,
	अणु
		.compatible = "ti,keystone-spi",
		.data = &keystone_spi_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_spi_of_match);

/**
 * spi_davinci_get_pdata - Get platक्रमm data from DTS binding
 * @pdev: ptr to platक्रमm data
 * @dspi: ptr to driver data
 *
 * Parses and populates pdata in dspi from device tree bindings.
 *
 * NOTE: Not all platक्रमm data params are supported currently.
 */
अटल पूर्णांक spi_davinci_get_pdata(काष्ठा platक्रमm_device *pdev,
			काष्ठा davinci_spi *dspi)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा davinci_spi_of_data *spi_data;
	काष्ठा davinci_spi_platक्रमm_data *pdata;
	अचिन्हित पूर्णांक num_cs, पूर्णांकr_line = 0;

	pdata = &dspi->pdata;

	spi_data = device_get_match_data(&pdev->dev);

	pdata->version = spi_data->version;
	pdata->prescaler_limit = spi_data->prescaler_limit;
	/*
	 * शेष num_cs is 1 and all chipsel are पूर्णांकernal to the chip
	 * indicated by chip_sel being शून्य or cs_gpios being शून्य or
	 * set to -ENOENT. num-cs includes पूर्णांकernal as well as gpios.
	 * indicated by chip_sel being शून्य. GPIO based CS is not
	 * supported yet in DT bindings.
	 */
	num_cs = 1;
	of_property_पढ़ो_u32(node, "num-cs", &num_cs);
	pdata->num_chipselect = num_cs;
	of_property_पढ़ो_u32(node, "ti,davinci-spi-intr-line", &पूर्णांकr_line);
	pdata->पूर्णांकr_line = पूर्णांकr_line;
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक spi_davinci_get_pdata(काष्ठा platक्रमm_device *pdev,
			काष्ठा davinci_spi *dspi)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/**
 * davinci_spi_probe - probe function क्रम SPI Master Controller
 * @pdev: platक्रमm_device काष्ठाure which contains plateक्रमm specअगरic data
 *
 * According to Linux Device Model this function will be invoked by Linux
 * with platक्रमm_device काष्ठा which contains the device specअगरic info.
 * This function will map the SPI controller's memory, रेजिस्टर IRQ,
 * Reset SPI controller and setting its रेजिस्टरs to शेष value.
 * It will invoke spi_bitbang_start to create work queue so that client driver
 * can रेजिस्टर transfer method to work queue.
 */
अटल पूर्णांक davinci_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा davinci_spi *dspi;
	काष्ठा davinci_spi_platक्रमm_data *pdata;
	काष्ठा resource *r;
	पूर्णांक ret = 0;
	u32 spipc0;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा davinci_spi));
	अगर (master == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, master);

	dspi = spi_master_get_devdata(master);

	अगर (dev_get_platdata(&pdev->dev)) अणु
		pdata = dev_get_platdata(&pdev->dev);
		dspi->pdata = *pdata;
	पूर्ण अन्यथा अणु
		/* update dspi pdata with that from the DT */
		ret = spi_davinci_get_pdata(pdev, dspi);
		अगर (ret < 0)
			जाओ मुक्त_master;
	पूर्ण

	/* pdata in dspi is now updated and poपूर्णांक pdata to that */
	pdata = &dspi->pdata;

	dspi->bytes_per_word = devm_kसुस्मृति(&pdev->dev,
					    pdata->num_chipselect,
					    माप(*dspi->bytes_per_word),
					    GFP_KERNEL);
	अगर (dspi->bytes_per_word == शून्य) अणु
		ret = -ENOMEM;
		जाओ मुक्त_master;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (r == शून्य) अणु
		ret = -ENOENT;
		जाओ मुक्त_master;
	पूर्ण

	dspi->pbase = r->start;

	dspi->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(dspi->base)) अणु
		ret = PTR_ERR(dspi->base);
		जाओ मुक्त_master;
	पूर्ण

	init_completion(&dspi->करोne);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret == 0)
		ret = -EINVAL;
	अगर (ret < 0)
		जाओ मुक्त_master;
	dspi->irq = ret;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, dspi->irq, davinci_spi_irq,
				dummy_thपढ़ो_fn, 0, dev_name(&pdev->dev), dspi);
	अगर (ret)
		जाओ मुक्त_master;

	dspi->bitbang.master = master;

	dspi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dspi->clk)) अणु
		ret = -ENODEV;
		जाओ मुक्त_master;
	पूर्ण
	ret = clk_prepare_enable(dspi->clk);
	अगर (ret)
		जाओ मुक्त_master;

	master->use_gpio_descriptors = true;
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;
	master->num_chipselect = pdata->num_chipselect;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(2, 16);
	master->flags = SPI_MASTER_MUST_RX;
	master->setup = davinci_spi_setup;
	master->cleanup = davinci_spi_cleanup;
	master->can_dma = davinci_spi_can_dma;

	dspi->bitbang.chipselect = davinci_spi_chipselect;
	dspi->bitbang.setup_transfer = davinci_spi_setup_transfer;
	dspi->prescaler_limit = pdata->prescaler_limit;
	dspi->version = pdata->version;

	dspi->bitbang.flags = SPI_NO_CS | SPI_LSB_FIRST | SPI_LOOP | SPI_CS_WORD;
	अगर (dspi->version == SPI_VERSION_2)
		dspi->bitbang.flags |= SPI_READY;

	dspi->bitbang.txrx_bufs = davinci_spi_bufs;

	ret = davinci_spi_request_dma(dspi);
	अगर (ret == -EPROBE_DEFER) अणु
		जाओ मुक्त_clk;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_info(&pdev->dev, "DMA is not supported (%d)\n", ret);
		dspi->dma_rx = शून्य;
		dspi->dma_tx = शून्य;
	पूर्ण

	dspi->get_rx = davinci_spi_rx_buf_u8;
	dspi->get_tx = davinci_spi_tx_buf_u8;

	/* Reset In/OUT SPI module */
	ioग_लिखो32(0, dspi->base + SPIGCR0);
	udelay(100);
	ioग_लिखो32(1, dspi->base + SPIGCR0);

	/* Set up SPIPC0.  CS and ENA init is करोne in davinci_spi_setup */
	spipc0 = SPIPC0_DIFUN_MASK | SPIPC0_DOFUN_MASK | SPIPC0_CLKFUN_MASK;
	ioग_लिखो32(spipc0, dspi->base + SPIPC0);

	अगर (pdata->पूर्णांकr_line)
		ioग_लिखो32(SPI_INTLVL_1, dspi->base + SPILVL);
	अन्यथा
		ioग_लिखो32(SPI_INTLVL_0, dspi->base + SPILVL);

	ioग_लिखो32(CS_DEFAULT, dspi->base + SPIDEF);

	/* master mode शेष */
	set_io_bits(dspi->base + SPIGCR1, SPIGCR1_CLKMOD_MASK);
	set_io_bits(dspi->base + SPIGCR1, SPIGCR1_MASTER_MASK);
	set_io_bits(dspi->base + SPIGCR1, SPIGCR1_POWERDOWN_MASK);

	ret = spi_bitbang_start(&dspi->bitbang);
	अगर (ret)
		जाओ मुक्त_dma;

	dev_info(&pdev->dev, "Controller at 0x%p\n", dspi->base);

	वापस ret;

मुक्त_dma:
	अगर (dspi->dma_rx) अणु
		dma_release_channel(dspi->dma_rx);
		dma_release_channel(dspi->dma_tx);
	पूर्ण
मुक्त_clk:
	clk_disable_unprepare(dspi->clk);
मुक्त_master:
	spi_master_put(master);
err:
	वापस ret;
पूर्ण

/**
 * davinci_spi_हटाओ - हटाओ function क्रम SPI Master Controller
 * @pdev: platक्रमm_device काष्ठाure which contains plateक्रमm specअगरic data
 *
 * This function will करो the reverse action of davinci_spi_probe function
 * It will मुक्त the IRQ and SPI controller's memory region.
 * It will also call spi_bitbang_stop to destroy the work queue which was
 * created by spi_bitbang_start.
 */
अटल पूर्णांक davinci_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_spi *dspi;
	काष्ठा spi_master *master;

	master = platक्रमm_get_drvdata(pdev);
	dspi = spi_master_get_devdata(master);

	spi_bitbang_stop(&dspi->bitbang);

	clk_disable_unprepare(dspi->clk);

	अगर (dspi->dma_rx) अणु
		dma_release_channel(dspi->dma_rx);
		dma_release_channel(dspi->dma_tx);
	पूर्ण

	spi_master_put(master);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_spi_driver = अणु
	.driver = अणु
		.name = "spi_davinci",
		.of_match_table = of_match_ptr(davinci_spi_of_match),
	पूर्ण,
	.probe = davinci_spi_probe,
	.हटाओ = davinci_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(davinci_spi_driver);

MODULE_DESCRIPTION("TI DaVinci SPI Master Controller Driver");
MODULE_LICENSE("GPL");
