<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  ATI Frame Buffer Device Driver Core Definitions
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
    /*
     *  Elements of the hardware specअगरic atyfb_par काष्ठाure
     */

काष्ठा crtc अणु
	u32 vxres;
	u32 vyres;
	u32 xoffset;
	u32 yoffset;
	u32 bpp;
	u32 h_tot_disp;
	u32 h_sync_strt_wid;
	u32 v_tot_disp;
	u32 v_sync_strt_wid;
	u32 vline_crnt_vline;
	u32 off_pitch;
	u32 gen_cntl;
	u32 dp_pix_width;	/* acceleration */
	u32 dp_chain_mask;	/* acceleration */
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	u32 horz_stretching;
	u32 vert_stretching;
	u32 ext_vert_stretch;
	u32 shaकरोw_h_tot_disp;
	u32 shaकरोw_h_sync_strt_wid;
	u32 shaकरोw_v_tot_disp;
	u32 shaकरोw_v_sync_strt_wid;
	u32 lcd_gen_cntl;
	u32 lcd_config_panel;
	u32 lcd_index;
#पूर्ण_अगर
पूर्ण;

काष्ठा aty_पूर्णांकerrupt अणु
	रुको_queue_head_t रुको;
	अचिन्हित पूर्णांक count;
	पूर्णांक pan_display;
पूर्ण;

काष्ठा pll_info अणु
	पूर्णांक pll_max;
	पूर्णांक pll_min;
	पूर्णांक sclk, mclk, mclk_pm, xclk;
	पूर्णांक ref_भाग;
	पूर्णांक ref_clk;
	पूर्णांक ecp_max;
पूर्ण;

प्रकार काष्ठा अणु
	u16 unknown1;
	u16 PCLK_min_freq;
	u16 PCLK_max_freq;
	u16 unknown2;
	u16 ref_freq;
	u16 ref_भागider;
	u16 unknown3;
	u16 MCLK_pwd;
	u16 MCLK_max_freq;
	u16 XCLK_max_freq;
	u16 SCLK_freq;
पूर्ण __attribute__ ((packed)) PLL_BLOCK_MACH64;

काष्ठा pll_514 अणु
	u8 m;
	u8 n;
पूर्ण;

काष्ठा pll_18818 अणु
	u32 program_bits;
	u32 locationAddr;
	u32 period_in_ps;
	u32 post_भागider;
पूर्ण;

काष्ठा pll_ct अणु
	u8 pll_ref_भाग;
	u8 pll_gen_cntl;
	u8 mclk_fb_भाग;
	u8 mclk_fb_mult; /* 2 ro 4 */
	u8 sclk_fb_भाग;
	u8 pll_vclk_cntl;
	u8 vclk_post_भाग;
	u8 vclk_fb_भाग;
	u8 pll_ext_cntl;
	u8 ext_vpll_cntl;
	u8 spll_cntl2;
	u32 dsp_config; /* Mach64 GTB DSP */
	u32 dsp_on_off; /* Mach64 GTB DSP */
	u32 dsp_loop_latency;
	u32 fअगरo_size;
	u32 xclkpagefaultdelay;
	u32 xclkmaxrasdelay;
	u8 xclk_ref_भाग;
	u8 xclk_post_भाग;
	u8 mclk_post_भाग_real;
	u8 xclk_post_भाग_real;
	u8 vclk_post_भाग_real;
	u8 features;
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	u32 xres; /* use क्रम LCD stretching/scaling */
#पूर्ण_अगर
पूर्ण;

/*
	क्रम pll_ct.features
*/
#घोषणा DONT_USE_SPLL 0x1
#घोषणा DONT_USE_XDLL 0x2
#घोषणा USE_CPUCLK    0x4
#घोषणा POWERDOWN_PLL 0x8

जोड़ aty_pll अणु
	काष्ठा pll_ct ct;
	काष्ठा pll_514 ibm514;
	काष्ठा pll_18818 ics2595;
पूर्ण;

    /*
     *  The hardware parameters क्रम each card
     */

काष्ठा atyfb_par अणु
	u32 pseuकरो_palette[16];
	काष्ठा अणु u8 red, green, blue; पूर्ण palette[256];
	स्थिर काष्ठा aty_dac_ops *dac_ops;
	स्थिर काष्ठा aty_pll_ops *pll_ops;
	व्योम __iomem *ati_regbase;
	अचिन्हित दीर्घ clk_wr_offset; /* meaning overloaded, घड़ी id by CT */
	काष्ठा crtc crtc;
	जोड़ aty_pll pll;
	काष्ठा pll_info pll_limits;
	u32 features;
	u32 ref_clk_per;
	u32 pll_per;
	u32 mclk_per;
	u32 xclk_per;
	u8 bus_type;
	u8 ram_type;
	u8 mem_refresh_rate;
	u16 pci_id;
	u32 accel_flags;
	पूर्णांक blitter_may_be_busy;
	अचिन्हित fअगरo_space;
	पूर्णांक asleep;
	पूर्णांक lock_blank;
	अचिन्हित दीर्घ res_start;
	अचिन्हित दीर्घ res_size;
	काष्ठा pci_dev *pdev;
#अगर_घोषित __sparc__
	काष्ठा pci_mmap_map *mmap_map;
	u8 mmaped;
#पूर्ण_अगर
	पूर्णांक खोलो;
#अगर_घोषित CONFIG_FB_ATY_GENERIC_LCD
	अचिन्हित दीर्घ bios_base_phys;
	अचिन्हित दीर्घ bios_base;
	अचिन्हित दीर्घ lcd_table;
	u16 lcd_width;
	u16 lcd_height;
	u32 lcd_pixघड़ी;
	u16 lcd_refreshrate;
	u16 lcd_htotal;
	u16 lcd_hdisp;
	u16 lcd_hsync_dly;
	u16 lcd_hsync_len;
	u16 lcd_vtotal;
	u16 lcd_vdisp;
	u16 lcd_vsync_len;
	u16 lcd_right_margin;
	u16 lcd_lower_margin;
	u16 lcd_hblank_len;
	u16 lcd_vblank_len;
#पूर्ण_अगर
	अचिन्हित दीर्घ aux_start; /* auxiliary aperture */
	अचिन्हित दीर्घ aux_size;
	काष्ठा aty_पूर्णांकerrupt vblank;
	अचिन्हित दीर्घ irq_flags;
	अचिन्हित पूर्णांक irq;
	spinlock_t पूर्णांक_lock;
	पूर्णांक wc_cookie;
	u32 mem_cntl;
	काष्ठा crtc saved_crtc;
	जोड़ aty_pll saved_pll;
पूर्ण;

    /*
     *  ATI Mach64 features
     */

#घोषणा M64_HAS(feature)	((par)->features & (M64F_##feature))

#घोषणा M64F_RESET_3D		0x00000001
#घोषणा M64F_MAGIC_FIFO		0x00000002
#घोषणा M64F_GTB_DSP		0x00000004
#घोषणा M64F_FIFO_32		0x00000008
#घोषणा M64F_SDRAM_MAGIC_PLL	0x00000010
#घोषणा M64F_MAGIC_POSTDIV	0x00000020
#घोषणा M64F_INTEGRATED		0x00000040
#घोषणा M64F_CT_BUS		0x00000080
#घोषणा M64F_VT_BUS		0x00000100
#घोषणा M64F_MOBIL_BUS		0x00000200
#घोषणा M64F_GX			0x00000400
#घोषणा M64F_CT			0x00000800
#घोषणा M64F_VT			0x00001000
#घोषणा M64F_GT			0x00002000
#घोषणा M64F_MAGIC_VRAM_SIZE	0x00004000
#घोषणा M64F_G3_PB_1_1		0x00008000
#घोषणा M64F_G3_PB_1024x768	0x00010000
#घोषणा M64F_EXTRA_BRIGHT	0x00020000
#घोषणा M64F_LT_LCD_REGS	0x00040000
#घोषणा M64F_XL_DLL		0x00080000
#घोषणा M64F_MFB_FORCE_4	0x00100000
#घोषणा M64F_HW_TRIPLE		0x00200000
#घोषणा M64F_XL_MEM		0x00400000
    /*
     *  Register access
     */

अटल अंतरभूत u32 aty_ld_le32(पूर्णांक regindex, स्थिर काष्ठा atyfb_par *par)
अणु
	/* Hack क्रम bloc 1, should be cleanly optimized by compiler */
	अगर (regindex >= 0x400)
		regindex -= 0x800;

#अगर_घोषित CONFIG_ATARI
	वापस in_le32(par->ati_regbase + regindex);
#अन्यथा
	वापस पढ़ोl(par->ati_regbase + regindex);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम aty_st_le32(पूर्णांक regindex, u32 val, स्थिर काष्ठा atyfb_par *par)
अणु
	/* Hack क्रम bloc 1, should be cleanly optimized by compiler */
	अगर (regindex >= 0x400)
		regindex -= 0x800;

#अगर_घोषित CONFIG_ATARI
	out_le32(par->ati_regbase + regindex, val);
#अन्यथा
	ग_लिखोl(val, par->ati_regbase + regindex);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम aty_st_le16(पूर्णांक regindex, u16 val,
			       स्थिर काष्ठा atyfb_par *par)
अणु
	/* Hack क्रम bloc 1, should be cleanly optimized by compiler */
	अगर (regindex >= 0x400)
		regindex -= 0x800;
#अगर_घोषित CONFIG_ATARI
	out_le16(par->ati_regbase + regindex, val);
#अन्यथा
	ग_लिखोl(val, par->ati_regbase + regindex);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u8 aty_ld_8(पूर्णांक regindex, स्थिर काष्ठा atyfb_par *par)
अणु
	/* Hack क्रम bloc 1, should be cleanly optimized by compiler */
	अगर (regindex >= 0x400)
		regindex -= 0x800;
#अगर_घोषित CONFIG_ATARI
	वापस in_8(par->ati_regbase + regindex);
#अन्यथा
	वापस पढ़ोb(par->ati_regbase + regindex);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम aty_st_8(पूर्णांक regindex, u8 val, स्थिर काष्ठा atyfb_par *par)
अणु
	/* Hack क्रम bloc 1, should be cleanly optimized by compiler */
	अगर (regindex >= 0x400)
		regindex -= 0x800;

#अगर_घोषित CONFIG_ATARI
	out_8(par->ati_regbase + regindex, val);
#अन्यथा
	ग_लिखोb(val, par->ati_regbase + regindex);
#पूर्ण_अगर
पूर्ण

बाह्य व्योम aty_st_lcd(पूर्णांक index, u32 val, स्थिर काष्ठा atyfb_par *par);
बाह्य u32 aty_ld_lcd(पूर्णांक index, स्थिर काष्ठा atyfb_par *par);

    /*
     *  DAC operations
     */

काष्ठा aty_dac_ops अणु
	पूर्णांक (*set_dac) (स्थिर काष्ठा fb_info * info,
		स्थिर जोड़ aty_pll * pll, u32 bpp, u32 accel);
पूर्ण;

बाह्य स्थिर काष्ठा aty_dac_ops aty_dac_ibm514; /* IBM RGB514 */
बाह्य स्थिर काष्ठा aty_dac_ops aty_dac_ati68860b; /* ATI 68860-B */
बाह्य स्थिर काष्ठा aty_dac_ops aty_dac_att21c498; /* AT&T 21C498 */
बाह्य स्थिर काष्ठा aty_dac_ops aty_dac_unsupported; /* unsupported */
बाह्य स्थिर काष्ठा aty_dac_ops aty_dac_ct; /* Integrated */


    /*
     *  Clock operations
     */

काष्ठा aty_pll_ops अणु
	पूर्णांक (*var_to_pll) (स्थिर काष्ठा fb_info * info, u32 vclk_per, u32 bpp, जोड़ aty_pll * pll);
	u32 (*pll_to_var) (स्थिर काष्ठा fb_info * info, स्थिर जोड़ aty_pll * pll);
	व्योम (*set_pll)   (स्थिर काष्ठा fb_info * info, स्थिर जोड़ aty_pll * pll);
	व्योम (*get_pll)   (स्थिर काष्ठा fb_info *info, जोड़ aty_pll * pll);
	पूर्णांक (*init_pll)   (स्थिर काष्ठा fb_info * info, जोड़ aty_pll * pll);
	व्योम (*resume_pll)(स्थिर काष्ठा fb_info *info, जोड़ aty_pll *pll);
पूर्ण;

बाह्य स्थिर काष्ठा aty_pll_ops aty_pll_ati18818_1; /* ATI 18818 */
बाह्य स्थिर काष्ठा aty_pll_ops aty_pll_stg1703; /* STG 1703 */
बाह्य स्थिर काष्ठा aty_pll_ops aty_pll_ch8398; /* Chrontel 8398 */
बाह्य स्थिर काष्ठा aty_pll_ops aty_pll_att20c408; /* AT&T 20C408 */
बाह्य स्थिर काष्ठा aty_pll_ops aty_pll_ibm514; /* IBM RGB514 */
बाह्य स्थिर काष्ठा aty_pll_ops aty_pll_unsupported; /* unsupported */
बाह्य स्थिर काष्ठा aty_pll_ops aty_pll_ct; /* Integrated */


बाह्य व्योम aty_set_pll_ct(स्थिर काष्ठा fb_info *info, स्थिर जोड़ aty_pll *pll);
बाह्य u8 aty_ld_pll_ct(पूर्णांक offset, स्थिर काष्ठा atyfb_par *par);

बाह्य स्थिर u8 aty_postभागiders[8];


    /*
     *  Hardware cursor support
     */

बाह्य पूर्णांक aty_init_cursor(काष्ठा fb_info *info, काष्ठा fb_ops *atyfb_ops);

    /*
     *  Hardware acceleration
     */

अटल अंतरभूत व्योम रुको_क्रम_fअगरo(u16 entries, काष्ठा atyfb_par *par)
अणु
	अचिन्हित fअगरo_space = par->fअगरo_space;
	जबतक (entries > fअगरo_space) अणु
		fअगरo_space = 16 - fls(aty_ld_le32(FIFO_STAT, par) & 0xffff);
	पूर्ण
	par->fअगरo_space = fअगरo_space - entries;
पूर्ण

अटल अंतरभूत व्योम रुको_क्रम_idle(काष्ठा atyfb_par *par)
अणु
	रुको_क्रम_fअगरo(16, par);
	जबतक ((aty_ld_le32(GUI_STAT, par) & 1) != 0);
	par->blitter_may_be_busy = 0;
पूर्ण

बाह्य व्योम aty_reset_engine(काष्ठा atyfb_par *par);
बाह्य व्योम aty_init_engine(काष्ठा atyfb_par *par, काष्ठा fb_info *info);

व्योम atyfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area);
व्योम atyfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
व्योम atyfb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);

