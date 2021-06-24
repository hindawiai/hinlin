<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Hauppauge HD PVR USB driver
 *
 * Copyright (C) 2008      Janne Grunau (j@jannau.net)
 *
 * IR device registration code is
 * Copyright (C) 2010	Andy Walls <awalls@md.metrocast.net>
 */

#अगर IS_ENABLED(CONFIG_I2C)

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश "hdpvr.h"

#घोषणा CTRL_READ_REQUEST	0xb8
#घोषणा CTRL_WRITE_REQUEST	0x38

#घोषणा REQTYPE_I2C_READ	0xb1
#घोषणा REQTYPE_I2C_WRITE	0xb0
#घोषणा REQTYPE_I2C_WRITE_STATT	0xd0

#घोषणा Z8F0811_IR_TX_I2C_ADDR	0x70
#घोषणा Z8F0811_IR_RX_I2C_ADDR	0x71


काष्ठा i2c_client *hdpvr_रेजिस्टर_ir_i2c(काष्ठा hdpvr_device *dev)
अणु
	काष्ठा IR_i2c_init_data *init_data = &dev->ir_i2c_init_data;
	काष्ठा i2c_board_info info = अणु
		I2C_BOARD_INFO("ir_z8f0811_hdpvr", Z8F0811_IR_RX_I2C_ADDR),
	पूर्ण;

	/* Our शेष inक्रमmation क्रम ir-kbd-i2c.c to use */
	init_data->ir_codes = RC_MAP_HAUPPAUGE;
	init_data->पूर्णांकernal_get_key_func = IR_KBD_GET_KEY_HAUP_XVR;
	init_data->type = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RC6_MCE |
			  RC_PROTO_BIT_RC6_6A_32;
	init_data->name = "HD-PVR";
	init_data->polling_पूर्णांकerval = 405; /* ms, duplicated from Winकरोws */
	info.platक्रमm_data = init_data;

	वापस i2c_new_client_device(&dev->i2c_adapter, &info);
पूर्ण

अटल पूर्णांक hdpvr_i2c_पढ़ो(काष्ठा hdpvr_device *dev, पूर्णांक bus,
			  अचिन्हित अक्षर addr, अक्षर *wdata, पूर्णांक wlen,
			  अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर ((len > माप(dev->i2c_buf)) || (wlen > माप(dev->i2c_buf)))
		वापस -EINVAL;

	अगर (wlen) अणु
		स_नकल(dev->i2c_buf, wdata, wlen);
		ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
				      REQTYPE_I2C_WRITE, CTRL_WRITE_REQUEST,
				      (bus << 8) | addr, 0, dev->i2c_buf,
				      wlen, 1000);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
			      REQTYPE_I2C_READ, CTRL_READ_REQUEST,
			      (bus << 8) | addr, 0, dev->i2c_buf, len, 1000);

	अगर (ret == len) अणु
		स_नकल(data, dev->i2c_buf, len);
		ret = 0;
	पूर्ण अन्यथा अगर (ret >= 0)
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक hdpvr_i2c_ग_लिखो(काष्ठा hdpvr_device *dev, पूर्णांक bus,
			   अचिन्हित अक्षर addr, अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (len > माप(dev->i2c_buf))
		वापस -EINVAL;

	स_नकल(dev->i2c_buf, data, len);
	ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			      REQTYPE_I2C_WRITE, CTRL_WRITE_REQUEST,
			      (bus << 8) | addr, 0, dev->i2c_buf, len, 1000);

	अगर (ret < 0)
		वापस ret;

	ret = usb_control_msg(dev->udev, usb_rcvctrlpipe(dev->udev, 0),
			      REQTYPE_I2C_WRITE_STATT, CTRL_READ_REQUEST,
			      0, 0, dev->i2c_buf, 2, 1000);

	अगर ((ret == 2) && (dev->i2c_buf[1] == (len - 1)))
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक hdpvr_transfer(काष्ठा i2c_adapter *i2c_adapter, काष्ठा i2c_msg *msgs,
			  पूर्णांक num)
अणु
	काष्ठा hdpvr_device *dev = i2c_get_adapdata(i2c_adapter);
	पूर्णांक retval = 0, addr;

	mutex_lock(&dev->i2c_mutex);

	addr = msgs[0].addr << 1;

	अगर (num == 1) अणु
		अगर (msgs[0].flags & I2C_M_RD)
			retval = hdpvr_i2c_पढ़ो(dev, 1, addr, शून्य, 0,
						msgs[0].buf, msgs[0].len);
		अन्यथा
			retval = hdpvr_i2c_ग_लिखो(dev, 1, addr, msgs[0].buf,
						 msgs[0].len);
	पूर्ण अन्यथा अगर (num == 2) अणु
		अगर (msgs[0].addr != msgs[1].addr) अणु
			v4l2_warn(&dev->v4l2_dev, "refusing 2-phase i2c xfer with conflicting target addresses\n");
			retval = -EINVAL;
			जाओ out;
		पूर्ण

		अगर ((msgs[0].flags & I2C_M_RD) || !(msgs[1].flags & I2C_M_RD)) अणु
			v4l2_warn(&dev->v4l2_dev, "refusing complex xfer with r0=%d, r1=%d\n",
				  msgs[0].flags & I2C_M_RD,
				  msgs[1].flags & I2C_M_RD);
			retval = -EINVAL;
			जाओ out;
		पूर्ण

		/*
		 * Write followed by atomic पढ़ो is the only complex xfer that
		 * we actually support here.
		 */
		retval = hdpvr_i2c_पढ़ो(dev, 1, addr, msgs[0].buf, msgs[0].len,
					msgs[1].buf, msgs[1].len);
	पूर्ण अन्यथा अणु
		v4l2_warn(&dev->v4l2_dev, "refusing %d-phase i2c xfer\n", num);
	पूर्ण

out:
	mutex_unlock(&dev->i2c_mutex);

	वापस retval ? retval : num;
पूर्ण

अटल u32 hdpvr_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm hdpvr_algo = अणु
	.master_xfer   = hdpvr_transfer,
	.functionality = hdpvr_functionality,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter hdpvr_i2c_adapter_ढाँचा = अणु
	.name   = "Hauppauge HD PVR I2C",
	.owner  = THIS_MODULE,
	.algo   = &hdpvr_algo,
पूर्ण;

अटल पूर्णांक hdpvr_activate_ir(काष्ठा hdpvr_device *dev)
अणु
	अक्षर buffer[2];

	mutex_lock(&dev->i2c_mutex);

	hdpvr_i2c_पढ़ो(dev, 0, 0x54, शून्य, 0, buffer, 1);

	buffer[0] = 0;
	buffer[1] = 0x8;
	hdpvr_i2c_ग_लिखो(dev, 1, 0x54, buffer, 2);

	buffer[1] = 0x18;
	hdpvr_i2c_ग_लिखो(dev, 1, 0x54, buffer, 2);

	mutex_unlock(&dev->i2c_mutex);

	वापस 0;
पूर्ण

पूर्णांक hdpvr_रेजिस्टर_i2c_adapter(काष्ठा hdpvr_device *dev)
अणु
	hdpvr_activate_ir(dev);

	dev->i2c_adapter = hdpvr_i2c_adapter_ढाँचा;
	dev->i2c_adapter.dev.parent = &dev->udev->dev;

	i2c_set_adapdata(&dev->i2c_adapter, dev);

	वापस i2c_add_adapter(&dev->i2c_adapter);
पूर्ण

#पूर्ण_अगर
