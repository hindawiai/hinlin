<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Load Analog Devices SigmaStudio firmware files
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "sigmadsp.h"

अटल पूर्णांक sigmadsp_ग_लिखो_i2c(व्योम *control_data,
	अचिन्हित पूर्णांक addr, स्थिर uपूर्णांक8_t data[], माप_प्रकार len)
अणु
	uपूर्णांक8_t *buf;
	पूर्णांक ret;

	buf = kzalloc(2 + len, GFP_KERNEL | GFP_DMA);
	अगर (!buf)
		वापस -ENOMEM;

	put_unaligned_be16(addr, buf);
	स_नकल(buf + 2, data, len);

	ret = i2c_master_send(control_data, buf, len + 2);

	kमुक्त(buf);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक sigmadsp_पढ़ो_i2c(व्योम *control_data,
	अचिन्हित पूर्णांक addr, uपूर्णांक8_t data[], माप_प्रकार len)
अणु
	काष्ठा i2c_client *client = control_data;
	काष्ठा i2c_msg msgs[2];
	uपूर्णांक8_t buf[2];
	पूर्णांक ret;

	put_unaligned_be16(addr, buf);

	msgs[0].addr = client->addr;
	msgs[0].len = माप(buf);
	msgs[0].buf = buf;
	msgs[0].flags = 0;

	msgs[1].addr = client->addr;
	msgs[1].len = len;
	msgs[1].buf = data;
	msgs[1].flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != ARRAY_SIZE(msgs))
		वापस -EIO;
	वापस 0;
पूर्ण

/**
 * devm_sigmadsp_init_i2c() - Initialize SigmaDSP instance
 * @client: The parent I2C device
 * @ops: The sigmadsp_ops to use क्रम this instance
 * @firmware_name: Name of the firmware file to load
 *
 * Allocates a SigmaDSP instance and loads the specअगरied firmware file.
 *
 * Returns a poपूर्णांकer to a काष्ठा sigmadsp on success, or a PTR_ERR() on error.
 */
काष्ठा sigmadsp *devm_sigmadsp_init_i2c(काष्ठा i2c_client *client,
	स्थिर काष्ठा sigmadsp_ops *ops,	स्थिर अक्षर *firmware_name)
अणु
	काष्ठा sigmadsp *sigmadsp;

	sigmadsp = devm_sigmadsp_init(&client->dev, ops, firmware_name);
	अगर (IS_ERR(sigmadsp))
		वापस sigmadsp;

	sigmadsp->control_data = client;
	sigmadsp->ग_लिखो = sigmadsp_ग_लिखो_i2c;
	sigmadsp->पढ़ो = sigmadsp_पढ़ो_i2c;

	वापस sigmadsp;
पूर्ण
EXPORT_SYMBOL_GPL(devm_sigmadsp_init_i2c);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("SigmaDSP I2C firmware loader");
MODULE_LICENSE("GPL");
