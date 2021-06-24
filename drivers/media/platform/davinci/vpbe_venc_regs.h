<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2006-2010 Texas Instruments Inc
 */
#अगर_अघोषित _VPBE_VENC_REGS_H
#घोषणा _VPBE_VENC_REGS_H

/* VPBE Video Encoder / Digital LCD Subप्रणाली Registers (VENC) */
#घोषणा VENC_VMOD				0x00
#घोषणा VENC_VIDCTL				0x04
#घोषणा VENC_VDPRO				0x08
#घोषणा VENC_SYNCCTL				0x0C
#घोषणा VENC_HSPLS				0x10
#घोषणा VENC_VSPLS				0x14
#घोषणा VENC_HINT				0x18
#घोषणा VENC_HSTART				0x1C
#घोषणा VENC_HVALID				0x20
#घोषणा VENC_VINT				0x24
#घोषणा VENC_VSTART				0x28
#घोषणा VENC_VVALID				0x2C
#घोषणा VENC_HSDLY				0x30
#घोषणा VENC_VSDLY				0x34
#घोषणा VENC_YCCCTL				0x38
#घोषणा VENC_RGBCTL				0x3C
#घोषणा VENC_RGBCLP				0x40
#घोषणा VENC_LINECTL				0x44
#घोषणा VENC_CULLLINE				0x48
#घोषणा VENC_LCDOUT				0x4C
#घोषणा VENC_BRTS				0x50
#घोषणा VENC_BRTW				0x54
#घोषणा VENC_ACCTL				0x58
#घोषणा VENC_PWMP				0x5C
#घोषणा VENC_PWMW				0x60
#घोषणा VENC_DCLKCTL				0x64
#घोषणा VENC_DCLKPTN0				0x68
#घोषणा VENC_DCLKPTN1				0x6C
#घोषणा VENC_DCLKPTN2				0x70
#घोषणा VENC_DCLKPTN3				0x74
#घोषणा VENC_DCLKPTN0A				0x78
#घोषणा VENC_DCLKPTN1A				0x7C
#घोषणा VENC_DCLKPTN2A				0x80
#घोषणा VENC_DCLKPTN3A				0x84
#घोषणा VENC_DCLKHS				0x88
#घोषणा VENC_DCLKHSA				0x8C
#घोषणा VENC_DCLKHR				0x90
#घोषणा VENC_DCLKVS				0x94
#घोषणा VENC_DCLKVR				0x98
#घोषणा VENC_CAPCTL				0x9C
#घोषणा VENC_CAPDO				0xA0
#घोषणा VENC_CAPDE				0xA4
#घोषणा VENC_ATR0				0xA8
#घोषणा VENC_ATR1				0xAC
#घोषणा VENC_ATR2				0xB0
#घोषणा VENC_VSTAT				0xB8
#घोषणा VENC_RAMADR				0xBC
#घोषणा VENC_RAMPORT				0xC0
#घोषणा VENC_DACTST				0xC4
#घोषणा VENC_YCOLVL				0xC8
#घोषणा VENC_SCPROG				0xCC
#घोषणा VENC_CVBS				0xDC
#घोषणा VENC_CMPNT				0xE0
#घोषणा VENC_ETMG0				0xE4
#घोषणा VENC_ETMG1				0xE8
#घोषणा VENC_ETMG2				0xEC
#घोषणा VENC_ETMG3				0xF0
#घोषणा VENC_DACSEL				0xF4
#घोषणा VENC_ARGBX0				0x100
#घोषणा VENC_ARGBX1				0x104
#घोषणा VENC_ARGBX2				0x108
#घोषणा VENC_ARGBX3				0x10C
#घोषणा VENC_ARGBX4				0x110
#घोषणा VENC_DRGBX0				0x114
#घोषणा VENC_DRGBX1				0x118
#घोषणा VENC_DRGBX2				0x11C
#घोषणा VENC_DRGBX3				0x120
#घोषणा VENC_DRGBX4				0x124
#घोषणा VENC_VSTARTA				0x128
#घोषणा VENC_OSDCLK0				0x12C
#घोषणा VENC_OSDCLK1				0x130
#घोषणा VENC_HVLDCL0				0x134
#घोषणा VENC_HVLDCL1				0x138
#घोषणा VENC_OSDHADV				0x13C
#घोषणा VENC_CLKCTL				0x140
#घोषणा VENC_GAMCTL				0x144
#घोषणा VENC_XHINTVL				0x174

/* bit definitions */
#घोषणा VPBE_PCR_VENC_DIV			(1 << 1)
#घोषणा VPBE_PCR_CLK_OFF			(1 << 0)

#घोषणा VENC_VMOD_VDMD_SHIFT			12
#घोषणा VENC_VMOD_VDMD_YCBCR16			0
#घोषणा VENC_VMOD_VDMD_YCBCR8			1
#घोषणा VENC_VMOD_VDMD_RGB666			2
#घोषणा VENC_VMOD_VDMD_RGB8			3
#घोषणा VENC_VMOD_VDMD_EPSON			4
#घोषणा VENC_VMOD_VDMD_CASIO			5
#घोषणा VENC_VMOD_VDMD_UDISPQVGA		6
#घोषणा VENC_VMOD_VDMD_STNLCD			7
#घोषणा VENC_VMOD_VIE_SHIFT			1
#घोषणा VENC_VMOD_VDMD				(7 << 12)
#घोषणा VENC_VMOD_ITLCL				(1 << 11)
#घोषणा VENC_VMOD_ITLC				(1 << 10)
#घोषणा VENC_VMOD_NSIT				(1 << 9)
#घोषणा VENC_VMOD_HDMD				(1 << 8)
#घोषणा VENC_VMOD_TVTYP_SHIFT			6
#घोषणा VENC_VMOD_TVTYP				(3 << 6)
#घोषणा VENC_VMOD_SLAVE				(1 << 5)
#घोषणा VENC_VMOD_VMD				(1 << 4)
#घोषणा VENC_VMOD_BLNK				(1 << 3)
#घोषणा VENC_VMOD_VIE				(1 << 1)
#घोषणा VENC_VMOD_VENC				(1 << 0)

/* VMOD TVTYP options क्रम HDMD=0 */
#घोषणा SDTV_NTSC				0
#घोषणा SDTV_PAL				1
/* VMOD TVTYP options क्रम HDMD=1 */
#घोषणा HDTV_525P				0
#घोषणा HDTV_625P				1
#घोषणा HDTV_1080I				2
#घोषणा HDTV_720P				3

#घोषणा VENC_VIDCTL_VCLKP			(1 << 14)
#घोषणा VENC_VIDCTL_VCLKE_SHIFT			13
#घोषणा VENC_VIDCTL_VCLKE			(1 << 13)
#घोषणा VENC_VIDCTL_VCLKZ_SHIFT			12
#घोषणा VENC_VIDCTL_VCLKZ			(1 << 12)
#घोषणा VENC_VIDCTL_SYसूची_SHIFT			8
#घोषणा VENC_VIDCTL_SYसूची			(1 << 8)
#घोषणा VENC_VIDCTL_DOMD_SHIFT			4
#घोषणा VENC_VIDCTL_DOMD			(3 << 4)
#घोषणा VENC_VIDCTL_YCसूची_SHIFT			0
#घोषणा VENC_VIDCTL_YCसूची			(1 << 0)

#घोषणा VENC_VDPRO_ATYCC_SHIFT			5
#घोषणा VENC_VDPRO_ATYCC			(1 << 5)
#घोषणा VENC_VDPRO_ATCOM_SHIFT			4
#घोषणा VENC_VDPRO_ATCOM			(1 << 4)
#घोषणा VENC_VDPRO_DAFRQ			(1 << 3)
#घोषणा VENC_VDPRO_DAUPS			(1 << 2)
#घोषणा VENC_VDPRO_CUPS				(1 << 1)
#घोषणा VENC_VDPRO_YUPS				(1 << 0)

#घोषणा VENC_SYNCCTL_VPL_SHIFT			3
#घोषणा VENC_SYNCCTL_VPL			(1 << 3)
#घोषणा VENC_SYNCCTL_HPL_SHIFT			2
#घोषणा VENC_SYNCCTL_HPL			(1 << 2)
#घोषणा VENC_SYNCCTL_SYEV_SHIFT			1
#घोषणा VENC_SYNCCTL_SYEV			(1 << 1)
#घोषणा VENC_SYNCCTL_SYEH_SHIFT			0
#घोषणा VENC_SYNCCTL_SYEH			(1 << 0)
#घोषणा VENC_SYNCCTL_OVD_SHIFT			14
#घोषणा VENC_SYNCCTL_OVD			(1 << 14)

#घोषणा VENC_DCLKCTL_DCKEC_SHIFT		11
#घोषणा VENC_DCLKCTL_DCKEC			(1 << 11)
#घोषणा VENC_DCLKCTL_DCKPW_SHIFT		0
#घोषणा VENC_DCLKCTL_DCKPW			(0x3f << 0)

#घोषणा VENC_VSTAT_FIDST			(1 << 4)

#घोषणा VENC_CMPNT_MRGB_SHIFT			14
#घोषणा VENC_CMPNT_MRGB				(1 << 14)

#पूर्ण_अगर				/* _VPBE_VENC_REGS_H */
