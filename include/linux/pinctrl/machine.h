<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Machine पूर्णांकerface क्रम the pinctrl subप्रणाली.
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित __LINUX_PINCTRL_MACHINE_H
#घोषणा __LINUX_PINCTRL_MACHINE_H

#समावेश <linux/bug.h>

#समावेश <linux/pinctrl/pinctrl-state.h>

क्रमागत pinctrl_map_type अणु
	PIN_MAP_TYPE_INVALID,
	PIN_MAP_TYPE_DUMMY_STATE,
	PIN_MAP_TYPE_MUX_GROUP,
	PIN_MAP_TYPE_CONFIGS_PIN,
	PIN_MAP_TYPE_CONFIGS_GROUP,
पूर्ण;

/**
 * काष्ठा pinctrl_map_mux - mapping table content क्रम MAP_TYPE_MUX_GROUP
 * @group: the name of the group whose mux function is to be configured. This
 *	field may be left शून्य, and the first applicable group क्रम the function
 *	will be used.
 * @function: the mux function to select क्रम the group
 */
काष्ठा pinctrl_map_mux अणु
	स्थिर अक्षर *group;
	स्थिर अक्षर *function;
पूर्ण;

/**
 * काष्ठा pinctrl_map_configs - mapping table content क्रम MAP_TYPE_CONFIGS_*
 * @group_or_pin: the name of the pin or group whose configuration parameters
 *	are to be configured.
 * @configs: a poपूर्णांकer to an array of config parameters/values to program पूर्णांकo
 *	hardware. Each inभागidual pin controller defines the क्रमmat and meaning
 *	of config parameters.
 * @num_configs: the number of entries in array @configs
 */
काष्ठा pinctrl_map_configs अणु
	स्थिर अक्षर *group_or_pin;
	अचिन्हित दीर्घ *configs;
	अचिन्हित num_configs;
पूर्ण;

/**
 * काष्ठा pinctrl_map - boards/machines shall provide this map क्रम devices
 * @dev_name: the name of the device using this specअगरic mapping, the name
 *	must be the same as in your काष्ठा device*. If this name is set to the
 *	same name as the pin controllers own dev_name(), the map entry will be
 *	hogged by the driver itself upon registration
 * @name: the name of this specअगरic map entry क्रम the particular machine.
 *	This is the parameter passed to pinmux_lookup_state()
 * @type: the type of mapping table entry
 * @ctrl_dev_name: the name of the device controlling this specअगरic mapping,
 *	the name must be the same as in your काष्ठा device*. This field is not
 *	used क्रम PIN_MAP_TYPE_DUMMY_STATE
 * @data: Data specअगरic to the mapping type
 */
काष्ठा pinctrl_map अणु
	स्थिर अक्षर *dev_name;
	स्थिर अक्षर *name;
	क्रमागत pinctrl_map_type type;
	स्थिर अक्षर *ctrl_dev_name;
	जोड़ अणु
		काष्ठा pinctrl_map_mux mux;
		काष्ठा pinctrl_map_configs configs;
	पूर्ण data;
पूर्ण;

/* Convenience macros to create mapping table entries */

#घोषणा PIN_MAP_DUMMY_STATE(dev, state) \
	अणु								\
		.dev_name = dev,					\
		.name = state,						\
		.type = PIN_MAP_TYPE_DUMMY_STATE,			\
	पूर्ण

#घोषणा PIN_MAP_MUX_GROUP(dev, state, pinctrl, grp, func)		\
	अणु								\
		.dev_name = dev,					\
		.name = state,						\
		.type = PIN_MAP_TYPE_MUX_GROUP,				\
		.ctrl_dev_name = pinctrl,				\
		.data.mux = अणु						\
			.group = grp,					\
			.function = func,				\
		पूर्ण,							\
	पूर्ण

#घोषणा PIN_MAP_MUX_GROUP_DEFAULT(dev, pinctrl, grp, func)		\
	PIN_MAP_MUX_GROUP(dev, PINCTRL_STATE_DEFAULT, pinctrl, grp, func)

#घोषणा PIN_MAP_MUX_GROUP_HOG(dev, state, grp, func)			\
	PIN_MAP_MUX_GROUP(dev, state, dev, grp, func)

#घोषणा PIN_MAP_MUX_GROUP_HOG_DEFAULT(dev, grp, func)			\
	PIN_MAP_MUX_GROUP(dev, PINCTRL_STATE_DEFAULT, dev, grp, func)

#घोषणा PIN_MAP_CONFIGS_PIN(dev, state, pinctrl, pin, cfgs)		\
	अणु								\
		.dev_name = dev,					\
		.name = state,						\
		.type = PIN_MAP_TYPE_CONFIGS_PIN,			\
		.ctrl_dev_name = pinctrl,				\
		.data.configs = अणु					\
			.group_or_pin = pin,				\
			.configs = cfgs,				\
			.num_configs = ARRAY_SIZE(cfgs),		\
		पूर्ण,							\
	पूर्ण

#घोषणा PIN_MAP_CONFIGS_PIN_DEFAULT(dev, pinctrl, pin, cfgs)		\
	PIN_MAP_CONFIGS_PIN(dev, PINCTRL_STATE_DEFAULT, pinctrl, pin, cfgs)

#घोषणा PIN_MAP_CONFIGS_PIN_HOG(dev, state, pin, cfgs)			\
	PIN_MAP_CONFIGS_PIN(dev, state, dev, pin, cfgs)

#घोषणा PIN_MAP_CONFIGS_PIN_HOG_DEFAULT(dev, pin, cfgs)			\
	PIN_MAP_CONFIGS_PIN(dev, PINCTRL_STATE_DEFAULT, dev, pin, cfgs)

#घोषणा PIN_MAP_CONFIGS_GROUP(dev, state, pinctrl, grp, cfgs)		\
	अणु								\
		.dev_name = dev,					\
		.name = state,						\
		.type = PIN_MAP_TYPE_CONFIGS_GROUP,			\
		.ctrl_dev_name = pinctrl,				\
		.data.configs = अणु					\
			.group_or_pin = grp,				\
			.configs = cfgs,				\
			.num_configs = ARRAY_SIZE(cfgs),		\
		पूर्ण,							\
	पूर्ण

#घोषणा PIN_MAP_CONFIGS_GROUP_DEFAULT(dev, pinctrl, grp, cfgs)		\
	PIN_MAP_CONFIGS_GROUP(dev, PINCTRL_STATE_DEFAULT, pinctrl, grp, cfgs)

#घोषणा PIN_MAP_CONFIGS_GROUP_HOG(dev, state, grp, cfgs)		\
	PIN_MAP_CONFIGS_GROUP(dev, state, dev, grp, cfgs)

#घोषणा PIN_MAP_CONFIGS_GROUP_HOG_DEFAULT(dev, grp, cfgs)		\
	PIN_MAP_CONFIGS_GROUP(dev, PINCTRL_STATE_DEFAULT, dev, grp, cfgs)

#अगर_घोषित CONFIG_PINCTRL

बाह्य पूर्णांक pinctrl_रेजिस्टर_mappings(स्थिर काष्ठा pinctrl_map *map,
				अचिन्हित num_maps);
बाह्य व्योम pinctrl_unरेजिस्टर_mappings(स्थिर काष्ठा pinctrl_map *map);
बाह्य व्योम pinctrl_provide_dummies(व्योम);
#अन्यथा

अटल अंतरभूत पूर्णांक pinctrl_रेजिस्टर_mappings(स्थिर काष्ठा pinctrl_map *map,
					   अचिन्हित num_maps)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pinctrl_unरेजिस्टर_mappings(स्थिर काष्ठा pinctrl_map *map)
अणु
पूर्ण

अटल अंतरभूत व्योम pinctrl_provide_dummies(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_PINCTRL */
#पूर्ण_अगर
