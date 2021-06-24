<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7190 AD7192 AD7193 AD7195 SPI ADC driver
 *
 * Copyright 2011-2015 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/adc/ad_sigma_delta.h>

/* Registers */
#घोषणा AD7192_REG_COMM		0 /* Communications Register (WO, 8-bit) */
#घोषणा AD7192_REG_STAT		0 /* Status Register	     (RO, 8-bit) */
#घोषणा AD7192_REG_MODE		1 /* Mode Register	     (RW, 24-bit */
#घोषणा AD7192_REG_CONF		2 /* Configuration Register  (RW, 24-bit) */
#घोषणा AD7192_REG_DATA		3 /* Data Register	     (RO, 24/32-bit) */
#घोषणा AD7192_REG_ID		4 /* ID Register	     (RO, 8-bit) */
#घोषणा AD7192_REG_GPOCON	5 /* GPOCON Register	     (RO, 8-bit) */
#घोषणा AD7192_REG_OFFSET	6 /* Offset Register	     (RW, 16-bit */
				  /* (AD7792)/24-bit (AD7192)) */
#घोषणा AD7192_REG_FULLSALE	7 /* Full-Scale Register */
				  /* (RW, 16-bit (AD7792)/24-bit (AD7192)) */

/* Communications Register Bit Designations (AD7192_REG_COMM) */
#घोषणा AD7192_COMM_WEN		BIT(7) /* Write Enable */
#घोषणा AD7192_COMM_WRITE	0 /* Write Operation */
#घोषणा AD7192_COMM_READ	BIT(6) /* Read Operation */
#घोषणा AD7192_COMM_ADDR(x)	(((x) & 0x7) << 3) /* Register Address */
#घोषणा AD7192_COMM_CREAD	BIT(2) /* Continuous Read of Data Register */

/* Status Register Bit Designations (AD7192_REG_STAT) */
#घोषणा AD7192_STAT_RDY		BIT(7) /* Ready */
#घोषणा AD7192_STAT_ERR		BIT(6) /* Error (Overrange, Underrange) */
#घोषणा AD7192_STAT_NOREF	BIT(5) /* Error no बाह्यal reference */
#घोषणा AD7192_STAT_PARITY	BIT(4) /* Parity */
#घोषणा AD7192_STAT_CH3		BIT(2) /* Channel 3 */
#घोषणा AD7192_STAT_CH2		BIT(1) /* Channel 2 */
#घोषणा AD7192_STAT_CH1		BIT(0) /* Channel 1 */

/* Mode Register Bit Designations (AD7192_REG_MODE) */
#घोषणा AD7192_MODE_SEL(x)	(((x) & 0x7) << 21) /* Operation Mode Select */
#घोषणा AD7192_MODE_SEL_MASK	(0x7 << 21) /* Operation Mode Select Mask */
#घोषणा AD7192_MODE_DAT_STA	BIT(20) /* Status Register transmission */
#घोषणा AD7192_MODE_CLKSRC(x)	(((x) & 0x3) << 18) /* Clock Source Select */
#घोषणा AD7192_MODE_SINC3	BIT(15) /* SINC3 Filter Select */
#घोषणा AD7192_MODE_ACX		BIT(14) /* AC excitation enable(AD7195 only)*/
#घोषणा AD7192_MODE_ENPAR	BIT(13) /* Parity Enable */
#घोषणा AD7192_MODE_CLKDIV	BIT(12) /* Clock भागide by 2 (AD7190/2 only)*/
#घोषणा AD7192_MODE_SCYCLE	BIT(11) /* Single cycle conversion */
#घोषणा AD7192_MODE_REJ60	BIT(10) /* 50/60Hz notch filter */
#घोषणा AD7192_MODE_RATE(x)	((x) & 0x3FF) /* Filter Update Rate Select */

/* Mode Register: AD7192_MODE_SEL options */
#घोषणा AD7192_MODE_CONT		0 /* Continuous Conversion Mode */
#घोषणा AD7192_MODE_SINGLE		1 /* Single Conversion Mode */
#घोषणा AD7192_MODE_IDLE		2 /* Idle Mode */
#घोषणा AD7192_MODE_PWRDN		3 /* Power-Down Mode */
#घोषणा AD7192_MODE_CAL_INT_ZERO	4 /* Internal Zero-Scale Calibration */
#घोषणा AD7192_MODE_CAL_INT_FULL	5 /* Internal Full-Scale Calibration */
#घोषणा AD7192_MODE_CAL_SYS_ZERO	6 /* System Zero-Scale Calibration */
#घोषणा AD7192_MODE_CAL_SYS_FULL	7 /* System Full-Scale Calibration */

/* Mode Register: AD7192_MODE_CLKSRC options */
#घोषणा AD7192_CLK_EXT_MCLK1_2		0 /* External 4.92 MHz Clock connected*/
					  /* from MCLK1 to MCLK2 */
#घोषणा AD7192_CLK_EXT_MCLK2		1 /* External Clock applied to MCLK2 */
#घोषणा AD7192_CLK_INT			2 /* Internal 4.92 MHz Clock not */
					  /* available at the MCLK2 pin */
#घोषणा AD7192_CLK_INT_CO		3 /* Internal 4.92 MHz Clock available*/
					  /* at the MCLK2 pin */

/* Configuration Register Bit Designations (AD7192_REG_CONF) */

#घोषणा AD7192_CONF_CHOP	BIT(23) /* CHOP enable */
#घोषणा AD7192_CONF_REFSEL	BIT(20) /* REFIN1/REFIN2 Reference Select */
#घोषणा AD7192_CONF_CHAN(x)	((x) << 8) /* Channel select */
#घोषणा AD7192_CONF_CHAN_MASK	(0x7FF << 8) /* Channel select mask */
#घोषणा AD7192_CONF_BURN	BIT(7) /* Burnout current enable */
#घोषणा AD7192_CONF_REFDET	BIT(6) /* Reference detect enable */
#घोषणा AD7192_CONF_BUF		BIT(4) /* Buffered Mode Enable */
#घोषणा AD7192_CONF_UNIPOLAR	BIT(3) /* Unipolar/Bipolar Enable */
#घोषणा AD7192_CONF_GAIN(x)	((x) & 0x7) /* Gain Select */

#घोषणा AD7192_CH_AIN1P_AIN2M	BIT(0) /* AIN1(+) - AIN2(-) */
#घोषणा AD7192_CH_AIN3P_AIN4M	BIT(1) /* AIN3(+) - AIN4(-) */
#घोषणा AD7192_CH_TEMP		BIT(2) /* Temp Sensor */
#घोषणा AD7192_CH_AIN2P_AIN2M	BIT(3) /* AIN2(+) - AIN2(-) */
#घोषणा AD7192_CH_AIN1		BIT(4) /* AIN1 - AINCOM */
#घोषणा AD7192_CH_AIN2		BIT(5) /* AIN2 - AINCOM */
#घोषणा AD7192_CH_AIN3		BIT(6) /* AIN3 - AINCOM */
#घोषणा AD7192_CH_AIN4		BIT(7) /* AIN4 - AINCOM */

#घोषणा AD7193_CH_AIN1P_AIN2M	0x001  /* AIN1(+) - AIN2(-) */
#घोषणा AD7193_CH_AIN3P_AIN4M	0x002  /* AIN3(+) - AIN4(-) */
#घोषणा AD7193_CH_AIN5P_AIN6M	0x004  /* AIN5(+) - AIN6(-) */
#घोषणा AD7193_CH_AIN7P_AIN8M	0x008  /* AIN7(+) - AIN8(-) */
#घोषणा AD7193_CH_TEMP		0x100 /* Temp senseor */
#घोषणा AD7193_CH_AIN2P_AIN2M	0x200 /* AIN2(+) - AIN2(-) */
#घोषणा AD7193_CH_AIN1		0x401 /* AIN1 - AINCOM */
#घोषणा AD7193_CH_AIN2		0x402 /* AIN2 - AINCOM */
#घोषणा AD7193_CH_AIN3		0x404 /* AIN3 - AINCOM */
#घोषणा AD7193_CH_AIN4		0x408 /* AIN4 - AINCOM */
#घोषणा AD7193_CH_AIN5		0x410 /* AIN5 - AINCOM */
#घोषणा AD7193_CH_AIN6		0x420 /* AIN6 - AINCOM */
#घोषणा AD7193_CH_AIN7		0x440 /* AIN7 - AINCOM */
#घोषणा AD7193_CH_AIN8		0x480 /* AIN7 - AINCOM */
#घोषणा AD7193_CH_AINCOM	0x600 /* AINCOM - AINCOM */

/* ID Register Bit Designations (AD7192_REG_ID) */
#घोषणा CHIPID_AD7190		0x4
#घोषणा CHIPID_AD7192		0x0
#घोषणा CHIPID_AD7193		0x2
#घोषणा CHIPID_AD7195		0x6
#घोषणा AD7192_ID_MASK		0x0F

/* GPOCON Register Bit Designations (AD7192_REG_GPOCON) */
#घोषणा AD7192_GPOCON_BPDSW	BIT(6) /* Bridge घातer-करोwn चयन enable */
#घोषणा AD7192_GPOCON_GP32EN	BIT(5) /* Digital Output P3 and P2 enable */
#घोषणा AD7192_GPOCON_GP10EN	BIT(4) /* Digital Output P1 and P0 enable */
#घोषणा AD7192_GPOCON_P3DAT	BIT(3) /* P3 state */
#घोषणा AD7192_GPOCON_P2DAT	BIT(2) /* P2 state */
#घोषणा AD7192_GPOCON_P1DAT	BIT(1) /* P1 state */
#घोषणा AD7192_GPOCON_P0DAT	BIT(0) /* P0 state */

#घोषणा AD7192_EXT_FREQ_MHZ_MIN	2457600
#घोषणा AD7192_EXT_FREQ_MHZ_MAX	5120000
#घोषणा AD7192_INT_FREQ_MHZ	4915200

#घोषणा AD7192_NO_SYNC_FILTER	1
#घोषणा AD7192_SYNC3_FILTER	3
#घोषणा AD7192_SYNC4_FILTER	4

/* NOTE:
 * The AD7190/2/5 features a dual use data out पढ़ोy DOUT/RDY output.
 * In order to aव्योम contentions on the SPI bus, it's thereक्रमe necessary
 * to use spi bus locking.
 *
 * The DOUT/RDY output must also be wired to an पूर्णांकerrupt capable GPIO.
 */

क्रमागत अणु
	AD7192_SYSCALIB_ZERO_SCALE,
	AD7192_SYSCALIB_FULL_SCALE,
पूर्ण;

क्रमागत अणु
	ID_AD7190,
	ID_AD7192,
	ID_AD7193,
	ID_AD7195,
पूर्ण;

काष्ठा ad7192_chip_info अणु
	अचिन्हित पूर्णांक			chip_id;
	स्थिर अक्षर			*name;
पूर्ण;

काष्ठा ad7192_state अणु
	स्थिर काष्ठा ad7192_chip_info	*chip_info;
	काष्ठा regulator		*avdd;
	काष्ठा regulator		*dvdd;
	काष्ठा clk			*mclk;
	u16				पूर्णांक_vref_mv;
	u32				fclk;
	u32				f_order;
	u32				mode;
	u32				conf;
	u32				scale_avail[8][2];
	u8				gpocon;
	u8				घड़ी_sel;
	काष्ठा mutex			lock;	/* protect sensor state */
	u8				syscalib_mode[8];

	काष्ठा ad_sigma_delta		sd;
पूर्ण;

अटल स्थिर अक्षर * स्थिर ad7192_syscalib_modes[] = अणु
	[AD7192_SYSCALIB_ZERO_SCALE] = "zero_scale",
	[AD7192_SYSCALIB_FULL_SCALE] = "full_scale",
पूर्ण;

अटल पूर्णांक ad7192_set_syscalib_mode(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad7192_state *st = iio_priv(indio_dev);

	st->syscalib_mode[chan->channel] = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7192_get_syscalib_mode(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad7192_state *st = iio_priv(indio_dev);

	वापस st->syscalib_mode[chan->channel];
पूर्ण

अटल sमाप_प्रकार ad7192_ग_लिखो_syscalib(काष्ठा iio_dev *indio_dev,
				     uपूर्णांकptr_t निजी,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad7192_state *st = iio_priv(indio_dev);
	bool sys_calib;
	पूर्णांक ret, temp;

	ret = strtobool(buf, &sys_calib);
	अगर (ret)
		वापस ret;

	temp = st->syscalib_mode[chan->channel];
	अगर (sys_calib) अणु
		अगर (temp == AD7192_SYSCALIB_ZERO_SCALE)
			ret = ad_sd_calibrate(&st->sd, AD7192_MODE_CAL_SYS_ZERO,
					      chan->address);
		अन्यथा
			ret = ad_sd_calibrate(&st->sd, AD7192_MODE_CAL_SYS_FULL,
					      chan->address);
	पूर्ण

	वापस ret ? ret : len;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad7192_syscalib_mode_क्रमागत = अणु
	.items = ad7192_syscalib_modes,
	.num_items = ARRAY_SIZE(ad7192_syscalib_modes),
	.set = ad7192_set_syscalib_mode,
	.get = ad7192_get_syscalib_mode
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad7192_calibsys_ext_info[] = अणु
	अणु
		.name = "sys_calibration",
		.ग_लिखो = ad7192_ग_लिखो_syscalib,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("sys_calibration_mode", IIO_SEPARATE,
		 &ad7192_syscalib_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("sys_calibration_mode", &ad7192_syscalib_mode_क्रमागत),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ad7192_state *ad_sigma_delta_to_ad7192(काष्ठा ad_sigma_delta *sd)
अणु
	वापस container_of(sd, काष्ठा ad7192_state, sd);
पूर्ण

अटल पूर्णांक ad7192_set_channel(काष्ठा ad_sigma_delta *sd, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा ad7192_state *st = ad_sigma_delta_to_ad7192(sd);

	st->conf &= ~AD7192_CONF_CHAN_MASK;
	st->conf |= AD7192_CONF_CHAN(channel);

	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_CONF, 3, st->conf);
पूर्ण

अटल पूर्णांक ad7192_set_mode(काष्ठा ad_sigma_delta *sd,
			   क्रमागत ad_sigma_delta_mode mode)
अणु
	काष्ठा ad7192_state *st = ad_sigma_delta_to_ad7192(sd);

	st->mode &= ~AD7192_MODE_SEL_MASK;
	st->mode |= AD7192_MODE_SEL(mode);

	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
पूर्ण

अटल स्थिर काष्ठा ad_sigma_delta_info ad7192_sigma_delta_info = अणु
	.set_channel = ad7192_set_channel,
	.set_mode = ad7192_set_mode,
	.has_रेजिस्टरs = true,
	.addr_shअगरt = 3,
	.पढ़ो_mask = BIT(6),
पूर्ण;

अटल स्थिर काष्ठा ad_sd_calib_data ad7192_calib_arr[8] = अणु
	अणुAD7192_MODE_CAL_INT_ZERO, AD7192_CH_AIN1पूर्ण,
	अणुAD7192_MODE_CAL_INT_FULL, AD7192_CH_AIN1पूर्ण,
	अणुAD7192_MODE_CAL_INT_ZERO, AD7192_CH_AIN2पूर्ण,
	अणुAD7192_MODE_CAL_INT_FULL, AD7192_CH_AIN2पूर्ण,
	अणुAD7192_MODE_CAL_INT_ZERO, AD7192_CH_AIN3पूर्ण,
	अणुAD7192_MODE_CAL_INT_FULL, AD7192_CH_AIN3पूर्ण,
	अणुAD7192_MODE_CAL_INT_ZERO, AD7192_CH_AIN4पूर्ण,
	अणुAD7192_MODE_CAL_INT_FULL, AD7192_CH_AIN4पूर्ण
पूर्ण;

अटल पूर्णांक ad7192_calibrate_all(काष्ठा ad7192_state *st)
अणु
	वापस ad_sd_calibrate_all(&st->sd, ad7192_calib_arr,
				   ARRAY_SIZE(ad7192_calib_arr));
पूर्ण

अटल अंतरभूत bool ad7192_valid_बाह्यal_frequency(u32 freq)
अणु
	वापस (freq >= AD7192_EXT_FREQ_MHZ_MIN &&
		freq <= AD7192_EXT_FREQ_MHZ_MAX);
पूर्ण

अटल पूर्णांक ad7192_of_घड़ी_select(काष्ठा ad7192_state *st)
अणु
	काष्ठा device_node *np = st->sd.spi->dev.of_node;
	अचिन्हित पूर्णांक घड़ी_sel;

	घड़ी_sel = AD7192_CLK_INT;

	/* use पूर्णांकernal घड़ी */
	अगर (PTR_ERR(st->mclk) == -ENOENT) अणु
		अगर (of_property_पढ़ो_bool(np, "adi,int-clock-output-enable"))
			घड़ी_sel = AD7192_CLK_INT_CO;
	पूर्ण अन्यथा अणु
		अगर (of_property_पढ़ो_bool(np, "adi,clock-xtal"))
			घड़ी_sel = AD7192_CLK_EXT_MCLK1_2;
		अन्यथा
			घड़ी_sel = AD7192_CLK_EXT_MCLK2;
	पूर्ण

	वापस घड़ी_sel;
पूर्ण

अटल पूर्णांक ad7192_setup(काष्ठा ad7192_state *st, काष्ठा device_node *np)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(st->sd.spi);
	bool rej60_en, refin2_en;
	bool buf_en, bipolar, burnout_curr_en;
	अचिन्हित दीर्घ दीर्घ scale_uv;
	पूर्णांक i, ret, id;

	/* reset the serial पूर्णांकerface */
	ret = ad_sd_reset(&st->sd, 48);
	अगर (ret < 0)
		वापस ret;
	usleep_range(500, 1000); /* Wait क्रम at least 500us */

	/* ग_लिखो/पढ़ो test क्रम device presence */
	ret = ad_sd_पढ़ो_reg(&st->sd, AD7192_REG_ID, 1, &id);
	अगर (ret)
		वापस ret;

	id &= AD7192_ID_MASK;

	अगर (id != st->chip_info->chip_id)
		dev_warn(&st->sd.spi->dev, "device ID query failed (0x%X)\n",
			 id);

	st->mode = AD7192_MODE_SEL(AD7192_MODE_IDLE) |
		AD7192_MODE_CLKSRC(st->घड़ी_sel) |
		AD7192_MODE_RATE(480);

	st->conf = AD7192_CONF_GAIN(0);

	rej60_en = of_property_पढ़ो_bool(np, "adi,rejection-60-Hz-enable");
	अगर (rej60_en)
		st->mode |= AD7192_MODE_REJ60;

	refin2_en = of_property_पढ़ो_bool(np, "adi,refin2-pins-enable");
	अगर (refin2_en && st->chip_info->chip_id != CHIPID_AD7195)
		st->conf |= AD7192_CONF_REFSEL;

	st->conf &= ~AD7192_CONF_CHOP;
	st->f_order = AD7192_NO_SYNC_FILTER;

	buf_en = of_property_पढ़ो_bool(np, "adi,buffer-enable");
	अगर (buf_en)
		st->conf |= AD7192_CONF_BUF;

	bipolar = of_property_पढ़ो_bool(np, "bipolar");
	अगर (!bipolar)
		st->conf |= AD7192_CONF_UNIPOLAR;

	burnout_curr_en = of_property_पढ़ो_bool(np,
						"adi,burnout-currents-enable");
	अगर (burnout_curr_en && buf_en) अणु
		st->conf |= AD7192_CONF_BURN;
	पूर्ण अन्यथा अगर (burnout_curr_en) अणु
		dev_warn(&st->sd.spi->dev,
			 "Can't enable burnout currents: see CHOP or buffer\n");
	पूर्ण

	ret = ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
	अगर (ret)
		वापस ret;

	ret = ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_CONF, 3, st->conf);
	अगर (ret)
		वापस ret;

	ret = ad7192_calibrate_all(st);
	अगर (ret)
		वापस ret;

	/* Populate available ADC input ranges */
	क्रम (i = 0; i < ARRAY_SIZE(st->scale_avail); i++) अणु
		scale_uv = ((u64)st->पूर्णांक_vref_mv * 100000000)
			>> (indio_dev->channels[0].scan_type.realbits -
			((st->conf & AD7192_CONF_UNIPOLAR) ? 0 : 1));
		scale_uv >>= i;

		st->scale_avail[i][1] = करो_भाग(scale_uv, 100000000) * 10;
		st->scale_avail[i][0] = scale_uv;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ad7192_show_ac_excitation(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7192_state *st = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d\n", !!(st->mode & AD7192_MODE_ACX));
पूर्ण

अटल sमाप_प्रकार ad7192_show_bridge_चयन(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7192_state *st = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d\n", !!(st->gpocon & AD7192_GPOCON_BPDSW));
पूर्ण

अटल sमाप_प्रकार ad7192_set(काष्ठा device *dev,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf,
			  माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7192_state *st = iio_priv(indio_dev);
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	पूर्णांक ret;
	bool val;

	ret = strtobool(buf, &val);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन ((u32)this_attr->address) अणु
	हाल AD7192_REG_GPOCON:
		अगर (val)
			st->gpocon |= AD7192_GPOCON_BPDSW;
		अन्यथा
			st->gpocon &= ~AD7192_GPOCON_BPDSW;

		ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_GPOCON, 1, st->gpocon);
		अवरोध;
	हाल AD7192_REG_MODE:
		अगर (val)
			st->mode |= AD7192_MODE_ACX;
		अन्यथा
			st->mode &= ~AD7192_MODE_ACX;

		ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	iio_device_release_direct_mode(indio_dev);

	वापस ret ? ret : len;
पूर्ण

अटल व्योम ad7192_get_available_filter_freq(काष्ठा ad7192_state *st,
						    पूर्णांक *freq)
अणु
	अचिन्हित पूर्णांक fadc;

	/* Formulas क्रम filter at page 25 of the datasheet */
	fadc = DIV_ROUND_CLOSEST(st->fclk,
				 AD7192_SYNC4_FILTER * AD7192_MODE_RATE(st->mode));
	freq[0] = DIV_ROUND_CLOSEST(fadc * 240, 1024);

	fadc = DIV_ROUND_CLOSEST(st->fclk,
				 AD7192_SYNC3_FILTER * AD7192_MODE_RATE(st->mode));
	freq[1] = DIV_ROUND_CLOSEST(fadc * 240, 1024);

	fadc = DIV_ROUND_CLOSEST(st->fclk, AD7192_MODE_RATE(st->mode));
	freq[2] = DIV_ROUND_CLOSEST(fadc * 230, 1024);
	freq[3] = DIV_ROUND_CLOSEST(fadc * 272, 1024);
पूर्ण

अटल sमाप_प्रकार ad7192_show_filter_avail(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7192_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक freq_avail[4], i;
	माप_प्रकार len = 0;

	ad7192_get_available_filter_freq(st, freq_avail);

	क्रम (i = 0; i < ARRAY_SIZE(freq_avail); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
				 "%d.%d ", freq_avail[i] / 1000,
				 freq_avail[i] % 1000);

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(filter_low_pass_3db_frequency_available,
		       0444, ad7192_show_filter_avail, शून्य, 0);

अटल IIO_DEVICE_ATTR(bridge_चयन_en, 0644,
		       ad7192_show_bridge_चयन, ad7192_set,
		       AD7192_REG_GPOCON);

अटल IIO_DEVICE_ATTR(ac_excitation_en, 0644,
		       ad7192_show_ac_excitation, ad7192_set,
		       AD7192_REG_MODE);

अटल काष्ठा attribute *ad7192_attributes[] = अणु
	&iio_dev_attr_filter_low_pass_3db_frequency_available.dev_attr.attr,
	&iio_dev_attr_bridge_चयन_en.dev_attr.attr,
	&iio_dev_attr_ac_excitation_en.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7192_attribute_group = अणु
	.attrs = ad7192_attributes,
पूर्ण;

अटल काष्ठा attribute *ad7195_attributes[] = अणु
	&iio_dev_attr_filter_low_pass_3db_frequency_available.dev_attr.attr,
	&iio_dev_attr_bridge_चयन_en.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7195_attribute_group = अणु
	.attrs = ad7195_attributes,
पूर्ण;

अटल अचिन्हित पूर्णांक ad7192_get_temp_scale(bool unipolar)
अणु
	वापस unipolar ? 2815 * 2 : 2815;
पूर्ण

अटल पूर्णांक ad7192_set_3db_filter_freq(काष्ठा ad7192_state *st,
				      पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक freq_avail[4], i, ret, freq;
	अचिन्हित पूर्णांक dअगरf_new, dअगरf_old;
	पूर्णांक idx = 0;

	dअगरf_old = U32_MAX;
	freq = val * 1000 + val2;

	ad7192_get_available_filter_freq(st, freq_avail);

	क्रम (i = 0; i < ARRAY_SIZE(freq_avail); i++) अणु
		dअगरf_new = असल(freq - freq_avail[i]);
		अगर (dअगरf_new < dअगरf_old) अणु
			dअगरf_old = dअगरf_new;
			idx = i;
		पूर्ण
	पूर्ण

	चयन (idx) अणु
	हाल 0:
		st->f_order = AD7192_SYNC4_FILTER;
		st->mode &= ~AD7192_MODE_SINC3;

		st->conf |= AD7192_CONF_CHOP;
		अवरोध;
	हाल 1:
		st->f_order = AD7192_SYNC3_FILTER;
		st->mode |= AD7192_MODE_SINC3;

		st->conf |= AD7192_CONF_CHOP;
		अवरोध;
	हाल 2:
		st->f_order = AD7192_NO_SYNC_FILTER;
		st->mode &= ~AD7192_MODE_SINC3;

		st->conf &= ~AD7192_CONF_CHOP;
		अवरोध;
	हाल 3:
		st->f_order = AD7192_NO_SYNC_FILTER;
		st->mode |= AD7192_MODE_SINC3;

		st->conf &= ~AD7192_CONF_CHOP;
		अवरोध;
	पूर्ण

	ret = ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
	अगर (ret < 0)
		वापस ret;

	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_CONF, 3, st->conf);
पूर्ण

अटल पूर्णांक ad7192_get_3db_filter_freq(काष्ठा ad7192_state *st)
अणु
	अचिन्हित पूर्णांक fadc;

	fadc = DIV_ROUND_CLOSEST(st->fclk,
				 st->f_order * AD7192_MODE_RATE(st->mode));

	अगर (st->conf & AD7192_CONF_CHOP)
		वापस DIV_ROUND_CLOSEST(fadc * 240, 1024);
	अगर (st->mode & AD7192_MODE_SINC3)
		वापस DIV_ROUND_CLOSEST(fadc * 272, 1024);
	अन्यथा
		वापस DIV_ROUND_CLOSEST(fadc * 230, 1024);
पूर्ण

अटल पूर्णांक ad7192_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad7192_state *st = iio_priv(indio_dev);
	bool unipolar = !!(st->conf & AD7192_CONF_UNIPOLAR);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस ad_sigma_delta_single_conversion(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			mutex_lock(&st->lock);
			*val = st->scale_avail[AD7192_CONF_GAIN(st->conf)][0];
			*val2 = st->scale_avail[AD7192_CONF_GAIN(st->conf)][1];
			mutex_unlock(&st->lock);
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_TEMP:
			*val = 0;
			*val2 = 1000000000 / ad7192_get_temp_scale(unipolar);
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (!unipolar)
			*val = -(1 << (chan->scan_type.realbits - 1));
		अन्यथा
			*val = 0;
		/* Kelvin to Celsius */
		अगर (chan->type == IIO_TEMP)
			*val -= 273 * ad7192_get_temp_scale(unipolar);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->fclk /
			(st->f_order * 1024 * AD7192_MODE_RATE(st->mode));
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		*val = ad7192_get_3db_filter_freq(st);
		*val2 = 1000;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad7192_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा ad7192_state *st = iio_priv(indio_dev);
	पूर्णांक ret, i, भाग;
	अचिन्हित पूर्णांक पंचांगp;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		ret = -EINVAL;
		mutex_lock(&st->lock);
		क्रम (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
			अगर (val2 == st->scale_avail[i][1]) अणु
				ret = 0;
				पंचांगp = st->conf;
				st->conf &= ~AD7192_CONF_GAIN(-1);
				st->conf |= AD7192_CONF_GAIN(i);
				अगर (पंचांगp == st->conf)
					अवरोध;
				ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_CONF,
						3, st->conf);
				ad7192_calibrate_all(st);
				अवरोध;
			पूर्ण
		mutex_unlock(&st->lock);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (!val) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		भाग = st->fclk / (val * st->f_order * 1024);
		अगर (भाग < 1 || भाग > 1023) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		st->mode &= ~AD7192_MODE_RATE(-1);
		st->mode |= AD7192_MODE_RATE(भाग);
		ad_sd_ग_लिखो_reg(&st->sd, AD7192_REG_MODE, 3, st->mode);
		अवरोध;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		ret = ad7192_set_3db_filter_freq(st, val, val2 / 1000);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	iio_device_release_direct_mode(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7192_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7192_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	काष्ठा ad7192_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		*vals = (पूर्णांक *)st->scale_avail;
		*type = IIO_VAL_INT_PLUS_न_अंकO;
		/* Values are stored in a 2D matrix  */
		*length = ARRAY_SIZE(st->scale_avail) * 2;

		वापस IIO_AVAIL_LIST;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7192_info = अणु
	.पढ़ो_raw = ad7192_पढ़ो_raw,
	.ग_लिखो_raw = ad7192_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = ad7192_ग_लिखो_raw_get_fmt,
	.पढ़ो_avail = ad7192_पढ़ो_avail,
	.attrs = &ad7192_attribute_group,
	.validate_trigger = ad_sd_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7195_info = अणु
	.पढ़ो_raw = ad7192_पढ़ो_raw,
	.ग_लिखो_raw = ad7192_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = ad7192_ग_लिखो_raw_get_fmt,
	.पढ़ो_avail = ad7192_पढ़ो_avail,
	.attrs = &ad7195_attribute_group,
	.validate_trigger = ad_sd_validate_trigger,
पूर्ण;

#घोषणा __AD719x_CHANNEL(_si, _channel1, _channel2, _address, _extend_name, \
	_type, _mask_type_av, _ext_info) \
	अणु \
		.type = (_type), \
		.dअगरferential = ((_channel2) == -1 ? 0 : 1), \
		.indexed = 1, \
		.channel = (_channel1), \
		.channel2 = (_channel2), \
		.address = (_address), \
		.extend_name = (_extend_name), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
			BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
		.info_mask_shared_by_type_available = (_mask_type_av), \
		.ext_info = (_ext_info), \
		.scan_index = (_si), \
		.scan_type = अणु \
			.sign = 'u', \
			.realbits = 24, \
			.storagebits = 32, \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

#घोषणा AD719x_DIFF_CHANNEL(_si, _channel1, _channel2, _address) \
	__AD719x_CHANNEL(_si, _channel1, _channel2, _address, शून्य, \
		IIO_VOLTAGE, BIT(IIO_CHAN_INFO_SCALE), \
		ad7192_calibsys_ext_info)

#घोषणा AD719x_CHANNEL(_si, _channel1, _address) \
	__AD719x_CHANNEL(_si, _channel1, -1, _address, शून्य, IIO_VOLTAGE, \
		BIT(IIO_CHAN_INFO_SCALE), ad7192_calibsys_ext_info)

#घोषणा AD719x_SHORTED_CHANNEL(_si, _channel1, _address) \
	__AD719x_CHANNEL(_si, _channel1, -1, _address, "shorted", IIO_VOLTAGE, \
		BIT(IIO_CHAN_INFO_SCALE), ad7192_calibsys_ext_info)

#घोषणा AD719x_TEMP_CHANNEL(_si, _address) \
	__AD719x_CHANNEL(_si, 0, -1, _address, शून्य, IIO_TEMP, 0, शून्य)

अटल स्थिर काष्ठा iio_chan_spec ad7192_channels[] = अणु
	AD719x_DIFF_CHANNEL(0, 1, 2, AD7192_CH_AIN1P_AIN2M),
	AD719x_DIFF_CHANNEL(1, 3, 4, AD7192_CH_AIN3P_AIN4M),
	AD719x_TEMP_CHANNEL(2, AD7192_CH_TEMP),
	AD719x_SHORTED_CHANNEL(3, 2, AD7192_CH_AIN2P_AIN2M),
	AD719x_CHANNEL(4, 1, AD7192_CH_AIN1),
	AD719x_CHANNEL(5, 2, AD7192_CH_AIN2),
	AD719x_CHANNEL(6, 3, AD7192_CH_AIN3),
	AD719x_CHANNEL(7, 4, AD7192_CH_AIN4),
	IIO_CHAN_SOFT_TIMESTAMP(8),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7193_channels[] = अणु
	AD719x_DIFF_CHANNEL(0, 1, 2, AD7193_CH_AIN1P_AIN2M),
	AD719x_DIFF_CHANNEL(1, 3, 4, AD7193_CH_AIN3P_AIN4M),
	AD719x_DIFF_CHANNEL(2, 5, 6, AD7193_CH_AIN5P_AIN6M),
	AD719x_DIFF_CHANNEL(3, 7, 8, AD7193_CH_AIN7P_AIN8M),
	AD719x_TEMP_CHANNEL(4, AD7193_CH_TEMP),
	AD719x_SHORTED_CHANNEL(5, 2, AD7193_CH_AIN2P_AIN2M),
	AD719x_CHANNEL(6, 1, AD7193_CH_AIN1),
	AD719x_CHANNEL(7, 2, AD7193_CH_AIN2),
	AD719x_CHANNEL(8, 3, AD7193_CH_AIN3),
	AD719x_CHANNEL(9, 4, AD7193_CH_AIN4),
	AD719x_CHANNEL(10, 5, AD7193_CH_AIN5),
	AD719x_CHANNEL(11, 6, AD7193_CH_AIN6),
	AD719x_CHANNEL(12, 7, AD7193_CH_AIN7),
	AD719x_CHANNEL(13, 8, AD7193_CH_AIN8),
	IIO_CHAN_SOFT_TIMESTAMP(14),
पूर्ण;

अटल स्थिर काष्ठा ad7192_chip_info ad7192_chip_info_tbl[] = अणु
	[ID_AD7190] = अणु
		.chip_id = CHIPID_AD7190,
		.name = "ad7190",
	पूर्ण,
	[ID_AD7192] = अणु
		.chip_id = CHIPID_AD7192,
		.name = "ad7192",
	पूर्ण,
	[ID_AD7193] = अणु
		.chip_id = CHIPID_AD7193,
		.name = "ad7193",
	पूर्ण,
	[ID_AD7195] = अणु
		.chip_id = CHIPID_AD7195,
		.name = "ad7195",
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad7192_channels_config(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7192_state *st = iio_priv(indio_dev);

	चयन (st->chip_info->chip_id) अणु
	हाल CHIPID_AD7193:
		indio_dev->channels = ad7193_channels;
		indio_dev->num_channels = ARRAY_SIZE(ad7193_channels);
		अवरोध;
	शेष:
		indio_dev->channels = ad7192_channels;
		indio_dev->num_channels = ARRAY_SIZE(ad7192_channels);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7192_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7192_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	अगर (!spi->irq) अणु
		dev_err(&spi->dev, "no IRQ?\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	mutex_init(&st->lock);

	st->avdd = devm_regulator_get(&spi->dev, "avdd");
	अगर (IS_ERR(st->avdd))
		वापस PTR_ERR(st->avdd);

	ret = regulator_enable(st->avdd);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable specified AVdd supply\n");
		वापस ret;
	पूर्ण

	st->dvdd = devm_regulator_get(&spi->dev, "dvdd");
	अगर (IS_ERR(st->dvdd)) अणु
		ret = PTR_ERR(st->dvdd);
		जाओ error_disable_avdd;
	पूर्ण

	ret = regulator_enable(st->dvdd);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable specified DVdd supply\n");
		जाओ error_disable_avdd;
	पूर्ण

	ret = regulator_get_voltage(st->avdd);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Device tree error, reference voltage undefined\n");
		जाओ error_disable_avdd;
	पूर्ण
	st->पूर्णांक_vref_mv = ret / 1000;

	spi_set_drvdata(spi, indio_dev);
	st->chip_info = of_device_get_match_data(&spi->dev);
	indio_dev->name = st->chip_info->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = ad7192_channels_config(indio_dev);
	अगर (ret < 0)
		जाओ error_disable_dvdd;

	अगर (st->chip_info->chip_id == CHIPID_AD7195)
		indio_dev->info = &ad7195_info;
	अन्यथा
		indio_dev->info = &ad7192_info;

	ad_sd_init(&st->sd, indio_dev, spi, &ad7192_sigma_delta_info);

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	अगर (ret)
		जाओ error_disable_dvdd;

	st->fclk = AD7192_INT_FREQ_MHZ;

	st->mclk = devm_clk_get(&st->sd.spi->dev, "mclk");
	अगर (IS_ERR(st->mclk) && PTR_ERR(st->mclk) != -ENOENT) अणु
		ret = PTR_ERR(st->mclk);
		जाओ error_हटाओ_trigger;
	पूर्ण

	st->घड़ी_sel = ad7192_of_घड़ी_select(st);

	अगर (st->घड़ी_sel == AD7192_CLK_EXT_MCLK1_2 ||
	    st->घड़ी_sel == AD7192_CLK_EXT_MCLK2) अणु
		ret = clk_prepare_enable(st->mclk);
		अगर (ret < 0)
			जाओ error_हटाओ_trigger;

		st->fclk = clk_get_rate(st->mclk);
		अगर (!ad7192_valid_बाह्यal_frequency(st->fclk)) अणु
			ret = -EINVAL;
			dev_err(&spi->dev,
				"External clock frequency out of bounds\n");
			जाओ error_disable_clk;
		पूर्ण
	पूर्ण

	ret = ad7192_setup(st, spi->dev.of_node);
	अगर (ret)
		जाओ error_disable_clk;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ error_disable_clk;
	वापस 0;

error_disable_clk:
	अगर (st->घड़ी_sel == AD7192_CLK_EXT_MCLK1_2 ||
	    st->घड़ी_sel == AD7192_CLK_EXT_MCLK2)
		clk_disable_unprepare(st->mclk);
error_हटाओ_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_disable_dvdd:
	regulator_disable(st->dvdd);
error_disable_avdd:
	regulator_disable(st->avdd);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7192_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7192_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (st->घड़ी_sel == AD7192_CLK_EXT_MCLK1_2 ||
	    st->घड़ी_sel == AD7192_CLK_EXT_MCLK2)
		clk_disable_unprepare(st->mclk);
	ad_sd_cleanup_buffer_and_trigger(indio_dev);

	regulator_disable(st->dvdd);
	regulator_disable(st->avdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ad7192_of_match[] = अणु
	अणु .compatible = "adi,ad7190", .data = &ad7192_chip_info_tbl[ID_AD7190] पूर्ण,
	अणु .compatible = "adi,ad7192", .data = &ad7192_chip_info_tbl[ID_AD7192] पूर्ण,
	अणु .compatible = "adi,ad7193", .data = &ad7192_chip_info_tbl[ID_AD7193] पूर्ण,
	अणु .compatible = "adi,ad7195", .data = &ad7192_chip_info_tbl[ID_AD7195] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7192_of_match);

अटल काष्ठा spi_driver ad7192_driver = अणु
	.driver = अणु
		.name	= "ad7192",
		.of_match_table = ad7192_of_match,
	पूर्ण,
	.probe		= ad7192_probe,
	.हटाओ		= ad7192_हटाओ,
पूर्ण;
module_spi_driver(ad7192_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7190, AD7192, AD7193, AD7195 ADC");
MODULE_LICENSE("GPL v2");
