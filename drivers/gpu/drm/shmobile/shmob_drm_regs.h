<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * shmob_drm_regs.h  --  SH Mobile DRM रेजिस्टरs
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __SHMOB_DRM_REGS_H__
#घोषणा __SHMOB_DRM_REGS_H__

#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>

#समावेश "shmob_drm_drv.h"

/* Register definitions */
#घोषणा LDDCKPAT1R		0x400
#घोषणा LDDCKPAT2R		0x404
#घोषणा LDDCKR			0x410
#घोषणा LDDCKR_ICKSEL_BUS	(0 << 16)
#घोषणा LDDCKR_ICKSEL_MIPI	(1 << 16)
#घोषणा LDDCKR_ICKSEL_HDMI	(2 << 16)
#घोषणा LDDCKR_ICKSEL_EXT	(3 << 16)
#घोषणा LDDCKR_ICKSEL_MASK	(7 << 16)
#घोषणा LDDCKR_MOSEL		(1 << 6)
#घोषणा LDDCKSTPR		0x414
#घोषणा LDDCKSTPR_DCKSTS	(1 << 16)
#घोषणा LDDCKSTPR_DCKSTP	(1 << 0)
#घोषणा LDMT1R			0x418
#घोषणा LDMT1R_VPOL		(1 << 28)
#घोषणा LDMT1R_HPOL		(1 << 27)
#घोषणा LDMT1R_DWPOL		(1 << 26)
#घोषणा LDMT1R_DIPOL		(1 << 25)
#घोषणा LDMT1R_DAPOL		(1 << 24)
#घोषणा LDMT1R_HSCNT		(1 << 17)
#घोषणा LDMT1R_DWCNT		(1 << 16)
#घोषणा LDMT1R_IFM		(1 << 12)
#घोषणा LDMT1R_MIFTYP_RGB8	(0x0 << 0)
#घोषणा LDMT1R_MIFTYP_RGB9	(0x4 << 0)
#घोषणा LDMT1R_MIFTYP_RGB12A	(0x5 << 0)
#घोषणा LDMT1R_MIFTYP_RGB12B	(0x6 << 0)
#घोषणा LDMT1R_MIFTYP_RGB16	(0x7 << 0)
#घोषणा LDMT1R_MIFTYP_RGB18	(0xa << 0)
#घोषणा LDMT1R_MIFTYP_RGB24	(0xb << 0)
#घोषणा LDMT1R_MIFTYP_YCBCR	(0xf << 0)
#घोषणा LDMT1R_MIFTYP_SYS8A	(0x0 << 0)
#घोषणा LDMT1R_MIFTYP_SYS8B	(0x1 << 0)
#घोषणा LDMT1R_MIFTYP_SYS8C	(0x2 << 0)
#घोषणा LDMT1R_MIFTYP_SYS8D	(0x3 << 0)
#घोषणा LDMT1R_MIFTYP_SYS9	(0x4 << 0)
#घोषणा LDMT1R_MIFTYP_SYS12	(0x5 << 0)
#घोषणा LDMT1R_MIFTYP_SYS16A	(0x7 << 0)
#घोषणा LDMT1R_MIFTYP_SYS16B	(0x8 << 0)
#घोषणा LDMT1R_MIFTYP_SYS16C	(0x9 << 0)
#घोषणा LDMT1R_MIFTYP_SYS18	(0xa << 0)
#घोषणा LDMT1R_MIFTYP_SYS24	(0xb << 0)
#घोषणा LDMT1R_MIFTYP_MASK	(0xf << 0)
#घोषणा LDMT2R			0x41c
#घोषणा LDMT2R_CSUP_MASK	(7 << 26)
#घोषणा LDMT2R_CSUP_SHIFT	26
#घोषणा LDMT2R_RSV		(1 << 25)
#घोषणा LDMT2R_VSEL		(1 << 24)
#घोषणा LDMT2R_WCSC_MASK	(0xff << 16)
#घोषणा LDMT2R_WCSC_SHIFT	16
#घोषणा LDMT2R_WCEC_MASK	(0xff << 8)
#घोषणा LDMT2R_WCEC_SHIFT	8
#घोषणा LDMT2R_WCLW_MASK	(0xff << 0)
#घोषणा LDMT2R_WCLW_SHIFT	0
#घोषणा LDMT3R			0x420
#घोषणा LDMT3R_RDLC_MASK	(0x3f << 24)
#घोषणा LDMT3R_RDLC_SHIFT	24
#घोषणा LDMT3R_RCSC_MASK	(0xff << 16)
#घोषणा LDMT3R_RCSC_SHIFT	16
#घोषणा LDMT3R_RCEC_MASK	(0xff << 8)
#घोषणा LDMT3R_RCEC_SHIFT	8
#घोषणा LDMT3R_RCLW_MASK	(0xff << 0)
#घोषणा LDMT3R_RCLW_SHIFT	0
#घोषणा LDDFR			0x424
#घोषणा LDDFR_CF1		(1 << 18)
#घोषणा LDDFR_CF0		(1 << 17)
#घोषणा LDDFR_CC		(1 << 16)
#घोषणा LDDFR_YF_420		(0 << 8)
#घोषणा LDDFR_YF_422		(1 << 8)
#घोषणा LDDFR_YF_444		(2 << 8)
#घोषणा LDDFR_YF_MASK		(3 << 8)
#घोषणा LDDFR_PKF_ARGB32	(0x00 << 0)
#घोषणा LDDFR_PKF_RGB16		(0x03 << 0)
#घोषणा LDDFR_PKF_RGB24		(0x0b << 0)
#घोषणा LDDFR_PKF_MASK		(0x1f << 0)
#घोषणा LDSM1R			0x428
#घोषणा LDSM1R_OS		(1 << 0)
#घोषणा LDSM2R			0x42c
#घोषणा LDSM2R_OSTRG		(1 << 0)
#घोषणा LDSA1R			0x430
#घोषणा LDSA2R			0x434
#घोषणा LDMLSR			0x438
#घोषणा LDWBFR			0x43c
#घोषणा LDWBCNTR		0x440
#घोषणा LDWBAR			0x444
#घोषणा LDHCNR			0x448
#घोषणा LDHSYNR			0x44c
#घोषणा LDVLNR			0x450
#घोषणा LDVSYNR			0x454
#घोषणा LDHPDR			0x458
#घोषणा LDVPDR			0x45c
#घोषणा LDPMR			0x460
#घोषणा LDPMR_LPS		(3 << 0)
#घोषणा LDINTR			0x468
#घोषणा LDINTR_FE		(1 << 10)
#घोषणा LDINTR_VSE		(1 << 9)
#घोषणा LDINTR_VEE		(1 << 8)
#घोषणा LDINTR_FS		(1 << 2)
#घोषणा LDINTR_VSS		(1 << 1)
#घोषणा LDINTR_VES		(1 << 0)
#घोषणा LDINTR_STATUS_MASK	(0xff << 0)
#घोषणा LDSR			0x46c
#घोषणा LDSR_MSS		(1 << 10)
#घोषणा LDSR_MRS		(1 << 8)
#घोषणा LDSR_AS			(1 << 1)
#घोषणा LDCNT1R			0x470
#घोषणा LDCNT1R_DE		(1 << 0)
#घोषणा LDCNT2R			0x474
#घोषणा LDCNT2R_BR		(1 << 8)
#घोषणा LDCNT2R_MD		(1 << 3)
#घोषणा LDCNT2R_SE		(1 << 2)
#घोषणा LDCNT2R_ME		(1 << 1)
#घोषणा LDCNT2R_DO		(1 << 0)
#घोषणा LDRCNTR			0x478
#घोषणा LDRCNTR_SRS		(1 << 17)
#घोषणा LDRCNTR_SRC		(1 << 16)
#घोषणा LDRCNTR_MRS		(1 << 1)
#घोषणा LDRCNTR_MRC		(1 << 0)
#घोषणा LDDDSR			0x47c
#घोषणा LDDDSR_LS		(1 << 2)
#घोषणा LDDDSR_WS		(1 << 1)
#घोषणा LDDDSR_BS		(1 << 0)
#घोषणा LDHAJR			0x4a0

#घोषणा LDDWD0R			0x800
#घोषणा LDDWDxR_WDACT		(1 << 28)
#घोषणा LDDWDxR_RSW		(1 << 24)
#घोषणा LDDRDR			0x840
#घोषणा LDDRDR_RSR		(1 << 24)
#घोषणा LDDRDR_DRD_MASK		(0x3ffff << 0)
#घोषणा LDDWAR			0x900
#घोषणा LDDWAR_WA		(1 << 0)
#घोषणा LDDRAR			0x904
#घोषणा LDDRAR_RA		(1 << 0)

#घोषणा LDBCR			0xb00
#घोषणा LDBCR_UPC(n)		(1 << ((n) + 16))
#घोषणा LDBCR_UPF(n)		(1 << ((n) + 8))
#घोषणा LDBCR_UPD(n)		(1 << ((n) + 0))
#घोषणा LDBnBSIFR(n)		(0xb20 + (n) * 0x20 + 0x00)
#घोषणा LDBBSIFR_EN		(1 << 31)
#घोषणा LDBBSIFR_VS		(1 << 29)
#घोषणा LDBBSIFR_BRSEL		(1 << 28)
#घोषणा LDBBSIFR_MX		(1 << 27)
#घोषणा LDBBSIFR_MY		(1 << 26)
#घोषणा LDBBSIFR_CV3		(3 << 24)
#घोषणा LDBBSIFR_CV2		(2 << 24)
#घोषणा LDBBSIFR_CV1		(1 << 24)
#घोषणा LDBBSIFR_CV0		(0 << 24)
#घोषणा LDBBSIFR_CV_MASK	(3 << 24)
#घोषणा LDBBSIFR_LAY_MASK	(0xff << 16)
#घोषणा LDBBSIFR_LAY_SHIFT	16
#घोषणा LDBBSIFR_ROP3_MASK	(0xff << 16)
#घोषणा LDBBSIFR_ROP3_SHIFT	16
#घोषणा LDBBSIFR_AL_PL8		(3 << 14)
#घोषणा LDBBSIFR_AL_PL1		(2 << 14)
#घोषणा LDBBSIFR_AL_PK		(1 << 14)
#घोषणा LDBBSIFR_AL_1		(0 << 14)
#घोषणा LDBBSIFR_AL_MASK	(3 << 14)
#घोषणा LDBBSIFR_SWPL		(1 << 10)
#घोषणा LDBBSIFR_SWPW		(1 << 9)
#घोषणा LDBBSIFR_SWPB		(1 << 8)
#घोषणा LDBBSIFR_RY		(1 << 7)
#घोषणा LDBBSIFR_CHRR_420	(2 << 0)
#घोषणा LDBBSIFR_CHRR_422	(1 << 0)
#घोषणा LDBBSIFR_CHRR_444	(0 << 0)
#घोषणा LDBBSIFR_RPKF_ARGB32	(0x00 << 0)
#घोषणा LDBBSIFR_RPKF_RGB16	(0x03 << 0)
#घोषणा LDBBSIFR_RPKF_RGB24	(0x0b << 0)
#घोषणा LDBBSIFR_RPKF_MASK	(0x1f << 0)
#घोषणा LDBnBSSZR(n)		(0xb20 + (n) * 0x20 + 0x04)
#घोषणा LDBBSSZR_BVSS_MASK	(0xfff << 16)
#घोषणा LDBBSSZR_BVSS_SHIFT	16
#घोषणा LDBBSSZR_BHSS_MASK	(0xfff << 0)
#घोषणा LDBBSSZR_BHSS_SHIFT	0
#घोषणा LDBnBLOCR(n)		(0xb20 + (n) * 0x20 + 0x08)
#घोषणा LDBBLOCR_CVLC_MASK	(0xfff << 16)
#घोषणा LDBBLOCR_CVLC_SHIFT	16
#घोषणा LDBBLOCR_CHLC_MASK	(0xfff << 0)
#घोषणा LDBBLOCR_CHLC_SHIFT	0
#घोषणा LDBnBSMWR(n)		(0xb20 + (n) * 0x20 + 0x0c)
#घोषणा LDBBSMWR_BSMWA_MASK	(0xffff << 16)
#घोषणा LDBBSMWR_BSMWA_SHIFT	16
#घोषणा LDBBSMWR_BSMW_MASK	(0xffff << 0)
#घोषणा LDBBSMWR_BSMW_SHIFT	0
#घोषणा LDBnBSAYR(n)		(0xb20 + (n) * 0x20 + 0x10)
#घोषणा LDBBSAYR_FG1A_MASK	(0xff << 24)
#घोषणा LDBBSAYR_FG1A_SHIFT	24
#घोषणा LDBBSAYR_FG1R_MASK	(0xff << 16)
#घोषणा LDBBSAYR_FG1R_SHIFT	16
#घोषणा LDBBSAYR_FG1G_MASK	(0xff << 8)
#घोषणा LDBBSAYR_FG1G_SHIFT	8
#घोषणा LDBBSAYR_FG1B_MASK	(0xff << 0)
#घोषणा LDBBSAYR_FG1B_SHIFT	0
#घोषणा LDBnBSACR(n)		(0xb20 + (n) * 0x20 + 0x14)
#घोषणा LDBBSACR_FG2A_MASK	(0xff << 24)
#घोषणा LDBBSACR_FG2A_SHIFT	24
#घोषणा LDBBSACR_FG2R_MASK	(0xff << 16)
#घोषणा LDBBSACR_FG2R_SHIFT	16
#घोषणा LDBBSACR_FG2G_MASK	(0xff << 8)
#घोषणा LDBBSACR_FG2G_SHIFT	8
#घोषणा LDBBSACR_FG2B_MASK	(0xff << 0)
#घोषणा LDBBSACR_FG2B_SHIFT	0
#घोषणा LDBnBSAAR(n)		(0xb20 + (n) * 0x20 + 0x18)
#घोषणा LDBBSAAR_AP_MASK	(0xff << 24)
#घोषणा LDBBSAAR_AP_SHIFT	24
#घोषणा LDBBSAAR_R_MASK		(0xff << 16)
#घोषणा LDBBSAAR_R_SHIFT	16
#घोषणा LDBBSAAR_GY_MASK	(0xff << 8)
#घोषणा LDBBSAAR_GY_SHIFT	8
#घोषणा LDBBSAAR_B_MASK		(0xff << 0)
#घोषणा LDBBSAAR_B_SHIFT	0
#घोषणा LDBnBPPCR(n)		(0xb20 + (n) * 0x20 + 0x1c)
#घोषणा LDBBPPCR_AP_MASK	(0xff << 24)
#घोषणा LDBBPPCR_AP_SHIFT	24
#घोषणा LDBBPPCR_R_MASK		(0xff << 16)
#घोषणा LDBBPPCR_R_SHIFT	16
#घोषणा LDBBPPCR_GY_MASK	(0xff << 8)
#घोषणा LDBBPPCR_GY_SHIFT	8
#घोषणा LDBBPPCR_B_MASK		(0xff << 0)
#घोषणा LDBBPPCR_B_SHIFT	0
#घोषणा LDBnBBGCL(n)		(0xb10 + (n) * 0x04)
#घोषणा LDBBBGCL_BGA_MASK	(0xff << 24)
#घोषणा LDBBBGCL_BGA_SHIFT	24
#घोषणा LDBBBGCL_BGR_MASK	(0xff << 16)
#घोषणा LDBBBGCL_BGR_SHIFT	16
#घोषणा LDBBBGCL_BGG_MASK	(0xff << 8)
#घोषणा LDBBBGCL_BGG_SHIFT	8
#घोषणा LDBBBGCL_BGB_MASK	(0xff << 0)
#घोषणा LDBBBGCL_BGB_SHIFT	0

#घोषणा LCDC_SIDE_B_OFFSET	0x1000
#घोषणा LCDC_MIRROR_OFFSET	0x2000

अटल अंतरभूत bool lcdc_is_banked(u32 reg)
अणु
	चयन (reg) अणु
	हाल LDMT1R:
	हाल LDMT2R:
	हाल LDMT3R:
	हाल LDDFR:
	हाल LDSM1R:
	हाल LDSA1R:
	हाल LDSA2R:
	हाल LDMLSR:
	हाल LDWBFR:
	हाल LDWBCNTR:
	हाल LDWBAR:
	हाल LDHCNR:
	हाल LDHSYNR:
	हाल LDVLNR:
	हाल LDVSYNR:
	हाल LDHPDR:
	हाल LDVPDR:
	हाल LDHAJR:
		वापस true;
	शेष:
		वापस reg >= LDBnBBGCL(0) && reg <= LDBnBPPCR(3);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम lcdc_ग_लिखो_mirror(काष्ठा shmob_drm_device *sdev, u32 reg,
				     u32 data)
अणु
	ioग_लिखो32(data, sdev->mmio + reg + LCDC_MIRROR_OFFSET);
पूर्ण

अटल अंतरभूत व्योम lcdc_ग_लिखो(काष्ठा shmob_drm_device *sdev, u32 reg, u32 data)
अणु
	ioग_लिखो32(data, sdev->mmio + reg);
	अगर (lcdc_is_banked(reg))
		ioग_लिखो32(data, sdev->mmio + reg + LCDC_SIDE_B_OFFSET);
पूर्ण

अटल अंतरभूत u32 lcdc_पढ़ो(काष्ठा shmob_drm_device *sdev, u32 reg)
अणु
	वापस ioपढ़ो32(sdev->mmio + reg);
पूर्ण

अटल अंतरभूत पूर्णांक lcdc_रुको_bit(काष्ठा shmob_drm_device *sdev, u32 reg,
				u32 mask, u32 until)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(5);

	जबतक ((lcdc_पढ़ो(sdev, reg) & mask) != until) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __SHMOB_DRM_REGS_H__ */
