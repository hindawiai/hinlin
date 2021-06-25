<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Marvell Armada 37xx SoC Peripheral घड़ीs
 *
 * Copyright (C) 2016 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 *
 * Most of the peripheral घड़ीs can be modelled like this:
 *             _____    _______    _______
 * TBG-A-P  --|     |  |       |  |       |   ______
 * TBG-B-P  --| Mux |--| /भाग1 |--| /भाग2 |--| Gate |--> perip_clk
 * TBG-A-S  --|     |  |       |  |       |  |______|
 * TBG-B-S  --|_____|  |_______|  |_______|
 *
 * However some घड़ीs may use only one or two block or and use the
 * xtal घड़ी as parent.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा TBG_SEL		0x0
#घोषणा DIV_SEL0	0x4
#घोषणा DIV_SEL1	0x8
#घोषणा DIV_SEL2	0xC
#घोषणा CLK_SEL		0x10
#घोषणा CLK_DIS		0x14

#घोषणा  ARMADA_37XX_DVFS_LOAD_1 1
#घोषणा LOAD_LEVEL_NR	4

#घोषणा ARMADA_37XX_NB_L0L1	0x18
#घोषणा ARMADA_37XX_NB_L2L3	0x1C
#घोषणा		ARMADA_37XX_NB_TBG_DIV_OFF	13
#घोषणा		ARMADA_37XX_NB_TBG_DIV_MASK	0x7
#घोषणा		ARMADA_37XX_NB_CLK_SEL_OFF	11
#घोषणा		ARMADA_37XX_NB_CLK_SEL_MASK	0x1
#घोषणा		ARMADA_37XX_NB_TBG_SEL_OFF	9
#घोषणा		ARMADA_37XX_NB_TBG_SEL_MASK	0x3
#घोषणा		ARMADA_37XX_NB_CONFIG_SHIFT	16
#घोषणा ARMADA_37XX_NB_DYN_MOD	0x24
#घोषणा		ARMADA_37XX_NB_DFS_EN	31
#घोषणा ARMADA_37XX_NB_CPU_LOAD	0x30
#घोषणा		ARMADA_37XX_NB_CPU_LOAD_MASK	0x3
#घोषणा		ARMADA_37XX_DVFS_LOAD_0		0
#घोषणा		ARMADA_37XX_DVFS_LOAD_1		1
#घोषणा		ARMADA_37XX_DVFS_LOAD_2		2
#घोषणा		ARMADA_37XX_DVFS_LOAD_3		3

काष्ठा clk_periph_driver_data अणु
	काष्ठा clk_hw_onecell_data *hw_data;
	spinlock_t lock;
	व्योम __iomem *reg;

	/* Storage रेजिस्टरs क्रम suspend/resume operations */
	u32 tbg_sel;
	u32 भाग_sel0;
	u32 भाग_sel1;
	u32 भाग_sel2;
	u32 clk_sel;
	u32 clk_dis;
पूर्ण;

काष्ठा clk_द्विगुन_भाग अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg1;
	u8 shअगरt1;
	व्योम __iomem *reg2;
	u8 shअगरt2;
पूर्ण;

काष्ठा clk_pm_cpu अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg_mux;
	u8 shअगरt_mux;
	u32 mask_mux;
	व्योम __iomem *reg_भाग;
	u8 shअगरt_भाग;
	काष्ठा regmap *nb_pm_base;
	अचिन्हित दीर्घ l1_expiration;
पूर्ण;

#घोषणा to_clk_द्विगुन_भाग(_hw) container_of(_hw, काष्ठा clk_द्विगुन_भाग, hw)
#घोषणा to_clk_pm_cpu(_hw) container_of(_hw, काष्ठा clk_pm_cpu, hw)

काष्ठा clk_periph_data अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_names;
	पूर्णांक num_parents;
	काष्ठा clk_hw *mux_hw;
	काष्ठा clk_hw *rate_hw;
	काष्ठा clk_hw *gate_hw;
	काष्ठा clk_hw *muxrate_hw;
	bool is_द्विगुन_भाग;
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable clk_table6[] = अणु
	अणु .val = 1, .भाग = 1, पूर्ण,
	अणु .val = 2, .भाग = 2, पूर्ण,
	अणु .val = 3, .भाग = 3, पूर्ण,
	अणु .val = 4, .भाग = 4, पूर्ण,
	अणु .val = 5, .भाग = 5, पूर्ण,
	अणु .val = 6, .भाग = 6, पूर्ण,
	अणु .val = 0, .भाग = 0, पूर्ण, /* last entry */
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable clk_table1[] = अणु
	अणु .val = 0, .भाग = 1, पूर्ण,
	अणु .val = 1, .भाग = 2, पूर्ण,
	अणु .val = 0, .भाग = 0, पूर्ण, /* last entry */
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable clk_table2[] = अणु
	अणु .val = 0, .भाग = 2, पूर्ण,
	अणु .val = 1, .भाग = 4, पूर्ण,
	अणु .val = 0, .भाग = 0, पूर्ण, /* last entry */
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_द्विगुन_भाग_ops;
अटल स्थिर काष्ठा clk_ops clk_pm_cpu_ops;

#घोषणा PERIPH_GATE(_name, _bit)		\
काष्ठा clk_gate gate_##_name = अणु		\
	.reg = (व्योम *)CLK_DIS,			\
	.bit_idx = _bit,			\
	.hw.init = &(काष्ठा clk_init_data)अणु	\
		.ops =  &clk_gate_ops,		\
	पूर्ण					\
पूर्ण;

#घोषणा PERIPH_MUX(_name, _shअगरt)		\
काष्ठा clk_mux mux_##_name = अणु			\
	.reg = (व्योम *)TBG_SEL,			\
	.shअगरt = _shअगरt,			\
	.mask = 3,				\
	.hw.init = &(काष्ठा clk_init_data)अणु	\
		.ops =  &clk_mux_ro_ops,	\
	पूर्ण					\
पूर्ण;

#घोषणा PERIPH_DOUBLEDIV(_name, _reg1, _reg2, _shअगरt1, _shअगरt2)	\
काष्ठा clk_द्विगुन_भाग rate_##_name = अणु		\
	.reg1 = (व्योम *)_reg1,			\
	.reg2 = (व्योम *)_reg2,			\
	.shअगरt1 = _shअगरt1,			\
	.shअगरt2 = _shअगरt2,			\
	.hw.init = &(काष्ठा clk_init_data)अणु	\
		.ops =  &clk_द्विगुन_भाग_ops,	\
	पूर्ण					\
पूर्ण;

#घोषणा PERIPH_DIV(_name, _reg, _shअगरt, _table)	\
काष्ठा clk_भागider rate_##_name = अणु		\
	.reg = (व्योम *)_reg,			\
	.table = _table,			\
	.shअगरt = _shअगरt,			\
	.hw.init = &(काष्ठा clk_init_data)अणु	\
		.ops =  &clk_भागider_ro_ops,	\
	पूर्ण					\
पूर्ण;

#घोषणा PERIPH_PM_CPU(_name, _shअगरt1, _reg, _shअगरt2)	\
काष्ठा clk_pm_cpu muxrate_##_name = अणु		\
	.reg_mux = (व्योम *)TBG_SEL,		\
	.mask_mux = 3,				\
	.shअगरt_mux = _shअगरt1,			\
	.reg_भाग = (व्योम *)_reg,		\
	.shअगरt_भाग = _shअगरt2,			\
	.hw.init = &(काष्ठा clk_init_data)अणु	\
		.ops =  &clk_pm_cpu_ops,	\
	पूर्ण					\
पूर्ण;

#घोषणा PERIPH_CLK_FULL_DD(_name, _bit, _shअगरt, _reg1, _reg2, _shअगरt1, _shअगरt2)\
अटल PERIPH_GATE(_name, _bit);			    \
अटल PERIPH_MUX(_name, _shअगरt);			    \
अटल PERIPH_DOUBLEDIV(_name, _reg1, _reg2, _shअगरt1, _shअगरt2);

#घोषणा PERIPH_CLK_FULL(_name, _bit, _shअगरt, _reg, _shअगरt1, _table)	\
अटल PERIPH_GATE(_name, _bit);			    \
अटल PERIPH_MUX(_name, _shअगरt);			    \
अटल PERIPH_DIV(_name, _reg, _shअगरt1, _table);

#घोषणा PERIPH_CLK_GATE_DIV(_name, _bit,  _reg, _shअगरt, _table)	\
अटल PERIPH_GATE(_name, _bit);			\
अटल PERIPH_DIV(_name, _reg, _shअगरt, _table);

#घोषणा PERIPH_CLK_MUX_DD(_name, _shअगरt, _reg1, _reg2, _shअगरt1, _shअगरt2)\
अटल PERIPH_MUX(_name, _shअगरt);			    \
अटल PERIPH_DOUBLEDIV(_name, _reg1, _reg2, _shअगरt1, _shअगरt2);

#घोषणा REF_CLK_FULL(_name)				\
	अणु .name = #_name,				\
	  .parent_names = (स्थिर अक्षर *[])अणु "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"पूर्ण,		\
	  .num_parents = 4,				\
	  .mux_hw = &mux_##_name.hw,			\
	  .gate_hw = &gate_##_name.hw,			\
	  .rate_hw = &rate_##_name.hw,			\
	पूर्ण

#घोषणा REF_CLK_FULL_DD(_name)				\
	अणु .name = #_name,				\
	  .parent_names = (स्थिर अक्षर *[])अणु "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"पूर्ण,		\
	  .num_parents = 4,				\
	  .mux_hw = &mux_##_name.hw,			\
	  .gate_hw = &gate_##_name.hw,			\
	  .rate_hw = &rate_##_name.hw,			\
	  .is_द्विगुन_भाग = true,			\
	पूर्ण

#घोषणा REF_CLK_GATE(_name, _parent_name)			\
	अणु .name = #_name,					\
	  .parent_names = (स्थिर अक्षर *[])अणु _parent_nameपूर्ण,	\
	  .num_parents = 1,					\
	  .gate_hw = &gate_##_name.hw,				\
	पूर्ण

#घोषणा REF_CLK_GATE_DIV(_name, _parent_name)			\
	अणु .name = #_name,					\
	  .parent_names = (स्थिर अक्षर *[])अणु _parent_nameपूर्ण,	\
	  .num_parents = 1,					\
	  .gate_hw = &gate_##_name.hw,				\
	  .rate_hw = &rate_##_name.hw,				\
	पूर्ण

#घोषणा REF_CLK_PM_CPU(_name)				\
	अणु .name = #_name,				\
	  .parent_names = (स्थिर अक्षर *[])अणु "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"पूर्ण,		\
	  .num_parents = 4,				\
	  .muxrate_hw = &muxrate_##_name.hw,		\
	पूर्ण

#घोषणा REF_CLK_MUX_DD(_name)				\
	अणु .name = #_name,				\
	  .parent_names = (स्थिर अक्षर *[])अणु "TBG-A-P",	\
	      "TBG-B-P", "TBG-A-S", "TBG-B-S"पूर्ण,		\
	  .num_parents = 4,				\
	  .mux_hw = &mux_##_name.hw,			\
	  .rate_hw = &rate_##_name.hw,			\
	  .is_द्विगुन_भाग = true,			\
	पूर्ण

/* NB periph घड़ीs */
PERIPH_CLK_FULL_DD(mmc, 2, 0, DIV_SEL2, DIV_SEL2, 16, 13);
PERIPH_CLK_FULL_DD(sata_host, 3, 2, DIV_SEL2, DIV_SEL2, 10, 7);
PERIPH_CLK_FULL_DD(sec_at, 6, 4, DIV_SEL1, DIV_SEL1, 3, 0);
PERIPH_CLK_FULL_DD(sec_dap, 7, 6, DIV_SEL1, DIV_SEL1, 9, 6);
PERIPH_CLK_FULL_DD(tscem, 8, 8, DIV_SEL1, DIV_SEL1, 15, 12);
PERIPH_CLK_FULL(tscem_पंचांगx, 10, 10, DIV_SEL1, 18, clk_table6);
अटल PERIPH_GATE(avs, 11);
PERIPH_CLK_FULL_DD(pwm, 13, 14, DIV_SEL0, DIV_SEL0, 3, 0);
PERIPH_CLK_FULL_DD(sqf, 12, 12, DIV_SEL1, DIV_SEL1, 27, 24);
अटल PERIPH_GATE(i2c_2, 16);
अटल PERIPH_GATE(i2c_1, 17);
PERIPH_CLK_GATE_DIV(ddr_phy, 19, DIV_SEL0, 18, clk_table2);
PERIPH_CLK_FULL_DD(ddr_fclk, 21, 16, DIV_SEL0, DIV_SEL0, 15, 12);
PERIPH_CLK_FULL(trace, 22, 18, DIV_SEL0, 20, clk_table6);
PERIPH_CLK_FULL(counter, 23, 20, DIV_SEL0, 23, clk_table6);
PERIPH_CLK_FULL_DD(eip97, 24, 24, DIV_SEL2, DIV_SEL2, 22, 19);
अटल PERIPH_PM_CPU(cpu, 22, DIV_SEL0, 28);

अटल काष्ठा clk_periph_data data_nb[] = अणु
	REF_CLK_FULL_DD(mmc),
	REF_CLK_FULL_DD(sata_host),
	REF_CLK_FULL_DD(sec_at),
	REF_CLK_FULL_DD(sec_dap),
	REF_CLK_FULL_DD(tscem),
	REF_CLK_FULL(tscem_पंचांगx),
	REF_CLK_GATE(avs, "xtal"),
	REF_CLK_FULL_DD(sqf),
	REF_CLK_FULL_DD(pwm),
	REF_CLK_GATE(i2c_2, "xtal"),
	REF_CLK_GATE(i2c_1, "xtal"),
	REF_CLK_GATE_DIV(ddr_phy, "TBG-A-S"),
	REF_CLK_FULL_DD(ddr_fclk),
	REF_CLK_FULL(trace),
	REF_CLK_FULL(counter),
	REF_CLK_FULL_DD(eip97),
	REF_CLK_PM_CPU(cpu),
	अणु पूर्ण,
पूर्ण;

/* SB periph घड़ीs */
PERIPH_CLK_MUX_DD(gbe_50, 6, DIV_SEL2, DIV_SEL2, 6, 9);
PERIPH_CLK_MUX_DD(gbe_core, 8, DIV_SEL1, DIV_SEL1, 18, 21);
PERIPH_CLK_MUX_DD(gbe_125, 10, DIV_SEL1, DIV_SEL1, 6, 9);
अटल PERIPH_GATE(gbe1_50, 0);
अटल PERIPH_GATE(gbe0_50, 1);
अटल PERIPH_GATE(gbe1_125, 2);
अटल PERIPH_GATE(gbe0_125, 3);
PERIPH_CLK_GATE_DIV(gbe1_core, 4, DIV_SEL1, 13, clk_table1);
PERIPH_CLK_GATE_DIV(gbe0_core, 5, DIV_SEL1, 14, clk_table1);
PERIPH_CLK_GATE_DIV(gbe_bm, 12, DIV_SEL1, 0, clk_table1);
PERIPH_CLK_FULL_DD(sdio, 11, 14, DIV_SEL0, DIV_SEL0, 3, 6);
PERIPH_CLK_FULL_DD(usb32_usb2_sys, 16, 16, DIV_SEL0, DIV_SEL0, 9, 12);
PERIPH_CLK_FULL_DD(usb32_ss_sys, 17, 18, DIV_SEL0, DIV_SEL0, 15, 18);
अटल PERIPH_GATE(pcie, 14);

अटल काष्ठा clk_periph_data data_sb[] = अणु
	REF_CLK_MUX_DD(gbe_50),
	REF_CLK_MUX_DD(gbe_core),
	REF_CLK_MUX_DD(gbe_125),
	REF_CLK_GATE(gbe1_50, "gbe_50"),
	REF_CLK_GATE(gbe0_50, "gbe_50"),
	REF_CLK_GATE(gbe1_125, "gbe_125"),
	REF_CLK_GATE(gbe0_125, "gbe_125"),
	REF_CLK_GATE_DIV(gbe1_core, "gbe_core"),
	REF_CLK_GATE_DIV(gbe0_core, "gbe_core"),
	REF_CLK_GATE_DIV(gbe_bm, "gbe_core"),
	REF_CLK_FULL_DD(sdio),
	REF_CLK_FULL_DD(usb32_usb2_sys),
	REF_CLK_FULL_DD(usb32_ss_sys),
	REF_CLK_GATE(pcie, "gbe_core"),
	अणु पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक get_भाग(व्योम __iomem *reg, पूर्णांक shअगरt)
अणु
	u32 val;

	val = (पढ़ोl(reg) >> shअगरt) & 0x7;
	अगर (val > 6)
		वापस 0;
	वापस val;
पूर्ण

अटल अचिन्हित दीर्घ clk_द्विगुन_भाग_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_द्विगुन_भाग *द्विगुन_भाग = to_clk_द्विगुन_भाग(hw);
	अचिन्हित पूर्णांक भाग;

	भाग = get_भाग(द्विगुन_भाग->reg1, द्विगुन_भाग->shअगरt1);
	भाग *= get_भाग(द्विगुन_भाग->reg2, द्विगुन_भाग->shअगरt2);

	वापस DIV_ROUND_UP_ULL((u64)parent_rate, भाग);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_द्विगुन_भाग_ops = अणु
	.recalc_rate = clk_द्विगुन_भाग_recalc_rate,
पूर्ण;

अटल व्योम armada_3700_pm_dvfs_update_regs(अचिन्हित पूर्णांक load_level,
					    अचिन्हित पूर्णांक *reg,
					    अचिन्हित पूर्णांक *offset)
अणु
	अगर (load_level <= ARMADA_37XX_DVFS_LOAD_1)
		*reg = ARMADA_37XX_NB_L0L1;
	अन्यथा
		*reg = ARMADA_37XX_NB_L2L3;

	अगर (load_level == ARMADA_37XX_DVFS_LOAD_0 ||
	    load_level ==  ARMADA_37XX_DVFS_LOAD_2)
		*offset += ARMADA_37XX_NB_CONFIG_SHIFT;
पूर्ण

अटल bool armada_3700_pm_dvfs_is_enabled(काष्ठा regmap *base)
अणु
	अचिन्हित पूर्णांक val, reg = ARMADA_37XX_NB_DYN_MOD;

	अगर (IS_ERR(base))
		वापस false;

	regmap_पढ़ो(base, reg, &val);

	वापस !!(val & BIT(ARMADA_37XX_NB_DFS_EN));
पूर्ण

अटल अचिन्हित पूर्णांक armada_3700_pm_dvfs_get_cpu_भाग(काष्ठा regmap *base)
अणु
	अचिन्हित पूर्णांक reg = ARMADA_37XX_NB_CPU_LOAD;
	अचिन्हित पूर्णांक offset = ARMADA_37XX_NB_TBG_DIV_OFF;
	अचिन्हित पूर्णांक load_level, भाग;

	/*
	 * This function is always called after the function
	 * armada_3700_pm_dvfs_is_enabled, so no need to check again
	 * अगर the base is valid.
	 */
	regmap_पढ़ो(base, reg, &load_level);

	/*
	 * The रेजिस्टर and the offset inside this रेजिस्टर accessed to
	 * पढ़ो the current भागider depend on the load level
	 */
	load_level &= ARMADA_37XX_NB_CPU_LOAD_MASK;
	armada_3700_pm_dvfs_update_regs(load_level, &reg, &offset);

	regmap_पढ़ो(base, reg, &भाग);

	वापस (भाग >> offset) & ARMADA_37XX_NB_TBG_DIV_MASK;
पूर्ण

अटल अचिन्हित पूर्णांक armada_3700_pm_dvfs_get_cpu_parent(काष्ठा regmap *base)
अणु
	अचिन्हित पूर्णांक reg = ARMADA_37XX_NB_CPU_LOAD;
	अचिन्हित पूर्णांक offset = ARMADA_37XX_NB_TBG_SEL_OFF;
	अचिन्हित पूर्णांक load_level, sel;

	/*
	 * This function is always called after the function
	 * armada_3700_pm_dvfs_is_enabled, so no need to check again
	 * अगर the base is valid
	 */
	regmap_पढ़ो(base, reg, &load_level);

	/*
	 * The रेजिस्टर and the offset inside this रेजिस्टर accessed to
	 * पढ़ो the current भागider depend on the load level
	 */
	load_level &= ARMADA_37XX_NB_CPU_LOAD_MASK;
	armada_3700_pm_dvfs_update_regs(load_level, &reg, &offset);

	regmap_पढ़ो(base, reg, &sel);

	वापस (sel >> offset) & ARMADA_37XX_NB_TBG_SEL_MASK;
पूर्ण

अटल u8 clk_pm_cpu_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pm_cpu *pm_cpu = to_clk_pm_cpu(hw);
	u32 val;

	अगर (armada_3700_pm_dvfs_is_enabled(pm_cpu->nb_pm_base)) अणु
		val = armada_3700_pm_dvfs_get_cpu_parent(pm_cpu->nb_pm_base);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(pm_cpu->reg_mux) >> pm_cpu->shअगरt_mux;
		val &= pm_cpu->mask_mux;
	पूर्ण

	वापस val;
पूर्ण

अटल अचिन्हित दीर्घ clk_pm_cpu_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pm_cpu *pm_cpu = to_clk_pm_cpu(hw);
	अचिन्हित पूर्णांक भाग;

	अगर (armada_3700_pm_dvfs_is_enabled(pm_cpu->nb_pm_base))
		भाग = armada_3700_pm_dvfs_get_cpu_भाग(pm_cpu->nb_pm_base);
	अन्यथा
		भाग = get_भाग(pm_cpu->reg_भाग, pm_cpu->shअगरt_भाग);
	वापस DIV_ROUND_UP_ULL((u64)parent_rate, भाग);
पूर्ण

अटल दीर्घ clk_pm_cpu_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_pm_cpu *pm_cpu = to_clk_pm_cpu(hw);
	काष्ठा regmap *base = pm_cpu->nb_pm_base;
	अचिन्हित पूर्णांक भाग = *parent_rate / rate;
	अचिन्हित पूर्णांक load_level;
	/* only available when DVFS is enabled */
	अगर (!armada_3700_pm_dvfs_is_enabled(base))
		वापस -EINVAL;

	क्रम (load_level = 0; load_level < LOAD_LEVEL_NR; load_level++) अणु
		अचिन्हित पूर्णांक reg, val, offset = ARMADA_37XX_NB_TBG_DIV_OFF;

		armada_3700_pm_dvfs_update_regs(load_level, &reg, &offset);

		regmap_पढ़ो(base, reg, &val);

		val >>= offset;
		val &= ARMADA_37XX_NB_TBG_DIV_MASK;
		अगर (val == भाग)
			/*
			 * We found a load level matching the target
			 * भागider, चयन to this load level and
			 * वापस.
			 */
			वापस *parent_rate / भाग;
	पूर्ण

	/* We didn't find any valid भागider */
	वापस -EINVAL;
पूर्ण

/*
 * Workaround when base CPU frequnecy is 1000 or 1200 MHz
 *
 * Switching the CPU from the L2 or L3 frequencies (250/300 or 200 MHz
 * respectively) to L0 frequency (1/1.2 GHz) requires a signअगरicant
 * amount of समय to let VDD stabilize to the appropriate
 * voltage. This amount of समय is large enough that it cannot be
 * covered by the hardware countकरोwn रेजिस्टर. Due to this, the CPU
 * might start operating at L0 beक्रमe the voltage is stabilized,
 * leading to CPU stalls.
 *
 * To work around this problem, we prevent चयनing directly from the
 * L2/L3 frequencies to the L0 frequency, and instead चयन to the L1
 * frequency in-between. The sequence thereक्रमe becomes:
 * 1. First चयन from L2/L3 (200/250/300 MHz) to L1 (500/600 MHz)
 * 2. Sleep 20ms क्रम stabling VDD voltage
 * 3. Then चयन from L1 (500/600 MHz) to L0 (1000/1200 MHz).
 */
अटल व्योम clk_pm_cpu_set_rate_wa(काष्ठा clk_pm_cpu *pm_cpu,
				   अचिन्हित पूर्णांक new_level, अचिन्हित दीर्घ rate,
				   काष्ठा regmap *base)
अणु
	अचिन्हित पूर्णांक cur_level;

	regmap_पढ़ो(base, ARMADA_37XX_NB_CPU_LOAD, &cur_level);
	cur_level &= ARMADA_37XX_NB_CPU_LOAD_MASK;

	अगर (cur_level == new_level)
		वापस;

	/*
	 * System wants to go to L1 on its own. If we are going from L2/L3,
	 * remember when 20ms will expire. If from L0, set the value so that
	 * next चयन to L0 won't have to रुको.
	 */
	अगर (new_level == ARMADA_37XX_DVFS_LOAD_1) अणु
		अगर (cur_level == ARMADA_37XX_DVFS_LOAD_0)
			pm_cpu->l1_expiration = jअगरfies;
		अन्यथा
			pm_cpu->l1_expiration = jअगरfies + msecs_to_jअगरfies(20);
		वापस;
	पूर्ण

	/*
	 * If we are setting to L2/L3, just invalidate L1 expiration समय,
	 * sleeping is not needed.
	 */
	अगर (rate < 1000*1000*1000)
		जाओ invalidate_l1_exp;

	/*
	 * We are going to L0 with rate >= 1GHz. Check whether we have been at
	 * L1 क्रम दीर्घ enough समय. If not, go to L1 क्रम 20ms.
	 */
	अगर (pm_cpu->l1_expiration && jअगरfies >= pm_cpu->l1_expiration)
		जाओ invalidate_l1_exp;

	regmap_update_bits(base, ARMADA_37XX_NB_CPU_LOAD,
			   ARMADA_37XX_NB_CPU_LOAD_MASK,
			   ARMADA_37XX_DVFS_LOAD_1);
	msleep(20);

invalidate_l1_exp:
	pm_cpu->l1_expiration = 0;
पूर्ण

अटल पूर्णांक clk_pm_cpu_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pm_cpu *pm_cpu = to_clk_pm_cpu(hw);
	काष्ठा regmap *base = pm_cpu->nb_pm_base;
	अचिन्हित पूर्णांक भाग = parent_rate / rate;
	अचिन्हित पूर्णांक load_level;

	/* only available when DVFS is enabled */
	अगर (!armada_3700_pm_dvfs_is_enabled(base))
		वापस -EINVAL;

	क्रम (load_level = 0; load_level < LOAD_LEVEL_NR; load_level++) अणु
		अचिन्हित पूर्णांक reg, mask, val,
			offset = ARMADA_37XX_NB_TBG_DIV_OFF;

		armada_3700_pm_dvfs_update_regs(load_level, &reg, &offset);

		regmap_पढ़ो(base, reg, &val);
		val >>= offset;
		val &= ARMADA_37XX_NB_TBG_DIV_MASK;

		अगर (val == भाग) अणु
			/*
			 * We found a load level matching the target
			 * भागider, चयन to this load level and
			 * वापस.
			 */
			reg = ARMADA_37XX_NB_CPU_LOAD;
			mask = ARMADA_37XX_NB_CPU_LOAD_MASK;

			/* Apply workaround when base CPU frequency is 1000 or 1200 MHz */
			अगर (parent_rate >= 1000*1000*1000)
				clk_pm_cpu_set_rate_wa(pm_cpu, load_level, rate, base);

			regmap_update_bits(base, reg, mask, load_level);

			वापस rate;
		पूर्ण
	पूर्ण

	/* We didn't find any valid भागider */
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pm_cpu_ops = अणु
	.get_parent = clk_pm_cpu_get_parent,
	.round_rate = clk_pm_cpu_round_rate,
	.set_rate = clk_pm_cpu_set_rate,
	.recalc_rate = clk_pm_cpu_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा of_device_id armada_3700_periph_घड़ी_of_match[] = अणु
	अणु .compatible = "marvell,armada-3700-periph-clock-nb",
	  .data = data_nb, पूर्ण,
	अणु .compatible = "marvell,armada-3700-periph-clock-sb",
	.data = data_sb, पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक armada_3700_add_composite_clk(स्थिर काष्ठा clk_periph_data *data,
					 व्योम __iomem *reg, spinlock_t *lock,
					 काष्ठा device *dev, काष्ठा clk_hw **hw)
अणु
	स्थिर काष्ठा clk_ops *mux_ops = शून्य, *gate_ops = शून्य,
		*rate_ops = शून्य;
	काष्ठा clk_hw *mux_hw = शून्य, *gate_hw = शून्य, *rate_hw = शून्य;

	अगर (data->mux_hw) अणु
		काष्ठा clk_mux *mux;

		mux_hw = data->mux_hw;
		mux = to_clk_mux(mux_hw);
		mux->lock = lock;
		mux_ops = mux_hw->init->ops;
		mux->reg = reg + (u64)mux->reg;
	पूर्ण

	अगर (data->gate_hw) अणु
		काष्ठा clk_gate *gate;

		gate_hw = data->gate_hw;
		gate = to_clk_gate(gate_hw);
		gate->lock = lock;
		gate_ops = gate_hw->init->ops;
		gate->reg = reg + (u64)gate->reg;
		gate->flags = CLK_GATE_SET_TO_DISABLE;
	पूर्ण

	अगर (data->rate_hw) अणु
		rate_hw = data->rate_hw;
		rate_ops = rate_hw->init->ops;
		अगर (data->is_द्विगुन_भाग) अणु
			काष्ठा clk_द्विगुन_भाग *rate;

			rate =  to_clk_द्विगुन_भाग(rate_hw);
			rate->reg1 = reg + (u64)rate->reg1;
			rate->reg2 = reg + (u64)rate->reg2;
		पूर्ण अन्यथा अणु
			काष्ठा clk_भागider *rate = to_clk_भागider(rate_hw);
			स्थिर काष्ठा clk_भाग_प्रकारable *clkt;
			पूर्णांक table_size = 0;

			rate->reg = reg + (u64)rate->reg;
			क्रम (clkt = rate->table; clkt->भाग; clkt++)
				table_size++;
			rate->width = order_base_2(table_size);
			rate->lock = lock;
		पूर्ण
	पूर्ण

	अगर (data->muxrate_hw) अणु
		काष्ठा clk_pm_cpu *pmcpu_clk;
		काष्ठा clk_hw *muxrate_hw = data->muxrate_hw;
		काष्ठा regmap *map;

		pmcpu_clk =  to_clk_pm_cpu(muxrate_hw);
		pmcpu_clk->reg_mux = reg + (u64)pmcpu_clk->reg_mux;
		pmcpu_clk->reg_भाग = reg + (u64)pmcpu_clk->reg_भाग;

		mux_hw = muxrate_hw;
		rate_hw = muxrate_hw;
		mux_ops = muxrate_hw->init->ops;
		rate_ops = muxrate_hw->init->ops;

		map = syscon_regmap_lookup_by_compatible(
				"marvell,armada-3700-nb-pm");
		pmcpu_clk->nb_pm_base = map;
	पूर्ण

	*hw = clk_hw_रेजिस्टर_composite(dev, data->name, data->parent_names,
					data->num_parents, mux_hw,
					mux_ops, rate_hw, rate_ops,
					gate_hw, gate_ops, CLK_IGNORE_UNUSED);

	वापस PTR_ERR_OR_ZERO(*hw);
पूर्ण

अटल पूर्णांक __maybe_unused armada_3700_periph_घड़ी_suspend(काष्ठा device *dev)
अणु
	काष्ठा clk_periph_driver_data *data = dev_get_drvdata(dev);

	data->tbg_sel = पढ़ोl(data->reg + TBG_SEL);
	data->भाग_sel0 = पढ़ोl(data->reg + DIV_SEL0);
	data->भाग_sel1 = पढ़ोl(data->reg + DIV_SEL1);
	data->भाग_sel2 = पढ़ोl(data->reg + DIV_SEL2);
	data->clk_sel = पढ़ोl(data->reg + CLK_SEL);
	data->clk_dis = पढ़ोl(data->reg + CLK_DIS);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused armada_3700_periph_घड़ी_resume(काष्ठा device *dev)
अणु
	काष्ठा clk_periph_driver_data *data = dev_get_drvdata(dev);

	/* Follow the same order than what the Cortex-M3 करोes (ATF code) */
	ग_लिखोl(data->clk_dis, data->reg + CLK_DIS);
	ग_लिखोl(data->भाग_sel0, data->reg + DIV_SEL0);
	ग_लिखोl(data->भाग_sel1, data->reg + DIV_SEL1);
	ग_लिखोl(data->भाग_sel2, data->reg + DIV_SEL2);
	ग_लिखोl(data->tbg_sel, data->reg + TBG_SEL);
	ग_लिखोl(data->clk_sel, data->reg + CLK_SEL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops armada_3700_periph_घड़ी_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(armada_3700_periph_घड़ी_suspend,
				      armada_3700_periph_घड़ी_resume)
पूर्ण;

अटल पूर्णांक armada_3700_periph_घड़ी_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_periph_driver_data *driver_data;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा clk_periph_data *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक num_periph = 0, i, ret;
	काष्ठा resource *res;

	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -ENODEV;

	जबतक (data[num_periph].name)
		num_periph++;

	driver_data = devm_kzalloc(dev, माप(*driver_data), GFP_KERNEL);
	अगर (!driver_data)
		वापस -ENOMEM;

	driver_data->hw_data = devm_kzalloc(dev,
					    काष्ठा_size(driver_data->hw_data,
							hws, num_periph),
					    GFP_KERNEL);
	अगर (!driver_data->hw_data)
		वापस -ENOMEM;
	driver_data->hw_data->num = num_periph;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	driver_data->reg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(driver_data->reg))
		वापस PTR_ERR(driver_data->reg);

	spin_lock_init(&driver_data->lock);

	क्रम (i = 0; i < num_periph; i++) अणु
		काष्ठा clk_hw **hw = &driver_data->hw_data->hws[i];
		अगर (armada_3700_add_composite_clk(&data[i], driver_data->reg,
						  &driver_data->lock, dev, hw))
			dev_err(dev, "Can't register periph clock %s\n",
				data[i].name);
	पूर्ण

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get,
				     driver_data->hw_data);
	अगर (ret) अणु
		क्रम (i = 0; i < num_periph; i++)
			clk_hw_unरेजिस्टर(driver_data->hw_data->hws[i]);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, driver_data);
	वापस 0;
पूर्ण

अटल पूर्णांक armada_3700_periph_घड़ी_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_periph_driver_data *data = platक्रमm_get_drvdata(pdev);
	काष्ठा clk_hw_onecell_data *hw_data = data->hw_data;
	पूर्णांक i;

	of_clk_del_provider(pdev->dev.of_node);

	क्रम (i = 0; i < hw_data->num; i++)
		clk_hw_unरेजिस्टर(hw_data->hws[i]);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver armada_3700_periph_घड़ी_driver = अणु
	.probe = armada_3700_periph_घड़ी_probe,
	.हटाओ = armada_3700_periph_घड़ी_हटाओ,
	.driver		= अणु
		.name	= "marvell-armada-3700-periph-clock",
		.of_match_table = armada_3700_periph_घड़ी_of_match,
		.pm	= &armada_3700_periph_घड़ी_pm_ops,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(armada_3700_periph_घड़ी_driver);
