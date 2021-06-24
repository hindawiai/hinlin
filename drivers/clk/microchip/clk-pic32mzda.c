<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Purna Chandra Mandal,<purna.mandal@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <dt-bindings/घड़ी/microchip,pic32-घड़ी.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/traps.h>

#समावेश "clk-core.h"

/* FRC Postscaler */
#घोषणा OSC_FRCDIV_MASK		0x07
#घोषणा OSC_FRCDIV_SHIFT	24

/* SPLL fields */
#घोषणा PLL_ICLK_MASK		0x01
#घोषणा PLL_ICLK_SHIFT		7

#घोषणा DECLARE_PERIPHERAL_CLOCK(__clk_name, __reg, __flags)	\
	अणु							\
		.ctrl_reg = (__reg),				\
		.init_data = अणु					\
			.name = (__clk_name),			\
			.parent_names = (स्थिर अक्षर *[]) अणु	\
				"sys_clk"			\
			पूर्ण,					\
			.num_parents = 1,			\
			.ops = &pic32_pbclk_ops,		\
			.flags = (__flags),			\
		पूर्ण,						\
	पूर्ण

#घोषणा DECLARE_REFO_CLOCK(__clkid, __reg)				\
	अणु								\
		.ctrl_reg = (__reg),					\
		.init_data = अणु						\
			.name = "refo" #__clkid "_clk",			\
			.parent_names = (स्थिर अक्षर *[]) अणु		\
				"sys_clk", "pb1_clk", "posc_clk",	\
				"frc_clk", "lprc_clk", "sosc_clk",	\
				"sys_pll", "refi" #__clkid "_clk",	\
				"bfrc_clk",				\
			पूर्ण,						\
			.num_parents = 9,				\
			.flags = CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE,\
			.ops = &pic32_roclk_ops,			\
		पूर्ण,							\
		.parent_map = (स्थिर u32[]) अणु				\
			0, 1, 2, 3, 4, 5, 7, 8, 9			\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा pic32_ref_osc_data ref_clks[] = अणु
	DECLARE_REFO_CLOCK(1, 0x80),
	DECLARE_REFO_CLOCK(2, 0xa0),
	DECLARE_REFO_CLOCK(3, 0xc0),
	DECLARE_REFO_CLOCK(4, 0xe0),
	DECLARE_REFO_CLOCK(5, 0x100),
पूर्ण;

अटल स्थिर काष्ठा pic32_periph_clk_data periph_घड़ीs[] = अणु
	DECLARE_PERIPHERAL_CLOCK("pb1_clk", 0x140, 0),
	DECLARE_PERIPHERAL_CLOCK("pb2_clk", 0x150, CLK_IGNORE_UNUSED),
	DECLARE_PERIPHERAL_CLOCK("pb3_clk", 0x160, 0),
	DECLARE_PERIPHERAL_CLOCK("pb4_clk", 0x170, 0),
	DECLARE_PERIPHERAL_CLOCK("pb5_clk", 0x180, 0),
	DECLARE_PERIPHERAL_CLOCK("pb6_clk", 0x190, 0),
	DECLARE_PERIPHERAL_CLOCK("cpu_clk", 0x1a0, CLK_IGNORE_UNUSED),
पूर्ण;

अटल स्थिर काष्ठा pic32_sys_clk_data sys_mux_clk = अणु
	.slew_reg = 0x1c0,
	.slew_भाग = 2, /* step of भाग_4 -> भाग_2 -> no_भाग */
	.init_data = अणु
		.name = "sys_clk",
		.parent_names = (स्थिर अक्षर *[]) अणु
			"frcdiv_clk", "sys_pll", "posc_clk",
			"sosc_clk", "lprc_clk", "frcdiv_clk",
		पूर्ण,
		.num_parents = 6,
		.ops = &pic32_sclk_ops,
	पूर्ण,
	.parent_map = (स्थिर u32[]) अणु
		0, 1, 2, 4, 5, 7,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pic32_sys_pll_data sys_pll = अणु
	.ctrl_reg = 0x020,
	.status_reg = 0x1d0,
	.lock_mask = BIT(7),
	.init_data = अणु
		.name = "sys_pll",
		.parent_names = (स्थिर अक्षर *[]) अणु
			"spll_mux_clk"
		पूर्ण,
		.num_parents = 1,
		.ops = &pic32_spll_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pic32_sec_osc_data sosc_clk = अणु
	.status_reg = 0x1d0,
	.enable_mask = BIT(1),
	.status_mask = BIT(4),
	.fixed_rate = 32768,
	.init_data = अणु
		.name = "sosc_clk",
		.parent_names = शून्य,
		.ops = &pic32_sosc_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक pic32mzda_critical_clks[] = अणु
	PB2CLK, PB7CLK
पूर्ण;

/* PIC32MZDA घड़ी data */
काष्ठा pic32mzda_clk_data अणु
	काष्ठा clk *clks[MAXCLKS];
	काष्ठा pic32_clk_common core;
	काष्ठा clk_onecell_data onecell_data;
	काष्ठा notअगरier_block failsafe_notअगरier;
पूर्ण;

अटल पूर्णांक pic32_fscm_nmi(काष्ठा notअगरier_block *nb,
			  अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा pic32mzda_clk_data *cd;

	cd  = container_of(nb, काष्ठा pic32mzda_clk_data, failsafe_notअगरier);

	/* SYSCLK is now running from BFRCCLK. Report घड़ी failure. */
	अगर (पढ़ोl(cd->core.iobase) & BIT(2))
		pr_alert("pic32-clk: FSCM detected clk failure.\n");

	/* TODO: detect reason of failure and recover accordingly */

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक pic32mzda_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *स्थिर pll_mux_parents[] = अणु"posc_clk", "frc_clk"पूर्ण;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा pic32mzda_clk_data *cd;
	काष्ठा pic32_clk_common *core;
	काष्ठा clk *pll_mux_clk, *clk;
	काष्ठा clk **clks;
	पूर्णांक nr_clks, i, ret;

	cd = devm_kzalloc(&pdev->dev, माप(*cd), GFP_KERNEL);
	अगर (!cd)
		वापस -ENOMEM;

	core = &cd->core;
	core->iobase = of_io_request_and_map(np, 0, of_node_full_name(np));
	अगर (IS_ERR(core->iobase)) अणु
		dev_err(&pdev->dev, "pic32-clk: failed to map registers\n");
		वापस PTR_ERR(core->iobase);
	पूर्ण

	spin_lock_init(&core->reg_lock);
	core->dev = &pdev->dev;
	clks = &cd->clks[0];

	/* रेजिस्टर fixed rate घड़ीs */
	clks[POSCCLK] = clk_रेजिस्टर_fixed_rate(&pdev->dev, "posc_clk", शून्य,
						0, 24000000);
	clks[FRCCLK] =  clk_रेजिस्टर_fixed_rate(&pdev->dev, "frc_clk", शून्य,
						0, 8000000);
	clks[BFRCCLK] = clk_रेजिस्टर_fixed_rate(&pdev->dev, "bfrc_clk", शून्य,
						0, 8000000);
	clks[LPRCCLK] = clk_रेजिस्टर_fixed_rate(&pdev->dev, "lprc_clk", शून्य,
						0, 32000);
	clks[UPLLCLK] = clk_रेजिस्टर_fixed_rate(&pdev->dev, "usbphy_clk", शून्य,
						0, 24000000);
	/* fixed rate (optional) घड़ी */
	अगर (of_find_property(np, "microchip,pic32mzda-sosc", शून्य)) अणु
		pr_info("pic32-clk: dt requests SOSC.\n");
		clks[SOSCCLK] = pic32_sosc_clk_रेजिस्टर(&sosc_clk, core);
	पूर्ण
	/* भागider घड़ी */
	clks[FRCDIVCLK] = clk_रेजिस्टर_भागider(&pdev->dev, "frcdiv_clk",
					       "frc_clk", 0,
					       core->iobase,
					       OSC_FRCDIV_SHIFT,
					       OSC_FRCDIV_MASK,
					       CLK_DIVIDER_POWER_OF_TWO,
					       &core->reg_lock);
	/* PLL ICLK mux */
	pll_mux_clk = clk_रेजिस्टर_mux(&pdev->dev, "spll_mux_clk",
				       pll_mux_parents, 2, 0,
				       core->iobase + 0x020,
				       PLL_ICLK_SHIFT, 1, 0, &core->reg_lock);
	अगर (IS_ERR(pll_mux_clk))
		pr_err("spll_mux_clk: clk register failed\n");

	/* PLL */
	clks[PLLCLK] = pic32_spll_clk_रेजिस्टर(&sys_pll, core);
	/* SYSTEM घड़ी */
	clks[SCLK] = pic32_sys_clk_रेजिस्टर(&sys_mux_clk, core);
	/* Peripheral bus घड़ीs */
	क्रम (nr_clks = PB1CLK, i = 0; nr_clks <= PB7CLK; i++, nr_clks++)
		clks[nr_clks] = pic32_periph_clk_रेजिस्टर(&periph_घड़ीs[i],
							  core);
	/* Reference oscillator घड़ी */
	क्रम (nr_clks = REF1CLK, i = 0; nr_clks <= REF5CLK; i++, nr_clks++)
		clks[nr_clks] = pic32_refo_clk_रेजिस्टर(&ref_clks[i], core);

	/* रेजिस्टर clkdev */
	क्रम (i = 0; i < MAXCLKS; i++) अणु
		अगर (IS_ERR(clks[i]))
			जारी;
		clk_रेजिस्टर_clkdev(clks[i], शून्य, __clk_get_name(clks[i]));
	पूर्ण

	/* रेजिस्टर घड़ी provider */
	cd->onecell_data.clks = clks;
	cd->onecell_data.clk_num = MAXCLKS;
	ret = of_clk_add_provider(np, of_clk_src_onecell_get,
				  &cd->onecell_data);
	अगर (ret)
		वापस ret;

	/* क्रमce enable critical घड़ीs */
	क्रम (i = 0; i < ARRAY_SIZE(pic32mzda_critical_clks); i++) अणु
		clk = clks[pic32mzda_critical_clks[i]];
		अगर (clk_prepare_enable(clk))
			dev_err(&pdev->dev, "clk_prepare_enable(%s) failed\n",
				__clk_get_name(clk));
	पूर्ण

	/* रेजिस्टर NMI क्रम failsafe घड़ी monitor */
	cd->failsafe_notअगरier.notअगरier_call = pic32_fscm_nmi;
	वापस रेजिस्टर_nmi_notअगरier(&cd->failsafe_notअगरier);
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32mzda_clk_match_table[] = अणु
	अणु .compatible = "microchip,pic32mzda-clk", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32mzda_clk_match_table);

अटल काष्ठा platक्रमm_driver pic32mzda_clk_driver = अणु
	.probe		= pic32mzda_clk_probe,
	.driver		= अणु
		.name	= "clk-pic32mzda",
		.of_match_table = pic32mzda_clk_match_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init microchip_pic32mzda_clk_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pic32mzda_clk_driver);
पूर्ण
core_initcall(microchip_pic32mzda_clk_init);

MODULE_DESCRIPTION("Microchip PIC32MZDA Clock Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:clk-pic32mzda");
