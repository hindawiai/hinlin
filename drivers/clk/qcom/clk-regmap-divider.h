<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __QCOM_CLK_REGMAP_DIVIDER_H__
#घोषणा __QCOM_CLK_REGMAP_DIVIDER_H__

#समावेश <linux/clk-provider.h>
#समावेश "clk-regmap.h"

काष्ठा clk_regmap_भाग अणु
	u32			reg;
	u32			shअगरt;
	u32			width;
	काष्ठा clk_regmap	clkr;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_regmap_भाग_ops;
बाह्य स्थिर काष्ठा clk_ops clk_regmap_भाग_ro_ops;

#पूर्ण_अगर
