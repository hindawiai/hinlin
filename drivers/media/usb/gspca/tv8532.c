<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Quickcam cameras initialization data
 *
 * V4L2 by Jean-Francois Moine <http://moinejf.मुक्त.fr>
 */
#घोषणा MODULE_NAME "tv8532"

#समावेश "gspca.h"

MODULE_AUTHOR("Michel Xhaard <mxhaard@users.sourceforge.net>");
MODULE_DESCRIPTION("TV8532 USB Camera Driver");
MODULE_LICENSE("GPL");

/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */

	__u8 packet;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat sअगर_mode[] = अणु
	अणु176, 144, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 176,
		.sizeimage = 176 * 144,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1पूर्ण,
	अणु352, 288, V4L2_PIX_FMT_SBGGR8, V4L2_FIELD_NONE,
		.bytesperline = 352,
		.sizeimage = 352 * 288,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 0पूर्ण,
पूर्ण;

/* TV-8532A (ICM532A) रेजिस्टरs (LE) */
#घोषणा R00_PART_CONTROL 0x00
#घोषणा		LATENT_CHANGE	0x80
#घोषणा		EXPO_CHANGE	0x04
#घोषणा R01_TIMING_CONTROL_LOW 0x01
#घोषणा		CMD_EEprom_Open 0x30
#घोषणा		CMD_EEprom_Close 0x29
#घोषणा R03_TABLE_ADDR 0x03
#घोषणा R04_WTRAM_DATA_L 0x04
#घोषणा R05_WTRAM_DATA_M 0x05
#घोषणा R06_WTRAM_DATA_H 0x06
#घोषणा R07_TABLE_LEN	0x07
#घोषणा R08_RAM_WRITE_ACTION 0x08
#घोषणा R0C_AD_WIDTHL	0x0c
#घोषणा R0D_AD_WIDTHH	0x0d
#घोषणा R0E_AD_HEIGHTL	0x0e
#घोषणा R0F_AD_HEIGHTH	0x0f
#घोषणा R10_AD_COL_BEGINL 0x10
#घोषणा R11_AD_COL_BEGINH 0x11
#घोषणा		MIRROR		0x04	/* [10] */
#घोषणा R14_AD_ROW_BEGINL 0x14
#घोषणा R15_AD_ROWBEGINH  0x15
#घोषणा R1C_AD_EXPOSE_TIMEL 0x1c
#घोषणा R20_GAIN_G1L	0x20
#घोषणा R21_GAIN_G1H	0x21
#घोषणा R22_GAIN_RL	0x22
#घोषणा R23_GAIN_RH	0x23
#घोषणा R24_GAIN_BL	0x24
#घोषणा R25_GAIN_BH	0x25
#घोषणा R26_GAIN_G2L	0x26
#घोषणा R27_GAIN_G2H	0x27
#घोषणा R28_QUANT	0x28
#घोषणा R29_LINE	0x29
#घोषणा R2C_POLARITY	0x2c
#घोषणा R2D_POINT	0x2d
#घोषणा R2E_POINTH	0x2e
#घोषणा R2F_POINTB	0x2f
#घोषणा R30_POINTBH	0x30
#घोषणा R31_UPD		0x31
#घोषणा R2A_HIGH_BUDGET 0x2a
#घोषणा R2B_LOW_BUDGET	0x2b
#घोषणा R34_VID		0x34
#घोषणा R35_VIDH	0x35
#घोषणा R36_PID		0x36
#घोषणा R37_PIDH	0x37
#घोषणा R39_Test1	0x39		/* GPIO */
#घोषणा R3B_Test3	0x3b		/* GPIO */
#घोषणा R83_AD_IDH	0x83
#घोषणा R91_AD_SLOPEREG 0x91
#घोषणा R94_AD_BITCONTROL 0x94

अटल स्थिर u8 eeprom_data[][3] = अणु
/*	dataH dataM dataL */
	अणु0x01, 0x00, 0x01पूर्ण,
	अणु0x01, 0x80, 0x11पूर्ण,
	अणु0x05, 0x00, 0x14पूर्ण,
	अणु0x05, 0x00, 0x1cपूर्ण,
	अणु0x0d, 0x00, 0x1eपूर्ण,
	अणु0x05, 0x00, 0x1fपूर्ण,
	अणु0x05, 0x05, 0x19पूर्ण,
	अणु0x05, 0x01, 0x1bपूर्ण,
	अणु0x05, 0x09, 0x1eपूर्ण,
	अणु0x0d, 0x89, 0x2eपूर्ण,
	अणु0x05, 0x89, 0x2fपूर्ण,
	अणु0x05, 0x0d, 0xd9पूर्ण,
	अणु0x05, 0x09, 0xf1पूर्ण,
पूर्ण;


/* ग_लिखो 1 byte */
अटल व्योम reg_w1(काष्ठा gspca_dev *gspca_dev,
		  __u16 index, __u8 value)
अणु
	gspca_dev->usb_buf[0] = value;
	usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x02,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,	/* value */
			index, gspca_dev->usb_buf, 1, 500);
पूर्ण

/* ग_लिखो 2 bytes */
अटल व्योम reg_w2(काष्ठा gspca_dev *gspca_dev,
		  u16 index, u16 value)
अणु
	gspca_dev->usb_buf[0] = value;
	gspca_dev->usb_buf[1] = value >> 8;
	usb_control_msg(gspca_dev->dev,
			usb_sndctrlpipe(gspca_dev->dev, 0),
			0x02,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0,	/* value */
			index, gspca_dev->usb_buf, 2, 500);
पूर्ण

अटल व्योम tv_8532WriteEEprom(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक i;

	reg_w1(gspca_dev, R01_TIMING_CONTROL_LOW, CMD_EEprom_Open);
	क्रम (i = 0; i < ARRAY_SIZE(eeprom_data); i++) अणु
		reg_w1(gspca_dev, R03_TABLE_ADDR, i);
		reg_w1(gspca_dev, R04_WTRAM_DATA_L, eeprom_data[i][2]);
		reg_w1(gspca_dev, R05_WTRAM_DATA_M, eeprom_data[i][1]);
		reg_w1(gspca_dev, R06_WTRAM_DATA_H, eeprom_data[i][0]);
		reg_w1(gspca_dev, R08_RAM_WRITE_ACTION, 0);
	पूर्ण
	reg_w1(gspca_dev, R07_TABLE_LEN, i);
	reg_w1(gspca_dev, R01_TIMING_CONTROL_LOW, CMD_EEprom_Close);
पूर्ण

/* this function is called at probe समय */
अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा cam *cam;

	cam = &gspca_dev->cam;
	cam->cam_mode = sअगर_mode;
	cam->nmodes = ARRAY_SIZE(sअगर_mode);

	वापस 0;
पूर्ण

अटल व्योम tv_8532_setReg(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w1(gspca_dev, R3B_Test3, 0x0a);	/* Test0Sel = 10 */
	/******************************************************/
	reg_w1(gspca_dev, R0E_AD_HEIGHTL, 0x90);
	reg_w1(gspca_dev, R0F_AD_HEIGHTH, 0x01);
	reg_w2(gspca_dev, R1C_AD_EXPOSE_TIMEL, 0x018f);
	reg_w1(gspca_dev, R10_AD_COL_BEGINL, 0x44);
						/* begin active line */
	reg_w1(gspca_dev, R11_AD_COL_BEGINH, 0x00);
						/* mirror and digital gain */
	reg_w1(gspca_dev, R14_AD_ROW_BEGINL, 0x0a);

	reg_w1(gspca_dev, R94_AD_BITCONTROL, 0x02);
	reg_w1(gspca_dev, R91_AD_SLOPEREG, 0x00);
	reg_w1(gspca_dev, R00_PART_CONTROL, LATENT_CHANGE | EXPO_CHANGE);
						/* = 0x84 */
पूर्ण

/* this function is called at probe and resume समय */
अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	tv_8532WriteEEprom(gspca_dev);

	वापस 0;
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w2(gspca_dev, R1C_AD_EXPOSE_TIMEL, val);
	reg_w1(gspca_dev, R00_PART_CONTROL, LATENT_CHANGE | EXPO_CHANGE);
						/* 0x84 */
पूर्ण

अटल व्योम setgain(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	reg_w2(gspca_dev, R20_GAIN_G1L, val);
	reg_w2(gspca_dev, R22_GAIN_RL, val);
	reg_w2(gspca_dev, R24_GAIN_BL, val);
	reg_w2(gspca_dev, R26_GAIN_G2L, val);
पूर्ण

/* -- start the camera -- */
अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	reg_w1(gspca_dev, R0C_AD_WIDTHL, 0xe8);		/* 0x20; 0x0c */
	reg_w1(gspca_dev, R0D_AD_WIDTHH, 0x03);

	/************************************************/
	reg_w1(gspca_dev, R28_QUANT, 0x90);
					/* 0x72 compressed mode 0x28 */
	अगर (gspca_dev->cam.cam_mode[(पूर्णांक) gspca_dev->curr_mode].priv) अणु
		/* 176x144 */
		reg_w1(gspca_dev, R29_LINE, 0x41);
					/* CIF - 2 lines/packet */
	पूर्ण अन्यथा अणु
		/* 352x288 */
		reg_w1(gspca_dev, R29_LINE, 0x81);
					/* CIF - 2 lines/packet */
	पूर्ण
	/************************************************/
	reg_w1(gspca_dev, R2C_POLARITY, 0x10);		/* slow घड़ी */
	reg_w1(gspca_dev, R2D_POINT, 0x14);
	reg_w1(gspca_dev, R2E_POINTH, 0x01);
	reg_w1(gspca_dev, R2F_POINTB, 0x12);
	reg_w1(gspca_dev, R30_POINTBH, 0x01);

	tv_8532_setReg(gspca_dev);

	/************************************************/
	reg_w1(gspca_dev, R31_UPD, 0x01);	/* update रेजिस्टरs */
	msleep(200);
	reg_w1(gspca_dev, R31_UPD, 0x00);	/* end update */

	gspca_dev->empty_packet = 0;		/* check the empty packets */
	sd->packet = 0;				/* ignore the first packets */

	वापस 0;
पूर्ण

अटल व्योम sd_stopN(काष्ठा gspca_dev *gspca_dev)
अणु
	reg_w1(gspca_dev, R3B_Test3, 0x0b);	/* Test0Sel = 11 = GPIO */
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,			/* isoc packet */
			पूर्णांक len)			/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक packet_type0, packet_type1;

	packet_type0 = packet_type1 = INTER_PACKET;
	अगर (gspca_dev->empty_packet) अणु
		gspca_dev->empty_packet = 0;
		sd->packet = gspca_dev->pixfmt.height / 2;
		packet_type0 = FIRST_PACKET;
	पूर्ण अन्यथा अगर (sd->packet == 0)
		वापस;			/* 2 more lines in 352x288 ! */
	sd->packet--;
	अगर (sd->packet == 0)
		packet_type1 = LAST_PACKET;

	/* each packet contains:
	 * - header 2 bytes
	 * - RGRG line
	 * - 4 bytes
	 * - GBGB line
	 * - 4 bytes
	 */
	gspca_frame_add(gspca_dev, packet_type0,
			data + 2, gspca_dev->pixfmt.width);
	gspca_frame_add(gspca_dev, packet_type1,
			data + gspca_dev->pixfmt.width + 5,
			gspca_dev->pixfmt.width);
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		setexposure(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		setgain(gspca_dev, ctrl->val);
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
	v4l2_ctrl_handler_init(hdl, 2);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 0x18f, 1, 0x18f);
	v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 0x7ff, 1, 0x100);

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
	अणुUSB_DEVICE(0x046d, 0x0920)पूर्ण,
	अणुUSB_DEVICE(0x046d, 0x0921)पूर्ण,
	अणुUSB_DEVICE(0x0545, 0x808b)पूर्ण,
	अणुUSB_DEVICE(0x0545, 0x8333)पूर्ण,
	अणुUSB_DEVICE(0x0923, 0x010f)पूर्ण,
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
