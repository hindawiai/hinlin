<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/**
 * Wrapper driver क्रम SERDES used in J721E
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <dt-bindings/phy/phy.h>
#समावेश <dt-bindings/phy/phy-ti.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#घोषणा WIZ_SERDES_CTRL		0x404
#घोषणा WIZ_SERDES_TOP_CTRL	0x408
#घोषणा WIZ_SERDES_RST		0x40c
#घोषणा WIZ_SERDES_TYPEC	0x410
#घोषणा WIZ_LANECTL(n)		(0x480 + (0x40 * (n)))
#घोषणा WIZ_LANEDIV(n)		(0x484 + (0x40 * (n)))

#घोषणा WIZ_MAX_INPUT_CLOCKS	4
/* To include mux घड़ीs, भागider घड़ीs and gate घड़ीs */
#घोषणा WIZ_MAX_OUTPUT_CLOCKS	32

#घोषणा WIZ_MAX_LANES		4
#घोषणा WIZ_MUX_NUM_CLOCKS	3
#घोषणा WIZ_DIV_NUM_CLOCKS_16G	2
#घोषणा WIZ_DIV_NUM_CLOCKS_10G	1

#घोषणा WIZ_SERDES_TYPEC_LN10_SWAP	BIT(30)

क्रमागत wiz_lane_standard_mode अणु
	LANE_MODE_GEN1,
	LANE_MODE_GEN2,
	LANE_MODE_GEN3,
	LANE_MODE_GEN4,
पूर्ण;

क्रमागत wiz_refclk_mux_sel अणु
	PLL0_REFCLK,
	PLL1_REFCLK,
	REFCLK_DIG,
पूर्ण;

क्रमागत wiz_refclk_भाग_sel अणु
	CMN_REFCLK_DIG_DIV,
	CMN_REFCLK1_DIG_DIV,
पूर्ण;

क्रमागत wiz_घड़ी_input अणु
	WIZ_CORE_REFCLK,
	WIZ_EXT_REFCLK,
	WIZ_CORE_REFCLK1,
	WIZ_EXT_REFCLK1,
पूर्ण;

अटल स्थिर काष्ठा reg_field por_en = REG_FIELD(WIZ_SERDES_CTRL, 31, 31);
अटल स्थिर काष्ठा reg_field phy_reset_n = REG_FIELD(WIZ_SERDES_RST, 31, 31);
अटल स्थिर काष्ठा reg_field phy_en_refclk = REG_FIELD(WIZ_SERDES_RST, 30, 30);
अटल स्थिर काष्ठा reg_field pll1_refclk_mux_sel =
					REG_FIELD(WIZ_SERDES_RST, 29, 29);
अटल स्थिर काष्ठा reg_field pll0_refclk_mux_sel =
					REG_FIELD(WIZ_SERDES_RST, 28, 28);
अटल स्थिर काष्ठा reg_field refclk_dig_sel_16g =
					REG_FIELD(WIZ_SERDES_RST, 24, 25);
अटल स्थिर काष्ठा reg_field refclk_dig_sel_10g =
					REG_FIELD(WIZ_SERDES_RST, 24, 24);
अटल स्थिर काष्ठा reg_field pma_cmn_refclk_पूर्णांक_mode =
					REG_FIELD(WIZ_SERDES_TOP_CTRL, 28, 29);
अटल स्थिर काष्ठा reg_field pma_cmn_refclk_mode =
					REG_FIELD(WIZ_SERDES_TOP_CTRL, 30, 31);
अटल स्थिर काष्ठा reg_field pma_cmn_refclk_dig_भाग =
					REG_FIELD(WIZ_SERDES_TOP_CTRL, 26, 27);
अटल स्थिर काष्ठा reg_field pma_cmn_refclk1_dig_भाग =
					REG_FIELD(WIZ_SERDES_TOP_CTRL, 24, 25);
अटल स्थिर अक्षर * स्थिर output_clk_names[] = अणु
	[TI_WIZ_PLL0_REFCLK] = "pll0-refclk",
	[TI_WIZ_PLL1_REFCLK] = "pll1-refclk",
	[TI_WIZ_REFCLK_DIG] = "refclk-dig",
	[TI_WIZ_PHY_EN_REFCLK] = "phy-en-refclk",
पूर्ण;

अटल स्थिर काष्ठा reg_field p_enable[WIZ_MAX_LANES] = अणु
	REG_FIELD(WIZ_LANECTL(0), 30, 31),
	REG_FIELD(WIZ_LANECTL(1), 30, 31),
	REG_FIELD(WIZ_LANECTL(2), 30, 31),
	REG_FIELD(WIZ_LANECTL(3), 30, 31),
पूर्ण;

क्रमागत p_enable अणु P_ENABLE = 2, P_ENABLE_FORCE = 1, P_ENABLE_DISABLE = 0 पूर्ण;

अटल स्थिर काष्ठा reg_field p_align[WIZ_MAX_LANES] = अणु
	REG_FIELD(WIZ_LANECTL(0), 29, 29),
	REG_FIELD(WIZ_LANECTL(1), 29, 29),
	REG_FIELD(WIZ_LANECTL(2), 29, 29),
	REG_FIELD(WIZ_LANECTL(3), 29, 29),
पूर्ण;

अटल स्थिर काष्ठा reg_field p_raw_स्वतः_start[WIZ_MAX_LANES] = अणु
	REG_FIELD(WIZ_LANECTL(0), 28, 28),
	REG_FIELD(WIZ_LANECTL(1), 28, 28),
	REG_FIELD(WIZ_LANECTL(2), 28, 28),
	REG_FIELD(WIZ_LANECTL(3), 28, 28),
पूर्ण;

अटल स्थिर काष्ठा reg_field p_standard_mode[WIZ_MAX_LANES] = अणु
	REG_FIELD(WIZ_LANECTL(0), 24, 25),
	REG_FIELD(WIZ_LANECTL(1), 24, 25),
	REG_FIELD(WIZ_LANECTL(2), 24, 25),
	REG_FIELD(WIZ_LANECTL(3), 24, 25),
पूर्ण;

अटल स्थिर काष्ठा reg_field p0_fullrt_भाग[WIZ_MAX_LANES] = अणु
	REG_FIELD(WIZ_LANECTL(0), 22, 23),
	REG_FIELD(WIZ_LANECTL(1), 22, 23),
	REG_FIELD(WIZ_LANECTL(2), 22, 23),
	REG_FIELD(WIZ_LANECTL(3), 22, 23),
पूर्ण;

अटल स्थिर काष्ठा reg_field p_mac_भाग_sel0[WIZ_MAX_LANES] = अणु
	REG_FIELD(WIZ_LANEDIV(0), 16, 22),
	REG_FIELD(WIZ_LANEDIV(1), 16, 22),
	REG_FIELD(WIZ_LANEDIV(2), 16, 22),
	REG_FIELD(WIZ_LANEDIV(3), 16, 22),
पूर्ण;

अटल स्थिर काष्ठा reg_field p_mac_भाग_sel1[WIZ_MAX_LANES] = अणु
	REG_FIELD(WIZ_LANEDIV(0), 0, 8),
	REG_FIELD(WIZ_LANEDIV(1), 0, 8),
	REG_FIELD(WIZ_LANEDIV(2), 0, 8),
	REG_FIELD(WIZ_LANEDIV(3), 0, 8),
पूर्ण;

अटल स्थिर काष्ठा reg_field typec_ln10_swap =
					REG_FIELD(WIZ_SERDES_TYPEC, 30, 30);

काष्ठा wiz_clk_mux अणु
	काष्ठा clk_hw		hw;
	काष्ठा regmap_field	*field;
	स्थिर u32		*table;
	काष्ठा clk_init_data	clk_data;
पूर्ण;

#घोषणा to_wiz_clk_mux(_hw) container_of(_hw, काष्ठा wiz_clk_mux, hw)

काष्ठा wiz_clk_भागider अणु
	काष्ठा clk_hw		hw;
	काष्ठा regmap_field	*field;
	स्थिर काष्ठा clk_भाग_प्रकारable	*table;
	काष्ठा clk_init_data	clk_data;
पूर्ण;

#घोषणा to_wiz_clk_भाग(_hw) container_of(_hw, काष्ठा wiz_clk_भागider, hw)

काष्ठा wiz_clk_mux_sel अणु
	u32			table[WIZ_MAX_INPUT_CLOCKS];
	स्थिर अक्षर		*node_name;
	u32			num_parents;
	u32			parents[WIZ_MAX_INPUT_CLOCKS];
पूर्ण;

काष्ठा wiz_clk_भाग_sel अणु
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
	स्थिर अक्षर		*node_name;
पूर्ण;

काष्ठा wiz_phy_en_refclk अणु
	काष्ठा clk_hw		hw;
	काष्ठा regmap_field	*phy_en_refclk;
	काष्ठा clk_init_data	clk_data;
पूर्ण;

#घोषणा to_wiz_phy_en_refclk(_hw) container_of(_hw, काष्ठा wiz_phy_en_refclk, hw)

अटल स्थिर काष्ठा wiz_clk_mux_sel clk_mux_sel_16g[] = अणु
	अणु
		/*
		 * Mux value to be configured क्रम each of the input घड़ीs
		 * in the order populated in device tree
		 */
		.table = अणु 1, 0 पूर्ण,
		.node_name = "pll0-refclk",
	पूर्ण,
	अणु
		.table = अणु 1, 0 पूर्ण,
		.node_name = "pll1-refclk",
	पूर्ण,
	अणु
		.table = अणु 1, 3, 0, 2 पूर्ण,
		.node_name = "refclk-dig",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wiz_clk_mux_sel clk_mux_sel_10g[] = अणु
	अणु
		/*
		 * Mux value to be configured क्रम each of the input घड़ीs
		 * in the order populated in device tree
		 */
		.num_parents = 2,
		.parents = अणु WIZ_CORE_REFCLK, WIZ_EXT_REFCLK पूर्ण,
		.table = अणु 1, 0 पूर्ण,
		.node_name = "pll0-refclk",
	पूर्ण,
	अणु
		.num_parents = 2,
		.parents = अणु WIZ_CORE_REFCLK, WIZ_EXT_REFCLK पूर्ण,
		.table = अणु 1, 0 पूर्ण,
		.node_name = "pll1-refclk",
	पूर्ण,
	अणु
		.num_parents = 2,
		.parents = अणु WIZ_CORE_REFCLK, WIZ_EXT_REFCLK पूर्ण,
		.table = अणु 1, 0 पूर्ण,
		.node_name = "refclk-dig",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable clk_भाग_प्रकारable[] = अणु
	अणु .val = 0, .भाग = 1, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 2, .भाग = 4, पूर्ण,
	अणु .val = 3, .भाग = 8, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wiz_clk_भाग_sel clk_भाग_sel[] = अणु
	अणु
		.table = clk_भाग_प्रकारable,
		.node_name = "cmn-refclk-dig-div",
	पूर्ण,
	अणु
		.table = clk_भाग_प्रकारable,
		.node_name = "cmn-refclk1-dig-div",
	पूर्ण,
पूर्ण;

क्रमागत wiz_type अणु
	J721E_WIZ_16G,
	J721E_WIZ_10G,
	AM64_WIZ_10G,
पूर्ण;

#घोषणा WIZ_TYPEC_सूची_DEBOUNCE_MIN	100	/* ms */
#घोषणा WIZ_TYPEC_सूची_DEBOUNCE_MAX	1000

काष्ठा wiz अणु
	काष्ठा regmap		*regmap;
	क्रमागत wiz_type		type;
	स्थिर काष्ठा wiz_clk_mux_sel *clk_mux_sel;
	स्थिर काष्ठा wiz_clk_भाग_sel *clk_भाग_sel;
	अचिन्हित पूर्णांक		clk_भाग_sel_num;
	काष्ठा regmap_field	*por_en;
	काष्ठा regmap_field	*phy_reset_n;
	काष्ठा regmap_field	*phy_en_refclk;
	काष्ठा regmap_field	*p_enable[WIZ_MAX_LANES];
	काष्ठा regmap_field	*p_align[WIZ_MAX_LANES];
	काष्ठा regmap_field	*p_raw_स्वतः_start[WIZ_MAX_LANES];
	काष्ठा regmap_field	*p_standard_mode[WIZ_MAX_LANES];
	काष्ठा regmap_field	*p_mac_भाग_sel0[WIZ_MAX_LANES];
	काष्ठा regmap_field	*p_mac_भाग_sel1[WIZ_MAX_LANES];
	काष्ठा regmap_field	*p0_fullrt_भाग[WIZ_MAX_LANES];
	काष्ठा regmap_field	*pma_cmn_refclk_पूर्णांक_mode;
	काष्ठा regmap_field	*pma_cmn_refclk_mode;
	काष्ठा regmap_field	*pma_cmn_refclk_dig_भाग;
	काष्ठा regmap_field	*pma_cmn_refclk1_dig_भाग;
	काष्ठा regmap_field	*mux_sel_field[WIZ_MUX_NUM_CLOCKS];
	काष्ठा regmap_field	*भाग_sel_field[WIZ_DIV_NUM_CLOCKS_16G];
	काष्ठा regmap_field	*typec_ln10_swap;

	काष्ठा device		*dev;
	u32			num_lanes;
	काष्ठा platक्रमm_device	*serdes_pdev;
	काष्ठा reset_controller_dev wiz_phy_reset_dev;
	काष्ठा gpio_desc	*gpio_typec_dir;
	पूर्णांक			typec_dir_delay;
	u32 lane_phy_type[WIZ_MAX_LANES];
	काष्ठा clk		*input_clks[WIZ_MAX_INPUT_CLOCKS];
	काष्ठा clk		*output_clks[WIZ_MAX_OUTPUT_CLOCKS];
	काष्ठा clk_onecell_data	clk_data;
पूर्ण;

अटल पूर्णांक wiz_reset(काष्ठा wiz *wiz)
अणु
	पूर्णांक ret;

	ret = regmap_field_ग_लिखो(wiz->por_en, 0x1);
	अगर (ret)
		वापस ret;

	mdelay(1);

	ret = regmap_field_ग_लिखो(wiz->por_en, 0x0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_p_mac_भाग_sel(काष्ठा wiz *wiz)
अणु
	u32 num_lanes = wiz->num_lanes;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < num_lanes; i++) अणु
		अगर (wiz->lane_phy_type[i] == PHY_TYPE_QSGMII) अणु
			ret = regmap_field_ग_लिखो(wiz->p_mac_भाग_sel0[i], 1);
			अगर (ret)
				वापस ret;

			ret = regmap_field_ग_लिखो(wiz->p_mac_भाग_sel1[i], 2);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_mode_select(काष्ठा wiz *wiz)
अणु
	u32 num_lanes = wiz->num_lanes;
	क्रमागत wiz_lane_standard_mode mode;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < num_lanes; i++) अणु
		अगर (wiz->lane_phy_type[i] == PHY_TYPE_DP)
			mode = LANE_MODE_GEN1;
		अन्यथा अगर (wiz->lane_phy_type[i] == PHY_TYPE_QSGMII)
			mode = LANE_MODE_GEN2;
		अन्यथा
			जारी;

		ret = regmap_field_ग_लिखो(wiz->p_standard_mode[i], mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_init_raw_पूर्णांकerface(काष्ठा wiz *wiz, bool enable)
अणु
	u32 num_lanes = wiz->num_lanes;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < num_lanes; i++) अणु
		ret = regmap_field_ग_लिखो(wiz->p_align[i], enable);
		अगर (ret)
			वापस ret;

		ret = regmap_field_ग_लिखो(wiz->p_raw_स्वतः_start[i], enable);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_init(काष्ठा wiz *wiz)
अणु
	काष्ठा device *dev = wiz->dev;
	पूर्णांक ret;

	ret = wiz_reset(wiz);
	अगर (ret) अणु
		dev_err(dev, "WIZ reset failed\n");
		वापस ret;
	पूर्ण

	ret = wiz_mode_select(wiz);
	अगर (ret) अणु
		dev_err(dev, "WIZ mode select failed\n");
		वापस ret;
	पूर्ण

	ret = wiz_p_mac_भाग_sel(wiz);
	अगर (ret) अणु
		dev_err(dev, "Configuring P0 MAC DIV SEL failed\n");
		वापस ret;
	पूर्ण

	ret = wiz_init_raw_पूर्णांकerface(wiz, true);
	अगर (ret) अणु
		dev_err(dev, "WIZ interface initialization failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_regfield_init(काष्ठा wiz *wiz)
अणु
	काष्ठा regmap *regmap = wiz->regmap;
	पूर्णांक num_lanes = wiz->num_lanes;
	काष्ठा device *dev = wiz->dev;
	पूर्णांक i;

	wiz->por_en = devm_regmap_field_alloc(dev, regmap, por_en);
	अगर (IS_ERR(wiz->por_en)) अणु
		dev_err(dev, "POR_EN reg field init failed\n");
		वापस PTR_ERR(wiz->por_en);
	पूर्ण

	wiz->phy_reset_n = devm_regmap_field_alloc(dev, regmap,
						   phy_reset_n);
	अगर (IS_ERR(wiz->phy_reset_n)) अणु
		dev_err(dev, "PHY_RESET_N reg field init failed\n");
		वापस PTR_ERR(wiz->phy_reset_n);
	पूर्ण

	wiz->pma_cmn_refclk_पूर्णांक_mode =
		devm_regmap_field_alloc(dev, regmap, pma_cmn_refclk_पूर्णांक_mode);
	अगर (IS_ERR(wiz->pma_cmn_refclk_पूर्णांक_mode)) अणु
		dev_err(dev, "PMA_CMN_REFCLK_INT_MODE reg field init failed\n");
		वापस PTR_ERR(wiz->pma_cmn_refclk_पूर्णांक_mode);
	पूर्ण

	wiz->pma_cmn_refclk_mode =
		devm_regmap_field_alloc(dev, regmap, pma_cmn_refclk_mode);
	अगर (IS_ERR(wiz->pma_cmn_refclk_mode)) अणु
		dev_err(dev, "PMA_CMN_REFCLK_MODE reg field init failed\n");
		वापस PTR_ERR(wiz->pma_cmn_refclk_mode);
	पूर्ण

	wiz->भाग_sel_field[CMN_REFCLK_DIG_DIV] =
		devm_regmap_field_alloc(dev, regmap, pma_cmn_refclk_dig_भाग);
	अगर (IS_ERR(wiz->भाग_sel_field[CMN_REFCLK_DIG_DIV])) अणु
		dev_err(dev, "PMA_CMN_REFCLK_DIG_DIV reg field init failed\n");
		वापस PTR_ERR(wiz->भाग_sel_field[CMN_REFCLK_DIG_DIV]);
	पूर्ण

	अगर (wiz->type == J721E_WIZ_16G) अणु
		wiz->भाग_sel_field[CMN_REFCLK1_DIG_DIV] =
			devm_regmap_field_alloc(dev, regmap,
						pma_cmn_refclk1_dig_भाग);
		अगर (IS_ERR(wiz->भाग_sel_field[CMN_REFCLK1_DIG_DIV])) अणु
			dev_err(dev, "PMA_CMN_REFCLK1_DIG_DIV reg field init failed\n");
			वापस PTR_ERR(wiz->भाग_sel_field[CMN_REFCLK1_DIG_DIV]);
		पूर्ण
	पूर्ण

	wiz->mux_sel_field[PLL0_REFCLK] =
		devm_regmap_field_alloc(dev, regmap, pll0_refclk_mux_sel);
	अगर (IS_ERR(wiz->mux_sel_field[PLL0_REFCLK])) अणु
		dev_err(dev, "PLL0_REFCLK_SEL reg field init failed\n");
		वापस PTR_ERR(wiz->mux_sel_field[PLL0_REFCLK]);
	पूर्ण

	wiz->mux_sel_field[PLL1_REFCLK] =
		devm_regmap_field_alloc(dev, regmap, pll1_refclk_mux_sel);
	अगर (IS_ERR(wiz->mux_sel_field[PLL1_REFCLK])) अणु
		dev_err(dev, "PLL1_REFCLK_SEL reg field init failed\n");
		वापस PTR_ERR(wiz->mux_sel_field[PLL1_REFCLK]);
	पूर्ण

	अगर (wiz->type == J721E_WIZ_10G || wiz->type == AM64_WIZ_10G)
		wiz->mux_sel_field[REFCLK_DIG] =
			devm_regmap_field_alloc(dev, regmap,
						refclk_dig_sel_10g);
	अन्यथा
		wiz->mux_sel_field[REFCLK_DIG] =
			devm_regmap_field_alloc(dev, regmap,
						refclk_dig_sel_16g);

	अगर (IS_ERR(wiz->mux_sel_field[REFCLK_DIG])) अणु
		dev_err(dev, "REFCLK_DIG_SEL reg field init failed\n");
		वापस PTR_ERR(wiz->mux_sel_field[REFCLK_DIG]);
	पूर्ण

	क्रम (i = 0; i < num_lanes; i++) अणु
		wiz->p_enable[i] = devm_regmap_field_alloc(dev, regmap,
							   p_enable[i]);
		अगर (IS_ERR(wiz->p_enable[i])) अणु
			dev_err(dev, "P%d_ENABLE reg field init failed\n", i);
			वापस PTR_ERR(wiz->p_enable[i]);
		पूर्ण

		wiz->p_align[i] = devm_regmap_field_alloc(dev, regmap,
							  p_align[i]);
		अगर (IS_ERR(wiz->p_align[i])) अणु
			dev_err(dev, "P%d_ALIGN reg field init failed\n", i);
			वापस PTR_ERR(wiz->p_align[i]);
		पूर्ण

		wiz->p_raw_स्वतः_start[i] =
		  devm_regmap_field_alloc(dev, regmap, p_raw_स्वतः_start[i]);
		अगर (IS_ERR(wiz->p_raw_स्वतः_start[i])) अणु
			dev_err(dev, "P%d_RAW_AUTO_START reg field init fail\n",
				i);
			वापस PTR_ERR(wiz->p_raw_स्वतः_start[i]);
		पूर्ण

		wiz->p_standard_mode[i] =
		  devm_regmap_field_alloc(dev, regmap, p_standard_mode[i]);
		अगर (IS_ERR(wiz->p_standard_mode[i])) अणु
			dev_err(dev, "P%d_STANDARD_MODE reg field init fail\n",
				i);
			वापस PTR_ERR(wiz->p_standard_mode[i]);
		पूर्ण

		wiz->p0_fullrt_भाग[i] = devm_regmap_field_alloc(dev, regmap, p0_fullrt_भाग[i]);
		अगर (IS_ERR(wiz->p0_fullrt_भाग[i])) अणु
			dev_err(dev, "P%d_FULLRT_DIV reg field init failed\n", i);
			वापस PTR_ERR(wiz->p0_fullrt_भाग[i]);
		पूर्ण

		wiz->p_mac_भाग_sel0[i] =
		  devm_regmap_field_alloc(dev, regmap, p_mac_भाग_sel0[i]);
		अगर (IS_ERR(wiz->p_mac_भाग_sel0[i])) अणु
			dev_err(dev, "P%d_MAC_DIV_SEL0 reg field init fail\n",
				i);
			वापस PTR_ERR(wiz->p_mac_भाग_sel0[i]);
		पूर्ण

		wiz->p_mac_भाग_sel1[i] =
		  devm_regmap_field_alloc(dev, regmap, p_mac_भाग_sel1[i]);
		अगर (IS_ERR(wiz->p_mac_भाग_sel1[i])) अणु
			dev_err(dev, "P%d_MAC_DIV_SEL1 reg field init fail\n",
				i);
			वापस PTR_ERR(wiz->p_mac_भाग_sel1[i]);
		पूर्ण
	पूर्ण

	wiz->typec_ln10_swap = devm_regmap_field_alloc(dev, regmap,
						       typec_ln10_swap);
	अगर (IS_ERR(wiz->typec_ln10_swap)) अणु
		dev_err(dev, "LN10_SWAP reg field init failed\n");
		वापस PTR_ERR(wiz->typec_ln10_swap);
	पूर्ण

	wiz->phy_en_refclk = devm_regmap_field_alloc(dev, regmap, phy_en_refclk);
	अगर (IS_ERR(wiz->phy_en_refclk)) अणु
		dev_err(dev, "PHY_EN_REFCLK reg field init failed\n");
		वापस PTR_ERR(wiz->phy_en_refclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_phy_en_refclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा wiz_phy_en_refclk *wiz_phy_en_refclk = to_wiz_phy_en_refclk(hw);
	काष्ठा regmap_field *phy_en_refclk = wiz_phy_en_refclk->phy_en_refclk;

	regmap_field_ग_लिखो(phy_en_refclk, 1);

	वापस 0;
पूर्ण

अटल व्योम wiz_phy_en_refclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा wiz_phy_en_refclk *wiz_phy_en_refclk = to_wiz_phy_en_refclk(hw);
	काष्ठा regmap_field *phy_en_refclk = wiz_phy_en_refclk->phy_en_refclk;

	regmap_field_ग_लिखो(phy_en_refclk, 0);
पूर्ण

अटल पूर्णांक wiz_phy_en_refclk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा wiz_phy_en_refclk *wiz_phy_en_refclk = to_wiz_phy_en_refclk(hw);
	काष्ठा regmap_field *phy_en_refclk = wiz_phy_en_refclk->phy_en_refclk;
	पूर्णांक val;

	regmap_field_पढ़ो(phy_en_refclk, &val);

	वापस !!val;
पूर्ण

अटल स्थिर काष्ठा clk_ops wiz_phy_en_refclk_ops = अणु
	.enable = wiz_phy_en_refclk_enable,
	.disable = wiz_phy_en_refclk_disable,
	.is_enabled = wiz_phy_en_refclk_is_enabled,
पूर्ण;

अटल पूर्णांक wiz_phy_en_refclk_रेजिस्टर(काष्ठा wiz *wiz)
अणु
	काष्ठा wiz_phy_en_refclk *wiz_phy_en_refclk;
	काष्ठा device *dev = wiz->dev;
	काष्ठा clk_init_data *init;
	काष्ठा clk *clk;

	wiz_phy_en_refclk = devm_kzalloc(dev, माप(*wiz_phy_en_refclk), GFP_KERNEL);
	अगर (!wiz_phy_en_refclk)
		वापस -ENOMEM;

	init = &wiz_phy_en_refclk->clk_data;

	init->ops = &wiz_phy_en_refclk_ops;
	init->flags = 0;
	init->name = output_clk_names[TI_WIZ_PHY_EN_REFCLK];

	wiz_phy_en_refclk->phy_en_refclk = wiz->phy_en_refclk;
	wiz_phy_en_refclk->hw.init = init;

	clk = devm_clk_रेजिस्टर(dev, &wiz_phy_en_refclk->hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	wiz->output_clks[TI_WIZ_PHY_EN_REFCLK] = clk;

	वापस 0;
पूर्ण

अटल u8 wiz_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा wiz_clk_mux *mux = to_wiz_clk_mux(hw);
	काष्ठा regmap_field *field = mux->field;
	अचिन्हित पूर्णांक val;

	regmap_field_पढ़ो(field, &val);
	वापस clk_mux_val_to_index(hw, (u32 *)mux->table, 0, val);
पूर्ण

अटल पूर्णांक wiz_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा wiz_clk_mux *mux = to_wiz_clk_mux(hw);
	काष्ठा regmap_field *field = mux->field;
	पूर्णांक val;

	val = mux->table[index];
	वापस regmap_field_ग_लिखो(field, val);
पूर्ण

अटल स्थिर काष्ठा clk_ops wiz_clk_mux_ops = अणु
	.set_parent = wiz_clk_mux_set_parent,
	.get_parent = wiz_clk_mux_get_parent,
पूर्ण;

अटल पूर्णांक wiz_mux_clk_रेजिस्टर(काष्ठा wiz *wiz, काष्ठा regmap_field *field,
				स्थिर काष्ठा wiz_clk_mux_sel *mux_sel, पूर्णांक clk_index)
अणु
	काष्ठा device *dev = wiz->dev;
	काष्ठा clk_init_data *init;
	स्थिर अक्षर **parent_names;
	अचिन्हित पूर्णांक num_parents;
	काष्ठा wiz_clk_mux *mux;
	अक्षर clk_name[100];
	काष्ठा clk *clk;
	पूर्णांक ret = 0, i;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	num_parents = mux_sel->num_parents;

	parent_names = kzalloc((माप(अक्षर *) * num_parents), GFP_KERNEL);
	अगर (!parent_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_parents; i++) अणु
		clk = wiz->input_clks[mux_sel->parents[i]];
		अगर (IS_ERR_OR_शून्य(clk)) अणु
			dev_err(dev, "Failed to get parent clk for %s\n",
				output_clk_names[clk_index]);
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		parent_names[i] = __clk_get_name(clk);
	पूर्ण

	snम_लिखो(clk_name, माप(clk_name), "%s_%s", dev_name(dev), output_clk_names[clk_index]);

	init = &mux->clk_data;

	init->ops = &wiz_clk_mux_ops;
	init->flags = CLK_SET_RATE_NO_REPARENT;
	init->parent_names = parent_names;
	init->num_parents = num_parents;
	init->name = clk_name;

	mux->field = field;
	mux->table = mux_sel->table;
	mux->hw.init = init;

	clk = devm_clk_रेजिस्टर(dev, &mux->hw);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		जाओ err;
	पूर्ण

	wiz->output_clks[clk_index] = clk;

err:
	kमुक्त(parent_names);

	वापस ret;
पूर्ण

अटल पूर्णांक wiz_mux_of_clk_रेजिस्टर(काष्ठा wiz *wiz, काष्ठा device_node *node,
				   काष्ठा regmap_field *field, स्थिर u32 *table)
अणु
	काष्ठा device *dev = wiz->dev;
	काष्ठा clk_init_data *init;
	स्थिर अक्षर **parent_names;
	अचिन्हित पूर्णांक num_parents;
	काष्ठा wiz_clk_mux *mux;
	अक्षर clk_name[100];
	काष्ठा clk *clk;
	पूर्णांक ret;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	num_parents = of_clk_get_parent_count(node);
	अगर (num_parents < 2) अणु
		dev_err(dev, "SERDES clock must have parents\n");
		वापस -EINVAL;
	पूर्ण

	parent_names = devm_kzalloc(dev, (माप(अक्षर *) * num_parents),
				    GFP_KERNEL);
	अगर (!parent_names)
		वापस -ENOMEM;

	of_clk_parent_fill(node, parent_names, num_parents);

	snम_लिखो(clk_name, माप(clk_name), "%s_%s", dev_name(dev),
		 node->name);

	init = &mux->clk_data;

	init->ops = &wiz_clk_mux_ops;
	init->flags = CLK_SET_RATE_NO_REPARENT;
	init->parent_names = parent_names;
	init->num_parents = num_parents;
	init->name = clk_name;

	mux->field = field;
	mux->table = table;
	mux->hw.init = init;

	clk = devm_clk_रेजिस्टर(dev, &mux->hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret)
		dev_err(dev, "Failed to add clock provider: %s\n", clk_name);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ wiz_clk_भाग_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा wiz_clk_भागider *भाग = to_wiz_clk_भाग(hw);
	काष्ठा regmap_field *field = भाग->field;
	पूर्णांक val;

	regmap_field_पढ़ो(field, &val);

	वापस भागider_recalc_rate(hw, parent_rate, val, भाग->table, 0x0, 2);
पूर्ण

अटल दीर्घ wiz_clk_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ *prate)
अणु
	काष्ठा wiz_clk_भागider *भाग = to_wiz_clk_भाग(hw);

	वापस भागider_round_rate(hw, rate, prate, भाग->table, 2, 0x0);
पूर्ण

अटल पूर्णांक wiz_clk_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा wiz_clk_भागider *भाग = to_wiz_clk_भाग(hw);
	काष्ठा regmap_field *field = भाग->field;
	पूर्णांक val;

	val = भागider_get_val(rate, parent_rate, भाग->table, 2, 0x0);
	अगर (val < 0)
		वापस val;

	वापस regmap_field_ग_लिखो(field, val);
पूर्ण

अटल स्थिर काष्ठा clk_ops wiz_clk_भाग_ops = अणु
	.recalc_rate = wiz_clk_भाग_recalc_rate,
	.round_rate = wiz_clk_भाग_round_rate,
	.set_rate = wiz_clk_भाग_set_rate,
पूर्ण;

अटल पूर्णांक wiz_भाग_clk_रेजिस्टर(काष्ठा wiz *wiz, काष्ठा device_node *node,
				काष्ठा regmap_field *field,
				स्थिर काष्ठा clk_भाग_प्रकारable *table)
अणु
	काष्ठा device *dev = wiz->dev;
	काष्ठा wiz_clk_भागider *भाग;
	काष्ठा clk_init_data *init;
	स्थिर अक्षर **parent_names;
	अक्षर clk_name[100];
	काष्ठा clk *clk;
	पूर्णांक ret;

	भाग = devm_kzalloc(dev, माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस -ENOMEM;

	snम_लिखो(clk_name, माप(clk_name), "%s_%s", dev_name(dev),
		 node->name);

	parent_names = devm_kzalloc(dev, माप(अक्षर *), GFP_KERNEL);
	अगर (!parent_names)
		वापस -ENOMEM;

	of_clk_parent_fill(node, parent_names, 1);

	init = &भाग->clk_data;

	init->ops = &wiz_clk_भाग_ops;
	init->flags = 0;
	init->parent_names = parent_names;
	init->num_parents = 1;
	init->name = clk_name;

	भाग->field = field;
	भाग->table = table;
	भाग->hw.init = init;

	clk = devm_clk_रेजिस्टर(dev, &भाग->hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	अगर (ret)
		dev_err(dev, "Failed to add clock provider: %s\n", clk_name);

	वापस ret;
पूर्ण

अटल व्योम wiz_घड़ी_cleanup(काष्ठा wiz *wiz, काष्ठा device_node *node)
अणु
	स्थिर काष्ठा wiz_clk_mux_sel *clk_mux_sel = wiz->clk_mux_sel;
	काष्ठा device *dev = wiz->dev;
	काष्ठा device_node *clk_node;
	पूर्णांक i;

	अगर (wiz->type == AM64_WIZ_10G) अणु
		of_clk_del_provider(dev->of_node);
		वापस;
	पूर्ण

	क्रम (i = 0; i < WIZ_MUX_NUM_CLOCKS; i++) अणु
		clk_node = of_get_child_by_name(node, clk_mux_sel[i].node_name);
		of_clk_del_provider(clk_node);
		of_node_put(clk_node);
	पूर्ण

	क्रम (i = 0; i < wiz->clk_भाग_sel_num; i++) अणु
		clk_node = of_get_child_by_name(node, clk_भाग_sel[i].node_name);
		of_clk_del_provider(clk_node);
		of_node_put(clk_node);
	पूर्ण

	of_clk_del_provider(wiz->dev->of_node);
पूर्ण

अटल पूर्णांक wiz_घड़ी_रेजिस्टर(काष्ठा wiz *wiz)
अणु
	स्थिर काष्ठा wiz_clk_mux_sel *clk_mux_sel = wiz->clk_mux_sel;
	काष्ठा device *dev = wiz->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक clk_index;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (wiz->type != AM64_WIZ_10G)
		वापस 0;

	clk_index = TI_WIZ_PLL0_REFCLK;
	क्रम (i = 0; i < WIZ_MUX_NUM_CLOCKS; i++, clk_index++) अणु
		ret = wiz_mux_clk_रेजिस्टर(wiz, wiz->mux_sel_field[i], &clk_mux_sel[i], clk_index);
		अगर (ret) अणु
			dev_err(dev, "Failed to register clk: %s\n", output_clk_names[clk_index]);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = wiz_phy_en_refclk_रेजिस्टर(wiz);
	अगर (ret) अणु
		dev_err(dev, "Failed to add phy-en-refclk\n");
		वापस ret;
	पूर्ण

	wiz->clk_data.clks = wiz->output_clks;
	wiz->clk_data.clk_num = WIZ_MAX_OUTPUT_CLOCKS;
	ret = of_clk_add_provider(node, of_clk_src_onecell_get, &wiz->clk_data);
	अगर (ret)
		dev_err(dev, "Failed to add clock provider: %s\n", node->name);

	वापस ret;
पूर्ण

अटल पूर्णांक wiz_घड़ी_init(काष्ठा wiz *wiz, काष्ठा device_node *node)
अणु
	स्थिर काष्ठा wiz_clk_mux_sel *clk_mux_sel = wiz->clk_mux_sel;
	काष्ठा device *dev = wiz->dev;
	काष्ठा device_node *clk_node;
	स्थिर अक्षर *node_name;
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक ret;
	पूर्णांक i;

	clk = devm_clk_get(dev, "core_ref_clk");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "core_ref_clk clock not found\n");
		ret = PTR_ERR(clk);
		वापस ret;
	पूर्ण
	wiz->input_clks[WIZ_CORE_REFCLK] = clk;

	rate = clk_get_rate(clk);
	अगर (rate >= 100000000)
		regmap_field_ग_लिखो(wiz->pma_cmn_refclk_पूर्णांक_mode, 0x1);
	अन्यथा
		regmap_field_ग_लिखो(wiz->pma_cmn_refclk_पूर्णांक_mode, 0x3);

	clk = devm_clk_get(dev, "ext_ref_clk");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "ext_ref_clk clock not found\n");
		ret = PTR_ERR(clk);
		वापस ret;
	पूर्ण
	wiz->input_clks[WIZ_EXT_REFCLK] = clk;

	rate = clk_get_rate(clk);
	अगर (rate >= 100000000)
		regmap_field_ग_लिखो(wiz->pma_cmn_refclk_mode, 0x0);
	अन्यथा
		regmap_field_ग_लिखो(wiz->pma_cmn_refclk_mode, 0x2);

	अगर (wiz->type == AM64_WIZ_10G) अणु
		ret = wiz_घड़ी_रेजिस्टर(wiz);
		अगर (ret)
			dev_err(dev, "Failed to register wiz clocks\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < WIZ_MUX_NUM_CLOCKS; i++) अणु
		node_name = clk_mux_sel[i].node_name;
		clk_node = of_get_child_by_name(node, node_name);
		अगर (!clk_node) अणु
			dev_err(dev, "Unable to get %s node\n", node_name);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		ret = wiz_mux_of_clk_रेजिस्टर(wiz, clk_node, wiz->mux_sel_field[i],
					      clk_mux_sel[i].table);
		अगर (ret) अणु
			dev_err(dev, "Failed to register %s clock\n",
				node_name);
			of_node_put(clk_node);
			जाओ err;
		पूर्ण

		of_node_put(clk_node);
	पूर्ण

	क्रम (i = 0; i < wiz->clk_भाग_sel_num; i++) अणु
		node_name = clk_भाग_sel[i].node_name;
		clk_node = of_get_child_by_name(node, node_name);
		अगर (!clk_node) अणु
			dev_err(dev, "Unable to get %s node\n", node_name);
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		ret = wiz_भाग_clk_रेजिस्टर(wiz, clk_node, wiz->भाग_sel_field[i],
					   clk_भाग_sel[i].table);
		अगर (ret) अणु
			dev_err(dev, "Failed to register %s clock\n",
				node_name);
			of_node_put(clk_node);
			जाओ err;
		पूर्ण

		of_node_put(clk_node);
	पूर्ण

	वापस 0;
err:
	wiz_घड़ी_cleanup(wiz, node);

	वापस ret;
पूर्ण

अटल पूर्णांक wiz_phy_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा device *dev = rcdev->dev;
	काष्ठा wiz *wiz = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (id == 0) अणु
		ret = regmap_field_ग_लिखो(wiz->phy_reset_n, false);
		वापस ret;
	पूर्ण

	ret = regmap_field_ग_लिखो(wiz->p_enable[id - 1], P_ENABLE_DISABLE);
	वापस ret;
पूर्ण

अटल पूर्णांक wiz_phy_fullrt_भाग(काष्ठा wiz *wiz, पूर्णांक lane)
अणु
	अगर (wiz->type != AM64_WIZ_10G)
		वापस 0;

	अगर (wiz->lane_phy_type[lane] == PHY_TYPE_PCIE)
		वापस regmap_field_ग_लिखो(wiz->p0_fullrt_भाग[lane], 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_phy_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	काष्ठा device *dev = rcdev->dev;
	काष्ठा wiz *wiz = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* अगर typec-dir gpio was specअगरied, set LN10 SWAP bit based on that */
	अगर (id == 0 && wiz->gpio_typec_dir) अणु
		अगर (wiz->typec_dir_delay)
			msleep_पूर्णांकerruptible(wiz->typec_dir_delay);

		अगर (gpiod_get_value_cansleep(wiz->gpio_typec_dir))
			regmap_field_ग_लिखो(wiz->typec_ln10_swap, 1);
		अन्यथा
			regmap_field_ग_लिखो(wiz->typec_ln10_swap, 0);
	पूर्ण

	अगर (id == 0) अणु
		ret = regmap_field_ग_लिखो(wiz->phy_reset_n, true);
		वापस ret;
	पूर्ण

	ret = wiz_phy_fullrt_भाग(wiz, id - 1);
	अगर (ret)
		वापस ret;

	अगर (wiz->lane_phy_type[id - 1] == PHY_TYPE_DP)
		ret = regmap_field_ग_लिखो(wiz->p_enable[id - 1], P_ENABLE);
	अन्यथा
		ret = regmap_field_ग_लिखो(wiz->p_enable[id - 1], P_ENABLE_FORCE);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops wiz_phy_reset_ops = अणु
	.निश्चित = wiz_phy_reset_निश्चित,
	.deनिश्चित = wiz_phy_reset_deनिश्चित,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wiz_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wiz_id_table[] = अणु
	अणु
		.compatible = "ti,j721e-wiz-16g", .data = (व्योम *)J721E_WIZ_16G
	पूर्ण,
	अणु
		.compatible = "ti,j721e-wiz-10g", .data = (व्योम *)J721E_WIZ_10G
	पूर्ण,
	अणु
		.compatible = "ti,am64-wiz-10g", .data = (व्योम *)AM64_WIZ_10G
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wiz_id_table);

अटल पूर्णांक wiz_get_lane_phy_types(काष्ठा device *dev, काष्ठा wiz *wiz)
अणु
	काष्ठा device_node *serdes, *subnode;

	serdes = of_get_child_by_name(dev->of_node, "serdes");
	अगर (!serdes) अणु
		dev_err(dev, "%s: Getting \"serdes\"-node failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(serdes, subnode) अणु
		u32 reg, num_lanes = 1, phy_type = PHY_NONE;
		पूर्णांक ret, i;

		अगर (!(of_node_name_eq(subnode, "phy") ||
		      of_node_name_eq(subnode, "link")))
			जारी;

		ret = of_property_पढ़ो_u32(subnode, "reg", &reg);
		अगर (ret) अणु
			of_node_put(subnode);
			dev_err(dev,
				"%s: Reading \"reg\" from \"%s\" failed: %d\n",
				__func__, subnode->name, ret);
			वापस ret;
		पूर्ण
		of_property_पढ़ो_u32(subnode, "cdns,num-lanes", &num_lanes);
		of_property_पढ़ो_u32(subnode, "cdns,phy-type", &phy_type);

		dev_dbg(dev, "%s: Lanes %u-%u have phy-type %u\n", __func__,
			reg, reg + num_lanes - 1, phy_type);

		क्रम (i = reg; i < reg + num_lanes; i++)
			wiz->lane_phy_type[i] = phy_type;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wiz_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा reset_controller_dev *phy_reset_dev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा platक्रमm_device *serdes_pdev;
	bool alपढ़ोy_configured = false;
	काष्ठा device_node *child_node;
	काष्ठा regmap *regmap;
	काष्ठा resource res;
	व्योम __iomem *base;
	काष्ठा wiz *wiz;
	पूर्णांक ret, val, i;
	u32 num_lanes;

	wiz = devm_kzalloc(dev, माप(*wiz), GFP_KERNEL);
	अगर (!wiz)
		वापस -ENOMEM;

	wiz->type = (क्रमागत wiz_type)of_device_get_match_data(dev);

	child_node = of_get_child_by_name(node, "serdes");
	अगर (!child_node) अणु
		dev_err(dev, "Failed to get SERDES child DT node\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_address_to_resource(child_node, 0, &res);
	अगर (ret) अणु
		dev_err(dev, "Failed to get memory resource\n");
		जाओ err_addr_to_resource;
	पूर्ण

	base = devm_ioremap(dev, res.start, resource_size(&res));
	अगर (!base) अणु
		ret = -ENOMEM;
		जाओ err_addr_to_resource;
	पूर्ण

	regmap = devm_regmap_init_mmio(dev, base, &wiz_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to initialize regmap\n");
		ret = PTR_ERR(regmap);
		जाओ err_addr_to_resource;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "num-lanes", &num_lanes);
	अगर (ret) अणु
		dev_err(dev, "Failed to read num-lanes property\n");
		जाओ err_addr_to_resource;
	पूर्ण

	अगर (num_lanes > WIZ_MAX_LANES) अणु
		dev_err(dev, "Cannot support %d lanes\n", num_lanes);
		ret = -ENODEV;
		जाओ err_addr_to_resource;
	पूर्ण

	wiz->gpio_typec_dir = devm_gpiod_get_optional(dev, "typec-dir",
						      GPIOD_IN);
	अगर (IS_ERR(wiz->gpio_typec_dir)) अणु
		ret = PTR_ERR(wiz->gpio_typec_dir);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to request typec-dir gpio: %d\n",
				ret);
		जाओ err_addr_to_resource;
	पूर्ण

	अगर (wiz->gpio_typec_dir) अणु
		ret = of_property_पढ़ो_u32(node, "typec-dir-debounce-ms",
					   &wiz->typec_dir_delay);
		अगर (ret && ret != -EINVAL) अणु
			dev_err(dev, "Invalid typec-dir-debounce property\n");
			जाओ err_addr_to_resource;
		पूर्ण

		/* use min. debounce from Type-C spec अगर not provided in DT  */
		अगर (ret == -EINVAL)
			wiz->typec_dir_delay = WIZ_TYPEC_सूची_DEBOUNCE_MIN;

		अगर (wiz->typec_dir_delay < WIZ_TYPEC_सूची_DEBOUNCE_MIN ||
		    wiz->typec_dir_delay > WIZ_TYPEC_सूची_DEBOUNCE_MAX) अणु
			ret = -EINVAL;
			dev_err(dev, "Invalid typec-dir-debounce property\n");
			जाओ err_addr_to_resource;
		पूर्ण
	पूर्ण

	ret = wiz_get_lane_phy_types(dev, wiz);
	अगर (ret)
		वापस ret;

	wiz->dev = dev;
	wiz->regmap = regmap;
	wiz->num_lanes = num_lanes;
	अगर (wiz->type == J721E_WIZ_10G || wiz->type == AM64_WIZ_10G)
		wiz->clk_mux_sel = clk_mux_sel_10g;
	अन्यथा
		wiz->clk_mux_sel = clk_mux_sel_16g;

	wiz->clk_भाग_sel = clk_भाग_sel;

	अगर (wiz->type == J721E_WIZ_10G || wiz->type == AM64_WIZ_10G)
		wiz->clk_भाग_sel_num = WIZ_DIV_NUM_CLOCKS_10G;
	अन्यथा
		wiz->clk_भाग_sel_num = WIZ_DIV_NUM_CLOCKS_16G;

	platक्रमm_set_drvdata(pdev, wiz);

	ret = wiz_regfield_init(wiz);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize regfields\n");
		जाओ err_addr_to_resource;
	पूर्ण

	phy_reset_dev = &wiz->wiz_phy_reset_dev;
	phy_reset_dev->dev = dev;
	phy_reset_dev->ops = &wiz_phy_reset_ops,
	phy_reset_dev->owner = THIS_MODULE,
	phy_reset_dev->of_node = node;
	/* Reset क्रम each of the lane and one क्रम the entire SERDES */
	phy_reset_dev->nr_resets = num_lanes + 1;

	ret = devm_reset_controller_रेजिस्टर(dev, phy_reset_dev);
	अगर (ret < 0) अणु
		dev_warn(dev, "Failed to register reset controller\n");
		जाओ err_addr_to_resource;
	पूर्ण

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		जाओ err_get_sync;
	पूर्ण

	ret = wiz_घड़ी_init(wiz, node);
	अगर (ret < 0) अणु
		dev_warn(dev, "Failed to initialize clocks\n");
		जाओ err_get_sync;
	पूर्ण

	क्रम (i = 0; i < wiz->num_lanes; i++) अणु
		regmap_field_पढ़ो(wiz->p_enable[i], &val);
		अगर (val & (P_ENABLE | P_ENABLE_FORCE)) अणु
			alपढ़ोy_configured = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!alपढ़ोy_configured) अणु
		ret = wiz_init(wiz);
		अगर (ret) अणु
			dev_err(dev, "WIZ initialization failed\n");
			जाओ err_wiz_init;
		पूर्ण
	पूर्ण

	serdes_pdev = of_platक्रमm_device_create(child_node, शून्य, dev);
	अगर (!serdes_pdev) अणु
		dev_WARN(dev, "Unable to create SERDES platform device\n");
		ret = -ENOMEM;
		जाओ err_wiz_init;
	पूर्ण
	wiz->serdes_pdev = serdes_pdev;

	of_node_put(child_node);
	वापस 0;

err_wiz_init:
	wiz_घड़ी_cleanup(wiz, node);

err_get_sync:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

err_addr_to_resource:
	of_node_put(child_node);

	वापस ret;
पूर्ण

अटल पूर्णांक wiz_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा platक्रमm_device *serdes_pdev;
	काष्ठा wiz *wiz;

	wiz = dev_get_drvdata(dev);
	serdes_pdev = wiz->serdes_pdev;

	of_platक्रमm_device_destroy(&serdes_pdev->dev, शून्य);
	wiz_घड़ी_cleanup(wiz, node);
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wiz_driver = अणु
	.probe		= wiz_probe,
	.हटाओ		= wiz_हटाओ,
	.driver		= अणु
		.name	= "wiz",
		.of_match_table = wiz_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(wiz_driver);

MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("TI J721E WIZ driver");
MODULE_LICENSE("GPL v2");
