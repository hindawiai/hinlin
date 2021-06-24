<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Socionext Inc.
 *   Author: Masahiro Yamada <yamada.masahiro@socionext.com>
 */

#अगर_अघोषित __CLK_UNIPHIER_H__
#घोषणा __CLK_UNIPHIER_H__

काष्ठा clk_hw;
काष्ठा device;
काष्ठा regmap;

#घोषणा UNIPHIER_CLK_CPUGEAR_MAX_PARENTS	16
#घोषणा UNIPHIER_CLK_MUX_MAX_PARENTS		8

क्रमागत uniphier_clk_type अणु
	UNIPHIER_CLK_TYPE_CPUGEAR,
	UNIPHIER_CLK_TYPE_FIXED_FACTOR,
	UNIPHIER_CLK_TYPE_FIXED_RATE,
	UNIPHIER_CLK_TYPE_GATE,
	UNIPHIER_CLK_TYPE_MUX,
पूर्ण;

काष्ठा uniphier_clk_cpugear_data अणु
	स्थिर अक्षर *parent_names[UNIPHIER_CLK_CPUGEAR_MAX_PARENTS];
	अचिन्हित पूर्णांक num_parents;
	अचिन्हित पूर्णांक regbase;
	अचिन्हित पूर्णांक mask;
पूर्ण;

काष्ठा uniphier_clk_fixed_factor_data अणु
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक भाग;
पूर्ण;

काष्ठा uniphier_clk_fixed_rate_data अणु
	अचिन्हित दीर्घ fixed_rate;
पूर्ण;

काष्ठा uniphier_clk_gate_data अणु
	स्थिर अक्षर *parent_name;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक bit;
पूर्ण;

काष्ठा uniphier_clk_mux_data अणु
	स्थिर अक्षर *parent_names[UNIPHIER_CLK_MUX_MAX_PARENTS];
	अचिन्हित पूर्णांक num_parents;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक masks[UNIPHIER_CLK_MUX_MAX_PARENTS];
	अचिन्हित पूर्णांक vals[UNIPHIER_CLK_MUX_MAX_PARENTS];
पूर्ण;

काष्ठा uniphier_clk_data अणु
	स्थिर अक्षर *name;
	क्रमागत uniphier_clk_type type;
	पूर्णांक idx;
	जोड़ अणु
		काष्ठा uniphier_clk_cpugear_data cpugear;
		काष्ठा uniphier_clk_fixed_factor_data factor;
		काष्ठा uniphier_clk_fixed_rate_data rate;
		काष्ठा uniphier_clk_gate_data gate;
		काष्ठा uniphier_clk_mux_data mux;
	पूर्ण data;
पूर्ण;

#घोषणा UNIPHIER_CLK_CPUGEAR(_name, _idx, _regbase, _mask,	\
			     _num_parents, ...)			\
	अणु							\
		.name = (_name),				\
		.type = UNIPHIER_CLK_TYPE_CPUGEAR,		\
		.idx = (_idx),					\
		.data.cpugear = अणु				\
			.parent_names = अणु __VA_ARGS__ पूर्ण,	\
			.num_parents = (_num_parents),		\
			.regbase = (_regbase),			\
			.mask = (_mask)				\
		 पूर्ण,						\
	पूर्ण

#घोषणा UNIPHIER_CLK_FACTOR(_name, _idx, _parent, _mult, _भाग)	\
	अणु							\
		.name = (_name),				\
		.type = UNIPHIER_CLK_TYPE_FIXED_FACTOR,		\
		.idx = (_idx),					\
		.data.factor = अणु				\
			.parent_name = (_parent),		\
			.mult = (_mult),			\
			.भाग = (_भाग),				\
		पूर्ण,						\
	पूर्ण

#घोषणा UNIPHIER_CLK_GATE(_name, _idx, _parent, _reg, _bit)	\
	अणु							\
		.name = (_name),				\
		.type = UNIPHIER_CLK_TYPE_GATE,			\
		.idx = (_idx),					\
		.data.gate = अणु					\
			.parent_name = (_parent),		\
			.reg = (_reg),				\
			.bit = (_bit),				\
		पूर्ण,						\
	पूर्ण

#घोषणा UNIPHIER_CLK_DIV(parent, भाग)				\
	UNIPHIER_CLK_FACTOR(parent "/" #भाग, -1, parent, 1, भाग)

#घोषणा UNIPHIER_CLK_DIV2(parent, भाग0, भाग1)			\
	UNIPHIER_CLK_DIV(parent, भाग0),				\
	UNIPHIER_CLK_DIV(parent, भाग1)

#घोषणा UNIPHIER_CLK_DIV3(parent, भाग0, भाग1, भाग2)		\
	UNIPHIER_CLK_DIV2(parent, भाग0, भाग1),			\
	UNIPHIER_CLK_DIV(parent, भाग2)

#घोषणा UNIPHIER_CLK_DIV4(parent, भाग0, भाग1, भाग2, भाग3)	\
	UNIPHIER_CLK_DIV2(parent, भाग0, भाग1),			\
	UNIPHIER_CLK_DIV2(parent, भाग2, भाग3)

काष्ठा clk_hw *uniphier_clk_रेजिस्टर_cpugear(काष्ठा device *dev,
					     काष्ठा regmap *regmap,
					     स्थिर अक्षर *name,
				स्थिर काष्ठा uniphier_clk_cpugear_data *data);
काष्ठा clk_hw *uniphier_clk_रेजिस्टर_fixed_factor(काष्ठा device *dev,
						  स्थिर अक्षर *name,
			स्थिर काष्ठा uniphier_clk_fixed_factor_data *data);
काष्ठा clk_hw *uniphier_clk_रेजिस्टर_fixed_rate(काष्ठा device *dev,
						स्थिर अक्षर *name,
			स्थिर काष्ठा uniphier_clk_fixed_rate_data *data);
काष्ठा clk_hw *uniphier_clk_रेजिस्टर_gate(काष्ठा device *dev,
					  काष्ठा regmap *regmap,
					  स्थिर अक्षर *name,
				स्थिर काष्ठा uniphier_clk_gate_data *data);
काष्ठा clk_hw *uniphier_clk_रेजिस्टर_mux(काष्ठा device *dev,
					 काष्ठा regmap *regmap,
					 स्थिर अक्षर *name,
				स्थिर काष्ठा uniphier_clk_mux_data *data);

बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_ld4_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_pro4_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_sld8_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_pro5_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_pxs2_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_ld11_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_ld20_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_pxs3_sys_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_ld4_mio_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_pro5_sd_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_ld4_peri_clk_data[];
बाह्य स्थिर काष्ठा uniphier_clk_data uniphier_pro4_peri_clk_data[];

#पूर्ण_अगर /* __CLK_UNIPHIER_H__ */
