<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL composite घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_COMPOSITE_H_
#घोषणा _OWL_COMPOSITE_H_

#समावेश "owl-common.h"
#समावेश "owl-mux.h"
#समावेश "owl-gate.h"
#समावेश "owl-factor.h"
#समावेश "owl-fixed-factor.h"
#समावेश "owl-divider.h"

जोड़ owl_rate अणु
	काष्ठा owl_भागider_hw	भाग_hw;
	काष्ठा owl_factor_hw	factor_hw;
	काष्ठा clk_fixed_factor	fix_fact_hw;
पूर्ण;

काष्ठा owl_composite अणु
	काष्ठा owl_mux_hw	mux_hw;
	काष्ठा owl_gate_hw	gate_hw;
	जोड़ owl_rate		rate;

	स्थिर काष्ठा clk_ops	*fix_fact_ops;

	काष्ठा owl_clk_common	common;
पूर्ण;

#घोषणा OWL_COMP_DIV(_काष्ठा, _name, _parent,				\
		     _mux, _gate, _भाग, _flags)				\
	काष्ठा owl_composite _काष्ठा = अणु				\
		.mux_hw		= _mux,					\
		.gate_hw	= _gate,				\
		.rate.भाग_hw	= _भाग,					\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
						     _parent,		\
						      &owl_comp_भाग_ops,\
						     _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा OWL_COMP_DIV_FIXED(_काष्ठा, _name, _parent,			\
		     _gate, _भाग, _flags)				\
	काष्ठा owl_composite _काष्ठा = अणु				\
		.gate_hw	= _gate,				\
		.rate.भाग_hw	= _भाग,					\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						     _parent,		\
						      &owl_comp_भाग_ops,\
						     _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा OWL_COMP_FACTOR(_काष्ठा, _name, _parent,			\
			_mux, _gate, _factor, _flags)			\
	काष्ठा owl_composite _काष्ठा = अणु				\
		.mux_hw		= _mux,					\
		.gate_hw	= _gate,				\
		.rate.factor_hw	= _factor,				\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
						     _parent,		\
						     &owl_comp_fact_ops,\
						     _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा OWL_COMP_FIXED_FACTOR(_काष्ठा, _name, _parent,			\
			_gate, _mul, _भाग, _flags)			\
	काष्ठा owl_composite _काष्ठा = अणु				\
		.gate_hw		= _gate,			\
		.rate.fix_fact_hw.mult	= _mul,				\
		.rate.fix_fact_hw.भाग	= _भाग,				\
		.fix_fact_ops		= &clk_fixed_factor_ops,	\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						 _parent,		\
						 &owl_comp_fix_fact_ops,\
						 _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा OWL_COMP_PASS(_काष्ठा, _name, _parent,				\
		      _mux, _gate, _flags)				\
	काष्ठा owl_composite _काष्ठा = अणु				\
		.mux_hw		= _mux,					\
		.gate_hw	= _gate,				\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
						     _parent,		\
						     &owl_comp_pass_ops,\
						     _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा owl_composite *hw_to_owl_comp(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_clk_common *common = hw_to_owl_clk_common(hw);

	वापस container_of(common, काष्ठा owl_composite, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops owl_comp_भाग_ops;
बाह्य स्थिर काष्ठा clk_ops owl_comp_fact_ops;
बाह्य स्थिर काष्ठा clk_ops owl_comp_fix_fact_ops;
बाह्य स्थिर काष्ठा clk_ops owl_comp_pass_ops;
बाह्य स्थिर काष्ठा clk_ops clk_fixed_factor_ops;

#पूर्ण_अगर /* _OWL_COMPOSITE_H_ */
