<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// em28xx-i2c.c - driver क्रम Empia EM2800/EM2820/2840 USB video capture devices
//
// Copyright (C) 2005 Luकरोvico Caveकरोn <caveकरोn@sssup.it>
//		      Markus Rechberger <mrechberger@gmail.com>
//		      Mauro Carvalho Chehab <mchehab@kernel.org>
//		      Sascha Sommer <saschasommer@मुक्तnet.de>
// Copyright (C) 2013 Frank Schथअfer <fschaefer.oss@googlemail.com>
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License क्रम more details.

#समावेश "em28xx.h"

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/jअगरfies.h>

#समावेश "tuner-xc2028.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>

/* ----------------------------------------------------------- */

अटल अचिन्हित पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan, "scan i2c bus at insmod time");

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "i2c debug message level (1: normal debug, 2: show I2C transfers)");

#घोषणा dprपूर्णांकk(level, fmt, arg...) करो अणु				\
	अगर (i2c_debug > level)						\
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "i2c: %s: " fmt, __func__, ## arg);		\
पूर्ण जबतक (0)

/*
 * Time in msecs to रुको क्रम i2c xfers to finish.
 * 35ms is the maximum समय a SMBUS device could रुको when
 * घड़ी stretching is used. As the transfer itself will take
 * some समय to happen, set it to 35 ms.
 *
 * Ok, I2C करोesn't specअगरy any limit. So, eventually, we may need
 * to increase this समयout.
 */
#घोषणा EM28XX_I2C_XFER_TIMEOUT         35 /* ms */

अटल पूर्णांक em28xx_i2c_समयout(काष्ठा em28xx *dev)
अणु
	पूर्णांक समय = EM28XX_I2C_XFER_TIMEOUT;

	चयन (dev->i2c_speed & 0x03) अणु
	हाल EM28XX_I2C_FREQ_25_KHZ:
		समय += 4;		/* Assume 4 ms क्रम transfers */
		अवरोध;
	हाल EM28XX_I2C_FREQ_100_KHZ:
	हाल EM28XX_I2C_FREQ_400_KHZ:
		समय += 1;		/* Assume 1 ms क्रम transfers */
		अवरोध;
	शेष: /* EM28XX_I2C_FREQ_1_5_MHZ */
		अवरोध;
	पूर्ण

	वापस msecs_to_jअगरfies(समय);
पूर्ण

/*
 * em2800_i2c_send_bytes()
 * send up to 4 bytes to the em2800 i2c device
 */
अटल पूर्णांक em2800_i2c_send_bytes(काष्ठा em28xx *dev, u8 addr, u8 *buf, u16 len)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + em28xx_i2c_समयout(dev);
	पूर्णांक ret;
	u8 b2[6];

	अगर (len < 1 || len > 4)
		वापस -EOPNOTSUPP;

	b2[5] = 0x80 + len - 1;
	b2[4] = addr;
	b2[3] = buf[0];
	अगर (len > 1)
		b2[2] = buf[1];
	अगर (len > 2)
		b2[1] = buf[2];
	अगर (len > 3)
		b2[0] = buf[3];

	/* trigger ग_लिखो */
	ret = dev->em28xx_ग_लिखो_regs(dev, 4 - len, &b2[4 - len], 2 + len);
	अगर (ret != 2 + len) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "failed to trigger write to i2c address 0x%x (error=%i)\n",
			    addr, ret);
		वापस (ret < 0) ? ret : -EIO;
	पूर्ण
	/* रुको क्रम completion */
	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		ret = dev->em28xx_पढ़ो_reg(dev, 0x05);
		अगर (ret == 0x80 + len - 1)
			वापस len;
		अगर (ret == 0x94 + len - 1) अणु
			dprपूर्णांकk(1, "R05 returned 0x%02x: I2C ACK error\n", ret);
			वापस -ENXIO;
		पूर्ण
		अगर (ret < 0) अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "failed to get i2c transfer status from bridge register (error=%i)\n",
				ret);
			वापस ret;
		पूर्ण
		usleep_range(5000, 6000);
	पूर्ण
	dprपूर्णांकk(0, "write to i2c device at 0x%x timed out\n", addr);
	वापस -ETIMEDOUT;
पूर्ण

/*
 * em2800_i2c_recv_bytes()
 * पढ़ो up to 4 bytes from the em2800 i2c device
 */
अटल पूर्णांक em2800_i2c_recv_bytes(काष्ठा em28xx *dev, u8 addr, u8 *buf, u16 len)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + em28xx_i2c_समयout(dev);
	u8 buf2[4];
	पूर्णांक ret;
	पूर्णांक i;

	अगर (len < 1 || len > 4)
		वापस -EOPNOTSUPP;

	/* trigger पढ़ो */
	buf2[1] = 0x84 + len - 1;
	buf2[0] = addr;
	ret = dev->em28xx_ग_लिखो_regs(dev, 0x04, buf2, 2);
	अगर (ret != 2) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "failed to trigger read from i2c address 0x%x (error=%i)\n",
			 addr, ret);
		वापस (ret < 0) ? ret : -EIO;
	पूर्ण

	/* रुको क्रम completion */
	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		ret = dev->em28xx_पढ़ो_reg(dev, 0x05);
		अगर (ret == 0x84 + len - 1)
			अवरोध;
		अगर (ret == 0x94 + len - 1) अणु
			dprपूर्णांकk(1, "R05 returned 0x%02x: I2C ACK error\n",
				ret);
			वापस -ENXIO;
		पूर्ण
		अगर (ret < 0) अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "failed to get i2c transfer status from bridge register (error=%i)\n",
				 ret);
			वापस ret;
		पूर्ण
		usleep_range(5000, 6000);
	पूर्ण
	अगर (ret != 0x84 + len - 1)
		dprपूर्णांकk(0, "read from i2c device at 0x%x timed out\n", addr);

	/* get the received message */
	ret = dev->em28xx_पढ़ो_reg_req_len(dev, 0x00, 4 - len, buf2, len);
	अगर (ret != len) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "reading from i2c device at 0x%x failed: couldn't get the received message from the bridge (error=%i)\n",
			 addr, ret);
		वापस (ret < 0) ? ret : -EIO;
	पूर्ण
	क्रम (i = 0; i < len; i++)
		buf[i] = buf2[len - 1 - i];

	वापस ret;
पूर्ण

/*
 * em2800_i2c_check_क्रम_device()
 * check अगर there is an i2c device at the supplied address
 */
अटल पूर्णांक em2800_i2c_check_क्रम_device(काष्ठा em28xx *dev, u8 addr)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = em2800_i2c_recv_bytes(dev, addr, &buf, 1);
	अगर (ret == 1)
		वापस 0;
	वापस (ret < 0) ? ret : -EIO;
पूर्ण

/*
 * em28xx_i2c_send_bytes()
 */
अटल पूर्णांक em28xx_i2c_send_bytes(काष्ठा em28xx *dev, u16 addr, u8 *buf,
				 u16 len, पूर्णांक stop)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + em28xx_i2c_समयout(dev);
	पूर्णांक ret;

	अगर (len < 1 || len > 64)
		वापस -EOPNOTSUPP;
	/*
	 * NOTE: limited by the USB ctrl message स्थिरraपूर्णांकs
	 * Zero length पढ़ोs always succeed, even अगर no device is connected
	 */

	/* Write to i2c device */
	ret = dev->em28xx_ग_लिखो_regs_req(dev, stop ? 2 : 3, addr, buf, len);
	अगर (ret != len) अणु
		अगर (ret < 0) अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "writing to i2c device at 0x%x failed (error=%i)\n",
				 addr, ret);
			वापस ret;
		पूर्ण
		dev_warn(&dev->पूर्णांकf->dev,
			 "%i bytes write to i2c device at 0x%x requested, but %i bytes written\n",
				len, addr, ret);
		वापस -EIO;
	पूर्ण

	/* रुको क्रम completion */
	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		ret = dev->em28xx_पढ़ो_reg(dev, 0x05);
		अगर (ret == 0) /* success */
			वापस len;
		अगर (ret == 0x10) अणु
			dprपूर्णांकk(1, "I2C ACK error on writing to addr 0x%02x\n",
				addr);
			वापस -ENXIO;
		पूर्ण
		अगर (ret < 0) अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "failed to get i2c transfer status from bridge register (error=%i)\n",
				 ret);
			वापस ret;
		पूर्ण
		usleep_range(5000, 6000);
		/*
		 * NOTE: करो we really have to रुको क्रम success ?
		 * Never seen anything अन्यथा than 0x00 or 0x10
		 * (even with high payload) ...
		 */
	पूर्ण

	अगर (ret == 0x02 || ret == 0x04) अणु
		/* NOTE: these errors seem to be related to घड़ी stretching */
		dprपूर्णांकk(0,
			"write to i2c device at 0x%x timed out (status=%i)\n",
			addr, ret);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_warn(&dev->पूर्णांकf->dev,
		 "write to i2c device at 0x%x failed with unknown error (status=%i)\n",
		 addr, ret);
	वापस -EIO;
पूर्ण

/*
 * em28xx_i2c_recv_bytes()
 * पढ़ो a byte from the i2c device
 */
अटल पूर्णांक em28xx_i2c_recv_bytes(काष्ठा em28xx *dev, u16 addr, u8 *buf, u16 len)
अणु
	पूर्णांक ret;

	अगर (len < 1 || len > 64)
		वापस -EOPNOTSUPP;
	/*
	 * NOTE: limited by the USB ctrl message स्थिरraपूर्णांकs
	 * Zero length पढ़ोs always succeed, even अगर no device is connected
	 */

	/* Read data from i2c device */
	ret = dev->em28xx_पढ़ो_reg_req_len(dev, 2, addr, buf, len);
	अगर (ret < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "reading from i2c device at 0x%x failed (error=%i)\n",
			 addr, ret);
		वापस ret;
	पूर्ण अन्यथा अगर (ret != len) अणु
		dev_dbg(&dev->पूर्णांकf->dev,
			"%i bytes read from i2c device at 0x%x requested, but %i bytes written\n",
				ret, addr, len);
	पूर्ण
	/*
	 * NOTE: some devices with two i2c buses have the bad habit to वापस 0
	 * bytes अगर we are on bus B AND there was no ग_लिखो attempt to the
	 * specअगरied slave address beक्रमe AND no device is present at the
	 * requested slave address.
	 * Anyway, the next check will fail with -ENXIO in this हाल, so aव्योम
	 * spamming the प्रणाली log on device probing and करो nothing here.
	 */

	/* Check success of the i2c operation */
	ret = dev->em28xx_पढ़ो_reg(dev, 0x05);
	अगर (ret == 0) /* success */
		वापस len;
	अगर (ret < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "failed to get i2c transfer status from bridge register (error=%i)\n",
			 ret);
		वापस ret;
	पूर्ण
	अगर (ret == 0x10) अणु
		dprपूर्णांकk(1, "I2C ACK error on writing to addr 0x%02x\n",
			addr);
		वापस -ENXIO;
	पूर्ण

	अगर (ret == 0x02 || ret == 0x04) अणु
		/* NOTE: these errors seem to be related to घड़ी stretching */
		dprपूर्णांकk(0,
			"write to i2c device at 0x%x timed out (status=%i)\n",
			addr, ret);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_warn(&dev->पूर्णांकf->dev,
		 "read from i2c device at 0x%x failed with unknown error (status=%i)\n",
		 addr, ret);
	वापस -EIO;
पूर्ण

/*
 * em28xx_i2c_check_क्रम_device()
 * check अगर there is a i2c_device at the supplied address
 */
अटल पूर्णांक em28xx_i2c_check_क्रम_device(काष्ठा em28xx *dev, u16 addr)
अणु
	पूर्णांक ret;
	u8 buf;

	ret = em28xx_i2c_recv_bytes(dev, addr, &buf, 1);
	अगर (ret == 1)
		वापस 0;
	वापस (ret < 0) ? ret : -EIO;
पूर्ण

/*
 * em25xx_bus_B_send_bytes
 * ग_लिखो bytes to the i2c device
 */
अटल पूर्णांक em25xx_bus_B_send_bytes(काष्ठा em28xx *dev, u16 addr, u8 *buf,
				   u16 len)
अणु
	पूर्णांक ret;

	अगर (len < 1 || len > 64)
		वापस -EOPNOTSUPP;
	/*
	 * NOTE: limited by the USB ctrl message स्थिरraपूर्णांकs
	 * Zero length पढ़ोs always succeed, even अगर no device is connected
	 */

	/* Set रेजिस्टर and ग_लिखो value */
	ret = dev->em28xx_ग_लिखो_regs_req(dev, 0x06, addr, buf, len);
	अगर (ret != len) अणु
		अगर (ret < 0) अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "writing to i2c device at 0x%x failed (error=%i)\n",
				 addr, ret);
			वापस ret;
		पूर्ण

		dev_warn(&dev->पूर्णांकf->dev,
			 "%i bytes write to i2c device at 0x%x requested, but %i bytes written\n",
			 len, addr, ret);
		वापस -EIO;
	पूर्ण
	/* Check success */
	ret = dev->em28xx_पढ़ो_reg_req(dev, 0x08, 0x0000);
	/*
	 * NOTE: the only error we've seen so far is
	 * 0x01 when the slave device is not present
	 */
	अगर (!ret)
		वापस len;

	अगर (ret > 0) अणु
		dprपूर्णांकk(1, "Bus B R08 returned 0x%02x: I2C ACK error\n", ret);
		वापस -ENXIO;
	पूर्ण

	वापस ret;
	/*
	 * NOTE: With chip types (other chip IDs) which actually करोn't support
	 * this operation, it seems to succeed ALWAYS ! (even अगर there is no
	 * slave device or even no second i2c bus provided)
	 */
पूर्ण

/*
 * em25xx_bus_B_recv_bytes
 * पढ़ो bytes from the i2c device
 */
अटल पूर्णांक em25xx_bus_B_recv_bytes(काष्ठा em28xx *dev, u16 addr, u8 *buf,
				   u16 len)
अणु
	पूर्णांक ret;

	अगर (len < 1 || len > 64)
		वापस -EOPNOTSUPP;
	/*
	 * NOTE: limited by the USB ctrl message स्थिरraपूर्णांकs
	 * Zero length पढ़ोs always succeed, even अगर no device is connected
	 */

	/* Read value */
	ret = dev->em28xx_पढ़ो_reg_req_len(dev, 0x06, addr, buf, len);
	अगर (ret < 0) अणु
		dev_warn(&dev->पूर्णांकf->dev,
			 "reading from i2c device at 0x%x failed (error=%i)\n",
			 addr, ret);
		वापस ret;
	पूर्ण
	/*
	 * NOTE: some devices with two i2c buses have the bad habit to वापस 0
	 * bytes अगर we are on bus B AND there was no ग_लिखो attempt to the
	 * specअगरied slave address beक्रमe AND no device is present at the
	 * requested slave address.
	 * Anyway, the next check will fail with -ENXIO in this हाल, so aव्योम
	 * spamming the प्रणाली log on device probing and करो nothing here.
	 */

	/* Check success */
	ret = dev->em28xx_पढ़ो_reg_req(dev, 0x08, 0x0000);
	/*
	 * NOTE: the only error we've seen so far is
	 * 0x01 when the slave device is not present
	 */
	अगर (!ret)
		वापस len;

	अगर (ret > 0) अणु
		dprपूर्णांकk(1, "Bus B R08 returned 0x%02x: I2C ACK error\n", ret);
		वापस -ENXIO;
	पूर्ण

	वापस ret;
	/*
	 * NOTE: With chip types (other chip IDs) which actually करोn't support
	 * this operation, it seems to succeed ALWAYS ! (even अगर there is no
	 * slave device or even no second i2c bus provided)
	 */
पूर्ण

/*
 * em25xx_bus_B_check_क्रम_device()
 * check अगर there is a i2c device at the supplied address
 */
अटल पूर्णांक em25xx_bus_B_check_क्रम_device(काष्ठा em28xx *dev, u16 addr)
अणु
	u8 buf;
	पूर्णांक ret;

	ret = em25xx_bus_B_recv_bytes(dev, addr, &buf, 1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
	/*
	 * NOTE: With chips which करो not support this operation,
	 * it seems to succeed ALWAYS ! (even अगर no device connected)
	 */
पूर्ण

अटल अंतरभूत पूर्णांक i2c_check_क्रम_device(काष्ठा em28xx_i2c_bus *i2c_bus, u16 addr)
अणु
	काष्ठा em28xx *dev = i2c_bus->dev;
	पूर्णांक rc = -EOPNOTSUPP;

	अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM28XX)
		rc = em28xx_i2c_check_क्रम_device(dev, addr);
	अन्यथा अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM2800)
		rc = em2800_i2c_check_क्रम_device(dev, addr);
	अन्यथा अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM25XX_BUS_B)
		rc = em25xx_bus_B_check_क्रम_device(dev, addr);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_recv_bytes(काष्ठा em28xx_i2c_bus *i2c_bus,
				 काष्ठा i2c_msg msg)
अणु
	काष्ठा em28xx *dev = i2c_bus->dev;
	u16 addr = msg.addr << 1;
	पूर्णांक rc = -EOPNOTSUPP;

	अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM28XX)
		rc = em28xx_i2c_recv_bytes(dev, addr, msg.buf, msg.len);
	अन्यथा अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM2800)
		rc = em2800_i2c_recv_bytes(dev, addr, msg.buf, msg.len);
	अन्यथा अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM25XX_BUS_B)
		rc = em25xx_bus_B_recv_bytes(dev, addr, msg.buf, msg.len);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_send_bytes(काष्ठा em28xx_i2c_bus *i2c_bus,
				 काष्ठा i2c_msg msg, पूर्णांक stop)
अणु
	काष्ठा em28xx *dev = i2c_bus->dev;
	u16 addr = msg.addr << 1;
	पूर्णांक rc = -EOPNOTSUPP;

	अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM28XX)
		rc = em28xx_i2c_send_bytes(dev, addr, msg.buf, msg.len, stop);
	अन्यथा अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM2800)
		rc = em2800_i2c_send_bytes(dev, addr, msg.buf, msg.len);
	अन्यथा अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM25XX_BUS_B)
		rc = em25xx_bus_B_send_bytes(dev, addr, msg.buf, msg.len);
	वापस rc;
पूर्ण

/*
 * em28xx_i2c_xfer()
 * the मुख्य i2c transfer function
 */
अटल पूर्णांक em28xx_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			   काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा em28xx_i2c_bus *i2c_bus = i2c_adap->algo_data;
	काष्ठा em28xx *dev = i2c_bus->dev;
	अचिन्हित पूर्णांक bus = i2c_bus->bus;
	पूर्णांक addr, rc, i;
	u8 reg;

	/*
	 * prevent i2c xfer attempts after device is disconnected
	 * some fe's try to करो i2c ग_लिखोs/पढ़ोs from their release
	 * पूर्णांकerfaces when called in disconnect path
	 */
	अगर (dev->disconnected)
		वापस -ENODEV;

	अगर (!rt_mutex_trylock(&dev->i2c_bus_lock))
		वापस -EAGAIN;

	/* Switch I2C bus अगर needed */
	अगर (bus != dev->cur_i2c_bus &&
	    i2c_bus->algo_type == EM28XX_I2C_ALGO_EM28XX) अणु
		अगर (bus == 1)
			reg = EM2874_I2C_SECONDARY_BUS_SELECT;
		अन्यथा
			reg = 0;
		em28xx_ग_लिखो_reg_bits(dev, EM28XX_R06_I2C_CLK, reg,
				      EM2874_I2C_SECONDARY_BUS_SELECT);
		dev->cur_i2c_bus = bus;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		addr = msgs[i].addr << 1;
		अगर (!msgs[i].len) अणु
			/*
			 * no len: check only क्रम device presence
			 * This code is only called during device probe.
			 */
			rc = i2c_check_क्रम_device(i2c_bus, addr);

			अगर (rc == -ENXIO)
				rc = -ENODEV;
		पूर्ण अन्यथा अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो bytes */
			rc = i2c_recv_bytes(i2c_bus, msgs[i]);
		पूर्ण अन्यथा अणु
			/* ग_लिखो bytes */
			rc = i2c_send_bytes(i2c_bus, msgs[i], i == num - 1);
		पूर्ण

		अगर (rc < 0)
			जाओ error;

		dprपूर्णांकk(2, "%s %s addr=%02x len=%d: %*ph\n",
			(msgs[i].flags & I2C_M_RD) ? "read" : "write",
			i == num - 1 ? "stop" : "nonstop",
			addr, msgs[i].len,
			msgs[i].len, msgs[i].buf);
	पूर्ण

	rt_mutex_unlock(&dev->i2c_bus_lock);
	वापस num;

error:
	dprपूर्णांकk(2, "%s %s addr=%02x len=%d: %sERROR: %i\n",
		(msgs[i].flags & I2C_M_RD) ? "read" : "write",
		i == num - 1 ? "stop" : "nonstop",
		addr, msgs[i].len,
		(rc == -ENODEV) ? "no device " : "",
		rc);

	rt_mutex_unlock(&dev->i2c_bus_lock);
	वापस rc;
पूर्ण

/*
 * based on linux/sunrpc/svcauth.h and linux/hash.h
 * The original hash function वापसs a dअगरferent value, अगर arch is x86_64
 * or i386.
 */
अटल अंतरभूत अचिन्हित दीर्घ em28xx_hash_mem(अक्षर *buf, पूर्णांक length, पूर्णांक bits)
अणु
	अचिन्हित दीर्घ hash = 0;
	अचिन्हित दीर्घ l = 0;
	पूर्णांक len = 0;
	अचिन्हित अक्षर c;

	करो अणु
		अगर (len == length) अणु
			c = (अक्षर)len;
			len = -1;
		पूर्ण अन्यथा अणु
			c = *buf++;
		पूर्ण
		l = (l << 8) | c;
		len++;
		अगर ((len & (32 / 8 - 1)) == 0)
			hash = ((hash ^ l) * 0x9e370001UL);
	पूर्ण जबतक (len);

	वापस (hash >> (32 - bits)) & 0xffffffffUL;
पूर्ण

/*
 * Helper function to पढ़ो data blocks from i2c clients with 8 or 16 bit
 * address width, 8 bit रेजिस्टर width and स्वतः incrementation been activated
 */
अटल पूर्णांक em28xx_i2c_पढ़ो_block(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus, u16 addr,
				 bool addr_w16, u16 len, u8 *data)
अणु
	पूर्णांक reमुख्य = len, rsize, rsize_max, ret;
	u8 buf[2];

	/* Sanity check */
	अगर (addr + reमुख्य > (addr_w16 * 0xff00 + 0xff + 1))
		वापस -EINVAL;
	/* Select address */
	buf[0] = addr >> 8;
	buf[1] = addr & 0xff;
	ret = i2c_master_send(&dev->i2c_client[bus],
			      buf + !addr_w16, 1 + addr_w16);
	अगर (ret < 0)
		वापस ret;
	/* Read data */
	अगर (dev->board.is_em2800)
		rsize_max = 4;
	अन्यथा
		rsize_max = 64;
	जबतक (reमुख्य > 0) अणु
		अगर (reमुख्य > rsize_max)
			rsize = rsize_max;
		अन्यथा
			rsize = reमुख्य;

		ret = i2c_master_recv(&dev->i2c_client[bus], data, rsize);
		अगर (ret < 0)
			वापस ret;

		reमुख्य -= rsize;
		data += rsize;
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक em28xx_i2c_eeprom(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus,
			     u8 **eedata, u16 *eedata_len)
अणु
	स्थिर u16 len = 256;
	/*
	 * FIXME common length/size क्रम bytes to पढ़ो, to display, hash
	 * calculation and वापसed device dataset. Simplअगरies the code a lot,
	 * but we might have to deal with multiple sizes in the future !
	 */
	पूर्णांक err;
	काष्ठा em28xx_eeprom *dev_config;
	u8 buf, *data;

	*eedata = शून्य;
	*eedata_len = 0;

	/* EEPROM is always on i2c bus 0 on all known devices. */

	dev->i2c_client[bus].addr = 0xa0 >> 1;

	/* Check अगर board has eeprom */
	err = i2c_master_recv(&dev->i2c_client[bus], &buf, 0);
	अगर (err < 0) अणु
		dev_info(&dev->पूर्णांकf->dev, "board has no eeprom\n");
		वापस -ENODEV;
	पूर्ण

	data = kzalloc(len, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* Read EEPROM content */
	err = em28xx_i2c_पढ़ो_block(dev, bus, 0x0000,
				    dev->eeprom_addrwidth_16bit,
				    len, data);
	अगर (err != len) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"failed to read eeprom (err=%d)\n", err);
		जाओ error;
	पूर्ण

	अगर (i2c_debug) अणु
		/* Display eeprom content */
		prपूर्णांक_hex_dump(KERN_DEBUG, "em28xx eeprom ", DUMP_PREFIX_OFFSET,
			       16, 1, data, len, true);

		अगर (dev->eeprom_addrwidth_16bit)
			dev_info(&dev->पूर्णांकf->dev,
				 "eeprom %06x: ... (skipped)\n", 256);
	पूर्ण

	अगर (dev->eeprom_addrwidth_16bit &&
	    data[0] == 0x26 && data[3] == 0x00) अणु
		/* new eeprom क्रमmat; size 4-64kb */
		u16 mc_start;
		u16 hwconf_offset;

		dev->hash = em28xx_hash_mem(data, len, 32);
		mc_start = (data[1] << 8) + 4;	/* usually 0x0004 */

		dev_info(&dev->पूर्णांकf->dev,
			 "EEPROM ID = %4ph, EEPROM hash = 0x%08lx\n",
			 data, dev->hash);
		dev_info(&dev->पूर्णांकf->dev,
			 "EEPROM info:\n");
		dev_info(&dev->पूर्णांकf->dev,
			 "\tmicrocode start address = 0x%04x, boot configuration = 0x%02x\n",
			 mc_start, data[2]);
		/*
		 * boot configuration (address 0x0002):
		 * [0]   microcode करोwnload speed: 1 = 400 kHz; 0 = 100 kHz
		 * [1]   always selects 12 kb RAM
		 * [2]   USB device speed: 1 = क्रमce Full Speed; 0 = स्वतः detect
		 * [4]   1 = क्रमce fast mode and no suspend क्रम device testing
		 * [5:7] USB PHY tuning रेजिस्टरs; determined by device
		 *       अक्षरacterization
		 */

		/*
		 * Read hardware config dataset offset from address
		 * (microcode start + 46)
		 */
		err = em28xx_i2c_पढ़ो_block(dev, bus, mc_start + 46, 1, 2,
					    data);
		अगर (err != 2) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"failed to read hardware configuration data from eeprom (err=%d)\n",
				err);
			जाओ error;
		पूर्ण

		/* Calculate hardware config dataset start address */
		hwconf_offset = mc_start + data[0] + (data[1] << 8);

		/* Read hardware config dataset */
		/*
		 * NOTE: the microcode copy can be multiple pages दीर्घ, but
		 * we assume the hardware config dataset is the same as in
		 * the old eeprom and not दीर्घer than 256 bytes.
		 * tveeprom is currently also limited to 256 bytes.
		 */
		err = em28xx_i2c_पढ़ो_block(dev, bus, hwconf_offset, 1, len,
					    data);
		अगर (err != len) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"failed to read hardware configuration data from eeprom (err=%d)\n",
				err);
			जाओ error;
		पूर्ण

		/* Verअगरy hardware config dataset */
		/* NOTE: not all devices provide this type of dataset */
		अगर (data[0] != 0x1a || data[1] != 0xeb ||
		    data[2] != 0x67 || data[3] != 0x95) अणु
			dev_info(&dev->पूर्णांकf->dev,
				 "\tno hardware configuration dataset found in eeprom\n");
			kमुक्त(data);
			वापस 0;
		पूर्ण

		/*
		 * TODO: decrypt eeprom data क्रम camera bridges
		 * (em25xx, em276x+)
		 */

	पूर्ण अन्यथा अगर (!dev->eeprom_addrwidth_16bit &&
		   data[0] == 0x1a && data[1] == 0xeb &&
		   data[2] == 0x67 && data[3] == 0x95) अणु
		dev->hash = em28xx_hash_mem(data, len, 32);
		dev_info(&dev->पूर्णांकf->dev,
			 "EEPROM ID = %4ph, EEPROM hash = 0x%08lx\n",
			 data, dev->hash);
		dev_info(&dev->पूर्णांकf->dev,
			 "EEPROM info:\n");
	पूर्ण अन्यथा अणु
		dev_info(&dev->पूर्णांकf->dev,
			 "unknown eeprom format or eeprom corrupted !\n");
		err = -ENODEV;
		जाओ error;
	पूर्ण

	*eedata = data;
	*eedata_len = len;
	dev_config = (व्योम *)*eedata;

	चयन (le16_to_cpu(dev_config->chip_conf) >> 4 & 0x3) अणु
	हाल 0:
		dev_info(&dev->पूर्णांकf->dev, "\tNo audio on board.\n");
		अवरोध;
	हाल 1:
		dev_info(&dev->पूर्णांकf->dev, "\tAC97 audio (5 sample rates)\n");
		अवरोध;
	हाल 2:
		अगर (dev->chip_id < CHIP_ID_EM2860)
			dev_info(&dev->पूर्णांकf->dev,
				 "\tI2S audio, sample rate=32k\n");
		अन्यथा
			dev_info(&dev->पूर्णांकf->dev,
				 "\tI2S audio, 3 sample rates\n");
		अवरोध;
	हाल 3:
		अगर (dev->chip_id < CHIP_ID_EM2860)
			dev_info(&dev->पूर्णांकf->dev,
				 "\tI2S audio, 3 sample rates\n");
		अन्यथा
			dev_info(&dev->पूर्णांकf->dev,
				 "\tI2S audio, 5 sample rates\n");
		अवरोध;
	पूर्ण

	अगर (le16_to_cpu(dev_config->chip_conf) & 1 << 3)
		dev_info(&dev->पूर्णांकf->dev, "\tUSB Remote wakeup capable\n");

	अगर (le16_to_cpu(dev_config->chip_conf) & 1 << 2)
		dev_info(&dev->पूर्णांकf->dev, "\tUSB Self power capable\n");

	चयन (le16_to_cpu(dev_config->chip_conf) & 0x3) अणु
	हाल 0:
		dev_info(&dev->पूर्णांकf->dev, "\t500mA max power\n");
		अवरोध;
	हाल 1:
		dev_info(&dev->पूर्णांकf->dev, "\t400mA max power\n");
		अवरोध;
	हाल 2:
		dev_info(&dev->पूर्णांकf->dev, "\t300mA max power\n");
		अवरोध;
	हाल 3:
		dev_info(&dev->पूर्णांकf->dev, "\t200mA max power\n");
		अवरोध;
	पूर्ण
	dev_info(&dev->पूर्णांकf->dev,
		 "\tTable at offset 0x%02x, strings=0x%04x, 0x%04x, 0x%04x\n",
		 dev_config->string_idx_table,
		 le16_to_cpu(dev_config->string1),
		 le16_to_cpu(dev_config->string2),
		 le16_to_cpu(dev_config->string3));

	वापस 0;

error:
	kमुक्त(data);
	वापस err;
पूर्ण

/* ----------------------------------------------------------- */

/*
 * functionality()
 */
अटल u32 functionality(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा em28xx_i2c_bus *i2c_bus = i2c_adap->algo_data;

	अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM28XX ||
	    i2c_bus->algo_type == EM28XX_I2C_ALGO_EM25XX_BUS_B) अणु
		वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
	पूर्ण अन्यथा अगर (i2c_bus->algo_type == EM28XX_I2C_ALGO_EM2800)  अणु
		वापस (I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL) &
			~I2C_FUNC_SMBUS_WRITE_BLOCK_DATA;
	पूर्ण

	WARN(1, "Unknown i2c bus algorithm.\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm em28xx_algo = अणु
	.master_xfer   = em28xx_i2c_xfer,
	.functionality = functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter em28xx_adap_ढाँचा = अणु
	.owner = THIS_MODULE,
	.name = "em28xx",
	.algo = &em28xx_algo,
पूर्ण;

अटल स्थिर काष्ठा i2c_client em28xx_client_ढाँचा = अणु
	.name = "em28xx internal",
पूर्ण;

/* ----------------------------------------------------------- */

/*
 * i2c_devs
 * incomplete list of known devices
 */
अटल अक्षर *i2c_devs[128] = अणु
	[0x1c >> 1] = "lgdt330x",
	[0x3e >> 1] = "remote IR sensor",
	[0x4a >> 1] = "saa7113h",
	[0x52 >> 1] = "drxk",
	[0x60 >> 1] = "remote IR sensor",
	[0x8e >> 1] = "remote IR sensor",
	[0x86 >> 1] = "tda9887",
	[0x80 >> 1] = "msp34xx",
	[0x88 >> 1] = "msp34xx",
	[0xa0 >> 1] = "eeprom",
	[0xb0 >> 1] = "tda9874",
	[0xb8 >> 1] = "tvp5150a",
	[0xba >> 1] = "webcam sensor or tvp5150a",
	[0xc0 >> 1] = "tuner (analog)",
	[0xc2 >> 1] = "tuner (analog)",
	[0xc4 >> 1] = "tuner (analog)",
	[0xc6 >> 1] = "tuner (analog)",
पूर्ण;

/*
 * करो_i2c_scan()
 * check i2c address range क्रम devices
 */
व्योम em28xx_करो_i2c_scan(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus)
अणु
	u8 i2c_devicelist[128];
	अचिन्हित अक्षर buf;
	पूर्णांक i, rc;

	स_रखो(i2c_devicelist, 0, माप(i2c_devicelist));

	क्रम (i = 0; i < ARRAY_SIZE(i2c_devs); i++) अणु
		dev->i2c_client[bus].addr = i;
		rc = i2c_master_recv(&dev->i2c_client[bus], &buf, 0);
		अगर (rc < 0)
			जारी;
		i2c_devicelist[i] = i;
		dev_info(&dev->पूर्णांकf->dev,
			 "found i2c device @ 0x%x on bus %d [%s]\n",
			 i << 1, bus, i2c_devs[i] ? i2c_devs[i] : "???");
	पूर्ण

	अगर (bus == dev->def_i2c_bus)
		dev->i2c_hash = em28xx_hash_mem(i2c_devicelist,
						माप(i2c_devicelist), 32);
पूर्ण

/*
 * em28xx_i2c_रेजिस्टर()
 * रेजिस्टर i2c bus
 */
पूर्णांक em28xx_i2c_रेजिस्टर(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus,
			क्रमागत em28xx_i2c_algo_type algo_type)
अणु
	पूर्णांक retval;

	अगर (WARN_ON(!dev->em28xx_ग_लिखो_regs || !dev->em28xx_पढ़ो_reg ||
		    !dev->em28xx_ग_लिखो_regs_req || !dev->em28xx_पढ़ो_reg_req))
		वापस -ENODEV;

	अगर (bus >= NUM_I2C_BUSES)
		वापस -ENODEV;

	dev->i2c_adap[bus] = em28xx_adap_ढाँचा;
	dev->i2c_adap[bus].dev.parent = &dev->पूर्णांकf->dev;
	strscpy(dev->i2c_adap[bus].name, dev_name(&dev->पूर्णांकf->dev),
		माप(dev->i2c_adap[bus].name));

	dev->i2c_bus[bus].bus = bus;
	dev->i2c_bus[bus].algo_type = algo_type;
	dev->i2c_bus[bus].dev = dev;
	dev->i2c_adap[bus].algo_data = &dev->i2c_bus[bus];

	retval = i2c_add_adapter(&dev->i2c_adap[bus]);
	अगर (retval < 0) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"%s: i2c_add_adapter failed! retval [%d]\n",
			__func__, retval);
		वापस retval;
	पूर्ण

	dev->i2c_client[bus] = em28xx_client_ढाँचा;
	dev->i2c_client[bus].adapter = &dev->i2c_adap[bus];

	/* Up to now, all eeproms are at bus 0 */
	अगर (!bus) अणु
		retval = em28xx_i2c_eeprom(dev, bus,
					   &dev->eedata, &dev->eedata_len);
		अगर (retval < 0 && retval != -ENODEV) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"%s: em28xx_i2_eeprom failed! retval [%d]\n",
				__func__, retval);
		पूर्ण
	पूर्ण

	अगर (i2c_scan)
		em28xx_करो_i2c_scan(dev, bus);

	वापस 0;
पूर्ण

/*
 * em28xx_i2c_unरेजिस्टर()
 * unरेजिस्टर i2c_bus
 */
पूर्णांक em28xx_i2c_unरेजिस्टर(काष्ठा em28xx *dev, अचिन्हित पूर्णांक bus)
अणु
	अगर (bus >= NUM_I2C_BUSES)
		वापस -ENODEV;

	i2c_del_adapter(&dev->i2c_adap[bus]);
	वापस 0;
पूर्ण
