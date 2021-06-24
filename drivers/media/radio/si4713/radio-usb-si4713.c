<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013 Cisco Systems, Inc. and/or its affiliates.
 * All rights reserved.
 */

/* kernel includes */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/input.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>
/* V4l includes */
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <linux/platक्रमm_data/media/si4713.h>

#समावेश "si4713.h"

/* driver and module definitions */
MODULE_AUTHOR("Dinesh Ram <dinesh.ram@cern.ch>");
MODULE_DESCRIPTION("Si4713 FM Transmitter USB driver");
MODULE_LICENSE("GPL v2");

/* The Device announces itself as Cygnal Integrated Products, Inc. */
#घोषणा USB_SI4713_VENDOR		0x10c4
#घोषणा USB_SI4713_PRODUCT		0x8244

#घोषणा BUFFER_LENGTH			64
#घोषणा USB_TIMEOUT			1000
#घोषणा USB_RESP_TIMEOUT		50000

/* USB Device ID List */
अटल स्थिर काष्ठा usb_device_id usb_si4713_usb_device_table[] = अणु
	अणुUSB_DEVICE_AND_INTERFACE_INFO(USB_SI4713_VENDOR, USB_SI4713_PRODUCT,
							USB_CLASS_HID, 0, 0) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_si4713_usb_device_table);

काष्ठा si4713_usb_device अणु
	काष्ठा usb_device	*usbdev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;
	काष्ठा video_device	vdev;
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा v4l2_subdev	*v4l2_subdev;
	काष्ठा mutex		lock;
	काष्ठा i2c_adapter	i2c_adapter;

	u8			*buffer;
पूर्ण;

अटल अंतरभूत काष्ठा si4713_usb_device *to_si4713_dev(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा si4713_usb_device, v4l2_dev);
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *v)
अणु
	काष्ठा si4713_usb_device *radio = video_drvdata(file);

	strscpy(v->driver, "radio-usb-si4713", माप(v->driver));
	strscpy(v->card, "Si4713 FM Transmitter", माप(v->card));
	usb_make_path(radio->usbdev, v->bus_info, माप(v->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_modulator(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_modulator *vm)
अणु
	काष्ठा si4713_usb_device *radio = video_drvdata(file);

	वापस v4l2_subdev_call(radio->v4l2_subdev, tuner, g_modulator, vm);
पूर्ण

अटल पूर्णांक vidioc_s_modulator(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_modulator *vm)
अणु
	काष्ठा si4713_usb_device *radio = video_drvdata(file);

	वापस v4l2_subdev_call(radio->v4l2_subdev, tuner, s_modulator, vm);
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा si4713_usb_device *radio = video_drvdata(file);

	वापस v4l2_subdev_call(radio->v4l2_subdev, tuner, s_frequency, vf);
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_frequency *vf)
अणु
	काष्ठा si4713_usb_device *radio = video_drvdata(file);

	वापस v4l2_subdev_call(radio->v4l2_subdev, tuner, g_frequency, vf);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops usb_si4713_ioctl_ops = अणु
	.vidioc_querycap	  = vidioc_querycap,
	.vidioc_g_modulator	  = vidioc_g_modulator,
	.vidioc_s_modulator	  = vidioc_s_modulator,
	.vidioc_g_frequency	  = vidioc_g_frequency,
	.vidioc_s_frequency	  = vidioc_s_frequency,
	.vidioc_log_status	  = v4l2_ctrl_log_status,
	.vidioc_subscribe_event   = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/* File प्रणाली पूर्णांकerface */
अटल स्थिर काष्ठा v4l2_file_operations usb_si4713_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो           = v4l2_fh_खोलो,
	.release        = v4l2_fh_release,
	.poll           = v4l2_ctrl_poll,
	.unlocked_ioctl	= video_ioctl2,
पूर्ण;

अटल व्योम usb_si4713_video_device_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा si4713_usb_device *radio = to_si4713_dev(v4l2_dev);
	काष्ठा i2c_adapter *adapter = &radio->i2c_adapter;

	i2c_del_adapter(adapter);
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
	kमुक्त(radio->buffer);
	kमुक्त(radio);
पूर्ण

/*
 * This command sequence emulates the behaviour of the Winकरोws driver.
 * The काष्ठाure of these commands was determined by snअगरfing the
 * usb traffic of the device during startup.
 * Most likely, these commands make some queries to the device.
 * Commands are sent to enquire parameters like the bus mode,
 * component revision, boot mode, the device serial number etc.
 *
 * These commands are necessary to be sent in this order during startup.
 * The device fails to घातerup अगर these commands are not sent.
 *
 * The complete list of startup commands is given in the start_seq table below.
 */
अटल पूर्णांक si4713_send_startup_command(काष्ठा si4713_usb_device *radio)
अणु
	अचिन्हित दीर्घ until_jअगरfies = jअगरfies + usecs_to_jअगरfies(USB_RESP_TIMEOUT) + 1;
	u8 *buffer = radio->buffer;
	पूर्णांक retval;

	/* send the command */
	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
					0x09, 0x21, 0x033f, 0, radio->buffer,
					BUFFER_LENGTH, USB_TIMEOUT);
	अगर (retval < 0)
		वापस retval;

	क्रम (;;) अणु
		/* receive the response */
		retval = usb_control_msg(radio->usbdev, usb_rcvctrlpipe(radio->usbdev, 0),
				0x01, 0xa1, 0x033f, 0, radio->buffer,
				BUFFER_LENGTH, USB_TIMEOUT);
		अगर (retval < 0)
			वापस retval;
		अगर (!radio->buffer[1]) अणु
			/* USB traffic snअगरfing showed that some commands require
			 * additional checks. */
			चयन (buffer[1]) अणु
			हाल 0x32:
				अगर (radio->buffer[2] == 0)
					वापस 0;
				अवरोध;
			हाल 0x14:
			हाल 0x12:
				अगर (radio->buffer[2] & SI4713_CTS)
					वापस 0;
				अवरोध;
			हाल 0x06:
				अगर ((radio->buffer[2] & SI4713_CTS) && radio->buffer[9] == 0x08)
					वापस 0;
				अवरोध;
			शेष:
				वापस 0;
			पूर्ण
		पूर्ण
		अगर (समय_is_beक्रमe_jअगरfies(until_jअगरfies))
			वापस -EIO;
		msleep(3);
	पूर्ण

	वापस retval;
पूर्ण

काष्ठा si4713_start_seq_table अणु
	पूर्णांक len;
	u8 payload[8];
पूर्ण;

/*
 * Some of the startup commands that could be recognized are :
 * (0x03): Get serial number of the board (Response : CB000-00-00)
 * (0x06, 0x03, 0x03, 0x08, 0x01, 0x0f) : Get Component revision
 */
अटल स्थिर काष्ठा si4713_start_seq_table start_seq[] = अणु

	अणु 1, अणु 0x03 पूर्ण पूर्ण,
	अणु 2, अणु 0x32, 0x7f पूर्ण पूर्ण,
	अणु 6, अणु 0x06, 0x03, 0x03, 0x08, 0x01, 0x0f पूर्ण पूर्ण,
	अणु 2, अणु 0x14, 0x02 पूर्ण पूर्ण,
	अणु 2, अणु 0x09, 0x90 पूर्ण पूर्ण,
	अणु 3, अणु 0x08, 0x90, 0xfa पूर्ण पूर्ण,
	अणु 2, अणु 0x36, 0x01 पूर्ण पूर्ण,
	अणु 2, अणु 0x05, 0x03 पूर्ण पूर्ण,
	अणु 7, अणु 0x06, 0x00, 0x06, 0x0e, 0x01, 0x0f, 0x05 पूर्ण पूर्ण,
	अणु 1, अणु 0x12 पूर्ण पूर्ण,
	/* Commands that are sent after pressing the 'Initialize'
		button in the winकरोws application */
	अणु 1, अणु 0x03 पूर्ण पूर्ण,
	अणु 1, अणु 0x01 पूर्ण पूर्ण,
	अणु 2, अणु 0x09, 0x90 पूर्ण पूर्ण,
	अणु 3, अणु 0x08, 0x90, 0xfa पूर्ण पूर्ण,
	अणु 1, अणु 0x34 पूर्ण पूर्ण,
	अणु 2, अणु 0x35, 0x01 पूर्ण पूर्ण,
	अणु 2, अणु 0x36, 0x01 पूर्ण पूर्ण,
	अणु 2, अणु 0x30, 0x09 पूर्ण पूर्ण,
	अणु 4, अणु 0x30, 0x06, 0x00, 0xe2 पूर्ण पूर्ण,
	अणु 3, अणु 0x31, 0x01, 0x30 पूर्ण पूर्ण,
	अणु 3, अणु 0x31, 0x04, 0x09 पूर्ण पूर्ण,
	अणु 2, अणु 0x05, 0x02 पूर्ण पूर्ण,
	अणु 6, अणु 0x06, 0x03, 0x03, 0x08, 0x01, 0x0f पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक si4713_start_seq(काष्ठा si4713_usb_device *radio)
अणु
	पूर्णांक retval = 0;
	पूर्णांक i;

	radio->buffer[0] = 0x3f;

	क्रम (i = 0; i < ARRAY_SIZE(start_seq); i++) अणु
		पूर्णांक len = start_seq[i].len;
		स्थिर u8 *payload = start_seq[i].payload;

		स_नकल(radio->buffer + 1, payload, len);
		स_रखो(radio->buffer + len + 1, 0, BUFFER_LENGTH - 1 - len);
		retval = si4713_send_startup_command(radio);
	पूर्ण

	वापस retval;
पूर्ण

अटल काष्ठा i2c_board_info si4713_board_info = अणु
	I2C_BOARD_INFO("si4713", SI4713_I2C_ADDR_BUSEN_HIGH),
पूर्ण;

काष्ठा si4713_command_table अणु
	पूर्णांक command_id;
	u8 payload[8];
पूर्ण;

/*
 * Structure of a command :
 *	Byte 1 : 0x3f (always)
 *	Byte 2 : 0x06 (send a command)
 *	Byte 3 : Unknown
 *	Byte 4 : Number of arguments + 1 (क्रम the command byte)
 *	Byte 5 : Number of response bytes
 */
अटल काष्ठा si4713_command_table command_table[] = अणु

	अणु SI4713_CMD_POWER_UP,		अणु 0x00, SI4713_PWUP_NARGS + 1, SI4713_PWUP_NRESPपूर्ण पूर्ण,
	अणु SI4713_CMD_GET_REV,		अणु 0x03, 0x01, SI4713_GETREV_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_POWER_DOWN,	अणु 0x00, 0x01, SI4713_PWDN_NRESPपूर्ण पूर्ण,
	अणु SI4713_CMD_SET_PROPERTY,	अणु 0x00, SI4713_SET_PROP_NARGS + 1, SI4713_SET_PROP_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_GET_PROPERTY,	अणु 0x00, SI4713_GET_PROP_NARGS + 1, SI4713_GET_PROP_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_TX_TUNE_FREQ,	अणु 0x03, SI4713_TXFREQ_NARGS + 1, SI4713_TXFREQ_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_TX_TUNE_POWER,	अणु 0x03, SI4713_TXPWR_NARGS + 1, SI4713_TXPWR_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_TX_TUNE_MEASURE,	अणु 0x03, SI4713_TXMEA_NARGS + 1, SI4713_TXMEA_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_TX_TUNE_STATUS,	अणु 0x00, SI4713_TXSTATUS_NARGS + 1, SI4713_TXSTATUS_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_TX_ASQ_STATUS,	अणु 0x03, SI4713_ASQSTATUS_NARGS + 1, SI4713_ASQSTATUS_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_GET_INT_STATUS,	अणु 0x03, 0x01, SI4713_GET_STATUS_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_TX_RDS_BUFF,	अणु 0x03, SI4713_RDSBUFF_NARGS + 1, SI4713_RDSBUFF_NRESP पूर्ण पूर्ण,
	अणु SI4713_CMD_TX_RDS_PS,		अणु 0x00, SI4713_RDSPS_NARGS + 1, SI4713_RDSPS_NRESP पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक send_command(काष्ठा si4713_usb_device *radio, u8 *payload, अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक retval;

	radio->buffer[0] = 0x3f;
	radio->buffer[1] = 0x06;

	स_नकल(radio->buffer + 2, payload, 3);
	स_नकल(radio->buffer + 5, data, len);
	स_रखो(radio->buffer + 5 + len, 0, BUFFER_LENGTH - 5 - len);

	/* send the command */
	retval = usb_control_msg(radio->usbdev, usb_sndctrlpipe(radio->usbdev, 0),
					0x09, 0x21, 0x033f, 0, radio->buffer,
					BUFFER_LENGTH, USB_TIMEOUT);

	वापस retval < 0 ? retval : 0;
पूर्ण

अटल पूर्णांक si4713_i2c_पढ़ो(काष्ठा si4713_usb_device *radio, अक्षर *data, पूर्णांक len)
अणु
	अचिन्हित दीर्घ until_jअगरfies = jअगरfies + usecs_to_jअगरfies(USB_RESP_TIMEOUT) + 1;
	पूर्णांक retval;

	/* receive the response */
	क्रम (;;) अणु
		retval = usb_control_msg(radio->usbdev,
					usb_rcvctrlpipe(radio->usbdev, 0),
					0x01, 0xa1, 0x033f, 0, radio->buffer,
					BUFFER_LENGTH, USB_TIMEOUT);
		अगर (retval < 0)
			वापस retval;

		/*
		 * Check that we get a valid reply back (buffer[1] == 0) and
		 * that CTS is set beक्रमe वापसing, otherwise we रुको and try
		 * again. The i2c driver also करोes the CTS check, but the समयouts
		 * used there are much too small क्रम this USB driver, so we रुको
		 * क्रम it here.
		 */
		अगर (radio->buffer[1] == 0 && (radio->buffer[2] & SI4713_CTS)) अणु
			स_नकल(data, radio->buffer + 2, len);
			वापस 0;
		पूर्ण
		अगर (समय_is_beक्रमe_jअगरfies(until_jअगरfies)) अणु
			/* Zero the status value, ensuring CTS isn't set */
			data[0] = 0;
			वापस 0;
		पूर्ण
		msleep(3);
	पूर्ण
पूर्ण

अटल पूर्णांक si4713_i2c_ग_लिखो(काष्ठा si4713_usb_device *radio, अक्षर *data, पूर्णांक len)
अणु
	पूर्णांक retval = -EINVAL;
	पूर्णांक i;

	अगर (len > BUFFER_LENGTH - 5)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(command_table); i++) अणु
		अगर (data[0] == command_table[i].command_id)
			retval = send_command(radio, command_table[i].payload,
						data, len);
	पूर्ण

	वापस retval < 0 ? retval : 0;
पूर्ण

अटल पूर्णांक si4713_transfer(काष्ठा i2c_adapter *i2c_adapter,
				काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा si4713_usb_device *radio = i2c_get_adapdata(i2c_adapter);
	पूर्णांक retval = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD)
			retval = si4713_i2c_पढ़ो(radio, msgs[i].buf, msgs[i].len);
		अन्यथा
			retval = si4713_i2c_ग_लिखो(radio, msgs[i].buf, msgs[i].len);
		अगर (retval)
			अवरोध;
	पूर्ण

	वापस retval ? retval : num;
पूर्ण

अटल u32 si4713_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm si4713_algo = अणु
	.master_xfer   = si4713_transfer,
	.functionality = si4713_functionality,
पूर्ण;

/* This name value shows up in the sysfs filename associated
		with this I2C adapter */
अटल स्थिर काष्ठा i2c_adapter si4713_i2c_adapter_ढाँचा = अणु
	.name   = "si4713-i2c",
	.owner  = THIS_MODULE,
	.algo   = &si4713_algo,
पूर्ण;

अटल पूर्णांक si4713_रेजिस्टर_i2c_adapter(काष्ठा si4713_usb_device *radio)
अणु
	radio->i2c_adapter = si4713_i2c_adapter_ढाँचा;
	/* set up sysfs linkage to our parent device */
	radio->i2c_adapter.dev.parent = &radio->usbdev->dev;
	i2c_set_adapdata(&radio->i2c_adapter, radio);

	वापस i2c_add_adapter(&radio->i2c_adapter);
पूर्ण

/* check अगर the device is present and रेजिस्टर with v4l and usb अगर it is */
अटल पूर्णांक usb_si4713_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा si4713_usb_device *radio;
	काष्ठा i2c_adapter *adapter;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक retval;

	dev_info(&पूर्णांकf->dev, "Si4713 development board discovered: (%04X:%04X)\n",
			id->idVenकरोr, id->idProduct);

	/* Initialize local device काष्ठाure */
	radio = kzalloc(माप(काष्ठा si4713_usb_device), GFP_KERNEL);
	अगर (radio)
		radio->buffer = kदो_स्मृति(BUFFER_LENGTH, GFP_KERNEL);

	अगर (!radio || !radio->buffer) अणु
		dev_err(&पूर्णांकf->dev, "kmalloc for si4713_usb_device failed\n");
		kमुक्त(radio);
		वापस -ENOMEM;
	पूर्ण

	mutex_init(&radio->lock);

	radio->usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	radio->पूर्णांकf = पूर्णांकf;
	usb_set_पूर्णांकfdata(पूर्णांकf, &radio->v4l2_dev);

	retval = si4713_start_seq(radio);
	अगर (retval < 0)
		जाओ err_v4l2;

	retval = v4l2_device_रेजिस्टर(&पूर्णांकf->dev, &radio->v4l2_dev);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't register v4l2_device\n");
		जाओ err_v4l2;
	पूर्ण

	retval = si4713_रेजिस्टर_i2c_adapter(radio);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "could not register i2c device\n");
		जाओ err_i2cdev;
	पूर्ण

	adapter = &radio->i2c_adapter;
	sd = v4l2_i2c_new_subdev_board(&radio->v4l2_dev, adapter,
					  &si4713_board_info, शून्य);
	radio->v4l2_subdev = sd;
	अगर (!sd) अणु
		dev_err(&पूर्णांकf->dev, "cannot get v4l2 subdevice\n");
		retval = -ENODEV;
		जाओ del_adapter;
	पूर्ण

	radio->vdev.ctrl_handler = sd->ctrl_handler;
	radio->v4l2_dev.release = usb_si4713_video_device_release;
	strscpy(radio->vdev.name, radio->v4l2_dev.name,
		माप(radio->vdev.name));
	radio->vdev.v4l2_dev = &radio->v4l2_dev;
	radio->vdev.fops = &usb_si4713_fops;
	radio->vdev.ioctl_ops = &usb_si4713_ioctl_ops;
	radio->vdev.lock = &radio->lock;
	radio->vdev.release = video_device_release_empty;
	radio->vdev.vfl_dir = VFL_सूची_TX;
	radio->vdev.device_caps = V4L2_CAP_MODULATOR | V4L2_CAP_RDS_OUTPUT;

	video_set_drvdata(&radio->vdev, radio);

	retval = video_रेजिस्टर_device(&radio->vdev, VFL_TYPE_RADIO, -1);
	अगर (retval < 0) अणु
		dev_err(&पूर्णांकf->dev, "could not register video device\n");
		जाओ del_adapter;
	पूर्ण

	dev_info(&पूर्णांकf->dev, "V4L2 device registered as %s\n",
			video_device_node_name(&radio->vdev));

	वापस 0;

del_adapter:
	i2c_del_adapter(adapter);
err_i2cdev:
	v4l2_device_unरेजिस्टर(&radio->v4l2_dev);
err_v4l2:
	kमुक्त(radio->buffer);
	kमुक्त(radio);
	वापस retval;
पूर्ण

अटल व्योम usb_si4713_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा si4713_usb_device *radio = to_si4713_dev(usb_get_पूर्णांकfdata(पूर्णांकf));

	dev_info(&पूर्णांकf->dev, "Si4713 development board now disconnected\n");

	mutex_lock(&radio->lock);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	video_unरेजिस्टर_device(&radio->vdev);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->lock);
	v4l2_device_put(&radio->v4l2_dev);
पूर्ण

/* USB subप्रणाली पूर्णांकerface */
अटल काष्ठा usb_driver usb_si4713_driver = अणु
	.name			= "radio-usb-si4713",
	.probe			= usb_si4713_probe,
	.disconnect		= usb_si4713_disconnect,
	.id_table		= usb_si4713_usb_device_table,
पूर्ण;

module_usb_driver(usb_si4713_driver);
