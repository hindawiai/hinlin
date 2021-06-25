<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * An RTC driver क्रम Allwinner A31/A23
 *
 * Copyright (c) 2014, Chen-Yu Tsai <wens@csie.org>
 *
 * based on rtc-sunxi.c
 *
 * An RTC driver क्रम Allwinner A10/A20
 *
 * Copyright (c) 2013, Carlo Caione <carlo.caione@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/* Control रेजिस्टर */
#घोषणा SUN6I_LOSC_CTRL				0x0000
#घोषणा SUN6I_LOSC_CTRL_KEY			(0x16aa << 16)
#घोषणा SUN6I_LOSC_CTRL_AUTO_SWT_BYPASS		BIT(15)
#घोषणा SUN6I_LOSC_CTRL_ALM_DHMS_ACC		BIT(9)
#घोषणा SUN6I_LOSC_CTRL_RTC_HMS_ACC		BIT(8)
#घोषणा SUN6I_LOSC_CTRL_RTC_YMD_ACC		BIT(7)
#घोषणा SUN6I_LOSC_CTRL_EXT_LOSC_EN		BIT(4)
#घोषणा SUN6I_LOSC_CTRL_EXT_OSC			BIT(0)
#घोषणा SUN6I_LOSC_CTRL_ACC_MASK		GENMASK(9, 7)

#घोषणा SUN6I_LOSC_CLK_PRESCAL			0x0008

/* RTC */
#घोषणा SUN6I_RTC_YMD				0x0010
#घोषणा SUN6I_RTC_HMS				0x0014

/* Alarm 0 (counter) */
#घोषणा SUN6I_ALRM_COUNTER			0x0020
#घोषणा SUN6I_ALRM_CUR_VAL			0x0024
#घोषणा SUN6I_ALRM_EN				0x0028
#घोषणा SUN6I_ALRM_EN_CNT_EN			BIT(0)
#घोषणा SUN6I_ALRM_IRQ_EN			0x002c
#घोषणा SUN6I_ALRM_IRQ_EN_CNT_IRQ_EN		BIT(0)
#घोषणा SUN6I_ALRM_IRQ_STA			0x0030
#घोषणा SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND		BIT(0)

/* Alarm 1 (wall घड़ी) */
#घोषणा SUN6I_ALRM1_EN				0x0044
#घोषणा SUN6I_ALRM1_IRQ_EN			0x0048
#घोषणा SUN6I_ALRM1_IRQ_STA			0x004c
#घोषणा SUN6I_ALRM1_IRQ_STA_WEEK_IRQ_PEND	BIT(0)

/* Alarm config */
#घोषणा SUN6I_ALARM_CONFIG			0x0050
#घोषणा SUN6I_ALARM_CONFIG_WAKEUP		BIT(0)

#घोषणा SUN6I_LOSC_OUT_GATING			0x0060
#घोषणा SUN6I_LOSC_OUT_GATING_EN_OFFSET		0

/*
 * Get date values
 */
#घोषणा SUN6I_DATE_GET_DAY_VALUE(x)		((x)  & 0x0000001f)
#घोषणा SUN6I_DATE_GET_MON_VALUE(x)		(((x) & 0x00000f00) >> 8)
#घोषणा SUN6I_DATE_GET_YEAR_VALUE(x)		(((x) & 0x003f0000) >> 16)
#घोषणा SUN6I_LEAP_GET_VALUE(x)			(((x) & 0x00400000) >> 22)

/*
 * Get समय values
 */
#घोषणा SUN6I_TIME_GET_SEC_VALUE(x)		((x)  & 0x0000003f)
#घोषणा SUN6I_TIME_GET_MIN_VALUE(x)		(((x) & 0x00003f00) >> 8)
#घोषणा SUN6I_TIME_GET_HOUR_VALUE(x)		(((x) & 0x001f0000) >> 16)

/*
 * Set date values
 */
#घोषणा SUN6I_DATE_SET_DAY_VALUE(x)		((x)       & 0x0000001f)
#घोषणा SUN6I_DATE_SET_MON_VALUE(x)		((x) <<  8 & 0x00000f00)
#घोषणा SUN6I_DATE_SET_YEAR_VALUE(x)		((x) << 16 & 0x003f0000)
#घोषणा SUN6I_LEAP_SET_VALUE(x)			((x) << 22 & 0x00400000)

/*
 * Set समय values
 */
#घोषणा SUN6I_TIME_SET_SEC_VALUE(x)		((x)       & 0x0000003f)
#घोषणा SUN6I_TIME_SET_MIN_VALUE(x)		((x) <<  8 & 0x00003f00)
#घोषणा SUN6I_TIME_SET_HOUR_VALUE(x)		((x) << 16 & 0x001f0000)

/*
 * The year parameter passed to the driver is usually an offset relative to
 * the year 1900. This macro is used to convert this offset to another one
 * relative to the minimum year allowed by the hardware.
 *
 * The year range is 1970 - 2033. This range is selected to match Allwinner's
 * driver, even though it is somewhat limited.
 */
#घोषणा SUN6I_YEAR_MIN				1970
#घोषणा SUN6I_YEAR_OFF				(SUN6I_YEAR_MIN - 1900)

/*
 * There are other dअगरferences between models, including:
 *
 *   - number of GPIO pins that can be configured to hold a certain level
 *   - crypto-key related रेजिस्टरs (H5, H6)
 *   - boot process related (super standby, secondary processor entry address)
 *     रेजिस्टरs (R40, H6)
 *   - SYS घातer करोमुख्य controls (R40)
 *   - DCXO controls (H6)
 *   - RC oscillator calibration (H6)
 *
 * These functions are not covered by this driver.
 */
काष्ठा sun6i_rtc_clk_data अणु
	अचिन्हित दीर्घ rc_osc_rate;
	अचिन्हित पूर्णांक fixed_prescaler : 16;
	अचिन्हित पूर्णांक has_prescaler : 1;
	अचिन्हित पूर्णांक has_out_clk : 1;
	अचिन्हित पूर्णांक export_iosc : 1;
	अचिन्हित पूर्णांक has_losc_en : 1;
	अचिन्हित पूर्णांक has_स्वतः_swt : 1;
पूर्ण;

काष्ठा sun6i_rtc_dev अणु
	काष्ठा rtc_device *rtc;
	स्थिर काष्ठा sun6i_rtc_clk_data *data;
	व्योम __iomem *base;
	पूर्णांक irq;
	अचिन्हित दीर्घ alarm;

	काष्ठा clk_hw hw;
	काष्ठा clk_hw *पूर्णांक_osc;
	काष्ठा clk *losc;
	काष्ठा clk *ext_losc;

	spinlock_t lock;
पूर्ण;

अटल काष्ठा sun6i_rtc_dev *sun6i_rtc;

अटल अचिन्हित दीर्घ sun6i_rtc_osc_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sun6i_rtc_dev *rtc = container_of(hw, काष्ठा sun6i_rtc_dev, hw);
	u32 val = 0;

	val = पढ़ोl(rtc->base + SUN6I_LOSC_CTRL);
	अगर (val & SUN6I_LOSC_CTRL_EXT_OSC)
		वापस parent_rate;

	अगर (rtc->data->fixed_prescaler)
		parent_rate /= rtc->data->fixed_prescaler;

	अगर (rtc->data->has_prescaler) अणु
		val = पढ़ोl(rtc->base + SUN6I_LOSC_CLK_PRESCAL);
		val &= GENMASK(4, 0);
	पूर्ण

	वापस parent_rate / (val + 1);
पूर्ण

अटल u8 sun6i_rtc_osc_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा sun6i_rtc_dev *rtc = container_of(hw, काष्ठा sun6i_rtc_dev, hw);

	वापस पढ़ोl(rtc->base + SUN6I_LOSC_CTRL) & SUN6I_LOSC_CTRL_EXT_OSC;
पूर्ण

अटल पूर्णांक sun6i_rtc_osc_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा sun6i_rtc_dev *rtc = container_of(hw, काष्ठा sun6i_rtc_dev, hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (index > 1)
		वापस -EINVAL;

	spin_lock_irqsave(&rtc->lock, flags);
	val = पढ़ोl(rtc->base + SUN6I_LOSC_CTRL);
	val &= ~SUN6I_LOSC_CTRL_EXT_OSC;
	val |= SUN6I_LOSC_CTRL_KEY;
	val |= index ? SUN6I_LOSC_CTRL_EXT_OSC : 0;
	अगर (rtc->data->has_losc_en) अणु
		val &= ~SUN6I_LOSC_CTRL_EXT_LOSC_EN;
		val |= index ? SUN6I_LOSC_CTRL_EXT_LOSC_EN : 0;
	पूर्ण
	ग_लिखोl(val, rtc->base + SUN6I_LOSC_CTRL);
	spin_unlock_irqrestore(&rtc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops sun6i_rtc_osc_ops = अणु
	.recalc_rate	= sun6i_rtc_osc_recalc_rate,

	.get_parent	= sun6i_rtc_osc_get_parent,
	.set_parent	= sun6i_rtc_osc_set_parent,
पूर्ण;

अटल व्योम __init sun6i_rtc_clk_init(काष्ठा device_node *node,
				      स्थिर काष्ठा sun6i_rtc_clk_data *data)
अणु
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा sun6i_rtc_dev *rtc;
	काष्ठा clk_init_data init = अणु
		.ops		= &sun6i_rtc_osc_ops,
		.name		= "losc",
	पूर्ण;
	स्थिर अक्षर *iosc_name = "rtc-int-osc";
	स्थिर अक्षर *clkout_name = "osc32k-out";
	स्थिर अक्षर *parents[2];
	u32 reg;

	rtc = kzalloc(माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस;

	rtc->data = data;
	clk_data = kzalloc(काष्ठा_size(clk_data, hws, 3), GFP_KERNEL);
	अगर (!clk_data) अणु
		kमुक्त(rtc);
		वापस;
	पूर्ण

	spin_lock_init(&rtc->lock);

	rtc->base = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(rtc->base)) अणु
		pr_crit("Can't map RTC registers");
		जाओ err;
	पूर्ण

	reg = SUN6I_LOSC_CTRL_KEY;
	अगर (rtc->data->has_स्वतः_swt) अणु
		/* Bypass स्वतः-चयन to पूर्णांक osc, on ext losc failure */
		reg |= SUN6I_LOSC_CTRL_AUTO_SWT_BYPASS;
		ग_लिखोl(reg, rtc->base + SUN6I_LOSC_CTRL);
	पूर्ण

	/* Switch to the बाह्यal, more precise, oscillator, अगर present */
	अगर (of_get_property(node, "clocks", शून्य)) अणु
		reg |= SUN6I_LOSC_CTRL_EXT_OSC;
		अगर (rtc->data->has_losc_en)
			reg |= SUN6I_LOSC_CTRL_EXT_LOSC_EN;
	पूर्ण
	ग_लिखोl(reg, rtc->base + SUN6I_LOSC_CTRL);

	/* Yes, I know, this is ugly. */
	sun6i_rtc = rtc;

	/* Only पढ़ो IOSC name from device tree अगर it is exported */
	अगर (rtc->data->export_iosc)
		of_property_पढ़ो_string_index(node, "clock-output-names", 2,
					      &iosc_name);

	rtc->पूर्णांक_osc = clk_hw_रेजिस्टर_fixed_rate_with_accuracy(शून्य,
								iosc_name,
								शून्य, 0,
								rtc->data->rc_osc_rate,
								300000000);
	अगर (IS_ERR(rtc->पूर्णांक_osc)) अणु
		pr_crit("Couldn't register the internal oscillator\n");
		जाओ err;
	पूर्ण

	parents[0] = clk_hw_get_name(rtc->पूर्णांक_osc);
	/* If there is no बाह्यal oscillator, this will be शून्य and ... */
	parents[1] = of_clk_get_parent_name(node, 0);

	rtc->hw.init = &init;

	init.parent_names = parents;
	/* ... number of घड़ी parents will be 1. */
	init.num_parents = of_clk_get_parent_count(node) + 1;
	of_property_पढ़ो_string_index(node, "clock-output-names", 0,
				      &init.name);

	rtc->losc = clk_रेजिस्टर(शून्य, &rtc->hw);
	अगर (IS_ERR(rtc->losc)) अणु
		pr_crit("Couldn't register the LOSC clock\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	of_property_पढ़ो_string_index(node, "clock-output-names", 1,
				      &clkout_name);
	rtc->ext_losc = clk_रेजिस्टर_gate(शून्य, clkout_name, init.name,
					  0, rtc->base + SUN6I_LOSC_OUT_GATING,
					  SUN6I_LOSC_OUT_GATING_EN_OFFSET, 0,
					  &rtc->lock);
	अगर (IS_ERR(rtc->ext_losc)) अणु
		pr_crit("Couldn't register the LOSC external gate\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	clk_data->num = 2;
	clk_data->hws[0] = &rtc->hw;
	clk_data->hws[1] = __clk_get_hw(rtc->ext_losc);
	अगर (rtc->data->export_iosc) अणु
		clk_data->hws[2] = rtc->पूर्णांक_osc;
		clk_data->num = 3;
	पूर्ण
	of_clk_add_hw_provider(node, of_clk_hw_onecell_get, clk_data);
	वापस;

err_रेजिस्टर:
	clk_hw_unरेजिस्टर_fixed_rate(rtc->पूर्णांक_osc);
err:
	kमुक्त(clk_data);
पूर्ण

अटल स्थिर काष्ठा sun6i_rtc_clk_data sun6i_a31_rtc_data = अणु
	.rc_osc_rate = 667000, /* datasheet says 600 ~ 700 KHz */
	.has_prescaler = 1,
पूर्ण;

अटल व्योम __init sun6i_a31_rtc_clk_init(काष्ठा device_node *node)
अणु
	sun6i_rtc_clk_init(node, &sun6i_a31_rtc_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(sun6i_a31_rtc_clk, "allwinner,sun6i-a31-rtc",
		      sun6i_a31_rtc_clk_init);

अटल स्थिर काष्ठा sun6i_rtc_clk_data sun8i_a23_rtc_data = अणु
	.rc_osc_rate = 667000, /* datasheet says 600 ~ 700 KHz */
	.has_prescaler = 1,
	.has_out_clk = 1,
पूर्ण;

अटल व्योम __init sun8i_a23_rtc_clk_init(काष्ठा device_node *node)
अणु
	sun6i_rtc_clk_init(node, &sun8i_a23_rtc_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(sun8i_a23_rtc_clk, "allwinner,sun8i-a23-rtc",
		      sun8i_a23_rtc_clk_init);

अटल स्थिर काष्ठा sun6i_rtc_clk_data sun8i_h3_rtc_data = अणु
	.rc_osc_rate = 16000000,
	.fixed_prescaler = 32,
	.has_prescaler = 1,
	.has_out_clk = 1,
	.export_iosc = 1,
पूर्ण;

अटल व्योम __init sun8i_h3_rtc_clk_init(काष्ठा device_node *node)
अणु
	sun6i_rtc_clk_init(node, &sun8i_h3_rtc_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(sun8i_h3_rtc_clk, "allwinner,sun8i-h3-rtc",
		      sun8i_h3_rtc_clk_init);
/* As far as we are concerned, घड़ीs क्रम H5 are the same as H3 */
CLK_OF_DECLARE_DRIVER(sun50i_h5_rtc_clk, "allwinner,sun50i-h5-rtc",
		      sun8i_h3_rtc_clk_init);

अटल स्थिर काष्ठा sun6i_rtc_clk_data sun50i_h6_rtc_data = अणु
	.rc_osc_rate = 16000000,
	.fixed_prescaler = 32,
	.has_prescaler = 1,
	.has_out_clk = 1,
	.export_iosc = 1,
	.has_losc_en = 1,
	.has_स्वतः_swt = 1,
पूर्ण;

अटल व्योम __init sun50i_h6_rtc_clk_init(काष्ठा device_node *node)
अणु
	sun6i_rtc_clk_init(node, &sun50i_h6_rtc_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(sun50i_h6_rtc_clk, "allwinner,sun50i-h6-rtc",
		      sun50i_h6_rtc_clk_init);

/*
 * The R40 user manual is self-conflicting on whether the prescaler is
 * fixed or configurable. The घड़ी diagram shows it as fixed, but there
 * is also a configurable भागider in the RTC block.
 */
अटल स्थिर काष्ठा sun6i_rtc_clk_data sun8i_r40_rtc_data = अणु
	.rc_osc_rate = 16000000,
	.fixed_prescaler = 512,
पूर्ण;
अटल व्योम __init sun8i_r40_rtc_clk_init(काष्ठा device_node *node)
अणु
	sun6i_rtc_clk_init(node, &sun8i_r40_rtc_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(sun8i_r40_rtc_clk, "allwinner,sun8i-r40-rtc",
		      sun8i_r40_rtc_clk_init);

अटल स्थिर काष्ठा sun6i_rtc_clk_data sun8i_v3_rtc_data = अणु
	.rc_osc_rate = 32000,
	.has_out_clk = 1,
पूर्ण;

अटल व्योम __init sun8i_v3_rtc_clk_init(काष्ठा device_node *node)
अणु
	sun6i_rtc_clk_init(node, &sun8i_v3_rtc_data);
पूर्ण
CLK_OF_DECLARE_DRIVER(sun8i_v3_rtc_clk, "allwinner,sun8i-v3-rtc",
		      sun8i_v3_rtc_clk_init);

अटल irqवापस_t sun6i_rtc_alarmirq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा sun6i_rtc_dev *chip = (काष्ठा sun6i_rtc_dev *) id;
	irqवापस_t ret = IRQ_NONE;
	u32 val;

	spin_lock(&chip->lock);
	val = पढ़ोl(chip->base + SUN6I_ALRM_IRQ_STA);

	अगर (val & SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND) अणु
		val |= SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND;
		ग_लिखोl(val, chip->base + SUN6I_ALRM_IRQ_STA);

		rtc_update_irq(chip->rtc, 1, RTC_AF | RTC_IRQF);

		ret = IRQ_HANDLED;
	पूर्ण
	spin_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल व्योम sun6i_rtc_setaie(पूर्णांक to, काष्ठा sun6i_rtc_dev *chip)
अणु
	u32 alrm_val = 0;
	u32 alrm_irq_val = 0;
	u32 alrm_wake_val = 0;
	अचिन्हित दीर्घ flags;

	अगर (to) अणु
		alrm_val = SUN6I_ALRM_EN_CNT_EN;
		alrm_irq_val = SUN6I_ALRM_IRQ_EN_CNT_IRQ_EN;
		alrm_wake_val = SUN6I_ALARM_CONFIG_WAKEUP;
	पूर्ण अन्यथा अणु
		ग_लिखोl(SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND,
		       chip->base + SUN6I_ALRM_IRQ_STA);
	पूर्ण

	spin_lock_irqsave(&chip->lock, flags);
	ग_लिखोl(alrm_val, chip->base + SUN6I_ALRM_EN);
	ग_लिखोl(alrm_irq_val, chip->base + SUN6I_ALRM_IRQ_EN);
	ग_लिखोl(alrm_wake_val, chip->base + SUN6I_ALARM_CONFIG);
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

अटल पूर्णांक sun6i_rtc_समय_लो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा sun6i_rtc_dev *chip = dev_get_drvdata(dev);
	u32 date, समय;

	/*
	 * पढ़ो again in हाल it changes
	 */
	करो अणु
		date = पढ़ोl(chip->base + SUN6I_RTC_YMD);
		समय = पढ़ोl(chip->base + SUN6I_RTC_HMS);
	पूर्ण जबतक ((date != पढ़ोl(chip->base + SUN6I_RTC_YMD)) ||
		 (समय != पढ़ोl(chip->base + SUN6I_RTC_HMS)));

	rtc_पंचांग->पंचांग_sec  = SUN6I_TIME_GET_SEC_VALUE(समय);
	rtc_पंचांग->पंचांग_min  = SUN6I_TIME_GET_MIN_VALUE(समय);
	rtc_पंचांग->पंचांग_hour = SUN6I_TIME_GET_HOUR_VALUE(समय);

	rtc_पंचांग->पंचांग_mday = SUN6I_DATE_GET_DAY_VALUE(date);
	rtc_पंचांग->पंचांग_mon  = SUN6I_DATE_GET_MON_VALUE(date);
	rtc_पंचांग->पंचांग_year = SUN6I_DATE_GET_YEAR_VALUE(date);

	rtc_पंचांग->पंचांग_mon  -= 1;

	/*
	 * चयन from (data_year->min)-relative offset to
	 * a (1900)-relative one
	 */
	rtc_पंचांग->पंचांग_year += SUN6I_YEAR_OFF;

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_rtc_getalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा sun6i_rtc_dev *chip = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;
	u32 alrm_st;
	u32 alrm_en;

	spin_lock_irqsave(&chip->lock, flags);
	alrm_en = पढ़ोl(chip->base + SUN6I_ALRM_IRQ_EN);
	alrm_st = पढ़ोl(chip->base + SUN6I_ALRM_IRQ_STA);
	spin_unlock_irqrestore(&chip->lock, flags);

	wkalrm->enabled = !!(alrm_en & SUN6I_ALRM_EN_CNT_EN);
	wkalrm->pending = !!(alrm_st & SUN6I_ALRM_EN_CNT_EN);
	rtc_समय64_to_पंचांग(chip->alarm, &wkalrm->समय);

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा sun6i_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alrm_पंचांग = &wkalrm->समय;
	काष्ठा rtc_समय पंचांग_now;
	अचिन्हित दीर्घ समय_now = 0;
	अचिन्हित दीर्घ समय_set = 0;
	अचिन्हित दीर्घ समय_gap = 0;
	पूर्णांक ret = 0;

	ret = sun6i_rtc_समय_लो(dev, &पंचांग_now);
	अगर (ret < 0) अणु
		dev_err(dev, "Error in getting time\n");
		वापस -EINVAL;
	पूर्ण

	समय_set = rtc_पंचांग_to_समय64(alrm_पंचांग);
	समय_now = rtc_पंचांग_to_समय64(&पंचांग_now);
	अगर (समय_set <= समय_now) अणु
		dev_err(dev, "Date to set in the past\n");
		वापस -EINVAL;
	पूर्ण

	समय_gap = समय_set - समय_now;

	अगर (समय_gap > U32_MAX) अणु
		dev_err(dev, "Date too far in the future\n");
		वापस -EINVAL;
	पूर्ण

	sun6i_rtc_setaie(0, chip);
	ग_लिखोl(0, chip->base + SUN6I_ALRM_COUNTER);
	usleep_range(100, 300);

	ग_लिखोl(समय_gap, chip->base + SUN6I_ALRM_COUNTER);
	chip->alarm = समय_set;

	sun6i_rtc_setaie(wkalrm->enabled, chip);

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_rtc_रुको(काष्ठा sun6i_rtc_dev *chip, पूर्णांक offset,
			  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक ms_समयout)
अणु
	स्थिर अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(ms_समयout);
	u32 reg;

	करो अणु
		reg = पढ़ोl(chip->base + offset);
		reg &= mask;

		अगर (!reg)
			वापस 0;

	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sun6i_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा sun6i_rtc_dev *chip = dev_get_drvdata(dev);
	u32 date = 0;
	u32 समय = 0;

	rtc_पंचांग->पंचांग_year -= SUN6I_YEAR_OFF;
	rtc_पंचांग->पंचांग_mon += 1;

	date = SUN6I_DATE_SET_DAY_VALUE(rtc_पंचांग->पंचांग_mday) |
		SUN6I_DATE_SET_MON_VALUE(rtc_पंचांग->पंचांग_mon)  |
		SUN6I_DATE_SET_YEAR_VALUE(rtc_पंचांग->पंचांग_year);

	अगर (is_leap_year(rtc_पंचांग->पंचांग_year + SUN6I_YEAR_MIN))
		date |= SUN6I_LEAP_SET_VALUE(1);

	समय = SUN6I_TIME_SET_SEC_VALUE(rtc_पंचांग->पंचांग_sec)  |
		SUN6I_TIME_SET_MIN_VALUE(rtc_पंचांग->पंचांग_min)  |
		SUN6I_TIME_SET_HOUR_VALUE(rtc_पंचांग->पंचांग_hour);

	/* Check whether रेजिस्टरs are writable */
	अगर (sun6i_rtc_रुको(chip, SUN6I_LOSC_CTRL,
			   SUN6I_LOSC_CTRL_ACC_MASK, 50)) अणु
		dev_err(dev, "rtc is still busy.\n");
		वापस -EBUSY;
	पूर्ण

	ग_लिखोl(समय, chip->base + SUN6I_RTC_HMS);

	/*
	 * After writing the RTC HH-MM-SS रेजिस्टर, the
	 * SUN6I_LOSC_CTRL_RTC_HMS_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	अगर (sun6i_rtc_रुको(chip, SUN6I_LOSC_CTRL,
			   SUN6I_LOSC_CTRL_RTC_HMS_ACC, 50)) अणु
		dev_err(dev, "Failed to set rtc time.\n");
		वापस -ETIMEDOUT;
	पूर्ण

	ग_लिखोl(date, chip->base + SUN6I_RTC_YMD);

	/*
	 * After writing the RTC YY-MM-DD रेजिस्टर, the
	 * SUN6I_LOSC_CTRL_RTC_YMD_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	अगर (sun6i_rtc_रुको(chip, SUN6I_LOSC_CTRL,
			   SUN6I_LOSC_CTRL_RTC_YMD_ACC, 50)) अणु
		dev_err(dev, "Failed to set rtc time.\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा sun6i_rtc_dev *chip = dev_get_drvdata(dev);

	अगर (!enabled)
		sun6i_rtc_setaie(enabled, chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sun6i_rtc_ops = अणु
	.पढ़ो_समय		= sun6i_rtc_समय_लो,
	.set_समय		= sun6i_rtc_समय_रखो,
	.पढ़ो_alarm		= sun6i_rtc_getalarm,
	.set_alarm		= sun6i_rtc_setalarm,
	.alarm_irq_enable	= sun6i_rtc_alarm_irq_enable
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
/* Enable IRQ wake on suspend, to wake up from RTC. */
अटल पूर्णांक sun6i_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun6i_rtc_dev *chip = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(chip->irq);

	वापस 0;
पूर्ण

/* Disable IRQ wake on resume. */
अटल पूर्णांक sun6i_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा sun6i_rtc_dev *chip = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(chip->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sun6i_rtc_pm_ops,
	sun6i_rtc_suspend, sun6i_rtc_resume);

अटल पूर्णांक sun6i_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun6i_rtc_dev *chip = sun6i_rtc;
	पूर्णांक ret;

	अगर (!chip)
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, chip);

	chip->irq = platक्रमm_get_irq(pdev, 0);
	अगर (chip->irq < 0)
		वापस chip->irq;

	ret = devm_request_irq(&pdev->dev, chip->irq, sun6i_rtc_alarmirq,
			       0, dev_name(&pdev->dev), chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not request IRQ\n");
		वापस ret;
	पूर्ण

	/* clear the alarm counter value */
	ग_लिखोl(0, chip->base + SUN6I_ALRM_COUNTER);

	/* disable counter alarm */
	ग_लिखोl(0, chip->base + SUN6I_ALRM_EN);

	/* disable counter alarm पूर्णांकerrupt */
	ग_लिखोl(0, chip->base + SUN6I_ALRM_IRQ_EN);

	/* disable week alarm */
	ग_लिखोl(0, chip->base + SUN6I_ALRM1_EN);

	/* disable week alarm पूर्णांकerrupt */
	ग_लिखोl(0, chip->base + SUN6I_ALRM1_IRQ_EN);

	/* clear counter alarm pending पूर्णांकerrupts */
	ग_लिखोl(SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND,
	       chip->base + SUN6I_ALRM_IRQ_STA);

	/* clear week alarm pending पूर्णांकerrupts */
	ग_लिखोl(SUN6I_ALRM1_IRQ_STA_WEEK_IRQ_PEND,
	       chip->base + SUN6I_ALRM1_IRQ_STA);

	/* disable alarm wakeup */
	ग_लिखोl(0, chip->base + SUN6I_ALARM_CONFIG);

	clk_prepare_enable(chip->losc);

	device_init_wakeup(&pdev->dev, 1);

	chip->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(chip->rtc))
		वापस PTR_ERR(chip->rtc);

	chip->rtc->ops = &sun6i_rtc_ops;
	chip->rtc->range_max = 2019686399LL; /* 2033-12-31 23:59:59 */

	ret = devm_rtc_रेजिस्टर_device(chip->rtc);
	अगर (ret)
		वापस ret;

	dev_info(&pdev->dev, "RTC enabled\n");

	वापस 0;
पूर्ण

/*
 * As far as RTC functionality goes, all models are the same. The
 * datasheets claim that dअगरferent models have dअगरferent number of
 * रेजिस्टरs available क्रम non-अस्थिर storage, but experiments show
 * that all SoCs have 16 रेजिस्टरs available क्रम this purpose.
 */
अटल स्थिर काष्ठा of_device_id sun6i_rtc_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-rtc" पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23-rtc" पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-rtc" पूर्ण,
	अणु .compatible = "allwinner,sun8i-r40-rtc" पूर्ण,
	अणु .compatible = "allwinner,sun8i-v3-rtc" पूर्ण,
	अणु .compatible = "allwinner,sun50i-h5-rtc" पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-rtc" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_rtc_dt_ids);

अटल काष्ठा platक्रमm_driver sun6i_rtc_driver = अणु
	.probe		= sun6i_rtc_probe,
	.driver		= अणु
		.name		= "sun6i-rtc",
		.of_match_table = sun6i_rtc_dt_ids,
		.pm = &sun6i_rtc_pm_ops,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(sun6i_rtc_driver);
