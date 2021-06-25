<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL factor घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_FACTOR_H_
#घोषणा _OWL_FACTOR_H_

#समावेश "owl-common.h"

काष्ठा clk_factor_table अणु
	अचिन्हित पूर्णांक		val;
	अचिन्हित पूर्णांक		mul;
	अचिन्हित पूर्णांक		भाग;
पूर्ण;

काष्ठा owl_factor_hw अणु
	u32			reg;
	u8			shअगरt;
	u8			width;
	u8			fct_flags;
	काष्ठा clk_factor_table	*table;
पूर्ण;

काष्ठा owl_factor अणु
	काष्ठा owl_factor_hw	factor_hw;
	काष्ठा owl_clk_common	common;
पूर्ण;

#घोषणा OWL_FACTOR_HW(_reg, _shअगरt, _width, _fct_flags, _table)		\
	अणु								\
		.reg		= _reg,					\
		.shअगरt		= _shअगरt,				\
		.width		= _width,				\
		.fct_flags	= _fct_flags,				\
		.table		= _table,				\
	पूर्ण

#घोषणा OWL_FACTOR(_काष्ठा, _name, _parent, _reg,			\
		   _shअगरt, _width, _table, _fct_flags, _flags)		\
	काष्ठा owl_factor _काष्ठा = अणु					\
		.factor_hw = OWL_FACTOR_HW(_reg, _shअगरt,		\
					   _width, _fct_flags, _table),	\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &owl_factor_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा भाग_mask(d) ((1 << ((d)->width)) - 1)

अटल अंतरभूत काष्ठा owl_factor *hw_to_owl_factor(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_clk_common *common = hw_to_owl_clk_common(hw);

	वापस container_of(common, काष्ठा owl_factor, common);
पूर्ण

दीर्घ owl_factor_helper_round_rate(काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_factor_hw *factor_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate);

अचिन्हित दीर्घ owl_factor_helper_recalc_rate(काष्ठा owl_clk_common *common,
					 स्थिर काष्ठा owl_factor_hw *factor_hw,
					 अचिन्हित दीर्घ parent_rate);

पूर्णांक owl_factor_helper_set_rate(स्थिर काष्ठा owl_clk_common *common,
				स्थिर काष्ठा owl_factor_hw *factor_hw,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate);

बाह्य स्थिर काष्ठा clk_ops owl_factor_ops;

#पूर्ण_अगर /* _OWL_FACTOR_H_ */
