<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

/*
 * AMD FCH gpio driver platक्रमm-data
 *
 * Copyright (C) 2018 metux IT consult
 * Author: Enrico Weigelt <info@metux.net>
 *
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_GPIO_AMD_FCH_H
#घोषणा __LINUX_PLATFORM_DATA_GPIO_AMD_FCH_H

#घोषणा AMD_FCH_GPIO_DRIVER_NAME "gpio_amd_fch"

/*
 * gpio रेजिस्टर index definitions
 */
#घोषणा AMD_FCH_GPIO_REG_GPIO49		0x40
#घोषणा AMD_FCH_GPIO_REG_GPIO50		0x41
#घोषणा AMD_FCH_GPIO_REG_GPIO51		0x42
#घोषणा AMD_FCH_GPIO_REG_GPIO55_DEVSLP0	0x43
#घोषणा AMD_FCH_GPIO_REG_GPIO57		0x44
#घोषणा AMD_FCH_GPIO_REG_GPIO58		0x45
#घोषणा AMD_FCH_GPIO_REG_GPIO59_DEVSLP1	0x46
#घोषणा AMD_FCH_GPIO_REG_GPIO64		0x47
#घोषणा AMD_FCH_GPIO_REG_GPIO68		0x48
#घोषणा AMD_FCH_GPIO_REG_GPIO66_SPKR	0x5B
#घोषणा AMD_FCH_GPIO_REG_GPIO71		0x4D
#घोषणा AMD_FCH_GPIO_REG_GPIO32_GE1	0x59
#घोषणा AMD_FCH_GPIO_REG_GPIO33_GE2	0x5A
#घोषणा AMT_FCH_GPIO_REG_GEVT22		0x09

/*
 * काष्ठा amd_fch_gpio_pdata - GPIO chip platक्रमm data
 * @gpio_num: number of entries
 * @gpio_reg: array of gpio रेजिस्टरs
 * @gpio_names: array of gpio names
 */
काष्ठा amd_fch_gpio_pdata अणु
	पूर्णांक			gpio_num;
	पूर्णांक			*gpio_reg;
	स्थिर अक्षर * स्थिर	*gpio_names;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PLATFORM_DATA_GPIO_AMD_FCH_H */
