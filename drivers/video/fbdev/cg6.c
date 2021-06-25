<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* cg6.c: CGSIX (GX, GXplus, TGX) frame buffer driver
 *
 * Copyright (C) 2003, 2006 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996,1998 Jakub Jelinek (jj@ultra.linux.cz)
 * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)
 * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)
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
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/fbपन.स>

#समावेश "sbuslib.h"

/*
 * Local functions.
 */

अटल पूर्णांक cg6_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			 अचिन्हित, काष्ठा fb_info *);
अटल पूर्णांक cg6_blank(पूर्णांक, काष्ठा fb_info *);

अटल व्योम cg6_imageblit(काष्ठा fb_info *, स्थिर काष्ठा fb_image *);
अटल व्योम cg6_fillrect(काष्ठा fb_info *, स्थिर काष्ठा fb_fillrect *);
अटल व्योम cg6_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area);
अटल पूर्णांक cg6_sync(काष्ठा fb_info *);
अटल पूर्णांक cg6_mmap(काष्ठा fb_info *, काष्ठा vm_area_काष्ठा *);
अटल पूर्णांक cg6_ioctl(काष्ठा fb_info *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
अटल पूर्णांक cg6_pan_display(काष्ठा fb_var_screeninfo *, काष्ठा fb_info *);

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops cg6_ops = अणु
	.owner			= THIS_MODULE,
	.fb_setcolreg		= cg6_setcolreg,
	.fb_blank		= cg6_blank,
	.fb_pan_display		= cg6_pan_display,
	.fb_fillrect		= cg6_fillrect,
	.fb_copyarea		= cg6_copyarea,
	.fb_imageblit		= cg6_imageblit,
	.fb_sync		= cg6_sync,
	.fb_mmap		= cg6_mmap,
	.fb_ioctl		= cg6_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.fb_compat_ioctl	= sbusfb_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

/* Offset of पूर्णांकeresting काष्ठाures in the OBIO space */
/*
 * Brooktree is the video dac and is funny to program on the cg6.
 * (it's even funnier on the cg3)
 * The FBC could be the frame buffer control
 * The FHC could is the frame buffer hardware control.
 */
#घोषणा CG6_ROM_OFFSET			0x0UL
#घोषणा CG6_BROOKTREE_OFFSET		0x200000UL
#घोषणा CG6_DHC_OFFSET			0x240000UL
#घोषणा CG6_ALT_OFFSET			0x280000UL
#घोषणा CG6_FHC_OFFSET			0x300000UL
#घोषणा CG6_THC_OFFSET			0x301000UL
#घोषणा CG6_FBC_OFFSET			0x700000UL
#घोषणा CG6_TEC_OFFSET			0x701000UL
#घोषणा CG6_RAM_OFFSET			0x800000UL

/* FHC definitions */
#घोषणा CG6_FHC_FBID_SHIFT		24
#घोषणा CG6_FHC_FBID_MASK		255
#घोषणा CG6_FHC_REV_SHIFT		20
#घोषणा CG6_FHC_REV_MASK		15
#घोषणा CG6_FHC_FROP_DISABLE		(1 << 19)
#घोषणा CG6_FHC_ROW_DISABLE		(1 << 18)
#घोषणा CG6_FHC_SRC_DISABLE		(1 << 17)
#घोषणा CG6_FHC_DST_DISABLE		(1 << 16)
#घोषणा CG6_FHC_RESET			(1 << 15)
#घोषणा CG6_FHC_LITTLE_ENDIAN		(1 << 13)
#घोषणा CG6_FHC_RES_MASK		(3 << 11)
#घोषणा CG6_FHC_1024			(0 << 11)
#घोषणा CG6_FHC_1152			(1 << 11)
#घोषणा CG6_FHC_1280			(2 << 11)
#घोषणा CG6_FHC_1600			(3 << 11)
#घोषणा CG6_FHC_CPU_MASK		(3 << 9)
#घोषणा CG6_FHC_CPU_SPARC		(0 << 9)
#घोषणा CG6_FHC_CPU_68020		(1 << 9)
#घोषणा CG6_FHC_CPU_386			(2 << 9)
#घोषणा CG6_FHC_TEST			(1 << 8)
#घोषणा CG6_FHC_TEST_X_SHIFT		4
#घोषणा CG6_FHC_TEST_X_MASK		15
#घोषणा CG6_FHC_TEST_Y_SHIFT		0
#घोषणा CG6_FHC_TEST_Y_MASK		15

/* FBC mode definitions */
#घोषणा CG6_FBC_BLIT_IGNORE		0x00000000
#घोषणा CG6_FBC_BLIT_NOSRC		0x00100000
#घोषणा CG6_FBC_BLIT_SRC		0x00200000
#घोषणा CG6_FBC_BLIT_ILLEGAL		0x00300000
#घोषणा CG6_FBC_BLIT_MASK		0x00300000

#घोषणा CG6_FBC_VBLANK			0x00080000

#घोषणा CG6_FBC_MODE_IGNORE		0x00000000
#घोषणा CG6_FBC_MODE_COLOR8		0x00020000
#घोषणा CG6_FBC_MODE_COLOR1		0x00040000
#घोषणा CG6_FBC_MODE_HRMONO		0x00060000
#घोषणा CG6_FBC_MODE_MASK		0x00060000

#घोषणा CG6_FBC_DRAW_IGNORE		0x00000000
#घोषणा CG6_FBC_DRAW_RENDER		0x00008000
#घोषणा CG6_FBC_DRAW_PICK		0x00010000
#घोषणा CG6_FBC_DRAW_ILLEGAL		0x00018000
#घोषणा CG6_FBC_DRAW_MASK		0x00018000

#घोषणा CG6_FBC_BWRITE0_IGNORE		0x00000000
#घोषणा CG6_FBC_BWRITE0_ENABLE		0x00002000
#घोषणा CG6_FBC_BWRITE0_DISABLE		0x00004000
#घोषणा CG6_FBC_BWRITE0_ILLEGAL		0x00006000
#घोषणा CG6_FBC_BWRITE0_MASK		0x00006000

#घोषणा CG6_FBC_BWRITE1_IGNORE		0x00000000
#घोषणा CG6_FBC_BWRITE1_ENABLE		0x00000800
#घोषणा CG6_FBC_BWRITE1_DISABLE		0x00001000
#घोषणा CG6_FBC_BWRITE1_ILLEGAL		0x00001800
#घोषणा CG6_FBC_BWRITE1_MASK		0x00001800

#घोषणा CG6_FBC_BREAD_IGNORE		0x00000000
#घोषणा CG6_FBC_BREAD_0			0x00000200
#घोषणा CG6_FBC_BREAD_1			0x00000400
#घोषणा CG6_FBC_BREAD_ILLEGAL		0x00000600
#घोषणा CG6_FBC_BREAD_MASK		0x00000600

#घोषणा CG6_FBC_BDISP_IGNORE		0x00000000
#घोषणा CG6_FBC_BDISP_0			0x00000080
#घोषणा CG6_FBC_BDISP_1			0x00000100
#घोषणा CG6_FBC_BDISP_ILLEGAL		0x00000180
#घोषणा CG6_FBC_BDISP_MASK		0x00000180

#घोषणा CG6_FBC_INDEX_MOD		0x00000040
#घोषणा CG6_FBC_INDEX_MASK		0x00000030

/* THC definitions */
#घोषणा CG6_THC_MISC_REV_SHIFT		16
#घोषणा CG6_THC_MISC_REV_MASK		15
#घोषणा CG6_THC_MISC_RESET		(1 << 12)
#घोषणा CG6_THC_MISC_VIDEO		(1 << 10)
#घोषणा CG6_THC_MISC_SYNC		(1 << 9)
#घोषणा CG6_THC_MISC_VSYNC		(1 << 8)
#घोषणा CG6_THC_MISC_SYNC_ENAB		(1 << 7)
#घोषणा CG6_THC_MISC_CURS_RES		(1 << 6)
#घोषणा CG6_THC_MISC_INT_ENAB		(1 << 5)
#घोषणा CG6_THC_MISC_INT		(1 << 4)
#घोषणा CG6_THC_MISC_INIT		0x9f
#घोषणा CG6_THC_CURSOFF			((65536-32) | ((65536-32) << 16))

/* The contents are unknown */
काष्ठा cg6_tec अणु
	पूर्णांक tec_matrix;
	पूर्णांक tec_clip;
	पूर्णांक tec_vdc;
पूर्ण;

काष्ठा cg6_thc अणु
	u32	thc_pad0[512];
	u32	thc_hs;		/* hsync timing */
	u32	thc_hsdvs;
	u32	thc_hd;
	u32	thc_vs;		/* vsync timing */
	u32	thc_vd;
	u32	thc_refresh;
	u32	thc_misc;
	u32	thc_pad1[56];
	u32	thc_cursxy;	/* cursor x,y position (16 bits each) */
	u32	thc_cursmask[32];	/* cursor mask bits */
	u32	thc_cursbits[32];	/* what to show where mask enabled */
पूर्ण;

काष्ठा cg6_fbc अणु
	u32	xxx0[1];
	u32	mode;
	u32	clip;
	u32	xxx1[1];
	u32	s;
	u32	draw;
	u32	blit;
	u32	font;
	u32	xxx2[24];
	u32	x0, y0, z0, color0;
	u32	x1, y1, z1, color1;
	u32	x2, y2, z2, color2;
	u32	x3, y3, z3, color3;
	u32	offx, offy;
	u32	xxx3[2];
	u32	incx, incy;
	u32	xxx4[2];
	u32	clipminx, clipminy;
	u32	xxx5[2];
	u32	clipmaxx, clipmaxy;
	u32	xxx6[2];
	u32	fg;
	u32	bg;
	u32	alu;
	u32	pm;
	u32	pixelm;
	u32	xxx7[2];
	u32	patalign;
	u32	pattern[8];
	u32	xxx8[432];
	u32	apoपूर्णांकx, apoपूर्णांकy, apoपूर्णांकz;
	u32	xxx9[1];
	u32	rpoपूर्णांकx, rpoपूर्णांकy, rpoपूर्णांकz;
	u32	xxx10[5];
	u32	poपूर्णांकr, poपूर्णांकg, poपूर्णांकb, poपूर्णांकa;
	u32	alinex, aliney, alinez;
	u32	xxx11[1];
	u32	rlinex, rliney, rlinez;
	u32	xxx12[5];
	u32	liner, lineg, lineb, linea;
	u32	atrix, atriy, atriz;
	u32	xxx13[1];
	u32	rtrix, rtriy, rtriz;
	u32	xxx14[5];
	u32	trir, trig, trib, tria;
	u32	aquadx, aquady, aquadz;
	u32	xxx15[1];
	u32	rquadx, rquady, rquadz;
	u32	xxx16[5];
	u32	quadr, quadg, quadb, quada;
	u32	arectx, arecty, arectz;
	u32	xxx17[1];
	u32	rrectx, rrecty, rrectz;
	u32	xxx18[5];
	u32	rectr, rectg, rectb, recta;
पूर्ण;

काष्ठा bt_regs अणु
	u32	addr;
	u32	color_map;
	u32	control;
	u32	cursor;
पूर्ण;

काष्ठा cg6_par अणु
	spinlock_t		lock;
	काष्ठा bt_regs		__iomem *bt;
	काष्ठा cg6_fbc		__iomem *fbc;
	काष्ठा cg6_thc		__iomem *thc;
	काष्ठा cg6_tec		__iomem *tec;
	u32			__iomem *fhc;

	u32			flags;
#घोषणा CG6_FLAG_BLANKED	0x00000001

	अचिन्हित दीर्घ		which_io;
पूर्ण;

अटल पूर्णांक cg6_sync(काष्ठा fb_info *info)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	काष्ठा cg6_fbc __iomem *fbc = par->fbc;
	पूर्णांक limit = 10000;

	करो अणु
		अगर (!(sbus_पढ़ोl(&fbc->s) & 0x10000000))
			अवरोध;
		udelay(10);
	पूर्ण जबतक (--limit > 0);

	वापस 0;
पूर्ण

अटल व्योम cg6_चयन_from_graph(काष्ठा cg6_par *par)
अणु
	काष्ठा cg6_thc __iomem *thc = par->thc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&par->lock, flags);

	/* Hide the cursor. */
	sbus_ग_लिखोl(CG6_THC_CURSOFF, &thc->thc_cursxy);

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

अटल पूर्णांक cg6_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;

	/* We just use this to catch चयनes out of
	 * graphics mode.
	 */
	cg6_चयन_from_graph(par);

	अगर (var->xoffset || var->yoffset || var->vmode)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/**
 *	cg6_fillrect -	Draws a rectangle on the screen.
 *
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@rect: काष्ठाure defining the rectagle and operation.
 */
अटल व्योम cg6_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	काष्ठा cg6_fbc __iomem *fbc = par->fbc;
	अचिन्हित दीर्घ flags;
	s32 val;

	/* CG6 करोesn't handle ROP_XOR */

	spin_lock_irqsave(&par->lock, flags);

	cg6_sync(info);

	sbus_ग_लिखोl(rect->color, &fbc->fg);
	sbus_ग_लिखोl(~(u32)0, &fbc->pixelm);
	sbus_ग_लिखोl(0xea80ff00, &fbc->alu);
	sbus_ग_लिखोl(0, &fbc->s);
	sbus_ग_लिखोl(0, &fbc->clip);
	sbus_ग_लिखोl(~(u32)0, &fbc->pm);
	sbus_ग_लिखोl(rect->dy, &fbc->arecty);
	sbus_ग_लिखोl(rect->dx, &fbc->arectx);
	sbus_ग_लिखोl(rect->dy + rect->height, &fbc->arecty);
	sbus_ग_लिखोl(rect->dx + rect->width, &fbc->arectx);
	करो अणु
		val = sbus_पढ़ोl(&fbc->draw);
	पूर्ण जबतक (val < 0 && (val & 0x20000000));
	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

/**
 *	cg6_copyarea - Copies one area of the screen to another area.
 *
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@area: Structure providing the data to copy the framebuffer contents
 *		from one region to another.
 *
 *	This drawing operation copies a rectangular area from one area of the
 *	screen to another area.
 */
अटल व्योम cg6_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	काष्ठा cg6_fbc __iomem *fbc = par->fbc;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&par->lock, flags);

	cg6_sync(info);

	sbus_ग_लिखोl(0xff, &fbc->fg);
	sbus_ग_लिखोl(0x00, &fbc->bg);
	sbus_ग_लिखोl(~0, &fbc->pixelm);
	sbus_ग_लिखोl(0xe880cccc, &fbc->alu);
	sbus_ग_लिखोl(0, &fbc->s);
	sbus_ग_लिखोl(0, &fbc->clip);

	sbus_ग_लिखोl(area->sy, &fbc->y0);
	sbus_ग_लिखोl(area->sx, &fbc->x0);
	sbus_ग_लिखोl(area->sy + area->height - 1, &fbc->y1);
	sbus_ग_लिखोl(area->sx + area->width - 1, &fbc->x1);
	sbus_ग_लिखोl(area->dy, &fbc->y2);
	sbus_ग_लिखोl(area->dx, &fbc->x2);
	sbus_ग_लिखोl(area->dy + area->height - 1, &fbc->y3);
	sbus_ग_लिखोl(area->dx + area->width - 1, &fbc->x3);
	करो अणु
		i = sbus_पढ़ोl(&fbc->blit);
	पूर्ण जबतक (i < 0 && (i & 0x20000000));
	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

/**
 *	cg6_imageblit -	Copies a image from प्रणाली memory to the screen.
 *
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 *	@image: काष्ठाure defining the image.
 */
अटल व्योम cg6_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	काष्ठा cg6_fbc __iomem *fbc = par->fbc;
	स्थिर u8 *data = image->data;
	अचिन्हित दीर्घ flags;
	u32 x, y;
	पूर्णांक i, width;

	अगर (image->depth > 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	spin_lock_irqsave(&par->lock, flags);

	cg6_sync(info);

	sbus_ग_लिखोl(image->fg_color, &fbc->fg);
	sbus_ग_लिखोl(image->bg_color, &fbc->bg);
	sbus_ग_लिखोl(0x140000, &fbc->mode);
	sbus_ग_लिखोl(0xe880fc30, &fbc->alu);
	sbus_ग_लिखोl(~(u32)0, &fbc->pixelm);
	sbus_ग_लिखोl(0, &fbc->s);
	sbus_ग_लिखोl(0, &fbc->clip);
	sbus_ग_लिखोl(0xff, &fbc->pm);
	sbus_ग_लिखोl(32, &fbc->incx);
	sbus_ग_लिखोl(0, &fbc->incy);

	x = image->dx;
	y = image->dy;
	क्रम (i = 0; i < image->height; i++) अणु
		width = image->width;

		जबतक (width >= 32) अणु
			u32 val;

			sbus_ग_लिखोl(y, &fbc->y0);
			sbus_ग_लिखोl(x, &fbc->x0);
			sbus_ग_लिखोl(x + 32 - 1, &fbc->x1);

			val = ((u32)data[0] << 24) |
			      ((u32)data[1] << 16) |
			      ((u32)data[2] <<  8) |
			      ((u32)data[3] <<  0);
			sbus_ग_लिखोl(val, &fbc->font);

			data += 4;
			x += 32;
			width -= 32;
		पूर्ण
		अगर (width) अणु
			u32 val;

			sbus_ग_लिखोl(y, &fbc->y0);
			sbus_ग_लिखोl(x, &fbc->x0);
			sbus_ग_लिखोl(x + width - 1, &fbc->x1);
			अगर (width <= 8) अणु
				val = (u32) data[0] << 24;
				data += 1;
			पूर्ण अन्यथा अगर (width <= 16) अणु
				val = ((u32) data[0] << 24) |
				      ((u32) data[1] << 16);
				data += 2;
			पूर्ण अन्यथा अणु
				val = ((u32) data[0] << 24) |
				      ((u32) data[1] << 16) |
				      ((u32) data[2] <<  8);
				data += 3;
			पूर्ण
			sbus_ग_लिखोl(val, &fbc->font);
		पूर्ण

		y += 1;
		x = image->dx;
	पूर्ण

	spin_unlock_irqrestore(&par->lock, flags);
पूर्ण

/**
 *	cg6_setcolreg - Sets a color रेजिस्टर.
 *
 *	@regno: boolean, 0 copy local, 1 get_user() function
 *	@red: frame buffer colormap काष्ठाure
 *	@green: The green value which can be up to 16 bits wide
 *	@blue:  The blue value which can be up to 16 bits wide.
 *	@transp: If supported the alpha value which can be up to 16 bits wide.
 *	@info: frame buffer info काष्ठाure
 */
अटल पूर्णांक cg6_setcolreg(अचिन्हित regno,
			 अचिन्हित red, अचिन्हित green, अचिन्हित blue,
			 अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	काष्ठा bt_regs __iomem *bt = par->bt;
	अचिन्हित दीर्घ flags;

	अगर (regno >= 256)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	spin_lock_irqsave(&par->lock, flags);

	sbus_ग_लिखोl((u32)regno << 24, &bt->addr);
	sbus_ग_लिखोl((u32)red << 24, &bt->color_map);
	sbus_ग_लिखोl((u32)green << 24, &bt->color_map);
	sbus_ग_लिखोl((u32)blue << 24, &bt->color_map);

	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

/**
 *	cg6_blank - Blanks the display.
 *
 *	@blank: the blank mode we want.
 *	@info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक cg6_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	काष्ठा cg6_thc __iomem *thc = par->thc;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&par->lock, flags);
	val = sbus_पढ़ोl(&thc->thc_misc);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		val |= CG6_THC_MISC_VIDEO;
		par->flags &= ~CG6_FLAG_BLANKED;
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		val &= ~CG6_THC_MISC_VIDEO;
		par->flags |= CG6_FLAG_BLANKED;
		अवरोध;
	पूर्ण

	sbus_ग_लिखोl(val, &thc->thc_misc);
	spin_unlock_irqrestore(&par->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा sbus_mmap_map cg6_mmap_map[] = अणु
	अणु
		.voff	= CG6_FBC,
		.poff	= CG6_FBC_OFFSET,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= CG6_TEC,
		.poff	= CG6_TEC_OFFSET,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= CG6_BTREGS,
		.poff	= CG6_BROOKTREE_OFFSET,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= CG6_FHC,
		.poff	= CG6_FHC_OFFSET,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= CG6_THC,
		.poff	= CG6_THC_OFFSET,
		.size	= PAGE_SIZE
	पूर्ण,
	अणु
		.voff	= CG6_ROM,
		.poff	= CG6_ROM_OFFSET,
		.size	= 0x10000
	पूर्ण,
	अणु
		.voff	= CG6_RAM,
		.poff	= CG6_RAM_OFFSET,
		.size	= SBUS_MMAP_FBSIZE(1)
	पूर्ण,
	अणु
		.voff	= CG6_DHC,
		.poff	= CG6_DHC_OFFSET,
		.size	= 0x40000
	पूर्ण,
	अणु .size	= 0 पूर्ण
पूर्ण;

अटल पूर्णांक cg6_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;

	वापस sbusfb_mmap_helper(cg6_mmap_map,
				  info->fix.smem_start, info->fix.smem_len,
				  par->which_io, vma);
पूर्ण

अटल पूर्णांक cg6_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस sbusfb_ioctl_helper(cmd, arg, info,
				   FBTYPE_SUNFAST_COLOR, 8, info->fix.smem_len);
पूर्ण

/*
 *  Initialisation
 */

अटल व्योम cg6_init_fix(काष्ठा fb_info *info, पूर्णांक linebytes)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	स्थिर अक्षर *cg6_cpu_name, *cg6_card_name;
	u32 conf;

	conf = sbus_पढ़ोl(par->fhc);
	चयन (conf & CG6_FHC_CPU_MASK) अणु
	हाल CG6_FHC_CPU_SPARC:
		cg6_cpu_name = "sparc";
		अवरोध;
	हाल CG6_FHC_CPU_68020:
		cg6_cpu_name = "68020";
		अवरोध;
	शेष:
		cg6_cpu_name = "i386";
		अवरोध;
	पूर्ण
	अगर (((conf >> CG6_FHC_REV_SHIFT) & CG6_FHC_REV_MASK) >= 11) अणु
		अगर (info->fix.smem_len <= 0x100000)
			cg6_card_name = "TGX";
		अन्यथा
			cg6_card_name = "TGX+";
	पूर्ण अन्यथा अणु
		अगर (info->fix.smem_len <= 0x100000)
			cg6_card_name = "GX";
		अन्यथा
			cg6_card_name = "GX+";
	पूर्ण

	प्र_लिखो(info->fix.id, "%s %s", cg6_card_name, cg6_cpu_name);
	info->fix.id[माप(info->fix.id) - 1] = 0;

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_CGSIX;
पूर्ण

/* Initialize Brooktree DAC */
अटल व्योम cg6_bt_init(काष्ठा cg6_par *par)
अणु
	काष्ठा bt_regs __iomem *bt = par->bt;

	sbus_ग_लिखोl(0x04 << 24, &bt->addr);	 /* color planes */
	sbus_ग_लिखोl(0xff << 24, &bt->control);
	sbus_ग_लिखोl(0x05 << 24, &bt->addr);
	sbus_ग_लिखोl(0x00 << 24, &bt->control);
	sbus_ग_लिखोl(0x06 << 24, &bt->addr);	 /* overlay plane */
	sbus_ग_लिखोl(0x73 << 24, &bt->control);
	sbus_ग_लिखोl(0x07 << 24, &bt->addr);
	sbus_ग_लिखोl(0x00 << 24, &bt->control);
पूर्ण

अटल व्योम cg6_chip_init(काष्ठा fb_info *info)
अणु
	काष्ठा cg6_par *par = (काष्ठा cg6_par *)info->par;
	काष्ठा cg6_tec __iomem *tec = par->tec;
	काष्ठा cg6_fbc __iomem *fbc = par->fbc;
	काष्ठा cg6_thc __iomem *thc = par->thc;
	u32 rev, conf, mode;
	पूर्णांक i;

	/* Hide the cursor. */
	sbus_ग_लिखोl(CG6_THC_CURSOFF, &thc->thc_cursxy);

	/* Turn off stuff in the Transक्रमm Engine. */
	sbus_ग_लिखोl(0, &tec->tec_matrix);
	sbus_ग_लिखोl(0, &tec->tec_clip);
	sbus_ग_लिखोl(0, &tec->tec_vdc);

	/* Take care of bugs in old revisions. */
	rev = (sbus_पढ़ोl(par->fhc) >> CG6_FHC_REV_SHIFT) & CG6_FHC_REV_MASK;
	अगर (rev < 5) अणु
		conf = (sbus_पढ़ोl(par->fhc) & CG6_FHC_RES_MASK) |
			CG6_FHC_CPU_68020 | CG6_FHC_TEST |
			(11 << CG6_FHC_TEST_X_SHIFT) |
			(11 << CG6_FHC_TEST_Y_SHIFT);
		अगर (rev < 2)
			conf |= CG6_FHC_DST_DISABLE;
		sbus_ग_लिखोl(conf, par->fhc);
	पूर्ण

	/* Set things in the FBC. Bad things appear to happen अगर we करो
	 * back to back store/loads on the mode रेजिस्टर, so copy it
	 * out instead. */
	mode = sbus_पढ़ोl(&fbc->mode);
	करो अणु
		i = sbus_पढ़ोl(&fbc->s);
	पूर्ण जबतक (i & 0x10000000);
	mode &= ~(CG6_FBC_BLIT_MASK | CG6_FBC_MODE_MASK |
		  CG6_FBC_DRAW_MASK | CG6_FBC_BWRITE0_MASK |
		  CG6_FBC_BWRITE1_MASK | CG6_FBC_BREAD_MASK |
		  CG6_FBC_BDISP_MASK);
	mode |= (CG6_FBC_BLIT_SRC | CG6_FBC_MODE_COLOR8 |
		 CG6_FBC_DRAW_RENDER | CG6_FBC_BWRITE0_ENABLE |
		 CG6_FBC_BWRITE1_DISABLE | CG6_FBC_BREAD_0 |
		 CG6_FBC_BDISP_0);
	sbus_ग_लिखोl(mode, &fbc->mode);

	sbus_ग_लिखोl(0, &fbc->clip);
	sbus_ग_लिखोl(0, &fbc->offx);
	sbus_ग_लिखोl(0, &fbc->offy);
	sbus_ग_लिखोl(0, &fbc->clipminx);
	sbus_ग_लिखोl(0, &fbc->clipminy);
	sbus_ग_लिखोl(info->var.xres - 1, &fbc->clipmaxx);
	sbus_ग_लिखोl(info->var.yres - 1, &fbc->clipmaxy);
पूर्ण

अटल व्योम cg6_unmap_regs(काष्ठा platक्रमm_device *op, काष्ठा fb_info *info,
			   काष्ठा cg6_par *par)
अणु
	अगर (par->fbc)
		of_iounmap(&op->resource[0], par->fbc, 4096);
	अगर (par->tec)
		of_iounmap(&op->resource[0], par->tec, माप(काष्ठा cg6_tec));
	अगर (par->thc)
		of_iounmap(&op->resource[0], par->thc, माप(काष्ठा cg6_thc));
	अगर (par->bt)
		of_iounmap(&op->resource[0], par->bt, माप(काष्ठा bt_regs));
	अगर (par->fhc)
		of_iounmap(&op->resource[0], par->fhc, माप(u32));

	अगर (info->screen_base)
		of_iounmap(&op->resource[0], info->screen_base,
			   info->fix.smem_len);
पूर्ण

अटल पूर्णांक cg6_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा fb_info *info;
	काष्ठा cg6_par *par;
	पूर्णांक linebytes, err;
	पूर्णांक dblbuf;

	info = framebuffer_alloc(माप(काष्ठा cg6_par), &op->dev);

	err = -ENOMEM;
	अगर (!info)
		जाओ out_err;
	par = info->par;

	spin_lock_init(&par->lock);

	info->fix.smem_start = op->resource[0].start;
	par->which_io = op->resource[0].flags & IORESOURCE_BITS;

	sbusfb_fill_var(&info->var, dp, 8);
	info->var.red.length = 8;
	info->var.green.length = 8;
	info->var.blue.length = 8;

	linebytes = of_getपूर्णांकprop_शेष(dp, "linebytes",
					  info->var.xres);
	info->fix.smem_len = PAGE_ALIGN(linebytes * info->var.yres);

	dblbuf = of_getपूर्णांकprop_शेष(dp, "dblbuf", 0);
	अगर (dblbuf)
		info->fix.smem_len *= 4;

	par->fbc = of_ioremap(&op->resource[0], CG6_FBC_OFFSET,
				4096, "cgsix fbc");
	par->tec = of_ioremap(&op->resource[0], CG6_TEC_OFFSET,
				माप(काष्ठा cg6_tec), "cgsix tec");
	par->thc = of_ioremap(&op->resource[0], CG6_THC_OFFSET,
				माप(काष्ठा cg6_thc), "cgsix thc");
	par->bt = of_ioremap(&op->resource[0], CG6_BROOKTREE_OFFSET,
				माप(काष्ठा bt_regs), "cgsix dac");
	par->fhc = of_ioremap(&op->resource[0], CG6_FHC_OFFSET,
				माप(u32), "cgsix fhc");

	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_IMAGEBLIT |
			FBINFO_HWACCEL_COPYAREA | FBINFO_HWACCEL_FILLRECT |
			FBINFO_READS_FAST;
	info->fbops = &cg6_ops;

	info->screen_base = of_ioremap(&op->resource[0], CG6_RAM_OFFSET,
					info->fix.smem_len, "cgsix ram");
	अगर (!par->fbc || !par->tec || !par->thc ||
	    !par->bt || !par->fhc || !info->screen_base)
		जाओ out_unmap_regs;

	info->var.accel_flags = FB_ACCELF_TEXT;

	cg6_bt_init(par);
	cg6_chip_init(info);
	cg6_blank(FB_BLANK_UNBLANK, info);

	अगर (fb_alloc_cmap(&info->cmap, 256, 0))
		जाओ out_unmap_regs;

	fb_set_cmap(&info->cmap, info);
	cg6_init_fix(info, linebytes);

	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0)
		जाओ out_dealloc_cmap;

	dev_set_drvdata(&op->dev, info);

	prपूर्णांकk(KERN_INFO "%pOF: CGsix [%s] at %lx:%lx\n",
	       dp, info->fix.id,
	       par->which_io, info->fix.smem_start);

	वापस 0;

out_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);

out_unmap_regs:
	cg6_unmap_regs(op, info, par);
	framebuffer_release(info);

out_err:
	वापस err;
पूर्ण

अटल पूर्णांक cg6_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fb_info *info = dev_get_drvdata(&op->dev);
	काष्ठा cg6_par *par = info->par;

	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);

	cg6_unmap_regs(op, info, par);

	framebuffer_release(info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cg6_match[] = अणु
	अणु
		.name = "cgsix",
	पूर्ण,
	अणु
		.name = "cgthree+",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cg6_match);

अटल काष्ठा platक्रमm_driver cg6_driver = अणु
	.driver = अणु
		.name = "cg6",
		.of_match_table = cg6_match,
	पूर्ण,
	.probe		= cg6_probe,
	.हटाओ		= cg6_हटाओ,
पूर्ण;

अटल पूर्णांक __init cg6_init(व्योम)
अणु
	अगर (fb_get_options("cg6fb", शून्य))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&cg6_driver);
पूर्ण

अटल व्योम __निकास cg6_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&cg6_driver);
पूर्ण

module_init(cg6_init);
module_निकास(cg6_निकास);

MODULE_DESCRIPTION("framebuffer driver for CGsix chipsets");
MODULE_AUTHOR("David S. Miller <davem@davemloft.net>");
MODULE_VERSION("2.0");
MODULE_LICENSE("GPL");
