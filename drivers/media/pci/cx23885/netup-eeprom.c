<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * netup-eeprom.c
 *
 * 24LC02 EEPROM driver in conjunction with NetUP Dual DVB-S2 CI card
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Abylay Ospan <aospan@netup.ru>
 */

#
#समावेश "cx23885.h"
#समावेश "netup-eeprom.h"

#घोषणा EEPROM_I2C_ADDR 0x50

पूर्णांक netup_eeprom_पढ़ो(काष्ठा i2c_adapter *i2c_adap, u8 addr)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर buf[2];

	/* Read from EEPROM */
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= EEPROM_I2C_ADDR,
			.flags	= 0,
			.buf	= &buf[0],
			.len	= 1
		पूर्ण, अणु
			.addr	= EEPROM_I2C_ADDR,
			.flags	= I2C_M_RD,
			.buf	= &buf[1],
			.len	= 1
		पूर्ण

	पूर्ण;

	buf[0] = addr;
	buf[1] = 0x0;

	ret = i2c_transfer(i2c_adap, msg, 2);

	अगर (ret != 2) अणु
		pr_err("eeprom i2c read error, status=%d\n", ret);
		वापस -1;
	पूर्ण

	वापस buf[1];
पूर्ण;

पूर्णांक netup_eeprom_ग_लिखो(काष्ठा i2c_adapter *i2c_adap, u8 addr, u8 data)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर bufw[2];

	/* Write पूर्णांकo EEPROM */
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr	= EEPROM_I2C_ADDR,
			.flags	= 0,
			.buf	= &bufw[0],
			.len	= 2
		पूर्ण
	पूर्ण;

	bufw[0] = addr;
	bufw[1] = data;

	ret = i2c_transfer(i2c_adap, msg, 1);

	अगर (ret != 1) अणु
		pr_err("eeprom i2c write error, status=%d\n", ret);
		वापस -1;
	पूर्ण

	mdelay(10); /* prophylactic delay, datasheet ग_लिखो cycle समय = 5 ms */
	वापस 0;
पूर्ण;

व्योम netup_get_card_info(काष्ठा i2c_adapter *i2c_adap,
				काष्ठा netup_card_info *cinfo)
अणु
	पूर्णांक i, j;

	cinfo->rev =  netup_eeprom_पढ़ो(i2c_adap, 63);

	क्रम (i = 64, j = 0; i < 70; i++, j++)
		cinfo->port[0].mac[j] =  netup_eeprom_पढ़ो(i2c_adap, i);

	क्रम (i = 70, j = 0; i < 76; i++, j++)
		cinfo->port[1].mac[j] =  netup_eeprom_पढ़ो(i2c_adap, i);
पूर्ण;
