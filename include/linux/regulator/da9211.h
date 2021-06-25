<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * da9211.h - Regulator device driver क्रम DA9211/DA9212
 * /DA9213/DA9223/DA9214/DA9224/DA9215/DA9225
 * Copyright (C) 2015  Dialog Semiconductor Ltd.
 */

#अगर_अघोषित __LINUX_REGULATOR_DA9211_H
#घोषणा __LINUX_REGULATOR_DA9211_H

#समावेश <linux/regulator/machine.h>

#घोषणा DA9211_MAX_REGULATORS	2

काष्ठा gpio_desc;

क्रमागत da9211_chip_id अणु
	DA9211,
	DA9212,
	DA9213,
	DA9223,
	DA9214,
	DA9224,
	DA9215,
	DA9225,
पूर्ण;

काष्ठा da9211_pdata अणु
	/*
	 * Number of buck
	 * 1 : 4 phase 1 buck
	 * 2 : 2 phase 2 buck
	 */
	पूर्णांक num_buck;
	काष्ठा gpio_desc *gpiod_ren[DA9211_MAX_REGULATORS];
	काष्ठा device_node *reg_node[DA9211_MAX_REGULATORS];
	काष्ठा regulator_init_data *init_data[DA9211_MAX_REGULATORS];
पूर्ण;
#पूर्ण_अगर
