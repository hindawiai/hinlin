<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_DIV_H_
#घोषणा _CCU_DIV_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"
#समावेश "ccu_mux.h"

/**
 * काष्ठा ccu_भाग_पूर्णांकernal - Internal भागider description
 * @shअगरt: Bit offset of the भागider in its रेजिस्टर
 * @width: Width of the भागider field in its रेजिस्टर
 * @max: Maximum value allowed क्रम that भागider. This is the
 *       arithmetic value, not the maximum value to be set in the
 *       रेजिस्टर.
 * @flags: clk_भागider flags to apply on this भागider
 * @table: Divider table poपूर्णांकer (अगर applicable)
 *
 * That काष्ठाure represents a single भागider, and is meant to be
 * embedded in other काष्ठाures representing the various घड़ी
 * classes.
 *
 * It is basically a wrapper around the clk_भागider functions
 * arguments.
 */
काष्ठा ccu_भाग_पूर्णांकernal अणु
	u8			shअगरt;
	u8			width;

	u32			max;
	u32			offset;

	u32			flags;

	काष्ठा clk_भाग_प्रकारable	*table;
पूर्ण;

#घोषणा _SUNXI_CCU_DIV_TABLE_FLAGS(_shअगरt, _width, _table, _flags)	\
	अणु								\
		.shअगरt	= _shअगरt,					\
		.width	= _width,					\
		.flags	= _flags,					\
		.table	= _table,					\
	पूर्ण

#घोषणा _SUNXI_CCU_DIV_TABLE(_shअगरt, _width, _table)			\
	_SUNXI_CCU_DIV_TABLE_FLAGS(_shअगरt, _width, _table, 0)

#घोषणा _SUNXI_CCU_DIV_OFFSET_MAX_FLAGS(_shअगरt, _width, _off, _max, _flags) \
	अणु								\
		.shअगरt	= _shअगरt,					\
		.width	= _width,					\
		.flags	= _flags,					\
		.max	= _max,						\
		.offset	= _off,						\
	पूर्ण

#घोषणा _SUNXI_CCU_DIV_MAX_FLAGS(_shअगरt, _width, _max, _flags)		\
	_SUNXI_CCU_DIV_OFFSET_MAX_FLAGS(_shअगरt, _width, 1, _max, _flags)

#घोषणा _SUNXI_CCU_DIV_FLAGS(_shअगरt, _width, _flags)			\
	_SUNXI_CCU_DIV_MAX_FLAGS(_shअगरt, _width, 0, _flags)

#घोषणा _SUNXI_CCU_DIV_MAX(_shअगरt, _width, _max)			\
	_SUNXI_CCU_DIV_MAX_FLAGS(_shअगरt, _width, _max, 0)

#घोषणा _SUNXI_CCU_DIV_OFFSET(_shअगरt, _width, _offset)			\
	_SUNXI_CCU_DIV_OFFSET_MAX_FLAGS(_shअगरt, _width, _offset, 0, 0)

#घोषणा _SUNXI_CCU_DIV(_shअगरt, _width)					\
	_SUNXI_CCU_DIV_FLAGS(_shअगरt, _width, 0)

काष्ठा ccu_भाग अणु
	u32			enable;

	काष्ठा ccu_भाग_पूर्णांकernal	भाग;
	काष्ठा ccu_mux_पूर्णांकernal	mux;
	काष्ठा ccu_common	common;
	अचिन्हित पूर्णांक		fixed_post_भाग;
पूर्ण;

#घोषणा SUNXI_CCU_DIV_TABLE_WITH_GATE(_काष्ठा, _name, _parent, _reg,	\
				      _shअगरt, _width,			\
				      _table, _gate, _flags)		\
	काष्ठा ccu_भाग _काष्ठा = अणु					\
		.भाग		= _SUNXI_CCU_DIV_TABLE(_shअगरt, _width,	\
						       _table),		\
		.enable		= _gate,				\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_भाग_ops,	\
						      _flags),		\
		पूर्ण							\
	पूर्ण


#घोषणा SUNXI_CCU_DIV_TABLE(_काष्ठा, _name, _parent, _reg,		\
			    _shअगरt, _width,				\
			    _table, _flags)				\
	SUNXI_CCU_DIV_TABLE_WITH_GATE(_काष्ठा, _name, _parent, _reg,	\
				      _shअगरt, _width, _table, 0,	\
				      _flags)

#घोषणा SUNXI_CCU_M_WITH_MUX_TABLE_GATE(_काष्ठा, _name,			\
					_parents, _table,		\
					_reg,				\
					_mshअगरt, _mwidth,		\
					_muxshअगरt, _muxwidth,		\
					_gate, _flags)			\
	काष्ठा ccu_भाग _काष्ठा = अणु					\
		.enable	= _gate,					\
		.भाग	= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),		\
		.mux	= _SUNXI_CCU_MUX_TABLE(_muxshअगरt, _muxwidth, _table), \
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
							      _parents, \
							      &ccu_भाग_ops, \
							      _flags),	\
		पूर्ण,							\
	पूर्ण

#घोषणा SUNXI_CCU_M_WITH_MUX_GATE(_काष्ठा, _name, _parents, _reg,	\
				  _mshअगरt, _mwidth, _muxshअगरt, _muxwidth, \
				  _gate, _flags)			\
	SUNXI_CCU_M_WITH_MUX_TABLE_GATE(_काष्ठा, _name,			\
					_parents, शून्य,			\
					_reg, _mshअगरt, _mwidth,		\
					_muxshअगरt, _muxwidth,		\
					_gate, _flags)

#घोषणा SUNXI_CCU_M_WITH_MUX(_काष्ठा, _name, _parents, _reg,		\
			     _mshअगरt, _mwidth, _muxshअगरt, _muxwidth,	\
			     _flags)					\
	SUNXI_CCU_M_WITH_MUX_TABLE_GATE(_काष्ठा, _name,			\
					_parents, शून्य,			\
					_reg, _mshअगरt, _mwidth,		\
					_muxshअगरt, _muxwidth,		\
					0, _flags)


#घोषणा SUNXI_CCU_M_WITH_GATE(_काष्ठा, _name, _parent, _reg,		\
			      _mshअगरt, _mwidth,	_gate,			\
			      _flags)					\
	काष्ठा ccu_भाग _काष्ठा = अणु					\
		.enable	= _gate,					\
		.भाग	= _SUNXI_CCU_DIV(_mshअगरt, _mwidth),		\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_भाग_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

#घोषणा SUNXI_CCU_M(_काष्ठा, _name, _parent, _reg, _mshअगरt, _mwidth,	\
		    _flags)						\
	SUNXI_CCU_M_WITH_GATE(_काष्ठा, _name, _parent, _reg,		\
			      _mshअगरt, _mwidth, 0, _flags)

अटल अंतरभूत काष्ठा ccu_भाग *hw_to_ccu_भाग(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_भाग, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_भाग_ops;

#पूर्ण_अगर /* _CCU_DIV_H_ */
