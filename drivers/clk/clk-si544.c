<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Silicon Lअसल Si544 Programmable Oscillator
 * Copyright (C) 2018 Topic Embedded Products
 * Author: Mike Looijmans <mike.looijmans@topic.nl>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* I2C रेजिस्टरs (decimal as in datasheet) */
#घोषणा SI544_REG_CONTROL	7
#घोषणा SI544_REG_OE_STATE	17
#घोषणा SI544_REG_HS_DIV	23
#घोषणा SI544_REG_LS_HS_DIV	24
#घोषणा SI544_REG_FBDIV0	26
#घोषणा SI544_REG_FBDIV8	27
#घोषणा SI544_REG_FBDIV16	28
#घोषणा SI544_REG_FBDIV24	29
#घोषणा SI544_REG_FBDIV32	30
#घोषणा SI544_REG_FBDIV40	31
#घोषणा SI544_REG_FCAL_OVR	69
#घोषणा SI544_REG_ADPLL_DELTA_M0	231
#घोषणा SI544_REG_ADPLL_DELTA_M8	232
#घोषणा SI544_REG_ADPLL_DELTA_M16	233
#घोषणा SI544_REG_PAGE_SELECT	255

/* Register values */
#घोषणा SI544_CONTROL_RESET	BIT(7)
#घोषणा SI544_CONTROL_MS_ICAL2	BIT(3)

#घोषणा SI544_OE_STATE_ODC_OE	BIT(0)

/* Max freq depends on speed grade */
#घोषणा SI544_MIN_FREQ	    200000U

/* Si544 Internal oscilator runs at 55.05 MHz */
#घोषणा FXO		  55050000U

/* VCO range is 10.8 .. 12.1 GHz, max depends on speed grade */
#घोषणा FVCO_MIN       10800000000ULL

#घोषणा HS_DIV_MAX	2046
#घोषणा HS_DIV_MAX_ODD	33

/* Lowest frequency synthesizeable using only the HS भागider */
#घोषणा MIN_HSDIV_FREQ	(FVCO_MIN / HS_DIV_MAX)

/* Range and पूर्णांकerpretation of the adjusपंचांगent value */
#घोषणा DELTA_M_MAX	8161512
#घोषणा DELTA_M_FRAC_NUM	19
#घोषणा DELTA_M_FRAC_DEN	20000

क्रमागत si544_speed_grade अणु
	si544a,
	si544b,
	si544c,
पूर्ण;

काष्ठा clk_si544 अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *i2c_client;
	क्रमागत si544_speed_grade speed_grade;
पूर्ण;
#घोषणा to_clk_si544(_hw)	container_of(_hw, काष्ठा clk_si544, hw)

/**
 * काष्ठा clk_si544_muद_भाग - Multiplier/भागider settings
 * @fb_भाग_frac:	पूर्णांकeger part of feedback भागider (32 bits)
 * @fb_भाग_पूर्णांक:		fractional part of feedback भागider (11 bits)
 * @hs_भाग:		1st भागider, 5..2046, must be even when >33
 * @ls_भाग_bits:	2nd भागider, as 2^x, range 0..5
 *                      If ls_भाग_bits is non-zero, hs_भाग must be even
 * @delta_m:		Frequency shअगरt क्रम small -950..+950 ppm changes, 24 bit
 */
काष्ठा clk_si544_muद_भाग अणु
	u32 fb_भाग_frac;
	u16 fb_भाग_पूर्णांक;
	u16 hs_भाग;
	u8 ls_भाग_bits;
	s32 delta_m;
पूर्ण;

/* Enables or disables the output driver */
अटल पूर्णांक si544_enable_output(काष्ठा clk_si544 *data, bool enable)
अणु
	वापस regmap_update_bits(data->regmap, SI544_REG_OE_STATE,
		SI544_OE_STATE_ODC_OE, enable ? SI544_OE_STATE_ODC_OE : 0);
पूर्ण

अटल पूर्णांक si544_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_si544 *data = to_clk_si544(hw);

	वापस si544_enable_output(data, true);
पूर्ण

अटल व्योम si544_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_si544 *data = to_clk_si544(hw);

	si544_enable_output(data, false);
पूर्ण

अटल पूर्णांक si544_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_si544 *data = to_clk_si544(hw);
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, SI544_REG_OE_STATE, &val);
	अगर (err < 0)
		वापस err;

	वापस !!(val & SI544_OE_STATE_ODC_OE);
पूर्ण

/* Retrieve घड़ी multiplier and भागiders from hardware */
अटल पूर्णांक si544_get_muद_भाग(काष्ठा clk_si544 *data,
	काष्ठा clk_si544_muद_भाग *settings)
अणु
	पूर्णांक err;
	u8 reg[6];

	err = regmap_bulk_पढ़ो(data->regmap, SI544_REG_HS_DIV, reg, 2);
	अगर (err)
		वापस err;

	settings->ls_भाग_bits = (reg[1] >> 4) & 0x07;
	settings->hs_भाग = (reg[1] & 0x07) << 8 | reg[0];

	err = regmap_bulk_पढ़ो(data->regmap, SI544_REG_FBDIV0, reg, 6);
	अगर (err)
		वापस err;

	settings->fb_भाग_पूर्णांक = reg[4] | (reg[5] & 0x07) << 8;
	settings->fb_भाग_frac = reg[0] | reg[1] << 8 | reg[2] << 16 |
				reg[3] << 24;

	err = regmap_bulk_पढ़ो(data->regmap, SI544_REG_ADPLL_DELTA_M0, reg, 3);
	अगर (err)
		वापस err;

	/* Interpret as 24-bit चिन्हित number */
	settings->delta_m = reg[0] << 8 | reg[1] << 16 | reg[2] << 24;
	settings->delta_m >>= 8;

	वापस 0;
पूर्ण

अटल पूर्णांक si544_set_delta_m(काष्ठा clk_si544 *data, s32 delta_m)
अणु
	u8 reg[3];

	reg[0] = delta_m;
	reg[1] = delta_m >> 8;
	reg[2] = delta_m >> 16;

	वापस regmap_bulk_ग_लिखो(data->regmap, SI544_REG_ADPLL_DELTA_M0,
				 reg, 3);
पूर्ण

अटल पूर्णांक si544_set_muद_भाग(काष्ठा clk_si544 *data,
	काष्ठा clk_si544_muद_भाग *settings)
अणु
	पूर्णांक err;
	u8 reg[6];

	reg[0] = settings->hs_भाग;
	reg[1] = settings->hs_भाग >> 8 | settings->ls_भाग_bits << 4;

	err = regmap_bulk_ग_लिखो(data->regmap, SI544_REG_HS_DIV, reg, 2);
	अगर (err < 0)
		वापस err;

	reg[0] = settings->fb_भाग_frac;
	reg[1] = settings->fb_भाग_frac >> 8;
	reg[2] = settings->fb_भाग_frac >> 16;
	reg[3] = settings->fb_भाग_frac >> 24;
	reg[4] = settings->fb_भाग_पूर्णांक;
	reg[5] = settings->fb_भाग_पूर्णांक >> 8;

	/*
	 * Writing to SI544_REG_FBDIV40 triggers the घड़ी change, so that
	 * must be written last
	 */
	वापस regmap_bulk_ग_लिखो(data->regmap, SI544_REG_FBDIV0, reg, 6);
पूर्ण

अटल bool is_valid_frequency(स्थिर काष्ठा clk_si544 *data,
	अचिन्हित दीर्घ frequency)
अणु
	अचिन्हित दीर्घ max_freq = 0;

	अगर (frequency < SI544_MIN_FREQ)
		वापस false;

	चयन (data->speed_grade) अणु
	हाल si544a:
		max_freq = 1500000000;
		अवरोध;
	हाल si544b:
		max_freq = 800000000;
		अवरोध;
	हाल si544c:
		max_freq = 350000000;
		अवरोध;
	पूर्ण

	वापस frequency <= max_freq;
पूर्ण

/* Calculate भागider settings क्रम a given frequency */
अटल पूर्णांक si544_calc_muद_भाग(काष्ठा clk_si544_muद_भाग *settings,
	अचिन्हित दीर्घ frequency)
अणु
	u64 vco;
	u32 ls_freq;
	u32 पंचांगp;
	u8 res;

	/* Determine the minimum value of LS_DIV and resulting target freq. */
	ls_freq = frequency;
	settings->ls_भाग_bits = 0;

	अगर (frequency >= MIN_HSDIV_FREQ) अणु
		settings->ls_भाग_bits = 0;
	पूर्ण अन्यथा अणु
		res = 1;
		पंचांगp = 2 * HS_DIV_MAX;
		जबतक (पंचांगp <= (HS_DIV_MAX * 32)) अणु
			अगर (((u64)frequency * पंचांगp) >= FVCO_MIN)
				अवरोध;
			++res;
			पंचांगp <<= 1;
		पूर्ण
		settings->ls_भाग_bits = res;
		ls_freq = frequency << res;
	पूर्ण

	/* Determine minimum HS_DIV by rounding up */
	vco = FVCO_MIN + ls_freq - 1;
	करो_भाग(vco, ls_freq);
	settings->hs_भाग = vco;

	/* round up to even number when required */
	अगर ((settings->hs_भाग & 1) &&
	    (settings->hs_भाग > HS_DIV_MAX_ODD || settings->ls_भाग_bits))
		++settings->hs_भाग;

	/* Calculate VCO frequency (in 10..12GHz range) */
	vco = (u64)ls_freq * settings->hs_भाग;

	/* Calculate the पूर्णांकeger part of the feedback भागider */
	पंचांगp = करो_भाग(vco, FXO);
	settings->fb_भाग_पूर्णांक = vco;

	/* And the fractional bits using the reमुख्यder */
	vco = (u64)पंचांगp << 32;
	vco += FXO / 2; /* Round to nearest multiple */
	करो_भाग(vco, FXO);
	settings->fb_भाग_frac = vco;

	/* Reset the frequency adjusपंचांगent */
	settings->delta_m = 0;

	वापस 0;
पूर्ण

/* Calculate resulting frequency given the रेजिस्टर settings */
अटल अचिन्हित दीर्घ si544_calc_center_rate(
		स्थिर काष्ठा clk_si544_muद_भाग *settings)
अणु
	u32 d = settings->hs_भाग * BIT(settings->ls_भाग_bits);
	u64 vco;

	/* Calculate VCO from the fractional part */
	vco = (u64)settings->fb_भाग_frac * FXO;
	vco += (FXO / 2);
	vco >>= 32;

	/* Add the पूर्णांकeger part of the VCO frequency */
	vco += (u64)settings->fb_भाग_पूर्णांक * FXO;

	/* Apply भागider to obtain the generated frequency */
	करो_भाग(vco, d);

	वापस vco;
पूर्ण

अटल अचिन्हित दीर्घ si544_calc_rate(स्थिर काष्ठा clk_si544_muद_भाग *settings)
अणु
	अचिन्हित दीर्घ rate = si544_calc_center_rate(settings);
	s64 delta = (s64)rate * (DELTA_M_FRAC_NUM * settings->delta_m);

	/*
	 * The घड़ी adjusपंचांगent is much smaller than 1 Hz, round to the
	 * nearest multiple. Apparently भाग64_s64 rounds towards zero, hence
	 * check the sign and adjust पूर्णांकo the proper direction.
	 */
	अगर (settings->delta_m < 0)
		delta -= ((s64)DELTA_M_MAX * DELTA_M_FRAC_DEN) / 2;
	अन्यथा
		delta += ((s64)DELTA_M_MAX * DELTA_M_FRAC_DEN) / 2;
	delta = भाग64_s64(delta, ((s64)DELTA_M_MAX * DELTA_M_FRAC_DEN));

	वापस rate + delta;
पूर्ण

अटल अचिन्हित दीर्घ si544_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_si544 *data = to_clk_si544(hw);
	काष्ठा clk_si544_muद_भाग settings;
	पूर्णांक err;

	err = si544_get_muद_भाग(data, &settings);
	अगर (err)
		वापस 0;

	वापस si544_calc_rate(&settings);
पूर्ण

अटल दीर्घ si544_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_si544 *data = to_clk_si544(hw);

	अगर (!is_valid_frequency(data, rate))
		वापस -EINVAL;

	/* The accuracy is less than 1 Hz, so any rate is possible */
	वापस rate;
पूर्ण

/* Calculates the maximum "small" change, 950 * rate / 1000000 */
अटल अचिन्हित दीर्घ si544_max_delta(अचिन्हित दीर्घ rate)
अणु
	u64 num = rate;

	num *= DELTA_M_FRAC_NUM;
	करो_भाग(num, DELTA_M_FRAC_DEN);

	वापस num;
पूर्ण

अटल s32 si544_calc_delta(s32 delta, s32 max_delta)
अणु
	s64 n = (s64)delta * DELTA_M_MAX;

	वापस भाग_s64(n, max_delta);
पूर्ण

अटल पूर्णांक si544_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_si544 *data = to_clk_si544(hw);
	काष्ठा clk_si544_muद_भाग settings;
	अचिन्हित दीर्घ center;
	दीर्घ max_delta;
	दीर्घ delta;
	अचिन्हित पूर्णांक old_oe_state;
	पूर्णांक err;

	अगर (!is_valid_frequency(data, rate))
		वापस -EINVAL;

	/* Try using the frequency adjusपंचांगent feature क्रम a <= 950ppm change */
	err = si544_get_muद_भाग(data, &settings);
	अगर (err)
		वापस err;

	center = si544_calc_center_rate(&settings);
	max_delta = si544_max_delta(center);
	delta = rate - center;

	अगर (असल(delta) <= max_delta)
		वापस si544_set_delta_m(data,
					 si544_calc_delta(delta, max_delta));

	/* Too big क्रम the delta adjusपंचांगent, need to reprogram */
	err = si544_calc_muद_भाग(&settings, rate);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(data->regmap, SI544_REG_OE_STATE, &old_oe_state);
	अगर (err)
		वापस err;

	si544_enable_output(data, false);

	/* Allow FCAL क्रम this frequency update */
	err = regmap_ग_लिखो(data->regmap, SI544_REG_FCAL_OVR, 0);
	अगर (err < 0)
		वापस err;

	err = si544_set_delta_m(data, settings.delta_m);
	अगर (err < 0)
		वापस err;

	err = si544_set_muद_भाग(data, &settings);
	अगर (err < 0)
		वापस err; /* Undefined state now, best to leave disabled */

	/* Trigger calibration */
	err = regmap_ग_लिखो(data->regmap, SI544_REG_CONTROL,
			   SI544_CONTROL_MS_ICAL2);
	अगर (err < 0)
		वापस err;

	/* Applying a new frequency can take up to 10ms */
	usleep_range(10000, 12000);

	अगर (old_oe_state & SI544_OE_STATE_ODC_OE)
		si544_enable_output(data, true);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा clk_ops si544_clk_ops = अणु
	.prepare = si544_prepare,
	.unprepare = si544_unprepare,
	.is_prepared = si544_is_prepared,
	.recalc_rate = si544_recalc_rate,
	.round_rate = si544_round_rate,
	.set_rate = si544_set_rate,
पूर्ण;

अटल bool si544_regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SI544_REG_CONTROL:
	हाल SI544_REG_FCAL_OVR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config si544_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = SI544_REG_PAGE_SELECT,
	.अस्थिर_reg = si544_regmap_is_अस्थिर,
पूर्ण;

अटल पूर्णांक si544_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा clk_si544 *data;
	काष्ठा clk_init_data init;
	पूर्णांक err;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	init.ops = &si544_clk_ops;
	init.flags = 0;
	init.num_parents = 0;
	data->hw.init = &init;
	data->i2c_client = client;
	data->speed_grade = id->driver_data;

	अगर (of_property_पढ़ो_string(client->dev.of_node, "clock-output-names",
			&init.name))
		init.name = client->dev.of_node->name;

	data->regmap = devm_regmap_init_i2c(client, &si544_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	i2c_set_clientdata(client, data);

	/* Select page 0, just to be sure, there appear to be no more */
	err = regmap_ग_लिखो(data->regmap, SI544_REG_PAGE_SELECT, 0);
	अगर (err < 0)
		वापस err;

	err = devm_clk_hw_रेजिस्टर(&client->dev, &data->hw);
	अगर (err) अणु
		dev_err(&client->dev, "clock registration failed\n");
		वापस err;
	पूर्ण
	err = devm_of_clk_add_hw_provider(&client->dev, of_clk_hw_simple_get,
					  &data->hw);
	अगर (err) अणु
		dev_err(&client->dev, "unable to add clk provider\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si544_id[] = अणु
	अणु "si544a", si544a पूर्ण,
	अणु "si544b", si544b पूर्ण,
	अणु "si544c", si544c पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si544_id);

अटल स्थिर काष्ठा of_device_id clk_si544_of_match[] = अणु
	अणु .compatible = "silabs,si544a" पूर्ण,
	अणु .compatible = "silabs,si544b" पूर्ण,
	अणु .compatible = "silabs,si544c" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_si544_of_match);

अटल काष्ठा i2c_driver si544_driver = अणु
	.driver = अणु
		.name = "si544",
		.of_match_table = clk_si544_of_match,
	पूर्ण,
	.probe		= si544_probe,
	.id_table	= si544_id,
पूर्ण;
module_i2c_driver(si544_driver);

MODULE_AUTHOR("Mike Looijmans <mike.looijmans@topic.nl>");
MODULE_DESCRIPTION("Si544 driver");
MODULE_LICENSE("GPL");
