<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * DA9121 Single-channel dual-phase 10A buck converter
 * DA9130 Single-channel dual-phase 10A buck converter (Automotive)
 * DA9217 Single-channel dual-phase  6A buck converter
 * DA9122 Dual-channel single-phase  5A buck converter
 * DA9131 Dual-channel single-phase  5A buck converter (Automotive)
 * DA9220 Dual-channel single-phase  3A buck converter
 * DA9132 Dual-channel single-phase  3A buck converter (Automotive)
 *
 * Copyright (C) 2020  Dialog Semiconductor
 *
 * Authors: Adam Ward, Dialog Semiconductor
 */

#अगर_अघोषित __LINUX_REGULATOR_DA9121_H
#घोषणा __LINUX_REGULATOR_DA9121_H

#समावेश <linux/regulator/machine.h>

काष्ठा gpio_desc;

क्रमागत अणु
	DA9121_IDX_BUCK1,
	DA9121_IDX_BUCK2,
	DA9121_IDX_MAX
पूर्ण;

काष्ठा da9121_pdata अणु
	पूर्णांक num_buck;
	काष्ठा gpio_desc *gpiod_ren[DA9121_IDX_MAX];
	काष्ठा device_node *reg_node[DA9121_IDX_MAX];
	काष्ठा regulator_init_data *init_data[DA9121_IDX_MAX];
पूर्ण;

#पूर्ण_अगर
