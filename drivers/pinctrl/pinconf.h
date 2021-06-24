<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Internal पूर्णांकerface between the core pin control प्रणाली and the
 * pin config portions
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * Based on bits of regulator core, gpio core and clk core
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#अगर_घोषित CONFIG_PINCONF

पूर्णांक pinconf_check_ops(काष्ठा pinctrl_dev *pctldev);
पूर्णांक pinconf_validate_map(स्थिर काष्ठा pinctrl_map *map, पूर्णांक i);
पूर्णांक pinconf_map_to_setting(स्थिर काष्ठा pinctrl_map *map,
			  काष्ठा pinctrl_setting *setting);
व्योम pinconf_मुक्त_setting(स्थिर काष्ठा pinctrl_setting *setting);
पूर्णांक pinconf_apply_setting(स्थिर काष्ठा pinctrl_setting *setting);

पूर्णांक pinconf_set_config(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
		       अचिन्हित दीर्घ *configs, माप_प्रकार nconfigs);

/*
 * You will only be पूर्णांकerested in these अगर you're using PINCONF
 * so करोn't supply any stubs क्रम these.
 */
पूर्णांक pin_config_get_क्रम_pin(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
			   अचिन्हित दीर्घ *config);
पूर्णांक pin_config_group_get(स्थिर अक्षर *dev_name, स्थिर अक्षर *pin_group,
			 अचिन्हित दीर्घ *config);

#अन्यथा

अटल अंतरभूत पूर्णांक pinconf_check_ops(काष्ठा pinctrl_dev *pctldev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinconf_validate_map(स्थिर काष्ठा pinctrl_map *map, पूर्णांक i)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinconf_map_to_setting(स्थिर काष्ठा pinctrl_map *map,
			  काष्ठा pinctrl_setting *setting)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pinconf_मुक्त_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक pinconf_apply_setting(स्थिर काष्ठा pinctrl_setting *setting)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pinconf_set_config(काष्ठा pinctrl_dev *pctldev, अचिन्हित pin,
				     अचिन्हित दीर्घ *configs, माप_प्रकार nconfigs)
अणु
	वापस -ENOTSUPP;
पूर्ण

#पूर्ण_अगर

#अगर defined(CONFIG_PINCONF) && defined(CONFIG_DEBUG_FS)

व्योम pinconf_show_map(काष्ठा seq_file *s, स्थिर काष्ठा pinctrl_map *map);
व्योम pinconf_show_setting(काष्ठा seq_file *s,
			  स्थिर काष्ठा pinctrl_setting *setting);
व्योम pinconf_init_device_debugfs(काष्ठा dentry *devroot,
				 काष्ठा pinctrl_dev *pctldev);

#अन्यथा

अटल अंतरभूत व्योम pinconf_show_map(काष्ठा seq_file *s,
				    स्थिर काष्ठा pinctrl_map *map)
अणु
पूर्ण

अटल अंतरभूत व्योम pinconf_show_setting(काष्ठा seq_file *s,
					स्थिर काष्ठा pinctrl_setting *setting)
अणु
पूर्ण

अटल अंतरभूत व्योम pinconf_init_device_debugfs(काष्ठा dentry *devroot,
					       काष्ठा pinctrl_dev *pctldev)
अणु
पूर्ण

#पूर्ण_अगर

/*
 * The following functions are available अगर the driver uses the generic
 * pin config.
 */

#अगर defined(CONFIG_GENERIC_PINCONF) && defined(CONFIG_DEBUG_FS)

व्योम pinconf_generic_dump_pins(काष्ठा pinctrl_dev *pctldev,
			       काष्ठा seq_file *s, स्थिर अक्षर *gname,
			       अचिन्हित pin);

व्योम pinconf_generic_dump_config(काष्ठा pinctrl_dev *pctldev,
				 काष्ठा seq_file *s, अचिन्हित दीर्घ config);
#अन्यथा

अटल अंतरभूत व्योम pinconf_generic_dump_pins(काष्ठा pinctrl_dev *pctldev,
					     काष्ठा seq_file *s,
					     स्थिर अक्षर *gname, अचिन्हित pin)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम pinconf_generic_dump_config(काष्ठा pinctrl_dev *pctldev,
					       काष्ठा seq_file *s,
					       अचिन्हित दीर्घ config)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_GENERIC_PINCONF) && defined(CONFIG_OF)
पूर्णांक pinconf_generic_parse_dt_config(काष्ठा device_node *np,
				    काष्ठा pinctrl_dev *pctldev,
				    अचिन्हित दीर्घ **configs,
				    अचिन्हित पूर्णांक *nconfigs);
#पूर्ण_अगर
