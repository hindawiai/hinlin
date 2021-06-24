<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface the generic pinconfig portions of the pinctrl subप्रणाली
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * This पूर्णांकerface is used in the core to keep track of pins.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित __LINUX_PINCTRL_PINCONF_GENERIC_H
#घोषणा __LINUX_PINCTRL_PINCONF_GENERIC_H

#समावेश <linux/device.h>
#समावेश <linux/pinctrl/machine.h>

काष्ठा pinctrl_dev;
काष्ठा pinctrl_map;

/**
 * क्रमागत pin_config_param - possible pin configuration parameters
 * @PIN_CONFIG_BIAS_BUS_HOLD: the pin will be set to weakly latch so that it
 *	weakly drives the last value on a tristate bus, also known as a "bus
 *	holder", "bus keeper" or "repeater". This allows another device on the
 *	bus to change the value by driving the bus high or low and चयनing to
 *	tristate. The argument is ignored.
 * @PIN_CONFIG_BIAS_DISABLE: disable any pin bias on the pin, a
 *	transition from say pull-up to pull-करोwn implies that you disable
 *	pull-up in the process, this setting disables all biasing.
 * @PIN_CONFIG_BIAS_HIGH_IMPEDANCE: the pin will be set to a high impedance
 *	mode, also know as "third-state" (tristate) or "high-Z" or "floating".
 *	On output pins this effectively disconnects the pin, which is useful
 *	अगर क्रम example some other pin is going to drive the संकेत connected
 *	to it क्रम a जबतक. Pins used क्रम input are usually always high
 *	impedance.
 * @PIN_CONFIG_BIAS_PULL_DOWN: the pin will be pulled करोwn (usually with high
 *	impedance to GROUND). If the argument is != 0 pull-करोwn is enabled,
 *	अगर it is 0, pull-करोwn is total, i.e. the pin is connected to GROUND.
 * @PIN_CONFIG_BIAS_PULL_PIN_DEFAULT: the pin will be pulled up or करोwn based
 *	on embedded knowledge of the controller hardware, like current mux
 *	function. The pull direction and possibly strength too will normally
 *	be decided completely inside the hardware block and not be पढ़ोable
 *	from the kernel side.
 *	If the argument is != 0 pull up/करोwn is enabled, अगर it is 0, the
 *	configuration is ignored. The proper way to disable it is to use
 *	@PIN_CONFIG_BIAS_DISABLE.
 * @PIN_CONFIG_BIAS_PULL_UP: the pin will be pulled up (usually with high
 *	impedance to VDD). If the argument is != 0 pull-up is enabled,
 *	अगर it is 0, pull-up is total, i.e. the pin is connected to VDD.
 * @PIN_CONFIG_DRIVE_OPEN_DRAIN: the pin will be driven with खोलो drain (खोलो
 *	collector) which means it is usually wired with other output ports
 *	which are then pulled up with an बाह्यal resistor. Setting this
 *	config will enable खोलो drain mode, the argument is ignored.
 * @PIN_CONFIG_DRIVE_OPEN_SOURCE: the pin will be driven with खोलो source
 *	(खोलो emitter). Setting this config will enable खोलो source mode, the
 *	argument is ignored.
 * @PIN_CONFIG_DRIVE_PUSH_PULL: the pin will be driven actively high and
 *	low, this is the most typical हाल and is typically achieved with two
 *	active transistors on the output. Setting this config will enable
 *	push-pull mode, the argument is ignored.
 * @PIN_CONFIG_DRIVE_STRENGTH: the pin will sink or source at most the current
 *	passed as argument. The argument is in mA.
 * @PIN_CONFIG_DRIVE_STRENGTH_UA: the pin will sink or source at most the current
 *	passed as argument. The argument is in uA.
 * @PIN_CONFIG_INPUT_DEBOUNCE: this will configure the pin to debounce mode,
 *	which means it will रुको क्रम संकेतs to settle when पढ़ोing inमाला_दो. The
 *	argument gives the debounce समय in usecs. Setting the
 *	argument to zero turns debouncing off.
 * @PIN_CONFIG_INPUT_ENABLE: enable the pin's input.  Note that this करोes not
 *	affect the pin's ability to drive output.  1 enables input, 0 disables
 *	input.
 * @PIN_CONFIG_INPUT_SCHMITT: this will configure an input pin to run in
 *	schmitt-trigger mode. If the schmitt-trigger has adjustable hysteresis,
 *	the threshold value is given on a custom क्रमmat as argument when
 *	setting pins to this mode.
 * @PIN_CONFIG_INPUT_SCHMITT_ENABLE: control schmitt-trigger mode on the pin.
 *      If the argument != 0, schmitt-trigger mode is enabled. If it's 0,
 *      schmitt-trigger mode is disabled.
 * @PIN_CONFIG_MODE_LOW_POWER: this will configure the pin क्रम low घातer
 *	operation, अगर several modes of operation are supported these can be
 *	passed in the argument on a custom क्रमm, अन्यथा just use argument 1
 *	to indicate low घातer mode, argument 0 turns low घातer mode off.
 * @PIN_CONFIG_MODE_PWM: this will configure the pin क्रम PWM
 * @PIN_CONFIG_OUTPUT_ENABLE: this will enable the pin's output mode
 * 	without driving a value there. For most platक्रमms this reduces to
 * 	enable the output buffers and then let the pin controller current
 * 	configuration (eg. the currently selected mux function) drive values on
 * 	the line. Use argument 1 to enable output mode, argument 0 to disable
 * 	it.
 * @PIN_CONFIG_OUTPUT: this will configure the pin as an output and drive a
 * 	value on the line. Use argument 1 to indicate high level, argument 0 to
 *	indicate low level. (Please see Documentation/driver-api/pinctl.rst,
 *	section "GPIO mode pitfalls" क्रम a discussion around this parameter.)
 * @PIN_CONFIG_PERSIST_STATE: retain pin state across sleep or controller reset
 * @PIN_CONFIG_POWER_SOURCE: अगर the pin can select between dअगरferent घातer
 *	supplies, the argument to this parameter (on a custom क्रमmat) tells
 *	the driver which alternative घातer source to use.
 * @PIN_CONFIG_SLEEP_HARDWARE_STATE: indicate this is sleep related state.
 * @PIN_CONFIG_SLEW_RATE: अगर the pin can select slew rate, the argument to
 *	this parameter (on a custom क्रमmat) tells the driver which alternative
 *	slew rate to use.
 * @PIN_CONFIG_SKEW_DELAY: अगर the pin has programmable skew rate (on inमाला_दो)
 *	or latch delay (on outमाला_दो) this parameter (in a custom क्रमmat)
 *	specअगरies the घड़ी skew or latch delay. It typically controls how
 *	many द्विगुन inverters are put in front of the line.
 * @PIN_CONFIG_END: this is the last क्रमागतerator क्रम pin configurations, अगर
 *	you need to pass in custom configurations to the pin controller, use
 *	PIN_CONFIG_END+1 as the base offset.
 * @PIN_CONFIG_MAX: this is the maximum configuration value that can be
 *	presented using the packed क्रमmat.
 */
क्रमागत pin_config_param अणु
	PIN_CONFIG_BIAS_BUS_HOLD,
	PIN_CONFIG_BIAS_DISABLE,
	PIN_CONFIG_BIAS_HIGH_IMPEDANCE,
	PIN_CONFIG_BIAS_PULL_DOWN,
	PIN_CONFIG_BIAS_PULL_PIN_DEFAULT,
	PIN_CONFIG_BIAS_PULL_UP,
	PIN_CONFIG_DRIVE_OPEN_DRAIN,
	PIN_CONFIG_DRIVE_OPEN_SOURCE,
	PIN_CONFIG_DRIVE_PUSH_PULL,
	PIN_CONFIG_DRIVE_STRENGTH,
	PIN_CONFIG_DRIVE_STRENGTH_UA,
	PIN_CONFIG_INPUT_DEBOUNCE,
	PIN_CONFIG_INPUT_ENABLE,
	PIN_CONFIG_INPUT_SCHMITT,
	PIN_CONFIG_INPUT_SCHMITT_ENABLE,
	PIN_CONFIG_MODE_LOW_POWER,
	PIN_CONFIG_MODE_PWM,
	PIN_CONFIG_OUTPUT_ENABLE,
	PIN_CONFIG_OUTPUT,
	PIN_CONFIG_PERSIST_STATE,
	PIN_CONFIG_POWER_SOURCE,
	PIN_CONFIG_SLEEP_HARDWARE_STATE,
	PIN_CONFIG_SLEW_RATE,
	PIN_CONFIG_SKEW_DELAY,
	PIN_CONFIG_END = 0x7F,
	PIN_CONFIG_MAX = 0xFF,
पूर्ण;

/*
 * Helpful configuration macro to be used in tables etc.
 */
#घोषणा PIN_CONF_PACKED(p, a) ((a << 8) | ((अचिन्हित दीर्घ) p & 0xffUL))

/*
 * The following अंतरभूतs stuffs a configuration parameter and data value
 * पूर्णांकo and out of an अचिन्हित दीर्घ argument, as used by the generic pin config
 * प्रणाली. We put the parameter in the lower 8 bits and the argument in the
 * upper 24 bits.
 */

अटल अंतरभूत क्रमागत pin_config_param pinconf_to_config_param(अचिन्हित दीर्घ config)
अणु
	वापस (क्रमागत pin_config_param) (config & 0xffUL);
पूर्ण

अटल अंतरभूत u32 pinconf_to_config_argument(अचिन्हित दीर्घ config)
अणु
	वापस (u32) ((config >> 8) & 0xffffffUL);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pinconf_to_config_packed(क्रमागत pin_config_param param,
						     u32 argument)
अणु
	वापस PIN_CONF_PACKED(param, argument);
पूर्ण

#घोषणा PCONFDUMP(a, b, c, d) अणु					\
	.param = a, .display = b, .क्रमmat = c, .has_arg = d	\
	पूर्ण

काष्ठा pin_config_item अणु
	स्थिर क्रमागत pin_config_param param;
	स्थिर अक्षर * स्थिर display;
	स्थिर अक्षर * स्थिर क्रमmat;
	bool has_arg;
पूर्ण;

काष्ठा pinconf_generic_params अणु
	स्थिर अक्षर * स्थिर property;
	क्रमागत pin_config_param param;
	u32 शेष_value;
पूर्ण;

पूर्णांक pinconf_generic_dt_subnode_to_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा device_node *np, काष्ठा pinctrl_map **map,
		अचिन्हित *reserved_maps, अचिन्हित *num_maps,
		क्रमागत pinctrl_map_type type);
पूर्णांक pinconf_generic_dt_node_to_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा device_node *np_config, काष्ठा pinctrl_map **map,
		अचिन्हित *num_maps, क्रमागत pinctrl_map_type type);
व्योम pinconf_generic_dt_मुक्त_map(काष्ठा pinctrl_dev *pctldev,
		काष्ठा pinctrl_map *map, अचिन्हित num_maps);

अटल अंतरभूत पूर्णांक pinconf_generic_dt_node_to_map_group(
		काष्ठा pinctrl_dev *pctldev, काष्ठा device_node *np_config,
		काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	वापस pinconf_generic_dt_node_to_map(pctldev, np_config, map, num_maps,
			PIN_MAP_TYPE_CONFIGS_GROUP);
पूर्ण

अटल अंतरभूत पूर्णांक pinconf_generic_dt_node_to_map_pin(
		काष्ठा pinctrl_dev *pctldev, काष्ठा device_node *np_config,
		काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	वापस pinconf_generic_dt_node_to_map(pctldev, np_config, map, num_maps,
			PIN_MAP_TYPE_CONFIGS_PIN);
पूर्ण

अटल अंतरभूत पूर्णांक pinconf_generic_dt_node_to_map_all(
		काष्ठा pinctrl_dev *pctldev, काष्ठा device_node *np_config,
		काष्ठा pinctrl_map **map, अचिन्हित *num_maps)
अणु
	/*
	 * passing the type as PIN_MAP_TYPE_INVALID causes the underlying parser
	 * to infer the map type from the DT properties used.
	 */
	वापस pinconf_generic_dt_node_to_map(pctldev, np_config, map, num_maps,
			PIN_MAP_TYPE_INVALID);
पूर्ण

#पूर्ण_अगर /* __LINUX_PINCTRL_PINCONF_GENERIC_H */
