<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Jeilin JL2005B/C/D library
 *
 * Copyright (C) 2011 Theoकरोre Kilgore <kilgota@auburn.edu>
 */

#घोषणा MODULE_NAME "jl2005bcd"

#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश "gspca.h"


MODULE_AUTHOR("Theodore Kilgore <kilgota@auburn.edu>");
MODULE_DESCRIPTION("JL2005B/C/D USB Camera Driver");
MODULE_LICENSE("GPL");

/* Default समयouts, in ms */
#घोषणा JL2005C_CMD_TIMEOUT 500
#घोषणा JL2005C_DATA_TIMEOUT 1000

/* Maximum transfer size to use. */
#घोषणा JL2005C_MAX_TRANSFER 0x200
#घोषणा FRAME_HEADER_LEN 16


/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;  /* !! must be the first item */
	अचिन्हित अक्षर firmware_id[6];
	स्थिर काष्ठा v4l2_pix_क्रमmat *cap_mode;
	/* Driver stuff */
	काष्ठा work_काष्ठा work_काष्ठा;
	u8 frame_brightness;
	पूर्णांक block_size;	/* block size of camera */
	पूर्णांक vga;	/* 1 अगर vga cam, 0 अगर cअगर cam */
पूर्ण;


/* Camera has two resolution settings. What they are depends on model. */
अटल स्थिर काष्ठा v4l2_pix_क्रमmat cअगर_mode[] = अणु
	अणु176, 144, V4L2_PIX_FMT_JL2005BCD, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_JL2005BCD, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JL2005BCD, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JL2005BCD, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

/*
 * cam uses endpoपूर्णांक 0x03 to send commands, 0x84 क्रम पढ़ो commands,
 * and 0x82 क्रम bulk data transfer.
 */

/* All commands are two bytes only */
अटल पूर्णांक jl2005c_ग_लिखो2(काष्ठा gspca_dev *gspca_dev, अचिन्हित अक्षर *command)
अणु
	पूर्णांक retval;

	स_नकल(gspca_dev->usb_buf, command, 2);
	retval = usb_bulk_msg(gspca_dev->dev,
			usb_sndbulkpipe(gspca_dev->dev, 3),
			gspca_dev->usb_buf, 2, शून्य, 500);
	अगर (retval < 0)
		pr_err("command write [%02x] error %d\n",
		       gspca_dev->usb_buf[0], retval);
	वापस retval;
पूर्ण

/* Response to a command is one byte in usb_buf[0], only अगर requested. */
अटल पूर्णांक jl2005c_पढ़ो1(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक retval;

	retval = usb_bulk_msg(gspca_dev->dev,
				usb_rcvbulkpipe(gspca_dev->dev, 0x84),
				gspca_dev->usb_buf, 1, शून्य, 500);
	अगर (retval < 0)
		pr_err("read command [0x%02x] error %d\n",
		       gspca_dev->usb_buf[0], retval);
	वापस retval;
पूर्ण

/* Response appears in gspca_dev->usb_buf[0] */
अटल पूर्णांक jl2005c_पढ़ो_reg(काष्ठा gspca_dev *gspca_dev, अचिन्हित अक्षर reg)
अणु
	पूर्णांक retval;

	अटल u8 inकाष्ठाion[2] = अणु0x95, 0x00पूर्ण;
	/* put रेजिस्टर to पढ़ो in byte 1 */
	inकाष्ठाion[1] = reg;
	/* Send the पढ़ो request */
	retval = jl2005c_ग_लिखो2(gspca_dev, inकाष्ठाion);
	अगर (retval < 0)
		वापस retval;
	retval = jl2005c_पढ़ो1(gspca_dev);

	वापस retval;
पूर्ण

अटल पूर्णांक jl2005c_start_new_frame(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	पूर्णांक retval;
	पूर्णांक frame_brightness = 0;

	अटल u8 inकाष्ठाion[2] = अणु0x7f, 0x01पूर्ण;

	retval = jl2005c_ग_लिखो2(gspca_dev, inकाष्ठाion);
	अगर (retval < 0)
		वापस retval;

	i = 0;
	जबतक (i < 20 && !frame_brightness) अणु
		/* If we tried 20 बार, give up. */
		retval = jl2005c_पढ़ो_reg(gspca_dev, 0x7e);
		अगर (retval < 0)
			वापस retval;
		frame_brightness = gspca_dev->usb_buf[0];
		retval = jl2005c_पढ़ो_reg(gspca_dev, 0x7d);
		अगर (retval < 0)
			वापस retval;
		i++;
	पूर्ण
	gspca_dbg(gspca_dev, D_FRAM, "frame_brightness is 0x%02x\n",
		  gspca_dev->usb_buf[0]);
	वापस retval;
पूर्ण

अटल पूर्णांक jl2005c_ग_लिखो_reg(काष्ठा gspca_dev *gspca_dev, अचिन्हित अक्षर reg,
						    अचिन्हित अक्षर value)
अणु
	पूर्णांक retval;
	u8 inकाष्ठाion[2];

	inकाष्ठाion[0] = reg;
	inकाष्ठाion[1] = value;

	retval = jl2005c_ग_लिखो2(gspca_dev, inकाष्ठाion);
	अगर (retval < 0)
			वापस retval;

	वापस retval;
पूर्ण

अटल पूर्णांक jl2005c_get_firmware_id(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	पूर्णांक i = 0;
	पूर्णांक retval;
	अचिन्हित अक्षर regs_to_पढ़ो[] = अणु0x57, 0x02, 0x03, 0x5d, 0x5e, 0x5fपूर्ण;

	gspca_dbg(gspca_dev, D_PROBE, "Running jl2005c_get_firmware_id\n");
	/* Read the first ID byte once क्रम warmup */
	retval = jl2005c_पढ़ो_reg(gspca_dev, regs_to_पढ़ो[0]);
	gspca_dbg(gspca_dev, D_PROBE, "response is %02x\n",
		  gspca_dev->usb_buf[0]);
	अगर (retval < 0)
		वापस retval;
	/* Now actually get the ID string */
	क्रम (i = 0; i < 6; i++) अणु
		retval = jl2005c_पढ़ो_reg(gspca_dev, regs_to_पढ़ो[i]);
		अगर (retval < 0)
			वापस retval;
		sd->firmware_id[i] = gspca_dev->usb_buf[0];
	पूर्ण
	gspca_dbg(gspca_dev, D_PROBE, "firmware ID is %02x%02x%02x%02x%02x%02x\n",
		  sd->firmware_id[0],
		  sd->firmware_id[1],
		  sd->firmware_id[2],
		  sd->firmware_id[3],
		  sd->firmware_id[4],
		  sd->firmware_id[5]);
	वापस 0;
पूर्ण

अटल पूर्णांक jl2005c_stream_start_vga_lg
		    (काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	पूर्णांक retval = -1;
	अटल u8 inकाष्ठाion[][2] = अणु
		अणु0x05, 0x00पूर्ण,
		अणु0x7c, 0x00पूर्ण,
		अणु0x7d, 0x18पूर्ण,
		अणु0x02, 0x00पूर्ण,
		अणु0x01, 0x00पूर्ण,
		अणु0x04, 0x52पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(inकाष्ठाion); i++) अणु
		msleep(60);
		retval = jl2005c_ग_लिखो2(gspca_dev, inकाष्ठाion[i]);
		अगर (retval < 0)
			वापस retval;
	पूर्ण
	msleep(60);
	वापस retval;
पूर्ण

अटल पूर्णांक jl2005c_stream_start_vga_small(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	पूर्णांक retval = -1;
	अटल u8 inकाष्ठाion[][2] = अणु
		अणु0x06, 0x00पूर्ण,
		अणु0x7c, 0x00पूर्ण,
		अणु0x7d, 0x1aपूर्ण,
		अणु0x02, 0x00पूर्ण,
		अणु0x01, 0x00पूर्ण,
		अणु0x04, 0x52पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(inकाष्ठाion); i++) अणु
		msleep(60);
		retval = jl2005c_ग_लिखो2(gspca_dev, inकाष्ठाion[i]);
		अगर (retval < 0)
			वापस retval;
	पूर्ण
	msleep(60);
	वापस retval;
पूर्ण

अटल पूर्णांक jl2005c_stream_start_cअगर_lg(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	पूर्णांक retval = -1;
	अटल u8 inकाष्ठाion[][2] = अणु
		अणु0x05, 0x00पूर्ण,
		अणु0x7c, 0x00पूर्ण,
		अणु0x7d, 0x30पूर्ण,
		अणु0x02, 0x00पूर्ण,
		अणु0x01, 0x00पूर्ण,
		अणु0x04, 0x42पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(inकाष्ठाion); i++) अणु
		msleep(60);
		retval = jl2005c_ग_लिखो2(gspca_dev, inकाष्ठाion[i]);
		अगर (retval < 0)
			वापस retval;
	पूर्ण
	msleep(60);
	वापस retval;
पूर्ण

अटल पूर्णांक jl2005c_stream_start_cअगर_small(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	पूर्णांक retval = -1;
	अटल u8 inकाष्ठाion[][2] = अणु
		अणु0x06, 0x00पूर्ण,
		अणु0x7c, 0x00पूर्ण,
		अणु0x7d, 0x32पूर्ण,
		अणु0x02, 0x00पूर्ण,
		अणु0x01, 0x00पूर्ण,
		अणु0x04, 0x42पूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(inकाष्ठाion); i++) अणु
		msleep(60);
		retval = jl2005c_ग_लिखो2(gspca_dev, inकाष्ठाion[i]);
		अगर (retval < 0)
			वापस retval;
	पूर्ण
	msleep(60);
	वापस retval;
पूर्ण


अटल पूर्णांक jl2005c_stop(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस jl2005c_ग_लिखो_reg(gspca_dev, 0x07, 0x00);
पूर्ण

/*
 * This function is called as a workqueue function and runs whenever the camera
 * is streaming data. Because it is a workqueue function it is allowed to sleep
 * so we can use synchronous USB calls. To aव्योम possible collisions with other
 * thपढ़ोs attempting to use gspca_dev->usb_buf we take the usb_lock when
 * perक्रमming USB operations using it. In practice we करोn't really need this
 * as the camera करोesn't provide any controls.
 */
अटल व्योम jl2005c_करोstream(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sd *dev = container_of(work, काष्ठा sd, work_काष्ठा);
	काष्ठा gspca_dev *gspca_dev = &dev->gspca_dev;
	पूर्णांक bytes_left = 0; /* bytes reमुख्यing in current frame. */
	पूर्णांक data_len;   /* size to use क्रम the next पढ़ो. */
	पूर्णांक header_पढ़ो = 0;
	अचिन्हित अक्षर header_sig[2] = अणु0x4a, 0x4cपूर्ण;
	पूर्णांक act_len;
	पूर्णांक packet_type;
	पूर्णांक ret;
	u8 *buffer;

	buffer = kदो_स्मृति(JL2005C_MAX_TRANSFER, GFP_KERNEL);
	अगर (!buffer) अणु
		pr_err("Couldn't allocate USB buffer\n");
		जाओ quit_stream;
	पूर्ण

	जबतक (gspca_dev->present && gspca_dev->streaming) अणु
#अगर_घोषित CONFIG_PM
		अगर (gspca_dev->frozen)
			अवरोध;
#पूर्ण_अगर
		/* Check अगर this is a new frame. If so, start the frame first */
		अगर (!header_पढ़ो) अणु
			mutex_lock(&gspca_dev->usb_lock);
			ret = jl2005c_start_new_frame(gspca_dev);
			mutex_unlock(&gspca_dev->usb_lock);
			अगर (ret < 0)
				जाओ quit_stream;
			ret = usb_bulk_msg(gspca_dev->dev,
				usb_rcvbulkpipe(gspca_dev->dev, 0x82),
				buffer, JL2005C_MAX_TRANSFER, &act_len,
				JL2005C_DATA_TIMEOUT);
			gspca_dbg(gspca_dev, D_PACK,
				  "Got %d bytes out of %d for header\n",
				  act_len, JL2005C_MAX_TRANSFER);
			अगर (ret < 0 || act_len < JL2005C_MAX_TRANSFER)
				जाओ quit_stream;
			/* Check whether we actually got the first blodk */
			अगर (स_भेद(header_sig, buffer, 2) != 0) अणु
				pr_err("First block is not the first block\n");
				जाओ quit_stream;
			पूर्ण
			/* total size to fetch is byte 7, बार blocksize
			 * of which we alपढ़ोy got act_len */
			bytes_left = buffer[0x07] * dev->block_size - act_len;
			gspca_dbg(gspca_dev, D_PACK, "bytes_left = 0x%x\n",
				  bytes_left);
			/* We keep the header. It has other inक्रमmation, too.*/
			packet_type = FIRST_PACKET;
			gspca_frame_add(gspca_dev, packet_type,
					buffer, act_len);
			header_पढ़ो = 1;
		पूर्ण
		जबतक (bytes_left > 0 && gspca_dev->present) अणु
			data_len = bytes_left > JL2005C_MAX_TRANSFER ?
				JL2005C_MAX_TRANSFER : bytes_left;
			ret = usb_bulk_msg(gspca_dev->dev,
				usb_rcvbulkpipe(gspca_dev->dev, 0x82),
				buffer, data_len, &act_len,
				JL2005C_DATA_TIMEOUT);
			अगर (ret < 0 || act_len < data_len)
				जाओ quit_stream;
			gspca_dbg(gspca_dev, D_PACK,
				  "Got %d bytes out of %d for frame\n",
				  data_len, bytes_left);
			bytes_left -= data_len;
			अगर (bytes_left == 0) अणु
				packet_type = LAST_PACKET;
				header_पढ़ो = 0;
			पूर्ण अन्यथा
				packet_type = INTER_PACKET;
			gspca_frame_add(gspca_dev, packet_type,
					buffer, data_len);
		पूर्ण
	पूर्ण
quit_stream:
	अगर (gspca_dev->present) अणु
		mutex_lock(&gspca_dev->usb_lock);
		jl2005c_stop(gspca_dev);
		mutex_unlock(&gspca_dev->usb_lock);
	पूर्ण
	kमुक्त(buffer);
पूर्ण




/* This function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	cam = &gspca_dev->cam;
	/* We करोn't use the buffer gspca allocates so make it small. */
	cam->bulk_size = 64;
	cam->bulk = 1;
	/* For the rest, the camera needs to be detected */
	jl2005c_get_firmware_id(gspca_dev);
	/* Here are some known firmware IDs
	 * First some JL2005B cameras
	 * अणु0x41, 0x07, 0x04, 0x2c, 0xe8, 0xf2पूर्ण	Sakar KidzCam
	 * अणु0x45, 0x02, 0x08, 0xb9, 0x00, 0xd2पूर्ण	No-name JL2005B
	 * JL2005C cameras
	 * अणु0x01, 0x0c, 0x16, 0x10, 0xf8, 0xc8पूर्ण	Argus DC-1512
	 * अणु0x12, 0x04, 0x03, 0xc0, 0x00, 0xd8पूर्ण	ICarly
	 * अणु0x86, 0x08, 0x05, 0x02, 0x00, 0xd4पूर्ण	Jazz
	 *
	 * Based upon this scanty evidence, we can detect a CIF camera by
	 * testing byte 0 क्रम 0x4x.
	 */
	अगर ((sd->firmware_id[0] & 0xf0) == 0x40) अणु
		cam->cam_mode	= cअगर_mode;
		cam->nmodes	= ARRAY_SIZE(cअगर_mode);
		sd->block_size	= 0x80;
	पूर्ण अन्यथा अणु
		cam->cam_mode	= vga_mode;
		cam->nmodes	= ARRAY_SIZE(vga_mode);
		sd->block_size	= 0x200;
	पूर्ण

	INIT_WORK(&sd->work_काष्ठा, jl2005c_करोstream);

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु

	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	sd->cap_mode = gspca_dev->cam.cam_mode;

	चयन (gspca_dev->pixfmt.width) अणु
	हाल 640:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at vga resolution\n");
		jl2005c_stream_start_vga_lg(gspca_dev);
		अवरोध;
	हाल 320:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at qvga resolution\n");
		jl2005c_stream_start_vga_small(gspca_dev);
		अवरोध;
	हाल 352:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at cif resolution\n");
		jl2005c_stream_start_cअगर_lg(gspca_dev);
		अवरोध;
	हाल 176:
		gspca_dbg(gspca_dev, D_STREAM, "Start streaming at qcif resolution\n");
		jl2005c_stream_start_cअगर_small(gspca_dev);
		अवरोध;
	शेष:
		pr_err("Unknown resolution specified\n");
		वापस -1;
	पूर्ण

	schedule_work(&sd->work_काष्ठा);

	वापस 0;
पूर्ण

/* called on streamoff with alt==0 and on disconnect */
/* the usb_lock is held at entry - restore on निकास */
अटल व्योम sd_stop0(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *dev = (काष्ठा sd *) gspca_dev;

	/* रुको क्रम the work queue to terminate */
	mutex_unlock(&gspca_dev->usb_lock);
	/* This रुकोs क्रम sq905c_करोstream to finish */
	flush_work(&dev->work_काष्ठा);
	mutex_lock(&gspca_dev->usb_lock);
पूर्ण



/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.start = sd_start,
	.stop0 = sd_stop0,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x0979, 0x0227)पूर्ण,
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

अटल काष्ठा usb_driver sd_driver = अणु
	.name = MODULE_NAME,
	.id_table = device_table,
	.probe = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
