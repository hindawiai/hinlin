<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rl6347a.c - RL6347A class device shared support
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 *
 * Author: Oder Chiou <oder_chiou@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

#समावेश "rl6347a.h"

पूर्णांक rl6347a_hw_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा rl6347a_priv *rl6347a = i2c_get_clientdata(client);
	u8 data[4];
	पूर्णांक ret, i;

	/* handle index रेजिस्टरs */
	अगर (reg <= 0xff) अणु
		rl6347a_hw_ग_लिखो(client, RL6347A_COEF_INDEX, reg);
		क्रम (i = 0; i < rl6347a->index_cache_size; i++) अणु
			अगर (reg == rl6347a->index_cache[i].reg) अणु
				rl6347a->index_cache[i].def = value;
				अवरोध;
			पूर्ण

		पूर्ण
		reg = RL6347A_PROC_COEF;
	पूर्ण

	data[0] = (reg >> 24) & 0xff;
	data[1] = (reg >> 16) & 0xff;
	/*
	 * 4 bit VID: reg should be 0
	 * 12 bit VID: value should be 0
	 * So we use an OR चालक to handle it rather than use अगर condition.
	 */
	data[2] = ((reg >> 8) & 0xff) | ((value >> 8) & 0xff);
	data[3] = value & 0xff;

	ret = i2c_master_send(client, data, 4);

	अगर (ret == 4)
		वापस 0;
	अन्यथा
		dev_err(&client->dev, "I2C error %d\n", ret);
	अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(rl6347a_hw_ग_लिखो);

पूर्णांक rl6347a_hw_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा i2c_msg xfer[2];
	पूर्णांक ret;
	__be32 be_reg, buf = 0x0;
	अचिन्हित पूर्णांक index, vid;

	/* handle index रेजिस्टरs */
	अगर (reg <= 0xff) अणु
		rl6347a_hw_ग_लिखो(client, RL6347A_COEF_INDEX, reg);
		reg = RL6347A_PROC_COEF;
	पूर्ण

	reg = reg | 0x80000;
	vid = (reg >> 8) & 0xfff;

	अगर (AC_VERB_GET_AMP_GAIN_MUTE == (vid & 0xf00)) अणु
		index = (reg >> 8) & 0xf;
		reg = (reg & ~0xf0f) | index;
	पूर्ण
	be_reg = cpu_to_be32(reg);

	/* Write रेजिस्टर */
	xfer[0].addr = client->addr;
	xfer[0].flags = 0;
	xfer[0].len = 4;
	xfer[0].buf = (u8 *)&be_reg;

	/* Read data */
	xfer[1].addr = client->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = 4;
	xfer[1].buf = (u8 *)&buf;

	ret = i2c_transfer(client->adapter, xfer, 2);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != 2)
		वापस -EIO;

	*value = be32_to_cpu(buf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rl6347a_hw_पढ़ो);

MODULE_DESCRIPTION("RL6347A class device shared support");
MODULE_AUTHOR("Oder Chiou <oder_chiou@realtek.com>");
MODULE_LICENSE("GPL v2");
