<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CS2000  --  CIRRUS LOGIC Fractional-N Clock Synthesizer & Clock Multiplier
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>

#घोषणा CH_MAX 4
#घोषणा RATIO_REG_SIZE 4

#घोषणा DEVICE_ID	0x1
#घोषणा DEVICE_CTRL	0x2
#घोषणा DEVICE_CFG1	0x3
#घोषणा DEVICE_CFG2	0x4
#घोषणा GLOBAL_CFG	0x5
#घोषणा Ratio_Add(x, nth)	(6 + (x * 4) + (nth))
#घोषणा Ratio_Val(x, nth)	((x >> (24 - (8 * nth))) & 0xFF)
#घोषणा Val_Ratio(x, nth)	((x & 0xFF) << (24 - (8 * nth)))
#घोषणा FUNC_CFG1	0x16
#घोषणा FUNC_CFG2	0x17

/* DEVICE_ID */
#घोषणा REVISION_MASK	(0x7)
#घोषणा REVISION_B2_B3	(0x4)
#घोषणा REVISION_C1	(0x6)

/* DEVICE_CTRL */
#घोषणा PLL_UNLOCK	(1 << 7)
#घोषणा AUXOUTDIS	(1 << 1)
#घोषणा CLKOUTDIS	(1 << 0)

/* DEVICE_CFG1 */
#घोषणा RSEL(x)		(((x) & 0x3) << 3)
#घोषणा RSEL_MASK	RSEL(0x3)
#घोषणा ENDEV1		(0x1)

/* DEVICE_CFG2 */
#घोषणा AUTORMOD	(1 << 3)
#घोषणा LOCKCLK(x)	(((x) & 0x3) << 1)
#घोषणा LOCKCLK_MASK	LOCKCLK(0x3)
#घोषणा FRACNSRC_MASK	(1 << 0)
#घोषणा FRACNSRC_STATIC		(0 << 0)
#घोषणा FRACNSRC_DYNAMIC	(1 << 1)

/* GLOBAL_CFG */
#घोषणा ENDEV2		(0x1)

/* FUNC_CFG1 */
#घोषणा CLKSKIPEN	(1 << 7)
#घोषणा REFCLKDIV(x)	(((x) & 0x3) << 3)
#घोषणा REFCLKDIV_MASK	REFCLKDIV(0x3)

/* FUNC_CFG2 */
#घोषणा LFRATIO_MASK	(1 << 3)
#घोषणा LFRATIO_20_12	(0 << 3)
#घोषणा LFRATIO_12_20	(1 << 3)

#घोषणा CH_SIZE_ERR(ch)		((ch < 0) || (ch >= CH_MAX))
#घोषणा hw_to_priv(_hw)		container_of(_hw, काष्ठा cs2000_priv, hw)
#घोषणा priv_to_client(priv)	(priv->client)
#घोषणा priv_to_dev(priv)	(&(priv_to_client(priv)->dev))

#घोषणा CLK_IN	0
#घोषणा REF_CLK	1
#घोषणा CLK_MAX 2

काष्ठा cs2000_priv अणु
	काष्ठा clk_hw hw;
	काष्ठा i2c_client *client;
	काष्ठा clk *clk_in;
	काष्ठा clk *ref_clk;

	/* suspend/resume */
	अचिन्हित दीर्घ saved_rate;
	अचिन्हित दीर्घ saved_parent_rate;
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs2000_of_match[] = अणु
	अणु .compatible = "cirrus,cs2000-cp", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs2000_of_match);

अटल स्थिर काष्ठा i2c_device_id cs2000_id[] = अणु
	अणु "cs2000-cp", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs2000_id);

#घोषणा cs2000_पढ़ो(priv, addr) \
	i2c_smbus_पढ़ो_byte_data(priv_to_client(priv), addr)
#घोषणा cs2000_ग_लिखो(priv, addr, val) \
	i2c_smbus_ग_लिखो_byte_data(priv_to_client(priv), addr, val)

अटल पूर्णांक cs2000_bset(काष्ठा cs2000_priv *priv, u8 addr, u8 mask, u8 val)
अणु
	s32 data;

	data = cs2000_पढ़ो(priv, addr);
	अगर (data < 0)
		वापस data;

	data &= ~mask;
	data |= (val & mask);

	वापस cs2000_ग_लिखो(priv, addr, data);
पूर्ण

अटल पूर्णांक cs2000_enable_dev_config(काष्ठा cs2000_priv *priv, bool enable)
अणु
	पूर्णांक ret;

	ret = cs2000_bset(priv, DEVICE_CFG1, ENDEV1,
			  enable ? ENDEV1 : 0);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_bset(priv, GLOBAL_CFG,  ENDEV2,
			  enable ? ENDEV2 : 0);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_bset(priv, FUNC_CFG1, CLKSKIPEN,
			  enable ? CLKSKIPEN : 0);
	अगर (ret < 0)
		वापस ret;

	/* FIXME: क्रम Static ratio mode */
	ret = cs2000_bset(priv, FUNC_CFG2, LFRATIO_MASK,
			  LFRATIO_12_20);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक cs2000_clk_in_bound_rate(काष्ठा cs2000_priv *priv,
				    u32 rate_in)
अणु
	u32 val;

	अगर (rate_in >= 32000000 && rate_in < 56000000)
		val = 0x0;
	अन्यथा अगर (rate_in >= 16000000 && rate_in < 28000000)
		val = 0x1;
	अन्यथा अगर (rate_in >= 8000000 && rate_in < 14000000)
		val = 0x2;
	अन्यथा
		वापस -EINVAL;

	वापस cs2000_bset(priv, FUNC_CFG1,
			   REFCLKDIV_MASK,
			   REFCLKDIV(val));
पूर्ण

अटल पूर्णांक cs2000_रुको_pll_lock(काष्ठा cs2000_priv *priv)
अणु
	काष्ठा device *dev = priv_to_dev(priv);
	s32 val;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < 256; i++) अणु
		val = cs2000_पढ़ो(priv, DEVICE_CTRL);
		अगर (val < 0)
			वापस val;
		अगर (!(val & PLL_UNLOCK))
			वापस 0;
		udelay(1);
	पूर्ण

	dev_err(dev, "pll lock failed\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक cs2000_clk_out_enable(काष्ठा cs2000_priv *priv, bool enable)
अणु
	/* enable both AUX_OUT, CLK_OUT */
	वापस cs2000_bset(priv, DEVICE_CTRL,
			   (AUXOUTDIS | CLKOUTDIS),
			   enable ? 0 :
			   (AUXOUTDIS | CLKOUTDIS));
पूर्ण

अटल u32 cs2000_rate_to_ratio(u32 rate_in, u32 rate_out)
अणु
	u64 ratio;

	/*
	 * ratio = rate_out / rate_in * 2^20
	 *
	 * To aव्योम over flow, rate_out is u64.
	 * The result should be u32.
	 */
	ratio = (u64)rate_out << 20;
	करो_भाग(ratio, rate_in);

	वापस ratio;
पूर्ण

अटल अचिन्हित दीर्घ cs2000_ratio_to_rate(u32 ratio, u32 rate_in)
अणु
	u64 rate_out;

	/*
	 * ratio = rate_out / rate_in * 2^20
	 *
	 * To aव्योम over flow, rate_out is u64.
	 * The result should be u32 or अचिन्हित दीर्घ.
	 */

	rate_out = (u64)ratio * rate_in;
	वापस rate_out >> 20;
पूर्ण

अटल पूर्णांक cs2000_ratio_set(काष्ठा cs2000_priv *priv,
			    पूर्णांक ch, u32 rate_in, u32 rate_out)
अणु
	u32 val;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (CH_SIZE_ERR(ch))
		वापस -EINVAL;

	val = cs2000_rate_to_ratio(rate_in, rate_out);
	क्रम (i = 0; i < RATIO_REG_SIZE; i++) अणु
		ret = cs2000_ग_लिखो(priv,
				   Ratio_Add(ch, i),
				   Ratio_Val(val, i));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 cs2000_ratio_get(काष्ठा cs2000_priv *priv, पूर्णांक ch)
अणु
	s32 पंचांगp;
	u32 val;
	अचिन्हित पूर्णांक i;

	val = 0;
	क्रम (i = 0; i < RATIO_REG_SIZE; i++) अणु
		पंचांगp = cs2000_पढ़ो(priv, Ratio_Add(ch, i));
		अगर (पंचांगp < 0)
			वापस 0;

		val |= Val_Ratio(पंचांगp, i);
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक cs2000_ratio_select(काष्ठा cs2000_priv *priv, पूर्णांक ch)
अणु
	पूर्णांक ret;

	अगर (CH_SIZE_ERR(ch))
		वापस -EINVAL;

	/*
	 * FIXME
	 *
	 * this driver supports अटल ratio mode only at this poपूर्णांक.
	 */
	ret = cs2000_bset(priv, DEVICE_CFG1, RSEL_MASK, RSEL(ch));
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_bset(priv, DEVICE_CFG2,
			  (AUTORMOD | LOCKCLK_MASK | FRACNSRC_MASK),
			  (LOCKCLK(ch) | FRACNSRC_STATIC));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ cs2000_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cs2000_priv *priv = hw_to_priv(hw);
	पूर्णांक ch = 0; /* it uses ch0 only at this poपूर्णांक */
	u32 ratio;

	ratio = cs2000_ratio_get(priv, ch);

	वापस cs2000_ratio_to_rate(ratio, parent_rate);
पूर्ण

अटल दीर्घ cs2000_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ *parent_rate)
अणु
	u32 ratio;

	ratio = cs2000_rate_to_ratio(*parent_rate, rate);

	वापस cs2000_ratio_to_rate(ratio, *parent_rate);
पूर्ण

अटल पूर्णांक __cs2000_set_rate(काष्ठा cs2000_priv *priv, पूर्णांक ch,
			     अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)

अणु
	पूर्णांक ret;

	ret = cs2000_clk_in_bound_rate(priv, parent_rate);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_ratio_set(priv, ch, parent_rate, rate);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_ratio_select(priv, ch);
	अगर (ret < 0)
		वापस ret;

	priv->saved_rate	= rate;
	priv->saved_parent_rate	= parent_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक cs2000_set_rate(काष्ठा clk_hw *hw,
			   अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा cs2000_priv *priv = hw_to_priv(hw);
	पूर्णांक ch = 0; /* it uses ch0 only at this poपूर्णांक */

	वापस __cs2000_set_rate(priv, ch, rate, parent_rate);
पूर्ण

अटल पूर्णांक cs2000_set_saved_rate(काष्ठा cs2000_priv *priv)
अणु
	पूर्णांक ch = 0; /* it uses ch0 only at this poपूर्णांक */

	वापस __cs2000_set_rate(priv, ch,
				 priv->saved_rate,
				 priv->saved_parent_rate);
पूर्ण

अटल पूर्णांक cs2000_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा cs2000_priv *priv = hw_to_priv(hw);
	पूर्णांक ret;

	ret = cs2000_enable_dev_config(priv, true);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_clk_out_enable(priv, true);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_रुको_pll_lock(priv);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल व्योम cs2000_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा cs2000_priv *priv = hw_to_priv(hw);

	cs2000_enable_dev_config(priv, false);

	cs2000_clk_out_enable(priv, false);
पूर्ण

अटल u8 cs2000_get_parent(काष्ठा clk_hw *hw)
अणु
	/* always वापस REF_CLK */
	वापस REF_CLK;
पूर्ण

अटल स्थिर काष्ठा clk_ops cs2000_ops = अणु
	.get_parent	= cs2000_get_parent,
	.recalc_rate	= cs2000_recalc_rate,
	.round_rate	= cs2000_round_rate,
	.set_rate	= cs2000_set_rate,
	.prepare	= cs2000_enable,
	.unprepare	= cs2000_disable,
पूर्ण;

अटल पूर्णांक cs2000_clk_get(काष्ठा cs2000_priv *priv)
अणु
	काष्ठा device *dev = priv_to_dev(priv);
	काष्ठा clk *clk_in, *ref_clk;

	clk_in = devm_clk_get(dev, "clk_in");
	/* not yet provided */
	अगर (IS_ERR(clk_in))
		वापस -EPROBE_DEFER;

	ref_clk = devm_clk_get(dev, "ref_clk");
	/* not yet provided */
	अगर (IS_ERR(ref_clk))
		वापस -EPROBE_DEFER;

	priv->clk_in	= clk_in;
	priv->ref_clk	= ref_clk;

	वापस 0;
पूर्ण

अटल पूर्णांक cs2000_clk_रेजिस्टर(काष्ठा cs2000_priv *priv)
अणु
	काष्ठा device *dev = priv_to_dev(priv);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *name = np->name;
	अटल स्थिर अक्षर *parent_names[CLK_MAX];
	पूर्णांक ch = 0; /* it uses ch0 only at this poपूर्णांक */
	पूर्णांक rate;
	पूर्णांक ret;

	of_property_पढ़ो_string(np, "clock-output-names", &name);

	/*
	 * set शेष rate as 1/1.
	 * otherwise .set_rate which setup ratio
	 * is never called अगर user requests 1/1 rate
	 */
	rate = clk_get_rate(priv->ref_clk);
	ret = __cs2000_set_rate(priv, ch, rate, rate);
	अगर (ret < 0)
		वापस ret;

	parent_names[CLK_IN]	= __clk_get_name(priv->clk_in);
	parent_names[REF_CLK]	= __clk_get_name(priv->ref_clk);

	init.name		= name;
	init.ops		= &cs2000_ops;
	init.flags		= CLK_SET_RATE_GATE;
	init.parent_names	= parent_names;
	init.num_parents	= ARRAY_SIZE(parent_names);

	priv->hw.init = &init;

	ret = clk_hw_रेजिस्टर(dev, &priv->hw);
	अगर (ret)
		वापस ret;

	ret = of_clk_add_hw_provider(np, of_clk_hw_simple_get, &priv->hw);
	अगर (ret < 0) अणु
		clk_hw_unरेजिस्टर(&priv->hw);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs2000_version_prपूर्णांक(काष्ठा cs2000_priv *priv)
अणु
	काष्ठा device *dev = priv_to_dev(priv);
	s32 val;
	स्थिर अक्षर *revision;

	val = cs2000_पढ़ो(priv, DEVICE_ID);
	अगर (val < 0)
		वापस val;

	/* CS2000 should be 0x0 */
	अगर (val >> 3)
		वापस -EIO;

	चयन (val & REVISION_MASK) अणु
	हाल REVISION_B2_B3:
		revision = "B2 / B3";
		अवरोध;
	हाल REVISION_C1:
		revision = "C1";
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	dev_info(dev, "revision - %s\n", revision);

	वापस 0;
पूर्ण

अटल पूर्णांक cs2000_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cs2000_priv *priv = i2c_get_clientdata(client);
	काष्ठा device *dev = priv_to_dev(priv);
	काष्ठा device_node *np = dev->of_node;

	of_clk_del_provider(np);

	clk_hw_unरेजिस्टर(&priv->hw);

	वापस 0;
पूर्ण

अटल पूर्णांक cs2000_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs2000_priv *priv;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->client = client;
	i2c_set_clientdata(client, priv);

	ret = cs2000_clk_get(priv);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_clk_रेजिस्टर(priv);
	अगर (ret < 0)
		वापस ret;

	ret = cs2000_version_prपूर्णांक(priv);
	अगर (ret < 0)
		जाओ probe_err;

	वापस 0;

probe_err:
	cs2000_हटाओ(client);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused cs2000_resume(काष्ठा device *dev)
अणु
	काष्ठा cs2000_priv *priv = dev_get_drvdata(dev);

	वापस cs2000_set_saved_rate(priv);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cs2000_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(शून्य, cs2000_resume)
पूर्ण;

अटल काष्ठा i2c_driver cs2000_driver = अणु
	.driver = अणु
		.name = "cs2000-cp",
		.pm	= &cs2000_pm_ops,
		.of_match_table = cs2000_of_match,
	पूर्ण,
	.probe		= cs2000_probe,
	.हटाओ		= cs2000_हटाओ,
	.id_table	= cs2000_id,
पूर्ण;

module_i2c_driver(cs2000_driver);

MODULE_DESCRIPTION("CS2000-CP driver");
MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
MODULE_LICENSE("GPL v2");
