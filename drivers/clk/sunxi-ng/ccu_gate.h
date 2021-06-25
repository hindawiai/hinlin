<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_GATE_H_
#घोषणा _CCU_GATE_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"

काष्ठा ccu_gate अणु
	u32			enable;

	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_GATE(_काष्ठा, _name, _parent, _reg, _gate, _flags)	\
	काष्ठा ccu_gate _काष्ठा = अणु					\
		.enable	= _gate,					\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_gate_ops,	\
						      _flags),		\
		पूर्ण							\
	पूर्ण

#घोषणा SUNXI_CCU_GATE_HW(_काष्ठा, _name, _parent, _reg, _gate, _flags)	\
	काष्ठा ccu_gate _काष्ठा = अणु					\
		.enable	= _gate,					\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_HW(_name,		\
							 _parent,	\
							 &ccu_gate_ops,	\
							 _flags),	\
		पूर्ण							\
	पूर्ण

#घोषणा SUNXI_CCU_GATE_FW(_काष्ठा, _name, _parent, _reg, _gate, _flags)	\
	काष्ठा ccu_gate _काष्ठा = अणु					\
		.enable	= _gate,					\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_FW_NAME(_name,	\
							      _parent,	\
							      &ccu_gate_ops, \
							      _flags),	\
		पूर्ण							\
	पूर्ण

/*
 * The following two macros allow the re-use of the data काष्ठाure
 * holding the parent info.
 */
#घोषणा SUNXI_CCU_GATE_HWS(_काष्ठा, _name, _parent, _reg, _gate, _flags) \
	काष्ठा ccu_gate _काष्ठा = अणु					\
		.enable	= _gate,					\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_HWS(_name,	\
							  _parent,	\
							  &ccu_gate_ops, \
							  _flags),	\
		पूर्ण							\
	पूर्ण

#घोषणा SUNXI_CCU_GATE_DATA(_काष्ठा, _name, _data, _reg, _gate, _flags)	\
	काष्ठा ccu_gate _काष्ठा = अणु					\
		.enable	= _gate,					\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	=				\
				CLK_HW_INIT_PARENTS_DATA(_name,		\
							 _data,		\
							 &ccu_gate_ops,	\
							 _flags),	\
		पूर्ण							\
	पूर्ण

अटल अंतरभूत काष्ठा ccu_gate *hw_to_ccu_gate(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_gate, common);
पूर्ण

व्योम ccu_gate_helper_disable(काष्ठा ccu_common *common, u32 gate);
पूर्णांक ccu_gate_helper_enable(काष्ठा ccu_common *common, u32 gate);
पूर्णांक ccu_gate_helper_is_enabled(काष्ठा ccu_common *common, u32 gate);

बाह्य स्थिर काष्ठा clk_ops ccu_gate_ops;

#पूर्ण_अगर /* _CCU_GATE_H_ */
