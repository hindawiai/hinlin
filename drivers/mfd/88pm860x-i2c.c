<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C driver क्रम Marvell 88PM860x
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *
 * Author: Haojian Zhuang <haojian.zhuang@marvell.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/88pm860x.h>

पूर्णांक pm860x_reg_पढ़ो(काष्ठा i2c_client *i2c, पूर्णांक reg)
अणु
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(i2c);
	काष्ठा regmap *map = (i2c == chip->client) ? chip->regmap
				: chip->regmap_companion;
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(map, reg, &data);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस (पूर्णांक)data;
पूर्ण
EXPORT_SYMBOL(pm860x_reg_पढ़ो);

पूर्णांक pm860x_reg_ग_लिखो(काष्ठा i2c_client *i2c, पूर्णांक reg,
		     अचिन्हित अक्षर data)
अणु
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(i2c);
	काष्ठा regmap *map = (i2c == chip->client) ? chip->regmap
				: chip->regmap_companion;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(map, reg, data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm860x_reg_ग_लिखो);

पूर्णांक pm860x_bulk_पढ़ो(काष्ठा i2c_client *i2c, पूर्णांक reg,
		     पूर्णांक count, अचिन्हित अक्षर *buf)
अणु
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(i2c);
	काष्ठा regmap *map = (i2c == chip->client) ? chip->regmap
				: chip->regmap_companion;
	पूर्णांक ret;

	ret = regmap_raw_पढ़ो(map, reg, buf, count);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm860x_bulk_पढ़ो);

पूर्णांक pm860x_bulk_ग_लिखो(काष्ठा i2c_client *i2c, पूर्णांक reg,
		      पूर्णांक count, अचिन्हित अक्षर *buf)
अणु
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(i2c);
	काष्ठा regmap *map = (i2c == chip->client) ? chip->regmap
				: chip->regmap_companion;
	पूर्णांक ret;

	ret = regmap_raw_ग_लिखो(map, reg, buf, count);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm860x_bulk_ग_लिखो);

पूर्णांक pm860x_set_bits(काष्ठा i2c_client *i2c, पूर्णांक reg,
		    अचिन्हित अक्षर mask, अचिन्हित अक्षर data)
अणु
	काष्ठा pm860x_chip *chip = i2c_get_clientdata(i2c);
	काष्ठा regmap *map = (i2c == chip->client) ? chip->regmap
				: chip->regmap_companion;
	पूर्णांक ret;

	ret = regmap_update_bits(map, reg, mask, data);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm860x_set_bits);

अटल पूर्णांक पढ़ो_device(काष्ठा i2c_client *i2c, पूर्णांक reg,
		       पूर्णांक bytes, व्योम *dest)
अणु
	अचिन्हित अक्षर msgbuf0[I2C_SMBUS_BLOCK_MAX + 3];
	अचिन्हित अक्षर msgbuf1[I2C_SMBUS_BLOCK_MAX + 2];
	काष्ठा i2c_adapter *adap = i2c->adapter;
	काष्ठा i2c_msg msg[2] = अणु
					अणु
						.addr = i2c->addr,
						.flags = 0,
						.len = 1,
						.buf = msgbuf0
					पूर्ण,
					अणु	.addr = i2c->addr,
						.flags = I2C_M_RD,
						.len = 0,
						.buf = msgbuf1
					पूर्ण,
				पूर्ण;
	पूर्णांक num = 1, ret = 0;

	अगर (dest == शून्य)
		वापस -EINVAL;
	msgbuf0[0] = (अचिन्हित अक्षर)reg;	/* command */
	msg[1].len = bytes;

	/* अगर data needs to पढ़ो back, num should be 2 */
	अगर (bytes > 0)
		num = 2;
	ret = adap->algo->master_xfer(adap, msg, num);
	स_नकल(dest, msgbuf1, bytes);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_device(काष्ठा i2c_client *i2c, पूर्णांक reg,
			पूर्णांक bytes, व्योम *src)
अणु
	अचिन्हित अक्षर buf[2];
	काष्ठा i2c_adapter *adap = i2c->adapter;
	काष्ठा i2c_msg msg;
	पूर्णांक ret;

	buf[0] = (अचिन्हित अक्षर)reg;
	स_नकल(&buf[1], src, bytes);
	msg.addr = i2c->addr;
	msg.flags = 0;
	msg.len = bytes + 1;
	msg.buf = buf;

	ret = adap->algo->master_xfer(adap, &msg, 1);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

पूर्णांक pm860x_page_reg_ग_लिखो(काष्ठा i2c_client *i2c, पूर्णांक reg,
			  अचिन्हित अक्षर data)
अणु
	अचिन्हित अक्षर zero;
	पूर्णांक ret;

	i2c_lock_bus(i2c->adapter, I2C_LOCK_SEGMENT);
	पढ़ो_device(i2c, 0xFA, 0, &zero);
	पढ़ो_device(i2c, 0xFB, 0, &zero);
	पढ़ो_device(i2c, 0xFF, 0, &zero);
	ret = ग_लिखो_device(i2c, reg, 1, &data);
	पढ़ो_device(i2c, 0xFE, 0, &zero);
	पढ़ो_device(i2c, 0xFC, 0, &zero);
	i2c_unlock_bus(i2c->adapter, I2C_LOCK_SEGMENT);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm860x_page_reg_ग_लिखो);

पूर्णांक pm860x_page_bulk_पढ़ो(काष्ठा i2c_client *i2c, पूर्णांक reg,
			  पूर्णांक count, अचिन्हित अक्षर *buf)
अणु
	अचिन्हित अक्षर zero = 0;
	पूर्णांक ret;

	i2c_lock_bus(i2c->adapter, I2C_LOCK_SEGMENT);
	पढ़ो_device(i2c, 0xfa, 0, &zero);
	पढ़ो_device(i2c, 0xfb, 0, &zero);
	पढ़ो_device(i2c, 0xff, 0, &zero);
	ret = पढ़ो_device(i2c, reg, count, buf);
	पढ़ो_device(i2c, 0xFE, 0, &zero);
	पढ़ो_device(i2c, 0xFC, 0, &zero);
	i2c_unlock_bus(i2c->adapter, I2C_LOCK_SEGMENT);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pm860x_page_bulk_पढ़ो);
