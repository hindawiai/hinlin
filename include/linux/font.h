<शैली गुरु>
/*
 *  font.h -- `Soft' font definitions
 *
 *  Created 1995 by Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अगर_अघोषित _VIDEO_FONT_H
#घोषणा _VIDEO_FONT_H

#समावेश <linux/types.h>

काष्ठा font_desc अणु
    पूर्णांक idx;
    स्थिर अक्षर *name;
    अचिन्हित पूर्णांक width, height;
    अचिन्हित पूर्णांक अक्षरcount;
    स्थिर व्योम *data;
    पूर्णांक pref;
पूर्ण;

#घोषणा VGA8x8_IDX	0
#घोषणा VGA8x16_IDX	1
#घोषणा PEARL8x8_IDX	2
#घोषणा VGA6x11_IDX	3
#घोषणा FONT7x14_IDX	4
#घोषणा	FONT10x18_IDX	5
#घोषणा SUN8x16_IDX	6
#घोषणा SUN12x22_IDX	7
#घोषणा ACORN8x8_IDX	8
#घोषणा	MINI4x6_IDX	9
#घोषणा FONT6x10_IDX	10
#घोषणा TER16x32_IDX	11
#घोषणा FONT6x8_IDX	12

बाह्य स्थिर काष्ठा font_desc	font_vga_8x8,
			font_vga_8x16,
			font_pearl_8x8,
			font_vga_6x11,
			font_7x14,
			font_10x18,
			font_sun_8x16,
			font_sun_12x22,
			font_acorn_8x8,
			font_mini_4x6,
			font_6x10,
			font_ter_16x32,
			font_6x8;

/* Find a font with a specअगरic name */

बाह्य स्थिर काष्ठा font_desc *find_font(स्थिर अक्षर *name);

/* Get the शेष font क्रम a specअगरic screen size */

बाह्य स्थिर काष्ठा font_desc *get_शेष_font(पूर्णांक xres, पूर्णांक yres,
						u32 font_w, u32 font_h);

/* Max. length क्रम the name of a predefined font */
#घोषणा MAX_FONT_NAME	32

/* Extra word getters */
#घोषणा REFCOUNT(fd)	(((पूर्णांक *)(fd))[-1])
#घोषणा FNTSIZE(fd)	(((पूर्णांक *)(fd))[-2])
#घोषणा FNTCHARCNT(fd)	(((पूर्णांक *)(fd))[-3])
#घोषणा FNTSUM(fd)	(((पूर्णांक *)(fd))[-4])

#घोषणा FONT_EXTRA_WORDS 4

काष्ठा font_data अणु
	अचिन्हित पूर्णांक extra[FONT_EXTRA_WORDS];
	स्थिर अचिन्हित अक्षर data[];
पूर्ण __packed;

#पूर्ण_अगर /* _VIDEO_FONT_H */
