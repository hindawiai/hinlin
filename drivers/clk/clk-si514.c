<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Silicon Lअसल Si514 Programmable Oscillator
 *
 * Copyright (C) 2015 Topic Embedded Products
 *
 * Author: Mike Looijmans <mike.looijmans@topic.nl>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* I2C रेजिस्टरs */
#घोषणा SI514_REG_LP		0
#घोषणा SI514_REG_M_FRAC1	5
#घोषणा SI514_REG_M_FRAC2	6
#घोषणा SI514_REG_M_FRAC3	7
#घोषणा SI514_REG_M_INT_FRAC	8
#घोषणा SI514_REG_M_INT		9
#घोषणा SI514_REG_HS_DIV	10
#घोषणा SI514_REG_LS_HS_DIV	11
#घोषणा SI514_REG_OE_STATE	14
#घोषणा SI514_REG_RESET		128
#घोषणा SI514_REG_CONTROL	132

/* Register values */
#घोषणा SI514_RESET_RST		BIT(7)

#घोषणा SI514_CONTROL_FCAL	BIT(0)
#घोषणा SI514_CONTROL_OE	BIT(2)

#घोषणा SI514_MIN_FREQ	    100000U
#घोषणा SI514_MAX_FREQ	 250000000U

#घोषणा FXO		  31980000U

#घोषणा FVCO_MIN	2080000000U
#घोषणा FVCO_MAX	2500000000U

#घोषणा HS_DIV_MAX	1022

काष्ठा clk_si514 अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *i2c_client;
पूर्ण;
#घोषणा to_clk_si514(_hw)	container_of(_hw, काष्ठा clk_si514, hw)

/* Multiplier/भागider settings */
काष्ठा clk_si514_muद_भाग अणु
	u32 m_frac;  /* 29-bit Fractional part of multiplier M */
	u8 m_पूर्णांक; /* Integer part of multiplier M, 65..78 */
	u8 ls_भाग_bits; /* 2nd भागider, as 2^x */
	u16 hs_भाग; /* 1st भागider, must be even and 10<=x<=1022 */
पूर्ण;

/* Enables or disables the output driver */
अटल पूर्णांक si514_enable_output(काष्ठा clk_si514 *data, bool enable)
अणु
	वापस regmap_update_bits(data->regmap, SI514_REG_CONTROL,
		SI514_CONTROL_OE, enable ? SI514_CONTROL_OE : 0);
पूर्ण

अटल पूर्णांक si514_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_si514 *data = to_clk_si514(hw);

	वापस si514_enable_output(data, true);
पूर्ण

अटल व्योम si514_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_si514 *data = to_clk_si514(hw);

	si514_enable_output(data, false);
पूर्ण

अटल पूर्णांक si514_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_si514 *data = to_clk_si514(hw);
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, SI514_REG_CONTROL, &val);
	अगर (err < 0)
		वापस err;

	वापस !!(val & SI514_CONTROL_OE);
पूर्ण

/* Retrieve घड़ी multiplier and भागiders from hardware */
अटल पूर्णांक si514_get_muद_भाग(काष्ठा clk_si514 *data,
	काष्ठा clk_si514_muद_भाग *settings)
अणु
	पूर्णांक err;
	u8 reg[7];

	err = regmap_bulk_पढ़ो(data->regmap, SI514_REG_M_FRAC1,
			reg, ARRAY_SIZE(reg));
	अगर (err)
		वापस err;

	settings->m_frac = reg[0] | reg[1] << 8 | reg[2] << 16 |
			   (reg[3] & 0x1F) << 24;
	settings->m_पूर्णांक = (reg[4] & 0x3f) << 3 | reg[3] >> 5;
	settings->ls_भाग_bits = (reg[6] >> 4) & 0x07;
	settings->hs_भाग = (reg[6] & 0x03) << 8 | reg[5];
	वापस 0;
पूर्ण

अटल पूर्णांक si514_set_muद_भाग(काष्ठा clk_si514 *data,
	काष्ठा clk_si514_muद_भाग *settings)
अणु
	u8 lp;
	u8 reg[7];
	पूर्णांक err;

	/* Calculate LP1/LP2 according to table 13 in the datasheet */
	/* 65.259980246 */
	अगर (settings->m_पूर्णांक < 65 ||
		(settings->m_पूर्णांक == 65 && settings->m_frac <= 139575831))
		lp = 0x22;
	/* 67.859763463 */
	अन्यथा अगर (settings->m_पूर्णांक < 67 ||
		(settings->m_पूर्णांक == 67 && settings->m_frac <= 461581994))
		lp = 0x23;
	/* 72.937624981 */
	अन्यथा अगर (settings->m_पूर्णांक < 72 ||
		(settings->m_पूर्णांक == 72 && settings->m_frac <= 503383578))
		lp = 0x33;
	/* 75.843265046 */
	अन्यथा अगर (settings->m_पूर्णांक < 75 ||
		(settings->m_पूर्णांक == 75 && settings->m_frac <= 452724474))
		lp = 0x34;
	अन्यथा
		lp = 0x44;

	err = regmap_ग_लिखो(data->regmap, SI514_REG_LP, lp);
	अगर (err < 0)
		वापस err;

	reg[0] = settings->m_frac;
	reg[1] = settings->m_frac >> 8;
	reg[2] = settings->m_frac >> 16;
	reg[3] = settings->m_frac >> 24 | settings->m_पूर्णांक << 5;
	reg[4] = settings->m_पूर्णांक >> 3;
	reg[5] = settings->hs_भाग;
	reg[6] = (settings->hs_भाग >> 8) | (settings->ls_भाग_bits << 4);

	err = regmap_bulk_ग_लिखो(data->regmap, SI514_REG_HS_DIV, reg + 5, 2);
	अगर (err < 0)
		वापस err;
	/*
	 * Writing to SI514_REG_M_INT_FRAC triggers the घड़ी change, so that
	 * must be written last
	 */
	वापस regmap_bulk_ग_लिखो(data->regmap, SI514_REG_M_FRAC1, reg, 5);
पूर्ण

/* Calculate भागider settings क्रम a given frequency */
अटल पूर्णांक si514_calc_muद_भाग(काष्ठा clk_si514_muद_भाग *settings,
	अचिन्हित दीर्घ frequency)
अणु
	u64 m;
	u32 ls_freq;
	u32 पंचांगp;
	u8 res;

	अगर ((frequency < SI514_MIN_FREQ) || (frequency > SI514_MAX_FREQ))
		वापस -EINVAL;

	/* Determine the minimum value of LS_DIV and resulting target freq. */
	ls_freq = frequency;
	अगर (frequency >= (FVCO_MIN / HS_DIV_MAX))
		settings->ls_भाग_bits = 0;
	अन्यथा अणु
		res = 1;
		पंचांगp = 2 * HS_DIV_MAX;
		जबतक (पंचांगp <= (HS_DIV_MAX * 32)) अणु
			अगर ((frequency * पंचांगp) >= FVCO_MIN)
				अवरोध;
			++res;
			पंचांगp <<= 1;
		पूर्ण
		settings->ls_भाग_bits = res;
		ls_freq = frequency << res;
	पूर्ण

	/* Determine minimum HS_DIV, round up to even number */
	settings->hs_भाग = DIV_ROUND_UP(FVCO_MIN >> 1, ls_freq) << 1;

	/* M = LS_DIV x HS_DIV x frequency / F_XO (in fixed-poपूर्णांक) */
	m = ((u64)(ls_freq * settings->hs_भाग) << 29) + (FXO / 2);
	करो_भाग(m, FXO);
	settings->m_frac = (u32)m & (BIT(29) - 1);
	settings->m_पूर्णांक = (u32)(m >> 29);

	वापस 0;
पूर्ण

/* Calculate resulting frequency given the रेजिस्टर settings */
अटल अचिन्हित दीर्घ si514_calc_rate(काष्ठा clk_si514_muद_भाग *settings)
अणु
	u64 m = settings->m_frac | ((u64)settings->m_पूर्णांक << 29);
	u32 d = settings->hs_भाग * BIT(settings->ls_भाग_bits);

	वापस ((u32)(((m * FXO) + (FXO / 2)) >> 29)) / d;
पूर्ण

अटल अचिन्हित दीर्घ si514_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_si514 *data = to_clk_si514(hw);
	काष्ठा clk_si514_muद_भाग settings;
	पूर्णांक err;

	err = si514_get_muद_भाग(data, &settings);
	अगर (err) अणु
		dev_err(&data->i2c_client->dev, "unable to retrieve settings\n");
		वापस 0;
	पूर्ण

	वापस si514_calc_rate(&settings);
पूर्ण

अटल दीर्घ si514_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_si514_muद_भाग settings;
	पूर्णांक err;

	अगर (!rate)
		वापस 0;

	err = si514_calc_muद_भाग(&settings, rate);
	अगर (err)
		वापस err;

	वापस si514_calc_rate(&settings);
पूर्ण

/*
 * Update output frequency क्रम big frequency changes (> 1000 ppm).
 * The chip supports <1000ppm changes "on the fly", we haven't implemented
 * that here.
 */
अटल पूर्णांक si514_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_si514 *data = to_clk_si514(hw);
	काष्ठा clk_si514_muद_भाग settings;
	अचिन्हित पूर्णांक old_oe_state;
	पूर्णांक err;

	err = si514_calc_muद_भाग(&settings, rate);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(data->regmap, SI514_REG_CONTROL, &old_oe_state);
	अगर (err)
		वापस err;

	si514_enable_output(data, false);

	err = si514_set_muद_भाग(data, &settings);
	अगर (err < 0)
		वापस err; /* Undefined state now, best to leave disabled */

	/* Trigger calibration */
	err = regmap_ग_लिखो(data->regmap, SI514_REG_CONTROL, SI514_CONTROL_FCAL);
	अगर (err < 0)
		वापस err;

	/* Applying a new frequency can take up to 10ms */
	usleep_range(10000, 12000);

	अगर (old_oe_state & SI514_CONTROL_OE)
		si514_enable_output(data, true);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा clk_ops si514_clk_ops = अणु
	.prepare = si514_prepare,
	.unprepare = si514_unprepare,
	.is_prepared = si514_is_prepared,
	.recalc_rate = si514_recalc_rate,
	.round_rate = si514_round_rate,
	.set_rate = si514_set_rate,
पूर्ण;

अटल bool si514_regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SI514_REG_CONTROL:
	हाल SI514_REG_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool si514_regmap_is_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SI514_REG_LP:
	हाल SI514_REG_M_FRAC1 ... SI514_REG_LS_HS_DIV:
	हाल SI514_REG_OE_STATE:
	हाल SI514_REG_RESET:
	हाल SI514_REG_CONTROL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config si514_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = SI514_REG_CONTROL,
	.ग_लिखोable_reg = si514_regmap_is_ग_लिखोable,
	.अस्थिर_reg = si514_regmap_is_अस्थिर,
पूर्ण;

अटल पूर्णांक si514_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा clk_si514 *data;
	काष्ठा clk_init_data init;
	पूर्णांक err;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	init.ops = &si514_clk_ops;
	init.flags = 0;
	init.num_parents = 0;
	data->hw.init = &init;
	data->i2c_client = client;

	अगर (of_property_पढ़ो_string(client->dev.of_node, "clock-output-names",
			&init.name))
		init.name = client->dev.of_node->name;

	data->regmap = devm_regmap_init_i2c(client, &si514_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	i2c_set_clientdata(client, data);

	err = devm_clk_hw_रेजिस्टर(&client->dev, &data->hw);
	अगर (err) अणु
		dev_err(&client->dev, "clock registration failed\n");
		वापस err;
	पूर्ण
	err = of_clk_add_hw_provider(client->dev.of_node, of_clk_hw_simple_get,
				     &data->hw);
	अगर (err) अणु
		dev_err(&client->dev, "unable to add clk provider\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si514_हटाओ(काष्ठा i2c_client *client)
अणु
	of_clk_del_provider(client->dev.of_node);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si514_id[] = अणु
	अणु "si514", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si514_id);

अटल स्थिर काष्ठा of_device_id clk_si514_of_match[] = अणु
	अणु .compatible = "silabs,si514" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_si514_of_match);

अटल काष्ठा i2c_driver si514_driver = अणु
	.driver = अणु
		.name = "si514",
		.of_match_table = clk_si514_of_match,
	पूर्ण,
	.probe		= si514_probe,
	.हटाओ		= si514_हटाओ,
	.id_table	= si514_id,
पूर्ण;
module_i2c_driver(si514_driver);

MODULE_AUTHOR("Mike Looijmans <mike.looijmans@topic.nl>");
MODULE_DESCRIPTION("Si514 driver");
MODULE_LICENSE("GPL");
