<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *		Sunplus spca504(abc) spca533 spca536 library
 *		Copyright (C) 2005 Michel Xhaard mxhaard@magic.fr
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "sunplus"

#समावेश "gspca.h"
#समावेश "jpeg.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("GSPCA/SPCA5xx USB Camera Driver");
MODULE_LICENSE("GPL");

#घोषणा QUALITY 85

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	bool स्वतःgain;

	u8 bridge;
#घोषणा BRIDGE_SPCA504 0
#घोषणा BRIDGE_SPCA504B 1
#घोषणा BRIDGE_SPCA504C 2
#घोषणा BRIDGE_SPCA533 3
#घोषणा BRIDGE_SPCA536 4
	u8 subtype;
#घोषणा AiptekMiniPenCam13 1
#घोषणा LogitechClickSmart420 2
#घोषणा LogitechClickSmart820 3
#घोषणा MegapixV4 4
#घोषणा MegaImageVI 5

	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat custom_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु464, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 464,
		.sizeimage = 464 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode2[] = अणु
	अणु176, 144, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 4पूर्ण,
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 3पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 2पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
पूर्ण;

#घोषणा SPCA50X_OFFSET_DATA 10
#घोषणा SPCA504_PCCAM600_OFFSET_SNAPSHOT 3
#घोषणा SPCA504_PCCAM600_OFFSET_COMPRESS 4
#घोषणा SPCA504_PCCAM600_OFFSET_MODE	 5
#घोषणा SPCA504_PCCAM600_OFFSET_DATA	 14
 /* Frame packet header offsets क्रम the spca533 */
#घोषणा SPCA533_OFFSET_DATA	16
#घोषणा SPCA533_OFFSET_FRAMSEQ	15
/* Frame packet header offsets क्रम the spca536 */
#घोषणा SPCA536_OFFSET_DATA	4
#घोषणा SPCA536_OFFSET_FRAMSEQ	1

काष्ठा cmd अणु
	u8 req;
	u16 val;
	u16 idx;
पूर्ण;

/* Initialisation data क्रम the Creative PC-CAM 600 */
अटल स्थिर काष्ठा cmd spca504_pccam600_init_data[] = अणु
/*	अणु0xa0, 0x0000, 0x0503पूर्ण,  * capture mode */
	अणु0x00, 0x0000, 0x2000पूर्ण,
	अणु0x00, 0x0013, 0x2301पूर्ण,
	अणु0x00, 0x0003, 0x2000पूर्ण,
	अणु0x00, 0x0001, 0x21acपूर्ण,
	अणु0x00, 0x0001, 0x21a6पूर्ण,
	अणु0x00, 0x0000, 0x21a7पूर्ण,	/* brightness */
	अणु0x00, 0x0020, 0x21a8पूर्ण,	/* contrast */
	अणु0x00, 0x0001, 0x21acपूर्ण,	/* sat/hue */
	अणु0x00, 0x0000, 0x21adपूर्ण,	/* hue */
	अणु0x00, 0x001a, 0x21aeपूर्ण,	/* saturation */
	अणु0x00, 0x0002, 0x21a3पूर्ण,	/* gamma */
	अणु0x30, 0x0154, 0x0008पूर्ण,
	अणु0x30, 0x0004, 0x0006पूर्ण,
	अणु0x30, 0x0258, 0x0009पूर्ण,
	अणु0x30, 0x0004, 0x0000पूर्ण,
	अणु0x30, 0x0093, 0x0004पूर्ण,
	अणु0x30, 0x0066, 0x0005पूर्ण,
	अणु0x00, 0x0000, 0x2000पूर्ण,
	अणु0x00, 0x0013, 0x2301पूर्ण,
	अणु0x00, 0x0003, 0x2000पूर्ण,
	अणु0x00, 0x0013, 0x2301पूर्ण,
	अणु0x00, 0x0003, 0x2000पूर्ण,
पूर्ण;

/* Creative PC-CAM 600 specअगरic खोलो data, sent beक्रमe using the
 * generic initialisation data from spca504_खोलो_data.
 */
अटल स्थिर काष्ठा cmd spca504_pccam600_खोलो_data[] = अणु
	अणु0x00, 0x0001, 0x2501पूर्ण,
	अणु0x20, 0x0500, 0x0001पूर्ण,	/* snapshot mode */
	अणु0x00, 0x0003, 0x2880पूर्ण,
	अणु0x00, 0x0001, 0x2881पूर्ण,
पूर्ण;

/* Initialisation data क्रम the logitech clicksmart 420 */
अटल स्थिर काष्ठा cmd spca504A_clicksmart420_init_data[] = अणु
/*	अणु0xa0, 0x0000, 0x0503पूर्ण,  * capture mode */
	अणु0x00, 0x0000, 0x2000पूर्ण,
	अणु0x00, 0x0013, 0x2301पूर्ण,
	अणु0x00, 0x0003, 0x2000पूर्ण,
	अणु0x00, 0x0001, 0x21acपूर्ण,
	अणु0x00, 0x0001, 0x21a6पूर्ण,
	अणु0x00, 0x0000, 0x21a7पूर्ण,	/* brightness */
	अणु0x00, 0x0020, 0x21a8पूर्ण,	/* contrast */
	अणु0x00, 0x0001, 0x21acपूर्ण,	/* sat/hue */
	अणु0x00, 0x0000, 0x21adपूर्ण,	/* hue */
	अणु0x00, 0x001a, 0x21aeपूर्ण,	/* saturation */
	अणु0x00, 0x0002, 0x21a3पूर्ण,	/* gamma */
	अणु0x30, 0x0004, 0x000aपूर्ण,
	अणु0xb0, 0x0001, 0x0000पूर्ण,

	अणु0xa1, 0x0080, 0x0001पूर्ण,
	अणु0x30, 0x0049, 0x0000पूर्ण,
	अणु0x30, 0x0060, 0x0005पूर्ण,
	अणु0x0c, 0x0004, 0x0000पूर्ण,
	अणु0x00, 0x0000, 0x0000पूर्ण,
	अणु0x00, 0x0000, 0x2000पूर्ण,
	अणु0x00, 0x0013, 0x2301पूर्ण,
	अणु0x00, 0x0003, 0x2000पूर्ण,
पूर्ण;

/* clicksmart 420 खोलो data ? */
अटल स्थिर काष्ठा cmd spca504A_clicksmart420_खोलो_data[] = अणु
	अणु0x00, 0x0001, 0x2501पूर्ण,
	अणु0x20, 0x0502, 0x0000पूर्ण,
	अणु0x06, 0x0000, 0x0000पूर्ण,
	अणु0x00, 0x0004, 0x2880पूर्ण,
	अणु0x00, 0x0001, 0x2881पूर्ण,

	अणु0xa0, 0x0000, 0x0503पूर्ण,
पूर्ण;

अटल स्थिर u8 qtable_creative_pccam[2][64] = अणु
	अणु				/* Q-table Y-components */
	 0x05, 0x03, 0x03, 0x05, 0x07, 0x0c, 0x0f, 0x12,
	 0x04, 0x04, 0x04, 0x06, 0x08, 0x11, 0x12, 0x11,
	 0x04, 0x04, 0x05, 0x07, 0x0c, 0x11, 0x15, 0x11,
	 0x04, 0x05, 0x07, 0x09, 0x0f, 0x1a, 0x18, 0x13,
	 0x05, 0x07, 0x0b, 0x11, 0x14, 0x21, 0x1f, 0x17,
	 0x07, 0x0b, 0x11, 0x13, 0x18, 0x1f, 0x22, 0x1c,
	 0x0f, 0x13, 0x17, 0x1a, 0x1f, 0x24, 0x24, 0x1e,
	 0x16, 0x1c, 0x1d, 0x1d, 0x22, 0x1e, 0x1f, 0x1eपूर्ण,
	अणु				/* Q-table C-components */
	 0x05, 0x05, 0x07, 0x0e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x05, 0x06, 0x08, 0x14, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x07, 0x08, 0x11, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x0e, 0x14, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1eपूर्ण
पूर्ण;

/* FIXME: This Q-table is identical to the Creative PC-CAM one,
 *		except क्रम one byte. Possibly a typo?
 *		NWG: 18/05/2003.
 */
अटल स्थिर u8 qtable_spca504_शेष[2][64] = अणु
	अणु				/* Q-table Y-components */
	 0x05, 0x03, 0x03, 0x05, 0x07, 0x0c, 0x0f, 0x12,
	 0x04, 0x04, 0x04, 0x06, 0x08, 0x11, 0x12, 0x11,
	 0x04, 0x04, 0x05, 0x07, 0x0c, 0x11, 0x15, 0x11,
	 0x04, 0x05, 0x07, 0x09, 0x0f, 0x1a, 0x18, 0x13,
	 0x05, 0x07, 0x0b, 0x11, 0x14, 0x21, 0x1f, 0x17,
	 0x07, 0x0b, 0x11, 0x13, 0x18, 0x1f, 0x22, 0x1c,
	 0x0f, 0x13, 0x17, 0x1a, 0x1f, 0x24, 0x24, 0x1e,
	 0x16, 0x1c, 0x1d, 0x1d, 0x1d /* 0x22 */ , 0x1e, 0x1f, 0x1e,
	 पूर्ण,
	अणु				/* Q-table C-components */
	 0x05, 0x05, 0x07, 0x0e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x05, 0x06, 0x08, 0x14, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x07, 0x08, 0x11, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x0e, 0x14, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1eपूर्ण
पूर्ण;

/* पढ़ो <len> bytes to gspca_dev->usb_buf */
अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev,
		  u8 req,
		  u16 index,
		  u16 len)
अणु
	पूर्णांक ret;

	अगर (len > USB_BUF_SZ) अणु
		gspca_err(gspca_dev, "reg_r: buffer overflow\n");
		वापस;
	पूर्ण
	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			req,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,		/* value */
			index,
			len ? gspca_dev->usb_buf : शून्य, len,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_r err %d\n", ret);
		gspca_dev->usb_err = ret;
		/*
		 * Make sure the buffer is zeroed to aव्योम uninitialized
		 * values.
		 */
		स_रखो(gspca_dev->usb_buf, 0, USB_BUF_SZ);
	पूर्ण
पूर्ण

/* ग_लिखो one byte */
अटल व्योम reg_w_1(काष्ठा gspca_dev *gspca_dev,
		   u8 req,
		   u16 value,
		   u16 index,
		   u16 byte)
अणु
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dev->usb_buf[0] = byte;
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index,
			gspca_dev->usb_buf, 1,
			500);
	अगर (ret < 0) अणु
		pr_err("reg_w_1 err %d\n", ret);
		gspca_dev->usb_err = ret;
	पूर्ण
पूर्ण

/* ग_लिखो req / index / value */
अटल व्योम reg_w_riv(काष्ठा gspca_dev *gspca_dev,
		     u8 req, u16 index, u16 value)
अणु
	काष्ठा usb_device *dev = gspca_dev->dev;
	पूर्णांक ret;

	अगर (gspca_dev->usb_err < 0)
		वापस;
	ret = usb_control_msg(dev,
			usb_sndctrlpipe(dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, शून्य, 0, 500);
	अगर (ret < 0) अणु
		pr_err("reg_w_riv err %d\n", ret);
		gspca_dev->usb_err = ret;
		वापस;
	पूर्ण
	gspca_dbg(gspca_dev, D_USBO, "reg_w_riv: 0x%02x,0x%04x:0x%04x\n",
		  req, index, value);
पूर्ण

अटल व्योम ग_लिखो_vector(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा cmd *data, पूर्णांक ncmds)
अणु
	जबतक (--ncmds >= 0) अणु
		reg_w_riv(gspca_dev, data->req, data->idx, data->val);
		data++;
	पूर्ण
पूर्ण

अटल व्योम setup_qtable(काष्ठा gspca_dev *gspca_dev,
			स्थिर u8 qtable[2][64])
अणु
	पूर्णांक i;

	/* loop over y components */
	क्रम (i = 0; i < 64; i++)
		reg_w_riv(gspca_dev, 0x00, 0x2800 + i, qtable[0][i]);

	/* loop over c components */
	क्रम (i = 0; i < 64; i++)
		reg_w_riv(gspca_dev, 0x00, 0x2840 + i, qtable[1][i]);
पूर्ण

अटल व्योम spca504_acknowledged_command(काष्ठा gspca_dev *gspca_dev,
			     u8 req, u16 idx, u16 val)
अणु
	reg_w_riv(gspca_dev, req, idx, val);
	reg_r(gspca_dev, 0x01, 0x0001, 1);
	gspca_dbg(gspca_dev, D_FRAM, "before wait 0x%04x\n",
		  gspca_dev->usb_buf[0]);
	reg_w_riv(gspca_dev, req, idx, val);

	msleep(200);
	reg_r(gspca_dev, 0x01, 0x0001, 1);
	gspca_dbg(gspca_dev, D_FRAM, "after wait 0x%04x\n",
		  gspca_dev->usb_buf[0]);
पूर्ण

अटल व्योम spca504_पढ़ो_info(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;
	u8 info[6];

	अगर (gspca_debug < D_STREAM)
		वापस;

	क्रम (i = 0; i < 6; i++) अणु
		reg_r(gspca_dev, 0, i, 1);
		info[i] = gspca_dev->usb_buf[0];
	पूर्ण
	gspca_dbg(gspca_dev, D_STREAM,
		  "Read info: %d %d %d %d %d %d. Should be 1,0,2,2,0,0\n",
		  info[0], info[1], info[2],
		  info[3], info[4], info[5]);
पूर्ण

अटल व्योम spca504A_acknowledged_command(काष्ठा gspca_dev *gspca_dev,
			u8 req,
			u16 idx, u16 val, u8 endcode, u8 count)
अणु
	u16 status;

	reg_w_riv(gspca_dev, req, idx, val);
	reg_r(gspca_dev, 0x01, 0x0001, 1);
	अगर (gspca_dev->usb_err < 0)
		वापस;
	gspca_dbg(gspca_dev, D_FRAM, "Status 0x%02x Need 0x%02x\n",
		  gspca_dev->usb_buf[0], endcode);
	अगर (!count)
		वापस;
	count = 200;
	जबतक (--count > 0) अणु
		msleep(10);
		/* gsmart mini2 ग_लिखो a each रुको setting 1 ms is enough */
/*		reg_w_riv(gspca_dev, req, idx, val); */
		reg_r(gspca_dev, 0x01, 0x0001, 1);
		status = gspca_dev->usb_buf[0];
		अगर (status == endcode) अणु
			gspca_dbg(gspca_dev, D_FRAM, "status 0x%04x after wait %d\n",
				  status, 200 - count);
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम spca504B_PollingDataReady(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक count = 10;

	जबतक (--count > 0) अणु
		reg_r(gspca_dev, 0x21, 0, 1);
		अगर ((gspca_dev->usb_buf[0] & 0x01) == 0)
			अवरोध;
		msleep(10);
	पूर्ण
पूर्ण

अटल व्योम spca504B_WaitCmdStatus(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक count = 50;

	जबतक (--count > 0) अणु
		reg_r(gspca_dev, 0x21, 1, 1);
		अगर (gspca_dev->usb_buf[0] != 0) अणु
			reg_w_1(gspca_dev, 0x21, 0, 1, 0);
			reg_r(gspca_dev, 0x21, 1, 1);
			spca504B_PollingDataReady(gspca_dev);
			अवरोध;
		पूर्ण
		msleep(10);
	पूर्ण
पूर्ण

अटल व्योम spca50x_GetFirmware(काष्ठा gspca_dev *gspca_dev)
अणु
	u8 *data;

	अगर (gspca_debug < D_STREAM)
		वापस;

	data = gspca_dev->usb_buf;
	reg_r(gspca_dev, 0x20, 0, 5);
	gspca_dbg(gspca_dev, D_STREAM, "FirmWare: %d %d %d %d %d\n",
		  data[0], data[1], data[2], data[3], data[4]);
	reg_r(gspca_dev, 0x23, 0, 64);
	reg_r(gspca_dev, 0x23, 1, 64);
पूर्ण

अटल व्योम spca504B_SetSizeType(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u8 Size;

	Size = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	चयन (sd->bridge) अणु
	हाल BRIDGE_SPCA533:
		reg_w_riv(gspca_dev, 0x31, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PollingDataReady(gspca_dev);
		spca50x_GetFirmware(gspca_dev);

		reg_w_1(gspca_dev, 0x24, 0, 8, 2);		/* type */
		reg_r(gspca_dev, 0x24, 8, 1);

		reg_w_1(gspca_dev, 0x25, 0, 4, Size);
		reg_r(gspca_dev, 0x25, 4, 1);			/* size */
		spca504B_PollingDataReady(gspca_dev);

		/* Init the cam width height with some values get on init ? */
		reg_w_riv(gspca_dev, 0x31, 0x0004, 0x00);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PollingDataReady(gspca_dev);
		अवरोध;
	शेष:
/* हाल BRIDGE_SPCA504B: */
/* हाल BRIDGE_SPCA536: */
		reg_w_1(gspca_dev, 0x25, 0, 4, Size);
		reg_r(gspca_dev, 0x25, 4, 1);			/* size */
		reg_w_1(gspca_dev, 0x27, 0, 0, 6);
		reg_r(gspca_dev, 0x27, 0, 1);			/* type */
		spca504B_PollingDataReady(gspca_dev);
		अवरोध;
	हाल BRIDGE_SPCA504:
		Size += 3;
		अगर (sd->subtype == AiptekMiniPenCam13) अणु
			/* spca504a aiptek */
			spca504A_acknowledged_command(gspca_dev,
						0x08, Size, 0,
						0x80 | (Size & 0x0f), 1);
			spca504A_acknowledged_command(gspca_dev,
							1, 3, 0, 0x9f, 0);
		पूर्ण अन्यथा अणु
			spca504_acknowledged_command(gspca_dev, 0x08, Size, 0);
		पूर्ण
		अवरोध;
	हाल BRIDGE_SPCA504C:
		/* capture mode */
		reg_w_riv(gspca_dev, 0xa0, (0x0500 | (Size & 0x0f)), 0x00);
		reg_w_riv(gspca_dev, 0x20, 0x01, 0x0500 | (Size & 0x0f));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम spca504_रुको_status(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक cnt;

	cnt = 256;
	जबतक (--cnt > 0) अणु
		/* With this we get the status, when वापस 0 it's all ok */
		reg_r(gspca_dev, 0x06, 0x00, 1);
		अगर (gspca_dev->usb_buf[0] == 0)
			वापस;
		msleep(10);
	पूर्ण
पूर्ण

अटल व्योम spca504B_setQtable(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w_1(gspca_dev, 0x26, 0, 0, 3);
	reg_r(gspca_dev, 0x26, 0, 1);
	spca504B_PollingDataReady(gspca_dev);
पूर्ण

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u16 reg;

	reg = sd->bridge == BRIDGE_SPCA536 ? 0x20f0 : 0x21a7;
	reg_w_riv(gspca_dev, 0x00, reg, val);
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u16 reg;

	reg = sd->bridge == BRIDGE_SPCA536 ? 0x20f1 : 0x21a8;
	reg_w_riv(gspca_dev, 0x00, reg, val);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	u16 reg;

	reg = sd->bridge == BRIDGE_SPCA536 ? 0x20f6 : 0x21ae;
	reg_w_riv(gspca_dev, 0x00, reg, val);
पूर्ण

अटल व्योम init_ctl_reg(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक pollreg = 1;

	चयन (sd->bridge) अणु
	हाल BRIDGE_SPCA504:
	हाल BRIDGE_SPCA504C:
		pollreg = 0;
		fallthrough;
	शेष:
/*	हाल BRIDGE_SPCA533: */
/*	हाल BRIDGE_SPCA504B: */
		reg_w_riv(gspca_dev, 0, 0x21ad, 0x00);	/* hue */
		reg_w_riv(gspca_dev, 0, 0x21ac, 0x01);	/* sat/hue */
		reg_w_riv(gspca_dev, 0, 0x21a3, 0x00);	/* gamma */
		अवरोध;
	हाल BRIDGE_SPCA536:
		reg_w_riv(gspca_dev, 0, 0x20f5, 0x40);
		reg_w_riv(gspca_dev, 0, 0x20f4, 0x01);
		reg_w_riv(gspca_dev, 0, 0x2089, 0x00);
		अवरोध;
	पूर्ण
	अगर (pollreg)
		spca504B_PollingDataReady(gspca_dev);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;

	sd->bridge = id->driver_info >> 8;
	sd->subtype = id->driver_info;

	अगर (sd->subtype == AiptekMiniPenCam13) अणु

		/* try to get the firmware as some cam answer 2.0.1.2.2
		 * and should be a spca504b then overग_लिखो that setting */
		reg_r(gspca_dev, 0x20, 0, 1);
		चयन (gspca_dev->usb_buf[0]) अणु
		हाल 1:
			अवरोध;		/* (right bridge/subtype) */
		हाल 2:
			sd->bridge = BRIDGE_SPCA504B;
			sd->subtype = 0;
			अवरोध;
		शेष:
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	चयन (sd->bridge) अणु
	शेष:
/*	हाल BRIDGE_SPCA504B: */
/*	हाल BRIDGE_SPCA504: */
/*	हाल BRIDGE_SPCA536: */
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
		अवरोध;
	हाल BRIDGE_SPCA533:
		cam->cam_mode = custom_mode;
		अगर (sd->subtype == MegaImageVI)		/* 320x240 only */
			cam->nmodes = ARRAY_SIZE(custom_mode) - 1;
		अन्यथा
			cam->nmodes = ARRAY_SIZE(custom_mode);
		अवरोध;
	हाल BRIDGE_SPCA504C:
		cam->cam_mode = vga_mode2;
		cam->nmodes = ARRAY_SIZE(vga_mode2);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->bridge) अणु
	हाल BRIDGE_SPCA504B:
		reg_w_riv(gspca_dev, 0x1d, 0x00, 0);
		reg_w_riv(gspca_dev, 0x00, 0x2306, 0x01);
		reg_w_riv(gspca_dev, 0x00, 0x0d04, 0x00);
		reg_w_riv(gspca_dev, 0x00, 0x2000, 0x00);
		reg_w_riv(gspca_dev, 0x00, 0x2301, 0x13);
		reg_w_riv(gspca_dev, 0x00, 0x2306, 0x00);
		fallthrough;
	हाल BRIDGE_SPCA533:
		spca504B_PollingDataReady(gspca_dev);
		spca50x_GetFirmware(gspca_dev);
		अवरोध;
	हाल BRIDGE_SPCA536:
		spca50x_GetFirmware(gspca_dev);
		reg_r(gspca_dev, 0x00, 0x5002, 1);
		reg_w_1(gspca_dev, 0x24, 0, 0, 0);
		reg_r(gspca_dev, 0x24, 0, 1);
		spca504B_PollingDataReady(gspca_dev);
		reg_w_riv(gspca_dev, 0x34, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		अवरोध;
	हाल BRIDGE_SPCA504C:	/* pccam600 */
		gspca_dbg(gspca_dev, D_STREAM, "Opening SPCA504 (PC-CAM 600)\n");
		reg_w_riv(gspca_dev, 0xe0, 0x0000, 0x0000);
		reg_w_riv(gspca_dev, 0xe0, 0x0000, 0x0001);	/* reset */
		spca504_रुको_status(gspca_dev);
		अगर (sd->subtype == LogitechClickSmart420)
			ग_लिखो_vector(gspca_dev,
				spca504A_clicksmart420_खोलो_data,
				ARRAY_SIZE(spca504A_clicksmart420_खोलो_data));
		अन्यथा
			ग_लिखो_vector(gspca_dev, spca504_pccam600_खोलो_data,
				ARRAY_SIZE(spca504_pccam600_खोलो_data));
		setup_qtable(gspca_dev, qtable_creative_pccam);
		अवरोध;
	शेष:
/*	हाल BRIDGE_SPCA504: */
		gspca_dbg(gspca_dev, D_STREAM, "Opening SPCA504\n");
		अगर (sd->subtype == AiptekMiniPenCam13) अणु
			spca504_पढ़ो_info(gspca_dev);

			/* Set AE AWB Banding Type 3-> 50Hz 2-> 60Hz */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 1);
			/* Twice sequential need status 0xff->0x9e->0x9d */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 0);

			spca504A_acknowledged_command(gspca_dev, 0x24,
							0, 0, 0x9d, 1);
			/******************************/
			/* spca504a aiptek */
			spca504A_acknowledged_command(gspca_dev, 0x08,
							6, 0, 0x86, 1);
/*			reg_ग_लिखो (dev, 0, 0x2000, 0); */
/*			reg_ग_लिखो (dev, 0, 0x2883, 1); */
/*			spca504A_acknowledged_command (gspca_dev, 0x08,
							6, 0, 0x86, 1); */
/*			spca504A_acknowledged_command (gspca_dev, 0x24,
							0, 0, 0x9D, 1); */
			reg_w_riv(gspca_dev, 0x00, 0x270c, 0x05);
							/* L92 sno1t.txt */
			reg_w_riv(gspca_dev, 0x00, 0x2310, 0x05);
			spca504A_acknowledged_command(gspca_dev, 0x01,
							0x0f, 0, 0xff, 0);
		पूर्ण
		/* setup qtable */
		reg_w_riv(gspca_dev, 0, 0x2000, 0);
		reg_w_riv(gspca_dev, 0, 0x2883, 1);
		setup_qtable(gspca_dev, qtable_spca504_शेष);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक enable;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, QUALITY);

	अगर (sd->bridge == BRIDGE_SPCA504B)
		spca504B_setQtable(gspca_dev);
	spca504B_SetSizeType(gspca_dev);
	चयन (sd->bridge) अणु
	शेष:
/*	हाल BRIDGE_SPCA504B: */
/*	हाल BRIDGE_SPCA533: */
/*	हाल BRIDGE_SPCA536: */
		चयन (sd->subtype) अणु
		हाल MegapixV4:
		हाल LogitechClickSmart820:
		हाल MegaImageVI:
			reg_w_riv(gspca_dev, 0xf0, 0, 0);
			spca504B_WaitCmdStatus(gspca_dev);
			reg_r(gspca_dev, 0xf0, 4, 0);
			spca504B_WaitCmdStatus(gspca_dev);
			अवरोध;
		शेष:
			reg_w_riv(gspca_dev, 0x31, 0x0004, 0x00);
			spca504B_WaitCmdStatus(gspca_dev);
			spca504B_PollingDataReady(gspca_dev);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BRIDGE_SPCA504:
		अगर (sd->subtype == AiptekMiniPenCam13) अणु
			spca504_पढ़ो_info(gspca_dev);

			/* Set AE AWB Banding Type 3-> 50Hz 2-> 60Hz */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 1);
			/* Twice sequential need status 0xff->0x9e->0x9d */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 0);
			spca504A_acknowledged_command(gspca_dev, 0x24,
							0, 0, 0x9d, 1);
		पूर्ण अन्यथा अणु
			spca504_acknowledged_command(gspca_dev, 0x24, 8, 3);
			spca504_पढ़ो_info(gspca_dev);
			spca504_acknowledged_command(gspca_dev, 0x24, 8, 3);
			spca504_acknowledged_command(gspca_dev, 0x24, 0, 0);
		पूर्ण
		spca504B_SetSizeType(gspca_dev);
		reg_w_riv(gspca_dev, 0x00, 0x270c, 0x05);
							/* L92 sno1t.txt */
		reg_w_riv(gspca_dev, 0x00, 0x2310, 0x05);
		अवरोध;
	हाल BRIDGE_SPCA504C:
		अगर (sd->subtype == LogitechClickSmart420) अणु
			ग_लिखो_vector(gspca_dev,
				spca504A_clicksmart420_init_data,
				ARRAY_SIZE(spca504A_clicksmart420_init_data));
		पूर्ण अन्यथा अणु
			ग_लिखो_vector(gspca_dev, spca504_pccam600_init_data,
				ARRAY_SIZE(spca504_pccam600_init_data));
		पूर्ण
		enable = (sd->स्वतःgain ? 0x04 : 0x01);
		reg_w_riv(gspca_dev, 0x0c, 0x0000, enable);
							/* स्वतः exposure */
		reg_w_riv(gspca_dev, 0xb0, 0x0000, enable);
							/* स्वतः whiteness */

		/* set शेष exposure compensation and whiteness balance */
		reg_w_riv(gspca_dev, 0x30, 0x0001, 800);	/* ~ 20 fps */
		reg_w_riv(gspca_dev, 0x30, 0x0002, 1600);
		spca504B_SetSizeType(gspca_dev);
		अवरोध;
	पूर्ण
	init_ctl_reg(gspca_dev);
	वापस gspca_dev->usb_err;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	चयन (sd->bridge) अणु
	शेष:
/*	हाल BRIDGE_SPCA533: */
/*	हाल BRIDGE_SPCA536: */
/*	हाल BRIDGE_SPCA504B: */
		reg_w_riv(gspca_dev, 0x31, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PollingDataReady(gspca_dev);
		अवरोध;
	हाल BRIDGE_SPCA504:
	हाल BRIDGE_SPCA504C:
		reg_w_riv(gspca_dev, 0x00, 0x2000, 0x0000);

		अगर (sd->subtype == AiptekMiniPenCam13) अणु
			/* spca504a aiptek */
/*			spca504A_acknowledged_command(gspca_dev, 0x08,
							 6, 0, 0x86, 1); */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							0x00, 0x00, 0x9d, 1);
			spca504A_acknowledged_command(gspca_dev, 0x01,
							0x0f, 0x00, 0xff, 1);
		पूर्ण अन्यथा अणु
			spca504_acknowledged_command(gspca_dev, 0x24, 0, 0);
			reg_w_riv(gspca_dev, 0x01, 0x000f, 0x0000);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i, sof = 0;
	अटल u8 ffd9[] = अणु0xff, 0xd9पूर्ण;

/* frames are jpeg 4.1.1 without 0xff escape */
	चयन (sd->bridge) अणु
	हाल BRIDGE_SPCA533:
		अगर (data[0] == 0xff) अणु
			अगर (data[1] != 0x01) अणु	/* drop packet */
/*				gspca_dev->last_packet_type = DISCARD_PACKET; */
				वापस;
			पूर्ण
			sof = 1;
			data += SPCA533_OFFSET_DATA;
			len -= SPCA533_OFFSET_DATA;
		पूर्ण अन्यथा अणु
			data += 1;
			len -= 1;
		पूर्ण
		अवरोध;
	हाल BRIDGE_SPCA536:
		अगर (data[0] == 0xff) अणु
			sof = 1;
			data += SPCA536_OFFSET_DATA;
			len -= SPCA536_OFFSET_DATA;
		पूर्ण अन्यथा अणु
			data += 2;
			len -= 2;
		पूर्ण
		अवरोध;
	शेष:
/*	हाल BRIDGE_SPCA504: */
/*	हाल BRIDGE_SPCA504B: */
		चयन (data[0]) अणु
		हाल 0xfe:			/* start of frame */
			sof = 1;
			data += SPCA50X_OFFSET_DATA;
			len -= SPCA50X_OFFSET_DATA;
			अवरोध;
		हाल 0xff:			/* drop packet */
/*			gspca_dev->last_packet_type = DISCARD_PACKET; */
			वापस;
		शेष:
			data += 1;
			len -= 1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BRIDGE_SPCA504C:
		चयन (data[0]) अणु
		हाल 0xfe:			/* start of frame */
			sof = 1;
			data += SPCA504_PCCAM600_OFFSET_DATA;
			len -= SPCA504_PCCAM600_OFFSET_DATA;
			अवरोध;
		हाल 0xff:			/* drop packet */
/*			gspca_dev->last_packet_type = DISCARD_PACKET; */
			वापस;
		शेष:
			data += 1;
			len -= 1;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (sof) अणु		/* start of frame */
		gspca_frame_add(gspca_dev, LAST_PACKET,
				ffd9, 2);

		/* put the JPEG header in the new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);
	पूर्ण

	/* add 0x00 after 0xff */
	i = 0;
	करो अणु
		अगर (data[i] == 0xff) अणु
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, i + 1);
			len -= i;
			data += i;
			*data = 0x00;
			i = 0;
		पूर्ण
		i++;
	पूर्ण जबतक (i < len);
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
पूर्ण

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
	हाल V4L2_CID_CONTRAST:
		setcontrast(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_SATURATION:
		setcolors(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_AUTOGAIN:
		sd->स्वतःgain = ctrl->val;
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
			V4L2_CID_BRIGHTNESS, -128, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 0x20);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 0x1a);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);

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
#घोषणा BS(bridge, subtype) \
	.driver_info = (BRIDGE_ ## bridge << 8) \
			| (subtype)
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणुUSB_DEVICE(0x041e, 0x400b), BS(SPCA504C, 0)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4012), BS(SPCA504C, 0)पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x4013), BS(SPCA504C, 0)पूर्ण,
	अणुUSB_DEVICE(0x0458, 0x7006), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x0461, 0x0821), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0905), BS(SPCA533, LogitechClickSmart820)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0960), BS(SPCA504C, LogitechClickSmart420)पूर्ण,
	अणुUSB_DEVICE(0x0471, 0x0322), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x04a5, 0x3003), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x04a5, 0x3008), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x04a5, 0x300a), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x04f1, 0x1001), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x04fc, 0x500c), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x04fc, 0x504a), BS(SPCA504, AiptekMiniPenCam13)पूर्ण,
	अणुUSB_DEVICE(0x04fc, 0x504b), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x04fc, 0x5330), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x04fc, 0x5360), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x04fc, 0xffff), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x052b, 0x1507), BS(SPCA533, MegapixV4)पूर्ण,
	अणुUSB_DEVICE(0x052b, 0x1513), BS(SPCA533, MegapixV4)पूर्ण,
	अणुUSB_DEVICE(0x052b, 0x1803), BS(SPCA533, MegaImageVI)पूर्ण,
	अणुUSB_DEVICE(0x0546, 0x3155), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x0546, 0x3191), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x0546, 0x3273), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc211), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc230), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc232), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc360), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc420), BS(SPCA504, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc430), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc440), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc520), BS(SPCA504, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc530), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc540), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc630), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc650), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x05da, 0x1018), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x06d6, 0x0031), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x06d6, 0x0041), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x0733, 0x1311), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x0733, 0x1314), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x0733, 0x2211), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x0733, 0x2221), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x0733, 0x3261), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x0733, 0x3281), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x0104), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x0106), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2008), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2010), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2016), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2018), BS(SPCA504B, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2020), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2022), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2024), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2028), BS(SPCA533, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2040), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2042), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2050), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x2060), BS(SPCA536, 0)पूर्ण,
	अणुUSB_DEVICE(0x0d64, 0x0303), BS(SPCA536, 0)पूर्ण,
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
