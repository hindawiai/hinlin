<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTC Driver क्रम X-Powers AC100
 *
 * Copyright (c) 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/bcd.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/ac100.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/types.h>

/* Control रेजिस्टर */
#घोषणा AC100_RTC_CTRL_24HOUR	BIT(0)

/* Clock output रेजिस्टर bits */
#घोषणा AC100_CLKOUT_PRE_DIV_SHIFT	5
#घोषणा AC100_CLKOUT_PRE_DIV_WIDTH	3
#घोषणा AC100_CLKOUT_MUX_SHIFT		4
#घोषणा AC100_CLKOUT_MUX_WIDTH		1
#घोषणा AC100_CLKOUT_DIV_SHIFT		1
#घोषणा AC100_CLKOUT_DIV_WIDTH		3
#घोषणा AC100_CLKOUT_EN			BIT(0)

/* RTC */
#घोषणा AC100_RTC_SEC_MASK	GENMASK(6, 0)
#घोषणा AC100_RTC_MIN_MASK	GENMASK(6, 0)
#घोषणा AC100_RTC_HOU_MASK	GENMASK(5, 0)
#घोषणा AC100_RTC_WEE_MASK	GENMASK(2, 0)
#घोषणा AC100_RTC_DAY_MASK	GENMASK(5, 0)
#घोषणा AC100_RTC_MON_MASK	GENMASK(4, 0)
#घोषणा AC100_RTC_YEA_MASK	GENMASK(7, 0)
#घोषणा AC100_RTC_YEA_LEAP	BIT(15)
#घोषणा AC100_RTC_UPD_TRIGGER	BIT(15)

/* Alarm (wall घड़ी) */
#घोषणा AC100_ALM_INT_ENABLE	BIT(0)

#घोषणा AC100_ALM_SEC_MASK	GENMASK(6, 0)
#घोषणा AC100_ALM_MIN_MASK	GENMASK(6, 0)
#घोषणा AC100_ALM_HOU_MASK	GENMASK(5, 0)
#घोषणा AC100_ALM_WEE_MASK	GENMASK(2, 0)
#घोषणा AC100_ALM_DAY_MASK	GENMASK(5, 0)
#घोषणा AC100_ALM_MON_MASK	GENMASK(4, 0)
#घोषणा AC100_ALM_YEA_MASK	GENMASK(7, 0)
#घोषणा AC100_ALM_ENABLE_FLAG	BIT(15)
#घोषणा AC100_ALM_UPD_TRIGGER	BIT(15)

/*
 * The year parameter passed to the driver is usually an offset relative to
 * the year 1900. This macro is used to convert this offset to another one
 * relative to the minimum year allowed by the hardware.
 *
 * The year range is 1970 - 2069. This range is selected to match Allwinner's
 * driver.
 */
#घोषणा AC100_YEAR_MIN				1970
#घोषणा AC100_YEAR_MAX				2069
#घोषणा AC100_YEAR_OFF				(AC100_YEAR_MIN - 1900)

काष्ठा ac100_clkout अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	u8 offset;
पूर्ण;

#घोषणा to_ac100_clkout(_hw) container_of(_hw, काष्ठा ac100_clkout, hw)

#घोषणा AC100_RTC_32K_NAME	"ac100-rtc-32k"
#घोषणा AC100_RTC_32K_RATE	32768
#घोषणा AC100_CLKOUT_NUM	3

अटल स्थिर अक्षर * स्थिर ac100_clkout_names[AC100_CLKOUT_NUM] = अणु
	"ac100-cko1-rtc",
	"ac100-cko2-rtc",
	"ac100-cko3-rtc",
पूर्ण;

काष्ठा ac100_rtc_dev अणु
	काष्ठा rtc_device *rtc;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	पूर्णांक irq;
	अचिन्हित दीर्घ alarm;

	काष्ठा clk_hw *rtc_32k_clk;
	काष्ठा ac100_clkout clks[AC100_CLKOUT_NUM];
	काष्ठा clk_hw_onecell_data *clk_data;
पूर्ण;

/**
 * Clock controls क्रम 3 घड़ी output pins
 */

अटल स्थिर काष्ठा clk_भाग_प्रकारable ac100_clkout_preभाग[] = अणु
	अणु .val = 0, .भाग = 1 पूर्ण,
	अणु .val = 1, .भाग = 2 पूर्ण,
	अणु .val = 2, .भाग = 4 पूर्ण,
	अणु .val = 3, .भाग = 8 पूर्ण,
	अणु .val = 4, .भाग = 16 पूर्ण,
	अणु .val = 5, .भाग = 32 पूर्ण,
	अणु .val = 6, .भाग = 64 पूर्ण,
	अणु .val = 7, .भाग = 122 पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* Abuse the fact that one parent is 32768 Hz, and the other is 4 MHz */
अटल अचिन्हित दीर्घ ac100_clkout_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ prate)
अणु
	काष्ठा ac100_clkout *clk = to_ac100_clkout(hw);
	अचिन्हित पूर्णांक reg, भाग;

	regmap_पढ़ो(clk->regmap, clk->offset, &reg);

	/* Handle pre-भागider first */
	अगर (prate != AC100_RTC_32K_RATE) अणु
		भाग = (reg >> AC100_CLKOUT_PRE_DIV_SHIFT) &
			((1 << AC100_CLKOUT_PRE_DIV_WIDTH) - 1);
		prate = भागider_recalc_rate(hw, prate, भाग,
					    ac100_clkout_preभाग, 0,
					    AC100_CLKOUT_PRE_DIV_WIDTH);
	पूर्ण

	भाग = (reg >> AC100_CLKOUT_DIV_SHIFT) &
		(BIT(AC100_CLKOUT_DIV_WIDTH) - 1);
	वापस भागider_recalc_rate(hw, prate, भाग, शून्य,
				   CLK_DIVIDER_POWER_OF_TWO,
				   AC100_CLKOUT_DIV_WIDTH);
पूर्ण

अटल दीर्घ ac100_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ prate)
अणु
	अचिन्हित दीर्घ best_rate = 0, पंचांगp_rate, पंचांगp_prate;
	पूर्णांक i;

	अगर (prate == AC100_RTC_32K_RATE)
		वापस भागider_round_rate(hw, rate, &prate, शून्य,
					  AC100_CLKOUT_DIV_WIDTH,
					  CLK_DIVIDER_POWER_OF_TWO);

	क्रम (i = 0; ac100_clkout_preभाग[i].भाग; i++) अणु
		पंचांगp_prate = DIV_ROUND_UP(prate, ac100_clkout_preभाग[i].val);
		पंचांगp_rate = भागider_round_rate(hw, rate, &पंचांगp_prate, शून्य,
					      AC100_CLKOUT_DIV_WIDTH,
					      CLK_DIVIDER_POWER_OF_TWO);

		अगर (पंचांगp_rate > rate)
			जारी;
		अगर (rate - पंचांगp_rate < best_rate - पंचांगp_rate)
			best_rate = पंचांगp_rate;
	पूर्ण

	वापस best_rate;
पूर्ण

अटल पूर्णांक ac100_clkout_determine_rate(काष्ठा clk_hw *hw,
				       काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_hw *best_parent;
	अचिन्हित दीर्घ best = 0;
	पूर्णांक i, num_parents = clk_hw_get_num_parents(hw);

	क्रम (i = 0; i < num_parents; i++) अणु
		काष्ठा clk_hw *parent = clk_hw_get_parent_by_index(hw, i);
		अचिन्हित दीर्घ पंचांगp, prate;

		/*
		 * The घड़ी has two parents, one is a fixed घड़ी which is
		 * पूर्णांकernally रेजिस्टरed by the ac100 driver. The other parent
		 * is a घड़ी from the codec side of the chip, which we
		 * properly declare and reference in the devicetree and is
		 * not implemented in any driver right now.
		 * If the घड़ी core looks क्रम the parent of that second
		 * missing घड़ी, it can't find one that is रेजिस्टरed and
		 * वापसs शून्य.
		 * So we end up in a situation where clk_hw_get_num_parents
		 * वापसs the amount of घड़ीs we can be parented to, but
		 * clk_hw_get_parent_by_index will not वापस the orphan
		 * घड़ीs.
		 * Thus we need to check अगर the parent exists beक्रमe
		 * we get the parent rate, so we could use the RTC
		 * without रुकोing क्रम the codec to be supported.
		 */
		अगर (!parent)
			जारी;

		prate = clk_hw_get_rate(parent);

		पंचांगp = ac100_clkout_round_rate(hw, req->rate, prate);

		अगर (पंचांगp > req->rate)
			जारी;
		अगर (req->rate - पंचांगp < req->rate - best) अणु
			best = पंचांगp;
			best_parent = parent;
		पूर्ण
	पूर्ण

	अगर (!best)
		वापस -EINVAL;

	req->best_parent_hw = best_parent;
	req->best_parent_rate = best;
	req->rate = best;

	वापस 0;
पूर्ण

अटल पूर्णांक ac100_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ prate)
अणु
	काष्ठा ac100_clkout *clk = to_ac100_clkout(hw);
	पूर्णांक भाग = 0, pre_भाग = 0;

	करो अणु
		भाग = भागider_get_val(rate * ac100_clkout_preभाग[pre_भाग].भाग,
				      prate, शून्य, AC100_CLKOUT_DIV_WIDTH,
				      CLK_DIVIDER_POWER_OF_TWO);
		अगर (भाग >= 0)
			अवरोध;
	पूर्ण जबतक (prate != AC100_RTC_32K_RATE &&
		 ac100_clkout_preभाग[++pre_भाग].भाग);

	अगर (भाग < 0)
		वापस भाग;

	pre_भाग = ac100_clkout_preभाग[pre_भाग].val;

	regmap_update_bits(clk->regmap, clk->offset,
			   ((1 << AC100_CLKOUT_DIV_WIDTH) - 1) << AC100_CLKOUT_DIV_SHIFT |
			   ((1 << AC100_CLKOUT_PRE_DIV_WIDTH) - 1) << AC100_CLKOUT_PRE_DIV_SHIFT,
			   (भाग - 1) << AC100_CLKOUT_DIV_SHIFT |
			   (pre_भाग - 1) << AC100_CLKOUT_PRE_DIV_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक ac100_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ac100_clkout *clk = to_ac100_clkout(hw);

	वापस regmap_update_bits(clk->regmap, clk->offset, AC100_CLKOUT_EN,
				  AC100_CLKOUT_EN);
पूर्ण

अटल व्योम ac100_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा ac100_clkout *clk = to_ac100_clkout(hw);

	regmap_update_bits(clk->regmap, clk->offset, AC100_CLKOUT_EN, 0);
पूर्ण

अटल पूर्णांक ac100_clkout_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा ac100_clkout *clk = to_ac100_clkout(hw);
	अचिन्हित पूर्णांक reg;

	regmap_पढ़ो(clk->regmap, clk->offset, &reg);

	वापस reg & AC100_CLKOUT_EN;
पूर्ण

अटल u8 ac100_clkout_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ac100_clkout *clk = to_ac100_clkout(hw);
	अचिन्हित पूर्णांक reg;

	regmap_पढ़ो(clk->regmap, clk->offset, &reg);

	वापस (reg >> AC100_CLKOUT_MUX_SHIFT) & 0x1;
पूर्ण

अटल पूर्णांक ac100_clkout_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा ac100_clkout *clk = to_ac100_clkout(hw);

	वापस regmap_update_bits(clk->regmap, clk->offset,
				  BIT(AC100_CLKOUT_MUX_SHIFT),
				  index ? BIT(AC100_CLKOUT_MUX_SHIFT) : 0);
पूर्ण

अटल स्थिर काष्ठा clk_ops ac100_clkout_ops = अणु
	.prepare	= ac100_clkout_prepare,
	.unprepare	= ac100_clkout_unprepare,
	.is_prepared	= ac100_clkout_is_prepared,
	.recalc_rate	= ac100_clkout_recalc_rate,
	.determine_rate	= ac100_clkout_determine_rate,
	.get_parent	= ac100_clkout_get_parent,
	.set_parent	= ac100_clkout_set_parent,
	.set_rate	= ac100_clkout_set_rate,
पूर्ण;

अटल पूर्णांक ac100_rtc_रेजिस्टर_clks(काष्ठा ac100_rtc_dev *chip)
अणु
	काष्ठा device_node *np = chip->dev->of_node;
	स्थिर अक्षर *parents[2] = अणुAC100_RTC_32K_NAMEपूर्ण;
	पूर्णांक i, ret;

	chip->clk_data = devm_kzalloc(chip->dev,
				      काष्ठा_size(chip->clk_data, hws,
						  AC100_CLKOUT_NUM),
				      GFP_KERNEL);
	अगर (!chip->clk_data)
		वापस -ENOMEM;

	chip->rtc_32k_clk = clk_hw_रेजिस्टर_fixed_rate(chip->dev,
						       AC100_RTC_32K_NAME,
						       शून्य, 0,
						       AC100_RTC_32K_RATE);
	अगर (IS_ERR(chip->rtc_32k_clk)) अणु
		ret = PTR_ERR(chip->rtc_32k_clk);
		dev_err(chip->dev, "Failed to register RTC-32k clock: %d\n",
			ret);
		वापस ret;
	पूर्ण

	parents[1] = of_clk_get_parent_name(np, 0);
	अगर (!parents[1]) अणु
		dev_err(chip->dev, "Failed to get ADDA 4M clock\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < AC100_CLKOUT_NUM; i++) अणु
		काष्ठा ac100_clkout *clk = &chip->clks[i];
		काष्ठा clk_init_data init = अणु
			.name = ac100_clkout_names[i],
			.ops = &ac100_clkout_ops,
			.parent_names = parents,
			.num_parents = ARRAY_SIZE(parents),
			.flags = 0,
		पूर्ण;

		of_property_पढ़ो_string_index(np, "clock-output-names",
					      i, &init.name);
		clk->regmap = chip->regmap;
		clk->offset = AC100_CLKOUT_CTRL1 + i;
		clk->hw.init = &init;

		ret = devm_clk_hw_रेजिस्टर(chip->dev, &clk->hw);
		अगर (ret) अणु
			dev_err(chip->dev, "Failed to register clk '%s': %d\n",
				init.name, ret);
			जाओ err_unरेजिस्टर_rtc_32k;
		पूर्ण

		chip->clk_data->hws[i] = &clk->hw;
	पूर्ण

	chip->clk_data->num = i;
	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, chip->clk_data);
	अगर (ret)
		जाओ err_unरेजिस्टर_rtc_32k;

	वापस 0;

err_unरेजिस्टर_rtc_32k:
	clk_unरेजिस्टर_fixed_rate(chip->rtc_32k_clk->clk);

	वापस ret;
पूर्ण

अटल व्योम ac100_rtc_unरेजिस्टर_clks(काष्ठा ac100_rtc_dev *chip)
अणु
	of_clk_del_provider(chip->dev->of_node);
	clk_unरेजिस्टर_fixed_rate(chip->rtc_32k_clk->clk);
पूर्ण

/**
 * RTC related bits
 */
अटल पूर्णांक ac100_rtc_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा ac100_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = chip->regmap;
	u16 reg[7];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(regmap, AC100_RTC_SEC, reg, 7);
	अगर (ret)
		वापस ret;

	rtc_पंचांग->पंचांग_sec  = bcd2bin(reg[0] & AC100_RTC_SEC_MASK);
	rtc_पंचांग->पंचांग_min  = bcd2bin(reg[1] & AC100_RTC_MIN_MASK);
	rtc_पंचांग->पंचांग_hour = bcd2bin(reg[2] & AC100_RTC_HOU_MASK);
	rtc_पंचांग->पंचांग_wday = bcd2bin(reg[3] & AC100_RTC_WEE_MASK);
	rtc_पंचांग->पंचांग_mday = bcd2bin(reg[4] & AC100_RTC_DAY_MASK);
	rtc_पंचांग->पंचांग_mon  = bcd2bin(reg[5] & AC100_RTC_MON_MASK) - 1;
	rtc_पंचांग->पंचांग_year = bcd2bin(reg[6] & AC100_RTC_YEA_MASK) +
			  AC100_YEAR_OFF;

	वापस 0;
पूर्ण

अटल पूर्णांक ac100_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा ac100_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = chip->regmap;
	पूर्णांक year;
	u16 reg[8];

	/* our RTC has a limited year range... */
	year = rtc_पंचांग->पंचांग_year - AC100_YEAR_OFF;
	अगर (year < 0 || year > (AC100_YEAR_MAX - 1900)) अणु
		dev_err(dev, "rtc only supports year in range %d - %d\n",
			AC100_YEAR_MIN, AC100_YEAR_MAX);
		वापस -EINVAL;
	पूर्ण

	/* convert to BCD */
	reg[0] = bin2bcd(rtc_पंचांग->पंचांग_sec)     & AC100_RTC_SEC_MASK;
	reg[1] = bin2bcd(rtc_पंचांग->पंचांग_min)     & AC100_RTC_MIN_MASK;
	reg[2] = bin2bcd(rtc_पंचांग->पंचांग_hour)    & AC100_RTC_HOU_MASK;
	reg[3] = bin2bcd(rtc_पंचांग->पंचांग_wday)    & AC100_RTC_WEE_MASK;
	reg[4] = bin2bcd(rtc_पंचांग->पंचांग_mday)    & AC100_RTC_DAY_MASK;
	reg[5] = bin2bcd(rtc_पंचांग->पंचांग_mon + 1) & AC100_RTC_MON_MASK;
	reg[6] = bin2bcd(year)		     & AC100_RTC_YEA_MASK;
	/* trigger ग_लिखो */
	reg[7] = AC100_RTC_UPD_TRIGGER;

	/* Is it a leap year? */
	अगर (is_leap_year(year + AC100_YEAR_OFF + 1900))
		reg[6] |= AC100_RTC_YEA_LEAP;

	वापस regmap_bulk_ग_लिखो(regmap, AC100_RTC_SEC, reg, 8);
पूर्ण

अटल पूर्णांक ac100_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक en)
अणु
	काष्ठा ac100_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = chip->regmap;
	अचिन्हित पूर्णांक val;

	val = en ? AC100_ALM_INT_ENABLE : 0;

	वापस regmap_ग_लिखो(regmap, AC100_ALM_INT_ENA, val);
पूर्ण

अटल पूर्णांक ac100_rtc_get_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा ac100_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = chip->regmap;
	काष्ठा rtc_समय *alrm_पंचांग = &alrm->समय;
	u16 reg[7];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, AC100_ALM_INT_ENA, &val);
	अगर (ret)
		वापस ret;

	alrm->enabled = !!(val & AC100_ALM_INT_ENABLE);

	ret = regmap_bulk_पढ़ो(regmap, AC100_ALM_SEC, reg, 7);
	अगर (ret)
		वापस ret;

	alrm_पंचांग->पंचांग_sec  = bcd2bin(reg[0] & AC100_ALM_SEC_MASK);
	alrm_पंचांग->पंचांग_min  = bcd2bin(reg[1] & AC100_ALM_MIN_MASK);
	alrm_पंचांग->पंचांग_hour = bcd2bin(reg[2] & AC100_ALM_HOU_MASK);
	alrm_पंचांग->पंचांग_wday = bcd2bin(reg[3] & AC100_ALM_WEE_MASK);
	alrm_पंचांग->पंचांग_mday = bcd2bin(reg[4] & AC100_ALM_DAY_MASK);
	alrm_पंचांग->पंचांग_mon  = bcd2bin(reg[5] & AC100_ALM_MON_MASK) - 1;
	alrm_पंचांग->पंचांग_year = bcd2bin(reg[6] & AC100_ALM_YEA_MASK) +
			   AC100_YEAR_OFF;

	वापस 0;
पूर्ण

अटल पूर्णांक ac100_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा ac100_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = chip->regmap;
	काष्ठा rtc_समय *alrm_पंचांग = &alrm->समय;
	u16 reg[8];
	पूर्णांक year;
	पूर्णांक ret;

	/* our alarm has a limited year range... */
	year = alrm_पंचांग->पंचांग_year - AC100_YEAR_OFF;
	अगर (year < 0 || year > (AC100_YEAR_MAX - 1900)) अणु
		dev_err(dev, "alarm only supports year in range %d - %d\n",
			AC100_YEAR_MIN, AC100_YEAR_MAX);
		वापस -EINVAL;
	पूर्ण

	/* convert to BCD */
	reg[0] = (bin2bcd(alrm_पंचांग->पंचांग_sec)  & AC100_ALM_SEC_MASK) |
			AC100_ALM_ENABLE_FLAG;
	reg[1] = (bin2bcd(alrm_पंचांग->पंचांग_min)  & AC100_ALM_MIN_MASK) |
			AC100_ALM_ENABLE_FLAG;
	reg[2] = (bin2bcd(alrm_पंचांग->पंचांग_hour) & AC100_ALM_HOU_MASK) |
			AC100_ALM_ENABLE_FLAG;
	/* Do not enable weekday alarm */
	reg[3] = bin2bcd(alrm_पंचांग->पंचांग_wday) & AC100_ALM_WEE_MASK;
	reg[4] = (bin2bcd(alrm_पंचांग->पंचांग_mday) & AC100_ALM_DAY_MASK) |
			AC100_ALM_ENABLE_FLAG;
	reg[5] = (bin2bcd(alrm_पंचांग->पंचांग_mon + 1)  & AC100_ALM_MON_MASK) |
			AC100_ALM_ENABLE_FLAG;
	reg[6] = (bin2bcd(year) & AC100_ALM_YEA_MASK) |
			AC100_ALM_ENABLE_FLAG;
	/* trigger ग_लिखो */
	reg[7] = AC100_ALM_UPD_TRIGGER;

	ret = regmap_bulk_ग_लिखो(regmap, AC100_ALM_SEC, reg, 8);
	अगर (ret)
		वापस ret;

	वापस ac100_rtc_alarm_irq_enable(dev, alrm->enabled);
पूर्ण

अटल irqवापस_t ac100_rtc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ac100_rtc_dev *chip = data;
	काष्ठा regmap *regmap = chip->regmap;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	rtc_lock(chip->rtc);

	/* पढ़ो status */
	ret = regmap_पढ़ो(regmap, AC100_ALM_INT_STA, &val);
	अगर (ret)
		जाओ out;

	अगर (val & AC100_ALM_INT_ENABLE) अणु
		/* संकेत rtc framework */
		rtc_update_irq(chip->rtc, 1, RTC_AF | RTC_IRQF);

		/* clear status */
		ret = regmap_ग_लिखो(regmap, AC100_ALM_INT_STA, val);
		अगर (ret)
			जाओ out;

		/* disable पूर्णांकerrupt */
		ret = ac100_rtc_alarm_irq_enable(chip->dev, 0);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	rtc_unlock(chip->rtc);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ac100_rtc_ops = अणु
	.पढ़ो_समय	  = ac100_rtc_get_समय,
	.set_समय	  = ac100_rtc_set_समय,
	.पढ़ो_alarm	  = ac100_rtc_get_alarm,
	.set_alarm	  = ac100_rtc_set_alarm,
	.alarm_irq_enable = ac100_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक ac100_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ac100_dev *ac100 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा ac100_rtc_dev *chip;
	पूर्णांक ret;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chip);
	chip->dev = &pdev->dev;
	chip->regmap = ac100->regmap;

	chip->irq = platक्रमm_get_irq(pdev, 0);
	अगर (chip->irq < 0)
		वापस chip->irq;

	chip->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(chip->rtc))
		वापस PTR_ERR(chip->rtc);

	chip->rtc->ops = &ac100_rtc_ops;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, chip->irq, शून्य,
					ac100_rtc_irq,
					IRQF_SHARED | IRQF_ONESHOT,
					dev_name(&pdev->dev), chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not request IRQ\n");
		वापस ret;
	पूर्ण

	/* always use 24 hour mode */
	regmap_ग_लिखो_bits(chip->regmap, AC100_RTC_CTRL, AC100_RTC_CTRL_24HOUR,
			  AC100_RTC_CTRL_24HOUR);

	/* disable counter alarm पूर्णांकerrupt */
	regmap_ग_लिखो(chip->regmap, AC100_ALM_INT_ENA, 0);

	/* clear counter alarm pending पूर्णांकerrupts */
	regmap_ग_लिखो(chip->regmap, AC100_ALM_INT_STA, AC100_ALM_INT_ENABLE);

	ret = ac100_rtc_रेजिस्टर_clks(chip);
	अगर (ret)
		वापस ret;

	वापस devm_rtc_रेजिस्टर_device(chip->rtc);
पूर्ण

अटल पूर्णांक ac100_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ac100_rtc_dev *chip = platक्रमm_get_drvdata(pdev);

	ac100_rtc_unरेजिस्टर_clks(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ac100_rtc_match[] = अणु
	अणु .compatible = "x-powers,ac100-rtc" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ac100_rtc_match);

अटल काष्ठा platक्रमm_driver ac100_rtc_driver = अणु
	.probe		= ac100_rtc_probe,
	.हटाओ		= ac100_rtc_हटाओ,
	.driver		= अणु
		.name		= "ac100-rtc",
		.of_match_table	= of_match_ptr(ac100_rtc_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ac100_rtc_driver);

MODULE_DESCRIPTION("X-Powers AC100 RTC driver");
MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_LICENSE("GPL v2");
