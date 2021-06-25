<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 Intel Corporation; author Matt Fleming
 */

#समावेश <linux/console.h>
#समावेश <linux/efi.h>
#समावेश <linux/font.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/screen_info.h>

#समावेश <यंत्र/early_ioremap.h>

अटल स्थिर काष्ठा console *earlycon_console __initdata;
अटल स्थिर काष्ठा font_desc *font;
अटल u32 efi_x, efi_y;
अटल u64 fb_base;
अटल bool fb_wb;
अटल व्योम *efi_fb;

/*
 * EFI earlycon needs to use early_memremap() to map the framebuffer.
 * But early_memremap() is not usable क्रम 'earlycon=efifb keep_bootcon',
 * memremap() should be used instead. memremap() will be available after
 * paging_init() which is earlier than initcall callbacks. Thus adding this
 * early initcall function early_efi_map_fb() to map the whole EFI framebuffer.
 */
अटल पूर्णांक __init efi_earlycon_remap_fb(व्योम)
अणु
	/* bail अगर there is no bootconsole or it has been disabled alपढ़ोy */
	अगर (!earlycon_console || !(earlycon_console->flags & CON_ENABLED))
		वापस 0;

	efi_fb = memremap(fb_base, screen_info.lfb_size,
			  fb_wb ? MEMREMAP_WB : MEMREMAP_WC);

	वापस efi_fb ? 0 : -ENOMEM;
पूर्ण
early_initcall(efi_earlycon_remap_fb);

अटल पूर्णांक __init efi_earlycon_unmap_fb(व्योम)
अणु
	/* unmap the bootconsole fb unless keep_bootcon has left it enabled */
	अगर (efi_fb && !(earlycon_console->flags & CON_ENABLED))
		memunmap(efi_fb);
	वापस 0;
पूर्ण
late_initcall(efi_earlycon_unmap_fb);

अटल __ref व्योम *efi_earlycon_map(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	pgprot_t fb_prot;

	अगर (efi_fb)
		वापस efi_fb + start;

	fb_prot = fb_wb ? PAGE_KERNEL : pgprot_ग_लिखोcombine(PAGE_KERNEL);
	वापस early_memremap_prot(fb_base + start, len, pgprot_val(fb_prot));
पूर्ण

अटल __ref व्योम efi_earlycon_unmap(व्योम *addr, अचिन्हित दीर्घ len)
अणु
	अगर (efi_fb)
		वापस;

	early_memunmap(addr, len);
पूर्ण

अटल व्योम efi_earlycon_clear_scanline(अचिन्हित पूर्णांक y)
अणु
	अचिन्हित दीर्घ *dst;
	u16 len;

	len = screen_info.lfb_linelength;
	dst = efi_earlycon_map(y*len, len);
	अगर (!dst)
		वापस;

	स_रखो(dst, 0, len);
	efi_earlycon_unmap(dst, len);
पूर्ण

अटल व्योम efi_earlycon_scroll_up(व्योम)
अणु
	अचिन्हित दीर्घ *dst, *src;
	u16 len;
	u32 i, height;

	len = screen_info.lfb_linelength;
	height = screen_info.lfb_height;

	क्रम (i = 0; i < height - font->height; i++) अणु
		dst = efi_earlycon_map(i*len, len);
		अगर (!dst)
			वापस;

		src = efi_earlycon_map((i + font->height) * len, len);
		अगर (!src) अणु
			efi_earlycon_unmap(dst, len);
			वापस;
		पूर्ण

		स_हटाओ(dst, src, len);

		efi_earlycon_unmap(src, len);
		efi_earlycon_unmap(dst, len);
	पूर्ण
पूर्ण

अटल व्योम efi_earlycon_ग_लिखो_अक्षर(u32 *dst, अचिन्हित अक्षर c, अचिन्हित पूर्णांक h)
अणु
	स्थिर u32 color_black = 0x00000000;
	स्थिर u32 color_white = 0x00ffffff;
	स्थिर u8 *src;
	पूर्णांक m, n, bytes;
	u8 x;

	bytes = BITS_TO_BYTES(font->width);
	src = font->data + c * font->height * bytes + h * bytes;

	क्रम (m = 0; m < font->width; m++) अणु
		n = m % 8;
		x = *(src + m / 8);
		अगर ((x >> (7 - n)) & 1)
			*dst = color_white;
		अन्यथा
			*dst = color_black;
		dst++;
	पूर्ण
पूर्ण

अटल व्योम
efi_earlycon_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *str, अचिन्हित पूर्णांक num)
अणु
	काष्ठा screen_info *si;
	अचिन्हित पूर्णांक len;
	स्थिर अक्षर *s;
	व्योम *dst;

	si = &screen_info;
	len = si->lfb_linelength;

	जबतक (num) अणु
		अचिन्हित पूर्णांक linemax;
		अचिन्हित पूर्णांक h, count = 0;

		क्रम (s = str; *s && *s != '\n'; s++) अणु
			अगर (count == num)
				अवरोध;
			count++;
		पूर्ण

		linemax = (si->lfb_width - efi_x) / font->width;
		अगर (count > linemax)
			count = linemax;

		क्रम (h = 0; h < font->height; h++) अणु
			अचिन्हित पूर्णांक n, x;

			dst = efi_earlycon_map((efi_y + h) * len, len);
			अगर (!dst)
				वापस;

			s = str;
			n = count;
			x = efi_x;

			जबतक (n-- > 0) अणु
				efi_earlycon_ग_लिखो_अक्षर(dst + x*4, *s, h);
				x += font->width;
				s++;
			पूर्ण

			efi_earlycon_unmap(dst, len);
		पूर्ण

		num -= count;
		efi_x += count * font->width;
		str += count;

		अगर (num > 0 && *s == '\n') अणु
			efi_x = 0;
			efi_y += font->height;
			str++;
			num--;
		पूर्ण

		अगर (efi_x + font->width > si->lfb_width) अणु
			efi_x = 0;
			efi_y += font->height;
		पूर्ण

		अगर (efi_y + font->height > si->lfb_height) अणु
			u32 i;

			efi_y -= font->height;
			efi_earlycon_scroll_up();

			क्रम (i = 0; i < font->height; i++)
				efi_earlycon_clear_scanline(efi_y + i);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init efi_earlycon_setup(काष्ठा earlycon_device *device,
				     स्थिर अक्षर *opt)
अणु
	काष्ठा screen_info *si;
	u16 xres, yres;
	u32 i;

	अगर (screen_info.orig_video_isVGA != VIDEO_TYPE_EFI)
		वापस -ENODEV;

	fb_base = screen_info.lfb_base;
	अगर (screen_info.capabilities & VIDEO_CAPABILITY_64BIT_BASE)
		fb_base |= (u64)screen_info.ext_lfb_base << 32;

	fb_wb = opt && !म_भेद(opt, "ram");

	si = &screen_info;
	xres = si->lfb_width;
	yres = si->lfb_height;

	/*
	 * efi_earlycon_ग_लिखो_अक्षर() implicitly assumes a framebuffer with
	 * 32 bits per pixel.
	 */
	अगर (si->lfb_depth != 32)
		वापस -ENODEV;

	font = get_शेष_font(xres, yres, -1, -1);
	अगर (!font)
		वापस -ENODEV;

	efi_y = roundकरोwn(yres, font->height) - font->height;
	क्रम (i = 0; i < (yres - efi_y) / font->height; i++)
		efi_earlycon_scroll_up();

	device->con->ग_लिखो = efi_earlycon_ग_लिखो;
	earlycon_console = device->con;
	वापस 0;
पूर्ण
EARLYCON_DECLARE(efअगरb, efi_earlycon_setup);
