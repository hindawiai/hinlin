<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>

#समावेश "clk-alpha-pll.h"
#समावेश "common.h"

#घोषणा PLL_MODE(p)		((p)->offset + 0x0)
# define PLL_OUTCTRL		BIT(0)
# define PLL_BYPASSNL		BIT(1)
# define PLL_RESET_N		BIT(2)
# define PLL_OFFLINE_REQ	BIT(7)
# define PLL_LOCK_COUNT_SHIFT	8
# define PLL_LOCK_COUNT_MASK	0x3f
# define PLL_BIAS_COUNT_SHIFT	14
# define PLL_BIAS_COUNT_MASK	0x3f
# define PLL_VOTE_FSM_ENA	BIT(20)
# define PLL_FSM_ENA		BIT(20)
# define PLL_VOTE_FSM_RESET	BIT(21)
# define PLL_UPDATE		BIT(22)
# define PLL_UPDATE_BYPASS	BIT(23)
# define PLL_OFFLINE_ACK	BIT(28)
# define ALPHA_PLL_ACK_LATCH	BIT(29)
# define PLL_ACTIVE_FLAG	BIT(30)
# define PLL_LOCK_DET		BIT(31)

#घोषणा PLL_L_VAL(p)		((p)->offset + (p)->regs[PLL_OFF_L_VAL])
#घोषणा PLL_CAL_L_VAL(p)	((p)->offset + (p)->regs[PLL_OFF_CAL_L_VAL])
#घोषणा PLL_ALPHA_VAL(p)	((p)->offset + (p)->regs[PLL_OFF_ALPHA_VAL])
#घोषणा PLL_ALPHA_VAL_U(p)	((p)->offset + (p)->regs[PLL_OFF_ALPHA_VAL_U])

#घोषणा PLL_USER_CTL(p)		((p)->offset + (p)->regs[PLL_OFF_USER_CTL])
# define PLL_POST_DIV_SHIFT	8
# define PLL_POST_DIV_MASK(p)	GENMASK((p)->width, 0)
# define PLL_ALPHA_EN		BIT(24)
# define PLL_ALPHA_MODE		BIT(25)
# define PLL_VCO_SHIFT		20
# define PLL_VCO_MASK		0x3

#घोषणा PLL_USER_CTL_U(p)	((p)->offset + (p)->regs[PLL_OFF_USER_CTL_U])
#घोषणा PLL_USER_CTL_U1(p)	((p)->offset + (p)->regs[PLL_OFF_USER_CTL_U1])

#घोषणा PLL_CONFIG_CTL(p)	((p)->offset + (p)->regs[PLL_OFF_CONFIG_CTL])
#घोषणा PLL_CONFIG_CTL_U(p)	((p)->offset + (p)->regs[PLL_OFF_CONFIG_CTL_U])
#घोषणा PLL_CONFIG_CTL_U1(p)	((p)->offset + (p)->regs[PLL_OFF_CONFIG_CTL_U1])
#घोषणा PLL_TEST_CTL(p)		((p)->offset + (p)->regs[PLL_OFF_TEST_CTL])
#घोषणा PLL_TEST_CTL_U(p)	((p)->offset + (p)->regs[PLL_OFF_TEST_CTL_U])
#घोषणा PLL_TEST_CTL_U1(p)     ((p)->offset + (p)->regs[PLL_OFF_TEST_CTL_U1])
#घोषणा PLL_STATUS(p)		((p)->offset + (p)->regs[PLL_OFF_STATUS])
#घोषणा PLL_OPMODE(p)		((p)->offset + (p)->regs[PLL_OFF_OPMODE])
#घोषणा PLL_FRAC(p)		((p)->offset + (p)->regs[PLL_OFF_FRAC])

स्थिर u8 clk_alpha_pll_regs[][PLL_OFF_MAX_REGS] = अणु
	[CLK_ALPHA_PLL_TYPE_DEFAULT] =  अणु
		[PLL_OFF_L_VAL] = 0x04,
		[PLL_OFF_ALPHA_VAL] = 0x08,
		[PLL_OFF_ALPHA_VAL_U] = 0x0c,
		[PLL_OFF_USER_CTL] = 0x10,
		[PLL_OFF_USER_CTL_U] = 0x14,
		[PLL_OFF_CONFIG_CTL] = 0x18,
		[PLL_OFF_TEST_CTL] = 0x1c,
		[PLL_OFF_TEST_CTL_U] = 0x20,
		[PLL_OFF_STATUS] = 0x24,
	पूर्ण,
	[CLK_ALPHA_PLL_TYPE_HUAYRA] =  अणु
		[PLL_OFF_L_VAL] = 0x04,
		[PLL_OFF_ALPHA_VAL] = 0x08,
		[PLL_OFF_USER_CTL] = 0x10,
		[PLL_OFF_CONFIG_CTL] = 0x14,
		[PLL_OFF_CONFIG_CTL_U] = 0x18,
		[PLL_OFF_TEST_CTL] = 0x1c,
		[PLL_OFF_TEST_CTL_U] = 0x20,
		[PLL_OFF_STATUS] = 0x24,
	पूर्ण,
	[CLK_ALPHA_PLL_TYPE_BRAMMO] =  अणु
		[PLL_OFF_L_VAL] = 0x04,
		[PLL_OFF_ALPHA_VAL] = 0x08,
		[PLL_OFF_ALPHA_VAL_U] = 0x0c,
		[PLL_OFF_USER_CTL] = 0x10,
		[PLL_OFF_CONFIG_CTL] = 0x18,
		[PLL_OFF_TEST_CTL] = 0x1c,
		[PLL_OFF_STATUS] = 0x24,
	पूर्ण,
	[CLK_ALPHA_PLL_TYPE_FABIA] =  अणु
		[PLL_OFF_L_VAL] = 0x04,
		[PLL_OFF_USER_CTL] = 0x0c,
		[PLL_OFF_USER_CTL_U] = 0x10,
		[PLL_OFF_CONFIG_CTL] = 0x14,
		[PLL_OFF_CONFIG_CTL_U] = 0x18,
		[PLL_OFF_TEST_CTL] = 0x1c,
		[PLL_OFF_TEST_CTL_U] = 0x20,
		[PLL_OFF_STATUS] = 0x24,
		[PLL_OFF_OPMODE] = 0x2c,
		[PLL_OFF_FRAC] = 0x38,
	पूर्ण,
	[CLK_ALPHA_PLL_TYPE_TRION] = अणु
		[PLL_OFF_L_VAL] = 0x04,
		[PLL_OFF_CAL_L_VAL] = 0x08,
		[PLL_OFF_USER_CTL] = 0x0c,
		[PLL_OFF_USER_CTL_U] = 0x10,
		[PLL_OFF_USER_CTL_U1] = 0x14,
		[PLL_OFF_CONFIG_CTL] = 0x18,
		[PLL_OFF_CONFIG_CTL_U] = 0x1c,
		[PLL_OFF_CONFIG_CTL_U1] = 0x20,
		[PLL_OFF_TEST_CTL] = 0x24,
		[PLL_OFF_TEST_CTL_U] = 0x28,
		[PLL_OFF_TEST_CTL_U1] = 0x2c,
		[PLL_OFF_STATUS] = 0x30,
		[PLL_OFF_OPMODE] = 0x38,
		[PLL_OFF_ALPHA_VAL] = 0x40,
	पूर्ण,
	[CLK_ALPHA_PLL_TYPE_AGERA] =  अणु
		[PLL_OFF_L_VAL] = 0x04,
		[PLL_OFF_ALPHA_VAL] = 0x08,
		[PLL_OFF_USER_CTL] = 0x0c,
		[PLL_OFF_CONFIG_CTL] = 0x10,
		[PLL_OFF_CONFIG_CTL_U] = 0x14,
		[PLL_OFF_TEST_CTL] = 0x18,
		[PLL_OFF_TEST_CTL_U] = 0x1c,
		[PLL_OFF_STATUS] = 0x2c,
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_regs);

/*
 * Even though 40 bits are present, use only 32 क्रम ease of calculation.
 */
#घोषणा ALPHA_REG_BITWIDTH	40
#घोषणा ALPHA_REG_16BIT_WIDTH	16
#घोषणा ALPHA_BITWIDTH		32U
#घोषणा ALPHA_SHIFT(w)		min(w, ALPHA_BITWIDTH)

#घोषणा PLL_HUAYRA_M_WIDTH		8
#घोषणा PLL_HUAYRA_M_SHIFT		8
#घोषणा PLL_HUAYRA_M_MASK		0xff
#घोषणा PLL_HUAYRA_N_SHIFT		0
#घोषणा PLL_HUAYRA_N_MASK		0xff
#घोषणा PLL_HUAYRA_ALPHA_WIDTH		16

#घोषणा PLL_STANDBY		0x0
#घोषणा PLL_RUN			0x1
#घोषणा PLL_OUT_MASK		0x7
#घोषणा PLL_RATE_MARGIN		500

/* TRION PLL specअगरic settings and offsets */
#घोषणा TRION_PLL_CAL_VAL	0x44
#घोषणा TRION_PCAL_DONE		BIT(26)

/* LUCID PLL specअगरic settings and offsets */
#घोषणा LUCID_PCAL_DONE		BIT(27)

/* LUCID 5LPE PLL specअगरic settings and offsets */
#घोषणा LUCID_5LPE_PCAL_DONE		BIT(11)
#घोषणा LUCID_5LPE_ALPHA_PLL_ACK_LATCH	BIT(13)
#घोषणा LUCID_5LPE_PLL_LATCH_INPUT	BIT(14)
#घोषणा LUCID_5LPE_ENABLE_VOTE_RUN	BIT(21)

#घोषणा pll_alpha_width(p)					\
		((PLL_ALPHA_VAL_U(p) - PLL_ALPHA_VAL(p) == 4) ?	\
				 ALPHA_REG_BITWIDTH : ALPHA_REG_16BIT_WIDTH)

#घोषणा pll_has_64bit_config(p)	((PLL_CONFIG_CTL_U(p) - PLL_CONFIG_CTL(p)) == 4)

#घोषणा to_clk_alpha_pll(_hw) container_of(to_clk_regmap(_hw), \
					   काष्ठा clk_alpha_pll, clkr)

#घोषणा to_clk_alpha_pll_postभाग(_hw) container_of(to_clk_regmap(_hw), \
					   काष्ठा clk_alpha_pll_postभाग, clkr)

अटल पूर्णांक रुको_क्रम_pll(काष्ठा clk_alpha_pll *pll, u32 mask, bool inverse,
			स्थिर अक्षर *action)
अणु
	u32 val;
	पूर्णांक count;
	पूर्णांक ret;
	स्थिर अक्षर *name = clk_hw_get_name(&pll->clkr.hw);

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	क्रम (count = 100; count > 0; count--) अणु
		ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
		अगर (ret)
			वापस ret;
		अगर (inverse && !(val & mask))
			वापस 0;
		अन्यथा अगर ((val & mask) == mask)
			वापस 0;

		udelay(1);
	पूर्ण

	WARN(1, "%s failed to %s!\n", name, action);
	वापस -ETIMEDOUT;
पूर्ण

#घोषणा रुको_क्रम_pll_enable_active(pll) \
	रुको_क्रम_pll(pll, PLL_ACTIVE_FLAG, 0, "enable")

#घोषणा रुको_क्रम_pll_enable_lock(pll) \
	रुको_क्रम_pll(pll, PLL_LOCK_DET, 0, "enable")

#घोषणा रुको_क्रम_pll_disable(pll) \
	रुको_क्रम_pll(pll, PLL_ACTIVE_FLAG, 1, "disable")

#घोषणा रुको_क्रम_pll_offline(pll) \
	रुको_क्रम_pll(pll, PLL_OFFLINE_ACK, 0, "offline")

#घोषणा रुको_क्रम_pll_update(pll) \
	रुको_क्रम_pll(pll, PLL_UPDATE, 1, "update")

#घोषणा रुको_क्रम_pll_update_ack_set(pll) \
	रुको_क्रम_pll(pll, ALPHA_PLL_ACK_LATCH, 0, "update_ack_set")

#घोषणा रुको_क्रम_pll_update_ack_clear(pll) \
	रुको_क्रम_pll(pll, ALPHA_PLL_ACK_LATCH, 1, "update_ack_clear")

अटल व्योम clk_alpha_pll_ग_लिखो_config(काष्ठा regmap *regmap, अचिन्हित पूर्णांक reg,
					अचिन्हित पूर्णांक val)
अणु
	अगर (val)
		regmap_ग_लिखो(regmap, reg, val);
पूर्ण

व्योम clk_alpha_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
			     स्थिर काष्ठा alpha_pll_config *config)
अणु
	u32 val, mask;

	regmap_ग_लिखो(regmap, PLL_L_VAL(pll), config->l);
	regmap_ग_लिखो(regmap, PLL_ALPHA_VAL(pll), config->alpha);
	regmap_ग_लिखो(regmap, PLL_CONFIG_CTL(pll), config->config_ctl_val);

	अगर (pll_has_64bit_config(pll))
		regmap_ग_लिखो(regmap, PLL_CONFIG_CTL_U(pll),
			     config->config_ctl_hi_val);

	अगर (pll_alpha_width(pll) > 32)
		regmap_ग_लिखो(regmap, PLL_ALPHA_VAL_U(pll), config->alpha_hi);

	val = config->मुख्य_output_mask;
	val |= config->aux_output_mask;
	val |= config->aux2_output_mask;
	val |= config->early_output_mask;
	val |= config->pre_भाग_val;
	val |= config->post_भाग_val;
	val |= config->vco_val;
	val |= config->alpha_en_mask;
	val |= config->alpha_mode_mask;

	mask = config->मुख्य_output_mask;
	mask |= config->aux_output_mask;
	mask |= config->aux2_output_mask;
	mask |= config->early_output_mask;
	mask |= config->pre_भाग_mask;
	mask |= config->post_भाग_mask;
	mask |= config->vco_mask;

	regmap_update_bits(regmap, PLL_USER_CTL(pll), mask, val);

	अगर (pll->flags & SUPPORTS_FSM_MODE)
		qcom_pll_set_fsm_mode(regmap, PLL_MODE(pll), 6, 0);
पूर्ण
EXPORT_SYMBOL_GPL(clk_alpha_pll_configure);

अटल पूर्णांक clk_alpha_pll_hwfsm_enable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	val |= PLL_FSM_ENA;

	अगर (pll->flags & SUPPORTS_OFFLINE_REQ)
		val &= ~PLL_OFFLINE_REQ;

	ret = regmap_ग_लिखो(pll->clkr.regmap, PLL_MODE(pll), val);
	अगर (ret)
		वापस ret;

	/* Make sure enable request goes through beक्रमe रुकोing क्रम update */
	mb();

	वापस रुको_क्रम_pll_enable_active(pll);
पूर्ण

अटल व्योम clk_alpha_pll_hwfsm_disable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस;

	अगर (pll->flags & SUPPORTS_OFFLINE_REQ) अणु
		ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll),
					 PLL_OFFLINE_REQ, PLL_OFFLINE_REQ);
		अगर (ret)
			वापस;

		ret = रुको_क्रम_pll_offline(pll);
		अगर (ret)
			वापस;
	पूर्ण

	/* Disable hwfsm */
	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll),
				 PLL_FSM_ENA, 0);
	अगर (ret)
		वापस;

	रुको_क्रम_pll_disable(pll);
पूर्ण

अटल पूर्णांक pll_is_enabled(काष्ठा clk_hw *hw, u32 mask)
अणु
	पूर्णांक ret;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & mask);
पूर्ण

अटल पूर्णांक clk_alpha_pll_hwfsm_is_enabled(काष्ठा clk_hw *hw)
अणु
	वापस pll_is_enabled(hw, PLL_ACTIVE_FLAG);
पूर्ण

अटल पूर्णांक clk_alpha_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	वापस pll_is_enabled(hw, PLL_LOCK_DET);
पूर्ण

अटल पूर्णांक clk_alpha_pll_enable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val, mask;

	mask = PLL_OUTCTRL | PLL_RESET_N | PLL_BYPASSNL;
	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	/* If in FSM mode, just vote क्रम it */
	अगर (val & PLL_VOTE_FSM_ENA) अणु
		ret = clk_enable_regmap(hw);
		अगर (ret)
			वापस ret;
		वापस रुको_क्रम_pll_enable_active(pll);
	पूर्ण

	/* Skip अगर alपढ़ोy enabled */
	अगर ((val & mask) == mask)
		वापस 0;

	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll),
				 PLL_BYPASSNL, PLL_BYPASSNL);
	अगर (ret)
		वापस ret;

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-निश्चितing the reset.
	 */
	mb();
	udelay(5);

	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll),
				 PLL_RESET_N, PLL_RESET_N);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_pll_enable_lock(pll);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll),
				 PLL_OUTCTRL, PLL_OUTCTRL);

	/* Ensure that the ग_लिखो above goes through beक्रमe वापसing. */
	mb();
	वापस ret;
पूर्ण

अटल व्योम clk_alpha_pll_disable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val, mask;

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस;

	/* If in FSM mode, just unvote it */
	अगर (val & PLL_VOTE_FSM_ENA) अणु
		clk_disable_regmap(hw);
		वापस;
	पूर्ण

	mask = PLL_OUTCTRL;
	regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), mask, 0);

	/* Delay of 2 output घड़ी ticks required until output is disabled */
	mb();
	udelay(1);

	mask = PLL_RESET_N | PLL_BYPASSNL;
	regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), mask, 0);
पूर्ण

अटल अचिन्हित दीर्घ
alpha_pll_calc_rate(u64 prate, u32 l, u32 a, u32 alpha_width)
अणु
	वापस (prate * l) + ((prate * a) >> ALPHA_SHIFT(alpha_width));
पूर्ण

अटल अचिन्हित दीर्घ
alpha_pll_round_rate(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ prate, u32 *l, u64 *a,
		     u32 alpha_width)
अणु
	u64 reमुख्यder;
	u64 quotient;

	quotient = rate;
	reमुख्यder = करो_भाग(quotient, prate);
	*l = quotient;

	अगर (!reमुख्यder) अणु
		*a = 0;
		वापस rate;
	पूर्ण

	/* Upper ALPHA_BITWIDTH bits of Alpha */
	quotient = reमुख्यder << ALPHA_SHIFT(alpha_width);

	reमुख्यder = करो_भाग(quotient, prate);

	अगर (reमुख्यder)
		quotient++;

	*a = quotient;
	वापस alpha_pll_calc_rate(prate, *l, *a, alpha_width);
पूर्ण

अटल स्थिर काष्ठा pll_vco *
alpha_pll_find_vco(स्थिर काष्ठा clk_alpha_pll *pll, अचिन्हित दीर्घ rate)
अणु
	स्थिर काष्ठा pll_vco *v = pll->vco_table;
	स्थिर काष्ठा pll_vco *end = v + pll->num_vco;

	क्रम (; v < end; v++)
		अगर (rate >= v->min_freq && rate <= v->max_freq)
			वापस v;

	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ
clk_alpha_pll_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	u32 l, low, high, ctl;
	u64 a = 0, prate = parent_rate;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 alpha_width = pll_alpha_width(pll);

	regmap_पढ़ो(pll->clkr.regmap, PLL_L_VAL(pll), &l);

	regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &ctl);
	अगर (ctl & PLL_ALPHA_EN) अणु
		regmap_पढ़ो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), &low);
		अगर (alpha_width > 32) अणु
			regmap_पढ़ो(pll->clkr.regmap, PLL_ALPHA_VAL_U(pll),
				    &high);
			a = (u64)high << 32 | low;
		पूर्ण अन्यथा अणु
			a = low & GENMASK(alpha_width - 1, 0);
		पूर्ण

		अगर (alpha_width > ALPHA_BITWIDTH)
			a >>= alpha_width - ALPHA_BITWIDTH;
	पूर्ण

	वापस alpha_pll_calc_rate(prate, l, a, alpha_width);
पूर्ण


अटल पूर्णांक __clk_alpha_pll_update_latch(काष्ठा clk_alpha_pll *pll)
अणु
	पूर्णांक ret;
	u32 mode;

	regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &mode);

	/* Latch the input to the PLL */
	regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), PLL_UPDATE,
			   PLL_UPDATE);

	/* Wait क्रम 2 reference cycle beक्रमe checking ACK bit */
	udelay(1);

	/*
	 * PLL will latch the new L, Alpha and freq control word.
	 * PLL will respond by raising PLL_ACK_LATCH output when new programming
	 * has been latched in and PLL is being updated. When
	 * UPDATE_LOGIC_BYPASS bit is not set, PLL_UPDATE will be cleared
	 * स्वतःmatically by hardware when PLL_ACK_LATCH is निश्चितed by PLL.
	 */
	अगर (mode & PLL_UPDATE_BYPASS) अणु
		ret = रुको_क्रम_pll_update_ack_set(pll);
		अगर (ret)
			वापस ret;

		regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), PLL_UPDATE, 0);
	पूर्ण अन्यथा अणु
		ret = रुको_क्रम_pll_update(pll);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = रुको_क्रम_pll_update_ack_clear(pll);
	अगर (ret)
		वापस ret;

	/* Wait क्रम PLL output to stabilize */
	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक clk_alpha_pll_update_latch(काष्ठा clk_alpha_pll *pll,
				      पूर्णांक (*is_enabled)(काष्ठा clk_hw *))
अणु
	अगर (!is_enabled(&pll->clkr.hw) ||
	    !(pll->flags & SUPPORTS_DYNAMIC_UPDATE))
		वापस 0;

	वापस __clk_alpha_pll_update_latch(pll);
पूर्ण

अटल पूर्णांक __clk_alpha_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ prate,
				    पूर्णांक (*is_enabled)(काष्ठा clk_hw *))
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	स्थिर काष्ठा pll_vco *vco;
	u32 l, alpha_width = pll_alpha_width(pll);
	u64 a;

	rate = alpha_pll_round_rate(rate, prate, &l, &a, alpha_width);
	vco = alpha_pll_find_vco(pll, rate);
	अगर (pll->vco_table && !vco) अणु
		pr_err("%s: alpha pll not in a valid vco range\n",
		       clk_hw_get_name(hw));
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(pll->clkr.regmap, PLL_L_VAL(pll), l);

	अगर (alpha_width > ALPHA_BITWIDTH)
		a <<= alpha_width - ALPHA_BITWIDTH;

	अगर (alpha_width > 32)
		regmap_ग_लिखो(pll->clkr.regmap, PLL_ALPHA_VAL_U(pll), a >> 32);

	regmap_ग_लिखो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), a);

	अगर (vco) अणु
		regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				   PLL_VCO_MASK << PLL_VCO_SHIFT,
				   vco->val << PLL_VCO_SHIFT);
	पूर्ण

	regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
			   PLL_ALPHA_EN, PLL_ALPHA_EN);

	वापस clk_alpha_pll_update_latch(pll, is_enabled);
पूर्ण

अटल पूर्णांक clk_alpha_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ prate)
अणु
	वापस __clk_alpha_pll_set_rate(hw, rate, prate,
					clk_alpha_pll_is_enabled);
पूर्ण

अटल पूर्णांक clk_alpha_pll_hwfsm_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ prate)
अणु
	वापस __clk_alpha_pll_set_rate(hw, rate, prate,
					clk_alpha_pll_hwfsm_is_enabled);
पूर्ण

अटल दीर्घ clk_alpha_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, alpha_width = pll_alpha_width(pll);
	u64 a;
	अचिन्हित दीर्घ min_freq, max_freq;

	rate = alpha_pll_round_rate(rate, *prate, &l, &a, alpha_width);
	अगर (!pll->vco_table || alpha_pll_find_vco(pll, rate))
		वापस rate;

	min_freq = pll->vco_table[0].min_freq;
	max_freq = pll->vco_table[pll->num_vco - 1].max_freq;

	वापस clamp(rate, min_freq, max_freq);
पूर्ण

अटल अचिन्हित दीर्घ
alpha_huayra_pll_calc_rate(u64 prate, u32 l, u32 a)
अणु
	/*
	 * a contains 16 bit alpha_val in twoै s complement number in the range
	 * of [-0.5, 0.5).
	 */
	अगर (a >= BIT(PLL_HUAYRA_ALPHA_WIDTH - 1))
		l -= 1;

	वापस (prate * l) + (prate * a >> PLL_HUAYRA_ALPHA_WIDTH);
पूर्ण

अटल अचिन्हित दीर्घ
alpha_huayra_pll_round_rate(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ prate,
			    u32 *l, u32 *a)
अणु
	u64 reमुख्यder;
	u64 quotient;

	quotient = rate;
	reमुख्यder = करो_भाग(quotient, prate);
	*l = quotient;

	अगर (!reमुख्यder) अणु
		*a = 0;
		वापस rate;
	पूर्ण

	quotient = reमुख्यder << PLL_HUAYRA_ALPHA_WIDTH;
	reमुख्यder = करो_भाग(quotient, prate);

	अगर (reमुख्यder)
		quotient++;

	/*
	 * alpha_val should be in twoै s complement number in the range
	 * of [-0.5, 0.5) so अगर quotient >= 0.5 then increment the l value
	 * since alpha value will be subtracted in this हाल.
	 */
	अगर (quotient >= BIT(PLL_HUAYRA_ALPHA_WIDTH - 1))
		*l += 1;

	*a = quotient;
	वापस alpha_huayra_pll_calc_rate(prate, *l, *a);
पूर्ण

अटल अचिन्हित दीर्घ
alpha_pll_huayra_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	u64 rate = parent_rate, पंचांगp;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, alpha = 0, ctl, alpha_m, alpha_n;

	regmap_पढ़ो(pll->clkr.regmap, PLL_L_VAL(pll), &l);
	regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &ctl);

	अगर (ctl & PLL_ALPHA_EN) अणु
		regmap_पढ़ो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), &alpha);
		/*
		 * Depending upon alpha_mode, it can be treated as M/N value or
		 * as a twoै s complement number. When alpha_mode=1,
		 * pll_alpha_val<15:8>=M and pll_apla_val<7:0>=N
		 *
		 *		Fout=FIN*(L+(M/N))
		 *
		 * M is a चिन्हित number (-128 to 127) and N is अचिन्हित
		 * (0 to 255). M/N has to be within +/-0.5.
		 *
		 * When alpha_mode=0, it is a twoै s complement number in the
		 * range [-0.5, 0.5).
		 *
		 *		Fout=FIN*(L+(alpha_val)/2^16)
		 *
		 * where alpha_val is twoै s complement number.
		 */
		अगर (!(ctl & PLL_ALPHA_MODE))
			वापस alpha_huayra_pll_calc_rate(rate, l, alpha);

		alpha_m = alpha >> PLL_HUAYRA_M_SHIFT & PLL_HUAYRA_M_MASK;
		alpha_n = alpha >> PLL_HUAYRA_N_SHIFT & PLL_HUAYRA_N_MASK;

		rate *= l;
		पंचांगp = parent_rate;
		अगर (alpha_m >= BIT(PLL_HUAYRA_M_WIDTH - 1)) अणु
			alpha_m = BIT(PLL_HUAYRA_M_WIDTH) - alpha_m;
			पंचांगp *= alpha_m;
			करो_भाग(पंचांगp, alpha_n);
			rate -= पंचांगp;
		पूर्ण अन्यथा अणु
			पंचांगp *= alpha_m;
			करो_भाग(पंचांगp, alpha_n);
			rate += पंचांगp;
		पूर्ण

		वापस rate;
	पूर्ण

	वापस alpha_huayra_pll_calc_rate(rate, l, alpha);
पूर्ण

अटल पूर्णांक alpha_pll_huayra_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, a, ctl, cur_alpha = 0;

	rate = alpha_huayra_pll_round_rate(rate, prate, &l, &a);

	regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &ctl);

	अगर (ctl & PLL_ALPHA_EN)
		regmap_पढ़ो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), &cur_alpha);

	/*
	 * Huayra PLL supports PLL dynamic programming. User can change L_VAL,
	 * without having to go through the घातer on sequence.
	 */
	अगर (clk_alpha_pll_is_enabled(hw)) अणु
		अगर (cur_alpha != a) अणु
			pr_err("%s: clock needs to be gated\n",
			       clk_hw_get_name(hw));
			वापस -EBUSY;
		पूर्ण

		regmap_ग_लिखो(pll->clkr.regmap, PLL_L_VAL(pll), l);
		/* Ensure that the ग_लिखो above goes to detect L val change. */
		mb();
		वापस रुको_क्रम_pll_enable_lock(pll);
	पूर्ण

	regmap_ग_लिखो(pll->clkr.regmap, PLL_L_VAL(pll), l);
	regmap_ग_लिखो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), a);

	अगर (a == 0)
		regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				   PLL_ALPHA_EN, 0x0);
	अन्यथा
		regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				   PLL_ALPHA_EN | PLL_ALPHA_MODE, PLL_ALPHA_EN);

	वापस 0;
पूर्ण

अटल दीर्घ alpha_pll_huayra_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *prate)
अणु
	u32 l, a;

	वापस alpha_huayra_pll_round_rate(rate, *prate, &l, &a);
पूर्ण

अटल पूर्णांक trion_pll_is_enabled(काष्ठा clk_alpha_pll *pll,
				काष्ठा regmap *regmap)
अणु
	u32 mode_val, opmode_val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, PLL_MODE(pll), &mode_val);
	ret |= regmap_पढ़ो(regmap, PLL_OPMODE(pll), &opmode_val);
	अगर (ret)
		वापस 0;

	वापस ((opmode_val & PLL_RUN) && (mode_val & PLL_OUTCTRL));
पूर्ण

अटल पूर्णांक clk_trion_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);

	वापस trion_pll_is_enabled(pll, pll->clkr.regmap);
पूर्ण

अटल पूर्णांक clk_trion_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	काष्ठा regmap *regmap = pll->clkr.regmap;
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	/* If in FSM mode, just vote क्रम it */
	अगर (val & PLL_VOTE_FSM_ENA) अणु
		ret = clk_enable_regmap(hw);
		अगर (ret)
			वापस ret;
		वापस रुको_क्रम_pll_enable_active(pll);
	पूर्ण

	/* Set operation mode to RUN */
	regmap_ग_लिखो(regmap, PLL_OPMODE(pll), PLL_RUN);

	ret = रुको_क्रम_pll_enable_lock(pll);
	अगर (ret)
		वापस ret;

	/* Enable the PLL outमाला_दो */
	ret = regmap_update_bits(regmap, PLL_USER_CTL(pll),
				 PLL_OUT_MASK, PLL_OUT_MASK);
	अगर (ret)
		वापस ret;

	/* Enable the global PLL outमाला_दो */
	वापस regmap_update_bits(regmap, PLL_MODE(pll),
				 PLL_OUTCTRL, PLL_OUTCTRL);
पूर्ण

अटल व्योम clk_trion_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	काष्ठा regmap *regmap = pll->clkr.regmap;
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस;

	/* If in FSM mode, just unvote it */
	अगर (val & PLL_VOTE_FSM_ENA) अणु
		clk_disable_regmap(hw);
		वापस;
	पूर्ण

	/* Disable the global PLL output */
	ret = regmap_update_bits(regmap, PLL_MODE(pll), PLL_OUTCTRL, 0);
	अगर (ret)
		वापस;

	/* Disable the PLL outमाला_दो */
	ret = regmap_update_bits(regmap, PLL_USER_CTL(pll),
				 PLL_OUT_MASK, 0);
	अगर (ret)
		वापस;

	/* Place the PLL mode in STANDBY */
	regmap_ग_लिखो(regmap, PLL_OPMODE(pll), PLL_STANDBY);
	regmap_update_bits(regmap, PLL_MODE(pll), PLL_RESET_N, PLL_RESET_N);
पूर्ण

अटल अचिन्हित दीर्घ
clk_trion_pll_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, frac, alpha_width = pll_alpha_width(pll);

	regmap_पढ़ो(pll->clkr.regmap, PLL_L_VAL(pll), &l);
	regmap_पढ़ो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), &frac);

	वापस alpha_pll_calc_rate(parent_rate, l, frac, alpha_width);
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_ops = अणु
	.enable = clk_alpha_pll_enable,
	.disable = clk_alpha_pll_disable,
	.is_enabled = clk_alpha_pll_is_enabled,
	.recalc_rate = clk_alpha_pll_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_fixed_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_ops = अणु
	.enable = clk_alpha_pll_enable,
	.disable = clk_alpha_pll_disable,
	.is_enabled = clk_alpha_pll_is_enabled,
	.recalc_rate = clk_alpha_pll_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
	.set_rate = clk_alpha_pll_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_huayra_ops = अणु
	.enable = clk_alpha_pll_enable,
	.disable = clk_alpha_pll_disable,
	.is_enabled = clk_alpha_pll_is_enabled,
	.recalc_rate = alpha_pll_huayra_recalc_rate,
	.round_rate = alpha_pll_huayra_round_rate,
	.set_rate = alpha_pll_huayra_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_huayra_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_hwfsm_ops = अणु
	.enable = clk_alpha_pll_hwfsm_enable,
	.disable = clk_alpha_pll_hwfsm_disable,
	.is_enabled = clk_alpha_pll_hwfsm_is_enabled,
	.recalc_rate = clk_alpha_pll_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
	.set_rate = clk_alpha_pll_hwfsm_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_hwfsm_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_trion_ops = अणु
	.enable = clk_trion_pll_enable,
	.disable = clk_trion_pll_disable,
	.is_enabled = clk_trion_pll_is_enabled,
	.recalc_rate = clk_trion_pll_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_fixed_trion_ops);

अटल अचिन्हित दीर्घ
clk_alpha_pll_postभाग_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	u32 ctl;

	regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &ctl);

	ctl >>= PLL_POST_DIV_SHIFT;
	ctl &= PLL_POST_DIV_MASK(pll);

	वापस parent_rate >> fls(ctl);
पूर्ण

अटल स्थिर काष्ठा clk_भाग_प्रकारable clk_alpha_भाग_प्रकारable[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु 0x3, 4 पूर्ण,
	अणु 0x7, 8 पूर्ण,
	अणु 0xf, 16 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा clk_भाग_प्रकारable clk_alpha_2bit_भाग_प्रकारable[] = अणु
	अणु 0x0, 1 पूर्ण,
	अणु 0x1, 2 पूर्ण,
	अणु 0x3, 4 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल दीर्घ
clk_alpha_pll_postभाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	स्थिर काष्ठा clk_भाग_प्रकारable *table;

	अगर (pll->width == 2)
		table = clk_alpha_2bit_भाग_प्रकारable;
	अन्यथा
		table = clk_alpha_भाग_प्रकारable;

	वापस भागider_round_rate(hw, rate, prate, table,
				  pll->width, CLK_DIVIDER_POWER_OF_TWO);
पूर्ण

अटल दीर्घ
clk_alpha_pll_postभाग_round_ro_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	u32 ctl, भाग;

	regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &ctl);

	ctl >>= PLL_POST_DIV_SHIFT;
	ctl &= BIT(pll->width) - 1;
	भाग = 1 << fls(ctl);

	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)
		*prate = clk_hw_round_rate(clk_hw_get_parent(hw), भाग * rate);

	वापस DIV_ROUND_UP_ULL((u64)*prate, भाग);
पूर्ण

अटल पूर्णांक clk_alpha_pll_postभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	पूर्णांक भाग;

	/* 16 -> 0xf, 8 -> 0x7, 4 -> 0x3, 2 -> 0x1, 1 -> 0x0 */
	भाग = DIV_ROUND_UP_ULL(parent_rate, rate) - 1;

	वापस regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				  PLL_POST_DIV_MASK(pll) << PLL_POST_DIV_SHIFT,
				  भाग << PLL_POST_DIV_SHIFT);
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_ops = अणु
	.recalc_rate = clk_alpha_pll_postभाग_recalc_rate,
	.round_rate = clk_alpha_pll_postभाग_round_rate,
	.set_rate = clk_alpha_pll_postभाग_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_postभाग_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_ro_ops = अणु
	.round_rate = clk_alpha_pll_postभाग_round_ro_rate,
	.recalc_rate = clk_alpha_pll_postभाग_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_postभाग_ro_ops);

व्योम clk_fabia_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
			     स्थिर काष्ठा alpha_pll_config *config)
अणु
	u32 val, mask;

	clk_alpha_pll_ग_लिखो_config(regmap, PLL_L_VAL(pll), config->l);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_FRAC(pll), config->alpha);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_CONFIG_CTL(pll),
						config->config_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_CONFIG_CTL_U(pll),
						config->config_ctl_hi_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_USER_CTL(pll),
						config->user_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_USER_CTL_U(pll),
						config->user_ctl_hi_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_TEST_CTL(pll),
						config->test_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_TEST_CTL_U(pll),
						config->test_ctl_hi_val);

	अगर (config->post_भाग_mask) अणु
		mask = config->post_भाग_mask;
		val = config->post_भाग_val;
		regmap_update_bits(regmap, PLL_USER_CTL(pll), mask, val);
	पूर्ण

	regmap_update_bits(regmap, PLL_MODE(pll), PLL_UPDATE_BYPASS,
							PLL_UPDATE_BYPASS);

	regmap_update_bits(regmap, PLL_MODE(pll), PLL_RESET_N, PLL_RESET_N);
पूर्ण
EXPORT_SYMBOL_GPL(clk_fabia_pll_configure);

अटल पूर्णांक alpha_pll_fabia_enable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val, opmode_val;
	काष्ठा regmap *regmap = pll->clkr.regmap;

	ret = regmap_पढ़ो(regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	/* If in FSM mode, just vote क्रम it */
	अगर (val & PLL_VOTE_FSM_ENA) अणु
		ret = clk_enable_regmap(hw);
		अगर (ret)
			वापस ret;
		वापस रुको_क्रम_pll_enable_active(pll);
	पूर्ण

	ret = regmap_पढ़ो(regmap, PLL_OPMODE(pll), &opmode_val);
	अगर (ret)
		वापस ret;

	/* Skip If PLL is alपढ़ोy running */
	अगर ((opmode_val & PLL_RUN) && (val & PLL_OUTCTRL))
		वापस 0;

	ret = regmap_update_bits(regmap, PLL_MODE(pll), PLL_OUTCTRL, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, PLL_OPMODE(pll), PLL_STANDBY);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(regmap, PLL_MODE(pll), PLL_RESET_N,
				 PLL_RESET_N);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, PLL_OPMODE(pll), PLL_RUN);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_pll_enable_lock(pll);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(regmap, PLL_USER_CTL(pll),
				 PLL_OUT_MASK, PLL_OUT_MASK);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(regmap, PLL_MODE(pll), PLL_OUTCTRL,
				 PLL_OUTCTRL);
पूर्ण

अटल व्योम alpha_pll_fabia_disable(काष्ठा clk_hw *hw)
अणु
	पूर्णांक ret;
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;
	काष्ठा regmap *regmap = pll->clkr.regmap;

	ret = regmap_पढ़ो(regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस;

	/* If in FSM mode, just unvote it */
	अगर (val & PLL_FSM_ENA) अणु
		clk_disable_regmap(hw);
		वापस;
	पूर्ण

	ret = regmap_update_bits(regmap, PLL_MODE(pll), PLL_OUTCTRL, 0);
	अगर (ret)
		वापस;

	/* Disable मुख्य outमाला_दो */
	ret = regmap_update_bits(regmap, PLL_USER_CTL(pll), PLL_OUT_MASK, 0);
	अगर (ret)
		वापस;

	/* Place the PLL in STANDBY */
	regmap_ग_लिखो(regmap, PLL_OPMODE(pll), PLL_STANDBY);
पूर्ण

अटल अचिन्हित दीर्घ alpha_pll_fabia_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, frac, alpha_width = pll_alpha_width(pll);

	regmap_पढ़ो(pll->clkr.regmap, PLL_L_VAL(pll), &l);
	regmap_पढ़ो(pll->clkr.regmap, PLL_FRAC(pll), &frac);

	वापस alpha_pll_calc_rate(parent_rate, l, frac, alpha_width);
पूर्ण

/*
 * Due to limited number of bits क्रम fractional rate programming, the
 * rounded up rate could be marginally higher than the requested rate.
 */
अटल पूर्णांक alpha_pll_check_rate_margin(काष्ठा clk_hw *hw,
			अचिन्हित दीर्घ rrate, अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ rate_margin = rate + PLL_RATE_MARGIN;

	अगर (rrate > rate_margin || rrate < rate) अणु
		pr_err("%s: Rounded rate %lu not within range [%lu, %lu)\n",
		       clk_hw_get_name(hw), rrate, rate, rate_margin);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alpha_pll_fabia_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
						अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, alpha_width = pll_alpha_width(pll);
	अचिन्हित दीर्घ rrate;
	पूर्णांक ret;
	u64 a;

	rrate = alpha_pll_round_rate(rate, prate, &l, &a, alpha_width);

	ret = alpha_pll_check_rate_margin(hw, rrate, rate);
	अगर (ret < 0)
		वापस ret;

	regmap_ग_लिखो(pll->clkr.regmap, PLL_L_VAL(pll), l);
	regmap_ग_लिखो(pll->clkr.regmap, PLL_FRAC(pll), a);

	वापस __clk_alpha_pll_update_latch(pll);
पूर्ण

अटल पूर्णांक alpha_pll_fabia_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	स्थिर काष्ठा pll_vco *vco;
	काष्ठा clk_hw *parent_hw;
	अचिन्हित दीर्घ cal_freq, rrate;
	u32 cal_l, val, alpha_width = pll_alpha_width(pll);
	स्थिर अक्षर *name = clk_hw_get_name(hw);
	u64 a;
	पूर्णांक ret;

	/* Check अगर calibration needs to be करोne i.e. PLL is in reset */
	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	/* Return early अगर calibration is not needed. */
	अगर (val & PLL_RESET_N)
		वापस 0;

	vco = alpha_pll_find_vco(pll, clk_hw_get_rate(hw));
	अगर (!vco) अणु
		pr_err("%s: alpha pll not in a valid vco range\n", name);
		वापस -EINVAL;
	पूर्ण

	cal_freq = DIV_ROUND_CLOSEST((pll->vco_table[0].min_freq +
				pll->vco_table[0].max_freq) * 54, 100);

	parent_hw = clk_hw_get_parent(hw);
	अगर (!parent_hw)
		वापस -EINVAL;

	rrate = alpha_pll_round_rate(cal_freq, clk_hw_get_rate(parent_hw),
					&cal_l, &a, alpha_width);

	ret = alpha_pll_check_rate_margin(hw, rrate, cal_freq);
	अगर (ret < 0)
		वापस ret;

	/* Setup PLL क्रम calibration frequency */
	regmap_ग_लिखो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), cal_l);

	/* Bringup the PLL at calibration frequency */
	ret = clk_alpha_pll_enable(hw);
	अगर (ret) अणु
		pr_err("%s: alpha pll calibration failed\n", name);
		वापस ret;
	पूर्ण

	clk_alpha_pll_disable(hw);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_fabia_ops = अणु
	.prepare = alpha_pll_fabia_prepare,
	.enable = alpha_pll_fabia_enable,
	.disable = alpha_pll_fabia_disable,
	.is_enabled = clk_alpha_pll_is_enabled,
	.set_rate = alpha_pll_fabia_set_rate,
	.recalc_rate = alpha_pll_fabia_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_fabia_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_fabia_ops = अणु
	.enable = alpha_pll_fabia_enable,
	.disable = alpha_pll_fabia_disable,
	.is_enabled = clk_alpha_pll_is_enabled,
	.recalc_rate = alpha_pll_fabia_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_fixed_fabia_ops);

अटल अचिन्हित दीर्घ clk_alpha_pll_postभाग_fabia_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	u32 i, भाग = 1, val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &val);
	अगर (ret)
		वापस ret;

	val >>= pll->post_भाग_shअगरt;
	val &= BIT(pll->width) - 1;

	क्रम (i = 0; i < pll->num_post_भाग; i++) अणु
		अगर (pll->post_भाग_प्रकारable[i].val == val) अणु
			भाग = pll->post_भाग_प्रकारable[i].भाग;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (parent_rate / भाग);
पूर्ण

अटल अचिन्हित दीर्घ
clk_trion_pll_postभाग_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	काष्ठा regmap *regmap = pll->clkr.regmap;
	u32 i, भाग = 1, val;

	regmap_पढ़ो(regmap, PLL_USER_CTL(pll), &val);

	val >>= pll->post_भाग_shअगरt;
	val &= PLL_POST_DIV_MASK(pll);

	क्रम (i = 0; i < pll->num_post_भाग; i++) अणु
		अगर (pll->post_भाग_प्रकारable[i].val == val) अणु
			भाग = pll->post_भाग_प्रकारable[i].भाग;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (parent_rate / भाग);
पूर्ण

अटल दीर्घ
clk_trion_pll_postभाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);

	वापस भागider_round_rate(hw, rate, prate, pll->post_भाग_प्रकारable,
				  pll->width, CLK_DIVIDER_ROUND_CLOSEST);
पूर्ण;

अटल पूर्णांक
clk_trion_pll_postभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	काष्ठा regmap *regmap = pll->clkr.regmap;
	पूर्णांक i, val = 0, भाग;

	भाग = DIV_ROUND_UP_ULL(parent_rate, rate);
	क्रम (i = 0; i < pll->num_post_भाग; i++) अणु
		अगर (pll->post_भाग_प्रकारable[i].भाग == भाग) अणु
			val = pll->post_भाग_प्रकारable[i].val;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस regmap_update_bits(regmap, PLL_USER_CTL(pll),
				  PLL_POST_DIV_MASK(pll) << PLL_POST_DIV_SHIFT,
				  val << PLL_POST_DIV_SHIFT);
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_प्रकारrion_ops = अणु
	.recalc_rate = clk_trion_pll_postभाग_recalc_rate,
	.round_rate = clk_trion_pll_postभाग_round_rate,
	.set_rate = clk_trion_pll_postभाग_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_postभाग_प्रकारrion_ops);

अटल दीर्घ clk_alpha_pll_postभाग_fabia_round_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);

	वापस भागider_round_rate(hw, rate, prate, pll->post_भाग_प्रकारable,
				pll->width, CLK_DIVIDER_ROUND_CLOSEST);
पूर्ण

अटल पूर्णांक clk_alpha_pll_postभाग_fabia_set_rate(काष्ठा clk_hw *hw,
				अचिन्हित दीर्घ rate, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	पूर्णांक i, val = 0, भाग, ret;

	/*
	 * If the PLL is in FSM mode, then treat set_rate callback as a
	 * no-operation.
	 */
	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (ret)
		वापस ret;

	अगर (val & PLL_VOTE_FSM_ENA)
		वापस 0;

	भाग = DIV_ROUND_UP_ULL(parent_rate, rate);
	क्रम (i = 0; i < pll->num_post_भाग; i++) अणु
		अगर (pll->post_भाग_प्रकारable[i].भाग == भाग) अणु
			val = pll->post_भाग_प्रकारable[i].val;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				(BIT(pll->width) - 1) << pll->post_भाग_shअगरt,
				val << pll->post_भाग_shअगरt);
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_fabia_ops = अणु
	.recalc_rate = clk_alpha_pll_postभाग_fabia_recalc_rate,
	.round_rate = clk_alpha_pll_postभाग_fabia_round_rate,
	.set_rate = clk_alpha_pll_postभाग_fabia_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_postभाग_fabia_ops);

/**
 * clk_lucid_pll_configure - configure the lucid pll
 *
 * @pll: clk alpha pll
 * @regmap: रेजिस्टर map
 * @config: configuration to apply क्रम pll
 */
व्योम clk_trion_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
			     स्थिर काष्ठा alpha_pll_config *config)
अणु
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_L_VAL(pll), config->l);
	regmap_ग_लिखो(regmap, PLL_CAL_L_VAL(pll), TRION_PLL_CAL_VAL);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_ALPHA_VAL(pll), config->alpha);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_CONFIG_CTL(pll),
				     config->config_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_CONFIG_CTL_U(pll),
				     config->config_ctl_hi_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_CONFIG_CTL_U1(pll),
				     config->config_ctl_hi1_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_USER_CTL(pll),
					config->user_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_USER_CTL_U(pll),
					config->user_ctl_hi_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_USER_CTL_U1(pll),
					config->user_ctl_hi1_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_TEST_CTL(pll),
					config->test_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_TEST_CTL_U(pll),
					config->test_ctl_hi_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_TEST_CTL_U1(pll),
					config->test_ctl_hi1_val);

	regmap_update_bits(regmap, PLL_MODE(pll), PLL_UPDATE_BYPASS,
			   PLL_UPDATE_BYPASS);

	/* Disable PLL output */
	regmap_update_bits(regmap, PLL_MODE(pll),  PLL_OUTCTRL, 0);

	/* Set operation mode to OFF */
	regmap_ग_लिखो(regmap, PLL_OPMODE(pll), PLL_STANDBY);

	/* Place the PLL in STANDBY mode */
	regmap_update_bits(regmap, PLL_MODE(pll), PLL_RESET_N, PLL_RESET_N);
पूर्ण
EXPORT_SYMBOL_GPL(clk_trion_pll_configure);

/*
 * The TRION PLL requires a घातer-on self-calibration which happens when the
 * PLL comes out of reset. Calibrate in हाल it is not completed.
 */
अटल पूर्णांक __alpha_pll_trion_prepare(काष्ठा clk_hw *hw, u32 pcal_करोne)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;
	पूर्णांक ret;

	/* Return early अगर calibration is not needed. */
	regmap_पढ़ो(pll->clkr.regmap, PLL_STATUS(pll), &val);
	अगर (val & pcal_करोne)
		वापस 0;

	/* On/off to calibrate */
	ret = clk_trion_pll_enable(hw);
	अगर (!ret)
		clk_trion_pll_disable(hw);

	वापस ret;
पूर्ण

अटल पूर्णांक alpha_pll_trion_prepare(काष्ठा clk_hw *hw)
अणु
	वापस __alpha_pll_trion_prepare(hw, TRION_PCAL_DONE);
पूर्ण

अटल पूर्णांक alpha_pll_lucid_prepare(काष्ठा clk_hw *hw)
अणु
	वापस __alpha_pll_trion_prepare(hw, LUCID_PCAL_DONE);
पूर्ण

अटल पूर्णांक __alpha_pll_trion_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ prate, u32 latch_bit, u32 latch_ack)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	अचिन्हित दीर्घ rrate;
	u32 val, l, alpha_width = pll_alpha_width(pll);
	u64 a;
	पूर्णांक ret;

	rrate = alpha_pll_round_rate(rate, prate, &l, &a, alpha_width);

	ret = alpha_pll_check_rate_margin(hw, rrate, rate);
	अगर (ret < 0)
		वापस ret;

	regmap_ग_लिखो(pll->clkr.regmap, PLL_L_VAL(pll), l);
	regmap_ग_लिखो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), a);

	/* Latch the PLL input */
	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), latch_bit, latch_bit);
	अगर (ret)
		वापस ret;

	/* Wait क्रम 2 reference cycles beक्रमe checking the ACK bit. */
	udelay(1);
	regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (!(val & latch_ack)) अणु
		pr_err("Lucid PLL latch failed. Output may be unstable!\n");
		वापस -EINVAL;
	पूर्ण

	/* Return the latch input to 0 */
	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), latch_bit, 0);
	अगर (ret)
		वापस ret;

	अगर (clk_hw_is_enabled(hw)) अणु
		ret = रुको_क्रम_pll_enable_lock(pll);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Wait क्रम PLL output to stabilize */
	udelay(100);
	वापस 0;
पूर्ण

अटल पूर्णांक alpha_pll_trion_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ prate)
अणु
	वापस __alpha_pll_trion_set_rate(hw, rate, prate, PLL_UPDATE, ALPHA_PLL_ACK_LATCH);
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_trion_ops = अणु
	.prepare = alpha_pll_trion_prepare,
	.enable = clk_trion_pll_enable,
	.disable = clk_trion_pll_disable,
	.is_enabled = clk_trion_pll_is_enabled,
	.recalc_rate = clk_trion_pll_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
	.set_rate = alpha_pll_trion_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_trion_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_lucid_ops = अणु
	.prepare = alpha_pll_lucid_prepare,
	.enable = clk_trion_pll_enable,
	.disable = clk_trion_pll_disable,
	.is_enabled = clk_trion_pll_is_enabled,
	.recalc_rate = clk_trion_pll_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
	.set_rate = alpha_pll_trion_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_lucid_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_lucid_ops = अणु
	.recalc_rate = clk_alpha_pll_postभाग_fabia_recalc_rate,
	.round_rate = clk_alpha_pll_postभाग_fabia_round_rate,
	.set_rate = clk_alpha_pll_postभाग_fabia_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_postभाग_lucid_ops);

व्योम clk_agera_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
			स्थिर काष्ठा alpha_pll_config *config)
अणु
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_L_VAL(pll), config->l);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_ALPHA_VAL(pll), config->alpha);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_USER_CTL(pll),
							config->user_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_CONFIG_CTL(pll),
						config->config_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_CONFIG_CTL_U(pll),
						config->config_ctl_hi_val);
	clk_alpha_pll_ग_लिखो_config(regmap, PLL_TEST_CTL(pll),
						config->test_ctl_val);
	clk_alpha_pll_ग_लिखो_config(regmap,  PLL_TEST_CTL_U(pll),
						config->test_ctl_hi_val);
पूर्ण
EXPORT_SYMBOL_GPL(clk_agera_pll_configure);

अटल पूर्णांक clk_alpha_pll_agera_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
							अचिन्हित दीर्घ prate)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, alpha_width = pll_alpha_width(pll);
	पूर्णांक ret;
	अचिन्हित दीर्घ rrate;
	u64 a;

	rrate = alpha_pll_round_rate(rate, prate, &l, &a, alpha_width);
	ret = alpha_pll_check_rate_margin(hw, rrate, rate);
	अगर (ret < 0)
		वापस ret;

	/* change L_VAL without having to go through the घातer on sequence */
	regmap_ग_लिखो(pll->clkr.regmap, PLL_L_VAL(pll), l);
	regmap_ग_लिखो(pll->clkr.regmap, PLL_ALPHA_VAL(pll), a);

	अगर (clk_hw_is_enabled(hw))
		वापस रुको_क्रम_pll_enable_lock(pll);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_agera_ops = अणु
	.enable = clk_alpha_pll_enable,
	.disable = clk_alpha_pll_disable,
	.is_enabled = clk_alpha_pll_is_enabled,
	.recalc_rate = alpha_pll_fabia_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
	.set_rate = clk_alpha_pll_agera_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_alpha_pll_agera_ops);

अटल पूर्णांक alpha_pll_lucid_5lpe_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &val);
	अगर (ret)
		वापस ret;

	/* If in FSM mode, just vote क्रम it */
	अगर (val & LUCID_5LPE_ENABLE_VOTE_RUN) अणु
		ret = clk_enable_regmap(hw);
		अगर (ret)
			वापस ret;
		वापस रुको_क्रम_pll_enable_lock(pll);
	पूर्ण

	/* Check अगर PLL is alपढ़ोy enabled, वापस अगर enabled */
	ret = trion_pll_is_enabled(pll, pll->clkr.regmap);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), PLL_RESET_N, PLL_RESET_N);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(pll->clkr.regmap, PLL_OPMODE(pll), PLL_RUN);

	ret = रुको_क्रम_pll_enable_lock(pll);
	अगर (ret)
		वापस ret;

	/* Enable the PLL outमाला_दो */
	ret = regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll), PLL_OUT_MASK, PLL_OUT_MASK);
	अगर (ret)
		वापस ret;

	/* Enable the global PLL outमाला_दो */
	वापस regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), PLL_OUTCTRL, PLL_OUTCTRL);
पूर्ण

अटल व्योम alpha_pll_lucid_5lpe_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &val);
	अगर (ret)
		वापस;

	/* If in FSM mode, just unvote it */
	अगर (val & LUCID_5LPE_ENABLE_VOTE_RUN) अणु
		clk_disable_regmap(hw);
		वापस;
	पूर्ण

	/* Disable the global PLL output */
	ret = regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), PLL_OUTCTRL, 0);
	अगर (ret)
		वापस;

	/* Disable the PLL outमाला_दो */
	ret = regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll), PLL_OUT_MASK, 0);
	अगर (ret)
		वापस;

	/* Place the PLL mode in STANDBY */
	regmap_ग_लिखो(pll->clkr.regmap, PLL_OPMODE(pll), PLL_STANDBY);
पूर्ण

/*
 * The Lucid 5LPE PLL requires a घातer-on self-calibration which happens
 * when the PLL comes out of reset. Calibrate in हाल it is not completed.
 */
अटल पूर्णांक alpha_pll_lucid_5lpe_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	काष्ठा clk_hw *p;
	u32 val = 0;
	पूर्णांक ret;

	/* Return early अगर calibration is not needed. */
	regmap_पढ़ो(pll->clkr.regmap, PLL_MODE(pll), &val);
	अगर (val & LUCID_5LPE_PCAL_DONE)
		वापस 0;

	p = clk_hw_get_parent(hw);
	अगर (!p)
		वापस -EINVAL;

	ret = alpha_pll_lucid_5lpe_enable(hw);
	अगर (ret)
		वापस ret;

	alpha_pll_lucid_5lpe_disable(hw);

	वापस 0;
पूर्ण

अटल पूर्णांक alpha_pll_lucid_5lpe_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ prate)
अणु
	वापस __alpha_pll_trion_set_rate(hw, rate, prate,
					  LUCID_5LPE_PLL_LATCH_INPUT,
					  LUCID_5LPE_ALPHA_PLL_ACK_LATCH);
पूर्ण

अटल पूर्णांक clk_lucid_5lpe_pll_postभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_alpha_pll_postभाग *pll = to_clk_alpha_pll_postभाग(hw);
	पूर्णांक i, val = 0, भाग, ret;
	u32 mask;

	/*
	 * If the PLL is in FSM mode, then treat set_rate callback as a
	 * no-operation.
	 */
	ret = regmap_पढ़ो(pll->clkr.regmap, PLL_USER_CTL(pll), &val);
	अगर (ret)
		वापस ret;

	अगर (val & LUCID_5LPE_ENABLE_VOTE_RUN)
		वापस 0;

	भाग = DIV_ROUND_UP_ULL((u64)parent_rate, rate);
	क्रम (i = 0; i < pll->num_post_भाग; i++) अणु
		अगर (pll->post_भाग_प्रकारable[i].भाग == भाग) अणु
			val = pll->post_भाग_प्रकारable[i].val;
			अवरोध;
		पूर्ण
	पूर्ण

	mask = GENMASK(pll->width + pll->post_भाग_shअगरt - 1, pll->post_भाग_shअगरt);
	वापस regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				  mask, val << pll->post_भाग_shअगरt);
पूर्ण

स्थिर काष्ठा clk_ops clk_alpha_pll_lucid_5lpe_ops = अणु
	.prepare = alpha_pll_lucid_5lpe_prepare,
	.enable = alpha_pll_lucid_5lpe_enable,
	.disable = alpha_pll_lucid_5lpe_disable,
	.is_enabled = clk_trion_pll_is_enabled,
	.recalc_rate = clk_trion_pll_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
	.set_rate = alpha_pll_lucid_5lpe_set_rate,
पूर्ण;
EXPORT_SYMBOL(clk_alpha_pll_lucid_5lpe_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_lucid_5lpe_ops = अणु
	.enable = alpha_pll_lucid_5lpe_enable,
	.disable = alpha_pll_lucid_5lpe_disable,
	.is_enabled = clk_trion_pll_is_enabled,
	.recalc_rate = clk_trion_pll_recalc_rate,
	.round_rate = clk_alpha_pll_round_rate,
पूर्ण;
EXPORT_SYMBOL(clk_alpha_pll_fixed_lucid_5lpe_ops);

स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_lucid_5lpe_ops = अणु
	.recalc_rate = clk_alpha_pll_postभाग_fabia_recalc_rate,
	.round_rate = clk_alpha_pll_postभाग_fabia_round_rate,
	.set_rate = clk_lucid_5lpe_pll_postभाग_set_rate,
पूर्ण;
EXPORT_SYMBOL(clk_alpha_pll_postभाग_lucid_5lpe_ops);
