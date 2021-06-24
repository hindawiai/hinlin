<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 ARM Limited
 */

#समावेश <linux/amba/sp810.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#घोषणा to_clk_sp810_समयrclken(_hw) \
		container_of(_hw, काष्ठा clk_sp810_समयrclken, hw)

काष्ठा clk_sp810;

काष्ठा clk_sp810_समयrclken अणु
	काष्ठा clk_hw hw;
	काष्ठा clk *clk;
	काष्ठा clk_sp810 *sp810;
	पूर्णांक channel;
पूर्ण;

काष्ठा clk_sp810 अणु
	काष्ठा device_node *node;
	व्योम __iomem *base;
	spinlock_t lock;
	काष्ठा clk_sp810_समयrclken समयrclken[4];
पूर्ण;

अटल u8 clk_sp810_समयrclken_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_sp810_समयrclken *समयrclken = to_clk_sp810_समयrclken(hw);
	u32 val = पढ़ोl(समयrclken->sp810->base + SCCTRL);

	वापस !!(val & (1 << SCCTRL_TIMERENnSEL_SHIFT(समयrclken->channel)));
पूर्ण

अटल पूर्णांक clk_sp810_समयrclken_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_sp810_समयrclken *समयrclken = to_clk_sp810_समयrclken(hw);
	काष्ठा clk_sp810 *sp810 = समयrclken->sp810;
	u32 val, shअगरt = SCCTRL_TIMERENnSEL_SHIFT(समयrclken->channel);
	अचिन्हित दीर्घ flags = 0;

	अगर (WARN_ON(index > 1))
		वापस -EINVAL;

	spin_lock_irqsave(&sp810->lock, flags);

	val = पढ़ोl(sp810->base + SCCTRL);
	val &= ~(1 << shअगरt);
	val |= index << shअगरt;
	ग_लिखोl(val, sp810->base + SCCTRL);

	spin_unlock_irqrestore(&sp810->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_sp810_समयrclken_ops = अणु
	.get_parent = clk_sp810_समयrclken_get_parent,
	.set_parent = clk_sp810_समयrclken_set_parent,
पूर्ण;

अटल काष्ठा clk *clk_sp810_समयrclken_of_get(काष्ठा of_phandle_args *clkspec,
		व्योम *data)
अणु
	काष्ठा clk_sp810 *sp810 = data;

	अगर (WARN_ON(clkspec->args_count != 1 ||
		    clkspec->args[0] >=	ARRAY_SIZE(sp810->समयrclken)))
		वापस शून्य;

	वापस sp810->समयrclken[clkspec->args[0]].clk;
पूर्ण

अटल व्योम __init clk_sp810_of_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk_sp810 *sp810 = kzalloc(माप(*sp810), GFP_KERNEL);
	स्थिर अक्षर *parent_names[2];
	पूर्णांक num = ARRAY_SIZE(parent_names);
	अक्षर name[12];
	काष्ठा clk_init_data init;
	अटल पूर्णांक instance;
	पूर्णांक i;
	bool deprecated;

	अगर (!sp810)
		वापस;

	अगर (of_clk_parent_fill(node, parent_names, num) != num) अणु
		pr_warn("Failed to obtain parent clocks for SP810!\n");
		kमुक्त(sp810);
		वापस;
	पूर्ण

	sp810->node = node;
	sp810->base = of_iomap(node, 0);
	spin_lock_init(&sp810->lock);

	init.name = name;
	init.ops = &clk_sp810_समयrclken_ops;
	init.flags = 0;
	init.parent_names = parent_names;
	init.num_parents = num;

	deprecated = !of_find_property(node, "assigned-clock-parents", शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(sp810->समयrclken); i++) अणु
		snम_लिखो(name, माप(name), "sp810_%d_%d", instance, i);

		sp810->समयrclken[i].sp810 = sp810;
		sp810->समयrclken[i].channel = i;
		sp810->समयrclken[i].hw.init = &init;

		/*
		 * If DT isn't setting the parent, क्रमce it to be
		 * the 1 MHz घड़ी without going through the framework.
		 * We करो this beक्रमe clk_रेजिस्टर() so that it can determine
		 * the parent and setup the tree properly.
		 */
		अगर (deprecated)
			init.ops->set_parent(&sp810->समयrclken[i].hw, 1);

		sp810->समयrclken[i].clk = clk_रेजिस्टर(शून्य,
				&sp810->समयrclken[i].hw);
		WARN_ON(IS_ERR(sp810->समयrclken[i].clk));
	पूर्ण

	of_clk_add_provider(node, clk_sp810_समयrclken_of_get, sp810);
	instance++;
पूर्ण
CLK_OF_DECLARE(sp810, "arm,sp810", clk_sp810_of_setup);
