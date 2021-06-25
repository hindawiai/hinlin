<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Google, Inc.
 */

#अगर_अघोषित __PISTACHIO_CLK_H
#घोषणा __PISTACHIO_CLK_H

#समावेश <linux/clk-provider.h>

काष्ठा pistachio_gate अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ reg;
	अचिन्हित पूर्णांक shअगरt;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
पूर्ण;

#घोषणा GATE(_id, _name, _pname, _reg, _shअगरt)	\
	अणु					\
		.id	= _id,			\
		.reg	= _reg,			\
		.shअगरt	= _shअगरt,		\
		.name	= _name,		\
		.parent = _pname,		\
	पूर्ण

काष्ठा pistachio_mux अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ reg;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक num_parents;
	स्थिर अक्षर *name;
	स्थिर अक्षर **parents;
पूर्ण;

#घोषणा PNAME(x) अटल स्थिर अक्षर *x[] __initस्थिर

#घोषणा MUX(_id, _name, _pnames, _reg, _shअगरt)			\
	अणु							\
		.id		= _id,				\
		.reg		= _reg,				\
		.shअगरt		= _shअगरt,			\
		.name		= _name,			\
		.parents	= _pnames,			\
		.num_parents	= ARRAY_SIZE(_pnames)		\
	पूर्ण


काष्ठा pistachio_भाग अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ reg;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक भाग_flags;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
पूर्ण;

#घोषणा DIV(_id, _name, _pname, _reg, _width)			\
	अणु							\
		.id		= _id,				\
		.reg		= _reg,				\
		.width		= _width,			\
		.भाग_flags	= 0,				\
		.name		= _name,			\
		.parent		= _pname,			\
	पूर्ण

#घोषणा DIV_F(_id, _name, _pname, _reg, _width, _भाग_flags)	\
	अणु							\
		.id		= _id,				\
		.reg		= _reg,				\
		.width		= _width,			\
		.भाग_flags	= _भाग_flags,			\
		.name		= _name,			\
		.parent		= _pname,			\
	पूर्ण

काष्ठा pistachio_fixed_factor अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक भाग;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
पूर्ण;

#घोषणा FIXED_FACTOR(_id, _name, _pname, _भाग)			\
	अणु							\
		.id		= _id,				\
		.भाग		= _भाग,				\
		.name		= _name,			\
		.parent		= _pname,			\
	पूर्ण

काष्ठा pistachio_pll_rate_table अणु
	अचिन्हित दीर्घ दीर्घ fref;
	अचिन्हित दीर्घ दीर्घ fout;
	अचिन्हित दीर्घ दीर्घ refभाग;
	अचिन्हित दीर्घ दीर्घ fbभाग;
	अचिन्हित दीर्घ दीर्घ postभाग1;
	अचिन्हित दीर्घ दीर्घ postभाग2;
	अचिन्हित दीर्घ दीर्घ frac;
पूर्ण;

क्रमागत pistachio_pll_type अणु
	PLL_GF40LP_LAINT,
	PLL_GF40LP_FRAC,
पूर्ण;

काष्ठा pistachio_pll अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ reg_base;
	क्रमागत pistachio_pll_type type;
	काष्ठा pistachio_pll_rate_table *rates;
	अचिन्हित पूर्णांक nr_rates;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent;
पूर्ण;

#घोषणा PLL(_id, _name, _pname, _type, _reg, _rates)		\
	अणु							\
		.id		= _id,				\
		.reg_base	= _reg,				\
		.type		= _type,			\
		.rates		= _rates,			\
		.nr_rates	= ARRAY_SIZE(_rates),		\
		.name		= _name,			\
		.parent		= _pname,			\
	पूर्ण

#घोषणा PLL_FIXED(_id, _name, _pname, _type, _reg)		\
	अणु							\
		.id		= _id,				\
		.reg_base	= _reg,				\
		.type		= _type,			\
		.rates		= शून्य,				\
		.nr_rates	= 0,				\
		.name		= _name,			\
		.parent		= _pname,			\
	पूर्ण

काष्ठा pistachio_clk_provider अणु
	काष्ठा device_node *node;
	व्योम __iomem *base;
	काष्ठा clk_onecell_data clk_data;
पूर्ण;

बाह्य काष्ठा pistachio_clk_provider *
pistachio_clk_alloc_provider(काष्ठा device_node *node, अचिन्हित पूर्णांक num_clks);
बाह्य व्योम pistachio_clk_रेजिस्टर_provider(काष्ठा pistachio_clk_provider *p);

बाह्य व्योम pistachio_clk_रेजिस्टर_gate(काष्ठा pistachio_clk_provider *p,
					काष्ठा pistachio_gate *gate,
					अचिन्हित पूर्णांक num);
बाह्य व्योम pistachio_clk_रेजिस्टर_mux(काष्ठा pistachio_clk_provider *p,
				       काष्ठा pistachio_mux *mux,
				       अचिन्हित पूर्णांक num);
बाह्य व्योम pistachio_clk_रेजिस्टर_भाग(काष्ठा pistachio_clk_provider *p,
				       काष्ठा pistachio_भाग *भाग,
				       अचिन्हित पूर्णांक num);
बाह्य व्योम
pistachio_clk_रेजिस्टर_fixed_factor(काष्ठा pistachio_clk_provider *p,
				    काष्ठा pistachio_fixed_factor *ff,
				    अचिन्हित पूर्णांक num);
बाह्य व्योम pistachio_clk_रेजिस्टर_pll(काष्ठा pistachio_clk_provider *p,
				       काष्ठा pistachio_pll *pll,
				       अचिन्हित पूर्णांक num);

बाह्य व्योम pistachio_clk_क्रमce_enable(काष्ठा pistachio_clk_provider *p,
				       अचिन्हित पूर्णांक *clk_ids, अचिन्हित पूर्णांक num);

#पूर्ण_अगर
