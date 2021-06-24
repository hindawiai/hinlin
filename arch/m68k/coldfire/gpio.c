<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Coldfire generic GPIO support.
 *
 * (C) Copyright 2009, Steven King <sfking@fdwdc.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfgpपन.स>

पूर्णांक __mcfgpio_get_value(अचिन्हित gpio)
अणु
	वापस mcfgpio_पढ़ो(__mcfgpio_ppdr(gpio)) & mcfgpio_bit(gpio);
पूर्ण
EXPORT_SYMBOL(__mcfgpio_get_value);

व्योम __mcfgpio_set_value(अचिन्हित gpio, पूर्णांक value)
अणु
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
पूर्ण
EXPORT_SYMBOL(__mcfgpio_set_value);

पूर्णांक __mcfgpio_direction_input(अचिन्हित gpio)
अणु
	अचिन्हित दीर्घ flags;
	MCFGPIO_PORTTYPE dir;

	local_irq_save(flags);
	dir = mcfgpio_पढ़ो(__mcfgpio_pddr(gpio));
	dir &= ~mcfgpio_bit(gpio);
	mcfgpio_ग_लिखो(dir, __mcfgpio_pddr(gpio));
	local_irq_restore(flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__mcfgpio_direction_input);

पूर्णांक __mcfgpio_direction_output(अचिन्हित gpio, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	MCFGPIO_PORTTYPE data;

	local_irq_save(flags);
	data = mcfgpio_पढ़ो(__mcfgpio_pddr(gpio));
	data |= mcfgpio_bit(gpio);
	mcfgpio_ग_लिखो(data, __mcfgpio_pddr(gpio));

	/* now set the data to output */
	अगर (gpio < MCFGPIO_SCR_START) अणु
		data = mcfgpio_पढ़ो(__mcfgpio_podr(gpio));
		अगर (value)
			data |= mcfgpio_bit(gpio);
		अन्यथा
			data &= ~mcfgpio_bit(gpio);
		mcfgpio_ग_लिखो(data, __mcfgpio_podr(gpio));
	पूर्ण अन्यथा अणु
		 अगर (value)
			mcfgpio_ग_लिखो(mcfgpio_bit(gpio),
					MCFGPIO_SETR_PORT(gpio));
		 अन्यथा
			 mcfgpio_ग_लिखो(~mcfgpio_bit(gpio),
					 MCFGPIO_CLRR_PORT(gpio));
	पूर्ण
	local_irq_restore(flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__mcfgpio_direction_output);

पूर्णांक __mcfgpio_request(अचिन्हित gpio)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__mcfgpio_request);

व्योम __mcfgpio_मुक्त(अचिन्हित gpio)
अणु
	__mcfgpio_direction_input(gpio);
पूर्ण
EXPORT_SYMBOL(__mcfgpio_मुक्त);

#अगर_घोषित CONFIG_GPIOLIB

अटल पूर्णांक mcfgpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस __mcfgpio_direction_input(offset);
पूर्ण

अटल पूर्णांक mcfgpio_get_value(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस !!__mcfgpio_get_value(offset);
पूर्ण

अटल पूर्णांक mcfgpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित offset,
				    पूर्णांक value)
अणु
	वापस __mcfgpio_direction_output(offset, value);
पूर्ण

अटल व्योम mcfgpio_set_value(काष्ठा gpio_chip *chip, अचिन्हित offset,
			      पूर्णांक value)
अणु
	__mcfgpio_set_value(offset, value);
पूर्ण

अटल पूर्णांक mcfgpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	वापस __mcfgpio_request(offset);
पूर्ण

अटल व्योम mcfgpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	__mcfgpio_मुक्त(offset);
पूर्ण

अटल पूर्णांक mcfgpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
#अगर defined(MCFGPIO_IRQ_MIN)
	अगर ((offset >= MCFGPIO_IRQ_MIN) && (offset < MCFGPIO_IRQ_MAX))
#अन्यथा
	अगर (offset < MCFGPIO_IRQ_MAX)
#पूर्ण_अगर
		वापस MCFGPIO_IRQ_VECBASE + offset;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल काष्ठा gpio_chip mcfgpio_chip = अणु
	.label			= "mcfgpio",
	.request		= mcfgpio_request,
	.मुक्त			= mcfgpio_मुक्त,
	.direction_input	= mcfgpio_direction_input,
	.direction_output	= mcfgpio_direction_output,
	.get			= mcfgpio_get_value,
	.set			= mcfgpio_set_value,
	.to_irq			= mcfgpio_to_irq,
	.base			= 0,
	.ngpio			= MCFGPIO_PIN_MAX,
पूर्ण;

अटल पूर्णांक __init mcfgpio_sysinit(व्योम)
अणु
	वापस gpiochip_add_data(&mcfgpio_chip, शून्य);
पूर्ण

core_initcall(mcfgpio_sysinit);
#पूर्ण_अगर
