<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL pll घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_PLL_H_
#घोषणा _OWL_PLL_H_

#समावेश "owl-common.h"

#घोषणा OWL_PLL_DEF_DELAY	50

/* last entry should have rate = 0 */
काष्ठा clk_pll_table अणु
	अचिन्हित पूर्णांक		val;
	अचिन्हित दीर्घ		rate;
पूर्ण;

काष्ठा owl_pll_hw अणु
	u32			reg;
	u32			bfreq;
	u8			bit_idx;
	u8			shअगरt;
	u8			width;
	u8			min_mul;
	u8			max_mul;
	u8			delay;
	स्थिर काष्ठा clk_pll_table *table;
पूर्ण;

काष्ठा owl_pll अणु
	काष्ठा owl_pll_hw	pll_hw;
	काष्ठा owl_clk_common	common;
पूर्ण;

#घोषणा OWL_PLL_HW(_reg, _bfreq, _bit_idx, _shअगरt,			\
		   _width, _min_mul, _max_mul, _delay, _table)		\
	अणु								\
		.reg		= _reg,					\
		.bfreq		= _bfreq,				\
		.bit_idx	= _bit_idx,				\
		.shअगरt		= _shअगरt,				\
		.width		= _width,				\
		.min_mul	= _min_mul,				\
		.max_mul	= _max_mul,				\
		.delay		= _delay,				\
		.table		= _table,				\
	पूर्ण

#घोषणा OWL_PLL(_काष्ठा, _name, _parent, _reg, _bfreq, _bit_idx,	\
		_shअगरt, _width, _min_mul, _max_mul, _table, _flags)	\
	काष्ठा owl_pll _काष्ठा = अणु					\
		.pll_hw	= OWL_PLL_HW(_reg, _bfreq, _bit_idx, _shअगरt,	\
				     _width, _min_mul, _max_mul,	\
				     OWL_PLL_DEF_DELAY,	_table),	\
		.common = अणु						\
			.regmap = शून्य,					\
			.hw.init = CLK_HW_INIT(_name,			\
					       _parent,			\
					       &owl_pll_ops,		\
					       _flags),			\
		पूर्ण,							\
	पूर्ण

#घोषणा OWL_PLL_NO_PARENT(_काष्ठा, _name, _reg, _bfreq, _bit_idx,	\
		_shअगरt, _width, _min_mul, _max_mul, _table, _flags)	\
	काष्ठा owl_pll _काष्ठा = अणु					\
		.pll_hw	= OWL_PLL_HW(_reg, _bfreq, _bit_idx, _shअगरt,	\
				     _width, _min_mul, _max_mul,	\
				     OWL_PLL_DEF_DELAY,	_table),	\
		.common = अणु						\
			.regmap = शून्य,					\
			.hw.init = CLK_HW_INIT_NO_PARENT(_name,		\
					       &owl_pll_ops,		\
					       _flags),			\
		पूर्ण,							\
	पूर्ण

#घोषणा OWL_PLL_NO_PARENT_DELAY(_काष्ठा, _name, _reg, _bfreq, _bit_idx,	\
		_shअगरt, _width, _min_mul, _max_mul, _delay, _table,	\
		_flags)							\
	काष्ठा owl_pll _काष्ठा = अणु					\
		.pll_hw	= OWL_PLL_HW(_reg, _bfreq, _bit_idx, _shअगरt,	\
				     _width, _min_mul,  _max_mul,	\
				     _delay, _table),			\
		.common = अणु						\
			.regmap = शून्य,					\
			.hw.init = CLK_HW_INIT_NO_PARENT(_name,		\
					       &owl_pll_ops,		\
					       _flags),			\
		पूर्ण,							\
	पूर्ण

#घोषणा mul_mask(m)		((1 << ((m)->width)) - 1)

अटल अंतरभूत काष्ठा owl_pll *hw_to_owl_pll(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_clk_common *common = hw_to_owl_clk_common(hw);

	वापस container_of(common, काष्ठा owl_pll, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops owl_pll_ops;

#पूर्ण_अगर /* _OWL_PLL_H_ */
