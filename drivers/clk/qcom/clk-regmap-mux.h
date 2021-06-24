<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __QCOM_CLK_REGMAP_MUX_H__
#घोषणा __QCOM_CLK_REGMAP_MUX_H__

#समावेश <linux/clk-provider.h>
#समावेश "clk-regmap.h"
#समावेश "common.h"

काष्ठा clk_regmap_mux अणु
	u32			reg;
	u32			shअगरt;
	u32			width;
	स्थिर काष्ठा parent_map	*parent_map;
	काष्ठा clk_regmap	clkr;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_regmap_mux_बंदst_ops;

#पूर्ण_अगर
