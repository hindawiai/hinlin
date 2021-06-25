<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPCA506 chip based cameras function
 * M Xhaard 15/04/2004 based on dअगरferent work Mark Taylor and others
 * and my own snoopy file on a pv-321c करोnate by a german compagny
 *                "Firma Frank Gmbh" from  Saarbruecken
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

#घोषणा MODULE_NAME "spca506"

#समावेश "gspca.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("GSPCA/SPCA506 USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	अक्षर norme;
	अक्षर channel;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु160, 120, V4L2_PIX_FMT_SPCA505, V4L2_FIELD_NONE,
		.bytesperline = 160,
		.sizeimage = 160 * 120 * 3 / 2,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 5पूर्ण,
	अणु176, 144, V4L2_PIX_FMT_SPCA505, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 2,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 4पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_SPCA505, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 2,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 2पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_SPCA505, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 2,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_SPCA505, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 2,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

#घोषणा SPCA50X_OFFSET_DATA 10

#घोषणा SAA7113_bright 0x0a	/* शेषs 0x80 */
#घोषणा SAA7113_contrast 0x0b	/* शेषs 0x47 */
#घोषणा SAA7113_saturation 0x0c	/* शेषs 0x40 */
#घोषणा SAA7113_hue 0x0d	/* शेषs 0x00 */
#घोषणा SAA7113_I2C_BASE_WRITE 0x4a

/* पढ़ो 'len' bytes to gspca_dev->usb_buf */
अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev,
		  __u16 req,
		  __u16 index,
		  __u16 length)
अणु
	usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			req,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,		/* value */
			index, gspca_dev->usb_buf, length,
			500);
पूर्ण

अटल व्योम reg_w(काष्ठा usb_device *dev,
		  __u16 req,
		  __u16 value,
		  __u16 index)
अणु
	usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index,
			शून्य, 0, 500);
पूर्ण

अटल व्योम spca506_Initi2c(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w(gspca_dev->dev, 0x07, SAA7113_I2C_BASE_WRITE, 0x0004);
पूर्ण

अटल व्योम spca506_WriteI2c(काष्ठा gspca_dev *gspca_dev, __u16 valeur,
			     __u16 reg)
अणु
	पूर्णांक retry = 60;

	reg_w(gspca_dev->dev, 0x07, reg, 0x0001);
	reg_w(gspca_dev->dev, 0x07, valeur, 0x0000);
	जबतक (retry--) अणु
		reg_r(gspca_dev, 0x07, 0x0003, 2);
		अगर ((gspca_dev->usb_buf[0] | gspca_dev->usb_buf[1]) == 0x00)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम spca506_SetNormeInput(काष्ठा gspca_dev *gspca_dev,
				 __u16 norme,
				 __u16 channel)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
/* fixme: check अगर channel == 0..3 and 6..9 (8 values) */
	__u8 setbit0 = 0x00;
	__u8 setbit1 = 0x00;
	__u8 videomask = 0x00;

	gspca_dbg(gspca_dev, D_STREAM, "** Open Set Norme **\n");
	spca506_Initi2c(gspca_dev);
	/* NTSC bit0 -> 1(525 l) PAL SECAM bit0 -> 0 (625 l) */
	/* Composite channel bit1 -> 1 S-video bit 1 -> 0 */
	/* and exclude SAA7113 reserved channel set शेष 0 otherwise */
	अगर (norme & V4L2_STD_NTSC)
		setbit0 = 0x01;
	अगर (channel == 4 || channel == 5 || channel > 9)
		channel = 0;
	अगर (channel < 4)
		setbit1 = 0x02;
	videomask = (0x48 | setbit0 | setbit1);
	reg_w(gspca_dev->dev, 0x08, videomask, 0x0000);
	spca506_WriteI2c(gspca_dev, (0xc0 | (channel & 0x0F)), 0x02);

	अगर (norme & V4L2_STD_NTSC)
		spca506_WriteI2c(gspca_dev, 0x33, 0x0e);
					/* Chrominance Control NTSC N */
	अन्यथा अगर (norme & V4L2_STD_SECAM)
		spca506_WriteI2c(gspca_dev, 0x53, 0x0e);
					/* Chrominance Control SECAM */
	अन्यथा
		spca506_WriteI2c(gspca_dev, 0x03, 0x0e);
					/* Chrominance Control PAL BGHIV */

	sd->norme = norme;
	sd->channel = channel;
	gspca_dbg(gspca_dev, D_STREAM, "Set Video Byte to 0x%2x\n", videomask);
	gspca_dbg(gspca_dev, D_STREAM, "Set Norme: %08x Channel %d",
		  norme, channel);
पूर्ण

अटल व्योम spca506_GetNormeInput(काष्ठा gspca_dev *gspca_dev,
				  __u16 *norme, __u16 *channel)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* Read the रेजिस्टर is not so good value change so
	   we use your own copy in spca50x काष्ठा */
	*norme = sd->norme;
	*channel = sd->channel;
	gspca_dbg(gspca_dev, D_STREAM, "Get Norme: %d Channel %d\n",
		  *norme, *channel);
पूर्ण

अटल व्योम spca506_Setsize(काष्ठा gspca_dev *gspca_dev, __u16 code,
			    __u16 xmult, __u16 ymult)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	gspca_dbg(gspca_dev, D_STREAM, "** SetSize **\n");
	reg_w(dev, 0x04, (0x18 | (code & 0x07)), 0x0000);
	/* Soft snap 0x40 Hard 0x41 */
	reg_w(dev, 0x04, 0x41, 0x0001);
	reg_w(dev, 0x04, 0x00, 0x0002);
	/* reserved */
	reg_w(dev, 0x04, 0x00, 0x0003);

	/* reserved */
	reg_w(dev, 0x04, 0x00, 0x0004);
	/* reserved */
	reg_w(dev, 0x04, 0x01, 0x0005);
	/* reserced */
	reg_w(dev, 0x04, xmult, 0x0006);
	/* reserved */
	reg_w(dev, 0x04, ymult, 0x0007);
	/* compression 1 */
	reg_w(dev, 0x04, 0x00, 0x0008);
	/* T=64 -> 2 */
	reg_w(dev, 0x04, 0x00, 0x0009);
	/* threshold2D */
	reg_w(dev, 0x04, 0x21, 0x000a);
	/* quantization */
	reg_w(dev, 0x04, 0x00, 0x000b);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0xFF, 0x0003);
	reg_w(dev, 0x03, 0x00, 0x0000);
	reg_w(dev, 0x03, 0x1c, 0x0001);
	reg_w(dev, 0x03, 0x18, 0x0001);
	/* Init on PAL and composite input0 */
	spca506_SetNormeInput(gspca_dev, 0, 0);
	reg_w(dev, 0x03, 0x1c, 0x0001);
	reg_w(dev, 0x03, 0x18, 0x0001);
	reg_w(dev, 0x05, 0x00, 0x0000);
	reg_w(dev, 0x05, 0xef, 0x0001);
	reg_w(dev, 0x05, 0x00, 0x00c1);
	reg_w(dev, 0x05, 0x00, 0x00c2);
	reg_w(dev, 0x06, 0x18, 0x0002);
	reg_w(dev, 0x06, 0xf5, 0x0011);
	reg_w(dev, 0x06, 0x02, 0x0012);
	reg_w(dev, 0x06, 0xfb, 0x0013);
	reg_w(dev, 0x06, 0x00, 0x0014);
	reg_w(dev, 0x06, 0xa4, 0x0051);
	reg_w(dev, 0x06, 0x40, 0x0052);
	reg_w(dev, 0x06, 0x71, 0x0053);
	reg_w(dev, 0x06, 0x40, 0x0054);
	/************************************************/
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0x00, 0x0003);
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0xFF, 0x0003);
	reg_w(dev, 0x02, 0x00, 0x0000);
	reg_w(dev, 0x03, 0x60, 0x0000);
	reg_w(dev, 0x03, 0x18, 0x0001);
	/* क्रम a better पढ़ोing mx :)	  */
	/*sdca506_WriteI2c(value,रेजिस्टर) */
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, 0x08, 0x01);
	spca506_WriteI2c(gspca_dev, 0xc0, 0x02);
						/* input composite video */
	spca506_WriteI2c(gspca_dev, 0x33, 0x03);
	spca506_WriteI2c(gspca_dev, 0x00, 0x04);
	spca506_WriteI2c(gspca_dev, 0x00, 0x05);
	spca506_WriteI2c(gspca_dev, 0x0d, 0x06);
	spca506_WriteI2c(gspca_dev, 0xf0, 0x07);
	spca506_WriteI2c(gspca_dev, 0x98, 0x08);
	spca506_WriteI2c(gspca_dev, 0x03, 0x09);
	spca506_WriteI2c(gspca_dev, 0x80, 0x0a);
	spca506_WriteI2c(gspca_dev, 0x47, 0x0b);
	spca506_WriteI2c(gspca_dev, 0x48, 0x0c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x0d);
	spca506_WriteI2c(gspca_dev, 0x03, 0x0e);	/* Chroma Pal adjust */
	spca506_WriteI2c(gspca_dev, 0x2a, 0x0f);
	spca506_WriteI2c(gspca_dev, 0x00, 0x10);
	spca506_WriteI2c(gspca_dev, 0x0c, 0x11);
	spca506_WriteI2c(gspca_dev, 0xb8, 0x12);
	spca506_WriteI2c(gspca_dev, 0x01, 0x13);
	spca506_WriteI2c(gspca_dev, 0x00, 0x14);
	spca506_WriteI2c(gspca_dev, 0x00, 0x15);
	spca506_WriteI2c(gspca_dev, 0x00, 0x16);
	spca506_WriteI2c(gspca_dev, 0x00, 0x17);
	spca506_WriteI2c(gspca_dev, 0x00, 0x18);
	spca506_WriteI2c(gspca_dev, 0x00, 0x19);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1a);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1b);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1d);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1e);
	spca506_WriteI2c(gspca_dev, 0xa1, 0x1f);
	spca506_WriteI2c(gspca_dev, 0x02, 0x40);
	spca506_WriteI2c(gspca_dev, 0xff, 0x41);
	spca506_WriteI2c(gspca_dev, 0xff, 0x42);
	spca506_WriteI2c(gspca_dev, 0xff, 0x43);
	spca506_WriteI2c(gspca_dev, 0xff, 0x44);
	spca506_WriteI2c(gspca_dev, 0xff, 0x45);
	spca506_WriteI2c(gspca_dev, 0xff, 0x46);
	spca506_WriteI2c(gspca_dev, 0xff, 0x47);
	spca506_WriteI2c(gspca_dev, 0xff, 0x48);
	spca506_WriteI2c(gspca_dev, 0xff, 0x49);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4a);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4b);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4c);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4d);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4e);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4f);
	spca506_WriteI2c(gspca_dev, 0xff, 0x50);
	spca506_WriteI2c(gspca_dev, 0xff, 0x51);
	spca506_WriteI2c(gspca_dev, 0xff, 0x52);
	spca506_WriteI2c(gspca_dev, 0xff, 0x53);
	spca506_WriteI2c(gspca_dev, 0xff, 0x54);
	spca506_WriteI2c(gspca_dev, 0xff, 0x55);
	spca506_WriteI2c(gspca_dev, 0xff, 0x56);
	spca506_WriteI2c(gspca_dev, 0xff, 0x57);
	spca506_WriteI2c(gspca_dev, 0x00, 0x58);
	spca506_WriteI2c(gspca_dev, 0x54, 0x59);
	spca506_WriteI2c(gspca_dev, 0x07, 0x5a);
	spca506_WriteI2c(gspca_dev, 0x83, 0x5b);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5d);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5e);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5f);
	spca506_WriteI2c(gspca_dev, 0x00, 0x60);
	spca506_WriteI2c(gspca_dev, 0x05, 0x61);
	spca506_WriteI2c(gspca_dev, 0x9f, 0x62);
	gspca_dbg(gspca_dev, D_STREAM, "** Close Init *\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	__u16 norme;
	__u16 channel;

	/**************************************/
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0x00, 0x0003);
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0xFF, 0x0003);
	reg_w(dev, 0x02, 0x00, 0x0000);
	reg_w(dev, 0x03, 0x60, 0x0000);
	reg_w(dev, 0x03, 0x18, 0x0001);

	/*sdca506_WriteI2c(value,रेजिस्टर) */
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, 0x08, 0x01);	/* Increment Delay */
/*	spca506_WriteI2c(gspca_dev, 0xc0, 0x02); * Analog Input Control 1 */
	spca506_WriteI2c(gspca_dev, 0x33, 0x03);
						/* Analog Input Control 2 */
	spca506_WriteI2c(gspca_dev, 0x00, 0x04);
						/* Analog Input Control 3 */
	spca506_WriteI2c(gspca_dev, 0x00, 0x05);
						/* Analog Input Control 4 */
	spca506_WriteI2c(gspca_dev, 0x0d, 0x06);
					/* Horizontal Sync Start 0xe9-0x0d */
	spca506_WriteI2c(gspca_dev, 0xf0, 0x07);
					/* Horizontal Sync Stop  0x0d-0xf0 */

	spca506_WriteI2c(gspca_dev, 0x98, 0x08);	/* Sync Control */
/*		Defaults value			*/
	spca506_WriteI2c(gspca_dev, 0x03, 0x09);	/* Luminance Control */
	spca506_WriteI2c(gspca_dev, 0x80, 0x0a);
						/* Luminance Brightness */
	spca506_WriteI2c(gspca_dev, 0x47, 0x0b);	/* Luminance Contrast */
	spca506_WriteI2c(gspca_dev, 0x48, 0x0c);
						/* Chrominance Saturation */
	spca506_WriteI2c(gspca_dev, 0x00, 0x0d);
						/* Chrominance Hue Control */
	spca506_WriteI2c(gspca_dev, 0x2a, 0x0f);
						/* Chrominance Gain Control */
	/**************************************/
	spca506_WriteI2c(gspca_dev, 0x00, 0x10);
						/* Format/Delay Control */
	spca506_WriteI2c(gspca_dev, 0x0c, 0x11);	/* Output Control 1 */
	spca506_WriteI2c(gspca_dev, 0xb8, 0x12);	/* Output Control 2 */
	spca506_WriteI2c(gspca_dev, 0x01, 0x13);	/* Output Control 3 */
	spca506_WriteI2c(gspca_dev, 0x00, 0x14);	/* reserved */
	spca506_WriteI2c(gspca_dev, 0x00, 0x15);	/* VGATE START */
	spca506_WriteI2c(gspca_dev, 0x00, 0x16);	/* VGATE STOP */
	spca506_WriteI2c(gspca_dev, 0x00, 0x17);    /* VGATE Control (MSB) */
	spca506_WriteI2c(gspca_dev, 0x00, 0x18);
	spca506_WriteI2c(gspca_dev, 0x00, 0x19);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1a);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1b);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1d);
	spca506_WriteI2c(gspca_dev, 0x00, 0x1e);
	spca506_WriteI2c(gspca_dev, 0xa1, 0x1f);
	spca506_WriteI2c(gspca_dev, 0x02, 0x40);
	spca506_WriteI2c(gspca_dev, 0xff, 0x41);
	spca506_WriteI2c(gspca_dev, 0xff, 0x42);
	spca506_WriteI2c(gspca_dev, 0xff, 0x43);
	spca506_WriteI2c(gspca_dev, 0xff, 0x44);
	spca506_WriteI2c(gspca_dev, 0xff, 0x45);
	spca506_WriteI2c(gspca_dev, 0xff, 0x46);
	spca506_WriteI2c(gspca_dev, 0xff, 0x47);
	spca506_WriteI2c(gspca_dev, 0xff, 0x48);
	spca506_WriteI2c(gspca_dev, 0xff, 0x49);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4a);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4b);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4c);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4d);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4e);
	spca506_WriteI2c(gspca_dev, 0xff, 0x4f);
	spca506_WriteI2c(gspca_dev, 0xff, 0x50);
	spca506_WriteI2c(gspca_dev, 0xff, 0x51);
	spca506_WriteI2c(gspca_dev, 0xff, 0x52);
	spca506_WriteI2c(gspca_dev, 0xff, 0x53);
	spca506_WriteI2c(gspca_dev, 0xff, 0x54);
	spca506_WriteI2c(gspca_dev, 0xff, 0x55);
	spca506_WriteI2c(gspca_dev, 0xff, 0x56);
	spca506_WriteI2c(gspca_dev, 0xff, 0x57);
	spca506_WriteI2c(gspca_dev, 0x00, 0x58);
	spca506_WriteI2c(gspca_dev, 0x54, 0x59);
	spca506_WriteI2c(gspca_dev, 0x07, 0x5a);
	spca506_WriteI2c(gspca_dev, 0x83, 0x5b);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5c);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5d);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5e);
	spca506_WriteI2c(gspca_dev, 0x00, 0x5f);
	spca506_WriteI2c(gspca_dev, 0x00, 0x60);
	spca506_WriteI2c(gspca_dev, 0x05, 0x61);
	spca506_WriteI2c(gspca_dev, 0x9f, 0x62);
	/**************************************/
	reg_w(dev, 0x05, 0x00, 0x0003);
	reg_w(dev, 0x05, 0x00, 0x0004);
	reg_w(dev, 0x03, 0x10, 0x0001);
	reg_w(dev, 0x03, 0x78, 0x0000);
	चयन (gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv) अणु
	हाल 0:
		spca506_Setsize(gspca_dev, 0, 0x10, 0x10);
		अवरोध;
	हाल 1:
		spca506_Setsize(gspca_dev, 1, 0x1a, 0x1a);
		अवरोध;
	हाल 2:
		spca506_Setsize(gspca_dev, 2, 0x1c, 0x1c);
		अवरोध;
	हाल 4:
		spca506_Setsize(gspca_dev, 4, 0x34, 0x34);
		अवरोध;
	शेष:
/*	हाल 5: */
		spca506_Setsize(gspca_dev, 5, 0x40, 0x40);
		अवरोध;
	पूर्ण

	/* compress setting and size */
	/* set i2c luma */
	reg_w(dev, 0x02, 0x01, 0x0000);
	reg_w(dev, 0x03, 0x12, 0x0000);
	reg_r(gspca_dev, 0x04, 0x0001, 2);
	gspca_dbg(gspca_dev, D_STREAM, "webcam started\n");
	spca506_GetNormeInput(gspca_dev, &norme, &channel);
	spca506_SetNormeInput(gspca_dev, norme, channel);
	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;

	reg_w(dev, 0x02, 0x00, 0x0000);
	reg_w(dev, 0x03, 0x00, 0x0004);
	reg_w(dev, 0x03, 0x00, 0x0003);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	चयन (data[0]) अणु
	हाल 0:				/* start of frame */
		gspca_frame_add(gspca_dev, LAST_PACKET, शून्य, 0);
		data += SPCA50X_OFFSET_DATA;
		len -= SPCA50X_OFFSET_DATA;
		gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		अवरोध;
	हाल 0xff:			/* drop */
/*		gspca_dev->last_packet_type = DISCARD_PACKET; */
		अवरोध;
	शेष:
		data += 1;
		len -= 1;
		gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, val, SAA7113_bright);
	spca506_WriteI2c(gspca_dev, 0x01, 0x09);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, val, SAA7113_contrast);
	spca506_WriteI2c(gspca_dev, 0x01, 0x09);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, val, SAA7113_saturation);
	spca506_WriteI2c(gspca_dev, 0x01, 0x09);
पूर्ण

अटल व्योम sethue(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	spca506_Initi2c(gspca_dev);
	spca506_WriteI2c(gspca_dev, val, SAA7113_hue);
	spca506_WriteI2c(gspca_dev, 0x01, 0x09);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		setbrightness(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		setcontrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolors(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_HUE:
		sethue(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 0x47);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 0x40);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_HUE, 0, 255, 1, 0);

	अगर (hdl->error) अणु
		pr_err("Could not initialize controls\n");
		वापस hdl->error;
	पूर्ण
	वापस 0;
पूर्ण

/* sub-driver description */
अटल स्थिर काष्ठा sd_desc sd_desc = अणु
	.name = MODULE_NAME,
	.config = sd_config,
	.init = sd_init,
	.init_controls = sd_init_controls,
	.start = sd_start,
	.stopN = sd_stopN,
	.pkt_scan = sd_pkt_scan,
पूर्ण;

/* -- module initialisation -- */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x06e1, 0xa190)पूर्ण,
/*	अणुUSB_DEVICE(0x0733, 0x0430)पूर्ण, FIXME: may be IntelPCCameraPro BRIDGE_SPCA505 */
	अणुUSB_DEVICE(0x0734, 0x043b)पूर्ण,
	अणुUSB_DEVICE(0x99fa, 0x8988)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

/* -- device connect -- */
अटल पूर्णांक sd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
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
