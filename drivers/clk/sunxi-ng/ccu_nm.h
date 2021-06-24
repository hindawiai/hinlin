<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_NM_H_
#घोषणा _CCU_NM_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"
#समावेश "ccu_div.h"
#समावेश "ccu_frac.h"
#समावेश "ccu_mult.h"
#समावेश "ccu_sdm.h"

/*
 * काष्ठा ccu_nm - Definition of an N-M घड़ी
 *
 * Clocks based on the क्रमmula parent * N / M
 */
काष्ठा ccu_nm अणु
	u32			enable;
	u32			lock;

	काष्ठा ccu_mult_पूर्णांकernal	n;
	काष्ठा ccu_भाग_पूर्णांकernal		m;
	काष्ठा ccu_frac_पूर्णांकernal	frac;
	काष्ठा ccu_sdm_पूर्णांकernal		sdm;

	अचिन्हित पूर्णांक		fixed_post_भाग;
	अचिन्हित पूर्णांक		min_rate;
	अचिन्हित पूर्णांक		max_rate;

	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_NM_WITH_SDM_GATE_LOCK(_काष्ठा, _name, _parent, _reg,	\
					_nshअगरt, _nwidth,		\
					_mshअगरt, _mwidth,		\
					_sdm_table, _sdm_en,		\
					_sdm_reg, _sdm_reg_en,		\
					_gate, _lock, _flags)		\
	काष्ठा ccu_nm _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.sdm		= _SUNXI_CCU_SDM(_sdm_table, _sdm_en,	\
						 _sdm_reg, _sdm_reg_en),\
		.common		= अणु					\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_SIGMA_DELTA_MOD,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nm_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK(_काष्ठा, _name, _parent, _reg,	\
					 _nshअगरt, _nwidth,		\
					 _mshअगरt, _mwidth,		\
					 _frac_en, _frac_sel,		\
					 _frac_rate_0, _frac_rate_1,	\
					 _gate, _lock, _flags)		\
	काष्ठा ccu_nm _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.frac		= _SUNXI_CCU_FRAC(_frac_en, _frac_sel,	\
						  _frac_rate_0,		\
						  _frac_rate_1),	\
		.common		= अणु					\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_FRACTIONAL,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nm_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK_MIN(_काष्ठा, _name, _parent,	\
					     _reg, _min_rate,		\
					     _nshअगरt, _nwidth,		\
					     _mshअगरt, _mwidth,		\
					     _frac_en, _frac_sel,	\
					     _frac_rate_0, _frac_rate_1,\
					     _gate, _lock, _flags)	\
	काष्ठा ccu_nm _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.frac		= _SUNXI_CCU_FRAC(_frac_en, _frac_sel,	\
						  _frac_rate_0,		\
						  _frac_rate_1),	\
		.min_rate	= _min_rate,				\
		.common		= अणु					\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_FRACTIONAL,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nm_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा SUNXI_CCU_NM_WITH_FRAC_GATE_LOCK_MIN_MAX(_काष्ठा, _name,	\
						 _parent, _reg,		\
						 _min_rate, _max_rate,	\
						 _nshअगरt, _nwidth,	\
						 _mshअगरt, _mwidth,	\
						 _frac_en, _frac_sel,	\
						 _frac_rate_0,		\
						 _frac_rate_1,		\
						 _gate, _lock, _flags)	\
	काष्ठा ccu_nm _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.frac		= _SUNXI_CCU_FRAC(_frac_en, _frac_sel,	\
						  _frac_rate_0,		\
						  _frac_rate_1),	\
		.min_rate	= _min_rate,				\
		.max_rate	= _max_rate,				\
		.common		= अणु					\
			.reg		= _reg,				\
			.features	= CCU_FEATURE_FRACTIONAL,	\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nm_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा SUNXI_CCU_NM_WITH_GATE_LOCK(_काष्ठा, _name, _parent, _reg,	\
				    _nshअगरt, _nwidth,			\
				    _mshअगरt, _mwidth,			\
				    _gate, _lock, _flags)		\
	काष्ठा ccu_nm _काष्ठा = अणु					\
		.enable		= _gate,				\
		.lock		= _lock,				\
		.n		= _SUNXI_CCU_MULT(_nshअगरt, _nwidth),	\
		.m		= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),	\
		.common		= अणु					\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_nm_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा ccu_nm *hw_to_ccu_nm(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_nm, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_nm_ops;

#पूर्ण_अगर /* _CCU_NM_H_ */
