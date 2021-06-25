<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 *	Based on Steven Toth <stoth@linuxtv.org> cx23885 driver
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश "cx25821.h"

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "enable debug messages [i2c]");

अटल अचिन्हित पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan, "scan i2c bus at insmod time");

#घोषणा dprपूर्णांकk(level, fmt, arg...)					\
करो अणु									\
	अगर (i2c_debug >= level)						\
		prपूर्णांकk(KERN_DEBUG "%s/0: " fmt, dev->name, ##arg);	\
पूर्ण जबतक (0)

#घोषणा I2C_WAIT_DELAY 32
#घोषणा I2C_WAIT_RETRY 64

#घोषणा I2C_EXTEND  (1 << 3)
#घोषणा I2C_NOSTOP  (1 << 4)

अटल अंतरभूत पूर्णांक i2c_slave_did_ack(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा cx25821_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx25821_dev *dev = bus->dev;
	वापस cx_पढ़ो(bus->reg_stat) & 0x01;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_busy(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा cx25821_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx25821_dev *dev = bus->dev;
	वापस cx_पढ़ो(bus->reg_stat) & 0x02 ? 1 : 0;
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

अटल पूर्णांक i2c_sendbytes(काष्ठा i2c_adapter *i2c_adap,
			 स्थिर काष्ठा i2c_msg *msg, पूर्णांक joined_rlen)
अणु
	काष्ठा cx25821_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx25821_dev *dev = bus->dev;
	u32 wdata, addr, ctrl;
	पूर्णांक retval, cnt;

	अगर (joined_rlen)
		dprपूर्णांकk(1, "%s(msg->wlen=%d, nextmsg->rlen=%d)\n", __func__,
			msg->len, joined_rlen);
	अन्यथा
		dprपूर्णांकk(1, "%s(msg->len=%d)\n", __func__, msg->len);

	/* Deal with i2c probe functions with zero payload */
	अगर (msg->len == 0) अणु
		cx_ग_लिखो(bus->reg_addr, msg->addr << 25);
		cx_ग_लिखो(bus->reg_ctrl, bus->i2c_period | (1 << 2));

		अगर (!i2c_रुको_करोne(i2c_adap))
			वापस -EIO;

		अगर (!i2c_slave_did_ack(i2c_adap))
			वापस -EIO;

		dprपूर्णांकk(1, "%s(): returns 0\n", __func__);
		वापस 0;
	पूर्ण

	/* dev, reg + first byte */
	addr = (msg->addr << 25) | msg->buf[0];
	wdata = msg->buf[0];

	ctrl = bus->i2c_period | (1 << 12) | (1 << 2);

	अगर (msg->len > 1)
		ctrl |= I2C_NOSTOP | I2C_EXTEND;
	अन्यथा अगर (joined_rlen)
		ctrl |= I2C_NOSTOP;

	cx_ग_लिखो(bus->reg_addr, addr);
	cx_ग_लिखो(bus->reg_wdata, wdata);
	cx_ग_लिखो(bus->reg_ctrl, ctrl);

	retval = i2c_रुको_करोne(i2c_adap);
	अगर (retval < 0)
		जाओ err;

	अगर (retval == 0)
		जाओ eio;

	अगर (i2c_debug) अणु
		अगर (!(ctrl & I2C_NOSTOP))
			prपूर्णांकk(" >\n");
	पूर्ण

	क्रम (cnt = 1; cnt < msg->len; cnt++) अणु
		/* following bytes */
		wdata = msg->buf[cnt];
		ctrl = bus->i2c_period | (1 << 12) | (1 << 2);

		अगर (cnt < msg->len - 1)
			ctrl |= I2C_NOSTOP | I2C_EXTEND;
		अन्यथा अगर (joined_rlen)
			ctrl |= I2C_NOSTOP;

		cx_ग_लिखो(bus->reg_addr, addr);
		cx_ग_लिखो(bus->reg_wdata, wdata);
		cx_ग_लिखो(bus->reg_ctrl, ctrl);

		retval = i2c_रुको_करोne(i2c_adap);
		अगर (retval < 0)
			जाओ err;

		अगर (retval == 0)
			जाओ eio;

		अगर (i2c_debug) अणु
			dprपूर्णांकk(1, " %02x", msg->buf[cnt]);
			अगर (!(ctrl & I2C_NOSTOP))
				dprपूर्णांकk(1, " >\n");
		पूर्ण
	पूर्ण

	वापस msg->len;

eio:
	retval = -EIO;
err:
	अगर (i2c_debug)
		pr_err(" ERR: %d\n", retval);
	वापस retval;
पूर्ण

अटल पूर्णांक i2c_पढ़ोbytes(काष्ठा i2c_adapter *i2c_adap,
			 स्थिर काष्ठा i2c_msg *msg, पूर्णांक joined)
अणु
	काष्ठा cx25821_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx25821_dev *dev = bus->dev;
	u32 ctrl, cnt;
	पूर्णांक retval;

	अगर (i2c_debug && !joined)
		dprपूर्णांकk(1, "6-%s(msg->len=%d)\n", __func__, msg->len);

	/* Deal with i2c probe functions with zero payload */
	अगर (msg->len == 0) अणु
		cx_ग_लिखो(bus->reg_addr, msg->addr << 25);
		cx_ग_लिखो(bus->reg_ctrl, bus->i2c_period | (1 << 2) | 1);
		अगर (!i2c_रुको_करोne(i2c_adap))
			वापस -EIO;
		अगर (!i2c_slave_did_ack(i2c_adap))
			वापस -EIO;

		dprपूर्णांकk(1, "%s(): returns 0\n", __func__);
		वापस 0;
	पूर्ण

	अगर (i2c_debug) अणु
		अगर (joined)
			dprपूर्णांकk(1, " R");
		अन्यथा
			dprपूर्णांकk(1, " <R %02x", (msg->addr << 1) + 1);
	पूर्ण

	क्रम (cnt = 0; cnt < msg->len; cnt++) अणु

		ctrl = bus->i2c_period | (1 << 12) | (1 << 2) | 1;

		अगर (cnt < msg->len - 1)
			ctrl |= I2C_NOSTOP | I2C_EXTEND;

		cx_ग_लिखो(bus->reg_addr, msg->addr << 25);
		cx_ग_लिखो(bus->reg_ctrl, ctrl);

		retval = i2c_रुको_करोne(i2c_adap);
		अगर (retval < 0)
			जाओ err;
		अगर (retval == 0)
			जाओ eio;
		msg->buf[cnt] = cx_पढ़ो(bus->reg_rdata) & 0xff;

		अगर (i2c_debug) अणु
			dprपूर्णांकk(1, " %02x", msg->buf[cnt]);
			अगर (!(ctrl & I2C_NOSTOP))
				dprपूर्णांकk(1, " >\n");
		पूर्ण
	पूर्ण

	वापस msg->len;
eio:
	retval = -EIO;
err:
	अगर (i2c_debug)
		pr_err(" ERR: %d\n", retval);
	वापस retval;
पूर्ण

अटल पूर्णांक i2c_xfer(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा cx25821_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx25821_dev *dev = bus->dev;
	पूर्णांक i, retval = 0;

	dprपूर्णांकk(1, "%s(num = %d)\n", __func__, num);

	क्रम (i = 0; i < num; i++) अणु
		dprपूर्णांकk(1, "%s(num = %d) addr = 0x%02x  len = 0x%x\n",
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


अटल u32 cx25821_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL | I2C_FUNC_I2C | I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_READ_WORD_DATA | I2C_FUNC_SMBUS_WRITE_WORD_DATA;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cx25821_i2c_algo_ढाँचा = अणु
	.master_xfer = i2c_xfer,
	.functionality = cx25821_functionality,
#अगर_घोषित NEED_ALGO_CONTROL
	.algo_control = dummy_algo_control,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter cx25821_i2c_adap_ढाँचा = अणु
	.name = "cx25821",
	.owner = THIS_MODULE,
	.algo = &cx25821_i2c_algo_ढाँचा,
पूर्ण;

अटल स्थिर काष्ठा i2c_client cx25821_i2c_client_ढाँचा = अणु
	.name = "cx25821 internal",
पूर्ण;

/* init + रेजिस्टर i2c adapter */
पूर्णांक cx25821_i2c_रेजिस्टर(काष्ठा cx25821_i2c *bus)
अणु
	काष्ठा cx25821_dev *dev = bus->dev;

	dprपूर्णांकk(1, "%s(bus = %d)\n", __func__, bus->nr);

	bus->i2c_adap = cx25821_i2c_adap_ढाँचा;
	bus->i2c_client = cx25821_i2c_client_ढाँचा;
	bus->i2c_adap.dev.parent = &dev->pci->dev;

	strscpy(bus->i2c_adap.name, bus->dev->name, माप(bus->i2c_adap.name));

	bus->i2c_adap.algo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, &dev->v4l2_dev);
	i2c_add_adapter(&bus->i2c_adap);

	bus->i2c_client.adapter = &bus->i2c_adap;

	/* set up the I2c */
	bus->i2c_client.addr = (0x88 >> 1);

	वापस bus->i2c_rc;
पूर्ण

पूर्णांक cx25821_i2c_unरेजिस्टर(काष्ठा cx25821_i2c *bus)
अणु
	i2c_del_adapter(&bus->i2c_adap);
	वापस 0;
पूर्ण

#अगर 0 /* Currently unused */
अटल व्योम cx25821_av_clk(काष्ठा cx25821_dev *dev, पूर्णांक enable)
अणु
	/* ग_लिखो 0 to bus 2 addr 0x144 via i2x_xfer() */
	अक्षर buffer[3];
	काष्ठा i2c_msg msg;
	dprपूर्णांकk(1, "%s(enabled = %d)\n", __func__, enable);

	/* Register 0x144 */
	buffer[0] = 0x01;
	buffer[1] = 0x44;
	अगर (enable == 1)
		buffer[2] = 0x05;
	अन्यथा
		buffer[2] = 0x00;

	msg.addr = 0x44;
	msg.flags = I2C_M_TEN;
	msg.len = 3;
	msg.buf = buffer;

	i2c_xfer(&dev->i2c_bus[0].i2c_adap, &msg, 1);
पूर्ण
#पूर्ण_अगर

पूर्णांक cx25821_i2c_पढ़ो(काष्ठा cx25821_i2c *bus, u16 reg_addr, पूर्णांक *value)
अणु
	काष्ठा i2c_client *client = &bus->i2c_client;
	पूर्णांक v = 0;
	u8 addr[2] = अणु 0, 0 पूर्ण;
	u8 buf[4] = अणु 0, 0, 0, 0 पूर्ण;

	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 2,
			.buf = addr,
		पूर्ण, अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 4,
			.buf = buf,
		पूर्ण
	पूर्ण;

	addr[0] = (reg_addr >> 8);
	addr[1] = (reg_addr & 0xff);
	msgs[0].addr = 0x44;
	msgs[1].addr = 0x44;

	i2c_xfer(client->adapter, msgs, 2);

	v = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];
	*value = v;

	वापस v;
पूर्ण

पूर्णांक cx25821_i2c_ग_लिखो(काष्ठा cx25821_i2c *bus, u16 reg_addr, पूर्णांक value)
अणु
	काष्ठा i2c_client *client = &bus->i2c_client;
	पूर्णांक retval = 0;
	u8 buf[6] = अणु 0, 0, 0, 0, 0, 0 पूर्ण;

	काष्ठा i2c_msg msgs[1] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 6,
			.buf = buf,
		पूर्ण
	पूर्ण;

	buf[0] = reg_addr >> 8;
	buf[1] = reg_addr & 0xff;
	buf[5] = (value >> 24) & 0xff;
	buf[4] = (value >> 16) & 0xff;
	buf[3] = (value >> 8) & 0xff;
	buf[2] = value & 0xff;
	client->flags = 0;
	msgs[0].addr = 0x44;

	retval = i2c_xfer(client->adapter, msgs, 1);

	वापस retval;
पूर्ण
