<शैली गुरु>
/*
 *  linux/drivers/video/pm3fb.c -- 3DLअसल Permedia3 frame buffer device
 *
 *  Copyright (C) 2001 Roमुख्य Dolbeau <roमुख्य@करोlbeau.org>.
 *
 *  Ported to 2.6 kernel on 1 May 2007 by Krzysztof Helt <krzysztof.h1@wp.pl>
 *	based on pm2fb.c
 *
 *  Based on code written by:
 *	   Sven Luther, <luther@dpt-info.u-strasbg.fr>
 *	   Alan Hourihane, <alanh@fairlite.demon.co.uk>
 *	   Russell King, <rmk@arm.linux.org.uk>
 *  Based on linux/drivers/video/skeletonfb.c:
 *	Copyright (C) 1997 Geert Uytterhoeven
 *  Based on linux/driver/video/pm2fb.c:
 *	Copyright (C) 1998-1999 Ilario Nardinocchi (nardinoc@CS.UniBO.IT)
 *	Copyright (C) 1999 Jakub Jelinek (jakub@redhat.com)
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <video/pm3fb.h>

#अगर !defined(CONFIG_PCI)
#त्रुटि "Only generic PCI cards supported."
#पूर्ण_अगर

#अघोषित PM3FB_MASTER_DEBUG
#अगर_घोषित PM3FB_MASTER_DEBUG
#घोषणा DPRINTK(a, b...)	\
	prपूर्णांकk(KERN_DEBUG "pm3fb: %s: " a, __func__ , ## b)
#अन्यथा
#घोषणा DPRINTK(a, b...)	no_prपूर्णांकk(a, ##b)
#पूर्ण_अगर

#घोषणा PM3_PIXMAP_SIZE	(2048 * 4)

/*
 * Driver data
 */
अटल पूर्णांक hwcursor = 1;
अटल अक्षर *mode_option;
अटल bool noaccel;
अटल bool nomtrr;

/*
 * This काष्ठाure defines the hardware state of the graphics card. Normally
 * you place this in a header file in linux/include/video. This file usually
 * also includes रेजिस्टर inक्रमmation. That allows other driver subप्रणालीs
 * and userland applications the ability to use the same header file to
 * aव्योम duplicate work and easy porting of software.
 */
काष्ठा pm3_par अणु
	अचिन्हित अक्षर	__iomem *v_regs;/* भव address of p_regs */
	u32		video;		/* video flags beक्रमe blanking */
	u32		base;		/* screen base in 128 bits unit */
	u32		palette[16];
	पूर्णांक		wc_cookie;
पूर्ण;

/*
 * Here we define the शेष काष्ठाs fb_fix_screeninfo and fb_var_screeninfo
 * अगर we करोn't use modedb. If we करो use modedb see pm3fb_init how to use it
 * to get a fb_var_screeninfo. Otherwise define a शेष var as well.
 */
अटल काष्ठा fb_fix_screeninfo pm3fb_fix = अणु
	.id =		"Permedia3",
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_PSEUDOCOLOR,
	.xpanstep =	1,
	.ypanstep =	1,
	.ywrapstep =	0,
	.accel =	FB_ACCEL_3DLABS_PERMEDIA3,
पूर्ण;

/*
 * Utility functions
 */

अटल अंतरभूत u32 PM3_READ_REG(काष्ठा pm3_par *par, s32 off)
अणु
	वापस fb_पढ़ोl(par->v_regs + off);
पूर्ण

अटल अंतरभूत व्योम PM3_WRITE_REG(काष्ठा pm3_par *par, s32 off, u32 v)
अणु
	fb_ग_लिखोl(v, par->v_regs + off);
पूर्ण

अटल अंतरभूत व्योम PM3_WAIT(काष्ठा pm3_par *par, u32 n)
अणु
	जबतक (PM3_READ_REG(par, PM3InFIFOSpace) < n)
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम PM3_WRITE_DAC_REG(काष्ठा pm3_par *par, अचिन्हित r, u8 v)
अणु
	PM3_WAIT(par, 3);
	PM3_WRITE_REG(par, PM3RD_IndexHigh, (r >> 8) & 0xff);
	PM3_WRITE_REG(par, PM3RD_IndexLow, r & 0xff);
	wmb();
	PM3_WRITE_REG(par, PM3RD_IndexedData, v);
	wmb();
पूर्ण

अटल अंतरभूत व्योम pm3fb_set_color(काष्ठा pm3_par *par, अचिन्हित अक्षर regno,
			अचिन्हित अक्षर r, अचिन्हित अक्षर g, अचिन्हित अक्षर b)
अणु
	PM3_WAIT(par, 4);
	PM3_WRITE_REG(par, PM3RD_PaletteWriteAddress, regno);
	wmb();
	PM3_WRITE_REG(par, PM3RD_PaletteData, r);
	wmb();
	PM3_WRITE_REG(par, PM3RD_PaletteData, g);
	wmb();
	PM3_WRITE_REG(par, PM3RD_PaletteData, b);
	wmb();
पूर्ण

अटल व्योम pm3fb_clear_colormap(काष्ठा pm3_par *par,
			अचिन्हित अक्षर r, अचिन्हित अक्षर g, अचिन्हित अक्षर b)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 256 ; i++)
		pm3fb_set_color(par, i, r, g, b);

पूर्ण

/* Calculating various घड़ी parameters */
अटल व्योम pm3fb_calculate_घड़ी(अचिन्हित दीर्घ reqघड़ी,
				अचिन्हित अक्षर *prescale,
				अचिन्हित अक्षर *feedback,
				अचिन्हित अक्षर *postscale)
अणु
	पूर्णांक f, pre, post;
	अचिन्हित दीर्घ freq;
	दीर्घ freqerr = 1000;
	दीर्घ currerr;

	क्रम (f = 1; f < 256; f++) अणु
		क्रम (pre = 1; pre < 256; pre++) अणु
			क्रम (post = 0; post < 5; post++) अणु
				freq = ((2*PM3_REF_CLOCK * f) >> post) / pre;
				currerr = (reqघड़ी > freq)
					? reqघड़ी - freq
					: freq - reqघड़ी;
				अगर (currerr < freqerr) अणु
					freqerr = currerr;
					*feedback = f;
					*prescale = pre;
					*postscale = post;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक pm3fb_depth(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	अगर (var->bits_per_pixel == 16)
		वापस var->red.length + var->green.length
			+ var->blue.length;

	वापस var->bits_per_pixel;
पूर्ण

अटल अंतरभूत पूर्णांक pm3fb_shअगरt_bpp(अचिन्हित bpp, पूर्णांक v)
अणु
	चयन (bpp) अणु
	हाल 8:
		वापस (v >> 4);
	हाल 16:
		वापस (v >> 3);
	हाल 32:
		वापस (v >> 2);
	पूर्ण
	DPRINTK("Unsupported depth %u\n", bpp);
	वापस 0;
पूर्ण

/* acceleration */
अटल पूर्णांक pm3fb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा pm3_par *par = info->par;

	PM3_WAIT(par, 2);
	PM3_WRITE_REG(par, PM3FilterMode, PM3FilterModeSync);
	PM3_WRITE_REG(par, PM3Sync, 0);
	mb();
	करो अणु
		जबतक ((PM3_READ_REG(par, PM3OutFIFOWords)) == 0)
			cpu_relax();
	पूर्ण जबतक ((PM3_READ_REG(par, PM3OutputFअगरo)) != PM3Sync_Tag);

	वापस 0;
पूर्ण

अटल व्योम pm3fb_init_engine(काष्ठा fb_info *info)
अणु
	काष्ठा pm3_par *par = info->par;
	स्थिर u32 width = (info->var.xres_भव + 7) & ~7;

	PM3_WAIT(par, 50);
	PM3_WRITE_REG(par, PM3FilterMode, PM3FilterModeSync);
	PM3_WRITE_REG(par, PM3StatisticMode, 0x0);
	PM3_WRITE_REG(par, PM3DeltaMode, 0x0);
	PM3_WRITE_REG(par, PM3RasterizerMode, 0x0);
	PM3_WRITE_REG(par, PM3ScissorMode, 0x0);
	PM3_WRITE_REG(par, PM3LineStippleMode, 0x0);
	PM3_WRITE_REG(par, PM3AreaStippleMode, 0x0);
	PM3_WRITE_REG(par, PM3GIDMode, 0x0);
	PM3_WRITE_REG(par, PM3DepthMode, 0x0);
	PM3_WRITE_REG(par, PM3StencilMode, 0x0);
	PM3_WRITE_REG(par, PM3StencilData, 0x0);
	PM3_WRITE_REG(par, PM3ColorDDAMode, 0x0);
	PM3_WRITE_REG(par, PM3TextureCoordMode, 0x0);
	PM3_WRITE_REG(par, PM3TextureIndexMode0, 0x0);
	PM3_WRITE_REG(par, PM3TextureIndexMode1, 0x0);
	PM3_WRITE_REG(par, PM3TextureReadMode, 0x0);
	PM3_WRITE_REG(par, PM3LUTMode, 0x0);
	PM3_WRITE_REG(par, PM3TextureFilterMode, 0x0);
	PM3_WRITE_REG(par, PM3TextureCompositeMode, 0x0);
	PM3_WRITE_REG(par, PM3TextureApplicationMode, 0x0);
	PM3_WRITE_REG(par, PM3TextureCompositeColorMode1, 0x0);
	PM3_WRITE_REG(par, PM3TextureCompositeAlphaMode1, 0x0);
	PM3_WRITE_REG(par, PM3TextureCompositeColorMode0, 0x0);
	PM3_WRITE_REG(par, PM3TextureCompositeAlphaMode0, 0x0);
	PM3_WRITE_REG(par, PM3FogMode, 0x0);
	PM3_WRITE_REG(par, PM3ChromaTestMode, 0x0);
	PM3_WRITE_REG(par, PM3AlphaTestMode, 0x0);
	PM3_WRITE_REG(par, PM3AntialiasMode, 0x0);
	PM3_WRITE_REG(par, PM3YUVMode, 0x0);
	PM3_WRITE_REG(par, PM3AlphaBlendColorMode, 0x0);
	PM3_WRITE_REG(par, PM3AlphaBlendAlphaMode, 0x0);
	PM3_WRITE_REG(par, PM3DitherMode, 0x0);
	PM3_WRITE_REG(par, PM3LogicalOpMode, 0x0);
	PM3_WRITE_REG(par, PM3RouterMode, 0x0);
	PM3_WRITE_REG(par, PM3Winकरोw, 0x0);

	PM3_WRITE_REG(par, PM3Config2D, 0x0);

	PM3_WRITE_REG(par, PM3SpanColorMask, 0xffffffff);

	PM3_WRITE_REG(par, PM3XBias, 0x0);
	PM3_WRITE_REG(par, PM3YBias, 0x0);
	PM3_WRITE_REG(par, PM3DeltaControl, 0x0);

	PM3_WRITE_REG(par, PM3BitMaskPattern, 0xffffffff);

	PM3_WRITE_REG(par, PM3FBDestReadEnables,
			   PM3FBDestReadEnables_E(0xff) |
			   PM3FBDestReadEnables_R(0xff) |
			   PM3FBDestReadEnables_ReferenceAlpha(0xff));
	PM3_WRITE_REG(par, PM3FBDestReadBufferAddr0, 0x0);
	PM3_WRITE_REG(par, PM3FBDestReadBufferOffset0, 0x0);
	PM3_WRITE_REG(par, PM3FBDestReadBufferWidth0,
			   PM3FBDestReadBufferWidth_Width(width));

	PM3_WRITE_REG(par, PM3FBDestReadMode,
			   PM3FBDestReadMode_ReadEnable |
			   PM3FBDestReadMode_Enable0);
	PM3_WRITE_REG(par, PM3FBSourceReadBufferAddr, 0x0);
	PM3_WRITE_REG(par, PM3FBSourceReadBufferOffset, 0x0);
	PM3_WRITE_REG(par, PM3FBSourceReadBufferWidth,
			   PM3FBSourceReadBufferWidth_Width(width));
	PM3_WRITE_REG(par, PM3FBSourceReadMode,
			   PM3FBSourceReadMode_Blocking |
			   PM3FBSourceReadMode_ReadEnable);

	PM3_WAIT(par, 2);
	अणु
		/* invert bits in biपंचांगask */
		अचिन्हित दीर्घ rm = 1 | (3 << 7);
		चयन (info->var.bits_per_pixel) अणु
		हाल 8:
			PM3_WRITE_REG(par, PM3PixelSize,
					   PM3PixelSize_GLOBAL_8BIT);
#अगर_घोषित __BIG_ENDIAN
			rm |= 3 << 15;
#पूर्ण_अगर
			अवरोध;
		हाल 16:
			PM3_WRITE_REG(par, PM3PixelSize,
					   PM3PixelSize_GLOBAL_16BIT);
#अगर_घोषित __BIG_ENDIAN
			rm |= 2 << 15;
#पूर्ण_अगर
			अवरोध;
		हाल 32:
			PM3_WRITE_REG(par, PM3PixelSize,
					   PM3PixelSize_GLOBAL_32BIT);
			अवरोध;
		शेष:
			DPRINTK("Unsupported depth %d\n",
				info->var.bits_per_pixel);
			अवरोध;
		पूर्ण
		PM3_WRITE_REG(par, PM3RasterizerMode, rm);
	पूर्ण

	PM3_WAIT(par, 20);
	PM3_WRITE_REG(par, PM3FBSoftwareWriteMask, 0xffffffff);
	PM3_WRITE_REG(par, PM3FBHardwareWriteMask, 0xffffffff);
	PM3_WRITE_REG(par, PM3FBWriteMode,
			   PM3FBWriteMode_WriteEnable |
			   PM3FBWriteMode_OpaqueSpan |
			   PM3FBWriteMode_Enable0);
	PM3_WRITE_REG(par, PM3FBWriteBufferAddr0, 0x0);
	PM3_WRITE_REG(par, PM3FBWriteBufferOffset0, 0x0);
	PM3_WRITE_REG(par, PM3FBWriteBufferWidth0,
			   PM3FBWriteBufferWidth_Width(width));

	PM3_WRITE_REG(par, PM3SizeOfFramebuffer, 0x0);
	अणु
		/* size in lines of FB */
		अचिन्हित दीर्घ sofb = info->screen_size /
			info->fix.line_length;
		अगर (sofb > 4095)
			PM3_WRITE_REG(par, PM3SizeOfFramebuffer, 4095);
		अन्यथा
			PM3_WRITE_REG(par, PM3SizeOfFramebuffer, sofb);

		चयन (info->var.bits_per_pixel) अणु
		हाल 8:
			PM3_WRITE_REG(par, PM3DitherMode,
					   (1 << 10) | (2 << 3));
			अवरोध;
		हाल 16:
			PM3_WRITE_REG(par, PM3DitherMode,
					   (1 << 10) | (1 << 3));
			अवरोध;
		हाल 32:
			PM3_WRITE_REG(par, PM3DitherMode,
					   (1 << 10) | (0 << 3));
			अवरोध;
		शेष:
			DPRINTK("Unsupported depth %d\n",
				info->var.bits_per_pixel);
			अवरोध;
		पूर्ण
	पूर्ण

	PM3_WRITE_REG(par, PM3dXDom, 0x0);
	PM3_WRITE_REG(par, PM3dXSub, 0x0);
	PM3_WRITE_REG(par, PM3dY, 1 << 16);
	PM3_WRITE_REG(par, PM3StartXDom, 0x0);
	PM3_WRITE_REG(par, PM3StartXSub, 0x0);
	PM3_WRITE_REG(par, PM3StartY, 0x0);
	PM3_WRITE_REG(par, PM3Count, 0x0);

/* Disable LocalBuffer. better safe than sorry */
	PM3_WRITE_REG(par, PM3LBDestReadMode, 0x0);
	PM3_WRITE_REG(par, PM3LBDestReadEnables, 0x0);
	PM3_WRITE_REG(par, PM3LBSourceReadMode, 0x0);
	PM3_WRITE_REG(par, PM3LBWriteMode, 0x0);

	pm3fb_sync(info);
पूर्ण

अटल व्योम pm3fb_fillrect(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_fillrect *region)
अणु
	काष्ठा pm3_par *par = info->par;
	काष्ठा fb_fillrect modded;
	पूर्णांक vxres, vyres;
	पूर्णांक rop;
	u32 color = (info->fix.visual == FB_VISUAL_TRUECOLOR) ?
		((u32 *)info->pseuकरो_palette)[region->color] : region->color;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_fillrect(info, region);
		वापस;
	पूर्ण
	अगर (region->rop == ROP_COPY )
		rop = PM3Config2D_ForegroundROP(0x3); /* GXcopy */
	अन्यथा
		rop = PM3Config2D_ForegroundROP(0x6) | /* GXxor */
			PM3Config2D_FBDestReadEnable;

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	स_नकल(&modded, region, माप(काष्ठा fb_fillrect));

	अगर (!modded.width || !modded.height ||
	    modded.dx >= vxres || modded.dy >= vyres)
		वापस;

	अगर (modded.dx + modded.width  > vxres)
		modded.width  = vxres - modded.dx;
	अगर (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	अगर (info->var.bits_per_pixel == 8)
		color |= color << 8;
	अगर (info->var.bits_per_pixel <= 16)
		color |= color << 16;

	PM3_WAIT(par, 4);
	/* ROP Ox3 is GXcopy */
	PM3_WRITE_REG(par, PM3Config2D,
			PM3Config2D_UseConstantSource |
			PM3Config2D_ForegroundROPEnable |
			rop |
			PM3Config2D_FBWriteEnable);

	PM3_WRITE_REG(par, PM3ForegroundColor, color);

	PM3_WRITE_REG(par, PM3RectanglePosition,
			PM3RectanglePosition_XOffset(modded.dx) |
			PM3RectanglePosition_YOffset(modded.dy));

	PM3_WRITE_REG(par, PM3Render2D,
		      PM3Render2D_XPositive |
		      PM3Render2D_YPositive |
		      PM3Render2D_Operation_Normal |
		      PM3Render2D_SpanOperation |
		      PM3Render2D_Width(modded.width) |
		      PM3Render2D_Height(modded.height));
पूर्ण

अटल व्योम pm3fb_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा pm3_par *par = info->par;
	काष्ठा fb_copyarea modded;
	u32 vxres, vyres;
	पूर्णांक x_align, o_x, o_y;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	स_नकल(&modded, area, माप(काष्ठा fb_copyarea));

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	अगर (!modded.width || !modded.height ||
	    modded.sx >= vxres || modded.sy >= vyres ||
	    modded.dx >= vxres || modded.dy >= vyres)
		वापस;

	अगर (modded.sx + modded.width > vxres)
		modded.width = vxres - modded.sx;
	अगर (modded.dx + modded.width > vxres)
		modded.width = vxres - modded.dx;
	अगर (modded.sy + modded.height > vyres)
		modded.height = vyres - modded.sy;
	अगर (modded.dy + modded.height > vyres)
		modded.height = vyres - modded.dy;

	o_x = modded.sx - modded.dx;	/*(sx > dx ) ? (sx - dx) : (dx - sx); */
	o_y = modded.sy - modded.dy;	/*(sy > dy ) ? (sy - dy) : (dy - sy); */

	x_align = (modded.sx & 0x1f);

	PM3_WAIT(par, 6);

	PM3_WRITE_REG(par, PM3Config2D,
			PM3Config2D_UserScissorEnable |
			PM3Config2D_ForegroundROPEnable |
			PM3Config2D_Blocking |
			PM3Config2D_ForegroundROP(0x3) | /* Ox3 is GXcopy */
			PM3Config2D_FBWriteEnable);

	PM3_WRITE_REG(par, PM3ScissorMinXY,
			((modded.dy & 0x0fff) << 16) | (modded.dx & 0x0fff));
	PM3_WRITE_REG(par, PM3ScissorMaxXY,
			(((modded.dy + modded.height) & 0x0fff) << 16) |
			((modded.dx + modded.width) & 0x0fff));

	PM3_WRITE_REG(par, PM3FBSourceReadBufferOffset,
			PM3FBSourceReadBufferOffset_XOffset(o_x) |
			PM3FBSourceReadBufferOffset_YOffset(o_y));

	PM3_WRITE_REG(par, PM3RectanglePosition,
			PM3RectanglePosition_XOffset(modded.dx - x_align) |
			PM3RectanglePosition_YOffset(modded.dy));

	PM3_WRITE_REG(par, PM3Render2D,
			((modded.sx > modded.dx) ? PM3Render2D_XPositive : 0) |
			((modded.sy > modded.dy) ? PM3Render2D_YPositive : 0) |
			PM3Render2D_Operation_Normal |
			PM3Render2D_SpanOperation |
			PM3Render2D_FBSourceReadEnable |
			PM3Render2D_Width(modded.width + x_align) |
			PM3Render2D_Height(modded.height));
पूर्ण

अटल व्योम pm3fb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा pm3_par *par = info->par;
	u32 height = image->height;
	u32 fgx, bgx;
	स्थिर u32 *src = (स्थिर u32 *)image->data;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण
	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_PSEUDOCOLOR:
		fgx = image->fg_color;
		bgx = image->bg_color;
		अवरोध;
	हाल FB_VISUAL_TRUECOLOR:
	शेष:
		fgx = par->palette[image->fg_color];
		bgx = par->palette[image->bg_color];
		अवरोध;
	पूर्ण
	अगर (image->depth != 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	अगर (info->var.bits_per_pixel == 8) अणु
		fgx |= fgx << 8;
		bgx |= bgx << 8;
	पूर्ण
	अगर (info->var.bits_per_pixel <= 16) अणु
		fgx |= fgx << 16;
		bgx |= bgx << 16;
	पूर्ण

	PM3_WAIT(par, 7);

	PM3_WRITE_REG(par, PM3ForegroundColor, fgx);
	PM3_WRITE_REG(par, PM3BackgroundColor, bgx);

	/* ROP Ox3 is GXcopy */
	PM3_WRITE_REG(par, PM3Config2D,
			PM3Config2D_UserScissorEnable |
			PM3Config2D_UseConstantSource |
			PM3Config2D_ForegroundROPEnable |
			PM3Config2D_ForegroundROP(0x3) |
			PM3Config2D_OpaqueSpan |
			PM3Config2D_FBWriteEnable);
	PM3_WRITE_REG(par, PM3ScissorMinXY,
			((image->dy & 0x0fff) << 16) | (image->dx & 0x0fff));
	PM3_WRITE_REG(par, PM3ScissorMaxXY,
			(((image->dy + image->height) & 0x0fff) << 16) |
			((image->dx + image->width) & 0x0fff));
	PM3_WRITE_REG(par, PM3RectanglePosition,
			PM3RectanglePosition_XOffset(image->dx) |
			PM3RectanglePosition_YOffset(image->dy));
	PM3_WRITE_REG(par, PM3Render2D,
			PM3Render2D_XPositive |
			PM3Render2D_YPositive |
			PM3Render2D_Operation_SyncOnBitMask |
			PM3Render2D_SpanOperation |
			PM3Render2D_Width(image->width) |
			PM3Render2D_Height(image->height));


	जबतक (height--) अणु
		पूर्णांक width = ((image->width + 7) >> 3)
				+ info->pixmap.scan_align - 1;
		width >>= 2;

		जबतक (width >= PM3_FIFO_SIZE) अणु
			पूर्णांक i = PM3_FIFO_SIZE - 1;

			PM3_WAIT(par, PM3_FIFO_SIZE);
			जबतक (i--) अणु
				PM3_WRITE_REG(par, PM3BitMaskPattern, *src);
				src++;
			पूर्ण
			width -= PM3_FIFO_SIZE - 1;
		पूर्ण

		PM3_WAIT(par, width + 1);
		जबतक (width--) अणु
			PM3_WRITE_REG(par, PM3BitMaskPattern, *src);
			src++;
		पूर्ण
	पूर्ण
पूर्ण
/* end of acceleration functions */

/*
 *	Hardware Cursor support.
 */
अटल स्थिर u8 cursor_bits_lookup[16] = अणु
	0x00, 0x40, 0x10, 0x50, 0x04, 0x44, 0x14, 0x54,
	0x01, 0x41, 0x11, 0x51, 0x05, 0x45, 0x15, 0x55
पूर्ण;

अटल पूर्णांक pm3fb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा pm3_par *par = info->par;
	u8 mode;

	अगर (!hwcursor)
		वापस -EINVAL;	/* just to क्रमce soft_cursor() call */

	/* Too large of a cursor or wrong bpp :-( */
	अगर (cursor->image.width > 64 ||
	    cursor->image.height > 64 ||
	    cursor->image.depth > 1)
		वापस -EINVAL;

	mode = PM3RD_CursorMode_TYPE_X;
	अगर (cursor->enable)
		 mode |= PM3RD_CursorMode_CURSOR_ENABLE;

	PM3_WRITE_DAC_REG(par, PM3RD_CursorMode, mode);

	/*
	 * If the cursor is not be changed this means either we want the
	 * current cursor state (अगर enable is set) or we want to query what
	 * we can करो with the cursor (अगर enable is not set)
	 */
	अगर (!cursor->set)
		वापस 0;

	अगर (cursor->set & FB_CUR_SETPOS) अणु
		पूर्णांक x = cursor->image.dx - info->var.xoffset;
		पूर्णांक y = cursor->image.dy - info->var.yoffset;

		PM3_WRITE_DAC_REG(par, PM3RD_CursorXLow, x & 0xff);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorXHigh, (x >> 8) & 0xf);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorYLow, y & 0xff);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorYHigh, (y >> 8) & 0xf);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETHOT) अणु
		PM3_WRITE_DAC_REG(par, PM3RD_CursorHotSpotX,
				  cursor->hot.x & 0x3f);
		PM3_WRITE_DAC_REG(par, PM3RD_CursorHotSpotY,
				  cursor->hot.y & 0x3f);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		u32 fg_idx = cursor->image.fg_color;
		u32 bg_idx = cursor->image.bg_color;
		काष्ठा fb_cmap cmap = info->cmap;

		/* the X11 driver says one should use these color रेजिस्टरs */
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(39),
				  cmap.red[fg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(40),
				  cmap.green[fg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(41),
				  cmap.blue[fg_idx] >> 8 );

		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(42),
				  cmap.red[bg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(43),
				  cmap.green[bg_idx] >> 8 );
		PM3_WRITE_DAC_REG(par, PM3RD_CursorPalette(44),
				  cmap.blue[bg_idx] >> 8 );
	पूर्ण

	अगर (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) अणु
		u8 *biपंचांगap = (u8 *)cursor->image.data;
		u8 *mask = (u8 *)cursor->mask;
		पूर्णांक i;
		पूर्णांक pos = PM3RD_CursorPattern(0);

		क्रम (i = 0; i < cursor->image.height; i++) अणु
			पूर्णांक j = (cursor->image.width + 7) >> 3;
			पूर्णांक k = 8 - j;

			क्रम (; j > 0; j--) अणु
				u8 data = *biपंचांगap ^ *mask;

				अगर (cursor->rop == ROP_COPY)
					data = *mask & *biपंचांगap;
				/* Upper 4 bits of biपंचांगap data */
				PM3_WRITE_DAC_REG(par, pos++,
					cursor_bits_lookup[data >> 4] |
					(cursor_bits_lookup[*mask >> 4] << 1));
				/* Lower 4 bits of biपंचांगap */
				PM3_WRITE_DAC_REG(par, pos++,
					cursor_bits_lookup[data & 0xf] |
					(cursor_bits_lookup[*mask & 0xf] << 1));
				biपंचांगap++;
				mask++;
			पूर्ण
			क्रम (; k > 0; k--) अणु
				PM3_WRITE_DAC_REG(par, pos++, 0);
				PM3_WRITE_DAC_REG(par, pos++, 0);
			पूर्ण
		पूर्ण
		जबतक (pos < PM3RD_CursorPattern(1024))
			PM3_WRITE_DAC_REG(par, pos++, 0);
	पूर्ण
	वापस 0;
पूर्ण

/* ग_लिखो the mode to रेजिस्टरs */
अटल व्योम pm3fb_ग_लिखो_mode(काष्ठा fb_info *info)
अणु
	काष्ठा pm3_par *par = info->par;
	अक्षर tempsync = 0x00;
	अक्षर tempmisc = 0x00;
	स्थिर u32 hsstart = info->var.right_margin;
	स्थिर u32 hsend = hsstart + info->var.hsync_len;
	स्थिर u32 hbend = hsend + info->var.left_margin;
	स्थिर u32 xres = (info->var.xres + 31) & ~31;
	स्थिर u32 htotal = xres + hbend;
	स्थिर u32 vsstart = info->var.lower_margin;
	स्थिर u32 vsend = vsstart + info->var.vsync_len;
	स्थिर u32 vbend = vsend + info->var.upper_margin;
	स्थिर u32 vtotal = info->var.yres + vbend;
	स्थिर u32 width = (info->var.xres_भव + 7) & ~7;
	स्थिर अचिन्हित bpp = info->var.bits_per_pixel;

	PM3_WAIT(par, 20);
	PM3_WRITE_REG(par, PM3MemBypassWriteMask, 0xffffffff);
	PM3_WRITE_REG(par, PM3Aperture0, 0x00000000);
	PM3_WRITE_REG(par, PM3Aperture1, 0x00000000);
	PM3_WRITE_REG(par, PM3FIFODis, 0x00000007);

	PM3_WRITE_REG(par, PM3HTotal,
			   pm3fb_shअगरt_bpp(bpp, htotal - 1));
	PM3_WRITE_REG(par, PM3HsEnd,
			   pm3fb_shअगरt_bpp(bpp, hsend));
	PM3_WRITE_REG(par, PM3HsStart,
			   pm3fb_shअगरt_bpp(bpp, hsstart));
	PM3_WRITE_REG(par, PM3HbEnd,
			   pm3fb_shअगरt_bpp(bpp, hbend));
	PM3_WRITE_REG(par, PM3HgEnd,
			   pm3fb_shअगरt_bpp(bpp, hbend));
	PM3_WRITE_REG(par, PM3ScreenStride,
			   pm3fb_shअगरt_bpp(bpp, width));
	PM3_WRITE_REG(par, PM3VTotal, vtotal - 1);
	PM3_WRITE_REG(par, PM3VsEnd, vsend - 1);
	PM3_WRITE_REG(par, PM3VsStart, vsstart - 1);
	PM3_WRITE_REG(par, PM3VbEnd, vbend);

	चयन (bpp) अणु
	हाल 8:
		PM3_WRITE_REG(par, PM3ByAperture1Mode,
				   PM3ByApertureMode_PIXELSIZE_8BIT);
		PM3_WRITE_REG(par, PM3ByAperture2Mode,
				   PM3ByApertureMode_PIXELSIZE_8BIT);
		अवरोध;

	हाल 16:
#अगर_अघोषित __BIG_ENDIAN
		PM3_WRITE_REG(par, PM3ByAperture1Mode,
				   PM3ByApertureMode_PIXELSIZE_16BIT);
		PM3_WRITE_REG(par, PM3ByAperture2Mode,
				   PM3ByApertureMode_PIXELSIZE_16BIT);
#अन्यथा
		PM3_WRITE_REG(par, PM3ByAperture1Mode,
				   PM3ByApertureMode_PIXELSIZE_16BIT |
				   PM3ByApertureMode_BYTESWAP_BADC);
		PM3_WRITE_REG(par, PM3ByAperture2Mode,
				   PM3ByApertureMode_PIXELSIZE_16BIT |
				   PM3ByApertureMode_BYTESWAP_BADC);
#पूर्ण_अगर /* ! __BIG_ENDIAN */
		अवरोध;

	हाल 32:
#अगर_अघोषित __BIG_ENDIAN
		PM3_WRITE_REG(par, PM3ByAperture1Mode,
				   PM3ByApertureMode_PIXELSIZE_32BIT);
		PM3_WRITE_REG(par, PM3ByAperture2Mode,
				   PM3ByApertureMode_PIXELSIZE_32BIT);
#अन्यथा
		PM3_WRITE_REG(par, PM3ByAperture1Mode,
				   PM3ByApertureMode_PIXELSIZE_32BIT |
				   PM3ByApertureMode_BYTESWAP_DCBA);
		PM3_WRITE_REG(par, PM3ByAperture2Mode,
				   PM3ByApertureMode_PIXELSIZE_32BIT |
				   PM3ByApertureMode_BYTESWAP_DCBA);
#पूर्ण_अगर /* ! __BIG_ENDIAN */
		अवरोध;

	शेष:
		DPRINTK("Unsupported depth %d\n", bpp);
		अवरोध;
	पूर्ण

	/*
	 * Oxygen VX1 - it appears that setting PM3VideoControl and
	 * then PM3RD_SyncControl to the same SYNC settings unकरोes
	 * any net change - they seem to xor together.  Only set the
	 * sync options in PM3RD_SyncControl.  --rmk
	 */
	अणु
		अचिन्हित पूर्णांक video = par->video;

		video &= ~(PM3VideoControl_HSYNC_MASK |
			   PM3VideoControl_VSYNC_MASK);
		video |= PM3VideoControl_HSYNC_ACTIVE_HIGH |
			 PM3VideoControl_VSYNC_ACTIVE_HIGH;
		PM3_WRITE_REG(par, PM3VideoControl, video);
	पूर्ण
	PM3_WRITE_REG(par, PM3VClkCtl,
			   (PM3_READ_REG(par, PM3VClkCtl) & 0xFFFFFFFC));
	PM3_WRITE_REG(par, PM3ScreenBase, par->base);
	PM3_WRITE_REG(par, PM3ChipConfig,
			   (PM3_READ_REG(par, PM3ChipConfig) & 0xFFFFFFFD));

	wmb();
	अणु
		अचिन्हित अक्षर m;	/* ClkPreScale */
		अचिन्हित अक्षर n;	/* ClkFeedBackScale */
		अचिन्हित अक्षर p;	/* ClkPostScale */
		अचिन्हित दीर्घ pixघड़ी = PICOS2KHZ(info->var.pixघड़ी);

		(व्योम)pm3fb_calculate_घड़ी(pixघड़ी, &m, &n, &p);

		DPRINTK("Pixclock: %ld, Pre: %d, Feedback: %d, Post: %d\n",
			pixघड़ी, (पूर्णांक) m, (पूर्णांक) n, (पूर्णांक) p);

		PM3_WRITE_DAC_REG(par, PM3RD_DClk0PreScale, m);
		PM3_WRITE_DAC_REG(par, PM3RD_DClk0FeedbackScale, n);
		PM3_WRITE_DAC_REG(par, PM3RD_DClk0PostScale, p);
	पूर्ण
	/*
	   PM3_WRITE_DAC_REG(par, PM3RD_IndexControl, 0x00);
	 */
	/*
	   PM3_SLOW_WRITE_REG(par, PM3RD_IndexControl, 0x00);
	 */
	अगर ((par->video & PM3VideoControl_HSYNC_MASK) ==
	    PM3VideoControl_HSYNC_ACTIVE_HIGH)
		tempsync |= PM3RD_SyncControl_HSYNC_ACTIVE_HIGH;
	अगर ((par->video & PM3VideoControl_VSYNC_MASK) ==
	    PM3VideoControl_VSYNC_ACTIVE_HIGH)
		tempsync |= PM3RD_SyncControl_VSYNC_ACTIVE_HIGH;

	PM3_WRITE_DAC_REG(par, PM3RD_SyncControl, tempsync);
	DPRINTK("PM3RD_SyncControl: %d\n", tempsync);

	PM3_WRITE_DAC_REG(par, PM3RD_DACControl, 0x00);

	चयन (pm3fb_depth(&info->var)) अणु
	हाल 8:
		PM3_WRITE_DAC_REG(par, PM3RD_PixelSize,
				  PM3RD_PixelSize_8_BIT_PIXELS);
		PM3_WRITE_DAC_REG(par, PM3RD_ColorFormat,
				  PM3RD_ColorFormat_CI8_COLOR |
				  PM3RD_ColorFormat_COLOR_ORDER_BLUE_LOW);
		tempmisc |= PM3RD_MiscControl_HIGHCOLOR_RES_ENABLE;
		अवरोध;
	हाल 12:
		PM3_WRITE_DAC_REG(par, PM3RD_PixelSize,
				  PM3RD_PixelSize_16_BIT_PIXELS);
		PM3_WRITE_DAC_REG(par, PM3RD_ColorFormat,
				  PM3RD_ColorFormat_4444_COLOR |
				  PM3RD_ColorFormat_COLOR_ORDER_BLUE_LOW |
				  PM3RD_ColorFormat_LINEAR_COLOR_EXT_ENABLE);
		tempmisc |= PM3RD_MiscControl_सूचीECTCOLOR_ENABLE |
			PM3RD_MiscControl_HIGHCOLOR_RES_ENABLE;
		अवरोध;
	हाल 15:
		PM3_WRITE_DAC_REG(par, PM3RD_PixelSize,
				  PM3RD_PixelSize_16_BIT_PIXELS);
		PM3_WRITE_DAC_REG(par, PM3RD_ColorFormat,
				  PM3RD_ColorFormat_5551_FRONT_COLOR |
				  PM3RD_ColorFormat_COLOR_ORDER_BLUE_LOW |
				  PM3RD_ColorFormat_LINEAR_COLOR_EXT_ENABLE);
		tempmisc |= PM3RD_MiscControl_सूचीECTCOLOR_ENABLE |
			PM3RD_MiscControl_HIGHCOLOR_RES_ENABLE;
		अवरोध;
	हाल 16:
		PM3_WRITE_DAC_REG(par, PM3RD_PixelSize,
				  PM3RD_PixelSize_16_BIT_PIXELS);
		PM3_WRITE_DAC_REG(par, PM3RD_ColorFormat,
				  PM3RD_ColorFormat_565_FRONT_COLOR |
				  PM3RD_ColorFormat_COLOR_ORDER_BLUE_LOW |
				  PM3RD_ColorFormat_LINEAR_COLOR_EXT_ENABLE);
		tempmisc |= PM3RD_MiscControl_सूचीECTCOLOR_ENABLE |
			PM3RD_MiscControl_HIGHCOLOR_RES_ENABLE;
		अवरोध;
	हाल 32:
		PM3_WRITE_DAC_REG(par, PM3RD_PixelSize,
				  PM3RD_PixelSize_32_BIT_PIXELS);
		PM3_WRITE_DAC_REG(par, PM3RD_ColorFormat,
				  PM3RD_ColorFormat_8888_COLOR |
				  PM3RD_ColorFormat_COLOR_ORDER_BLUE_LOW);
		tempmisc |= PM3RD_MiscControl_सूचीECTCOLOR_ENABLE |
			PM3RD_MiscControl_HIGHCOLOR_RES_ENABLE;
		अवरोध;
	पूर्ण
	PM3_WRITE_DAC_REG(par, PM3RD_MiscControl, tempmisc);
पूर्ण

/*
 * hardware independent functions
 */
अटल पूर्णांक pm3fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	u32 lpitch;
	अचिन्हित bpp = var->red.length + var->green.length
			+ var->blue.length + var->transp.length;

	अगर (bpp != var->bits_per_pixel) अणु
		/* set predefined mode क्रम bits_per_pixel settings */

		चयन (var->bits_per_pixel) अणु
		हाल 8:
			var->red.length = 8;
			var->green.length = 8;
			var->blue.length = 8;
			var->red.offset = 0;
			var->green.offset = 0;
			var->blue.offset = 0;
			var->transp.offset = 0;
			var->transp.length = 0;
			अवरोध;
		हाल 16:
			var->red.length = 5;
			var->blue.length = 5;
			var->green.length = 6;
			var->transp.length = 0;
			अवरोध;
		हाल 32:
			var->red.length = 8;
			var->green.length = 8;
			var->blue.length = 8;
			var->transp.length = 8;
			अवरोध;
		शेष:
			DPRINTK("depth not supported: %u\n",
				var->bits_per_pixel);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* it is assumed BGRA order */
	अगर (var->bits_per_pixel > 8 ) अणु
		var->blue.offset = 0;
		var->green.offset = var->blue.length;
		var->red.offset = var->green.offset + var->green.length;
		var->transp.offset = var->red.offset + var->red.length;
	पूर्ण
	var->height = -1;
	var->width = -1;

	अगर (var->xres != var->xres_भव) अणु
		DPRINTK("virtual x resolution != "
			"physical x resolution not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (var->yres > var->yres_भव) अणु
		DPRINTK("virtual y resolution < "
			"physical y resolution not possible\n");
		वापस -EINVAL;
	पूर्ण

	अगर (var->xoffset) अणु
		DPRINTK("xoffset not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) अणु
		DPRINTK("interlace not supported\n");
		वापस -EINVAL;
	पूर्ण

	var->xres = (var->xres + 31) & ~31; /* could someबार be 8 */
	lpitch = var->xres * ((var->bits_per_pixel + 7) >> 3);

	अगर (var->xres < 200 || var->xres > 2048) अणु
		DPRINTK("width not supported: %u\n", var->xres);
		वापस -EINVAL;
	पूर्ण

	अगर (var->yres < 200 || var->yres > 4095) अणु
		DPRINTK("height not supported: %u\n", var->yres);
		वापस -EINVAL;
	पूर्ण

	अगर (lpitch * var->yres_भव > info->fix.smem_len) अणु
		DPRINTK("no memory for screen (%ux%ux%u)\n",
			var->xres, var->yres_भव, var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	अगर (PICOS2KHZ(var->pixघड़ी) > PM3_MAX_PIXCLOCK) अणु
		DPRINTK("pixclock too high (%ldKHz)\n",
			PICOS2KHZ(var->pixघड़ी));
		वापस -EINVAL;
	पूर्ण

	var->accel_flags = 0;	/* Can't mmap अगर this is on */

	DPRINTK("Checking graphics mode at %dx%d depth %d\n",
		var->xres, var->yres, var->bits_per_pixel);
	वापस 0;
पूर्ण

अटल पूर्णांक pm3fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा pm3_par *par = info->par;
	स्थिर u32 xres = (info->var.xres + 31) & ~31;
	स्थिर अचिन्हित bpp = info->var.bits_per_pixel;

	par->base = pm3fb_shअगरt_bpp(bpp, (info->var.yoffset * xres)
					+ info->var.xoffset);
	par->video = 0;

	अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		par->video |= PM3VideoControl_HSYNC_ACTIVE_HIGH;
	अन्यथा
		par->video |= PM3VideoControl_HSYNC_ACTIVE_LOW;

	अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		par->video |= PM3VideoControl_VSYNC_ACTIVE_HIGH;
	अन्यथा
		par->video |= PM3VideoControl_VSYNC_ACTIVE_LOW;

	अगर ((info->var.vmode & FB_VMODE_MASK) == FB_VMODE_DOUBLE)
		par->video |= PM3VideoControl_LINE_DOUBLE_ON;

	अगर ((info->var.activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW)
		par->video |= PM3VideoControl_ENABLE;
	अन्यथा
		DPRINTK("PM3Video disabled\n");

	चयन (bpp) अणु
	हाल 8:
		par->video |= PM3VideoControl_PIXELSIZE_8BIT;
		अवरोध;
	हाल 16:
		par->video |= PM3VideoControl_PIXELSIZE_16BIT;
		अवरोध;
	हाल 32:
		par->video |= PM3VideoControl_PIXELSIZE_32BIT;
		अवरोध;
	शेष:
		DPRINTK("Unsupported depth\n");
		अवरोध;
	पूर्ण

	info->fix.visual =
		(bpp == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = ((info->var.xres_भव + 7)  >> 3) * bpp;

/*	pm3fb_clear_memory(info, 0);*/
	pm3fb_clear_colormap(par, 0, 0, 0);
	PM3_WRITE_DAC_REG(par, PM3RD_CursorMode, 0);
	pm3fb_init_engine(info);
	pm3fb_ग_लिखो_mode(info);
	वापस 0;
पूर्ण

अटल पूर्णांक pm3fb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	काष्ठा pm3_par *par = info->par;

	अगर (regno >= 256)  /* no. of hw रेजिस्टरs */
	   वापस -EINVAL;

	/* grayscale works only partially under directcolor */
	/* grayscale = 0.30*R + 0.59*G + 0.11*B */
	अगर (info->var.grayscale)
	   red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;

	/* Directcolor:
	 *   var->अणुcolorपूर्ण.offset contains start of bitfield
	 *   var->अणुcolorपूर्ण.length contains length of bitfield
	 *   अणुhardwarespecअगरicपूर्ण contains width of DAC
	 *   pseuकरो_palette[X] is programmed to (X << red.offset) |
	 *					(X << green.offset) |
	 *					(X << blue.offset)
	 *   RAMDAC[X] is programmed to (red, green, blue)
	 *   color depth = SUM(var->अणुcolorपूर्ण.length)
	 *
	 * Pseuकरोcolor:
	 *	var->अणुcolorपूर्ण.offset is 0
	 *	var->अणुcolorपूर्ण.length contains width of DAC or the number
	 *			of unique colors available (color depth)
	 *	pseuकरो_palette is not used
	 *	RAMDAC[X] is programmed to (red, green, blue)
	 *	color depth = var->अणुcolorपूर्ण.length
	 */

	/*
	 * This is the poपूर्णांक where the color is converted to something that
	 * is acceptable by the hardware.
	 */
#घोषणा CNVT_TOHW(val, width) ((((val) << (width)) + 0x7FFF - (val)) >> 16)
	red = CNVT_TOHW(red, info->var.red.length);
	green = CNVT_TOHW(green, info->var.green.length);
	blue = CNVT_TOHW(blue, info->var.blue.length);
	transp = CNVT_TOHW(transp, info->var.transp.length);
#अघोषित CNVT_TOHW

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		u32 v;

		अगर (regno >= 16)
			वापस -EINVAL;

		v = (red << info->var.red.offset) |
			(green << info->var.green.offset) |
			(blue << info->var.blue.offset) |
			(transp << info->var.transp.offset);

		चयन (info->var.bits_per_pixel) अणु
		हाल 8:
			अवरोध;
		हाल 16:
		हाल 32:
			((u32 *)(info->pseuकरो_palette))[regno] = v;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR)
		pm3fb_set_color(par, regno, red, green, blue);

	वापस 0;
पूर्ण

अटल पूर्णांक pm3fb_pan_display(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info)
अणु
	काष्ठा pm3_par *par = info->par;
	स्थिर u32 xres = (info->var.xres + 31) & ~31;

	par->base = pm3fb_shअगरt_bpp(info->var.bits_per_pixel,
					(var->yoffset * xres)
					+ var->xoffset);
	PM3_WAIT(par, 1);
	PM3_WRITE_REG(par, PM3ScreenBase, par->base);
	वापस 0;
पूर्ण

अटल पूर्णांक pm3fb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा pm3_par *par = info->par;
	u32 video = par->video;

	/*
	 * Oxygen VX1 - it appears that setting PM3VideoControl and
	 * then PM3RD_SyncControl to the same SYNC settings unकरोes
	 * any net change - they seem to xor together.  Only set the
	 * sync options in PM3RD_SyncControl.  --rmk
	 */
	video &= ~(PM3VideoControl_HSYNC_MASK |
		   PM3VideoControl_VSYNC_MASK);
	video |= PM3VideoControl_HSYNC_ACTIVE_HIGH |
		 PM3VideoControl_VSYNC_ACTIVE_HIGH;

	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		video |= PM3VideoControl_ENABLE;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		video &= ~PM3VideoControl_ENABLE;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		video &= ~(PM3VideoControl_HSYNC_MASK |
			  PM3VideoControl_BLANK_ACTIVE_LOW);
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		video &= ~(PM3VideoControl_VSYNC_MASK |
			  PM3VideoControl_BLANK_ACTIVE_LOW);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		video &= ~(PM3VideoControl_HSYNC_MASK |
			  PM3VideoControl_VSYNC_MASK |
			  PM3VideoControl_BLANK_ACTIVE_LOW);
		अवरोध;
	शेष:
		DPRINTK("Unsupported blanking %d\n", blank_mode);
		वापस 1;
	पूर्ण

	PM3_WAIT(par, 1);
	PM3_WRITE_REG(par, PM3VideoControl, video);
	वापस 0;
पूर्ण

	/*
	 *  Frame buffer operations
	 */

अटल स्थिर काष्ठा fb_ops pm3fb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= pm3fb_check_var,
	.fb_set_par	= pm3fb_set_par,
	.fb_setcolreg	= pm3fb_setcolreg,
	.fb_pan_display	= pm3fb_pan_display,
	.fb_fillrect	= pm3fb_fillrect,
	.fb_copyarea	= pm3fb_copyarea,
	.fb_imageblit	= pm3fb_imageblit,
	.fb_blank	= pm3fb_blank,
	.fb_sync	= pm3fb_sync,
	.fb_cursor	= pm3fb_cursor,
पूर्ण;

/* ------------------------------------------------------------------------- */

	/*
	 *  Initialization
	 */

/* mmio रेजिस्टर are alपढ़ोy mapped when this function is called */
/* the pm3fb_fix.smem_start is also set */
अटल अचिन्हित दीर्घ pm3fb_size_memory(काष्ठा pm3_par *par)
अणु
	अचिन्हित दीर्घ	memsize = 0;
	अचिन्हित दीर्घ	tempBypass, i, temp1, temp2;
	अचिन्हित अक्षर	__iomem *screen_mem;

	pm3fb_fix.smem_len = 64 * 1024l * 1024; /* request full aperture size */
	/* Linear frame buffer - request region and map it. */
	अगर (!request_mem_region(pm3fb_fix.smem_start, pm3fb_fix.smem_len,
				 "pm3fb smem")) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't reserve smem.\n");
		वापस 0;
	पूर्ण
	screen_mem =
		ioremap(pm3fb_fix.smem_start, pm3fb_fix.smem_len);
	अगर (!screen_mem) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't ioremap smem area.\n");
		release_mem_region(pm3fb_fix.smem_start, pm3fb_fix.smem_len);
		वापस 0;
	पूर्ण

	/* TODO: card-specअगरic stuff, *beक्रमe* accessing *any* FB memory */
	/* For Appian Jeronimo 2000 board second head */

	tempBypass = PM3_READ_REG(par, PM3MemBypassWriteMask);

	DPRINTK("PM3MemBypassWriteMask was: 0x%08lx\n", tempBypass);

	PM3_WAIT(par, 1);
	PM3_WRITE_REG(par, PM3MemBypassWriteMask, 0xFFFFFFFF);

	/* pm3 split up memory, replicates, and करो a lot of
	 * nasty stuff IMHO ;-)
	 */
	क्रम (i = 0; i < 32; i++) अणु
		fb_ग_लिखोl(i * 0x00345678,
			  (screen_mem + (i * 1048576)));
		mb();
		temp1 = fb_पढ़ोl((screen_mem + (i * 1048576)));

		/* Let's check क्रम wrapover, ग_लिखो will fail at 16MB boundary */
		अगर (temp1 == (i * 0x00345678))
			memsize = i;
		अन्यथा
			अवरोध;
	पूर्ण

	DPRINTK("First detect pass already got %ld MB\n", memsize + 1);

	अगर (memsize + 1 == i) अणु
		क्रम (i = 0; i < 32; i++) अणु
			/* Clear first 32MB ; 0 is 0, no need to byteswap */
			ग_लिखोl(0x0000000, (screen_mem + (i * 1048576)));
		पूर्ण
		wmb();

		क्रम (i = 32; i < 64; i++) अणु
			fb_ग_लिखोl(i * 0x00345678,
				  (screen_mem + (i * 1048576)));
			mb();
			temp1 =
			    fb_पढ़ोl((screen_mem + (i * 1048576)));
			temp2 =
			    fb_पढ़ोl((screen_mem + ((i - 32) * 1048576)));
			/* dअगरferent value, dअगरferent RAM... */
			अगर ((temp1 == (i * 0x00345678)) && (temp2 == 0))
				memsize = i;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	DPRINTK("Second detect pass got %ld MB\n", memsize + 1);

	PM3_WAIT(par, 1);
	PM3_WRITE_REG(par, PM3MemBypassWriteMask, tempBypass);

	iounmap(screen_mem);
	release_mem_region(pm3fb_fix.smem_start, pm3fb_fix.smem_len);
	memsize = 1048576 * (memsize + 1);

	DPRINTK("Returning 0x%08lx bytes\n", memsize);

	वापस memsize;
पूर्ण

अटल पूर्णांक pm3fb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info;
	काष्ठा pm3_par *par;
	काष्ठा device *device = &dev->dev; /* क्रम pci drivers */
	पूर्णांक err;
	पूर्णांक retval = -ENXIO;

	err = pci_enable_device(dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't enable PCI dev: %d\n", err);
		वापस err;
	पूर्ण
	/*
	 * Dynamically allocate info and par
	 */
	info = framebuffer_alloc(माप(काष्ठा pm3_par), device);

	अगर (!info)
		वापस -ENOMEM;
	par = info->par;

	/*
	 * Here we set the screen_base to the भव memory address
	 * क्रम the framebuffer.
	 */
	pm3fb_fix.mmio_start = pci_resource_start(dev, 0);
	pm3fb_fix.mmio_len = PM3_REGS_SIZE;
#अगर defined(__BIG_ENDIAN)
	pm3fb_fix.mmio_start += PM3_REGS_SIZE;
	DPRINTK("Adjusting register base for big-endian.\n");
#पूर्ण_अगर

	/* Registers - request region and map it. */
	अगर (!request_mem_region(pm3fb_fix.mmio_start, pm3fb_fix.mmio_len,
				 "pm3fb regbase")) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't reserve regbase.\n");
		जाओ err_निकास_neither;
	पूर्ण
	par->v_regs =
		ioremap(pm3fb_fix.mmio_start, pm3fb_fix.mmio_len);
	अगर (!par->v_regs) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't remap %s register area.\n",
			pm3fb_fix.id);
		release_mem_region(pm3fb_fix.mmio_start, pm3fb_fix.mmio_len);
		जाओ err_निकास_neither;
	पूर्ण

	/* Linear frame buffer - request region and map it. */
	pm3fb_fix.smem_start = pci_resource_start(dev, 1);
	pm3fb_fix.smem_len = pm3fb_size_memory(par);
	अगर (!pm3fb_fix.smem_len) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't find memory on board.\n");
		जाओ err_निकास_mmio;
	पूर्ण
	अगर (!request_mem_region(pm3fb_fix.smem_start, pm3fb_fix.smem_len,
				 "pm3fb smem")) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't reserve smem.\n");
		जाओ err_निकास_mmio;
	पूर्ण
	info->screen_base = ioremap_wc(pm3fb_fix.smem_start,
				       pm3fb_fix.smem_len);
	अगर (!info->screen_base) अणु
		prपूर्णांकk(KERN_WARNING "pm3fb: Can't ioremap smem area.\n");
		release_mem_region(pm3fb_fix.smem_start, pm3fb_fix.smem_len);
		जाओ err_निकास_mmio;
	पूर्ण
	info->screen_size = pm3fb_fix.smem_len;

	अगर (!nomtrr)
		par->wc_cookie = arch_phys_wc_add(pm3fb_fix.smem_start,
						  pm3fb_fix.smem_len);
	info->fbops = &pm3fb_ops;

	par->video = PM3_READ_REG(par, PM3VideoControl);

	info->fix = pm3fb_fix;
	info->pseuकरो_palette = par->palette;
	info->flags = FBINFO_DEFAULT |
			FBINFO_HWACCEL_XPAN |
			FBINFO_HWACCEL_YPAN |
			FBINFO_HWACCEL_COPYAREA |
			FBINFO_HWACCEL_IMAGEBLIT |
			FBINFO_HWACCEL_FILLRECT;

	अगर (noaccel) अणु
		prपूर्णांकk(KERN_DEBUG "disabling acceleration\n");
		info->flags |= FBINFO_HWACCEL_DISABLED;
	पूर्ण
	info->pixmap.addr = kदो_स्मृति(PM3_PIXMAP_SIZE, GFP_KERNEL);
	अगर (!info->pixmap.addr) अणु
		retval = -ENOMEM;
		जाओ err_निकास_pixmap;
	पूर्ण
	info->pixmap.size = PM3_PIXMAP_SIZE;
	info->pixmap.buf_align = 4;
	info->pixmap.scan_align = 4;
	info->pixmap.access_align = 32;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;

	/*
	 * This should give a reasonable शेष video mode. The following is
	 * करोne when we can set a video mode.
	 */
	अगर (!mode_option)
		mode_option = "640x480@60";

	retval = fb_find_mode(&info->var, info, mode_option, शून्य, 0, शून्य, 8);

	अगर (!retval || retval == 4) अणु
		retval = -EINVAL;
		जाओ err_निकास_both;
	पूर्ण

	अगर (fb_alloc_cmap(&info->cmap, 256, 0) < 0) अणु
		retval = -ENOMEM;
		जाओ err_निकास_both;
	पूर्ण

	/*
	 * For drivers that can...
	 */
	pm3fb_check_var(&info->var, info);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		retval = -EINVAL;
		जाओ err_निकास_all;
	पूर्ण
	fb_info(info, "%s frame buffer device\n", info->fix.id);
	pci_set_drvdata(dev, info);
	वापस 0;

 err_निकास_all:
	fb_dealloc_cmap(&info->cmap);
 err_निकास_both:
	kमुक्त(info->pixmap.addr);
 err_निकास_pixmap:
	iounmap(info->screen_base);
	release_mem_region(pm3fb_fix.smem_start, pm3fb_fix.smem_len);
 err_निकास_mmio:
	iounmap(par->v_regs);
	release_mem_region(pm3fb_fix.mmio_start, pm3fb_fix.mmio_len);
 err_निकास_neither:
	framebuffer_release(info);
	वापस retval;
पूर्ण

	/*
	 *  Cleanup
	 */
अटल व्योम pm3fb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(dev);

	अगर (info) अणु
		काष्ठा fb_fix_screeninfo *fix = &info->fix;
		काष्ठा pm3_par *par = info->par;

		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);

		arch_phys_wc_del(par->wc_cookie);
		iounmap(info->screen_base);
		release_mem_region(fix->smem_start, fix->smem_len);
		iounmap(par->v_regs);
		release_mem_region(fix->mmio_start, fix->mmio_len);

		kमुक्त(info->pixmap.addr);
		framebuffer_release(info);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id pm3fb_id_table[] = अणु
	अणु PCI_VENDOR_ID_3DLABS, 0x0a,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

/* For PCI drivers */
अटल काष्ठा pci_driver pm3fb_driver = अणु
	.name =		"pm3fb",
	.id_table =	pm3fb_id_table,
	.probe =	pm3fb_probe,
	.हटाओ =	pm3fb_हटाओ,
पूर्ण;

MODULE_DEVICE_TABLE(pci, pm3fb_id_table);

#अगर_अघोषित MODULE
	/*
	 *  Setup
	 */

/*
 * Only necessary अगर your driver takes special options,
 * otherwise we fall back on the generic fb_setup().
 */
अटल पूर्णांक __init pm3fb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	/* Parse user specअगरied options (`video=pm3fb:') */
	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*this_opt)
			जारी;
		अन्यथा अगर (!म_भेदन(this_opt, "noaccel", 7))
			noaccel = 1;
		अन्यथा अगर (!म_भेदन(this_opt, "hwcursor=", 9))
			hwcursor = simple_म_से_अदीर्घ(this_opt + 9, शून्य, 0);
		अन्यथा अगर (!म_भेदन(this_opt, "nomtrr", 6))
			nomtrr = 1;
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* MODULE */

अटल पूर्णांक __init pm3fb_init(व्योम)
अणु
	/*
	 *  For kernel boot options (in 'video=pm3fb:<options>' क्रमmat)
	 */
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("pm3fb", &option))
		वापस -ENODEV;
	pm3fb_setup(option);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&pm3fb_driver);
पूर्ण

#अगर_घोषित MODULE
अटल व्योम __निकास pm3fb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pm3fb_driver);
पूर्ण

module_निकास(pm3fb_निकास);
#पूर्ण_अगर
module_init(pm3fb_init);

module_param(mode_option, अक्षरp, 0);
MODULE_PARM_DESC(mode_option, "Initial video mode e.g. '648x480-8@60'");
module_param(noaccel, bool, 0);
MODULE_PARM_DESC(noaccel, "Disable acceleration");
module_param(hwcursor, पूर्णांक, 0644);
MODULE_PARM_DESC(hwcursor, "Enable hardware cursor "
			"(1=enable, 0=disable, default=1)");
module_param(nomtrr, bool, 0);
MODULE_PARM_DESC(nomtrr, "Disable MTRR support (0 or 1=disabled) (default=0)");

MODULE_DESCRIPTION("Permedia3 framebuffer device driver");
MODULE_LICENSE("GPL");
