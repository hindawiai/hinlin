<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// handle au0828 IR remotes via linux kernel input layer.
//
// Copyright (c) 2014 Mauro Carvalho Chehab <mchehab@samsung.com>
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Based on em28xx-input.c.

#समावेश "au0828.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <media/rc-core.h>

अटल पूर्णांक disable_ir;
module_param(disable_ir,        पूर्णांक, 0444);
MODULE_PARM_DESC(disable_ir, "disable infrared remote support");

काष्ठा au0828_rc अणु
	काष्ठा au0828_dev *dev;
	काष्ठा rc_dev *rc;
	अक्षर name[32];
	अक्षर phys[32];

	/* poll decoder */
	पूर्णांक polling;
	काष्ठा delayed_work work;

	/* i2c slave address of बाह्यal device (अगर used) */
	u16 i2c_dev_addr;

	पूर्णांक  (*get_key_i2c)(काष्ठा au0828_rc *ir);
पूर्ण;

/*
 * AU8522 has a builtin IR receiver. Add functions to get IR from it
 */

अटल पूर्णांक au8522_rc_ग_लिखो(काष्ठा au0828_rc *ir, u16 reg, u8 data)
अणु
	पूर्णांक rc;
	अक्षर buf[] = अणु (reg >> 8) | 0x80, reg & 0xff, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = ir->i2c_dev_addr, .flags = 0,
			       .buf = buf, .len = माप(buf) पूर्ण;

	rc = i2c_transfer(ir->dev->i2c_client.adapter, &msg, 1);

	अगर (rc < 0)
		वापस rc;

	वापस (rc == 1) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक au8522_rc_पढ़ो(काष्ठा au0828_rc *ir, u16 reg, पूर्णांक val,
				 अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक rc;
	अक्षर obuf[3];
	काष्ठा i2c_msg msg[2] = अणु अणु .addr = ir->i2c_dev_addr, .flags = 0,
				    .buf = obuf, .len = 2 पूर्ण,
				  अणु .addr = ir->i2c_dev_addr, .flags = I2C_M_RD,
				    .buf = buf, .len = size पूर्ण पूर्ण;

	obuf[0] = 0x40 | reg >> 8;
	obuf[1] = reg & 0xff;
	अगर (val >= 0) अणु
		obuf[2] = val;
		msg[0].len++;
	पूर्ण

	rc = i2c_transfer(ir->dev->i2c_client.adapter, msg, 2);

	अगर (rc < 0)
		वापस rc;

	वापस (rc == 2) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक au8522_rc_anकरोr(काष्ठा au0828_rc *ir, u16 reg, u8 mask, u8 value)
अणु
	पूर्णांक rc;
	अक्षर buf, oldbuf;

	rc = au8522_rc_पढ़ो(ir, reg, -1, &buf, 1);
	अगर (rc < 0)
		वापस rc;

	oldbuf = buf;
	buf = (buf & ~mask) | (value & mask);

	/* Nothing to करो, just वापस */
	अगर (buf == oldbuf)
		वापस 0;

	वापस au8522_rc_ग_लिखो(ir, reg, buf);
पूर्ण

#घोषणा au8522_rc_set(ir, reg, bit) au8522_rc_anकरोr(ir, (reg), (bit), (bit))
#घोषणा au8522_rc_clear(ir, reg, bit) au8522_rc_anकरोr(ir, (reg), (bit), 0)

/* Remote Controller समय units */

#घोषणा AU8522_UNIT		200 /* us */
#घोषणा NEC_START_SPACE		(4500 / AU8522_UNIT)
#घोषणा NEC_START_PULSE		(563 * 16)
#घोषणा RC5_START_SPACE		(4 * AU8522_UNIT)
#घोषणा RC5_START_PULSE		889

अटल पूर्णांक au0828_get_key_au8522(काष्ठा au0828_rc *ir)
अणु
	अचिन्हित अक्षर buf[40];
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	पूर्णांक i, j, rc;
	पूर्णांक prv_bit, bit, width;
	bool first = true;

	/* करो nothing अगर device is disconnected */
	अगर (test_bit(DEV_DISCONNECTED, &ir->dev->dev_state))
		वापस 0;

	/* Check IR पूर्णांक */
	rc = au8522_rc_पढ़ो(ir, 0xe1, -1, buf, 1);
	अगर (rc < 0 || !(buf[0] & (1 << 4))) अणु
		/* Be sure that IR is enabled */
		au8522_rc_set(ir, 0xe0, 1 << 4);
		वापस 0;
	पूर्ण

	/* Something arrived. Get the data */
	rc = au8522_rc_पढ़ो(ir, 0xe3, 0x11, buf, माप(buf));


	अगर (rc < 0)
		वापस rc;

	/* Disable IR */
	au8522_rc_clear(ir, 0xe0, 1 << 4);

	/* Enable IR */
	au8522_rc_set(ir, 0xe0, 1 << 4);

	dprपूर्णांकk(16, "RC data received: %*ph\n", 40, buf);

	prv_bit = (buf[0] >> 7) & 0x01;
	width = 0;
	क्रम (i = 0; i < माप(buf); i++) अणु
		क्रम (j = 7; j >= 0; j--) अणु
			bit = (buf[i] >> j) & 0x01;
			अगर (bit == prv_bit) अणु
				width++;
				जारी;
			पूर्ण

			/*
			 * Fix an au8522 bug: the first pulse event
			 * is lost. So, we need to fake it, based on the
			 * protocol. That means that not all raw decoders
			 * will work, as we need to add a hack क्रम each
			 * protocol, based on the first space.
			 * So, we only support RC5 and NEC.
			 */

			अगर (first) अणु
				first = false;

				rawir.pulse = true;
				अगर (width > NEC_START_SPACE - 2 &&
				    width < NEC_START_SPACE + 2) अणु
					/* NEC protocol */
					rawir.duration = NEC_START_PULSE;
					dprपूर्णांकk(16, "Storing NEC start %s with duration %d",
						rawir.pulse ? "pulse" : "space",
						rawir.duration);
				पूर्ण अन्यथा अणु
					/* RC5 protocol */
					rawir.duration = RC5_START_PULSE;
					dprपूर्णांकk(16, "Storing RC5 start %s with duration %d",
						rawir.pulse ? "pulse" : "space",
						rawir.duration);
				पूर्ण
				ir_raw_event_store(ir->rc, &rawir);
			पूर्ण

			rawir.pulse = prv_bit ? false : true;
			rawir.duration = AU8522_UNIT * width;
			dprपूर्णांकk(16, "Storing %s with duration %d",
				rawir.pulse ? "pulse" : "space",
				rawir.duration);
			ir_raw_event_store(ir->rc, &rawir);

			width = 1;
			prv_bit = bit;
		पूर्ण
	पूर्ण

	rawir.pulse = prv_bit ? false : true;
	rawir.duration = AU8522_UNIT * width;
	dprपूर्णांकk(16, "Storing end %s with duration %d",
		rawir.pulse ? "pulse" : "space",
		rawir.duration);
	ir_raw_event_store(ir->rc, &rawir);

	ir_raw_event_handle(ir->rc);

	वापस 1;
पूर्ण

/*
 * Generic IR code
 */

अटल व्योम au0828_rc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा au0828_rc *ir = container_of(work, काष्ठा au0828_rc, work.work);
	पूर्णांक rc;

	rc = ir->get_key_i2c(ir);
	अगर (rc < 0)
		pr_info("Error while getting RC scancode\n");

	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(ir->polling));
पूर्ण

अटल पूर्णांक au0828_rc_start(काष्ठा rc_dev *rc)
अणु
	काष्ठा au0828_rc *ir = rc->priv;

	INIT_DELAYED_WORK(&ir->work, au0828_rc_work);

	/* Enable IR */
	au8522_rc_set(ir, 0xe0, 1 << 4);

	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(ir->polling));

	वापस 0;
पूर्ण

अटल व्योम au0828_rc_stop(काष्ठा rc_dev *rc)
अणु
	काष्ठा au0828_rc *ir = rc->priv;

	cancel_delayed_work_sync(&ir->work);

	/* करो nothing अगर device is disconnected */
	अगर (!test_bit(DEV_DISCONNECTED, &ir->dev->dev_state)) अणु
		/* Disable IR */
		au8522_rc_clear(ir, 0xe0, 1 << 4);
	पूर्ण
पूर्ण

अटल पूर्णांक au0828_probe_i2c_ir(काष्ठा au0828_dev *dev)
अणु
	पूर्णांक i = 0;
	अटल स्थिर अचिन्हित लघु addr_list[] = अणु
		 0x47, I2C_CLIENT_END
	पूर्ण;

	जबतक (addr_list[i] != I2C_CLIENT_END) अणु
		अगर (i2c_probe_func_quick_पढ़ो(dev->i2c_client.adapter,
					      addr_list[i]) == 1)
			वापस addr_list[i];
		i++;
	पूर्ण

	वापस -ENODEV;
पूर्ण

पूर्णांक au0828_rc_रेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_rc *ir;
	काष्ठा rc_dev *rc;
	पूर्णांक err = -ENOMEM;
	u16 i2c_rc_dev_addr = 0;

	अगर (!dev->board.has_ir_i2c || disable_ir)
		वापस 0;

	i2c_rc_dev_addr = au0828_probe_i2c_ir(dev);
	अगर (!i2c_rc_dev_addr)
		वापस -ENODEV;

	ir = kzalloc(माप(*ir), GFP_KERNEL);
	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!ir || !rc)
		जाओ error;

	/* record handles to ourself */
	ir->dev = dev;
	dev->ir = ir;
	ir->rc = rc;

	rc->priv = ir;
	rc->खोलो = au0828_rc_start;
	rc->बंद = au0828_rc_stop;

	अगर (dev->board.has_ir_i2c) अणु	/* बाह्यal i2c device */
		चयन (dev->boardnr) अणु
		हाल AU0828_BOARD_HAUPPAUGE_HVR950Q:
			rc->map_name = RC_MAP_HAUPPAUGE;
			ir->get_key_i2c = au0828_get_key_au8522;
			अवरोध;
		शेष:
			err = -ENODEV;
			जाओ error;
		पूर्ण

		ir->i2c_dev_addr = i2c_rc_dev_addr;
	पूर्ण

	/* This is how often we ask the chip क्रम IR inक्रमmation */
	ir->polling = 100; /* ms */

	/* init input device */
	snम_लिखो(ir->name, माप(ir->name), "au0828 IR (%s)",
		 dev->board.name);

	usb_make_path(dev->usbdev, ir->phys, माप(ir->phys));
	strlcat(ir->phys, "/input0", माप(ir->phys));

	rc->device_name = ir->name;
	rc->input_phys = ir->phys;
	rc->input_id.bustype = BUS_USB;
	rc->input_id.version = 1;
	rc->input_id.venकरोr = le16_to_cpu(dev->usbdev->descriptor.idVenकरोr);
	rc->input_id.product = le16_to_cpu(dev->usbdev->descriptor.idProduct);
	rc->dev.parent = &dev->usbdev->dev;
	rc->driver_name = "au0828-input";
	rc->allowed_protocols = RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX |
				RC_PROTO_BIT_NEC32 | RC_PROTO_BIT_RC5;

	/* all करोne */
	err = rc_रेजिस्टर_device(rc);
	अगर (err)
		जाओ error;

	pr_info("Remote controller %s initialized\n", ir->name);

	वापस 0;

error:
	dev->ir = शून्य;
	rc_मुक्त_device(rc);
	kमुक्त(ir);
	वापस err;
पूर्ण

व्योम au0828_rc_unरेजिस्टर(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_rc *ir = dev->ir;

	/* skip detach on non attached boards */
	अगर (!ir)
		वापस;

	rc_unरेजिस्टर_device(ir->rc);

	/* करोne */
	kमुक्त(ir);
	dev->ir = शून्य;
पूर्ण

पूर्णांक au0828_rc_suspend(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_rc *ir = dev->ir;

	अगर (!ir)
		वापस 0;

	pr_info("Stopping RC\n");

	cancel_delayed_work_sync(&ir->work);

	/* Disable IR */
	au8522_rc_clear(ir, 0xe0, 1 << 4);

	वापस 0;
पूर्ण

पूर्णांक au0828_rc_resume(काष्ठा au0828_dev *dev)
अणु
	काष्ठा au0828_rc *ir = dev->ir;

	अगर (!ir)
		वापस 0;

	pr_info("Restarting RC\n");

	/* Enable IR */
	au8522_rc_set(ir, 0xe0, 1 << 4);

	schedule_delayed_work(&ir->work, msecs_to_jअगरfies(ir->polling));

	वापस 0;
पूर्ण
