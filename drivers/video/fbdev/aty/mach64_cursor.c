<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  ATI Mach64 CT/VT/GT/LT Cursor Support
 */

#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश "../core/fb_draw.h"

#समावेश <यंत्र/पन.स>

#अगर_घोषित __sparc__
#समावेश <यंत्र/fbपन.स>
#पूर्ण_अगर

#समावेश <video/mach64.h>
#समावेश "atyfb.h"

/*
 * The hardware cursor definition requires 2 bits per pixel. The
 * Cursor size reguardless of the visible cursor size is 64 pixels
 * by 64 lines. The total memory required to define the cursor is
 * 16 bytes / line क्रम 64 lines or 1024 bytes of data. The data
 * must be in a contigiuos क्रमmat. The 2 bit cursor code values are
 * as follows:
 *
 *	00 - pixel colour = CURSOR_CLR_0
 *	01 - pixel colour = CURSOR_CLR_1
 *	10 - pixel colour = transparent (current display pixel)
 *	11 - pixel colour = 1's complement of current display pixel
 *
 *	Cursor Offset        64 pixels		 Actual Displayed Area
 *            \_________________________/
 *	      |			|	|	|
 *	      |<--------------->|	|	|
 *	      | CURS_HORZ_OFFSET|	|	|
 *	      |			|_______|	|  64 Lines
 *	      |			   ^	|	|
 *	      |			   |	|	|
 *	      |		CURS_VERT_OFFSET|	|
 *	      |			   |	|	|
 *	      |____________________|____|	|
 *
 *
 * The Screen position of the top left corner of the displayed
 * cursor is specअगरiced by CURS_HORZ_VERT_POSN. Care must be taken
 * when the cursor hot spot is not the top left corner and the
 * physical cursor position becomes negative. It will be be displayed
 * अगर either the horizontal or vertical cursor position is negative
 *
 * If x becomes negative the cursor manager must adjust the CURS_HORZ_OFFSET
 * to a larger number and saturate CUR_HORZ_POSN to zero.
 *
 * अगर Y becomes negative, CUR_VERT_OFFSET must be adjusted to a larger number,
 * CUR_OFFSET must be adjusted to a poपूर्णांक to the appropriate line in the cursor
 * definitation and CUR_VERT_POSN must be saturated to zero.
 */

    /*
     *  Hardware Cursor support.
     */
अटल स्थिर u8 cursor_bits_lookup[16] = अणु
	0x00, 0x40, 0x10, 0x50, 0x04, 0x44, 0x14, 0x54,
	0x01, 0x41, 0x11, 0x51, 0x05, 0x45, 0x15, 0x55
पूर्ण;

अटल पूर्णांक atyfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u16 xoff, yoff;
	पूर्णांक x, y, h;

#अगर_घोषित __sparc__
	अगर (par->mmaped)
		वापस -EPERM;
#पूर्ण_अगर
	अगर (par->asleep)
		वापस -EPERM;

	रुको_क्रम_fअगरo(1, par);
	अगर (cursor->enable)
		aty_st_le32(GEN_TEST_CNTL, aty_ld_le32(GEN_TEST_CNTL, par)
			    | HWCURSOR_ENABLE, par);
	अन्यथा
		aty_st_le32(GEN_TEST_CNTL, aty_ld_le32(GEN_TEST_CNTL, par)
				& ~HWCURSOR_ENABLE, par);

	/* set position */
	अगर (cursor->set & FB_CUR_SETPOS) अणु
		x = cursor->image.dx - cursor->hot.x - info->var.xoffset;
		अगर (x < 0) अणु
			xoff = -x;
			x = 0;
		पूर्ण अन्यथा अणु
			xoff = 0;
		पूर्ण

		y = cursor->image.dy - cursor->hot.y - info->var.yoffset;
		अगर (y < 0) अणु
			yoff = -y;
			y = 0;
		पूर्ण अन्यथा अणु
			yoff = 0;
		पूर्ण

		h = cursor->image.height;

		/*
		 * In द्विगुनscan mode, the cursor location
		 * and heigh also needs to be द्विगुनd.
		 */
                अगर (par->crtc.gen_cntl & CRTC_DBL_SCAN_EN) अणु
			y<<=1;
			h<<=1;
		पूर्ण
		रुको_क्रम_fअगरo(3, par);
		aty_st_le32(CUR_OFFSET, (info->fix.smem_len >> 3) + (yoff << 1), par);
		aty_st_le32(CUR_HORZ_VERT_OFF,
			    ((u32) (64 - h + yoff) << 16) | xoff, par);
		aty_st_le32(CUR_HORZ_VERT_POSN, ((u32) y << 16) | x, par);
	पूर्ण

	/* Set color map */
	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		u32 fg_idx, bg_idx, fg, bg;

		fg_idx = cursor->image.fg_color;
		bg_idx = cursor->image.bg_color;

		fg = ((info->cmap.red[fg_idx] & 0xff) << 24) |
		     ((info->cmap.green[fg_idx] & 0xff) << 16) |
		     ((info->cmap.blue[fg_idx] & 0xff) << 8) | 0xff;

		bg = ((info->cmap.red[bg_idx] & 0xff) << 24) |
		     ((info->cmap.green[bg_idx] & 0xff) << 16) |
		     ((info->cmap.blue[bg_idx] & 0xff) << 8);

		रुको_क्रम_fअगरo(2, par);
		aty_st_le32(CUR_CLR0, bg, par);
		aty_st_le32(CUR_CLR1, fg, par);
	पूर्ण

	अगर (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) अणु
	    u8 *src = (u8 *)cursor->image.data;
	    u8 *msk = (u8 *)cursor->mask;
	    u8 __iomem *dst = (u8 __iomem *)info->sprite.addr;
	    अचिन्हित पूर्णांक width = (cursor->image.width + 7) >> 3;
	    अचिन्हित पूर्णांक height = cursor->image.height;
	    अचिन्हित पूर्णांक align = info->sprite.scan_align;

	    अचिन्हित पूर्णांक i, j, offset;
	    u8 m, b;

	    // Clear cursor image with 1010101010...
	    fb_स_रखो(dst, 0xaa, 1024);

	    offset = align - width*2;

	    क्रम (i = 0; i < height; i++) अणु
		क्रम (j = 0; j < width; j++) अणु
			u16 l = 0xaaaa;
			b = *src++;
			m = *msk++;
			चयन (cursor->rop) अणु
			हाल ROP_XOR:
			    // Upper 4 bits of mask data
			    l = cursor_bits_lookup[(b ^ m) >> 4] |
			    // Lower 4 bits of mask
				    (cursor_bits_lookup[(b ^ m) & 0x0f] << 8);
			    अवरोध;
			हाल ROP_COPY:
			    // Upper 4 bits of mask data
			    l = cursor_bits_lookup[(b & m) >> 4] |
			    // Lower 4 bits of mask
				    (cursor_bits_lookup[(b & m) & 0x0f] << 8);
			    अवरोध;
			पूर्ण
			/*
			 * If cursor size is not a multiple of 8 अक्षरacters
			 * we must pad it with transparent pattern (0xaaaa).
			 */
			अगर ((j + 1) * 8 > cursor->image.width) अणु
				l = comp(l, 0xaaaa,
				    (1 << ((cursor->image.width & 7) * 2)) - 1);
			पूर्ण
			fb_ग_लिखोb(l & 0xff, dst++);
			fb_ग_लिखोb(l >> 8, dst++);
		पूर्ण
		dst += offset;
	    पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक aty_init_cursor(काष्ठा fb_info *info, काष्ठा fb_ops *atyfb_ops)
अणु
	अचिन्हित दीर्घ addr;

	info->fix.smem_len -= PAGE_SIZE;

#अगर_घोषित __sparc__
	addr = (अचिन्हित दीर्घ) info->screen_base - 0x800000 + info->fix.smem_len;
	info->sprite.addr = (u8 *) addr;
#अन्यथा
#अगर_घोषित __BIG_ENDIAN
	addr = info->fix.smem_start - 0x800000 + info->fix.smem_len;
	info->sprite.addr = (u8 *) ioremap(addr, 1024);
#अन्यथा
	addr = (अचिन्हित दीर्घ) info->screen_base + info->fix.smem_len;
	info->sprite.addr = (u8 *) addr;
#पूर्ण_अगर
#पूर्ण_अगर
	अगर (!info->sprite.addr)
		वापस -ENXIO;
	info->sprite.size = PAGE_SIZE;
	info->sprite.scan_align = 16;	/* Scratch pad 64 bytes wide */
	info->sprite.buf_align = 16; 	/* and 64 lines tall. */
	info->sprite.flags = FB_PIXMAP_IO;

	atyfb_ops->fb_cursor = atyfb_cursor;

	वापस 0;
पूर्ण

