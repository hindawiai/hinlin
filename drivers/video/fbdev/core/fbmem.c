<शैली गुरु>
/*
 *  linux/drivers/video/fbmem.c
 *
 *  Copyright (C) 1994 Martin Schaller
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>

#समावेश <linux/compat.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/major.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/vt.h>
#समावेश <linux/init.h>
#समावेश <linux/linux_logo.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/console.h>
#समावेश <linux/kmod.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/efi.h>
#समावेश <linux/fb.h>
#समावेश <linux/fbcon.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/fb.h>


    /*
     *  Frame buffer device initialization and setup routines
     */

#घोषणा FBPIXMAPSIZE	(1024 * 8)

अटल DEFINE_MUTEX(registration_lock);

काष्ठा fb_info *रेजिस्टरed_fb[FB_MAX] __पढ़ो_mostly;
EXPORT_SYMBOL(रेजिस्टरed_fb);

पूर्णांक num_रेजिस्टरed_fb __पढ़ो_mostly;
EXPORT_SYMBOL(num_रेजिस्टरed_fb);

bool fb_center_logo __पढ़ो_mostly;

पूर्णांक fb_logo_count __पढ़ो_mostly = -1;

अटल काष्ठा fb_info *get_fb_info(अचिन्हित पूर्णांक idx)
अणु
	काष्ठा fb_info *fb_info;

	अगर (idx >= FB_MAX)
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&registration_lock);
	fb_info = रेजिस्टरed_fb[idx];
	अगर (fb_info)
		atomic_inc(&fb_info->count);
	mutex_unlock(&registration_lock);

	वापस fb_info;
पूर्ण

अटल व्योम put_fb_info(काष्ठा fb_info *fb_info)
अणु
	अगर (!atomic_dec_and_test(&fb_info->count))
		वापस;
	अगर (fb_info->fbops->fb_destroy)
		fb_info->fbops->fb_destroy(fb_info);
पूर्ण

/*
 * Helpers
 */

पूर्णांक fb_get_color_depth(काष्ठा fb_var_screeninfo *var,
		       काष्ठा fb_fix_screeninfo *fix)
अणु
	पूर्णांक depth = 0;

	अगर (fix->visual == FB_VISUAL_MONO01 ||
	    fix->visual == FB_VISUAL_MONO10)
		depth = 1;
	अन्यथा अणु
		अगर (var->green.length == var->blue.length &&
		    var->green.length == var->red.length &&
		    var->green.offset == var->blue.offset &&
		    var->green.offset == var->red.offset)
			depth = var->green.length;
		अन्यथा
			depth = var->green.length + var->red.length +
				var->blue.length;
	पूर्ण

	वापस depth;
पूर्ण
EXPORT_SYMBOL(fb_get_color_depth);

/*
 * Data padding functions.
 */
व्योम fb_pad_aligned_buffer(u8 *dst, u32 d_pitch, u8 *src, u32 s_pitch, u32 height)
अणु
	__fb_pad_aligned_buffer(dst, d_pitch, src, s_pitch, height);
पूर्ण
EXPORT_SYMBOL(fb_pad_aligned_buffer);

व्योम fb_pad_unaligned_buffer(u8 *dst, u32 d_pitch, u8 *src, u32 idx, u32 height,
				u32 shअगरt_high, u32 shअगरt_low, u32 mod)
अणु
	u8 mask = (u8) (0xfff << shअगरt_high), पंचांगp;
	पूर्णांक i, j;

	क्रम (i = height; i--; ) अणु
		क्रम (j = 0; j < idx; j++) अणु
			पंचांगp = dst[j];
			पंचांगp &= mask;
			पंचांगp |= *src >> shअगरt_low;
			dst[j] = पंचांगp;
			पंचांगp = *src << shअगरt_high;
			dst[j+1] = पंचांगp;
			src++;
		पूर्ण
		पंचांगp = dst[idx];
		पंचांगp &= mask;
		पंचांगp |= *src >> shअगरt_low;
		dst[idx] = पंचांगp;
		अगर (shअगरt_high < mod) अणु
			पंचांगp = *src << shअगरt_high;
			dst[idx+1] = पंचांगp;
		पूर्ण
		src++;
		dst += d_pitch;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fb_pad_unaligned_buffer);

/*
 * we need to lock this section since fb_cursor
 * may use fb_imageblit()
 */
अक्षर* fb_get_buffer_offset(काष्ठा fb_info *info, काष्ठा fb_pixmap *buf, u32 size)
अणु
	u32 align = buf->buf_align - 1, offset;
	अक्षर *addr = buf->addr;

	/* If IO mapped, we need to sync beक्रमe access, no sharing of
	 * the pixmap is करोne
	 */
	अगर (buf->flags & FB_PIXMAP_IO) अणु
		अगर (info->fbops->fb_sync && (buf->flags & FB_PIXMAP_SYNC))
			info->fbops->fb_sync(info);
		वापस addr;
	पूर्ण

	/* See अगर we fit in the reमुख्यing pixmap space */
	offset = buf->offset + align;
	offset &= ~align;
	अगर (offset + size > buf->size) अणु
		/* We करो not fit. In order to be able to re-use the buffer,
		 * we must ensure no asynchronous DMA'ing or whatever operation
		 * is in progress, we sync क्रम that.
		 */
		अगर (info->fbops->fb_sync && (buf->flags & FB_PIXMAP_SYNC))
			info->fbops->fb_sync(info);
		offset = 0;
	पूर्ण
	buf->offset = offset + size;
	addr += offset;

	वापस addr;
पूर्ण
EXPORT_SYMBOL(fb_get_buffer_offset);

#अगर_घोषित CONFIG_LOGO

अटल अंतरभूत अचिन्हित safe_shअगरt(अचिन्हित d, पूर्णांक n)
अणु
	वापस n < 0 ? d >> -n : d << n;
पूर्ण

अटल व्योम fb_set_logocmap(काष्ठा fb_info *info,
				   स्थिर काष्ठा linux_logo *logo)
अणु
	काष्ठा fb_cmap palette_cmap;
	u16 palette_green[16];
	u16 palette_blue[16];
	u16 palette_red[16];
	पूर्णांक i, j, n;
	स्थिर अचिन्हित अक्षर *clut = logo->clut;

	palette_cmap.start = 0;
	palette_cmap.len = 16;
	palette_cmap.red = palette_red;
	palette_cmap.green = palette_green;
	palette_cmap.blue = palette_blue;
	palette_cmap.transp = शून्य;

	क्रम (i = 0; i < logo->clutsize; i += n) अणु
		n = logo->clutsize - i;
		/* palette_cmap provides space क्रम only 16 colors at once */
		अगर (n > 16)
			n = 16;
		palette_cmap.start = 32 + i;
		palette_cmap.len = n;
		क्रम (j = 0; j < n; ++j) अणु
			palette_cmap.red[j] = clut[0] << 8 | clut[0];
			palette_cmap.green[j] = clut[1] << 8 | clut[1];
			palette_cmap.blue[j] = clut[2] << 8 | clut[2];
			clut += 3;
		पूर्ण
		fb_set_cmap(&palette_cmap, info);
	पूर्ण
पूर्ण

अटल व्योम  fb_set_logo_truepalette(काष्ठा fb_info *info,
					    स्थिर काष्ठा linux_logo *logo,
					    u32 *palette)
अणु
	अटल स्थिर अचिन्हित अक्षर mask[] = अणु 0,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff पूर्ण;
	अचिन्हित अक्षर redmask, greenmask, bluemask;
	पूर्णांक redshअगरt, greenshअगरt, blueshअगरt;
	पूर्णांक i;
	स्थिर अचिन्हित अक्षर *clut = logo->clut;

	/*
	 * We have to create a temporary palette since console palette is only
	 * 16 colors दीर्घ.
	 */
	/* Bug: Doesn't obey msb_right ... (who needs that?) */
	redmask   = mask[info->var.red.length   < 8 ? info->var.red.length   : 8];
	greenmask = mask[info->var.green.length < 8 ? info->var.green.length : 8];
	bluemask  = mask[info->var.blue.length  < 8 ? info->var.blue.length  : 8];
	redshअगरt   = info->var.red.offset   - (8 - info->var.red.length);
	greenshअगरt = info->var.green.offset - (8 - info->var.green.length);
	blueshअगरt  = info->var.blue.offset  - (8 - info->var.blue.length);

	क्रम ( i = 0; i < logo->clutsize; i++) अणु
		palette[i+32] = (safe_shअगरt((clut[0] & redmask), redshअगरt) |
				 safe_shअगरt((clut[1] & greenmask), greenshअगरt) |
				 safe_shअगरt((clut[2] & bluemask), blueshअगरt));
		clut += 3;
	पूर्ण
पूर्ण

अटल व्योम fb_set_logo_directpalette(काष्ठा fb_info *info,
					     स्थिर काष्ठा linux_logo *logo,
					     u32 *palette)
अणु
	पूर्णांक redshअगरt, greenshअगरt, blueshअगरt;
	पूर्णांक i;

	redshअगरt = info->var.red.offset;
	greenshअगरt = info->var.green.offset;
	blueshअगरt = info->var.blue.offset;

	क्रम (i = 32; i < 32 + logo->clutsize; i++)
		palette[i] = i << redshअगरt | i << greenshअगरt | i << blueshअगरt;
पूर्ण

अटल व्योम fb_set_logo(काष्ठा fb_info *info,
			       स्थिर काष्ठा linux_logo *logo, u8 *dst,
			       पूर्णांक depth)
अणु
	पूर्णांक i, j, k;
	स्थिर u8 *src = logo->data;
	u8 xor = (info->fix.visual == FB_VISUAL_MONO01) ? 0xff : 0;
	u8 fg = 1, d;

	चयन (fb_get_color_depth(&info->var, &info->fix)) अणु
	हाल 1:
		fg = 1;
		अवरोध;
	हाल 2:
		fg = 3;
		अवरोध;
	शेष:
		fg = 7;
		अवरोध;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_MONO01 ||
	    info->fix.visual == FB_VISUAL_MONO10)
		fg = ~((u8) (0xfff << info->var.green.length));

	चयन (depth) अणु
	हाल 4:
		क्रम (i = 0; i < logo->height; i++)
			क्रम (j = 0; j < logo->width; src++) अणु
				*dst++ = *src >> 4;
				j++;
				अगर (j < logo->width) अणु
					*dst++ = *src & 0x0f;
					j++;
				पूर्ण
			पूर्ण
		अवरोध;
	हाल 1:
		क्रम (i = 0; i < logo->height; i++) अणु
			क्रम (j = 0; j < logo->width; src++) अणु
				d = *src ^ xor;
				क्रम (k = 7; k >= 0 && j < logo->width; k--) अणु
					*dst++ = ((d >> k) & 1) ? fg : 0;
					j++;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Three (3) kinds of logo maps exist.  linux_logo_clut224 (>16 colors),
 * linux_logo_vga16 (16 colors) and linux_logo_mono (2 colors).  Depending on
 * the visual क्रमmat and color depth of the framebuffer, the DAC, the
 * pseuकरो_palette, and the logo data will be adjusted accordingly.
 *
 * Case 1 - linux_logo_clut224:
 * Color exceeds the number of console colors (16), thus we set the hardware DAC
 * using fb_set_cmap() appropriately.  The "needs_cmapreset"  flag will be set.
 *
 * For visuals that require color info from the pseuकरो_palette, we also स्थिरruct
 * one क्रम temporary use. The "needs_directpalette" or "needs_truepalette" flags
 * will be set.
 *
 * Case 2 - linux_logo_vga16:
 * The number of colors just matches the console colors, thus there is no need
 * to set the DAC or the pseuकरो_palette.  However, the biपंचांगap is packed, ie,
 * each byte contains color inक्रमmation क्रम two pixels (upper and lower nibble).
 * To be consistent with fb_imageblit() usage, we thereक्रमe separate the two
 * nibbles पूर्णांकo separate bytes. The "depth" flag will be set to 4.
 *
 * Case 3 - linux_logo_mono:
 * This is similar with Case 2.  Each byte contains inक्रमmation क्रम 8 pixels.
 * We isolate each bit and expand each पूर्णांकo a byte. The "depth" flag will
 * be set to 1.
 */
अटल काष्ठा logo_data अणु
	पूर्णांक depth;
	पूर्णांक needs_directpalette;
	पूर्णांक needs_truepalette;
	पूर्णांक needs_cmapreset;
	स्थिर काष्ठा linux_logo *logo;
पूर्ण fb_logo __पढ़ो_mostly;

अटल व्योम fb_rotate_logo_ud(स्थिर u8 *in, u8 *out, u32 width, u32 height)
अणु
	u32 size = width * height, i;

	out += size - 1;

	क्रम (i = size; i--; )
		*out-- = *in++;
पूर्ण

अटल व्योम fb_rotate_logo_cw(स्थिर u8 *in, u8 *out, u32 width, u32 height)
अणु
	पूर्णांक i, j, h = height - 1;

	क्रम (i = 0; i < height; i++)
		क्रम (j = 0; j < width; j++)
				out[height * j + h - i] = *in++;
पूर्ण

अटल व्योम fb_rotate_logo_ccw(स्थिर u8 *in, u8 *out, u32 width, u32 height)
अणु
	पूर्णांक i, j, w = width - 1;

	क्रम (i = 0; i < height; i++)
		क्रम (j = 0; j < width; j++)
			out[height * (w - j) + i] = *in++;
पूर्ण

अटल व्योम fb_rotate_logo(काष्ठा fb_info *info, u8 *dst,
			   काष्ठा fb_image *image, पूर्णांक rotate)
अणु
	u32 पंचांगp;

	अगर (rotate == FB_ROTATE_UD) अणु
		fb_rotate_logo_ud(image->data, dst, image->width,
				  image->height);
		image->dx = info->var.xres - image->width - image->dx;
		image->dy = info->var.yres - image->height - image->dy;
	पूर्ण अन्यथा अगर (rotate == FB_ROTATE_CW) अणु
		fb_rotate_logo_cw(image->data, dst, image->width,
				  image->height);
		पंचांगp = image->width;
		image->width = image->height;
		image->height = पंचांगp;
		पंचांगp = image->dy;
		image->dy = image->dx;
		image->dx = info->var.xres - image->width - पंचांगp;
	पूर्ण अन्यथा अगर (rotate == FB_ROTATE_CCW) अणु
		fb_rotate_logo_ccw(image->data, dst, image->width,
				   image->height);
		पंचांगp = image->width;
		image->width = image->height;
		image->height = पंचांगp;
		पंचांगp = image->dx;
		image->dx = image->dy;
		image->dy = info->var.yres - image->height - पंचांगp;
	पूर्ण

	image->data = dst;
पूर्ण

अटल व्योम fb_करो_show_logo(काष्ठा fb_info *info, काष्ठा fb_image *image,
			    पूर्णांक rotate, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक x;

	अगर (image->width > info->var.xres || image->height > info->var.yres)
		वापस;

	अगर (rotate == FB_ROTATE_UR) अणु
		क्रम (x = 0;
		     x < num && image->dx + image->width <= info->var.xres;
		     x++) अणु
			info->fbops->fb_imageblit(info, image);
			image->dx += image->width + 8;
		पूर्ण
	पूर्ण अन्यथा अगर (rotate == FB_ROTATE_UD) अणु
		u32 dx = image->dx;

		क्रम (x = 0; x < num && image->dx <= dx; x++) अणु
			info->fbops->fb_imageblit(info, image);
			image->dx -= image->width + 8;
		पूर्ण
	पूर्ण अन्यथा अगर (rotate == FB_ROTATE_CW) अणु
		क्रम (x = 0;
		     x < num && image->dy + image->height <= info->var.yres;
		     x++) अणु
			info->fbops->fb_imageblit(info, image);
			image->dy += image->height + 8;
		पूर्ण
	पूर्ण अन्यथा अगर (rotate == FB_ROTATE_CCW) अणु
		u32 dy = image->dy;

		क्रम (x = 0; x < num && image->dy <= dy; x++) अणु
			info->fbops->fb_imageblit(info, image);
			image->dy -= image->height + 8;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक fb_show_logo_line(काष्ठा fb_info *info, पूर्णांक rotate,
			     स्थिर काष्ठा linux_logo *logo, पूर्णांक y,
			     अचिन्हित पूर्णांक n)
अणु
	u32 *palette = शून्य, *saved_pseuकरो_palette = शून्य;
	अचिन्हित अक्षर *logo_new = शून्य, *logo_rotate = शून्य;
	काष्ठा fb_image image;

	/* Return अगर the frame buffer is not mapped or suspended */
	अगर (logo == शून्य || info->state != FBINFO_STATE_RUNNING ||
	    info->fbops->owner)
		वापस 0;

	image.depth = 8;
	image.data = logo->data;

	अगर (fb_logo.needs_cmapreset)
		fb_set_logocmap(info, logo);

	अगर (fb_logo.needs_truepalette ||
	    fb_logo.needs_directpalette) अणु
		palette = kदो_स्मृति(256 * 4, GFP_KERNEL);
		अगर (palette == शून्य)
			वापस 0;

		अगर (fb_logo.needs_truepalette)
			fb_set_logo_truepalette(info, logo, palette);
		अन्यथा
			fb_set_logo_directpalette(info, logo, palette);

		saved_pseuकरो_palette = info->pseuकरो_palette;
		info->pseuकरो_palette = palette;
	पूर्ण

	अगर (fb_logo.depth <= 4) अणु
		logo_new = kदो_स्मृति_array(logo->width, logo->height,
					 GFP_KERNEL);
		अगर (logo_new == शून्य) अणु
			kमुक्त(palette);
			अगर (saved_pseuकरो_palette)
				info->pseuकरो_palette = saved_pseuकरो_palette;
			वापस 0;
		पूर्ण
		image.data = logo_new;
		fb_set_logo(info, logo, logo_new, fb_logo.depth);
	पूर्ण

	अगर (fb_center_logo) अणु
		पूर्णांक xres = info->var.xres;
		पूर्णांक yres = info->var.yres;

		अगर (rotate == FB_ROTATE_CW || rotate == FB_ROTATE_CCW) अणु
			xres = info->var.yres;
			yres = info->var.xres;
		पूर्ण

		जबतक (n && (n * (logo->width + 8) - 8 > xres))
			--n;
		image.dx = (xres - n * (logo->width + 8) - 8) / 2;
		image.dy = y ?: (yres - logo->height) / 2;
	पूर्ण अन्यथा अणु
		image.dx = 0;
		image.dy = y;
	पूर्ण

	image.width = logo->width;
	image.height = logo->height;

	अगर (rotate) अणु
		logo_rotate = kदो_स्मृति_array(logo->width, logo->height,
					    GFP_KERNEL);
		अगर (logo_rotate)
			fb_rotate_logo(info, logo_rotate, &image, rotate);
	पूर्ण

	fb_करो_show_logo(info, &image, rotate, n);

	kमुक्त(palette);
	अगर (saved_pseuकरो_palette != शून्य)
		info->pseuकरो_palette = saved_pseuकरो_palette;
	kमुक्त(logo_new);
	kमुक्त(logo_rotate);
	वापस image.dy + logo->height;
पूर्ण


#अगर_घोषित CONFIG_FB_LOGO_EXTRA

#घोषणा FB_LOGO_EX_NUM_MAX 10
अटल काष्ठा logo_data_extra अणु
	स्थिर काष्ठा linux_logo *logo;
	अचिन्हित पूर्णांक n;
पूर्ण fb_logo_ex[FB_LOGO_EX_NUM_MAX];
अटल अचिन्हित पूर्णांक fb_logo_ex_num;

व्योम fb_append_extra_logo(स्थिर काष्ठा linux_logo *logo, अचिन्हित पूर्णांक n)
अणु
	अगर (!n || fb_logo_ex_num == FB_LOGO_EX_NUM_MAX)
		वापस;

	fb_logo_ex[fb_logo_ex_num].logo = logo;
	fb_logo_ex[fb_logo_ex_num].n = n;
	fb_logo_ex_num++;
पूर्ण

अटल पूर्णांक fb_prepare_extra_logos(काष्ठा fb_info *info, अचिन्हित पूर्णांक height,
				  अचिन्हित पूर्णांक yres)
अणु
	अचिन्हित पूर्णांक i;

	/* FIXME: logo_ex supports only truecolor fb. */
	अगर (info->fix.visual != FB_VISUAL_TRUECOLOR)
		fb_logo_ex_num = 0;

	क्रम (i = 0; i < fb_logo_ex_num; i++) अणु
		अगर (fb_logo_ex[i].logo->type != fb_logo.logo->type) अणु
			fb_logo_ex[i].logo = शून्य;
			जारी;
		पूर्ण
		height += fb_logo_ex[i].logo->height;
		अगर (height > yres) अणु
			height -= fb_logo_ex[i].logo->height;
			fb_logo_ex_num = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस height;
पूर्ण

अटल पूर्णांक fb_show_extra_logos(काष्ठा fb_info *info, पूर्णांक y, पूर्णांक rotate)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < fb_logo_ex_num; i++)
		y = fb_show_logo_line(info, rotate,
				      fb_logo_ex[i].logo, y, fb_logo_ex[i].n);

	वापस y;
पूर्ण

#अन्यथा /* !CONFIG_FB_LOGO_EXTRA */

अटल अंतरभूत पूर्णांक fb_prepare_extra_logos(काष्ठा fb_info *info,
					 अचिन्हित पूर्णांक height,
					 अचिन्हित पूर्णांक yres)
अणु
	वापस height;
पूर्ण

अटल अंतरभूत पूर्णांक fb_show_extra_logos(काष्ठा fb_info *info, पूर्णांक y, पूर्णांक rotate)
अणु
	वापस y;
पूर्ण

#पूर्ण_अगर /* CONFIG_FB_LOGO_EXTRA */


पूर्णांक fb_prepare_logo(काष्ठा fb_info *info, पूर्णांक rotate)
अणु
	पूर्णांक depth = fb_get_color_depth(&info->var, &info->fix);
	अचिन्हित पूर्णांक yres;
	पूर्णांक height;

	स_रखो(&fb_logo, 0, माप(काष्ठा logo_data));

	अगर (info->flags & FBINFO_MISC_TILEBLITTING ||
	    info->fbops->owner || !fb_logo_count)
		वापस 0;

	अगर (info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
		depth = info->var.blue.length;
		अगर (info->var.red.length < depth)
			depth = info->var.red.length;
		अगर (info->var.green.length < depth)
			depth = info->var.green.length;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR && depth > 4) अणु
		/* assume console colormap */
		depth = 4;
	पूर्ण

	/* Return अगर no suitable logo was found */
	fb_logo.logo = fb_find_logo(depth);

	अगर (!fb_logo.logo) अणु
		वापस 0;
	पूर्ण

	अगर (rotate == FB_ROTATE_UR || rotate == FB_ROTATE_UD)
		yres = info->var.yres;
	अन्यथा
		yres = info->var.xres;

	अगर (fb_logo.logo->height > yres) अणु
		fb_logo.logo = शून्य;
		वापस 0;
	पूर्ण

	/* What depth we asked क्रम might be dअगरferent from what we get */
	अगर (fb_logo.logo->type == LINUX_LOGO_CLUT224)
		fb_logo.depth = 8;
	अन्यथा अगर (fb_logo.logo->type == LINUX_LOGO_VGA16)
		fb_logo.depth = 4;
	अन्यथा
		fb_logo.depth = 1;


	अगर (fb_logo.depth > 4 && depth > 4) अणु
		चयन (info->fix.visual) अणु
		हाल FB_VISUAL_TRUECOLOR:
			fb_logo.needs_truepalette = 1;
			अवरोध;
		हाल FB_VISUAL_सूचीECTCOLOR:
			fb_logo.needs_directpalette = 1;
			fb_logo.needs_cmapreset = 1;
			अवरोध;
		हाल FB_VISUAL_PSEUDOCOLOR:
			fb_logo.needs_cmapreset = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	height = fb_logo.logo->height;
	अगर (fb_center_logo)
		height += (yres - fb_logo.logo->height) / 2;

	वापस fb_prepare_extra_logos(info, height, yres);
पूर्ण

पूर्णांक fb_show_logo(काष्ठा fb_info *info, पूर्णांक rotate)
अणु
	अचिन्हित पूर्णांक count;
	पूर्णांक y;

	अगर (!fb_logo_count)
		वापस 0;

	count = fb_logo_count < 0 ? num_online_cpus() : fb_logo_count;
	y = fb_show_logo_line(info, rotate, fb_logo.logo, 0, count);
	y = fb_show_extra_logos(info, y, rotate);

	वापस y;
पूर्ण
#अन्यथा
पूर्णांक fb_prepare_logo(काष्ठा fb_info *info, पूर्णांक rotate) अणु वापस 0; पूर्ण
पूर्णांक fb_show_logo(काष्ठा fb_info *info, पूर्णांक rotate) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_LOGO */
EXPORT_SYMBOL(fb_prepare_logo);
EXPORT_SYMBOL(fb_show_logo);

अटल व्योम *fb_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&registration_lock);
	वापस (*pos < FB_MAX) ? pos : शून्य;
पूर्ण

अटल व्योम *fb_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस (*pos < FB_MAX) ? pos : शून्य;
पूर्ण

अटल व्योम fb_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	mutex_unlock(&registration_lock);
पूर्ण

अटल पूर्णांक fb_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i = *(loff_t *)v;
	काष्ठा fb_info *fi = रेजिस्टरed_fb[i];

	अगर (fi)
		seq_म_लिखो(m, "%d %s\n", fi->node, fi->fix.id);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations __maybe_unused proc_fb_seq_ops = अणु
	.start	= fb_seq_start,
	.next	= fb_seq_next,
	.stop	= fb_seq_stop,
	.show	= fb_seq_show,
पूर्ण;

/*
 * We hold a reference to the fb_info in file->निजी_data,
 * but अगर the current रेजिस्टरed fb has changed, we करोn't
 * actually want to use it.
 *
 * So look up the fb_info using the inode minor number,
 * and just verअगरy it against the reference we have.
 */
अटल काष्ठा fb_info *file_fb_info(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक fbidx = iminor(inode);
	काष्ठा fb_info *info = रेजिस्टरed_fb[fbidx];

	अगर (info != file->निजी_data)
		info = शून्य;
	वापस info;
पूर्ण

अटल sमाप_प्रकार
fb_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ p = *ppos;
	काष्ठा fb_info *info = file_fb_info(file);
	u8 *buffer, *dst;
	u8 __iomem *src;
	पूर्णांक c, cnt = 0, err = 0;
	अचिन्हित दीर्घ total_size;

	अगर (!info || ! info->screen_base)
		वापस -ENODEV;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	अगर (info->fbops->fb_पढ़ो)
		वापस info->fbops->fb_पढ़ो(info, buf, count, ppos);

	total_size = info->screen_size;

	अगर (total_size == 0)
		total_size = info->fix.smem_len;

	अगर (p >= total_size)
		वापस 0;

	अगर (count >= total_size)
		count = total_size;

	अगर (count + p > total_size)
		count = total_size - p;

	buffer = kदो_स्मृति((count > PAGE_SIZE) ? PAGE_SIZE : count,
			 GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	src = (u8 __iomem *) (info->screen_base + p);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	जबतक (count) अणु
		c  = (count > PAGE_SIZE) ? PAGE_SIZE : count;
		dst = buffer;
		fb_स_नकल_fromfb(dst, src, c);
		dst += c;
		src += c;

		अगर (copy_to_user(buf, buffer, c)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		*ppos += c;
		buf += c;
		cnt += c;
		count -= c;
	पूर्ण

	kमुक्त(buffer);

	वापस (err) ? err : cnt;
पूर्ण

अटल sमाप_प्रकार
fb_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ p = *ppos;
	काष्ठा fb_info *info = file_fb_info(file);
	u8 *buffer, *src;
	u8 __iomem *dst;
	पूर्णांक c, cnt = 0, err = 0;
	अचिन्हित दीर्घ total_size;

	अगर (!info || !info->screen_base)
		वापस -ENODEV;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	अगर (info->fbops->fb_ग_लिखो)
		वापस info->fbops->fb_ग_लिखो(info, buf, count, ppos);

	total_size = info->screen_size;

	अगर (total_size == 0)
		total_size = info->fix.smem_len;

	अगर (p > total_size)
		वापस -EFBIG;

	अगर (count > total_size) अणु
		err = -EFBIG;
		count = total_size;
	पूर्ण

	अगर (count + p > total_size) अणु
		अगर (!err)
			err = -ENOSPC;

		count = total_size - p;
	पूर्ण

	buffer = kदो_स्मृति((count > PAGE_SIZE) ? PAGE_SIZE : count,
			 GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	dst = (u8 __iomem *) (info->screen_base + p);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	जबतक (count) अणु
		c = (count > PAGE_SIZE) ? PAGE_SIZE : count;
		src = buffer;

		अगर (copy_from_user(src, buf, c)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		fb_स_नकल_tofb(dst, src, c);
		dst += c;
		src += c;
		*ppos += c;
		buf += c;
		cnt += c;
		count -= c;
	पूर्ण

	kमुक्त(buffer);

	वापस (cnt) ? cnt : err;
पूर्ण

पूर्णांक
fb_pan_display(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा fb_fix_screeninfo *fix = &info->fix;
	अचिन्हित पूर्णांक yres = info->var.yres;
	पूर्णांक err = 0;

	अगर (var->yoffset > 0) अणु
		अगर (var->vmode & FB_VMODE_YWRAP) अणु
			अगर (!fix->ywrapstep || (var->yoffset % fix->ywrapstep))
				err = -EINVAL;
			अन्यथा
				yres = 0;
		पूर्ण अन्यथा अगर (!fix->ypanstep || (var->yoffset % fix->ypanstep))
			err = -EINVAL;
	पूर्ण

	अगर (var->xoffset > 0 && (!fix->xpanstep ||
				 (var->xoffset % fix->xpanstep)))
		err = -EINVAL;

	अगर (err || !info->fbops->fb_pan_display ||
	    var->yoffset > info->var.yres_भव - yres ||
	    var->xoffset > info->var.xres_भव - info->var.xres)
		वापस -EINVAL;

	अगर ((err = info->fbops->fb_pan_display(var, info)))
		वापस err;
	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;
	अगर (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	अन्यथा
		info->var.vmode &= ~FB_VMODE_YWRAP;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fb_pan_display);

अटल पूर्णांक fb_check_caps(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var,
			 u32 activate)
अणु
	काष्ठा fb_blit_caps caps, fbcaps;
	पूर्णांक err = 0;

	स_रखो(&caps, 0, माप(caps));
	स_रखो(&fbcaps, 0, माप(fbcaps));
	caps.flags = (activate & FB_ACTIVATE_ALL) ? 1 : 0;
	fbcon_get_requirement(info, &caps);
	info->fbops->fb_get_caps(info, &fbcaps, var);

	अगर (((fbcaps.x ^ caps.x) & caps.x) ||
	    ((fbcaps.y ^ caps.y) & caps.y) ||
	    (fbcaps.len < caps.len))
		err = -EINVAL;

	वापस err;
पूर्ण

पूर्णांक
fb_set_var(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक ret = 0;
	u32 activate;
	काष्ठा fb_var_screeninfo old_var;
	काष्ठा fb_videomode mode;
	काष्ठा fb_event event;

	अगर (var->activate & FB_ACTIVATE_INV_MODE) अणु
		काष्ठा fb_videomode mode1, mode2;

		fb_var_to_videomode(&mode1, var);
		fb_var_to_videomode(&mode2, &info->var);
		/* make sure we करोn't delete the videomode of current var */
		ret = fb_mode_is_equal(&mode1, &mode2);

		अगर (!ret)
			fbcon_mode_deleted(info, &mode1);

		अगर (!ret)
			fb_delete_videomode(&mode1, &info->modelist);


		वापस ret ? -EINVAL : 0;
	पूर्ण

	अगर (!(var->activate & FB_ACTIVATE_FORCE) &&
	    !स_भेद(&info->var, var, माप(काष्ठा fb_var_screeninfo)))
		वापस 0;

	activate = var->activate;

	/* When using FOURCC mode, make sure the red, green, blue and
	 * transp fields are set to 0.
	 */
	अगर ((info->fix.capabilities & FB_CAP_FOURCC) &&
	    var->grayscale > 1) अणु
		अगर (var->red.offset     || var->green.offset    ||
		    var->blue.offset    || var->transp.offset   ||
		    var->red.length     || var->green.length    ||
		    var->blue.length    || var->transp.length   ||
		    var->red.msb_right  || var->green.msb_right ||
		    var->blue.msb_right || var->transp.msb_right)
			वापस -EINVAL;
	पूर्ण

	अगर (!info->fbops->fb_check_var) अणु
		*var = info->var;
		वापस 0;
	पूर्ण

	/* bitfill_aligned() assumes that it's at least 8x8 */
	अगर (var->xres < 8 || var->yres < 8)
		वापस -EINVAL;

	ret = info->fbops->fb_check_var(var, info);

	अगर (ret)
		वापस ret;

	अगर ((var->activate & FB_ACTIVATE_MASK) != FB_ACTIVATE_NOW)
		वापस 0;

	अगर (info->fbops->fb_get_caps) अणु
		ret = fb_check_caps(info, var, activate);

		अगर (ret)
			वापस ret;
	पूर्ण

	old_var = info->var;
	info->var = *var;

	अगर (info->fbops->fb_set_par) अणु
		ret = info->fbops->fb_set_par(info);

		अगर (ret) अणु
			info->var = old_var;
			prपूर्णांकk(KERN_WARNING "detected "
				"fb_set_par error, "
				"error code: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	fb_pan_display(info, &info->var);
	fb_set_cmap(&info->cmap, info);
	fb_var_to_videomode(&mode, &info->var);

	अगर (info->modelist.prev && info->modelist.next &&
	    !list_empty(&info->modelist))
		ret = fb_add_videomode(&mode, &info->modelist);

	अगर (ret)
		वापस ret;

	event.info = info;
	event.data = &mode;
	fb_notअगरier_call_chain(FB_EVENT_MODE_CHANGE, &event);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fb_set_var);

पूर्णांक
fb_blank(काष्ठा fb_info *info, पूर्णांक blank)
अणु
	काष्ठा fb_event event;
	पूर्णांक ret = -EINVAL;

	अगर (blank > FB_BLANK_POWERDOWN)
		blank = FB_BLANK_POWERDOWN;

	event.info = info;
	event.data = &blank;

	अगर (info->fbops->fb_blank)
		ret = info->fbops->fb_blank(blank, info);

	अगर (!ret)
		fb_notअगरier_call_chain(FB_EVENT_BLANK, &event);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fb_blank);

अटल दीर्घ करो_fb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg)
अणु
	स्थिर काष्ठा fb_ops *fb;
	काष्ठा fb_var_screeninfo var;
	काष्ठा fb_fix_screeninfo fix;
	काष्ठा fb_cmap cmap_from;
	काष्ठा fb_cmap_user cmap;
	व्योम __user *argp = (व्योम __user *)arg;
	दीर्घ ret = 0;

	चयन (cmd) अणु
	हाल FBIOGET_VSCREENINFO:
		lock_fb_info(info);
		var = info->var;
		unlock_fb_info(info);

		ret = copy_to_user(argp, &var, माप(var)) ? -EFAULT : 0;
		अवरोध;
	हाल FBIOPUT_VSCREENINFO:
		अगर (copy_from_user(&var, argp, माप(var)))
			वापस -EFAULT;
		console_lock();
		lock_fb_info(info);
		ret = fb_set_var(info, &var);
		अगर (!ret)
			fbcon_update_vcs(info, var.activate & FB_ACTIVATE_ALL);
		unlock_fb_info(info);
		console_unlock();
		अगर (!ret && copy_to_user(argp, &var, माप(var)))
			ret = -EFAULT;
		अवरोध;
	हाल FBIOGET_FSCREENINFO:
		lock_fb_info(info);
		स_नकल(&fix, &info->fix, माप(fix));
		अगर (info->flags & FBINFO_HIDE_SMEM_START)
			fix.smem_start = 0;
		unlock_fb_info(info);

		ret = copy_to_user(argp, &fix, माप(fix)) ? -EFAULT : 0;
		अवरोध;
	हाल FBIOPUTCMAP:
		अगर (copy_from_user(&cmap, argp, माप(cmap)))
			वापस -EFAULT;
		ret = fb_set_user_cmap(&cmap, info);
		अवरोध;
	हाल FBIOGETCMAP:
		अगर (copy_from_user(&cmap, argp, माप(cmap)))
			वापस -EFAULT;
		lock_fb_info(info);
		cmap_from = info->cmap;
		unlock_fb_info(info);
		ret = fb_cmap_to_user(&cmap_from, &cmap);
		अवरोध;
	हाल FBIOPAN_DISPLAY:
		अगर (copy_from_user(&var, argp, माप(var)))
			वापस -EFAULT;
		console_lock();
		lock_fb_info(info);
		ret = fb_pan_display(info, &var);
		unlock_fb_info(info);
		console_unlock();
		अगर (ret == 0 && copy_to_user(argp, &var, माप(var)))
			वापस -EFAULT;
		अवरोध;
	हाल FBIO_CURSOR:
		ret = -EINVAL;
		अवरोध;
	हाल FBIOGET_CON2FBMAP:
		ret = fbcon_get_con2fb_map_ioctl(argp);
		अवरोध;
	हाल FBIOPUT_CON2FBMAP:
		ret = fbcon_set_con2fb_map_ioctl(argp);
		अवरोध;
	हाल FBIOBLANK:
		console_lock();
		lock_fb_info(info);
		ret = fb_blank(info, arg);
		/* might again call पूर्णांकo fb_blank */
		fbcon_fb_blanked(info, arg);
		unlock_fb_info(info);
		console_unlock();
		अवरोध;
	शेष:
		lock_fb_info(info);
		fb = info->fbops;
		अगर (fb->fb_ioctl)
			ret = fb->fb_ioctl(info, cmd, arg);
		अन्यथा
			ret = -ENOTTY;
		unlock_fb_info(info);
	पूर्ण
	वापस ret;
पूर्ण

अटल दीर्घ fb_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा fb_info *info = file_fb_info(file);

	अगर (!info)
		वापस -ENODEV;
	वापस करो_fb_ioctl(info, cmd, arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा fb_fix_screeninfo32 अणु
	अक्षर			id[16];
	compat_caddr_t		smem_start;
	u32			smem_len;
	u32			type;
	u32			type_aux;
	u32			visual;
	u16			xpanstep;
	u16			ypanstep;
	u16			ywrapstep;
	u32			line_length;
	compat_caddr_t		mmio_start;
	u32			mmio_len;
	u32			accel;
	u16			reserved[3];
पूर्ण;

काष्ठा fb_cmap32 अणु
	u32			start;
	u32			len;
	compat_caddr_t	red;
	compat_caddr_t	green;
	compat_caddr_t	blue;
	compat_caddr_t	transp;
पूर्ण;

अटल पूर्णांक fb_getput_cmap(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा fb_cmap32 cmap32;
	काष्ठा fb_cmap cmap_from;
	काष्ठा fb_cmap_user cmap;

	अगर (copy_from_user(&cmap32, compat_ptr(arg), माप(cmap32)))
		वापस -EFAULT;

	cmap = (काष्ठा fb_cmap_user) अणु
		.start	= cmap32.start,
		.len	= cmap32.len,
		.red	= compat_ptr(cmap32.red),
		.green	= compat_ptr(cmap32.green),
		.blue	= compat_ptr(cmap32.blue),
		.transp	= compat_ptr(cmap32.transp),
	पूर्ण;

	अगर (cmd == FBIOPUTCMAP)
		वापस fb_set_user_cmap(&cmap, info);

	lock_fb_info(info);
	cmap_from = info->cmap;
	unlock_fb_info(info);

	वापस fb_cmap_to_user(&cmap_from, &cmap);
पूर्ण

अटल पूर्णांक करो_fscreeninfo_to_user(काष्ठा fb_fix_screeninfo *fix,
				  काष्ठा fb_fix_screeninfo32 __user *fix32)
अणु
	__u32 data;
	पूर्णांक err;

	err = copy_to_user(&fix32->id, &fix->id, माप(fix32->id));

	data = (__u32) (अचिन्हित दीर्घ) fix->smem_start;
	err |= put_user(data, &fix32->smem_start);

	err |= put_user(fix->smem_len, &fix32->smem_len);
	err |= put_user(fix->type, &fix32->type);
	err |= put_user(fix->type_aux, &fix32->type_aux);
	err |= put_user(fix->visual, &fix32->visual);
	err |= put_user(fix->xpanstep, &fix32->xpanstep);
	err |= put_user(fix->ypanstep, &fix32->ypanstep);
	err |= put_user(fix->ywrapstep, &fix32->ywrapstep);
	err |= put_user(fix->line_length, &fix32->line_length);

	data = (__u32) (अचिन्हित दीर्घ) fix->mmio_start;
	err |= put_user(data, &fix32->mmio_start);

	err |= put_user(fix->mmio_len, &fix32->mmio_len);
	err |= put_user(fix->accel, &fix32->accel);
	err |= copy_to_user(fix32->reserved, fix->reserved,
			    माप(fix->reserved));

	अगर (err)
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक fb_get_fscreeninfo(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			      अचिन्हित दीर्घ arg)
अणु
	काष्ठा fb_fix_screeninfo fix;

	lock_fb_info(info);
	fix = info->fix;
	अगर (info->flags & FBINFO_HIDE_SMEM_START)
		fix.smem_start = 0;
	unlock_fb_info(info);
	वापस करो_fscreeninfo_to_user(&fix, compat_ptr(arg));
पूर्ण

अटल दीर्घ fb_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा fb_info *info = file_fb_info(file);
	स्थिर काष्ठा fb_ops *fb;
	दीर्घ ret = -ENOIOCTLCMD;

	अगर (!info)
		वापस -ENODEV;
	fb = info->fbops;
	चयन(cmd) अणु
	हाल FBIOGET_VSCREENINFO:
	हाल FBIOPUT_VSCREENINFO:
	हाल FBIOPAN_DISPLAY:
	हाल FBIOGET_CON2FBMAP:
	हाल FBIOPUT_CON2FBMAP:
		arg = (अचिन्हित दीर्घ) compat_ptr(arg);
		fallthrough;
	हाल FBIOBLANK:
		ret = करो_fb_ioctl(info, cmd, arg);
		अवरोध;

	हाल FBIOGET_FSCREENINFO:
		ret = fb_get_fscreeninfo(info, cmd, arg);
		अवरोध;

	हाल FBIOGETCMAP:
	हाल FBIOPUTCMAP:
		ret = fb_getput_cmap(info, cmd, arg);
		अवरोध;

	शेष:
		अगर (fb->fb_compat_ioctl)
			ret = fb->fb_compat_ioctl(info, cmd, arg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
fb_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा * vma)
अणु
	काष्ठा fb_info *info = file_fb_info(file);
	पूर्णांक (*fb_mmap_fn)(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma);
	अचिन्हित दीर्घ mmio_pgoff;
	अचिन्हित दीर्घ start;
	u32 len;

	अगर (!info)
		वापस -ENODEV;
	mutex_lock(&info->mm_lock);

	fb_mmap_fn = info->fbops->fb_mmap;

#अगर IS_ENABLED(CONFIG_FB_DEFERRED_IO)
	अगर (info->fbdefio)
		fb_mmap_fn = fb_deferred_io_mmap;
#पूर्ण_अगर

	अगर (fb_mmap_fn) अणु
		पूर्णांक res;

		/*
		 * The framebuffer needs to be accessed decrypted, be sure
		 * SME protection is हटाओd ahead of the call
		 */
		vma->vm_page_prot = pgprot_decrypted(vma->vm_page_prot);
		res = fb_mmap_fn(info, vma);
		mutex_unlock(&info->mm_lock);
		वापस res;
	पूर्ण

	/*
	 * Ugh. This can be either the frame buffer mapping, or
	 * अगर pgoff poपूर्णांकs past it, the mmio mapping.
	 */
	start = info->fix.smem_start;
	len = info->fix.smem_len;
	mmio_pgoff = PAGE_ALIGN((start & ~PAGE_MASK) + len) >> PAGE_SHIFT;
	अगर (vma->vm_pgoff >= mmio_pgoff) अणु
		अगर (info->var.accel_flags) अणु
			mutex_unlock(&info->mm_lock);
			वापस -EINVAL;
		पूर्ण

		vma->vm_pgoff -= mmio_pgoff;
		start = info->fix.mmio_start;
		len = info->fix.mmio_len;
	पूर्ण
	mutex_unlock(&info->mm_lock);

	vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	fb_pgprotect(file, vma, start);

	वापस vm_iomap_memory(vma, start, len);
पूर्ण

अटल पूर्णांक
fb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
__acquires(&info->lock)
__releases(&info->lock)
अणु
	पूर्णांक fbidx = iminor(inode);
	काष्ठा fb_info *info;
	पूर्णांक res = 0;

	info = get_fb_info(fbidx);
	अगर (!info) अणु
		request_module("fb%d", fbidx);
		info = get_fb_info(fbidx);
		अगर (!info)
			वापस -ENODEV;
	पूर्ण
	अगर (IS_ERR(info))
		वापस PTR_ERR(info);

	lock_fb_info(info);
	अगर (!try_module_get(info->fbops->owner)) अणु
		res = -ENODEV;
		जाओ out;
	पूर्ण
	file->निजी_data = info;
	अगर (info->fbops->fb_खोलो) अणु
		res = info->fbops->fb_खोलो(info,1);
		अगर (res)
			module_put(info->fbops->owner);
	पूर्ण
#अगर_घोषित CONFIG_FB_DEFERRED_IO
	अगर (info->fbdefio)
		fb_deferred_io_खोलो(info, inode, file);
#पूर्ण_अगर
out:
	unlock_fb_info(info);
	अगर (res)
		put_fb_info(info);
	वापस res;
पूर्ण

अटल पूर्णांक
fb_release(काष्ठा inode *inode, काष्ठा file *file)
__acquires(&info->lock)
__releases(&info->lock)
अणु
	काष्ठा fb_info * स्थिर info = file->निजी_data;

	lock_fb_info(info);
	अगर (info->fbops->fb_release)
		info->fbops->fb_release(info,1);
	module_put(info->fbops->owner);
	unlock_fb_info(info);
	put_fb_info(info);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_FB_PROVIDE_GET_FB_UNMAPPED_AREA) && !defined(CONFIG_MMU)
अचिन्हित दीर्घ get_fb_unmapped_area(काष्ठा file *filp,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				   अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा fb_info * स्थिर info = filp->निजी_data;
	अचिन्हित दीर्घ fb_size = PAGE_ALIGN(info->fix.smem_len);

	अगर (pgoff > fb_size || len > fb_size - pgoff)
		वापस -EINVAL;

	वापस (अचिन्हित दीर्घ)info->screen_base + pgoff;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations fb_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		fb_पढ़ो,
	.ग_लिखो =	fb_ग_लिखो,
	.unlocked_ioctl = fb_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = fb_compat_ioctl,
#पूर्ण_अगर
	.mmap =		fb_mmap,
	.खोलो =		fb_खोलो,
	.release =	fb_release,
#अगर defined(HAVE_ARCH_FB_UNMAPPED_AREA) || \
	(defined(CONFIG_FB_PROVIDE_GET_FB_UNMAPPED_AREA) && \
	 !defined(CONFIG_MMU))
	.get_unmapped_area = get_fb_unmapped_area,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_DEFERRED_IO
	.fsync =	fb_deferred_io_fsync,
#पूर्ण_अगर
	.llseek =	शेष_llseek,
पूर्ण;

काष्ठा class *fb_class;
EXPORT_SYMBOL(fb_class);

अटल पूर्णांक fb_check_क्रमeignness(काष्ठा fb_info *fi)
अणु
	स्थिर bool क्रमeign_endian = fi->flags & FBINFO_FOREIGN_ENDIAN;

	fi->flags &= ~FBINFO_FOREIGN_ENDIAN;

#अगर_घोषित __BIG_ENDIAN
	fi->flags |= क्रमeign_endian ? 0 : FBINFO_BE_MATH;
#अन्यथा
	fi->flags |= क्रमeign_endian ? FBINFO_BE_MATH : 0;
#पूर्ण_अगर /* __BIG_ENDIAN */

	अगर (fi->flags & FBINFO_BE_MATH && !fb_be_math(fi)) अणु
		pr_err("%s: enable CONFIG_FB_BIG_ENDIAN to "
		       "support this framebuffer\n", fi->fix.id);
		वापस -ENOSYS;
	पूर्ण अन्यथा अगर (!(fi->flags & FBINFO_BE_MATH) && fb_be_math(fi)) अणु
		pr_err("%s: enable CONFIG_FB_LITTLE_ENDIAN to "
		       "support this framebuffer\n", fi->fix.id);
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool apertures_overlap(काष्ठा aperture *gen, काष्ठा aperture *hw)
अणु
	/* is the generic aperture base the same as the HW one */
	अगर (gen->base == hw->base)
		वापस true;
	/* is the generic aperture base inside the hw base->hw base+size */
	अगर (gen->base > hw->base && gen->base < hw->base + hw->size)
		वापस true;
	वापस false;
पूर्ण

अटल bool fb_करो_apertures_overlap(काष्ठा apertures_काष्ठा *gena,
				    काष्ठा apertures_काष्ठा *hwa)
अणु
	पूर्णांक i, j;
	अगर (!hwa || !gena)
		वापस false;

	क्रम (i = 0; i < hwa->count; ++i) अणु
		काष्ठा aperture *h = &hwa->ranges[i];
		क्रम (j = 0; j < gena->count; ++j) अणु
			काष्ठा aperture *g = &gena->ranges[j];
			prपूर्णांकk(KERN_DEBUG "checking generic (%llx %llx) vs hw (%llx %llx)\n",
				(अचिन्हित दीर्घ दीर्घ)g->base,
				(अचिन्हित दीर्घ दीर्घ)g->size,
				(अचिन्हित दीर्घ दीर्घ)h->base,
				(अचिन्हित दीर्घ दीर्घ)h->size);
			अगर (apertures_overlap(g, h))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम करो_unरेजिस्टर_framebuffer(काष्ठा fb_info *fb_info);

#घोषणा VGA_FB_PHYS 0xA0000
अटल व्योम करो_हटाओ_conflicting_framebuffers(काष्ठा apertures_काष्ठा *a,
					       स्थिर अक्षर *name, bool primary)
अणु
	पूर्णांक i;

	/* check all firmware fbs and kick off अगर the base addr overlaps */
	क्रम_each_रेजिस्टरed_fb(i) अणु
		काष्ठा apertures_काष्ठा *gen_aper;

		अगर (!(रेजिस्टरed_fb[i]->flags & FBINFO_MISC_FIRMWARE))
			जारी;

		gen_aper = रेजिस्टरed_fb[i]->apertures;
		अगर (fb_करो_apertures_overlap(gen_aper, a) ||
			(primary && gen_aper && gen_aper->count &&
			 gen_aper->ranges[0].base == VGA_FB_PHYS)) अणु

			prपूर्णांकk(KERN_INFO "fb%d: switching to %s from %s\n",
			       i, name, रेजिस्टरed_fb[i]->fix.id);
			करो_unरेजिस्टर_framebuffer(रेजिस्टरed_fb[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool lockless_रेजिस्टर_fb;
module_param_named_unsafe(lockless_रेजिस्टर_fb, lockless_रेजिस्टर_fb, bool, 0400);
MODULE_PARM_DESC(lockless_रेजिस्टर_fb,
	"Lockless framebuffer registration for debugging [default=off]");

अटल पूर्णांक करो_रेजिस्टर_framebuffer(काष्ठा fb_info *fb_info)
अणु
	पूर्णांक i, ret;
	काष्ठा fb_videomode mode;

	अगर (fb_check_क्रमeignness(fb_info))
		वापस -ENOSYS;

	करो_हटाओ_conflicting_framebuffers(fb_info->apertures,
					   fb_info->fix.id,
					   fb_is_primary_device(fb_info));

	अगर (num_रेजिस्टरed_fb == FB_MAX)
		वापस -ENXIO;

	num_रेजिस्टरed_fb++;
	क्रम (i = 0 ; i < FB_MAX; i++)
		अगर (!रेजिस्टरed_fb[i])
			अवरोध;
	fb_info->node = i;
	atomic_set(&fb_info->count, 1);
	mutex_init(&fb_info->lock);
	mutex_init(&fb_info->mm_lock);

	fb_info->dev = device_create(fb_class, fb_info->device,
				     MKDEV(FB_MAJOR, i), शून्य, "fb%d", i);
	अगर (IS_ERR(fb_info->dev)) अणु
		/* Not fatal */
		prपूर्णांकk(KERN_WARNING "Unable to create device for framebuffer %d; errno = %ld\n", i, PTR_ERR(fb_info->dev));
		fb_info->dev = शून्य;
	पूर्ण अन्यथा
		fb_init_device(fb_info);

	अगर (fb_info->pixmap.addr == शून्य) अणु
		fb_info->pixmap.addr = kदो_स्मृति(FBPIXMAPSIZE, GFP_KERNEL);
		अगर (fb_info->pixmap.addr) अणु
			fb_info->pixmap.size = FBPIXMAPSIZE;
			fb_info->pixmap.buf_align = 1;
			fb_info->pixmap.scan_align = 1;
			fb_info->pixmap.access_align = 32;
			fb_info->pixmap.flags = FB_PIXMAP_DEFAULT;
		पूर्ण
	पूर्ण
	fb_info->pixmap.offset = 0;

	अगर (!fb_info->pixmap.blit_x)
		fb_info->pixmap.blit_x = ~(u32)0;

	अगर (!fb_info->pixmap.blit_y)
		fb_info->pixmap.blit_y = ~(u32)0;

	अगर (!fb_info->modelist.prev || !fb_info->modelist.next)
		INIT_LIST_HEAD(&fb_info->modelist);

	अगर (fb_info->skip_vt_चयन)
		pm_vt_चयन_required(fb_info->dev, false);
	अन्यथा
		pm_vt_चयन_required(fb_info->dev, true);

	fb_var_to_videomode(&mode, &fb_info->var);
	fb_add_videomode(&mode, &fb_info->modelist);
	रेजिस्टरed_fb[i] = fb_info;

#अगर_घोषित CONFIG_GUMSTIX_AM200EPD
	अणु
		काष्ठा fb_event event;
		event.info = fb_info;
		fb_notअगरier_call_chain(FB_EVENT_FB_REGISTERED, &event);
	पूर्ण
#पूर्ण_अगर

	अगर (!lockless_रेजिस्टर_fb)
		console_lock();
	अन्यथा
		atomic_inc(&ignore_console_lock_warning);
	lock_fb_info(fb_info);
	ret = fbcon_fb_रेजिस्टरed(fb_info);
	unlock_fb_info(fb_info);

	अगर (!lockless_रेजिस्टर_fb)
		console_unlock();
	अन्यथा
		atomic_dec(&ignore_console_lock_warning);
	वापस ret;
पूर्ण

अटल व्योम unbind_console(काष्ठा fb_info *fb_info)
अणु
	पूर्णांक i = fb_info->node;

	अगर (WARN_ON(i < 0 || i >= FB_MAX || रेजिस्टरed_fb[i] != fb_info))
		वापस;

	console_lock();
	lock_fb_info(fb_info);
	fbcon_fb_unbind(fb_info);
	unlock_fb_info(fb_info);
	console_unlock();
पूर्ण

अटल व्योम unlink_framebuffer(काष्ठा fb_info *fb_info)
अणु
	पूर्णांक i;

	i = fb_info->node;
	अगर (WARN_ON(i < 0 || i >= FB_MAX || रेजिस्टरed_fb[i] != fb_info))
		वापस;

	अगर (!fb_info->dev)
		वापस;

	device_destroy(fb_class, MKDEV(FB_MAJOR, i));

	pm_vt_चयन_unरेजिस्टर(fb_info->dev);

	unbind_console(fb_info);

	fb_info->dev = शून्य;
पूर्ण

अटल व्योम करो_unरेजिस्टर_framebuffer(काष्ठा fb_info *fb_info)
अणु
	unlink_framebuffer(fb_info);
	अगर (fb_info->pixmap.addr &&
	    (fb_info->pixmap.flags & FB_PIXMAP_DEFAULT))
		kमुक्त(fb_info->pixmap.addr);
	fb_destroy_modelist(&fb_info->modelist);
	रेजिस्टरed_fb[fb_info->node] = शून्य;
	num_रेजिस्टरed_fb--;
	fb_cleanup_device(fb_info);
#अगर_घोषित CONFIG_GUMSTIX_AM200EPD
	अणु
		काष्ठा fb_event event;
		event.info = fb_info;
		fb_notअगरier_call_chain(FB_EVENT_FB_UNREGISTERED, &event);
	पूर्ण
#पूर्ण_अगर
	console_lock();
	fbcon_fb_unरेजिस्टरed(fb_info);
	console_unlock();

	/* this may मुक्त fb info */
	put_fb_info(fb_info);
पूर्ण

/**
 * हटाओ_conflicting_framebuffers - हटाओ firmware-configured framebuffers
 * @a: memory range, users of which are to be हटाओd
 * @name: requesting driver name
 * @primary: also kick vga16fb अगर present
 *
 * This function हटाओs framebuffer devices (initialized by firmware/bootloader)
 * which use memory range described by @a. If @a is शून्य all such devices are
 * हटाओd.
 */
पूर्णांक हटाओ_conflicting_framebuffers(काष्ठा apertures_काष्ठा *a,
				    स्थिर अक्षर *name, bool primary)
अणु
	bool करो_मुक्त = false;

	अगर (!a) अणु
		a = alloc_apertures(1);
		अगर (!a)
			वापस -ENOMEM;

		a->ranges[0].base = 0;
		a->ranges[0].size = ~0;
		करो_मुक्त = true;
	पूर्ण

	mutex_lock(&registration_lock);
	करो_हटाओ_conflicting_framebuffers(a, name, primary);
	mutex_unlock(&registration_lock);

	अगर (करो_मुक्त)
		kमुक्त(a);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(हटाओ_conflicting_framebuffers);

/**
 * हटाओ_conflicting_pci_framebuffers - हटाओ firmware-configured framebuffers क्रम PCI devices
 * @pdev: PCI device
 * @name: requesting driver name
 *
 * This function हटाओs framebuffer devices (eg. initialized by firmware)
 * using memory range configured क्रम any of @pdev's memory bars.
 *
 * The function assumes that PCI device with shaकरोwed ROM drives a primary
 * display and so kicks out vga16fb.
 */
पूर्णांक हटाओ_conflicting_pci_framebuffers(काष्ठा pci_dev *pdev, स्थिर अक्षर *name)
अणु
	काष्ठा apertures_काष्ठा *ap;
	bool primary = false;
	पूर्णांक err, idx, bar;

	क्रम (idx = 0, bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		अगर (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM))
			जारी;
		idx++;
	पूर्ण

	ap = alloc_apertures(idx);
	अगर (!ap)
		वापस -ENOMEM;

	क्रम (idx = 0, bar = 0; bar < PCI_STD_NUM_BARS; bar++) अणु
		अगर (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM))
			जारी;
		ap->ranges[idx].base = pci_resource_start(pdev, bar);
		ap->ranges[idx].size = pci_resource_len(pdev, bar);
		pci_dbg(pdev, "%s: bar %d: 0x%lx -> 0x%lx\n", __func__, bar,
			(अचिन्हित दीर्घ)pci_resource_start(pdev, bar),
			(अचिन्हित दीर्घ)pci_resource_end(pdev, bar));
		idx++;
	पूर्ण

#अगर_घोषित CONFIG_X86
	primary = pdev->resource[PCI_ROM_RESOURCE].flags &
					IORESOURCE_ROM_SHADOW;
#पूर्ण_अगर
	err = हटाओ_conflicting_framebuffers(ap, name, primary);
	kमुक्त(ap);
	वापस err;
पूर्ण
EXPORT_SYMBOL(हटाओ_conflicting_pci_framebuffers);

/**
 *	रेजिस्टर_framebuffer - रेजिस्टरs a frame buffer device
 *	@fb_info: frame buffer info काष्ठाure
 *
 *	Registers a frame buffer device @fb_info.
 *
 *	Returns negative त्रुटि_सं on error, or zero क्रम success.
 *
 */
पूर्णांक
रेजिस्टर_framebuffer(काष्ठा fb_info *fb_info)
अणु
	पूर्णांक ret;

	mutex_lock(&registration_lock);
	ret = करो_रेजिस्टर_framebuffer(fb_info);
	mutex_unlock(&registration_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_framebuffer);

/**
 *	unरेजिस्टर_framebuffer - releases a frame buffer device
 *	@fb_info: frame buffer info काष्ठाure
 *
 *	Unरेजिस्टरs a frame buffer device @fb_info.
 *
 *	Returns negative त्रुटि_सं on error, or zero क्रम success.
 *
 *      This function will also notअगरy the framebuffer console
 *      to release the driver.
 *
 *      This is meant to be called within a driver's module_निकास()
 *      function. If this is called outside module_निकास(), ensure
 *      that the driver implements fb_खोलो() and fb_release() to
 *      check that no processes are using the device.
 */
व्योम
unरेजिस्टर_framebuffer(काष्ठा fb_info *fb_info)
अणु
	mutex_lock(&registration_lock);
	करो_unरेजिस्टर_framebuffer(fb_info);
	mutex_unlock(&registration_lock);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_framebuffer);

/**
 *	fb_set_suspend - low level driver संकेतs suspend
 *	@info: framebuffer affected
 *	@state: 0 = resuming, !=0 = suspending
 *
 *	This is meant to be used by low level drivers to
 * 	संकेत suspend/resume to the core & clients.
 *	It must be called with the console semaphore held
 */
व्योम fb_set_suspend(काष्ठा fb_info *info, पूर्णांक state)
अणु
	WARN_CONSOLE_UNLOCKED();

	अगर (state) अणु
		fbcon_suspended(info);
		info->state = FBINFO_STATE_SUSPENDED;
	पूर्ण अन्यथा अणु
		info->state = FBINFO_STATE_RUNNING;
		fbcon_resumed(info);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fb_set_suspend);

/**
 *	fbmem_init - init frame buffer subप्रणाली
 *
 *	Initialize the frame buffer subप्रणाली.
 *
 *	NOTE: This function is _only_ to be called by drivers/अक्षर/mem.c.
 *
 */

अटल पूर्णांक __init
fbmem_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!proc_create_seq("fb", 0, शून्य, &proc_fb_seq_ops))
		वापस -ENOMEM;

	ret = रेजिस्टर_chrdev(FB_MAJOR, "fb", &fb_fops);
	अगर (ret) अणु
		prपूर्णांकk("unable to get major %d for fb devs\n", FB_MAJOR);
		जाओ err_chrdev;
	पूर्ण

	fb_class = class_create(THIS_MODULE, "graphics");
	अगर (IS_ERR(fb_class)) अणु
		ret = PTR_ERR(fb_class);
		pr_warn("Unable to create fb class; errno = %d\n", ret);
		fb_class = शून्य;
		जाओ err_class;
	पूर्ण

	fb_console_init();

	वापस 0;

err_class:
	unरेजिस्टर_chrdev(FB_MAJOR, "fb");
err_chrdev:
	हटाओ_proc_entry("fb", शून्य);
	वापस ret;
पूर्ण

#अगर_घोषित MODULE
module_init(fbmem_init);
अटल व्योम __निकास
fbmem_निकास(व्योम)
अणु
	fb_console_निकास();

	हटाओ_proc_entry("fb", शून्य);
	class_destroy(fb_class);
	unरेजिस्टर_chrdev(FB_MAJOR, "fb");
पूर्ण

module_निकास(fbmem_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Framebuffer base");
#अन्यथा
subsys_initcall(fbmem_init);
#पूर्ण_अगर

पूर्णांक fb_new_modelist(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo var = info->var;
	काष्ठा list_head *pos, *n;
	काष्ठा fb_modelist *modelist;
	काष्ठा fb_videomode *m, mode;
	पूर्णांक err;

	list_क्रम_each_safe(pos, n, &info->modelist) अणु
		modelist = list_entry(pos, काष्ठा fb_modelist, list);
		m = &modelist->mode;
		fb_videomode_to_var(&var, m);
		var.activate = FB_ACTIVATE_TEST;
		err = fb_set_var(info, &var);
		fb_var_to_videomode(&mode, &var);
		अगर (err || !fb_mode_is_equal(m, &mode)) अणु
			list_del(pos);
			kमुक्त(pos);
		पूर्ण
	पूर्ण

	अगर (list_empty(&info->modelist))
		वापस 1;

	fbcon_new_modelist(info);

	वापस 0;
पूर्ण

MODULE_LICENSE("GPL");
