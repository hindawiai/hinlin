<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Emilio Lथकpez
 * Emilio Lथकpez <emilio@elopez.com.ar>
 *
 * Copyright 2013 Chen-Yu Tsai
 * Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

अटल DEFINE_SPINLOCK(gmac_lock);

/**
 * sun7i_a20_gmac_clk_setup - Setup function क्रम A20/A31 GMAC घड़ी module
 *
 * This घड़ी looks something like this
 *                               ________________________
 *  MII TX घड़ी from PHY >-----|___________    _________|----> to GMAC core
 *  GMAC Int. RGMII TX clk >----|___________\__/__gate---|----> to PHY
 *  Ext. 125MHz RGMII TX clk >--|__भागider__/            |
 *                              |________________________|
 *
 * The बाह्यal 125 MHz reference is optional, i.e. GMAC can use its
 * पूर्णांकernal TX घड़ी just fine. The A31 GMAC घड़ी module करोes not have
 * the भागider controls क्रम the बाह्यal reference.
 *
 * To keep it simple, let the GMAC use either the MII TX घड़ी क्रम MII mode,
 * and its पूर्णांकernal TX घड़ी क्रम GMII and RGMII modes. The GMAC driver should
 * select the appropriate source and gate/ungate the output to the PHY.
 *
 * Only the GMAC should use this घड़ी. Altering the घड़ी so that it करोesn't
 * match the GMAC's operation parameters will result in the GMAC not being
 * able to send traffic out. The GMAC driver should set the घड़ी rate and
 * enable/disable this घड़ी to configure the required state. The घड़ी
 * driver then responds by स्वतः-reparenting the घड़ी.
 */

#घोषणा SUN7I_A20_GMAC_GPIT	2
#घोषणा SUN7I_A20_GMAC_MASK	0x3
#घोषणा SUN7I_A20_GMAC_PARENTS	2

अटल u32 sun7i_a20_gmac_mux_table[SUN7I_A20_GMAC_PARENTS] = अणु
	0x00, /* Select mii_phy_tx_clk */
	0x02, /* Select gmac_पूर्णांक_tx_clk */
पूर्ण;

अटल व्योम __init sun7i_a20_gmac_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	काष्ठा clk_mux *mux;
	काष्ठा clk_gate *gate;
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parents[SUN7I_A20_GMAC_PARENTS];
	व्योम __iomem *reg;

	अगर (of_property_पढ़ो_string(node, "clock-output-names", &clk_name))
		वापस;

	/* allocate mux and gate घड़ी काष्ठाs */
	mux = kzalloc(माप(काष्ठा clk_mux), GFP_KERNEL);
	अगर (!mux)
		वापस;

	gate = kzalloc(माप(काष्ठा clk_gate), GFP_KERNEL);
	अगर (!gate)
		जाओ मुक्त_mux;

	/* gmac घड़ी requires exactly 2 parents */
	अगर (of_clk_parent_fill(node, parents, 2) != 2)
		जाओ मुक्त_gate;

	reg = of_iomap(node, 0);
	अगर (!reg)
		जाओ मुक्त_gate;

	/* set up gate and fixed rate properties */
	gate->reg = reg;
	gate->bit_idx = SUN7I_A20_GMAC_GPIT;
	gate->lock = &gmac_lock;
	mux->reg = reg;
	mux->mask = SUN7I_A20_GMAC_MASK;
	mux->table = sun7i_a20_gmac_mux_table;
	mux->lock = &gmac_lock;

	clk = clk_रेजिस्टर_composite(शून्य, clk_name,
			parents, SUN7I_A20_GMAC_PARENTS,
			&mux->hw, &clk_mux_ops,
			शून्य, शून्य,
			&gate->hw, &clk_gate_ops,
			0);

	अगर (IS_ERR(clk))
		जाओ iounmap_reg;

	of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस;

iounmap_reg:
	iounmap(reg);
मुक्त_gate:
	kमुक्त(gate);
मुक्त_mux:
	kमुक्त(mux);
पूर्ण
CLK_OF_DECLARE(sun7i_a20_gmac, "allwinner,sun7i-a20-gmac-clk",
		sun7i_a20_gmac_clk_setup);
