<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Helpers क्रम controlling modem lines via GPIO
 *
 * Copyright (C) 2014 Paratronic S.A.
 */

#अगर_अघोषित __SERIAL_MCTRL_GPIO__
#घोषणा __SERIAL_MCTRL_GPIO__

#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>

काष्ठा uart_port;

क्रमागत mctrl_gpio_idx अणु
	UART_GPIO_CTS,
	UART_GPIO_DSR,
	UART_GPIO_DCD,
	UART_GPIO_RNG,
	UART_GPIO_RI = UART_GPIO_RNG,
	UART_GPIO_RTS,
	UART_GPIO_DTR,
	UART_GPIO_MAX,
पूर्ण;

/*
 * Opaque descriptor क्रम modem lines controlled by GPIOs
 */
काष्ठा mctrl_gpios;

#अगर_घोषित CONFIG_GPIOLIB

/*
 * Set state of the modem control output lines via GPIOs.
 */
व्योम mctrl_gpio_set(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक mctrl);

/*
 * Get state of the modem control input lines from GPIOs.
 * The mctrl flags are updated and वापसed.
 */
अचिन्हित पूर्णांक mctrl_gpio_get(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक *mctrl);

/*
 * Get state of the modem control output lines from GPIOs.
 * The mctrl flags are updated and वापसed.
 */
अचिन्हित पूर्णांक
mctrl_gpio_get_outमाला_दो(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक *mctrl);

/*
 * Returns the associated काष्ठा gpio_desc to the modem line gidx
 */
काष्ठा gpio_desc *mctrl_gpio_to_gpiod(काष्ठा mctrl_gpios *gpios,
				      क्रमागत mctrl_gpio_idx gidx);

/*
 * Request and set direction of modem control line GPIOs and set up irq
 * handling.
 * devm_* functions are used, so there's no need to call mctrl_gpio_मुक्त().
 * Returns a poपूर्णांकer to the allocated mctrl काष्ठाure अगर ok, -ENOMEM on
 * allocation error.
 */
काष्ठा mctrl_gpios *mctrl_gpio_init(काष्ठा uart_port *port, अचिन्हित पूर्णांक idx);

/*
 * Request and set direction of modem control line GPIOs.
 * devm_* functions are used, so there's no need to call mctrl_gpio_मुक्त().
 * Returns a poपूर्णांकer to the allocated mctrl काष्ठाure अगर ok, -ENOMEM on
 * allocation error.
 */
काष्ठा mctrl_gpios *mctrl_gpio_init_noस्वतः(काष्ठा device *dev,
					   अचिन्हित पूर्णांक idx);

/*
 * Free the mctrl_gpios काष्ठाure.
 * Normally, this function will not be called, as the GPIOs will
 * be disposed of by the resource management code.
 */
व्योम mctrl_gpio_मुक्त(काष्ठा device *dev, काष्ठा mctrl_gpios *gpios);

/*
 * Enable gpio पूर्णांकerrupts to report status line changes.
 */
व्योम mctrl_gpio_enable_ms(काष्ठा mctrl_gpios *gpios);

/*
 * Disable gpio पूर्णांकerrupts to report status line changes.
 */
व्योम mctrl_gpio_disable_ms(काष्ठा mctrl_gpios *gpios);

#अन्यथा /* GPIOLIB */

अटल अंतरभूत
व्योम mctrl_gpio_set(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक mctrl_gpio_get(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक *mctrl)
अणु
	वापस *mctrl;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mctrl_gpio_get_outमाला_दो(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक *mctrl)
अणु
	वापस *mctrl;
पूर्ण

अटल अंतरभूत
काष्ठा gpio_desc *mctrl_gpio_to_gpiod(काष्ठा mctrl_gpios *gpios,
				      क्रमागत mctrl_gpio_idx gidx)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा mctrl_gpios *mctrl_gpio_init(काष्ठा uart_port *port, अचिन्हित पूर्णांक idx)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
काष्ठा mctrl_gpios *mctrl_gpio_init_noस्वतः(काष्ठा device *dev, अचिन्हित पूर्णांक idx)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
व्योम mctrl_gpio_मुक्त(काष्ठा device *dev, काष्ठा mctrl_gpios *gpios)
अणु
पूर्ण

अटल अंतरभूत व्योम mctrl_gpio_enable_ms(काष्ठा mctrl_gpios *gpios)
अणु
पूर्ण

अटल अंतरभूत व्योम mctrl_gpio_disable_ms(काष्ठा mctrl_gpios *gpios)
अणु
पूर्ण

#पूर्ण_अगर /* GPIOLIB */

#पूर्ण_अगर
