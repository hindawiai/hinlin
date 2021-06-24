<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2017, Linaro Limited
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#अगर_अघोषित __QCOM_CLK_REGMAP_MUX_DIV_H__
#घोषणा __QCOM_CLK_REGMAP_MUX_DIV_H__

#समावेश <linux/clk-provider.h>
#समावेश "clk-regmap.h"

/**
 * काष्ठा mux_भाग_clk - combined mux/भागider घड़ी
 * @reg_offset: offset of the mux/भागider रेजिस्टर
 * @hid_width:	number of bits in half पूर्णांकeger भागider
 * @hid_shअगरt:	lowest bit of hid value field
 * @src_width:	number of bits in source select
 * @src_shअगरt:	lowest bit of source select field
 * @भाग:	the भागider raw configuration value
 * @src:	the mux index which will be used अगर the घड़ी is enabled
 * @parent_map: map from parent_names index to src_sel field
 * @clkr:	handle between common and hardware-specअगरic पूर्णांकerfaces
 * @pclk:	the input PLL घड़ी
 * @clk_nb:	घड़ी notअगरier क्रम rate changes of the input PLL
 */
काष्ठा clk_regmap_mux_भाग अणु
	u32				reg_offset;
	u32				hid_width;
	u32				hid_shअगरt;
	u32				src_width;
	u32				src_shअगरt;
	u32				भाग;
	u32				src;
	स्थिर u32			*parent_map;
	काष्ठा clk_regmap		clkr;
	काष्ठा clk			*pclk;
	काष्ठा notअगरier_block		clk_nb;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_regmap_mux_भाग_ops;
बाह्य पूर्णांक mux_भाग_set_src_भाग(काष्ठा clk_regmap_mux_भाग *md, u32 src, u32 भाग);

#पूर्ण_अगर
