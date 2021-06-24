<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// पंचांग6000-i2c.c - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
//
// Copyright (c) 2006-2007 Mauro Carvalho Chehab <mchehab@kernel.org>
//
// Copyright (c) 2007 Michel Ludwig <michel.ludwig@gmail.com>
//	- Fix SMBus Read Byte command

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>

#समावेश "tm6000.h"
#समावेश "tm6000-regs.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>
#समावेश "tuner-xc2028.h"


/* ----------------------------------------------------------- */

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "enable debug messages [i2c]");

#घोषणा i2c_dprपूर्णांकk(lvl, fmt, args...) अगर (i2c_debug >= lvl) करो अणु \
			prपूर्णांकk(KERN_DEBUG "%s at %s: " fmt, \
			dev->name, __func__, ##args); पूर्ण जबतक (0)

अटल पूर्णांक पंचांग6000_i2c_send_regs(काष्ठा पंचांग6000_core *dev, अचिन्हित अक्षर addr,
				__u8 reg, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक i2c_packet_limit = 16;

	अगर (dev->dev_type == TM6010)
		i2c_packet_limit = 80;

	अगर (!buf)
		वापस -1;

	अगर (len < 1 || len > i2c_packet_limit) अणु
		prपूर्णांकk(KERN_ERR "Incorrect length of i2c packet = %d, limit set to %d\n",
			len, i2c_packet_limit);
		वापस -1;
	पूर्ण

	/* capture mutex */
	rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_OUT | USB_TYPE_VENDOR |
		USB_RECIP_DEVICE, REQ_16_SET_GET_I2C_WR1_RDN,
		addr | reg << 8, 0, buf, len);

	अगर (rc < 0) अणु
		/* release mutex */
		वापस rc;
	पूर्ण

	/* release mutex */
	वापस rc;
पूर्ण

/* Generic पढ़ो - करोesn't work fine with 16bit रेजिस्टरs */
अटल पूर्णांक पंचांग6000_i2c_recv_regs(काष्ठा पंचांग6000_core *dev, अचिन्हित अक्षर addr,
				__u8 reg, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक rc;
	u8 b[2];
	अचिन्हित पूर्णांक i2c_packet_limit = 16;

	अगर (dev->dev_type == TM6010)
		i2c_packet_limit = 64;

	अगर (!buf)
		वापस -1;

	अगर (len < 1 || len > i2c_packet_limit) अणु
		prपूर्णांकk(KERN_ERR "Incorrect length of i2c packet = %d, limit set to %d\n",
			len, i2c_packet_limit);
		वापस -1;
	पूर्ण

	/* capture mutex */
	अगर ((dev->caps.has_zl10353) && (dev->demod_addr << 1 == addr) && (reg % 2 == 0)) अणु
		/*
		 * Workaround an I2C bug when पढ़ोing from zl10353
		 */
		reg -= 1;
		len += 1;

		rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			REQ_16_SET_GET_I2C_WR1_RDN, addr | reg << 8, 0, b, len);

		*buf = b[1];
	पूर्ण अन्यथा अणु
		rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			REQ_16_SET_GET_I2C_WR1_RDN, addr | reg << 8, 0, buf, len);
	पूर्ण

	/* release mutex */
	वापस rc;
पूर्ण

/*
 * पढ़ो from a 16bit रेजिस्टर
 * क्रम example xc2028, xc3028 or xc3028L
 */
अटल पूर्णांक पंचांग6000_i2c_recv_regs16(काष्ठा पंचांग6000_core *dev, अचिन्हित अक्षर addr,
				  __u16 reg, अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक rc;
	अचिन्हित अक्षर ureg;

	अगर (!buf || len != 2)
		वापस -1;

	/* capture mutex */
	अगर (dev->dev_type == TM6010) अणु
		ureg = reg & 0xFF;
		rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_OUT | USB_TYPE_VENDOR |
			USB_RECIP_DEVICE, REQ_16_SET_GET_I2C_WR1_RDN,
			addr | (reg & 0xFF00), 0, &ureg, 1);

		अगर (rc < 0) अणु
			/* release mutex */
			वापस rc;
		पूर्ण

		rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR |
			USB_RECIP_DEVICE, REQ_35_AFTEK_TUNER_READ,
			reg, 0, buf, len);
	पूर्ण अन्यथा अणु
		rc = पंचांग6000_पढ़ो_ग_लिखो_usb(dev, USB_सूची_IN | USB_TYPE_VENDOR |
			USB_RECIP_DEVICE, REQ_14_SET_GET_I2C_WR2_RDN,
			addr, reg, buf, len);
	पूर्ण

	/* release mutex */
	वापस rc;
पूर्ण

अटल पूर्णांक पंचांग6000_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			   काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा पंचांग6000_core *dev = i2c_adap->algo_data;
	पूर्णांक addr, rc, i, byte;

	क्रम (i = 0; i < num; i++) अणु
		addr = (msgs[i].addr << 1) & 0xff;
		i2c_dprपूर्णांकk(2, "%s %s addr=0x%x len=%d:",
			 (msgs[i].flags & I2C_M_RD) ? "read" : "write",
			 i == num - 1 ? "stop" : "nonstop", addr, msgs[i].len);
		अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो request without preceding रेजिस्टर selection */
			/*
			 * The TM6000 only supports a पढ़ो transaction
			 * immediately after a 1 or 2 byte ग_लिखो to select
			 * a रेजिस्टर.  We cannot fulfill this request.
			 */
			i2c_dprपूर्णांकk(2, " read without preceding write not supported");
			rc = -EOPNOTSUPP;
			जाओ err;
		पूर्ण अन्यथा अगर (i + 1 < num && msgs[i].len <= 2 &&
			   (msgs[i + 1].flags & I2C_M_RD) &&
			   msgs[i].addr == msgs[i + 1].addr) अणु
			/* 1 or 2 byte ग_लिखो followed by a पढ़ो */
			अगर (i2c_debug >= 2)
				क्रम (byte = 0; byte < msgs[i].len; byte++)
					prपूर्णांकk(KERN_CONT " %02x", msgs[i].buf[byte]);
			i2c_dprपूर्णांकk(2, "; joined to read %s len=%d:",
				    i == num - 2 ? "stop" : "nonstop",
				    msgs[i + 1].len);

			अगर (msgs[i].len == 2) अणु
				rc = पंचांग6000_i2c_recv_regs16(dev, addr,
					msgs[i].buf[0] << 8 | msgs[i].buf[1],
					msgs[i + 1].buf, msgs[i + 1].len);
			पूर्ण अन्यथा अणु
				rc = पंचांग6000_i2c_recv_regs(dev, addr, msgs[i].buf[0],
					msgs[i + 1].buf, msgs[i + 1].len);
			पूर्ण

			i++;

			अगर (addr == dev->tuner_addr << 1) अणु
				पंचांग6000_set_reg(dev, REQ_50_SET_START, 0, 0);
				पंचांग6000_set_reg(dev, REQ_51_SET_STOP, 0, 0);
			पूर्ण
			अगर (i2c_debug >= 2)
				क्रम (byte = 0; byte < msgs[i].len; byte++)
					prपूर्णांकk(KERN_CONT " %02x", msgs[i].buf[byte]);
		पूर्ण अन्यथा अणु
			/* ग_लिखो bytes */
			अगर (i2c_debug >= 2)
				क्रम (byte = 0; byte < msgs[i].len; byte++)
					prपूर्णांकk(KERN_CONT " %02x", msgs[i].buf[byte]);
			rc = पंचांग6000_i2c_send_regs(dev, addr, msgs[i].buf[0],
				msgs[i].buf + 1, msgs[i].len - 1);
		पूर्ण
		अगर (i2c_debug >= 2)
			prपूर्णांकk(KERN_CONT "\n");
		अगर (rc < 0)
			जाओ err;
	पूर्ण

	वापस num;
err:
	i2c_dprपूर्णांकk(2, " ERROR: %i\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक पंचांग6000_i2c_eeprom(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक i, rc;
	अचिन्हित अक्षर *p = dev->eedata;
	अचिन्हित अक्षर bytes[17];

	dev->i2c_client.addr = 0xa0 >> 1;
	dev->eedata_size = 0;

	bytes[16] = '\0';
	क्रम (i = 0; i < माप(dev->eedata); ) अणु
		*p = i;
		rc = पंचांग6000_i2c_recv_regs(dev, 0xa0, i, p, 1);
		अगर (rc < 1) अणु
			अगर (p == dev->eedata)
				जाओ noeeprom;
			अन्यथा अणु
				prपूर्णांकk(KERN_WARNING
				"%s: i2c eeprom read error (err=%d)\n",
				dev->name, rc);
			पूर्ण
			वापस -EINVAL;
		पूर्ण
		dev->eedata_size++;
		p++;
		अगर (0 == (i % 16))
			prपूर्णांकk(KERN_INFO "%s: i2c eeprom %02x:", dev->name, i);
		prपूर्णांकk(KERN_CONT " %02x", dev->eedata[i]);
		अगर ((dev->eedata[i] >= ' ') && (dev->eedata[i] <= 'z'))
			bytes[i%16] = dev->eedata[i];
		अन्यथा
			bytes[i%16] = '.';

		i++;

		अगर (0 == (i % 16)) अणु
			bytes[16] = '\0';
			prपूर्णांकk(KERN_CONT "  %s\n", bytes);
		पूर्ण
	पूर्ण
	अगर (0 != (i%16)) अणु
		bytes[i%16] = '\0';
		क्रम (i %= 16; i < 16; i++)
			prपूर्णांकk(KERN_CONT "   ");
		prपूर्णांकk(KERN_CONT "  %s\n", bytes);
	पूर्ण

	वापस 0;

noeeprom:
	prपूर्णांकk(KERN_INFO "%s: Huh, no eeprom present (err=%d)?\n",
	       dev->name, rc);
	वापस -EINVAL;
पूर्ण

/* ----------------------------------------------------------- */

/*
 * functionality()
 */
अटल u32 functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm पंचांग6000_algo = अणु
	.master_xfer   = पंचांग6000_i2c_xfer,
	.functionality = functionality,
पूर्ण;

/* ----------------------------------------------------------- */

/*
 * पंचांग6000_i2c_रेजिस्टर()
 * रेजिस्टर i2c bus
 */
पूर्णांक पंचांग6000_i2c_रेजिस्टर(काष्ठा पंचांग6000_core *dev)
अणु
	पूर्णांक rc;

	dev->i2c_adap.owner = THIS_MODULE;
	dev->i2c_adap.algo = &पंचांग6000_algo;
	dev->i2c_adap.dev.parent = &dev->udev->dev;
	strscpy(dev->i2c_adap.name, dev->name, माप(dev->i2c_adap.name));
	dev->i2c_adap.algo_data = dev;
	i2c_set_adapdata(&dev->i2c_adap, &dev->v4l2_dev);
	rc = i2c_add_adapter(&dev->i2c_adap);
	अगर (rc)
		वापस rc;

	dev->i2c_client.adapter = &dev->i2c_adap;
	strscpy(dev->i2c_client.name, "tm6000 internal", I2C_NAME_SIZE);
	पंचांग6000_i2c_eeprom(dev);

	वापस 0;
पूर्ण

/*
 * पंचांग6000_i2c_unरेजिस्टर()
 * unरेजिस्टर i2c_bus
 */
पूर्णांक पंचांग6000_i2c_unरेजिस्टर(काष्ठा पंचांग6000_core *dev)
अणु
	i2c_del_adapter(&dev->i2c_adap);
	वापस 0;
पूर्ण
