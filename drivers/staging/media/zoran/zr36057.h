<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * zr36057.h - zr36057 रेजिस्टर offsets
 *
 * Copyright (C) 1998 Dave Perks <dperks@ibm.net>
 */

#अगर_अघोषित _ZR36057_H_
#घोषणा _ZR36057_H_

/* Zoran ZR36057 रेजिस्टरs */

#घोषणा ZR36057_VFEHCR          0x000	/* Video Front End, Horizontal Configuration Register */
#घोषणा ZR36057_VFEHCR_HS_POL             BIT(30)
#घोषणा ZR36057_VFEHCR_H_START           10
#घोषणा ZR36057_VFEHCR_H_END		0
#घोषणा ZR36057_VFEHCR_HMASK		0x3ff

#घोषणा ZR36057_VFEVCR          0x004	/* Video Front End, Vertical Configuration Register */
#घोषणा ZR36057_VFEVCR_VS_POL             BIT(30)
#घोषणा ZR36057_VFEVCR_V_START           10
#घोषणा ZR36057_VFEVCR_V_END		0
#घोषणा ZR36057_VFEVCR_VMASK		0x3ff

#घोषणा ZR36057_VFESPFR         0x008	/* Video Front End, Scaler and Pixel Format Register */
#घोषणा ZR36057_VFESPFR_EXT_FL            BIT(26)
#घोषणा ZR36057_VFESPFR_TOP_FIELD         BIT(25)
#घोषणा ZR36057_VFESPFR_VCLK_POL          BIT(24)
#घोषणा ZR36057_VFESPFR_H_FILTER         21
#घोषणा ZR36057_VFESPFR_HOR_DCM          14
#घोषणा ZR36057_VFESPFR_VER_DCM          8
#घोषणा ZR36057_VFESPFR_DISP_MODE        6
#घोषणा ZR36057_VFESPFR_YUV422          (0<<3)
#घोषणा ZR36057_VFESPFR_RGB888          (1<<3)
#घोषणा ZR36057_VFESPFR_RGB565          (2<<3)
#घोषणा ZR36057_VFESPFR_RGB555          (3<<3)
#घोषणा ZR36057_VFESPFR_ERR_DIF          (1<<2)
#घोषणा ZR36057_VFESPFR_PACK24          (1<<1)
#घोषणा ZR36057_VFESPFR_LITTLE_ENDIAN    (1<<0)

#घोषणा ZR36057_VDTR            0x00c	/* Video Display "Top" Register */

#घोषणा ZR36057_VDBR            0x010	/* Video Display "Bottom" Register */

#घोषणा ZR36057_VSSFGR          0x014	/* Video Stride, Status, and Frame Grab Register */
#घोषणा ZR36057_VSSFGR_DISP_STRIDE       16
#घोषणा ZR36057_VSSFGR_VID_OVF            BIT(8)
#घोषणा ZR36057_VSSFGR_SNAP_SHOT          BIT(1)
#घोषणा ZR36057_VSSFGR_FRAME_GRAB         BIT(0)

#घोषणा ZR36057_VDCR            0x018	/* Video Display Configuration Register */
#घोषणा ZR36057_VDCR_VID_EN               BIT(31)
#घोषणा ZR36057_VDCR_MIN_PIX             24
#घोषणा ZR36057_VDCR_TRITON              BIT(24)
#घोषणा ZR36057_VDCR_VID_WIN_HT           12
#घोषणा ZR36057_VDCR_VID_WIN_WID          0

#घोषणा ZR36057_MMTR            0x01c	/* Masking Map "Top" Register */

#घोषणा ZR36057_MMBR            0x020	/* Masking Map "Bottom" Register */

#घोषणा ZR36057_OCR             0x024	/* Overlay Control Register */
#घोषणा ZR36057_OCR_OVL_ENABLE            BIT(15)
#घोषणा ZR36057_OCR_MASK_STRIDE          0

#घोषणा ZR36057_SPGPPCR         0x028	/* System, PCI, and General Purpose Pins Control Register */
#घोषणा ZR36057_SPGPPCR_SOFT_RESET	 BIT(24)

#घोषणा ZR36057_GPPGCR1         0x02c	/* General Purpose Pins and GuestBus Control Register (1) */

#घोषणा ZR36057_MCSAR           0x030	/* MPEG Code Source Address Register */

#घोषणा ZR36057_MCTCR           0x034	/* MPEG Code Transfer Control Register */
#घोषणा ZR36057_MCTCR_COD_TIME            BIT(30)
#घोषणा ZR36057_MCTCR_C_EMPTY             BIT(29)
#घोषणा ZR36057_MCTCR_C_FLUSH             BIT(28)
#घोषणा ZR36057_MCTCR_COD_GUEST_ID	20
#घोषणा ZR36057_MCTCR_COD_GUEST_REG	16

#घोषणा ZR36057_MCMPR           0x038	/* MPEG Code Memory Poपूर्णांकer Register */

#घोषणा ZR36057_ISR             0x03c	/* Interrupt Status Register */
#घोषणा ZR36057_ISR_GIRQ1                BIT(30)
#घोषणा ZR36057_ISR_GIRQ0                BIT(29)
#घोषणा ZR36057_ISR_COD_REP_IRQ            BIT(28)
#घोषणा ZR36057_ISR_JPEG_REP_IRQ           BIT(27)

#घोषणा ZR36057_ICR             0x040	/* Interrupt Control Register */
#घोषणा ZR36057_ICR_GIRQ1                BIT(30)
#घोषणा ZR36057_ICR_GIRQ0                BIT(29)
#घोषणा ZR36057_ICR_COD_REP_IRQ            BIT(28)
#घोषणा ZR36057_ICR_JPEG_REP_IRQ           BIT(27)
#घोषणा ZR36057_ICR_INT_PIN_EN             BIT(24)

#घोषणा ZR36057_I2CBR           0x044	/* I2C Bus Register */
#घोषणा ZR36057_I2CBR_SDA		 BIT(1)
#घोषणा ZR36057_I2CBR_SCL		 BIT(0)

#घोषणा ZR36057_JMC             0x100	/* JPEG Mode and Control */
#घोषणा ZR36057_JMC_JPG                  BIT(31)
#घोषणा ZR36057_JMC_JPG_EXP_MODE          (0 << 29)
#घोषणा ZR36057_JMC_JPG_CMP_MODE           BIT(29)
#घोषणा ZR36057_JMC_MJPG_EXP_MODE         (2 << 29)
#घोषणा ZR36057_JMC_MJPG_CMP_MODE         (3 << 29)
#घोषणा ZR36057_JMC_RTBUSY_FB            BIT(6)
#घोषणा ZR36057_JMC_GO_EN                BIT(5)
#घोषणा ZR36057_JMC_SYNC_MSTR             BIT(4)
#घोषणा ZR36057_JMC_FLD_PER_BUFF         BIT(3)
#घोषणा ZR36057_JMC_VFIFO_FB             BIT(2)
#घोषणा ZR36057_JMC_CFIFO_FB             BIT(1)
#घोषणा ZR36057_JMC_STLL_LIT_ENDIAN       BIT(0)

#घोषणा ZR36057_JPC             0x104	/* JPEG Process Control */
#घोषणा ZR36057_JPC_P_RESET              BIT(7)
#घोषणा ZR36057_JPC_COD_TRNS_EN            BIT(5)
#घोषणा ZR36057_JPC_ACTIVE               BIT(0)

#घोषणा ZR36057_VSP             0x108	/* Vertical Sync Parameters */
#घोषणा ZR36057_VSP_VSYNC_SIZE           16
#घोषणा ZR36057_VSP_FRM_TOT              0

#घोषणा ZR36057_HSP             0x10c	/* Horizontal Sync Parameters */
#घोषणा ZR36057_HSP_HSYNC_START          16
#घोषणा ZR36057_HSP_LINE_TOT             0

#घोषणा ZR36057_FHAP            0x110	/* Field Horizontal Active Portion */
#घोषणा ZR36057_FHAP_NAX                16
#घोषणा ZR36057_FHAP_PAX                0

#घोषणा ZR36057_FVAP            0x114	/* Field Vertical Active Portion */
#घोषणा ZR36057_FVAP_NAY                16
#घोषणा ZR36057_FVAP_PAY                0

#घोषणा ZR36057_FPP             0x118	/* Field Process Parameters */
#घोषणा ZR36057_FPP_ODD_EVEN             BIT(0)

#घोषणा ZR36057_JCBA            0x11c	/* JPEG Code Base Address */

#घोषणा ZR36057_JCFT            0x120	/* JPEG Code FIFO Threshold */

#घोषणा ZR36057_JCGI            0x124	/* JPEG Codec Guest ID */
#घोषणा ZR36057_JCGI_JPE_GUEST_ID         4
#घोषणा ZR36057_JCGI_JPE_GUEST_REG        0

#घोषणा ZR36057_GCR2            0x12c	/* GuestBus Control Register (2) */

#घोषणा ZR36057_POR             0x200	/* Post Office Register */
#घोषणा ZR36057_POR_PO_PEN                BIT(25)
#घोषणा ZR36057_POR_PO_TIME               BIT(24)
#घोषणा ZR36057_POR_PO_सूची                BIT(23)

#घोषणा ZR36057_STR             0x300	/* "Still" Transfer Register */

#पूर्ण_अगर
