<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2015, 2018, The Linux Foundation. All rights reserved. */

#अगर_अघोषित __QCOM_CLK_ALPHA_PLL_H__
#घोषणा __QCOM_CLK_ALPHA_PLL_H__

#समावेश <linux/clk-provider.h>
#समावेश "clk-regmap.h"

/* Alpha PLL types */
क्रमागत अणु
	CLK_ALPHA_PLL_TYPE_DEFAULT,
	CLK_ALPHA_PLL_TYPE_HUAYRA,
	CLK_ALPHA_PLL_TYPE_BRAMMO,
	CLK_ALPHA_PLL_TYPE_FABIA,
	CLK_ALPHA_PLL_TYPE_TRION,
	CLK_ALPHA_PLL_TYPE_LUCID = CLK_ALPHA_PLL_TYPE_TRION,
	CLK_ALPHA_PLL_TYPE_AGERA,
	CLK_ALPHA_PLL_TYPE_MAX,
पूर्ण;

क्रमागत अणु
	PLL_OFF_L_VAL,
	PLL_OFF_CAL_L_VAL,
	PLL_OFF_ALPHA_VAL,
	PLL_OFF_ALPHA_VAL_U,
	PLL_OFF_USER_CTL,
	PLL_OFF_USER_CTL_U,
	PLL_OFF_USER_CTL_U1,
	PLL_OFF_CONFIG_CTL,
	PLL_OFF_CONFIG_CTL_U,
	PLL_OFF_CONFIG_CTL_U1,
	PLL_OFF_TEST_CTL,
	PLL_OFF_TEST_CTL_U,
	PLL_OFF_TEST_CTL_U1,
	PLL_OFF_STATUS,
	PLL_OFF_OPMODE,
	PLL_OFF_FRAC,
	PLL_OFF_CAL_VAL,
	PLL_OFF_MAX_REGS
पूर्ण;

बाह्य स्थिर u8 clk_alpha_pll_regs[CLK_ALPHA_PLL_TYPE_MAX][PLL_OFF_MAX_REGS];

काष्ठा pll_vco अणु
	अचिन्हित दीर्घ min_freq;
	अचिन्हित दीर्घ max_freq;
	u32 val;
पूर्ण;

#घोषणा VCO(a, b, c) अणु \
	.val = a,\
	.min_freq = b,\
	.max_freq = c,\
पूर्ण

/**
 * काष्ठा clk_alpha_pll - phase locked loop (PLL)
 * @offset: base address of रेजिस्टरs
 * @vco_table: array of VCO settings
 * @regs: alpha pll रेजिस्टर map (see @clk_alpha_pll_regs)
 * @clkr: regmap घड़ी handle
 */
काष्ठा clk_alpha_pll अणु
	u32 offset;
	स्थिर u8 *regs;

	स्थिर काष्ठा pll_vco *vco_table;
	माप_प्रकार num_vco;
#घोषणा SUPPORTS_OFFLINE_REQ	BIT(0)
#घोषणा SUPPORTS_FSM_MODE	BIT(2)
#घोषणा SUPPORTS_DYNAMIC_UPDATE	BIT(3)
	u8 flags;

	काष्ठा clk_regmap clkr;
पूर्ण;

/**
 * काष्ठा clk_alpha_pll_postभाग - phase locked loop (PLL) post-भागider
 * @offset: base address of रेजिस्टरs
 * @regs: alpha pll रेजिस्टर map (see @clk_alpha_pll_regs)
 * @width: width of post-भागider
 * @post_भाग_shअगरt: shअगरt to dअगरferentiate between odd & even post-भागider
 * @post_भाग_प्रकारable: table with PLL odd and even post-भागider settings
 * @num_post_भाग: Number of PLL post-भागider settings
 *
 * @clkr: regmap घड़ी handle
 */
काष्ठा clk_alpha_pll_postभाग अणु
	u32 offset;
	u8 width;
	स्थिर u8 *regs;

	काष्ठा clk_regmap clkr;
	पूर्णांक post_भाग_shअगरt;
	स्थिर काष्ठा clk_भाग_प्रकारable *post_भाग_प्रकारable;
	माप_प्रकार num_post_भाग;
पूर्ण;

काष्ठा alpha_pll_config अणु
	u32 l;
	u32 alpha;
	u32 alpha_hi;
	u32 config_ctl_val;
	u32 config_ctl_hi_val;
	u32 config_ctl_hi1_val;
	u32 user_ctl_val;
	u32 user_ctl_hi_val;
	u32 user_ctl_hi1_val;
	u32 test_ctl_val;
	u32 test_ctl_hi_val;
	u32 test_ctl_hi1_val;
	u32 मुख्य_output_mask;
	u32 aux_output_mask;
	u32 aux2_output_mask;
	u32 early_output_mask;
	u32 alpha_en_mask;
	u32 alpha_mode_mask;
	u32 pre_भाग_val;
	u32 pre_भाग_mask;
	u32 post_भाग_val;
	u32 post_भाग_mask;
	u32 vco_val;
	u32 vco_mask;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_hwfsm_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_huayra_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_ro_ops;

बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_fabia_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_fabia_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_fabia_ops;

बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_trion_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_trion_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_प्रकारrion_ops;

बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_lucid_ops;
#घोषणा clk_alpha_pll_fixed_lucid_ops clk_alpha_pll_fixed_trion_ops
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_lucid_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_agera_ops;

बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_lucid_5lpe_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_fixed_lucid_5lpe_ops;
बाह्य स्थिर काष्ठा clk_ops clk_alpha_pll_postभाग_lucid_5lpe_ops;

व्योम clk_alpha_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
			     स्थिर काष्ठा alpha_pll_config *config);
व्योम clk_fabia_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
				स्थिर काष्ठा alpha_pll_config *config);
व्योम clk_trion_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
			     स्थिर काष्ठा alpha_pll_config *config);
व्योम clk_agera_pll_configure(काष्ठा clk_alpha_pll *pll, काष्ठा regmap *regmap,
				स्थिर काष्ठा alpha_pll_config *config);
#घोषणा clk_lucid_pll_configure(pll, regmap, config) \
	clk_trion_pll_configure(pll, regmap, config)



#पूर्ण_अगर
