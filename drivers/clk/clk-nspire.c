<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2013 Daniel Tang <tangrs@tangrs.id.au>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#घोषणा MHZ (1000 * 1000)

#घोषणा BASE_CPU_SHIFT		1
#घोषणा BASE_CPU_MASK		0x7F

#घोषणा CPU_AHB_SHIFT		12
#घोषणा CPU_AHB_MASK		0x07

#घोषणा FIXED_BASE_SHIFT	8
#घोषणा FIXED_BASE_MASK		0x01

#घोषणा CLASSIC_BASE_SHIFT	16
#घोषणा CLASSIC_BASE_MASK	0x1F

#घोषणा CX_BASE_SHIFT		15
#घोषणा CX_BASE_MASK		0x3F

#घोषणा CX_UNKNOWN_SHIFT	21
#घोषणा CX_UNKNOWN_MASK		0x03

काष्ठा nspire_clk_info अणु
	u32 base_घड़ी;
	u16 base_cpu_ratio;
	u16 base_ahb_ratio;
पूर्ण;


#घोषणा EXTRACT(var, prop) (((var)>>prop##_SHIFT) & prop##_MASK)
अटल व्योम nspire_clkinfo_cx(u32 val, काष्ठा nspire_clk_info *clk)
अणु
	अगर (EXTRACT(val, FIXED_BASE))
		clk->base_घड़ी = 48 * MHZ;
	अन्यथा
		clk->base_घड़ी = 6 * EXTRACT(val, CX_BASE) * MHZ;

	clk->base_cpu_ratio = EXTRACT(val, BASE_CPU) * EXTRACT(val, CX_UNKNOWN);
	clk->base_ahb_ratio = clk->base_cpu_ratio * (EXTRACT(val, CPU_AHB) + 1);
पूर्ण

अटल व्योम nspire_clkinfo_classic(u32 val, काष्ठा nspire_clk_info *clk)
अणु
	अगर (EXTRACT(val, FIXED_BASE))
		clk->base_घड़ी = 27 * MHZ;
	अन्यथा
		clk->base_घड़ी = (300 - 6 * EXTRACT(val, CLASSIC_BASE)) * MHZ;

	clk->base_cpu_ratio = EXTRACT(val, BASE_CPU) * 2;
	clk->base_ahb_ratio = clk->base_cpu_ratio * (EXTRACT(val, CPU_AHB) + 1);
पूर्ण

अटल व्योम __init nspire_ahbभाग_setup(काष्ठा device_node *node,
		व्योम (*get_clkinfo)(u32, काष्ठा nspire_clk_info *))
अणु
	u32 val;
	व्योम __iomem *io;
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	काष्ठा nspire_clk_info info;

	io = of_iomap(node, 0);
	अगर (!io)
		वापस;
	val = पढ़ोl(io);
	iounmap(io);

	get_clkinfo(val, &info);

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	parent_name = of_clk_get_parent_name(node, 0);

	hw = clk_hw_रेजिस्टर_fixed_factor(शून्य, clk_name, parent_name, 0,
					  1, info.base_ahb_ratio);
	अगर (!IS_ERR(hw))
		of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
पूर्ण

अटल व्योम __init nspire_ahbभाग_setup_cx(काष्ठा device_node *node)
अणु
	nspire_ahbभाग_setup(node, nspire_clkinfo_cx);
पूर्ण

अटल व्योम __init nspire_ahbभाग_setup_classic(काष्ठा device_node *node)
अणु
	nspire_ahbभाग_setup(node, nspire_clkinfo_classic);
पूर्ण

CLK_OF_DECLARE(nspire_ahbभाग_cx, "lsi,nspire-cx-ahb-divider",
		nspire_ahbभाग_setup_cx);
CLK_OF_DECLARE(nspire_ahbभाग_classic, "lsi,nspire-classic-ahb-divider",
		nspire_ahbभाग_setup_classic);

अटल व्योम __init nspire_clk_setup(काष्ठा device_node *node,
		व्योम (*get_clkinfo)(u32, काष्ठा nspire_clk_info *))
अणु
	u32 val;
	व्योम __iomem *io;
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = node->name;
	काष्ठा nspire_clk_info info;

	io = of_iomap(node, 0);
	अगर (!io)
		वापस;
	val = पढ़ोl(io);
	iounmap(io);

	get_clkinfo(val, &info);

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	hw = clk_hw_रेजिस्टर_fixed_rate(शून्य, clk_name, शून्य, 0,
					info.base_घड़ी);
	अगर (!IS_ERR(hw))
		of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
	अन्यथा
		वापस;

	pr_info("TI-NSPIRE Base: %uMHz CPU: %uMHz AHB: %uMHz\n",
		info.base_घड़ी / MHZ,
		info.base_घड़ी / info.base_cpu_ratio / MHZ,
		info.base_घड़ी / info.base_ahb_ratio / MHZ);
पूर्ण

अटल व्योम __init nspire_clk_setup_cx(काष्ठा device_node *node)
अणु
	nspire_clk_setup(node, nspire_clkinfo_cx);
पूर्ण

अटल व्योम __init nspire_clk_setup_classic(काष्ठा device_node *node)
अणु
	nspire_clk_setup(node, nspire_clkinfo_classic);
पूर्ण

CLK_OF_DECLARE(nspire_clk_cx, "lsi,nspire-cx-clock", nspire_clk_setup_cx);
CLK_OF_DECLARE(nspire_clk_classic, "lsi,nspire-classic-clock",
		nspire_clk_setup_classic);
