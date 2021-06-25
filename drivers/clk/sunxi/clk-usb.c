<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013-2015 Emilio Lथकpez
 *
 * Emilio Lथकpez <emilio@elopez.com.ar>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>


/*
 * sunxi_usb_reset... - reset bits in usb clk रेजिस्टरs handling
 */

काष्ठा usb_reset_data अणु
	व्योम __iomem			*reg;
	spinlock_t			*lock;
	काष्ठा clk			*clk;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;

अटल पूर्णांक sunxi_usb_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा usb_reset_data *data = container_of(rcdev,
						   काष्ठा usb_reset_data,
						   rcdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	clk_prepare_enable(data->clk);
	spin_lock_irqsave(data->lock, flags);

	reg = पढ़ोl(data->reg);
	ग_लिखोl(reg & ~BIT(id), data->reg);

	spin_unlock_irqrestore(data->lock, flags);
	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_usb_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा usb_reset_data *data = container_of(rcdev,
						     काष्ठा usb_reset_data,
						     rcdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	clk_prepare_enable(data->clk);
	spin_lock_irqsave(data->lock, flags);

	reg = पढ़ोl(data->reg);
	ग_लिखोl(reg | BIT(id), data->reg);

	spin_unlock_irqrestore(data->lock, flags);
	clk_disable_unprepare(data->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops sunxi_usb_reset_ops = अणु
	.निश्चित		= sunxi_usb_reset_निश्चित,
	.deनिश्चित	= sunxi_usb_reset_deनिश्चित,
पूर्ण;

/**
 * sunxi_usb_clk_setup() - Setup function क्रम usb gate घड़ीs
 */

#घोषणा SUNXI_USB_MAX_SIZE 32

काष्ठा usb_clk_data अणु
	u32 clk_mask;
	u32 reset_mask;
	bool reset_needs_clk;
पूर्ण;

अटल व्योम __init sunxi_usb_clk_setup(काष्ठा device_node *node,
				       स्थिर काष्ठा usb_clk_data *data,
				       spinlock_t *lock)
अणु
	काष्ठा clk_onecell_data *clk_data;
	काष्ठा usb_reset_data *reset_data;
	स्थिर अक्षर *clk_parent;
	स्थिर अक्षर *clk_name;
	व्योम __iomem *reg;
	पूर्णांक qty;
	पूर्णांक i = 0;
	पूर्णांक j = 0;

	reg = of_io_request_and_map(node, 0, of_node_full_name(node));
	अगर (IS_ERR(reg))
		वापस;

	clk_parent = of_clk_get_parent_name(node, 0);
	अगर (!clk_parent)
		वापस;

	/* Worst-हाल size approximation and memory allocation */
	qty = find_last_bit((अचिन्हित दीर्घ *)&data->clk_mask,
			    SUNXI_USB_MAX_SIZE);

	clk_data = kदो_स्मृति(माप(काष्ठा clk_onecell_data), GFP_KERNEL);
	अगर (!clk_data)
		वापस;

	clk_data->clks = kसुस्मृति(qty + 1, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clk_data->clks) अणु
		kमुक्त(clk_data);
		वापस;
	पूर्ण

	क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)&data->clk_mask,
			 SUNXI_USB_MAX_SIZE) अणु
		of_property_पढ़ो_string_index(node, "clock-output-names",
					      j, &clk_name);
		clk_data->clks[i] = clk_रेजिस्टर_gate(शून्य, clk_name,
						      clk_parent, 0,
						      reg, i, 0, lock);
		WARN_ON(IS_ERR(clk_data->clks[i]));

		j++;
	पूर्ण

	/* Adjust to the real max */
	clk_data->clk_num = i;

	of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);

	/* Register a reset controller क्रम usb with reset bits */
	अगर (data->reset_mask == 0)
		वापस;

	reset_data = kzalloc(माप(*reset_data), GFP_KERNEL);
	अगर (!reset_data)
		वापस;

	अगर (data->reset_needs_clk) अणु
		reset_data->clk = of_clk_get(node, 0);
		अगर (IS_ERR(reset_data->clk)) अणु
			pr_err("Could not get clock for reset controls\n");
			kमुक्त(reset_data);
			वापस;
		पूर्ण
	पूर्ण

	reset_data->reg = reg;
	reset_data->lock = lock;
	reset_data->rcdev.nr_resets = __fls(data->reset_mask) + 1;
	reset_data->rcdev.ops = &sunxi_usb_reset_ops;
	reset_data->rcdev.of_node = node;
	reset_controller_रेजिस्टर(&reset_data->rcdev);
पूर्ण

अटल स्थिर काष्ठा usb_clk_data sun4i_a10_usb_clk_data __initस्थिर = अणु
	.clk_mask = BIT(8) | BIT(7) | BIT(6),
	.reset_mask = BIT(2) | BIT(1) | BIT(0),
पूर्ण;

अटल DEFINE_SPINLOCK(sun4i_a10_usb_lock);

अटल व्योम __init sun4i_a10_usb_setup(काष्ठा device_node *node)
अणु
	sunxi_usb_clk_setup(node, &sun4i_a10_usb_clk_data, &sun4i_a10_usb_lock);
पूर्ण
CLK_OF_DECLARE(sun4i_a10_usb, "allwinner,sun4i-a10-usb-clk", sun4i_a10_usb_setup);

अटल स्थिर काष्ठा usb_clk_data sun5i_a13_usb_clk_data __initस्थिर = अणु
	.clk_mask = BIT(8) | BIT(6),
	.reset_mask = BIT(1) | BIT(0),
पूर्ण;

अटल व्योम __init sun5i_a13_usb_setup(काष्ठा device_node *node)
अणु
	sunxi_usb_clk_setup(node, &sun5i_a13_usb_clk_data, &sun4i_a10_usb_lock);
पूर्ण
CLK_OF_DECLARE(sun5i_a13_usb, "allwinner,sun5i-a13-usb-clk", sun5i_a13_usb_setup);

अटल स्थिर काष्ठा usb_clk_data sun6i_a31_usb_clk_data __initस्थिर = अणु
	.clk_mask = BIT(18) | BIT(17) | BIT(16) | BIT(10) | BIT(9) | BIT(8),
	.reset_mask = BIT(2) | BIT(1) | BIT(0),
पूर्ण;

अटल व्योम __init sun6i_a31_usb_setup(काष्ठा device_node *node)
अणु
	sunxi_usb_clk_setup(node, &sun6i_a31_usb_clk_data, &sun4i_a10_usb_lock);
पूर्ण
CLK_OF_DECLARE(sun6i_a31_usb, "allwinner,sun6i-a31-usb-clk", sun6i_a31_usb_setup);

अटल स्थिर काष्ठा usb_clk_data sun8i_a23_usb_clk_data __initस्थिर = अणु
	.clk_mask = BIT(16) | BIT(11) | BIT(10) | BIT(9) | BIT(8),
	.reset_mask = BIT(2) | BIT(1) | BIT(0),
पूर्ण;

अटल व्योम __init sun8i_a23_usb_setup(काष्ठा device_node *node)
अणु
	sunxi_usb_clk_setup(node, &sun8i_a23_usb_clk_data, &sun4i_a10_usb_lock);
पूर्ण
CLK_OF_DECLARE(sun8i_a23_usb, "allwinner,sun8i-a23-usb-clk", sun8i_a23_usb_setup);

अटल स्थिर काष्ठा usb_clk_data sun8i_h3_usb_clk_data __initस्थिर = अणु
	.clk_mask =  BIT(19) | BIT(18) | BIT(17) | BIT(16) |
		     BIT(11) | BIT(10) | BIT(9) | BIT(8),
	.reset_mask = BIT(3) | BIT(2) | BIT(1) | BIT(0),
पूर्ण;

अटल व्योम __init sun8i_h3_usb_setup(काष्ठा device_node *node)
अणु
	sunxi_usb_clk_setup(node, &sun8i_h3_usb_clk_data, &sun4i_a10_usb_lock);
पूर्ण
CLK_OF_DECLARE(sun8i_h3_usb, "allwinner,sun8i-h3-usb-clk", sun8i_h3_usb_setup);

अटल स्थिर काष्ठा usb_clk_data sun9i_a80_usb_mod_data __initस्थिर = अणु
	.clk_mask = BIT(6) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1),
	.reset_mask = BIT(19) | BIT(18) | BIT(17),
	.reset_needs_clk = 1,
पूर्ण;

अटल DEFINE_SPINLOCK(a80_usb_mod_lock);

अटल व्योम __init sun9i_a80_usb_mod_setup(काष्ठा device_node *node)
अणु
	sunxi_usb_clk_setup(node, &sun9i_a80_usb_mod_data, &a80_usb_mod_lock);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_usb_mod, "allwinner,sun9i-a80-usb-mod-clk", sun9i_a80_usb_mod_setup);

अटल स्थिर काष्ठा usb_clk_data sun9i_a80_usb_phy_data __initस्थिर = अणु
	.clk_mask = BIT(10) | BIT(5) | BIT(4) | BIT(3) | BIT(2) | BIT(1),
	.reset_mask = BIT(21) | BIT(20) | BIT(19) | BIT(18) | BIT(17),
	.reset_needs_clk = 1,
पूर्ण;

अटल DEFINE_SPINLOCK(a80_usb_phy_lock);

अटल व्योम __init sun9i_a80_usb_phy_setup(काष्ठा device_node *node)
अणु
	sunxi_usb_clk_setup(node, &sun9i_a80_usb_phy_data, &a80_usb_phy_lock);
पूर्ण
CLK_OF_DECLARE(sun9i_a80_usb_phy, "allwinner,sun9i-a80-usb-phy-clk", sun9i_a80_usb_phy_setup);
