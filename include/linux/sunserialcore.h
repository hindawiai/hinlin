<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* sunserialcore.h
 *
 * Generic SUN serial/kbd/ms layer.  Based entirely
 * upon drivers/sbus/अक्षर/sunserial.h which is:
 *
 * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 *
 * Port to new UART layer is:
 *
 * Copyright (C) 2002 David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित _SERIAL_SUN_H
#घोषणा _SERIAL_SUN_H

#समावेश <linux/device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/console.h>

/* Serial keyboard defines क्रम L1-A processing... */
#घोषणा SUNKBD_RESET		0xff
#घोषणा SUNKBD_L1		0x01
#घोषणा SUNKBD_UP		0x80
#घोषणा SUNKBD_A		0x4d

बाह्य अचिन्हित पूर्णांक suncore_mouse_baud_cflag_next(अचिन्हित पूर्णांक, पूर्णांक *);
बाह्य पूर्णांक suncore_mouse_baud_detection(अचिन्हित अक्षर, पूर्णांक);

बाह्य पूर्णांक sunserial_रेजिस्टर_minors(काष्ठा uart_driver *, पूर्णांक);
बाह्य व्योम sunserial_unरेजिस्टर_minors(काष्ठा uart_driver *, पूर्णांक);

बाह्य पूर्णांक sunserial_console_match(काष्ठा console *, काष्ठा device_node *,
				   काष्ठा uart_driver *, पूर्णांक, bool);
बाह्य व्योम sunserial_console_termios(काष्ठा console *,
				      काष्ठा device_node *);

#पूर्ण_अगर /* !(_SERIAL_SUN_H) */
