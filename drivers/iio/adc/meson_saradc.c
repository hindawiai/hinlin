<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Amlogic Meson Successive Approximation Register (SAR) A/D Converter
 *
 * Copyright (C) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mfd/syscon.h>

#घोषणा MESON_SAR_ADC_REG0					0x00
	#घोषणा MESON_SAR_ADC_REG0_PANEL_DETECT			BIT(31)
	#घोषणा MESON_SAR_ADC_REG0_BUSY_MASK			GENMASK(30, 28)
	#घोषणा MESON_SAR_ADC_REG0_DELTA_BUSY			BIT(30)
	#घोषणा MESON_SAR_ADC_REG0_AVG_BUSY			BIT(29)
	#घोषणा MESON_SAR_ADC_REG0_SAMPLE_BUSY			BIT(28)
	#घोषणा MESON_SAR_ADC_REG0_FIFO_FULL			BIT(27)
	#घोषणा MESON_SAR_ADC_REG0_FIFO_EMPTY			BIT(26)
	#घोषणा MESON_SAR_ADC_REG0_FIFO_COUNT_MASK		GENMASK(25, 21)
	#घोषणा MESON_SAR_ADC_REG0_ADC_BIAS_CTRL_MASK		GENMASK(20, 19)
	#घोषणा MESON_SAR_ADC_REG0_CURR_CHAN_ID_MASK		GENMASK(18, 16)
	#घोषणा MESON_SAR_ADC_REG0_ADC_TEMP_SEN_SEL		BIT(15)
	#घोषणा MESON_SAR_ADC_REG0_SAMPLING_STOP		BIT(14)
	#घोषणा MESON_SAR_ADC_REG0_CHAN_DELTA_EN_MASK		GENMASK(13, 12)
	#घोषणा MESON_SAR_ADC_REG0_DETECT_IRQ_POL		BIT(10)
	#घोषणा MESON_SAR_ADC_REG0_DETECT_IRQ_EN		BIT(9)
	#घोषणा MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK		GENMASK(8, 4)
	#घोषणा MESON_SAR_ADC_REG0_FIFO_IRQ_EN			BIT(3)
	#घोषणा MESON_SAR_ADC_REG0_SAMPLING_START		BIT(2)
	#घोषणा MESON_SAR_ADC_REG0_CONTINUOUS_EN		BIT(1)
	#घोषणा MESON_SAR_ADC_REG0_SAMPLE_ENGINE_ENABLE		BIT(0)

#घोषणा MESON_SAR_ADC_CHAN_LIST					0x04
	#घोषणा MESON_SAR_ADC_CHAN_LIST_MAX_INDEX_MASK		GENMASK(26, 24)
	#घोषणा MESON_SAR_ADC_CHAN_LIST_ENTRY_MASK(_chan)	\
					(GENMASK(2, 0) << ((_chan) * 3))

#घोषणा MESON_SAR_ADC_AVG_CNTL					0x08
	#घोषणा MESON_SAR_ADC_AVG_CNTL_AVG_MODE_SHIFT(_chan)	\
					(16 + ((_chan) * 2))
	#घोषणा MESON_SAR_ADC_AVG_CNTL_AVG_MODE_MASK(_chan)	\
					(GENMASK(17, 16) << ((_chan) * 2))
	#घोषणा MESON_SAR_ADC_AVG_CNTL_NUM_SAMPLES_SHIFT(_chan)	\
					(0 + ((_chan) * 2))
	#घोषणा MESON_SAR_ADC_AVG_CNTL_NUM_SAMPLES_MASK(_chan)	\
					(GENMASK(1, 0) << ((_chan) * 2))

#घोषणा MESON_SAR_ADC_REG3					0x0c
	#घोषणा MESON_SAR_ADC_REG3_CNTL_USE_SC_DLY		BIT(31)
	#घोषणा MESON_SAR_ADC_REG3_CLK_EN			BIT(30)
	#घोषणा MESON_SAR_ADC_REG3_BL30_INITIALIZED		BIT(28)
	#घोषणा MESON_SAR_ADC_REG3_CTRL_CONT_RING_COUNTER_EN	BIT(27)
	#घोषणा MESON_SAR_ADC_REG3_CTRL_SAMPLING_CLOCK_PHASE	BIT(26)
	#घोषणा MESON_SAR_ADC_REG3_CTRL_CHAN7_MUX_SEL_MASK	GENMASK(25, 23)
	#घोषणा MESON_SAR_ADC_REG3_DETECT_EN			BIT(22)
	#घोषणा MESON_SAR_ADC_REG3_ADC_EN			BIT(21)
	#घोषणा MESON_SAR_ADC_REG3_PANEL_DETECT_COUNT_MASK	GENMASK(20, 18)
	#घोषणा MESON_SAR_ADC_REG3_PANEL_DETECT_FILTER_TB_MASK	GENMASK(17, 16)
	#घोषणा MESON_SAR_ADC_REG3_ADC_CLK_DIV_SHIFT		10
	#घोषणा MESON_SAR_ADC_REG3_ADC_CLK_DIV_WIDTH		5
	#घोषणा MESON_SAR_ADC_REG3_BLOCK_DLY_SEL_MASK		GENMASK(9, 8)
	#घोषणा MESON_SAR_ADC_REG3_BLOCK_DLY_MASK		GENMASK(7, 0)

#घोषणा MESON_SAR_ADC_DELAY					0x10
	#घोषणा MESON_SAR_ADC_DELAY_INPUT_DLY_SEL_MASK		GENMASK(25, 24)
	#घोषणा MESON_SAR_ADC_DELAY_BL30_BUSY			BIT(15)
	#घोषणा MESON_SAR_ADC_DELAY_KERNEL_BUSY			BIT(14)
	#घोषणा MESON_SAR_ADC_DELAY_INPUT_DLY_CNT_MASK		GENMASK(23, 16)
	#घोषणा MESON_SAR_ADC_DELAY_SAMPLE_DLY_SEL_MASK		GENMASK(9, 8)
	#घोषणा MESON_SAR_ADC_DELAY_SAMPLE_DLY_CNT_MASK		GENMASK(7, 0)

#घोषणा MESON_SAR_ADC_LAST_RD					0x14
	#घोषणा MESON_SAR_ADC_LAST_RD_LAST_CHANNEL1_MASK	GENMASK(23, 16)
	#घोषणा MESON_SAR_ADC_LAST_RD_LAST_CHANNEL0_MASK	GENMASK(9, 0)

#घोषणा MESON_SAR_ADC_FIFO_RD					0x18
	#घोषणा MESON_SAR_ADC_FIFO_RD_CHAN_ID_MASK		GENMASK(14, 12)
	#घोषणा MESON_SAR_ADC_FIFO_RD_SAMPLE_VALUE_MASK		GENMASK(11, 0)

#घोषणा MESON_SAR_ADC_AUX_SW					0x1c
	#घोषणा MESON_SAR_ADC_AUX_SW_MUX_SEL_CHAN_SHIFT(_chan)	\
					(8 + (((_chan) - 2) * 3))
	#घोषणा MESON_SAR_ADC_AUX_SW_VREF_P_MUX			BIT(6)
	#घोषणा MESON_SAR_ADC_AUX_SW_VREF_N_MUX			BIT(5)
	#घोषणा MESON_SAR_ADC_AUX_SW_MODE_SEL			BIT(4)
	#घोषणा MESON_SAR_ADC_AUX_SW_YP_DRIVE_SW		BIT(3)
	#घोषणा MESON_SAR_ADC_AUX_SW_XP_DRIVE_SW		BIT(2)
	#घोषणा MESON_SAR_ADC_AUX_SW_YM_DRIVE_SW		BIT(1)
	#घोषणा MESON_SAR_ADC_AUX_SW_XM_DRIVE_SW		BIT(0)

#घोषणा MESON_SAR_ADC_CHAN_10_SW				0x20
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_MUX_SEL_MASK	GENMASK(25, 23)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_VREF_P_MUX	BIT(22)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_VREF_N_MUX	BIT(21)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_MODE_SEL		BIT(20)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_YP_DRIVE_SW	BIT(19)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_XP_DRIVE_SW	BIT(18)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_YM_DRIVE_SW	BIT(17)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN1_XM_DRIVE_SW	BIT(16)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_MUX_SEL_MASK	GENMASK(9, 7)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_VREF_P_MUX	BIT(6)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_VREF_N_MUX	BIT(5)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_MODE_SEL		BIT(4)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_YP_DRIVE_SW	BIT(3)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_XP_DRIVE_SW	BIT(2)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_YM_DRIVE_SW	BIT(1)
	#घोषणा MESON_SAR_ADC_CHAN_10_SW_CHAN0_XM_DRIVE_SW	BIT(0)

#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW				0x24
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_SW_EN	BIT(26)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_MUX_MASK	GENMASK(25, 23)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_VREF_P_MUX	BIT(22)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_VREF_N_MUX	BIT(21)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_MODE_SEL	BIT(20)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_YP_DRIVE_SW	BIT(19)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_XP_DRIVE_SW	BIT(18)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_YM_DRIVE_SW	BIT(17)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_XM_DRIVE_SW	BIT(16)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_MUX_SEL_MASK	GENMASK(9, 7)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_VREF_P_MUX	BIT(6)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_VREF_N_MUX	BIT(5)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_MODE_SEL	BIT(4)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_YP_DRIVE_SW	BIT(3)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_XP_DRIVE_SW	BIT(2)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_YM_DRIVE_SW	BIT(1)
	#घोषणा MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_XM_DRIVE_SW	BIT(0)

#घोषणा MESON_SAR_ADC_DELTA_10					0x28
	#घोषणा MESON_SAR_ADC_DELTA_10_TEMP_SEL			BIT(27)
	#घोषणा MESON_SAR_ADC_DELTA_10_TS_REVE1			BIT(26)
	#घोषणा MESON_SAR_ADC_DELTA_10_CHAN1_DELTA_VALUE_MASK	GENMASK(25, 16)
	#घोषणा MESON_SAR_ADC_DELTA_10_TS_REVE0			BIT(15)
	#घोषणा MESON_SAR_ADC_DELTA_10_TS_C_MASK		GENMASK(14, 11)
	#घोषणा MESON_SAR_ADC_DELTA_10_TS_VBG_EN		BIT(10)
	#घोषणा MESON_SAR_ADC_DELTA_10_CHAN0_DELTA_VALUE_MASK	GENMASK(9, 0)

/*
 * NOTE: रेजिस्टरs from here are unकरोcumented (the venकरोr Linux kernel driver
 * and u-boot source served as reference). These only seem to be relevant on
 * GXBB and newer.
 */
#घोषणा MESON_SAR_ADC_REG11					0x2c
	#घोषणा MESON_SAR_ADC_REG11_BANDGAP_EN			BIT(13)

#घोषणा MESON_SAR_ADC_REG13					0x34
	#घोषणा MESON_SAR_ADC_REG13_12BIT_CALIBRATION_MASK	GENMASK(13, 8)

#घोषणा MESON_SAR_ADC_MAX_FIFO_SIZE				32
#घोषणा MESON_SAR_ADC_TIMEOUT					100 /* ms */
#घोषणा MESON_SAR_ADC_VOLTAGE_AND_TEMP_CHANNEL			6
#घोषणा MESON_SAR_ADC_TEMP_OFFSET				27

/* temperature sensor calibration inक्रमmation in eFuse */
#घोषणा MESON_SAR_ADC_EFUSE_BYTES				4
#घोषणा MESON_SAR_ADC_EFUSE_BYTE3_UPPER_ADC_VAL			GENMASK(6, 0)
#घोषणा MESON_SAR_ADC_EFUSE_BYTE3_IS_CALIBRATED			BIT(7)

#घोषणा MESON_HHI_DPLL_TOP_0					0x318
#घोषणा MESON_HHI_DPLL_TOP_0_TSC_BIT4				BIT(9)

/* क्रम use with IIO_VAL_INT_PLUS_MICRO */
#घोषणा MILLION							1000000

#घोषणा MESON_SAR_ADC_CHAN(_chan) अणु					\
	.type = IIO_VOLTAGE,						\
	.indexed = 1,							\
	.channel = _chan,						\
	.address = _chan,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
				BIT(IIO_CHAN_INFO_AVERAGE_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),		\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_CALIBBIAS) |	\
				BIT(IIO_CHAN_INFO_CALIBSCALE),		\
	.datasheet_name = "SAR_ADC_CH"#_chan,				\
पूर्ण

#घोषणा MESON_SAR_ADC_TEMP_CHAN(_chan) अणु				\
	.type = IIO_TEMP,						\
	.channel = _chan,						\
	.address = MESON_SAR_ADC_VOLTAGE_AND_TEMP_CHANNEL,		\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
				BIT(IIO_CHAN_INFO_AVERAGE_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |		\
					BIT(IIO_CHAN_INFO_SCALE),	\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_CALIBBIAS) |	\
				BIT(IIO_CHAN_INFO_CALIBSCALE),		\
	.datasheet_name = "TEMP_SENSOR",				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec meson_sar_adc_iio_channels[] = अणु
	MESON_SAR_ADC_CHAN(0),
	MESON_SAR_ADC_CHAN(1),
	MESON_SAR_ADC_CHAN(2),
	MESON_SAR_ADC_CHAN(3),
	MESON_SAR_ADC_CHAN(4),
	MESON_SAR_ADC_CHAN(5),
	MESON_SAR_ADC_CHAN(6),
	MESON_SAR_ADC_CHAN(7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec meson_sar_adc_and_temp_iio_channels[] = अणु
	MESON_SAR_ADC_CHAN(0),
	MESON_SAR_ADC_CHAN(1),
	MESON_SAR_ADC_CHAN(2),
	MESON_SAR_ADC_CHAN(3),
	MESON_SAR_ADC_CHAN(4),
	MESON_SAR_ADC_CHAN(5),
	MESON_SAR_ADC_CHAN(6),
	MESON_SAR_ADC_CHAN(7),
	MESON_SAR_ADC_TEMP_CHAN(8),
	IIO_CHAN_SOFT_TIMESTAMP(9),
पूर्ण;

क्रमागत meson_sar_adc_avg_mode अणु
	NO_AVERAGING = 0x0,
	MEAN_AVERAGING = 0x1,
	MEDIAN_AVERAGING = 0x2,
पूर्ण;

क्रमागत meson_sar_adc_num_samples अणु
	ONE_SAMPLE = 0x0,
	TWO_SAMPLES = 0x1,
	FOUR_SAMPLES = 0x2,
	EIGHT_SAMPLES = 0x3,
पूर्ण;

क्रमागत meson_sar_adc_chan7_mux_sel अणु
	CHAN7_MUX_VSS = 0x0,
	CHAN7_MUX_VDD_DIV4 = 0x1,
	CHAN7_MUX_VDD_DIV2 = 0x2,
	CHAN7_MUX_VDD_MUL3_DIV4 = 0x3,
	CHAN7_MUX_VDD = 0x4,
	CHAN7_MUX_CH7_INPUT = 0x7,
पूर्ण;

काष्ठा meson_sar_adc_param अणु
	bool					has_bl30_पूर्णांकegration;
	अचिन्हित दीर्घ				घड़ी_rate;
	u32					bandgap_reg;
	अचिन्हित पूर्णांक				resolution;
	स्थिर काष्ठा regmap_config		*regmap_config;
	u8					temperature_trimming_bits;
	अचिन्हित पूर्णांक				temperature_multiplier;
	अचिन्हित पूर्णांक				temperature_भागider;
पूर्ण;

काष्ठा meson_sar_adc_data अणु
	स्थिर काष्ठा meson_sar_adc_param	*param;
	स्थिर अक्षर				*name;
पूर्ण;

काष्ठा meson_sar_adc_priv अणु
	काष्ठा regmap				*regmap;
	काष्ठा regulator			*vref;
	स्थिर काष्ठा meson_sar_adc_param	*param;
	काष्ठा clk				*clkin;
	काष्ठा clk				*core_clk;
	काष्ठा clk				*adc_sel_clk;
	काष्ठा clk				*adc_clk;
	काष्ठा clk_gate				clk_gate;
	काष्ठा clk				*adc_भाग_clk;
	काष्ठा clk_भागider			clk_भाग;
	काष्ठा completion			करोne;
	पूर्णांक					calibbias;
	पूर्णांक					calibscale;
	काष्ठा regmap				*tsc_regmap;
	bool					temperature_sensor_calibrated;
	u8					temperature_sensor_coefficient;
	u16					temperature_sensor_adc_val;
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson_sar_adc_regmap_config_gxbb = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = MESON_SAR_ADC_REG13,
पूर्ण;

अटल स्थिर काष्ठा regmap_config meson_sar_adc_regmap_config_meson8 = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = MESON_SAR_ADC_DELTA_10,
पूर्ण;

अटल अचिन्हित पूर्णांक meson_sar_adc_get_fअगरo_count(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	u32 regval;

	regmap_पढ़ो(priv->regmap, MESON_SAR_ADC_REG0, &regval);

	वापस FIELD_GET(MESON_SAR_ADC_REG0_FIFO_COUNT_MASK, regval);
पूर्ण

अटल पूर्णांक meson_sar_adc_calib_val(काष्ठा iio_dev *indio_dev, पूर्णांक val)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक पंचांगp;

	/* use val_calib = scale * val_raw + offset calibration function */
	पंचांगp = भाग_s64((s64)val * priv->calibscale, MILLION) + priv->calibbias;

	वापस clamp(पंचांगp, 0, (1 << priv->param->resolution) - 1);
पूर्ण

अटल पूर्णांक meson_sar_adc_रुको_busy_clear(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक regval, समयout = 10000;

	/*
	 * NOTE: we need a small delay beक्रमe पढ़ोing the status, otherwise
	 * the sample engine may not have started पूर्णांकernally (which would
	 * seem to us that sampling is alपढ़ोy finished).
	 */
	करो अणु
		udelay(1);
		regmap_पढ़ो(priv->regmap, MESON_SAR_ADC_REG0, &regval);
	पूर्ण जबतक (FIELD_GET(MESON_SAR_ADC_REG0_BUSY_MASK, regval) && समयout--);

	अगर (समयout < 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक meson_sar_adc_पढ़ो_raw_sample(काष्ठा iio_dev *indio_dev,
					 स्थिर काष्ठा iio_chan_spec *chan,
					 पूर्णांक *val)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक regval, fअगरo_chan, fअगरo_val, count;

	अगर(!रुको_क्रम_completion_समयout(&priv->करोne,
				msecs_to_jअगरfies(MESON_SAR_ADC_TIMEOUT)))
		वापस -ETIMEDOUT;

	count = meson_sar_adc_get_fअगरo_count(indio_dev);
	अगर (count != 1) अणु
		dev_err(&indio_dev->dev,
			"ADC FIFO has %d element(s) instead of one\n", count);
		वापस -EINVAL;
	पूर्ण

	regmap_पढ़ो(priv->regmap, MESON_SAR_ADC_FIFO_RD, &regval);
	fअगरo_chan = FIELD_GET(MESON_SAR_ADC_FIFO_RD_CHAN_ID_MASK, regval);
	अगर (fअगरo_chan != chan->address) अणु
		dev_err(&indio_dev->dev,
			"ADC FIFO entry belongs to channel %d instead of %lu\n",
			fअगरo_chan, chan->address);
		वापस -EINVAL;
	पूर्ण

	fअगरo_val = FIELD_GET(MESON_SAR_ADC_FIFO_RD_SAMPLE_VALUE_MASK, regval);
	fअगरo_val &= GENMASK(priv->param->resolution - 1, 0);
	*val = meson_sar_adc_calib_val(indio_dev, fअगरo_val);

	वापस 0;
पूर्ण

अटल व्योम meson_sar_adc_set_averaging(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत meson_sar_adc_avg_mode mode,
					क्रमागत meson_sar_adc_num_samples samples)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक val, address = chan->address;

	val = samples << MESON_SAR_ADC_AVG_CNTL_NUM_SAMPLES_SHIFT(address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_AVG_CNTL,
			   MESON_SAR_ADC_AVG_CNTL_NUM_SAMPLES_MASK(address),
			   val);

	val = mode << MESON_SAR_ADC_AVG_CNTL_AVG_MODE_SHIFT(address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_AVG_CNTL,
			   MESON_SAR_ADC_AVG_CNTL_AVG_MODE_MASK(address), val);
पूर्ण

अटल व्योम meson_sar_adc_enable_channel(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	u32 regval;

	/*
	 * the SAR ADC engine allows sampling multiple channels at the same
	 * समय. to keep it simple we're only working with one *पूर्णांकernal*
	 * channel, which starts counting at index 0 (which means: count = 1).
	 */
	regval = FIELD_PREP(MESON_SAR_ADC_CHAN_LIST_MAX_INDEX_MASK, 0);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_CHAN_LIST,
			   MESON_SAR_ADC_CHAN_LIST_MAX_INDEX_MASK, regval);

	/* map channel index 0 to the channel which we want to पढ़ो */
	regval = FIELD_PREP(MESON_SAR_ADC_CHAN_LIST_ENTRY_MASK(0),
			    chan->address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_CHAN_LIST,
			   MESON_SAR_ADC_CHAN_LIST_ENTRY_MASK(0), regval);

	regval = FIELD_PREP(MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_MUX_MASK,
			    chan->address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DETECT_IDLE_SW,
			   MESON_SAR_ADC_DETECT_IDLE_SW_DETECT_MUX_MASK,
			   regval);

	regval = FIELD_PREP(MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_MUX_SEL_MASK,
			    chan->address);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DETECT_IDLE_SW,
			   MESON_SAR_ADC_DETECT_IDLE_SW_IDLE_MUX_SEL_MASK,
			   regval);

	अगर (chan->address == MESON_SAR_ADC_VOLTAGE_AND_TEMP_CHANNEL) अणु
		अगर (chan->type == IIO_TEMP)
			regval = MESON_SAR_ADC_DELTA_10_TEMP_SEL;
		अन्यथा
			regval = 0;

		regmap_update_bits(priv->regmap,
				   MESON_SAR_ADC_DELTA_10,
				   MESON_SAR_ADC_DELTA_10_TEMP_SEL, regval);
	पूर्ण
पूर्ण

अटल व्योम meson_sar_adc_set_chan7_mux(काष्ठा iio_dev *indio_dev,
					क्रमागत meson_sar_adc_chan7_mux_sel sel)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	u32 regval;

	regval = FIELD_PREP(MESON_SAR_ADC_REG3_CTRL_CHAN7_MUX_SEL_MASK, sel);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_CTRL_CHAN7_MUX_SEL_MASK, regval);

	usleep_range(10, 20);
पूर्ण

अटल व्योम meson_sar_adc_start_sample_engine(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);

	reinit_completion(&priv->करोne);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_FIFO_IRQ_EN,
			   MESON_SAR_ADC_REG0_FIFO_IRQ_EN);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_SAMPLE_ENGINE_ENABLE,
			   MESON_SAR_ADC_REG0_SAMPLE_ENGINE_ENABLE);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_SAMPLING_START,
			   MESON_SAR_ADC_REG0_SAMPLING_START);
पूर्ण

अटल व्योम meson_sar_adc_stop_sample_engine(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_FIFO_IRQ_EN, 0);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_SAMPLING_STOP,
			   MESON_SAR_ADC_REG0_SAMPLING_STOP);

	/* रुको until all modules are stopped */
	meson_sar_adc_रुको_busy_clear(indio_dev);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_SAMPLE_ENGINE_ENABLE, 0);
पूर्ण

अटल पूर्णांक meson_sar_adc_lock(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक val, समयout = 10000;

	mutex_lock(&indio_dev->mlock);

	अगर (priv->param->has_bl30_पूर्णांकegration) अणु
		/* prevent BL30 from using the SAR ADC जबतक we are using it */
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
				MESON_SAR_ADC_DELAY_KERNEL_BUSY,
				MESON_SAR_ADC_DELAY_KERNEL_BUSY);

		/*
		 * रुको until BL30 releases it's lock (so we can use the SAR
		 * ADC)
		 */
		करो अणु
			udelay(1);
			regmap_पढ़ो(priv->regmap, MESON_SAR_ADC_DELAY, &val);
		पूर्ण जबतक (val & MESON_SAR_ADC_DELAY_BL30_BUSY && समयout--);

		अगर (समयout < 0) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_sar_adc_unlock(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);

	अगर (priv->param->has_bl30_पूर्णांकegration)
		/* allow BL30 to use the SAR ADC again */
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
				MESON_SAR_ADC_DELAY_KERNEL_BUSY, 0);

	mutex_unlock(&indio_dev->mlock);
पूर्ण

अटल व्योम meson_sar_adc_clear_fअगरo(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक count, पंचांगp;

	क्रम (count = 0; count < MESON_SAR_ADC_MAX_FIFO_SIZE; count++) अणु
		अगर (!meson_sar_adc_get_fअगरo_count(indio_dev))
			अवरोध;

		regmap_पढ़ो(priv->regmap, MESON_SAR_ADC_FIFO_RD, &पंचांगp);
	पूर्ण
पूर्ण

अटल पूर्णांक meson_sar_adc_get_sample(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत meson_sar_adc_avg_mode avg_mode,
				    क्रमागत meson_sar_adc_num_samples avg_samples,
				    पूर्णांक *val)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (chan->type == IIO_TEMP && !priv->temperature_sensor_calibrated)
		वापस -ENOTSUPP;

	ret = meson_sar_adc_lock(indio_dev);
	अगर (ret)
		वापस ret;

	/* clear the FIFO to make sure we're not पढ़ोing old values */
	meson_sar_adc_clear_fअगरo(indio_dev);

	meson_sar_adc_set_averaging(indio_dev, chan, avg_mode, avg_samples);

	meson_sar_adc_enable_channel(indio_dev, chan);

	meson_sar_adc_start_sample_engine(indio_dev);
	ret = meson_sar_adc_पढ़ो_raw_sample(indio_dev, chan, val);
	meson_sar_adc_stop_sample_engine(indio_dev);

	meson_sar_adc_unlock(indio_dev);

	अगर (ret) अणु
		dev_warn(indio_dev->dev.parent,
			 "failed to read sample for channel %lu: %d\n",
			 chan->address, ret);
		वापस ret;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक meson_sar_adc_iio_info_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस meson_sar_adc_get_sample(indio_dev, chan, NO_AVERAGING,
						ONE_SAMPLE, val);

	हाल IIO_CHAN_INFO_AVERAGE_RAW:
		वापस meson_sar_adc_get_sample(indio_dev, chan,
						MEAN_AVERAGING, EIGHT_SAMPLES,
						val);

	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_VOLTAGE) अणु
			ret = regulator_get_voltage(priv->vref);
			अगर (ret < 0) अणु
				dev_err(indio_dev->dev.parent,
					"failed to get vref voltage: %d\n",
					ret);
				वापस ret;
			पूर्ण

			*val = ret / 1000;
			*val2 = priv->param->resolution;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		पूर्ण अन्यथा अगर (chan->type == IIO_TEMP) अणु
			/* SoC specअगरic multiplier and भागider */
			*val = priv->param->temperature_multiplier;
			*val2 = priv->param->temperature_भागider;

			/* celsius to millicelsius */
			*val *= 1000;

			वापस IIO_VAL_FRACTIONAL;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण

	हाल IIO_CHAN_INFO_CALIBBIAS:
		*val = priv->calibbias;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_CALIBSCALE:
		*val = priv->calibscale / MILLION;
		*val2 = priv->calibscale % MILLION;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CHAN_INFO_OFFSET:
		*val = DIV_ROUND_CLOSEST(MESON_SAR_ADC_TEMP_OFFSET *
					 priv->param->temperature_भागider,
					 priv->param->temperature_multiplier);
		*val -= priv->temperature_sensor_adc_val;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक meson_sar_adc_clk_init(काष्ठा iio_dev *indio_dev,
				  व्योम __iomem *base)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	काष्ठा clk_init_data init;
	स्थिर अक्षर *clk_parents[1];

	init.name = devm_kaप्र_लिखो(&indio_dev->dev, GFP_KERNEL, "%s#adc_div",
				   dev_name(indio_dev->dev.parent));
	अगर (!init.name)
		वापस -ENOMEM;

	init.flags = 0;
	init.ops = &clk_भागider_ops;
	clk_parents[0] = __clk_get_name(priv->clkin);
	init.parent_names = clk_parents;
	init.num_parents = 1;

	priv->clk_भाग.reg = base + MESON_SAR_ADC_REG3;
	priv->clk_भाग.shअगरt = MESON_SAR_ADC_REG3_ADC_CLK_DIV_SHIFT;
	priv->clk_भाग.width = MESON_SAR_ADC_REG3_ADC_CLK_DIV_WIDTH;
	priv->clk_भाग.hw.init = &init;
	priv->clk_भाग.flags = 0;

	priv->adc_भाग_clk = devm_clk_रेजिस्टर(&indio_dev->dev,
					      &priv->clk_भाग.hw);
	अगर (WARN_ON(IS_ERR(priv->adc_भाग_clk)))
		वापस PTR_ERR(priv->adc_भाग_clk);

	init.name = devm_kaप्र_लिखो(&indio_dev->dev, GFP_KERNEL, "%s#adc_en",
				   dev_name(indio_dev->dev.parent));
	अगर (!init.name)
		वापस -ENOMEM;

	init.flags = CLK_SET_RATE_PARENT;
	init.ops = &clk_gate_ops;
	clk_parents[0] = __clk_get_name(priv->adc_भाग_clk);
	init.parent_names = clk_parents;
	init.num_parents = 1;

	priv->clk_gate.reg = base + MESON_SAR_ADC_REG3;
	priv->clk_gate.bit_idx = __ffs(MESON_SAR_ADC_REG3_CLK_EN);
	priv->clk_gate.hw.init = &init;

	priv->adc_clk = devm_clk_रेजिस्टर(&indio_dev->dev, &priv->clk_gate.hw);
	अगर (WARN_ON(IS_ERR(priv->adc_clk)))
		वापस PTR_ERR(priv->adc_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_sar_adc_temp_sensor_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	u8 *buf, trimming_bits, trimming_mask, upper_adc_val;
	काष्ठा nvmem_cell *temperature_calib;
	माप_प्रकार पढ़ो_len;
	पूर्णांक ret;

	temperature_calib = devm_nvmem_cell_get(indio_dev->dev.parent,
						"temperature_calib");
	अगर (IS_ERR(temperature_calib)) अणु
		ret = PTR_ERR(temperature_calib);

		/*
		 * leave the temperature sensor disabled अगर no calibration data
		 * was passed via nvmem-cells.
		 */
		अगर (ret == -ENODEV)
			वापस 0;

		वापस dev_err_probe(indio_dev->dev.parent, ret,
				     "failed to get temperature_calib cell\n");
	पूर्ण

	priv->tsc_regmap =
		syscon_regmap_lookup_by_phandle(indio_dev->dev.parent->of_node,
						"amlogic,hhi-sysctrl");
	अगर (IS_ERR(priv->tsc_regmap)) अणु
		dev_err(indio_dev->dev.parent,
			"failed to get amlogic,hhi-sysctrl regmap\n");
		वापस PTR_ERR(priv->tsc_regmap);
	पूर्ण

	पढ़ो_len = MESON_SAR_ADC_EFUSE_BYTES;
	buf = nvmem_cell_पढ़ो(temperature_calib, &पढ़ो_len);
	अगर (IS_ERR(buf)) अणु
		dev_err(indio_dev->dev.parent,
			"failed to read temperature_calib cell\n");
		वापस PTR_ERR(buf);
	पूर्ण अन्यथा अगर (पढ़ो_len != MESON_SAR_ADC_EFUSE_BYTES) अणु
		kमुक्त(buf);
		dev_err(indio_dev->dev.parent,
			"invalid read size of temperature_calib cell\n");
		वापस -EINVAL;
	पूर्ण

	trimming_bits = priv->param->temperature_trimming_bits;
	trimming_mask = BIT(trimming_bits) - 1;

	priv->temperature_sensor_calibrated =
		buf[3] & MESON_SAR_ADC_EFUSE_BYTE3_IS_CALIBRATED;
	priv->temperature_sensor_coefficient = buf[2] & trimming_mask;

	upper_adc_val = FIELD_GET(MESON_SAR_ADC_EFUSE_BYTE3_UPPER_ADC_VAL,
				  buf[3]);

	priv->temperature_sensor_adc_val = buf[2];
	priv->temperature_sensor_adc_val |= upper_adc_val << BITS_PER_BYTE;
	priv->temperature_sensor_adc_val >>= trimming_bits;

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_sar_adc_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक regval, i, ret;

	/*
	 * make sure we start at CH7 input since the other muxes are only used
	 * क्रम पूर्णांकernal calibration.
	 */
	meson_sar_adc_set_chan7_mux(indio_dev, CHAN7_MUX_CH7_INPUT);

	अगर (priv->param->has_bl30_पूर्णांकegration) अणु
		/*
		 * leave sampling delay and the input घड़ीs as configured by
		 * BL30 to make sure BL30 माला_लो the values it expects when
		 * पढ़ोing the temperature sensor.
		 */
		regmap_पढ़ो(priv->regmap, MESON_SAR_ADC_REG3, &regval);
		अगर (regval & MESON_SAR_ADC_REG3_BL30_INITIALIZED)
			वापस 0;
	पूर्ण

	meson_sar_adc_stop_sample_engine(indio_dev);

	/*
	 * disable this bit as seems to be only relevant क्रम Meson6 (based
	 * on the venकरोr driver), which we करोn't support at the moment.
	 */
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			MESON_SAR_ADC_REG0_ADC_TEMP_SEN_SEL, 0);

	/* disable all channels by शेष */
	regmap_ग_लिखो(priv->regmap, MESON_SAR_ADC_CHAN_LIST, 0x0);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_CTRL_SAMPLING_CLOCK_PHASE, 0);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_CNTL_USE_SC_DLY,
			   MESON_SAR_ADC_REG3_CNTL_USE_SC_DLY);

	/* delay between two samples = (10+1) * 1uS */
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
			   MESON_SAR_ADC_DELAY_INPUT_DLY_CNT_MASK,
			   FIELD_PREP(MESON_SAR_ADC_DELAY_SAMPLE_DLY_CNT_MASK,
				      10));
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
			   MESON_SAR_ADC_DELAY_SAMPLE_DLY_SEL_MASK,
			   FIELD_PREP(MESON_SAR_ADC_DELAY_SAMPLE_DLY_SEL_MASK,
				      0));

	/* delay between two samples = (10+1) * 1uS */
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
			   MESON_SAR_ADC_DELAY_INPUT_DLY_CNT_MASK,
			   FIELD_PREP(MESON_SAR_ADC_DELAY_INPUT_DLY_CNT_MASK,
				      10));
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELAY,
			   MESON_SAR_ADC_DELAY_INPUT_DLY_SEL_MASK,
			   FIELD_PREP(MESON_SAR_ADC_DELAY_INPUT_DLY_SEL_MASK,
				      1));

	/*
	 * set up the input channel muxes in MESON_SAR_ADC_CHAN_10_SW
	 * (0 = SAR_ADC_CH0, 1 = SAR_ADC_CH1)
	 */
	regval = FIELD_PREP(MESON_SAR_ADC_CHAN_10_SW_CHAN0_MUX_SEL_MASK, 0);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_CHAN_10_SW,
			   MESON_SAR_ADC_CHAN_10_SW_CHAN0_MUX_SEL_MASK,
			   regval);
	regval = FIELD_PREP(MESON_SAR_ADC_CHAN_10_SW_CHAN1_MUX_SEL_MASK, 1);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_CHAN_10_SW,
			   MESON_SAR_ADC_CHAN_10_SW_CHAN1_MUX_SEL_MASK,
			   regval);

	/*
	 * set up the input channel muxes in MESON_SAR_ADC_AUX_SW
	 * (2 = SAR_ADC_CH2, 3 = SAR_ADC_CH3, ...) and enable
	 * MESON_SAR_ADC_AUX_SW_YP_DRIVE_SW and
	 * MESON_SAR_ADC_AUX_SW_XP_DRIVE_SW like the venकरोr driver.
	 */
	regval = 0;
	क्रम (i = 2; i <= 7; i++)
		regval |= i << MESON_SAR_ADC_AUX_SW_MUX_SEL_CHAN_SHIFT(i);
	regval |= MESON_SAR_ADC_AUX_SW_YP_DRIVE_SW;
	regval |= MESON_SAR_ADC_AUX_SW_XP_DRIVE_SW;
	regmap_ग_लिखो(priv->regmap, MESON_SAR_ADC_AUX_SW, regval);

	अगर (priv->temperature_sensor_calibrated) अणु
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELTA_10,
				   MESON_SAR_ADC_DELTA_10_TS_REVE1,
				   MESON_SAR_ADC_DELTA_10_TS_REVE1);
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELTA_10,
				   MESON_SAR_ADC_DELTA_10_TS_REVE0,
				   MESON_SAR_ADC_DELTA_10_TS_REVE0);

		/*
		 * set bits [3:0] of the TSC (temperature sensor coefficient)
		 * to get the correct values when पढ़ोing the temperature.
		 */
		regval = FIELD_PREP(MESON_SAR_ADC_DELTA_10_TS_C_MASK,
				    priv->temperature_sensor_coefficient);
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELTA_10,
				   MESON_SAR_ADC_DELTA_10_TS_C_MASK, regval);

		अगर (priv->param->temperature_trimming_bits == 5) अणु
			अगर (priv->temperature_sensor_coefficient & BIT(4))
				regval = MESON_HHI_DPLL_TOP_0_TSC_BIT4;
			अन्यथा
				regval = 0;

			/*
			 * bit [4] (the 5th bit when starting to count at 1)
			 * of the TSC is located in the HHI रेजिस्टर area.
			 */
			regmap_update_bits(priv->tsc_regmap,
					   MESON_HHI_DPLL_TOP_0,
					   MESON_HHI_DPLL_TOP_0_TSC_BIT4,
					   regval);
		पूर्ण
	पूर्ण अन्यथा अणु
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELTA_10,
				   MESON_SAR_ADC_DELTA_10_TS_REVE1, 0);
		regmap_update_bits(priv->regmap, MESON_SAR_ADC_DELTA_10,
				   MESON_SAR_ADC_DELTA_10_TS_REVE0, 0);
	पूर्ण

	ret = clk_set_parent(priv->adc_sel_clk, priv->clkin);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent,
			"failed to set adc parent to clkin\n");
		वापस ret;
	पूर्ण

	ret = clk_set_rate(priv->adc_clk, priv->param->घड़ी_rate);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent,
			"failed to set adc clock rate\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम meson_sar_adc_set_bandgap(काष्ठा iio_dev *indio_dev, bool on_off)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	स्थिर काष्ठा meson_sar_adc_param *param = priv->param;
	u32 enable_mask;

	अगर (param->bandgap_reg == MESON_SAR_ADC_REG11)
		enable_mask = MESON_SAR_ADC_REG11_BANDGAP_EN;
	अन्यथा
		enable_mask = MESON_SAR_ADC_DELTA_10_TS_VBG_EN;

	regmap_update_bits(priv->regmap, param->bandgap_reg, enable_mask,
			   on_off ? enable_mask : 0);
पूर्ण

अटल पूर्णांक meson_sar_adc_hw_enable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 regval;

	ret = meson_sar_adc_lock(indio_dev);
	अगर (ret)
		जाओ err_lock;

	ret = regulator_enable(priv->vref);
	अगर (ret < 0) अणु
		dev_err(indio_dev->dev.parent,
			"failed to enable vref regulator\n");
		जाओ err_vref;
	पूर्ण

	ret = clk_prepare_enable(priv->core_clk);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent, "failed to enable core clk\n");
		जाओ err_core_clk;
	पूर्ण

	regval = FIELD_PREP(MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK, 1);
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG0,
			   MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK, regval);

	meson_sar_adc_set_bandgap(indio_dev, true);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_ADC_EN,
			   MESON_SAR_ADC_REG3_ADC_EN);

	udelay(5);

	ret = clk_prepare_enable(priv->adc_clk);
	अगर (ret) अणु
		dev_err(indio_dev->dev.parent, "failed to enable adc clk\n");
		जाओ err_adc_clk;
	पूर्ण

	meson_sar_adc_unlock(indio_dev);

	वापस 0;

err_adc_clk:
	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_ADC_EN, 0);
	meson_sar_adc_set_bandgap(indio_dev, false);
	clk_disable_unprepare(priv->core_clk);
err_core_clk:
	regulator_disable(priv->vref);
err_vref:
	meson_sar_adc_unlock(indio_dev);
err_lock:
	वापस ret;
पूर्ण

अटल पूर्णांक meson_sar_adc_hw_disable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = meson_sar_adc_lock(indio_dev);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(priv->adc_clk);

	regmap_update_bits(priv->regmap, MESON_SAR_ADC_REG3,
			   MESON_SAR_ADC_REG3_ADC_EN, 0);

	meson_sar_adc_set_bandgap(indio_dev, false);

	clk_disable_unprepare(priv->core_clk);

	regulator_disable(priv->vref);

	meson_sar_adc_unlock(indio_dev);

	वापस 0;
पूर्ण

अटल irqवापस_t meson_sar_adc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	अचिन्हित पूर्णांक cnt, threshold;
	u32 regval;

	regmap_पढ़ो(priv->regmap, MESON_SAR_ADC_REG0, &regval);
	cnt = FIELD_GET(MESON_SAR_ADC_REG0_FIFO_COUNT_MASK, regval);
	threshold = FIELD_GET(MESON_SAR_ADC_REG0_FIFO_CNT_IRQ_MASK, regval);

	अगर (cnt < threshold)
		वापस IRQ_NONE;

	complete(&priv->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक meson_sar_adc_calib(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा meson_sar_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret, nominal0, nominal1, value0, value1;

	/* use poपूर्णांकs 25% and 75% क्रम calibration */
	nominal0 = (1 << priv->param->resolution) / 4;
	nominal1 = (1 << priv->param->resolution) * 3 / 4;

	meson_sar_adc_set_chan7_mux(indio_dev, CHAN7_MUX_VDD_DIV4);
	usleep_range(10, 20);
	ret = meson_sar_adc_get_sample(indio_dev,
				       &indio_dev->channels[7],
				       MEAN_AVERAGING, EIGHT_SAMPLES, &value0);
	अगर (ret < 0)
		जाओ out;

	meson_sar_adc_set_chan7_mux(indio_dev, CHAN7_MUX_VDD_MUL3_DIV4);
	usleep_range(10, 20);
	ret = meson_sar_adc_get_sample(indio_dev,
				       &indio_dev->channels[7],
				       MEAN_AVERAGING, EIGHT_SAMPLES, &value1);
	अगर (ret < 0)
		जाओ out;

	अगर (value1 <= value0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	priv->calibscale = भाग_s64((nominal1 - nominal0) * (s64)MILLION,
				   value1 - value0);
	priv->calibbias = nominal0 - भाग_s64((s64)value0 * priv->calibscale,
					     MILLION);
	ret = 0;
out:
	meson_sar_adc_set_chan7_mux(indio_dev, CHAN7_MUX_CH7_INPUT);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info meson_sar_adc_iio_info = अणु
	.पढ़ो_raw = meson_sar_adc_iio_info_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_param meson_sar_adc_meson8_param = अणु
	.has_bl30_पूर्णांकegration = false,
	.घड़ी_rate = 1150000,
	.bandgap_reg = MESON_SAR_ADC_DELTA_10,
	.regmap_config = &meson_sar_adc_regmap_config_meson8,
	.resolution = 10,
	.temperature_trimming_bits = 4,
	.temperature_multiplier = 18 * 10000,
	.temperature_भागider = 1024 * 10 * 85,
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_param meson_sar_adc_meson8b_param = अणु
	.has_bl30_पूर्णांकegration = false,
	.घड़ी_rate = 1150000,
	.bandgap_reg = MESON_SAR_ADC_DELTA_10,
	.regmap_config = &meson_sar_adc_regmap_config_meson8,
	.resolution = 10,
	.temperature_trimming_bits = 5,
	.temperature_multiplier = 10,
	.temperature_भागider = 32,
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_param meson_sar_adc_gxbb_param = अणु
	.has_bl30_पूर्णांकegration = true,
	.घड़ी_rate = 1200000,
	.bandgap_reg = MESON_SAR_ADC_REG11,
	.regmap_config = &meson_sar_adc_regmap_config_gxbb,
	.resolution = 10,
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_param meson_sar_adc_gxl_param = अणु
	.has_bl30_पूर्णांकegration = true,
	.घड़ी_rate = 1200000,
	.bandgap_reg = MESON_SAR_ADC_REG11,
	.regmap_config = &meson_sar_adc_regmap_config_gxbb,
	.resolution = 12,
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_meson8_data = अणु
	.param = &meson_sar_adc_meson8_param,
	.name = "meson-meson8-saradc",
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_meson8b_data = अणु
	.param = &meson_sar_adc_meson8b_param,
	.name = "meson-meson8b-saradc",
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_meson8m2_data = अणु
	.param = &meson_sar_adc_meson8b_param,
	.name = "meson-meson8m2-saradc",
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_gxbb_data = अणु
	.param = &meson_sar_adc_gxbb_param,
	.name = "meson-gxbb-saradc",
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_gxl_data = अणु
	.param = &meson_sar_adc_gxl_param,
	.name = "meson-gxl-saradc",
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_gxm_data = अणु
	.param = &meson_sar_adc_gxl_param,
	.name = "meson-gxm-saradc",
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_axg_data = अणु
	.param = &meson_sar_adc_gxl_param,
	.name = "meson-axg-saradc",
पूर्ण;

अटल स्थिर काष्ठा meson_sar_adc_data meson_sar_adc_g12a_data = अणु
	.param = &meson_sar_adc_gxl_param,
	.name = "meson-g12a-saradc",
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_sar_adc_of_match[] = अणु
	अणु
		.compatible = "amlogic,meson8-saradc",
		.data = &meson_sar_adc_meson8_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson8b-saradc",
		.data = &meson_sar_adc_meson8b_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson8m2-saradc",
		.data = &meson_sar_adc_meson8m2_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson-gxbb-saradc",
		.data = &meson_sar_adc_gxbb_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson-gxl-saradc",
		.data = &meson_sar_adc_gxl_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson-gxm-saradc",
		.data = &meson_sar_adc_gxm_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson-axg-saradc",
		.data = &meson_sar_adc_axg_data,
	पूर्ण, अणु
		.compatible = "amlogic,meson-g12a-saradc",
		.data = &meson_sar_adc_g12a_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_sar_adc_of_match);

अटल पूर्णांक meson_sar_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा meson_sar_adc_data *match_data;
	काष्ठा meson_sar_adc_priv *priv;
	काष्ठा iio_dev *indio_dev;
	व्योम __iomem *base;
	पूर्णांक irq, ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*priv));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	priv = iio_priv(indio_dev);
	init_completion(&priv->करोne);

	match_data = of_device_get_match_data(&pdev->dev);
	अगर (!match_data) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	priv->param = match_data->param;

	indio_dev->name = match_data->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &meson_sar_adc_iio_info;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					     priv->param->regmap_config);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (!irq)
		वापस -EINVAL;

	ret = devm_request_irq(&pdev->dev, irq, meson_sar_adc_irq, IRQF_SHARED,
			       dev_name(&pdev->dev), indio_dev);
	अगर (ret)
		वापस ret;

	priv->clkin = devm_clk_get(&pdev->dev, "clkin");
	अगर (IS_ERR(priv->clkin)) अणु
		dev_err(&pdev->dev, "failed to get clkin\n");
		वापस PTR_ERR(priv->clkin);
	पूर्ण

	priv->core_clk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(priv->core_clk)) अणु
		dev_err(&pdev->dev, "failed to get core clk\n");
		वापस PTR_ERR(priv->core_clk);
	पूर्ण

	priv->adc_clk = devm_clk_get(&pdev->dev, "adc_clk");
	अगर (IS_ERR(priv->adc_clk)) अणु
		अगर (PTR_ERR(priv->adc_clk) == -ENOENT) अणु
			priv->adc_clk = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "failed to get adc clk\n");
			वापस PTR_ERR(priv->adc_clk);
		पूर्ण
	पूर्ण

	priv->adc_sel_clk = devm_clk_get(&pdev->dev, "adc_sel");
	अगर (IS_ERR(priv->adc_sel_clk)) अणु
		अगर (PTR_ERR(priv->adc_sel_clk) == -ENOENT) अणु
			priv->adc_sel_clk = शून्य;
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "failed to get adc_sel clk\n");
			वापस PTR_ERR(priv->adc_sel_clk);
		पूर्ण
	पूर्ण

	/* on pre-GXBB SoCs the SAR ADC itself provides the ADC घड़ी: */
	अगर (!priv->adc_clk) अणु
		ret = meson_sar_adc_clk_init(indio_dev, base);
		अगर (ret)
			वापस ret;
	पूर्ण

	priv->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(priv->vref)) अणु
		dev_err(&pdev->dev, "failed to get vref regulator\n");
		वापस PTR_ERR(priv->vref);
	पूर्ण

	priv->calibscale = MILLION;

	अगर (priv->param->temperature_trimming_bits) अणु
		ret = meson_sar_adc_temp_sensor_init(indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->temperature_sensor_calibrated) अणु
		indio_dev->channels = meson_sar_adc_and_temp_iio_channels;
		indio_dev->num_channels =
			ARRAY_SIZE(meson_sar_adc_and_temp_iio_channels);
	पूर्ण अन्यथा अणु
		indio_dev->channels = meson_sar_adc_iio_channels;
		indio_dev->num_channels =
			ARRAY_SIZE(meson_sar_adc_iio_channels);
	पूर्ण

	ret = meson_sar_adc_init(indio_dev);
	अगर (ret)
		जाओ err;

	ret = meson_sar_adc_hw_enable(indio_dev);
	अगर (ret)
		जाओ err;

	ret = meson_sar_adc_calib(indio_dev);
	अगर (ret)
		dev_warn(&pdev->dev, "calibration failed\n");

	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_hw;

	वापस 0;

err_hw:
	meson_sar_adc_hw_disable(indio_dev);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक meson_sar_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	iio_device_unरेजिस्टर(indio_dev);

	वापस meson_sar_adc_hw_disable(indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused meson_sar_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);

	वापस meson_sar_adc_hw_disable(indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused meson_sar_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);

	वापस meson_sar_adc_hw_enable(indio_dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(meson_sar_adc_pm_ops,
			 meson_sar_adc_suspend, meson_sar_adc_resume);

अटल काष्ठा platक्रमm_driver meson_sar_adc_driver = अणु
	.probe		= meson_sar_adc_probe,
	.हटाओ		= meson_sar_adc_हटाओ,
	.driver		= अणु
		.name	= "meson-saradc",
		.of_match_table = meson_sar_adc_of_match,
		.pm = &meson_sar_adc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(meson_sar_adc_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Amlogic Meson SAR ADC driver");
MODULE_LICENSE("GPL v2");
