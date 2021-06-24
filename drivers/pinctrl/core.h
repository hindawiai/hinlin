<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Core निजी header क्रम the pin control subप्रणाली
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/machine.h>

काष्ठा pinctrl_gpio_range;

/**
 * काष्ठा pinctrl_dev - pin control class device
 * @node: node to include this pin controller in the global pin controller list
 * @desc: the pin controller descriptor supplied when initializing this pin
 *	controller
 * @pin_desc_tree: each pin descriptor क्रम this pin controller is stored in
 *	this radix tree
 * @pin_group_tree: optionally each pin group can be stored in this radix tree
 * @num_groups: optionally number of groups can be kept here
 * @pin_function_tree: optionally each function can be stored in this radix tree
 * @num_functions: optionally number of functions can be kept here
 * @gpio_ranges: a list of GPIO ranges that is handled by this pin controller,
 *	ranges are added to this list at runसमय
 * @dev: the device entry क्रम this pin controller
 * @owner: module providing the pin controller, used क्रम refcounting
 * @driver_data: driver data क्रम drivers रेजिस्टरing to the pin controller
 *	subप्रणाली
 * @p: result of pinctrl_get() क्रम this device
 * @hog_शेष: शेष state क्रम pins hogged by this device
 * @hog_sleep: sleep state क्रम pins hogged by this device
 * @mutex: mutex taken on each pin controller specअगरic action
 * @device_root: debugfs root क्रम this device
 */
काष्ठा pinctrl_dev अणु
	काष्ठा list_head node;
	काष्ठा pinctrl_desc *desc;
	काष्ठा radix_tree_root pin_desc_tree;
#अगर_घोषित CONFIG_GENERIC_PINCTRL_GROUPS
	काष्ठा radix_tree_root pin_group_tree;
	अचिन्हित पूर्णांक num_groups;
#पूर्ण_अगर
#अगर_घोषित CONFIG_GENERIC_PINMUX_FUNCTIONS
	काष्ठा radix_tree_root pin_function_tree;
	अचिन्हित पूर्णांक num_functions;
#पूर्ण_अगर
	काष्ठा list_head gpio_ranges;
	काष्ठा device *dev;
	काष्ठा module *owner;
	व्योम *driver_data;
	काष्ठा pinctrl *p;
	काष्ठा pinctrl_state *hog_शेष;
	काष्ठा pinctrl_state *hog_sleep;
	काष्ठा mutex mutex;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *device_root;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा pinctrl - per-device pin control state holder
 * @node: global list node
 * @dev: the device using this pin control handle
 * @states: a list of states क्रम this device
 * @state: the current state
 * @dt_maps: the mapping table chunks dynamically parsed from device tree क्रम
 *	this device, अगर any
 * @users: reference count
 */
काष्ठा pinctrl अणु
	काष्ठा list_head node;
	काष्ठा device *dev;
	काष्ठा list_head states;
	काष्ठा pinctrl_state *state;
	काष्ठा list_head dt_maps;
	काष्ठा kref users;
पूर्ण;

/**
 * काष्ठा pinctrl_state - a pinctrl state क्रम a device
 * @node: list node क्रम काष्ठा pinctrl's @states field
 * @name: the name of this state
 * @settings: a list of settings क्रम this state
 */
काष्ठा pinctrl_state अणु
	काष्ठा list_head node;
	स्थिर अक्षर *name;
	काष्ठा list_head settings;
पूर्ण;

/**
 * काष्ठा pinctrl_setting_mux - setting data क्रम MAP_TYPE_MUX_GROUP
 * @group: the group selector to program
 * @func: the function selector to program
 */
काष्ठा pinctrl_setting_mux अणु
	अचिन्हित group;
	अचिन्हित func;
पूर्ण;

/**
 * काष्ठा pinctrl_setting_configs - setting data क्रम MAP_TYPE_CONFIGS_*
 * @group_or_pin: the group selector or pin ID to program
 * @configs: a poपूर्णांकer to an array of config parameters/values to program पूर्णांकo
 *	hardware. Each inभागidual pin controller defines the क्रमmat and meaning
 *	of config parameters.
 * @num_configs: the number of entries in array @configs
 */
काष्ठा pinctrl_setting_configs अणु
	अचिन्हित group_or_pin;
	अचिन्हित दीर्घ *configs;
	अचिन्हित num_configs;
पूर्ण;

/**
 * काष्ठा pinctrl_setting - an inभागidual mux or config setting
 * @node: list node क्रम काष्ठा pinctrl_settings's @settings field
 * @type: the type of setting
 * @pctldev: pin control device handling to be programmed. Not used क्रम
 *   PIN_MAP_TYPE_DUMMY_STATE.
 * @dev_name: the name of the device using this state
 * @data: Data specअगरic to the setting type
 */
काष्ठा pinctrl_setting अणु
	काष्ठा list_head node;
	क्रमागत pinctrl_map_type type;
	काष्ठा pinctrl_dev *pctldev;
	स्थिर अक्षर *dev_name;
	जोड़ अणु
		काष्ठा pinctrl_setting_mux mux;
		काष्ठा pinctrl_setting_configs configs;
	पूर्ण data;
पूर्ण;

/**
 * काष्ठा pin_desc - pin descriptor क्रम each physical pin in the arch
 * @pctldev: corresponding pin control device
 * @name: a name क्रम the pin, e.g. the name of the pin/pad/finger on a
 *	datasheet or such
 * @dynamic_name: अगर the name of this pin was dynamically allocated
 * @drv_data: driver-defined per-pin data. pinctrl core करोes not touch this
 * @mux_usecount: If zero, the pin is not claimed, and @owner should be शून्य.
 *	If non-zero, this pin is claimed by @owner. This field is an पूर्णांकeger
 *	rather than a boolean, since pinctrl_get() might process multiple
 *	mapping table entries that refer to, and hence claim, the same group
 *	or pin, and each of these will increment the @usecount.
 * @mux_owner: The name of device that called pinctrl_get().
 * @mux_setting: The most recent selected mux setting क्रम this pin, अगर any.
 * @gpio_owner: If pinctrl_gpio_request() was called क्रम this pin, this is
 *	the name of the GPIO that "owns" this pin.
 */
काष्ठा pin_desc अणु
	काष्ठा pinctrl_dev *pctldev;
	स्थिर अक्षर *name;
	bool dynamic_name;
	व्योम *drv_data;
	/* These fields only added when supporting pinmux drivers */
#अगर_घोषित CONFIG_PINMUX
	अचिन्हित mux_usecount;
	स्थिर अक्षर *mux_owner;
	स्थिर काष्ठा pinctrl_setting_mux *mux_setting;
	स्थिर अक्षर *gpio_owner;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा pinctrl_maps - a list item containing part of the mapping table
 * @node: mapping table list node
 * @maps: array of mapping table entries
 * @num_maps: the number of entries in @maps
 */
काष्ठा pinctrl_maps अणु
	काष्ठा list_head node;
	स्थिर काष्ठा pinctrl_map *maps;
	अचिन्हित num_maps;
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_PINCTRL_GROUPS

/**
 * काष्ठा group_desc - generic pin group descriptor
 * @name: name of the pin group
 * @pins: array of pins that beदीर्घ to the group
 * @num_pins: number of pins in the group
 * @data: pin controller driver specअगरic data
 */
काष्ठा group_desc अणु
	स्थिर अक्षर *name;
	पूर्णांक *pins;
	पूर्णांक num_pins;
	व्योम *data;
पूर्ण;

पूर्णांक pinctrl_generic_get_group_count(काष्ठा pinctrl_dev *pctldev);

स्थिर अक्षर *pinctrl_generic_get_group_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक group_selector);

पूर्णांक pinctrl_generic_get_group_pins(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक group_selector,
				   स्थिर अचिन्हित पूर्णांक **pins,
				   अचिन्हित पूर्णांक *npins);

काष्ठा group_desc *pinctrl_generic_get_group(काष्ठा pinctrl_dev *pctldev,
					     अचिन्हित पूर्णांक group_selector);

पूर्णांक pinctrl_generic_add_group(काष्ठा pinctrl_dev *pctldev, स्थिर अक्षर *name,
			      पूर्णांक *gpins, पूर्णांक ngpins, व्योम *data);

पूर्णांक pinctrl_generic_हटाओ_group(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक group_selector);

#पूर्ण_अगर	/* CONFIG_GENERIC_PINCTRL_GROUPS */

काष्ठा pinctrl_dev *get_pinctrl_dev_from_devname(स्थिर अक्षर *dev_name);
काष्ठा pinctrl_dev *get_pinctrl_dev_from_of_node(काष्ठा device_node *np);
पूर्णांक pin_get_from_name(काष्ठा pinctrl_dev *pctldev, स्थिर अक्षर *name);
स्थिर अक्षर *pin_get_name(काष्ठा pinctrl_dev *pctldev, स्थिर अचिन्हित pin);
पूर्णांक pinctrl_get_group_selector(काष्ठा pinctrl_dev *pctldev,
			       स्थिर अक्षर *pin_group);

अटल अंतरभूत काष्ठा pin_desc *pin_desc_get(काष्ठा pinctrl_dev *pctldev,
					    अचिन्हित पूर्णांक pin)
अणु
	वापस radix_tree_lookup(&pctldev->pin_desc_tree, pin);
पूर्ण

बाह्य काष्ठा pinctrl_gpio_range *
pinctrl_find_gpio_range_from_pin_nolock(काष्ठा pinctrl_dev *pctldev,
					अचिन्हित पूर्णांक pin);

बाह्य पूर्णांक pinctrl_क्रमce_sleep(काष्ठा pinctrl_dev *pctldev);
बाह्य पूर्णांक pinctrl_क्रमce_शेष(काष्ठा pinctrl_dev *pctldev);

बाह्य काष्ठा mutex pinctrl_maps_mutex;
बाह्य काष्ठा list_head pinctrl_maps;

#घोषणा क्रम_each_maps(_maps_node_, _i_, _map_) \
	list_क्रम_each_entry(_maps_node_, &pinctrl_maps, node) \
		क्रम (_i_ = 0, _map_ = &_maps_node_->maps[_i_]; \
			_i_ < _maps_node_->num_maps; \
			_i_++, _map_ = &_maps_node_->maps[_i_])
