<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BQ27xxx battery monitor I2C driver
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/घातer/bq27xxx_battery.h>

अटल DEFINE_IDR(battery_id);
अटल DEFINE_MUTEX(battery_mutex);

अटल irqवापस_t bq27xxx_battery_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bq27xxx_device_info *di = data;

	bq27xxx_battery_update(di);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bq27xxx_battery_i2c_पढ़ो(काष्ठा bq27xxx_device_info *di, u8 reg,
				    bool single)
अणु
	काष्ठा i2c_client *client = to_i2c_client(di->dev);
	काष्ठा i2c_msg msg[2];
	u8 data[2];
	पूर्णांक ret;

	अगर (!client->adapter)
		वापस -ENODEV;

	msg[0].addr = client->addr;
	msg[0].flags = 0;
	msg[0].buf = &reg;
	msg[0].len = माप(reg);
	msg[1].addr = client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = data;
	अगर (single)
		msg[1].len = 1;
	अन्यथा
		msg[1].len = 2;

	ret = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret < 0)
		वापस ret;

	अगर (!single)
		ret = get_unaligned_le16(data);
	अन्यथा
		ret = data[0];

	वापस ret;
पूर्ण

अटल पूर्णांक bq27xxx_battery_i2c_ग_लिखो(काष्ठा bq27xxx_device_info *di, u8 reg,
				     पूर्णांक value, bool single)
अणु
	काष्ठा i2c_client *client = to_i2c_client(di->dev);
	काष्ठा i2c_msg msg;
	u8 data[4];
	पूर्णांक ret;

	अगर (!client->adapter)
		वापस -ENODEV;

	data[0] = reg;
	अगर (single) अणु
		data[1] = (u8) value;
		msg.len = 2;
	पूर्ण अन्यथा अणु
		put_unaligned_le16(value, &data[1]);
		msg.len = 3;
	पूर्ण

	msg.buf = data;
	msg.addr = client->addr;
	msg.flags = 0;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक bq27xxx_battery_i2c_bulk_पढ़ो(काष्ठा bq27xxx_device_info *di, u8 reg,
					 u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = to_i2c_client(di->dev);
	पूर्णांक ret;

	अगर (!client->adapter)
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg, len, data);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != len)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक bq27xxx_battery_i2c_bulk_ग_लिखो(काष्ठा bq27xxx_device_info *di,
					  u8 reg, u8 *data, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = to_i2c_client(di->dev);
	काष्ठा i2c_msg msg;
	u8 buf[33];
	पूर्णांक ret;

	अगर (!client->adapter)
		वापस -ENODEV;

	buf[0] = reg;
	स_नकल(&buf[1], data, len);

	msg.buf = buf;
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = len + 1;

	ret = i2c_transfer(client->adapter, &msg, 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक bq27xxx_battery_i2c_probe(काष्ठा i2c_client *client,
				     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bq27xxx_device_info *di;
	पूर्णांक ret;
	अक्षर *name;
	पूर्णांक num;

	/* Get new ID क्रम the new battery device */
	mutex_lock(&battery_mutex);
	num = idr_alloc(&battery_id, client, 0, 0, GFP_KERNEL);
	mutex_unlock(&battery_mutex);
	अगर (num < 0)
		वापस num;

	name = devm_kaप्र_लिखो(&client->dev, GFP_KERNEL, "%s-%d", id->name, num);
	अगर (!name)
		जाओ err_mem;

	di = devm_kzalloc(&client->dev, माप(*di), GFP_KERNEL);
	अगर (!di)
		जाओ err_mem;

	di->id = num;
	di->dev = &client->dev;
	di->chip = id->driver_data;
	di->name = name;

	di->bus.पढ़ो = bq27xxx_battery_i2c_पढ़ो;
	di->bus.ग_लिखो = bq27xxx_battery_i2c_ग_लिखो;
	di->bus.पढ़ो_bulk = bq27xxx_battery_i2c_bulk_पढ़ो;
	di->bus.ग_लिखो_bulk = bq27xxx_battery_i2c_bulk_ग_लिखो;

	ret = bq27xxx_battery_setup(di);
	अगर (ret)
		जाओ err_failed;

	/* Schedule a polling after about 1 min */
	schedule_delayed_work(&di->work, 60 * HZ);

	i2c_set_clientdata(client, di);

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				शून्य, bq27xxx_battery_irq_handler_thपढ़ो,
				IRQF_ONESHOT,
				di->name, di);
		अगर (ret) अणु
			dev_err(&client->dev,
				"Unable to register IRQ %d error %d\n",
				client->irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;

err_mem:
	ret = -ENOMEM;

err_failed:
	mutex_lock(&battery_mutex);
	idr_हटाओ(&battery_id, num);
	mutex_unlock(&battery_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक bq27xxx_battery_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bq27xxx_device_info *di = i2c_get_clientdata(client);

	bq27xxx_battery_tearकरोwn(di);

	mutex_lock(&battery_mutex);
	idr_हटाओ(&battery_id, di->id);
	mutex_unlock(&battery_mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bq27xxx_i2c_id_table[] = अणु
	अणु "bq27200", BQ27000 पूर्ण,
	अणु "bq27210", BQ27010 पूर्ण,
	अणु "bq27500", BQ2750X पूर्ण,
	अणु "bq27510", BQ2751X पूर्ण,
	अणु "bq27520", BQ2752X पूर्ण,
	अणु "bq27500-1", BQ27500 पूर्ण,
	अणु "bq27510g1", BQ27510G1 पूर्ण,
	अणु "bq27510g2", BQ27510G2 पूर्ण,
	अणु "bq27510g3", BQ27510G3 पूर्ण,
	अणु "bq27520g1", BQ27520G1 पूर्ण,
	अणु "bq27520g2", BQ27520G2 पूर्ण,
	अणु "bq27520g3", BQ27520G3 पूर्ण,
	अणु "bq27520g4", BQ27520G4 पूर्ण,
	अणु "bq27521", BQ27521 पूर्ण,
	अणु "bq27530", BQ27530 पूर्ण,
	अणु "bq27531", BQ27531 पूर्ण,
	अणु "bq27541", BQ27541 पूर्ण,
	अणु "bq27542", BQ27542 पूर्ण,
	अणु "bq27546", BQ27546 पूर्ण,
	अणु "bq27742", BQ27742 पूर्ण,
	अणु "bq27545", BQ27545 पूर्ण,
	अणु "bq27411", BQ27411 पूर्ण,
	अणु "bq27421", BQ27421 पूर्ण,
	अणु "bq27425", BQ27425 पूर्ण,
	अणु "bq27426", BQ27426 पूर्ण,
	अणु "bq27441", BQ27441 पूर्ण,
	अणु "bq27621", BQ27621 पूर्ण,
	अणु "bq27z561", BQ27Z561 पूर्ण,
	अणु "bq28z610", BQ28Z610 पूर्ण,
	अणु "bq34z100", BQ34Z100 पूर्ण,
	अणु "bq78z100", BQ78Z100 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq27xxx_i2c_id_table);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id bq27xxx_battery_i2c_of_match_table[] = अणु
	अणु .compatible = "ti,bq27200" पूर्ण,
	अणु .compatible = "ti,bq27210" पूर्ण,
	अणु .compatible = "ti,bq27500" पूर्ण,
	अणु .compatible = "ti,bq27510" पूर्ण,
	अणु .compatible = "ti,bq27520" पूर्ण,
	अणु .compatible = "ti,bq27500-1" पूर्ण,
	अणु .compatible = "ti,bq27510g1" पूर्ण,
	अणु .compatible = "ti,bq27510g2" पूर्ण,
	अणु .compatible = "ti,bq27510g3" पूर्ण,
	अणु .compatible = "ti,bq27520g1" पूर्ण,
	अणु .compatible = "ti,bq27520g2" पूर्ण,
	अणु .compatible = "ti,bq27520g3" पूर्ण,
	अणु .compatible = "ti,bq27520g4" पूर्ण,
	अणु .compatible = "ti,bq27521" पूर्ण,
	अणु .compatible = "ti,bq27530" पूर्ण,
	अणु .compatible = "ti,bq27531" पूर्ण,
	अणु .compatible = "ti,bq27541" पूर्ण,
	अणु .compatible = "ti,bq27542" पूर्ण,
	अणु .compatible = "ti,bq27546" पूर्ण,
	अणु .compatible = "ti,bq27742" पूर्ण,
	अणु .compatible = "ti,bq27545" पूर्ण,
	अणु .compatible = "ti,bq27411" पूर्ण,
	अणु .compatible = "ti,bq27421" पूर्ण,
	अणु .compatible = "ti,bq27425" पूर्ण,
	अणु .compatible = "ti,bq27426" पूर्ण,
	अणु .compatible = "ti,bq27441" पूर्ण,
	अणु .compatible = "ti,bq27621" पूर्ण,
	अणु .compatible = "ti,bq27z561" पूर्ण,
	अणु .compatible = "ti,bq28z610" पूर्ण,
	अणु .compatible = "ti,bq34z100" पूर्ण,
	अणु .compatible = "ti,bq78z100" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq27xxx_battery_i2c_of_match_table);
#पूर्ण_अगर

अटल काष्ठा i2c_driver bq27xxx_battery_i2c_driver = अणु
	.driver = अणु
		.name = "bq27xxx-battery",
		.of_match_table = of_match_ptr(bq27xxx_battery_i2c_of_match_table),
	पूर्ण,
	.probe = bq27xxx_battery_i2c_probe,
	.हटाओ = bq27xxx_battery_i2c_हटाओ,
	.id_table = bq27xxx_i2c_id_table,
पूर्ण;
module_i2c_driver(bq27xxx_battery_i2c_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("BQ27xxx battery monitor i2c driver");
MODULE_LICENSE("GPL");
