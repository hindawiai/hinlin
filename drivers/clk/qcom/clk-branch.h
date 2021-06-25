<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2013, The Linux Foundation. All rights reserved. */

#अगर_अघोषित __QCOM_CLK_BRANCH_H__
#घोषणा __QCOM_CLK_BRANCH_H__

#समावेश <linux/clk-provider.h>

#समावेश "clk-regmap.h"

/**
 * काष्ठा clk_branch - gating घड़ी with status bit and dynamic hardware gating
 *
 * @hwcg_reg: dynamic hardware घड़ी gating रेजिस्टर
 * @hwcg_bit: ORed with @hwcg_reg to enable dynamic hardware घड़ी gating
 * @halt_reg: halt रेजिस्टर
 * @halt_bit: ANDed with @halt_reg to test क्रम घड़ी halted
 * @halt_check: type of halt checking to perक्रमm
 * @clkr: handle between common and hardware-specअगरic पूर्णांकerfaces
 *
 * Clock which can gate its output.
 */
काष्ठा clk_branch अणु
	u32	hwcg_reg;
	u32	halt_reg;
	u8	hwcg_bit;
	u8	halt_bit;
	u8	halt_check;
#घोषणा BRANCH_VOTED			BIT(7) /* Delay on disable */
#घोषणा BRANCH_HALT			0 /* pol: 1 = halt */
#घोषणा BRANCH_HALT_VOTED		(BRANCH_HALT | BRANCH_VOTED)
#घोषणा BRANCH_HALT_ENABLE		1 /* pol: 0 = halt */
#घोषणा BRANCH_HALT_ENABLE_VOTED	(BRANCH_HALT_ENABLE | BRANCH_VOTED)
#घोषणा BRANCH_HALT_DELAY		2 /* No bit to check; just delay */
#घोषणा BRANCH_HALT_SKIP		3 /* Don't check halt bit */

	काष्ठा clk_regmap clkr;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_branch_ops;
बाह्य स्थिर काष्ठा clk_ops clk_branch2_ops;
बाह्य स्थिर काष्ठा clk_ops clk_branch_simple_ops;
बाह्य स्थिर काष्ठा clk_ops clk_branch2_aon_ops;

#घोषणा to_clk_branch(_hw) \
	container_of(to_clk_regmap(_hw), काष्ठा clk_branch, clkr)

#पूर्ण_अगर
