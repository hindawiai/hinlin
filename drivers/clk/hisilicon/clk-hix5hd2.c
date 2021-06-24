<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Linaro Ltd.
 * Copyright (c) 2014 Hisilicon Limited.
 */

#समावेश <linux/of_address.h>
#समावेश <dt-bindings/घड़ी/hix5hd2-घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश "clk.h"

अटल काष्ठा hisi_fixed_rate_घड़ी hix5hd2_fixed_rate_clks[] __initdata = अणु
	अणु HIX5HD2_FIXED_1200M, "1200m", शून्य, 0, 1200000000, पूर्ण,
	अणु HIX5HD2_FIXED_400M, "400m", शून्य, 0, 400000000, पूर्ण,
	अणु HIX5HD2_FIXED_48M, "48m", शून्य, 0, 48000000, पूर्ण,
	अणु HIX5HD2_FIXED_24M, "24m", शून्य, 0, 24000000, पूर्ण,
	अणु HIX5HD2_FIXED_600M, "600m", शून्य, 0, 600000000, पूर्ण,
	अणु HIX5HD2_FIXED_300M, "300m", शून्य, 0, 300000000, पूर्ण,
	अणु HIX5HD2_FIXED_75M, "75m", शून्य, 0, 75000000, पूर्ण,
	अणु HIX5HD2_FIXED_200M, "200m", शून्य, 0, 200000000, पूर्ण,
	अणु HIX5HD2_FIXED_100M, "100m", शून्य, 0, 100000000, पूर्ण,
	अणु HIX5HD2_FIXED_40M, "40m", शून्य, 0, 40000000, पूर्ण,
	अणु HIX5HD2_FIXED_150M, "150m", शून्य, 0, 150000000, पूर्ण,
	अणु HIX5HD2_FIXED_1728M, "1728m", शून्य, 0, 1728000000, पूर्ण,
	अणु HIX5HD2_FIXED_28P8M, "28p8m", शून्य, 0, 28000000, पूर्ण,
	अणु HIX5HD2_FIXED_432M, "432m", शून्य, 0, 432000000, पूर्ण,
	अणु HIX5HD2_FIXED_345P6M, "345p6m", शून्य, 0, 345000000, पूर्ण,
	अणु HIX5HD2_FIXED_288M, "288m", शून्य, 0, 288000000, पूर्ण,
	अणु HIX5HD2_FIXED_60M,	"60m", शून्य, 0, 60000000, पूर्ण,
	अणु HIX5HD2_FIXED_750M, "750m", शून्य, 0, 750000000, पूर्ण,
	अणु HIX5HD2_FIXED_500M, "500m", शून्य, 0, 500000000, पूर्ण,
	अणु HIX5HD2_FIXED_54M,	"54m", शून्य, 0, 54000000, पूर्ण,
	अणु HIX5HD2_FIXED_27M, "27m", शून्य, 0, 27000000, पूर्ण,
	अणु HIX5HD2_FIXED_1500M, "1500m", शून्य, 0, 1500000000, पूर्ण,
	अणु HIX5HD2_FIXED_375M, "375m", शून्य, 0, 375000000, पूर्ण,
	अणु HIX5HD2_FIXED_187M, "187m", शून्य, 0, 187000000, पूर्ण,
	अणु HIX5HD2_FIXED_250M, "250m", शून्य, 0, 250000000, पूर्ण,
	अणु HIX5HD2_FIXED_125M, "125m", शून्य, 0, 125000000, पूर्ण,
	अणु HIX5HD2_FIXED_2P02M, "2m", शून्य, 0, 2000000, पूर्ण,
	अणु HIX5HD2_FIXED_50M, "50m", शून्य, 0, 50000000, पूर्ण,
	अणु HIX5HD2_FIXED_25M, "25m", शून्य, 0, 25000000, पूर्ण,
	अणु HIX5HD2_FIXED_83M, "83m", शून्य, 0, 83333333, पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *स्थिर sfc_mux_p[] __initस्थिर = अणु
		"24m", "150m", "200m", "100m", "75m", पूर्ण;
अटल u32 sfc_mux_table[] = अणु0, 4, 5, 6, 7पूर्ण;

अटल स्थिर अक्षर *स्थिर sdio_mux_p[] __initस्थिर = अणु
		"75m", "100m", "50m", "15m", पूर्ण;
अटल u32 sdio_mux_table[] = अणु0, 1, 2, 3पूर्ण;

अटल स्थिर अक्षर *स्थिर fephy_mux_p[] __initस्थिर = अणु "25m", "125m"पूर्ण;
अटल u32 fephy_mux_table[] = अणु0, 1पूर्ण;


अटल काष्ठा hisi_mux_घड़ी hix5hd2_mux_clks[] __initdata = अणु
	अणु HIX5HD2_SFC_MUX, "sfc_mux", sfc_mux_p, ARRAY_SIZE(sfc_mux_p),
		CLK_SET_RATE_PARENT, 0x5c, 8, 3, 0, sfc_mux_table, पूर्ण,
	अणु HIX5HD2_MMC_MUX, "mmc_mux", sdio_mux_p, ARRAY_SIZE(sdio_mux_p),
		CLK_SET_RATE_PARENT, 0xa0, 8, 2, 0, sdio_mux_table, पूर्ण,
	अणु HIX5HD2_SD_MUX, "sd_mux", sdio_mux_p, ARRAY_SIZE(sdio_mux_p),
		CLK_SET_RATE_PARENT, 0x9c, 8, 2, 0, sdio_mux_table, पूर्ण,
	अणु HIX5HD2_FEPHY_MUX, "fephy_mux",
		fephy_mux_p, ARRAY_SIZE(fephy_mux_p),
		CLK_SET_RATE_PARENT, 0x120, 8, 2, 0, fephy_mux_table, पूर्ण,
पूर्ण;

अटल काष्ठा hisi_gate_घड़ी hix5hd2_gate_clks[] __initdata = अणु
	/* sfc */
	अणु HIX5HD2_SFC_CLK, "clk_sfc", "sfc_mux",
		CLK_SET_RATE_PARENT, 0x5c, 0, 0, पूर्ण,
	अणु HIX5HD2_SFC_RST, "rst_sfc", "clk_sfc",
		CLK_SET_RATE_PARENT, 0x5c, 4, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	/* sdio0 */
	अणु HIX5HD2_SD_BIU_CLK, "clk_sd_biu", "200m",
		CLK_SET_RATE_PARENT, 0x9c, 0, 0, पूर्ण,
	अणु HIX5HD2_SD_CIU_CLK, "clk_sd_ciu", "sd_mux",
		CLK_SET_RATE_PARENT, 0x9c, 1, 0, पूर्ण,
	अणु HIX5HD2_SD_CIU_RST, "rst_sd_ciu", "clk_sd_ciu",
		CLK_SET_RATE_PARENT, 0x9c, 4, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	/* sdio1 */
	अणु HIX5HD2_MMC_BIU_CLK, "clk_mmc_biu", "200m",
		CLK_SET_RATE_PARENT, 0xa0, 0, 0, पूर्ण,
	अणु HIX5HD2_MMC_CIU_CLK, "clk_mmc_ciu", "mmc_mux",
		CLK_SET_RATE_PARENT, 0xa0, 1, 0, पूर्ण,
	अणु HIX5HD2_MMC_CIU_RST, "rst_mmc_ciu", "clk_mmc_ciu",
		CLK_SET_RATE_PARENT, 0xa0, 4, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	/* gsf */
	अणु HIX5HD2_FWD_BUS_CLK, "clk_fwd_bus", शून्य, 0, 0xcc, 0, 0, पूर्ण,
	अणु HIX5HD2_FWD_SYS_CLK, "clk_fwd_sys", "clk_fwd_bus", 0, 0xcc, 5, 0, पूर्ण,
	अणु HIX5HD2_MAC0_PHY_CLK, "clk_fephy", "clk_fwd_sys",
		 CLK_SET_RATE_PARENT, 0x120, 0, 0, पूर्ण,
	/* wdg0 */
	अणु HIX5HD2_WDG0_CLK, "clk_wdg0", "24m",
		CLK_SET_RATE_PARENT, 0x178, 0, 0, पूर्ण,
	अणु HIX5HD2_WDG0_RST, "rst_wdg0", "clk_wdg0",
		CLK_SET_RATE_PARENT, 0x178, 4, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	/* I2C */
	अणुHIX5HD2_I2C0_CLK, "clk_i2c0", "100m",
		 CLK_SET_RATE_PARENT, 0x06c, 4, 0, पूर्ण,
	अणुHIX5HD2_I2C0_RST, "rst_i2c0", "clk_i2c0",
		 CLK_SET_RATE_PARENT, 0x06c, 5, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	अणुHIX5HD2_I2C1_CLK, "clk_i2c1", "100m",
		 CLK_SET_RATE_PARENT, 0x06c, 8, 0, पूर्ण,
	अणुHIX5HD2_I2C1_RST, "rst_i2c1", "clk_i2c1",
		 CLK_SET_RATE_PARENT, 0x06c, 9, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	अणुHIX5HD2_I2C2_CLK, "clk_i2c2", "100m",
		 CLK_SET_RATE_PARENT, 0x06c, 12, 0, पूर्ण,
	अणुHIX5HD2_I2C2_RST, "rst_i2c2", "clk_i2c2",
		 CLK_SET_RATE_PARENT, 0x06c, 13, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	अणुHIX5HD2_I2C3_CLK, "clk_i2c3", "100m",
		 CLK_SET_RATE_PARENT, 0x06c, 16, 0, पूर्ण,
	अणुHIX5HD2_I2C3_RST, "rst_i2c3", "clk_i2c3",
		 CLK_SET_RATE_PARENT, 0x06c, 17, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	अणुHIX5HD2_I2C4_CLK, "clk_i2c4", "100m",
		 CLK_SET_RATE_PARENT, 0x06c, 20, 0, पूर्ण,
	अणुHIX5HD2_I2C4_RST, "rst_i2c4", "clk_i2c4",
		 CLK_SET_RATE_PARENT, 0x06c, 21, CLK_GATE_SET_TO_DISABLE, पूर्ण,
	अणुHIX5HD2_I2C5_CLK, "clk_i2c5", "100m",
		 CLK_SET_RATE_PARENT, 0x06c, 0, 0, पूर्ण,
	अणुHIX5HD2_I2C5_RST, "rst_i2c5", "clk_i2c5",
		 CLK_SET_RATE_PARENT, 0x06c, 1, CLK_GATE_SET_TO_DISABLE, पूर्ण,
पूर्ण;

क्रमागत hix5hd2_clk_type अणु
	TYPE_COMPLEX,
	TYPE_ETHER,
पूर्ण;

काष्ठा hix5hd2_complex_घड़ी अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*parent_name;
	u32		id;
	u32		ctrl_reg;
	u32		ctrl_clk_mask;
	u32		ctrl_rst_mask;
	u32		phy_reg;
	u32		phy_clk_mask;
	u32		phy_rst_mask;
	क्रमागत hix5hd2_clk_type type;
पूर्ण;

काष्ठा hix5hd2_clk_complex अणु
	काष्ठा clk_hw	hw;
	u32		id;
	व्योम __iomem	*ctrl_reg;
	u32		ctrl_clk_mask;
	u32		ctrl_rst_mask;
	व्योम __iomem	*phy_reg;
	u32		phy_clk_mask;
	u32		phy_rst_mask;
पूर्ण;

अटल काष्ठा hix5hd2_complex_घड़ी hix5hd2_complex_clks[] __initdata = अणु
	अणु"clk_mac0", "clk_fephy", HIX5HD2_MAC0_CLK,
		0xcc, 0xa, 0x500, 0x120, 0, 0x10, TYPE_ETHERपूर्ण,
	अणु"clk_mac1", "clk_fwd_sys", HIX5HD2_MAC1_CLK,
		0xcc, 0x14, 0xa00, 0x168, 0x2, 0, TYPE_ETHERपूर्ण,
	अणु"clk_sata", शून्य, HIX5HD2_SATA_CLK,
		0xa8, 0x1f, 0x300, 0xac, 0x1, 0x0, TYPE_COMPLEXपूर्ण,
	अणु"clk_usb", शून्य, HIX5HD2_USB_CLK,
		0xb8, 0xff, 0x3f000, 0xbc, 0x7, 0x3f00, TYPE_COMPLEXपूर्ण,
पूर्ण;

#घोषणा to_complex_clk(_hw) container_of(_hw, काष्ठा hix5hd2_clk_complex, hw)

अटल पूर्णांक clk_ether_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा hix5hd2_clk_complex *clk = to_complex_clk(hw);
	u32 val;

	val = पढ़ोl_relaxed(clk->ctrl_reg);
	val |= clk->ctrl_clk_mask | clk->ctrl_rst_mask;
	ग_लिखोl_relaxed(val, clk->ctrl_reg);
	val &= ~(clk->ctrl_rst_mask);
	ग_लिखोl_relaxed(val, clk->ctrl_reg);

	val = पढ़ोl_relaxed(clk->phy_reg);
	val |= clk->phy_clk_mask;
	val &= ~(clk->phy_rst_mask);
	ग_लिखोl_relaxed(val, clk->phy_reg);
	mdelay(10);

	val &= ~(clk->phy_clk_mask);
	val |= clk->phy_rst_mask;
	ग_लिखोl_relaxed(val, clk->phy_reg);
	mdelay(10);

	val |= clk->phy_clk_mask;
	val &= ~(clk->phy_rst_mask);
	ग_लिखोl_relaxed(val, clk->phy_reg);
	mdelay(30);
	वापस 0;
पूर्ण

अटल व्योम clk_ether_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा hix5hd2_clk_complex *clk = to_complex_clk(hw);
	u32 val;

	val = पढ़ोl_relaxed(clk->ctrl_reg);
	val &= ~(clk->ctrl_clk_mask);
	ग_लिखोl_relaxed(val, clk->ctrl_reg);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_ether_ops = अणु
	.prepare = clk_ether_prepare,
	.unprepare = clk_ether_unprepare,
पूर्ण;

अटल पूर्णांक clk_complex_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा hix5hd2_clk_complex *clk = to_complex_clk(hw);
	u32 val;

	val = पढ़ोl_relaxed(clk->ctrl_reg);
	val |= clk->ctrl_clk_mask;
	val &= ~(clk->ctrl_rst_mask);
	ग_लिखोl_relaxed(val, clk->ctrl_reg);

	val = पढ़ोl_relaxed(clk->phy_reg);
	val |= clk->phy_clk_mask;
	val &= ~(clk->phy_rst_mask);
	ग_लिखोl_relaxed(val, clk->phy_reg);

	वापस 0;
पूर्ण

अटल व्योम clk_complex_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा hix5hd2_clk_complex *clk = to_complex_clk(hw);
	u32 val;

	val = पढ़ोl_relaxed(clk->ctrl_reg);
	val |= clk->ctrl_rst_mask;
	val &= ~(clk->ctrl_clk_mask);
	ग_लिखोl_relaxed(val, clk->ctrl_reg);

	val = पढ़ोl_relaxed(clk->phy_reg);
	val |= clk->phy_rst_mask;
	val &= ~(clk->phy_clk_mask);
	ग_लिखोl_relaxed(val, clk->phy_reg);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_complex_ops = अणु
	.enable = clk_complex_enable,
	.disable = clk_complex_disable,
पूर्ण;

अटल व्योम __init
hix5hd2_clk_रेजिस्टर_complex(काष्ठा hix5hd2_complex_घड़ी *clks, पूर्णांक nums,
			     काष्ठा hisi_घड़ी_data *data)
अणु
	व्योम __iomem *base = data->base;
	पूर्णांक i;

	क्रम (i = 0; i < nums; i++) अणु
		काष्ठा hix5hd2_clk_complex *p_clk;
		काष्ठा clk *clk;
		काष्ठा clk_init_data init;

		p_clk = kzalloc(माप(*p_clk), GFP_KERNEL);
		अगर (!p_clk)
			वापस;

		init.name = clks[i].name;
		अगर (clks[i].type == TYPE_ETHER)
			init.ops = &clk_ether_ops;
		अन्यथा
			init.ops = &clk_complex_ops;

		init.flags = 0;
		init.parent_names =
			(clks[i].parent_name ? &clks[i].parent_name : शून्य);
		init.num_parents = (clks[i].parent_name ? 1 : 0);

		p_clk->ctrl_reg = base + clks[i].ctrl_reg;
		p_clk->ctrl_clk_mask = clks[i].ctrl_clk_mask;
		p_clk->ctrl_rst_mask = clks[i].ctrl_rst_mask;
		p_clk->phy_reg = base + clks[i].phy_reg;
		p_clk->phy_clk_mask = clks[i].phy_clk_mask;
		p_clk->phy_rst_mask = clks[i].phy_rst_mask;
		p_clk->hw.init = &init;

		clk = clk_रेजिस्टर(शून्य, &p_clk->hw);
		अगर (IS_ERR(clk)) अणु
			kमुक्त(p_clk);
			pr_err("%s: failed to register clock %s\n",
			       __func__, clks[i].name);
			जारी;
		पूर्ण

		data->clk_data.clks[clks[i].id] = clk;
	पूर्ण
पूर्ण

अटल व्योम __init hix5hd2_clk_init(काष्ठा device_node *np)
अणु
	काष्ठा hisi_घड़ी_data *clk_data;

	clk_data = hisi_clk_init(np, HIX5HD2_NR_CLKS);
	अगर (!clk_data)
		वापस;

	hisi_clk_रेजिस्टर_fixed_rate(hix5hd2_fixed_rate_clks,
				     ARRAY_SIZE(hix5hd2_fixed_rate_clks),
				     clk_data);
	hisi_clk_रेजिस्टर_mux(hix5hd2_mux_clks, ARRAY_SIZE(hix5hd2_mux_clks),
					clk_data);
	hisi_clk_रेजिस्टर_gate(hix5hd2_gate_clks,
			ARRAY_SIZE(hix5hd2_gate_clks), clk_data);
	hix5hd2_clk_रेजिस्टर_complex(hix5hd2_complex_clks,
				     ARRAY_SIZE(hix5hd2_complex_clks),
				     clk_data);
पूर्ण

CLK_OF_DECLARE(hix5hd2_clk, "hisilicon,hix5hd2-clock", hix5hd2_clk_init);
