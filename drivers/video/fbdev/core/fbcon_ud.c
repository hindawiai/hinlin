<शैली गुरु>
/*
 *  linux/drivers/video/console/fbcon_ud.c -- Software Rotation - 180 degrees
 *
 *      Copyright (C) 2005 Antonino Daplas <adaplas @pol.net>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/console.h>
#समावेश <यंत्र/types.h>
#समावेश "fbcon.h"
#समावेश "fbcon_rotate.h"

/*
 * Rotation 180 degrees
 */

अटल व्योम ud_update_attr(u8 *dst, u8 *src, पूर्णांक attribute,
				  काष्ठा vc_data *vc)
अणु
	पूर्णांक i, offset = (vc->vc_font.height < 10) ? 1 : 2;
	पूर्णांक width = (vc->vc_font.width + 7) >> 3;
	अचिन्हित पूर्णांक cellsize = vc->vc_font.height * width;
	u8 c;

	offset = offset * width;

	क्रम (i = 0; i < cellsize; i++) अणु
		c = src[i];
		अगर (attribute & FBCON_ATTRIBUTE_UNDERLINE && i < offset)
			c = 0xff;
		अगर (attribute & FBCON_ATTRIBUTE_BOLD)
			c |= c << 1;
		अगर (attribute & FBCON_ATTRIBUTE_REVERSE)
			c = ~c;
		dst[i] = c;
	पूर्ण
पूर्ण


अटल व्योम ud_bmove(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक sy,
		     पूर्णांक sx, पूर्णांक dy, पूर्णांक dx, पूर्णांक height, पूर्णांक width)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fb_copyarea area;
	u32 vyres = GETVYRES(ops->p->scrollmode, info);
	u32 vxres = GETVXRES(ops->p->scrollmode, info);

	area.sy = vyres - ((sy + height) * vc->vc_font.height);
	area.sx = vxres - ((sx + width) * vc->vc_font.width);
	area.dy = vyres - ((dy + height) * vc->vc_font.height);
	area.dx = vxres - ((dx + width) * vc->vc_font.width);
	area.height = height * vc->vc_font.height;
	area.width  = width * vc->vc_font.width;

	info->fbops->fb_copyarea(info, &area);
पूर्ण

अटल व्योम ud_clear(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक sy,
		     पूर्णांक sx, पूर्णांक height, पूर्णांक width)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	काष्ठा fb_fillrect region;
	पूर्णांक bgshअगरt = (vc->vc_hi_font_mask) ? 13 : 12;
	u32 vyres = GETVYRES(ops->p->scrollmode, info);
	u32 vxres = GETVXRES(ops->p->scrollmode, info);

	region.color = attr_bgcol_ec(bgshअगरt,vc,info);
	region.dy = vyres - ((sy + height) * vc->vc_font.height);
	region.dx = vxres - ((sx + width) *  vc->vc_font.width);
	region.width = width * vc->vc_font.width;
	region.height = height * vc->vc_font.height;
	region.rop = ROP_COPY;

	info->fbops->fb_fillrect(info, &region);
पूर्ण

अटल अंतरभूत व्योम ud_अ_दोs_aligned(काष्ठा vc_data *vc, काष्ठा fb_info *info,
				    स्थिर u16 *s, u32 attr, u32 cnt,
				    u32 d_pitch, u32 s_pitch, u32 cellsize,
				    काष्ठा fb_image *image, u8 *buf, u8 *dst)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	u16 अक्षरmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 idx = vc->vc_font.width >> 3;
	u8 *src;

	जबतक (cnt--) अणु
		src = ops->fontbuffer + (scr_पढ़ोw(s--) & अक्षरmask)*cellsize;

		अगर (attr) अणु
			ud_update_attr(buf, src, attr, vc);
			src = buf;
		पूर्ण

		अगर (likely(idx == 1))
			__fb_pad_aligned_buffer(dst, d_pitch, src, idx,
						image->height);
		अन्यथा
			fb_pad_aligned_buffer(dst, d_pitch, src, idx,
					      image->height);

		dst += s_pitch;
	पूर्ण

	info->fbops->fb_imageblit(info, image);
पूर्ण

अटल अंतरभूत व्योम ud_अ_दोs_unaligned(काष्ठा vc_data *vc,
				      काष्ठा fb_info *info, स्थिर u16 *s,
				      u32 attr, u32 cnt, u32 d_pitch,
				      u32 s_pitch, u32 cellsize,
				      काष्ठा fb_image *image, u8 *buf,
				      u8 *dst)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	u16 अक्षरmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 shअगरt_low = 0, mod = vc->vc_font.width % 8;
	u32 shअगरt_high = 8;
	u32 idx = vc->vc_font.width >> 3;
	u8 *src;

	जबतक (cnt--) अणु
		src = ops->fontbuffer + (scr_पढ़ोw(s--) & अक्षरmask)*cellsize;

		अगर (attr) अणु
			ud_update_attr(buf, src, attr, vc);
			src = buf;
		पूर्ण

		fb_pad_unaligned_buffer(dst, d_pitch, src, idx,
					image->height, shअगरt_high,
					shअगरt_low, mod);
		shअगरt_low += mod;
		dst += (shअगरt_low >= 8) ? s_pitch : s_pitch - 1;
		shअगरt_low &= 7;
		shअगरt_high = 8 - shअगरt_low;
	पूर्ण

	info->fbops->fb_imageblit(info, image);

पूर्ण

अटल व्योम ud_अ_दोs(काष्ठा vc_data *vc, काष्ठा fb_info *info,
		      स्थिर अचिन्हित लघु *s, पूर्णांक count, पूर्णांक yy, पूर्णांक xx,
		      पूर्णांक fg, पूर्णांक bg)
अणु
	काष्ठा fb_image image;
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	u32 width = (vc->vc_font.width + 7)/8;
	u32 cellsize = width * vc->vc_font.height;
	u32 maxcnt = info->pixmap.size/cellsize;
	u32 scan_align = info->pixmap.scan_align - 1;
	u32 buf_align = info->pixmap.buf_align - 1;
	u32 mod = vc->vc_font.width % 8, cnt, pitch, size;
	u32 attribute = get_attribute(info, scr_पढ़ोw(s));
	u8 *dst, *buf = शून्य;
	u32 vyres = GETVYRES(ops->p->scrollmode, info);
	u32 vxres = GETVXRES(ops->p->scrollmode, info);

	अगर (!ops->fontbuffer)
		वापस;

	image.fg_color = fg;
	image.bg_color = bg;
	image.dy = vyres - ((yy * vc->vc_font.height) + vc->vc_font.height);
	image.dx = vxres - ((xx + count) * vc->vc_font.width);
	image.height = vc->vc_font.height;
	image.depth = 1;

	अगर (attribute) अणु
		buf = kदो_स्मृति(cellsize, GFP_KERNEL);
		अगर (!buf)
			वापस;
	पूर्ण

	s += count - 1;

	जबतक (count) अणु
		अगर (count > maxcnt)
			cnt = maxcnt;
		अन्यथा
			cnt = count;

		image.width = vc->vc_font.width * cnt;
		pitch = ((image.width + 7) >> 3) + scan_align;
		pitch &= ~scan_align;
		size = pitch * image.height + buf_align;
		size &= ~buf_align;
		dst = fb_get_buffer_offset(info, &info->pixmap, size);
		image.data = dst;

		अगर (!mod)
			ud_अ_दोs_aligned(vc, info, s, attribute, cnt, pitch,
					 width, cellsize, &image, buf, dst);
		अन्यथा
			ud_अ_दोs_unaligned(vc, info, s, attribute, cnt, pitch,
					   width, cellsize, &image,
					   buf, dst);

		image.dx += image.width;
		count -= cnt;
		s -= cnt;
		xx += cnt;
	पूर्ण

	/* buf is always शून्य except when in monochrome mode, so in this हाल
	   it's a gain to check buf against शून्य even though kमुक्त() handles
	   शून्य poपूर्णांकers just fine */
	अगर (unlikely(buf))
		kमुक्त(buf);

पूर्ण

अटल व्योम ud_clear_margins(काष्ठा vc_data *vc, काष्ठा fb_info *info,
			     पूर्णांक color, पूर्णांक bottom_only)
अणु
	अचिन्हित पूर्णांक cw = vc->vc_font.width;
	अचिन्हित पूर्णांक ch = vc->vc_font.height;
	अचिन्हित पूर्णांक rw = info->var.xres - (vc->vc_cols*cw);
	अचिन्हित पूर्णांक bh = info->var.yres - (vc->vc_rows*ch);
	काष्ठा fb_fillrect region;

	region.color = color;
	region.rop = ROP_COPY;

	अगर ((पूर्णांक) rw > 0 && !bottom_only) अणु
		region.dy = 0;
		region.dx = info->var.xoffset;
		region.width  = rw;
		region.height = info->var.yres_भव;
		info->fbops->fb_fillrect(info, &region);
	पूर्ण

	अगर ((पूर्णांक) bh > 0) अणु
		region.dy = info->var.yoffset;
		region.dx = info->var.xoffset;
                region.height  = bh;
                region.width = info->var.xres;
		info->fbops->fb_fillrect(info, &region);
	पूर्ण
पूर्ण

अटल व्योम ud_cursor(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक mode,
		      पूर्णांक fg, पूर्णांक bg)
अणु
	काष्ठा fb_cursor cursor;
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	अचिन्हित लघु अक्षरmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	पूर्णांक w = (vc->vc_font.width + 7) >> 3, c;
	पूर्णांक y = real_y(ops->p, vc->state.y);
	पूर्णांक attribute, use_sw = vc->vc_cursor_type & CUR_SW;
	पूर्णांक err = 1, dx, dy;
	अक्षर *src;
	u32 vyres = GETVYRES(ops->p->scrollmode, info);
	u32 vxres = GETVXRES(ops->p->scrollmode, info);

	अगर (!ops->fontbuffer)
		वापस;

	cursor.set = 0;

 	c = scr_पढ़ोw((u16 *) vc->vc_pos);
	attribute = get_attribute(info, c);
	src = ops->fontbuffer + ((c & अक्षरmask) * (w * vc->vc_font.height));

	अगर (ops->cursor_state.image.data != src ||
	    ops->cursor_reset) अणु
	    ops->cursor_state.image.data = src;
	    cursor.set |= FB_CUR_SETIMAGE;
	पूर्ण

	अगर (attribute) अणु
		u8 *dst;

		dst = kदो_स्मृति_array(w, vc->vc_font.height, GFP_ATOMIC);
		अगर (!dst)
			वापस;
		kमुक्त(ops->cursor_data);
		ops->cursor_data = dst;
		ud_update_attr(dst, src, attribute, vc);
		src = dst;
	पूर्ण

	अगर (ops->cursor_state.image.fg_color != fg ||
	    ops->cursor_state.image.bg_color != bg ||
	    ops->cursor_reset) अणु
		ops->cursor_state.image.fg_color = fg;
		ops->cursor_state.image.bg_color = bg;
		cursor.set |= FB_CUR_SETCMAP;
	पूर्ण

	अगर (ops->cursor_state.image.height != vc->vc_font.height ||
	    ops->cursor_state.image.width != vc->vc_font.width ||
	    ops->cursor_reset) अणु
		ops->cursor_state.image.height = vc->vc_font.height;
		ops->cursor_state.image.width = vc->vc_font.width;
		cursor.set |= FB_CUR_SETSIZE;
	पूर्ण

	dy = vyres - ((y * vc->vc_font.height) + vc->vc_font.height);
	dx = vxres - ((vc->state.x * vc->vc_font.width) + vc->vc_font.width);

	अगर (ops->cursor_state.image.dx != dx ||
	    ops->cursor_state.image.dy != dy ||
	    ops->cursor_reset) अणु
		ops->cursor_state.image.dx = dx;
		ops->cursor_state.image.dy = dy;
		cursor.set |= FB_CUR_SETPOS;
	पूर्ण

	अगर (ops->cursor_state.hot.x || ops->cursor_state.hot.y ||
	    ops->cursor_reset) अणु
		ops->cursor_state.hot.x = cursor.hot.y = 0;
		cursor.set |= FB_CUR_SETHOT;
	पूर्ण

	अगर (cursor.set & FB_CUR_SETSIZE ||
	    vc->vc_cursor_type != ops->p->cursor_shape ||
	    ops->cursor_state.mask == शून्य ||
	    ops->cursor_reset) अणु
		अक्षर *mask = kदो_स्मृति_array(w, vc->vc_font.height, GFP_ATOMIC);
		पूर्णांक cur_height, size, i = 0;
		u8 msk = 0xff;

		अगर (!mask)
			वापस;

		kमुक्त(ops->cursor_state.mask);
		ops->cursor_state.mask = mask;

		ops->p->cursor_shape = vc->vc_cursor_type;
		cursor.set |= FB_CUR_SETSHAPE;

		चयन (CUR_SIZE(ops->p->cursor_shape)) अणु
		हाल CUR_NONE:
			cur_height = 0;
			अवरोध;
		हाल CUR_UNDERLINE:
			cur_height = (vc->vc_font.height < 10) ? 1 : 2;
			अवरोध;
		हाल CUR_LOWER_THIRD:
			cur_height = vc->vc_font.height/3;
			अवरोध;
		हाल CUR_LOWER_HALF:
			cur_height = vc->vc_font.height >> 1;
			अवरोध;
		हाल CUR_TWO_THIRDS:
			cur_height = (vc->vc_font.height << 1)/3;
			अवरोध;
		हाल CUR_BLOCK:
		शेष:
			cur_height = vc->vc_font.height;
			अवरोध;
		पूर्ण

		size = cur_height * w;

		जबतक (size--)
			mask[i++] = msk;

		size = (vc->vc_font.height - cur_height) * w;

		जबतक (size--)
			mask[i++] = ~msk;
	पूर्ण

	चयन (mode) अणु
	हाल CM_ERASE:
		ops->cursor_state.enable = 0;
		अवरोध;
	हाल CM_DRAW:
	हाल CM_MOVE:
	शेष:
		ops->cursor_state.enable = (use_sw) ? 0 : 1;
		अवरोध;
	पूर्ण

	cursor.image.data = src;
	cursor.image.fg_color = ops->cursor_state.image.fg_color;
	cursor.image.bg_color = ops->cursor_state.image.bg_color;
	cursor.image.dx = ops->cursor_state.image.dx;
	cursor.image.dy = ops->cursor_state.image.dy;
	cursor.image.height = ops->cursor_state.image.height;
	cursor.image.width = ops->cursor_state.image.width;
	cursor.hot.x = ops->cursor_state.hot.x;
	cursor.hot.y = ops->cursor_state.hot.y;
	cursor.mask = ops->cursor_state.mask;
	cursor.enable = ops->cursor_state.enable;
	cursor.image.depth = 1;
	cursor.rop = ROP_XOR;

	अगर (info->fbops->fb_cursor)
		err = info->fbops->fb_cursor(info, &cursor);

	अगर (err)
		soft_cursor(info, &cursor);

	ops->cursor_reset = 0;
पूर्ण

अटल पूर्णांक ud_update_start(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	पूर्णांक xoffset, yoffset;
	u32 vyres = GETVYRES(ops->p->scrollmode, info);
	u32 vxres = GETVXRES(ops->p->scrollmode, info);
	पूर्णांक err;

	xoffset = vxres - info->var.xres - ops->var.xoffset;
	yoffset = vyres - info->var.yres - ops->var.yoffset;
	अगर (yoffset < 0)
		yoffset += vyres;
	ops->var.xoffset = xoffset;
	ops->var.yoffset = yoffset;
	err = fb_pan_display(info, &ops->var);
	ops->var.xoffset = info->var.xoffset;
	ops->var.yoffset = info->var.yoffset;
	ops->var.vmode = info->var.vmode;
	वापस err;
पूर्ण

व्योम fbcon_rotate_ud(काष्ठा fbcon_ops *ops)
अणु
	ops->bmove = ud_bmove;
	ops->clear = ud_clear;
	ops->अ_दोs = ud_अ_दोs;
	ops->clear_margins = ud_clear_margins;
	ops->cursor = ud_cursor;
	ops->update_start = ud_update_start;
पूर्ण
