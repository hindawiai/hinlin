<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */
#अगर_अघोषित USB6FIRE_COMM_H
#घोषणा USB6FIRE_COMM_H

#समावेश "common.h"

क्रमागत /* settings क्रम comm */
अणु
	COMM_RECEIVER_बफ_मानE = 64,
पूर्ण;

काष्ठा comm_runसमय अणु
	काष्ठा sfire_chip *chip;

	काष्ठा urb receiver;
	u8 *receiver_buffer;

	u8 serial; /* urb serial */

	व्योम (*init_urb)(काष्ठा comm_runसमय *rt, काष्ठा urb *urb, u8 *buffer,
			व्योम *context, व्योम(*handler)(काष्ठा urb *urb));
	/* ग_लिखोs control data to the device */
	पूर्णांक (*ग_लिखो8)(काष्ठा comm_runसमय *rt, u8 request, u8 reg, u8 value);
	पूर्णांक (*ग_लिखो16)(काष्ठा comm_runसमय *rt, u8 request, u8 reg,
			u8 vh, u8 vl);
पूर्ण;

पूर्णांक usb6fire_comm_init(काष्ठा sfire_chip *chip);
व्योम usb6fire_comm_पात(काष्ठा sfire_chip *chip);
व्योम usb6fire_comm_destroy(काष्ठा sfire_chip *chip);
#पूर्ण_अगर /* USB6FIRE_COMM_H */

