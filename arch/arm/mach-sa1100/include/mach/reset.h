<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_RESET_H
#घोषणा __ASM_ARCH_RESET_H

#समावेश "hardware.h"

#घोषणा RESET_STATUS_HARDWARE	(1 << 0)	/* Hardware Reset */
#घोषणा RESET_STATUS_WATCHDOG	(1 << 1)	/* Watchकरोg Reset */
#घोषणा RESET_STATUS_LOWPOWER	(1 << 2)	/* Exit from Low Power/Sleep */
#घोषणा RESET_STATUS_GPIO	(1 << 3)	/* GPIO Reset */
#घोषणा RESET_STATUS_ALL	(0xf)

बाह्य अचिन्हित पूर्णांक reset_status;
अटल अंतरभूत व्योम clear_reset_status(अचिन्हित पूर्णांक mask)
अणु
	RCSR = mask;
पूर्ण

#पूर्ण_अगर /* __ASM_ARCH_RESET_H */
