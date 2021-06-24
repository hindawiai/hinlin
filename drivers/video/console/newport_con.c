<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * newport_con.c: Abscon क्रम newport hardware
 * 
 * (C) 1998 Thomas Bogenकरोerfer (tsbogend@alpha.franken.de)
 * (C) 1999 Ulf Carlsson (ulfc@thepuffingruop.com)
 * 
 * This driver is based on sgicons.c and cons_newport.
 * 
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1997 Miguel de Icaza (miguel@nuclecu.unam.mx)
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kd.h>
#समावेश <linux/selection.h>
#समावेश <linux/console.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/gio_device.h>

#समावेश <video/newport.h>

#समावेश <linux/linux_logo.h>
#समावेश <linux/font.h>

#घोषणा NEWPORT_LEN	0x10000

#घोषणा FONT_DATA ((अचिन्हित अक्षर *)font_vga_8x16.data)

अटल अचिन्हित अक्षर *font_data[MAX_NR_CONSOLES];

अटल काष्ठा newport_regs *npregs;
अटल अचिन्हित दीर्घ newport_addr;

अटल पूर्णांक logo_active;
अटल पूर्णांक topscan;
अटल पूर्णांक xcurs_correction = 29;
अटल पूर्णांक newport_xsize;
अटल पूर्णांक newport_ysize;
अटल पूर्णांक newport_has_init;

अटल पूर्णांक newport_set_def_font(पूर्णांक unit, काष्ठा console_font *op);

#घोषणा BMASK(c) (c << 24)

#घोषणा RENDER(regs, cp) करो अणु \
(regs)->go.zpattern = BMASK((cp)[0x0]); (regs)->go.zpattern = BMASK((cp)[0x1]); \
(regs)->go.zpattern = BMASK((cp)[0x2]); (regs)->go.zpattern = BMASK((cp)[0x3]); \
(regs)->go.zpattern = BMASK((cp)[0x4]); (regs)->go.zpattern = BMASK((cp)[0x5]); \
(regs)->go.zpattern = BMASK((cp)[0x6]); (regs)->go.zpattern = BMASK((cp)[0x7]); \
(regs)->go.zpattern = BMASK((cp)[0x8]); (regs)->go.zpattern = BMASK((cp)[0x9]); \
(regs)->go.zpattern = BMASK((cp)[0xa]); (regs)->go.zpattern = BMASK((cp)[0xb]); \
(regs)->go.zpattern = BMASK((cp)[0xc]); (regs)->go.zpattern = BMASK((cp)[0xd]); \
(regs)->go.zpattern = BMASK((cp)[0xe]); (regs)->go.zpattern = BMASK((cp)[0xf]); \
पूर्ण जबतक(0)

#घोषणा TESTVAL 0xdeadbeef
#घोषणा XSTI_TO_FXSTART(val) (((val) & 0xffff) << 11)

अटल अंतरभूत व्योम newport_render_background(पूर्णांक xstart, पूर्णांक ystart,
					     पूर्णांक xend, पूर्णांक yend, पूर्णांक ci)
अणु
	newport_रुको(npregs);
	npregs->set.wrmask = 0xffffffff;
	npregs->set.drawmode0 = (NPORT_DMODE0_DRAW | NPORT_DMODE0_BLOCK |
				 NPORT_DMODE0_DOSETUP | NPORT_DMODE0_STOPX
				 | NPORT_DMODE0_STOPY);
	npregs->set.colori = ci;
	npregs->set.xystarti =
	    (xstart << 16) | ((ystart + topscan) & 0x3ff);
	npregs->go.xyendi =
	    ((xend + 7) << 16) | ((yend + topscan + 15) & 0x3ff);
पूर्ण

अटल अंतरभूत व्योम newport_init_cmap(व्योम)
अणु
	अचिन्हित लघु i;

	क्रम (i = 0; i < 16; i++) अणु
		newport_bfरुको(npregs);
		newport_cmap_setaddr(npregs, color_table[i]);
		newport_cmap_setrgb(npregs,
				    शेष_red[i],
				    शेष_grn[i], शेष_blu[i]);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा linux_logo *newport_show_logo(व्योम)
अणु
#अगर_घोषित CONFIG_LOGO_SGI_CLUT224
	स्थिर काष्ठा linux_logo *logo = fb_find_logo(8);
	स्थिर अचिन्हित अक्षर *clut;
	स्थिर अचिन्हित अक्षर *data;
	अचिन्हित दीर्घ i;

	अगर (!logo)
		वापस शून्य;
	clut = logo->clut;
	data = logo->data;

	क्रम (i = 0; i < logo->clutsize; i++) अणु
		newport_bfरुको(npregs);
		newport_cmap_setaddr(npregs, i + 0x20);
		newport_cmap_setrgb(npregs, clut[0], clut[1], clut[2]);
		clut += 3;
	पूर्ण

	newport_रुको(npregs);
	npregs->set.drawmode0 = (NPORT_DMODE0_DRAW | NPORT_DMODE0_BLOCK |
				 NPORT_DMODE0_CHOST);

	npregs->set.xystarti = ((newport_xsize - logo->width) << 16) | (0);
	npregs->set.xyendi = ((newport_xsize - 1) << 16);
	newport_रुको(npregs);

	क्रम (i = 0; i < logo->width*logo->height; i++)
		npregs->go.hostrw0 = *data++ << 24;

	वापस logo;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर /* CONFIG_LOGO_SGI_CLUT224 */
पूर्ण

अटल अंतरभूत व्योम newport_clear_screen(पूर्णांक xstart, पूर्णांक ystart, पूर्णांक xend,
					पूर्णांक yend, पूर्णांक ci)
अणु
	अगर (logo_active)
		वापस;

	newport_रुको(npregs);
	npregs->set.wrmask = 0xffffffff;
	npregs->set.drawmode0 = (NPORT_DMODE0_DRAW | NPORT_DMODE0_BLOCK |
				 NPORT_DMODE0_DOSETUP | NPORT_DMODE0_STOPX
				 | NPORT_DMODE0_STOPY);
	npregs->set.colori = ci;
	npregs->set.xystarti = (xstart << 16) | ystart;
	npregs->go.xyendi = (xend << 16) | yend;
पूर्ण

अटल अंतरभूत व्योम newport_clear_lines(पूर्णांक ystart, पूर्णांक yend, पूर्णांक ci)
अणु
	ystart = ((ystart << 4) + topscan) & 0x3ff;
	yend = ((yend << 4) + topscan + 15) & 0x3ff;
	newport_clear_screen(0, ystart, 1280 + 63, yend, ci);
पूर्ण

अटल व्योम newport_reset(व्योम)
अणु
	अचिन्हित लघु treg;
	पूर्णांक i;

	newport_रुको(npregs);
	treg = newport_vc2_get(npregs, VC2_IREG_CONTROL);
	newport_vc2_set(npregs, VC2_IREG_CONTROL,
			(treg | VC2_CTRL_EVIDEO));

	treg = newport_vc2_get(npregs, VC2_IREG_CENTRY);
	newport_vc2_set(npregs, VC2_IREG_RADDR, treg);
	npregs->set.dcbmode = (NPORT_DMODE_AVC2 | VC2_REGADDR_RAM |
			       NPORT_DMODE_W2 | VC2_PROTOCOL);
	क्रम (i = 0; i < 128; i++) अणु
		newport_bfरुको(npregs);
		अगर (i == 92 || i == 94)
			npregs->set.dcbdata0.byलघु.s1 = 0xff00;
		अन्यथा
			npregs->set.dcbdata0.byलघु.s1 = 0x0000;
	पूर्ण

	newport_init_cmap();

	/* turn off popup plane */
	npregs->set.dcbmode = (DCB_XMAP0 | R_DCB_XMAP9_PROTOCOL |
			       XM9_CRS_CONFIG | NPORT_DMODE_W1);
	npregs->set.dcbdata0.bybytes.b3 &= ~XM9_PUPMODE;
	npregs->set.dcbmode = (DCB_XMAP1 | R_DCB_XMAP9_PROTOCOL |
			       XM9_CRS_CONFIG | NPORT_DMODE_W1);
	npregs->set.dcbdata0.bybytes.b3 &= ~XM9_PUPMODE;

	topscan = 0;
	npregs->cset.topscan = 0x3ff;
	npregs->cset.xywin = (4096 << 16) | 4096;

	/* Clear the screen. */
	newport_clear_screen(0, 0, 1280 + 63, 1024, 0);
पूर्ण

/*
 * calculate the actual screen size by पढ़ोing
 * the video timing out of the VC2
 */
अटल व्योम newport_get_screensize(व्योम)
अणु
	पूर्णांक i, cols;
	अचिन्हित लघु ventry, treg;
	अचिन्हित लघु linetable[128];	/* should be enough */

	ventry = newport_vc2_get(npregs, VC2_IREG_VENTRY);
	newport_vc2_set(npregs, VC2_IREG_RADDR, ventry);
	npregs->set.dcbmode = (NPORT_DMODE_AVC2 | VC2_REGADDR_RAM |
			       NPORT_DMODE_W2 | VC2_PROTOCOL);
	क्रम (i = 0; i < 128; i++) अणु
		newport_bfरुको(npregs);
		linetable[i] = npregs->set.dcbdata0.byलघु.s1;
	पूर्ण

	newport_xsize = newport_ysize = 0;
	क्रम (i = 0; i < ARRAY_SIZE(linetable) - 1 && linetable[i + 1]; i += 2) अणु
		cols = 0;
		newport_vc2_set(npregs, VC2_IREG_RADDR, linetable[i]);
		npregs->set.dcbmode = (NPORT_DMODE_AVC2 | VC2_REGADDR_RAM |
				       NPORT_DMODE_W2 | VC2_PROTOCOL);
		करो अणु
			newport_bfरुको(npregs);
			treg = npregs->set.dcbdata0.byलघु.s1;
			अगर ((treg & 1) == 0)
				cols += (treg >> 7) & 0xfe;
			अगर ((treg & 0x80) == 0) अणु
				newport_bfरुको(npregs);
				treg = npregs->set.dcbdata0.byलघु.s1;
			पूर्ण
		पूर्ण जबतक ((treg & 0x8000) == 0);
		अगर (cols) अणु
			अगर (cols > newport_xsize)
				newport_xsize = cols;
			newport_ysize += linetable[i + 1];
		पूर्ण
	पूर्ण
	prपूर्णांकk("NG1: Screensize %dx%d\n", newport_xsize, newport_ysize);
पूर्ण

अटल व्योम newport_get_revisions(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक board_rev;
	अचिन्हित पूर्णांक rex3_rev;
	अचिन्हित पूर्णांक vc2_rev;
	अचिन्हित पूर्णांक cmap_rev;
	अचिन्हित पूर्णांक xmap9_rev;
	अचिन्हित पूर्णांक bt445_rev;
	अचिन्हित पूर्णांक bitplanes;

	rex3_rev = npregs->cset.status & NPORT_STAT_VERS;

	npregs->set.dcbmode = (DCB_CMAP0 | NCMAP_PROTOCOL |
			       NCMAP_REGADDR_RREG | NPORT_DMODE_W1);
	पंचांगp = npregs->set.dcbdata0.bybytes.b3;
	cmap_rev = पंचांगp & 7;
	board_rev = (पंचांगp >> 4) & 7;
	bitplanes = ((board_rev > 1) && (पंचांगp & 0x80)) ? 8 : 24;

	npregs->set.dcbmode = (DCB_CMAP1 | NCMAP_PROTOCOL |
			       NCMAP_REGADDR_RREG | NPORT_DMODE_W1);
	पंचांगp = npregs->set.dcbdata0.bybytes.b3;
	अगर ((पंचांगp & 7) < cmap_rev)
		cmap_rev = (पंचांगp & 7);

	vc2_rev = (newport_vc2_get(npregs, VC2_IREG_CONFIG) >> 5) & 7;

	npregs->set.dcbmode = (DCB_XMAP0 | R_DCB_XMAP9_PROTOCOL |
			       XM9_CRS_REVISION | NPORT_DMODE_W1);
	xmap9_rev = npregs->set.dcbdata0.bybytes.b3 & 7;

	npregs->set.dcbmode = (DCB_BT445 | BT445_PROTOCOL |
			       BT445_CSR_ADDR_REG | NPORT_DMODE_W1);
	npregs->set.dcbdata0.bybytes.b3 = BT445_REVISION_REG;
	npregs->set.dcbmode = (DCB_BT445 | BT445_PROTOCOL |
			       BT445_CSR_REVISION | NPORT_DMODE_W1);
	bt445_rev = (npregs->set.dcbdata0.bybytes.b3 >> 4) - 0x0a;

#घोषणा L(a)     (अक्षर)('A'+(a))
	prपूर्णांकk
	    ("NG1: Revision %d, %d bitplanes, REX3 revision %c, VC2 revision %c, xmap9 revision %c, cmap revision %c, bt445 revision %c\n",
	     board_rev, bitplanes, L(rex3_rev), L(vc2_rev), L(xmap9_rev),
	     L(cmap_rev ? (cmap_rev + 1) : 0), L(bt445_rev));
#अघोषित L

	अगर (board_rev == 3)	/* I करोn't know all affected revisions */
		xcurs_correction = 21;
पूर्ण

अटल व्योम newport_निकास(व्योम)
अणु
	पूर्णांक i;

	/* मुक्त memory used by user font */
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		newport_set_def_font(i, शून्य);
पूर्ण

/* Can't be __init, करो_take_over_console may call it later */
अटल स्थिर अक्षर *newport_startup(व्योम)
अणु
	पूर्णांक i;

	npregs->cset.config = NPORT_CFG_GD0;

	अगर (newport_रुको(npregs))
		जाओ out_unmap;

	npregs->set.xstarti = TESTVAL;
	अगर (npregs->set._xstart.word != XSTI_TO_FXSTART(TESTVAL))
		जाओ out_unmap;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		font_data[i] = FONT_DATA;

	newport_reset();
	newport_get_revisions();
	newport_get_screensize();
	newport_has_init = 1;

	वापस "SGI Newport";

out_unmap:
	वापस शून्य;
पूर्ण

अटल व्योम newport_init(काष्ठा vc_data *vc, पूर्णांक init)
अणु
	पूर्णांक cols, rows;

	cols = newport_xsize / 8;
	rows = newport_ysize / 16;
	vc->vc_can_करो_color = 1;
	अगर (init) अणु
		vc->vc_cols = cols;
		vc->vc_rows = rows;
	पूर्ण अन्यथा
		vc_resize(vc, cols, rows);
पूर्ण

अटल व्योम newport_deinit(काष्ठा vc_data *c)
अणु
	अगर (!con_is_bound(&newport_con) && newport_has_init) अणु
		newport_निकास();
		newport_has_init = 0;
	पूर्ण
पूर्ण

अटल व्योम newport_clear(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक height,
			  पूर्णांक width)
अणु
	पूर्णांक xend = ((sx + width) << 3) - 1;
	पूर्णांक ystart = ((sy << 4) + topscan) & 0x3ff;
	पूर्णांक yend = (((sy + height) << 4) + topscan - 1) & 0x3ff;

	अगर (logo_active)
		वापस;

	अगर (ystart < yend) अणु
		newport_clear_screen(sx << 3, ystart, xend, yend,
				     (vc->state.color & 0xf0) >> 4);
	पूर्ण अन्यथा अणु
		newport_clear_screen(sx << 3, ystart, xend, 1023,
				     (vc->state.color & 0xf0) >> 4);
		newport_clear_screen(sx << 3, 0, xend, yend,
				     (vc->state.color & 0xf0) >> 4);
	पूर्ण
पूर्ण

अटल व्योम newport_अ_दो(काष्ठा vc_data *vc, पूर्णांक अक्षरattr, पूर्णांक ypos,
			 पूर्णांक xpos)
अणु
	अचिन्हित अक्षर *p;

	p = &font_data[vc->vc_num][(अक्षरattr & 0xff) << 4];
	अक्षरattr = (अक्षरattr >> 8) & 0xff;
	xpos <<= 3;
	ypos <<= 4;

	newport_render_background(xpos, ypos, xpos, ypos,
				  (अक्षरattr & 0xf0) >> 4);

	/* Set the color and drawing mode. */
	newport_रुको(npregs);
	npregs->set.colori = अक्षरattr & 0xf;
	npregs->set.drawmode0 = (NPORT_DMODE0_DRAW | NPORT_DMODE0_BLOCK |
				 NPORT_DMODE0_STOPX | NPORT_DMODE0_ZPENAB |
				 NPORT_DMODE0_L32);

	/* Set coordinates क्रम biपंचांगap operation. */
	npregs->set.xystarti = (xpos << 16) | ((ypos + topscan) & 0x3ff);
	npregs->set.xyendi = ((xpos + 7) << 16);
	newport_रुको(npregs);

	/* Go, baby, go... */
	RENDER(npregs, p);
पूर्ण

अटल व्योम newport_अ_दोs(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
			  पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos)
अणु
	पूर्णांक i;
	पूर्णांक अक्षरattr;
	अचिन्हित अक्षर *p;

	अक्षरattr = (scr_पढ़ोw(s) >> 8) & 0xff;

	xpos <<= 3;
	ypos <<= 4;

	अगर (!logo_active)
		/* Clear the area behing the string */
		newport_render_background(xpos, ypos,
					  xpos + ((count - 1) << 3), ypos,
					  (अक्षरattr & 0xf0) >> 4);

	newport_रुको(npregs);

	/* Set the color and drawing mode. */
	npregs->set.colori = अक्षरattr & 0xf;
	npregs->set.drawmode0 = (NPORT_DMODE0_DRAW | NPORT_DMODE0_BLOCK |
				 NPORT_DMODE0_STOPX | NPORT_DMODE0_ZPENAB |
				 NPORT_DMODE0_L32);

	क्रम (i = 0; i < count; i++, xpos += 8) अणु
		p = &font_data[vc->vc_num][(scr_पढ़ोw(s++) & 0xff) << 4];

		newport_रुको(npregs);

		/* Set coordinates क्रम biपंचांगap operation. */
		npregs->set.xystarti =
		    (xpos << 16) | ((ypos + topscan) & 0x3ff);
		npregs->set.xyendi = ((xpos + 7) << 16);

		/* Go, baby, go... */
		RENDER(npregs, p);
	पूर्ण
पूर्ण

अटल व्योम newport_cursor(काष्ठा vc_data *vc, पूर्णांक mode)
अणु
	अचिन्हित लघु treg;
	पूर्णांक xcurs, ycurs;

	चयन (mode) अणु
	हाल CM_ERASE:
		treg = newport_vc2_get(npregs, VC2_IREG_CONTROL);
		newport_vc2_set(npregs, VC2_IREG_CONTROL,
				(treg & ~(VC2_CTRL_ECDISP)));
		अवरोध;

	हाल CM_MOVE:
	हाल CM_DRAW:
		treg = newport_vc2_get(npregs, VC2_IREG_CONTROL);
		newport_vc2_set(npregs, VC2_IREG_CONTROL,
				(treg | VC2_CTRL_ECDISP));
		xcurs = (vc->vc_pos - vc->vc_visible_origin) / 2;
		ycurs = ((xcurs / vc->vc_cols) << 4) + 31;
		xcurs = ((xcurs % vc->vc_cols) << 3) + xcurs_correction;
		newport_vc2_set(npregs, VC2_IREG_CURSX, xcurs);
		newport_vc2_set(npregs, VC2_IREG_CURSY, ycurs);
	पूर्ण
पूर्ण

अटल पूर्णांक newport_चयन(काष्ठा vc_data *vc)
अणु
	अटल पूर्णांक logo_drawn = 0;

	topscan = 0;
	npregs->cset.topscan = 0x3ff;

	अगर (!logo_drawn) अणु
		अगर (newport_show_logo()) अणु
			logo_drawn = 1;
			logo_active = 1;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक newport_blank(काष्ठा vc_data *c, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	अचिन्हित लघु treg;

	अगर (blank == 0) अणु
		/* unblank console */
		treg = newport_vc2_get(npregs, VC2_IREG_CONTROL);
		newport_vc2_set(npregs, VC2_IREG_CONTROL,
				(treg | VC2_CTRL_EDISP));
	पूर्ण अन्यथा अणु
		/* blank console */
		treg = newport_vc2_get(npregs, VC2_IREG_CONTROL);
		newport_vc2_set(npregs, VC2_IREG_CONTROL,
				(treg & ~(VC2_CTRL_EDISP)));
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक newport_set_font(पूर्णांक unit, काष्ठा console_font *op)
अणु
	पूर्णांक w = op->width;
	पूर्णांक h = op->height;
	पूर्णांक size = h * op->अक्षरcount;
	पूर्णांक i;
	अचिन्हित अक्षर *new_data, *data = op->data, *p;

	/* ladis: when I grow up, there will be a day... and more sizes will
	 * be supported ;-) */
	अगर ((w != 8) || (h != 16)
	    || (op->अक्षरcount != 256 && op->अक्षरcount != 512))
		वापस -EINVAL;

	अगर (!(new_data = kदो_स्मृति(FONT_EXTRA_WORDS * माप(पूर्णांक) + size,
	     GFP_USER))) वापस -ENOMEM;

	new_data += FONT_EXTRA_WORDS * माप(पूर्णांक);
	FNTSIZE(new_data) = size;
	FNTCHARCNT(new_data) = op->अक्षरcount;
	REFCOUNT(new_data) = 0;	/* usage counter */
	FNTSUM(new_data) = 0;

	p = new_data;
	क्रम (i = 0; i < op->अक्षरcount; i++) अणु
		स_नकल(p, data, h);
		data += 32;
		p += h;
	पूर्ण

	/* check अगर font is alपढ़ोy used by other console */
	क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
		अगर (font_data[i] != FONT_DATA
		    && FNTSIZE(font_data[i]) == size
		    && !स_भेद(font_data[i], new_data, size)) अणु
			kमुक्त(new_data - FONT_EXTRA_WORDS * माप(पूर्णांक));
			/* current font is the same as the new one */
			अगर (i == unit)
				वापस 0;
			new_data = font_data[i];
			अवरोध;
		पूर्ण
	पूर्ण
	/* old font is user font */
	अगर (font_data[unit] != FONT_DATA) अणु
		अगर (--REFCOUNT(font_data[unit]) == 0)
			kमुक्त(font_data[unit] -
			      FONT_EXTRA_WORDS * माप(पूर्णांक));
	पूर्ण
	REFCOUNT(new_data)++;
	font_data[unit] = new_data;

	वापस 0;
पूर्ण

अटल पूर्णांक newport_set_def_font(पूर्णांक unit, काष्ठा console_font *op)
अणु
	अगर (font_data[unit] != FONT_DATA) अणु
		अगर (--REFCOUNT(font_data[unit]) == 0)
			kमुक्त(font_data[unit] -
			      FONT_EXTRA_WORDS * माप(पूर्णांक));
		font_data[unit] = FONT_DATA;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक newport_font_शेष(काष्ठा vc_data *vc, काष्ठा console_font *op, अक्षर *name)
अणु
	वापस newport_set_def_font(vc->vc_num, op);
पूर्ण

अटल पूर्णांक newport_font_set(काष्ठा vc_data *vc, काष्ठा console_font *font, अचिन्हित flags)
अणु
	वापस newport_set_font(vc->vc_num, font);
पूर्ण

अटल bool newport_scroll(काष्ठा vc_data *vc, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b,
		क्रमागत con_scroll dir, अचिन्हित पूर्णांक lines)
अणु
	पूर्णांक count, x, y;
	अचिन्हित लघु *s, *d;
	अचिन्हित लघु chattr;

	logo_active = 0;	/* it's समय to disable the logo now.. */

	अगर (t == 0 && b == vc->vc_rows) अणु
		अगर (dir == SM_UP) अणु
			topscan = (topscan + (lines << 4)) & 0x3ff;
			newport_clear_lines(vc->vc_rows - lines,
					    vc->vc_rows - 1,
					    (vc->state.color & 0xf0) >> 4);
		पूर्ण अन्यथा अणु
			topscan = (topscan + (-lines << 4)) & 0x3ff;
			newport_clear_lines(0, lines - 1,
					    (vc->state.color & 0xf0) >> 4);
		पूर्ण
		npregs->cset.topscan = (topscan - 1) & 0x3ff;
		वापस false;
	पूर्ण

	count = (b - t - lines) * vc->vc_cols;
	अगर (dir == SM_UP) अणु
		x = 0;
		y = t;
		s = (अचिन्हित लघु *) (vc->vc_origin +
					vc->vc_size_row * (t + lines));
		d = (अचिन्हित लघु *) (vc->vc_origin +
					vc->vc_size_row * t);
		जबतक (count--) अणु
			chattr = scr_पढ़ोw(s++);
			अगर (chattr != scr_पढ़ोw(d)) अणु
				newport_अ_दो(vc, chattr, y, x);
				scr_ग_लिखोw(chattr, d);
			पूर्ण
			d++;
			अगर (++x == vc->vc_cols) अणु
				x = 0;
				y++;
			पूर्ण
		पूर्ण
		d = (अचिन्हित लघु *) (vc->vc_origin +
					vc->vc_size_row * (b - lines));
		x = 0;
		y = b - lines;
		क्रम (count = 0; count < (lines * vc->vc_cols); count++) अणु
			अगर (scr_पढ़ोw(d) != vc->vc_video_erase_अक्षर) अणु
				newport_अ_दो(vc, vc->vc_video_erase_अक्षर,
					     y, x);
				scr_ग_लिखोw(vc->vc_video_erase_अक्षर, d);
			पूर्ण
			d++;
			अगर (++x == vc->vc_cols) अणु
				x = 0;
				y++;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		x = vc->vc_cols - 1;
		y = b - 1;
		s = (अचिन्हित लघु *) (vc->vc_origin +
					vc->vc_size_row * (b - lines) - 2);
		d = (अचिन्हित लघु *) (vc->vc_origin +
					vc->vc_size_row * b - 2);
		जबतक (count--) अणु
			chattr = scr_पढ़ोw(s--);
			अगर (chattr != scr_पढ़ोw(d)) अणु
				newport_अ_दो(vc, chattr, y, x);
				scr_ग_लिखोw(chattr, d);
			पूर्ण
			d--;
			अगर (x-- == 0) अणु
				x = vc->vc_cols - 1;
				y--;
			पूर्ण
		पूर्ण
		d = (अचिन्हित लघु *) (vc->vc_origin +
					vc->vc_size_row * t);
		x = 0;
		y = t;
		क्रम (count = 0; count < (lines * vc->vc_cols); count++) अणु
			अगर (scr_पढ़ोw(d) != vc->vc_video_erase_अक्षर) अणु
				newport_अ_दो(vc, vc->vc_video_erase_अक्षर,
					     y, x);
				scr_ग_लिखोw(vc->vc_video_erase_अक्षर, d);
			पूर्ण
			d++;
			अगर (++x == vc->vc_cols) अणु
				x = 0;
				y++;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम newport_save_screen(काष्ठा vc_data *vc) अणु पूर्ण

स्थिर काष्ठा consw newport_con = अणु
	.owner		  = THIS_MODULE,
	.con_startup	  = newport_startup,
	.con_init	  = newport_init,
	.con_deinit	  = newport_deinit,
	.con_clear	  = newport_clear,
	.con_अ_दो	  = newport_अ_दो,
	.con_अ_दोs	  = newport_अ_दोs,
	.con_cursor	  = newport_cursor,
	.con_scroll	  = newport_scroll,
	.con_चयन	  = newport_चयन,
	.con_blank	  = newport_blank,
	.con_font_set	  = newport_font_set,
	.con_font_शेष = newport_font_शेष,
	.con_save_screen  = newport_save_screen
पूर्ण;

अटल पूर्णांक newport_probe(काष्ठा gio_device *dev,
			 स्थिर काष्ठा gio_device_id *id)
अणु
	पूर्णांक err;

	अगर (!dev->resource.start)
		वापस -EINVAL;

	अगर (npregs)
		वापस -EBUSY; /* we only support one Newport as console */

	newport_addr = dev->resource.start + 0xF0000;
	अगर (!request_mem_region(newport_addr, NEWPORT_LEN, "Newport"))
		वापस -ENODEV;

	npregs = (काष्ठा newport_regs *)/* ioremap cannot fail */
		ioremap(newport_addr, माप(काष्ठा newport_regs));
	console_lock();
	err = करो_take_over_console(&newport_con, 0, MAX_NR_CONSOLES - 1, 1);
	console_unlock();

	अगर (err) अणु
		iounmap((व्योम *)npregs);
		release_mem_region(newport_addr, NEWPORT_LEN);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम newport_हटाओ(काष्ठा gio_device *dev)
अणु
	give_up_console(&newport_con);
	iounmap((व्योम *)npregs);
	release_mem_region(newport_addr, NEWPORT_LEN);
पूर्ण

अटल काष्ठा gio_device_id newport_ids[] = अणु
	अणु .id = 0x7e पूर्ण,
	अणु .id = 0xff पूर्ण
पूर्ण;

MODULE_ALIAS("gio:7e");

अटल काष्ठा gio_driver newport_driver = अणु
	.name = "newport",
	.id_table = newport_ids,
	.probe = newport_probe,
	.हटाओ = newport_हटाओ,
पूर्ण;
module_driver(newport_driver, gio_रेजिस्टर_driver, gio_unरेजिस्टर_driver);

MODULE_LICENSE("GPL");
