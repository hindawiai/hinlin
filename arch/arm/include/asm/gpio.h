<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_ARM_GPIO_H
#घोषणा _ARCH_ARM_GPIO_H

#अगर CONFIG_ARCH_NR_GPIO > 0
#घोषणा ARCH_NR_GPIOS CONFIG_ARCH_NR_GPIO
#पूर्ण_अगर

/* Note: this may rely upon the value of ARCH_NR_GPIOS set in mach/gpपन.स */
#समावेश <यंत्र-generic/gpपन.स>

/* The trivial gpiolib dispatchers */
#घोषणा gpio_get_value  __gpio_get_value
#घोषणा gpio_set_value  __gpio_set_value
#घोषणा gpio_cansleep   __gpio_cansleep

/*
 * Provide a शेष gpio_to_irq() which should satisfy every हाल.
 * However, some platक्रमms want to करो this dअगरferently, so allow them
 * to override it.
 */
#अगर_अघोषित gpio_to_irq
#घोषणा gpio_to_irq	__gpio_to_irq
#पूर्ण_अगर

#पूर्ण_अगर /* _ARCH_ARM_GPIO_H */
