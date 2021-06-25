<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * First generation of pinmux driver क्रम Amlogic Meson SoCs
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 * Copyright (C) 2017 Jerome Brunet  <jbrunet@baylibre.com>
 */

काष्ठा meson8_pmx_data अणु
	bool is_gpio;
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक bit;
पूर्ण;

#घोषणा PMX_DATA(r, b, g)						\
	अणु								\
		.reg = r,						\
		.bit = b,						\
		.is_gpio = g,						\
	पूर्ण

#घोषणा GROUP(grp, r, b)						\
	अणु								\
		.name = #grp,						\
		.pins = grp ## _pins,					\
		.num_pins = ARRAY_SIZE(grp ## _pins),			\
		.data = (स्थिर काष्ठा meson8_pmx_data[])अणु		\
			PMX_DATA(r, b, false),				\
		पूर्ण,							\
	 पूर्ण

#घोषणा GPIO_GROUP(gpio)						\
	अणु								\
		.name = #gpio,						\
		.pins = (स्थिर अचिन्हित पूर्णांक[])अणु gpio पूर्ण,			\
		.num_pins = 1,						\
		.data = (स्थिर काष्ठा meson8_pmx_data[])अणु		\
			PMX_DATA(0, 0, true),				\
		पूर्ण,							\
	पूर्ण

बाह्य स्थिर काष्ठा pinmux_ops meson8_pmx_ops;
