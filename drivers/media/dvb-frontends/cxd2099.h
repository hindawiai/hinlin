<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2099.h: Driver क्रम the Sony CXD2099AR Common Interface Controller
 *
 * Copyright (C) 2010-2011 Digital Devices GmbH
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

#अगर_अघोषित _CXD2099_H_
#घोषणा _CXD2099_H_

#समावेश <media/dvb_ca_en50221.h>

काष्ठा cxd2099_cfg अणु
	u32 bitrate;
	u8  polarity;
	u8  घड़ी_mode;

	u32 max_i2c;

	/* ptr to DVB CA काष्ठा */
	काष्ठा dvb_ca_en50221 **en;
पूर्ण;

#पूर्ण_अगर
