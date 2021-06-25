<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_MOBILE_LCDC_H__
#घोषणा __ASM_SH_MOBILE_LCDC_H__

#समावेश <linux/fb.h>

/* Register definitions */
#घोषणा _LDDCKR			0x410
#घोषणा LDDCKR_ICKSEL_BUS	(0 << 16)
#घोषणा LDDCKR_ICKSEL_MIPI	(1 << 16)
#घोषणा LDDCKR_ICKSEL_HDMI	(2 << 16)
#घोषणा LDDCKR_ICKSEL_EXT	(3 << 16)
#घोषणा LDDCKR_ICKSEL_MASK	(7 << 16)
#घोषणा LDDCKR_MOSEL		(1 << 6)
#घोषणा _LDDCKSTPR		0x414
#घोषणा _LDINTR			0x468
#घोषणा LDINTR_FE		(1 << 10)
#घोषणा LDINTR_VSE		(1 << 9)
#घोषणा LDINTR_VEE		(1 << 8)
#घोषणा LDINTR_FS		(1 << 2)
#घोषणा LDINTR_VSS		(1 << 1)
#घोषणा LDINTR_VES		(1 << 0)
#घोषणा LDINTR_STATUS_MASK	(0xff << 0)
#घोषणा _LDSR			0x46c
#घोषणा LDSR_MSS		(1 << 10)
#घोषणा LDSR_MRS		(1 << 8)
#घोषणा LDSR_AS			(1 << 1)
#घोषणा _LDCNT1R		0x470
#घोषणा LDCNT1R_DE		(1 << 0)
#घोषणा _LDCNT2R		0x474
#घोषणा LDCNT2R_BR		(1 << 8)
#घोषणा LDCNT2R_MD		(1 << 3)
#घोषणा LDCNT2R_SE		(1 << 2)
#घोषणा LDCNT2R_ME		(1 << 1)
#घोषणा LDCNT2R_DO		(1 << 0)
#घोषणा _LDRCNTR		0x478
#घोषणा LDRCNTR_SRS		(1 << 17)
#घोषणा LDRCNTR_SRC		(1 << 16)
#घोषणा LDRCNTR_MRS		(1 << 1)
#घोषणा LDRCNTR_MRC		(1 << 0)
#घोषणा _LDDDSR			0x47c
#घोषणा LDDDSR_LS		(1 << 2)
#घोषणा LDDDSR_WS		(1 << 1)
#घोषणा LDDDSR_BS		(1 << 0)

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

#घोषणा LDSM1R_OS		(1 << 0)

#घोषणा LDSM2R_OSTRG		(1 << 0)

#घोषणा LDPMR_LPS		(3 << 0)

#घोषणा _LDDWD0R		0x800
#घोषणा LDDWDxR_WDACT		(1 << 28)
#घोषणा LDDWDxR_RSW		(1 << 24)
#घोषणा _LDDRDR			0x840
#घोषणा LDDRDR_RSR		(1 << 24)
#घोषणा LDDRDR_DRD_MASK		(0x3ffff << 0)
#घोषणा _LDDWAR			0x900
#घोषणा LDDWAR_WA		(1 << 0)
#घोषणा _LDDRAR			0x904
#घोषणा LDDRAR_RA		(1 << 0)

क्रमागत अणु
	RGB8	= LDMT1R_MIFTYP_RGB8,	/* 24bpp, 8:8:8 */
	RGB9	= LDMT1R_MIFTYP_RGB9,	/* 18bpp, 9:9 */
	RGB12A	= LDMT1R_MIFTYP_RGB12A,	/* 24bpp, 12:12 */
	RGB12B	= LDMT1R_MIFTYP_RGB12B,	/* 12bpp */
	RGB16	= LDMT1R_MIFTYP_RGB16,	/* 16bpp */
	RGB18	= LDMT1R_MIFTYP_RGB18,	/* 18bpp */
	RGB24	= LDMT1R_MIFTYP_RGB24,	/* 24bpp */
	YUV422	= LDMT1R_MIFTYP_YCBCR,	/* 16bpp */
	SYS8A	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS8A,	/* 24bpp, 8:8:8 */
	SYS8B	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS8B,	/* 18bpp, 8:8:2 */
	SYS8C	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS8C,	/* 18bpp, 2:8:8 */
	SYS8D	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS8D,	/* 16bpp, 8:8 */
	SYS9	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS9,	/* 18bpp, 9:9 */
	SYS12	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS12,	/* 24bpp, 12:12 */
	SYS16A	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS16A,	/* 16bpp */
	SYS16B	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS16B,	/* 18bpp, 16:2 */
	SYS16C	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS16C,	/* 18bpp, 2:16 */
	SYS18	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS18,	/* 18bpp */
	SYS24	= LDMT1R_IFM | LDMT1R_MIFTYP_SYS24,	/* 24bpp */
पूर्ण;

क्रमागत अणु LCDC_CHAN_DISABLED = 0,
       LCDC_CHAN_MAINLCD,
       LCDC_CHAN_SUBLCD पूर्ण;

क्रमागत अणु LCDC_CLK_BUS, LCDC_CLK_PERIPHERAL, LCDC_CLK_EXTERNAL पूर्ण;

#घोषणा LCDC_FLAGS_DWPOL (1 << 0) /* Rising edge करोt घड़ी data latch */
#घोषणा LCDC_FLAGS_DIPOL (1 << 1) /* Active low display enable polarity */
#घोषणा LCDC_FLAGS_DAPOL (1 << 2) /* Active low display data polarity */
#घोषणा LCDC_FLAGS_HSCNT (1 << 3) /* Disable HSYNC during VBLANK */
#घोषणा LCDC_FLAGS_DWCNT (1 << 4) /* Disable करोtघड़ी during blanking */

काष्ठा sh_mobile_lcdc_sys_bus_cfg अणु
	अचिन्हित दीर्घ ldmt2r;
	अचिन्हित दीर्घ ldmt3r;
	अचिन्हित दीर्घ deferred_io_msec;
पूर्ण;

काष्ठा sh_mobile_lcdc_sys_bus_ops अणु
	व्योम (*ग_लिखो_index)(व्योम *handle, अचिन्हित दीर्घ data);
	व्योम (*ग_लिखो_data)(व्योम *handle, अचिन्हित दीर्घ data);
	अचिन्हित दीर्घ (*पढ़ो_data)(व्योम *handle);
पूर्ण;

काष्ठा sh_mobile_lcdc_panel_cfg अणु
	अचिन्हित दीर्घ width;		/* Panel width in mm */
	अचिन्हित दीर्घ height;		/* Panel height in mm */
	पूर्णांक (*setup_sys)(व्योम *sys_ops_handle,
			 काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops);
	व्योम (*start_transfer)(व्योम *sys_ops_handle,
			       काष्ठा sh_mobile_lcdc_sys_bus_ops *sys_ops);
	व्योम (*display_on)(व्योम);
	व्योम (*display_off)(व्योम);
पूर्ण;

/* backlight info */
काष्ठा sh_mobile_lcdc_bl_info अणु
	स्थिर अक्षर *name;
	पूर्णांक max_brightness;
	पूर्णांक (*set_brightness)(पूर्णांक brightness);
पूर्ण;

काष्ठा sh_mobile_lcdc_overlay_cfg अणु
	पूर्णांक fourcc;
	अचिन्हित पूर्णांक max_xres;
	अचिन्हित पूर्णांक max_yres;
पूर्ण;

काष्ठा sh_mobile_lcdc_chan_cfg अणु
	पूर्णांक chan;
	पूर्णांक fourcc;
	पूर्णांक colorspace;
	पूर्णांक पूर्णांकerface_type; /* selects RGBn or SYSn I/F, see above */
	पूर्णांक घड़ी_भागider;
	अचिन्हित दीर्घ flags; /* LCDC_FLAGS_... */
	स्थिर काष्ठा fb_videomode *lcd_modes;
	पूर्णांक num_modes;
	काष्ठा sh_mobile_lcdc_panel_cfg panel_cfg;
	काष्ठा sh_mobile_lcdc_bl_info bl_info;
	काष्ठा sh_mobile_lcdc_sys_bus_cfg sys_bus_cfg; /* only क्रम SYSn I/F */

	काष्ठा platक्रमm_device *tx_dev;	/* HDMI/DSI transmitter device */
पूर्ण;

काष्ठा sh_mobile_lcdc_info अणु
	पूर्णांक घड़ी_source;
	काष्ठा sh_mobile_lcdc_chan_cfg ch[2];
	काष्ठा sh_mobile_lcdc_overlay_cfg overlays[4];
पूर्ण;

#पूर्ण_अगर /* __ASM_SH_MOBILE_LCDC_H__ */
