<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2010 Samsung Electronics Co., Ltd.
//		http://www.samsung.com/
//
// GPIO configuration क्रम S3C64XX KeyPad device

#समावेश <linux/gpपन.स>
#समावेश "gpio-cfg.h"
#समावेश "keypad.h"
#समावेश "gpio-samsung.h"

व्योम samsung_keypad_cfg_gpio(अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols)
अणु
	/* Set all the necessary GPK pins to special-function 3: KP_ROW[x] */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPK(8), rows, S3C_GPIO_SFN(3));

	/* Set all the necessary GPL pins to special-function 3: KP_COL[x] */
	s3c_gpio_cfgrange_nopull(S3C64XX_GPL(0), cols, S3C_GPIO_SFN(3));
पूर्ण
