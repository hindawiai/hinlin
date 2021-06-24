<शैली गुरु>
/*
 * tps6507x.c  --  TPS6507x chip family multi-function driver
 *
 *  Copyright (c) 2010 RidgeRun (todd.fischer@ridgerun.com)
 *
 * Author: Todd Fischer
 *         todd.fischer@ridgerun.com
 *
 * Credits:
 *
 *    Using code from wm831x-*.c, wm8400-core, Wolfson Microelectronics PLC.
 *
 * For licencing details see kernel-base/COPYING
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps6507x.h>

अटल स्थिर काष्ठा mfd_cell tps6507x_devs[] = अणु
	अणु
		.name = "tps6507x-pmic",
	पूर्ण,
	अणु
		.name = "tps6507x-ts",
	पूर्ण,
पूर्ण;


अटल पूर्णांक tps6507x_i2c_पढ़ो_device(काष्ठा tps6507x_dev *tps6507x, अक्षर reg,
				  पूर्णांक bytes, व्योम *dest)
अणु
	काष्ठा i2c_client *i2c = tps6507x->i2c_client;
	काष्ठा i2c_msg xfer[2];
	पूर्णांक ret;

	/* Write रेजिस्टर */
	xfer[0].addr = i2c->addr;
	xfer[0].flags = 0;
	xfer[0].len = 1;
	xfer[0].buf = &reg;

	/* Read data */
	xfer[1].addr = i2c->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = bytes;
	xfer[1].buf = dest;

	ret = i2c_transfer(i2c->adapter, xfer, 2);
	अगर (ret == 2)
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक tps6507x_i2c_ग_लिखो_device(काष्ठा tps6507x_dev *tps6507x, अक्षर reg,
				   पूर्णांक bytes, व्योम *src)
अणु
	काष्ठा i2c_client *i2c = tps6507x->i2c_client;
	/* we add 1 byte क्रम device रेजिस्टर */
	u8 msg[TPS6507X_MAX_REGISTER + 1];
	पूर्णांक ret;

	अगर (bytes > TPS6507X_MAX_REGISTER)
		वापस -EINVAL;

	msg[0] = reg;
	स_नकल(&msg[1], src, bytes);

	ret = i2c_master_send(i2c, msg, bytes + 1);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != bytes + 1)
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक tps6507x_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tps6507x_dev *tps6507x;

	tps6507x = devm_kzalloc(&i2c->dev, माप(काष्ठा tps6507x_dev),
				GFP_KERNEL);
	अगर (tps6507x == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, tps6507x);
	tps6507x->dev = &i2c->dev;
	tps6507x->i2c_client = i2c;
	tps6507x->पढ़ो_dev = tps6507x_i2c_पढ़ो_device;
	tps6507x->ग_लिखो_dev = tps6507x_i2c_ग_लिखो_device;

	वापस devm_mfd_add_devices(tps6507x->dev, -1, tps6507x_devs,
				    ARRAY_SIZE(tps6507x_devs), शून्य, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps6507x_i2c_id[] = अणु
	अणु "tps6507x", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tps6507x_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tps6507x_of_match[] = अणु
	अणु.compatible = "ti,tps6507x", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps6507x_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tps6507x_i2c_driver = अणु
	.driver = अणु
		   .name = "tps6507x",
		   .of_match_table = of_match_ptr(tps6507x_of_match),
	पूर्ण,
	.probe = tps6507x_i2c_probe,
	.id_table = tps6507x_i2c_id,
पूर्ण;

अटल पूर्णांक __init tps6507x_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&tps6507x_i2c_driver);
पूर्ण
/* init early so consumer devices can complete प्रणाली boot */
subsys_initcall(tps6507x_i2c_init);

अटल व्योम __निकास tps6507x_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&tps6507x_i2c_driver);
पूर्ण
module_निकास(tps6507x_i2c_निकास);

MODULE_DESCRIPTION("TPS6507x chip family multi-function driver");
MODULE_LICENSE("GPL");
