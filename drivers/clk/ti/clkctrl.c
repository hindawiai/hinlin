<शैली गुरु>
/*
 * OMAP clkctrl घड़ी support
 *
 * Copyright (C) 2017 Texas Instruments, Inc.
 *
 * Tero Kristo <t-kristo@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/clk/ti.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयkeeping.h>
#समावेश "clock.h"

#घोषणा NO_IDLEST			0

#घोषणा OMAP4_MODULEMODE_MASK		0x3

#घोषणा MODULEMODE_HWCTRL		0x1
#घोषणा MODULEMODE_SWCTRL		0x2

#घोषणा OMAP4_IDLEST_MASK		(0x3 << 16)
#घोषणा OMAP4_IDLEST_SHIFT		16

#घोषणा OMAP4_STBYST_MASK		BIT(18)
#घोषणा OMAP4_STBYST_SHIFT		18

#घोषणा CLKCTRL_IDLEST_FUNCTIONAL	0x0
#घोषणा CLKCTRL_IDLEST_INTERFACE_IDLE	0x2
#घोषणा CLKCTRL_IDLEST_DISABLED		0x3

/* These समयouts are in us */
#घोषणा OMAP4_MAX_MODULE_READY_TIME	2000
#घोषणा OMAP4_MAX_MODULE_DISABLE_TIME	5000

अटल bool _early_समयout = true;

काष्ठा omap_clkctrl_provider अणु
	व्योम __iomem *base;
	काष्ठा list_head घड़ीs;
	अक्षर *clkdm_name;
पूर्ण;

काष्ठा omap_clkctrl_clk अणु
	काष्ठा clk_hw *clk;
	u16 reg_offset;
	पूर्णांक bit_offset;
	काष्ठा list_head node;
पूर्ण;

जोड़ omap4_समयout अणु
	u32 cycles;
	kसमय_प्रकार start;
पूर्ण;

अटल स्थिर काष्ठा omap_clkctrl_data शेष_clkctrl_data[] __initस्थिर = अणु
	अणु 0 पूर्ण,
पूर्ण;

अटल u32 _omap4_idlest(u32 val)
अणु
	val &= OMAP4_IDLEST_MASK;
	val >>= OMAP4_IDLEST_SHIFT;

	वापस val;
पूर्ण

अटल bool _omap4_is_idle(u32 val)
अणु
	val = _omap4_idlest(val);

	वापस val == CLKCTRL_IDLEST_DISABLED;
पूर्ण

अटल bool _omap4_is_पढ़ोy(u32 val)
अणु
	val = _omap4_idlest(val);

	वापस val == CLKCTRL_IDLEST_FUNCTIONAL ||
	       val == CLKCTRL_IDLEST_INTERFACE_IDLE;
पूर्ण

अटल bool _omap4_is_समयout(जोड़ omap4_समयout *समय, u32 समयout)
अणु
	/*
	 * There are two special हालs where kसमय_प्रकारo_ns() can't be
	 * used to track the समयouts. First one is during early boot
	 * when the समयrs haven't been initialized yet. The second
	 * one is during suspend-resume cycle जबतक समयkeeping is
	 * being suspended / resumed. Clocksource क्रम the प्रणाली
	 * can be from a समयr that requires pm_runसमय access, which
	 * will eventually bring us here with समयkeeping_suspended,
	 * during both suspend entry and resume paths. This happens
	 * at least on am43xx platक्रमm. Account क्रम flakeyness
	 * with udelay() by multiplying the समयout value by 2.
	 */
	अगर (unlikely(_early_समयout || समयkeeping_suspended)) अणु
		अगर (समय->cycles++ < समयout) अणु
			udelay(1 * 2);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!kसमय_प्रकारo_ns(समय->start)) अणु
			समय->start = kसमय_get();
			वापस false;
		पूर्ण

		अगर (kसमय_us_delta(kसमय_get(), समय->start) < समयout) अणु
			cpu_relax();
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक __init _omap4_disable_early_समयout(व्योम)
अणु
	_early_समयout = false;

	वापस 0;
पूर्ण
arch_initcall(_omap4_disable_early_समयout);

अटल पूर्णांक _omap4_clkctrl_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 val;
	पूर्णांक ret;
	जोड़ omap4_समयout समयout = अणु 0 पूर्ण;

	अगर (clk->clkdm) अणु
		ret = ti_clk_ll_ops->clkdm_clk_enable(clk->clkdm, hw->clk);
		अगर (ret) अणु
			WARN(1,
			     "%s: could not enable %s's clockdomain %s: %d\n",
			     __func__, clk_hw_get_name(hw),
			     clk->clkdm_name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!clk->enable_bit)
		वापस 0;

	val = ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg);

	val &= ~OMAP4_MODULEMODE_MASK;
	val |= clk->enable_bit;

	ti_clk_ll_ops->clk_ग_लिखोl(val, &clk->enable_reg);

	अगर (test_bit(NO_IDLEST, &clk->flags))
		वापस 0;

	/* Wait until module is enabled */
	जबतक (!_omap4_is_पढ़ोy(ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg))) अणु
		अगर (_omap4_is_समयout(&समयout, OMAP4_MAX_MODULE_READY_TIME)) अणु
			pr_err("%s: failed to enable\n", clk_hw_get_name(hw));
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _omap4_clkctrl_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 val;
	जोड़ omap4_समयout समयout = अणु 0 पूर्ण;

	अगर (!clk->enable_bit)
		जाओ निकास;

	val = ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg);

	val &= ~OMAP4_MODULEMODE_MASK;

	ti_clk_ll_ops->clk_ग_लिखोl(val, &clk->enable_reg);

	अगर (test_bit(NO_IDLEST, &clk->flags))
		जाओ निकास;

	/* Wait until module is disabled */
	जबतक (!_omap4_is_idle(ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg))) अणु
		अगर (_omap4_is_समयout(&समयout,
				      OMAP4_MAX_MODULE_DISABLE_TIME)) अणु
			pr_err("%s: failed to disable\n", clk_hw_get_name(hw));
			अवरोध;
		पूर्ण
	पूर्ण

निकास:
	अगर (clk->clkdm)
		ti_clk_ll_ops->clkdm_clk_disable(clk->clkdm, hw->clk);
पूर्ण

अटल पूर्णांक _omap4_clkctrl_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 val;

	val = ti_clk_ll_ops->clk_पढ़ोl(&clk->enable_reg);

	अगर (val & clk->enable_bit)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops omap4_clkctrl_clk_ops = अणु
	.enable		= _omap4_clkctrl_clk_enable,
	.disable	= _omap4_clkctrl_clk_disable,
	.is_enabled	= _omap4_clkctrl_clk_is_enabled,
	.init		= omap2_init_clk_clkdm,
पूर्ण;

अटल काष्ठा clk_hw *_ti_omap4_clkctrl_xlate(काष्ठा of_phandle_args *clkspec,
					      व्योम *data)
अणु
	काष्ठा omap_clkctrl_provider *provider = data;
	काष्ठा omap_clkctrl_clk *entry;
	bool found = false;

	अगर (clkspec->args_count != 2)
		वापस ERR_PTR(-EINVAL);

	pr_debug("%s: looking for %x:%x\n", __func__,
		 clkspec->args[0], clkspec->args[1]);

	list_क्रम_each_entry(entry, &provider->घड़ीs, node) अणु
		अगर (entry->reg_offset == clkspec->args[0] &&
		    entry->bit_offset == clkspec->args[1]) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस ERR_PTR(-EINVAL);

	वापस entry->clk;
पूर्ण

/* Get clkctrl घड़ी base name based on clkctrl_name or dts node */
अटल स्थिर अक्षर * __init clkctrl_get_घड़ी_name(काष्ठा device_node *np,
						  स्थिर अक्षर *clkctrl_name,
						  पूर्णांक offset, पूर्णांक index,
						  bool legacy_naming)
अणु
	अक्षर *घड़ी_name;

	/* l4per-clkctrl:1234:0 style naming based on clkctrl_name */
	अगर (clkctrl_name && !legacy_naming) अणु
		घड़ी_name = kaप्र_लिखो(GFP_KERNEL, "%s-clkctrl:%04x:%d",
				       clkctrl_name, offset, index);
		strreplace(घड़ी_name, '_', '-');

		वापस घड़ी_name;
	पूर्ण

	/* l4per:1234:0 old style naming based on clkctrl_name */
	अगर (clkctrl_name)
		वापस kaप्र_लिखो(GFP_KERNEL, "%s_cm:clk:%04x:%d",
				 clkctrl_name, offset, index);

	/* l4per_cm:1234:0 old style naming based on parent node name */
	अगर (legacy_naming)
		वापस kaप्र_लिखो(GFP_KERNEL, "%pOFn:clk:%04x:%d",
				 np->parent, offset, index);

	/* l4per-clkctrl:1234:0 style naming based on node name */
	वापस kaप्र_लिखो(GFP_KERNEL, "%pOFn:%04x:%d", np, offset, index);
पूर्ण

अटल पूर्णांक __init
_ti_clkctrl_clk_रेजिस्टर(काष्ठा omap_clkctrl_provider *provider,
			 काष्ठा device_node *node, काष्ठा clk_hw *clk_hw,
			 u16 offset, u8 bit, स्थिर अक्षर * स्थिर *parents,
			 पूर्णांक num_parents, स्थिर काष्ठा clk_ops *ops,
			 स्थिर अक्षर *clkctrl_name)
अणु
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk *clk;
	काष्ठा omap_clkctrl_clk *clkctrl_clk;
	पूर्णांक ret = 0;

	init.name = clkctrl_get_घड़ी_name(node, clkctrl_name, offset, bit,
					   ti_clk_get_features()->flags &
					   TI_CLK_CLKCTRL_COMPAT);

	clkctrl_clk = kzalloc(माप(*clkctrl_clk), GFP_KERNEL);
	अगर (!init.name || !clkctrl_clk) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	clk_hw->init = &init;
	init.parent_names = parents;
	init.num_parents = num_parents;
	init.ops = ops;
	init.flags = 0;

	clk = ti_clk_रेजिस्टर(शून्य, clk_hw, init.name);
	अगर (IS_ERR_OR_शून्य(clk)) अणु
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	clkctrl_clk->reg_offset = offset;
	clkctrl_clk->bit_offset = bit;
	clkctrl_clk->clk = clk_hw;

	list_add(&clkctrl_clk->node, &provider->घड़ीs);

	वापस 0;

cleanup:
	kमुक्त(init.name);
	kमुक्त(clkctrl_clk);
	वापस ret;
पूर्ण

अटल व्योम __init
_ti_clkctrl_setup_gate(काष्ठा omap_clkctrl_provider *provider,
		       काष्ठा device_node *node, u16 offset,
		       स्थिर काष्ठा omap_clkctrl_bit_data *data,
		       व्योम __iomem *reg, स्थिर अक्षर *clkctrl_name)
अणु
	काष्ठा clk_hw_omap *clk_hw;

	clk_hw = kzalloc(माप(*clk_hw), GFP_KERNEL);
	अगर (!clk_hw)
		वापस;

	clk_hw->enable_bit = data->bit;
	clk_hw->enable_reg.ptr = reg;

	अगर (_ti_clkctrl_clk_रेजिस्टर(provider, node, &clk_hw->hw, offset,
				     data->bit, data->parents, 1,
				     &omap_gate_clk_ops, clkctrl_name))
		kमुक्त(clk_hw);
पूर्ण

अटल व्योम __init
_ti_clkctrl_setup_mux(काष्ठा omap_clkctrl_provider *provider,
		      काष्ठा device_node *node, u16 offset,
		      स्थिर काष्ठा omap_clkctrl_bit_data *data,
		      व्योम __iomem *reg, स्थिर अक्षर *clkctrl_name)
अणु
	काष्ठा clk_omap_mux *mux;
	पूर्णांक num_parents = 0;
	स्थिर अक्षर * स्थिर *pname;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस;

	pname = data->parents;
	जबतक (*pname) अणु
		num_parents++;
		pname++;
	पूर्ण

	mux->mask = num_parents;
	अगर (!(mux->flags & CLK_MUX_INDEX_ONE))
		mux->mask--;

	mux->mask = (1 << fls(mux->mask)) - 1;

	mux->shअगरt = data->bit;
	mux->reg.ptr = reg;

	अगर (_ti_clkctrl_clk_रेजिस्टर(provider, node, &mux->hw, offset,
				     data->bit, data->parents, num_parents,
				     &ti_clk_mux_ops, clkctrl_name))
		kमुक्त(mux);
पूर्ण

अटल व्योम __init
_ti_clkctrl_setup_भाग(काष्ठा omap_clkctrl_provider *provider,
		      काष्ठा device_node *node, u16 offset,
		      स्थिर काष्ठा omap_clkctrl_bit_data *data,
		      व्योम __iomem *reg, स्थिर अक्षर *clkctrl_name)
अणु
	काष्ठा clk_omap_भागider *भाग;
	स्थिर काष्ठा omap_clkctrl_भाग_data *भाग_data = data->data;
	u8 भाग_flags = 0;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस;

	भाग->reg.ptr = reg;
	भाग->shअगरt = data->bit;
	भाग->flags = भाग_data->flags;

	अगर (भाग->flags & CLK_DIVIDER_POWER_OF_TWO)
		भाग_flags |= CLKF_INDEX_POWER_OF_TWO;

	अगर (ti_clk_parse_भागider_data((पूर्णांक *)भाग_data->भागiders, 0,
				      भाग_data->max_भाग, भाग_flags,
				      भाग)) अणु
		pr_err("%s: Data parsing for %pOF:%04x:%d failed\n", __func__,
		       node, offset, data->bit);
		kमुक्त(भाग);
		वापस;
	पूर्ण

	अगर (_ti_clkctrl_clk_रेजिस्टर(provider, node, &भाग->hw, offset,
				     data->bit, data->parents, 1,
				     &ti_clk_भागider_ops, clkctrl_name))
		kमुक्त(भाग);
पूर्ण

अटल व्योम __init
_ti_clkctrl_setup_subclks(काष्ठा omap_clkctrl_provider *provider,
			  काष्ठा device_node *node,
			  स्थिर काष्ठा omap_clkctrl_reg_data *data,
			  व्योम __iomem *reg, स्थिर अक्षर *clkctrl_name)
अणु
	स्थिर काष्ठा omap_clkctrl_bit_data *bits = data->bit_data;

	अगर (!bits)
		वापस;

	जबतक (bits->bit) अणु
		चयन (bits->type) अणु
		हाल TI_CLK_GATE:
			_ti_clkctrl_setup_gate(provider, node, data->offset,
					       bits, reg, clkctrl_name);
			अवरोध;

		हाल TI_CLK_DIVIDER:
			_ti_clkctrl_setup_भाग(provider, node, data->offset,
					      bits, reg, clkctrl_name);
			अवरोध;

		हाल TI_CLK_MUX:
			_ti_clkctrl_setup_mux(provider, node, data->offset,
					      bits, reg, clkctrl_name);
			अवरोध;

		शेष:
			pr_err("%s: bad subclk type: %d\n", __func__,
			       bits->type);
			वापस;
		पूर्ण
		bits++;
	पूर्ण
पूर्ण

अटल व्योम __init _clkctrl_add_provider(व्योम *data,
					 काष्ठा device_node *np)
अणु
	of_clk_add_hw_provider(np, _ti_omap4_clkctrl_xlate, data);
पूर्ण

/* Get घड़ी name based on compatible string क्रम clkctrl */
अटल अक्षर * __init clkctrl_get_name(काष्ठा device_node *np)
अणु
	काष्ठा property *prop;
	स्थिर पूर्णांक prefix_len = 11;
	स्थिर अक्षर *compat;
	अक्षर *name;

	of_property_क्रम_each_string(np, "compatible", prop, compat) अणु
		अगर (!म_भेदन("ti,clkctrl-", compat, prefix_len)) अणु
			/* Two letter minimum name length क्रम l3, l4 etc */
			अगर (strnlen(compat + prefix_len, 16) < 2)
				जारी;
			name = kaप्र_लिखो(GFP_KERNEL, "%s", compat + prefix_len);
			अगर (!name)
				जारी;
			strreplace(name, '-', '_');

			वापस name;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __init _ti_omap4_clkctrl_setup(काष्ठा device_node *node)
अणु
	काष्ठा omap_clkctrl_provider *provider;
	स्थिर काष्ठा omap_clkctrl_data *data = शेष_clkctrl_data;
	स्थिर काष्ठा omap_clkctrl_reg_data *reg_data;
	काष्ठा clk_init_data init = अणु शून्य पूर्ण;
	काष्ठा clk_hw_omap *hw;
	काष्ठा clk *clk;
	काष्ठा omap_clkctrl_clk *clkctrl_clk = शून्य;
	स्थिर __be32 *addrp;
	bool legacy_naming;
	अक्षर *clkctrl_name;
	u32 addr;
	पूर्णांक ret;
	अक्षर *c;
	u16 soc_mask = 0;

	अगर (!(ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT) &&
	    of_node_name_eq(node, "clk"))
		ti_clk_features.flags |= TI_CLK_CLKCTRL_COMPAT;

	addrp = of_get_address(node, 0, शून्य, शून्य);
	addr = (u32)of_translate_address(node, addrp);

#अगर_घोषित CONFIG_ARCH_OMAP4
	अगर (of_machine_is_compatible("ti,omap4"))
		data = omap4_clkctrl_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_OMAP5
	अगर (of_machine_is_compatible("ti,omap5"))
		data = omap5_clkctrl_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_DRA7XX
	अगर (of_machine_is_compatible("ti,dra7")) अणु
		अगर (ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT)
			data = dra7_clkctrl_compat_data;
		अन्यथा
			data = dra7_clkctrl_data;
	पूर्ण

	अगर (of_machine_is_compatible("ti,dra72"))
		soc_mask = CLKF_SOC_DRA72;
	अगर (of_machine_is_compatible("ti,dra74"))
		soc_mask = CLKF_SOC_DRA74;
	अगर (of_machine_is_compatible("ti,dra76"))
		soc_mask = CLKF_SOC_DRA76;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_AM33XX
	अगर (of_machine_is_compatible("ti,am33xx")) अणु
		अगर (ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT)
			data = am3_clkctrl_compat_data;
		अन्यथा
			data = am3_clkctrl_data;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_AM43XX
	अगर (of_machine_is_compatible("ti,am4372")) अणु
		अगर (ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT)
			data = am4_clkctrl_compat_data;
		अन्यथा
			data = am4_clkctrl_data;
	पूर्ण

	अगर (of_machine_is_compatible("ti,am438x")) अणु
		अगर (ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT)
			data = am438x_clkctrl_compat_data;
		अन्यथा
			data = am438x_clkctrl_data;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOC_TI81XX
	अगर (of_machine_is_compatible("ti,dm814"))
		data = dm814_clkctrl_data;

	अगर (of_machine_is_compatible("ti,dm816"))
		data = dm816_clkctrl_data;
#पूर्ण_अगर

	अगर (ti_clk_get_features()->flags & TI_CLK_DEVICE_TYPE_GP)
		soc_mask |= CLKF_SOC_NONSEC;

	जबतक (data->addr) अणु
		अगर (addr == data->addr)
			अवरोध;

		data++;
	पूर्ण

	अगर (!data->addr) अणु
		pr_err("%pOF not found from clkctrl data.\n", node);
		वापस;
	पूर्ण

	provider = kzalloc(माप(*provider), GFP_KERNEL);
	अगर (!provider)
		वापस;

	provider->base = of_iomap(node, 0);

	legacy_naming = ti_clk_get_features()->flags & TI_CLK_CLKCTRL_COMPAT;
	clkctrl_name = clkctrl_get_name(node);
	अगर (clkctrl_name) अणु
		provider->clkdm_name = kaप्र_लिखो(GFP_KERNEL,
						 "%s_clkdm", clkctrl_name);
		जाओ clkdm_found;
	पूर्ण

	/*
	 * The code below can be हटाओd when all clkctrl nodes use करोमुख्य
	 * specअगरic compatible proprerty and standard घड़ी node naming
	 */
	अगर (legacy_naming) अणु
		provider->clkdm_name = kaप्र_लिखो(GFP_KERNEL, "%pOFnxxx", node->parent);
		अगर (!provider->clkdm_name) अणु
			kमुक्त(provider);
			वापस;
		पूर्ण

		/*
		 * Create शेष clkdm name, replace _cm from end of parent
		 * node name with _clkdm
		 */
		provider->clkdm_name[म_माप(provider->clkdm_name) - 2] = 0;
	पूर्ण अन्यथा अणु
		provider->clkdm_name = kaप्र_लिखो(GFP_KERNEL, "%pOFn", node);
		अगर (!provider->clkdm_name) अणु
			kमुक्त(provider);
			वापस;
		पूर्ण

		/*
		 * Create शेष clkdm name, replace _clkctrl from end of
		 * node name with _clkdm
		 */
		provider->clkdm_name[म_माप(provider->clkdm_name) - 7] = 0;
	पूर्ण

	म_जोड़ो(provider->clkdm_name, "clkdm");

	/* Replace any dash from the clkdm name with underscore */
	c = provider->clkdm_name;

	जबतक (*c) अणु
		अगर (*c == '-')
			*c = '_';
		c++;
	पूर्ण
clkdm_found:
	INIT_LIST_HEAD(&provider->घड़ीs);

	/* Generate घड़ीs */
	reg_data = data->regs;

	जबतक (reg_data->parent) अणु
		अगर ((reg_data->flags & CLKF_SOC_MASK) &&
		    (reg_data->flags & soc_mask) == 0) अणु
			reg_data++;
			जारी;
		पूर्ण

		hw = kzalloc(माप(*hw), GFP_KERNEL);
		अगर (!hw)
			वापस;

		hw->enable_reg.ptr = provider->base + reg_data->offset;

		_ti_clkctrl_setup_subclks(provider, node, reg_data,
					  hw->enable_reg.ptr, clkctrl_name);

		अगर (reg_data->flags & CLKF_SW_SUP)
			hw->enable_bit = MODULEMODE_SWCTRL;
		अगर (reg_data->flags & CLKF_HW_SUP)
			hw->enable_bit = MODULEMODE_HWCTRL;
		अगर (reg_data->flags & CLKF_NO_IDLEST)
			set_bit(NO_IDLEST, &hw->flags);

		अगर (reg_data->clkdm_name)
			hw->clkdm_name = reg_data->clkdm_name;
		अन्यथा
			hw->clkdm_name = provider->clkdm_name;

		init.parent_names = &reg_data->parent;
		init.num_parents = 1;
		init.flags = 0;
		अगर (reg_data->flags & CLKF_SET_RATE_PARENT)
			init.flags |= CLK_SET_RATE_PARENT;

		init.name = clkctrl_get_घड़ी_name(node, clkctrl_name,
						   reg_data->offset, 0,
						   legacy_naming);
		अगर (!init.name)
			जाओ cleanup;

		clkctrl_clk = kzalloc(माप(*clkctrl_clk), GFP_KERNEL);
		अगर (!clkctrl_clk)
			जाओ cleanup;

		init.ops = &omap4_clkctrl_clk_ops;
		hw->hw.init = &init;

		clk = ti_clk_रेजिस्टर_omap_hw(शून्य, &hw->hw, init.name);
		अगर (IS_ERR_OR_शून्य(clk))
			जाओ cleanup;

		clkctrl_clk->reg_offset = reg_data->offset;
		clkctrl_clk->clk = &hw->hw;

		list_add(&clkctrl_clk->node, &provider->घड़ीs);

		reg_data++;
	पूर्ण

	ret = of_clk_add_hw_provider(node, _ti_omap4_clkctrl_xlate, provider);
	अगर (ret == -EPROBE_DEFER)
		ti_clk_retry_init(node, provider, _clkctrl_add_provider);

	kमुक्त(clkctrl_name);

	वापस;

cleanup:
	kमुक्त(hw);
	kमुक्त(init.name);
	kमुक्त(clkctrl_name);
	kमुक्त(clkctrl_clk);
पूर्ण
CLK_OF_DECLARE(ti_omap4_clkctrl_घड़ी, "ti,clkctrl",
	       _ti_omap4_clkctrl_setup);

/**
 * ti_clk_is_in_standby - Check अगर clkctrl घड़ी is in standby or not
 * @clk: घड़ी to check standby status क्रम
 *
 * Finds whether the provided घड़ी is in standby mode or not. Returns
 * true अगर the provided घड़ी is a clkctrl type घड़ी and it is in standby,
 * false otherwise.
 */
bool ti_clk_is_in_standby(काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_hw_omap *hwclk;
	u32 val;

	hw = __clk_get_hw(clk);

	अगर (!omap2_clk_is_hw_omap(hw))
		वापस false;

	hwclk = to_clk_hw_omap(hw);

	val = ti_clk_ll_ops->clk_पढ़ोl(&hwclk->enable_reg);

	अगर (val & OMAP4_STBYST_MASK)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(ti_clk_is_in_standby);
