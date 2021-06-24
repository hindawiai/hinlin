<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _LIBPS2_H
#घोषणा _LIBPS2_H

/*
 * Copyright (C) 1999-2002 Vojtech Pavlik
 * Copyright (C) 2004 Dmitry Torokhov
 */

#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#घोषणा PS2_CMD_SETSCALE11	0x00e6
#घोषणा PS2_CMD_SETRES		0x10e8
#घोषणा PS2_CMD_GETID		0x02f2
#घोषणा PS2_CMD_RESET_BAT	0x02ff

#घोषणा PS2_RET_BAT		0xaa
#घोषणा PS2_RET_ID		0x00
#घोषणा PS2_RET_ACK		0xfa
#घोषणा PS2_RET_NAK		0xfe
#घोषणा PS2_RET_ERR		0xfc

#घोषणा PS2_FLAG_ACK		BIT(0)	/* Waiting क्रम ACK/NAK */
#घोषणा PS2_FLAG_CMD		BIT(1)	/* Waiting क्रम a command to finish */
#घोषणा PS2_FLAG_CMD1		BIT(2)	/* Waiting क्रम the first byte of command response */
#घोषणा PS2_FLAG_WAITID		BIT(3)	/* Command executing is GET ID */
#घोषणा PS2_FLAG_NAK		BIT(4)	/* Last transmission was NAKed */
#घोषणा PS2_FLAG_ACK_CMD	BIT(5)	/* Waiting to ACK the command (first) byte */

काष्ठा ps2dev अणु
	काष्ठा serio *serio;

	/* Ensures that only one command is executing at a समय */
	काष्ठा mutex cmd_mutex;

	/* Used to संकेत completion from पूर्णांकerrupt handler */
	रुको_queue_head_t रुको;

	अचिन्हित दीर्घ flags;
	u8 cmdbuf[8];
	u8 cmdcnt;
	u8 nak;
पूर्ण;

व्योम ps2_init(काष्ठा ps2dev *ps2dev, काष्ठा serio *serio);
पूर्णांक ps2_sendbyte(काष्ठा ps2dev *ps2dev, u8 byte, अचिन्हित पूर्णांक समयout);
व्योम ps2_drain(काष्ठा ps2dev *ps2dev, माप_प्रकार maxbytes, अचिन्हित पूर्णांक समयout);
व्योम ps2_begin_command(काष्ठा ps2dev *ps2dev);
व्योम ps2_end_command(काष्ठा ps2dev *ps2dev);
पूर्णांक __ps2_command(काष्ठा ps2dev *ps2dev, u8 *param, अचिन्हित पूर्णांक command);
पूर्णांक ps2_command(काष्ठा ps2dev *ps2dev, u8 *param, अचिन्हित पूर्णांक command);
पूर्णांक ps2_sliced_command(काष्ठा ps2dev *ps2dev, u8 command);
bool ps2_handle_ack(काष्ठा ps2dev *ps2dev, u8 data);
bool ps2_handle_response(काष्ठा ps2dev *ps2dev, u8 data);
व्योम ps2_cmd_पातed(काष्ठा ps2dev *ps2dev);
bool ps2_is_keyboard_id(u8 id);

#पूर्ण_अगर /* _LIBPS2_H */
