<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ADC driver क्रम the Ingenic JZ47xx SoCs
 * Copyright (c) 2019 Artur Rojek <contact@artur-rojek.eu>
 *
 * based on drivers/mfd/jz4740-adc.c
 */

#समावेश <dt-bindings/iio/adc/ingenic,adc.h>
#समावेश <linux/clk.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा JZ_ADC_REG_ENABLE		0x00
#घोषणा JZ_ADC_REG_CFG			0x04
#घोषणा JZ_ADC_REG_CTRL			0x08
#घोषणा JZ_ADC_REG_STATUS		0x0c
#घोषणा JZ_ADC_REG_ADSAME		0x10
#घोषणा JZ_ADC_REG_ADWAIT		0x14
#घोषणा JZ_ADC_REG_ADTCH		0x18
#घोषणा JZ_ADC_REG_ADBDAT		0x1c
#घोषणा JZ_ADC_REG_ADSDAT		0x20
#घोषणा JZ_ADC_REG_ADCMD		0x24
#घोषणा JZ_ADC_REG_ADCLK		0x28

#घोषणा JZ_ADC_REG_ENABLE_PD		BIT(7)
#घोषणा JZ_ADC_REG_CFG_AUX_MD		(BIT(0) | BIT(1))
#घोषणा JZ_ADC_REG_CFG_BAT_MD		BIT(4)
#घोषणा JZ_ADC_REG_CFG_SAMPLE_NUM(n)	((n) << 10)
#घोषणा JZ_ADC_REG_CFG_PULL_UP(n)	((n) << 16)
#घोषणा JZ_ADC_REG_CFG_CMD_SEL		BIT(22)
#घोषणा JZ_ADC_REG_CFG_TOUCH_OPS_MASK	(BIT(31) | GENMASK(23, 10))
#घोषणा JZ_ADC_REG_ADCLK_CLKDIV_LSB	0
#घोषणा JZ4725B_ADC_REG_ADCLK_CLKDIV10US_LSB	16
#घोषणा JZ4770_ADC_REG_ADCLK_CLKDIV10US_LSB	8
#घोषणा JZ4770_ADC_REG_ADCLK_CLKDIVMS_LSB	16

#घोषणा JZ_ADC_REG_ADCMD_YNADC		BIT(7)
#घोषणा JZ_ADC_REG_ADCMD_YPADC		BIT(8)
#घोषणा JZ_ADC_REG_ADCMD_XNADC		BIT(9)
#घोषणा JZ_ADC_REG_ADCMD_XPADC		BIT(10)
#घोषणा JZ_ADC_REG_ADCMD_VREFPYP	BIT(11)
#घोषणा JZ_ADC_REG_ADCMD_VREFPXP	BIT(12)
#घोषणा JZ_ADC_REG_ADCMD_VREFPXN	BIT(13)
#घोषणा JZ_ADC_REG_ADCMD_VREFPAUX	BIT(14)
#घोषणा JZ_ADC_REG_ADCMD_VREFPVDD33	BIT(15)
#घोषणा JZ_ADC_REG_ADCMD_VREFNYN	BIT(16)
#घोषणा JZ_ADC_REG_ADCMD_VREFNXP	BIT(17)
#घोषणा JZ_ADC_REG_ADCMD_VREFNXN	BIT(18)
#घोषणा JZ_ADC_REG_ADCMD_VREFAUX	BIT(19)
#घोषणा JZ_ADC_REG_ADCMD_YNGRU		BIT(20)
#घोषणा JZ_ADC_REG_ADCMD_XNGRU		BIT(21)
#घोषणा JZ_ADC_REG_ADCMD_XPGRU		BIT(22)
#घोषणा JZ_ADC_REG_ADCMD_YPSUP		BIT(23)
#घोषणा JZ_ADC_REG_ADCMD_XNSUP		BIT(24)
#घोषणा JZ_ADC_REG_ADCMD_XPSUP		BIT(25)

#घोषणा JZ_ADC_AUX_VREF				3300
#घोषणा JZ_ADC_AUX_VREF_BITS			12
#घोषणा JZ_ADC_BATTERY_LOW_VREF			2500
#घोषणा JZ_ADC_BATTERY_LOW_VREF_BITS		12
#घोषणा JZ4725B_ADC_BATTERY_HIGH_VREF		7500
#घोषणा JZ4725B_ADC_BATTERY_HIGH_VREF_BITS	10
#घोषणा JZ4740_ADC_BATTERY_HIGH_VREF		(7500 * 0.986)
#घोषणा JZ4740_ADC_BATTERY_HIGH_VREF_BITS	12
#घोषणा JZ4770_ADC_BATTERY_VREF			1200
#घोषणा JZ4770_ADC_BATTERY_VREF_BITS		12

#घोषणा JZ_ADC_IRQ_AUX			BIT(0)
#घोषणा JZ_ADC_IRQ_BATTERY		BIT(1)
#घोषणा JZ_ADC_IRQ_TOUCH		BIT(2)
#घोषणा JZ_ADC_IRQ_PEN_DOWN		BIT(3)
#घोषणा JZ_ADC_IRQ_PEN_UP		BIT(4)
#घोषणा JZ_ADC_IRQ_PEN_DOWN_SLEEP	BIT(5)
#घोषणा JZ_ADC_IRQ_SLEEP		BIT(7)

काष्ठा ingenic_adc;

काष्ठा ingenic_adc_soc_data अणु
	अचिन्हित पूर्णांक battery_high_vref;
	अचिन्हित पूर्णांक battery_high_vref_bits;
	स्थिर पूर्णांक *battery_raw_avail;
	माप_प्रकार battery_raw_avail_size;
	स्थिर पूर्णांक *battery_scale_avail;
	माप_प्रकार battery_scale_avail_size;
	अचिन्हित पूर्णांक battery_vref_mode: 1;
	अचिन्हित पूर्णांक has_aux2: 1;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	पूर्णांक (*init_clk_भाग)(काष्ठा device *dev, काष्ठा ingenic_adc *adc);
पूर्ण;

काष्ठा ingenic_adc अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा mutex lock;
	काष्ठा mutex aux_lock;
	स्थिर काष्ठा ingenic_adc_soc_data *soc_data;
	bool low_vref_mode;
पूर्ण;

अटल व्योम ingenic_adc_set_adcmd(काष्ठा iio_dev *iio_dev, अचिन्हित दीर्घ mask)
अणु
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);

	mutex_lock(&adc->lock);

	/* Init ADCMD */
	पढ़ोl(adc->base + JZ_ADC_REG_ADCMD);

	अगर (mask & 0x3) अणु
		/* Second channel (INGENIC_ADC_TOUCH_YP): sample YP vs. GND */
		ग_लिखोl(JZ_ADC_REG_ADCMD_XNGRU
		       | JZ_ADC_REG_ADCMD_VREFNXN | JZ_ADC_REG_ADCMD_VREFPVDD33
		       | JZ_ADC_REG_ADCMD_YPADC,
		       adc->base + JZ_ADC_REG_ADCMD);

		/* First channel (INGENIC_ADC_TOUCH_XP): sample XP vs. GND */
		ग_लिखोl(JZ_ADC_REG_ADCMD_YNGRU
		       | JZ_ADC_REG_ADCMD_VREFNYN | JZ_ADC_REG_ADCMD_VREFPVDD33
		       | JZ_ADC_REG_ADCMD_XPADC,
		       adc->base + JZ_ADC_REG_ADCMD);
	पूर्ण

	अगर (mask & 0xc) अणु
		/* Fourth channel (INGENIC_ADC_TOUCH_YN): sample YN vs. GND */
		ग_लिखोl(JZ_ADC_REG_ADCMD_XNGRU
		       | JZ_ADC_REG_ADCMD_VREFNXN | JZ_ADC_REG_ADCMD_VREFPVDD33
		       | JZ_ADC_REG_ADCMD_YNADC,
		       adc->base + JZ_ADC_REG_ADCMD);

		/* Third channel (INGENIC_ADC_TOUCH_XN): sample XN vs. GND */
		ग_लिखोl(JZ_ADC_REG_ADCMD_YNGRU
		       | JZ_ADC_REG_ADCMD_VREFNYN | JZ_ADC_REG_ADCMD_VREFPVDD33
		       | JZ_ADC_REG_ADCMD_XNADC,
		       adc->base + JZ_ADC_REG_ADCMD);
	पूर्ण

	अगर (mask & 0x30) अणु
		/* Sixth channel (INGENIC_ADC_TOUCH_YD): sample YP vs. YN */
		ग_लिखोl(JZ_ADC_REG_ADCMD_VREFNYN | JZ_ADC_REG_ADCMD_VREFPVDD33
		       | JZ_ADC_REG_ADCMD_YPADC,
		       adc->base + JZ_ADC_REG_ADCMD);

		/* Fअगरth channel (INGENIC_ADC_TOUCH_XD): sample XP vs. XN */
		ग_लिखोl(JZ_ADC_REG_ADCMD_VREFNXN | JZ_ADC_REG_ADCMD_VREFPVDD33
		       | JZ_ADC_REG_ADCMD_XPADC,
		       adc->base + JZ_ADC_REG_ADCMD);
	पूर्ण

	/* We're करोne */
	ग_लिखोl(0, adc->base + JZ_ADC_REG_ADCMD);

	mutex_unlock(&adc->lock);
पूर्ण

अटल व्योम ingenic_adc_set_config(काष्ठा ingenic_adc *adc,
				   uपूर्णांक32_t mask,
				   uपूर्णांक32_t val)
अणु
	uपूर्णांक32_t cfg;

	mutex_lock(&adc->lock);

	cfg = पढ़ोl(adc->base + JZ_ADC_REG_CFG) & ~mask;
	cfg |= val;
	ग_लिखोl(cfg, adc->base + JZ_ADC_REG_CFG);

	mutex_unlock(&adc->lock);
पूर्ण

अटल व्योम ingenic_adc_enable_unlocked(काष्ठा ingenic_adc *adc,
					पूर्णांक engine,
					bool enabled)
अणु
	u8 val;

	val = पढ़ोb(adc->base + JZ_ADC_REG_ENABLE);

	अगर (enabled)
		val |= BIT(engine);
	अन्यथा
		val &= ~BIT(engine);

	ग_लिखोb(val, adc->base + JZ_ADC_REG_ENABLE);
पूर्ण

अटल व्योम ingenic_adc_enable(काष्ठा ingenic_adc *adc,
			       पूर्णांक engine,
			       bool enabled)
अणु
	mutex_lock(&adc->lock);
	ingenic_adc_enable_unlocked(adc, engine, enabled);
	mutex_unlock(&adc->lock);
पूर्ण

अटल पूर्णांक ingenic_adc_capture(काष्ठा ingenic_adc *adc,
			       पूर्णांक engine)
अणु
	u32 cfg;
	u8 val;
	पूर्णांक ret;

	/*
	 * Disable CMD_SEL temporarily, because it causes wrong VBAT पढ़ोings,
	 * probably due to the चयन of VREF. We must keep the lock here to
	 * aव्योम races with the buffer enable/disable functions.
	 */
	mutex_lock(&adc->lock);
	cfg = पढ़ोl(adc->base + JZ_ADC_REG_CFG);
	ग_लिखोl(cfg & ~JZ_ADC_REG_CFG_CMD_SEL, adc->base + JZ_ADC_REG_CFG);

	ingenic_adc_enable_unlocked(adc, engine, true);
	ret = पढ़ोb_poll_समयout(adc->base + JZ_ADC_REG_ENABLE, val,
				 !(val & BIT(engine)), 250, 1000);
	अगर (ret)
		ingenic_adc_enable_unlocked(adc, engine, false);

	ग_लिखोl(cfg, adc->base + JZ_ADC_REG_CFG);
	mutex_unlock(&adc->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ingenic_adc_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक val,
				 पूर्णांक val2,
				 दीर्घ m)
अणु
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);
	काष्ठा device *dev = iio_dev->dev.parent;
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->channel) अणु
		हाल INGENIC_ADC_BATTERY:
			अगर (!adc->soc_data->battery_vref_mode)
				वापस -EINVAL;

			ret = clk_enable(adc->clk);
			अगर (ret) अणु
				dev_err(dev, "Failed to enable clock: %d\n",
					ret);
				वापस ret;
			पूर्ण

			अगर (val > JZ_ADC_BATTERY_LOW_VREF) अणु
				ingenic_adc_set_config(adc,
						       JZ_ADC_REG_CFG_BAT_MD,
						       0);
				adc->low_vref_mode = false;
			पूर्ण अन्यथा अणु
				ingenic_adc_set_config(adc,
						       JZ_ADC_REG_CFG_BAT_MD,
						       JZ_ADC_REG_CFG_BAT_MD);
				adc->low_vref_mode = true;
			पूर्ण

			clk_disable(adc->clk);

			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर पूर्णांक jz4725b_adc_battery_raw_avail[] = अणु
	0, 1, (1 << JZ_ADC_BATTERY_LOW_VREF_BITS) - 1,
पूर्ण;

अटल स्थिर पूर्णांक jz4725b_adc_battery_scale_avail[] = अणु
	JZ4725B_ADC_BATTERY_HIGH_VREF, JZ4725B_ADC_BATTERY_HIGH_VREF_BITS,
	JZ_ADC_BATTERY_LOW_VREF, JZ_ADC_BATTERY_LOW_VREF_BITS,
पूर्ण;

अटल स्थिर पूर्णांक jz4740_adc_battery_raw_avail[] = अणु
	0, 1, (1 << JZ_ADC_BATTERY_LOW_VREF_BITS) - 1,
पूर्ण;

अटल स्थिर पूर्णांक jz4740_adc_battery_scale_avail[] = अणु
	JZ4740_ADC_BATTERY_HIGH_VREF, JZ4740_ADC_BATTERY_HIGH_VREF_BITS,
	JZ_ADC_BATTERY_LOW_VREF, JZ_ADC_BATTERY_LOW_VREF_BITS,
पूर्ण;

अटल स्थिर पूर्णांक jz4770_adc_battery_raw_avail[] = अणु
	0, 1, (1 << JZ4770_ADC_BATTERY_VREF_BITS) - 1,
पूर्ण;

अटल स्थिर पूर्णांक jz4770_adc_battery_scale_avail[] = अणु
	JZ4770_ADC_BATTERY_VREF, JZ4770_ADC_BATTERY_VREF_BITS,
पूर्ण;

अटल पूर्णांक jz4725b_adc_init_clk_भाग(काष्ठा device *dev, काष्ठा ingenic_adc *adc)
अणु
	काष्ठा clk *parent_clk;
	अचिन्हित दीर्घ parent_rate, rate;
	अचिन्हित पूर्णांक भाग_मुख्य, भाग_10us;

	parent_clk = clk_get_parent(adc->clk);
	अगर (!parent_clk) अणु
		dev_err(dev, "ADC clock has no parent\n");
		वापस -ENODEV;
	पूर्ण
	parent_rate = clk_get_rate(parent_clk);

	/*
	 * The JZ4725B ADC works at 500 kHz to 8 MHz.
	 * We pick the highest rate possible.
	 * In practice we typically get 6 MHz, half of the 12 MHz EXT घड़ी.
	 */
	भाग_मुख्य = DIV_ROUND_UP(parent_rate, 8000000);
	भाग_मुख्य = clamp(भाग_मुख्य, 1u, 64u);
	rate = parent_rate / भाग_मुख्य;
	अगर (rate < 500000 || rate > 8000000) अणु
		dev_err(dev, "No valid divider for ADC main clock\n");
		वापस -EINVAL;
	पूर्ण

	/* We also need a भागider that produces a 10us घड़ी. */
	भाग_10us = DIV_ROUND_UP(rate, 100000);

	ग_लिखोl(((भाग_10us - 1) << JZ4725B_ADC_REG_ADCLK_CLKDIV10US_LSB) |
	       (भाग_मुख्य - 1) << JZ_ADC_REG_ADCLK_CLKDIV_LSB,
	       adc->base + JZ_ADC_REG_ADCLK);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4770_adc_init_clk_भाग(काष्ठा device *dev, काष्ठा ingenic_adc *adc)
अणु
	काष्ठा clk *parent_clk;
	अचिन्हित दीर्घ parent_rate, rate;
	अचिन्हित पूर्णांक भाग_मुख्य, भाग_ms, भाग_10us;

	parent_clk = clk_get_parent(adc->clk);
	अगर (!parent_clk) अणु
		dev_err(dev, "ADC clock has no parent\n");
		वापस -ENODEV;
	पूर्ण
	parent_rate = clk_get_rate(parent_clk);

	/*
	 * The JZ4770 ADC works at 20 kHz to 200 kHz.
	 * We pick the highest rate possible.
	 */
	भाग_मुख्य = DIV_ROUND_UP(parent_rate, 200000);
	भाग_मुख्य = clamp(भाग_मुख्य, 1u, 256u);
	rate = parent_rate / भाग_मुख्य;
	अगर (rate < 20000 || rate > 200000) अणु
		dev_err(dev, "No valid divider for ADC main clock\n");
		वापस -EINVAL;
	पूर्ण

	/* We also need a भागider that produces a 10us घड़ी. */
	भाग_10us = DIV_ROUND_UP(rate, 10000);
	/* And another, which produces a 1ms घड़ी. */
	भाग_ms = DIV_ROUND_UP(rate, 1000);

	ग_लिखोl(((भाग_ms - 1) << JZ4770_ADC_REG_ADCLK_CLKDIVMS_LSB) |
	       ((भाग_10us - 1) << JZ4770_ADC_REG_ADCLK_CLKDIV10US_LSB) |
	       (भाग_मुख्य - 1) << JZ_ADC_REG_ADCLK_CLKDIV_LSB,
	       adc->base + JZ_ADC_REG_ADCLK);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec jz4740_channels[] = अणु
	अणु
		.extend_name = "aux",
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
		.channel = INGENIC_ADC_AUX,
		.scan_index = -1,
	पूर्ण,
	अणु
		.extend_name = "battery",
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_separate_available = BIT(IIO_CHAN_INFO_RAW) |
						BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
		.channel = INGENIC_ADC_BATTERY,
		.scan_index = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec jz4770_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = INGENIC_ADC_TOUCH_XP,
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 12,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = INGENIC_ADC_TOUCH_YP,
		.scan_index = 1,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 12,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = INGENIC_ADC_TOUCH_XN,
		.scan_index = 2,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 12,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = INGENIC_ADC_TOUCH_YN,
		.scan_index = 3,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 12,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = INGENIC_ADC_TOUCH_XD,
		.scan_index = 4,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 12,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = INGENIC_ADC_TOUCH_YD,
		.scan_index = 5,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 12,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	अणु
		.extend_name = "aux",
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
		.channel = INGENIC_ADC_AUX,
		.scan_index = -1,
	पूर्ण,
	अणु
		.extend_name = "battery",
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_separate_available = BIT(IIO_CHAN_INFO_RAW) |
						BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
		.channel = INGENIC_ADC_BATTERY,
		.scan_index = -1,
	पूर्ण,
	अणु
		.extend_name = "aux2",
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
		.channel = INGENIC_ADC_AUX2,
		.scan_index = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ingenic_adc_soc_data jz4725b_adc_soc_data = अणु
	.battery_high_vref = JZ4725B_ADC_BATTERY_HIGH_VREF,
	.battery_high_vref_bits = JZ4725B_ADC_BATTERY_HIGH_VREF_BITS,
	.battery_raw_avail = jz4725b_adc_battery_raw_avail,
	.battery_raw_avail_size = ARRAY_SIZE(jz4725b_adc_battery_raw_avail),
	.battery_scale_avail = jz4725b_adc_battery_scale_avail,
	.battery_scale_avail_size = ARRAY_SIZE(jz4725b_adc_battery_scale_avail),
	.battery_vref_mode = true,
	.has_aux2 = false,
	.channels = jz4740_channels,
	.num_channels = ARRAY_SIZE(jz4740_channels),
	.init_clk_भाग = jz4725b_adc_init_clk_भाग,
पूर्ण;

अटल स्थिर काष्ठा ingenic_adc_soc_data jz4740_adc_soc_data = अणु
	.battery_high_vref = JZ4740_ADC_BATTERY_HIGH_VREF,
	.battery_high_vref_bits = JZ4740_ADC_BATTERY_HIGH_VREF_BITS,
	.battery_raw_avail = jz4740_adc_battery_raw_avail,
	.battery_raw_avail_size = ARRAY_SIZE(jz4740_adc_battery_raw_avail),
	.battery_scale_avail = jz4740_adc_battery_scale_avail,
	.battery_scale_avail_size = ARRAY_SIZE(jz4740_adc_battery_scale_avail),
	.battery_vref_mode = true,
	.has_aux2 = false,
	.channels = jz4740_channels,
	.num_channels = ARRAY_SIZE(jz4740_channels),
	.init_clk_भाग = शून्य, /* no ADCLK रेजिस्टर on JZ4740 */
पूर्ण;

अटल स्थिर काष्ठा ingenic_adc_soc_data jz4770_adc_soc_data = अणु
	.battery_high_vref = JZ4770_ADC_BATTERY_VREF,
	.battery_high_vref_bits = JZ4770_ADC_BATTERY_VREF_BITS,
	.battery_raw_avail = jz4770_adc_battery_raw_avail,
	.battery_raw_avail_size = ARRAY_SIZE(jz4770_adc_battery_raw_avail),
	.battery_scale_avail = jz4770_adc_battery_scale_avail,
	.battery_scale_avail_size = ARRAY_SIZE(jz4770_adc_battery_scale_avail),
	.battery_vref_mode = false,
	.has_aux2 = true,
	.channels = jz4770_channels,
	.num_channels = ARRAY_SIZE(jz4770_channels),
	.init_clk_भाग = jz4770_adc_init_clk_भाग,
पूर्ण;

अटल पूर्णांक ingenic_adc_पढ़ो_avail(काष्ठा iio_dev *iio_dev,
				  काष्ठा iio_chan_spec स्थिर *chan,
				  स्थिर पूर्णांक **vals,
				  पूर्णांक *type,
				  पूर्णांक *length,
				  दीर्घ m)
अणु
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		*type = IIO_VAL_INT;
		*length = adc->soc_data->battery_raw_avail_size;
		*vals = adc->soc_data->battery_raw_avail;
		वापस IIO_AVAIL_RANGE;
	हाल IIO_CHAN_INFO_SCALE:
		*type = IIO_VAL_FRACTIONAL_LOG2;
		*length = adc->soc_data->battery_scale_avail_size;
		*vals = adc->soc_data->battery_scale_avail;
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ingenic_adc_पढ़ो_chan_info_raw(काष्ठा iio_dev *iio_dev,
					  काष्ठा iio_chan_spec स्थिर *chan,
					  पूर्णांक *val)
अणु
	पूर्णांक bit, ret, engine = (chan->channel == INGENIC_ADC_BATTERY);
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);

	ret = clk_enable(adc->clk);
	अगर (ret) अणु
		dev_err(iio_dev->dev.parent, "Failed to enable clock: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* We cannot sample AUX/AUX2 in parallel. */
	mutex_lock(&adc->aux_lock);
	अगर (adc->soc_data->has_aux2 && engine == 0) अणु
		bit = BIT(chan->channel == INGENIC_ADC_AUX2);
		ingenic_adc_set_config(adc, JZ_ADC_REG_CFG_AUX_MD, bit);
	पूर्ण

	ret = ingenic_adc_capture(adc, engine);
	अगर (ret)
		जाओ out;

	चयन (chan->channel) अणु
	हाल INGENIC_ADC_AUX:
	हाल INGENIC_ADC_AUX2:
		*val = पढ़ोw(adc->base + JZ_ADC_REG_ADSDAT);
		अवरोध;
	हाल INGENIC_ADC_BATTERY:
		*val = पढ़ोw(adc->base + JZ_ADC_REG_ADBDAT);
		अवरोध;
	पूर्ण

	ret = IIO_VAL_INT;
out:
	mutex_unlock(&adc->aux_lock);
	clk_disable(adc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक ingenic_adc_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val,
				पूर्णांक *val2,
				दीर्घ m)
अणु
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस ingenic_adc_पढ़ो_chan_info_raw(iio_dev, chan, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->channel) अणु
		हाल INGENIC_ADC_AUX:
		हाल INGENIC_ADC_AUX2:
			*val = JZ_ADC_AUX_VREF;
			*val2 = JZ_ADC_AUX_VREF_BITS;
			अवरोध;
		हाल INGENIC_ADC_BATTERY:
			अगर (adc->low_vref_mode) अणु
				*val = JZ_ADC_BATTERY_LOW_VREF;
				*val2 = JZ_ADC_BATTERY_LOW_VREF_BITS;
			पूर्ण अन्यथा अणु
				*val = adc->soc_data->battery_high_vref;
				*val2 = adc->soc_data->battery_high_vref_bits;
			पूर्ण
			अवरोध;
		पूर्ण

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ingenic_adc_of_xlate(काष्ठा iio_dev *iio_dev,
				स्थिर काष्ठा of_phandle_args *iiospec)
अणु
	पूर्णांक i;

	अगर (!iiospec->args_count)
		वापस -EINVAL;

	क्रम (i = 0; i < iio_dev->num_channels; ++i)
		अगर (iio_dev->channels[i].channel == iiospec->args[0])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल व्योम ingenic_adc_clk_cleanup(व्योम *data)
अणु
	clk_unprepare(data);
पूर्ण

अटल स्थिर काष्ठा iio_info ingenic_adc_info = अणु
	.ग_लिखो_raw = ingenic_adc_ग_लिखो_raw,
	.पढ़ो_raw = ingenic_adc_पढ़ो_raw,
	.पढ़ो_avail = ingenic_adc_पढ़ो_avail,
	.of_xlate = ingenic_adc_of_xlate,
पूर्ण;

अटल पूर्णांक ingenic_adc_buffer_enable(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);
	पूर्णांक ret;

	ret = clk_enable(adc->clk);
	अगर (ret) अणु
		dev_err(iio_dev->dev.parent, "Failed to enable clock: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* It takes signअगरicant समय क्रम the touchscreen hw to stabilize. */
	msleep(50);
	ingenic_adc_set_config(adc, JZ_ADC_REG_CFG_TOUCH_OPS_MASK,
			       JZ_ADC_REG_CFG_SAMPLE_NUM(4) |
			       JZ_ADC_REG_CFG_PULL_UP(4));

	ग_लिखोw(80, adc->base + JZ_ADC_REG_ADWAIT);
	ग_लिखोw(2, adc->base + JZ_ADC_REG_ADSAME);
	ग_लिखोb((u8)~JZ_ADC_IRQ_TOUCH, adc->base + JZ_ADC_REG_CTRL);
	ग_लिखोl(0, adc->base + JZ_ADC_REG_ADTCH);

	ingenic_adc_set_config(adc, JZ_ADC_REG_CFG_CMD_SEL,
			       JZ_ADC_REG_CFG_CMD_SEL);
	ingenic_adc_set_adcmd(iio_dev, iio_dev->active_scan_mask[0]);

	ingenic_adc_enable(adc, 2, true);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_adc_buffer_disable(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);

	ingenic_adc_enable(adc, 2, false);

	ingenic_adc_set_config(adc, JZ_ADC_REG_CFG_CMD_SEL, 0);

	ग_लिखोb(0xff, adc->base + JZ_ADC_REG_CTRL);
	ग_लिखोb(0xff, adc->base + JZ_ADC_REG_STATUS);
	ingenic_adc_set_config(adc, JZ_ADC_REG_CFG_TOUCH_OPS_MASK, 0);
	ग_लिखोw(0, adc->base + JZ_ADC_REG_ADSAME);
	ग_लिखोw(0, adc->base + JZ_ADC_REG_ADWAIT);
	clk_disable(adc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ingenic_buffer_setup_ops = अणु
	.postenable = &ingenic_adc_buffer_enable,
	.predisable = &ingenic_adc_buffer_disable
पूर्ण;

अटल irqवापस_t ingenic_adc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *iio_dev = data;
	काष्ठा ingenic_adc *adc = iio_priv(iio_dev);
	अचिन्हित दीर्घ mask = iio_dev->active_scan_mask[0];
	अचिन्हित पूर्णांक i;
	u32 tdat[3];

	क्रम (i = 0; i < ARRAY_SIZE(tdat); mask >>= 2, i++) अणु
		अगर (mask & 0x3)
			tdat[i] = पढ़ोl(adc->base + JZ_ADC_REG_ADTCH);
		अन्यथा
			tdat[i] = 0;
	पूर्ण

	iio_push_to_buffers(iio_dev, tdat);
	ग_लिखोb(JZ_ADC_IRQ_TOUCH, adc->base + JZ_ADC_REG_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ingenic_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *iio_dev;
	काष्ठा ingenic_adc *adc;
	स्थिर काष्ठा ingenic_adc_soc_data *soc_data;
	पूर्णांक irq, ret;

	soc_data = device_get_match_data(dev);
	अगर (!soc_data)
		वापस -EINVAL;

	iio_dev = devm_iio_device_alloc(dev, माप(*adc));
	अगर (!iio_dev)
		वापस -ENOMEM;

	adc = iio_priv(iio_dev);
	mutex_init(&adc->lock);
	mutex_init(&adc->aux_lock);
	adc->soc_data = soc_data;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, ingenic_adc_irq, 0,
			       dev_name(dev), iio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to request irq: %d\n", ret);
		वापस ret;
	पूर्ण

	adc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adc->base))
		वापस PTR_ERR(adc->base);

	adc->clk = devm_clk_get(dev, "adc");
	अगर (IS_ERR(adc->clk)) अणु
		dev_err(dev, "Unable to get clock\n");
		वापस PTR_ERR(adc->clk);
	पूर्ण

	ret = clk_prepare_enable(adc->clk);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	/* Set घड़ी भागiders. */
	अगर (soc_data->init_clk_भाग) अणु
		ret = soc_data->init_clk_भाग(dev, adc);
		अगर (ret) अणु
			clk_disable_unprepare(adc->clk);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Put hardware in a known passive state. */
	ग_लिखोb(0x00, adc->base + JZ_ADC_REG_ENABLE);
	ग_लिखोb(0xff, adc->base + JZ_ADC_REG_CTRL);
	usleep_range(2000, 3000); /* Must रुको at least 2ms. */
	clk_disable(adc->clk);

	ret = devm_add_action_or_reset(dev, ingenic_adc_clk_cleanup, adc->clk);
	अगर (ret) अणु
		dev_err(dev, "Unable to add action\n");
		वापस ret;
	पूर्ण

	iio_dev->name = "jz-adc";
	iio_dev->modes = INDIO_सूचीECT_MODE | INDIO_BUFFER_SOFTWARE;
	iio_dev->setup_ops = &ingenic_buffer_setup_ops;
	iio_dev->channels = soc_data->channels;
	iio_dev->num_channels = soc_data->num_channels;
	iio_dev->info = &ingenic_adc_info;

	ret = devm_iio_device_रेजिस्टर(dev, iio_dev);
	अगर (ret)
		dev_err(dev, "Unable to register IIO device\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id ingenic_adc_of_match[] = अणु
	अणु .compatible = "ingenic,jz4725b-adc", .data = &jz4725b_adc_soc_data, पूर्ण,
	अणु .compatible = "ingenic,jz4740-adc", .data = &jz4740_adc_soc_data, पूर्ण,
	अणु .compatible = "ingenic,jz4770-adc", .data = &jz4770_adc_soc_data, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_adc_of_match);

अटल काष्ठा platक्रमm_driver ingenic_adc_driver = अणु
	.driver = अणु
		.name = "ingenic-adc",
		.of_match_table = ingenic_adc_of_match,
	पूर्ण,
	.probe = ingenic_adc_probe,
पूर्ण;
module_platक्रमm_driver(ingenic_adc_driver);
MODULE_LICENSE("GPL v2");
