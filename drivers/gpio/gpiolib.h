<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Internal GPIO functions.
 *
 * Copyright (C) 2013, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित GPIOLIB_H
#घोषणा GPIOLIB_H

#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/consumer.h> /* क्रम क्रमागत gpiod_flags */
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/cdev.h>

#घोषणा GPIOCHIP_NAME	"gpiochip"

/**
 * काष्ठा gpio_device - पूर्णांकernal state container क्रम GPIO devices
 * @id: numerical ID number क्रम the GPIO chip
 * @dev: the GPIO device काष्ठा
 * @chrdev: अक्षरacter device क्रम the GPIO device
 * @mockdev: class device used by the deprecated sysfs पूर्णांकerface (may be
 * शून्य)
 * @owner: helps prevent removal of modules exporting active GPIOs
 * @chip: poपूर्णांकer to the corresponding gpiochip, holding अटल
 * data क्रम this device
 * @descs: array of ngpio descriptors.
 * @ngpio: the number of GPIO lines on this GPIO device, equal to the size
 * of the @descs array.
 * @base: GPIO base in the DEPRECATED global Linux GPIO numberspace, asचिन्हित
 * at device creation समय.
 * @label: a descriptive name क्रम the GPIO device, such as the part number
 * or name of the IP component in a System on Chip.
 * @data: per-instance data asचिन्हित by the driver
 * @list: links gpio_device:s together क्रम traversal
 *
 * This state container holds most of the runसमय variable data
 * क्रम a GPIO device and can hold references and live on after the
 * GPIO chip has been हटाओd, अगर it is still being used from
 * userspace.
 */
काष्ठा gpio_device अणु
	पूर्णांक			id;
	काष्ठा device		dev;
	काष्ठा cdev		chrdev;
	काष्ठा device		*mockdev;
	काष्ठा module		*owner;
	काष्ठा gpio_chip	*chip;
	काष्ठा gpio_desc	*descs;
	पूर्णांक			base;
	u16			ngpio;
	स्थिर अक्षर		*label;
	व्योम			*data;
	काष्ठा list_head        list;
	काष्ठा blocking_notअगरier_head notअगरier;

#अगर_घोषित CONFIG_PINCTRL
	/*
	 * If CONFIG_PINCTRL is enabled, then gpio controllers can optionally
	 * describe the actual pin range which they serve in an SoC. This
	 * inक्रमmation would be used by pinctrl subप्रणाली to configure
	 * corresponding pins क्रम gpio usage.
	 */
	काष्ठा list_head pin_ranges;
#पूर्ण_अगर
पूर्ण;

/* gpio suffixes used क्रम ACPI and device tree lookup */
अटल __maybe_unused स्थिर अक्षर * स्थिर gpio_suffixes[] = अणु "gpios", "gpio" पूर्ण;

काष्ठा gpio_array अणु
	काष्ठा gpio_desc	**desc;
	अचिन्हित पूर्णांक		size;
	काष्ठा gpio_chip	*chip;
	अचिन्हित दीर्घ		*get_mask;
	अचिन्हित दीर्घ		*set_mask;
	अचिन्हित दीर्घ		invert_mask[];
पूर्ण;

काष्ठा gpio_desc *gpiochip_get_desc(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक hwnum);
पूर्णांक gpiod_get_array_value_complex(bool raw, bool can_sleep,
				  अचिन्हित पूर्णांक array_size,
				  काष्ठा gpio_desc **desc_array,
				  काष्ठा gpio_array *array_info,
				  अचिन्हित दीर्घ *value_biपंचांगap);
पूर्णांक gpiod_set_array_value_complex(bool raw, bool can_sleep,
				  अचिन्हित पूर्णांक array_size,
				  काष्ठा gpio_desc **desc_array,
				  काष्ठा gpio_array *array_info,
				  अचिन्हित दीर्घ *value_biपंचांगap);

बाह्य spinlock_t gpio_lock;
बाह्य काष्ठा list_head gpio_devices;

काष्ठा gpio_desc अणु
	काष्ठा gpio_device	*gdev;
	अचिन्हित दीर्घ		flags;
/* flag symbols are bit numbers */
#घोषणा FLAG_REQUESTED	0
#घोषणा FLAG_IS_OUT	1
#घोषणा FLAG_EXPORT	2	/* रक्षित by sysfs_lock */
#घोषणा FLAG_SYSFS	3	/* exported via /sys/class/gpio/control */
#घोषणा FLAG_ACTIVE_LOW	6	/* value has active low */
#घोषणा FLAG_OPEN_DRAIN	7	/* Gpio is खोलो drain type */
#घोषणा FLAG_OPEN_SOURCE 8	/* Gpio is खोलो source type */
#घोषणा FLAG_USED_AS_IRQ 9	/* GPIO is connected to an IRQ */
#घोषणा FLAG_IRQ_IS_ENABLED 10	/* GPIO is connected to an enabled IRQ */
#घोषणा FLAG_IS_HOGGED	11	/* GPIO is hogged */
#घोषणा FLAG_TRANSITORY 12	/* GPIO may lose value in sleep or reset */
#घोषणा FLAG_PULL_UP    13	/* GPIO has pull up enabled */
#घोषणा FLAG_PULL_DOWN  14	/* GPIO has pull करोwn enabled */
#घोषणा FLAG_BIAS_DISABLE    15	/* GPIO has pull disabled */
#घोषणा FLAG_EDGE_RISING     16	/* GPIO CDEV detects rising edge events */
#घोषणा FLAG_EDGE_FALLING    17	/* GPIO CDEV detects falling edge events */
#घोषणा FLAG_EVENT_CLOCK_REALTIME	18 /* GPIO CDEV reports REALTIME बारtamps in events */

	/* Connection label */
	स्थिर अक्षर		*label;
	/* Name of the GPIO */
	स्थिर अक्षर		*name;
#अगर_घोषित CONFIG_OF_DYNAMIC
	काष्ठा device_node	*hog;
#पूर्ण_अगर
#अगर_घोषित CONFIG_GPIO_CDEV
	/* debounce period in microseconds */
	अचिन्हित पूर्णांक		debounce_period_us;
#पूर्ण_अगर
पूर्ण;

#घोषणा gpiod_not_found(desc)		(IS_ERR(desc) && PTR_ERR(desc) == -ENOENT)

पूर्णांक gpiod_request(काष्ठा gpio_desc *desc, स्थिर अक्षर *label);
व्योम gpiod_मुक्त(काष्ठा gpio_desc *desc);
पूर्णांक gpiod_configure_flags(काष्ठा gpio_desc *desc, स्थिर अक्षर *con_id,
		अचिन्हित दीर्घ lflags, क्रमागत gpiod_flags dflags);
पूर्णांक gpio_set_debounce_समयout(काष्ठा gpio_desc *desc, अचिन्हित पूर्णांक debounce);
पूर्णांक gpiod_hog(काष्ठा gpio_desc *desc, स्थिर अक्षर *name,
		अचिन्हित दीर्घ lflags, क्रमागत gpiod_flags dflags);

/*
 * Return the GPIO number of the passed descriptor relative to its chip
 */
अटल अंतरभूत पूर्णांक gpio_chip_hwgpio(स्थिर काष्ठा gpio_desc *desc)
अणु
	वापस desc - &desc->gdev->descs[0];
पूर्ण

/* With descriptor prefix */

#घोषणा gpiod_emerg(desc, fmt, ...)					       \
	pr_emerg("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->label ? : "?",\
		 ##__VA_ARGS__)
#घोषणा gpiod_crit(desc, fmt, ...)					       \
	pr_crit("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->label ? : "?", \
		 ##__VA_ARGS__)
#घोषणा gpiod_err(desc, fmt, ...)					       \
	pr_err("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->label ? : "?",  \
		 ##__VA_ARGS__)
#घोषणा gpiod_warn(desc, fmt, ...)					       \
	pr_warn("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->label ? : "?", \
		 ##__VA_ARGS__)
#घोषणा gpiod_info(desc, fmt, ...)					       \
	pr_info("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->label ? : "?", \
		 ##__VA_ARGS__)
#घोषणा gpiod_dbg(desc, fmt, ...)					       \
	pr_debug("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->label ? : "?",\
		 ##__VA_ARGS__)

/* With chip prefix */

#घोषणा chip_emerg(gc, fmt, ...)					\
	dev_emerg(&gc->gpiodev->dev, "(%s): " fmt, gc->label, ##__VA_ARGS__)
#घोषणा chip_crit(gc, fmt, ...)					\
	dev_crit(&gc->gpiodev->dev, "(%s): " fmt, gc->label, ##__VA_ARGS__)
#घोषणा chip_err(gc, fmt, ...)					\
	dev_err(&gc->gpiodev->dev, "(%s): " fmt, gc->label, ##__VA_ARGS__)
#घोषणा chip_warn(gc, fmt, ...)					\
	dev_warn(&gc->gpiodev->dev, "(%s): " fmt, gc->label, ##__VA_ARGS__)
#घोषणा chip_info(gc, fmt, ...)					\
	dev_info(&gc->gpiodev->dev, "(%s): " fmt, gc->label, ##__VA_ARGS__)
#घोषणा chip_dbg(gc, fmt, ...)					\
	dev_dbg(&gc->gpiodev->dev, "(%s): " fmt, gc->label, ##__VA_ARGS__)

#पूर्ण_अगर /* GPIOLIB_H */
