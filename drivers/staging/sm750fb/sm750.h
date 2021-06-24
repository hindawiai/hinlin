<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LYNXDRV_H_
#घोषणा LYNXDRV_H_

#घोषणा FB_ACCEL_SMI 0xab

#घोषणा MHZ(x) ((x) * 1000000)

#घोषणा DEFAULT_SM750_CHIP_CLOCK	290
#घोषणा DEFAULT_SM750LE_CHIP_CLOCK	333
#अगर_अघोषित SM750LE_REVISION_ID
#घोषणा SM750LE_REVISION_ID ((अचिन्हित अक्षर)0xfe)
#पूर्ण_अगर

क्रमागत sm750_pnltype अणु
	sm750_24TFT = 0,	/* 24bit tft */
	sm750_dualTFT = 2,	/* dual 18 bit tft */
	sm750_द्विगुनTFT = 1,	/* 36 bit द्विगुन pixel tft */
पूर्ण;

/* vga channel is not concerned  */
क्रमागत sm750_dataflow अणु
	sm750_simul_pri,	/* primary => all head */
	sm750_simul_sec,	/* secondary => all head */
	sm750_dual_normal,	/* primary => panel head and secondary => crt */
	sm750_dual_swap,	/* primary => crt head and secondary => panel */
पूर्ण;

क्रमागत sm750_channel अणु
	sm750_primary = 0,
	/* क्रमागत value equal to the रेजिस्टर filed data */
	sm750_secondary = 1,
पूर्ण;

क्रमागत sm750_path अणु
	sm750_panel = 1,
	sm750_crt = 2,
	sm750_pnc = 3,	/* panel and crt */
पूर्ण;

काष्ठा init_status अणु
	uलघु घातerMode;
	/* below three घड़ीs are in unit of MHZ*/
	uलघु chip_clk;
	uलघु mem_clk;
	uलघु master_clk;
	uलघु setAllEngOff;
	uलघु resetMemory;
पूर्ण;

काष्ठा lynx_accel अणु
	/* base भव address of DPR रेजिस्टरs */
	अस्थिर अचिन्हित अक्षर __iomem *dprBase;
	/* base भव address of de data port */
	अस्थिर अचिन्हित अक्षर __iomem *dpPortBase;

	/* function poपूर्णांकers */
	व्योम (*de_init)(काष्ठा lynx_accel *accel);

	पूर्णांक (*de_रुको)(व्योम);/* see अगर hardware पढ़ोy to work */

	पूर्णांक (*de_fillrect)(काष्ठा lynx_accel *accel,
			   u32 base, u32 pitch, u32 bpp,
			   u32 x, u32 y, u32 width, u32 height,
			   u32 color, u32 rop);

	पूर्णांक (*de_copyarea)(काष्ठा lynx_accel *accel,
			   u32 s_base, u32 s_pitch,
			   u32 sx, u32 sy,
			   u32 d_base, u32 d_pitch,
			   u32 bpp, u32 dx, u32 dy,
			   u32 width, u32 height,
			   u32 rop2);

	पूर्णांक (*de_imageblit)(काष्ठा lynx_accel *accel, स्थिर अक्षर *p_srcbuf,
			    u32 src_delta, u32 start_bit, u32 d_base, u32 d_pitch,
			    u32 byte_per_pixel, u32 dx, u32 dy, u32 width,
			    u32 height, u32 f_color, u32 b_color, u32 rop2);

पूर्ण;

काष्ठा sm750_dev अणु
	/* common members */
	u16 devid;
	u8 revid;
	काष्ठा pci_dev *pdev;
	काष्ठा fb_info *fbinfo[2];
	काष्ठा lynx_accel accel;
	पूर्णांक accel_off;
	पूर्णांक fb_count;
	पूर्णांक mtrr_off;
	काष्ठाअणु
		पूर्णांक vram;
	पूर्ण mtrr;
	/* all smi graphic adaptor got below attributes */
	अचिन्हित दीर्घ vidmem_start;
	अचिन्हित दीर्घ vidreg_start;
	__u32 vidmem_size;
	__u32 vidreg_size;
	व्योम __iomem *pvReg;
	अचिन्हित अक्षर __iomem *pvMem;
	/* locks*/
	spinlock_t slock;

	काष्ठा init_status initParm;
	क्रमागत sm750_pnltype pnltype;
	क्रमागत sm750_dataflow dataflow;
	पूर्णांक nocrt;

	/*
	 * 0: no hardware cursor
	 * 1: primary crtc hw cursor enabled,
	 * 2: secondary crtc hw cursor enabled
	 * 3: both ctrc hw cursor enabled
	 */
	पूर्णांक hwCursor;
पूर्ण;

काष्ठा lynx_cursor अणु
	/* cursor width ,height and size */
	पूर्णांक w;
	पूर्णांक h;
	पूर्णांक size;
	/* hardware limitation */
	पूर्णांक maxW;
	पूर्णांक maxH;
	/* base भव address and offset  of cursor image */
	अक्षर __iomem *vstart;
	पूर्णांक offset;
	/* mmio addr of hw cursor */
	अस्थिर अक्षर __iomem *mmio;
पूर्ण;

काष्ठा lynxfb_crtc अणु
	अचिन्हित अक्षर __iomem *vCursor; /* भव address of cursor */
	अचिन्हित अक्षर __iomem *vScreen; /* भव address of on_screen */
	पूर्णांक oCursor; /* cursor address offset in vidmem */
	पूर्णांक oScreen; /* onscreen address offset in vidmem */
	पूर्णांक channel;/* which channel this crtc stands क्रम*/
	resource_माप_प्रकार vidmem_size;/* this view's video memory max size */

	/* below attributes beदीर्घ to info->fix, their value depends on specअगरic adaptor*/
	u16 line_pad;/* padding inक्रमmation:0,1,2,4,8,16,... */
	u16 xpanstep;
	u16 ypanstep;
	u16 ywrapstep;

	व्योम *priv;

	/* cursor inक्रमmation */
	काष्ठा lynx_cursor cursor;
पूर्ण;

काष्ठा lynxfb_output अणु
	पूर्णांक dpms;
	पूर्णांक paths;
	/*
	 * which paths(s) this output stands क्रम,क्रम sm750:
	 * paths=1:means output क्रम panel paths
	 * paths=2:means output क्रम crt paths
	 * paths=3:means output क्रम both panel and crt paths
	 */

	पूर्णांक *channel;
	/*
	 * which channel these outमाला_दो linked with,क्रम sm750:
	 * *channel=0 means primary channel
	 * *channel=1 means secondary channel
	 * output->channel ==> &crtc->channel
	 */
	व्योम *priv;

	पूर्णांक (*proc_setBLANK)(काष्ठा lynxfb_output *output, पूर्णांक blank);
पूर्ण;

काष्ठा lynxfb_par अणु
	/* either 0 or 1 क्रम dual head adaptor,0 is the older one रेजिस्टरed */
	पूर्णांक index;
	अचिन्हित पूर्णांक pseuकरो_palette[256];
	काष्ठा lynxfb_crtc crtc;
	काष्ठा lynxfb_output output;
	काष्ठा fb_info *info;
	काष्ठा sm750_dev *dev;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ ps_to_hz(अचिन्हित पूर्णांक psvalue)
अणु
	अचिन्हित दीर्घ दीर्घ numerator = 1000 * 1000 * 1000 * 1000ULL;
	/* 10^12 / picosecond period gives frequency in Hz */
	करो_भाग(numerator, psvalue);
	वापस (अचिन्हित दीर्घ)numerator;
पूर्ण

पूर्णांक hw_sm750_map(काष्ठा sm750_dev *sm750_dev, काष्ठा pci_dev *pdev);
पूर्णांक hw_sm750_inithw(काष्ठा sm750_dev *sm750_dev, काष्ठा pci_dev *pdev);
व्योम hw_sm750_initAccel(काष्ठा sm750_dev *sm750_dev);
पूर्णांक hw_sm750_deWait(व्योम);
पूर्णांक hw_sm750le_deWait(व्योम);

पूर्णांक hw_sm750_output_setMode(काष्ठा lynxfb_output *output,
			    काष्ठा fb_var_screeninfo *var,
			    काष्ठा fb_fix_screeninfo *fix);

पूर्णांक hw_sm750_crtc_checkMode(काष्ठा lynxfb_crtc *crtc,
			    काष्ठा fb_var_screeninfo *var);

पूर्णांक hw_sm750_crtc_setMode(काष्ठा lynxfb_crtc *crtc,
			  काष्ठा fb_var_screeninfo *var,
			  काष्ठा fb_fix_screeninfo *fix);

पूर्णांक hw_sm750_setColReg(काष्ठा lynxfb_crtc *crtc, uलघु index,
		       uलघु red, uलघु green, uलघु blue);

पूर्णांक hw_sm750_setBLANK(काष्ठा lynxfb_output *output, पूर्णांक blank);
पूर्णांक hw_sm750le_setBLANK(काष्ठा lynxfb_output *output, पूर्णांक blank);
पूर्णांक hw_sm750_pan_display(काष्ठा lynxfb_crtc *crtc,
			 स्थिर काष्ठा fb_var_screeninfo *var,
			 स्थिर काष्ठा fb_info *info);

#पूर्ण_अगर
