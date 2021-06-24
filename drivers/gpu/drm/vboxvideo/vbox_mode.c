<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2013-2017 Oracle Corporation
 * This file is based on ast_mode.c
 * Copyright 2012 Red Hat Inc.
 * Parts based on xf86-video-ast
 * Copyright (c) 2005 ASPEED Technology Inc.
 * Authors: Dave Airlie <airlied@redhat.com>
 *          Michael Thayer <michael.thayer@oracle.com,
 *          Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/export.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "hgsmi_channels.h"
#समावेश "vbox_drv.h"
#समावेश "vboxvideo.h"

/*
 * Set a graphics mode.  Poke any required values पूर्णांकo रेजिस्टरs, करो an HGSMI
 * mode set and tell the host we support advanced graphics functions.
 */
अटल व्योम vbox_करो_modeset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_framebuffer *fb = crtc->primary->state->fb;
	काष्ठा vbox_crtc *vbox_crtc = to_vbox_crtc(crtc);
	काष्ठा vbox_निजी *vbox;
	पूर्णांक width, height, bpp, pitch;
	u16 flags;
	s32 x_offset, y_offset;

	vbox = to_vbox_dev(crtc->dev);
	width = vbox_crtc->width ? vbox_crtc->width : 640;
	height = vbox_crtc->height ? vbox_crtc->height : 480;
	bpp = fb ? fb->क्रमmat->cpp[0] * 8 : 32;
	pitch = fb ? fb->pitches[0] : width * bpp / 8;
	x_offset = vbox->single_framebuffer ? vbox_crtc->x : vbox_crtc->x_hपूर्णांक;
	y_offset = vbox->single_framebuffer ? vbox_crtc->y : vbox_crtc->y_hपूर्णांक;

	/*
	 * This is the old way of setting graphics modes.  It assumed one screen
	 * and a frame-buffer at the start of video RAM.  On older versions of
	 * VirtualBox, certain parts of the code still assume that the first
	 * screen is programmed this way, so try to fake it.
	 */
	अगर (vbox_crtc->crtc_id == 0 && fb &&
	    vbox_crtc->fb_offset / pitch < 0xffff - crtc->y &&
	    vbox_crtc->fb_offset % (bpp / 8) == 0) अणु
		vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_XRES, width);
		vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_YRES, height);
		vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_VIRT_WIDTH, pitch * 8 / bpp);
		vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_BPP, bpp);
		vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED);
		vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_X_OFFSET,
			vbox_crtc->fb_offset % pitch / bpp * 8 + vbox_crtc->x);
		vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_Y_OFFSET,
				  vbox_crtc->fb_offset / pitch + vbox_crtc->y);
	पूर्ण

	flags = VBVA_SCREEN_F_ACTIVE;
	flags |= (fb && crtc->state->enable) ? 0 : VBVA_SCREEN_F_BLANK;
	flags |= vbox_crtc->disconnected ? VBVA_SCREEN_F_DISABLED : 0;
	hgsmi_process_display_info(vbox->guest_pool, vbox_crtc->crtc_id,
				   x_offset, y_offset,
				   vbox_crtc->x * bpp / 8 +
							vbox_crtc->y * pitch,
				   pitch, width, height, bpp, flags);
पूर्ण

अटल पूर्णांक vbox_set_view(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vbox_crtc *vbox_crtc = to_vbox_crtc(crtc);
	काष्ठा vbox_निजी *vbox = to_vbox_dev(crtc->dev);
	काष्ठा vbva_infoview *p;

	/*
	 * Tell the host about the view.  This design originally targeted the
	 * Winकरोws XP driver architecture and assumed that each screen would
	 * have a dedicated frame buffer with the command buffer following it,
	 * the whole being a "view".  The host works out which screen a command
	 * buffer beदीर्घs to by checking whether it is in the first view, then
	 * whether it is in the second and so on.  The first match wins.  We
	 * cheat around this by making the first view be the managed memory
	 * plus the first command buffer, the second the same plus the second
	 * buffer and so on.
	 */
	p = hgsmi_buffer_alloc(vbox->guest_pool, माप(*p),
			       HGSMI_CH_VBVA, VBVA_INFO_VIEW);
	अगर (!p)
		वापस -ENOMEM;

	p->view_index = vbox_crtc->crtc_id;
	p->view_offset = vbox_crtc->fb_offset;
	p->view_size = vbox->available_vram_size - vbox_crtc->fb_offset +
		       vbox_crtc->crtc_id * VBVA_MIN_BUFFER_SIZE;
	p->max_screen_size = vbox->available_vram_size - vbox_crtc->fb_offset;

	hgsmi_buffer_submit(vbox->guest_pool, p);
	hgsmi_buffer_मुक्त(vbox->guest_pool, p);

	वापस 0;
पूर्ण

/*
 * Try to map the layout of भव screens to the range of the input device.
 * Return true अगर we need to re-set the crtc modes due to screen offset
 * changes.
 */
अटल bool vbox_set_up_input_mapping(काष्ठा vbox_निजी *vbox)
अणु
	काष्ठा drm_crtc *crtci;
	काष्ठा drm_connector *connectori;
	काष्ठा drm_framebuffer *fb, *fb1 = शून्य;
	bool single_framebuffer = true;
	bool old_single_framebuffer = vbox->single_framebuffer;
	u16 width = 0, height = 0;

	/*
	 * Are we using an X.Org-style single large frame-buffer क्रम all crtcs?
	 * If so then screen layout can be deduced from the crtc offsets.
	 * Same fall-back अगर this is the fbdev frame-buffer.
	 */
	list_क्रम_each_entry(crtci, &vbox->ddev.mode_config.crtc_list, head) अणु
		fb = crtci->primary->state->fb;
		अगर (!fb)
			जारी;

		अगर (!fb1) अणु
			fb1 = fb;
			अगर (fb1 == vbox->ddev.fb_helper->fb)
				अवरोध;
		पूर्ण अन्यथा अगर (fb != fb1) अणु
			single_framebuffer = false;
		पूर्ण
	पूर्ण
	अगर (!fb1)
		वापस false;

	अगर (single_framebuffer) अणु
		vbox->single_framebuffer = true;
		vbox->input_mapping_width = fb1->width;
		vbox->input_mapping_height = fb1->height;
		वापस old_single_framebuffer != vbox->single_framebuffer;
	पूर्ण
	/* Otherwise calculate the total span of all screens. */
	list_क्रम_each_entry(connectori, &vbox->ddev.mode_config.connector_list,
			    head) अणु
		काष्ठा vbox_connector *vbox_connector =
		    to_vbox_connector(connectori);
		काष्ठा vbox_crtc *vbox_crtc = vbox_connector->vbox_crtc;

		width = max_t(u16, width, vbox_crtc->x_hपूर्णांक +
					  vbox_connector->mode_hपूर्णांक.width);
		height = max_t(u16, height, vbox_crtc->y_hपूर्णांक +
					    vbox_connector->mode_hपूर्णांक.height);
	पूर्ण

	vbox->single_framebuffer = false;
	vbox->input_mapping_width = width;
	vbox->input_mapping_height = height;

	वापस old_single_framebuffer != vbox->single_framebuffer;
पूर्ण

अटल व्योम vbox_crtc_set_base_and_mode(काष्ठा drm_crtc *crtc,
					काष्ठा drm_framebuffer *fb,
					पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा drm_gem_vram_object *gbo = drm_gem_vram_of_gem(fb->obj[0]);
	काष्ठा vbox_निजी *vbox = to_vbox_dev(crtc->dev);
	काष्ठा vbox_crtc *vbox_crtc = to_vbox_crtc(crtc);
	bool needs_modeset = drm_atomic_crtc_needs_modeset(crtc->state);

	mutex_lock(&vbox->hw_mutex);

	अगर (crtc->state->enable) अणु
		vbox_crtc->width = crtc->state->mode.hdisplay;
		vbox_crtc->height = crtc->state->mode.vdisplay;
	पूर्ण

	vbox_crtc->x = x;
	vbox_crtc->y = y;
	vbox_crtc->fb_offset = drm_gem_vram_offset(gbo);

	/* vbox_करो_modeset() checks vbox->single_framebuffer so update it now */
	अगर (needs_modeset && vbox_set_up_input_mapping(vbox)) अणु
		काष्ठा drm_crtc *crtci;

		list_क्रम_each_entry(crtci, &vbox->ddev.mode_config.crtc_list,
				    head) अणु
			अगर (crtci == crtc)
				जारी;
			vbox_करो_modeset(crtci);
		पूर्ण
	पूर्ण

	vbox_set_view(crtc);
	vbox_करो_modeset(crtc);

	अगर (needs_modeset)
		hgsmi_update_input_mapping(vbox->guest_pool, 0, 0,
					   vbox->input_mapping_width,
					   vbox->input_mapping_height);

	mutex_unlock(&vbox->hw_mutex);
पूर्ण

अटल व्योम vbox_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल व्योम vbox_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल व्योम vbox_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs vbox_crtc_helper_funcs = अणु
	.atomic_enable = vbox_crtc_atomic_enable,
	.atomic_disable = vbox_crtc_atomic_disable,
	.atomic_flush = vbox_crtc_atomic_flush,
पूर्ण;

अटल व्योम vbox_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	drm_crtc_cleanup(crtc);
	kमुक्त(crtc);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs vbox_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	/* .gamma_set = vbox_crtc_gamma_set, */
	.destroy = vbox_crtc_destroy,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
पूर्ण;

अटल पूर्णांक vbox_primary_atomic_check(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_crtc_state *crtc_state = शून्य;

	अगर (new_state->crtc) अणु
		crtc_state = drm_atomic_get_existing_crtc_state(state,
								new_state->crtc);
		अगर (WARN_ON(!crtc_state))
			वापस -EINVAL;
	पूर्ण

	वापस drm_atomic_helper_check_plane_state(new_state, crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   false, true);
पूर्ण

अटल व्योम vbox_primary_atomic_update(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_crtc *crtc = new_state->crtc;
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा vbox_निजी *vbox = to_vbox_dev(fb->dev);
	काष्ठा drm_mode_rect *clips;
	uपूर्णांक32_t num_clips, i;

	vbox_crtc_set_base_and_mode(crtc, fb,
				    new_state->src_x >> 16,
				    new_state->src_y >> 16);

	/* Send inक्रमmation about dirty rectangles to VBVA. */

	clips = drm_plane_get_damage_clips(new_state);
	num_clips = drm_plane_get_damage_clips_count(new_state);

	अगर (!num_clips)
		वापस;

	mutex_lock(&vbox->hw_mutex);

	क्रम (i = 0; i < num_clips; ++i, ++clips) अणु
		काष्ठा vbva_cmd_hdr cmd_hdr;
		अचिन्हित पूर्णांक crtc_id = to_vbox_crtc(crtc)->crtc_id;

		cmd_hdr.x = (s16)clips->x1;
		cmd_hdr.y = (s16)clips->y1;
		cmd_hdr.w = (u16)clips->x2 - clips->x1;
		cmd_hdr.h = (u16)clips->y2 - clips->y1;

		अगर (!vbva_buffer_begin_update(&vbox->vbva_info[crtc_id],
					      vbox->guest_pool))
			जारी;

		vbva_ग_लिखो(&vbox->vbva_info[crtc_id], vbox->guest_pool,
			   &cmd_hdr, माप(cmd_hdr));
		vbva_buffer_end_update(&vbox->vbva_info[crtc_id]);
	पूर्ण

	mutex_unlock(&vbox->hw_mutex);
पूर्ण

अटल व्योम vbox_primary_atomic_disable(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_crtc *crtc = old_state->crtc;

	/* vbox_करो_modeset checks plane->state->fb and will disable अगर शून्य */
	vbox_crtc_set_base_and_mode(crtc, old_state->fb,
				    old_state->src_x >> 16,
				    old_state->src_y >> 16);
पूर्ण

अटल पूर्णांक vbox_cursor_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_crtc_state *crtc_state = शून्य;
	u32 width = new_state->crtc_w;
	u32 height = new_state->crtc_h;
	पूर्णांक ret;

	अगर (new_state->crtc) अणु
		crtc_state = drm_atomic_get_existing_crtc_state(state,
								new_state->crtc);
		अगर (WARN_ON(!crtc_state))
			वापस -EINVAL;
	पूर्ण

	ret = drm_atomic_helper_check_plane_state(new_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	अगर (ret)
		वापस ret;

	अगर (!new_state->fb)
		वापस 0;

	अगर (width > VBOX_MAX_CURSOR_WIDTH || height > VBOX_MAX_CURSOR_HEIGHT ||
	    width == 0 || height == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Copy the ARGB image and generate the mask, which is needed in हाल the host
 * करोes not support ARGB cursors.  The mask is a 1BPP biपंचांगap with the bit set
 * अगर the corresponding alpha value in the ARGB image is greater than 0xF0.
 */
अटल व्योम copy_cursor_image(u8 *src, u8 *dst, u32 width, u32 height,
			      माप_प्रकार mask_size)
अणु
	माप_प्रकार line_size = (width + 7) / 8;
	u32 i, j;

	स_नकल(dst + mask_size, src, width * height * 4);
	क्रम (i = 0; i < height; ++i)
		क्रम (j = 0; j < width; ++j)
			अगर (((u32 *)src)[i * width + j] > 0xf0000000)
				dst[i * line_size + j / 8] |= (0x80 >> (j % 8));
पूर्ण

अटल व्योम vbox_cursor_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा vbox_निजी *vbox =
		container_of(plane->dev, काष्ठा vbox_निजी, ddev);
	काष्ठा vbox_crtc *vbox_crtc = to_vbox_crtc(new_state->crtc);
	काष्ठा drm_framebuffer *fb = new_state->fb;
	u32 width = new_state->crtc_w;
	u32 height = new_state->crtc_h;
	काष्ठा drm_shaकरोw_plane_state *shaकरोw_plane_state =
		to_drm_shaकरोw_plane_state(new_state);
	काष्ठा dma_buf_map map = shaकरोw_plane_state->map[0];
	u8 *src = map.vaddr; /* TODO: Use mapping असलtraction properly */
	माप_प्रकार data_size, mask_size;
	u32 flags;

	/*
	 * VirtualBox uses the host winकरोwing प्रणाली to draw the cursor so
	 * moves are a no-op, we only need to upload new cursor sprites.
	 */
	अगर (fb == old_state->fb)
		वापस;

	mutex_lock(&vbox->hw_mutex);

	vbox_crtc->cursor_enabled = true;

	/*
	 * The mask must be calculated based on the alpha
	 * channel, one bit per ARGB word, and must be 32-bit
	 * padded.
	 */
	mask_size = ((width + 7) / 8 * height + 3) & ~3;
	data_size = width * height * 4 + mask_size;

	copy_cursor_image(src, vbox->cursor_data, width, height, mask_size);

	flags = VBOX_MOUSE_POINTER_VISIBLE | VBOX_MOUSE_POINTER_SHAPE |
		VBOX_MOUSE_POINTER_ALPHA;
	hgsmi_update_poपूर्णांकer_shape(vbox->guest_pool, flags,
				   min_t(u32, max(fb->hot_x, 0), width),
				   min_t(u32, max(fb->hot_y, 0), height),
				   width, height, vbox->cursor_data, data_size);

	mutex_unlock(&vbox->hw_mutex);
पूर्ण

अटल व्योम vbox_cursor_atomic_disable(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा vbox_निजी *vbox =
		container_of(plane->dev, काष्ठा vbox_निजी, ddev);
	काष्ठा vbox_crtc *vbox_crtc = to_vbox_crtc(old_state->crtc);
	bool cursor_enabled = false;
	काष्ठा drm_crtc *crtci;

	mutex_lock(&vbox->hw_mutex);

	vbox_crtc->cursor_enabled = false;

	list_क्रम_each_entry(crtci, &vbox->ddev.mode_config.crtc_list, head) अणु
		अगर (to_vbox_crtc(crtci)->cursor_enabled)
			cursor_enabled = true;
	पूर्ण

	अगर (!cursor_enabled)
		hgsmi_update_poपूर्णांकer_shape(vbox->guest_pool, 0, 0, 0,
					   0, 0, शून्य, 0);

	mutex_unlock(&vbox->hw_mutex);
पूर्ण

अटल स्थिर u32 vbox_cursor_plane_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs vbox_cursor_helper_funcs = अणु
	.atomic_check	= vbox_cursor_atomic_check,
	.atomic_update	= vbox_cursor_atomic_update,
	.atomic_disable	= vbox_cursor_atomic_disable,
	DRM_GEM_SHADOW_PLANE_HELPER_FUNCS,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs vbox_cursor_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_primary_helper_destroy,
	DRM_GEM_SHADOW_PLANE_FUNCS,
पूर्ण;

अटल स्थिर u32 vbox_primary_plane_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs vbox_primary_helper_funcs = अणु
	.atomic_check = vbox_primary_atomic_check,
	.atomic_update = vbox_primary_atomic_update,
	.atomic_disable = vbox_primary_atomic_disable,
	.prepare_fb	= drm_gem_vram_plane_helper_prepare_fb,
	.cleanup_fb	= drm_gem_vram_plane_helper_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs vbox_primary_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_primary_helper_destroy,
	.reset		= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल काष्ठा drm_plane *vbox_create_plane(काष्ठा vbox_निजी *vbox,
					   अचिन्हित पूर्णांक possible_crtcs,
					   क्रमागत drm_plane_type type)
अणु
	स्थिर काष्ठा drm_plane_helper_funcs *helper_funcs = शून्य;
	स्थिर काष्ठा drm_plane_funcs *funcs;
	काष्ठा drm_plane *plane;
	स्थिर u32 *क्रमmats;
	पूर्णांक num_क्रमmats;
	पूर्णांक err;

	अगर (type == DRM_PLANE_TYPE_PRIMARY) अणु
		funcs = &vbox_primary_plane_funcs;
		क्रमmats = vbox_primary_plane_क्रमmats;
		helper_funcs = &vbox_primary_helper_funcs;
		num_क्रमmats = ARRAY_SIZE(vbox_primary_plane_क्रमmats);
	पूर्ण अन्यथा अगर (type == DRM_PLANE_TYPE_CURSOR) अणु
		funcs = &vbox_cursor_plane_funcs;
		क्रमmats = vbox_cursor_plane_क्रमmats;
		helper_funcs = &vbox_cursor_helper_funcs;
		num_क्रमmats = ARRAY_SIZE(vbox_cursor_plane_क्रमmats);
	पूर्ण अन्यथा अणु
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	plane = kzalloc(माप(*plane), GFP_KERNEL);
	अगर (!plane)
		वापस ERR_PTR(-ENOMEM);

	err = drm_universal_plane_init(&vbox->ddev, plane, possible_crtcs,
				       funcs, क्रमmats, num_क्रमmats,
				       शून्य, type, शून्य);
	अगर (err)
		जाओ मुक्त_plane;

	drm_plane_helper_add(plane, helper_funcs);

	वापस plane;

मुक्त_plane:
	kमुक्त(plane);
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा vbox_crtc *vbox_crtc_init(काष्ठा drm_device *dev, अचिन्हित पूर्णांक i)
अणु
	काष्ठा vbox_निजी *vbox =
		container_of(dev, काष्ठा vbox_निजी, ddev);
	काष्ठा drm_plane *cursor = शून्य;
	काष्ठा vbox_crtc *vbox_crtc;
	काष्ठा drm_plane *primary;
	u32 caps = 0;
	पूर्णांक ret;

	ret = hgsmi_query_conf(vbox->guest_pool,
			       VBOX_VBVA_CONF32_CURSOR_CAPABILITIES, &caps);
	अगर (ret)
		वापस ERR_PTR(ret);

	vbox_crtc = kzalloc(माप(*vbox_crtc), GFP_KERNEL);
	अगर (!vbox_crtc)
		वापस ERR_PTR(-ENOMEM);

	primary = vbox_create_plane(vbox, 1 << i, DRM_PLANE_TYPE_PRIMARY);
	अगर (IS_ERR(primary)) अणु
		ret = PTR_ERR(primary);
		जाओ मुक्त_mem;
	पूर्ण

	अगर ((caps & VBOX_VBVA_CURSOR_CAPABILITY_HARDWARE)) अणु
		cursor = vbox_create_plane(vbox, 1 << i, DRM_PLANE_TYPE_CURSOR);
		अगर (IS_ERR(cursor)) अणु
			ret = PTR_ERR(cursor);
			जाओ clean_primary;
		पूर्ण
	पूर्ण अन्यथा अणु
		DRM_WARN("VirtualBox host is too old, no cursor support\n");
	पूर्ण

	vbox_crtc->crtc_id = i;

	ret = drm_crtc_init_with_planes(dev, &vbox_crtc->base, primary, cursor,
					&vbox_crtc_funcs, शून्य);
	अगर (ret)
		जाओ clean_cursor;

	drm_mode_crtc_set_gamma_size(&vbox_crtc->base, 256);
	drm_crtc_helper_add(&vbox_crtc->base, &vbox_crtc_helper_funcs);

	वापस vbox_crtc;

clean_cursor:
	अगर (cursor) अणु
		drm_plane_cleanup(cursor);
		kमुक्त(cursor);
	पूर्ण
clean_primary:
	drm_plane_cleanup(primary);
	kमुक्त(primary);
मुक्त_mem:
	kमुक्त(vbox_crtc);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम vbox_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs vbox_enc_funcs = अणु
	.destroy = vbox_encoder_destroy,
पूर्ण;

अटल काष्ठा drm_encoder *vbox_encoder_init(काष्ठा drm_device *dev,
					     अचिन्हित पूर्णांक i)
अणु
	काष्ठा vbox_encoder *vbox_encoder;

	vbox_encoder = kzalloc(माप(*vbox_encoder), GFP_KERNEL);
	अगर (!vbox_encoder)
		वापस शून्य;

	drm_encoder_init(dev, &vbox_encoder->base, &vbox_enc_funcs,
			 DRM_MODE_ENCODER_DAC, शून्य);

	vbox_encoder->base.possible_crtcs = 1 << i;
	वापस &vbox_encoder->base;
पूर्ण

/*
 * Generate EDID data with a mode-unique serial number क्रम the भव
 * monitor to try to persuade Unity that dअगरferent modes correspond to
 * dअगरferent monitors and it should not try to क्रमce the same resolution on
 * them.
 */
अटल व्योम vbox_set_edid(काष्ठा drm_connector *connector, पूर्णांक width,
			  पूर्णांक height)
अणु
	क्रमागत अणु EDID_SIZE = 128 पूर्ण;
	अचिन्हित अक्षर edid[EDID_SIZE] = अणु
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,	/* header */
		0x58, 0x58,	/* manufacturer (VBX) */
		0x00, 0x00,	/* product code */
		0x00, 0x00, 0x00, 0x00,	/* serial number goes here */
		0x01,		/* week of manufacture */
		0x00,		/* year of manufacture */
		0x01, 0x03,	/* EDID version */
		0x80,		/* capabilities - digital */
		0x00,		/* horiz. res in cm, zero क्रम projectors */
		0x00,		/* vert. res in cm */
		0x78,		/* display gamma (120 == 2.2). */
		0xEE,		/* features (standby, suspend, off, RGB, std */
				/* colour space, preferred timing mode) */
		0xEE, 0x91, 0xA3, 0x54, 0x4C, 0x99, 0x26, 0x0F, 0x50, 0x54,
		/* chromaticity क्रम standard colour space. */
		0x00, 0x00, 0x00,	/* no शेष timings */
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		    0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,	/* no standard timings */
		0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x02, 0x02,
		    0x02, 0x02,
		/* descriptor block 1 goes below */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* descriptor block 2, monitor ranges */
		0x00, 0x00, 0x00, 0xFD, 0x00,
		0x00, 0xC8, 0x00, 0xC8, 0x64, 0x00, 0x0A, 0x20, 0x20, 0x20,
		    0x20, 0x20,
		/* 0-200Hz vertical, 0-200KHz horizontal, 1000MHz pixel घड़ी */
		0x20,
		/* descriptor block 3, monitor name */
		0x00, 0x00, 0x00, 0xFC, 0x00,
		'V', 'B', 'O', 'X', ' ', 'm', 'o', 'n', 'i', 't', 'o', 'r',
		'\n',
		/* descriptor block 4: dummy data */
		0x00, 0x00, 0x00, 0x10, 0x00,
		0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20,
		0x00,		/* number of extensions */
		0x00		/* checksum goes here */
	पूर्ण;
	पूर्णांक घड़ी = (width + 6) * (height + 6) * 60 / 10000;
	अचिन्हित पूर्णांक i, sum = 0;

	edid[12] = width & 0xff;
	edid[13] = width >> 8;
	edid[14] = height & 0xff;
	edid[15] = height >> 8;
	edid[54] = घड़ी & 0xff;
	edid[55] = घड़ी >> 8;
	edid[56] = width & 0xff;
	edid[58] = (width >> 4) & 0xf0;
	edid[59] = height & 0xff;
	edid[61] = (height >> 4) & 0xf0;
	क्रम (i = 0; i < EDID_SIZE - 1; ++i)
		sum += edid[i];
	edid[EDID_SIZE - 1] = (0x100 - (sum & 0xFF)) & 0xFF;
	drm_connector_update_edid_property(connector, (काष्ठा edid *)edid);
पूर्ण

अटल पूर्णांक vbox_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा vbox_connector *vbox_connector = शून्य;
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा vbox_निजी *vbox = शून्य;
	अचिन्हित पूर्णांक num_modes = 0;
	पूर्णांक preferred_width, preferred_height;

	vbox_connector = to_vbox_connector(connector);
	vbox = to_vbox_dev(connector->dev);

	hgsmi_report_flags_location(vbox->guest_pool, GUEST_HEAP_OFFSET(vbox) +
				    HOST_FLAGS_OFFSET);
	अगर (vbox_connector->vbox_crtc->crtc_id == 0)
		vbox_report_caps(vbox);

	num_modes = drm_add_modes_noedid(connector, 2560, 1600);
	preferred_width = vbox_connector->mode_hपूर्णांक.width ?
			  vbox_connector->mode_hपूर्णांक.width : 1024;
	preferred_height = vbox_connector->mode_hपूर्णांक.height ?
			   vbox_connector->mode_hपूर्णांक.height : 768;
	mode = drm_cvt_mode(connector->dev, preferred_width, preferred_height,
			    60, false, false, false);
	अगर (mode) अणु
		mode->type |= DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
		++num_modes;
	पूर्ण
	vbox_set_edid(connector, preferred_width, preferred_height);

	अगर (vbox_connector->vbox_crtc->x_hपूर्णांक != -1)
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_x_property,
			vbox_connector->vbox_crtc->x_hपूर्णांक);
	अन्यथा
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_x_property, 0);

	अगर (vbox_connector->vbox_crtc->y_hपूर्णांक != -1)
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_y_property,
			vbox_connector->vbox_crtc->y_hपूर्णांक);
	अन्यथा
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_y_property, 0);

	वापस num_modes;
पूर्ण

अटल व्योम vbox_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल क्रमागत drm_connector_status
vbox_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा vbox_connector *vbox_connector;

	vbox_connector = to_vbox_connector(connector);

	वापस vbox_connector->mode_hपूर्णांक.disconnected ?
	    connector_status_disconnected : connector_status_connected;
पूर्ण

अटल पूर्णांक vbox_fill_modes(काष्ठा drm_connector *connector, u32 max_x,
			   u32 max_y)
अणु
	काष्ठा vbox_connector *vbox_connector;
	काष्ठा drm_device *dev;
	काष्ठा drm_display_mode *mode, *iterator;

	vbox_connector = to_vbox_connector(connector);
	dev = vbox_connector->base.dev;
	list_क्रम_each_entry_safe(mode, iterator, &connector->modes, head) अणु
		list_del(&mode->head);
		drm_mode_destroy(dev, mode);
	पूर्ण

	वापस drm_helper_probe_single_connector_modes(connector, max_x, max_y);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs vbox_connector_helper_funcs = अणु
	.get_modes = vbox_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs vbox_connector_funcs = अणु
	.detect = vbox_connector_detect,
	.fill_modes = vbox_fill_modes,
	.destroy = vbox_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक vbox_connector_init(काष्ठा drm_device *dev,
			       काष्ठा vbox_crtc *vbox_crtc,
			       काष्ठा drm_encoder *encoder)
अणु
	काष्ठा vbox_connector *vbox_connector;
	काष्ठा drm_connector *connector;

	vbox_connector = kzalloc(माप(*vbox_connector), GFP_KERNEL);
	अगर (!vbox_connector)
		वापस -ENOMEM;

	connector = &vbox_connector->base;
	vbox_connector->vbox_crtc = vbox_crtc;

	drm_connector_init(dev, connector, &vbox_connector_funcs,
			   DRM_MODE_CONNECTOR_VGA);
	drm_connector_helper_add(connector, &vbox_connector_helper_funcs);

	connector->पूर्णांकerlace_allowed = 0;
	connector->द्विगुनscan_allowed = 0;

	drm_mode_create_suggested_offset_properties(dev);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_x_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_y_property, 0);

	drm_connector_attach_encoder(connector, encoder);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs vbox_mode_funcs = अणु
	.fb_create = drm_gem_fb_create_with_dirty,
	.mode_valid = drm_vram_helper_mode_valid,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

पूर्णांक vbox_mode_init(काष्ठा vbox_निजी *vbox)
अणु
	काष्ठा drm_device *dev = &vbox->ddev;
	काष्ठा drm_encoder *encoder;
	काष्ठा vbox_crtc *vbox_crtc;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	drm_mode_config_init(dev);

	dev->mode_config.funcs = (व्योम *)&vbox_mode_funcs;
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.preferred_depth = 24;
	dev->mode_config.max_width = VBE_DISPI_MAX_XRES;
	dev->mode_config.max_height = VBE_DISPI_MAX_YRES;

	क्रम (i = 0; i < vbox->num_crtcs; ++i) अणु
		vbox_crtc = vbox_crtc_init(dev, i);
		अगर (IS_ERR(vbox_crtc)) अणु
			ret = PTR_ERR(vbox_crtc);
			जाओ err_drm_mode_cleanup;
		पूर्ण
		encoder = vbox_encoder_init(dev, i);
		अगर (!encoder) अणु
			ret = -ENOMEM;
			जाओ err_drm_mode_cleanup;
		पूर्ण
		ret = vbox_connector_init(dev, vbox_crtc, encoder);
		अगर (ret)
			जाओ err_drm_mode_cleanup;
	पूर्ण

	drm_mode_config_reset(dev);
	वापस 0;

err_drm_mode_cleanup:
	drm_mode_config_cleanup(dev);
	वापस ret;
पूर्ण

व्योम vbox_mode_fini(काष्ठा vbox_निजी *vbox)
अणु
	drm_mode_config_cleanup(&vbox->ddev);
पूर्ण
