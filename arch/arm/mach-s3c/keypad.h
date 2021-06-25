<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Samsung Platक्रमm - Keypad platक्रमm data definitions
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#अगर_अघोषित __PLAT_SAMSUNG_KEYPAD_H
#घोषणा __PLAT_SAMSUNG_KEYPAD_H

#समावेश <linux/input/samsung-keypad.h>

/**
 * samsung_keypad_set_platdata - Set platक्रमm data क्रम Samsung Keypad device.
 * @pd: Platक्रमm data to रेजिस्टर to device.
 *
 * Register the given platक्रमm data क्रम use with Samsung Keypad device.
 * The call will copy the platक्रमm data, so the board definitions can
 * make the काष्ठाure itself __initdata.
 */
बाह्य व्योम samsung_keypad_set_platdata(काष्ठा samsung_keypad_platdata *pd);

/* defined by architecture to configure gpio. */
बाह्य व्योम samsung_keypad_cfg_gpio(अचिन्हित पूर्णांक rows, अचिन्हित पूर्णांक cols);

#पूर्ण_अगर /* __PLAT_SAMSUNG_KEYPAD_H */
