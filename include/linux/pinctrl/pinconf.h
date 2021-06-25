<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface the pinconfig portions of the pinctrl subप्रणाली
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 * This पूर्णांकerface is used in the core to keep track of pins.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित __LINUX_PINCTRL_PINCONF_H
#घोषणा __LINUX_PINCTRL_PINCONF_H

#समावेश <linux/types.h>

काष्ठा pinctrl_dev;
काष्ठा seq_file;

/**
 * काष्ठा pinconf_ops - pin config operations, to be implemented by
 * pin configuration capable drivers.
 * @is_generic: क्रम pin controllers that want to use the generic पूर्णांकerface,
 *	this flag tells the framework that it's generic.
 * @pin_config_get: get the config of a certain pin, अगर the requested config
 *	is not available on this controller this should वापस -ENOTSUPP
 *	and अगर it is available but disabled it should वापस -EINVAL
 * @pin_config_set: configure an inभागidual pin
 * @pin_config_group_get: get configurations क्रम an entire pin group; should
 *	वापस -ENOTSUPP and -EINVAL using the same rules as pin_config_get.
 * @pin_config_group_set: configure all pins in a group
 * @pin_config_dbg_show: optional debugfs display hook that will provide
 *	per-device info क्रम a certain pin in debugfs
 * @pin_config_group_dbg_show: optional debugfs display hook that will provide
 *	per-device info क्रम a certain group in debugfs
 * @pin_config_config_dbg_show: optional debugfs display hook that will decode
 *	and display a driver's pin configuration parameter
 */
काष्ठा pinconf_ops अणु
#अगर_घोषित CONFIG_GENERIC_PINCONF
	bool is_generic;
#पूर्ण_अगर
	पूर्णांक (*pin_config_get) (काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित pin,
			       अचिन्हित दीर्घ *config);
	पूर्णांक (*pin_config_set) (काष्ठा pinctrl_dev *pctldev,
			       अचिन्हित pin,
			       अचिन्हित दीर्घ *configs,
			       अचिन्हित num_configs);
	पूर्णांक (*pin_config_group_get) (काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित selector,
				     अचिन्हित दीर्घ *config);
	पूर्णांक (*pin_config_group_set) (काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित selector,
				     अचिन्हित दीर्घ *configs,
				     अचिन्हित num_configs);
	व्योम (*pin_config_dbg_show) (काष्ठा pinctrl_dev *pctldev,
				     काष्ठा seq_file *s,
				     अचिन्हित offset);
	व्योम (*pin_config_group_dbg_show) (काष्ठा pinctrl_dev *pctldev,
					   काष्ठा seq_file *s,
					   अचिन्हित selector);
	व्योम (*pin_config_config_dbg_show) (काष्ठा pinctrl_dev *pctldev,
					    काष्ठा seq_file *s,
					    अचिन्हित दीर्घ config);
पूर्ण;

#पूर्ण_अगर /* __LINUX_PINCTRL_PINCONF_H */
