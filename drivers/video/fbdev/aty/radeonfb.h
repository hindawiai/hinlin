<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __RADEONFB_H__
#घोषणा __RADEONFB_H__

#अगर_घोषित CONFIG_FB_RADEON_DEBUG
#घोषणा DEBUG		1
#पूर्ण_अगर

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/fb.h>


#अगर_घोषित CONFIG_FB_RADEON_I2C
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#पूर्ण_अगर

#समावेश <यंत्र/पन.स>

#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#समावेश <video/radeon.h>

/***************************************************************
 * Most of the definitions here are adapted right from XFree86 *
 ***************************************************************/


/*
 * Chip families. Must fit in the low 16 bits of a दीर्घ word
 */
क्रमागत radeon_family अणु
	CHIP_FAMILY_UNKNOW,
	CHIP_FAMILY_LEGACY,
	CHIP_FAMILY_RADEON,
	CHIP_FAMILY_RV100,
	CHIP_FAMILY_RS100,    /* U1 (IGP320M) or A3 (IGP320)*/
	CHIP_FAMILY_RV200,
	CHIP_FAMILY_RS200,    /* U2 (IGP330M/340M/350M) or A4 (IGP330/340/345/350),
				 RS250 (IGP 7000) */
	CHIP_FAMILY_R200,
	CHIP_FAMILY_RV250,
	CHIP_FAMILY_RS300,    /* Radeon 9000 IGP */
	CHIP_FAMILY_RV280,
	CHIP_FAMILY_R300,
	CHIP_FAMILY_R350,
	CHIP_FAMILY_RV350,
	CHIP_FAMILY_RV380,    /* RV370/RV380/M22/M24 */
	CHIP_FAMILY_R420,     /* R420/R423/M18 */
	CHIP_FAMILY_RC410,
	CHIP_FAMILY_RS400,
	CHIP_FAMILY_RS480,
	CHIP_FAMILY_LAST,
पूर्ण;

#घोषणा IS_RV100_VARIANT(rinfo) (((rinfo)->family == CHIP_FAMILY_RV100)  || \
				 ((rinfo)->family == CHIP_FAMILY_RV200)  || \
				 ((rinfo)->family == CHIP_FAMILY_RS100)  || \
				 ((rinfo)->family == CHIP_FAMILY_RS200)  || \
				 ((rinfo)->family == CHIP_FAMILY_RV250)  || \
				 ((rinfo)->family == CHIP_FAMILY_RV280)  || \
				 ((rinfo)->family == CHIP_FAMILY_RS300))


#घोषणा IS_R300_VARIANT(rinfo) (((rinfo)->family == CHIP_FAMILY_R300)  || \
				((rinfo)->family == CHIP_FAMILY_RV350) || \
				((rinfo)->family == CHIP_FAMILY_R350)  || \
				((rinfo)->family == CHIP_FAMILY_RV380) || \
				((rinfo)->family == CHIP_FAMILY_R420)  || \
                               ((rinfo)->family == CHIP_FAMILY_RC410) || \
                               ((rinfo)->family == CHIP_FAMILY_RS480))

/*
 * Chip flags
 */
क्रमागत radeon_chip_flags अणु
	CHIP_FAMILY_MASK	= 0x0000ffffUL,
	CHIP_FLAGS_MASK		= 0xffff0000UL,
	CHIP_IS_MOBILITY	= 0x00010000UL,
	CHIP_IS_IGP		= 0x00020000UL,
	CHIP_HAS_CRTC2		= 0x00040000UL,	
पूर्ण;

/*
 * Errata workarounds
 */
क्रमागत radeon_errata अणु
	CHIP_ERRATA_R300_CG		= 0x00000001,
	CHIP_ERRATA_PLL_DUMMYREADS	= 0x00000002,
	CHIP_ERRATA_PLL_DELAY		= 0x00000004,
पूर्ण;


/*
 * Monitor types
 */
क्रमागत radeon_montype अणु
	MT_NONE = 0,
	MT_CRT,		/* CRT */
	MT_LCD,		/* LCD */
	MT_DFP,		/* DVI */
	MT_CTV,		/* composite TV */
	MT_STV		/* S-Video out */
पूर्ण;

/*
 * DDC i2c ports
 */
क्रमागत ddc_type अणु
	ddc_none,
	ddc_monid,
	ddc_dvi,
	ddc_vga,
	ddc_crt2,
पूर्ण;

/*
 * Connector types
 */
क्रमागत conn_type अणु
	conn_none,
	conn_proprietary,
	conn_crt,
	conn_DVI_I,
	conn_DVI_D,
पूर्ण;


/*
 * PLL infos
 */
काष्ठा pll_info अणु
	पूर्णांक ppll_max;
	पूर्णांक ppll_min;
	पूर्णांक sclk, mclk;
	पूर्णांक ref_भाग;
	पूर्णांक ref_clk;
पूर्ण;


/*
 * This काष्ठाure contains the various रेजिस्टरs manipulated by this
 * driver क्रम setting or restoring a mode. It's mostly copied from
 * XFree's RADEONSaveRec काष्ठाure. A few chip settings might still be
 * tweaked without beeing reflected or saved in these रेजिस्टरs though
 */
काष्ठा radeon_regs अणु
	/* Common रेजिस्टरs */
	u32		ovr_clr;
	u32		ovr_wid_left_right;
	u32		ovr_wid_top_bottom;
	u32		ov0_scale_cntl;
	u32		mpp_tb_config;
	u32		mpp_gp_config;
	u32		subpic_cntl;
	u32		viph_control;
	u32		i2c_cntl_1;
	u32		gen_पूर्णांक_cntl;
	u32		cap0_trig_cntl;
	u32		cap1_trig_cntl;
	u32		bus_cntl;
	u32		surface_cntl;
	u32		bios_5_scratch;

	/* Other रेजिस्टरs to save क्रम VT चयनes or driver load/unload */
	u32		dp_datatype;
	u32		rbbm_soft_reset;
	u32		घड़ी_cntl_index;
	u32		amcgpio_en_reg;
	u32		amcgpio_mask;

	/* Surface/tiling रेजिस्टरs */
	u32		surf_lower_bound[8];
	u32		surf_upper_bound[8];
	u32		surf_info[8];

	/* CRTC रेजिस्टरs */
	u32		crtc_gen_cntl;
	u32		crtc_ext_cntl;
	u32		dac_cntl;
	u32		crtc_h_total_disp;
	u32		crtc_h_sync_strt_wid;
	u32		crtc_v_total_disp;
	u32		crtc_v_sync_strt_wid;
	u32		crtc_offset;
	u32		crtc_offset_cntl;
	u32		crtc_pitch;
	u32		disp_merge_cntl;
	u32		grph_buffer_cntl;
	u32		crtc_more_cntl;

	/* CRTC2 रेजिस्टरs */
	u32		crtc2_gen_cntl;
	u32		dac2_cntl;
	u32		disp_output_cntl;
	u32		disp_hw_debug;
	u32		disp2_merge_cntl;
	u32		grph2_buffer_cntl;
	u32		crtc2_h_total_disp;
	u32		crtc2_h_sync_strt_wid;
	u32		crtc2_v_total_disp;
	u32		crtc2_v_sync_strt_wid;
	u32		crtc2_offset;
	u32		crtc2_offset_cntl;
	u32		crtc2_pitch;

	/* Flat panel regs */
	u32 		fp_crtc_h_total_disp;
	u32		fp_crtc_v_total_disp;
	u32		fp_gen_cntl;
	u32		fp2_gen_cntl;
	u32		fp_h_sync_strt_wid;
	u32		fp2_h_sync_strt_wid;
	u32		fp_horz_stretch;
	u32		fp_panel_cntl;
	u32		fp_v_sync_strt_wid;
	u32		fp2_v_sync_strt_wid;
	u32		fp_vert_stretch;
	u32		lvds_gen_cntl;
	u32		lvds_pll_cntl;
	u32		पंचांगds_crc;
	u32		पंचांगds_transmitter_cntl;

	/* Computed values क्रम PLL */
	u32		करोt_घड़ी_freq;
	पूर्णांक		feedback_भाग;
	पूर्णांक		post_भाग;	

	/* PLL रेजिस्टरs */
	u32		ppll_भाग_3;
	u32		ppll_ref_भाग;
	u32		vclk_ecp_cntl;
	u32		clk_cntl_index;

	/* Computed values क्रम PLL2 */
	u32		करोt_घड़ी_freq_2;
	पूर्णांक		feedback_भाग_2;
	पूर्णांक		post_भाग_2;

	/* PLL2 रेजिस्टरs */
	u32		p2pll_ref_भाग;
	u32		p2pll_भाग_0;
	u32		htotal_cntl2;

       	/* Palette */
	पूर्णांक		palette_valid;
पूर्ण;

काष्ठा panel_info अणु
	पूर्णांक xres, yres;
	पूर्णांक valid;
	पूर्णांक घड़ी;
	पूर्णांक hOver_plus, hSync_width, hblank;
	पूर्णांक vOver_plus, vSync_width, vblank;
	पूर्णांक hAct_high, vAct_high, पूर्णांकerlaced;
	पूर्णांक pwr_delay;
	पूर्णांक use_bios_भागiders;
	पूर्णांक ref_भागider;
	पूर्णांक post_भागider;
	पूर्णांक fbk_भागider;
पूर्ण;

काष्ठा radeonfb_info;

#अगर_घोषित CONFIG_FB_RADEON_I2C
काष्ठा radeon_i2c_chan अणु
	काष्ठा radeonfb_info		*rinfo;
	u32		 		ddc_reg;
	काष्ठा i2c_adapter		adapter;
	काष्ठा i2c_algo_bit_data	algo;
पूर्ण;
#पूर्ण_अगर

क्रमागत radeon_pm_mode अणु
	radeon_pm_none	= 0,		/* Nothing supported */
	radeon_pm_d2	= 0x00000001,	/* Can करो D2 state */
	radeon_pm_off	= 0x00000002,	/* Can resume from D3 cold */
पूर्ण;

प्रकार व्योम (*reinit_function_ptr)(काष्ठा radeonfb_info *rinfo);

काष्ठा radeonfb_info अणु
	काष्ठा fb_info		*info;

	काष्ठा radeon_regs 	state;
	काष्ठा radeon_regs	init_state;

	अक्षर			name[50];

	अचिन्हित दीर्घ		mmio_base_phys;
	अचिन्हित दीर्घ		fb_base_phys;

	व्योम __iomem		*mmio_base;
	व्योम __iomem		*fb_base;

	अचिन्हित दीर्घ		fb_local_base;

	काष्ठा pci_dev		*pdev;
#अगर defined(CONFIG_PPC) || defined(CONFIG_SPARC)
	काष्ठा device_node	*of_node;
#पूर्ण_अगर

	व्योम __iomem		*bios_seg;
	पूर्णांक			fp_bios_start;

	u32			pseuकरो_palette[16];
	काष्ठा अणु u8 red, green, blue, pad; पूर्ण
				palette[256];

	पूर्णांक			chipset;
	u8			family;
	u8			rev;
	अचिन्हित पूर्णांक		errata;
	अचिन्हित दीर्घ		video_ram;
	अचिन्हित दीर्घ		mapped_vram;
	पूर्णांक			vram_width;
	पूर्णांक			vram_ddr;

	पूर्णांक			pitch, bpp, depth;

	पूर्णांक			has_CRTC2;
	पूर्णांक			is_mobility;
	पूर्णांक			is_IGP;
	पूर्णांक			reversed_DAC;
	पूर्णांक			reversed_TMDS;
	काष्ठा panel_info	panel_info;
	पूर्णांक			mon1_type;
	u8			*mon1_EDID;
	काष्ठा fb_videomode	*mon1_modedb;
	पूर्णांक			mon1_dbsize;
	पूर्णांक			mon2_type;
	u8		        *mon2_EDID;

	u32			dp_gui_master_cntl;

	काष्ठा pll_info		pll;

	पूर्णांक			wc_cookie;

	u32			save_regs[100];
	पूर्णांक			asleep;
	पूर्णांक			lock_blank;
	पूर्णांक			dynclk;
	पूर्णांक			no_schedule;
	क्रमागत radeon_pm_mode	pm_mode;
	reinit_function_ptr     reinit_func;

	/* Lock on रेजिस्टर access */
	spinlock_t		reg_lock;

	/* Timer used क्रम delayed LVDS operations */
	काष्ठा समयr_list	lvds_समयr;
	u32			pending_lvds_gen_cntl;

#अगर_घोषित CONFIG_FB_RADEON_I2C
	काष्ठा radeon_i2c_chan 	i2c[4];
#पूर्ण_अगर
पूर्ण;


#घोषणा PRIMARY_MONITOR(rinfo)	(rinfo->mon1_type)


/*
 * IO macros
 */

व्योम _radeon_msleep(काष्ठा radeonfb_info *rinfo, अचिन्हित दीर्घ ms);

#घोषणा INREG8(addr)		पढ़ोb((rinfo->mmio_base)+addr)
#घोषणा OUTREG8(addr,val)	ग_लिखोb(val, (rinfo->mmio_base)+addr)
#घोषणा INREG16(addr)		पढ़ोw((rinfo->mmio_base)+addr)
#घोषणा OUTREG16(addr,val)	ग_लिखोw(val, (rinfo->mmio_base)+addr)
#घोषणा INREG(addr)		पढ़ोl((rinfo->mmio_base)+addr)
#घोषणा OUTREG(addr,val)	ग_लिखोl(val, (rinfo->mmio_base)+addr)

व्योम _OUTREGP(काष्ठा radeonfb_info *rinfo, u32 addr, u32 val, u32 mask);

#घोषणा OUTREGP(addr,val,mask)	_OUTREGP(rinfo, addr, val,mask)

/*
 * Note about PLL रेजिस्टर accesses:
 *
 * I have हटाओd the spinlock on them on purpose. The driver now
 * expects that it will only manipulate the PLL रेजिस्टरs in normal
 * task environment, where radeon_msleep() will be called, रक्षित
 * by a semaphore (currently the console semaphore) so that no conflict
 * will happen on the PLL रेजिस्टर index.
 *
 * With the latest changes to the VT layer, this is guaranteed क्रम all
 * calls except the actual drawing/blits which aren't supposed to use
 * the PLL रेजिस्टरs anyway
 *
 * This is very important क्रम the workarounds to work properly. The only
 * possible exception to this rule is the call to unblank(), which may
 * be करोne at irq समय अगर an oops is in progress.
 */
व्योम radeon_pll_errata_after_index_slow(काष्ठा radeonfb_info *rinfo);
अटल अंतरभूत व्योम radeon_pll_errata_after_index(काष्ठा radeonfb_info *rinfo)
अणु
	अगर (rinfo->errata & CHIP_ERRATA_PLL_DUMMYREADS)
		radeon_pll_errata_after_index_slow(rinfo);
पूर्ण

व्योम radeon_pll_errata_after_data_slow(काष्ठा radeonfb_info *rinfo);
अटल अंतरभूत व्योम radeon_pll_errata_after_data(काष्ठा radeonfb_info *rinfo)
अणु
	अगर (rinfo->errata & (CHIP_ERRATA_PLL_DELAY|CHIP_ERRATA_R300_CG))
		radeon_pll_errata_after_data_slow(rinfo);
पूर्ण

u32 __INPLL(काष्ठा radeonfb_info *rinfo, u32 addr);
व्योम __OUTPLL(काष्ठा radeonfb_info *rinfo, अचिन्हित पूर्णांक index, u32 val);
व्योम __OUTPLLP(काष्ठा radeonfb_info *rinfo, अचिन्हित पूर्णांक index,
			     u32 val, u32 mask);

#घोषणा INPLL(addr)			__INPLL(rinfo, addr)
#घोषणा OUTPLL(index, val)		__OUTPLL(rinfo, index, val)
#घोषणा OUTPLLP(index, val, mask)	__OUTPLLP(rinfo, index, val, mask)


#घोषणा BIOS_IN8(v)  	(पढ़ोb(rinfo->bios_seg + (v)))
#घोषणा BIOS_IN16(v) 	(पढ़ोb(rinfo->bios_seg + (v)) | \
			  (पढ़ोb(rinfo->bios_seg + (v) + 1) << 8))
#घोषणा BIOS_IN32(v) 	(पढ़ोb(rinfo->bios_seg + (v)) | \
			  (पढ़ोb(rinfo->bios_seg + (v) + 1) << 8) | \
			  (पढ़ोb(rinfo->bios_seg + (v) + 2) << 16) | \
			  (पढ़ोb(rinfo->bios_seg + (v) + 3) << 24))

/*
 * Inline utilities
 */
अटल अंतरभूत पूर्णांक round_भाग(पूर्णांक num, पूर्णांक den)
अणु
        वापस (num + (den / 2)) / den;
पूर्ण

अटल अंतरभूत पूर्णांक var_to_depth(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	अगर (var->bits_per_pixel != 16)
		वापस var->bits_per_pixel;
	वापस (var->green.length == 5) ? 15 : 16;
पूर्ण

अटल अंतरभूत u32 radeon_get_dstbpp(u16 depth)
अणु
	चयन (depth) अणु
       	हाल 8:
       		वापस DST_8BPP;
       	हाल 15:
       		वापस DST_15BPP;
       	हाल 16:
       		वापस DST_16BPP;
       	हाल 32:
       		वापस DST_32BPP;
       	शेष:
       		वापस 0;
	पूर्ण
पूर्ण

/*
 * 2D Engine helper routines
 */

व्योम _radeon_fअगरo_रुको(काष्ठा radeonfb_info *rinfo, पूर्णांक entries);
व्योम radeon_engine_flush(काष्ठा radeonfb_info *rinfo);
व्योम _radeon_engine_idle(काष्ठा radeonfb_info *rinfo);

#घोषणा radeon_engine_idle()		_radeon_engine_idle(rinfo)
#घोषणा radeon_fअगरo_रुको(entries)	_radeon_fअगरo_रुको(rinfo,entries)
#घोषणा radeon_msleep(ms)		_radeon_msleep(rinfo,ms)


/* I2C Functions */
बाह्य व्योम radeon_create_i2c_busses(काष्ठा radeonfb_info *rinfo);
बाह्य व्योम radeon_delete_i2c_busses(काष्ठा radeonfb_info *rinfo);
बाह्य पूर्णांक radeon_probe_i2c_connector(काष्ठा radeonfb_info *rinfo, पूर्णांक conn, u8 **out_edid);

/* PM Functions */
बाह्य स्थिर काष्ठा dev_pm_ops radeonfb_pci_pm_ops;
बाह्य व्योम radeonfb_pm_init(काष्ठा radeonfb_info *rinfo, पूर्णांक dynclk, पूर्णांक ignore_devlist, पूर्णांक क्रमce_sleep);
बाह्य व्योम radeonfb_pm_निकास(काष्ठा radeonfb_info *rinfo);

/* Monitor probe functions */
बाह्य व्योम radeon_probe_screens(काष्ठा radeonfb_info *rinfo,
				 स्थिर अक्षर *monitor_layout, पूर्णांक ignore_edid);
बाह्य व्योम radeon_check_modes(काष्ठा radeonfb_info *rinfo, स्थिर अक्षर *mode_option);
बाह्य पूर्णांक radeon_match_mode(काष्ठा radeonfb_info *rinfo,
			     काष्ठा fb_var_screeninfo *dest,
			     स्थिर काष्ठा fb_var_screeninfo *src);

/* Accel functions */
बाह्य व्योम radeonfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *region);
बाह्य व्योम radeonfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area);
बाह्य व्योम radeonfb_imageblit(काष्ठा fb_info *p, स्थिर काष्ठा fb_image *image);
बाह्य पूर्णांक radeonfb_sync(काष्ठा fb_info *info);
बाह्य व्योम radeonfb_engine_init (काष्ठा radeonfb_info *rinfo);
बाह्य व्योम radeonfb_engine_reset(काष्ठा radeonfb_info *rinfo);

/* Other functions */
बाह्य पूर्णांक radeon_screen_blank(काष्ठा radeonfb_info *rinfo, पूर्णांक blank, पूर्णांक mode_चयन);
बाह्य व्योम radeon_ग_लिखो_mode (काष्ठा radeonfb_info *rinfo, काष्ठा radeon_regs *mode,
			       पूर्णांक reg_only);

/* Backlight functions */
#अगर_घोषित CONFIG_FB_RADEON_BACKLIGHT
बाह्य व्योम radeonfb_bl_init(काष्ठा radeonfb_info *rinfo);
बाह्य व्योम radeonfb_bl_निकास(काष्ठा radeonfb_info *rinfo);
#अन्यथा
अटल अंतरभूत व्योम radeonfb_bl_init(काष्ठा radeonfb_info *rinfo) अणुपूर्ण
अटल अंतरभूत व्योम radeonfb_bl_निकास(काष्ठा radeonfb_info *rinfo) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __RADEONFB_H__ */
