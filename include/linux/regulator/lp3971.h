<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * National Semiconductors LP3971 PMIC chip client पूर्णांकerface
 *
 *  Copyright (C) 2009 Samsung Electronics
 *  Author: Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * Based on wm8400.h
 */

#अगर_अघोषित __LINUX_REGULATOR_LP3971_H
#घोषणा __LINUX_REGULATOR_LP3971_H

#समावेश <linux/regulator/machine.h>

#घोषणा LP3971_LDO1  0
#घोषणा LP3971_LDO2  1
#घोषणा LP3971_LDO3  2
#घोषणा LP3971_LDO4  3
#घोषणा LP3971_LDO5  4

#घोषणा LP3971_DCDC1 5
#घोषणा LP3971_DCDC2 6
#घोषणा LP3971_DCDC3 7

#घोषणा LP3971_NUM_REGULATORS 8

काष्ठा lp3971_regulator_subdev अणु
	पूर्णांक id;
	काष्ठा regulator_init_data *initdata;
पूर्ण;

काष्ठा lp3971_platक्रमm_data अणु
	पूर्णांक num_regulators;
	काष्ठा lp3971_regulator_subdev *regulators;
पूर्ण;

#पूर्ण_अगर
