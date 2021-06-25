<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017 Chen-Yu Tsai. All rights reserved.
 */

#अगर_अघोषित _LINUX_CLK_SUNXI_NG_H_
#घोषणा _LINUX_CLK_SUNXI_NG_H_

#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित CONFIG_SUNXI_CCU
पूर्णांक sunxi_ccu_set_mmc_timing_mode(काष्ठा clk *clk, bool new_mode);
पूर्णांक sunxi_ccu_get_mmc_timing_mode(काष्ठा clk *clk);
#अन्यथा
अटल अंतरभूत पूर्णांक sunxi_ccu_set_mmc_timing_mode(काष्ठा clk *clk,
						bool new_mode)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक sunxi_ccu_get_mmc_timing_mode(काष्ठा clk *clk)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
