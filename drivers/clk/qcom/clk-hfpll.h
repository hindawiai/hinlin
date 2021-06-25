<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __QCOM_CLK_HFPLL_H__
#घोषणा __QCOM_CLK_HFPLL_H__

#समावेश <linux/clk-provider.h>
#समावेश <linux/spinlock.h>
#समावेश "clk-regmap.h"

काष्ठा hfpll_data अणु
	u32 mode_reg;
	u32 l_reg;
	u32 m_reg;
	u32 n_reg;
	u32 user_reg;
	u32 droop_reg;
	u32 config_reg;
	u32 status_reg;
	u8  lock_bit;

	u32 droop_val;
	u32 config_val;
	u32 user_val;
	u32 user_vco_mask;
	अचिन्हित दीर्घ low_vco_max_rate;

	अचिन्हित दीर्घ min_rate;
	अचिन्हित दीर्घ max_rate;
पूर्ण;

काष्ठा clk_hfpll अणु
	काष्ठा hfpll_data स्थिर *d;
	पूर्णांक init_करोne;

	काष्ठा clk_regmap clkr;
	spinlock_t lock;
पूर्ण;

#घोषणा to_clk_hfpll(_hw) \
	container_of(to_clk_regmap(_hw), काष्ठा clk_hfpll, clkr)

बाह्य स्थिर काष्ठा clk_ops clk_ops_hfpll;

#पूर्ण_अगर
