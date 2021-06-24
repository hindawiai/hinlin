<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 Linaro Ltd.
 * Author: Pi-Cheng Chen <pi-cheng.chen@linaro.org>
 */

#अगर_अघोषित __DRV_CLK_CPUMUX_H
#घोषणा __DRV_CLK_CPUMUX_H

काष्ठा mtk_clk_cpumux अणु
	काष्ठा clk_hw	hw;
	काष्ठा regmap	*regmap;
	u32		reg;
	u32		mask;
	u8		shअगरt;
पूर्ण;

पूर्णांक mtk_clk_रेजिस्टर_cpumuxes(काष्ठा device_node *node,
			      स्थिर काष्ठा mtk_composite *clks, पूर्णांक num,
			      काष्ठा clk_onecell_data *clk_data);

#पूर्ण_अगर /* __DRV_CLK_CPUMUX_H */
