<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_NKM_H_
#घोषणा _CCU_NKM_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"
#समावेश "ccu_div.h"
#समावेश "ccu_mult.h"

/*
 * काष्ठा ccu_nkm - Definition of an N-K-M घड़ी
 *
 * Clocks based on the क्रमmula parent * N * K / M
 */
काष्ठा ccu_nkm अणु
	u32			enable;
	u32			lock;

	काष्ठा ccu_mult_पूर्णांकernal	n;
	काष्ठा ccu_mult_पूर्णांकernal	k;
	काष्ठा ccu_भाग_पूर्णांकernal		m;
	काष्ठा ccu_mux_पूर्णांकernal	mux;

	अचिन्हित पूर्णांक		fixed_post_भाग;

	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_NKM_WITH_MUX_GATE_LOCK(_काष्ठा, _name, _parents, _reg, \
					 _nshअगरt, _nwidth,		\
					 _kshअगरt, _kwidth,		\
					 _mshअगरt, _mwidth,		\
					 _muxshअगरt, _muxwidth,		\
					 _gate, _lock, _flags)		\
	काष्ठा ccu_nkm _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.k		= _SUNXI_CCU_MULT(_kshअगरt, _kwidth),	\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.mux		= _SUNXI_CCU_MUX(_muxshअगरt, _muxwidth),	\
		.common		= अणु					\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
						      _parents,		\
						      &ccu_nkm_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा SUNXI_CCU_NKM_WITH_GATE_LOCK(_काष्ठा, _name, _parent, _reg,	\
				     _nshअगरt, _nwidth,			\
				     _kshअगरt, _kwidth,			\
				     _mshअगरt, _mwidth,			\
				     _gate, _lock, _flags)		\
	काष्ठा ccu_nkm _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.k		= _SUNXI_CCU_MULT(_kshअगरt, _kwidth),	\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.common		= अणु					\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nkm_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा ccu_nkm *hw_to_ccu_nkm(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_nkm, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_nkm_ops;

#पूर्ण_अगर /* _CCU_NKM_H_ */
