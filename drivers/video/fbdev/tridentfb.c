<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Frame buffer driver क्रम Trident TGUI, Blade and Image series
 *
 * Copyright 2001, 2002 - Jani Monoses   <jani@iv.ro>
 * Copyright 2009 Krzysztof Helt <krzysztof.h1@wp.pl>
 *
 * CREDITS:(in order of appearance)
 *	skeletonfb.c by Geert Uytterhoeven and other fb code in drivers/video
 *	Special thanks ;) to Mattia Crivellini <tia@mclink.it>
 *	much inspired by the XFree86 4.x Trident driver sources
 *	by Alan Hourihane the FreeVGA project
 *	Francesco Salvestrini <salvestrini@users.sf.net> XP support,
 *	code, suggestions
 * TODO:
 *	timing value tweaking so it looks good on every monitor in every mode
 */

#समावेश <linux/module.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <linux/delay.h>
#समावेश <video/vga.h>
#समावेश <video/trident.h>

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

काष्ठा tridentfb_par अणु
	व्योम __iomem *io_virt;	/* iospace भव memory address */
	u32 pseuकरो_pal[16];
	पूर्णांक chip_id;
	पूर्णांक flatpanel;
	व्योम (*init_accel) (काष्ठा tridentfb_par *, पूर्णांक, पूर्णांक);
	व्योम (*रुको_engine) (काष्ठा tridentfb_par *);
	व्योम (*fill_rect)
		(काष्ठा tridentfb_par *par, u32, u32, u32, u32, u32, u32);
	व्योम (*copy_rect)
		(काष्ठा tridentfb_par *par, u32, u32, u32, u32, u32, u32);
	व्योम (*image_blit)
		(काष्ठा tridentfb_par *par, स्थिर अक्षर*,
		 u32, u32, u32, u32, u32, u32);
	अचिन्हित अक्षर eng_oper;	/* engine operation... */
	bool ddc_रेजिस्टरed;
	काष्ठा i2c_adapter ddc_adapter;
	काष्ठा i2c_algo_bit_data ddc_algo;
पूर्ण;

अटल काष्ठा fb_fix_screeninfo tridentfb_fix = अणु
	.id = "Trident",
	.type = FB_TYPE_PACKED_PIXELS,
	.ypanstep = 1,
	.visual = FB_VISUAL_PSEUDOCOLOR,
	.accel = FB_ACCEL_NONE,
पूर्ण;

/* शेषs which are normally overriden by user values */

/* video mode */
अटल अक्षर *mode_option;
अटल पूर्णांक bpp = 8;

अटल पूर्णांक noaccel;

अटल पूर्णांक center;
अटल पूर्णांक stretch;

अटल पूर्णांक fp;
अटल पूर्णांक crt;

अटल पूर्णांक memsize;
अटल पूर्णांक memdअगरf;
अटल पूर्णांक nativex;

module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Initial video mode e.g. '648x480-8@60'");
module_param_named(mode, mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode, "Initial video mode e.g. '648x480-8@60' (deprecated)");
module_param(bpp, पूर्णांक, 0);
module_param(center, पूर्णांक, 0);
module_param(stretch, पूर्णांक, 0);
module_param(noaccel, पूर्णांक, 0);
module_param(memsize, पूर्णांक, 0);
module_param(memdअगरf, पूर्णांक, 0);
module_param(nativex, पूर्णांक, 0);
module_param(fp, पूर्णांक, 0);
MODULE_PARM_DESC(fp, "Define if flatpanel is connected");
module_param(crt, पूर्णांक, 0);
MODULE_PARM_DESC(crt, "Define if CRT is connected");

अटल अंतरभूत पूर्णांक is_oldघड़ी(पूर्णांक id)
अणु
	वापस	(id == TGUI9440) ||
		(id == TGUI9660) ||
		(id == CYBER9320);
पूर्ण

अटल अंतरभूत पूर्णांक is_oldprotect(पूर्णांक id)
अणु
	वापस	is_oldघड़ी(id) ||
		(id == PROVIDIA9685) ||
		(id == CYBER9382) ||
		(id == CYBER9385);
पूर्ण

अटल अंतरभूत पूर्णांक is_blade(पूर्णांक id)
अणु
	वापस	(id == BLADE3D) ||
		(id == CYBERBLADEE4) ||
		(id == CYBERBLADEi7) ||
		(id == CYBERBLADEi7D) ||
		(id == CYBERBLADEi1) ||
		(id == CYBERBLADEi1D) ||
		(id == CYBERBLADEAi1) ||
		(id == CYBERBLADEAi1D);
पूर्ण

अटल अंतरभूत पूर्णांक is_xp(पूर्णांक id)
अणु
	वापस	(id == CYBERBLADEXPAi1) ||
		(id == CYBERBLADEXPm8) ||
		(id == CYBERBLADEXPm16);
पूर्ण

अटल अंतरभूत पूर्णांक is3Dchip(पूर्णांक id)
अणु
	वापस	is_blade(id) || is_xp(id) ||
		(id == CYBER9397) || (id == CYBER9397DVD) ||
		(id == CYBER9520) || (id == CYBER9525DVD) ||
		(id == IMAGE975) || (id == IMAGE985);
पूर्ण

अटल अंतरभूत पूर्णांक iscyber(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल CYBER9388:
	हाल CYBER9382:
	हाल CYBER9385:
	हाल CYBER9397:
	हाल CYBER9397DVD:
	हाल CYBER9520:
	हाल CYBER9525DVD:
	हाल CYBERBLADEE4:
	हाल CYBERBLADEi7D:
	हाल CYBERBLADEi1:
	हाल CYBERBLADEi1D:
	हाल CYBERBLADEAi1:
	हाल CYBERBLADEAi1D:
	हाल CYBERBLADEXPAi1:
		वापस 1;

	हाल CYBER9320:
	हाल CYBERBLADEi7:	/* VIA MPV4 पूर्णांकegrated version */
	शेष:
		/* हाल CYBERBLDAEXPm8:  Strange */
		/* हाल CYBERBLDAEXPm16: Strange */
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम t_outb(काष्ठा tridentfb_par *p, u8 val, u16 reg)
अणु
	fb_ग_लिखोb(val, p->io_virt + reg);
पूर्ण

अटल अंतरभूत u8 t_inb(काष्ठा tridentfb_par *p, u16 reg)
अणु
	वापस fb_पढ़ोb(p->io_virt + reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोmmr(काष्ठा tridentfb_par *par, u16 r, u32 v)
अणु
	fb_ग_लिखोl(v, par->io_virt + r);
पूर्ण

अटल अंतरभूत u32 पढ़ोmmr(काष्ठा tridentfb_par *par, u16 r)
अणु
	वापस fb_पढ़ोl(par->io_virt + r);
पूर्ण

#घोषणा DDC_SDA_TGUI		BIT(0)
#घोषणा DDC_SCL_TGUI		BIT(1)
#घोषणा DDC_SCL_DRIVE_TGUI	BIT(2)
#घोषणा DDC_SDA_DRIVE_TGUI	BIT(3)
#घोषणा DDC_MASK_TGUI		(DDC_SCL_DRIVE_TGUI | DDC_SDA_DRIVE_TGUI)

अटल व्योम tridentfb_ddc_setscl_tgui(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tridentfb_par *par = data;
	u8 reg = vga_mm_rcrt(par->io_virt, I2C) & DDC_MASK_TGUI;

	अगर (val)
		reg &= ~DDC_SCL_DRIVE_TGUI; /* disable drive - करोn't drive hi */
	अन्यथा
		reg |= DDC_SCL_DRIVE_TGUI; /* drive low */

	vga_mm_wcrt(par->io_virt, I2C, reg);
पूर्ण

अटल व्योम tridentfb_ddc_setsda_tgui(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tridentfb_par *par = data;
	u8 reg = vga_mm_rcrt(par->io_virt, I2C) & DDC_MASK_TGUI;

	अगर (val)
		reg &= ~DDC_SDA_DRIVE_TGUI; /* disable drive - करोn't drive hi */
	अन्यथा
		reg |= DDC_SDA_DRIVE_TGUI; /* drive low */

	vga_mm_wcrt(par->io_virt, I2C, reg);
पूर्ण

अटल पूर्णांक tridentfb_ddc_माला_लोda_tgui(व्योम *data)
अणु
	काष्ठा tridentfb_par *par = data;

	वापस !!(vga_mm_rcrt(par->io_virt, I2C) & DDC_SDA_TGUI);
पूर्ण

#घोषणा DDC_SDA_IN	BIT(0)
#घोषणा DDC_SCL_OUT	BIT(1)
#घोषणा DDC_SDA_OUT	BIT(3)
#घोषणा DDC_SCL_IN	BIT(6)
#घोषणा DDC_MASK	(DDC_SCL_OUT | DDC_SDA_OUT)

अटल व्योम tridentfb_ddc_setscl(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tridentfb_par *par = data;
	अचिन्हित अक्षर reg;

	reg = vga_mm_rcrt(par->io_virt, I2C) & DDC_MASK;
	अगर (val)
		reg |= DDC_SCL_OUT;
	अन्यथा
		reg &= ~DDC_SCL_OUT;
	vga_mm_wcrt(par->io_virt, I2C, reg);
पूर्ण

अटल व्योम tridentfb_ddc_setsda(व्योम *data, पूर्णांक val)
अणु
	काष्ठा tridentfb_par *par = data;
	अचिन्हित अक्षर reg;

	reg = vga_mm_rcrt(par->io_virt, I2C) & DDC_MASK;
	अगर (!val)
		reg |= DDC_SDA_OUT;
	अन्यथा
		reg &= ~DDC_SDA_OUT;
	vga_mm_wcrt(par->io_virt, I2C, reg);
पूर्ण

अटल पूर्णांक tridentfb_ddc_माला_लोcl(व्योम *data)
अणु
	काष्ठा tridentfb_par *par = data;

	वापस !!(vga_mm_rcrt(par->io_virt, I2C) & DDC_SCL_IN);
पूर्ण

अटल पूर्णांक tridentfb_ddc_माला_लोda(व्योम *data)
अणु
	काष्ठा tridentfb_par *par = data;

	वापस !!(vga_mm_rcrt(par->io_virt, I2C) & DDC_SDA_IN);
पूर्ण

अटल पूर्णांक tridentfb_setup_ddc_bus(काष्ठा fb_info *info)
अणु
	काष्ठा tridentfb_par *par = info->par;

	strlcpy(par->ddc_adapter.name, info->fix.id,
		माप(par->ddc_adapter.name));
	par->ddc_adapter.owner		= THIS_MODULE;
	par->ddc_adapter.class		= I2C_CLASS_DDC;
	par->ddc_adapter.algo_data	= &par->ddc_algo;
	par->ddc_adapter.dev.parent	= info->device;
	अगर (is_oldघड़ी(par->chip_id)) अणु /* not sure अगर this check is OK */
		par->ddc_algo.setsda	= tridentfb_ddc_setsda_tgui;
		par->ddc_algo.setscl	= tridentfb_ddc_setscl_tgui;
		par->ddc_algo.माला_लोda	= tridentfb_ddc_माला_लोda_tgui;
		/* no माला_लोcl */
	पूर्ण अन्यथा अणु
		par->ddc_algo.setsda	= tridentfb_ddc_setsda;
		par->ddc_algo.setscl	= tridentfb_ddc_setscl;
		par->ddc_algo.माला_लोda	= tridentfb_ddc_माला_लोda;
		par->ddc_algo.माला_लोcl	= tridentfb_ddc_माला_लोcl;
	पूर्ण
	par->ddc_algo.udelay		= 10;
	par->ddc_algo.समयout		= 20;
	par->ddc_algo.data		= par;

	i2c_set_adapdata(&par->ddc_adapter, par);

	वापस i2c_bit_add_bus(&par->ddc_adapter);
पूर्ण

/*
 * Blade specअगरic acceleration.
 */

#घोषणा poपूर्णांक(x, y) ((y) << 16 | (x))

अटल व्योम blade_init_accel(काष्ठा tridentfb_par *par, पूर्णांक pitch, पूर्णांक bpp)
अणु
	पूर्णांक v1 = (pitch >> 3) << 20;
	पूर्णांक पंचांगp = bpp == 24 ? 2 : (bpp >> 4);
	पूर्णांक v2 = v1 | (पंचांगp << 29);

	ग_लिखोmmr(par, 0x21C0, v2);
	ग_लिखोmmr(par, 0x21C4, v2);
	ग_लिखोmmr(par, 0x21B8, v2);
	ग_लिखोmmr(par, 0x21BC, v2);
	ग_लिखोmmr(par, 0x21D0, v1);
	ग_लिखोmmr(par, 0x21D4, v1);
	ग_लिखोmmr(par, 0x21C8, v1);
	ग_लिखोmmr(par, 0x21CC, v1);
	ग_लिखोmmr(par, 0x216C, 0);
पूर्ण

अटल व्योम blade_रुको_engine(काष्ठा tridentfb_par *par)
अणु
	जबतक (पढ़ोmmr(par, STATUS) & 0xFA800000)
		cpu_relax();
पूर्ण

अटल व्योम blade_fill_rect(काष्ठा tridentfb_par *par,
			    u32 x, u32 y, u32 w, u32 h, u32 c, u32 rop)
अणु
	ग_लिखोmmr(par, COLOR, c);
	ग_लिखोmmr(par, ROP, rop ? ROP_X : ROP_S);
	ग_लिखोmmr(par, CMD, 0x20000000 | 1 << 19 | 1 << 4 | 2 << 2);

	ग_लिखोmmr(par, DST1, poपूर्णांक(x, y));
	ग_लिखोmmr(par, DST2, poपूर्णांक(x + w - 1, y + h - 1));
पूर्ण

अटल व्योम blade_image_blit(काष्ठा tridentfb_par *par, स्थिर अक्षर *data,
			     u32 x, u32 y, u32 w, u32 h, u32 c, u32 b)
अणु
	अचिन्हित size = ((w + 31) >> 5) * h;

	ग_लिखोmmr(par, COLOR, c);
	ग_लिखोmmr(par, BGCOLOR, b);
	ग_लिखोmmr(par, CMD, 0xa0000000 | 3 << 19);

	ग_लिखोmmr(par, DST1, poपूर्णांक(x, y));
	ग_लिखोmmr(par, DST2, poपूर्णांक(x + w - 1, y + h - 1));

	ioग_लिखो32_rep(par->io_virt + 0x10000, data, size);
पूर्ण

अटल व्योम blade_copy_rect(काष्ठा tridentfb_par *par,
			    u32 x1, u32 y1, u32 x2, u32 y2, u32 w, u32 h)
अणु
	पूर्णांक direction = 2;
	u32 s1 = poपूर्णांक(x1, y1);
	u32 s2 = poपूर्णांक(x1 + w - 1, y1 + h - 1);
	u32 d1 = poपूर्णांक(x2, y2);
	u32 d2 = poपूर्णांक(x2 + w - 1, y2 + h - 1);

	अगर ((y1 > y2) || ((y1 == y2) && (x1 > x2)))
		direction = 0;

	ग_लिखोmmr(par, ROP, ROP_S);
	ग_लिखोmmr(par, CMD, 0xE0000000 | 1 << 19 | 1 << 4 | 1 << 2 | direction);

	ग_लिखोmmr(par, SRC1, direction ? s2 : s1);
	ग_लिखोmmr(par, SRC2, direction ? s1 : s2);
	ग_लिखोmmr(par, DST1, direction ? d2 : d1);
	ग_लिखोmmr(par, DST2, direction ? d1 : d2);
पूर्ण

/*
 * BladeXP specअगरic acceleration functions
 */

अटल व्योम xp_init_accel(काष्ठा tridentfb_par *par, पूर्णांक pitch, पूर्णांक bpp)
अणु
	अचिन्हित अक्षर x = bpp == 24 ? 3 : (bpp >> 4);
	पूर्णांक v1 = pitch << (bpp == 24 ? 20 : (18 + x));

	चयन (pitch << (bpp >> 3)) अणु
	हाल 8192:
	हाल 512:
		x |= 0x00;
		अवरोध;
	हाल 1024:
		x |= 0x04;
		अवरोध;
	हाल 2048:
		x |= 0x08;
		अवरोध;
	हाल 4096:
		x |= 0x0C;
		अवरोध;
	पूर्ण

	t_outb(par, x, 0x2125);

	par->eng_oper = x | 0x40;

	ग_लिखोmmr(par, 0x2154, v1);
	ग_लिखोmmr(par, 0x2150, v1);
	t_outb(par, 3, 0x2126);
पूर्ण

अटल व्योम xp_रुको_engine(काष्ठा tridentfb_par *par)
अणु
	पूर्णांक count = 0;
	पूर्णांक समयout = 0;

	जबतक (t_inb(par, STATUS) & 0x80) अणु
		count++;
		अगर (count == 10000000) अणु
			/* Timeout */
			count = 9990000;
			समयout++;
			अगर (समयout == 8) अणु
				/* Reset engine */
				t_outb(par, 0x00, STATUS);
				वापस;
			पूर्ण
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

अटल व्योम xp_fill_rect(काष्ठा tridentfb_par *par,
			 u32 x, u32 y, u32 w, u32 h, u32 c, u32 rop)
अणु
	ग_लिखोmmr(par, 0x2127, ROP_P);
	ग_लिखोmmr(par, 0x2158, c);
	ग_लिखोmmr(par, DRAWFL, 0x4000);
	ग_लिखोmmr(par, OLDDIM, poपूर्णांक(h, w));
	ग_लिखोmmr(par, OLDDST, poपूर्णांक(y, x));
	t_outb(par, 0x01, OLDCMD);
	t_outb(par, par->eng_oper, 0x2125);
पूर्ण

अटल व्योम xp_copy_rect(काष्ठा tridentfb_par *par,
			 u32 x1, u32 y1, u32 x2, u32 y2, u32 w, u32 h)
अणु
	u32 x1_पंचांगp, x2_पंचांगp, y1_पंचांगp, y2_पंचांगp;
	पूर्णांक direction = 0x0004;

	अगर ((x1 < x2) && (y1 == y2)) अणु
		direction |= 0x0200;
		x1_पंचांगp = x1 + w - 1;
		x2_पंचांगp = x2 + w - 1;
	पूर्ण अन्यथा अणु
		x1_पंचांगp = x1;
		x2_पंचांगp = x2;
	पूर्ण

	अगर (y1 < y2) अणु
		direction |= 0x0100;
		y1_पंचांगp = y1 + h - 1;
		y2_पंचांगp = y2 + h - 1;
	पूर्ण अन्यथा अणु
		y1_पंचांगp = y1;
		y2_पंचांगp = y2;
	पूर्ण

	ग_लिखोmmr(par, DRAWFL, direction);
	t_outb(par, ROP_S, 0x2127);
	ग_लिखोmmr(par, OLDSRC, poपूर्णांक(y1_पंचांगp, x1_पंचांगp));
	ग_लिखोmmr(par, OLDDST, poपूर्णांक(y2_पंचांगp, x2_पंचांगp));
	ग_लिखोmmr(par, OLDDIM, poपूर्णांक(h, w));
	t_outb(par, 0x01, OLDCMD);
पूर्ण

/*
 * Image specअगरic acceleration functions
 */
अटल व्योम image_init_accel(काष्ठा tridentfb_par *par, पूर्णांक pitch, पूर्णांक bpp)
अणु
	पूर्णांक पंचांगp = bpp == 24 ? 2: (bpp >> 4);

	ग_लिखोmmr(par, 0x2120, 0xF0000000);
	ग_लिखोmmr(par, 0x2120, 0x40000000 | पंचांगp);
	ग_लिखोmmr(par, 0x2120, 0x80000000);
	ग_लिखोmmr(par, 0x2144, 0x00000000);
	ग_लिखोmmr(par, 0x2148, 0x00000000);
	ग_लिखोmmr(par, 0x2150, 0x00000000);
	ग_लिखोmmr(par, 0x2154, 0x00000000);
	ग_लिखोmmr(par, 0x2120, 0x60000000 | (pitch << 16) | pitch);
	ग_लिखोmmr(par, 0x216C, 0x00000000);
	ग_लिखोmmr(par, 0x2170, 0x00000000);
	ग_लिखोmmr(par, 0x217C, 0x00000000);
	ग_लिखोmmr(par, 0x2120, 0x10000000);
	ग_लिखोmmr(par, 0x2130, (2047 << 16) | 2047);
पूर्ण

अटल व्योम image_रुको_engine(काष्ठा tridentfb_par *par)
अणु
	जबतक (पढ़ोmmr(par, 0x2164) & 0xF0000000)
		cpu_relax();
पूर्ण

अटल व्योम image_fill_rect(काष्ठा tridentfb_par *par,
			    u32 x, u32 y, u32 w, u32 h, u32 c, u32 rop)
अणु
	ग_लिखोmmr(par, 0x2120, 0x80000000);
	ग_लिखोmmr(par, 0x2120, 0x90000000 | ROP_S);

	ग_लिखोmmr(par, 0x2144, c);

	ग_लिखोmmr(par, DST1, poपूर्णांक(x, y));
	ग_लिखोmmr(par, DST2, poपूर्णांक(x + w - 1, y + h - 1));

	ग_लिखोmmr(par, 0x2124, 0x80000000 | 3 << 22 | 1 << 10 | 1 << 9);
पूर्ण

अटल व्योम image_copy_rect(काष्ठा tridentfb_par *par,
			    u32 x1, u32 y1, u32 x2, u32 y2, u32 w, u32 h)
अणु
	पूर्णांक direction = 0x4;
	u32 s1 = poपूर्णांक(x1, y1);
	u32 s2 = poपूर्णांक(x1 + w - 1, y1 + h - 1);
	u32 d1 = poपूर्णांक(x2, y2);
	u32 d2 = poपूर्णांक(x2 + w - 1, y2 + h - 1);

	अगर ((y1 > y2) || ((y1 == y2) && (x1 > x2)))
		direction = 0;

	ग_लिखोmmr(par, 0x2120, 0x80000000);
	ग_लिखोmmr(par, 0x2120, 0x90000000 | ROP_S);

	ग_लिखोmmr(par, SRC1, direction ? s2 : s1);
	ग_लिखोmmr(par, SRC2, direction ? s1 : s2);
	ग_लिखोmmr(par, DST1, direction ? d2 : d1);
	ग_लिखोmmr(par, DST2, direction ? d1 : d2);
	ग_लिखोmmr(par, 0x2124,
		 0x80000000 | 1 << 22 | 1 << 10 | 1 << 7 | direction);
पूर्ण

/*
 * TGUI 9440/96XX acceleration
 */

अटल व्योम tgui_init_accel(काष्ठा tridentfb_par *par, पूर्णांक pitch, पूर्णांक bpp)
अणु
	अचिन्हित अक्षर x = bpp == 24 ? 3 : (bpp >> 4);

	/* disable clipping */
	ग_लिखोmmr(par, 0x2148, 0);
	ग_लिखोmmr(par, 0x214C, poपूर्णांक(4095, 2047));

	चयन ((pitch * bpp) / 8) अणु
	हाल 8192:
	हाल 512:
		x |= 0x00;
		अवरोध;
	हाल 1024:
		x |= 0x04;
		अवरोध;
	हाल 2048:
		x |= 0x08;
		अवरोध;
	हाल 4096:
		x |= 0x0C;
		अवरोध;
	पूर्ण

	fb_ग_लिखोw(x, par->io_virt + 0x2122);
पूर्ण

अटल व्योम tgui_fill_rect(काष्ठा tridentfb_par *par,
			   u32 x, u32 y, u32 w, u32 h, u32 c, u32 rop)
अणु
	t_outb(par, ROP_P, 0x2127);
	ग_लिखोmmr(par, OLDCLR, c);
	ग_लिखोmmr(par, DRAWFL, 0x4020);
	ग_लिखोmmr(par, OLDDIM, poपूर्णांक(w - 1, h - 1));
	ग_लिखोmmr(par, OLDDST, poपूर्णांक(x, y));
	t_outb(par, 1, OLDCMD);
पूर्ण

अटल व्योम tgui_copy_rect(काष्ठा tridentfb_par *par,
			   u32 x1, u32 y1, u32 x2, u32 y2, u32 w, u32 h)
अणु
	पूर्णांक flags = 0;
	u16 x1_पंचांगp, x2_पंचांगp, y1_पंचांगp, y2_पंचांगp;

	अगर ((x1 < x2) && (y1 == y2)) अणु
		flags |= 0x0200;
		x1_पंचांगp = x1 + w - 1;
		x2_पंचांगp = x2 + w - 1;
	पूर्ण अन्यथा अणु
		x1_पंचांगp = x1;
		x2_पंचांगp = x2;
	पूर्ण

	अगर (y1 < y2) अणु
		flags |= 0x0100;
		y1_पंचांगp = y1 + h - 1;
		y2_पंचांगp = y2 + h - 1;
	पूर्ण अन्यथा अणु
		y1_पंचांगp = y1;
		y2_पंचांगp = y2;
	पूर्ण

	ग_लिखोmmr(par, DRAWFL, 0x4 | flags);
	t_outb(par, ROP_S, 0x2127);
	ग_लिखोmmr(par, OLDSRC, poपूर्णांक(x1_पंचांगp, y1_पंचांगp));
	ग_लिखोmmr(par, OLDDST, poपूर्णांक(x2_पंचांगp, y2_पंचांगp));
	ग_लिखोmmr(par, OLDDIM, poपूर्णांक(w - 1, h - 1));
	t_outb(par, 1, OLDCMD);
पूर्ण

/*
 * Accel functions called by the upper layers
 */
अटल व्योम tridentfb_fillrect(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_fillrect *fr)
अणु
	काष्ठा tridentfb_par *par = info->par;
	पूर्णांक col;

	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_fillrect(info, fr);
		वापस;
	पूर्ण
	अगर (info->var.bits_per_pixel == 8) अणु
		col = fr->color;
		col |= col << 8;
		col |= col << 16;
	पूर्ण अन्यथा
		col = ((u32 *)(info->pseuकरो_palette))[fr->color];

	par->रुको_engine(par);
	par->fill_rect(par, fr->dx, fr->dy, fr->width,
		       fr->height, col, fr->rop);
पूर्ण

अटल व्योम tridentfb_imageblit(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_image *img)
अणु
	काष्ठा tridentfb_par *par = info->par;
	पूर्णांक col, bgcol;

	अगर ((info->flags & FBINFO_HWACCEL_DISABLED) || img->depth != 1) अणु
		cfb_imageblit(info, img);
		वापस;
	पूर्ण
	अगर (info->var.bits_per_pixel == 8) अणु
		col = img->fg_color;
		col |= col << 8;
		col |= col << 16;
		bgcol = img->bg_color;
		bgcol |= bgcol << 8;
		bgcol |= bgcol << 16;
	पूर्ण अन्यथा अणु
		col = ((u32 *)(info->pseuकरो_palette))[img->fg_color];
		bgcol = ((u32 *)(info->pseuकरो_palette))[img->bg_color];
	पूर्ण

	par->रुको_engine(par);
	अगर (par->image_blit)
		par->image_blit(par, img->data, img->dx, img->dy,
				img->width, img->height, col, bgcol);
	अन्यथा
		cfb_imageblit(info, img);
पूर्ण

अटल व्योम tridentfb_copyarea(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_copyarea *ca)
अणु
	काष्ठा tridentfb_par *par = info->par;

	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_copyarea(info, ca);
		वापस;
	पूर्ण
	par->रुको_engine(par);
	par->copy_rect(par, ca->sx, ca->sy, ca->dx, ca->dy,
		       ca->width, ca->height);
पूर्ण

अटल पूर्णांक tridentfb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा tridentfb_par *par = info->par;

	अगर (!(info->flags & FBINFO_HWACCEL_DISABLED))
		par->रुको_engine(par);
	वापस 0;
पूर्ण

/*
 * Hardware access functions
 */

अटल अंतरभूत अचिन्हित अक्षर पढ़ो3X4(काष्ठा tridentfb_par *par, पूर्णांक reg)
अणु
	वापस vga_mm_rcrt(par->io_virt, reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो3X4(काष्ठा tridentfb_par *par, पूर्णांक reg,
			    अचिन्हित अक्षर val)
अणु
	vga_mm_wcrt(par->io_virt, reg, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो3CE(काष्ठा tridentfb_par *par,
				    अचिन्हित अक्षर reg)
अणु
	वापस vga_mm_rgfx(par->io_virt, reg);
पूर्ण

अटल अंतरभूत व्योम ग_लिखोAttr(काष्ठा tridentfb_par *par, पूर्णांक reg,
			     अचिन्हित अक्षर val)
अणु
	fb_पढ़ोb(par->io_virt + VGA_IS1_RC);	/* flip-flop to index */
	vga_mm_wattr(par->io_virt, reg, val);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो3CE(काष्ठा tridentfb_par *par, पूर्णांक reg,
			    अचिन्हित अक्षर val)
अणु
	vga_mm_wgfx(par->io_virt, reg, val);
पूर्ण

अटल व्योम enable_mmio(काष्ठा tridentfb_par *par)
अणु
	/* Goto New Mode */
	vga_io_rseq(0x0B);

	/* Unprotect रेजिस्टरs */
	vga_io_wseq(NewMode1, 0x80);
	अगर (!is_oldprotect(par->chip_id))
		vga_io_wseq(Protection, 0x92);

	/* Enable MMIO */
	outb(PCIReg, 0x3D4);
	outb(inb(0x3D5) | 0x01, 0x3D5);
पूर्ण

अटल व्योम disable_mmio(काष्ठा tridentfb_par *par)
अणु
	/* Goto New Mode */
	vga_mm_rseq(par->io_virt, 0x0B);

	/* Unprotect रेजिस्टरs */
	vga_mm_wseq(par->io_virt, NewMode1, 0x80);
	अगर (!is_oldprotect(par->chip_id))
		vga_mm_wseq(par->io_virt, Protection, 0x92);

	/* Disable MMIO */
	t_outb(par, PCIReg, 0x3D4);
	t_outb(par, t_inb(par, 0x3D5) & ~0x01, 0x3D5);
पूर्ण

अटल अंतरभूत व्योम crtc_unlock(काष्ठा tridentfb_par *par)
अणु
	ग_लिखो3X4(par, VGA_CRTC_V_SYNC_END,
		 पढ़ो3X4(par, VGA_CRTC_V_SYNC_END) & 0x7F);
पूर्ण

/*  Return flat panel's maximum x resolution */
अटल पूर्णांक get_nativex(काष्ठा tridentfb_par *par)
अणु
	पूर्णांक x, y, पंचांगp;

	अगर (nativex)
		वापस nativex;

	पंचांगp = (पढ़ो3CE(par, VertStretch) >> 4) & 3;

	चयन (पंचांगp) अणु
	हाल 0:
		x = 1280; y = 1024;
		अवरोध;
	हाल 2:
		x = 1024; y = 768;
		अवरोध;
	हाल 3:
		x = 800; y = 600;
		अवरोध;
	हाल 1:
	शेष:
		x = 640;  y = 480;
		अवरोध;
	पूर्ण

	output("%dx%d flat panel found\n", x, y);
	वापस x;
पूर्ण

/* Set pitch */
अटल अंतरभूत व्योम set_lwidth(काष्ठा tridentfb_par *par, पूर्णांक width)
अणु
	ग_लिखो3X4(par, VGA_CRTC_OFFSET, width & 0xFF);
	/* chips older than TGUI9660 have only 1 width bit in AddColReg */
	/* touching the other one अवरोधs I2C/DDC */
	अगर (par->chip_id == TGUI9440 || par->chip_id == CYBER9320)
		ग_लिखो3X4(par, AddColReg,
		     (पढ़ो3X4(par, AddColReg) & 0xEF) | ((width & 0x100) >> 4));
	अन्यथा
		ग_लिखो3X4(par, AddColReg,
		     (पढ़ो3X4(par, AddColReg) & 0xCF) | ((width & 0x300) >> 4));
पूर्ण

/* For resolutions smaller than FP resolution stretch */
अटल व्योम screen_stretch(काष्ठा tridentfb_par *par)
अणु
	अगर (par->chip_id != CYBERBLADEXPAi1)
		ग_लिखो3CE(par, BiosReg, 0);
	अन्यथा
		ग_लिखो3CE(par, BiosReg, 8);
	ग_लिखो3CE(par, VertStretch, (पढ़ो3CE(par, VertStretch) & 0x7C) | 1);
	ग_लिखो3CE(par, HorStretch, (पढ़ो3CE(par, HorStretch) & 0x7C) | 1);
पूर्ण

/* For resolutions smaller than FP resolution center */
अटल अंतरभूत व्योम screen_center(काष्ठा tridentfb_par *par)
अणु
	ग_लिखो3CE(par, VertStretch, (पढ़ो3CE(par, VertStretch) & 0x7C) | 0x80);
	ग_लिखो3CE(par, HorStretch, (पढ़ो3CE(par, HorStretch) & 0x7C) | 0x80);
पूर्ण

/* Address of first shown pixel in display memory */
अटल व्योम set_screen_start(काष्ठा tridentfb_par *par, पूर्णांक base)
अणु
	u8 पंचांगp;
	ग_लिखो3X4(par, VGA_CRTC_START_LO, base & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_START_HI, (base & 0xFF00) >> 8);
	पंचांगp = पढ़ो3X4(par, CRTCModuleTest) & 0xDF;
	ग_लिखो3X4(par, CRTCModuleTest, पंचांगp | ((base & 0x10000) >> 11));
	पंचांगp = पढ़ो3X4(par, CRTHiOrd) & 0xF8;
	ग_लिखो3X4(par, CRTHiOrd, पंचांगp | ((base & 0xE0000) >> 17));
पूर्ण

/* Set करोtघड़ी frequency */
अटल व्योम set_vclk(काष्ठा tridentfb_par *par, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक m, n, k;
	अचिन्हित दीर्घ fi, d, di;
	अचिन्हित अक्षर best_m = 0, best_n = 0, best_k = 0;
	अचिन्हित अक्षर hi, lo;
	अचिन्हित अक्षर shअगरt = !is_oldघड़ी(par->chip_id) ? 2 : 1;

	d = 20000;
	क्रम (k = shअगरt; k >= 0; k--)
		क्रम (m = 1; m < 32; m++) अणु
			n = ((m + 2) << shअगरt) - 8;
			क्रम (n = (n < 0 ? 0 : n); n < 122; n++) अणु
				fi = ((14318l * (n + 8)) / (m + 2)) >> k;
				di = असल(fi - freq);
				अगर (di < d || (di == d && k == best_k)) अणु
					d = di;
					best_n = n;
					best_m = m;
					best_k = k;
				पूर्ण
				अगर (fi > freq)
					अवरोध;
			पूर्ण
		पूर्ण

	अगर (is_oldघड़ी(par->chip_id)) अणु
		lo = best_n | (best_m << 7);
		hi = (best_m >> 1) | (best_k << 4);
	पूर्ण अन्यथा अणु
		lo = best_n;
		hi = best_m | (best_k << 6);
	पूर्ण

	अगर (is3Dchip(par->chip_id)) अणु
		vga_mm_wseq(par->io_virt, ClockHigh, hi);
		vga_mm_wseq(par->io_virt, ClockLow, lo);
	पूर्ण अन्यथा अणु
		t_outb(par, lo, 0x43C8);
		t_outb(par, hi, 0x43C9);
	पूर्ण
	debug("VCLK = %X %X\n", hi, lo);
पूर्ण

/* Set number of lines क्रम flat panels*/
अटल व्योम set_number_of_lines(काष्ठा tridentfb_par *par, पूर्णांक lines)
अणु
	पूर्णांक पंचांगp = पढ़ो3CE(par, CyberEnhance) & 0x8F;
	अगर (lines > 1024)
		पंचांगp |= 0x50;
	अन्यथा अगर (lines > 768)
		पंचांगp |= 0x30;
	अन्यथा अगर (lines > 600)
		पंचांगp |= 0x20;
	अन्यथा अगर (lines > 480)
		पंचांगp |= 0x10;
	ग_लिखो3CE(par, CyberEnhance, पंचांगp);
पूर्ण

/*
 * If we see that FP is active we assume we have one.
 * Otherwise we have a CRT display. User can override.
 */
अटल पूर्णांक is_flatpanel(काष्ठा tridentfb_par *par)
अणु
	अगर (fp)
		वापस 1;
	अगर (crt || !iscyber(par->chip_id))
		वापस 0;
	वापस (पढ़ो3CE(par, FPConfig) & 0x10) ? 1 : 0;
पूर्ण

/* Try detecting the video memory size */
अटल अचिन्हित पूर्णांक get_memsize(काष्ठा tridentfb_par *par)
अणु
	अचिन्हित अक्षर पंचांगp, पंचांगp2;
	अचिन्हित पूर्णांक k;

	/* If memory size provided by user */
	अगर (memsize)
		k = memsize * Kb;
	अन्यथा
		चयन (par->chip_id) अणु
		हाल CYBER9525DVD:
			k = 2560 * Kb;
			अवरोध;
		शेष:
			पंचांगp = पढ़ो3X4(par, SPR) & 0x0F;
			चयन (पंचांगp) अणु

			हाल 0x01:
				k = 512 * Kb;
				अवरोध;
			हाल 0x02:
				k = 6 * Mb;	/* XP */
				अवरोध;
			हाल 0x03:
				k = 1 * Mb;
				अवरोध;
			हाल 0x04:
				k = 8 * Mb;
				अवरोध;
			हाल 0x06:
				k = 10 * Mb;	/* XP */
				अवरोध;
			हाल 0x07:
				k = 2 * Mb;
				अवरोध;
			हाल 0x08:
				k = 12 * Mb;	/* XP */
				अवरोध;
			हाल 0x0A:
				k = 14 * Mb;	/* XP */
				अवरोध;
			हाल 0x0C:
				k = 16 * Mb;	/* XP */
				अवरोध;
			हाल 0x0E:		/* XP */

				पंचांगp2 = vga_mm_rseq(par->io_virt, 0xC1);
				चयन (पंचांगp2) अणु
				हाल 0x00:
					k = 20 * Mb;
					अवरोध;
				हाल 0x01:
					k = 24 * Mb;
					अवरोध;
				हाल 0x10:
					k = 28 * Mb;
					अवरोध;
				हाल 0x11:
					k = 32 * Mb;
					अवरोध;
				शेष:
					k = 1 * Mb;
					अवरोध;
				पूर्ण
				अवरोध;

			हाल 0x0F:
				k = 4 * Mb;
				अवरोध;
			शेष:
				k = 1 * Mb;
				अवरोध;
			पूर्ण
		पूर्ण

	k -= memdअगरf * Kb;
	output("framebuffer size = %d Kb\n", k / Kb);
	वापस k;
पूर्ण

/* See अगर we can handle the video mode described in var */
अटल पूर्णांक tridentfb_check_var(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info)
अणु
	काष्ठा tridentfb_par *par = info->par;
	पूर्णांक bpp = var->bits_per_pixel;
	पूर्णांक line_length;
	पूर्णांक ramdac = 230000; /* 230MHz क्रम most 3D chips */
	debug("enter\n");

	/* check color depth */
	अगर (bpp == 24)
		bpp = var->bits_per_pixel = 32;
	अगर (bpp != 8 && bpp != 16 && bpp != 32)
		वापस -EINVAL;
	अगर (par->chip_id == TGUI9440 && bpp == 32)
		वापस -EINVAL;
	/* check whether resolution fits on panel and in memory */
	अगर (par->flatpanel && nativex && var->xres > nativex)
		वापस -EINVAL;
	/* various resolution checks */
	var->xres = (var->xres + 7) & ~0x7;
	अगर (var->xres > var->xres_भव)
		var->xres_भव = var->xres;
	अगर (var->yres > var->yres_भव)
		var->yres_भव = var->yres;
	अगर (var->xres_भव > 4095 || var->yres > 2048)
		वापस -EINVAL;
	/* prevent from position overflow क्रम acceleration */
	अगर (var->yres_भव > 0xffff)
		वापस -EINVAL;
	line_length = var->xres_भव * bpp / 8;

	अगर (!is3Dchip(par->chip_id) &&
	    !(info->flags & FBINFO_HWACCEL_DISABLED)) अणु
		/* acceleration requires line length to be घातer of 2 */
		अगर (line_length <= 512)
			var->xres_भव = 512 * 8 / bpp;
		अन्यथा अगर (line_length <= 1024)
			var->xres_भव = 1024 * 8 / bpp;
		अन्यथा अगर (line_length <= 2048)
			var->xres_भव = 2048 * 8 / bpp;
		अन्यथा अगर (line_length <= 4096)
			var->xres_भव = 4096 * 8 / bpp;
		अन्यथा अगर (line_length <= 8192)
			var->xres_भव = 8192 * 8 / bpp;
		अन्यथा
			वापस -EINVAL;

		line_length = var->xres_भव * bpp / 8;
	पूर्ण

	/* datasheet specअगरies how to set panning only up to 4 MB */
	अगर (line_length * (var->yres_भव - var->yres) > (4 << 20))
		var->yres_भव = ((4 << 20) / line_length) + var->yres;

	अगर (line_length * var->yres_भव > info->fix.smem_len)
		वापस -EINVAL;

	चयन (bpp) अणु
	हाल 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green = var->red;
		var->blue = var->red;
		अवरोध;
	हाल 16:
		var->red.offset = 11;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		अवरोध;
	हाल 32:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (is_xp(par->chip_id))
		ramdac = 350000;

	चयन (par->chip_id) अणु
	हाल TGUI9440:
		ramdac = (bpp >= 16) ? 45000 : 90000;
		अवरोध;
	हाल CYBER9320:
	हाल TGUI9660:
		ramdac = 135000;
		अवरोध;
	हाल PROVIDIA9685:
	हाल CYBER9388:
	हाल CYBER9382:
	हाल CYBER9385:
		ramdac = 170000;
		अवरोध;
	पूर्ण

	/* The घड़ी is द्विगुनd क्रम 32 bpp */
	अगर (bpp == 32)
		ramdac /= 2;

	अगर (PICOS2KHZ(var->pixघड़ी) > ramdac)
		वापस -EINVAL;

	debug("exit\n");

	वापस 0;

पूर्ण

/* Pan the display */
अटल पूर्णांक tridentfb_pan_display(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info)
अणु
	काष्ठा tridentfb_par *par = info->par;
	अचिन्हित पूर्णांक offset;

	debug("enter\n");
	offset = (var->xoffset + (var->yoffset * info->var.xres_भव))
		* info->var.bits_per_pixel / 32;
	set_screen_start(par, offset);
	debug("exit\n");
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम shaकरोwmode_on(काष्ठा tridentfb_par *par)
अणु
	ग_लिखो3CE(par, CyberControl, पढ़ो3CE(par, CyberControl) | 0x81);
पूर्ण

अटल अंतरभूत व्योम shaकरोwmode_off(काष्ठा tridentfb_par *par)
अणु
	ग_लिखो3CE(par, CyberControl, पढ़ो3CE(par, CyberControl) & 0x7E);
पूर्ण

/* Set the hardware to the requested video mode */
अटल पूर्णांक tridentfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा tridentfb_par *par = info->par;
	u32 htotal, hdispend, hsyncstart, hsyncend, hblankstart, hblankend;
	u32 vtotal, vdispend, vsyncstart, vsyncend, vblankstart, vblankend;
	काष्ठा fb_var_screeninfo *var = &info->var;
	पूर्णांक bpp = var->bits_per_pixel;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित दीर्घ vclk;

	debug("enter\n");
	hdispend = var->xres / 8 - 1;
	hsyncstart = (var->xres + var->right_margin) / 8;
	hsyncend = (var->xres + var->right_margin + var->hsync_len) / 8;
	htotal = (var->xres + var->left_margin + var->right_margin +
		  var->hsync_len) / 8 - 5;
	hblankstart = hdispend + 1;
	hblankend = htotal + 3;

	vdispend = var->yres - 1;
	vsyncstart = var->yres + var->lower_margin;
	vsyncend = vsyncstart + var->vsync_len;
	vtotal = var->upper_margin + vsyncend - 2;
	vblankstart = vdispend + 1;
	vblankend = vtotal;

	अगर (info->var.vmode & FB_VMODE_INTERLACED) अणु
		vtotal /= 2;
		vdispend /= 2;
		vsyncstart /= 2;
		vsyncend /= 2;
		vblankstart /= 2;
		vblankend /= 2;
	पूर्ण

	enable_mmio(par);
	crtc_unlock(par);
	ग_लिखो3CE(par, CyberControl, 8);
	पंचांगp = 0xEB;
	अगर (var->sync & FB_SYNC_HOR_HIGH_ACT)
		पंचांगp &= ~0x40;
	अगर (var->sync & FB_SYNC_VERT_HIGH_ACT)
		पंचांगp &= ~0x80;

	अगर (par->flatpanel && var->xres < nativex) अणु
		/*
		 * on flat panels with native size larger
		 * than requested resolution decide whether
		 * we stretch or center
		 */
		t_outb(par, पंचांगp | 0xC0, VGA_MIS_W);

		shaकरोwmode_on(par);

		अगर (center)
			screen_center(par);
		अन्यथा अगर (stretch)
			screen_stretch(par);

	पूर्ण अन्यथा अणु
		t_outb(par, पंचांगp, VGA_MIS_W);
		ग_लिखो3CE(par, CyberControl, 8);
	पूर्ण

	/* vertical timing values */
	ग_लिखो3X4(par, VGA_CRTC_V_TOTAL, vtotal & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_V_DISP_END, vdispend & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_V_SYNC_START, vsyncstart & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_V_SYNC_END, (vsyncend & 0x0F));
	ग_लिखो3X4(par, VGA_CRTC_V_BLANK_START, vblankstart & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_V_BLANK_END, vblankend & 0xFF);

	/* horizontal timing values */
	ग_लिखो3X4(par, VGA_CRTC_H_TOTAL, htotal & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_H_DISP, hdispend & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_H_SYNC_START, hsyncstart & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_H_SYNC_END,
		 (hsyncend & 0x1F) | ((hblankend & 0x20) << 2));
	ग_लिखो3X4(par, VGA_CRTC_H_BLANK_START, hblankstart & 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_H_BLANK_END, hblankend & 0x1F);

	/* higher bits of vertical timing values */
	पंचांगp = 0x10;
	अगर (vtotal & 0x100) पंचांगp |= 0x01;
	अगर (vdispend & 0x100) पंचांगp |= 0x02;
	अगर (vsyncstart & 0x100) पंचांगp |= 0x04;
	अगर (vblankstart & 0x100) पंचांगp |= 0x08;

	अगर (vtotal & 0x200) पंचांगp |= 0x20;
	अगर (vdispend & 0x200) पंचांगp |= 0x40;
	अगर (vsyncstart & 0x200) पंचांगp |= 0x80;
	ग_लिखो3X4(par, VGA_CRTC_OVERFLOW, पंचांगp);

	पंचांगp = पढ़ो3X4(par, CRTHiOrd) & 0x07;
	पंचांगp |= 0x08;	/* line compare bit 10 */
	अगर (vtotal & 0x400) पंचांगp |= 0x80;
	अगर (vblankstart & 0x400) पंचांगp |= 0x40;
	अगर (vsyncstart & 0x400) पंचांगp |= 0x20;
	अगर (vdispend & 0x400) पंचांगp |= 0x10;
	ग_लिखो3X4(par, CRTHiOrd, पंचांगp);

	पंचांगp = (htotal >> 8) & 0x01;
	पंचांगp |= (hdispend >> 7) & 0x02;
	पंचांगp |= (hsyncstart >> 5) & 0x08;
	पंचांगp |= (hblankstart >> 4) & 0x10;
	ग_लिखो3X4(par, HorizOverflow, पंचांगp);

	पंचांगp = 0x40;
	अगर (vblankstart & 0x200) पंचांगp |= 0x20;
//FIXME	अगर (info->var.vmode & FB_VMODE_DOUBLE) पंचांगp |= 0x80;  /* द्विगुन scan क्रम 200 line modes */
	ग_लिखो3X4(par, VGA_CRTC_MAX_SCAN, पंचांगp);

	ग_लिखो3X4(par, VGA_CRTC_LINE_COMPARE, 0xFF);
	ग_लिखो3X4(par, VGA_CRTC_PRESET_ROW, 0);
	ग_लिखो3X4(par, VGA_CRTC_MODE, 0xC3);

	ग_लिखो3X4(par, LinearAddReg, 0x20);	/* enable linear addressing */

	पंचांगp = (info->var.vmode & FB_VMODE_INTERLACED) ? 0x84 : 0x80;
	/* enable access extended memory */
	ग_लिखो3X4(par, CRTCModuleTest, पंचांगp);
	पंचांगp = पढ़ो3CE(par, MiscIntContReg) & ~0x4;
	अगर (info->var.vmode & FB_VMODE_INTERLACED)
		पंचांगp |= 0x4;
	ग_लिखो3CE(par, MiscIntContReg, पंचांगp);

	/* enable GE क्रम text acceleration */
	ग_लिखो3X4(par, GraphEngReg, 0x80);

	चयन (bpp) अणु
	हाल 8:
		पंचांगp = 0x00;
		अवरोध;
	हाल 16:
		पंचांगp = 0x05;
		अवरोध;
	हाल 24:
		पंचांगp = 0x29;
		अवरोध;
	हाल 32:
		पंचांगp = 0x09;
		अवरोध;
	पूर्ण

	ग_लिखो3X4(par, PixelBusReg, पंचांगp);

	पंचांगp = पढ़ो3X4(par, DRAMControl);
	अगर (!is_oldprotect(par->chip_id))
		पंचांगp |= 0x10;
	अगर (iscyber(par->chip_id))
		पंचांगp |= 0x20;
	ग_लिखो3X4(par, DRAMControl, पंचांगp);	/* both IO, linear enable */

	ग_लिखो3X4(par, InterfaceSel, पढ़ो3X4(par, InterfaceSel) | 0x40);
	अगर (!is_xp(par->chip_id))
		ग_लिखो3X4(par, Perक्रमmance, पढ़ो3X4(par, Perक्रमmance) | 0x10);
	/* MMIO & PCI पढ़ो and ग_लिखो burst enable */
	अगर (par->chip_id != TGUI9440 && par->chip_id != IMAGE975)
		ग_लिखो3X4(par, PCIReg, पढ़ो3X4(par, PCIReg) | 0x06);

	vga_mm_wseq(par->io_virt, 0, 3);
	vga_mm_wseq(par->io_virt, 1, 1); /* set अक्षर घड़ी 8 करोts wide */
	/* enable 4 maps because needed in chain4 mode */
	vga_mm_wseq(par->io_virt, 2, 0x0F);
	vga_mm_wseq(par->io_virt, 3, 0);
	vga_mm_wseq(par->io_virt, 4, 0x0E); /* memory mode enable biपंचांगaps ?? */

	/* convert from picoseconds to kHz */
	vclk = PICOS2KHZ(info->var.pixघड़ी);

	/* भागide घड़ी by 2 अगर 32bpp chain4 mode display and CPU path */
	पंचांगp = पढ़ो3CE(par, MiscExtFunc) & 0xF0;
	अगर (bpp == 32 || (par->chip_id == TGUI9440 && bpp == 16)) अणु
		पंचांगp |= 8;
		vclk *= 2;
	पूर्ण
	set_vclk(par, vclk);
	ग_लिखो3CE(par, MiscExtFunc, पंचांगp | 0x12);
	ग_लिखो3CE(par, 0x5, 0x40);	/* no CGA compat, allow 256 col */
	ग_लिखो3CE(par, 0x6, 0x05);	/* graphics mode */
	ग_लिखो3CE(par, 0x7, 0x0F);	/* planes? */

	/* graphics mode and support 256 color modes */
	ग_लिखोAttr(par, 0x10, 0x41);
	ग_लिखोAttr(par, 0x12, 0x0F);	/* planes */
	ग_लिखोAttr(par, 0x13, 0);	/* horizontal pel panning */

	/* colors */
	क्रम (पंचांगp = 0; पंचांगp < 0x10; पंचांगp++)
		ग_लिखोAttr(par, पंचांगp, पंचांगp);
	fb_पढ़ोb(par->io_virt + VGA_IS1_RC);	/* flip-flop to index */
	t_outb(par, 0x20, VGA_ATT_W);		/* enable attr */

	चयन (bpp) अणु
	हाल 8:
		पंचांगp = 0;
		अवरोध;
	हाल 16:
		पंचांगp = 0x30;
		अवरोध;
	हाल 24:
	हाल 32:
		पंचांगp = 0xD0;
		अवरोध;
	पूर्ण

	t_inb(par, VGA_PEL_IW);
	t_inb(par, VGA_PEL_MSK);
	t_inb(par, VGA_PEL_MSK);
	t_inb(par, VGA_PEL_MSK);
	t_inb(par, VGA_PEL_MSK);
	t_outb(par, पंचांगp, VGA_PEL_MSK);
	t_inb(par, VGA_PEL_IW);

	अगर (par->flatpanel)
		set_number_of_lines(par, info->var.yres);
	info->fix.line_length = info->var.xres_भव * bpp / 8;
	set_lwidth(par, info->fix.line_length / 8);

	अगर (!(info->flags & FBINFO_HWACCEL_DISABLED))
		par->init_accel(par, info->var.xres_भव, bpp);

	info->fix.visual = (bpp == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->cmap.len = (bpp == 8) ? 256 : 16;
	debug("exit\n");
	वापस 0;
पूर्ण

/* Set one color रेजिस्टर */
अटल पूर्णांक tridentfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			       अचिन्हित blue, अचिन्हित transp,
			       काष्ठा fb_info *info)
अणु
	पूर्णांक bpp = info->var.bits_per_pixel;
	काष्ठा tridentfb_par *par = info->par;

	अगर (regno >= info->cmap.len)
		वापस 1;

	अगर (bpp == 8) अणु
		t_outb(par, 0xFF, VGA_PEL_MSK);
		t_outb(par, regno, VGA_PEL_IW);

		t_outb(par, red >> 10, VGA_PEL_D);
		t_outb(par, green >> 10, VGA_PEL_D);
		t_outb(par, blue >> 10, VGA_PEL_D);

	पूर्ण अन्यथा अगर (regno < 16) अणु
		अगर (bpp == 16) अणु	/* RGB 565 */
			u32 col;

			col = (red & 0xF800) | ((green & 0xFC00) >> 5) |
				((blue & 0xF800) >> 11);
			col |= col << 16;
			((u32 *)(info->pseuकरो_palette))[regno] = col;
		पूर्ण अन्यथा अगर (bpp == 32)		/* ARGB 8888 */
			((u32 *)info->pseuकरो_palette)[regno] =
				((transp & 0xFF00) << 16)	|
				((red & 0xFF00) << 8)		|
				((green & 0xFF00))		|
				((blue & 0xFF00) >> 8);
	पूर्ण

	वापस 0;
पूर्ण

/* Try blanking the screen. For flat panels it करोes nothing */
अटल पूर्णांक tridentfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	अचिन्हित अक्षर PMCont, DPMSCont;
	काष्ठा tridentfb_par *par = info->par;

	debug("enter\n");
	अगर (par->flatpanel)
		वापस 0;
	t_outb(par, 0x04, 0x83C8); /* Read DPMS Control */
	PMCont = t_inb(par, 0x83C6) & 0xFC;
	DPMSCont = पढ़ो3CE(par, PowerStatus) & 0xFC;
	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		/* Screen: On, HSync: On, VSync: On */
	हाल FB_BLANK_NORMAL:
		/* Screen: Off, HSync: On, VSync: On */
		PMCont |= 0x03;
		DPMSCont |= 0x00;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		/* Screen: Off, HSync: Off, VSync: On */
		PMCont |= 0x02;
		DPMSCont |= 0x01;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		/* Screen: Off, HSync: On, VSync: Off */
		PMCont |= 0x02;
		DPMSCont |= 0x02;
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		/* Screen: Off, HSync: Off, VSync: Off */
		PMCont |= 0x00;
		DPMSCont |= 0x03;
		अवरोध;
	पूर्ण

	ग_लिखो3CE(par, PowerStatus, DPMSCont);
	t_outb(par, 4, 0x83C8);
	t_outb(par, PMCont, 0x83C6);

	debug("exit\n");

	/* let fbcon करो a softblank क्रम us */
	वापस (blank_mode == FB_BLANK_NORMAL) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops tridentfb_ops = अणु
	.owner = THIS_MODULE,
	.fb_setcolreg = tridentfb_setcolreg,
	.fb_pan_display = tridentfb_pan_display,
	.fb_blank = tridentfb_blank,
	.fb_check_var = tridentfb_check_var,
	.fb_set_par = tridentfb_set_par,
	.fb_fillrect = tridentfb_fillrect,
	.fb_copyarea = tridentfb_copyarea,
	.fb_imageblit = tridentfb_imageblit,
	.fb_sync = tridentfb_sync,
पूर्ण;

अटल पूर्णांक trident_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err;
	अचिन्हित अक्षर revision;
	काष्ठा fb_info *info;
	काष्ठा tridentfb_par *शेष_par;
	पूर्णांक chip3D;
	पूर्णांक chip_id;
	bool found = false;

	err = pci_enable_device(dev);
	अगर (err)
		वापस err;

	info = framebuffer_alloc(माप(काष्ठा tridentfb_par), &dev->dev);
	अगर (!info)
		वापस -ENOMEM;
	शेष_par = info->par;

	chip_id = id->device;

	/* If PCI id is 0x9660 then further detect chip type */

	अगर (chip_id == TGUI9660) अणु
		revision = vga_io_rseq(RevisionID);

		चयन (revision) अणु
		हाल 0x21:
			chip_id = PROVIDIA9685;
			अवरोध;
		हाल 0x22:
		हाल 0x23:
			chip_id = CYBER9397;
			अवरोध;
		हाल 0x2A:
			chip_id = CYBER9397DVD;
			अवरोध;
		हाल 0x30:
		हाल 0x33:
		हाल 0x34:
		हाल 0x35:
		हाल 0x38:
		हाल 0x3A:
		हाल 0xB3:
			chip_id = CYBER9385;
			अवरोध;
		हाल 0x40 ... 0x43:
			chip_id = CYBER9382;
			अवरोध;
		हाल 0x4A:
			chip_id = CYBER9388;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	chip3D = is3Dchip(chip_id);

	अगर (is_xp(chip_id)) अणु
		शेष_par->init_accel = xp_init_accel;
		शेष_par->रुको_engine = xp_रुको_engine;
		शेष_par->fill_rect = xp_fill_rect;
		शेष_par->copy_rect = xp_copy_rect;
		tridentfb_fix.accel = FB_ACCEL_TRIDENT_BLADEXP;
	पूर्ण अन्यथा अगर (is_blade(chip_id)) अणु
		शेष_par->init_accel = blade_init_accel;
		शेष_par->रुको_engine = blade_रुको_engine;
		शेष_par->fill_rect = blade_fill_rect;
		शेष_par->copy_rect = blade_copy_rect;
		शेष_par->image_blit = blade_image_blit;
		tridentfb_fix.accel = FB_ACCEL_TRIDENT_BLADE3D;
	पूर्ण अन्यथा अगर (chip3D) अणु			/* 3DImage family left */
		शेष_par->init_accel = image_init_accel;
		शेष_par->रुको_engine = image_रुको_engine;
		शेष_par->fill_rect = image_fill_rect;
		शेष_par->copy_rect = image_copy_rect;
		tridentfb_fix.accel = FB_ACCEL_TRIDENT_3DIMAGE;
	पूर्ण अन्यथा अणु 				/* TGUI 9440/96XX family */
		शेष_par->init_accel = tgui_init_accel;
		शेष_par->रुको_engine = xp_रुको_engine;
		शेष_par->fill_rect = tgui_fill_rect;
		शेष_par->copy_rect = tgui_copy_rect;
		tridentfb_fix.accel = FB_ACCEL_TRIDENT_TGUI;
	पूर्ण

	शेष_par->chip_id = chip_id;

	/* setup MMIO region */
	tridentfb_fix.mmio_start = pci_resource_start(dev, 1);
	tridentfb_fix.mmio_len = pci_resource_len(dev, 1);

	अगर (!request_mem_region(tridentfb_fix.mmio_start,
				tridentfb_fix.mmio_len, "tridentfb")) अणु
		debug("request_region failed!\n");
		framebuffer_release(info);
		वापस -1;
	पूर्ण

	शेष_par->io_virt = ioremap(tridentfb_fix.mmio_start,
					       tridentfb_fix.mmio_len);

	अगर (!शेष_par->io_virt) अणु
		debug("ioremap failed\n");
		err = -1;
		जाओ out_unmap1;
	पूर्ण

	enable_mmio(शेष_par);

	/* setup framebuffer memory */
	tridentfb_fix.smem_start = pci_resource_start(dev, 0);
	tridentfb_fix.smem_len = get_memsize(शेष_par);

	अगर (!request_mem_region(tridentfb_fix.smem_start,
				tridentfb_fix.smem_len, "tridentfb")) अणु
		debug("request_mem_region failed!\n");
		disable_mmio(info->par);
		err = -1;
		जाओ out_unmap1;
	पूर्ण

	info->screen_base = ioremap(tridentfb_fix.smem_start,
					    tridentfb_fix.smem_len);

	अगर (!info->screen_base) अणु
		debug("ioremap failed\n");
		err = -1;
		जाओ out_unmap2;
	पूर्ण

	शेष_par->flatpanel = is_flatpanel(शेष_par);

	अगर (शेष_par->flatpanel)
		nativex = get_nativex(शेष_par);

	info->fix = tridentfb_fix;
	info->fbops = &tridentfb_ops;
	info->pseuकरो_palette = शेष_par->pseuकरो_pal;

	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	अगर (!noaccel && शेष_par->init_accel) अणु
		info->flags &= ~FBINFO_HWACCEL_DISABLED;
		info->flags |= FBINFO_HWACCEL_COPYAREA;
		info->flags |= FBINFO_HWACCEL_FILLRECT;
	पूर्ण अन्यथा
		info->flags |= FBINFO_HWACCEL_DISABLED;

	अगर (is_blade(chip_id) && chip_id != BLADE3D)
		info->flags |= FBINFO_READS_FAST;

	info->pixmap.addr = kदो_स्मृति(4096, GFP_KERNEL);
	अगर (!info->pixmap.addr) अणु
		err = -ENOMEM;
		जाओ out_unmap2;
	पूर्ण

	info->pixmap.size = 4096;
	info->pixmap.buf_align = 4;
	info->pixmap.scan_align = 1;
	info->pixmap.access_align = 32;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;
	info->var.bits_per_pixel = 8;

	अगर (शेष_par->image_blit) अणु
		info->flags |= FBINFO_HWACCEL_IMAGEBLIT;
		info->pixmap.scan_align = 4;
	पूर्ण

	अगर (noaccel) अणु
		prपूर्णांकk(KERN_DEBUG "disabling acceleration\n");
		info->flags |= FBINFO_HWACCEL_DISABLED;
		info->pixmap.scan_align = 1;
	पूर्ण

	अगर (tridentfb_setup_ddc_bus(info) == 0) अणु
		u8 *edid = fb_ddc_पढ़ो(&शेष_par->ddc_adapter);

		शेष_par->ddc_रेजिस्टरed = true;
		अगर (edid) अणु
			fb_edid_to_monspecs(edid, &info->monspecs);
			kमुक्त(edid);
			अगर (!info->monspecs.modedb)
				dev_err(info->device, "error getting mode database\n");
			अन्यथा अणु
				स्थिर काष्ठा fb_videomode *m;

				fb_videomode_to_modelist(info->monspecs.modedb,
						 info->monspecs.modedb_len,
						 &info->modelist);
				m = fb_find_best_display(&info->monspecs,
							 &info->modelist);
				अगर (m) अणु
					fb_videomode_to_var(&info->var, m);
					/* fill all other info->var's fields */
					अगर (tridentfb_check_var(&info->var,
								info) == 0)
						found = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!mode_option && !found)
		mode_option = "640x480-8@60";

	/* Prepare startup mode */
	अगर (mode_option) अणु
		err = fb_find_mode(&info->var, info, mode_option,
				   info->monspecs.modedb,
				   info->monspecs.modedb_len,
				   शून्य, info->var.bits_per_pixel);
		अगर (!err || err == 4) अणु
			err = -EINVAL;
			dev_err(info->device, "mode %s not found\n",
								mode_option);
			fb_destroy_modedb(info->monspecs.modedb);
			info->monspecs.modedb = शून्य;
			जाओ out_unmap2;
		पूर्ण
	पूर्ण

	fb_destroy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = शून्य;

	err = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (err < 0)
		जाओ out_unmap2;

	info->var.activate |= FB_ACTIVATE_NOW;
	info->device = &dev->dev;
	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR "tridentfb: could not register framebuffer\n");
		fb_dealloc_cmap(&info->cmap);
		err = -EINVAL;
		जाओ out_unmap2;
	पूर्ण
	output("fb%d: %s frame buffer device %dx%d-%dbpp\n",
	   info->node, info->fix.id, info->var.xres,
	   info->var.yres, info->var.bits_per_pixel);

	pci_set_drvdata(dev, info);
	वापस 0;

out_unmap2:
	अगर (शेष_par->ddc_रेजिस्टरed)
		i2c_del_adapter(&शेष_par->ddc_adapter);
	kमुक्त(info->pixmap.addr);
	अगर (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(tridentfb_fix.smem_start, tridentfb_fix.smem_len);
	disable_mmio(info->par);
out_unmap1:
	अगर (शेष_par->io_virt)
		iounmap(शेष_par->io_virt);
	release_mem_region(tridentfb_fix.mmio_start, tridentfb_fix.mmio_len);
	framebuffer_release(info);
	वापस err;
पूर्ण

अटल व्योम trident_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);
	काष्ठा tridentfb_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	अगर (par->ddc_रेजिस्टरed)
		i2c_del_adapter(&par->ddc_adapter);
	iounmap(par->io_virt);
	iounmap(info->screen_base);
	release_mem_region(tridentfb_fix.smem_start, tridentfb_fix.smem_len);
	release_mem_region(tridentfb_fix.mmio_start, tridentfb_fix.mmio_len);
	kमुक्त(info->pixmap.addr);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
पूर्ण

/* List of boards that we are trying to support */
अटल स्थिर काष्ठा pci_device_id trident_devices[] = अणु
	अणुPCI_VENDOR_ID_TRIDENT,	BLADE3D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEi7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEi7D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEi1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEi1D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEAi1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEAi1D, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEE4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	TGUI9440, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	TGUI9660, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	IMAGE975, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	IMAGE985, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBER9320, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBER9388, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBER9520, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBER9525DVD, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBER9397, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBER9397DVD, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEXPAi1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEXPm8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणुPCI_VENDOR_ID_TRIDENT,	CYBERBLADEXPm16, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, trident_devices);

अटल काष्ठा pci_driver tridentfb_pci_driver = अणु
	.name = "tridentfb",
	.id_table = trident_devices,
	.probe = trident_pci_probe,
	.हटाओ = trident_pci_हटाओ,
पूर्ण;

/*
 * Parse user specअगरied options (`video=trident:')
 * example:
 *	video=trident:800x600,bpp=16,noaccel
 */
#अगर_अघोषित MODULE
अटल पूर्णांक __init tridentfb_setup(अक्षर *options)
अणु
	अक्षर *opt;
	अगर (!options || !*options)
		वापस 0;
	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;
		अगर (!म_भेदन(opt, "noaccel", 7))
			noaccel = 1;
		अन्यथा अगर (!म_भेदन(opt, "fp", 2))
			fp = 1;
		अन्यथा अगर (!म_भेदन(opt, "crt", 3))
			fp = 0;
		अन्यथा अगर (!म_भेदन(opt, "bpp=", 4))
			bpp = simple_म_से_अदीर्घ(opt + 4, शून्य, 0);
		अन्यथा अगर (!म_भेदन(opt, "center", 6))
			center = 1;
		अन्यथा अगर (!म_भेदन(opt, "stretch", 7))
			stretch = 1;
		अन्यथा अगर (!म_भेदन(opt, "memsize=", 8))
			memsize = simple_म_से_अदीर्घ(opt + 8, शून्य, 0);
		अन्यथा अगर (!म_भेदन(opt, "memdiff=", 8))
			memdअगरf = simple_म_से_अदीर्घ(opt + 8, शून्य, 0);
		अन्यथा अगर (!म_भेदन(opt, "nativex=", 8))
			nativex = simple_म_से_अदीर्घ(opt + 8, शून्य, 0);
		अन्यथा
			mode_option = opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init tridentfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("tridentfb", &option))
		वापस -ENODEV;
	tridentfb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&tridentfb_pci_driver);
पूर्ण

अटल व्योम __निकास tridentfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&tridentfb_pci_driver);
पूर्ण

module_init(tridentfb_init);
module_निकास(tridentfb_निकास);

MODULE_AUTHOR("Jani Monoses <jani@iv.ro>");
MODULE_DESCRIPTION("Framebuffer driver for Trident cards");
MODULE_LICENSE("GPL");
MODULE_ALIAS("cyblafb");

