<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Internal पूर्णांकerface between the core pin control प्रणाली and the
 * pinmux portions
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_घोषित CONFIG_PINMUX

पूर्णांक pinmux_check_ops(काष्ठा pinctrl_dev *pctldev);

पूर्णांक pinmux_validate_map(स्थिर काष्ठा pinctrl_map *map, पूर्णांक i);

bool pinmux_can_be_used_क्रम_gpio(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin);

पूर्णांक pinmux_request_gpio(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range,
			अचिन्हित pin, अचिन्हित gpio);
व्योम pinmux_मुक्त_gpio(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
		      काष्ठा pinctrl_gpio_range *range);
पूर्णांक pinmux_gpio_direction(काष्ठा pinctrl_dev *pctldev,
			  काष्ठा pinctrl_gpio_range *range,
			  अचिन्हित pin, bool input);

पूर्णांक pinmux_map_to_setting(स्थिर काष्ठा pinctrl_map *map,
			  काष्ठा pinctrl_setting *setting);
व्योम pinmux_मुक्त_setting(स्थिर काष्ठा pinctrl_setting *setting);
पूर्णांक pinmux_enable_setting(स्थिर काष्ठा pinctrl_setting *setting);
व्योम pinmux_disable_setting(स्थिर काष्ठा pinctrl_setting *setting);

#अन्यथा

अटल अंतरभूत पूर्णांक pinmux_check_ops(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinmux_validate_map(स्थिर काष्ठा pinctrl_map *map, पूर्णांक i)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool pinmux_can_be_used_क्रम_gpio(काष्ठा pinctrl_dev *pctldev,
					       अचिन्हित pin)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक pinmux_request_gpio(काष्ठा pinctrl_dev *pctldev,
			काष्ठा pinctrl_gpio_range *range,
			अचिन्हित pin, अचिन्हित gpio)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pinmux_मुक्त_gpio(काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित pin,
				    काष्ठा pinctrl_gpio_range *range)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pinmux_gpio_direction(काष्ठा pinctrl_dev *pctldev,
					काष्ठा pinctrl_gpio_range *range,
					अचिन्हित pin, bool input)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinmux_map_to_setting(स्थिर काष्ठा pinctrl_map *map,
			  काष्ठा pinctrl_setting *setting)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pinmux_मुक्त_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pinmux_enable_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pinmux_disable_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
पूर्ण

#पूर्ण_अगर

#अगर defined(CONFIG_PINMUX) && defined(CONFIG_DEBUG_FS)

व्योम pinmux_show_map(काष्ठा seq_file *s, स्थिर काष्ठा pinctrl_map *map);
व्योम pinmux_show_setting(काष्ठा seq_file *s,
			 स्थिर काष्ठा pinctrl_setting *setting);
व्योम pinmux_init_device_debugfs(काष्ठा dentry *devroot,
				काष्ठा pinctrl_dev *pctldev);

#अन्यथा

अटल अंतरभूत व्योम pinmux_show_map(काष्ठा seq_file *s,
				   स्थिर काष्ठा pinctrl_map *map)
अणु
पूर्ण

अटल अंतरभूत व्योम pinmux_show_setting(काष्ठा seq_file *s,
				       स्थिर काष्ठा pinctrl_setting *setting)
अणु
पूर्ण

अटल अंतरभूत व्योम pinmux_init_device_debugfs(काष्ठा dentry *devroot,
					      काष्ठा pinctrl_dev *pctldev)
अणु
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_GENERIC_PINMUX_FUNCTIONS

/**
 * काष्ठा function_desc - generic function descriptor
 * @name: name of the function
 * @group_names: array of pin group names
 * @num_group_names: number of pin group names
 * @data: pin controller driver specअगरic data
 */
काष्ठा function_desc अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर **group_names;
	पूर्णांक num_group_names;
	व्योम *data;
पूर्ण;

पूर्णांक pinmux_generic_get_function_count(काष्ठा pinctrl_dev *pctldev);

स्थिर अक्षर *
pinmux_generic_get_function_name(काष्ठा pinctrl_dev *pctldev,
				 अचिन्हित पूर्णांक selector);

पूर्णांक pinmux_generic_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				       अचिन्हित पूर्णांक selector,
				       स्थिर अक्षर * स्थिर **groups,
				       अचिन्हित * स्थिर num_groups);

काष्ठा function_desc *pinmux_generic_get_function(काष्ठा pinctrl_dev *pctldev,
						  अचिन्हित पूर्णांक selector);

पूर्णांक pinmux_generic_add_function(काष्ठा pinctrl_dev *pctldev,
				स्थिर अक्षर *name,
				स्थिर अक्षर **groups,
				अचिन्हित स्थिर num_groups,
				व्योम *data);

पूर्णांक pinmux_generic_हटाओ_function(काष्ठा pinctrl_dev *pctldev,
				   अचिन्हित पूर्णांक selector);

व्योम pinmux_generic_मुक्त_functions(काष्ठा pinctrl_dev *pctldev);

#अन्यथा

अटल अंतरभूत व्योम pinmux_generic_मुक्त_functions(काष्ठा pinctrl_dev *pctldev)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_GENERIC_PINMUX_FUNCTIONS */
