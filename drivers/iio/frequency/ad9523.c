<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD9523 SPI Low Jitter Clock Generator
 *
 * Copyright 2012 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/frequency/ad9523.h>

#घोषणा AD9523_READ	(1 << 15)
#घोषणा AD9523_WRITE	(0 << 15)
#घोषणा AD9523_CNT(x)	(((x) - 1) << 13)
#घोषणा AD9523_ADDR(x)	((x) & 0xFFF)

#घोषणा AD9523_R1B	(1 << 16)
#घोषणा AD9523_R2B	(2 << 16)
#घोषणा AD9523_R3B	(3 << 16)
#घोषणा AD9523_TRANSF_LEN(x)			((x) >> 16)

#घोषणा AD9523_SERIAL_PORT_CONFIG		(AD9523_R1B | 0x0)
#घोषणा AD9523_VERSION_REGISTER			(AD9523_R1B | 0x2)
#घोषणा AD9523_PART_REGISTER			(AD9523_R1B | 0x3)
#घोषणा AD9523_READBACK_CTRL			(AD9523_R1B | 0x4)

#घोषणा AD9523_EEPROM_CUSTOMER_VERSION_ID	(AD9523_R2B | 0x6)

#घोषणा AD9523_PLL1_REF_A_DIVIDER		(AD9523_R2B | 0x11)
#घोषणा AD9523_PLL1_REF_B_DIVIDER		(AD9523_R2B | 0x13)
#घोषणा AD9523_PLL1_REF_TEST_DIVIDER		(AD9523_R1B | 0x14)
#घोषणा AD9523_PLL1_FEEDBACK_DIVIDER		(AD9523_R2B | 0x17)
#घोषणा AD9523_PLL1_CHARGE_PUMP_CTRL		(AD9523_R2B | 0x19)
#घोषणा AD9523_PLL1_INPUT_RECEIVERS_CTRL	(AD9523_R1B | 0x1A)
#घोषणा AD9523_PLL1_REF_CTRL			(AD9523_R1B | 0x1B)
#घोषणा AD9523_PLL1_MISC_CTRL			(AD9523_R1B | 0x1C)
#घोषणा AD9523_PLL1_LOOP_FILTER_CTRL		(AD9523_R1B | 0x1D)

#घोषणा AD9523_PLL2_CHARGE_PUMP			(AD9523_R1B | 0xF0)
#घोषणा AD9523_PLL2_FEEDBACK_DIVIDER_AB		(AD9523_R1B | 0xF1)
#घोषणा AD9523_PLL2_CTRL			(AD9523_R1B | 0xF2)
#घोषणा AD9523_PLL2_VCO_CTRL			(AD9523_R1B | 0xF3)
#घोषणा AD9523_PLL2_VCO_DIVIDER			(AD9523_R1B | 0xF4)
#घोषणा AD9523_PLL2_LOOP_FILTER_CTRL		(AD9523_R2B | 0xF6)
#घोषणा AD9523_PLL2_R2_DIVIDER			(AD9523_R1B | 0xF7)

#घोषणा AD9523_CHANNEL_CLOCK_DIST(ch)		(AD9523_R3B | (0x192 + 3 * ch))

#घोषणा AD9523_PLL1_OUTPUT_CTRL			(AD9523_R1B | 0x1BA)
#घोषणा AD9523_PLL1_OUTPUT_CHANNEL_CTRL		(AD9523_R1B | 0x1BB)

#घोषणा AD9523_READBACK_0			(AD9523_R1B | 0x22C)
#घोषणा AD9523_READBACK_1			(AD9523_R1B | 0x22D)

#घोषणा AD9523_STATUS_SIGNALS			(AD9523_R3B | 0x232)
#घोषणा AD9523_POWER_DOWN_CTRL			(AD9523_R1B | 0x233)
#घोषणा AD9523_IO_UPDATE			(AD9523_R1B | 0x234)

#घोषणा AD9523_EEPROM_DATA_XFER_STATUS		(AD9523_R1B | 0xB00)
#घोषणा AD9523_EEPROM_ERROR_READBACK		(AD9523_R1B | 0xB01)
#घोषणा AD9523_EEPROM_CTRL1			(AD9523_R1B | 0xB02)
#घोषणा AD9523_EEPROM_CTRL2			(AD9523_R1B | 0xB03)

/* AD9523_SERIAL_PORT_CONFIG */

#घोषणा AD9523_SER_CONF_SDO_ACTIVE		(1 << 7)
#घोषणा AD9523_SER_CONF_SOFT_RESET		(1 << 5)

/* AD9523_READBACK_CTRL */
#घोषणा AD9523_READBACK_CTRL_READ_BUFFERED	(1 << 0)

/* AD9523_PLL1_CHARGE_PUMP_CTRL */
#घोषणा AD9523_PLL1_CHARGE_PUMP_CURRENT_nA(x)	(((x) / 500) & 0x7F)
#घोषणा AD9523_PLL1_CHARGE_PUMP_TRISTATE	(1 << 7)
#घोषणा AD9523_PLL1_CHARGE_PUMP_MODE_NORMAL	(3 << 8)
#घोषणा AD9523_PLL1_CHARGE_PUMP_MODE_PUMP_DOWN	(2 << 8)
#घोषणा AD9523_PLL1_CHARGE_PUMP_MODE_PUMP_UP	(1 << 8)
#घोषणा AD9523_PLL1_CHARGE_PUMP_MODE_TRISTATE	(0 << 8)
#घोषणा AD9523_PLL1_BACKLASH_PW_MIN		(0 << 10)
#घोषणा AD9523_PLL1_BACKLASH_PW_LOW		(1 << 10)
#घोषणा AD9523_PLL1_BACKLASH_PW_HIGH		(2 << 10)
#घोषणा AD9523_PLL1_BACKLASH_PW_MAX		(3 << 10)

/* AD9523_PLL1_INPUT_RECEIVERS_CTRL */
#घोषणा AD9523_PLL1_REF_TEST_RCV_EN		(1 << 7)
#घोषणा AD9523_PLL1_REFB_DIFF_RCV_EN		(1 << 6)
#घोषणा AD9523_PLL1_REFA_DIFF_RCV_EN		(1 << 5)
#घोषणा AD9523_PLL1_REFB_RCV_EN			(1 << 4)
#घोषणा AD9523_PLL1_REFA_RCV_EN			(1 << 3)
#घोषणा AD9523_PLL1_REFA_REFB_PWR_CTRL_EN	(1 << 2)
#घोषणा AD9523_PLL1_OSC_IN_CMOS_NEG_INP_EN	(1 << 1)
#घोषणा AD9523_PLL1_OSC_IN_DIFF_EN		(1 << 0)

/* AD9523_PLL1_REF_CTRL */
#घोषणा AD9523_PLL1_BYPASS_REF_TEST_DIV_EN	(1 << 7)
#घोषणा AD9523_PLL1_BYPASS_FEEDBACK_DIV_EN	(1 << 6)
#घोषणा AD9523_PLL1_ZERO_DELAY_MODE_INT		(1 << 5)
#घोषणा AD9523_PLL1_ZERO_DELAY_MODE_EXT		(0 << 5)
#घोषणा AD9523_PLL1_OSC_IN_PLL_FEEDBACK_EN	(1 << 4)
#घोषणा AD9523_PLL1_ZD_IN_CMOS_NEG_INP_EN	(1 << 3)
#घोषणा AD9523_PLL1_ZD_IN_DIFF_EN		(1 << 2)
#घोषणा AD9523_PLL1_REFB_CMOS_NEG_INP_EN	(1 << 1)
#घोषणा AD9523_PLL1_REFA_CMOS_NEG_INP_EN	(1 << 0)

/* AD9523_PLL1_MISC_CTRL */
#घोषणा AD9523_PLL1_REFB_INDEP_DIV_CTRL_EN	(1 << 7)
#घोषणा AD9523_PLL1_OSC_CTRL_FAIL_VCC_BY2_EN	(1 << 6)
#घोषणा AD9523_PLL1_REF_MODE(x)			((x) << 2)
#घोषणा AD9523_PLL1_BYPASS_REFB_DIV		(1 << 1)
#घोषणा AD9523_PLL1_BYPASS_REFA_DIV		(1 << 0)

/* AD9523_PLL1_LOOP_FILTER_CTRL */
#घोषणा AD9523_PLL1_LOOP_FILTER_RZERO(x)	((x) & 0xF)

/* AD9523_PLL2_CHARGE_PUMP */
#घोषणा AD9523_PLL2_CHARGE_PUMP_CURRENT_nA(x)	((x) / 3500)

/* AD9523_PLL2_FEEDBACK_DIVIDER_AB */
#घोषणा AD9523_PLL2_FB_NDIV_A_CNT(x)		(((x) & 0x3) << 6)
#घोषणा AD9523_PLL2_FB_NDIV_B_CNT(x)		(((x) & 0x3F) << 0)
#घोषणा AD9523_PLL2_FB_NDIV(a, b)		(4 * (b) + (a))

/* AD9523_PLL2_CTRL */
#घोषणा AD9523_PLL2_CHARGE_PUMP_MODE_NORMAL	(3 << 0)
#घोषणा AD9523_PLL2_CHARGE_PUMP_MODE_PUMP_DOWN	(2 << 0)
#घोषणा AD9523_PLL2_CHARGE_PUMP_MODE_PUMP_UP	(1 << 0)
#घोषणा AD9523_PLL2_CHARGE_PUMP_MODE_TRISTATE	(0 << 0)
#घोषणा AD9523_PLL2_BACKLASH_PW_MIN		(0 << 2)
#घोषणा AD9523_PLL2_BACKLASH_PW_LOW		(1 << 2)
#घोषणा AD9523_PLL2_BACKLASH_PW_HIGH		(2 << 2)
#घोषणा AD9523_PLL2_BACKLASH_PW_MAX		(3 << 1)
#घोषणा AD9523_PLL2_BACKLASH_CTRL_EN		(1 << 4)
#घोषणा AD9523_PLL2_FREQ_DOUBLER_EN		(1 << 5)
#घोषणा AD9523_PLL2_LOCK_DETECT_PWR_DOWN_EN	(1 << 7)

/* AD9523_PLL2_VCO_CTRL */
#घोषणा AD9523_PLL2_VCO_CALIBRATE		(1 << 1)
#घोषणा AD9523_PLL2_FORCE_VCO_MIDSCALE		(1 << 2)
#घोषणा AD9523_PLL2_FORCE_REFERENCE_VALID	(1 << 3)
#घोषणा AD9523_PLL2_FORCE_RELEASE_SYNC		(1 << 4)

/* AD9523_PLL2_VCO_DIVIDER */
#घोषणा AD9523_PLL2_VCO_DIV_M1(x)		((((x) - 3) & 0x3) << 0)
#घोषणा AD9523_PLL2_VCO_DIV_M2(x)		((((x) - 3) & 0x3) << 4)
#घोषणा AD9523_PLL2_VCO_DIV_M1_PWR_DOWN_EN	(1 << 2)
#घोषणा AD9523_PLL2_VCO_DIV_M2_PWR_DOWN_EN	(1 << 6)

/* AD9523_PLL2_LOOP_FILTER_CTRL */
#घोषणा AD9523_PLL2_LOOP_FILTER_CPOLE1(x)	(((x) & 0x7) << 0)
#घोषणा AD9523_PLL2_LOOP_FILTER_RZERO(x)	(((x) & 0x7) << 3)
#घोषणा AD9523_PLL2_LOOP_FILTER_RPOLE2(x)	(((x) & 0x7) << 6)
#घोषणा AD9523_PLL2_LOOP_FILTER_RZERO_BYPASS_EN	(1 << 8)

/* AD9523_PLL2_R2_DIVIDER */
#घोषणा AD9523_PLL2_R2_DIVIDER_VAL(x)		(((x) & 0x1F) << 0)

/* AD9523_CHANNEL_CLOCK_DIST */
#घोषणा AD9523_CLK_DIST_DIV_PHASE(x)		(((x) & 0x3F) << 18)
#घोषणा AD9523_CLK_DIST_DIV_PHASE_REV(x)	((ret >> 18) & 0x3F)
#घोषणा AD9523_CLK_DIST_DIV(x)			((((x) - 1) & 0x3FF) << 8)
#घोषणा AD9523_CLK_DIST_DIV_REV(x)		(((ret >> 8) & 0x3FF) + 1)
#घोषणा AD9523_CLK_DIST_INV_DIV_OUTPUT_EN	(1 << 7)
#घोषणा AD9523_CLK_DIST_IGNORE_SYNC_EN		(1 << 6)
#घोषणा AD9523_CLK_DIST_PWR_DOWN_EN		(1 << 5)
#घोषणा AD9523_CLK_DIST_LOW_PWR_MODE_EN		(1 << 4)
#घोषणा AD9523_CLK_DIST_DRIVER_MODE(x)		(((x) & 0xF) << 0)

/* AD9523_PLL1_OUTPUT_CTRL */
#घोषणा AD9523_PLL1_OUTP_CTRL_VCO_DIV_SEL_CH6_M2	(1 << 7)
#घोषणा AD9523_PLL1_OUTP_CTRL_VCO_DIV_SEL_CH5_M2	(1 << 6)
#घोषणा AD9523_PLL1_OUTP_CTRL_VCO_DIV_SEL_CH4_M2	(1 << 5)
#घोषणा AD9523_PLL1_OUTP_CTRL_CMOS_DRV_WEAK		(1 << 4)
#घोषणा AD9523_PLL1_OUTP_CTRL_OUTPUT_DIV_1		(0 << 0)
#घोषणा AD9523_PLL1_OUTP_CTRL_OUTPUT_DIV_2		(1 << 0)
#घोषणा AD9523_PLL1_OUTP_CTRL_OUTPUT_DIV_4		(2 << 0)
#घोषणा AD9523_PLL1_OUTP_CTRL_OUTPUT_DIV_8		(4 << 0)
#घोषणा AD9523_PLL1_OUTP_CTRL_OUTPUT_DIV_16		(8 << 0)

/* AD9523_PLL1_OUTPUT_CHANNEL_CTRL */
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_OUTPUT_PWR_DOWN_EN	(1 << 7)
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_VCO_DIV_SEL_CH9_M2	(1 << 6)
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_VCO_DIV_SEL_CH8_M2	(1 << 5)
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_VCO_DIV_SEL_CH7_M2	(1 << 4)
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_VCXO_SRC_SEL_CH3	(1 << 3)
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_VCXO_SRC_SEL_CH2	(1 << 2)
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_VCXO_SRC_SEL_CH1	(1 << 1)
#घोषणा AD9523_PLL1_OUTP_CH_CTRL_VCXO_SRC_SEL_CH0	(1 << 0)

/* AD9523_READBACK_0 */
#घोषणा AD9523_READBACK_0_STAT_PLL2_REF_CLK		(1 << 7)
#घोषणा AD9523_READBACK_0_STAT_PLL2_FB_CLK		(1 << 6)
#घोषणा AD9523_READBACK_0_STAT_VCXO			(1 << 5)
#घोषणा AD9523_READBACK_0_STAT_REF_TEST			(1 << 4)
#घोषणा AD9523_READBACK_0_STAT_REFB			(1 << 3)
#घोषणा AD9523_READBACK_0_STAT_REFA			(1 << 2)
#घोषणा AD9523_READBACK_0_STAT_PLL2_LD			(1 << 1)
#घोषणा AD9523_READBACK_0_STAT_PLL1_LD			(1 << 0)

/* AD9523_READBACK_1 */
#घोषणा AD9523_READBACK_1_HOLDOVER_ACTIVE		(1 << 3)
#घोषणा AD9523_READBACK_1_AUTOMODE_SEL_REFB		(1 << 2)
#घोषणा AD9523_READBACK_1_VCO_CALIB_IN_PROGRESS		(1 << 0)

/* AD9523_STATUS_SIGNALS */
#घोषणा AD9523_STATUS_SIGNALS_SYNC_MAN_CTRL		(1 << 16)
#घोषणा AD9523_STATUS_MONITOR_01_PLL12_LOCKED		(0x302)
/* AD9523_POWER_DOWN_CTRL */
#घोषणा AD9523_POWER_DOWN_CTRL_PLL1_PWR_DOWN		(1 << 2)
#घोषणा AD9523_POWER_DOWN_CTRL_PLL2_PWR_DOWN		(1 << 1)
#घोषणा AD9523_POWER_DOWN_CTRL_DIST_PWR_DOWN		(1 << 0)

/* AD9523_IO_UPDATE */
#घोषणा AD9523_IO_UPDATE_EN				(1 << 0)

/* AD9523_EEPROM_DATA_XFER_STATUS */
#घोषणा AD9523_EEPROM_DATA_XFER_IN_PROGRESS		(1 << 0)

/* AD9523_EEPROM_ERROR_READBACK */
#घोषणा AD9523_EEPROM_ERROR_READBACK_FAIL		(1 << 0)

/* AD9523_EEPROM_CTRL1 */
#घोषणा AD9523_EEPROM_CTRL1_SOFT_EEPROM			(1 << 1)
#घोषणा AD9523_EEPROM_CTRL1_EEPROM_WRITE_PROT_DIS	(1 << 0)

/* AD9523_EEPROM_CTRL2 */
#घोषणा AD9523_EEPROM_CTRL2_REG2EEPROM			(1 << 0)

#घोषणा AD9523_NUM_CHAN					14
#घोषणा AD9523_NUM_CHAN_ALT_CLK_SRC			10

/* Helpers to aव्योम excess line अवरोधs */
#घोषणा AD_IFE(_pde, _a, _b) ((pdata->_pde) ? _a : _b)
#घोषणा AD_IF(_pde, _a) AD_IFE(_pde, _a, 0)

क्रमागत अणु
	AD9523_STAT_PLL1_LD,
	AD9523_STAT_PLL2_LD,
	AD9523_STAT_REFA,
	AD9523_STAT_REFB,
	AD9523_STAT_REF_TEST,
	AD9523_STAT_VCXO,
	AD9523_STAT_PLL2_FB_CLK,
	AD9523_STAT_PLL2_REF_CLK,
	AD9523_SYNC,
	AD9523_EEPROM,
पूर्ण;

क्रमागत अणु
	AD9523_VCO1,
	AD9523_VCO2,
	AD9523_VCXO,
	AD9523_NUM_CLK_SRC,
पूर्ण;

काष्ठा ad9523_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*reg;
	काष्ठा ad9523_platक्रमm_data	*pdata;
	काष्ठा iio_chan_spec		ad9523_channels[AD9523_NUM_CHAN];
	काष्ठा gpio_desc		*pwrकरोwn_gpio;
	काष्ठा gpio_desc		*reset_gpio;
	काष्ठा gpio_desc		*sync_gpio;

	अचिन्हित दीर्घ		vcxo_freq;
	अचिन्हित दीर्घ		vco_freq;
	अचिन्हित दीर्घ		vco_out_freq[AD9523_NUM_CLK_SRC];
	अचिन्हित अक्षर		vco_out_map[AD9523_NUM_CHAN_ALT_CLK_SRC];

	/*
	 * Lock क्रम accessing device रेजिस्टरs. Some operations require
	 * multiple consecutive R/W operations, during which the device
	 * shouldn't be पूर्णांकerrupted.  The buffers are also shared across
	 * all operations so need to be रक्षित on stand alone पढ़ोs and
	 * ग_लिखोs.
	 */
	काष्ठा mutex		lock;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण data[2] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad9523_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	/* We encode the रेजिस्टर size 1..3 bytes पूर्णांकo the रेजिस्टर address.
	 * On transfer we get the size from the रेजिस्टर datum, and make sure
	 * the result is properly aligned.
	 */

	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[2],
			.len = 2,
		पूर्ण, अणु
			.rx_buf = &st->data[1].d8[4 - AD9523_TRANSF_LEN(addr)],
			.len = AD9523_TRANSF_LEN(addr),
		पूर्ण,
	पूर्ण;

	st->data[0].d32 = cpu_to_be32(AD9523_READ |
				      AD9523_CNT(AD9523_TRANSF_LEN(addr)) |
				      AD9523_ADDR(addr));

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret < 0)
		dev_err(&indio_dev->dev, "read failed (%d)", ret);
	अन्यथा
		ret = be32_to_cpu(st->data[1].d32) & (0xFFFFFF >>
				  (8 * (3 - AD9523_TRANSF_LEN(addr))));

	वापस ret;
पूर्ण;

अटल पूर्णांक ad9523_ग_लिखो(काष्ठा iio_dev *indio_dev,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[2],
			.len = 2,
		पूर्ण, अणु
			.tx_buf = &st->data[1].d8[4 - AD9523_TRANSF_LEN(addr)],
			.len = AD9523_TRANSF_LEN(addr),
		पूर्ण,
	पूर्ण;

	st->data[0].d32 = cpu_to_be32(AD9523_WRITE |
				      AD9523_CNT(AD9523_TRANSF_LEN(addr)) |
				      AD9523_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(val);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));

	अगर (ret < 0)
		dev_err(&indio_dev->dev, "write failed (%d)", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ad9523_io_update(काष्ठा iio_dev *indio_dev)
अणु
	वापस ad9523_ग_लिखो(indio_dev, AD9523_IO_UPDATE, AD9523_IO_UPDATE_EN);
पूर्ण

अटल पूर्णांक ad9523_vco_out_map(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक ch, अचिन्हित पूर्णांक out)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक mask;

	चयन (ch) अणु
	हाल 0 ... 3:
		ret = ad9523_पढ़ो(indio_dev, AD9523_PLL1_OUTPUT_CHANNEL_CTRL);
		अगर (ret < 0)
			अवरोध;
		mask = AD9523_PLL1_OUTP_CH_CTRL_VCXO_SRC_SEL_CH0 << ch;
		अगर (out) अणु
			ret |= mask;
			out = 2;
		पूर्ण अन्यथा अणु
			ret &= ~mask;
		पूर्ण
		ret = ad9523_ग_लिखो(indio_dev,
				   AD9523_PLL1_OUTPUT_CHANNEL_CTRL, ret);
		अवरोध;
	हाल 4 ... 6:
		ret = ad9523_पढ़ो(indio_dev, AD9523_PLL1_OUTPUT_CTRL);
		अगर (ret < 0)
			अवरोध;
		mask = AD9523_PLL1_OUTP_CTRL_VCO_DIV_SEL_CH4_M2 << (ch - 4);
		अगर (out)
			ret |= mask;
		अन्यथा
			ret &= ~mask;
		ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_OUTPUT_CTRL, ret);
		अवरोध;
	हाल 7 ... 9:
		ret = ad9523_पढ़ो(indio_dev, AD9523_PLL1_OUTPUT_CHANNEL_CTRL);
		अगर (ret < 0)
			अवरोध;
		mask = AD9523_PLL1_OUTP_CH_CTRL_VCO_DIV_SEL_CH7_M2 << (ch - 7);
		अगर (out)
			ret |= mask;
		अन्यथा
			ret &= ~mask;
		ret = ad9523_ग_लिखो(indio_dev,
				   AD9523_PLL1_OUTPUT_CHANNEL_CTRL, ret);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	st->vco_out_map[ch] = out;

	वापस ret;
पूर्ण

अटल पूर्णांक ad9523_set_घड़ी_provider(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक ch, अचिन्हित दीर्घ freq)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	दीर्घ पंचांगp1, पंचांगp2;
	bool use_alt_clk_src;

	चयन (ch) अणु
	हाल 0 ... 3:
		use_alt_clk_src = (freq == st->vco_out_freq[AD9523_VCXO]);
		अवरोध;
	हाल 4 ... 9:
		पंचांगp1 = st->vco_out_freq[AD9523_VCO1] / freq;
		पंचांगp2 = st->vco_out_freq[AD9523_VCO2] / freq;
		पंचांगp1 *= freq;
		पंचांगp2 *= freq;
		use_alt_clk_src = (असल(पंचांगp1 - freq) > असल(पंचांगp2 - freq));
		अवरोध;
	शेष:
		/* Ch 10..14: No action required, वापस success */
		वापस 0;
	पूर्ण

	वापस ad9523_vco_out_map(indio_dev, ch, use_alt_clk_src);
पूर्ण

अटल पूर्णांक ad9523_store_eeprom(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret, पंचांगp;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_EEPROM_CTRL1,
			   AD9523_EEPROM_CTRL1_EEPROM_WRITE_PROT_DIS);
	अगर (ret < 0)
		वापस ret;
	ret = ad9523_ग_लिखो(indio_dev, AD9523_EEPROM_CTRL2,
			   AD9523_EEPROM_CTRL2_REG2EEPROM);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = 4;
	करो अणु
		msleep(20);
		ret = ad9523_पढ़ो(indio_dev,
				  AD9523_EEPROM_DATA_XFER_STATUS);
		अगर (ret < 0)
			वापस ret;
	पूर्ण जबतक ((ret & AD9523_EEPROM_DATA_XFER_IN_PROGRESS) && पंचांगp--);

	ret = ad9523_ग_लिखो(indio_dev, AD9523_EEPROM_CTRL1, 0);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_पढ़ो(indio_dev, AD9523_EEPROM_ERROR_READBACK);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & AD9523_EEPROM_ERROR_READBACK_FAIL) अणु
		dev_err(&indio_dev->dev, "Verify EEPROM failed");
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ad9523_sync(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret, पंचांगp;

	ret = ad9523_पढ़ो(indio_dev, AD9523_STATUS_SIGNALS);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = ret;
	पंचांगp |= AD9523_STATUS_SIGNALS_SYNC_MAN_CTRL;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_STATUS_SIGNALS, पंचांगp);
	अगर (ret < 0)
		वापस ret;

	ad9523_io_update(indio_dev);
	पंचांगp &= ~AD9523_STATUS_SIGNALS_SYNC_MAN_CTRL;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_STATUS_SIGNALS, पंचांगp);
	अगर (ret < 0)
		वापस ret;

	वापस ad9523_io_update(indio_dev);
पूर्ण

अटल sमाप_प्रकार ad9523_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	bool state;
	पूर्णांक ret;

	ret = strtobool(buf, &state);
	अगर (ret < 0)
		वापस ret;

	अगर (!state)
		वापस len;

	mutex_lock(&st->lock);
	चयन ((u32)this_attr->address) अणु
	हाल AD9523_SYNC:
		ret = ad9523_sync(indio_dev);
		अवरोध;
	हाल AD9523_EEPROM:
		ret = ad9523_store_eeprom(indio_dev);
		अवरोध;
	शेष:
		ret = -ENODEV;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार ad9523_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad9523_पढ़ो(indio_dev, AD9523_READBACK_0);
	अगर (ret >= 0) अणु
		ret = प्र_लिखो(buf, "%d\n", !!(ret & (1 <<
			(u32)this_attr->address)));
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल IIO_DEVICE_ATTR(pll1_locked, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_PLL1_LD);

अटल IIO_DEVICE_ATTR(pll2_locked, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_PLL2_LD);

अटल IIO_DEVICE_ATTR(pll1_reference_clk_a_present, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_REFA);

अटल IIO_DEVICE_ATTR(pll1_reference_clk_b_present, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_REFB);

अटल IIO_DEVICE_ATTR(pll1_reference_clk_test_present, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_REF_TEST);

अटल IIO_DEVICE_ATTR(vcxo_clk_present, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_VCXO);

अटल IIO_DEVICE_ATTR(pll2_feedback_clk_present, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_PLL2_FB_CLK);

अटल IIO_DEVICE_ATTR(pll2_reference_clk_present, S_IRUGO,
			ad9523_show,
			शून्य,
			AD9523_STAT_PLL2_REF_CLK);

अटल IIO_DEVICE_ATTR(sync_भागiders, S_IWUSR,
			शून्य,
			ad9523_store,
			AD9523_SYNC);

अटल IIO_DEVICE_ATTR(store_eeprom, S_IWUSR,
			शून्य,
			ad9523_store,
			AD9523_EEPROM);

अटल काष्ठा attribute *ad9523_attributes[] = अणु
	&iio_dev_attr_sync_भागiders.dev_attr.attr,
	&iio_dev_attr_store_eeprom.dev_attr.attr,
	&iio_dev_attr_pll2_feedback_clk_present.dev_attr.attr,
	&iio_dev_attr_pll2_reference_clk_present.dev_attr.attr,
	&iio_dev_attr_pll1_reference_clk_a_present.dev_attr.attr,
	&iio_dev_attr_pll1_reference_clk_b_present.dev_attr.attr,
	&iio_dev_attr_pll1_reference_clk_test_present.dev_attr.attr,
	&iio_dev_attr_vcxo_clk_present.dev_attr.attr,
	&iio_dev_attr_pll1_locked.dev_attr.attr,
	&iio_dev_attr_pll2_locked.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad9523_attribute_group = अणु
	.attrs = ad9523_attributes,
पूर्ण;

अटल पूर्णांक ad9523_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक code;
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad9523_पढ़ो(indio_dev, AD9523_CHANNEL_CLOCK_DIST(chan->channel));
	mutex_unlock(&st->lock);

	अगर (ret < 0)
		वापस ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = !(ret & AD9523_CLK_DIST_PWR_DOWN_EN);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_FREQUENCY:
		*val = st->vco_out_freq[st->vco_out_map[chan->channel]] /
			AD9523_CLK_DIST_DIV_REV(ret);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_PHASE:
		code = (AD9523_CLK_DIST_DIV_PHASE_REV(ret) * 3141592) /
			AD9523_CLK_DIST_DIV_REV(ret);
		*val = code / 1000000;
		*val2 = code % 1000000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण;

अटल पूर्णांक ad9523_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret, पंचांगp, code;

	mutex_lock(&st->lock);
	ret = ad9523_पढ़ो(indio_dev, AD9523_CHANNEL_CLOCK_DIST(chan->channel));
	अगर (ret < 0)
		जाओ out;

	reg = ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val)
			reg &= ~AD9523_CLK_DIST_PWR_DOWN_EN;
		अन्यथा
			reg |= AD9523_CLK_DIST_PWR_DOWN_EN;
		अवरोध;
	हाल IIO_CHAN_INFO_FREQUENCY:
		अगर (val <= 0) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		ret = ad9523_set_घड़ी_provider(indio_dev, chan->channel, val);
		अगर (ret < 0)
			जाओ out;
		पंचांगp = st->vco_out_freq[st->vco_out_map[chan->channel]] / val;
		पंचांगp = clamp(पंचांगp, 1, 1024);
		reg &= ~(0x3FF << 8);
		reg |= AD9523_CLK_DIST_DIV(पंचांगp);
		अवरोध;
	हाल IIO_CHAN_INFO_PHASE:
		code = val * 1000000 + val2 % 1000000;
		पंचांगp = (code * AD9523_CLK_DIST_DIV_REV(ret)) / 3141592;
		पंचांगp = clamp(पंचांगp, 0, 63);
		reg &= ~AD9523_CLK_DIST_DIV_PHASE(~0);
		reg |= AD9523_CLK_DIST_DIV_PHASE(पंचांगp);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = ad9523_ग_लिखो(indio_dev, AD9523_CHANNEL_CLOCK_DIST(chan->channel),
			   reg);
	अगर (ret < 0)
		जाओ out;

	ad9523_io_update(indio_dev);
out:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad9523_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक ग_लिखोval,
			      अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	अगर (पढ़ोval == शून्य) अणु
		ret = ad9523_ग_लिखो(indio_dev, reg | AD9523_R1B, ग_लिखोval);
		ad9523_io_update(indio_dev);
	पूर्ण अन्यथा अणु
		ret = ad9523_पढ़ो(indio_dev, reg | AD9523_R1B);
		अगर (ret < 0)
			जाओ out_unlock;
		*पढ़ोval = ret;
		ret = 0;
	पूर्ण

out_unlock:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad9523_info = अणु
	.पढ़ो_raw = &ad9523_पढ़ो_raw,
	.ग_लिखो_raw = &ad9523_ग_लिखो_raw,
	.debugfs_reg_access = &ad9523_reg_access,
	.attrs = &ad9523_attribute_group,
पूर्ण;

अटल पूर्णांक ad9523_setup(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad9523_state *st = iio_priv(indio_dev);
	काष्ठा ad9523_platक्रमm_data *pdata = st->pdata;
	काष्ठा ad9523_channel_spec *chan;
	अचिन्हित दीर्घ active_mask = 0;
	पूर्णांक ret, i;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_SERIAL_PORT_CONFIG,
			   AD9523_SER_CONF_SOFT_RESET |
			  (st->spi->mode & SPI_3WIRE ? 0 :
			  AD9523_SER_CONF_SDO_ACTIVE));
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_READBACK_CTRL,
			  AD9523_READBACK_CTRL_READ_BUFFERED);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_io_update(indio_dev);
	अगर (ret < 0)
		वापस ret;

	/*
	 * PLL1 Setup
	 */
	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_REF_A_DIVIDER,
		pdata->refa_r_भाग);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_REF_B_DIVIDER,
		pdata->refb_r_भाग);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_FEEDBACK_DIVIDER,
		pdata->pll1_feedback_भाग);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_CHARGE_PUMP_CTRL,
		AD9523_PLL1_CHARGE_PUMP_CURRENT_nA(pdata->
			pll1_अक्षरge_pump_current_nA) |
		AD9523_PLL1_CHARGE_PUMP_MODE_NORMAL |
		AD9523_PLL1_BACKLASH_PW_MIN);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_INPUT_RECEIVERS_CTRL,
		AD_IF(refa_dअगरf_rcv_en, AD9523_PLL1_REFA_RCV_EN) |
		AD_IF(refb_dअगरf_rcv_en, AD9523_PLL1_REFB_RCV_EN) |
		AD_IF(osc_in_dअगरf_en, AD9523_PLL1_OSC_IN_DIFF_EN) |
		AD_IF(osc_in_cmos_neg_inp_en,
		      AD9523_PLL1_OSC_IN_CMOS_NEG_INP_EN) |
		AD_IF(refa_dअगरf_rcv_en, AD9523_PLL1_REFA_DIFF_RCV_EN) |
		AD_IF(refb_dअगरf_rcv_en, AD9523_PLL1_REFB_DIFF_RCV_EN));
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_REF_CTRL,
		AD_IF(zd_in_dअगरf_en, AD9523_PLL1_ZD_IN_DIFF_EN) |
		AD_IF(zd_in_cmos_neg_inp_en,
		      AD9523_PLL1_ZD_IN_CMOS_NEG_INP_EN) |
		AD_IF(zero_delay_mode_पूर्णांकernal_en,
		      AD9523_PLL1_ZERO_DELAY_MODE_INT) |
		AD_IF(osc_in_feedback_en, AD9523_PLL1_OSC_IN_PLL_FEEDBACK_EN) |
		AD_IF(refa_cmos_neg_inp_en, AD9523_PLL1_REFA_CMOS_NEG_INP_EN) |
		AD_IF(refb_cmos_neg_inp_en, AD9523_PLL1_REFB_CMOS_NEG_INP_EN));
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_MISC_CTRL,
		AD9523_PLL1_REFB_INDEP_DIV_CTRL_EN |
		AD9523_PLL1_REF_MODE(pdata->ref_mode));
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL1_LOOP_FILTER_CTRL,
		AD9523_PLL1_LOOP_FILTER_RZERO(pdata->pll1_loop_filter_rzero));
	अगर (ret < 0)
		वापस ret;
	/*
	 * PLL2 Setup
	 */

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL2_CHARGE_PUMP,
		AD9523_PLL2_CHARGE_PUMP_CURRENT_nA(pdata->
			pll2_अक्षरge_pump_current_nA));
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL2_FEEDBACK_DIVIDER_AB,
		AD9523_PLL2_FB_NDIV_A_CNT(pdata->pll2_nभाग_a_cnt) |
		AD9523_PLL2_FB_NDIV_B_CNT(pdata->pll2_nभाग_b_cnt));
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL2_CTRL,
		AD9523_PLL2_CHARGE_PUMP_MODE_NORMAL |
		AD9523_PLL2_BACKLASH_CTRL_EN |
		AD_IF(pll2_freq_द्विगुनr_en, AD9523_PLL2_FREQ_DOUBLER_EN));
	अगर (ret < 0)
		वापस ret;

	st->vco_freq = भाग_u64((अचिन्हित दीर्घ दीर्घ)pdata->vcxo_freq *
			       (pdata->pll2_freq_द्विगुनr_en ? 2 : 1) *
			       AD9523_PLL2_FB_NDIV(pdata->pll2_nभाग_a_cnt,
						   pdata->pll2_nभाग_b_cnt),
			       pdata->pll2_r2_भाग);

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL2_VCO_CTRL,
		AD9523_PLL2_VCO_CALIBRATE);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL2_VCO_DIVIDER,
		AD9523_PLL2_VCO_DIV_M1(pdata->pll2_vco_भाग_m1) |
		AD9523_PLL2_VCO_DIV_M2(pdata->pll2_vco_भाग_m2) |
		AD_IFE(pll2_vco_भाग_m1, 0,
		       AD9523_PLL2_VCO_DIV_M1_PWR_DOWN_EN) |
		AD_IFE(pll2_vco_भाग_m2, 0,
		       AD9523_PLL2_VCO_DIV_M2_PWR_DOWN_EN));
	अगर (ret < 0)
		वापस ret;

	अगर (pdata->pll2_vco_भाग_m1)
		st->vco_out_freq[AD9523_VCO1] =
			st->vco_freq / pdata->pll2_vco_भाग_m1;

	अगर (pdata->pll2_vco_भाग_m2)
		st->vco_out_freq[AD9523_VCO2] =
			st->vco_freq / pdata->pll2_vco_भाग_m2;

	st->vco_out_freq[AD9523_VCXO] = pdata->vcxo_freq;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL2_R2_DIVIDER,
		AD9523_PLL2_R2_DIVIDER_VAL(pdata->pll2_r2_भाग));
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_PLL2_LOOP_FILTER_CTRL,
		AD9523_PLL2_LOOP_FILTER_CPOLE1(pdata->cpole1) |
		AD9523_PLL2_LOOP_FILTER_RZERO(pdata->rzero) |
		AD9523_PLL2_LOOP_FILTER_RPOLE2(pdata->rpole2) |
		AD_IF(rzero_bypass_en,
		      AD9523_PLL2_LOOP_FILTER_RZERO_BYPASS_EN));
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < pdata->num_channels; i++) अणु
		chan = &pdata->channels[i];
		अगर (chan->channel_num < AD9523_NUM_CHAN) अणु
			__set_bit(chan->channel_num, &active_mask);
			ret = ad9523_ग_लिखो(indio_dev,
				AD9523_CHANNEL_CLOCK_DIST(chan->channel_num),
				AD9523_CLK_DIST_DRIVER_MODE(chan->driver_mode) |
				AD9523_CLK_DIST_DIV(chan->channel_भागider) |
				AD9523_CLK_DIST_DIV_PHASE(chan->भागider_phase) |
				(chan->sync_ignore_en ?
					AD9523_CLK_DIST_IGNORE_SYNC_EN : 0) |
				(chan->भागider_output_invert_en ?
					AD9523_CLK_DIST_INV_DIV_OUTPUT_EN : 0) |
				(chan->low_घातer_mode_en ?
					AD9523_CLK_DIST_LOW_PWR_MODE_EN : 0) |
				(chan->output_dis ?
					AD9523_CLK_DIST_PWR_DOWN_EN : 0));
			अगर (ret < 0)
				वापस ret;

			ret = ad9523_vco_out_map(indio_dev, chan->channel_num,
					   chan->use_alt_घड़ी_src);
			अगर (ret < 0)
				वापस ret;

			st->ad9523_channels[i].type = IIO_ALTVOLTAGE;
			st->ad9523_channels[i].output = 1;
			st->ad9523_channels[i].indexed = 1;
			st->ad9523_channels[i].channel = chan->channel_num;
			st->ad9523_channels[i].extend_name =
				chan->extended_name;
			st->ad9523_channels[i].info_mask_separate =
				BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_PHASE) |
				BIT(IIO_CHAN_INFO_FREQUENCY);
		पूर्ण
	पूर्ण

	क्रम_each_clear_bit(i, &active_mask, AD9523_NUM_CHAN) अणु
		ret = ad9523_ग_लिखो(indio_dev,
			     AD9523_CHANNEL_CLOCK_DIST(i),
			     AD9523_CLK_DIST_DRIVER_MODE(TRISTATE) |
			     AD9523_CLK_DIST_PWR_DOWN_EN);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = ad9523_ग_लिखो(indio_dev, AD9523_POWER_DOWN_CTRL, 0);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_ग_लिखो(indio_dev, AD9523_STATUS_SIGNALS,
			   AD9523_STATUS_MONITOR_01_PLL12_LOCKED);
	अगर (ret < 0)
		वापस ret;

	ret = ad9523_io_update(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम ad9523_reg_disable(व्योम *data)
अणु
	काष्ठा regulator *reg = data;

	regulator_disable(reg);
पूर्ण

अटल पूर्णांक ad9523_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad9523_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad9523_state *st;
	पूर्णांक ret;

	अगर (!pdata) अणु
		dev_err(&spi->dev, "no platform data?\n");
		वापस -EINVAL;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	mutex_init(&st->lock);

	st->reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(&spi->dev, ad9523_reg_disable,
					       st->reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	st->pwrकरोwn_gpio = devm_gpiod_get_optional(&spi->dev, "powerdown",
		GPIOD_OUT_HIGH);
	अगर (IS_ERR(st->pwrकरोwn_gpio))
		वापस PTR_ERR(st->pwrकरोwn_gpio);

	st->reset_gpio = devm_gpiod_get_optional(&spi->dev, "reset",
		GPIOD_OUT_LOW);
	अगर (IS_ERR(st->reset_gpio))
		वापस PTR_ERR(st->reset_gpio);

	अगर (st->reset_gpio) अणु
		udelay(1);
		gpiod_direction_output(st->reset_gpio, 1);
	पूर्ण

	st->sync_gpio = devm_gpiod_get_optional(&spi->dev, "sync",
		GPIOD_OUT_HIGH);
	अगर (IS_ERR(st->sync_gpio))
		वापस PTR_ERR(st->sync_gpio);

	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;
	st->pdata = pdata;

	indio_dev->name = (pdata->name[0] != 0) ? pdata->name :
			  spi_get_device_id(spi)->name;
	indio_dev->info = &ad9523_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->ad9523_channels;
	indio_dev->num_channels = pdata->num_channels;

	ret = ad9523_setup(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad9523_id[] = अणु
	अणु"ad9523-1", 9523पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad9523_id);

अटल काष्ठा spi_driver ad9523_driver = अणु
	.driver = अणु
		.name	= "ad9523",
	पूर्ण,
	.probe		= ad9523_probe,
	.id_table	= ad9523_id,
पूर्ण;
module_spi_driver(ad9523_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD9523 CLOCKDIST/PLL");
MODULE_LICENSE("GPL v2");
