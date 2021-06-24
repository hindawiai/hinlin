<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __GPIO_PXA_H
#घोषणा __GPIO_PXA_H

#घोषणा GPIO_bit(x)	(1 << ((x) & 0x1f))

#घोषणा gpio_to_bank(gpio)	((gpio) >> 5)

/* NOTE: some PXAs have fewer on-chip GPIOs (like PXA255, with 85).
 * Those हालs currently cause holes in the GPIO number space, the
 * actual number of the last GPIO is recorded by 'pxa_last_gpio'.
 */
बाह्य पूर्णांक pxa_last_gpio;

बाह्य पूर्णांक pxa_irq_to_gpio(पूर्णांक irq);

काष्ठा pxa_gpio_platक्रमm_data अणु
	पूर्णांक irq_base;
	पूर्णांक (*gpio_set_wake)(अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक on);
पूर्ण;

#पूर्ण_अगर /* __GPIO_PXA_H */
