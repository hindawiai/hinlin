<शैली गुरु>
/*
 * Texas Instruments' Message Manager
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित TI_MSGMGR_H
#घोषणा TI_MSGMGR_H

/**
 * काष्ठा ti_msgmgr_message - Message Manager काष्ठाure
 * @len: Length of data in the Buffer
 * @buf: Buffer poपूर्णांकer
 *
 * This is the काष्ठाure क्रम data used in mbox_send_message
 * the length of data buffer used depends on the SoC पूर्णांकegration
 * parameters - each message may be 64, 128 bytes दीर्घ depending
 * on SoC. Client is supposed to be aware of this.
 */
काष्ठा ti_msgmgr_message अणु
	माप_प्रकार len;
	u8 *buf;
पूर्ण;

#पूर्ण_अगर /* TI_MSGMGR_H */
