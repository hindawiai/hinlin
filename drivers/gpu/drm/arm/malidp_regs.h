<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Liviu Dudau <Liviu.Dudau@arm.com>
 *
 * ARM Mali DP500/DP550/DP650 रेजिस्टरs definition.
 */

#अगर_अघोषित __MALIDP_REGS_H__
#घोषणा __MALIDP_REGS_H__

/*
 * abbreviations used:
 *    - DC - display core (general settings)
 *    - DE - display engine
 *    - SE - scaling engine
 */

/* पूर्णांकerrupt bit masks */
#घोषणा MALIDP_DE_IRQ_UNDERRUN			(1 << 0)

#घोषणा MALIDP500_DE_IRQ_AXI_ERR		(1 << 4)
#घोषणा MALIDP500_DE_IRQ_VSYNC			(1 << 5)
#घोषणा MALIDP500_DE_IRQ_PROG_LINE		(1 << 6)
#घोषणा MALIDP500_DE_IRQ_SATURATION		(1 << 7)
#घोषणा MALIDP500_DE_IRQ_CONF_VALID		(1 << 8)
#घोषणा MALIDP500_DE_IRQ_CONF_MODE		(1 << 11)
#घोषणा MALIDP500_DE_IRQ_CONF_ACTIVE		(1 << 17)
#घोषणा MALIDP500_DE_IRQ_PM_ACTIVE		(1 << 18)
#घोषणा MALIDP500_DE_IRQ_TESTMODE_ACTIVE	(1 << 19)
#घोषणा MALIDP500_DE_IRQ_FORCE_BLNK_ACTIVE	(1 << 24)
#घोषणा MALIDP500_DE_IRQ_AXI_BUSY		(1 << 28)
#घोषणा MALIDP500_DE_IRQ_GLOBAL			(1 << 31)
#घोषणा MALIDP500_SE_IRQ_CONF_MODE		(1 << 0)
#घोषणा MALIDP500_SE_IRQ_CONF_VALID		(1 << 4)
#घोषणा MALIDP500_SE_IRQ_INIT_BUSY		(1 << 5)
#घोषणा MALIDP500_SE_IRQ_AXI_ERROR		(1 << 8)
#घोषणा MALIDP500_SE_IRQ_OVERRUN		(1 << 9)
#घोषणा MALIDP500_SE_IRQ_PROG_LINE1		(1 << 12)
#घोषणा MALIDP500_SE_IRQ_PROG_LINE2		(1 << 13)
#घोषणा MALIDP500_SE_IRQ_CONF_ACTIVE		(1 << 17)
#घोषणा MALIDP500_SE_IRQ_PM_ACTIVE		(1 << 18)
#घोषणा MALIDP500_SE_IRQ_AXI_BUSY		(1 << 28)
#घोषणा MALIDP500_SE_IRQ_GLOBAL			(1 << 31)

#घोषणा MALIDP550_DE_IRQ_SATURATION		(1 << 8)
#घोषणा MALIDP550_DE_IRQ_VSYNC			(1 << 12)
#घोषणा MALIDP550_DE_IRQ_PROG_LINE		(1 << 13)
#घोषणा MALIDP550_DE_IRQ_AXI_ERR		(1 << 16)
#घोषणा MALIDP550_SE_IRQ_EOW			(1 << 0)
#घोषणा MALIDP550_SE_IRQ_AXI_ERR		(1 << 16)
#घोषणा MALIDP550_SE_IRQ_OVR			(1 << 17)
#घोषणा MALIDP550_SE_IRQ_IBSY			(1 << 18)
#घोषणा MALIDP550_DC_IRQ_CONF_VALID		(1 << 0)
#घोषणा MALIDP550_DC_IRQ_CONF_MODE		(1 << 4)
#घोषणा MALIDP550_DC_IRQ_CONF_ACTIVE		(1 << 16)
#घोषणा MALIDP550_DC_IRQ_DE			(1 << 20)
#घोषणा MALIDP550_DC_IRQ_SE			(1 << 24)

#घोषणा MALIDP650_DE_IRQ_DRIFT			(1 << 4)
#घोषणा MALIDP650_DE_IRQ_ACEV1			(1 << 17)
#घोषणा MALIDP650_DE_IRQ_ACEV2			(1 << 18)
#घोषणा MALIDP650_DE_IRQ_ACEG			(1 << 19)
#घोषणा MALIDP650_DE_IRQ_AXIEP			(1 << 28)

/* bit masks that are common between products */
#घोषणा   MALIDP_CFG_VALID		(1 << 0)
#घोषणा   MALIDP_DISP_FUNC_GAMMA	(1 << 0)
#घोषणा   MALIDP_DISP_FUNC_CADJ		(1 << 4)
#घोषणा   MALIDP_DISP_FUNC_ILACED	(1 << 8)
#घोषणा   MALIDP_SCALE_ENGINE_EN	(1 << 16)
#घोषणा   MALIDP_SE_MEMWRITE_EN		(2 << 5)

/* रेजिस्टर offsets क्रम IRQ management */
#घोषणा MALIDP_REG_STATUS		0x00000
#घोषणा MALIDP_REG_SETIRQ		0x00004
#घोषणा MALIDP_REG_MASKIRQ		0x00008
#घोषणा MALIDP_REG_CLEARIRQ		0x0000c

/* रेजिस्टर offsets */
#घोषणा MALIDP_DE_CORE_ID		0x00018
#घोषणा MALIDP_DE_DISPLAY_FUNC		0x00020

/* these offsets are relative to MALIDP5x0_TIMINGS_BASE */
#घोषणा MALIDP_DE_H_TIMINGS		0x0
#घोषणा MALIDP_DE_V_TIMINGS		0x4
#घोषणा MALIDP_DE_SYNC_WIDTH		0x8
#घोषणा MALIDP_DE_HV_ACTIVE		0xc

/* Stride रेजिस्टर offsets relative to Lx_BASE */
#घोषणा MALIDP_DE_LG_STRIDE		0x18
#घोषणा MALIDP_DE_LV_STRIDE0		0x18
#घोषणा MALIDP550_DE_LS_R1_STRIDE	0x28

/* macros to set values पूर्णांकo रेजिस्टरs */
#घोषणा MALIDP_DE_H_FRONTPORCH(x)	(((x) & 0xfff) << 0)
#घोषणा MALIDP_DE_H_BACKPORCH(x)	(((x) & 0x3ff) << 16)
#घोषणा MALIDP500_DE_V_FRONTPORCH(x)	(((x) & 0xff) << 0)
#घोषणा MALIDP550_DE_V_FRONTPORCH(x)	(((x) & 0xfff) << 0)
#घोषणा MALIDP_DE_V_BACKPORCH(x)	(((x) & 0xff) << 16)
#घोषणा MALIDP_DE_H_SYNCWIDTH(x)	(((x) & 0x3ff) << 0)
#घोषणा MALIDP_DE_V_SYNCWIDTH(x)	(((x) & 0xff) << 16)
#घोषणा MALIDP_DE_H_ACTIVE(x)		(((x) & 0x1fff) << 0)
#घोषणा MALIDP_DE_V_ACTIVE(x)		(((x) & 0x1fff) << 16)

#घोषणा MALIDP_PRODUCT_ID(__core_id) ((u32)(__core_id) >> 16)

/* रेजिस्टर offsets relative to MALIDP5x0_COEFFS_BASE */
#घोषणा MALIDP_COLOR_ADJ_COEF		0x00000
#घोषणा MALIDP_COEF_TABLE_ADDR		0x00030
#घोषणा MALIDP_COEF_TABLE_DATA		0x00034

/* Scaling engine रेजिस्टरs and masks. */
#घोषणा   MALIDP_SE_SCALING_EN			(1 << 0)
#घोषणा   MALIDP_SE_ALPHA_EN			(1 << 1)
#घोषणा   MALIDP_SE_ENH_MASK			3
#घोषणा   MALIDP_SE_ENH(x)			(((x) & MALIDP_SE_ENH_MASK) << 2)
#घोषणा   MALIDP_SE_RGBO_IF_EN			(1 << 4)
#घोषणा   MALIDP550_SE_CTL_SEL_MASK		7
#घोषणा   MALIDP550_SE_CTL_VCSEL(x) \
		(((x) & MALIDP550_SE_CTL_SEL_MASK) << 20)
#घोषणा   MALIDP550_SE_CTL_HCSEL(x) \
		(((x) & MALIDP550_SE_CTL_SEL_MASK) << 16)

/* Blocks with offsets from SE_CONTROL रेजिस्टर. */
#घोषणा MALIDP_SE_LAYER_CONTROL			0x14
#घोषणा   MALIDP_SE_L0_IN_SIZE			0x00
#घोषणा   MALIDP_SE_L0_OUT_SIZE			0x04
#घोषणा   MALIDP_SE_SET_V_SIZE(x)		(((x) & 0x1fff) << 16)
#घोषणा   MALIDP_SE_SET_H_SIZE(x)		(((x) & 0x1fff) << 0)
#घोषणा MALIDP_SE_SCALING_CONTROL		0x24
#घोषणा   MALIDP_SE_H_INIT_PH			0x00
#घोषणा   MALIDP_SE_H_DELTA_PH			0x04
#घोषणा   MALIDP_SE_V_INIT_PH			0x08
#घोषणा   MALIDP_SE_V_DELTA_PH			0x0c
#घोषणा   MALIDP_SE_COEFFTAB_ADDR		0x10
#घोषणा     MALIDP_SE_COEFFTAB_ADDR_MASK	0x7f
#घोषणा     MALIDP_SE_V_COEFFTAB		(1 << 8)
#घोषणा     MALIDP_SE_H_COEFFTAB		(1 << 9)
#घोषणा     MALIDP_SE_SET_V_COEFFTAB_ADDR(x) \
		(MALIDP_SE_V_COEFFTAB | ((x) & MALIDP_SE_COEFFTAB_ADDR_MASK))
#घोषणा     MALIDP_SE_SET_H_COEFFTAB_ADDR(x) \
		(MALIDP_SE_H_COEFFTAB | ((x) & MALIDP_SE_COEFFTAB_ADDR_MASK))
#घोषणा   MALIDP_SE_COEFFTAB_DATA		0x14
#घोषणा     MALIDP_SE_COEFFTAB_DATA_MASK	0x3fff
#घोषणा     MALIDP_SE_SET_COEFFTAB_DATA(x) \
		((x) & MALIDP_SE_COEFFTAB_DATA_MASK)
/* Enhance coeffents reigster offset */
#घोषणा MALIDP_SE_IMAGE_ENH			0x3C
/* ENH_LIMITS offset 0x0 */
#घोषणा     MALIDP_SE_ENH_LOW_LEVEL		24
#घोषणा     MALIDP_SE_ENH_HIGH_LEVEL		63
#घोषणा     MALIDP_SE_ENH_LIMIT_MASK		0xfff
#घोषणा     MALIDP_SE_SET_ENH_LIMIT_LOW(x) \
		((x) & MALIDP_SE_ENH_LIMIT_MASK)
#घोषणा     MALIDP_SE_SET_ENH_LIMIT_HIGH(x) \
		(((x) & MALIDP_SE_ENH_LIMIT_MASK) << 16)
#घोषणा   MALIDP_SE_ENH_COEFF0			0x04


/* रेजिस्टर offsets relative to MALIDP5x0_SE_MEMWRITE_BASE */
#घोषणा MALIDP_MW_FORMAT		0x00000
#घोषणा MALIDP_MW_P1_STRIDE		0x00004
#घोषणा MALIDP_MW_P2_STRIDE		0x00008
#घोषणा MALIDP_MW_P1_PTR_LOW		0x0000c
#घोषणा MALIDP_MW_P1_PTR_HIGH		0x00010
#घोषणा MALIDP_MW_P2_PTR_LOW		0x0002c
#घोषणा MALIDP_MW_P2_PTR_HIGH		0x00030

/* रेजिस्टर offsets and bits specअगरic to DP500 */
#घोषणा MALIDP500_ADDR_SPACE_SIZE	0x01000
#घोषणा MALIDP500_DC_BASE		0x00000
#घोषणा MALIDP500_DC_CONTROL		0x0000c
#घोषणा   MALIDP500_DC_CONFIG_REQ	(1 << 17)
#घोषणा   MALIDP500_HSYNCPOL		(1 << 20)
#घोषणा   MALIDP500_VSYNCPOL		(1 << 21)
#घोषणा   MALIDP500_DC_CLEAR_MASK	0x300fff
#घोषणा MALIDP500_DE_LINE_COUNTER	0x00010
#घोषणा MALIDP500_DE_AXI_CONTROL	0x00014
#घोषणा MALIDP500_DE_SECURE_CTRL	0x0001c
#घोषणा MALIDP500_DE_CHROMA_KEY		0x00024
#घोषणा MALIDP500_TIMINGS_BASE		0x00028

#घोषणा MALIDP500_CONFIG_3D		0x00038
#घोषणा MALIDP500_BGND_COLOR		0x0003c
#घोषणा MALIDP500_OUTPUT_DEPTH		0x00044
#घोषणा MALIDP500_COEFFS_BASE		0x00078

/*
 * The YUV2RGB coefficients on the DP500 are not in the video layer's रेजिस्टर
 * block. They beदीर्घ in a separate block above the layer's रेजिस्टरs, hence
 * the negative offset.
 */
#घोषणा MALIDP500_LV_YUV2RGB		((s16)(-0xB8))
#घोषणा MALIDP500_DE_LV_BASE		0x00100
#घोषणा MALIDP500_DE_LV_PTR_BASE	0x00124
#घोषणा MALIDP500_DE_LV_AD_CTRL		0x00400
#घोषणा MALIDP500_DE_LG1_BASE		0x00200
#घोषणा MALIDP500_DE_LG1_PTR_BASE	0x0021c
#घोषणा MALIDP500_DE_LG1_AD_CTRL	0x0040c
#घोषणा MALIDP500_DE_LG2_BASE		0x00300
#घोषणा MALIDP500_DE_LG2_PTR_BASE	0x0031c
#घोषणा MALIDP500_DE_LG2_AD_CTRL	0x00418
#घोषणा MALIDP500_SE_BASE		0x00c00
#घोषणा MALIDP500_SE_CONTROL		0x00c0c
#घोषणा MALIDP500_SE_MEMWRITE_OUT_SIZE	0x00c2c
#घोषणा MALIDP500_SE_RGB_YUV_COEFFS	0x00C74
#घोषणा MALIDP500_SE_MEMWRITE_BASE	0x00e00
#घोषणा MALIDP500_DC_IRQ_BASE		0x00f00
#घोषणा MALIDP500_CONFIG_VALID		0x00f00
#घोषणा MALIDP500_CONFIG_ID		0x00fd4

/*
 * The quality of service (QoS) रेजिस्टर on the DP500. RQOS रेजिस्टर values
 * are driven by the ARQOS संकेत, using AXI transacations, dependent on the
 * FIFO input level.
 * The RQOS रेजिस्टर can also set QoS levels क्रम:
 *    - RED_ARQOS   @ A 4-bit संकेत value क्रम बंद to underflow conditions
 *    - GREEN_ARQOS @ A 4-bit संकेत value क्रम normal conditions
 */
#घोषणा MALIDP500_RQOS_QUALITY          0x00500

/* रेजिस्टर offsets and bits specअगरic to DP550/DP650 */
#घोषणा MALIDP550_ADDR_SPACE_SIZE	0x10000
#घोषणा MALIDP550_DE_CONTROL		0x00010
#घोषणा MALIDP550_DE_LINE_COUNTER	0x00014
#घोषणा MALIDP550_DE_AXI_CONTROL	0x00018
#घोषणा MALIDP550_DE_QOS		0x0001c
#घोषणा MALIDP550_TIMINGS_BASE		0x00030
#घोषणा MALIDP550_HSYNCPOL		(1 << 12)
#घोषणा MALIDP550_VSYNCPOL		(1 << 28)

#घोषणा MALIDP550_DE_DISP_SIDEBAND	0x00040
#घोषणा MALIDP550_DE_BGND_COLOR		0x00044
#घोषणा MALIDP550_DE_OUTPUT_DEPTH	0x0004c
#घोषणा MALIDP550_COEFFS_BASE		0x00050
#घोषणा MALIDP550_LV_YUV2RGB		0x00084
#घोषणा MALIDP550_DE_LV1_BASE		0x00100
#घोषणा MALIDP550_DE_LV1_PTR_BASE	0x00124
#घोषणा MALIDP550_DE_LV1_AD_CTRL	0x001B8
#घोषणा MALIDP550_DE_LV2_BASE		0x00200
#घोषणा MALIDP550_DE_LV2_PTR_BASE	0x00224
#घोषणा MALIDP550_DE_LV2_AD_CTRL	0x002B8
#घोषणा MALIDP550_DE_LG_BASE		0x00300
#घोषणा MALIDP550_DE_LG_PTR_BASE	0x0031c
#घोषणा MALIDP550_DE_LG_AD_CTRL		0x00330
#घोषणा MALIDP550_DE_LS_BASE		0x00400
#घोषणा MALIDP550_DE_LS_PTR_BASE	0x0042c
#घोषणा MALIDP550_DE_PERF_BASE		0x00500
#घोषणा MALIDP550_SE_BASE		0x08000
#घोषणा MALIDP550_SE_CONTROL		0x08010
#घोषणा   MALIDP550_SE_MEMWRITE_ONESHOT	(1 << 7)
#घोषणा MALIDP550_SE_MEMWRITE_OUT_SIZE	0x08030
#घोषणा MALIDP550_SE_RGB_YUV_COEFFS	0x08078
#घोषणा MALIDP550_SE_MEMWRITE_BASE	0x08100
#घोषणा MALIDP550_DC_BASE		0x0c000
#घोषणा MALIDP550_DC_CONTROL		0x0c010
#घोषणा   MALIDP550_DC_CONFIG_REQ	(1 << 16)
#घोषणा MALIDP550_CONFIG_VALID		0x0c014
#घोषणा MALIDP550_CONFIG_ID		0x0ffd4

/* रेजिस्टर offsets specअगरic to DP650 */
#घोषणा MALIDP650_DE_LV_MMU_CTRL	0x000D0
#घोषणा MALIDP650_DE_LG_MMU_CTRL	0x00048
#घोषणा MALIDP650_DE_LS_MMU_CTRL	0x00078

/* bit masks to set the MMU control रेजिस्टर */
#घोषणा MALIDP_MMU_CTRL_EN		(1 << 0)
#घोषणा MALIDP_MMU_CTRL_MODE		(1 << 4)
#घोषणा MALIDP_MMU_CTRL_PX_PS(x)	(1 << (8 + (x)))
#घोषणा MALIDP_MMU_CTRL_PP_NUM_REQ(x)	(((x) & 0x7f) << 12)

/* AFBC रेजिस्टर offsets relative to MALIDPXXX_DE_LX_AD_CTRL */
/* The following रेजिस्टर offsets are common क्रम DP500, DP550 and DP650 */
#घोषणा MALIDP_AD_CROP_H                0x4
#घोषणा MALIDP_AD_CROP_V                0x8
#घोषणा MALIDP_AD_END_PTR_LOW           0xc
#घोषणा MALIDP_AD_END_PTR_HIGH          0x10

/* AFBC decoder Registers */
#घोषणा MALIDP_AD_EN                    BIT(0)
#घोषणा MALIDP_AD_YTR                   BIT(4)
#घोषणा MALIDP_AD_BS                    BIT(8)
#घोषणा MALIDP_AD_CROP_RIGHT_OFFSET     16
#घोषणा MALIDP_AD_CROP_BOTTOM_OFFSET    16

/*
 * Starting with DP550 the रेजिस्टर map blocks has been standardised to the
 * following layout:
 *
 *   Offset            Block रेजिस्टरs
 *  0x00000            Display Engine
 *  0x08000            Scaling Engine
 *  0x0c000            Display Core
 *  0x10000            Secure control
 *
 * The old DP500 IP mixes some DC with the DE रेजिस्टरs, hence the need
 * क्रम a mapping काष्ठाure.
 */

#पूर्ण_अगर /* __MALIDP_REGS_H__ */
