<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Zoran zr36057/zr36067 PCI controller driver, क्रम the
 * Pinnacle/Miro DC10/DC10+/DC30/DC30+, Iomega Buz, Linux
 * Media Lअसल LML33/LML33R10.
 *
 * Copyright (C) 2000 Serguei Miriकरोnov <mirsev@cicese.mx>
 *
 * Changes क्रम BUZ by Wolfgang Scherr <scherr@net4you.net>
 *
 * Changes क्रम DC10/DC30 by Laurent Pinअक्षरt <laurent.pinअक्षरt@skynet.be>
 *
 * Changes क्रम LML33R10 by Maxim Yevtyushkin <max@linuxmediaद_असल.com>
 *
 * Changes क्रम videodev2/v4l2 by Ronald Bultje <rbultje@ronald.bitfreak.net>
 *
 * Based on
 *
 * Miro DC10 driver
 * Copyright (C) 1999 Wolfgang Scherr <scherr@net4you.net>
 *
 * Iomega Buz driver version 1.0
 * Copyright (C) 1999 Rainer Johanni <Rainer@Johanni.de>
 *
 * buz.0.0.3
 * Copyright (C) 1998 Dave Perks <dperks@ibm.net>
 *
 * bttv - Bt848 frame grabber driver
 * Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
 *                        & Marcus Metzler (mocm@thp.uni-koeln.de)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/रुको.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

#समावेश <linux/spinlock.h>

#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश "videocodec.h"

#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <linux/mutex.h>
#समावेश "zoran.h"
#समावेश "zoran_device.h"
#समावेश "zoran_card.h"

स्थिर काष्ठा zoran_क्रमmat zoran_क्रमmats[] = अणु
	अणु
		.name = "15-bit RGB LE",
		.fourcc = V4L2_PIX_FMT_RGB555,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.depth = 15,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_RGB555 | ZR36057_VFESPFR_ERR_DIF |
			   ZR36057_VFESPFR_LITTLE_ENDIAN,
	पूर्ण, अणु
		.name = "15-bit RGB BE",
		.fourcc = V4L2_PIX_FMT_RGB555X,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.depth = 15,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_RGB555 | ZR36057_VFESPFR_ERR_DIF,
	पूर्ण, अणु
		.name = "16-bit RGB LE",
		.fourcc = V4L2_PIX_FMT_RGB565,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.depth = 16,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_RGB565 | ZR36057_VFESPFR_ERR_DIF |
			   ZR36057_VFESPFR_LITTLE_ENDIAN,
	पूर्ण, अणु
		.name = "16-bit RGB BE",
		.fourcc = V4L2_PIX_FMT_RGB565X,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.depth = 16,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_RGB565 | ZR36057_VFESPFR_ERR_DIF,
	पूर्ण, अणु
		.name = "24-bit RGB",
		.fourcc = V4L2_PIX_FMT_BGR24,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.depth = 24,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_RGB888 | ZR36057_VFESPFR_PACK24,
	पूर्ण, अणु
		.name = "32-bit RGB LE",
		.fourcc = V4L2_PIX_FMT_BGR32,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.depth = 32,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_RGB888 | ZR36057_VFESPFR_LITTLE_ENDIAN,
	पूर्ण, अणु
		.name = "32-bit RGB BE",
		.fourcc = V4L2_PIX_FMT_RGB32,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.depth = 32,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_RGB888,
	पूर्ण, अणु
		.name = "4:2:2, packed, YUYV",
		.fourcc = V4L2_PIX_FMT_YUYV,
		.colorspace = V4L2_COLORSPACE_SMPTE170M,
		.depth = 16,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_YUV422,
	पूर्ण, अणु
		.name = "4:2:2, packed, UYVY",
		.fourcc = V4L2_PIX_FMT_UYVY,
		.colorspace = V4L2_COLORSPACE_SMPTE170M,
		.depth = 16,
		.flags = ZORAN_FORMAT_CAPTURE,
		.vfespfr = ZR36057_VFESPFR_YUV422 | ZR36057_VFESPFR_LITTLE_ENDIAN,
	पूर्ण, अणु
		.name = "Hardware-encoded Motion-JPEG",
		.fourcc = V4L2_PIX_FMT_MJPEG,
		.colorspace = V4L2_COLORSPACE_SMPTE170M,
		.depth = 0,
		.flags = ZORAN_FORMAT_CAPTURE |
			 ZORAN_FORMAT_PLAYBACK |
			 ZORAN_FORMAT_COMPRESSED,
	पूर्ण
पूर्ण;

#घोषणा NUM_FORMATS ARRAY_SIZE(zoran_क्रमmats)

	/*
	 * small helper function क्रम calculating buffersizes क्रम v4l2
	 * we calculate the nearest higher घातer-of-two, which
	 * will be the recommended buffersize
	 */
अटल __u32 zoran_v4l2_calc_bufsize(काष्ठा zoran_jpg_settings *settings)
अणु
	__u8 भाग = settings->ver_dcm * settings->hor_dcm * settings->पंचांगp_dcm;
	__u32 num = (1024 * 512) / (भाग);
	__u32 result = 2;

	num--;
	जबतक (num) अणु
		num >>= 1;
		result <<= 1;
	पूर्ण

	अगर (result > jpg_bufsize)
		वापस jpg_bufsize;
	अगर (result < 8192)
		वापस 8192;

	वापस result;
पूर्ण

/*
 *   V4L Buffer grabbing
 */
अटल पूर्णांक zoran_v4l_set_क्रमmat(काष्ठा zoran *zr, पूर्णांक width, पूर्णांक height,
				स्थिर काष्ठा zoran_क्रमmat *क्रमmat)
अणु
	पूर्णांक bpp;

	/* Check size and क्रमmat of the grab wanted */

	अगर (height < BUZ_MIN_HEIGHT || width < BUZ_MIN_WIDTH ||
	    height > BUZ_MAX_HEIGHT || width > BUZ_MAX_WIDTH) अणु
		pci_err(zr->pci_dev, "%s - wrong frame size (%dx%d)\n", __func__, width, height);
		वापस -EINVAL;
	पूर्ण

	bpp = (क्रमmat->depth + 7) / 8;

	zr->buffer_size = height * width * bpp;

	/* Check against available buffer size */
	अगर (height * width * bpp > zr->buffer_size) अणु
		pci_err(zr->pci_dev, "%s - video buffer size (%d kB) is too small\n",
			__func__, zr->buffer_size >> 10);
		वापस -EINVAL;
	पूर्ण

	/* The video front end needs 4-byte alinged line sizes */

	अगर ((bpp == 2 && (width & 1)) || (bpp == 3 && (width & 3))) अणु
		pci_err(zr->pci_dev, "%s - wrong frame alignment\n", __func__);
		वापस -EINVAL;
	पूर्ण

	zr->v4l_settings.width = width;
	zr->v4l_settings.height = height;
	zr->v4l_settings.क्रमmat = क्रमmat;
	zr->v4l_settings.bytesperline = bpp * zr->v4l_settings.width;

	वापस 0;
पूर्ण

अटल पूर्णांक zoran_set_norm(काष्ठा zoran *zr, v4l2_std_id norm)
अणु

	अगर (!(norm & zr->card.norms)) अणु
		pci_err(zr->pci_dev, "%s - unsupported norm %llx\n", __func__, norm);
		वापस -EINVAL;
	पूर्ण

	अगर (norm & V4L2_STD_SECAM)
		zr->timing = zr->card.tvn[ZR_NORM_SECAM];
	अन्यथा अगर (norm & V4L2_STD_NTSC)
		zr->timing = zr->card.tvn[ZR_NORM_NTSC];
	अन्यथा
		zr->timing = zr->card.tvn[ZR_NORM_PAL];

	decoder_call(zr, video, s_std, norm);
	encoder_call(zr, video, s_std_output, norm);

	/* Make sure the changes come पूर्णांकo effect */
	zr->norm = norm;

	वापस 0;
पूर्ण

अटल पूर्णांक zoran_set_input(काष्ठा zoran *zr, पूर्णांक input)
अणु
	अगर (input == zr->input)
		वापस 0;

	अगर (input < 0 || input >= zr->card.inमाला_दो) अणु
		pci_err(zr->pci_dev, "%s - unsupported input %d\n", __func__, input);
		वापस -EINVAL;
	पूर्ण

	zr->input = input;

	decoder_call(zr, video, s_routing, zr->card.input[input].muxsel, 0, 0);

	वापस 0;
पूर्ण

/*
 *   ioctl routine
 */

अटल पूर्णांक zoran_querycap(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_capability *cap)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	strscpy(cap->card, ZR_DEVNAME(zr), माप(cap->card));
	strscpy(cap->driver, "zoran", माप(cap->driver));
	snम_लिखो(cap->bus_info, माप(cap->bus_info), "PCI:%s", pci_name(zr->pci_dev));
	cap->device_caps = zr->video_dev->device_caps;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	वापस 0;
पूर्ण

अटल पूर्णांक zoran_क्रमागत_fmt(काष्ठा zoran *zr, काष्ठा v4l2_fmtdesc *fmt, पूर्णांक flag)
अणु
	अचिन्हित पूर्णांक num, i;

	अगर (fmt->index >= ARRAY_SIZE(zoran_क्रमmats))
		वापस -EINVAL;
	अगर (fmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	क्रम (num = i = 0; i < NUM_FORMATS; i++) अणु
		अगर (zoran_क्रमmats[i].flags & flag && num++ == fmt->index) अणु
			strscpy(fmt->description, zoran_क्रमmats[i].name,
				माप(fmt->description));
			/* fmt काष्ठा pre-zeroed, so adding '\0' not needed */
			fmt->pixelक्रमmat = zoran_क्रमmats[i].fourcc;
			अगर (zoran_क्रमmats[i].flags & ZORAN_FORMAT_COMPRESSED)
				fmt->flags |= V4L2_FMT_FLAG_COMPRESSED;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक zoran_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *__fh,
				  काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	वापस zoran_क्रमागत_fmt(zr, f, ZORAN_FORMAT_CAPTURE);
पूर्ण

#अगर 0
/* TODO: output करोes not work yet */
अटल पूर्णांक zoran_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *__fh,
				  काष्ठा v4l2_fmtdesc *f)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	वापस zoran_क्रमागत_fmt(zr, f, ZORAN_FORMAT_PLAYBACK);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक zoran_g_fmt_vid_out(काष्ठा file *file, व्योम *__fh,
			       काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	fmt->fmt.pix.width = zr->jpg_settings.img_width / zr->jpg_settings.hor_dcm;
	fmt->fmt.pix.height = zr->jpg_settings.img_height * 2 /
		(zr->jpg_settings.ver_dcm * zr->jpg_settings.पंचांगp_dcm);
	fmt->fmt.pix.sizeimage = zr->buffer_size;
	fmt->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_MJPEG;
	अगर (zr->jpg_settings.पंचांगp_dcm == 1)
		fmt->fmt.pix.field = (zr->jpg_settings.odd_even ?
				V4L2_FIELD_SEQ_TB : V4L2_FIELD_SEQ_BT);
	अन्यथा
		fmt->fmt.pix.field = (zr->jpg_settings.odd_even ?
				V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM);
	fmt->fmt.pix.bytesperline = 0;
	fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक zoran_g_fmt_vid_cap(काष्ठा file *file, व्योम *__fh,
			       काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	अगर (zr->map_mode != ZORAN_MAP_MODE_RAW)
		वापस zoran_g_fmt_vid_out(file, __fh, fmt);
	fmt->fmt.pix.width = zr->v4l_settings.width;
	fmt->fmt.pix.height = zr->v4l_settings.height;
	fmt->fmt.pix.sizeimage = zr->buffer_size;
	fmt->fmt.pix.pixelक्रमmat = zr->v4l_settings.क्रमmat->fourcc;
	fmt->fmt.pix.colorspace = zr->v4l_settings.क्रमmat->colorspace;
	fmt->fmt.pix.bytesperline = zr->v4l_settings.bytesperline;
	अगर (BUZ_MAX_HEIGHT < (zr->v4l_settings.height * 2))
		fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;
	अन्यथा
		fmt->fmt.pix.field = V4L2_FIELD_TOP;
	वापस 0;
पूर्ण

अटल पूर्णांक zoran_try_fmt_vid_out(काष्ठा file *file, व्योम *__fh,
				 काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा zoran *zr = video_drvdata(file);
	काष्ठा zoran_jpg_settings settings;
	पूर्णांक res = 0;

	अगर (fmt->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_MJPEG)
		वापस -EINVAL;

	settings = zr->jpg_settings;

	/* we actually need to set 'real' parameters now */
	अगर ((fmt->fmt.pix.height * 2) > BUZ_MAX_HEIGHT)
		settings.पंचांगp_dcm = 1;
	अन्यथा
		settings.पंचांगp_dcm = 2;
	settings.decimation = 0;
	अगर (fmt->fmt.pix.height <= zr->jpg_settings.img_height / 2)
		settings.ver_dcm = 2;
	अन्यथा
		settings.ver_dcm = 1;
	अगर (fmt->fmt.pix.width <= zr->jpg_settings.img_width / 4)
		settings.hor_dcm = 4;
	अन्यथा अगर (fmt->fmt.pix.width <= zr->jpg_settings.img_width / 2)
		settings.hor_dcm = 2;
	अन्यथा
		settings.hor_dcm = 1;
	अगर (settings.पंचांगp_dcm == 1)
		settings.field_per_buff = 2;
	अन्यथा
		settings.field_per_buff = 1;

	अगर (settings.hor_dcm > 1) अणु
		settings.img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings.img_width = (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
	पूर्ण अन्यथा अणु
		settings.img_x = 0;
		settings.img_width = BUZ_MAX_WIDTH;
	पूर्ण

	/* check */
	res = zoran_check_jpg_settings(zr, &settings, 1);
	अगर (res)
		वापस res;

	/* tell the user what we actually did */
	fmt->fmt.pix.width = settings.img_width / settings.hor_dcm;
	fmt->fmt.pix.height = settings.img_height * 2 /
		(settings.पंचांगp_dcm * settings.ver_dcm);
	अगर (settings.पंचांगp_dcm == 1)
		fmt->fmt.pix.field = (zr->jpg_settings.odd_even ?
				V4L2_FIELD_SEQ_TB : V4L2_FIELD_SEQ_BT);
	अन्यथा
		fmt->fmt.pix.field = (zr->jpg_settings.odd_even ?
				V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM);

	fmt->fmt.pix.sizeimage = zoran_v4l2_calc_bufsize(&settings);
	zr->buffer_size = fmt->fmt.pix.sizeimage;
	fmt->fmt.pix.bytesperline = 0;
	fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस res;
पूर्ण

अटल पूर्णांक zoran_try_fmt_vid_cap(काष्ठा file *file, व्योम *__fh,
				 काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा zoran *zr = video_drvdata(file);
	पूर्णांक bpp;
	पूर्णांक i;

	अगर (fmt->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_MJPEG)
		वापस zoran_try_fmt_vid_out(file, __fh, fmt);

	क्रम (i = 0; i < NUM_FORMATS; i++)
		अगर (zoran_क्रमmats[i].fourcc == fmt->fmt.pix.pixelक्रमmat)
			अवरोध;

	अगर (i == NUM_FORMATS) अणु
		/* TODO करो not वापस here to fix the TRY_FMT cannot handle an invalid pixelक्रमmat*/
		वापस -EINVAL;
	पूर्ण

	fmt->fmt.pix.pixelक्रमmat = zoran_क्रमmats[i].fourcc;
	fmt->fmt.pix.colorspace = zoran_क्रमmats[i].colorspace;
	अगर (BUZ_MAX_HEIGHT < (fmt->fmt.pix.height * 2))
		fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;
	अन्यथा
		fmt->fmt.pix.field = V4L2_FIELD_TOP;

	bpp = DIV_ROUND_UP(zoran_क्रमmats[i].depth, 8);
	v4l_bound_align_image(&fmt->fmt.pix.width, BUZ_MIN_WIDTH, BUZ_MAX_WIDTH, bpp == 2 ? 1 : 2,
		&fmt->fmt.pix.height, BUZ_MIN_HEIGHT, BUZ_MAX_HEIGHT, 0, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक zoran_s_fmt_vid_out(काष्ठा file *file, व्योम *__fh,
			       काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा zoran *zr = video_drvdata(file);
	__le32 म_लिखोormat = __cpu_to_le32(fmt->fmt.pix.pixelक्रमmat);
	काष्ठा zoran_jpg_settings settings;
	पूर्णांक res = 0;

	pci_dbg(zr->pci_dev, "size=%dx%d, fmt=0x%x (%4.4s)\n",
		fmt->fmt.pix.width, fmt->fmt.pix.height,
			fmt->fmt.pix.pixelक्रमmat,
			(अक्षर *)&म_लिखोormat);
	अगर (fmt->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_MJPEG)
		वापस -EINVAL;

	अगर (!fmt->fmt.pix.height || !fmt->fmt.pix.width)
		वापस -EINVAL;

	settings = zr->jpg_settings;

	/* we actually need to set 'real' parameters now */
	अगर (fmt->fmt.pix.height * 2 > BUZ_MAX_HEIGHT)
		settings.पंचांगp_dcm = 1;
	अन्यथा
		settings.पंचांगp_dcm = 2;
	settings.decimation = 0;
	अगर (fmt->fmt.pix.height <= zr->jpg_settings.img_height / 2)
		settings.ver_dcm = 2;
	अन्यथा
		settings.ver_dcm = 1;
	अगर (fmt->fmt.pix.width <= zr->jpg_settings.img_width / 4)
		settings.hor_dcm = 4;
	अन्यथा अगर (fmt->fmt.pix.width <= zr->jpg_settings.img_width / 2)
		settings.hor_dcm = 2;
	अन्यथा
		settings.hor_dcm = 1;
	अगर (settings.पंचांगp_dcm == 1)
		settings.field_per_buff = 2;
	अन्यथा
		settings.field_per_buff = 1;

	अगर (settings.hor_dcm > 1) अणु
		settings.img_x = (BUZ_MAX_WIDTH == 720) ? 8 : 0;
		settings.img_width = (BUZ_MAX_WIDTH == 720) ? 704 : BUZ_MAX_WIDTH;
	पूर्ण अन्यथा अणु
		settings.img_x = 0;
		settings.img_width = BUZ_MAX_WIDTH;
	पूर्ण

	/* check */
	res = zoran_check_jpg_settings(zr, &settings, 0);
	अगर (res)
		वापस res;

	/* it's ok, so set them */
	zr->jpg_settings = settings;

	अगर (fmt->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		zr->map_mode = ZORAN_MAP_MODE_JPG_REC;
	अन्यथा
		zr->map_mode = ZORAN_MAP_MODE_JPG_PLAY;

	zr->buffer_size = zoran_v4l2_calc_bufsize(&zr->jpg_settings);

	/* tell the user what we actually did */
	fmt->fmt.pix.width = settings.img_width / settings.hor_dcm;
	fmt->fmt.pix.height = settings.img_height * 2 /
		(settings.पंचांगp_dcm * settings.ver_dcm);
	अगर (settings.पंचांगp_dcm == 1)
		fmt->fmt.pix.field = (zr->jpg_settings.odd_even ?
				V4L2_FIELD_SEQ_TB : V4L2_FIELD_SEQ_BT);
	अन्यथा
		fmt->fmt.pix.field = (zr->jpg_settings.odd_even ?
				V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM);
	fmt->fmt.pix.bytesperline = 0;
	fmt->fmt.pix.sizeimage = zr->buffer_size;
	fmt->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	वापस res;
पूर्ण

अटल पूर्णांक zoran_s_fmt_vid_cap(काष्ठा file *file, व्योम *__fh,
			       काष्ठा v4l2_क्रमmat *fmt)
अणु
	काष्ठा zoran *zr = video_drvdata(file);
	काष्ठा zoran_fh *fh = __fh;
	पूर्णांक i;
	पूर्णांक res = 0;

	अगर (fmt->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_MJPEG)
		वापस zoran_s_fmt_vid_out(file, fh, fmt);

	क्रम (i = 0; i < NUM_FORMATS; i++)
		अगर (fmt->fmt.pix.pixelक्रमmat == zoran_क्रमmats[i].fourcc)
			अवरोध;
	अगर (i == NUM_FORMATS) अणु
		pci_err(zr->pci_dev, "VIDIOC_S_FMT - unknown/unsupported format 0x%x\n",
			fmt->fmt.pix.pixelक्रमmat);
		/* TODO करो not वापस here to fix the TRY_FMT cannot handle an invalid pixelक्रमmat*/
		वापस -EINVAL;
	पूर्ण

	fmt->fmt.pix.pixelक्रमmat = zoran_क्रमmats[i].fourcc;
	अगर (fmt->fmt.pix.height > BUZ_MAX_HEIGHT)
		fmt->fmt.pix.height = BUZ_MAX_HEIGHT;
	अगर (fmt->fmt.pix.width > BUZ_MAX_WIDTH)
		fmt->fmt.pix.width = BUZ_MAX_WIDTH;
	अगर (fmt->fmt.pix.height < BUZ_MIN_HEIGHT)
		fmt->fmt.pix.height = BUZ_MIN_HEIGHT;
	अगर (fmt->fmt.pix.width < BUZ_MIN_WIDTH)
		fmt->fmt.pix.width = BUZ_MIN_WIDTH;

	zr->map_mode = ZORAN_MAP_MODE_RAW;

	res = zoran_v4l_set_क्रमmat(zr, fmt->fmt.pix.width, fmt->fmt.pix.height,
				   &zoran_क्रमmats[i]);
	अगर (res)
		वापस res;

	/* tell the user the results/missing stuff */
	fmt->fmt.pix.bytesperline = zr->v4l_settings.bytesperline;
	fmt->fmt.pix.sizeimage = zr->buffer_size;
	fmt->fmt.pix.colorspace = zr->v4l_settings.क्रमmat->colorspace;
	अगर (BUZ_MAX_HEIGHT < (zr->v4l_settings.height * 2))
		fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;
	अन्यथा
		fmt->fmt.pix.field = V4L2_FIELD_TOP;
	वापस res;
पूर्ण

अटल पूर्णांक zoran_g_std(काष्ठा file *file, व्योम *__fh, v4l2_std_id *std)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	*std = zr->norm;
	वापस 0;
पूर्ण

अटल पूर्णांक zoran_s_std(काष्ठा file *file, व्योम *__fh, v4l2_std_id std)
अणु
	काष्ठा zoran *zr = video_drvdata(file);
	पूर्णांक res = 0;

	अगर (zr->running != ZORAN_MAP_MODE_NONE)
		वापस -EBUSY;

	res = zoran_set_norm(zr, std);
	वापस res;
पूर्ण

अटल पूर्णांक zoran_क्रमागत_input(काष्ठा file *file, व्योम *__fh,
			    काष्ठा v4l2_input *inp)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	अगर (inp->index >= zr->card.inमाला_दो)
		वापस -EINVAL;

	strscpy(inp->name, zr->card.input[inp->index].name, माप(inp->name));
	inp->type = V4L2_INPUT_TYPE_CAMERA;
	inp->std = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM;

	/* Get status of video decoder */
	decoder_call(zr, video, g_input_status, &inp->status);
	वापस 0;
पूर्ण

अटल पूर्णांक zoran_g_input(काष्ठा file *file, व्योम *__fh, अचिन्हित पूर्णांक *input)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	*input = zr->input;

	वापस 0;
पूर्ण

अटल पूर्णांक zoran_s_input(काष्ठा file *file, व्योम *__fh, अचिन्हित पूर्णांक input)
अणु
	काष्ठा zoran *zr = video_drvdata(file);
	पूर्णांक res;

	अगर (zr->running != ZORAN_MAP_MODE_NONE)
		वापस -EBUSY;

	res = zoran_set_input(zr, input);
	वापस res;
पूर्ण

#अगर 0
/* TODO: output करोes not work yet */
अटल पूर्णांक zoran_क्रमागत_output(काष्ठा file *file, व्योम *__fh,
			     काष्ठा v4l2_output *outp)
अणु
	अगर (outp->index != 0)
		वापस -EINVAL;

	outp->index = 0;
	outp->type = V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY;
	outp->std = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM;
	outp->capabilities = V4L2_OUT_CAP_STD;
	strscpy(outp->name, "Autodetect", माप(outp->name));

	वापस 0;
पूर्ण
अटल पूर्णांक zoran_g_output(काष्ठा file *file, व्योम *__fh, अचिन्हित पूर्णांक *output)
अणु
	*output = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक zoran_s_output(काष्ठा file *file, व्योम *__fh, अचिन्हित पूर्णांक output)
अणु
	अगर (output != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* cropping (sub-frame capture) */
अटल पूर्णांक zoran_g_selection(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा zoran *zr = video_drvdata(file);

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) अणु
		pci_err(zr->pci_dev, "%s invalid selection type combination\n", __func__);
		वापस -EINVAL;
	पूर्ण

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		sel->r.top = zr->jpg_settings.img_y;
		sel->r.left = zr->jpg_settings.img_x;
		sel->r.width = zr->jpg_settings.img_width;
		sel->r.height = zr->jpg_settings.img_height;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r.top = sel->r.left = 0;
		sel->r.width = BUZ_MIN_WIDTH;
		sel->r.height = BUZ_MIN_HEIGHT;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.top = sel->r.left = 0;
		sel->r.width = BUZ_MAX_WIDTH;
		sel->r.height = BUZ_MAX_HEIGHT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक zoran_s_selection(काष्ठा file *file, व्योम *__fh, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा zoran *zr = video_drvdata(file);
	काष्ठा zoran_jpg_settings settings;
	पूर्णांक res;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	अगर (!sel->r.width || !sel->r.height)
		वापस -EINVAL;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	अगर (zr->map_mode == ZORAN_MAP_MODE_RAW) अणु
		pci_err(zr->pci_dev, "VIDIOC_S_SELECTION - subcapture only supported for compressed capture\n");
		वापस -EINVAL;
	पूर्ण

	settings = zr->jpg_settings;

	/* move पूर्णांकo a क्रमm that we understand */
	settings.img_x = sel->r.left;
	settings.img_y = sel->r.top;
	settings.img_width = sel->r.width;
	settings.img_height = sel->r.height;

	/* check validity */
	res = zoran_check_jpg_settings(zr, &settings, 0);
	अगर (res)
		वापस res;

	/* accept */
	zr->jpg_settings = settings;
	वापस res;
पूर्ण

अटल पूर्णांक zoran_g_parm(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_streamparm *parm)
अणु
	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Output is disabled temporarily
 * Zoran is picky about jpeg data it accepts. At least it seems to unsupport COM and APPn.
 * So until a way to filter data will be करोne, disable output.
 */
अटल स्थिर काष्ठा v4l2_ioctl_ops zoran_ioctl_ops = अणु
	.vidioc_querycap		    = zoran_querycap,
	.vidioc_g_parm			    = zoran_g_parm,
	.vidioc_s_selection		    = zoran_s_selection,
	.vidioc_g_selection		    = zoran_g_selection,
	.vidioc_क्रमागत_input		    = zoran_क्रमागत_input,
	.vidioc_g_input			    = zoran_g_input,
	.vidioc_s_input			    = zoran_s_input,
/*	.vidioc_क्रमागत_output		    = zoran_क्रमागत_output,
	.vidioc_g_output		    = zoran_g_output,
	.vidioc_s_output		    = zoran_s_output,*/
	.vidioc_g_std			    = zoran_g_std,
	.vidioc_s_std			    = zoran_s_std,
	.vidioc_create_bufs		    = vb2_ioctl_create_bufs,
	.vidioc_reqbufs			    = vb2_ioctl_reqbufs,
	.vidioc_querybuf		    = vb2_ioctl_querybuf,
	.vidioc_qbuf			    = vb2_ioctl_qbuf,
	.vidioc_dqbuf			    = vb2_ioctl_dqbuf,
	.vidioc_expbuf                      = vb2_ioctl_expbuf,
	.vidioc_streamon		    = vb2_ioctl_streamon,
	.vidioc_streamoff		    = vb2_ioctl_streamoff,
	.vidioc_क्रमागत_fmt_vid_cap	    = zoran_क्रमागत_fmt_vid_cap,
/*	.vidioc_क्रमागत_fmt_vid_out	    = zoran_क्रमागत_fmt_vid_out,*/
	.vidioc_g_fmt_vid_cap		    = zoran_g_fmt_vid_cap,
/*	.vidioc_g_fmt_vid_out               = zoran_g_fmt_vid_out,*/
	.vidioc_s_fmt_vid_cap		    = zoran_s_fmt_vid_cap,
/*	.vidioc_s_fmt_vid_out               = zoran_s_fmt_vid_out,*/
	.vidioc_try_fmt_vid_cap		    = zoran_try_fmt_vid_cap,
/*	.vidioc_try_fmt_vid_out		    = zoran_try_fmt_vid_out,*/
	.vidioc_subscribe_event             = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event           = v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations zoran_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
	.पढ़ो		= vb2_fop_पढ़ो,
	.ग_लिखो		= vb2_fop_ग_लिखो,
	.mmap		= vb2_fop_mmap,
	.poll		= vb2_fop_poll,
पूर्ण;

स्थिर काष्ठा video_device zoran_ढाँचा = अणु
	.name = ZORAN_NAME,
	.fops = &zoran_fops,
	.ioctl_ops = &zoran_ioctl_ops,
	.release = &zoran_vdev_release,
	.tvnorms = V4L2_STD_NTSC | V4L2_STD_PAL | V4L2_STD_SECAM,
पूर्ण;

अटल पूर्णांक zr_vb2_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			      अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा zoran *zr = vb2_get_drv_priv(vq);
	अचिन्हित पूर्णांक size = zr->buffer_size;

	pci_dbg(zr->pci_dev, "%s nbuf=%u nplanes=%u", __func__, *nbuffers, *nplanes);

	zr->buf_in_reserve = 0;

	अगर (*nbuffers < vq->min_buffers_needed)
		*nbuffers = vq->min_buffers_needed;

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
		अन्यथा
			वापस 0;
	पूर्ण

	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल व्योम zr_vb2_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा zoran *zr = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा zr_buffer *buf = vb2_to_zr_buffer(vb);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&zr->queued_bufs_lock, flags);
	list_add_tail(&buf->queue, &zr->queued_bufs);
	zr->buf_in_reserve++;
	spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
	अगर (zr->running == ZORAN_MAP_MODE_JPG_REC)
		zoran_feed_stat_com(zr);
	zr->queued++;
पूर्ण

अटल पूर्णांक zr_vb2_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा zoran *zr = vb2_get_drv_priv(vb->vb2_queue);

	अगर (vb2_plane_size(vb, 0) < zr->buffer_size)
		वापस -EINVAL;
	zr->prepared++;

	वापस 0;
पूर्ण

पूर्णांक zr_set_buf(काष्ठा zoran *zr)
अणु
	काष्ठा zr_buffer *buf;
	काष्ठा vb2_v4l2_buffer *vbuf;
	dma_addr_t phys_addr;
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (zr->running == ZORAN_MAP_MODE_NONE)
		वापस 0;

	अगर (zr->inuse[0]) अणु
		buf = zr->inuse[0];
		buf->vbuf.vb2_buf.बारtamp = kसमय_get_ns();
		buf->vbuf.sequence = zr->vbseq++;
		vbuf = &buf->vbuf;

		buf->vbuf.field = V4L2_FIELD_INTERLACED;
		vb2_set_plane_payload(&buf->vbuf.vb2_buf, 0, zr->buffer_size);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
		zr->inuse[0] = शून्य;
	पूर्ण

	spin_lock_irqsave(&zr->queued_bufs_lock, flags);
	अगर (list_empty(&zr->queued_bufs)) अणु
		btand(~ZR36057_ICR_INT_PIN_EN, ZR36057_ICR);
		vb2_queue_error(zr->video_dev->queue);
		spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
		वापस -EINVAL;
	पूर्ण
	buf = list_first_entry_or_null(&zr->queued_bufs, काष्ठा zr_buffer, queue);
	अगर (!buf) अणु
		btand(~ZR36057_ICR_INT_PIN_EN, ZR36057_ICR);
		vb2_queue_error(zr->video_dev->queue);
		spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
		वापस -EINVAL;
	पूर्ण
	list_del(&buf->queue);
	spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);

	vbuf = &buf->vbuf;
	vbuf->vb2_buf.state = VB2_BUF_STATE_ACTIVE;
	phys_addr = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, 0);

	अगर (!phys_addr)
		वापस -EINVAL;

	zr->inuse[0] = buf;

	reg = phys_addr;
	btग_लिखो(reg, ZR36057_VDTR);
	अगर (zr->v4l_settings.height > BUZ_MAX_HEIGHT / 2)
		reg += zr->v4l_settings.bytesperline;
	btग_लिखो(reg, ZR36057_VDBR);

	reg = 0;
	अगर (zr->v4l_settings.height > BUZ_MAX_HEIGHT / 2)
		reg += zr->v4l_settings.bytesperline;
	reg = (reg << ZR36057_VSSFGR_DISP_STRIDE);
	reg |= ZR36057_VSSFGR_VID_OVF;
	reg |= ZR36057_VSSFGR_SNAP_SHOT;
	reg |= ZR36057_VSSFGR_FRAME_GRAB;
	btग_लिखो(reg, ZR36057_VSSFGR);

	btor(ZR36057_VDCR_VID_EN, ZR36057_VDCR);
	वापस 0;
पूर्ण

अटल पूर्णांक zr_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा zoran *zr = vq->drv_priv;
	पूर्णांक j;

	क्रम (j = 0; j < BUZ_NUM_STAT_COM; j++) अणु
		zr->stat_com[j] = cpu_to_le32(1);
		zr->inuse[j] = शून्य;
	पूर्ण

	अगर (zr->map_mode != ZORAN_MAP_MODE_RAW) अणु
		pci_info(zr->pci_dev, "START JPG\n");
		zr36057_restart(zr);
		zoran_init_hardware(zr);
		अगर (zr->map_mode == ZORAN_MAP_MODE_JPG_REC)
			zr36057_enable_jpg(zr, BUZ_MODE_MOTION_DECOMPRESS);
		अन्यथा
			zr36057_enable_jpg(zr, BUZ_MODE_MOTION_COMPRESS);
		zoran_feed_stat_com(zr);
		jpeg_start(zr);
		zr->running = zr->map_mode;
		btor(ZR36057_ICR_INT_PIN_EN, ZR36057_ICR);
		वापस 0;
	पूर्ण

	pci_info(zr->pci_dev, "START RAW\n");
	zr36057_restart(zr);
	zoran_init_hardware(zr);

	zr36057_enable_jpg(zr, BUZ_MODE_IDLE);
	zr36057_set_memgrab(zr, 1);
	zr->running = zr->map_mode;
	btor(ZR36057_ICR_INT_PIN_EN, ZR36057_ICR);
	वापस 0;
पूर्ण

अटल व्योम zr_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा zoran *zr = vq->drv_priv;
	काष्ठा zr_buffer *buf;
	अचिन्हित दीर्घ flags;
	पूर्णांक j;

	btand(~ZR36057_ICR_INT_PIN_EN, ZR36057_ICR);
	अगर (zr->map_mode != ZORAN_MAP_MODE_RAW)
		zr36057_enable_jpg(zr, BUZ_MODE_IDLE);
	zr36057_set_memgrab(zr, 0);
	zr->running = ZORAN_MAP_MODE_NONE;

	zoran_set_pci_master(zr, 0);

	अगर (!pass_through) अणु	/* Switch to color bar */
		decoder_call(zr, video, s_stream, 0);
		encoder_call(zr, video, s_routing, 2, 0, 0);
	पूर्ण

	क्रम (j = 0; j < BUZ_NUM_STAT_COM; j++) अणु
		zr->stat_com[j] = cpu_to_le32(1);
		अगर (!zr->inuse[j])
			जारी;
		buf = zr->inuse[j];
		pci_dbg(zr->pci_dev, "%s clean buf %d\n", __func__, j);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_ERROR);
		zr->inuse[j] = शून्य;
	पूर्ण

	spin_lock_irqsave(&zr->queued_bufs_lock, flags);
	जबतक (!list_empty(&zr->queued_bufs)) अणु
		buf = list_entry(zr->queued_bufs.next, काष्ठा zr_buffer, queue);
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_ERROR);
		zr->buf_in_reserve--;
	पूर्ण
	spin_unlock_irqrestore(&zr->queued_bufs_lock, flags);
	अगर (zr->buf_in_reserve)
		pci_err(zr->pci_dev, "Buffer remaining %d\n", zr->buf_in_reserve);
	zr->map_mode = ZORAN_MAP_MODE_RAW;
पूर्ण

अटल स्थिर काष्ठा vb2_ops zr_video_qops = अणु
	.queue_setup            = zr_vb2_queue_setup,
	.buf_queue              = zr_vb2_queue,
	.buf_prepare            = zr_vb2_prepare,
	.start_streaming        = zr_vb2_start_streaming,
	.stop_streaming         = zr_vb2_stop_streaming,
	.रुको_prepare           = vb2_ops_रुको_prepare,
	.रुको_finish            = vb2_ops_रुको_finish,
पूर्ण;

पूर्णांक zoran_queue_init(काष्ठा zoran *zr, काष्ठा vb2_queue *vq)
अणु
	पूर्णांक err;

	spin_lock_init(&zr->queued_bufs_lock);
	INIT_LIST_HEAD(&zr->queued_bufs);

	vq->dev = &zr->pci_dev->dev;
	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->io_modes = VB2_USERPTR | VB2_DMABUF | VB2_MMAP | VB2_READ | VB2_WRITE;
	vq->drv_priv = zr;
	vq->buf_काष्ठा_size = माप(काष्ठा zr_buffer);
	vq->ops = &zr_video_qops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->gfp_flags = GFP_DMA32;
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->min_buffers_needed = 9;
	vq->lock = &zr->lock;
	err = vb2_queue_init(vq);
	अगर (err)
		वापस err;
	zr->video_dev->queue = vq;
	वापस 0;
पूर्ण

व्योम zoran_queue_निकास(काष्ठा zoran *zr)
अणु
	vb2_queue_release(zr->video_dev->queue);
पूर्ण
