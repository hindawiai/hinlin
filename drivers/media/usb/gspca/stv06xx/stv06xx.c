<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2001 Jean-Fredric Clere, Nikolas Zimmermann, Georg Acher
 *		      Mark Cave-Ayland, Carlo E Prelz, Dick Streefland
 * Copyright (c) 2002, 2003 Tuukka Toivonen
 * Copyright (c) 2008 Erik Andrथऊn
 *
 * P/N 861037:      Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensor Photobit PB100  ASIC STV0600-1 - QuickCam Express
 * P/N 861055:      Sensor ST VV6410       ASIC STV0610   - LEGO cam
 * P/N 861075-0040: Sensor HDCS1000        ASIC
 * P/N 961179-0700: Sensor ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensor ST VV6410       ASIC STV0610   - QuickCam Web
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/input.h>
#समावेश "stv06xx_sensor.h"

MODULE_AUTHOR("Erik Andrथऊn");
MODULE_DESCRIPTION("STV06XX USB Camera Driver");
MODULE_LICENSE("GPL");

अटल bool dump_bridge;
अटल bool dump_sensor;

पूर्णांक stv06xx_ग_लिखो_bridge(काष्ठा sd *sd, u16 address, u16 i2c_data)
अणु
	पूर्णांक err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	u8 len = (i2c_data > 0xff) ? 2 : 1;

	buf[0] = i2c_data & 0xff;
	buf[1] = (i2c_data >> 8) & 0xff;

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      0x04, 0x40, address, 0, buf, len,
			      STV06XX_URB_MSG_TIMEOUT);

	gspca_dbg(gspca_dev, D_CONF, "Written 0x%x to address 0x%x, status: %d\n",
		  i2c_data, address, err);

	वापस (err < 0) ? err : 0;
पूर्ण

पूर्णांक stv06xx_पढ़ो_bridge(काष्ठा sd *sd, u16 address, u8 *i2c_data)
अणु
	पूर्णांक err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	err = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      0x04, 0xc0, address, 0, buf, 1,
			      STV06XX_URB_MSG_TIMEOUT);

	*i2c_data = buf[0];

	gspca_dbg(gspca_dev, D_CONF, "Reading 0x%x from address 0x%x, status %d\n",
		  *i2c_data, address, err);

	वापस (err < 0) ? err : 0;
पूर्ण

/* Wraps the normal ग_लिखो sensor bytes / words functions क्रम writing a
   single value */
पूर्णांक stv06xx_ग_लिखो_sensor(काष्ठा sd *sd, u8 address, u16 value)
अणु
	अगर (sd->sensor->i2c_len == 2) अणु
		u16 data[2] = अणु address, value पूर्ण;
		वापस stv06xx_ग_लिखो_sensor_words(sd, data, 1);
	पूर्ण अन्यथा अणु
		u8 data[2] = अणु address, value पूर्ण;
		वापस stv06xx_ग_लिखो_sensor_bytes(sd, data, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक stv06xx_ग_लिखो_sensor_finish(काष्ठा sd *sd)
अणु
	पूर्णांक err = 0;

	अगर (sd->bridge == BRIDGE_STV610) अणु
		काष्ठा usb_device *udev = sd->gspca_dev.dev;
		__u8 *buf = sd->gspca_dev.usb_buf;

		buf[0] = 0;
		err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				      0x04, 0x40, 0x1704, 0, buf, 1,
				      STV06XX_URB_MSG_TIMEOUT);
	पूर्ण

	वापस (err < 0) ? err : 0;
पूर्ण

पूर्णांक stv06xx_ग_लिखो_sensor_bytes(काष्ठा sd *sd, स्थिर u8 *data, u8 len)
अणु
	पूर्णांक err, i, j;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	gspca_dbg(gspca_dev, D_CONF, "I2C: Command buffer contains %d entries\n",
		  len);
	क्रम (i = 0; i < len;) अणु
		/* Build the command buffer */
		स_रखो(buf, 0, I2C_BUFFER_LENGTH);
		क्रम (j = 0; j < I2C_MAX_BYTES && i < len; j++, i++) अणु
			buf[j] = data[2*i];
			buf[0x10 + j] = data[2*i+1];
			gspca_dbg(gspca_dev, D_CONF, "I2C: Writing 0x%02x to reg 0x%02x\n",
				  data[2*i+1], data[2*i]);
		पूर्ण
		buf[0x20] = sd->sensor->i2c_addr;
		buf[0x21] = j - 1; /* Number of commands to send - 1 */
		buf[0x22] = I2C_WRITE_CMD;
		err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				      0x04, 0x40, 0x0400, 0, buf,
				      I2C_BUFFER_LENGTH,
				      STV06XX_URB_MSG_TIMEOUT);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस stv06xx_ग_लिखो_sensor_finish(sd);
पूर्ण

पूर्णांक stv06xx_ग_लिखो_sensor_words(काष्ठा sd *sd, स्थिर u16 *data, u8 len)
अणु
	पूर्णांक err, i, j;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	gspca_dbg(gspca_dev, D_CONF, "I2C: Command buffer contains %d entries\n",
		  len);

	क्रम (i = 0; i < len;) अणु
		/* Build the command buffer */
		स_रखो(buf, 0, I2C_BUFFER_LENGTH);
		क्रम (j = 0; j < I2C_MAX_WORDS && i < len; j++, i++) अणु
			buf[j] = data[2*i];
			buf[0x10 + j * 2] = data[2*i+1];
			buf[0x10 + j * 2 + 1] = data[2*i+1] >> 8;
			gspca_dbg(gspca_dev, D_CONF, "I2C: Writing 0x%04x to reg 0x%02x\n",
				  data[2*i+1], data[2*i]);
		पूर्ण
		buf[0x20] = sd->sensor->i2c_addr;
		buf[0x21] = j - 1; /* Number of commands to send - 1 */
		buf[0x22] = I2C_WRITE_CMD;
		err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				0x04, 0x40, 0x0400, 0, buf,
				I2C_BUFFER_LENGTH,
				STV06XX_URB_MSG_TIMEOUT);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस stv06xx_ग_लिखो_sensor_finish(sd);
पूर्ण

पूर्णांक stv06xx_पढ़ो_sensor(काष्ठा sd *sd, स्थिर u8 address, u16 *value)
अणु
	पूर्णांक err;
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;
	काष्ठा usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	err = stv06xx_ग_लिखो_bridge(sd, STV_I2C_FLUSH, sd->sensor->i2c_flush);
	अगर (err < 0)
		वापस err;

	/* Clear mem */
	स_रखो(buf, 0, I2C_BUFFER_LENGTH);

	buf[0] = address;
	buf[0x20] = sd->sensor->i2c_addr;
	buf[0x21] = 0;

	/* Read I2C रेजिस्टर */
	buf[0x22] = I2C_READ_CMD;

	err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			      0x04, 0x40, 0x1400, 0, buf, I2C_BUFFER_LENGTH,
			      STV06XX_URB_MSG_TIMEOUT);
	अगर (err < 0) अणु
		pr_err("I2C: Read error writing address: %d\n", err);
		वापस err;
	पूर्ण

	err = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      0x04, 0xc0, 0x1410, 0, buf, sd->sensor->i2c_len,
			      STV06XX_URB_MSG_TIMEOUT);
	अगर (sd->sensor->i2c_len == 2)
		*value = buf[0] | (buf[1] << 8);
	अन्यथा
		*value = buf[0];

	gspca_dbg(gspca_dev, D_CONF, "I2C: Read 0x%x from address 0x%x, status: %d\n",
		  *value, address, err);

	वापस (err < 0) ? err : 0;
पूर्ण

/* Dumps all bridge रेजिस्टरs */
अटल व्योम stv06xx_dump_bridge(काष्ठा sd *sd)
अणु
	पूर्णांक i;
	u8 data, buf;

	pr_info("Dumping all stv06xx bridge registers\n");
	क्रम (i = 0x1400; i < 0x160f; i++) अणु
		stv06xx_पढ़ो_bridge(sd, i, &data);

		pr_info("Read 0x%x from address 0x%x\n", data, i);
	पूर्ण

	pr_info("Testing stv06xx bridge registers for writability\n");
	क्रम (i = 0x1400; i < 0x160f; i++) अणु
		stv06xx_पढ़ो_bridge(sd, i, &data);
		buf = data;

		stv06xx_ग_लिखो_bridge(sd, i, 0xff);
		stv06xx_पढ़ो_bridge(sd, i, &data);
		अगर (data == 0xff)
			pr_info("Register 0x%x is read/write\n", i);
		अन्यथा अगर (data != buf)
			pr_info("Register 0x%x is read/write, but only partially\n",
				i);
		अन्यथा
			pr_info("Register 0x%x is read-only\n", i);

		stv06xx_ग_लिखो_bridge(sd, i, buf);
	पूर्ण
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक stv06xx_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;

	gspca_dbg(gspca_dev, D_PROBE, "Initializing camera\n");

	/* Let the usb init settle क्रम a bit
	   beक्रमe perक्रमming the initialization */
	msleep(250);

	err = sd->sensor->init(sd);

	अगर (dump_sensor && sd->sensor->dump)
		sd->sensor->dump(sd);

	वापस (err < 0) ? err : 0;
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक stv06xx_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PROBE, "Initializing controls\n");

	gspca_dev->vdev.ctrl_handler = &gspca_dev->ctrl_handler;
	वापस sd->sensor->init_controls(sd);
पूर्ण

/* Start the camera */
अटल पूर्णांक stv06xx_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	पूर्णांक err, packet_size;

	पूर्णांकf = usb_अगरnum_to_अगर(sd->gspca_dev.dev, sd->gspca_dev.अगरace);
	alt = usb_altnum_to_altsetting(पूर्णांकf, sd->gspca_dev.alt);
	अगर (!alt) अणु
		gspca_err(gspca_dev, "Couldn't get altsetting\n");
		वापस -EIO;
	पूर्ण

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	packet_size = le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);
	err = stv06xx_ग_लिखो_bridge(sd, STV_ISO_SIZE_L, packet_size);
	अगर (err < 0)
		वापस err;

	/* Prepare the sensor क्रम start */
	err = sd->sensor->start(sd);
	अगर (err < 0)
		जाओ out;

	/* Start isochronous streaming */
	err = stv06xx_ग_लिखो_bridge(sd, STV_ISO_ENABLE, 1);

out:
	अगर (err < 0)
		gspca_dbg(gspca_dev, D_STREAM, "Starting stream failed\n");
	अन्यथा
		gspca_dbg(gspca_dev, D_STREAM, "Started streaming\n");

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक stv06xx_isoc_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_पूर्णांकerface_cache *पूर्णांकfc;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	पूर्णांकfc = gspca_dev->dev->actconfig->पूर्णांकf_cache[0];

	अगर (पूर्णांकfc->num_altsetting < 2)
		वापस -ENODEV;

	alt = &पूर्णांकfc->altsetting[1];

	अगर (alt->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	/* Start isoc bandwidth "negotiation" at max isoc bandwidth */
	alt->endpoपूर्णांक[0].desc.wMaxPacketSize =
		cpu_to_le16(sd->sensor->max_packet_size[gspca_dev->curr_mode]);

	वापस 0;
पूर्ण

अटल पूर्णांक stv06xx_isoc_nego(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक ret, packet_size, min_packet_size;
	काष्ठा usb_host_पूर्णांकerface *alt;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/*
	 * Existence of altsetting and endpoपूर्णांक was verअगरied in
	 * stv06xx_isoc_init()
	 */
	alt = &gspca_dev->dev->actconfig->पूर्णांकf_cache[0]->altsetting[1];
	packet_size = le16_to_cpu(alt->endpoपूर्णांक[0].desc.wMaxPacketSize);
	min_packet_size = sd->sensor->min_packet_size[gspca_dev->curr_mode];
	अगर (packet_size <= min_packet_size)
		वापस -EIO;

	packet_size -= 100;
	अगर (packet_size < min_packet_size)
		packet_size = min_packet_size;
	alt->endpoपूर्णांक[0].desc.wMaxPacketSize = cpu_to_le16(packet_size);

	ret = usb_set_पूर्णांकerface(gspca_dev->dev, gspca_dev->अगरace, 1);
	अगर (ret < 0)
		gspca_err(gspca_dev, "set alt 1 err %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम stv06xx_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक err;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* stop ISO-streaming */
	err = stv06xx_ग_लिखो_bridge(sd, STV_ISO_ENABLE, 0);
	अगर (err < 0)
		जाओ out;

	err = sd->sensor->stop(sd);

out:
	अगर (err < 0)
		gspca_dbg(gspca_dev, D_STREAM, "Failed to stop stream\n");
	अन्यथा
		gspca_dbg(gspca_dev, D_STREAM, "Stopped streaming\n");
पूर्ण

/*
 * Analyse an USB packet of the data stream and store it appropriately.
 * Each packet contains an पूर्णांकegral number of chunks. Each chunk has
 * 2-bytes identअगरication, followed by 2-bytes that describe the chunk
 * length. Known/guessed chunk identअगरications are:
 * 8001/8005/C001/C005 - Begin new frame
 * 8002/8006/C002/C006 - End frame
 * 0200/4200           - Contains actual image data, bayer or compressed
 * 0005                - 11 bytes of unknown data
 * 0100                - 2 bytes of unknown data
 * The 0005 and 0100 chunks seem to appear only in compressed stream.
 */
अटल व्योम stv06xx_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PACK, "Packet of length %d arrived\n", len);

	/* A packet may contain several frames
	   loop until the whole packet is reached */
	जबतक (len) अणु
		पूर्णांक id, chunk_len;

		अगर (len < 4) अणु
			gspca_dbg(gspca_dev, D_PACK, "Packet is smaller than 4 bytes\n");
			वापस;
		पूर्ण

		/* Capture the id */
		id = (data[0] << 8) | data[1];

		/* Capture the chunk length */
		chunk_len = (data[2] << 8) | data[3];
		gspca_dbg(gspca_dev, D_PACK, "Chunk id: %x, length: %d\n",
			  id, chunk_len);

		data += 4;
		len -= 4;

		अगर (len < chunk_len) अणु
			gspca_err(gspca_dev, "URB packet length is smaller than the specified chunk length\n");
			gspca_dev->last_packet_type = DISCARD_PACKET;
			वापस;
		पूर्ण

		/* First byte seem to be 02=data 2nd byte is unknown??? */
		अगर (sd->bridge == BRIDGE_ST6422 && (id & 0xff00) == 0x0200)
			जाओ frame_data;

		चयन (id) अणु
		हाल 0x0200:
		हाल 0x4200:
frame_data:
			gspca_dbg(gspca_dev, D_PACK, "Frame data packet detected\n");

			अगर (sd->to_skip) अणु
				पूर्णांक skip = (sd->to_skip < chunk_len) ?
					    sd->to_skip : chunk_len;
				data += skip;
				len -= skip;
				chunk_len -= skip;
				sd->to_skip -= skip;
			पूर्ण

			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, chunk_len);
			अवरोध;

		हाल 0x8001:
		हाल 0x8005:
		हाल 0xc001:
		हाल 0xc005:
			gspca_dbg(gspca_dev, D_PACK, "Starting new frame\n");

			/* Create a new frame, chunk length should be zero */
			gspca_frame_add(gspca_dev, FIRST_PACKET,
					शून्य, 0);

			अगर (sd->bridge == BRIDGE_ST6422)
				sd->to_skip = gspca_dev->pixfmt.width * 4;

			अगर (chunk_len)
				gspca_err(gspca_dev, "Chunk length is non-zero on a SOF\n");
			अवरोध;

		हाल 0x8002:
		हाल 0x8006:
		हाल 0xc002:
			gspca_dbg(gspca_dev, D_PACK, "End of frame detected\n");

			/* Complete the last frame (अगर any) */
			gspca_frame_add(gspca_dev, LAST_PACKET,
					शून्य, 0);

			अगर (chunk_len)
				gspca_err(gspca_dev, "Chunk length is non-zero on a EOF\n");
			अवरोध;

		हाल 0x0005:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x005 detected\n");
			/* Unknown chunk with 11 bytes of data,
			   occurs just beक्रमe end of each frame
			   in compressed mode */
			अवरोध;

		हाल 0x0100:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x0100 detected\n");
			/* Unknown chunk with 2 bytes of data,
			   occurs 2-3 बार per USB पूर्णांकerrupt */
			अवरोध;
		हाल 0x42ff:
			gspca_dbg(gspca_dev, D_PACK, "Chunk 0x42ff detected\n");
			/* Special chunk seen someबार on the ST6422 */
			अवरोध;
		शेष:
			gspca_dbg(gspca_dev, D_PACK, "Unknown chunk 0x%04x detected\n",
				  id);
			/* Unknown chunk */
		पूर्ण
		data    += chunk_len;
		len     -= chunk_len;
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
अटल पूर्णांक sd_पूर्णांक_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,		/* पूर्णांकerrupt packet data */
			पूर्णांक len)		/* पूर्णांकerrupt packet length */
अणु
	पूर्णांक ret = -EINVAL;

	अगर (len == 1 && (data[0] == 0x80 || data[0] == 0x10)) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 1);
		input_sync(gspca_dev->input_dev);
		ret = 0;
	पूर्ण

	अगर (len == 1 && (data[0] == 0x88 || data[0] == 0x11)) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक stv06xx_config(काष्ठा gspca_dev *gspca_dev,
			  स्थिर काष्ठा usb_device_id *id);

अटल व्योम stv06xx_probe_error(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	kमुक्त(sd->sensor_priv);
	sd->sensor_priv = शून्य;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = stv06xx_config,
	.init = stv06xx_init,
	.init_controls = stv06xx_init_controls,
	.probe_error = stv06xx_probe_error,
	.start = stv06xx_start,
	.stopN = stv06xx_stopN,
	.pkt_scan = stv06xx_pkt_scan,
	.isoc_init = stv06xx_isoc_init,
	.isoc_nego = stv06xx_isoc_nego,
#अगर IS_ENABLED(CONFIG_INPUT)
	.पूर्णांक_pkt_scan = sd_पूर्णांक_pkt_scan,
#पूर्ण_अगर
पूर्ण;

/* This function is called at probe समय */
अटल पूर्णांक stv06xx_config(काष्ठा gspca_dev *gspca_dev,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_PROBE, "Configuring camera\n");

	sd->bridge = id->driver_info;
	gspca_dev->sd_desc = &sd_desc;

	अगर (dump_bridge)
		stv06xx_dump_bridge(sd);

	sd->sensor = &stv06xx_sensor_st6422;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	sd->sensor = &stv06xx_sensor_vv6410;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	sd->sensor = &stv06xx_sensor_hdcs1x00;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	sd->sensor = &stv06xx_sensor_hdcs1020;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	sd->sensor = &stv06xx_sensor_pb0100;
	अगर (!sd->sensor->probe(sd))
		वापस 0;

	sd->sensor = शून्य;
	वापस -ENODEV;
पूर्ण



/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x046d, 0x0840), .driver_info = BRIDGE_STV600 पूर्ण,	/* QuickCam Express */
	अणुUSB_DEVICE(0x046d, 0x0850), .driver_info = BRIDGE_STV610 पूर्ण,	/* LEGO cam / QuickCam Web */
	अणुUSB_DEVICE(0x046d, 0x0870), .driver_info = BRIDGE_STV602 पूर्ण,	/* Dexxa WebCam USB */
	अणुUSB_DEVICE(0x046D, 0x08F0), .driver_info = BRIDGE_ST6422 पूर्ण,	/* QuickCam Messenger */
	अणुUSB_DEVICE(0x046D, 0x08F5), .driver_info = BRIDGE_ST6422 पूर्ण,	/* QuickCam Communicate */
	अणुUSB_DEVICE(0x046D, 0x08F6), .driver_info = BRIDGE_ST6422 पूर्ण,	/* QuickCam Messenger (new) */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc, माप(काष्ठा sd),
			       THIS_MODULE);
पूर्ण

अटल व्योम sd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा gspca_dev *gspca_dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	व्योम *priv = sd->sensor_priv;
	gspca_dbg(gspca_dev, D_PROBE, "Disconnecting the stv06xx device\n");

	sd->sensor = शून्य;
	gspca_disconnect(पूर्णांकf);
	kमुक्त(priv);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name = MODULE_NAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = sd_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);

module_param(dump_bridge, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dump_bridge, "Dumps all usb bridge registers at startup");

module_param(dump_sensor, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dump_sensor, "Dumps all sensor registers at startup");
