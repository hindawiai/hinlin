<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ddbridge-i2c.h: Digital Devices bridge i2c driver
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

#अगर_अघोषित __DDBRIDGE_I2C_H__
#घोषणा __DDBRIDGE_I2C_H__

#समावेश <linux/i2c.h>

#समावेश "ddbridge.h"

/******************************************************************************/

व्योम ddb_i2c_release(काष्ठा ddb *dev);
पूर्णांक ddb_i2c_init(काष्ठा ddb *dev);

/******************************************************************************/

अटल पूर्णांक __maybe_unused i2c_io(काष्ठा i2c_adapter *adapter, u8 adr,
				 u8 *wbuf, u32 wlen, u8 *rbuf, u32 rlen)
अणु
	काष्ठा i2c_msg msgs[2] = अणु अणु .addr = adr,  .flags = 0,
				     .buf  = wbuf, .len   = wlen पूर्ण,
				   अणु .addr = adr,  .flags = I2C_M_RD,
				     .buf  = rbuf, .len   = rlen पूर्ण पूर्ण;

	वापस (i2c_transfer(adapter, msgs, 2) == 2) ? 0 : -1;
पूर्ण

अटल पूर्णांक __maybe_unused i2c_ग_लिखो(काष्ठा i2c_adapter *adap, u8 adr,
				    u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = adr, .flags = 0,
			       .buf = data, .len = len पूर्ण;

	वापस (i2c_transfer(adap, &msg, 1) == 1) ? 0 : -1;
पूर्ण

अटल पूर्णांक __maybe_unused i2c_पढ़ो(काष्ठा i2c_adapter *adapter, u8 adr, u8 *val)
अणु
	काष्ठा i2c_msg msgs[1] = अणु अणु .addr = adr, .flags = I2C_M_RD,
				     .buf  = val, .len   = 1 पूर्ण पूर्ण;

	वापस (i2c_transfer(adapter, msgs, 1) == 1) ? 0 : -1;
पूर्ण

अटल पूर्णांक __maybe_unused i2c_पढ़ो_regs(काष्ठा i2c_adapter *adapter,
					u8 adr, u8 reg, u8 *val, u8 len)
अणु
	काष्ठा i2c_msg msgs[2] = अणु अणु .addr = adr,  .flags = 0,
				     .buf  = &reg, .len   = 1 पूर्ण,
				   अणु .addr = adr,  .flags = I2C_M_RD,
				     .buf  = val,  .len   = len पूर्ण पूर्ण;

	वापस (i2c_transfer(adapter, msgs, 2) == 2) ? 0 : -1;
पूर्ण

अटल पूर्णांक __maybe_unused i2c_पढ़ो_regs16(काष्ठा i2c_adapter *adapter,
					  u8 adr, u16 reg, u8 *val, u8 len)
अणु
	u8 msg[2] = अणु reg >> 8, reg & 0xff पूर्ण;
	काष्ठा i2c_msg msgs[2] = अणु अणु .addr = adr, .flags = 0,
				     .buf  = msg, .len   = 2 पूर्ण,
				   अणु .addr = adr, .flags = I2C_M_RD,
				     .buf  = val, .len   = len पूर्ण पूर्ण;

	वापस (i2c_transfer(adapter, msgs, 2) == 2) ? 0 : -1;
पूर्ण

अटल पूर्णांक __maybe_unused i2c_ग_लिखो_reg16(काष्ठा i2c_adapter *adap,
					  u8 adr, u16 reg, u8 val)
अणु
	u8 msg[3] = अणु reg >> 8, reg & 0xff, val पूर्ण;

	वापस i2c_ग_लिखो(adap, adr, msg, 3);
पूर्ण

अटल पूर्णांक __maybe_unused i2c_ग_लिखो_reg(काष्ठा i2c_adapter *adap,
					u8 adr, u8 reg, u8 val)
अणु
	u8 msg[2] = अणु reg, val पूर्ण;

	वापस i2c_ग_लिखो(adap, adr, msg, 2);
पूर्ण

अटल पूर्णांक __maybe_unused i2c_पढ़ो_reg16(काष्ठा i2c_adapter *adapter,
					 u8 adr, u16 reg, u8 *val)
अणु
	वापस i2c_पढ़ो_regs16(adapter, adr, reg, val, 1);
पूर्ण

अटल पूर्णांक __maybe_unused i2c_पढ़ो_reg(काष्ठा i2c_adapter *adapter,
				       u8 adr, u8 reg, u8 *val)
अणु
	वापस i2c_पढ़ो_regs(adapter, adr, reg, val, 1);
पूर्ण

#पूर्ण_अगर /* __DDBRIDGE_I2C_H__ */
