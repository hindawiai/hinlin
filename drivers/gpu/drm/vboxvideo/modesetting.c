<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/* Copyright (C) 2006-2017 Oracle Corporation */

#समावेश <linux/vbox_err.h>
#समावेश "vbox_drv.h"
#समावेश "vboxvideo_guest.h"
#समावेश "vboxvideo_vbe.h"
#समावेश "hgsmi_channels.h"

/**
 * Set a video mode via an HGSMI request.  The views must have been
 * initialised first using @a VBoxHGSMISendViewInfo and अगर the mode is being
 * set on the first display then it must be set first using रेजिस्टरs.
 * @ctx:           The context containing the heap to use.
 * @display:       The screen number.
 * @origin_x:      The horizontal displacement relative to the first scrn.
 * @origin_y:      The vertical displacement relative to the first screen.
 * @start_offset:  The offset of the visible area of the framebuffer
 *                 relative to the framebuffer start.
 * @pitch:         The offset in bytes between the starts of two adjecent
 *                 scan lines in video RAM.
 * @width:         The mode width.
 * @height:        The mode height.
 * @bpp:           The colour depth of the mode.
 * @flags:         Flags.
 */
व्योम hgsmi_process_display_info(काष्ठा gen_pool *ctx, u32 display,
				s32 origin_x, s32 origin_y, u32 start_offset,
				u32 pitch, u32 width, u32 height,
				u16 bpp, u16 flags)
अणु
	काष्ठा vbva_infoscreen *p;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_VBVA,
			       VBVA_INFO_SCREEN);
	अगर (!p)
		वापस;

	p->view_index = display;
	p->origin_x = origin_x;
	p->origin_y = origin_y;
	p->start_offset = start_offset;
	p->line_size = pitch;
	p->width = width;
	p->height = height;
	p->bits_per_pixel = bpp;
	p->flags = flags;

	hgsmi_buffer_submit(ctx, p);
	hgsmi_buffer_मुक्त(ctx, p);
पूर्ण

/**
 * Report the rectangle relative to which असलolute poपूर्णांकer events should be
 * expressed.  This inक्रमmation reमुख्यs valid until the next VBVA resize event
 * क्रम any screen, at which समय it is reset to the bounding rectangle of all
 * भव screens.
 * Return: 0 or negative त्रुटि_सं value.
 * @ctx:       The context containing the heap to use.
 * @origin_x:  Upper left X co-ordinate relative to the first screen.
 * @origin_y:  Upper left Y co-ordinate relative to the first screen.
 * @width:     Rectangle width.
 * @height:    Rectangle height.
 */
पूर्णांक hgsmi_update_input_mapping(काष्ठा gen_pool *ctx, s32 origin_x, s32 origin_y,
			       u32 width, u32 height)
अणु
	काष्ठा vbva_report_input_mapping *p;

	p = hgsmi_buffer_alloc(ctx, माप(*p), HGSMI_CH_VBVA,
			       VBVA_REPORT_INPUT_MAPPING);
	अगर (!p)
		वापस -ENOMEM;

	p->x = origin_x;
	p->y = origin_y;
	p->cx = width;
	p->cy = height;

	hgsmi_buffer_submit(ctx, p);
	hgsmi_buffer_मुक्त(ctx, p);

	वापस 0;
पूर्ण

/**
 * Get most recent video mode hपूर्णांकs.
 * Return: 0 or negative त्रुटि_सं value.
 * @ctx:      The context containing the heap to use.
 * @screens:  The number of screens to query hपूर्णांकs क्रम, starting at 0.
 * @hपूर्णांकs:    Array of vbva_modehपूर्णांक काष्ठाures क्रम receiving the hपूर्णांकs.
 */
पूर्णांक hgsmi_get_mode_hपूर्णांकs(काष्ठा gen_pool *ctx, अचिन्हित पूर्णांक screens,
			 काष्ठा vbva_modehपूर्णांक *hपूर्णांकs)
अणु
	काष्ठा vbva_query_mode_hपूर्णांकs *p;
	माप_प्रकार size;

	अगर (WARN_ON(!hपूर्णांकs))
		वापस -EINVAL;

	size = screens * माप(काष्ठा vbva_modehपूर्णांक);
	p = hgsmi_buffer_alloc(ctx, माप(*p) + size, HGSMI_CH_VBVA,
			       VBVA_QUERY_MODE_HINTS);
	अगर (!p)
		वापस -ENOMEM;

	p->hपूर्णांकs_queried_count = screens;
	p->hपूर्णांक_काष्ठाure_guest_size = माप(काष्ठा vbva_modehपूर्णांक);
	p->rc = VERR_NOT_SUPPORTED;

	hgsmi_buffer_submit(ctx, p);

	अगर (p->rc < 0) अणु
		hgsmi_buffer_मुक्त(ctx, p);
		वापस -EIO;
	पूर्ण

	स_नकल(hपूर्णांकs, ((u8 *)p) + माप(काष्ठा vbva_query_mode_hपूर्णांकs), size);
	hgsmi_buffer_मुक्त(ctx, p);

	वापस 0;
पूर्ण
