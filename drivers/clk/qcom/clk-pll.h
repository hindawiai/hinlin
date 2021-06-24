<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __QCOM_CLK_PLL_H__
#घोषणा __QCOM_CLK_PLL_H__

#समावेश <linux/clk-provider.h>
#समावेश "clk-regmap.h"

/**
 * काष्ठा pll_freq_tbl - PLL frequency table
 * @l: L value
 * @m: M value
 * @n: N value
 * @ibits: पूर्णांकernal values
 */
काष्ठा pll_freq_tbl अणु
	अचिन्हित दीर्घ freq;
	u16 l;
	u16 m;
	u16 n;
	u32 ibits;
पूर्ण;

/**
 * काष्ठा clk_pll - phase locked loop (PLL)
 * @l_reg: L रेजिस्टर
 * @m_reg: M रेजिस्टर
 * @n_reg: N रेजिस्टर
 * @config_reg: config रेजिस्टर
 * @mode_reg: mode रेजिस्टर
 * @status_reg: status रेजिस्टर
 * @status_bit: ANDed with @status_reg to determine अगर PLL is enabled
 * @freq_tbl: PLL frequency table
 * @hw: handle between common and hardware-specअगरic पूर्णांकerfaces
 */
काष्ठा clk_pll अणु
	u32	l_reg;
	u32	m_reg;
	u32	n_reg;
	u32	config_reg;
	u32	mode_reg;
	u32	status_reg;
	u8	status_bit;
	u8	post_भाग_width;
	u8	post_भाग_shअगरt;

	स्थिर काष्ठा pll_freq_tbl *freq_tbl;

	काष्ठा clk_regmap clkr;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_pll_ops;
बाह्य स्थिर काष्ठा clk_ops clk_pll_vote_ops;
बाह्य स्थिर काष्ठा clk_ops clk_pll_sr2_ops;

#घोषणा to_clk_pll(_hw) container_of(to_clk_regmap(_hw), काष्ठा clk_pll, clkr)

काष्ठा pll_config अणु
	u16 l;
	u32 m;
	u32 n;
	u32 vco_val;
	u32 vco_mask;
	u32 pre_भाग_val;
	u32 pre_भाग_mask;
	u32 post_भाग_val;
	u32 post_भाग_mask;
	u32 mn_ena_mask;
	u32 मुख्य_output_mask;
	u32 aux_output_mask;
पूर्ण;

व्योम clk_pll_configure_sr(काष्ठा clk_pll *pll, काष्ठा regmap *regmap,
		स्थिर काष्ठा pll_config *config, bool fsm_mode);
व्योम clk_pll_configure_sr_hpm_lp(काष्ठा clk_pll *pll, काष्ठा regmap *regmap,
		स्थिर काष्ठा pll_config *config, bool fsm_mode);

#पूर्ण_अगर
