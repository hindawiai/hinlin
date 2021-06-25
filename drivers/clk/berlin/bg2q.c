<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/berlin2q.h>

#समावेश "berlin2-div.h"
#समावेश "berlin2-pll.h"
#समावेश "common.h"

#घोषणा REG_PINMUX0		0x0018
#घोषणा REG_PINMUX5		0x002c
#घोषणा REG_SYSPLLCTL0		0x0030
#घोषणा REG_SYSPLLCTL4		0x0040
#घोषणा REG_CLKENABLE		0x00e8
#घोषणा REG_CLKSELECT0		0x00ec
#घोषणा REG_CLKSELECT1		0x00f0
#घोषणा REG_CLKSELECT2		0x00f4
#घोषणा REG_CLKSWITCH0		0x00f8
#घोषणा REG_CLKSWITCH1		0x00fc
#घोषणा REG_SW_GENERIC0		0x0110
#घोषणा REG_SW_GENERIC3		0x011c
#घोषणा REG_SDIO0XIN_CLKCTL	0x0158
#घोषणा REG_SDIO1XIN_CLKCTL	0x015c

#घोषणा	MAX_CLKS 28
अटल काष्ठा clk_hw_onecell_data *clk_data;
अटल DEFINE_SPINLOCK(lock);
अटल व्योम __iomem *gbase;
अटल व्योम __iomem *cpupll_base;

क्रमागत अणु
	REFCLK,
	SYSPLL, CPUPLL,
	AVPLL_B1, AVPLL_B2, AVPLL_B3, AVPLL_B4,
	AVPLL_B5, AVPLL_B6, AVPLL_B7, AVPLL_B8,
पूर्ण;

अटल स्थिर अक्षर *clk_names[] = अणु
	[REFCLK]		= "refclk",
	[SYSPLL]		= "syspll",
	[CPUPLL]		= "cpupll",
	[AVPLL_B1]		= "avpll_b1",
	[AVPLL_B2]		= "avpll_b2",
	[AVPLL_B3]		= "avpll_b3",
	[AVPLL_B4]		= "avpll_b4",
	[AVPLL_B5]		= "avpll_b5",
	[AVPLL_B6]		= "avpll_b6",
	[AVPLL_B7]		= "avpll_b7",
	[AVPLL_B8]		= "avpll_b8",
पूर्ण;

अटल स्थिर काष्ठा berlin2_pll_map bg2q_pll_map __initस्थिर = अणु
	.vcoभाग		= अणु1, 0, 2, 0, 3, 4, 0, 6, 8पूर्ण,
	.mult		= 1,
	.fbभाग_shअगरt	= 7,
	.rfभाग_shअगरt	= 2,
	.भागsel_shअगरt	= 9,
पूर्ण;

अटल स्थिर u8 शेष_parent_ids[] = अणु
	SYSPLL, AVPLL_B4, AVPLL_B5, AVPLL_B6, AVPLL_B7, SYSPLL
पूर्ण;

अटल स्थिर काष्ठा berlin2_भाग_data bg2q_भागs[] __initस्थिर = अणु
	अणु
		.name = "sys",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 0),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 0),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 3),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 3),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 4),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 5),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	अणु
		.name = "drmfigo",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 17),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 6),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 9),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 6),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 7),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 8),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "cfg",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 1),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 12),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 15),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 9),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 10),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 11),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "gfx2d",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 4),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 18),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 21),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 12),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 13),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 14),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "zsp",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 6),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 24),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 27),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 15),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 16),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 17),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "perif",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 7),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 0),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 3),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 18),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 19),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 20),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	अणु
		.name = "pcube",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 2),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 6),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 9),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 21),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 22),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 23),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "vscope",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 3),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 12),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 15),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 24),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 25),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 26),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "nfc_ecc",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 19),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 18),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 21),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 27),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 28),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 29),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "vpp",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 21),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 24),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 27),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 30),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 31),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 0),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "app",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 20),
			BERLIN2_PLL_SELECT(REG_CLKSELECT2, 0),
			BERLIN2_DIV_SELECT(REG_CLKSELECT2, 3),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH1, 1),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 2),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 3),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "sdio0xin",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_SDIO0XIN_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "sdio1xin",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_SDIO1XIN_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा berlin2_gate_data bg2q_gates[] __initस्थिर = अणु
	अणु "gfx2daxi",	"perif",	5 पूर्ण,
	अणु "geth0",	"perif",	8 पूर्ण,
	अणु "sata",	"perif",	9 पूर्ण,
	अणु "ahbapb",	"perif",	10, CLK_IGNORE_UNUSED पूर्ण,
	अणु "usb0",	"perif",	11 पूर्ण,
	अणु "usb1",	"perif",	12 पूर्ण,
	अणु "usb2",	"perif",	13 पूर्ण,
	अणु "usb3",	"perif",	14 पूर्ण,
	अणु "pbridge",	"perif",	15, CLK_IGNORE_UNUSED पूर्ण,
	अणु "sdio",	"perif",	16 पूर्ण,
	अणु "nfc",	"perif",	18 पूर्ण,
	अणु "pcie",	"perif",	22 पूर्ण,
पूर्ण;

अटल व्योम __init berlin2q_घड़ी_setup(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent_np = of_get_parent(np);
	स्थिर अक्षर *parent_names[9];
	काष्ठा clk *clk;
	काष्ठा clk_hw **hws;
	पूर्णांक n, ret;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, MAX_CLKS), GFP_KERNEL);
	अगर (!clk_data)
		वापस;
	clk_data->num = MAX_CLKS;
	hws = clk_data->hws;

	gbase = of_iomap(parent_np, 0);
	अगर (!gbase) अणु
		pr_err("%pOF: Unable to map global base\n", np);
		वापस;
	पूर्ण

	/* BG2Q CPU PLL is not part of global रेजिस्टरs */
	cpupll_base = of_iomap(parent_np, 1);
	अगर (!cpupll_base) अणु
		pr_err("%pOF: Unable to map cpupll base\n", np);
		iounmap(gbase);
		वापस;
	पूर्ण

	/* overग_लिखो शेष घड़ी names with DT provided ones */
	clk = of_clk_get_by_name(np, clk_names[REFCLK]);
	अगर (!IS_ERR(clk)) अणु
		clk_names[REFCLK] = __clk_get_name(clk);
		clk_put(clk);
	पूर्ण

	/* simple रेजिस्टर PLLs */
	ret = berlin2_pll_रेजिस्टर(&bg2q_pll_map, gbase + REG_SYSPLLCTL0,
				   clk_names[SYSPLL], clk_names[REFCLK], 0);
	अगर (ret)
		जाओ bg2q_fail;

	ret = berlin2_pll_रेजिस्टर(&bg2q_pll_map, cpupll_base,
				   clk_names[CPUPLL], clk_names[REFCLK], 0);
	अगर (ret)
		जाओ bg2q_fail;

	/* TODO: add BG2Q AVPLL */

	/*
	 * TODO: add reference घड़ी bypass चयनes:
	 * memPLLSWBypass, cpuPLLSWBypass, and sysPLLSWBypass
	 */

	/* घड़ी भागider cells */
	क्रम (n = 0; n < ARRAY_SIZE(bg2q_भागs); n++) अणु
		स्थिर काष्ठा berlin2_भाग_data *dd = &bg2q_भागs[n];
		पूर्णांक k;

		क्रम (k = 0; k < dd->num_parents; k++)
			parent_names[k] = clk_names[dd->parent_ids[k]];

		hws[CLKID_SYS + n] = berlin2_भाग_रेजिस्टर(&dd->map, gbase,
				dd->name, dd->भाग_flags, parent_names,
				dd->num_parents, dd->flags, &lock);
	पूर्ण

	/* घड़ी gate cells */
	क्रम (n = 0; n < ARRAY_SIZE(bg2q_gates); n++) अणु
		स्थिर काष्ठा berlin2_gate_data *gd = &bg2q_gates[n];

		hws[CLKID_GFX2DAXI + n] = clk_hw_रेजिस्टर_gate(शून्य, gd->name,
			    gd->parent_name, gd->flags, gbase + REG_CLKENABLE,
			    gd->bit_idx, 0, &lock);
	पूर्ण

	/* cpuclk भागider is fixed to 1 */
	hws[CLKID_CPU] =
		clk_hw_रेजिस्टर_fixed_factor(शून्य, "cpu", clk_names[CPUPLL],
					  0, 1, 1);
	/* twdclk is derived from cpu/3 */
	hws[CLKID_TWD] =
		clk_hw_रेजिस्टर_fixed_factor(शून्य, "twd", "cpu", 0, 1, 3);

	/* check क्रम errors on leaf घड़ीs */
	क्रम (n = 0; n < MAX_CLKS; n++) अणु
		अगर (!IS_ERR(hws[n]))
			जारी;

		pr_err("%pOF: Unable to register leaf clock %d\n", np, n);
		जाओ bg2q_fail;
	पूर्ण

	/* रेजिस्टर clk-provider */
	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);

	वापस;

bg2q_fail:
	iounmap(cpupll_base);
	iounmap(gbase);
पूर्ण
CLK_OF_DECLARE(berlin2q_clk, "marvell,berlin2q-clk",
	       berlin2q_घड़ी_setup);
