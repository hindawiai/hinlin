<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Silicon Lअसल Si570/Si571 Programmable XO/VCXO
 *
 * Copyright (C) 2010, 2011 Ericsson AB.
 * Copyright (C) 2011 Guenter Roeck.
 * Copyright (C) 2011 - 2021 Xilinx Inc.
 *
 * Author: Guenter Roeck <guenter.roeck@ericsson.com>
 *	   Sथघren Brinkmann <soren.brinkmann@xilinx.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* Si570 रेजिस्टरs */
#घोषणा SI570_REG_HS_N1		7
#घोषणा SI570_REG_N1_RFREQ0	8
#घोषणा SI570_REG_RFREQ1	9
#घोषणा SI570_REG_RFREQ2	10
#घोषणा SI570_REG_RFREQ3	11
#घोषणा SI570_REG_RFREQ4	12
#घोषणा SI570_REG_CONTROL	135
#घोषणा SI570_REG_FREEZE_DCO	137
#घोषणा SI570_DIV_OFFSET_7PPM	6

#घोषणा HS_DIV_SHIFT		5
#घोषणा HS_DIV_MASK		0xe0
#घोषणा HS_DIV_OFFSET		4
#घोषणा N1_6_2_MASK		0x1f
#घोषणा N1_1_0_MASK		0xc0
#घोषणा RFREQ_37_32_MASK	0x3f

#घोषणा SI570_MIN_FREQ		10000000L
#घोषणा SI570_MAX_FREQ		1417500000L
#घोषणा SI598_MAX_FREQ		525000000L

#घोषणा FDCO_MIN		4850000000LL
#घोषणा FDCO_MAX		5670000000LL

#घोषणा SI570_CNTRL_RECALL	(1 << 0)
#घोषणा SI570_CNTRL_FREEZE_M	(1 << 5)
#घोषणा SI570_CNTRL_NEWFREQ	(1 << 6)

#घोषणा SI570_FREEZE_DCO	(1 << 4)

/**
 * काष्ठा clk_si570:
 * @hw:	Clock hw काष्ठा
 * @regmap:	Device's regmap
 * @भाग_offset:	Rgister offset क्रम भागiders
 * @max_freq:	Maximum frequency क्रम this device
 * @fxtal:	Factory xtal frequency
 * @n1:		Clock भागider N1
 * @hs_भाग:	Clock भागider HSDIV
 * @rfreq:	Clock multiplier RFREQ
 * @frequency:	Current output frequency
 * @i2c_client:	I2C client poपूर्णांकer
 */
काष्ठा clk_si570 अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक भाग_offset;
	u64 max_freq;
	u64 fxtal;
	अचिन्हित पूर्णांक n1;
	अचिन्हित पूर्णांक hs_भाग;
	u64 rfreq;
	u64 frequency;
	काष्ठा i2c_client *i2c_client;
पूर्ण;
#घोषणा to_clk_si570(_hw)	container_of(_hw, काष्ठा clk_si570, hw)

क्रमागत clk_si570_variant अणु
	si57x,
	si59x
पूर्ण;

/**
 * si570_get_भागs() - Read घड़ी भागiders from HW
 * @data:	Poपूर्णांकer to काष्ठा clk_si570
 * @rfreq:	Fractional multiplier (output)
 * @n1:		Divider N1 (output)
 * @hs_भाग:	Divider HSDIV (output)
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 *
 * Retrieve घड़ी भागiders and multipliers from the HW.
 */
अटल पूर्णांक si570_get_भागs(काष्ठा clk_si570 *data, u64 *rfreq,
		अचिन्हित पूर्णांक *n1, अचिन्हित पूर्णांक *hs_भाग)
अणु
	पूर्णांक err;
	u8 reg[6];
	u64 पंचांगp;

	err = regmap_bulk_पढ़ो(data->regmap, SI570_REG_HS_N1 + data->भाग_offset,
			reg, ARRAY_SIZE(reg));
	अगर (err)
		वापस err;

	*hs_भाग = ((reg[0] & HS_DIV_MASK) >> HS_DIV_SHIFT) + HS_DIV_OFFSET;
	*n1 = ((reg[0] & N1_6_2_MASK) << 2) + ((reg[1] & N1_1_0_MASK) >> 6) + 1;
	/* Handle invalid हालs */
	अगर (*n1 > 1)
		*n1 &= ~1;

	पंचांगp = reg[1] & RFREQ_37_32_MASK;
	पंचांगp = (पंचांगp << 8) + reg[2];
	पंचांगp = (पंचांगp << 8) + reg[3];
	पंचांगp = (पंचांगp << 8) + reg[4];
	पंचांगp = (पंचांगp << 8) + reg[5];
	*rfreq = पंचांगp;

	वापस 0;
पूर्ण

/**
 * si570_get_शेषs() - Get शेष values
 * @data:	Driver data काष्ठाure
 * @fout:	Factory frequency output
 * @skip_recall:	If true, करोn't recall NVM पूर्णांकo RAM
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक si570_get_शेषs(काष्ठा clk_si570 *data, u64 fout,
			      bool skip_recall)
अणु
	पूर्णांक err;
	u64 fdco;

	अगर (!skip_recall)
		regmap_ग_लिखो(data->regmap, SI570_REG_CONTROL,
			     SI570_CNTRL_RECALL);

	err = si570_get_भागs(data, &data->rfreq, &data->n1, &data->hs_भाग);
	अगर (err)
		वापस err;

	/*
	 * Accept optional precision loss to aव्योम arithmetic overflows.
	 * Acceptable per Silicon Lअसल Application Note AN334.
	 */
	fdco = fout * data->n1 * data->hs_भाग;
	अगर (fdco >= (1LL << 36))
		data->fxtal = भाग64_u64(fdco << 24, data->rfreq >> 4);
	अन्यथा
		data->fxtal = भाग64_u64(fdco << 28, data->rfreq);

	data->frequency = fout;

	वापस 0;
पूर्ण

/**
 * si570_update_rfreq() - Update घड़ी multiplier
 * @data:	Driver data काष्ठाure
 * Passes on regmap_bulk_ग_लिखो() वापस value.
 */
अटल पूर्णांक si570_update_rfreq(काष्ठा clk_si570 *data)
अणु
	u8 reg[5];

	reg[0] = ((data->n1 - 1) << 6) |
		((data->rfreq >> 32) & RFREQ_37_32_MASK);
	reg[1] = (data->rfreq >> 24) & 0xff;
	reg[2] = (data->rfreq >> 16) & 0xff;
	reg[3] = (data->rfreq >> 8) & 0xff;
	reg[4] = data->rfreq & 0xff;

	वापस regmap_bulk_ग_लिखो(data->regmap, SI570_REG_N1_RFREQ0 +
			data->भाग_offset, reg, ARRAY_SIZE(reg));
पूर्ण

/**
 * si570_calc_भागs() - Caluclate घड़ी भागiders
 * @frequency:	Target frequency
 * @data:	Driver data काष्ठाure
 * @out_rfreq:	RFREG fractional multiplier (output)
 * @out_n1:	Clock भागider N1 (output)
 * @out_hs_भाग:	Clock भागider HSDIV (output)
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 *
 * Calculate the घड़ी भागiders (@out_hs_भाग, @out_n1) and घड़ी multiplier
 * (@out_rfreq) क्रम a given target @frequency.
 */
अटल पूर्णांक si570_calc_भागs(अचिन्हित दीर्घ frequency, काष्ठा clk_si570 *data,
		u64 *out_rfreq, अचिन्हित पूर्णांक *out_n1, अचिन्हित पूर्णांक *out_hs_भाग)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक n1, hs_भाग;
	u64 fdco, best_fdco = ULदीर्घ_उच्च;
	अटल स्थिर uपूर्णांक8_t si570_hs_भाग_values[] = अणु 11, 9, 7, 6, 5, 4 पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(si570_hs_भाग_values); i++) अणु
		hs_भाग = si570_hs_भाग_values[i];
		/* Calculate lowest possible value क्रम n1 */
		n1 = भाग_u64(भाग_u64(FDCO_MIN, hs_भाग), frequency);
		अगर (!n1 || (n1 & 1))
			n1++;
		जबतक (n1 <= 128) अणु
			fdco = (u64)frequency * (u64)hs_भाग * (u64)n1;
			अगर (fdco > FDCO_MAX)
				अवरोध;
			अगर (fdco >= FDCO_MIN && fdco < best_fdco) अणु
				*out_n1 = n1;
				*out_hs_भाग = hs_भाग;
				*out_rfreq = भाग64_u64(fdco << 28, data->fxtal);
				best_fdco = fdco;
			पूर्ण
			n1 += (n1 == 1 ? 1 : 2);
		पूर्ण
	पूर्ण

	अगर (best_fdco == ULदीर्घ_उच्च)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ si570_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	पूर्णांक err;
	u64 rfreq, rate;
	अचिन्हित पूर्णांक n1, hs_भाग;
	काष्ठा clk_si570 *data = to_clk_si570(hw);

	err = si570_get_भागs(data, &rfreq, &n1, &hs_भाग);
	अगर (err) अणु
		dev_err(&data->i2c_client->dev, "unable to recalc rate\n");
		वापस data->frequency;
	पूर्ण

	rfreq = भाग_u64(rfreq, hs_भाग * n1);
	rate = (data->fxtal * rfreq) >> 28;

	वापस rate;
पूर्ण

अटल दीर्घ si570_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	पूर्णांक err;
	u64 rfreq;
	अचिन्हित पूर्णांक n1, hs_भाग;
	काष्ठा clk_si570 *data = to_clk_si570(hw);

	अगर (!rate)
		वापस 0;

	अगर (भाग64_u64(असल(rate - data->frequency) * 10000LL,
				data->frequency) < 35) अणु
		rfreq = भाग64_u64((data->rfreq * rate) +
				भाग64_u64(data->frequency, 2), data->frequency);
		n1 = data->n1;
		hs_भाग = data->hs_भाग;

	पूर्ण अन्यथा अणु
		err = si570_calc_भागs(rate, data, &rfreq, &n1, &hs_भाग);
		अगर (err) अणु
			dev_err(&data->i2c_client->dev,
					"unable to round rate\n");
			वापस 0;
		पूर्ण
	पूर्ण

	वापस rate;
पूर्ण

/**
 * si570_set_frequency() - Adjust output frequency
 * @data:	Driver data काष्ठाure
 * @frequency:	Target frequency
 * Returns 0 on success.
 *
 * Update output frequency क्रम big frequency changes (> 3,500 ppm).
 */
अटल पूर्णांक si570_set_frequency(काष्ठा clk_si570 *data, अचिन्हित दीर्घ frequency)
अणु
	पूर्णांक err;

	err = si570_calc_भागs(frequency, data, &data->rfreq, &data->n1,
			&data->hs_भाग);
	अगर (err)
		वापस err;

	/*
	 * The DCO reg should be accessed with a पढ़ो-modअगरy-ग_लिखो operation
	 * per AN334
	 */
	regmap_ग_लिखो(data->regmap, SI570_REG_FREEZE_DCO, SI570_FREEZE_DCO);
	regmap_ग_लिखो(data->regmap, SI570_REG_HS_N1 + data->भाग_offset,
			((data->hs_भाग - HS_DIV_OFFSET) << HS_DIV_SHIFT) |
			(((data->n1 - 1) >> 2) & N1_6_2_MASK));
	si570_update_rfreq(data);
	regmap_ग_लिखो(data->regmap, SI570_REG_FREEZE_DCO, 0);
	regmap_ग_लिखो(data->regmap, SI570_REG_CONTROL, SI570_CNTRL_NEWFREQ);

	/* Applying a new frequency can take up to 10ms */
	usleep_range(10000, 12000);

	वापस 0;
पूर्ण

/**
 * si570_set_frequency_small() - Adjust output frequency
 * @data:	Driver data काष्ठाure
 * @frequency:	Target frequency
 * Returns 0 on success.
 *
 * Update output frequency क्रम small frequency changes (< 3,500 ppm).
 */
अटल पूर्णांक si570_set_frequency_small(काष्ठा clk_si570 *data,
				     अचिन्हित दीर्घ frequency)
अणु
	/*
	 * This is a re-implementation of DIV_ROUND_CLOSEST
	 * using the भाग64_u64 function lieu of letting the compiler
	 * insert EABI calls
	 */
	data->rfreq = भाग64_u64((data->rfreq * frequency) +
			भाग_u64(data->frequency, 2), data->frequency);
	regmap_ग_लिखो(data->regmap, SI570_REG_CONTROL, SI570_CNTRL_FREEZE_M);
	si570_update_rfreq(data);
	regmap_ग_लिखो(data->regmap, SI570_REG_CONTROL, 0);

	/* Applying a new frequency (small change) can take up to 100us */
	usleep_range(100, 200);

	वापस 0;
पूर्ण

अटल पूर्णांक si570_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_si570 *data = to_clk_si570(hw);
	काष्ठा i2c_client *client = data->i2c_client;
	पूर्णांक err;

	अगर (rate < SI570_MIN_FREQ || rate > data->max_freq) अणु
		dev_err(&client->dev,
			"requested frequency %lu Hz is out of range\n", rate);
		वापस -EINVAL;
	पूर्ण

	अगर (भाग64_u64(असल(rate - data->frequency) * 10000LL,
				data->frequency) < 35)
		err = si570_set_frequency_small(data, rate);
	अन्यथा
		err = si570_set_frequency(data, rate);

	अगर (err)
		वापस err;

	data->frequency = rate;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops si570_clk_ops = अणु
	.recalc_rate = si570_recalc_rate,
	.round_rate = si570_round_rate,
	.set_rate = si570_set_rate,
पूर्ण;

अटल bool si570_regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SI570_REG_CONTROL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool si570_regmap_is_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SI570_REG_HS_N1 ... (SI570_REG_RFREQ4 + SI570_DIV_OFFSET_7PPM):
	हाल SI570_REG_CONTROL:
	हाल SI570_REG_FREEZE_DCO:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config si570_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = 137,
	.ग_लिखोable_reg = si570_regmap_is_ग_लिखोable,
	.अस्थिर_reg = si570_regmap_is_अस्थिर,
पूर्ण;

अटल पूर्णांक si570_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा clk_si570 *data;
	काष्ठा clk_init_data init;
	u32 initial_fout, factory_fout, stability;
	bool skip_recall;
	पूर्णांक err;
	क्रमागत clk_si570_variant variant = id->driver_data;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	init.ops = &si570_clk_ops;
	init.flags = 0;
	init.num_parents = 0;
	data->hw.init = &init;
	data->i2c_client = client;

	अगर (variant == si57x) अणु
		err = of_property_पढ़ो_u32(client->dev.of_node,
				"temperature-stability", &stability);
		अगर (err) अणु
			dev_err(&client->dev,
				  "'temperature-stability' property missing\n");
			वापस err;
		पूर्ण
		/* adjust रेजिस्टर offsets क्रम 7ppm devices */
		अगर (stability == 7)
			data->भाग_offset = SI570_DIV_OFFSET_7PPM;

		data->max_freq = SI570_MAX_FREQ;
	पूर्ण अन्यथा अणु
		data->max_freq = SI598_MAX_FREQ;
	पूर्ण

	अगर (of_property_पढ़ो_string(client->dev.of_node, "clock-output-names",
			&init.name))
		init.name = client->dev.of_node->name;

	err = of_property_पढ़ो_u32(client->dev.of_node, "factory-fout",
			&factory_fout);
	अगर (err) अणु
		dev_err(&client->dev, "'factory-fout' property missing\n");
		वापस err;
	पूर्ण

	skip_recall = of_property_पढ़ो_bool(client->dev.of_node,
					    "silabs,skip-recall");

	data->regmap = devm_regmap_init_i2c(client, &si570_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	i2c_set_clientdata(client, data);
	err = si570_get_शेषs(data, factory_fout, skip_recall);
	अगर (err)
		वापस err;

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

	/* Read the requested initial output frequency from device tree */
	अगर (!of_property_पढ़ो_u32(client->dev.of_node, "clock-frequency",
				&initial_fout)) अणु
		err = clk_set_rate(data->hw.clk, initial_fout);
		अगर (err) अणु
			of_clk_del_provider(client->dev.of_node);
			वापस err;
		पूर्ण
	पूर्ण

	/* Display a message indicating that we've successfully रेजिस्टरed */
	dev_info(&client->dev, "registered, current frequency %llu Hz\n",
			data->frequency);

	वापस 0;
पूर्ण

अटल पूर्णांक si570_हटाओ(काष्ठा i2c_client *client)
अणु
	of_clk_del_provider(client->dev.of_node);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si570_id[] = अणु
	अणु "si570", si57x पूर्ण,
	अणु "si571", si57x पूर्ण,
	अणु "si598", si59x पूर्ण,
	अणु "si599", si59x पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si570_id);

अटल स्थिर काष्ठा of_device_id clk_si570_of_match[] = अणु
	अणु .compatible = "silabs,si570" पूर्ण,
	अणु .compatible = "silabs,si571" पूर्ण,
	अणु .compatible = "silabs,si598" पूर्ण,
	अणु .compatible = "silabs,si599" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_si570_of_match);

अटल काष्ठा i2c_driver si570_driver = अणु
	.driver = अणु
		.name = "si570",
		.of_match_table = clk_si570_of_match,
	पूर्ण,
	.probe		= si570_probe,
	.हटाओ		= si570_हटाओ,
	.id_table	= si570_id,
पूर्ण;
module_i2c_driver(si570_driver);

MODULE_AUTHOR("Guenter Roeck <guenter.roeck@ericsson.com>");
MODULE_AUTHOR("Soeren Brinkmann <soren.brinkmann@xilinx.com>");
MODULE_DESCRIPTION("Si570 driver");
MODULE_LICENSE("GPL");
