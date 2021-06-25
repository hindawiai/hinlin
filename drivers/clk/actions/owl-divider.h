<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL भागider घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_DIVIDER_H_
#घोषणा _OWL_DIVIDER_H_

#समावेश "owl-common.h"

काष्ठा owl_भागider_hw अणु
	u32			reg;
	u8			shअगरt;
	u8			width;
	u8			भाग_flags;
	काष्ठा clk_भाग_प्रकारable	*table;
पूर्ण;

काष्ठा owl_भागider अणु
	काष्ठा owl_भागider_hw	भाग_hw;
	काष्ठा owl_clk_common	common;
पूर्ण;

#घोषणा OWL_DIVIDER_HW(_reg, _shअगरt, _width, _भाग_flags, _table)	\
	अणु								\
		.reg		= _reg,					\
		.shअगरt		= _shअगरt,				\
		.width		= _width,				\
		.भाग_flags	= _भाग_flags,				\
		.table		= _table,				\
	पूर्ण

#घोषणा OWL_DIVIDER(_काष्ठा, _name, _parent, _reg,			\
		    _shअगरt, _width, _table, _भाग_flags, _flags)		\
	काष्ठा owl_भागider _काष्ठा = अणु					\
		.भाग_hw	= OWL_DIVIDER_HW(_reg, _shअगरt, _width,		\
					 _भाग_flags, _table),		\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &owl_भागider_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा owl_भागider *hw_to_owl_भागider(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_clk_common *common = hw_to_owl_clk_common(hw);

	वापस container_of(common, काष्ठा owl_भागider, common);
पूर्ण

दीर्घ owl_भागider_helper_round_rate(काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_भागider_hw *भाग_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate);

अचिन्हित दीर्घ owl_भागider_helper_recalc_rate(काष्ठा owl_clk_common *common,
					 स्थिर काष्ठा owl_भागider_hw *भाग_hw,
					 अचिन्हित दीर्घ parent_rate);

पूर्णांक owl_भागider_helper_set_rate(स्थिर काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_भागider_hw *भाग_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate);

बाह्य स्थिर काष्ठा clk_ops owl_भागider_ops;

#पूर्ण_अगर /* _OWL_DIVIDER_H_ */
