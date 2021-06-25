<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश "saa7164.h"

अटल पूर्णांक i2c_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा saa7164_i2c *bus = i2c_adap->algo_data;
	काष्ठा saa7164_dev *dev = bus->dev;
	पूर्णांक i, retval = 0;

	dprपूर्णांकk(DBGLVL_I2C, "%s(num = %d)\n", __func__, num);

	क्रम (i = 0 ; i < num; i++) अणु
		dprपूर्णांकk(DBGLVL_I2C, "%s(num = %d) addr = 0x%02x  len = 0x%x\n",
			__func__, num, msgs[i].addr, msgs[i].len);
		अगर (msgs[i].flags & I2C_M_RD) अणु
			retval = saa7164_api_i2c_पढ़ो(bus,
				msgs[i].addr,
				0 /* reglen */,
				शून्य /* reg */, msgs[i].len, msgs[i].buf);
		पूर्ण अन्यथा अगर (i + 1 < num && (msgs[i + 1].flags & I2C_M_RD) &&
			   msgs[i].addr == msgs[i + 1].addr) अणु
			/* ग_लिखो then पढ़ो from same address */

			retval = saa7164_api_i2c_पढ़ो(bus, msgs[i].addr,
				msgs[i].len, msgs[i].buf,
				msgs[i+1].len, msgs[i+1].buf
				);

			i++;

			अगर (retval < 0)
				जाओ err;
		पूर्ण अन्यथा अणु
			/* ग_लिखो */
			retval = saa7164_api_i2c_ग_लिखो(bus, msgs[i].addr,
				msgs[i].len, msgs[i].buf);
		पूर्ण
		अगर (retval < 0)
			जाओ err;
	पूर्ण
	वापस num;

err:
	वापस retval;
पूर्ण

अटल u32 saa7164_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm saa7164_i2c_algo_ढाँचा = अणु
	.master_xfer	= i2c_xfer,
	.functionality	= saa7164_functionality,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_adapter saa7164_i2c_adap_ढाँचा = अणु
	.name              = "saa7164",
	.owner             = THIS_MODULE,
	.algo              = &saa7164_i2c_algo_ढाँचा,
पूर्ण;

अटल स्थिर काष्ठा i2c_client saa7164_i2c_client_ढाँचा = अणु
	.name	= "saa7164 internal",
पूर्ण;

पूर्णांक saa7164_i2c_रेजिस्टर(काष्ठा saa7164_i2c *bus)
अणु
	काष्ठा saa7164_dev *dev = bus->dev;

	dprपूर्णांकk(DBGLVL_I2C, "%s(bus = %d)\n", __func__, bus->nr);

	bus->i2c_adap = saa7164_i2c_adap_ढाँचा;
	bus->i2c_client = saa7164_i2c_client_ढाँचा;

	bus->i2c_adap.dev.parent = &dev->pci->dev;

	strscpy(bus->i2c_adap.name, bus->dev->name,
		माप(bus->i2c_adap.name));

	bus->i2c_adap.algo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, bus);
	i2c_add_adapter(&bus->i2c_adap);

	bus->i2c_client.adapter = &bus->i2c_adap;

	अगर (0 != bus->i2c_rc)
		prपूर्णांकk(KERN_ERR "%s: i2c bus %d register FAILED\n",
			dev->name, bus->nr);

	वापस bus->i2c_rc;
पूर्ण

पूर्णांक saa7164_i2c_unरेजिस्टर(काष्ठा saa7164_i2c *bus)
अणु
	i2c_del_adapter(&bus->i2c_adap);
	वापस 0;
पूर्ण
