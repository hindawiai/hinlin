<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/screen_info.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/setup.h>

#समावेश <xen/पूर्णांकerface/xen.h>

#समावेश "xen-ops.h"

व्योम __init xen_init_vga(स्थिर काष्ठा करोm0_vga_console_info *info, माप_प्रकार size)
अणु
	काष्ठा screen_info *screen_info = &boot_params.screen_info;

	/* This is drawn from a dump from vgacon:startup in
	 * standard Linux. */
	screen_info->orig_video_mode = 3;
	screen_info->orig_video_isVGA = 1;
	screen_info->orig_video_lines = 25;
	screen_info->orig_video_cols = 80;
	screen_info->orig_video_ega_bx = 3;
	screen_info->orig_video_poपूर्णांकs = 16;
	screen_info->orig_y = screen_info->orig_video_lines - 1;

	चयन (info->video_type) अणु
	हाल XEN_VGATYPE_TEXT_MODE_3:
		अगर (size < दुरत्व(काष्ठा करोm0_vga_console_info, u.text_mode_3)
		    + माप(info->u.text_mode_3))
			अवरोध;
		screen_info->orig_video_lines = info->u.text_mode_3.rows;
		screen_info->orig_video_cols = info->u.text_mode_3.columns;
		screen_info->orig_x = info->u.text_mode_3.cursor_x;
		screen_info->orig_y = info->u.text_mode_3.cursor_y;
		screen_info->orig_video_poपूर्णांकs =
			info->u.text_mode_3.font_height;
		अवरोध;

	हाल XEN_VGATYPE_EFI_LFB:
	हाल XEN_VGATYPE_VESA_LFB:
		अगर (size < दुरत्व(काष्ठा करोm0_vga_console_info,
				    u.vesa_lfb.gbl_caps))
			अवरोध;
		screen_info->orig_video_isVGA = VIDEO_TYPE_VLFB;
		screen_info->lfb_width = info->u.vesa_lfb.width;
		screen_info->lfb_height = info->u.vesa_lfb.height;
		screen_info->lfb_depth = info->u.vesa_lfb.bits_per_pixel;
		screen_info->lfb_base = info->u.vesa_lfb.lfb_base;
		screen_info->lfb_size = info->u.vesa_lfb.lfb_size;
		screen_info->lfb_linelength = info->u.vesa_lfb.bytes_per_line;
		screen_info->red_size = info->u.vesa_lfb.red_size;
		screen_info->red_pos = info->u.vesa_lfb.red_pos;
		screen_info->green_size = info->u.vesa_lfb.green_size;
		screen_info->green_pos = info->u.vesa_lfb.green_pos;
		screen_info->blue_size = info->u.vesa_lfb.blue_size;
		screen_info->blue_pos = info->u.vesa_lfb.blue_pos;
		screen_info->rsvd_size = info->u.vesa_lfb.rsvd_size;
		screen_info->rsvd_pos = info->u.vesa_lfb.rsvd_pos;

		अगर (info->video_type == XEN_VGATYPE_EFI_LFB) अणु
			screen_info->orig_video_isVGA = VIDEO_TYPE_EFI;
			अवरोध;
		पूर्ण

		अगर (size >= दुरत्व(काष्ठा करोm0_vga_console_info,
				     u.vesa_lfb.gbl_caps)
		    + माप(info->u.vesa_lfb.gbl_caps))
			screen_info->capabilities = info->u.vesa_lfb.gbl_caps;
		अगर (size >= दुरत्व(काष्ठा करोm0_vga_console_info,
				     u.vesa_lfb.mode_attrs)
		    + माप(info->u.vesa_lfb.mode_attrs))
			screen_info->vesa_attributes = info->u.vesa_lfb.mode_attrs;
		अवरोध;
	पूर्ण
पूर्ण
