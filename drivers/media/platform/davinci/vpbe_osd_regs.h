<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2006-2010 Texas Instruments Inc
 */
#अगर_अघोषित _VPBE_OSD_REGS_H
#घोषणा _VPBE_OSD_REGS_H

/* VPBE Global Registers */
#घोषणा VPBE_PID				0x0
#घोषणा VPBE_PCR				0x4

/* VPSS CLock Registers */
#घोषणा VPSSCLK_PID				0x00
#घोषणा VPSSCLK_CLKCTRL				0x04

/* VPSS Buffer Logic Registers */
#घोषणा VPSSBL_PID				0x00
#घोषणा VPSSBL_PCR				0x04
#घोषणा VPSSBL_BCR				0x08
#घोषणा VPSSBL_INTSTAT				0x0C
#घोषणा VPSSBL_INTSEL				0x10
#घोषणा VPSSBL_EVTSEL				0x14
#घोषणा VPSSBL_MEMCTRL				0x18
#घोषणा VPSSBL_CCDCMUX				0x1C

/* DM365 ISP5 प्रणाली configuration */
#घोषणा ISP5_PID				0x0
#घोषणा ISP5_PCCR				0x4
#घोषणा ISP5_BCR				0x8
#घोषणा ISP5_INTSTAT				0xC
#घोषणा ISP5_INTSEL1				0x10
#घोषणा ISP5_INTSEL2				0x14
#घोषणा ISP5_INTSEL3				0x18
#घोषणा ISP5_EVTSEL				0x1c
#घोषणा ISP5_CCDCMUX				0x20

/* VPBE On-Screen Display Subप्रणाली Registers (OSD) */
#घोषणा OSD_MODE				0x00
#घोषणा OSD_VIDWINMD				0x04
#घोषणा OSD_OSDWIN0MD				0x08
#घोषणा OSD_OSDWIN1MD				0x0C
#घोषणा OSD_OSDATRMD				0x0C
#घोषणा OSD_RECTCUR				0x10
#घोषणा OSD_VIDWIN0OFST				0x18
#घोषणा OSD_VIDWIN1OFST				0x1C
#घोषणा OSD_OSDWIN0OFST				0x20
#घोषणा OSD_OSDWIN1OFST				0x24
#घोषणा OSD_VIDWINADH				0x28
#घोषणा OSD_VIDWIN0ADL				0x2C
#घोषणा OSD_VIDWIN0ADR				0x2C
#घोषणा OSD_VIDWIN1ADL				0x30
#घोषणा OSD_VIDWIN1ADR				0x30
#घोषणा OSD_OSDWINADH				0x34
#घोषणा OSD_OSDWIN0ADL				0x38
#घोषणा OSD_OSDWIN0ADR				0x38
#घोषणा OSD_OSDWIN1ADL				0x3C
#घोषणा OSD_OSDWIN1ADR				0x3C
#घोषणा OSD_BASEPX				0x40
#घोषणा OSD_BASEPY				0x44
#घोषणा OSD_VIDWIN0XP				0x48
#घोषणा OSD_VIDWIN0YP				0x4C
#घोषणा OSD_VIDWIN0XL				0x50
#घोषणा OSD_VIDWIN0YL				0x54
#घोषणा OSD_VIDWIN1XP				0x58
#घोषणा OSD_VIDWIN1YP				0x5C
#घोषणा OSD_VIDWIN1XL				0x60
#घोषणा OSD_VIDWIN1YL				0x64
#घोषणा OSD_OSDWIN0XP				0x68
#घोषणा OSD_OSDWIN0YP				0x6C
#घोषणा OSD_OSDWIN0XL				0x70
#घोषणा OSD_OSDWIN0YL				0x74
#घोषणा OSD_OSDWIN1XP				0x78
#घोषणा OSD_OSDWIN1YP				0x7C
#घोषणा OSD_OSDWIN1XL				0x80
#घोषणा OSD_OSDWIN1YL				0x84
#घोषणा OSD_CURXP				0x88
#घोषणा OSD_CURYP				0x8C
#घोषणा OSD_CURXL				0x90
#घोषणा OSD_CURYL				0x94
#घोषणा OSD_W0BMP01				0xA0
#घोषणा OSD_W0BMP23				0xA4
#घोषणा OSD_W0BMP45				0xA8
#घोषणा OSD_W0BMP67				0xAC
#घोषणा OSD_W0BMP89				0xB0
#घोषणा OSD_W0BMPAB				0xB4
#घोषणा OSD_W0BMPCD				0xB8
#घोषणा OSD_W0BMPEF				0xBC
#घोषणा OSD_W1BMP01				0xC0
#घोषणा OSD_W1BMP23				0xC4
#घोषणा OSD_W1BMP45				0xC8
#घोषणा OSD_W1BMP67				0xCC
#घोषणा OSD_W1BMP89				0xD0
#घोषणा OSD_W1BMPAB				0xD4
#घोषणा OSD_W1BMPCD				0xD8
#घोषणा OSD_W1BMPEF				0xDC
#घोषणा OSD_VBNDRY				0xE0
#घोषणा OSD_EXTMODE				0xE4
#घोषणा OSD_MISCCTL				0xE8
#घोषणा OSD_CLUTRAMYCB				0xEC
#घोषणा OSD_CLUTRAMCR				0xF0
#घोषणा OSD_TRANSPVAL				0xF4
#घोषणा OSD_TRANSPVALL				0xF4
#घोषणा OSD_TRANSPVALU				0xF8
#घोषणा OSD_TRANSPBMPIDX			0xFC
#घोषणा OSD_PPVWIN0ADR				0xFC

/* bit definitions */
#घोषणा VPBE_PCR_VENC_DIV			(1 << 1)
#घोषणा VPBE_PCR_CLK_OFF			(1 << 0)

#घोषणा VPSSBL_INTSTAT_HSSIINT			(1 << 14)
#घोषणा VPSSBL_INTSTAT_CFALDINT			(1 << 13)
#घोषणा VPSSBL_INTSTAT_IPIPE_INT5		(1 << 12)
#घोषणा VPSSBL_INTSTAT_IPIPE_INT4		(1 << 11)
#घोषणा VPSSBL_INTSTAT_IPIPE_INT3		(1 << 10)
#घोषणा VPSSBL_INTSTAT_IPIPE_INT2		(1 << 9)
#घोषणा VPSSBL_INTSTAT_IPIPE_INT1		(1 << 8)
#घोषणा VPSSBL_INTSTAT_IPIPE_INT0		(1 << 7)
#घोषणा VPSSBL_INTSTAT_IPIPEIFINT		(1 << 6)
#घोषणा VPSSBL_INTSTAT_OSDINT			(1 << 5)
#घोषणा VPSSBL_INTSTAT_VENCINT			(1 << 4)
#घोषणा VPSSBL_INTSTAT_H3AINT			(1 << 3)
#घोषणा VPSSBL_INTSTAT_CCDC_VDINT2		(1 << 2)
#घोषणा VPSSBL_INTSTAT_CCDC_VDINT1		(1 << 1)
#घोषणा VPSSBL_INTSTAT_CCDC_VDINT0		(1 << 0)

/* DM365 ISP5 bit definitions */
#घोषणा ISP5_INTSTAT_VENCINT			(1 << 21)
#घोषणा ISP5_INTSTAT_OSDINT			(1 << 20)

/* VMOD TVTYP options क्रम HDMD=0 */
#घोषणा SDTV_NTSC				0
#घोषणा SDTV_PAL				1
/* VMOD TVTYP options क्रम HDMD=1 */
#घोषणा HDTV_525P				0
#घोषणा HDTV_625P				1
#घोषणा HDTV_1080I				2
#घोषणा HDTV_720P				3

#घोषणा OSD_MODE_CS				(1 << 15)
#घोषणा OSD_MODE_OVRSZ				(1 << 14)
#घोषणा OSD_MODE_OHRSZ				(1 << 13)
#घोषणा OSD_MODE_EF				(1 << 12)
#घोषणा OSD_MODE_VVRSZ				(1 << 11)
#घोषणा OSD_MODE_VHRSZ				(1 << 10)
#घोषणा OSD_MODE_FSINV				(1 << 9)
#घोषणा OSD_MODE_BCLUT				(1 << 8)
#घोषणा OSD_MODE_CABG_SHIFT			0
#घोषणा OSD_MODE_CABG				(0xff << 0)

#घोषणा OSD_VIDWINMD_VFINV			(1 << 15)
#घोषणा OSD_VIDWINMD_V1EFC			(1 << 14)
#घोषणा OSD_VIDWINMD_VHZ1_SHIFT			12
#घोषणा OSD_VIDWINMD_VHZ1			(3 << 12)
#घोषणा OSD_VIDWINMD_VVZ1_SHIFT			10
#घोषणा OSD_VIDWINMD_VVZ1			(3 << 10)
#घोषणा OSD_VIDWINMD_VFF1			(1 << 9)
#घोषणा OSD_VIDWINMD_ACT1			(1 << 8)
#घोषणा OSD_VIDWINMD_V0EFC			(1 << 6)
#घोषणा OSD_VIDWINMD_VHZ0_SHIFT			4
#घोषणा OSD_VIDWINMD_VHZ0			(3 << 4)
#घोषणा OSD_VIDWINMD_VVZ0_SHIFT			2
#घोषणा OSD_VIDWINMD_VVZ0			(3 << 2)
#घोषणा OSD_VIDWINMD_VFF0			(1 << 1)
#घोषणा OSD_VIDWINMD_ACT0			(1 << 0)

#घोषणा OSD_OSDWIN0MD_ATN0E			(1 << 14)
#घोषणा OSD_OSDWIN0MD_RGB0E			(1 << 13)
#घोषणा OSD_OSDWIN0MD_BMP0MD_SHIFT		13
#घोषणा OSD_OSDWIN0MD_BMP0MD			(3 << 13)
#घोषणा OSD_OSDWIN0MD_CLUTS0			(1 << 12)
#घोषणा OSD_OSDWIN0MD_OHZ0_SHIFT		10
#घोषणा OSD_OSDWIN0MD_OHZ0			(3 << 10)
#घोषणा OSD_OSDWIN0MD_OVZ0_SHIFT		8
#घोषणा OSD_OSDWIN0MD_OVZ0			(3 << 8)
#घोषणा OSD_OSDWIN0MD_BMW0_SHIFT		6
#घोषणा OSD_OSDWIN0MD_BMW0			(3 << 6)
#घोषणा OSD_OSDWIN0MD_BLND0_SHIFT		3
#घोषणा OSD_OSDWIN0MD_BLND0			(7 << 3)
#घोषणा OSD_OSDWIN0MD_TE0			(1 << 2)
#घोषणा OSD_OSDWIN0MD_OFF0			(1 << 1)
#घोषणा OSD_OSDWIN0MD_OACT0			(1 << 0)

#घोषणा OSD_OSDWIN1MD_OASW			(1 << 15)
#घोषणा OSD_OSDWIN1MD_ATN1E			(1 << 14)
#घोषणा OSD_OSDWIN1MD_RGB1E			(1 << 13)
#घोषणा OSD_OSDWIN1MD_BMP1MD_SHIFT		13
#घोषणा OSD_OSDWIN1MD_BMP1MD			(3 << 13)
#घोषणा OSD_OSDWIN1MD_CLUTS1			(1 << 12)
#घोषणा OSD_OSDWIN1MD_OHZ1_SHIFT		10
#घोषणा OSD_OSDWIN1MD_OHZ1			(3 << 10)
#घोषणा OSD_OSDWIN1MD_OVZ1_SHIFT		8
#घोषणा OSD_OSDWIN1MD_OVZ1			(3 << 8)
#घोषणा OSD_OSDWIN1MD_BMW1_SHIFT		6
#घोषणा OSD_OSDWIN1MD_BMW1			(3 << 6)
#घोषणा OSD_OSDWIN1MD_BLND1_SHIFT		3
#घोषणा OSD_OSDWIN1MD_BLND1			(7 << 3)
#घोषणा OSD_OSDWIN1MD_TE1			(1 << 2)
#घोषणा OSD_OSDWIN1MD_OFF1			(1 << 1)
#घोषणा OSD_OSDWIN1MD_OACT1			(1 << 0)

#घोषणा OSD_OSDATRMD_OASW			(1 << 15)
#घोषणा OSD_OSDATRMD_OHZA_SHIFT			10
#घोषणा OSD_OSDATRMD_OHZA			(3 << 10)
#घोषणा OSD_OSDATRMD_OVZA_SHIFT			8
#घोषणा OSD_OSDATRMD_OVZA			(3 << 8)
#घोषणा OSD_OSDATRMD_BLNKINT_SHIFT		6
#घोषणा OSD_OSDATRMD_BLNKINT			(3 << 6)
#घोषणा OSD_OSDATRMD_OFFA			(1 << 1)
#घोषणा OSD_OSDATRMD_BLNK			(1 << 0)

#घोषणा OSD_RECTCUR_RCAD_SHIFT			8
#घोषणा OSD_RECTCUR_RCAD			(0xff << 8)
#घोषणा OSD_RECTCUR_CLUTSR			(1 << 7)
#घोषणा OSD_RECTCUR_RCHW_SHIFT			4
#घोषणा OSD_RECTCUR_RCHW			(7 << 4)
#घोषणा OSD_RECTCUR_RCVW_SHIFT			1
#घोषणा OSD_RECTCUR_RCVW			(7 << 1)
#घोषणा OSD_RECTCUR_RCACT			(1 << 0)

#घोषणा OSD_VIDWIN0OFST_V0LO			(0x1ff << 0)

#घोषणा OSD_VIDWIN1OFST_V1LO			(0x1ff << 0)

#घोषणा OSD_OSDWIN0OFST_O0LO			(0x1ff << 0)

#घोषणा OSD_OSDWIN1OFST_O1LO			(0x1ff << 0)

#घोषणा OSD_WINOFST_AH_SHIFT			9

#घोषणा OSD_VIDWIN0OFST_V0AH			(0xf << 9)
#घोषणा OSD_VIDWIN1OFST_V1AH			(0xf << 9)
#घोषणा OSD_OSDWIN0OFST_O0AH			(0xf << 9)
#घोषणा OSD_OSDWIN1OFST_O1AH			(0xf << 9)

#घोषणा OSD_VIDWINADH_V1AH_SHIFT		8
#घोषणा OSD_VIDWINADH_V1AH			(0x7f << 8)
#घोषणा OSD_VIDWINADH_V0AH_SHIFT		0
#घोषणा OSD_VIDWINADH_V0AH			(0x7f << 0)

#घोषणा OSD_VIDWIN0ADL_V0AL			(0xffff << 0)

#घोषणा OSD_VIDWIN1ADL_V1AL			(0xffff << 0)

#घोषणा OSD_OSDWINADH_O1AH_SHIFT		8
#घोषणा OSD_OSDWINADH_O1AH			(0x7f << 8)
#घोषणा OSD_OSDWINADH_O0AH_SHIFT		0
#घोषणा OSD_OSDWINADH_O0AH			(0x7f << 0)

#घोषणा OSD_OSDWIN0ADL_O0AL			(0xffff << 0)

#घोषणा OSD_OSDWIN1ADL_O1AL			(0xffff << 0)

#घोषणा OSD_BASEPX_BPX				(0x3ff << 0)

#घोषणा OSD_BASEPY_BPY				(0x1ff << 0)

#घोषणा OSD_VIDWIN0XP_V0X			(0x7ff << 0)

#घोषणा OSD_VIDWIN0YP_V0Y			(0x7ff << 0)

#घोषणा OSD_VIDWIN0XL_V0W			(0x7ff << 0)

#घोषणा OSD_VIDWIN0YL_V0H			(0x7ff << 0)

#घोषणा OSD_VIDWIN1XP_V1X			(0x7ff << 0)

#घोषणा OSD_VIDWIN1YP_V1Y			(0x7ff << 0)

#घोषणा OSD_VIDWIN1XL_V1W			(0x7ff << 0)

#घोषणा OSD_VIDWIN1YL_V1H			(0x7ff << 0)

#घोषणा OSD_OSDWIN0XP_W0X			(0x7ff << 0)

#घोषणा OSD_OSDWIN0YP_W0Y			(0x7ff << 0)

#घोषणा OSD_OSDWIN0XL_W0W			(0x7ff << 0)

#घोषणा OSD_OSDWIN0YL_W0H			(0x7ff << 0)

#घोषणा OSD_OSDWIN1XP_W1X			(0x7ff << 0)

#घोषणा OSD_OSDWIN1YP_W1Y			(0x7ff << 0)

#घोषणा OSD_OSDWIN1XL_W1W			(0x7ff << 0)

#घोषणा OSD_OSDWIN1YL_W1H			(0x7ff << 0)

#घोषणा OSD_CURXP_RCSX				(0x7ff << 0)

#घोषणा OSD_CURYP_RCSY				(0x7ff << 0)

#घोषणा OSD_CURXL_RCSW				(0x7ff << 0)

#घोषणा OSD_CURYL_RCSH				(0x7ff << 0)

#घोषणा OSD_EXTMODE_EXPMDSEL			(1 << 15)
#घोषणा OSD_EXTMODE_SCRNHEXP_SHIFT		13
#घोषणा OSD_EXTMODE_SCRNHEXP			(3 << 13)
#घोषणा OSD_EXTMODE_SCRNVEXP			(1 << 12)
#घोषणा OSD_EXTMODE_OSD1BLDCHR			(1 << 11)
#घोषणा OSD_EXTMODE_OSD0BLDCHR			(1 << 10)
#घोषणा OSD_EXTMODE_ATNOSD1EN			(1 << 9)
#घोषणा OSD_EXTMODE_ATNOSD0EN			(1 << 8)
#घोषणा OSD_EXTMODE_OSDHRSZ15			(1 << 7)
#घोषणा OSD_EXTMODE_VIDHRSZ15			(1 << 6)
#घोषणा OSD_EXTMODE_ZMFILV1HEN			(1 << 5)
#घोषणा OSD_EXTMODE_ZMFILV1VEN			(1 << 4)
#घोषणा OSD_EXTMODE_ZMFILV0HEN			(1 << 3)
#घोषणा OSD_EXTMODE_ZMFILV0VEN			(1 << 2)
#घोषणा OSD_EXTMODE_EXPFILHEN			(1 << 1)
#घोषणा OSD_EXTMODE_EXPFILVEN			(1 << 0)

#घोषणा OSD_MISCCTL_BLDSEL			(1 << 15)
#घोषणा OSD_MISCCTL_S420D			(1 << 14)
#घोषणा OSD_MISCCTL_BMAPT			(1 << 13)
#घोषणा OSD_MISCCTL_DM365M			(1 << 12)
#घोषणा OSD_MISCCTL_RGBEN			(1 << 7)
#घोषणा OSD_MISCCTL_RGBWIN			(1 << 6)
#घोषणा OSD_MISCCTL_DMANG			(1 << 6)
#घोषणा OSD_MISCCTL_TMON			(1 << 5)
#घोषणा OSD_MISCCTL_RSEL			(1 << 4)
#घोषणा OSD_MISCCTL_CPBSY			(1 << 3)
#घोषणा OSD_MISCCTL_PPSW			(1 << 2)
#घोषणा OSD_MISCCTL_PPRV			(1 << 1)

#घोषणा OSD_CLUTRAMYCB_Y_SHIFT			8
#घोषणा OSD_CLUTRAMYCB_Y			(0xff << 8)
#घोषणा OSD_CLUTRAMYCB_CB_SHIFT			0
#घोषणा OSD_CLUTRAMYCB_CB			(0xff << 0)

#घोषणा OSD_CLUTRAMCR_CR_SHIFT			8
#घोषणा OSD_CLUTRAMCR_CR			(0xff << 8)
#घोषणा OSD_CLUTRAMCR_CADDR_SHIFT		0
#घोषणा OSD_CLUTRAMCR_CADDR			(0xff << 0)

#घोषणा OSD_TRANSPVAL_RGBTRANS			(0xffff << 0)

#घोषणा OSD_TRANSPVALL_RGBL			(0xffff << 0)

#घोषणा OSD_TRANSPVALU_Y_SHIFT			8
#घोषणा OSD_TRANSPVALU_Y			(0xff << 8)
#घोषणा OSD_TRANSPVALU_RGBU_SHIFT		0
#घोषणा OSD_TRANSPVALU_RGBU			(0xff << 0)

#घोषणा OSD_TRANSPBMPIDX_BMP1_SHIFT		8
#घोषणा OSD_TRANSPBMPIDX_BMP1			(0xff << 8)
#घोषणा OSD_TRANSPBMPIDX_BMP0_SHIFT		0
#घोषणा OSD_TRANSPBMPIDX_BMP0			0xff

#पूर्ण_अगर				/* _DAVINCI_VPBE_H_ */
