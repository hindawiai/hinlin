<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * OF helpers क्रम the GPIO API
 *
 * Copyright (c) 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#अगर_अघोषित __LINUX_OF_GPIO_H
#घोषणा __LINUX_OF_GPIO_H

#समावेश <linux/compiler.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpपन.स>		/* FIXME: Shouldn't be here */
#समावेश <linux/of.h>

काष्ठा device_node;

/*
 * This is Linux-specअगरic flags. By शेष controllers' and Linux' mapping
 * match, but GPIO controllers are मुक्त to translate their own flags to
 * Linux-specअगरic in their .xlate callback. Though, 1:1 mapping is recommended.
 */
क्रमागत of_gpio_flags अणु
	OF_GPIO_ACTIVE_LOW = 0x1,
	OF_GPIO_SINGLE_ENDED = 0x2,
	OF_GPIO_OPEN_DRAIN = 0x4,
	OF_GPIO_TRANSITORY = 0x8,
	OF_GPIO_PULL_UP = 0x10,
	OF_GPIO_PULL_DOWN = 0x20,
पूर्ण;

#अगर_घोषित CONFIG_OF_GPIO

#समावेश <linux/kernel.h>

/*
 * OF GPIO chip क्रम memory mapped banks
 */
काष्ठा of_mm_gpio_chip अणु
	काष्ठा gpio_chip gc;
	व्योम (*save_regs)(काष्ठा of_mm_gpio_chip *mm_gc);
	व्योम __iomem *regs;
पूर्ण;

अटल अंतरभूत काष्ठा of_mm_gpio_chip *to_of_mm_gpio_chip(काष्ठा gpio_chip *gc)
अणु
	वापस container_of(gc, काष्ठा of_mm_gpio_chip, gc);
पूर्ण

बाह्य पूर्णांक of_get_named_gpio_flags(काष्ठा device_node *np,
		स्थिर अक्षर *list_name, पूर्णांक index, क्रमागत of_gpio_flags *flags);

बाह्य पूर्णांक of_mm_gpiochip_add_data(काष्ठा device_node *np,
				   काष्ठा of_mm_gpio_chip *mm_gc,
				   व्योम *data);
अटल अंतरभूत पूर्णांक of_mm_gpiochip_add(काष्ठा device_node *np,
				     काष्ठा of_mm_gpio_chip *mm_gc)
अणु
	वापस of_mm_gpiochip_add_data(np, mm_gc, शून्य);
पूर्ण
बाह्य व्योम of_mm_gpiochip_हटाओ(काष्ठा of_mm_gpio_chip *mm_gc);

#अन्यथा /* CONFIG_OF_GPIO */

#समावेश <linux/त्रुटिसं.स>

/* Drivers may not strictly depend on the GPIO support, so let them link. */
अटल अंतरभूत पूर्णांक of_get_named_gpio_flags(काष्ठा device_node *np,
		स्थिर अक्षर *list_name, पूर्णांक index, क्रमागत of_gpio_flags *flags)
अणु
	अगर (flags)
		*flags = 0;

	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_OF_GPIO */

/**
 * of_gpio_named_count() - Count GPIOs क्रम a device
 * @np:		device node to count GPIOs क्रम
 * @propname:	property name containing gpio specअगरier(s)
 *
 * The function वापसs the count of GPIOs specअगरied क्रम a node.
 * Note that the empty GPIO specअगरiers count too. Returns either
 *   Number of gpios defined in property,
 *   -EINVAL क्रम an incorrectly क्रमmed gpios property, or
 *   -ENOENT क्रम a missing gpios property
 *
 * Example:
 * gpios = <0
 *          &gpio1 1 2
 *          0
 *          &gpio2 3 4>;
 *
 * The above example defines four GPIOs, two of which are not specअगरied.
 * This function will वापस '4'
 */
अटल अंतरभूत पूर्णांक of_gpio_named_count(काष्ठा device_node *np, स्थिर अक्षर* propname)
अणु
	वापस of_count_phandle_with_args(np, propname, "#gpio-cells");
पूर्ण

/**
 * of_gpio_count() - Count GPIOs क्रम a device
 * @np:		device node to count GPIOs क्रम
 *
 * Same as of_gpio_named_count, but hard coded to use the 'gpios' property
 */
अटल अंतरभूत पूर्णांक of_gpio_count(काष्ठा device_node *np)
अणु
	वापस of_gpio_named_count(np, "gpios");
पूर्ण

अटल अंतरभूत पूर्णांक of_get_gpio_flags(काष्ठा device_node *np, पूर्णांक index,
		      क्रमागत of_gpio_flags *flags)
अणु
	वापस of_get_named_gpio_flags(np, "gpios", index, flags);
पूर्ण

/**
 * of_get_named_gpio() - Get a GPIO number to use with GPIO API
 * @np:		device node to get GPIO from
 * @propname:	Name of property containing gpio specअगरier(s)
 * @index:	index of the GPIO
 *
 * Returns GPIO number to use with Linux generic GPIO API, or one of the त्रुटि_सं
 * value on the error condition.
 */
अटल अंतरभूत पूर्णांक of_get_named_gpio(काष्ठा device_node *np,
                                   स्थिर अक्षर *propname, पूर्णांक index)
अणु
	वापस of_get_named_gpio_flags(np, propname, index, शून्य);
पूर्ण

/**
 * of_get_gpio() - Get a GPIO number to use with GPIO API
 * @np:		device node to get GPIO from
 * @index:	index of the GPIO
 *
 * Returns GPIO number to use with Linux generic GPIO API, or one of the त्रुटि_सं
 * value on the error condition.
 */
अटल अंतरभूत पूर्णांक of_get_gpio(काष्ठा device_node *np, पूर्णांक index)
अणु
	वापस of_get_gpio_flags(np, index, शून्य);
पूर्ण

#पूर्ण_अगर /* __LINUX_OF_GPIO_H */
