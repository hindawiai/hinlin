<शैली गुरु>
/*
 *  linux/drivers/video/iplan2p4.c -- Low level frame buffer operations क्रम
 *				      पूर्णांकerleaved bitplanes थ  la Atari (4
 *				      planes, 2 bytes पूर्णांकerleave)
 *
 *	Created 5 Apr 1997 by Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/माला.स>
#समावेश <linux/fb.h>

#समावेश <यंत्र/setup.h>

#समावेश "atafb.h"

#घोषणा BPL	4
#समावेश "atafb_utils.h"

व्योम atafb_iplan2p4_copyarea(काष्ठा fb_info *info, u_दीर्घ next_line,
			     पूर्णांक sy, पूर्णांक sx, पूर्णांक dy, पूर्णांक dx,
			     पूर्णांक height, पूर्णांक width)
अणु
	/*  bmove() has to distinguish two major हालs: If both, source and
	 *  destination, start at even addresses or both are at odd
	 *  addresses, just the first odd and last even column (अगर present)
	 *  require special treaपंचांगent (स_हटाओ_col()). The rest between
	 *  then can be copied by normal operations, because all adjacent
	 *  bytes are affected and are to be stored in the same order.
	 *    The pathological हाल is when the move should go from an odd
	 *  address to an even or vice versa. Since the bytes in the plane
	 *  words must be assembled in new order, it seems wisest to make
	 *  all movements by स_हटाओ_col().
	 */

	u8 *src, *dst;
	u32 *s, *d;
	पूर्णांक w, l , i, j;
	u_पूर्णांक colsize;
	u_पूर्णांक upwards = (dy < sy) || (dy == sy && dx < sx);

	colsize = height;
	अगर (!((sx ^ dx) & 15)) अणु
		/* odd->odd or even->even */

		अगर (upwards) अणु
			src = (u8 *)info->screen_base + sy * next_line + (sx & ~15) / (8 / BPL);
			dst = (u8 *)info->screen_base + dy * next_line + (dx & ~15) / (8 / BPL);
			अगर (sx & 15) अणु
				स_हटाओ32_col(dst, src, 0xff00ff, height, next_line - BPL * 2);
				src += BPL * 2;
				dst += BPL * 2;
				width -= 8;
			पूर्ण
			w = width >> 4;
			अगर (w) अणु
				s = (u32 *)src;
				d = (u32 *)dst;
				w *= BPL / 2;
				l = next_line - w * 4;
				क्रम (j = height; j > 0; j--) अणु
					क्रम (i = w; i > 0; i--)
						*d++ = *s++;
					s = (u32 *)((u8 *)s + l);
					d = (u32 *)((u8 *)d + l);
				पूर्ण
			पूर्ण
			अगर (width & 15)
				स_हटाओ32_col(dst + width / (8 / BPL), src + width / (8 / BPL),
					      0xff00ff00, height, next_line - BPL * 2);
		पूर्ण अन्यथा अणु
			src = (u8 *)info->screen_base + (sy - 1) * next_line + ((sx + width + 8) & ~15) / (8 / BPL);
			dst = (u8 *)info->screen_base + (dy - 1) * next_line + ((dx + width + 8) & ~15) / (8 / BPL);

			अगर ((sx + width) & 15) अणु
				src -= BPL * 2;
				dst -= BPL * 2;
				स_हटाओ32_col(dst, src, 0xff00ff00, colsize, -next_line - BPL * 2);
				width -= 8;
			पूर्ण
			w = width >> 4;
			अगर (w) अणु
				s = (u32 *)src;
				d = (u32 *)dst;
				w *= BPL / 2;
				l = next_line - w * 4;
				क्रम (j = height; j > 0; j--) अणु
					क्रम (i = w; i > 0; i--)
						*--d = *--s;
					s = (u32 *)((u8 *)s - l);
					d = (u32 *)((u8 *)d - l);
				पूर्ण
			पूर्ण
			अगर (sx & 15)
				स_हटाओ32_col(dst - (width - 16) / (8 / BPL),
					      src - (width - 16) / (8 / BPL),
					      0xff00ff, colsize, -next_line - BPL * 2);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* odd->even or even->odd */
		अगर (upwards) अणु
			u32 *src32, *dst32;
			u32 pval[4], v, v1, mask;
			पूर्णांक i, j, w, f;

			src = (u8 *)info->screen_base + sy * next_line + (sx & ~15) / (8 / BPL);
			dst = (u8 *)info->screen_base + dy * next_line + (dx & ~15) / (8 / BPL);

			mask = 0xff00ff00;
			f = 0;
			w = width;
			अगर (sx & 15) अणु
				f = 1;
				w += 8;
			पूर्ण
			अगर ((sx + width) & 15)
				f |= 2;
			w >>= 4;
			क्रम (i = height; i; i--) अणु
				src32 = (u32 *)src;
				dst32 = (u32 *)dst;

				अगर (f & 1) अणु
					pval[0] = (*src32++ << 8) & mask;
					pval[1] = (*src32++ << 8) & mask;
				पूर्ण अन्यथा अणु
					pval[0] = dst32[0] & mask;
					pval[1] = dst32[1] & mask;
				पूर्ण

				क्रम (j = w; j > 0; j--) अणु
					v = *src32++;
					v1 = v & mask;
					*dst32++ = pval[0] | (v1 >> 8);
					pval[0] = (v ^ v1) << 8;
					v = *src32++;
					v1 = v & mask;
					*dst32++ = pval[1] | (v1 >> 8);
					pval[1] = (v ^ v1) << 8;
				पूर्ण

				अगर (f & 2) अणु
					dst32[0] = (dst32[0] & mask) | pval[0];
					dst32[1] = (dst32[1] & mask) | pval[1];
				पूर्ण

				src += next_line;
				dst += next_line;
			पूर्ण
		पूर्ण अन्यथा अणु
			u32 *src32, *dst32;
			u32 pval[4], v, v1, mask;
			पूर्णांक i, j, w, f;

			src = (u8 *)info->screen_base + (sy - 1) * next_line + ((sx + width + 8) & ~15) / (8 / BPL);
			dst = (u8 *)info->screen_base + (dy - 1) * next_line + ((dx + width + 8) & ~15) / (8 / BPL);

			mask = 0xff00ff;
			f = 0;
			w = width;
			अगर ((dx + width) & 15)
				f = 1;
			अगर (sx & 15) अणु
				f |= 2;
				w += 8;
			पूर्ण
			w >>= 4;
			क्रम (i = height; i; i--) अणु
				src32 = (u32 *)src;
				dst32 = (u32 *)dst;

				अगर (f & 1) अणु
					pval[0] = dst32[-1] & mask;
					pval[1] = dst32[-2] & mask;
				पूर्ण अन्यथा अणु
					pval[0] = (*--src32 >> 8) & mask;
					pval[1] = (*--src32 >> 8) & mask;
				पूर्ण

				क्रम (j = w; j > 0; j--) अणु
					v = *--src32;
					v1 = v & mask;
					*--dst32 = pval[0] | (v1 << 8);
					pval[0] = (v ^ v1) >> 8;
					v = *--src32;
					v1 = v & mask;
					*--dst32 = pval[1] | (v1 << 8);
					pval[1] = (v ^ v1) >> 8;
				पूर्ण

				अगर (!(f & 2)) अणु
					dst32[-1] = (dst32[-1] & mask) | pval[0];
					dst32[-2] = (dst32[-2] & mask) | pval[1];
				पूर्ण

				src -= next_line;
				dst -= next_line;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम atafb_iplan2p4_fillrect(काष्ठा fb_info *info, u_दीर्घ next_line, u32 color,
                             पूर्णांक sy, पूर्णांक sx, पूर्णांक height, पूर्णांक width)
अणु
	u32 *dest;
	पूर्णांक rows, i;
	u32 cval[4];

	dest = (u32 *)(info->screen_base + sy * next_line + (sx & ~15) / (8 / BPL));
	अगर (sx & 15) अणु
		u8 *dest8 = (u8 *)dest + 1;

		expand8_col2mask(color, cval);

		क्रम (i = height; i; i--) अणु
			fill8_col(dest8, cval);
			dest8 += next_line;
		पूर्ण
		dest += BPL / 2;
		width -= 8;
	पूर्ण

	expand16_col2mask(color, cval);
	rows = width >> 4;
	अगर (rows) अणु
		u32 *d = dest;
		u32 off = next_line - rows * BPL * 2;
		क्रम (i = height; i; i--) अणु
			d = fill16_col(d, rows, cval);
			d = (u32 *)((दीर्घ)d + off);
		पूर्ण
		dest += rows * BPL / 2;
		width &= 15;
	पूर्ण

	अगर (width) अणु
		u8 *dest8 = (u8 *)dest;

		expand8_col2mask(color, cval);

		क्रम (i = height; i; i--) अणु
			fill8_col(dest8, cval);
			dest8 += next_line;
		पूर्ण
	पूर्ण
पूर्ण

व्योम atafb_iplan2p4_linefill(काष्ठा fb_info *info, u_दीर्घ next_line,
                             पूर्णांक dy, पूर्णांक dx, u32 width,
                             स्थिर u8 *data, u32 bgcolor, u32 fgcolor)
अणु
	u32 *dest;
	स्थिर u16 *data16;
	पूर्णांक rows;
	u32 fgm[4], bgm[4], m;

	dest = (u32 *)(info->screen_base + dy * next_line + (dx & ~15) / (8 / BPL));
	अगर (dx & 15) अणु
		fill8_2col((u8 *)dest + 1, fgcolor, bgcolor, *data++);
		dest += BPL / 2;
		width -= 8;
	पूर्ण

	अगर (width >= 16) अणु
		data16 = (स्थिर u16 *)data;
		expand16_2col2mask(fgcolor, bgcolor, fgm, bgm);

		क्रम (rows = width / 16; rows; rows--) अणु
			u16 d = *data16++;
			m = d | ((u32)d << 16);
			*dest++ = (m & fgm[0]) ^ bgm[0];
			*dest++ = (m & fgm[1]) ^ bgm[1];
		पूर्ण

		data = (स्थिर u8 *)data16;
		width &= 15;
	पूर्ण

	अगर (width)
		fill8_2col((u8 *)dest, fgcolor, bgcolor, *data);
पूर्ण
