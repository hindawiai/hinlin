<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 1998-2009 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#अगर_अघोषित __VIA_I2C_H__
#घोषणा __VIA_I2C_H__

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

काष्ठा via_i2c_stuff अणु
	u16 i2c_port;			/* GPIO or I2C port */
	u16 is_active;			/* Being used as I2C? */
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
पूर्ण;


पूर्णांक viafb_i2c_पढ़ोbyte(u8 adap, u8 slave_addr, u8 index, u8 *pdata);
पूर्णांक viafb_i2c_ग_लिखोbyte(u8 adap, u8 slave_addr, u8 index, u8 data);
पूर्णांक viafb_i2c_पढ़ोbytes(u8 adap, u8 slave_addr, u8 index, u8 *buff, पूर्णांक buff_len);
काष्ठा i2c_adapter *viafb_find_i2c_adapter(क्रमागत viafb_i2c_adap which);

बाह्य पूर्णांक viafb_i2c_init(व्योम);
बाह्य व्योम viafb_i2c_निकास(व्योम);
#पूर्ण_अगर /* __VIA_I2C_H__ */
