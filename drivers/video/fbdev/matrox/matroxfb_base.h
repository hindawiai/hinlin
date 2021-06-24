<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *
 * Hardware accelerated Matrox Millennium I, II, Mystique, G100, G200, G400 and G450
 *
 * (c) 1998-2002 Petr Vandrovec <vandrove@vc.cvut.cz>
 *
 */
#अगर_अघोषित __MATROXFB_H__
#घोषणा __MATROXFB_H__

/* general, but fairly heavy, debugging */
#अघोषित MATROXFB_DEBUG

/* heavy debugging: */
/* -- logs अ_दो[s], so every समय a अक्षर is displayed, it's logged */
#अघोषित MATROXFB_DEBUG_HEAVY

/* This one _could_ cause infinite loops */
/* It _करोes_ cause lots and lots of messages during idle loops */
#अघोषित MATROXFB_DEBUG_LOOP

/* Debug रेजिस्टर calls, too? */
#अघोषित MATROXFB_DEBUG_REG

/* Guard accelerator accesses with spin_lock_irqsave... */
#अघोषित MATROXFB_USE_SPINLOCKS

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/console.h>
#समावेश <linux/selection.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/समयr.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kd.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/unaligned.h>

#अगर defined(CONFIG_PPC_PMAC)
#समावेश <यंत्र/prom.h>
#समावेश "../macmodes.h"
#पूर्ण_अगर

#अगर_घोषित MATROXFB_DEBUG

#घोषणा DEBUG
#घोषणा DBG(x)		prपूर्णांकk(KERN_DEBUG "matroxfb: %s\n", (x));

#अगर_घोषित MATROXFB_DEBUG_HEAVY
#घोषणा DBG_HEAVY(x)	DBG(x)
#अन्यथा /* MATROXFB_DEBUG_HEAVY */
#घोषणा DBG_HEAVY(x)	/* DBG_HEAVY */
#पूर्ण_अगर /* MATROXFB_DEBUG_HEAVY */

#अगर_घोषित MATROXFB_DEBUG_LOOP
#घोषणा DBG_LOOP(x)	DBG(x)
#अन्यथा /* MATROXFB_DEBUG_LOOP */
#घोषणा DBG_LOOP(x)	/* DBG_LOOP */
#पूर्ण_अगर /* MATROXFB_DEBUG_LOOP */

#अगर_घोषित MATROXFB_DEBUG_REG
#घोषणा DBG_REG(x)	DBG(x)
#अन्यथा /* MATROXFB_DEBUG_REG */
#घोषणा DBG_REG(x)	/* DBG_REG */
#पूर्ण_अगर /* MATROXFB_DEBUG_REG */

#अन्यथा /* MATROXFB_DEBUG */

#घोषणा DBG(x)		/* DBG */
#घोषणा DBG_HEAVY(x)	/* DBG_HEAVY */
#घोषणा DBG_REG(x)	/* DBG_REG */
#घोषणा DBG_LOOP(x)	/* DBG_LOOP */

#पूर्ण_अगर /* MATROXFB_DEBUG */

#अगर_घोषित DEBUG
#घोषणा dprपूर्णांकk(X...)	prपूर्णांकk(X)
#अन्यथा
#घोषणा dprपूर्णांकk(X...)	no_prपूर्णांकk(X)
#पूर्ण_अगर

#अगर_अघोषित PCI_SS_VENDOR_ID_SIEMENS_NIXDORF
#घोषणा PCI_SS_VENDOR_ID_SIEMENS_NIXDORF	0x110A
#पूर्ण_अगर
#अगर_अघोषित PCI_SS_VENDOR_ID_MATROX
#घोषणा PCI_SS_VENDOR_ID_MATROX		PCI_VENDOR_ID_MATROX
#पूर्ण_अगर

#अगर_अघोषित PCI_SS_ID_MATROX_PRODUCTIVA_G100_AGP
#घोषणा PCI_SS_ID_MATROX_GENERIC		0xFF00
#घोषणा PCI_SS_ID_MATROX_PRODUCTIVA_G100_AGP	0xFF01
#घोषणा PCI_SS_ID_MATROX_MYSTIQUE_G200_AGP	0xFF02
#घोषणा PCI_SS_ID_MATROX_MILLENIUM_G200_AGP	0xFF03
#घोषणा PCI_SS_ID_MATROX_MARVEL_G200_AGP	0xFF04
#घोषणा PCI_SS_ID_MATROX_MGA_G100_PCI		0xFF05
#घोषणा PCI_SS_ID_MATROX_MGA_G100_AGP		0x1001
#घोषणा PCI_SS_ID_MATROX_MILLENNIUM_G400_MAX_AGP	0x2179
#घोषणा PCI_SS_ID_SIEMENS_MGA_G100_AGP		0x001E /* 30 */
#घोषणा PCI_SS_ID_SIEMENS_MGA_G200_AGP		0x0032 /* 50 */
#पूर्ण_अगर

#घोषणा MX_VISUAL_TRUECOLOR	FB_VISUAL_सूचीECTCOLOR
#घोषणा MX_VISUAL_सूचीECTCOLOR	FB_VISUAL_TRUECOLOR
#घोषणा MX_VISUAL_PSEUDOCOLOR	FB_VISUAL_PSEUDOCOLOR

#घोषणा CNVT_TOHW(val,width) ((((val)<<(width))+0x7FFF-(val))>>16)

/* G-series and Mystique have (almost) same DAC */
#अघोषित NEED_DAC1064
#अगर defined(CONFIG_FB_MATROX_MYSTIQUE) || defined(CONFIG_FB_MATROX_G)
#घोषणा NEED_DAC1064 1
#पूर्ण_अगर

प्रकार काष्ठा अणु
	व्योम __iomem*	vaddr;
पूर्ण vaddr_t;

अटल अंतरभूत अचिन्हित पूर्णांक mga_पढ़ोb(vaddr_t va, अचिन्हित पूर्णांक offs) अणु
	वापस पढ़ोb(va.vaddr + offs);
पूर्ण

अटल अंतरभूत व्योम mga_ग_लिखोb(vaddr_t va, अचिन्हित पूर्णांक offs, u_पूर्णांक8_t value) अणु
	ग_लिखोb(value, va.vaddr + offs);
पूर्ण

अटल अंतरभूत व्योम mga_ग_लिखोw(vaddr_t va, अचिन्हित पूर्णांक offs, u_पूर्णांक16_t value) अणु
	ग_लिखोw(value, va.vaddr + offs);
पूर्ण

अटल अंतरभूत u_पूर्णांक32_t mga_पढ़ोl(vaddr_t va, अचिन्हित पूर्णांक offs) अणु
	वापस पढ़ोl(va.vaddr + offs);
पूर्ण

अटल अंतरभूत व्योम mga_ग_लिखोl(vaddr_t va, अचिन्हित पूर्णांक offs, u_पूर्णांक32_t value) अणु
	ग_लिखोl(value, va.vaddr + offs);
पूर्ण

अटल अंतरभूत व्योम mga_स_नकल_toio(vaddr_t va, स्थिर व्योम* src, पूर्णांक len) अणु
#अगर defined(__alpha__) || defined(__i386__) || defined(__x86_64__)
	/*
	 * ioग_लिखो32_rep works क्रम us अगर:
	 *  (1) Copies data as 32bit quantities, not byte after byte,
	 *  (2) Perक्रमms LE ordered stores, and
	 *  (3) It copes with unaligned source (destination is guaranteed to be page
	 *      aligned and length is guaranteed to be multiple of 4).
	 */
	ioग_लिखो32_rep(va.vaddr, src, len >> 2);
#अन्यथा
        u_पूर्णांक32_t __iomem* addr = va.vaddr;

	अगर ((अचिन्हित दीर्घ)src & 3) अणु
		जबतक (len >= 4) अणु
			fb_ग_लिखोl(get_unaligned((u32 *)src), addr);
			addr++;
			len -= 4;
			src += 4;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (len >= 4) अणु
			fb_ग_लिखोl(*(u32 *)src, addr);
			addr++;
			len -= 4;
			src += 4;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम vaddr_add(vaddr_t* va, अचिन्हित दीर्घ offs) अणु
	va->vaddr += offs;
पूर्ण

अटल अंतरभूत व्योम __iomem* vaddr_va(vaddr_t va) अणु
	वापस va.vaddr;
पूर्ण

काष्ठा my_timming अणु
	अचिन्हित पूर्णांक pixघड़ी;
	पूर्णांक mnp;
	अचिन्हित पूर्णांक crtc;
	अचिन्हित पूर्णांक HDisplay;
	अचिन्हित पूर्णांक HSyncStart;
	अचिन्हित पूर्णांक HSyncEnd;
	अचिन्हित पूर्णांक HTotal;
	अचिन्हित पूर्णांक VDisplay;
	अचिन्हित पूर्णांक VSyncStart;
	अचिन्हित पूर्णांक VSyncEnd;
	अचिन्हित पूर्णांक VTotal;
	अचिन्हित पूर्णांक sync;
	पूर्णांक	     dblscan;
	पूर्णांक	     पूर्णांकerlaced;
	अचिन्हित पूर्णांक delay;	/* CRTC delay */
पूर्ण;

क्रमागत अणु M_SYSTEM_PLL, M_PIXEL_PLL_A, M_PIXEL_PLL_B, M_PIXEL_PLL_C, M_VIDEO_PLL पूर्ण;

काष्ठा matrox_pll_cache अणु
	अचिन्हित पूर्णांक	valid;
	काष्ठा अणु
		अचिन्हित पूर्णांक	mnp_key;
		अचिन्हित पूर्णांक	mnp_value;
		      पूर्ण data[4];
पूर्ण;

काष्ठा matrox_pll_limits अणु
	अचिन्हित पूर्णांक	vcomin;
	अचिन्हित पूर्णांक	vcomax;
पूर्ण;

काष्ठा matrox_pll_features अणु
	अचिन्हित पूर्णांक	vco_freq_min;
	अचिन्हित पूर्णांक	ref_freq;
	अचिन्हित पूर्णांक	feed_भाग_min;
	अचिन्हित पूर्णांक	feed_भाग_max;
	अचिन्हित पूर्णांक	in_भाग_min;
	अचिन्हित पूर्णांक	in_भाग_max;
	अचिन्हित पूर्णांक	post_shअगरt_max;
पूर्ण;

काष्ठा matroxfb_par
अणु
	अचिन्हित पूर्णांक	final_bppShअगरt;
	अचिन्हित पूर्णांक	cmap_len;
	काष्ठा अणु
		अचिन्हित पूर्णांक bytes;
		अचिन्हित पूर्णांक pixels;
		अचिन्हित पूर्णांक chunks;
		      पूर्ण ydstorg;
पूर्ण;

काष्ठा matrox_fb_info;

काष्ठा matrox_DAC1064_features अणु
	u_पूर्णांक8_t	xvrefctrl;
	u_पूर्णांक8_t	xmiscctrl;
पूर्ण;

/* current hardware status */
काष्ठा mavenregs अणु
	u_पूर्णांक8_t regs[256];
	पूर्णांक	 mode;
	पूर्णांक	 vlines;
	पूर्णांक	 xtal;
	पूर्णांक	 fv;

	u_पूर्णांक16_t htotal;
	u_पूर्णांक16_t hcorr;
पूर्ण;

काष्ठा matrox_crtc2 अणु
	u_पूर्णांक32_t ctl;
पूर्ण;

काष्ठा matrox_hw_state अणु
	u_पूर्णांक32_t	MXoptionReg;
	अचिन्हित अक्षर	DACclk[6];
	अचिन्हित अक्षर	DACreg[80];
	अचिन्हित अक्षर	MiscOutReg;
	अचिन्हित अक्षर	DACpal[768];
	अचिन्हित अक्षर	CRTC[25];
	अचिन्हित अक्षर	CRTCEXT[9];
	अचिन्हित अक्षर	SEQ[5];
	/* unused क्रम MGA mode, but who knows... */
	अचिन्हित अक्षर	GCTL[9];
	/* unused क्रम MGA mode, but who knows... */
	अचिन्हित अक्षर	ATTR[21];

	/* TVOut only */
	काष्ठा mavenregs	maven;

	काष्ठा matrox_crtc2	crtc2;
पूर्ण;

काष्ठा matrox_accel_data अणु
#अगर_घोषित CONFIG_FB_MATROX_MILLENIUM
	अचिन्हित अक्षर	ramdac_rev;
#पूर्ण_अगर
	u_पूर्णांक32_t	m_dwg_rect;
	u_पूर्णांक32_t	m_opmode;
	u_पूर्णांक32_t	m_access;
	u_पूर्णांक32_t	m_pitch;
पूर्ण;

काष्ठा v4l2_queryctrl;
काष्ठा v4l2_control;

काष्ठा matrox_altout अणु
	स्थिर अक्षर	*name;
	पूर्णांक		(*compute)(व्योम* altout_dev, काष्ठा my_timming* input);
	पूर्णांक		(*program)(व्योम* altout_dev);
	पूर्णांक		(*start)(व्योम* altout_dev);
	पूर्णांक		(*verअगरymode)(व्योम* altout_dev, u_पूर्णांक32_t mode);
	पूर्णांक		(*getqueryctrl)(व्योम* altout_dev,
					काष्ठा v4l2_queryctrl* ctrl);
	पूर्णांक		(*अ_लोtrl)(व्योम* altout_dev, 
				   काष्ठा v4l2_control* ctrl);
	पूर्णांक		(*setctrl)(व्योम* altout_dev, 
				   काष्ठा v4l2_control* ctrl);
पूर्ण;

#घोषणा MATROXFB_SRC_NONE	0
#घोषणा MATROXFB_SRC_CRTC1	1
#घोषणा MATROXFB_SRC_CRTC2	2

क्रमागत mga_chip अणु MGA_2064, MGA_2164, MGA_1064, MGA_1164, MGA_G100, MGA_G200, MGA_G400, MGA_G450, MGA_G550 पूर्ण;

काष्ठा matrox_bios अणु
	अचिन्हित पूर्णांक	bios_valid : 1;
	अचिन्हित पूर्णांक	pins_len;
	अचिन्हित अक्षर	pins[128];
	काष्ठा अणु
		अचिन्हित अक्षर vMaj, vMin, vRev;
		      पूर्ण version;
	काष्ठा अणु
		अचिन्हित अक्षर state, tvout;
		      पूर्ण output;
पूर्ण;

काष्ठा matrox_चयन;
काष्ठा matroxfb_driver;
काष्ठा matroxfb_dh_fb_info;

काष्ठा matrox_vsync अणु
	रुको_queue_head_t	रुको;
	अचिन्हित पूर्णांक		cnt;
पूर्ण;

काष्ठा matrox_fb_info अणु
	काष्ठा fb_info		fbcon;

	काष्ठा list_head	next_fb;

	पूर्णांक			dead;
	पूर्णांक                     initialized;
	अचिन्हित पूर्णांक		usecount;

	अचिन्हित पूर्णांक		userusecount;
	अचिन्हित दीर्घ		irq_flags;

	काष्ठा matroxfb_par	curr;
	काष्ठा matrox_hw_state	hw;

	काष्ठा matrox_accel_data accel;

	काष्ठा pci_dev*		pcidev;

	काष्ठा अणु
		काष्ठा matrox_vsync	vsync;
		अचिन्हित पूर्णांक	pixघड़ी;
		पूर्णांक		mnp;
		पूर्णांक		panpos;
			      पूर्ण crtc1;
	काष्ठा अणु
		काष्ठा matrox_vsync	vsync;
		अचिन्हित पूर्णांक 	pixघड़ी;
		पूर्णांक		mnp;
	काष्ठा matroxfb_dh_fb_info*	info;
	काष्ठा rw_semaphore	lock;
			      पूर्ण crtc2;
	काष्ठा अणु
	काष्ठा rw_semaphore	lock;
	काष्ठा अणु
		पूर्णांक brightness, contrast, saturation, hue, gamma;
		पूर्णांक testout, deflicker;
				पूर्ण tvo_params;
			      पूर्ण altout;
#घोषणा MATROXFB_MAX_OUTPUTS		3
	काष्ठा अणु
	अचिन्हित पूर्णांक		src;
	काष्ठा matrox_altout*	output;
	व्योम*			data;
	अचिन्हित पूर्णांक		mode;
	अचिन्हित पूर्णांक		शेष_src;
			      पूर्ण outमाला_दो[MATROXFB_MAX_OUTPUTS];

#घोषणा MATROXFB_MAX_FB_DRIVERS		5
	काष्ठा matroxfb_driver* (drivers[MATROXFB_MAX_FB_DRIVERS]);
	व्योम*			(drivers_data[MATROXFB_MAX_FB_DRIVERS]);
	अचिन्हित पूर्णांक		drivers_count;

	काष्ठा अणु
	अचिन्हित दीर्घ	base;	/* physical */
	vaddr_t		vbase;	/* CPU view */
	अचिन्हित पूर्णांक	len;
	अचिन्हित पूर्णांक	len_usable;
	अचिन्हित पूर्णांक	len_maximum;
		      पूर्ण video;

	काष्ठा अणु
	अचिन्हित दीर्घ	base;	/* physical */
	vaddr_t		vbase;	/* CPU view */
	अचिन्हित पूर्णांक	len;
		      पूर्ण mmio;

	अचिन्हित पूर्णांक	max_pixel_घड़ी;
	अचिन्हित पूर्णांक	max_pixel_घड़ी_panellink;

	काष्ठा matrox_चयन*	hw_चयन;

	काष्ठा अणु
		काष्ठा matrox_pll_features pll;
		काष्ठा matrox_DAC1064_features DAC1064;
			      पूर्ण features;
	काष्ठा अणु
		spinlock_t	DAC;
		spinlock_t	accel;
			      पूर्ण lock;

	क्रमागत mga_chip		chip;

	पूर्णांक			पूर्णांकerleave;
	पूर्णांक			millenium;
	पूर्णांक			milleniumII;
	काष्ठा अणु
		पूर्णांक		cfb4;
		स्थिर पूर्णांक*	vxres;
		पूर्णांक		cross4MB;
		पूर्णांक		text;
		पूर्णांक		plnwt;
		पूर्णांक		srcorg;
			      पूर्ण capable;
	पूर्णांक			wc_cookie;
	काष्ठा अणु
		पूर्णांक		precise_width;
		पूर्णांक		mga_24bpp_fix;
		पूर्णांक		novga;
		पूर्णांक		nobios;
		पूर्णांक		nopciretry;
		पूर्णांक		noinit;
		पूर्णांक		sgram;
		पूर्णांक		support32MB;

		पूर्णांक		accelerator;
		पूर्णांक		text_type_aux;
		पूर्णांक		video64bits;
		पूर्णांक		crtc2;
		पूर्णांक		maven_capable;
		अचिन्हित पूर्णांक	vgastep;
		अचिन्हित पूर्णांक	texपंचांगode;
		अचिन्हित पूर्णांक	textstep;
		अचिन्हित पूर्णांक	textvram;	/* अक्षरacter cells */
		अचिन्हित पूर्णांक	ydstorg;	/* offset in bytes from video start to usable memory */
						/* 0 except क्रम 6MB Millenium */
		पूर्णांक		memtype;
		पूर्णांक		g450dac;
		पूर्णांक		dfp_type;
		पूर्णांक		panellink;	/* G400 DFP possible (not G450/G550) */
		पूर्णांक		dualhead;
		अचिन्हित पूर्णांक	fbResource;
			      पूर्ण devflags;
	काष्ठा fb_ops		fbops;
	काष्ठा matrox_bios	bios;
	काष्ठा अणु
		काष्ठा matrox_pll_limits	pixel;
		काष्ठा matrox_pll_limits	प्रणाली;
		काष्ठा matrox_pll_limits	video;
			      पूर्ण limits;
	काष्ठा अणु
		काष्ठा matrox_pll_cache	pixel;
		काष्ठा matrox_pll_cache	प्रणाली;
		काष्ठा matrox_pll_cache	video;
				      पूर्ण cache;
	काष्ठा अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक	video;
			अचिन्हित पूर्णांक	प्रणाली;
				      पूर्ण pll;
		काष्ठा अणु
			u_पूर्णांक32_t	opt;
			u_पूर्णांक32_t	opt2;
			u_पूर्णांक32_t	opt3;
			u_पूर्णांक32_t	mctlwtst;
			u_पूर्णांक32_t	mctlwtst_core;
			u_पूर्णांक32_t	memmisc;
			u_पूर्णांक32_t	memrdbk;
			u_पूर्णांक32_t	maccess;
				      पूर्ण reg;
		काष्ठा अणु
			अचिन्हित पूर्णांक	ddr:1,
			                emrswen:1,
					dll:1;
				      पूर्ण memory;
			      पूर्ण values;
	u_पूर्णांक32_t cmap[16];
पूर्ण;

#घोषणा info2minfo(info) container_of(info, काष्ठा matrox_fb_info, fbcon)

काष्ठा matrox_चयन अणु
	पूर्णांक	(*preinit)(काष्ठा matrox_fb_info *minfo);
	व्योम	(*reset)(काष्ठा matrox_fb_info *minfo);
	पूर्णांक	(*init)(काष्ठा matrox_fb_info *minfo, काष्ठा my_timming*);
	व्योम	(*restore)(काष्ठा matrox_fb_info *minfo);
पूर्ण;

काष्ठा matroxfb_driver अणु
	काष्ठा list_head	node;
	अक्षर*			name;
	व्योम*			(*probe)(काष्ठा matrox_fb_info* info);
	व्योम			(*हटाओ)(काष्ठा matrox_fb_info* info, व्योम* data);
पूर्ण;

पूर्णांक matroxfb_रेजिस्टर_driver(काष्ठा matroxfb_driver* drv);
व्योम matroxfb_unरेजिस्टर_driver(काष्ठा matroxfb_driver* drv);

#घोषणा PCI_OPTION_REG	0x40
#घोषणा   PCI_OPTION_ENABLE_ROM		0x40000000

#घोषणा PCI_MGA_INDEX	0x44
#घोषणा PCI_MGA_DATA	0x48
#घोषणा PCI_OPTION2_REG	0x50
#घोषणा PCI_OPTION3_REG	0x54
#घोषणा PCI_MEMMISC_REG	0x58

#घोषणा M_DWGCTL	0x1C00
#घोषणा M_MACCESS	0x1C04
#घोषणा M_CTLWTST	0x1C08

#घोषणा M_PLNWT		0x1C1C

#घोषणा M_BCOL		0x1C20
#घोषणा M_FCOL		0x1C24

#घोषणा M_SGN		0x1C58
#घोषणा M_LEN		0x1C5C
#घोषणा M_AR0		0x1C60
#घोषणा M_AR1		0x1C64
#घोषणा M_AR2		0x1C68
#घोषणा M_AR3		0x1C6C
#घोषणा M_AR4		0x1C70
#घोषणा M_AR5		0x1C74
#घोषणा M_AR6		0x1C78

#घोषणा M_CXBNDRY	0x1C80
#घोषणा M_FXBNDRY	0x1C84
#घोषणा M_YDSTLEN	0x1C88
#घोषणा M_PITCH		0x1C8C
#घोषणा M_YDST		0x1C90
#घोषणा M_YDSTORG	0x1C94
#घोषणा M_YTOP		0x1C98
#घोषणा M_YBOT		0x1C9C

/* mystique only */
#घोषणा M_CACHEFLUSH	0x1FFF

#घोषणा M_EXEC		0x0100

#घोषणा M_DWG_TRAP	0x04
#घोषणा M_DWG_BITBLT	0x08
#घोषणा M_DWG_ILOAD	0x09

#घोषणा M_DWG_LINEAR	0x0080
#घोषणा M_DWG_SOLID	0x0800
#घोषणा M_DWG_ARZERO	0x1000
#घोषणा M_DWG_SGNZERO	0x2000
#घोषणा M_DWG_SHIFTZERO	0x4000

#घोषणा M_DWG_REPLACE	0x000C0000
#घोषणा M_DWG_REPLACE2	(M_DWG_REPLACE | 0x40)
#घोषणा M_DWG_XOR	0x00060010

#घोषणा M_DWG_BFCOL	0x04000000
#घोषणा M_DWG_BMONOWF	0x08000000

#घोषणा M_DWG_TRANSC	0x40000000

#घोषणा M_FIFOSTATUS	0x1E10
#घोषणा M_STATUS	0x1E14
#घोषणा M_ICLEAR	0x1E18
#घोषणा M_IEN		0x1E1C

#घोषणा M_VCOUNT	0x1E20

#घोषणा M_RESET		0x1E40
#घोषणा M_MEMRDBK	0x1E44

#घोषणा M_AGP2PLL	0x1E4C

#घोषणा M_OPMODE	0x1E54
#घोषणा     M_OPMODE_DMA_GEN_WRITE	0x00
#घोषणा     M_OPMODE_DMA_BLIT		0x04
#घोषणा     M_OPMODE_DMA_VECTOR_WRITE	0x08
#घोषणा     M_OPMODE_DMA_LE		0x0000		/* little endian - no transक्रमmation */
#घोषणा     M_OPMODE_DMA_BE_8BPP	0x0000
#घोषणा     M_OPMODE_DMA_BE_16BPP	0x0100
#घोषणा     M_OPMODE_DMA_BE_32BPP	0x0200
#घोषणा     M_OPMODE_सूची_LE		0x000000	/* little endian - no transक्रमmation */
#घोषणा     M_OPMODE_सूची_BE_8BPP	0x000000
#घोषणा     M_OPMODE_सूची_BE_16BPP	0x010000
#घोषणा     M_OPMODE_सूची_BE_32BPP	0x020000

#घोषणा M_ATTR_INDEX	0x1FC0
#घोषणा M_ATTR_DATA	0x1FC1

#घोषणा M_MISC_REG	0x1FC2
#घोषणा M_3C2_RD	0x1FC2

#घोषणा M_SEQ_INDEX	0x1FC4
#घोषणा M_SEQ_DATA	0x1FC5
#घोषणा     M_SEQ1		0x01
#घोषणा        M_SEQ1_SCROFF		0x20

#घोषणा M_MISC_REG_READ	0x1FCC

#घोषणा M_GRAPHICS_INDEX 0x1FCE
#घोषणा M_GRAPHICS_DATA	0x1FCF

#घोषणा M_CRTC_INDEX	0x1FD4

#घोषणा M_ATTR_RESET	0x1FDA
#घोषणा M_3DA_WR	0x1FDA
#घोषणा M_INSTS1	0x1FDA

#घोषणा M_EXTVGA_INDEX	0x1FDE
#घोषणा M_EXTVGA_DATA	0x1FDF

/* G200 only */
#घोषणा M_SRCORG	0x2CB4
#घोषणा M_DSTORG	0x2CB8

#घोषणा M_RAMDAC_BASE	0x3C00

/* क्रमtunately, same on TVP3026 and MGA1064 */
#घोषणा M_DAC_REG	(M_RAMDAC_BASE+0)
#घोषणा M_DAC_VAL	(M_RAMDAC_BASE+1)
#घोषणा M_PALETTE_MASK	(M_RAMDAC_BASE+2)

#घोषणा M_X_INDEX	0x00
#घोषणा M_X_DATAREG	0x0A

#घोषणा DAC_XGENIOCTRL		0x2A
#घोषणा DAC_XGENIODATA		0x2B

#घोषणा M_C2CTL		0x3C10

#घोषणा MX_OPTION_BSWAP         0x00000000

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा M_OPMODE_4BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_LE | M_OPMODE_DMA_BLIT)
#घोषणा M_OPMODE_8BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_LE | M_OPMODE_DMA_BLIT)
#घोषणा M_OPMODE_16BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_LE | M_OPMODE_DMA_BLIT)
#घोषणा M_OPMODE_24BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_LE | M_OPMODE_DMA_BLIT)
#घोषणा M_OPMODE_32BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_LE | M_OPMODE_DMA_BLIT)
#अन्यथा
#अगर_घोषित __BIG_ENDIAN
#घोषणा M_OPMODE_4BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_LE       | M_OPMODE_DMA_BLIT)	/* TODO */
#घोषणा M_OPMODE_8BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_BE_8BPP  | M_OPMODE_DMA_BLIT)
#घोषणा M_OPMODE_16BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_BE_16BPP | M_OPMODE_DMA_BLIT)
#घोषणा M_OPMODE_24BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_BE_8BPP  | M_OPMODE_DMA_BLIT)	/* TODO, ?32 */
#घोषणा M_OPMODE_32BPP	(M_OPMODE_DMA_LE | M_OPMODE_सूची_BE_32BPP | M_OPMODE_DMA_BLIT)
#अन्यथा
#त्रुटि "Byte ordering have to be defined. Cannot continue."
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा mga_inb(addr)		mga_पढ़ोb(minfo->mmio.vbase, (addr))
#घोषणा mga_inl(addr)		mga_पढ़ोl(minfo->mmio.vbase, (addr))
#घोषणा mga_outb(addr,val)	mga_ग_लिखोb(minfo->mmio.vbase, (addr), (val))
#घोषणा mga_outw(addr,val)	mga_ग_लिखोw(minfo->mmio.vbase, (addr), (val))
#घोषणा mga_outl(addr,val)	mga_ग_लिखोl(minfo->mmio.vbase, (addr), (val))
#घोषणा mga_पढ़ोr(port,idx)	(mga_outb((port),(idx)), mga_inb((port)+1))
#घोषणा mga_setr(addr,port,val)	mga_outw(addr, ((val)<<8) | (port))

#घोषणा mga_fअगरo(n)	करो अणुपूर्ण जबतक ((mga_inl(M_FIFOSTATUS) & 0xFF) < (n))

#घोषणा WaitTillIdle()	करो अणु mga_inl(M_STATUS); करो अणुपूर्ण जबतक (mga_inl(M_STATUS) & 0x10000); पूर्ण जबतक (0)

/* code speedup */
#अगर_घोषित CONFIG_FB_MATROX_MILLENIUM
#घोषणा isInterleave(x)	 (x->पूर्णांकerleave)
#घोषणा isMillenium(x)	 (x->millenium)
#घोषणा isMilleniumII(x) (x->milleniumII)
#अन्यथा
#घोषणा isInterleave(x)  (0)
#घोषणा isMillenium(x)	 (0)
#घोषणा isMilleniumII(x) (0)
#पूर्ण_अगर

#घोषणा matroxfb_DAC_lock()                   spin_lock(&minfo->lock.DAC)
#घोषणा matroxfb_DAC_unlock()                 spin_unlock(&minfo->lock.DAC)
#घोषणा matroxfb_DAC_lock_irqsave(flags)      spin_lock_irqsave(&minfo->lock.DAC, flags)
#घोषणा matroxfb_DAC_unlock_irqrestore(flags) spin_unlock_irqrestore(&minfo->lock.DAC, flags)
बाह्य व्योम matroxfb_DAC_out(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक reg,
			     पूर्णांक val);
बाह्य पूर्णांक matroxfb_DAC_in(स्थिर काष्ठा matrox_fb_info *minfo, पूर्णांक reg);
बाह्य व्योम matroxfb_var2my(काष्ठा fb_var_screeninfo* fvsi, काष्ठा my_timming* mt);
बाह्य पूर्णांक matroxfb_रुको_क्रम_sync(काष्ठा matrox_fb_info *minfo, u_पूर्णांक32_t crtc);
बाह्य पूर्णांक matroxfb_enable_irq(काष्ठा matrox_fb_info *minfo, पूर्णांक reenable);

#अगर_घोषित MATROXFB_USE_SPINLOCKS
#घोषणा CRITBEGIN  spin_lock_irqsave(&minfo->lock.accel, critflags);
#घोषणा CRITEND	   spin_unlock_irqrestore(&minfo->lock.accel, critflags);
#घोषणा CRITFLAGS  अचिन्हित दीर्घ critflags;
#अन्यथा
#घोषणा CRITBEGIN
#घोषणा CRITEND
#घोषणा CRITFLAGS
#पूर्ण_अगर

#पूर्ण_अगर	/* __MATROXFB_H__ */
