<शैली गुरु>
/*
 * `Soft' font definitions
 *
 *    Created 1995 by Geert Uytterhoeven
 *    Rewritten 1998 by Martin Mares <mj@ucw.cz>
 *
 *	2001 - Documented with DocBook
 *	- Brad Douglas <brad@neruo.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#अगर defined(__mc68000__)
#समावेश <यंत्र/setup.h>
#पूर्ण_अगर
#समावेश <linux/font.h>

अटल स्थिर काष्ठा font_desc *fonts[] = अणु
#अगर_घोषित CONFIG_FONT_8x8
	&font_vga_8x8,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_8x16
	&font_vga_8x16,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_6x11
	&font_vga_6x11,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_7x14
	&font_7x14,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_SUN8x16
	&font_sun_8x16,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_SUN12x22
	&font_sun_12x22,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_10x18
	&font_10x18,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_ACORN_8x8
	&font_acorn_8x8,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_PEARL_8x8
	&font_pearl_8x8,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_MINI_4x6
	&font_mini_4x6,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_6x10
	&font_6x10,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_TER16x32
	&font_ter_16x32,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_6x8
	&font_6x8,
#पूर्ण_अगर
पूर्ण;

#घोषणा num_fonts ARRAY_SIZE(fonts)

#अगर_घोषित NO_FONTS
#त्रुटि No fonts configured.
#पूर्ण_अगर


/**
 *	find_font - find a font
 *	@name: string name of a font
 *
 *	Find a specअगरied font with string name @name.
 *
 *	Returns %शून्य अगर no font found, or a poपूर्णांकer to the
 *	specअगरied font.
 *
 */
स्थिर काष्ठा font_desc *find_font(स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(!num_fonts);
	क्रम (i = 0; i < num_fonts; i++)
		अगर (!म_भेद(fonts[i]->name, name))
			वापस fonts[i];
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(find_font);


/**
 *	get_शेष_font - get शेष font
 *	@xres: screen size of X
 *	@yres: screen size of Y
 *      @font_w: bit array of supported widths (1 - 32)
 *      @font_h: bit array of supported heights (1 - 32)
 *
 *	Get the शेष font क्रम a specअगरied screen size.
 *	Dimensions are in pixels.
 *
 *	Returns %शून्य अगर no font is found, or a poपूर्णांकer to the
 *	chosen font.
 *
 */
स्थिर काष्ठा font_desc *get_शेष_font(पूर्णांक xres, पूर्णांक yres, u32 font_w,
					 u32 font_h)
अणु
	पूर्णांक i, c, cc, res;
	स्थिर काष्ठा font_desc *f, *g;

	g = शून्य;
	cc = -10000;
	क्रम (i = 0; i < num_fonts; i++) अणु
		f = fonts[i];
		c = f->pref;
#अगर defined(__mc68000__)
#अगर_घोषित CONFIG_FONT_PEARL_8x8
		अगर (MACH_IS_AMIGA && f->idx == PEARL8x8_IDX)
			c = 100;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FONT_6x11
		अगर (MACH_IS_MAC && xres < 640 && f->idx == VGA6x11_IDX)
			c = 100;
#पूर्ण_अगर
#पूर्ण_अगर
		अगर ((yres < 400) == (f->height <= 8))
			c += 1000;

		/* prefer a bigger font क्रम high resolution */
		res = (xres / f->width) * (yres / f->height) / 1000;
		अगर (res > 20)
			c += 20 - res;

		अगर ((font_w & (1 << (f->width - 1))) &&
		    (font_h & (1 << (f->height - 1))))
			c += 1000;

		अगर (c > cc) अणु
			cc = c;
			g = f;
		पूर्ण
	पूर्ण
	वापस g;
पूर्ण
EXPORT_SYMBOL(get_शेष_font);

MODULE_AUTHOR("James Simmons <jsimmons@users.sf.net>");
MODULE_DESCRIPTION("Console Fonts");
MODULE_LICENSE("GPL");
