<शैली गुरु>
/*
 * TI घड़ी drivers support
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __LINUX_CLK_TI_H__
#घोषणा __LINUX_CLK_TI_H__

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>

/**
 * काष्ठा clk_omap_reg - OMAP रेजिस्टर declaration
 * @offset: offset from the master IP module base address
 * @index: index of the master IP module
 */
काष्ठा clk_omap_reg अणु
	व्योम __iomem *ptr;
	u16 offset;
	u8 index;
	u8 flags;
पूर्ण;

/**
 * काष्ठा dpll_data - DPLL रेजिस्टरs and पूर्णांकegration data
 * @mult_भाग1_reg: रेजिस्टर containing the DPLL M and N bitfields
 * @mult_mask: mask of the DPLL M bitfield in @mult_भाग1_reg
 * @भाग1_mask: mask of the DPLL N bitfield in @mult_भाग1_reg
 * @clk_bypass: काष्ठा clk_hw poपूर्णांकer to the घड़ी's bypass घड़ी input
 * @clk_ref: काष्ठा clk_hw poपूर्णांकer to the घड़ी's reference घड़ी input
 * @control_reg: रेजिस्टर containing the DPLL mode bitfield
 * @enable_mask: mask of the DPLL mode bitfield in @control_reg
 * @last_rounded_rate: cache of the last rate result of omap2_dpll_round_rate()
 * @last_rounded_m: cache of the last M result of omap2_dpll_round_rate()
 * @last_rounded_m4xen: cache of the last M4X result of
 *			omap4_dpll_regm4xen_round_rate()
 * @last_rounded_lpmode: cache of the last lpmode result of
 *			 omap4_dpll_lpmode_recalc()
 * @max_multiplier: maximum valid non-bypass multiplier value (actual)
 * @last_rounded_n: cache of the last N result of omap2_dpll_round_rate()
 * @min_भागider: minimum valid non-bypass भागider value (actual)
 * @max_भागider: maximum valid non-bypass भागider value (actual)
 * @max_rate: maximum घड़ी rate क्रम the DPLL
 * @modes: possible values of @enable_mask
 * @स्वतःidle_reg: रेजिस्टर containing the DPLL स्वतःidle mode bitfield
 * @idlest_reg: रेजिस्टर containing the DPLL idle status bitfield
 * @स्वतःidle_mask: mask of the DPLL स्वतःidle mode bitfield in @स्वतःidle_reg
 * @freqsel_mask: mask of the DPLL jitter correction bitfield in @control_reg
 * @dcc_mask: mask of the DPLL DCC correction bitfield @mult_भाग1_reg
 * @dcc_rate: rate atleast which DCC @dcc_mask must be set
 * @idlest_mask: mask of the DPLL idle status bitfield in @idlest_reg
 * @lpmode_mask: mask of the DPLL low-घातer mode bitfield in @control_reg
 * @m4xen_mask: mask of the DPLL M4X multiplier bitfield in @control_reg
 * @स्वतः_recal_bit: bitshअगरt of the drअगरtguard enable bit in @control_reg
 * @recal_en_bit: bitshअगरt of the PRM_IRQENABLE_* bit क्रम recalibration IRQs
 * @recal_st_bit: bitshअगरt of the PRM_IRQSTATUS_* bit क्रम recalibration IRQs
 * @flags: DPLL type/features (see below)
 *
 * Possible values क्रम @flags:
 * DPLL_J_TYPE: "J-type DPLL" (only some 36xx, 4xxx DPLLs)
 *
 * @freqsel_mask is only used on the OMAP34xx family and AM35xx.
 *
 * XXX Some DPLLs have multiple bypass inमाला_दो, so it's not technically
 * correct to only have one @clk_bypass poपूर्णांकer.
 *
 * XXX The runसमय-variable fields (@last_rounded_rate, @last_rounded_m,
 * @last_rounded_n) should be separated from the runसमय-fixed fields
 * and placed पूर्णांकo a dअगरferent काष्ठाure, so that the runसमय-fixed data
 * can be placed पूर्णांकo पढ़ो-only space.
 */
काष्ठा dpll_data अणु
	काष्ठा clk_omap_reg	mult_भाग1_reg;
	u32			mult_mask;
	u32			भाग1_mask;
	काष्ठा clk_hw		*clk_bypass;
	काष्ठा clk_hw		*clk_ref;
	काष्ठा clk_omap_reg	control_reg;
	u32			enable_mask;
	अचिन्हित दीर्घ		last_rounded_rate;
	u16			last_rounded_m;
	u8			last_rounded_m4xen;
	u8			last_rounded_lpmode;
	u16			max_multiplier;
	u8			last_rounded_n;
	u8			min_भागider;
	u16			max_भागider;
	अचिन्हित दीर्घ		max_rate;
	u8			modes;
	काष्ठा clk_omap_reg	स्वतःidle_reg;
	काष्ठा clk_omap_reg	idlest_reg;
	u32			स्वतःidle_mask;
	u32			freqsel_mask;
	u32			idlest_mask;
	u32			dco_mask;
	u32			sdभाग_mask;
	u32			dcc_mask;
	अचिन्हित दीर्घ		dcc_rate;
	u32			lpmode_mask;
	u32			m4xen_mask;
	u8			स्वतः_recal_bit;
	u8			recal_en_bit;
	u8			recal_st_bit;
	u8			flags;
पूर्ण;

काष्ठा clk_hw_omap;

/**
 * काष्ठा clk_hw_omap_ops - OMAP clk ops
 * @find_idlest: find idlest रेजिस्टर inक्रमmation क्रम a घड़ी
 * @find_companion: find companion घड़ी रेजिस्टर inक्रमmation क्रम a घड़ी,
 *		    basically converts CM_ICLKEN* <-> CM_FCLKEN*
 * @allow_idle: enables स्वतःidle hardware functionality क्रम a घड़ी
 * @deny_idle: prevent स्वतःidle hardware functionality क्रम a घड़ी
 */
काष्ठा clk_hw_omap_ops अणु
	व्योम	(*find_idlest)(काष्ठा clk_hw_omap *oclk,
			       काष्ठा clk_omap_reg *idlest_reg,
			       u8 *idlest_bit, u8 *idlest_val);
	व्योम	(*find_companion)(काष्ठा clk_hw_omap *oclk,
				  काष्ठा clk_omap_reg *other_reg,
				  u8 *other_bit);
	व्योम	(*allow_idle)(काष्ठा clk_hw_omap *oclk);
	व्योम	(*deny_idle)(काष्ठा clk_hw_omap *oclk);
पूर्ण;

/**
 * काष्ठा clk_hw_omap - OMAP काष्ठा clk
 * @node: list_head connecting this घड़ी पूर्णांकo the full घड़ी list
 * @enable_reg: रेजिस्टर to ग_लिखो to enable the घड़ी (see @enable_bit)
 * @enable_bit: bitshअगरt to ग_लिखो to enable/disable the घड़ी (see @enable_reg)
 * @flags: see "struct clk.flags possibilities" above
 * @clksel_reg: क्रम clksel clks, रेजिस्टर va containing src/भागisor select
 * @dpll_data: क्रम DPLLs, poपूर्णांकer to काष्ठा dpll_data क्रम this घड़ी
 * @clkdm_name: घड़ीकरोमुख्य name that this घड़ी is contained in
 * @clkdm: poपूर्णांकer to काष्ठा घड़ीकरोमुख्य, resolved from @clkdm_name at runसमय
 * @ops: घड़ी ops क्रम this घड़ी
 */
काष्ठा clk_hw_omap अणु
	काष्ठा clk_hw		hw;
	काष्ठा list_head	node;
	अचिन्हित दीर्घ		fixed_rate;
	u8			fixed_भाग;
	काष्ठा clk_omap_reg	enable_reg;
	u8			enable_bit;
	अचिन्हित दीर्घ		flags;
	काष्ठा clk_omap_reg	clksel_reg;
	काष्ठा dpll_data	*dpll_data;
	स्थिर अक्षर		*clkdm_name;
	काष्ठा घड़ीकरोमुख्य	*clkdm;
	स्थिर काष्ठा clk_hw_omap_ops	*ops;
	u32			context;
	पूर्णांक			स्वतःidle_count;
पूर्ण;

/*
 * काष्ठा clk_hw_omap.flags possibilities
 *
 * XXX करोcument the rest of the घड़ी flags here
 *
 * ENABLE_REG_32BIT: (OMAP1 only) घड़ी control रेजिस्टर must be accessed
 *     with 32bit ops, by शेष OMAP1 uses 16bit ops.
 * CLOCK_IDLE_CONTROL: (OMAP1 only) घड़ी has स्वतःidle support.
 * CLOCK_NO_IDLE_PARENT: (OMAP1 only) when घड़ी is enabled, its parent
 *     घड़ी is put to no-idle mode.
 * ENABLE_ON_INIT: Clock is enabled on init.
 * INVERT_ENABLE: By शेष, घड़ी enable bit behavior is '1' enable, '0'
 *     disable. This inverts the behavior making '0' enable and '1' disable.
 * CLOCK_CLKOUTX2: (OMAP4 only) DPLL CLKOUT and CLKOUTX2 GATE_CTRL
 *     bits share the same रेजिस्टर.  This flag allows the
 *     omap4_dpllmx*() code to determine which GATE_CTRL bit field
 *     should be used.  This is a temporary solution - a better approach
 *     would be to associate घड़ी type-specअगरic data with the घड़ी,
 *     similar to the काष्ठा dpll_data approach.
 */
#घोषणा ENABLE_REG_32BIT	(1 << 0)	/* Use 32-bit access */
#घोषणा CLOCK_IDLE_CONTROL	(1 << 1)
#घोषणा CLOCK_NO_IDLE_PARENT	(1 << 2)
#घोषणा ENABLE_ON_INIT		(1 << 3)	/* Enable upon framework init */
#घोषणा INVERT_ENABLE		(1 << 4)	/* 0 enables, 1 disables */
#घोषणा CLOCK_CLKOUTX2		(1 << 5)

/* CM_CLKEN_PLL*.EN* bit values - not all are available क्रम every DPLL */
#घोषणा DPLL_LOW_POWER_STOP	0x1
#घोषणा DPLL_LOW_POWER_BYPASS	0x5
#घोषणा DPLL_LOCKED		0x7

/* DPLL Type and DCO Selection Flags */
#घोषणा DPLL_J_TYPE		0x1

/* Static memmap indices */
क्रमागत अणु
	TI_CLKM_CM = 0,
	TI_CLKM_CM2,
	TI_CLKM_PRM,
	TI_CLKM_SCRM,
	TI_CLKM_CTRL,
	TI_CLKM_CTRL_AUX,
	TI_CLKM_PLLSS,
	CLK_MAX_MEMMAPS
पूर्ण;

/**
 * काष्ठा ti_clk_ll_ops - low-level ops क्रम घड़ीs
 * @clk_पढ़ोl: poपूर्णांकer to रेजिस्टर पढ़ो function
 * @clk_ग_लिखोl: poपूर्णांकer to रेजिस्टर ग_लिखो function
 * @clk_rmw: poपूर्णांकer to रेजिस्टर पढ़ो-modअगरy-ग_लिखो function
 * @clkdm_clk_enable: poपूर्णांकer to घड़ीकरोमुख्य enable function
 * @clkdm_clk_disable: poपूर्णांकer to घड़ीकरोमुख्य disable function
 * @clkdm_lookup: poपूर्णांकer to घड़ीकरोमुख्य lookup function
 * @cm_रुको_module_पढ़ोy: poपूर्णांकer to CM module रुको पढ़ोy function
 * @cm_split_idlest_reg: poपूर्णांकer to CM module function to split idlest reg
 *
 * Low-level ops are generally used by the basic घड़ी types (clk-gate,
 * clk-mux, clk-भागider etc.) to provide support क्रम various low-level
 * hadrware पूर्णांकerfaces (direct MMIO, regmap etc.), and is initialized
 * by board code. Low-level ops also contain some other platक्रमm specअगरic
 * operations not provided directly by घड़ी drivers.
 */
काष्ठा ti_clk_ll_ops अणु
	u32	(*clk_पढ़ोl)(स्थिर काष्ठा clk_omap_reg *reg);
	व्योम	(*clk_ग_लिखोl)(u32 val, स्थिर काष्ठा clk_omap_reg *reg);
	व्योम	(*clk_rmw)(u32 val, u32 mask, स्थिर काष्ठा clk_omap_reg *reg);
	पूर्णांक	(*clkdm_clk_enable)(काष्ठा घड़ीकरोमुख्य *clkdm, काष्ठा clk *clk);
	पूर्णांक	(*clkdm_clk_disable)(काष्ठा घड़ीकरोमुख्य *clkdm,
				     काष्ठा clk *clk);
	काष्ठा घड़ीकरोमुख्य * (*clkdm_lookup)(स्थिर अक्षर *name);
	पूर्णांक	(*cm_रुको_module_पढ़ोy)(u8 part, s16 prcm_mod, u16 idlest_reg,
					u8 idlest_shअगरt);
	पूर्णांक	(*cm_split_idlest_reg)(काष्ठा clk_omap_reg *idlest_reg,
				       s16 *prcm_inst, u8 *idlest_reg_id);
पूर्ण;

#घोषणा to_clk_hw_omap(_hw) container_of(_hw, काष्ठा clk_hw_omap, hw)

bool omap2_clk_is_hw_omap(काष्ठा clk_hw *hw);
पूर्णांक omap2_clk_disable_स्वतःidle_all(व्योम);
पूर्णांक omap2_clk_enable_स्वतःidle_all(व्योम);
पूर्णांक omap2_clk_allow_idle(काष्ठा clk *clk);
पूर्णांक omap2_clk_deny_idle(काष्ठा clk *clk);
अचिन्हित दीर्घ omap2_dpllcore_recalc(काष्ठा clk_hw *hw,
				    अचिन्हित दीर्घ parent_rate);
पूर्णांक omap2_reprogram_dpllcore(काष्ठा clk_hw *clk, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate);
व्योम omap2xxx_clkt_dpllcore_init(काष्ठा clk_hw *hw);
व्योम omap2xxx_clkt_vps_init(व्योम);
अचिन्हित दीर्घ omap2_get_dpll_rate(काष्ठा clk_hw_omap *clk);

व्योम ti_dt_clk_init_retry_clks(व्योम);
व्योम ti_dt_घड़ीकरोमुख्यs_setup(व्योम);
पूर्णांक ti_clk_setup_ll_ops(काष्ठा ti_clk_ll_ops *ops);

काष्ठा regmap;

पूर्णांक omap2_clk_provider_init(काष्ठा device_node *parent, पूर्णांक index,
			    काष्ठा regmap *syscon, व्योम __iomem *mem);
व्योम omap2_clk_legacy_provider_init(पूर्णांक index, व्योम __iomem *mem);

पूर्णांक omap3430_dt_clk_init(व्योम);
पूर्णांक omap3630_dt_clk_init(व्योम);
पूर्णांक am35xx_dt_clk_init(व्योम);
पूर्णांक dm814x_dt_clk_init(व्योम);
पूर्णांक dm816x_dt_clk_init(व्योम);
पूर्णांक omap4xxx_dt_clk_init(व्योम);
पूर्णांक omap5xxx_dt_clk_init(व्योम);
पूर्णांक dra7xx_dt_clk_init(व्योम);
पूर्णांक am33xx_dt_clk_init(व्योम);
पूर्णांक am43xx_dt_clk_init(व्योम);
पूर्णांक omap2420_dt_clk_init(व्योम);
पूर्णांक omap2430_dt_clk_init(व्योम);

काष्ठा ti_clk_features अणु
	u32 flags;
	दीर्घ fपूर्णांक_min;
	दीर्घ fपूर्णांक_max;
	दीर्घ fपूर्णांक_band1_max;
	दीर्घ fपूर्णांक_band2_min;
	u8 dpll_bypass_vals;
	u8 cm_idlest_val;
पूर्ण;

#घोषणा TI_CLK_DPLL_HAS_FREQSEL			BIT(0)
#घोषणा TI_CLK_DPLL4_DENY_REPROGRAM		BIT(1)
#घोषणा TI_CLK_DISABLE_CLKDM_CONTROL		BIT(2)
#घोषणा TI_CLK_ERRATA_I810			BIT(3)
#घोषणा TI_CLK_CLKCTRL_COMPAT			BIT(4)
#घोषणा TI_CLK_DEVICE_TYPE_GP			BIT(5)

व्योम ti_clk_setup_features(काष्ठा ti_clk_features *features);
स्थिर काष्ठा ti_clk_features *ti_clk_get_features(व्योम);
bool ti_clk_is_in_standby(काष्ठा clk *clk);
पूर्णांक omap3_noncore_dpll_save_context(काष्ठा clk_hw *hw);
व्योम omap3_noncore_dpll_restore_context(काष्ठा clk_hw *hw);

पूर्णांक omap3_core_dpll_save_context(काष्ठा clk_hw *hw);
व्योम omap3_core_dpll_restore_context(काष्ठा clk_hw *hw);

बाह्य स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap2xxx_dpll;

#अगर_घोषित CONFIG_ATAGS
पूर्णांक omap3430_clk_legacy_init(व्योम);
पूर्णांक omap3430es1_clk_legacy_init(व्योम);
पूर्णांक omap36xx_clk_legacy_init(व्योम);
पूर्णांक am35xx_clk_legacy_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक omap3430_clk_legacy_init(व्योम) अणु वापस -ENXIO; पूर्ण
अटल अंतरभूत पूर्णांक omap3430es1_clk_legacy_init(व्योम) अणु वापस -ENXIO; पूर्ण
अटल अंतरभूत पूर्णांक omap36xx_clk_legacy_init(व्योम) अणु वापस -ENXIO; पूर्ण
अटल अंतरभूत पूर्णांक am35xx_clk_legacy_init(व्योम) अणु वापस -ENXIO; पूर्ण
#पूर्ण_अगर


#पूर्ण_अगर
