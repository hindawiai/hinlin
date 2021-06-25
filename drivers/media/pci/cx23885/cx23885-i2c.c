<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "cx23885.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

#समावेश <media/v4l2-common.h>

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "enable debug messages [i2c]");

अटल अचिन्हित पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan, "scan i2c bus at insmod time");

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (i2c_debug >= level)\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: i2c:" fmt), \
			__func__, ##arg); \
	पूर्ण जबतक (0)

#घोषणा I2C_WAIT_DELAY 32
#घोषणा I2C_WAIT_RETRY 64

#घोषणा I2C_EXTEND  (1 << 3)
#घोषणा I2C_NOSTOP  (1 << 4)

अटल अंतरभूत पूर्णांक i2c_slave_did_ack(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा cx23885_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx23885_dev *dev = bus->dev;
	वापस cx_पढ़ो(bus->reg_stat) & 0x01;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_is_busy(काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा cx23885_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx23885_dev *dev = bus->dev;
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
	काष्ठा cx23885_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx23885_dev *dev = bus->dev;
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
			वापस -ENXIO;

		dprपूर्णांकk(1, "%s() returns 0\n", __func__);
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

	अगर (!i2c_रुको_करोne(i2c_adap))
		जाओ eio;
	अगर (i2c_debug) अणु
		prपूर्णांकk(KERN_DEBUG " <W %02x %02x", msg->addr << 1, msg->buf[0]);
		अगर (!(ctrl & I2C_NOSTOP))
			pr_cont(" >\n");
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

		अगर (!i2c_रुको_करोne(i2c_adap))
			जाओ eio;
		अगर (i2c_debug) अणु
			pr_cont(" %02x", msg->buf[cnt]);
			अगर (!(ctrl & I2C_NOSTOP))
				pr_cont(" >\n");
		पूर्ण
	पूर्ण
	वापस msg->len;

 eio:
	retval = -EIO;
	अगर (i2c_debug)
		pr_err(" ERR: %d\n", retval);
	वापस retval;
पूर्ण

अटल पूर्णांक i2c_पढ़ोbytes(काष्ठा i2c_adapter *i2c_adap,
			 स्थिर काष्ठा i2c_msg *msg, पूर्णांक joined)
अणु
	काष्ठा cx23885_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx23885_dev *dev = bus->dev;
	u32 ctrl, cnt;
	पूर्णांक retval;


	अगर (i2c_debug && !joined)
		dprपूर्णांकk(1, "%s(msg->len=%d)\n", __func__, msg->len);

	/* Deal with i2c probe functions with zero payload */
	अगर (msg->len == 0) अणु
		cx_ग_लिखो(bus->reg_addr, msg->addr << 25);
		cx_ग_लिखो(bus->reg_ctrl, bus->i2c_period | (1 << 2) | 1);
		अगर (!i2c_रुको_करोne(i2c_adap))
			वापस -EIO;
		अगर (!i2c_slave_did_ack(i2c_adap))
			वापस -ENXIO;


		dprपूर्णांकk(1, "%s() returns 0\n", __func__);
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

		अगर (!i2c_रुको_करोne(i2c_adap))
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
	अगर (i2c_debug)
		pr_err(" ERR: %d\n", retval);
	वापस retval;
पूर्ण

अटल पूर्णांक i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
		    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक i, retval = 0;

	dprपूर्णांकk(1, "%s(num = %d)\n", __func__, num);

	क्रम (i = 0 ; i < num; i++) अणु
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

अटल u32 cx23885_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL | I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cx23885_i2c_algo_ढाँचा = अणु
	.master_xfer	= i2c_xfer,
	.functionality	= cx23885_functionality,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_adapter cx23885_i2c_adap_ढाँचा = अणु
	.name              = "cx23885",
	.owner             = THIS_MODULE,
	.algo              = &cx23885_i2c_algo_ढाँचा,
पूर्ण;

अटल स्थिर काष्ठा i2c_client cx23885_i2c_client_ढाँचा = अणु
	.name	= "cx23885 internal",
पूर्ण;

अटल अक्षर *i2c_devs[128] = अणु
	[0x10 >> 1] = "tda10048",
	[0x12 >> 1] = "dib7000pc",
	[0x1c >> 1] = "lgdt3303",
	[0x80 >> 1] = "cs3308",
	[0x82 >> 1] = "cs3308",
	[0x86 >> 1] = "tda9887",
	[0x32 >> 1] = "cx24227",
	[0x88 >> 1] = "cx25837",
	[0x84 >> 1] = "tda8295",
	[0x98 >> 1] = "flatiron",
	[0xa0 >> 1] = "eeprom",
	[0xc0 >> 1] = "tuner/mt2131/tda8275",
	[0xc2 >> 1] = "tuner/mt2131/tda8275/xc5000/xc3028",
	[0xc8 >> 1] = "tuner/xc3028L",
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
		pr_info("%s: i2c scan: found device @ 0x%04x  [%s]\n",
		       name, i, i2c_devs[i] ? i2c_devs[i] : "???");
	पूर्ण
पूर्ण

/* init + रेजिस्टर i2c adapter */
पूर्णांक cx23885_i2c_रेजिस्टर(काष्ठा cx23885_i2c *bus)
अणु
	काष्ठा cx23885_dev *dev = bus->dev;

	dprपूर्णांकk(1, "%s(bus = %d)\n", __func__, bus->nr);

	bus->i2c_adap = cx23885_i2c_adap_ढाँचा;
	bus->i2c_client = cx23885_i2c_client_ढाँचा;
	bus->i2c_adap.dev.parent = &dev->pci->dev;

	strscpy(bus->i2c_adap.name, bus->dev->name,
		माप(bus->i2c_adap.name));

	bus->i2c_adap.algo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, &dev->v4l2_dev);
	i2c_add_adapter(&bus->i2c_adap);

	bus->i2c_client.adapter = &bus->i2c_adap;

	अगर (0 == bus->i2c_rc) अणु
		dprपूर्णांकk(1, "%s: i2c bus %d registered\n", dev->name, bus->nr);
		अगर (i2c_scan) अणु
			pr_info("%s: scan bus %d:\n",
					dev->name, bus->nr);
			करो_i2c_scan(dev->name, &bus->i2c_client);
		पूर्ण
	पूर्ण अन्यथा
		pr_warn("%s: i2c bus %d register FAILED\n",
			dev->name, bus->nr);

	/* Instantiate the IR receiver device, अगर present */
	अगर (0 == bus->i2c_rc) अणु
		काष्ठा i2c_board_info info;
		अटल स्थिर अचिन्हित लघु addr_list[] = अणु
			0x6b, I2C_CLIENT_END
		पूर्ण;

		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "ir_video", I2C_NAME_SIZE);
		/* Use quick पढ़ो command क्रम probe, some IR chips करोn't
		 * support ग_लिखोs */
		i2c_new_scanned_device(&bus->i2c_adap, &info, addr_list,
				       i2c_probe_func_quick_पढ़ो);
	पूर्ण

	वापस bus->i2c_rc;
पूर्ण

पूर्णांक cx23885_i2c_unरेजिस्टर(काष्ठा cx23885_i2c *bus)
अणु
	i2c_del_adapter(&bus->i2c_adap);
	वापस 0;
पूर्ण

व्योम cx23885_av_clk(काष्ठा cx23885_dev *dev, पूर्णांक enable)
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

	i2c_xfer(&dev->i2c_bus[2].i2c_adap, &msg, 1);
पूर्ण
