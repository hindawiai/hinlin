<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * netup-init.c
 *
 * NetUP Dual DVB-S2 CI driver
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 * Copyright (C) 2009 Abylay Ospan <aospan@netup.ru>
 */

#समावेश "cx23885.h"
#समावेश "netup-init.h"

अटल व्योम i2c_av_ग_लिखो(काष्ठा i2c_adapter *i2c, u16 reg, u8 val)
अणु
	पूर्णांक ret;
	u8 buf[3];
	काष्ठा i2c_msg msg = अणु
		.addr	= 0x88 >> 1,
		.flags	= 0,
		.buf	= buf,
		.len	= 3
	पूर्ण;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;
	buf[2] = val;

	ret = i2c_transfer(i2c, &msg, 1);

	अगर (ret != 1)
		pr_err("%s: i2c write error!\n", __func__);
पूर्ण

अटल व्योम i2c_av_ग_लिखो4(काष्ठा i2c_adapter *i2c, u16 reg, u32 val)
अणु
	पूर्णांक ret;
	u8 buf[6];
	काष्ठा i2c_msg msg = अणु
		.addr	= 0x88 >> 1,
		.flags	= 0,
		.buf	= buf,
		.len	= 6
	पूर्ण;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;
	buf[2] = val & 0xff;
	buf[3] = (val >> 8) & 0xff;
	buf[4] = (val >> 16) & 0xff;
	buf[5] = val >> 24;

	ret = i2c_transfer(i2c, &msg, 1);

	अगर (ret != 1)
		pr_err("%s: i2c write error!\n", __func__);
पूर्ण

अटल u8 i2c_av_पढ़ो(काष्ठा i2c_adapter *i2c, u16 reg)
अणु
	पूर्णांक ret;
	u8 buf[2];
	काष्ठा i2c_msg msg = अणु
		.addr	= 0x88 >> 1,
		.flags	= 0,
		.buf	= buf,
		.len	= 2
	पूर्ण;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	ret = i2c_transfer(i2c, &msg, 1);

	अगर (ret != 1)
		pr_err("%s: i2c write error!\n", __func__);

	msg.flags = I2C_M_RD;
	msg.len = 1;

	ret = i2c_transfer(i2c, &msg, 1);

	अगर (ret != 1)
		pr_err("%s: i2c read error!\n", __func__);

	वापस buf[0];
पूर्ण

अटल व्योम i2c_av_and_or(काष्ठा i2c_adapter *i2c, u16 reg, अचिन्हित and_mask,
								u8 or_value)
अणु
	i2c_av_ग_लिखो(i2c, reg, (i2c_av_पढ़ो(i2c, reg) & and_mask) | or_value);
पूर्ण
/* set 27MHz on AUX_CLK */
व्योम netup_initialize(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा cx23885_i2c *i2c_bus = &dev->i2c_bus[2];
	काष्ठा i2c_adapter *i2c = &i2c_bus->i2c_adap;

	/* Stop microcontroller */
	i2c_av_and_or(i2c, 0x803, ~0x10, 0x00);

	/* Aux PLL frac क्रम 27 MHz */
	i2c_av_ग_लिखो4(i2c, 0x114, 0xea0eb3);

	/* Aux PLL पूर्णांक क्रम 27 MHz */
	i2c_av_ग_लिखो4(i2c, 0x110, 0x090319);

	/* start microcontroller */
	i2c_av_and_or(i2c, 0x803, ~0x10, 0x10);
पूर्ण
