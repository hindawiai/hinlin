<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/mb862xx/mb862xxfb_accel.c
 *
 * Fujitsu Carmine/Coral-P(A)/Lime framebuffer driver acceleration support
 *
 * (C) 2007 Alexander Shishkin <virtuoso@slind.org>
 * (C) 2009 Valentin Sitdikov <v.sitdikov@gmail.com>
 * (C) 2009 Siemens AG
 */
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#अगर defined(CONFIG_OF)
#समावेश <linux/of_platक्रमm.h>
#पूर्ण_अगर
#समावेश "mb862xxfb.h"
#समावेश "mb862xx_reg.h"
#समावेश "mb862xxfb_accel.h"

अटल व्योम mb862xxfb_ग_लिखो_fअगरo(u32 count, u32 *data, काष्ठा fb_info *info)
अणु
	काष्ठा mb862xxfb_par *par = info->par;
	अटल u32 मुक्त;

	u32 total = 0;
	जबतक (total < count) अणु
		अगर (मुक्त) अणु
			outreg(geo, GDC_GEO_REG_INPUT_FIFO, data[total]);
			total++;
			मुक्त--;
		पूर्ण अन्यथा अणु
			मुक्त = (u32) inreg(draw, GDC_REG_FIFO_COUNT);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mb86290fb_copyarea(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_copyarea *area)
अणु
	__u32 cmd[6];

	cmd[0] = (GDC_TYPE_SETREGISTER << 24) | (1 << 16) | GDC_REG_MODE_BITMAP;
	/* Set raster operation */
	cmd[1] = (2 << 7) | (GDC_ROP_COPY << 9);
	cmd[2] = GDC_TYPE_BLTCOPYP << 24;

	अगर (area->sx >= area->dx && area->sy >= area->dy)
		cmd[2] |= GDC_CMD_BLTCOPY_TOP_LEFT << 16;
	अन्यथा अगर (area->sx >= area->dx && area->sy <= area->dy)
		cmd[2] |= GDC_CMD_BLTCOPY_BOTTOM_LEFT << 16;
	अन्यथा अगर (area->sx <= area->dx && area->sy >= area->dy)
		cmd[2] |= GDC_CMD_BLTCOPY_TOP_RIGHT << 16;
	अन्यथा
		cmd[2] |= GDC_CMD_BLTCOPY_BOTTOM_RIGHT << 16;

	cmd[3] = (area->sy << 16) | area->sx;
	cmd[4] = (area->dy << 16) | area->dx;
	cmd[5] = (area->height << 16) | area->width;
	mb862xxfb_ग_लिखो_fअगरo(6, cmd, info);
पूर्ण

/*
 * Fill in the cmd array /GDC FIFO commands/ to draw a 1bit image.
 * Make sure cmd has enough room!
 */
अटल व्योम mb86290fb_imageblit1(u32 *cmd, u16 step, u16 dx, u16 dy,
				 u16 width, u16 height, u32 fgcolor,
				 u32 bgcolor, स्थिर काष्ठा fb_image *image,
				 काष्ठा fb_info *info)
अणु
	पूर्णांक i;
	अचिन्हित स्थिर अक्षर *line;
	u16 bytes;

	/* set colors and raster operation regs */
	cmd[0] = (GDC_TYPE_SETREGISTER << 24) | (1 << 16) | GDC_REG_MODE_BITMAP;
	/* Set raster operation */
	cmd[1] = (2 << 7) | (GDC_ROP_COPY << 9);
	cmd[2] =
	    (GDC_TYPE_SETCOLORREGISTER << 24) | (GDC_CMD_BODY_FORE_COLOR << 16);
	cmd[3] = fgcolor;
	cmd[4] =
	    (GDC_TYPE_SETCOLORREGISTER << 24) | (GDC_CMD_BODY_BACK_COLOR << 16);
	cmd[5] = bgcolor;

	i = 0;
	line = image->data;
	bytes = (image->width + 7) >> 3;

	/* and the image */
	cmd[6] = (GDC_TYPE_DRAWBITMAPP << 24) |
	    (GDC_CMD_BITMAP << 16) | (2 + (step * height));
	cmd[7] = (dy << 16) | dx;
	cmd[8] = (height << 16) | width;

	जबतक (i < height) अणु
		स_नकल(&cmd[9 + i * step], line, step << 2);
#अगर_घोषित __LITTLE_ENDIAN
		अणु
			पूर्णांक k = 0;
			क्रम (k = 0; k < step; k++)
				cmd[9 + i * step + k] =
				    cpu_to_be32(cmd[9 + i * step + k]);
		पूर्ण
#पूर्ण_अगर
		line += bytes;
		i++;
	पूर्ण
पूर्ण

/*
 * Fill in the cmd array /GDC FIFO commands/ to draw a 8bit image.
 * Make sure cmd has enough room!
 */
अटल व्योम mb86290fb_imageblit8(u32 *cmd, u16 step, u16 dx, u16 dy,
				 u16 width, u16 height, u32 fgcolor,
				 u32 bgcolor, स्थिर काष्ठा fb_image *image,
				 काष्ठा fb_info *info)
अणु
	पूर्णांक i, j;
	अचिन्हित स्थिर अक्षर *line, *ptr;
	u16 bytes;

	cmd[0] = (GDC_TYPE_DRAWBITMAPP << 24) |
	    (GDC_CMD_BLT_DRAW << 16) | (2 + (height * step));
	cmd[1] = (dy << 16) | dx;
	cmd[2] = (height << 16) | width;

	i = 0;
	line = ptr = image->data;
	bytes = image->width;

	जबतक (i < height) अणु
		ptr = line;
		क्रम (j = 0; j < step; j++) अणु
			cmd[3 + i * step + j] =
			    (((u32 *) (info->pseuकरो_palette))[*ptr]) & 0xffff;
			ptr++;
			cmd[3 + i * step + j] |=
			    ((((u32 *) (info->
					pseuकरो_palette))[*ptr]) & 0xffff) << 16;
			ptr++;
		पूर्ण

		line += bytes;
		i++;
	पूर्ण
पूर्ण

/*
 * Fill in the cmd array /GDC FIFO commands/ to draw a 16bit image.
 * Make sure cmd has enough room!
 */
अटल व्योम mb86290fb_imageblit16(u32 *cmd, u16 step, u16 dx, u16 dy,
				  u16 width, u16 height, u32 fgcolor,
				  u32 bgcolor, स्थिर काष्ठा fb_image *image,
				  काष्ठा fb_info *info)
अणु
	पूर्णांक i;
	अचिन्हित स्थिर अक्षर *line;
	u16 bytes;

	i = 0;
	line = image->data;
	bytes = image->width << 1;

	cmd[0] = (GDC_TYPE_DRAWBITMAPP << 24) |
	    (GDC_CMD_BLT_DRAW << 16) | (2 + step * height);
	cmd[1] = (dy << 16) | dx;
	cmd[2] = (height << 16) | width;

	जबतक (i < height) अणु
		स_नकल(&cmd[3 + i * step], line, step);
		line += bytes;
		i++;
	पूर्ण
पूर्ण

अटल व्योम mb86290fb_imageblit(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_image *image)
अणु
	u32 *cmd = शून्य;
	व्योम (*cmdfn) (u32 *, u16, u16, u16, u16, u16, u32, u32,
		       स्थिर काष्ठा fb_image *, काष्ठा fb_info *) = शून्य;
	u32 cmdlen;
	u32 fgcolor = 0, bgcolor = 0;
	u16 step;

	u16 width = image->width, height = image->height;
	u16 dx = image->dx, dy = image->dy;
	पूर्णांक x2, y2, vxres, vyres;

	x2 = image->dx + image->width;
	y2 = image->dy + image->height;
	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;
	x2 = min(x2, vxres);
	y2 = min(y2, vyres);
	width = x2 - dx;
	height = y2 - dy;

	चयन (image->depth) अणु
	हाल 1:
		step = (width + 31) >> 5;
		cmdlen = 9 + height * step;
		cmdfn = mb86290fb_imageblit1;
		अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
		    info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
			fgcolor =
			    ((u32 *) (info->pseuकरो_palette))[image->fg_color];
			bgcolor =
			    ((u32 *) (info->pseuकरो_palette))[image->bg_color];
		पूर्ण अन्यथा अणु
			fgcolor = image->fg_color;
			bgcolor = image->bg_color;
		पूर्ण

		अवरोध;

	हाल 8:
		step = (width + 1) >> 1;
		cmdlen = 3 + height * step;
		cmdfn = mb86290fb_imageblit8;
		अवरोध;

	हाल 16:
		step = (width + 1) >> 1;
		cmdlen = 3 + height * step;
		cmdfn = mb86290fb_imageblit16;
		अवरोध;

	शेष:
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	cmd = kदो_स्मृति_array(cmdlen, 4, GFP_DMA);
	अगर (!cmd)
		वापस cfb_imageblit(info, image);
	cmdfn(cmd, step, dx, dy, width, height, fgcolor, bgcolor, image, info);
	mb862xxfb_ग_लिखो_fअगरo(cmdlen, cmd, info);
	kमुक्त(cmd);
पूर्ण

अटल व्योम mb86290fb_fillrect(काष्ठा fb_info *info,
			       स्थिर काष्ठा fb_fillrect *rect)
अणु

	u32 x2, y2, vxres, vyres, height, width, fg;
	u32 cmd[7];

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	अगर (!rect->width || !rect->height || rect->dx > vxres
	    || rect->dy > vyres)
		वापस;

	/* We could use hardware clipping but on many cards you get around
	 * hardware clipping by writing to framebuffer directly. */
	x2 = rect->dx + rect->width;
	y2 = rect->dy + rect->height;
	x2 = min(x2, vxres);
	y2 = min(y2, vyres);
	width = x2 - rect->dx;
	height = y2 - rect->dy;
	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_सूचीECTCOLOR)
		fg = ((u32 *) (info->pseuकरो_palette))[rect->color];
	अन्यथा
		fg = rect->color;

	चयन (rect->rop) अणु

	हाल ROP_XOR:
		/* Set raster operation */
		cmd[1] = (2 << 7) | (GDC_ROP_XOR << 9);
		अवरोध;

	हाल ROP_COPY:
		/* Set raster operation */
		cmd[1] = (2 << 7) | (GDC_ROP_COPY << 9);
		अवरोध;

	पूर्ण

	cmd[0] = (GDC_TYPE_SETREGISTER << 24) | (1 << 16) | GDC_REG_MODE_BITMAP;
	/* cmd[1] set earlier */
	cmd[2] =
	    (GDC_TYPE_SETCOLORREGISTER << 24) | (GDC_CMD_BODY_FORE_COLOR << 16);
	cmd[3] = fg;
	cmd[4] = (GDC_TYPE_DRAWRECTP << 24) | (GDC_CMD_BLT_FILL << 16);
	cmd[5] = (rect->dy << 16) | (rect->dx);
	cmd[6] = (height << 16) | width;

	mb862xxfb_ग_लिखो_fअगरo(7, cmd, info);
पूर्ण

व्योम mb862xxfb_init_accel(काष्ठा fb_info *info, काष्ठा fb_ops *fbops, पूर्णांक xres)
अणु
	काष्ठा mb862xxfb_par *par = info->par;

	अगर (info->var.bits_per_pixel == 32) अणु
		fbops->fb_fillrect = cfb_fillrect;
		fbops->fb_copyarea = cfb_copyarea;
		fbops->fb_imageblit = cfb_imageblit;
	पूर्ण अन्यथा अणु
		outreg(disp, GC_L0EM, 3);
		fbops->fb_fillrect = mb86290fb_fillrect;
		fbops->fb_copyarea = mb86290fb_copyarea;
		fbops->fb_imageblit = mb86290fb_imageblit;
	पूर्ण
	outreg(draw, GDC_REG_DRAW_BASE, 0);
	outreg(draw, GDC_REG_MODE_MISC, 0x8000);
	outreg(draw, GDC_REG_X_RESOLUTION, xres);

	info->flags |=
	    FBINFO_HWACCEL_COPYAREA | FBINFO_HWACCEL_FILLRECT |
	    FBINFO_HWACCEL_IMAGEBLIT;
	info->fix.accel = 0xff;	/*FIXME: add right define */
पूर्ण

MODULE_LICENSE("GPL v2");
