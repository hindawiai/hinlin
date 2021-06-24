<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * JZ47xx SoCs TCU घड़ीs driver
 * Copyright (C) 2019 Paul Cercueil <paul@crapouillou.net>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/mfd/ingenic-tcu.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscore_ops.h>

#समावेश <dt-bindings/घड़ी/ingenic,tcu.h>

/* 8 channels max + watchकरोg + OST */
#घोषणा TCU_CLK_COUNT	10

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) "ingenic-tcu-clk: " fmt

क्रमागत tcu_clk_parent अणु
	TCU_PARENT_PCLK,
	TCU_PARENT_RTC,
	TCU_PARENT_EXT,
पूर्ण;

काष्ठा ingenic_soc_info अणु
	अचिन्हित पूर्णांक num_channels;
	bool has_ost;
	bool has_tcu_clk;
पूर्ण;

काष्ठा ingenic_tcu_clk_info अणु
	काष्ठा clk_init_data init_data;
	u8 gate_bit;
	u8 tcsr_reg;
पूर्ण;

काष्ठा ingenic_tcu_clk अणु
	काष्ठा clk_hw hw;
	अचिन्हित पूर्णांक idx;
	काष्ठा ingenic_tcu *tcu;
	स्थिर काष्ठा ingenic_tcu_clk_info *info;
पूर्ण;

काष्ठा ingenic_tcu अणु
	स्थिर काष्ठा ingenic_soc_info *soc_info;
	काष्ठा regmap *map;
	काष्ठा clk *clk;

	काष्ठा clk_hw_onecell_data *घड़ीs;
पूर्ण;

अटल काष्ठा ingenic_tcu *ingenic_tcu;

अटल अंतरभूत काष्ठा ingenic_tcu_clk *to_tcu_clk(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा ingenic_tcu_clk, hw);
पूर्ण

अटल पूर्णांक ingenic_tcu_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	काष्ठा ingenic_tcu *tcu = tcu_clk->tcu;

	regmap_ग_लिखो(tcu->map, TCU_REG_TSCR, BIT(info->gate_bit));

	वापस 0;
पूर्ण

अटल व्योम ingenic_tcu_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	काष्ठा ingenic_tcu *tcu = tcu_clk->tcu;

	regmap_ग_लिखो(tcu->map, TCU_REG_TSSR, BIT(info->gate_bit));
पूर्ण

अटल पूर्णांक ingenic_tcu_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	अचिन्हित पूर्णांक value;

	regmap_पढ़ो(tcu_clk->tcu->map, TCU_REG_TSR, &value);

	वापस !(value & BIT(info->gate_bit));
पूर्ण

अटल bool ingenic_tcu_enable_regs(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	काष्ठा ingenic_tcu *tcu = tcu_clk->tcu;
	bool enabled = false;

	/*
	 * If the SoC has no global TCU घड़ी, we must ungate the channel's
	 * घड़ी to be able to access its रेजिस्टरs.
	 * If we have a TCU घड़ी, it will be enabled स्वतःmatically as it has
	 * been attached to the regmap.
	 */
	अगर (!tcu->clk) अणु
		enabled = !!ingenic_tcu_is_enabled(hw);
		regmap_ग_लिखो(tcu->map, TCU_REG_TSCR, BIT(info->gate_bit));
	पूर्ण

	वापस enabled;
पूर्ण

अटल व्योम ingenic_tcu_disable_regs(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	काष्ठा ingenic_tcu *tcu = tcu_clk->tcu;

	अगर (!tcu->clk)
		regmap_ग_लिखो(tcu->map, TCU_REG_TSSR, BIT(info->gate_bit));
पूर्ण

अटल u8 ingenic_tcu_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tcu_clk->tcu->map, info->tcsr_reg, &val);
	WARN_ONCE(ret < 0, "Unable to read TCSR %d", tcu_clk->idx);

	वापस ffs(val & TCU_TCSR_PARENT_CLOCK_MASK) - 1;
पूर्ण

अटल पूर्णांक ingenic_tcu_set_parent(काष्ठा clk_hw *hw, u8 idx)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	bool was_enabled;
	पूर्णांक ret;

	was_enabled = ingenic_tcu_enable_regs(hw);

	ret = regmap_update_bits(tcu_clk->tcu->map, info->tcsr_reg,
				 TCU_TCSR_PARENT_CLOCK_MASK, BIT(idx));
	WARN_ONCE(ret < 0, "Unable to update TCSR %d", tcu_clk->idx);

	अगर (!was_enabled)
		ingenic_tcu_disable_regs(hw);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ingenic_tcu_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	अचिन्हित पूर्णांक prescale;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tcu_clk->tcu->map, info->tcsr_reg, &prescale);
	WARN_ONCE(ret < 0, "Unable to read TCSR %d", tcu_clk->idx);

	prescale = (prescale & TCU_TCSR_PRESCALE_MASK) >> TCU_TCSR_PRESCALE_LSB;

	वापस parent_rate >> (prescale * 2);
पूर्ण

अटल u8 ingenic_tcu_get_prescale(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ req_rate)
अणु
	u8 prescale;

	क्रम (prescale = 0; prescale < 5; prescale++)
		अगर ((rate >> (prescale * 2)) <= req_rate)
			वापस prescale;

	वापस 5; /* /1024 भागider */
पूर्ण

अटल दीर्घ ingenic_tcu_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ rate = *parent_rate;
	u8 prescale;

	अगर (req_rate > rate)
		वापस rate;

	prescale = ingenic_tcu_get_prescale(rate, req_rate);

	वापस rate >> (prescale * 2);
पूर्ण

अटल पूर्णांक ingenic_tcu_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ req_rate,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk = to_tcu_clk(hw);
	स्थिर काष्ठा ingenic_tcu_clk_info *info = tcu_clk->info;
	u8 prescale = ingenic_tcu_get_prescale(parent_rate, req_rate);
	bool was_enabled;
	पूर्णांक ret;

	was_enabled = ingenic_tcu_enable_regs(hw);

	ret = regmap_update_bits(tcu_clk->tcu->map, info->tcsr_reg,
				 TCU_TCSR_PRESCALE_MASK,
				 prescale << TCU_TCSR_PRESCALE_LSB);
	WARN_ONCE(ret < 0, "Unable to update TCSR %d", tcu_clk->idx);

	अगर (!was_enabled)
		ingenic_tcu_disable_regs(hw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops ingenic_tcu_clk_ops = अणु
	.get_parent	= ingenic_tcu_get_parent,
	.set_parent	= ingenic_tcu_set_parent,

	.recalc_rate	= ingenic_tcu_recalc_rate,
	.round_rate	= ingenic_tcu_round_rate,
	.set_rate	= ingenic_tcu_set_rate,

	.enable		= ingenic_tcu_enable,
	.disable	= ingenic_tcu_disable,
	.is_enabled	= ingenic_tcu_is_enabled,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ingenic_tcu_समयr_parents[] = अणु
	[TCU_PARENT_PCLK] = "pclk",
	[TCU_PARENT_RTC]  = "rtc",
	[TCU_PARENT_EXT]  = "ext",
पूर्ण;

#घोषणा DEF_TIMER(_name, _gate_bit, _tcsr)				\
	अणु								\
		.init_data = अणु						\
			.name = _name,					\
			.parent_names = ingenic_tcu_समयr_parents,	\
			.num_parents = ARRAY_SIZE(ingenic_tcu_समयr_parents),\
			.ops = &ingenic_tcu_clk_ops,			\
			.flags = CLK_SET_RATE_UNGATE,			\
		पूर्ण,							\
		.gate_bit = _gate_bit,					\
		.tcsr_reg = _tcsr,					\
	पूर्ण
अटल स्थिर काष्ठा ingenic_tcu_clk_info ingenic_tcu_clk_info[] = अणु
	[TCU_CLK_TIMER0] = DEF_TIMER("timer0", 0, TCU_REG_TCSRc(0)),
	[TCU_CLK_TIMER1] = DEF_TIMER("timer1", 1, TCU_REG_TCSRc(1)),
	[TCU_CLK_TIMER2] = DEF_TIMER("timer2", 2, TCU_REG_TCSRc(2)),
	[TCU_CLK_TIMER3] = DEF_TIMER("timer3", 3, TCU_REG_TCSRc(3)),
	[TCU_CLK_TIMER4] = DEF_TIMER("timer4", 4, TCU_REG_TCSRc(4)),
	[TCU_CLK_TIMER5] = DEF_TIMER("timer5", 5, TCU_REG_TCSRc(5)),
	[TCU_CLK_TIMER6] = DEF_TIMER("timer6", 6, TCU_REG_TCSRc(6)),
	[TCU_CLK_TIMER7] = DEF_TIMER("timer7", 7, TCU_REG_TCSRc(7)),
पूर्ण;

अटल स्थिर काष्ठा ingenic_tcu_clk_info ingenic_tcu_watchकरोg_clk_info =
					 DEF_TIMER("wdt", 16, TCU_REG_WDT_TCSR);
अटल स्थिर काष्ठा ingenic_tcu_clk_info ingenic_tcu_ost_clk_info =
					 DEF_TIMER("ost", 15, TCU_REG_OST_TCSR);
#अघोषित DEF_TIMER

अटल पूर्णांक __init ingenic_tcu_रेजिस्टर_घड़ी(काष्ठा ingenic_tcu *tcu,
			अचिन्हित पूर्णांक idx, क्रमागत tcu_clk_parent parent,
			स्थिर काष्ठा ingenic_tcu_clk_info *info,
			काष्ठा clk_hw_onecell_data *घड़ीs)
अणु
	काष्ठा ingenic_tcu_clk *tcu_clk;
	पूर्णांक err;

	tcu_clk = kzalloc(माप(*tcu_clk), GFP_KERNEL);
	अगर (!tcu_clk)
		वापस -ENOMEM;

	tcu_clk->hw.init = &info->init_data;
	tcu_clk->idx = idx;
	tcu_clk->info = info;
	tcu_clk->tcu = tcu;

	/* Reset channel and घड़ी भागider, set शेष parent */
	ingenic_tcu_enable_regs(&tcu_clk->hw);
	regmap_update_bits(tcu->map, info->tcsr_reg, 0xffff, BIT(parent));
	ingenic_tcu_disable_regs(&tcu_clk->hw);

	err = clk_hw_रेजिस्टर(शून्य, &tcu_clk->hw);
	अगर (err) अणु
		kमुक्त(tcu_clk);
		वापस err;
	पूर्ण

	घड़ीs->hws[idx] = &tcu_clk->hw;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ingenic_soc_info jz4740_soc_info = अणु
	.num_channels = 8,
	.has_ost = false,
	.has_tcu_clk = true,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info jz4725b_soc_info = अणु
	.num_channels = 6,
	.has_ost = true,
	.has_tcu_clk = true,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info jz4770_soc_info = अणु
	.num_channels = 8,
	.has_ost = true,
	.has_tcu_clk = false,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info x1000_soc_info = अणु
	.num_channels = 8,
	.has_ost = false, /* X1000 has OST, but it not beदीर्घ TCU */
	.has_tcu_clk = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id __maybe_unused ingenic_tcu_of_match[] __initस्थिर = अणु
	अणु .compatible = "ingenic,jz4740-tcu", .data = &jz4740_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4725b-tcu", .data = &jz4725b_soc_info, पूर्ण,
	अणु .compatible = "ingenic,jz4770-tcu", .data = &jz4770_soc_info, पूर्ण,
	अणु .compatible = "ingenic,x1000-tcu", .data = &x1000_soc_info, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक __init ingenic_tcu_probe(काष्ठा device_node *np)
अणु
	स्थिर काष्ठा of_device_id *id = of_match_node(ingenic_tcu_of_match, np);
	काष्ठा ingenic_tcu *tcu;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	map = device_node_to_regmap(np);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	tcu = kzalloc(माप(*tcu), GFP_KERNEL);
	अगर (!tcu)
		वापस -ENOMEM;

	tcu->map = map;
	tcu->soc_info = id->data;

	अगर (tcu->soc_info->has_tcu_clk) अणु
		tcu->clk = of_clk_get_by_name(np, "tcu");
		अगर (IS_ERR(tcu->clk)) अणु
			ret = PTR_ERR(tcu->clk);
			pr_crit("Cannot get TCU clock\n");
			जाओ err_मुक्त_tcu;
		पूर्ण

		ret = clk_prepare_enable(tcu->clk);
		अगर (ret) अणु
			pr_crit("Unable to enable TCU clock\n");
			जाओ err_put_clk;
		पूर्ण
	पूर्ण

	tcu->घड़ीs = kzalloc(काष्ठा_size(tcu->घड़ीs, hws, TCU_CLK_COUNT),
			      GFP_KERNEL);
	अगर (!tcu->घड़ीs) अणु
		ret = -ENOMEM;
		जाओ err_clk_disable;
	पूर्ण

	tcu->घड़ीs->num = TCU_CLK_COUNT;

	क्रम (i = 0; i < tcu->soc_info->num_channels; i++) अणु
		ret = ingenic_tcu_रेजिस्टर_घड़ी(tcu, i, TCU_PARENT_EXT,
						 &ingenic_tcu_clk_info[i],
						 tcu->घड़ीs);
		अगर (ret) अणु
			pr_crit("cannot register clock %d\n", i);
			जाओ err_unरेजिस्टर_समयr_घड़ीs;
		पूर्ण
	पूर्ण

	/*
	 * We set EXT as the शेष parent घड़ी क्रम all the TCU घड़ीs
	 * except क्रम the watchकरोg one, where we set the RTC घड़ी as the
	 * parent. Since the EXT and PCLK are much faster than the RTC घड़ी,
	 * the watchकरोg would kick after a maximum समय of 5s, and we might
	 * want a slower kicking समय.
	 */
	ret = ingenic_tcu_रेजिस्टर_घड़ी(tcu, TCU_CLK_WDT, TCU_PARENT_RTC,
					 &ingenic_tcu_watchकरोg_clk_info,
					 tcu->घड़ीs);
	अगर (ret) अणु
		pr_crit("cannot register watchdog clock\n");
		जाओ err_unरेजिस्टर_समयr_घड़ीs;
	पूर्ण

	अगर (tcu->soc_info->has_ost) अणु
		ret = ingenic_tcu_रेजिस्टर_घड़ी(tcu, TCU_CLK_OST,
						 TCU_PARENT_EXT,
						 &ingenic_tcu_ost_clk_info,
						 tcu->घड़ीs);
		अगर (ret) अणु
			pr_crit("cannot register ost clock\n");
			जाओ err_unरेजिस्टर_watchकरोg_घड़ी;
		पूर्ण
	पूर्ण

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get, tcu->घड़ीs);
	अगर (ret) अणु
		pr_crit("cannot add OF clock provider\n");
		जाओ err_unरेजिस्टर_ost_घड़ी;
	पूर्ण

	ingenic_tcu = tcu;

	वापस 0;

err_unरेजिस्टर_ost_घड़ी:
	अगर (tcu->soc_info->has_ost)
		clk_hw_unरेजिस्टर(tcu->घड़ीs->hws[i + 1]);
err_unरेजिस्टर_watchकरोg_घड़ी:
	clk_hw_unरेजिस्टर(tcu->घड़ीs->hws[i]);
err_unरेजिस्टर_समयr_घड़ीs:
	क्रम (i = 0; i < tcu->घड़ीs->num; i++)
		अगर (tcu->घड़ीs->hws[i])
			clk_hw_unरेजिस्टर(tcu->घड़ीs->hws[i]);
	kमुक्त(tcu->घड़ीs);
err_clk_disable:
	अगर (tcu->soc_info->has_tcu_clk)
		clk_disable_unprepare(tcu->clk);
err_put_clk:
	अगर (tcu->soc_info->has_tcu_clk)
		clk_put(tcu->clk);
err_मुक्त_tcu:
	kमुक्त(tcu);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused tcu_pm_suspend(व्योम)
अणु
	काष्ठा ingenic_tcu *tcu = ingenic_tcu;

	अगर (tcu->clk)
		clk_disable(tcu->clk);

	वापस 0;
पूर्ण

अटल व्योम __maybe_unused tcu_pm_resume(व्योम)
अणु
	काष्ठा ingenic_tcu *tcu = ingenic_tcu;

	अगर (tcu->clk)
		clk_enable(tcu->clk);
पूर्ण

अटल काष्ठा syscore_ops __maybe_unused tcu_pm_ops = अणु
	.suspend = tcu_pm_suspend,
	.resume = tcu_pm_resume,
पूर्ण;

अटल व्योम __init ingenic_tcu_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret = ingenic_tcu_probe(np);

	अगर (ret)
		pr_crit("Failed to initialize TCU clocks: %d\n", ret);

	अगर (IS_ENABLED(CONFIG_PM_SLEEP))
		रेजिस्टर_syscore_ops(&tcu_pm_ops);
पूर्ण

CLK_OF_DECLARE_DRIVER(jz4740_cgu, "ingenic,jz4740-tcu", ingenic_tcu_init);
CLK_OF_DECLARE_DRIVER(jz4725b_cgu, "ingenic,jz4725b-tcu", ingenic_tcu_init);
CLK_OF_DECLARE_DRIVER(jz4770_cgu, "ingenic,jz4770-tcu", ingenic_tcu_init);
CLK_OF_DECLARE_DRIVER(x1000_cgu, "ingenic,x1000-tcu", ingenic_tcu_init);
