<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell Orion SPI controller driver
 *
 * Author: Shadi Ammouri <shadi@marvell.com>
 * Copyright (C) 2007-2008 Marvell Ltd.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/sizes.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा DRIVER_NAME			"orion_spi"

/* Runसमय PM स्वतःsuspend समयout: PM is fairly light on this driver */
#घोषणा SPI_AUTOSUSPEND_TIMEOUT		200

/* Some SoCs using this driver support up to 8 chip selects.
 * It is up to the implementer to only use the chip selects
 * that are available.
 */
#घोषणा ORION_NUM_CHIPSELECTS		8

#घोषणा ORION_SPI_WAIT_RDY_MAX_LOOP	2000 /* in usec */

#घोषणा ORION_SPI_IF_CTRL_REG		0x00
#घोषणा ORION_SPI_IF_CONFIG_REG		0x04
#घोषणा ORION_SPI_IF_RXLSBF		BIT(14)
#घोषणा ORION_SPI_IF_TXLSBF		BIT(13)
#घोषणा ORION_SPI_DATA_OUT_REG		0x08
#घोषणा ORION_SPI_DATA_IN_REG		0x0c
#घोषणा ORION_SPI_INT_CAUSE_REG		0x10
#घोषणा ORION_SPI_TIMING_PARAMS_REG	0x18

/* Register क्रम the "Direct Mode" */
#घोषणा SPI_सूचीECT_WRITE_CONFIG_REG	0x20

#घोषणा ORION_SPI_TMISO_SAMPLE_MASK	(0x3 << 6)
#घोषणा ORION_SPI_TMISO_SAMPLE_1	(1 << 6)
#घोषणा ORION_SPI_TMISO_SAMPLE_2	(2 << 6)

#घोषणा ORION_SPI_MODE_CPOL		(1 << 11)
#घोषणा ORION_SPI_MODE_CPHA		(1 << 12)
#घोषणा ORION_SPI_IF_8_16_BIT_MODE	(1 << 5)
#घोषणा ORION_SPI_CLK_PRESCALE_MASK	0x1F
#घोषणा ARMADA_SPI_CLK_PRESCALE_MASK	0xDF
#घोषणा ORION_SPI_MODE_MASK		(ORION_SPI_MODE_CPOL | \
					 ORION_SPI_MODE_CPHA)
#घोषणा ORION_SPI_CS_MASK	0x1C
#घोषणा ORION_SPI_CS_SHIFT	2
#घोषणा ORION_SPI_CS(cs)	((cs << ORION_SPI_CS_SHIFT) & \
					ORION_SPI_CS_MASK)

क्रमागत orion_spi_type अणु
	ORION_SPI,
	ARMADA_SPI,
पूर्ण;

काष्ठा orion_spi_dev अणु
	क्रमागत orion_spi_type	typ;
	/*
	 * min_भागisor and max_hz should be exclusive, the only we can
	 * have both is क्रम managing the armada-370-spi हाल with old
	 * device tree
	 */
	अचिन्हित दीर्घ		max_hz;
	अचिन्हित पूर्णांक		min_भागisor;
	अचिन्हित पूर्णांक		max_भागisor;
	u32			prescale_mask;
	bool			is_errata_50mhz_ac;
पूर्ण;

काष्ठा orion_direct_acc अणु
	व्योम __iomem		*vaddr;
	u32			size;
पूर्ण;

काष्ठा orion_child_options अणु
	काष्ठा orion_direct_acc direct_access;
पूर्ण;

काष्ठा orion_spi अणु
	काष्ठा spi_master	*master;
	व्योम __iomem		*base;
	काष्ठा clk              *clk;
	काष्ठा clk              *axi_clk;
	स्थिर काष्ठा orion_spi_dev *devdata;
	काष्ठा device		*dev;

	काष्ठा orion_child_options	child[ORION_NUM_CHIPSELECTS];
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक orion_spi_runसमय_suspend(काष्ठा device *dev);
अटल पूर्णांक orion_spi_runसमय_resume(काष्ठा device *dev);
#पूर्ण_अगर

अटल अंतरभूत व्योम __iomem *spi_reg(काष्ठा orion_spi *orion_spi, u32 reg)
अणु
	वापस orion_spi->base + reg;
पूर्ण

अटल अंतरभूत व्योम
orion_spi_setbits(काष्ठा orion_spi *orion_spi, u32 reg, u32 mask)
अणु
	व्योम __iomem *reg_addr = spi_reg(orion_spi, reg);
	u32 val;

	val = पढ़ोl(reg_addr);
	val |= mask;
	ग_लिखोl(val, reg_addr);
पूर्ण

अटल अंतरभूत व्योम
orion_spi_clrbits(काष्ठा orion_spi *orion_spi, u32 reg, u32 mask)
अणु
	व्योम __iomem *reg_addr = spi_reg(orion_spi, reg);
	u32 val;

	val = पढ़ोl(reg_addr);
	val &= ~mask;
	ग_लिखोl(val, reg_addr);
पूर्ण

अटल पूर्णांक orion_spi_baudrate_set(काष्ठा spi_device *spi, अचिन्हित पूर्णांक speed)
अणु
	u32 tclk_hz;
	u32 rate;
	u32 prescale;
	u32 reg;
	काष्ठा orion_spi *orion_spi;
	स्थिर काष्ठा orion_spi_dev *devdata;

	orion_spi = spi_master_get_devdata(spi->master);
	devdata = orion_spi->devdata;

	tclk_hz = clk_get_rate(orion_spi->clk);

	अगर (devdata->typ == ARMADA_SPI) अणु
		/*
		 * Given the core_clk (tclk_hz) and the target rate (speed) we
		 * determine the best values क्रम SPR (in [0 .. 15]) and SPPR (in
		 * [0..7]) such that
		 *
		 * 	core_clk / (SPR * 2 ** SPPR)
		 *
		 * is as big as possible but not bigger than speed.
		 */

		/* best पूर्णांकeger भागider: */
		अचिन्हित भागider = DIV_ROUND_UP(tclk_hz, speed);
		अचिन्हित spr, sppr;

		अगर (भागider < 16) अणु
			/* This is the easy हाल, भागider is less than 16 */
			spr = भागider;
			sppr = 0;

		पूर्ण अन्यथा अणु
			अचिन्हित two_घात_sppr;
			/*
			 * Find the highest bit set in भागider. This and the
			 * three next bits define SPR (apart from rounding).
			 * SPPR is then the number of zero bits that must be
			 * appended:
			 */
			sppr = fls(भागider) - 4;

			/*
			 * As SPR only has 4 bits, we have to round भागider up
			 * to the next multiple of 2 ** sppr.
			 */
			two_घात_sppr = 1 << sppr;
			भागider = (भागider + two_घात_sppr - 1) & -two_घात_sppr;

			/*
			 * recalculate sppr as rounding up भागider might have
			 * increased it enough to change the position of the
			 * highest set bit. In this हाल the bit that now
			 * करोesn't make it पूर्णांकo SPR is 0, so there is no need to
			 * round again.
			 */
			sppr = fls(भागider) - 4;
			spr = भागider >> sppr;

			/*
			 * Now करो range checking. SPR is स्थिरructed to have a
			 * width of 4 bits, so this is fine क्रम sure. So we
			 * still need to check क्रम sppr to fit पूर्णांकo 3 bits:
			 */
			अगर (sppr > 7)
				वापस -EINVAL;
		पूर्ण

		prescale = ((sppr & 0x6) << 5) | ((sppr & 0x1) << 4) | spr;
	पूर्ण अन्यथा अणु
		/*
		 * the supported rates are: 4,6,8...30
		 * round up as we look क्रम equal or less speed
		 */
		rate = DIV_ROUND_UP(tclk_hz, speed);
		rate = roundup(rate, 2);

		/* check अगर requested speed is too small */
		अगर (rate > 30)
			वापस -EINVAL;

		अगर (rate < 4)
			rate = 4;

		/* Convert the rate to SPI घड़ी भागisor value.	*/
		prescale = 0x10 + rate/2;
	पूर्ण

	reg = पढ़ोl(spi_reg(orion_spi, ORION_SPI_IF_CONFIG_REG));
	reg = ((reg & ~devdata->prescale_mask) | prescale);
	ग_लिखोl(reg, spi_reg(orion_spi, ORION_SPI_IF_CONFIG_REG));

	वापस 0;
पूर्ण

अटल व्योम
orion_spi_mode_set(काष्ठा spi_device *spi)
अणु
	u32 reg;
	काष्ठा orion_spi *orion_spi;

	orion_spi = spi_master_get_devdata(spi->master);

	reg = पढ़ोl(spi_reg(orion_spi, ORION_SPI_IF_CONFIG_REG));
	reg &= ~ORION_SPI_MODE_MASK;
	अगर (spi->mode & SPI_CPOL)
		reg |= ORION_SPI_MODE_CPOL;
	अगर (spi->mode & SPI_CPHA)
		reg |= ORION_SPI_MODE_CPHA;
	अगर (spi->mode & SPI_LSB_FIRST)
		reg |= ORION_SPI_IF_RXLSBF | ORION_SPI_IF_TXLSBF;
	अन्यथा
		reg &= ~(ORION_SPI_IF_RXLSBF | ORION_SPI_IF_TXLSBF);

	ग_लिखोl(reg, spi_reg(orion_spi, ORION_SPI_IF_CONFIG_REG));
पूर्ण

अटल व्योम
orion_spi_50mhz_ac_timing_erratum(काष्ठा spi_device *spi, अचिन्हित पूर्णांक speed)
अणु
	u32 reg;
	काष्ठा orion_spi *orion_spi;

	orion_spi = spi_master_get_devdata(spi->master);

	/*
	 * Erratum description: (Erratum NO. FE-9144572) The device
	 * SPI पूर्णांकerface supports frequencies of up to 50 MHz.
	 * However, due to this erratum, when the device core घड़ी is
	 * 250 MHz and the SPI पूर्णांकerfaces is configured क्रम 50MHz SPI
	 * घड़ी and CPOL=CPHA=1 there might occur data corruption on
	 * पढ़ोs from the SPI device.
	 * Erratum Workaround:
	 * Work in one of the following configurations:
	 * 1. Set CPOL=CPHA=0 in "SPI Interface Configuration
	 * Register".
	 * 2. Set TMISO_SAMPLE value to 0x2 in "SPI Timing Parameters 1
	 * Register" beक्रमe setting the पूर्णांकerface.
	 */
	reg = पढ़ोl(spi_reg(orion_spi, ORION_SPI_TIMING_PARAMS_REG));
	reg &= ~ORION_SPI_TMISO_SAMPLE_MASK;

	अगर (clk_get_rate(orion_spi->clk) == 250000000 &&
			speed == 50000000 && spi->mode & SPI_CPOL &&
			spi->mode & SPI_CPHA)
		reg |= ORION_SPI_TMISO_SAMPLE_2;
	अन्यथा
		reg |= ORION_SPI_TMISO_SAMPLE_1; /* This is the शेष value */

	ग_लिखोl(reg, spi_reg(orion_spi, ORION_SPI_TIMING_PARAMS_REG));
पूर्ण

/*
 * called only when no transfer is active on the bus
 */
अटल पूर्णांक
orion_spi_setup_transfer(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा orion_spi *orion_spi;
	अचिन्हित पूर्णांक speed = spi->max_speed_hz;
	अचिन्हित पूर्णांक bits_per_word = spi->bits_per_word;
	पूर्णांक	rc;

	orion_spi = spi_master_get_devdata(spi->master);

	अगर ((t != शून्य) && t->speed_hz)
		speed = t->speed_hz;

	अगर ((t != शून्य) && t->bits_per_word)
		bits_per_word = t->bits_per_word;

	orion_spi_mode_set(spi);

	अगर (orion_spi->devdata->is_errata_50mhz_ac)
		orion_spi_50mhz_ac_timing_erratum(spi, speed);

	rc = orion_spi_baudrate_set(spi, speed);
	अगर (rc)
		वापस rc;

	अगर (bits_per_word == 16)
		orion_spi_setbits(orion_spi, ORION_SPI_IF_CONFIG_REG,
				  ORION_SPI_IF_8_16_BIT_MODE);
	अन्यथा
		orion_spi_clrbits(orion_spi, ORION_SPI_IF_CONFIG_REG,
				  ORION_SPI_IF_8_16_BIT_MODE);

	वापस 0;
पूर्ण

अटल व्योम orion_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा orion_spi *orion_spi;

	orion_spi = spi_master_get_devdata(spi->master);

	/*
	 * If this line is using a GPIO to control chip select, this पूर्णांकernal
	 * .set_cs() function will still be called, so we clear any previous
	 * chip select. The CS we activate will not have any elecrical effect,
	 * as it is handled by a GPIO, but that करोesn't matter. What we need
	 * is to deनिश्चित the old chip select and निश्चित some other chip select.
	 */
	orion_spi_clrbits(orion_spi, ORION_SPI_IF_CTRL_REG, ORION_SPI_CS_MASK);
	orion_spi_setbits(orion_spi, ORION_SPI_IF_CTRL_REG,
			  ORION_SPI_CS(spi->chip_select));

	/*
	 * Chip select logic is inverted from spi_set_cs(). For lines using a
	 * GPIO to करो chip select SPI_CS_HIGH is enक्रमced and inversion happens
	 * in the GPIO library, but we करोn't care about that, because in those
	 * हालs we are dealing with an unused native CS anyways so the polarity
	 * करोesn't matter.
	 */
	अगर (!enable)
		orion_spi_setbits(orion_spi, ORION_SPI_IF_CTRL_REG, 0x1);
	अन्यथा
		orion_spi_clrbits(orion_spi, ORION_SPI_IF_CTRL_REG, 0x1);
पूर्ण

अटल अंतरभूत पूर्णांक orion_spi_रुको_till_पढ़ोy(काष्ठा orion_spi *orion_spi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ORION_SPI_WAIT_RDY_MAX_LOOP; i++) अणु
		अगर (पढ़ोl(spi_reg(orion_spi, ORION_SPI_INT_CAUSE_REG)))
			वापस 1;

		udelay(1);
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक
orion_spi_ग_लिखो_पढ़ो_8bit(काष्ठा spi_device *spi,
			  स्थिर u8 **tx_buf, u8 **rx_buf)
अणु
	व्योम __iomem *tx_reg, *rx_reg, *पूर्णांक_reg;
	काष्ठा orion_spi *orion_spi;
	bool cs_single_byte;

	cs_single_byte = spi->mode & SPI_CS_WORD;

	orion_spi = spi_master_get_devdata(spi->master);

	अगर (cs_single_byte)
		orion_spi_set_cs(spi, 0);

	tx_reg = spi_reg(orion_spi, ORION_SPI_DATA_OUT_REG);
	rx_reg = spi_reg(orion_spi, ORION_SPI_DATA_IN_REG);
	पूर्णांक_reg = spi_reg(orion_spi, ORION_SPI_INT_CAUSE_REG);

	/* clear the पूर्णांकerrupt cause रेजिस्टर */
	ग_लिखोl(0x0, पूर्णांक_reg);

	अगर (tx_buf && *tx_buf)
		ग_लिखोl(*(*tx_buf)++, tx_reg);
	अन्यथा
		ग_लिखोl(0, tx_reg);

	अगर (orion_spi_रुको_till_पढ़ोy(orion_spi) < 0) अणु
		अगर (cs_single_byte) अणु
			orion_spi_set_cs(spi, 1);
			/* Satisfy some SLIC devices requirements */
			udelay(4);
		पूर्ण
		dev_err(&spi->dev, "TXS timed out\n");
		वापस -1;
	पूर्ण

	अगर (rx_buf && *rx_buf)
		*(*rx_buf)++ = पढ़ोl(rx_reg);

	अगर (cs_single_byte) अणु
		orion_spi_set_cs(spi, 1);
		/* Satisfy some SLIC devices requirements */
		udelay(4);
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक
orion_spi_ग_लिखो_पढ़ो_16bit(काष्ठा spi_device *spi,
			   स्थिर u16 **tx_buf, u16 **rx_buf)
अणु
	व्योम __iomem *tx_reg, *rx_reg, *पूर्णांक_reg;
	काष्ठा orion_spi *orion_spi;

	अगर (spi->mode & SPI_CS_WORD) अणु
		dev_err(&spi->dev, "SPI_CS_WORD is only supported for 8 bit words\n");
		वापस -1;
	पूर्ण

	orion_spi = spi_master_get_devdata(spi->master);
	tx_reg = spi_reg(orion_spi, ORION_SPI_DATA_OUT_REG);
	rx_reg = spi_reg(orion_spi, ORION_SPI_DATA_IN_REG);
	पूर्णांक_reg = spi_reg(orion_spi, ORION_SPI_INT_CAUSE_REG);

	/* clear the पूर्णांकerrupt cause रेजिस्टर */
	ग_लिखोl(0x0, पूर्णांक_reg);

	अगर (tx_buf && *tx_buf)
		ग_लिखोl(__cpu_to_le16(get_unaligned((*tx_buf)++)), tx_reg);
	अन्यथा
		ग_लिखोl(0, tx_reg);

	अगर (orion_spi_रुको_till_पढ़ोy(orion_spi) < 0) अणु
		dev_err(&spi->dev, "TXS timed out\n");
		वापस -1;
	पूर्ण

	अगर (rx_buf && *rx_buf)
		put_unaligned(__le16_to_cpu(पढ़ोl(rx_reg)), (*rx_buf)++);

	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक
orion_spi_ग_लिखो_पढ़ो(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	अचिन्हित पूर्णांक count;
	पूर्णांक word_len;
	काष्ठा orion_spi *orion_spi;
	पूर्णांक cs = spi->chip_select;
	व्योम __iomem *vaddr;

	word_len = spi->bits_per_word;
	count = xfer->len;

	orion_spi = spi_master_get_devdata(spi->master);

	/*
	 * Use SPI direct ग_लिखो mode अगर base address is available
	 * and SPI_CS_WORD flag is not set.
	 * Otherwise fall back to PIO mode क्रम this transfer.
	 */
	vaddr = orion_spi->child[cs].direct_access.vaddr;

	अगर (vaddr && xfer->tx_buf && word_len == 8 && (spi->mode & SPI_CS_WORD) == 0) अणु
		अचिन्हित पूर्णांक cnt = count / 4;
		अचिन्हित पूर्णांक rem = count % 4;

		/*
		 * Send the TX-data to the SPI device via the direct
		 * mapped address winकरोw
		 */
		ioग_लिखो32_rep(vaddr, xfer->tx_buf, cnt);
		अगर (rem) अणु
			u32 *buf = (u32 *)xfer->tx_buf;

			ioग_लिखो8_rep(vaddr, &buf[cnt], rem);
		पूर्ण

		वापस count;
	पूर्ण

	अगर (word_len == 8) अणु
		स्थिर u8 *tx = xfer->tx_buf;
		u8 *rx = xfer->rx_buf;

		करो अणु
			अगर (orion_spi_ग_लिखो_पढ़ो_8bit(spi, &tx, &rx) < 0)
				जाओ out;
			count--;
			spi_delay_exec(&xfer->word_delay, xfer);
		पूर्ण जबतक (count);
	पूर्ण अन्यथा अगर (word_len == 16) अणु
		स्थिर u16 *tx = xfer->tx_buf;
		u16 *rx = xfer->rx_buf;

		करो अणु
			अगर (orion_spi_ग_लिखो_पढ़ो_16bit(spi, &tx, &rx) < 0)
				जाओ out;
			count -= 2;
			spi_delay_exec(&xfer->word_delay, xfer);
		पूर्ण जबतक (count);
	पूर्ण

out:
	वापस xfer->len - count;
पूर्ण

अटल पूर्णांक orion_spi_transfer_one(काष्ठा spi_master *master,
					काष्ठा spi_device *spi,
					काष्ठा spi_transfer *t)
अणु
	पूर्णांक status = 0;

	status = orion_spi_setup_transfer(spi, t);
	अगर (status < 0)
		वापस status;

	अगर (t->len)
		orion_spi_ग_लिखो_पढ़ो(spi, t);

	वापस status;
पूर्ण

अटल पूर्णांक orion_spi_setup(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
#अगर_घोषित CONFIG_PM
	काष्ठा orion_spi *orion_spi = spi_master_get_devdata(spi->master);
	काष्ठा device *dev = orion_spi->dev;

	orion_spi_runसमय_resume(dev);
#पूर्ण_अगर

	ret = orion_spi_setup_transfer(spi, शून्य);

#अगर_घोषित CONFIG_PM
	orion_spi_runसमय_suspend(dev);
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक orion_spi_reset(काष्ठा orion_spi *orion_spi)
अणु
	/* Verअगरy that the CS is deनिश्चितed */
	orion_spi_clrbits(orion_spi, ORION_SPI_IF_CTRL_REG, 0x1);

	/* Don't deनिश्चित CS between the direct mapped SPI transfers */
	ग_लिखोl(0, spi_reg(orion_spi, SPI_सूचीECT_WRITE_CONFIG_REG));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा orion_spi_dev orion_spi_dev_data = अणु
	.typ = ORION_SPI,
	.min_भागisor = 4,
	.max_भागisor = 30,
	.prescale_mask = ORION_SPI_CLK_PRESCALE_MASK,
पूर्ण;

अटल स्थिर काष्ठा orion_spi_dev armada_370_spi_dev_data = अणु
	.typ = ARMADA_SPI,
	.min_भागisor = 4,
	.max_भागisor = 1920,
	.max_hz = 50000000,
	.prescale_mask = ARMADA_SPI_CLK_PRESCALE_MASK,
पूर्ण;

अटल स्थिर काष्ठा orion_spi_dev armada_xp_spi_dev_data = अणु
	.typ = ARMADA_SPI,
	.max_hz = 50000000,
	.max_भागisor = 1920,
	.prescale_mask = ARMADA_SPI_CLK_PRESCALE_MASK,
पूर्ण;

अटल स्थिर काष्ठा orion_spi_dev armada_375_spi_dev_data = अणु
	.typ = ARMADA_SPI,
	.min_भागisor = 15,
	.max_भागisor = 1920,
	.prescale_mask = ARMADA_SPI_CLK_PRESCALE_MASK,
पूर्ण;

अटल स्थिर काष्ठा orion_spi_dev armada_380_spi_dev_data = अणु
	.typ = ARMADA_SPI,
	.max_hz = 50000000,
	.max_भागisor = 1920,
	.prescale_mask = ARMADA_SPI_CLK_PRESCALE_MASK,
	.is_errata_50mhz_ac = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id orion_spi_of_match_table[] = अणु
	अणु
		.compatible = "marvell,orion-spi",
		.data = &orion_spi_dev_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-370-spi",
		.data = &armada_370_spi_dev_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-375-spi",
		.data = &armada_375_spi_dev_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-380-spi",
		.data = &armada_380_spi_dev_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-390-spi",
		.data = &armada_xp_spi_dev_data,
	पूर्ण,
	अणु
		.compatible = "marvell,armada-xp-spi",
		.data = &armada_xp_spi_dev_data,
	पूर्ण,

	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, orion_spi_of_match_table);

अटल पूर्णांक orion_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा orion_spi_dev *devdata;
	काष्ठा spi_master *master;
	काष्ठा orion_spi *spi;
	काष्ठा resource *r;
	अचिन्हित दीर्घ tclk_hz;
	पूर्णांक status = 0;
	काष्ठा device_node *np;

	master = spi_alloc_master(&pdev->dev, माप(*spi));
	अगर (master == शून्य) अणु
		dev_dbg(&pdev->dev, "master allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (pdev->id != -1)
		master->bus_num = pdev->id;
	अगर (pdev->dev.of_node) अणु
		u32 cell_index;

		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "cell-index",
					  &cell_index))
			master->bus_num = cell_index;
	पूर्ण

	/* we support all 4 SPI modes and LSB first option */
	master->mode_bits = SPI_CPHA | SPI_CPOL | SPI_LSB_FIRST | SPI_CS_WORD;
	master->set_cs = orion_spi_set_cs;
	master->transfer_one = orion_spi_transfer_one;
	master->num_chipselect = ORION_NUM_CHIPSELECTS;
	master->setup = orion_spi_setup;
	master->bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	master->स्वतः_runसमय_pm = true;
	master->use_gpio_descriptors = true;
	master->flags = SPI_MASTER_GPIO_SS;

	platक्रमm_set_drvdata(pdev, master);

	spi = spi_master_get_devdata(master);
	spi->master = master;
	spi->dev = &pdev->dev;

	devdata = device_get_match_data(&pdev->dev);
	devdata = devdata ? devdata : &orion_spi_dev_data;
	spi->devdata = devdata;

	spi->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(spi->clk)) अणु
		status = PTR_ERR(spi->clk);
		जाओ out;
	पूर्ण

	status = clk_prepare_enable(spi->clk);
	अगर (status)
		जाओ out;

	/* The following घड़ी is only used by some SoCs */
	spi->axi_clk = devm_clk_get(&pdev->dev, "axi");
	अगर (PTR_ERR(spi->axi_clk) == -EPROBE_DEFER) अणु
		status = -EPROBE_DEFER;
		जाओ out_rel_clk;
	पूर्ण
	अगर (!IS_ERR(spi->axi_clk))
		clk_prepare_enable(spi->axi_clk);

	tclk_hz = clk_get_rate(spi->clk);

	/*
	 * With old device tree, armada-370-spi could be used with
	 * Armada XP, however क्रम this SoC the maximum frequency is
	 * 50MHz instead of tclk/4. On Armada 370, tclk cannot be
	 * higher than 200MHz. So, in order to be able to handle both
	 * SoCs, we can take the minimum of 50MHz and tclk/4.
	 */
	अगर (of_device_is_compatible(pdev->dev.of_node,
					"marvell,armada-370-spi"))
		master->max_speed_hz = min(devdata->max_hz,
				DIV_ROUND_UP(tclk_hz, devdata->min_भागisor));
	अन्यथा अगर (devdata->min_भागisor)
		master->max_speed_hz =
			DIV_ROUND_UP(tclk_hz, devdata->min_भागisor);
	अन्यथा
		master->max_speed_hz = devdata->max_hz;
	master->min_speed_hz = DIV_ROUND_UP(tclk_hz, devdata->max_भागisor);

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	spi->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(spi->base)) अणु
		status = PTR_ERR(spi->base);
		जाओ out_rel_axi_clk;
	पूर्ण

	क्रम_each_available_child_of_node(pdev->dev.of_node, np) अणु
		काष्ठा orion_direct_acc *dir_acc;
		u32 cs;

		/* Get chip-select number from the "reg" property */
		status = of_property_पढ़ो_u32(np, "reg", &cs);
		अगर (status) अणु
			dev_err(&pdev->dev,
				"%pOF has no valid 'reg' property (%d)\n",
				np, status);
			जारी;
		पूर्ण

		/*
		 * Check अगर an address is configured क्रम this SPI device. If
		 * not, the MBus mapping via the 'ranges' property in the 'soc'
		 * node is not configured and this device should not use the
		 * direct mode. In this हाल, just जारी with the next
		 * device.
		 */
		status = of_address_to_resource(pdev->dev.of_node, cs + 1, r);
		अगर (status)
			जारी;

		/*
		 * Only map one page क्रम direct access. This is enough क्रम the
		 * simple TX transfer which only ग_लिखोs to the first word.
		 * This needs to get extended क्रम the direct SPI NOR / SPI न_अंकD
		 * support, once this माला_लो implemented.
		 */
		dir_acc = &spi->child[cs].direct_access;
		dir_acc->vaddr = devm_ioremap(&pdev->dev, r->start, PAGE_SIZE);
		अगर (!dir_acc->vaddr) अणु
			status = -ENOMEM;
			जाओ out_rel_axi_clk;
		पूर्ण
		dir_acc->size = PAGE_SIZE;

		dev_info(&pdev->dev, "CS%d configured for direct access\n", cs);
	पूर्ण

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, SPI_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_enable(&pdev->dev);

	status = orion_spi_reset(spi);
	अगर (status < 0)
		जाओ out_rel_pm;

	master->dev.of_node = pdev->dev.of_node;
	status = spi_रेजिस्टर_master(master);
	अगर (status < 0)
		जाओ out_rel_pm;

	वापस status;

out_rel_pm:
	pm_runसमय_disable(&pdev->dev);
out_rel_axi_clk:
	clk_disable_unprepare(spi->axi_clk);
out_rel_clk:
	clk_disable_unprepare(spi->clk);
out:
	spi_master_put(master);
	वापस status;
पूर्ण


अटल पूर्णांक orion_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा orion_spi *spi = spi_master_get_devdata(master);

	pm_runसमय_get_sync(&pdev->dev);
	clk_disable_unprepare(spi->axi_clk);
	clk_disable_unprepare(spi->clk);

	spi_unरेजिस्टर_master(master);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:" DRIVER_NAME);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक orion_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा orion_spi *spi = spi_master_get_devdata(master);

	clk_disable_unprepare(spi->axi_clk);
	clk_disable_unprepare(spi->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक orion_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा orion_spi *spi = spi_master_get_devdata(master);

	अगर (!IS_ERR(spi->axi_clk))
		clk_prepare_enable(spi->axi_clk);
	वापस clk_prepare_enable(spi->clk);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops orion_spi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(orion_spi_runसमय_suspend,
			   orion_spi_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver orion_spi_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.pm	= &orion_spi_pm_ops,
		.of_match_table = of_match_ptr(orion_spi_of_match_table),
	पूर्ण,
	.probe		= orion_spi_probe,
	.हटाओ		= orion_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(orion_spi_driver);

MODULE_DESCRIPTION("Orion SPI driver");
MODULE_AUTHOR("Shadi Ammouri <shadi@marvell.com>");
MODULE_LICENSE("GPL");
