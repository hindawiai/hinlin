<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * National Semiconductors LP3972 PMIC chip client पूर्णांकerface
 *
 * Based on lp3971.h
 */

#अगर_अघोषित __LINUX_REGULATOR_LP3972_H
#घोषणा __LINUX_REGULATOR_LP3972_H

#समावेश <linux/regulator/machine.h>

#घोषणा LP3972_LDO1  0
#घोषणा LP3972_LDO2  1
#घोषणा LP3972_LDO3  2
#घोषणा LP3972_LDO4  3
#घोषणा LP3972_LDO5  4

#घोषणा LP3972_DCDC1 5
#घोषणा LP3972_DCDC2 6
#घोषणा LP3972_DCDC3 7

#घोषणा LP3972_NUM_REGULATORS 8

काष्ठा lp3972_regulator_subdev अणु
	पूर्णांक id;
	काष्ठा regulator_init_data *initdata;
पूर्ण;

काष्ठा lp3972_platक्रमm_data अणु
	पूर्णांक num_regulators;
	काष्ठा lp3972_regulator_subdev *regulators;
पूर्ण;

#पूर्ण_अगर
