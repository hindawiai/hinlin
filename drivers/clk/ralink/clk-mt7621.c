<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Mediatek MT7621 Clock Driver
 * Author: Sergio Paracuellos <sergio.paracuellos@gmail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <dt-bindings/घड़ी/mt7621-clk.h>

/* Configuration रेजिस्टरs */
#घोषणा SYSC_REG_SYSTEM_CONFIG0         0x10
#घोषणा SYSC_REG_SYSTEM_CONFIG1         0x14
#घोषणा SYSC_REG_CLKCFG0		0x2c
#घोषणा SYSC_REG_CLKCFG1		0x30
#घोषणा SYSC_REG_CUR_CLK_STS		0x44
#घोषणा MEMC_REG_CPU_PLL		0x648

#घोषणा XTAL_MODE_SEL_MASK		GENMASK(8, 6)
#घोषणा CPU_CLK_SEL_MASK		GENMASK(31, 30)
#घोषणा CUR_CPU_FDIV_MASK		GENMASK(12, 8)
#घोषणा CUR_CPU_FFRAC_MASK		GENMASK(4, 0)
#घोषणा CPU_PLL_PREDIV_MASK		GENMASK(13, 12)
#घोषणा CPU_PLL_FBDIV_MASK		GENMASK(10, 4)

काष्ठा mt7621_clk_priv अणु
	काष्ठा regmap *sysc;
	काष्ठा regmap *memc;
पूर्ण;

काष्ठा mt7621_clk अणु
	काष्ठा clk_hw hw;
	काष्ठा mt7621_clk_priv *priv;
पूर्ण;

काष्ठा mt7621_fixed_clk अणु
	u8 idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ rate;
	काष्ठा clk_hw *hw;
पूर्ण;

काष्ठा mt7621_gate अणु
	u8 idx;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	काष्ठा mt7621_clk_priv *priv;
	u32 bit_idx;
	काष्ठा clk_hw hw;
पूर्ण;

#घोषणा GATE(_id, _name, _pname, _shअगरt)	\
	अणु					\
		.idx		= _id,		\
		.name		= _name,	\
		.parent_name	= _pname,	\
		.bit_idx	= _shअगरt	\
	पूर्ण

अटल काष्ठा mt7621_gate mt7621_gates[] = अणु
	GATE(MT7621_CLK_HSDMA, "hsdma", "150m", BIT(5)),
	GATE(MT7621_CLK_FE, "fe", "250m", BIT(6)),
	GATE(MT7621_CLK_SP_DIVTX, "sp_divtx", "270m", BIT(7)),
	GATE(MT7621_CLK_TIMER, "timer", "50m", BIT(8)),
	GATE(MT7621_CLK_PCM, "pcm", "270m", BIT(11)),
	GATE(MT7621_CLK_PIO, "pio", "50m", BIT(13)),
	GATE(MT7621_CLK_GDMA, "gdma", "bus", BIT(14)),
	GATE(MT7621_CLK_न_अंकD, "nand", "125m", BIT(15)),
	GATE(MT7621_CLK_I2C, "i2c", "50m", BIT(16)),
	GATE(MT7621_CLK_I2S, "i2s", "270m", BIT(17)),
	GATE(MT7621_CLK_SPI, "spi", "bus", BIT(18)),
	GATE(MT7621_CLK_UART1, "uart1", "50m", BIT(19)),
	GATE(MT7621_CLK_UART2, "uart2", "50m", BIT(20)),
	GATE(MT7621_CLK_UART3, "uart3", "50m", BIT(21)),
	GATE(MT7621_CLK_ETH, "eth", "50m", BIT(23)),
	GATE(MT7621_CLK_PCIE0, "pcie0", "125m", BIT(24)),
	GATE(MT7621_CLK_PCIE1, "pcie1", "125m", BIT(25)),
	GATE(MT7621_CLK_PCIE2, "pcie2", "125m", BIT(26)),
	GATE(MT7621_CLK_CRYPTO, "crypto", "250m", BIT(29)),
	GATE(MT7621_CLK_SHXC, "shxc", "50m", BIT(30))
पूर्ण;

अटल अंतरभूत काष्ठा mt7621_gate *to_mt7621_gate(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mt7621_gate, hw);
पूर्ण

अटल पूर्णांक mt7621_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mt7621_gate *clk_gate = to_mt7621_gate(hw);
	काष्ठा regmap *sysc = clk_gate->priv->sysc;

	वापस regmap_update_bits(sysc, SYSC_REG_CLKCFG1,
				  clk_gate->bit_idx, clk_gate->bit_idx);
पूर्ण

अटल व्योम mt7621_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा mt7621_gate *clk_gate = to_mt7621_gate(hw);
	काष्ठा regmap *sysc = clk_gate->priv->sysc;

	regmap_update_bits(sysc, SYSC_REG_CLKCFG1, clk_gate->bit_idx, 0);
पूर्ण

अटल पूर्णांक mt7621_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा mt7621_gate *clk_gate = to_mt7621_gate(hw);
	काष्ठा regmap *sysc = clk_gate->priv->sysc;
	u32 val;

	अगर (regmap_पढ़ो(sysc, SYSC_REG_CLKCFG1, &val))
		वापस 0;

	वापस val & BIT(clk_gate->bit_idx);
पूर्ण

अटल स्थिर काष्ठा clk_ops mt7621_gate_ops = अणु
	.enable = mt7621_gate_enable,
	.disable = mt7621_gate_disable,
	.is_enabled = mt7621_gate_is_enabled,
पूर्ण;

अटल पूर्णांक mt7621_gate_ops_init(काष्ठा device *dev,
				काष्ठा mt7621_gate *sclk)
अणु
	काष्ठा clk_init_data init = अणु
		/*
		 * Until now no घड़ी driver existed so
		 * these SoC drivers are not prepared
		 * yet क्रम the घड़ी. We करोn't want kernel to
		 * disable anything so we add CLK_IS_CRITICAL
		 * flag here.
		 */
		.flags = CLK_SET_RATE_PARENT | CLK_IS_CRITICAL,
		.num_parents = 1,
		.parent_names = &sclk->parent_name,
		.ops = &mt7621_gate_ops,
		.name = sclk->name,
	पूर्ण;

	sclk->hw.init = &init;
	वापस devm_clk_hw_रेजिस्टर(dev, &sclk->hw);
पूर्ण

अटल पूर्णांक mt7621_रेजिस्टर_gates(काष्ठा device *dev,
				 काष्ठा clk_hw_onecell_data *clk_data,
				 काष्ठा mt7621_clk_priv *priv)
अणु
	काष्ठा clk_hw **hws = clk_data->hws;
	काष्ठा mt7621_gate *sclk;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(mt7621_gates); i++) अणु
		sclk = &mt7621_gates[i];
		sclk->priv = priv;
		ret = mt7621_gate_ops_init(dev, sclk);
		अगर (ret) अणु
			dev_err(dev, "Couldn't register clock %s\n", sclk->name);
			जाओ err_clk_unreg;
		पूर्ण

		hws[sclk->idx] = &sclk->hw;
	पूर्ण

	वापस 0;

err_clk_unreg:
	जबतक (--i >= 0) अणु
		sclk = &mt7621_gates[i];
		clk_hw_unरेजिस्टर(&sclk->hw);
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा FIXED(_id, _name, _rate)		\
	अणु					\
		.idx		= _id,		\
		.name		= _name,	\
		.parent_name	= "xtal",	\
		.rate		= _rate		\
	पूर्ण

अटल काष्ठा mt7621_fixed_clk mt7621_fixed_clks[] = अणु
	FIXED(MT7621_CLK_50M, "50m", 50000000),
	FIXED(MT7621_CLK_125M, "125m", 125000000),
	FIXED(MT7621_CLK_150M, "150m", 150000000),
	FIXED(MT7621_CLK_250M, "250m", 250000000),
	FIXED(MT7621_CLK_270M, "270m", 270000000),
पूर्ण;

अटल पूर्णांक mt7621_रेजिस्टर_fixed_घड़ीs(काष्ठा device *dev,
					काष्ठा clk_hw_onecell_data *clk_data)
अणु
	काष्ठा clk_hw **hws = clk_data->hws;
	काष्ठा mt7621_fixed_clk *sclk;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(mt7621_fixed_clks); i++) अणु
		sclk = &mt7621_fixed_clks[i];
		sclk->hw = clk_hw_रेजिस्टर_fixed_rate(dev, sclk->name,
						      sclk->parent_name, 0,
						      sclk->rate);
		अगर (IS_ERR(sclk->hw)) अणु
			dev_err(dev, "Couldn't register clock %s\n", sclk->name);
			ret = PTR_ERR(sclk->hw);
			जाओ err_clk_unreg;
		पूर्ण

		hws[sclk->idx] = sclk->hw;
	पूर्ण

	वापस 0;

err_clk_unreg:
	जबतक (--i >= 0) अणु
		sclk = &mt7621_fixed_clks[i];
		clk_hw_unरेजिस्टर_fixed_rate(sclk->hw);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा mt7621_clk *to_mt7621_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mt7621_clk, hw);
पूर्ण

अटल अचिन्हित दीर्घ mt7621_xtal_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mt7621_clk *clk = to_mt7621_clk(hw);
	काष्ठा regmap *sysc = clk->priv->sysc;
	u32 val;

	regmap_पढ़ो(sysc, SYSC_REG_SYSTEM_CONFIG0, &val);
	val = FIELD_GET(XTAL_MODE_SEL_MASK, val);

	अगर (val <= 2)
		वापस 20000000;
	अगर (val <= 5)
		वापस 40000000;

	वापस 25000000;
पूर्ण

अटल अचिन्हित दीर्घ mt7621_cpu_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ xtal_clk)
अणु
	अटल स्थिर u32 preभाग_प्रकारbl[] = अणु 0, 1, 2, 2 पूर्ण;
	काष्ठा mt7621_clk *clk = to_mt7621_clk(hw);
	काष्ठा regmap *sysc = clk->priv->sysc;
	काष्ठा regmap *memc = clk->priv->memc;
	u32 clkcfg, clk_sel, curclk, ffiv, ffrac;
	u32 pll, preभाग, fbभाग;
	अचिन्हित दीर्घ cpu_clk;

	regmap_पढ़ो(sysc, SYSC_REG_CLKCFG0, &clkcfg);
	clk_sel = FIELD_GET(CPU_CLK_SEL_MASK, clkcfg);

	regmap_पढ़ो(sysc, SYSC_REG_CUR_CLK_STS, &curclk);
	ffiv = FIELD_GET(CUR_CPU_FDIV_MASK, curclk);
	ffrac = FIELD_GET(CUR_CPU_FFRAC_MASK, curclk);

	चयन (clk_sel) अणु
	हाल 0:
		cpu_clk = 500000000;
		अवरोध;
	हाल 1:
		regmap_पढ़ो(memc, MEMC_REG_CPU_PLL, &pll);
		fbभाग = FIELD_GET(CPU_PLL_FBDIV_MASK, pll);
		preभाग = FIELD_GET(CPU_PLL_PREDIV_MASK, pll);
		cpu_clk = ((fbभाग + 1) * xtal_clk) >> preभाग_प्रकारbl[preभाग];
		अवरोध;
	शेष:
		cpu_clk = xtal_clk;
	पूर्ण

	वापस cpu_clk / ffiv * ffrac;
पूर्ण

अटल अचिन्हित दीर्घ mt7621_bus_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate / 4;
पूर्ण

#घोषणा CLK_BASE(_name, _parent, _recalc) अणु				\
	.init = &(काष्ठा clk_init_data) अणु				\
		.name = _name,						\
		.ops = &(स्थिर काष्ठा clk_ops) अणु			\
			.recalc_rate = _recalc,				\
		पूर्ण,							\
		.parent_data = &(स्थिर काष्ठा clk_parent_data) अणु	\
			.name = _parent,				\
			.fw_name = _parent				\
		पूर्ण,							\
		.num_parents = _parent ? 1 : 0				\
	पूर्ण,								\
पूर्ण

अटल काष्ठा mt7621_clk mt7621_clks_base[] = अणु
	अणु CLK_BASE("xtal", शून्य, mt7621_xtal_recalc_rate) पूर्ण,
	अणु CLK_BASE("cpu", "xtal", mt7621_cpu_recalc_rate) पूर्ण,
	अणु CLK_BASE("bus", "cpu", mt7621_bus_recalc_rate) पूर्ण,
पूर्ण;

अटल काष्ठा clk_hw *mt7621_clk_early[MT7621_CLK_MAX];

अटल पूर्णांक mt7621_रेजिस्टर_early_घड़ीs(काष्ठा device_node *np,
					काष्ठा clk_hw_onecell_data *clk_data,
					काष्ठा mt7621_clk_priv *priv)
अणु
	काष्ठा clk_hw **hws = clk_data->hws;
	काष्ठा mt7621_clk *sclk;
	पूर्णांक ret, i, j;

	क्रम (i = 0; i < ARRAY_SIZE(mt7621_clks_base); i++) अणु
		sclk = &mt7621_clks_base[i];
		sclk->priv = priv;
		ret = of_clk_hw_रेजिस्टर(np, &sclk->hw);
		अगर (ret) अणु
			pr_err("Couldn't register top clock %i\n", i);
			जाओ err_clk_unreg;
		पूर्ण

		hws[i] = &sclk->hw;
		mt7621_clk_early[i] = &sclk->hw;
	पूर्ण

	क्रम (j = i; j < MT7621_CLK_MAX; j++)
		mt7621_clk_early[j] = ERR_PTR(-EPROBE_DEFER);

	वापस 0;

err_clk_unreg:
	जबतक (--i >= 0) अणु
		sclk = &mt7621_clks_base[i];
		clk_hw_unरेजिस्टर(&sclk->hw);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __init mt7621_clk_init(काष्ठा device_node *node)
अणु
	काष्ठा mt7621_clk_priv *priv;
	काष्ठा clk_hw_onecell_data *clk_data;
	पूर्णांक ret, i, count;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस;

	priv->sysc = syscon_node_to_regmap(node);
	अगर (IS_ERR(priv->sysc)) अणु
		pr_err("Could not get sysc syscon regmap\n");
		जाओ मुक्त_clk_priv;
	पूर्ण

	priv->memc = syscon_regmap_lookup_by_phandle(node, "ralink,memctl");
	अगर (IS_ERR(priv->memc)) अणु
		pr_err("Could not get memc syscon regmap\n");
		जाओ मुक्त_clk_priv;
	पूर्ण

	count = ARRAY_SIZE(mt7621_clks_base) +
		ARRAY_SIZE(mt7621_fixed_clks) + ARRAY_SIZE(mt7621_gates);
	clk_data = kzalloc(काष्ठा_size(clk_data, hws, count), GFP_KERNEL);
	अगर (!clk_data)
		जाओ मुक्त_clk_priv;

	ret = mt7621_रेजिस्टर_early_घड़ीs(node, clk_data, priv);
	अगर (ret) अणु
		pr_err("Couldn't register top clocks\n");
		जाओ मुक्त_clk_data;
	पूर्ण

	clk_data->num = count;

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get, clk_data);
	अगर (ret) अणु
		pr_err("Couldn't add clk hw provider\n");
		जाओ unreg_clk_top;
	पूर्ण

	वापस;

unreg_clk_top:
	क्रम (i = 0; i < ARRAY_SIZE(mt7621_clks_base); i++) अणु
		काष्ठा mt7621_clk *sclk = &mt7621_clks_base[i];

		clk_hw_unरेजिस्टर(&sclk->hw);
	पूर्ण

मुक्त_clk_data:
	kमुक्त(clk_data);

मुक्त_clk_priv:
	kमुक्त(priv);
पूर्ण
CLK_OF_DECLARE_DRIVER(mt7621_clk, "mediatek,mt7621-sysc", mt7621_clk_init);

अटल पूर्णांक mt7621_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mt7621_clk_priv *priv;
	पूर्णांक ret, i, count;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->sysc = syscon_node_to_regmap(np);
	अगर (IS_ERR(priv->sysc)) अणु
		ret = PTR_ERR(priv->sysc);
		dev_err(dev, "Could not get sysc syscon regmap\n");
		वापस ret;
	पूर्ण

	priv->memc = syscon_regmap_lookup_by_phandle(np, "ralink,memctl");
	अगर (IS_ERR(priv->memc)) अणु
		ret = PTR_ERR(priv->memc);
		dev_err(dev, "Could not get memc syscon regmap\n");
		वापस ret;
	पूर्ण

	count = ARRAY_SIZE(mt7621_clks_base) +
		ARRAY_SIZE(mt7621_fixed_clks) + ARRAY_SIZE(mt7621_gates);
	clk_data = devm_kzalloc(dev, काष्ठा_size(clk_data, hws, count),
				GFP_KERNEL);
	अगर (!clk_data)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(mt7621_clks_base); i++)
		clk_data->hws[i] = mt7621_clk_early[i];

	ret = mt7621_रेजिस्टर_fixed_घड़ीs(dev, clk_data);
	अगर (ret) अणु
		dev_err(dev, "Couldn't register fixed clocks\n");
		वापस ret;
	पूर्ण

	ret = mt7621_रेजिस्टर_gates(dev, clk_data, priv);
	अगर (ret) अणु
		dev_err(dev, "Couldn't register fixed clock gates\n");
		जाओ unreg_clk_fixed;
	पूर्ण

	clk_data->num = count;

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get, clk_data);
	अगर (ret) अणु
		dev_err(dev, "Couldn't add clk hw provider\n");
		जाओ unreg_clk_gates;
	पूर्ण

	वापस 0;

unreg_clk_gates:
	क्रम (i = 0; i < ARRAY_SIZE(mt7621_gates); i++) अणु
		काष्ठा mt7621_gate *sclk = &mt7621_gates[i];

		clk_hw_unरेजिस्टर(&sclk->hw);
	पूर्ण

unreg_clk_fixed:
	क्रम (i = 0; i < ARRAY_SIZE(mt7621_fixed_clks); i++) अणु
		काष्ठा mt7621_fixed_clk *sclk = &mt7621_fixed_clks[i];

		clk_hw_unरेजिस्टर_fixed_rate(sclk->hw);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt7621_clk_of_match[] = अणु
	अणु .compatible = "mediatek,mt7621-sysc" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mt7621_clk_driver = अणु
	.probe = mt7621_clk_probe,
	.driver = अणु
		.name = "mt7621-clk",
		.of_match_table = mt7621_clk_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(mt7621_clk_driver);
