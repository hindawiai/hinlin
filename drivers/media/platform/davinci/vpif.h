<शैली गुरु>
/*
 * VPIF header file
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित VPIF_H
#घोषणा VPIF_H

#समावेश <linux/पन.स>
#समावेश <linux/videodev2.h>
#समावेश <media/davinci/vpअगर_types.h>

/* Maximum channel allowed */
#घोषणा VPIF_NUM_CHANNELS		(4)
#घोषणा VPIF_CAPTURE_NUM_CHANNELS	(2)
#घोषणा VPIF_DISPLAY_NUM_CHANNELS	(2)

/* Macros to पढ़ो/ग_लिखो रेजिस्टरs */
बाह्य व्योम __iomem *vpअगर_base;
बाह्य spinlock_t vpअगर_lock;

#घोषणा regr(reg)               पढ़ोl((reg) + vpअगर_base)
#घोषणा regw(value, reg)        ग_लिखोl(value, (reg + vpअगर_base))

/* Register Address Offsets */
#घोषणा VPIF_PID			(0x0000)
#घोषणा VPIF_CH0_CTRL			(0x0004)
#घोषणा VPIF_CH1_CTRL			(0x0008)
#घोषणा VPIF_CH2_CTRL			(0x000C)
#घोषणा VPIF_CH3_CTRL			(0x0010)

#घोषणा VPIF_INTEN			(0x0020)
#घोषणा VPIF_INTEN_SET			(0x0024)
#घोषणा VPIF_INTEN_CLR			(0x0028)
#घोषणा VPIF_STATUS			(0x002C)
#घोषणा VPIF_STATUS_CLR			(0x0030)
#घोषणा VPIF_EMULATION_CTRL		(0x0034)
#घोषणा VPIF_REQ_SIZE			(0x0038)

#घोषणा VPIF_CH0_TOP_STRT_ADD_LUMA	(0x0040)
#घोषणा VPIF_CH0_BTM_STRT_ADD_LUMA	(0x0044)
#घोषणा VPIF_CH0_TOP_STRT_ADD_CHROMA	(0x0048)
#घोषणा VPIF_CH0_BTM_STRT_ADD_CHROMA	(0x004c)
#घोषणा VPIF_CH0_TOP_STRT_ADD_HANC	(0x0050)
#घोषणा VPIF_CH0_BTM_STRT_ADD_HANC	(0x0054)
#घोषणा VPIF_CH0_TOP_STRT_ADD_VANC	(0x0058)
#घोषणा VPIF_CH0_BTM_STRT_ADD_VANC	(0x005c)
#घोषणा VPIF_CH0_SP_CFG			(0x0060)
#घोषणा VPIF_CH0_IMG_ADD_OFST		(0x0064)
#घोषणा VPIF_CH0_HANC_ADD_OFST		(0x0068)
#घोषणा VPIF_CH0_H_CFG			(0x006c)
#घोषणा VPIF_CH0_V_CFG_00		(0x0070)
#घोषणा VPIF_CH0_V_CFG_01		(0x0074)
#घोषणा VPIF_CH0_V_CFG_02		(0x0078)
#घोषणा VPIF_CH0_V_CFG_03		(0x007c)

#घोषणा VPIF_CH1_TOP_STRT_ADD_LUMA	(0x0080)
#घोषणा VPIF_CH1_BTM_STRT_ADD_LUMA	(0x0084)
#घोषणा VPIF_CH1_TOP_STRT_ADD_CHROMA	(0x0088)
#घोषणा VPIF_CH1_BTM_STRT_ADD_CHROMA	(0x008c)
#घोषणा VPIF_CH1_TOP_STRT_ADD_HANC	(0x0090)
#घोषणा VPIF_CH1_BTM_STRT_ADD_HANC	(0x0094)
#घोषणा VPIF_CH1_TOP_STRT_ADD_VANC	(0x0098)
#घोषणा VPIF_CH1_BTM_STRT_ADD_VANC	(0x009c)
#घोषणा VPIF_CH1_SP_CFG			(0x00a0)
#घोषणा VPIF_CH1_IMG_ADD_OFST		(0x00a4)
#घोषणा VPIF_CH1_HANC_ADD_OFST		(0x00a8)
#घोषणा VPIF_CH1_H_CFG			(0x00ac)
#घोषणा VPIF_CH1_V_CFG_00		(0x00b0)
#घोषणा VPIF_CH1_V_CFG_01		(0x00b4)
#घोषणा VPIF_CH1_V_CFG_02		(0x00b8)
#घोषणा VPIF_CH1_V_CFG_03		(0x00bc)

#घोषणा VPIF_CH2_TOP_STRT_ADD_LUMA	(0x00c0)
#घोषणा VPIF_CH2_BTM_STRT_ADD_LUMA	(0x00c4)
#घोषणा VPIF_CH2_TOP_STRT_ADD_CHROMA	(0x00c8)
#घोषणा VPIF_CH2_BTM_STRT_ADD_CHROMA	(0x00cc)
#घोषणा VPIF_CH2_TOP_STRT_ADD_HANC	(0x00d0)
#घोषणा VPIF_CH2_BTM_STRT_ADD_HANC	(0x00d4)
#घोषणा VPIF_CH2_TOP_STRT_ADD_VANC	(0x00d8)
#घोषणा VPIF_CH2_BTM_STRT_ADD_VANC	(0x00dc)
#घोषणा VPIF_CH2_SP_CFG			(0x00e0)
#घोषणा VPIF_CH2_IMG_ADD_OFST		(0x00e4)
#घोषणा VPIF_CH2_HANC_ADD_OFST		(0x00e8)
#घोषणा VPIF_CH2_H_CFG			(0x00ec)
#घोषणा VPIF_CH2_V_CFG_00		(0x00f0)
#घोषणा VPIF_CH2_V_CFG_01		(0x00f4)
#घोषणा VPIF_CH2_V_CFG_02		(0x00f8)
#घोषणा VPIF_CH2_V_CFG_03		(0x00fc)
#घोषणा VPIF_CH2_HANC0_STRT		(0x0100)
#घोषणा VPIF_CH2_HANC0_SIZE		(0x0104)
#घोषणा VPIF_CH2_HANC1_STRT		(0x0108)
#घोषणा VPIF_CH2_HANC1_SIZE		(0x010c)
#घोषणा VPIF_CH2_VANC0_STRT		(0x0110)
#घोषणा VPIF_CH2_VANC0_SIZE		(0x0114)
#घोषणा VPIF_CH2_VANC1_STRT		(0x0118)
#घोषणा VPIF_CH2_VANC1_SIZE		(0x011c)

#घोषणा VPIF_CH3_TOP_STRT_ADD_LUMA	(0x0140)
#घोषणा VPIF_CH3_BTM_STRT_ADD_LUMA	(0x0144)
#घोषणा VPIF_CH3_TOP_STRT_ADD_CHROMA	(0x0148)
#घोषणा VPIF_CH3_BTM_STRT_ADD_CHROMA	(0x014c)
#घोषणा VPIF_CH3_TOP_STRT_ADD_HANC	(0x0150)
#घोषणा VPIF_CH3_BTM_STRT_ADD_HANC	(0x0154)
#घोषणा VPIF_CH3_TOP_STRT_ADD_VANC	(0x0158)
#घोषणा VPIF_CH3_BTM_STRT_ADD_VANC	(0x015c)
#घोषणा VPIF_CH3_SP_CFG			(0x0160)
#घोषणा VPIF_CH3_IMG_ADD_OFST		(0x0164)
#घोषणा VPIF_CH3_HANC_ADD_OFST		(0x0168)
#घोषणा VPIF_CH3_H_CFG			(0x016c)
#घोषणा VPIF_CH3_V_CFG_00		(0x0170)
#घोषणा VPIF_CH3_V_CFG_01		(0x0174)
#घोषणा VPIF_CH3_V_CFG_02		(0x0178)
#घोषणा VPIF_CH3_V_CFG_03		(0x017c)
#घोषणा VPIF_CH3_HANC0_STRT		(0x0180)
#घोषणा VPIF_CH3_HANC0_SIZE		(0x0184)
#घोषणा VPIF_CH3_HANC1_STRT		(0x0188)
#घोषणा VPIF_CH3_HANC1_SIZE		(0x018c)
#घोषणा VPIF_CH3_VANC0_STRT		(0x0190)
#घोषणा VPIF_CH3_VANC0_SIZE		(0x0194)
#घोषणा VPIF_CH3_VANC1_STRT		(0x0198)
#घोषणा VPIF_CH3_VANC1_SIZE		(0x019c)

#घोषणा VPIF_IODFT_CTRL			(0x01c0)

/* Functions क्रम bit Manipulation */
अटल अंतरभूत व्योम vpअगर_set_bit(u32 reg, u32 bit)
अणु
	regw((regr(reg)) | (0x01 << bit), reg);
पूर्ण

अटल अंतरभूत व्योम vpअगर_clr_bit(u32 reg, u32 bit)
अणु
	regw(((regr(reg)) & ~(0x01 << bit)), reg);
पूर्ण

/* Macro क्रम Generating mask */
#अगर_घोषित GENERATE_MASK
#अघोषित GENERATE_MASK
#पूर्ण_अगर

#घोषणा GENERATE_MASK(bits, pos) \
		((((0xFFFFFFFF) << (32 - bits)) >> (32 - bits)) << pos)

/* Bit positions in the channel control रेजिस्टरs */
#घोषणा VPIF_CH_DATA_MODE_BIT	(2)
#घोषणा VPIF_CH_YC_MUX_BIT	(3)
#घोषणा VPIF_CH_SDR_FMT_BIT	(4)
#घोषणा VPIF_CH_HANC_EN_BIT	(8)
#घोषणा VPIF_CH_VANC_EN_BIT	(9)

#घोषणा VPIF_CAPTURE_CH_NIP	(10)
#घोषणा VPIF_DISPLAY_CH_NIP	(11)

#घोषणा VPIF_DISPLAY_PIX_EN_BIT	(10)

#घोषणा VPIF_CH_INPUT_FIELD_FRAME_BIT	(12)

#घोषणा VPIF_CH_FID_POLARITY_BIT	(15)
#घोषणा VPIF_CH_V_VALID_POLARITY_BIT	(14)
#घोषणा VPIF_CH_H_VALID_POLARITY_BIT	(13)
#घोषणा VPIF_CH_DATA_WIDTH_BIT		(28)

#घोषणा VPIF_CH_CLK_EDGE_CTRL_BIT	(31)

/* Mask various length */
#घोषणा VPIF_CH_EAVSAV_MASK	GENERATE_MASK(13, 0)
#घोषणा VPIF_CH_LEN_MASK	GENERATE_MASK(12, 0)
#घोषणा VPIF_CH_WIDTH_MASK	GENERATE_MASK(13, 0)
#घोषणा VPIF_CH_LEN_SHIFT	(16)

/* VPIF masks क्रम रेजिस्टरs */
#घोषणा VPIF_REQ_SIZE_MASK	(0x1ff)

/* bit posotion of पूर्णांकerrupt vpअगर_ch_पूर्णांकr रेजिस्टर */
#घोषणा VPIF_INTEN_FRAME_CH0	(0x00000001)
#घोषणा VPIF_INTEN_FRAME_CH1	(0x00000002)
#घोषणा VPIF_INTEN_FRAME_CH2	(0x00000004)
#घोषणा VPIF_INTEN_FRAME_CH3	(0x00000008)

/* bit position of घड़ी and channel enable in vpअगर_chn_ctrl रेजिस्टर */

#घोषणा VPIF_CH0_CLK_EN		(0x00000002)
#घोषणा VPIF_CH0_EN		(0x00000001)
#घोषणा VPIF_CH1_CLK_EN		(0x00000002)
#घोषणा VPIF_CH1_EN		(0x00000001)
#घोषणा VPIF_CH2_CLK_EN		(0x00000002)
#घोषणा VPIF_CH2_EN		(0x00000001)
#घोषणा VPIF_CH3_CLK_EN		(0x00000002)
#घोषणा VPIF_CH3_EN		(0x00000001)
#घोषणा VPIF_CH_CLK_EN		(0x00000002)
#घोषणा VPIF_CH_EN		(0x00000001)

#घोषणा VPIF_INT_TOP	(0x00)
#घोषणा VPIF_INT_BOTTOM	(0x01)
#घोषणा VPIF_INT_BOTH	(0x02)

#घोषणा VPIF_CH0_INT_CTRL_SHIFT	(6)
#घोषणा VPIF_CH1_INT_CTRL_SHIFT	(6)
#घोषणा VPIF_CH2_INT_CTRL_SHIFT	(6)
#घोषणा VPIF_CH3_INT_CTRL_SHIFT	(6)
#घोषणा VPIF_CH_INT_CTRL_SHIFT	(6)

#घोषणा VPIF_CH2_CLIP_ANC_EN	14
#घोषणा VPIF_CH2_CLIP_ACTIVE_EN	13

#घोषणा VPIF_CH3_CLIP_ANC_EN	14
#घोषणा VPIF_CH3_CLIP_ACTIVE_EN	13

/* enabled पूर्णांकerrupt on both the fields on vpid_ch0_ctrl रेजिस्टर */
#घोषणा channel0_पूर्णांकr_निश्चित()	(regw((regr(VPIF_CH0_CTRL)|\
	(VPIF_INT_BOTH << VPIF_CH0_INT_CTRL_SHIFT)), VPIF_CH0_CTRL))

/* enabled पूर्णांकerrupt on both the fields on vpid_ch1_ctrl रेजिस्टर */
#घोषणा channel1_पूर्णांकr_निश्चित()	(regw((regr(VPIF_CH1_CTRL)|\
	(VPIF_INT_BOTH << VPIF_CH1_INT_CTRL_SHIFT)), VPIF_CH1_CTRL))

/* enabled पूर्णांकerrupt on both the fields on vpid_ch0_ctrl रेजिस्टर */
#घोषणा channel2_पूर्णांकr_निश्चित()	(regw((regr(VPIF_CH2_CTRL)|\
	(VPIF_INT_BOTH << VPIF_CH2_INT_CTRL_SHIFT)), VPIF_CH2_CTRL))

/* enabled पूर्णांकerrupt on both the fields on vpid_ch1_ctrl रेजिस्टर */
#घोषणा channel3_पूर्णांकr_निश्चित()	(regw((regr(VPIF_CH3_CTRL)|\
	(VPIF_INT_BOTH << VPIF_CH3_INT_CTRL_SHIFT)), VPIF_CH3_CTRL))

#घोषणा VPIF_CH_FID_MASK	(0x20)
#घोषणा VPIF_CH_FID_SHIFT	(5)

#घोषणा VPIF_NTSC_VBI_START_FIELD0	(1)
#घोषणा VPIF_NTSC_VBI_START_FIELD1	(263)
#घोषणा VPIF_PAL_VBI_START_FIELD0	(624)
#घोषणा VPIF_PAL_VBI_START_FIELD1	(311)

#घोषणा VPIF_NTSC_HBI_START_FIELD0	(1)
#घोषणा VPIF_NTSC_HBI_START_FIELD1	(263)
#घोषणा VPIF_PAL_HBI_START_FIELD0	(624)
#घोषणा VPIF_PAL_HBI_START_FIELD1	(311)

#घोषणा VPIF_NTSC_VBI_COUNT_FIELD0	(20)
#घोषणा VPIF_NTSC_VBI_COUNT_FIELD1	(19)
#घोषणा VPIF_PAL_VBI_COUNT_FIELD0	(24)
#घोषणा VPIF_PAL_VBI_COUNT_FIELD1	(25)

#घोषणा VPIF_NTSC_HBI_COUNT_FIELD0	(263)
#घोषणा VPIF_NTSC_HBI_COUNT_FIELD1	(262)
#घोषणा VPIF_PAL_HBI_COUNT_FIELD0	(312)
#घोषणा VPIF_PAL_HBI_COUNT_FIELD1	(313)

#घोषणा VPIF_NTSC_VBI_SAMPLES_PER_LINE	(720)
#घोषणा VPIF_PAL_VBI_SAMPLES_PER_LINE	(720)
#घोषणा VPIF_NTSC_HBI_SAMPLES_PER_LINE	(268)
#घोषणा VPIF_PAL_HBI_SAMPLES_PER_LINE	(280)

#घोषणा VPIF_CH_VANC_EN			(0x20)
#घोषणा VPIF_DMA_REQ_SIZE		(0x080)
#घोषणा VPIF_EMULATION_DISABLE		(0x01)

बाह्य u8 irq_vpअगर_capture_channel[VPIF_NUM_CHANNELS];

/* अंतरभूत function to enable/disable channel0 */
अटल अंतरभूत व्योम enable_channel0(पूर्णांक enable)
अणु
	अगर (enable)
		regw((regr(VPIF_CH0_CTRL) | (VPIF_CH0_EN)), VPIF_CH0_CTRL);
	अन्यथा
		regw((regr(VPIF_CH0_CTRL) & (~VPIF_CH0_EN)), VPIF_CH0_CTRL);
पूर्ण

/* अंतरभूत function to enable/disable channel1 */
अटल अंतरभूत व्योम enable_channel1(पूर्णांक enable)
अणु
	अगर (enable)
		regw((regr(VPIF_CH1_CTRL) | (VPIF_CH1_EN)), VPIF_CH1_CTRL);
	अन्यथा
		regw((regr(VPIF_CH1_CTRL) & (~VPIF_CH1_EN)), VPIF_CH1_CTRL);
पूर्ण

/* अंतरभूत function to enable पूर्णांकerrupt क्रम channel0 */
अटल अंतरभूत व्योम channel0_पूर्णांकr_enable(पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vpअगर_lock, flags);

	अगर (enable) अणु
		regw((regr(VPIF_INTEN) | 0x10), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);

		regw((regr(VPIF_INTEN) | VPIF_INTEN_FRAME_CH0), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH0),
							VPIF_INTEN_SET);
	पूर्ण अन्यथा अणु
		regw((regr(VPIF_INTEN) & (~VPIF_INTEN_FRAME_CH0)), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH0),
							VPIF_INTEN_SET);
	पूर्ण
	spin_unlock_irqrestore(&vpअगर_lock, flags);
पूर्ण

/* अंतरभूत function to enable पूर्णांकerrupt क्रम channel1 */
अटल अंतरभूत व्योम channel1_पूर्णांकr_enable(पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vpअगर_lock, flags);

	अगर (enable) अणु
		regw((regr(VPIF_INTEN) | 0x10), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);

		regw((regr(VPIF_INTEN) | VPIF_INTEN_FRAME_CH1), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH1),
							VPIF_INTEN_SET);
	पूर्ण अन्यथा अणु
		regw((regr(VPIF_INTEN) & (~VPIF_INTEN_FRAME_CH1)), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH1),
							VPIF_INTEN_SET);
	पूर्ण
	spin_unlock_irqrestore(&vpअगर_lock, flags);
पूर्ण

/* अंतरभूत function to set buffer addresses in हाल of Y/C non mux mode */
अटल अंतरभूत व्योम ch0_set_videobuf_addr_yc_nmux(अचिन्हित दीर्घ top_strt_luma,
						 अचिन्हित दीर्घ bपंचांग_strt_luma,
						 अचिन्हित दीर्घ top_strt_chroma,
						 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु
	regw(top_strt_luma, VPIF_CH0_TOP_STRT_ADD_LUMA);
	regw(bपंचांग_strt_luma, VPIF_CH0_BTM_STRT_ADD_LUMA);
	regw(top_strt_chroma, VPIF_CH1_TOP_STRT_ADD_CHROMA);
	regw(bपंचांग_strt_chroma, VPIF_CH1_BTM_STRT_ADD_CHROMA);
पूर्ण

/* अंतरभूत function to set buffer addresses in VPIF रेजिस्टरs क्रम video data */
अटल अंतरभूत व्योम ch0_set_videobuf_addr(अचिन्हित दीर्घ top_strt_luma,
					 अचिन्हित दीर्घ bपंचांग_strt_luma,
					 अचिन्हित दीर्घ top_strt_chroma,
					 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु
	regw(top_strt_luma, VPIF_CH0_TOP_STRT_ADD_LUMA);
	regw(bपंचांग_strt_luma, VPIF_CH0_BTM_STRT_ADD_LUMA);
	regw(top_strt_chroma, VPIF_CH0_TOP_STRT_ADD_CHROMA);
	regw(bपंचांग_strt_chroma, VPIF_CH0_BTM_STRT_ADD_CHROMA);
पूर्ण

अटल अंतरभूत व्योम ch1_set_videobuf_addr(अचिन्हित दीर्घ top_strt_luma,
					 अचिन्हित दीर्घ bपंचांग_strt_luma,
					 अचिन्हित दीर्घ top_strt_chroma,
					 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु

	regw(top_strt_luma, VPIF_CH1_TOP_STRT_ADD_LUMA);
	regw(bपंचांग_strt_luma, VPIF_CH1_BTM_STRT_ADD_LUMA);
	regw(top_strt_chroma, VPIF_CH1_TOP_STRT_ADD_CHROMA);
	regw(bपंचांग_strt_chroma, VPIF_CH1_BTM_STRT_ADD_CHROMA);
पूर्ण

अटल अंतरभूत व्योम ch0_set_vbi_addr(अचिन्हित दीर्घ top_vbi,
	अचिन्हित दीर्घ bपंचांग_vbi, अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	regw(top_vbi, VPIF_CH0_TOP_STRT_ADD_VANC);
	regw(bपंचांग_vbi, VPIF_CH0_BTM_STRT_ADD_VANC);
पूर्ण

अटल अंतरभूत व्योम ch0_set_hbi_addr(अचिन्हित दीर्घ top_vbi,
	अचिन्हित दीर्घ bपंचांग_vbi, अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	regw(top_vbi, VPIF_CH0_TOP_STRT_ADD_HANC);
	regw(bपंचांग_vbi, VPIF_CH0_BTM_STRT_ADD_HANC);
पूर्ण

अटल अंतरभूत व्योम ch1_set_vbi_addr(अचिन्हित दीर्घ top_vbi,
	अचिन्हित दीर्घ bपंचांग_vbi, अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	regw(top_vbi, VPIF_CH1_TOP_STRT_ADD_VANC);
	regw(bपंचांग_vbi, VPIF_CH1_BTM_STRT_ADD_VANC);
पूर्ण

अटल अंतरभूत व्योम ch1_set_hbi_addr(अचिन्हित दीर्घ top_vbi,
	अचिन्हित दीर्घ bपंचांग_vbi, अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	regw(top_vbi, VPIF_CH1_TOP_STRT_ADD_HANC);
	regw(bपंचांग_vbi, VPIF_CH1_BTM_STRT_ADD_HANC);
पूर्ण

/* Inline function to enable raw vbi in the given channel */
अटल अंतरभूत व्योम disable_raw_feature(u8 channel_id, u8 index)
अणु
	u32 ctrl_reg;
	अगर (0 == channel_id)
		ctrl_reg = VPIF_CH0_CTRL;
	अन्यथा
		ctrl_reg = VPIF_CH1_CTRL;

	अगर (1 == index)
		vpअगर_clr_bit(ctrl_reg, VPIF_CH_VANC_EN_BIT);
	अन्यथा
		vpअगर_clr_bit(ctrl_reg, VPIF_CH_HANC_EN_BIT);
पूर्ण

अटल अंतरभूत व्योम enable_raw_feature(u8 channel_id, u8 index)
अणु
	u32 ctrl_reg;
	अगर (0 == channel_id)
		ctrl_reg = VPIF_CH0_CTRL;
	अन्यथा
		ctrl_reg = VPIF_CH1_CTRL;

	अगर (1 == index)
		vpअगर_set_bit(ctrl_reg, VPIF_CH_VANC_EN_BIT);
	अन्यथा
		vpअगर_set_bit(ctrl_reg, VPIF_CH_HANC_EN_BIT);
पूर्ण

/* अंतरभूत function to enable/disable channel2 */
अटल अंतरभूत व्योम enable_channel2(पूर्णांक enable)
अणु
	अगर (enable) अणु
		regw((regr(VPIF_CH2_CTRL) | (VPIF_CH2_CLK_EN)), VPIF_CH2_CTRL);
		regw((regr(VPIF_CH2_CTRL) | (VPIF_CH2_EN)), VPIF_CH2_CTRL);
	पूर्ण अन्यथा अणु
		regw((regr(VPIF_CH2_CTRL) & (~VPIF_CH2_CLK_EN)), VPIF_CH2_CTRL);
		regw((regr(VPIF_CH2_CTRL) & (~VPIF_CH2_EN)), VPIF_CH2_CTRL);
	पूर्ण
पूर्ण

/* अंतरभूत function to enable/disable channel3 */
अटल अंतरभूत व्योम enable_channel3(पूर्णांक enable)
अणु
	अगर (enable) अणु
		regw((regr(VPIF_CH3_CTRL) | (VPIF_CH3_CLK_EN)), VPIF_CH3_CTRL);
		regw((regr(VPIF_CH3_CTRL) | (VPIF_CH3_EN)), VPIF_CH3_CTRL);
	पूर्ण अन्यथा अणु
		regw((regr(VPIF_CH3_CTRL) & (~VPIF_CH3_CLK_EN)), VPIF_CH3_CTRL);
		regw((regr(VPIF_CH3_CTRL) & (~VPIF_CH3_EN)), VPIF_CH3_CTRL);
	पूर्ण
पूर्ण

/* अंतरभूत function to enable पूर्णांकerrupt क्रम channel2 */
अटल अंतरभूत व्योम channel2_पूर्णांकr_enable(पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vpअगर_lock, flags);

	अगर (enable) अणु
		regw((regr(VPIF_INTEN) | 0x10), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);
		regw((regr(VPIF_INTEN) | VPIF_INTEN_FRAME_CH2), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH2),
							VPIF_INTEN_SET);
	पूर्ण अन्यथा अणु
		regw((regr(VPIF_INTEN) & (~VPIF_INTEN_FRAME_CH2)), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH2),
							VPIF_INTEN_SET);
	पूर्ण
	spin_unlock_irqrestore(&vpअगर_lock, flags);
पूर्ण

/* अंतरभूत function to enable पूर्णांकerrupt क्रम channel3 */
अटल अंतरभूत व्योम channel3_पूर्णांकr_enable(पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vpअगर_lock, flags);

	अगर (enable) अणु
		regw((regr(VPIF_INTEN) | 0x10), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | 0x10), VPIF_INTEN_SET);

		regw((regr(VPIF_INTEN) | VPIF_INTEN_FRAME_CH3), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH3),
							VPIF_INTEN_SET);
	पूर्ण अन्यथा अणु
		regw((regr(VPIF_INTEN) & (~VPIF_INTEN_FRAME_CH3)), VPIF_INTEN);
		regw((regr(VPIF_INTEN_SET) | VPIF_INTEN_FRAME_CH3),
							VPIF_INTEN_SET);
	पूर्ण
	spin_unlock_irqrestore(&vpअगर_lock, flags);
पूर्ण

/* अंतरभूत function to enable raw vbi data क्रम channel2 */
अटल अंतरभूत व्योम channel2_raw_enable(पूर्णांक enable, u8 index)
अणु
	u32 mask;

	अगर (1 == index)
		mask = VPIF_CH_VANC_EN_BIT;
	अन्यथा
		mask = VPIF_CH_HANC_EN_BIT;

	अगर (enable)
		vpअगर_set_bit(VPIF_CH2_CTRL, mask);
	अन्यथा
		vpअगर_clr_bit(VPIF_CH2_CTRL, mask);
पूर्ण

/* अंतरभूत function to enable raw vbi data क्रम channel3*/
अटल अंतरभूत व्योम channel3_raw_enable(पूर्णांक enable, u8 index)
अणु
	u32 mask;

	अगर (1 == index)
		mask = VPIF_CH_VANC_EN_BIT;
	अन्यथा
		mask = VPIF_CH_HANC_EN_BIT;

	अगर (enable)
		vpअगर_set_bit(VPIF_CH3_CTRL, mask);
	अन्यथा
		vpअगर_clr_bit(VPIF_CH3_CTRL, mask);
पूर्ण

/* function to enable clipping (क्रम both active and blanking regions) on ch 2 */
अटल अंतरभूत व्योम channel2_clipping_enable(पूर्णांक enable)
अणु
	अगर (enable) अणु
		vpअगर_set_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ANC_EN);
		vpअगर_set_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ACTIVE_EN);
	पूर्ण अन्यथा अणु
		vpअगर_clr_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ANC_EN);
		vpअगर_clr_bit(VPIF_CH2_CTRL, VPIF_CH2_CLIP_ACTIVE_EN);
	पूर्ण
पूर्ण

/* function to enable clipping (क्रम both active and blanking regions) on ch 3 */
अटल अंतरभूत व्योम channel3_clipping_enable(पूर्णांक enable)
अणु
	अगर (enable) अणु
		vpअगर_set_bit(VPIF_CH3_CTRL, VPIF_CH3_CLIP_ANC_EN);
		vpअगर_set_bit(VPIF_CH3_CTRL, VPIF_CH3_CLIP_ACTIVE_EN);
	पूर्ण अन्यथा अणु
		vpअगर_clr_bit(VPIF_CH3_CTRL, VPIF_CH3_CLIP_ANC_EN);
		vpअगर_clr_bit(VPIF_CH3_CTRL, VPIF_CH3_CLIP_ACTIVE_EN);
	पूर्ण
पूर्ण

/* अंतरभूत function to set buffer addresses in हाल of Y/C non mux mode */
अटल अंतरभूत व्योम ch2_set_videobuf_addr_yc_nmux(अचिन्हित दीर्घ top_strt_luma,
						 अचिन्हित दीर्घ bपंचांग_strt_luma,
						 अचिन्हित दीर्घ top_strt_chroma,
						 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु
	regw(top_strt_luma, VPIF_CH2_TOP_STRT_ADD_LUMA);
	regw(bपंचांग_strt_luma, VPIF_CH2_BTM_STRT_ADD_LUMA);
	regw(top_strt_chroma, VPIF_CH3_TOP_STRT_ADD_CHROMA);
	regw(bपंचांग_strt_chroma, VPIF_CH3_BTM_STRT_ADD_CHROMA);
पूर्ण

/* अंतरभूत function to set buffer addresses in VPIF रेजिस्टरs क्रम video data */
अटल अंतरभूत व्योम ch2_set_videobuf_addr(अचिन्हित दीर्घ top_strt_luma,
					 अचिन्हित दीर्घ bपंचांग_strt_luma,
					 अचिन्हित दीर्घ top_strt_chroma,
					 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु
	regw(top_strt_luma, VPIF_CH2_TOP_STRT_ADD_LUMA);
	regw(bपंचांग_strt_luma, VPIF_CH2_BTM_STRT_ADD_LUMA);
	regw(top_strt_chroma, VPIF_CH2_TOP_STRT_ADD_CHROMA);
	regw(bपंचांग_strt_chroma, VPIF_CH2_BTM_STRT_ADD_CHROMA);
पूर्ण

अटल अंतरभूत व्योम ch3_set_videobuf_addr(अचिन्हित दीर्घ top_strt_luma,
					 अचिन्हित दीर्घ bपंचांग_strt_luma,
					 अचिन्हित दीर्घ top_strt_chroma,
					 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु
	regw(top_strt_luma, VPIF_CH3_TOP_STRT_ADD_LUMA);
	regw(bपंचांग_strt_luma, VPIF_CH3_BTM_STRT_ADD_LUMA);
	regw(top_strt_chroma, VPIF_CH3_TOP_STRT_ADD_CHROMA);
	regw(bपंचांग_strt_chroma, VPIF_CH3_BTM_STRT_ADD_CHROMA);
पूर्ण

/* अंतरभूत function to set buffer addresses in VPIF रेजिस्टरs क्रम vbi data */
अटल अंतरभूत व्योम ch2_set_vbi_addr(अचिन्हित दीर्घ top_strt_luma,
					 अचिन्हित दीर्घ bपंचांग_strt_luma,
					 अचिन्हित दीर्घ top_strt_chroma,
					 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु
	regw(top_strt_luma, VPIF_CH2_TOP_STRT_ADD_VANC);
	regw(bपंचांग_strt_luma, VPIF_CH2_BTM_STRT_ADD_VANC);
पूर्ण

अटल अंतरभूत व्योम ch3_set_vbi_addr(अचिन्हित दीर्घ top_strt_luma,
					 अचिन्हित दीर्घ bपंचांग_strt_luma,
					 अचिन्हित दीर्घ top_strt_chroma,
					 अचिन्हित दीर्घ bपंचांग_strt_chroma)
अणु
	regw(top_strt_luma, VPIF_CH3_TOP_STRT_ADD_VANC);
	regw(bपंचांग_strt_luma, VPIF_CH3_BTM_STRT_ADD_VANC);
पूर्ण

अटल अंतरभूत पूर्णांक vpअगर_पूर्णांकr_status(पूर्णांक channel)
अणु
	पूर्णांक status = 0;
	पूर्णांक mask;

	अगर (channel < 0 || channel > 3)
		वापस 0;

	mask = 1 << channel;
	status = regr(VPIF_STATUS) & mask;
	regw(status, VPIF_STATUS_CLR);

	वापस status;
पूर्ण

#घोषणा VPIF_MAX_NAME	(30)

/* This काष्ठाure will store size parameters as per the mode selected by user */
काष्ठा vpअगर_channel_config_params अणु
	अक्षर name[VPIF_MAX_NAME];	/* Name of the mode */
	u16 width;			/* Indicates width of the image */
	u16 height;			/* Indicates height of the image */
	u8 frm_fmt;			/* Interlaced (0) or progressive (1) */
	u8 ycmux_mode;			/* This mode requires one (0) or two (1)
					   channels */
	u16 eav2sav;			/* length of eav 2 sav */
	u16 sav2eav;			/* length of sav 2 eav */
	u16 l1, l3, l5, l7, l9, l11;	/* Other parameter configurations */
	u16 vsize;			/* Vertical size of the image */
	u8 capture_क्रमmat;		/* Indicates whether capture क्रमmat
					 * is in BT or in CCD/CMOS */
	u8  vbi_supported;		/* Indicates whether this mode
					 * supports capturing vbi or not */
	u8 hd_sd;			/* HDTV (1) or SDTV (0) क्रमmat */
	v4l2_std_id stdid;		/* SDTV क्रमmat */
	काष्ठा v4l2_dv_timings dv_timings;	/* HDTV क्रमmat */
पूर्ण;

बाह्य स्थिर अचिन्हित पूर्णांक vpअगर_ch_params_count;
बाह्य स्थिर काष्ठा vpअगर_channel_config_params vpअगर_ch_params[];

काष्ठा vpअगर_video_params;
काष्ठा vpअगर_params;
काष्ठा vpअगर_vbi_params;

पूर्णांक vpअगर_set_video_params(काष्ठा vpअगर_params *vpअगरparams, u8 channel_id);
व्योम vpअगर_set_vbi_display_params(काष्ठा vpअगर_vbi_params *vbiparams,
							u8 channel_id);
पूर्णांक vpअगर_channel_getfid(u8 channel_id);

क्रमागत data_size अणु
	_8BITS = 0,
	_10BITS,
	_12BITS,
पूर्ण;

/* Structure क्रम vpअगर parameters क्रम raw vbi data */
काष्ठा vpअगर_vbi_params अणु
	__u32 hstart0;  /* Horizontal start of raw vbi data क्रम first field */
	__u32 vstart0;  /* Vertical start of raw vbi data क्रम first field */
	__u32 hsize0;   /* Horizontal size of raw vbi data क्रम first field */
	__u32 vsize0;   /* Vertical size of raw vbi data क्रम first field */
	__u32 hstart1;  /* Horizontal start of raw vbi data क्रम second field */
	__u32 vstart1;  /* Vertical start of raw vbi data क्रम second field */
	__u32 hsize1;   /* Horizontal size of raw vbi data क्रम second field */
	__u32 vsize1;   /* Vertical size of raw vbi data क्रम second field */
पूर्ण;

/* काष्ठाure क्रम vpअगर parameters */
काष्ठा vpअगर_video_params अणु
	__u8 storage_mode;	/* Indicates field or frame mode */
	अचिन्हित दीर्घ hpitch;
	v4l2_std_id stdid;
पूर्ण;

काष्ठा vpअगर_params अणु
	काष्ठा vpअगर_पूर्णांकerface अगरace;
	काष्ठा vpअगर_video_params video_params;
	काष्ठा vpअगर_channel_config_params std_info;
	जोड़ param अणु
		काष्ठा vpअगर_vbi_params	vbi_params;
		क्रमागत data_size data_sz;
	पूर्ण params;
पूर्ण;

#पूर्ण_अगर				/* End of #अगर_अघोषित VPIF_H */

