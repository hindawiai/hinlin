<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#अगर_अघोषित __DRV_CLK_MTK_H
#घोषणा __DRV_CLK_MTK_H

#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk-provider.h>

काष्ठा clk;
काष्ठा clk_onecell_data;

#घोषणा MAX_MUX_GATE_BIT	31
#घोषणा INVALID_MUX_GATE_BIT	(MAX_MUX_GATE_BIT + 1)

#घोषणा MHZ (1000 * 1000)

काष्ठा mtk_fixed_clk अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
	अचिन्हित दीर्घ rate;
पूर्ण;

#घोषणा FIXED_CLK(_id, _name, _parent, _rate) अणु		\
		.id = _id,				\
		.name = _name,				\
		.parent = _parent,			\
		.rate = _rate,				\
	पूर्ण

व्योम mtk_clk_रेजिस्टर_fixed_clks(स्थिर काष्ठा mtk_fixed_clk *clks,
		पूर्णांक num, काष्ठा clk_onecell_data *clk_data);

काष्ठा mtk_fixed_factor अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	पूर्णांक mult;
	पूर्णांक भाग;
पूर्ण;

#घोषणा FACTOR(_id, _name, _parent, _mult, _भाग) अणु	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.mult = _mult,				\
		.भाग = _भाग,				\
	पूर्ण

व्योम mtk_clk_रेजिस्टर_factors(स्थिर काष्ठा mtk_fixed_factor *clks,
		पूर्णांक num, काष्ठा clk_onecell_data *clk_data);

काष्ठा mtk_composite अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_names;
	स्थिर अक्षर *parent;
	अचिन्हित flags;

	uपूर्णांक32_t mux_reg;
	uपूर्णांक32_t भागider_reg;
	uपूर्णांक32_t gate_reg;

	चिन्हित अक्षर mux_shअगरt;
	चिन्हित अक्षर mux_width;
	चिन्हित अक्षर gate_shअगरt;

	चिन्हित अक्षर भागider_shअगरt;
	चिन्हित अक्षर भागider_width;

	u8 mux_flags;

	चिन्हित अक्षर num_parents;
पूर्ण;

#घोषणा MUX_GATE_FLAGS_2(_id, _name, _parents, _reg, _shअगरt,		\
				_width, _gate, _flags, _muxflags) अणु	\
		.id = _id,						\
		.name = _name,						\
		.mux_reg = _reg,					\
		.mux_shअगरt = _shअगरt,					\
		.mux_width = _width,					\
		.gate_reg = _reg,					\
		.gate_shअगरt = _gate,					\
		.भागider_shअगरt = -1,					\
		.parent_names = _parents,				\
		.num_parents = ARRAY_SIZE(_parents),			\
		.flags = _flags,					\
		.mux_flags = _muxflags,					\
	पूर्ण

/*
 * In हाल the rate change propagation to parent घड़ीs is undesirable,
 * this macro allows to specअगरy the घड़ी flags manually.
 */
#घोषणा MUX_GATE_FLAGS(_id, _name, _parents, _reg, _shअगरt, _width,	\
			_gate, _flags)					\
		MUX_GATE_FLAGS_2(_id, _name, _parents, _reg,		\
					_shअगरt, _width, _gate, _flags, 0)

/*
 * Unless necessary, all MUX_GATE घड़ीs propagate rate changes to their
 * parent घड़ी by शेष.
 */
#घोषणा MUX_GATE(_id, _name, _parents, _reg, _shअगरt, _width, _gate)	\
	MUX_GATE_FLAGS(_id, _name, _parents, _reg, _shअगरt, _width,	\
		_gate, CLK_SET_RATE_PARENT)

#घोषणा MUX(_id, _name, _parents, _reg, _shअगरt, _width)			\
	MUX_FLAGS(_id, _name, _parents, _reg,				\
		  _shअगरt, _width, CLK_SET_RATE_PARENT)

#घोषणा MUX_FLAGS(_id, _name, _parents, _reg, _shअगरt, _width, _flags) अणु	\
		.id = _id,						\
		.name = _name,						\
		.mux_reg = _reg,					\
		.mux_shअगरt = _shअगरt,					\
		.mux_width = _width,					\
		.gate_shअगरt = -1,					\
		.भागider_shअगरt = -1,					\
		.parent_names = _parents,				\
		.num_parents = ARRAY_SIZE(_parents),			\
		.flags = _flags,				\
	पूर्ण

#घोषणा DIV_GATE(_id, _name, _parent, _gate_reg, _gate_shअगरt, _भाग_reg,	\
					_भाग_width, _भाग_shअगरt) अणु	\
		.id = _id,						\
		.parent = _parent,					\
		.name = _name,						\
		.भागider_reg = _भाग_reg,				\
		.भागider_shअगरt = _भाग_shअगरt,				\
		.भागider_width = _भाग_width,				\
		.gate_reg = _gate_reg,					\
		.gate_shअगरt = _gate_shअगरt,				\
		.mux_shअगरt = -1,					\
		.flags = 0,						\
	पूर्ण

काष्ठा clk *mtk_clk_रेजिस्टर_composite(स्थिर काष्ठा mtk_composite *mc,
		व्योम __iomem *base, spinlock_t *lock);

व्योम mtk_clk_रेजिस्टर_composites(स्थिर काष्ठा mtk_composite *mcs,
		पूर्णांक num, व्योम __iomem *base, spinlock_t *lock,
		काष्ठा clk_onecell_data *clk_data);

काष्ठा mtk_gate_regs अणु
	u32 sta_ofs;
	u32 clr_ofs;
	u32 set_ofs;
पूर्ण;

काष्ठा mtk_gate अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	स्थिर काष्ठा mtk_gate_regs *regs;
	पूर्णांक shअगरt;
	स्थिर काष्ठा clk_ops *ops;
	अचिन्हित दीर्घ flags;
पूर्ण;

पूर्णांक mtk_clk_रेजिस्टर_gates(काष्ठा device_node *node,
			स्थिर काष्ठा mtk_gate *clks, पूर्णांक num,
			काष्ठा clk_onecell_data *clk_data);

पूर्णांक mtk_clk_रेजिस्टर_gates_with_dev(काष्ठा device_node *node,
		स्थिर काष्ठा mtk_gate *clks,
		पूर्णांक num, काष्ठा clk_onecell_data *clk_data,
		काष्ठा device *dev);

काष्ठा mtk_clk_भागider अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;

	u32 भाग_reg;
	अचिन्हित अक्षर भाग_shअगरt;
	अचिन्हित अक्षर भाग_width;
	अचिन्हित अक्षर clk_भागider_flags;
	स्थिर काष्ठा clk_भाग_प्रकारable *clk_भाग_प्रकारable;
पूर्ण;

#घोषणा DIV_ADJ(_id, _name, _parent, _reg, _shअगरt, _width) अणु	\
		.id = _id,					\
		.name = _name,					\
		.parent_name = _parent,				\
		.भाग_reg = _reg,				\
		.भाग_shअगरt = _shअगरt,				\
		.भाग_width = _width,				\
पूर्ण

व्योम mtk_clk_रेजिस्टर_भागiders(स्थिर काष्ठा mtk_clk_भागider *mcds,
			पूर्णांक num, व्योम __iomem *base, spinlock_t *lock,
				काष्ठा clk_onecell_data *clk_data);

काष्ठा clk_onecell_data *mtk_alloc_clk_data(अचिन्हित पूर्णांक clk_num);

#घोषणा HAVE_RST_BAR	BIT(0)
#घोषणा PLL_AO		BIT(1)

काष्ठा mtk_pll_भाग_प्रकारable अणु
	u32 भाग;
	अचिन्हित दीर्घ freq;
पूर्ण;

काष्ठा mtk_pll_data अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	uपूर्णांक32_t reg;
	uपूर्णांक32_t pwr_reg;
	uपूर्णांक32_t en_mask;
	uपूर्णांक32_t pd_reg;
	uपूर्णांक32_t tuner_reg;
	uपूर्णांक32_t tuner_en_reg;
	uपूर्णांक8_t tuner_en_bit;
	पूर्णांक pd_shअगरt;
	अचिन्हित पूर्णांक flags;
	स्थिर काष्ठा clk_ops *ops;
	u32 rst_bar_mask;
	अचिन्हित दीर्घ fmin;
	अचिन्हित दीर्घ fmax;
	पूर्णांक pcwbits;
	पूर्णांक pcwibits;
	uपूर्णांक32_t pcw_reg;
	पूर्णांक pcw_shअगरt;
	uपूर्णांक32_t pcw_chg_reg;
	स्थिर काष्ठा mtk_pll_भाग_प्रकारable *भाग_प्रकारable;
	स्थिर अक्षर *parent_name;
पूर्ण;

व्योम mtk_clk_रेजिस्टर_plls(काष्ठा device_node *node,
		स्थिर काष्ठा mtk_pll_data *plls, पूर्णांक num_plls,
		काष्ठा clk_onecell_data *clk_data);

काष्ठा clk *mtk_clk_रेजिस्टर_ref2usb_tx(स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name, व्योम __iomem *reg);

व्योम mtk_रेजिस्टर_reset_controller(काष्ठा device_node *np,
			अचिन्हित पूर्णांक num_regs, पूर्णांक regofs);

व्योम mtk_रेजिस्टर_reset_controller_set_clr(काष्ठा device_node *np,
	अचिन्हित पूर्णांक num_regs, पूर्णांक regofs);

#पूर्ण_अगर /* __DRV_CLK_MTK_H */
