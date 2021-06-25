<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ddbridge-hw.h: Digital Devices bridge hardware maps
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *                         Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _DDBRIDGE_HW_H_
#घोषणा _DDBRIDGE_HW_H_

#समावेश "ddbridge.h"

/******************************************************************************/

#घोषणा DDVID 0xdd01 /* Digital Devices Venकरोr ID */

/******************************************************************************/

काष्ठा ddb_device_id अणु
	u16 venकरोr;
	u16 device;
	u16 subvenकरोr;
	u16 subdevice;
	स्थिर काष्ठा ddb_info *info;
पूर्ण;

/******************************************************************************/

स्थिर काष्ठा ddb_info *get_ddb_info(u16 venकरोr, u16 device,
				    u16 subvenकरोr, u16 subdevice);

#पूर्ण_अगर /* _DDBRIDGE_HW_H */
