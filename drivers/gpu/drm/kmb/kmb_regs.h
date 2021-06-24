<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 *
 * Copyright तऊ 2018-2020 Intel Corporation
 */

#अगर_अघोषित __KMB_REGS_H__
#घोषणा __KMB_REGS_H__

/***************************************************************************
 *		   LCD controller control रेजिस्टर defines
 ***************************************************************************/
#घोषणा LCD_CONTROL				(0x4 * 0x000)
#घोषणा LCD_CTRL_PROGRESSIVE			  (0 << 0)
#घोषणा LCD_CTRL_INTERLACED			  BIT(0)
#घोषणा LCD_CTRL_ENABLE				  BIT(1)
#घोषणा LCD_CTRL_VL1_ENABLE			  BIT(2)
#घोषणा LCD_CTRL_VL2_ENABLE			  BIT(3)
#घोषणा LCD_CTRL_GL1_ENABLE			  BIT(4)
#घोषणा LCD_CTRL_GL2_ENABLE			  BIT(5)
#घोषणा LCD_CTRL_ALPHA_BLEND_VL1		  (0 << 6)
#घोषणा LCD_CTRL_ALPHA_BLEND_VL2		  BIT(6)
#घोषणा LCD_CTRL_ALPHA_BLEND_GL1		  (2 << 6)
#घोषणा LCD_CTRL_ALPHA_BLEND_GL2		  (3 << 6)
#घोषणा LCD_CTRL_ALPHA_TOP_VL1			  (0 << 8)
#घोषणा LCD_CTRL_ALPHA_TOP_VL2			  BIT(8)
#घोषणा LCD_CTRL_ALPHA_TOP_GL1			  (2 << 8)
#घोषणा LCD_CTRL_ALPHA_TOP_GL2			  (3 << 8)
#घोषणा LCD_CTRL_ALPHA_MIDDLE_VL1		  (0 << 10)
#घोषणा LCD_CTRL_ALPHA_MIDDLE_VL2		  BIT(10)
#घोषणा LCD_CTRL_ALPHA_MIDDLE_GL1		  (2 << 10)
#घोषणा LCD_CTRL_ALPHA_MIDDLE_GL2		  (3 << 10)
#घोषणा LCD_CTRL_ALPHA_BOTTOM_VL1		  (0 << 12)
#घोषणा LCD_CTRL_ALPHA_BOTTOM_VL2		  BIT(12)
#घोषणा LCD_CTRL_ALPHA_BOTTOM_GL1		  (2 << 12)
#घोषणा LCD_CTRL_ALPHA_BOTTOM_GL2		  (3 << 12)
#घोषणा LCD_CTRL_TIM_GEN_ENABLE			  BIT(14)
#घोषणा LCD_CTRL_CONTINUOUS			  (0 << 15)
#घोषणा LCD_CTRL_ONE_SHOT			  BIT(15)
#घोषणा LCD_CTRL_PWM0_EN			  BIT(16)
#घोषणा LCD_CTRL_PWM1_EN			  BIT(17)
#घोषणा LCD_CTRL_PWM2_EN			  BIT(18)
#घोषणा LCD_CTRL_OUTPUT_DISABLED		  (0 << 19)
#घोषणा LCD_CTRL_OUTPUT_ENABLED			  BIT(19)
#घोषणा LCD_CTRL_BPORCH_ENABLE			  BIT(21)
#घोषणा LCD_CTRL_FPORCH_ENABLE			  BIT(22)
#घोषणा LCD_CTRL_PIPELINE_DMA			  BIT(28)
#घोषणा LCD_CTRL_VHSYNC_IDLE_LVL		  BIT(31)

/* पूर्णांकerrupts */
#घोषणा LCD_INT_STATUS				(0x4 * 0x001)
#घोषणा LCD_INT_खातापूर्ण				  BIT(0)
#घोषणा LCD_INT_LINE_CMP			  BIT(1)
#घोषणा LCD_INT_VERT_COMP			  BIT(2)
#घोषणा LAYER0_DMA_DONE				  BIT(3)
#घोषणा LAYER0_DMA_IDLE				  BIT(4)
#घोषणा LAYER0_DMA_FIFO_OVERFLOW		  BIT(5)
#घोषणा LAYER0_DMA_FIFO_UNDERFLOW		  BIT(6)
#घोषणा LAYER0_DMA_CB_FIFO_OVERFLOW		  BIT(7)
#घोषणा LAYER0_DMA_CB_FIFO_UNDERFLOW		  BIT(8)
#घोषणा LAYER0_DMA_CR_FIFO_OVERFLOW		  BIT(9)
#घोषणा LAYER0_DMA_CR_FIFO_UNDERFLOW		  BIT(10)
#घोषणा LAYER1_DMA_DONE				  BIT(11)
#घोषणा LAYER1_DMA_IDLE				  BIT(12)
#घोषणा LAYER1_DMA_FIFO_OVERFLOW		  BIT(13)
#घोषणा LAYER1_DMA_FIFO_UNDERFLOW		  BIT(14)
#घोषणा LAYER1_DMA_CB_FIFO_OVERFLOW		  BIT(15)
#घोषणा LAYER1_DMA_CB_FIFO_UNDERFLOW		  BIT(16)
#घोषणा LAYER1_DMA_CR_FIFO_OVERFLOW		  BIT(17)
#घोषणा LAYER1_DMA_CR_FIFO_UNDERFLOW		  BIT(18)
#घोषणा LAYER2_DMA_DONE				  BIT(19)
#घोषणा LAYER2_DMA_IDLE				  BIT(20)
#घोषणा LAYER2_DMA_FIFO_OVERFLOW		  BIT(21)
#घोषणा LAYER2_DMA_FIFO_UNDERFLOW		  BIT(22)
#घोषणा LAYER3_DMA_DONE				  BIT(23)
#घोषणा LAYER3_DMA_IDLE				  BIT(24)
#घोषणा LAYER3_DMA_FIFO_OVERFLOW		  BIT(25)
#घोषणा LAYER3_DMA_FIFO_UNDERFLOW		  BIT(26)
#घोषणा LCD_INT_LAYER				  (0x07fffff8)
#घोषणा LCD_INT_ENABLE				(0x4 * 0x002)
#घोषणा LCD_INT_CLEAR				(0x4 * 0x003)
#घोषणा LCD_LINE_COUNT				(0x4 * 0x004)
#घोषणा LCD_LINE_COMPARE			(0x4 * 0x005)
#घोषणा LCD_VSTATUS				(0x4 * 0x006)

/*LCD_VSTATUS_COMPARE Vertcal पूर्णांकerval in which to generate vertcal
 * पूर्णांकerval पूर्णांकerrupt
 */
/* BITS 13 and 14 */
#घोषणा LCD_VSTATUS_COMPARE			(0x4 * 0x007)
#घोषणा LCD_VSTATUS_VERTICAL_STATUS_MASK	  (3 << 13)
#घोषणा LCD_VSTATUS_COMPARE_VSYNC		  (0 << 13)
#घोषणा LCD_VSTATUS_COMPARE_BACKPORCH		  BIT(13)
#घोषणा LCD_VSTATUS_COMPARE_ACTIVE		  (2 << 13)
#घोषणा LCD_VSTATUS_COMPARE_FRONT_PORCH		  (3 << 13)

#घोषणा LCD_SCREEN_WIDTH			(0x4 * 0x008)
#घोषणा LCD_SCREEN_HEIGHT			(0x4 * 0x009)
#घोषणा LCD_FIELD_INT_CFG			(0x4 * 0x00a)
#घोषणा LCD_FIFO_FLUSH				(0x4 * 0x00b)
#घोषणा LCD_BG_COLOUR_LS			(0x4 * 0x00c)
#घोषणा LCD_BG_COLOUR_MS			(0x4 * 0x00d)
#घोषणा LCD_RAM_CFG			        (0x4 * 0x00e)

/****************************************************************************
 *		   LCD controller Layer config रेजिस्टर
 ***************************************************************************/
#घोषणा LCD_LAYER0_CFG		        (0x4 * 0x100)
#घोषणा LCD_LAYERn_CFG(N)			(LCD_LAYER0_CFG + (0x400 * (N)))
#घोषणा LCD_LAYER_SCALE_H			BIT(1)
#घोषणा LCD_LAYER_SCALE_V			BIT(2)
#घोषणा LCD_LAYER_SCALE_H_V			(LCD_LAYER_SCALE_H | \
						      LCD_LAYER_SCALE_V)
#घोषणा LCD_LAYER_CSC_EN			BIT(3)
#घोषणा LCD_LAYER_ALPHA_STATIC			BIT(4)
#घोषणा LCD_LAYER_ALPHA_EMBED			BIT(5)
#घोषणा LCD_LAYER_ALPHA_COMBI			(LCD_LAYER_ALPHA_STATIC | \
						      LCD_LAYER_ALPHA_EMBED)
/* RGB multiplied with alpha */
#घोषणा LCD_LAYER_ALPHA_PREMULT			BIT(6)
#घोषणा LCD_LAYER_INVERT_COL			BIT(7)
#घोषणा LCD_LAYER_TRANSPARENT_EN		BIT(8)
#घोषणा LCD_LAYER_FORMAT_YCBCR444PLAN		(0 << 9)
#घोषणा LCD_LAYER_FORMAT_YCBCR422PLAN		BIT(9)
#घोषणा LCD_LAYER_FORMAT_YCBCR420PLAN		(2 << 9)
#घोषणा LCD_LAYER_FORMAT_RGB888PLAN		(3 << 9)
#घोषणा LCD_LAYER_FORMAT_YCBCR444LIN		(4 << 9)
#घोषणा LCD_LAYER_FORMAT_YCBCR422LIN		(5 << 9)
#घोषणा LCD_LAYER_FORMAT_RGB888			(6 << 9)
#घोषणा LCD_LAYER_FORMAT_RGBA8888		(7 << 9)
#घोषणा LCD_LAYER_FORMAT_RGBX8888		(8 << 9)
#घोषणा LCD_LAYER_FORMAT_RGB565			(9 << 9)
#घोषणा LCD_LAYER_FORMAT_RGBA1555		(0xa << 9)
#घोषणा LCD_LAYER_FORMAT_XRGB1555		(0xb << 9)
#घोषणा LCD_LAYER_FORMAT_RGB444			(0xc << 9)
#घोषणा LCD_LAYER_FORMAT_RGBA4444		(0xd << 9)
#घोषणा LCD_LAYER_FORMAT_RGBX4444		(0xe << 9)
#घोषणा LCD_LAYER_FORMAT_RGB332			(0xf << 9)
#घोषणा LCD_LAYER_FORMAT_RGBA3328		(0x10 << 9)
#घोषणा LCD_LAYER_FORMAT_RGBX3328		(0x11 << 9)
#घोषणा LCD_LAYER_FORMAT_CLUT			(0x12 << 9)
#घोषणा LCD_LAYER_FORMAT_NV12			(0x1c << 9)
#घोषणा LCD_LAYER_PLANAR_STORAGE		BIT(14)
#घोषणा LCD_LAYER_8BPP				(0 << 15)
#घोषणा LCD_LAYER_16BPP				BIT(15)
#घोषणा LCD_LAYER_24BPP				(2 << 15)
#घोषणा LCD_LAYER_32BPP				(3 << 15)
#घोषणा LCD_LAYER_Y_ORDER			BIT(17)
#घोषणा LCD_LAYER_CRCB_ORDER			BIT(18)
#घोषणा LCD_LAYER_BGR_ORDER			BIT(19)
#घोषणा LCD_LAYER_LUT_2ENT			(0 << 20)
#घोषणा LCD_LAYER_LUT_4ENT			BIT(20)
#घोषणा LCD_LAYER_LUT_16ENT			(2 << 20)
#घोषणा LCD_LAYER_NO_FLIP			(0 << 22)
#घोषणा LCD_LAYER_FLIP_V			BIT(22)
#घोषणा LCD_LAYER_FLIP_H			(2 << 22)
#घोषणा LCD_LAYER_ROT_R90			(3 << 22)
#घोषणा LCD_LAYER_ROT_L90			(4 << 22)
#घोषणा LCD_LAYER_ROT_180			(5 << 22)
#घोषणा LCD_LAYER_FIFO_00			(0 << 25)
#घोषणा LCD_LAYER_FIFO_25			BIT(25)
#घोषणा LCD_LAYER_FIFO_50			(2 << 25)
#घोषणा LCD_LAYER_FIFO_100			(3 << 25)
#घोषणा LCD_LAYER_INTERLEAVE_DIS		(0 << 27)
#घोषणा LCD_LAYER_INTERLEAVE_V			BIT(27)
#घोषणा LCD_LAYER_INTERLEAVE_H			(2 << 27)
#घोषणा LCD_LAYER_INTERLEAVE_CH			(3 << 27)
#घोषणा LCD_LAYER_INTERLEAVE_V_SUB		(4 << 27)
#घोषणा LCD_LAYER_INTERLEAVE_H_SUB		(5 << 27)
#घोषणा LCD_LAYER_INTERLEAVE_CH_SUB		(6 << 27)
#घोषणा LCD_LAYER_INTER_POS_EVEN		(0 << 30)
#घोषणा LCD_LAYER_INTER_POS_ODD			BIT(30)

#घोषणा LCD_LAYER0_COL_START		(0x4 * 0x101)
#घोषणा LCD_LAYERn_COL_START(N)		(LCD_LAYER0_COL_START + (0x400 * (N)))
#घोषणा LCD_LAYER0_ROW_START		(0x4 * 0x102)
#घोषणा LCD_LAYERn_ROW_START(N)		(LCD_LAYER0_ROW_START + (0x400 * (N)))
#घोषणा LCD_LAYER0_WIDTH		(0x4 * 0x103)
#घोषणा LCD_LAYERn_WIDTH(N)		(LCD_LAYER0_WIDTH + (0x400 * (N)))
#घोषणा LCD_LAYER0_HEIGHT		(0x4 * 0x104)
#घोषणा LCD_LAYERn_HEIGHT(N)		(LCD_LAYER0_HEIGHT + (0x400 * (N)))
#घोषणा LCD_LAYER0_SCALE_CFG		(0x4 * 0x105)
#घोषणा LCD_LAYERn_SCALE_CFG(N)		(LCD_LAYER0_SCALE_CFG + (0x400 * (N)))
#घोषणा LCD_LAYER0_ALPHA		(0x4 * 0x106)
#घोषणा LCD_LAYERn_ALPHA(N)		(LCD_LAYER0_ALPHA + (0x400 * (N)))
#घोषणा LCD_LAYER0_INV_COLOUR_LS	(0x4 * 0x107)
#घोषणा LCD_LAYERn_INV_COLOUR_LS(N)	(LCD_LAYER0_INV_COLOUR_LS + \
					(0x400 * (N)))
#घोषणा LCD_LAYER0_INV_COLOUR_MS	(0x4 * 0x108)
#घोषणा LCD_LAYERn_INV_COLOUR_MS(N)	(LCD_LAYER0_INV_COLOUR_MS + \
					(0x400 * (N)))
#घोषणा LCD_LAYER0_TRANS_COLOUR_LS	(0x4 * 0x109)
#घोषणा LCD_LAYERn_TRANS_COLOUR_LS(N)	(LCD_LAYER0_TRANS_COLOUR_LS + \
					(0x400 * (N)))
#घोषणा LCD_LAYER0_TRANS_COLOUR_MS	(0x4 * 0x10a)
#घोषणा LCD_LAYERn_TRANS_COLOUR_MS(N)	(LCD_LAYER0_TRANS_COLOUR_MS + \
					(0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF11		(0x4 * 0x10b)
#घोषणा LCD_LAYERn_CSC_COEFF11(N)	(LCD_LAYER0_CSC_COEFF11 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF12		(0x4 * 0x10c)
#घोषणा LCD_LAYERn_CSC_COEFF12(N)	(LCD_LAYER0_CSC_COEFF12 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF13		(0x4 * 0x10d)
#घोषणा LCD_LAYERn_CSC_COEFF13(N)	(LCD_LAYER0_CSC_COEFF13 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF21		(0x4 * 0x10e)
#घोषणा LCD_LAYERn_CSC_COEFF21(N)	(LCD_LAYER0_CSC_COEFF21 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF22		(0x4 * 0x10f)
#घोषणा LCD_LAYERn_CSC_COEFF22(N)	(LCD_LAYER0_CSC_COEFF22 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF23		(0x4 * 0x110)
#घोषणा LCD_LAYERn_CSC_COEFF23(N)	(LCD_LAYER0_CSC_COEFF23 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF31		(0x4 * 0x111)
#घोषणा LCD_LAYERn_CSC_COEFF31(N)	(LCD_LAYER0_CSC_COEFF31 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF32		(0x4 * 0x112)
#घोषणा LCD_LAYERn_CSC_COEFF32(N)	(LCD_LAYER0_CSC_COEFF32 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_COEFF33		(0x4 * 0x113)
#घोषणा LCD_LAYERn_CSC_COEFF33(N)	(LCD_LAYER0_CSC_COEFF33 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_OFF1		(0x4 * 0x114)
#घोषणा LCD_LAYERn_CSC_OFF1(N)		(LCD_LAYER0_CSC_OFF1 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_OFF2		(0x4 * 0x115)
#घोषणा LCD_LAYERn_CSC_OFF2(N)		(LCD_LAYER0_CSC_OFF2 + (0x400 * (N)))
#घोषणा LCD_LAYER0_CSC_OFF3		(0x4 * 0x116)
#घोषणा LCD_LAYERn_CSC_OFF3(N)		(LCD_LAYER0_CSC_OFF3 + (0x400 * (N)))

/* LCD controller Layer DMA config रेजिस्टर */
#घोषणा LCD_LAYER0_DMA_CFG			(0x4 * 0x117)
#घोषणा LCD_LAYERn_DMA_CFG(N)			(LCD_LAYER0_DMA_CFG + \
						(0x400 * (N)))
#घोषणा LCD_DMA_LAYER_ENABLE			  BIT(0)
#घोषणा LCD_DMA_LAYER_STATUS			  BIT(1)
#घोषणा LCD_DMA_LAYER_AUTO_UPDATE		  BIT(2)
#घोषणा LCD_DMA_LAYER_CONT_UPDATE		  BIT(3)
#घोषणा LCD_DMA_LAYER_CONT_PING_PONG_UPDATE	  (LCD_DMA_LAYER_AUTO_UPDATE \
						| LCD_DMA_LAYER_CONT_UPDATE)
#घोषणा LCD_DMA_LAYER_FIFO_ADR_MODE		  BIT(4)
#घोषणा LCD_DMA_LAYER_AXI_BURST_1		  BIT(5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_2		  (2 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_3		  (3 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_4		  (4 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_5		  (5 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_6		  (6 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_7		  (7 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_8		  (8 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_9		  (9 << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_10		  (0xa << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_11		  (0xb << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_12		  (0xc << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_13		  (0xd << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_14		  (0xe << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_15		  (0xf << 5)
#घोषणा LCD_DMA_LAYER_AXI_BURST_16		  (0x10 << 5)
#घोषणा LCD_DMA_LAYER_VSTRIDE_EN		  BIT(10)

#घोषणा LCD_LAYER0_DMA_START_ADR		(0x4 * 0x118)
#घोषणा LCD_LAYERn_DMA_START_ADDR(N)		(LCD_LAYER0_DMA_START_ADR \
						+ (0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_START_SHADOW		(0x4 * 0x119)
#घोषणा LCD_LAYERn_DMA_START_SHADOW(N)		(LCD_LAYER0_DMA_START_SHADOW \
						+ (0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_LEN			(0x4 * 0x11a)
#घोषणा LCD_LAYERn_DMA_LEN(N)			(LCD_LAYER0_DMA_LEN + \
						(0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_LEN_SHADOW		(0x4 * 0x11b)
#घोषणा LCD_LAYERn_DMA_LEN_SHADOW(N)		(LCD_LAYER0_DMA_LEN_SHADOW + \
						(0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_STATUS			(0x4 * 0x11c)
#घोषणा LCD_LAYERn_DMA_STATUS(N)		(LCD_LAYER0_DMA_STATUS + \
						(0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_LINE_WIDTH		(0x4 * 0x11d)
#घोषणा LCD_LAYERn_DMA_LINE_WIDTH(N)		(LCD_LAYER0_DMA_LINE_WIDTH + \
						(0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_LINE_VSTRIDE		(0x4 * 0x11e)
#घोषणा LCD_LAYERn_DMA_LINE_VSTRIDE(N)		(LCD_LAYER0_DMA_LINE_VSTRIDE +\
						(0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_FIFO_STATUS		(0x4 * 0x11f)
#घोषणा LCD_LAYERn_DMA_FIFO_STATUS(N)		(LCD_LAYER0_DMA_FIFO_STATUS + \
						(0x400 * (N)))
#घोषणा LCD_LAYER0_CFG2				(0x4 * 0x120)
#घोषणा LCD_LAYERn_CFG2(N)			(LCD_LAYER0_CFG2 + (0x400 * (N)))
#घोषणा LCD_LAYER0_DMA_START_CB_ADR		(0x4 * 0x700)
#घोषणा LCD_LAYERn_DMA_START_CB_ADR(N)		(LCD_LAYER0_DMA_START_CB_ADR + \
						(0x20 * (N)))
#घोषणा LCD_LAYER0_DMA_START_CB_SHADOW		(0x4 * 0x701)
#घोषणा LCD_LAYERn_DMA_START_CB_SHADOW(N)	(LCD_LAYER0_DMA_START_CB_SHADOW\
						+ (0x20 * (N)))
#घोषणा LCD_LAYER0_DMA_CB_LINE_WIDTH		(0x4 * 0x702)
#घोषणा LCD_LAYERn_DMA_CB_LINE_WIDTH(N)		(LCD_LAYER0_DMA_CB_LINE_WIDTH +\
						(0x20 * (N)))
#घोषणा LCD_LAYER0_DMA_CB_LINE_VSTRIDE		(0x4 * 0x703)
#घोषणा LCD_LAYERn_DMA_CB_LINE_VSTRIDE(N)	(LCD_LAYER0_DMA_CB_LINE_VSTRIDE\
						+ (0x20 * (N)))
#घोषणा LCD_LAYER0_DMA_START_CR_ADR		(0x4 * 0x704)
#घोषणा LCD_LAYERn_DMA_START_CR_ADR(N)		(LCD_LAYER0_DMA_START_CR_ADR + \
						(0x20 * (N)))
#घोषणा LCD_LAYER0_DMA_START_CR_SHADOW		(0x4 * 0x705)
#घोषणा LCD_LAYERn_DMA_START_CR_SHADOW(N)	\
						(LCD_LAYER0_DMA_START_CR_SHADOW\
						 + (0x20 * (N)))
#घोषणा LCD_LAYER0_DMA_CR_LINE_WIDTH		(0x4 * 0x706)
#घोषणा LCD_LAYERn_DMA_CR_LINE_WIDTH(N)		(LCD_LAYER0_DMA_CR_LINE_WIDTH +\
						(0x20 * (N)))
#घोषणा LCD_LAYER0_DMA_CR_LINE_VSTRIDE		(0x4 * 0x707)
#घोषणा LCD_LAYERn_DMA_CR_LINE_VSTRIDE(N)	(LCD_LAYER0_DMA_CR_LINE_VSTRIDE\
						+ (0x20 * (N)))
#घोषणा LCD_LAYER1_DMA_START_CB_ADR		(0x4 * 0x708)
#घोषणा LCD_LAYER1_DMA_START_CB_SHADOW		(0x4 * 0x709)
#घोषणा LCD_LAYER1_DMA_CB_LINE_WIDTH		(0x4 * 0x70a)
#घोषणा LCD_LAYER1_DMA_CB_LINE_VSTRIDE		(0x4 * 0x70b)
#घोषणा LCD_LAYER1_DMA_START_CR_ADR		(0x4 * 0x70c)
#घोषणा LCD_LAYER1_DMA_START_CR_SHADOW		(0x4 * 0x70d)
#घोषणा LCD_LAYER1_DMA_CR_LINE_WIDTH		(0x4 * 0x70e)
#घोषणा LCD_LAYER1_DMA_CR_LINE_VSTRIDE		(0x4 * 0x70f)

/****************************************************************************
 *		   LCD controller output क्रमmat रेजिस्टर defines
 ***************************************************************************/
#घोषणा LCD_OUT_FORMAT_CFG			(0x4 * 0x800)
#घोषणा LCD_OUTF_FORMAT_RGB121212                 (0x00)
#घोषणा LCD_OUTF_FORMAT_RGB101010                 (0x01)
#घोषणा LCD_OUTF_FORMAT_RGB888                    (0x02)
#घोषणा LCD_OUTF_FORMAT_RGB666                    (0x03)
#घोषणा LCD_OUTF_FORMAT_RGB565                    (0x04)
#घोषणा LCD_OUTF_FORMAT_RGB444                    (0x05)
#घोषणा LCD_OUTF_FORMAT_MRGB121212                (0x10)
#घोषणा LCD_OUTF_FORMAT_MRGB101010                (0x11)
#घोषणा LCD_OUTF_FORMAT_MRGB888                   (0x12)
#घोषणा LCD_OUTF_FORMAT_MRGB666                   (0x13)
#घोषणा LCD_OUTF_FORMAT_MRGB565                   (0x14)
#घोषणा LCD_OUTF_FORMAT_YCBCR420_8B_LEGACY        (0x08)
#घोषणा LCD_OUTF_FORMAT_YCBCR420_8B_DCI           (0x09)
#घोषणा LCD_OUTF_FORMAT_YCBCR420_8B               (0x0A)
#घोषणा LCD_OUTF_FORMAT_YCBCR420_10B              (0x0B)
#घोषणा LCD_OUTF_FORMAT_YCBCR420_12B              (0x0C)
#घोषणा LCD_OUTF_FORMAT_YCBCR422_8B               (0x0D)
#घोषणा LCD_OUTF_FORMAT_YCBCR422_10B              (0x0E)
#घोषणा LCD_OUTF_FORMAT_YCBCR444                  (0x0F)
#घोषणा LCD_OUTF_FORMAT_MYCBCR420_8B_LEGACY       (0x18)
#घोषणा LCD_OUTF_FORMAT_MYCBCR420_8B_DCI          (0x19)
#घोषणा LCD_OUTF_FORMAT_MYCBCR420_8B              (0x1A)
#घोषणा LCD_OUTF_FORMAT_MYCBCR420_10B             (0x1B)
#घोषणा LCD_OUTF_FORMAT_MYCBCR420_12B             (0x1C)
#घोषणा LCD_OUTF_FORMAT_MYCBCR422_8B              (0x1D)
#घोषणा LCD_OUTF_FORMAT_MYCBCR422_10B             (0x1E)
#घोषणा LCD_OUTF_FORMAT_MYCBCR444                 (0x1F)
#घोषणा LCD_OUTF_BGR_ORDER			  BIT(5)
#घोषणा LCD_OUTF_Y_ORDER			  BIT(6)
#घोषणा LCD_OUTF_CRCB_ORDER			  BIT(7)
#घोषणा LCD_OUTF_SYNC_MODE			  BIT(11)
#घोषणा LCD_OUTF_RGB_CONV_MODE			  BIT(14)
#घोषणा LCD_OUTF_MIPI_RGB_MODE			  BIT(18)

#घोषणा LCD_HSYNC_WIDTH				(0x4 * 0x801)
#घोषणा LCD_H_BACKPORCH				(0x4 * 0x802)
#घोषणा LCD_H_ACTIVEWIDTH			(0x4 * 0x803)
#घोषणा LCD_H_FRONTPORCH			(0x4 * 0x804)
#घोषणा LCD_VSYNC_WIDTH				(0x4 * 0x805)
#घोषणा LCD_V_BACKPORCH				(0x4 * 0x806)
#घोषणा LCD_V_ACTIVEHEIGHT			(0x4 * 0x807)
#घोषणा LCD_V_FRONTPORCH			(0x4 * 0x808)
#घोषणा LCD_VSYNC_START				(0x4 * 0x809)
#घोषणा LCD_VSYNC_END				(0x4 * 0x80a)
#घोषणा LCD_V_BACKPORCH_EVEN			(0x4 * 0x80b)
#घोषणा LCD_VSYNC_WIDTH_EVEN			(0x4 * 0x80c)
#घोषणा LCD_V_ACTIVEHEIGHT_EVEN			(0x4 * 0x80d)
#घोषणा LCD_V_FRONTPORCH_EVEN			(0x4 * 0x80e)
#घोषणा LCD_VSYNC_START_EVEN			(0x4 * 0x80f)
#घोषणा LCD_VSYNC_END_EVEN			(0x4 * 0x810)
#घोषणा LCD_TIMING_GEN_TRIG			(0x4 * 0x811)
#घोषणा LCD_PWM0_CTRL				(0x4 * 0x812)
#घोषणा LCD_PWM0_RPT_LEADIN			(0x4 * 0x813)
#घोषणा LCD_PWM0_HIGH_LOW			(0x4 * 0x814)
#घोषणा LCD_PWM1_CTRL				(0x4 * 0x815)
#घोषणा LCD_PWM1_RPT_LEADIN			(0x4 * 0x816)
#घोषणा LCD_PWM1_HIGH_LOW			(0x4 * 0x817)
#घोषणा LCD_PWM2_CTRL				(0x4 * 0x818)
#घोषणा LCD_PWM2_RPT_LEADIN			(0x4 * 0x819)
#घोषणा LCD_PWM2_HIGH_LOW			(0x4 * 0x81a)
#घोषणा LCD_VIDEO0_DMA0_BYTES			(0x4 * 0xb00)
#घोषणा LCD_VIDEO0_DMA0_STATE			(0x4 * 0xb01)
#घोषणा LCD_DMA_STATE_ACTIVE			  BIT(3)
#घोषणा LCD_VIDEO0_DMA1_BYTES			(0x4 * 0xb02)
#घोषणा LCD_VIDEO0_DMA1_STATE			(0x4 * 0xb03)
#घोषणा LCD_VIDEO0_DMA2_BYTES			(0x4 * 0xb04)
#घोषणा LCD_VIDEO0_DMA2_STATE			(0x4 * 0xb05)
#घोषणा LCD_VIDEO1_DMA0_BYTES			(0x4 * 0xb06)
#घोषणा LCD_VIDEO1_DMA0_STATE			(0x4 * 0xb07)
#घोषणा LCD_VIDEO1_DMA1_BYTES			(0x4 * 0xb08)
#घोषणा LCD_VIDEO1_DMA1_STATE			(0x4 * 0xb09)
#घोषणा LCD_VIDEO1_DMA2_BYTES			(0x4 * 0xb0a)
#घोषणा LCD_VIDEO1_DMA2_STATE			(0x4 * 0xb0b)
#घोषणा LCD_GRAPHIC0_DMA_BYTES			(0x4 * 0xb0c)
#घोषणा LCD_GRAPHIC0_DMA_STATE			(0x4 * 0xb0d)
#घोषणा LCD_GRAPHIC1_DMA_BYTES			(0x4 * 0xb0e)
#घोषणा LCD_GRAPHIC1_DMA_STATE			(0x4 * 0xb0f)

/***************************************************************************
 *		   MIPI controller control रेजिस्टर defines
 *************************************************************************/
#घोषणा MIPI0_HS_BASE_ADDR			(MIPI_BASE_ADDR + 0x400)
#घोषणा HS_OFFSET(M)				(((M) + 1) * 0x400)

#घोषणा MIPI_TX_HS_CTRL				(0x0)
#घोषणा   MIPI_TXm_HS_CTRL(M)			(MIPI_TX_HS_CTRL + HS_OFFSET(M))
#घोषणा   HS_CTRL_EN				BIT(0)
/* 1:CSI 0:DSI */
#घोषणा   HS_CTRL_CSIDSIN			BIT(2)
/* 1:LCD, 0:DMA */
#घोषणा   TX_SOURCE				BIT(3)
#घोषणा   ACTIVE_LANES(n)			((n) << 4)
#घोषणा   LCD_VC(ch)				((ch) << 8)
#घोषणा   DSI_EOTP_EN				BIT(11)
#घोषणा   DSI_CMD_HFP_EN			BIT(12)
#घोषणा   CRC_EN				BIT(14)
#घोषणा   HSEXIT_CNT(n)				((n) << 16)
#घोषणा   HSCLKIDLE_CNT				BIT(24)
#घोषणा MIPI_TX_HS_SYNC_CFG			(0x8)
#घोषणा   MIPI_TXm_HS_SYNC_CFG(M)		(MIPI_TX_HS_SYNC_CFG \
						+ HS_OFFSET(M))
#घोषणा   LINE_SYNC_PKT_ENABLE			BIT(0)
#घोषणा   FRAME_COUNTER_ACTIVE			BIT(1)
#घोषणा   LINE_COUNTER_ACTIVE			BIT(2)
#घोषणा   DSI_V_BLANKING			BIT(4)
#घोषणा   DSI_HSA_BLANKING			BIT(5)
#घोषणा   DSI_HBP_BLANKING			BIT(6)
#घोषणा   DSI_HFP_BLANKING			BIT(7)
#घोषणा   DSI_SYNC_PULSE_EVENTN			BIT(8)
#घोषणा   DSI_LPM_FIRST_VSA_LINE		BIT(9)
#घोषणा   DSI_LPM_LAST_VFP_LINE			BIT(10)
#घोषणा   WAIT_ALL_SECT				BIT(11)
#घोषणा   WAIT_TRIG_POS				BIT(15)
#घोषणा   ALWAYS_USE_HACT(f)			((f) << 19)
#घोषणा   FRAME_GEN_EN(f)			((f) << 23)
#घोषणा   HACT_WAIT_STOP(f)			((f) << 28)
#घोषणा MIPI_TX0_HS_FG0_SECT0_PH		(0x40)
#घोषणा   MIPI_TXm_HS_FGn_SECTo_PH(M, N, O)	(MIPI_TX0_HS_FG0_SECT0_PH + \
						HS_OFFSET(M) + (0x2C * (N)) \
						+ (8 * (O)))
#घोषणा   MIPI_TX_SECT_WC_MASK			(0xffff)
#घोषणा	  MIPI_TX_SECT_VC_MASK			(3)
#घोषणा   MIPI_TX_SECT_VC_SHIFT			(22)
#घोषणा   MIPI_TX_SECT_DT_MASK			(0x3f)
#घोषणा   MIPI_TX_SECT_DT_SHIFT			(16)
#घोषणा   MIPI_TX_SECT_DM_MASK			(3)
#घोषणा   MIPI_TX_SECT_DM_SHIFT			(24)
#घोषणा   MIPI_TX_SECT_DMA_PACKED		BIT(26)
#घोषणा MIPI_TX_HS_FG0_SECT_UNPACKED_BYTES0	(0x60)
#घोषणा MIPI_TX_HS_FG0_SECT_UNPACKED_BYTES1	(0x64)
#घोषणा   MIPI_TXm_HS_FGn_SECT_UNPACKED_BYTES0(M, N)	\
					(MIPI_TX_HS_FG0_SECT_UNPACKED_BYTES0 \
					+ HS_OFFSET(M) + (0x2C * (N)))
#घोषणा MIPI_TX_HS_FG0_SECT0_LINE_CFG		(0x44)
#घोषणा   MIPI_TXm_HS_FGn_SECTo_LINE_CFG(M, N, O)	\
				(MIPI_TX_HS_FG0_SECT0_LINE_CFG + HS_OFFSET(M) \
				+ (0x2C * (N)) + (8 * (O)))

#घोषणा MIPI_TX_HS_FG0_NUM_LINES		(0x68)
#घोषणा   MIPI_TXm_HS_FGn_NUM_LINES(M, N)	\
				(MIPI_TX_HS_FG0_NUM_LINES + HS_OFFSET(M) \
				+ (0x2C * (N)))
#घोषणा MIPI_TX_HS_VSYNC_WIDTHS0		(0x104)
#घोषणा   MIPI_TXm_HS_VSYNC_WIDTHn(M, N)		\
				(MIPI_TX_HS_VSYNC_WIDTHS0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_V_BACKPORCHES0		(0x16c)
#घोषणा   MIPI_TXm_HS_V_BACKPORCHESn(M, N)	\
				(MIPI_TX_HS_V_BACKPORCHES0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_V_FRONTPORCHES0		(0x174)
#घोषणा   MIPI_TXm_HS_V_FRONTPORCHESn(M, N)	\
				(MIPI_TX_HS_V_FRONTPORCHES0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_V_ACTIVE0			(0x17c)
#घोषणा   MIPI_TXm_HS_V_ACTIVEn(M, N)		\
				(MIPI_TX_HS_V_ACTIVE0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_HSYNC_WIDTH0			(0x10c)
#घोषणा   MIPI_TXm_HS_HSYNC_WIDTHn(M, N)		\
				(MIPI_TX_HS_HSYNC_WIDTH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_H_BACKPORCH0			(0x11c)
#घोषणा   MIPI_TXm_HS_H_BACKPORCHn(M, N)		\
				(MIPI_TX_HS_H_BACKPORCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_H_FRONTPORCH0		(0x12c)
#घोषणा   MIPI_TXm_HS_H_FRONTPORCHn(M, N)	\
				(MIPI_TX_HS_H_FRONTPORCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_H_ACTIVE0			(0x184)
#घोषणा   MIPI_TXm_HS_H_ACTIVEn(M, N)		\
				(MIPI_TX_HS_H_ACTIVE0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_LLP_HSYNC_WIDTH0		(0x13c)
#घोषणा   MIPI_TXm_HS_LLP_HSYNC_WIDTHn(M, N)	\
				(MIPI_TX_HS_LLP_HSYNC_WIDTH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_LLP_H_BACKPORCH0		(0x14c)
#घोषणा   MIPI_TXm_HS_LLP_H_BACKPORCHn(M, N)	\
				(MIPI_TX_HS_LLP_H_BACKPORCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा MIPI_TX_HS_LLP_H_FRONTPORCH0		(0x15c)
#घोषणा   MIPI_TXm_HS_LLP_H_FRONTPORCHn(M, N)	\
				(MIPI_TX_HS_LLP_H_FRONTPORCH0 + HS_OFFSET(M) \
				+ (0x4 * (N)))

#घोषणा MIPI_TX_HS_MC_FIFO_CTRL_EN		(0x194)
#घोषणा   MIPI_TXm_HS_MC_FIFO_CTRL_EN(M)	\
				(MIPI_TX_HS_MC_FIFO_CTRL_EN + HS_OFFSET(M))

#घोषणा MIPI_TX_HS_MC_FIFO_CHAN_ALLOC0		(0x198)
#घोषणा MIPI_TX_HS_MC_FIFO_CHAN_ALLOC1		(0x19c)
#घोषणा   MIPI_TXm_HS_MC_FIFO_CHAN_ALLOCn(M, N)	\
			(MIPI_TX_HS_MC_FIFO_CHAN_ALLOC0 + HS_OFFSET(M) \
			+ (0x4 * (N)))
#घोषणा   SET_MC_FIFO_CHAN_ALLOC(dev, ctrl, vc, sz)	\
		kmb_ग_लिखो_bits_mipi(dev, \
				MIPI_TXm_HS_MC_FIFO_CHAN_ALLOCn(ctrl, \
				(vc) / 2), ((vc) % 2) * 16, 16, sz)
#घोषणा MIPI_TX_HS_MC_FIFO_RTHRESHOLD0		(0x1a0)
#घोषणा MIPI_TX_HS_MC_FIFO_RTHRESHOLD1		(0x1a4)
#घोषणा   MIPI_TXm_HS_MC_FIFO_RTHRESHOLDn(M, N)	\
				(MIPI_TX_HS_MC_FIFO_RTHRESHOLD0 + HS_OFFSET(M) \
				+ (0x4 * (N)))
#घोषणा   SET_MC_FIFO_RTHRESHOLD(dev, ctrl, vc, th)	\
	kmb_ग_लिखो_bits_mipi(dev, MIPI_TXm_HS_MC_FIFO_RTHRESHOLDn(ctrl, \
				(vc) / 2), ((vc) % 2) * 16, 16, th)
#घोषणा MIPI_TX_HS_DMA_CFG			(0x1a8)
#घोषणा MIPI_TX_HS_DMA_START_ADR_CHAN0		(0x1ac)
#घोषणा MIPI_TX_HS_DMA_LEN_CHAN0		(0x1b4)

/* MIPI IRQ */
#घोषणा MIPI_CTRL_IRQ_STATUS0				(0x00)
#घोषणा   MIPI_DPHY_ERR_IRQ				1
#घोषणा   MIPI_DPHY_ERR_MASK				0x7FE	/*bits 1-10 */
#घोषणा   MIPI_HS_IRQ					13
/* bits 13-22 */
#घोषणा   MIPI_HS_IRQ_MASK				0x7FE000
#घोषणा   MIPI_LP_EVENT_IRQ				25
#घोषणा   MIPI_GET_IRQ_STAT0(dev)		kmb_पढ़ो_mipi(dev, \
						MIPI_CTRL_IRQ_STATUS0)
#घोषणा MIPI_CTRL_IRQ_STATUS1				(0x04)
#घोषणा   MIPI_HS_RX_EVENT_IRQ				0
#घोषणा   MIPI_GET_IRQ_STAT1(dev)		kmb_पढ़ो_mipi(dev, \
						MIPI_CTRL_IRQ_STATUS1)
#घोषणा MIPI_CTRL_IRQ_ENABLE0				(0x08)
#घोषणा   SET_MIPI_CTRL_IRQ_ENABLE0(dev, M, N)	kmb_set_bit_mipi(dev, \
						MIPI_CTRL_IRQ_ENABLE0, \
						(M) + (N))
#घोषणा   MIPI_GET_IRQ_ENABLED0(dev)		kmb_पढ़ो_mipi(dev, \
						MIPI_CTRL_IRQ_ENABLE0)
#घोषणा MIPI_CTRL_IRQ_ENABLE1				(0x0c)
#घोषणा   MIPI_GET_IRQ_ENABLED1(dev)		kmb_पढ़ो_mipi(dev, \
						MIPI_CTRL_IRQ_ENABLE1)
#घोषणा MIPI_CTRL_IRQ_CLEAR0				(0x010)
#घोषणा   SET_MIPI_CTRL_IRQ_CLEAR0(dev, M, N)		\
		kmb_set_bit_mipi(dev, MIPI_CTRL_IRQ_CLEAR0, (M) + (N))
#घोषणा MIPI_CTRL_IRQ_CLEAR1				(0x014)
#घोषणा   SET_MIPI_CTRL_IRQ_CLEAR1(dev, M, N)		\
		kmb_set_bit_mipi(dev, MIPI_CTRL_IRQ_CLEAR1, (M) + (N))
#घोषणा MIPI_CTRL_DIG_LOOPBACK				(0x018)
#घोषणा MIPI_TX_HS_IRQ_STATUS				(0x01c)
#घोषणा   MIPI_TX_HS_IRQ_STATUSm(M)		(MIPI_TX_HS_IRQ_STATUS + \
						HS_OFFSET(M))
#घोषणा   GET_MIPI_TX_HS_IRQ_STATUS(dev, M)	kmb_पढ़ो_mipi(dev, \
						MIPI_TX_HS_IRQ_STATUSm(M))
#घोषणा   MIPI_TX_HS_IRQ_LINE_COMPARE			BIT(1)
#घोषणा   MIPI_TX_HS_IRQ_FRAME_DONE_0			BIT(2)
#घोषणा   MIPI_TX_HS_IRQ_FRAME_DONE_1			BIT(3)
#घोषणा   MIPI_TX_HS_IRQ_FRAME_DONE_2			BIT(4)
#घोषणा   MIPI_TX_HS_IRQ_FRAME_DONE_3			BIT(5)
#घोषणा   MIPI_TX_HS_IRQ_DMA_DONE_0			BIT(6)
#घोषणा   MIPI_TX_HS_IRQ_DMA_IDLE_0			BIT(7)
#घोषणा   MIPI_TX_HS_IRQ_DMA_DONE_1			BIT(8)
#घोषणा   MIPI_TX_HS_IRQ_DMA_IDLE_1			BIT(9)
#घोषणा   MIPI_TX_HS_IRQ_DMA_DONE_2			BIT(10)
#घोषणा   MIPI_TX_HS_IRQ_DMA_IDLE_2			BIT(11)
#घोषणा   MIPI_TX_HS_IRQ_DMA_DONE_3			BIT(12)
#घोषणा   MIPI_TX_HS_IRQ_DMA_IDLE_3			BIT(13)
#घोषणा   MIPI_TX_HS_IRQ_MC_FIFO_UNDERFLOW		BIT(14)
#घोषणा   MIPI_TX_HS_IRQ_MC_FIFO_OVERFLOW		BIT(15)
#घोषणा   MIPI_TX_HS_IRQ_LLP_FIFO_EMPTY			BIT(16)
#घोषणा   MIPI_TX_HS_IRQ_LLP_REQUEST_QUEUE_FULL		BIT(17)
#घोषणा   MIPI_TX_HS_IRQ_LLP_REQUEST_QUEUE_ERROR	BIT(18)
#घोषणा   MIPI_TX_HS_IRQ_LLP_WORD_COUNT_ERROR		BIT(20)
#घोषणा   MIPI_TX_HS_IRQ_FRAME_DONE			\
				(MIPI_TX_HS_IRQ_FRAME_DONE_0 | \
				MIPI_TX_HS_IRQ_FRAME_DONE_1 | \
				MIPI_TX_HS_IRQ_FRAME_DONE_2 | \
				MIPI_TX_HS_IRQ_FRAME_DONE_3)

#घोषणा MIPI_TX_HS_IRQ_DMA_DONE				\
				(MIPI_TX_HS_IRQ_DMA_DONE_0 | \
				MIPI_TX_HS_IRQ_DMA_DONE_1 | \
				MIPI_TX_HS_IRQ_DMA_DONE_2 | \
				MIPI_TX_HS_IRQ_DMA_DONE_3)

#घोषणा MIPI_TX_HS_IRQ_DMA_IDLE				\
				(MIPI_TX_HS_IRQ_DMA_IDLE_0 | \
				MIPI_TX_HS_IRQ_DMA_IDLE_1 | \
				MIPI_TX_HS_IRQ_DMA_IDLE_2 | \
				MIPI_TX_HS_IRQ_DMA_IDLE_3)

#घोषणा MIPI_TX_HS_IRQ_ERROR				\
				(MIPI_TX_HS_IRQ_MC_FIFO_UNDERFLOW | \
				MIPI_TX_HS_IRQ_MC_FIFO_OVERFLOW | \
				MIPI_TX_HS_IRQ_LLP_FIFO_EMPTY | \
				MIPI_TX_HS_IRQ_LLP_REQUEST_QUEUE_FULL | \
				MIPI_TX_HS_IRQ_LLP_REQUEST_QUEUE_ERROR | \
				MIPI_TX_HS_IRQ_LLP_WORD_COUNT_ERROR)

#घोषणा MIPI_TX_HS_IRQ_ALL				\
				(MIPI_TX_HS_IRQ_FRAME_DONE | \
				MIPI_TX_HS_IRQ_DMA_DONE | \
				MIPI_TX_HS_IRQ_DMA_IDLE | \
				MIPI_TX_HS_IRQ_LINE_COMPARE | \
				MIPI_TX_HS_IRQ_ERROR)

#घोषणा MIPI_TX_HS_IRQ_ENABLE				(0x020)
#घोषणा	  GET_HS_IRQ_ENABLE(dev, M)		kmb_पढ़ो_mipi(dev, \
						MIPI_TX_HS_IRQ_ENABLE \
						+ HS_OFFSET(M))
#घोषणा MIPI_TX_HS_IRQ_CLEAR				(0x024)

/* MIPI Test Pattern Generation */
#घोषणा MIPI_TX_HS_TEST_PAT_CTRL			(0x230)
#घोषणा   MIPI_TXm_HS_TEST_PAT_CTRL(M)			\
				(MIPI_TX_HS_TEST_PAT_CTRL + HS_OFFSET(M))
#घोषणा   TP_EN_VCm(M)					(1 << ((M) * 0x04))
#घोषणा   TP_SEL_VCm(M, N)				\
				((N) << (((M) * 0x04) + 1))
#घोषणा   TP_STRIPE_WIDTH(M)				((M) << 16)
#घोषणा MIPI_TX_HS_TEST_PAT_COLOR0			(0x234)
#घोषणा   MIPI_TXm_HS_TEST_PAT_COLOR0(M)		\
				(MIPI_TX_HS_TEST_PAT_COLOR0 + HS_OFFSET(M))
#घोषणा MIPI_TX_HS_TEST_PAT_COLOR1			(0x238)
#घोषणा   MIPI_TXm_HS_TEST_PAT_COLOR1(M)		\
				(MIPI_TX_HS_TEST_PAT_COLOR1 + HS_OFFSET(M))

/* D-PHY regs */
#घोषणा DPHY_ENABLE				(0x100)
#घोषणा DPHY_INIT_CTRL0				(0x104)
#घोषणा   SHUTDOWNZ				0
#घोषणा   RESETZ				12
#घोषणा DPHY_INIT_CTRL1				(0x108)
#घोषणा   PLL_CLKSEL_0				18
#घोषणा   PLL_SHADOW_CTRL			16
#घोषणा DPHY_INIT_CTRL2				(0x10c)
#घोषणा   SET_DPHY_INIT_CTRL0(dev, dphy, offset)	\
			kmb_set_bit_mipi(dev, DPHY_INIT_CTRL0, \
					((dphy) + (offset)))
#घोषणा   CLR_DPHY_INIT_CTRL0(dev, dphy, offset)	\
			kmb_clr_bit_mipi(dev, DPHY_INIT_CTRL0, \
					((dphy) + (offset)))
#घोषणा DPHY_INIT_CTRL2				(0x10c)
#घोषणा DPHY_PLL_OBS0				(0x110)
#घोषणा DPHY_PLL_OBS1				(0x114)
#घोषणा DPHY_PLL_OBS2				(0x118)
#घोषणा DPHY_FREQ_CTRL0_3			(0x11c)
#घोषणा DPHY_FREQ_CTRL4_7			(0x120)
#घोषणा   SET_DPHY_FREQ_CTRL0_3(dev, dphy, val)	\
			kmb_ग_लिखो_bits_mipi(dev, DPHY_FREQ_CTRL0_3 \
			+ (((dphy) / 4) * 4), (dphy % 4) * 8, 6, val)

#घोषणा DPHY_FORCE_CTRL0			(0x128)
#घोषणा DPHY_FORCE_CTRL1			(0x12C)
#घोषणा MIPI_DPHY_STAT0_3			(0x134)
#घोषणा MIPI_DPHY_STAT4_7			(0x138)
#घोषणा	  GET_STOPSTATE_DATA(dev, dphy)		\
			(((kmb_पढ़ो_mipi(dev, MIPI_DPHY_STAT0_3 + \
					 ((dphy) / 4) * 4)) >> \
					 (((dphy % 4) * 8) + 4)) & 0x03)

#घोषणा MIPI_DPHY_ERR_STAT6_7			(0x14C)

#घोषणा DPHY_TEST_CTRL0				(0x154)
#घोषणा   SET_DPHY_TEST_CTRL0(dev, dphy)		\
			kmb_set_bit_mipi(dev, DPHY_TEST_CTRL0, (dphy))
#घोषणा   CLR_DPHY_TEST_CTRL0(dev, dphy)		\
			kmb_clr_bit_mipi(dev, DPHY_TEST_CTRL0, \
						(dphy))
#घोषणा DPHY_TEST_CTRL1				(0x158)
#घोषणा   SET_DPHY_TEST_CTRL1_CLK(dev, dphy)	\
			kmb_set_bit_mipi(dev, DPHY_TEST_CTRL1, (dphy))
#घोषणा   CLR_DPHY_TEST_CTRL1_CLK(dev, dphy)	\
			kmb_clr_bit_mipi(dev, DPHY_TEST_CTRL1, (dphy))
#घोषणा   SET_DPHY_TEST_CTRL1_EN(dev, dphy)	\
			kmb_set_bit_mipi(dev, DPHY_TEST_CTRL1, ((dphy) + 12))
#घोषणा   CLR_DPHY_TEST_CTRL1_EN(dev, dphy)	\
			kmb_clr_bit_mipi(dev, DPHY_TEST_CTRL1, ((dphy) + 12))
#घोषणा DPHY_TEST_DIN0_3			(0x15c)
#घोषणा   SET_TEST_DIN0_3(dev, dphy, val)		\
			kmb_ग_लिखो_mipi(dev, DPHY_TEST_DIN0_3 + \
			4, ((val) << (((dphy) % 4) * 8)))
#घोषणा DPHY_TEST_DOUT0_3			(0x168)
#घोषणा   GET_TEST_DOUT0_3(dev, dphy)		\
			(kmb_पढ़ो_mipi(dev, DPHY_TEST_DOUT0_3) \
			>> (((dphy) % 4) * 8) & 0xff)
#घोषणा DPHY_TEST_DOUT4_7			(0x16C)
#घोषणा   GET_TEST_DOUT4_7(dev, dphy)		\
			(kmb_पढ़ो_mipi(dev, DPHY_TEST_DOUT4_7) \
			>> (((dphy) % 4) * 8) & 0xff)
#घोषणा DPHY_TEST_DOUT8_9			(0x170)
#घोषणा DPHY_TEST_DIN4_7			(0x160)
#घोषणा DPHY_TEST_DIN8_9			(0x164)
#घोषणा DPHY_PLL_LOCK				(0x188)
#घोषणा   GET_PLL_LOCK(dev, dphy)		\
			(kmb_पढ़ो_mipi(dev, DPHY_PLL_LOCK) \
			& (1 << ((dphy) - MIPI_DPHY6)))
#घोषणा DPHY_CFG_CLK_EN				(0x18c)

#घोषणा MSS_MIPI_CIF_CFG			(0x00)
#घोषणा MSS_LCD_MIPI_CFG			(0x04)
#घोषणा MSS_CAM_CLK_CTRL			(0x10)
#घोषणा MSS_LOOPBACK_CFG			(0x0C)
#घोषणा   LCD					BIT(1)
#घोषणा   MIPI_COMMON				BIT(2)
#घोषणा   MIPI_TX0				BIT(9)
#घोषणा MSS_CAM_RSTN_CTRL			(0x14)
#घोषणा MSS_CAM_RSTN_SET			(0x20)
#घोषणा MSS_CAM_RSTN_CLR			(0x24)

#घोषणा MSSCPU_CPR_CLK_EN			(0x0)
#घोषणा MSSCPU_CPR_RST_EN			(0x10)
#घोषणा BIT_MASK_16				(0xffff)
/* icam lcd qos */
#घोषणा LCD_QOS_PRIORITY			(0x8)
#घोषणा LCD_QOS_MODE				(0xC)
#घोषणा LCD_QOS_BW				(0x10)
#पूर्ण_अगर /* __KMB_REGS_H__ */
