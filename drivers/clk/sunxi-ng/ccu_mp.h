<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_MP_H_
#घोषणा _CCU_MP_H_

#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"
#समावेश "ccu_div.h"
#समावेश "ccu_mult.h"
#समावेश "ccu_mux.h"

/*
 * काष्ठा ccu_mp - Definition of an M-P घड़ी
 *
 * Clocks based on the क्रमmula parent >> P / M
 */
काष्ठा ccu_mp अणु
	u32			enable;

	काष्ठा ccu_भाग_पूर्णांकernal		m;
	काष्ठा ccu_भाग_पूर्णांकernal		p;
	काष्ठा ccu_mux_पूर्णांकernal	mux;

	अचिन्हित पूर्णांक		fixed_post_भाग;

	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_MP_WITH_MUX_GATE_POSTDIV(_काष्ठा, _name, _parents, _reg, \
					   _mshअगरt, _mwidth,		\
					   _pshअगरt, _pwidth,		\
					   _muxshअगरt, _muxwidth,	\
					   _gate, _postभाग, _flags)	\
	काष्ठा ccu_mp _काष्ठा = अणु					\
		.enable	= _gate,					\
		.m	= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),		\
		.p	= _SUNXI_CCU_DIV(_pshअगरt, _pwidth),		\
		.mux	= _SUNXI_CCU_MUX(_muxshअगरt, _muxwidth),		\
		.fixed_post_भाग	= _postभाग,				\
		.common	= अणु						\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_FIXED_POSTDIV,	\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
							      _parents, \
							      &ccu_mp_ops, \
							      _flags),	\
		पूर्ण							\
	पूर्ण

#घोषणा SUNXI_CCU_MP_WITH_MUX_GATE(_काष्ठा, _name, _parents, _reg,	\
				   _mshअगरt, _mwidth,			\
				   _pshअगरt, _pwidth,			\
				   _muxshअगरt, _muxwidth,		\
				   _gate, _flags)			\
	काष्ठा ccu_mp _काष्ठा = अणु					\
		.enable	= _gate,					\
		.m	= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),		\
		.p	= _SUNXI_CCU_DIV(_pshअगरt, _pwidth),		\
		.mux	= _SUNXI_CCU_MUX(_muxshअगरt, _muxwidth),		\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
							      _parents, \
							      &ccu_mp_ops, \
							      _flags),	\
		पूर्ण							\
	पूर्ण

#घोषणा SUNXI_CCU_MP_WITH_MUX(_काष्ठा, _name, _parents, _reg,		\
			      _mshअगरt, _mwidth,				\
			      _pshअगरt, _pwidth,				\
			      _muxshअगरt, _muxwidth,			\
			      _flags)					\
	SUNXI_CCU_MP_WITH_MUX_GATE(_काष्ठा, _name, _parents, _reg,	\
				   _mshअगरt, _mwidth,			\
				   _pshअगरt, _pwidth,			\
				   _muxshअगरt, _muxwidth,		\
				   0, _flags)

अटल अंतरभूत काष्ठा ccu_mp *hw_to_ccu_mp(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_mp, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_mp_ops;

/*
 * Special class of M-P घड़ी that supports MMC timing modes
 *
 * Since the MMC घड़ी रेजिस्टरs all follow the same layout, we can
 * simplअगरy the macro क्रम this particular हाल. In addition, as
 * चयनing modes also affects the output घड़ी rate, we need to
 * have CLK_GET_RATE_NOCACHE क्रम all these types of घड़ीs.
 */

#घोषणा SUNXI_CCU_MP_MMC_WITH_MUX_GATE(_काष्ठा, _name, _parents, _reg,	\
				       _flags)				\
	काष्ठा ccu_mp _काष्ठा = अणु					\
		.enable	= BIT(31),					\
		.m	= _SUNXI_CCU_DIV(0, 4),				\
		.p	= _SUNXI_CCU_DIV(16, 2),			\
		.mux	= _SUNXI_CCU_MUX(24, 2),			\
		.common	= अणु						\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_MMC_TIMING_SWITCH, \
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
							      _parents, \
							      &ccu_mp_mmc_ops, \
							      CLK_GET_RATE_NOCACHE | \
							      _flags),	\
		पूर्ण							\
	पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_mp_mmc_ops;

#पूर्ण_अगर /* _CCU_MP_H_ */
