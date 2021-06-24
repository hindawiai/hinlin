<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * STK1160 driver
 *
 * Copyright (C) 2012 Ezequiel Garcia
 * <elezegarcia--a.t--gmail.com>
 *
 * Based on Easycap driver by R.M. Thomas
 *	Copyright (C) 2010 R.M. Thomas
 *	<rmthomas--a.t--sciolus.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>

#समावेश "stk1160.h"
#समावेश "stk1160-reg.h"

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "enable debug messages [i2c]");

#घोषणा dprपूर्णांकk_i2c(fmt, args...)				\
करो अणु								\
	अगर (i2c_debug)						\
		prपूर्णांकk(KERN_DEBUG fmt, ##args);			\
पूर्ण जबतक (0)

अटल पूर्णांक stk1160_i2c_busy_रुको(काष्ठा stk1160 *dev, u8 रुको_bit_mask)
अणु
	अचिन्हित दीर्घ end;
	u8 flag;

	/* Wait until पढ़ो/ग_लिखो finish bit is set */
	end = jअगरfies + msecs_to_jअगरfies(STK1160_I2C_TIMEOUT);
	जबतक (समय_is_after_jअगरfies(end)) अणु

		stk1160_पढ़ो_reg(dev, STK1160_SICTL+1, &flag);
		/* पढ़ो/ग_लिखो करोne? */
		अगर (flag & रुको_bit_mask)
			जाओ करोne;

		usleep_range(10 * USEC_PER_MSEC, 20 * USEC_PER_MSEC);
	पूर्ण

	वापस -ETIMEDOUT;

करोne:
	वापस 0;
पूर्ण

अटल पूर्णांक stk1160_i2c_ग_लिखो_reg(काष्ठा stk1160 *dev, u8 addr,
		u8 reg, u8 value)
अणु
	पूर्णांक rc;

	/* Set serial device address */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SICTL_SDA, addr);
	अगर (rc < 0)
		वापस rc;

	/* Set i2c device रेजिस्टर sub-address */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SBUSW_WA, reg);
	अगर (rc < 0)
		वापस rc;

	/* Set i2c device रेजिस्टर value */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SBUSW_WD, value);
	अगर (rc < 0)
		वापस rc;

	/* Start ग_लिखो now */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SICTL, 0x01);
	अगर (rc < 0)
		वापस rc;

	rc = stk1160_i2c_busy_रुको(dev, 0x04);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक stk1160_i2c_पढ़ो_reg(काष्ठा stk1160 *dev, u8 addr,
		u8 reg, u8 *value)
अणु
	पूर्णांक rc;

	/* Set serial device address */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SICTL_SDA, addr);
	अगर (rc < 0)
		वापस rc;

	/* Set i2c device रेजिस्टर sub-address */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SBUSR_RA, reg);
	अगर (rc < 0)
		वापस rc;

	/* Start पढ़ो now */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SICTL, 0x20);
	अगर (rc < 0)
		वापस rc;

	rc = stk1160_i2c_busy_रुको(dev, 0x01);
	अगर (rc < 0)
		वापस rc;

	rc = stk1160_पढ़ो_reg(dev, STK1160_SBUSR_RD, value);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

/*
 * stk1160_i2c_check_क्रम_device()
 * check अगर there is a i2c_device at the supplied address
 */
अटल पूर्णांक stk1160_i2c_check_क्रम_device(काष्ठा stk1160 *dev,
		अचिन्हित अक्षर addr)
अणु
	पूर्णांक rc;

	/* Set serial device address */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SICTL_SDA, addr);
	अगर (rc < 0)
		वापस rc;

	/* Set device sub-address, we'll chip version reg */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SBUSR_RA, 0x00);
	अगर (rc < 0)
		वापस rc;

	/* Start पढ़ो now */
	rc = stk1160_ग_लिखो_reg(dev, STK1160_SICTL, 0x20);
	अगर (rc < 0)
		वापस rc;

	rc = stk1160_i2c_busy_रुको(dev, 0x01);
	अगर (rc < 0)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/*
 * stk1160_i2c_xfer()
 * the मुख्य i2c transfer function
 */
अटल पूर्णांक stk1160_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			   काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा stk1160 *dev = i2c_adap->algo_data;
	पूर्णांक addr, rc, i;

	क्रम (i = 0; i < num; i++) अणु
		addr = msgs[i].addr << 1;
		dprपूर्णांकk_i2c("%s: addr=%x", __func__, addr);

		अगर (!msgs[i].len) अणु
			/* no len: check only क्रम device presence */
			rc = stk1160_i2c_check_क्रम_device(dev, addr);
			अगर (rc < 0) अणु
				dprपूर्णांकk_i2c(" no device\n");
				वापस rc;
			पूर्ण

		पूर्ण अन्यथा अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो request without preceding रेजिस्टर selection */
			dprपूर्णांकk_i2c(" subaddr not selected");
			rc = -EOPNOTSUPP;
			जाओ err;

		पूर्ण अन्यथा अगर (i + 1 < num && msgs[i].len <= 2 &&
			   (msgs[i + 1].flags & I2C_M_RD) &&
			   msgs[i].addr == msgs[i + 1].addr) अणु

			अगर (msgs[i].len != 1 || msgs[i + 1].len != 1) अणु
				dprपूर्णांकk_i2c(" len not supported");
				rc = -EOPNOTSUPP;
				जाओ err;
			पूर्ण

			dprपूर्णांकk_i2c(" subaddr=%x", msgs[i].buf[0]);

			rc = stk1160_i2c_पढ़ो_reg(dev, addr, msgs[i].buf[0],
				msgs[i + 1].buf);

			dprपूर्णांकk_i2c(" read=%x", *msgs[i + 1].buf);

			/* consumed two msgs, so we skip one of them */
			i++;

		पूर्ण अन्यथा अणु
			अगर (msgs[i].len != 2) अणु
				dprपूर्णांकk_i2c(" len not supported");
				rc = -EOPNOTSUPP;
				जाओ err;
			पूर्ण

			dprपूर्णांकk_i2c(" subaddr=%x write=%x",
				msgs[i].buf[0],  msgs[i].buf[1]);

			rc = stk1160_i2c_ग_लिखो_reg(dev, addr, msgs[i].buf[0],
				msgs[i].buf[1]);
		पूर्ण

		अगर (rc < 0)
			जाओ err;
		dprपूर्णांकk_i2c(" OK\n");
	पूर्ण

	वापस num;
err:
	dprपूर्णांकk_i2c(" ERROR: %d\n", rc);
	वापस num;
पूर्ण

/*
 * functionality(), what da heck is this?
 */
अटल u32 functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm algo = अणु
	.master_xfer   = stk1160_i2c_xfer,
	.functionality = functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter adap_ढाँचा = अणु
	.owner = THIS_MODULE,
	.name = "stk1160",
	.algo = &algo,
पूर्ण;

अटल स्थिर काष्ठा i2c_client client_ढाँचा = अणु
	.name = "stk1160 internal",
पूर्ण;

/*
 * stk1160_i2c_रेजिस्टर()
 * रेजिस्टर i2c bus
 */
पूर्णांक stk1160_i2c_रेजिस्टर(काष्ठा stk1160 *dev)
अणु
	पूर्णांक rc;

	dev->i2c_adap = adap_ढाँचा;
	dev->i2c_adap.dev.parent = dev->dev;
	strscpy(dev->i2c_adap.name, "stk1160", माप(dev->i2c_adap.name));
	dev->i2c_adap.algo_data = dev;

	i2c_set_adapdata(&dev->i2c_adap, &dev->v4l2_dev);

	rc = i2c_add_adapter(&dev->i2c_adap);
	अगर (rc < 0) अणु
		stk1160_err("cannot add i2c adapter (%d)\n", rc);
		वापस rc;
	पूर्ण

	dev->i2c_client = client_ढाँचा;
	dev->i2c_client.adapter = &dev->i2c_adap;

	/* Set i2c घड़ी भागider device address */
	stk1160_ग_लिखो_reg(dev, STK1160_SICTL_CD,  0x0f);

	/* ??? */
	stk1160_ग_लिखो_reg(dev, STK1160_ASIC + 3,  0x00);

	वापस 0;
पूर्ण

/*
 * stk1160_i2c_unरेजिस्टर()
 * unरेजिस्टर i2c_bus
 */
पूर्णांक stk1160_i2c_unरेजिस्टर(काष्ठा stk1160 *dev)
अणु
	i2c_del_adapter(&dev->i2c_adap);
	वापस 0;
पूर्ण
