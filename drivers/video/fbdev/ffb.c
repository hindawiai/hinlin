<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ffb.c: Creator/Elite3D frame buffer driver
 *
 * Copyright (C) 2003, 2006 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997,1998,1999 Jakub Jelinek (jj@ultra.linux.cz)
 *
 * Driver layout based loosely on tgafb.c, see that file क्रम credits.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>
#समावेश <linux/mm.h>
#समावेश <linux/समयr.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/upa.h>
#समावेश <यंत्र/fbपन.स>

#समावेश "sbuslib.h"

/*
 * Local functions.
 */

अटल पूर्णांक ffb_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			 अचिन्हित, काष्ठा fb_info *);
अटल पूर्णांक ffb_blank(पूर्णांक, काष्ठा fb_info *);

अटल व्योम ffb_imageblit(काष्ठा fb_info *, स्थिर काष्ठा fb_image *);
अटल व्योम ffb_fillrect(काष्ठा fb_info *, स्थिर काष्ठा fb_fillrect *);
अटल व्योम ffb_copyarea(काष्ठा fb_info *, स्थिर काष्ठा fb_copyarea *);
अटल पूर्णांक ffb_sync(काष्ठा fb_info *);
अटल पूर्णांक ffb_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक ffb_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल पूर्णांक ffb_pan_display(काष्ठा fb_var_screeninfo *, काष्ठा fb_info *);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops ffb_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= ffb_setcolreg,
	.fb_blank		= ffb_blank,
	.fb_pan_display		= ffb_pan_display,
	.fb_fillrect		= ffb_fillrect,
	.fb_copyarea		= ffb_copyarea,
	.fb_imageblit		= ffb_imageblit,
	.fb_sync		= ffb_sync,
	.fb_mmap		= ffb_mmap,
	.fb_ioctl		= ffb_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

/* Register layout and definitions */
#घोषणा	FFB_SFB8R_VOFF		0x00000000
#घोषणा	FFB_SFB8G_VOFF		0x00400000
#घोषणा	FFB_SFB8B_VOFF		0x00800000
#घोषणा	FFB_SFB8X_VOFF		0x00c00000
#घोषणा	FFB_SFB32_VOFF		0x01000000
#घोषणा	FFB_SFB64_VOFF		0x02000000
#घोषणा	FFB_FBC_REGS_VOFF	0x04000000
#घोषणा	FFB_BM_FBC_REGS_VOFF	0x04002000
#घोषणा	FFB_DFB8R_VOFF		0x04004000
#घोषणा	FFB_DFB8G_VOFF		0x04404000
#घोषणा	FFB_DFB8B_VOFF		0x04804000
#घोषणा	FFB_DFB8X_VOFF		0x04c04000
#घोषणा	FFB_DFB24_VOFF		0x05004000
#घोषणा	FFB_DFB32_VOFF		0x06004000
#घोषणा	FFB_DFB422A_VOFF	0x07004000	/* DFB 422 mode ग_लिखो to A */
#घोषणा	FFB_DFB422AD_VOFF	0x07804000	/* DFB 422 mode with line करोubling */
#घोषणा	FFB_DFB24B_VOFF		0x08004000	/* DFB 24bit mode ग_लिखो to B */
#घोषणा	FFB_DFB422B_VOFF	0x09004000	/* DFB 422 mode ग_लिखो to B */
#घोषणा	FFB_DFB422BD_VOFF	0x09804000	/* DFB 422 mode with line करोubling */
#घोषणा	FFB_SFB16Z_VOFF		0x0a004000	/* 16bit mode Z planes */
#घोषणा	FFB_SFB8Z_VOFF		0x0a404000	/* 8bit mode Z planes */
#घोषणा	FFB_SFB422_VOFF		0x0ac04000	/* SFB 422 mode ग_लिखो to A/B */
#घोषणा	FFB_SFB422D_VOFF	0x0b404000	/* SFB 422 mode with line करोubling */
#घोषणा	FFB_FBC_KREGS_VOFF	0x0bc04000
#घोषणा	FFB_DAC_VOFF		0x0bc06000
#घोषणा	FFB_PROM_VOFF		0x0bc08000
#घोषणा	FFB_EXP_VOFF		0x0bc18000

#घोषणा	FFB_SFB8R_POFF		0x04000000UL
#घोषणा	FFB_SFB8G_POFF		0x04400000UL
#घोषणा	FFB_SFB8B_POFF		0x04800000UL
#घोषणा	FFB_SFB8X_POFF		0x04c00000UL
#घोषणा	FFB_SFB32_POFF		0x05000000UL
#घोषणा	FFB_SFB64_POFF		0x06000000UL
#घोषणा	FFB_FBC_REGS_POFF	0x00600000UL
#घोषणा	FFB_BM_FBC_REGS_POFF	0x00600000UL
#घोषणा	FFB_DFB8R_POFF		0x01000000UL
#घोषणा	FFB_DFB8G_POFF		0x01400000UL
#घोषणा	FFB_DFB8B_POFF		0x01800000UL
#घोषणा	FFB_DFB8X_POFF		0x01c00000UL
#घोषणा	FFB_DFB24_POFF		0x02000000UL
#घोषणा	FFB_DFB32_POFF		0x03000000UL
#घोषणा	FFB_FBC_KREGS_POFF	0x00610000UL
#घोषणा	FFB_DAC_POFF		0x00400000UL
#घोषणा	FFB_PROM_POFF		0x00000000UL
#घोषणा	FFB_EXP_POFF		0x00200000UL
#घोषणा FFB_DFB422A_POFF	0x09000000UL
#घोषणा FFB_DFB422AD_POFF	0x09800000UL
#घोषणा FFB_DFB24B_POFF		0x0a000000UL
#घोषणा FFB_DFB422B_POFF	0x0b000000UL
#घोषणा FFB_DFB422BD_POFF	0x0b800000UL
#घोषणा FFB_SFB16Z_POFF		0x0c800000UL
#घोषणा FFB_SFB8Z_POFF		0x0c000000UL
#घोषणा FFB_SFB422_POFF		0x0d000000UL
#घोषणा FFB_SFB422D_POFF	0x0d800000UL

/* Draw operations */
#घोषणा FFB_DRAWOP_DOT		0x00
#घोषणा FFB_DRAWOP_AADOT	0x01
#घोषणा FFB_DRAWOP_BRLINECAP	0x02
#घोषणा FFB_DRAWOP_BRLINEOPEN	0x03
#घोषणा FFB_DRAWOP_DDLINE	0x04
#घोषणा FFB_DRAWOP_AALINE	0x05
#घोषणा FFB_DRAWOP_TRIANGLE	0x06
#घोषणा FFB_DRAWOP_POLYGON	0x07
#घोषणा FFB_DRAWOP_RECTANGLE	0x08
#घोषणा FFB_DRAWOP_FASTFILL	0x09
#घोषणा FFB_DRAWOP_BCOPY	0x0a
#घोषणा FFB_DRAWOP_VSCROLL	0x0b

/* Pixel processor control */
/* Force WID */
#घोषणा FFB_PPC_FW_DISABLE	0x800000
#घोषणा FFB_PPC_FW_ENABLE	0xc00000
/* Auxiliary clip */
#घोषणा FFB_PPC_ACE_DISABLE	0x040000
#घोषणा FFB_PPC_ACE_AUX_SUB	0x080000
#घोषणा FFB_PPC_ACE_AUX_ADD	0x0c0000
/* Depth cue */
#घोषणा FFB_PPC_DCE_DISABLE	0x020000
#घोषणा FFB_PPC_DCE_ENABLE	0x030000
/* Alpha blend */
#घोषणा FFB_PPC_ABE_DISABLE	0x008000
#घोषणा FFB_PPC_ABE_ENABLE	0x00c000
/* View clip */
#घोषणा FFB_PPC_VCE_DISABLE	0x001000
#घोषणा FFB_PPC_VCE_2D		0x002000
#घोषणा FFB_PPC_VCE_3D		0x003000
/* Area pattern */
#घोषणा FFB_PPC_APE_DISABLE	0x000800
#घोषणा FFB_PPC_APE_ENABLE	0x000c00
/* Transparent background */
#घोषणा FFB_PPC_TBE_OPAQUE	0x000200
#घोषणा FFB_PPC_TBE_TRANSPARENT	0x000300
/* Z source */
#घोषणा FFB_PPC_ZS_VAR		0x000080
#घोषणा FFB_PPC_ZS_CONST	0x0000c0
/* Y source */
#घोषणा FFB_PPC_YS_VAR		0x000020
#घोषणा FFB_PPC_YS_CONST	0x000030
/* X source */
#घोषणा FFB_PPC_XS_WID		0x000004
#घोषणा FFB_PPC_XS_VAR		0x000008
#घोषणा FFB_PPC_XS_CONST	0x00000c
/* Color (BGR) source */
#घोषणा FFB_PPC_CS_VAR		0x000002
#घोषणा FFB_PPC_CS_CONST	0x000003

#घोषणा FFB_ROP_NEW		0x83
#घोषणा FFB_ROP_OLD		0x85
#घोषणा FFB_ROP_NEW_XOR_OLD	0x86

#घोषणा FFB_UCSR_FIFO_MASK	0x00000fff
#घोषणा FFB_UCSR_FB_BUSY	0x01000000
#घोषणा FFB_UCSR_RP_BUSY	0x02000000
#घोषणा FFB_UCSR_ALL_BUSY	(FFB_UCSR_RP_BUSY|FFB_UCSR_FB_BUSY)
#घोषणा FFB_UCSR_READ_ERR	0x40000000
#घोषणा FFB_UCSR_FIFO_OVFL	0x80000000
#घोषणा FFB_UCSR_ALL_ERRORS	(FFB_UCSR_READ_ERR|FFB_UCSR_FIFO_OVFL)

काष्ठा ffb_fbc अणु
	/* Next vertex रेजिस्टरs */
	u32	xxx1[3];
	u32	alpha;
	u32	red;
	u32	green;
	u32	blue;
	u32	depth;
	u32	y;
	u32	x;
	u32	xxx2[2];
	u32	ryf;
	u32	rxf;
	u32	xxx3[2];

	u32	dmyf;
	u32	dmxf;
	u32	xxx4[2];
	u32	ebyi;
	u32	ebxi;
	u32	xxx5[2];
	u32	by;
	u32	bx;
	u32	dy;
	u32	dx;
	u32	bh;
	u32	bw;
	u32	xxx6[2];

	u32	xxx7[32];

	/* Setup unit vertex state रेजिस्टर */
	u32	suvtx;
	u32	xxx8[63];

	/* Control रेजिस्टरs */
	u32	ppc;
	u32	wid;
	u32	fg;
	u32	bg;
	u32	स्थिरy;
	u32	स्थिरz;
	u32	xclip;
	u32	dcss;
	u32	vclipmin;
	u32	vclipmax;
	u32	vclipzmin;
	u32	vclipzmax;
	u32	dcsf;
	u32	dcsb;
	u32	dczf;
	u32	dczb;

	u32	xxx9;
	u32	blendc;
	u32	blendc1;
	u32	blendc2;
	u32	fbramitc;
	u32	fbc;
	u32	rop;
	u32	cmp;
	u32	matchab;
	u32	matchc;
	u32	magnab;
	u32	magnc;
	u32	fbcfg0;
	u32	fbcfg1;
	u32	fbcfg2;
	u32	fbcfg3;

	u32	ppcfg;
	u32	pick;
	u32	fillmode;
	u32	fbramwac;
	u32	pmask;
	u32	xpmask;
	u32	ypmask;
	u32	zpmask;
	u32	clip0min;
	u32	clip0max;
	u32	clip1min;
	u32	clip1max;
	u32	clip2min;
	u32	clip2max;
	u32	clip3min;
	u32	clip3max;

	/* New 3dRAM III support regs */
	u32	rawblend2;
	u32	rawpreblend;
	u32	rawstencil;
	u32	rawstencilctl;
	u32	threedram1;
	u32	threedram2;
	u32	passin;
	u32	rawclrdepth;
	u32	rawpmask;
	u32	rawcsrc;
	u32	rawmatch;
	u32	rawmagn;
	u32	rawropblend;
	u32	rawcmp;
	u32	rawwac;
	u32	fbramid;

	u32	drawop;
	u32	xxx10[2];
	u32	fontlpat;
	u32	xxx11;
	u32	fontxy;
	u32	fontw;
	u32	fontinc;
	u32	font;
	u32	xxx12[3];
	u32	blend2;
	u32	preblend;
	u32	stencil;
	u32	stencilctl;

	u32	xxx13[4];
	u32	dcss1;
	u32	dcss2;
	u32	dcss3;
	u32	widpmask;
	u32	dcs2;
	u32	dcs3;
	u32	dcs4;
	u32	xxx14;
	u32	dcd2;
	u32	dcd3;
	u32	dcd4;
	u32	xxx15;

	u32	pattern[32];

	u32	xxx16[256];

	u32	devid;
	u32	xxx17[63];

	u32	ucsr;
	u32	xxx18[31];

	u32	mer;
पूर्ण;

काष्ठा ffb_dac अणु
	u32	type;
	u32	value;
	u32	type2;
	u32	value2;
पूर्ण;

#घोषणा FFB_DAC_UCTRL		0x1001 /* User Control */
#घोषणा FFB_DAC_UCTRL_MANREV	0x00000f00 /* 4-bit Manufacturing Revision */
#घोषणा FFB_DAC_UCTRL_MANREV_SHIFT 8
#घोषणा FFB_DAC_TGEN		0x6000 /* Timing Generator */
#घोषणा FFB_DAC_TGEN_VIDE	0x00000001 /* Video Enable */
#घोषणा FFB_DAC_DID		0x8000 /* Device Identअगरication */
#घोषणा FFB_DAC_DID_PNUM	0x0ffff000 /* Device Part Number */
#घोषणा FFB_DAC_DID_PNUM_SHIFT	12
#घोषणा FFB_DAC_DID_REV		0xf0000000 /* Device Revision */
#घोषणा FFB_DAC_DID_REV_SHIFT	28

#घोषणा FFB_DAC_CUR_CTRL	0x100
#घोषणा FFB_DAC_CUR_CTRL_P0	0x00000001
#घोषणा FFB_DAC_CUR_CTRL_P1	0x00000002

काष्ठा ffb_par अणु
	spinlock_t		lock;
	काष्ठा ffb_fbc __iomem	*fbc;
	काष्ठा ffb_dac __iomem	*dac;

	u32			flags;
#घोषणा FFB_FLAG_AFB		0x00000001 /* AFB m3 or m6 */
#घोषणा FFB_FLAG_BLANKED	0x00000002 /* screen is blanked */
#घोषणा FFB_FLAG_INVCURSOR	0x00000004 /* DAC has inverted cursor logic */

	u32			fg_cache __attribute__((aligned (8)));
	u32			bg_cache;
	u32			rop_cache;

	पूर्णांक			fअगरo_cache;

	अचिन्हित दीर्घ		physbase;
	अचिन्हित दीर्घ		fbsize;

	पूर्णांक			board_type;

	u32			pseuकरो_palette[16];
पूर्ण;

अटल व्योम FFBFअगरo(काष्ठा ffb_par *par, पूर्णांक n)
अणु
	काष्ठा ffb_fbc __iomem *fbc;
	पूर्णांक cache = par->fअगरo_cache;

	अगर (cache - n < 0) अणु
		fbc = par->fbc;
		करो अणु
			cache = (upa_पढ़ोl(&fbc->ucsr) & FFB_UCSR_FIFO_MASK);
			cache -= 8;
		पूर्ण जबतक (cache - n < 0);
	पूर्ण
	par->fअगरo_cache = cache - n;
पूर्ण

अटल व्योम FFBWait(काष्ठा ffb_par *par)
अणु
	काष्ठा ffb_fbc __iomem *fbc;
	पूर्णांक limit = 10000;

	fbc = par->fbc;
	करो अणु
		अगर ((upa_पढ़ोl(&fbc->ucsr) & FFB_UCSR_ALL_BUSY) == 0)
			अवरोध;
		अगर ((upa_पढ़ोl(&fbc->ucsr) & FFB_UCSR_ALL_ERRORS) != 0) अणु
			upa_ग_लिखोl(FFB_UCSR_ALL_ERRORS, &fbc->ucsr);
		पूर्ण
		udelay(10);
	पूर्ण जबतक (--limit > 0);
पूर्ण

अटल पूर्णांक ffb_sync(काष्ठा fb_info *p)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)p->par;

	FFBWait(par);
	वापस 0;
पूर्ण

अटल __अंतरभूत__ व्योम ffb_rop(काष्ठा ffb_par *par, u32 rop)
अणु
	अगर (par->rop_cache != rop) अणु
		FFBFअगरo(par, 1);
		upa_ग_लिखोl(rop, &par->fbc->rop);
		par->rop_cache = rop;
	पूर्ण
पूर्ण

अटल व्योम ffb_चयन_from_graph(काष्ठा ffb_par *par)
अणु
	काष्ठा ffb_fbc __iomem *fbc = par->fbc;
	काष्ठा ffb_dac __iomem *dac = par->dac;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&par->lock, flags);
	FFBWait(par);
	par->fअगरo_cache = 0;
	FFBFअगरo(par, 7);
	upa_ग_लिखोl(FFB_PPC_VCE_DISABLE | FFB_PPC_TBE_OPAQUE |
		   FFB_PPC_APE_DISABLE | FFB_PPC_CS_CONST,
		   &fbc->ppc);
	upa_ग_लिखोl(0x2000707f, &fbc->fbc);
	upa_ग_लिखोl(par->rop_cache, &fbc->rop);
	upa_ग_लिखोl(0xffffffff, &fbc->pmask);
	upa_ग_लिखोl((1 << 16) | (0 << 0), &fbc->fontinc);
	upa_ग_लिखोl(par->fg_cache, &fbc->fg);
	upa_ग_लिखोl(par->bg_cache, &fbc->bg);
	FFBWait(par);

	/* Disable cursor.  */
	upa_ग_लिखोl(FFB_DAC_CUR_CTRL, &dac->type2);
	अगर (par->flags & FFB_FLAG_INVCURSOR)
		upa_ग_लिखोl(0, &dac->value2);
	अन्यथा
		upa_ग_लिखोl((FFB_DAC_CUR_CTRL_P0 |
			    FFB_DAC_CUR_CTRL_P1), &dac->value2);

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

अटल पूर्णांक ffb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;

	/* We just use this to catch चयनes out of
	 * graphics mode.
	 */
	ffb_चयन_from_graph(par);

	अगर (var->xoffset || var->yoffset || var->vmode)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 *	ffb_fillrect - Draws a rectangle on the screen.
 *
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@rect: काष्ठाure defining the rectagle and operation.
 */
अटल व्योम ffb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;
	काष्ठा ffb_fbc __iomem *fbc = par->fbc;
	अचिन्हित दीर्घ flags;
	u32 fg;

	BUG_ON(rect->rop != ROP_COPY && rect->rop != ROP_XOR);

	fg = ((u32 *)info->pseuकरो_palette)[rect->color];

	spin_lock_irqsave(&par->lock, flags);

	अगर (fg != par->fg_cache) अणु
		FFBFअगरo(par, 1);
		upa_ग_लिखोl(fg, &fbc->fg);
		par->fg_cache = fg;
	पूर्ण

	ffb_rop(par, rect->rop == ROP_COPY ?
		     FFB_ROP_NEW :
		     FFB_ROP_NEW_XOR_OLD);

	FFBFअगरo(par, 5);
	upa_ग_लिखोl(FFB_DRAWOP_RECTANGLE, &fbc->drawop);
	upa_ग_लिखोl(rect->dy, &fbc->by);
	upa_ग_लिखोl(rect->dx, &fbc->bx);
	upa_ग_लिखोl(rect->height, &fbc->bh);
	upa_ग_लिखोl(rect->width, &fbc->bw);

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

/**
 *	ffb_copyarea - Copies on area of the screen to another area.
 *
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@area: काष्ठाure defining the source and destination.
 */

अटल व्योम ffb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;
	काष्ठा ffb_fbc __iomem *fbc = par->fbc;
	अचिन्हित दीर्घ flags;

	अगर (area->dx != area->sx ||
	    area->dy == area->sy) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	spin_lock_irqsave(&par->lock, flags);

	ffb_rop(par, FFB_ROP_OLD);

	FFBFअगरo(par, 7);
	upa_ग_लिखोl(FFB_DRAWOP_VSCROLL, &fbc->drawop);
	upa_ग_लिखोl(area->sy, &fbc->by);
	upa_ग_लिखोl(area->sx, &fbc->bx);
	upa_ग_लिखोl(area->dy, &fbc->dy);
	upa_ग_लिखोl(area->dx, &fbc->dx);
	upa_ग_लिखोl(area->height, &fbc->bh);
	upa_ग_लिखोl(area->width, &fbc->bw);

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

/**
 *	ffb_imageblit - Copies a image from प्रणाली memory to the screen.
 *
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@image: काष्ठाure defining the image.
 */
अटल व्योम ffb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;
	काष्ठा ffb_fbc __iomem *fbc = par->fbc;
	स्थिर u8 *data = image->data;
	अचिन्हित दीर्घ flags;
	u32 fg, bg, xy;
	u64 fgbg;
	पूर्णांक i, width, stride;

	अगर (image->depth > 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	fg = ((u32 *)info->pseuकरो_palette)[image->fg_color];
	bg = ((u32 *)info->pseuकरो_palette)[image->bg_color];
	fgbg = ((u64) fg << 32) | (u64) bg;
	xy = (image->dy << 16) | image->dx;
	width = image->width;
	stride = ((width + 7) >> 3);

	spin_lock_irqsave(&par->lock, flags);

	अगर (fgbg != *(u64 *)&par->fg_cache) अणु
		FFBFअगरo(par, 2);
		upa_ग_लिखोq(fgbg, &fbc->fg);
		*(u64 *)&par->fg_cache = fgbg;
	पूर्ण

	अगर (width >= 32) अणु
		FFBFअगरo(par, 1);
		upa_ग_लिखोl(32, &fbc->fontw);
	पूर्ण

	जबतक (width >= 32) अणु
		स्थिर u8 *next_data = data + 4;

		FFBFअगरo(par, 1);
		upa_ग_लिखोl(xy, &fbc->fontxy);
		xy += (32 << 0);

		क्रम (i = 0; i < image->height; i++) अणु
			u32 val = (((u32)data[0] << 24) |
				   ((u32)data[1] << 16) |
				   ((u32)data[2] <<  8) |
				   ((u32)data[3] <<  0));
			FFBFअगरo(par, 1);
			upa_ग_लिखोl(val, &fbc->font);

			data += stride;
		पूर्ण

		data = next_data;
		width -= 32;
	पूर्ण

	अगर (width) अणु
		FFBFअगरo(par, 2);
		upa_ग_लिखोl(width, &fbc->fontw);
		upa_ग_लिखोl(xy, &fbc->fontxy);

		क्रम (i = 0; i < image->height; i++) अणु
			u32 val = (((u32)data[0] << 24) |
				   ((u32)data[1] << 16) |
				   ((u32)data[2] <<  8) |
				   ((u32)data[3] <<  0));
			FFBFअगरo(par, 1);
			upa_ग_लिखोl(val, &fbc->font);

			data += stride;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

अटल व्योम ffb_fixup_var_rgb(काष्ठा fb_var_screeninfo *var)
अणु
	var->red.offset = 0;
	var->red.length = 8;
	var->green.offset = 8;
	var->green.length = 8;
	var->blue.offset = 16;
	var->blue.length = 8;
	var->transp.offset = 0;
	var->transp.length = 0;
पूर्ण

/**
 *	ffb_setcolreg - Sets a color रेजिस्टर.
 *
 *	@regno: boolean, 0 copy local, 1 get_user() function
 *	@red: frame buffer colormap काष्ठाure
 *	@green: The green value which can be up to 16 bits wide
 *	@blue:  The blue value which can be up to 16 bits wide.
 *	@transp: If supported the alpha value which can be up to 16 bits wide.
 *	@info: frame buffer info काष्ठाure
 */
अटल पूर्णांक ffb_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	u32 value;

	अगर (regno >= 16)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	value = (blue << 16) | (green << 8) | red;
	((u32 *)info->pseuकरो_palette)[regno] = value;

	वापस 0;
पूर्ण

/**
 *	ffb_blank - Optional function.  Blanks the display.
 *	@blank: the blank mode we want.
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक ffb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;
	काष्ठा ffb_dac __iomem *dac = par->dac;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक i;

	spin_lock_irqsave(&par->lock, flags);

	FFBWait(par);

	upa_ग_लिखोl(FFB_DAC_TGEN, &dac->type);
	val = upa_पढ़ोl(&dac->value);
	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		val |= FFB_DAC_TGEN_VIDE;
		par->flags &= ~FFB_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		val &= ~FFB_DAC_TGEN_VIDE;
		par->flags |= FFB_FLAG_BLANKED;
		अवरोध;
	पूर्ण
	upa_ग_लिखोl(FFB_DAC_TGEN, &dac->type);
	upa_ग_लिखोl(val, &dac->value);
	क्रम (i = 0; i < 10; i++) अणु
		upa_ग_लिखोl(FFB_DAC_TGEN, &dac->type);
		upa_पढ़ोl(&dac->value);
	पूर्ण

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा sbus_mmap_map ffb_mmap_map[] = अणु
	अणु
		.voff	= FFB_SFB8R_VOFF,
		.poff	= FFB_SFB8R_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_SFB8G_VOFF,
		.poff	= FFB_SFB8G_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_SFB8B_VOFF,
		.poff	= FFB_SFB8B_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_SFB8X_VOFF,
		.poff	= FFB_SFB8X_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_SFB32_VOFF,
		.poff	= FFB_SFB32_POFF,
		.size	= 0x1000000
	पूर्ण,
	अणु
		.voff	= FFB_SFB64_VOFF,
		.poff	= FFB_SFB64_POFF,
		.size	= 0x2000000
	पूर्ण,
	अणु
		.voff	= FFB_FBC_REGS_VOFF,
		.poff	= FFB_FBC_REGS_POFF,
		.size	= 0x0002000
	पूर्ण,
	अणु
		.voff	= FFB_BM_FBC_REGS_VOFF,
		.poff	= FFB_BM_FBC_REGS_POFF,
		.size	= 0x0002000
	पूर्ण,
	अणु
		.voff	= FFB_DFB8R_VOFF,
		.poff	= FFB_DFB8R_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_DFB8G_VOFF,
		.poff	= FFB_DFB8G_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_DFB8B_VOFF,
		.poff	= FFB_DFB8B_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_DFB8X_VOFF,
		.poff	= FFB_DFB8X_POFF,
		.size	= 0x0400000
	पूर्ण,
	अणु
		.voff	= FFB_DFB24_VOFF,
		.poff	= FFB_DFB24_POFF,
		.size	= 0x1000000
	पूर्ण,
	अणु
		.voff	= FFB_DFB32_VOFF,
		.poff	= FFB_DFB32_POFF,
		.size	= 0x1000000
	पूर्ण,
	अणु
		.voff	= FFB_FBC_KREGS_VOFF,
		.poff	= FFB_FBC_KREGS_POFF,
		.size	= 0x0002000
	पूर्ण,
	अणु
		.voff	= FFB_DAC_VOFF,
		.poff	= FFB_DAC_POFF,
		.size	= 0x0002000
	पूर्ण,
	अणु
		.voff	= FFB_PROM_VOFF,
		.poff	= FFB_PROM_POFF,
		.size	= 0x0010000
	पूर्ण,
	अणु
		.voff	= FFB_EXP_VOFF,
		.poff	= FFB_EXP_POFF,
		.size	= 0x0002000
	पूर्ण,
	अणु
		.voff	= FFB_DFB422A_VOFF,
		.poff	= FFB_DFB422A_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु
		.voff	= FFB_DFB422AD_VOFF,
		.poff	= FFB_DFB422AD_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु
		.voff	= FFB_DFB24B_VOFF,
		.poff	= FFB_DFB24B_POFF,
		.size	= 0x1000000
	पूर्ण,
	अणु
		.voff	= FFB_DFB422B_VOFF,
		.poff	= FFB_DFB422B_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु
		.voff	= FFB_DFB422BD_VOFF,
		.poff	= FFB_DFB422BD_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु
		.voff	= FFB_SFB16Z_VOFF,
		.poff	= FFB_SFB16Z_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु
		.voff	= FFB_SFB8Z_VOFF,
		.poff	= FFB_SFB8Z_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु
		.voff	= FFB_SFB422_VOFF,
		.poff	= FFB_SFB422_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु
		.voff	= FFB_SFB422D_VOFF,
		.poff	= FFB_SFB422D_POFF,
		.size	= 0x0800000
	पूर्ण,
	अणु .size = 0 पूर्ण
पूर्ण;

अटल पूर्णांक ffb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;

	वापस sbusfb_mmap_helper(ffb_mmap_map,
				  par->physbase, par->fbsize,
				  0, vma);
पूर्ण

अटल पूर्णांक ffb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;

	वापस sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_CREATOR, 24, par->fbsize);
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम ffb_init_fix(काष्ठा fb_info *info)
अणु
	काष्ठा ffb_par *par = (काष्ठा ffb_par *)info->par;
	स्थिर अक्षर *ffb_type_name;

	अगर (!(par->flags & FFB_FLAG_AFB)) अणु
		अगर ((par->board_type & 0x7) == 0x3)
			ffb_type_name = "Creator 3D";
		अन्यथा
			ffb_type_name = "Creator";
	पूर्ण अन्यथा
		ffb_type_name = "Elite 3D";

	strlcpy(info->fix.id, ffb_type_name, माप(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;

	/* Framebuffer length is the same regardless of resolution. */
	info->fix.line_length = 8192;

	info->fix.accel = FB_ACCEL_SUN_CREATOR;
पूर्ण

अटल पूर्णांक ffb_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा ffb_fbc __iomem *fbc;
	काष्ठा ffb_dac __iomem *dac;
	काष्ठा fb_info *info;
	काष्ठा ffb_par *par;
	u32 dac_pnum, dac_rev, dac_mrev;
	पूर्णांक err;

	info = framebuffer_alloc(माप(काष्ठा ffb_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;

	par = info->par;

	spin_lock_init(&par->lock);
	par->fbc = of_ioremap(&op->resource[2], 0,
			      माप(काष्ठा ffb_fbc), "ffb fbc");
	अगर (!par->fbc)
		जाओ out_release_fb;

	par->dac = of_ioremap(&op->resource[1], 0,
			      माप(काष्ठा ffb_dac), "ffb dac");
	अगर (!par->dac)
		जाओ out_unmap_fbc;

	par->rop_cache = FFB_ROP_NEW;
	par->physbase = op->resource[0].start;

	/* Don't mention copyarea, so SCROLL_REDRAW is always
	 * used.  It is the fastest on this chip.
	 */
	info->flags = (FBINFO_DEFAULT |
		       /* FBINFO_HWACCEL_COPYAREA | */
		       FBINFO_HWACCEL_FILLRECT |
		       FBINFO_HWACCEL_IMAGEBLIT);

	info->fbops = &ffb_ops;

	info->screen_base = (अक्षर *) par->physbase + FFB_DFB24_POFF;
	info->pseuकरो_palette = par->pseuकरो_palette;

	sbusfb_fill_var(&info->var, dp, 32);
	par->fbsize = PAGE_ALIGN(info->var.xres * info->var.yres * 4);
	ffb_fixup_var_rgb(&info->var);

	info->var.accel_flags = FB_ACCELF_TEXT;

	अगर (of_node_name_eq(dp, "SUNW,afb"))
		par->flags |= FFB_FLAG_AFB;

	par->board_type = of_getपूर्णांकprop_शेष(dp, "board_type", 0);

	fbc = par->fbc;
	अगर ((upa_पढ़ोl(&fbc->ucsr) & FFB_UCSR_ALL_ERRORS) != 0)
		upa_ग_लिखोl(FFB_UCSR_ALL_ERRORS, &fbc->ucsr);

	dac = par->dac;
	upa_ग_लिखोl(FFB_DAC_DID, &dac->type);
	dac_pnum = upa_पढ़ोl(&dac->value);
	dac_rev = (dac_pnum & FFB_DAC_DID_REV) >> FFB_DAC_DID_REV_SHIFT;
	dac_pnum = (dac_pnum & FFB_DAC_DID_PNUM) >> FFB_DAC_DID_PNUM_SHIFT;

	upa_ग_लिखोl(FFB_DAC_UCTRL, &dac->type);
	dac_mrev = upa_पढ़ोl(&dac->value);
	dac_mrev = (dac_mrev & FFB_DAC_UCTRL_MANREV) >>
		FFB_DAC_UCTRL_MANREV_SHIFT;

	/* Elite3D has dअगरferent DAC revision numbering, and no DAC revisions
	 * have the reversed meaning of cursor enable.  Otherwise, Pacअगरica 1
	 * ramdacs with manufacturing revision less than 3 have inverted
	 * cursor logic.  We identअगरy Pacअगरica 1 as not Pacअगरica 2, the
	 * latter having a part number value of 0x236e.
	 */
	अगर ((par->flags & FFB_FLAG_AFB) || dac_pnum == 0x236e) अणु
		par->flags &= ~FFB_FLAG_INVCURSOR;
	पूर्ण अन्यथा अणु
		अगर (dac_mrev < 3)
			par->flags |= FFB_FLAG_INVCURSOR;
	पूर्ण

	ffb_चयन_from_graph(par);

	/* Unblank it just to be sure.  When there are multiple
	 * FFB/AFB cards in the प्रणाली, or it is not the OBP
	 * chosen console, it will have video outमाला_दो off in
	 * the DAC.
	 */
	ffb_blank(FB_BLANK_UNBLANK, info);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0))
		जाओ out_unmap_dac;

	ffb_init_fix(info);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_dealloc_cmap;

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: %s at %016lx, type %d, "
	       "DAC pnum[%x] rev[%d] manuf_rev[%d]\n",
	       dp,
	       ((par->flags & FFB_FLAG_AFB) ? "AFB" : "FFB"),
	       par->physbase, par->board_type,
	       dac_pnum, dac_rev, dac_mrev);

	वापस 0;

out_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);

out_unmap_dac:
	of_iounmap(&op->resource[1], par->dac, माप(काष्ठा ffb_dac));

out_unmap_fbc:
	of_iounmap(&op->resource[2], par->fbc, माप(काष्ठा ffb_fbc));

out_release_fb:
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक ffb_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा ffb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	of_iounmap(&op->resource[2], par->fbc, माप(काष्ठा ffb_fbc));
	of_iounmap(&op->resource[1], par->dac, माप(काष्ठा ffb_dac));

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ffb_match[] = अणु
	अणु
		.name = "SUNW,ffb",
	पूर्ण,
	अणु
		.name = "SUNW,afb",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ffb_match);

अटल काष्ठा platक्रमm_driver ffb_driver = अणु
	.driver = अणु
		.name = "ffb",
		.of_match_table = ffb_match,
	पूर्ण,
	.probe		= ffb_probe,
	.हटाओ		= ffb_हटाओ,
पूर्ण;

अटल पूर्णांक __init ffb_init(व्योम)
अणु
	अगर (fb_get_options("ffb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&ffb_driver);
पूर्ण

अटल व्योम __निकास ffb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ffb_driver);
पूर्ण

module_init(ffb_init);
module_निकास(ffb_निकास);

MODULE_DESCRIPTION("framebuffer driver for Creator/Elite3D chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
