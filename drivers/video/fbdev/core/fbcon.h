<शैली गुरु>
/*
 *  linux/drivers/video/console/fbcon.h -- Low level frame buffer based console driver
 *
 *	Copyright (C) 1997 Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अगर_अघोषित _VIDEO_FBCON_H
#घोषणा _VIDEO_FBCON_H

#समावेश <linux/types.h>
#समावेश <linux/vt_buffer.h>
#समावेश <linux/vt_kern.h>

#समावेश <यंत्र/पन.स>

#घोषणा FBCON_FLAGS_INIT         1
#घोषणा FBCON_FLAGS_CURSOR_TIMER 2

   /*
    *    This is the पूर्णांकerface between the low-level console driver and the
    *    low-level frame buffer device
    */

काष्ठा fbcon_display अणु
    /* Filled in by the low-level console driver */
    स्थिर u_अक्षर *fontdata;
    पूर्णांक userfont;                   /* != 0 अगर fontdata kदो_स्मृति()ed */
    u_लघु scrollmode;             /* Scroll Method */
    u_लघु inverse;                /* != 0 text black on white as शेष */
    लघु yscroll;                  /* Hardware scrolling */
    पूर्णांक vrows;                      /* number of भव rows */
    पूर्णांक cursor_shape;
    पूर्णांक con_rotate;
    u32 xres_भव;
    u32 yres_भव;
    u32 height;
    u32 width;
    u32 bits_per_pixel;
    u32 grayscale;
    u32 nonstd;
    u32 accel_flags;
    u32 rotate;
    काष्ठा fb_bitfield red;
    काष्ठा fb_bitfield green;
    काष्ठा fb_bitfield blue;
    काष्ठा fb_bitfield transp;
    स्थिर काष्ठा fb_videomode *mode;
पूर्ण;

काष्ठा fbcon_ops अणु
	व्योम (*bmove)(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक sy,
		      पूर्णांक sx, पूर्णांक dy, पूर्णांक dx, पूर्णांक height, पूर्णांक width);
	व्योम (*clear)(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक sy,
		      पूर्णांक sx, पूर्णांक height, पूर्णांक width);
	व्योम (*अ_दोs)(काष्ठा vc_data *vc, काष्ठा fb_info *info,
		      स्थिर अचिन्हित लघु *s, पूर्णांक count, पूर्णांक yy, पूर्णांक xx,
		      पूर्णांक fg, पूर्णांक bg);
	व्योम (*clear_margins)(काष्ठा vc_data *vc, काष्ठा fb_info *info,
			      पूर्णांक color, पूर्णांक bottom_only);
	व्योम (*cursor)(काष्ठा vc_data *vc, काष्ठा fb_info *info, पूर्णांक mode,
		       पूर्णांक fg, पूर्णांक bg);
	पूर्णांक  (*update_start)(काष्ठा fb_info *info);
	पूर्णांक  (*rotate_font)(काष्ठा fb_info *info, काष्ठा vc_data *vc);
	काष्ठा fb_var_screeninfo var;  /* copy of the current fb_var_screeninfo */
	काष्ठा समयr_list cursor_समयr; /* Cursor समयr */
	काष्ठा fb_cursor cursor_state;
	काष्ठा fbcon_display *p;
	काष्ठा fb_info *info;
        पूर्णांक    currcon;	                /* Current VC. */
	पूर्णांक    cur_blink_jअगरfies;
	पूर्णांक    cursor_flash;
	पूर्णांक    cursor_reset;
	पूर्णांक    blank_state;
	पूर्णांक    graphics;
	पूर्णांक    save_graphics; /* क्रम debug enter/leave */
	पूर्णांक    flags;
	पूर्णांक    rotate;
	पूर्णांक    cur_rotate;
	अक्षर  *cursor_data;
	u8    *fontbuffer;
	u8    *fontdata;
	u8    *cursor_src;
	u32    cursor_size;
	u32    fd_size;
पूर्ण;
    /*
     *  Attribute Decoding
     */

/* Color */
#घोषणा attr_fgcol(fgshअगरt,s)    \
	(((s) >> (fgshअगरt)) & 0x0f)
#घोषणा attr_bgcol(bgshअगरt,s)    \
	(((s) >> (bgshअगरt)) & 0x0f)

/* Monochrome */
#घोषणा attr_bold(s) \
	((s) & 0x200)
#घोषणा attr_reverse(s) \
	((s) & 0x800)
#घोषणा attr_underline(s) \
	((s) & 0x400)
#घोषणा attr_blink(s) \
	((s) & 0x8000)
	

अटल अंतरभूत पूर्णांक mono_col(स्थिर काष्ठा fb_info *info)
अणु
	__u32 max_len;
	max_len = max(info->var.green.length, info->var.red.length);
	max_len = max(info->var.blue.length, max_len);
	वापस (~(0xfff << max_len)) & 0xff;
पूर्ण

अटल अंतरभूत पूर्णांक attr_col_ec(पूर्णांक shअगरt, काष्ठा vc_data *vc,
			      काष्ठा fb_info *info, पूर्णांक is_fg)
अणु
	पूर्णांक is_mono01;
	पूर्णांक col;
	पूर्णांक fg;
	पूर्णांक bg;

	अगर (!vc)
		वापस 0;

	अगर (vc->vc_can_करो_color)
		वापस is_fg ? attr_fgcol(shअगरt,vc->vc_video_erase_अक्षर)
			: attr_bgcol(shअगरt,vc->vc_video_erase_अक्षर);

	अगर (!info)
		वापस 0;

	col = mono_col(info);
	is_mono01 = info->fix.visual == FB_VISUAL_MONO01;

	अगर (attr_reverse(vc->vc_video_erase_अक्षर)) अणु
		fg = is_mono01 ? col : 0;
		bg = is_mono01 ? 0 : col;
	पूर्ण
	अन्यथा अणु
		fg = is_mono01 ? 0 : col;
		bg = is_mono01 ? col : 0;
	पूर्ण

	वापस is_fg ? fg : bg;
पूर्ण

#घोषणा attr_bgcol_ec(bgshअगरt, vc, info) attr_col_ec(bgshअगरt, vc, info, 0)
#घोषणा attr_fgcol_ec(fgshअगरt, vc, info) attr_col_ec(fgshअगरt, vc, info, 1)

    /*
     *  Scroll Method
     */
     
/* There are several methods fbcon can use to move text around the screen:
 *
 *                     Operation   Pan    Wrap
 *---------------------------------------------
 * SCROLL_MOVE         copyarea    No     No
 * SCROLL_PAN_MOVE     copyarea    Yes    No
 * SCROLL_WRAP_MOVE    copyarea    No     Yes
 * SCROLL_REDRAW       imageblit   No     No
 * SCROLL_PAN_REDRAW   imageblit   Yes    No
 * SCROLL_WRAP_REDRAW  imageblit   No     Yes
 *
 * (SCROLL_WRAP_REDRAW is not implemented yet)
 *
 * In general, fbcon will choose the best scrolling
 * method based on the rule below:
 *
 * Pan/Wrap > accel imageblit > accel copyarea >
 * soft imageblit > (soft copyarea)
 *
 * Exception to the rule: Pan + accel copyarea is
 * preferred over Pan + accel imageblit.
 *
 * The above is typical क्रम PCI/AGP cards. Unless
 * overridden, fbcon will never use soft copyarea.
 *
 * If you need to override the above rule, set the
 * appropriate flags in fb_info->flags.  For example,
 * to prefer copyarea over imageblit, set
 * FBINFO_READS_FAST.
 *
 * Other notes:
 * + use the hardware engine to move the text
 *    (hw-accelerated copyarea() and fillrect())
 * + use hardware-supported panning on a large भव screen
 * + amअगरb can not only pan, but also wrap the display by N lines
 *    (i.e. visible line i = physical line (i+N) % yres).
 * + पढ़ो what's alपढ़ोy rendered on the screen and
 *     ग_लिखो it in a dअगरferent place (this is cfb_copyarea())
 * + re-render the text to the screen
 *
 * Whether to use wrapping or panning can only be figured out at
 * runसमय (when we know whether our font height is a multiple
 * of the pan/wrap step)
 *
 */

#घोषणा SCROLL_MOVE	   0x001
#घोषणा SCROLL_PAN_MOVE	   0x002
#घोषणा SCROLL_WRAP_MOVE   0x003
#घोषणा SCROLL_REDRAW	   0x004
#घोषणा SCROLL_PAN_REDRAW  0x005

#अगर_घोषित CONFIG_FB_TILEBLITTING
बाह्य व्योम fbcon_set_tileops(काष्ठा vc_data *vc, काष्ठा fb_info *info);
#पूर्ण_अगर
बाह्य व्योम fbcon_set_bitops(काष्ठा fbcon_ops *ops);
बाह्य पूर्णांक  soft_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor);

#घोषणा FBCON_ATTRIBUTE_UNDERLINE 1
#घोषणा FBCON_ATTRIBUTE_REVERSE   2
#घोषणा FBCON_ATTRIBUTE_BOLD      4

अटल अंतरभूत पूर्णांक real_y(काष्ठा fbcon_display *p, पूर्णांक ypos)
अणु
	पूर्णांक rows = p->vrows;

	ypos += p->yscroll;
	वापस ypos < rows ? ypos : ypos - rows;
पूर्ण


अटल अंतरभूत पूर्णांक get_attribute(काष्ठा fb_info *info, u16 c)
अणु
	पूर्णांक attribute = 0;

	अगर (fb_get_color_depth(&info->var, &info->fix) == 1) अणु
		अगर (attr_underline(c))
			attribute |= FBCON_ATTRIBUTE_UNDERLINE;
		अगर (attr_reverse(c))
			attribute |= FBCON_ATTRIBUTE_REVERSE;
		अगर (attr_bold(c))
			attribute |= FBCON_ATTRIBUTE_BOLD;
	पूर्ण

	वापस attribute;
पूर्ण

#घोषणा FBCON_SWAP(i,r,v) (अणु \
        typeof(r) _r = (r);  \
        typeof(v) _v = (v);  \
        (व्योम) (&_r == &_v); \
        (i == FB_ROTATE_UR || i == FB_ROTATE_UD) ? _r : _v; पूर्ण)

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_ROTATION
बाह्य व्योम fbcon_set_rotate(काष्ठा fbcon_ops *ops);
#अन्यथा
#घोषणा fbcon_set_rotate(x) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर /* CONFIG_FRAMEBUFFER_CONSOLE_ROTATION */

#पूर्ण_अगर /* _VIDEO_FBCON_H */
