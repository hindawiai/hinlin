<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Samsung Keypad platक्रमm data definitions
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#अगर_अघोषित __SAMSUNG_KEYPAD_H
#घोषणा __SAMSUNG_KEYPAD_H

#समावेश <linux/input/matrix_keypad.h>

#घोषणा SAMSUNG_MAX_ROWS	8
#घोषणा SAMSUNG_MAX_COLS	8

/**
 * काष्ठा samsung_keypad_platdata - Platक्रमm device data क्रम Samsung Keypad.
 * @keymap_data: poपूर्णांकer to &matrix_keymap_data.
 * @rows: number of keypad row supported.
 * @cols: number of keypad col supported.
 * @no_स्वतःrepeat: disable key स्वतःrepeat.
 * @wakeup: controls whether the device should be set up as wakeup source.
 * @cfg_gpio: configure the GPIO.
 *
 * Initialisation data specअगरic to either the machine or the platक्रमm
 * क्रम the device driver to use or call-back when configuring gpio.
 */
काष्ठा samsung_keypad_platdata अणु
	स्थिर काष्ठा matrix_keymap_data	*keymap_data;
	अचिन्हित पूर्णांक rows;
	अचिन्हित पूर्णांक cols;
	bool no_स्वतःrepeat;
	bool wakeup;

	व्योम (*cfg_gpio)(अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols);
पूर्ण;

#पूर्ण_अगर /* __SAMSUNG_KEYPAD_H */
