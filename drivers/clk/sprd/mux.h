<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Spपढ़ोtrum multiplexer घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#अगर_अघोषित _SPRD_MUX_H_
#घोषणा _SPRD_MUX_H_

#समावेश "common.h"

/**
 * काष्ठा sprd_mux_ssel - Mux घड़ी's source select bits in its रेजिस्टर
 * @shअगरt: Bit offset of the भागider in its रेजिस्टर
 * @width: Width of the भागider field in its रेजिस्टर
 * @table: For some mux घड़ीs, not all sources are used on some special
 *	   chips, this matches the value of mux घड़ी's रेजिस्टर and the
 *	   sources which are used क्रम this mux घड़ी
 */
काष्ठा sprd_mux_ssel अणु
	u8		shअगरt;
	u8		width;
	स्थिर u8	*table;
पूर्ण;

काष्ठा sprd_mux अणु
	काष्ठा sprd_mux_ssel mux;
	काष्ठा sprd_clk_common	common;
पूर्ण;

#घोषणा _SPRD_MUX_CLK(_shअगरt, _width, _table)		\
	अणु						\
		.shअगरt	= _shअगरt,			\
		.width	= _width,			\
		.table	= _table,			\
	पूर्ण

#घोषणा SPRD_MUX_CLK_HW_INIT_FN(_काष्ठा, _name, _parents, _table,	\
				_reg, _shअगरt, _width, _flags, _fn)	\
	काष्ठा sprd_mux _काष्ठा = अणु					\
		.mux	= _SPRD_MUX_CLK(_shअगरt, _width, _table),	\
		.common	= अणु						\
			.regmap		= शून्य,				\
			.reg		= _reg,				\
			.hw.init = _fn(_name, _parents,			\
				       &sprd_mux_ops, _flags),		\
		पूर्ण							\
	पूर्ण

#घोषणा SPRD_MUX_CLK_TABLE(_काष्ठा, _name, _parents, _table,		\
			   _reg, _shअगरt, _width, _flags)		\
	SPRD_MUX_CLK_HW_INIT_FN(_काष्ठा, _name, _parents, _table,	\
				_reg, _shअगरt, _width, _flags,		\
				CLK_HW_INIT_PARENTS)

#घोषणा SPRD_MUX_CLK(_काष्ठा, _name, _parents, _reg,		\
		     _shअगरt, _width, _flags)			\
	SPRD_MUX_CLK_TABLE(_काष्ठा, _name, _parents, शून्य,	\
			   _reg, _shअगरt, _width, _flags)

#घोषणा SPRD_MUX_CLK_DATA_TABLE(_काष्ठा, _name, _parents, _table,	\
				_reg, _shअगरt, _width, _flags)		\
	SPRD_MUX_CLK_HW_INIT_FN(_काष्ठा, _name, _parents, _table,	\
				_reg, _shअगरt, _width, _flags,		\
				CLK_HW_INIT_PARENTS_DATA)

#घोषणा SPRD_MUX_CLK_DATA(_काष्ठा, _name, _parents, _reg,		\
			  _shअगरt, _width, _flags)			\
	SPRD_MUX_CLK_DATA_TABLE(_काष्ठा, _name, _parents, शून्य,		\
				_reg, _shअगरt, _width, _flags)

अटल अंतरभूत काष्ठा sprd_mux *hw_to_sprd_mux(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_clk_common *common = hw_to_sprd_clk_common(hw);

	वापस container_of(common, काष्ठा sprd_mux, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops sprd_mux_ops;

u8 sprd_mux_helper_get_parent(स्थिर काष्ठा sprd_clk_common *common,
			      स्थिर काष्ठा sprd_mux_ssel *mux);
पूर्णांक sprd_mux_helper_set_parent(स्थिर काष्ठा sprd_clk_common *common,
			       स्थिर काष्ठा sprd_mux_ssel *mux,
			       u8 index);

#पूर्ण_अगर /* _SPRD_MUX_H_ */
