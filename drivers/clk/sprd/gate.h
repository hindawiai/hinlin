<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Spपढ़ोtrum gate घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#अगर_अघोषित _SPRD_GATE_H_
#घोषणा _SPRD_GATE_H_

#समावेश "common.h"

काष्ठा sprd_gate अणु
	u32			enable_mask;
	u16			flags;
	u16			sc_offset;
	u16			udelay;

	काष्ठा sprd_clk_common	common;
पूर्ण;

/*
 * sprd_gate->flags is used क्रम:
 * CLK_GATE_SET_TO_DISABLE	BIT(0)
 * CLK_GATE_HIWORD_MASK		BIT(1)
 * CLK_GATE_BIG_ENDIAN		BIT(2)
 * so we define new flags from	BIT(3)
 */
#घोषणा SPRD_GATE_NON_AON BIT(3) /* not alway घातered on, check beक्रमe पढ़ो */

#घोषणा SPRD_SC_GATE_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,	\
				    _sc_offset, _enable_mask, _flags,	\
				    _gate_flags, _udelay, _ops, _fn)	\
	काष्ठा sprd_gate _काष्ठा = अणु					\
		.enable_mask	= _enable_mask,				\
		.sc_offset	= _sc_offset,				\
		.flags		= _gate_flags,				\
		.udelay		= _udelay,				\
		.common	= अणु						\
			.regmap		= शून्य,				\
			.reg		= _reg,				\
			.hw.init	= _fn(_name, _parent,		\
					      _ops, _flags),		\
		पूर्ण							\
	पूर्ण

#घोषणा SPRD_SC_GATE_CLK_OPS_UDELAY(_काष्ठा, _name, _parent, _reg,	\
				    _sc_offset, _enable_mask, _flags,	\
				    _gate_flags, _udelay, _ops)		\
	SPRD_SC_GATE_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,	\
				    _sc_offset, _enable_mask, _flags,	\
				    _gate_flags, _udelay, _ops, CLK_HW_INIT)

#घोषणा SPRD_SC_GATE_CLK_OPS(_काष्ठा, _name, _parent, _reg, _sc_offset,	\
			     _enable_mask, _flags, _gate_flags, _ops)	\
	SPRD_SC_GATE_CLK_OPS_UDELAY(_काष्ठा, _name, _parent, _reg,	\
				    _sc_offset, _enable_mask, _flags,	\
				    _gate_flags, 0, _ops)

#घोषणा SPRD_SC_GATE_CLK(_काष्ठा, _name, _parent, _reg, _sc_offset,	\
			 _enable_mask, _flags, _gate_flags)		\
	SPRD_SC_GATE_CLK_OPS(_काष्ठा, _name, _parent, _reg, _sc_offset,	\
			     _enable_mask, _flags, _gate_flags,		\
			     &sprd_sc_gate_ops)

#घोषणा SPRD_GATE_CLK(_काष्ठा, _name, _parent, _reg,			\
		      _enable_mask, _flags, _gate_flags)		\
	SPRD_SC_GATE_CLK_OPS(_काष्ठा, _name, _parent, _reg, 0,		\
			     _enable_mask, _flags, _gate_flags,		\
			     &sprd_gate_ops)

#घोषणा SPRD_PLL_SC_GATE_CLK(_काष्ठा, _name, _parent, _reg, _sc_offset,	\
			     _enable_mask, _flags, _gate_flags,		\
			     _udelay)					\
	SPRD_SC_GATE_CLK_OPS_UDELAY(_काष्ठा, _name, _parent, _reg,	\
				    _sc_offset,	_enable_mask, _flags,	\
				    _gate_flags, _udelay,		\
				    &sprd_pll_sc_gate_ops)


#घोषणा SPRD_SC_GATE_CLK_HW_OPS_UDELAY(_काष्ठा, _name, _parent, _reg,	\
				       _sc_offset, _enable_mask,	\
				       _flags, _gate_flags,		\
				       _udelay, _ops)			\
	SPRD_SC_GATE_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,	\
				    _sc_offset, _enable_mask, _flags,	\
				    _gate_flags, _udelay, _ops,		\
				    CLK_HW_INIT_HW)

#घोषणा SPRD_SC_GATE_CLK_HW_OPS(_काष्ठा, _name, _parent, _reg,		\
				_sc_offset, _enable_mask, _flags,	\
				_gate_flags, _ops)			\
	SPRD_SC_GATE_CLK_HW_OPS_UDELAY(_काष्ठा, _name, _parent, _reg,	\
				       _sc_offset, _enable_mask,	\
				       _flags, _gate_flags, 0, _ops)

#घोषणा SPRD_SC_GATE_CLK_HW(_काष्ठा, _name, _parent, _reg,		\
			    _sc_offset, _enable_mask, _flags,		\
			    _gate_flags)				\
	SPRD_SC_GATE_CLK_HW_OPS(_काष्ठा, _name, _parent, _reg,		\
				_sc_offset, _enable_mask, _flags,	\
				_gate_flags, &sprd_sc_gate_ops)

#घोषणा SPRD_GATE_CLK_HW(_काष्ठा, _name, _parent, _reg,			\
			 _enable_mask, _flags, _gate_flags)		\
	SPRD_SC_GATE_CLK_HW_OPS(_काष्ठा, _name, _parent, _reg, 0,	\
				_enable_mask, _flags, _gate_flags,	\
				&sprd_gate_ops)

#घोषणा SPRD_PLL_SC_GATE_CLK_HW(_काष्ठा, _name, _parent, _reg,		\
				_sc_offset, _enable_mask, _flags,	\
				_gate_flags, _udelay)			\
	SPRD_SC_GATE_CLK_HW_OPS_UDELAY(_काष्ठा, _name, _parent, _reg,	\
				       _sc_offset, _enable_mask,	\
				       _flags, _gate_flags, _udelay,	\
				       &sprd_pll_sc_gate_ops)

#घोषणा SPRD_SC_GATE_CLK_FW_NAME_OPS_UDELAY(_काष्ठा, _name, _parent,	\
					    _reg, _sc_offset,		\
					    _enable_mask, _flags,	\
					    _gate_flags, _udelay, _ops)	\
	SPRD_SC_GATE_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,	\
				    _sc_offset, _enable_mask, _flags,	\
				    _gate_flags, _udelay, _ops,		\
				    CLK_HW_INIT_FW_NAME)

#घोषणा SPRD_SC_GATE_CLK_FW_NAME_OPS(_काष्ठा, _name, _parent, _reg,	\
				     _sc_offset, _enable_mask, _flags,	\
				     _gate_flags, _ops)			\
	SPRD_SC_GATE_CLK_FW_NAME_OPS_UDELAY(_काष्ठा, _name, _parent,	\
					    _reg, _sc_offset,		\
					    _enable_mask, _flags,	\
					    _gate_flags, 0, _ops)

#घोषणा SPRD_SC_GATE_CLK_FW_NAME(_काष्ठा, _name, _parent, _reg,		\
				 _sc_offset, _enable_mask, _flags,	\
				 _gate_flags)				\
	SPRD_SC_GATE_CLK_FW_NAME_OPS(_काष्ठा, _name, _parent, _reg,	\
				     _sc_offset, _enable_mask, _flags,	\
				     _gate_flags, &sprd_sc_gate_ops)

#घोषणा SPRD_GATE_CLK_FW_NAME(_काष्ठा, _name, _parent, _reg,		\
			      _enable_mask, _flags, _gate_flags)	\
	SPRD_SC_GATE_CLK_FW_NAME_OPS(_काष्ठा, _name, _parent, _reg, 0,	\
				     _enable_mask, _flags, _gate_flags,	\
				     &sprd_gate_ops)

#घोषणा SPRD_PLL_SC_GATE_CLK_FW_NAME(_काष्ठा, _name, _parent, _reg,	\
				     _sc_offset, _enable_mask, _flags,	\
				     _gate_flags, _udelay)		\
	SPRD_SC_GATE_CLK_FW_NAME_OPS_UDELAY(_काष्ठा, _name, _parent,	\
					    _reg, _sc_offset,		\
					    _enable_mask, _flags,	\
					    _gate_flags, _udelay,	\
					    &sprd_pll_sc_gate_ops)

अटल अंतरभूत काष्ठा sprd_gate *hw_to_sprd_gate(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_clk_common *common = hw_to_sprd_clk_common(hw);

	वापस container_of(common, काष्ठा sprd_gate, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops sprd_gate_ops;
बाह्य स्थिर काष्ठा clk_ops sprd_sc_gate_ops;
बाह्य स्थिर काष्ठा clk_ops sprd_pll_sc_gate_ops;

#पूर्ण_अगर /* _SPRD_GATE_H_ */
