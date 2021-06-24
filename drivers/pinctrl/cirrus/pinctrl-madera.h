<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Pinctrl क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2016-2017 Cirrus Logic
 */

#अगर_अघोषित PINCTRL_MADERA_H
#घोषणा PINCTRL_MADERA_H

काष्ठा madera_pin_groups अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	अचिन्हित पूर्णांक n_pins;
पूर्ण;

काष्ठा madera_pin_chip अणु
	अचिन्हित पूर्णांक n_pins;

	स्थिर काष्ठा madera_pin_groups *pin_groups;
	अचिन्हित पूर्णांक n_pin_groups;
पूर्ण;

काष्ठा madera_pin_निजी अणु
	काष्ठा madera *madera;

	स्थिर काष्ठा madera_pin_chip *chip; /* chip-specअगरic groups */

	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
पूर्ण;

बाह्य स्थिर काष्ठा madera_pin_chip cs47l15_pin_chip;
बाह्य स्थिर काष्ठा madera_pin_chip cs47l35_pin_chip;
बाह्य स्थिर काष्ठा madera_pin_chip cs47l85_pin_chip;
बाह्य स्थिर काष्ठा madera_pin_chip cs47l90_pin_chip;
बाह्य स्थिर काष्ठा madera_pin_chip cs47l92_pin_chip;

#पूर्ण_अगर
