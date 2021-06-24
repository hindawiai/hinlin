<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * w1-gpio पूर्णांकerface to platक्रमm code
 *
 * Copyright (C) 2007 Ville Syrjala <syrjala@sci.fi>
 */
#अगर_अघोषित _LINUX_W1_GPIO_H
#घोषणा _LINUX_W1_GPIO_H

काष्ठा gpio_desc;

/**
 * काष्ठा w1_gpio_platक्रमm_data - Platक्रमm-dependent data क्रम w1-gpio
 */
काष्ठा w1_gpio_platक्रमm_data अणु
	काष्ठा gpio_desc *gpiod;
	काष्ठा gpio_desc *pullup_gpiod;
	व्योम (*enable_बाह्यal_pullup)(पूर्णांक enable);
	अचिन्हित पूर्णांक pullup_duration;
पूर्ण;

#पूर्ण_अगर /* _LINUX_W1_GPIO_H */
