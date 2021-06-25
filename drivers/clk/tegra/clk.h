<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
	/*
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __TEGRA_CLK_H
#घोषणा __TEGRA_CLK_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>

#घोषणा CLK_OUT_ENB_L			0x010
#घोषणा CLK_OUT_ENB_H			0x014
#घोषणा CLK_OUT_ENB_U			0x018
#घोषणा CLK_OUT_ENB_V			0x360
#घोषणा CLK_OUT_ENB_W			0x364
#घोषणा CLK_OUT_ENB_X			0x280
#घोषणा CLK_OUT_ENB_Y			0x298
#घोषणा CLK_ENB_PLLP_OUT_CPU		BIT(31)
#घोषणा CLK_OUT_ENB_SET_L		0x320
#घोषणा CLK_OUT_ENB_CLR_L		0x324
#घोषणा CLK_OUT_ENB_SET_H		0x328
#घोषणा CLK_OUT_ENB_CLR_H		0x32c
#घोषणा CLK_OUT_ENB_SET_U		0x330
#घोषणा CLK_OUT_ENB_CLR_U		0x334
#घोषणा CLK_OUT_ENB_SET_V		0x440
#घोषणा CLK_OUT_ENB_CLR_V		0x444
#घोषणा CLK_OUT_ENB_SET_W		0x448
#घोषणा CLK_OUT_ENB_CLR_W		0x44c
#घोषणा CLK_OUT_ENB_SET_X		0x284
#घोषणा CLK_OUT_ENB_CLR_X		0x288
#घोषणा CLK_OUT_ENB_SET_Y		0x29c
#घोषणा CLK_OUT_ENB_CLR_Y		0x2a0

#घोषणा RST_DEVICES_L			0x004
#घोषणा RST_DEVICES_H			0x008
#घोषणा RST_DEVICES_U			0x00C
#घोषणा RST_DEVICES_V			0x358
#घोषणा RST_DEVICES_W			0x35C
#घोषणा RST_DEVICES_X			0x28C
#घोषणा RST_DEVICES_Y			0x2a4
#घोषणा RST_DEVICES_SET_L		0x300
#घोषणा RST_DEVICES_CLR_L		0x304
#घोषणा RST_DEVICES_SET_H		0x308
#घोषणा RST_DEVICES_CLR_H		0x30c
#घोषणा RST_DEVICES_SET_U		0x310
#घोषणा RST_DEVICES_CLR_U		0x314
#घोषणा RST_DEVICES_SET_V		0x430
#घोषणा RST_DEVICES_CLR_V		0x434
#घोषणा RST_DEVICES_SET_W		0x438
#घोषणा RST_DEVICES_CLR_W		0x43c
#घोषणा RST_DEVICES_SET_X		0x290
#घोषणा RST_DEVICES_CLR_X		0x294
#घोषणा RST_DEVICES_SET_Y		0x2a8
#घोषणा RST_DEVICES_CLR_Y		0x2ac

/*
 * Tegra CLK_OUT_ENB रेजिस्टरs have some undefined bits which are not used and
 * any accidental ग_लिखो of 1 to these bits can cause PSLVERR.
 * So below are the valid mask defines क्रम each CLK_OUT_ENB रेजिस्टर used to
 * turn ON only the valid घड़ीs.
 */
#घोषणा TEGRA210_CLK_ENB_VLD_MSK_L	0xdcd7dff9
#घोषणा TEGRA210_CLK_ENB_VLD_MSK_H	0x87d1f3e7
#घोषणा TEGRA210_CLK_ENB_VLD_MSK_U	0xf3fed3fa
#घोषणा TEGRA210_CLK_ENB_VLD_MSK_V	0xffc18cfb
#घोषणा TEGRA210_CLK_ENB_VLD_MSK_W	0x793fb7ff
#घोषणा TEGRA210_CLK_ENB_VLD_MSK_X	0x3fe66fff
#घोषणा TEGRA210_CLK_ENB_VLD_MSK_Y	0xfc1fc7ff

/**
 * काष्ठा tegra_clk_sync_source - बाह्यal घड़ी source from codec
 *
 * @hw: handle between common and hardware-specअगरic पूर्णांकerfaces
 * @rate: input frequency from source
 * @max_rate: max rate allowed
 */
काष्ठा tegra_clk_sync_source अणु
	काष्ठा		clk_hw hw;
	अचिन्हित दीर्घ	rate;
	अचिन्हित दीर्घ	max_rate;
पूर्ण;

#घोषणा to_clk_sync_source(_hw)					\
	container_of(_hw, काष्ठा tegra_clk_sync_source, hw)

बाह्य स्थिर काष्ठा clk_ops tegra_clk_sync_source_ops;
बाह्य पूर्णांक *periph_clk_enb_refcnt;

काष्ठा clk *tegra_clk_रेजिस्टर_sync_source(स्थिर अक्षर *name,
					   अचिन्हित दीर्घ max_rate);

/**
 * काष्ठा tegra_clk_frac_भाग - fractional भागider घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर containing भागider
 * @flags:	hardware-specअगरic flags
 * @shअगरt:	shअगरt to the भागider bit field
 * @width:	width of the भागider bit field
 * @frac_width:	width of the fractional bit field
 * @lock:	रेजिस्टर lock
 *
 * Flags:
 * TEGRA_DIVIDER_ROUND_UP - This flags indicates to round up the भागider value.
 * TEGRA_DIVIDER_FIXED - Fixed rate PLL भागiders has addition override bit, this
 *      flag indicates that this भागider is क्रम fixed rate PLL.
 * TEGRA_DIVIDER_INT - Some modules can not cope with the duty cycle when
 *      fraction bit is set. This flags indicates to calculate भागider क्रम which
 *      fracton bit will be zero.
 * TEGRA_DIVIDER_UART - UART module भागider has additional enable bit which is
 *      set when भागider value is not 0. This flags indicates that the भागider
 *      is क्रम UART module.
 */
काष्ठा tegra_clk_frac_भाग अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		flags;
	u8		shअगरt;
	u8		width;
	u8		frac_width;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_clk_frac_भाग(_hw) container_of(_hw, काष्ठा tegra_clk_frac_भाग, hw)

#घोषणा TEGRA_DIVIDER_ROUND_UP BIT(0)
#घोषणा TEGRA_DIVIDER_FIXED BIT(1)
#घोषणा TEGRA_DIVIDER_INT BIT(2)
#घोषणा TEGRA_DIVIDER_UART BIT(3)

बाह्य स्थिर काष्ठा clk_ops tegra_clk_frac_भाग_ops;
काष्ठा clk *tegra_clk_रेजिस्टर_भागider(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, व्योम __iomem *reg,
		अचिन्हित दीर्घ flags, u8 clk_भागider_flags, u8 shअगरt, u8 width,
		u8 frac_width, spinlock_t *lock);
काष्ठा clk *tegra_clk_रेजिस्टर_mc(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				  व्योम __iomem *reg, spinlock_t *lock);

/*
 * Tegra PLL:
 *
 * In general, there are 3 requirements क्रम each PLL
 * that SW needs to be comply with.
 * (1) Input frequency range (REF).
 * (2) Comparison frequency range (CF). CF = REF/DIVM.
 * (3) VCO frequency range (VCO).  VCO = CF * DIVN.
 *
 * The final PLL output frequency (FO) = VCO >> DIVP.
 */

/**
 * काष्ठा tegra_clk_pll_freq_table - PLL frequecy table
 *
 * @input_rate:		input rate from source
 * @output_rate:	output rate from PLL क्रम the input rate
 * @n:			feedback भागider
 * @m:			input भागider
 * @p:			post भागider
 * @cpcon:		अक्षरge pump current
 * @sdm_data:		fraction भागider setting (0 = disabled)
 */
काष्ठा tegra_clk_pll_freq_table अणु
	अचिन्हित दीर्घ	input_rate;
	अचिन्हित दीर्घ	output_rate;
	u32		n;
	u32		m;
	u8		p;
	u8		cpcon;
	u16		sdm_data;
पूर्ण;

/**
 * काष्ठा pभाग_map - map post भागider to hw value
 *
 * @pभाग:		post भागider
 * @hw_val:		value to be written to the PLL hw
 */
काष्ठा pभाग_map अणु
	u8 pभाग;
	u8 hw_val;
पूर्ण;

/**
 * काष्ठा भाग_nmp - offset and width of m,n and p fields
 *
 * @भागn_shअगरt:	shअगरt to the feedback भागider bit field
 * @भागn_width:	width of the feedback भागider bit field
 * @भागm_shअगरt:	shअगरt to the input भागider bit field
 * @भागm_width:	width of the input भागider bit field
 * @भागp_shअगरt:	shअगरt to the post भागider bit field
 * @भागp_width:	width of the post भागider bit field
 * @override_भागn_shअगरt: shअगरt to the feedback भागider bitfield in override reg
 * @override_भागm_shअगरt: shअगरt to the input भागider bitfield in override reg
 * @override_भागp_shअगरt: shअगरt to the post भागider bitfield in override reg
 */
काष्ठा भाग_nmp अणु
	u8		भागn_shअगरt;
	u8		भागn_width;
	u8		भागm_shअगरt;
	u8		भागm_width;
	u8		भागp_shअगरt;
	u8		भागp_width;
	u8		override_भागn_shअगरt;
	u8		override_भागm_shअगरt;
	u8		override_भागp_shअगरt;
पूर्ण;

#घोषणा MAX_PLL_MISC_REG_COUNT	6

काष्ठा tegra_clk_pll;

/**
 * काष्ठा tegra_clk_pll_params - PLL parameters
 *
 * @input_min:			Minimum input frequency
 * @input_max:			Maximum input frequency
 * @cf_min:			Minimum comparison frequency
 * @cf_max:			Maximum comparison frequency
 * @vco_min:			Minimum VCO frequency
 * @vco_max:			Maximum VCO frequency
 * @base_reg:			PLL base reg offset
 * @misc_reg:			PLL misc reg offset
 * @lock_reg:			PLL lock reg offset
 * @lock_mask:			Biपंचांगask क्रम PLL lock status
 * @lock_enable_bit_idx:	Bit index to enable PLL lock
 * @iddq_reg:			PLL IDDQ रेजिस्टर offset
 * @iddq_bit_idx:		Bit index to enable PLL IDDQ
 * @reset_reg:			Register offset of where RESET bit is
 * @reset_bit_idx:		Shअगरt of reset bit in reset_reg
 * @sdm_din_reg:		Register offset where SDM settings are
 * @sdm_din_mask:		Mask of SDM भागider bits
 * @sdm_ctrl_reg:		Register offset where SDM enable is
 * @sdm_ctrl_en_mask:		Mask of SDM enable bit
 * @ssc_ctrl_reg:		Register offset where SSC settings are
 * @ssc_ctrl_en_mask:		Mask of SSC enable bit
 * @aux_reg:			AUX रेजिस्टर offset
 * @dyn_ramp_reg:		Dynamic ramp control रेजिस्टर offset
 * @ext_misc_reg:		Miscellaneous control रेजिस्टर offsets
 * @pmc_भागnm_reg:		n, m भागider PMC override रेजिस्टर offset (PLLM)
 * @pmc_भागp_reg:		p भागider PMC override रेजिस्टर offset (PLLM)
 * @flags:			PLL flags
 * @stepa_shअगरt:		Dynamic ramp step A field shअगरt
 * @stepb_shअगरt:		Dynamic ramp step B field shअगरt
 * @lock_delay:			Delay in us अगर PLL lock is not used
 * @max_p:			maximum value क्रम the p भागider
 * @शेषs_set:		Boolean संकेतing all reg शेषs क्रम PLL set.
 * @pभाग_प्रकारohw:			mapping of p भागider to रेजिस्टर values
 * @भाग_nmp:			offsets and widths on n, m and p fields
 * @freq_table:			array of frequencies supported by PLL
 * @fixed_rate:			PLL rate अगर it is fixed
 * @mभाग_शेष:		Default value क्रम fixed mभाग क्रम this PLL
 * @round_p_to_pभाग:		Callback used to round p to the बंदd pभाग
 * @set_gain:			Callback to adjust N भाग क्रम SDM enabled
 *				PLL's based on fractional भागider value.
 * @calc_rate:			Callback used to change how out of table
 *				rates (भागiders and multipler) are calculated.
 * @adjust_vco:			Callback to adjust the programming range of the
 *				भागider range (अगर SDM is present)
 * @set_शेषs:		Callback which will try to initialize PLL
 *				रेजिस्टरs to sane शेष values. This is first
 *				tried during PLL registration, but अगर the PLL
 *				is alपढ़ोy enabled, it will be करोne the first
 *				समय the rate is changed जबतक the PLL is
 *				disabled.
 * @dyn_ramp:			Callback which can be used to define a custom
 *				dynamic ramp function क्रम a given PLL.
 * @pre_rate_change:		Callback which is invoked just beक्रमe changing
 *				PLL's rate.
 * @post_rate_change:		Callback which is invoked right after changing
 *				PLL's rate.
 *
 * Flags:
 * TEGRA_PLL_USE_LOCK - This flag indicated to use lock bits क्रम
 *     PLL locking. If not set it will use lock_delay value to रुको.
 * TEGRA_PLL_HAS_CPCON - This flag indicates that CPCON value needs
 *     to be programmed to change output frequency of the PLL.
 * TEGRA_PLL_SET_LFCON - This flag indicates that LFCON value needs
 *     to be programmed to change output frequency of the PLL.
 * TEGRA_PLL_SET_DCCON - This flag indicates that DCCON value needs
 *     to be programmed to change output frequency of the PLL.
 * TEGRA_PLLU - PLLU has inverted post भागider. This flags indicated
 *     that it is PLLU and invert post भागider value.
 * TEGRA_PLLM - PLLM has additional override settings in PMC. This
 *     flag indicates that it is PLLM and use override settings.
 * TEGRA_PLL_FIXED - We are not supposed to change output frequency
 *     of some plls.
 * TEGRA_PLLE_CONFIGURE - Configure PLLE when enabling.
 * TEGRA_PLL_LOCK_MISC - Lock bit is in the misc रेजिस्टर instead of the
 *     base रेजिस्टर.
 * TEGRA_PLL_BYPASS - PLL has bypass bit
 * TEGRA_PLL_HAS_LOCK_ENABLE - PLL has bit to enable lock monitoring
 * TEGRA_MDIV_NEW - Switch to new method क्रम calculating fixed mभाग
 *     it may be more accurate (especially अगर SDM present)
 * TEGRA_PLLMB - PLLMB has should be treated similar to PLLM. This
 *     flag indicated that it is PLLMB.
 * TEGRA_PLL_VCO_OUT - Used to indicate that the PLL has a VCO output
 */
काष्ठा tegra_clk_pll_params अणु
	अचिन्हित दीर्घ	input_min;
	अचिन्हित दीर्घ	input_max;
	अचिन्हित दीर्घ	cf_min;
	अचिन्हित दीर्घ	cf_max;
	अचिन्हित दीर्घ	vco_min;
	अचिन्हित दीर्घ	vco_max;

	u32		base_reg;
	u32		misc_reg;
	u32		lock_reg;
	u32		lock_mask;
	u32		lock_enable_bit_idx;
	u32		iddq_reg;
	u32		iddq_bit_idx;
	u32		reset_reg;
	u32		reset_bit_idx;
	u32		sdm_din_reg;
	u32		sdm_din_mask;
	u32		sdm_ctrl_reg;
	u32		sdm_ctrl_en_mask;
	u32		ssc_ctrl_reg;
	u32		ssc_ctrl_en_mask;
	u32		aux_reg;
	u32		dyn_ramp_reg;
	u32		ext_misc_reg[MAX_PLL_MISC_REG_COUNT];
	u32		pmc_भागnm_reg;
	u32		pmc_भागp_reg;
	u32		flags;
	पूर्णांक		stepa_shअगरt;
	पूर्णांक		stepb_shअगरt;
	पूर्णांक		lock_delay;
	पूर्णांक		max_p;
	bool		शेषs_set;
	स्थिर काष्ठा pभाग_map *pभाग_प्रकारohw;
	काष्ठा भाग_nmp	*भाग_nmp;
	काष्ठा tegra_clk_pll_freq_table	*freq_table;
	अचिन्हित दीर्घ	fixed_rate;
	u16		mभाग_शेष;
	u32	(*round_p_to_pभाग)(u32 p, u32 *pभाग);
	व्योम	(*set_gain)(काष्ठा tegra_clk_pll_freq_table *cfg);
	पूर्णांक	(*calc_rate)(काष्ठा clk_hw *hw,
			काष्ठा tegra_clk_pll_freq_table *cfg,
			अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate);
	अचिन्हित दीर्घ	(*adjust_vco)(काष्ठा tegra_clk_pll_params *pll_params,
				अचिन्हित दीर्घ parent_rate);
	व्योम	(*set_शेषs)(काष्ठा tegra_clk_pll *pll);
	पूर्णांक	(*dyn_ramp)(काष्ठा tegra_clk_pll *pll,
			काष्ठा tegra_clk_pll_freq_table *cfg);
	पूर्णांक	(*pre_rate_change)(व्योम);
	व्योम	(*post_rate_change)(व्योम);
पूर्ण;

#घोषणा TEGRA_PLL_USE_LOCK BIT(0)
#घोषणा TEGRA_PLL_HAS_CPCON BIT(1)
#घोषणा TEGRA_PLL_SET_LFCON BIT(2)
#घोषणा TEGRA_PLL_SET_DCCON BIT(3)
#घोषणा TEGRA_PLLU BIT(4)
#घोषणा TEGRA_PLLM BIT(5)
#घोषणा TEGRA_PLL_FIXED BIT(6)
#घोषणा TEGRA_PLLE_CONFIGURE BIT(7)
#घोषणा TEGRA_PLL_LOCK_MISC BIT(8)
#घोषणा TEGRA_PLL_BYPASS BIT(9)
#घोषणा TEGRA_PLL_HAS_LOCK_ENABLE BIT(10)
#घोषणा TEGRA_MDIV_NEW BIT(11)
#घोषणा TEGRA_PLLMB BIT(12)
#घोषणा TEGRA_PLL_VCO_OUT BIT(13)

/**
 * काष्ठा tegra_clk_pll - Tegra PLL घड़ी
 *
 * @hw:		handle between common and hardware-specअगरix पूर्णांकerfaces
 * @clk_base:	address of CAR controller
 * @pmc:	address of PMC, required to पढ़ो override bits
 * @lock:	रेजिस्टर lock
 * @params:	PLL parameters
 */
काष्ठा tegra_clk_pll अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*clk_base;
	व्योम __iomem	*pmc;
	spinlock_t	*lock;
	काष्ठा tegra_clk_pll_params	*params;
पूर्ण;

#घोषणा to_clk_pll(_hw) container_of(_hw, काष्ठा tegra_clk_pll, hw)

/**
 * काष्ठा tegra_audio_clk_info - Tegra Audio Clk Inक्रमmation
 *
 * @name:	name क्रम the audio pll
 * @pll_params:	pll_params क्रम audio pll
 * @clk_id:	clk_ids क्रम the audio pll
 * @parent:	name of the parent of the audio pll
 */
काष्ठा tegra_audio_clk_info अणु
	अक्षर *name;
	काष्ठा tegra_clk_pll_params *pll_params;
	पूर्णांक clk_id;
	अक्षर *parent;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops tegra_clk_pll_ops;
बाह्य स्थिर काष्ठा clk_ops tegra_clk_plle_ops;
काष्ठा clk *tegra_clk_रेजिस्टर_pll(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *clk_base, व्योम __iomem *pmc,
		अचिन्हित दीर्घ flags, काष्ठा tegra_clk_pll_params *pll_params,
		spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_plle(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *clk_base, व्योम __iomem *pmc,
		अचिन्हित दीर्घ flags, काष्ठा tegra_clk_pll_params *pll_params,
		spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllxc(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			    व्योम __iomem *clk_base, व्योम __iomem *pmc,
			    अचिन्हित दीर्घ flags,
			    काष्ठा tegra_clk_pll_params *pll_params,
			    spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllm(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			   व्योम __iomem *clk_base, व्योम __iomem *pmc,
			   अचिन्हित दीर्घ flags,
			   काष्ठा tegra_clk_pll_params *pll_params,
			   spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllc(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			   व्योम __iomem *clk_base, व्योम __iomem *pmc,
			   अचिन्हित दीर्घ flags,
			   काष्ठा tegra_clk_pll_params *pll_params,
			   spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllre(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			   व्योम __iomem *clk_base, व्योम __iomem *pmc,
			   अचिन्हित दीर्घ flags,
			   काष्ठा tegra_clk_pll_params *pll_params,
			   spinlock_t *lock, अचिन्हित दीर्घ parent_rate);

काष्ठा clk *tegra_clk_रेजिस्टर_pllre_tegra210(स्थिर अक्षर *name,
			   स्थिर अक्षर *parent_name, व्योम __iomem *clk_base,
			   व्योम __iomem *pmc, अचिन्हित दीर्घ flags,
			   काष्ठा tegra_clk_pll_params *pll_params,
			   spinlock_t *lock, अचिन्हित दीर्घ parent_rate);

काष्ठा clk *tegra_clk_रेजिस्टर_plle_tegra114(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_plle_tegra210(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllc_tegra210(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name, व्योम __iomem *clk_base,
				व्योम __iomem *pmc, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllss_tegra210(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name, व्योम __iomem *clk_base,
				अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllss(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			   व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
			   काष्ठा tegra_clk_pll_params *pll_params,
			   spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllmb(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			   व्योम __iomem *clk_base, व्योम __iomem *pmc,
			   अचिन्हित दीर्घ flags,
			   काष्ठा tegra_clk_pll_params *pll_params,
			   spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllu(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllu_tegra114(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock);

काष्ठा clk *tegra_clk_रेजिस्टर_pllu_tegra210(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				व्योम __iomem *clk_base, अचिन्हित दीर्घ flags,
				काष्ठा tegra_clk_pll_params *pll_params,
				spinlock_t *lock);

/**
 * काष्ठा tegra_clk_pll_out - PLL भागider करोwn घड़ी
 *
 * @hw:			handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:		रेजिस्टर containing the PLL भागider
 * @enb_bit_idx:	bit to enable/disable PLL भागider
 * @rst_bit_idx:	bit to reset PLL भागider
 * @lock:		रेजिस्टर lock
 * @flags:		hardware-specअगरic flags
 */
काष्ठा tegra_clk_pll_out अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	u8		enb_bit_idx;
	u8		rst_bit_idx;
	spinlock_t	*lock;
	u8		flags;
पूर्ण;

#घोषणा to_clk_pll_out(_hw) container_of(_hw, काष्ठा tegra_clk_pll_out, hw)

बाह्य स्थिर काष्ठा clk_ops tegra_clk_pll_out_ops;
काष्ठा clk *tegra_clk_रेजिस्टर_pll_out(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, व्योम __iomem *reg, u8 enb_bit_idx,
		u8 rst_bit_idx, अचिन्हित दीर्घ flags, u8 pll_भाग_flags,
		spinlock_t *lock);

/**
 * काष्ठा tegra_clk_periph_regs -  Registers controlling peripheral घड़ी
 *
 * @enb_reg:		पढ़ो the enable status
 * @enb_set_reg:	ग_लिखो 1 to enable घड़ी
 * @enb_clr_reg:	ग_लिखो 1 to disable घड़ी
 * @rst_reg:		पढ़ो the reset status
 * @rst_set_reg:	ग_लिखो 1 to निश्चित the reset of peripheral
 * @rst_clr_reg:	ग_लिखो 1 to deनिश्चित the reset of peripheral
 */
काष्ठा tegra_clk_periph_regs अणु
	u32 enb_reg;
	u32 enb_set_reg;
	u32 enb_clr_reg;
	u32 rst_reg;
	u32 rst_set_reg;
	u32 rst_clr_reg;
पूर्ण;

/**
 * काष्ठा tegra_clk_periph_gate - peripheral gate घड़ी
 *
 * @magic:		magic number to validate type
 * @hw:			handle between common and hardware-specअगरic पूर्णांकerfaces
 * @clk_base:		address of CAR controller
 * @regs:		Registers to control the peripheral
 * @flags:		hardware-specअगरic flags
 * @clk_num:		Clock number
 * @enable_refcnt:	array to मुख्यtain reference count of the घड़ी
 *
 * Flags:
 * TEGRA_PERIPH_NO_RESET - This flag indicates that reset is not allowed
 *     क्रम this module.
 * TEGRA_PERIPH_MANUAL_RESET - This flag indicates not to reset module
 *     after घड़ी enable and driver क्रम the module is responsible क्रम
 *     करोing reset.
 * TEGRA_PERIPH_ON_APB - If peripheral is in the APB bus then पढ़ो the
 *     bus to flush the ग_लिखो operation in apb bus. This flag indicates
 *     that this peripheral is in apb bus.
 * TEGRA_PERIPH_WAR_1005168 - Apply workaround क्रम Tegra114 MSENC bug
 */
काष्ठा tegra_clk_periph_gate अणु
	u32			magic;
	काष्ठा clk_hw		hw;
	व्योम __iomem		*clk_base;
	u8			flags;
	पूर्णांक			clk_num;
	पूर्णांक			*enable_refcnt;
	स्थिर काष्ठा tegra_clk_periph_regs *regs;
पूर्ण;

#घोषणा to_clk_periph_gate(_hw)					\
	container_of(_hw, काष्ठा tegra_clk_periph_gate, hw)

#घोषणा TEGRA_CLK_PERIPH_GATE_MAGIC 0x17760309

#घोषणा TEGRA_PERIPH_NO_RESET BIT(0)
#घोषणा TEGRA_PERIPH_MANUAL_RESET BIT(1)
#घोषणा TEGRA_PERIPH_ON_APB BIT(2)
#घोषणा TEGRA_PERIPH_WAR_1005168 BIT(3)
#घोषणा TEGRA_PERIPH_NO_DIV BIT(4)
#घोषणा TEGRA_PERIPH_NO_GATE BIT(5)

बाह्य स्थिर काष्ठा clk_ops tegra_clk_periph_gate_ops;
काष्ठा clk *tegra_clk_रेजिस्टर_periph_gate(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, u8 gate_flags, व्योम __iomem *clk_base,
		अचिन्हित दीर्घ flags, पूर्णांक clk_num, पूर्णांक *enable_refcnt);

काष्ठा tegra_clk_periph_fixed अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	स्थिर काष्ठा tegra_clk_periph_regs *regs;
	अचिन्हित पूर्णांक mul;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक num;
पूर्ण;

काष्ठा clk *tegra_clk_रेजिस्टर_periph_fixed(स्थिर अक्षर *name,
					    स्थिर अक्षर *parent,
					    अचिन्हित दीर्घ flags,
					    व्योम __iomem *base,
					    अचिन्हित पूर्णांक mul,
					    अचिन्हित पूर्णांक भाग,
					    अचिन्हित पूर्णांक num);

/**
 * काष्ठा clk-periph - peripheral घड़ी
 *
 * @magic:	magic number to validate type
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @mux:	mux घड़ी
 * @भागider:	भागider घड़ी
 * @gate:	gate घड़ी
 * @mux_ops:	mux घड़ी ops
 * @भाग_ops:	भागider घड़ी ops
 * @gate_ops:	gate घड़ी ops
 */
काष्ठा tegra_clk_periph अणु
	u32			magic;
	काष्ठा clk_hw		hw;
	काष्ठा clk_mux		mux;
	काष्ठा tegra_clk_frac_भाग	भागider;
	काष्ठा tegra_clk_periph_gate	gate;

	स्थिर काष्ठा clk_ops	*mux_ops;
	स्थिर काष्ठा clk_ops	*भाग_ops;
	स्थिर काष्ठा clk_ops	*gate_ops;
पूर्ण;

#घोषणा to_clk_periph(_hw) container_of(_hw, काष्ठा tegra_clk_periph, hw)

#घोषणा TEGRA_CLK_PERIPH_MAGIC 0x18221223

बाह्य स्थिर काष्ठा clk_ops tegra_clk_periph_ops;
काष्ठा clk *tegra_clk_रेजिस्टर_periph(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		काष्ठा tegra_clk_periph *periph, व्योम __iomem *clk_base,
		u32 offset, अचिन्हित दीर्घ flags);
काष्ठा clk *tegra_clk_रेजिस्टर_periph_noभाग(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
		काष्ठा tegra_clk_periph *periph, व्योम __iomem *clk_base,
		u32 offset);

#घोषणा TEGRA_CLK_PERIPH(_mux_shअगरt, _mux_mask, _mux_flags,		\
			 _भाग_shअगरt, _भाग_width, _भाग_frac_width,	\
			 _भाग_flags, _clk_num,\
			 _gate_flags, _table, _lock)			\
	अणु								\
		.mux = अणु						\
			.flags = _mux_flags,				\
			.shअगरt = _mux_shअगरt,				\
			.mask = _mux_mask,				\
			.table = _table,				\
			.lock = _lock,					\
		पूर्ण,							\
		.भागider = अणु						\
			.flags = _भाग_flags,				\
			.shअगरt = _भाग_shअगरt,				\
			.width = _भाग_width,				\
			.frac_width = _भाग_frac_width,			\
			.lock = _lock,					\
		पूर्ण,							\
		.gate = अणु						\
			.flags = _gate_flags,				\
			.clk_num = _clk_num,				\
		पूर्ण,							\
		.mux_ops = &clk_mux_ops,				\
		.भाग_ops = &tegra_clk_frac_भाग_ops,			\
		.gate_ops = &tegra_clk_periph_gate_ops,			\
	पूर्ण

काष्ठा tegra_periph_init_data अणु
	स्थिर अक्षर *name;
	पूर्णांक clk_id;
	जोड़ अणु
		स्थिर अक्षर *स्थिर *parent_names;
		स्थिर अक्षर *parent_name;
	पूर्ण p;
	पूर्णांक num_parents;
	काष्ठा tegra_clk_periph periph;
	u32 offset;
	स्थिर अक्षर *con_id;
	स्थिर अक्षर *dev_id;
	अचिन्हित दीर्घ flags;
पूर्ण;

#घोषणा TEGRA_INIT_DATA_TABLE(_name, _con_id, _dev_id, _parent_names, _offset,\
			_mux_shअगरt, _mux_mask, _mux_flags, _भाग_shअगरt,	\
			_भाग_width, _भाग_frac_width, _भाग_flags,	\
			_clk_num, _gate_flags, _clk_id, _table,		\
			_flags, _lock) \
	अणु								\
		.name = _name,						\
		.clk_id = _clk_id,					\
		.p.parent_names = _parent_names,			\
		.num_parents = ARRAY_SIZE(_parent_names),		\
		.periph = TEGRA_CLK_PERIPH(_mux_shअगरt, _mux_mask,	\
					   _mux_flags, _भाग_shअगरt,	\
					   _भाग_width, _भाग_frac_width,	\
					   _भाग_flags, _clk_num,	\
					   _gate_flags, _table, _lock),	\
		.offset = _offset,					\
		.con_id = _con_id,					\
		.dev_id = _dev_id,					\
		.flags = _flags						\
	पूर्ण

#घोषणा TEGRA_INIT_DATA(_name, _con_id, _dev_id, _parent_names, _offset,\
			_mux_shअगरt, _mux_width, _mux_flags, _भाग_shअगरt,	\
			_भाग_width, _भाग_frac_width, _भाग_flags, \
			_clk_num, _gate_flags, _clk_id)	\
	TEGRA_INIT_DATA_TABLE(_name, _con_id, _dev_id, _parent_names, _offset,\
			_mux_shअगरt, BIT(_mux_width) - 1, _mux_flags,	\
			_भाग_shअगरt, _भाग_width, _भाग_frac_width, _भाग_flags, \
			_clk_num, _gate_flags, _clk_id,\
			शून्य, 0, शून्य)

काष्ठा clk *tegra_clk_रेजिस्टर_periph_data(व्योम __iomem *clk_base,
					   काष्ठा tegra_periph_init_data *init);

/**
 * काष्ठा clk_super_mux - super घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर controlling multiplexer
 * @width:	width of the multiplexer bit field
 * @flags:	hardware-specअगरic flags
 * @भाग2_index:	bit controlling भागide-by-2
 * @pllx_index:	PLLX index in the parent list
 * @lock:	रेजिस्टर lock
 *
 * Flags:
 * TEGRA_DIVIDER_2 - LP cluster has additional भागider. This flag indicates
 *     that this is LP cluster घड़ी.
 * TEGRA210_CPU_CLK - This flag is used to identअगरy CPU cluster क्रम gen5
 *     super mux parent using PLLP branches. To use PLLP branches to CPU, need
 *     to configure additional bit PLLP_OUT_CPU in the घड़ी रेजिस्टरs.
 * TEGRA20_SUPER_CLK - Tegra20 करोesn't have a dedicated भागider क्रम Super
 *     घड़ीs, it only has a घड़ी-skipper.
 */
काष्ठा tegra_clk_super_mux अणु
	काष्ठा clk_hw	hw;
	व्योम __iomem	*reg;
	काष्ठा tegra_clk_frac_भाग frac_भाग;
	स्थिर काष्ठा clk_ops	*भाग_ops;
	u8		width;
	u8		flags;
	u8		भाग2_index;
	u8		pllx_index;
	spinlock_t	*lock;
पूर्ण;

#घोषणा to_clk_super_mux(_hw) container_of(_hw, काष्ठा tegra_clk_super_mux, hw)

#घोषणा TEGRA_DIVIDER_2 BIT(0)
#घोषणा TEGRA210_CPU_CLK BIT(1)
#घोषणा TEGRA20_SUPER_CLK BIT(2)

बाह्य स्थिर काष्ठा clk_ops tegra_clk_super_ops;
काष्ठा clk *tegra_clk_रेजिस्टर_super_mux(स्थिर अक्षर *name,
		स्थिर अक्षर **parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 clk_super_flags,
		u8 width, u8 pllx_index, u8 भाग2_index, spinlock_t *lock);
काष्ठा clk *tegra_clk_रेजिस्टर_super_clk(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 clk_super_flags,
		spinlock_t *lock);
काष्ठा clk *tegra_clk_रेजिस्टर_super_cclk(स्थिर अक्षर *name,
		स्थिर अक्षर * स्थिर *parent_names, u8 num_parents,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 clk_super_flags,
		spinlock_t *lock);
पूर्णांक tegra_cclk_pre_pllx_rate_change(व्योम);
व्योम tegra_cclk_post_pllx_rate_change(व्योम);

/**
 * काष्ठा tegra_sdmmc_mux - चयन भागider with Low Jitter inमाला_दो क्रम SDMMC
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @reg:	रेजिस्टर controlling mux and भागider
 * @flags:	hardware-specअगरic flags
 * @lock:	optional रेजिस्टर lock
 * @gate:	gate घड़ी
 * @gate_ops:	gate घड़ी ops
 */
काष्ठा tegra_sdmmc_mux अणु
	काष्ठा clk_hw		hw;
	व्योम __iomem		*reg;
	spinlock_t		*lock;
	स्थिर काष्ठा clk_ops	*gate_ops;
	काष्ठा tegra_clk_periph_gate	gate;
	u8			भाग_flags;
पूर्ण;

#घोषणा to_clk_sdmmc_mux(_hw) container_of(_hw, काष्ठा tegra_sdmmc_mux, hw)

काष्ठा clk *tegra_clk_रेजिस्टर_sdmmc_mux_भाग(स्थिर अक्षर *name,
		व्योम __iomem *clk_base, u32 offset, u32 clk_num, u8 भाग_flags,
		अचिन्हित दीर्घ flags, व्योम *lock);

/**
 * काष्ठा clk_init_table - घड़ी initialization table
 * @clk_id:	घड़ी id as mentioned in device tree bindings
 * @parent_id:	parent घड़ी id as mentioned in device tree bindings
 * @rate:	rate to set
 * @state:	enable/disable
 */
काष्ठा tegra_clk_init_table अणु
	अचिन्हित पूर्णांक	clk_id;
	अचिन्हित पूर्णांक	parent_id;
	अचिन्हित दीर्घ	rate;
	पूर्णांक		state;
पूर्ण;

/**
 * काष्ठा clk_duplicate - duplicate घड़ीs
 * @clk_id:	घड़ी id as mentioned in device tree bindings
 * @lookup:	duplicate lookup entry क्रम the घड़ी
 */
काष्ठा tegra_clk_duplicate अणु
	पूर्णांक			clk_id;
	काष्ठा clk_lookup	lookup;
पूर्ण;

#घोषणा TEGRA_CLK_DUPLICATE(_clk_id, _dev, _con) \
	अणु					\
		.clk_id = _clk_id,		\
		.lookup = अणु			\
			.dev_id = _dev,		\
			.con_id = _con,		\
		पूर्ण,				\
	पूर्ण

काष्ठा tegra_clk अणु
	पूर्णांक			dt_id;
	bool			present;
पूर्ण;

काष्ठा tegra_devclk अणु
	पूर्णांक		dt_id;
	अक्षर		*dev_id;
	अक्षर		*con_id;
पूर्ण;

व्योम tegra_init_special_resets(अचिन्हित पूर्णांक num, पूर्णांक (*निश्चित)(अचिन्हित दीर्घ),
			       पूर्णांक (*deनिश्चित)(अचिन्हित दीर्घ));

व्योम tegra_init_from_table(काष्ठा tegra_clk_init_table *tbl,
		काष्ठा clk *clks[], पूर्णांक clk_max);

व्योम tegra_init_dup_clks(काष्ठा tegra_clk_duplicate *dup_list,
		काष्ठा clk *clks[], पूर्णांक clk_max);

स्थिर काष्ठा tegra_clk_periph_regs *get_reg_bank(पूर्णांक clkid);
काष्ठा clk **tegra_clk_init(व्योम __iomem *clk_base, पूर्णांक num, पूर्णांक periph_banks);

काष्ठा clk **tegra_lookup_dt_id(पूर्णांक clk_id, काष्ठा tegra_clk *tegra_clk);

व्योम tegra_add_of_provider(काष्ठा device_node *np, व्योम *clk_src_onecell_get);
व्योम tegra_रेजिस्टर_devclks(काष्ठा tegra_devclk *dev_clks, पूर्णांक num);

व्योम tegra_audio_clk_init(व्योम __iomem *clk_base,
			व्योम __iomem *pmc_base, काष्ठा tegra_clk *tegra_clks,
			काष्ठा tegra_audio_clk_info *audio_info,
			अचिन्हित पूर्णांक num_plls, अचिन्हित दीर्घ sync_max_rate);

व्योम tegra_periph_clk_init(व्योम __iomem *clk_base, व्योम __iomem *pmc_base,
			काष्ठा tegra_clk *tegra_clks,
			काष्ठा tegra_clk_pll_params *pll_params);

व्योम tegra_fixed_clk_init(काष्ठा tegra_clk *tegra_clks);
पूर्णांक tegra_osc_clk_init(व्योम __iomem *clk_base, काष्ठा tegra_clk *clks,
		       अचिन्हित दीर्घ *input_freqs, अचिन्हित पूर्णांक num,
		       अचिन्हित पूर्णांक clk_m_भाग, अचिन्हित दीर्घ *osc_freq,
		       अचिन्हित दीर्घ *pll_ref_freq);
व्योम tegra_super_clk_gen4_init(व्योम __iomem *clk_base,
			व्योम __iomem *pmc_base, काष्ठा tegra_clk *tegra_clks,
			काष्ठा tegra_clk_pll_params *pll_params);
व्योम tegra_super_clk_gen5_init(व्योम __iomem *clk_base,
			व्योम __iomem *pmc_base, काष्ठा tegra_clk *tegra_clks,
			काष्ठा tegra_clk_pll_params *pll_params);

#अगर_घोषित CONFIG_TEGRA124_CLK_EMC
काष्ठा clk *tegra124_clk_रेजिस्टर_emc(व्योम __iomem *base, काष्ठा device_node *np,
				      spinlock_t *lock);
bool tegra124_clk_emc_driver_available(काष्ठा clk_hw *emc_hw);
#अन्यथा
अटल अंतरभूत काष्ठा clk *
tegra124_clk_रेजिस्टर_emc(व्योम __iomem *base, काष्ठा device_node *np,
			  spinlock_t *lock)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool tegra124_clk_emc_driver_available(काष्ठा clk_hw *emc_hw)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

व्योम tegra114_घड़ी_प्रकारune_cpu_trimmers_high(व्योम);
व्योम tegra114_घड़ी_प्रकारune_cpu_trimmers_low(व्योम);
व्योम tegra114_घड़ी_प्रकारune_cpu_trimmers_init(व्योम);
व्योम tegra114_घड़ी_निश्चित_dfll_dvco_reset(व्योम);
व्योम tegra114_घड़ी_deनिश्चित_dfll_dvco_reset(व्योम);

प्रकार व्योम (*tegra_clk_apply_init_table_func)(व्योम);
बाह्य tegra_clk_apply_init_table_func tegra_clk_apply_init_table;
पूर्णांक tegra_pll_रुको_क्रम_lock(काष्ठा tegra_clk_pll *pll);
u16 tegra_pll_get_fixed_mभाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ input_rate);
पूर्णांक tegra_pll_p_भाग_प्रकारo_hw(काष्ठा tegra_clk_pll *pll, u8 p_भाग);
पूर्णांक भाग_frac_get(अचिन्हित दीर्घ rate, अचिन्हित parent_rate, u8 width,
		 u8 frac_width, u8 flags);
व्योम tegra_clk_osc_resume(व्योम __iomem *clk_base);
व्योम tegra_clk_set_pllp_out_cpu(bool enable);
व्योम tegra_clk_periph_suspend(व्योम);
व्योम tegra_clk_periph_resume(व्योम);


/* Combined पढ़ो fence with delay */
#घोषणा fence_udelay(delay, reg)	\
	करो अणु				\
		पढ़ोl(reg);		\
		udelay(delay);		\
	पूर्ण जबतक (0)

bool tegra20_clk_emc_driver_available(काष्ठा clk_hw *emc_hw);
काष्ठा clk *tegra20_clk_रेजिस्टर_emc(व्योम __iomem *ioaddr, bool low_jitter);

काष्ठा clk *tegra210_clk_रेजिस्टर_emc(काष्ठा device_node *np,
				      व्योम __iomem *regs);

#पूर्ण_अगर /* TEGRA_CLK_H */
