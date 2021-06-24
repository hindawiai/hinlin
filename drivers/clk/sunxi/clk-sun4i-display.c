<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

काष्ठा sun4i_a10_display_clk_data अणु
	bool	has_भाग;
	u8	num_rst;
	u8	parents;

	u8	offset_en;
	u8	offset_भाग;
	u8	offset_mux;
	u8	offset_rst;

	u8	width_भाग;
	u8	width_mux;

	u32	flags;
पूर्ण;

काष्ठा reset_data अणु
	व्योम __iomem			*reg;
	spinlock_t			*lock;
	काष्ठा reset_controller_dev	rcdev;
	u8				offset;
पूर्ण;

अटल DEFINE_SPINLOCK(sun4i_a10_display_lock);

अटल अंतरभूत काष्ठा reset_data *rcdev_to_reset_data(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा reset_data, rcdev);
पूर्ण;

अटल पूर्णांक sun4i_a10_display_निश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा reset_data *data = rcdev_to_reset_data(rcdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(data->lock, flags);

	reg = पढ़ोl(data->reg);
	ग_लिखोl(reg & ~BIT(data->offset + id), data->reg);

	spin_unlock_irqrestore(data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_a10_display_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				      अचिन्हित दीर्घ id)
अणु
	काष्ठा reset_data *data = rcdev_to_reset_data(rcdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(data->lock, flags);

	reg = पढ़ोl(data->reg);
	ग_लिखोl(reg | BIT(data->offset + id), data->reg);

	spin_unlock_irqrestore(data->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_a10_display_status(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ id)
अणु
	काष्ठा reset_data *data = rcdev_to_reset_data(rcdev);

	वापस !(पढ़ोl(data->reg) & BIT(data->offset + id));
पूर्ण

अटल स्थिर काष्ठा reset_control_ops sun4i_a10_display_reset_ops = अणु
	.निश्चित		= sun4i_a10_display_निश्चित,
	.deनिश्चित	= sun4i_a10_display_deनिश्चित,
	.status		= sun4i_a10_display_status,
पूर्ण;

अटल पूर्णांक sun4i_a10_display_reset_xlate(काष्ठा reset_controller_dev *rcdev,
					 स्थिर काष्ठा of_phandle_args *spec)
अणु
	/* We only have a single reset संकेत */
	वापस 0;
पूर्ण

अटल व्योम __init sun4i_a10_display_init(काष्ठा device_node *node,
					  स्थिर काष्ठा sun4i_a10_display_clk_data *data)
अणु
	स्थिर अक्षर *parents[4];
	स्थिर अक्षर *clk_name = node->name;
	काष्ठा reset_data *reset_data;
	काष्ठा clk_भागider *भाग = शून्य;
	काष्ठा clk_gate *gate;
	काष्ठा resource res;
	काष्ठा clk_mux *mux;
	व्योम __iomem *reg;
	काष्ठा clk *clk;
	पूर्णांक ret;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg)) अणु
		pr_err("%s: Could not map the clock registers\n", clk_name);
		वापस;
	पूर्ण

	ret = of_clk_parent_fill(node, parents, data->parents);
	अगर (ret != data->parents) अणु
		pr_err("%s: Could not retrieve the parents\n", clk_name);
		जाओ unmap;
	पूर्ण

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		जाओ unmap;

	mux->reg = reg;
	mux->shअगरt = data->offset_mux;
	mux->mask = (1 << data->width_mux) - 1;
	mux->lock = &sun4i_a10_display_lock;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		जाओ मुक्त_mux;

	gate->reg = reg;
	gate->bit_idx = data->offset_en;
	gate->lock = &sun4i_a10_display_lock;

	अगर (data->has_भाग) अणु
		भाग = kzalloc(माप(*भाग), GFP_KERNEL);
		अगर (!भाग)
			जाओ मुक्त_gate;

		भाग->reg = reg;
		भाग->shअगरt = data->offset_भाग;
		भाग->width = data->width_भाग;
		भाग->lock = &sun4i_a10_display_lock;
	पूर्ण

	clk = clk_रेजिस्टर_composite(शून्य, clk_name,
				     parents, data->parents,
				     &mux->hw, &clk_mux_ops,
				     data->has_भाग ? &भाग->hw : शून्य,
				     data->has_भाग ? &clk_भागider_ops : शून्य,
				     &gate->hw, &clk_gate_ops,
				     data->flags);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: Couldn't register the clock\n", clk_name);
		जाओ मुक्त_भाग;
	पूर्ण

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret) अणु
		pr_err("%s: Couldn't register DT provider\n", clk_name);
		जाओ मुक्त_clk;
	पूर्ण

	अगर (!data->num_rst)
		वापस;

	reset_data = kzalloc(माप(*reset_data), GFP_KERNEL);
	अगर (!reset_data)
		जाओ मुक्त_of_clk;

	reset_data->reg = reg;
	reset_data->offset = data->offset_rst;
	reset_data->lock = &sun4i_a10_display_lock;
	reset_data->rcdev.nr_resets = data->num_rst;
	reset_data->rcdev.ops = &sun4i_a10_display_reset_ops;
	reset_data->rcdev.of_node = node;

	अगर (data->num_rst == 1) अणु
		reset_data->rcdev.of_reset_n_cells = 0;
		reset_data->rcdev.of_xlate = &sun4i_a10_display_reset_xlate;
	पूर्ण अन्यथा अणु
		reset_data->rcdev.of_reset_n_cells = 1;
	पूर्ण

	अगर (reset_controller_रेजिस्टर(&reset_data->rcdev)) अणु
		pr_err("%s: Couldn't register the reset controller\n",
		       clk_name);
		जाओ मुक्त_reset;
	पूर्ण

	वापस;

मुक्त_reset:
	kमुक्त(reset_data);
मुक्त_of_clk:
	of_clk_del_provider(node);
मुक्त_clk:
	clk_unरेजिस्टर_composite(clk);
मुक्त_भाग:
	kमुक्त(भाग);
मुक्त_gate:
	kमुक्त(gate);
मुक्त_mux:
	kमुक्त(mux);
unmap:
	iounmap(reg);
	of_address_to_resource(node, 0, &res);
	release_mem_region(res.start, resource_size(&res));
पूर्ण

अटल स्थिर काष्ठा sun4i_a10_display_clk_data sun4i_a10_tcon_ch0_data __initस्थिर = अणु
	.num_rst	= 2,
	.parents	= 4,
	.offset_en	= 31,
	.offset_rst	= 29,
	.offset_mux	= 24,
	.width_mux	= 2,
	.flags		= CLK_SET_RATE_PARENT,
पूर्ण;

अटल व्योम __init sun4i_a10_tcon_ch0_setup(काष्ठा device_node *node)
अणु
	sun4i_a10_display_init(node, &sun4i_a10_tcon_ch0_data);
पूर्ण
CLK_OF_DECLARE(sun4i_a10_tcon_ch0, "allwinner,sun4i-a10-tcon-ch0-clk",
	       sun4i_a10_tcon_ch0_setup);

अटल स्थिर काष्ठा sun4i_a10_display_clk_data sun4i_a10_display_data __initस्थिर = अणु
	.has_भाग	= true,
	.num_rst	= 1,
	.parents	= 3,
	.offset_en	= 31,
	.offset_rst	= 30,
	.offset_mux	= 24,
	.offset_भाग	= 0,
	.width_mux	= 2,
	.width_भाग	= 4,
पूर्ण;

अटल व्योम __init sun4i_a10_display_setup(काष्ठा device_node *node)
अणु
	sun4i_a10_display_init(node, &sun4i_a10_display_data);
पूर्ण
CLK_OF_DECLARE(sun4i_a10_display, "allwinner,sun4i-a10-display-clk",
	       sun4i_a10_display_setup);
