<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface the pinctrl subप्रणाली
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * This पूर्णांकerface is used in the core to keep track of pins.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित __LINUX_PINCTRL_PINCTRL_H
#घोषणा __LINUX_PINCTRL_PINCTRL_H

#समावेश <linux/radix-tree.h>
#समावेश <linux/list.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pinctrl/pinctrl-state.h>
#समावेश <linux/pinctrl/devinfo.h>

काष्ठा device;
काष्ठा pinctrl_dev;
काष्ठा pinctrl_map;
काष्ठा pinmux_ops;
काष्ठा pinconf_ops;
काष्ठा pin_config_item;
काष्ठा gpio_chip;
काष्ठा device_node;

/**
 * काष्ठा pinctrl_pin_desc - boards/machines provide inक्रमmation on their
 * pins, pads or other muxable units in this काष्ठा
 * @number: unique pin number from the global pin number space
 * @name: a name क्रम this pin
 * @drv_data: driver-defined per-pin data. pinctrl core करोes not touch this
 */
काष्ठा pinctrl_pin_desc अणु
	अचिन्हित number;
	स्थिर अक्षर *name;
	व्योम *drv_data;
पूर्ण;

/* Convenience macro to define a single named or anonymous pin descriptor */
#घोषणा PINCTRL_PIN(a, b) अणु .number = a, .name = b पूर्ण
#घोषणा PINCTRL_PIN_ANON(a) अणु .number = a पूर्ण

/**
 * काष्ठा pinctrl_gpio_range - each pin controller can provide subranges of
 * the GPIO number space to be handled by the controller
 * @node: list node क्रम पूर्णांकernal use
 * @name: a name क्रम the chip in this range
 * @id: an ID number क्रम the chip in this range
 * @base: base offset of the GPIO range
 * @pin_base: base pin number of the GPIO range अगर pins == शून्य
 * @npins: number of pins in the GPIO range, including the base number
 * @pins: क्रमागतeration of pins in GPIO range or शून्य
 * @gc: an optional poपूर्णांकer to a gpio_chip
 */
काष्ठा pinctrl_gpio_range अणु
	काष्ठा list_head node;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक pin_base;
	अचिन्हित पूर्णांक npins;
	अचिन्हित स्थिर *pins;
	काष्ठा gpio_chip *gc;
पूर्ण;

/**
 * काष्ठा pinctrl_ops - global pin control operations, to be implemented by
 * pin controller drivers.
 * @get_groups_count: Returns the count of total number of groups रेजिस्टरed.
 * @get_group_name: वापस the group name of the pin group
 * @get_group_pins: वापस an array of pins corresponding to a certain
 *	group selector @pins, and the size of the array in @num_pins
 * @pin_dbg_show: optional debugfs display hook that will provide per-device
 *	info क्रम a certain pin in debugfs
 * @dt_node_to_map: parse a device tree "pin configuration node", and create
 *	mapping table entries क्रम it. These are वापसed through the @map and
 *	@num_maps output parameters. This function is optional, and may be
 *	omitted क्रम pinctrl drivers that करो not support device tree.
 * @dt_मुक्त_map: मुक्त mapping table entries created via @dt_node_to_map. The
 *	top-level @map poपूर्णांकer must be मुक्तd, aदीर्घ with any dynamically
 *	allocated members of the mapping table entries themselves. This
 *	function is optional, and may be omitted क्रम pinctrl drivers that करो
 *	not support device tree.
 */
काष्ठा pinctrl_ops अणु
	पूर्णांक (*get_groups_count) (काष्ठा pinctrl_dev *pctldev);
	स्थिर अक्षर *(*get_group_name) (काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित selector);
	पूर्णांक (*get_group_pins) (काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित selector,
			       स्थिर अचिन्हित **pins,
			       अचिन्हित *num_pins);
	व्योम (*pin_dbg_show) (काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			  अचिन्हित offset);
	पूर्णांक (*dt_node_to_map) (काष्ठा pinctrl_dev *pctldev,
			       काष्ठा device_node *np_config,
			       काष्ठा pinctrl_map **map, अचिन्हित *num_maps);
	व्योम (*dt_मुक्त_map) (काष्ठा pinctrl_dev *pctldev,
			     काष्ठा pinctrl_map *map, अचिन्हित num_maps);
पूर्ण;

/**
 * काष्ठा pinctrl_desc - pin controller descriptor, रेजिस्टर this to pin
 * control subप्रणाली
 * @name: name क्रम the pin controller
 * @pins: an array of pin descriptors describing all the pins handled by
 *	this pin controller
 * @npins: number of descriptors in the array, usually just ARRAY_SIZE()
 *	of the pins field above
 * @pctlops: pin control operation vtable, to support global concepts like
 *	grouping of pins, this is optional.
 * @pmxops: pinmux operations vtable, अगर you support pinmuxing in your driver
 * @confops: pin config operations vtable, अगर you support pin configuration in
 *	your driver
 * @owner: module providing the pin controller, used क्रम refcounting
 * @num_custom_params: Number of driver-specअगरic custom parameters to be parsed
 *	from the hardware description
 * @custom_params: List of driver_specअगरic custom parameters to be parsed from
 *	the hardware description
 * @custom_conf_items: Inक्रमmation how to prपूर्णांक @params in debugfs, must be
 *	the same size as the @custom_params, i.e. @num_custom_params
 * @link_consumers: If true create a device link between pinctrl and its
 *	consumers (i.e. the devices requesting pin control states). This is
 *	someबार necessary to ascertain the right suspend/resume order क्रम
 *	example.
 */
काष्ठा pinctrl_desc अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित पूर्णांक npins;
	स्थिर काष्ठा pinctrl_ops *pctlops;
	स्थिर काष्ठा pinmux_ops *pmxops;
	स्थिर काष्ठा pinconf_ops *confops;
	काष्ठा module *owner;
#अगर_घोषित CONFIG_GENERIC_PINCONF
	अचिन्हित पूर्णांक num_custom_params;
	स्थिर काष्ठा pinconf_generic_params *custom_params;
	स्थिर काष्ठा pin_config_item *custom_conf_items;
#पूर्ण_अगर
	bool link_consumers;
पूर्ण;

/* External पूर्णांकerface to pin controller */

बाह्य पूर्णांक pinctrl_रेजिस्टर_and_init(काष्ठा pinctrl_desc *pctldesc,
				     काष्ठा device *dev, व्योम *driver_data,
				     काष्ठा pinctrl_dev **pctldev);
बाह्य पूर्णांक pinctrl_enable(काष्ठा pinctrl_dev *pctldev);

/* Please use pinctrl_रेजिस्टर_and_init() and pinctrl_enable() instead */
बाह्य काष्ठा pinctrl_dev *pinctrl_रेजिस्टर(काष्ठा pinctrl_desc *pctldesc,
				काष्ठा device *dev, व्योम *driver_data);

बाह्य व्योम pinctrl_unरेजिस्टर(काष्ठा pinctrl_dev *pctldev);

बाह्य पूर्णांक devm_pinctrl_रेजिस्टर_and_init(काष्ठा device *dev,
				काष्ठा pinctrl_desc *pctldesc,
				व्योम *driver_data,
				काष्ठा pinctrl_dev **pctldev);

/* Please use devm_pinctrl_रेजिस्टर_and_init() instead */
बाह्य काष्ठा pinctrl_dev *devm_pinctrl_रेजिस्टर(काष्ठा device *dev,
				काष्ठा pinctrl_desc *pctldesc,
				व्योम *driver_data);

बाह्य व्योम devm_pinctrl_unरेजिस्टर(काष्ठा device *dev,
				काष्ठा pinctrl_dev *pctldev);

बाह्य व्योम pinctrl_add_gpio_range(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_gpio_range *range);
बाह्य व्योम pinctrl_add_gpio_ranges(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_gpio_range *ranges,
				अचिन्हित nranges);
बाह्य व्योम pinctrl_हटाओ_gpio_range(काष्ठा pinctrl_dev *pctldev,
				काष्ठा pinctrl_gpio_range *range);

बाह्य काष्ठा pinctrl_dev *pinctrl_find_and_add_gpio_range(स्थिर अक्षर *devname,
		काष्ठा pinctrl_gpio_range *range);
बाह्य काष्ठा pinctrl_gpio_range *
pinctrl_find_gpio_range_from_pin(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक pin);
बाह्य पूर्णांक pinctrl_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				स्थिर अक्षर *pin_group, स्थिर अचिन्हित **pins,
				अचिन्हित *num_pins);

#अगर IS_ENABLED(CONFIG_OF) && IS_ENABLED(CONFIG_PINCTRL)
बाह्य काष्ठा pinctrl_dev *of_pinctrl_get(काष्ठा device_node *np);
#अन्यथा
अटल अंतरभूत
काष्ठा pinctrl_dev *of_pinctrl_get(काष्ठा device_node *np)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

बाह्य स्थिर अक्षर *pinctrl_dev_get_name(काष्ठा pinctrl_dev *pctldev);
बाह्य स्थिर अक्षर *pinctrl_dev_get_devname(काष्ठा pinctrl_dev *pctldev);
बाह्य व्योम *pinctrl_dev_get_drvdata(काष्ठा pinctrl_dev *pctldev);

#पूर्ण_अगर /* __LINUX_PINCTRL_PINCTRL_H */
