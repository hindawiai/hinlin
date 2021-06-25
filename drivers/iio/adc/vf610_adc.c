<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale Vybrid vf610 ADC driver
 *
 * Copyright 2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/err.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

/* This will be the driver name the kernel reports */
#घोषणा DRIVER_NAME "vf610-adc"

/* Vybrid/IMX ADC रेजिस्टरs */
#घोषणा VF610_REG_ADC_HC0		0x00
#घोषणा VF610_REG_ADC_HC1		0x04
#घोषणा VF610_REG_ADC_HS		0x08
#घोषणा VF610_REG_ADC_R0		0x0c
#घोषणा VF610_REG_ADC_R1		0x10
#घोषणा VF610_REG_ADC_CFG		0x14
#घोषणा VF610_REG_ADC_GC		0x18
#घोषणा VF610_REG_ADC_GS		0x1c
#घोषणा VF610_REG_ADC_CV		0x20
#घोषणा VF610_REG_ADC_OFS		0x24
#घोषणा VF610_REG_ADC_CAL		0x28
#घोषणा VF610_REG_ADC_PCTL		0x30

/* Configuration रेजिस्टर field define */
#घोषणा VF610_ADC_MODE_BIT8		0x00
#घोषणा VF610_ADC_MODE_BIT10		0x04
#घोषणा VF610_ADC_MODE_BIT12		0x08
#घोषणा VF610_ADC_MODE_MASK		0x0c
#घोषणा VF610_ADC_BUSCLK2_SEL		0x01
#घोषणा VF610_ADC_ALTCLK_SEL		0x02
#घोषणा VF610_ADC_ADACK_SEL		0x03
#घोषणा VF610_ADC_ADCCLK_MASK		0x03
#घोषणा VF610_ADC_CLK_DIV2		0x20
#घोषणा VF610_ADC_CLK_DIV4		0x40
#घोषणा VF610_ADC_CLK_DIV8		0x60
#घोषणा VF610_ADC_CLK_MASK		0x60
#घोषणा VF610_ADC_ADLSMP_LONG		0x10
#घोषणा VF610_ADC_ADSTS_SHORT   0x100
#घोषणा VF610_ADC_ADSTS_NORMAL  0x200
#घोषणा VF610_ADC_ADSTS_LONG    0x300
#घोषणा VF610_ADC_ADSTS_MASK		0x300
#घोषणा VF610_ADC_ADLPC_EN		0x80
#घोषणा VF610_ADC_ADHSC_EN		0x400
#घोषणा VF610_ADC_REFSEL_VALT		0x800
#घोषणा VF610_ADC_REFSEL_VBG		0x1000
#घोषणा VF610_ADC_ADTRG_HARD		0x2000
#घोषणा VF610_ADC_AVGS_8		0x4000
#घोषणा VF610_ADC_AVGS_16		0x8000
#घोषणा VF610_ADC_AVGS_32		0xC000
#घोषणा VF610_ADC_AVGS_MASK		0xC000
#घोषणा VF610_ADC_OVWREN		0x10000

/* General control रेजिस्टर field define */
#घोषणा VF610_ADC_ADACKEN		0x1
#घोषणा VF610_ADC_DMAEN			0x2
#घोषणा VF610_ADC_ACREN			0x4
#घोषणा VF610_ADC_ACFGT			0x8
#घोषणा VF610_ADC_ACFE			0x10
#घोषणा VF610_ADC_AVGEN			0x20
#घोषणा VF610_ADC_ADCON			0x40
#घोषणा VF610_ADC_CAL			0x80

/* Other field define */
#घोषणा VF610_ADC_ADCHC(x)		((x) & 0x1F)
#घोषणा VF610_ADC_AIEN			(0x1 << 7)
#घोषणा VF610_ADC_CONV_DISABLE		0x1F
#घोषणा VF610_ADC_HS_COCO0		0x1
#घोषणा VF610_ADC_CALF			0x2
#घोषणा VF610_ADC_TIMEOUT		msecs_to_jअगरfies(100)

#घोषणा DEFAULT_SAMPLE_TIME		1000

/* V at 25तओC of 696 mV */
#घोषणा VF610_VTEMP25_3V0		950
/* V at 25तओC of 699 mV */
#घोषणा VF610_VTEMP25_3V3		867
/* Typical sensor slope coefficient at all temperatures */
#घोषणा VF610_TEMP_SLOPE_COEFF		1840

क्रमागत clk_sel अणु
	VF610_ADCIOC_BUSCLK_SET,
	VF610_ADCIOC_ALTCLK_SET,
	VF610_ADCIOC_ADACK_SET,
पूर्ण;

क्रमागत vol_ref अणु
	VF610_ADCIOC_VR_VREF_SET,
	VF610_ADCIOC_VR_VALT_SET,
	VF610_ADCIOC_VR_VBG_SET,
पूर्ण;

क्रमागत average_sel अणु
	VF610_ADC_SAMPLE_1,
	VF610_ADC_SAMPLE_4,
	VF610_ADC_SAMPLE_8,
	VF610_ADC_SAMPLE_16,
	VF610_ADC_SAMPLE_32,
पूर्ण;

क्रमागत conversion_mode_sel अणु
	VF610_ADC_CONV_NORMAL,
	VF610_ADC_CONV_HIGH_SPEED,
	VF610_ADC_CONV_LOW_POWER,
पूर्ण;

क्रमागत lst_adder_sel अणु
	VF610_ADCK_CYCLES_3,
	VF610_ADCK_CYCLES_5,
	VF610_ADCK_CYCLES_7,
	VF610_ADCK_CYCLES_9,
	VF610_ADCK_CYCLES_13,
	VF610_ADCK_CYCLES_17,
	VF610_ADCK_CYCLES_21,
	VF610_ADCK_CYCLES_25,
पूर्ण;

काष्ठा vf610_adc_feature अणु
	क्रमागत clk_sel	clk_sel;
	क्रमागत vol_ref	vol_ref;
	क्रमागत conversion_mode_sel conv_mode;

	पूर्णांक	clk_भाग;
	पूर्णांक     sample_rate;
	पूर्णांक	res_mode;
	u32 lst_adder_index;
	u32 शेष_sample_समय;

	bool	calibration;
	bool	ovwren;
पूर्ण;

काष्ठा vf610_adc अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *clk;

	u32 vref_uv;
	u32 value;
	काष्ठा regulator *vref;

	u32 max_adck_rate[3];
	काष्ठा vf610_adc_feature adc_feature;

	u32 sample_freq_avail[5];

	काष्ठा completion completion;
	u16 buffer[8];
पूर्ण;

अटल स्थिर u32 vf610_hw_avgs[] = अणु 1, 4, 8, 16, 32 पूर्ण;
अटल स्थिर u32 vf610_lst_adder[] = अणु 3, 5, 7, 9, 13, 17, 21, 25 पूर्ण;

अटल अंतरभूत व्योम vf610_adc_calculate_rates(काष्ठा vf610_adc *info)
अणु
	काष्ठा vf610_adc_feature *adc_feature = &info->adc_feature;
	अचिन्हित दीर्घ adck_rate, ipg_rate = clk_get_rate(info->clk);
	u32 adck_period, lst_addr_min;
	पूर्णांक भागisor, i;

	adck_rate = info->max_adck_rate[adc_feature->conv_mode];

	अगर (adck_rate) अणु
		/* calculate clk भागider which is within specअगरication */
		भागisor = ipg_rate / adck_rate;
		adc_feature->clk_भाग = 1 << fls(भागisor + 1);
	पूर्ण अन्यथा अणु
		/* fall-back value using a safe भागisor */
		adc_feature->clk_भाग = 8;
	पूर्ण

	adck_rate = ipg_rate / adc_feature->clk_भाग;

	/*
	 * Determine the दीर्घ sample समय adder value to be used based
	 * on the शेष minimum sample समय provided.
	 */
	adck_period = NSEC_PER_SEC / adck_rate;
	lst_addr_min = adc_feature->शेष_sample_समय / adck_period;
	क्रम (i = 0; i < ARRAY_SIZE(vf610_lst_adder); i++) अणु
		अगर (vf610_lst_adder[i] > lst_addr_min) अणु
			adc_feature->lst_adder_index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Calculate ADC sample frequencies
	 * Sample समय unit is ADCK cycles. ADCK clk source is ipg घड़ी,
	 * which is the same as bus घड़ी.
	 *
	 * ADC conversion समय = SFCAdder + AverageNum x (BCT + LSTAdder)
	 * SFCAdder: fixed to 6 ADCK cycles
	 * AverageNum: 1, 4, 8, 16, 32 samples क्रम hardware average.
	 * BCT (Base Conversion Time): fixed to 25 ADCK cycles क्रम 12 bit mode
	 * LSTAdder(Long Sample Time): 3, 5, 7, 9, 13, 17, 21, 25 ADCK cycles
	 */
	क्रम (i = 0; i < ARRAY_SIZE(vf610_hw_avgs); i++)
		info->sample_freq_avail[i] =
			adck_rate / (6 + vf610_hw_avgs[i] *
			 (25 + vf610_lst_adder[adc_feature->lst_adder_index]));
पूर्ण

अटल अंतरभूत व्योम vf610_adc_cfg_init(काष्ठा vf610_adc *info)
अणु
	काष्ठा vf610_adc_feature *adc_feature = &info->adc_feature;

	/* set शेष Configuration क्रम ADC controller */
	adc_feature->clk_sel = VF610_ADCIOC_BUSCLK_SET;
	adc_feature->vol_ref = VF610_ADCIOC_VR_VREF_SET;

	adc_feature->calibration = true;
	adc_feature->ovwren = true;

	adc_feature->res_mode = 12;
	adc_feature->sample_rate = 1;

	adc_feature->conv_mode = VF610_ADC_CONV_LOW_POWER;

	vf610_adc_calculate_rates(info);
पूर्ण

अटल व्योम vf610_adc_cfg_post_set(काष्ठा vf610_adc *info)
अणु
	काष्ठा vf610_adc_feature *adc_feature = &info->adc_feature;
	पूर्णांक cfg_data = 0;
	पूर्णांक gc_data = 0;

	चयन (adc_feature->clk_sel) अणु
	हाल VF610_ADCIOC_ALTCLK_SET:
		cfg_data |= VF610_ADC_ALTCLK_SEL;
		अवरोध;
	हाल VF610_ADCIOC_ADACK_SET:
		cfg_data |= VF610_ADC_ADACK_SEL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* low घातer set क्रम calibration */
	cfg_data |= VF610_ADC_ADLPC_EN;

	/* enable high speed क्रम calibration */
	cfg_data |= VF610_ADC_ADHSC_EN;

	/* voltage reference */
	चयन (adc_feature->vol_ref) अणु
	हाल VF610_ADCIOC_VR_VREF_SET:
		अवरोध;
	हाल VF610_ADCIOC_VR_VALT_SET:
		cfg_data |= VF610_ADC_REFSEL_VALT;
		अवरोध;
	हाल VF610_ADCIOC_VR_VBG_SET:
		cfg_data |= VF610_ADC_REFSEL_VBG;
		अवरोध;
	शेष:
		dev_err(info->dev, "error voltage reference\n");
	पूर्ण

	/* data overग_लिखो enable */
	अगर (adc_feature->ovwren)
		cfg_data |= VF610_ADC_OVWREN;

	ग_लिखोl(cfg_data, info->regs + VF610_REG_ADC_CFG);
	ग_लिखोl(gc_data, info->regs + VF610_REG_ADC_GC);
पूर्ण

अटल व्योम vf610_adc_calibration(काष्ठा vf610_adc *info)
अणु
	पूर्णांक adc_gc, hc_cfg;

	अगर (!info->adc_feature.calibration)
		वापस;

	/* enable calibration पूर्णांकerrupt */
	hc_cfg = VF610_ADC_AIEN | VF610_ADC_CONV_DISABLE;
	ग_लिखोl(hc_cfg, info->regs + VF610_REG_ADC_HC0);

	adc_gc = पढ़ोl(info->regs + VF610_REG_ADC_GC);
	ग_लिखोl(adc_gc | VF610_ADC_CAL, info->regs + VF610_REG_ADC_GC);

	अगर (!रुको_क्रम_completion_समयout(&info->completion, VF610_ADC_TIMEOUT))
		dev_err(info->dev, "Timeout for adc calibration\n");

	adc_gc = पढ़ोl(info->regs + VF610_REG_ADC_GS);
	अगर (adc_gc & VF610_ADC_CALF)
		dev_err(info->dev, "ADC calibration failed\n");

	info->adc_feature.calibration = false;
पूर्ण

अटल व्योम vf610_adc_cfg_set(काष्ठा vf610_adc *info)
अणु
	काष्ठा vf610_adc_feature *adc_feature = &(info->adc_feature);
	पूर्णांक cfg_data;

	cfg_data = पढ़ोl(info->regs + VF610_REG_ADC_CFG);

	cfg_data &= ~VF610_ADC_ADLPC_EN;
	अगर (adc_feature->conv_mode == VF610_ADC_CONV_LOW_POWER)
		cfg_data |= VF610_ADC_ADLPC_EN;

	cfg_data &= ~VF610_ADC_ADHSC_EN;
	अगर (adc_feature->conv_mode == VF610_ADC_CONV_HIGH_SPEED)
		cfg_data |= VF610_ADC_ADHSC_EN;

	ग_लिखोl(cfg_data, info->regs + VF610_REG_ADC_CFG);
पूर्ण

अटल व्योम vf610_adc_sample_set(काष्ठा vf610_adc *info)
अणु
	काष्ठा vf610_adc_feature *adc_feature = &(info->adc_feature);
	पूर्णांक cfg_data, gc_data;

	cfg_data = पढ़ोl(info->regs + VF610_REG_ADC_CFG);
	gc_data = पढ़ोl(info->regs + VF610_REG_ADC_GC);

	/* resolution mode */
	cfg_data &= ~VF610_ADC_MODE_MASK;
	चयन (adc_feature->res_mode) अणु
	हाल 8:
		cfg_data |= VF610_ADC_MODE_BIT8;
		अवरोध;
	हाल 10:
		cfg_data |= VF610_ADC_MODE_BIT10;
		अवरोध;
	हाल 12:
		cfg_data |= VF610_ADC_MODE_BIT12;
		अवरोध;
	शेष:
		dev_err(info->dev, "error resolution mode\n");
		अवरोध;
	पूर्ण

	/* घड़ी select and घड़ी भागider */
	cfg_data &= ~(VF610_ADC_CLK_MASK | VF610_ADC_ADCCLK_MASK);
	चयन (adc_feature->clk_भाग) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		cfg_data |= VF610_ADC_CLK_DIV2;
		अवरोध;
	हाल 4:
		cfg_data |= VF610_ADC_CLK_DIV4;
		अवरोध;
	हाल 8:
		cfg_data |= VF610_ADC_CLK_DIV8;
		अवरोध;
	हाल 16:
		चयन (adc_feature->clk_sel) अणु
		हाल VF610_ADCIOC_BUSCLK_SET:
			cfg_data |= VF610_ADC_BUSCLK2_SEL | VF610_ADC_CLK_DIV8;
			अवरोध;
		शेष:
			dev_err(info->dev, "error clk divider\n");
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * Set ADLSMP and ADSTS based on the Long Sample Time Adder value
	 * determined.
	 */
	चयन (adc_feature->lst_adder_index) अणु
	हाल VF610_ADCK_CYCLES_3:
		अवरोध;
	हाल VF610_ADCK_CYCLES_5:
		cfg_data |= VF610_ADC_ADSTS_SHORT;
		अवरोध;
	हाल VF610_ADCK_CYCLES_7:
		cfg_data |= VF610_ADC_ADSTS_NORMAL;
		अवरोध;
	हाल VF610_ADCK_CYCLES_9:
		cfg_data |= VF610_ADC_ADSTS_LONG;
		अवरोध;
	हाल VF610_ADCK_CYCLES_13:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		अवरोध;
	हाल VF610_ADCK_CYCLES_17:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		cfg_data |= VF610_ADC_ADSTS_SHORT;
		अवरोध;
	हाल VF610_ADCK_CYCLES_21:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		cfg_data |= VF610_ADC_ADSTS_NORMAL;
		अवरोध;
	हाल VF610_ADCK_CYCLES_25:
		cfg_data |= VF610_ADC_ADLSMP_LONG;
		cfg_data |= VF610_ADC_ADSTS_NORMAL;
		अवरोध;
	शेष:
		dev_err(info->dev, "error in sample time select\n");
	पूर्ण

	/* update hardware average selection */
	cfg_data &= ~VF610_ADC_AVGS_MASK;
	gc_data &= ~VF610_ADC_AVGEN;
	चयन (adc_feature->sample_rate) अणु
	हाल VF610_ADC_SAMPLE_1:
		अवरोध;
	हाल VF610_ADC_SAMPLE_4:
		gc_data |= VF610_ADC_AVGEN;
		अवरोध;
	हाल VF610_ADC_SAMPLE_8:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_8;
		अवरोध;
	हाल VF610_ADC_SAMPLE_16:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_16;
		अवरोध;
	हाल VF610_ADC_SAMPLE_32:
		gc_data |= VF610_ADC_AVGEN;
		cfg_data |= VF610_ADC_AVGS_32;
		अवरोध;
	शेष:
		dev_err(info->dev,
			"error hardware sample average select\n");
	पूर्ण

	ग_लिखोl(cfg_data, info->regs + VF610_REG_ADC_CFG);
	ग_लिखोl(gc_data, info->regs + VF610_REG_ADC_GC);
पूर्ण

अटल व्योम vf610_adc_hw_init(काष्ठा vf610_adc *info)
अणु
	/* CFG: Feature set */
	vf610_adc_cfg_post_set(info);
	vf610_adc_sample_set(info);

	/* adc calibration */
	vf610_adc_calibration(info);

	/* CFG: घातer and speed set */
	vf610_adc_cfg_set(info);
पूर्ण

अटल पूर्णांक vf610_set_conversion_mode(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     अचिन्हित पूर्णांक mode)
अणु
	काष्ठा vf610_adc *info = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	info->adc_feature.conv_mode = mode;
	vf610_adc_calculate_rates(info);
	vf610_adc_hw_init(info);
	mutex_unlock(&indio_dev->mlock);

	वापस 0;
पूर्ण

अटल पूर्णांक vf610_get_conversion_mode(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा vf610_adc *info = iio_priv(indio_dev);

	वापस info->adc_feature.conv_mode;
पूर्ण

अटल स्थिर अक्षर * स्थिर vf610_conv_modes[] = अणु "normal", "high-speed",
						 "low-power" पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत vf610_conversion_mode = अणु
	.items = vf610_conv_modes,
	.num_items = ARRAY_SIZE(vf610_conv_modes),
	.get = vf610_get_conversion_mode,
	.set = vf610_set_conversion_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info vf610_ext_info[] = अणु
	IIO_ENUM("conversion_mode", IIO_SHARED_BY_सूची, &vf610_conversion_mode),
	अणुपूर्ण,
पूर्ण;

#घोषणा VF610_ADC_CHAN(_idx, _chan_type) अणु			\
	.type = (_chan_type),					\
	.indexed = 1,						\
	.channel = (_idx),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.ext_info = vf610_ext_info,				\
	.scan_index = (_idx),			\
	.scan_type = अणु					\
		.sign = 'u',				\
		.realbits = 12,				\
		.storagebits = 16,			\
	पूर्ण,						\
पूर्ण

#घोषणा VF610_ADC_TEMPERATURE_CHAN(_idx, _chan_type) अणु	\
	.type = (_chan_type),	\
	.channel = (_idx),		\
	.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),	\
	.scan_index = (_idx),					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = 12,					\
		.storagebits = 16,				\
	पूर्ण,							\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec vf610_adc_iio_channels[] = अणु
	VF610_ADC_CHAN(0, IIO_VOLTAGE),
	VF610_ADC_CHAN(1, IIO_VOLTAGE),
	VF610_ADC_CHAN(2, IIO_VOLTAGE),
	VF610_ADC_CHAN(3, IIO_VOLTAGE),
	VF610_ADC_CHAN(4, IIO_VOLTAGE),
	VF610_ADC_CHAN(5, IIO_VOLTAGE),
	VF610_ADC_CHAN(6, IIO_VOLTAGE),
	VF610_ADC_CHAN(7, IIO_VOLTAGE),
	VF610_ADC_CHAN(8, IIO_VOLTAGE),
	VF610_ADC_CHAN(9, IIO_VOLTAGE),
	VF610_ADC_CHAN(10, IIO_VOLTAGE),
	VF610_ADC_CHAN(11, IIO_VOLTAGE),
	VF610_ADC_CHAN(12, IIO_VOLTAGE),
	VF610_ADC_CHAN(13, IIO_VOLTAGE),
	VF610_ADC_CHAN(14, IIO_VOLTAGE),
	VF610_ADC_CHAN(15, IIO_VOLTAGE),
	VF610_ADC_TEMPERATURE_CHAN(26, IIO_TEMP),
	IIO_CHAN_SOFT_TIMESTAMP(32),
	/* sentinel */
पूर्ण;

अटल पूर्णांक vf610_adc_पढ़ो_data(काष्ठा vf610_adc *info)
अणु
	पूर्णांक result;

	result = पढ़ोl(info->regs + VF610_REG_ADC_R0);

	चयन (info->adc_feature.res_mode) अणु
	हाल 8:
		result &= 0xFF;
		अवरोध;
	हाल 10:
		result &= 0x3FF;
		अवरोध;
	हाल 12:
		result &= 0xFFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल irqवापस_t vf610_adc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iio_dev *indio_dev = dev_id;
	काष्ठा vf610_adc *info = iio_priv(indio_dev);
	पूर्णांक coco;

	coco = पढ़ोl(info->regs + VF610_REG_ADC_HS);
	अगर (coco & VF610_ADC_HS_COCO0) अणु
		info->value = vf610_adc_पढ़ो_data(info);
		अगर (iio_buffer_enabled(indio_dev)) अणु
			info->buffer[0] = info->value;
			iio_push_to_buffers_with_बारtamp(indio_dev,
					info->buffer,
					iio_get_समय_ns(indio_dev));
			iio_trigger_notअगरy_करोne(indio_dev->trig);
		पूर्ण अन्यथा
			complete(&info->completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार vf610_show_samp_freq_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vf610_adc *info = iio_priv(dev_to_iio_dev(dev));
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(info->sample_freq_avail); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"%u ", info->sample_freq_avail[i]);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(vf610_show_samp_freq_avail);

अटल काष्ठा attribute *vf610_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group vf610_attribute_group = अणु
	.attrs = vf610_attributes,
पूर्ण;

अटल पूर्णांक vf610_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val,
			पूर्णांक *val2,
			दीर्घ mask)
अणु
	काष्ठा vf610_adc *info = iio_priv(indio_dev);
	अचिन्हित पूर्णांक hc_cfg;
	दीर्घ ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&indio_dev->mlock);
		अगर (iio_buffer_enabled(indio_dev)) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस -EBUSY;
		पूर्ण

		reinit_completion(&info->completion);
		hc_cfg = VF610_ADC_ADCHC(chan->channel);
		hc_cfg |= VF610_ADC_AIEN;
		ग_लिखोl(hc_cfg, info->regs + VF610_REG_ADC_HC0);
		ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout
				(&info->completion, VF610_ADC_TIMEOUT);
		अगर (ret == 0) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (ret < 0) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस ret;
		पूर्ण

		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			*val = info->value;
			अवरोध;
		हाल IIO_TEMP:
			/*
			 * Calculate in degree Celsius बार 1000
			 * Using the typical sensor slope of 1.84 mV/तओC
			 * and VREFH_ADC at 3.3V, V at 25तओC of 699 mV
			 */
			*val = 25000 - ((पूर्णांक)info->value - VF610_VTEMP25_3V3) *
					1000000 / VF610_TEMP_SLOPE_COEFF;

			अवरोध;
		शेष:
			mutex_unlock(&indio_dev->mlock);
			वापस -EINVAL;
		पूर्ण

		mutex_unlock(&indio_dev->mlock);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = info->vref_uv / 1000;
		*val2 = info->adc_feature.res_mode;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = info->sample_freq_avail[info->adc_feature.sample_rate];
		*val2 = 0;
		वापस IIO_VAL_INT;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vf610_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक val,
			पूर्णांक val2,
			दीर्घ mask)
अणु
	काष्ठा vf610_adc *info = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		क्रम (i = 0;
			i < ARRAY_SIZE(info->sample_freq_avail);
			i++)
			अगर (val == info->sample_freq_avail[i]) अणु
				info->adc_feature.sample_rate = i;
				vf610_adc_sample_set(info);
				वापस 0;
			पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vf610_adc_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा vf610_adc *info = iio_priv(indio_dev);
	अचिन्हित पूर्णांक channel;
	पूर्णांक val;

	val = पढ़ोl(info->regs + VF610_REG_ADC_GC);
	val |= VF610_ADC_ADCON;
	ग_लिखोl(val, info->regs + VF610_REG_ADC_GC);

	channel = find_first_bit(indio_dev->active_scan_mask,
						indio_dev->masklength);

	val = VF610_ADC_ADCHC(channel);
	val |= VF610_ADC_AIEN;

	ग_लिखोl(val, info->regs + VF610_REG_ADC_HC0);

	वापस 0;
पूर्ण

अटल पूर्णांक vf610_adc_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा vf610_adc *info = iio_priv(indio_dev);
	अचिन्हित पूर्णांक hc_cfg = 0;
	पूर्णांक val;

	val = पढ़ोl(info->regs + VF610_REG_ADC_GC);
	val &= ~VF610_ADC_ADCON;
	ग_लिखोl(val, info->regs + VF610_REG_ADC_GC);

	hc_cfg |= VF610_ADC_CONV_DISABLE;
	hc_cfg &= ~VF610_ADC_AIEN;

	ग_लिखोl(hc_cfg, info->regs + VF610_REG_ADC_HC0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops iio_triggered_buffer_setup_ops = अणु
	.postenable = &vf610_adc_buffer_postenable,
	.predisable = &vf610_adc_buffer_predisable,
	.validate_scan_mask = &iio_validate_scan_mask_onehot,
पूर्ण;

अटल पूर्णांक vf610_adc_reg_access(काष्ठा iio_dev *indio_dev,
			अचिन्हित reg, अचिन्हित ग_लिखोval,
			अचिन्हित *पढ़ोval)
अणु
	काष्ठा vf610_adc *info = iio_priv(indio_dev);

	अगर ((पढ़ोval == शून्य) ||
		((reg % 4) || (reg > VF610_REG_ADC_PCTL)))
		वापस -EINVAL;

	*पढ़ोval = पढ़ोl(info->regs + reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info vf610_adc_iio_info = अणु
	.पढ़ो_raw = &vf610_पढ़ो_raw,
	.ग_लिखो_raw = &vf610_ग_लिखो_raw,
	.debugfs_reg_access = &vf610_adc_reg_access,
	.attrs = &vf610_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vf610_adc_match[] = अणु
	अणु .compatible = "fsl,vf610-adc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vf610_adc_match);

अटल पूर्णांक vf610_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vf610_adc *info;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक irq;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(काष्ठा vf610_adc));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "Failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	info = iio_priv(indio_dev);
	info->dev = &pdev->dev;

	info->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(info->dev, irq,
				vf610_adc_isr, 0,
				dev_name(&pdev->dev), indio_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed requesting irq, irq = %d\n", irq);
		वापस ret;
	पूर्ण

	info->clk = devm_clk_get(&pdev->dev, "adc");
	अगर (IS_ERR(info->clk)) अणु
		dev_err(&pdev->dev, "failed getting clock, err = %ld\n",
						PTR_ERR(info->clk));
		वापस PTR_ERR(info->clk);
	पूर्ण

	info->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(info->vref))
		वापस PTR_ERR(info->vref);

	ret = regulator_enable(info->vref);
	अगर (ret)
		वापस ret;

	info->vref_uv = regulator_get_voltage(info->vref);

	of_property_पढ़ो_u32_array(pdev->dev.of_node, "fsl,adck-max-frequency",
			info->max_adck_rate, 3);

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "min-sample-time",
			&info->adc_feature.शेष_sample_समय);
	अगर (ret)
		info->adc_feature.शेष_sample_समय = DEFAULT_SAMPLE_TIME;

	platक्रमm_set_drvdata(pdev, indio_dev);

	init_completion(&info->completion);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &vf610_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = vf610_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(vf610_adc_iio_channels);

	ret = clk_prepare_enable(info->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Could not prepare or enable the clock.\n");
		जाओ error_adc_clk_enable;
	पूर्ण

	vf610_adc_cfg_init(info);
	vf610_adc_hw_init(info);

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
					शून्य, &iio_triggered_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Couldn't initialise the buffer\n");
		जाओ error_iio_device_रेजिस्टर;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't register the device.\n");
		जाओ error_adc_buffer_init;
	पूर्ण

	वापस 0;

error_adc_buffer_init:
	iio_triggered_buffer_cleanup(indio_dev);
error_iio_device_रेजिस्टर:
	clk_disable_unprepare(info->clk);
error_adc_clk_enable:
	regulator_disable(info->vref);

	वापस ret;
पूर्ण

अटल पूर्णांक vf610_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा vf610_adc *info = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(info->vref);
	clk_disable_unprepare(info->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक vf610_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा vf610_adc *info = iio_priv(indio_dev);
	पूर्णांक hc_cfg;

	/* ADC controller enters to stop mode */
	hc_cfg = पढ़ोl(info->regs + VF610_REG_ADC_HC0);
	hc_cfg |= VF610_ADC_CONV_DISABLE;
	ग_लिखोl(hc_cfg, info->regs + VF610_REG_ADC_HC0);

	clk_disable_unprepare(info->clk);
	regulator_disable(info->vref);

	वापस 0;
पूर्ण

अटल पूर्णांक vf610_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा vf610_adc *info = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(info->vref);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(info->clk);
	अगर (ret)
		जाओ disable_reg;

	vf610_adc_hw_init(info);

	वापस 0;

disable_reg:
	regulator_disable(info->vref);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(vf610_adc_pm_ops, vf610_adc_suspend, vf610_adc_resume);

अटल काष्ठा platक्रमm_driver vf610_adc_driver = अणु
	.probe          = vf610_adc_probe,
	.हटाओ         = vf610_adc_हटाओ,
	.driver         = अणु
		.name   = DRIVER_NAME,
		.of_match_table = vf610_adc_match,
		.pm     = &vf610_adc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vf610_adc_driver);

MODULE_AUTHOR("Fugang Duan <B38611@freescale.com>");
MODULE_DESCRIPTION("Freescale VF610 ADC driver");
MODULE_LICENSE("GPL v2");
