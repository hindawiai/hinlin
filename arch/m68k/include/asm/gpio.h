<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Coldfire generic GPIO support
 *
 * (C) Copyright 2009, Steven King <sfking@fdwdc.com>
*/

#अगर_अघोषित coldfire_gpio_h
#घोषणा coldfire_gpio_h

#समावेश <linux/पन.स>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfgpपन.स>
/*
 * The Generic GPIO functions
 *
 * If the gpio is a compile समय स्थिरant and is one of the Coldfire gpios,
 * use the अंतरभूत version, otherwise dispatch thru gpiolib.
 */

अटल अंतरभूत पूर्णांक gpio_get_value(अचिन्हित gpio)
अणु
	अगर (__builtin_स्थिरant_p(gpio) && gpio < MCFGPIO_PIN_MAX)
		वापस mcfgpio_पढ़ो(__mcfgpio_ppdr(gpio)) & mcfgpio_bit(gpio);
	अन्यथा
		वापस __gpio_get_value(gpio);
पूर्ण

अटल अंतरभूत व्योम gpio_set_value(अचिन्हित gpio, पूर्णांक value)
अणु
	अगर (__builtin_स्थिरant_p(gpio) && gpio < MCFGPIO_PIN_MAX) अणु
		अगर (gpio < MCFGPIO_SCR_START) अणु
			अचिन्हित दीर्घ flags;
			MCFGPIO_PORTTYPE data;

			local_irq_save(flags);
			data = mcfgpio_पढ़ो(__mcfgpio_podr(gpio));
			अगर (value)
				data |= mcfgpio_bit(gpio);
			अन्यथा
				data &= ~mcfgpio_bit(gpio);
			mcfgpio_ग_लिखो(data, __mcfgpio_podr(gpio));
			local_irq_restore(flags);
		पूर्ण अन्यथा अणु
			अगर (value)
				mcfgpio_ग_लिखो(mcfgpio_bit(gpio),
						MCFGPIO_SETR_PORT(gpio));
			अन्यथा
				mcfgpio_ग_लिखो(~mcfgpio_bit(gpio),
						MCFGPIO_CLRR_PORT(gpio));
		पूर्ण
	पूर्ण अन्यथा
		__gpio_set_value(gpio, value);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_to_irq(अचिन्हित gpio)
अणु
#अगर defined(MCFGPIO_IRQ_MIN)
	अगर ((gpio >= MCFGPIO_IRQ_MIN) && (gpio < MCFGPIO_IRQ_MAX))
#अन्यथा
	अगर (gpio < MCFGPIO_IRQ_MAX)
#पूर्ण_अगर
		वापस gpio + MCFGPIO_IRQ_VECBASE;
	अन्यथा
		वापस __gpio_to_irq(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक irq_to_gpio(अचिन्हित irq)
अणु
	वापस (irq >= MCFGPIO_IRQ_VECBASE &&
		irq < (MCFGPIO_IRQ_VECBASE + MCFGPIO_IRQ_MAX)) ?
		irq - MCFGPIO_IRQ_VECBASE : -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_cansleep(अचिन्हित gpio)
अणु
	वापस gpio < MCFGPIO_PIN_MAX ? 0 : __gpio_cansleep(gpio);
पूर्ण

#अगर_अघोषित CONFIG_GPIOLIB
अटल अंतरभूत पूर्णांक gpio_request_one(अचिन्हित gpio, अचिन्हित दीर्घ flags, स्थिर अक्षर *label)
अणु
	पूर्णांक err;

	err = gpio_request(gpio, label);
	अगर (err)
		वापस err;

	अगर (flags & GPIOF_सूची_IN)
		err = gpio_direction_input(gpio);
	अन्यथा
		err = gpio_direction_output(gpio,
			(flags & GPIOF_INIT_HIGH) ? 1 : 0);

	अगर (err)
		gpio_मुक्त(gpio);

	वापस err;
पूर्ण
#पूर्ण_अगर /* !CONFIG_GPIOLIB */
#पूर्ण_अगर
