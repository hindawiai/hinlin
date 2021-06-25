<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Spपढ़ोtrum composite घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#अगर_अघोषित _SPRD_COMPOSITE_H_
#घोषणा _SPRD_COMPOSITE_H_

#समावेश "common.h"
#समावेश "mux.h"
#समावेश "div.h"

काष्ठा sprd_comp अणु
	काष्ठा sprd_mux_ssel	mux;
	काष्ठा sprd_भाग_पूर्णांकernal	भाग;
	काष्ठा sprd_clk_common	common;
पूर्ण;

#घोषणा SPRD_COMP_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg, _table,	\
				 _mshअगरt, _mwidth, _dshअगरt, _dwidth,	\
				 _flags, _fn)				\
	काष्ठा sprd_comp _काष्ठा = अणु					\
		.mux	= _SPRD_MUX_CLK(_mshअगरt, _mwidth, _table),	\
		.भाग	= _SPRD_DIV_CLK(_dshअगरt, _dwidth),		\
		.common = अणु						\
			.regmap		= शून्य,				\
			.reg		= _reg,				\
			.hw.init = _fn(_name, _parent,			\
				       &sprd_comp_ops, _flags),		\
			 पूर्ण						\
	पूर्ण

#घोषणा SPRD_COMP_CLK_TABLE(_काष्ठा, _name, _parent, _reg, _table,	\
			    _mshअगरt, _mwidth, _dshअगरt, _dwidth, _flags)	\
	SPRD_COMP_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg, _table,	\
				 _mshअगरt, _mwidth, _dshअगरt, _dwidth,	\
				 _flags, CLK_HW_INIT_PARENTS)

#घोषणा SPRD_COMP_CLK(_काष्ठा, _name, _parent, _reg, _mshअगरt,		\
		      _mwidth, _dshअगरt, _dwidth, _flags)		\
	SPRD_COMP_CLK_TABLE(_काष्ठा, _name, _parent, _reg, शून्य,	\
			    _mshअगरt, _mwidth, _dshअगरt, _dwidth, _flags)

#घोषणा SPRD_COMP_CLK_DATA_TABLE(_काष्ठा, _name, _parent, _reg, _table,	\
				 _mshअगरt, _mwidth, _dshअगरt,		\
				 _dwidth, _flags)			\
	SPRD_COMP_CLK_HW_INIT_FN(_काष्ठा, _name, _parent, _reg, _table,	\
				 _mshअगरt, _mwidth, _dshअगरt, _dwidth,	\
				 _flags, CLK_HW_INIT_PARENTS_DATA)

#घोषणा SPRD_COMP_CLK_DATA(_काष्ठा, _name, _parent, _reg, _mshअगरt,	\
			   _mwidth, _dshअगरt, _dwidth, _flags)		\
	SPRD_COMP_CLK_DATA_TABLE(_काष्ठा, _name, _parent, _reg,	शून्य,	\
				 _mshअगरt, _mwidth, _dshअगरt, _dwidth,	\
				 _flags)

अटल अंतरभूत काष्ठा sprd_comp *hw_to_sprd_comp(स्थिर काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_clk_common *common = hw_to_sprd_clk_common(hw);

	वापस container_of(common, काष्ठा sprd_comp, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops sprd_comp_ops;

#पूर्ण_अगर /* _SPRD_COMPOSITE_H_ */
