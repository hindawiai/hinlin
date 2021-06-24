<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * wm8400 client पूर्णांकerface
 *
 * Copyright 2008 Wolfson Microelectronics plc
 */

#अगर_अघोषित __LINUX_MFD_WM8400_H
#घोषणा __LINUX_MFD_WM8400_H

#समावेश <linux/regulator/machine.h>

#घोषणा WM8400_LDO1  0
#घोषणा WM8400_LDO2  1
#घोषणा WM8400_LDO3  2
#घोषणा WM8400_LDO4  3
#घोषणा WM8400_DCDC1 4
#घोषणा WM8400_DCDC2 5

काष्ठा wm8400_platक्रमm_data अणु
	पूर्णांक (*platक्रमm_init)(काष्ठा device *dev);
पूर्ण;

पूर्णांक wm8400_रेजिस्टर_regulator(काष्ठा device *dev, पूर्णांक reg,
			      काष्ठा regulator_init_data *initdata);

#पूर्ण_अगर
