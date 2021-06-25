<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_PHASE_H_
#घोषणा _CCU_PHASE_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"

काष्ठा ccu_phase अणु
	u8			shअगरt;
	u8			width;

	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_PHASE(_काष्ठा, _name, _parent, _reg, _shअगरt, _width, _flags) \
	काष्ठा ccu_phase _काष्ठा = अणु					\
		.shअगरt	= _shअगरt,					\
		.width	= _width,					\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_phase_ops,	\
						      _flags),		\
		पूर्ण							\
	पूर्ण

अटल अंतरभूत काष्ठा ccu_phase *hw_to_ccu_phase(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_phase, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_phase_ops;

#पूर्ण_अगर /* _CCU_PHASE_H_ */
