<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
 * USB Driver क्रम ALi m5602 based webcams
 *
 * Copyright (C) 2008 Erik Andrथऊn
 * Copyright (C) 2007 Ilyes Gouta. Based on the m5603x Linux Driver Project.
 * Copyright (C) 2005 m5603x Linux Driver Project <m5602@x3ng.com.br>
 *
 * Portions of code to USB पूर्णांकerface and ALi driver software,
 * Copyright (c) 2006 Willem Duinker
 * v4l2 पूर्णांकerface modeled after the V4L2 driver
 * क्रम SN9C10x PC Camera Controllers
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "m5602_ov9650.h"
#समावेश "m5602_ov7660.h"
#समावेश "m5602_mt9m111.h"
#समावेश "m5602_po1030.h"
#समावेश "m5602_s5k83a.h"
#समावेश "m5602_s5k4aa.h"

/* Kernel module parameters */
पूर्णांक क्रमce_sensor;
अटल bool dump_bridge;
bool dump_sensor;

अटल स्थिर काष्ठा usb_device_id m5602_table[] = अणु
	अणुUSB_DEVICE(0x0402, 0x5602)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, m5602_table);

/* A skeleton used क्रम sending messages to the sensor */
अटल स्थिर अचिन्हित अक्षर sensor_urb_skeleton[] = अणु
	0x23, M5602_XB_GPIO_EN_H, 0x81, 0x06,
	0x23, M5602_XB_MISC_CTRL, 0x81, 0x80,
	0x13, M5602_XB_I2C_DEV_ADDR, 0x81, 0x00,
	0x13, M5602_XB_I2C_REG_ADDR, 0x81, 0x00,
	0x13, M5602_XB_I2C_DATA, 0x81, 0x00,
	0x13, M5602_XB_I2C_CTRL, 0x81, 0x11
पूर्ण;

/* A skeleton used क्रम sending messages to the m5602 bridge */
अटल स्थिर अचिन्हित अक्षर bridge_urb_skeleton[] = अणु
	0x13, 0x00, 0x81, 0x00
पूर्ण;

/* Reads a byte from the m5602 */
पूर्णांक m5602_पढ़ो_bridge(काष्ठा sd *sd, स्थिर u8 address, u8 *i2c_data)
अणु
	पूर्णांक err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	err = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      0x04, 0xc0, 0x14,
			      0x8100 + address, buf,
			      1, M5602_URB_MSG_TIMEOUT);
	*i2c_data = buf[0];

	gspca_dbg(gspca_dev, D_CONF, "Reading bridge register 0x%x containing 0x%x\n",
		  address, *i2c_data);

	/* usb_control_msg(...) वापसs the number of bytes sent upon success,
	mask that and वापस zero instead*/
	वापस (err < 0) ? err : 0;
पूर्ण

/* Writes a byte to the m5602 */
पूर्णांक m5602_ग_लिखो_bridge(काष्ठा sd *sd, स्थिर u8 address, स्थिर u8 i2c_data)
अणु
	पूर्णांक err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	gspca_dbg(gspca_dev, D_CONF, "Writing bridge register 0x%x with 0x%x\n",
		  address, i2c_data);

	स_नकल(buf, bridge_urb_skeleton,
	       माप(bridge_urb_skeleton));
	buf[1] = address;
	buf[3] = i2c_data;

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				0x04, 0x40, 0x19,
				0x0000, buf,
				4, M5602_URB_MSG_TIMEOUT);

	/* usb_control_msg(...) वापसs the number of bytes sent upon success,
	   mask that and वापस zero instead */
	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक m5602_रुको_क्रम_i2c(काष्ठा sd *sd)
अणु
	पूर्णांक err;
	u8 data;

	करो अणु
		err = m5602_पढ़ो_bridge(sd, M5602_XB_I2C_STATUS, &data);
	पूर्ण जबतक ((data & I2C_BUSY) && !err);
	वापस err;
पूर्ण

पूर्णांक m5602_पढ़ो_sensor(काष्ठा sd *sd, स्थिर u8 address,
		       u8 *i2c_data, स्थिर u8 len)
अणु
	पूर्णांक err, i;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) sd;

	अगर (!len || len > sd->sensor->i2c_regW)
		वापस -EINVAL;

	err = m5602_रुको_क्रम_i2c(sd);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_I2C_DEV_ADDR,
				 sd->sensor->i2c_slave_id);
	अगर (err < 0)
		वापस err;

	err = m5602_ग_लिखो_bridge(sd, M5602_XB_I2C_REG_ADDR, address);
	अगर (err < 0)
		वापस err;

	/* Sensors with रेजिस्टरs that are of only
	   one byte width are dअगरferently पढ़ो */

	/* FIXME: This works with the ov9650, but has issues with the po1030 */
	अगर (sd->sensor->i2c_regW == 1) अणु
		err = m5602_ग_लिखो_bridge(sd, M5602_XB_I2C_CTRL, 1);
		अगर (err < 0)
			वापस err;

		err = m5602_ग_लिखो_bridge(sd, M5602_XB_I2C_CTRL, 0x08);
	पूर्ण अन्यथा अणु
		err = m5602_ग_लिखो_bridge(sd, M5602_XB_I2C_CTRL, 0x18 + len);
	पूर्ण

	क्रम (i = 0; (i < len) && !err; i++) अणु
		err = m5602_रुको_क्रम_i2c(sd);
		अगर (err < 0)
			वापस err;

		err = m5602_पढ़ो_bridge(sd, M5602_XB_I2C_DATA, &(i2c_data[i]));

		gspca_dbg(gspca_dev, D_CONF, "Reading sensor register 0x%x containing 0x%x\n",
			  address, *i2c_data);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक m5602_ग_लिखो_sensor(काष्ठा sd *sd, स्थिर u8 address,
			u8 *i2c_data, स्थिर u8 len)
अणु
	पूर्णांक err, i;
	u8 *p;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *) sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	/* No sensor with a data width larger than 16 bits has yet been seen */
	अगर (len > sd->sensor->i2c_regW || !len)
		वापस -EINVAL;

	स_नकल(buf, sensor_urb_skeleton,
	       माप(sensor_urb_skeleton));

	buf[11] = sd->sensor->i2c_slave_id;
	buf[15] = address;

	/* Special हाल larger sensor ग_लिखोs */
	p = buf + 16;

	/* Copy a four byte ग_लिखो sequence क्रम each byte to be written to */
	क्रम (i = 0; i < len; i++) अणु
		स_नकल(p, sensor_urb_skeleton + 16, 4);
		p[3] = i2c_data[i];
		p += 4;
		gspca_dbg(gspca_dev, D_CONF, "Writing sensor register 0x%x with 0x%x\n",
			  address, i2c_data[i]);
	पूर्ण

	/* Copy the tailer */
	स_नकल(p, sensor_urb_skeleton + 20, 4);

	/* Set the total length */
	p[3] = 0x10 + len;

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      0x04, 0x40, 0x19,
			      0x0000, buf,
			      20 + len * 4, M5602_URB_MSG_TIMEOUT);

	वापस (err < 0) ? err : 0;
पूर्ण

/* Dump all the रेजिस्टरs of the m5602 bridge,
   unक्रमtunately this अवरोधs the camera until it's घातer cycled */
अटल व्योम m5602_dump_bridge(काष्ठा sd *sd)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 0x80; i++) अणु
		अचिन्हित अक्षर val = 0;
		m5602_पढ़ो_bridge(sd, i, &val);
		pr_info("ALi m5602 address 0x%x contains 0x%x\n", i, val);
	पूर्ण
	pr_info("Warning: The ALi m5602 webcam probably won't work until it's power cycled\n");
पूर्ण

अटल पूर्णांक m5602_probe_sensor(काष्ठा sd *sd)
अणु
	/* Try the po1030 */
	sd->sensor = &po1030;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	/* Try the mt9m111 sensor */
	sd->sensor = &mt9m111;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	/* Try the s5k4aa */
	sd->sensor = &s5k4aa;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	/* Try the ov9650 */
	sd->sensor = &ov9650;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	/* Try the ov7660 */
	sd->sensor = &ov7660;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	/* Try the s5k83a */
	sd->sensor = &s5k83a;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	/* More sensor probe function goes here */
	pr_info("Failed to find a sensor\n");
	sd->sensor = शून्य;
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक m5602_configure(काष्ठा gspca_dev *gspca_dev,
			   स्थिर काष्ठा usb_device_id *id);

अटल पूर्णांक m5602_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_CONF, "Initializing ALi m5602 webcam\n");
	/* Run the init sequence */
	err = sd->sensor->init(sd);

	वापस err;
पूर्ण

अटल पूर्णांक m5602_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (!sd->sensor->init_controls)
		वापस 0;

	वापस sd->sensor->init_controls(sd);
पूर्ण

अटल पूर्णांक m5602_start_transfer(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	__u8 *buf = sd->gspca_dev.usb_buf;
	पूर्णांक err;

	/* Send start command to the camera */
	स्थिर u8 buffer[4] = अणु0x13, 0xf9, 0x0f, 0x01पूर्ण;

	अगर (sd->sensor->start)
		sd->sensor->start(sd);

	स_नकल(buf, buffer, माप(buffer));
	err = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      0x04, 0x40, 0x19, 0x0000, buf,
			      माप(buffer), M5602_URB_MSG_TIMEOUT);

	gspca_dbg(gspca_dev, D_STREAM, "Transfer started\n");
	वापस (err < 0) ? err : 0;
पूर्ण

अटल व्योम m5602_urb_complete(काष्ठा gspca_dev *gspca_dev,
				u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (len < 6) अणु
		gspca_dbg(gspca_dev, D_PACK, "Packet is less than 6 bytes\n");
		वापस;
	पूर्ण

	/* Frame delimiter: ff xx xx xx ff ff */
	अगर (data[0] == 0xff && data[4] == 0xff && data[5] == 0xff &&
	    data[2] != sd->frame_id) अणु
		gspca_dbg(gspca_dev, D_FRAM, "Frame delimiter detected\n");
		sd->frame_id = data[2];

		/* Remove the extra fluff appended on each header */
		data += 6;
		len -= 6;

		/* Complete the last frame (अगर any) */
		gspca_frame_add(gspca_dev, LAST_PACKET,
				शून्य, 0);
		sd->frame_count++;

		/* Create a new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);

		gspca_dbg(gspca_dev, D_FRAM, "Starting new frame %d\n",
			  sd->frame_count);

	पूर्ण अन्यथा अणु
		पूर्णांक cur_frame_len;

		cur_frame_len = gspca_dev->image_len;
		/* Remove urb header */
		data += 4;
		len -= 4;

		अगर (cur_frame_len + len <= gspca_dev->pixfmt.sizeimage) अणु
			gspca_dbg(gspca_dev, D_FRAM, "Continuing frame %d copying %d bytes\n",
				  sd->frame_count, len);

			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, len);
		पूर्ण अन्यथा अणु
			/* Add the reमुख्यing data up to frame size */
			gspca_frame_add(gspca_dev, INTER_PACKET, data,
				gspca_dev->pixfmt.sizeimage - cur_frame_len);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम m5602_stop_transfer(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Run the sensor specअगरic end transfer sequence */
	अगर (sd->sensor->stop)
		sd->sensor->stop(sd);
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name		= MODULE_NAME,
	.config		= m5602_configure,
	.init		= m5602_init,
	.init_controls	= m5602_init_controls,
	.start		= m5602_start_transfer,
	.stopN		= m5602_stop_transfer,
	.pkt_scan	= m5602_urb_complete
पूर्ण;

/* this function is called at probe समय */
अटल पूर्णांक m5602_configure(काष्ठा gspca_dev *gspca_dev,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;
	पूर्णांक err;

	cam = &gspca_dev->cam;

	अगर (dump_bridge)
		m5602_dump_bridge(sd);

	/* Probe sensor */
	err = m5602_probe_sensor(sd);
	अगर (err)
		जाओ fail;

	वापस 0;

fail:
	gspca_err(gspca_dev, "ALi m5602 webcam failed\n");
	cam->cam_mode = शून्य;
	cam->nmodes = 0;

	वापस err;
पूर्ण

अटल पूर्णांक m5602_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
			       THIS_MODULE);
पूर्ण

अटल व्योम m5602_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gspca_dev *gspca_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (sd->sensor->disconnect)
		sd->sensor->disconnect(sd);

	gspca_disconnect(पूर्णांकf);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name = MODULE_NAME,
	.id_table = m5602_table,
	.probe = m5602_probe,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
	.disconnect = m5602_disconnect
पूर्ण;

module_usb_driver(sd_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
module_param(क्रमce_sensor, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(क्रमce_sensor,
		"forces detection of a sensor, 1 = OV9650, 2 = S5K83A, 3 = S5K4AA, 4 = MT9M111, 5 = PO1030, 6 = OV7660");

module_param(dump_bridge, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dump_bridge, "Dumps all usb bridge registers at startup");

module_param(dump_sensor, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dump_sensor, "Dumps all usb sensor registers at startup providing a sensor is found");
