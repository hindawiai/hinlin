<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// em28xx-video.c - driver क्रम Empia EM2800/EM2820/2840 USB
//		    video capture devices
//
// Copyright (C) 2005 Luकरोvico Caveकरोn <caveकरोn@sssup.it>
//		      Markus Rechberger <mrechberger@gmail.com>
//		      Mauro Carvalho Chehab <mchehab@kernel.org>
//		      Sascha Sommer <saschasommer@मुक्तnet.de>
// Copyright (C) 2012 Frank Schथअfer <fschaefer.oss@googlemail.com>
//
//	Some parts based on SN9C10x PC Camera Controllers GPL driver made
//		by Luca Risolia <luca.risolia@studio.unibo.it>
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License क्रम more details.

#समावेश "em28xx.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/usb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश "em28xx-v4l.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/tuner.h>

#घोषणा DRIVER_AUTHOR "Ludovico Cavedon <cavedon@sssup.it>, " \
		      "Markus Rechberger <mrechberger@gmail.com>, " \
		      "Mauro Carvalho Chehab <mchehab@kernel.org>, " \
		      "Sascha Sommer <saschasommer@freenet.de>"

अटल अचिन्हित पूर्णांक isoc_debug;
module_param(isoc_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(isoc_debug, "enable debug messages [isoc transfers]");

अटल अचिन्हित पूर्णांक disable_vbi;
module_param(disable_vbi, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_vbi, "disable vbi support");

अटल पूर्णांक alt;
module_param(alt, पूर्णांक, 0644);
MODULE_PARM_DESC(alt, "alternate setting to use for video endpoint");

#घोषणा em28xx_videodbg(fmt, arg...) करो अणु				\
	अगर (video_debug)						\
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "video: %s: " fmt, __func__, ## arg);	\
पूर्ण जबतक (0)

#घोषणा em28xx_isocdbg(fmt, arg...) करो अणु\
	अगर (isoc_debug) \
		dev_prपूर्णांकk(KERN_DEBUG, &dev->पूर्णांकf->dev,			\
			   "isoc: %s: " fmt, __func__, ## arg);		\
पूर्ण जबतक (0)

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC " - v4l2 interface");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(EM28XX_VERSION);

#घोषणा EM25XX_FRMDATAHDR_BYTE1			0x02
#घोषणा EM25XX_FRMDATAHDR_BYTE2_STILL_IMAGE	0x20
#घोषणा EM25XX_FRMDATAHDR_BYTE2_FRAME_END	0x02
#घोषणा EM25XX_FRMDATAHDR_BYTE2_FRAME_ID	0x01
#घोषणा EM25XX_FRMDATAHDR_BYTE2_MASK	(EM25XX_FRMDATAHDR_BYTE2_STILL_IMAGE | \
					 EM25XX_FRMDATAHDR_BYTE2_FRAME_END |   \
					 EM25XX_FRMDATAHDR_BYTE2_FRAME_ID)

अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (EM28XX_MAXBOARDS - 1)] = -1U पूर्ण;
अटल अचिन्हित पूर्णांक vbi_nr[]   = अणु[0 ... (EM28XX_MAXBOARDS - 1)] = -1U पूर्ण;
अटल अचिन्हित पूर्णांक radio_nr[] = अणु[0 ... (EM28XX_MAXBOARDS - 1)] = -1U पूर्ण;

module_param_array(video_nr, पूर्णांक, शून्य, 0444);
module_param_array(vbi_nr, पूर्णांक, शून्य, 0444);
module_param_array(radio_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(video_nr, "video device numbers");
MODULE_PARM_DESC(vbi_nr,   "vbi device numbers");
MODULE_PARM_DESC(radio_nr, "radio device numbers");

अटल अचिन्हित पूर्णांक video_debug;
module_param(video_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(video_debug, "enable debug messages [video]");

/* supported video standards */
अटल काष्ठा em28xx_fmt क्रमmat[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_YUYV,
		.depth    = 16,
		.reg	  = EM28XX_OUTFMT_YUV422_Y0UY1V,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_RGB565,
		.depth    = 16,
		.reg      = EM28XX_OUTFMT_RGB_16_656,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_SRGGB8,
		.depth    = 8,
		.reg      = EM28XX_OUTFMT_RGB_8_RGRG,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_SBGGR8,
		.depth    = 8,
		.reg      = EM28XX_OUTFMT_RGB_8_BGBG,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_SGRBG8,
		.depth    = 8,
		.reg      = EM28XX_OUTFMT_RGB_8_GRGR,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_SGBRG8,
		.depth    = 8,
		.reg      = EM28XX_OUTFMT_RGB_8_GBGB,
	पूर्ण, अणु
		.fourcc   = V4L2_PIX_FMT_YUV411P,
		.depth    = 12,
		.reg      = EM28XX_OUTFMT_YUV411,
	पूर्ण,
पूर्ण;

/*FIXME: maxw should be dependent of alt mode */
अटल अंतरभूत अचिन्हित पूर्णांक norm_maxw(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	अगर (dev->is_webcam)
		वापस v4l2->sensor_xres;

	अगर (dev->board.max_range_640_480)
		वापस 640;

	वापस 720;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_maxh(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	अगर (dev->is_webcam)
		वापस v4l2->sensor_yres;

	अगर (dev->board.max_range_640_480)
		वापस 480;

	वापस (v4l2->norm & V4L2_STD_625_50) ? 576 : 480;
पूर्ण

अटल पूर्णांक em28xx_vbi_supported(काष्ठा em28xx *dev)
अणु
	/* Modprobe option to manually disable */
	अगर (disable_vbi == 1)
		वापस 0;

	अगर (dev->is_webcam)
		वापस 0;

	/* FIXME: check subdevices क्रम VBI support */

	अगर (dev->chip_id == CHIP_ID_EM2860 ||
	    dev->chip_id == CHIP_ID_EM2883)
		वापस 1;

	/* Version of em28xx that करोes not support VBI */
	वापस 0;
पूर्ण

/*
 * em28xx_wake_i2c()
 * configure i2c attached devices
 */
अटल व्योम em28xx_wake_i2c(काष्ठा em28xx *dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = &dev->v4l2->v4l2_dev;

	v4l2_device_call_all(v4l2_dev, 0, core,  reset, 0);
	v4l2_device_call_all(v4l2_dev, 0, video, s_routing,
			     INPUT(dev->ctl_input)->vmux, 0, 0);
पूर्ण

अटल पूर्णांक em28xx_colorlevels_set_शेष(काष्ठा em28xx *dev)
अणु
	em28xx_ग_लिखो_reg(dev, EM28XX_R20_YGAIN, CONTRAST_DEFAULT);
	em28xx_ग_लिखो_reg(dev, EM28XX_R21_YOFFSET, BRIGHTNESS_DEFAULT);
	em28xx_ग_लिखो_reg(dev, EM28XX_R22_UVGAIN, SATURATION_DEFAULT);
	em28xx_ग_लिखो_reg(dev, EM28XX_R23_UOFFSET, BLUE_BALANCE_DEFAULT);
	em28xx_ग_लिखो_reg(dev, EM28XX_R24_VOFFSET, RED_BALANCE_DEFAULT);
	em28xx_ग_लिखो_reg(dev, EM28XX_R25_SHARPNESS, SHARPNESS_DEFAULT);

	em28xx_ग_लिखो_reg(dev, EM28XX_R14_GAMMA, 0x20);
	em28xx_ग_लिखो_reg(dev, EM28XX_R15_RGAIN, 0x20);
	em28xx_ग_लिखो_reg(dev, EM28XX_R16_GGAIN, 0x20);
	em28xx_ग_लिखो_reg(dev, EM28XX_R17_BGAIN, 0x20);
	em28xx_ग_लिखो_reg(dev, EM28XX_R18_ROFFSET, 0x00);
	em28xx_ग_लिखो_reg(dev, EM28XX_R19_GOFFSET, 0x00);
	वापस em28xx_ग_लिखो_reg(dev, EM28XX_R1A_BOFFSET, 0x00);
पूर्ण

अटल पूर्णांक em28xx_set_outfmt(काष्ठा em28xx *dev)
अणु
	पूर्णांक ret;
	u8 fmt, vinctrl;
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	fmt = v4l2->क्रमmat->reg;
	अगर (!dev->is_em25xx)
		fmt |= 0x20;
	/*
	 * NOTE: it's not clear अगर this is really needed !
	 * The datasheets say bit 5 is a reserved bit and devices seem to work
	 * fine without it. But the Winकरोws driver sets it क्रम em2710/50+em28xx
	 * devices and we've always been setting it, too.
	 *
	 * em2765 (em25xx, em276x/7x/8x) devices करो NOT work with this bit set,
	 * it's likely used क्रम an additional (compressed ?) क्रमmat there.
	 */
	ret = em28xx_ग_लिखो_reg(dev, EM28XX_R27_OUTFMT, fmt);
	अगर (ret < 0)
		वापस ret;

	ret = em28xx_ग_लिखो_reg(dev, EM28XX_R10_VINMODE, v4l2->vinmode);
	अगर (ret < 0)
		वापस ret;

	vinctrl = v4l2->vinctl;
	अगर (em28xx_vbi_supported(dev) == 1) अणु
		vinctrl |= EM28XX_VINCTRL_VBI_RAW;
		em28xx_ग_लिखो_reg(dev, EM28XX_R34_VBI_START_H, 0x00);
		em28xx_ग_लिखो_reg(dev, EM28XX_R36_VBI_WIDTH,
				 v4l2->vbi_width / 4);
		em28xx_ग_लिखो_reg(dev, EM28XX_R37_VBI_HEIGHT, v4l2->vbi_height);
		अगर (v4l2->norm & V4L2_STD_525_60) अणु
			/* NTSC */
			em28xx_ग_लिखो_reg(dev, EM28XX_R35_VBI_START_V, 0x09);
		पूर्ण अन्यथा अगर (v4l2->norm & V4L2_STD_625_50) अणु
			/* PAL */
			em28xx_ग_लिखो_reg(dev, EM28XX_R35_VBI_START_V, 0x07);
		पूर्ण
	पूर्ण

	वापस em28xx_ग_लिखो_reg(dev, EM28XX_R11_VINCTRL, vinctrl);
पूर्ण

अटल पूर्णांक em28xx_accumulator_set(काष्ठा em28xx *dev, u8 xmin, u8 xmax,
				  u8 ymin, u8 ymax)
अणु
	em28xx_videodbg("em28xx Scale: (%d,%d)-(%d,%d)\n",
			xmin, ymin, xmax, ymax);

	em28xx_ग_लिखो_regs(dev, EM28XX_R28_XMIN, &xmin, 1);
	em28xx_ग_लिखो_regs(dev, EM28XX_R29_XMAX, &xmax, 1);
	em28xx_ग_लिखो_regs(dev, EM28XX_R2A_YMIN, &ymin, 1);
	वापस em28xx_ग_लिखो_regs(dev, EM28XX_R2B_YMAX, &ymax, 1);
पूर्ण

अटल व्योम em28xx_capture_area_set(काष्ठा em28xx *dev, u8 hstart, u8 vstart,
				    u16 width, u16 height)
अणु
	u8 cwidth = width >> 2;
	u8 cheight = height >> 2;
	u8 overflow = (height >> 9 & 0x02) | (width >> 10 & 0x01);
	/* NOTE: size limit: 2047x1023 = 2MPix */

	em28xx_videodbg("capture area set to (%d,%d): %dx%d\n",
			hstart, vstart,
		       ((overflow & 2) << 9 | cwidth << 2),
		       ((overflow & 1) << 10 | cheight << 2));

	em28xx_ग_लिखो_regs(dev, EM28XX_R1C_HSTART, &hstart, 1);
	em28xx_ग_लिखो_regs(dev, EM28XX_R1D_VSTART, &vstart, 1);
	em28xx_ग_लिखो_regs(dev, EM28XX_R1E_CWIDTH, &cwidth, 1);
	em28xx_ग_लिखो_regs(dev, EM28XX_R1F_CHEIGHT, &cheight, 1);
	em28xx_ग_लिखो_regs(dev, EM28XX_R1B_OFLOW, &overflow, 1);

	/* FIXME: function/meaning of these रेजिस्टरs ? */
	/* FIXME: align width+height to multiples of 4 ?! */
	अगर (dev->is_em25xx) अणु
		em28xx_ग_लिखो_reg(dev, 0x34, width >> 4);
		em28xx_ग_लिखो_reg(dev, 0x35, height >> 4);
	पूर्ण
पूर्ण

अटल पूर्णांक em28xx_scaler_set(काष्ठा em28xx *dev, u16 h, u16 v)
अणु
	u8 mode = 0x00;
	/* the em2800 scaler only supports scaling करोwn to 50% */

	अगर (dev->board.is_em2800) अणु
		mode = (v ? 0x20 : 0x00) | (h ? 0x10 : 0x00);
	पूर्ण अन्यथा अणु
		u8 buf[2];

		buf[0] = h;
		buf[1] = h >> 8;
		em28xx_ग_लिखो_regs(dev, EM28XX_R30_HSCALELOW, (अक्षर *)buf, 2);

		buf[0] = v;
		buf[1] = v >> 8;
		em28xx_ग_लिखो_regs(dev, EM28XX_R32_VSCALELOW, (अक्षर *)buf, 2);
		/*
		 * it seems that both H and V scalers must be active
		 * to work correctly
		 */
		mode = (h || v) ? 0x30 : 0x00;
	पूर्ण
	वापस em28xx_ग_लिखो_reg(dev, EM28XX_R26_COMPR, mode);
पूर्ण

/* FIXME: this only function पढ़ो values from dev */
अटल पूर्णांक em28xx_resolution_set(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	पूर्णांक width = norm_maxw(dev);
	पूर्णांक height = norm_maxh(dev);

	/* Properly setup VBI */
	v4l2->vbi_width = 720;
	अगर (v4l2->norm & V4L2_STD_525_60)
		v4l2->vbi_height = 12;
	अन्यथा
		v4l2->vbi_height = 18;

	em28xx_set_outfmt(dev);

	em28xx_accumulator_set(dev, 1, (width - 4) >> 2, 1, (height - 4) >> 2);

	/*
	 * If we करोn't set the start position to 2 in VBI mode, we end up
	 * with line 20/21 being YUYV encoded instead of being in 8-bit
	 * greyscale.  The core of the issue is that line 21 (and line 23 क्रम
	 * PAL WSS) are inside of active video region, and as a result they
	 * get the pixelक्रमmatting associated with that area.  So by cropping
	 * it out, we end up with the same क्रमmat as the rest of the VBI
	 * region
	 */
	अगर (em28xx_vbi_supported(dev) == 1)
		em28xx_capture_area_set(dev, 0, 2, width, height);
	अन्यथा
		em28xx_capture_area_set(dev, 0, 0, width, height);

	वापस em28xx_scaler_set(dev, v4l2->hscale, v4l2->vscale);
पूर्ण

/* Set USB alternate setting क्रम analog video */
अटल पूर्णांक em28xx_set_alternate(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक err;
	पूर्णांक i;
	अचिन्हित पूर्णांक min_pkt_size = v4l2->width * 2 + 4;

	/*
	 * NOTE: क्रम isoc transfers, only alt settings > 0 are allowed
	 * bulk transfers seem to work only with alt=0 !
	 */
	dev->alt = 0;
	अगर (alt > 0 && alt < dev->num_alt) अणु
		em28xx_videodbg("alternate forced to %d\n", dev->alt);
		dev->alt = alt;
		जाओ set_alt;
	पूर्ण
	अगर (dev->analog_xfer_bulk)
		जाओ set_alt;

	/*
	 * When image size is bigger than a certain value,
	 * the frame size should be increased, otherwise, only
	 * green screen will be received.
	 */
	अगर (v4l2->width * 2 * v4l2->height > 720 * 240 * 2)
		min_pkt_size *= 2;

	क्रम (i = 0; i < dev->num_alt; i++) अणु
		/* stop when the selected alt setting offers enough bandwidth */
		अगर (dev->alt_max_pkt_size_isoc[i] >= min_pkt_size) अणु
			dev->alt = i;
			अवरोध;
		/*
		 * otherwise make sure that we end up with the maximum
		 * bandwidth because the min_pkt_size equation might be wrong.
		 *
		 */
		पूर्ण अन्यथा अगर (dev->alt_max_pkt_size_isoc[i] >
			   dev->alt_max_pkt_size_isoc[dev->alt])
			dev->alt = i;
	पूर्ण

set_alt:
	/*
	 * NOTE: क्रम bulk transfers, we need to call usb_set_पूर्णांकerface()
	 * even अगर the previous settings were the same. Otherwise streaming
	 * fails with all urbs having status = -EOVERFLOW !
	 */
	अगर (dev->analog_xfer_bulk) अणु
		dev->max_pkt_size = 512; /* USB 2.0 spec */
		dev->packet_multiplier = EM28XX_BULK_PACKET_MULTIPLIER;
	पूर्ण अन्यथा अणु /* isoc */
		em28xx_videodbg("minimum isoc packet size: %u (alt=%d)\n",
				min_pkt_size, dev->alt);
		dev->max_pkt_size =
				  dev->alt_max_pkt_size_isoc[dev->alt];
		dev->packet_multiplier = EM28XX_NUM_ISOC_PACKETS;
	पूर्ण
	em28xx_videodbg("setting alternate %d with wMaxPacketSize=%u\n",
			dev->alt, dev->max_pkt_size);
	err = usb_set_पूर्णांकerface(udev, dev->अगरnum, dev->alt);
	अगर (err < 0) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"cannot change alternate number to %d (error=%i)\n",
			dev->alt, err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * DMA and thपढ़ो functions
 */

/*
 * Finish the current buffer
 */
अटल अंतरभूत व्योम finish_buffer(काष्ठा em28xx *dev,
				 काष्ठा em28xx_buffer *buf)
अणु
	em28xx_isocdbg("[%p/%d] wakeup\n", buf, buf->top_field);

	buf->vb.sequence = dev->v4l2->field_count++;
	अगर (dev->v4l2->progressive)
		buf->vb.field = V4L2_FIELD_NONE;
	अन्यथा
		buf->vb.field = V4L2_FIELD_INTERLACED;
	buf->vb.vb2_buf.बारtamp = kसमय_get_ns();

	vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
पूर्ण

/*
 * Copy picture data from USB buffer to videobuf buffer
 */
अटल व्योम em28xx_copy_video(काष्ठा em28xx *dev,
			      काष्ठा em28xx_buffer *buf,
			      अचिन्हित अक्षर *usb_buf,
			      अचिन्हित दीर्घ len)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	व्योम *fieldstart, *startग_लिखो, *startपढ़ो;
	पूर्णांक  linesकरोne, currlineकरोne, offset, lencopy, reमुख्य;
	पूर्णांक bytesperline = v4l2->width << 1;

	अगर (buf->pos + len > buf->length)
		len = buf->length - buf->pos;

	startपढ़ो = usb_buf;
	reमुख्य = len;

	अगर (v4l2->progressive || buf->top_field)
		fieldstart = buf->vb_buf;
	अन्यथा /* पूर्णांकerlaced mode, even nr. of lines */
		fieldstart = buf->vb_buf + bytesperline;

	linesकरोne = buf->pos / bytesperline;
	currlineकरोne = buf->pos % bytesperline;

	अगर (v4l2->progressive)
		offset = linesकरोne * bytesperline + currlineकरोne;
	अन्यथा
		offset = linesकरोne * bytesperline * 2 + currlineकरोne;

	startग_लिखो = fieldstart + offset;
	lencopy = bytesperline - currlineकरोne;
	lencopy = lencopy > reमुख्य ? reमुख्य : lencopy;

	अगर ((अक्षर *)startग_लिखो + lencopy > (अक्षर *)buf->vb_buf + buf->length) अणु
		em28xx_isocdbg("Overflow of %zu bytes past buffer end (1)\n",
			       ((अक्षर *)startग_लिखो + lencopy) -
			      ((अक्षर *)buf->vb_buf + buf->length));
		reमुख्य = (अक्षर *)buf->vb_buf + buf->length -
			 (अक्षर *)startग_लिखो;
		lencopy = reमुख्य;
	पूर्ण
	अगर (lencopy <= 0)
		वापस;
	स_नकल(startग_लिखो, startपढ़ो, lencopy);

	reमुख्य -= lencopy;

	जबतक (reमुख्य > 0) अणु
		अगर (v4l2->progressive)
			startग_लिखो += lencopy;
		अन्यथा
			startग_लिखो += lencopy + bytesperline;
		startपढ़ो += lencopy;
		अगर (bytesperline > reमुख्य)
			lencopy = reमुख्य;
		अन्यथा
			lencopy = bytesperline;

		अगर ((अक्षर *)startग_लिखो + lencopy > (अक्षर *)buf->vb_buf +
		    buf->length) अणु
			em28xx_isocdbg("Overflow of %zu bytes past buffer end(2)\n",
				       ((अक्षर *)startग_लिखो + lencopy) -
				       ((अक्षर *)buf->vb_buf + buf->length));
			reमुख्य = (अक्षर *)buf->vb_buf + buf->length -
				 (अक्षर *)startग_लिखो;
			lencopy = reमुख्य;
		पूर्ण
		अगर (lencopy <= 0)
			अवरोध;

		स_नकल(startग_लिखो, startपढ़ो, lencopy);

		reमुख्य -= lencopy;
	पूर्ण

	buf->pos += len;
पूर्ण

/*
 * Copy VBI data from USB buffer to videobuf buffer
 */
अटल व्योम em28xx_copy_vbi(काष्ठा em28xx *dev,
			    काष्ठा em28xx_buffer *buf,
			    अचिन्हित अक्षर *usb_buf,
			    अचिन्हित दीर्घ len)
अणु
	अचिन्हित पूर्णांक offset;

	अगर (buf->pos + len > buf->length)
		len = buf->length - buf->pos;

	offset = buf->pos;
	/* Make sure the bottom field populates the second half of the frame */
	अगर (buf->top_field == 0)
		offset += dev->v4l2->vbi_width * dev->v4l2->vbi_height;

	स_नकल(buf->vb_buf + offset, usb_buf, len);
	buf->pos += len;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_err_status(काष्ठा em28xx *dev,
				    पूर्णांक packet, पूर्णांक status)
अणु
	अक्षर *errmsg = "Unknown";

	चयन (status) अणु
	हाल -ENOENT:
		errmsg = "unlinked synchronously";
		अवरोध;
	हाल -ECONNRESET:
		errmsg = "unlinked asynchronously";
		अवरोध;
	हाल -ENOSR:
		errmsg = "Buffer error (overrun)";
		अवरोध;
	हाल -EPIPE:
		errmsg = "Stalled (device not responding)";
		अवरोध;
	हाल -EOVERFLOW:
		errmsg = "Babble (bad cable?)";
		अवरोध;
	हाल -EPROTO:
		errmsg = "Bit-stuff error (bad cable?)";
		अवरोध;
	हाल -EILSEQ:
		errmsg = "CRC/Timeout (could be anything)";
		अवरोध;
	हाल -ETIME:
		errmsg = "Device does not respond";
		अवरोध;
	पूर्ण
	अगर (packet < 0) अणु
		em28xx_isocdbg("URB status %d [%s].\n",	status, errmsg);
	पूर्ण अन्यथा अणु
		em28xx_isocdbg("URB packet %d, status %d [%s].\n",
			       packet, status, errmsg);
	पूर्ण
पूर्ण

/*
 * get the next available buffer from dma queue
 */
अटल अंतरभूत काष्ठा em28xx_buffer *get_next_buf(काष्ठा em28xx *dev,
						 काष्ठा em28xx_dmaqueue *dma_q)
अणु
	काष्ठा em28xx_buffer *buf;

	अगर (list_empty(&dma_q->active)) अणु
		em28xx_isocdbg("No active queue to serve\n");
		वापस शून्य;
	पूर्ण

	/* Get the next buffer */
	buf = list_entry(dma_q->active.next, काष्ठा em28xx_buffer, list);
	/* Cleans up buffer - Useful क्रम testing क्रम frame/URB loss */
	list_del(&buf->list);
	buf->pos = 0;
	buf->vb_buf = buf->mem;

	वापस buf;
पूर्ण

/*
 * Finish the current buffer अगर completed and prepare क्रम the next field
 */
अटल काष्ठा em28xx_buffer *
finish_field_prepare_next(काष्ठा em28xx *dev,
			  काष्ठा em28xx_buffer *buf,
			  काष्ठा em28xx_dmaqueue *dma_q)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	अगर (v4l2->progressive || v4l2->top_field) अणु /* Bअक्रम new frame */
		अगर (buf)
			finish_buffer(dev, buf);
		buf = get_next_buf(dev, dma_q);
	पूर्ण
	अगर (buf) अणु
		buf->top_field = v4l2->top_field;
		buf->pos = 0;
	पूर्ण

	वापस buf;
पूर्ण

/*
 * Process data packet according to the em2710/em2750/em28xx frame data क्रमmat
 */
अटल अंतरभूत व्योम process_frame_data_em28xx(काष्ठा em28xx *dev,
					     अचिन्हित अक्षर *data_pkt,
					     अचिन्हित पूर्णांक  data_len)
अणु
	काष्ठा em28xx_v4l2      *v4l2 = dev->v4l2;
	काष्ठा em28xx_buffer    *buf = dev->usb_ctl.vid_buf;
	काष्ठा em28xx_buffer    *vbi_buf = dev->usb_ctl.vbi_buf;
	काष्ठा em28xx_dmaqueue  *dma_q = &dev->vidq;
	काष्ठा em28xx_dmaqueue  *vbi_dma_q = &dev->vbiq;

	/*
	 * capture type 0 = vbi start
	 * capture type 1 = vbi in progress
	 * capture type 2 = video start
	 * capture type 3 = video in progress
	 */
	अगर (data_len >= 4) अणु
		/*
		 * NOTE: Headers are always 4 bytes and
		 * never split across packets
		 */
		अगर (data_pkt[0] == 0x88 && data_pkt[1] == 0x88 &&
		    data_pkt[2] == 0x88 && data_pkt[3] == 0x88) अणु
			/* Continuation */
			data_pkt += 4;
			data_len -= 4;
		पूर्ण अन्यथा अगर (data_pkt[0] == 0x33 && data_pkt[1] == 0x95) अणु
			/* Field start (VBI mode) */
			v4l2->capture_type = 0;
			v4l2->vbi_पढ़ो = 0;
			em28xx_isocdbg("VBI START HEADER !!!\n");
			v4l2->top_field = !(data_pkt[2] & 1);
			data_pkt += 4;
			data_len -= 4;
		पूर्ण अन्यथा अगर (data_pkt[0] == 0x22 && data_pkt[1] == 0x5a) अणु
			/* Field start (VBI disabled) */
			v4l2->capture_type = 2;
			em28xx_isocdbg("VIDEO START HEADER !!!\n");
			v4l2->top_field = !(data_pkt[2] & 1);
			data_pkt += 4;
			data_len -= 4;
		पूर्ण
	पूर्ण
	/*
	 * NOTE: With bulk transfers, पूर्णांकermediate data packets
	 * have no continuation header
	 */

	अगर (v4l2->capture_type == 0) अणु
		vbi_buf = finish_field_prepare_next(dev, vbi_buf, vbi_dma_q);
		dev->usb_ctl.vbi_buf = vbi_buf;
		v4l2->capture_type = 1;
	पूर्ण

	अगर (v4l2->capture_type == 1) अणु
		पूर्णांक vbi_size = v4l2->vbi_width * v4l2->vbi_height;
		पूर्णांक vbi_data_len = ((v4l2->vbi_पढ़ो + data_len) > vbi_size) ?
				   (vbi_size - v4l2->vbi_पढ़ो) : data_len;

		/* Copy VBI data */
		अगर (vbi_buf)
			em28xx_copy_vbi(dev, vbi_buf, data_pkt, vbi_data_len);
		v4l2->vbi_पढ़ो += vbi_data_len;

		अगर (vbi_data_len < data_len) अणु
			/* Continue with copying video data */
			v4l2->capture_type = 2;
			data_pkt += vbi_data_len;
			data_len -= vbi_data_len;
		पूर्ण
	पूर्ण

	अगर (v4l2->capture_type == 2) अणु
		buf = finish_field_prepare_next(dev, buf, dma_q);
		dev->usb_ctl.vid_buf = buf;
		v4l2->capture_type = 3;
	पूर्ण

	अगर (v4l2->capture_type == 3 && buf && data_len > 0)
		em28xx_copy_video(dev, buf, data_pkt, data_len);
पूर्ण

/*
 * Process data packet according to the em25xx/em276x/7x/8x frame data क्रमmat
 */
अटल अंतरभूत व्योम process_frame_data_em25xx(काष्ठा em28xx *dev,
					     अचिन्हित अक्षर *data_pkt,
					     अचिन्हित पूर्णांक  data_len)
अणु
	काष्ठा em28xx_buffer    *buf = dev->usb_ctl.vid_buf;
	काष्ठा em28xx_dmaqueue  *dmaq = &dev->vidq;
	काष्ठा em28xx_v4l2      *v4l2 = dev->v4l2;
	bool frame_end = false;

	/* Check क्रम header */
	/*
	 * NOTE: at least with bulk transfers, only the first packet
	 * has a header and has always set the FRAME_END bit
	 */
	अगर (data_len >= 2) अणु	/* em25xx header is only 2 bytes दीर्घ */
		अगर ((data_pkt[0] == EM25XX_FRMDATAHDR_BYTE1) &&
		    ((data_pkt[1] & ~EM25XX_FRMDATAHDR_BYTE2_MASK) == 0x00)) अणु
			v4l2->top_field = !(data_pkt[1] &
					   EM25XX_FRMDATAHDR_BYTE2_FRAME_ID);
			frame_end = data_pkt[1] &
				    EM25XX_FRMDATAHDR_BYTE2_FRAME_END;
			data_pkt += 2;
			data_len -= 2;
		पूर्ण

		/* Finish field and prepare next (BULK only) */
		अगर (dev->analog_xfer_bulk && frame_end) अणु
			buf = finish_field_prepare_next(dev, buf, dmaq);
			dev->usb_ctl.vid_buf = buf;
		पूर्ण
		/*
		 * NOTE: in ISOC mode when a new frame starts and buf==शून्य,
		 * we COULD alपढ़ोy prepare a buffer here to aव्योम skipping the
		 * first frame.
		 */
	पूर्ण

	/* Copy data */
	अगर (buf && data_len > 0)
		em28xx_copy_video(dev, buf, data_pkt, data_len);

	/* Finish frame (ISOC only) => aव्योमs lag of 1 frame */
	अगर (!dev->analog_xfer_bulk && frame_end) अणु
		buf = finish_field_prepare_next(dev, buf, dmaq);
		dev->usb_ctl.vid_buf = buf;
	पूर्ण

	/*
	 * NOTES:
	 *
	 * 1) Tested with USB bulk transfers only !
	 * The wording in the datasheet suggests that isoc might work dअगरferent.
	 * The current code assumes that with isoc transfers each packet has a
	 * header like with the other em28xx devices.
	 *
	 * 2) Support क्रम पूर्णांकerlaced mode is pure theory. It has not been
	 * tested and it is unknown अगर these devices actually support it.
	 */
पूर्ण

/* Processes and copies the URB data content (video and VBI data) */
अटल अंतरभूत पूर्णांक em28xx_urb_data_copy(काष्ठा em28xx *dev, काष्ठा urb *urb)
अणु
	पूर्णांक xfer_bulk, num_packets, i;
	अचिन्हित अक्षर *usb_data_pkt;
	अचिन्हित पूर्णांक usb_data_len;

	अगर (!dev)
		वापस 0;

	अगर (dev->disconnected)
		वापस 0;

	अगर (urb->status < 0)
		prपूर्णांक_err_status(dev, -1, urb->status);

	xfer_bulk = usb_pipebulk(urb->pipe);

	अगर (xfer_bulk) /* bulk */
		num_packets = 1;
	अन्यथा /* isoc */
		num_packets = urb->number_of_packets;

	क्रम (i = 0; i < num_packets; i++) अणु
		अगर (xfer_bulk) अणु /* bulk */
			usb_data_len = urb->actual_length;

			usb_data_pkt = urb->transfer_buffer;
		पूर्ण अन्यथा अणु /* isoc */
			अगर (urb->iso_frame_desc[i].status < 0) अणु
				prपूर्णांक_err_status(dev, i,
						 urb->iso_frame_desc[i].status);
				अगर (urb->iso_frame_desc[i].status != -EPROTO)
					जारी;
			पूर्ण

			usb_data_len = urb->iso_frame_desc[i].actual_length;
			अगर (usb_data_len > dev->max_pkt_size) अणु
				em28xx_isocdbg("packet bigger than packet size");
				जारी;
			पूर्ण

			usb_data_pkt = urb->transfer_buffer +
				       urb->iso_frame_desc[i].offset;
		पूर्ण

		अगर (usb_data_len == 0) अणु
			/* NOTE: happens very often with isoc transfers */
			/* em28xx_usbdbg("packet %d is empty",i); - spammy */
			जारी;
		पूर्ण

		अगर (dev->is_em25xx)
			process_frame_data_em25xx(dev,
						  usb_data_pkt, usb_data_len);
		अन्यथा
			process_frame_data_em28xx(dev,
						  usb_data_pkt, usb_data_len);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक get_resource(क्रमागत v4l2_buf_type f_type)
अणु
	चयन (f_type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		वापस EM28XX_RESOURCE_VIDEO;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		वापस EM28XX_RESOURCE_VBI;
	शेष:
		WARN_ON(1);
		वापस -1; /* Indicate that device is busy */
	पूर्ण
पूर्ण

/* Usage lock check functions */
अटल पूर्णांक res_get(काष्ठा em28xx *dev, क्रमागत v4l2_buf_type f_type)
अणु
	पूर्णांक res_type = get_resource(f_type);

	/* is it मुक्त? */
	अगर (dev->resources & res_type) अणु
		/* no, someone अन्यथा uses it */
		वापस -EBUSY;
	पूर्ण

	/* it's मुक्त, grab it */
	dev->resources |= res_type;
	em28xx_videodbg("res: get %d\n", res_type);
	वापस 0;
पूर्ण

अटल व्योम res_मुक्त(काष्ठा em28xx *dev, क्रमागत v4l2_buf_type f_type)
अणु
	पूर्णांक res_type = get_resource(f_type);

	dev->resources &= ~res_type;
	em28xx_videodbg("res: put %d\n", res_type);
पूर्ण

अटल व्योम em28xx_v4l2_media_release(काष्ठा em28xx *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	पूर्णांक i;

	क्रम (i = 0; i < MAX_EM28XX_INPUT; i++) अणु
		अगर (!INPUT(i)->type)
			वापस;
		media_device_unरेजिस्टर_entity(&dev->input_ent[i]);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Media Controller helper functions
 */

अटल पूर्णांक em28xx_enable_analog_tuner(काष्ठा em28xx *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *mdev = dev->media_dev;
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	काष्ठा media_entity *source;
	काष्ठा media_link *link, *found_link = शून्य;
	पूर्णांक ret, active_links = 0;

	अगर (!mdev || !v4l2->decoder)
		वापस 0;

	/*
	 * This will find the tuner that is connected पूर्णांकo the decoder.
	 * Technically, this is not 100% correct, as the device may be
	 * using an analog input instead of the tuner. However, as we can't
	 * करो DVB streaming जबतक the DMA engine is being used क्रम V4L2,
	 * this should be enough क्रम the actual needs.
	 */
	list_क्रम_each_entry(link, &v4l2->decoder->links, list) अणु
		अगर (link->sink->entity == v4l2->decoder) अणु
			found_link = link;
			अगर (link->flags & MEDIA_LNK_FL_ENABLED)
				active_links++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (active_links == 1 || !found_link)
		वापस 0;

	source = found_link->source->entity;
	list_क्रम_each_entry(link, &source->links, list) अणु
		काष्ठा media_entity *sink;
		पूर्णांक flags = 0;

		sink = link->sink->entity;

		अगर (sink == v4l2->decoder)
			flags = MEDIA_LNK_FL_ENABLED;

		ret = media_entity_setup_link(link, flags);
		अगर (ret) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"Couldn't change link %s->%s to %s. Error %d\n",
				source->name, sink->name,
				flags ? "enabled" : "disabled",
				ret);
			वापस ret;
		पूर्ण

		em28xx_videodbg("link %s->%s was %s\n",
				source->name, sink->name,
				flags ? "ENABLED" : "disabled");
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर iname[] = अणु
	[EM28XX_VMUX_COMPOSITE]  = "Composite",
	[EM28XX_VMUX_SVIDEO]     = "S-Video",
	[EM28XX_VMUX_TELEVISION] = "Television",
	[EM28XX_RADIO]           = "Radio",
पूर्ण;

अटल व्योम em28xx_v4l2_create_entities(काष्ठा em28xx *dev)
अणु
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	पूर्णांक ret, i;

	/* Initialize Video, VBI and Radio pads */
	v4l2->video_pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&v4l2->vdev.entity, 1, &v4l2->video_pad);
	अगर (ret < 0)
		dev_err(&dev->पूर्णांकf->dev,
			"failed to initialize video media entity!\n");

	अगर (em28xx_vbi_supported(dev)) अणु
		v4l2->vbi_pad.flags = MEDIA_PAD_FL_SINK;
		ret = media_entity_pads_init(&v4l2->vbi_dev.entity, 1,
					     &v4l2->vbi_pad);
		अगर (ret < 0)
			dev_err(&dev->पूर्णांकf->dev,
				"failed to initialize vbi media entity!\n");
	पूर्ण

	/* Webcams करोn't have input connectors */
	अगर (dev->is_webcam)
		वापस;

	/* Create entities क्रम each input connector */
	क्रम (i = 0; i < MAX_EM28XX_INPUT; i++) अणु
		काष्ठा media_entity *ent = &dev->input_ent[i];

		अगर (!INPUT(i)->type)
			अवरोध;

		ent->name = iname[INPUT(i)->type];
		ent->flags = MEDIA_ENT_FL_CONNECTOR;
		dev->input_pad[i].flags = MEDIA_PAD_FL_SOURCE;

		चयन (INPUT(i)->type) अणु
		हाल EM28XX_VMUX_COMPOSITE:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			अवरोध;
		हाल EM28XX_VMUX_SVIDEO:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			अवरोध;
		शेष: /* EM28XX_VMUX_TELEVISION or EM28XX_RADIO */
			अगर (dev->tuner_type != TUNER_ABSENT)
				ent->function = MEDIA_ENT_F_CONN_RF;
			अवरोध;
		पूर्ण

		ret = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		अगर (ret < 0)
			dev_err(&dev->पूर्णांकf->dev,
				"failed to initialize input pad[%d]!\n", i);

		ret = media_device_रेजिस्टर_entity(dev->media_dev, ent);
		अगर (ret < 0)
			dev_err(&dev->पूर्णांकf->dev,
				"failed to register input entity %d!\n", i);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Videobuf2 operations
 */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *vq,
		       अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
		       अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा em28xx *dev = vb2_get_drv_priv(vq);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	अचिन्हित दीर्घ size =
		    (v4l2->width * v4l2->height * v4l2->क्रमmat->depth + 7) >> 3;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;

	em28xx_enable_analog_tuner(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक
buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा em28xx        *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा em28xx_v4l2   *v4l2 = dev->v4l2;
	अचिन्हित दीर्घ size;

	em28xx_videodbg("%s, field=%d\n", __func__, vbuf->field);

	size = (v4l2->width * v4l2->height * v4l2->क्रमmat->depth + 7) >> 3;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		em28xx_videodbg("%s data will not fit into plane (%lu < %lu)\n",
				__func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

पूर्णांक em28xx_start_analog_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा em28xx *dev = vb2_get_drv_priv(vq);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	काष्ठा v4l2_frequency f;
	काष्ठा v4l2_fh *owner;
	पूर्णांक rc = 0;

	em28xx_videodbg("%s\n", __func__);

	dev->v4l2->field_count = 0;

	/*
	 * Make sure streaming is not alपढ़ोy in progress क्रम this type
	 * of filehandle (e.g. video, vbi)
	 */
	rc = res_get(dev, vq->type);
	अगर (rc)
		वापस rc;

	अगर (v4l2->streaming_users == 0) अणु
		/* First active streaming user, so allocate all the URBs */

		/* Allocate the USB bandwidth */
		em28xx_set_alternate(dev);

		/*
		 * Needed, since GPIO might have disabled घातer of
		 * some i2c device
		 */
		em28xx_wake_i2c(dev);

		v4l2->capture_type = -1;
		rc = em28xx_init_usb_xfer(dev, EM28XX_ANALOG_MODE,
					  dev->analog_xfer_bulk,
					  EM28XX_NUM_BUFS,
					  dev->max_pkt_size,
					  dev->packet_multiplier,
					  em28xx_urb_data_copy);
		अगर (rc < 0)
			वापस rc;

		/*
		 * djh: it's not clear whether this code is still needed.  I'm
		 * leaving it in here क्रम now entirely out of concern क्रम
		 * backward compatibility (the old code did it)
		 */

		/* Ask tuner to go to analog or radio mode */
		स_रखो(&f, 0, माप(f));
		f.frequency = v4l2->frequency;
		owner = (काष्ठा v4l2_fh *)vq->owner;
		अगर (owner && owner->vdev->vfl_type == VFL_TYPE_RADIO)
			f.type = V4L2_TUNER_RADIO;
		अन्यथा
			f.type = V4L2_TUNER_ANALOG_TV;
		v4l2_device_call_all(&v4l2->v4l2_dev,
				     0, tuner, s_frequency, &f);

		/* Enable video stream at TV decoder */
		v4l2_device_call_all(&v4l2->v4l2_dev, 0, video, s_stream, 1);
	पूर्ण

	v4l2->streaming_users++;

	वापस rc;
पूर्ण

अटल व्योम em28xx_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा em28xx *dev = vb2_get_drv_priv(vq);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	काष्ठा em28xx_dmaqueue *vidq = &dev->vidq;
	अचिन्हित दीर्घ flags = 0;

	em28xx_videodbg("%s\n", __func__);

	res_मुक्त(dev, vq->type);

	अगर (v4l2->streaming_users-- == 1) अणु
		/* Disable video stream at TV decoder */
		v4l2_device_call_all(&v4l2->v4l2_dev, 0, video, s_stream, 0);

		/* Last active user, so shutकरोwn all the URBS */
		em28xx_uninit_usb_xfer(dev, EM28XX_ANALOG_MODE);
	पूर्ण

	spin_lock_irqsave(&dev->slock, flags);
	अगर (dev->usb_ctl.vid_buf) अणु
		vb2_buffer_करोne(&dev->usb_ctl.vid_buf->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
		dev->usb_ctl.vid_buf = शून्य;
	पूर्ण
	जबतक (!list_empty(&vidq->active)) अणु
		काष्ठा em28xx_buffer *buf;

		buf = list_entry(vidq->active.next, काष्ठा em28xx_buffer, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

व्योम em28xx_stop_vbi_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा em28xx *dev = vb2_get_drv_priv(vq);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	काष्ठा em28xx_dmaqueue *vbiq = &dev->vbiq;
	अचिन्हित दीर्घ flags = 0;

	em28xx_videodbg("%s\n", __func__);

	res_मुक्त(dev, vq->type);

	अगर (v4l2->streaming_users-- == 1) अणु
		/* Disable video stream at TV decoder */
		v4l2_device_call_all(&v4l2->v4l2_dev, 0, video, s_stream, 0);

		/* Last active user, so shutकरोwn all the URBS */
		em28xx_uninit_usb_xfer(dev, EM28XX_ANALOG_MODE);
	पूर्ण

	spin_lock_irqsave(&dev->slock, flags);
	अगर (dev->usb_ctl.vbi_buf) अणु
		vb2_buffer_करोne(&dev->usb_ctl.vbi_buf->vb.vb2_buf,
				VB2_BUF_STATE_ERROR);
		dev->usb_ctl.vbi_buf = शून्य;
	पूर्ण
	जबतक (!list_empty(&vbiq->active)) अणु
		काष्ठा em28xx_buffer *buf;

		buf = list_entry(vbiq->active.next, काष्ठा em28xx_buffer, list);
		list_del(&buf->list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल व्योम
buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा em28xx *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा em28xx_buffer *buf =
		container_of(vbuf, काष्ठा em28xx_buffer, vb);
	काष्ठा em28xx_dmaqueue *vidq = &dev->vidq;
	अचिन्हित दीर्घ flags = 0;

	em28xx_videodbg("%s\n", __func__);
	buf->mem = vb2_plane_vaddr(vb, 0);
	buf->length = vb2_plane_size(vb, 0);

	spin_lock_irqsave(&dev->slock, flags);
	list_add_tail(&buf->list, &vidq->active);
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

अटल स्थिर काष्ठा vb2_ops em28xx_video_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare    = buffer_prepare,
	.buf_queue      = buffer_queue,
	.start_streaming = em28xx_start_analog_streaming,
	.stop_streaming = em28xx_stop_streaming,
	.रुको_prepare   = vb2_ops_रुको_prepare,
	.रुको_finish    = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक em28xx_vb2_setup(काष्ठा em28xx *dev)
अणु
	पूर्णांक rc;
	काष्ठा vb2_queue *q;
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	/* Setup Videobuf2 क्रम Video capture */
	q = &v4l2->vb_vidq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_READ | VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा em28xx_buffer);
	q->ops = &em28xx_video_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;

	rc = vb2_queue_init(q);
	अगर (rc < 0)
		वापस rc;

	/* Setup Videobuf2 क्रम VBI capture */
	q = &v4l2->vb_vbiq;
	q->type = V4L2_BUF_TYPE_VBI_CAPTURE;
	q->io_modes = VB2_READ | VB2_MMAP | VB2_USERPTR;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->drv_priv = dev;
	q->buf_काष्ठा_size = माप(काष्ठा em28xx_buffer);
	q->ops = &em28xx_vbi_qops;
	q->mem_ops = &vb2_vदो_स्मृति_memops;

	rc = vb2_queue_init(q);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

/*
 * v4l2 पूर्णांकerface
 */

अटल व्योम video_mux(काष्ठा em28xx *dev, पूर्णांक index)
अणु
	काष्ठा v4l2_device *v4l2_dev = &dev->v4l2->v4l2_dev;

	dev->ctl_input = index;
	dev->ctl_ainput = INPUT(index)->amux;
	dev->ctl_aoutput = INPUT(index)->aout;

	अगर (!dev->ctl_aoutput)
		dev->ctl_aoutput = EM28XX_AOUT_MASTER;

	v4l2_device_call_all(v4l2_dev, 0, video, s_routing,
			     INPUT(index)->vmux, 0, 0);

	अगर (dev->has_msp34xx) अणु
		अगर (dev->i2s_speed) अणु
			v4l2_device_call_all(v4l2_dev, 0, audio,
					     s_i2s_घड़ी_freq, dev->i2s_speed);
		पूर्ण
		/* Note: this is msp3400 specअगरic */
		v4l2_device_call_all(v4l2_dev, 0, audio, s_routing,
				     dev->ctl_ainput,
				     MSP_OUTPUT(MSP_SC_IN_DSP_SCART1), 0);
	पूर्ण

	अगर (dev->board.adecoder != EM28XX_NOADECODER) अणु
		v4l2_device_call_all(v4l2_dev, 0, audio, s_routing,
				     dev->ctl_ainput, dev->ctl_aoutput, 0);
	पूर्ण

	em28xx_audio_analog_set(dev);
पूर्ण

अटल व्योम em28xx_ctrl_notअगरy(काष्ठा v4l2_ctrl *ctrl, व्योम *priv)
अणु
	काष्ठा em28xx *dev = priv;

	/*
	 * In the हाल of non-AC97 volume controls, we still need
	 * to करो some setups at em28xx, in order to mute/unmute
	 * and to adjust audio volume. However, the value ranges
	 * should be checked by the corresponding V4L subdriver.
	 */
	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		dev->mute = ctrl->val;
		em28xx_audio_analog_set(dev);
		अवरोध;
	हाल V4L2_CID_AUDIO_VOLUME:
		dev->volume = ctrl->val;
		em28xx_audio_analog_set(dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक em28xx_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा em28xx_v4l2 *v4l2 =
		  container_of(ctrl->handler, काष्ठा em28xx_v4l2, ctrl_handler);
	काष्ठा em28xx *dev = v4l2->dev;
	पूर्णांक ret = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_MUTE:
		dev->mute = ctrl->val;
		ret = em28xx_audio_analog_set(dev);
		अवरोध;
	हाल V4L2_CID_AUDIO_VOLUME:
		dev->volume = ctrl->val;
		ret = em28xx_audio_analog_set(dev);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		ret = em28xx_ग_लिखो_reg(dev, EM28XX_R20_YGAIN, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BRIGHTNESS:
		ret = em28xx_ग_लिखो_reg(dev, EM28XX_R21_YOFFSET, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		ret = em28xx_ग_लिखो_reg(dev, EM28XX_R22_UVGAIN, ctrl->val);
		अवरोध;
	हाल V4L2_CID_BLUE_BALANCE:
		ret = em28xx_ग_लिखो_reg(dev, EM28XX_R23_UOFFSET, ctrl->val);
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		ret = em28xx_ग_लिखो_reg(dev, EM28XX_R24_VOFFSET, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		ret = em28xx_ग_लिखो_reg(dev, EM28XX_R25_SHARPNESS, ctrl->val);
		अवरोध;
	पूर्ण

	वापस (ret < 0) ? ret : 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops em28xx_ctrl_ops = अणु
	.s_ctrl = em28xx_s_ctrl,
पूर्ण;

अटल व्योम माप_प्रकारo_scale(काष्ठा em28xx *dev,
			  अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
			अचिन्हित पूर्णांक *hscale, अचिन्हित पूर्णांक *vscale)
अणु
	अचिन्हित पूर्णांक          maxw = norm_maxw(dev);
	अचिन्हित पूर्णांक          maxh = norm_maxh(dev);

	*hscale = (((अचिन्हित दीर्घ)maxw) << 12) / width - 4096L;
	अगर (*hscale > EM28XX_HVSCALE_MAX)
		*hscale = EM28XX_HVSCALE_MAX;

	*vscale = (((अचिन्हित दीर्घ)maxh) << 12) / height - 4096L;
	अगर (*vscale > EM28XX_HVSCALE_MAX)
		*vscale = EM28XX_HVSCALE_MAX;
पूर्ण

अटल व्योम scale_to_size(काष्ठा em28xx *dev,
			  अचिन्हित पूर्णांक hscale, अचिन्हित पूर्णांक vscale,
			  अचिन्हित पूर्णांक *width, अचिन्हित पूर्णांक *height)
अणु
	अचिन्हित पूर्णांक          maxw = norm_maxw(dev);
	अचिन्हित पूर्णांक          maxh = norm_maxh(dev);

	*width = (((अचिन्हित दीर्घ)maxw) << 12) / (hscale + 4096L);
	*height = (((अचिन्हित दीर्घ)maxh) << 12) / (vscale + 4096L);

	/* Don't let width or height to be zero */
	अगर (*width < 1)
		*width = 1;
	अगर (*height < 1)
		*height = 1;
पूर्ण

/*
 * IOCTL vidioc handling
 */

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा em28xx         *dev = video_drvdata(file);
	काष्ठा em28xx_v4l2    *v4l2 = dev->v4l2;

	f->fmt.pix.width = v4l2->width;
	f->fmt.pix.height = v4l2->height;
	f->fmt.pix.pixelक्रमmat = v4l2->क्रमmat->fourcc;
	f->fmt.pix.bytesperline = (v4l2->width * v4l2->क्रमmat->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * v4l2->height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	/* FIXME: TOP? NONE? BOTTOM? ALTENATE? */
	अगर (v4l2->progressive)
		f->fmt.pix.field = V4L2_FIELD_NONE;
	अन्यथा
		f->fmt.pix.field = v4l2->पूर्णांकerlaced_fieldmode ?
			   V4L2_FIELD_INTERLACED : V4L2_FIELD_TOP;
	वापस 0;
पूर्ण

अटल काष्ठा em28xx_fmt *क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmat); i++)
		अगर (क्रमmat[i].fourcc == fourcc)
			वापस &क्रमmat[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा em28xx         *dev   = video_drvdata(file);
	काष्ठा em28xx_v4l2    *v4l2  = dev->v4l2;
	अचिन्हित पूर्णांक          width  = f->fmt.pix.width;
	अचिन्हित पूर्णांक          height = f->fmt.pix.height;
	अचिन्हित पूर्णांक          maxw   = norm_maxw(dev);
	अचिन्हित पूर्णांक          maxh   = norm_maxh(dev);
	अचिन्हित पूर्णांक          hscale, vscale;
	काष्ठा em28xx_fmt     *fmt;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (!fmt) अणु
		fmt = &क्रमmat[0];
		em28xx_videodbg("Fourcc format (%08x) invalid. Using default (%08x).\n",
				f->fmt.pix.pixelक्रमmat, fmt->fourcc);
	पूर्ण

	अगर (dev->board.is_em2800) अणु
		/* the em2800 can only scale करोwn to 50% */
		height = height > (3 * maxh / 4) ? maxh : maxh / 2;
		width = width > (3 * maxw / 4) ? maxw : maxw / 2;
		/*
		 * MaxPacketSize क्रम em2800 is too small to capture at full
		 * resolution use half of maxw as the scaler can only scale
		 * to 50%
		 */
		अगर (width == maxw && height == maxh)
			width /= 2;
	पूर्ण अन्यथा अणु
		/*
		 * width must even because of the YUYV क्रमmat
		 * height must be even because of पूर्णांकerlacing
		 */
		v4l_bound_align_image(&width, 48, maxw, 1, &height, 32, maxh,
				      1, 0);
	पूर्ण
	/* Aव्योम भागision by zero at माप_प्रकारo_scale */
	अगर (width < 1)
		width = 1;
	अगर (height < 1)
		height = 1;

	माप_प्रकारo_scale(dev, width, height, &hscale, &vscale);
	scale_to_size(dev, hscale, vscale, &width, &height);

	f->fmt.pix.width = width;
	f->fmt.pix.height = height;
	f->fmt.pix.pixelक्रमmat = fmt->fourcc;
	f->fmt.pix.bytesperline = (width * fmt->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	अगर (v4l2->progressive)
		f->fmt.pix.field = V4L2_FIELD_NONE;
	अन्यथा
		f->fmt.pix.field = v4l2->पूर्णांकerlaced_fieldmode ?
			   V4L2_FIELD_INTERLACED : V4L2_FIELD_TOP;

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_set_video_क्रमmat(काष्ठा em28xx *dev, अचिन्हित पूर्णांक fourcc,
				   अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा em28xx_fmt     *fmt;
	काष्ठा em28xx_v4l2    *v4l2 = dev->v4l2;

	fmt = क्रमmat_by_fourcc(fourcc);
	अगर (!fmt)
		वापस -EINVAL;

	v4l2->क्रमmat = fmt;
	v4l2->width  = width;
	v4l2->height = height;

	/* set new image size */
	माप_प्रकारo_scale(dev, v4l2->width, v4l2->height,
		      &v4l2->hscale, &v4l2->vscale);

	em28xx_resolution_set(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	अगर (vb2_is_busy(&v4l2->vb_vidq))
		वापस -EBUSY;

	vidioc_try_fmt_vid_cap(file, priv, f);

	वापस em28xx_set_video_क्रमmat(dev, f->fmt.pix.pixelक्रमmat,
				f->fmt.pix.width, f->fmt.pix.height);
पूर्ण

अटल पूर्णांक vidioc_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	*norm = dev->v4l2->norm;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	v4l2_device_call_all(&dev->v4l2->v4l2_dev, 0, video, querystd, norm);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id norm)
अणु
	काष्ठा em28xx      *dev  = video_drvdata(file);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	काष्ठा v4l2_क्रमmat f;

	अगर (norm == v4l2->norm)
		वापस 0;

	अगर (v4l2->streaming_users > 0)
		वापस -EBUSY;

	v4l2->norm = norm;

	/* Adjusts width/height, अगर needed */
	f.fmt.pix.width = 720;
	f.fmt.pix.height = (norm & V4L2_STD_525_60) ? 480 : 576;
	vidioc_try_fmt_vid_cap(file, priv, &f);

	/* set new image size */
	v4l2->width = f.fmt.pix.width;
	v4l2->height = f.fmt.pix.height;
	माप_प्रकारo_scale(dev, v4l2->width, v4l2->height,
		      &v4l2->hscale, &v4l2->vscale);

	em28xx_resolution_set(dev);
	v4l2_device_call_all(&v4l2->v4l2_dev, 0, video, s_std, v4l2->norm);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *p)
अणु
	काष्ठा v4l2_subdev_frame_पूर्णांकerval ival = अणु 0 पूर्ण;
	काष्ठा em28xx      *dev  = video_drvdata(file);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	पूर्णांक rc = 0;

	अगर (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस -EINVAL;

	p->parm.capture.पढ़ोbuffers = EM28XX_MIN_BUF;
	p->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	अगर (dev->is_webcam) अणु
		rc = v4l2_device_call_until_err(&v4l2->v4l2_dev, 0,
						video, g_frame_पूर्णांकerval, &ival);
		अगर (!rc)
			p->parm.capture.समयperframe = ival.पूर्णांकerval;
	पूर्ण अन्यथा अणु
		v4l2_video_std_frame_period(v4l2->norm,
					    &p->parm.capture.समयperframe);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक vidioc_s_parm(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_streamparm *p)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);
	काष्ठा v4l2_subdev_frame_पूर्णांकerval ival = अणु
		0,
		p->parm.capture.समयperframe
	पूर्ण;
	पूर्णांक rc = 0;

	अगर (!dev->is_webcam)
		वापस -ENOTTY;

	अगर (p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    p->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस -EINVAL;

	स_रखो(&p->parm, 0, माप(p->parm));
	p->parm.capture.पढ़ोbuffers = EM28XX_MIN_BUF;
	p->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	rc = v4l2_device_call_until_err(&dev->v4l2->v4l2_dev, 0,
					video, s_frame_पूर्णांकerval, &ival);
	अगर (!rc)
		p->parm.capture.समयperframe = ival.पूर्णांकerval;
	वापस rc;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_input *i)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);
	अचिन्हित पूर्णांक       n;
	पूर्णांक j;

	n = i->index;
	अगर (n >= MAX_EM28XX_INPUT)
		वापस -EINVAL;
	अगर (!INPUT(n)->type)
		वापस -EINVAL;

	i->type = V4L2_INPUT_TYPE_CAMERA;

	strscpy(i->name, iname[INPUT(n)->type], माप(i->name));

	अगर (INPUT(n)->type == EM28XX_VMUX_TELEVISION)
		i->type = V4L2_INPUT_TYPE_TUNER;

	i->std = dev->v4l2->vdev.tvnorms;
	/* webcams करो not have the STD API */
	अगर (dev->is_webcam)
		i->capabilities = 0;

	/* Dynamically generates an audioset biपंचांगask */
	i->audioset = 0;
	क्रम (j = 0; j < MAX_EM28XX_INPUT; j++)
		अगर (dev->amux_map[j] != EM28XX_AMUX_UNUSED)
			i->audioset |= 1 << j;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	*i = dev->ctl_input;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	अगर (i >= MAX_EM28XX_INPUT)
		वापस -EINVAL;
	अगर (!INPUT(i)->type)
		वापस -EINVAL;

	video_mux(dev, i);
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_fill_audio_input(काष्ठा em28xx *dev,
				   स्थिर अक्षर *s,
				   काष्ठा v4l2_audio *a,
				   अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक idx = dev->amux_map[index];

	/*
	 * With msp3400, almost all mappings use the शेष (amux = 0).
	 * The only one may use a dअगरferent value is WinTV USB2, where it
	 * can also be SCART1 input.
	 * As it is very करोubtful that we would see new boards with msp3400,
	 * let's just reuse the existing चयन.
	 */
	अगर (dev->has_msp34xx && idx != EM28XX_AMUX_UNUSED)
		idx = EM28XX_AMUX_LINE_IN;

	चयन (idx) अणु
	हाल EM28XX_AMUX_VIDEO:
		strscpy(a->name, "Television", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_LINE_IN:
		strscpy(a->name, "Line In", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_VIDEO2:
		strscpy(a->name, "Television alt", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_PHONE:
		strscpy(a->name, "Phone", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_MIC:
		strscpy(a->name, "Mic", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_CD:
		strscpy(a->name, "CD", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_AUX:
		strscpy(a->name, "Aux", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_PCM_OUT:
		strscpy(a->name, "PCM", माप(a->name));
		अवरोध;
	हाल EM28XX_AMUX_UNUSED:
	शेष:
		वापस -EINVAL;
	पूर्ण
	a->index = index;
	a->capability = V4L2_AUDCAP_STEREO;

	em28xx_videodbg("%s: audio input index %d is '%s'\n",
			s, a->index, a->name);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागतaudio(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_audio *a)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	अगर (a->index >= MAX_EM28XX_INPUT)
		वापस -EINVAL;

	वापस em28xx_fill_audio_input(dev, __func__, a, a->index);
पूर्ण

अटल पूर्णांक vidioc_g_audio(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_audio *a)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);
	पूर्णांक i;

	क्रम (i = 0; i < MAX_EM28XX_INPUT; i++)
		अगर (dev->ctl_ainput == dev->amux_map[i])
			वापस em28xx_fill_audio_input(dev, __func__, a, i);

	/* Should never happen! */
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vidioc_s_audio(काष्ठा file *file, व्योम *priv,
			  स्थिर काष्ठा v4l2_audio *a)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);
	पूर्णांक idx, i;

	अगर (a->index >= MAX_EM28XX_INPUT)
		वापस -EINVAL;

	idx = dev->amux_map[a->index];

	अगर (idx == EM28XX_AMUX_UNUSED)
		वापस -EINVAL;

	dev->ctl_ainput = idx;

	/*
	 * FIXME: This is wrong, as dअगरferent inमाला_दो at em28xx_cards
	 * may have dअगरferent audio outमाला_दो. So, the right thing
	 * to करो is to implement VIDIOC_G_AUDOUT/VIDIOC_S_AUDOUT.
	 * With the current board definitions, this would work fine,
	 * as, currently, all boards fit.
	 */
	क्रम (i = 0; i < MAX_EM28XX_INPUT; i++)
		अगर (idx == dev->amux_map[i])
			अवरोध;
	अगर (i == MAX_EM28XX_INPUT)
		वापस -EINVAL;

	dev->ctl_aoutput = INPUT(i)->aout;

	अगर (!dev->ctl_aoutput)
		dev->ctl_aoutput = EM28XX_AOUT_MASTER;

	em28xx_videodbg("%s: set audio input to %d\n", __func__,
			dev->ctl_ainput);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_tuner(काष्ठा file *file, व्योम *priv,
			  काष्ठा v4l2_tuner *t)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	अगर (t->index != 0)
		वापस -EINVAL;

	strscpy(t->name, "Tuner", माप(t->name));

	v4l2_device_call_all(&dev->v4l2->v4l2_dev, 0, tuner, g_tuner, t);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_tuner(काष्ठा file *file, व्योम *priv,
			  स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	अगर (t->index != 0)
		वापस -EINVAL;

	v4l2_device_call_all(&dev->v4l2->v4l2_dev, 0, tuner, s_tuner, t);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_frequency(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_frequency *f)
अणु
	काष्ठा em28xx         *dev = video_drvdata(file);
	काष्ठा em28xx_v4l2    *v4l2 = dev->v4l2;

	अगर (f->tuner != 0)
		वापस -EINVAL;

	f->frequency = v4l2->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_frequency(काष्ठा file *file, व्योम *priv,
			      स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा v4l2_frequency  new_freq = *f;
	काष्ठा em28xx             *dev  = video_drvdata(file);
	काष्ठा em28xx_v4l2        *v4l2 = dev->v4l2;

	अगर (f->tuner != 0)
		वापस -EINVAL;

	v4l2_device_call_all(&v4l2->v4l2_dev, 0, tuner, s_frequency, f);
	v4l2_device_call_all(&v4l2->v4l2_dev, 0, tuner, g_frequency, &new_freq);
	v4l2->frequency = new_freq.frequency;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_chip_info(काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_dbg_chip_info *chip)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	अगर (chip->match.addr > 1)
		वापस -EINVAL;
	अगर (chip->match.addr == 1)
		strscpy(chip->name, "ac97", माप(chip->name));
	अन्यथा
		strscpy(chip->name,
			dev->v4l2->v4l2_dev.name, माप(chip->name));
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_reg_len(पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल EM28XX_R40_AC97LSB:
	हाल EM28XX_R30_HSCALELOW:
	हाल EM28XX_R32_VSCALELOW:
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक vidioc_g_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);
	पूर्णांक ret;

	अगर (reg->match.addr > 1)
		वापस -EINVAL;
	अगर (reg->match.addr) अणु
		ret = em28xx_पढ़ो_ac97(dev, reg->reg);
		अगर (ret < 0)
			वापस ret;

		reg->val = ret;
		reg->size = 1;
		वापस 0;
	पूर्ण

	/* Match host */
	reg->size = em28xx_reg_len(reg->reg);
	अगर (reg->size == 1) अणु
		ret = em28xx_पढ़ो_reg(dev, reg->reg);

		अगर (ret < 0)
			वापस ret;

		reg->val = ret;
	पूर्ण अन्यथा अणु
		__le16 val = 0;

		ret = dev->em28xx_पढ़ो_reg_req_len(dev, USB_REQ_GET_STATUS,
						   reg->reg, (अक्षर *)&val, 2);
		अगर (ret < 0)
			वापस ret;

		reg->val = le16_to_cpu(val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर(काष्ठा file *file, व्योम *priv,
			     स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);
	__le16 buf;

	अगर (reg->match.addr > 1)
		वापस -EINVAL;
	अगर (reg->match.addr)
		वापस em28xx_ग_लिखो_ac97(dev, reg->reg, reg->val);

	/* Match host */
	buf = cpu_to_le16(reg->val);

	वापस em28xx_ग_लिखो_regs(dev, reg->reg, (अक्षर *)&buf,
			       em28xx_reg_len(reg->reg));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम  *priv,
			   काष्ठा v4l2_capability *cap)
अणु
	काष्ठा em28xx         *dev  = video_drvdata(file);
	काष्ठा em28xx_v4l2    *v4l2 = dev->v4l2;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);

	strscpy(cap->driver, "em28xx", माप(cap->driver));
	strscpy(cap->card, em28xx_boards[dev->model].name, माप(cap->card));
	usb_make_path(udev, cap->bus_info, माप(cap->bus_info));

	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_READWRITE |
			    V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
	अगर (dev->पूर्णांक_audio_type != EM28XX_INT_AUDIO_NONE)
		cap->capabilities |= V4L2_CAP_AUDIO;
	अगर (dev->tuner_type != TUNER_ABSENT)
		cap->capabilities |= V4L2_CAP_TUNER;
	अगर (video_is_रेजिस्टरed(&v4l2->vbi_dev))
		cap->capabilities |= V4L2_CAP_VBI_CAPTURE;
	अगर (video_is_रेजिस्टरed(&v4l2->radio_dev))
		cap->capabilities |= V4L2_CAP_RADIO;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				   काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (unlikely(f->index >= ARRAY_SIZE(क्रमmat)))
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmat[f->index].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_framesizes(काष्ठा file *file, व्योम *priv,
				  काष्ठा v4l2_frmsizeक्रमागत *fsize)
अणु
	काष्ठा em28xx         *dev = video_drvdata(file);
	काष्ठा em28xx_fmt     *fmt;
	अचिन्हित पूर्णांक	      maxw = norm_maxw(dev);
	अचिन्हित पूर्णांक	      maxh = norm_maxh(dev);

	fmt = क्रमmat_by_fourcc(fsize->pixel_क्रमmat);
	अगर (!fmt) अणु
		em28xx_videodbg("Fourcc format (%08x) invalid.\n",
				fsize->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	अगर (dev->board.is_em2800) अणु
		अगर (fsize->index > 1)
			वापस -EINVAL;
		fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		fsize->discrete.width = maxw / (1 + fsize->index);
		fsize->discrete.height = maxh / (1 + fsize->index);
		वापस 0;
	पूर्ण

	अगर (fsize->index != 0)
		वापस -EINVAL;

	/* Report a continuous range */
	fsize->type = V4L2_FRMSIZE_TYPE_STEPWISE;
	scale_to_size(dev, EM28XX_HVSCALE_MAX, EM28XX_HVSCALE_MAX,
		      &fsize->stepwise.min_width, &fsize->stepwise.min_height);
	अगर (fsize->stepwise.min_width < 48)
		fsize->stepwise.min_width = 48;
	अगर (fsize->stepwise.min_height < 38)
		fsize->stepwise.min_height = 38;
	fsize->stepwise.max_width = maxw;
	fsize->stepwise.max_height = maxh;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.step_height = 1;
	वापस 0;
पूर्ण

/* RAW VBI ioctls */

अटल पूर्णांक vidioc_g_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *क्रमmat)
अणु
	काष्ठा em28xx         *dev  = video_drvdata(file);
	काष्ठा em28xx_v4l2    *v4l2 = dev->v4l2;

	क्रमmat->fmt.vbi.samples_per_line = v4l2->vbi_width;
	क्रमmat->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	क्रमmat->fmt.vbi.offset = 0;
	क्रमmat->fmt.vbi.flags = 0;
	क्रमmat->fmt.vbi.sampling_rate = 6750000 * 4 / 2;
	क्रमmat->fmt.vbi.count[0] = v4l2->vbi_height;
	क्रमmat->fmt.vbi.count[1] = v4l2->vbi_height;
	स_रखो(क्रमmat->fmt.vbi.reserved, 0, माप(क्रमmat->fmt.vbi.reserved));

	/* Varies by video standard (NTSC, PAL, etc.) */
	अगर (v4l2->norm & V4L2_STD_525_60) अणु
		/* NTSC */
		क्रमmat->fmt.vbi.start[0] = 10;
		क्रमmat->fmt.vbi.start[1] = 273;
	पूर्ण अन्यथा अगर (v4l2->norm & V4L2_STD_625_50) अणु
		/* PAL */
		क्रमmat->fmt.vbi.start[0] = 6;
		क्रमmat->fmt.vbi.start[1] = 318;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * RADIO ESPECIFIC IOCTLS
 */

अटल पूर्णांक radio_g_tuner(काष्ठा file *file, व्योम *priv,
			 काष्ठा v4l2_tuner *t)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	अगर (unlikely(t->index > 0))
		वापस -EINVAL;

	strscpy(t->name, "Radio", माप(t->name));

	v4l2_device_call_all(&dev->v4l2->v4l2_dev, 0, tuner, g_tuner, t);

	वापस 0;
पूर्ण

अटल पूर्णांक radio_s_tuner(काष्ठा file *file, व्योम *priv,
			 स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा em28xx *dev = video_drvdata(file);

	अगर (t->index != 0)
		वापस -EINVAL;

	v4l2_device_call_all(&dev->v4l2->v4l2_dev, 0, tuner, s_tuner, t);

	वापस 0;
पूर्ण

/*
 * em28xx_मुक्त_v4l2() - Free काष्ठा em28xx_v4l2
 *
 * @ref: काष्ठा kref क्रम काष्ठा em28xx_v4l2
 *
 * Called when all users of काष्ठा em28xx_v4l2 are gone
 */
अटल व्योम em28xx_मुक्त_v4l2(काष्ठा kref *ref)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = container_of(ref, काष्ठा em28xx_v4l2, ref);

	v4l2->dev->v4l2 = शून्य;
	kमुक्त(v4l2);
पूर्ण

/*
 * em28xx_v4l2_खोलो()
 * inits the device and starts isoc transfer
 */
अटल पूर्णांक em28xx_v4l2_खोलो(काष्ठा file *filp)
अणु
	काष्ठा video_device *vdev = video_devdata(filp);
	काष्ठा em28xx *dev = video_drvdata(filp);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	क्रमागत v4l2_buf_type fh_type = 0;
	पूर्णांक ret;

	चयन (vdev->vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
		fh_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		अवरोध;
	हाल VFL_TYPE_VBI:
		fh_type = V4L2_BUF_TYPE_VBI_CAPTURE;
		अवरोध;
	हाल VFL_TYPE_RADIO:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	em28xx_videodbg("open dev=%s type=%s users=%d\n",
			video_device_node_name(vdev), v4l2_type_names[fh_type],
			v4l2->users);

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;

	ret = v4l2_fh_खोलो(filp);
	अगर (ret) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"%s: v4l2_fh_open() returned error %d\n",
		       __func__, ret);
		mutex_unlock(&dev->lock);
		वापस ret;
	पूर्ण

	अगर (v4l2->users == 0) अणु
		em28xx_set_mode(dev, EM28XX_ANALOG_MODE);

		अगर (vdev->vfl_type != VFL_TYPE_RADIO)
			em28xx_resolution_set(dev);

		/*
		 * Needed, since GPIO might have disabled घातer
		 * of some i2c devices
		 */
		em28xx_wake_i2c(dev);
	पूर्ण

	अगर (vdev->vfl_type == VFL_TYPE_RADIO) अणु
		em28xx_videodbg("video_open: setting radio device\n");
		v4l2_device_call_all(&v4l2->v4l2_dev, 0, tuner, s_radio);
	पूर्ण

	kref_get(&dev->ref);
	kref_get(&v4l2->ref);
	v4l2->users++;

	mutex_unlock(&dev->lock);

	वापस 0;
पूर्ण

/*
 * em28xx_v4l2_fini()
 * unरेजिस्टरs the v4l2,i2c and usb devices
 * called when the device माला_लो disconnected or at module unload
 */
अटल पूर्णांक em28xx_v4l2_fini(काष्ठा em28xx *dev)
अणु
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;

	अगर (dev->is_audio_only) अणु
		/* Shouldn't initialize IR क्रम this पूर्णांकerface */
		वापस 0;
	पूर्ण

	अगर (!dev->has_video) अणु
		/* This device करोes not support the v4l2 extension */
		वापस 0;
	पूर्ण

	अगर (!v4l2)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Closing video extension\n");

	mutex_lock(&dev->lock);

	v4l2_device_disconnect(&v4l2->v4l2_dev);

	em28xx_uninit_usb_xfer(dev, EM28XX_ANALOG_MODE);

	em28xx_v4l2_media_release(dev);

	अगर (video_is_रेजिस्टरed(&v4l2->radio_dev)) अणु
		dev_info(&dev->पूर्णांकf->dev, "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->radio_dev));
		video_unरेजिस्टर_device(&v4l2->radio_dev);
	पूर्ण
	अगर (video_is_रेजिस्टरed(&v4l2->vbi_dev)) अणु
		dev_info(&dev->पूर्णांकf->dev, "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->vbi_dev));
		video_unरेजिस्टर_device(&v4l2->vbi_dev);
	पूर्ण
	अगर (video_is_रेजिस्टरed(&v4l2->vdev)) अणु
		dev_info(&dev->पूर्णांकf->dev, "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->vdev));
		video_unरेजिस्टर_device(&v4l2->vdev);
	पूर्ण

	v4l2_ctrl_handler_मुक्त(&v4l2->ctrl_handler);
	v4l2_device_unरेजिस्टर(&v4l2->v4l2_dev);

	kref_put(&v4l2->ref, em28xx_मुक्त_v4l2);

	mutex_unlock(&dev->lock);

	kref_put(&dev->ref, em28xx_मुक्त_device);

	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_v4l2_suspend(काष्ठा em28xx *dev)
अणु
	अगर (dev->is_audio_only)
		वापस 0;

	अगर (!dev->has_video)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Suspending video extension\n");
	em28xx_stop_urbs(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक em28xx_v4l2_resume(काष्ठा em28xx *dev)
अणु
	अगर (dev->is_audio_only)
		वापस 0;

	अगर (!dev->has_video)
		वापस 0;

	dev_info(&dev->पूर्णांकf->dev, "Resuming video extension\n");
	/* what करो we करो here */
	वापस 0;
पूर्ण

/*
 * em28xx_v4l2_बंद()
 * stops streaming and deallocates all resources allocated by the v4l2
 * calls and ioctls
 */
अटल पूर्णांक em28xx_v4l2_बंद(काष्ठा file *filp)
अणु
	काष्ठा em28xx         *dev  = video_drvdata(filp);
	काष्ठा em28xx_v4l2    *v4l2 = dev->v4l2;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(dev->पूर्णांकf);
	पूर्णांक              err;

	em28xx_videodbg("users=%d\n", v4l2->users);

	vb2_fop_release(filp);
	mutex_lock(&dev->lock);

	अगर (v4l2->users == 1) अणु
		/* No sense to try to ग_लिखो to the device */
		अगर (dev->disconnected)
			जाओ निकास;

		/* Save some घातer by putting tuner to sleep */
		v4l2_device_call_all(&v4l2->v4l2_dev, 0, tuner, standby);

		/* करो this beक्रमe setting alternate! */
		em28xx_set_mode(dev, EM28XX_SUSPEND);

		/* set alternate 0 */
		dev->alt = 0;
		em28xx_videodbg("setting alternate 0\n");
		err = usb_set_पूर्णांकerface(udev, 0, 0);
		अगर (err < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"cannot change alternate number to 0 (error=%i)\n",
				err);
		पूर्ण
	पूर्ण

निकास:
	v4l2->users--;
	kref_put(&v4l2->ref, em28xx_मुक्त_v4l2);
	mutex_unlock(&dev->lock);
	kref_put(&dev->ref, em28xx_मुक्त_device);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations em28xx_v4l_fops = अणु
	.owner         = THIS_MODULE,
	.खोलो          = em28xx_v4l2_खोलो,
	.release       = em28xx_v4l2_बंद,
	.पढ़ो          = vb2_fop_पढ़ो,
	.poll          = vb2_fop_poll,
	.mmap          = vb2_fop_mmap,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap            = vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_cap    = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap       = vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap     = vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap       = vidioc_s_fmt_vid_cap,
	.vidioc_g_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_try_fmt_vbi_cap     = vidioc_g_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap       = vidioc_g_fmt_vbi_cap,
	.vidioc_क्रमागत_framesizes     = vidioc_क्रमागत_framesizes,
	.vidioc_क्रमागतaudio           = vidioc_क्रमागतaudio,
	.vidioc_g_audio             = vidioc_g_audio,
	.vidioc_s_audio             = vidioc_s_audio,

	.vidioc_reqbufs             = vb2_ioctl_reqbufs,
	.vidioc_create_bufs         = vb2_ioctl_create_bufs,
	.vidioc_prepare_buf         = vb2_ioctl_prepare_buf,
	.vidioc_querybuf            = vb2_ioctl_querybuf,
	.vidioc_qbuf                = vb2_ioctl_qbuf,
	.vidioc_dqbuf               = vb2_ioctl_dqbuf,

	.vidioc_g_std               = vidioc_g_std,
	.vidioc_querystd            = vidioc_querystd,
	.vidioc_s_std               = vidioc_s_std,
	.vidioc_g_parm		    = vidioc_g_parm,
	.vidioc_s_parm		    = vidioc_s_parm,
	.vidioc_क्रमागत_input          = vidioc_क्रमागत_input,
	.vidioc_g_input             = vidioc_g_input,
	.vidioc_s_input             = vidioc_s_input,
	.vidioc_streamon            = vb2_ioctl_streamon,
	.vidioc_streamoff           = vb2_ioctl_streamoff,
	.vidioc_g_tuner             = vidioc_g_tuner,
	.vidioc_s_tuner             = vidioc_s_tuner,
	.vidioc_g_frequency         = vidioc_g_frequency,
	.vidioc_s_frequency         = vidioc_s_frequency,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info         = vidioc_g_chip_info,
	.vidioc_g_रेजिस्टर          = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर          = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा video_device em28xx_video_ढाँचा = अणु
	.fops		= &em28xx_v4l_fops,
	.ioctl_ops	= &video_ioctl_ops,
	.release	= video_device_release_empty,
	.tvnorms	= V4L2_STD_ALL,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations radio_fops = अणु
	.owner         = THIS_MODULE,
	.खोलो          = em28xx_v4l2_खोलो,
	.release       = em28xx_v4l2_बंद,
	.unlocked_ioctl = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops radio_ioctl_ops = अणु
	.vidioc_querycap      = vidioc_querycap,
	.vidioc_g_tuner       = radio_g_tuner,
	.vidioc_s_tuner       = radio_s_tuner,
	.vidioc_g_frequency   = vidioc_g_frequency,
	.vidioc_s_frequency   = vidioc_s_frequency,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_chip_info   = vidioc_g_chip_info,
	.vidioc_g_रेजिस्टर    = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर    = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा video_device em28xx_radio_ढाँचा = अणु
	.fops		= &radio_fops,
	.ioctl_ops	= &radio_ioctl_ops,
	.release	= video_device_release_empty,
पूर्ण;

/* I2C possible address to saa7115, tvp5150, msp3400, tvaudio */
अटल अचिन्हित लघु saa711x_addrs[] = अणु
	0x4a >> 1, 0x48 >> 1,   /* SAA7111, SAA7111A and SAA7113 */
	0x42 >> 1, 0x40 >> 1,   /* SAA7114, SAA7115 and SAA7118 */
	I2C_CLIENT_END पूर्ण;

अटल अचिन्हित लघु tvp5150_addrs[] = अणु
	0xb8 >> 1,
	0xba >> 1,
	I2C_CLIENT_END
पूर्ण;

अटल अचिन्हित लघु msp3400_addrs[] = अणु
	0x80 >> 1,
	0x88 >> 1,
	I2C_CLIENT_END
पूर्ण;

/******************************** usb पूर्णांकerface ******************************/

अटल व्योम em28xx_vdev_init(काष्ठा em28xx *dev,
			     काष्ठा video_device *vfd,
			     स्थिर काष्ठा video_device *ढाँचा,
			     स्थिर अक्षर *type_name)
अणु
	*vfd		= *ढाँचा;
	vfd->v4l2_dev	= &dev->v4l2->v4l2_dev;
	vfd->lock	= &dev->lock;
	अगर (dev->is_webcam)
		vfd->tvnorms = 0;

	snम_लिखो(vfd->name, माप(vfd->name), "%s %s",
		 dev_name(&dev->पूर्णांकf->dev), type_name);

	video_set_drvdata(vfd, dev);
पूर्ण

अटल व्योम em28xx_tuner_setup(काष्ठा em28xx *dev, अचिन्हित लघु tuner_addr)
अणु
	काष्ठा em28xx_v4l2      *v4l2 = dev->v4l2;
	काष्ठा v4l2_device      *v4l2_dev = &v4l2->v4l2_dev;
	काष्ठा tuner_setup      tun_setup;
	काष्ठा v4l2_frequency   f;

	स_रखो(&tun_setup, 0, माप(tun_setup));

	tun_setup.mode_mask = T_ANALOG_TV | T_RADIO;
	tun_setup.tuner_callback = em28xx_tuner_callback;

	अगर (dev->board.radio.type) अणु
		tun_setup.type = dev->board.radio.type;
		tun_setup.addr = dev->board.radio_addr;

		v4l2_device_call_all(v4l2_dev,
				     0, tuner, s_type_addr, &tun_setup);
	पूर्ण

	अगर (dev->tuner_type != TUNER_ABSENT && dev->tuner_type) अणु
		tun_setup.type   = dev->tuner_type;
		tun_setup.addr   = tuner_addr;

		v4l2_device_call_all(v4l2_dev,
				     0, tuner, s_type_addr, &tun_setup);
	पूर्ण

	अगर (dev->board.tda9887_conf) अणु
		काष्ठा v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &dev->board.tda9887_conf;

		v4l2_device_call_all(v4l2_dev,
				     0, tuner, s_config, &tda9887_cfg);
	पूर्ण

	अगर (dev->tuner_type == TUNER_XC2028) अणु
		काष्ठा v4l2_priv_tun_config  xc2028_cfg;
		काष्ठा xc2028_ctrl           ctl;

		स_रखो(&xc2028_cfg, 0, माप(xc2028_cfg));
		स_रखो(&ctl, 0, माप(ctl));

		em28xx_setup_xc3028(dev, &ctl);

		xc2028_cfg.tuner = TUNER_XC2028;
		xc2028_cfg.priv  = &ctl;

		v4l2_device_call_all(v4l2_dev, 0, tuner, s_config, &xc2028_cfg);
	पूर्ण

	/* configure tuner */
	f.tuner = 0;
	f.type = V4L2_TUNER_ANALOG_TV;
	f.frequency = 9076;     /* just a magic number */
	v4l2->frequency = f.frequency;
	v4l2_device_call_all(v4l2_dev, 0, tuner, s_frequency, &f);
पूर्ण

अटल पूर्णांक em28xx_v4l2_init(काष्ठा em28xx *dev)
अणु
	u8 val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक maxw;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा em28xx_v4l2 *v4l2;

	अगर (dev->is_audio_only) अणु
		/* Shouldn't initialize IR क्रम this पूर्णांकerface */
		वापस 0;
	पूर्ण

	अगर (!dev->has_video) अणु
		/* This device करोes not support the v4l2 extension */
		वापस 0;
	पूर्ण

	dev_info(&dev->पूर्णांकf->dev, "Registering V4L2 extension\n");

	mutex_lock(&dev->lock);

	v4l2 = kzalloc(माप(*v4l2), GFP_KERNEL);
	अगर (!v4l2) अणु
		mutex_unlock(&dev->lock);
		वापस -ENOMEM;
	पूर्ण
	kref_init(&v4l2->ref);
	v4l2->dev = dev;
	dev->v4l2 = v4l2;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	v4l2->v4l2_dev.mdev = dev->media_dev;
#पूर्ण_अगर
	ret = v4l2_device_रेजिस्टर(&dev->पूर्णांकf->dev, &v4l2->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"Call to v4l2_device_register() failed!\n");
		जाओ err;
	पूर्ण

	hdl = &v4l2->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 8);
	v4l2->v4l2_dev.ctrl_handler = hdl;

	अगर (dev->is_webcam)
		v4l2->progressive = true;

	/*
	 * Default क्रमmat, used क्रम tvp5150 or saa711x output क्रमmats
	 */
	v4l2->vinmode = EM28XX_VINMODE_YUV422_CbYCrY;
	v4l2->vinctl  = EM28XX_VINCTRL_INTERLACED |
			EM28XX_VINCTRL_CCIR656_ENABLE;

	/* request some modules */

	अगर (dev->has_msp34xx)
		v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "msp3400", 0, msp3400_addrs);

	अगर (dev->board.decoder == EM28XX_SAA711X)
		v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "saa7115_auto", 0, saa711x_addrs);

	अगर (dev->board.decoder == EM28XX_TVP5150)
		v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "tvp5150", 0, tvp5150_addrs);

	अगर (dev->board.adecoder == EM28XX_TVAUDIO)
		v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
				    &dev->i2c_adap[dev->def_i2c_bus],
				    "tvaudio", dev->board.tvaudio_addr, शून्य);

	/* Initialize tuner and camera */

	अगर (dev->board.tuner_type != TUNER_ABSENT) अणु
		अचिन्हित लघु tuner_addr = dev->board.tuner_addr;
		पूर्णांक has_demod = (dev->board.tda9887_conf & TDA9887_PRESENT);

		अगर (dev->board.radio.type)
			v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
					    &dev->i2c_adap[dev->def_i2c_bus],
					    "tuner", dev->board.radio_addr,
					    शून्य);

		अगर (has_demod)
			v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
					    &dev->i2c_adap[dev->def_i2c_bus],
					    "tuner", 0,
					    v4l2_i2c_tuner_addrs(ADDRS_DEMOD));
		अगर (tuner_addr == 0) अणु
			क्रमागत v4l2_i2c_tuner_type type =
				has_demod ? ADDRS_TV_WITH_DEMOD : ADDRS_TV;
			काष्ठा v4l2_subdev *sd;

			sd = v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
						 &dev->i2c_adap[dev->def_i2c_bus],
						 "tuner", 0,
						 v4l2_i2c_tuner_addrs(type));

			अगर (sd)
				tuner_addr = v4l2_i2c_subdev_addr(sd);
		पूर्ण अन्यथा अणु
			v4l2_i2c_new_subdev(&v4l2->v4l2_dev,
					    &dev->i2c_adap[dev->def_i2c_bus],
					    "tuner", tuner_addr, शून्य);
		पूर्ण

		em28xx_tuner_setup(dev, tuner_addr);
	पूर्ण

	अगर (dev->em28xx_sensor != EM28XX_NOSENSOR)
		em28xx_init_camera(dev);

	/* Configure audio */
	ret = em28xx_audio_setup(dev);
	अगर (ret < 0) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"%s: Error while setting audio - error [%d]!\n",
			__func__, ret);
		जाओ unरेजिस्टर_dev;
	पूर्ण
	अगर (dev->audio_mode.ac97 != EM28XX_NO_AC97) अणु
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_AUDIO_VOLUME, 0, 0x1f, 1, 0x1f);
	पूर्ण अन्यथा अणु
		/* install the em28xx notअगरy callback */
		v4l2_ctrl_notअगरy(v4l2_ctrl_find(hdl, V4L2_CID_AUDIO_MUTE),
				 em28xx_ctrl_notअगरy, dev);
		v4l2_ctrl_notअगरy(v4l2_ctrl_find(hdl, V4L2_CID_AUDIO_VOLUME),
				 em28xx_ctrl_notअगरy, dev);
	पूर्ण

	/* wake i2c devices */
	em28xx_wake_i2c(dev);

	/* init video dma queues */
	INIT_LIST_HEAD(&dev->vidq.active);
	INIT_LIST_HEAD(&dev->vbiq.active);

	अगर (dev->has_msp34xx) अणु
		/* Send a reset to other chips via gpio */
		ret = em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xf7);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"%s: em28xx_write_reg - msp34xx(1) failed! error [%d]\n",
				__func__, ret);
			जाओ unरेजिस्टर_dev;
		पूर्ण
		usleep_range(10000, 11000);

		ret = em28xx_ग_लिखो_reg(dev, EM2820_R08_GPIO_CTRL, 0xff);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"%s: em28xx_write_reg - msp34xx(2) failed! error [%d]\n",
				__func__, ret);
			जाओ unरेजिस्टर_dev;
		पूर्ण
		usleep_range(10000, 11000);
	पूर्ण

	/* set शेष norm */
	v4l2->norm = V4L2_STD_PAL;
	v4l2_device_call_all(&v4l2->v4l2_dev, 0, video, s_std, v4l2->norm);
	v4l2->पूर्णांकerlaced_fieldmode = EM28XX_INTERLACED_DEFAULT;

	/* Analog specअगरic initialization */
	v4l2->क्रमmat = &क्रमmat[0];

	maxw = norm_maxw(dev);
	/*
	 * MaxPacketSize क्रम em2800 is too small to capture at full resolution
	 * use half of maxw as the scaler can only scale to 50%
	 */
	अगर (dev->board.is_em2800)
		maxw /= 2;

	em28xx_set_video_क्रमmat(dev, क्रमmat[0].fourcc,
				maxw, norm_maxh(dev));

	video_mux(dev, 0);

	/* Audio शेषs */
	dev->mute = 1;
	dev->volume = 0x1f;

/*	em28xx_ग_लिखो_reg(dev, EM28XX_R0E_AUDIOSRC, 0xc0); audio रेजिस्टर */
	val = (u8)em28xx_पढ़ो_reg(dev, EM28XX_R0F_XCLK);
	em28xx_ग_लिखो_reg(dev, EM28XX_R0F_XCLK,
			 (EM28XX_XCLK_AUDIO_UNMUTE | val));

	em28xx_set_outfmt(dev);

	/* Add image controls */

	/*
	 * NOTE: at this poपूर्णांक, the subdevices are alपढ़ोy रेजिस्टरed, so
	 * bridge controls are only added/enabled when no subdevice provides
	 * them
	 */
	अगर (!v4l2_ctrl_find(hdl, V4L2_CID_CONTRAST))
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_CONTRAST,
				  0, 0x1f, 1, CONTRAST_DEFAULT);
	अगर (!v4l2_ctrl_find(hdl, V4L2_CID_BRIGHTNESS))
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_BRIGHTNESS,
				  -0x80, 0x7f, 1, BRIGHTNESS_DEFAULT);
	अगर (!v4l2_ctrl_find(hdl, V4L2_CID_SATURATION))
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_SATURATION,
				  0, 0x1f, 1, SATURATION_DEFAULT);
	अगर (!v4l2_ctrl_find(hdl, V4L2_CID_BLUE_BALANCE))
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_BLUE_BALANCE,
				  -0x30, 0x30, 1, BLUE_BALANCE_DEFAULT);
	अगर (!v4l2_ctrl_find(hdl, V4L2_CID_RED_BALANCE))
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_RED_BALANCE,
				  -0x30, 0x30, 1, RED_BALANCE_DEFAULT);
	अगर (!v4l2_ctrl_find(hdl, V4L2_CID_SHARPNESS))
		v4l2_ctrl_new_std(hdl, &em28xx_ctrl_ops,
				  V4L2_CID_SHARPNESS,
				  0, 0x0f, 1, SHARPNESS_DEFAULT);

	/* Reset image controls */
	em28xx_colorlevels_set_शेष(dev);
	v4l2_ctrl_handler_setup(hdl);
	ret = hdl->error;
	अगर (ret)
		जाओ unरेजिस्टर_dev;

	/* allocate and fill video video_device काष्ठा */
	em28xx_vdev_init(dev, &v4l2->vdev, &em28xx_video_ढाँचा, "video");
	mutex_init(&v4l2->vb_queue_lock);
	mutex_init(&v4l2->vb_vbi_queue_lock);
	v4l2->vdev.queue = &v4l2->vb_vidq;
	v4l2->vdev.queue->lock = &v4l2->vb_queue_lock;
	v4l2->vdev.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_VIDEO_CAPTURE |
				 V4L2_CAP_STREAMING;
	अगर (dev->पूर्णांक_audio_type != EM28XX_INT_AUDIO_NONE)
		v4l2->vdev.device_caps |= V4L2_CAP_AUDIO;
	अगर (dev->tuner_type != TUNER_ABSENT)
		v4l2->vdev.device_caps |= V4L2_CAP_TUNER;


	/* disable inapplicable ioctls */
	अगर (dev->is_webcam) अणु
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_QUERYSTD);
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_G_STD);
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_S_STD);
	पूर्ण अन्यथा अणु
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_S_PARM);
	पूर्ण
	अगर (dev->tuner_type == TUNER_ABSENT) अणु
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_S_FREQUENCY);
	पूर्ण
	अगर (dev->पूर्णांक_audio_type == EM28XX_INT_AUDIO_NONE) अणु
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(&v4l2->vdev, VIDIOC_S_AUDIO);
	पूर्ण

	/* रेजिस्टर v4l2 video video_device */
	ret = video_रेजिस्टर_device(&v4l2->vdev, VFL_TYPE_VIDEO,
				    video_nr[dev->devno]);
	अगर (ret) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"unable to register video device (error=%i).\n", ret);
		जाओ unरेजिस्टर_dev;
	पूर्ण

	/* Allocate and fill vbi video_device काष्ठा */
	अगर (em28xx_vbi_supported(dev) == 1) अणु
		em28xx_vdev_init(dev, &v4l2->vbi_dev, &em28xx_video_ढाँचा,
				 "vbi");

		v4l2->vbi_dev.queue = &v4l2->vb_vbiq;
		v4l2->vbi_dev.queue->lock = &v4l2->vb_vbi_queue_lock;
		v4l2->vbi_dev.device_caps = V4L2_CAP_STREAMING |
			V4L2_CAP_READWRITE | V4L2_CAP_VBI_CAPTURE;
		अगर (dev->tuner_type != TUNER_ABSENT)
			v4l2->vbi_dev.device_caps |= V4L2_CAP_TUNER;

		/* disable inapplicable ioctls */
		v4l2_disable_ioctl(&v4l2->vbi_dev, VIDIOC_S_PARM);
		अगर (dev->tuner_type == TUNER_ABSENT) अणु
			v4l2_disable_ioctl(&v4l2->vbi_dev, VIDIOC_G_TUNER);
			v4l2_disable_ioctl(&v4l2->vbi_dev, VIDIOC_S_TUNER);
			v4l2_disable_ioctl(&v4l2->vbi_dev, VIDIOC_G_FREQUENCY);
			v4l2_disable_ioctl(&v4l2->vbi_dev, VIDIOC_S_FREQUENCY);
		पूर्ण
		अगर (dev->पूर्णांक_audio_type == EM28XX_INT_AUDIO_NONE) अणु
			v4l2_disable_ioctl(&v4l2->vbi_dev, VIDIOC_G_AUDIO);
			v4l2_disable_ioctl(&v4l2->vbi_dev, VIDIOC_S_AUDIO);
		पूर्ण

		/* रेजिस्टर v4l2 vbi video_device */
		ret = video_रेजिस्टर_device(&v4l2->vbi_dev, VFL_TYPE_VBI,
					    vbi_nr[dev->devno]);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"unable to register vbi device\n");
			जाओ unरेजिस्टर_dev;
		पूर्ण
	पूर्ण

	अगर (em28xx_boards[dev->model].radio.type == EM28XX_RADIO) अणु
		em28xx_vdev_init(dev, &v4l2->radio_dev, &em28xx_radio_ढाँचा,
				 "radio");
		v4l2->radio_dev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
		ret = video_रेजिस्टर_device(&v4l2->radio_dev, VFL_TYPE_RADIO,
					    radio_nr[dev->devno]);
		अगर (ret < 0) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"can't register radio device\n");
			जाओ unरेजिस्टर_dev;
		पूर्ण
		dev_info(&dev->पूर्णांकf->dev,
			 "Registered radio device as %s\n",
			 video_device_node_name(&v4l2->radio_dev));
	पूर्ण

	/* Init entities at the Media Controller */
	em28xx_v4l2_create_entities(dev);

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	ret = v4l2_mc_create_media_graph(dev->media_dev);
	अगर (ret) अणु
		dev_err(&dev->पूर्णांकf->dev,
			"failed to create media graph\n");
		em28xx_v4l2_media_release(dev);
		जाओ unरेजिस्टर_dev;
	पूर्ण
#पूर्ण_अगर

	dev_info(&dev->पूर्णांकf->dev,
		 "V4L2 video device registered as %s\n",
		 video_device_node_name(&v4l2->vdev));

	अगर (video_is_रेजिस्टरed(&v4l2->vbi_dev))
		dev_info(&dev->पूर्णांकf->dev,
			 "V4L2 VBI device registered as %s\n",
			 video_device_node_name(&v4l2->vbi_dev));

	/* Save some घातer by putting tuner to sleep */
	v4l2_device_call_all(&v4l2->v4l2_dev, 0, tuner, standby);

	/* initialize videobuf2 stuff */
	em28xx_vb2_setup(dev);

	dev_info(&dev->पूर्णांकf->dev,
		 "V4L2 extension successfully initialized\n");

	kref_get(&dev->ref);

	mutex_unlock(&dev->lock);
	वापस 0;

unरेजिस्टर_dev:
	अगर (video_is_रेजिस्टरed(&v4l2->radio_dev)) अणु
		dev_info(&dev->पूर्णांकf->dev,
			 "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->radio_dev));
		video_unरेजिस्टर_device(&v4l2->radio_dev);
	पूर्ण
	अगर (video_is_रेजिस्टरed(&v4l2->vbi_dev)) अणु
		dev_info(&dev->पूर्णांकf->dev,
			 "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->vbi_dev));
		video_unरेजिस्टर_device(&v4l2->vbi_dev);
	पूर्ण
	अगर (video_is_रेजिस्टरed(&v4l2->vdev)) अणु
		dev_info(&dev->पूर्णांकf->dev,
			 "V4L2 device %s deregistered\n",
			 video_device_node_name(&v4l2->vdev));
		video_unरेजिस्टर_device(&v4l2->vdev);
	पूर्ण

	v4l2_ctrl_handler_मुक्त(&v4l2->ctrl_handler);
	v4l2_device_unरेजिस्टर(&v4l2->v4l2_dev);
err:
	dev->v4l2 = शून्य;
	kref_put(&v4l2->ref, em28xx_मुक्त_v4l2);
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल काष्ठा em28xx_ops v4l2_ops = अणु
	.id   = EM28XX_V4L2,
	.name = "Em28xx v4l2 Extension",
	.init = em28xx_v4l2_init,
	.fini = em28xx_v4l2_fini,
	.suspend = em28xx_v4l2_suspend,
	.resume = em28xx_v4l2_resume,
पूर्ण;

अटल पूर्णांक __init em28xx_video_रेजिस्टर(व्योम)
अणु
	वापस em28xx_रेजिस्टर_extension(&v4l2_ops);
पूर्ण

अटल व्योम __निकास em28xx_video_unरेजिस्टर(व्योम)
अणु
	em28xx_unरेजिस्टर_extension(&v4l2_ops);
पूर्ण

module_init(em28xx_video_रेजिस्टर);
module_निकास(em28xx_video_unरेजिस्टर);
