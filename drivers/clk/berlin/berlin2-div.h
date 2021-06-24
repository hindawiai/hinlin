<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 */
#अगर_अघोषित __BERLIN2_DIV_H
#घोषणा __BERLIN2_DIV_H

काष्ठा clk_hw;

#घोषणा BERLIN2_DIV_HAS_GATE		BIT(0)
#घोषणा BERLIN2_DIV_HAS_MUX		BIT(1)

#घोषणा BERLIN2_PLL_SELECT(_off, _sh)	\
	.pll_select_offs = _off,	\
	.pll_select_shअगरt = _sh

#घोषणा BERLIN2_PLL_SWITCH(_off, _sh)	\
	.pll_चयन_offs = _off,	\
	.pll_चयन_shअगरt = _sh

#घोषणा BERLIN2_DIV_SELECT(_off, _sh)	\
	.भाग_select_offs = _off,	\
	.भाग_select_shअगरt = _sh

#घोषणा BERLIN2_DIV_SWITCH(_off, _sh)	\
	.भाग_चयन_offs = _off,	\
	.भाग_चयन_shअगरt = _sh

#घोषणा BERLIN2_DIV_D3SWITCH(_off, _sh)	\
	.भाग3_चयन_offs = _off,	\
	.भाग3_चयन_shअगरt = _sh

#घोषणा BERLIN2_DIV_GATE(_off, _sh)	\
	.gate_offs = _off,		\
	.gate_shअगरt = _sh

#घोषणा BERLIN2_SINGLE_DIV(_off)	\
	BERLIN2_DIV_GATE(_off, 0),	\
	BERLIN2_PLL_SELECT(_off, 1),	\
	BERLIN2_PLL_SWITCH(_off, 4),	\
	BERLIN2_DIV_SWITCH(_off, 5),	\
	BERLIN2_DIV_D3SWITCH(_off, 6),	\
	BERLIN2_DIV_SELECT(_off, 7)

काष्ठा berlin2_भाग_map अणु
	u16 pll_select_offs;
	u16 pll_चयन_offs;
	u16 भाग_select_offs;
	u16 भाग_चयन_offs;
	u16 भाग3_चयन_offs;
	u16 gate_offs;
	u8 pll_select_shअगरt;
	u8 pll_चयन_shअगरt;
	u8 भाग_select_shअगरt;
	u8 भाग_चयन_shअगरt;
	u8 भाग3_चयन_shअगरt;
	u8 gate_shअगरt;
पूर्ण;

काष्ठा berlin2_भाग_data अणु
	स्थिर अक्षर *name;
	स्थिर u8 *parent_ids;
	पूर्णांक num_parents;
	अचिन्हित दीर्घ flags;
	काष्ठा berlin2_भाग_map map;
	u8 भाग_flags;
पूर्ण;

काष्ठा clk_hw *
berlin2_भाग_रेजिस्टर(स्थिर काष्ठा berlin2_भाग_map *map,
	     व्योम __iomem *base,  स्थिर अक्षर *name, u8 भाग_flags,
	     स्थिर अक्षर **parent_names, पूर्णांक num_parents,
	     अचिन्हित दीर्घ flags,  spinlock_t *lock);

#पूर्ण_अगर /* __BERLIN2_DIV_H */
