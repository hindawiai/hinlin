<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARTPEC-6 घड़ी initialization
 *
 * Copyright 2015-2016 Axis Comunications AB.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <dt-bindings/घड़ी/axis,artpec6-clkctrl.h>

#घोषणा NUM_I2S_CLOCKS 2

काष्ठा artpec6_clkctrl_drvdata अणु
	काष्ठा clk *clk_table[ARTPEC6_CLK_NUMCLOCKS];
	व्योम __iomem *syscon_base;
	काष्ठा clk_onecell_data clk_data;
	spinlock_t i2scfg_lock;
पूर्ण;

अटल काष्ठा artpec6_clkctrl_drvdata *clkdata;

अटल स्थिर अक्षर *स्थिर i2s_clk_names[NUM_I2S_CLOCKS] = अणु
	"i2s0",
	"i2s1",
पूर्ण;

अटल स्थिर पूर्णांक i2s_clk_indexes[NUM_I2S_CLOCKS] = अणु
	ARTPEC6_CLK_I2S0_CLK,
	ARTPEC6_CLK_I2S1_CLK,
पूर्ण;

अटल व्योम of_artpec6_clkctrl_setup(काष्ठा device_node *np)
अणु
	पूर्णांक i;
	स्थिर अक्षर *sys_refclk_name;
	u32 pll_mode, pll_m, pll_n;
	काष्ठा clk **clks;

	/* Mandatory parent घड़ी. */
	i = of_property_match_string(np, "clock-names", "sys_refclk");
	अगर (i < 0)
		वापस;

	sys_refclk_name = of_clk_get_parent_name(np, i);

	clkdata = kzalloc(माप(*clkdata), GFP_KERNEL);
	अगर (!clkdata)
		वापस;

	clks = clkdata->clk_table;

	क्रम (i = 0; i < ARTPEC6_CLK_NUMCLOCKS; ++i)
		clks[i] = ERR_PTR(-EPROBE_DEFER);

	clkdata->syscon_base = of_iomap(np, 0);
	BUG_ON(clkdata->syscon_base == शून्य);

	/* Read PLL1 factors configured by boot strap pins. */
	pll_mode = (पढ़ोl(clkdata->syscon_base) >> 6) & 3;
	चयन (pll_mode) अणु
	हाल 0:		/* DDR3-2133 mode */
		pll_m = 4;
		pll_n = 85;
		अवरोध;
	हाल 1:		/* DDR3-1866 mode */
		pll_m = 6;
		pll_n = 112;
		अवरोध;
	हाल 2:		/* DDR3-1600 mode */
		pll_m = 4;
		pll_n = 64;
		अवरोध;
	हाल 3:		/* DDR3-1333 mode */
		pll_m = 8;
		pll_n = 106;
		अवरोध;
	पूर्ण

	clks[ARTPEC6_CLK_CPU] =
	    clk_रेजिस्टर_fixed_factor(शून्य, "cpu", sys_refclk_name, 0, pll_n,
				      pll_m);
	clks[ARTPEC6_CLK_CPU_PERIPH] =
	    clk_रेजिस्टर_fixed_factor(शून्य, "cpu_periph", "cpu", 0, 1, 2);

	/* EPROBE_DEFER on the apb_घड़ी is not handled in amba devices. */
	clks[ARTPEC6_CLK_UART_PCLK] =
	    clk_रेजिस्टर_fixed_factor(शून्य, "uart_pclk", "cpu", 0, 1, 8);
	clks[ARTPEC6_CLK_UART_REFCLK] =
	    clk_रेजिस्टर_fixed_rate(शून्य, "uart_ref", sys_refclk_name, 0,
				    50000000);

	clks[ARTPEC6_CLK_SPI_PCLK] =
	    clk_रेजिस्टर_fixed_factor(शून्य, "spi_pclk", "cpu", 0, 1, 8);
	clks[ARTPEC6_CLK_SPI_SSPCLK] =
	    clk_रेजिस्टर_fixed_rate(शून्य, "spi_sspclk", sys_refclk_name, 0,
				    50000000);

	clks[ARTPEC6_CLK_DBG_PCLK] =
	    clk_रेजिस्टर_fixed_factor(शून्य, "dbg_pclk", "cpu", 0, 1, 8);

	clkdata->clk_data.clks = clkdata->clk_table;
	clkdata->clk_data.clk_num = ARTPEC6_CLK_NUMCLOCKS;

	of_clk_add_provider(np, of_clk_src_onecell_get, &clkdata->clk_data);
पूर्ण

CLK_OF_DECLARE_DRIVER(artpec6_clkctrl, "axis,artpec6-clkctrl",
		      of_artpec6_clkctrl_setup);

अटल पूर्णांक artpec6_clkctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक propidx;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा clk **clks = clkdata->clk_table;
	स्थिर अक्षर *sys_refclk_name;
	स्थिर अक्षर *i2s_refclk_name = शून्य;
	स्थिर अक्षर *frac_clk_name[2] = अणु शून्य, शून्य पूर्ण;
	स्थिर अक्षर *i2s_mux_parents[2];
	u32 muxreg;
	पूर्णांक i;
	पूर्णांक err = 0;

	/* Mandatory parent घड़ी. */
	propidx = of_property_match_string(np, "clock-names", "sys_refclk");
	अगर (propidx < 0)
		वापस -EINVAL;

	sys_refclk_name = of_clk_get_parent_name(np, propidx);

	/* Find घड़ी names of optional parent घड़ीs. */
	propidx = of_property_match_string(np, "clock-names", "i2s_refclk");
	अगर (propidx >= 0)
		i2s_refclk_name = of_clk_get_parent_name(np, propidx);

	propidx = of_property_match_string(np, "clock-names", "frac_clk0");
	अगर (propidx >= 0)
		frac_clk_name[0] = of_clk_get_parent_name(np, propidx);
	propidx = of_property_match_string(np, "clock-names", "frac_clk1");
	अगर (propidx >= 0)
		frac_clk_name[1] = of_clk_get_parent_name(np, propidx);

	spin_lock_init(&clkdata->i2scfg_lock);

	clks[ARTPEC6_CLK_न_अंकD_CLKA] =
	    clk_रेजिस्टर_fixed_factor(dev, "nand_clka", "cpu", 0, 1, 8);
	clks[ARTPEC6_CLK_न_अंकD_CLKB] =
	    clk_रेजिस्टर_fixed_rate(dev, "nand_clkb", sys_refclk_name, 0,
				    100000000);
	clks[ARTPEC6_CLK_ETH_ACLK] =
	    clk_रेजिस्टर_fixed_factor(dev, "eth_aclk", "cpu", 0, 1, 4);
	clks[ARTPEC6_CLK_DMA_ACLK] =
	    clk_रेजिस्टर_fixed_factor(dev, "dma_aclk", "cpu", 0, 1, 4);
	clks[ARTPEC6_CLK_PTP_REF] =
	    clk_रेजिस्टर_fixed_rate(dev, "ptp_ref", sys_refclk_name, 0,
				    100000000);
	clks[ARTPEC6_CLK_SD_PCLK] =
	    clk_रेजिस्टर_fixed_rate(dev, "sd_pclk", sys_refclk_name, 0,
				    100000000);
	clks[ARTPEC6_CLK_SD_IMCLK] =
	    clk_रेजिस्टर_fixed_rate(dev, "sd_imclk", sys_refclk_name, 0,
				    100000000);
	clks[ARTPEC6_CLK_I2S_HST] =
	    clk_रेजिस्टर_fixed_factor(dev, "i2s_hst", "cpu", 0, 1, 8);

	क्रम (i = 0; i < NUM_I2S_CLOCKS; ++i) अणु
		अगर (i2s_refclk_name && frac_clk_name[i]) अणु
			i2s_mux_parents[0] = frac_clk_name[i];
			i2s_mux_parents[1] = i2s_refclk_name;

			clks[i2s_clk_indexes[i]] =
			    clk_रेजिस्टर_mux(dev, i2s_clk_names[i],
					     i2s_mux_parents, 2,
					     CLK_SET_RATE_NO_REPARENT |
					     CLK_SET_RATE_PARENT,
					     clkdata->syscon_base + 0x14, i, 1,
					     0, &clkdata->i2scfg_lock);
		पूर्ण अन्यथा अगर (frac_clk_name[i]) अणु
			/* Lock the mux क्रम पूर्णांकernal घड़ी reference. */
			muxreg = पढ़ोl(clkdata->syscon_base + 0x14);
			muxreg &= ~BIT(i);
			ग_लिखोl(muxreg, clkdata->syscon_base + 0x14);
			clks[i2s_clk_indexes[i]] =
			    clk_रेजिस्टर_fixed_factor(dev, i2s_clk_names[i],
						      frac_clk_name[i], 0, 1,
						      1);
		पूर्ण अन्यथा अगर (i2s_refclk_name) अणु
			/* Lock the mux क्रम बाह्यal घड़ी reference. */
			muxreg = पढ़ोl(clkdata->syscon_base + 0x14);
			muxreg |= BIT(i);
			ग_लिखोl(muxreg, clkdata->syscon_base + 0x14);
			clks[i2s_clk_indexes[i]] =
			    clk_रेजिस्टर_fixed_factor(dev, i2s_clk_names[i],
						      i2s_refclk_name, 0, 1, 1);
		पूर्ण
	पूर्ण

	clks[ARTPEC6_CLK_I2C] =
	    clk_रेजिस्टर_fixed_rate(dev, "i2c", sys_refclk_name, 0, 100000000);

	clks[ARTPEC6_CLK_SYS_TIMER] =
	    clk_रेजिस्टर_fixed_rate(dev, "timer", sys_refclk_name, 0,
				    100000000);
	clks[ARTPEC6_CLK_FRACDIV_IN] =
	    clk_रेजिस्टर_fixed_rate(dev, "fracdiv_in", sys_refclk_name, 0,
				    600000000);

	क्रम (i = 0; i < ARTPEC6_CLK_NUMCLOCKS; ++i) अणु
		अगर (IS_ERR(clks[i]) && PTR_ERR(clks[i]) != -EPROBE_DEFER) अणु
			dev_err(dev,
				"Failed to register clock at index %d err=%ld\n",
				i, PTR_ERR(clks[i]));
			err = PTR_ERR(clks[i]);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id artpec_clkctrl_of_match[] = अणु
	अणु .compatible = "axis,artpec6-clkctrl" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver artpec6_clkctrl_driver = अणु
	.probe = artpec6_clkctrl_probe,
	.driver = अणु
		   .name = "artpec6_clkctrl",
		   .of_match_table = artpec_clkctrl_of_match,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(artpec6_clkctrl_driver);
