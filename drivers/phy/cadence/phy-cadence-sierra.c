<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence Sierra PHY Driver
 *
 * Copyright (c) 2018 Cadence Design Systems
 * Author: Alan Douglas <aकरोuglas@cadence.com>
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <dt-bindings/phy/phy.h>
#समावेश <dt-bindings/phy/phy-cadence.h>

/* PHY रेजिस्टर offsets */
#घोषणा SIERRA_COMMON_CDB_OFFSET			0x0
#घोषणा SIERRA_MACRO_ID_REG				0x0
#घोषणा SIERRA_CMN_PLLLC_GEN_PREG			0x42
#घोषणा SIERRA_CMN_PLLLC_MODE_PREG			0x48
#घोषणा SIERRA_CMN_PLLLC_LF_COEFF_MODE1_PREG		0x49
#घोषणा SIERRA_CMN_PLLLC_LF_COEFF_MODE0_PREG		0x4A
#घोषणा SIERRA_CMN_PLLLC_LOCK_CNTSTART_PREG		0x4B
#घोषणा SIERRA_CMN_PLLLC_BWCAL_MODE1_PREG		0x4F
#घोषणा SIERRA_CMN_PLLLC_BWCAL_MODE0_PREG		0x50
#घोषणा SIERRA_CMN_PLLLC_SS_TIME_STEPSIZE_MODE_PREG	0x62
#घोषणा SIERRA_CMN_REFRCV_PREG				0x98
#घोषणा SIERRA_CMN_REFRCV1_PREG				0xB8
#घोषणा SIERRA_CMN_PLLLC1_GEN_PREG			0xC2

#घोषणा SIERRA_LANE_CDB_OFFSET(ln, block_offset, reg_offset)	\
				((0x4000 << (block_offset)) + \
				 (((ln) << 9) << (reg_offset)))

#घोषणा SIERRA_DET_STANDEC_A_PREG			0x000
#घोषणा SIERRA_DET_STANDEC_B_PREG			0x001
#घोषणा SIERRA_DET_STANDEC_C_PREG			0x002
#घोषणा SIERRA_DET_STANDEC_D_PREG			0x003
#घोषणा SIERRA_DET_STANDEC_E_PREG			0x004
#घोषणा SIERRA_PSM_LANECAL_DLY_A1_RESETS_PREG		0x008
#घोषणा SIERRA_PSM_A0IN_TMR_PREG			0x009
#घोषणा SIERRA_PSM_DIAG_PREG				0x015
#घोषणा SIERRA_PSC_TX_A0_PREG				0x028
#घोषणा SIERRA_PSC_TX_A1_PREG				0x029
#घोषणा SIERRA_PSC_TX_A2_PREG				0x02A
#घोषणा SIERRA_PSC_TX_A3_PREG				0x02B
#घोषणा SIERRA_PSC_RX_A0_PREG				0x030
#घोषणा SIERRA_PSC_RX_A1_PREG				0x031
#घोषणा SIERRA_PSC_RX_A2_PREG				0x032
#घोषणा SIERRA_PSC_RX_A3_PREG				0x033
#घोषणा SIERRA_PLLCTRL_SUBRATE_PREG			0x03A
#घोषणा SIERRA_PLLCTRL_GEN_D_PREG			0x03E
#घोषणा SIERRA_PLLCTRL_CPGAIN_MODE_PREG			0x03F
#घोषणा SIERRA_PLLCTRL_STATUS_PREG			0x044
#घोषणा SIERRA_CLKPATH_BIASTRIM_PREG			0x04B
#घोषणा SIERRA_DFE_BIASTRIM_PREG			0x04C
#घोषणा SIERRA_DRVCTRL_ATTEN_PREG			0x06A
#घोषणा SIERRA_CLKPATHCTRL_TMR_PREG			0x081
#घोषणा SIERRA_RX_CREQ_FLTR_A_MODE3_PREG		0x085
#घोषणा SIERRA_RX_CREQ_FLTR_A_MODE2_PREG		0x086
#घोषणा SIERRA_RX_CREQ_FLTR_A_MODE1_PREG		0x087
#घोषणा SIERRA_RX_CREQ_FLTR_A_MODE0_PREG		0x088
#घोषणा SIERRA_CREQ_CCLKDET_MODE01_PREG			0x08E
#घोषणा SIERRA_RX_CTLE_MAINTEन_अंकCE_PREG			0x091
#घोषणा SIERRA_CREQ_FSMCLK_SEL_PREG			0x092
#घोषणा SIERRA_CREQ_EQ_CTRL_PREG			0x093
#घोषणा SIERRA_CREQ_SPARE_PREG				0x096
#घोषणा SIERRA_CREQ_EQ_OPEN_EYE_THRESH_PREG		0x097
#घोषणा SIERRA_CTLELUT_CTRL_PREG			0x098
#घोषणा SIERRA_DFE_ECMP_RATESEL_PREG			0x0C0
#घोषणा SIERRA_DFE_SMP_RATESEL_PREG			0x0C1
#घोषणा SIERRA_DEQ_PHALIGN_CTRL				0x0C4
#घोषणा SIERRA_DEQ_CONCUR_CTRL1_PREG			0x0C8
#घोषणा SIERRA_DEQ_CONCUR_CTRL2_PREG			0x0C9
#घोषणा SIERRA_DEQ_EPIPWR_CTRL2_PREG			0x0CD
#घोषणा SIERRA_DEQ_FAST_MAINT_CYCLES_PREG		0x0CE
#घोषणा SIERRA_DEQ_ERRCMP_CTRL_PREG			0x0D0
#घोषणा SIERRA_DEQ_OFFSET_CTRL_PREG			0x0D8
#घोषणा SIERRA_DEQ_GAIN_CTRL_PREG			0x0E0
#घोषणा SIERRA_DEQ_VGATUNE_CTRL_PREG			0x0E1
#घोषणा SIERRA_DEQ_GLUT0				0x0E8
#घोषणा SIERRA_DEQ_GLUT1				0x0E9
#घोषणा SIERRA_DEQ_GLUT2				0x0EA
#घोषणा SIERRA_DEQ_GLUT3				0x0EB
#घोषणा SIERRA_DEQ_GLUT4				0x0EC
#घोषणा SIERRA_DEQ_GLUT5				0x0ED
#घोषणा SIERRA_DEQ_GLUT6				0x0EE
#घोषणा SIERRA_DEQ_GLUT7				0x0EF
#घोषणा SIERRA_DEQ_GLUT8				0x0F0
#घोषणा SIERRA_DEQ_GLUT9				0x0F1
#घोषणा SIERRA_DEQ_GLUT10				0x0F2
#घोषणा SIERRA_DEQ_GLUT11				0x0F3
#घोषणा SIERRA_DEQ_GLUT12				0x0F4
#घोषणा SIERRA_DEQ_GLUT13				0x0F5
#घोषणा SIERRA_DEQ_GLUT14				0x0F6
#घोषणा SIERRA_DEQ_GLUT15				0x0F7
#घोषणा SIERRA_DEQ_GLUT16				0x0F8
#घोषणा SIERRA_DEQ_ALUT0				0x108
#घोषणा SIERRA_DEQ_ALUT1				0x109
#घोषणा SIERRA_DEQ_ALUT2				0x10A
#घोषणा SIERRA_DEQ_ALUT3				0x10B
#घोषणा SIERRA_DEQ_ALUT4				0x10C
#घोषणा SIERRA_DEQ_ALUT5				0x10D
#घोषणा SIERRA_DEQ_ALUT6				0x10E
#घोषणा SIERRA_DEQ_ALUT7				0x10F
#घोषणा SIERRA_DEQ_ALUT8				0x110
#घोषणा SIERRA_DEQ_ALUT9				0x111
#घोषणा SIERRA_DEQ_ALUT10				0x112
#घोषणा SIERRA_DEQ_ALUT11				0x113
#घोषणा SIERRA_DEQ_ALUT12				0x114
#घोषणा SIERRA_DEQ_ALUT13				0x115
#घोषणा SIERRA_DEQ_DFETAP_CTRL_PREG			0x128
#घोषणा SIERRA_DFE_EN_1010_IGNORE_PREG			0x134
#घोषणा SIERRA_DEQ_TAU_CTRL1_SLOW_MAINT_PREG		0x150
#घोषणा SIERRA_DEQ_TAU_CTRL2_PREG			0x151
#घोषणा SIERRA_DEQ_PICTRL_PREG				0x161
#घोषणा SIERRA_CPICAL_TMRVAL_MODE1_PREG			0x170
#घोषणा SIERRA_CPICAL_TMRVAL_MODE0_PREG			0x171
#घोषणा SIERRA_CPICAL_PICNT_MODE1_PREG			0x174
#घोषणा SIERRA_CPI_OUTBUF_RATESEL_PREG			0x17C
#घोषणा SIERRA_CPICAL_RES_STARTCODE_MODE23_PREG		0x183
#घोषणा SIERRA_LFPSDET_SUPPORT_PREG			0x188
#घोषणा SIERRA_LFPSFILT_NS_PREG				0x18A
#घोषणा SIERRA_LFPSFILT_RD_PREG				0x18B
#घोषणा SIERRA_LFPSFILT_MP_PREG				0x18C
#घोषणा SIERRA_SIGDET_SUPPORT_PREG			0x190
#घोषणा SIERRA_SDFILT_H2L_A_PREG			0x191
#घोषणा SIERRA_SDFILT_L2H_PREG				0x193
#घोषणा SIERRA_RXBUFFER_CTLECTRL_PREG			0x19E
#घोषणा SIERRA_RXBUFFER_RCDFECTRL_PREG			0x19F
#घोषणा SIERRA_RXBUFFER_DFECTRL_PREG			0x1A0
#घोषणा SIERRA_DEQ_TAU_CTRL1_FAST_MAINT_PREG		0x14F
#घोषणा SIERRA_DEQ_TAU_CTRL1_SLOW_MAINT_PREG		0x150

#घोषणा SIERRA_PHY_CONFIG_CTRL_OFFSET(block_offset)	\
				      (0xc000 << (block_offset))
#घोषणा SIERRA_PHY_PLL_CFG				0xe

#घोषणा SIERRA_MACRO_ID					0x00007364
#घोषणा SIERRA_MAX_LANES				16
#घोषणा PLL_LOCK_TIME					100000

#घोषणा CDNS_SIERRA_OUTPUT_CLOCKS			2
#घोषणा CDNS_SIERRA_INPUT_CLOCKS			5
क्रमागत cdns_sierra_घड़ी_input अणु
	PHY_CLK,
	CMN_REFCLK_DIG_DIV,
	CMN_REFCLK1_DIG_DIV,
	PLL0_REFCLK,
	PLL1_REFCLK,
पूर्ण;

#घोषणा SIERRA_NUM_CMN_PLLC				2
#घोषणा SIERRA_NUM_CMN_PLLC_PARENTS			2

अटल स्थिर काष्ठा reg_field macro_id_type =
				REG_FIELD(SIERRA_MACRO_ID_REG, 0, 15);
अटल स्थिर काष्ठा reg_field phy_pll_cfg_1 =
				REG_FIELD(SIERRA_PHY_PLL_CFG, 1, 1);
अटल स्थिर काष्ठा reg_field pllctrl_lock =
				REG_FIELD(SIERRA_PLLCTRL_STATUS_PREG, 0, 0);

अटल स्थिर अक्षर * स्थिर clk_names[] = अणु
	[CDNS_SIERRA_PLL_CMNLC] = "pll_cmnlc",
	[CDNS_SIERRA_PLL_CMNLC1] = "pll_cmnlc1",
पूर्ण;

क्रमागत cdns_sierra_cmn_plllc अणु
	CMN_PLLLC,
	CMN_PLLLC1,
पूर्ण;

काष्ठा cdns_sierra_pll_mux_reg_fields अणु
	काष्ठा reg_field	pfdclk_sel_preg;
	काष्ठा reg_field	plllc1en_field;
	काष्ठा reg_field	termen_field;
पूर्ण;

अटल स्थिर काष्ठा cdns_sierra_pll_mux_reg_fields cmn_plllc_pfdclk1_sel_preg[] = अणु
	[CMN_PLLLC] = अणु
		.pfdclk_sel_preg = REG_FIELD(SIERRA_CMN_PLLLC_GEN_PREG, 1, 1),
		.plllc1en_field = REG_FIELD(SIERRA_CMN_REFRCV1_PREG, 8, 8),
		.termen_field = REG_FIELD(SIERRA_CMN_REFRCV1_PREG, 0, 0),
	पूर्ण,
	[CMN_PLLLC1] = अणु
		.pfdclk_sel_preg = REG_FIELD(SIERRA_CMN_PLLLC1_GEN_PREG, 1, 1),
		.plllc1en_field = REG_FIELD(SIERRA_CMN_REFRCV_PREG, 8, 8),
		.termen_field = REG_FIELD(SIERRA_CMN_REFRCV_PREG, 0, 0),
	पूर्ण,
पूर्ण;

काष्ठा cdns_sierra_pll_mux अणु
	काष्ठा clk_hw		hw;
	काष्ठा regmap_field	*pfdclk_sel_preg;
	काष्ठा regmap_field	*plllc1en_field;
	काष्ठा regmap_field	*termen_field;
	काष्ठा clk_init_data	clk_data;
पूर्ण;

#घोषणा to_cdns_sierra_pll_mux(_hw)	\
			container_of(_hw, काष्ठा cdns_sierra_pll_mux, hw)

अटल स्थिर पूर्णांक pll_mux_parent_index[][SIERRA_NUM_CMN_PLLC_PARENTS] = अणु
	[CMN_PLLLC] = अणु PLL0_REFCLK, PLL1_REFCLK पूर्ण,
	[CMN_PLLLC1] = अणु PLL1_REFCLK, PLL0_REFCLK पूर्ण,
पूर्ण;

अटल u32 cdns_sierra_pll_mux_table[] = अणु 0, 1 पूर्ण;

काष्ठा cdns_sierra_inst अणु
	काष्ठा phy *phy;
	u32 phy_type;
	u32 num_lanes;
	u32 mlane;
	काष्ठा reset_control *lnk_rst;
पूर्ण;

काष्ठा cdns_reg_pairs अणु
	u16 val;
	u32 off;
पूर्ण;

काष्ठा cdns_sierra_data अणु
		u32 id_value;
		u8 block_offset_shअगरt;
		u8 reg_offset_shअगरt;
		u32 pcie_cmn_regs;
		u32 pcie_ln_regs;
		u32 usb_cmn_regs;
		u32 usb_ln_regs;
		स्थिर काष्ठा cdns_reg_pairs *pcie_cmn_vals;
		स्थिर काष्ठा cdns_reg_pairs *pcie_ln_vals;
		स्थिर काष्ठा cdns_reg_pairs *usb_cmn_vals;
		स्थिर काष्ठा cdns_reg_pairs *usb_ln_vals;
पूर्ण;

काष्ठा cdns_regmap_cdb_context अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	u8 reg_offset_shअगरt;
पूर्ण;

काष्ठा cdns_sierra_phy अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा cdns_sierra_data *init_data;
	काष्ठा cdns_sierra_inst phys[SIERRA_MAX_LANES];
	काष्ठा reset_control *phy_rst;
	काष्ठा reset_control *apb_rst;
	काष्ठा regmap *regmap_lane_cdb[SIERRA_MAX_LANES];
	काष्ठा regmap *regmap_phy_config_ctrl;
	काष्ठा regmap *regmap_common_cdb;
	काष्ठा regmap_field *macro_id_type;
	काष्ठा regmap_field *phy_pll_cfg_1;
	काष्ठा regmap_field *pllctrl_lock[SIERRA_MAX_LANES];
	काष्ठा regmap_field *cmn_refrcv_refclk_plllc1en_preg[SIERRA_NUM_CMN_PLLC];
	काष्ठा regmap_field *cmn_refrcv_refclk_termen_preg[SIERRA_NUM_CMN_PLLC];
	काष्ठा regmap_field *cmn_plllc_pfdclk1_sel_preg[SIERRA_NUM_CMN_PLLC];
	काष्ठा clk *input_clks[CDNS_SIERRA_INPUT_CLOCKS];
	पूर्णांक nsubnodes;
	u32 num_lanes;
	bool स्वतःconf;
	काष्ठा clk_onecell_data clk_data;
	काष्ठा clk *output_clks[CDNS_SIERRA_OUTPUT_CLOCKS];
पूर्ण;

अटल पूर्णांक cdns_regmap_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx = context;
	u32 offset = reg << ctx->reg_offset_shअगरt;

	ग_लिखोw(val, ctx->base + offset);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_regmap_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx = context;
	u32 offset = reg << ctx->reg_offset_shअगरt;

	*val = पढ़ोw(ctx->base + offset);
	वापस 0;
पूर्ण

#घोषणा SIERRA_LANE_CDB_REGMAP_CONF(n) \
अणु \
	.name = "sierra_lane" n "_cdb", \
	.reg_stride = 1, \
	.fast_io = true, \
	.reg_ग_लिखो = cdns_regmap_ग_लिखो, \
	.reg_पढ़ो = cdns_regmap_पढ़ो, \
पूर्ण

अटल स्थिर काष्ठा regmap_config cdns_sierra_lane_cdb_config[] = अणु
	SIERRA_LANE_CDB_REGMAP_CONF("0"),
	SIERRA_LANE_CDB_REGMAP_CONF("1"),
	SIERRA_LANE_CDB_REGMAP_CONF("2"),
	SIERRA_LANE_CDB_REGMAP_CONF("3"),
	SIERRA_LANE_CDB_REGMAP_CONF("4"),
	SIERRA_LANE_CDB_REGMAP_CONF("5"),
	SIERRA_LANE_CDB_REGMAP_CONF("6"),
	SIERRA_LANE_CDB_REGMAP_CONF("7"),
	SIERRA_LANE_CDB_REGMAP_CONF("8"),
	SIERRA_LANE_CDB_REGMAP_CONF("9"),
	SIERRA_LANE_CDB_REGMAP_CONF("10"),
	SIERRA_LANE_CDB_REGMAP_CONF("11"),
	SIERRA_LANE_CDB_REGMAP_CONF("12"),
	SIERRA_LANE_CDB_REGMAP_CONF("13"),
	SIERRA_LANE_CDB_REGMAP_CONF("14"),
	SIERRA_LANE_CDB_REGMAP_CONF("15"),
पूर्ण;

अटल स्थिर काष्ठा regmap_config cdns_sierra_common_cdb_config = अणु
	.name = "sierra_common_cdb",
	.reg_stride = 1,
	.fast_io = true,
	.reg_ग_लिखो = cdns_regmap_ग_लिखो,
	.reg_पढ़ो = cdns_regmap_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cdns_sierra_phy_config_ctrl_config = अणु
	.name = "sierra_phy_config_ctrl",
	.reg_stride = 1,
	.fast_io = true,
	.reg_ग_लिखो = cdns_regmap_ग_लिखो,
	.reg_पढ़ो = cdns_regmap_पढ़ो,
पूर्ण;

अटल पूर्णांक cdns_sierra_phy_init(काष्ठा phy *gphy)
अणु
	काष्ठा cdns_sierra_inst *ins = phy_get_drvdata(gphy);
	काष्ठा cdns_sierra_phy *phy = dev_get_drvdata(gphy->dev.parent);
	काष्ठा regmap *regmap;
	पूर्णांक i, j;
	स्थिर काष्ठा cdns_reg_pairs *cmn_vals, *ln_vals;
	u32 num_cmn_regs, num_ln_regs;

	/* Initialise the PHY रेजिस्टरs, unless स्वतः configured */
	अगर (phy->स्वतःconf)
		वापस 0;

	clk_set_rate(phy->input_clks[CMN_REFCLK_DIG_DIV], 25000000);
	clk_set_rate(phy->input_clks[CMN_REFCLK1_DIG_DIV], 25000000);
	अगर (ins->phy_type == PHY_TYPE_PCIE) अणु
		num_cmn_regs = phy->init_data->pcie_cmn_regs;
		num_ln_regs = phy->init_data->pcie_ln_regs;
		cmn_vals = phy->init_data->pcie_cmn_vals;
		ln_vals = phy->init_data->pcie_ln_vals;
	पूर्ण अन्यथा अगर (ins->phy_type == PHY_TYPE_USB3) अणु
		num_cmn_regs = phy->init_data->usb_cmn_regs;
		num_ln_regs = phy->init_data->usb_ln_regs;
		cmn_vals = phy->init_data->usb_cmn_vals;
		ln_vals = phy->init_data->usb_ln_vals;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	regmap = phy->regmap_common_cdb;
	क्रम (j = 0; j < num_cmn_regs ; j++)
		regmap_ग_लिखो(regmap, cmn_vals[j].off, cmn_vals[j].val);

	क्रम (i = 0; i < ins->num_lanes; i++) अणु
		क्रम (j = 0; j < num_ln_regs ; j++) अणु
			regmap = phy->regmap_lane_cdb[i + ins->mlane];
			regmap_ग_लिखो(regmap, ln_vals[j].off, ln_vals[j].val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_sierra_phy_on(काष्ठा phy *gphy)
अणु
	काष्ठा cdns_sierra_phy *sp = dev_get_drvdata(gphy->dev.parent);
	काष्ठा cdns_sierra_inst *ins = phy_get_drvdata(gphy);
	काष्ठा device *dev = sp->dev;
	u32 val;
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(sp->phy_rst);
	अगर (ret) अणु
		dev_err(dev, "Failed to take the PHY out of reset\n");
		वापस ret;
	पूर्ण

	/* Take the PHY lane group out of reset */
	ret = reset_control_deनिश्चित(ins->lnk_rst);
	अगर (ret) अणु
		dev_err(dev, "Failed to take the PHY lane out of reset\n");
		वापस ret;
	पूर्ण

	ret = regmap_field_पढ़ो_poll_समयout(sp->pllctrl_lock[ins->mlane],
					     val, val, 1000, PLL_LOCK_TIME);
	अगर (ret < 0)
		dev_err(dev, "PLL lock of lane failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_sierra_phy_off(काष्ठा phy *gphy)
अणु
	काष्ठा cdns_sierra_inst *ins = phy_get_drvdata(gphy);

	वापस reset_control_निश्चित(ins->lnk_rst);
पूर्ण

अटल पूर्णांक cdns_sierra_phy_reset(काष्ठा phy *gphy)
अणु
	काष्ठा cdns_sierra_phy *sp = dev_get_drvdata(gphy->dev.parent);

	reset_control_निश्चित(sp->phy_rst);
	reset_control_deनिश्चित(sp->phy_rst);
	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= cdns_sierra_phy_init,
	.घातer_on	= cdns_sierra_phy_on,
	.घातer_off	= cdns_sierra_phy_off,
	.reset		= cdns_sierra_phy_reset,
	.owner		= THIS_MODULE,
पूर्ण;

अटल u8 cdns_sierra_pll_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा cdns_sierra_pll_mux *mux = to_cdns_sierra_pll_mux(hw);
	काष्ठा regmap_field *field = mux->pfdclk_sel_preg;
	अचिन्हित पूर्णांक val;

	regmap_field_पढ़ो(field, &val);
	वापस clk_mux_val_to_index(hw, cdns_sierra_pll_mux_table, 0, val);
पूर्ण

अटल पूर्णांक cdns_sierra_pll_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा cdns_sierra_pll_mux *mux = to_cdns_sierra_pll_mux(hw);
	काष्ठा regmap_field *plllc1en_field = mux->plllc1en_field;
	काष्ठा regmap_field *termen_field = mux->termen_field;
	काष्ठा regmap_field *field = mux->pfdclk_sel_preg;
	पूर्णांक val, ret;

	ret = regmap_field_ग_लिखो(plllc1en_field, 0);
	ret |= regmap_field_ग_लिखो(termen_field, 0);
	अगर (index == 1) अणु
		ret |= regmap_field_ग_लिखो(plllc1en_field, 1);
		ret |= regmap_field_ग_लिखो(termen_field, 1);
	पूर्ण

	val = cdns_sierra_pll_mux_table[index];
	ret |= regmap_field_ग_लिखो(field, val);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops cdns_sierra_pll_mux_ops = अणु
	.set_parent = cdns_sierra_pll_mux_set_parent,
	.get_parent = cdns_sierra_pll_mux_get_parent,
पूर्ण;

अटल पूर्णांक cdns_sierra_pll_mux_रेजिस्टर(काष्ठा cdns_sierra_phy *sp,
					काष्ठा regmap_field *pfdclk1_sel_field,
					काष्ठा regmap_field *plllc1en_field,
					काष्ठा regmap_field *termen_field,
					पूर्णांक clk_index)
अणु
	काष्ठा cdns_sierra_pll_mux *mux;
	काष्ठा device *dev = sp->dev;
	काष्ठा clk_init_data *init;
	स्थिर अक्षर **parent_names;
	अचिन्हित पूर्णांक num_parents;
	अक्षर clk_name[100];
	काष्ठा clk *clk;
	पूर्णांक i;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	num_parents = SIERRA_NUM_CMN_PLLC_PARENTS;
	parent_names = devm_kzalloc(dev, (माप(अक्षर *) * num_parents), GFP_KERNEL);
	अगर (!parent_names)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_parents; i++) अणु
		clk = sp->input_clks[pll_mux_parent_index[clk_index][i]];
		अगर (IS_ERR_OR_शून्य(clk)) अणु
			dev_err(dev, "No parent clock for derived_refclk\n");
			वापस PTR_ERR(clk);
		पूर्ण
		parent_names[i] = __clk_get_name(clk);
	पूर्ण

	snम_लिखो(clk_name, माप(clk_name), "%s_%s", dev_name(dev), clk_names[clk_index]);

	init = &mux->clk_data;

	init->ops = &cdns_sierra_pll_mux_ops;
	init->flags = CLK_SET_RATE_NO_REPARENT;
	init->parent_names = parent_names;
	init->num_parents = num_parents;
	init->name = clk_name;

	mux->pfdclk_sel_preg = pfdclk1_sel_field;
	mux->plllc1en_field = plllc1en_field;
	mux->termen_field = termen_field;
	mux->hw.init = init;

	clk = devm_clk_रेजिस्टर(dev, &mux->hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	sp->output_clks[clk_index] = clk;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_sierra_phy_रेजिस्टर_pll_mux(काष्ठा cdns_sierra_phy *sp)
अणु
	काष्ठा regmap_field *pfdclk1_sel_field;
	काष्ठा regmap_field *plllc1en_field;
	काष्ठा regmap_field *termen_field;
	काष्ठा device *dev = sp->dev;
	पूर्णांक ret = 0, i, clk_index;

	clk_index = CDNS_SIERRA_PLL_CMNLC;
	क्रम (i = 0; i < SIERRA_NUM_CMN_PLLC; i++, clk_index++) अणु
		pfdclk1_sel_field = sp->cmn_plllc_pfdclk1_sel_preg[i];
		plllc1en_field = sp->cmn_refrcv_refclk_plllc1en_preg[i];
		termen_field = sp->cmn_refrcv_refclk_termen_preg[i];

		ret = cdns_sierra_pll_mux_रेजिस्टर(sp, pfdclk1_sel_field, plllc1en_field,
						   termen_field, clk_index);
		अगर (ret) अणु
			dev_err(dev, "Fail to register cmn plllc mux\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम cdns_sierra_clk_unरेजिस्टर(काष्ठा cdns_sierra_phy *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा device_node *node = dev->of_node;

	of_clk_del_provider(node);
पूर्ण

अटल पूर्णांक cdns_sierra_clk_रेजिस्टर(काष्ठा cdns_sierra_phy *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret;

	ret = cdns_sierra_phy_रेजिस्टर_pll_mux(sp);
	अगर (ret) अणु
		dev_err(dev, "Failed to pll mux clocks\n");
		वापस ret;
	पूर्ण

	sp->clk_data.clks = sp->output_clks;
	sp->clk_data.clk_num = CDNS_SIERRA_OUTPUT_CLOCKS;
	ret = of_clk_add_provider(node, of_clk_src_onecell_get, &sp->clk_data);
	अगर (ret)
		dev_err(dev, "Failed to add clock provider: %s\n", node->name);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_sierra_get_optional(काष्ठा cdns_sierra_inst *inst,
				    काष्ठा device_node *child)
अणु
	अगर (of_property_पढ़ो_u32(child, "reg", &inst->mlane))
		वापस -EINVAL;

	अगर (of_property_पढ़ो_u32(child, "cdns,num-lanes", &inst->num_lanes))
		वापस -EINVAL;

	अगर (of_property_पढ़ो_u32(child, "cdns,phy-type", &inst->phy_type))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cdns_sierra_id_table[];

अटल काष्ठा regmap *cdns_regmap_init(काष्ठा device *dev, व्योम __iomem *base,
				       u32 block_offset, u8 reg_offset_shअगरt,
				       स्थिर काष्ठा regmap_config *config)
अणु
	काष्ठा cdns_regmap_cdb_context *ctx;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->dev = dev;
	ctx->base = base + block_offset;
	ctx->reg_offset_shअगरt = reg_offset_shअगरt;

	वापस devm_regmap_init(dev, शून्य, ctx, config);
पूर्ण

अटल पूर्णांक cdns_regfield_init(काष्ठा cdns_sierra_phy *sp)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा regmap_field *field;
	काष्ठा reg_field reg_field;
	काष्ठा regmap *regmap;
	पूर्णांक i;

	regmap = sp->regmap_common_cdb;
	field = devm_regmap_field_alloc(dev, regmap, macro_id_type);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "MACRO_ID_TYPE reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	sp->macro_id_type = field;

	क्रम (i = 0; i < SIERRA_NUM_CMN_PLLC; i++) अणु
		reg_field = cmn_plllc_pfdclk1_sel_preg[i].pfdclk_sel_preg;
		field = devm_regmap_field_alloc(dev, regmap, reg_field);
		अगर (IS_ERR(field)) अणु
			dev_err(dev, "PLLLC%d_PFDCLK1_SEL failed\n", i);
			वापस PTR_ERR(field);
		पूर्ण
		sp->cmn_plllc_pfdclk1_sel_preg[i] = field;

		reg_field = cmn_plllc_pfdclk1_sel_preg[i].plllc1en_field;
		field = devm_regmap_field_alloc(dev, regmap, reg_field);
		अगर (IS_ERR(field)) अणु
			dev_err(dev, "REFRCV%d_REFCLK_PLLLC1EN failed\n", i);
			वापस PTR_ERR(field);
		पूर्ण
		sp->cmn_refrcv_refclk_plllc1en_preg[i] = field;

		reg_field = cmn_plllc_pfdclk1_sel_preg[i].termen_field;
		field = devm_regmap_field_alloc(dev, regmap, reg_field);
		अगर (IS_ERR(field)) अणु
			dev_err(dev, "REFRCV%d_REFCLK_TERMEN failed\n", i);
			वापस PTR_ERR(field);
		पूर्ण
		sp->cmn_refrcv_refclk_termen_preg[i] = field;
	पूर्ण

	regmap = sp->regmap_phy_config_ctrl;
	field = devm_regmap_field_alloc(dev, regmap, phy_pll_cfg_1);
	अगर (IS_ERR(field)) अणु
		dev_err(dev, "PHY_PLL_CFG_1 reg field init failed\n");
		वापस PTR_ERR(field);
	पूर्ण
	sp->phy_pll_cfg_1 = field;

	क्रम (i = 0; i < SIERRA_MAX_LANES; i++) अणु
		regmap = sp->regmap_lane_cdb[i];
		field = devm_regmap_field_alloc(dev, regmap, pllctrl_lock);
		अगर (IS_ERR(field)) अणु
			dev_err(dev, "P%d_ENABLE reg field init failed\n", i);
			वापस PTR_ERR(field);
		पूर्ण
		sp->pllctrl_lock[i] =  field;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_regmap_init_blocks(काष्ठा cdns_sierra_phy *sp,
				   व्योम __iomem *base, u8 block_offset_shअगरt,
				   u8 reg_offset_shअगरt)
अणु
	काष्ठा device *dev = sp->dev;
	काष्ठा regmap *regmap;
	u32 block_offset;
	पूर्णांक i;

	क्रम (i = 0; i < SIERRA_MAX_LANES; i++) अणु
		block_offset = SIERRA_LANE_CDB_OFFSET(i, block_offset_shअगरt,
						      reg_offset_shअगरt);
		regmap = cdns_regmap_init(dev, base, block_offset,
					  reg_offset_shअगरt,
					  &cdns_sierra_lane_cdb_config[i]);
		अगर (IS_ERR(regmap)) अणु
			dev_err(dev, "Failed to init lane CDB regmap\n");
			वापस PTR_ERR(regmap);
		पूर्ण
		sp->regmap_lane_cdb[i] = regmap;
	पूर्ण

	regmap = cdns_regmap_init(dev, base, SIERRA_COMMON_CDB_OFFSET,
				  reg_offset_shअगरt,
				  &cdns_sierra_common_cdb_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to init common CDB regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	sp->regmap_common_cdb = regmap;

	block_offset = SIERRA_PHY_CONFIG_CTRL_OFFSET(block_offset_shअगरt);
	regmap = cdns_regmap_init(dev, base, block_offset, reg_offset_shअगरt,
				  &cdns_sierra_phy_config_ctrl_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to init PHY config and control regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	sp->regmap_phy_config_ctrl = regmap;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_sierra_phy_get_घड़ीs(काष्ठा cdns_sierra_phy *sp,
				      काष्ठा device *dev)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = devm_clk_get_optional(dev, "phy_clk");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to get clock phy_clk\n");
		वापस PTR_ERR(clk);
	पूर्ण
	sp->input_clks[PHY_CLK] = clk;

	clk = devm_clk_get_optional(dev, "cmn_refclk_dig_div");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "cmn_refclk_dig_div clock not found\n");
		ret = PTR_ERR(clk);
		वापस ret;
	पूर्ण
	sp->input_clks[CMN_REFCLK_DIG_DIV] = clk;

	clk = devm_clk_get_optional(dev, "cmn_refclk1_dig_div");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "cmn_refclk1_dig_div clock not found\n");
		ret = PTR_ERR(clk);
		वापस ret;
	पूर्ण
	sp->input_clks[CMN_REFCLK1_DIG_DIV] = clk;

	clk = devm_clk_get_optional(dev, "pll0_refclk");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "pll0_refclk clock not found\n");
		ret = PTR_ERR(clk);
		वापस ret;
	पूर्ण
	sp->input_clks[PLL0_REFCLK] = clk;

	clk = devm_clk_get_optional(dev, "pll1_refclk");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "pll1_refclk clock not found\n");
		ret = PTR_ERR(clk);
		वापस ret;
	पूर्ण
	sp->input_clks[PLL1_REFCLK] = clk;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_sierra_phy_enable_घड़ीs(काष्ठा cdns_sierra_phy *sp)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(sp->input_clks[PHY_CLK]);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(sp->output_clks[CDNS_SIERRA_PLL_CMNLC]);
	अगर (ret)
		जाओ err_pll_cmnlc;

	ret = clk_prepare_enable(sp->output_clks[CDNS_SIERRA_PLL_CMNLC1]);
	अगर (ret)
		जाओ err_pll_cmnlc1;

	वापस 0;

err_pll_cmnlc1:
	clk_disable_unprepare(sp->output_clks[CDNS_SIERRA_PLL_CMNLC]);

err_pll_cmnlc:
	clk_disable_unprepare(sp->input_clks[PHY_CLK]);

	वापस ret;
पूर्ण

अटल व्योम cdns_sierra_phy_disable_घड़ीs(काष्ठा cdns_sierra_phy *sp)
अणु
	clk_disable_unprepare(sp->output_clks[CDNS_SIERRA_PLL_CMNLC1]);
	clk_disable_unprepare(sp->output_clks[CDNS_SIERRA_PLL_CMNLC]);
	clk_disable_unprepare(sp->input_clks[PHY_CLK]);
पूर्ण

अटल पूर्णांक cdns_sierra_phy_get_resets(काष्ठा cdns_sierra_phy *sp,
				      काष्ठा device *dev)
अणु
	काष्ठा reset_control *rst;

	rst = devm_reset_control_get_exclusive(dev, "sierra_reset");
	अगर (IS_ERR(rst)) अणु
		dev_err(dev, "failed to get reset\n");
		वापस PTR_ERR(rst);
	पूर्ण
	sp->phy_rst = rst;

	rst = devm_reset_control_get_optional_exclusive(dev, "sierra_apb");
	अगर (IS_ERR(rst)) अणु
		dev_err(dev, "failed to get apb reset\n");
		वापस PTR_ERR(rst);
	पूर्ण
	sp->apb_rst = rst;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_sierra_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_sierra_phy *sp;
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा cdns_sierra_data *data;
	अचिन्हित पूर्णांक id_value;
	पूर्णांक i, ret, node = 0;
	व्योम __iomem *base;
	काष्ठा device_node *dn = dev->of_node, *child;

	अगर (of_get_child_count(dn) == 0)
		वापस -ENODEV;

	/* Get init data क्रम this PHY */
	match = of_match_device(cdns_sierra_id_table, dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा cdns_sierra_data *)match->data;

	sp = devm_kzalloc(dev, माप(*sp), GFP_KERNEL);
	अगर (!sp)
		वापस -ENOMEM;
	dev_set_drvdata(dev, sp);
	sp->dev = dev;
	sp->init_data = data;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		dev_err(dev, "missing \"reg\"\n");
		वापस PTR_ERR(base);
	पूर्ण

	ret = cdns_regmap_init_blocks(sp, base, data->block_offset_shअगरt,
				      data->reg_offset_shअगरt);
	अगर (ret)
		वापस ret;

	ret = cdns_regfield_init(sp);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, sp);

	ret = cdns_sierra_phy_get_घड़ीs(sp, dev);
	अगर (ret)
		वापस ret;

	ret = cdns_sierra_clk_रेजिस्टर(sp);
	अगर (ret)
		वापस ret;

	ret = cdns_sierra_phy_get_resets(sp, dev);
	अगर (ret)
		जाओ unरेजिस्टर_clk;

	ret = cdns_sierra_phy_enable_घड़ीs(sp);
	अगर (ret)
		जाओ unरेजिस्टर_clk;

	/* Enable APB */
	reset_control_deनिश्चित(sp->apb_rst);

	/* Check that PHY is present */
	regmap_field_पढ़ो(sp->macro_id_type, &id_value);
	अगर  (sp->init_data->id_value != id_value) अणु
		ret = -EINVAL;
		जाओ clk_disable;
	पूर्ण

	sp->स्वतःconf = of_property_पढ़ो_bool(dn, "cdns,autoconf");

	क्रम_each_available_child_of_node(dn, child) अणु
		काष्ठा phy *gphy;

		अगर (!(of_node_name_eq(child, "phy") ||
		      of_node_name_eq(child, "link")))
			जारी;

		sp->phys[node].lnk_rst =
			of_reset_control_array_get_exclusive(child);

		अगर (IS_ERR(sp->phys[node].lnk_rst)) अणु
			dev_err(dev, "failed to get reset %s\n",
				child->full_name);
			ret = PTR_ERR(sp->phys[node].lnk_rst);
			जाओ put_child2;
		पूर्ण

		अगर (!sp->स्वतःconf) अणु
			ret = cdns_sierra_get_optional(&sp->phys[node], child);
			अगर (ret) अणु
				dev_err(dev, "missing property in node %s\n",
					child->name);
				जाओ put_child;
			पूर्ण
		पूर्ण

		sp->num_lanes += sp->phys[node].num_lanes;

		gphy = devm_phy_create(dev, child, &ops);

		अगर (IS_ERR(gphy)) अणु
			ret = PTR_ERR(gphy);
			जाओ put_child;
		पूर्ण
		sp->phys[node].phy = gphy;
		phy_set_drvdata(gphy, &sp->phys[node]);

		node++;
	पूर्ण
	sp->nsubnodes = node;

	अगर (sp->num_lanes > SIERRA_MAX_LANES) अणु
		ret = -EINVAL;
		dev_err(dev, "Invalid lane configuration\n");
		जाओ put_child2;
	पूर्ण

	/* If more than one subnode, configure the PHY as multilink */
	अगर (!sp->स्वतःconf && sp->nsubnodes > 1)
		regmap_field_ग_लिखो(sp->phy_pll_cfg_1, 0x1);

	pm_runसमय_enable(dev);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);

put_child:
	node++;
put_child2:
	क्रम (i = 0; i < node; i++)
		reset_control_put(sp->phys[i].lnk_rst);
	of_node_put(child);
clk_disable:
	cdns_sierra_phy_disable_घड़ीs(sp);
	reset_control_निश्चित(sp->apb_rst);
unरेजिस्टर_clk:
	cdns_sierra_clk_unरेजिस्टर(sp);
	वापस ret;
पूर्ण

अटल पूर्णांक cdns_sierra_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_sierra_phy *phy = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	reset_control_निश्चित(phy->phy_rst);
	reset_control_निश्चित(phy->apb_rst);
	pm_runसमय_disable(&pdev->dev);

	cdns_sierra_phy_disable_घड़ीs(phy);
	/*
	 * The device level resets will be put स्वतःmatically.
	 * Need to put the subnode resets here though.
	 */
	क्रम (i = 0; i < phy->nsubnodes; i++) अणु
		reset_control_निश्चित(phy->phys[i].lnk_rst);
		reset_control_put(phy->phys[i].lnk_rst);
	पूर्ण

	cdns_sierra_clk_unरेजिस्टर(phy);

	वापस 0;
पूर्ण

/* refclk100MHz_32b_PCIe_cmn_pll_ext_ssc */
अटल स्थिर काष्ठा cdns_reg_pairs cdns_pcie_cmn_regs_ext_ssc[] = अणु
	अणु0x2106, SIERRA_CMN_PLLLC_LF_COEFF_MODE1_PREGपूर्ण,
	अणु0x2106, SIERRA_CMN_PLLLC_LF_COEFF_MODE0_PREGपूर्ण,
	अणु0x8A06, SIERRA_CMN_PLLLC_BWCAL_MODE1_PREGपूर्ण,
	अणु0x8A06, SIERRA_CMN_PLLLC_BWCAL_MODE0_PREGपूर्ण,
	अणु0x1B1B, SIERRA_CMN_PLLLC_SS_TIME_STEPSIZE_MODE_PREGपूर्ण
पूर्ण;

/* refclk100MHz_32b_PCIe_ln_ext_ssc */
अटल स्थिर काष्ठा cdns_reg_pairs cdns_pcie_ln_regs_ext_ssc[] = अणु
	अणु0x813E, SIERRA_CLKPATHCTRL_TMR_PREGपूर्ण,
	अणु0x8047, SIERRA_RX_CREQ_FLTR_A_MODE3_PREGपूर्ण,
	अणु0x808F, SIERRA_RX_CREQ_FLTR_A_MODE2_PREGपूर्ण,
	अणु0x808F, SIERRA_RX_CREQ_FLTR_A_MODE1_PREGपूर्ण,
	अणु0x808F, SIERRA_RX_CREQ_FLTR_A_MODE0_PREGपूर्ण,
	अणु0x033C, SIERRA_RX_CTLE_MAINTEन_अंकCE_PREGपूर्ण,
	अणु0x44CC, SIERRA_CREQ_EQ_OPEN_EYE_THRESH_PREGपूर्ण
पूर्ण;

/* refclk100MHz_20b_USB_cmn_pll_ext_ssc */
अटल स्थिर काष्ठा cdns_reg_pairs cdns_usb_cmn_regs_ext_ssc[] = अणु
	अणु0x2085, SIERRA_CMN_PLLLC_LF_COEFF_MODE1_PREGपूर्ण,
	अणु0x2085, SIERRA_CMN_PLLLC_LF_COEFF_MODE0_PREGपूर्ण,
	अणु0x0000, SIERRA_CMN_PLLLC_BWCAL_MODE0_PREGपूर्ण,
	अणु0x0000, SIERRA_CMN_PLLLC_SS_TIME_STEPSIZE_MODE_PREGपूर्ण
पूर्ण;

/* refclk100MHz_20b_USB_ln_ext_ssc */
अटल स्थिर काष्ठा cdns_reg_pairs cdns_usb_ln_regs_ext_ssc[] = अणु
	अणु0xFE0A, SIERRA_DET_STANDEC_A_PREGपूर्ण,
	अणु0x000F, SIERRA_DET_STANDEC_B_PREGपूर्ण,
	अणु0x55A5, SIERRA_DET_STANDEC_C_PREGपूर्ण,
	अणु0x69ad, SIERRA_DET_STANDEC_D_PREGपूर्ण,
	अणु0x0241, SIERRA_DET_STANDEC_E_PREGपूर्ण,
	अणु0x0110, SIERRA_PSM_LANECAL_DLY_A1_RESETS_PREGपूर्ण,
	अणु0x0014, SIERRA_PSM_A0IN_TMR_PREGपूर्ण,
	अणु0xCF00, SIERRA_PSM_DIAG_PREGपूर्ण,
	अणु0x001F, SIERRA_PSC_TX_A0_PREGपूर्ण,
	अणु0x0007, SIERRA_PSC_TX_A1_PREGपूर्ण,
	अणु0x0003, SIERRA_PSC_TX_A2_PREGपूर्ण,
	अणु0x0003, SIERRA_PSC_TX_A3_PREGपूर्ण,
	अणु0x0FFF, SIERRA_PSC_RX_A0_PREGपूर्ण,
	अणु0x0003, SIERRA_PSC_RX_A1_PREGपूर्ण,
	अणु0x0003, SIERRA_PSC_RX_A2_PREGपूर्ण,
	अणु0x0001, SIERRA_PSC_RX_A3_PREGपूर्ण,
	अणु0x0001, SIERRA_PLLCTRL_SUBRATE_PREGपूर्ण,
	अणु0x0406, SIERRA_PLLCTRL_GEN_D_PREGपूर्ण,
	अणु0x5233, SIERRA_PLLCTRL_CPGAIN_MODE_PREGपूर्ण,
	अणु0x00CA, SIERRA_CLKPATH_BIASTRIM_PREGपूर्ण,
	अणु0x2512, SIERRA_DFE_BIASTRIM_PREGपूर्ण,
	अणु0x0000, SIERRA_DRVCTRL_ATTEN_PREGपूर्ण,
	अणु0x823E, SIERRA_CLKPATHCTRL_TMR_PREGपूर्ण,
	अणु0x078F, SIERRA_RX_CREQ_FLTR_A_MODE1_PREGपूर्ण,
	अणु0x078F, SIERRA_RX_CREQ_FLTR_A_MODE0_PREGपूर्ण,
	अणु0x7B3C, SIERRA_CREQ_CCLKDET_MODE01_PREGपूर्ण,
	अणु0x023C, SIERRA_RX_CTLE_MAINTEन_अंकCE_PREGपूर्ण,
	अणु0x3232, SIERRA_CREQ_FSMCLK_SEL_PREGपूर्ण,
	अणु0x0000, SIERRA_CREQ_EQ_CTRL_PREGपूर्ण,
	अणु0x0000, SIERRA_CREQ_SPARE_PREGपूर्ण,
	अणु0xCC44, SIERRA_CREQ_EQ_OPEN_EYE_THRESH_PREGपूर्ण,
	अणु0x8452, SIERRA_CTLELUT_CTRL_PREGपूर्ण,
	अणु0x4121, SIERRA_DFE_ECMP_RATESEL_PREGपूर्ण,
	अणु0x4121, SIERRA_DFE_SMP_RATESEL_PREGपूर्ण,
	अणु0x0003, SIERRA_DEQ_PHALIGN_CTRLपूर्ण,
	अणु0x3200, SIERRA_DEQ_CONCUR_CTRL1_PREGपूर्ण,
	अणु0x5064, SIERRA_DEQ_CONCUR_CTRL2_PREGपूर्ण,
	अणु0x0030, SIERRA_DEQ_EPIPWR_CTRL2_PREGपूर्ण,
	अणु0x0048, SIERRA_DEQ_FAST_MAINT_CYCLES_PREGपूर्ण,
	अणु0x5A5A, SIERRA_DEQ_ERRCMP_CTRL_PREGपूर्ण,
	अणु0x02F5, SIERRA_DEQ_OFFSET_CTRL_PREGपूर्ण,
	अणु0x02F5, SIERRA_DEQ_GAIN_CTRL_PREGपूर्ण,
	अणु0x9999, SIERRA_DEQ_VGATUNE_CTRL_PREGपूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT0पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT1पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT2पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT3पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT4पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT5पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT6पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT7पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT8पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT9पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT10पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT11पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT12पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT13पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT14पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT15पूर्ण,
	अणु0x0014, SIERRA_DEQ_GLUT16पूर्ण,
	अणु0x0BAE, SIERRA_DEQ_ALUT0पूर्ण,
	अणु0x0AEB, SIERRA_DEQ_ALUT1पूर्ण,
	अणु0x0A28, SIERRA_DEQ_ALUT2पूर्ण,
	अणु0x0965, SIERRA_DEQ_ALUT3पूर्ण,
	अणु0x08A2, SIERRA_DEQ_ALUT4पूर्ण,
	अणु0x07DF, SIERRA_DEQ_ALUT5पूर्ण,
	अणु0x071C, SIERRA_DEQ_ALUT6पूर्ण,
	अणु0x0659, SIERRA_DEQ_ALUT7पूर्ण,
	अणु0x0596, SIERRA_DEQ_ALUT8पूर्ण,
	अणु0x0514, SIERRA_DEQ_ALUT9पूर्ण,
	अणु0x0492, SIERRA_DEQ_ALUT10पूर्ण,
	अणु0x0410, SIERRA_DEQ_ALUT11पूर्ण,
	अणु0x038E, SIERRA_DEQ_ALUT12पूर्ण,
	अणु0x030C, SIERRA_DEQ_ALUT13पूर्ण,
	अणु0x03F4, SIERRA_DEQ_DFETAP_CTRL_PREGपूर्ण,
	अणु0x0001, SIERRA_DFE_EN_1010_IGNORE_PREGपूर्ण,
	अणु0x3C01, SIERRA_DEQ_TAU_CTRL1_FAST_MAINT_PREGपूर्ण,
	अणु0x3C40, SIERRA_DEQ_TAU_CTRL1_SLOW_MAINT_PREGपूर्ण,
	अणु0x1C08, SIERRA_DEQ_TAU_CTRL2_PREGपूर्ण,
	अणु0x0033, SIERRA_DEQ_PICTRL_PREGपूर्ण,
	अणु0x0400, SIERRA_CPICAL_TMRVAL_MODE1_PREGपूर्ण,
	अणु0x0330, SIERRA_CPICAL_TMRVAL_MODE0_PREGपूर्ण,
	अणु0x01FF, SIERRA_CPICAL_PICNT_MODE1_PREGपूर्ण,
	अणु0x0009, SIERRA_CPI_OUTBUF_RATESEL_PREGपूर्ण,
	अणु0x3232, SIERRA_CPICAL_RES_STARTCODE_MODE23_PREGपूर्ण,
	अणु0x0005, SIERRA_LFPSDET_SUPPORT_PREGपूर्ण,
	अणु0x000F, SIERRA_LFPSFILT_NS_PREGपूर्ण,
	अणु0x0009, SIERRA_LFPSFILT_RD_PREGपूर्ण,
	अणु0x0001, SIERRA_LFPSFILT_MP_PREGपूर्ण,
	अणु0x6013, SIERRA_SIGDET_SUPPORT_PREGपूर्ण,
	अणु0x8013, SIERRA_SDFILT_H2L_A_PREGपूर्ण,
	अणु0x8009, SIERRA_SDFILT_L2H_PREGपूर्ण,
	अणु0x0024, SIERRA_RXBUFFER_CTLECTRL_PREGपूर्ण,
	अणु0x0020, SIERRA_RXBUFFER_RCDFECTRL_PREGपूर्ण,
	अणु0x4243, SIERRA_RXBUFFER_DFECTRL_PREGपूर्ण
पूर्ण;

अटल स्थिर काष्ठा cdns_sierra_data cdns_map_sierra = अणु
	SIERRA_MACRO_ID,
	0x2,
	0x2,
	ARRAY_SIZE(cdns_pcie_cmn_regs_ext_ssc),
	ARRAY_SIZE(cdns_pcie_ln_regs_ext_ssc),
	ARRAY_SIZE(cdns_usb_cmn_regs_ext_ssc),
	ARRAY_SIZE(cdns_usb_ln_regs_ext_ssc),
	cdns_pcie_cmn_regs_ext_ssc,
	cdns_pcie_ln_regs_ext_ssc,
	cdns_usb_cmn_regs_ext_ssc,
	cdns_usb_ln_regs_ext_ssc,
पूर्ण;

अटल स्थिर काष्ठा cdns_sierra_data cdns_ti_map_sierra = अणु
	SIERRA_MACRO_ID,
	0x0,
	0x1,
	ARRAY_SIZE(cdns_pcie_cmn_regs_ext_ssc),
	ARRAY_SIZE(cdns_pcie_ln_regs_ext_ssc),
	ARRAY_SIZE(cdns_usb_cmn_regs_ext_ssc),
	ARRAY_SIZE(cdns_usb_ln_regs_ext_ssc),
	cdns_pcie_cmn_regs_ext_ssc,
	cdns_pcie_ln_regs_ext_ssc,
	cdns_usb_cmn_regs_ext_ssc,
	cdns_usb_ln_regs_ext_ssc,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_sierra_id_table[] = अणु
	अणु
		.compatible = "cdns,sierra-phy-t0",
		.data = &cdns_map_sierra,
	पूर्ण,
	अणु
		.compatible = "ti,sierra-phy-t0",
		.data = &cdns_ti_map_sierra,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_sierra_id_table);

अटल काष्ठा platक्रमm_driver cdns_sierra_driver = अणु
	.probe		= cdns_sierra_phy_probe,
	.हटाओ		= cdns_sierra_phy_हटाओ,
	.driver		= अणु
		.name	= "cdns-sierra-phy",
		.of_match_table = cdns_sierra_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cdns_sierra_driver);

MODULE_ALIAS("platform:cdns_sierra");
MODULE_AUTHOR("Cadence Design Systems");
MODULE_DESCRIPTION("CDNS sierra phy driver");
MODULE_LICENSE("GPL v2");
