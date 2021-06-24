<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_rect.h>
#समावेश <drm/drm_sysfs.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vmwgfx_kms.h"

व्योम vmw_du_cleanup(काष्ठा vmw_display_unit *du)
अणु
	drm_plane_cleanup(&du->primary);
	drm_plane_cleanup(&du->cursor);

	drm_connector_unरेजिस्टर(&du->connector);
	drm_crtc_cleanup(&du->crtc);
	drm_encoder_cleanup(&du->encoder);
	drm_connector_cleanup(&du->connector);
पूर्ण

/*
 * Display Unit Cursor functions
 */

अटल पूर्णांक vmw_cursor_update_image(काष्ठा vmw_निजी *dev_priv,
				   u32 *image, u32 width, u32 height,
				   u32 hotspotX, u32 hotspotY)
अणु
	काष्ठा अणु
		u32 cmd;
		SVGAFअगरoCmdDefineAlphaCursor cursor;
	पूर्ण *cmd;
	u32 image_size = width * height * 4;
	u32 cmd_size = माप(*cmd) + image_size;

	अगर (!image)
		वापस -EINVAL;

	cmd = VMW_CMD_RESERVE(dev_priv, cmd_size);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	स_रखो(cmd, 0, माप(*cmd));

	स_नकल(&cmd[1], image, image_size);

	cmd->cmd = SVGA_CMD_DEFINE_ALPHA_CURSOR;
	cmd->cursor.id = 0;
	cmd->cursor.width = width;
	cmd->cursor.height = height;
	cmd->cursor.hotspotX = hotspotX;
	cmd->cursor.hotspotY = hotspotY;

	vmw_cmd_commit_flush(dev_priv, cmd_size);

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_cursor_update_bo(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_buffer_object *bo,
				u32 width, u32 height,
				u32 hotspotX, u32 hotspotY)
अणु
	काष्ठा tपंचांग_bo_kmap_obj map;
	अचिन्हित दीर्घ kmap_offset;
	अचिन्हित दीर्घ kmap_num;
	व्योम *भव;
	bool dummy;
	पूर्णांक ret;

	kmap_offset = 0;
	kmap_num = (width*height*4 + PAGE_SIZE - 1) >> PAGE_SHIFT;

	ret = tपंचांग_bo_reserve(&bo->base, true, false, शून्य);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("reserve failed\n");
		वापस -EINVAL;
	पूर्ण

	ret = tपंचांग_bo_kmap(&bo->base, kmap_offset, kmap_num, &map);
	अगर (unlikely(ret != 0))
		जाओ err_unreserve;

	भव = tपंचांग_kmap_obj_भव(&map, &dummy);
	ret = vmw_cursor_update_image(dev_priv, भव, width, height,
				      hotspotX, hotspotY);

	tपंचांग_bo_kunmap(&map);
err_unreserve:
	tपंचांग_bo_unreserve(&bo->base);

	वापस ret;
पूर्ण


अटल व्योम vmw_cursor_update_position(काष्ठा vmw_निजी *dev_priv,
				       bool show, पूर्णांक x, पूर्णांक y)
अणु
	uपूर्णांक32_t count;

	spin_lock(&dev_priv->cursor_lock);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_CURSOR_ON, show ? 1 : 0);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_CURSOR_X, x);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_CURSOR_Y, y);
	count = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_CURSOR_COUNT);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_CURSOR_COUNT, ++count);
	spin_unlock(&dev_priv->cursor_lock);
पूर्ण


व्योम vmw_kms_cursor_snoop(काष्ठा vmw_surface *srf,
			  काष्ठा tपंचांग_object_file *tfile,
			  काष्ठा tपंचांग_buffer_object *bo,
			  SVGA3dCmdHeader *header)
अणु
	काष्ठा tपंचांग_bo_kmap_obj map;
	अचिन्हित दीर्घ kmap_offset;
	अचिन्हित दीर्घ kmap_num;
	SVGA3dCopyBox *box;
	अचिन्हित box_count;
	व्योम *भव;
	bool dummy;
	काष्ठा vmw_dma_cmd अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdSurfaceDMA dma;
	पूर्ण *cmd;
	पूर्णांक i, ret;

	cmd = container_of(header, काष्ठा vmw_dma_cmd, header);

	/* No snooper installed */
	अगर (!srf->snooper.image)
		वापस;

	अगर (cmd->dma.host.face != 0 || cmd->dma.host.mipmap != 0) अणु
		DRM_ERROR("face and mipmap for cursors should never != 0\n");
		वापस;
	पूर्ण

	अगर (cmd->header.size < 64) अणु
		DRM_ERROR("at least one full copy box must be given\n");
		वापस;
	पूर्ण

	box = (SVGA3dCopyBox *)&cmd[1];
	box_count = (cmd->header.size - माप(SVGA3dCmdSurfaceDMA)) /
			माप(SVGA3dCopyBox);

	अगर (cmd->dma.guest.ptr.offset % PAGE_SIZE ||
	    box->x != 0    || box->y != 0    || box->z != 0    ||
	    box->srcx != 0 || box->srcy != 0 || box->srcz != 0 ||
	    box->d != 1    || box_count != 1) अणु
		/* TODO handle none page aligned offsets */
		/* TODO handle more dst & src != 0 */
		/* TODO handle more then one copy */
		DRM_ERROR("Can't snoop dma request for cursor!\n");
		DRM_ERROR("(%u, %u, %u) (%u, %u, %u) (%ux%ux%u) %u %u\n",
			  box->srcx, box->srcy, box->srcz,
			  box->x, box->y, box->z,
			  box->w, box->h, box->d, box_count,
			  cmd->dma.guest.ptr.offset);
		वापस;
	पूर्ण

	kmap_offset = cmd->dma.guest.ptr.offset >> PAGE_SHIFT;
	kmap_num = (64*64*4) >> PAGE_SHIFT;

	ret = tपंचांग_bo_reserve(bo, true, false, शून्य);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("reserve failed\n");
		वापस;
	पूर्ण

	ret = tपंचांग_bo_kmap(bo, kmap_offset, kmap_num, &map);
	अगर (unlikely(ret != 0))
		जाओ err_unreserve;

	भव = tपंचांग_kmap_obj_भव(&map, &dummy);

	अगर (box->w == 64 && cmd->dma.guest.pitch == 64*4) अणु
		स_नकल(srf->snooper.image, भव, 64*64*4);
	पूर्ण अन्यथा अणु
		/* Image is अचिन्हित poपूर्णांकer. */
		क्रम (i = 0; i < box->h; i++)
			स_नकल(srf->snooper.image + i * 64,
			       भव + i * cmd->dma.guest.pitch,
			       box->w * 4);
	पूर्ण

	srf->snooper.age++;

	tपंचांग_bo_kunmap(&map);
err_unreserve:
	tपंचांग_bo_unreserve(bo);
पूर्ण

/**
 * vmw_kms_legacy_hotspot_clear - Clear legacy hotspots
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठा.
 *
 * Clears all legacy hotspots.
 */
व्योम vmw_kms_legacy_hotspot_clear(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा vmw_display_unit *du;
	काष्ठा drm_crtc *crtc;

	drm_modeset_lock_all(dev);
	drm_क्रम_each_crtc(crtc, dev) अणु
		du = vmw_crtc_to_du(crtc);

		du->hotspot_x = 0;
		du->hotspot_y = 0;
	पूर्ण
	drm_modeset_unlock_all(dev);
पूर्ण

व्योम vmw_kms_cursor_post_execbuf(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा vmw_display_unit *du;
	काष्ठा drm_crtc *crtc;

	mutex_lock(&dev->mode_config.mutex);

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		du = vmw_crtc_to_du(crtc);
		अगर (!du->cursor_surface ||
		    du->cursor_age == du->cursor_surface->snooper.age)
			जारी;

		du->cursor_age = du->cursor_surface->snooper.age;
		vmw_cursor_update_image(dev_priv,
					du->cursor_surface->snooper.image,
					64, 64,
					du->hotspot_x + du->core_hotspot_x,
					du->hotspot_y + du->core_hotspot_y);
	पूर्ण

	mutex_unlock(&dev->mode_config.mutex);
पूर्ण


व्योम vmw_du_cursor_plane_destroy(काष्ठा drm_plane *plane)
अणु
	vmw_cursor_update_position(plane->dev->dev_निजी, false, 0, 0);

	drm_plane_cleanup(plane);
पूर्ण


व्योम vmw_du_primary_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);

	/* Planes are अटल in our हाल so we करोn't मुक्त it */
पूर्ण


/**
 * vmw_du_vps_unpin_surf - unpins resource associated with a framebuffer surface
 *
 * @vps: plane state associated with the display surface
 * @unreference: true अगर we also want to unreference the display.
 */
व्योम vmw_du_plane_unpin_surf(काष्ठा vmw_plane_state *vps,
			     bool unreference)
अणु
	अगर (vps->surf) अणु
		अगर (vps->pinned) अणु
			vmw_resource_unpin(&vps->surf->res);
			vps->pinned--;
		पूर्ण

		अगर (unreference) अणु
			अगर (vps->pinned)
				DRM_ERROR("Surface still pinned\n");
			vmw_surface_unreference(&vps->surf);
		पूर्ण
	पूर्ण
पूर्ण


/**
 * vmw_du_plane_cleanup_fb - Unpins the cursor
 *
 * @plane:  display plane
 * @old_state: Contains the FB to clean up
 *
 * Unpins the framebuffer surface
 *
 * Returns 0 on success
 */
व्योम
vmw_du_plane_cleanup_fb(काष्ठा drm_plane *plane,
			काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(old_state);

	vmw_du_plane_unpin_surf(vps, false);
पूर्ण


/**
 * vmw_du_cursor_plane_prepare_fb - Readies the cursor by referencing it
 *
 * @plane:  display plane
 * @new_state: info on the new plane state, including the FB
 *
 * Returns 0 on success
 */
पूर्णांक
vmw_du_cursor_plane_prepare_fb(काष्ठा drm_plane *plane,
			       काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा drm_framebuffer *fb = new_state->fb;
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(new_state);


	अगर (vps->surf)
		vmw_surface_unreference(&vps->surf);

	अगर (vps->bo)
		vmw_bo_unreference(&vps->bo);

	अगर (fb) अणु
		अगर (vmw_framebuffer_to_vfb(fb)->bo) अणु
			vps->bo = vmw_framebuffer_to_vfbd(fb)->buffer;
			vmw_bo_reference(vps->bo);
		पूर्ण अन्यथा अणु
			vps->surf = vmw_framebuffer_to_vfbs(fb)->surface;
			vmw_surface_reference(vps->surf);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण


व्योम
vmw_du_cursor_plane_atomic_update(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_crtc *crtc = new_state->crtc ?: old_state->crtc;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(crtc->dev);
	काष्ठा vmw_display_unit *du = vmw_crtc_to_du(crtc);
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(new_state);
	s32 hotspot_x, hotspot_y;
	पूर्णांक ret = 0;


	hotspot_x = du->hotspot_x;
	hotspot_y = du->hotspot_y;

	अगर (new_state->fb) अणु
		hotspot_x += new_state->fb->hot_x;
		hotspot_y += new_state->fb->hot_y;
	पूर्ण

	du->cursor_surface = vps->surf;
	du->cursor_bo = vps->bo;

	अगर (vps->surf) अणु
		du->cursor_age = du->cursor_surface->snooper.age;

		ret = vmw_cursor_update_image(dev_priv,
					      vps->surf->snooper.image,
					      64, 64, hotspot_x,
					      hotspot_y);
	पूर्ण अन्यथा अगर (vps->bo) अणु
		ret = vmw_cursor_update_bo(dev_priv, vps->bo,
					   new_state->crtc_w,
					   new_state->crtc_h,
					   hotspot_x, hotspot_y);
	पूर्ण अन्यथा अणु
		vmw_cursor_update_position(dev_priv, false, 0, 0);
		वापस;
	पूर्ण

	अगर (!ret) अणु
		du->cursor_x = new_state->crtc_x + du->set_gui_x;
		du->cursor_y = new_state->crtc_y + du->set_gui_y;

		vmw_cursor_update_position(dev_priv, true,
					   du->cursor_x + hotspot_x,
					   du->cursor_y + hotspot_y);

		du->core_hotspot_x = hotspot_x - du->hotspot_x;
		du->core_hotspot_y = hotspot_y - du->hotspot_y;
	पूर्ण अन्यथा अणु
		DRM_ERROR("Failed to update cursor image\n");
	पूर्ण
पूर्ण


/**
 * vmw_du_primary_plane_atomic_check - check अगर the new state is okay
 *
 * @plane: display plane
 * @state: info on the new plane state, including the FB
 *
 * Check अगर the new state is settable given the current state.  Other
 * than what the atomic helper checks, we care about crtc fitting
 * the FB and मुख्यtaining one active framebuffer.
 *
 * Returns 0 on success
 */
पूर्णांक vmw_du_primary_plane_atomic_check(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_crtc_state *crtc_state = शून्य;
	काष्ठा drm_framebuffer *new_fb = new_state->fb;
	पूर्णांक ret;

	अगर (new_state->crtc)
		crtc_state = drm_atomic_get_new_crtc_state(state,
							   new_state->crtc);

	ret = drm_atomic_helper_check_plane_state(new_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  false, true);

	अगर (!ret && new_fb) अणु
		काष्ठा drm_crtc *crtc = new_state->crtc;
		काष्ठा vmw_display_unit *du = vmw_crtc_to_du(crtc);

		vmw_connector_state_to_vcs(du->connector.state);
	पूर्ण


	वापस ret;
पूर्ण


/**
 * vmw_du_cursor_plane_atomic_check - check अगर the new state is okay
 *
 * @plane: cursor plane
 * @new_state: info on the new plane state
 *
 * This is a chance to fail अगर the new cursor state करोes not fit
 * our requirements.
 *
 * Returns 0 on success
 */
पूर्णांक vmw_du_cursor_plane_atomic_check(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	पूर्णांक ret = 0;
	काष्ठा drm_crtc_state *crtc_state = शून्य;
	काष्ठा vmw_surface *surface = शून्य;
	काष्ठा drm_framebuffer *fb = new_state->fb;

	अगर (new_state->crtc)
		crtc_state = drm_atomic_get_new_crtc_state(new_state->state,
							   new_state->crtc);

	ret = drm_atomic_helper_check_plane_state(new_state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	अगर (ret)
		वापस ret;

	/* Turning off */
	अगर (!fb)
		वापस 0;

	/* A lot of the code assumes this */
	अगर (new_state->crtc_w != 64 || new_state->crtc_h != 64) अणु
		DRM_ERROR("Invalid cursor dimensions (%d, %d)\n",
			  new_state->crtc_w, new_state->crtc_h);
		ret = -EINVAL;
	पूर्ण

	अगर (!vmw_framebuffer_to_vfb(fb)->bo)
		surface = vmw_framebuffer_to_vfbs(fb)->surface;

	अगर (surface && !surface->snooper.image) अणु
		DRM_ERROR("surface not suitable for cursor\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण


पूर्णांक vmw_du_crtc_atomic_check(काष्ठा drm_crtc *crtc,
			     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *new_state = drm_atomic_get_new_crtc_state(state,
									 crtc);
	काष्ठा vmw_display_unit *du = vmw_crtc_to_du(new_state->crtc);
	पूर्णांक connector_mask = drm_connector_mask(&du->connector);
	bool has_primary = new_state->plane_mask &
			   drm_plane_mask(crtc->primary);

	/* We always want to have an active plane with an active CRTC */
	अगर (has_primary != new_state->enable)
		वापस -EINVAL;


	अगर (new_state->connector_mask != connector_mask &&
	    new_state->connector_mask != 0) अणु
		DRM_ERROR("Invalid connectors configuration\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Our भव device करोes not have a करोt घड़ी, so use the logical
	 * घड़ी value as the करोt घड़ी.
	 */
	अगर (new_state->mode.crtc_घड़ी == 0)
		new_state->adjusted_mode.crtc_घड़ी = new_state->mode.घड़ी;

	वापस 0;
पूर्ण


व्योम vmw_du_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state)
अणु
पूर्ण


व्योम vmw_du_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण


/**
 * vmw_du_crtc_duplicate_state - duplicate crtc state
 * @crtc: DRM crtc
 *
 * Allocates and वापसs a copy of the crtc state (both common and
 * vmw-specअगरic) क्रम the specअगरied crtc.
 *
 * Returns: The newly allocated crtc state, or शून्य on failure.
 */
काष्ठा drm_crtc_state *
vmw_du_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_crtc_state *state;
	काष्ठा vmw_crtc_state *vcs;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	vcs = kmemdup(crtc->state, माप(*vcs), GFP_KERNEL);

	अगर (!vcs)
		वापस शून्य;

	state = &vcs->base;

	__drm_atomic_helper_crtc_duplicate_state(crtc, state);

	वापस state;
पूर्ण


/**
 * vmw_du_crtc_reset - creates a blank vmw crtc state
 * @crtc: DRM crtc
 *
 * Resets the atomic state क्रम @crtc by मुक्तing the state poपूर्णांकer (which
 * might be शून्य, e.g. at driver load समय) and allocating a new empty state
 * object.
 */
व्योम vmw_du_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vmw_crtc_state *vcs;


	अगर (crtc->state) अणु
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

		kमुक्त(vmw_crtc_state_to_vcs(crtc->state));
	पूर्ण

	vcs = kzalloc(माप(*vcs), GFP_KERNEL);

	अगर (!vcs) अणु
		DRM_ERROR("Cannot allocate vmw_crtc_state\n");
		वापस;
	पूर्ण

	__drm_atomic_helper_crtc_reset(crtc, &vcs->base);
पूर्ण


/**
 * vmw_du_crtc_destroy_state - destroy crtc state
 * @crtc: DRM crtc
 * @state: state object to destroy
 *
 * Destroys the crtc state (both common and vmw-specअगरic) क्रम the
 * specअगरied plane.
 */
व्योम
vmw_du_crtc_destroy_state(काष्ठा drm_crtc *crtc,
			  काष्ठा drm_crtc_state *state)
अणु
	drm_atomic_helper_crtc_destroy_state(crtc, state);
पूर्ण


/**
 * vmw_du_plane_duplicate_state - duplicate plane state
 * @plane: drm plane
 *
 * Allocates and वापसs a copy of the plane state (both common and
 * vmw-specअगरic) क्रम the specअगरied plane.
 *
 * Returns: The newly allocated plane state, or शून्य on failure.
 */
काष्ठा drm_plane_state *
vmw_du_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_plane_state *state;
	काष्ठा vmw_plane_state *vps;

	vps = kmemdup(plane->state, माप(*vps), GFP_KERNEL);

	अगर (!vps)
		वापस शून्य;

	vps->pinned = 0;
	vps->cpp = 0;

	/* Each ref counted resource needs to be acquired again */
	अगर (vps->surf)
		(व्योम) vmw_surface_reference(vps->surf);

	अगर (vps->bo)
		(व्योम) vmw_bo_reference(vps->bo);

	state = &vps->base;

	__drm_atomic_helper_plane_duplicate_state(plane, state);

	वापस state;
पूर्ण


/**
 * vmw_du_plane_reset - creates a blank vmw plane state
 * @plane: drm plane
 *
 * Resets the atomic state क्रम @plane by मुक्तing the state poपूर्णांकer (which might
 * be शून्य, e.g. at driver load समय) and allocating a new empty state object.
 */
व्योम vmw_du_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा vmw_plane_state *vps;


	अगर (plane->state)
		vmw_du_plane_destroy_state(plane, plane->state);

	vps = kzalloc(माप(*vps), GFP_KERNEL);

	अगर (!vps) अणु
		DRM_ERROR("Cannot allocate vmw_plane_state\n");
		वापस;
	पूर्ण

	__drm_atomic_helper_plane_reset(plane, &vps->base);
पूर्ण


/**
 * vmw_du_plane_destroy_state - destroy plane state
 * @plane: DRM plane
 * @state: state object to destroy
 *
 * Destroys the plane state (both common and vmw-specअगरic) क्रम the
 * specअगरied plane.
 */
व्योम
vmw_du_plane_destroy_state(काष्ठा drm_plane *plane,
			   काष्ठा drm_plane_state *state)
अणु
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(state);


	/* Should have been मुक्तd by cleanup_fb */
	अगर (vps->surf)
		vmw_surface_unreference(&vps->surf);

	अगर (vps->bo)
		vmw_bo_unreference(&vps->bo);

	drm_atomic_helper_plane_destroy_state(plane, state);
पूर्ण


/**
 * vmw_du_connector_duplicate_state - duplicate connector state
 * @connector: DRM connector
 *
 * Allocates and वापसs a copy of the connector state (both common and
 * vmw-specअगरic) क्रम the specअगरied connector.
 *
 * Returns: The newly allocated connector state, or शून्य on failure.
 */
काष्ठा drm_connector_state *
vmw_du_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_connector_state *state;
	काष्ठा vmw_connector_state *vcs;

	अगर (WARN_ON(!connector->state))
		वापस शून्य;

	vcs = kmemdup(connector->state, माप(*vcs), GFP_KERNEL);

	अगर (!vcs)
		वापस शून्य;

	state = &vcs->base;

	__drm_atomic_helper_connector_duplicate_state(connector, state);

	वापस state;
पूर्ण


/**
 * vmw_du_connector_reset - creates a blank vmw connector state
 * @connector: DRM connector
 *
 * Resets the atomic state क्रम @connector by मुक्तing the state poपूर्णांकer (which
 * might be शून्य, e.g. at driver load समय) and allocating a new empty state
 * object.
 */
व्योम vmw_du_connector_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा vmw_connector_state *vcs;


	अगर (connector->state) अणु
		__drm_atomic_helper_connector_destroy_state(connector->state);

		kमुक्त(vmw_connector_state_to_vcs(connector->state));
	पूर्ण

	vcs = kzalloc(माप(*vcs), GFP_KERNEL);

	अगर (!vcs) अणु
		DRM_ERROR("Cannot allocate vmw_connector_state\n");
		वापस;
	पूर्ण

	__drm_atomic_helper_connector_reset(connector, &vcs->base);
पूर्ण


/**
 * vmw_du_connector_destroy_state - destroy connector state
 * @connector: DRM connector
 * @state: state object to destroy
 *
 * Destroys the connector state (both common and vmw-specअगरic) क्रम the
 * specअगरied plane.
 */
व्योम
vmw_du_connector_destroy_state(काष्ठा drm_connector *connector,
			  काष्ठा drm_connector_state *state)
अणु
	drm_atomic_helper_connector_destroy_state(connector, state);
पूर्ण
/*
 * Generic framebuffer code
 */

/*
 * Surface framebuffer code
 */

अटल व्योम vmw_framebuffer_surface_destroy(काष्ठा drm_framebuffer *framebuffer)
अणु
	काष्ठा vmw_framebuffer_surface *vfbs =
		vmw_framebuffer_to_vfbs(framebuffer);

	drm_framebuffer_cleanup(framebuffer);
	vmw_surface_unreference(&vfbs->surface);
	अगर (vfbs->base.user_obj)
		tपंचांग_base_object_unref(&vfbs->base.user_obj);

	kमुक्त(vfbs);
पूर्ण

/**
 * vmw_kms_पढ़ोback - Perक्रमm a पढ़ोback from the screen प्रणाली to
 * a buffer-object backed framebuffer.
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठाure.
 * @file_priv: Poपूर्णांकer to a काष्ठा drm_file identअगरying the caller.
 * Must be set to शून्य अगर @user_fence_rep is शून्य.
 * @vfb: Poपूर्णांकer to the buffer-object backed framebuffer.
 * @user_fence_rep: User-space provided काष्ठाure क्रम fence inक्रमmation.
 * Must be set to non-शून्य अगर @file_priv is non-शून्य.
 * @vclips: Array of clip rects.
 * @num_clips: Number of clip rects in @vclips.
 *
 * Returns 0 on success, negative error code on failure. -ERESTARTSYS अगर
 * पूर्णांकerrupted.
 */
पूर्णांक vmw_kms_पढ़ोback(काष्ठा vmw_निजी *dev_priv,
		     काष्ठा drm_file *file_priv,
		     काष्ठा vmw_framebuffer *vfb,
		     काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
		     काष्ठा drm_vmw_rect *vclips,
		     uपूर्णांक32_t num_clips)
अणु
	चयन (dev_priv->active_display_unit) अणु
	हाल vmw_du_screen_object:
		वापस vmw_kms_sou_पढ़ोback(dev_priv, file_priv, vfb,
					    user_fence_rep, vclips, num_clips,
					    शून्य);
	हाल vmw_du_screen_target:
		वापस vmw_kms_stdu_dma(dev_priv, file_priv, vfb,
					user_fence_rep, शून्य, vclips, num_clips,
					1, false, true, शून्य);
	शेष:
		WARN_ONCE(true,
			  "Readback called with invalid display system.\n");
पूर्ण

	वापस -ENOSYS;
पूर्ण


अटल स्थिर काष्ठा drm_framebuffer_funcs vmw_framebuffer_surface_funcs = अणु
	.destroy = vmw_framebuffer_surface_destroy,
	.dirty = drm_atomic_helper_dirtyfb,
पूर्ण;

अटल पूर्णांक vmw_kms_new_framebuffer_surface(काष्ठा vmw_निजी *dev_priv,
					   काष्ठा vmw_surface *surface,
					   काष्ठा vmw_framebuffer **out,
					   स्थिर काष्ठा drm_mode_fb_cmd2
					   *mode_cmd,
					   bool is_bo_proxy)

अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा vmw_framebuffer_surface *vfbs;
	क्रमागत SVGA3dSurfaceFormat क्रमmat;
	पूर्णांक ret;

	/* 3D is only supported on HWv8 and newer hosts */
	अगर (dev_priv->active_display_unit == vmw_du_legacy)
		वापस -ENOSYS;

	/*
	 * Sanity checks.
	 */

	/* Surface must be marked as a scanout. */
	अगर (unlikely(!surface->metadata.scanout))
		वापस -EINVAL;

	अगर (unlikely(surface->metadata.mip_levels[0] != 1 ||
		     surface->metadata.num_sizes != 1 ||
		     surface->metadata.base_size.width < mode_cmd->width ||
		     surface->metadata.base_size.height < mode_cmd->height ||
		     surface->metadata.base_size.depth != 1)) अणु
		DRM_ERROR("Incompatible surface dimensions "
			  "for requested mode.\n");
		वापस -EINVAL;
	पूर्ण

	चयन (mode_cmd->pixel_क्रमmat) अणु
	हाल DRM_FORMAT_ARGB8888:
		क्रमmat = SVGA3D_A8R8G8B8;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		क्रमmat = SVGA3D_X8R8G8B8;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		क्रमmat = SVGA3D_R5G6B5;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		क्रमmat = SVGA3D_A1R5G5B5;
		अवरोध;
	शेष:
		DRM_ERROR("Invalid pixel format: %p4cc\n",
			  &mode_cmd->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	/*
	 * For DX, surface क्रमmat validation is करोne when surface->scanout
	 * is set.
	 */
	अगर (!has_sm4_context(dev_priv) && क्रमmat != surface->metadata.क्रमmat) अणु
		DRM_ERROR("Invalid surface format for requested mode.\n");
		वापस -EINVAL;
	पूर्ण

	vfbs = kzalloc(माप(*vfbs), GFP_KERNEL);
	अगर (!vfbs) अणु
		ret = -ENOMEM;
		जाओ out_err1;
	पूर्ण

	drm_helper_mode_fill_fb_काष्ठा(dev, &vfbs->base.base, mode_cmd);
	vfbs->surface = vmw_surface_reference(surface);
	vfbs->base.user_handle = mode_cmd->handles[0];
	vfbs->is_bo_proxy = is_bo_proxy;

	*out = &vfbs->base;

	ret = drm_framebuffer_init(dev, &vfbs->base.base,
				   &vmw_framebuffer_surface_funcs);
	अगर (ret)
		जाओ out_err2;

	वापस 0;

out_err2:
	vmw_surface_unreference(&surface);
	kमुक्त(vfbs);
out_err1:
	वापस ret;
पूर्ण

/*
 * Buffer-object framebuffer code
 */

अटल व्योम vmw_framebuffer_bo_destroy(काष्ठा drm_framebuffer *framebuffer)
अणु
	काष्ठा vmw_framebuffer_bo *vfbd =
		vmw_framebuffer_to_vfbd(framebuffer);

	drm_framebuffer_cleanup(framebuffer);
	vmw_bo_unreference(&vfbd->buffer);
	अगर (vfbd->base.user_obj)
		tपंचांग_base_object_unref(&vfbd->base.user_obj);

	kमुक्त(vfbd);
पूर्ण

अटल पूर्णांक vmw_framebuffer_bo_dirty(काष्ठा drm_framebuffer *framebuffer,
				    काष्ठा drm_file *file_priv,
				    अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक color,
				    काष्ठा drm_clip_rect *clips,
				    अचिन्हित पूर्णांक num_clips)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(framebuffer->dev);
	काष्ठा vmw_framebuffer_bo *vfbd =
		vmw_framebuffer_to_vfbd(framebuffer);
	काष्ठा drm_clip_rect norect;
	पूर्णांक ret, increment = 1;

	drm_modeset_lock_all(&dev_priv->drm);

	ret = tपंचांग_पढ़ो_lock(&dev_priv->reservation_sem, true);
	अगर (unlikely(ret != 0)) अणु
		drm_modeset_unlock_all(&dev_priv->drm);
		वापस ret;
	पूर्ण

	अगर (!num_clips) अणु
		num_clips = 1;
		clips = &norect;
		norect.x1 = norect.y1 = 0;
		norect.x2 = framebuffer->width;
		norect.y2 = framebuffer->height;
	पूर्ण अन्यथा अगर (flags & DRM_MODE_FB_सूचीTY_ANNOTATE_COPY) अणु
		num_clips /= 2;
		increment = 2;
	पूर्ण

	चयन (dev_priv->active_display_unit) अणु
	हाल vmw_du_legacy:
		ret = vmw_kms_ldu_करो_bo_dirty(dev_priv, &vfbd->base, 0, 0,
					      clips, num_clips, increment);
		अवरोध;
	शेष:
		ret = -EINVAL;
		WARN_ONCE(true, "Dirty called with invalid display system.\n");
		अवरोध;
	पूर्ण

	vmw_cmd_flush(dev_priv, false);
	tपंचांग_पढ़ो_unlock(&dev_priv->reservation_sem);

	drm_modeset_unlock_all(&dev_priv->drm);

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_framebuffer_bo_dirty_ext(काष्ठा drm_framebuffer *framebuffer,
					काष्ठा drm_file *file_priv,
					अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक color,
					काष्ठा drm_clip_rect *clips,
					अचिन्हित पूर्णांक num_clips)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(framebuffer->dev);

	अगर (dev_priv->active_display_unit == vmw_du_legacy)
		वापस vmw_framebuffer_bo_dirty(framebuffer, file_priv, flags,
						color, clips, num_clips);

	वापस drm_atomic_helper_dirtyfb(framebuffer, file_priv, flags, color,
					 clips, num_clips);
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs vmw_framebuffer_bo_funcs = अणु
	.destroy = vmw_framebuffer_bo_destroy,
	.dirty = vmw_framebuffer_bo_dirty_ext,
पूर्ण;

/*
 * Pin the bofer in a location suitable क्रम access by the
 * display प्रणाली.
 */
अटल पूर्णांक vmw_framebuffer_pin(काष्ठा vmw_framebuffer *vfb)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(vfb->base.dev);
	काष्ठा vmw_buffer_object *buf;
	काष्ठा tपंचांग_placement *placement;
	पूर्णांक ret;

	buf = vfb->bo ?  vmw_framebuffer_to_vfbd(&vfb->base)->buffer :
		vmw_framebuffer_to_vfbs(&vfb->base)->surface->res.backup;

	अगर (!buf)
		वापस 0;

	चयन (dev_priv->active_display_unit) अणु
	हाल vmw_du_legacy:
		vmw_overlay_छोड़ो_all(dev_priv);
		ret = vmw_bo_pin_in_start_of_vram(dev_priv, buf, false);
		vmw_overlay_resume_all(dev_priv);
		अवरोध;
	हाल vmw_du_screen_object:
	हाल vmw_du_screen_target:
		अगर (vfb->bo) अणु
			अगर (dev_priv->capabilities & SVGA_CAP_3D) अणु
				/*
				 * Use surface DMA to get content to
				 * sreen target surface.
				 */
				placement = &vmw_vram_gmr_placement;
			पूर्ण अन्यथा अणु
				/* Use CPU blit. */
				placement = &vmw_sys_placement;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Use surface / image update */
			placement = &vmw_mob_placement;
		पूर्ण

		वापस vmw_bo_pin_in_placement(dev_priv, buf, placement, false);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vmw_framebuffer_unpin(काष्ठा vmw_framebuffer *vfb)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(vfb->base.dev);
	काष्ठा vmw_buffer_object *buf;

	buf = vfb->bo ?  vmw_framebuffer_to_vfbd(&vfb->base)->buffer :
		vmw_framebuffer_to_vfbs(&vfb->base)->surface->res.backup;

	अगर (WARN_ON(!buf))
		वापस 0;

	वापस vmw_bo_unpin(dev_priv, buf, false);
पूर्ण

/**
 * vmw_create_bo_proxy - create a proxy surface क्रम the buffer object
 *
 * @dev: DRM device
 * @mode_cmd: parameters क्रम the new surface
 * @bo_mob: MOB backing the buffer object
 * @srf_out: newly created surface
 *
 * When the content FB is a buffer object, we create a surface as a proxy to the
 * same buffer.  This way we can करो a surface copy rather than a surface DMA.
 * This is a more efficient approach
 *
 * RETURNS:
 * 0 on success, error code otherwise
 */
अटल पूर्णांक vmw_create_bo_proxy(काष्ठा drm_device *dev,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			       काष्ठा vmw_buffer_object *bo_mob,
			       काष्ठा vmw_surface **srf_out)
अणु
	काष्ठा vmw_surface_metadata metadata = अणु0पूर्ण;
	uपूर्णांक32_t क्रमmat;
	काष्ठा vmw_resource *res;
	अचिन्हित पूर्णांक bytes_pp;
	पूर्णांक ret;

	चयन (mode_cmd->pixel_क्रमmat) अणु
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB8888:
		क्रमmat = SVGA3D_X8R8G8B8;
		bytes_pp = 4;
		अवरोध;

	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_XRGB1555:
		क्रमmat = SVGA3D_R5G6B5;
		bytes_pp = 2;
		अवरोध;

	हाल 8:
		क्रमmat = SVGA3D_P8;
		bytes_pp = 1;
		अवरोध;

	शेष:
		DRM_ERROR("Invalid framebuffer format %p4cc\n",
			  &mode_cmd->pixel_क्रमmat);
		वापस -EINVAL;
	पूर्ण

	metadata.क्रमmat = क्रमmat;
	metadata.mip_levels[0] = 1;
	metadata.num_sizes = 1;
	metadata.base_size.width = mode_cmd->pitches[0] / bytes_pp;
	metadata.base_size.height =  mode_cmd->height;
	metadata.base_size.depth = 1;
	metadata.scanout = true;

	ret = vmw_gb_surface_define(vmw_priv(dev), 0, &metadata, srf_out);
	अगर (ret) अणु
		DRM_ERROR("Failed to allocate proxy content buffer\n");
		वापस ret;
	पूर्ण

	res = &(*srf_out)->res;

	/* Reserve and चयन the backing mob. */
	mutex_lock(&res->dev_priv->cmdbuf_mutex);
	(व्योम) vmw_resource_reserve(res, false, true);
	vmw_bo_unreference(&res->backup);
	res->backup = vmw_bo_reference(bo_mob);
	res->backup_offset = 0;
	vmw_resource_unreserve(res, false, false, false, शून्य, 0);
	mutex_unlock(&res->dev_priv->cmdbuf_mutex);

	वापस 0;
पूर्ण



अटल पूर्णांक vmw_kms_new_framebuffer_bo(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा vmw_buffer_object *bo,
				      काष्ठा vmw_framebuffer **out,
				      स्थिर काष्ठा drm_mode_fb_cmd2
				      *mode_cmd)

अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा vmw_framebuffer_bo *vfbd;
	अचिन्हित पूर्णांक requested_size;
	पूर्णांक ret;

	requested_size = mode_cmd->height * mode_cmd->pitches[0];
	अगर (unlikely(requested_size > bo->base.base.size)) अणु
		DRM_ERROR("Screen buffer object size is too small "
			  "for requested mode.\n");
		वापस -EINVAL;
	पूर्ण

	/* Limited framebuffer color depth support क्रम screen objects */
	अगर (dev_priv->active_display_unit == vmw_du_screen_object) अणु
		चयन (mode_cmd->pixel_क्रमmat) अणु
		हाल DRM_FORMAT_XRGB8888:
		हाल DRM_FORMAT_ARGB8888:
			अवरोध;
		हाल DRM_FORMAT_XRGB1555:
		हाल DRM_FORMAT_RGB565:
			अवरोध;
		शेष:
			DRM_ERROR("Invalid pixel format: %p4cc\n",
				  &mode_cmd->pixel_क्रमmat);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	vfbd = kzalloc(माप(*vfbd), GFP_KERNEL);
	अगर (!vfbd) अणु
		ret = -ENOMEM;
		जाओ out_err1;
	पूर्ण

	drm_helper_mode_fill_fb_काष्ठा(dev, &vfbd->base.base, mode_cmd);
	vfbd->base.bo = true;
	vfbd->buffer = vmw_bo_reference(bo);
	vfbd->base.user_handle = mode_cmd->handles[0];
	*out = &vfbd->base;

	ret = drm_framebuffer_init(dev, &vfbd->base.base,
				   &vmw_framebuffer_bo_funcs);
	अगर (ret)
		जाओ out_err2;

	वापस 0;

out_err2:
	vmw_bo_unreference(&bo);
	kमुक्त(vfbd);
out_err1:
	वापस ret;
पूर्ण


/**
 * vmw_kms_srf_ok - check अगर a surface can be created
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 * @width: requested width
 * @height: requested height
 *
 * Surfaces need to be less than texture size
 */
अटल bool
vmw_kms_srf_ok(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t width, uपूर्णांक32_t height)
अणु
	अगर (width  > dev_priv->texture_max_width ||
	    height > dev_priv->texture_max_height)
		वापस false;

	वापस true;
पूर्ण

/**
 * vmw_kms_new_framebuffer - Create a new framebuffer.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठा.
 * @bo: Poपूर्णांकer to buffer object to wrap the kms framebuffer around.
 * Either @bo or @surface must be शून्य.
 * @surface: Poपूर्णांकer to a surface to wrap the kms framebuffer around.
 * Either @bo or @surface must be शून्य.
 * @only_2d: No presents will occur to this buffer object based framebuffer.
 * This helps the code to करो some important optimizations.
 * @mode_cmd: Frame-buffer metadata.
 */
काष्ठा vmw_framebuffer *
vmw_kms_new_framebuffer(काष्ठा vmw_निजी *dev_priv,
			काष्ठा vmw_buffer_object *bo,
			काष्ठा vmw_surface *surface,
			bool only_2d,
			स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा vmw_framebuffer *vfb = शून्य;
	bool is_bo_proxy = false;
	पूर्णांक ret;

	/*
	 * We cannot use the SurfaceDMA command in an non-accelerated VM,
	 * thereक्रमe, wrap the buffer object in a surface so we can use the
	 * SurfaceCopy command.
	 */
	अगर (vmw_kms_srf_ok(dev_priv, mode_cmd->width, mode_cmd->height)  &&
	    bo && only_2d &&
	    mode_cmd->width > 64 &&  /* Don't create a proxy क्रम cursor */
	    dev_priv->active_display_unit == vmw_du_screen_target) अणु
		ret = vmw_create_bo_proxy(&dev_priv->drm, mode_cmd,
					  bo, &surface);
		अगर (ret)
			वापस ERR_PTR(ret);

		is_bo_proxy = true;
	पूर्ण

	/* Create the new framebuffer depending one what we have */
	अगर (surface) अणु
		ret = vmw_kms_new_framebuffer_surface(dev_priv, surface, &vfb,
						      mode_cmd,
						      is_bo_proxy);

		/*
		 * vmw_create_bo_proxy() adds a reference that is no दीर्घer
		 * needed
		 */
		अगर (is_bo_proxy)
			vmw_surface_unreference(&surface);
	पूर्ण अन्यथा अगर (bo) अणु
		ret = vmw_kms_new_framebuffer_bo(dev_priv, bo, &vfb,
						 mode_cmd);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण

	अगर (ret)
		वापस ERR_PTR(ret);

	vfb->pin = vmw_framebuffer_pin;
	vfb->unpin = vmw_framebuffer_unpin;

	वापस vfb;
पूर्ण

/*
 * Generic Kernel modesetting functions
 */

अटल काष्ठा drm_framebuffer *vmw_kms_fb_create(काष्ठा drm_device *dev,
						 काष्ठा drm_file *file_priv,
						 स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा tपंचांग_object_file *tfile = vmw_fpriv(file_priv)->tfile;
	काष्ठा vmw_framebuffer *vfb = शून्य;
	काष्ठा vmw_surface *surface = शून्य;
	काष्ठा vmw_buffer_object *bo = शून्य;
	काष्ठा tपंचांग_base_object *user_obj;
	पूर्णांक ret;

	/*
	 * Take a reference on the user object of the resource
	 * backing the kms fb. This ensures that user-space handle
	 * lookups on that resource will always work as दीर्घ as
	 * it's रेजिस्टरed with a kms framebuffer. This is important,
	 * since vmw_execbuf_process identअगरies resources in the
	 * command stream using user-space handles.
	 */

	user_obj = tपंचांग_base_object_lookup(tfile, mode_cmd->handles[0]);
	अगर (unlikely(user_obj == शून्य)) अणु
		DRM_ERROR("Could not locate requested kms frame buffer.\n");
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	/**
	 * End conditioned code.
	 */

	/* वापसs either a bo or surface */
	ret = vmw_user_lookup_handle(dev_priv, tfile,
				     mode_cmd->handles[0],
				     &surface, &bo);
	अगर (ret)
		जाओ err_out;


	अगर (!bo &&
	    !vmw_kms_srf_ok(dev_priv, mode_cmd->width, mode_cmd->height)) अणु
		DRM_ERROR("Surface size cannot exceed %dx%d",
			dev_priv->texture_max_width,
			dev_priv->texture_max_height);
		जाओ err_out;
	पूर्ण


	vfb = vmw_kms_new_framebuffer(dev_priv, bo, surface,
				      !(dev_priv->capabilities & SVGA_CAP_3D),
				      mode_cmd);
	अगर (IS_ERR(vfb)) अणु
		ret = PTR_ERR(vfb);
		जाओ err_out;
 	पूर्ण

err_out:
	/* vmw_user_lookup_handle takes one ref so करोes new_fb */
	अगर (bo)
		vmw_bo_unreference(&bo);
	अगर (surface)
		vmw_surface_unreference(&surface);

	अगर (ret) अणु
		DRM_ERROR("failed to create vmw_framebuffer: %i\n", ret);
		tपंचांग_base_object_unref(&user_obj);
		वापस ERR_PTR(ret);
	पूर्ण अन्यथा
		vfb->user_obj = user_obj;

	वापस &vfb->base;
पूर्ण

/**
 * vmw_kms_check_display_memory - Validates display memory required क्रम a
 * topology
 * @dev: DRM device
 * @num_rects: number of drm_rect in rects
 * @rects: array of drm_rect representing the topology to validate indexed by
 * crtc index.
 *
 * Returns:
 * 0 on success otherwise negative error code
 */
अटल पूर्णांक vmw_kms_check_display_memory(काष्ठा drm_device *dev,
					uपूर्णांक32_t num_rects,
					काष्ठा drm_rect *rects)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_rect bounding_box = अणु0पूर्ण;
	u64 total_pixels = 0, pixel_mem, bb_mem;
	पूर्णांक i;

	क्रम (i = 0; i < num_rects; i++) अणु
		/*
		 * For STDU only inभागidual screen (screen target) is limited by
		 * SCREENTARGET_MAX_WIDTH/HEIGHT रेजिस्टरs.
		 */
		अगर (dev_priv->active_display_unit == vmw_du_screen_target &&
		    (drm_rect_width(&rects[i]) > dev_priv->stdu_max_width ||
		     drm_rect_height(&rects[i]) > dev_priv->stdu_max_height)) अणु
			VMW_DEBUG_KMS("Screen size not supported.\n");
			वापस -EINVAL;
		पूर्ण

		/* Bounding box upper left is at (0,0). */
		अगर (rects[i].x2 > bounding_box.x2)
			bounding_box.x2 = rects[i].x2;

		अगर (rects[i].y2 > bounding_box.y2)
			bounding_box.y2 = rects[i].y2;

		total_pixels += (u64) drm_rect_width(&rects[i]) *
			(u64) drm_rect_height(&rects[i]);
	पूर्ण

	/* Virtual svga device primary limits are always in 32-bpp. */
	pixel_mem = total_pixels * 4;

	/*
	 * For HV10 and below prim_bb_mem is vram size. When
	 * SVGA_REG_MAX_PRIMARY_BOUNDING_BOX_MEM is not present vram size is
	 * limit on primary bounding box
	 */
	अगर (pixel_mem > dev_priv->prim_bb_mem) अणु
		VMW_DEBUG_KMS("Combined output size too large.\n");
		वापस -EINVAL;
	पूर्ण

	/* SVGA_CAP_NO_BB_RESTRICTION is available क्रम STDU only. */
	अगर (dev_priv->active_display_unit != vmw_du_screen_target ||
	    !(dev_priv->capabilities & SVGA_CAP_NO_BB_RESTRICTION)) अणु
		bb_mem = (u64) bounding_box.x2 * bounding_box.y2 * 4;

		अगर (bb_mem > dev_priv->prim_bb_mem) अणु
			VMW_DEBUG_KMS("Topology is beyond supported limits.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_crtc_state_and_lock - Return new or current crtc state with locked
 * crtc mutex
 * @state: The atomic state poपूर्णांकer containing the new atomic state
 * @crtc: The crtc
 *
 * This function वापसs the new crtc state अगर it's part of the state update.
 * Otherwise वापसs the current crtc state. It also makes sure that the
 * crtc mutex is locked.
 *
 * Returns: A valid crtc state poपूर्णांकer or शून्य. It may also वापस a
 * poपूर्णांकer error, in particular -EDEADLK अगर locking needs to be rerun.
 */
अटल काष्ठा drm_crtc_state *
vmw_crtc_state_and_lock(काष्ठा drm_atomic_state *state, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_crtc_state *crtc_state;

	crtc_state = drm_atomic_get_new_crtc_state(state, crtc);
	अगर (crtc_state) अणु
		lockdep_निश्चित_held(&crtc->mutex.mutex.base);
	पूर्ण अन्यथा अणु
		पूर्णांक ret = drm_modeset_lock(&crtc->mutex, state->acquire_ctx);

		अगर (ret != 0 && ret != -EALREADY)
			वापस ERR_PTR(ret);

		crtc_state = crtc->state;
	पूर्ण

	वापस crtc_state;
पूर्ण

/**
 * vmw_kms_check_implicit - Verअगरy that all implicit display units scan out
 * from the same fb after the new state is committed.
 * @dev: The drm_device.
 * @state: The new state to be checked.
 *
 * Returns:
 *   Zero on success,
 *   -EINVAL on invalid state,
 *   -EDEADLK अगर modeset locking needs to be rerun.
 */
अटल पूर्णांक vmw_kms_check_implicit(काष्ठा drm_device *dev,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_framebuffer *implicit_fb = शून्य;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_plane_state *plane_state;

	drm_क्रम_each_crtc(crtc, dev) अणु
		काष्ठा vmw_display_unit *du = vmw_crtc_to_du(crtc);

		अगर (!du->is_implicit)
			जारी;

		crtc_state = vmw_crtc_state_and_lock(state, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		अगर (!crtc_state || !crtc_state->enable)
			जारी;

		/*
		 * Can't move primary planes across crtcs, so this is OK.
		 * It also means we करोn't need to take the plane mutex.
		 */
		plane_state = du->primary.state;
		अगर (plane_state->crtc != crtc)
			जारी;

		अगर (!implicit_fb)
			implicit_fb = plane_state->fb;
		अन्यथा अगर (implicit_fb != plane_state->fb)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_kms_check_topology - Validates topology in drm_atomic_state
 * @dev: DRM device
 * @state: the driver state object
 *
 * Returns:
 * 0 on success otherwise negative error code
 */
अटल पूर्णांक vmw_kms_check_topology(काष्ठा drm_device *dev,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा drm_rect *rects;
	काष्ठा drm_crtc *crtc;
	uपूर्णांक32_t i;
	पूर्णांक ret = 0;

	rects = kसुस्मृति(dev->mode_config.num_crtc, माप(काष्ठा drm_rect),
			GFP_KERNEL);
	अगर (!rects)
		वापस -ENOMEM;

	drm_क्रम_each_crtc(crtc, dev) अणु
		काष्ठा vmw_display_unit *du = vmw_crtc_to_du(crtc);
		काष्ठा drm_crtc_state *crtc_state;

		i = drm_crtc_index(crtc);

		crtc_state = vmw_crtc_state_and_lock(state, crtc);
		अगर (IS_ERR(crtc_state)) अणु
			ret = PTR_ERR(crtc_state);
			जाओ clean;
		पूर्ण

		अगर (!crtc_state)
			जारी;

		अगर (crtc_state->enable) अणु
			rects[i].x1 = du->gui_x;
			rects[i].y1 = du->gui_y;
			rects[i].x2 = du->gui_x + crtc_state->mode.hdisplay;
			rects[i].y2 = du->gui_y + crtc_state->mode.vdisplay;
		पूर्ण अन्यथा अणु
			rects[i].x1 = 0;
			rects[i].y1 = 0;
			rects[i].x2 = 0;
			rects[i].y2 = 0;
		पूर्ण
	पूर्ण

	/* Determine change to topology due to new atomic state */
	क्रम_each_oldnew_crtc_in_state(state, crtc, old_crtc_state,
				      new_crtc_state, i) अणु
		काष्ठा vmw_display_unit *du = vmw_crtc_to_du(crtc);
		काष्ठा drm_connector *connector;
		काष्ठा drm_connector_state *conn_state;
		काष्ठा vmw_connector_state *vmw_conn_state;

		अगर (!du->pref_active && new_crtc_state->enable) अणु
			VMW_DEBUG_KMS("Enabling a disabled display unit\n");
			ret = -EINVAL;
			जाओ clean;
		पूर्ण

		/*
		 * For vmwgfx each crtc has only one connector attached and it
		 * is not changed so करोn't really need to check the
		 * crtc->connector_mask and iterate over it.
		 */
		connector = &du->connector;
		conn_state = drm_atomic_get_connector_state(state, connector);
		अगर (IS_ERR(conn_state)) अणु
			ret = PTR_ERR(conn_state);
			जाओ clean;
		पूर्ण

		vmw_conn_state = vmw_connector_state_to_vcs(conn_state);
		vmw_conn_state->gui_x = du->gui_x;
		vmw_conn_state->gui_y = du->gui_y;
	पूर्ण

	ret = vmw_kms_check_display_memory(dev, dev->mode_config.num_crtc,
					   rects);

clean:
	kमुक्त(rects);
	वापस ret;
पूर्ण

/**
 * vmw_kms_atomic_check_modeset- validate state object क्रम modeset changes
 *
 * @dev: DRM device
 * @state: the driver state object
 *
 * This is a simple wrapper around drm_atomic_helper_check_modeset() क्रम
 * us to assign a value to mode->crtc_घड़ी so that
 * drm_calc_बारtamping_स्थिरants() won't throw an error message
 *
 * Returns:
 * Zero क्रम success or -त्रुटि_सं
 */
अटल पूर्णांक
vmw_kms_atomic_check_modeset(काष्ठा drm_device *dev,
			     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *crtc_state;
	bool need_modeset = false;
	पूर्णांक i, ret;

	ret = drm_atomic_helper_check(dev, state);
	अगर (ret)
		वापस ret;

	ret = vmw_kms_check_implicit(dev, state);
	अगर (ret) अणु
		VMW_DEBUG_KMS("Invalid implicit state\n");
		वापस ret;
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		अगर (drm_atomic_crtc_needs_modeset(crtc_state))
			need_modeset = true;
	पूर्ण

	अगर (need_modeset)
		वापस vmw_kms_check_topology(dev, state);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs vmw_kms_funcs = अणु
	.fb_create = vmw_kms_fb_create,
	.atomic_check = vmw_kms_atomic_check_modeset,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक vmw_kms_generic_present(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा drm_file *file_priv,
				   काष्ठा vmw_framebuffer *vfb,
				   काष्ठा vmw_surface *surface,
				   uपूर्णांक32_t sid,
				   पूर्णांक32_t destX, पूर्णांक32_t destY,
				   काष्ठा drm_vmw_rect *clips,
				   uपूर्णांक32_t num_clips)
अणु
	वापस vmw_kms_sou_करो_surface_dirty(dev_priv, vfb, शून्य, clips,
					    &surface->res, destX, destY,
					    num_clips, 1, शून्य, शून्य);
पूर्ण


पूर्णांक vmw_kms_present(काष्ठा vmw_निजी *dev_priv,
		    काष्ठा drm_file *file_priv,
		    काष्ठा vmw_framebuffer *vfb,
		    काष्ठा vmw_surface *surface,
		    uपूर्णांक32_t sid,
		    पूर्णांक32_t destX, पूर्णांक32_t destY,
		    काष्ठा drm_vmw_rect *clips,
		    uपूर्णांक32_t num_clips)
अणु
	पूर्णांक ret;

	चयन (dev_priv->active_display_unit) अणु
	हाल vmw_du_screen_target:
		ret = vmw_kms_stdu_surface_dirty(dev_priv, vfb, शून्य, clips,
						 &surface->res, destX, destY,
						 num_clips, 1, शून्य, शून्य);
		अवरोध;
	हाल vmw_du_screen_object:
		ret = vmw_kms_generic_present(dev_priv, file_priv, vfb, surface,
					      sid, destX, destY, clips,
					      num_clips);
		अवरोध;
	शेष:
		WARN_ONCE(true,
			  "Present called with invalid display system.\n");
		ret = -ENOSYS;
		अवरोध;
	पूर्ण
	अगर (ret)
		वापस ret;

	vmw_cmd_flush(dev_priv, false);

	वापस 0;
पूर्ण

अटल व्योम
vmw_kms_create_hotplug_mode_update_property(काष्ठा vmw_निजी *dev_priv)
अणु
	अगर (dev_priv->hotplug_mode_update_property)
		वापस;

	dev_priv->hotplug_mode_update_property =
		drm_property_create_range(&dev_priv->drm,
					  DRM_MODE_PROP_IMMUTABLE,
					  "hotplug_mode_update", 0, 1);
पूर्ण

पूर्णांक vmw_kms_init(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक ret;

	drm_mode_config_init(dev);
	dev->mode_config.funcs = &vmw_kms_funcs;
	dev->mode_config.min_width = 1;
	dev->mode_config.min_height = 1;
	dev->mode_config.max_width = dev_priv->texture_max_width;
	dev->mode_config.max_height = dev_priv->texture_max_height;

	drm_mode_create_suggested_offset_properties(dev);
	vmw_kms_create_hotplug_mode_update_property(dev_priv);

	ret = vmw_kms_stdu_init_display(dev_priv);
	अगर (ret) अणु
		ret = vmw_kms_sou_init_display(dev_priv);
		अगर (ret) /* Fallback */
			ret = vmw_kms_ldu_init_display(dev_priv);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vmw_kms_बंद(काष्ठा vmw_निजी *dev_priv)
अणु
	पूर्णांक ret = 0;

	/*
	 * Docs says we should take the lock beक्रमe calling this function
	 * but since it destroys encoders and our deकाष्ठाor calls
	 * drm_encoder_cleanup which takes the lock we deadlock.
	 */
	drm_mode_config_cleanup(&dev_priv->drm);
	अगर (dev_priv->active_display_unit == vmw_du_legacy)
		ret = vmw_kms_ldu_बंद_display(dev_priv);

	वापस ret;
पूर्ण

पूर्णांक vmw_kms_cursor_bypass_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vmw_cursor_bypass_arg *arg = data;
	काष्ठा vmw_display_unit *du;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret = 0;


	mutex_lock(&dev->mode_config.mutex);
	अगर (arg->flags & DRM_VMW_CURSOR_BYPASS_ALL) अणु

		list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
			du = vmw_crtc_to_du(crtc);
			du->hotspot_x = arg->xhot;
			du->hotspot_y = arg->yhot;
		पूर्ण

		mutex_unlock(&dev->mode_config.mutex);
		वापस 0;
	पूर्ण

	crtc = drm_crtc_find(dev, file_priv, arg->crtc_id);
	अगर (!crtc) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	du = vmw_crtc_to_du(crtc);

	du->hotspot_x = arg->xhot;
	du->hotspot_y = arg->yhot;

out:
	mutex_unlock(&dev->mode_config.mutex);

	वापस ret;
पूर्ण

पूर्णांक vmw_kms_ग_लिखो_svga(काष्ठा vmw_निजी *vmw_priv,
			अचिन्हित width, अचिन्हित height, अचिन्हित pitch,
			अचिन्हित bpp, अचिन्हित depth)
अणु
	अगर (vmw_priv->capabilities & SVGA_CAP_PITCHLOCK)
		vmw_ग_लिखो(vmw_priv, SVGA_REG_PITCHLOCK, pitch);
	अन्यथा अगर (vmw_fअगरo_have_pitchlock(vmw_priv))
		vmw_fअगरo_mem_ग_लिखो(vmw_priv, SVGA_FIFO_PITCHLOCK, pitch);
	vmw_ग_लिखो(vmw_priv, SVGA_REG_WIDTH, width);
	vmw_ग_लिखो(vmw_priv, SVGA_REG_HEIGHT, height);
	अगर ((vmw_priv->capabilities & SVGA_CAP_8BIT_EMULATION) != 0)
		vmw_ग_लिखो(vmw_priv, SVGA_REG_BITS_PER_PIXEL, bpp);

	अगर (vmw_पढ़ो(vmw_priv, SVGA_REG_DEPTH) != depth) अणु
		DRM_ERROR("Invalid depth %u for %u bpp, host expects %u\n",
			  depth, bpp, vmw_पढ़ो(vmw_priv, SVGA_REG_DEPTH));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

bool vmw_kms_validate_mode_vram(काष्ठा vmw_निजी *dev_priv,
				uपूर्णांक32_t pitch,
				uपूर्णांक32_t height)
अणु
	वापस ((u64) pitch * (u64) height) < (u64)
		((dev_priv->active_display_unit == vmw_du_screen_target) ?
		 dev_priv->prim_bb_mem : dev_priv->vram_size);
पूर्ण


/*
 * Function called by DRM code called with vbl_lock held.
 */
u32 vmw_get_vblank_counter(काष्ठा drm_crtc *crtc)
अणु
	वापस 0;
पूर्ण

/*
 * Function called by DRM code called with vbl_lock held.
 */
पूर्णांक vmw_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	वापस -EINVAL;
पूर्ण

/*
 * Function called by DRM code called with vbl_lock held.
 */
व्योम vmw_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
पूर्ण

/**
 * vmw_du_update_layout - Update the display unit with topology from resolution
 * plugin and generate DRM uevent
 * @dev_priv: device निजी
 * @num_rects: number of drm_rect in rects
 * @rects: toplogy to update
 */
अटल पूर्णांक vmw_du_update_layout(काष्ठा vmw_निजी *dev_priv,
				अचिन्हित पूर्णांक num_rects, काष्ठा drm_rect *rects)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा vmw_display_unit *du;
	काष्ठा drm_connector *con;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret;

	/* Currently gui_x/y is रक्षित with the crtc mutex */
	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_acquire_init(&ctx, 0);
retry:
	drm_क्रम_each_crtc(crtc, dev) अणु
		ret = drm_modeset_lock(&crtc->mutex, &ctx);
		अगर (ret < 0) अणु
			अगर (ret == -EDEADLK) अणु
				drm_modeset_backoff(&ctx);
				जाओ retry;
      		पूर्ण
			जाओ out_fini;
		पूर्ण
	पूर्ण

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(con, &conn_iter) अणु
		du = vmw_connector_to_du(con);
		अगर (num_rects > du->unit) अणु
			du->pref_width = drm_rect_width(&rects[du->unit]);
			du->pref_height = drm_rect_height(&rects[du->unit]);
			du->pref_active = true;
			du->gui_x = rects[du->unit].x1;
			du->gui_y = rects[du->unit].y1;
		पूर्ण अन्यथा अणु
			du->pref_width = 800;
			du->pref_height = 600;
			du->pref_active = false;
			du->gui_x = 0;
			du->gui_y = 0;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	list_क्रम_each_entry(con, &dev->mode_config.connector_list, head) अणु
		du = vmw_connector_to_du(con);
		अगर (num_rects > du->unit) अणु
			drm_object_property_set_value
			  (&con->base, dev->mode_config.suggested_x_property,
			   du->gui_x);
			drm_object_property_set_value
			  (&con->base, dev->mode_config.suggested_y_property,
			   du->gui_y);
		पूर्ण अन्यथा अणु
			drm_object_property_set_value
			  (&con->base, dev->mode_config.suggested_x_property,
			   0);
			drm_object_property_set_value
			  (&con->base, dev->mode_config.suggested_y_property,
			   0);
		पूर्ण
		con->status = vmw_du_connector_detect(con, true);
	पूर्ण

	drm_sysfs_hotplug_event(dev);
out_fini:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
	mutex_unlock(&dev->mode_config.mutex);
 
	वापस 0;
पूर्ण

पूर्णांक vmw_du_crtc_gamma_set(काष्ठा drm_crtc *crtc,
			  u16 *r, u16 *g, u16 *b,
			  uपूर्णांक32_t size,
			  काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(crtc->dev);
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		DRM_DEBUG("%d r/g/b = 0x%04x / 0x%04x / 0x%04x\n", i,
			  r[i], g[i], b[i]);
		vmw_ग_लिखो(dev_priv, SVGA_PALETTE_BASE + i * 3 + 0, r[i] >> 8);
		vmw_ग_लिखो(dev_priv, SVGA_PALETTE_BASE + i * 3 + 1, g[i] >> 8);
		vmw_ग_लिखो(dev_priv, SVGA_PALETTE_BASE + i * 3 + 2, b[i] >> 8);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vmw_du_connector_dpms(काष्ठा drm_connector *connector, पूर्णांक mode)
अणु
	वापस 0;
पूर्ण

क्रमागत drm_connector_status
vmw_du_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	uपूर्णांक32_t num_displays;
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा vmw_display_unit *du = vmw_connector_to_du(connector);

	num_displays = vmw_पढ़ो(dev_priv, SVGA_REG_NUM_DISPLAYS);

	वापस ((vmw_connector_to_du(connector)->unit < num_displays &&
		 du->pref_active) ?
		connector_status_connected : connector_status_disconnected);
पूर्ण

अटल काष्ठा drm_display_mode vmw_kms_connector_builtin[] = अणु
	/* 640x480@60Hz */
	अणु DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 489, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 800x600@60Hz */
	अणु DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
		   968, 1056, 0, 600, 601, 605, 628, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1024x768@60Hz */
	अणु DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
		   1184, 1344, 0, 768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 1152x864@75Hz */
	अणु DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
		   1344, 1600, 0, 864, 865, 868, 900, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1280x720@60Hz */
	अणु DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74500, 1280, 1344,
		   1472, 1664, 0, 720, 723, 728, 748, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1280x768@60Hz */
	अणु DRM_MODE("1280x768", DRM_MODE_TYPE_DRIVER, 79500, 1280, 1344,
		   1472, 1664, 0, 768, 771, 778, 798, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1280x800@60Hz */
	अणु DRM_MODE("1280x800", DRM_MODE_TYPE_DRIVER, 83500, 1280, 1352,
		   1480, 1680, 0, 800, 803, 809, 831, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 1280x960@60Hz */
	अणु DRM_MODE("1280x960", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1376,
		   1488, 1800, 0, 960, 961, 964, 1000, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1280x1024@60Hz */
	अणु DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 108000, 1280, 1328,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1360x768@60Hz */
	अणु DRM_MODE("1360x768", DRM_MODE_TYPE_DRIVER, 85500, 1360, 1424,
		   1536, 1792, 0, 768, 771, 777, 795, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1440x1050@60Hz */
	अणु DRM_MODE("1400x1050", DRM_MODE_TYPE_DRIVER, 121750, 1400, 1488,
		   1632, 1864, 0, 1050, 1053, 1057, 1089, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1440x900@60Hz */
	अणु DRM_MODE("1440x900", DRM_MODE_TYPE_DRIVER, 106500, 1440, 1520,
		   1672, 1904, 0, 900, 903, 909, 934, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1600x1200@60Hz */
	अणु DRM_MODE("1600x1200", DRM_MODE_TYPE_DRIVER, 162000, 1600, 1664,
		   1856, 2160, 0, 1200, 1201, 1204, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1680x1050@60Hz */
	अणु DRM_MODE("1680x1050", DRM_MODE_TYPE_DRIVER, 146250, 1680, 1784,
		   1960, 2240, 0, 1050, 1053, 1059, 1089, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1792x1344@60Hz */
	अणु DRM_MODE("1792x1344", DRM_MODE_TYPE_DRIVER, 204750, 1792, 1920,
		   2120, 2448, 0, 1344, 1345, 1348, 1394, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1853x1392@60Hz */
	अणु DRM_MODE("1856x1392", DRM_MODE_TYPE_DRIVER, 218250, 1856, 1952,
		   2176, 2528, 0, 1392, 1393, 1396, 1439, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1920x1080@60Hz */
	अणु DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 173000, 1920, 2048,
		   2248, 2576, 0, 1080, 1083, 1088, 1120, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1920x1200@60Hz */
	अणु DRM_MODE("1920x1200", DRM_MODE_TYPE_DRIVER, 193250, 1920, 2056,
		   2256, 2592, 0, 1200, 1203, 1209, 1245, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 1920x1440@60Hz */
	अणु DRM_MODE("1920x1440", DRM_MODE_TYPE_DRIVER, 234000, 1920, 2048,
		   2256, 2600, 0, 1440, 1441, 1444, 1500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 2560x1440@60Hz */
	अणु DRM_MODE("2560x1440", DRM_MODE_TYPE_DRIVER, 241500, 2560, 2608,
		   2640, 2720, 0, 1440, 1443, 1448, 1481, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 2560x1600@60Hz */
	अणु DRM_MODE("2560x1600", DRM_MODE_TYPE_DRIVER, 348500, 2560, 2752,
		   3032, 3504, 0, 1600, 1603, 1609, 1658, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) पूर्ण,
	/* 2880x1800@60Hz */
	अणु DRM_MODE("2880x1800", DRM_MODE_TYPE_DRIVER, 337500, 2880, 2928,
		   2960, 3040, 0, 1800, 1803, 1809, 1852, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 3840x2160@60Hz */
	अणु DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 533000, 3840, 3888,
		   3920, 4000, 0, 2160, 2163, 2168, 2222, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* 3840x2400@60Hz */
	अणु DRM_MODE("3840x2400", DRM_MODE_TYPE_DRIVER, 592250, 3840, 3888,
		   3920, 4000, 0, 2400, 2403, 2409, 2469, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC) पूर्ण,
	/* Terminate */
	अणु DRM_MODE("", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) पूर्ण,
पूर्ण;

/**
 * vmw_guess_mode_timing - Provide fake timings क्रम a
 * 60Hz vrefresh mode.
 *
 * @mode: Poपूर्णांकer to a काष्ठा drm_display_mode with hdisplay and vdisplay
 * members filled in.
 */
व्योम vmw_guess_mode_timing(काष्ठा drm_display_mode *mode)
अणु
	mode->hsync_start = mode->hdisplay + 50;
	mode->hsync_end = mode->hsync_start + 50;
	mode->htotal = mode->hsync_end + 50;

	mode->vsync_start = mode->vdisplay + 50;
	mode->vsync_end = mode->vsync_start + 50;
	mode->vtotal = mode->vsync_end + 50;

	mode->घड़ी = (u32)mode->htotal * (u32)mode->vtotal / 100 * 6;
पूर्ण


पूर्णांक vmw_du_connector_fill_modes(काष्ठा drm_connector *connector,
				uपूर्णांक32_t max_width, uपूर्णांक32_t max_height)
अणु
	काष्ठा vmw_display_unit *du = vmw_connector_to_du(connector);
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_display_mode *bmode;
	काष्ठा drm_display_mode preभ_शेषe = अणु DRM_MODE("preferred",
		DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC)
	पूर्ण;
	पूर्णांक i;
	u32 assumed_bpp = 4;

	अगर (dev_priv->assume_16bpp)
		assumed_bpp = 2;

	max_width  = min(max_width,  dev_priv->texture_max_width);
	max_height = min(max_height, dev_priv->texture_max_height);

	/*
	 * For STDU extra limit क्रम a mode on SVGA_REG_SCREENTARGET_MAX_WIDTH/
	 * HEIGHT रेजिस्टरs.
	 */
	अगर (dev_priv->active_display_unit == vmw_du_screen_target) अणु
		max_width  = min(max_width,  dev_priv->stdu_max_width);
		max_height = min(max_height, dev_priv->stdu_max_height);
	पूर्ण

	/* Add preferred mode */
	mode = drm_mode_duplicate(dev, &preभ_शेषe);
	अगर (!mode)
		वापस 0;
	mode->hdisplay = du->pref_width;
	mode->vdisplay = du->pref_height;
	vmw_guess_mode_timing(mode);
	drm_mode_set_name(mode);

	अगर (vmw_kms_validate_mode_vram(dev_priv,
					mode->hdisplay * assumed_bpp,
					mode->vdisplay)) अणु
		drm_mode_probed_add(connector, mode);
	पूर्ण अन्यथा अणु
		drm_mode_destroy(dev, mode);
		mode = शून्य;
	पूर्ण

	अगर (du->pref_mode) अणु
		list_del_init(&du->pref_mode->head);
		drm_mode_destroy(dev, du->pref_mode);
	पूर्ण

	/* mode might be null here, this is पूर्णांकended */
	du->pref_mode = mode;

	क्रम (i = 0; vmw_kms_connector_builtin[i].type != 0; i++) अणु
		bmode = &vmw_kms_connector_builtin[i];
		अगर (bmode->hdisplay > max_width ||
		    bmode->vdisplay > max_height)
			जारी;

		अगर (!vmw_kms_validate_mode_vram(dev_priv,
						bmode->hdisplay * assumed_bpp,
						bmode->vdisplay))
			जारी;

		mode = drm_mode_duplicate(dev, bmode);
		अगर (!mode)
			वापस 0;

		drm_mode_probed_add(connector, mode);
	पूर्ण

	drm_connector_list_update(connector);
	/* Move the prefered mode first, help apps pick the right mode. */
	drm_mode_sort(&connector->modes);

	वापस 1;
पूर्ण

/**
 * vmw_kms_update_layout_ioctl - Handler क्रम DRM_VMW_UPDATE_LAYOUT ioctl
 * @dev: drm device क्रम the ioctl
 * @data: data poपूर्णांकer क्रम the ioctl
 * @file_priv: drm file क्रम the ioctl call
 *
 * Update preferred topology of display unit as per ioctl request. The topology
 * is expressed as array of drm_vmw_rect.
 * e.g.
 * [0 0 640 480] [640 0 800 600] [0 480 640 480]
 *
 * NOTE:
 * The x and y offset (upper left) in drm_vmw_rect cannot be less than 0. Beside
 * device limit on topology, x + w and y + h (lower right) cannot be greater
 * than पूर्णांक_उच्च. So topology beyond these limits will वापस with error.
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
पूर्णांक vmw_kms_update_layout_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_vmw_update_layout_arg *arg =
		(काष्ठा drm_vmw_update_layout_arg *)data;
	व्योम __user *user_rects;
	काष्ठा drm_vmw_rect *rects;
	काष्ठा drm_rect *drm_rects;
	अचिन्हित rects_size;
	पूर्णांक ret, i;

	अगर (!arg->num_outमाला_दो) अणु
		काष्ठा drm_rect def_rect = अणु0, 0, 800, 600पूर्ण;
		VMW_DEBUG_KMS("Default layout x1 = %d y1 = %d x2 = %d y2 = %d\n",
			      def_rect.x1, def_rect.y1,
			      def_rect.x2, def_rect.y2);
		vmw_du_update_layout(dev_priv, 1, &def_rect);
		वापस 0;
	पूर्ण

	rects_size = arg->num_outमाला_दो * माप(काष्ठा drm_vmw_rect);
	rects = kसुस्मृति(arg->num_outमाला_दो, माप(काष्ठा drm_vmw_rect),
			GFP_KERNEL);
	अगर (unlikely(!rects))
		वापस -ENOMEM;

	user_rects = (व्योम __user *)(अचिन्हित दीर्घ)arg->rects;
	ret = copy_from_user(rects, user_rects, rects_size);
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed to get rects.\n");
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	drm_rects = (काष्ठा drm_rect *)rects;

	VMW_DEBUG_KMS("Layout count = %u\n", arg->num_outमाला_दो);
	क्रम (i = 0; i < arg->num_outमाला_दो; i++) अणु
		काष्ठा drm_vmw_rect curr_rect;

		/* Verअगरy user-space क्रम overflow as kernel use drm_rect */
		अगर ((rects[i].x + rects[i].w > पूर्णांक_उच्च) ||
		    (rects[i].y + rects[i].h > पूर्णांक_उच्च)) अणु
			ret = -दुस्फल;
			जाओ out_मुक्त;
		पूर्ण

		curr_rect = rects[i];
		drm_rects[i].x1 = curr_rect.x;
		drm_rects[i].y1 = curr_rect.y;
		drm_rects[i].x2 = curr_rect.x + curr_rect.w;
		drm_rects[i].y2 = curr_rect.y + curr_rect.h;

		VMW_DEBUG_KMS("  x1 = %d y1 = %d x2 = %d y2 = %d\n",
			      drm_rects[i].x1, drm_rects[i].y1,
			      drm_rects[i].x2, drm_rects[i].y2);

		/*
		 * Currently this check is limiting the topology within
		 * mode_config->max (which actually is max texture size
		 * supported by भव device). This limit is here to address
		 * winकरोw managers that create a big framebuffer क्रम whole
		 * topology.
		 */
		अगर (drm_rects[i].x1 < 0 ||  drm_rects[i].y1 < 0 ||
		    drm_rects[i].x2 > mode_config->max_width ||
		    drm_rects[i].y2 > mode_config->max_height) अणु
			VMW_DEBUG_KMS("Invalid layout %d %d %d %d\n",
				      drm_rects[i].x1, drm_rects[i].y1,
				      drm_rects[i].x2, drm_rects[i].y2);
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	ret = vmw_kms_check_display_memory(dev, arg->num_outमाला_दो, drm_rects);

	अगर (ret == 0)
		vmw_du_update_layout(dev_priv, arg->num_outमाला_दो, drm_rects);

out_मुक्त:
	kमुक्त(rects);
	वापस ret;
पूर्ण

/**
 * vmw_kms_helper_dirty - Helper to build commands and perक्रमm actions based
 * on a set of cliprects and a set of display units.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठाure.
 * @framebuffer: Poपूर्णांकer to the framebuffer on which to perक्रमm the actions.
 * @clips: A set of काष्ठा drm_clip_rect. Either this os @vclips must be शून्य.
 * Cliprects are given in framebuffer coordinates.
 * @vclips: A set of काष्ठा drm_vmw_rect cliprects. Either this or @clips must
 * be शून्य. Cliprects are given in source coordinates.
 * @dest_x: X coordinate offset क्रम the crtc / destination clip rects.
 * @dest_y: Y coordinate offset क्रम the crtc / destination clip rects.
 * @num_clips: Number of cliprects in the @clips or @vclips array.
 * @increment: Integer with which to increment the clip counter when looping.
 * Used to skip a predetermined number of clip rects.
 * @dirty: Closure काष्ठाure. See the description of काष्ठा vmw_kms_dirty.
 */
पूर्णांक vmw_kms_helper_dirty(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा vmw_framebuffer *framebuffer,
			 स्थिर काष्ठा drm_clip_rect *clips,
			 स्थिर काष्ठा drm_vmw_rect *vclips,
			 s32 dest_x, s32 dest_y,
			 पूर्णांक num_clips,
			 पूर्णांक increment,
			 काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_display_unit *units[VMWGFX_NUM_DISPLAY_UNITS];
	काष्ठा drm_crtc *crtc;
	u32 num_units = 0;
	u32 i, k;

	dirty->dev_priv = dev_priv;

	/* If crtc is passed, no need to iterate over other display units */
	अगर (dirty->crtc) अणु
		units[num_units++] = vmw_crtc_to_du(dirty->crtc);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(crtc, &dev_priv->drm.mode_config.crtc_list,
				    head) अणु
			काष्ठा drm_plane *plane = crtc->primary;

			अगर (plane->state->fb == &framebuffer->base)
				units[num_units++] = vmw_crtc_to_du(crtc);
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < num_units; k++) अणु
		काष्ठा vmw_display_unit *unit = units[k];
		s32 crtc_x = unit->crtc.x;
		s32 crtc_y = unit->crtc.y;
		s32 crtc_width = unit->crtc.mode.hdisplay;
		s32 crtc_height = unit->crtc.mode.vdisplay;
		स्थिर काष्ठा drm_clip_rect *clips_ptr = clips;
		स्थिर काष्ठा drm_vmw_rect *vclips_ptr = vclips;

		dirty->unit = unit;
		अगर (dirty->fअगरo_reserve_size > 0) अणु
			dirty->cmd = VMW_CMD_RESERVE(dev_priv,
						      dirty->fअगरo_reserve_size);
			अगर (!dirty->cmd)
				वापस -ENOMEM;

			स_रखो(dirty->cmd, 0, dirty->fअगरo_reserve_size);
		पूर्ण
		dirty->num_hits = 0;
		क्रम (i = 0; i < num_clips; i++, clips_ptr += increment,
		       vclips_ptr += increment) अणु
			s32 clip_left;
			s32 clip_top;

			/*
			 * Select clip array type. Note that पूर्णांकeger type
			 * in @clips is अचिन्हित लघु, whereas in @vclips
			 * it's 32-bit.
			 */
			अगर (clips) अणु
				dirty->fb_x = (s32) clips_ptr->x1;
				dirty->fb_y = (s32) clips_ptr->y1;
				dirty->unit_x2 = (s32) clips_ptr->x2 + dest_x -
					crtc_x;
				dirty->unit_y2 = (s32) clips_ptr->y2 + dest_y -
					crtc_y;
			पूर्ण अन्यथा अणु
				dirty->fb_x = vclips_ptr->x;
				dirty->fb_y = vclips_ptr->y;
				dirty->unit_x2 = dirty->fb_x + vclips_ptr->w +
					dest_x - crtc_x;
				dirty->unit_y2 = dirty->fb_y + vclips_ptr->h +
					dest_y - crtc_y;
			पूर्ण

			dirty->unit_x1 = dirty->fb_x + dest_x - crtc_x;
			dirty->unit_y1 = dirty->fb_y + dest_y - crtc_y;

			/* Skip this clip अगर it's outside the crtc region */
			अगर (dirty->unit_x1 >= crtc_width ||
			    dirty->unit_y1 >= crtc_height ||
			    dirty->unit_x2 <= 0 || dirty->unit_y2 <= 0)
				जारी;

			/* Clip right and bottom to crtc limits */
			dirty->unit_x2 = min_t(s32, dirty->unit_x2,
					       crtc_width);
			dirty->unit_y2 = min_t(s32, dirty->unit_y2,
					       crtc_height);

			/* Clip left and top to crtc limits */
			clip_left = min_t(s32, dirty->unit_x1, 0);
			clip_top = min_t(s32, dirty->unit_y1, 0);
			dirty->unit_x1 -= clip_left;
			dirty->unit_y1 -= clip_top;
			dirty->fb_x -= clip_left;
			dirty->fb_y -= clip_top;

			dirty->clip(dirty);
		पूर्ण

		dirty->fअगरo_commit(dirty);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_kms_helper_validation_finish - Helper क्रम post KMS command submission
 * cleanup and fencing
 * @dev_priv: Poपूर्णांकer to the device-निजी काष्ठा
 * @file_priv: Poपूर्णांकer identअगरying the client when user-space fencing is used
 * @ctx: Poपूर्णांकer to the validation context
 * @out_fence: If non-शून्य, वापसed refcounted fence-poपूर्णांकer
 * @user_fence_rep: If non-शून्य, poपूर्णांकer to user-space address area
 * in which to copy user-space fence info
 */
व्योम vmw_kms_helper_validation_finish(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा drm_file *file_priv,
				      काष्ठा vmw_validation_context *ctx,
				      काष्ठा vmw_fence_obj **out_fence,
				      काष्ठा drm_vmw_fence_rep __user *
				      user_fence_rep)
अणु
	काष्ठा vmw_fence_obj *fence = शून्य;
	uपूर्णांक32_t handle = 0;
	पूर्णांक ret = 0;

	अगर (file_priv || user_fence_rep || vmw_validation_has_bos(ctx) ||
	    out_fence)
		ret = vmw_execbuf_fence_commands(file_priv, dev_priv, &fence,
						 file_priv ? &handle : शून्य);
	vmw_validation_करोne(ctx, fence);
	अगर (file_priv)
		vmw_execbuf_copy_fence_user(dev_priv, vmw_fpriv(file_priv),
					    ret, user_fence_rep, fence,
					    handle, -1, शून्य);
	अगर (out_fence)
		*out_fence = fence;
	अन्यथा
		vmw_fence_obj_unreference(&fence);
पूर्ण

/**
 * vmw_kms_update_proxy - Helper function to update a proxy surface from
 * its backing MOB.
 *
 * @res: Poपूर्णांकer to the surface resource
 * @clips: Clip rects in framebuffer (surface) space.
 * @num_clips: Number of clips in @clips.
 * @increment: Integer with which to increment the clip counter when looping.
 * Used to skip a predetermined number of clip rects.
 *
 * This function makes sure the proxy surface is updated from its backing MOB
 * using the region given by @clips. The surface resource @res and its backing
 * MOB needs to be reserved and validated on call.
 */
पूर्णांक vmw_kms_update_proxy(काष्ठा vmw_resource *res,
			 स्थिर काष्ठा drm_clip_rect *clips,
			 अचिन्हित num_clips,
			 पूर्णांक increment)
अणु
	काष्ठा vmw_निजी *dev_priv = res->dev_priv;
	काष्ठा drm_vmw_size *size = &vmw_res_to_srf(res)->metadata.base_size;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdUpdateGBImage body;
	पूर्ण *cmd;
	SVGA3dBox *box;
	माप_प्रकार copy_size = 0;
	पूर्णांक i;

	अगर (!clips)
		वापस 0;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd) * num_clips);
	अगर (!cmd)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_clips; ++i, clips += increment, ++cmd) अणु
		box = &cmd->body.box;

		cmd->header.id = SVGA_3D_CMD_UPDATE_GB_IMAGE;
		cmd->header.size = माप(cmd->body);
		cmd->body.image.sid = res->id;
		cmd->body.image.face = 0;
		cmd->body.image.mipmap = 0;

		अगर (clips->x1 > size->width || clips->x2 > size->width ||
		    clips->y1 > size->height || clips->y2 > size->height) अणु
			DRM_ERROR("Invalid clips outsize of framebuffer.\n");
			वापस -EINVAL;
		पूर्ण

		box->x = clips->x1;
		box->y = clips->y1;
		box->z = 0;
		box->w = clips->x2 - clips->x1;
		box->h = clips->y2 - clips->y1;
		box->d = 1;

		copy_size += माप(*cmd);
	पूर्ण

	vmw_cmd_commit(dev_priv, copy_size);

	वापस 0;
पूर्ण

पूर्णांक vmw_kms_fbdev_init_data(काष्ठा vmw_निजी *dev_priv,
			    अचिन्हित unit,
			    u32 max_width,
			    u32 max_height,
			    काष्ठा drm_connector **p_con,
			    काष्ठा drm_crtc **p_crtc,
			    काष्ठा drm_display_mode **p_mode)
अणु
	काष्ठा drm_connector *con;
	काष्ठा vmw_display_unit *du;
	काष्ठा drm_display_mode *mode;
	पूर्णांक i = 0;
	पूर्णांक ret = 0;

	mutex_lock(&dev_priv->drm.mode_config.mutex);
	list_क्रम_each_entry(con, &dev_priv->drm.mode_config.connector_list,
			    head) अणु
		अगर (i == unit)
			अवरोध;

		++i;
	पूर्ण

	अगर (&con->head == &dev_priv->drm.mode_config.connector_list) अणु
		DRM_ERROR("Could not find initial display unit.\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (list_empty(&con->modes))
		(व्योम) vmw_du_connector_fill_modes(con, max_width, max_height);

	अगर (list_empty(&con->modes)) अणु
		DRM_ERROR("Could not find initial display mode.\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	du = vmw_connector_to_du(con);
	*p_con = con;
	*p_crtc = &du->crtc;

	list_क्रम_each_entry(mode, &con->modes, head) अणु
		अगर (mode->type & DRM_MODE_TYPE_PREFERRED)
			अवरोध;
	पूर्ण

	अगर (&mode->head == &con->modes) अणु
		WARN_ONCE(true, "Could not find initial preferred mode.\n");
		*p_mode = list_first_entry(&con->modes,
					   काष्ठा drm_display_mode,
					   head);
	पूर्ण अन्यथा अणु
		*p_mode = mode;
	पूर्ण

 out_unlock:
	mutex_unlock(&dev_priv->drm.mode_config.mutex);

	वापस ret;
पूर्ण

/**
 * vmw_kms_create_implicit_placement_proparty - Set up the implicit placement
 * property.
 *
 * @dev_priv: Poपूर्णांकer to a device निजी काष्ठा.
 *
 * Sets up the implicit placement property unless it's alपढ़ोy set up.
 */
व्योम
vmw_kms_create_implicit_placement_property(काष्ठा vmw_निजी *dev_priv)
अणु
	अगर (dev_priv->implicit_placement_property)
		वापस;

	dev_priv->implicit_placement_property =
		drm_property_create_range(&dev_priv->drm,
					  DRM_MODE_PROP_IMMUTABLE,
					  "implicit_placement", 0, 1);
पूर्ण

/**
 * vmw_kms_suspend - Save modesetting state and turn modesetting off.
 *
 * @dev: Poपूर्णांकer to the drm device
 * Return: 0 on success. Negative error code on failure.
 */
पूर्णांक vmw_kms_suspend(काष्ठा drm_device *dev)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);

	dev_priv->suspend_state = drm_atomic_helper_suspend(dev);
	अगर (IS_ERR(dev_priv->suspend_state)) अणु
		पूर्णांक ret = PTR_ERR(dev_priv->suspend_state);

		DRM_ERROR("Failed kms suspend: %d\n", ret);
		dev_priv->suspend_state = शून्य;

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * vmw_kms_resume - Re-enable modesetting and restore state
 *
 * @dev: Poपूर्णांकer to the drm device
 * Return: 0 on success. Negative error code on failure.
 *
 * State is resumed from a previous vmw_kms_suspend(). It's illegal
 * to call this function without a previous vmw_kms_suspend().
 */
पूर्णांक vmw_kms_resume(काष्ठा drm_device *dev)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(dev);
	पूर्णांक ret;

	अगर (WARN_ON(!dev_priv->suspend_state))
		वापस 0;

	ret = drm_atomic_helper_resume(dev, dev_priv->suspend_state);
	dev_priv->suspend_state = शून्य;

	वापस ret;
पूर्ण

/**
 * vmw_kms_lost_device - Notअगरy kms that modesetting capabilities will be lost
 *
 * @dev: Poपूर्णांकer to the drm device
 */
व्योम vmw_kms_lost_device(काष्ठा drm_device *dev)
अणु
	drm_atomic_helper_shutकरोwn(dev);
पूर्ण

/**
 * vmw_du_helper_plane_update - Helper to करो plane update on a display unit.
 * @update: The closure काष्ठाure.
 *
 * Call this helper after setting callbacks in &vmw_du_update_plane to करो plane
 * update on display unit.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक vmw_du_helper_plane_update(काष्ठा vmw_du_update_plane *update)
अणु
	काष्ठा drm_plane_state *state = update->plane->state;
	काष्ठा drm_plane_state *old_state = update->old_state;
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_rect clip;
	काष्ठा drm_rect bb;
	DECLARE_VAL_CONTEXT(val_ctx, शून्य, 0);
	uपूर्णांक32_t reserved_size = 0;
	uपूर्णांक32_t submit_size = 0;
	uपूर्णांक32_t curr_size = 0;
	uपूर्णांक32_t num_hits = 0;
	व्योम *cmd_start;
	अक्षर *cmd_next;
	पूर्णांक ret;

	/*
	 * Iterate in advance to check अगर really need plane update and find the
	 * number of clips that actually are in plane src क्रम fअगरo allocation.
	 */
	drm_atomic_helper_damage_iter_init(&iter, old_state, state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip)
		num_hits++;

	अगर (num_hits == 0)
		वापस 0;

	अगर (update->vfb->bo) अणु
		काष्ठा vmw_framebuffer_bo *vfbbo =
			container_of(update->vfb, typeof(*vfbbo), base);

		ret = vmw_validation_add_bo(&val_ctx, vfbbo->buffer, false,
					    update->cpu_blit);
	पूर्ण अन्यथा अणु
		काष्ठा vmw_framebuffer_surface *vfbs =
			container_of(update->vfb, typeof(*vfbs), base);

		ret = vmw_validation_add_resource(&val_ctx, &vfbs->surface->res,
						  0, VMW_RES_सूचीTY_NONE, शून्य,
						  शून्य);
	पूर्ण

	अगर (ret)
		वापस ret;

	ret = vmw_validation_prepare(&val_ctx, update->mutex, update->पूर्णांकr);
	अगर (ret)
		जाओ out_unref;

	reserved_size = update->calc_fअगरo_size(update, num_hits);
	cmd_start = VMW_CMD_RESERVE(update->dev_priv, reserved_size);
	अगर (!cmd_start) अणु
		ret = -ENOMEM;
		जाओ out_revert;
	पूर्ण

	cmd_next = cmd_start;

	अगर (update->post_prepare) अणु
		curr_size = update->post_prepare(update, cmd_next);
		cmd_next += curr_size;
		submit_size += curr_size;
	पूर्ण

	अगर (update->pre_clip) अणु
		curr_size = update->pre_clip(update, cmd_next, num_hits);
		cmd_next += curr_size;
		submit_size += curr_size;
	पूर्ण

	bb.x1 = पूर्णांक_उच्च;
	bb.y1 = पूर्णांक_उच्च;
	bb.x2 = पूर्णांक_न्यून;
	bb.y2 = पूर्णांक_न्यून;

	drm_atomic_helper_damage_iter_init(&iter, old_state, state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip) अणु
		uपूर्णांक32_t fb_x = clip.x1;
		uपूर्णांक32_t fb_y = clip.y1;

		vmw_du_translate_to_crtc(state, &clip);
		अगर (update->clip) अणु
			curr_size = update->clip(update, cmd_next, &clip, fb_x,
						 fb_y);
			cmd_next += curr_size;
			submit_size += curr_size;
		पूर्ण
		bb.x1 = min_t(पूर्णांक, bb.x1, clip.x1);
		bb.y1 = min_t(पूर्णांक, bb.y1, clip.y1);
		bb.x2 = max_t(पूर्णांक, bb.x2, clip.x2);
		bb.y2 = max_t(पूर्णांक, bb.y2, clip.y2);
	पूर्ण

	curr_size = update->post_clip(update, cmd_next, &bb);
	submit_size += curr_size;

	अगर (reserved_size < submit_size)
		submit_size = 0;

	vmw_cmd_commit(update->dev_priv, submit_size);

	vmw_kms_helper_validation_finish(update->dev_priv, शून्य, &val_ctx,
					 update->out_fence, शून्य);
	वापस ret;

out_revert:
	vmw_validation_revert(&val_ctx);

out_unref:
	vmw_validation_unref_lists(&val_ctx);
	वापस ret;
पूर्ण
