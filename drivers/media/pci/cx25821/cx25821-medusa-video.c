<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "cx25821.h"
#समावेश "cx25821-medusa-video.h"
#समावेश "cx25821-biffuncs.h"

/*
 * medusa_enable_bluefield_output()
 *
 * Enable the generation of blue filed output अगर no video
 *
 */
अटल व्योम medusa_enable_bluefield_output(काष्ठा cx25821_dev *dev, पूर्णांक channel,
					   पूर्णांक enable)
अणु
	u32 value = 0;
	u32 पंचांगp = 0;
	पूर्णांक out_ctrl = OUT_CTRL1;
	पूर्णांक out_ctrl_ns = OUT_CTRL_NS;

	चयन (channel) अणु
	शेष:
	हाल VDEC_A:
		अवरोध;
	हाल VDEC_B:
		out_ctrl = VDEC_B_OUT_CTRL1;
		out_ctrl_ns = VDEC_B_OUT_CTRL_NS;
		अवरोध;
	हाल VDEC_C:
		out_ctrl = VDEC_C_OUT_CTRL1;
		out_ctrl_ns = VDEC_C_OUT_CTRL_NS;
		अवरोध;
	हाल VDEC_D:
		out_ctrl = VDEC_D_OUT_CTRL1;
		out_ctrl_ns = VDEC_D_OUT_CTRL_NS;
		अवरोध;
	हाल VDEC_E:
		out_ctrl = VDEC_E_OUT_CTRL1;
		out_ctrl_ns = VDEC_E_OUT_CTRL_NS;
		वापस;
	हाल VDEC_F:
		out_ctrl = VDEC_F_OUT_CTRL1;
		out_ctrl_ns = VDEC_F_OUT_CTRL_NS;
		वापस;
	हाल VDEC_G:
		out_ctrl = VDEC_G_OUT_CTRL1;
		out_ctrl_ns = VDEC_G_OUT_CTRL_NS;
		वापस;
	हाल VDEC_H:
		out_ctrl = VDEC_H_OUT_CTRL1;
		out_ctrl_ns = VDEC_H_OUT_CTRL_NS;
		वापस;
	पूर्ण

	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], out_ctrl, &पंचांगp);
	value &= 0xFFFFFF7F;	/* clear BLUE_FIELD_EN */
	अगर (enable)
		value |= 0x00000080;	/* set BLUE_FIELD_EN */
	cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], out_ctrl, value);

	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], out_ctrl_ns, &पंचांगp);
	value &= 0xFFFFFF7F;
	अगर (enable)
		value |= 0x00000080;	/* set BLUE_FIELD_EN */
	cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], out_ctrl_ns, value);
पूर्ण

अटल पूर्णांक medusa_initialize_ntsc(काष्ठा cx25821_dev *dev)
अणु
	पूर्णांक ret_val = 0;
	पूर्णांक i = 0;
	u32 value = 0;
	u32 पंचांगp = 0;

	क्रम (i = 0; i < MAX_DECODERS; i++) अणु
		/* set video क्रमmat NTSC-M */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				MODE_CTRL + (0x200 * i), &पंचांगp);
		value &= 0xFFFFFFF0;
		/* enable the fast locking mode bit[16] */
		value |= 0x10001;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				MODE_CTRL + (0x200 * i), value);

		/* resolution NTSC 720x480 */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				HORIZ_TIM_CTRL + (0x200 * i), &पंचांगp);
		value &= 0x00C00C00;
		value |= 0x612D0074;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				HORIZ_TIM_CTRL + (0x200 * i), value);

		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				VERT_TIM_CTRL + (0x200 * i), &पंचांगp);
		value &= 0x00C00C00;
		value |= 0x1C1E001A;	/* vblank_cnt + 2 to get camera ID */
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				VERT_TIM_CTRL + (0x200 * i), value);

		/* chroma subcarrier step size */
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				SC_STEP_SIZE + (0x200 * i), 0x43E00000);

		/* enable VIP optional active */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				OUT_CTRL_NS + (0x200 * i), &पंचांगp);
		value &= 0xFFFBFFFF;
		value |= 0x00040000;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				OUT_CTRL_NS + (0x200 * i), value);

		/* enable VIP optional active (VIP_OPT_AL) क्रम direct output. */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				OUT_CTRL1 + (0x200 * i), &पंचांगp);
		value &= 0xFFFBFFFF;
		value |= 0x00040000;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				OUT_CTRL1 + (0x200 * i), value);

		/*
		 * clear VPRES_VERT_EN bit, fixes the chroma run away problem
		 * when the input चयनing rate < 16 fields
		*/
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				MISC_TIM_CTRL + (0x200 * i), &पंचांगp);
		/* disable special play detection */
		value = setBitAtPos(value, 14);
		value = clearBitAtPos(value, 15);
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				MISC_TIM_CTRL + (0x200 * i), value);

		/* set vbi_gate_en to 0 */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DFE_CTRL1 + (0x200 * i), &पंचांगp);
		value = clearBitAtPos(value, 29);
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DFE_CTRL1 + (0x200 * i), value);

		/* Enable the generation of blue field output अगर no video */
		medusa_enable_bluefield_output(dev, i, 1);
	पूर्ण

	क्रम (i = 0; i < MAX_ENCODERS; i++) अणु
		/* NTSC hघड़ी */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_1 + (0x100 * i), &पंचांगp);
		value &= 0xF000FC00;
		value |= 0x06B402D0;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_1 + (0x100 * i), value);

		/* burst begin and burst end */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_2 + (0x100 * i), &पंचांगp);
		value &= 0xFF000000;
		value |= 0x007E9054;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_2 + (0x100 * i), value);

		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_3 + (0x100 * i), &पंचांगp);
		value &= 0xFC00FE00;
		value |= 0x00EC00F0;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_3 + (0x100 * i), value);

		/* set NTSC vblank, no phase alternation, 7.5 IRE pedestal */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_4 + (0x100 * i), &पंचांगp);
		value &= 0x00FCFFFF;
		value |= 0x13020000;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_4 + (0x100 * i), value);

		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_5 + (0x100 * i), &पंचांगp);
		value &= 0xFFFF0000;
		value |= 0x0000E575;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_5 + (0x100 * i), value);

		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_6 + (0x100 * i), 0x009A89C1);

		/* Subcarrier Increment */
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_7 + (0x100 * i), 0x21F07C1F);
	पूर्ण

	/* set picture resolutions */
	/* 0 - 720 */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], HSCALE_CTRL, 0x0);
	/* 0 - 480 */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], VSCALE_CTRL, 0x0);

	/* set Bypass input क्रमmat to NTSC 525 lines */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], BYP_AB_CTRL, &पंचांगp);
	value |= 0x00080200;
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], BYP_AB_CTRL, value);

	वापस ret_val;
पूर्ण

अटल पूर्णांक medusa_PALCombInit(काष्ठा cx25821_dev *dev, पूर्णांक dec)
अणु
	पूर्णांक ret_val = -1;
	u32 value = 0, पंचांगp = 0;

	/* Setup क्रम 2D threshold */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			COMB_2D_HFS_CFG + (0x200 * dec), 0x20002861);
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			COMB_2D_HFD_CFG + (0x200 * dec), 0x20002861);
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			COMB_2D_LF_CFG + (0x200 * dec), 0x200A1023);

	/* Setup flat chroma and luma thresholds */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
			COMB_FLAT_THRESH_CTRL + (0x200 * dec), &पंचांगp);
	value &= 0x06230000;
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			COMB_FLAT_THRESH_CTRL + (0x200 * dec), value);

	/* set comb 2D blend */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			COMB_2D_BLEND + (0x200 * dec), 0x210F0F0F);

	/* COMB MISC CONTROL */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			COMB_MISC_CTRL + (0x200 * dec), 0x41120A7F);

	वापस ret_val;
पूर्ण

अटल पूर्णांक medusa_initialize_pal(काष्ठा cx25821_dev *dev)
अणु
	पूर्णांक ret_val = 0;
	पूर्णांक i = 0;
	u32 value = 0;
	u32 पंचांगp = 0;

	क्रम (i = 0; i < MAX_DECODERS; i++) अणु
		/* set video क्रमmat PAL-BDGHI */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				MODE_CTRL + (0x200 * i), &पंचांगp);
		value &= 0xFFFFFFF0;
		/* enable the fast locking mode bit[16] */
		value |= 0x10004;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				MODE_CTRL + (0x200 * i), value);

		/* resolution PAL 720x576 */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				HORIZ_TIM_CTRL + (0x200 * i), &पंचांगp);
		value &= 0x00C00C00;
		value |= 0x632D007D;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				HORIZ_TIM_CTRL + (0x200 * i), value);

		/* vblank656_cnt=x26, vactive_cnt=240h, vblank_cnt=x24 */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				VERT_TIM_CTRL + (0x200 * i), &पंचांगp);
		value &= 0x00C00C00;
		value |= 0x28240026;	/* vblank_cnt + 2 to get camera ID */
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				VERT_TIM_CTRL + (0x200 * i), value);

		/* chroma subcarrier step size */
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				SC_STEP_SIZE + (0x200 * i), 0x5411E2D0);

		/* enable VIP optional active */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				OUT_CTRL_NS + (0x200 * i), &पंचांगp);
		value &= 0xFFFBFFFF;
		value |= 0x00040000;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				OUT_CTRL_NS + (0x200 * i), value);

		/* enable VIP optional active (VIP_OPT_AL) क्रम direct output. */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				OUT_CTRL1 + (0x200 * i), &पंचांगp);
		value &= 0xFFFBFFFF;
		value |= 0x00040000;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				OUT_CTRL1 + (0x200 * i), value);

		/*
		 * clear VPRES_VERT_EN bit, fixes the chroma run away problem
		 * when the input चयनing rate < 16 fields
		 */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				MISC_TIM_CTRL + (0x200 * i), &पंचांगp);
		/* disable special play detection */
		value = setBitAtPos(value, 14);
		value = clearBitAtPos(value, 15);
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				MISC_TIM_CTRL + (0x200 * i), value);

		/* set vbi_gate_en to 0 */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DFE_CTRL1 + (0x200 * i), &पंचांगp);
		value = clearBitAtPos(value, 29);
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DFE_CTRL1 + (0x200 * i), value);

		medusa_PALCombInit(dev, i);

		/* Enable the generation of blue field output अगर no video */
		medusa_enable_bluefield_output(dev, i, 1);
	पूर्ण

	क्रम (i = 0; i < MAX_ENCODERS; i++) अणु
		/* PAL hघड़ी */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_1 + (0x100 * i), &पंचांगp);
		value &= 0xF000FC00;
		value |= 0x06C002D0;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_1 + (0x100 * i), value);

		/* burst begin and burst end */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_2 + (0x100 * i), &पंचांगp);
		value &= 0xFF000000;
		value |= 0x007E9754;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_2 + (0x100 * i), value);

		/* hblank and vactive */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_3 + (0x100 * i), &पंचांगp);
		value &= 0xFC00FE00;
		value |= 0x00FC0120;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_3 + (0x100 * i), value);

		/* set PAL vblank, phase alternation, 0 IRE pedestal */
		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_4 + (0x100 * i), &पंचांगp);
		value &= 0x00FCFFFF;
		value |= 0x14010000;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_4 + (0x100 * i), value);

		value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
				DENC_A_REG_5 + (0x100 * i), &पंचांगp);
		value &= 0xFFFF0000;
		value |= 0x0000F078;
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_5 + (0x100 * i), value);

		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_6 + (0x100 * i), 0x00A493CF);

		/* Subcarrier Increment */
		ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				DENC_A_REG_7 + (0x100 * i), 0x2A098ACB);
	पूर्ण

	/* set picture resolutions */
	/* 0 - 720 */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], HSCALE_CTRL, 0x0);
	/* 0 - 576 */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], VSCALE_CTRL, 0x0);

	/* set Bypass input क्रमmat to PAL 625 lines */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], BYP_AB_CTRL, &पंचांगp);
	value &= 0xFFF7FDFF;
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], BYP_AB_CTRL, value);

	वापस ret_val;
पूर्ण

पूर्णांक medusa_set_videostandard(काष्ठा cx25821_dev *dev)
अणु
	पूर्णांक status = 0;
	u32 value = 0, पंचांगp = 0;

	अगर (dev->tvnorm & V4L2_STD_PAL_BG || dev->tvnorm & V4L2_STD_PAL_DK)
		status = medusa_initialize_pal(dev);
	अन्यथा
		status = medusa_initialize_ntsc(dev);

	/* Enable DENC_A output */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], DENC_A_REG_4, &पंचांगp);
	value = setBitAtPos(value, 4);
	status = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], DENC_A_REG_4, value);

	/* Enable DENC_B output */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], DENC_B_REG_4, &पंचांगp);
	value = setBitAtPos(value, 4);
	status = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], DENC_B_REG_4, value);

	वापस status;
पूर्ण

व्योम medusa_set_resolution(काष्ठा cx25821_dev *dev, पूर्णांक width,
			   पूर्णांक decoder_select)
अणु
	पूर्णांक decoder = 0;
	पूर्णांक decoder_count = 0;
	u32 hscale = 0x0;
	u32 vscale = 0x0;
	स्थिर पूर्णांक MAX_WIDTH = 720;

	/* validate the width */
	अगर (width > MAX_WIDTH) अणु
		pr_info("%s(): width %d > MAX_WIDTH %d ! resetting to MAX_WIDTH\n",
			__func__, width, MAX_WIDTH);
		width = MAX_WIDTH;
	पूर्ण

	अगर (decoder_select <= 7 && decoder_select >= 0) अणु
		decoder = decoder_select;
		decoder_count = decoder_select + 1;
	पूर्ण अन्यथा अणु
		decoder = 0;
		decoder_count = dev->_max_num_decoders;
	पूर्ण

	चयन (width) अणु
	हाल 320:
		hscale = 0x13E34B;
		vscale = 0x0;
		अवरोध;

	हाल 352:
		hscale = 0x10A273;
		vscale = 0x0;
		अवरोध;

	हाल 176:
		hscale = 0x3115B2;
		vscale = 0x1E00;
		अवरोध;

	हाल 160:
		hscale = 0x378D84;
		vscale = 0x1E00;
		अवरोध;

	शेष:		/* 720 */
		hscale = 0x0;
		vscale = 0x0;
		अवरोध;
	पूर्ण

	क्रम (; decoder < decoder_count; decoder++) अणु
		/* ग_लिखो scaling values क्रम each decoder */
		cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				HSCALE_CTRL + (0x200 * decoder), hscale);
		cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
				VSCALE_CTRL + (0x200 * decoder), vscale);
	पूर्ण
पूर्ण

अटल व्योम medusa_set_decoderduration(काष्ठा cx25821_dev *dev, पूर्णांक decoder,
				       पूर्णांक duration)
अणु
	u32 fld_cnt = 0;
	u32 पंचांगp = 0;
	u32 disp_cnt_reg = DISP_AB_CNT;

	/* no support */
	अगर (decoder < VDEC_A || decoder > VDEC_H) अणु
		वापस;
	पूर्ण

	चयन (decoder) अणु
	शेष:
		अवरोध;
	हाल VDEC_C:
	हाल VDEC_D:
		disp_cnt_reg = DISP_CD_CNT;
		अवरोध;
	हाल VDEC_E:
	हाल VDEC_F:
		disp_cnt_reg = DISP_EF_CNT;
		अवरोध;
	हाल VDEC_G:
	हाल VDEC_H:
		disp_cnt_reg = DISP_GH_CNT;
		अवरोध;
	पूर्ण

	/* update hardware */
	fld_cnt = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], disp_cnt_reg, &पंचांगp);

	अगर (!(decoder % 2)) अणु	/* EVEN decoder */
		fld_cnt &= 0xFFFF0000;
		fld_cnt |= duration;
	पूर्ण अन्यथा अणु
		fld_cnt &= 0x0000FFFF;
		fld_cnt |= ((u32) duration) << 16;
	पूर्ण

	cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], disp_cnt_reg, fld_cnt);
पूर्ण

/* Map to Medusa रेजिस्टर setting */
अटल पूर्णांक mapM(पूर्णांक srcMin, पूर्णांक srcMax, पूर्णांक srcVal, पूर्णांक dstMin, पूर्णांक dstMax,
		पूर्णांक *dstVal)
अणु
	पूर्णांक numerator;
	पूर्णांक denominator;
	पूर्णांक quotient;

	अगर ((srcMin == srcMax) || (srcVal < srcMin) || (srcVal > srcMax))
		वापस -1;
	/*
	 * This is the overall expression used:
	 * *dstVal =
	 *   (srcVal - srcMin)*(dstMax - dstMin) / (srcMax - srcMin) + dstMin;
	 * but we need to account क्रम rounding so below we use the modulus
	 * चालक to find the reमुख्यder and increment अगर necessary.
	 */
	numerator = (srcVal - srcMin) * (dstMax - dstMin);
	denominator = srcMax - srcMin;
	quotient = numerator / denominator;

	अगर (2 * (numerator % denominator) >= denominator)
		quotient++;

	*dstVal = quotient + dstMin;

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ convert_to_twos(दीर्घ numeric, अचिन्हित दीर्घ bits_len)
अणु
	अचिन्हित अक्षर temp;

	अगर (numeric >= 0)
		वापस numeric;
	अन्यथा अणु
		temp = ~(असल(numeric) & 0xFF);
		temp += 1;
		वापस temp;
	पूर्ण
पूर्ण

पूर्णांक medusa_set_brightness(काष्ठा cx25821_dev *dev, पूर्णांक brightness, पूर्णांक decoder)
अणु
	पूर्णांक ret_val = 0;
	पूर्णांक value = 0;
	u32 val = 0, पंचांगp = 0;

	अगर ((brightness > VIDEO_PROCAMP_MAX) ||
	    (brightness < VIDEO_PROCAMP_MIN)) अणु
		वापस -1;
	पूर्ण
	ret_val = mapM(VIDEO_PROCAMP_MIN, VIDEO_PROCAMP_MAX, brightness,
			SIGNED_BYTE_MIN, SIGNED_BYTE_MAX, &value);
	value = convert_to_twos(value, 8);
	val = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
			VDEC_A_BRITE_CTRL + (0x200 * decoder), &पंचांगp);
	val &= 0xFFFFFF00;
	ret_val |= cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			VDEC_A_BRITE_CTRL + (0x200 * decoder), val | value);
	वापस ret_val;
पूर्ण

पूर्णांक medusa_set_contrast(काष्ठा cx25821_dev *dev, पूर्णांक contrast, पूर्णांक decoder)
अणु
	पूर्णांक ret_val = 0;
	पूर्णांक value = 0;
	u32 val = 0, पंचांगp = 0;

	अगर ((contrast > VIDEO_PROCAMP_MAX) || (contrast < VIDEO_PROCAMP_MIN)) अणु
		वापस -1;
	पूर्ण

	ret_val = mapM(VIDEO_PROCAMP_MIN, VIDEO_PROCAMP_MAX, contrast,
			UNSIGNED_BYTE_MIN, UNSIGNED_BYTE_MAX, &value);
	val = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
			VDEC_A_CNTRST_CTRL + (0x200 * decoder), &पंचांगp);
	val &= 0xFFFFFF00;
	ret_val |= cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			VDEC_A_CNTRST_CTRL + (0x200 * decoder), val | value);

	वापस ret_val;
पूर्ण

पूर्णांक medusa_set_hue(काष्ठा cx25821_dev *dev, पूर्णांक hue, पूर्णांक decoder)
अणु
	पूर्णांक ret_val = 0;
	पूर्णांक value = 0;
	u32 val = 0, पंचांगp = 0;

	अगर ((hue > VIDEO_PROCAMP_MAX) || (hue < VIDEO_PROCAMP_MIN)) अणु
		वापस -1;
	पूर्ण

	ret_val = mapM(VIDEO_PROCAMP_MIN, VIDEO_PROCAMP_MAX, hue,
			SIGNED_BYTE_MIN, SIGNED_BYTE_MAX, &value);

	value = convert_to_twos(value, 8);
	val = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
			VDEC_A_HUE_CTRL + (0x200 * decoder), &पंचांगp);
	val &= 0xFFFFFF00;

	ret_val |= cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			VDEC_A_HUE_CTRL + (0x200 * decoder), val | value);

	वापस ret_val;
पूर्ण

पूर्णांक medusa_set_saturation(काष्ठा cx25821_dev *dev, पूर्णांक saturation, पूर्णांक decoder)
अणु
	पूर्णांक ret_val = 0;
	पूर्णांक value = 0;
	u32 val = 0, पंचांगp = 0;

	अगर ((saturation > VIDEO_PROCAMP_MAX) ||
	    (saturation < VIDEO_PROCAMP_MIN)) अणु
		वापस -1;
	पूर्ण

	ret_val = mapM(VIDEO_PROCAMP_MIN, VIDEO_PROCAMP_MAX, saturation,
			UNSIGNED_BYTE_MIN, UNSIGNED_BYTE_MAX, &value);

	val = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
			VDEC_A_USAT_CTRL + (0x200 * decoder), &पंचांगp);
	val &= 0xFFFFFF00;
	ret_val |= cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			VDEC_A_USAT_CTRL + (0x200 * decoder), val | value);

	val = cx25821_i2c_पढ़ो(&dev->i2c_bus[0],
			VDEC_A_VSAT_CTRL + (0x200 * decoder), &पंचांगp);
	val &= 0xFFFFFF00;
	ret_val |= cx25821_i2c_ग_लिखो(&dev->i2c_bus[0],
			VDEC_A_VSAT_CTRL + (0x200 * decoder), val | value);

	वापस ret_val;
पूर्ण

/* Program the display sequence and monitor output. */

पूर्णांक medusa_video_init(काष्ठा cx25821_dev *dev)
अणु
	u32 value = 0, पंचांगp = 0;
	पूर्णांक ret_val = 0;
	पूर्णांक i = 0;

	/* disable Auto source selection on all video decoders */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], MON_A_CTRL, &पंचांगp);
	value &= 0xFFFFF0FF;
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], MON_A_CTRL, value);

	अगर (ret_val < 0)
		जाओ error;

	/* Turn off Master source चयन enable */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], MON_A_CTRL, &पंचांगp);
	value &= 0xFFFFFFDF;
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], MON_A_CTRL, value);

	अगर (ret_val < 0)
		जाओ error;

	/*
	 * FIXME: due to a coding bug the duration was always 0. It's
	 * likely that it really should be something अन्यथा, but due to the
	 * lack of करोcumentation I have no idea what it should be. For
	 * now just fill in 0 as the duration.
	 */
	क्रम (i = 0; i < dev->_max_num_decoders; i++)
		medusa_set_decoderduration(dev, i, 0);

	/* Select monitor as DENC A input, घातer up the DAC */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], DENC_AB_CTRL, &पंचांगp);
	value &= 0xFF70FF70;
	value |= 0x00090008;	/* set en_active */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], DENC_AB_CTRL, value);

	अगर (ret_val < 0)
		जाओ error;

	/* enable input is VIP/656 */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], BYP_AB_CTRL, &पंचांगp);
	value |= 0x00040100;	/* enable VIP */
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], BYP_AB_CTRL, value);

	अगर (ret_val < 0)
		जाओ error;

	/* select AFE घड़ी to output mode */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL, &पंचांगp);
	value &= 0x83FFFFFF;
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], AFE_AB_DIAG_CTRL,
			value | 0x10000000);

	अगर (ret_val < 0)
		जाओ error;

	/* Turn on all of the data out and control output pins. */
	value = cx25821_i2c_पढ़ो(&dev->i2c_bus[0], PIN_OE_CTRL, &पंचांगp);
	value &= 0xFEF0FE00;
	अगर (dev->_max_num_decoders == MAX_DECODERS) अणु
		/*
		 * Note: The octal board करोes not support control pins(bit16-19)
		 * These bits are ignored in the octal board.
		 *
		 * disable VDEC A-C port, शेष to Mobilygen Interface
		 */
		value |= 0x010001F8;
	पूर्ण अन्यथा अणु
		/* disable VDEC A-C port, शेष to Mobilygen Interface */
		value |= 0x010F0108;
	पूर्ण

	value |= 7;
	ret_val = cx25821_i2c_ग_लिखो(&dev->i2c_bus[0], PIN_OE_CTRL, value);

	अगर (ret_val < 0)
		जाओ error;

	ret_val = medusa_set_videostandard(dev);

error:
	वापस ret_val;
पूर्ण
