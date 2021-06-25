<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Jeilinj subdriver
 *
 * Supports some Jeilin dual-mode cameras which use bulk transport and
 * करोwnload raw JPEG data.
 *
 * Copyright (C) 2009 Theoकरोre Kilgore
 *
 * Sportscam DV15 support and control settings are
 * Copyright (C) 2011 Patrice Chotard
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "jeilinj"

#समावेश <linux/slab.h>
#समावेश "gspca.h"
#समावेश "jpeg.h"

MODULE_AUTHOR("Theodore Kilgore <kilgota@auburn.edu>");
MODULE_DESCRIPTION("GSPCA/JEILINJ USB Camera Driver");
MODULE_LICENSE("GPL");

/* Default समयouts, in ms */
#घोषणा JEILINJ_CMD_TIMEOUT 500
#घोषणा JEILINJ_CMD_DELAY 160
#घोषणा JEILINJ_DATA_TIMEOUT 1000

/* Maximum transfer size to use. */
#घोषणा JEILINJ_MAX_TRANSFER 0x200
#घोषणा FRAME_HEADER_LEN 0x10
#घोषणा FRAME_START 0xFFFFFFFF

क्रमागत अणु
	SAKAR_57379,
	SPORTSCAM_DV15,
पूर्ण;

#घोषणा CAMQUALITY_MIN 0	/* highest cam quality */
#घोषणा CAMQUALITY_MAX 97	/* lowest cam quality  */

/* Structure to hold all of our device specअगरic stuff */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	पूर्णांक blocks_left;
	स्थिर काष्ठा v4l2_pix_क्रमmat *cap_mode;
	काष्ठा v4l2_ctrl *freq;
	काष्ठा v4l2_ctrl *jpegqual;
	/* Driver stuff */
	u8 type;
	u8 quality;				 /* image quality */
#घोषणा QUALITY_MIN 35
#घोषणा QUALITY_MAX 85
#घोषणा QUALITY_DEF 85
	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;

काष्ठा jlj_command अणु
	अचिन्हित अक्षर inकाष्ठाion[2];
	अचिन्हित अक्षर ack_wanted;
	अचिन्हित अक्षर delay;
पूर्ण;

/* AFAICT these cameras will only करो 320x240. */
अटल काष्ठा v4l2_pix_क्रमmat jlj_mode[] = अणु
	अणु 320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
	अणु 640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण
पूर्ण;

/*
 * cam uses endpoपूर्णांक 0x03 to send commands, 0x84 क्रम पढ़ो commands,
 * and 0x82 क्रम bulk transfer.
 */

/* All commands are two bytes only */
अटल व्योम jlj_ग_लिखो2(काष्ठा gspca_dev *gspca_dev, अचिन्हित अक्षर *command)
अणु
	पूर्णांक retval;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	स_नकल(gspca_dev->usb_buf, command, 2);
	retval = usb_bulk_msg(gspca_dev->dev,
			usb_sndbulkpipe(gspca_dev->dev, 3),
			gspca_dev->usb_buf, 2, शून्य, 500);
	अगर (retval < 0) अणु
		pr_err("command write [%02x] error %d\n",
		       gspca_dev->usb_buf[0], retval);
		gspca_dev->usb_err = retval;
	पूर्ण
पूर्ण

/* Responses are one byte only */
अटल व्योम jlj_पढ़ो1(काष्ठा gspca_dev *gspca_dev, अचिन्हित अक्षर *response)
अणु
	पूर्णांक retval;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	retval = usb_bulk_msg(gspca_dev->dev,
	usb_rcvbulkpipe(gspca_dev->dev, 0x84),
				gspca_dev->usb_buf, 1, शून्य, 500);
	*response = gspca_dev->usb_buf[0];
	अगर (retval < 0) अणु
		pr_err("read command [%02x] error %d\n",
		       gspca_dev->usb_buf[0], retval);
		gspca_dev->usb_err = retval;
	पूर्ण
पूर्ण

अटल व्योम setfreq(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 freq_commands[][2] = अणु
		अणु0x71, 0x80पूर्ण,
		अणु0x70, 0x07पूर्ण
	पूर्ण;

	freq_commands[0][1] |= val >> 1;

	jlj_ग_लिखो2(gspca_dev, freq_commands[0]);
	jlj_ग_लिखो2(gspca_dev, freq_commands[1]);
पूर्ण

अटल व्योम setcamquality(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 quality_commands[][2] = अणु
		अणु0x71, 0x1Eपूर्ण,
		अणु0x70, 0x06पूर्ण
	पूर्ण;
	u8 camquality;

	/* adapt camera quality from jpeg quality */
	camquality = ((QUALITY_MAX - val) * CAMQUALITY_MAX)
		/ (QUALITY_MAX - QUALITY_MIN);
	quality_commands[0][1] += camquality;

	jlj_ग_लिखो2(gspca_dev, quality_commands[0]);
	jlj_ग_लिखो2(gspca_dev, quality_commands[1]);
पूर्ण

अटल व्योम setस्वतःgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 स्वतःgain_commands[][2] = अणु
		अणु0x94, 0x02पूर्ण,
		अणु0xcf, 0x00पूर्ण
	पूर्ण;

	स्वतःgain_commands[1][1] = val << 4;

	jlj_ग_लिखो2(gspca_dev, स्वतःgain_commands[0]);
	jlj_ग_लिखो2(gspca_dev, स्वतःgain_commands[1]);
पूर्ण

अटल व्योम setred(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 setred_commands[][2] = अणु
		अणु0x94, 0x02पूर्ण,
		अणु0xe6, 0x00पूर्ण
	पूर्ण;

	setred_commands[1][1] = val;

	jlj_ग_लिखो2(gspca_dev, setred_commands[0]);
	jlj_ग_लिखो2(gspca_dev, setred_commands[1]);
पूर्ण

अटल व्योम setgreen(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 setgreen_commands[][2] = अणु
		अणु0x94, 0x02पूर्ण,
		अणु0xe7, 0x00पूर्ण
	पूर्ण;

	setgreen_commands[1][1] = val;

	jlj_ग_लिखो2(gspca_dev, setgreen_commands[0]);
	jlj_ग_लिखो2(gspca_dev, setgreen_commands[1]);
पूर्ण

अटल व्योम setblue(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u8 setblue_commands[][2] = अणु
		अणु0x94, 0x02पूर्ण,
		अणु0xe9, 0x00पूर्ण
	पूर्ण;

	setblue_commands[1][1] = val;

	jlj_ग_लिखो2(gspca_dev, setblue_commands[0]);
	jlj_ग_लिखो2(gspca_dev, setblue_commands[1]);
पूर्ण

अटल पूर्णांक jlj_start(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	पूर्णांक start_commands_size;
	u8 response = 0xff;
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा jlj_command start_commands[] = अणु
		अणुअणु0x71, 0x81पूर्ण, 0, 0पूर्ण,
		अणुअणु0x70, 0x05पूर्ण, 0, JEILINJ_CMD_DELAYपूर्ण,
		अणुअणु0x95, 0x70पूर्ण, 1, 0पूर्ण,
		अणुअणु0x71, 0x81 - gspca_dev->curr_modeपूर्ण, 0, 0पूर्ण,
		अणुअणु0x70, 0x04पूर्ण, 0, JEILINJ_CMD_DELAYपूर्ण,
		अणुअणु0x95, 0x70पूर्ण, 1, 0पूर्ण,
		अणुअणु0x71, 0x00पूर्ण, 0, 0पूर्ण,   /* start streaming ??*/
		अणुअणु0x70, 0x08पूर्ण, 0, JEILINJ_CMD_DELAYपूर्ण,
		अणुअणु0x95, 0x70पूर्ण, 1, 0पूर्ण,
#घोषणा SPORTSCAM_DV15_CMD_SIZE 9
		अणुअणु0x94, 0x02पूर्ण, 0, 0पूर्ण,
		अणुअणु0xde, 0x24पूर्ण, 0, 0पूर्ण,
		अणुअणु0x94, 0x02पूर्ण, 0, 0पूर्ण,
		अणुअणु0xdd, 0xf0पूर्ण, 0, 0पूर्ण,
		अणुअणु0x94, 0x02पूर्ण, 0, 0पूर्ण,
		अणुअणु0xe3, 0x2cपूर्ण, 0, 0पूर्ण,
		अणुअणु0x94, 0x02पूर्ण, 0, 0पूर्ण,
		अणुअणु0xe4, 0x00पूर्ण, 0, 0पूर्ण,
		अणुअणु0x94, 0x02पूर्ण, 0, 0पूर्ण,
		अणुअणु0xe5, 0x00पूर्ण, 0, 0पूर्ण,
		अणुअणु0x94, 0x02पूर्ण, 0, 0पूर्ण,
		अणुअणु0xe6, 0x2cपूर्ण, 0, 0पूर्ण,
		अणुअणु0x94, 0x03पूर्ण, 0, 0पूर्ण,
		अणुअणु0xaa, 0x00पूर्ण, 0, 0पूर्ण
	पूर्ण;

	sd->blocks_left = 0;
	/* Under Winकरोws, USB spy shows that only the 9 first start
	 * commands are used क्रम SPORTSCAM_DV15 webcam
	 */
	अगर (sd->type == SPORTSCAM_DV15)
		start_commands_size = SPORTSCAM_DV15_CMD_SIZE;
	अन्यथा
		start_commands_size = ARRAY_SIZE(start_commands);

	क्रम (i = 0; i < start_commands_size; i++) अणु
		jlj_ग_लिखो2(gspca_dev, start_commands[i].inकाष्ठाion);
		अगर (start_commands[i].delay)
			msleep(start_commands[i].delay);
		अगर (start_commands[i].ack_wanted)
			jlj_पढ़ो1(gspca_dev, &response);
	पूर्ण
	setcamquality(gspca_dev, v4l2_ctrl_g_ctrl(sd->jpegqual));
	msleep(2);
	setfreq(gspca_dev, v4l2_ctrl_g_ctrl(sd->freq));
	अगर (gspca_dev->usb_err < 0)
		gspca_err(gspca_dev, "Start streaming command failed\n");
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक packet_type;
	u32 header_marker;

	gspca_dbg(gspca_dev, D_STREAM, "Got %d bytes out of %d for Block 0\n",
		  len, JEILINJ_MAX_TRANSFER);
	अगर (len != JEILINJ_MAX_TRANSFER) अणु
		gspca_dbg(gspca_dev, D_PACK, "bad length\n");
		जाओ discard;
	पूर्ण
	/* check अगर it's start of frame */
	header_marker = ((u32 *)data)[0];
	अगर (header_marker == FRAME_START) अणु
		sd->blocks_left = data[0x0a] - 1;
		gspca_dbg(gspca_dev, D_STREAM, "blocks_left = 0x%x\n",
			  sd->blocks_left);
		/* Start a new frame, and add the JPEG header, first thing */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
				sd->jpeg_hdr, JPEG_HDR_SZ);
		/* Toss line 0 of data block 0, keep the rest. */
		gspca_frame_add(gspca_dev, INTER_PACKET,
				data + FRAME_HEADER_LEN,
				JEILINJ_MAX_TRANSFER - FRAME_HEADER_LEN);
	पूर्ण अन्यथा अगर (sd->blocks_left > 0) अणु
		gspca_dbg(gspca_dev, D_STREAM, "%d blocks remaining for frame\n",
			  sd->blocks_left);
		sd->blocks_left -= 1;
		अगर (sd->blocks_left == 0)
			packet_type = LAST_PACKET;
		अन्यथा
			packet_type = INTER_PACKET;
		gspca_frame_add(gspca_dev, packet_type,
				data, JEILINJ_MAX_TRANSFER);
	पूर्ण अन्यथा
		जाओ discard;
	वापस;
discard:
	/* Discard data until a new frame starts. */
	gspca_dev->last_packet_type = DISCARD_PACKET;
पूर्ण

/* This function is called at probe समय just beक्रमe sd_init */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam = &gspca_dev->cam;
	काष्ठा sd *dev  = (काष्ठा sd *) gspca_dev;

	dev->type = id->driver_info;
	dev->quality = QUALITY_DEF;

	cam->cam_mode = jlj_mode;
	cam->nmodes = ARRAY_SIZE(jlj_mode);
	cam->bulk = 1;
	cam->bulk_nurbs = 1;
	cam->bulk_size = JEILINJ_MAX_TRANSFER;
	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	u8 *buf;
	अटल u8 stop_commands[][2] = अणु
		अणु0x71, 0x00पूर्ण,
		अणु0x70, 0x09पूर्ण,
		अणु0x71, 0x80पूर्ण,
		अणु0x70, 0x05पूर्ण
	पूर्ण;

	क्रम (;;) अणु
		/* get the image reमुख्यing blocks */
		usb_bulk_msg(gspca_dev->dev,
				gspca_dev->urb[0]->pipe,
				gspca_dev->urb[0]->transfer_buffer,
				JEILINJ_MAX_TRANSFER, शून्य,
				JEILINJ_DATA_TIMEOUT);

		/* search क्रम 0xff 0xd9  (खातापूर्ण क्रम JPEG) */
		i = 0;
		buf = gspca_dev->urb[0]->transfer_buffer;
		जबतक ((i < (JEILINJ_MAX_TRANSFER - 1)) &&
			((buf[i] != 0xff) || (buf[i+1] != 0xd9)))
			i++;

		अगर (i != (JEILINJ_MAX_TRANSFER - 1))
			/* last reमुख्यing block found */
			अवरोध;
		पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(stop_commands); i++)
		jlj_ग_लिखो2(gspca_dev, stop_commands[i]);
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस gspca_dev->usb_err;
पूर्ण

/* Set up क्रम getting frames. */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *dev = (काष्ठा sd *) gspca_dev;

	/* create the JPEG header */
	jpeg_define(dev->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x21);          /* JPEG 422 */
	jpeg_set_qual(dev->jpeg_hdr, dev->quality);
	gspca_dbg(gspca_dev, D_STREAM, "Start streaming at %dx%d\n",
		  gspca_dev->pixfmt.height, gspca_dev->pixfmt.width);
	jlj_start(gspca_dev);
	वापस gspca_dev->usb_err;
पूर्ण

/* Table of supported USB devices */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x0979, 0x0280), .driver_info = SAKAR_57379पूर्ण,
	अणुUSB_DEVICE(0x0979, 0x0270), .driver_info = SPORTSCAM_DV15पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_POWER_LINE_FREQUENCY:
		setfreq(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		setred(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		setgreen(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BLUE_BALANCE:
		setblue(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		setस्वतःgain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		jpeg_set_qual(sd->jpeg_hdr, ctrl->val);
		setcamquality(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;
	अटल स्थिर काष्ठा v4l2_ctrl_config custom_स्वतःgain = अणु
		.ops = &sd_ctrl_ops,
		.id = V4L2_CID_AUTOGAIN,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Automatic Gain (and Exposure)",
		.max = 3,
		.step = 1,
		.def = 0,
	पूर्ण;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 6);
	sd->freq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 1,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ);
	v4l2_ctrl_new_custom(hdl, &custom_स्वतःgain, शून्य);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 3, 1, 2);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 3, 1, 2);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 3, 1, 2);
	sd->jpegqual = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_JPEG_COMPRESSION_QUALITY,
			QUALITY_MIN, QUALITY_MAX, 1, QUALITY_DEF);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sd_set_jcomp(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा v4l2_jpegcompression *jcomp)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	v4l2_ctrl_s_ctrl(sd->jpegqual, jcomp->quality);
	वापस 0;
पूर्ण

अटल पूर्णांक sd_get_jcomp(काष्ठा gspca_dev *gspca_dev,
			काष्ठा v4l2_jpegcompression *jcomp)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	स_रखो(jcomp, 0, माप *jcomp);
	jcomp->quality = v4l2_ctrl_g_ctrl(sd->jpegqual);
	jcomp->jpeg_markers = V4L2_JPEG_MARKER_DHT
			| V4L2_JPEG_MARKER_DQT;
	वापस 0;
पूर्ण


/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc_sakar_57379 = अणु
	.name   = MODULE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.start  = sd_start,
	.stopN  = sd_stopN,
	.pkt_scan = sd_pkt_scan,
पूर्ण;

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc_sportscam_dv15 = अणु
	.name   = MODULE_NAME,
	.config = sd_config,
	.init   = sd_init,
	.init_controls = sd_init_controls,
	.start  = sd_start,
	.stopN  = sd_stopN,
	.pkt_scan = sd_pkt_scan,
	.get_jcomp = sd_get_jcomp,
	.set_jcomp = sd_set_jcomp,
पूर्ण;

अटल स्थिर काष्ठा sd_desc *sd_desc[2] = अणु
	&sd_desc_sakar_57379,
	&sd_desc_sportscam_dv15
पूर्ण;

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	वापस gspca_dev_probe(पूर्णांकf, id,
			sd_desc[id->driver_info],
			माप(काष्ठा sd),
			THIS_MODULE);
पूर्ण

अटल काष्ठा usb_driver sd_driver = अणु
	.name       = MODULE_NAME,
	.id_table   = device_table,
	.probe      = sd_probe,
	.disconnect = gspca_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend = gspca_suspend,
	.resume  = gspca_resume,
	.reset_resume = gspca_resume,
#पूर्ण_अगर
पूर्ण;

module_usb_driver(sd_driver);
