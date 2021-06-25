<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_NK_H_
#घोषणा _CCU_NK_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"
#समावेश "ccu_div.h"
#समावेश "ccu_mult.h"

/*
 * काष्ठा ccu_nk - Definition of an N-K घड़ी
 *
 * Clocks based on the क्रमmula parent * N * K
 */
काष्ठा ccu_nk अणु
	u16			reg;
	u32			enable;
	u32			lock;

	काष्ठा ccu_mult_पूर्णांकernal	n;
	काष्ठा ccu_mult_पूर्णांकernal	k;

	अचिन्हित पूर्णांक		fixed_post_भाग;

	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_NK_WITH_GATE_LOCK_POSTDIV(_काष्ठा, _name, _parent, _reg, \
					    _nshअगरt, _nwidth,		\
					    _kshअगरt, _kwidth,		\
					    _gate, _lock, _postभाग,	\
					    _flags)			\
	काष्ठा ccu_nk _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.k		= _SUNXI_CCU_MULT(_kshअगरt, _kwidth),	\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.fixed_post_भाग	= _postभाग,				\
		.common		= अणु					\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_FIXED_POSTDIV,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nk_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा ccu_nk *hw_to_ccu_nk(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_nk, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_nk_ops;

#पूर्ण_अगर /* _CCU_NK_H_ */
