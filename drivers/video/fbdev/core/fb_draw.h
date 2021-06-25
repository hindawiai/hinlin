<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FB_DRAW_H
#घोषणा _FB_DRAW_H

#समावेश <यंत्र/types.h>
#समावेश <linux/fb.h>
#समावेश <linux/bug.h>

    /*
     *  Compose two values, using a biपंचांगask as decision value
     *  This is equivalent to (a & mask) | (b & ~mask)
     */

अटल अंतरभूत अचिन्हित दीर्घ
comp(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b, अचिन्हित दीर्घ mask)
अणु
    वापस ((a ^ b) & mask) ^ b;
पूर्ण

    /*
     *  Create a pattern with the given pixel's color
     */

#अगर BITS_PER_LONG == 64
अटल अंतरभूत अचिन्हित दीर्घ
pixel_to_pat( u32 bpp, u32 pixel)
अणु
	चयन (bpp) अणु
	हाल 1:
		वापस 0xfffffffffffffffful*pixel;
	हाल 2:
		वापस 0x5555555555555555ul*pixel;
	हाल 4:
		वापस 0x1111111111111111ul*pixel;
	हाल 8:
		वापस 0x0101010101010101ul*pixel;
	हाल 12:
		वापस 0x1001001001001001ul*pixel;
	हाल 16:
		वापस 0x0001000100010001ul*pixel;
	हाल 24:
		वापस 0x0001000001000001ul*pixel;
	हाल 32:
		वापस 0x0000000100000001ul*pixel;
	शेष:
		WARN(1, "pixel_to_pat(): unsupported pixelformat %d\n", bpp);
		वापस 0;
    पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ
pixel_to_pat( u32 bpp, u32 pixel)
अणु
	चयन (bpp) अणु
	हाल 1:
		वापस 0xfffffffful*pixel;
	हाल 2:
		वापस 0x55555555ul*pixel;
	हाल 4:
		वापस 0x11111111ul*pixel;
	हाल 8:
		वापस 0x01010101ul*pixel;
	हाल 12:
		वापस 0x01001001ul*pixel;
	हाल 16:
		वापस 0x00010001ul*pixel;
	हाल 24:
		वापस 0x01000001ul*pixel;
	हाल 32:
		वापस 0x00000001ul*pixel;
	शेष:
		WARN(1, "pixel_to_pat(): unsupported pixelformat %d\n", bpp);
		वापस 0;
    पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_CFB_REV_PIXELS_IN_BYTE
#अगर BITS_PER_LONG == 64
#घोषणा REV_PIXELS_MASK1 0x5555555555555555ul
#घोषणा REV_PIXELS_MASK2 0x3333333333333333ul
#घोषणा REV_PIXELS_MASK4 0x0f0f0f0f0f0f0f0ful
#अन्यथा
#घोषणा REV_PIXELS_MASK1 0x55555555ul
#घोषणा REV_PIXELS_MASK2 0x33333333ul
#घोषणा REV_PIXELS_MASK4 0x0f0f0f0ful
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ fb_rev_pixels_in_दीर्घ(अचिन्हित दीर्घ val,
						  u32 bswapmask)
अणु
	अगर (bswapmask & 1)
		val = comp(val >> 1, val << 1, REV_PIXELS_MASK1);
	अगर (bswapmask & 2)
		val = comp(val >> 2, val << 2, REV_PIXELS_MASK2);
	अगर (bswapmask & 3)
		val = comp(val >> 4, val << 4, REV_PIXELS_MASK4);
	वापस val;
पूर्ण

अटल अंतरभूत u32 fb_shअगरted_pixels_mask_u32(काष्ठा fb_info *p, u32 index,
					     u32 bswapmask)
अणु
	u32 mask;

	अगर (!bswapmask) अणु
		mask = FB_SHIFT_HIGH(p, ~(u32)0, index);
	पूर्ण अन्यथा अणु
		mask = 0xff << FB_LEFT_POS(p, 8);
		mask = FB_SHIFT_LOW(p, mask, index & (bswapmask)) & mask;
		mask = FB_SHIFT_HIGH(p, mask, index & ~(bswapmask));
#अगर defined(__i386__) || defined(__x86_64__)
		/* Shअगरt argument is limited to 0 - 31 on x86 based CPU's */
		अगर(index + bswapmask < 32)
#पूर्ण_अगर
			mask |= FB_SHIFT_HIGH(p, ~(u32)0,
					(index + bswapmask) & ~(bswapmask));
	पूर्ण
	वापस mask;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fb_shअगरted_pixels_mask_दीर्घ(काष्ठा fb_info *p,
							u32 index,
							u32 bswapmask)
अणु
	अचिन्हित दीर्घ mask;

	अगर (!bswapmask) अणु
		mask = FB_SHIFT_HIGH(p, ~0UL, index);
	पूर्ण अन्यथा अणु
		mask = 0xff << FB_LEFT_POS(p, 8);
		mask = FB_SHIFT_LOW(p, mask, index & (bswapmask)) & mask;
		mask = FB_SHIFT_HIGH(p, mask, index & ~(bswapmask));
#अगर defined(__i386__) || defined(__x86_64__)
		/* Shअगरt argument is limited to 0 - 31 on x86 based CPU's */
		अगर(index + bswapmask < BITS_PER_LONG)
#पूर्ण_अगर
			mask |= FB_SHIFT_HIGH(p, ~0UL,
					(index + bswapmask) & ~(bswapmask));
	पूर्ण
	वापस mask;
पूर्ण


अटल अंतरभूत u32 fb_compute_bswapmask(काष्ठा fb_info *info)
अणु
	u32 bswapmask = 0;
	अचिन्हित bpp = info->var.bits_per_pixel;

	अगर ((bpp < 8) && (info->var.nonstd & FB_NONSTD_REV_PIX_IN_B)) अणु
		/*
		 * Reversed order of pixel layout in bytes
		 * works only क्रम 1, 2 and 4 bpp
		 */
		bswapmask = 7 - bpp + 1;
	पूर्ण
	वापस bswapmask;
पूर्ण

#अन्यथा /* CONFIG_FB_CFB_REV_PIXELS_IN_BYTE */

अटल अंतरभूत अचिन्हित दीर्घ fb_rev_pixels_in_दीर्घ(अचिन्हित दीर्घ val,
						  u32 bswapmask)
अणु
	वापस val;
पूर्ण

#घोषणा fb_shअगरted_pixels_mask_u32(p, i, b) FB_SHIFT_HIGH((p), ~(u32)0, (i))
#घोषणा fb_shअगरted_pixels_mask_दीर्घ(p, i, b) FB_SHIFT_HIGH((p), ~0UL, (i))
#घोषणा fb_compute_bswapmask(...) 0

#पूर्ण_अगर  /* CONFIG_FB_CFB_REV_PIXELS_IN_BYTE */

#घोषणा cpu_to_le_दीर्घ _cpu_to_le_दीर्घ(BITS_PER_LONG)
#घोषणा _cpu_to_le_दीर्घ(x) __cpu_to_le_दीर्घ(x)
#घोषणा __cpu_to_le_दीर्घ(x) cpu_to_le##x

#घोषणा le_दीर्घ_to_cpu _le_दीर्घ_to_cpu(BITS_PER_LONG)
#घोषणा _le_दीर्घ_to_cpu(x) __le_दीर्घ_to_cpu(x)
#घोषणा __le_दीर्घ_to_cpu(x) le##x##_to_cpu

अटल अंतरभूत अचिन्हित दीर्घ rolx(अचिन्हित दीर्घ word, अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक x)
अणु
	वापस (word << shअगरt) | (word >> (x - shअगरt));
पूर्ण

#पूर्ण_अगर /* FB_DRAW_H */
