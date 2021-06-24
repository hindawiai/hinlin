<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Spपढ़ोtrum भागider घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#अगर_अघोषित _SPRD_DIV_H_
#घोषणा _SPRD_DIV_H_

#समावेश "common.h"

/**
 * काष्ठा sprd_भाग_पूर्णांकernal - Internal भागider description
 * @shअगरt: Bit offset of the भागider in its रेजिस्टर
 * @width: Width of the भागider field in its रेजिस्टर
 *
 * That काष्ठाure represents a single भागider, and is meant to be
 * embedded in other काष्ठाures representing the various घड़ी
 * classes.
 */
काष्ठा sprd_भाग_पूर्णांकernal अणु
	u8	shअगरt;
	u8	width;
पूर्ण;

#घोषणा _SPRD_DIV_CLK(_shअगरt, _width)	\
	अणु				\
		.shअगरt	= _shअगरt,	\
		.width	= _width,	\
	पूर्ण

काष्ठा sprd_भाग अणु
	काष्ठा sprd_भाग_पूर्णांकernal	भाग;
	काष्ठा sprd_clk_common	common;
पूर्ण;

#घोषणा SPRD_DIV_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,		\
				_shअगरt, _width, _flags, _fn)		\
	काष्ठा sprd_भाग _काष्ठा = अणु					\
		.भाग	= _SPRD_DIV_CLK(_shअगरt, _width),		\
		.common	= अणु						\
			.regmap		= शून्य,				\
			.reg		= _reg,				\
			.hw.init	= _fn(_name, _parent,		\
					      &sprd_भाग_ops, _flags),	\
		पूर्ण							\
	पूर्ण

#घोषणा SPRD_DIV_CLK(_काष्ठा, _name, _parent, _reg,			\
		     _shअगरt, _width, _flags)				\
	SPRD_DIV_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,		\
				_shअगरt, _width, _flags, CLK_HW_INIT)

#घोषणा SPRD_DIV_CLK_HW(_काष्ठा, _name, _parent, _reg,			\
			_shअगरt, _width, _flags)				\
	SPRD_DIV_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg,		\
				_shअगरt, _width, _flags, CLK_HW_INIT_HW)

अटल अंतरभूत काष्ठा sprd_भाग *hw_to_sprd_भाग(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_clk_common *common = hw_to_sprd_clk_common(hw);

	वापस container_of(common, काष्ठा sprd_भाग, common);
पूर्ण

दीर्घ sprd_भाग_helper_round_rate(काष्ठा sprd_clk_common *common,
				स्थिर काष्ठा sprd_भाग_पूर्णांकernal *भाग,
				अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate);

अचिन्हित दीर्घ sprd_भाग_helper_recalc_rate(काष्ठा sprd_clk_common *common,
					  स्थिर काष्ठा sprd_भाग_पूर्णांकernal *भाग,
					  अचिन्हित दीर्घ parent_rate);

पूर्णांक sprd_भाग_helper_set_rate(स्थिर काष्ठा sprd_clk_common *common,
			     स्थिर काष्ठा sprd_भाग_पूर्णांकernal *भाग,
			     अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate);

बाह्य स्थिर काष्ठा clk_ops sprd_भाग_ops;

#पूर्ण_अगर /* _SPRD_DIV_H_ */
