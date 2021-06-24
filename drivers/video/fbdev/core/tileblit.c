<शैली गुरु>
/*
 *  linux/drivers/video/console/tileblit.c -- Tile Blitting Operation
 *
 *      Copyright (C) 2004 Antonino Daplas <adaplas @pol.net>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/console.h>
#समावेश <यंत्र/types.h>
#समावेश "fbcon.h"

अटल व्योम tile_bmove(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक sy,
		       पूर्णांक sx, पूर्णांक dy, पूर्णांक dx, पूर्णांक height, पूर्णांक width)
अणु
	काष्ठा fb_tilearea area;

	area.sx = sx;
	area.sy = sy;
	area.dx = dx;
	area.dy = dy;
	area.height = height;
	area.width = width;

	info->tileops->fb_tilecopy(info, &area);
पूर्ण

अटल व्योम tile_clear(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक sy,
		       पूर्णांक sx, पूर्णांक height, पूर्णांक width)
अणु
	काष्ठा fb_tilerect rect;
	पूर्णांक bgshअगरt = (vc->vc_hi_font_mask) ? 13 : 12;
	पूर्णांक fgshअगरt = (vc->vc_hi_font_mask) ? 9 : 8;

	rect.index = vc->vc_video_erase_अक्षर &
		((vc->vc_hi_font_mask) ? 0x1ff : 0xff);
	rect.fg = attr_fgcol_ec(fgshअगरt, vc, info);
	rect.bg = attr_bgcol_ec(bgshअगरt, vc, info);
	rect.sx = sx;
	rect.sy = sy;
	rect.width = width;
	rect.height = height;
	rect.rop = ROP_COPY;

	info->tileops->fb_tilefill(info, &rect);
पूर्ण

अटल व्योम tile_अ_दोs(काष्ठा vc_data *vc, काष्ठा fb_info *info,
		       स्थिर अचिन्हित लघु *s, पूर्णांक count, पूर्णांक yy, पूर्णांक xx,
		       पूर्णांक fg, पूर्णांक bg)
अणु
	काष्ठा fb_tileblit blit;
	अचिन्हित लघु अक्षरmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	पूर्णांक size = माप(u32) * count, i;

	blit.sx = xx;
	blit.sy = yy;
	blit.width = count;
	blit.height = 1;
	blit.fg = fg;
	blit.bg = bg;
	blit.length = count;
	blit.indices = (u32 *) fb_get_buffer_offset(info, &info->pixmap, size);
	क्रम (i = 0; i < count; i++)
		blit.indices[i] = (u32)(scr_पढ़ोw(s++) & अक्षरmask);

	info->tileops->fb_tileblit(info, &blit);
पूर्ण

अटल व्योम tile_clear_margins(काष्ठा vc_data *vc, काष्ठा fb_info *info,
			       पूर्णांक color, पूर्णांक bottom_only)
अणु
	वापस;
पूर्ण

अटल व्योम tile_cursor(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक mode,
			पूर्णांक fg, पूर्णांक bg)
अणु
	काष्ठा fb_tilecursor cursor;
	पूर्णांक use_sw = vc->vc_cursor_type & CUR_SW;

	cursor.sx = vc->state.x;
	cursor.sy = vc->state.y;
	cursor.mode = (mode == CM_ERASE || use_sw) ? 0 : 1;
	cursor.fg = fg;
	cursor.bg = bg;

	चयन (vc->vc_cursor_type & 0x0f) अणु
	हाल CUR_NONE:
		cursor.shape = FB_TILE_CURSOR_NONE;
		अवरोध;
	हाल CUR_UNDERLINE:
		cursor.shape = FB_TILE_CURSOR_UNDERLINE;
		अवरोध;
	हाल CUR_LOWER_THIRD:
		cursor.shape = FB_TILE_CURSOR_LOWER_THIRD;
		अवरोध;
	हाल CUR_LOWER_HALF:
		cursor.shape = FB_TILE_CURSOR_LOWER_HALF;
		अवरोध;
	हाल CUR_TWO_THIRDS:
		cursor.shape = FB_TILE_CURSOR_TWO_THIRDS;
		अवरोध;
	हाल CUR_BLOCK:
	शेष:
		cursor.shape = FB_TILE_CURSOR_BLOCK;
		अवरोध;
	पूर्ण

	info->tileops->fb_tilecursor(info, &cursor);
पूर्ण

अटल पूर्णांक tile_update_start(काष्ठा fb_info *info)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	पूर्णांक err;

	err = fb_pan_display(info, &ops->var);
	ops->var.xoffset = info->var.xoffset;
	ops->var.yoffset = info->var.yoffset;
	ops->var.vmode = info->var.vmode;
	वापस err;
पूर्ण

व्योम fbcon_set_tileops(काष्ठा vc_data *vc, काष्ठा fb_info *info)
अणु
	काष्ठा fb_tilemap map;
	काष्ठा fbcon_ops *ops = info->fbcon_par;

	ops->bmove = tile_bmove;
	ops->clear = tile_clear;
	ops->अ_दोs = tile_अ_दोs;
	ops->clear_margins = tile_clear_margins;
	ops->cursor = tile_cursor;
	ops->update_start = tile_update_start;

	अगर (ops->p) अणु
		map.width = vc->vc_font.width;
		map.height = vc->vc_font.height;
		map.depth = 1;
		map.length = vc->vc_font.अक्षरcount;
		map.data = ops->p->fontdata;
		info->tileops->fb_settile(info, &map);
	पूर्ण
पूर्ण
