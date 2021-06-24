<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

अटल DEFINE_SPINLOCK(ve_lock);

#घोषणा SUN4I_VE_ENABLE		31
#घोषणा SUN4I_VE_DIVIDER_SHIFT	16
#घोषणा SUN4I_VE_DIVIDER_WIDTH	3
#घोषणा SUN4I_VE_RESET		0

/*
 * sunxi_ve_reset... - reset bit in ve clk रेजिस्टरs handling
 */

काष्ठा ve_reset_data अणु
	व्योम __iomem			*reg;
	spinlock_t			*lock;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

अटल पूर्णांक sunxi_ve_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				 अचिन्हित दीर्घ id)
अणु
	काष्ठा ve_reset_data *data = container_of(rcdev,
						  काष्ठा ve_reset_data,
						  rcdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(data->lock, flags);

	reg = पढ़ोl(data->reg);
	ग_लिखोl(reg & ~BIT(SUN4I_VE_RESET), data->reg);

	spin_unlock_irqrestore(data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_ve_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				   अचिन्हित दीर्घ id)
अणु
	काष्ठा ve_reset_data *data = container_of(rcdev,
						  काष्ठा ve_reset_data,
						  rcdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(data->lock, flags);

	reg = पढ़ोl(data->reg);
	ग_लिखोl(reg | BIT(SUN4I_VE_RESET), data->reg);

	spin_unlock_irqrestore(data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_ve_of_xlate(काष्ठा reset_controller_dev *rcdev,
			     स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	अगर (WARN_ON(reset_spec->args_count != 0))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops sunxi_ve_reset_ops = अणु
	.निश्चित		= sunxi_ve_reset_निश्चित,
	.deनिश्चित	= sunxi_ve_reset_deनिश्चित,
पूर्ण;

अटल व्योम __init sun4i_ve_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_भागider *भाग;
	काष्ठा clk_gate *gate;
	काष्ठा ve_reset_data *reset_data;
	स्थिर अक्षर *parent;
	स्थिर अक्षर *clk_name = node->name;
	व्योम __iomem *reg;
	पूर्णांक err;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg))
		वापस;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		जाओ err_unmap;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		जाओ err_मुक्त_भाग;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	parent = of_clk_get_parent_name(node, 0);

	gate->reg = reg;
	gate->bit_idx = SUN4I_VE_ENABLE;
	gate->lock = &ve_lock;

	भाग->reg = reg;
	भाग->shअगरt = SUN4I_VE_DIVIDER_SHIFT;
	भाग->width = SUN4I_VE_DIVIDER_WIDTH;
	भाग->lock = &ve_lock;

	clk = clk_रेजिस्टर_composite(शून्य, clk_name, &parent, 1,
				     शून्य, शून्य,
				     &भाग->hw, &clk_भागider_ops,
				     &gate->hw, &clk_gate_ops,
				     CLK_SET_RATE_PARENT);
	अगर (IS_ERR(clk))
		जाओ err_मुक्त_gate;

	err = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (err)
		जाओ err_unरेजिस्टर_clk;

	reset_data = kzalloc(माप(*reset_data), GFP_KERNEL);
	अगर (!reset_data)
		जाओ err_del_provider;

	reset_data->reg = reg;
	reset_data->lock = &ve_lock;
	reset_data->rcdev.nr_resets = 1;
	reset_data->rcdev.ops = &sunxi_ve_reset_ops;
	reset_data->rcdev.of_node = node;
	reset_data->rcdev.of_xlate = sunxi_ve_of_xlate;
	reset_data->rcdev.of_reset_n_cells = 0;
	err = reset_controller_रेजिस्टर(&reset_data->rcdev);
	अगर (err)
		जाओ err_मुक्त_reset;

	वापस;

err_मुक्त_reset:
	kमुक्त(reset_data);
err_del_provider:
	of_clk_del_provider(node);
err_unरेजिस्टर_clk:
	clk_unरेजिस्टर(clk);
err_मुक्त_gate:
	kमुक्त(gate);
err_मुक्त_भाग:
	kमुक्त(भाग);
err_unmap:
	iounmap(reg);
पूर्ण
CLK_OF_DECLARE(sun4i_ve, "allwinner,sun4i-a10-ve-clk",
	       sun4i_ve_clk_setup);
