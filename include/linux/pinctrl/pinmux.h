<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface the pinmux subप्रणाली
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित __LINUX_PINCTRL_PINMUX_H
#घोषणा __LINUX_PINCTRL_PINMUX_H

#समावेश <linux/list.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pinctrl/pinctrl.h>

काष्ठा pinctrl_dev;

/**
 * काष्ठा pinmux_ops - pinmux operations, to be implemented by pin controller
 * drivers that support pinmuxing
 * @request: called by the core to see अगर a certain pin can be made
 *	available क्रम muxing. This is called by the core to acquire the pins
 *	beक्रमe selecting any actual mux setting across a function. The driver
 *	is allowed to answer "no" by वापसing a negative error code
 * @मुक्त: the reverse function of the request() callback, मुक्तs a pin after
 *	being requested
 * @get_functions_count: वापसs number of selectable named functions available
 *	in this pinmux driver
 * @get_function_name: वापस the function name of the muxing selector,
 *	called by the core to figure out which mux setting it shall map a
 *	certain device to
 * @get_function_groups: वापस an array of groups names (in turn
 *	referencing pins) connected to a certain function selector. The group
 *	name can be used with the generic @pinctrl_ops to retrieve the
 *	actual pins affected. The applicable groups will be वापसed in
 *	@groups and the number of groups in @num_groups
 * @set_mux: enable a certain muxing function with a certain pin group. The
 *	driver करोes not need to figure out whether enabling this function
 *	conflicts some other use of the pins in that group, such collisions
 *	are handled by the pinmux subप्रणाली. The @func_selector selects a
 *	certain function whereas @group_selector selects a certain set of pins
 *	to be used. On simple controllers the latter argument may be ignored
 * @gpio_request_enable: requests and enables GPIO on a certain pin.
 *	Implement this only अगर you can mux every pin inभागidually as GPIO. The
 *	affected GPIO range is passed aदीर्घ with an offset(pin number) पूर्णांकo that
 *	specअगरic GPIO range - function selectors and pin groups are orthogonal
 *	to this, the core will however make sure the pins करो not collide.
 * @gpio_disable_मुक्त: मुक्त up GPIO muxing on a certain pin, the reverse of
 *	@gpio_request_enable
 * @gpio_set_direction: Since controllers may need dअगरferent configurations
 *	depending on whether the GPIO is configured as input or output,
 *	a direction selector function may be implemented as a backing
 *	to the GPIO controllers that need pin muxing.
 * @strict: करो not allow simultaneous use of the same pin क्रम GPIO and another
 *	function. Check both gpio_owner and mux_owner strictly beक्रमe approving
 *	the pin request.
 */
काष्ठा pinmux_ops अणु
	पूर्णांक (*request) (काष्ठा pinctrl_dev *pctldev, अचिन्हित offset);
	पूर्णांक (*मुक्त) (काष्ठा pinctrl_dev *pctldev, अचिन्हित offset);
	पूर्णांक (*get_functions_count) (काष्ठा pinctrl_dev *pctldev);
	स्थिर अक्षर *(*get_function_name) (काष्ठा pinctrl_dev *pctldev,
					  अचिन्हित selector);
	पूर्णांक (*get_function_groups) (काष्ठा pinctrl_dev *pctldev,
				  अचिन्हित selector,
				  स्थिर अक्षर * स्थिर **groups,
				  अचिन्हित *num_groups);
	पूर्णांक (*set_mux) (काष्ठा pinctrl_dev *pctldev, अचिन्हित func_selector,
			अचिन्हित group_selector);
	पूर्णांक (*gpio_request_enable) (काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित offset);
	व्योम (*gpio_disable_मुक्त) (काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित offset);
	पूर्णांक (*gpio_set_direction) (काष्ठा pinctrl_dev *pctldev,
				   काष्ठा pinctrl_gpio_range *range,
				   अचिन्हित offset,
				   bool input);
	bool strict;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PINCTRL_PINMUX_H */
