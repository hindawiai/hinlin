<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Spपढ़ोtrum pll घड़ी driver
//
// Copyright (C) 2015~2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#अगर_अघोषित _SPRD_PLL_H_
#घोषणा _SPRD_PLL_H_

#समावेश "common.h"

काष्ठा reg_cfg अणु
	u32 val;
	u32 msk;
पूर्ण;

काष्ठा clk_bit_field अणु
	u8 shअगरt;
	u8 width;
पूर्ण;

क्रमागत अणु
	PLL_LOCK_DONE,
	PLL_DIV_S,
	PLL_MOD_EN,
	PLL_SDM_EN,
	PLL_REFIN,
	PLL_IBIAS,
	PLL_N,
	PLL_NINT,
	PLL_KINT,
	PLL_PREDIV,
	PLL_POSTDIV,

	PLL_FACT_MAX
पूर्ण;

/*
 * काष्ठा sprd_pll - definition of adjustable pll घड़ी
 *
 * @reg:	रेजिस्टरs used to set the configuration of pll घड़ी,
 *		reg[0] shows how many रेजिस्टरs this pll घड़ी uses.
 * @itable:	pll ibias table, itable[0] means how many items this
 *		table includes
 * @udelay	delay समय after setting rate
 * @factors	used to calculate the pll घड़ी rate
 * @fvco:	fvco threshold rate
 * @fflag:	fvco flag
 */
काष्ठा sprd_pll अणु
	u32 regs_num;
	स्थिर u64 *itable;
	स्थिर काष्ठा clk_bit_field *factors;
	u16 udelay;
	u16 k1;
	u16 k2;
	u16 fflag;
	u64 fvco;

	काष्ठा sprd_clk_common	common;
पूर्ण;

#घोषणा SPRD_PLL_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,	\
			    _regs_num, _itable, _factors,	\
			    _udelay, _k1, _k2, _fflag,		\
			    _fvco, _fn)				\
	काष्ठा sprd_pll _काष्ठा = अणु				\
		.regs_num	= _regs_num,			\
		.itable		= _itable,			\
		.factors	= _factors,			\
		.udelay		= _udelay,			\
		.k1		= _k1,				\
		.k2		= _k2,				\
		.fflag		= _fflag,			\
		.fvco		= _fvco,			\
		.common		= अणु				\
			.regmap		= शून्य,			\
			.reg		= _reg,			\
			.hw.init	= _fn(_name, _parent,	\
					      &sprd_pll_ops, 0),\
		पूर्ण,						\
	पूर्ण

#घोषणा SPRD_PLL_WITH_ITABLE_K_FVCO(_काष्ठा, _name, _parent, _reg,	\
				    _regs_num, _itable, _factors,	\
				    _udelay, _k1, _k2, _fflag, _fvco)	\
	SPRD_PLL_HW_INIT_FN(_काष्ठा, _name, _parent, _reg, _regs_num,	\
			    _itable, _factors, _udelay, _k1, _k2,	\
			    _fflag, _fvco, CLK_HW_INIT)

#घोषणा SPRD_PLL_WITH_ITABLE_K(_काष्ठा, _name, _parent, _reg,		\
			       _regs_num, _itable, _factors,		\
			       _udelay, _k1, _k2)			\
	SPRD_PLL_WITH_ITABLE_K_FVCO(_काष्ठा, _name, _parent, _reg,	\
				    _regs_num, _itable, _factors,	\
				    _udelay, _k1, _k2, 0, 0)

#घोषणा SPRD_PLL_WITH_ITABLE_1K(_काष्ठा, _name, _parent, _reg,		\
				_regs_num, _itable, _factors, _udelay)	\
	SPRD_PLL_WITH_ITABLE_K_FVCO(_काष्ठा, _name, _parent, _reg,	\
				    _regs_num, _itable, _factors,	\
				    _udelay, 1000, 1000, 0, 0)

#घोषणा SPRD_PLL_FW_NAME(_काष्ठा, _name, _parent, _reg, _regs_num,	\
			 _itable, _factors, _udelay, _k1, _k2,		\
			 _fflag, _fvco)					\
	SPRD_PLL_HW_INIT_FN(_काष्ठा, _name, _parent, _reg, _regs_num,	\
			    _itable, _factors, _udelay, _k1, _k2,	\
			    _fflag, _fvco, CLK_HW_INIT_FW_NAME)

#घोषणा SPRD_PLL_HW(_काष्ठा, _name, _parent, _reg, _regs_num, _itable,	\
		    _factors, _udelay, _k1, _k2, _fflag, _fvco)		\
	SPRD_PLL_HW_INIT_FN(_काष्ठा, _name, _parent, _reg, _regs_num,	\
			    _itable, _factors, _udelay, _k1, _k2,	\
			    _fflag, _fvco, CLK_HW_INIT_HW)

अटल अंतरभूत काष्ठा sprd_pll *hw_to_sprd_pll(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_clk_common *common = hw_to_sprd_clk_common(hw);

	वापस container_of(common, काष्ठा sprd_pll, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops sprd_pll_ops;

#पूर्ण_अगर /* _SPRD_PLL_H_ */
