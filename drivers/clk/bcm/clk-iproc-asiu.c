<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>

#समावेश "clk-iproc.h"

काष्ठा iproc_asiu;

काष्ठा iproc_asiu_clk अणु
	काष्ठा clk_hw hw;
	स्थिर अक्षर *name;
	काष्ठा iproc_asiu *asiu;
	अचिन्हित दीर्घ rate;
	काष्ठा iproc_asiu_भाग भाग;
	काष्ठा iproc_asiu_gate gate;
पूर्ण;

काष्ठा iproc_asiu अणु
	व्योम __iomem *भाग_base;
	व्योम __iomem *gate_base;

	काष्ठा clk_hw_onecell_data *clk_data;
	काष्ठा iproc_asiu_clk *clks;
पूर्ण;

#घोषणा to_asiu_clk(hw) container_of(hw, काष्ठा iproc_asiu_clk, hw)

अटल पूर्णांक iproc_asiu_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा iproc_asiu_clk *clk = to_asiu_clk(hw);
	काष्ठा iproc_asiu *asiu = clk->asiu;
	u32 val;

	/* some घड़ीs at the ASIU level are always enabled */
	अगर (clk->gate.offset == IPROC_CLK_INVALID_OFFSET)
		वापस 0;

	val = पढ़ोl(asiu->gate_base + clk->gate.offset);
	val |= (1 << clk->gate.en_shअगरt);
	ग_लिखोl(val, asiu->gate_base + clk->gate.offset);

	वापस 0;
पूर्ण

अटल व्योम iproc_asiu_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा iproc_asiu_clk *clk = to_asiu_clk(hw);
	काष्ठा iproc_asiu *asiu = clk->asiu;
	u32 val;

	/* some घड़ीs at the ASIU level are always enabled */
	अगर (clk->gate.offset == IPROC_CLK_INVALID_OFFSET)
		वापस;

	val = पढ़ोl(asiu->gate_base + clk->gate.offset);
	val &= ~(1 << clk->gate.en_shअगरt);
	ग_लिखोl(val, asiu->gate_base + clk->gate.offset);
पूर्ण

अटल अचिन्हित दीर्घ iproc_asiu_clk_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_asiu_clk *clk = to_asiu_clk(hw);
	काष्ठा iproc_asiu *asiu = clk->asiu;
	u32 val;
	अचिन्हित पूर्णांक भाग_h, भाग_l;

	अगर (parent_rate == 0) अणु
		clk->rate = 0;
		वापस 0;
	पूर्ण

	/* अगर घड़ी भागisor is not enabled, simply वापस parent rate */
	val = पढ़ोl(asiu->भाग_base + clk->भाग.offset);
	अगर ((val & (1 << clk->भाग.en_shअगरt)) == 0) अणु
		clk->rate = parent_rate;
		वापस parent_rate;
	पूर्ण

	/* घड़ी rate = parent rate / (high_भाग + 1) + (low_भाग + 1) */
	भाग_h = (val >> clk->भाग.high_shअगरt) & bit_mask(clk->भाग.high_width);
	भाग_h++;
	भाग_l = (val >> clk->भाग.low_shअगरt) & bit_mask(clk->भाग.low_width);
	भाग_l++;

	clk->rate = parent_rate / (भाग_h + भाग_l);
	pr_debug("%s: rate: %lu. parent rate: %lu div_h: %u div_l: %u\n",
		 __func__, clk->rate, parent_rate, भाग_h, भाग_l);

	वापस clk->rate;
पूर्ण

अटल दीर्घ iproc_asiu_clk_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित पूर्णांक भाग;

	अगर (rate == 0 || *parent_rate == 0)
		वापस -EINVAL;

	अगर (rate == *parent_rate)
		वापस *parent_rate;

	भाग = DIV_ROUND_CLOSEST(*parent_rate, rate);
	अगर (भाग < 2)
		वापस *parent_rate;

	वापस *parent_rate / भाग;
पूर्ण

अटल पूर्णांक iproc_asiu_clk_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा iproc_asiu_clk *clk = to_asiu_clk(hw);
	काष्ठा iproc_asiu *asiu = clk->asiu;
	अचिन्हित पूर्णांक भाग, भाग_h, भाग_l;
	u32 val;

	अगर (rate == 0 || parent_rate == 0)
		वापस -EINVAL;

	/* simply disable the भागisor अगर one wants the same rate as parent */
	अगर (rate == parent_rate) अणु
		val = पढ़ोl(asiu->भाग_base + clk->भाग.offset);
		val &= ~(1 << clk->भाग.en_shअगरt);
		ग_लिखोl(val, asiu->भाग_base + clk->भाग.offset);
		वापस 0;
	पूर्ण

	भाग = DIV_ROUND_CLOSEST(parent_rate, rate);
	अगर (भाग < 2)
		वापस -EINVAL;

	भाग_h = भाग_l = भाग >> 1;
	भाग_h--;
	भाग_l--;

	val = पढ़ोl(asiu->भाग_base + clk->भाग.offset);
	val |= 1 << clk->भाग.en_shअगरt;
	अगर (भाग_h) अणु
		val &= ~(bit_mask(clk->भाग.high_width)
			 << clk->भाग.high_shअगरt);
		val |= भाग_h << clk->भाग.high_shअगरt;
	पूर्ण अन्यथा अणु
		val &= ~(bit_mask(clk->भाग.high_width)
			 << clk->भाग.high_shअगरt);
	पूर्ण
	अगर (भाग_l) अणु
		val &= ~(bit_mask(clk->भाग.low_width) << clk->भाग.low_shअगरt);
		val |= भाग_l << clk->भाग.low_shअगरt;
	पूर्ण अन्यथा अणु
		val &= ~(bit_mask(clk->भाग.low_width) << clk->भाग.low_shअगरt);
	पूर्ण
	ग_लिखोl(val, asiu->भाग_base + clk->भाग.offset);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops iproc_asiu_ops = अणु
	.enable = iproc_asiu_clk_enable,
	.disable = iproc_asiu_clk_disable,
	.recalc_rate = iproc_asiu_clk_recalc_rate,
	.round_rate = iproc_asiu_clk_round_rate,
	.set_rate = iproc_asiu_clk_set_rate,
पूर्ण;

व्योम __init iproc_asiu_setup(काष्ठा device_node *node,
			     स्थिर काष्ठा iproc_asiu_भाग *भाग,
			     स्थिर काष्ठा iproc_asiu_gate *gate,
			     अचिन्हित पूर्णांक num_clks)
अणु
	पूर्णांक i, ret;
	काष्ठा iproc_asiu *asiu;

	अगर (WARN_ON(!gate || !भाग))
		वापस;

	asiu = kzalloc(माप(*asiu), GFP_KERNEL);
	अगर (WARN_ON(!asiu))
		वापस;

	asiu->clk_data = kzalloc(काष्ठा_size(asiu->clk_data, hws, num_clks),
				 GFP_KERNEL);
	अगर (WARN_ON(!asiu->clk_data))
		जाओ err_clks;
	asiu->clk_data->num = num_clks;

	asiu->clks = kसुस्मृति(num_clks, माप(*asiu->clks), GFP_KERNEL);
	अगर (WARN_ON(!asiu->clks))
		जाओ err_asiu_clks;

	asiu->भाग_base = of_iomap(node, 0);
	अगर (WARN_ON(!asiu->भाग_base))
		जाओ err_iomap_भाग;

	asiu->gate_base = of_iomap(node, 1);
	अगर (WARN_ON(!asiu->gate_base))
		जाओ err_iomap_gate;

	क्रम (i = 0; i < num_clks; i++) अणु
		काष्ठा clk_init_data init;
		स्थिर अक्षर *parent_name;
		काष्ठा iproc_asiu_clk *asiu_clk;
		स्थिर अक्षर *clk_name;

		ret = of_property_पढ़ो_string_index(node, "clock-output-names",
						    i, &clk_name);
		अगर (WARN_ON(ret))
			जाओ err_clk_रेजिस्टर;

		asiu_clk = &asiu->clks[i];
		asiu_clk->name = clk_name;
		asiu_clk->asiu = asiu;
		asiu_clk->भाग = भाग[i];
		asiu_clk->gate = gate[i];
		init.name = clk_name;
		init.ops = &iproc_asiu_ops;
		init.flags = 0;
		parent_name = of_clk_get_parent_name(node, 0);
		init.parent_names = (parent_name ? &parent_name : शून्य);
		init.num_parents = (parent_name ? 1 : 0);
		asiu_clk->hw.init = &init;

		ret = clk_hw_रेजिस्टर(शून्य, &asiu_clk->hw);
		अगर (WARN_ON(ret))
			जाओ err_clk_रेजिस्टर;
		asiu->clk_data->hws[i] = &asiu_clk->hw;
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get,
				     asiu->clk_data);
	अगर (WARN_ON(ret))
		जाओ err_clk_रेजिस्टर;

	वापस;

err_clk_रेजिस्टर:
	जबतक (--i >= 0)
		clk_hw_unरेजिस्टर(asiu->clk_data->hws[i]);
	iounmap(asiu->gate_base);

err_iomap_gate:
	iounmap(asiu->भाग_base);

err_iomap_भाग:
	kमुक्त(asiu->clks);

err_asiu_clks:
	kमुक्त(asiu->clk_data);

err_clks:
	kमुक्त(asiu);
पूर्ण
