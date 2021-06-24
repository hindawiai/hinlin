<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  i2c-versatile.c
 *
 *  Copyright (C) 2006 ARM Ltd.
 *  written by Russell King, Deep Blue Solutions Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#घोषणा I2C_CONTROL	0x00
#घोषणा I2C_CONTROLS	0x00
#घोषणा I2C_CONTROLC	0x04
#घोषणा SCL		(1 << 0)
#घोषणा SDA		(1 << 1)

काष्ठा i2c_versatile अणु
	काष्ठा i2c_adapter	 adap;
	काष्ठा i2c_algo_bit_data algo;
	व्योम __iomem		 *base;
पूर्ण;

अटल व्योम i2c_versatile_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा i2c_versatile *i2c = data;

	ग_लिखोl(SDA, i2c->base + (state ? I2C_CONTROLS : I2C_CONTROLC));
पूर्ण

अटल व्योम i2c_versatile_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा i2c_versatile *i2c = data;

	ग_लिखोl(SCL, i2c->base + (state ? I2C_CONTROLS : I2C_CONTROLC));
पूर्ण

अटल पूर्णांक i2c_versatile_माला_लोda(व्योम *data)
अणु
	काष्ठा i2c_versatile *i2c = data;
	वापस !!(पढ़ोl(i2c->base + I2C_CONTROL) & SDA);
पूर्ण

अटल पूर्णांक i2c_versatile_माला_लोcl(व्योम *data)
अणु
	काष्ठा i2c_versatile *i2c = data;
	वापस !!(पढ़ोl(i2c->base + I2C_CONTROL) & SCL);
पूर्ण

अटल स्थिर काष्ठा i2c_algo_bit_data i2c_versatile_algo = अणु
	.setsda	= i2c_versatile_setsda,
	.setscl = i2c_versatile_setscl,
	.माला_लोda	= i2c_versatile_माला_लोda,
	.माला_लोcl = i2c_versatile_माला_लोcl,
	.udelay	= 30,
	.समयout = HZ,
पूर्ण;

अटल पूर्णांक i2c_versatile_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा i2c_versatile *i2c;
	काष्ठा resource *r;
	पूर्णांक ret;

	i2c = devm_kzalloc(&dev->dev, माप(काष्ठा i2c_versatile), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	i2c->base = devm_ioremap_resource(&dev->dev, r);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	ग_लिखोl(SCL | SDA, i2c->base + I2C_CONTROLS);

	i2c->adap.owner = THIS_MODULE;
	strlcpy(i2c->adap.name, "Versatile I2C adapter", माप(i2c->adap.name));
	i2c->adap.algo_data = &i2c->algo;
	i2c->adap.dev.parent = &dev->dev;
	i2c->adap.dev.of_node = dev->dev.of_node;
	i2c->algo = i2c_versatile_algo;
	i2c->algo.data = i2c;

	i2c->adap.nr = dev->id;
	ret = i2c_bit_add_numbered_bus(&i2c->adap);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(dev, i2c);

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_versatile_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा i2c_versatile *i2c = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&i2c->adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_versatile_match[] = अणु
	अणु .compatible = "arm,versatile-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_versatile_match);

अटल काष्ठा platक्रमm_driver i2c_versatile_driver = अणु
	.probe		= i2c_versatile_probe,
	.हटाओ		= i2c_versatile_हटाओ,
	.driver		= अणु
		.name	= "versatile-i2c",
		.of_match_table = i2c_versatile_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init i2c_versatile_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&i2c_versatile_driver);
पूर्ण

अटल व्योम __निकास i2c_versatile_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&i2c_versatile_driver);
पूर्ण

subsys_initcall(i2c_versatile_init);
module_निकास(i2c_versatile_निकास);

MODULE_DESCRIPTION("ARM Versatile I2C bus driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:versatile-i2c");
