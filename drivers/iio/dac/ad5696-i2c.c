<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD5338R, AD5671R, AD5673R, AD5675R, AD5677R, AD5691R, AD5692R, AD5693,
 * AD5693R, AD5694, AD5694R, AD5695R, AD5696, AD5696R
 * Digital to analog converters driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश "ad5686.h"

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>

अटल पूर्णांक ad5686_i2c_पढ़ो(काष्ठा ad5686_state *st, u8 addr)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = i2c->addr,
			.flags = i2c->flags,
			.len = 3,
			.buf = &st->data[0].d8[1],
		पूर्ण,
		अणु
			.addr = i2c->addr,
			.flags = i2c->flags | I2C_M_RD,
			.len = 2,
			.buf = (अक्षर *)&st->data[0].d16,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	st->data[0].d32 = cpu_to_be32(AD5686_CMD(AD5686_CMD_NOOP) |
				      AD5686_ADDR(addr) |
				      0x00);

	ret = i2c_transfer(i2c->adapter, msg, 2);
	अगर (ret < 0)
		वापस ret;

	वापस be16_to_cpu(st->data[0].d16);
पूर्ण

अटल पूर्णांक ad5686_i2c_ग_लिखो(काष्ठा ad5686_state *st,
			    u8 cmd, u8 addr, u16 val)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);
	पूर्णांक ret;

	st->data[0].d32 = cpu_to_be32(AD5686_CMD(cmd) | AD5686_ADDR(addr)
				      | val);

	ret = i2c_master_send(i2c, &st->data[0].d8[1], 3);
	अगर (ret < 0)
		वापस ret;

	वापस (ret != 3) ? -EIO : 0;
पूर्ण

अटल पूर्णांक ad5686_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस ad5686_probe(&i2c->dev, id->driver_data, id->name,
			    ad5686_i2c_ग_लिखो, ad5686_i2c_पढ़ो);
पूर्ण

अटल पूर्णांक ad5686_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस ad5686_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad5686_i2c_id[] = अणु
	अणु"ad5311r", ID_AD5311Rपूर्ण,
	अणु"ad5338r", ID_AD5338Rपूर्ण,
	अणु"ad5671r", ID_AD5671Rपूर्ण,
	अणु"ad5673r", ID_AD5673Rपूर्ण,
	अणु"ad5675r", ID_AD5675Rपूर्ण,
	अणु"ad5677r", ID_AD5677Rपूर्ण,
	अणु"ad5691r", ID_AD5691Rपूर्ण,
	अणु"ad5692r", ID_AD5692Rपूर्ण,
	अणु"ad5693", ID_AD5693पूर्ण,
	अणु"ad5693r", ID_AD5693Rपूर्ण,
	अणु"ad5694", ID_AD5694पूर्ण,
	अणु"ad5694r", ID_AD5694Rपूर्ण,
	अणु"ad5695r", ID_AD5695Rपूर्ण,
	अणु"ad5696", ID_AD5696पूर्ण,
	अणु"ad5696r", ID_AD5696Rपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5686_i2c_id);

अटल स्थिर काष्ठा of_device_id ad5686_of_match[] = अणु
	अणु .compatible = "adi,ad5311r" पूर्ण,
	अणु .compatible = "adi,ad5338r" पूर्ण,
	अणु .compatible = "adi,ad5671r" पूर्ण,
	अणु .compatible = "adi,ad5675r" पूर्ण,
	अणु .compatible = "adi,ad5691r" पूर्ण,
	अणु .compatible = "adi,ad5692r" पूर्ण,
	अणु .compatible = "adi,ad5693" पूर्ण,
	अणु .compatible = "adi,ad5693r" पूर्ण,
	अणु .compatible = "adi,ad5694" पूर्ण,
	अणु .compatible = "adi,ad5694r" पूर्ण,
	अणु .compatible = "adi,ad5695r" पूर्ण,
	अणु .compatible = "adi,ad5696" पूर्ण,
	अणु .compatible = "adi,ad5696r" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5686_of_match);

अटल काष्ठा i2c_driver ad5686_i2c_driver = अणु
	.driver = अणु
		.name = "ad5696",
		.of_match_table = ad5686_of_match,
	पूर्ण,
	.probe = ad5686_i2c_probe,
	.हटाओ = ad5686_i2c_हटाओ,
	.id_table = ad5686_i2c_id,
पूर्ण;

module_i2c_driver(ad5686_i2c_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5686 and similar multi-channel DACs");
MODULE_LICENSE("GPL v2");
