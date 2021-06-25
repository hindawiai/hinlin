<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * <linux/gpपन.स>
 *
 * This is the LEGACY GPIO bulk include file, including legacy APIs. It is
 * used क्रम GPIO drivers still referencing the global GPIO numberspace,
 * and should not be included in new code.
 *
 * If you're implementing a GPIO driver, only include <linux/gpio/driver.h>
 * If you're implementing a GPIO consumer, only include <linux/gpio/consumer.h>
 */
#अगर_अघोषित __LINUX_GPIO_H
#घोषणा __LINUX_GPIO_H

#समावेश <linux/त्रुटिसं.स>

/* see Documentation/driver-api/gpio/legacy.rst */

/* make these flag values available regardless of GPIO kconfig options */
#घोषणा GPIOF_सूची_OUT	(0 << 0)
#घोषणा GPIOF_सूची_IN	(1 << 0)

#घोषणा GPIOF_INIT_LOW	(0 << 1)
#घोषणा GPIOF_INIT_HIGH	(1 << 1)

#घोषणा GPIOF_IN		(GPIOF_सूची_IN)
#घोषणा GPIOF_OUT_INIT_LOW	(GPIOF_सूची_OUT | GPIOF_INIT_LOW)
#घोषणा GPIOF_OUT_INIT_HIGH	(GPIOF_सूची_OUT | GPIOF_INIT_HIGH)

/* Gpio pin is active-low */
#घोषणा GPIOF_ACTIVE_LOW        (1 << 2)

/* Gpio pin is खोलो drain */
#घोषणा GPIOF_OPEN_DRAIN	(1 << 3)

/* Gpio pin is खोलो source */
#घोषणा GPIOF_OPEN_SOURCE	(1 << 4)

#घोषणा GPIOF_EXPORT		(1 << 5)
#घोषणा GPIOF_EXPORT_CHANGEABLE	(1 << 6)
#घोषणा GPIOF_EXPORT_सूची_FIXED	(GPIOF_EXPORT)
#घोषणा GPIOF_EXPORT_सूची_CHANGEABLE (GPIOF_EXPORT | GPIOF_EXPORT_CHANGEABLE)

/**
 * काष्ठा gpio - a काष्ठाure describing a GPIO with configuration
 * @gpio:	the GPIO number
 * @flags:	GPIO configuration as specअगरied by GPIOF_*
 * @label:	a literal description string of this GPIO
 */
काष्ठा gpio अणु
	अचिन्हित	gpio;
	अचिन्हित दीर्घ	flags;
	स्थिर अक्षर	*label;
पूर्ण;

#अगर_घोषित CONFIG_GPIOLIB

#अगर_घोषित CONFIG_ARCH_HAVE_CUSTOM_GPIO_H
#समावेश <यंत्र/gpपन.स>
#अन्यथा

#समावेश <यंत्र-generic/gpपन.स>

अटल अंतरभूत पूर्णांक gpio_get_value(अचिन्हित पूर्णांक gpio)
अणु
	वापस __gpio_get_value(gpio);
पूर्ण

अटल अंतरभूत व्योम gpio_set_value(अचिन्हित पूर्णांक gpio, पूर्णांक value)
अणु
	__gpio_set_value(gpio, value);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_cansleep(अचिन्हित पूर्णांक gpio)
अणु
	वापस __gpio_cansleep(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_to_irq(अचिन्हित पूर्णांक gpio)
अणु
	वापस __gpio_to_irq(gpio);
पूर्ण

अटल अंतरभूत पूर्णांक irq_to_gpio(अचिन्हित पूर्णांक irq)
अणु
	वापस -EINVAL;
पूर्ण

#पूर्ण_अगर /* ! CONFIG_ARCH_HAVE_CUSTOM_GPIO_H */

/* CONFIG_GPIOLIB: bindings क्रम managed devices that want to request gpios */

काष्ठा device;

पूर्णांक devm_gpio_request(काष्ठा device *dev, अचिन्हित gpio, स्थिर अक्षर *label);
पूर्णांक devm_gpio_request_one(काष्ठा device *dev, अचिन्हित gpio,
			  अचिन्हित दीर्घ flags, स्थिर अक्षर *label);
व्योम devm_gpio_मुक्त(काष्ठा device *dev, अचिन्हित पूर्णांक gpio);

#अन्यथा /* ! CONFIG_GPIOLIB */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>

काष्ठा device;
काष्ठा gpio_chip;

अटल अंतरभूत bool gpio_is_valid(पूर्णांक number)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_request(अचिन्हित gpio, स्थिर अक्षर *label)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_request_one(अचिन्हित gpio,
					अचिन्हित दीर्घ flags, स्थिर अक्षर *label)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_request_array(स्थिर काष्ठा gpio *array, माप_प्रकार num)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम gpio_मुक्त(अचिन्हित gpio)
अणु
	might_sleep();

	/* GPIO can never have been requested */
	WARN_ON(1);
पूर्ण

अटल अंतरभूत व्योम gpio_मुक्त_array(स्थिर काष्ठा gpio *array, माप_प्रकार num)
अणु
	might_sleep();

	/* GPIO can never have been requested */
	WARN_ON(1);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_direction_input(अचिन्हित gpio)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_direction_output(अचिन्हित gpio, पूर्णांक value)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_set_debounce(अचिन्हित gpio, अचिन्हित debounce)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_get_value(अचिन्हित gpio)
अणु
	/* GPIO can never have been requested or set as अणुin,outपूर्णput */
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम gpio_set_value(अचिन्हित gpio, पूर्णांक value)
अणु
	/* GPIO can never have been requested or set as output */
	WARN_ON(1);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_cansleep(अचिन्हित gpio)
अणु
	/* GPIO can never have been requested or set as अणुin,outपूर्णput */
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_get_value_cansleep(अचिन्हित gpio)
अणु
	/* GPIO can never have been requested or set as अणुin,outपूर्णput */
	WARN_ON(1);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम gpio_set_value_cansleep(अचिन्हित gpio, पूर्णांक value)
अणु
	/* GPIO can never have been requested or set as output */
	WARN_ON(1);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_export(अचिन्हित gpio, bool direction_may_change)
अणु
	/* GPIO can never have been requested or set as अणुin,outपूर्णput */
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक gpio_export_link(काष्ठा device *dev, स्थिर अक्षर *name,
				अचिन्हित gpio)
अणु
	/* GPIO can never have been exported */
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम gpio_unexport(अचिन्हित gpio)
अणु
	/* GPIO can never have been exported */
	WARN_ON(1);
पूर्ण

अटल अंतरभूत पूर्णांक gpio_to_irq(अचिन्हित gpio)
अणु
	/* GPIO can never have been requested or set as input */
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक irq_to_gpio(अचिन्हित irq)
अणु
	/* irq can never have been वापसed from gpio_to_irq() */
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक devm_gpio_request(काष्ठा device *dev, अचिन्हित gpio,
				    स्थिर अक्षर *label)
अणु
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक devm_gpio_request_one(काष्ठा device *dev, अचिन्हित gpio,
					अचिन्हित दीर्घ flags, स्थिर अक्षर *label)
अणु
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम devm_gpio_मुक्त(काष्ठा device *dev, अचिन्हित पूर्णांक gpio)
अणु
	WARN_ON(1);
पूर्ण

#पूर्ण_अगर /* ! CONFIG_GPIOLIB */

#पूर्ण_अगर /* __LINUX_GPIO_H */
