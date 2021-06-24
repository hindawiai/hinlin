<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Marvell Berlin SoC pinctrl driver.
 *
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Antoine Tथऊnart <antoine.tenart@मुक्त-electrons.com>
 */

#अगर_अघोषित __PINCTRL_BERLIN_H
#घोषणा __PINCTRL_BERLIN_H

काष्ठा berlin_desc_function अणु
	स्थिर अक्षर	*name;
	u8		muxval;
पूर्ण;

काष्ठा berlin_desc_group अणु
	स्थिर अक्षर			*name;
	u8				offset;
	u8				bit_width;
	u8				lsb;
	काष्ठा berlin_desc_function	*functions;
पूर्ण;

काष्ठा berlin_pinctrl_desc अणु
	स्थिर काष्ठा berlin_desc_group	*groups;
	अचिन्हित			ngroups;
पूर्ण;

काष्ठा berlin_pinctrl_function अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	**groups;
	अचिन्हित	ngroups;
पूर्ण;

#घोषणा BERLIN_PINCTRL_GROUP(_name, _offset, _width, _lsb, ...)		\
	अणु								\
		.name = _name,						\
		.offset = _offset,					\
		.bit_width = _width,					\
		.lsb = _lsb,						\
		.functions = (काष्ठा berlin_desc_function[])अणु		\
			__VA_ARGS__, अणु पूर्ण पूर्ण,				\
	पूर्ण

#घोषणा BERLIN_PINCTRL_FUNCTION(_muxval, _name)		\
	अणु						\
		.name = _name,				\
		.muxval = _muxval,			\
	पूर्ण

#घोषणा BERLIN_PINCTRL_FUNCTION_UNKNOWN		अणुपूर्ण

पूर्णांक berlin_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा berlin_pinctrl_desc *desc);

पूर्णांक berlin_pinctrl_probe_regmap(काष्ठा platक्रमm_device *pdev,
				स्थिर काष्ठा berlin_pinctrl_desc *desc,
				काष्ठा regmap *regmap);

#पूर्ण_अगर /* __PINCTRL_BERLIN_H */
