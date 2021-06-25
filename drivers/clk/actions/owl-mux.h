<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL mux घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_MUX_H_
#घोषणा _OWL_MUX_H_

#समावेश "owl-common.h"

काष्ठा owl_mux_hw अणु
	u32			reg;
	u8			shअगरt;
	u8			width;
पूर्ण;

काष्ठा owl_mux अणु
	काष्ठा owl_mux_hw	mux_hw;
	काष्ठा owl_clk_common	common;
पूर्ण;

#घोषणा OWL_MUX_HW(_reg, _shअगरt, _width)		\
	अणु						\
		.reg	= _reg,				\
		.shअगरt	= _shअगरt,			\
		.width	= _width,			\
	पूर्ण

#घोषणा OWL_MUX(_काष्ठा, _name, _parents, _reg,				\
		_shअगरt, _width, _flags)					\
	काष्ठा owl_mux _काष्ठा = अणु					\
		.mux_hw	= OWL_MUX_HW(_reg, _shअगरt, _width),		\
		.common = अणु						\
			.regmap = शून्य,					\
			.hw.init = CLK_HW_INIT_PARENTS(_name,		\
						       _parents,	\
						       &owl_mux_ops,	\
						       _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा owl_mux *hw_to_owl_mux(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_clk_common *common = hw_to_owl_clk_common(hw);

	वापस container_of(common, काष्ठा owl_mux, common);
पूर्ण

u8 owl_mux_helper_get_parent(स्थिर काष्ठा owl_clk_common *common,
			     स्थिर काष्ठा owl_mux_hw *mux_hw);
पूर्णांक owl_mux_helper_set_parent(स्थिर काष्ठा owl_clk_common *common,
			      काष्ठा owl_mux_hw *mux_hw, u8 index);

बाह्य स्थिर काष्ठा clk_ops owl_mux_ops;

#पूर्ण_अगर /* _OWL_MUX_H_ */
