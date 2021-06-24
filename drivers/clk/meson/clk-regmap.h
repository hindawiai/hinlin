<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित __CLK_REGMAP_H
#घोषणा __CLK_REGMAP_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>

/**
 * काष्ठा clk_regmap - regmap backed घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @map:	poपूर्णांकer to the regmap काष्ठाure controlling the घड़ी
 * @data:	data specअगरic to the घड़ी type
 *
 * Clock which is controlled by regmap backed रेजिस्टरs. The actual type of
 * of the घड़ी is controlled by the घड़ी_ops and data.
 */
काष्ठा clk_regmap अणु
	काष्ठा clk_hw	hw;
	काष्ठा regmap	*map;
	व्योम		*data;
पूर्ण;

अटल अंतरभूत काष्ठा clk_regmap *to_clk_regmap(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा clk_regmap, hw);
पूर्ण

/**
 * काष्ठा clk_regmap_gate_data - regmap backed gate specअगरic data
 *
 * @offset:	offset of the रेजिस्टर controlling gate
 * @bit_idx:	single bit controlling gate
 * @flags:	hardware-specअगरic flags
 *
 * Flags:
 * Same as clk_gate except CLK_GATE_HIWORD_MASK which is ignored
 */
काष्ठा clk_regmap_gate_data अणु
	अचिन्हित पूर्णांक	offset;
	u8		bit_idx;
	u8		flags;
पूर्ण;

अटल अंतरभूत काष्ठा clk_regmap_gate_data *
clk_get_regmap_gate_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा clk_regmap_gate_data *)clk->data;
पूर्ण

बाह्य स्थिर काष्ठा clk_ops clk_regmap_gate_ops;
बाह्य स्थिर काष्ठा clk_ops clk_regmap_gate_ro_ops;

/**
 * काष्ठा clk_regmap_भाग_data - regmap backed adjustable भागider specअगरic data
 *
 * @offset:	offset of the रेजिस्टर controlling the भागider
 * @shअगरt:	shअगरt to the भागider bit field
 * @width:	width of the भागider bit field
 * @table:	array of value/भागider pairs, last entry should have भाग = 0
 *
 * Flags:
 * Same as clk_भागider except CLK_DIVIDER_HIWORD_MASK which is ignored
 */
काष्ठा clk_regmap_भाग_data अणु
	अचिन्हित पूर्णांक	offset;
	u8		shअगरt;
	u8		width;
	u8		flags;
	स्थिर काष्ठा clk_भाग_प्रकारable	*table;
पूर्ण;

अटल अंतरभूत काष्ठा clk_regmap_भाग_data *
clk_get_regmap_भाग_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा clk_regmap_भाग_data *)clk->data;
पूर्ण

बाह्य स्थिर काष्ठा clk_ops clk_regmap_भागider_ops;
बाह्य स्थिर काष्ठा clk_ops clk_regmap_भागider_ro_ops;

/**
 * काष्ठा clk_regmap_mux_data - regmap backed multiplexer घड़ी specअगरic data
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @offset:	offset of theरेजिस्टर controlling multiplexer
 * @table:	array of parent indexed रेजिस्टर values
 * @shअगरt:	shअगरt to multiplexer bit field
 * @mask:	mask of mutliplexer bit field
 * @flags:	hardware-specअगरic flags
 *
 * Flags:
 * Same as clk_भागider except CLK_MUX_HIWORD_MASK which is ignored
 */
काष्ठा clk_regmap_mux_data अणु
	अचिन्हित पूर्णांक	offset;
	u32		*table;
	u32		mask;
	u8		shअगरt;
	u8		flags;
पूर्ण;

अटल अंतरभूत काष्ठा clk_regmap_mux_data *
clk_get_regmap_mux_data(काष्ठा clk_regmap *clk)
अणु
	वापस (काष्ठा clk_regmap_mux_data *)clk->data;
पूर्ण

बाह्य स्थिर काष्ठा clk_ops clk_regmap_mux_ops;
बाह्य स्थिर काष्ठा clk_ops clk_regmap_mux_ro_ops;

#घोषणा __MESON_PCLK(_name, _reg, _bit, _ops, _pname)			\
काष्ठा clk_regmap _name = अणु						\
	.data = &(काष्ठा clk_regmap_gate_data)अणु				\
		.offset = (_reg),					\
		.bit_idx = (_bit),					\
	पूर्ण,								\
	.hw.init = &(काष्ठा clk_init_data) अणु				\
		.name = #_name,						\
		.ops = _ops,						\
		.parent_hws = (स्थिर काष्ठा clk_hw *[]) अणु _pname पूर्ण,	\
		.num_parents = 1,					\
		.flags = (CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED),	\
	पूर्ण,								\
पूर्ण

#घोषणा MESON_PCLK(_name, _reg, _bit, _pname)	\
	__MESON_PCLK(_name, _reg, _bit, &clk_regmap_gate_ops, _pname)

#घोषणा MESON_PCLK_RO(_name, _reg, _bit, _pname)	\
	__MESON_PCLK(_name, _reg, _bit, &clk_regmap_gate_ro_ops, _pname)
#पूर्ण_अगर /* __CLK_REGMAP_H */
