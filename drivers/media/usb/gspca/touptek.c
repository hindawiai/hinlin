<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ToupTek UCMOS / AmScope MU series camera driver
 * TODO: contrast with ScopeTek / AmScope MDC cameras
 *
 * Copyright (C) 2012-2014 John McMaster <JohnDMcMaster@gmail.com>
 *
 * Special thanks to Bushing क्रम helping with the decrypt algorithm and
 * Sean O'Sullivan / the Rensselaer Center क्रम Open Source
 * Software (RCOS) क्रम helping me learn kernel development
 */

#समावेश "gspca.h"

#घोषणा MODULE_NAME "touptek"

MODULE_AUTHOR("John McMaster");
MODULE_DESCRIPTION("ToupTek UCMOS / Amscope MU microscope camera driver");
MODULE_LICENSE("GPL");

/*
 * Exposure reg is linear with exposure समय
 * Exposure (sec), E (reg)
 * 0.000400, 0x0002
 * 0.001000, 0x0005
 * 0.005000, 0x0019
 * 0.020000, 0x0064
 * 0.080000, 0x0190
 * 0.400000, 0x07D0
 * 1.000000, 0x1388
 * 2.000000, 0x2710
 *
 * Three gain stages
 * 0x1000: master channel enable bit
 * 0x007F: low gain bits
 * 0x0080: medium gain bit
 * 0x0100: high gain bit
 * gain = enable * (1 + regH) * (1 + regM) * z * regL
 *
 * Gain implementation
 * Want to करो something similar to mt9v011.c's set_balance
 *
 * Gain करोes not vary with resolution (checked 640x480 vs 1600x1200)
 *
 * Constant derivation:
 *
 * Raw data:
 * Gain,   GTOP,   B,	  R,	  GBOT
 * 1.00,   0x105C, 0x1068, 0x10C8, 0x105C
 * 1.20,   0x106E, 0x107E, 0x10D6, 0x106E
 * 1.40,   0x10C0, 0x10CA, 0x10E5, 0x10C0
 * 1.60,   0x10C9, 0x10D4, 0x10F3, 0x10C9
 * 1.80,   0x10D2, 0x10DE, 0x11C1, 0x10D2
 * 2.00,   0x10DC, 0x10E9, 0x11C8, 0x10DC
 * 2.20,   0x10E5, 0x10F3, 0x11CF, 0x10E5
 * 2.40,   0x10EE, 0x10FE, 0x11D7, 0x10EE
 * 2.60,   0x10F7, 0x11C4, 0x11DE, 0x10F7
 * 2.80,   0x11C0, 0x11CA, 0x11E5, 0x11C0
 * 3.00,   0x11C5, 0x11CF, 0x11ED, 0x11C5
 *
 * zR = 0.0069605943152454778
 *	about 3/431 = 0.0069605568445475635
 * zB = 0.0095695970695970703
 *	about 6/627 = 0.0095693779904306216
 * zG = 0.010889328063241107
 *	about 6/551 = 0.010889292196007259
 * about 10 bits क्रम स्थिरant + 7 bits क्रम value => at least 17 bit
 * पूर्णांकermediate with 32 bit पूर्णांकs should be fine क्रम overflow etc
 * Essentially gains are in range 0-0x001FF
 *
 * However, V4L expects a मुख्य gain channel + R and B balance
 * To keep things simple क्रम now saturate the values of balance is too high/low
 * This isn't really ideal but easy way to fit the Linux model
 *
 * Converted using gain model turns out to be quite linear:
 * Gain, GTOP, B, R, GBOT
 * 1.00, 92, 104, 144, 92
 * 1.20, 110, 126, 172, 110
 * 1.40, 128, 148, 202, 128
 * 1.60, 146, 168, 230, 146
 * 1.80, 164, 188, 260, 164
 * 2.00, 184, 210, 288, 184
 * 2.20, 202, 230, 316, 202
 * 2.40, 220, 252, 348, 220
 * 2.60, 238, 272, 376, 238
 * 2.80, 256, 296, 404, 256
 * 3.00, 276, 316, 436, 276
 *
 * Maximum gain is 0x7FF * 2 * 2 => 0x1FFC (8188)
 * or about 13 effective bits of gain
 * The highest the commercial driver goes in my setup 436
 * However, because could *maybe* damage circuits
 * limit the gain until have a reason to go higher
 * Solution: gain clipped and warning emitted
 */
#घोषणा GAIN_MAX		511

/* Frame sync is a लघु पढ़ो */
#घोषणा BULK_SIZE		0x4000

/* MT9E001 reg names to give a rough approximation */
#घोषणा REG_COARSE_INTEGRATION_TIME_	0x3012
#घोषणा REG_GROUPED_PARAMETER_HOLD_	0x3022
#घोषणा REG_MODE_SELECT			0x0100
#घोषणा REG_OP_SYS_CLK_DIV		0x030A
#घोषणा REG_VT_SYS_CLK_DIV		0x0302
#घोषणा REG_PRE_PLL_CLK_DIV		0x0304
#घोषणा REG_VT_PIX_CLK_DIV		0x0300
#घोषणा REG_OP_PIX_CLK_DIV		0x0308
#घोषणा REG_PLL_MULTIPLIER		0x0306
#घोषणा REG_COARSE_INTEGRATION_TIME_	0x3012
#घोषणा REG_FRAME_LENGTH_LINES		0x0340
#घोषणा REG_FRAME_LENGTH_LINES_		0x300A
#घोषणा REG_GREEN1_GAIN			0x3056
#घोषणा REG_GREEN2_GAIN			0x305C
#घोषणा REG_GROUPED_PARAMETER_HOLD	0x0104
#घोषणा REG_LINE_LENGTH_PCK_		0x300C
#घोषणा REG_MODE_SELECT			0x0100
#घोषणा REG_PLL_MULTIPLIER		0x0306
#घोषणा REG_READ_MODE			0x3040
#घोषणा REG_BLUE_GAIN			0x3058
#घोषणा REG_RED_GAIN			0x305A
#घोषणा REG_RESET_REGISTER		0x301A
#घोषणा REG_SCALE_M			0x0404
#घोषणा REG_SCALING_MODE		0x0400
#घोषणा REG_SOFTWARE_RESET		0x0103
#घोषणा REG_X_ADDR_END			0x0348
#घोषणा REG_X_ADDR_START		0x0344
#घोषणा REG_X_ADDR_START		0x0344
#घोषणा REG_X_OUTPUT_SIZE		0x034C
#घोषणा REG_Y_ADDR_END			0x034A
#घोषणा REG_Y_ADDR_START		0x0346
#घोषणा REG_Y_OUTPUT_SIZE		0x034E


/* specअगरic webcam descriptor */
काष्ठा sd अणु
	काष्ठा gspca_dev gspca_dev;	/* !! must be the first item */
	/* How many bytes this frame */
	अचिन्हित पूर्णांक this_f;

	/*
	Device has separate gains क्रम each Bayer quadrant
	V4L supports master gain which is referenced to G1/G2 and supplies
	inभागidual balance controls क्रम R/B
	*/
	काष्ठा v4l2_ctrl *blue;
	काष्ठा v4l2_ctrl *red;
पूर्ण;

/* Used to simplअगरy reg ग_लिखो error handling */
काष्ठा cmd अणु
	u16 value;
	u16 index;
पूर्ण;

अटल स्थिर काष्ठा v4l2_pix_क्रमmat vga_mode[] = अणु
	अणु800, 600,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.bytesperline = 800,
		.sizeimage = 800 * 600,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु1600, 1200,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.bytesperline = 1600,
		.sizeimage = 1600 * 1200,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
	अणु3264, 2448,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.bytesperline = 3264,
		.sizeimage = 3264 * 2448,
		.colorspace = V4L2_COLORSPACE_SRGBपूर्ण,
पूर्ण;

/*
 * As there's no known frame sync, the only way to keep synced is to try hard
 * to never miss any packets
 */
#अगर MAX_NURBS < 4
#त्रुटि "Not enough URBs in the gspca table"
#पूर्ण_अगर

अटल पूर्णांक val_reply(काष्ठा gspca_dev *gspca_dev, स्थिर अक्षर *reply, पूर्णांक rc)
अणु
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "reply has error %d\n", rc);
		वापस -EIO;
	पूर्ण
	अगर (rc != 1) अणु
		gspca_err(gspca_dev, "Bad reply size %d\n", rc);
		वापस -EIO;
	पूर्ण
	अगर (reply[0] != 0x08) अणु
		gspca_err(gspca_dev, "Bad reply 0x%02x\n", (पूर्णांक)reply[0]);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम reg_w(काष्ठा gspca_dev *gspca_dev, u16 value, u16 index)
अणु
	अक्षर *buff = gspca_dev->usb_buf;
	पूर्णांक rc;

	gspca_dbg(gspca_dev, D_USBO,
		  "reg_w bReq=0x0B, bReqT=0xC0, wVal=0x%04X, wInd=0x%04X\n\n",
		  value, index);
	rc = usb_control_msg(gspca_dev->dev, usb_rcvctrlpipe(gspca_dev->dev, 0),
		0x0B, 0xC0, value, index, buff, 1, 500);
	gspca_dbg(gspca_dev, D_USBO, "rc=%d, ret={0x%02x}\n", rc, (पूर्णांक)buff[0]);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "Failed reg_w(0x0B, 0xC0, 0x%04X, 0x%04X) w/ rc %d\n",
			  value, index, rc);
		gspca_dev->usb_err = rc;
		वापस;
	पूर्ण
	अगर (val_reply(gspca_dev, buff, rc)) अणु
		gspca_err(gspca_dev, "Bad reply to reg_w(0x0B, 0xC0, 0x%04X, 0x%04X\n",
			  value, index);
		gspca_dev->usb_err = -EIO;
	पूर्ण
पूर्ण

अटल व्योम reg_w_buf(काष्ठा gspca_dev *gspca_dev,
		स्थिर काष्ठा cmd *p, पूर्णांक l)
अणु
	करो अणु
		reg_w(gspca_dev, p->value, p->index);
		p++;
	पूर्ण जबतक (--l > 0);
पूर्ण

अटल व्योम setexposure(काष्ठा gspca_dev *gspca_dev, s32 val)
अणु
	u16 value;
	अचिन्हित पूर्णांक w = gspca_dev->pixfmt.width;

	अगर (w == 800)
		value = val * 5;
	अन्यथा अगर (w == 1600)
		value = val * 3;
	अन्यथा अगर (w == 3264)
		value = val * 3 / 2;
	अन्यथा अणु
		gspca_err(gspca_dev, "Invalid width %u\n", w);
		gspca_dev->usb_err = -EINVAL;
		वापस;
	पूर्ण
	gspca_dbg(gspca_dev, D_STREAM, "exposure: 0x%04X ms\n\n", value);
	/* Wonder अगर there's a good reason क्रम sending it twice */
	/* probably not but leave it in because...why not */
	reg_w(gspca_dev, value, REG_COARSE_INTEGRATION_TIME_);
	reg_w(gspca_dev, value, REG_COARSE_INTEGRATION_TIME_);
पूर्ण

अटल पूर्णांक gainअगरy(पूर्णांक in)
अणु
	/*
	 * TODO: check अगर there are any issues with corner हालs
	 * 0x000 (0):0x07F (127): regL
	 * 0x080 (128) - 0x0FF (255): regM, regL
	 * 0x100 (256) - max: regH, regM, regL
	 */
	अगर (in <= 0x7F)
		वापस 0x1000 | in;
	अन्यथा अगर (in <= 0xFF)
		वापस 0x1080 | in / 2;
	अन्यथा
		वापस 0x1180 | in / 4;
पूर्ण

अटल व्योम setggain(काष्ठा gspca_dev *gspca_dev, u16 global_gain)
अणु
	u16 normalized;

	normalized = gainअगरy(global_gain);
	gspca_dbg(gspca_dev, D_STREAM, "gain G1/G2 (0x%04X): 0x%04X (src 0x%04X)\n\n",
		  REG_GREEN1_GAIN,
		  normalized, global_gain);

	reg_w(gspca_dev, normalized, REG_GREEN1_GAIN);
	reg_w(gspca_dev, normalized, REG_GREEN2_GAIN);
पूर्ण

अटल व्योम setbgain(काष्ठा gspca_dev *gspca_dev,
		u16 gain, u16 global_gain)
अणु
	u16 normalized;

	normalized = global_gain +
		((u32)global_gain) * gain / GAIN_MAX;
	अगर (normalized > GAIN_MAX) अणु
		gspca_dbg(gspca_dev, D_STREAM, "Truncating blue 0x%04X w/ value 0x%04X\n\n",
			  GAIN_MAX, normalized);
		normalized = GAIN_MAX;
	पूर्ण
	normalized = gainअगरy(normalized);
	gspca_dbg(gspca_dev, D_STREAM, "gain B (0x%04X): 0x%04X w/ source 0x%04X\n\n",
		  REG_BLUE_GAIN, normalized, gain);

	reg_w(gspca_dev, normalized, REG_BLUE_GAIN);
पूर्ण

अटल व्योम setrgain(काष्ठा gspca_dev *gspca_dev,
		u16 gain, u16 global_gain)
अणु
	u16 normalized;

	normalized = global_gain +
		((u32)global_gain) * gain / GAIN_MAX;
	अगर (normalized > GAIN_MAX) अणु
		gspca_dbg(gspca_dev, D_STREAM, "Truncating gain 0x%04X w/ value 0x%04X\n\n",
			  GAIN_MAX, normalized);
		normalized = GAIN_MAX;
	पूर्ण
	normalized = gainअगरy(normalized);
	gspca_dbg(gspca_dev, D_STREAM, "gain R (0x%04X): 0x%04X w / source 0x%04X\n\n",
		  REG_RED_GAIN, normalized, gain);

	reg_w(gspca_dev, normalized, REG_RED_GAIN);
पूर्ण

अटल व्योम configure_wh(काष्ठा gspca_dev *gspca_dev)
अणु
	अचिन्हित पूर्णांक w = gspca_dev->pixfmt.width;

	gspca_dbg(gspca_dev, D_STREAM, "configure_wh\n\n");

	अगर (w == 800) अणु
		अटल स्थिर काष्ठा cmd reg_init_res[] = अणु
			अणु0x0060, REG_X_ADDR_STARTपूर्ण,
			अणु0x0CD9, REG_X_ADDR_ENDपूर्ण,
			अणु0x0036, REG_Y_ADDR_STARTपूर्ण,
			अणु0x098F, REG_Y_ADDR_ENDपूर्ण,
			अणु0x07C7, REG_READ_MODEपूर्ण,
		पूर्ण;

		reg_w_buf(gspca_dev,
			       reg_init_res, ARRAY_SIZE(reg_init_res));
	पूर्ण अन्यथा अगर (w == 1600) अणु
		अटल स्थिर काष्ठा cmd reg_init_res[] = अणु
			अणु0x009C, REG_X_ADDR_STARTपूर्ण,
			अणु0x0D19, REG_X_ADDR_ENDपूर्ण,
			अणु0x0068, REG_Y_ADDR_STARTपूर्ण,
			अणु0x09C5, REG_Y_ADDR_ENDपूर्ण,
			अणु0x06C3, REG_READ_MODEपूर्ण,
		पूर्ण;

		reg_w_buf(gspca_dev,
			       reg_init_res, ARRAY_SIZE(reg_init_res));
	पूर्ण अन्यथा अगर (w == 3264) अणु
		अटल स्थिर काष्ठा cmd reg_init_res[] = अणु
			अणु0x00E8, REG_X_ADDR_STARTपूर्ण,
			अणु0x0DA7, REG_X_ADDR_ENDपूर्ण,
			अणु0x009E, REG_Y_ADDR_STARTपूर्ण,
			अणु0x0A2D, REG_Y_ADDR_ENDपूर्ण,
			अणु0x0241, REG_READ_MODEपूर्ण,
		पूर्ण;

		reg_w_buf(gspca_dev,
			       reg_init_res, ARRAY_SIZE(reg_init_res));
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "bad width %u\n", w);
		gspca_dev->usb_err = -EINVAL;
		वापस;
	पूर्ण

	reg_w(gspca_dev, 0x0000, REG_SCALING_MODE);
	reg_w(gspca_dev, 0x0010, REG_SCALE_M);
	reg_w(gspca_dev, w, REG_X_OUTPUT_SIZE);
	reg_w(gspca_dev, gspca_dev->pixfmt.height, REG_Y_OUTPUT_SIZE);

	अगर (w == 800) अणु
		reg_w(gspca_dev, 0x0384, REG_FRAME_LENGTH_LINES_);
		reg_w(gspca_dev, 0x0960, REG_LINE_LENGTH_PCK_);
	पूर्ण अन्यथा अगर (w == 1600) अणु
		reg_w(gspca_dev, 0x0640, REG_FRAME_LENGTH_LINES_);
		reg_w(gspca_dev, 0x0FA0, REG_LINE_LENGTH_PCK_);
	पूर्ण अन्यथा अगर (w == 3264) अणु
		reg_w(gspca_dev, 0x0B4B, REG_FRAME_LENGTH_LINES_);
		reg_w(gspca_dev, 0x1F40, REG_LINE_LENGTH_PCK_);
	पूर्ण अन्यथा अणु
		gspca_err(gspca_dev, "bad width %u\n", w);
		gspca_dev->usb_err = -EINVAL;
		वापस;
	पूर्ण
पूर्ण

/* Packets that were encrypted, no idea अगर the grouping is signअगरicant */
अटल व्योम configure_encrypted(काष्ठा gspca_dev *gspca_dev)
अणु
	अटल स्थिर काष्ठा cmd reg_init_begin[] = अणु
		अणु0x0100, REG_SOFTWARE_RESETपूर्ण,
		अणु0x0000, REG_MODE_SELECTपूर्ण,
		अणु0x0100, REG_GROUPED_PARAMETER_HOLDपूर्ण,
		अणु0x0004, REG_VT_PIX_CLK_DIVपूर्ण,
		अणु0x0001, REG_VT_SYS_CLK_DIVपूर्ण,
		अणु0x0008, REG_OP_PIX_CLK_DIVपूर्ण,
		अणु0x0001, REG_OP_SYS_CLK_DIVपूर्ण,
		अणु0x0004, REG_PRE_PLL_CLK_DIVपूर्ण,
		अणु0x0040, REG_PLL_MULTIPLIERपूर्ण,
		अणु0x0000, REG_GROUPED_PARAMETER_HOLDपूर्ण,
		अणु0x0100, REG_GROUPED_PARAMETER_HOLDपूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा cmd reg_init_end[] = अणु
		अणु0x0000, REG_GROUPED_PARAMETER_HOLDपूर्ण,
		अणु0x0301, 0x31AEपूर्ण,
		अणु0x0805, 0x3064पूर्ण,
		अणु0x0071, 0x3170पूर्ण,
		अणु0x10DE, REG_RESET_REGISTERपूर्ण,
		अणु0x0000, REG_MODE_SELECTपूर्ण,
		अणु0x0010, REG_PLL_MULTIPLIERपूर्ण,
		अणु0x0100, REG_MODE_SELECTपूर्ण,
	पूर्ण;

	gspca_dbg(gspca_dev, D_STREAM, "Encrypted begin, w = %u\n\n",
		  gspca_dev->pixfmt.width);
	reg_w_buf(gspca_dev, reg_init_begin, ARRAY_SIZE(reg_init_begin));
	configure_wh(gspca_dev);
	reg_w_buf(gspca_dev, reg_init_end, ARRAY_SIZE(reg_init_end));
	reg_w(gspca_dev, 0x0100, REG_GROUPED_PARAMETER_HOLD);
	reg_w(gspca_dev, 0x0000, REG_GROUPED_PARAMETER_HOLD);

	gspca_dbg(gspca_dev, D_STREAM, "Encrypted end\n\n");
पूर्ण

अटल पूर्णांक configure(काष्ठा gspca_dev *gspca_dev)
अणु
	पूर्णांक rc;
	अक्षर *buff = gspca_dev->usb_buf;

	gspca_dbg(gspca_dev, D_STREAM, "configure()\n\n");

	/*
	 * First driver sets a sort of encryption key
	 * A number of futur requests of this type have wValue and wIndex
	 * encrypted as follows:
	 * -Compute key = this wValue rotate left by 4 bits
	 *	(decrypt.py rotates right because we are decrypting)
	 * -Later packets encrypt packets by XOR'ing with key
	 *	XOR encrypt/decrypt is symmetrical
	 *	wValue, and wIndex are encrypted
	 *	bRequest is not and bRequestType is always 0xC0
	 *		This allows resyncing अगर key is unknown?
	 * By setting 0 we XOR with 0 and the shअगरting and XOR drops out
	 */
	rc = usb_control_msg(gspca_dev->dev, usb_rcvctrlpipe(gspca_dev->dev, 0),
			     0x16, 0xC0, 0x0000, 0x0000, buff, 2, 500);
	अगर (val_reply(gspca_dev, buff, rc)) अणु
		gspca_err(gspca_dev, "failed key req\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Next करोes some sort of 2 packet challenge / response
	 * evidence suggests its an Aपंचांगel I2C crypto part but nobody cares to
	 * look
	 * (to make sure its not cloned hardware?)
	 * Ignore: I want to work with their hardware, not clone it
	 * 16 bytes out challenge, requestType: 0x40
	 * 16 bytes in response, requestType: 0xC0
	 */

	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0001, 0x000F, शून्य, 0, 500);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "failed to replay packet 176 w/ rc %d\n",
			  rc);
		वापस rc;
	पूर्ण

	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0000, 0x000F, शून्य, 0, 500);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "failed to replay packet 178 w/ rc %d\n",
			  rc);
		वापस rc;
	पूर्ण

	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0001, 0x000F, शून्य, 0, 500);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "failed to replay packet 180 w/ rc %d\n",
			  rc);
		वापस rc;
	पूर्ण

	/*
	 * Serial number?  Doesn't seem to be required
	 * cam1: \षE6\ष0D\ष00\ष00, cam2: \ष70\ष19\ष00\ष00
	 * rc = usb_control_msg(gspca_dev->dev,
	 *			usb_rcvctrlpipe(gspca_dev->dev, 0),
	 *			0x20, 0xC0, 0x0000, 0x0000, buff, 4, 500);
	 */

	/* Large (EEPROM?) पढ़ो, skip it since no idea what to करो with it */
	gspca_dev->usb_err = 0;
	configure_encrypted(gspca_dev);
	अगर (gspca_dev->usb_err)
		वापस gspca_dev->usb_err;

	/* Omitted this by accident, करोes not work without it */
	rc = usb_control_msg(gspca_dev->dev, usb_sndctrlpipe(gspca_dev->dev, 0),
			     0x01, 0x40, 0x0003, 0x000F, शून्य, 0, 500);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "failed to replay final packet w/ rc %d\n",
			  rc);
		वापस rc;
	पूर्ण

	gspca_dbg(gspca_dev, D_STREAM, "Configure complete\n\n");
	वापस 0;
पूर्ण

अटल पूर्णांक sd_config(काष्ठा gspca_dev *gspca_dev,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);

	/* Yes we want URBs and we want them now! */
	gspca_dev->cam.no_urb_create = 0;
	gspca_dev->cam.bulk_nurbs = 4;
	/* Largest size the winकरोws driver uses */
	gspca_dev->cam.bulk_size = BULK_SIZE;
	/* Def need to use bulk transfers */
	gspca_dev->cam.bulk = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sd_start(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	पूर्णांक rc;

	sd->this_f = 0;

	rc = configure(gspca_dev);
	अगर (rc < 0) अणु
		gspca_err(gspca_dev, "Failed configure\n");
		वापस rc;
	पूर्ण
	/* First two frames have messed up gains
	Drop them to aव्योम special हालs in user apps? */
	वापस 0;
पूर्ण

अटल व्योम sd_pkt_scan(काष्ठा gspca_dev *gspca_dev,
			u8 *data,	/* isoc packet */
			पूर्णांक len)	/* iso packet length */
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	अगर (len != BULK_SIZE) अणु
		/* can we finish a frame? */
		अगर (sd->this_f + len == gspca_dev->pixfmt.sizeimage) अणु
			gspca_frame_add(gspca_dev, LAST_PACKET, data, len);
			gspca_dbg(gspca_dev, D_FRAM, "finish frame sz %u/%u w/ len %u\n\n",
				  sd->this_f, gspca_dev->pixfmt.sizeimage, len);
		/* lost some data, discard the frame */
		पूर्ण अन्यथा अणु
			gspca_frame_add(gspca_dev, DISCARD_PACKET, शून्य, 0);
			gspca_dbg(gspca_dev, D_FRAM, "abort frame sz %u/%u w/ len %u\n\n",
				  sd->this_f, gspca_dev->pixfmt.sizeimage, len);
		पूर्ण
		sd->this_f = 0;
	पूर्ण अन्यथा अणु
		अगर (sd->this_f == 0)
			gspca_frame_add(gspca_dev, FIRST_PACKET, data, len);
		अन्यथा
			gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
		sd->this_f += len;
	पूर्ण
पूर्ण

अटल पूर्णांक sd_init(काष्ठा gspca_dev *gspca_dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sd_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	gspca_dev->usb_err = 0;

	अगर (!gspca_dev->streaming)
		वापस 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_EXPOSURE:
		setexposure(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_GAIN:
		/* gspca_dev->gain स्वतःmatically updated */
		setggain(gspca_dev, gspca_dev->gain->val);
		अवरोध;
	हाल V4L2_CID_BLUE_BALANCE:
		sd->blue->val = ctrl->val;
		setbgain(gspca_dev, sd->blue->val, gspca_dev->gain->val);
		अवरोध;
	हाल V4L2_CID_RED_BALANCE:
		sd->red->val = ctrl->val;
		setrgain(gspca_dev, sd->red->val, gspca_dev->gain->val);
		अवरोध;
	पूर्ण
	वापस gspca_dev->usb_err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops sd_ctrl_ops = अणु
	.s_ctrl = sd_s_ctrl,
पूर्ण;

अटल पूर्णांक sd_init_controls(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);

	gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
	/* Mostly limited by URB समयouts */
	/* XXX: make dynamic based on frame rate? */
		V4L2_CID_EXPOSURE, 0, 800, 1, 350);
	gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 511, 1, 128);
	sd->blue = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 1023, 1, 80);
	sd->red = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 1023, 1, 295);

	अगर (hdl->error) अणु
		gspca_err(gspca_dev, "Could not initialize controls\n");
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
	.pkt_scan = sd_pkt_scan,
पूर्ण;

/* Table of supported USB devices */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	/* Commented out devices should be related */
	/* AS: AmScope, TT: ToupTek */
	/* अणु USB_DEVICE(0x0547, 0x6035) पूर्ण,  TT UCMOS00350KPA */
	/* अणु USB_DEVICE(0x0547, 0x6130) पूर्ण,  TT UCMOS01300KPA */
	/* अणु USB_DEVICE(0x0547, 0x6200) पूर्ण,  TT UCMOS02000KPA */
	/* अणु USB_DEVICE(0x0547, 0x6310) पूर्ण,  TT UCMOS03100KPA */
	/* अणु USB_DEVICE(0x0547, 0x6510) पूर्ण,  TT UCMOS05100KPA */
	/* अणु USB_DEVICE(0x0547, 0x6800) पूर्ण,  TT UCMOS08000KPA */
	/* अणु USB_DEVICE(0x0547, 0x6801) पूर्ण,  TT UCMOS08000KPB */
	अणु USB_DEVICE(0x0547, 0x6801) पूर्ण, /* TT UCMOS08000KPB, AS MU800 */
	/* अणु USB_DEVICE(0x0547, 0x6900) पूर्ण,  TT UCMOS09000KPA */
	/* अणु USB_DEVICE(0x0547, 0x6901) पूर्ण,  TT UCMOS09000KPB */
	/* अणु USB_DEVICE(0x0547, 0x6010) पूर्ण,  TT UCMOS10000KPA */
	/* अणु USB_DEVICE(0x0547, 0x6014) पूर्ण,  TT UCMOS14000KPA */
	/* अणु USB_DEVICE(0x0547, 0x6131) पूर्ण,  TT UCMOS01300KMA */
	/* अणु USB_DEVICE(0x0547, 0x6511) पूर्ण,  TT UCMOS05100KMA */
	/* अणु USB_DEVICE(0x0547, 0x8080) पूर्ण,  TT UHCCD00800KPA */
	/* अणु USB_DEVICE(0x0547, 0x8140) पूर्ण,  TT UHCCD01400KPA */
	/* अणु USB_DEVICE(0x0547, 0x8141) पूर्ण,  TT EXCCD01400KPA */
	/* अणु USB_DEVICE(0x0547, 0x8200) पूर्ण,  TT UHCCD02000KPA */
	/* अणु USB_DEVICE(0x0547, 0x8201) पूर्ण,  TT UHCCD02000KPB */
	/* अणु USB_DEVICE(0x0547, 0x8310) पूर्ण,  TT UHCCD03100KPA */
	/* अणु USB_DEVICE(0x0547, 0x8500) पूर्ण,  TT UHCCD05000KPA */
	/* अणु USB_DEVICE(0x0547, 0x8510) पूर्ण,  TT UHCCD05100KPA */
	/* अणु USB_DEVICE(0x0547, 0x8600) पूर्ण,  TT UHCCD06000KPA */
	/* अणु USB_DEVICE(0x0547, 0x8800) पूर्ण,  TT UHCCD08000KPA */
	/* अणु USB_DEVICE(0x0547, 0x8315) पूर्ण,  TT UHCCD03150KPA */
	/* अणु USB_DEVICE(0x0547, 0x7800) पूर्ण,  TT UHCCD00800KMA */
	/* अणु USB_DEVICE(0x0547, 0x7140) पूर्ण,  TT UHCCD01400KMA */
	/* अणु USB_DEVICE(0x0547, 0x7141) पूर्ण,  TT UHCCD01400KMB */
	/* अणु USB_DEVICE(0x0547, 0x7200) पूर्ण,  TT UHCCD02000KMA */
	/* अणु USB_DEVICE(0x0547, 0x7315) पूर्ण,  TT UHCCD03150KMA */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, device_table);

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
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init sd_mod_init(व्योम)
अणु
	पूर्णांक ret;

	ret = usb_रेजिस्टर(&sd_driver);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण
अटल व्योम __निकास sd_mod_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&sd_driver);
पूर्ण

module_init(sd_mod_init);
module_निकास(sd_mod_निकास);
