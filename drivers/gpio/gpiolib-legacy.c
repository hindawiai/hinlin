<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>

#समावेश <linux/gpपन.स>

#समावेश "gpiolib.h"

व्योम gpio_मुक्त(अचिन्हित gpio)
अणु
	gpiod_मुक्त(gpio_to_desc(gpio));
पूर्ण
EXPORT_SYMBOL_GPL(gpio_मुक्त);

/**
 * gpio_request_one - request a single GPIO with initial configuration
 * @gpio:	the GPIO number
 * @flags:	GPIO configuration as specअगरied by GPIOF_*
 * @label:	a literal description string of this GPIO
 */
पूर्णांक gpio_request_one(अचिन्हित gpio, अचिन्हित दीर्घ flags, स्थिर अक्षर *label)
अणु
	काष्ठा gpio_desc *desc;
	पूर्णांक err;

	desc = gpio_to_desc(gpio);

	/* Compatibility: assume unavailable "valid" GPIOs will appear later */
	अगर (!desc && gpio_is_valid(gpio))
		वापस -EPROBE_DEFER;

	err = gpiod_request(desc, label);
	अगर (err)
		वापस err;

	अगर (flags & GPIOF_OPEN_DRAIN)
		set_bit(FLAG_OPEN_DRAIN, &desc->flags);

	अगर (flags & GPIOF_OPEN_SOURCE)
		set_bit(FLAG_OPEN_SOURCE, &desc->flags);

	अगर (flags & GPIOF_ACTIVE_LOW)
		set_bit(FLAG_ACTIVE_LOW, &desc->flags);

	अगर (flags & GPIOF_सूची_IN)
		err = gpiod_direction_input(desc);
	अन्यथा
		err = gpiod_direction_output_raw(desc,
				(flags & GPIOF_INIT_HIGH) ? 1 : 0);

	अगर (err)
		जाओ मुक्त_gpio;

	अगर (flags & GPIOF_EXPORT) अणु
		err = gpiod_export(desc, flags & GPIOF_EXPORT_CHANGEABLE);
		अगर (err)
			जाओ मुक्त_gpio;
	पूर्ण

	वापस 0;

 मुक्त_gpio:
	gpiod_मुक्त(desc);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(gpio_request_one);

पूर्णांक gpio_request(अचिन्हित gpio, स्थिर अक्षर *label)
अणु
	काष्ठा gpio_desc *desc = gpio_to_desc(gpio);

	/* Compatibility: assume unavailable "valid" GPIOs will appear later */
	अगर (!desc && gpio_is_valid(gpio))
		वापस -EPROBE_DEFER;

	वापस gpiod_request(desc, label);
पूर्ण
EXPORT_SYMBOL_GPL(gpio_request);

/**
 * gpio_request_array - request multiple GPIOs in a single call
 * @array:	array of the 'struct gpio'
 * @num:	how many GPIOs in the array
 */
पूर्णांक gpio_request_array(स्थिर काष्ठा gpio *array, माप_प्रकार num)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < num; i++, array++) अणु
		err = gpio_request_one(array->gpio, array->flags, array->label);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण
	वापस 0;

err_मुक्त:
	जबतक (i--)
		gpio_मुक्त((--array)->gpio);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(gpio_request_array);

/**
 * gpio_मुक्त_array - release multiple GPIOs in a single call
 * @array:	array of the 'struct gpio'
 * @num:	how many GPIOs in the array
 */
व्योम gpio_मुक्त_array(स्थिर काष्ठा gpio *array, माप_प्रकार num)
अणु
	जबतक (num--)
		gpio_मुक्त((array++)->gpio);
पूर्ण
EXPORT_SYMBOL_GPL(gpio_मुक्त_array);
