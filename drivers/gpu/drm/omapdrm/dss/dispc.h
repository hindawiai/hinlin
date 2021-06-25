<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Archit Taneja <archit@ti.com>
 */

#अगर_अघोषित __OMAP2_DISPC_REG_H
#घोषणा __OMAP2_DISPC_REG_H

/* DISPC common रेजिस्टरs */
#घोषणा DISPC_REVISION			0x0000
#घोषणा DISPC_SYSCONFIG			0x0010
#घोषणा DISPC_SYSSTATUS			0x0014
#घोषणा DISPC_IRQSTATUS			0x0018
#घोषणा DISPC_IRQENABLE			0x001C
#घोषणा DISPC_CONTROL			0x0040
#घोषणा DISPC_CONFIG			0x0044
#घोषणा DISPC_CAPABLE			0x0048
#घोषणा DISPC_LINE_STATUS		0x005C
#घोषणा DISPC_LINE_NUMBER		0x0060
#घोषणा DISPC_GLOBAL_ALPHA		0x0074
#घोषणा DISPC_CONTROL2			0x0238
#घोषणा DISPC_CONFIG2			0x0620
#घोषणा DISPC_DIVISOR			0x0804
#घोषणा DISPC_GLOBAL_BUFFER		0x0800
#घोषणा DISPC_CONTROL3                  0x0848
#घोषणा DISPC_CONFIG3                   0x084C
#घोषणा DISPC_MSTANDBY_CTRL		0x0858
#घोषणा DISPC_GLOBAL_MFLAG_ATTRIBUTE	0x085C

#घोषणा DISPC_GAMMA_TABLE0		0x0630
#घोषणा DISPC_GAMMA_TABLE1		0x0634
#घोषणा DISPC_GAMMA_TABLE2		0x0638
#घोषणा DISPC_GAMMA_TABLE3		0x0850

/* DISPC overlay रेजिस्टरs */
#घोषणा DISPC_OVL_BA0(n)		(DISPC_OVL_BASE(n) + \
					DISPC_BA0_OFFSET(n))
#घोषणा DISPC_OVL_BA1(n)		(DISPC_OVL_BASE(n) + \
					DISPC_BA1_OFFSET(n))
#घोषणा DISPC_OVL_BA0_UV(n)		(DISPC_OVL_BASE(n) + \
					DISPC_BA0_UV_OFFSET(n))
#घोषणा DISPC_OVL_BA1_UV(n)		(DISPC_OVL_BASE(n) + \
					DISPC_BA1_UV_OFFSET(n))
#घोषणा DISPC_OVL_POSITION(n)		(DISPC_OVL_BASE(n) + \
					DISPC_POS_OFFSET(n))
#घोषणा DISPC_OVL_SIZE(n)		(DISPC_OVL_BASE(n) + \
					DISPC_SIZE_OFFSET(n))
#घोषणा DISPC_OVL_ATTRIBUTES(n)		(DISPC_OVL_BASE(n) + \
					DISPC_ATTR_OFFSET(n))
#घोषणा DISPC_OVL_ATTRIBUTES2(n)	(DISPC_OVL_BASE(n) + \
					DISPC_ATTR2_OFFSET(n))
#घोषणा DISPC_OVL_FIFO_THRESHOLD(n)	(DISPC_OVL_BASE(n) + \
					DISPC_FIFO_THRESH_OFFSET(n))
#घोषणा DISPC_OVL_FIFO_SIZE_STATUS(n)	(DISPC_OVL_BASE(n) + \
					DISPC_FIFO_SIZE_STATUS_OFFSET(n))
#घोषणा DISPC_OVL_ROW_INC(n)		(DISPC_OVL_BASE(n) + \
					DISPC_ROW_INC_OFFSET(n))
#घोषणा DISPC_OVL_PIXEL_INC(n)		(DISPC_OVL_BASE(n) + \
					DISPC_PIX_INC_OFFSET(n))
#घोषणा DISPC_OVL_WINDOW_SKIP(n)	(DISPC_OVL_BASE(n) + \
					DISPC_WINDOW_SKIP_OFFSET(n))
#घोषणा DISPC_OVL_TABLE_BA(n)		(DISPC_OVL_BASE(n) + \
					DISPC_TABLE_BA_OFFSET(n))
#घोषणा DISPC_OVL_FIR(n)		(DISPC_OVL_BASE(n) + \
					DISPC_FIR_OFFSET(n))
#घोषणा DISPC_OVL_FIR2(n)		(DISPC_OVL_BASE(n) + \
					DISPC_FIR2_OFFSET(n))
#घोषणा DISPC_OVL_PICTURE_SIZE(n)	(DISPC_OVL_BASE(n) + \
					DISPC_PIC_SIZE_OFFSET(n))
#घोषणा DISPC_OVL_ACCU0(n)		(DISPC_OVL_BASE(n) + \
					DISPC_ACCU0_OFFSET(n))
#घोषणा DISPC_OVL_ACCU1(n)		(DISPC_OVL_BASE(n) + \
					DISPC_ACCU1_OFFSET(n))
#घोषणा DISPC_OVL_ACCU2_0(n)		(DISPC_OVL_BASE(n) + \
					DISPC_ACCU2_0_OFFSET(n))
#घोषणा DISPC_OVL_ACCU2_1(n)		(DISPC_OVL_BASE(n) + \
					DISPC_ACCU2_1_OFFSET(n))
#घोषणा DISPC_OVL_FIR_COEF_H(n, i)	(DISPC_OVL_BASE(n) + \
					DISPC_FIR_COEF_H_OFFSET(n, i))
#घोषणा DISPC_OVL_FIR_COEF_HV(n, i)	(DISPC_OVL_BASE(n) + \
					DISPC_FIR_COEF_HV_OFFSET(n, i))
#घोषणा DISPC_OVL_FIR_COEF_H2(n, i)	(DISPC_OVL_BASE(n) + \
					DISPC_FIR_COEF_H2_OFFSET(n, i))
#घोषणा DISPC_OVL_FIR_COEF_HV2(n, i)	(DISPC_OVL_BASE(n) + \
					DISPC_FIR_COEF_HV2_OFFSET(n, i))
#घोषणा DISPC_OVL_CONV_COEF(n, i)	(DISPC_OVL_BASE(n) + \
					DISPC_CONV_COEF_OFFSET(n, i))
#घोषणा DISPC_OVL_FIR_COEF_V(n, i)	(DISPC_OVL_BASE(n) + \
					DISPC_FIR_COEF_V_OFFSET(n, i))
#घोषणा DISPC_OVL_FIR_COEF_V2(n, i)	(DISPC_OVL_BASE(n) + \
					DISPC_FIR_COEF_V2_OFFSET(n, i))
#घोषणा DISPC_OVL_PRELOAD(n)		(DISPC_OVL_BASE(n) + \
					DISPC_PRELOAD_OFFSET(n))
#घोषणा DISPC_OVL_MFLAG_THRESHOLD(n)	DISPC_MFLAG_THRESHOLD_OFFSET(n)

/* DISPC up/करोwnsampling FIR filter coefficient काष्ठाure */
काष्ठा dispc_coef अणु
	s8 hc4_vc22;
	s8 hc3_vc2;
	u8 hc2_vc1;
	s8 hc1_vc0;
	s8 hc0_vc00;
पूर्ण;

स्थिर काष्ठा dispc_coef *dispc_ovl_get_scale_coef(पूर्णांक inc, पूर्णांक five_taps);

/* DISPC manager/channel specअगरic रेजिस्टरs */
अटल अंतरभूत u16 DISPC_DEFAULT_COLOR(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x004C;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		वापस 0x0050;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03AC;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0814;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_TRANS_COLOR(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x0054;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		वापस 0x0058;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03B0;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0818;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_TIMING_H(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x0064;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x0400;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0840;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_TIMING_V(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x0068;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x0404;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0844;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_POL_FREQ(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x006C;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x0408;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x083C;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_DIVISORo(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x0070;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x040C;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0838;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* Named as DISPC_SIZE_LCD, DISPC_SIZE_DIGIT and DISPC_SIZE_LCD2 in TRM */
अटल अंतरभूत u16 DISPC_SIZE_MGR(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x007C;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		वापस 0x0078;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03CC;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0834;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_DATA_CYCLE1(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x01D4;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03C0;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0828;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_DATA_CYCLE2(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x01D8;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03C4;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x082C;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_DATA_CYCLE3(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x01DC;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03C8;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0830;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_CPR_COEF_R(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x0220;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03BC;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0824;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_CPR_COEF_G(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x0224;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03B8;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x0820;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_CPR_COEF_B(क्रमागत omap_channel channel)
अणु
	चयन (channel) अणु
	हाल OMAP_DSS_CHANNEL_LCD:
		वापस 0x0228;
	हाल OMAP_DSS_CHANNEL_DIGIT:
		BUG();
		वापस 0;
	हाल OMAP_DSS_CHANNEL_LCD2:
		वापस 0x03B4;
	हाल OMAP_DSS_CHANNEL_LCD3:
		वापस 0x081C;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* DISPC overlay रेजिस्टर base addresses */
अटल अंतरभूत u16 DISPC_OVL_BASE(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0080;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x00BC;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x014C;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0300;
	हाल OMAP_DSS_WB:
		वापस 0x0500;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* DISPC overlay रेजिस्टर offsets */
अटल अंतरभूत u16 DISPC_BA0_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0000;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0008;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_BA1_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0004;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x000C;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_BA0_UV_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0544;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x04BC;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0310;
	हाल OMAP_DSS_WB:
		वापस 0x0118;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_BA1_UV_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0548;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x04C0;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0314;
	हाल OMAP_DSS_WB:
		वापस 0x011C;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_POS_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0008;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x009C;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_SIZE_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x000C;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x00A8;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_ATTR_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0020;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0010;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0070;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_ATTR2_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0568;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x04DC;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x032C;
	हाल OMAP_DSS_WB:
		वापस 0x0310;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_FIFO_THRESH_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0024;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0014;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x008C;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_FIFO_SIZE_STATUS_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0028;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0018;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0088;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_ROW_INC_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x002C;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x001C;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x00A4;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_PIX_INC_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0030;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0020;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0098;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_WINDOW_SKIP_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0034;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
	हाल OMAP_DSS_VIDEO3:
		BUG();
		वापस 0;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_TABLE_BA_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0038;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
	हाल OMAP_DSS_VIDEO3:
		BUG();
		वापस 0;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_FIR_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0024;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0090;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_FIR2_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0580;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x055C;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0424;
	हाल OMAP_DSS_WB:
		वापस 0x290;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_PIC_SIZE_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0028;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0094;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण


अटल अंतरभूत u16 DISPC_ACCU0_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x002C;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0000;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_ACCU2_0_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0584;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0560;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0428;
	हाल OMAP_DSS_WB:
		वापस 0x0294;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_ACCU1_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0030;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0004;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_ACCU2_1_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0588;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0564;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x042C;
	हाल OMAP_DSS_WB:
		वापस 0x0298;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* coef index i = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण */
अटल अंतरभूत u16 DISPC_FIR_COEF_H_OFFSET(क्रमागत omap_plane_id plane, u16 i)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0034 + i * 0x8;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0010 + i * 0x8;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* coef index i = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण */
अटल अंतरभूत u16 DISPC_FIR_COEF_H2_OFFSET(क्रमागत omap_plane_id plane, u16 i)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x058C + i * 0x8;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0568 + i * 0x8;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0430 + i * 0x8;
	हाल OMAP_DSS_WB:
		वापस 0x02A0 + i * 0x8;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* coef index i = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण */
अटल अंतरभूत u16 DISPC_FIR_COEF_HV_OFFSET(क्रमागत omap_plane_id plane, u16 i)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0038 + i * 0x8;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0014 + i * 0x8;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* coef index i = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण */
अटल अंतरभूत u16 DISPC_FIR_COEF_HV2_OFFSET(क्रमागत omap_plane_id plane, u16 i)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0590 + i * 8;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x056C + i * 0x8;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0434 + i * 0x8;
	हाल OMAP_DSS_WB:
		वापस 0x02A4 + i * 0x8;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* coef index i = अणु0, 1, 2, 3, 4,पूर्ण */
अटल अंतरभूत u16 DISPC_CONV_COEF_OFFSET(क्रमागत omap_plane_id plane, u16 i)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
	हाल OMAP_DSS_VIDEO2:
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0074 + i * 0x4;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* coef index i = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण */
अटल अंतरभूत u16 DISPC_FIR_COEF_V_OFFSET(क्रमागत omap_plane_id plane, u16 i)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0124 + i * 0x4;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x00B4 + i * 0x4;
	हाल OMAP_DSS_VIDEO3:
	हाल OMAP_DSS_WB:
		वापस 0x0050 + i * 0x4;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

/* coef index i = अणु0, 1, 2, 3, 4, 5, 6, 7पूर्ण */
अटल अंतरभूत u16 DISPC_FIR_COEF_V2_OFFSET(क्रमागत omap_plane_id plane, u16 i)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		BUG();
		वापस 0;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x05CC + i * 0x4;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x05A8 + i * 0x4;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x0470 + i * 0x4;
	हाल OMAP_DSS_WB:
		वापस 0x02E0 + i * 0x4;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_PRELOAD_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x01AC;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0174;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x00E8;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x00A0;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 DISPC_MFLAG_THRESHOLD_OFFSET(क्रमागत omap_plane_id plane)
अणु
	चयन (plane) अणु
	हाल OMAP_DSS_GFX:
		वापस 0x0860;
	हाल OMAP_DSS_VIDEO1:
		वापस 0x0864;
	हाल OMAP_DSS_VIDEO2:
		वापस 0x0868;
	हाल OMAP_DSS_VIDEO3:
		वापस 0x086c;
	हाल OMAP_DSS_WB:
		वापस 0x0870;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर
