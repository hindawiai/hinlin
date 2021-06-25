<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * device driver क्रम philips saa7134 based TV cards
 * video4linux video पूर्णांकerface
 *
 * (c) 2001-03 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]
 */

#समावेश "saa7134.h"
#समावेश "saa7134-reg.h"

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/i2c/saa6588.h>

/* ------------------------------------------------------------------ */

अचिन्हित पूर्णांक video_debug;
अटल अचिन्हित पूर्णांक gbuffers      = 8;
अटल अचिन्हित पूर्णांक nonपूर्णांकerlaced; /* 0 */
अटल अचिन्हित पूर्णांक gbufsize      = 720*576*4;
अटल अचिन्हित पूर्णांक gbufsize_max  = 720*576*4;
अटल अक्षर secam[] = "--";
module_param(video_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(video_debug,"enable debug messages [video]");
module_param(gbuffers, पूर्णांक, 0444);
MODULE_PARM_DESC(gbuffers,"number of capture buffers, range 2-32");
module_param(nonपूर्णांकerlaced, पूर्णांक, 0644);
MODULE_PARM_DESC(nonपूर्णांकerlaced,"capture non interlaced video");
module_param_string(secam, secam, माप(secam), 0644);
MODULE_PARM_DESC(secam, "force SECAM variant, either DK,L or Lc");


#घोषणा video_dbg(fmt, arg...) करो अणु \
	अगर (video_debug & 0x04) \
		prपूर्णांकk(KERN_DEBUG pr_fmt("video: " fmt), ## arg); \
	पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */
/* Defines क्रम Video Output Port Register at address 0x191            */

/* Bit 0: VIP code T bit polarity */

#घोषणा VP_T_CODE_P_NON_INVERTED	0x00
#घोषणा VP_T_CODE_P_INVERTED		0x01

/* ------------------------------------------------------------------ */
/* Defines क्रम Video Output Port Register at address 0x195            */

/* Bit 2: Video output घड़ी delay control */

#घोषणा VP_CLK_CTRL2_NOT_DELAYED	0x00
#घोषणा VP_CLK_CTRL2_DELAYED		0x04

/* Bit 1: Video output घड़ी invert control */

#घोषणा VP_CLK_CTRL1_NON_INVERTED	0x00
#घोषणा VP_CLK_CTRL1_INVERTED		0x02

/* ------------------------------------------------------------------ */
/* Defines क्रम Video Output Port Register at address 0x196            */

/* Bits 2 to 0: VSYNC pin video vertical sync type */

#घोषणा VP_VS_TYPE_MASK			0x07

#घोषणा VP_VS_TYPE_OFF			0x00
#घोषणा VP_VS_TYPE_V123			0x01
#घोषणा VP_VS_TYPE_V_ITU		0x02
#घोषणा VP_VS_TYPE_VGATE_L		0x03
#घोषणा VP_VS_TYPE_RESERVED1		0x04
#घोषणा VP_VS_TYPE_RESERVED2		0x05
#घोषणा VP_VS_TYPE_F_ITU		0x06
#घोषणा VP_VS_TYPE_SC_FID		0x07

/* ------------------------------------------------------------------ */
/* data काष्ठाs क्रम video                                             */

अटल पूर्णांक video_out[][9] = अणु
	[CCIR656] = अणु 0x00, 0xb1, 0x00, 0xa1, 0x00, 0x04, 0x06, 0x00, 0x00 पूर्ण,
पूर्ण;

अटल काष्ठा saa7134_क्रमmat क्रमmats[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_GREY,
		.depth    = 8,
		.pm       = 0x06,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB555,
		.depth    = 16,
		.pm       = 0x13 | 0x80,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB555X,
		.depth    = 16,
		.pm       = 0x13 | 0x80,
		.bswap    = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB565,
		.depth    = 16,
		.pm       = 0x10 | 0x80,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB565X,
		.depth    = 16,
		.pm       = 0x10 | 0x80,
		.bswap    = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_BGR24,
		.depth    = 24,
		.pm       = 0x11,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB24,
		.depth    = 24,
		.pm       = 0x11,
		.bswap    = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_BGR32,
		.depth    = 32,
		.pm       = 0x12,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB32,
		.depth    = 32,
		.pm       = 0x12,
		.bswap    = 1,
		.wswap    = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUYV,
		.depth    = 16,
		.pm       = 0x00,
		.bswap    = 1,
		.yuv      = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_UYVY,
		.depth    = 16,
		.pm       = 0x00,
		.yuv      = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUV422P,
		.depth    = 16,
		.pm       = 0x09,
		.yuv      = 1,
		.planar   = 1,
		.hshअगरt   = 1,
		.vshअगरt   = 0,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUV420,
		.depth    = 12,
		.pm       = 0x0a,
		.yuv      = 1,
		.planar   = 1,
		.hshअगरt   = 1,
		.vshअगरt   = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YVU420,
		.depth    = 12,
		.pm       = 0x0a,
		.yuv      = 1,
		.planar   = 1,
		.uvswap   = 1,
		.hshअगरt   = 1,
		.vshअगरt   = 1,
	पूर्ण
पूर्ण;
#घोषणा FORMATS ARRAY_SIZE(क्रमmats)

#घोषणा NORM_625_50			\
		.h_start       = 0,	\
		.h_stop        = 719,	\
		.video_v_start = 24,	\
		.video_v_stop  = 311,	\
		.vbi_v_start_0 = 7,	\
		.vbi_v_stop_0  = 23,	\
		.vbi_v_start_1 = 319,   \
		.src_timing    = 4

#घोषणा NORM_525_60			\
		.h_start       = 0,	\
		.h_stop        = 719,	\
		.video_v_start = 23,	\
		.video_v_stop  = 262,	\
		.vbi_v_start_0 = 10,	\
		.vbi_v_stop_0  = 21,	\
		.vbi_v_start_1 = 273,	\
		.src_timing    = 7

अटल काष्ठा saa7134_tvnorm tvnorms[] = अणु
	अणु
		.name          = "PAL", /* स्वतःdetect */
		.id            = V4L2_STD_PAL,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0x81,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x06,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "PAL-BG",
		.id            = V4L2_STD_PAL_BG,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0x81,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x06,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "PAL-I",
		.id            = V4L2_STD_PAL_I,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0x81,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x06,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "PAL-DK",
		.id            = V4L2_STD_PAL_DK,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0x81,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x06,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "NTSC",
		.id            = V4L2_STD_NTSC,
		NORM_525_60,

		.sync_control  = 0x59,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0x89,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x0e,
		.vgate_misc    = 0x18,

	पूर्ण,अणु
		.name          = "SECAM",
		.id            = V4L2_STD_SECAM,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x1b,
		.chroma_ctrl1  = 0xd1,
		.chroma_gain   = 0x80,
		.chroma_ctrl2  = 0x00,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "SECAM-DK",
		.id            = V4L2_STD_SECAM_DK,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x1b,
		.chroma_ctrl1  = 0xd1,
		.chroma_gain   = 0x80,
		.chroma_ctrl2  = 0x00,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "SECAM-L",
		.id            = V4L2_STD_SECAM_L,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x1b,
		.chroma_ctrl1  = 0xd1,
		.chroma_gain   = 0x80,
		.chroma_ctrl2  = 0x00,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "SECAM-Lc",
		.id            = V4L2_STD_SECAM_LC,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x1b,
		.chroma_ctrl1  = 0xd1,
		.chroma_gain   = 0x80,
		.chroma_ctrl2  = 0x00,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "PAL-M",
		.id            = V4L2_STD_PAL_M,
		NORM_525_60,

		.sync_control  = 0x59,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0xb9,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x0e,
		.vgate_misc    = 0x18,

	पूर्ण,अणु
		.name          = "PAL-Nc",
		.id            = V4L2_STD_PAL_Nc,
		NORM_625_50,

		.sync_control  = 0x18,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0xa1,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x06,
		.vgate_misc    = 0x1c,

	पूर्ण,अणु
		.name          = "PAL-60",
		.id            = V4L2_STD_PAL_60,

		.h_start       = 0,
		.h_stop        = 719,
		.video_v_start = 23,
		.video_v_stop  = 262,
		.vbi_v_start_0 = 10,
		.vbi_v_stop_0  = 21,
		.vbi_v_start_1 = 273,
		.src_timing    = 7,

		.sync_control  = 0x18,
		.luma_control  = 0x40,
		.chroma_ctrl1  = 0x81,
		.chroma_gain   = 0x2a,
		.chroma_ctrl2  = 0x06,
		.vgate_misc    = 0x1c,
	पूर्ण
पूर्ण;
#घोषणा TVNORMS ARRAY_SIZE(tvnorms)

अटल काष्ठा saa7134_क्रमmat* क्रमmat_by_fourcc(अचिन्हित पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < FORMATS; i++)
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस क्रमmats+i;
	वापस शून्य;
पूर्ण

/* ------------------------------------------------------------------ */

अटल व्योम set_tvnorm(काष्ठा saa7134_dev *dev, काष्ठा saa7134_tvnorm *norm)
अणु
	video_dbg("set tv norm = %s\n", norm->name);
	dev->tvnorm = norm;

	/* setup cropping */
	dev->crop_bounds.left    = norm->h_start;
	dev->crop_defrect.left   = norm->h_start;
	dev->crop_bounds.width   = norm->h_stop - norm->h_start +1;
	dev->crop_defrect.width  = norm->h_stop - norm->h_start +1;

	dev->crop_bounds.top     = (norm->vbi_v_stop_0+1)*2;
	dev->crop_defrect.top    = norm->video_v_start*2;
	dev->crop_bounds.height  = ((norm->id & V4L2_STD_525_60) ? 524 : 624)
		- dev->crop_bounds.top;
	dev->crop_defrect.height = (norm->video_v_stop - norm->video_v_start +1)*2;

	dev->crop_current = dev->crop_defrect;

	saa7134_set_tvnorm_hw(dev);
पूर्ण

अटल व्योम video_mux(काष्ठा saa7134_dev *dev, पूर्णांक input)
अणु
	video_dbg("video input = %d [%s]\n",
		  input, saa7134_input_name[card_in(dev, input).type]);
	dev->ctl_input = input;
	set_tvnorm(dev, dev->tvnorm);
	saa7134_tvaudio_setinput(dev, &card_in(dev, input));
पूर्ण


अटल व्योम saa7134_set_decoder(काष्ठा saa7134_dev *dev)
अणु
	पूर्णांक luma_control, sync_control, chroma_ctrl1, mux;

	काष्ठा saa7134_tvnorm *norm = dev->tvnorm;
	mux = card_in(dev, dev->ctl_input).vmux;

	luma_control = norm->luma_control;
	sync_control = norm->sync_control;
	chroma_ctrl1 = norm->chroma_ctrl1;

	अगर (mux > 5)
		luma_control |= 0x80; /* svideo */
	अगर (nonपूर्णांकerlaced || dev->noसंकेत)
		sync_control |= 0x20;

	/* चयन on स्वतः standard detection */
	sync_control |= SAA7134_SYNC_CTRL_AUFD;
	chroma_ctrl1 |= SAA7134_CHROMA_CTRL1_AUTO0;
	chroma_ctrl1 &= ~SAA7134_CHROMA_CTRL1_FCTC;
	luma_control &= ~SAA7134_LUMA_CTRL_LDEL;

	/* setup video decoder */
	saa_ग_लिखोb(SAA7134_INCR_DELAY,            0x08);
	saa_ग_लिखोb(SAA7134_ANALOG_IN_CTRL1,       0xc0 | mux);
	saa_ग_लिखोb(SAA7134_ANALOG_IN_CTRL2,       0x00);

	saa_ग_लिखोb(SAA7134_ANALOG_IN_CTRL3,       0x90);
	saa_ग_लिखोb(SAA7134_ANALOG_IN_CTRL4,       0x90);
	saa_ग_लिखोb(SAA7134_HSYNC_START,           0xeb);
	saa_ग_लिखोb(SAA7134_HSYNC_STOP,            0xe0);
	saa_ग_लिखोb(SAA7134_SOURCE_TIMING1,        norm->src_timing);

	saa_ग_लिखोb(SAA7134_SYNC_CTRL,             sync_control);
	saa_ग_लिखोb(SAA7134_LUMA_CTRL,             luma_control);
	saa_ग_लिखोb(SAA7134_DEC_LUMA_BRIGHT,       dev->ctl_bright);

	saa_ग_लिखोb(SAA7134_DEC_LUMA_CONTRAST,
		dev->ctl_invert ? -dev->ctl_contrast : dev->ctl_contrast);

	saa_ग_लिखोb(SAA7134_DEC_CHROMA_SATURATION,
		dev->ctl_invert ? -dev->ctl_saturation : dev->ctl_saturation);

	saa_ग_लिखोb(SAA7134_DEC_CHROMA_HUE,        dev->ctl_hue);
	saa_ग_लिखोb(SAA7134_CHROMA_CTRL1,          chroma_ctrl1);
	saa_ग_लिखोb(SAA7134_CHROMA_GAIN,           norm->chroma_gain);

	saa_ग_लिखोb(SAA7134_CHROMA_CTRL2,          norm->chroma_ctrl2);
	saa_ग_लिखोb(SAA7134_MODE_DELAY_CTRL,       0x00);

	saa_ग_लिखोb(SAA7134_ANALOG_ADC,            0x01);
	saa_ग_लिखोb(SAA7134_VGATE_START,           0x11);
	saa_ग_लिखोb(SAA7134_VGATE_STOP,            0xfe);
	saa_ग_लिखोb(SAA7134_MISC_VGATE_MSB,        norm->vgate_misc);
	saa_ग_लिखोb(SAA7134_RAW_DATA_GAIN,         0x40);
	saa_ग_लिखोb(SAA7134_RAW_DATA_OFFSET,       0x80);
पूर्ण

व्योम saa7134_set_tvnorm_hw(काष्ठा saa7134_dev *dev)
अणु
	saa7134_set_decoder(dev);

	saa_call_all(dev, video, s_std, dev->tvnorm->id);
	/* Set the correct norm क्रम the saa6752hs. This function
	   करोes nothing अगर there is no saa6752hs. */
	saa_call_empress(dev, video, s_std, dev->tvnorm->id);
पूर्ण

अटल व्योम set_h_prescale(काष्ठा saa7134_dev *dev, पूर्णांक task, पूर्णांक prescale)
अणु
	अटल स्थिर काष्ठा अणु
		पूर्णांक xpsc;
		पूर्णांक xacl;
		पूर्णांक xc2_1;
		पूर्णांक xdcg;
		पूर्णांक vpfy;
	पूर्ण vals[] = अणु
		/* XPSC XACL XC2_1 XDCG VPFY */
		अणु    1,   0,    0,    0,   0 पूर्ण,
		अणु    2,   2,    1,    2,   2 पूर्ण,
		अणु    3,   4,    1,    3,   2 पूर्ण,
		अणु    4,   8,    1,    4,   2 पूर्ण,
		अणु    5,   8,    1,    4,   2 पूर्ण,
		अणु    6,   8,    1,    4,   3 पूर्ण,
		अणु    7,   8,    1,    4,   3 पूर्ण,
		अणु    8,  15,    0,    4,   3 पूर्ण,
		अणु    9,  15,    0,    4,   3 पूर्ण,
		अणु   10,  16,    1,    5,   3 पूर्ण,
	पूर्ण;
	अटल स्थिर पूर्णांक count = ARRAY_SIZE(vals);
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (vals[i].xpsc == prescale)
			अवरोध;
	अगर (i == count)
		वापस;

	saa_ग_लिखोb(SAA7134_H_PRESCALE(task), vals[i].xpsc);
	saa_ग_लिखोb(SAA7134_ACC_LENGTH(task), vals[i].xacl);
	saa_ग_लिखोb(SAA7134_LEVEL_CTRL(task),
		   (vals[i].xc2_1 << 3) | (vals[i].xdcg));
	saa_anकरोrb(SAA7134_FIR_PREFILTER_CTRL(task), 0x0f,
		   (vals[i].vpfy << 2) | vals[i].vpfy);
पूर्ण

अटल व्योम set_v_scale(काष्ठा saa7134_dev *dev, पूर्णांक task, पूर्णांक yscale)
अणु
	पूर्णांक val,mirror;

	saa_ग_लिखोb(SAA7134_V_SCALE_RATIO1(task), yscale &  0xff);
	saa_ग_लिखोb(SAA7134_V_SCALE_RATIO2(task), yscale >> 8);

	mirror = (dev->ctl_mirror) ? 0x02 : 0x00;
	अगर (yscale < 2048) अणु
		/* LPI */
		video_dbg("yscale LPI yscale=%d\n", yscale);
		saa_ग_लिखोb(SAA7134_V_FILTER(task), 0x00 | mirror);
		saa_ग_लिखोb(SAA7134_LUMA_CONTRAST(task), 0x40);
		saa_ग_लिखोb(SAA7134_CHROMA_SATURATION(task), 0x40);
	पूर्ण अन्यथा अणु
		/* ACM */
		val = 0x40 * 1024 / yscale;
		video_dbg("yscale ACM yscale=%d val=0x%x\n", yscale, val);
		saa_ग_लिखोb(SAA7134_V_FILTER(task), 0x01 | mirror);
		saa_ग_लिखोb(SAA7134_LUMA_CONTRAST(task), val);
		saa_ग_लिखोb(SAA7134_CHROMA_SATURATION(task), val);
	पूर्ण
	saa_ग_लिखोb(SAA7134_LUMA_BRIGHT(task),       0x80);
पूर्ण

अटल व्योम set_size(काष्ठा saa7134_dev *dev, पूर्णांक task,
		     पूर्णांक width, पूर्णांक height, पूर्णांक पूर्णांकerlace)
अणु
	पूर्णांक prescale,xscale,yscale,y_even,y_odd;
	पूर्णांक h_start, h_stop, v_start, v_stop;
	पूर्णांक भाग = पूर्णांकerlace ? 2 : 1;

	/* setup video scaler */
	h_start = dev->crop_current.left;
	v_start = dev->crop_current.top/2;
	h_stop  = (dev->crop_current.left + dev->crop_current.width -1);
	v_stop  = (dev->crop_current.top + dev->crop_current.height -1)/2;

	saa_ग_लिखोb(SAA7134_VIDEO_H_START1(task), h_start &  0xff);
	saa_ग_लिखोb(SAA7134_VIDEO_H_START2(task), h_start >> 8);
	saa_ग_लिखोb(SAA7134_VIDEO_H_STOP1(task),  h_stop  &  0xff);
	saa_ग_लिखोb(SAA7134_VIDEO_H_STOP2(task),  h_stop  >> 8);
	saa_ग_लिखोb(SAA7134_VIDEO_V_START1(task), v_start &  0xff);
	saa_ग_लिखोb(SAA7134_VIDEO_V_START2(task), v_start >> 8);
	saa_ग_लिखोb(SAA7134_VIDEO_V_STOP1(task),  v_stop  &  0xff);
	saa_ग_लिखोb(SAA7134_VIDEO_V_STOP2(task),  v_stop  >> 8);

	prescale = dev->crop_current.width / width;
	अगर (0 == prescale)
		prescale = 1;
	xscale = 1024 * dev->crop_current.width / prescale / width;
	yscale = 512 * भाग * dev->crop_current.height / height;
	video_dbg("prescale=%d xscale=%d yscale=%d\n",
		  prescale, xscale, yscale);
	set_h_prescale(dev,task,prescale);
	saa_ग_लिखोb(SAA7134_H_SCALE_INC1(task),      xscale &  0xff);
	saa_ग_लिखोb(SAA7134_H_SCALE_INC2(task),      xscale >> 8);
	set_v_scale(dev,task,yscale);

	saa_ग_लिखोb(SAA7134_VIDEO_PIXELS1(task),     width  & 0xff);
	saa_ग_लिखोb(SAA7134_VIDEO_PIXELS2(task),     width  >> 8);
	saa_ग_लिखोb(SAA7134_VIDEO_LINES1(task),      height/भाग & 0xff);
	saa_ग_लिखोb(SAA7134_VIDEO_LINES2(task),      height/भाग >> 8);

	/* deपूर्णांकerlace y offsets */
	y_odd  = dev->ctl_y_odd;
	y_even = dev->ctl_y_even;
	saa_ग_लिखोb(SAA7134_V_PHASE_OFFSET0(task), y_odd);
	saa_ग_लिखोb(SAA7134_V_PHASE_OFFSET1(task), y_even);
	saa_ग_लिखोb(SAA7134_V_PHASE_OFFSET2(task), y_odd);
	saa_ग_लिखोb(SAA7134_V_PHASE_OFFSET3(task), y_even);
पूर्ण

/* ------------------------------------------------------------------ */

काष्ठा cliplist अणु
	__u16 position;
	__u8  enable;
	__u8  disable;
पूर्ण;

अटल व्योम set_cliplist(काष्ठा saa7134_dev *dev, पूर्णांक reg,
			काष्ठा cliplist *cl, पूर्णांक entries, अक्षर *name)
अणु
	__u8 winbits = 0;
	पूर्णांक i;

	क्रम (i = 0; i < entries; i++) अणु
		winbits |= cl[i].enable;
		winbits &= ~cl[i].disable;
		अगर (i < 15 && cl[i].position == cl[i+1].position)
			जारी;
		saa_ग_लिखोb(reg + 0, winbits);
		saa_ग_लिखोb(reg + 2, cl[i].position & 0xff);
		saa_ग_लिखोb(reg + 3, cl[i].position >> 8);
		video_dbg("clip: %s winbits=%02x pos=%d\n",
			name,winbits,cl[i].position);
		reg += 8;
	पूर्ण
	क्रम (; reg < 0x400; reg += 8) अणु
		saa_ग_लिखोb(reg+ 0, 0);
		saa_ग_लिखोb(reg + 1, 0);
		saa_ग_लिखोb(reg + 2, 0);
		saa_ग_लिखोb(reg + 3, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक clip_range(पूर्णांक val)
अणु
	अगर (val < 0)
		val = 0;
	वापस val;
पूर्ण

/* Sort पूर्णांकo smallest position first order */
अटल पूर्णांक cliplist_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा cliplist *cla = a;
	स्थिर काष्ठा cliplist *clb = b;
	अगर (cla->position < clb->position)
		वापस -1;
	अगर (cla->position > clb->position)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक setup_clipping(काष्ठा saa7134_dev *dev, काष्ठा v4l2_clip *clips,
			  पूर्णांक nclips, पूर्णांक पूर्णांकerlace)
अणु
	काष्ठा cliplist col[16], row[16];
	पूर्णांक cols = 0, rows = 0, i;
	पूर्णांक भाग = पूर्णांकerlace ? 2 : 1;

	स_रखो(col, 0, माप(col));
	स_रखो(row, 0, माप(row));
	क्रम (i = 0; i < nclips && i < 8; i++) अणु
		col[cols].position = clip_range(clips[i].c.left);
		col[cols].enable   = (1 << i);
		cols++;
		col[cols].position = clip_range(clips[i].c.left+clips[i].c.width);
		col[cols].disable  = (1 << i);
		cols++;
		row[rows].position = clip_range(clips[i].c.top / भाग);
		row[rows].enable   = (1 << i);
		rows++;
		row[rows].position = clip_range((clips[i].c.top + clips[i].c.height)
						/ भाग);
		row[rows].disable  = (1 << i);
		rows++;
	पूर्ण
	sort(col, cols, माप col[0], cliplist_cmp, शून्य);
	sort(row, rows, माप row[0], cliplist_cmp, शून्य);
	set_cliplist(dev,0x380,col,cols,"cols");
	set_cliplist(dev,0x384,row,rows,"rows");
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_preview(काष्ठा saa7134_dev *dev, काष्ठा v4l2_winकरोw *win, bool try)
अणु
	क्रमागत v4l2_field field;
	पूर्णांक maxw, maxh;

	अगर (!try && (dev->ovbuf.base == शून्य || dev->ovfmt == शून्य))
		वापस -EINVAL;
	अगर (win->w.width < 48)
		win->w.width = 48;
	अगर (win->w.height < 32)
		win->w.height = 32;
	अगर (win->clipcount > 8)
		win->clipcount = 8;

	win->chromakey = 0;
	win->global_alpha = 0;
	field = win->field;
	maxw  = dev->crop_current.width;
	maxh  = dev->crop_current.height;

	अगर (V4L2_FIELD_ANY == field) अणु
		field = (win->w.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
	पूर्ण
	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		अवरोध;
	शेष:
		field = V4L2_FIELD_INTERLACED;
		अवरोध;
	पूर्ण

	win->field = field;
	अगर (win->w.width > maxw)
		win->w.width = maxw;
	अगर (win->w.height > maxh)
		win->w.height = maxh;
	वापस 0;
पूर्ण

अटल पूर्णांक start_preview(काष्ठा saa7134_dev *dev)
अणु
	अचिन्हित दीर्घ base,control,bpl;
	पूर्णांक err;

	err = verअगरy_preview(dev, &dev->win, false);
	अगर (0 != err)
		वापस err;

	dev->ovfield = dev->win.field;
	video_dbg("%s %dx%d+%d+%d 0x%08x field=%s\n", __func__,
		  dev->win.w.width, dev->win.w.height,
		  dev->win.w.left, dev->win.w.top,
		  dev->ovfmt->fourcc, v4l2_field_names[dev->ovfield]);

	/* setup winकरोw + clipping */
	set_size(dev, TASK_B, dev->win.w.width, dev->win.w.height,
		 V4L2_FIELD_HAS_BOTH(dev->ovfield));
	setup_clipping(dev, dev->clips, dev->nclips,
		       V4L2_FIELD_HAS_BOTH(dev->ovfield));
	अगर (dev->ovfmt->yuv)
		saa_anकरोrb(SAA7134_DATA_PATH(TASK_B), 0x3f, 0x03);
	अन्यथा
		saa_anकरोrb(SAA7134_DATA_PATH(TASK_B), 0x3f, 0x01);
	saa_ग_लिखोb(SAA7134_OFMT_VIDEO_B, dev->ovfmt->pm | 0x20);

	/* dma: setup channel 1 (= Video Task B) */
	base  = (अचिन्हित दीर्घ)dev->ovbuf.base;
	base += dev->ovbuf.fmt.bytesperline * dev->win.w.top;
	base += dev->ovfmt->depth/8         * dev->win.w.left;
	bpl   = dev->ovbuf.fmt.bytesperline;
	control = SAA7134_RS_CONTROL_BURST_16;
	अगर (dev->ovfmt->bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;
	अगर (dev->ovfmt->wswap)
		control |= SAA7134_RS_CONTROL_WSWAP;
	अगर (V4L2_FIELD_HAS_BOTH(dev->ovfield)) अणु
		saa_ग_लिखोl(SAA7134_RS_BA1(1),base);
		saa_ग_लिखोl(SAA7134_RS_BA2(1),base+bpl);
		saa_ग_लिखोl(SAA7134_RS_PITCH(1),bpl*2);
		saa_ग_लिखोl(SAA7134_RS_CONTROL(1),control);
	पूर्ण अन्यथा अणु
		saa_ग_लिखोl(SAA7134_RS_BA1(1),base);
		saa_ग_लिखोl(SAA7134_RS_BA2(1),base);
		saa_ग_लिखोl(SAA7134_RS_PITCH(1),bpl);
		saa_ग_लिखोl(SAA7134_RS_CONTROL(1),control);
	पूर्ण

	/* start dma */
	dev->ovenable = 1;
	saa7134_set_dmabits(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक stop_preview(काष्ठा saa7134_dev *dev)
अणु
	dev->ovenable = 0;
	saa7134_set_dmabits(dev);
	वापस 0;
पूर्ण

/*
 * Media Controller helper functions
 */

अटल पूर्णांक saa7134_enable_analog_tuner(काष्ठा saa7134_dev *dev)
अणु
#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *mdev = dev->media_dev;
	काष्ठा media_entity *source;
	काष्ठा media_link *link, *found_link = शून्य;
	पूर्णांक ret, active_links = 0;

	अगर (!mdev || !dev->decoder)
		वापस 0;

	/*
	 * This will find the tuner that is connected पूर्णांकo the decoder.
	 * Technically, this is not 100% correct, as the device may be
	 * using an analog input instead of the tuner. However, as we can't
	 * करो DVB streaming जबतक the DMA engine is being used क्रम V4L2,
	 * this should be enough क्रम the actual needs.
	 */
	list_क्रम_each_entry(link, &dev->decoder->links, list) अणु
		अगर (link->sink->entity == dev->decoder) अणु
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

		अगर (sink == dev->decoder)
			flags = MEDIA_LNK_FL_ENABLED;

		ret = media_entity_setup_link(link, flags);
		अगर (ret) अणु
			pr_err("Couldn't change link %s->%s to %s. Error %d\n",
			       source->name, sink->name,
			       flags ? "enabled" : "disabled",
			       ret);
			वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक buffer_activate(काष्ठा saa7134_dev *dev,
			   काष्ठा saa7134_buf *buf,
			   काष्ठा saa7134_buf *next)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = buf->vb2.vb2_buf.vb2_queue->drv_priv;
	अचिन्हित दीर्घ base,control,bpl;
	अचिन्हित दीर्घ bpl_uv,lines_uv,base2,base3,पंचांगp; /* planar */

	video_dbg("buffer_activate buf=%p\n", buf);
	buf->top_seen = 0;

	set_size(dev, TASK_A, dev->width, dev->height,
		 V4L2_FIELD_HAS_BOTH(dev->field));
	अगर (dev->fmt->yuv)
		saa_anकरोrb(SAA7134_DATA_PATH(TASK_A), 0x3f, 0x03);
	अन्यथा
		saa_anकरोrb(SAA7134_DATA_PATH(TASK_A), 0x3f, 0x01);
	saa_ग_लिखोb(SAA7134_OFMT_VIDEO_A, dev->fmt->pm);

	/* DMA: setup channel 0 (= Video Task A0) */
	base  = saa7134_buffer_base(buf);
	अगर (dev->fmt->planar)
		bpl = dev->width;
	अन्यथा
		bpl = (dev->width * dev->fmt->depth) / 8;
	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(dmaq->pt.dma >> 12);
	अगर (dev->fmt->bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;
	अगर (dev->fmt->wswap)
		control |= SAA7134_RS_CONTROL_WSWAP;
	अगर (V4L2_FIELD_HAS_BOTH(dev->field)) अणु
		/* पूर्णांकerlaced */
		saa_ग_लिखोl(SAA7134_RS_BA1(0),base);
		saa_ग_लिखोl(SAA7134_RS_BA2(0),base+bpl);
		saa_ग_लिखोl(SAA7134_RS_PITCH(0),bpl*2);
	पूर्ण अन्यथा अणु
		/* non-पूर्णांकerlaced */
		saa_ग_लिखोl(SAA7134_RS_BA1(0),base);
		saa_ग_लिखोl(SAA7134_RS_BA2(0),base);
		saa_ग_लिखोl(SAA7134_RS_PITCH(0),bpl);
	पूर्ण
	saa_ग_लिखोl(SAA7134_RS_CONTROL(0),control);

	अगर (dev->fmt->planar) अणु
		/* DMA: setup channel 4+5 (= planar task A) */
		bpl_uv   = bpl >> dev->fmt->hshअगरt;
		lines_uv = dev->height >> dev->fmt->vshअगरt;
		base2    = base + bpl * dev->height;
		base3    = base2 + bpl_uv * lines_uv;
		अगर (dev->fmt->uvswap) अणु
			पंचांगp = base2;
			base2 = base3;
			base3 = पंचांगp;
		पूर्ण
		video_dbg("uv: bpl=%ld lines=%ld base2/3=%ld/%ld\n",
			bpl_uv,lines_uv,base2,base3);
		अगर (V4L2_FIELD_HAS_BOTH(dev->field)) अणु
			/* पूर्णांकerlaced */
			saa_ग_लिखोl(SAA7134_RS_BA1(4),base2);
			saa_ग_लिखोl(SAA7134_RS_BA2(4),base2+bpl_uv);
			saa_ग_लिखोl(SAA7134_RS_PITCH(4),bpl_uv*2);
			saa_ग_लिखोl(SAA7134_RS_BA1(5),base3);
			saa_ग_लिखोl(SAA7134_RS_BA2(5),base3+bpl_uv);
			saa_ग_लिखोl(SAA7134_RS_PITCH(5),bpl_uv*2);
		पूर्ण अन्यथा अणु
			/* non-पूर्णांकerlaced */
			saa_ग_लिखोl(SAA7134_RS_BA1(4),base2);
			saa_ग_लिखोl(SAA7134_RS_BA2(4),base2);
			saa_ग_लिखोl(SAA7134_RS_PITCH(4),bpl_uv);
			saa_ग_लिखोl(SAA7134_RS_BA1(5),base3);
			saa_ग_लिखोl(SAA7134_RS_BA2(5),base3);
			saa_ग_लिखोl(SAA7134_RS_PITCH(5),bpl_uv);
		पूर्ण
		saa_ग_लिखोl(SAA7134_RS_CONTROL(4),control);
		saa_ग_लिखोl(SAA7134_RS_CONTROL(5),control);
	पूर्ण

	/* start DMA */
	saa7134_set_dmabits(dev);
	mod_समयr(&dmaq->समयout, jअगरfies + BUFFER_TIMEOUT);
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_init(काष्ठा vb2_buffer *vb2)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vb2->vb2_queue->drv_priv;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	काष्ठा saa7134_buf *buf = container_of(vbuf, काष्ठा saa7134_buf, vb2);

	dmaq->curr = शून्य;
	buf->activate = buffer_activate;
	वापस 0;
पूर्ण

अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb2)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vb2->vb2_queue->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb2);
	काष्ठा saa7134_buf *buf = container_of(vbuf, काष्ठा saa7134_buf, vb2);
	काष्ठा sg_table *dma = vb2_dma_sg_plane_desc(vb2, 0);
	अचिन्हित पूर्णांक size;

	अगर (dma->sgl->offset) अणु
		pr_err("The buffer is not page-aligned\n");
		वापस -EINVAL;
	पूर्ण
	size = (dev->width * dev->height * dev->fmt->depth) >> 3;
	अगर (vb2_plane_size(vb2, 0) < size)
		वापस -EINVAL;

	vb2_set_plane_payload(vb2, 0, size);
	vbuf->field = dev->field;

	वापस saa7134_pgtable_build(dev->pci, &dmaq->pt, dma->sgl, dma->nents,
				    saa7134_buffer_startpage(buf));
पूर्ण

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा saa7134_dmaqueue *dmaq = q->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	पूर्णांक size = dev->fmt->depth * dev->width * dev->height >> 3;

	अगर (dev->width    < 48 ||
	    dev->height   < 32 ||
	    dev->width/4  > dev->crop_current.width  ||
	    dev->height/4 > dev->crop_current.height ||
	    dev->width    > dev->crop_bounds.width  ||
	    dev->height   > dev->crop_bounds.height)
		वापस -EINVAL;

	*nbuffers = saa7134_buffer_count(size, *nbuffers);
	*nplanes = 1;
	sizes[0] = size;

	saa7134_enable_analog_tuner(dev);

	वापस 0;
पूर्ण

/*
 * move buffer to hardware queue
 */
व्योम saa7134_vb2_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vb->vb2_queue->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा saa7134_buf *buf = container_of(vbuf, काष्ठा saa7134_buf, vb2);

	saa7134_buffer_queue(dev, dmaq, buf);
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_vb2_buffer_queue);

पूर्णांक saa7134_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vq->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;

	/*
	 * Planar video capture and TS share the same DMA channel,
	 * so only one can be active at a समय.
	 */
	अगर (card_is_empress(dev) && vb2_is_busy(&dev->empress_vbq) &&
	    dmaq == &dev->video_q && dev->fmt->planar) अणु
		काष्ठा saa7134_buf *buf, *पंचांगp;

		list_क्रम_each_entry_safe(buf, पंचांगp, &dmaq->queue, entry) अणु
			list_del(&buf->entry);
			vb2_buffer_करोne(&buf->vb2.vb2_buf,
					VB2_BUF_STATE_QUEUED);
		पूर्ण
		अगर (dmaq->curr) अणु
			vb2_buffer_करोne(&dmaq->curr->vb2.vb2_buf,
					VB2_BUF_STATE_QUEUED);
			dmaq->curr = शून्य;
		पूर्ण
		वापस -EBUSY;
	पूर्ण

	/* The SAA7134 has a 1K FIFO; the datasheet suggests that when
	 * configured conservatively, there's 22 usec of buffering क्रम video.
	 * We thereक्रमe request a DMA latency of 20 usec, giving us 2 usec of
	 * margin in हाल the FIFO is configured dअगरferently to the datasheet.
	 * Unक्रमtunately, I lack रेजिस्टर-level करोcumentation to check the
	 * Linux FIFO setup and confirm the perfect value.
	 */
	अगर ((dmaq == &dev->video_q && !vb2_is_streaming(&dev->vbi_vbq)) ||
	    (dmaq == &dev->vbi_q && !vb2_is_streaming(&dev->video_vbq)))
		cpu_latency_qos_add_request(&dev->qos_request, 20);
	dmaq->seq_nr = 0;

	वापस 0;
पूर्ण

व्योम saa7134_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा saa7134_dmaqueue *dmaq = vq->drv_priv;
	काष्ठा saa7134_dev *dev = dmaq->dev;

	saa7134_stop_streaming(dev, dmaq);

	अगर ((dmaq == &dev->video_q && !vb2_is_streaming(&dev->vbi_vbq)) ||
	    (dmaq == &dev->vbi_q && !vb2_is_streaming(&dev->video_vbq)))
		cpu_latency_qos_हटाओ_request(&dev->qos_request);
पूर्ण

अटल स्थिर काष्ठा vb2_ops vb2_qops = अणु
	.queue_setup	= queue_setup,
	.buf_init	= buffer_init,
	.buf_prepare	= buffer_prepare,
	.buf_queue	= saa7134_vb2_buffer_queue,
	.रुको_prepare	= vb2_ops_रुको_prepare,
	.रुको_finish	= vb2_ops_रुको_finish,
	.start_streaming = saa7134_vb2_start_streaming,
	.stop_streaming = saa7134_vb2_stop_streaming,
पूर्ण;

/* ------------------------------------------------------------------ */

अटल पूर्णांक saa7134_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा saa7134_dev *dev = container_of(ctrl->handler, काष्ठा saa7134_dev, ctrl_handler);
	अचिन्हित दीर्घ flags;
	पूर्णांक restart_overlay = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		dev->ctl_bright = ctrl->val;
		saa_ग_लिखोb(SAA7134_DEC_LUMA_BRIGHT, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		dev->ctl_hue = ctrl->val;
		saa_ग_लिखोb(SAA7134_DEC_CHROMA_HUE, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		dev->ctl_contrast = ctrl->val;
		saa_ग_लिखोb(SAA7134_DEC_LUMA_CONTRAST,
			   dev->ctl_invert ? -dev->ctl_contrast : dev->ctl_contrast);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		dev->ctl_saturation = ctrl->val;
		saa_ग_लिखोb(SAA7134_DEC_CHROMA_SATURATION,
			   dev->ctl_invert ? -dev->ctl_saturation : dev->ctl_saturation);
		अवरोध;
	हाल V4L2_CID_AUDIO_MUTE:
		dev->ctl_mute = ctrl->val;
		saa7134_tvaudio_seपंचांगute(dev);
		अवरोध;
	हाल V4L2_CID_AUDIO_VOLUME:
		dev->ctl_volume = ctrl->val;
		saa7134_tvaudio_setvolume(dev,dev->ctl_volume);
		अवरोध;
	हाल V4L2_CID_PRIVATE_INVERT:
		dev->ctl_invert = ctrl->val;
		saa_ग_लिखोb(SAA7134_DEC_LUMA_CONTRAST,
			   dev->ctl_invert ? -dev->ctl_contrast : dev->ctl_contrast);
		saa_ग_लिखोb(SAA7134_DEC_CHROMA_SATURATION,
			   dev->ctl_invert ? -dev->ctl_saturation : dev->ctl_saturation);
		अवरोध;
	हाल V4L2_CID_HFLIP:
		dev->ctl_mirror = ctrl->val;
		restart_overlay = 1;
		अवरोध;
	हाल V4L2_CID_PRIVATE_Y_EVEN:
		dev->ctl_y_even = ctrl->val;
		restart_overlay = 1;
		अवरोध;
	हाल V4L2_CID_PRIVATE_Y_ODD:
		dev->ctl_y_odd = ctrl->val;
		restart_overlay = 1;
		अवरोध;
	हाल V4L2_CID_PRIVATE_AUTOMUTE:
	अणु
		काष्ठा v4l2_priv_tun_config tda9887_cfg;

		tda9887_cfg.tuner = TUNER_TDA9887;
		tda9887_cfg.priv = &dev->tda9887_conf;

		dev->ctl_स्वतःmute = ctrl->val;
		अगर (dev->tda9887_conf) अणु
			अगर (dev->ctl_स्वतःmute)
				dev->tda9887_conf |= TDA9887_AUTOMUTE;
			अन्यथा
				dev->tda9887_conf &= ~TDA9887_AUTOMUTE;

			saa_call_all(dev, tuner, s_config, &tda9887_cfg);
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (restart_overlay && dev->overlay_owner) अणु
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev);
		start_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक video_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	पूर्णांक ret = v4l2_fh_खोलो(file);

	अगर (ret < 0)
		वापस ret;

	mutex_lock(&dev->lock);
	अगर (vdev->vfl_type == VFL_TYPE_RADIO) अणु
		/* चयन to radio mode */
		saa7134_tvaudio_setinput(dev, &card(dev).radio);
		saa_call_all(dev, tuner, s_radio);
	पूर्ण अन्यथा अणु
		/* चयन to video/vbi mode */
		video_mux(dev, dev->ctl_input);
	पूर्ण
	mutex_unlock(&dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक video_release(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा v4l2_fh *fh = file->निजी_data;
	काष्ठा saa6588_command cmd;
	अचिन्हित दीर्घ flags;

	mutex_lock(&dev->lock);
	saa7134_tvaudio_बंद(dev);

	/* turn off overlay */
	अगर (fh == dev->overlay_owner) अणु
		spin_lock_irqsave(&dev->slock,flags);
		stop_preview(dev);
		spin_unlock_irqrestore(&dev->slock,flags);
		dev->overlay_owner = शून्य;
	पूर्ण

	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		v4l2_fh_release(file);
	अन्यथा
		_vb2_fop_release(file, शून्य);

	/* ts-capture will not work in planar mode, so turn it off Hac: 04.05*/
	saa_anकरोrb(SAA7134_OFMT_VIDEO_A, 0x1f, 0);
	saa_anकरोrb(SAA7134_OFMT_VIDEO_B, 0x1f, 0);
	saa_anकरोrb(SAA7134_OFMT_DATA_A, 0x1f, 0);
	saa_anकरोrb(SAA7134_OFMT_DATA_B, 0x1f, 0);

	saa_call_all(dev, tuner, standby);
	अगर (vdev->vfl_type == VFL_TYPE_RADIO)
		saa_call_all(dev, core, ioctl, SAA6588_CMD_CLOSE, &cmd);
	mutex_unlock(&dev->lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार radio_पढ़ो(काष्ठा file *file, अक्षर __user *data,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा saa6588_command cmd;

	cmd.block_count = count/3;
	cmd.nonblocking = file->f_flags & O_NONBLOCK;
	cmd.buffer = data;
	cmd.instance = file;
	cmd.result = -ENODEV;

	mutex_lock(&dev->lock);
	saa_call_all(dev, core, ioctl, SAA6588_CMD_READ, &cmd);
	mutex_unlock(&dev->lock);

	वापस cmd.result;
पूर्ण

अटल __poll_t radio_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा saa6588_command cmd;
	__poll_t rc = v4l2_ctrl_poll(file, रुको);

	cmd.instance = file;
	cmd.event_list = रुको;
	cmd.poll_mask = 0;
	mutex_lock(&dev->lock);
	saa_call_all(dev, core, ioctl, SAA6588_CMD_POLL, &cmd);
	mutex_unlock(&dev->lock);

	वापस rc | cmd.poll_mask;
पूर्ण

/* ------------------------------------------------------------------ */

अटल पूर्णांक saa7134_try_get_set_fmt_vbi_cap(काष्ठा file *file, व्योम *priv,
						काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा saa7134_tvnorm *norm = dev->tvnorm;

	स_रखो(&f->fmt.vbi.reserved, 0, माप(f->fmt.vbi.reserved));
	f->fmt.vbi.sampling_rate = 6750000 * 4;
	f->fmt.vbi.samples_per_line = 2048 /* VBI_LINE_LENGTH */;
	f->fmt.vbi.sample_क्रमmat = V4L2_PIX_FMT_GREY;
	f->fmt.vbi.offset = 64 * 4;
	f->fmt.vbi.start[0] = norm->vbi_v_start_0;
	f->fmt.vbi.count[0] = norm->vbi_v_stop_0 - norm->vbi_v_start_0 +1;
	f->fmt.vbi.start[1] = norm->vbi_v_start_1;
	f->fmt.vbi.count[1] = f->fmt.vbi.count[0];
	f->fmt.vbi.flags = 0; /* VBI_UNSYNC VBI_INTERLACED */

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	f->fmt.pix.width        = dev->width;
	f->fmt.pix.height       = dev->height;
	f->fmt.pix.field        = dev->field;
	f->fmt.pix.pixelक्रमmat  = dev->fmt->fourcc;
	अगर (dev->fmt->planar)
		f->fmt.pix.bytesperline = f->fmt.pix.width;
	अन्यथा
		f->fmt.pix.bytesperline =
			(f->fmt.pix.width * dev->fmt->depth) / 8;
	f->fmt.pix.sizeimage =
		(f->fmt.pix.height * f->fmt.pix.width * dev->fmt->depth) / 8;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_g_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	u32 clipcount = f->fmt.win.clipcount;
	पूर्णांक i;

	अगर (saa7134_no_overlay > 0) अणु
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		वापस -EINVAL;
	पूर्ण
	f->fmt.win = dev->win;
	अगर (!f->fmt.win.clips) अणु
		f->fmt.win.clipcount = 0;
		वापस 0;
	पूर्ण
	अगर (dev->nclips < clipcount)
		clipcount = dev->nclips;
	f->fmt.win.clipcount = clipcount;

	क्रम (i = 0; i < clipcount; i++) अणु
		स_नकल(&f->fmt.win.clips[i].c, &dev->clips[i].c,
		       माप(काष्ठा v4l2_rect));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
						काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा saa7134_क्रमmat *fmt;
	क्रमागत v4l2_field field;
	अचिन्हित पूर्णांक maxw, maxh;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;

	field = f->fmt.pix.field;
	maxw  = min(dev->crop_current.width*4,  dev->crop_bounds.width);
	maxh  = min(dev->crop_current.height*4, dev->crop_bounds.height);

	अगर (V4L2_FIELD_ANY == field) अणु
		field = (f->fmt.pix.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
	पूर्ण
	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		अवरोध;
	शेष:
		field = V4L2_FIELD_INTERLACED;
		अवरोध;
	पूर्ण

	f->fmt.pix.field = field;
	अगर (f->fmt.pix.width  < 48)
		f->fmt.pix.width  = 48;
	अगर (f->fmt.pix.height < 32)
		f->fmt.pix.height = 32;
	अगर (f->fmt.pix.width > maxw)
		f->fmt.pix.width = maxw;
	अगर (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;
	f->fmt.pix.width &= ~0x03;
	अगर (fmt->planar)
		f->fmt.pix.bytesperline = f->fmt.pix.width;
	अन्यथा
		f->fmt.pix.bytesperline =
			(f->fmt.pix.width * fmt->depth) / 8;
	f->fmt.pix.sizeimage =
		(f->fmt.pix.height * f->fmt.pix.width * fmt->depth) / 8;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_try_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
						काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (saa7134_no_overlay > 0) अणु
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		वापस -EINVAL;
	पूर्ण

	अगर (f->fmt.win.clips == शून्य)
		f->fmt.win.clipcount = 0;
	वापस verअगरy_preview(dev, &f->fmt.win, true);
पूर्ण

अटल पूर्णांक saa7134_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	पूर्णांक err;

	err = saa7134_try_fmt_vid_cap(file, priv, f);
	अगर (0 != err)
		वापस err;

	dev->fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	dev->width = f->fmt.pix.width;
	dev->height = f->fmt.pix.height;
	dev->field = f->fmt.pix.field;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_s_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	पूर्णांक err;
	अचिन्हित दीर्घ flags;

	अगर (saa7134_no_overlay > 0) अणु
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		वापस -EINVAL;
	पूर्ण
	अगर (f->fmt.win.clips == शून्य)
		f->fmt.win.clipcount = 0;
	err = verअगरy_preview(dev, &f->fmt.win, true);
	अगर (0 != err)
		वापस err;

	dev->win    = f->fmt.win;
	dev->nclips = f->fmt.win.clipcount;

	स_नकल(dev->clips, f->fmt.win.clips,
	       माप(काष्ठा v4l2_clip) * dev->nclips);

	अगर (priv == dev->overlay_owner) अणु
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev);
		start_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक saa7134_क्रमागत_input(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *i)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	अचिन्हित पूर्णांक n;

	n = i->index;
	अगर (n >= SAA7134_INPUT_MAX)
		वापस -EINVAL;
	अगर (card_in(dev, i->index).type == SAA7134_NO_INPUT)
		वापस -EINVAL;
	i->index = n;
	strscpy(i->name, saa7134_input_name[card_in(dev, n).type],
		माप(i->name));
	चयन (card_in(dev, n).type) अणु
	हाल SAA7134_INPUT_TV:
	हाल SAA7134_INPUT_TV_MONO:
		i->type = V4L2_INPUT_TYPE_TUNER;
		अवरोध;
	शेष:
		i->type  = V4L2_INPUT_TYPE_CAMERA;
		अवरोध;
	पूर्ण
	अगर (n == dev->ctl_input) अणु
		पूर्णांक v1 = saa_पढ़ोb(SAA7134_STATUS_VIDEO1);
		पूर्णांक v2 = saa_पढ़ोb(SAA7134_STATUS_VIDEO2);

		अगर (0 != (v1 & 0x40))
			i->status |= V4L2_IN_ST_NO_H_LOCK;
		अगर (0 != (v2 & 0x40))
			i->status |= V4L2_IN_ST_NO_SIGNAL;
		अगर (0 != (v2 & 0x0e))
			i->status |= V4L2_IN_ST_MACROVISION;
	पूर्ण
	i->std = SAA7134_NORMS;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_क्रमागत_input);

पूर्णांक saa7134_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	*i = dev->ctl_input;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_g_input);

पूर्णांक saa7134_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (i >= SAA7134_INPUT_MAX)
		वापस -EINVAL;
	अगर (card_in(dev, i).type == SAA7134_NO_INPUT)
		वापस -EINVAL;
	video_mux(dev, i);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_s_input);

पूर्णांक saa7134_querycap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_capability *cap)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	strscpy(cap->driver, "saa7134", माप(cap->driver));
	strscpy(cap->card, saa7134_boards[dev->board].name,
		माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCI:%s", pci_name(dev->pci));
	cap->capabilities = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
			    V4L2_CAP_RADIO | V4L2_CAP_VIDEO_CAPTURE |
			    V4L2_CAP_VBI_CAPTURE | V4L2_CAP_DEVICE_CAPS;
	अगर (dev->tuner_type != TUNER_ABSENT && dev->tuner_type != UNSET)
		cap->capabilities |= V4L2_CAP_TUNER;
	अगर (dev->has_rds)
		cap->capabilities |= V4L2_CAP_RDS_CAPTURE;
	अगर (saa7134_no_overlay <= 0)
		cap->capabilities |= V4L2_CAP_VIDEO_OVERLAY;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_querycap);

पूर्णांक saa7134_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा v4l2_fh *fh = priv;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	v4l2_std_id fixup;

	अगर (is_empress(file) && dev->overlay_owner) अणु
		/* Don't change the std from the mpeg device
		   अगर overlay is active. */
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < TVNORMS; i++)
		अगर (id == tvnorms[i].id)
			अवरोध;

	अगर (i == TVNORMS)
		क्रम (i = 0; i < TVNORMS; i++)
			अगर (id & tvnorms[i].id)
				अवरोध;
	अगर (i == TVNORMS)
		वापस -EINVAL;

	अगर ((id & V4L2_STD_SECAM) && (secam[0] != '-')) अणु
		अगर (secam[0] == 'L' || secam[0] == 'l') अणु
			अगर (secam[1] == 'C' || secam[1] == 'c')
				fixup = V4L2_STD_SECAM_LC;
			अन्यथा
				fixup = V4L2_STD_SECAM_L;
		पूर्ण अन्यथा अणु
			अगर (secam[0] == 'D' || secam[0] == 'd')
				fixup = V4L2_STD_SECAM_DK;
			अन्यथा
				fixup = V4L2_STD_SECAM;
		पूर्ण
		क्रम (i = 0; i < TVNORMS; i++) अणु
			अगर (fixup == tvnorms[i].id)
				अवरोध;
		पूर्ण
		अगर (i == TVNORMS)
			वापस -EINVAL;
	पूर्ण

	id = tvnorms[i].id;

	अगर (!is_empress(file) && fh == dev->overlay_owner) अणु
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);

		set_tvnorm(dev, &tvnorms[i]);

		spin_lock_irqsave(&dev->slock, flags);
		start_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	पूर्ण अन्यथा
		set_tvnorm(dev, &tvnorms[i]);

	saa7134_tvaudio_करो_scan(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_s_std);

पूर्णांक saa7134_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	*id = dev->tvnorm->id;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_g_std);

अटल v4l2_std_id saa7134_पढ़ो_std(काष्ठा saa7134_dev *dev)
अणु
	अटल v4l2_std_id stds[] = अणु
		V4L2_STD_UNKNOWN,
		V4L2_STD_NTSC,
		V4L2_STD_PAL,
		V4L2_STD_SECAM पूर्ण;

	v4l2_std_id result = 0;

	u8 st1 = saa_पढ़ोb(SAA7134_STATUS_VIDEO1);
	u8 st2 = saa_पढ़ोb(SAA7134_STATUS_VIDEO2);

	अगर (!(st2 & 0x1)) /* RDCAP == 0 */
		result = V4L2_STD_UNKNOWN;
	अन्यथा
		result = stds[st1 & 0x03];

	वापस result;
पूर्ण

पूर्णांक saa7134_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	*std &= saa7134_पढ़ो_std(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_querystd);

अटल पूर्णांक saa7134_g_pixelaspect(काष्ठा file *file, व्योम *priv,
				 पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		वापस -EINVAL;

	अगर (dev->tvnorm->id & V4L2_STD_525_60) अणु
		f->numerator   = 11;
		f->denominator = 10;
	पूर्ण
	अगर (dev->tvnorm->id & V4L2_STD_625_50) अणु
		f->numerator   = 54;
		f->denominator = 59;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_g_selection(काष्ठा file *file, व्योम *f, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		sel->r = dev->crop_current;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r = dev->crop_defrect;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r  = dev->crop_bounds;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_s_selection(काष्ठा file *file, व्योम *f, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा v4l2_rect *b = &dev->crop_bounds;
	काष्ठा v4l2_rect *c = &dev->crop_current;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		वापस -EINVAL;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	अगर (dev->overlay_owner)
		वापस -EBUSY;
	अगर (vb2_is_streaming(&dev->video_vbq))
		वापस -EBUSY;

	*c = sel->r;
	अगर (c->top < b->top)
		c->top = b->top;
	अगर (c->top > b->top + b->height)
		c->top = b->top + b->height;
	अगर (c->height > b->top - c->top + b->height)
		c->height = b->top - c->top + b->height;

	अगर (c->left < b->left)
		c->left = b->left;
	अगर (c->left > b->left + b->width)
		c->left = b->left + b->width;
	अगर (c->width > b->left - c->left + b->width)
		c->width = b->left - c->left + b->width;
	sel->r = *c;
	वापस 0;
पूर्ण

पूर्णांक saa7134_g_tuner(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	पूर्णांक n;

	अगर (0 != t->index)
		वापस -EINVAL;
	स_रखो(t, 0, माप(*t));
	क्रम (n = 0; n < SAA7134_INPUT_MAX; n++) अणु
		अगर (card_in(dev, n).type == SAA7134_INPUT_TV ||
		    card_in(dev, n).type == SAA7134_INPUT_TV_MONO)
			अवरोध;
	पूर्ण
	अगर (n == SAA7134_INPUT_MAX)
		वापस -EINVAL;
	अगर (card_in(dev, n).type != SAA7134_NO_INPUT) अणु
		strscpy(t->name, "Television", माप(t->name));
		t->type = V4L2_TUNER_ANALOG_TV;
		saa_call_all(dev, tuner, g_tuner, t);
		t->capability = V4L2_TUNER_CAP_NORM |
			V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_LANG1 |
			V4L2_TUNER_CAP_LANG2;
		t->rxsubchans = saa7134_tvaudio_माला_लोtereo(dev);
		t->audmode = saa7134_tvaudio_rx2mode(t->rxsubchans);
	पूर्ण
	अगर (0 != (saa_पढ़ोb(SAA7134_STATUS_VIDEO1) & 0x03))
		t->संकेत = 0xffff;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_g_tuner);

पूर्णांक saa7134_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	पूर्णांक rx, mode;

	अगर (0 != t->index)
		वापस -EINVAL;

	mode = dev->thपढ़ो.mode;
	अगर (UNSET == mode) अणु
		rx   = saa7134_tvaudio_माला_लोtereo(dev);
		mode = saa7134_tvaudio_rx2mode(rx);
	पूर्ण
	अगर (mode != t->audmode)
		dev->thपढ़ो.mode = t->audmode;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_s_tuner);

पूर्णांक saa7134_g_frequency(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (0 != f->tuner)
		वापस -EINVAL;

	saa_call_all(dev, tuner, g_frequency, f);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_g_frequency);

पूर्णांक saa7134_s_frequency(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (0 != f->tuner)
		वापस -EINVAL;

	saa_call_all(dev, tuner, s_frequency, f);

	saa7134_tvaudio_करो_scan(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(saa7134_s_frequency);

अटल पूर्णांक saa7134_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index >= FORMATS)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_क्रमागत_fmt_vid_overlay(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (saa7134_no_overlay > 0) अणु
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((f->index >= FORMATS) || क्रमmats[f->index].planar)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[f->index].fourcc;

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_g_fbuf(काष्ठा file *file, व्योम *f,
				काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	*fb = dev->ovbuf;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;

	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_s_fbuf(काष्ठा file *file, व्योम *f,
					स्थिर काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	काष्ठा saa7134_क्रमmat *fmt;

	अगर (!capable(CAP_SYS_ADMIN) &&
	   !capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	/* check args */
	fmt = क्रमmat_by_fourcc(fb->fmt.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;

	/* ok, accept it */
	dev->ovbuf = *fb;
	dev->ovfmt = fmt;
	अगर (0 == dev->ovbuf.fmt.bytesperline)
		dev->ovbuf.fmt.bytesperline =
			dev->ovbuf.fmt.width*fmt->depth/8;
	वापस 0;
पूर्ण

अटल पूर्णांक saa7134_overlay(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक on)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);
	अचिन्हित दीर्घ flags;

	अगर (on) अणु
		अगर (saa7134_no_overlay > 0) अणु
			video_dbg("no_overlay\n");
			वापस -EINVAL;
		पूर्ण

		अगर (dev->overlay_owner && priv != dev->overlay_owner)
			वापस -EBUSY;
		dev->overlay_owner = priv;
		spin_lock_irqsave(&dev->slock, flags);
		start_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
	पूर्ण
	अगर (!on) अणु
		अगर (priv != dev->overlay_owner)
			वापस -EINVAL;
		spin_lock_irqsave(&dev->slock, flags);
		stop_preview(dev);
		spin_unlock_irqrestore(&dev->slock, flags);
		dev->overlay_owner = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक vidioc_g_रेजिस्टर (काष्ठा file *file, व्योम *priv,
			      काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	reg->val = saa_पढ़ोb(reg->reg & 0xffffff);
	reg->size = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_रेजिस्टर (काष्ठा file *file, व्योम *priv,
				स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	saa_ग_लिखोb(reg->reg & 0xffffff, reg->val);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक radio_g_tuner(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (0 != t->index)
		वापस -EINVAL;

	strscpy(t->name, "Radio", माप(t->name));

	saa_call_all(dev, tuner, g_tuner, t);
	t->audmode &= V4L2_TUNER_MODE_MONO | V4L2_TUNER_MODE_STEREO;
	अगर (dev->input->amux == TV) अणु
		t->संकेत = 0xf800 - ((saa_पढ़ोb(0x581) & 0x1f) << 11);
		t->rxsubchans = (saa_पढ़ोb(0x529) & 0x08) ?
				V4L2_TUNER_SUB_STEREO : V4L2_TUNER_SUB_MONO;
	पूर्ण
	वापस 0;
पूर्ण
अटल पूर्णांक radio_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा saa7134_dev *dev = video_drvdata(file);

	अगर (0 != t->index)
		वापस -EINVAL;

	saa_call_all(dev, tuner, s_tuner, t);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations video_fops =
अणु
	.owner	  = THIS_MODULE,
	.खोलो	  = video_खोलो,
	.release  = video_release,
	.पढ़ो	  = vb2_fop_पढ़ो,
	.poll     = vb2_fop_poll,
	.mmap	  = vb2_fop_mmap,
	.unlocked_ioctl	  = video_ioctl2,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops video_ioctl_ops = अणु
	.vidioc_querycap		= saa7134_querycap,
	.vidioc_क्रमागत_fmt_vid_cap	= saa7134_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= saa7134_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap		= saa7134_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= saa7134_s_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_overlay	= saa7134_क्रमागत_fmt_vid_overlay,
	.vidioc_g_fmt_vid_overlay	= saa7134_g_fmt_vid_overlay,
	.vidioc_try_fmt_vid_overlay	= saa7134_try_fmt_vid_overlay,
	.vidioc_s_fmt_vid_overlay	= saa7134_s_fmt_vid_overlay,
	.vidioc_g_fmt_vbi_cap		= saa7134_try_get_set_fmt_vbi_cap,
	.vidioc_try_fmt_vbi_cap		= saa7134_try_get_set_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap		= saa7134_try_get_set_fmt_vbi_cap,
	.vidioc_g_pixelaspect		= saa7134_g_pixelaspect,
	.vidioc_reqbufs			= vb2_ioctl_reqbufs,
	.vidioc_querybuf		= vb2_ioctl_querybuf,
	.vidioc_qbuf			= vb2_ioctl_qbuf,
	.vidioc_dqbuf			= vb2_ioctl_dqbuf,
	.vidioc_expbuf			= vb2_ioctl_expbuf,
	.vidioc_s_std			= saa7134_s_std,
	.vidioc_g_std			= saa7134_g_std,
	.vidioc_querystd		= saa7134_querystd,
	.vidioc_क्रमागत_input		= saa7134_क्रमागत_input,
	.vidioc_g_input			= saa7134_g_input,
	.vidioc_s_input			= saa7134_s_input,
	.vidioc_streamon		= vb2_ioctl_streamon,
	.vidioc_streamoff		= vb2_ioctl_streamoff,
	.vidioc_g_tuner			= saa7134_g_tuner,
	.vidioc_s_tuner			= saa7134_s_tuner,
	.vidioc_g_selection		= saa7134_g_selection,
	.vidioc_s_selection		= saa7134_s_selection,
	.vidioc_g_fbuf			= saa7134_g_fbuf,
	.vidioc_s_fbuf			= saa7134_s_fbuf,
	.vidioc_overlay			= saa7134_overlay,
	.vidioc_g_frequency		= saa7134_g_frequency,
	.vidioc_s_frequency		= saa7134_s_frequency,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर              = vidioc_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर              = vidioc_s_रेजिस्टर,
#पूर्ण_अगर
	.vidioc_log_status		= v4l2_ctrl_log_status,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations radio_fops = अणु
	.owner	  = THIS_MODULE,
	.खोलो	  = video_खोलो,
	.पढ़ो     = radio_पढ़ो,
	.release  = video_release,
	.unlocked_ioctl	= video_ioctl2,
	.poll     = radio_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops radio_ioctl_ops = अणु
	.vidioc_querycap	= saa7134_querycap,
	.vidioc_g_tuner		= radio_g_tuner,
	.vidioc_s_tuner		= radio_s_tuner,
	.vidioc_g_frequency	= saa7134_g_frequency,
	.vidioc_s_frequency	= saa7134_s_frequency,
	.vidioc_subscribe_event	= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

/* ----------------------------------------------------------- */
/* exported stuff                                              */

काष्ठा video_device saa7134_video_ढाँचा = अणु
	.name				= "saa7134-video",
	.fops				= &video_fops,
	.ioctl_ops			= &video_ioctl_ops,
	.tvnorms			= SAA7134_NORMS,
पूर्ण;

काष्ठा video_device saa7134_radio_ढाँचा = अणु
	.name			= "saa7134-radio",
	.fops			= &radio_fops,
	.ioctl_ops		= &radio_ioctl_ops,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops saa7134_ctrl_ops = अणु
	.s_ctrl = saa7134_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config saa7134_ctrl_invert = अणु
	.ops = &saa7134_ctrl_ops,
	.id = V4L2_CID_PRIVATE_INVERT,
	.name = "Invert",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config saa7134_ctrl_y_odd = अणु
	.ops = &saa7134_ctrl_ops,
	.id = V4L2_CID_PRIVATE_Y_ODD,
	.name = "Y Offset Odd Field",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 128,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config saa7134_ctrl_y_even = अणु
	.ops = &saa7134_ctrl_ops,
	.id = V4L2_CID_PRIVATE_Y_EVEN,
	.name = "Y Offset Even Field",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 128,
	.step = 1,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_config saa7134_ctrl_स्वतःmute = अणु
	.ops = &saa7134_ctrl_ops,
	.id = V4L2_CID_PRIVATE_AUTOMUTE,
	.name = "Automute",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

पूर्णांक saa7134_video_init1(काष्ठा saa7134_dev *dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &dev->ctrl_handler;
	काष्ठा vb2_queue *q;
	पूर्णांक ret;

	/* sanitycheck insmod options */
	अगर (gbuffers < 2 || gbuffers > VIDEO_MAX_FRAME)
		gbuffers = 2;
	अगर (gbufsize > gbufsize_max)
		gbufsize = gbufsize_max;
	gbufsize = (gbufsize + PAGE_SIZE - 1) & PAGE_MASK;

	v4l2_ctrl_handler_init(hdl, 11);
	v4l2_ctrl_new_std(hdl, &saa7134_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &saa7134_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 127, 1, 68);
	v4l2_ctrl_new_std(hdl, &saa7134_ctrl_ops,
			V4L2_CID_SATURATION, 0, 127, 1, 64);
	v4l2_ctrl_new_std(hdl, &saa7134_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa7134_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa7134_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &saa7134_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, -15, 15, 1, 0);
	v4l2_ctrl_new_custom(hdl, &saa7134_ctrl_invert, शून्य);
	v4l2_ctrl_new_custom(hdl, &saa7134_ctrl_y_odd, शून्य);
	v4l2_ctrl_new_custom(hdl, &saa7134_ctrl_y_even, शून्य);
	v4l2_ctrl_new_custom(hdl, &saa7134_ctrl_स्वतःmute, शून्य);
	अगर (hdl->error)
		वापस hdl->error;
	अगर (card_has_radio(dev)) अणु
		hdl = &dev->radio_ctrl_handler;
		v4l2_ctrl_handler_init(hdl, 2);
		v4l2_ctrl_add_handler(hdl, &dev->ctrl_handler,
				v4l2_ctrl_radio_filter, false);
		अगर (hdl->error)
			वापस hdl->error;
	पूर्ण
	dev->ctl_mute       = 1;

	अगर (dev->tda9887_conf && saa7134_ctrl_स्वतःmute.def)
		dev->tda9887_conf |= TDA9887_AUTOMUTE;
	dev->स्वतःmute       = 0;

	INIT_LIST_HEAD(&dev->video_q.queue);
	समयr_setup(&dev->video_q.समयout, saa7134_buffer_समयout, 0);
	dev->video_q.dev              = dev;
	dev->fmt = क्रमmat_by_fourcc(V4L2_PIX_FMT_BGR24);
	dev->width    = 720;
	dev->height   = 576;
	dev->field = V4L2_FIELD_INTERLACED;
	dev->win.w.width = dev->width;
	dev->win.w.height = dev->height;
	dev->win.field = V4L2_FIELD_INTERLACED;
	dev->ovbuf.fmt.width = dev->width;
	dev->ovbuf.fmt.height = dev->height;
	dev->ovbuf.fmt.pixelक्रमmat = dev->fmt->fourcc;
	dev->ovbuf.fmt.colorspace = V4L2_COLORSPACE_SMPTE170M;

	अगर (saa7134_boards[dev->board].video_out)
		saa7134_videoport_init(dev);

	q = &dev->video_vbq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	/*
	 * Do not add VB2_USERPTR unless explicitly requested: the saa7134 DMA
	 * engine cannot handle transfers that करो not start at the beginning
	 * of a page. A user-provided poपूर्णांकer can start anywhere in a page, so
	 * USERPTR support is a no-go unless the application knows about these
	 * limitations and has special support क्रम this.
	 */
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	अगर (saa7134_userptr)
		q->io_modes |= VB2_USERPTR;
	q->drv_priv = &dev->video_q;
	q->ops = &vb2_qops;
	q->gfp_flags = GFP_DMA32;
	q->mem_ops = &vb2_dma_sg_memops;
	q->buf_काष्ठा_size = माप(काष्ठा saa7134_buf);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &dev->lock;
	q->dev = &dev->pci->dev;
	ret = vb2_queue_init(q);
	अगर (ret)
		वापस ret;
	saa7134_pgtable_alloc(dev->pci, &dev->video_q.pt);

	q = &dev->vbi_vbq;
	q->type = V4L2_BUF_TYPE_VBI_CAPTURE;
	/* Don't add VB2_USERPTR, see comment above */
	q->io_modes = VB2_MMAP | VB2_READ;
	अगर (saa7134_userptr)
		q->io_modes |= VB2_USERPTR;
	q->drv_priv = &dev->vbi_q;
	q->ops = &saa7134_vbi_qops;
	q->gfp_flags = GFP_DMA32;
	q->mem_ops = &vb2_dma_sg_memops;
	q->buf_काष्ठा_size = माप(काष्ठा saa7134_buf);
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &dev->lock;
	q->dev = &dev->pci->dev;
	ret = vb2_queue_init(q);
	अगर (ret)
		वापस ret;
	saa7134_pgtable_alloc(dev->pci, &dev->vbi_q.pt);

	वापस 0;
पूर्ण

व्योम saa7134_video_fini(काष्ठा saa7134_dev *dev)
अणु
	/* मुक्त stuff */
	saa7134_pgtable_मुक्त(dev->pci, &dev->video_q.pt);
	saa7134_pgtable_मुक्त(dev->pci, &dev->vbi_q.pt);
	v4l2_ctrl_handler_मुक्त(&dev->ctrl_handler);
	अगर (card_has_radio(dev))
		v4l2_ctrl_handler_मुक्त(&dev->radio_ctrl_handler);
पूर्ण

पूर्णांक saa7134_videoport_init(काष्ठा saa7134_dev *dev)
अणु
	/* enable video output */
	पूर्णांक vo = saa7134_boards[dev->board].video_out;
	पूर्णांक video_reg;
	अचिन्हित पूर्णांक vid_port_opts = saa7134_boards[dev->board].vid_port_opts;

	/* Configure videoport */
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL0, video_out[vo][0]);
	video_reg = video_out[vo][1];
	अगर (vid_port_opts & SET_T_CODE_POLARITY_NON_INVERTED)
		video_reg &= ~VP_T_CODE_P_INVERTED;
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL1, video_reg);
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL2, video_out[vo][2]);
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL4, video_out[vo][4]);
	video_reg = video_out[vo][5];
	अगर (vid_port_opts & SET_CLOCK_NOT_DELAYED)
		video_reg &= ~VP_CLK_CTRL2_DELAYED;
	अगर (vid_port_opts & SET_CLOCK_INVERTED)
		video_reg |= VP_CLK_CTRL1_INVERTED;
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL5, video_reg);
	video_reg = video_out[vo][6];
	अगर (vid_port_opts & SET_VSYNC_OFF) अणु
		video_reg &= ~VP_VS_TYPE_MASK;
		video_reg |= VP_VS_TYPE_OFF;
	पूर्ण
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL6, video_reg);
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL7, video_out[vo][7]);
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL8, video_out[vo][8]);

	/* Start videoport */
	saa_ग_लिखोb(SAA7134_VIDEO_PORT_CTRL3, video_out[vo][3]);

	वापस 0;
पूर्ण

पूर्णांक saa7134_video_init2(काष्ठा saa7134_dev *dev)
अणु
	/* init video hw */
	set_tvnorm(dev,&tvnorms[0]);
	video_mux(dev,0);
	v4l2_ctrl_handler_setup(&dev->ctrl_handler);
	saa7134_tvaudio_seपंचांगute(dev);
	saa7134_tvaudio_setvolume(dev,dev->ctl_volume);
	वापस 0;
पूर्ण

व्योम saa7134_irq_video_संकेतchange(काष्ठा saa7134_dev *dev)
अणु
	अटल स्थिर अक्षर *st[] = अणु
		"(no signal)", "NTSC", "PAL", "SECAM" पूर्ण;
	u32 st1,st2;

	st1 = saa_पढ़ोb(SAA7134_STATUS_VIDEO1);
	st2 = saa_पढ़ोb(SAA7134_STATUS_VIDEO2);
	video_dbg("DCSDT: pll: %s, sync: %s, norm: %s\n",
		(st1 & 0x40) ? "not locked" : "locked",
		(st2 & 0x40) ? "no"         : "yes",
		st[st1 & 0x03]);
	dev->noसंकेत = (st1 & 0x40) || (st2 & 0x40)  || !(st2 & 0x1);

	अगर (dev->noसंकेत) अणु
		/* no video संकेत -> mute audio */
		अगर (dev->ctl_स्वतःmute)
			dev->स्वतःmute = 1;
		saa7134_tvaudio_seपंचांगute(dev);
	पूर्ण अन्यथा अणु
		/* wake up tvaudio audio carrier scan thपढ़ो */
		saa7134_tvaudio_करो_scan(dev);
	पूर्ण

	अगर ((st2 & 0x80) && !nonपूर्णांकerlaced && !dev->noसंकेत)
		saa_clearb(SAA7134_SYNC_CTRL, 0x20);
	अन्यथा
		saa_setb(SAA7134_SYNC_CTRL, 0x20);

	अगर (dev->mops && dev->mops->संकेत_change)
		dev->mops->संकेत_change(dev);
पूर्ण


व्योम saa7134_irq_video_करोne(काष्ठा saa7134_dev *dev, अचिन्हित दीर्घ status)
अणु
	क्रमागत v4l2_field field;

	spin_lock(&dev->slock);
	अगर (dev->video_q.curr) अणु
		field = dev->field;
		अगर (V4L2_FIELD_HAS_BOTH(field)) अणु
			/* make sure we have seen both fields */
			अगर ((status & 0x10) == 0x00) अणु
				dev->video_q.curr->top_seen = 1;
				जाओ करोne;
			पूर्ण
			अगर (!dev->video_q.curr->top_seen)
				जाओ करोne;
		पूर्ण अन्यथा अगर (field == V4L2_FIELD_TOP) अणु
			अगर ((status & 0x10) != 0x10)
				जाओ करोne;
		पूर्ण अन्यथा अगर (field == V4L2_FIELD_BOTTOM) अणु
			अगर ((status & 0x10) != 0x00)
				जाओ करोne;
		पूर्ण
		saa7134_buffer_finish(dev, &dev->video_q, VB2_BUF_STATE_DONE);
	पूर्ण
	saa7134_buffer_next(dev, &dev->video_q);

 करोne:
	spin_unlock(&dev->slock);
पूर्ण
