<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * घड़ी framework क्रम AMD Stoney based घड़ीs
 *
 * Copyright 2018 Advanced Micro Devices, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/platक्रमm_data/clk-fch.h>
#समावेश <linux/platक्रमm_device.h>

/* Clock Driving Strength 2 रेजिस्टर */
#घोषणा CLKDRVSTR2	0x28
/* Clock Control 1 रेजिस्टर */
#घोषणा MISCCLKCNTL1	0x40
/* Auxiliary घड़ी1 enable bit */
#घोषणा OSCCLKENB	2
/* 25Mhz auxiliary output घड़ी freq bit */
#घोषणा OSCOUT1CLK25MHZ	16

#घोषणा ST_CLK_48M	0
#घोषणा ST_CLK_25M	1
#घोषणा ST_CLK_MUX	2
#घोषणा ST_CLK_GATE	3
#घोषणा ST_MAX_CLKS	4

#घोषणा RV_CLK_48M	0
#घोषणा RV_CLK_GATE	1
#घोषणा RV_MAX_CLKS	2

अटल स्थिर अक्षर * स्थिर clk_oscout1_parents[] = अणु "clk48MHz", "clk25MHz" पूर्ण;
अटल काष्ठा clk_hw *hws[ST_MAX_CLKS];

अटल पूर्णांक fch_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fch_clk_data *fch_data;

	fch_data = dev_get_platdata(&pdev->dev);
	अगर (!fch_data || !fch_data->base)
		वापस -EINVAL;

	अगर (!fch_data->is_rv) अणु
		hws[ST_CLK_48M] = clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk48MHz",
			शून्य, 0, 48000000);
		hws[ST_CLK_25M] = clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk25MHz",
			शून्य, 0, 25000000);

		hws[ST_CLK_MUX] = clk_hw_रेजिस्टर_mux(शून्य, "oscout1_mux",
			clk_oscout1_parents, ARRAY_SIZE(clk_oscout1_parents),
			0, fch_data->base + CLKDRVSTR2, OSCOUT1CLK25MHZ, 3, 0,
			शून्य);

		clk_set_parent(hws[ST_CLK_MUX]->clk, hws[ST_CLK_48M]->clk);

		hws[ST_CLK_GATE] = clk_hw_रेजिस्टर_gate(शून्य, "oscout1",
			"oscout1_mux", 0, fch_data->base + MISCCLKCNTL1,
			OSCCLKENB, CLK_GATE_SET_TO_DISABLE, शून्य);

		devm_clk_hw_रेजिस्टर_clkdev(&pdev->dev, hws[ST_CLK_GATE],
			"oscout1", शून्य);
	पूर्ण अन्यथा अणु
		hws[RV_CLK_48M] = clk_hw_रेजिस्टर_fixed_rate(शून्य, "clk48MHz",
			शून्य, 0, 48000000);

		hws[RV_CLK_GATE] = clk_hw_रेजिस्टर_gate(शून्य, "oscout1",
			"clk48MHz", 0, fch_data->base + MISCCLKCNTL1,
			OSCCLKENB, CLK_GATE_SET_TO_DISABLE, शून्य);

		devm_clk_hw_रेजिस्टर_clkdev(&pdev->dev, hws[RV_CLK_GATE],
			"oscout1", शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fch_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, clks;
	काष्ठा fch_clk_data *fch_data;

	fch_data = dev_get_platdata(&pdev->dev);

	clks = fch_data->is_rv ? RV_MAX_CLKS : ST_MAX_CLKS;

	क्रम (i = 0; i < clks; i++)
		clk_hw_unरेजिस्टर(hws[i]);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver fch_clk_driver = अणु
	.driver = अणु
		.name = "clk-fch",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = fch_clk_probe,
	.हटाओ = fch_clk_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(fch_clk_driver);
