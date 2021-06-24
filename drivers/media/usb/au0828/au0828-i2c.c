<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Auvitek AU0828 USB bridge
 *
 *  Copyright (c) 2008 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "au0828.h"

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश "media/tuner.h"
#समावेश <media/v4l2-common.h>

अटल पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan, "scan i2c bus at insmod time");

#घोषणा I2C_WAIT_DELAY 25
#घोषणा I2C_WAIT_RETRY 1000

अटल अंतरभूत पूर्णांक i2c_slave_did_ग_लिखो_ack(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा au0828_dev *dev = i2c_adap->algo_data;
	वापस au0828_पढ़ो(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_NO_WRITE_ACK ? 0 : 1;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_slave_did_पढ़ो_ack(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा au0828_dev *dev = i2c_adap->algo_data;
	वापस au0828_पढ़ो(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_NO_READ_ACK ? 0 : 1;
पूर्ण

अटल पूर्णांक i2c_रुको_पढ़ो_ack(काष्ठा i2c_adapter *i2c_adap)
अणु
	पूर्णांक count;

	क्रम (count = 0; count < I2C_WAIT_RETRY; count++) अणु
		अगर (!i2c_slave_did_पढ़ो_ack(i2c_adap))
			अवरोध;
		udelay(I2C_WAIT_DELAY);
	पूर्ण

	अगर (I2C_WAIT_RETRY == count)
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_पढ़ो_busy(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा au0828_dev *dev = i2c_adap->algo_data;
	वापस au0828_पढ़ो(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_READ_DONE ? 0 : 1;
पूर्ण

अटल पूर्णांक i2c_रुको_पढ़ो_करोne(काष्ठा i2c_adapter *i2c_adap)
अणु
	पूर्णांक count;

	क्रम (count = 0; count < I2C_WAIT_RETRY; count++) अणु
		अगर (!i2c_is_पढ़ो_busy(i2c_adap))
			अवरोध;
		udelay(I2C_WAIT_DELAY);
	पूर्ण

	अगर (I2C_WAIT_RETRY == count)
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_ग_लिखो_करोne(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा au0828_dev *dev = i2c_adap->algo_data;
	वापस au0828_पढ़ो(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_WRITE_DONE ? 1 : 0;
पूर्ण

अटल पूर्णांक i2c_रुको_ग_लिखो_करोne(काष्ठा i2c_adapter *i2c_adap)
अणु
	पूर्णांक count;

	क्रम (count = 0; count < I2C_WAIT_RETRY; count++) अणु
		अगर (i2c_is_ग_लिखो_करोne(i2c_adap))
			अवरोध;
		udelay(I2C_WAIT_DELAY);
	पूर्ण

	अगर (I2C_WAIT_RETRY == count)
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_busy(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा au0828_dev *dev = i2c_adap->algo_data;
	वापस au0828_पढ़ो(dev, AU0828_I2C_STATUS_201) &
		AU0828_I2C_STATUS_BUSY ? 1 : 0;
पूर्ण

अटल पूर्णांक i2c_रुको_करोne(काष्ठा i2c_adapter *i2c_adap)
अणु
	पूर्णांक count;

	क्रम (count = 0; count < I2C_WAIT_RETRY; count++) अणु
		अगर (!i2c_is_busy(i2c_adap))
			अवरोध;
		udelay(I2C_WAIT_DELAY);
	पूर्ण

	अगर (I2C_WAIT_RETRY == count)
		वापस 0;

	वापस 1;
पूर्ण

/* FIXME: Implement join handling correctly */
अटल पूर्णांक i2c_sendbytes(काष्ठा i2c_adapter *i2c_adap,
	स्थिर काष्ठा i2c_msg *msg, पूर्णांक joined_rlen)
अणु
	पूर्णांक i, strobe = 0;
	काष्ठा au0828_dev *dev = i2c_adap->algo_data;
	u8 i2c_speed = dev->board.i2c_clk_भागider;

	dprपूर्णांकk(4, "%s()\n", __func__);

	au0828_ग_लिखो(dev, AU0828_I2C_MULTIBYTE_MODE_2FF, 0x01);

	अगर (((dev->board.tuner_type == TUNER_XC5000) ||
	     (dev->board.tuner_type == TUNER_XC5000C)) &&
	    (dev->board.tuner_addr == msg->addr)) अणु
		/*
		 * Due to I2C घड़ी stretch, we need to use a lower speed
		 * on xc5000 क्रम commands. However, firmware transfer can
		 * speed up to 400 KHz.
		 */
		अगर (msg->len == 64)
			i2c_speed = AU0828_I2C_CLK_250KHZ;
		अन्यथा
			i2c_speed = AU0828_I2C_CLK_20KHZ;
	पूर्ण
	/* Set the I2C घड़ी */
	au0828_ग_लिखो(dev, AU0828_I2C_CLK_DIVIDER_202, i2c_speed);

	/* Hardware needs 8 bit addresses */
	au0828_ग_लिखो(dev, AU0828_I2C_DEST_ADDR_203, msg->addr << 1);

	dprपूर्णांकk(4, "SEND: %02x\n", msg->addr);

	/* Deal with i2c_scan */
	अगर (msg->len == 0) अणु
		/* The analog tuner detection code makes use of the SMBUS_QUICK
		   message (which involves a zero length i2c ग_लिखो).  To aव्योम
		   checking the status रेजिस्टर when we didn't strobe out any
		   actual bytes to the bus, just करो a पढ़ो check.  This is
		   consistent with how I saw i2c device checking करोne in the
		   USB trace of the Winकरोws driver */
		au0828_ग_लिखो(dev, AU0828_I2C_TRIGGER_200,
			     AU0828_I2C_TRIGGER_READ);

		अगर (!i2c_रुको_करोne(i2c_adap))
			वापस -EIO;

		अगर (i2c_रुको_पढ़ो_ack(i2c_adap))
			वापस -EIO;

		वापस 0;
	पूर्ण

	क्रम (i = 0; i < msg->len;) अणु

		dprपूर्णांकk(4, " %02x\n", msg->buf[i]);

		au0828_ग_लिखो(dev, AU0828_I2C_WRITE_FIFO_205, msg->buf[i]);

		strobe++;
		i++;

		अगर ((strobe >= 4) || (i >= msg->len)) अणु

			/* Strobe the byte पूर्णांकo the bus */
			अगर (i < msg->len)
				au0828_ग_लिखो(dev, AU0828_I2C_TRIGGER_200,
					     AU0828_I2C_TRIGGER_WRITE |
					     AU0828_I2C_TRIGGER_HOLD);
			अन्यथा
				au0828_ग_लिखो(dev, AU0828_I2C_TRIGGER_200,
					     AU0828_I2C_TRIGGER_WRITE);

			/* Reset strobe trigger */
			strobe = 0;

			अगर (!i2c_रुको_ग_लिखो_करोne(i2c_adap))
				वापस -EIO;

		पूर्ण

	पूर्ण
	अगर (!i2c_रुको_करोne(i2c_adap))
		वापस -EIO;

	dprपूर्णांकk(4, "\n");

	वापस msg->len;
पूर्ण

/* FIXME: Implement join handling correctly */
अटल पूर्णांक i2c_पढ़ोbytes(काष्ठा i2c_adapter *i2c_adap,
	स्थिर काष्ठा i2c_msg *msg, पूर्णांक joined)
अणु
	काष्ठा au0828_dev *dev = i2c_adap->algo_data;
	u8 i2c_speed = dev->board.i2c_clk_भागider;
	पूर्णांक i;

	dprपूर्णांकk(4, "%s()\n", __func__);

	au0828_ग_लिखो(dev, AU0828_I2C_MULTIBYTE_MODE_2FF, 0x01);

	/*
	 * Due to xc5000c घड़ी stretch, we cannot use full speed at
	 * पढ़ोings from xc5000, as otherwise they'll fail.
	 */
	अगर (((dev->board.tuner_type == TUNER_XC5000) ||
	     (dev->board.tuner_type == TUNER_XC5000C)) &&
	    (dev->board.tuner_addr == msg->addr))
		i2c_speed = AU0828_I2C_CLK_20KHZ;

	/* Set the I2C घड़ी */
	au0828_ग_लिखो(dev, AU0828_I2C_CLK_DIVIDER_202, i2c_speed);

	/* Hardware needs 8 bit addresses */
	au0828_ग_लिखो(dev, AU0828_I2C_DEST_ADDR_203, msg->addr << 1);

	dprपूर्णांकk(4, " RECV:\n");

	/* Deal with i2c_scan */
	अगर (msg->len == 0) अणु
		au0828_ग_लिखो(dev, AU0828_I2C_TRIGGER_200,
			     AU0828_I2C_TRIGGER_READ);

		अगर (i2c_रुको_पढ़ो_ack(i2c_adap))
			वापस -EIO;
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < msg->len;) अणु

		i++;

		अगर (i < msg->len)
			au0828_ग_लिखो(dev, AU0828_I2C_TRIGGER_200,
				     AU0828_I2C_TRIGGER_READ |
				     AU0828_I2C_TRIGGER_HOLD);
		अन्यथा
			au0828_ग_लिखो(dev, AU0828_I2C_TRIGGER_200,
				     AU0828_I2C_TRIGGER_READ);

		अगर (!i2c_रुको_पढ़ो_करोne(i2c_adap))
			वापस -EIO;

		msg->buf[i-1] = au0828_पढ़ो(dev, AU0828_I2C_READ_FIFO_209) &
			0xff;

		dprपूर्णांकk(4, " %02x\n", msg->buf[i-1]);
	पूर्ण
	अगर (!i2c_रुको_करोne(i2c_adap))
		वापस -EIO;

	dprपूर्णांकk(4, "\n");

	वापस msg->len;
पूर्ण

अटल पूर्णांक i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
		    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक i, retval = 0;

	dprपूर्णांकk(4, "%s(num = %d)\n", __func__, num);

	क्रम (i = 0; i < num; i++) अणु
		dprपूर्णांकk(4, "%s(num = %d) addr = 0x%02x  len = 0x%x\n",
			__func__, num, msgs[i].addr, msgs[i].len);
		अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो */
			retval = i2c_पढ़ोbytes(i2c_adap, &msgs[i], 0);
		पूर्ण अन्यथा अगर (i + 1 < num && (msgs[i + 1].flags & I2C_M_RD) &&
			   msgs[i].addr == msgs[i + 1].addr) अणु
			/* ग_लिखो then पढ़ो from same address */
			retval = i2c_sendbytes(i2c_adap, &msgs[i],
					       msgs[i + 1].len);
			अगर (retval < 0)
				जाओ err;
			i++;
			retval = i2c_पढ़ोbytes(i2c_adap, &msgs[i], 1);
		पूर्ण अन्यथा अणु
			/* ग_लिखो */
			retval = i2c_sendbytes(i2c_adap, &msgs[i], 0);
		पूर्ण
		अगर (retval < 0)
			जाओ err;
	पूर्ण
	वापस num;

err:
	वापस retval;
पूर्ण

अटल u32 au0828_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL | I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm au0828_i2c_algo_ढाँचा = अणु
	.master_xfer	= i2c_xfer,
	.functionality	= au0828_functionality,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_adapter au0828_i2c_adap_ढाँचा = अणु
	.name              = KBUILD_MODNAME,
	.owner             = THIS_MODULE,
	.algo              = &au0828_i2c_algo_ढाँचा,
पूर्ण;

अटल स्थिर काष्ठा i2c_client au0828_i2c_client_ढाँचा = अणु
	.name	= "au0828 internal",
पूर्ण;

अटल अक्षर *i2c_devs[128] = अणु
	[0x8e >> 1] = "au8522",
	[0xa0 >> 1] = "eeprom",
	[0xc2 >> 1] = "tuner/xc5000",
पूर्ण;

अटल व्योम करो_i2c_scan(अक्षर *name, काष्ठा i2c_client *c)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक i, rc;

	क्रम (i = 0; i < 128; i++) अणु
		c->addr = i;
		rc = i2c_master_recv(c, &buf, 0);
		अगर (rc < 0)
			जारी;
		pr_info("%s: i2c scan: found device @ 0x%x  [%s]\n",
		       name, i << 1, i2c_devs[i] ? i2c_devs[i] : "???");
	पूर्ण
पूर्ण

/* init + रेजिस्टर i2c adapter */
पूर्णांक au0828_i2c_रेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	dev->i2c_adap = au0828_i2c_adap_ढाँचा;
	dev->i2c_algo = au0828_i2c_algo_ढाँचा;
	dev->i2c_client = au0828_i2c_client_ढाँचा;

	dev->i2c_adap.dev.parent = &dev->usbdev->dev;

	strscpy(dev->i2c_adap.name, KBUILD_MODNAME,
		माप(dev->i2c_adap.name));

	dev->i2c_adap.algo = &dev->i2c_algo;
	dev->i2c_adap.algo_data = dev;
#अगर_घोषित CONFIG_VIDEO_AU0828_V4L2
	i2c_set_adapdata(&dev->i2c_adap, &dev->v4l2_dev);
#अन्यथा
	i2c_set_adapdata(&dev->i2c_adap, dev);
#पूर्ण_अगर
	i2c_add_adapter(&dev->i2c_adap);

	dev->i2c_client.adapter = &dev->i2c_adap;

	अगर (0 == dev->i2c_rc) अणु
		pr_info("i2c bus registered\n");
		अगर (i2c_scan)
			करो_i2c_scan(KBUILD_MODNAME, &dev->i2c_client);
	पूर्ण अन्यथा
		pr_info("i2c bus register FAILED\n");

	वापस dev->i2c_rc;
पूर्ण

पूर्णांक au0828_i2c_unरेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	i2c_del_adapter(&dev->i2c_adap);
	वापस 0;
पूर्ण

