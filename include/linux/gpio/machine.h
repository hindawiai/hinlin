<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_GPIO_MACHINE_H
#घोषणा __LINUX_GPIO_MACHINE_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>

क्रमागत gpio_lookup_flags अणु
	GPIO_ACTIVE_HIGH		= (0 << 0),
	GPIO_ACTIVE_LOW			= (1 << 0),
	GPIO_OPEN_DRAIN			= (1 << 1),
	GPIO_OPEN_SOURCE		= (1 << 2),
	GPIO_PERSISTENT			= (0 << 3),
	GPIO_TRANSITORY			= (1 << 3),
	GPIO_PULL_UP			= (1 << 4),
	GPIO_PULL_DOWN			= (1 << 5),

	GPIO_LOOKUP_FLAGS_DEFAULT	= GPIO_ACTIVE_HIGH | GPIO_PERSISTENT,
पूर्ण;

/**
 * काष्ठा gpiod_lookup - lookup table
 * @key: either the name of the chip the GPIO beदीर्घs to, or the GPIO line name
 *       Note that GPIO line names are not guaranteed to be globally unique,
 *       so this will use the first match found!
 * @chip_hwnum: hardware number (i.e. relative to the chip) of the GPIO, or
 *              U16_MAX to indicate that @key is a GPIO line name
 * @con_id: name of the GPIO from the device's poपूर्णांक of view
 * @idx: index of the GPIO in हाल several GPIOs share the same name
 * @flags: biपंचांगask of gpio_lookup_flags GPIO_* values
 *
 * gpiod_lookup is a lookup table क्रम associating GPIOs to specअगरic devices and
 * functions using platक्रमm data.
 */
काष्ठा gpiod_lookup अणु
	स्थिर अक्षर *key;
	u16 chip_hwnum;
	स्थिर अक्षर *con_id;
	अचिन्हित पूर्णांक idx;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा gpiod_lookup_table अणु
	काष्ठा list_head list;
	स्थिर अक्षर *dev_id;
	काष्ठा gpiod_lookup table[];
पूर्ण;

/**
 * काष्ठा gpiod_hog - GPIO line hog table
 * @chip_label: name of the chip the GPIO beदीर्घs to
 * @chip_hwnum: hardware number (i.e. relative to the chip) of the GPIO
 * @line_name: consumer name क्रम the hogged line
 * @lflags: biपंचांगask of gpio_lookup_flags GPIO_* values
 * @dflags: GPIO flags used to specअगरy the direction and value
 */
काष्ठा gpiod_hog अणु
	काष्ठा list_head list;
	स्थिर अक्षर *chip_label;
	u16 chip_hwnum;
	स्थिर अक्षर *line_name;
	अचिन्हित दीर्घ lflags;
	पूर्णांक dflags;
पूर्ण;

/*
 * Simple definition of a single GPIO under a con_id
 */
#घोषणा GPIO_LOOKUP(_key, _chip_hwnum, _con_id, _flags) \
	GPIO_LOOKUP_IDX(_key, _chip_hwnum, _con_id, 0, _flags)

/*
 * Use this macro अगर you need to have several GPIOs under the same con_id.
 * Each GPIO needs to use a dअगरferent index and can be accessed using
 * gpiod_get_index()
 */
#घोषणा GPIO_LOOKUP_IDX(_key, _chip_hwnum, _con_id, _idx, _flags)         \
(काष्ठा gpiod_lookup) अणु                                                   \
	.key = _key,                                                      \
	.chip_hwnum = _chip_hwnum,                                        \
	.con_id = _con_id,                                                \
	.idx = _idx,                                                      \
	.flags = _flags,                                                  \
पूर्ण

/*
 * Simple definition of a single GPIO hog in an array.
 */
#घोषणा GPIO_HOG(_chip_label, _chip_hwnum, _line_name, _lflags, _dflags)  \
(काष्ठा gpiod_hog) अणु                                                      \
	.chip_label = _chip_label,                                        \
	.chip_hwnum = _chip_hwnum,                                        \
	.line_name = _line_name,                                          \
	.lflags = _lflags,                                                \
	.dflags = _dflags,                                                \
पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
व्योम gpiod_add_lookup_table(काष्ठा gpiod_lookup_table *table);
व्योम gpiod_add_lookup_tables(काष्ठा gpiod_lookup_table **tables, माप_प्रकार n);
व्योम gpiod_हटाओ_lookup_table(काष्ठा gpiod_lookup_table *table);
व्योम gpiod_add_hogs(काष्ठा gpiod_hog *hogs);
#अन्यथा /* ! CONFIG_GPIOLIB */
अटल अंतरभूत
व्योम gpiod_add_lookup_table(काष्ठा gpiod_lookup_table *table) अणुपूर्ण
अटल अंतरभूत
व्योम gpiod_add_lookup_tables(काष्ठा gpiod_lookup_table **tables, माप_प्रकार n) अणुपूर्ण
अटल अंतरभूत
व्योम gpiod_हटाओ_lookup_table(काष्ठा gpiod_lookup_table *table) अणुपूर्ण
अटल अंतरभूत व्योम gpiod_add_hogs(काष्ठा gpiod_hog *hogs) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_GPIOLIB */

#पूर्ण_अगर /* __LINUX_GPIO_MACHINE_H */
