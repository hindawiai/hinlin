<शैली गुरु>
/*
 *  linux/drivers/video/console/fbcon_rotate.h -- Software Display Rotation
 *
 *	Copyright (C) 2005 Antonino Daplas <adaplas@pol.net>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अगर_अघोषित _FBCON_ROTATE_H
#घोषणा _FBCON_ROTATE_H

#घोषणा GETVYRES(s,i) (अणु                           \
        (s == SCROLL_REDRAW || s == SCROLL_MOVE) ? \
        (i)->var.yres : (i)->var.yres_भव; पूर्ण)

#घोषणा GETVXRES(s,i) (अणु                           \
        (s == SCROLL_REDRAW || s == SCROLL_MOVE || !(i)->fix.xpanstep) ? \
        (i)->var.xres : (i)->var.xres_भव; पूर्ण)


अटल अंतरभूत पूर्णांक pattern_test_bit(u32 x, u32 y, u32 pitch, स्थिर अक्षर *pat)
अणु
	u32 पंचांगp = (y * pitch) + x, index = पंचांगp / 8,  bit = पंचांगp % 8;

	pat +=index;
	वापस (*pat) & (0x80 >> bit);
पूर्ण

अटल अंतरभूत व्योम pattern_set_bit(u32 x, u32 y, u32 pitch, अक्षर *pat)
अणु
	u32 पंचांगp = (y * pitch) + x, index = पंचांगp / 8, bit = पंचांगp % 8;

	pat += index;

	(*pat) |= 0x80 >> bit;
पूर्ण

अटल अंतरभूत व्योम rotate_ud(स्थिर अक्षर *in, अक्षर *out, u32 width, u32 height)
अणु
	पूर्णांक i, j;
	पूर्णांक shअगरt = (8 - (width % 8)) & 7;

	width = (width + 7) & ~7;

	क्रम (i = 0; i < height; i++) अणु
		क्रम (j = 0; j < width - shअगरt; j++) अणु
			अगर (pattern_test_bit(j, i, width, in))
				pattern_set_bit(width - (1 + j + shअगरt),
						height - (1 + i),
						width, out);
		पूर्ण

	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rotate_cw(स्थिर अक्षर *in, अक्षर *out, u32 width, u32 height)
अणु
	पूर्णांक i, j, h = height, w = width;
	पूर्णांक shअगरt = (8 - (height % 8)) & 7;

	width = (width + 7) & ~7;
	height = (height + 7) & ~7;

	क्रम (i = 0; i < h; i++) अणु
		क्रम (j = 0; j < w; j++) अणु
			अगर (pattern_test_bit(j, i, width, in))
				pattern_set_bit(height - 1 - i - shअगरt, j,
						height, out);

		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम rotate_ccw(स्थिर अक्षर *in, अक्षर *out, u32 width, u32 height)
अणु
	पूर्णांक i, j, h = height, w = width;
	पूर्णांक shअगरt = (8 - (width % 8)) & 7;

	width = (width + 7) & ~7;
	height = (height + 7) & ~7;

	क्रम (i = 0; i < h; i++) अणु
		क्रम (j = 0; j < w; j++) अणु
			अगर (pattern_test_bit(j, i, width, in))
				pattern_set_bit(i, width - 1 - j - shअगरt,
						height, out);
		पूर्ण
	पूर्ण
पूर्ण

बाह्य व्योम fbcon_rotate_cw(काष्ठा fbcon_ops *ops);
बाह्य व्योम fbcon_rotate_ud(काष्ठा fbcon_ops *ops);
बाह्य व्योम fbcon_rotate_ccw(काष्ठा fbcon_ops *ops);
#पूर्ण_अगर
