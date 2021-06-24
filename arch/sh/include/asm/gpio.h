<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *  include/यंत्र-sh/gpपन.स
 *
 * Generic GPIO API and pinmux table support क्रम SuperH.
 *
 * Copyright (c) 2008 Magnus Damm
 */
#अगर_अघोषित __ASM_SH_GPIO_H
#घोषणा __ASM_SH_GPIO_H

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>

#अगर defined(CONFIG_CPU_SH3)
#समावेश <cpu/gpपन.स>
#पूर्ण_अगर

#समावेश <यंत्र-generic/gpपन.स>

#अगर_घोषित CONFIG_GPIOLIB

अटल अंतरभूत पूर्णांक gpio_get_value(अचिन्हित gpio)
अणु
	वापस __gpio_get_value(gpio);
पूर्ण

अटल अंतरभूत व्योम gpio_set_value(अचिन्हित gpio, पूर्णांक value)
अणु
	__gpio_set_value(gpio, value);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_cansleep(अचिन्हित gpio)
अणु
	वापस __gpio_cansleep(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_to_irq(अचिन्हित gpio)
अणु
	वापस __gpio_to_irq(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक irq_to_gpio(अचिन्हित पूर्णांक irq)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_GPIOLIB */

#पूर्ण_अगर /* __ASM_SH_GPIO_H */
