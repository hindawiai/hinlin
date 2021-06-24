<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   cx231xx-i2c.c - driver क्रम Conexant Cx23100/101/102 USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
		Based on em28xx driver
		Based on Cx23885 driver

 */

#समावेश "cx231xx.h"
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/tuner.h>


/* ----------------------------------------------------------- */

अटल अचिन्हित पूर्णांक i2c_scan;
module_param(i2c_scan, पूर्णांक, 0444);
MODULE_PARM_DESC(i2c_scan, "scan i2c bus at insmod time");

अटल अचिन्हित पूर्णांक i2c_debug;
module_param(i2c_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(i2c_debug, "enable debug messages [i2c]");

#घोषणा dprपूर्णांकk1(lvl, fmt, args...)			\
करो अणु							\
	अगर (i2c_debug >= lvl) अणु				\
		prपूर्णांकk(fmt, ##args);			\
		पूर्ण					\
पूर्ण जबतक (0)

#घोषणा dprपूर्णांकk2(lvl, fmt, args...)			\
करो अणु							\
	अगर (i2c_debug >= lvl) अणु				\
		prपूर्णांकk(KERN_DEBUG "%s at %s: " fmt,	\
		       dev->name, __func__ , ##args);	\
      पूर्ण							\
पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक get_real_i2c_port(काष्ठा cx231xx *dev, पूर्णांक bus_nr)
अणु
	अगर (bus_nr == 1)
		वापस dev->port_3_चयन_enabled ? I2C_1_MUX_3 : I2C_1_MUX_1;
	वापस bus_nr;
पूर्ण

अटल अंतरभूत bool is_tuner(काष्ठा cx231xx *dev, काष्ठा cx231xx_i2c *bus,
			स्थिर काष्ठा i2c_msg *msg, पूर्णांक tuner_type)
अणु
	पूर्णांक i2c_port = get_real_i2c_port(dev, bus->nr);

	अगर (i2c_port != dev->board.tuner_i2c_master)
		वापस false;

	अगर (msg->addr != dev->board.tuner_addr)
		वापस false;

	अगर (dev->tuner_type != tuner_type)
		वापस false;

	वापस true;
पूर्ण

/*
 * cx231xx_i2c_send_bytes()
 */
अटल पूर्णांक cx231xx_i2c_send_bytes(काष्ठा i2c_adapter *i2c_adap,
				  स्थिर काष्ठा i2c_msg *msg)
अणु
	काष्ठा cx231xx_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx231xx *dev = bus->dev;
	काष्ठा cx231xx_i2c_xfer_data req_data;
	पूर्णांक status = 0;
	u16 size = 0;
	u8 loop = 0;
	u8 saddr_len = 1;
	u8 *buf_ptr = शून्य;
	u16 saddr = 0;
	u8 need_gpio = 0;

	अगर (is_tuner(dev, bus, msg, TUNER_XC5000)) अणु
		size = msg->len;

		अगर (size == 2) अणु	/* रेजिस्टर ग_लिखो sub addr */
			/* Just writing sub address will cause problem
			* to XC5000. So ignore the request */
			वापस 0;
		पूर्ण अन्यथा अगर (size == 4) अणु	/* रेजिस्टर ग_लिखो with sub addr */
			अगर (msg->len >= 2)
				saddr = msg->buf[0] << 8 | msg->buf[1];
			अन्यथा अगर (msg->len == 1)
				saddr = msg->buf[0];

			चयन (saddr) अणु
			हाल 0x0000:	/* start tuner calibration mode */
				need_gpio = 1;
				/* FW Loading is करोne */
				dev->xc_fw_load_करोne = 1;
				अवरोध;
			हाल 0x000D:	/* Set संकेत source */
			हाल 0x0001:	/* Set TV standard - Video */
			हाल 0x0002:	/* Set TV standard - Audio */
			हाल 0x0003:	/* Set RF Frequency */
				need_gpio = 1;
				अवरोध;
			शेष:
				अगर (dev->xc_fw_load_करोne)
					need_gpio = 1;
				अवरोध;
			पूर्ण

			अगर (need_gpio) अणु
				dprपूर्णांकk1(1,
				"GPIO WRITE: addr 0x%x, len %d, saddr 0x%x\n",
				msg->addr, msg->len, saddr);

				वापस dev->cx231xx_gpio_i2c_ग_लिखो(dev,
								   msg->addr,
								   msg->buf,
								   msg->len);
			पूर्ण
		पूर्ण

		/* special हाल क्रम Xc5000 tuner हाल */
		saddr_len = 1;

		/* adjust the length to correct length */
		size -= saddr_len;
		buf_ptr = (u8 *) (msg->buf + 1);

		करो अणु
			/* prepare xfer_data काष्ठा */
			req_data.dev_addr = msg->addr;
			req_data.direction = msg->flags;
			req_data.saddr_len = saddr_len;
			req_data.saddr_dat = msg->buf[0];
			req_data.buf_size = size > 16 ? 16 : size;
			req_data.p_buffer = (u8 *) (buf_ptr + loop * 16);

			bus->i2c_nostop = (size > 16) ? 1 : 0;
			bus->i2c_reserve = (loop == 0) ? 0 : 1;

			/* usb send command */
			status = dev->cx231xx_send_usb_command(bus, &req_data);
			loop++;

			अगर (size >= 16)
				size -= 16;
			अन्यथा
				size = 0;

		पूर्ण जबतक (size > 0);

		bus->i2c_nostop = 0;
		bus->i2c_reserve = 0;

	पूर्ण अन्यथा अणु		/* regular हाल */

		/* prepare xfer_data काष्ठा */
		req_data.dev_addr = msg->addr;
		req_data.direction = msg->flags;
		req_data.saddr_len = 0;
		req_data.saddr_dat = 0;
		req_data.buf_size = msg->len;
		req_data.p_buffer = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &req_data);
	पूर्ण

	वापस status < 0 ? status : 0;
पूर्ण

/*
 * cx231xx_i2c_recv_bytes()
 * पढ़ो a byte from the i2c device
 */
अटल पूर्णांक cx231xx_i2c_recv_bytes(काष्ठा i2c_adapter *i2c_adap,
				  स्थिर काष्ठा i2c_msg *msg)
अणु
	काष्ठा cx231xx_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx231xx *dev = bus->dev;
	काष्ठा cx231xx_i2c_xfer_data req_data;
	पूर्णांक status = 0;
	u16 saddr = 0;
	u8 need_gpio = 0;

	अगर (is_tuner(dev, bus, msg, TUNER_XC5000)) अणु
		अगर (msg->len == 2)
			saddr = msg->buf[0] << 8 | msg->buf[1];
		अन्यथा अगर (msg->len == 1)
			saddr = msg->buf[0];

		अगर (dev->xc_fw_load_करोne) अणु

			चयन (saddr) अणु
			हाल 0x0009:	/* BUSY check */
				dprपूर्णांकk1(1,
				"GPIO R E A D: Special case BUSY check \n");
				/*Try पढ़ो BUSY रेजिस्टर, just set it to zero*/
				msg->buf[0] = 0;
				अगर (msg->len == 2)
					msg->buf[1] = 0;
				वापस 0;
			हाल 0x0004:	/* पढ़ो Lock status */
				need_gpio = 1;
				अवरोध;

			पूर्ण

			अगर (need_gpio) अणु
				/* this is a special हाल to handle Xceive tuner
				घड़ी stretch issue with gpio based I2C */

				dprपूर्णांकk1(1,
				"GPIO R E A D: addr 0x%x, len %d, saddr 0x%x\n",
				msg->addr, msg->len,
				msg->buf[0] << 8 | msg->buf[1]);

				status =
				    dev->cx231xx_gpio_i2c_ग_लिखो(dev, msg->addr,
								msg->buf,
								msg->len);
				status =
				    dev->cx231xx_gpio_i2c_पढ़ो(dev, msg->addr,
							       msg->buf,
							       msg->len);
				वापस status;
			पूर्ण
		पूर्ण

		/* prepare xfer_data काष्ठा */
		req_data.dev_addr = msg->addr;
		req_data.direction = msg->flags;
		req_data.saddr_len = msg->len;
		req_data.saddr_dat = msg->buf[0] << 8 | msg->buf[1];
		req_data.buf_size = msg->len;
		req_data.p_buffer = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &req_data);

	पूर्ण अन्यथा अणु

		/* prepare xfer_data काष्ठा */
		req_data.dev_addr = msg->addr;
		req_data.direction = msg->flags;
		req_data.saddr_len = 0;
		req_data.saddr_dat = 0;
		req_data.buf_size = msg->len;
		req_data.p_buffer = msg->buf;

		/* usb send command */
		status = dev->cx231xx_send_usb_command(bus, &req_data);
	पूर्ण

	वापस status < 0 ? status : 0;
पूर्ण

/*
 * cx231xx_i2c_recv_bytes_with_saddr()
 * पढ़ो a byte from the i2c device
 */
अटल पूर्णांक cx231xx_i2c_recv_bytes_with_saddr(काष्ठा i2c_adapter *i2c_adap,
					     स्थिर काष्ठा i2c_msg *msg1,
					     स्थिर काष्ठा i2c_msg *msg2)
अणु
	काष्ठा cx231xx_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx231xx *dev = bus->dev;
	काष्ठा cx231xx_i2c_xfer_data req_data;
	पूर्णांक status = 0;
	u16 saddr = 0;
	u8 need_gpio = 0;

	अगर (msg1->len == 2)
		saddr = msg1->buf[0] << 8 | msg1->buf[1];
	अन्यथा अगर (msg1->len == 1)
		saddr = msg1->buf[0];

	अगर (is_tuner(dev, bus, msg2, TUNER_XC5000)) अणु
		अगर ((msg2->len < 16)) अणु

			dprपूर्णांकk1(1,
			"i2c_read: addr 0x%x, len %d, saddr 0x%x, len %d\n",
			msg2->addr, msg2->len, saddr, msg1->len);

			चयन (saddr) अणु
			हाल 0x0008:	/* पढ़ो FW load status */
				need_gpio = 1;
				अवरोध;
			हाल 0x0004:	/* पढ़ो Lock status */
				need_gpio = 1;
				अवरोध;
			पूर्ण

			अगर (need_gpio) अणु
				status =
				    dev->cx231xx_gpio_i2c_ग_लिखो(dev, msg1->addr,
								msg1->buf,
								msg1->len);
				status =
				    dev->cx231xx_gpio_i2c_पढ़ो(dev, msg2->addr,
							       msg2->buf,
							       msg2->len);
				वापस status;
			पूर्ण
		पूर्ण
	पूर्ण

	/* prepare xfer_data काष्ठा */
	req_data.dev_addr = msg2->addr;
	req_data.direction = msg2->flags;
	req_data.saddr_len = msg1->len;
	req_data.saddr_dat = saddr;
	req_data.buf_size = msg2->len;
	req_data.p_buffer = msg2->buf;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(bus, &req_data);

	वापस status < 0 ? status : 0;
पूर्ण

/*
 * cx231xx_i2c_check_क्रम_device()
 * check अगर there is a i2c_device at the supplied address
 */
अटल पूर्णांक cx231xx_i2c_check_क्रम_device(काष्ठा i2c_adapter *i2c_adap,
					स्थिर काष्ठा i2c_msg *msg)
अणु
	काष्ठा cx231xx_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx231xx *dev = bus->dev;
	काष्ठा cx231xx_i2c_xfer_data req_data;
	पूर्णांक status = 0;
	u8 buf[1];

	/* prepare xfer_data काष्ठा */
	req_data.dev_addr = msg->addr;
	req_data.direction = I2C_M_RD;
	req_data.saddr_len = 0;
	req_data.saddr_dat = 0;
	req_data.buf_size = 1;
	req_data.p_buffer = buf;

	/* usb send command */
	status = dev->cx231xx_send_usb_command(bus, &req_data);

	वापस status < 0 ? status : 0;
पूर्ण

/*
 * cx231xx_i2c_xfer()
 * the मुख्य i2c transfer function
 */
अटल पूर्णांक cx231xx_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			    काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा cx231xx_i2c *bus = i2c_adap->algo_data;
	काष्ठा cx231xx *dev = bus->dev;
	पूर्णांक addr, rc, i, byte;

	mutex_lock(&dev->i2c_lock);
	क्रम (i = 0; i < num; i++) अणु

		addr = msgs[i].addr;

		dprपूर्णांकk2(2, "%s %s addr=0x%x len=%d:",
			 (msgs[i].flags & I2C_M_RD) ? "read" : "write",
			 i == num - 1 ? "stop" : "nonstop", addr, msgs[i].len);
		अगर (!msgs[i].len) अणु
			/* no len: check only क्रम device presence */
			rc = cx231xx_i2c_check_क्रम_device(i2c_adap, &msgs[i]);
			अगर (rc < 0) अणु
				dprपूर्णांकk2(2, " no device\n");
				mutex_unlock(&dev->i2c_lock);
				वापस rc;
			पूर्ण

		पूर्ण अन्यथा अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो bytes */
			rc = cx231xx_i2c_recv_bytes(i2c_adap, &msgs[i]);
			अगर (i2c_debug >= 2) अणु
				क्रम (byte = 0; byte < msgs[i].len; byte++)
					prपूर्णांकk(KERN_CONT " %02x", msgs[i].buf[byte]);
			पूर्ण
		पूर्ण अन्यथा अगर (i + 1 < num && (msgs[i + 1].flags & I2C_M_RD) &&
			   msgs[i].addr == msgs[i + 1].addr
			   && (msgs[i].len <= 2) && (bus->nr < 3)) अणु
			/* ग_लिखो bytes */
			अगर (i2c_debug >= 2) अणु
				क्रम (byte = 0; byte < msgs[i].len; byte++)
					prपूर्णांकk(KERN_CONT " %02x", msgs[i].buf[byte]);
				prपूर्णांकk(KERN_CONT "\n");
			पूर्ण
			/* पढ़ो bytes */
			dprपूर्णांकk2(2, "plus %s %s addr=0x%x len=%d:",
				(msgs[i+1].flags & I2C_M_RD) ? "read" : "write",
				i+1 == num - 1 ? "stop" : "nonstop", addr, msgs[i+1].len);
			rc = cx231xx_i2c_recv_bytes_with_saddr(i2c_adap,
							       &msgs[i],
							       &msgs[i + 1]);
			अगर (i2c_debug >= 2) अणु
				क्रम (byte = 0; byte < msgs[i+1].len; byte++)
					prपूर्णांकk(KERN_CONT " %02x", msgs[i+1].buf[byte]);
			पूर्ण
			i++;
		पूर्ण अन्यथा अणु
			/* ग_लिखो bytes */
			अगर (i2c_debug >= 2) अणु
				क्रम (byte = 0; byte < msgs[i].len; byte++)
					prपूर्णांकk(KERN_CONT " %02x", msgs[i].buf[byte]);
			पूर्ण
			rc = cx231xx_i2c_send_bytes(i2c_adap, &msgs[i]);
		पूर्ण
		अगर (rc < 0)
			जाओ err;
		अगर (i2c_debug >= 2)
			prपूर्णांकk(KERN_CONT "\n");
	पूर्ण
	mutex_unlock(&dev->i2c_lock);
	वापस num;
err:
	dprपूर्णांकk2(2, " ERROR: %i\n", rc);
	mutex_unlock(&dev->i2c_lock);
	वापस rc;
पूर्ण

/* ----------------------------------------------------------- */

/*
 * functionality()
 */
अटल u32 functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_SMBUS_EMUL | I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cx231xx_algo = अणु
	.master_xfer = cx231xx_i2c_xfer,
	.functionality = functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter cx231xx_adap_ढाँचा = अणु
	.owner = THIS_MODULE,
	.name = "cx231xx",
	.algo = &cx231xx_algo,
पूर्ण;

/* ----------------------------------------------------------- */

/*
 * i2c_devs
 * incomplete list of known devices
 */
अटल स्थिर अक्षर *i2c_devs[128] = अणु
	[0x20 >> 1] = "demod",
	[0x60 >> 1] = "colibri",
	[0x88 >> 1] = "hammerhead",
	[0x8e >> 1] = "CIR",
	[0x32 >> 1] = "GeminiIII",
	[0x02 >> 1] = "Aquarius",
	[0xa0 >> 1] = "eeprom",
	[0xc0 >> 1] = "tuner",
	[0xc2 >> 1] = "tuner",
पूर्ण;

/*
 * cx231xx_करो_i2c_scan()
 * check i2c address range क्रम devices
 */
व्योम cx231xx_करो_i2c_scan(काष्ठा cx231xx *dev, पूर्णांक i2c_port)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक i, rc;
	काष्ठा i2c_adapter *adap;
	काष्ठा i2c_msg msg = अणु
		.flags = I2C_M_RD,
		.len = 1,
		.buf = &buf,
	पूर्ण;

	अगर (!i2c_scan)
		वापस;

	/* Don't generate I2C errors during scan */
	dev->i2c_scan_running = true;
	adap = cx231xx_get_i2c_adap(dev, i2c_port);

	क्रम (i = 0; i < 128; i++) अणु
		msg.addr = i;
		rc = i2c_transfer(adap, &msg, 1);

		अगर (rc < 0)
			जारी;
		dev_info(dev->dev,
			 "i2c scan: found device @ port %d addr 0x%x  [%s]\n",
			 i2c_port,
			 i << 1,
			 i2c_devs[i] ? i2c_devs[i] : "???");
	पूर्ण

	dev->i2c_scan_running = false;
पूर्ण

/*
 * cx231xx_i2c_रेजिस्टर()
 * रेजिस्टर i2c bus
 */
पूर्णांक cx231xx_i2c_रेजिस्टर(काष्ठा cx231xx_i2c *bus)
अणु
	काष्ठा cx231xx *dev = bus->dev;

	अगर (!dev->cx231xx_send_usb_command)
		वापस -EINVAL;

	bus->i2c_adap = cx231xx_adap_ढाँचा;
	bus->i2c_adap.dev.parent = dev->dev;

	snम_लिखो(bus->i2c_adap.name, माप(bus->i2c_adap.name), "%s-%d", bus->dev->name, bus->nr);

	bus->i2c_adap.algo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, &dev->v4l2_dev);
	bus->i2c_rc = i2c_add_adapter(&bus->i2c_adap);

	अगर (0 != bus->i2c_rc)
		dev_warn(dev->dev,
			 "i2c bus %d register FAILED\n", bus->nr);

	वापस bus->i2c_rc;
पूर्ण

/*
 * cx231xx_i2c_unरेजिस्टर()
 * unरेजिस्टर i2c_bus
 */
व्योम cx231xx_i2c_unरेजिस्टर(काष्ठा cx231xx_i2c *bus)
अणु
	अगर (!bus->i2c_rc)
		i2c_del_adapter(&bus->i2c_adap);
पूर्ण

/*
 * cx231xx_i2c_mux_select()
 * चयन i2c master number 1 between port1 and port3
 */
अटल पूर्णांक cx231xx_i2c_mux_select(काष्ठा i2c_mux_core *muxc, u32 chan_id)
अणु
	काष्ठा cx231xx *dev = i2c_mux_priv(muxc);

	वापस cx231xx_enable_i2c_port_3(dev, chan_id);
पूर्ण

पूर्णांक cx231xx_i2c_mux_create(काष्ठा cx231xx *dev)
अणु
	dev->muxc = i2c_mux_alloc(&dev->i2c_bus[1].i2c_adap, dev->dev, 2, 0, 0,
				  cx231xx_i2c_mux_select, शून्य);
	अगर (!dev->muxc)
		वापस -ENOMEM;
	dev->muxc->priv = dev;
	वापस 0;
पूर्ण

पूर्णांक cx231xx_i2c_mux_रेजिस्टर(काष्ठा cx231xx *dev, पूर्णांक mux_no)
अणु
	वापस i2c_mux_add_adapter(dev->muxc,
				   0,
				   mux_no /* chan_id */,
				   0 /* class */);
पूर्ण

व्योम cx231xx_i2c_mux_unरेजिस्टर(काष्ठा cx231xx *dev)
अणु
	i2c_mux_del_adapters(dev->muxc);
पूर्ण

काष्ठा i2c_adapter *cx231xx_get_i2c_adap(काष्ठा cx231xx *dev, पूर्णांक i2c_port)
अणु
	चयन (i2c_port) अणु
	हाल I2C_0:
		वापस &dev->i2c_bus[0].i2c_adap;
	हाल I2C_1:
		वापस &dev->i2c_bus[1].i2c_adap;
	हाल I2C_2:
		वापस &dev->i2c_bus[2].i2c_adap;
	हाल I2C_1_MUX_1:
		वापस dev->muxc->adapter[0];
	हाल I2C_1_MUX_3:
		वापस dev->muxc->adapter[1];
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cx231xx_get_i2c_adap);
