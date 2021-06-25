<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * clk-si5351.c: Silicon Laboratories Si5351A/B/C I2C Clock Generator
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Rabeeh Khoury <rabeeh@solid-run.com>
 *
 * References:
 * [1] "Si5351A/B/C Data Sheet"
 *     https://www.siद_असल.com/Support%20Documents/TechnicalDocs/Si5351.pdf
 * [2] "Manually Generating an Si5351 Register Map"
 *     https://www.siद_असल.com/Support%20Documents/TechnicalDocs/AN619.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rational.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_data/si5351.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/भाग64.h>

#समावेश "clk-si5351.h"

काष्ठा si5351_driver_data;

काष्ठा si5351_parameters अणु
	अचिन्हित दीर्घ	p1;
	अचिन्हित दीर्घ	p2;
	अचिन्हित दीर्घ	p3;
	पूर्णांक		valid;
पूर्ण;

काष्ठा si5351_hw_data अणु
	काष्ठा clk_hw			hw;
	काष्ठा si5351_driver_data	*drvdata;
	काष्ठा si5351_parameters	params;
	अचिन्हित अक्षर			num;
पूर्ण;

काष्ठा si5351_driver_data अणु
	क्रमागत si5351_variant	variant;
	काष्ठा i2c_client	*client;
	काष्ठा regmap		*regmap;

	काष्ठा clk		*pxtal;
	स्थिर अक्षर		*pxtal_name;
	काष्ठा clk_hw		xtal;
	काष्ठा clk		*pclkin;
	स्थिर अक्षर		*pclkin_name;
	काष्ठा clk_hw		clkin;

	काष्ठा si5351_hw_data	pll[2];
	काष्ठा si5351_hw_data	*msynth;
	काष्ठा si5351_hw_data	*clkout;
	माप_प्रकार			num_clkout;
पूर्ण;

अटल स्थिर अक्षर * स्थिर si5351_input_names[] = अणु
	"xtal", "clkin"
पूर्ण;
अटल स्थिर अक्षर * स्थिर si5351_pll_names[] = अणु
	"si5351_plla", "si5351_pllb", "si5351_vxco"
पूर्ण;
अटल स्थिर अक्षर * स्थिर si5351_msynth_names[] = अणु
	"ms0", "ms1", "ms2", "ms3", "ms4", "ms5", "ms6", "ms7"
पूर्ण;
अटल स्थिर अक्षर * स्थिर si5351_clkout_names[] = अणु
	"clk0", "clk1", "clk2", "clk3", "clk4", "clk5", "clk6", "clk7"
पूर्ण;

/*
 * Si5351 i2c regmap
 */
अटल अंतरभूत u8 si5351_reg_पढ़ो(काष्ठा si5351_driver_data *drvdata, u8 reg)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(drvdata->regmap, reg, &val);
	अगर (ret) अणु
		dev_err(&drvdata->client->dev,
			"unable to read from reg%02x\n", reg);
		वापस 0;
	पूर्ण

	वापस (u8)val;
पूर्ण

अटल अंतरभूत पूर्णांक si5351_bulk_पढ़ो(काष्ठा si5351_driver_data *drvdata,
				   u8 reg, u8 count, u8 *buf)
अणु
	वापस regmap_bulk_पढ़ो(drvdata->regmap, reg, buf, count);
पूर्ण

अटल अंतरभूत पूर्णांक si5351_reg_ग_लिखो(काष्ठा si5351_driver_data *drvdata,
				   u8 reg, u8 val)
अणु
	वापस regmap_ग_लिखो(drvdata->regmap, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक si5351_bulk_ग_लिखो(काष्ठा si5351_driver_data *drvdata,
				    u8 reg, u8 count, स्थिर u8 *buf)
अणु
	वापस regmap_raw_ग_लिखो(drvdata->regmap, reg, buf, count);
पूर्ण

अटल अंतरभूत पूर्णांक si5351_set_bits(काष्ठा si5351_driver_data *drvdata,
				  u8 reg, u8 mask, u8 val)
अणु
	वापस regmap_update_bits(drvdata->regmap, reg, mask, val);
पूर्ण

अटल अंतरभूत u8 si5351_msynth_params_address(पूर्णांक num)
अणु
	अगर (num > 5)
		वापस SI5351_CLK6_PARAMETERS + (num - 6);
	वापस SI5351_CLK0_PARAMETERS + (SI5351_PARAMETERS_LENGTH * num);
पूर्ण

अटल व्योम si5351_पढ़ो_parameters(काष्ठा si5351_driver_data *drvdata,
				   u8 reg, काष्ठा si5351_parameters *params)
अणु
	u8 buf[SI5351_PARAMETERS_LENGTH];

	चयन (reg) अणु
	हाल SI5351_CLK6_PARAMETERS:
	हाल SI5351_CLK7_PARAMETERS:
		buf[0] = si5351_reg_पढ़ो(drvdata, reg);
		params->p1 = buf[0];
		params->p2 = 0;
		params->p3 = 1;
		अवरोध;
	शेष:
		si5351_bulk_पढ़ो(drvdata, reg, SI5351_PARAMETERS_LENGTH, buf);
		params->p1 = ((buf[2] & 0x03) << 16) | (buf[3] << 8) | buf[4];
		params->p2 = ((buf[5] & 0x0f) << 16) | (buf[6] << 8) | buf[7];
		params->p3 = ((buf[5] & 0xf0) << 12) | (buf[0] << 8) | buf[1];
	पूर्ण
	params->valid = 1;
पूर्ण

अटल व्योम si5351_ग_लिखो_parameters(काष्ठा si5351_driver_data *drvdata,
				    u8 reg, काष्ठा si5351_parameters *params)
अणु
	u8 buf[SI5351_PARAMETERS_LENGTH];

	चयन (reg) अणु
	हाल SI5351_CLK6_PARAMETERS:
	हाल SI5351_CLK7_PARAMETERS:
		buf[0] = params->p1 & 0xff;
		si5351_reg_ग_लिखो(drvdata, reg, buf[0]);
		अवरोध;
	शेष:
		buf[0] = ((params->p3 & 0x0ff00) >> 8) & 0xff;
		buf[1] = params->p3 & 0xff;
		/* save rभाग and भागby4 */
		buf[2] = si5351_reg_पढ़ो(drvdata, reg + 2) & ~0x03;
		buf[2] |= ((params->p1 & 0x30000) >> 16) & 0x03;
		buf[3] = ((params->p1 & 0x0ff00) >> 8) & 0xff;
		buf[4] = params->p1 & 0xff;
		buf[5] = ((params->p3 & 0xf0000) >> 12) |
			((params->p2 & 0xf0000) >> 16);
		buf[6] = ((params->p2 & 0x0ff00) >> 8) & 0xff;
		buf[7] = params->p2 & 0xff;
		si5351_bulk_ग_लिखो(drvdata, reg, SI5351_PARAMETERS_LENGTH, buf);
	पूर्ण
पूर्ण

अटल bool si5351_regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SI5351_DEVICE_STATUS:
	हाल SI5351_INTERRUPT_STATUS:
	हाल SI5351_PLL_RESET:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool si5351_regmap_is_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* reserved रेजिस्टरs */
	अगर (reg >= 4 && reg <= 8)
		वापस false;
	अगर (reg >= 10 && reg <= 14)
		वापस false;
	अगर (reg >= 173 && reg <= 176)
		वापस false;
	अगर (reg >= 178 && reg <= 182)
		वापस false;
	/* पढ़ो-only */
	अगर (reg == SI5351_DEVICE_STATUS)
		वापस false;
	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config si5351_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = 187,
	.ग_लिखोable_reg = si5351_regmap_is_ग_लिखोable,
	.अस्थिर_reg = si5351_regmap_is_अस्थिर,
पूर्ण;

/*
 * Si5351 xtal घड़ी input
 */
अटल पूर्णांक si5351_xtal_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_driver_data *drvdata =
		container_of(hw, काष्ठा si5351_driver_data, xtal);
	si5351_set_bits(drvdata, SI5351_FANOUT_ENABLE,
			SI5351_XTAL_ENABLE, SI5351_XTAL_ENABLE);
	वापस 0;
पूर्ण

अटल व्योम si5351_xtal_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_driver_data *drvdata =
		container_of(hw, काष्ठा si5351_driver_data, xtal);
	si5351_set_bits(drvdata, SI5351_FANOUT_ENABLE,
			SI5351_XTAL_ENABLE, 0);
पूर्ण

अटल स्थिर काष्ठा clk_ops si5351_xtal_ops = अणु
	.prepare = si5351_xtal_prepare,
	.unprepare = si5351_xtal_unprepare,
पूर्ण;

/*
 * Si5351 clkin घड़ी input (Si5351C only)
 */
अटल पूर्णांक si5351_clkin_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_driver_data *drvdata =
		container_of(hw, काष्ठा si5351_driver_data, clkin);
	si5351_set_bits(drvdata, SI5351_FANOUT_ENABLE,
			SI5351_CLKIN_ENABLE, SI5351_CLKIN_ENABLE);
	वापस 0;
पूर्ण

अटल व्योम si5351_clkin_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_driver_data *drvdata =
		container_of(hw, काष्ठा si5351_driver_data, clkin);
	si5351_set_bits(drvdata, SI5351_FANOUT_ENABLE,
			SI5351_CLKIN_ENABLE, 0);
पूर्ण

/*
 * CMOS घड़ी source स्थिरraपूर्णांकs:
 * The input frequency range of the PLL is 10Mhz to 40MHz.
 * If CLKIN is >40MHz, the input भागider must be used.
 */
अटल अचिन्हित दीर्घ si5351_clkin_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा si5351_driver_data *drvdata =
		container_of(hw, काष्ठा si5351_driver_data, clkin);
	अचिन्हित दीर्घ rate;
	अचिन्हित अक्षर iभाग;

	rate = parent_rate;
	अगर (parent_rate > 160000000) अणु
		iभाग = SI5351_CLKIN_DIV_8;
		rate /= 8;
	पूर्ण अन्यथा अगर (parent_rate > 80000000) अणु
		iभाग = SI5351_CLKIN_DIV_4;
		rate /= 4;
	पूर्ण अन्यथा अगर (parent_rate > 40000000) अणु
		iभाग = SI5351_CLKIN_DIV_2;
		rate /= 2;
	पूर्ण अन्यथा अणु
		iभाग = SI5351_CLKIN_DIV_1;
	पूर्ण

	si5351_set_bits(drvdata, SI5351_PLL_INPUT_SOURCE,
			SI5351_CLKIN_DIV_MASK, iभाग);

	dev_dbg(&drvdata->client->dev, "%s - clkin div = %d, rate = %lu\n",
		__func__, (1 << (iभाग >> 6)), rate);

	वापस rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops si5351_clkin_ops = अणु
	.prepare = si5351_clkin_prepare,
	.unprepare = si5351_clkin_unprepare,
	.recalc_rate = si5351_clkin_recalc_rate,
पूर्ण;

/*
 * Si5351 vxco घड़ी input (Si5351B only)
 */

अटल पूर्णांक si5351_vxco_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);

	dev_warn(&hwdata->drvdata->client->dev, "VXCO currently unsupported\n");

	वापस 0;
पूर्ण

अटल व्योम si5351_vxco_unprepare(काष्ठा clk_hw *hw)
अणु
पूर्ण

अटल अचिन्हित दीर्घ si5351_vxco_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक si5351_vxco_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops si5351_vxco_ops = अणु
	.prepare = si5351_vxco_prepare,
	.unprepare = si5351_vxco_unprepare,
	.recalc_rate = si5351_vxco_recalc_rate,
	.set_rate = si5351_vxco_set_rate,
पूर्ण;

/*
 * Si5351 pll a/b
 *
 * Feedback Multisynth Divider Equations [2]
 *
 * fVCO = fIN * (a + b/c)
 *
 * with 15 + 0/1048575 <= (a + b/c) <= 90 + 0/1048575 and
 * fIN = fXTAL or fIN = fCLKIN/CLKIN_DIV
 *
 * Feedback Multisynth Register Equations
 *
 * (1) MSNx_P1[17:0] = 128 * a + न्यूनमान(128 * b/c) - 512
 * (2) MSNx_P2[19:0] = 128 * b - c * न्यूनमान(128 * b/c) = (128*b) mod c
 * (3) MSNx_P3[19:0] = c
 *
 * Transposing (2) yields: (4) न्यूनमान(128 * b/c) = (128 * b / MSNx_P2)/c
 *
 * Using (4) on (1) yields:
 * MSNx_P1 = 128 * a + (128 * b/MSNx_P2)/c - 512
 * MSNx_P1 + 512 + MSNx_P2/c = 128 * a + 128 * b/c
 *
 * a + b/c = (MSNx_P1 + MSNx_P2/MSNx_P3 + 512)/128
 *         = (MSNx_P1*MSNx_P3 + MSNx_P2 + 512*MSNx_P3)/(128*MSNx_P3)
 *
 */
अटल पूर्णांक _si5351_pll_reparent(काष्ठा si5351_driver_data *drvdata,
				पूर्णांक num, क्रमागत si5351_pll_src parent)
अणु
	u8 mask = (num == 0) ? SI5351_PLLA_SOURCE : SI5351_PLLB_SOURCE;

	अगर (parent == SI5351_PLL_SRC_DEFAULT)
		वापस 0;

	अगर (num > 2)
		वापस -EINVAL;

	अगर (drvdata->variant != SI5351_VARIANT_C &&
	    parent != SI5351_PLL_SRC_XTAL)
		वापस -EINVAL;

	si5351_set_bits(drvdata, SI5351_PLL_INPUT_SOURCE, mask,
			(parent == SI5351_PLL_SRC_XTAL) ? 0 : mask);
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर si5351_pll_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	u8 mask = (hwdata->num == 0) ? SI5351_PLLA_SOURCE : SI5351_PLLB_SOURCE;
	u8 val;

	val = si5351_reg_पढ़ो(hwdata->drvdata, SI5351_PLL_INPUT_SOURCE);

	वापस (val & mask) ? 1 : 0;
पूर्ण

अटल पूर्णांक si5351_pll_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);

	अगर (hwdata->drvdata->variant != SI5351_VARIANT_C &&
	    index > 0)
		वापस -EPERM;

	अगर (index > 1)
		वापस -EINVAL;

	वापस _si5351_pll_reparent(hwdata->drvdata, hwdata->num,
			     (index == 0) ? SI5351_PLL_SRC_XTAL :
			     SI5351_PLL_SRC_CLKIN);
पूर्ण

अटल अचिन्हित दीर्घ si5351_pll_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	u8 reg = (hwdata->num == 0) ? SI5351_PLLA_PARAMETERS :
		SI5351_PLLB_PARAMETERS;
	अचिन्हित दीर्घ दीर्घ rate;

	अगर (!hwdata->params.valid)
		si5351_पढ़ो_parameters(hwdata->drvdata, reg, &hwdata->params);

	अगर (hwdata->params.p3 == 0)
		वापस parent_rate;

	/* fVCO = fIN * (P1*P3 + 512*P3 + P2)/(128*P3) */
	rate  = hwdata->params.p1 * hwdata->params.p3;
	rate += 512 * hwdata->params.p3;
	rate += hwdata->params.p2;
	rate *= parent_rate;
	करो_भाग(rate, 128 * hwdata->params.p3);

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: p1 = %lu, p2 = %lu, p3 = %lu, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw),
		hwdata->params.p1, hwdata->params.p2, hwdata->params.p3,
		parent_rate, (अचिन्हित दीर्घ)rate);

	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

अटल दीर्घ si5351_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	अचिन्हित दीर्घ rfrac, denom, a, b, c;
	अचिन्हित दीर्घ दीर्घ llपंचांगp;

	अगर (rate < SI5351_PLL_VCO_MIN)
		rate = SI5351_PLL_VCO_MIN;
	अगर (rate > SI5351_PLL_VCO_MAX)
		rate = SI5351_PLL_VCO_MAX;

	/* determine पूर्णांकeger part of feedback equation */
	a = rate / *parent_rate;

	अगर (a < SI5351_PLL_A_MIN)
		rate = *parent_rate * SI5351_PLL_A_MIN;
	अगर (a > SI5351_PLL_A_MAX)
		rate = *parent_rate * SI5351_PLL_A_MAX;

	/* find best approximation क्रम b/c = fVCO mod fIN */
	denom = 1000 * 1000;
	llपंचांगp = rate % (*parent_rate);
	llपंचांगp *= denom;
	करो_भाग(llपंचांगp, *parent_rate);
	rfrac = (अचिन्हित दीर्घ)llपंचांगp;

	b = 0;
	c = 1;
	अगर (rfrac)
		rational_best_approximation(rfrac, denom,
				    SI5351_PLL_B_MAX, SI5351_PLL_C_MAX, &b, &c);

	/* calculate parameters */
	hwdata->params.p3  = c;
	hwdata->params.p2  = (128 * b) % c;
	hwdata->params.p1  = 128 * a;
	hwdata->params.p1 += (128 * b / c);
	hwdata->params.p1 -= 512;

	/* recalculate rate by fIN * (a + b/c) */
	llपंचांगp  = *parent_rate;
	llपंचांगp *= b;
	करो_भाग(llपंचांगp, c);

	rate  = (अचिन्हित दीर्घ)llपंचांगp;
	rate += *parent_rate * a;

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: a = %lu, b = %lu, c = %lu, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw), a, b, c,
		*parent_rate, rate);

	वापस rate;
पूर्ण

अटल पूर्णांक si5351_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	u8 reg = (hwdata->num == 0) ? SI5351_PLLA_PARAMETERS :
		SI5351_PLLB_PARAMETERS;

	/* ग_लिखो multisynth parameters */
	si5351_ग_लिखो_parameters(hwdata->drvdata, reg, &hwdata->params);

	/* plla/pllb ctrl is in clk6/clk7 ctrl रेजिस्टरs */
	si5351_set_bits(hwdata->drvdata, SI5351_CLK6_CTRL + hwdata->num,
		SI5351_CLK_INTEGER_MODE,
		(hwdata->params.p2 == 0) ? SI5351_CLK_INTEGER_MODE : 0);

	/* Do a pll soft reset on the affected pll */
	si5351_reg_ग_लिखो(hwdata->drvdata, SI5351_PLL_RESET,
			 hwdata->num == 0 ? SI5351_PLL_RESET_A :
					    SI5351_PLL_RESET_B);

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: p1 = %lu, p2 = %lu, p3 = %lu, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw),
		hwdata->params.p1, hwdata->params.p2, hwdata->params.p3,
		parent_rate, rate);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops si5351_pll_ops = अणु
	.set_parent = si5351_pll_set_parent,
	.get_parent = si5351_pll_get_parent,
	.recalc_rate = si5351_pll_recalc_rate,
	.round_rate = si5351_pll_round_rate,
	.set_rate = si5351_pll_set_rate,
पूर्ण;

/*
 * Si5351 multisync भागider
 *
 * क्रम fOUT <= 150 MHz:
 *
 * fOUT = (fIN * (a + b/c)) / CLKOUTDIV
 *
 * with 6 + 0/1048575 <= (a + b/c) <= 1800 + 0/1048575 and
 * fIN = fVCO0, fVCO1
 *
 * Output Clock Multisynth Register Equations
 *
 * MSx_P1[17:0] = 128 * a + न्यूनमान(128 * b/c) - 512
 * MSx_P2[19:0] = 128 * b - c * न्यूनमान(128 * b/c) = (128*b) mod c
 * MSx_P3[19:0] = c
 *
 * MS[6,7] are पूर्णांकeger (P1) भागide only, P1 = भागide value,
 * P2 and P3 are not applicable
 *
 * क्रम 150MHz < fOUT <= 160MHz:
 *
 * MSx_P1 = 0, MSx_P2 = 0, MSx_P3 = 1, MSx_INT = 1, MSx_DIVBY4 = 11b
 */
अटल पूर्णांक _si5351_msynth_reparent(काष्ठा si5351_driver_data *drvdata,
				   पूर्णांक num, क्रमागत si5351_multisynth_src parent)
अणु
	अगर (parent == SI5351_MULTISYNTH_SRC_DEFAULT)
		वापस 0;

	अगर (num > 8)
		वापस -EINVAL;

	si5351_set_bits(drvdata, SI5351_CLK0_CTRL + num, SI5351_CLK_PLL_SELECT,
			(parent == SI5351_MULTISYNTH_SRC_VCO0) ? 0 :
			SI5351_CLK_PLL_SELECT);
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर si5351_msynth_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	u8 val;

	val = si5351_reg_पढ़ो(hwdata->drvdata, SI5351_CLK0_CTRL + hwdata->num);

	वापस (val & SI5351_CLK_PLL_SELECT) ? 1 : 0;
पूर्ण

अटल पूर्णांक si5351_msynth_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);

	वापस _si5351_msynth_reparent(hwdata->drvdata, hwdata->num,
			       (index == 0) ? SI5351_MULTISYNTH_SRC_VCO0 :
			       SI5351_MULTISYNTH_SRC_VCO1);
पूर्ण

अटल अचिन्हित दीर्घ si5351_msynth_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	u8 reg = si5351_msynth_params_address(hwdata->num);
	अचिन्हित दीर्घ दीर्घ rate;
	अचिन्हित दीर्घ m;

	अगर (!hwdata->params.valid)
		si5351_पढ़ो_parameters(hwdata->drvdata, reg, &hwdata->params);

	/*
	 * multisync0-5: fOUT = (128 * P3 * fIN) / (P1*P3 + P2 + 512*P3)
	 * multisync6-7: fOUT = fIN / P1
	 */
	rate = parent_rate;
	अगर (hwdata->num > 5) अणु
		m = hwdata->params.p1;
	पूर्ण अन्यथा अगर (hwdata->params.p3 == 0) अणु
		वापस parent_rate;
	पूर्ण अन्यथा अगर ((si5351_reg_पढ़ो(hwdata->drvdata, reg + 2) &
		    SI5351_OUTPUT_CLK_DIVBY4) == SI5351_OUTPUT_CLK_DIVBY4) अणु
		m = 4;
	पूर्ण अन्यथा अणु
		rate *= 128 * hwdata->params.p3;
		m = hwdata->params.p1 * hwdata->params.p3;
		m += hwdata->params.p2;
		m += 512 * hwdata->params.p3;
	पूर्ण

	अगर (m == 0)
		वापस 0;
	करो_भाग(rate, m);

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: p1 = %lu, p2 = %lu, p3 = %lu, m = %lu, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw),
		hwdata->params.p1, hwdata->params.p2, hwdata->params.p3,
		m, parent_rate, (अचिन्हित दीर्घ)rate);

	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

अटल दीर्घ si5351_msynth_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	अचिन्हित दीर्घ दीर्घ llपंचांगp;
	अचिन्हित दीर्घ a, b, c;
	पूर्णांक भागby4;

	/* multisync6-7 can only handle freqencies < 150MHz */
	अगर (hwdata->num >= 6 && rate > SI5351_MULTISYNTH67_MAX_FREQ)
		rate = SI5351_MULTISYNTH67_MAX_FREQ;

	/* multisync frequency is 1MHz .. 160MHz */
	अगर (rate > SI5351_MULTISYNTH_MAX_FREQ)
		rate = SI5351_MULTISYNTH_MAX_FREQ;
	अगर (rate < SI5351_MULTISYNTH_MIN_FREQ)
		rate = SI5351_MULTISYNTH_MIN_FREQ;

	भागby4 = 0;
	अगर (rate > SI5351_MULTISYNTH_DIVBY4_FREQ)
		भागby4 = 1;

	/* multisync can set pll */
	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		/*
		 * find largest पूर्णांकeger भागider क्रम max
		 * vco frequency and given target rate
		 */
		अगर (भागby4 == 0) अणु
			llपंचांगp = SI5351_PLL_VCO_MAX;
			करो_भाग(llपंचांगp, rate);
			a = (अचिन्हित दीर्घ)llपंचांगp;
		पूर्ण अन्यथा
			a = 4;

		b = 0;
		c = 1;

		*parent_rate = a * rate;
	पूर्ण अन्यथा अगर (hwdata->num >= 6) अणु
		/* determine the बंदst पूर्णांकeger भागider */
		a = DIV_ROUND_CLOSEST(*parent_rate, rate);
		अगर (a < SI5351_MULTISYNTH_A_MIN)
			a = SI5351_MULTISYNTH_A_MIN;
		अगर (a > SI5351_MULTISYNTH67_A_MAX)
			a = SI5351_MULTISYNTH67_A_MAX;

		b = 0;
		c = 1;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ rfrac, denom;

		/* disable भागby4 */
		अगर (भागby4) अणु
			rate = SI5351_MULTISYNTH_DIVBY4_FREQ;
			भागby4 = 0;
		पूर्ण

		/* determine पूर्णांकeger part of भागider equation */
		a = *parent_rate / rate;
		अगर (a < SI5351_MULTISYNTH_A_MIN)
			a = SI5351_MULTISYNTH_A_MIN;
		अगर (a > SI5351_MULTISYNTH_A_MAX)
			a = SI5351_MULTISYNTH_A_MAX;

		/* find best approximation क्रम b/c = fVCO mod fOUT */
		denom = 1000 * 1000;
		llपंचांगp = (*parent_rate) % rate;
		llपंचांगp *= denom;
		करो_भाग(llपंचांगp, rate);
		rfrac = (अचिन्हित दीर्घ)llपंचांगp;

		b = 0;
		c = 1;
		अगर (rfrac)
			rational_best_approximation(rfrac, denom,
			    SI5351_MULTISYNTH_B_MAX, SI5351_MULTISYNTH_C_MAX,
			    &b, &c);
	पूर्ण

	/* recalculate rate by fOUT = fIN / (a + b/c) */
	llपंचांगp  = *parent_rate;
	llपंचांगp *= c;
	करो_भाग(llपंचांगp, a * c + b);
	rate  = (अचिन्हित दीर्घ)llपंचांगp;

	/* calculate parameters */
	अगर (भागby4) अणु
		hwdata->params.p3 = 1;
		hwdata->params.p2 = 0;
		hwdata->params.p1 = 0;
	पूर्ण अन्यथा अगर (hwdata->num >= 6) अणु
		hwdata->params.p3 = 0;
		hwdata->params.p2 = 0;
		hwdata->params.p1 = a;
	पूर्ण अन्यथा अणु
		hwdata->params.p3  = c;
		hwdata->params.p2  = (128 * b) % c;
		hwdata->params.p1  = 128 * a;
		hwdata->params.p1 += (128 * b / c);
		hwdata->params.p1 -= 512;
	पूर्ण

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: a = %lu, b = %lu, c = %lu, divby4 = %d, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw), a, b, c, भागby4,
		*parent_rate, rate);

	वापस rate;
पूर्ण

अटल पूर्णांक si5351_msynth_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	u8 reg = si5351_msynth_params_address(hwdata->num);
	पूर्णांक भागby4 = 0;

	/* ग_लिखो multisynth parameters */
	si5351_ग_लिखो_parameters(hwdata->drvdata, reg, &hwdata->params);

	अगर (rate > SI5351_MULTISYNTH_DIVBY4_FREQ)
		भागby4 = 1;

	/* enable/disable पूर्णांकeger mode and भागby4 on multisynth0-5 */
	अगर (hwdata->num < 6) अणु
		si5351_set_bits(hwdata->drvdata, reg + 2,
				SI5351_OUTPUT_CLK_DIVBY4,
				(भागby4) ? SI5351_OUTPUT_CLK_DIVBY4 : 0);
		si5351_set_bits(hwdata->drvdata, SI5351_CLK0_CTRL + hwdata->num,
			SI5351_CLK_INTEGER_MODE,
			(hwdata->params.p2 == 0) ? SI5351_CLK_INTEGER_MODE : 0);
	पूर्ण

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: p1 = %lu, p2 = %lu, p3 = %lu, divby4 = %d, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw),
		hwdata->params.p1, hwdata->params.p2, hwdata->params.p3,
		भागby4, parent_rate, rate);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops si5351_msynth_ops = अणु
	.set_parent = si5351_msynth_set_parent,
	.get_parent = si5351_msynth_get_parent,
	.recalc_rate = si5351_msynth_recalc_rate,
	.round_rate = si5351_msynth_round_rate,
	.set_rate = si5351_msynth_set_rate,
पूर्ण;

/*
 * Si5351 clkout भागider
 */
अटल पूर्णांक _si5351_clkout_reparent(काष्ठा si5351_driver_data *drvdata,
				   पूर्णांक num, क्रमागत si5351_clkout_src parent)
अणु
	u8 val;

	अगर (num > 8)
		वापस -EINVAL;

	चयन (parent) अणु
	हाल SI5351_CLKOUT_SRC_MSYNTH_N:
		val = SI5351_CLK_INPUT_MULTISYNTH_N;
		अवरोध;
	हाल SI5351_CLKOUT_SRC_MSYNTH_0_4:
		/* clk0/clk4 can only connect to its own multisync */
		अगर (num == 0 || num == 4)
			val = SI5351_CLK_INPUT_MULTISYNTH_N;
		अन्यथा
			val = SI5351_CLK_INPUT_MULTISYNTH_0_4;
		अवरोध;
	हाल SI5351_CLKOUT_SRC_XTAL:
		val = SI5351_CLK_INPUT_XTAL;
		अवरोध;
	हाल SI5351_CLKOUT_SRC_CLKIN:
		अगर (drvdata->variant != SI5351_VARIANT_C)
			वापस -EINVAL;

		val = SI5351_CLK_INPUT_CLKIN;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	si5351_set_bits(drvdata, SI5351_CLK0_CTRL + num,
			SI5351_CLK_INPUT_MASK, val);
	वापस 0;
पूर्ण

अटल पूर्णांक _si5351_clkout_set_drive_strength(
	काष्ठा si5351_driver_data *drvdata, पूर्णांक num,
	क्रमागत si5351_drive_strength drive)
अणु
	u8 mask;

	अगर (num > 8)
		वापस -EINVAL;

	चयन (drive) अणु
	हाल SI5351_DRIVE_2MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_2MA;
		अवरोध;
	हाल SI5351_DRIVE_4MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_4MA;
		अवरोध;
	हाल SI5351_DRIVE_6MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_6MA;
		अवरोध;
	हाल SI5351_DRIVE_8MA:
		mask = SI5351_CLK_DRIVE_STRENGTH_8MA;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	si5351_set_bits(drvdata, SI5351_CLK0_CTRL + num,
			SI5351_CLK_DRIVE_STRENGTH_MASK, mask);
	वापस 0;
पूर्ण

अटल पूर्णांक _si5351_clkout_set_disable_state(
	काष्ठा si5351_driver_data *drvdata, पूर्णांक num,
	क्रमागत si5351_disable_state state)
अणु
	u8 reg = (num < 4) ? SI5351_CLK3_0_DISABLE_STATE :
		SI5351_CLK7_4_DISABLE_STATE;
	u8 shअगरt = (num < 4) ? (2 * num) : (2 * (num-4));
	u8 mask = SI5351_CLK_DISABLE_STATE_MASK << shअगरt;
	u8 val;

	अगर (num > 8)
		वापस -EINVAL;

	चयन (state) अणु
	हाल SI5351_DISABLE_LOW:
		val = SI5351_CLK_DISABLE_STATE_LOW;
		अवरोध;
	हाल SI5351_DISABLE_HIGH:
		val = SI5351_CLK_DISABLE_STATE_HIGH;
		अवरोध;
	हाल SI5351_DISABLE_FLOATING:
		val = SI5351_CLK_DISABLE_STATE_FLOAT;
		अवरोध;
	हाल SI5351_DISABLE_NEVER:
		val = SI5351_CLK_DISABLE_STATE_NEVER;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	si5351_set_bits(drvdata, reg, mask, val << shअगरt);

	वापस 0;
पूर्ण

अटल व्योम _si5351_clkout_reset_pll(काष्ठा si5351_driver_data *drvdata, पूर्णांक num)
अणु
	u8 val = si5351_reg_पढ़ो(drvdata, SI5351_CLK0_CTRL + num);
	u8 mask = val & SI5351_CLK_PLL_SELECT ? SI5351_PLL_RESET_B :
						       SI5351_PLL_RESET_A;
	अचिन्हित पूर्णांक v;
	पूर्णांक err;

	चयन (val & SI5351_CLK_INPUT_MASK) अणु
	हाल SI5351_CLK_INPUT_XTAL:
	हाल SI5351_CLK_INPUT_CLKIN:
		वापस;  /* pll not used, no need to reset */
	पूर्ण

	si5351_reg_ग_लिखो(drvdata, SI5351_PLL_RESET, mask);

	err = regmap_पढ़ो_poll_समयout(drvdata->regmap, SI5351_PLL_RESET, v,
				 !(v & mask), 0, 20000);
	अगर (err < 0)
		dev_err(&drvdata->client->dev, "Reset bit didn't clear\n");

	dev_dbg(&drvdata->client->dev, "%s - %s: pll = %d\n",
		__func__, clk_hw_get_name(&drvdata->clkout[num].hw),
		(val & SI5351_CLK_PLL_SELECT) ? 1 : 0);
पूर्ण

अटल पूर्णांक si5351_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	काष्ठा si5351_platक्रमm_data *pdata =
		hwdata->drvdata->client->dev.platक्रमm_data;

	si5351_set_bits(hwdata->drvdata, SI5351_CLK0_CTRL + hwdata->num,
			SI5351_CLK_POWERDOWN, 0);

	/*
	 * Do a pll soft reset on the parent pll -- needed to get a
	 * deterministic phase relationship between the output घड़ीs.
	 */
	अगर (pdata->clkout[hwdata->num].pll_reset)
		_si5351_clkout_reset_pll(hwdata->drvdata, hwdata->num);

	si5351_set_bits(hwdata->drvdata, SI5351_OUTPUT_ENABLE_CTRL,
			(1 << hwdata->num), 0);
	वापस 0;
पूर्ण

अटल व्योम si5351_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);

	si5351_set_bits(hwdata->drvdata, SI5351_CLK0_CTRL + hwdata->num,
			SI5351_CLK_POWERDOWN, SI5351_CLK_POWERDOWN);
	si5351_set_bits(hwdata->drvdata, SI5351_OUTPUT_ENABLE_CTRL,
			(1 << hwdata->num), (1 << hwdata->num));
पूर्ण

अटल u8 si5351_clkout_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	पूर्णांक index = 0;
	अचिन्हित अक्षर val;

	val = si5351_reg_पढ़ो(hwdata->drvdata, SI5351_CLK0_CTRL + hwdata->num);
	चयन (val & SI5351_CLK_INPUT_MASK) अणु
	हाल SI5351_CLK_INPUT_MULTISYNTH_N:
		index = 0;
		अवरोध;
	हाल SI5351_CLK_INPUT_MULTISYNTH_0_4:
		index = 1;
		अवरोध;
	हाल SI5351_CLK_INPUT_XTAL:
		index = 2;
		अवरोध;
	हाल SI5351_CLK_INPUT_CLKIN:
		index = 3;
		अवरोध;
	पूर्ण

	वापस index;
पूर्ण

अटल पूर्णांक si5351_clkout_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	क्रमागत si5351_clkout_src parent = SI5351_CLKOUT_SRC_DEFAULT;

	चयन (index) अणु
	हाल 0:
		parent = SI5351_CLKOUT_SRC_MSYNTH_N;
		अवरोध;
	हाल 1:
		parent = SI5351_CLKOUT_SRC_MSYNTH_0_4;
		अवरोध;
	हाल 2:
		parent = SI5351_CLKOUT_SRC_XTAL;
		अवरोध;
	हाल 3:
		parent = SI5351_CLKOUT_SRC_CLKIN;
		अवरोध;
	पूर्ण

	वापस _si5351_clkout_reparent(hwdata->drvdata, hwdata->num, parent);
पूर्ण

अटल अचिन्हित दीर्घ si5351_clkout_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	अचिन्हित अक्षर reg;
	अचिन्हित अक्षर rभाग;

	अगर (hwdata->num <= 5)
		reg = si5351_msynth_params_address(hwdata->num) + 2;
	अन्यथा
		reg = SI5351_CLK6_7_OUTPUT_DIVIDER;

	rभाग = si5351_reg_पढ़ो(hwdata->drvdata, reg);
	अगर (hwdata->num == 6) अणु
		rभाग &= SI5351_OUTPUT_CLK6_DIV_MASK;
	पूर्ण अन्यथा अणु
		rभाग &= SI5351_OUTPUT_CLK_DIV_MASK;
		rभाग >>= SI5351_OUTPUT_CLK_DIV_SHIFT;
	पूर्ण

	वापस parent_rate >> rभाग;
पूर्ण

अटल दीर्घ si5351_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	अचिन्हित अक्षर rभाग;

	/* clkout6/7 can only handle output freqencies < 150MHz */
	अगर (hwdata->num >= 6 && rate > SI5351_CLKOUT67_MAX_FREQ)
		rate = SI5351_CLKOUT67_MAX_FREQ;

	/* clkout freqency is 8kHz - 160MHz */
	अगर (rate > SI5351_CLKOUT_MAX_FREQ)
		rate = SI5351_CLKOUT_MAX_FREQ;
	अगर (rate < SI5351_CLKOUT_MIN_FREQ)
		rate = SI5351_CLKOUT_MIN_FREQ;

	/* request frequency अगर multisync master */
	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		/* use r भागider क्रम frequencies below 1MHz */
		rभाग = SI5351_OUTPUT_CLK_DIV_1;
		जबतक (rate < SI5351_MULTISYNTH_MIN_FREQ &&
		       rभाग < SI5351_OUTPUT_CLK_DIV_128) अणु
			rभाग += 1;
			rate *= 2;
		पूर्ण
		*parent_rate = rate;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ new_rate, new_err, err;

		/* round to बंदd rभाग */
		rभाग = SI5351_OUTPUT_CLK_DIV_1;
		new_rate = *parent_rate;
		err = असल(new_rate - rate);
		करो अणु
			new_rate >>= 1;
			new_err = असल(new_rate - rate);
			अगर (new_err > err || rभाग == SI5351_OUTPUT_CLK_DIV_128)
				अवरोध;
			rभाग++;
			err = new_err;
		पूर्ण जबतक (1);
	पूर्ण
	rate = *parent_rate >> rभाग;

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: rdiv = %u, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw), (1 << rभाग),
		*parent_rate, rate);

	वापस rate;
पूर्ण

अटल पूर्णांक si5351_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा si5351_hw_data *hwdata =
		container_of(hw, काष्ठा si5351_hw_data, hw);
	अचिन्हित दीर्घ new_rate, new_err, err;
	अचिन्हित अक्षर rभाग;

	/* round to बंदd rभाग */
	rभाग = SI5351_OUTPUT_CLK_DIV_1;
	new_rate = parent_rate;
	err = असल(new_rate - rate);
	करो अणु
		new_rate >>= 1;
		new_err = असल(new_rate - rate);
		अगर (new_err > err || rभाग == SI5351_OUTPUT_CLK_DIV_128)
			अवरोध;
		rभाग++;
		err = new_err;
	पूर्ण जबतक (1);

	/* ग_लिखो output भागider */
	चयन (hwdata->num) अणु
	हाल 6:
		si5351_set_bits(hwdata->drvdata, SI5351_CLK6_7_OUTPUT_DIVIDER,
				SI5351_OUTPUT_CLK6_DIV_MASK, rभाग);
		अवरोध;
	हाल 7:
		si5351_set_bits(hwdata->drvdata, SI5351_CLK6_7_OUTPUT_DIVIDER,
				SI5351_OUTPUT_CLK_DIV_MASK,
				rभाग << SI5351_OUTPUT_CLK_DIV_SHIFT);
		अवरोध;
	शेष:
		si5351_set_bits(hwdata->drvdata,
				si5351_msynth_params_address(hwdata->num) + 2,
				SI5351_OUTPUT_CLK_DIV_MASK,
				rभाग << SI5351_OUTPUT_CLK_DIV_SHIFT);
	पूर्ण

	/* घातerup clkout */
	si5351_set_bits(hwdata->drvdata, SI5351_CLK0_CTRL + hwdata->num,
			SI5351_CLK_POWERDOWN, 0);

	dev_dbg(&hwdata->drvdata->client->dev,
		"%s - %s: rdiv = %u, parent_rate = %lu, rate = %lu\n",
		__func__, clk_hw_get_name(hw), (1 << rभाग),
		parent_rate, rate);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops si5351_clkout_ops = अणु
	.prepare = si5351_clkout_prepare,
	.unprepare = si5351_clkout_unprepare,
	.set_parent = si5351_clkout_set_parent,
	.get_parent = si5351_clkout_get_parent,
	.recalc_rate = si5351_clkout_recalc_rate,
	.round_rate = si5351_clkout_round_rate,
	.set_rate = si5351_clkout_set_rate,
पूर्ण;

/*
 * Si5351 i2c probe and DT
 */
#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id si5351_dt_ids[] = अणु
	अणु .compatible = "silabs,si5351a", .data = (व्योम *)SI5351_VARIANT_A, पूर्ण,
	अणु .compatible = "silabs,si5351a-msop",
					 .data = (व्योम *)SI5351_VARIANT_A3, पूर्ण,
	अणु .compatible = "silabs,si5351b", .data = (व्योम *)SI5351_VARIANT_B, पूर्ण,
	अणु .compatible = "silabs,si5351c", .data = (व्योम *)SI5351_VARIANT_C, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, si5351_dt_ids);

अटल पूर्णांक si5351_dt_parse(काष्ठा i2c_client *client,
			   क्रमागत si5351_variant variant)
अणु
	काष्ठा device_node *child, *np = client->dev.of_node;
	काष्ठा si5351_platक्रमm_data *pdata;
	काष्ठा property *prop;
	स्थिर __be32 *p;
	पूर्णांक num = 0;
	u32 val;

	अगर (np == शून्य)
		वापस 0;

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	/*
	 * property siद_असल,pll-source : <num src>, [<..>]
	 * allow to selectively set pll source
	 */
	of_property_क्रम_each_u32(np, "silabs,pll-source", prop, p, num) अणु
		अगर (num >= 2) अणु
			dev_err(&client->dev,
				"invalid pll %d on pll-source prop\n", num);
			वापस -EINVAL;
		पूर्ण

		p = of_prop_next_u32(prop, p, &val);
		अगर (!p) अणु
			dev_err(&client->dev,
				"missing pll-source for pll %d\n", num);
			वापस -EINVAL;
		पूर्ण

		चयन (val) अणु
		हाल 0:
			pdata->pll_src[num] = SI5351_PLL_SRC_XTAL;
			अवरोध;
		हाल 1:
			अगर (variant != SI5351_VARIANT_C) अणु
				dev_err(&client->dev,
					"invalid parent %d for pll %d\n",
					val, num);
				वापस -EINVAL;
			पूर्ण
			pdata->pll_src[num] = SI5351_PLL_SRC_CLKIN;
			अवरोध;
		शेष:
			dev_err(&client->dev,
				 "invalid parent %d for pll %d\n", val, num);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* per clkout properties */
	क्रम_each_child_of_node(np, child) अणु
		अगर (of_property_पढ़ो_u32(child, "reg", &num)) अणु
			dev_err(&client->dev, "missing reg property of %pOFn\n",
				child);
			जाओ put_child;
		पूर्ण

		अगर (num >= 8 ||
		    (variant == SI5351_VARIANT_A3 && num >= 3)) अणु
			dev_err(&client->dev, "invalid clkout %d\n", num);
			जाओ put_child;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(child, "silabs,multisynth-source",
					  &val)) अणु
			चयन (val) अणु
			हाल 0:
				pdata->clkout[num].multisynth_src =
					SI5351_MULTISYNTH_SRC_VCO0;
				अवरोध;
			हाल 1:
				pdata->clkout[num].multisynth_src =
					SI5351_MULTISYNTH_SRC_VCO1;
				अवरोध;
			शेष:
				dev_err(&client->dev,
					"invalid parent %d for multisynth %d\n",
					val, num);
				जाओ put_child;
			पूर्ण
		पूर्ण

		अगर (!of_property_पढ़ो_u32(child, "silabs,clock-source", &val)) अणु
			चयन (val) अणु
			हाल 0:
				pdata->clkout[num].clkout_src =
					SI5351_CLKOUT_SRC_MSYNTH_N;
				अवरोध;
			हाल 1:
				pdata->clkout[num].clkout_src =
					SI5351_CLKOUT_SRC_MSYNTH_0_4;
				अवरोध;
			हाल 2:
				pdata->clkout[num].clkout_src =
					SI5351_CLKOUT_SRC_XTAL;
				अवरोध;
			हाल 3:
				अगर (variant != SI5351_VARIANT_C) अणु
					dev_err(&client->dev,
						"invalid parent %d for clkout %d\n",
						val, num);
					जाओ put_child;
				पूर्ण
				pdata->clkout[num].clkout_src =
					SI5351_CLKOUT_SRC_CLKIN;
				अवरोध;
			शेष:
				dev_err(&client->dev,
					"invalid parent %d for clkout %d\n",
					val, num);
				जाओ put_child;
			पूर्ण
		पूर्ण

		अगर (!of_property_पढ़ो_u32(child, "silabs,drive-strength",
					  &val)) अणु
			चयन (val) अणु
			हाल SI5351_DRIVE_2MA:
			हाल SI5351_DRIVE_4MA:
			हाल SI5351_DRIVE_6MA:
			हाल SI5351_DRIVE_8MA:
				pdata->clkout[num].drive = val;
				अवरोध;
			शेष:
				dev_err(&client->dev,
					"invalid drive strength %d for clkout %d\n",
					val, num);
				जाओ put_child;
			पूर्ण
		पूर्ण

		अगर (!of_property_पढ़ो_u32(child, "silabs,disable-state",
					  &val)) अणु
			चयन (val) अणु
			हाल 0:
				pdata->clkout[num].disable_state =
					SI5351_DISABLE_LOW;
				अवरोध;
			हाल 1:
				pdata->clkout[num].disable_state =
					SI5351_DISABLE_HIGH;
				अवरोध;
			हाल 2:
				pdata->clkout[num].disable_state =
					SI5351_DISABLE_FLOATING;
				अवरोध;
			हाल 3:
				pdata->clkout[num].disable_state =
					SI5351_DISABLE_NEVER;
				अवरोध;
			शेष:
				dev_err(&client->dev,
					"invalid disable state %d for clkout %d\n",
					val, num);
				जाओ put_child;
			पूर्ण
		पूर्ण

		अगर (!of_property_पढ़ो_u32(child, "clock-frequency", &val))
			pdata->clkout[num].rate = val;

		pdata->clkout[num].pll_master =
			of_property_पढ़ो_bool(child, "silabs,pll-master");

		pdata->clkout[num].pll_reset =
			of_property_पढ़ो_bool(child, "silabs,pll-reset");
	पूर्ण
	client->dev.platक्रमm_data = pdata;

	वापस 0;
put_child:
	of_node_put(child);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा clk_hw *
si53351_of_clk_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	काष्ठा si5351_driver_data *drvdata = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= drvdata->num_clkout) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &drvdata->clkout[idx].hw;
पूर्ण
#अन्यथा
अटल पूर्णांक si5351_dt_parse(काष्ठा i2c_client *client, क्रमागत si5351_variant variant)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा clk_hw *
si53351_of_clk_get(काष्ठा of_phandle_args *clkspec, व्योम *data)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक si5351_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	क्रमागत si5351_variant variant = (क्रमागत si5351_variant)id->driver_data;
	काष्ठा si5351_platक्रमm_data *pdata;
	काष्ठा si5351_driver_data *drvdata;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_names[4];
	u8 num_parents, num_घड़ीs;
	पूर्णांक ret, n;

	ret = si5351_dt_parse(client, variant);
	अगर (ret)
		वापस ret;

	pdata = client->dev.platक्रमm_data;
	अगर (!pdata)
		वापस -EINVAL;

	drvdata = devm_kzalloc(&client->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	i2c_set_clientdata(client, drvdata);
	drvdata->client = client;
	drvdata->variant = variant;
	drvdata->pxtal = devm_clk_get(&client->dev, "xtal");
	drvdata->pclkin = devm_clk_get(&client->dev, "clkin");

	अगर (PTR_ERR(drvdata->pxtal) == -EPROBE_DEFER ||
	    PTR_ERR(drvdata->pclkin) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	/*
	 * Check क्रम valid parent घड़ी: VARIANT_A and VARIANT_B need XTAL,
	 *   VARIANT_C can have CLKIN instead.
	 */
	अगर (IS_ERR(drvdata->pxtal) &&
	    (drvdata->variant != SI5351_VARIANT_C || IS_ERR(drvdata->pclkin))) अणु
		dev_err(&client->dev, "missing parent clock\n");
		वापस -EINVAL;
	पूर्ण

	drvdata->regmap = devm_regmap_init_i2c(client, &si5351_regmap_config);
	अगर (IS_ERR(drvdata->regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		वापस PTR_ERR(drvdata->regmap);
	पूर्ण

	/* Disable पूर्णांकerrupts */
	si5351_reg_ग_लिखो(drvdata, SI5351_INTERRUPT_MASK, 0xf0);
	/* Ensure pll select is on XTAL क्रम Si5351A/B */
	अगर (drvdata->variant != SI5351_VARIANT_C)
		si5351_set_bits(drvdata, SI5351_PLL_INPUT_SOURCE,
				SI5351_PLLA_SOURCE | SI5351_PLLB_SOURCE, 0);

	/* setup घड़ी configuration */
	क्रम (n = 0; n < 2; n++) अणु
		ret = _si5351_pll_reparent(drvdata, n, pdata->pll_src[n]);
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed to reparent pll %d to %d\n",
				n, pdata->pll_src[n]);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (n = 0; n < 8; n++) अणु
		ret = _si5351_msynth_reparent(drvdata, n,
					      pdata->clkout[n].multisynth_src);
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed to reparent multisynth %d to %d\n",
				n, pdata->clkout[n].multisynth_src);
			वापस ret;
		पूर्ण

		ret = _si5351_clkout_reparent(drvdata, n,
					      pdata->clkout[n].clkout_src);
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed to reparent clkout %d to %d\n",
				n, pdata->clkout[n].clkout_src);
			वापस ret;
		पूर्ण

		ret = _si5351_clkout_set_drive_strength(drvdata, n,
							pdata->clkout[n].drive);
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed set drive strength of clkout%d to %d\n",
				n, pdata->clkout[n].drive);
			वापस ret;
		पूर्ण

		ret = _si5351_clkout_set_disable_state(drvdata, n,
						pdata->clkout[n].disable_state);
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed set disable state of clkout%d to %d\n",
				n, pdata->clkout[n].disable_state);
			वापस ret;
		पूर्ण
	पूर्ण

	/* रेजिस्टर xtal input घड़ी gate */
	स_रखो(&init, 0, माप(init));
	init.name = si5351_input_names[0];
	init.ops = &si5351_xtal_ops;
	init.flags = 0;
	अगर (!IS_ERR(drvdata->pxtal)) अणु
		drvdata->pxtal_name = __clk_get_name(drvdata->pxtal);
		init.parent_names = &drvdata->pxtal_name;
		init.num_parents = 1;
	पूर्ण
	drvdata->xtal.init = &init;
	ret = devm_clk_hw_रेजिस्टर(&client->dev, &drvdata->xtal);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to register %s\n", init.name);
		वापस ret;
	पूर्ण

	/* रेजिस्टर clkin input घड़ी gate */
	अगर (drvdata->variant == SI5351_VARIANT_C) अणु
		स_रखो(&init, 0, माप(init));
		init.name = si5351_input_names[1];
		init.ops = &si5351_clkin_ops;
		अगर (!IS_ERR(drvdata->pclkin)) अणु
			drvdata->pclkin_name = __clk_get_name(drvdata->pclkin);
			init.parent_names = &drvdata->pclkin_name;
			init.num_parents = 1;
		पूर्ण
		drvdata->clkin.init = &init;
		ret = devm_clk_hw_रेजिस्टर(&client->dev, &drvdata->clkin);
		अगर (ret) अणु
			dev_err(&client->dev, "unable to register %s\n",
				init.name);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Si5351C allows to mux either xtal or clkin to PLL input */
	num_parents = (drvdata->variant == SI5351_VARIANT_C) ? 2 : 1;
	parent_names[0] = si5351_input_names[0];
	parent_names[1] = si5351_input_names[1];

	/* रेजिस्टर PLLA */
	drvdata->pll[0].num = 0;
	drvdata->pll[0].drvdata = drvdata;
	drvdata->pll[0].hw.init = &init;
	स_रखो(&init, 0, माप(init));
	init.name = si5351_pll_names[0];
	init.ops = &si5351_pll_ops;
	init.flags = 0;
	init.parent_names = parent_names;
	init.num_parents = num_parents;
	ret = devm_clk_hw_रेजिस्टर(&client->dev, &drvdata->pll[0].hw);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to register %s\n", init.name);
		वापस ret;
	पूर्ण

	/* रेजिस्टर PLLB or VXCO (Si5351B) */
	drvdata->pll[1].num = 1;
	drvdata->pll[1].drvdata = drvdata;
	drvdata->pll[1].hw.init = &init;
	स_रखो(&init, 0, माप(init));
	अगर (drvdata->variant == SI5351_VARIANT_B) अणु
		init.name = si5351_pll_names[2];
		init.ops = &si5351_vxco_ops;
		init.flags = 0;
		init.parent_names = शून्य;
		init.num_parents = 0;
	पूर्ण अन्यथा अणु
		init.name = si5351_pll_names[1];
		init.ops = &si5351_pll_ops;
		init.flags = 0;
		init.parent_names = parent_names;
		init.num_parents = num_parents;
	पूर्ण
	ret = devm_clk_hw_रेजिस्टर(&client->dev, &drvdata->pll[1].hw);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to register %s\n", init.name);
		वापस ret;
	पूर्ण

	/* रेजिस्टर clk multisync and clk out भागider */
	num_घड़ीs = (drvdata->variant == SI5351_VARIANT_A3) ? 3 : 8;
	parent_names[0] = si5351_pll_names[0];
	अगर (drvdata->variant == SI5351_VARIANT_B)
		parent_names[1] = si5351_pll_names[2];
	अन्यथा
		parent_names[1] = si5351_pll_names[1];

	drvdata->msynth = devm_kसुस्मृति(&client->dev, num_घड़ीs,
				       माप(*drvdata->msynth), GFP_KERNEL);
	drvdata->clkout = devm_kसुस्मृति(&client->dev, num_घड़ीs,
				       माप(*drvdata->clkout), GFP_KERNEL);
	drvdata->num_clkout = num_घड़ीs;

	अगर (WARN_ON(!drvdata->msynth || !drvdata->clkout)) अणु
		ret = -ENOMEM;
		वापस ret;
	पूर्ण

	क्रम (n = 0; n < num_घड़ीs; n++) अणु
		drvdata->msynth[n].num = n;
		drvdata->msynth[n].drvdata = drvdata;
		drvdata->msynth[n].hw.init = &init;
		स_रखो(&init, 0, माप(init));
		init.name = si5351_msynth_names[n];
		init.ops = &si5351_msynth_ops;
		init.flags = 0;
		अगर (pdata->clkout[n].pll_master)
			init.flags |= CLK_SET_RATE_PARENT;
		init.parent_names = parent_names;
		init.num_parents = 2;
		ret = devm_clk_hw_रेजिस्टर(&client->dev,
					   &drvdata->msynth[n].hw);
		अगर (ret) अणु
			dev_err(&client->dev, "unable to register %s\n",
				init.name);
			वापस ret;
		पूर्ण
	पूर्ण

	num_parents = (drvdata->variant == SI5351_VARIANT_C) ? 4 : 3;
	parent_names[2] = si5351_input_names[0];
	parent_names[3] = si5351_input_names[1];
	क्रम (n = 0; n < num_घड़ीs; n++) अणु
		parent_names[0] = si5351_msynth_names[n];
		parent_names[1] = (n < 4) ? si5351_msynth_names[0] :
			si5351_msynth_names[4];

		drvdata->clkout[n].num = n;
		drvdata->clkout[n].drvdata = drvdata;
		drvdata->clkout[n].hw.init = &init;
		स_रखो(&init, 0, माप(init));
		init.name = si5351_clkout_names[n];
		init.ops = &si5351_clkout_ops;
		init.flags = 0;
		अगर (pdata->clkout[n].clkout_src == SI5351_CLKOUT_SRC_MSYNTH_N)
			init.flags |= CLK_SET_RATE_PARENT;
		init.parent_names = parent_names;
		init.num_parents = num_parents;
		ret = devm_clk_hw_रेजिस्टर(&client->dev,
					   &drvdata->clkout[n].hw);
		अगर (ret) अणु
			dev_err(&client->dev, "unable to register %s\n",
				init.name);
			वापस ret;
		पूर्ण

		/* set initial clkout rate */
		अगर (pdata->clkout[n].rate != 0) अणु
			पूर्णांक ret;
			ret = clk_set_rate(drvdata->clkout[n].hw.clk,
					   pdata->clkout[n].rate);
			अगर (ret != 0) अणु
				dev_err(&client->dev, "Cannot set rate : %d\n",
					ret);
			पूर्ण
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(client->dev.of_node, si53351_of_clk_get,
				     drvdata);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to add clk provider\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si5351_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	of_clk_del_provider(client->dev.of_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si5351_i2c_ids[] = अणु
	अणु "si5351a", SI5351_VARIANT_A पूर्ण,
	अणु "si5351a-msop", SI5351_VARIANT_A3 पूर्ण,
	अणु "si5351b", SI5351_VARIANT_B पूर्ण,
	अणु "si5351c", SI5351_VARIANT_C पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si5351_i2c_ids);

अटल काष्ठा i2c_driver si5351_driver = अणु
	.driver = अणु
		.name = "si5351",
		.of_match_table = of_match_ptr(si5351_dt_ids),
	पूर्ण,
	.probe = si5351_i2c_probe,
	.हटाओ = si5351_i2c_हटाओ,
	.id_table = si5351_i2c_ids,
पूर्ण;
module_i2c_driver(si5351_driver);

MODULE_AUTHOR("Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com");
MODULE_DESCRIPTION("Silicon Labs Si5351A/B/C clock generator driver");
MODULE_LICENSE("GPL");
