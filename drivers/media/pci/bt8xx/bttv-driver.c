<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    bttv - Bt848 frame grabber driver

    Copyright (C) 1996,97,98 Ralph  Metzler <rjkm@thp.uni-koeln.de>
			   & Marcus Metzler <mocm@thp.uni-koeln.de>
    (c) 1999-2002 Gerd Knorr <kraxel@bytesex.org>

    some v4l2 code lines are taken from Justin's bttv2 driver which is
    (c) 2000 Justin Schoeman <justin@suntiger.ee.up.ac.za>

    V4L1 removal from:
    (c) 2005-2006 Nickolay V. Shmyrev <nshmyrev@yandex.ru>

    Fixes to be fully V4L2 compliant by
    (c) 2006 Mauro Carvalho Chehab <mchehab@kernel.org>

    Cropping and overscan support
    Copyright (C) 2005, 2006 Michael H. Schimek <mschimek@gmx.at>
    Sponsored by OPQ Systems AB

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kdev_t.h>
#समावेश "bttvp.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/i2c/tvaudपन.स>
#समावेश <media/drv-पूर्णांकf/msp3400.h>

#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

#समावेश <media/i2c/saa6588.h>

#घोषणा BTTV_VERSION "0.9.19"

अचिन्हित पूर्णांक bttv_num;			/* number of Bt848s in use */
काष्ठा bttv *bttvs[BTTV_MAX];

अचिन्हित पूर्णांक bttv_debug;
अचिन्हित पूर्णांक bttv_verbose = 1;
अचिन्हित पूर्णांक bttv_gpio;

/* config variables */
#अगर_घोषित __BIG_ENDIAN
अटल अचिन्हित पूर्णांक bigendian=1;
#अन्यथा
अटल अचिन्हित पूर्णांक bigendian;
#पूर्ण_अगर
अटल अचिन्हित पूर्णांक radio[BTTV_MAX];
अटल अचिन्हित पूर्णांक irq_debug;
अटल अचिन्हित पूर्णांक gbuffers = 8;
अटल अचिन्हित पूर्णांक gbufsize = 0x208000;
अटल अचिन्हित पूर्णांक reset_crop = 1;

अटल पूर्णांक video_nr[BTTV_MAX] = अणु [0 ... (BTTV_MAX-1)] = -1 पूर्ण;
अटल पूर्णांक radio_nr[BTTV_MAX] = अणु [0 ... (BTTV_MAX-1)] = -1 पूर्ण;
अटल पूर्णांक vbi_nr[BTTV_MAX] = अणु [0 ... (BTTV_MAX-1)] = -1 पूर्ण;
अटल पूर्णांक debug_latency;
अटल पूर्णांक disable_ir;

अटल अचिन्हित पूर्णांक fdsr;

/* options */
अटल अचिन्हित पूर्णांक combfilter;
अटल अचिन्हित पूर्णांक lumafilter;
अटल अचिन्हित पूर्णांक स्वतःmute    = 1;
अटल अचिन्हित पूर्णांक chroma_agc;
अटल अचिन्हित पूर्णांक agc_crush   = 1;
अटल अचिन्हित पूर्णांक whitecrush_upper = 0xCF;
अटल अचिन्हित पूर्णांक whitecrush_lower = 0x7F;
अटल अचिन्हित पूर्णांक vcr_hack;
अटल अचिन्हित पूर्णांक irq_iचयन;
अटल अचिन्हित पूर्णांक uv_ratio    = 50;
अटल अचिन्हित पूर्णांक full_luma_range;
अटल अचिन्हित पूर्णांक coring;

/* API features (turn on/off stuff क्रम testing) */
अटल अचिन्हित पूर्णांक v4l2        = 1;

/* insmod args */
module_param(bttv_verbose,      पूर्णांक, 0644);
module_param(bttv_gpio,         पूर्णांक, 0644);
module_param(bttv_debug,        पूर्णांक, 0644);
module_param(irq_debug,         पूर्णांक, 0644);
module_param(debug_latency,     पूर्णांक, 0644);
module_param(disable_ir,        पूर्णांक, 0444);

module_param(fdsr,              पूर्णांक, 0444);
module_param(gbuffers,          पूर्णांक, 0444);
module_param(gbufsize,          पूर्णांक, 0444);
module_param(reset_crop,        पूर्णांक, 0444);

module_param(v4l2,              पूर्णांक, 0644);
module_param(bigendian,         पूर्णांक, 0644);
module_param(irq_iचयन,       पूर्णांक, 0644);
module_param(combfilter,        पूर्णांक, 0444);
module_param(lumafilter,        पूर्णांक, 0444);
module_param(स्वतःmute,          पूर्णांक, 0444);
module_param(chroma_agc,        पूर्णांक, 0444);
module_param(agc_crush,         पूर्णांक, 0444);
module_param(whitecrush_upper,  पूर्णांक, 0444);
module_param(whitecrush_lower,  पूर्णांक, 0444);
module_param(vcr_hack,          पूर्णांक, 0444);
module_param(uv_ratio,          पूर्णांक, 0444);
module_param(full_luma_range,   पूर्णांक, 0444);
module_param(coring,            पूर्णांक, 0444);

module_param_array(radio,       पूर्णांक, शून्य, 0444);
module_param_array(video_nr,    पूर्णांक, शून्य, 0444);
module_param_array(radio_nr,    पूर्णांक, शून्य, 0444);
module_param_array(vbi_nr,      पूर्णांक, शून्य, 0444);

MODULE_PARM_DESC(radio, "The TV card supports radio, default is 0 (no)");
MODULE_PARM_DESC(bigendian, "byte order of the framebuffer, default is native endian");
MODULE_PARM_DESC(bttv_verbose, "verbose startup messages, default is 1 (yes)");
MODULE_PARM_DESC(bttv_gpio, "log gpio changes, default is 0 (no)");
MODULE_PARM_DESC(bttv_debug, "debug messages, default is 0 (no)");
MODULE_PARM_DESC(irq_debug, "irq handler debug messages, default is 0 (no)");
MODULE_PARM_DESC(disable_ir, "disable infrared remote support");
MODULE_PARM_DESC(gbuffers, "number of capture buffers. range 2-32, default 8");
MODULE_PARM_DESC(gbufsize, "size of the capture buffers, default is 0x208000");
MODULE_PARM_DESC(reset_crop, "reset cropping parameters at open(), default is 1 (yes) for compatibility with older applications");
MODULE_PARM_DESC(स्वतःmute, "mute audio on bad/missing video signal, default is 1 (yes)");
MODULE_PARM_DESC(chroma_agc, "enables the AGC of chroma signal, default is 0 (no)");
MODULE_PARM_DESC(agc_crush, "enables the luminance AGC crush, default is 1 (yes)");
MODULE_PARM_DESC(whitecrush_upper, "sets the white crush upper value, default is 207");
MODULE_PARM_DESC(whitecrush_lower, "sets the white crush lower value, default is 127");
MODULE_PARM_DESC(vcr_hack, "enables the VCR hack (improves synch on poor VCR tapes), default is 0 (no)");
MODULE_PARM_DESC(irq_iचयन, "switch inputs in irq handler");
MODULE_PARM_DESC(uv_ratio, "ratio between u and v gains, default is 50");
MODULE_PARM_DESC(full_luma_range, "use the full luma range, default is 0 (no)");
MODULE_PARM_DESC(coring, "set the luma coring level, default is 0 (no)");
MODULE_PARM_DESC(video_nr, "video device numbers");
MODULE_PARM_DESC(vbi_nr, "vbi device numbers");
MODULE_PARM_DESC(radio_nr, "radio device numbers");

MODULE_DESCRIPTION("bttv - v4l/v4l2 driver module for bt848/878 based cards");
MODULE_AUTHOR("Ralph Metzler & Marcus Metzler & Gerd Knorr");
MODULE_LICENSE("GPL");
MODULE_VERSION(BTTV_VERSION);

#घोषणा V4L2_CID_PRIVATE_COMBFILTER		(V4L2_CID_USER_BTTV_BASE + 0)
#घोषणा V4L2_CID_PRIVATE_AUTOMUTE		(V4L2_CID_USER_BTTV_BASE + 1)
#घोषणा V4L2_CID_PRIVATE_LUMAFILTER		(V4L2_CID_USER_BTTV_BASE + 2)
#घोषणा V4L2_CID_PRIVATE_AGC_CRUSH		(V4L2_CID_USER_BTTV_BASE + 3)
#घोषणा V4L2_CID_PRIVATE_VCR_HACK		(V4L2_CID_USER_BTTV_BASE + 4)
#घोषणा V4L2_CID_PRIVATE_WHITECRUSH_LOWER	(V4L2_CID_USER_BTTV_BASE + 5)
#घोषणा V4L2_CID_PRIVATE_WHITECRUSH_UPPER	(V4L2_CID_USER_BTTV_BASE + 6)
#घोषणा V4L2_CID_PRIVATE_UV_RATIO		(V4L2_CID_USER_BTTV_BASE + 7)
#घोषणा V4L2_CID_PRIVATE_FULL_LUMA_RANGE	(V4L2_CID_USER_BTTV_BASE + 8)
#घोषणा V4L2_CID_PRIVATE_CORING			(V4L2_CID_USER_BTTV_BASE + 9)

/* ----------------------------------------------------------------------- */
/* sysfs                                                                   */

अटल sमाप_प्रकार show_card(काष्ठा device *cd,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा video_device *vfd = to_video_device(cd);
	काष्ठा bttv *btv = video_get_drvdata(vfd);
	वापस प्र_लिखो(buf, "%d\n", btv ? btv->c.type : UNSET);
पूर्ण
अटल DEVICE_ATTR(card, S_IRUGO, show_card, शून्य);

/* ----------------------------------------------------------------------- */
/* dvb स्वतः-load setup                                                     */
#अगर defined(CONFIG_MODULES) && defined(MODULE)
अटल व्योम request_module_async(काष्ठा work_काष्ठा *work)
अणु
	request_module("dvb-bt8xx");
पूर्ण

अटल व्योम request_modules(काष्ठा bttv *dev)
अणु
	INIT_WORK(&dev->request_module_wk, request_module_async);
	schedule_work(&dev->request_module_wk);
पूर्ण

अटल व्योम flush_request_modules(काष्ठा bttv *dev)
अणु
	flush_work(&dev->request_module_wk);
पूर्ण
#अन्यथा
#घोषणा request_modules(dev)
#घोषणा flush_request_modules(dev) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर /* CONFIG_MODULES */


/* ----------------------------------------------------------------------- */
/* अटल data                                                             */

/* special timing tables from conexant... */
अटल u8 SRAM_Table[][60] =
अणु
	/* PAL digital input over GPIO[7:0] */
	अणु
		45, // 45 bytes following
		0x36,0x11,0x01,0x00,0x90,0x02,0x05,0x10,0x04,0x16,
		0x12,0x05,0x11,0x00,0x04,0x12,0xC0,0x00,0x31,0x00,
		0x06,0x51,0x08,0x03,0x89,0x08,0x07,0xC0,0x44,0x00,
		0x81,0x01,0x01,0xA9,0x0D,0x02,0x02,0x50,0x03,0x37,
		0x37,0x00,0xAF,0x21,0x00
	पूर्ण,
	/* NTSC digital input over GPIO[7:0] */
	अणु
		51, // 51 bytes following
		0x0C,0xC0,0x00,0x00,0x90,0x02,0x03,0x10,0x03,0x06,
		0x10,0x04,0x12,0x12,0x05,0x02,0x13,0x04,0x19,0x00,
		0x04,0x39,0x00,0x06,0x59,0x08,0x03,0x83,0x08,0x07,
		0x03,0x50,0x00,0xC0,0x40,0x00,0x86,0x01,0x01,0xA6,
		0x0D,0x02,0x03,0x11,0x01,0x05,0x37,0x00,0xAC,0x21,
		0x00,
	पूर्ण,
	// TGB_NTSC392 // quartzsight
	// This table has been modअगरied to be used क्रम Fusion Rev D
	अणु
		0x2A, // size of table = 42
		0x06, 0x08, 0x04, 0x0a, 0xc0, 0x00, 0x18, 0x08, 0x03, 0x24,
		0x08, 0x07, 0x02, 0x90, 0x02, 0x08, 0x10, 0x04, 0x0c, 0x10,
		0x05, 0x2c, 0x11, 0x04, 0x55, 0x48, 0x00, 0x05, 0x50, 0x00,
		0xbf, 0x0c, 0x02, 0x2f, 0x3d, 0x00, 0x2f, 0x3f, 0x00, 0xc3,
		0x20, 0x00
	पूर्ण
पूर्ण;

/* minhdelayx1	first video pixel we can capture on a line and
   hdelayx1	start of active video, both relative to rising edge of
		/HRESET pulse (0H) in 1 / fCLKx1.
   swidth	width of active video and
   totalwidth	total line width, both in 1 / fCLKx1.
   sqwidth	total line width in square pixels.
   vdelay	start of active video in 2 * field lines relative to
		trailing edge of /VRESET pulse (VDELAY रेजिस्टर).
   sheight	height of active video in 2 * field lines.
   extraheight	Added to sheight क्रम cropcap.bounds.height only
   videostart0	ITU-R frame line number of the line corresponding
		to vdelay in the first field. */
#घोषणा CROPCAP(minhdelayx1, hdelayx1, swidth, totalwidth, sqwidth,	 \
		vdelay, sheight, extraheight, videostart0)		 \
	.cropcap.bounds.left = minhdelayx1,				 \
	/* * 2 because vertically we count field lines बार two, */	 \
	/* e.g. 23 * 2 to 23 * 2 + 576 in PAL-BGHI defrect. */		 \
	.cropcap.bounds.top = (videostart0) * 2 - (vdelay) + MIN_VDELAY, \
	/* 4 is a safety margin at the end of the line. */		 \
	.cropcap.bounds.width = (totalwidth) - (minhdelayx1) - 4,	 \
	.cropcap.bounds.height = (sheight) + (extraheight) + (vdelay) -	 \
				 MIN_VDELAY,				 \
	.cropcap.defrect.left = hdelayx1,				 \
	.cropcap.defrect.top = (videostart0) * 2,			 \
	.cropcap.defrect.width = swidth,				 \
	.cropcap.defrect.height = sheight,				 \
	.cropcap.pixelaspect.numerator = totalwidth,			 \
	.cropcap.pixelaspect.denominator = sqwidth,

स्थिर काष्ठा bttv_tvnorm bttv_tvnorms[] = अणु
	/* PAL-BDGHI */
	/* max. active video is actually 922, but 924 is भागisible by 4 and 3! */
	/* actually, max active PAL with HSCALE=0 is 948, NTSC is 768 - nil */
	अणु
		.v4l2_id        = V4L2_STD_PAL,
		.name           = "PAL",
		.Fsc            = 35468950,
		.swidth         = 924,
		.sheight        = 576,
		.totalwidth     = 1135,
		.adelay         = 0x7f,
		.bdelay         = 0x72,
		.अगरorm          = (BT848_IFORM_PAL_BDGHI|BT848_IFORM_XT1),
		.scaledtwidth   = 1135,
		.hdelayx1       = 186,
		.hactivex1      = 924,
		.vdelay         = 0x20,
		.vbipack        = 255, /* min (2048 / 4, 0x1ff) & 0xff */
		.sram           = 0,
		/* ITU-R frame line number of the first VBI line
		   we can capture, of the first and second field.
		   The last line is determined by cropcap.bounds. */
		.vbistart       = अणु 7, 320 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 186,
			/* Should be (768 * 1135 + 944 / 2) / 944.
			   cropcap.defrect is used क्रम image width
			   checks, so we keep the old value 924. */
			/* swidth */ 924,
			/* totalwidth */ 1135,
			/* sqwidth */ 944,
			/* vdelay */ 0x20,
			/* sheight */ 576,
			/* bt878 (and bt848?) can capture another
			   line below active video. */
			/* extraheight */ 2,
			/* videostart0 */ 23)
	पूर्ण,अणु
		.v4l2_id        = V4L2_STD_NTSC_M | V4L2_STD_NTSC_M_KR,
		.name           = "NTSC",
		.Fsc            = 28636363,
		.swidth         = 768,
		.sheight        = 480,
		.totalwidth     = 910,
		.adelay         = 0x68,
		.bdelay         = 0x5d,
		.अगरorm          = (BT848_IFORM_NTSC|BT848_IFORM_XT0),
		.scaledtwidth   = 910,
		.hdelayx1       = 128,
		.hactivex1      = 910,
		.vdelay         = 0x1a,
		.vbipack        = 144, /* min (1600 / 4, 0x1ff) & 0xff */
		.sram           = 1,
		.vbistart	= अणु 10, 273 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 128,
			/* Should be (640 * 910 + 780 / 2) / 780? */
			/* swidth */ 768,
			/* totalwidth */ 910,
			/* sqwidth */ 780,
			/* vdelay */ 0x1a,
			/* sheight */ 480,
			/* extraheight */ 0,
			/* videostart0 */ 23)
	पूर्ण,अणु
		.v4l2_id        = V4L2_STD_SECAM,
		.name           = "SECAM",
		.Fsc            = 35468950,
		.swidth         = 924,
		.sheight        = 576,
		.totalwidth     = 1135,
		.adelay         = 0x7f,
		.bdelay         = 0xb0,
		.अगरorm          = (BT848_IFORM_SECAM|BT848_IFORM_XT1),
		.scaledtwidth   = 1135,
		.hdelayx1       = 186,
		.hactivex1      = 922,
		.vdelay         = 0x20,
		.vbipack        = 255,
		.sram           = 0, /* like PAL, correct? */
		.vbistart	= अणु 7, 320 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 186,
			/* swidth */ 924,
			/* totalwidth */ 1135,
			/* sqwidth */ 944,
			/* vdelay */ 0x20,
			/* sheight */ 576,
			/* extraheight */ 0,
			/* videostart0 */ 23)
	पूर्ण,अणु
		.v4l2_id        = V4L2_STD_PAL_Nc,
		.name           = "PAL-Nc",
		.Fsc            = 28636363,
		.swidth         = 640,
		.sheight        = 576,
		.totalwidth     = 910,
		.adelay         = 0x68,
		.bdelay         = 0x5d,
		.अगरorm          = (BT848_IFORM_PAL_NC|BT848_IFORM_XT0),
		.scaledtwidth   = 780,
		.hdelayx1       = 130,
		.hactivex1      = 734,
		.vdelay         = 0x1a,
		.vbipack        = 144,
		.sram           = -1,
		.vbistart	= अणु 7, 320 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 130,
			/* swidth */ (640 * 910 + 780 / 2) / 780,
			/* totalwidth */ 910,
			/* sqwidth */ 780,
			/* vdelay */ 0x1a,
			/* sheight */ 576,
			/* extraheight */ 0,
			/* videostart0 */ 23)
	पूर्ण,अणु
		.v4l2_id        = V4L2_STD_PAL_M,
		.name           = "PAL-M",
		.Fsc            = 28636363,
		.swidth         = 640,
		.sheight        = 480,
		.totalwidth     = 910,
		.adelay         = 0x68,
		.bdelay         = 0x5d,
		.अगरorm          = (BT848_IFORM_PAL_M|BT848_IFORM_XT0),
		.scaledtwidth   = 780,
		.hdelayx1       = 135,
		.hactivex1      = 754,
		.vdelay         = 0x1a,
		.vbipack        = 144,
		.sram           = -1,
		.vbistart	= अणु 10, 273 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 135,
			/* swidth */ (640 * 910 + 780 / 2) / 780,
			/* totalwidth */ 910,
			/* sqwidth */ 780,
			/* vdelay */ 0x1a,
			/* sheight */ 480,
			/* extraheight */ 0,
			/* videostart0 */ 23)
	पूर्ण,अणु
		.v4l2_id        = V4L2_STD_PAL_N,
		.name           = "PAL-N",
		.Fsc            = 35468950,
		.swidth         = 768,
		.sheight        = 576,
		.totalwidth     = 1135,
		.adelay         = 0x7f,
		.bdelay         = 0x72,
		.अगरorm          = (BT848_IFORM_PAL_N|BT848_IFORM_XT1),
		.scaledtwidth   = 944,
		.hdelayx1       = 186,
		.hactivex1      = 922,
		.vdelay         = 0x20,
		.vbipack        = 144,
		.sram           = -1,
		.vbistart       = अणु 7, 320 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 186,
			/* swidth */ (768 * 1135 + 944 / 2) / 944,
			/* totalwidth */ 1135,
			/* sqwidth */ 944,
			/* vdelay */ 0x20,
			/* sheight */ 576,
			/* extraheight */ 0,
			/* videostart0 */ 23)
	पूर्ण,अणु
		.v4l2_id        = V4L2_STD_NTSC_M_JP,
		.name           = "NTSC-JP",
		.Fsc            = 28636363,
		.swidth         = 640,
		.sheight        = 480,
		.totalwidth     = 910,
		.adelay         = 0x68,
		.bdelay         = 0x5d,
		.अगरorm          = (BT848_IFORM_NTSC_J|BT848_IFORM_XT0),
		.scaledtwidth   = 780,
		.hdelayx1       = 135,
		.hactivex1      = 754,
		.vdelay         = 0x16,
		.vbipack        = 144,
		.sram           = -1,
		.vbistart       = अणु 10, 273 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 135,
			/* swidth */ (640 * 910 + 780 / 2) / 780,
			/* totalwidth */ 910,
			/* sqwidth */ 780,
			/* vdelay */ 0x16,
			/* sheight */ 480,
			/* extraheight */ 0,
			/* videostart0 */ 23)
	पूर्ण,अणु
		/* that one hopefully works with the strange timing
		 * which video recorders produce when playing a NTSC
		 * tape on a PAL TV ... */
		.v4l2_id        = V4L2_STD_PAL_60,
		.name           = "PAL-60",
		.Fsc            = 35468950,
		.swidth         = 924,
		.sheight        = 480,
		.totalwidth     = 1135,
		.adelay         = 0x7f,
		.bdelay         = 0x72,
		.अगरorm          = (BT848_IFORM_PAL_BDGHI|BT848_IFORM_XT1),
		.scaledtwidth   = 1135,
		.hdelayx1       = 186,
		.hactivex1      = 924,
		.vdelay         = 0x1a,
		.vbipack        = 255,
		.vtotal         = 524,
		.sram           = -1,
		.vbistart	= अणु 10, 273 पूर्ण,
		CROPCAP(/* minhdelayx1 */ 68,
			/* hdelayx1 */ 186,
			/* swidth */ 924,
			/* totalwidth */ 1135,
			/* sqwidth */ 944,
			/* vdelay */ 0x1a,
			/* sheight */ 480,
			/* extraheight */ 0,
			/* videostart0 */ 23)
	पूर्ण
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक BTTV_TVNORMS = ARRAY_SIZE(bttv_tvnorms);

/* ----------------------------------------------------------------------- */
/* bttv क्रमmat list
   packed pixel क्रमmats must come first */
अटल स्थिर काष्ठा bttv_क्रमmat क्रमmats[] = अणु
	अणु
		.fourcc   = V4L2_PIX_FMT_GREY,
		.btक्रमmat = BT848_COLOR_FMT_Y8,
		.depth    = 8,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_HI240,
		.btक्रमmat = BT848_COLOR_FMT_RGB8,
		.depth    = 8,
		.flags    = FORMAT_FLAGS_PACKED | FORMAT_FLAGS_DITHER,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB555,
		.btक्रमmat = BT848_COLOR_FMT_RGB15,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB555X,
		.btक्रमmat = BT848_COLOR_FMT_RGB15,
		.btswap   = 0x03, /* byteswap */
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB565,
		.btक्रमmat = BT848_COLOR_FMT_RGB16,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB565X,
		.btक्रमmat = BT848_COLOR_FMT_RGB16,
		.btswap   = 0x03, /* byteswap */
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_BGR24,
		.btक्रमmat = BT848_COLOR_FMT_RGB24,
		.depth    = 24,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_BGR32,
		.btक्रमmat = BT848_COLOR_FMT_RGB32,
		.depth    = 32,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_RGB32,
		.btक्रमmat = BT848_COLOR_FMT_RGB32,
		.btswap   = 0x0f, /* byte+word swap */
		.depth    = 32,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUYV,
		.btक्रमmat = BT848_COLOR_FMT_YUY2,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_UYVY,
		.btक्रमmat = BT848_COLOR_FMT_YUY2,
		.btswap   = 0x03, /* byteswap */
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PACKED,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUV422P,
		.btक्रमmat = BT848_COLOR_FMT_YCrCb422,
		.depth    = 16,
		.flags    = FORMAT_FLAGS_PLANAR,
		.hshअगरt   = 1,
		.vshअगरt   = 0,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUV420,
		.btक्रमmat = BT848_COLOR_FMT_YCrCb422,
		.depth    = 12,
		.flags    = FORMAT_FLAGS_PLANAR,
		.hshअगरt   = 1,
		.vshअगरt   = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YVU420,
		.btक्रमmat = BT848_COLOR_FMT_YCrCb422,
		.depth    = 12,
		.flags    = FORMAT_FLAGS_PLANAR | FORMAT_FLAGS_CrCb,
		.hshअगरt   = 1,
		.vshअगरt   = 1,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUV411P,
		.btक्रमmat = BT848_COLOR_FMT_YCrCb411,
		.depth    = 12,
		.flags    = FORMAT_FLAGS_PLANAR,
		.hshअगरt   = 2,
		.vshअगरt   = 0,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YUV410,
		.btक्रमmat = BT848_COLOR_FMT_YCrCb411,
		.depth    = 9,
		.flags    = FORMAT_FLAGS_PLANAR,
		.hshअगरt   = 2,
		.vshअगरt   = 2,
	पूर्ण,अणु
		.fourcc   = V4L2_PIX_FMT_YVU410,
		.btक्रमmat = BT848_COLOR_FMT_YCrCb411,
		.depth    = 9,
		.flags    = FORMAT_FLAGS_PLANAR | FORMAT_FLAGS_CrCb,
		.hshअगरt   = 2,
		.vshअगरt   = 2,
	पूर्ण,अणु
		.fourcc   = -1,
		.btक्रमmat = BT848_COLOR_FMT_RAW,
		.depth    = 8,
		.flags    = FORMAT_FLAGS_RAW,
	पूर्ण
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक FORMATS = ARRAY_SIZE(क्रमmats);

/* ----------------------------------------------------------------------- */
/* resource management                                                     */

/*
   RESOURCE_    allocated by                मुक्तd by

   VIDEO_READ   bttv_पढ़ो 1)                bttv_पढ़ो 2)

   VIDEO_STREAM VIDIOC_STREAMON             VIDIOC_STREAMOFF
		 VIDIOC_QBUF 1)              bttv_release
		 VIDIOCMCAPTURE 1)

   OVERLAY	 VIDIOCCAPTURE on            VIDIOCCAPTURE off
		 VIDIOC_OVERLAY on           VIDIOC_OVERLAY off
		 3)                          bttv_release

   VBI		 VIDIOC_STREAMON             VIDIOC_STREAMOFF
		 VIDIOC_QBUF 1)              bttv_release
		 bttv_पढ़ो, bttv_poll 1) 4)

   1) The resource must be allocated when we enter buffer prepare functions
      and reमुख्य allocated जबतक buffers are in the DMA queue.
   2) This is a single frame पढ़ो.
   3) VIDIOC_S_FBUF and VIDIOC_S_FMT (OVERLAY) still work when
      RESOURCE_OVERLAY is allocated.
   4) This is a continuous पढ़ो, implies VIDIOC_STREAMON.

   Note this driver permits video input and standard changes regardless अगर
   resources are allocated.
*/

#घोषणा VBI_RESOURCES (RESOURCE_VBI)
#घोषणा VIDEO_RESOURCES (RESOURCE_VIDEO_READ | \
			 RESOURCE_VIDEO_STREAM | \
			 RESOURCE_OVERLAY)

अटल
पूर्णांक check_alloc_btres_lock(काष्ठा bttv *btv, काष्ठा bttv_fh *fh, पूर्णांक bit)
अणु
	पूर्णांक xbits; /* mutual exclusive resources */

	अगर (fh->resources & bit)
		/* have it alपढ़ोy allocated */
		वापस 1;

	xbits = bit;
	अगर (bit & (RESOURCE_VIDEO_READ | RESOURCE_VIDEO_STREAM))
		xbits |= RESOURCE_VIDEO_READ | RESOURCE_VIDEO_STREAM;

	/* is it मुक्त? */
	अगर (btv->resources & xbits) अणु
		/* no, someone अन्यथा uses it */
		जाओ fail;
	पूर्ण

	अगर ((bit & VIDEO_RESOURCES)
	    && 0 == (btv->resources & VIDEO_RESOURCES)) अणु
		/* Do crop - use current, करोn't - use शेष parameters. */
		__s32 top = btv->crop[!!fh->करो_crop].rect.top;

		अगर (btv->vbi_end > top)
			जाओ fail;

		/* We cannot capture the same line as video and VBI data.
		   Claim scan lines crop[].rect.top to bottom. */
		btv->crop_start = top;
	पूर्ण अन्यथा अगर (bit & VBI_RESOURCES) अणु
		__s32 end = fh->vbi_fmt.end;

		अगर (end > btv->crop_start)
			जाओ fail;

		/* Claim scan lines above fh->vbi_fmt.end. */
		btv->vbi_end = end;
	पूर्ण

	/* it's मुक्त, grab it */
	fh->resources  |= bit;
	btv->resources |= bit;
	वापस 1;

 fail:
	वापस 0;
पूर्ण

अटल
पूर्णांक check_btres(काष्ठा bttv_fh *fh, पूर्णांक bit)
अणु
	वापस (fh->resources & bit);
पूर्ण

अटल
पूर्णांक locked_btres(काष्ठा bttv *btv, पूर्णांक bit)
अणु
	वापस (btv->resources & bit);
पूर्ण

/* Call with btv->lock करोwn. */
अटल व्योम
disclaim_vbi_lines(काष्ठा bttv *btv)
अणु
	btv->vbi_end = 0;
पूर्ण

/* Call with btv->lock करोwn. */
अटल व्योम
disclaim_video_lines(काष्ठा bttv *btv)
अणु
	स्थिर काष्ठा bttv_tvnorm *tvnorm;
	u8 crop;

	tvnorm = &bttv_tvnorms[btv->tvnorm];
	btv->crop_start = tvnorm->cropcap.bounds.top
		+ tvnorm->cropcap.bounds.height;

	/* VBI capturing ends at VDELAY, start of video capturing, no
	   matter how many lines the VBI RISC program expects. When video
	   capturing is off, it shall no दीर्घer "preempt" VBI capturing,
	   so we set VDELAY to maximum. */
	crop = btपढ़ो(BT848_E_CROP) | 0xc0;
	btग_लिखो(crop, BT848_E_CROP);
	btग_लिखो(0xfe, BT848_E_VDELAY_LO);
	btग_लिखो(crop, BT848_O_CROP);
	btग_लिखो(0xfe, BT848_O_VDELAY_LO);
पूर्ण

अटल
व्योम मुक्त_btres_lock(काष्ठा bttv *btv, काष्ठा bttv_fh *fh, पूर्णांक bits)
अणु
	अगर ((fh->resources & bits) != bits) अणु
		/* trying to मुक्त resources not allocated by us ... */
		pr_err("BUG! (btres)\n");
	पूर्ण
	fh->resources  &= ~bits;
	btv->resources &= ~bits;

	bits = btv->resources;

	अगर (0 == (bits & VIDEO_RESOURCES))
		disclaim_video_lines(btv);

	अगर (0 == (bits & VBI_RESOURCES))
		disclaim_vbi_lines(btv);
पूर्ण

/* ----------------------------------------------------------------------- */
/* If Bt848a or Bt849, use PLL क्रम PAL/SECAM and crystal क्रम NTSC          */

/* Frequency = (F_input / PLL_X) * PLL_I.PLL_F/PLL_C
   PLL_X = Reference pre-भागider (0=1, 1=2)
   PLL_C = Post भागider (0=6, 1=4)
   PLL_I = Integer input
   PLL_F = Fractional input

   F_input = 28.636363 MHz:
   PAL (CLKx2 = 35.46895 MHz): PLL_X = 1, PLL_I = 0x0E, PLL_F = 0xDCF9, PLL_C = 0
*/

अटल व्योम set_pll_freq(काष्ठा bttv *btv, अचिन्हित पूर्णांक fin, अचिन्हित पूर्णांक fout)
अणु
	अचिन्हित अक्षर fl, fh, fi;

	/* prevent overflows */
	fin/=4;
	fout/=4;

	fout*=12;
	fi=fout/fin;

	fout=(fout%fin)*256;
	fh=fout/fin;

	fout=(fout%fin)*256;
	fl=fout/fin;

	btग_लिखो(fl, BT848_PLL_F_LO);
	btग_लिखो(fh, BT848_PLL_F_HI);
	btग_लिखो(fi|BT848_PLL_X, BT848_PLL_XCI);
पूर्ण

अटल व्योम set_pll(काष्ठा bttv *btv)
अणु
	पूर्णांक i;

	अगर (!btv->pll.pll_crystal)
		वापस;

	अगर (btv->pll.pll_ofreq == btv->pll.pll_current) अणु
		dprपूर्णांकk("%d: PLL: no change required\n", btv->c.nr);
		वापस;
	पूर्ण

	अगर (btv->pll.pll_अगरreq == btv->pll.pll_ofreq) अणु
		/* no PLL needed */
		अगर (btv->pll.pll_current == 0)
			वापस;
		अगर (bttv_verbose)
			pr_info("%d: PLL can sleep, using XTAL (%d)\n",
				btv->c.nr, btv->pll.pll_अगरreq);
		btग_लिखो(0x00,BT848_TGCTRL);
		btग_लिखो(0x00,BT848_PLL_XCI);
		btv->pll.pll_current = 0;
		वापस;
	पूर्ण

	अगर (bttv_verbose)
		pr_info("%d: Setting PLL: %d => %d (needs up to 100ms)\n",
			btv->c.nr,
			btv->pll.pll_अगरreq, btv->pll.pll_ofreq);
	set_pll_freq(btv, btv->pll.pll_अगरreq, btv->pll.pll_ofreq);

	क्रम (i=0; i<10; i++) अणु
		/*  Let other people run जबतक the PLL stabilizes */
		msleep(10);

		अगर (btपढ़ो(BT848_DSTATUS) & BT848_DSTATUS_PLOCK) अणु
			btग_लिखो(0,BT848_DSTATUS);
		पूर्ण अन्यथा अणु
			btग_लिखो(0x08,BT848_TGCTRL);
			btv->pll.pll_current = btv->pll.pll_ofreq;
			अगर (bttv_verbose)
				pr_info("PLL set ok\n");
			वापस;
		पूर्ण
	पूर्ण
	btv->pll.pll_current = -1;
	अगर (bttv_verbose)
		pr_info("Setting PLL failed\n");
	वापस;
पूर्ण

/* used to चयन between the bt848's analog/digital video capture modes */
अटल व्योम bt848A_set_timing(काष्ठा bttv *btv)
अणु
	पूर्णांक i, len;
	पूर्णांक table_idx = bttv_tvnorms[btv->tvnorm].sram;
	पूर्णांक fsc       = bttv_tvnorms[btv->tvnorm].Fsc;

	अगर (btv->input == btv->dig) अणु
		dprपूर्णांकk("%d: load digital timing table (table_idx=%d)\n",
			btv->c.nr,table_idx);

		/* timing change...reset timing generator address */
		btग_लिखो(0x00, BT848_TGCTRL);
		btग_लिखो(0x02, BT848_TGCTRL);
		btग_लिखो(0x00, BT848_TGCTRL);

		len=SRAM_Table[table_idx][0];
		क्रम(i = 1; i <= len; i++)
			btग_लिखो(SRAM_Table[table_idx][i],BT848_TGLB);
		btv->pll.pll_ofreq = 27000000;

		set_pll(btv);
		btग_लिखो(0x11, BT848_TGCTRL);
		btग_लिखो(0x41, BT848_DVSIF);
	पूर्ण अन्यथा अणु
		btv->pll.pll_ofreq = fsc;
		set_pll(btv);
		btग_लिखो(0x0, BT848_DVSIF);
	पूर्ण
पूर्ण

/* ----------------------------------------------------------------------- */

अटल व्योम bt848_bright(काष्ठा bttv *btv, पूर्णांक bright)
अणु
	पूर्णांक value;

	// prपूर्णांकk("set bright: %d\n", bright); // DEBUG
	btv->bright = bright;

	/* We want -128 to 127 we get 0-65535 */
	value = (bright >> 8) - 128;
	btग_लिखो(value & 0xff, BT848_BRIGHT);
पूर्ण

अटल व्योम bt848_hue(काष्ठा bttv *btv, पूर्णांक hue)
अणु
	पूर्णांक value;

	btv->hue = hue;

	/* -128 to 127 */
	value = (hue >> 8) - 128;
	btग_लिखो(value & 0xff, BT848_HUE);
पूर्ण

अटल व्योम bt848_contrast(काष्ठा bttv *btv, पूर्णांक cont)
अणु
	पूर्णांक value,hibit;

	btv->contrast = cont;

	/* 0-511 */
	value = (cont  >> 7);
	hibit = (value >> 6) & 4;
	btग_लिखो(value & 0xff, BT848_CONTRAST_LO);
	btaor(hibit, ~4, BT848_E_CONTROL);
	btaor(hibit, ~4, BT848_O_CONTROL);
पूर्ण

अटल व्योम bt848_sat(काष्ठा bttv *btv, पूर्णांक color)
अणु
	पूर्णांक val_u,val_v,hibits;

	btv->saturation = color;

	/* 0-511 क्रम the color */
	val_u   = ((color * btv->opt_uv_ratio) / 50) >> 7;
	val_v   = (((color * (100 - btv->opt_uv_ratio) / 50) >>7)*180L)/254;
	hibits  = (val_u >> 7) & 2;
	hibits |= (val_v >> 8) & 1;
	btग_लिखो(val_u & 0xff, BT848_SAT_U_LO);
	btग_लिखो(val_v & 0xff, BT848_SAT_V_LO);
	btaor(hibits, ~3, BT848_E_CONTROL);
	btaor(hibits, ~3, BT848_O_CONTROL);
पूर्ण

/* ----------------------------------------------------------------------- */

अटल पूर्णांक
video_mux(काष्ठा bttv *btv, अचिन्हित पूर्णांक input)
अणु
	पूर्णांक mux,mask2;

	अगर (input >= bttv_tvcards[btv->c.type].video_inमाला_दो)
		वापस -EINVAL;

	/* needed by RemoteVideo MX */
	mask2 = bttv_tvcards[btv->c.type].gpiomask2;
	अगर (mask2)
		gpio_inout(mask2,mask2);

	अगर (input == btv->svhs)  अणु
		btor(BT848_CONTROL_COMP, BT848_E_CONTROL);
		btor(BT848_CONTROL_COMP, BT848_O_CONTROL);
	पूर्ण अन्यथा अणु
		btand(~BT848_CONTROL_COMP, BT848_E_CONTROL);
		btand(~BT848_CONTROL_COMP, BT848_O_CONTROL);
	पूर्ण
	mux = bttv_muxsel(btv, input);
	btaor(mux<<5, ~(3<<5), BT848_IFORM);
	dprपूर्णांकk("%d: video mux: input=%d mux=%d\n", btv->c.nr, input, mux);

	/* card specअगरic hook */
	अगर(bttv_tvcards[btv->c.type].muxsel_hook)
		bttv_tvcards[btv->c.type].muxsel_hook (btv, input);
	वापस 0;
पूर्ण

अटल अक्षर *audio_modes[] = अणु
	"audio: tuner", "audio: radio", "audio: extern",
	"audio: intern", "audio: mute"
पूर्ण;

अटल व्योम
audio_mux_gpio(काष्ठा bttv *btv, पूर्णांक input, पूर्णांक mute)
अणु
	पूर्णांक gpio_val, संकेत, mute_gpio;

	gpio_inout(bttv_tvcards[btv->c.type].gpiomask,
		   bttv_tvcards[btv->c.type].gpiomask);
	संकेत = btपढ़ो(BT848_DSTATUS) & BT848_DSTATUS_HLOC;

	/* स्वतःmute */
	mute_gpio = mute || (btv->opt_स्वतःmute && (!संकेत || !btv->users)
				&& !btv->has_radio_tuner);

	अगर (mute_gpio)
		gpio_val = bttv_tvcards[btv->c.type].gpiomute;
	अन्यथा
		gpio_val = bttv_tvcards[btv->c.type].gpiomux[input];

	चयन (btv->c.type) अणु
	हाल BTTV_BOARD_VOODOOTV_FM:
	हाल BTTV_BOARD_VOODOOTV_200:
		gpio_val = bttv_tda9880_setnorm(btv, gpio_val);
		अवरोध;

	शेष:
		gpio_bits(bttv_tvcards[btv->c.type].gpiomask, gpio_val);
	पूर्ण

	अगर (bttv_gpio)
		bttv_gpio_tracking(btv, audio_modes[mute_gpio ? 4 : input]);
पूर्ण

अटल पूर्णांक
audio_mute(काष्ठा bttv *btv, पूर्णांक mute)
अणु
	काष्ठा v4l2_ctrl *ctrl;

	audio_mux_gpio(btv, btv->audio_input, mute);

	अगर (btv->sd_msp34xx) अणु
		ctrl = v4l2_ctrl_find(btv->sd_msp34xx->ctrl_handler, V4L2_CID_AUDIO_MUTE);
		अगर (ctrl)
			v4l2_ctrl_s_ctrl(ctrl, mute);
	पूर्ण
	अगर (btv->sd_tvaudio) अणु
		ctrl = v4l2_ctrl_find(btv->sd_tvaudio->ctrl_handler, V4L2_CID_AUDIO_MUTE);
		अगर (ctrl)
			v4l2_ctrl_s_ctrl(ctrl, mute);
	पूर्ण
	अगर (btv->sd_tda7432) अणु
		ctrl = v4l2_ctrl_find(btv->sd_tda7432->ctrl_handler, V4L2_CID_AUDIO_MUTE);
		अगर (ctrl)
			v4l2_ctrl_s_ctrl(ctrl, mute);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
audio_input(काष्ठा bttv *btv, पूर्णांक input)
अणु
	audio_mux_gpio(btv, input, btv->mute);

	अगर (btv->sd_msp34xx) अणु
		u32 in;

		/* Note: the inमाला_दो tuner/radio/बाह्य/पूर्णांकern are translated
		   to msp routings. This assumes common behavior क्रम all msp3400
		   based TV cards. When this assumption fails, then the
		   specअगरic MSP routing must be added to the card table.
		   For now this is sufficient. */
		चयन (input) अणु
		हाल TVAUDIO_INPUT_RADIO:
			/* Some boards need the msp करो to the radio demod */
			अगर (btv->radio_uses_msp_demodulator) अणु
				in = MSP_INPUT_DEFAULT;
				अवरोध;
			पूर्ण
			in = MSP_INPUT(MSP_IN_SCART2, MSP_IN_TUNER1,
				    MSP_DSP_IN_SCART, MSP_DSP_IN_SCART);
			अवरोध;
		हाल TVAUDIO_INPUT_EXTERN:
			in = MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER1,
				    MSP_DSP_IN_SCART, MSP_DSP_IN_SCART);
			अवरोध;
		हाल TVAUDIO_INPUT_INTERN:
			/* Yes, this is the same input as क्रम RADIO. I करोubt
			   अगर this is ever used. The only board with an INTERN
			   input is the BTTV_BOARD_AVERMEDIA98. I wonder how
			   that was tested. My guess is that the whole INTERN
			   input करोes not work. */
			in = MSP_INPUT(MSP_IN_SCART2, MSP_IN_TUNER1,
				    MSP_DSP_IN_SCART, MSP_DSP_IN_SCART);
			अवरोध;
		हाल TVAUDIO_INPUT_TUNER:
		शेष:
			/* This is the only card that uses TUNER2, and afaik,
			   is the only dअगरference between the VOODOOTV_FM
			   and VOODOOTV_200 */
			अगर (btv->c.type == BTTV_BOARD_VOODOOTV_200)
				in = MSP_INPUT(MSP_IN_SCART1, MSP_IN_TUNER2, \
					MSP_DSP_IN_TUNER, MSP_DSP_IN_TUNER);
			अन्यथा
				in = MSP_INPUT_DEFAULT;
			अवरोध;
		पूर्ण
		v4l2_subdev_call(btv->sd_msp34xx, audio, s_routing,
			       in, MSP_OUTPUT_DEFAULT, 0);
	पूर्ण
	अगर (btv->sd_tvaudio) अणु
		v4l2_subdev_call(btv->sd_tvaudio, audio, s_routing,
				 input, 0, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
bttv_crop_calc_limits(काष्ठा bttv_crop *c)
अणु
	/* Scale factor min. 1:1, max. 16:1. Min. image size
	   48 x 32. Scaled width must be a multiple of 4. */

	अगर (1) अणु
		/* For bug compatibility with VIDIOCGCAP and image
		   size checks in earlier driver versions. */
		c->min_scaled_width = 48;
		c->min_scaled_height = 32;
	पूर्ण अन्यथा अणु
		c->min_scaled_width =
			(max_t(अचिन्हित पूर्णांक, 48, c->rect.width >> 4) + 3) & ~3;
		c->min_scaled_height =
			max_t(अचिन्हित पूर्णांक, 32, c->rect.height >> 4);
	पूर्ण

	c->max_scaled_width  = c->rect.width & ~3;
	c->max_scaled_height = c->rect.height;
पूर्ण

अटल व्योम
bttv_crop_reset(काष्ठा bttv_crop *c, अचिन्हित पूर्णांक norm)
अणु
	c->rect = bttv_tvnorms[norm].cropcap.defrect;
	bttv_crop_calc_limits(c);
पूर्ण

/* Call with btv->lock करोwn. */
अटल पूर्णांक
set_tvnorm(काष्ठा bttv *btv, अचिन्हित पूर्णांक norm)
अणु
	स्थिर काष्ठा bttv_tvnorm *tvnorm;
	v4l2_std_id id;

	BUG_ON(norm >= BTTV_TVNORMS);
	BUG_ON(btv->tvnorm >= BTTV_TVNORMS);

	tvnorm = &bttv_tvnorms[norm];

	अगर (स_भेद(&bttv_tvnorms[btv->tvnorm].cropcap, &tvnorm->cropcap,
		    माप (tvnorm->cropcap))) अणु
		bttv_crop_reset(&btv->crop[0], norm);
		btv->crop[1] = btv->crop[0]; /* current = शेष */

		अगर (0 == (btv->resources & VIDEO_RESOURCES)) अणु
			btv->crop_start = tvnorm->cropcap.bounds.top
				+ tvnorm->cropcap.bounds.height;
		पूर्ण
	पूर्ण

	btv->tvnorm = norm;

	btग_लिखो(tvnorm->adelay, BT848_ADELAY);
	btग_लिखो(tvnorm->bdelay, BT848_BDELAY);
	btaor(tvnorm->अगरorm,~(BT848_IFORM_NORM|BT848_IFORM_XTBOTH),
	      BT848_IFORM);
	btग_लिखो(tvnorm->vbipack, BT848_VBI_PACK_SIZE);
	btग_लिखो(1, BT848_VBI_PACK_DEL);
	bt848A_set_timing(btv);

	चयन (btv->c.type) अणु
	हाल BTTV_BOARD_VOODOOTV_FM:
	हाल BTTV_BOARD_VOODOOTV_200:
		bttv_tda9880_setnorm(btv, gpio_पढ़ो());
		अवरोध;
	पूर्ण
	id = tvnorm->v4l2_id;
	bttv_call_all(btv, video, s_std, id);

	वापस 0;
पूर्ण

/* Call with btv->lock करोwn. */
अटल व्योम
set_input(काष्ठा bttv *btv, अचिन्हित पूर्णांक input, अचिन्हित पूर्णांक norm)
अणु
	अचिन्हित दीर्घ flags;

	btv->input = input;
	अगर (irq_iचयन) अणु
		spin_lock_irqsave(&btv->s_lock,flags);
		अगर (btv->curr.frame_irq) अणु
			/* active capture -> delayed input चयन */
			btv->new_input = input;
		पूर्ण अन्यथा अणु
			video_mux(btv,input);
		पूर्ण
		spin_unlock_irqrestore(&btv->s_lock,flags);
	पूर्ण अन्यथा अणु
		video_mux(btv,input);
	पूर्ण
	btv->audio_input = (btv->tuner_type != TUNER_ABSENT && input == 0) ?
				TVAUDIO_INPUT_TUNER : TVAUDIO_INPUT_EXTERN;
	audio_input(btv, btv->audio_input);
	set_tvnorm(btv, norm);
पूर्ण

अटल व्योम init_irqreg(काष्ठा bttv *btv)
अणु
	/* clear status */
	btग_लिखो(0xfffffUL, BT848_INT_STAT);

	अगर (bttv_tvcards[btv->c.type].no_video) अणु
		/* i2c only */
		btग_लिखो(BT848_INT_I2CDONE,
			BT848_INT_MASK);
	पूर्ण अन्यथा अणु
		/* full video */
		btग_लिखो((btv->triton1)  |
			(btv->gpioirq ? BT848_INT_GPINT : 0) |
			BT848_INT_SCERR |
			(fdsr ? BT848_INT_FDSR : 0) |
			BT848_INT_RISCI | BT848_INT_OCERR |
			BT848_INT_FMTCHG|BT848_INT_HLOCK|
			BT848_INT_I2CDONE,
			BT848_INT_MASK);
	पूर्ण
पूर्ण

अटल व्योम init_bt848(काष्ठा bttv *btv)
अणु
	अगर (bttv_tvcards[btv->c.type].no_video) अणु
		/* very basic init only */
		init_irqreg(btv);
		वापस;
	पूर्ण

	btग_लिखो(0x00, BT848_CAP_CTL);
	btग_लिखो(BT848_COLOR_CTL_GAMMA, BT848_COLOR_CTL);
	btग_लिखो(BT848_IFORM_XTAUTO | BT848_IFORM_AUTO, BT848_IFORM);

	/* set planar and packed mode trigger poपूर्णांकs and         */
	/* set rising edge of inverted GPINTR pin as irq trigger */
	btग_लिखो(BT848_GPIO_DMA_CTL_PKTP_32|
		BT848_GPIO_DMA_CTL_PLTP1_16|
		BT848_GPIO_DMA_CTL_PLTP23_16|
		BT848_GPIO_DMA_CTL_GPINTC|
		BT848_GPIO_DMA_CTL_GPINTI,
		BT848_GPIO_DMA_CTL);

	btग_लिखो(0x20, BT848_E_VSCALE_HI);
	btग_लिखो(0x20, BT848_O_VSCALE_HI);

	v4l2_ctrl_handler_setup(&btv->ctrl_handler);

	/* पूर्णांकerrupt */
	init_irqreg(btv);
पूर्ण

अटल व्योम bttv_reinit_bt848(काष्ठा bttv *btv)
अणु
	अचिन्हित दीर्घ flags;

	अगर (bttv_verbose)
		pr_info("%d: reset, reinitialize\n", btv->c.nr);
	spin_lock_irqsave(&btv->s_lock,flags);
	btv->errors=0;
	bttv_set_dma(btv,0);
	spin_unlock_irqrestore(&btv->s_lock,flags);

	init_bt848(btv);
	btv->pll.pll_current = -1;
	set_input(btv, btv->input, btv->tvnorm);
पूर्ण

अटल पूर्णांक bttv_s_ctrl(काष्ठा v4l2_ctrl *c)
अणु
	काष्ठा bttv *btv = container_of(c->handler, काष्ठा bttv, ctrl_handler);
	पूर्णांक val;

	चयन (c->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		bt848_bright(btv, c->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		bt848_hue(btv, c->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		bt848_contrast(btv, c->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		bt848_sat(btv, c->val);
		अवरोध;
	हाल V4L2_CID_COLOR_KILLER:
		अगर (c->val) अणु
			btor(BT848_SCLOOP_CKILL, BT848_E_SCLOOP);
			btor(BT848_SCLOOP_CKILL, BT848_O_SCLOOP);
		पूर्ण अन्यथा अणु
			btand(~BT848_SCLOOP_CKILL, BT848_E_SCLOOP);
			btand(~BT848_SCLOOP_CKILL, BT848_O_SCLOOP);
		पूर्ण
		अवरोध;
	हाल V4L2_CID_AUDIO_MUTE:
		audio_mute(btv, c->val);
		btv->mute = c->val;
		अवरोध;
	हाल V4L2_CID_AUDIO_VOLUME:
		btv->volume_gpio(btv, c->val);
		अवरोध;

	हाल V4L2_CID_CHROMA_AGC:
		val = c->val ? BT848_SCLOOP_CAGC : 0;
		btग_लिखो(val, BT848_E_SCLOOP);
		btग_लिखो(val, BT848_O_SCLOOP);
		अवरोध;
	हाल V4L2_CID_PRIVATE_COMBFILTER:
		btv->opt_combfilter = c->val;
		अवरोध;
	हाल V4L2_CID_PRIVATE_LUMAFILTER:
		अगर (c->val) अणु
			btand(~BT848_CONTROL_LDEC, BT848_E_CONTROL);
			btand(~BT848_CONTROL_LDEC, BT848_O_CONTROL);
		पूर्ण अन्यथा अणु
			btor(BT848_CONTROL_LDEC, BT848_E_CONTROL);
			btor(BT848_CONTROL_LDEC, BT848_O_CONTROL);
		पूर्ण
		अवरोध;
	हाल V4L2_CID_PRIVATE_AUTOMUTE:
		btv->opt_स्वतःmute = c->val;
		अवरोध;
	हाल V4L2_CID_PRIVATE_AGC_CRUSH:
		btग_लिखो(BT848_ADC_RESERVED |
				(c->val ? BT848_ADC_CRUSH : 0),
				BT848_ADC);
		अवरोध;
	हाल V4L2_CID_PRIVATE_VCR_HACK:
		btv->opt_vcr_hack = c->val;
		अवरोध;
	हाल V4L2_CID_PRIVATE_WHITECRUSH_UPPER:
		btग_लिखो(c->val, BT848_WC_UP);
		अवरोध;
	हाल V4L2_CID_PRIVATE_WHITECRUSH_LOWER:
		btग_लिखो(c->val, BT848_WC_DOWN);
		अवरोध;
	हाल V4L2_CID_PRIVATE_UV_RATIO:
		btv->opt_uv_ratio = c->val;
		bt848_sat(btv, btv->saturation);
		अवरोध;
	हाल V4L2_CID_PRIVATE_FULL_LUMA_RANGE:
		btaor((c->val << 7), ~BT848_OFORM_RANGE, BT848_OFORM);
		अवरोध;
	हाल V4L2_CID_PRIVATE_CORING:
		btaor((c->val << 5), ~BT848_OFORM_CORE32, BT848_OFORM);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops bttv_ctrl_ops = अणु
	.s_ctrl = bttv_s_ctrl,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_combfilter = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_COMBFILTER,
	.name = "Comb Filter",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_स्वतःmute = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_AUTOMUTE,
	.name = "Auto Mute",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_lumafilter = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_LUMAFILTER,
	.name = "Luma Decimation Filter",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_agc_crush = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_AGC_CRUSH,
	.name = "AGC Crush",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_vcr_hack = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_VCR_HACK,
	.name = "VCR Hack",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
	.def = 1,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_whitecrush_lower = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_WHITECRUSH_LOWER,
	.name = "Whitecrush Lower",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 255,
	.step = 1,
	.def = 0x7f,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_whitecrush_upper = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_WHITECRUSH_UPPER,
	.name = "Whitecrush Upper",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 255,
	.step = 1,
	.def = 0xcf,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_uv_ratio = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_UV_RATIO,
	.name = "UV Ratio",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 100,
	.step = 1,
	.def = 50,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_full_luma = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_FULL_LUMA_RANGE,
	.name = "Full Luma Range",
	.type = V4L2_CTRL_TYPE_BOOLEAN,
	.min = 0,
	.max = 1,
	.step = 1,
पूर्ण;

अटल काष्ठा v4l2_ctrl_config bttv_ctrl_coring = अणु
	.ops = &bttv_ctrl_ops,
	.id = V4L2_CID_PRIVATE_CORING,
	.name = "Coring",
	.type = V4L2_CTRL_TYPE_INTEGER,
	.min = 0,
	.max = 3,
	.step = 1,
पूर्ण;


/* ----------------------------------------------------------------------- */

व्योम bttv_gpio_tracking(काष्ठा bttv *btv, अक्षर *comment)
अणु
	अचिन्हित पूर्णांक outbits, data;
	outbits = btपढ़ो(BT848_GPIO_OUT_EN);
	data    = btपढ़ो(BT848_GPIO_DATA);
	pr_debug("%d: gpio: en=%08x, out=%08x in=%08x [%s]\n",
		 btv->c.nr, outbits, data & outbits, data & ~outbits, comment);
पूर्ण

अटल व्योम bttv_field_count(काष्ठा bttv *btv)
अणु
	पूर्णांक need_count = 0;

	अगर (btv->users)
		need_count++;

	अगर (need_count) अणु
		/* start field counter */
		btor(BT848_INT_VSYNC,BT848_INT_MASK);
	पूर्ण अन्यथा अणु
		/* stop field counter */
		btand(~BT848_INT_VSYNC,BT848_INT_MASK);
		btv->field_count = 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bttv_क्रमmat*
क्रमmat_by_fourcc(पूर्णांक fourcc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < FORMATS; i++) अणु
		अगर (-1 == क्रमmats[i].fourcc)
			जारी;
		अगर (क्रमmats[i].fourcc == fourcc)
			वापस क्रमmats+i;
	पूर्ण
	वापस शून्य;
पूर्ण

/* ----------------------------------------------------------------------- */
/* misc helpers                                                            */

अटल पूर्णांक
bttv_चयन_overlay(काष्ठा bttv *btv, काष्ठा bttv_fh *fh,
		    काष्ठा bttv_buffer *new)
अणु
	काष्ठा bttv_buffer *old;
	अचिन्हित दीर्घ flags;

	dprपूर्णांकk("switch_overlay: enter [new=%p]\n", new);
	अगर (new)
		new->vb.state = VIDEOBUF_DONE;
	spin_lock_irqsave(&btv->s_lock,flags);
	old = btv->screen;
	btv->screen = new;
	btv->loop_irq |= 1;
	bttv_set_dma(btv, 0x03);
	spin_unlock_irqrestore(&btv->s_lock,flags);
	अगर (शून्य != old) अणु
		dprपूर्णांकk("switch_overlay: old=%p state is %d\n",
			old, old->vb.state);
		bttv_dma_मुक्त(&fh->cap,btv, old);
		kमुक्त(old);
	पूर्ण
	अगर (शून्य == new)
		मुक्त_btres_lock(btv,fh,RESOURCE_OVERLAY);
	dprपूर्णांकk("switch_overlay: done\n");
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */
/* video4linux (1) पूर्णांकerface                                               */

अटल पूर्णांक bttv_prepare_buffer(काष्ठा videobuf_queue *q,काष्ठा bttv *btv,
			       काष्ठा bttv_buffer *buf,
			       स्थिर काष्ठा bttv_क्रमmat *fmt,
			       अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
			       क्रमागत v4l2_field field)
अणु
	काष्ठा bttv_fh *fh = q->priv_data;
	पूर्णांक reकरो_dma_risc = 0;
	काष्ठा bttv_crop c;
	पूर्णांक norm;
	पूर्णांक rc;

	/* check settings */
	अगर (शून्य == fmt)
		वापस -EINVAL;
	अगर (fmt->btक्रमmat == BT848_COLOR_FMT_RAW) अणु
		width  = RAW_BPL;
		height = RAW_LINES*2;
		अगर (width*height > buf->vb.bsize)
			वापस -EINVAL;
		buf->vb.size = buf->vb.bsize;

		/* Make sure tvnorm and vbi_end reमुख्य consistent
		   until we're करोne. */

		norm = btv->tvnorm;

		/* In this mode capturing always starts at defrect.top
		   (शेष VDELAY), ignoring cropping parameters. */
		अगर (btv->vbi_end > bttv_tvnorms[norm].cropcap.defrect.top) अणु
			वापस -EINVAL;
		पूर्ण

		c.rect = bttv_tvnorms[norm].cropcap.defrect;
	पूर्ण अन्यथा अणु
		norm = btv->tvnorm;
		c = btv->crop[!!fh->करो_crop];

		अगर (width < c.min_scaled_width ||
		    width > c.max_scaled_width ||
		    height < c.min_scaled_height)
			वापस -EINVAL;

		चयन (field) अणु
		हाल V4L2_FIELD_TOP:
		हाल V4L2_FIELD_BOTTOM:
		हाल V4L2_FIELD_ALTERNATE:
			/* btv->crop counts frame lines. Max. scale
			   factor is 16:1 क्रम frames, 8:1 क्रम fields. */
			अगर (height * 2 > c.max_scaled_height)
				वापस -EINVAL;
			अवरोध;

		शेष:
			अगर (height > c.max_scaled_height)
				वापस -EINVAL;
			अवरोध;
		पूर्ण

		buf->vb.size = (width * height * fmt->depth) >> 3;
		अगर (0 != buf->vb.baddr  &&  buf->vb.bsize < buf->vb.size)
			वापस -EINVAL;
	पूर्ण

	/* alloc + fill काष्ठा bttv_buffer (अगर changed) */
	अगर (buf->vb.width != width || buf->vb.height != height ||
	    buf->vb.field != field ||
	    buf->tvnorm != norm || buf->fmt != fmt ||
	    buf->crop.top != c.rect.top ||
	    buf->crop.left != c.rect.left ||
	    buf->crop.width != c.rect.width ||
	    buf->crop.height != c.rect.height) अणु
		buf->vb.width  = width;
		buf->vb.height = height;
		buf->vb.field  = field;
		buf->tvnorm    = norm;
		buf->fmt       = fmt;
		buf->crop      = c.rect;
		reकरो_dma_risc = 1;
	पूर्ण

	/* alloc risc memory */
	अगर (VIDEOBUF_NEEDS_INIT == buf->vb.state) अणु
		reकरो_dma_risc = 1;
		अगर (0 != (rc = videobuf_iolock(q,&buf->vb,&btv->fbuf)))
			जाओ fail;
	पूर्ण

	अगर (reकरो_dma_risc)
		अगर (0 != (rc = bttv_buffer_risc(btv,buf)))
			जाओ fail;

	buf->vb.state = VIDEOBUF_PREPARED;
	वापस 0;

 fail:
	bttv_dma_मुक्त(q,btv,buf);
	वापस rc;
पूर्ण

अटल पूर्णांक
buffer_setup(काष्ठा videobuf_queue *q, अचिन्हित पूर्णांक *count, अचिन्हित पूर्णांक *size)
अणु
	काष्ठा bttv_fh *fh = q->priv_data;

	*size = fh->fmt->depth*fh->width*fh->height >> 3;
	अगर (0 == *count)
		*count = gbuffers;
	अगर (*size * *count > gbuffers * gbufsize)
		*count = (gbuffers * gbufsize) / *size;
	वापस 0;
पूर्ण

अटल पूर्णांक
buffer_prepare(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb,
	       क्रमागत v4l2_field field)
अणु
	काष्ठा bttv_buffer *buf = container_of(vb,काष्ठा bttv_buffer,vb);
	काष्ठा bttv_fh *fh = q->priv_data;

	वापस bttv_prepare_buffer(q,fh->btv, buf, fh->fmt,
				   fh->width, fh->height, field);
पूर्ण

अटल व्योम
buffer_queue(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा bttv_buffer *buf = container_of(vb,काष्ठा bttv_buffer,vb);
	काष्ठा bttv_fh *fh = q->priv_data;
	काष्ठा bttv    *btv = fh->btv;

	buf->vb.state = VIDEOBUF_QUEUED;
	list_add_tail(&buf->vb.queue,&btv->capture);
	अगर (!btv->curr.frame_irq) अणु
		btv->loop_irq |= 1;
		bttv_set_dma(btv, 0x03);
	पूर्ण
पूर्ण

अटल व्योम buffer_release(काष्ठा videobuf_queue *q, काष्ठा videobuf_buffer *vb)
अणु
	काष्ठा bttv_buffer *buf = container_of(vb,काष्ठा bttv_buffer,vb);
	काष्ठा bttv_fh *fh = q->priv_data;

	bttv_dma_मुक्त(q,fh->btv,buf);
पूर्ण

अटल स्थिर काष्ठा videobuf_queue_ops bttv_video_qops = अणु
	.buf_setup    = buffer_setup,
	.buf_prepare  = buffer_prepare,
	.buf_queue    = buffer_queue,
	.buf_release  = buffer_release,
पूर्ण;

अटल व्योम radio_enable(काष्ठा bttv *btv)
अणु
	/* Switch to the radio tuner */
	अगर (!btv->has_radio_tuner) अणु
		btv->has_radio_tuner = 1;
		bttv_call_all(btv, tuner, s_radio);
		btv->audio_input = TVAUDIO_INPUT_RADIO;
		audio_input(btv, btv->audio_input);
	पूर्ण
पूर्ण

अटल पूर्णांक bttv_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id)
अणु
	काष्ठा bttv_fh *fh  = priv;
	काष्ठा bttv *btv = fh->btv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < BTTV_TVNORMS; i++)
		अगर (id & bttv_tvnorms[i].v4l2_id)
			अवरोध;
	अगर (i == BTTV_TVNORMS)
		वापस -EINVAL;
	btv->std = id;
	set_tvnorm(btv, i);
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id)
अणु
	काष्ठा bttv_fh *fh  = priv;
	काष्ठा bttv *btv = fh->btv;

	*id = btv->std;
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_querystd(काष्ठा file *file, व्योम *f, v4l2_std_id *id)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;

	अगर (btपढ़ो(BT848_DSTATUS) & BT848_DSTATUS_NUML)
		*id &= V4L2_STD_625_50;
	अन्यथा
		*id &= V4L2_STD_525_60;
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_क्रमागत_input(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_input *i)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (i->index >= bttv_tvcards[btv->c.type].video_inमाला_दो)
		वापस -EINVAL;

	i->type     = V4L2_INPUT_TYPE_CAMERA;
	i->audioset = 0;

	अगर (btv->tuner_type != TUNER_ABSENT && i->index == 0) अणु
		प्र_लिखो(i->name, "Television");
		i->type  = V4L2_INPUT_TYPE_TUNER;
		i->tuner = 0;
	पूर्ण अन्यथा अगर (i->index == btv->svhs) अणु
		प्र_लिखो(i->name, "S-Video");
	पूर्ण अन्यथा अणु
		प्र_लिखो(i->name, "Composite%d", i->index);
	पूर्ण

	अगर (i->index == btv->input) अणु
		__u32 dstatus = btपढ़ो(BT848_DSTATUS);
		अगर (0 == (dstatus & BT848_DSTATUS_PRES))
			i->status |= V4L2_IN_ST_NO_SIGNAL;
		अगर (0 == (dstatus & BT848_DSTATUS_HLOC))
			i->status |= V4L2_IN_ST_NO_H_LOCK;
	पूर्ण

	i->std = BTTV_NORMS;
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	*i = btv->input;

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा bttv_fh *fh  = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (i >= bttv_tvcards[btv->c.type].video_inमाला_दो)
		वापस -EINVAL;

	set_input(btv, i, btv->tvnorm);
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा bttv_fh *fh  = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (t->index)
		वापस -EINVAL;

	bttv_call_all(btv, tuner, s_tuner, t);

	अगर (btv->audio_mode_gpio) अणु
		काष्ठा v4l2_tuner copy = *t;

		btv->audio_mode_gpio(btv, &copy, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_frequency(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency *f)
अणु
	काष्ठा bttv_fh *fh  = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (f->tuner)
		वापस -EINVAL;

	अगर (f->type == V4L2_TUNER_RADIO)
		radio_enable(btv);
	f->frequency = f->type == V4L2_TUNER_RADIO ?
				btv->radio_freq : btv->tv_freq;

	वापस 0;
पूर्ण

अटल व्योम bttv_set_frequency(काष्ठा bttv *btv, स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा v4l2_frequency new_freq = *f;

	bttv_call_all(btv, tuner, s_frequency, f);
	/* s_frequency may clamp the frequency, so get the actual
	   frequency beक्रमe assigning radio/tv_freq. */
	bttv_call_all(btv, tuner, g_frequency, &new_freq);
	अगर (new_freq.type == V4L2_TUNER_RADIO) अणु
		radio_enable(btv);
		btv->radio_freq = new_freq.frequency;
		अगर (btv->has_tea575x) अणु
			btv->tea.freq = btv->radio_freq;
			snd_tea575x_set_freq(&btv->tea);
		पूर्ण
	पूर्ण अन्यथा अणु
		btv->tv_freq = new_freq.frequency;
	पूर्ण
पूर्ण

अटल पूर्णांक bttv_s_frequency(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_frequency *f)
अणु
	काष्ठा bttv_fh *fh  = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (f->tuner)
		वापस -EINVAL;

	bttv_set_frequency(btv, f);
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_log_status(काष्ठा file *file, व्योम *f)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा bttv_fh *fh  = f;
	काष्ठा bttv *btv = fh->btv;

	v4l2_ctrl_handler_log_status(vdev->ctrl_handler, btv->c.v4l2_dev.name);
	bttv_call_all(btv, core, log_status);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
अटल पूर्णांक bttv_g_रेजिस्टर(काष्ठा file *file, व्योम *f,
					काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;

	/* bt848 has a 12-bit रेजिस्टर space */
	reg->reg &= 0xfff;
	reg->val = btपढ़ो(reg->reg);
	reg->size = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_s_रेजिस्टर(काष्ठा file *file, व्योम *f,
					स्थिर काष्ठा v4l2_dbg_रेजिस्टर *reg)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;

	/* bt848 has a 12-bit रेजिस्टर space */
	btग_लिखो(reg->val, reg->reg & 0xfff);

	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Given cropping boundaries b and the scaled width and height of a
   single field or frame, which must not exceed hardware limits, this
   function adjusts the cropping parameters c. */
अटल व्योम
bttv_crop_adjust	(काष्ठा bttv_crop *             c,
			 स्थिर काष्ठा v4l2_rect *	b,
			 __s32                          width,
			 __s32                          height,
			 क्रमागत v4l2_field                field)
अणु
	__s32 frame_height = height << !V4L2_FIELD_HAS_BOTH(field);
	__s32 max_left;
	__s32 max_top;

	अगर (width < c->min_scaled_width) अणु
		/* Max. hor. scale factor 16:1. */
		c->rect.width = width * 16;
	पूर्ण अन्यथा अगर (width > c->max_scaled_width) अणु
		/* Min. hor. scale factor 1:1. */
		c->rect.width = width;

		max_left = b->left + b->width - width;
		max_left = min(max_left, (__s32) MAX_HDELAY);
		अगर (c->rect.left > max_left)
			c->rect.left = max_left;
	पूर्ण

	अगर (height < c->min_scaled_height) अणु
		/* Max. vert. scale factor 16:1, single fields 8:1. */
		c->rect.height = height * 16;
	पूर्ण अन्यथा अगर (frame_height > c->max_scaled_height) अणु
		/* Min. vert. scale factor 1:1.
		   Top and height count field lines बार two. */
		c->rect.height = (frame_height + 1) & ~1;

		max_top = b->top + b->height - c->rect.height;
		अगर (c->rect.top > max_top)
			c->rect.top = max_top;
	पूर्ण

	bttv_crop_calc_limits(c);
पूर्ण

/* Returns an error अगर scaling to a frame or single field with the given
   width and height is not possible with the current cropping parameters
   and width aligned according to width_mask. If adjust_size is TRUE the
   function may adjust the width and/or height instead, rounding width
   to (width + width_bias) & width_mask. If adjust_crop is TRUE it may
   also adjust the current cropping parameters to get बंदr to the
   desired image size. */
अटल पूर्णांक
limit_scaled_size_lock       (काष्ठा bttv_fh *               fh,
			 __s32 *                        width,
			 __s32 *                        height,
			 क्रमागत v4l2_field                field,
			 अचिन्हित पूर्णांक			width_mask,
			 अचिन्हित पूर्णांक			width_bias,
			 पूर्णांक                            adjust_size,
			 पूर्णांक                            adjust_crop)
अणु
	काष्ठा bttv *btv = fh->btv;
	स्थिर काष्ठा v4l2_rect *b;
	काष्ठा bttv_crop *c;
	__s32 min_width;
	__s32 min_height;
	__s32 max_width;
	__s32 max_height;
	पूर्णांक rc;

	BUG_ON((पूर्णांक) width_mask >= 0 ||
	       width_bias >= (अचिन्हित पूर्णांक) -width_mask);

	/* Make sure tvnorm, vbi_end and the current cropping parameters
	   reमुख्य consistent until we're करोne. */

	b = &bttv_tvnorms[btv->tvnorm].cropcap.bounds;

	/* Do crop - use current, करोn't - use शेष parameters. */
	c = &btv->crop[!!fh->करो_crop];

	अगर (fh->करो_crop
	    && adjust_size
	    && adjust_crop
	    && !locked_btres(btv, VIDEO_RESOURCES)) अणु
		min_width = 48;
		min_height = 32;

		/* We cannot scale up. When the scaled image is larger
		   than crop.rect we adjust the crop.rect as required
		   by the V4L2 spec, hence cropcap.bounds are our limit. */
		max_width = min_t(अचिन्हित पूर्णांक, b->width, MAX_HACTIVE);
		max_height = b->height;

		/* We cannot capture the same line as video and VBI data.
		   Note btv->vbi_end is really a minimum, see
		   bttv_vbi_try_fmt(). */
		अगर (btv->vbi_end > b->top) अणु
			max_height -= btv->vbi_end - b->top;
			rc = -EBUSY;
			अगर (min_height > max_height)
				जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = -EBUSY;
		अगर (btv->vbi_end > c->rect.top)
			जाओ fail;

		min_width  = c->min_scaled_width;
		min_height = c->min_scaled_height;
		max_width  = c->max_scaled_width;
		max_height = c->max_scaled_height;

		adjust_crop = 0;
	पूर्ण

	min_width = (min_width - width_mask - 1) & width_mask;
	max_width = max_width & width_mask;

	/* Max. scale factor is 16:1 क्रम frames, 8:1 क्रम fields. */
	/* Min. scale factor is 1:1. */
	max_height >>= !V4L2_FIELD_HAS_BOTH(field);

	अगर (adjust_size) अणु
		*width = clamp(*width, min_width, max_width);
		*height = clamp(*height, min_height, max_height);

		/* Round after clamping to aव्योम overflow. */
		*width = (*width + width_bias) & width_mask;

		अगर (adjust_crop) अणु
			bttv_crop_adjust(c, b, *width, *height, field);

			अगर (btv->vbi_end > c->rect.top) अणु
				/* Move the crop winकरोw out of the way. */
				c->rect.top = btv->vbi_end;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		अगर (*width  < min_width ||
		    *height < min_height ||
		    *width  > max_width ||
		    *height > max_height ||
		    0 != (*width & ~width_mask))
			जाओ fail;
	पूर्ण

	rc = 0; /* success */

 fail:

	वापस rc;
पूर्ण

/* Returns an error अगर the given overlay winकरोw dimensions are not
   possible with the current cropping parameters. If adjust_size is
   TRUE the function may adjust the winकरोw width and/or height
   instead, however it always rounds the horizontal position and
   width as btcx_align() करोes. If adjust_crop is TRUE the function
   may also adjust the current cropping parameters to get बंदr
   to the desired winकरोw size. */
अटल पूर्णांक
verअगरy_winकरोw_lock(काष्ठा bttv_fh *fh, काष्ठा v4l2_winकरोw *win,
			 पूर्णांक adjust_size, पूर्णांक adjust_crop)
अणु
	क्रमागत v4l2_field field;
	अचिन्हित पूर्णांक width_mask;

	अगर (win->w.width < 48)
		win->w.width = 48;
	अगर (win->w.height < 32)
		win->w.height = 32;
	अगर (win->clipcount > 2048)
		win->clipcount = 2048;

	win->chromakey = 0;
	win->global_alpha = 0;
	field = win->field;

	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_INTERLACED:
		अवरोध;
	शेष:
		field = V4L2_FIELD_ANY;
		अवरोध;
	पूर्ण
	अगर (V4L2_FIELD_ANY == field) अणु
		__s32 height2;

		height2 = fh->btv->crop[!!fh->करो_crop].rect.height >> 1;
		field = (win->w.height > height2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_TOP;
	पूर्ण
	win->field = field;

	अगर (शून्य == fh->ovfmt)
		वापस -EINVAL;
	/* 4-byte alignment. */
	width_mask = ~0;
	चयन (fh->ovfmt->depth) अणु
	हाल 8:
	हाल 24:
		width_mask = ~3;
		अवरोध;
	हाल 16:
		width_mask = ~1;
		अवरोध;
	हाल 32:
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	win->w.width -= win->w.left & ~width_mask;
	win->w.left = (win->w.left - width_mask - 1) & width_mask;

	वापस limit_scaled_size_lock(fh, &win->w.width, &win->w.height,
				      field, width_mask,
				      /* width_bias: round करोwn */ 0,
				      adjust_size, adjust_crop);
पूर्ण

अटल पूर्णांक setup_winकरोw_lock(काष्ठा bttv_fh *fh, काष्ठा bttv *btv,
			काष्ठा v4l2_winकरोw *win, पूर्णांक fixup)
अणु
	काष्ठा v4l2_clip *clips = शून्य;
	पूर्णांक n,size,retval = 0;

	अगर (शून्य == fh->ovfmt)
		वापस -EINVAL;
	अगर (!(fh->ovfmt->flags & FORMAT_FLAGS_PACKED))
		वापस -EINVAL;
	retval = verअगरy_winकरोw_lock(fh, win,
			       /* adjust_size */ fixup,
			       /* adjust_crop */ fixup);
	अगर (0 != retval)
		वापस retval;

	/* copy clips  --  luckily v4l1 + v4l2 are binary
	   compatible here ...*/
	n = win->clipcount;
	size = माप(*clips)*(n+4);
	clips = kदो_स्मृति(size,GFP_KERNEL);
	अगर (शून्य == clips)
		वापस -ENOMEM;
	अगर (n > 0)
		स_नकल(clips, win->clips, माप(काष्ठा v4l2_clip) * n);

	/* clip against screen */
	अगर (शून्य != btv->fbuf.base)
		n = btcx_screen_clips(btv->fbuf.fmt.width, btv->fbuf.fmt.height,
				      &win->w, clips, n);
	btcx_sort_clips(clips,n);

	/* 4-byte alignments */
	चयन (fh->ovfmt->depth) अणु
	हाल 8:
	हाल 24:
		btcx_align(&win->w, clips, n, 3);
		अवरोध;
	हाल 16:
		btcx_align(&win->w, clips, n, 1);
		अवरोध;
	हाल 32:
		/* no alignment fixups needed */
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	kमुक्त(fh->ov.clips);
	fh->ov.clips    = clips;
	fh->ov.nclips   = n;

	fh->ov.w        = win->w;
	fh->ov.field    = win->field;
	fh->ov.setup_ok = 1;

	btv->init.ov.w.width   = win->w.width;
	btv->init.ov.w.height  = win->w.height;
	btv->init.ov.field     = win->field;

	/* update overlay अगर needed */
	retval = 0;
	अगर (check_btres(fh, RESOURCE_OVERLAY)) अणु
		काष्ठा bttv_buffer *new;

		new = videobuf_sg_alloc(माप(*new));
		new->crop = btv->crop[!!fh->करो_crop].rect;
		bttv_overlay_risc(btv, &fh->ov, fh->ovfmt, new);
		retval = bttv_चयन_overlay(btv,fh,new);
	पूर्ण
	वापस retval;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल काष्ठा videobuf_queue* bttv_queue(काष्ठा bttv_fh *fh)
अणु
	काष्ठा videobuf_queue* q = शून्य;

	चयन (fh->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		q = &fh->cap;
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		q = &fh->vbi;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस q;
पूर्ण

अटल पूर्णांक bttv_resource(काष्ठा bttv_fh *fh)
अणु
	पूर्णांक res = 0;

	चयन (fh->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		res = RESOURCE_VIDEO_STREAM;
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		res = RESOURCE_VBI;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक bttv_चयन_type(काष्ठा bttv_fh *fh, क्रमागत v4l2_buf_type type)
अणु
	काष्ठा videobuf_queue *q = bttv_queue(fh);
	पूर्णांक res = bttv_resource(fh);

	अगर (check_btres(fh,res))
		वापस -EBUSY;
	अगर (videobuf_queue_is_busy(q))
		वापस -EBUSY;
	fh->type = type;
	वापस 0;
पूर्ण

अटल व्योम
pix_क्रमmat_set_size     (काष्ठा v4l2_pix_क्रमmat *       f,
			 स्थिर काष्ठा bttv_क्रमmat *     fmt,
			 अचिन्हित पूर्णांक                   width,
			 अचिन्हित पूर्णांक                   height)
अणु
	f->width = width;
	f->height = height;

	अगर (fmt->flags & FORMAT_FLAGS_PLANAR) अणु
		f->bytesperline = width; /* Y plane */
		f->sizeimage = (width * height * fmt->depth) >> 3;
	पूर्ण अन्यथा अणु
		f->bytesperline = (width * fmt->depth) >> 3;
		f->sizeimage = height * f->bytesperline;
	पूर्ण
पूर्ण

अटल पूर्णांक bttv_g_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bttv_fh *fh  = priv;

	pix_क्रमmat_set_size(&f->fmt.pix, fh->fmt,
				fh->width, fh->height);
	f->fmt.pix.field        = fh->cap.field;
	f->fmt.pix.pixelक्रमmat  = fh->fmt->fourcc;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bttv_fh *fh  = priv;

	f->fmt.win.w     = fh->ov.w;
	f->fmt.win.field = fh->ov.field;

	वापस 0;
पूर्ण

अटल व्योम bttv_get_width_mask_vid_cap(स्थिर काष्ठा bttv_क्रमmat *fmt,
					अचिन्हित पूर्णांक *width_mask,
					अचिन्हित पूर्णांक *width_bias)
अणु
	अगर (fmt->flags & FORMAT_FLAGS_PLANAR) अणु
		*width_mask = ~15; /* width must be a multiple of 16 pixels */
		*width_bias = 8;   /* nearest */
	पूर्ण अन्यथा अणु
		*width_mask = ~3; /* width must be a multiple of 4 pixels */
		*width_bias = 2;  /* nearest */
	पूर्ण
पूर्ण

अटल पूर्णांक bttv_try_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
						काष्ठा v4l2_क्रमmat *f)
अणु
	स्थिर काष्ठा bttv_क्रमmat *fmt;
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;
	क्रमागत v4l2_field field;
	__s32 width, height;
	__s32 height2;
	अचिन्हित पूर्णांक width_mask, width_bias;
	पूर्णांक rc;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;

	field = f->fmt.pix.field;

	चयन (field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_ALTERNATE:
	हाल V4L2_FIELD_INTERLACED:
		अवरोध;
	हाल V4L2_FIELD_SEQ_BT:
	हाल V4L2_FIELD_SEQ_TB:
		अगर (!(fmt->flags & FORMAT_FLAGS_PLANAR)) अणु
			field = V4L2_FIELD_SEQ_TB;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष: /* FIELD_ANY हाल */
		height2 = btv->crop[!!fh->करो_crop].rect.height >> 1;
		field = (f->fmt.pix.height > height2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
		अवरोध;
	पूर्ण

	width = f->fmt.pix.width;
	height = f->fmt.pix.height;

	bttv_get_width_mask_vid_cap(fmt, &width_mask, &width_bias);
	rc = limit_scaled_size_lock(fh, &width, &height, field,
			       width_mask, width_bias,
			       /* adjust_size */ 1,
			       /* adjust_crop */ 0);
	अगर (0 != rc)
		वापस rc;

	/* update data क्रम the application */
	f->fmt.pix.field = field;
	pix_क्रमmat_set_size(&f->fmt.pix, fmt, width, height);
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_try_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
						काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bttv_fh *fh = priv;

	verअगरy_winकरोw_lock(fh, &f->fmt.win,
			/* adjust_size */ 1,
			/* adjust_crop */ 0);
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_s_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक retval;
	स्थिर काष्ठा bttv_क्रमmat *fmt;
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;
	__s32 width, height;
	अचिन्हित पूर्णांक width_mask, width_bias;
	क्रमागत v4l2_field field;

	retval = bttv_चयन_type(fh, f->type);
	अगर (0 != retval)
		वापस retval;

	retval = bttv_try_fmt_vid_cap(file, priv, f);
	अगर (0 != retval)
		वापस retval;

	width = f->fmt.pix.width;
	height = f->fmt.pix.height;
	field = f->fmt.pix.field;

	fmt = क्रमmat_by_fourcc(f->fmt.pix.pixelक्रमmat);
	bttv_get_width_mask_vid_cap(fmt, &width_mask, &width_bias);
	retval = limit_scaled_size_lock(fh, &width, &height, f->fmt.pix.field,
			       width_mask, width_bias,
			       /* adjust_size */ 1,
			       /* adjust_crop */ 1);
	अगर (0 != retval)
		वापस retval;

	f->fmt.pix.field = field;

	/* update our state inक्रमmation */
	fh->fmt              = fmt;
	fh->cap.field        = f->fmt.pix.field;
	fh->cap.last         = V4L2_FIELD_NONE;
	fh->width            = f->fmt.pix.width;
	fh->height           = f->fmt.pix.height;
	btv->init.fmt        = fmt;
	btv->init.width      = f->fmt.pix.width;
	btv->init.height     = f->fmt.pix.height;

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_s_fmt_vid_overlay(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (no_overlay > 0) अणु
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		वापस -EINVAL;
	पूर्ण

	वापस setup_winकरोw_lock(fh, btv, &f->fmt.win, 1);
पूर्ण

अटल पूर्णांक bttv_querycap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_capability *cap)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (0 == v4l2)
		वापस -EINVAL;

	strscpy(cap->driver, "bttv", माप(cap->driver));
	strscpy(cap->card, btv->video_dev.name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "PCI:%s", pci_name(btv->c.pci));
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
			    V4L2_CAP_STREAMING | V4L2_CAP_DEVICE_CAPS;
	अगर (no_overlay <= 0)
		cap->capabilities |= V4L2_CAP_VIDEO_OVERLAY;
	अगर (video_is_रेजिस्टरed(&btv->vbi_dev))
		cap->capabilities |= V4L2_CAP_VBI_CAPTURE;
	अगर (video_is_रेजिस्टरed(&btv->radio_dev)) अणु
		cap->capabilities |= V4L2_CAP_RADIO;
		अगर (btv->has_tea575x)
			cap->capabilities |= V4L2_CAP_HW_FREQ_SEEK;
	पूर्ण

	/*
	 * No need to lock here: those vars are initialized during board
	 * probe and reमुख्यs untouched during the rest of the driver lअगरecycle
	 */
	अगर (btv->has_saa6588)
		cap->capabilities |= V4L2_CAP_RDS_CAPTURE;
	अगर (btv->tuner_type != TUNER_ABSENT)
		cap->capabilities |= V4L2_CAP_TUNER;
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_क्रमागत_fmt_cap_ovr(काष्ठा v4l2_fmtdesc *f)
अणु
	पूर्णांक index = -1, i;

	क्रम (i = 0; i < FORMATS; i++) अणु
		अगर (क्रमmats[i].fourcc != -1)
			index++;
		अगर ((अचिन्हित पूर्णांक)index == f->index)
			अवरोध;
	पूर्ण
	अगर (FORMATS == i)
		वापस -EINVAL;

	f->pixelक्रमmat = क्रमmats[i].fourcc;

	वापस i;
पूर्ण

अटल पूर्णांक bttv_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
				काष्ठा v4l2_fmtdesc *f)
अणु
	पूर्णांक rc = bttv_क्रमागत_fmt_cap_ovr(f);

	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_क्रमागत_fmt_vid_overlay(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	पूर्णांक rc;

	अगर (no_overlay > 0) अणु
		pr_err("V4L2_BUF_TYPE_VIDEO_OVERLAY: no_overlay\n");
		वापस -EINVAL;
	पूर्ण

	rc = bttv_क्रमागत_fmt_cap_ovr(f);

	अगर (rc < 0)
		वापस rc;

	अगर (!(क्रमmats[rc].flags & FORMAT_FLAGS_PACKED))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_fbuf(काष्ठा file *file, व्योम *f,
				काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;

	*fb = btv->fbuf;
	fb->capability = V4L2_FBUF_CAP_LIST_CLIPPING;
	fb->flags = V4L2_FBUF_FLAG_PRIMARY;
	अगर (fh->ovfmt)
		fb->fmt.pixelक्रमmat  = fh->ovfmt->fourcc;
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_overlay(काष्ठा file *file, व्योम *f, अचिन्हित पूर्णांक on)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;
	काष्ठा bttv_buffer *new;
	पूर्णांक retval = 0;

	अगर (on) अणु
		/* verअगरy args */
		अगर (unlikely(!btv->fbuf.base)) अणु
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely(!fh->ov.setup_ok)) अणु
			dprपूर्णांकk("%d: overlay: !setup_ok\n", btv->c.nr);
			retval = -EINVAL;
		पूर्ण
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (!check_alloc_btres_lock(btv, fh, RESOURCE_OVERLAY))
		वापस -EBUSY;

	अगर (on) अणु
		fh->ov.tvnorm = btv->tvnorm;
		new = videobuf_sg_alloc(माप(*new));
		new->crop = btv->crop[!!fh->करो_crop].rect;
		bttv_overlay_risc(btv, &fh->ov, fh->ovfmt, new);
	पूर्ण अन्यथा अणु
		new = शून्य;
	पूर्ण

	/* चयन over */
	retval = bttv_चयन_overlay(btv, fh, new);
	वापस retval;
पूर्ण

अटल पूर्णांक bttv_s_fbuf(काष्ठा file *file, व्योम *f,
				स्थिर काष्ठा v4l2_framebuffer *fb)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;
	स्थिर काष्ठा bttv_क्रमmat *fmt;
	पूर्णांक retval;

	अगर (!capable(CAP_SYS_ADMIN) &&
		!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	/* check args */
	fmt = क्रमmat_by_fourcc(fb->fmt.pixelक्रमmat);
	अगर (शून्य == fmt)
		वापस -EINVAL;
	अगर (0 == (fmt->flags & FORMAT_FLAGS_PACKED))
		वापस -EINVAL;

	retval = -EINVAL;
	अगर (fb->flags & V4L2_FBUF_FLAG_OVERLAY) अणु
		__s32 width = fb->fmt.width;
		__s32 height = fb->fmt.height;

		retval = limit_scaled_size_lock(fh, &width, &height,
					   V4L2_FIELD_INTERLACED,
					   /* width_mask */ ~3,
					   /* width_bias */ 2,
					   /* adjust_size */ 0,
					   /* adjust_crop */ 0);
		अगर (0 != retval)
			वापस retval;
	पूर्ण

	/* ok, accept it */
	btv->fbuf.base       = fb->base;
	btv->fbuf.fmt.width  = fb->fmt.width;
	btv->fbuf.fmt.height = fb->fmt.height;
	अगर (0 != fb->fmt.bytesperline)
		btv->fbuf.fmt.bytesperline = fb->fmt.bytesperline;
	अन्यथा
		btv->fbuf.fmt.bytesperline = btv->fbuf.fmt.width*fmt->depth/8;

	retval = 0;
	fh->ovfmt = fmt;
	btv->init.ovfmt = fmt;
	अगर (fb->flags & V4L2_FBUF_FLAG_OVERLAY) अणु
		fh->ov.w.left   = 0;
		fh->ov.w.top    = 0;
		fh->ov.w.width  = fb->fmt.width;
		fh->ov.w.height = fb->fmt.height;
		btv->init.ov.w.width  = fb->fmt.width;
		btv->init.ov.w.height = fb->fmt.height;

		kमुक्त(fh->ov.clips);
		fh->ov.clips = शून्य;
		fh->ov.nclips = 0;

		अगर (check_btres(fh, RESOURCE_OVERLAY)) अणु
			काष्ठा bttv_buffer *new;

			new = videobuf_sg_alloc(माप(*new));
			new->crop = btv->crop[!!fh->करो_crop].rect;
			bttv_overlay_risc(btv, &fh->ov, fh->ovfmt, new);
			retval = bttv_चयन_overlay(btv, fh, new);
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक bttv_reqbufs(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_requestbuffers *p)
अणु
	काष्ठा bttv_fh *fh = priv;
	वापस videobuf_reqbufs(bttv_queue(fh), p);
पूर्ण

अटल पूर्णांक bttv_querybuf(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_buffer *b)
अणु
	काष्ठा bttv_fh *fh = priv;
	वापस videobuf_querybuf(bttv_queue(fh), b);
पूर्ण

अटल पूर्णांक bttv_qbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;
	पूर्णांक res = bttv_resource(fh);

	अगर (!check_alloc_btres_lock(btv, fh, res))
		वापस -EBUSY;

	वापस videobuf_qbuf(bttv_queue(fh), b);
पूर्ण

अटल पूर्णांक bttv_dqbuf(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_buffer *b)
अणु
	काष्ठा bttv_fh *fh = priv;
	वापस videobuf_dqbuf(bttv_queue(fh), b,
			file->f_flags & O_NONBLOCK);
पूर्ण

अटल पूर्णांक bttv_streamon(काष्ठा file *file, व्योम *priv,
					क्रमागत v4l2_buf_type type)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;
	पूर्णांक res = bttv_resource(fh);

	अगर (!check_alloc_btres_lock(btv, fh, res))
		वापस -EBUSY;
	वापस videobuf_streamon(bttv_queue(fh));
पूर्ण


अटल पूर्णांक bttv_streamoff(काष्ठा file *file, व्योम *priv,
					क्रमागत v4l2_buf_type type)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;
	पूर्णांक retval;
	पूर्णांक res = bttv_resource(fh);


	retval = videobuf_streamoff(bttv_queue(fh));
	अगर (retval < 0)
		वापस retval;
	मुक्त_btres_lock(btv, fh, res);
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_parm(काष्ठा file *file, व्योम *f,
				काष्ठा v4l2_streamparm *parm)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;

	अगर (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;
	parm->parm.capture.पढ़ोbuffers = gbuffers;
	v4l2_video_std_frame_period(bttv_tvnorms[btv->tvnorm].v4l2_id,
				    &parm->parm.capture.समयperframe);

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_tuner(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_tuner *t)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (0 != t->index)
		वापस -EINVAL;

	t->rxsubchans = V4L2_TUNER_SUB_MONO;
	t->capability = V4L2_TUNER_CAP_NORM;
	bttv_call_all(btv, tuner, g_tuner, t);
	strscpy(t->name, "Television", माप(t->name));
	t->type       = V4L2_TUNER_ANALOG_TV;
	अगर (btपढ़ो(BT848_DSTATUS)&BT848_DSTATUS_HLOC)
		t->संकेत = 0xffff;

	अगर (btv->audio_mode_gpio)
		btv->audio_mode_gpio(btv, t, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_pixelaspect(काष्ठा file *file, व्योम *priv,
			      पूर्णांक type, काष्ठा v4l2_fract *f)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		वापस -EINVAL;

	/* defrect and bounds are set via g_selection */
	*f = bttv_tvnorms[btv->tvnorm].cropcap.pixelaspect;
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_g_selection(काष्ठा file *file, व्योम *f, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		/*
		 * No fh->करो_crop = 1; because btv->crop[1] may be
		 * inconsistent with fh->width or fh->height and apps
		 * करो not expect a change here.
		 */
		sel->r = btv->crop[!!fh->करो_crop].rect;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r = bttv_tvnorms[btv->tvnorm].cropcap.defrect;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r = bttv_tvnorms[btv->tvnorm].cropcap.bounds;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bttv_s_selection(काष्ठा file *file, व्योम *f, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा bttv_fh *fh = f;
	काष्ठा bttv *btv = fh->btv;
	स्थिर काष्ठा v4l2_rect *b;
	पूर्णांक retval;
	काष्ठा bttv_crop c;
	__s32 b_left;
	__s32 b_top;
	__s32 b_right;
	__s32 b_bottom;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    sel->type != V4L2_BUF_TYPE_VIDEO_OVERLAY)
		वापस -EINVAL;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	/* Make sure tvnorm, vbi_end and the current cropping
	   parameters reमुख्य consistent until we're करोne. Note
	   पढ़ो() may change vbi_end in check_alloc_btres_lock(). */
	retval = -EBUSY;

	अगर (locked_btres(fh->btv, VIDEO_RESOURCES)) अणु
		वापस retval;
	पूर्ण

	b = &bttv_tvnorms[btv->tvnorm].cropcap.bounds;

	b_left = b->left;
	b_right = b_left + b->width;
	b_bottom = b->top + b->height;

	b_top = max(b->top, btv->vbi_end);
	अगर (b_top + 32 >= b_bottom) अणु
		वापस retval;
	पूर्ण

	/* Min. scaled size 48 x 32. */
	c.rect.left = clamp_t(s32, sel->r.left, b_left, b_right - 48);
	c.rect.left = min(c.rect.left, (__s32) MAX_HDELAY);

	c.rect.width = clamp_t(s32, sel->r.width,
			     48, b_right - c.rect.left);

	c.rect.top = clamp_t(s32, sel->r.top, b_top, b_bottom - 32);
	/* Top and height must be a multiple of two. */
	c.rect.top = (c.rect.top + 1) & ~1;

	c.rect.height = clamp_t(s32, sel->r.height,
			      32, b_bottom - c.rect.top);
	c.rect.height = (c.rect.height + 1) & ~1;

	bttv_crop_calc_limits(&c);

	sel->r = c.rect;

	btv->crop[1] = c;

	fh->करो_crop = 1;

	अगर (fh->width < c.min_scaled_width) अणु
		fh->width = c.min_scaled_width;
		btv->init.width = c.min_scaled_width;
	पूर्ण अन्यथा अगर (fh->width > c.max_scaled_width) अणु
		fh->width = c.max_scaled_width;
		btv->init.width = c.max_scaled_width;
	पूर्ण

	अगर (fh->height < c.min_scaled_height) अणु
		fh->height = c.min_scaled_height;
		btv->init.height = c.min_scaled_height;
	पूर्ण अन्यथा अगर (fh->height > c.max_scaled_height) अणु
		fh->height = c.max_scaled_height;
		btv->init.height = c.max_scaled_height;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार bttv_पढ़ो(काष्ठा file *file, अक्षर __user *data,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bttv_fh *fh = file->निजी_data;
	पूर्णांक retval = 0;

	अगर (fh->btv->errors)
		bttv_reinit_bt848(fh->btv);
	dprपूर्णांकk("%d: read count=%d type=%s\n",
		fh->btv->c.nr, (पूर्णांक)count, v4l2_type_names[fh->type]);

	चयन (fh->type) अणु
	हाल V4L2_BUF_TYPE_VIDEO_CAPTURE:
		अगर (!check_alloc_btres_lock(fh->btv, fh, RESOURCE_VIDEO_READ)) अणु
			/* VIDEO_READ in use by another fh,
			   or VIDEO_STREAM by any fh. */
			वापस -EBUSY;
		पूर्ण
		retval = videobuf_पढ़ो_one(&fh->cap, data, count, ppos,
					   file->f_flags & O_NONBLOCK);
		मुक्त_btres_lock(fh->btv, fh, RESOURCE_VIDEO_READ);
		अवरोध;
	हाल V4L2_BUF_TYPE_VBI_CAPTURE:
		अगर (!check_alloc_btres_lock(fh->btv,fh,RESOURCE_VBI))
			वापस -EBUSY;
		retval = videobuf_पढ़ो_stream(&fh->vbi, data, count, ppos, 1,
					      file->f_flags & O_NONBLOCK);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस retval;
पूर्ण

अटल __poll_t bttv_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा bttv_fh *fh = file->निजी_data;
	काष्ठा bttv_buffer *buf;
	क्रमागत v4l2_field field;
	__poll_t rc = 0;
	__poll_t req_events = poll_requested_events(रुको);

	अगर (v4l2_event_pending(&fh->fh))
		rc = EPOLLPRI;
	अन्यथा अगर (req_events & EPOLLPRI)
		poll_रुको(file, &fh->fh.रुको, रुको);

	अगर (!(req_events & (EPOLLIN | EPOLLRDNORM)))
		वापस rc;

	अगर (V4L2_BUF_TYPE_VBI_CAPTURE == fh->type) अणु
		अगर (!check_alloc_btres_lock(fh->btv,fh,RESOURCE_VBI))
			वापस rc | EPOLLERR;
		वापस rc | videobuf_poll_stream(file, &fh->vbi, रुको);
	पूर्ण

	अगर (check_btres(fh,RESOURCE_VIDEO_STREAM)) अणु
		/* streaming capture */
		अगर (list_empty(&fh->cap.stream))
			वापस rc | EPOLLERR;
		buf = list_entry(fh->cap.stream.next,काष्ठा bttv_buffer,vb.stream);
	पूर्ण अन्यथा अणु
		/* पढ़ो() capture */
		अगर (शून्य == fh->cap.पढ़ो_buf) अणु
			/* need to capture a new frame */
			अगर (locked_btres(fh->btv,RESOURCE_VIDEO_STREAM))
				वापस rc | EPOLLERR;
			fh->cap.पढ़ो_buf = videobuf_sg_alloc(fh->cap.msize);
			अगर (शून्य == fh->cap.पढ़ो_buf)
				वापस rc | EPOLLERR;
			fh->cap.पढ़ो_buf->memory = V4L2_MEMORY_USERPTR;
			field = videobuf_next_field(&fh->cap);
			अगर (0 != fh->cap.ops->buf_prepare(&fh->cap,fh->cap.पढ़ो_buf,field)) अणु
				kमुक्त (fh->cap.पढ़ो_buf);
				fh->cap.पढ़ो_buf = शून्य;
				वापस rc | EPOLLERR;
			पूर्ण
			fh->cap.ops->buf_queue(&fh->cap,fh->cap.पढ़ो_buf);
			fh->cap.पढ़ो_off = 0;
		पूर्ण
		buf = (काष्ठा bttv_buffer*)fh->cap.पढ़ो_buf;
	पूर्ण

	poll_रुको(file, &buf->vb.करोne, रुको);
	अगर (buf->vb.state == VIDEOBUF_DONE ||
	    buf->vb.state == VIDEOBUF_ERROR)
		rc = rc | EPOLLIN|EPOLLRDNORM;
	वापस rc;
पूर्ण

अटल पूर्णांक bttv_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा bttv *btv = video_drvdata(file);
	काष्ठा bttv_fh *fh;
	क्रमागत v4l2_buf_type type = 0;

	dprपूर्णांकk("open dev=%s\n", video_device_node_name(vdev));

	अगर (vdev->vfl_type == VFL_TYPE_VIDEO) अणु
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	पूर्ण अन्यथा अगर (vdev->vfl_type == VFL_TYPE_VBI) अणु
		type = V4L2_BUF_TYPE_VBI_CAPTURE;
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		वापस -ENODEV;
	पूर्ण

	dprपूर्णांकk("%d: open called (type=%s)\n",
		btv->c.nr, v4l2_type_names[type]);

	/* allocate per filehandle data */
	fh = kदो_स्मृति(माप(*fh), GFP_KERNEL);
	अगर (unlikely(!fh))
		वापस -ENOMEM;
	btv->users++;
	file->निजी_data = fh;

	*fh = btv->init;
	v4l2_fh_init(&fh->fh, vdev);

	fh->type = type;
	fh->ov.setup_ok = 0;

	videobuf_queue_sg_init(&fh->cap, &bttv_video_qops,
			    &btv->c.pci->dev, &btv->s_lock,
			    V4L2_BUF_TYPE_VIDEO_CAPTURE,
			    V4L2_FIELD_INTERLACED,
			    माप(काष्ठा bttv_buffer),
			    fh, &btv->lock);
	videobuf_queue_sg_init(&fh->vbi, &bttv_vbi_qops,
			    &btv->c.pci->dev, &btv->s_lock,
			    V4L2_BUF_TYPE_VBI_CAPTURE,
			    V4L2_FIELD_SEQ_TB,
			    माप(काष्ठा bttv_buffer),
			    fh, &btv->lock);
	set_tvnorm(btv,btv->tvnorm);
	set_input(btv, btv->input, btv->tvnorm);
	audio_mute(btv, btv->mute);

	/* The V4L2 spec requires one global set of cropping parameters
	   which only change on request. These are stored in btv->crop[1].
	   However क्रम compatibility with V4L apps and cropping unaware
	   V4L2 apps we now reset the cropping parameters as seen through
	   this fh, which is to say VIDIOC_G_SELECTION and scaling limit checks
	   will use btv->crop[0], the शेष cropping parameters क्रम the
	   current video standard, and VIDIOC_S_FMT will not implicitly
	   change the cropping parameters until VIDIOC_S_SELECTION has been
	   called. */
	fh->करो_crop = !reset_crop; /* module parameter */

	/* Likewise there should be one global set of VBI capture
	   parameters, but क्रम compatibility with V4L apps and earlier
	   driver versions each fh has its own parameters. */
	bttv_vbi_fmt_reset(&fh->vbi_fmt, btv->tvnorm);

	bttv_field_count(btv);
	v4l2_fh_add(&fh->fh);
	वापस 0;
पूर्ण

अटल पूर्णांक bttv_release(काष्ठा file *file)
अणु
	काष्ठा bttv_fh *fh = file->निजी_data;
	काष्ठा bttv *btv = fh->btv;

	/* turn off overlay */
	अगर (check_btres(fh, RESOURCE_OVERLAY))
		bttv_चयन_overlay(btv,fh,शून्य);

	/* stop video capture */
	अगर (check_btres(fh, RESOURCE_VIDEO_STREAM)) अणु
		videobuf_streamoff(&fh->cap);
		मुक्त_btres_lock(btv,fh,RESOURCE_VIDEO_STREAM);
	पूर्ण
	अगर (fh->cap.पढ़ो_buf) अणु
		buffer_release(&fh->cap,fh->cap.पढ़ो_buf);
		kमुक्त(fh->cap.पढ़ो_buf);
	पूर्ण
	अगर (check_btres(fh, RESOURCE_VIDEO_READ)) अणु
		मुक्त_btres_lock(btv, fh, RESOURCE_VIDEO_READ);
	पूर्ण

	/* stop vbi capture */
	अगर (check_btres(fh, RESOURCE_VBI)) अणु
		videobuf_stop(&fh->vbi);
		मुक्त_btres_lock(btv,fh,RESOURCE_VBI);
	पूर्ण

	/* मुक्त stuff */

	videobuf_mmap_मुक्त(&fh->cap);
	videobuf_mmap_मुक्त(&fh->vbi);
	file->निजी_data = शून्य;

	btv->users--;
	bttv_field_count(btv);

	अगर (!btv->users)
		audio_mute(btv, btv->mute);

	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	kमुक्त(fh);
	वापस 0;
पूर्ण

अटल पूर्णांक
bttv_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा bttv_fh *fh = file->निजी_data;

	dprपूर्णांकk("%d: mmap type=%s 0x%lx+%ld\n",
		fh->btv->c.nr, v4l2_type_names[fh->type],
		vma->vm_start, vma->vm_end - vma->vm_start);
	वापस videobuf_mmap_mapper(bttv_queue(fh),vma);
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations bttv_fops =
अणु
	.owner		  = THIS_MODULE,
	.खोलो		  = bttv_खोलो,
	.release	  = bttv_release,
	.unlocked_ioctl	  = video_ioctl2,
	.पढ़ो		  = bttv_पढ़ो,
	.mmap		  = bttv_mmap,
	.poll		  = bttv_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops bttv_ioctl_ops = अणु
	.vidioc_querycap                = bttv_querycap,
	.vidioc_क्रमागत_fmt_vid_cap        = bttv_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap           = bttv_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap         = bttv_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap           = bttv_s_fmt_vid_cap,
	.vidioc_क्रमागत_fmt_vid_overlay    = bttv_क्रमागत_fmt_vid_overlay,
	.vidioc_g_fmt_vid_overlay       = bttv_g_fmt_vid_overlay,
	.vidioc_try_fmt_vid_overlay     = bttv_try_fmt_vid_overlay,
	.vidioc_s_fmt_vid_overlay       = bttv_s_fmt_vid_overlay,
	.vidioc_g_fmt_vbi_cap           = bttv_g_fmt_vbi_cap,
	.vidioc_try_fmt_vbi_cap         = bttv_try_fmt_vbi_cap,
	.vidioc_s_fmt_vbi_cap           = bttv_s_fmt_vbi_cap,
	.vidioc_g_pixelaspect           = bttv_g_pixelaspect,
	.vidioc_reqbufs                 = bttv_reqbufs,
	.vidioc_querybuf                = bttv_querybuf,
	.vidioc_qbuf                    = bttv_qbuf,
	.vidioc_dqbuf                   = bttv_dqbuf,
	.vidioc_s_std                   = bttv_s_std,
	.vidioc_g_std                   = bttv_g_std,
	.vidioc_क्रमागत_input              = bttv_क्रमागत_input,
	.vidioc_g_input                 = bttv_g_input,
	.vidioc_s_input                 = bttv_s_input,
	.vidioc_streamon                = bttv_streamon,
	.vidioc_streamoff               = bttv_streamoff,
	.vidioc_g_tuner                 = bttv_g_tuner,
	.vidioc_s_tuner                 = bttv_s_tuner,
	.vidioc_g_selection             = bttv_g_selection,
	.vidioc_s_selection             = bttv_s_selection,
	.vidioc_g_fbuf                  = bttv_g_fbuf,
	.vidioc_s_fbuf                  = bttv_s_fbuf,
	.vidioc_overlay                 = bttv_overlay,
	.vidioc_g_parm                  = bttv_g_parm,
	.vidioc_g_frequency             = bttv_g_frequency,
	.vidioc_s_frequency             = bttv_s_frequency,
	.vidioc_log_status		= bttv_log_status,
	.vidioc_querystd		= bttv_querystd,
	.vidioc_subscribe_event		= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event	= v4l2_event_unsubscribe,
#अगर_घोषित CONFIG_VIDEO_ADV_DEBUG
	.vidioc_g_रेजिस्टर		= bttv_g_रेजिस्टर,
	.vidioc_s_रेजिस्टर		= bttv_s_रेजिस्टर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा video_device bttv_video_ढाँचा = अणु
	.fops         = &bttv_fops,
	.ioctl_ops    = &bttv_ioctl_ops,
	.tvnorms      = BTTV_NORMS,
पूर्ण;

/* ----------------------------------------------------------------------- */
/* radio पूर्णांकerface                                                         */

अटल पूर्णांक radio_खोलो(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा bttv *btv = video_drvdata(file);
	काष्ठा bttv_fh *fh;

	dprपूर्णांकk("open dev=%s\n", video_device_node_name(vdev));

	dprपूर्णांकk("%d: open called (radio)\n", btv->c.nr);

	/* allocate per filehandle data */
	fh = kदो_स्मृति(माप(*fh), GFP_KERNEL);
	अगर (unlikely(!fh))
		वापस -ENOMEM;
	file->निजी_data = fh;
	*fh = btv->init;
	v4l2_fh_init(&fh->fh, vdev);

	btv->radio_user++;
	audio_mute(btv, btv->mute);

	v4l2_fh_add(&fh->fh);

	वापस 0;
पूर्ण

अटल पूर्णांक radio_release(काष्ठा file *file)
अणु
	काष्ठा bttv_fh *fh = file->निजी_data;
	काष्ठा bttv *btv = fh->btv;
	काष्ठा saa6588_command cmd;

	file->निजी_data = शून्य;
	v4l2_fh_del(&fh->fh);
	v4l2_fh_निकास(&fh->fh);
	kमुक्त(fh);

	btv->radio_user--;

	bttv_call_all(btv, core, ioctl, SAA6588_CMD_CLOSE, &cmd);

	अगर (btv->radio_user == 0)
		btv->has_radio_tuner = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक radio_g_tuner(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_tuner *t)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (0 != t->index)
		वापस -EINVAL;
	strscpy(t->name, "Radio", माप(t->name));
	t->type = V4L2_TUNER_RADIO;
	radio_enable(btv);

	bttv_call_all(btv, tuner, g_tuner, t);

	अगर (btv->audio_mode_gpio)
		btv->audio_mode_gpio(btv, t, 0);

	अगर (btv->has_tea575x)
		वापस snd_tea575x_g_tuner(&btv->tea, t);

	वापस 0;
पूर्ण

अटल पूर्णांक radio_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *t)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (0 != t->index)
		वापस -EINVAL;

	radio_enable(btv);
	bttv_call_all(btv, tuner, s_tuner, t);
	वापस 0;
पूर्ण

अटल पूर्णांक radio_s_hw_freq_seek(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_hw_freq_seek *a)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (btv->has_tea575x)
		वापस snd_tea575x_s_hw_freq_seek(file, &btv->tea, a);

	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक radio_क्रमागत_freq_bands(काष्ठा file *file, व्योम *priv,
					 काष्ठा v4l2_frequency_band *band)
अणु
	काष्ठा bttv_fh *fh = priv;
	काष्ठा bttv *btv = fh->btv;

	अगर (btv->has_tea575x)
		वापस snd_tea575x_क्रमागत_freq_bands(&btv->tea, band);

	वापस -ENOTTY;
पूर्ण

अटल sमाप_प्रकार radio_पढ़ो(काष्ठा file *file, अक्षर __user *data,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा bttv_fh *fh = file->निजी_data;
	काष्ठा bttv *btv = fh->btv;
	काष्ठा saa6588_command cmd;

	cmd.block_count = count / 3;
	cmd.nonblocking = file->f_flags & O_NONBLOCK;
	cmd.buffer = data;
	cmd.instance = file;
	cmd.result = -ENODEV;
	radio_enable(btv);

	bttv_call_all(btv, core, ioctl, SAA6588_CMD_READ, &cmd);

	वापस cmd.result;
पूर्ण

अटल __poll_t radio_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा bttv_fh *fh = file->निजी_data;
	काष्ठा bttv *btv = fh->btv;
	__poll_t req_events = poll_requested_events(रुको);
	काष्ठा saa6588_command cmd;
	__poll_t res = 0;

	अगर (v4l2_event_pending(&fh->fh))
		res = EPOLLPRI;
	अन्यथा अगर (req_events & EPOLLPRI)
		poll_रुको(file, &fh->fh.रुको, रुको);
	radio_enable(btv);
	cmd.instance = file;
	cmd.event_list = रुको;
	cmd.poll_mask = res;
	bttv_call_all(btv, core, ioctl, SAA6588_CMD_POLL, &cmd);

	वापस cmd.poll_mask;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations radio_fops =
अणु
	.owner	  = THIS_MODULE,
	.खोलो	  = radio_खोलो,
	.पढ़ो     = radio_पढ़ो,
	.release  = radio_release,
	.unlocked_ioctl = video_ioctl2,
	.poll     = radio_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops radio_ioctl_ops = अणु
	.vidioc_querycap        = bttv_querycap,
	.vidioc_log_status	= bttv_log_status,
	.vidioc_g_tuner         = radio_g_tuner,
	.vidioc_s_tuner         = radio_s_tuner,
	.vidioc_g_frequency     = bttv_g_frequency,
	.vidioc_s_frequency     = bttv_s_frequency,
	.vidioc_s_hw_freq_seek	= radio_s_hw_freq_seek,
	.vidioc_क्रमागत_freq_bands	= radio_क्रमागत_freq_bands,
	.vidioc_subscribe_event = v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
पूर्ण;

अटल काष्ठा video_device radio_ढाँचा = अणु
	.fops      = &radio_fops,
	.ioctl_ops = &radio_ioctl_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */
/* some debug code                                                         */

अटल पूर्णांक bttv_risc_decode(u32 risc)
अणु
	अटल अक्षर *instr[16] = अणु
		[ BT848_RISC_WRITE     >> 28 ] = "write",
		[ BT848_RISC_SKIP      >> 28 ] = "skip",
		[ BT848_RISC_WRITEC    >> 28 ] = "writec",
		[ BT848_RISC_JUMP      >> 28 ] = "jump",
		[ BT848_RISC_SYNC      >> 28 ] = "sync",
		[ BT848_RISC_WRITE123  >> 28 ] = "write123",
		[ BT848_RISC_SKIP123   >> 28 ] = "skip123",
		[ BT848_RISC_WRITE1S23 >> 28 ] = "write1s23",
	पूर्ण;
	अटल पूर्णांक incr[16] = अणु
		[ BT848_RISC_WRITE     >> 28 ] = 2,
		[ BT848_RISC_JUMP      >> 28 ] = 2,
		[ BT848_RISC_SYNC      >> 28 ] = 2,
		[ BT848_RISC_WRITE123  >> 28 ] = 5,
		[ BT848_RISC_SKIP123   >> 28 ] = 2,
		[ BT848_RISC_WRITE1S23 >> 28 ] = 3,
	पूर्ण;
	अटल अक्षर *bits[] = अणु
		"be0",  "be1",  "be2",  "be3/resync",
		"set0", "set1", "set2", "set3",
		"clr0", "clr1", "clr2", "clr3",
		"irq",  "res",  "eol",  "sol",
	पूर्ण;
	पूर्णांक i;

	pr_cont("0x%08x [ %s", risc,
	       instr[risc >> 28] ? instr[risc >> 28] : "INVALID");
	क्रम (i = ARRAY_SIZE(bits)-1; i >= 0; i--)
		अगर (risc & (1 << (i + 12)))
			pr_cont(" %s", bits[i]);
	pr_cont(" count=%d ]\n", risc & 0xfff);
	वापस incr[risc >> 28] ? incr[risc >> 28] : 1;
पूर्ण

अटल व्योम bttv_risc_disयंत्र(काष्ठा bttv *btv,
			     काष्ठा btcx_riscmem *risc)
अणु
	अचिन्हित पूर्णांक i,j,n;

	pr_info("%s: risc disasm: %p [dma=0x%08lx]\n",
		btv->c.v4l2_dev.name, risc->cpu, (अचिन्हित दीर्घ)risc->dma);
	क्रम (i = 0; i < (risc->size >> 2); i += n) अणु
		pr_info("%s:   0x%lx: ",
			btv->c.v4l2_dev.name,
			(अचिन्हित दीर्घ)(risc->dma + (i<<2)));
		n = bttv_risc_decode(le32_to_cpu(risc->cpu[i]));
		क्रम (j = 1; j < n; j++)
			pr_info("%s:   0x%lx: 0x%08x [ arg #%d ]\n",
				btv->c.v4l2_dev.name,
				(अचिन्हित दीर्घ)(risc->dma + ((i+j)<<2)),
				risc->cpu[i+j], j);
		अगर (0 == risc->cpu[i])
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bttv_prपूर्णांक_riscaddr(काष्ठा bttv *btv)
अणु
	pr_info("  main: %08llx\n", (अचिन्हित दीर्घ दीर्घ)btv->मुख्य.dma);
	pr_info("  vbi : o=%08llx e=%08llx\n",
		btv->cvbi ? (अचिन्हित दीर्घ दीर्घ)btv->cvbi->top.dma : 0,
		btv->cvbi ? (अचिन्हित दीर्घ दीर्घ)btv->cvbi->bottom.dma : 0);
	pr_info("  cap : o=%08llx e=%08llx\n",
		btv->curr.top
		? (अचिन्हित दीर्घ दीर्घ)btv->curr.top->top.dma : 0,
		btv->curr.bottom
		? (अचिन्हित दीर्घ दीर्घ)btv->curr.bottom->bottom.dma : 0);
	pr_info("  scr : o=%08llx e=%08llx\n",
		btv->screen ? (अचिन्हित दीर्घ दीर्घ)btv->screen->top.dma : 0,
		btv->screen ? (अचिन्हित दीर्घ दीर्घ)btv->screen->bottom.dma : 0);
	bttv_risc_disयंत्र(btv, &btv->मुख्य);
पूर्ण

/* ----------------------------------------------------------------------- */
/* irq handler                                                             */

अटल अक्षर *irq_name[] = अणु
	"FMTCHG",  // क्रमmat change detected (525 vs. 625)
	"VSYNC",   // vertical sync (new field)
	"HSYNC",   // horizontal sync
	"OFLOW",   // chroma/luma AGC overflow
	"HLOCK",   // horizontal lock changed
	"VPRES",   // video presence changed
	"6", "7",
	"I2CDONE", // hw irc operation finished
	"GPINT",   // gpio port triggered irq
	"10",
	"RISCI",   // risc inकाष्ठाion triggered irq
	"FBUS",    // pixel data fअगरo dropped data (high pci bus latencies)
	"FTRGT",   // pixel data fअगरo overrun
	"FDSR",    // fअगरo data stream resyncronisation
	"PPERR",   // parity error (data transfer)
	"RIPERR",  // parity error (पढ़ो risc inकाष्ठाions)
	"PABORT",  // pci पात
	"OCERR",   // risc inकाष्ठाion error
	"SCERR",   // syncronisation error
पूर्ण;

अटल व्योम bttv_prपूर्णांक_irqbits(u32 prपूर्णांक, u32 mark)
अणु
	अचिन्हित पूर्णांक i;

	pr_cont("bits:");
	क्रम (i = 0; i < ARRAY_SIZE(irq_name); i++) अणु
		अगर (prपूर्णांक & (1 << i))
			pr_cont(" %s", irq_name[i]);
		अगर (mark & (1 << i))
			pr_cont("*");
	पूर्ण
पूर्ण

अटल व्योम bttv_irq_debug_low_latency(काष्ठा bttv *btv, u32 rc)
अणु
	pr_warn("%d: irq: skipped frame [main=%lx,o_vbi=%lx,o_field=%lx,rc=%lx]\n",
		btv->c.nr,
		(अचिन्हित दीर्घ)btv->मुख्य.dma,
		(अचिन्हित दीर्घ)le32_to_cpu(btv->मुख्य.cpu[RISC_SLOT_O_VBI+1]),
		(अचिन्हित दीर्घ)le32_to_cpu(btv->मुख्य.cpu[RISC_SLOT_O_FIELD+1]),
		(अचिन्हित दीर्घ)rc);

	अगर (0 == (btपढ़ो(BT848_DSTATUS) & BT848_DSTATUS_HLOC)) अणु
		pr_notice("%d: Oh, there (temporarily?) is no input signal. Ok, then this is harmless, don't worry ;)\n",
			  btv->c.nr);
		वापस;
	पूर्ण
	pr_notice("%d: Uhm. Looks like we have unusual high IRQ latencies\n",
		  btv->c.nr);
	pr_notice("%d: Lets try to catch the culprit red-handed ...\n",
		  btv->c.nr);
	dump_stack();
पूर्ण

अटल पूर्णांक
bttv_irq_next_video(काष्ठा bttv *btv, काष्ठा bttv_buffer_set *set)
अणु
	काष्ठा bttv_buffer *item;

	स_रखो(set,0,माप(*set));

	/* capture request ? */
	अगर (!list_empty(&btv->capture)) अणु
		set->frame_irq = 1;
		item = list_entry(btv->capture.next, काष्ठा bttv_buffer, vb.queue);
		अगर (V4L2_FIELD_HAS_TOP(item->vb.field))
			set->top    = item;
		अगर (V4L2_FIELD_HAS_BOTTOM(item->vb.field))
			set->bottom = item;

		/* capture request क्रम other field ? */
		अगर (!V4L2_FIELD_HAS_BOTH(item->vb.field) &&
		    (item->vb.queue.next != &btv->capture)) अणु
			item = list_entry(item->vb.queue.next, काष्ठा bttv_buffer, vb.queue);
			/* Mike Isely <isely@pobox.com> - Only check
			 * and set up the bottom field in the logic
			 * below.  Don't ever करो the top field.  This
			 * of course means that अगर we set up the
			 * bottom field in the above code that we'll
			 * actually skip a field.  But that's OK.
			 * Having processed only a single buffer this
			 * समय, then the next समय around the first
			 * available buffer should be क्रम a top field.
			 * That will then cause us here to set up a
			 * top then a bottom field in the normal way.
			 * The alternative to this understanding is
			 * that we set up the second available buffer
			 * as a top field, but that's out of order
			 * since this driver always processes the top
			 * field first - the effect will be the two
			 * buffers being वापसed in the wrong order,
			 * with the second buffer also being delayed
			 * by one field समय (owing to the fअगरo nature
			 * of videobuf).  Worse still, we'll be stuck
			 * करोing fields out of order now every समय
			 * until something अन्यथा causes a field to be
			 * dropped.  By effectively क्रमcing a field to
			 * drop this way then we always get back पूर्णांकo
			 * sync within a single frame समय.  (Out of
			 * order fields can screw up deपूर्णांकerlacing
			 * algorithms.) */
			अगर (!V4L2_FIELD_HAS_BOTH(item->vb.field)) अणु
				अगर (शून्य == set->bottom &&
				    V4L2_FIELD_BOTTOM == item->vb.field) अणु
					set->bottom = item;
				पूर्ण
				अगर (शून्य != set->top  &&  शून्य != set->bottom)
					set->top_irq = 2;
			पूर्ण
		पूर्ण
	पूर्ण

	/* screen overlay ? */
	अगर (शून्य != btv->screen) अणु
		अगर (V4L2_FIELD_HAS_BOTH(btv->screen->vb.field)) अणु
			अगर (शून्य == set->top && शून्य == set->bottom) अणु
				set->top    = btv->screen;
				set->bottom = btv->screen;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (V4L2_FIELD_TOP == btv->screen->vb.field &&
			    शून्य == set->top) अणु
				set->top = btv->screen;
			पूर्ण
			अगर (V4L2_FIELD_BOTTOM == btv->screen->vb.field &&
			    शून्य == set->bottom) अणु
				set->bottom = btv->screen;
			पूर्ण
		पूर्ण
	पूर्ण

	dprपूर्णांकk("%d: next set: top=%p bottom=%p [screen=%p,irq=%d,%d]\n",
		btv->c.nr, set->top, set->bottom,
		btv->screen, set->frame_irq, set->top_irq);
	वापस 0;
पूर्ण

अटल व्योम
bttv_irq_wakeup_video(काष्ठा bttv *btv, काष्ठा bttv_buffer_set *wakeup,
		      काष्ठा bttv_buffer_set *curr, अचिन्हित पूर्णांक state)
अणु
	u64 ts = kसमय_get_ns();

	अगर (wakeup->top == wakeup->bottom) अणु
		अगर (शून्य != wakeup->top && curr->top != wakeup->top) अणु
			अगर (irq_debug > 1)
				pr_debug("%d: wakeup: both=%p\n",
					 btv->c.nr, wakeup->top);
			wakeup->top->vb.ts = ts;
			wakeup->top->vb.field_count = btv->field_count;
			wakeup->top->vb.state = state;
			wake_up(&wakeup->top->vb.करोne);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (शून्य != wakeup->top && curr->top != wakeup->top) अणु
			अगर (irq_debug > 1)
				pr_debug("%d: wakeup: top=%p\n",
					 btv->c.nr, wakeup->top);
			wakeup->top->vb.ts = ts;
			wakeup->top->vb.field_count = btv->field_count;
			wakeup->top->vb.state = state;
			wake_up(&wakeup->top->vb.करोne);
		पूर्ण
		अगर (शून्य != wakeup->bottom && curr->bottom != wakeup->bottom) अणु
			अगर (irq_debug > 1)
				pr_debug("%d: wakeup: bottom=%p\n",
					 btv->c.nr, wakeup->bottom);
			wakeup->bottom->vb.ts = ts;
			wakeup->bottom->vb.field_count = btv->field_count;
			wakeup->bottom->vb.state = state;
			wake_up(&wakeup->bottom->vb.करोne);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
bttv_irq_wakeup_vbi(काष्ठा bttv *btv, काष्ठा bttv_buffer *wakeup,
		    अचिन्हित पूर्णांक state)
अणु
	अगर (शून्य == wakeup)
		वापस;

	wakeup->vb.ts = kसमय_get_ns();
	wakeup->vb.field_count = btv->field_count;
	wakeup->vb.state = state;
	wake_up(&wakeup->vb.करोne);
पूर्ण

अटल व्योम bttv_irq_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bttv *btv = from_समयr(btv, t, समयout);
	काष्ठा bttv_buffer_set old,new;
	काष्ठा bttv_buffer *ovbi;
	काष्ठा bttv_buffer *item;
	अचिन्हित दीर्घ flags;

	अगर (bttv_verbose) अणु
		pr_info("%d: timeout: drop=%d irq=%d/%d, risc=%08x, ",
			btv->c.nr, btv->framedrop, btv->irq_me, btv->irq_total,
			btपढ़ो(BT848_RISC_COUNT));
		bttv_prपूर्णांक_irqbits(btपढ़ो(BT848_INT_STAT),0);
		pr_cont("\n");
	पूर्ण

	spin_lock_irqsave(&btv->s_lock,flags);

	/* deactivate stuff */
	स_रखो(&new,0,माप(new));
	old  = btv->curr;
	ovbi = btv->cvbi;
	btv->curr = new;
	btv->cvbi = शून्य;
	btv->loop_irq = 0;
	bttv_buffer_activate_video(btv, &new);
	bttv_buffer_activate_vbi(btv,   शून्य);
	bttv_set_dma(btv, 0);

	/* wake up */
	bttv_irq_wakeup_video(btv, &old, &new, VIDEOBUF_ERROR);
	bttv_irq_wakeup_vbi(btv, ovbi, VIDEOBUF_ERROR);

	/* cancel all outstanding capture / vbi requests */
	जबतक (!list_empty(&btv->capture)) अणु
		item = list_entry(btv->capture.next, काष्ठा bttv_buffer, vb.queue);
		list_del(&item->vb.queue);
		item->vb.state = VIDEOBUF_ERROR;
		wake_up(&item->vb.करोne);
	पूर्ण
	जबतक (!list_empty(&btv->vcapture)) अणु
		item = list_entry(btv->vcapture.next, काष्ठा bttv_buffer, vb.queue);
		list_del(&item->vb.queue);
		item->vb.state = VIDEOBUF_ERROR;
		wake_up(&item->vb.करोne);
	पूर्ण

	btv->errors++;
	spin_unlock_irqrestore(&btv->s_lock,flags);
पूर्ण

अटल व्योम
bttv_irq_wakeup_top(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_buffer *wakeup = btv->curr.top;

	अगर (शून्य == wakeup)
		वापस;

	spin_lock(&btv->s_lock);
	btv->curr.top_irq = 0;
	btv->curr.top = शून्य;
	bttv_risc_hook(btv, RISC_SLOT_O_FIELD, शून्य, 0);

	wakeup->vb.ts = kसमय_get_ns();
	wakeup->vb.field_count = btv->field_count;
	wakeup->vb.state = VIDEOBUF_DONE;
	wake_up(&wakeup->vb.करोne);
	spin_unlock(&btv->s_lock);
पूर्ण

अटल अंतरभूत पूर्णांक is_active(काष्ठा btcx_riscmem *risc, u32 rc)
अणु
	अगर (rc < risc->dma)
		वापस 0;
	अगर (rc > risc->dma + risc->size)
		वापस 0;
	वापस 1;
पूर्ण

अटल व्योम
bttv_irq_चयन_video(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_buffer_set new;
	काष्ठा bttv_buffer_set old;
	dma_addr_t rc;

	spin_lock(&btv->s_lock);

	/* new buffer set */
	bttv_irq_next_video(btv, &new);
	rc = btपढ़ो(BT848_RISC_COUNT);
	अगर ((btv->curr.top    && is_active(&btv->curr.top->top,       rc)) ||
	    (btv->curr.bottom && is_active(&btv->curr.bottom->bottom, rc))) अणु
		btv->framedrop++;
		अगर (debug_latency)
			bttv_irq_debug_low_latency(btv, rc);
		spin_unlock(&btv->s_lock);
		वापस;
	पूर्ण

	/* चयन over */
	old = btv->curr;
	btv->curr = new;
	btv->loop_irq &= ~1;
	bttv_buffer_activate_video(btv, &new);
	bttv_set_dma(btv, 0);

	/* चयन input */
	अगर (UNSET != btv->new_input) अणु
		video_mux(btv,btv->new_input);
		btv->new_input = UNSET;
	पूर्ण

	/* wake up finished buffers */
	bttv_irq_wakeup_video(btv, &old, &new, VIDEOBUF_DONE);
	spin_unlock(&btv->s_lock);
पूर्ण

अटल व्योम
bttv_irq_चयन_vbi(काष्ठा bttv *btv)
अणु
	काष्ठा bttv_buffer *new = शून्य;
	काष्ठा bttv_buffer *old;
	u32 rc;

	spin_lock(&btv->s_lock);

	अगर (!list_empty(&btv->vcapture))
		new = list_entry(btv->vcapture.next, काष्ठा bttv_buffer, vb.queue);
	old = btv->cvbi;

	rc = btपढ़ो(BT848_RISC_COUNT);
	अगर (शून्य != old && (is_active(&old->top,    rc) ||
			    is_active(&old->bottom, rc))) अणु
		btv->framedrop++;
		अगर (debug_latency)
			bttv_irq_debug_low_latency(btv, rc);
		spin_unlock(&btv->s_lock);
		वापस;
	पूर्ण

	/* चयन */
	btv->cvbi = new;
	btv->loop_irq &= ~4;
	bttv_buffer_activate_vbi(btv, new);
	bttv_set_dma(btv, 0);

	bttv_irq_wakeup_vbi(btv, old, VIDEOBUF_DONE);
	spin_unlock(&btv->s_lock);
पूर्ण

अटल irqवापस_t bttv_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 stat,astat;
	u32 dstat;
	पूर्णांक count;
	काष्ठा bttv *btv;
	पूर्णांक handled = 0;

	btv=(काष्ठा bttv *)dev_id;

	count=0;
	जबतक (1) अणु
		/* get/clear पूर्णांकerrupt status bits */
		stat=btपढ़ो(BT848_INT_STAT);
		astat=stat&btपढ़ो(BT848_INT_MASK);
		अगर (!astat)
			अवरोध;
		handled = 1;
		btग_लिखो(stat,BT848_INT_STAT);

		/* get device status bits */
		dstat=btपढ़ो(BT848_DSTATUS);

		अगर (irq_debug) अणु
			pr_debug("%d: irq loop=%d fc=%d riscs=%x, riscc=%08x, ",
				 btv->c.nr, count, btv->field_count,
				 stat>>28, btपढ़ो(BT848_RISC_COUNT));
			bttv_prपूर्णांक_irqbits(stat,astat);
			अगर (stat & BT848_INT_HLOCK)
				pr_cont("   HLOC => %s",
					dstat & BT848_DSTATUS_HLOC
					? "yes" : "no");
			अगर (stat & BT848_INT_VPRES)
				pr_cont("   PRES => %s",
					dstat & BT848_DSTATUS_PRES
					? "yes" : "no");
			अगर (stat & BT848_INT_FMTCHG)
				pr_cont("   NUML => %s",
					dstat & BT848_DSTATUS_NUML
					? "625" : "525");
			pr_cont("\n");
		पूर्ण

		अगर (astat&BT848_INT_VSYNC)
			btv->field_count++;

		अगर ((astat & BT848_INT_GPINT) && btv->remote) अणु
			bttv_input_irq(btv);
		पूर्ण

		अगर (astat & BT848_INT_I2CDONE) अणु
			btv->i2c_करोne = stat;
			wake_up(&btv->i2c_queue);
		पूर्ण

		अगर ((astat & BT848_INT_RISCI)  &&  (stat & (4<<28)))
			bttv_irq_चयन_vbi(btv);

		अगर ((astat & BT848_INT_RISCI)  &&  (stat & (2<<28)))
			bttv_irq_wakeup_top(btv);

		अगर ((astat & BT848_INT_RISCI)  &&  (stat & (1<<28)))
			bttv_irq_चयन_video(btv);

		अगर ((astat & BT848_INT_HLOCK)  &&  btv->opt_स्वतःmute)
			/* trigger स्वतःmute */
			audio_mux_gpio(btv, btv->audio_input, btv->mute);

		अगर (astat & (BT848_INT_SCERR|BT848_INT_OCERR)) अणु
			pr_info("%d: %s%s @ %08x,",
				btv->c.nr,
				(astat & BT848_INT_SCERR) ? "SCERR" : "",
				(astat & BT848_INT_OCERR) ? "OCERR" : "",
				btपढ़ो(BT848_RISC_COUNT));
			bttv_prपूर्णांक_irqbits(stat,astat);
			pr_cont("\n");
			अगर (bttv_debug)
				bttv_prपूर्णांक_riscaddr(btv);
		पूर्ण
		अगर (fdsr && astat & BT848_INT_FDSR) अणु
			pr_info("%d: FDSR @ %08x\n",
				btv->c.nr, btपढ़ो(BT848_RISC_COUNT));
			अगर (bttv_debug)
				bttv_prपूर्णांक_riscaddr(btv);
		पूर्ण

		count++;
		अगर (count > 4) अणु

			अगर (count > 8 || !(astat & BT848_INT_GPINT)) अणु
				btग_लिखो(0, BT848_INT_MASK);

				pr_err("%d: IRQ lockup, cleared int mask [",
				       btv->c.nr);
			पूर्ण अन्यथा अणु
				pr_err("%d: IRQ lockup, clearing GPINT from int mask [",
				       btv->c.nr);

				btग_लिखो(btपढ़ो(BT848_INT_MASK) & (-1 ^ BT848_INT_GPINT),
						BT848_INT_MASK);
			पूर्ण

			bttv_prपूर्णांक_irqbits(stat,astat);

			pr_cont("]\n");
		पूर्ण
	पूर्ण
	btv->irq_total++;
	अगर (handled)
		btv->irq_me++;
	वापस IRQ_RETVAL(handled);
पूर्ण


/* ----------------------------------------------------------------------- */
/* initialization                                                          */

अटल व्योम vdev_init(काष्ठा bttv *btv,
		      काष्ठा video_device *vfd,
		      स्थिर काष्ठा video_device *ढाँचा,
		      स्थिर अक्षर *type_name)
अणु
	*vfd = *ढाँचा;
	vfd->v4l2_dev = &btv->c.v4l2_dev;
	vfd->release = video_device_release_empty;
	video_set_drvdata(vfd, btv);
	snम_लिखो(vfd->name, माप(vfd->name), "BT%d%s %s (%s)",
		 btv->id, (btv->id==848 && btv->revision==0x12) ? "A" : "",
		 type_name, bttv_tvcards[btv->c.type].name);
	अगर (btv->tuner_type == TUNER_ABSENT) अणु
		v4l2_disable_ioctl(vfd, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(vfd, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(vfd, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(vfd, VIDIOC_S_TUNER);
	पूर्ण
पूर्ण

अटल व्योम bttv_unरेजिस्टर_video(काष्ठा bttv *btv)
अणु
	video_unरेजिस्टर_device(&btv->video_dev);
	video_unरेजिस्टर_device(&btv->vbi_dev);
	video_unरेजिस्टर_device(&btv->radio_dev);
पूर्ण

/* रेजिस्टर video4linux devices */
अटल पूर्णांक bttv_रेजिस्टर_video(काष्ठा bttv *btv)
अणु
	अगर (no_overlay > 0)
		pr_notice("Overlay support disabled\n");

	/* video */
	vdev_init(btv, &btv->video_dev, &bttv_video_ढाँचा, "video");
	btv->video_dev.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER |
				     V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	अगर (btv->tuner_type != TUNER_ABSENT)
		btv->video_dev.device_caps |= V4L2_CAP_TUNER;
	अगर (no_overlay <= 0)
		btv->video_dev.device_caps |= V4L2_CAP_VIDEO_OVERLAY;

	अगर (video_रेजिस्टर_device(&btv->video_dev, VFL_TYPE_VIDEO,
				  video_nr[btv->c.nr]) < 0)
		जाओ err;
	pr_info("%d: registered device %s\n",
		btv->c.nr, video_device_node_name(&btv->video_dev));
	अगर (device_create_file(&btv->video_dev.dev,
				     &dev_attr_card)<0) अणु
		pr_err("%d: device_create_file 'card' failed\n", btv->c.nr);
		जाओ err;
	पूर्ण

	/* vbi */
	vdev_init(btv, &btv->vbi_dev, &bttv_video_ढाँचा, "vbi");
	btv->vbi_dev.device_caps = V4L2_CAP_VBI_CAPTURE | V4L2_CAP_READWRITE |
				   V4L2_CAP_STREAMING | V4L2_CAP_TUNER;
	अगर (btv->tuner_type != TUNER_ABSENT)
		btv->vbi_dev.device_caps |= V4L2_CAP_TUNER;

	अगर (video_रेजिस्टर_device(&btv->vbi_dev, VFL_TYPE_VBI,
				  vbi_nr[btv->c.nr]) < 0)
		जाओ err;
	pr_info("%d: registered device %s\n",
		btv->c.nr, video_device_node_name(&btv->vbi_dev));

	अगर (!btv->has_radio)
		वापस 0;
	/* radio */
	vdev_init(btv, &btv->radio_dev, &radio_ढाँचा, "radio");
	btv->radio_dev.device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
	अगर (btv->has_saa6588)
		btv->radio_dev.device_caps |= V4L2_CAP_READWRITE |
					      V4L2_CAP_RDS_CAPTURE;
	अगर (btv->has_tea575x)
		btv->radio_dev.device_caps |= V4L2_CAP_HW_FREQ_SEEK;
	btv->radio_dev.ctrl_handler = &btv->radio_ctrl_handler;
	अगर (video_रेजिस्टर_device(&btv->radio_dev, VFL_TYPE_RADIO,
				  radio_nr[btv->c.nr]) < 0)
		जाओ err;
	pr_info("%d: registered device %s\n",
		btv->c.nr, video_device_node_name(&btv->radio_dev));

	/* all करोne */
	वापस 0;

 err:
	bttv_unरेजिस्टर_video(btv);
	वापस -1;
पूर्ण


/* on OpenFirmware machines (PowerMac at least), PCI memory cycle */
/* response on cards with no firmware is not enabled by OF */
अटल व्योम pci_set_command(काष्ठा pci_dev *dev)
अणु
#अगर defined(__घातerpc__)
	अचिन्हित पूर्णांक cmd;

	pci_पढ़ो_config_dword(dev, PCI_COMMAND, &cmd);
	cmd = (cmd | PCI_COMMAND_MEMORY );
	pci_ग_लिखो_config_dword(dev, PCI_COMMAND, cmd);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bttv_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा v4l2_frequency init_freq = अणु
		.tuner = 0,
		.type = V4L2_TUNER_ANALOG_TV,
		.frequency = 980,
	पूर्ण;
	पूर्णांक result;
	अचिन्हित अक्षर lat;
	काष्ठा bttv *btv;
	काष्ठा v4l2_ctrl_handler *hdl;

	अगर (bttv_num == BTTV_MAX)
		वापस -ENOMEM;
	pr_info("Bt8xx card found (%d)\n", bttv_num);
	bttvs[bttv_num] = btv = kzalloc(माप(*btv), GFP_KERNEL);
	अगर (btv == शून्य) अणु
		pr_err("out of memory\n");
		वापस -ENOMEM;
	पूर्ण
	btv->c.nr  = bttv_num;
	snम_लिखो(btv->c.v4l2_dev.name, माप(btv->c.v4l2_dev.name),
			"bttv%d", btv->c.nr);

	/* initialize काष्ठाs / fill in शेषs */
	mutex_init(&btv->lock);
	spin_lock_init(&btv->s_lock);
	spin_lock_init(&btv->gpio_lock);
	init_रुकोqueue_head(&btv->i2c_queue);
	INIT_LIST_HEAD(&btv->c.subs);
	INIT_LIST_HEAD(&btv->capture);
	INIT_LIST_HEAD(&btv->vcapture);

	समयr_setup(&btv->समयout, bttv_irq_समयout, 0);

	btv->i2c_rc = -1;
	btv->tuner_type  = UNSET;
	btv->new_input   = UNSET;
	btv->has_radio=radio[btv->c.nr];

	/* pci stuff (init, get irq/mmio, ... */
	btv->c.pci = dev;
	btv->id  = dev->device;
	अगर (pci_enable_device(dev)) अणु
		pr_warn("%d: Can't enable device\n", btv->c.nr);
		result = -EIO;
		जाओ मुक्त_mem;
	पूर्ण
	अगर (dma_set_mask(&dev->dev, DMA_BIT_MASK(32))) अणु
		pr_warn("%d: No suitable DMA available\n", btv->c.nr);
		result = -EIO;
		जाओ मुक्त_mem;
	पूर्ण
	अगर (!request_mem_region(pci_resource_start(dev,0),
				pci_resource_len(dev,0),
				btv->c.v4l2_dev.name)) अणु
		pr_warn("%d: can't request iomem (0x%llx)\n",
			btv->c.nr,
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 0));
		result = -EBUSY;
		जाओ मुक्त_mem;
	पूर्ण
	pci_set_master(dev);
	pci_set_command(dev);

	result = v4l2_device_रेजिस्टर(&dev->dev, &btv->c.v4l2_dev);
	अगर (result < 0) अणु
		pr_warn("%d: v4l2_device_register() failed\n", btv->c.nr);
		जाओ fail0;
	पूर्ण
	hdl = &btv->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 20);
	btv->c.v4l2_dev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(&btv->radio_ctrl_handler, 6);

	btv->revision = dev->revision;
	pci_पढ़ो_config_byte(dev, PCI_LATENCY_TIMER, &lat);
	pr_info("%d: Bt%d (rev %d) at %s, irq: %d, latency: %d, mmio: 0x%llx\n",
		bttv_num, btv->id, btv->revision, pci_name(dev),
		btv->c.pci->irq, lat,
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 0));
	schedule();

	btv->bt848_mmio = ioremap(pci_resource_start(dev, 0), 0x1000);
	अगर (शून्य == btv->bt848_mmio) अणु
		pr_err("%d: ioremap() failed\n", btv->c.nr);
		result = -EIO;
		जाओ fail1;
	पूर्ण

	/* identअगरy card */
	bttv_idcard(btv);

	/* disable irqs, रेजिस्टर irq handler */
	btग_लिखो(0, BT848_INT_MASK);
	result = request_irq(btv->c.pci->irq, bttv_irq,
	    IRQF_SHARED, btv->c.v4l2_dev.name, (व्योम *)btv);
	अगर (result < 0) अणु
		pr_err("%d: can't get IRQ %d\n",
		       bttv_num, btv->c.pci->irq);
		जाओ fail1;
	पूर्ण

	अगर (0 != bttv_handle_chipset(btv)) अणु
		result = -EIO;
		जाओ fail2;
	पूर्ण

	/* init options from insmod args */
	btv->opt_combfilter = combfilter;
	bttv_ctrl_combfilter.def = combfilter;
	bttv_ctrl_lumafilter.def = lumafilter;
	btv->opt_स्वतःmute   = स्वतःmute;
	bttv_ctrl_स्वतःmute.def = स्वतःmute;
	bttv_ctrl_agc_crush.def = agc_crush;
	btv->opt_vcr_hack   = vcr_hack;
	bttv_ctrl_vcr_hack.def = vcr_hack;
	bttv_ctrl_whitecrush_upper.def = whitecrush_upper;
	bttv_ctrl_whitecrush_lower.def = whitecrush_lower;
	btv->opt_uv_ratio   = uv_ratio;
	bttv_ctrl_uv_ratio.def = uv_ratio;
	bttv_ctrl_full_luma.def = full_luma_range;
	bttv_ctrl_coring.def = coring;

	/* fill काष्ठा bttv with some useful शेषs */
	btv->init.btv         = btv;
	btv->init.ov.w.width  = 320;
	btv->init.ov.w.height = 240;
	btv->init.fmt         = क्रमmat_by_fourcc(V4L2_PIX_FMT_BGR24);
	btv->init.width       = 320;
	btv->init.height      = 240;
	btv->init.ov.w.width  = 320;
	btv->init.ov.w.height = 240;
	btv->init.ov.field    = V4L2_FIELD_INTERLACED;
	btv->input = 0;

	v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 0xff00, 0x100, 32768);
	v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 0xff80, 0x80, 0x6c00);
	v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
			V4L2_CID_SATURATION, 0, 0xff80, 0x80, 32768);
	v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
			V4L2_CID_COLOR_KILLER, 0, 1, 1, 0);
	v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
			V4L2_CID_HUE, 0, 0xff00, 0x100, 32768);
	v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
			V4L2_CID_CHROMA_AGC, 0, 1, 1, !!chroma_agc);
	v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
		V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	अगर (btv->volume_gpio)
		v4l2_ctrl_new_std(hdl, &bttv_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 0xff00, 0x100, 0xff00);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_combfilter, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_स्वतःmute, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_lumafilter, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_agc_crush, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_vcr_hack, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_whitecrush_lower, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_whitecrush_upper, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_uv_ratio, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_full_luma, शून्य);
	v4l2_ctrl_new_custom(hdl, &bttv_ctrl_coring, शून्य);

	/* initialize hardware */
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv,"pre-init");

	bttv_risc_init_मुख्य(btv);
	init_bt848(btv);

	/* gpio */
	btग_लिखो(0x00, BT848_GPIO_REG_INP);
	btग_लिखो(0x00, BT848_GPIO_OUT_EN);
	अगर (bttv_verbose)
		bttv_gpio_tracking(btv,"init");

	/* needs to be करोne beक्रमe i2c is रेजिस्टरed */
	bttv_init_card1(btv);

	/* रेजिस्टर i2c + gpio */
	init_bttv_i2c(btv);

	/* some card-specअगरic stuff (needs working i2c) */
	bttv_init_card2(btv);
	bttv_init_tuner(btv);
	अगर (btv->tuner_type != TUNER_ABSENT) अणु
		bttv_set_frequency(btv, &init_freq);
		btv->radio_freq = 90500 * 16; /* 90.5Mhz शेष */
	पूर्ण
	btv->std = V4L2_STD_PAL;
	init_irqreg(btv);
	अगर (!bttv_tvcards[btv->c.type].no_video)
		v4l2_ctrl_handler_setup(hdl);
	अगर (hdl->error) अणु
		result = hdl->error;
		जाओ fail2;
	पूर्ण
	/* mute device */
	audio_mute(btv, 1);

	/* रेजिस्टर video4linux + input */
	अगर (!bttv_tvcards[btv->c.type].no_video) अणु
		v4l2_ctrl_add_handler(&btv->radio_ctrl_handler, hdl,
				v4l2_ctrl_radio_filter, false);
		अगर (btv->radio_ctrl_handler.error) अणु
			result = btv->radio_ctrl_handler.error;
			जाओ fail2;
		पूर्ण
		set_input(btv, 0, btv->tvnorm);
		bttv_crop_reset(&btv->crop[0], btv->tvnorm);
		btv->crop[1] = btv->crop[0]; /* current = शेष */
		disclaim_vbi_lines(btv);
		disclaim_video_lines(btv);
		bttv_रेजिस्टर_video(btv);
	पूर्ण

	/* add subdevices and स्वतःload dvb-bt8xx अगर needed */
	अगर (bttv_tvcards[btv->c.type].has_dvb) अणु
		bttv_sub_add_device(&btv->c, "dvb");
		request_modules(btv);
	पूर्ण

	अगर (!disable_ir) अणु
		init_bttv_i2c_ir(btv);
		bttv_input_init(btv);
	पूर्ण

	/* everything is fine */
	bttv_num++;
	वापस 0;

fail2:
	मुक्त_irq(btv->c.pci->irq,btv);

fail1:
	v4l2_ctrl_handler_मुक्त(&btv->ctrl_handler);
	v4l2_ctrl_handler_मुक्त(&btv->radio_ctrl_handler);
	v4l2_device_unरेजिस्टर(&btv->c.v4l2_dev);

fail0:
	अगर (btv->bt848_mmio)
		iounmap(btv->bt848_mmio);
	release_mem_region(pci_resource_start(btv->c.pci,0),
			   pci_resource_len(btv->c.pci,0));
	pci_disable_device(btv->c.pci);

मुक्त_mem:
	bttvs[btv->c.nr] = शून्य;
	kमुक्त(btv);
	वापस result;
पूर्ण

अटल व्योम bttv_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा bttv *btv = to_bttv(v4l2_dev);

	अगर (bttv_verbose)
		pr_info("%d: unloading\n", btv->c.nr);

	अगर (bttv_tvcards[btv->c.type].has_dvb)
		flush_request_modules(btv);

	/* shutकरोwn everything (DMA+IRQs) */
	btand(~15, BT848_GPIO_DMA_CTL);
	btग_लिखो(0, BT848_INT_MASK);
	btग_लिखो(~0x0, BT848_INT_STAT);
	btग_लिखो(0x0, BT848_GPIO_OUT_EN);
	अगर (bttv_gpio)
		bttv_gpio_tracking(btv,"cleanup");

	/* tell gpio modules we are leaving ... */
	btv->shutकरोwn=1;
	bttv_input_fini(btv);
	bttv_sub_del_devices(&btv->c);

	/* unरेजिस्टर i2c_bus + input */
	fini_bttv_i2c(btv);

	/* unरेजिस्टर video4linux */
	bttv_unरेजिस्टर_video(btv);

	/* मुक्त allocated memory */
	v4l2_ctrl_handler_मुक्त(&btv->ctrl_handler);
	v4l2_ctrl_handler_मुक्त(&btv->radio_ctrl_handler);
	btcx_riscmem_मुक्त(btv->c.pci,&btv->मुख्य);

	/* मुक्त resources */
	मुक्त_irq(btv->c.pci->irq,btv);
	iounmap(btv->bt848_mmio);
	release_mem_region(pci_resource_start(btv->c.pci,0),
			   pci_resource_len(btv->c.pci,0));
	pci_disable_device(btv->c.pci);

	v4l2_device_unरेजिस्टर(&btv->c.v4l2_dev);
	bttvs[btv->c.nr] = शून्य;
	kमुक्त(btv);

	वापस;
पूर्ण

अटल पूर्णांक __maybe_unused bttv_suspend(काष्ठा device *dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा bttv *btv = to_bttv(v4l2_dev);
	काष्ठा bttv_buffer_set idle;
	अचिन्हित दीर्घ flags;

	dprपूर्णांकk("%d: suspend\n", btv->c.nr);

	/* stop dma + irqs */
	spin_lock_irqsave(&btv->s_lock,flags);
	स_रखो(&idle, 0, माप(idle));
	btv->state.video = btv->curr;
	btv->state.vbi   = btv->cvbi;
	btv->state.loop_irq = btv->loop_irq;
	btv->curr = idle;
	btv->loop_irq = 0;
	bttv_buffer_activate_video(btv, &idle);
	bttv_buffer_activate_vbi(btv, शून्य);
	bttv_set_dma(btv, 0);
	btग_लिखो(0, BT848_INT_MASK);
	spin_unlock_irqrestore(&btv->s_lock,flags);

	/* save bt878 state */
	btv->state.gpio_enable = btपढ़ो(BT848_GPIO_OUT_EN);
	btv->state.gpio_data   = gpio_पढ़ो();

	btv->state.disabled = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bttv_resume(काष्ठा device *dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा bttv *btv = to_bttv(v4l2_dev);
	अचिन्हित दीर्घ flags;

	dprपूर्णांकk("%d: resume\n", btv->c.nr);

	btv->state.disabled = 0;

	/* restore bt878 state */
	bttv_reinit_bt848(btv);
	gpio_inout(0xffffff, btv->state.gpio_enable);
	gpio_ग_लिखो(btv->state.gpio_data);

	/* restart dma */
	spin_lock_irqsave(&btv->s_lock,flags);
	btv->curr = btv->state.video;
	btv->cvbi = btv->state.vbi;
	btv->loop_irq = btv->state.loop_irq;
	bttv_buffer_activate_video(btv, &btv->curr);
	bttv_buffer_activate_vbi(btv, btv->cvbi);
	bttv_set_dma(btv, 0);
	spin_unlock_irqrestore(&btv->s_lock,flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id bttv_pci_tbl[] = अणु
	अणुPCI_VDEVICE(BROOKTREE, PCI_DEVICE_ID_BT848), 0पूर्ण,
	अणुPCI_VDEVICE(BROOKTREE, PCI_DEVICE_ID_BT849), 0पूर्ण,
	अणुPCI_VDEVICE(BROOKTREE, PCI_DEVICE_ID_BT878), 0पूर्ण,
	अणुPCI_VDEVICE(BROOKTREE, PCI_DEVICE_ID_BT879), 0पूर्ण,
	अणुPCI_VDEVICE(BROOKTREE, PCI_DEVICE_ID_FUSION879), 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, bttv_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(bttv_pm_ops,
			 bttv_suspend,
			 bttv_resume);

अटल काष्ठा pci_driver bttv_pci_driver = अणु
	.name      = "bttv",
	.id_table  = bttv_pci_tbl,
	.probe     = bttv_probe,
	.हटाओ    = bttv_हटाओ,
	.driver.pm = &bttv_pm_ops,
पूर्ण;

अटल पूर्णांक __init bttv_init_module(व्योम)
अणु
	पूर्णांक ret;

	bttv_num = 0;

	pr_info("driver version %s loaded\n", BTTV_VERSION);
	अगर (gbuffers < 2 || gbuffers > VIDEO_MAX_FRAME)
		gbuffers = 2;
	अगर (gbufsize > BTTV_MAX_FBUF)
		gbufsize = BTTV_MAX_FBUF;
	gbufsize = (gbufsize + PAGE_SIZE - 1) & PAGE_MASK;
	अगर (bttv_verbose)
		pr_info("using %d buffers with %dk (%d pages) each for capture\n",
			gbuffers, gbufsize >> 10, gbufsize >> PAGE_SHIFT);

	bttv_check_chipset();

	ret = bus_रेजिस्टर(&bttv_sub_bus_type);
	अगर (ret < 0) अणु
		pr_warn("bus_register error: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = pci_रेजिस्टर_driver(&bttv_pci_driver);
	अगर (ret < 0)
		bus_unरेजिस्टर(&bttv_sub_bus_type);

	वापस ret;
पूर्ण

अटल व्योम __निकास bttv_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bttv_pci_driver);
	bus_unरेजिस्टर(&bttv_sub_bus_type);
पूर्ण

module_init(bttv_init_module);
module_निकास(bttv_cleanup_module);
