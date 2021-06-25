<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * kinect sensor device camera, gspca driver
 *
 * Copyright (C) 2011  Antonio Ospite <ospite@studenti.unina.it>
 *
 * Based on the OpenKinect project and libमुक्तnect
 * http://खोलोkinect.org/wiki/Init_Analysis
 *
 * Special thanks to Steven Toth and kernelद_असल.com क्रम sponsoring a Kinect
 * sensor device which I tested the driver on.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "kinect"

#समावेश "gspca.h"

#घोषणा CTRL_TIMEOUT 500

MODULE_AUTHOR("Antonio Ospite <ospite@studenti.unina.it>");
MODULE_DESCRIPTION("GSPCA/Kinect Sensor Device USB Camera Driver");
MODULE_LICENSE("GPL");

अटल bool depth_mode;

काष्ठा pkt_hdr अणु
	uपूर्णांक8_t magic[2];
	uपूर्णांक8_t pad;
	uपूर्णांक8_t flag;
	uपूर्णांक8_t unk1;
	uपूर्णांक8_t seq;
	uपूर्णांक8_t unk2;
	uपूर्णांक8_t unk3;
	uपूर्णांक32_t बारtamp;
पूर्ण;

काष्ठा cam_hdr अणु
	uपूर्णांक8_t magic[2];
	__le16 len;
	__le16 cmd;
	__le16 tag;
पूर्ण;

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev; /* !! must be the first item */
	uपूर्णांक16_t cam_tag;           /* a sequence number क्रम packets */
	uपूर्णांक8_t stream_flag;        /* to identअगरy dअगरferent stream types */
	uपूर्णांक8_t obuf[0x400];        /* output buffer क्रम control commands */
	uपूर्णांक8_t ibuf[0x200];        /* input buffer क्रम control commands */
पूर्ण;

#घोषणा MODE_640x480   0x0001
#घोषणा MODE_640x488   0x0002
#घोषणा MODE_1280x1024 0x0004

#घोषणा FORMAT_BAYER   0x0010
#घोषणा FORMAT_UYVY    0x0020
#घोषणा FORMAT_Y10B    0x0040

#घोषणा FPS_HIGH       0x0100

अटल स्थिर काष्ठा v4l2_pix_क्रमmat depth_camera_mode[] = अणु
	अणु640, 480, V4L2_PIX_FMT_Y10BPACK, V4L2_FIELD_NONE,
	 .bytesperline = 640 * 10 / 8,
	 .sizeimage =  640 * 480 * 10 / 8,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = MODE_640x488 | FORMAT_Y10Bपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat video_camera_mode[] = अणु
	अणु640, 480, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
	 .bytesperline = 640,
	 .sizeimage = 640 * 480,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = MODE_640x480 | FORMAT_BAYER | FPS_HIGHपूर्ण,
	अणु640, 480, V4L2_PIX_FMT_UYVY, V4L2_FIELD_NONE,
	 .bytesperline = 640 * 2,
	 .sizeimage = 640 * 480 * 2,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = MODE_640x480 | FORMAT_UYVYपूर्ण,
	अणु1280, 1024, V4L2_PIX_FMT_SGRBG8, V4L2_FIELD_NONE,
	 .bytesperline = 1280,
	 .sizeimage = 1280 * 1024,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = MODE_1280x1024 | FORMAT_BAYERपूर्ण,
	अणु640, 488, V4L2_PIX_FMT_Y10BPACK, V4L2_FIELD_NONE,
	 .bytesperline = 640 * 10 / 8,
	 .sizeimage =  640 * 488 * 10 / 8,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = MODE_640x488 | FORMAT_Y10B | FPS_HIGHपूर्ण,
	अणु1280, 1024, V4L2_PIX_FMT_Y10BPACK, V4L2_FIELD_NONE,
	 .bytesperline = 1280 * 10 / 8,
	 .sizeimage =  1280 * 1024 * 10 / 8,
	 .colorspace = V4L2_COLORSPACE_SRGB,
	 .priv = MODE_1280x1024 | FORMAT_Y10Bपूर्ण,
पूर्ण;

अटल पूर्णांक kinect_ग_लिखो(काष्ठा usb_device *udev, uपूर्णांक8_t *data,
			uपूर्णांक16_t wLength)
अणु
	वापस usb_control_msg(udev,
			      usb_sndctrlpipe(udev, 0),
			      0x00,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, 0, data, wLength, CTRL_TIMEOUT);
पूर्ण

अटल पूर्णांक kinect_पढ़ो(काष्ठा usb_device *udev, uपूर्णांक8_t *data, uपूर्णांक16_t wLength)
अणु
	वापस usb_control_msg(udev,
			      usb_rcvctrlpipe(udev, 0),
			      0x00,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, 0, data, wLength, CTRL_TIMEOUT);
पूर्ण

अटल पूर्णांक send_cmd(काष्ठा gspca_dev *gspca_dev, uपूर्णांक16_t cmd, व्योम *cmdbuf,
		अचिन्हित पूर्णांक cmd_len, व्योम *replybuf, अचिन्हित पूर्णांक reply_len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा usb_device *udev = gspca_dev->dev;
	पूर्णांक res, actual_len;
	uपूर्णांक8_t *obuf = sd->obuf;
	uपूर्णांक8_t *ibuf = sd->ibuf;
	काष्ठा cam_hdr *chdr = (व्योम *)obuf;
	काष्ठा cam_hdr *rhdr = (व्योम *)ibuf;

	अगर (cmd_len & 1 || cmd_len > (0x400 - माप(*chdr))) अणु
		pr_err("send_cmd: Invalid command length (0x%x)\n", cmd_len);
		वापस -1;
	पूर्ण

	chdr->magic[0] = 0x47;
	chdr->magic[1] = 0x4d;
	chdr->cmd = cpu_to_le16(cmd);
	chdr->tag = cpu_to_le16(sd->cam_tag);
	chdr->len = cpu_to_le16(cmd_len / 2);

	स_नकल(obuf+माप(*chdr), cmdbuf, cmd_len);

	res = kinect_ग_लिखो(udev, obuf, cmd_len + माप(*chdr));
	gspca_dbg(gspca_dev, D_USBO, "Control cmd=%04x tag=%04x len=%04x: %d\n",
		  cmd,
		  sd->cam_tag, cmd_len, res);
	अगर (res < 0) अणु
		pr_err("send_cmd: Output control transfer failed (%d)\n", res);
		वापस res;
	पूर्ण

	करो अणु
		actual_len = kinect_पढ़ो(udev, ibuf, 0x200);
	पूर्ण जबतक (actual_len == 0);
	gspca_dbg(gspca_dev, D_USBO, "Control reply: %d\n", actual_len);
	अगर (actual_len < (पूर्णांक)माप(*rhdr)) अणु
		pr_err("send_cmd: Input control transfer failed (%d)\n",
		       actual_len);
		वापस actual_len < 0 ? actual_len : -EREMOTEIO;
	पूर्ण
	actual_len -= माप(*rhdr);

	अगर (rhdr->magic[0] != 0x52 || rhdr->magic[1] != 0x42) अणु
		pr_err("send_cmd: Bad magic %02x %02x\n",
		       rhdr->magic[0], rhdr->magic[1]);
		वापस -1;
	पूर्ण
	अगर (rhdr->cmd != chdr->cmd) अणु
		pr_err("send_cmd: Bad cmd %02x != %02x\n",
		       rhdr->cmd, chdr->cmd);
		वापस -1;
	पूर्ण
	अगर (rhdr->tag != chdr->tag) अणु
		pr_err("send_cmd: Bad tag %04x != %04x\n",
		       rhdr->tag, chdr->tag);
		वापस -1;
	पूर्ण
	अगर (le16_to_cpu(rhdr->len) != (actual_len/2)) अणु
		pr_err("send_cmd: Bad len %04x != %04x\n",
		       le16_to_cpu(rhdr->len), (पूर्णांक)(actual_len/2));
		वापस -1;
	पूर्ण

	अगर (actual_len > reply_len) अणु
		pr_warn("send_cmd: Data buffer is %d bytes long, but got %d bytes\n",
			reply_len, actual_len);
		स_नकल(replybuf, ibuf+माप(*rhdr), reply_len);
	पूर्ण अन्यथा अणु
		स_नकल(replybuf, ibuf+माप(*rhdr), actual_len);
	पूर्ण

	sd->cam_tag++;

	वापस actual_len;
पूर्ण

अटल पूर्णांक ग_लिखो_रेजिस्टर(काष्ठा gspca_dev *gspca_dev, uपूर्णांक16_t reg,
			uपूर्णांक16_t data)
अणु
	uपूर्णांक16_t reply[2];
	__le16 cmd[2];
	पूर्णांक res;

	cmd[0] = cpu_to_le16(reg);
	cmd[1] = cpu_to_le16(data);

	gspca_dbg(gspca_dev, D_USBO, "Write Reg 0x%04x <= 0x%02x\n", reg, data);
	res = send_cmd(gspca_dev, 0x03, cmd, 4, reply, 4);
	अगर (res < 0)
		वापस res;
	अगर (res != 2) अणु
		pr_warn("send_cmd returned %d [%04x %04x], 0000 expected\n",
			res, reply[0], reply[1]);
	पूर्ण
	वापस 0;
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config_video(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	sd->cam_tag = 0;

	sd->stream_flag = 0x80;

	cam = &gspca_dev->cam;

	cam->cam_mode = video_camera_mode;
	cam->nmodes = ARRAY_SIZE(video_camera_mode);

	gspca_dev->xfer_ep = 0x81;

#अगर 0
	/* Setting those values is not needed क्रम video stream */
	cam->npkt = 15;
	gspca_dev->pkt_size = 960 * 2;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक sd_config_depth(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	sd->cam_tag = 0;

	sd->stream_flag = 0x70;

	cam = &gspca_dev->cam;

	cam->cam_mode = depth_camera_mode;
	cam->nmodes = ARRAY_SIZE(depth_camera_mode);

	gspca_dev->xfer_ep = 0x82;

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dbg(gspca_dev, D_PROBE, "Kinect Camera device.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक sd_start_video(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक mode;
	uपूर्णांक8_t fmt_reg, fmt_val;
	uपूर्णांक8_t res_reg, res_val;
	uपूर्णांक8_t fps_reg, fps_val;
	uपूर्णांक8_t mode_val;

	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;

	अगर (mode & FORMAT_Y10B) अणु
		fmt_reg = 0x19;
		res_reg = 0x1a;
		fps_reg = 0x1b;
		mode_val = 0x03;
	पूर्ण अन्यथा अणु
		fmt_reg = 0x0c;
		res_reg = 0x0d;
		fps_reg = 0x0e;
		mode_val = 0x01;
	पूर्ण

	/* क्रमmat */
	अगर (mode & FORMAT_UYVY)
		fmt_val = 0x05;
	अन्यथा
		fmt_val = 0x00;

	अगर (mode & MODE_1280x1024)
		res_val = 0x02;
	अन्यथा
		res_val = 0x01;

	अगर (mode & FPS_HIGH)
		fps_val = 0x1e;
	अन्यथा
		fps_val = 0x0f;


	/* turn off IR-reset function */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x105, 0x00);

	/* Reset video stream */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x05, 0x00);

	/* Due to some ridiculous condition in the firmware, we have to start
	 * and stop the depth stream beक्रमe the camera will hand us 1280x1024
	 * IR.  This is a stupid workaround, but we've yet to find a better
	 * solution.
	 *
	 * Thanks to Drew Fisher क्रम figuring this out.
	 */
	अगर (mode & (FORMAT_Y10B | MODE_1280x1024)) अणु
		ग_लिखो_रेजिस्टर(gspca_dev, 0x13, 0x01);
		ग_लिखो_रेजिस्टर(gspca_dev, 0x14, 0x1e);
		ग_लिखो_रेजिस्टर(gspca_dev, 0x06, 0x02);
		ग_लिखो_रेजिस्टर(gspca_dev, 0x06, 0x00);
	पूर्ण

	ग_लिखो_रेजिस्टर(gspca_dev, fmt_reg, fmt_val);
	ग_लिखो_रेजिस्टर(gspca_dev, res_reg, res_val);
	ग_लिखो_रेजिस्टर(gspca_dev, fps_reg, fps_val);

	/* Start video stream */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x05, mode_val);

	/* disable Hflip */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x47, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक sd_start_depth(काष्ठा gspca_dev *gspca_dev)
अणु
	/* turn off IR-reset function */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x105, 0x00);

	/* reset depth stream */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x06, 0x00);
	/* Depth Stream Format 0x03: 11 bit stream | 0x02: 10 bit */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x12, 0x02);
	/* Depth Stream Resolution 1: standard (640x480) */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x13, 0x01);
	/* Depth Framerate / 0x1e (30): 30 fps */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x14, 0x1e);
	/* Depth Stream Control  / 2: Open Depth Stream */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x06, 0x02);
	/* disable depth hflip / LSB = 0: Smoothing Disabled */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x17, 0x00);

	वापस 0;
पूर्ण

अटल व्योम sd_stopN_video(काष्ठा gspca_dev *gspca_dev)
अणु
	/* reset video stream */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x05, 0x00);
पूर्ण

अटल व्योम sd_stopN_depth(काष्ठा gspca_dev *gspca_dev)
अणु
	/* reset depth stream */
	ग_लिखो_रेजिस्टर(gspca_dev, 0x06, 0x00);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev, u8 *__data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	काष्ठा pkt_hdr *hdr = (व्योम *)__data;
	uपूर्णांक8_t *data = __data + माप(*hdr);
	पूर्णांक datalen = len - माप(*hdr);

	uपूर्णांक8_t sof = sd->stream_flag | 1;
	uपूर्णांक8_t mof = sd->stream_flag | 2;
	uपूर्णांक8_t eof = sd->stream_flag | 5;

	अगर (len < 12)
		वापस;

	अगर (hdr->magic[0] != 'R' || hdr->magic[1] != 'B') अणु
		pr_warn("[Stream %02x] Invalid magic %02x%02x\n",
			sd->stream_flag, hdr->magic[0], hdr->magic[1]);
		वापस;
	पूर्ण

	अगर (hdr->flag == sof)
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, datalen);

	अन्यथा अगर (hdr->flag == mof)
		gspca_frame_add(gspca_dev, INTER_PACKET, data, datalen);

	अन्यथा अगर (hdr->flag == eof)
		gspca_frame_add(gspca_dev, LAST_PACKET, data, datalen);

	अन्यथा
		pr_warn("Packet type not recognized...\n");
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc_video = अणु
	.name      = MODULE_NAME,
	.config    = sd_config_video,
	.init      = sd_init,
	.start     = sd_start_video,
	.stopN     = sd_stopN_video,
	.pkt_scan  = sd_pkt_scan,
	/*
	.get_streamparm = sd_get_streamparm,
	.set_streamparm = sd_set_streamparm,
	*/
पूर्ण;
अटल स्थिर काष्ठा sd_desc sd_desc_depth = अणु
	.name      = MODULE_NAME,
	.config    = sd_config_depth,
	.init      = sd_init,
	.start     = sd_start_depth,
	.stopN     = sd_stopN_depth,
	.pkt_scan  = sd_pkt_scan,
	/*
	.get_streamparm = sd_get_streamparm,
	.set_streamparm = sd_set_streamparm,
	*/
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x045e, 0x02ae)पूर्ण,
	अणुUSB_DEVICE(0x045e, 0x02bf)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (depth_mode)
		वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc_depth,
				       माप(काष्ठा sd), THIS_MODULE);
	अन्यथा
		वापस gspca_dev_probe(पूर्णांकf, id, &sd_desc_video,
				       माप(काष्ठा sd), THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name       = MODULE_NAME,
	.id_table   = device_table,
	.probe      = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend    = gspca_suspend,
	.resume     = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);

module_param(depth_mode, bool, 0644);
MODULE_PARM_DESC(depth_mode, "0=video 1=depth");
