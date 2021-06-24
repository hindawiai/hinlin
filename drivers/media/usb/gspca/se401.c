<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GSPCA Endpoपूर्णांकs (क्रमmerly known as AOX) se401 USB Camera sub Driver
 *
 * Copyright (C) 2011 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on the v4l1 se401 driver which is:
 *
 * Copyright (c) 2000 Jeroen B. Vreeken (pe1rxq@amsat.org)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "se401"

#घोषणा BULK_SIZE 4096
#घोषणा PACKET_SIZE 1024
#घोषणा READ_REQ_SIZE 64
#घोषणा MAX_MODES ((READ_REQ_SIZE - 6) / 4)
/* The se401 compression algorithm uses a fixed quant factor, which
   can be configured by setting the high nibble of the SE401_OPERATINGMODE
   feature. This needs to exactly match what is in libv4l! */
#घोषणा SE401_QUANT_FACT 8

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश "gspca.h"
#समावेश "se401.h"

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Endpoints se401");
MODULE_LICENSE("GPL");

/* exposure change state machine states */
क्रमागत अणु
	EXPO_CHANGED,
	EXPO_DROP_FRAME,
	EXPO_NO_CHANGE,
पूर्ण;

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	काष्ठा अणु /* exposure/freq control cluster */
		काष्ठा v4l2_ctrl *exposure;
		काष्ठा v4l2_ctrl *freq;
	पूर्ण;
	bool has_brightness;
	काष्ठा v4l2_pix_क्रमmat fmts[MAX_MODES];
	पूर्णांक pixels_पढ़ो;
	पूर्णांक packet_पढ़ो;
	u8 packet[PACKET_SIZE];
	u8 restart_stream;
	u8 button_state;
	u8 resetlevel;
	u8 resetlevel_frame_count;
	पूर्णांक resetlevel_adjust_dir;
	पूर्णांक expo_change_state;
पूर्ण;


अटल व्योम se401_ग_लिखो_req(काष्ठा gspca_dev *gspca_dev, u16 req, u16 value,
			    पूर्णांक silent)
अणु
	पूर्णांक err;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	err = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0), req,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      value, 0, शून्य, 0, 1000);
	अगर (err < 0) अणु
		अगर (!silent)
			pr_err("write req failed req %#04x val %#04x error %d\n",
			       req, value, err);
		gspca_dev->usb_err = err;
	पूर्ण
पूर्ण

अटल व्योम se401_पढ़ो_req(काष्ठा gspca_dev *gspca_dev, u16 req, पूर्णांक silent)
अणु
	पूर्णांक err;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	अगर (USB_BUF_SZ < READ_REQ_SIZE) अणु
		pr_err("USB_BUF_SZ too small!!\n");
		gspca_dev->usb_err = -ENOBUFS;
		वापस;
	पूर्ण

	err = usb_control_msg(gspca_dev->dev,
			      usb_rcvctrlpipe(gspca_dev->dev, 0), req,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, 0, gspca_dev->usb_buf, READ_REQ_SIZE, 1000);
	अगर (err < 0) अणु
		अगर (!silent)
			pr_err("read req failed req %#04x error %d\n",
			       req, err);
		gspca_dev->usb_err = err;
		/*
		 * Make sure the buffer is zeroed to aव्योम uninitialized
		 * values.
		 */
		स_रखो(gspca_dev->usb_buf, 0, READ_REQ_SIZE);
	पूर्ण
पूर्ण

अटल व्योम se401_set_feature(काष्ठा gspca_dev *gspca_dev,
			      u16 selector, u16 param)
अणु
	पूर्णांक err;

	अगर (gspca_dev->usb_err < 0)
		वापस;

	err = usb_control_msg(gspca_dev->dev,
			      usb_sndctrlpipe(gspca_dev->dev, 0),
			      SE401_REQ_SET_EXT_FEATURE,
			      USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      param, selector, शून्य, 0, 1000);
	अगर (err < 0) अणु
		pr_err("set feature failed sel %#04x param %#04x error %d\n",
		       selector, param, err);
		gspca_dev->usb_err = err;
	पूर्ण
पूर्ण

अटल पूर्णांक se401_get_feature(काष्ठा gspca_dev *gspca_dev, u16 selector)
अणु
	पूर्णांक err;

	अगर (gspca_dev->usb_err < 0)
		वापस gspca_dev->usb_err;

	अगर (USB_BUF_SZ < 2) अणु
		pr_err("USB_BUF_SZ too small!!\n");
		gspca_dev->usb_err = -ENOBUFS;
		वापस gspca_dev->usb_err;
	पूर्ण

	err = usb_control_msg(gspca_dev->dev,
			      usb_rcvctrlpipe(gspca_dev->dev, 0),
			      SE401_REQ_GET_EXT_FEATURE,
			      USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      0, selector, gspca_dev->usb_buf, 2, 1000);
	अगर (err < 0) अणु
		pr_err("get feature failed sel %#04x error %d\n",
		       selector, err);
		gspca_dev->usb_err = err;
		वापस err;
	पूर्ण
	वापस gspca_dev->usb_buf[0] | (gspca_dev->usb_buf[1] << 8);
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	/* HDG: this करोes not seem to करो anything on my cam */
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_SET_BRT, val, 0);
पूर्ण

अटल व्योम setgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u16 gain = 63 - val;

	/* red color gain */
	se401_set_feature(gspca_dev, HV7131_REG_ARCG, gain);
	/* green color gain */
	se401_set_feature(gspca_dev, HV7131_REG_AGCG, gain);
	/* blue color gain */
	se401_set_feature(gspca_dev, HV7131_REG_ABCG, gain);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val, s32 freq)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक पूर्णांकegration = val << 6;
	u8 expose_h, expose_m, expose_l;

	/* Do this beक्रमe the set_feature calls, क्रम proper timing wrt
	   the पूर्णांकerrupt driven pkt_scan. Note we may still race but that
	   is not a big issue, the expo change state machine is merely क्रम
	   aव्योमing underexposed frames getting send out, अगर one sneaks
	   through so be it */
	sd->expo_change_state = EXPO_CHANGED;

	अगर (freq == V4L2_CID_POWER_LINE_FREQUENCY_50HZ)
		पूर्णांकegration = पूर्णांकegration - पूर्णांकegration % 106667;
	अगर (freq == V4L2_CID_POWER_LINE_FREQUENCY_60HZ)
		पूर्णांकegration = पूर्णांकegration - पूर्णांकegration % 88889;

	expose_h = (पूर्णांकegration >> 16);
	expose_m = (पूर्णांकegration >> 8);
	expose_l = पूर्णांकegration;

	/* पूर्णांकegration समय low */
	se401_set_feature(gspca_dev, HV7131_REG_TITL, expose_l);
	/* पूर्णांकegration समय mid */
	se401_set_feature(gspca_dev, HV7131_REG_TITM, expose_m);
	/* पूर्णांकegration समय high */
	se401_set_feature(gspca_dev, HV7131_REG_TITU, expose_h);
पूर्ण

अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	काष्ठा cam *cam = &gspca_dev->cam;
	u8 *cd = gspca_dev->usb_buf;
	पूर्णांक i, j, n;
	पूर्णांक widths[MAX_MODES], heights[MAX_MODES];

	/* Read the camera descriptor */
	se401_पढ़ो_req(gspca_dev, SE401_REQ_GET_CAMERA_DESCRIPTOR, 1);
	अगर (gspca_dev->usb_err) अणु
		/* Someबार after being idle क्रम a जबतक the se401 won't
		   respond and needs a good kicking  */
		usb_reset_device(gspca_dev->dev);
		gspca_dev->usb_err = 0;
		se401_पढ़ो_req(gspca_dev, SE401_REQ_GET_CAMERA_DESCRIPTOR, 0);
	पूर्ण

	/* Some cameras start with their LED on */
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_LED_CONTROL, 0, 0);
	अगर (gspca_dev->usb_err)
		वापस gspca_dev->usb_err;

	अगर (cd[1] != 0x41) अणु
		pr_err("Wrong descriptor type\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!(cd[2] & SE401_FORMAT_BAYER)) अणु
		pr_err("Bayer format not supported!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cd[3])
		pr_info("ExtraFeatures: %d\n", cd[3]);

	n = cd[4] | (cd[5] << 8);
	अगर (n > MAX_MODES) अणु
		pr_err("Too many frame sizes\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < n ; i++) अणु
		widths[i] = cd[6 + i * 4 + 0] | (cd[6 + i * 4 + 1] << 8);
		heights[i] = cd[6 + i * 4 + 2] | (cd[6 + i * 4 + 3] << 8);
	पूर्ण

	क्रम (i = 0; i < n ; i++) अणु
		sd->fmts[i].width = widths[i];
		sd->fmts[i].height = heights[i];
		sd->fmts[i].field = V4L2_FIELD_NONE;
		sd->fmts[i].colorspace = V4L2_COLORSPACE_SRGB;
		sd->fmts[i].priv = 1;

		/* janggu compression only works क्रम 1/4th or 1/16th res */
		क्रम (j = 0; j < n; j++) अणु
			अगर (widths[j] / 2 == widths[i] &&
			    heights[j] / 2 == heights[i]) अणु
				sd->fmts[i].priv = 2;
				अवरोध;
			पूर्ण
		पूर्ण
		/* 1/16th अगर available too is better then 1/4th, because
		   we then use a larger area of the sensor */
		क्रम (j = 0; j < n; j++) अणु
			अगर (widths[j] / 4 == widths[i] &&
			    heights[j] / 4 == heights[i]) अणु
				sd->fmts[i].priv = 4;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (sd->fmts[i].priv == 1) अणु
			/* Not a 1/4th or 1/16th res, use bayer */
			sd->fmts[i].pixelक्रमmat = V4L2_PIX_FMT_SBGGR8;
			sd->fmts[i].bytesperline = widths[i];
			sd->fmts[i].sizeimage = widths[i] * heights[i];
			pr_info("Frame size: %dx%d bayer\n",
				widths[i], heights[i]);
		पूर्ण अन्यथा अणु
			/* Found a match use janggu compression */
			sd->fmts[i].pixelक्रमmat = V4L2_PIX_FMT_SE401;
			sd->fmts[i].bytesperline = 0;
			sd->fmts[i].sizeimage = widths[i] * heights[i] * 3;
			pr_info("Frame size: %dx%d 1/%dth janggu\n",
				widths[i], heights[i],
				sd->fmts[i].priv * sd->fmts[i].priv);
		पूर्ण
	पूर्ण

	cam->cam_mode = sd->fmts;
	cam->nmodes = n;
	cam->bulk = 1;
	cam->bulk_size = BULK_SIZE;
	cam->bulk_nurbs = 4;
	sd->resetlevel = 0x2d; /* Set initial resetlevel */

	/* See अगर the camera supports brightness */
	se401_पढ़ो_req(gspca_dev, SE401_REQ_GET_BRT, 1);
	sd->has_brightness = !!gspca_dev->usb_err;
	gspca_dev->usb_err = 0;

	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

/* function called at start समय beक्रमe URB creation */
अटल पूर्णांक sd_isoc_init(काष्ठा gspca_dev *gspca_dev)
अणु
	gspca_dev->alt = 1;	/* Ignore the bogus isoc alt settings */

	वापस gspca_dev->usb_err;
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	पूर्णांक mult = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	पूर्णांक mode = 0;

	se401_ग_लिखो_req(gspca_dev, SE401_REQ_CAMERA_POWER, 1, 1);
	अगर (gspca_dev->usb_err) अणु
		/* Someबार after being idle क्रम a जबतक the se401 won't
		   respond and needs a good kicking  */
		usb_reset_device(gspca_dev->dev);
		gspca_dev->usb_err = 0;
		se401_ग_लिखो_req(gspca_dev, SE401_REQ_CAMERA_POWER, 1, 0);
	पूर्ण
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_LED_CONTROL, 1, 0);

	se401_set_feature(gspca_dev, HV7131_REG_MODE_B, 0x05);

	/* set size + mode */
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_SET_WIDTH,
			gspca_dev->pixfmt.width * mult, 0);
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_SET_HEIGHT,
			gspca_dev->pixfmt.height * mult, 0);
	/*
	 * HDG: disabled this as it करोes not seem to करो anything
	 * se401_ग_लिखो_req(gspca_dev, SE401_REQ_SET_OUTPUT_MODE,
	 *		   SE401_FORMAT_BAYER, 0);
	 */

	चयन (mult) अणु
	हाल 1: /* Raw bayer */
		mode = 0x03; अवरोध;
	हाल 2: /* 1/4th janggu */
		mode = SE401_QUANT_FACT << 4; अवरोध;
	हाल 4: /* 1/16th janggu */
		mode = (SE401_QUANT_FACT << 4) | 0x02; अवरोध;
	पूर्ण
	se401_set_feature(gspca_dev, SE401_OPERATINGMODE, mode);

	se401_set_feature(gspca_dev, HV7131_REG_ARLV, sd->resetlevel);

	sd->packet_पढ़ो = 0;
	sd->pixels_पढ़ो = 0;
	sd->restart_stream = 0;
	sd->resetlevel_frame_count = 0;
	sd->resetlevel_adjust_dir = 0;
	sd->expo_change_state = EXPO_NO_CHANGE;

	se401_ग_लिखो_req(gspca_dev, SE401_REQ_START_CONTINUOUS_CAPTURE, 0, 0);

	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_STOP_CONTINUOUS_CAPTURE, 0, 0);
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_LED_CONTROL, 0, 0);
	se401_ग_लिखो_req(gspca_dev, SE401_REQ_CAMERA_POWER, 0, 0);
पूर्ण

अटल व्योम sd_dq_callback(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	अचिन्हित पूर्णांक ahrc, alrc;
	पूर्णांक oldreset, adjust_dir;

	/* Restart the stream अगर requested करो so by pkt_scan */
	अगर (sd->restart_stream) अणु
		sd_stopN(gspca_dev);
		sd_start(gspca_dev);
		sd->restart_stream = 0;
	पूर्ण

	/* Automatically adjust sensor reset level
	   Hyundai have some really nice करोcs about this and other sensor
	   related stuff on their homepage: www.hei.co.kr */
	sd->resetlevel_frame_count++;
	अगर (sd->resetlevel_frame_count < 20)
		वापस;

	/* For some reason this normally पढ़ो-only रेजिस्टर करोesn't get reset
	   to zero after पढ़ोing them just once... */
	se401_get_feature(gspca_dev, HV7131_REG_HIREFNOH);
	se401_get_feature(gspca_dev, HV7131_REG_HIREFNOL);
	se401_get_feature(gspca_dev, HV7131_REG_LOREFNOH);
	se401_get_feature(gspca_dev, HV7131_REG_LOREFNOL);
	ahrc = 256*se401_get_feature(gspca_dev, HV7131_REG_HIREFNOH) +
	    se401_get_feature(gspca_dev, HV7131_REG_HIREFNOL);
	alrc = 256*se401_get_feature(gspca_dev, HV7131_REG_LOREFNOH) +
	    se401_get_feature(gspca_dev, HV7131_REG_LOREFNOL);

	/* Not an exact science, but it seems to work pretty well... */
	oldreset = sd->resetlevel;
	अगर (alrc > 10) अणु
		जबतक (alrc >= 10 && sd->resetlevel < 63) अणु
			sd->resetlevel++;
			alrc /= 2;
		पूर्ण
	पूर्ण अन्यथा अगर (ahrc > 20) अणु
		जबतक (ahrc >= 20 && sd->resetlevel > 0) अणु
			sd->resetlevel--;
			ahrc /= 2;
		पूर्ण
	पूर्ण
	/* Detect ping-pong-ing and halve adjusपंचांगent to aव्योम overshoot */
	अगर (sd->resetlevel > oldreset)
		adjust_dir = 1;
	अन्यथा
		adjust_dir = -1;
	अगर (sd->resetlevel_adjust_dir &&
	    sd->resetlevel_adjust_dir != adjust_dir)
		sd->resetlevel = oldreset + (sd->resetlevel - oldreset) / 2;

	अगर (sd->resetlevel != oldreset) अणु
		sd->resetlevel_adjust_dir = adjust_dir;
		se401_set_feature(gspca_dev, HV7131_REG_ARLV, sd->resetlevel);
	पूर्ण

	sd->resetlevel_frame_count = 0;
पूर्ण

अटल व्योम sd_complete_frame(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	चयन (sd->expo_change_state) अणु
	हाल EXPO_CHANGED:
		/* The exposure was changed जबतक this frame
		   was being send, so this frame is ok */
		sd->expo_change_state = EXPO_DROP_FRAME;
		अवरोध;
	हाल EXPO_DROP_FRAME:
		/* The exposure was changed जबतक this frame
		   was being captured, drop it! */
		gspca_dev->last_packet_type = DISCARD_PACKET;
		sd->expo_change_state = EXPO_NO_CHANGE;
		अवरोध;
	हाल EXPO_NO_CHANGE:
		अवरोध;
	पूर्ण
	gspca_frame_add(gspca_dev, LAST_PACKET, data, len);
पूर्ण

अटल व्योम sd_pkt_scan_janggu(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	पूर्णांक imagesize = gspca_dev->pixfmt.width * gspca_dev->pixfmt.height;
	पूर्णांक i, plen, bits, pixels, info, count;

	अगर (sd->restart_stream)
		वापस;

	/* Someबार a 1024 bytes garbage bulk packet is send between frames */
	अगर (gspca_dev->last_packet_type == LAST_PACKET && len == 1024) अणु
		gspca_dev->last_packet_type = DISCARD_PACKET;
		वापस;
	पूर्ण

	i = 0;
	जबतक (i < len) अणु
		/* Read header अगर not alपढ़ोy be present from prev bulk pkt */
		अगर (sd->packet_पढ़ो < 4) अणु
			count = 4 - sd->packet_पढ़ो;
			अगर (count > len - i)
				count = len - i;
			स_नकल(&sd->packet[sd->packet_पढ़ो], &data[i], count);
			sd->packet_पढ़ो += count;
			i += count;
			अगर (sd->packet_पढ़ो < 4)
				अवरोध;
		पूर्ण
		bits   = sd->packet[3] + (sd->packet[2] << 8);
		pixels = sd->packet[1] + ((sd->packet[0] & 0x3f) << 8);
		info   = (sd->packet[0] & 0xc0) >> 6;
		plen   = ((bits + 47) >> 4) << 1;
		/* Sanity checks */
		अगर (plen > 1024) अणु
			pr_err("invalid packet len %d restarting stream\n",
			       plen);
			जाओ error;
		पूर्ण
		अगर (info == 3) अणु
			pr_err("unknown frame info value restarting stream\n");
			जाओ error;
		पूर्ण

		/* Read (reमुख्यder of) packet contents */
		count = plen - sd->packet_पढ़ो;
		अगर (count > len - i)
			count = len - i;
		स_नकल(&sd->packet[sd->packet_पढ़ो], &data[i], count);
		sd->packet_पढ़ो += count;
		i += count;
		अगर (sd->packet_पढ़ो < plen)
			अवरोध;

		sd->pixels_पढ़ो += pixels;
		sd->packet_पढ़ो = 0;

		चयन (info) अणु
		हाल 0: /* Frame data */
			gspca_frame_add(gspca_dev, INTER_PACKET, sd->packet,
					plen);
			अवरोध;
		हाल 1: /* खातापूर्ण */
			अगर (sd->pixels_पढ़ो != imagesize) अणु
				pr_err("frame size %d expected %d\n",
				       sd->pixels_पढ़ो, imagesize);
				जाओ error;
			पूर्ण
			sd_complete_frame(gspca_dev, sd->packet, plen);
			वापस; /* Discard the rest of the bulk packet !! */
		हाल 2: /* SOF */
			gspca_frame_add(gspca_dev, FIRST_PACKET, sd->packet,
					plen);
			sd->pixels_पढ़ो = pixels;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस;

error:
	sd->restart_stream = 1;
	/* Give userspace a 0 bytes frame, so our dq callback माला_लो
	   called and it can restart the stream */
	gspca_frame_add(gspca_dev, FIRST_PACKET, शून्य, 0);
	gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
पूर्ण

अटल व्योम sd_pkt_scan_bayer(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक len)
अणु
	काष्ठा cam *cam = &gspca_dev->cam;
	पूर्णांक imagesize = cam->cam_mode[gspca_dev->curr_mode].sizeimage;

	अगर (gspca_dev->image_len == 0) अणु
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		वापस;
	पूर्ण

	अगर (gspca_dev->image_len + len >= imagesize) अणु
		sd_complete_frame(gspca_dev, data, len);
		वापस;
	पूर्ण

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक len)
अणु
	पूर्णांक mult = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;

	अगर (len == 0)
		वापस;

	अगर (mult == 1) /* mult == 1 means raw bayer */
		sd_pkt_scan_bayer(gspca_dev, data, len);
	अन्यथा
		sd_pkt_scan_janggu(gspca_dev, data, len);
पूर्ण

#अगर IS_ENABLED(CONFIG_INPUT)
अटल पूर्णांक sd_पूर्णांक_pkt_scan(काष्ठा gspca_dev *gspca_dev, u8 *data, पूर्णांक len)
अणु
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;
	u8 state;

	अगर (len != 2)
		वापस -EINVAL;

	चयन (data[0]) अणु
	हाल 0:
	हाल 1:
		state = data[0];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (sd->button_state != state) अणु
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, state);
		input_sync(gspca_dev->input_dev);
		sd->button_state = state;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *)gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		setgain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		setexposure(gspca_dev, ctrl->val, sd->freq->val);
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

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	अगर (sd->has_brightness)
		v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 15);
	/* max is really 63 but > 50 is not pretty */
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 50, 1, 25);
	sd->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 32767, 1, 15000);
	sd->freq = v4l2_ctrl_new_std_menu(hdl, &sd_ctrl_ops,
			V4L2_CID_POWER_LINE_FREQUENCY,
			V4L2_CID_POWER_LINE_FREQUENCY_60HZ, 0, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	v4l2_ctrl_cluster(2, &sd->exposure);
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.isoc_init = sd_isoc_init,
	.start = sd_start,
	.stopN = sd_stopN,
	.dq_callback = sd_dq_callback,
	.pkt_scan = sd_pkt_scan,
#अगर IS_ENABLED(CONFIG_INPUT)
	.पूर्णांक_pkt_scan = sd_पूर्णांक_pkt_scan,
#पूर्ण_अगर
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x03e8, 0x0004)पूर्ण, /* Endpoपूर्णांकs/Aox SE401 */
	अणुUSB_DEVICE(0x0471, 0x030b)पूर्ण, /* Philips PCVC665K */
	अणुUSB_DEVICE(0x047d, 0x5001)पूर्ण, /* Kensington 67014 */
	अणुUSB_DEVICE(0x047d, 0x5002)पूर्ण, /* Kensington 6701(5/7) */
	अणुUSB_DEVICE(0x047d, 0x5003)पूर्ण, /* Kensington 67016 */
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

अटल पूर्णांक sd_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sd_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
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
	.pre_reset = sd_pre_reset,
	.post_reset = sd_post_reset,
पूर्ण;

module_usb_driver(sd_driver);
