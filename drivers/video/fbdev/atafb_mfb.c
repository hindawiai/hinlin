<शैली गुरु>
/*
 *  linux/drivers/video/mfb.c -- Low level frame buffer operations क्रम
 *				 monochrome
 *
 *	Created 5 Apr 1997 by Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/माला.स>
#समावेश <linux/fb.h>

#समावेश "atafb.h"
#समावेश "atafb_utils.h"


    /*
     *  Monochrome
     */

व्योम atafb_mfb_copyarea(काष्ठा fb_info *info, u_दीर्घ next_line,
			पूर्णांक sy, पूर्णांक sx, पूर्णांक dy, पूर्णांक dx,
			पूर्णांक height, पूर्णांक width)
अणु
	u8 *src, *dest;
	u_पूर्णांक rows;

	अगर (sx == 0 && dx == 0 && width == next_line) अणु
		src = (u8 *)info->screen_base + sy * (width >> 3);
		dest = (u8 *)info->screen_base + dy * (width >> 3);
		fb_स_हटाओ(dest, src, height * (width >> 3));
	पूर्ण अन्यथा अगर (dy <= sy) अणु
		src = (u8 *)info->screen_base + sy * next_line + (sx >> 3);
		dest = (u8 *)info->screen_base + dy * next_line + (dx >> 3);
		क्रम (rows = height; rows--;) अणु
			fb_स_हटाओ(dest, src, width >> 3);
			src += next_line;
			dest += next_line;
		पूर्ण
	पूर्ण अन्यथा अणु
		src = (u8 *)info->screen_base + (sy + height - 1) * next_line + (sx >> 3);
		dest = (u8 *)info->screen_base + (dy + height - 1) * next_line + (dx >> 3);
		क्रम (rows = height; rows--;) अणु
			fb_स_हटाओ(dest, src, width >> 3);
			src -= next_line;
			dest -= next_line;
		पूर्ण
	पूर्ण
पूर्ण

व्योम atafb_mfb_fillrect(काष्ठा fb_info *info, u_दीर्घ next_line, u32 color,
			पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width)
अणु
	u8 *dest;
	u_पूर्णांक rows;

	dest = (u8 *)info->screen_base + sy * next_line + (sx >> 3);

	अगर (sx == 0 && width == next_line) अणु
		अगर (color)
			fb_स_रखो255(dest, height * (width >> 3));
		अन्यथा
			fb_memclear(dest, height * (width >> 3));
	पूर्ण अन्यथा अणु
		क्रम (rows = height; rows--; dest += next_line) अणु
			अगर (color)
				fb_स_रखो255(dest, width >> 3);
			अन्यथा
				fb_memclear_small(dest, width >> 3);
		पूर्ण
	पूर्ण
पूर्ण

व्योम atafb_mfb_linefill(काष्ठा fb_info *info, u_दीर्घ next_line,
			पूर्णांक dy, पूर्णांक dx, u32 width,
			स्थिर u8 *data, u32 bgcolor, u32 fgcolor)
अणु
	u8 *dest;
	u_पूर्णांक rows;

	dest = (u8 *)info->screen_base + dy * next_line + (dx >> 3);

	क्रम (rows = width / 8; rows--; /* check margins */ ) अणु
		// use fast_स_हटाओ or fb_स_हटाओ
		*dest++ = *data++;
	पूर्ण
पूर्ण
