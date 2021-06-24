<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ or MIT) */
/*
 * Copyright (c) 2017 Baylibre SAS.
 * Author:  Jerome Brunet  <jbrunet@baylibre.com>
 *
 * Copyright (c) 2017 Amlogic, Inc. All rights reserved.
 * Author: Xingyu Chen <xingyu.chen@amlogic.com>
 *
 */

काष्ठा meson_pmx_bank अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक last;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक offset;
पूर्ण;

काष्ठा meson_axg_pmx_data अणु
	काष्ठा meson_pmx_bank *pmx_banks;
	अचिन्हित पूर्णांक num_pmx_banks;
पूर्ण;

#घोषणा BANK_PMX(n, f, l, r, o)				\
	अणु							\
		.name   = n,					\
		.first	= f,					\
		.last	= l,					\
		.reg	= r,					\
		.offset = o,					\
	पूर्ण

काष्ठा meson_pmx_axg_data अणु
        अचिन्हित पूर्णांक func;
पूर्ण;

#घोषणा PMX_DATA(f)							\
	अणु								\
		.func = f,						\
	पूर्ण

#घोषणा GROUP(grp, f)							\
	अणु								\
		.name = #grp,						\
		.pins = grp ## _pins,                                   \
		.num_pins = ARRAY_SIZE(grp ## _pins),			\
		.data = (स्थिर काष्ठा meson_pmx_axg_data[])अणु		\
			PMX_DATA(f),					\
		पूर्ण,							\
	पूर्ण

#घोषणा GPIO_GROUP(gpio)						\
	अणु								\
		.name = #gpio,						\
		.pins = (स्थिर अचिन्हित पूर्णांक[])अणु gpio पूर्ण,			\
		.num_pins = 1,						\
		.data = (स्थिर काष्ठा meson_pmx_axg_data[])अणु		\
			PMX_DATA(0),					\
		पूर्ण,							\
	पूर्ण

बाह्य स्थिर काष्ठा pinmux_ops meson_axg_pmx_ops;
