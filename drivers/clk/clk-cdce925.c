<शैली गुरु>
/*
 * Driver क्रम TI Multi PLL CDCE913/925/937/949 घड़ी synthesizer
 *
 * This driver always connects the Y1 to the input घड़ी, Y2/Y3 to PLL1,
 * Y4/Y5 to PLL2, and so on. PLL frequency is set on a first-come-first-serve
 * basis. Clients can directly request any frequency that the chip can
 * deliver using the standard clk framework. In addition, the device can
 * be configured and activated via the devicetree.
 *
 * Copyright (C) 2014, Topic Embedded Products
 * Licenced under GPL
 */
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/gcd.h>

/* Each chip has dअगरferent number of PLLs and outमाला_दो, क्रम example:
 * The CECE925 has 2 PLLs which can be routed through भागiders to 5 outमाला_दो.
 * Model this as 2 PLL घड़ीs which are parents to the outमाला_दो.
 */

क्रमागत अणु
	CDCE913,
	CDCE925,
	CDCE937,
	CDCE949,
पूर्ण;

काष्ठा clk_cdce925_chip_info अणु
	पूर्णांक num_plls;
	पूर्णांक num_outमाला_दो;
पूर्ण;

अटल स्थिर काष्ठा clk_cdce925_chip_info clk_cdce925_chip_info_tbl[] = अणु
	[CDCE913] = अणु .num_plls = 1, .num_outमाला_दो = 3 पूर्ण,
	[CDCE925] = अणु .num_plls = 2, .num_outमाला_दो = 5 पूर्ण,
	[CDCE937] = अणु .num_plls = 3, .num_outमाला_दो = 7 पूर्ण,
	[CDCE949] = अणु .num_plls = 4, .num_outमाला_दो = 9 पूर्ण,
पूर्ण;

#घोषणा MAX_NUMBER_OF_PLLS	4
#घोषणा MAX_NUMBER_OF_OUTPUTS	9

#घोषणा CDCE925_REG_GLOBAL1	0x01
#घोषणा CDCE925_REG_Y1SPIPDIVH	0x02
#घोषणा CDCE925_REG_PDIVL	0x03
#घोषणा CDCE925_REG_XCSEL	0x05
/* PLL parameters start at 0x10, steps of 0x10 */
#घोषणा CDCE925_OFFSET_PLL	0x10
/* Add CDCE925_OFFSET_PLL * (pll) to these रेजिस्टरs beक्रमe sending */
#घोषणा CDCE925_PLL_MUX_OUTPUTS	0x14
#घोषणा CDCE925_PLL_MULDIV	0x18

#घोषणा CDCE925_PLL_FREQUENCY_MIN	 80000000ul
#घोषणा CDCE925_PLL_FREQUENCY_MAX	230000000ul
काष्ठा clk_cdce925_chip;

काष्ठा clk_cdce925_output अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_cdce925_chip *chip;
	u8 index;
	u16 pभाग; /* 1..127 क्रम Y2-Y9; 1..1023 क्रम Y1 */
पूर्ण;
#घोषणा to_clk_cdce925_output(_hw) \
	container_of(_hw, काष्ठा clk_cdce925_output, hw)

काष्ठा clk_cdce925_pll अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_cdce925_chip *chip;
	u8 index;
	u16 m;   /* 1..511 */
	u16 n;   /* 1..4095 */
पूर्ण;
#घोषणा to_clk_cdce925_pll(_hw)	container_of(_hw, काष्ठा clk_cdce925_pll, hw)

काष्ठा clk_cdce925_chip अणु
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *i2c_client;
	स्थिर काष्ठा clk_cdce925_chip_info *chip_info;
	काष्ठा clk_cdce925_pll pll[MAX_NUMBER_OF_PLLS];
	काष्ठा clk_cdce925_output clk[MAX_NUMBER_OF_OUTPUTS];
पूर्ण;

/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** */

अटल अचिन्हित दीर्घ cdce925_pll_calculate_rate(अचिन्हित दीर्घ parent_rate,
	u16 n, u16 m)
अणु
	अगर ((!m || !n) || (m == n))
		वापस parent_rate; /* In bypass mode runs at same frequency */
	वापस mult_frac(parent_rate, (अचिन्हित दीर्घ)n, (अचिन्हित दीर्घ)m);
पूर्ण

अटल अचिन्हित दीर्घ cdce925_pll_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	/* Output frequency of PLL is Fout = (Fin/Pभाग)*(N/M) */
	काष्ठा clk_cdce925_pll *data = to_clk_cdce925_pll(hw);

	वापस cdce925_pll_calculate_rate(parent_rate, data->n, data->m);
पूर्ण

अटल व्योम cdce925_pll_find_rate(अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate, u16 *n, u16 *m)
अणु
	अचिन्हित दीर्घ un;
	अचिन्हित दीर्घ um;
	अचिन्हित दीर्घ g;

	अगर (rate <= parent_rate) अणु
		/* Can always deliver parent_rate in bypass mode */
		rate = parent_rate;
		*n = 0;
		*m = 0;
	पूर्ण अन्यथा अणु
		/* In PLL mode, need to apply min/max range */
		अगर (rate < CDCE925_PLL_FREQUENCY_MIN)
			rate = CDCE925_PLL_FREQUENCY_MIN;
		अन्यथा अगर (rate > CDCE925_PLL_FREQUENCY_MAX)
			rate = CDCE925_PLL_FREQUENCY_MAX;

		g = gcd(rate, parent_rate);
		um = parent_rate / g;
		un = rate / g;
		/* When outside hw range, reduce to fit (rounding errors) */
		जबतक ((un > 4095) || (um > 511)) अणु
			un >>= 1;
			um >>= 1;
		पूर्ण
		अगर (un == 0)
			un = 1;
		अगर (um == 0)
			um = 1;

		*n = un;
		*m = um;
	पूर्ण
पूर्ण

अटल दीर्घ cdce925_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	u16 n, m;

	cdce925_pll_find_rate(rate, *parent_rate, &n, &m);
	वापस (दीर्घ)cdce925_pll_calculate_rate(*parent_rate, n, m);
पूर्ण

अटल पूर्णांक cdce925_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_cdce925_pll *data = to_clk_cdce925_pll(hw);

	अगर (!rate || (rate == parent_rate)) अणु
		data->m = 0; /* Bypass mode */
		data->n = 0;
		वापस 0;
	पूर्ण

	अगर ((rate < CDCE925_PLL_FREQUENCY_MIN) ||
		(rate > CDCE925_PLL_FREQUENCY_MAX)) अणु
		pr_debug("%s: rate %lu outside PLL range.\n", __func__, rate);
		वापस -EINVAL;
	पूर्ण

	अगर (rate < parent_rate) अणु
		pr_debug("%s: rate %lu less than parent rate %lu.\n", __func__,
			rate, parent_rate);
		वापस -EINVAL;
	पूर्ण

	cdce925_pll_find_rate(rate, parent_rate, &data->n, &data->m);
	वापस 0;
पूर्ण


/* calculate p = max(0, 4 - पूर्णांक(log2 (n/m))) */
अटल u8 cdce925_pll_calc_p(u16 n, u16 m)
अणु
	u8 p;
	u16 r = n / m;

	अगर (r >= 16)
		वापस 0;
	p = 4;
	जबतक (r > 1) अणु
		r >>= 1;
		--p;
	पूर्ण
	वापस p;
पूर्ण

/* Returns VCO range bits क्रम VCO1_0_RANGE */
अटल u8 cdce925_pll_calc_range_bits(काष्ठा clk_hw *hw, u16 n, u16 m)
अणु
	काष्ठा clk *parent = clk_get_parent(hw->clk);
	अचिन्हित दीर्घ rate = clk_get_rate(parent);

	rate = mult_frac(rate, (अचिन्हित दीर्घ)n, (अचिन्हित दीर्घ)m);
	अगर (rate >= 175000000)
		वापस 0x3;
	अगर (rate >= 150000000)
		वापस 0x02;
	अगर (rate >= 125000000)
		वापस 0x01;
	वापस 0x00;
पूर्ण

/* I2C घड़ी, hence everything must happen in (un)prepare because this
 * may sleep */
अटल पूर्णांक cdce925_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_cdce925_pll *data = to_clk_cdce925_pll(hw);
	u16 n = data->n;
	u16 m = data->m;
	u16 r;
	u8 q;
	u8 p;
	u16 nn;
	u8 pll[4]; /* Bits are spपढ़ो out over 4 byte रेजिस्टरs */
	u8 reg_ofs = data->index * CDCE925_OFFSET_PLL;
	अचिन्हित i;

	अगर ((!m || !n) || (m == n)) अणु
		/* Set PLL mux to bypass mode, leave the rest as is */
		regmap_update_bits(data->chip->regmap,
			reg_ofs + CDCE925_PLL_MUX_OUTPUTS, 0x80, 0x80);
	पूर्ण अन्यथा अणु
		/* According to data sheet: */
		/* p = max(0, 4 - पूर्णांक(log2 (n/m))) */
		p = cdce925_pll_calc_p(n, m);
		/* nn = n * 2^p */
		nn = n * BIT(p);
		/* q = पूर्णांक(nn/m) */
		q = nn / m;
		अगर ((q < 16) || (q > 63)) अणु
			pr_debug("%s invalid q=%d\n", __func__, q);
			वापस -EINVAL;
		पूर्ण
		r = nn - (m*q);
		अगर (r > 511) अणु
			pr_debug("%s invalid r=%d\n", __func__, r);
			वापस -EINVAL;
		पूर्ण
		pr_debug("%s n=%d m=%d p=%d q=%d r=%d\n", __func__,
			n, m, p, q, r);
		/* encode पूर्णांकo रेजिस्टर bits */
		pll[0] = n >> 4;
		pll[1] = ((n & 0x0F) << 4) | ((r >> 5) & 0x0F);
		pll[2] = ((r & 0x1F) << 3) | ((q >> 3) & 0x07);
		pll[3] = ((q & 0x07) << 5) | (p << 2) |
				cdce925_pll_calc_range_bits(hw, n, m);
		/* Write to रेजिस्टरs */
		क्रम (i = 0; i < ARRAY_SIZE(pll); ++i)
			regmap_ग_लिखो(data->chip->regmap,
				reg_ofs + CDCE925_PLL_MULDIV + i, pll[i]);
		/* Enable PLL */
		regmap_update_bits(data->chip->regmap,
			reg_ofs + CDCE925_PLL_MUX_OUTPUTS, 0x80, 0x00);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdce925_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_cdce925_pll *data = to_clk_cdce925_pll(hw);
	u8 reg_ofs = data->index * CDCE925_OFFSET_PLL;

	regmap_update_bits(data->chip->regmap,
			reg_ofs + CDCE925_PLL_MUX_OUTPUTS, 0x80, 0x80);
पूर्ण

अटल स्थिर काष्ठा clk_ops cdce925_pll_ops = अणु
	.prepare = cdce925_pll_prepare,
	.unprepare = cdce925_pll_unprepare,
	.recalc_rate = cdce925_pll_recalc_rate,
	.round_rate = cdce925_pll_round_rate,
	.set_rate = cdce925_pll_set_rate,
पूर्ण;


अटल व्योम cdce925_clk_set_pभाग(काष्ठा clk_cdce925_output *data, u16 pभाग)
अणु
	चयन (data->index) अणु
	हाल 0:
		regmap_update_bits(data->chip->regmap,
			CDCE925_REG_Y1SPIPDIVH,
			0x03, (pभाग >> 8) & 0x03);
		regmap_ग_लिखो(data->chip->regmap, 0x03, pभाग & 0xFF);
		अवरोध;
	हाल 1:
		regmap_update_bits(data->chip->regmap, 0x16, 0x7F, pभाग);
		अवरोध;
	हाल 2:
		regmap_update_bits(data->chip->regmap, 0x17, 0x7F, pभाग);
		अवरोध;
	हाल 3:
		regmap_update_bits(data->chip->regmap, 0x26, 0x7F, pभाग);
		अवरोध;
	हाल 4:
		regmap_update_bits(data->chip->regmap, 0x27, 0x7F, pभाग);
		अवरोध;
	हाल 5:
		regmap_update_bits(data->chip->regmap, 0x36, 0x7F, pभाग);
		अवरोध;
	हाल 6:
		regmap_update_bits(data->chip->regmap, 0x37, 0x7F, pभाग);
		अवरोध;
	हाल 7:
		regmap_update_bits(data->chip->regmap, 0x46, 0x7F, pभाग);
		अवरोध;
	हाल 8:
		regmap_update_bits(data->chip->regmap, 0x47, 0x7F, pभाग);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम cdce925_clk_activate(काष्ठा clk_cdce925_output *data)
अणु
	चयन (data->index) अणु
	हाल 0:
		regmap_update_bits(data->chip->regmap,
			CDCE925_REG_Y1SPIPDIVH, 0x0c, 0x0c);
		अवरोध;
	हाल 1:
	हाल 2:
		regmap_update_bits(data->chip->regmap, 0x14, 0x03, 0x03);
		अवरोध;
	हाल 3:
	हाल 4:
		regmap_update_bits(data->chip->regmap, 0x24, 0x03, 0x03);
		अवरोध;
	हाल 5:
	हाल 6:
		regmap_update_bits(data->chip->regmap, 0x34, 0x03, 0x03);
		अवरोध;
	हाल 7:
	हाल 8:
		regmap_update_bits(data->chip->regmap, 0x44, 0x03, 0x03);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक cdce925_clk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_cdce925_output *data = to_clk_cdce925_output(hw);

	cdce925_clk_set_pभाग(data, data->pभाग);
	cdce925_clk_activate(data);
	वापस 0;
पूर्ण

अटल व्योम cdce925_clk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_cdce925_output *data = to_clk_cdce925_output(hw);

	/* Disable घड़ी by setting भागider to "0" */
	cdce925_clk_set_pभाग(data, 0);
पूर्ण

अटल अचिन्हित दीर्घ cdce925_clk_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_cdce925_output *data = to_clk_cdce925_output(hw);

	अगर (data->pभाग)
		वापस parent_rate / data->pभाग;
	वापस 0;
पूर्ण

अटल u16 cdce925_calc_भागider(अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ भागider;

	अगर (!rate)
		वापस 0;
	अगर (rate >= parent_rate)
		वापस 1;

	भागider = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (भागider > 0x7F)
		भागider = 0x7F;

	वापस (u16)भागider;
पूर्ण

अटल अचिन्हित दीर्घ cdce925_clk_best_parent_rate(
	काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate)
अणु
	काष्ठा clk *pll = clk_get_parent(hw->clk);
	काष्ठा clk *root = clk_get_parent(pll);
	अचिन्हित दीर्घ root_rate = clk_get_rate(root);
	अचिन्हित दीर्घ best_rate_error = rate;
	u16 pभाग_min;
	u16 pभाग_max;
	u16 pभाग_best;
	u16 pभाग_now;

	अगर (root_rate % rate == 0)
		वापस root_rate; /* Don't need the PLL, use bypass */

	pभाग_min = (u16)max(1ul, DIV_ROUND_UP(CDCE925_PLL_FREQUENCY_MIN, rate));
	pभाग_max = (u16)min(127ul, CDCE925_PLL_FREQUENCY_MAX / rate);

	अगर (pभाग_min > pभाग_max)
		वापस 0; /* No can करो? */

	pभाग_best = pभाग_min;
	क्रम (pभाग_now = pभाग_min; pभाग_now < pभाग_max; ++pभाग_now) अणु
		अचिन्हित दीर्घ target_rate = rate * pभाग_now;
		दीर्घ pll_rate = clk_round_rate(pll, target_rate);
		अचिन्हित दीर्घ actual_rate;
		अचिन्हित दीर्घ rate_error;

		अगर (pll_rate <= 0)
			जारी;
		actual_rate = pll_rate / pभाग_now;
		rate_error = असल((दीर्घ)actual_rate - (दीर्घ)rate);
		अगर (rate_error < best_rate_error) अणु
			pभाग_best = pभाग_now;
			best_rate_error = rate_error;
		पूर्ण
		/* TODO: Consider PLL frequency based on smaller n/m values
		 * and pick the better one अगर the error is equal */
	पूर्ण

	वापस rate * pभाग_best;
पूर्ण

अटल दीर्घ cdce925_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ l_parent_rate = *parent_rate;
	u16 भागider = cdce925_calc_भागider(rate, l_parent_rate);

	अगर (l_parent_rate / भागider != rate) अणु
		l_parent_rate = cdce925_clk_best_parent_rate(hw, rate);
		भागider = cdce925_calc_भागider(rate, l_parent_rate);
		*parent_rate = l_parent_rate;
	पूर्ण

	अगर (भागider)
		वापस (दीर्घ)(l_parent_rate / भागider);
	वापस 0;
पूर्ण

अटल पूर्णांक cdce925_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_cdce925_output *data = to_clk_cdce925_output(hw);

	data->pभाग = cdce925_calc_भागider(rate, parent_rate);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops cdce925_clk_ops = अणु
	.prepare = cdce925_clk_prepare,
	.unprepare = cdce925_clk_unprepare,
	.recalc_rate = cdce925_clk_recalc_rate,
	.round_rate = cdce925_clk_round_rate,
	.set_rate = cdce925_clk_set_rate,
पूर्ण;


अटल u16 cdce925_y1_calc_भागider(अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	अचिन्हित दीर्घ भागider;

	अगर (!rate)
		वापस 0;
	अगर (rate >= parent_rate)
		वापस 1;

	भागider = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (भागider > 0x3FF) /* Y1 has 10-bit भागider */
		भागider = 0x3FF;

	वापस (u16)भागider;
पूर्ण

अटल दीर्घ cdce925_clk_y1_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ l_parent_rate = *parent_rate;
	u16 भागider = cdce925_y1_calc_भागider(rate, l_parent_rate);

	अगर (भागider)
		वापस (दीर्घ)(l_parent_rate / भागider);
	वापस 0;
पूर्ण

अटल पूर्णांक cdce925_clk_y1_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_cdce925_output *data = to_clk_cdce925_output(hw);

	data->pभाग = cdce925_y1_calc_भागider(rate, parent_rate);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops cdce925_clk_y1_ops = अणु
	.prepare = cdce925_clk_prepare,
	.unprepare = cdce925_clk_unprepare,
	.recalc_rate = cdce925_clk_recalc_rate,
	.round_rate = cdce925_clk_y1_round_rate,
	.set_rate = cdce925_clk_y1_set_rate,
पूर्ण;

#घोषणा CDCE925_I2C_COMMAND_BLOCK_TRANSFER	0x00
#घोषणा CDCE925_I2C_COMMAND_BYTE_TRANSFER	0x80

अटल पूर्णांक cdce925_regmap_i2c_ग_लिखो(
	व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	पूर्णांक ret;
	u8 reg_data[2];

	अगर (count != 2)
		वापस -ENOTSUPP;

	/* First byte is command code */
	reg_data[0] = CDCE925_I2C_COMMAND_BYTE_TRANSFER | ((u8 *)data)[0];
	reg_data[1] = ((u8 *)data)[1];

	dev_dbg(&i2c->dev, "%s(%zu) %#x %#x\n", __func__, count,
			reg_data[0], reg_data[1]);

	ret = i2c_master_send(i2c, reg_data, count);
	अगर (likely(ret == count))
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक cdce925_regmap_i2c_पढ़ो(व्योम *context,
	   स्थिर व्योम *reg, माप_प्रकार reg_size, व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा i2c_msg xfer[2];
	पूर्णांक ret;
	u8 reg_data[2];

	अगर (reg_size != 1)
		वापस -ENOTSUPP;

	xfer[0].addr = i2c->addr;
	xfer[0].flags = 0;
	xfer[0].buf = reg_data;
	अगर (val_size == 1) अणु
		reg_data[0] =
			CDCE925_I2C_COMMAND_BYTE_TRANSFER | ((u8 *)reg)[0];
		xfer[0].len = 1;
	पूर्ण अन्यथा अणु
		reg_data[0] =
			CDCE925_I2C_COMMAND_BLOCK_TRANSFER | ((u8 *)reg)[0];
		reg_data[1] = val_size;
		xfer[0].len = 2;
	पूर्ण

	xfer[1].addr = i2c->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = val_size;
	xfer[1].buf = val;

	ret = i2c_transfer(i2c->adapter, xfer, 2);
	अगर (likely(ret == 2)) अणु
		dev_dbg(&i2c->dev, "%s(%zu, %zu) %#x %#x\n", __func__,
				reg_size, val_size, reg_data[0], *((u8 *)val));
		वापस 0;
	पूर्ण अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल काष्ठा clk_hw *
of_clk_cdce925_get(काष्ठा of_phandle_args *clkspec, व्योम *_data)
अणु
	काष्ठा clk_cdce925_chip *data = _data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= ARRAY_SIZE(data->clk)) अणु
		pr_err("%s: invalid index %u\n", __func__, idx);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस &data->clk[idx].hw;
पूर्ण

अटल व्योम cdce925_regulator_disable(व्योम *regulator)
अणु
	regulator_disable(regulator);
पूर्ण

अटल पूर्णांक cdce925_regulator_enable(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा regulator *regulator;
	पूर्णांक err;

	regulator = devm_regulator_get(dev, name);
	अगर (IS_ERR(regulator))
		वापस PTR_ERR(regulator);

	err = regulator_enable(regulator);
	अगर (err) अणु
		dev_err(dev, "Failed to enable %s: %d\n", name, err);
		वापस err;
	पूर्ण

	वापस devm_add_action_or_reset(dev, cdce925_regulator_disable,
					regulator);
पूर्ण

/* The CDCE925 uses a funky way to पढ़ो/ग_लिखो रेजिस्टरs. Bulk mode is
 * just weird, so just use the single byte mode exclusively. */
अटल काष्ठा regmap_bus regmap_cdce925_bus = अणु
	.ग_लिखो = cdce925_regmap_i2c_ग_लिखो,
	.पढ़ो = cdce925_regmap_i2c_पढ़ो,
पूर्ण;

अटल पूर्णांक cdce925_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा clk_cdce925_chip *data;
	काष्ठा device_node *node = client->dev.of_node;
	स्थिर अक्षर *parent_name;
	स्थिर अक्षर *pll_clk_name[MAX_NUMBER_OF_PLLS] = अणुशून्य,पूर्ण;
	काष्ठा clk_init_data init;
	u32 value;
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा device_node *np_output;
	अक्षर child_name[6];
	काष्ठा regmap_config config = अणु
		.name = "configuration0",
		.reg_bits = 8,
		.val_bits = 8,
		.cache_type = REGCACHE_RBTREE,
	पूर्ण;

	dev_dbg(&client->dev, "%s\n", __func__);

	err = cdce925_regulator_enable(&client->dev, "vdd");
	अगर (err)
		वापस err;

	err = cdce925_regulator_enable(&client->dev, "vddout");
	अगर (err)
		वापस err;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->i2c_client = client;
	data->chip_info = &clk_cdce925_chip_info_tbl[id->driver_data];
	config.max_रेजिस्टर = CDCE925_OFFSET_PLL +
		data->chip_info->num_plls * 0x10 - 1;
	data->regmap = devm_regmap_init(&client->dev, &regmap_cdce925_bus,
			&client->dev, &config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण
	i2c_set_clientdata(client, data);

	parent_name = of_clk_get_parent_name(node, 0);
	अगर (!parent_name) अणु
		dev_err(&client->dev, "missing parent clock\n");
		वापस -ENODEV;
	पूर्ण
	dev_dbg(&client->dev, "parent is: %s\n", parent_name);

	अगर (of_property_पढ़ो_u32(node, "xtal-load-pf", &value) == 0)
		regmap_ग_लिखो(data->regmap,
			CDCE925_REG_XCSEL, (value << 3) & 0xF8);
	/* PWDN bit */
	regmap_update_bits(data->regmap, CDCE925_REG_GLOBAL1, BIT(4), 0);

	/* Set input source क्रम Y1 to be the XTAL */
	regmap_update_bits(data->regmap, 0x02, BIT(7), 0);

	init.ops = &cdce925_pll_ops;
	init.flags = 0;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	/* Register PLL घड़ीs */
	क्रम (i = 0; i < data->chip_info->num_plls; ++i) अणु
		pll_clk_name[i] = kaप्र_लिखो(GFP_KERNEL, "%pOFn.pll%d",
			client->dev.of_node, i);
		init.name = pll_clk_name[i];
		data->pll[i].chip = data;
		data->pll[i].hw.init = &init;
		data->pll[i].index = i;
		err = devm_clk_hw_रेजिस्टर(&client->dev, &data->pll[i].hw);
		अगर (err) अणु
			dev_err(&client->dev, "Failed register PLL %d\n", i);
			जाओ error;
		पूर्ण
		प्र_लिखो(child_name, "PLL%d", i+1);
		np_output = of_get_child_by_name(node, child_name);
		अगर (!np_output)
			जारी;
		अगर (!of_property_पढ़ो_u32(np_output,
			"clock-frequency", &value)) अणु
			err = clk_set_rate(data->pll[i].hw.clk, value);
			अगर (err)
				dev_err(&client->dev,
					"unable to set PLL frequency %ud\n",
					value);
		पूर्ण
		अगर (!of_property_पढ़ो_u32(np_output,
			"spread-spectrum", &value)) अणु
			u8 flag = of_property_पढ़ो_bool(np_output,
				"spread-spectrum-center") ? 0x80 : 0x00;
			regmap_update_bits(data->regmap,
				0x16 + (i*CDCE925_OFFSET_PLL),
				0x80, flag);
			regmap_update_bits(data->regmap,
				0x12 + (i*CDCE925_OFFSET_PLL),
				0x07, value & 0x07);
		पूर्ण
		of_node_put(np_output);
	पूर्ण

	/* Register output घड़ी Y1 */
	init.ops = &cdce925_clk_y1_ops;
	init.flags = 0;
	init.num_parents = 1;
	init.parent_names = &parent_name; /* Mux Y1 to input */
	init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.Y1", client->dev.of_node);
	data->clk[0].chip = data;
	data->clk[0].hw.init = &init;
	data->clk[0].index = 0;
	data->clk[0].pभाग = 1;
	err = devm_clk_hw_रेजिस्टर(&client->dev, &data->clk[0].hw);
	kमुक्त(init.name); /* घड़ी framework made a copy of the name */
	अगर (err) अणु
		dev_err(&client->dev, "clock registration Y1 failed\n");
		जाओ error;
	पूर्ण

	/* Register output घड़ीs Y2 .. Y5*/
	init.ops = &cdce925_clk_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.num_parents = 1;
	क्रम (i = 1; i < data->chip_info->num_outमाला_दो; ++i) अणु
		init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.Y%d",
			client->dev.of_node, i+1);
		data->clk[i].chip = data;
		data->clk[i].hw.init = &init;
		data->clk[i].index = i;
		data->clk[i].pभाग = 1;
		चयन (i) अणु
		हाल 1:
		हाल 2:
			/* Mux Y2/3 to PLL1 */
			init.parent_names = &pll_clk_name[0];
			अवरोध;
		हाल 3:
		हाल 4:
			/* Mux Y4/5 to PLL2 */
			init.parent_names = &pll_clk_name[1];
			अवरोध;
		हाल 5:
		हाल 6:
			/* Mux Y6/7 to PLL3 */
			init.parent_names = &pll_clk_name[2];
			अवरोध;
		हाल 7:
		हाल 8:
			/* Mux Y8/9 to PLL4 */
			init.parent_names = &pll_clk_name[3];
			अवरोध;
		पूर्ण
		err = devm_clk_hw_रेजिस्टर(&client->dev, &data->clk[i].hw);
		kमुक्त(init.name); /* घड़ी framework made a copy of the name */
		अगर (err) अणु
			dev_err(&client->dev, "clock registration failed\n");
			जाओ error;
		पूर्ण
	पूर्ण

	/* Register the output घड़ीs */
	err = of_clk_add_hw_provider(client->dev.of_node, of_clk_cdce925_get,
				  data);
	अगर (err)
		dev_err(&client->dev, "unable to add OF clock provider\n");

	err = 0;

error:
	क्रम (i = 0; i < data->chip_info->num_plls; ++i)
		/* घड़ी framework made a copy of the name */
		kमुक्त(pll_clk_name[i]);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cdce925_id[] = अणु
	अणु "cdce913", CDCE913 पूर्ण,
	अणु "cdce925", CDCE925 पूर्ण,
	अणु "cdce937", CDCE937 पूर्ण,
	अणु "cdce949", CDCE949 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cdce925_id);

अटल स्थिर काष्ठा of_device_id clk_cdce925_of_match[] = अणु
	अणु .compatible = "ti,cdce913" पूर्ण,
	अणु .compatible = "ti,cdce925" पूर्ण,
	अणु .compatible = "ti,cdce937" पूर्ण,
	अणु .compatible = "ti,cdce949" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_cdce925_of_match);

अटल काष्ठा i2c_driver cdce925_driver = अणु
	.driver = अणु
		.name = "cdce925",
		.of_match_table = of_match_ptr(clk_cdce925_of_match),
	पूर्ण,
	.probe		= cdce925_probe,
	.id_table	= cdce925_id,
पूर्ण;
module_i2c_driver(cdce925_driver);

MODULE_AUTHOR("Mike Looijmans <mike.looijmans@topic.nl>");
MODULE_DESCRIPTION("TI CDCE913/925/937/949 driver");
MODULE_LICENSE("GPL");
