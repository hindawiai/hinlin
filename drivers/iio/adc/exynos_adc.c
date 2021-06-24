<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  exynos_adc.c - Support क्रम ADC in EXYNOS SoCs
 *
 *  8 ~ 10 channel, 10/12-bit ADC
 *
 *  Copyright (C) 2013 Naveen Krishna Chatradhi <ch.naveen@samsung.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
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
#समावेश <linux/input.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/driver.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश <linux/platक्रमm_data/touchscreen-s3c2410.h>

/* S3C/EXYNOS4412/5250 ADC_V1 रेजिस्टरs definitions */
#घोषणा ADC_V1_CON(x)		((x) + 0x00)
#घोषणा ADC_V1_TSC(x)		((x) + 0x04)
#घोषणा ADC_V1_DLY(x)		((x) + 0x08)
#घोषणा ADC_V1_DATX(x)		((x) + 0x0C)
#घोषणा ADC_V1_DATY(x)		((x) + 0x10)
#घोषणा ADC_V1_UPDN(x)		((x) + 0x14)
#घोषणा ADC_V1_INTCLR(x)	((x) + 0x18)
#घोषणा ADC_V1_MUX(x)		((x) + 0x1c)
#घोषणा ADC_V1_CLRINTPNDNUP(x)	((x) + 0x20)

/* S3C2410 ADC रेजिस्टरs definitions */
#घोषणा ADC_S3C2410_MUX(x)	((x) + 0x18)

/* Future ADC_V2 रेजिस्टरs definitions */
#घोषणा ADC_V2_CON1(x)		((x) + 0x00)
#घोषणा ADC_V2_CON2(x)		((x) + 0x04)
#घोषणा ADC_V2_STAT(x)		((x) + 0x08)
#घोषणा ADC_V2_INT_EN(x)	((x) + 0x10)
#घोषणा ADC_V2_INT_ST(x)	((x) + 0x14)
#घोषणा ADC_V2_VER(x)		((x) + 0x20)

/* Bit definitions क्रम ADC_V1 */
#घोषणा ADC_V1_CON_RES		(1u << 16)
#घोषणा ADC_V1_CON_PRSCEN	(1u << 14)
#घोषणा ADC_V1_CON_PRSCLV(x)	(((x) & 0xFF) << 6)
#घोषणा ADC_V1_CON_STANDBY	(1u << 2)

/* Bit definitions क्रम S3C2410 ADC */
#घोषणा ADC_S3C2410_CON_SELMUX(x) (((x) & 7) << 3)
#घोषणा ADC_S3C2410_DATX_MASK	0x3FF
#घोषणा ADC_S3C2416_CON_RES_SEL	(1u << 3)

/* touch screen always uses channel 0 */
#घोषणा ADC_S3C2410_MUX_TS	0

/* ADCTSC Register Bits */
#घोषणा ADC_S3C2443_TSC_UD_SEN		(1u << 8)
#घोषणा ADC_S3C2410_TSC_YM_SEN		(1u << 7)
#घोषणा ADC_S3C2410_TSC_YP_SEN		(1u << 6)
#घोषणा ADC_S3C2410_TSC_XM_SEN		(1u << 5)
#घोषणा ADC_S3C2410_TSC_XP_SEN		(1u << 4)
#घोषणा ADC_S3C2410_TSC_PULL_UP_DISABLE	(1u << 3)
#घोषणा ADC_S3C2410_TSC_AUTO_PST	(1u << 2)
#घोषणा ADC_S3C2410_TSC_XY_PST(x)	(((x) & 0x3) << 0)

#घोषणा ADC_TSC_WAIT4INT (ADC_S3C2410_TSC_YM_SEN | \
			 ADC_S3C2410_TSC_YP_SEN | \
			 ADC_S3C2410_TSC_XP_SEN | \
			 ADC_S3C2410_TSC_XY_PST(3))

#घोषणा ADC_TSC_AUTOPST	(ADC_S3C2410_TSC_YM_SEN | \
			 ADC_S3C2410_TSC_YP_SEN | \
			 ADC_S3C2410_TSC_XP_SEN | \
			 ADC_S3C2410_TSC_AUTO_PST | \
			 ADC_S3C2410_TSC_XY_PST(0))

/* Bit definitions क्रम ADC_V2 */
#घोषणा ADC_V2_CON1_SOFT_RESET	(1u << 2)

#घोषणा ADC_V2_CON2_OSEL	(1u << 10)
#घोषणा ADC_V2_CON2_ESEL	(1u << 9)
#घोषणा ADC_V2_CON2_HIGHF	(1u << 8)
#घोषणा ADC_V2_CON2_C_TIME(x)	(((x) & 7) << 4)
#घोषणा ADC_V2_CON2_ACH_SEL(x)	(((x) & 0xF) << 0)
#घोषणा ADC_V2_CON2_ACH_MASK	0xF

#घोषणा MAX_ADC_V2_CHANNELS		10
#घोषणा MAX_ADC_V1_CHANNELS		8
#घोषणा MAX_EXYNOS3250_ADC_CHANNELS	2
#घोषणा MAX_EXYNOS4212_ADC_CHANNELS	4
#घोषणा MAX_S5PV210_ADC_CHANNELS	10

/* Bit definitions common क्रम ADC_V1 and ADC_V2 */
#घोषणा ADC_CON_EN_START	(1u << 0)
#घोषणा ADC_CON_EN_START_MASK	(0x3 << 0)
#घोषणा ADC_DATX_PRESSED	(1u << 15)
#घोषणा ADC_DATX_MASK		0xFFF
#घोषणा ADC_DATY_MASK		0xFFF

#घोषणा EXYNOS_ADC_TIMEOUT	(msecs_to_jअगरfies(100))

#घोषणा EXYNOS_ADCV1_PHY_OFFSET	0x0718
#घोषणा EXYNOS_ADCV2_PHY_OFFSET	0x0720

काष्ठा exynos_adc अणु
	काष्ठा exynos_adc_data	*data;
	काष्ठा device		*dev;
	काष्ठा input_dev	*input;
	व्योम __iomem		*regs;
	काष्ठा regmap		*pmu_map;
	काष्ठा clk		*clk;
	काष्ठा clk		*sclk;
	अचिन्हित पूर्णांक		irq;
	अचिन्हित पूर्णांक		tsirq;
	अचिन्हित पूर्णांक		delay;
	काष्ठा regulator	*vdd;

	काष्ठा completion	completion;

	u32			value;
	अचिन्हित पूर्णांक            version;

	bool			ts_enabled;

	bool			पढ़ो_ts;
	u32			ts_x;
	u32			ts_y;

	/*
	 * Lock to protect from potential concurrent access to the
	 * completion callback during a manual conversion. For this driver
	 * a रुको-callback is used to रुको क्रम the conversion result,
	 * so in the meanसमय no other पढ़ो request (or conversion start)
	 * must be perक्रमmed, otherwise it would पूर्णांकerfere with the
	 * current conversion result.
	 */
	काष्ठा mutex		lock;
पूर्ण;

काष्ठा exynos_adc_data अणु
	पूर्णांक num_channels;
	bool needs_sclk;
	bool needs_adc_phy;
	पूर्णांक phy_offset;
	u32 mask;

	व्योम (*init_hw)(काष्ठा exynos_adc *info);
	व्योम (*निकास_hw)(काष्ठा exynos_adc *info);
	व्योम (*clear_irq)(काष्ठा exynos_adc *info);
	व्योम (*start_conv)(काष्ठा exynos_adc *info, अचिन्हित दीर्घ addr);
पूर्ण;

अटल व्योम exynos_adc_unprepare_clk(काष्ठा exynos_adc *info)
अणु
	अगर (info->data->needs_sclk)
		clk_unprepare(info->sclk);
	clk_unprepare(info->clk);
पूर्ण

अटल पूर्णांक exynos_adc_prepare_clk(काष्ठा exynos_adc *info)
अणु
	पूर्णांक ret;

	ret = clk_prepare(info->clk);
	अगर (ret) अणु
		dev_err(info->dev, "failed preparing adc clock: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (info->data->needs_sclk) अणु
		ret = clk_prepare(info->sclk);
		अगर (ret) अणु
			clk_unprepare(info->clk);
			dev_err(info->dev,
				"failed preparing sclk_adc clock: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exynos_adc_disable_clk(काष्ठा exynos_adc *info)
अणु
	अगर (info->data->needs_sclk)
		clk_disable(info->sclk);
	clk_disable(info->clk);
पूर्ण

अटल पूर्णांक exynos_adc_enable_clk(काष्ठा exynos_adc *info)
अणु
	पूर्णांक ret;

	ret = clk_enable(info->clk);
	अगर (ret) अणु
		dev_err(info->dev, "failed enabling adc clock: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (info->data->needs_sclk) अणु
		ret = clk_enable(info->sclk);
		अगर (ret) अणु
			clk_disable(info->clk);
			dev_err(info->dev,
				"failed enabling sclk_adc clock: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exynos_adc_v1_init_hw(काष्ठा exynos_adc *info)
अणु
	u32 con1;

	अगर (info->data->needs_adc_phy)
		regmap_ग_लिखो(info->pmu_map, info->data->phy_offset, 1);

	/* set शेष prescaler values and Enable prescaler */
	con1 =  ADC_V1_CON_PRSCLV(49) | ADC_V1_CON_PRSCEN;

	/* Enable 12-bit ADC resolution */
	con1 |= ADC_V1_CON_RES;
	ग_लिखोl(con1, ADC_V1_CON(info->regs));

	/* set touchscreen delay */
	ग_लिखोl(info->delay, ADC_V1_DLY(info->regs));
पूर्ण

अटल व्योम exynos_adc_v1_निकास_hw(काष्ठा exynos_adc *info)
अणु
	u32 con;

	अगर (info->data->needs_adc_phy)
		regmap_ग_लिखो(info->pmu_map, info->data->phy_offset, 0);

	con = पढ़ोl(ADC_V1_CON(info->regs));
	con |= ADC_V1_CON_STANDBY;
	ग_लिखोl(con, ADC_V1_CON(info->regs));
पूर्ण

अटल व्योम exynos_adc_v1_clear_irq(काष्ठा exynos_adc *info)
अणु
	ग_लिखोl(1, ADC_V1_INTCLR(info->regs));
पूर्ण

अटल व्योम exynos_adc_v1_start_conv(काष्ठा exynos_adc *info,
				     अचिन्हित दीर्घ addr)
अणु
	u32 con1;

	ग_लिखोl(addr, ADC_V1_MUX(info->regs));

	con1 = पढ़ोl(ADC_V1_CON(info->regs));
	ग_लिखोl(con1 | ADC_CON_EN_START, ADC_V1_CON(info->regs));
पूर्ण

/* Exynos4212 and 4412 is like ADCv1 but with four channels only */
अटल स्थिर काष्ठा exynos_adc_data exynos4212_adc_data = अणु
	.num_channels	= MAX_EXYNOS4212_ADC_CHANNELS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC resolution */
	.needs_adc_phy	= true,
	.phy_offset	= EXYNOS_ADCV1_PHY_OFFSET,

	.init_hw	= exynos_adc_v1_init_hw,
	.निकास_hw	= exynos_adc_v1_निकास_hw,
	.clear_irq	= exynos_adc_v1_clear_irq,
	.start_conv	= exynos_adc_v1_start_conv,
पूर्ण;

अटल स्थिर काष्ठा exynos_adc_data exynos_adc_v1_data = अणु
	.num_channels	= MAX_ADC_V1_CHANNELS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC resolution */
	.needs_adc_phy	= true,
	.phy_offset	= EXYNOS_ADCV1_PHY_OFFSET,

	.init_hw	= exynos_adc_v1_init_hw,
	.निकास_hw	= exynos_adc_v1_निकास_hw,
	.clear_irq	= exynos_adc_v1_clear_irq,
	.start_conv	= exynos_adc_v1_start_conv,
पूर्ण;

अटल स्थिर काष्ठा exynos_adc_data exynos_adc_s5pv210_data = अणु
	.num_channels	= MAX_S5PV210_ADC_CHANNELS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC resolution */

	.init_hw	= exynos_adc_v1_init_hw,
	.निकास_hw	= exynos_adc_v1_निकास_hw,
	.clear_irq	= exynos_adc_v1_clear_irq,
	.start_conv	= exynos_adc_v1_start_conv,
पूर्ण;

अटल व्योम exynos_adc_s3c2416_start_conv(काष्ठा exynos_adc *info,
					  अचिन्हित दीर्घ addr)
अणु
	u32 con1;

	/* Enable 12 bit ADC resolution */
	con1 = पढ़ोl(ADC_V1_CON(info->regs));
	con1 |= ADC_S3C2416_CON_RES_SEL;
	ग_लिखोl(con1, ADC_V1_CON(info->regs));

	/* Select channel क्रम S3C2416 */
	ग_लिखोl(addr, ADC_S3C2410_MUX(info->regs));

	con1 = पढ़ोl(ADC_V1_CON(info->regs));
	ग_लिखोl(con1 | ADC_CON_EN_START, ADC_V1_CON(info->regs));
पूर्ण

अटल काष्ठा exynos_adc_data स्थिर exynos_adc_s3c2416_data = अणु
	.num_channels	= MAX_ADC_V1_CHANNELS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC resolution */

	.init_hw	= exynos_adc_v1_init_hw,
	.निकास_hw	= exynos_adc_v1_निकास_hw,
	.start_conv	= exynos_adc_s3c2416_start_conv,
पूर्ण;

अटल व्योम exynos_adc_s3c2443_start_conv(काष्ठा exynos_adc *info,
					  अचिन्हित दीर्घ addr)
अणु
	u32 con1;

	/* Select channel क्रम S3C2433 */
	ग_लिखोl(addr, ADC_S3C2410_MUX(info->regs));

	con1 = पढ़ोl(ADC_V1_CON(info->regs));
	ग_लिखोl(con1 | ADC_CON_EN_START, ADC_V1_CON(info->regs));
पूर्ण

अटल काष्ठा exynos_adc_data स्थिर exynos_adc_s3c2443_data = अणु
	.num_channels	= MAX_ADC_V1_CHANNELS,
	.mask		= ADC_S3C2410_DATX_MASK, /* 10 bit ADC resolution */

	.init_hw	= exynos_adc_v1_init_hw,
	.निकास_hw	= exynos_adc_v1_निकास_hw,
	.start_conv	= exynos_adc_s3c2443_start_conv,
पूर्ण;

अटल व्योम exynos_adc_s3c64xx_start_conv(काष्ठा exynos_adc *info,
					  अचिन्हित दीर्घ addr)
अणु
	u32 con1;

	con1 = पढ़ोl(ADC_V1_CON(info->regs));
	con1 &= ~ADC_S3C2410_CON_SELMUX(0x7);
	con1 |= ADC_S3C2410_CON_SELMUX(addr);
	ग_लिखोl(con1 | ADC_CON_EN_START, ADC_V1_CON(info->regs));
पूर्ण

अटल काष्ठा exynos_adc_data स्थिर exynos_adc_s3c24xx_data = अणु
	.num_channels	= MAX_ADC_V1_CHANNELS,
	.mask		= ADC_S3C2410_DATX_MASK, /* 10 bit ADC resolution */

	.init_hw	= exynos_adc_v1_init_hw,
	.निकास_hw	= exynos_adc_v1_निकास_hw,
	.start_conv	= exynos_adc_s3c64xx_start_conv,
पूर्ण;

अटल काष्ठा exynos_adc_data स्थिर exynos_adc_s3c64xx_data = अणु
	.num_channels	= MAX_ADC_V1_CHANNELS,
	.mask		= ADC_DATX_MASK,	/* 12 bit ADC resolution */

	.init_hw	= exynos_adc_v1_init_hw,
	.निकास_hw	= exynos_adc_v1_निकास_hw,
	.clear_irq	= exynos_adc_v1_clear_irq,
	.start_conv	= exynos_adc_s3c64xx_start_conv,
पूर्ण;

अटल व्योम exynos_adc_v2_init_hw(काष्ठा exynos_adc *info)
अणु
	u32 con1, con2;

	अगर (info->data->needs_adc_phy)
		regmap_ग_लिखो(info->pmu_map, info->data->phy_offset, 1);

	con1 = ADC_V2_CON1_SOFT_RESET;
	ग_लिखोl(con1, ADC_V2_CON1(info->regs));

	con2 = ADC_V2_CON2_OSEL | ADC_V2_CON2_ESEL |
		ADC_V2_CON2_HIGHF | ADC_V2_CON2_C_TIME(0);
	ग_लिखोl(con2, ADC_V2_CON2(info->regs));

	/* Enable पूर्णांकerrupts */
	ग_लिखोl(1, ADC_V2_INT_EN(info->regs));
पूर्ण

अटल व्योम exynos_adc_v2_निकास_hw(काष्ठा exynos_adc *info)
अणु
	u32 con;

	अगर (info->data->needs_adc_phy)
		regmap_ग_लिखो(info->pmu_map, info->data->phy_offset, 0);

	con = पढ़ोl(ADC_V2_CON1(info->regs));
	con &= ~ADC_CON_EN_START;
	ग_लिखोl(con, ADC_V2_CON1(info->regs));
पूर्ण

अटल व्योम exynos_adc_v2_clear_irq(काष्ठा exynos_adc *info)
अणु
	ग_लिखोl(1, ADC_V2_INT_ST(info->regs));
पूर्ण

अटल व्योम exynos_adc_v2_start_conv(काष्ठा exynos_adc *info,
				     अचिन्हित दीर्घ addr)
अणु
	u32 con1, con2;

	con2 = पढ़ोl(ADC_V2_CON2(info->regs));
	con2 &= ~ADC_V2_CON2_ACH_MASK;
	con2 |= ADC_V2_CON2_ACH_SEL(addr);
	ग_लिखोl(con2, ADC_V2_CON2(info->regs));

	con1 = पढ़ोl(ADC_V2_CON1(info->regs));
	ग_लिखोl(con1 | ADC_CON_EN_START, ADC_V2_CON1(info->regs));
पूर्ण

अटल स्थिर काष्ठा exynos_adc_data exynos_adc_v2_data = अणु
	.num_channels	= MAX_ADC_V2_CHANNELS,
	.mask		= ADC_DATX_MASK, /* 12 bit ADC resolution */
	.needs_adc_phy	= true,
	.phy_offset	= EXYNOS_ADCV2_PHY_OFFSET,

	.init_hw	= exynos_adc_v2_init_hw,
	.निकास_hw	= exynos_adc_v2_निकास_hw,
	.clear_irq	= exynos_adc_v2_clear_irq,
	.start_conv	= exynos_adc_v2_start_conv,
पूर्ण;

अटल स्थिर काष्ठा exynos_adc_data exynos3250_adc_data = अणु
	.num_channels	= MAX_EXYNOS3250_ADC_CHANNELS,
	.mask		= ADC_DATX_MASK, /* 12 bit ADC resolution */
	.needs_sclk	= true,
	.needs_adc_phy	= true,
	.phy_offset	= EXYNOS_ADCV1_PHY_OFFSET,

	.init_hw	= exynos_adc_v2_init_hw,
	.निकास_hw	= exynos_adc_v2_निकास_hw,
	.clear_irq	= exynos_adc_v2_clear_irq,
	.start_conv	= exynos_adc_v2_start_conv,
पूर्ण;

अटल व्योम exynos_adc_exynos7_init_hw(काष्ठा exynos_adc *info)
अणु
	u32 con1, con2;

	con1 = ADC_V2_CON1_SOFT_RESET;
	ग_लिखोl(con1, ADC_V2_CON1(info->regs));

	con2 = पढ़ोl(ADC_V2_CON2(info->regs));
	con2 &= ~ADC_V2_CON2_C_TIME(7);
	con2 |= ADC_V2_CON2_C_TIME(0);
	ग_लिखोl(con2, ADC_V2_CON2(info->regs));

	/* Enable पूर्णांकerrupts */
	ग_लिखोl(1, ADC_V2_INT_EN(info->regs));
पूर्ण

अटल स्थिर काष्ठा exynos_adc_data exynos7_adc_data = अणु
	.num_channels	= MAX_ADC_V1_CHANNELS,
	.mask		= ADC_DATX_MASK, /* 12 bit ADC resolution */

	.init_hw	= exynos_adc_exynos7_init_hw,
	.निकास_hw	= exynos_adc_v2_निकास_hw,
	.clear_irq	= exynos_adc_v2_clear_irq,
	.start_conv	= exynos_adc_v2_start_conv,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_adc_match[] = अणु
	अणु
		.compatible = "samsung,s3c2410-adc",
		.data = &exynos_adc_s3c24xx_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c2416-adc",
		.data = &exynos_adc_s3c2416_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c2440-adc",
		.data = &exynos_adc_s3c24xx_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c2443-adc",
		.data = &exynos_adc_s3c2443_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c6410-adc",
		.data = &exynos_adc_s3c64xx_data,
	पूर्ण, अणु
		.compatible = "samsung,s5pv210-adc",
		.data = &exynos_adc_s5pv210_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos4212-adc",
		.data = &exynos4212_adc_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos-adc-v1",
		.data = &exynos_adc_v1_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos-adc-v2",
		.data = &exynos_adc_v2_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos3250-adc",
		.data = &exynos3250_adc_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos7-adc",
		.data = &exynos7_adc_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_adc_match);

अटल काष्ठा exynos_adc_data *exynos_adc_get_data(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;

	match = of_match_node(exynos_adc_match, pdev->dev.of_node);
	वापस (काष्ठा exynos_adc_data *)match->data;
पूर्ण

अटल पूर्णांक exynos_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val,
				पूर्णांक *val2,
				दीर्घ mask)
अणु
	काष्ठा exynos_adc *info = iio_priv(indio_dev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	अगर (mask == IIO_CHAN_INFO_SCALE) अणु
		ret = regulator_get_voltage(info->vdd);
		अगर (ret < 0)
			वापस ret;

		/* Regulator voltage is in uV, but need mV */
		*val = ret / 1000;
		*val2 = info->data->mask;

		वापस IIO_VAL_FRACTIONAL;
	पूर्ण अन्यथा अगर (mask != IIO_CHAN_INFO_RAW) अणु
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&info->lock);
	reinit_completion(&info->completion);

	/* Select the channel to be used and Trigger conversion */
	अगर (info->data->start_conv)
		info->data->start_conv(info, chan->address);

	समयout = रुको_क्रम_completion_समयout(&info->completion,
					      EXYNOS_ADC_TIMEOUT);
	अगर (समयout == 0) अणु
		dev_warn(&indio_dev->dev, "Conversion timed out! Resetting\n");
		अगर (info->data->init_hw)
			info->data->init_hw(info);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		*val = info->value;
		*val2 = 0;
		ret = IIO_VAL_INT;
	पूर्ण

	mutex_unlock(&info->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_पढ़ो_s3c64xx_ts(काष्ठा iio_dev *indio_dev, पूर्णांक *x, पूर्णांक *y)
अणु
	काष्ठा exynos_adc *info = iio_priv(indio_dev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	mutex_lock(&info->lock);
	info->पढ़ो_ts = true;

	reinit_completion(&info->completion);

	ग_लिखोl(ADC_S3C2410_TSC_PULL_UP_DISABLE | ADC_TSC_AUTOPST,
	       ADC_V1_TSC(info->regs));

	/* Select the ts channel to be used and Trigger conversion */
	info->data->start_conv(info, ADC_S3C2410_MUX_TS);

	समयout = रुको_क्रम_completion_समयout(&info->completion,
					      EXYNOS_ADC_TIMEOUT);
	अगर (समयout == 0) अणु
		dev_warn(&indio_dev->dev, "Conversion timed out! Resetting\n");
		अगर (info->data->init_hw)
			info->data->init_hw(info);
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		*x = info->ts_x;
		*y = info->ts_y;
		ret = 0;
	पूर्ण

	info->पढ़ो_ts = false;
	mutex_unlock(&info->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t exynos_adc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा exynos_adc *info = dev_id;
	u32 mask = info->data->mask;

	/* Read value */
	अगर (info->पढ़ो_ts) अणु
		info->ts_x = पढ़ोl(ADC_V1_DATX(info->regs));
		info->ts_y = पढ़ोl(ADC_V1_DATY(info->regs));
		ग_लिखोl(ADC_TSC_WAIT4INT | ADC_S3C2443_TSC_UD_SEN, ADC_V1_TSC(info->regs));
	पूर्ण अन्यथा अणु
		info->value = पढ़ोl(ADC_V1_DATX(info->regs)) & mask;
	पूर्ण

	/* clear irq */
	अगर (info->data->clear_irq)
		info->data->clear_irq(info);

	complete(&info->completion);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Here we (ab)use a thपढ़ोed पूर्णांकerrupt handler to stay running
 * क्रम as दीर्घ as the touchscreen reमुख्यs pressed, we report
 * a new event with the latest data and then sleep until the
 * next समयr tick. This mirrors the behavior of the old
 * driver, with much less code.
 */
अटल irqवापस_t exynos_ts_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा exynos_adc *info = dev_id;
	काष्ठा iio_dev *dev = dev_get_drvdata(info->dev);
	u32 x, y;
	bool pressed;
	पूर्णांक ret;

	जबतक (READ_ONCE(info->ts_enabled)) अणु
		ret = exynos_पढ़ो_s3c64xx_ts(dev, &x, &y);
		अगर (ret == -ETIMEDOUT)
			अवरोध;

		pressed = x & y & ADC_DATX_PRESSED;
		अगर (!pressed) अणु
			input_report_key(info->input, BTN_TOUCH, 0);
			input_sync(info->input);
			अवरोध;
		पूर्ण

		input_report_असल(info->input, ABS_X, x & ADC_DATX_MASK);
		input_report_असल(info->input, ABS_Y, y & ADC_DATY_MASK);
		input_report_key(info->input, BTN_TOUCH, 1);
		input_sync(info->input);

		usleep_range(1000, 1100);
	पूर्ण

	ग_लिखोl(0, ADC_V1_CLRINTPNDNUP(info->regs));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक exynos_adc_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित reg, अचिन्हित ग_लिखोval,
			      अचिन्हित *पढ़ोval)
अणु
	काष्ठा exynos_adc *info = iio_priv(indio_dev);

	अगर (पढ़ोval == शून्य)
		वापस -EINVAL;

	*पढ़ोval = पढ़ोl(info->regs + reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info exynos_adc_iio_info = अणु
	.पढ़ो_raw = &exynos_पढ़ो_raw,
	.debugfs_reg_access = &exynos_adc_reg_access,
पूर्ण;

#घोषणा ADC_CHANNEL(_index, _id) अणु			\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = _index,				\
	.address = _index,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SCALE),	\
	.datasheet_name = _id,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec exynos_adc_iio_channels[] = अणु
	ADC_CHANNEL(0, "adc0"),
	ADC_CHANNEL(1, "adc1"),
	ADC_CHANNEL(2, "adc2"),
	ADC_CHANNEL(3, "adc3"),
	ADC_CHANNEL(4, "adc4"),
	ADC_CHANNEL(5, "adc5"),
	ADC_CHANNEL(6, "adc6"),
	ADC_CHANNEL(7, "adc7"),
	ADC_CHANNEL(8, "adc8"),
	ADC_CHANNEL(9, "adc9"),
पूर्ण;

अटल पूर्णांक exynos_adc_हटाओ_devices(काष्ठा device *dev, व्योम *c)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_adc_ts_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा exynos_adc *info = input_get_drvdata(dev);

	WRITE_ONCE(info->ts_enabled, true);
	enable_irq(info->tsirq);

	वापस 0;
पूर्ण

अटल व्योम exynos_adc_ts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा exynos_adc *info = input_get_drvdata(dev);

	WRITE_ONCE(info->ts_enabled, false);
	disable_irq(info->tsirq);
पूर्ण

अटल पूर्णांक exynos_adc_ts_init(काष्ठा exynos_adc *info)
अणु
	पूर्णांक ret;

	अगर (info->tsirq <= 0)
		वापस -ENODEV;

	info->input = input_allocate_device();
	अगर (!info->input)
		वापस -ENOMEM;

	info->input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	info->input->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_असल_params(info->input, ABS_X, 0, 0x3FF, 0, 0);
	input_set_असल_params(info->input, ABS_Y, 0, 0x3FF, 0, 0);

	info->input->name = "S3C24xx TouchScreen";
	info->input->id.bustype = BUS_HOST;
	info->input->खोलो = exynos_adc_ts_खोलो;
	info->input->बंद = exynos_adc_ts_बंद;

	input_set_drvdata(info->input, info);

	ret = input_रेजिस्टर_device(info->input);
	अगर (ret) अणु
		input_मुक्त_device(info->input);
		वापस ret;
	पूर्ण

	ret = request_thपढ़ोed_irq(info->tsirq, शून्य, exynos_ts_isr,
				   IRQF_ONESHOT | IRQF_NO_AUTOEN,
				   "touchscreen", info);
	अगर (ret)
		input_unरेजिस्टर_device(info->input);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_adc *info = शून्य;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा s3c2410_ts_mach_info *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा iio_dev *indio_dev = शून्य;
	bool has_ts = false;
	पूर्णांक ret = -ENODEV;
	पूर्णांक irq;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(काष्ठा exynos_adc));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	info = iio_priv(indio_dev);

	info->data = exynos_adc_get_data(pdev);
	अगर (!info->data) अणु
		dev_err(&pdev->dev, "failed getting exynos_adc_data\n");
		वापस -EINVAL;
	पूर्ण

	info->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);


	अगर (info->data->needs_adc_phy) अणु
		info->pmu_map = syscon_regmap_lookup_by_phandle(
					pdev->dev.of_node,
					"samsung,syscon-phandle");
		अगर (IS_ERR(info->pmu_map)) अणु
			dev_err(&pdev->dev, "syscon regmap lookup failed.\n");
			वापस PTR_ERR(info->pmu_map);
		पूर्ण
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	info->irq = irq;

	irq = platक्रमm_get_irq(pdev, 1);
	अगर (irq == -EPROBE_DEFER)
		वापस irq;

	info->tsirq = irq;

	info->dev = &pdev->dev;

	init_completion(&info->completion);

	info->clk = devm_clk_get(&pdev->dev, "adc");
	अगर (IS_ERR(info->clk)) अणु
		dev_err(&pdev->dev, "failed getting clock, err = %ld\n",
							PTR_ERR(info->clk));
		वापस PTR_ERR(info->clk);
	पूर्ण

	अगर (info->data->needs_sclk) अणु
		info->sclk = devm_clk_get(&pdev->dev, "sclk");
		अगर (IS_ERR(info->sclk)) अणु
			dev_err(&pdev->dev,
				"failed getting sclk clock, err = %ld\n",
				PTR_ERR(info->sclk));
			वापस PTR_ERR(info->sclk);
		पूर्ण
	पूर्ण

	info->vdd = devm_regulator_get(&pdev->dev, "vdd");
	अगर (IS_ERR(info->vdd))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(info->vdd),
				     "failed getting regulator");

	ret = regulator_enable(info->vdd);
	अगर (ret)
		वापस ret;

	ret = exynos_adc_prepare_clk(info);
	अगर (ret)
		जाओ err_disable_reg;

	ret = exynos_adc_enable_clk(info);
	अगर (ret)
		जाओ err_unprepare_clk;

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &exynos_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = exynos_adc_iio_channels;
	indio_dev->num_channels = info->data->num_channels;

	mutex_init(&info->lock);

	ret = request_irq(info->irq, exynos_adc_isr,
					0, dev_name(&pdev->dev), info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed requesting irq, irq = %d\n",
							info->irq);
		जाओ err_disable_clk;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_irq;

	अगर (info->data->init_hw)
		info->data->init_hw(info);

	/* leave out any TS related code अगर unreachable */
	अगर (IS_REACHABLE(CONFIG_INPUT)) अणु
		has_ts = of_property_पढ़ो_bool(pdev->dev.of_node,
					       "has-touchscreen") || pdata;
	पूर्ण

	अगर (pdata)
		info->delay = pdata->delay;
	अन्यथा
		info->delay = 10000;

	अगर (has_ts)
		ret = exynos_adc_ts_init(info);
	अगर (ret)
		जाओ err_iio;

	ret = of_platक्रमm_populate(np, exynos_adc_match, शून्य, &indio_dev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed adding child nodes\n");
		जाओ err_of_populate;
	पूर्ण

	वापस 0;

err_of_populate:
	device_क्रम_each_child(&indio_dev->dev, शून्य,
				exynos_adc_हटाओ_devices);
	अगर (has_ts) अणु
		input_unरेजिस्टर_device(info->input);
		मुक्त_irq(info->tsirq, info);
	पूर्ण
err_iio:
	iio_device_unरेजिस्टर(indio_dev);
err_irq:
	मुक्त_irq(info->irq, info);
err_disable_clk:
	अगर (info->data->निकास_hw)
		info->data->निकास_hw(info);
	exynos_adc_disable_clk(info);
err_unprepare_clk:
	exynos_adc_unprepare_clk(info);
err_disable_reg:
	regulator_disable(info->vdd);
	वापस ret;
पूर्ण

अटल पूर्णांक exynos_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा exynos_adc *info = iio_priv(indio_dev);

	अगर (IS_REACHABLE(CONFIG_INPUT) && info->input) अणु
		मुक्त_irq(info->tsirq, info);
		input_unरेजिस्टर_device(info->input);
	पूर्ण
	device_क्रम_each_child(&indio_dev->dev, शून्य,
				exynos_adc_हटाओ_devices);
	iio_device_unरेजिस्टर(indio_dev);
	मुक्त_irq(info->irq, info);
	अगर (info->data->निकास_hw)
		info->data->निकास_hw(info);
	exynos_adc_disable_clk(info);
	exynos_adc_unprepare_clk(info);
	regulator_disable(info->vdd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक exynos_adc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा exynos_adc *info = iio_priv(indio_dev);

	अगर (info->data->निकास_hw)
		info->data->निकास_hw(info);
	exynos_adc_disable_clk(info);
	regulator_disable(info->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा exynos_adc *info = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(info->vdd);
	अगर (ret)
		वापस ret;

	ret = exynos_adc_enable_clk(info);
	अगर (ret)
		वापस ret;

	अगर (info->data->init_hw)
		info->data->init_hw(info);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(exynos_adc_pm_ops,
			exynos_adc_suspend,
			exynos_adc_resume);

अटल काष्ठा platक्रमm_driver exynos_adc_driver = अणु
	.probe		= exynos_adc_probe,
	.हटाओ		= exynos_adc_हटाओ,
	.driver		= अणु
		.name	= "exynos-adc",
		.of_match_table = exynos_adc_match,
		.pm	= &exynos_adc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(exynos_adc_driver);

MODULE_AUTHOR("Naveen Krishna Chatradhi <ch.naveen@samsung.com>");
MODULE_DESCRIPTION("Samsung EXYNOS5 ADC driver");
MODULE_LICENSE("GPL v2");
