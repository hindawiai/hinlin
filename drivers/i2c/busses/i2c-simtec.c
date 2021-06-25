<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2005 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Simtec Generic I2C Controller
*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

काष्ठा simtec_i2c_data अणु
	काष्ठा resource		*ioarea;
	व्योम __iomem		*reg;
	काष्ठा i2c_adapter	 adap;
	काष्ठा i2c_algo_bit_data bit;
पूर्ण;

#घोषणा CMD_SET_SDA	(1<<2)
#घोषणा CMD_SET_SCL	(1<<3)

#घोषणा STATE_SDA	(1<<0)
#घोषणा STATE_SCL	(1<<1)

/* i2c bit-bus functions */

अटल व्योम simtec_i2c_setsda(व्योम *pw, पूर्णांक state)
अणु
	काष्ठा simtec_i2c_data *pd = pw;
	ग_लिखोb(CMD_SET_SDA | (state ? STATE_SDA : 0), pd->reg);
पूर्ण

अटल व्योम simtec_i2c_setscl(व्योम *pw, पूर्णांक state)
अणु
	काष्ठा simtec_i2c_data *pd = pw;
	ग_लिखोb(CMD_SET_SCL | (state ? STATE_SCL : 0), pd->reg);
पूर्ण

अटल पूर्णांक simtec_i2c_माला_लोda(व्योम *pw)
अणु
	काष्ठा simtec_i2c_data *pd = pw;
	वापस पढ़ोb(pd->reg) & STATE_SDA ? 1 : 0;
पूर्ण

अटल पूर्णांक simtec_i2c_माला_लोcl(व्योम *pw)
अणु
	काष्ठा simtec_i2c_data *pd = pw;
	वापस पढ़ोb(pd->reg) & STATE_SCL ? 1 : 0;
पूर्ण

/* device registration */

अटल पूर्णांक simtec_i2c_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा simtec_i2c_data *pd;
	काष्ठा resource *res;
	पूर्णांक size;
	पूर्णांक ret;

	pd = kzalloc(माप(काष्ठा simtec_i2c_data), GFP_KERNEL);
	अगर (pd == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(dev, pd);

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(&dev->dev, "cannot find IO resource\n");
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	size = resource_size(res);

	pd->ioarea = request_mem_region(res->start, size, dev->name);
	अगर (pd->ioarea == शून्य) अणु
		dev_err(&dev->dev, "cannot request IO\n");
		ret = -ENXIO;
		जाओ err;
	पूर्ण

	pd->reg = ioremap(res->start, size);
	अगर (pd->reg == शून्य) अणु
		dev_err(&dev->dev, "cannot map IO\n");
		ret = -ENXIO;
		जाओ err_res;
	पूर्ण

	/* setup the निजी data */

	pd->adap.owner = THIS_MODULE;
	pd->adap.algo_data = &pd->bit;
	pd->adap.dev.parent = &dev->dev;

	strlcpy(pd->adap.name, "Simtec I2C", माप(pd->adap.name));

	pd->bit.data = pd;
	pd->bit.setsda = simtec_i2c_setsda;
	pd->bit.setscl = simtec_i2c_setscl;
	pd->bit.माला_लोda = simtec_i2c_माला_लोda;
	pd->bit.माला_लोcl = simtec_i2c_माला_लोcl;
	pd->bit.समयout = HZ;
	pd->bit.udelay = 20;

	ret = i2c_bit_add_bus(&pd->adap);
	अगर (ret)
		जाओ err_all;

	वापस 0;

 err_all:
	iounmap(pd->reg);

 err_res:
	release_mem_region(pd->ioarea->start, size);

 err:
	kमुक्त(pd);
	वापस ret;
पूर्ण

अटल पूर्णांक simtec_i2c_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा simtec_i2c_data *pd = platक्रमm_get_drvdata(dev);

	i2c_del_adapter(&pd->adap);

	iounmap(pd->reg);
	release_mem_region(pd->ioarea->start, resource_size(pd->ioarea));
	kमुक्त(pd);

	वापस 0;
पूर्ण

/* device driver */

अटल काष्ठा platक्रमm_driver simtec_i2c_driver = अणु
	.driver		= अणु
		.name		= "simtec-i2c",
	पूर्ण,
	.probe		= simtec_i2c_probe,
	.हटाओ		= simtec_i2c_हटाओ,
पूर्ण;

module_platक्रमm_driver(simtec_i2c_driver);

MODULE_DESCRIPTION("Simtec Generic I2C Bus driver");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:simtec-i2c");
