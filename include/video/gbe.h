<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/video/gbe.h -- SGI GBE (Graphics Back End)
 *
 * Copyright (C) 1999 Silicon Graphics, Inc. (Jeffrey Newquist)
 */

#अगर_अघोषित __GBE_H__
#घोषणा __GBE_H__

काष्ठा sgi_gbe अणु
	अस्थिर uपूर्णांक32_t ctrlstat;	/* general control */
	अस्थिर uपूर्णांक32_t करोtघड़ी;	/* करोt घड़ी PLL control */
	अस्थिर uपूर्णांक32_t i2c;		/* crt I2C control */
	अस्थिर uपूर्णांक32_t sysclk;	/* प्रणाली घड़ी PLL control */
	अस्थिर uपूर्णांक32_t i2cfp;	/* flat panel I2C control */
	अस्थिर uपूर्णांक32_t id;		/* device id/chip revision */
	अस्थिर uपूर्णांक32_t config;       /* घातer on configuration [1] */
	अस्थिर uपूर्णांक32_t bist;         /* पूर्णांकernal bist status [1] */
	uपूर्णांक32_t _pad0[0x010000/4 - 8];
	अस्थिर uपूर्णांक32_t vt_xy;	/* current करोt coords */
	अस्थिर uपूर्णांक32_t vt_xymax;	/* maximum करोt coords */
	अस्थिर uपूर्णांक32_t vt_vsync;	/* vsync on/off */
	अस्थिर uपूर्णांक32_t vt_hsync;	/* hsync on/off */
	अस्थिर uपूर्णांक32_t vt_vblank;	/* vblank on/off */
	अस्थिर uपूर्णांक32_t vt_hblank;	/* hblank on/off */
	अस्थिर uपूर्णांक32_t vt_flags;	/* polarity of vt संकेतs */
	अस्थिर uपूर्णांक32_t vt_f2rf_lock;	/* f2rf & framelck y coord */
	अस्थिर uपूर्णांक32_t vt_पूर्णांकr01;	/* पूर्णांकr 0,1 y coords */
	अस्थिर uपूर्णांक32_t vt_पूर्णांकr23;	/* पूर्णांकr 2,3 y coords */
	अस्थिर uपूर्णांक32_t fp_hdrv;	/* flat panel hdrv on/off */
	अस्थिर uपूर्णांक32_t fp_vdrv;	/* flat panel vdrv on/off */
	अस्थिर uपूर्णांक32_t fp_de;	/* flat panel de on/off */
	अस्थिर uपूर्णांक32_t vt_hpixen;	/* पूर्णांकrnl horiz pixel on/off */
	अस्थिर uपूर्णांक32_t vt_vpixen;	/* पूर्णांकrnl vert pixel on/off */
	अस्थिर uपूर्णांक32_t vt_hcmap;	/* cmap ग_लिखो (horiz) */
	अस्थिर uपूर्णांक32_t vt_vcmap;	/* cmap ग_लिखो (vert) */
	अस्थिर uपूर्णांक32_t did_start_xy;	/* eol/f did/xy reset val */
	अस्थिर uपूर्णांक32_t crs_start_xy;	/* eol/f crs/xy reset val */
	अस्थिर uपूर्णांक32_t vc_start_xy;	/* eol/f vc/xy reset val */
	uपूर्णांक32_t _pad1[0xffb0/4];
	अस्थिर uपूर्णांक32_t ovr_width_tile;/*overlay plane ctrl 0 */
	अस्थिर uपूर्णांक32_t ovr_inhwctrl;	/* overlay plane ctrl 1 */
	अस्थिर uपूर्णांक32_t ovr_control;	/* overlay plane ctrl 1 */
	uपूर्णांक32_t _pad2[0xfff4/4];
	अस्थिर uपूर्णांक32_t frm_माप_प्रकारile;/* normal plane ctrl 0 */
	अस्थिर uपूर्णांक32_t frm_size_pixel;/*normal plane ctrl 1 */
	अस्थिर uपूर्णांक32_t frm_inhwctrl;	/* normal plane ctrl 2 */
	अस्थिर uपूर्णांक32_t frm_control;	/* normal plane ctrl 3 */
	uपूर्णांक32_t _pad3[0xfff0/4];
	अस्थिर uपूर्णांक32_t did_inhwctrl;	/* DID control */
	अस्थिर uपूर्णांक32_t did_control;	/* DID shaकरोw */
	uपूर्णांक32_t _pad4[0x7ff8/4];
	अस्थिर uपूर्णांक32_t mode_regs[32];/* WID table */
	uपूर्णांक32_t _pad5[0x7f80/4];
	अस्थिर uपूर्णांक32_t cmap[6144];	/* color map */
	uपूर्णांक32_t _pad6[0x2000/4];
	अस्थिर uपूर्णांक32_t cm_fअगरo;	/* color map fअगरo status */
	uपूर्णांक32_t _pad7[0x7ffc/4];
	अस्थिर uपूर्णांक32_t gmap[256];	/* gamma map */
	uपूर्णांक32_t _pad8[0x7c00/4];
	अस्थिर uपूर्णांक32_t gmap10[1024];	/* gamma map */
	uपूर्णांक32_t _pad9[0x7000/4];
	अस्थिर uपूर्णांक32_t crs_pos;	/* cusror control 0 */
	अस्थिर uपूर्णांक32_t crs_ctl;	/* cusror control 1 */
	अस्थिर uपूर्णांक32_t crs_cmap[3];	/* crs cmap */
	uपूर्णांक32_t _pad10[0x7fec/4];
	अस्थिर uपूर्णांक32_t crs_glyph[64];/* crs glyph */
	uपूर्णांक32_t _pad11[0x7f00/4];
	अस्थिर uपूर्णांक32_t vc_0;	/* video capture crtl 0 */
	अस्थिर uपूर्णांक32_t vc_1;	/* video capture crtl 1 */
	अस्थिर uपूर्णांक32_t vc_2;	/* video capture crtl 2 */
	अस्थिर uपूर्णांक32_t vc_3;	/* video capture crtl 3 */
	अस्थिर uपूर्णांक32_t vc_4;	/* video capture crtl 4 */
	अस्थिर uपूर्णांक32_t vc_5;	/* video capture crtl 5 */
	अस्थिर uपूर्णांक32_t vc_6;	/* video capture crtl 6 */
	अस्थिर uपूर्णांक32_t vc_7;	/* video capture crtl 7 */
	अस्थिर uपूर्णांक32_t vc_8;	/* video capture crtl 8 */
पूर्ण;

#घोषणा MASK(msb, lsb)		\
	( (((u32)1<<((msb)-(lsb)+1))-1) << (lsb) )
#घोषणा GET(v, msb, lsb)	\
	( ((u32)(v) & MASK(msb,lsb)) >> (lsb) )
#घोषणा SET(v, f, msb, lsb)	\
	( (v) = ((v)&~MASK(msb,lsb)) | (( (u32)(f)<<(lsb) ) & MASK(msb,lsb)) )

#घोषणा GET_GBE_FIELD(reg, field, v)		\
	GET((v), GBE_##reg##_##field##_MSB, GBE_##reg##_##field##_LSB)
#घोषणा SET_GBE_FIELD(reg, field, v, f)		\
	SET((v), (f), GBE_##reg##_##field##_MSB, GBE_##reg##_##field##_LSB)

/*
 * Bit mask inक्रमmation
 */
#घोषणा GBE_CTRLSTAT_CHIPID_MSB		 3
#घोषणा GBE_CTRLSTAT_CHIPID_LSB		 0
#घोषणा GBE_CTRLSTAT_SENSE_N_MSB	 4
#घोषणा GBE_CTRLSTAT_SENSE_N_LSB	 4
#घोषणा GBE_CTRLSTAT_PCLKSEL_MSB	29
#घोषणा GBE_CTRLSTAT_PCLKSEL_LSB	28

#घोषणा GBE_DOTCLK_M_MSB		 7
#घोषणा GBE_DOTCLK_M_LSB		 0
#घोषणा GBE_DOTCLK_N_MSB		13
#घोषणा GBE_DOTCLK_N_LSB		 8
#घोषणा GBE_DOTCLK_P_MSB		15
#घोषणा GBE_DOTCLK_P_LSB		14
#घोषणा GBE_DOTCLK_RUN_MSB		20
#घोषणा GBE_DOTCLK_RUN_LSB		20

#घोषणा GBE_VT_XY_Y_MSB		23
#घोषणा GBE_VT_XY_Y_LSB		12
#घोषणा GBE_VT_XY_X_MSB		11
#घोषणा GBE_VT_XY_X_LSB		 0
#घोषणा GBE_VT_XY_FREEZE_MSB		31
#घोषणा GBE_VT_XY_FREEZE_LSB		31

#घोषणा GBE_FP_VDRV_ON_MSB	23
#घोषणा GBE_FP_VDRV_ON_LSB	12
#घोषणा GBE_FP_VDRV_OFF_MSB	11
#घोषणा GBE_FP_VDRV_OFF_LSB	0

#घोषणा GBE_FP_HDRV_ON_MSB	23
#घोषणा GBE_FP_HDRV_ON_LSB	12
#घोषणा GBE_FP_HDRV_OFF_MSB	11
#घोषणा GBE_FP_HDRV_OFF_LSB	0

#घोषणा GBE_FP_DE_ON_MSB		23
#घोषणा GBE_FP_DE_ON_LSB		12
#घोषणा GBE_FP_DE_OFF_MSB		11
#घोषणा GBE_FP_DE_OFF_LSB		0

#घोषणा GBE_VT_VSYNC_VSYNC_ON_MSB	23
#घोषणा GBE_VT_VSYNC_VSYNC_ON_LSB	12
#घोषणा GBE_VT_VSYNC_VSYNC_OFF_MSB	11
#घोषणा GBE_VT_VSYNC_VSYNC_OFF_LSB	 0

#घोषणा GBE_VT_HSYNC_HSYNC_ON_MSB	23
#घोषणा GBE_VT_HSYNC_HSYNC_ON_LSB	12
#घोषणा GBE_VT_HSYNC_HSYNC_OFF_MSB	11
#घोषणा GBE_VT_HSYNC_HSYNC_OFF_LSB	 0

#घोषणा GBE_VT_VBLANK_VBLANK_ON_MSB	23
#घोषणा GBE_VT_VBLANK_VBLANK_ON_LSB	12
#घोषणा GBE_VT_VBLANK_VBLANK_OFF_MSB	11
#घोषणा GBE_VT_VBLANK_VBLANK_OFF_LSB	 0

#घोषणा GBE_VT_HBLANK_HBLANK_ON_MSB	23
#घोषणा GBE_VT_HBLANK_HBLANK_ON_LSB	12
#घोषणा GBE_VT_HBLANK_HBLANK_OFF_MSB	11
#घोषणा GBE_VT_HBLANK_HBLANK_OFF_LSB	 0

#घोषणा GBE_VT_FLAGS_F2RF_HIGH_MSB	 6
#घोषणा GBE_VT_FLAGS_F2RF_HIGH_LSB	 6
#घोषणा GBE_VT_FLAGS_SYNC_LOW_MSB	 5
#घोषणा GBE_VT_FLAGS_SYNC_LOW_LSB	 5
#घोषणा GBE_VT_FLAGS_SYNC_HIGH_MSB	 4
#घोषणा GBE_VT_FLAGS_SYNC_HIGH_LSB	 4
#घोषणा GBE_VT_FLAGS_HDRV_LOW_MSB	 3
#घोषणा GBE_VT_FLAGS_HDRV_LOW_LSB	 3
#घोषणा GBE_VT_FLAGS_HDRV_INVERT_MSB	 2
#घोषणा GBE_VT_FLAGS_HDRV_INVERT_LSB	 2
#घोषणा GBE_VT_FLAGS_VDRV_LOW_MSB	 1
#घोषणा GBE_VT_FLAGS_VDRV_LOW_LSB	 1
#घोषणा GBE_VT_FLAGS_VDRV_INVERT_MSB	 0
#घोषणा GBE_VT_FLAGS_VDRV_INVERT_LSB	 0

#घोषणा GBE_VT_VCMAP_VCMAP_ON_MSB	23
#घोषणा GBE_VT_VCMAP_VCMAP_ON_LSB	12
#घोषणा GBE_VT_VCMAP_VCMAP_OFF_MSB	11
#घोषणा GBE_VT_VCMAP_VCMAP_OFF_LSB	 0

#घोषणा GBE_VT_HCMAP_HCMAP_ON_MSB	23
#घोषणा GBE_VT_HCMAP_HCMAP_ON_LSB	12
#घोषणा GBE_VT_HCMAP_HCMAP_OFF_MSB	11
#घोषणा GBE_VT_HCMAP_HCMAP_OFF_LSB	 0

#घोषणा GBE_VT_XYMAX_MAXX_MSB	11
#घोषणा GBE_VT_XYMAX_MAXX_LSB	 0
#घोषणा GBE_VT_XYMAX_MAXY_MSB	23
#घोषणा GBE_VT_XYMAX_MAXY_LSB	12

#घोषणा GBE_VT_HPIXEN_HPIXEN_ON_MSB	23
#घोषणा GBE_VT_HPIXEN_HPIXEN_ON_LSB	12
#घोषणा GBE_VT_HPIXEN_HPIXEN_OFF_MSB	11
#घोषणा GBE_VT_HPIXEN_HPIXEN_OFF_LSB	 0

#घोषणा GBE_VT_VPIXEN_VPIXEN_ON_MSB	23
#घोषणा GBE_VT_VPIXEN_VPIXEN_ON_LSB	12
#घोषणा GBE_VT_VPIXEN_VPIXEN_OFF_MSB	11
#घोषणा GBE_VT_VPIXEN_VPIXEN_OFF_LSB	 0

#घोषणा GBE_OVR_CONTROL_OVR_DMA_ENABLE_MSB	 0
#घोषणा GBE_OVR_CONTROL_OVR_DMA_ENABLE_LSB	 0

#घोषणा GBE_OVR_INHWCTRL_OVR_DMA_ENABLE_MSB	 0
#घोषणा GBE_OVR_INHWCTRL_OVR_DMA_ENABLE_LSB	 0

#घोषणा GBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_MSB	13
#घोषणा GBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_LSB	13

#घोषणा GBE_FRM_CONTROL_FRM_DMA_ENABLE_MSB	 0
#घोषणा GBE_FRM_CONTROL_FRM_DMA_ENABLE_LSB	 0
#घोषणा GBE_FRM_CONTROL_FRM_TILE_PTR_MSB	31
#घोषणा GBE_FRM_CONTROL_FRM_TILE_PTR_LSB	 9
#घोषणा GBE_FRM_CONTROL_FRM_LINEAR_MSB		 1
#घोषणा GBE_FRM_CONTROL_FRM_LINEAR_LSB		 1

#घोषणा GBE_FRM_INHWCTRL_FRM_DMA_ENABLE_MSB	 0
#घोषणा GBE_FRM_INHWCTRL_FRM_DMA_ENABLE_LSB	 0

#घोषणा GBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_MSB	12
#घोषणा GBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_LSB	 5
#घोषणा GBE_FRM_SIZE_TILE_FRM_RHS_MSB		 4
#घोषणा GBE_FRM_SIZE_TILE_FRM_RHS_LSB		 0
#घोषणा GBE_FRM_SIZE_TILE_FRM_DEPTH_MSB		14
#घोषणा GBE_FRM_SIZE_TILE_FRM_DEPTH_LSB		13
#घोषणा GBE_FRM_SIZE_TILE_FRM_FIFO_RESET_MSB	15
#घोषणा GBE_FRM_SIZE_TILE_FRM_FIFO_RESET_LSB	15

#घोषणा GBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_MSB	31
#घोषणा GBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_LSB	16

#घोषणा GBE_DID_CONTROL_DID_DMA_ENABLE_MSB	 0
#घोषणा GBE_DID_CONTROL_DID_DMA_ENABLE_LSB	 0
#घोषणा GBE_DID_INHWCTRL_DID_DMA_ENABLE_MSB	 0
#घोषणा GBE_DID_INHWCTRL_DID_DMA_ENABLE_LSB	 0

#घोषणा GBE_DID_START_XY_DID_STARTY_MSB		23
#घोषणा GBE_DID_START_XY_DID_STARTY_LSB		12
#घोषणा GBE_DID_START_XY_DID_STARTX_MSB		11
#घोषणा GBE_DID_START_XY_DID_STARTX_LSB		 0

#घोषणा GBE_CRS_START_XY_CRS_STARTY_MSB		23
#घोषणा GBE_CRS_START_XY_CRS_STARTY_LSB		12
#घोषणा GBE_CRS_START_XY_CRS_STARTX_MSB		11
#घोषणा GBE_CRS_START_XY_CRS_STARTX_LSB		 0

#घोषणा GBE_WID_AUX_MSB		12
#घोषणा GBE_WID_AUX_LSB		11
#घोषणा GBE_WID_GAMMA_MSB	10
#घोषणा GBE_WID_GAMMA_LSB	10
#घोषणा GBE_WID_CM_MSB		 9
#घोषणा GBE_WID_CM_LSB		 5
#घोषणा GBE_WID_TYP_MSB		 4
#घोषणा GBE_WID_TYP_LSB		 2
#घोषणा GBE_WID_BUF_MSB		 1
#घोषणा GBE_WID_BUF_LSB		 0

#घोषणा GBE_VC_START_XY_VC_STARTY_MSB	23
#घोषणा GBE_VC_START_XY_VC_STARTY_LSB	12
#घोषणा GBE_VC_START_XY_VC_STARTX_MSB	11
#घोषणा GBE_VC_START_XY_VC_STARTX_LSB	 0

/* Constants */

#घोषणा GBE_FRM_DEPTH_8		0
#घोषणा GBE_FRM_DEPTH_16	1
#घोषणा GBE_FRM_DEPTH_32	2

#घोषणा GBE_CMODE_I8		0
#घोषणा GBE_CMODE_I12		1
#घोषणा GBE_CMODE_RG3B2		2
#घोषणा GBE_CMODE_RGB4		3
#घोषणा GBE_CMODE_ARGB5		4
#घोषणा GBE_CMODE_RGB8		5
#घोषणा GBE_CMODE_RGBA5		6
#घोषणा GBE_CMODE_RGB10		7

#घोषणा GBE_BMODE_BOTH		3

#घोषणा GBE_CRS_MAGIC		54
#घोषणा GBE_PIXEN_MAGIC_ON	19
#घोषणा GBE_PIXEN_MAGIC_OFF	 2

#घोषणा GBE_TLB_SIZE		128

/* [1] - only GBE revision 2 and later */

/*
 * Video Timing Data Structure
 */

काष्ठा gbe_timing_info अणु
	पूर्णांक flags;
	लघु width;		/* Monitor resolution */
	लघु height;
	पूर्णांक fields_sec;		/* fields/sec  (Hz -3 dec. places */
	पूर्णांक cfreq;		/* pixel घड़ी frequency (MHz -3 dec. places) */
	लघु htotal;		/* Horizontal total pixels */
	लघु hblank_start;	/* Horizontal blank start */
	लघु hblank_end;	/* Horizontal blank end */
	लघु hsync_start;	/* Horizontal sync start */
	लघु hsync_end;	/* Horizontal sync end */
	लघु vtotal;		/* Vertical total lines */
	लघु vblank_start;	/* Vertical blank start */
	लघु vblank_end;	/* Vertical blank end */
	लघु vsync_start;	/* Vertical sync start */
	लघु vsync_end;	/* Vertical sync end */
	लघु pll_m;		/* PLL M parameter */
	लघु pll_n;		/* PLL P parameter */
	लघु pll_p;		/* PLL N parameter */
पूर्ण;

/* Defines क्रम gbe_vof_info_t flags */

#घोषणा GBE_VOF_UNKNOWNMON	1
#घोषणा GBE_VOF_STEREO		2
#घोषणा GBE_VOF_DO_GENSYNC	4	/* enable incoming sync */
#घोषणा GBE_VOF_SYNC_ON_GREEN	8	/* sync on green */
#घोषणा GBE_VOF_FLATPANEL	0x1000	/* FLATPANEL Timing */
#घोषणा GBE_VOF_MAGICKEY	0x2000	/* Backकरोor key */

#पूर्ण_अगर		/* ! __GBE_H__ */
