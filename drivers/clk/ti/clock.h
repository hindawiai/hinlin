<शैली गुरु>
/*
 * TI Clock driver पूर्णांकernal definitions
 *
 * Copyright (C) 2014 Texas Instruments, Inc
 *     Tero Kristo (t-kristo@ti.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __DRIVERS_CLK_TI_CLOCK__
#घोषणा __DRIVERS_CLK_TI_CLOCK__

काष्ठा clk_omap_भागider अणु
	काष्ठा clk_hw		hw;
	काष्ठा clk_omap_reg	reg;
	u8			shअगरt;
	u8			flags;
	s8			latch;
	u16			min;
	u16			max;
	u16			mask;
	स्थिर काष्ठा clk_भाग_प्रकारable	*table;
	u32		context;
पूर्ण;

#घोषणा to_clk_omap_भागider(_hw) container_of(_hw, काष्ठा clk_omap_भागider, hw)

काष्ठा clk_omap_mux अणु
	काष्ठा clk_hw		hw;
	काष्ठा clk_omap_reg	reg;
	u32			*table;
	u32			mask;
	u8			shअगरt;
	s8			latch;
	u8			flags;
	u8			saved_parent;
पूर्ण;

#घोषणा to_clk_omap_mux(_hw) container_of(_hw, काष्ठा clk_omap_mux, hw)

क्रमागत अणु
	TI_CLK_FIXED,
	TI_CLK_MUX,
	TI_CLK_DIVIDER,
	TI_CLK_COMPOSITE,
	TI_CLK_FIXED_FACTOR,
	TI_CLK_GATE,
	TI_CLK_DPLL,
पूर्ण;

/* Global flags */
#घोषणा CLKF_INDEX_POWER_OF_TWO		(1 << 0)
#घोषणा CLKF_INDEX_STARTS_AT_ONE	(1 << 1)
#घोषणा CLKF_SET_RATE_PARENT		(1 << 2)
#घोषणा CLKF_OMAP3			(1 << 3)
#घोषणा CLKF_AM35XX			(1 << 4)

/* Gate flags */
#घोषणा CLKF_SET_BIT_TO_DISABLE		(1 << 5)
#घोषणा CLKF_INTERFACE			(1 << 6)
#घोषणा CLKF_SSI			(1 << 7)
#घोषणा CLKF_DSS			(1 << 8)
#घोषणा CLKF_HSOTGUSB			(1 << 9)
#घोषणा CLKF_WAIT			(1 << 10)
#घोषणा CLKF_NO_WAIT			(1 << 11)
#घोषणा CLKF_HSDIV			(1 << 12)
#घोषणा CLKF_CLKDM			(1 << 13)

/* DPLL flags */
#घोषणा CLKF_LOW_POWER_STOP		(1 << 5)
#घोषणा CLKF_LOCK			(1 << 6)
#घोषणा CLKF_LOW_POWER_BYPASS		(1 << 7)
#घोषणा CLKF_PER			(1 << 8)
#घोषणा CLKF_CORE			(1 << 9)
#घोषणा CLKF_J_TYPE			(1 << 10)

/* CLKCTRL flags */
#घोषणा CLKF_SW_SUP			BIT(5)
#घोषणा CLKF_HW_SUP			BIT(6)
#घोषणा CLKF_NO_IDLEST			BIT(7)

#घोषणा CLKF_SOC_MASK			GENMASK(11, 8)

#घोषणा CLKF_SOC_NONSEC			BIT(8)
#घोषणा CLKF_SOC_DRA72			BIT(9)
#घोषणा CLKF_SOC_DRA74			BIT(10)
#घोषणा CLKF_SOC_DRA76			BIT(11)

#घोषणा CLK(dev, con, ck)		\
	अणु				\
		.lk = अणु			\
			.dev_id = dev,	\
			.con_id = con,	\
		पूर्ण,			\
		.clk = ck,		\
	पूर्ण

काष्ठा ti_clk अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *clkdm_name;
	पूर्णांक type;
	व्योम *data;
	काष्ठा ti_clk *patch;
	काष्ठा clk *clk;
पूर्ण;

काष्ठा ti_clk_mux अणु
	u8 bit_shअगरt;
	पूर्णांक num_parents;
	u16 reg;
	u8 module;
	स्थिर अक्षर * स्थिर *parents;
	u16 flags;
पूर्ण;

काष्ठा ti_clk_भागider अणु
	स्थिर अक्षर *parent;
	u8 bit_shअगरt;
	u16 max_भाग;
	u16 reg;
	u8 module;
	पूर्णांक *भागiders;
	पूर्णांक num_भागiders;
	u16 flags;
पूर्ण;

काष्ठा ti_clk_gate अणु
	स्थिर अक्षर *parent;
	u8 bit_shअगरt;
	u16 reg;
	u8 module;
	u16 flags;
पूर्ण;

/* Composite घड़ी component types */
क्रमागत अणु
	CLK_COMPONENT_TYPE_GATE = 0,
	CLK_COMPONENT_TYPE_DIVIDER,
	CLK_COMPONENT_TYPE_MUX,
	CLK_COMPONENT_TYPE_MAX,
पूर्ण;

/**
 * काष्ठा ti_dt_clk - OMAP DT घड़ी alias declarations
 * @lk: घड़ी lookup definition
 * @node_name: घड़ी DT node to map to
 */
काष्ठा ti_dt_clk अणु
	काष्ठा clk_lookup		lk;
	अक्षर				*node_name;
पूर्ण;

#घोषणा DT_CLK(dev, con, name)		\
	अणु				\
		.lk = अणु			\
			.dev_id = dev,	\
			.con_id = con,	\
		पूर्ण,			\
		.node_name = name,	\
	पूर्ण

/* CLKCTRL type definitions */
काष्ठा omap_clkctrl_भाग_data अणु
	स्थिर पूर्णांक *भागiders;
	पूर्णांक max_भाग;
	u32 flags;
पूर्ण;

काष्ठा omap_clkctrl_bit_data अणु
	u8 bit;
	u8 type;
	स्थिर अक्षर * स्थिर *parents;
	स्थिर व्योम *data;
पूर्ण;

काष्ठा omap_clkctrl_reg_data अणु
	u16 offset;
	स्थिर काष्ठा omap_clkctrl_bit_data *bit_data;
	u16 flags;
	स्थिर अक्षर *parent;
	स्थिर अक्षर *clkdm_name;
पूर्ण;

काष्ठा omap_clkctrl_data अणु
	u32 addr;
	स्थिर काष्ठा omap_clkctrl_reg_data *regs;
पूर्ण;

बाह्य स्थिर काष्ठा omap_clkctrl_data omap4_clkctrl_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data omap5_clkctrl_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data dra7_clkctrl_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data dra7_clkctrl_compat_data[];
बाह्य काष्ठा ti_dt_clk dra7xx_compat_clks[];
बाह्य स्थिर काष्ठा omap_clkctrl_data am3_clkctrl_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data am3_clkctrl_compat_data[];
बाह्य काष्ठा ti_dt_clk am33xx_compat_clks[];
बाह्य स्थिर काष्ठा omap_clkctrl_data am4_clkctrl_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data am4_clkctrl_compat_data[];
बाह्य काष्ठा ti_dt_clk am43xx_compat_clks[];
बाह्य स्थिर काष्ठा omap_clkctrl_data am438x_clkctrl_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data am438x_clkctrl_compat_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data dm814_clkctrl_data[];
बाह्य स्थिर काष्ठा omap_clkctrl_data dm816_clkctrl_data[];

प्रकार व्योम (*ti_of_clk_init_cb_t)(व्योम *, काष्ठा device_node *);

काष्ठा clk *ti_clk_रेजिस्टर(काष्ठा device *dev, काष्ठा clk_hw *hw,
			    स्थिर अक्षर *con);
काष्ठा clk *ti_clk_रेजिस्टर_omap_hw(काष्ठा device *dev, काष्ठा clk_hw *hw,
				    स्थिर अक्षर *con);
पूर्णांक ti_clk_add_alias(काष्ठा device *dev, काष्ठा clk *clk, स्थिर अक्षर *con);
व्योम ti_clk_add_aliases(व्योम);

व्योम ti_clk_latch(काष्ठा clk_omap_reg *reg, s8 shअगरt);

काष्ठा clk_hw *ti_clk_build_component_mux(काष्ठा ti_clk_mux *setup);

पूर्णांक ti_clk_parse_भागider_data(पूर्णांक *भाग_प्रकारable, पूर्णांक num_भागiders, पूर्णांक max_भाग,
			      u8 flags, काष्ठा clk_omap_भागider *भाग);

पूर्णांक ti_clk_get_reg_addr(काष्ठा device_node *node, पूर्णांक index,
			काष्ठा clk_omap_reg *reg);
व्योम ti_dt_घड़ीs_रेजिस्टर(काष्ठा ti_dt_clk *oclks);
पूर्णांक ti_clk_retry_init(काष्ठा device_node *node, व्योम *user,
		      ti_of_clk_init_cb_t func);
पूर्णांक ti_clk_add_component(काष्ठा device_node *node, काष्ठा clk_hw *hw, पूर्णांक type);

पूर्णांक of_ti_clk_स्वतःidle_setup(काष्ठा device_node *node);
व्योम omap2_clk_enable_init_घड़ीs(स्थिर अक्षर **clk_names, u8 num_घड़ीs);

बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3_dpll;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap4_dpllmx;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_iclk;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_iclk_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap2430_i2chs_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_dss_usbhost_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_iclk_hsotgusb_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_iclk_dss_usbhost_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_iclk_ssi_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_am35xx_ipss_module_रुको;
बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_am35xx_ipss_रुको;

बाह्य स्थिर काष्ठा clk_ops ti_clk_भागider_ops;
बाह्य स्थिर काष्ठा clk_ops ti_clk_mux_ops;
बाह्य स्थिर काष्ठा clk_ops omap_gate_clk_ops;

बाह्य काष्ठा ti_clk_features ti_clk_features;

पूर्णांक omap2_init_clk_clkdm(काष्ठा clk_hw *hw);
पूर्णांक omap2_clkops_enable_clkdm(काष्ठा clk_hw *hw);
व्योम omap2_clkops_disable_clkdm(काष्ठा clk_hw *hw);

पूर्णांक omap2_dflt_clk_enable(काष्ठा clk_hw *hw);
व्योम omap2_dflt_clk_disable(काष्ठा clk_hw *hw);
पूर्णांक omap2_dflt_clk_is_enabled(काष्ठा clk_hw *hw);
व्योम omap2_clk_dflt_find_companion(काष्ठा clk_hw_omap *clk,
				   काष्ठा clk_omap_reg *other_reg,
				   u8 *other_bit);
व्योम omap2_clk_dflt_find_idlest(काष्ठा clk_hw_omap *clk,
				काष्ठा clk_omap_reg *idlest_reg,
				u8 *idlest_bit, u8 *idlest_val);

व्योम omap2_clkt_iclk_allow_idle(काष्ठा clk_hw_omap *clk);
व्योम omap2_clkt_iclk_deny_idle(काष्ठा clk_hw_omap *clk);

u8 omap2_init_dpll_parent(काष्ठा clk_hw *hw);
पूर्णांक omap3_noncore_dpll_enable(काष्ठा clk_hw *hw);
व्योम omap3_noncore_dpll_disable(काष्ठा clk_hw *hw);
पूर्णांक omap3_noncore_dpll_set_parent(काष्ठा clk_hw *hw, u8 index);
पूर्णांक omap3_noncore_dpll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate);
पूर्णांक omap3_noncore_dpll_set_rate_and_parent(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ rate,
					   अचिन्हित दीर्घ parent_rate,
					   u8 index);
पूर्णांक omap3_noncore_dpll_determine_rate(काष्ठा clk_hw *hw,
				      काष्ठा clk_rate_request *req);
दीर्घ omap2_dpll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ target_rate,
			   अचिन्हित दीर्घ *parent_rate);
अचिन्हित दीर्घ omap3_clkoutx2_recalc(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ parent_rate);

/*
 * OMAP3_DPLL5_FREQ_FOR_USBHOST: USBHOST and USBTLL are the only घड़ीs
 * that are sourced by DPLL5, and both of these require this घड़ी
 * to be at 120 MHz क्रम proper operation.
 */
#घोषणा OMAP3_DPLL5_FREQ_FOR_USBHOST	120000000

अचिन्हित दीर्घ omap3_dpll_recalc(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate);
पूर्णांक omap3_dpll4_set_rate(काष्ठा clk_hw *clk, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate);
पूर्णांक omap3_dpll4_set_rate_and_parent(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ parent_rate, u8 index);
पूर्णांक omap3_dpll5_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ parent_rate);
व्योम omap3_clk_lock_dpll5(व्योम);

अचिन्हित दीर्घ omap4_dpll_regm4xen_recalc(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate);
दीर्घ omap4_dpll_regm4xen_round_rate(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ target_rate,
				    अचिन्हित दीर्घ *parent_rate);
पूर्णांक omap4_dpll_regm4xen_determine_rate(काष्ठा clk_hw *hw,
				       काष्ठा clk_rate_request *req);
पूर्णांक omap2_clk_क्रम_each(पूर्णांक (*fn)(काष्ठा clk_hw_omap *hw));

बाह्य काष्ठा ti_clk_ll_ops *ti_clk_ll_ops;

#पूर्ण_अगर
