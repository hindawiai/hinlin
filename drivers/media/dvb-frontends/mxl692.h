<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Driver क्रम the MaxLinear MxL69x family of tuners/demods
 *
 * Copyright (C) 2020 Brad Love <brad@nextdimension.cc>
 *
 * based on code:
 * Copyright (c) 2016 MaxLinear, Inc. All rights reserved
 * which was released under GPL V2
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _MXL692_H_
#घोषणा _MXL692_H_

#समावेश <media/dvb_frontend.h>

#घोषणा MXL692_FIRMWARE "dvb-demod-mxl692.fw"

काष्ठा mxl692_config अणु
	अचिन्हित अक्षर  id;
	u8 i2c_addr;
	/*
	 * frontend
	 * वापसed by driver
	 */
	काष्ठा dvb_frontend **fe;
पूर्ण;

#पूर्ण_अगर /* _MXL692_H_ */
