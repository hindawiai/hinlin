<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL gate घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_GATE_H_
#घोषणा _OWL_GATE_H_

#समावेश "owl-common.h"

काष्ठा owl_gate_hw अणु
	u32			reg;
	u8			bit_idx;
	u8			gate_flags;
पूर्ण;

काष्ठा owl_gate अणु
	काष्ठा owl_gate_hw	gate_hw;
	काष्ठा owl_clk_common	common;
पूर्ण;

#घोषणा OWL_GATE_HW(_reg, _bit_idx, _gate_flags)	\
	अणु						\
		.reg		= _reg,			\
		.bit_idx	= _bit_idx,		\
		.gate_flags	= _gate_flags,		\
	पूर्ण

#घोषणा OWL_GATE(_काष्ठा, _name, _parent, _reg,				\
		_bit_idx, _gate_flags, _flags)				\
	काष्ठा owl_gate _काष्ठा = अणु					\
		.gate_hw = OWL_GATE_HW(_reg, _bit_idx, _gate_flags),	\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &owl_gate_ops,	\
						      _flags),		\
		पूर्ण							\
	पूर्ण								\

#घोषणा OWL_GATE_NO_PARENT(_काष्ठा, _name, _reg,			\
		_bit_idx, _gate_flags, _flags)				\
	काष्ठा owl_gate _काष्ठा = अणु					\
		.gate_hw = OWL_GATE_HW(_reg, _bit_idx, _gate_flags),	\
		.common = अणु						\
			.regmap		= शून्य,				\
			.hw.init	= CLK_HW_INIT_NO_PARENT(_name,	\
						      &owl_gate_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण								\

अटल अंतरभूत काष्ठा owl_gate *hw_to_owl_gate(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा owl_clk_common *common = hw_to_owl_clk_common(hw);

	वापस container_of(common, काष्ठा owl_gate, common);
पूर्ण

व्योम owl_gate_set(स्थिर काष्ठा owl_clk_common *common,
		 स्थिर काष्ठा owl_gate_hw *gate_hw, bool enable);
पूर्णांक owl_gate_clk_is_enabled(स्थिर काष्ठा owl_clk_common *common,
		   स्थिर काष्ठा owl_gate_hw *gate_hw);

बाह्य स्थिर काष्ठा clk_ops owl_gate_ops;

#पूर्ण_अगर /* _OWL_GATE_H_ */
