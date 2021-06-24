<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम IDT Versaघड़ी 5
 *
 * Copyright (C) 2017 Marek Vasut <marek.vasut@gmail.com>
 */

/*
 * Possible optimizations:
 * - Use spपढ़ो spectrum
 * - Use पूर्णांकeger भागider in FOD अगर applicable
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/rational.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/clk/versaघड़ी.h>

/* VersaClock5 रेजिस्टरs */
#घोषणा VC5_OTP_CONTROL				0x00

/* Factory-reserved रेजिस्टर block */
#घोषणा VC5_RSVD_DEVICE_ID			0x01
#घोषणा VC5_RSVD_ADC_GAIN_7_0			0x02
#घोषणा VC5_RSVD_ADC_GAIN_15_8			0x03
#घोषणा VC5_RSVD_ADC_OFFSET_7_0			0x04
#घोषणा VC5_RSVD_ADC_OFFSET_15_8		0x05
#घोषणा VC5_RSVD_TEMPY				0x06
#घोषणा VC5_RSVD_OFFSET_TBIN			0x07
#घोषणा VC5_RSVD_GAIN				0x08
#घोषणा VC5_RSVD_TEST_NP			0x09
#घोषणा VC5_RSVD_UNUSED				0x0a
#घोषणा VC5_RSVD_BANDGAP_TRIM_UP		0x0b
#घोषणा VC5_RSVD_BANDGAP_TRIM_DN		0x0c
#घोषणा VC5_RSVD_CLK_R_12_CLK_AMP_4		0x0d
#घोषणा VC5_RSVD_CLK_R_34_CLK_AMP_4		0x0e
#घोषणा VC5_RSVD_CLK_AMP_123			0x0f

/* Configuration रेजिस्टर block */
#घोषणा VC5_PRIM_SRC_SHDN			0x10
#घोषणा VC5_PRIM_SRC_SHDN_EN_XTAL		BIT(7)
#घोषणा VC5_PRIM_SRC_SHDN_EN_CLKIN		BIT(6)
#घोषणा VC5_PRIM_SRC_SHDN_EN_DOUBLE_XTAL_FREQ	BIT(3)
#घोषणा VC5_PRIM_SRC_SHDN_SP			BIT(1)
#घोषणा VC5_PRIM_SRC_SHDN_EN_GBL_SHDN		BIT(0)

#घोषणा VC5_VCO_BAND				0x11
#घोषणा VC5_XTAL_X1_LOAD_CAP			0x12
#घोषणा VC5_XTAL_X2_LOAD_CAP			0x13
#घोषणा VC5_REF_DIVIDER				0x15
#घोषणा VC5_REF_DIVIDER_SEL_PREDIV2		BIT(7)
#घोषणा VC5_REF_DIVIDER_REF_DIV(n)		((n) & 0x3f)

#घोषणा VC5_VCO_CTRL_AND_PREDIV			0x16
#घोषणा VC5_VCO_CTRL_AND_PREDIV_BYPASS_PREDIV	BIT(7)

#घोषणा VC5_FEEDBACK_INT_DIV			0x17
#घोषणा VC5_FEEDBACK_INT_DIV_BITS		0x18
#घोषणा VC5_FEEDBACK_FRAC_DIV(n)		(0x19 + (n))
#घोषणा VC5_RC_CONTROL0				0x1e
#घोषणा VC5_RC_CONTROL1				0x1f
/* Register 0x20 is factory reserved */

/* Output भागider control क्रम भागider 1,2,3,4 */
#घोषणा VC5_OUT_DIV_CONTROL(idx)	(0x21 + ((idx) * 0x10))
#घोषणा VC5_OUT_DIV_CONTROL_RESET	BIT(7)
#घोषणा VC5_OUT_DIV_CONTROL_SELB_NORM	BIT(3)
#घोषणा VC5_OUT_DIV_CONTROL_SEL_EXT	BIT(2)
#घोषणा VC5_OUT_DIV_CONTROL_INT_MODE	BIT(1)
#घोषणा VC5_OUT_DIV_CONTROL_EN_FOD	BIT(0)

#घोषणा VC5_OUT_DIV_FRAC(idx, n)	(0x22 + ((idx) * 0x10) + (n))
#घोषणा VC5_OUT_DIV_FRAC4_OD_SCEE	BIT(1)

#घोषणा VC5_OUT_DIV_STEP_SPREAD(idx, n)	(0x26 + ((idx) * 0x10) + (n))
#घोषणा VC5_OUT_DIV_SPREAD_MOD(idx, n)	(0x29 + ((idx) * 0x10) + (n))
#घोषणा VC5_OUT_DIV_SKEW_INT(idx, n)	(0x2b + ((idx) * 0x10) + (n))
#घोषणा VC5_OUT_DIV_INT(idx, n)		(0x2d + ((idx) * 0x10) + (n))
#घोषणा VC5_OUT_DIV_SKEW_FRAC(idx)	(0x2f + ((idx) * 0x10))
/* Registers 0x30, 0x40, 0x50 are factory reserved */

/* Clock control रेजिस्टर क्रम घड़ी 1,2 */
#घोषणा VC5_CLK_OUTPUT_CFG(idx, n)	(0x60 + ((idx) * 0x2) + (n))
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_SHIFT	5
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_MASK GENMASK(7, VC5_CLK_OUTPUT_CFG0_CFG_SHIFT)

#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_LVPECL	(VC5_LVPECL)
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_CMOS		(VC5_CMOS)
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_HCSL33	(VC5_HCSL33)
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_LVDS		(VC5_LVDS)
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_CMOS2		(VC5_CMOS2)
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_CMOSD		(VC5_CMOSD)
#घोषणा VC5_CLK_OUTPUT_CFG0_CFG_HCSL25	(VC5_HCSL25)

#घोषणा VC5_CLK_OUTPUT_CFG0_PWR_SHIFT	3
#घोषणा VC5_CLK_OUTPUT_CFG0_PWR_MASK GENMASK(4, VC5_CLK_OUTPUT_CFG0_PWR_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_PWR_18	(0<<VC5_CLK_OUTPUT_CFG0_PWR_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_PWR_25	(2<<VC5_CLK_OUTPUT_CFG0_PWR_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_PWR_33	(3<<VC5_CLK_OUTPUT_CFG0_PWR_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_SLEW_SHIFT	0
#घोषणा VC5_CLK_OUTPUT_CFG0_SLEW_MASK GENMASK(1, VC5_CLK_OUTPUT_CFG0_SLEW_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_SLEW_80	(0<<VC5_CLK_OUTPUT_CFG0_SLEW_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_SLEW_85	(1<<VC5_CLK_OUTPUT_CFG0_SLEW_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_SLEW_90	(2<<VC5_CLK_OUTPUT_CFG0_SLEW_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG0_SLEW_100	(3<<VC5_CLK_OUTPUT_CFG0_SLEW_SHIFT)
#घोषणा VC5_CLK_OUTPUT_CFG1_EN_CLKBUF	BIT(0)

#घोषणा VC5_CLK_OE_SHDN				0x68
#घोषणा VC5_CLK_OS_SHDN				0x69

#घोषणा VC5_GLOBAL_REGISTER			0x76
#घोषणा VC5_GLOBAL_REGISTER_GLOBAL_RESET	BIT(5)

/* PLL/VCO runs between 2.5 GHz and 3.0 GHz */
#घोषणा VC5_PLL_VCO_MIN				2500000000UL
#घोषणा VC5_PLL_VCO_MAX				3000000000UL

/* VC5 Input mux settings */
#घोषणा VC5_MUX_IN_XIN		BIT(0)
#घोषणा VC5_MUX_IN_CLKIN	BIT(1)

/* Maximum number of clk_out supported by this driver */
#घोषणा VC5_MAX_CLK_OUT_NUM	5

/* Maximum number of FODs supported by this driver */
#घोषणा VC5_MAX_FOD_NUM	4

/* flags to describe chip features */
/* chip has built-in oscilator */
#घोषणा VC5_HAS_INTERNAL_XTAL	BIT(0)
/* chip has PFD requency द्विगुनr */
#घोषणा VC5_HAS_PFD_FREQ_DBL	BIT(1)

/* Supported IDT VC5 models. */
क्रमागत vc5_model अणु
	IDT_VC5_5P49V5923,
	IDT_VC5_5P49V5925,
	IDT_VC5_5P49V5933,
	IDT_VC5_5P49V5935,
	IDT_VC6_5P49V6901,
	IDT_VC6_5P49V6965,
पूर्ण;

/* Structure to describe features of a particular VC5 model */
काष्ठा vc5_chip_info अणु
	स्थिर क्रमागत vc5_model	model;
	स्थिर अचिन्हित पूर्णांक	clk_fod_cnt;
	स्थिर अचिन्हित पूर्णांक	clk_out_cnt;
	स्थिर u32		flags;
पूर्ण;

काष्ठा vc5_driver_data;

काष्ठा vc5_hw_data अणु
	काष्ठा clk_hw		hw;
	काष्ठा vc5_driver_data	*vc5;
	u32			भाग_पूर्णांक;
	u32			भाग_frc;
	अचिन्हित पूर्णांक		num;
पूर्ण;

काष्ठा vc5_out_data अणु
	काष्ठा clk_hw		hw;
	काष्ठा vc5_driver_data	*vc5;
	अचिन्हित पूर्णांक		num;
	अचिन्हित पूर्णांक		clk_output_cfg0;
	अचिन्हित पूर्णांक		clk_output_cfg0_mask;
पूर्ण;

काष्ठा vc5_driver_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा regmap		*regmap;
	स्थिर काष्ठा vc5_chip_info	*chip_info;

	काष्ठा clk		*pin_xin;
	काष्ठा clk		*pin_clkin;
	अचिन्हित अक्षर		clk_mux_ins;
	काष्ठा clk_hw		clk_mux;
	काष्ठा clk_hw		clk_mul;
	काष्ठा clk_hw		clk_pfd;
	काष्ठा vc5_hw_data	clk_pll;
	काष्ठा vc5_hw_data	clk_fod[VC5_MAX_FOD_NUM];
	काष्ठा vc5_out_data	clk_out[VC5_MAX_CLK_OUT_NUM];
पूर्ण;

/*
 * VersaClock5 i2c regmap
 */
अटल bool vc5_regmap_is_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Factory reserved regs, make them पढ़ो-only */
	अगर (reg <= 0xf)
		वापस false;

	/* Factory reserved regs, make them पढ़ो-only */
	अगर (reg == 0x14 || reg == 0x1c || reg == 0x1d)
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा regmap_config vc5_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = 0x76,
	.ग_लिखोable_reg = vc5_regmap_is_ग_लिखोable,
पूर्ण;

/*
 * VersaClock5 input multiplexer between XTAL and CLKIN भागider
 */
अटल अचिन्हित अक्षर vc5_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा vc5_driver_data *vc5 =
		container_of(hw, काष्ठा vc5_driver_data, clk_mux);
	स्थिर u8 mask = VC5_PRIM_SRC_SHDN_EN_XTAL | VC5_PRIM_SRC_SHDN_EN_CLKIN;
	अचिन्हित पूर्णांक src;

	regmap_पढ़ो(vc5->regmap, VC5_PRIM_SRC_SHDN, &src);
	src &= mask;

	अगर (src == VC5_PRIM_SRC_SHDN_EN_XTAL)
		वापस 0;

	अगर (src == VC5_PRIM_SRC_SHDN_EN_CLKIN)
		वापस 1;

	dev_warn(&vc5->client->dev,
		 "Invalid clock input configuration (%02x)\n", src);
	वापस 0;
पूर्ण

अटल पूर्णांक vc5_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा vc5_driver_data *vc5 =
		container_of(hw, काष्ठा vc5_driver_data, clk_mux);
	स्थिर u8 mask = VC5_PRIM_SRC_SHDN_EN_XTAL | VC5_PRIM_SRC_SHDN_EN_CLKIN;
	u8 src;

	अगर ((index > 1) || !vc5->clk_mux_ins)
		वापस -EINVAL;

	अगर (vc5->clk_mux_ins == (VC5_MUX_IN_CLKIN | VC5_MUX_IN_XIN)) अणु
		अगर (index == 0)
			src = VC5_PRIM_SRC_SHDN_EN_XTAL;
		अगर (index == 1)
			src = VC5_PRIM_SRC_SHDN_EN_CLKIN;
	पूर्ण अन्यथा अणु
		अगर (index != 0)
			वापस -EINVAL;

		अगर (vc5->clk_mux_ins == VC5_MUX_IN_XIN)
			src = VC5_PRIM_SRC_SHDN_EN_XTAL;
		अन्यथा अगर (vc5->clk_mux_ins == VC5_MUX_IN_CLKIN)
			src = VC5_PRIM_SRC_SHDN_EN_CLKIN;
		अन्यथा /* Invalid; should have been caught by vc5_probe() */
			वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(vc5->regmap, VC5_PRIM_SRC_SHDN, mask, src);
पूर्ण

अटल स्थिर काष्ठा clk_ops vc5_mux_ops = अणु
	.set_parent	= vc5_mux_set_parent,
	.get_parent	= vc5_mux_get_parent,
पूर्ण;

अटल अचिन्हित दीर्घ vc5_dbl_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_driver_data *vc5 =
		container_of(hw, काष्ठा vc5_driver_data, clk_mul);
	अचिन्हित पूर्णांक premul;

	regmap_पढ़ो(vc5->regmap, VC5_PRIM_SRC_SHDN, &premul);
	अगर (premul & VC5_PRIM_SRC_SHDN_EN_DOUBLE_XTAL_FREQ)
		parent_rate *= 2;

	वापस parent_rate;
पूर्ण

अटल दीर्घ vc5_dbl_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	अगर ((*parent_rate == rate) || ((*parent_rate * 2) == rate))
		वापस rate;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक vc5_dbl_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_driver_data *vc5 =
		container_of(hw, काष्ठा vc5_driver_data, clk_mul);
	u32 mask;

	अगर ((parent_rate * 2) == rate)
		mask = VC5_PRIM_SRC_SHDN_EN_DOUBLE_XTAL_FREQ;
	अन्यथा
		mask = 0;

	regmap_update_bits(vc5->regmap, VC5_PRIM_SRC_SHDN,
			   VC5_PRIM_SRC_SHDN_EN_DOUBLE_XTAL_FREQ,
			   mask);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops vc5_dbl_ops = अणु
	.recalc_rate	= vc5_dbl_recalc_rate,
	.round_rate	= vc5_dbl_round_rate,
	.set_rate	= vc5_dbl_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ vc5_pfd_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_driver_data *vc5 =
		container_of(hw, काष्ठा vc5_driver_data, clk_pfd);
	अचिन्हित पूर्णांक preभाग, भाग;

	regmap_पढ़ो(vc5->regmap, VC5_VCO_CTRL_AND_PREDIV, &preभाग);

	/* The bypass_preभाग is set, PLL fed from Ref_in directly. */
	अगर (preभाग & VC5_VCO_CTRL_AND_PREDIV_BYPASS_PREDIV)
		वापस parent_rate;

	regmap_पढ़ो(vc5->regmap, VC5_REF_DIVIDER, &भाग);

	/* The Sel_preभाग2 is set, PLL fed from preभाग2 (Ref_in / 2) */
	अगर (भाग & VC5_REF_DIVIDER_SEL_PREDIV2)
		वापस parent_rate / 2;
	अन्यथा
		वापस parent_rate / VC5_REF_DIVIDER_REF_DIV(भाग);
पूर्ण

अटल दीर्घ vc5_pfd_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित दीर्घ iभाग;

	/* PLL cannot operate with input घड़ी above 50 MHz. */
	अगर (rate > 50000000)
		वापस -EINVAL;

	/* CLKIN within range of PLL input, feed directly to PLL. */
	अगर (*parent_rate <= 50000000)
		वापस *parent_rate;

	iभाग = DIV_ROUND_UP(*parent_rate, rate);
	अगर (iभाग > 127)
		वापस -EINVAL;

	वापस *parent_rate / iभाग;
पूर्ण

अटल पूर्णांक vc5_pfd_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_driver_data *vc5 =
		container_of(hw, काष्ठा vc5_driver_data, clk_pfd);
	अचिन्हित दीर्घ iभाग;
	u8 भाग;

	/* CLKIN within range of PLL input, feed directly to PLL. */
	अगर (parent_rate <= 50000000) अणु
		regmap_update_bits(vc5->regmap, VC5_VCO_CTRL_AND_PREDIV,
				   VC5_VCO_CTRL_AND_PREDIV_BYPASS_PREDIV,
				   VC5_VCO_CTRL_AND_PREDIV_BYPASS_PREDIV);
		regmap_update_bits(vc5->regmap, VC5_REF_DIVIDER, 0xff, 0x00);
		वापस 0;
	पूर्ण

	iभाग = DIV_ROUND_UP(parent_rate, rate);

	/* We have dedicated भाग-2 preभागider. */
	अगर (iभाग == 2)
		भाग = VC5_REF_DIVIDER_SEL_PREDIV2;
	अन्यथा
		भाग = VC5_REF_DIVIDER_REF_DIV(iभाग);

	regmap_update_bits(vc5->regmap, VC5_REF_DIVIDER, 0xff, भाग);
	regmap_update_bits(vc5->regmap, VC5_VCO_CTRL_AND_PREDIV,
			   VC5_VCO_CTRL_AND_PREDIV_BYPASS_PREDIV, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops vc5_pfd_ops = अणु
	.recalc_rate	= vc5_pfd_recalc_rate,
	.round_rate	= vc5_pfd_round_rate,
	.set_rate	= vc5_pfd_set_rate,
पूर्ण;

/*
 * VersaClock5 PLL/VCO
 */
अटल अचिन्हित दीर्घ vc5_pll_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_hw_data *hwdata = container_of(hw, काष्ठा vc5_hw_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;
	u32 भाग_पूर्णांक, भाग_frc;
	u8 fb[5];

	regmap_bulk_पढ़ो(vc5->regmap, VC5_FEEDBACK_INT_DIV, fb, 5);

	भाग_पूर्णांक = (fb[0] << 4) | (fb[1] >> 4);
	भाग_frc = (fb[2] << 16) | (fb[3] << 8) | fb[4];

	/* The PLL भागider has 12 पूर्णांकeger bits and 24 fractional bits */
	वापस (parent_rate * भाग_पूर्णांक) + ((parent_rate * भाग_frc) >> 24);
पूर्ण

अटल दीर्घ vc5_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा vc5_hw_data *hwdata = container_of(hw, काष्ठा vc5_hw_data, hw);
	u32 भाग_पूर्णांक;
	u64 भाग_frc;

	अगर (rate < VC5_PLL_VCO_MIN)
		rate = VC5_PLL_VCO_MIN;
	अगर (rate > VC5_PLL_VCO_MAX)
		rate = VC5_PLL_VCO_MAX;

	/* Determine पूर्णांकeger part, which is 12 bit wide */
	भाग_पूर्णांक = rate / *parent_rate;
	अगर (भाग_पूर्णांक > 0xfff)
		rate = *parent_rate * 0xfff;

	/* Determine best fractional part, which is 24 bit wide */
	भाग_frc = rate % *parent_rate;
	भाग_frc *= BIT(24) - 1;
	करो_भाग(भाग_frc, *parent_rate);

	hwdata->भाग_पूर्णांक = भाग_पूर्णांक;
	hwdata->भाग_frc = (u32)भाग_frc;

	वापस (*parent_rate * भाग_पूर्णांक) + ((*parent_rate * भाग_frc) >> 24);
पूर्ण

अटल पूर्णांक vc5_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_hw_data *hwdata = container_of(hw, काष्ठा vc5_hw_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;
	u8 fb[5];

	fb[0] = hwdata->भाग_पूर्णांक >> 4;
	fb[1] = hwdata->भाग_पूर्णांक << 4;
	fb[2] = hwdata->भाग_frc >> 16;
	fb[3] = hwdata->भाग_frc >> 8;
	fb[4] = hwdata->भाग_frc;

	वापस regmap_bulk_ग_लिखो(vc5->regmap, VC5_FEEDBACK_INT_DIV, fb, 5);
पूर्ण

अटल स्थिर काष्ठा clk_ops vc5_pll_ops = अणु
	.recalc_rate	= vc5_pll_recalc_rate,
	.round_rate	= vc5_pll_round_rate,
	.set_rate	= vc5_pll_set_rate,
पूर्ण;

अटल अचिन्हित दीर्घ vc5_fod_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_hw_data *hwdata = container_of(hw, काष्ठा vc5_hw_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;
	/* VCO frequency is भागided by two beक्रमe entering FOD */
	u32 f_in = parent_rate / 2;
	u32 भाग_पूर्णांक, भाग_frc;
	u8 od_पूर्णांक[2];
	u8 od_frc[4];

	regmap_bulk_पढ़ो(vc5->regmap, VC5_OUT_DIV_INT(hwdata->num, 0),
			 od_पूर्णांक, 2);
	regmap_bulk_पढ़ो(vc5->regmap, VC5_OUT_DIV_FRAC(hwdata->num, 0),
			 od_frc, 4);

	भाग_पूर्णांक = (od_पूर्णांक[0] << 4) | (od_पूर्णांक[1] >> 4);
	भाग_frc = (od_frc[0] << 22) | (od_frc[1] << 14) |
		  (od_frc[2] << 6) | (od_frc[3] >> 2);

	/* Aव्योम भागision by zero अगर the output is not configured. */
	अगर (भाग_पूर्णांक == 0 && भाग_frc == 0)
		वापस 0;

	/* The PLL भागider has 12 पूर्णांकeger bits and 30 fractional bits */
	वापस भाग64_u64((u64)f_in << 24ULL, ((u64)भाग_पूर्णांक << 24ULL) + भाग_frc);
पूर्ण

अटल दीर्घ vc5_fod_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा vc5_hw_data *hwdata = container_of(hw, काष्ठा vc5_hw_data, hw);
	/* VCO frequency is भागided by two beक्रमe entering FOD */
	u32 f_in = *parent_rate / 2;
	u32 भाग_पूर्णांक;
	u64 भाग_frc;

	/* Determine पूर्णांकeger part, which is 12 bit wide */
	भाग_पूर्णांक = f_in / rate;
	/*
	 * WARNING: The घड़ी chip करोes not output संकेत अगर the पूर्णांकeger part
	 *          of the भागider is 0xfff and fractional part is non-zero.
	 *          Clamp the भागider at 0xffe to keep the code simple.
	 */
	अगर (भाग_पूर्णांक > 0xffe) अणु
		भाग_पूर्णांक = 0xffe;
		rate = f_in / भाग_पूर्णांक;
	पूर्ण

	/* Determine best fractional part, which is 30 bit wide */
	भाग_frc = f_in % rate;
	भाग_frc <<= 24;
	करो_भाग(भाग_frc, rate);

	hwdata->भाग_पूर्णांक = भाग_पूर्णांक;
	hwdata->भाग_frc = (u32)भाग_frc;

	वापस भाग64_u64((u64)f_in << 24ULL, ((u64)भाग_पूर्णांक << 24ULL) + भाग_frc);
पूर्ण

अटल पूर्णांक vc5_fod_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा vc5_hw_data *hwdata = container_of(hw, काष्ठा vc5_hw_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;
	u8 data[14] = अणु
		hwdata->भाग_frc >> 22, hwdata->भाग_frc >> 14,
		hwdata->भाग_frc >> 6, hwdata->भाग_frc << 2,
		0, 0, 0, 0, 0,
		0, 0,
		hwdata->भाग_पूर्णांक >> 4, hwdata->भाग_पूर्णांक << 4,
		0
	पूर्ण;

	regmap_bulk_ग_लिखो(vc5->regmap, VC5_OUT_DIV_FRAC(hwdata->num, 0),
			  data, 14);

	/*
	 * Toggle magic bit in unकरोcumented रेजिस्टर क्रम unknown reason.
	 * This is what the IDT timing commander tool करोes and the chip
	 * datasheet somewhat implies this is needed, but the रेजिस्टर
	 * and the bit is not करोcumented.
	 */
	regmap_update_bits(vc5->regmap, VC5_GLOBAL_REGISTER,
			   VC5_GLOBAL_REGISTER_GLOBAL_RESET, 0);
	regmap_update_bits(vc5->regmap, VC5_GLOBAL_REGISTER,
			   VC5_GLOBAL_REGISTER_GLOBAL_RESET,
			   VC5_GLOBAL_REGISTER_GLOBAL_RESET);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops vc5_fod_ops = अणु
	.recalc_rate	= vc5_fod_recalc_rate,
	.round_rate	= vc5_fod_round_rate,
	.set_rate	= vc5_fod_set_rate,
पूर्ण;

अटल पूर्णांक vc5_clk_out_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा vc5_out_data *hwdata = container_of(hw, काष्ठा vc5_out_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;
	स्थिर u8 mask = VC5_OUT_DIV_CONTROL_SELB_NORM |
			VC5_OUT_DIV_CONTROL_SEL_EXT |
			VC5_OUT_DIV_CONTROL_EN_FOD;
	अचिन्हित पूर्णांक src;
	पूर्णांक ret;

	/*
	 * If the input mux is disabled, enable it first and
	 * select source from matching FOD.
	 */
	regmap_पढ़ो(vc5->regmap, VC5_OUT_DIV_CONTROL(hwdata->num), &src);
	अगर ((src & mask) == 0) अणु
		src = VC5_OUT_DIV_CONTROL_RESET | VC5_OUT_DIV_CONTROL_EN_FOD;
		ret = regmap_update_bits(vc5->regmap,
					 VC5_OUT_DIV_CONTROL(hwdata->num),
					 mask | VC5_OUT_DIV_CONTROL_RESET, src);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Enable the घड़ी buffer */
	regmap_update_bits(vc5->regmap, VC5_CLK_OUTPUT_CFG(hwdata->num, 1),
			   VC5_CLK_OUTPUT_CFG1_EN_CLKBUF,
			   VC5_CLK_OUTPUT_CFG1_EN_CLKBUF);
	अगर (hwdata->clk_output_cfg0_mask) अणु
		dev_dbg(&vc5->client->dev, "Update output %d mask 0x%0X val 0x%0X\n",
			hwdata->num, hwdata->clk_output_cfg0_mask,
			hwdata->clk_output_cfg0);

		regmap_update_bits(vc5->regmap,
			VC5_CLK_OUTPUT_CFG(hwdata->num, 0),
			hwdata->clk_output_cfg0_mask,
			hwdata->clk_output_cfg0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vc5_clk_out_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा vc5_out_data *hwdata = container_of(hw, काष्ठा vc5_out_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;

	/* Disable the घड़ी buffer */
	regmap_update_bits(vc5->regmap, VC5_CLK_OUTPUT_CFG(hwdata->num, 1),
			   VC5_CLK_OUTPUT_CFG1_EN_CLKBUF, 0);
पूर्ण

अटल अचिन्हित अक्षर vc5_clk_out_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा vc5_out_data *hwdata = container_of(hw, काष्ठा vc5_out_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;
	स्थिर u8 mask = VC5_OUT_DIV_CONTROL_SELB_NORM |
			VC5_OUT_DIV_CONTROL_SEL_EXT |
			VC5_OUT_DIV_CONTROL_EN_FOD;
	स्थिर u8 fodclkmask = VC5_OUT_DIV_CONTROL_SELB_NORM |
			      VC5_OUT_DIV_CONTROL_EN_FOD;
	स्थिर u8 extclk = VC5_OUT_DIV_CONTROL_SELB_NORM |
			  VC5_OUT_DIV_CONTROL_SEL_EXT;
	अचिन्हित पूर्णांक src;

	regmap_पढ़ो(vc5->regmap, VC5_OUT_DIV_CONTROL(hwdata->num), &src);
	src &= mask;

	अगर (src == 0)	/* Input mux set to DISABLED */
		वापस 0;

	अगर ((src & fodclkmask) == VC5_OUT_DIV_CONTROL_EN_FOD)
		वापस 0;

	अगर (src == extclk)
		वापस 1;

	dev_warn(&vc5->client->dev,
		 "Invalid clock output configuration (%02x)\n", src);
	वापस 0;
पूर्ण

अटल पूर्णांक vc5_clk_out_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा vc5_out_data *hwdata = container_of(hw, काष्ठा vc5_out_data, hw);
	काष्ठा vc5_driver_data *vc5 = hwdata->vc5;
	स्थिर u8 mask = VC5_OUT_DIV_CONTROL_RESET |
			VC5_OUT_DIV_CONTROL_SELB_NORM |
			VC5_OUT_DIV_CONTROL_SEL_EXT |
			VC5_OUT_DIV_CONTROL_EN_FOD;
	स्थिर u8 extclk = VC5_OUT_DIV_CONTROL_SELB_NORM |
			  VC5_OUT_DIV_CONTROL_SEL_EXT;
	u8 src = VC5_OUT_DIV_CONTROL_RESET;

	अगर (index == 0)
		src |= VC5_OUT_DIV_CONTROL_EN_FOD;
	अन्यथा
		src |= extclk;

	वापस regmap_update_bits(vc5->regmap, VC5_OUT_DIV_CONTROL(hwdata->num),
				  mask, src);
पूर्ण

अटल स्थिर काष्ठा clk_ops vc5_clk_out_ops = अणु
	.prepare	= vc5_clk_out_prepare,
	.unprepare	= vc5_clk_out_unprepare,
	.set_parent	= vc5_clk_out_set_parent,
	.get_parent	= vc5_clk_out_get_parent,
पूर्ण;

अटल काष्ठा clk_hw *vc5_of_clk_get(काष्ठा of_phandle_args *clkspec,
				     व्योम *data)
अणु
	काष्ठा vc5_driver_data *vc5 = data;
	अचिन्हित पूर्णांक idx = clkspec->args[0];

	अगर (idx >= vc5->chip_info->clk_out_cnt)
		वापस ERR_PTR(-EINVAL);

	वापस &vc5->clk_out[idx].hw;
पूर्ण

अटल पूर्णांक vc5_map_index_to_output(स्थिर क्रमागत vc5_model model,
				   स्थिर अचिन्हित पूर्णांक n)
अणु
	चयन (model) अणु
	हाल IDT_VC5_5P49V5933:
		वापस (n == 0) ? 0 : 3;
	हाल IDT_VC5_5P49V5923:
	हाल IDT_VC5_5P49V5925:
	हाल IDT_VC5_5P49V5935:
	हाल IDT_VC6_5P49V6901:
	हाल IDT_VC6_5P49V6965:
	शेष:
		वापस n;
	पूर्ण
पूर्ण

अटल पूर्णांक vc5_update_mode(काष्ठा device_node *np_output,
			   काष्ठा vc5_out_data *clk_out)
अणु
	u32 value;

	अगर (!of_property_पढ़ो_u32(np_output, "idt,mode", &value)) अणु
		clk_out->clk_output_cfg0_mask |= VC5_CLK_OUTPUT_CFG0_CFG_MASK;
		चयन (value) अणु
		हाल VC5_CLK_OUTPUT_CFG0_CFG_LVPECL:
		हाल VC5_CLK_OUTPUT_CFG0_CFG_CMOS:
		हाल VC5_CLK_OUTPUT_CFG0_CFG_HCSL33:
		हाल VC5_CLK_OUTPUT_CFG0_CFG_LVDS:
		हाल VC5_CLK_OUTPUT_CFG0_CFG_CMOS2:
		हाल VC5_CLK_OUTPUT_CFG0_CFG_CMOSD:
		हाल VC5_CLK_OUTPUT_CFG0_CFG_HCSL25:
			clk_out->clk_output_cfg0 |=
			    value << VC5_CLK_OUTPUT_CFG0_CFG_SHIFT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vc5_update_घातer(काष्ठा device_node *np_output,
			    काष्ठा vc5_out_data *clk_out)
अणु
	u32 value;

	अगर (!of_property_पढ़ो_u32(np_output, "idt,voltage-microvolt",
				  &value)) अणु
		clk_out->clk_output_cfg0_mask |= VC5_CLK_OUTPUT_CFG0_PWR_MASK;
		चयन (value) अणु
		हाल 1800000:
			clk_out->clk_output_cfg0 |= VC5_CLK_OUTPUT_CFG0_PWR_18;
			अवरोध;
		हाल 2500000:
			clk_out->clk_output_cfg0 |= VC5_CLK_OUTPUT_CFG0_PWR_25;
			अवरोध;
		हाल 3300000:
			clk_out->clk_output_cfg0 |= VC5_CLK_OUTPUT_CFG0_PWR_33;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vc5_map_cap_value(u32 femtofarads)
अणु
	पूर्णांक mapped_value;

	/*
	 * The datasheet explicitly states 9000 - 25000 with 0.5pF
	 * steps, but the Programmer's guide shows the steps are 0.430pF.
	 * After getting feedback from Renesas, the .5pF steps were the
	 * goal, but 430nF was the actual values.
	 * Because of this, the actual range goes to 22760 instead of 25000
	 */
	अगर (femtofarads < 9000 || femtofarads > 22760)
		वापस -EINVAL;

	/*
	 * The Programmer's guide shows XTAL[5:0] but in reality,
	 * XTAL[0] and XTAL[1] are both LSB which makes the math
	 * strange.  With clarfication from Renesas, setting the
	 * values should be simpler by ignoring XTAL[0]
	 */
	mapped_value = DIV_ROUND_CLOSEST(femtofarads - 9000, 430);

	/*
	 * Since the calculation ignores XTAL[0], there is one
	 * special हाल where mapped_value = 32.  In reality, this means
	 * the real mapped value should be 111111b.  In other हालs,
	 * the mapped_value needs to be shअगरted 1 to the left.
	 */
	अगर (mapped_value > 31)
		mapped_value = 0x3f;
	अन्यथा
		mapped_value <<= 1;

	वापस mapped_value;
पूर्ण
अटल पूर्णांक vc5_update_cap_load(काष्ठा device_node *node, काष्ठा vc5_driver_data *vc5)
अणु
	u32 value;
	पूर्णांक mapped_value;

	अगर (!of_property_पढ़ो_u32(node, "idt,xtal-load-femtofarads", &value)) अणु
		mapped_value = vc5_map_cap_value(value);
		अगर (mapped_value < 0)
			वापस mapped_value;

		/*
		 * The mapped_value is really the high 6 bits of
		 * VC5_XTAL_X1_LOAD_CAP and VC5_XTAL_X2_LOAD_CAP, so
		 * shअगरt the value 2 places.
		 */
		regmap_update_bits(vc5->regmap, VC5_XTAL_X1_LOAD_CAP, ~0x03, mapped_value << 2);
		regmap_update_bits(vc5->regmap, VC5_XTAL_X2_LOAD_CAP, ~0x03, mapped_value << 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vc5_update_slew(काष्ठा device_node *np_output,
			   काष्ठा vc5_out_data *clk_out)
अणु
	u32 value;

	अगर (!of_property_पढ़ो_u32(np_output, "idt,slew-percent", &value)) अणु
		clk_out->clk_output_cfg0_mask |= VC5_CLK_OUTPUT_CFG0_SLEW_MASK;
		चयन (value) अणु
		हाल 80:
			clk_out->clk_output_cfg0 |= VC5_CLK_OUTPUT_CFG0_SLEW_80;
			अवरोध;
		हाल 85:
			clk_out->clk_output_cfg0 |= VC5_CLK_OUTPUT_CFG0_SLEW_85;
			अवरोध;
		हाल 90:
			clk_out->clk_output_cfg0 |= VC5_CLK_OUTPUT_CFG0_SLEW_90;
			अवरोध;
		हाल 100:
			clk_out->clk_output_cfg0 |=
			    VC5_CLK_OUTPUT_CFG0_SLEW_100;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vc5_get_output_config(काष्ठा i2c_client *client,
				 काष्ठा vc5_out_data *clk_out)
अणु
	काष्ठा device_node *np_output;
	अक्षर *child_name;
	पूर्णांक ret = 0;

	child_name = kaप्र_लिखो(GFP_KERNEL, "OUT%d", clk_out->num + 1);
	अगर (!child_name)
		वापस -ENOMEM;

	np_output = of_get_child_by_name(client->dev.of_node, child_name);
	kमुक्त(child_name);
	अगर (!np_output)
		वापस 0;

	ret = vc5_update_mode(np_output, clk_out);
	अगर (ret)
		जाओ output_error;

	ret = vc5_update_घातer(np_output, clk_out);
	अगर (ret)
		जाओ output_error;

	ret = vc5_update_slew(np_output, clk_out);

output_error:
	अगर (ret) अणु
		dev_err(&client->dev,
			"Invalid clock output configuration OUT%d\n",
			clk_out->num + 1);
	पूर्ण

	of_node_put(np_output);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id clk_vc5_of_match[];

अटल पूर्णांक vc5_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vc5_driver_data *vc5;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *parent_names[2];
	अचिन्हित पूर्णांक n, idx = 0;
	पूर्णांक ret;

	vc5 = devm_kzalloc(&client->dev, माप(*vc5), GFP_KERNEL);
	अगर (!vc5)
		वापस -ENOMEM;

	i2c_set_clientdata(client, vc5);
	vc5->client = client;
	vc5->chip_info = of_device_get_match_data(&client->dev);

	vc5->pin_xin = devm_clk_get(&client->dev, "xin");
	अगर (PTR_ERR(vc5->pin_xin) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	vc5->pin_clkin = devm_clk_get(&client->dev, "clkin");
	अगर (PTR_ERR(vc5->pin_clkin) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	vc5->regmap = devm_regmap_init_i2c(client, &vc5_regmap_config);
	अगर (IS_ERR(vc5->regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		वापस PTR_ERR(vc5->regmap);
	पूर्ण

	/* Register घड़ी input mux */
	स_रखो(&init, 0, माप(init));

	अगर (!IS_ERR(vc5->pin_xin)) अणु
		vc5->clk_mux_ins |= VC5_MUX_IN_XIN;
		parent_names[init.num_parents++] = __clk_get_name(vc5->pin_xin);
	पूर्ण अन्यथा अगर (vc5->chip_info->flags & VC5_HAS_INTERNAL_XTAL) अणु
		vc5->pin_xin = clk_रेजिस्टर_fixed_rate(&client->dev,
						       "internal-xtal", शून्य,
						       0, 25000000);
		अगर (IS_ERR(vc5->pin_xin))
			वापस PTR_ERR(vc5->pin_xin);
		vc5->clk_mux_ins |= VC5_MUX_IN_XIN;
		parent_names[init.num_parents++] = __clk_get_name(vc5->pin_xin);
	पूर्ण

	अगर (!IS_ERR(vc5->pin_clkin)) अणु
		vc5->clk_mux_ins |= VC5_MUX_IN_CLKIN;
		parent_names[init.num_parents++] =
		    __clk_get_name(vc5->pin_clkin);
	पूर्ण

	अगर (!init.num_parents) अणु
		dev_err(&client->dev, "no input clock specified!\n");
		वापस -EINVAL;
	पूर्ण

	/* Configure Optional Loading Capacitance क्रम बाह्यal XTAL */
	अगर (!(vc5->chip_info->flags & VC5_HAS_INTERNAL_XTAL)) अणु
		ret = vc5_update_cap_load(client->dev.of_node, vc5);
		अगर (ret)
			जाओ err_clk_रेजिस्टर;
	पूर्ण

	init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.mux", client->dev.of_node);
	init.ops = &vc5_mux_ops;
	init.flags = 0;
	init.parent_names = parent_names;
	vc5->clk_mux.init = &init;
	ret = devm_clk_hw_रेजिस्टर(&client->dev, &vc5->clk_mux);
	अगर (ret)
		जाओ err_clk_रेजिस्टर;
	kमुक्त(init.name);	/* घड़ी framework made a copy of the name */

	अगर (vc5->chip_info->flags & VC5_HAS_PFD_FREQ_DBL) अणु
		/* Register frequency द्विगुनr */
		स_रखो(&init, 0, माप(init));
		init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.dbl",
				      client->dev.of_node);
		init.ops = &vc5_dbl_ops;
		init.flags = CLK_SET_RATE_PARENT;
		init.parent_names = parent_names;
		parent_names[0] = clk_hw_get_name(&vc5->clk_mux);
		init.num_parents = 1;
		vc5->clk_mul.init = &init;
		ret = devm_clk_hw_रेजिस्टर(&client->dev, &vc5->clk_mul);
		अगर (ret)
			जाओ err_clk_रेजिस्टर;
		kमुक्त(init.name); /* घड़ी framework made a copy of the name */
	पूर्ण

	/* Register PFD */
	स_रखो(&init, 0, माप(init));
	init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.pfd", client->dev.of_node);
	init.ops = &vc5_pfd_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_names;
	अगर (vc5->chip_info->flags & VC5_HAS_PFD_FREQ_DBL)
		parent_names[0] = clk_hw_get_name(&vc5->clk_mul);
	अन्यथा
		parent_names[0] = clk_hw_get_name(&vc5->clk_mux);
	init.num_parents = 1;
	vc5->clk_pfd.init = &init;
	ret = devm_clk_hw_रेजिस्टर(&client->dev, &vc5->clk_pfd);
	अगर (ret)
		जाओ err_clk_रेजिस्टर;
	kमुक्त(init.name);	/* घड़ी framework made a copy of the name */

	/* Register PLL */
	स_रखो(&init, 0, माप(init));
	init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.pll", client->dev.of_node);
	init.ops = &vc5_pll_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_names;
	parent_names[0] = clk_hw_get_name(&vc5->clk_pfd);
	init.num_parents = 1;
	vc5->clk_pll.num = 0;
	vc5->clk_pll.vc5 = vc5;
	vc5->clk_pll.hw.init = &init;
	ret = devm_clk_hw_रेजिस्टर(&client->dev, &vc5->clk_pll.hw);
	अगर (ret)
		जाओ err_clk_रेजिस्टर;
	kमुक्त(init.name); /* घड़ी framework made a copy of the name */

	/* Register FODs */
	क्रम (n = 0; n < vc5->chip_info->clk_fod_cnt; n++) अणु
		idx = vc5_map_index_to_output(vc5->chip_info->model, n);
		स_रखो(&init, 0, माप(init));
		init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.fod%d",
				      client->dev.of_node, idx);
		init.ops = &vc5_fod_ops;
		init.flags = CLK_SET_RATE_PARENT;
		init.parent_names = parent_names;
		parent_names[0] = clk_hw_get_name(&vc5->clk_pll.hw);
		init.num_parents = 1;
		vc5->clk_fod[n].num = idx;
		vc5->clk_fod[n].vc5 = vc5;
		vc5->clk_fod[n].hw.init = &init;
		ret = devm_clk_hw_रेजिस्टर(&client->dev, &vc5->clk_fod[n].hw);
		अगर (ret)
			जाओ err_clk_रेजिस्टर;
		kमुक्त(init.name); /* घड़ी framework made a copy of the name */
	पूर्ण

	/* Register MUX-connected OUT0_I2C_SELB output */
	स_रखो(&init, 0, माप(init));
	init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.out0_sel_i2cb",
			      client->dev.of_node);
	init.ops = &vc5_clk_out_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = parent_names;
	parent_names[0] = clk_hw_get_name(&vc5->clk_mux);
	init.num_parents = 1;
	vc5->clk_out[0].num = idx;
	vc5->clk_out[0].vc5 = vc5;
	vc5->clk_out[0].hw.init = &init;
	ret = devm_clk_hw_रेजिस्टर(&client->dev, &vc5->clk_out[0].hw);
	अगर (ret)
		जाओ err_clk_रेजिस्टर;
	kमुक्त(init.name); /* घड़ी framework made a copy of the name */

	/* Register FOD-connected OUTx outमाला_दो */
	क्रम (n = 1; n < vc5->chip_info->clk_out_cnt; n++) अणु
		idx = vc5_map_index_to_output(vc5->chip_info->model, n - 1);
		parent_names[0] = clk_hw_get_name(&vc5->clk_fod[idx].hw);
		अगर (n == 1)
			parent_names[1] = clk_hw_get_name(&vc5->clk_mux);
		अन्यथा
			parent_names[1] =
			    clk_hw_get_name(&vc5->clk_out[n - 1].hw);

		स_रखो(&init, 0, माप(init));
		init.name = kaप्र_लिखो(GFP_KERNEL, "%pOFn.out%d",
				      client->dev.of_node, idx + 1);
		init.ops = &vc5_clk_out_ops;
		init.flags = CLK_SET_RATE_PARENT;
		init.parent_names = parent_names;
		init.num_parents = 2;
		vc5->clk_out[n].num = idx;
		vc5->clk_out[n].vc5 = vc5;
		vc5->clk_out[n].hw.init = &init;
		ret = devm_clk_hw_रेजिस्टर(&client->dev, &vc5->clk_out[n].hw);
		अगर (ret)
			जाओ err_clk_रेजिस्टर;
		kमुक्त(init.name); /* घड़ी framework made a copy of the name */

		/* Fetch Clock Output configuration from DT (अगर specअगरied) */
		ret = vc5_get_output_config(client, &vc5->clk_out[n]);
		अगर (ret)
			जाओ err_clk;
	पूर्ण

	ret = of_clk_add_hw_provider(client->dev.of_node, vc5_of_clk_get, vc5);
	अगर (ret) अणु
		dev_err(&client->dev, "unable to add clk provider\n");
		जाओ err_clk;
	पूर्ण

	वापस 0;

err_clk_रेजिस्टर:
	dev_err(&client->dev, "unable to register %s\n", init.name);
	kमुक्त(init.name); /* घड़ी framework made a copy of the name */
err_clk:
	अगर (vc5->chip_info->flags & VC5_HAS_INTERNAL_XTAL)
		clk_unरेजिस्टर_fixed_rate(vc5->pin_xin);
	वापस ret;
पूर्ण

अटल पूर्णांक vc5_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा vc5_driver_data *vc5 = i2c_get_clientdata(client);

	of_clk_del_provider(client->dev.of_node);

	अगर (vc5->chip_info->flags & VC5_HAS_INTERNAL_XTAL)
		clk_unरेजिस्टर_fixed_rate(vc5->pin_xin);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused vc5_suspend(काष्ठा device *dev)
अणु
	काष्ठा vc5_driver_data *vc5 = dev_get_drvdata(dev);

	regcache_cache_only(vc5->regmap, true);
	regcache_mark_dirty(vc5->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused vc5_resume(काष्ठा device *dev)
अणु
	काष्ठा vc5_driver_data *vc5 = dev_get_drvdata(dev);
	पूर्णांक ret;

	regcache_cache_only(vc5->regmap, false);
	ret = regcache_sync(vc5->regmap);
	अगर (ret)
		dev_err(dev, "Failed to restore register map: %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vc5_chip_info idt_5p49v5923_info = अणु
	.model = IDT_VC5_5P49V5923,
	.clk_fod_cnt = 2,
	.clk_out_cnt = 3,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा vc5_chip_info idt_5p49v5925_info = अणु
	.model = IDT_VC5_5P49V5925,
	.clk_fod_cnt = 4,
	.clk_out_cnt = 5,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा vc5_chip_info idt_5p49v5933_info = अणु
	.model = IDT_VC5_5P49V5933,
	.clk_fod_cnt = 2,
	.clk_out_cnt = 3,
	.flags = VC5_HAS_INTERNAL_XTAL,
पूर्ण;

अटल स्थिर काष्ठा vc5_chip_info idt_5p49v5935_info = अणु
	.model = IDT_VC5_5P49V5935,
	.clk_fod_cnt = 4,
	.clk_out_cnt = 5,
	.flags = VC5_HAS_INTERNAL_XTAL,
पूर्ण;

अटल स्थिर काष्ठा vc5_chip_info idt_5p49v6901_info = अणु
	.model = IDT_VC6_5P49V6901,
	.clk_fod_cnt = 4,
	.clk_out_cnt = 5,
	.flags = VC5_HAS_PFD_FREQ_DBL,
पूर्ण;

अटल स्थिर काष्ठा vc5_chip_info idt_5p49v6965_info = अणु
	.model = IDT_VC6_5P49V6965,
	.clk_fod_cnt = 4,
	.clk_out_cnt = 5,
	.flags = 0,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id vc5_id[] = अणु
	अणु "5p49v5923", .driver_data = IDT_VC5_5P49V5923 पूर्ण,
	अणु "5p49v5925", .driver_data = IDT_VC5_5P49V5925 पूर्ण,
	अणु "5p49v5933", .driver_data = IDT_VC5_5P49V5933 पूर्ण,
	अणु "5p49v5935", .driver_data = IDT_VC5_5P49V5935 पूर्ण,
	अणु "5p49v6901", .driver_data = IDT_VC6_5P49V6901 पूर्ण,
	अणु "5p49v6965", .driver_data = IDT_VC6_5P49V6965 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vc5_id);

अटल स्थिर काष्ठा of_device_id clk_vc5_of_match[] = अणु
	अणु .compatible = "idt,5p49v5923", .data = &idt_5p49v5923_info पूर्ण,
	अणु .compatible = "idt,5p49v5925", .data = &idt_5p49v5925_info पूर्ण,
	अणु .compatible = "idt,5p49v5933", .data = &idt_5p49v5933_info पूर्ण,
	अणु .compatible = "idt,5p49v5935", .data = &idt_5p49v5935_info पूर्ण,
	अणु .compatible = "idt,5p49v6901", .data = &idt_5p49v6901_info पूर्ण,
	अणु .compatible = "idt,5p49v6965", .data = &idt_5p49v6965_info पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_vc5_of_match);

अटल SIMPLE_DEV_PM_OPS(vc5_pm_ops, vc5_suspend, vc5_resume);

अटल काष्ठा i2c_driver vc5_driver = अणु
	.driver = अणु
		.name = "vc5",
		.pm	= &vc5_pm_ops,
		.of_match_table = clk_vc5_of_match,
	पूर्ण,
	.probe		= vc5_probe,
	.हटाओ		= vc5_हटाओ,
	.id_table	= vc5_id,
पूर्ण;
module_i2c_driver(vc5_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("IDT VersaClock 5 driver");
MODULE_LICENSE("GPL");
