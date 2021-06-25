<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_NKMP_H_
#घोषणा _CCU_NKMP_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"
#समावेश "ccu_div.h"
#समावेश "ccu_mult.h"

/*
 * काष्ठा ccu_nkmp - Definition of an N-K-M-P घड़ी
 *
 * Clocks based on the क्रमmula parent * N * K >> P / M
 */
काष्ठा ccu_nkmp अणु
	u32			enable;
	u32			lock;

	काष्ठा ccu_mult_पूर्णांकernal	n;
	काष्ठा ccu_mult_पूर्णांकernal	k;
	काष्ठा ccu_भाग_पूर्णांकernal		m;
	काष्ठा ccu_भाग_पूर्णांकernal		p;

	अचिन्हित पूर्णांक		fixed_post_भाग;
	अचिन्हित पूर्णांक		max_rate;

	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_NKMP_WITH_GATE_LOCK(_काष्ठा, _name, _parent, _reg,	\
				      _nshअगरt, _nwidth,			\
				      _kshअगरt, _kwidth,			\
				      _mshअगरt, _mwidth,			\
				      _pshअगरt, _pwidth,			\
				      _gate, _lock, _flags)		\
	काष्ठा ccu_nkmp _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.k		= _SUNXI_CCU_MULT(_kshअगरt, _kwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.p		= _SUNXI_CCU_DIV(_pshअगरt, _pwidth),	\
		.common		= अणु					\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nkmp_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा ccu_nkmp *hw_to_ccu_nkmp(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_nkmp, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_nkmp_ops;

#पूर्ण_अगर /* _CCU_NKMP_H_ */
