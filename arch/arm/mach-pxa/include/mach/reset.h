<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_RESET_H
#घोषणा __ASM_ARCH_RESET_H

#घोषणा RESET_STATUS_HARDWARE	(1 << 0)	/* Hardware Reset */
#घोषणा RESET_STATUS_WATCHDOG	(1 << 1)	/* Watchकरोg Reset */
#घोषणा RESET_STATUS_LOWPOWER	(1 << 2)	/* Low Power/Sleep Exit */
#घोषणा RESET_STATUS_GPIO	(1 << 3)	/* GPIO Reset */
#घोषणा RESET_STATUS_ALL	(0xf)

बाह्य अचिन्हित पूर्णांक reset_status;
बाह्य व्योम clear_reset_status(अचिन्हित पूर्णांक mask);

/**
 * init_gpio_reset() - रेजिस्टर GPIO as reset generator
 * @gpio: gpio nr
 * @output: set gpio as output instead of input during normal work
 * @level: output level
 */
बाह्य पूर्णांक init_gpio_reset(पूर्णांक gpio, पूर्णांक output, पूर्णांक level);

#पूर्ण_अगर /* __ASM_ARCH_RESET_H */
