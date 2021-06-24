<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPCA500 chip based cameras initialization data
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#घोषणा MODULE_NAME "spca500"

#समावेश "gspca.h"
#समावेश "jpeg.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("GSPCA/SPCA500 USB Camera Driver");
MODULE_LICENSE("GPL");

#घोषणा QUALITY 85

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;		/* !! must be the first item */

	अक्षर subtype;
#घोषणा AgfaCl20 0
#घोषणा AiptekPocketDV 1
#घोषणा BenqDC1016 2
#घोषणा CreativePCCam300 3
#घोषणा DLinkDSC350 4
#घोषणा Gsmarपंचांगini 5
#घोषणा IntelPocketPCCamera 6
#घोषणा KodakEZ200 7
#घोषणा LogitechClickSmart310 8
#घोषणा LogitechClickSmart510 9
#घोषणा LogitechTraveler 10
#घोषणा MustekGsmart300 11
#घोषणा Opसमयdia 12
#घोषणा PalmPixDC85 13
#घोषणा ToptroIndus 14

	u8 jpeg_hdr[JPEG_HDR_SZ];
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु320, 240, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 320,
		.sizeimage = 320 * 240 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु640, 480, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 640,
		.sizeimage = 640 * 480 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sअगर_mode[] = अणु
	अणु176, 144, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_JPEG, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288 * 3 / 8 + 590,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.priv = 0पूर्ण,
पूर्ण;

/* Frame packet header offsets क्रम the spca500 */
#घोषणा SPCA500_OFFSET_PADDINGLB 2
#घोषणा SPCA500_OFFSET_PADDINGHB 3
#घोषणा SPCA500_OFFSET_MODE      4
#घोषणा SPCA500_OFFSET_IMGWIDTH  5
#घोषणा SPCA500_OFFSET_IMGHEIGHT 6
#घोषणा SPCA500_OFFSET_IMGMODE   7
#घोषणा SPCA500_OFFSET_QTBLINDEX 8
#घोषणा SPCA500_OFFSET_FRAMSEQ   9
#घोषणा SPCA500_OFFSET_CDSPINFO  10
#घोषणा SPCA500_OFFSET_GPIO      11
#घोषणा SPCA500_OFFSET_AUGPIO    12
#घोषणा SPCA500_OFFSET_DATA      16


अटल स्थिर __u16 spca500_visual_शेषs[][3] = अणु
	अणु0x00, 0x0003, 0x816bपूर्ण,	/* SSI not active sync with vsync,
				 * hue (H byte) = 0,
				 * saturation/hue enable,
				 * brightness/contrast enable.
				 */
	अणु0x00, 0x0000, 0x8167पूर्ण,	/* brightness = 0 */
	अणु0x00, 0x0020, 0x8168पूर्ण,	/* contrast = 0 */
	अणु0x00, 0x0003, 0x816bपूर्ण,	/* SSI not active sync with vsync,
				 * hue (H byte) = 0, saturation/hue enable,
				 * brightness/contrast enable.
				 * was 0x0003, now 0x0000.
				 */
	अणु0x00, 0x0000, 0x816aपूर्ण,	/* hue (L byte) = 0 */
	अणु0x00, 0x0020, 0x8169पूर्ण,	/* saturation = 0x20 */
	अणु0x00, 0x0050, 0x8157पूर्ण,	/* edge gain high threshold */
	अणु0x00, 0x0030, 0x8158पूर्ण,	/* edge gain low threshold */
	अणु0x00, 0x0028, 0x8159पूर्ण,	/* edge bandwidth high threshold */
	अणु0x00, 0x000a, 0x815aपूर्ण,	/* edge bandwidth low threshold */
	अणु0x00, 0x0001, 0x8202पूर्ण,	/* घड़ी rate compensation = 1/25 sec/frame */
	अणु0x0c, 0x0004, 0x0000पूर्ण,
	/* set पूर्णांकerface */
	अणुपूर्ण
पूर्ण;
अटल स्थिर __u16 Clicksmart510_शेषs[][3] = अणु
	अणु0x00, 0x00, 0x8211पूर्ण,
	अणु0x00, 0x01, 0x82c0पूर्ण,
	अणु0x00, 0x10, 0x82cbपूर्ण,
	अणु0x00, 0x0f, 0x800dपूर्ण,
	अणु0x00, 0x82, 0x8225पूर्ण,
	अणु0x00, 0x21, 0x8228पूर्ण,
	अणु0x00, 0x00, 0x8203पूर्ण,
	अणु0x00, 0x00, 0x8204पूर्ण,
	अणु0x00, 0x08, 0x8205पूर्ण,
	अणु0x00, 0xf8, 0x8206पूर्ण,
	अणु0x00, 0x28, 0x8207पूर्ण,
	अणु0x00, 0xa0, 0x8208पूर्ण,
	अणु0x00, 0x08, 0x824aपूर्ण,
	अणु0x00, 0x08, 0x8214पूर्ण,
	अणु0x00, 0x80, 0x82c1पूर्ण,
	अणु0x00, 0x00, 0x82c2पूर्ण,
	अणु0x00, 0x00, 0x82caपूर्ण,
	अणु0x00, 0x80, 0x82c1पूर्ण,
	अणु0x00, 0x04, 0x82c2पूर्ण,
	अणु0x00, 0x00, 0x82caपूर्ण,
	अणु0x00, 0xfc, 0x8100पूर्ण,
	अणु0x00, 0xfc, 0x8105पूर्ण,
	अणु0x00, 0x30, 0x8101पूर्ण,
	अणु0x00, 0x00, 0x8102पूर्ण,
	अणु0x00, 0x00, 0x8103पूर्ण,
	अणु0x00, 0x66, 0x8107पूर्ण,
	अणु0x00, 0x00, 0x816bपूर्ण,
	अणु0x00, 0x00, 0x8155पूर्ण,
	अणु0x00, 0x01, 0x8156पूर्ण,
	अणु0x00, 0x60, 0x8157पूर्ण,
	अणु0x00, 0x40, 0x8158पूर्ण,
	अणु0x00, 0x0a, 0x8159पूर्ण,
	अणु0x00, 0x06, 0x815aपूर्ण,
	अणु0x00, 0x00, 0x813fपूर्ण,
	अणु0x00, 0x00, 0x8200पूर्ण,
	अणु0x00, 0x19, 0x8201पूर्ण,
	अणु0x00, 0x00, 0x82c1पूर्ण,
	अणु0x00, 0xa0, 0x82c2पूर्ण,
	अणु0x00, 0x00, 0x82caपूर्ण,
	अणु0x00, 0x00, 0x8117पूर्ण,
	अणु0x00, 0x00, 0x8118पूर्ण,
	अणु0x00, 0x65, 0x8119पूर्ण,
	अणु0x00, 0x00, 0x811aपूर्ण,
	अणु0x00, 0x00, 0x811bपूर्ण,
	अणु0x00, 0x55, 0x811cपूर्ण,
	अणु0x00, 0x65, 0x811dपूर्ण,
	अणु0x00, 0x55, 0x811eपूर्ण,
	अणु0x00, 0x16, 0x811fपूर्ण,
	अणु0x00, 0x19, 0x8120पूर्ण,
	अणु0x00, 0x80, 0x8103पूर्ण,
	अणु0x00, 0x83, 0x816bपूर्ण,
	अणु0x00, 0x25, 0x8168पूर्ण,
	अणु0x00, 0x01, 0x820fपूर्ण,
	अणु0x00, 0xff, 0x8115पूर्ण,
	अणु0x00, 0x48, 0x8116पूर्ण,
	अणु0x00, 0x50, 0x8151पूर्ण,
	अणु0x00, 0x40, 0x8152पूर्ण,
	अणु0x00, 0x78, 0x8153पूर्ण,
	अणु0x00, 0x40, 0x8154पूर्ण,
	अणु0x00, 0x00, 0x8167पूर्ण,
	अणु0x00, 0x20, 0x8168पूर्ण,
	अणु0x00, 0x00, 0x816aपूर्ण,
	अणु0x00, 0x03, 0x816bपूर्ण,
	अणु0x00, 0x20, 0x8169पूर्ण,
	अणु0x00, 0x60, 0x8157पूर्ण,
	अणु0x00, 0x00, 0x8190पूर्ण,
	अणु0x00, 0x00, 0x81a1पूर्ण,
	अणु0x00, 0x00, 0x81b2पूर्ण,
	अणु0x00, 0x27, 0x8191पूर्ण,
	अणु0x00, 0x27, 0x81a2पूर्ण,
	अणु0x00, 0x27, 0x81b3पूर्ण,
	अणु0x00, 0x4b, 0x8192पूर्ण,
	अणु0x00, 0x4b, 0x81a3पूर्ण,
	अणु0x00, 0x4b, 0x81b4पूर्ण,
	अणु0x00, 0x66, 0x8193पूर्ण,
	अणु0x00, 0x66, 0x81a4पूर्ण,
	अणु0x00, 0x66, 0x81b5पूर्ण,
	अणु0x00, 0x79, 0x8194पूर्ण,
	अणु0x00, 0x79, 0x81a5पूर्ण,
	अणु0x00, 0x79, 0x81b6पूर्ण,
	अणु0x00, 0x8a, 0x8195पूर्ण,
	अणु0x00, 0x8a, 0x81a6पूर्ण,
	अणु0x00, 0x8a, 0x81b7पूर्ण,
	अणु0x00, 0x9b, 0x8196पूर्ण,
	अणु0x00, 0x9b, 0x81a7पूर्ण,
	अणु0x00, 0x9b, 0x81b8पूर्ण,
	अणु0x00, 0xa6, 0x8197पूर्ण,
	अणु0x00, 0xa6, 0x81a8पूर्ण,
	अणु0x00, 0xa6, 0x81b9पूर्ण,
	अणु0x00, 0xb2, 0x8198पूर्ण,
	अणु0x00, 0xb2, 0x81a9पूर्ण,
	अणु0x00, 0xb2, 0x81baपूर्ण,
	अणु0x00, 0xbe, 0x8199पूर्ण,
	अणु0x00, 0xbe, 0x81aaपूर्ण,
	अणु0x00, 0xbe, 0x81bbपूर्ण,
	अणु0x00, 0xc8, 0x819aपूर्ण,
	अणु0x00, 0xc8, 0x81abपूर्ण,
	अणु0x00, 0xc8, 0x81bcपूर्ण,
	अणु0x00, 0xd2, 0x819bपूर्ण,
	अणु0x00, 0xd2, 0x81acपूर्ण,
	अणु0x00, 0xd2, 0x81bdपूर्ण,
	अणु0x00, 0xdb, 0x819cपूर्ण,
	अणु0x00, 0xdb, 0x81adपूर्ण,
	अणु0x00, 0xdb, 0x81beपूर्ण,
	अणु0x00, 0xe4, 0x819dपूर्ण,
	अणु0x00, 0xe4, 0x81aeपूर्ण,
	अणु0x00, 0xe4, 0x81bfपूर्ण,
	अणु0x00, 0xed, 0x819eपूर्ण,
	अणु0x00, 0xed, 0x81afपूर्ण,
	अणु0x00, 0xed, 0x81c0पूर्ण,
	अणु0x00, 0xf7, 0x819fपूर्ण,
	अणु0x00, 0xf7, 0x81b0पूर्ण,
	अणु0x00, 0xf7, 0x81c1पूर्ण,
	अणु0x00, 0xff, 0x81a0पूर्ण,
	अणु0x00, 0xff, 0x81b1पूर्ण,
	अणु0x00, 0xff, 0x81c2पूर्ण,
	अणु0x00, 0x03, 0x8156पूर्ण,
	अणु0x00, 0x00, 0x8211पूर्ण,
	अणु0x00, 0x20, 0x8168पूर्ण,
	अणु0x00, 0x01, 0x8202पूर्ण,
	अणु0x00, 0x30, 0x8101पूर्ण,
	अणु0x00, 0x00, 0x8111पूर्ण,
	अणु0x00, 0x00, 0x8112पूर्ण,
	अणु0x00, 0x00, 0x8113पूर्ण,
	अणु0x00, 0x00, 0x8114पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर __u8 qtable_creative_pccam[2][64] = अणु
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

अटल स्थिर __u8 qtable_kodak_ez200[2][64] = अणु
	अणु				/* Q-table Y-components */
	 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x05, 0x06,
	 0x01, 0x01, 0x01, 0x02, 0x03, 0x06, 0x06, 0x06,
	 0x01, 0x01, 0x02, 0x02, 0x04, 0x06, 0x07, 0x06,
	 0x01, 0x02, 0x02, 0x03, 0x05, 0x09, 0x08, 0x06,
	 0x02, 0x02, 0x04, 0x06, 0x07, 0x0b, 0x0a, 0x08,
	 0x02, 0x04, 0x06, 0x06, 0x08, 0x0a, 0x0b, 0x09,
	 0x05, 0x06, 0x08, 0x09, 0x0a, 0x0c, 0x0c, 0x0a,
	 0x07, 0x09, 0x0a, 0x0a, 0x0b, 0x0a, 0x0a, 0x0aपूर्ण,
	अणु				/* Q-table C-components */
	 0x02, 0x02, 0x02, 0x05, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x02, 0x02, 0x03, 0x07, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x02, 0x03, 0x06, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x05, 0x07, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
	 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0aपूर्ण
पूर्ण;

अटल स्थिर __u8 qtable_pocketdv[2][64] = अणु
	अणु		/* Q-table Y-components start रेजिस्टरs 0x8800 */
	 0x06, 0x04, 0x04, 0x06, 0x0a, 0x10, 0x14, 0x18,
	 0x05, 0x05, 0x06, 0x08, 0x0a, 0x17, 0x18, 0x16,
	 0x06, 0x05, 0x06, 0x0a, 0x10, 0x17, 0x1c, 0x16,
	 0x06, 0x07, 0x09, 0x0c, 0x14, 0x23, 0x20, 0x19,
	 0x07, 0x09, 0x0f, 0x16, 0x1b, 0x2c, 0x29, 0x1f,
	 0x0a, 0x0e, 0x16, 0x1a, 0x20, 0x2a, 0x2d, 0x25,
	 0x14, 0x1a, 0x1f, 0x23, 0x29, 0x30, 0x30, 0x28,
	 0x1d, 0x25, 0x26, 0x27, 0x2d, 0x28, 0x29, 0x28,
	 पूर्ण,
	अणु		/* Q-table C-components start रेजिस्टरs 0x8840 */
	 0x07, 0x07, 0x0a, 0x13, 0x28, 0x28, 0x28, 0x28,
	 0x07, 0x08, 0x0a, 0x1a, 0x28, 0x28, 0x28, 0x28,
	 0x0a, 0x0a, 0x16, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x13, 0x1a, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
	 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28पूर्ण
पूर्ण;

/* पढ़ो 'len' bytes to gspca_dev->usb_buf */
अटल व्योम reg_r(काष्ठा gspca_dev *gspca_dev,
		  __u16 index,
		  __u16 length)
अणु
	usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			0,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,		/* value */
			index, gspca_dev->usb_buf, length, 500);
पूर्ण

अटल पूर्णांक reg_w(काष्ठा gspca_dev *gspca_dev,
		     __u16 req, __u16 index, __u16 value)
अणु
	पूर्णांक ret;

	gspca_dbg(gspca_dev, D_USBO, "reg write: [0x%02x] = 0x%02x\n",
		  index, value);
	ret = usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			req,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value, index, शून्य, 0, 500);
	अगर (ret < 0)
		pr_err("reg write: error %d\n", ret);
	वापस ret;
पूर्ण

/* वापसs: negative is error, pos or zero is data */
अटल पूर्णांक reg_r_12(काष्ठा gspca_dev *gspca_dev,
			__u16 req,	/* bRequest */
			__u16 index,	/* wIndex */
			__u16 length)	/* wLength (1 or 2 only) */
अणु
	पूर्णांक ret;

	gspca_dev->usb_buf[1] = 0;
	ret = usb_control_msg(gspca_dev->dev,
			usb_rcvctrlpipe(gspca_dev->dev, 0),
			req,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,		/* value */
			index,
			gspca_dev->usb_buf, length,
			500);		/* समयout */
	अगर (ret < 0) अणु
		pr_err("reg_r_12 err %d\n", ret);
		वापस ret;
	पूर्ण
	वापस (gspca_dev->usb_buf[1] << 8) + gspca_dev->usb_buf[0];
पूर्ण

/*
 * Simple function to रुको क्रम a given 8-bit value to be वापसed from
 * a reg_पढ़ो call.
 * Returns: negative is error or समयout, zero is success.
 */
अटल पूर्णांक reg_r_रुको(काष्ठा gspca_dev *gspca_dev,
			__u16 reg, __u16 index, __u16 value)
अणु
	पूर्णांक ret, cnt = 20;

	जबतक (--cnt > 0) अणु
		ret = reg_r_12(gspca_dev, reg, index, 1);
		अगर (ret == value)
			वापस 0;
		msleep(50);
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक ग_लिखो_vector(काष्ठा gspca_dev *gspca_dev,
			स्थिर __u16 data[][3])
अणु
	पूर्णांक ret, i = 0;

	जबतक (data[i][0] != 0 || data[i][1] != 0 || data[i][2] != 0) अणु
		ret = reg_w(gspca_dev, data[i][0], data[i][2], data[i][1]);
		अगर (ret < 0)
			वापस ret;
		i++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक spca50x_setup_qtable(काष्ठा gspca_dev *gspca_dev,
				अचिन्हित पूर्णांक request,
				अचिन्हित पूर्णांक ybase,
				अचिन्हित पूर्णांक cbase,
				स्थिर __u8 qtable[2][64])
अणु
	पूर्णांक i, err;

	/* loop over y components */
	क्रम (i = 0; i < 64; i++) अणु
		err = reg_w(gspca_dev, request, ybase + i, qtable[0][i]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* loop over c components */
	क्रम (i = 0; i < 64; i++) अणु
		err = reg_w(gspca_dev, request, cbase + i, qtable[1][i]);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम spca500_ping310(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_r(gspca_dev, 0x0d04, 2);
	gspca_dbg(gspca_dev, D_STREAM, "ClickSmart310 ping 0x0d04 0x%02x 0x%02x\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
पूर्ण

अटल व्योम spca500_clksmart310_init(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_r(gspca_dev, 0x0d05, 2);
	gspca_dbg(gspca_dev, D_STREAM, "ClickSmart310 init 0x0d05 0x%02x 0x%02x\n",
		  gspca_dev->usb_buf[0], gspca_dev->usb_buf[1]);
	reg_w(gspca_dev, 0x00, 0x8167, 0x5a);
	spca500_ping310(gspca_dev);

	reg_w(gspca_dev, 0x00, 0x8168, 0x22);
	reg_w(gspca_dev, 0x00, 0x816a, 0xc0);
	reg_w(gspca_dev, 0x00, 0x816b, 0x0b);
	reg_w(gspca_dev, 0x00, 0x8169, 0x25);
	reg_w(gspca_dev, 0x00, 0x8157, 0x5b);
	reg_w(gspca_dev, 0x00, 0x8158, 0x5b);
	reg_w(gspca_dev, 0x00, 0x813f, 0x03);
	reg_w(gspca_dev, 0x00, 0x8151, 0x4a);
	reg_w(gspca_dev, 0x00, 0x8153, 0x78);
	reg_w(gspca_dev, 0x00, 0x0d01, 0x04);
						/* 00 क्रम adjust shutter */
	reg_w(gspca_dev, 0x00, 0x0d02, 0x01);
	reg_w(gspca_dev, 0x00, 0x8169, 0x25);
	reg_w(gspca_dev, 0x00, 0x0d01, 0x02);
पूर्ण

अटल व्योम spca500_seपंचांगode(काष्ठा gspca_dev *gspca_dev,
			__u8 xmult, __u8 ymult)
अणु
	पूर्णांक mode;

	/* set x multiplier */
	reg_w(gspca_dev, 0, 0x8001, xmult);

	/* set y multiplier */
	reg_w(gspca_dev, 0, 0x8002, ymult);

	/* use compressed mode, VGA, with mode specअगरic subsample */
	mode = gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv;
	reg_w(gspca_dev, 0, 0x8003, mode << 4);
पूर्ण

अटल पूर्णांक spca500_full_reset(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक err;

	/* send the reset command */
	err = reg_w(gspca_dev, 0xe0, 0x0001, 0x0000);
	अगर (err < 0)
		वापस err;

	/* रुको क्रम the reset to complete */
	err = reg_r_रुको(gspca_dev, 0x06, 0x0000, 0x0000);
	अगर (err < 0)
		वापस err;
	err = reg_w(gspca_dev, 0xe0, 0x0000, 0x0000);
	अगर (err < 0)
		वापस err;
	err = reg_r_रुको(gspca_dev, 0x06, 0, 0);
	अगर (err < 0) अणु
		gspca_err(gspca_dev, "reg_r_wait() failed\n");
		वापस err;
	पूर्ण
	/* all ok */
	वापस 0;
पूर्ण

/* Synchro the Bridge with sensor */
/* Maybe that will work on all spca500 chip */
/* because i only own a clicksmart310 try क्रम that chip */
/* using spca50x_set_packet_size() cause an Ooops here */
/* usb_set_पूर्णांकerface from kernel 2.6.x clear all the urb stuff */
/* up-port the same feature as in 2.4.x kernel */
अटल पूर्णांक spca500_synch310(काष्ठा gspca_dev *gspca_dev)
अणु
	अगर (usb_set_पूर्णांकerface(gspca_dev->dev, gspca_dev->अगरace, 0) < 0) अणु
		gspca_err(gspca_dev, "Set packet size: set interface error\n");
		जाओ error;
	पूर्ण
	spca500_ping310(gspca_dev);

	reg_r(gspca_dev, 0x0d00, 1);

	/* need alt setting here */
	gspca_dbg(gspca_dev, D_PACK, "ClickSmart310 sync alt: %d\n",
		  gspca_dev->alt);

	/* Winकरोze use pipe with altsetting 6 why 7 here */
	अगर (usb_set_पूर्णांकerface(gspca_dev->dev,
				gspca_dev->अगरace,
				gspca_dev->alt) < 0) अणु
		gspca_err(gspca_dev, "Set packet size: set interface error\n");
		जाओ error;
	पूर्ण
	वापस 0;
error:
	वापस -EBUSY;
पूर्ण

अटल व्योम spca500_reinit(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक err;
	__u8 Data;

	/* some unknown command from Aiptek pocket dv and family300 */

	reg_w(gspca_dev, 0x00, 0x0d01, 0x01);
	reg_w(gspca_dev, 0x00, 0x0d03, 0x00);
	reg_w(gspca_dev, 0x00, 0x0d02, 0x01);

	/* enable drop packet */
	reg_w(gspca_dev, 0x00, 0x850a, 0x0001);

	err = spca50x_setup_qtable(gspca_dev, 0x00, 0x8800, 0x8840,
				 qtable_pocketdv);
	अगर (err < 0)
		gspca_err(gspca_dev, "spca50x_setup_qtable failed on init\n");

	/* set qtable index */
	reg_w(gspca_dev, 0x00, 0x8880, 2);
	/* family cam Quicksmart stuff */
	reg_w(gspca_dev, 0x00, 0x800a, 0x00);
	/* Set agc transfer: synced between frames */
	reg_w(gspca_dev, 0x00, 0x820f, 0x01);
	/* Init SDRAM - needed क्रम SDRAM access */
	reg_w(gspca_dev, 0x00, 0x870a, 0x04);
	/*Start init sequence or stream */
	reg_w(gspca_dev, 0, 0x8003, 0x00);
	/* चयन to video camera mode */
	reg_w(gspca_dev, 0x00, 0x8000, 0x0004);
	msleep(2000);
	अगर (reg_r_रुको(gspca_dev, 0, 0x8000, 0x44) != 0) अणु
		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);
	पूर्ण
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;
	sd->subtype = id->driver_info;
	अगर (sd->subtype != LogitechClickSmart310) अणु
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
	पूर्ण अन्यथा अणु
		cam->cam_mode = sअगर_mode;
		cam->nmodes = ARRAY_SIZE(sअगर_mode);
	पूर्ण
	वापस 0;
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	/* initialisation of spca500 based cameras is deferred */
	gspca_dbg(gspca_dev, D_STREAM, "SPCA500 init\n");
	अगर (sd->subtype == LogitechClickSmart310)
		spca500_clksmart310_init(gspca_dev);
/*	अन्यथा
		spca500_initialise(gspca_dev); */
	gspca_dbg(gspca_dev, D_STREAM, "SPCA500 init done\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक err;
	__u8 Data;
	__u8 xmult, ymult;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, QUALITY);

	अगर (sd->subtype == LogitechClickSmart310) अणु
		xmult = 0x16;
		ymult = 0x12;
	पूर्ण अन्यथा अणु
		xmult = 0x28;
		ymult = 0x1e;
	पूर्ण

	/* is there a sensor here ? */
	reg_r(gspca_dev, 0x8a04, 1);
	gspca_dbg(gspca_dev, D_STREAM, "Spca500 Sensor Address 0x%02x\n",
		  gspca_dev->usb_buf[0]);
	gspca_dbg(gspca_dev, D_STREAM, "Spca500 curr_mode: %d Xmult: 0x%02x, Ymult: 0x%02x",
		  gspca_dev->curr_mode, xmult, ymult);

	/* setup qtable */
	चयन (sd->subtype) अणु
	हाल LogitechClickSmart310:
		 spca500_seपंचांगode(gspca_dev, xmult, ymult);

		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_creative_pccam);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca50x_setup_qtable failed\n");
		/* Init SDRAM - needed क्रम SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		/* चयन to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);
		msleep(500);
		अगर (reg_r_रुको(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_err(gspca_dev, "reg_r_wait() failed\n");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);

		spca500_synch310(gspca_dev);

		ग_लिखो_vector(gspca_dev, spca500_visual_शेषs);
		spca500_seपंचांगode(gspca_dev, xmult, ymult);
		/* enable drop packet */
		err = reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		अगर (err < 0)
			gspca_err(gspca_dev, "failed to enable drop packet\n");
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_creative_pccam);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca50x_setup_qtable failed\n");

		/* Init SDRAM - needed क्रम SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		/* चयन to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		अगर (reg_r_रुको(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_err(gspca_dev, "reg_r_wait() failed\n");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);
		अवरोध;
	हाल CreativePCCam300:		/* Creative PC-CAM 300 640x480 CCD */
	हाल IntelPocketPCCamera:	/* FIXME: Temporary fix क्रम
					 *	Intel Pocket PC Camera
					 *	- NWG (Sat 29th March 2003) */

		/* करो a full reset */
		err = spca500_full_reset(gspca_dev);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca500_full_reset failed\n");

		/* enable drop packet */
		err = reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		अगर (err < 0)
			gspca_err(gspca_dev, "failed to enable drop packet\n");
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_creative_pccam);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca50x_setup_qtable failed\n");

		spca500_seपंचांगode(gspca_dev, xmult, ymult);
		reg_w(gspca_dev, 0x20, 0x0001, 0x0004);

		/* चयन to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		अगर (reg_r_रुको(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_err(gspca_dev, "reg_r_wait() failed\n");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);

/*		ग_लिखो_vector(gspca_dev, spca500_visual_शेषs); */
		अवरोध;
	हाल KodakEZ200:		/* Kodak EZ200 */

		/* करो a full reset */
		err = spca500_full_reset(gspca_dev);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca500_full_reset failed\n");
		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);
		reg_w(gspca_dev, 0x00, 0x8880, 0);
		err = spca50x_setup_qtable(gspca_dev,
					   0x00, 0x8800, 0x8840,
					   qtable_kodak_ez200);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca50x_setup_qtable failed\n");
		spca500_seपंचांगode(gspca_dev, xmult, ymult);

		reg_w(gspca_dev, 0x20, 0x0001, 0x0004);

		/* चयन to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		अगर (reg_r_रुको(gspca_dev, 0, 0x8000, 0x44) != 0)
			gspca_err(gspca_dev, "reg_r_wait() failed\n");

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);

/*		ग_लिखो_vector(gspca_dev, spca500_visual_शेषs); */
		अवरोध;

	हाल BenqDC1016:
	हाल DLinkDSC350:		/* FamilyCam 300 */
	हाल AiptekPocketDV:		/* Aiptek PocketDV */
	हाल Gsmarपंचांगini:		/*Mustek Gsmart Mini */
	हाल MustekGsmart300:		/* Mustek Gsmart 300 */
	हाल PalmPixDC85:
	हाल Opसमयdia:
	हाल ToptroIndus:
	हाल AgfaCl20:
		spca500_reinit(gspca_dev);
		reg_w(gspca_dev, 0x00, 0x0d01, 0x01);
		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);

		err = spca50x_setup_qtable(gspca_dev,
				   0x00, 0x8800, 0x8840, qtable_pocketdv);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca50x_setup_qtable failed\n");
		reg_w(gspca_dev, 0x00, 0x8880, 2);

		/* familycam Quicksmart pocketDV stuff */
		reg_w(gspca_dev, 0x00, 0x800a, 0x00);
		/* Set agc transfer: synced between frames */
		reg_w(gspca_dev, 0x00, 0x820f, 0x01);
		/* Init SDRAM - needed क्रम SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		spca500_seपंचांगode(gspca_dev, xmult, ymult);
		/* चयन to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);

		reg_r_रुको(gspca_dev, 0, 0x8000, 0x44);

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);
		अवरोध;
	हाल LogitechTraveler:
	हाल LogitechClickSmart510:
		reg_w(gspca_dev, 0x02, 0x00, 0x00);
		/* enable drop packet */
		reg_w(gspca_dev, 0x00, 0x850a, 0x0001);

		err = spca50x_setup_qtable(gspca_dev,
					0x00, 0x8800,
					0x8840, qtable_creative_pccam);
		अगर (err < 0)
			gspca_err(gspca_dev, "spca50x_setup_qtable failed\n");
		reg_w(gspca_dev, 0x00, 0x8880, 3);
		reg_w(gspca_dev, 0x00, 0x800a, 0x00);
		/* Init SDRAM - needed क्रम SDRAM access */
		reg_w(gspca_dev, 0x00, 0x870a, 0x04);

		spca500_seपंचांगode(gspca_dev, xmult, ymult);

		/* चयन to video camera mode */
		reg_w(gspca_dev, 0x00, 0x8000, 0x0004);
		reg_r_रुको(gspca_dev, 0, 0x8000, 0x44);

		reg_r(gspca_dev, 0x816b, 1);
		Data = gspca_dev->usb_buf[0];
		reg_w(gspca_dev, 0x00, 0x816b, Data);
		ग_लिखो_vector(gspca_dev, Clicksmart510_शेषs);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w(gspca_dev, 0, 0x8003, 0x00);

	/* चयन to video camera mode */
	reg_w(gspca_dev, 0x00, 0x8000, 0x0004);
	reg_r(gspca_dev, 0x8000, 1);
	gspca_dbg(gspca_dev, D_STREAM, "stop SPCA500 done reg8000: 0x%2x\n",
		  gspca_dev->usb_buf[0]);
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक i;
	अटल __u8 ffd9[] = अणु0xff, 0xd9पूर्ण;

/* frames are jpeg 4.1.1 without 0xff escape */
	अगर (data[0] == 0xff) अणु
		अगर (data[1] != 0x01) अणु	/* drop packet */
/*			gspca_dev->last_packet_type = DISCARD_PACKET; */
			वापस;
		पूर्ण
		gspca_frame_add(gspca_dev, LAST_PACKET,
					ffd9, 2);

		/* put the JPEG header in the new frame */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sd->jpeg_hdr, JPEG_HDR_SZ);

		data += SPCA500_OFFSET_DATA;
		len -= SPCA500_OFFSET_DATA;
	पूर्ण अन्यथा अणु
		data += 1;
		len -= 1;
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

अटल व्योम setbrightness(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w(gspca_dev, 0x00, 0x8167,
			(__u8) (val - 128));
पूर्ण

अटल व्योम setcontrast(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w(gspca_dev, 0x00, 0x8168, val);
पूर्ण

अटल व्योम setcolors(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w(gspca_dev, 0x00, 0x8169, val);
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
	v4l2_ctrl_handler_init(hdl, 3);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 127);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 63, 1, 31);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_SATURATION, 0, 63, 1, 31);

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
	अणुUSB_DEVICE(0x040a, 0x0300), .driver_info = KodakEZ200पूर्ण,
	अणुUSB_DEVICE(0x041e, 0x400a), .driver_info = CreativePCCam300पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0890), .driver_info = LogitechTravelerपूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0900), .driver_info = LogitechClickSmart310पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0901), .driver_info = LogitechClickSmart510पूर्ण,
	अणुUSB_DEVICE(0x04a5, 0x300c), .driver_info = BenqDC1016पूर्ण,
	अणुUSB_DEVICE(0x04fc, 0x7333), .driver_info = PalmPixDC85पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc200), .driver_info = MustekGsmart300पूर्ण,
	अणुUSB_DEVICE(0x055f, 0xc220), .driver_info = Gsmarपंचांगiniपूर्ण,
	अणुUSB_DEVICE(0x06bd, 0x0404), .driver_info = AgfaCl20पूर्ण,
	अणुUSB_DEVICE(0x06be, 0x0800), .driver_info = Opसमयdiaपूर्ण,
	अणुUSB_DEVICE(0x084d, 0x0003), .driver_info = DLinkDSC350पूर्ण,
	अणुUSB_DEVICE(0x08ca, 0x0103), .driver_info = AiptekPocketDVपूर्ण,
	अणुUSB_DEVICE(0x2899, 0x012c), .driver_info = ToptroIndusपूर्ण,
	अणुUSB_DEVICE(0x8086, 0x0630), .driver_info = IntelPocketPCCameraपूर्ण,
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
