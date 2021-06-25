<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2011-2015 VMware, Inc., Palo Alto, CA., USA
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
#समावेश <drm/drm_vblank.h>

#समावेश "vmwgfx_kms.h"

#घोषणा vmw_crtc_to_sou(x) \
	container_of(x, काष्ठा vmw_screen_object_unit, base.crtc)
#घोषणा vmw_encoder_to_sou(x) \
	container_of(x, काष्ठा vmw_screen_object_unit, base.encoder)
#घोषणा vmw_connector_to_sou(x) \
	container_of(x, काष्ठा vmw_screen_object_unit, base.connector)

/**
 * काष्ठा vmw_kms_sou_surface_dirty - Closure काष्ठाure क्रम
 * blit surface to screen command.
 * @base: The base type we derive from. Used by vmw_kms_helper_dirty().
 * @left: Left side of bounding box.
 * @right: Right side of bounding box.
 * @top: Top side of bounding box.
 * @bottom: Bottom side of bounding box.
 * @dst_x: Dअगरference between source clip rects and framebuffer coordinates.
 * @dst_y: Dअगरference between source clip rects and framebuffer coordinates.
 * @sid: Surface id of surface to copy from.
 */
काष्ठा vmw_kms_sou_surface_dirty अणु
	काष्ठा vmw_kms_dirty base;
	s32 left, right, top, bottom;
	s32 dst_x, dst_y;
	u32 sid;
पूर्ण;

/*
 * SVGA commands that are used by this code. Please see the device headers
 * क्रम explanation.
 */
काष्ठा vmw_kms_sou_पढ़ोback_blit अणु
	uपूर्णांक32 header;
	SVGAFअगरoCmdBlitScreenToGMRFB body;
पूर्ण;

काष्ठा vmw_kms_sou_bo_blit अणु
	uपूर्णांक32 header;
	SVGAFअगरoCmdBlitGMRFBToScreen body;
पूर्ण;

काष्ठा vmw_kms_sou_dirty_cmd अणु
	SVGA3dCmdHeader header;
	SVGA3dCmdBlitSurfaceToScreen body;
पूर्ण;

काष्ठा vmw_kms_sou_define_gmrfb अणु
	uपूर्णांक32_t header;
	SVGAFअगरoCmdDefineGMRFB body;
पूर्ण;

/*
 * Display unit using screen objects.
 */
काष्ठा vmw_screen_object_unit अणु
	काष्ठा vmw_display_unit base;

	अचिन्हित दीर्घ buffer_size; /**< Size of allocated buffer */
	काष्ठा vmw_buffer_object *buffer; /**< Backing store buffer */

	bool defined;
पूर्ण;

अटल व्योम vmw_sou_destroy(काष्ठा vmw_screen_object_unit *sou)
अणु
	vmw_du_cleanup(&sou->base);
	kमुक्त(sou);
पूर्ण


/*
 * Screen Object Display Unit CRTC functions
 */

अटल व्योम vmw_sou_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	vmw_sou_destroy(vmw_crtc_to_sou(crtc));
पूर्ण

/*
 * Send the fअगरo command to create a screen.
 */
अटल पूर्णांक vmw_sou_fअगरo_create(काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_screen_object_unit *sou,
			       पूर्णांक x, पूर्णांक y,
			       काष्ठा drm_display_mode *mode)
अणु
	माप_प्रकार fअगरo_size;

	काष्ठा अणु
		काष्ठा अणु
			uपूर्णांक32_t cmdType;
		पूर्ण header;
		SVGAScreenObject obj;
	पूर्ण *cmd;

	BUG_ON(!sou->buffer);

	fअगरo_size = माप(*cmd);
	cmd = VMW_CMD_RESERVE(dev_priv, fअगरo_size);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	स_रखो(cmd, 0, fअगरo_size);
	cmd->header.cmdType = SVGA_CMD_DEFINE_SCREEN;
	cmd->obj.काष्ठाSize = माप(SVGAScreenObject);
	cmd->obj.id = sou->base.unit;
	cmd->obj.flags = SVGA_SCREEN_HAS_ROOT |
		(sou->base.unit == 0 ? SVGA_SCREEN_IS_PRIMARY : 0);
	cmd->obj.size.width = mode->hdisplay;
	cmd->obj.size.height = mode->vdisplay;
	cmd->obj.root.x = x;
	cmd->obj.root.y = y;
	sou->base.set_gui_x = cmd->obj.root.x;
	sou->base.set_gui_y = cmd->obj.root.y;

	/* Ok to assume that buffer is pinned in vram */
	vmw_bo_get_guest_ptr(&sou->buffer->base, &cmd->obj.backingStore.ptr);
	cmd->obj.backingStore.pitch = mode->hdisplay * 4;

	vmw_cmd_commit(dev_priv, fअगरo_size);

	sou->defined = true;

	वापस 0;
पूर्ण

/*
 * Send the fअगरo command to destroy a screen.
 */
अटल पूर्णांक vmw_sou_fअगरo_destroy(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_screen_object_unit *sou)
अणु
	माप_प्रकार fअगरo_size;
	पूर्णांक ret;

	काष्ठा अणु
		काष्ठा अणु
			uपूर्णांक32_t cmdType;
		पूर्ण header;
		SVGAFअगरoCmdDestroyScreen body;
	पूर्ण *cmd;

	/* no need to करो anything */
	अगर (unlikely(!sou->defined))
		वापस 0;

	fअगरo_size = माप(*cmd);
	cmd = VMW_CMD_RESERVE(dev_priv, fअगरo_size);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	स_रखो(cmd, 0, fअगरo_size);
	cmd->header.cmdType = SVGA_CMD_DESTROY_SCREEN;
	cmd->body.screenId = sou->base.unit;

	vmw_cmd_commit(dev_priv, fअगरo_size);

	/* Force sync */
	ret = vmw_fallback_रुको(dev_priv, false, true, 0, false, 3*HZ);
	अगर (unlikely(ret != 0))
		DRM_ERROR("Failed to sync with HW");
	अन्यथा
		sou->defined = false;

	वापस ret;
पूर्ण

/**
 * vmw_sou_crtc_mode_set_nofb - Create new screen
 *
 * @crtc: CRTC associated with the new screen
 *
 * This function creates/destroys a screen.  This function cannot fail, so अगर
 * somehow we run पूर्णांकo a failure, just करो the best we can to get out.
 */
अटल व्योम vmw_sou_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_screen_object_unit *sou;
	काष्ठा vmw_framebuffer *vfb;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_plane_state *ps;
	काष्ठा vmw_plane_state *vps;
	पूर्णांक ret;

	sou = vmw_crtc_to_sou(crtc);
	dev_priv = vmw_priv(crtc->dev);
	ps = crtc->primary->state;
	fb = ps->fb;
	vps = vmw_plane_state_to_vps(ps);

	vfb = (fb) ? vmw_framebuffer_to_vfb(fb) : शून्य;

	अगर (sou->defined) अणु
		ret = vmw_sou_fअगरo_destroy(dev_priv, sou);
		अगर (ret) अणु
			DRM_ERROR("Failed to destroy Screen Object\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (vfb) अणु
		काष्ठा drm_connector_state *conn_state;
		काष्ठा vmw_connector_state *vmw_conn_state;
		पूर्णांक x, y;

		sou->buffer = vps->bo;
		sou->buffer_size = vps->bo_size;

		conn_state = sou->base.connector.state;
		vmw_conn_state = vmw_connector_state_to_vcs(conn_state);

		x = vmw_conn_state->gui_x;
		y = vmw_conn_state->gui_y;

		ret = vmw_sou_fअगरo_create(dev_priv, sou, x, y, &crtc->mode);
		अगर (ret)
			DRM_ERROR("Failed to define Screen Object %dx%d\n",
				  crtc->x, crtc->y);

	पूर्ण अन्यथा अणु
		sou->buffer = शून्य;
		sou->buffer_size = 0;
	पूर्ण
पूर्ण

/**
 * vmw_sou_crtc_helper_prepare - Noop
 *
 * @crtc:  CRTC associated with the new screen
 *
 * Prepares the CRTC क्रम a mode set, but we करोn't need to करो anything here.
 */
अटल व्योम vmw_sou_crtc_helper_prepare(काष्ठा drm_crtc *crtc)
अणु
पूर्ण

/**
 * vmw_sou_crtc_atomic_enable - Noop
 *
 * @crtc: CRTC associated with the new screen
 * @state: Unused
 *
 * This is called after a mode set has been completed.
 */
अटल व्योम vmw_sou_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
पूर्ण

/**
 * vmw_sou_crtc_atomic_disable - Turns off CRTC
 *
 * @crtc: CRTC to be turned off
 * @state: Unused
 */
अटल व्योम vmw_sou_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_screen_object_unit *sou;
	पूर्णांक ret;


	अगर (!crtc) अणु
		DRM_ERROR("CRTC is NULL\n");
		वापस;
	पूर्ण

	sou = vmw_crtc_to_sou(crtc);
	dev_priv = vmw_priv(crtc->dev);

	अगर (sou->defined) अणु
		ret = vmw_sou_fअगरo_destroy(dev_priv, sou);
		अगर (ret)
			DRM_ERROR("Failed to destroy Screen Object\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs vmw_screen_object_crtc_funcs = अणु
	.gamma_set = vmw_du_crtc_gamma_set,
	.destroy = vmw_sou_crtc_destroy,
	.reset = vmw_du_crtc_reset,
	.atomic_duplicate_state = vmw_du_crtc_duplicate_state,
	.atomic_destroy_state = vmw_du_crtc_destroy_state,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.get_vblank_counter = vmw_get_vblank_counter,
	.enable_vblank = vmw_enable_vblank,
	.disable_vblank = vmw_disable_vblank,
पूर्ण;

/*
 * Screen Object Display Unit encoder functions
 */

अटल व्योम vmw_sou_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	vmw_sou_destroy(vmw_encoder_to_sou(encoder));
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs vmw_screen_object_encoder_funcs = अणु
	.destroy = vmw_sou_encoder_destroy,
पूर्ण;

/*
 * Screen Object Display Unit connector functions
 */

अटल व्योम vmw_sou_connector_destroy(काष्ठा drm_connector *connector)
अणु
	vmw_sou_destroy(vmw_connector_to_sou(connector));
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs vmw_sou_connector_funcs = अणु
	.dpms = vmw_du_connector_dpms,
	.detect = vmw_du_connector_detect,
	.fill_modes = vmw_du_connector_fill_modes,
	.destroy = vmw_sou_connector_destroy,
	.reset = vmw_du_connector_reset,
	.atomic_duplicate_state = vmw_du_connector_duplicate_state,
	.atomic_destroy_state = vmw_du_connector_destroy_state,
पूर्ण;


अटल स्थिर काष्ठा
drm_connector_helper_funcs vmw_sou_connector_helper_funcs = अणु
पूर्ण;



/*
 * Screen Object Display Plane Functions
 */

/**
 * vmw_sou_primary_plane_cleanup_fb - Frees sou backing buffer
 *
 * @plane:  display plane
 * @old_state: Contains the FB to clean up
 *
 * Unpins the display surface
 *
 * Returns 0 on success
 */
अटल व्योम
vmw_sou_primary_plane_cleanup_fb(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(old_state);
	काष्ठा drm_crtc *crtc = plane->state->crtc ?
		plane->state->crtc : old_state->crtc;

	अगर (vps->bo)
		vmw_bo_unpin(vmw_priv(crtc->dev), vps->bo, false);
	vmw_bo_unreference(&vps->bo);
	vps->bo_size = 0;

	vmw_du_plane_cleanup_fb(plane, old_state);
पूर्ण


/**
 * vmw_sou_primary_plane_prepare_fb - allocate backing buffer
 *
 * @plane:  display plane
 * @new_state: info on the new plane state, including the FB
 *
 * The SOU backing buffer is our equivalent of the display plane.
 *
 * Returns 0 on success
 */
अटल पूर्णांक
vmw_sou_primary_plane_prepare_fb(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा drm_framebuffer *new_fb = new_state->fb;
	काष्ठा drm_crtc *crtc = plane->state->crtc ?: new_state->crtc;
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(new_state);
	काष्ठा vmw_निजी *dev_priv;
	माप_प्रकार size;
	पूर्णांक ret;


	अगर (!new_fb) अणु
		vmw_bo_unreference(&vps->bo);
		vps->bo_size = 0;

		वापस 0;
	पूर्ण

	size = new_state->crtc_w * new_state->crtc_h * 4;
	dev_priv = vmw_priv(crtc->dev);

	अगर (vps->bo) अणु
		अगर (vps->bo_size == size) अणु
			/*
			 * Note that this might temporarily up the pin-count
			 * to 2, until cleanup_fb() is called.
			 */
			वापस vmw_bo_pin_in_vram(dev_priv, vps->bo,
						      true);
		पूर्ण

		vmw_bo_unreference(&vps->bo);
		vps->bo_size = 0;
	पूर्ण

	vps->bo = kzalloc(माप(*vps->bo), GFP_KERNEL);
	अगर (!vps->bo)
		वापस -ENOMEM;

	vmw_svga_enable(dev_priv);

	/* After we have alloced the backing store might not be able to
	 * resume the overlays, this is preferred to failing to alloc.
	 */
	vmw_overlay_छोड़ो_all(dev_priv);
	ret = vmw_bo_init(dev_priv, vps->bo, size,
			      &vmw_vram_placement,
			      false, true, &vmw_bo_bo_मुक्त);
	vmw_overlay_resume_all(dev_priv);
	अगर (ret) अणु
		vps->bo = शून्य; /* vmw_bo_init मुक्तs on error */
		वापस ret;
	पूर्ण

	vps->bo_size = size;

	/*
	 * TTM alपढ़ोy thinks the buffer is pinned, but make sure the
	 * pin_count is upped.
	 */
	वापस vmw_bo_pin_in_vram(dev_priv, vps->bo, true);
पूर्ण

अटल uपूर्णांक32_t vmw_sou_bo_fअगरo_size(काष्ठा vmw_du_update_plane *update,
				     uपूर्णांक32_t num_hits)
अणु
	वापस माप(काष्ठा vmw_kms_sou_define_gmrfb) +
		माप(काष्ठा vmw_kms_sou_bo_blit) * num_hits;
पूर्ण

अटल uपूर्णांक32_t vmw_sou_bo_define_gmrfb(काष्ठा vmw_du_update_plane *update,
					व्योम *cmd)
अणु
	काष्ठा vmw_framebuffer_bo *vfbbo =
		container_of(update->vfb, typeof(*vfbbo), base);
	काष्ठा vmw_kms_sou_define_gmrfb *gmr = cmd;
	पूर्णांक depth = update->vfb->base.क्रमmat->depth;

	/* Emulate RGBA support, contrary to svga_reg.h this is not
	 * supported by hosts. This is only a problem अगर we are पढ़ोing
	 * this value later and expecting what we uploaded back.
	 */
	अगर (depth == 32)
		depth = 24;

	gmr->header = SVGA_CMD_DEFINE_GMRFB;

	gmr->body.क्रमmat.bitsPerPixel = update->vfb->base.क्रमmat->cpp[0] * 8;
	gmr->body.क्रमmat.colorDepth = depth;
	gmr->body.क्रमmat.reserved = 0;
	gmr->body.bytesPerLine = update->vfb->base.pitches[0];
	vmw_bo_get_guest_ptr(&vfbbo->buffer->base, &gmr->body.ptr);

	वापस माप(*gmr);
पूर्ण

अटल uपूर्णांक32_t vmw_sou_bo_populate_clip(काष्ठा vmw_du_update_plane  *update,
					 व्योम *cmd, काष्ठा drm_rect *clip,
					 uपूर्णांक32_t fb_x, uपूर्णांक32_t fb_y)
अणु
	काष्ठा vmw_kms_sou_bo_blit *blit = cmd;

	blit->header = SVGA_CMD_BLIT_GMRFB_TO_SCREEN;
	blit->body.destScreenId = update->du->unit;
	blit->body.srcOrigin.x = fb_x;
	blit->body.srcOrigin.y = fb_y;
	blit->body.destRect.left = clip->x1;
	blit->body.destRect.top = clip->y1;
	blit->body.destRect.right = clip->x2;
	blit->body.destRect.bottom = clip->y2;

	वापस माप(*blit);
पूर्ण

अटल uपूर्णांक32_t vmw_stud_bo_post_clip(काष्ठा vmw_du_update_plane  *update,
				      व्योम *cmd, काष्ठा drm_rect *bb)
अणु
	वापस 0;
पूर्ण

/**
 * vmw_sou_plane_update_bo - Update display unit क्रम bo backed fb.
 * @dev_priv: Device निजी.
 * @plane: Plane state.
 * @old_state: Old plane state.
 * @vfb: Framebuffer which is blitted to display unit.
 * @out_fence: If non-शून्य, will वापस a ref-counted poपूर्णांकer to vmw_fence_obj.
 *             The वापसed fence poपूर्णांकer may be शून्य in which हाल the device
 *             has alपढ़ोy synchronized.
 *
 * Return: 0 on success or a negative error code on failure.
 */
अटल पूर्णांक vmw_sou_plane_update_bo(काष्ठा vmw_निजी *dev_priv,
				   काष्ठा drm_plane *plane,
				   काष्ठा drm_plane_state *old_state,
				   काष्ठा vmw_framebuffer *vfb,
				   काष्ठा vmw_fence_obj **out_fence)
अणु
	काष्ठा vmw_du_update_plane_buffer bo_update;

	स_रखो(&bo_update, 0, माप(काष्ठा vmw_du_update_plane_buffer));
	bo_update.base.plane = plane;
	bo_update.base.old_state = old_state;
	bo_update.base.dev_priv = dev_priv;
	bo_update.base.du = vmw_crtc_to_du(plane->state->crtc);
	bo_update.base.vfb = vfb;
	bo_update.base.out_fence = out_fence;
	bo_update.base.mutex = शून्य;
	bo_update.base.cpu_blit = false;
	bo_update.base.पूर्णांकr = true;

	bo_update.base.calc_fअगरo_size = vmw_sou_bo_fअगरo_size;
	bo_update.base.post_prepare = vmw_sou_bo_define_gmrfb;
	bo_update.base.clip = vmw_sou_bo_populate_clip;
	bo_update.base.post_clip = vmw_stud_bo_post_clip;

	वापस vmw_du_helper_plane_update(&bo_update.base);
पूर्ण

अटल uपूर्णांक32_t vmw_sou_surface_fअगरo_size(काष्ठा vmw_du_update_plane *update,
					  uपूर्णांक32_t num_hits)
अणु
	वापस माप(काष्ठा vmw_kms_sou_dirty_cmd) + माप(SVGASignedRect) *
		num_hits;
पूर्ण

अटल uपूर्णांक32_t vmw_sou_surface_post_prepare(काष्ठा vmw_du_update_plane *update,
					     व्योम *cmd)
अणु
	काष्ठा vmw_du_update_plane_surface *srf_update;

	srf_update = container_of(update, typeof(*srf_update), base);

	/*
	 * SOU SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN is special in the sense that
	 * its bounding box is filled beक्रमe iterating over all the clips. So
	 * store the FIFO start address and revisit to fill the details.
	 */
	srf_update->cmd_start = cmd;

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vmw_sou_surface_pre_clip(काष्ठा vmw_du_update_plane *update,
					 व्योम *cmd, uपूर्णांक32_t num_hits)
अणु
	काष्ठा vmw_kms_sou_dirty_cmd *blit = cmd;
	काष्ठा vmw_framebuffer_surface *vfbs;

	vfbs = container_of(update->vfb, typeof(*vfbs), base);

	blit->header.id = SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN;
	blit->header.size = माप(blit->body) + माप(SVGASignedRect) *
		num_hits;

	blit->body.srcImage.sid = vfbs->surface->res.id;
	blit->body.destScreenId = update->du->unit;

	/* Update the source and destination bounding box later in post_clip */
	blit->body.srcRect.left = 0;
	blit->body.srcRect.top = 0;
	blit->body.srcRect.right = 0;
	blit->body.srcRect.bottom = 0;

	blit->body.destRect.left = 0;
	blit->body.destRect.top = 0;
	blit->body.destRect.right = 0;
	blit->body.destRect.bottom = 0;

	वापस माप(*blit);
पूर्ण

अटल uपूर्णांक32_t vmw_sou_surface_clip_rect(काष्ठा vmw_du_update_plane *update,
					  व्योम *cmd, काष्ठा drm_rect *clip,
					  uपूर्णांक32_t src_x, uपूर्णांक32_t src_y)
अणु
	SVGASignedRect *rect = cmd;

	/*
	 * rects are relative to dest bounding box rect on screen object, so
	 * translate to it later in post_clip
	 */
	rect->left = clip->x1;
	rect->top = clip->y1;
	rect->right = clip->x2;
	rect->bottom = clip->y2;

	वापस माप(*rect);
पूर्ण

अटल uपूर्णांक32_t vmw_sou_surface_post_clip(काष्ठा vmw_du_update_plane *update,
					  व्योम *cmd, काष्ठा drm_rect *bb)
अणु
	काष्ठा vmw_du_update_plane_surface *srf_update;
	काष्ठा drm_plane_state *state = update->plane->state;
	काष्ठा drm_rect src_bb;
	काष्ठा vmw_kms_sou_dirty_cmd *blit;
	SVGASignedRect *rect;
	uपूर्णांक32_t num_hits;
	पूर्णांक translate_src_x;
	पूर्णांक translate_src_y;
	पूर्णांक i;

	srf_update = container_of(update, typeof(*srf_update), base);

	blit = srf_update->cmd_start;
	rect = (SVGASignedRect *)&blit[1];

	num_hits = (blit->header.size - माप(blit->body))/
		माप(SVGASignedRect);

	src_bb = *bb;

	/* To translate bb back to fb src coord */
	translate_src_x = (state->src_x >> 16) - state->crtc_x;
	translate_src_y = (state->src_y >> 16) - state->crtc_y;

	drm_rect_translate(&src_bb, translate_src_x, translate_src_y);

	blit->body.srcRect.left = src_bb.x1;
	blit->body.srcRect.top = src_bb.y1;
	blit->body.srcRect.right = src_bb.x2;
	blit->body.srcRect.bottom = src_bb.y2;

	blit->body.destRect.left = bb->x1;
	blit->body.destRect.top = bb->y1;
	blit->body.destRect.right = bb->x2;
	blit->body.destRect.bottom = bb->y2;

	/* rects are relative to dest bb rect */
	क्रम (i = 0; i < num_hits; i++) अणु
		rect->left -= bb->x1;
		rect->top -= bb->y1;
		rect->right -= bb->x1;
		rect->bottom -= bb->y1;
		rect++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_sou_plane_update_surface - Update display unit क्रम surface backed fb.
 * @dev_priv: Device निजी.
 * @plane: Plane state.
 * @old_state: Old plane state.
 * @vfb: Framebuffer which is blitted to display unit
 * @out_fence: If non-शून्य, will वापस a ref-counted poपूर्णांकer to vmw_fence_obj.
 *             The वापसed fence poपूर्णांकer may be शून्य in which हाल the device
 *             has alपढ़ोy synchronized.
 *
 * Return: 0 on success or a negative error code on failure.
 */
अटल पूर्णांक vmw_sou_plane_update_surface(काष्ठा vmw_निजी *dev_priv,
					काष्ठा drm_plane *plane,
					काष्ठा drm_plane_state *old_state,
					काष्ठा vmw_framebuffer *vfb,
					काष्ठा vmw_fence_obj **out_fence)
अणु
	काष्ठा vmw_du_update_plane_surface srf_update;

	स_रखो(&srf_update, 0, माप(काष्ठा vmw_du_update_plane_surface));
	srf_update.base.plane = plane;
	srf_update.base.old_state = old_state;
	srf_update.base.dev_priv = dev_priv;
	srf_update.base.du = vmw_crtc_to_du(plane->state->crtc);
	srf_update.base.vfb = vfb;
	srf_update.base.out_fence = out_fence;
	srf_update.base.mutex = &dev_priv->cmdbuf_mutex;
	srf_update.base.cpu_blit = false;
	srf_update.base.पूर्णांकr = true;

	srf_update.base.calc_fअगरo_size = vmw_sou_surface_fअगरo_size;
	srf_update.base.post_prepare = vmw_sou_surface_post_prepare;
	srf_update.base.pre_clip = vmw_sou_surface_pre_clip;
	srf_update.base.clip = vmw_sou_surface_clip_rect;
	srf_update.base.post_clip = vmw_sou_surface_post_clip;

	वापस vmw_du_helper_plane_update(&srf_update.base);
पूर्ण

अटल व्योम
vmw_sou_primary_plane_atomic_update(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state, plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state, plane);
	काष्ठा drm_crtc *crtc = new_state->crtc;
	काष्ठा drm_pending_vblank_event *event = शून्य;
	काष्ठा vmw_fence_obj *fence = शून्य;
	पूर्णांक ret;

	/* In हाल of device error, मुख्यtain consistent atomic state */
	अगर (crtc && new_state->fb) अणु
		काष्ठा vmw_निजी *dev_priv = vmw_priv(crtc->dev);
		काष्ठा vmw_framebuffer *vfb =
			vmw_framebuffer_to_vfb(new_state->fb);

		अगर (vfb->bo)
			ret = vmw_sou_plane_update_bo(dev_priv, plane,
						      old_state, vfb, &fence);
		अन्यथा
			ret = vmw_sou_plane_update_surface(dev_priv, plane,
							   old_state, vfb,
							   &fence);
		अगर (ret != 0)
			DRM_ERROR("Failed to update screen.\n");
	पूर्ण अन्यथा अणु
		/* Do nothing when fb and crtc is शून्य (blank crtc) */
		वापस;
	पूर्ण

	/* For error हाल vblank event is send from vmw_du_crtc_atomic_flush */
	event = crtc->state->event;
	अगर (event && fence) अणु
		काष्ठा drm_file *file_priv = event->base.file_priv;

		ret = vmw_event_fence_action_queue(file_priv,
						   fence,
						   &event->base,
						   &event->event.vbl.tv_sec,
						   &event->event.vbl.tv_usec,
						   true);

		अगर (unlikely(ret != 0))
			DRM_ERROR("Failed to queue event on fence.\n");
		अन्यथा
			crtc->state->event = शून्य;
	पूर्ण

	अगर (fence)
		vmw_fence_obj_unreference(&fence);
पूर्ण


अटल स्थिर काष्ठा drm_plane_funcs vmw_sou_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = vmw_du_primary_plane_destroy,
	.reset = vmw_du_plane_reset,
	.atomic_duplicate_state = vmw_du_plane_duplicate_state,
	.atomic_destroy_state = vmw_du_plane_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs vmw_sou_cursor_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = vmw_du_cursor_plane_destroy,
	.reset = vmw_du_plane_reset,
	.atomic_duplicate_state = vmw_du_plane_duplicate_state,
	.atomic_destroy_state = vmw_du_plane_destroy_state,
पूर्ण;

/*
 * Atomic Helpers
 */
अटल स्थिर काष्ठा
drm_plane_helper_funcs vmw_sou_cursor_plane_helper_funcs = अणु
	.atomic_check = vmw_du_cursor_plane_atomic_check,
	.atomic_update = vmw_du_cursor_plane_atomic_update,
	.prepare_fb = vmw_du_cursor_plane_prepare_fb,
	.cleanup_fb = vmw_du_plane_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा
drm_plane_helper_funcs vmw_sou_primary_plane_helper_funcs = अणु
	.atomic_check = vmw_du_primary_plane_atomic_check,
	.atomic_update = vmw_sou_primary_plane_atomic_update,
	.prepare_fb = vmw_sou_primary_plane_prepare_fb,
	.cleanup_fb = vmw_sou_primary_plane_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs vmw_sou_crtc_helper_funcs = अणु
	.prepare = vmw_sou_crtc_helper_prepare,
	.mode_set_nofb = vmw_sou_crtc_mode_set_nofb,
	.atomic_check = vmw_du_crtc_atomic_check,
	.atomic_begin = vmw_du_crtc_atomic_begin,
	.atomic_flush = vmw_du_crtc_atomic_flush,
	.atomic_enable = vmw_sou_crtc_atomic_enable,
	.atomic_disable = vmw_sou_crtc_atomic_disable,
पूर्ण;


अटल पूर्णांक vmw_sou_init(काष्ठा vmw_निजी *dev_priv, अचिन्हित unit)
अणु
	काष्ठा vmw_screen_object_unit *sou;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_plane *primary, *cursor;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret;

	sou = kzalloc(माप(*sou), GFP_KERNEL);
	अगर (!sou)
		वापस -ENOMEM;

	sou->base.unit = unit;
	crtc = &sou->base.crtc;
	encoder = &sou->base.encoder;
	connector = &sou->base.connector;
	primary = &sou->base.primary;
	cursor = &sou->base.cursor;

	sou->base.pref_active = (unit == 0);
	sou->base.pref_width = dev_priv->initial_width;
	sou->base.pref_height = dev_priv->initial_height;
	sou->base.pref_mode = शून्य;

	/*
	 * Remove this after enabling atomic because property values can
	 * only exist in a state object
	 */
	sou->base.is_implicit = false;

	/* Initialize primary plane */
	ret = drm_universal_plane_init(dev, &sou->base.primary,
				       0, &vmw_sou_plane_funcs,
				       vmw_primary_plane_क्रमmats,
				       ARRAY_SIZE(vmw_primary_plane_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize primary plane");
		जाओ err_मुक्त;
	पूर्ण

	drm_plane_helper_add(primary, &vmw_sou_primary_plane_helper_funcs);
	drm_plane_enable_fb_damage_clips(primary);

	/* Initialize cursor plane */
	ret = drm_universal_plane_init(dev, &sou->base.cursor,
			0, &vmw_sou_cursor_funcs,
			vmw_cursor_plane_क्रमmats,
			ARRAY_SIZE(vmw_cursor_plane_क्रमmats),
			शून्य, DRM_PLANE_TYPE_CURSOR, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize cursor plane");
		drm_plane_cleanup(&sou->base.primary);
		जाओ err_मुक्त;
	पूर्ण

	drm_plane_helper_add(cursor, &vmw_sou_cursor_plane_helper_funcs);

	ret = drm_connector_init(dev, connector, &vmw_sou_connector_funcs,
				 DRM_MODE_CONNECTOR_VIRTUAL);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector\n");
		जाओ err_मुक्त;
	पूर्ण

	drm_connector_helper_add(connector, &vmw_sou_connector_helper_funcs);
	connector->status = vmw_du_connector_detect(connector, true);

	ret = drm_encoder_init(dev, encoder, &vmw_screen_object_encoder_funcs,
			       DRM_MODE_ENCODER_VIRTUAL, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize encoder\n");
		जाओ err_मुक्त_connector;
	पूर्ण

	(व्योम) drm_connector_attach_encoder(connector, encoder);
	encoder->possible_crtcs = (1 << unit);
	encoder->possible_clones = 0;

	ret = drm_connector_रेजिस्टर(connector);
	अगर (ret) अणु
		DRM_ERROR("Failed to register connector\n");
		जाओ err_मुक्त_encoder;
	पूर्ण

	ret = drm_crtc_init_with_planes(dev, crtc, &sou->base.primary,
					&sou->base.cursor,
					&vmw_screen_object_crtc_funcs, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize CRTC\n");
		जाओ err_मुक्त_unरेजिस्टर;
	पूर्ण

	drm_crtc_helper_add(crtc, &vmw_sou_crtc_helper_funcs);

	drm_mode_crtc_set_gamma_size(crtc, 256);

	drm_object_attach_property(&connector->base,
				   dev_priv->hotplug_mode_update_property, 1);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_x_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_y_property, 0);
	वापस 0;

err_मुक्त_unरेजिस्टर:
	drm_connector_unरेजिस्टर(connector);
err_मुक्त_encoder:
	drm_encoder_cleanup(encoder);
err_मुक्त_connector:
	drm_connector_cleanup(connector);
err_मुक्त:
	kमुक्त(sou);
	वापस ret;
पूर्ण

पूर्णांक vmw_kms_sou_init_display(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक i, ret;

	अगर (!(dev_priv->capabilities & SVGA_CAP_SCREEN_OBJECT_2)) अणु
		DRM_INFO("Not using screen objects,"
			 " missing cap SCREEN_OBJECT_2\n");
		वापस -ENOSYS;
	पूर्ण

	ret = -ENOMEM;

	ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	अगर (unlikely(ret != 0))
		वापस ret;

	क्रम (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i)
		vmw_sou_init(dev_priv, i);

	dev_priv->active_display_unit = vmw_du_screen_object;

	drm_mode_config_reset(dev);

	DRM_INFO("Screen Objects Display Unit initialized\n");

	वापस 0;
पूर्ण

अटल पूर्णांक करो_bo_define_gmrfb(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा vmw_framebuffer *framebuffer)
अणु
	काष्ठा vmw_buffer_object *buf =
		container_of(framebuffer, काष्ठा vmw_framebuffer_bo,
			     base)->buffer;
	पूर्णांक depth = framebuffer->base.क्रमmat->depth;
	काष्ठा अणु
		uपूर्णांक32_t header;
		SVGAFअगरoCmdDefineGMRFB body;
	पूर्ण *cmd;

	/* Emulate RGBA support, contrary to svga_reg.h this is not
	 * supported by hosts. This is only a problem अगर we are पढ़ोing
	 * this value later and expecting what we uploaded back.
	 */
	अगर (depth == 32)
		depth = 24;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (!cmd)
		वापस -ENOMEM;

	cmd->header = SVGA_CMD_DEFINE_GMRFB;
	cmd->body.क्रमmat.bitsPerPixel = framebuffer->base.क्रमmat->cpp[0] * 8;
	cmd->body.क्रमmat.colorDepth = depth;
	cmd->body.क्रमmat.reserved = 0;
	cmd->body.bytesPerLine = framebuffer->base.pitches[0];
	/* Buffer is reserved in vram or GMR */
	vmw_bo_get_guest_ptr(&buf->base, &cmd->body.ptr);
	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_sou_surface_fअगरo_commit - Callback to fill in and submit a
 * blit surface to screen command.
 *
 * @dirty: The closure काष्ठाure.
 *
 * Fills in the missing fields in the command, and translates the cliprects
 * to match the destination bounding box encoded.
 */
अटल व्योम vmw_sou_surface_fअगरo_commit(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_kms_sou_surface_dirty *sdirty =
		container_of(dirty, typeof(*sdirty), base);
	काष्ठा vmw_kms_sou_dirty_cmd *cmd = dirty->cmd;
	s32 trans_x = dirty->unit->crtc.x - sdirty->dst_x;
	s32 trans_y = dirty->unit->crtc.y - sdirty->dst_y;
	माप_प्रकार region_size = dirty->num_hits * माप(SVGASignedRect);
	SVGASignedRect *blit = (SVGASignedRect *) &cmd[1];
	पूर्णांक i;

	अगर (!dirty->num_hits) अणु
		vmw_cmd_commit(dirty->dev_priv, 0);
		वापस;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_BLIT_SURFACE_TO_SCREEN;
	cmd->header.size = माप(cmd->body) + region_size;

	/*
	 * Use the destination bounding box to specअगरy destination - and
	 * source bounding regions.
	 */
	cmd->body.destRect.left = sdirty->left;
	cmd->body.destRect.right = sdirty->right;
	cmd->body.destRect.top = sdirty->top;
	cmd->body.destRect.bottom = sdirty->bottom;

	cmd->body.srcRect.left = sdirty->left + trans_x;
	cmd->body.srcRect.right = sdirty->right + trans_x;
	cmd->body.srcRect.top = sdirty->top + trans_y;
	cmd->body.srcRect.bottom = sdirty->bottom + trans_y;

	cmd->body.srcImage.sid = sdirty->sid;
	cmd->body.destScreenId = dirty->unit->unit;

	/* Blits are relative to the destination rect. Translate. */
	क्रम (i = 0; i < dirty->num_hits; ++i, ++blit) अणु
		blit->left -= sdirty->left;
		blit->right -= sdirty->left;
		blit->top -= sdirty->top;
		blit->bottom -= sdirty->top;
	पूर्ण

	vmw_cmd_commit(dirty->dev_priv, region_size + माप(*cmd));

	sdirty->left = sdirty->top = S32_MAX;
	sdirty->right = sdirty->bottom = S32_MIN;
पूर्ण

/**
 * vmw_sou_surface_clip - Callback to encode a blit surface to screen cliprect.
 *
 * @dirty: The closure काष्ठाure
 *
 * Encodes a SVGASignedRect cliprect and updates the bounding box of the
 * BLIT_SURFACE_TO_SCREEN command.
 */
अटल व्योम vmw_sou_surface_clip(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_kms_sou_surface_dirty *sdirty =
		container_of(dirty, typeof(*sdirty), base);
	काष्ठा vmw_kms_sou_dirty_cmd *cmd = dirty->cmd;
	SVGASignedRect *blit = (SVGASignedRect *) &cmd[1];

	/* Destination rect. */
	blit += dirty->num_hits;
	blit->left = dirty->unit_x1;
	blit->top = dirty->unit_y1;
	blit->right = dirty->unit_x2;
	blit->bottom = dirty->unit_y2;

	/* Destination bounding box */
	sdirty->left = min_t(s32, sdirty->left, dirty->unit_x1);
	sdirty->top = min_t(s32, sdirty->top, dirty->unit_y1);
	sdirty->right = max_t(s32, sdirty->right, dirty->unit_x2);
	sdirty->bottom = max_t(s32, sdirty->bottom, dirty->unit_y2);

	dirty->num_hits++;
पूर्ण

/**
 * vmw_kms_sou_करो_surface_dirty - Dirty part of a surface backed framebuffer
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठाure.
 * @framebuffer: Poपूर्णांकer to the surface-buffer backed framebuffer.
 * @clips: Array of clip rects. Either @clips or @vclips must be शून्य.
 * @vclips: Alternate array of clip rects. Either @clips or @vclips must
 * be शून्य.
 * @srf: Poपूर्णांकer to surface to blit from. If शून्य, the surface attached
 * to @framebuffer will be used.
 * @dest_x: X coordinate offset to align @srf with framebuffer coordinates.
 * @dest_y: Y coordinate offset to align @srf with framebuffer coordinates.
 * @num_clips: Number of clip rects in @clips.
 * @inc: Increment to use when looping over @clips.
 * @out_fence: If non-शून्य, will वापस a ref-counted poपूर्णांकer to a
 * काष्ठा vmw_fence_obj. The वापसed fence poपूर्णांकer may be शून्य in which
 * हाल the device has alपढ़ोy synchronized.
 * @crtc: If crtc is passed, perक्रमm surface dirty on that crtc only.
 *
 * Returns 0 on success, negative error code on failure. -ERESTARTSYS अगर
 * पूर्णांकerrupted.
 */
पूर्णांक vmw_kms_sou_करो_surface_dirty(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_framebuffer *framebuffer,
				 काष्ठा drm_clip_rect *clips,
				 काष्ठा drm_vmw_rect *vclips,
				 काष्ठा vmw_resource *srf,
				 s32 dest_x,
				 s32 dest_y,
				 अचिन्हित num_clips, पूर्णांक inc,
				 काष्ठा vmw_fence_obj **out_fence,
				 काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vmw_framebuffer_surface *vfbs =
		container_of(framebuffer, typeof(*vfbs), base);
	काष्ठा vmw_kms_sou_surface_dirty sdirty;
	DECLARE_VAL_CONTEXT(val_ctx, शून्य, 0);
	पूर्णांक ret;

	अगर (!srf)
		srf = &vfbs->surface->res;

	ret = vmw_validation_add_resource(&val_ctx, srf, 0, VMW_RES_सूचीTY_NONE,
					  शून्य, शून्य);
	अगर (ret)
		वापस ret;

	ret = vmw_validation_prepare(&val_ctx, &dev_priv->cmdbuf_mutex, true);
	अगर (ret)
		जाओ out_unref;

	sdirty.base.fअगरo_commit = vmw_sou_surface_fअगरo_commit;
	sdirty.base.clip = vmw_sou_surface_clip;
	sdirty.base.dev_priv = dev_priv;
	sdirty.base.fअगरo_reserve_size = माप(काष्ठा vmw_kms_sou_dirty_cmd) +
	  माप(SVGASignedRect) * num_clips;
	sdirty.base.crtc = crtc;

	sdirty.sid = srf->id;
	sdirty.left = sdirty.top = S32_MAX;
	sdirty.right = sdirty.bottom = S32_MIN;
	sdirty.dst_x = dest_x;
	sdirty.dst_y = dest_y;

	ret = vmw_kms_helper_dirty(dev_priv, framebuffer, clips, vclips,
				   dest_x, dest_y, num_clips, inc,
				   &sdirty.base);
	vmw_kms_helper_validation_finish(dev_priv, शून्य, &val_ctx, out_fence,
					 शून्य);

	वापस ret;

out_unref:
	vmw_validation_unref_lists(&val_ctx);
	वापस ret;
पूर्ण

/**
 * vmw_sou_bo_fअगरo_commit - Callback to submit a set of पढ़ोback clips.
 *
 * @dirty: The closure काष्ठाure.
 *
 * Commits a previously built command buffer of पढ़ोback clips.
 */
अटल व्योम vmw_sou_bo_fअगरo_commit(काष्ठा vmw_kms_dirty *dirty)
अणु
	अगर (!dirty->num_hits) अणु
		vmw_cmd_commit(dirty->dev_priv, 0);
		वापस;
	पूर्ण

	vmw_cmd_commit(dirty->dev_priv,
			माप(काष्ठा vmw_kms_sou_bo_blit) *
			dirty->num_hits);
पूर्ण

/**
 * vmw_sou_bo_clip - Callback to encode a पढ़ोback cliprect.
 *
 * @dirty: The closure काष्ठाure
 *
 * Encodes a BLIT_GMRFB_TO_SCREEN cliprect.
 */
अटल व्योम vmw_sou_bo_clip(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_kms_sou_bo_blit *blit = dirty->cmd;

	blit += dirty->num_hits;
	blit->header = SVGA_CMD_BLIT_GMRFB_TO_SCREEN;
	blit->body.destScreenId = dirty->unit->unit;
	blit->body.srcOrigin.x = dirty->fb_x;
	blit->body.srcOrigin.y = dirty->fb_y;
	blit->body.destRect.left = dirty->unit_x1;
	blit->body.destRect.top = dirty->unit_y1;
	blit->body.destRect.right = dirty->unit_x2;
	blit->body.destRect.bottom = dirty->unit_y2;
	dirty->num_hits++;
पूर्ण

/**
 * vmw_kms_करो_bo_dirty - Dirty part of a buffer-object backed framebuffer
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठाure.
 * @framebuffer: Poपूर्णांकer to the buffer-object backed framebuffer.
 * @clips: Array of clip rects.
 * @vclips: Alternate array of clip rects. Either @clips or @vclips must
 * be शून्य.
 * @num_clips: Number of clip rects in @clips.
 * @increment: Increment to use when looping over @clips.
 * @पूर्णांकerruptible: Whether to perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 * @out_fence: If non-शून्य, will वापस a ref-counted poपूर्णांकer to a
 * काष्ठा vmw_fence_obj. The वापसed fence poपूर्णांकer may be शून्य in which
 * हाल the device has alपढ़ोy synchronized.
 * @crtc: If crtc is passed, perक्रमm bo dirty on that crtc only.
 *
 * Returns 0 on success, negative error code on failure. -ERESTARTSYS अगर
 * पूर्णांकerrupted.
 */
पूर्णांक vmw_kms_sou_करो_bo_dirty(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_framebuffer *framebuffer,
				काष्ठा drm_clip_rect *clips,
				काष्ठा drm_vmw_rect *vclips,
				अचिन्हित num_clips, पूर्णांक increment,
				bool पूर्णांकerruptible,
				काष्ठा vmw_fence_obj **out_fence,
				काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vmw_buffer_object *buf =
		container_of(framebuffer, काष्ठा vmw_framebuffer_bo,
			     base)->buffer;
	काष्ठा vmw_kms_dirty dirty;
	DECLARE_VAL_CONTEXT(val_ctx, शून्य, 0);
	पूर्णांक ret;

	ret = vmw_validation_add_bo(&val_ctx, buf, false, false);
	अगर (ret)
		वापस ret;

	ret = vmw_validation_prepare(&val_ctx, शून्य, पूर्णांकerruptible);
	अगर (ret)
		जाओ out_unref;

	ret = करो_bo_define_gmrfb(dev_priv, framebuffer);
	अगर (unlikely(ret != 0))
		जाओ out_revert;

	dirty.crtc = crtc;
	dirty.fअगरo_commit = vmw_sou_bo_fअगरo_commit;
	dirty.clip = vmw_sou_bo_clip;
	dirty.fअगरo_reserve_size = माप(काष्ठा vmw_kms_sou_bo_blit) *
		num_clips;
	ret = vmw_kms_helper_dirty(dev_priv, framebuffer, clips, vclips,
				   0, 0, num_clips, increment, &dirty);
	vmw_kms_helper_validation_finish(dev_priv, शून्य, &val_ctx, out_fence,
					 शून्य);

	वापस ret;

out_revert:
	vmw_validation_revert(&val_ctx);
out_unref:
	vmw_validation_unref_lists(&val_ctx);

	वापस ret;
पूर्ण


/**
 * vmw_sou_पढ़ोback_fअगरo_commit - Callback to submit a set of पढ़ोback clips.
 *
 * @dirty: The closure काष्ठाure.
 *
 * Commits a previously built command buffer of पढ़ोback clips.
 */
अटल व्योम vmw_sou_पढ़ोback_fअगरo_commit(काष्ठा vmw_kms_dirty *dirty)
अणु
	अगर (!dirty->num_hits) अणु
		vmw_cmd_commit(dirty->dev_priv, 0);
		वापस;
	पूर्ण

	vmw_cmd_commit(dirty->dev_priv,
			माप(काष्ठा vmw_kms_sou_पढ़ोback_blit) *
			dirty->num_hits);
पूर्ण

/**
 * vmw_sou_पढ़ोback_clip - Callback to encode a पढ़ोback cliprect.
 *
 * @dirty: The closure काष्ठाure
 *
 * Encodes a BLIT_SCREEN_TO_GMRFB cliprect.
 */
अटल व्योम vmw_sou_पढ़ोback_clip(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_kms_sou_पढ़ोback_blit *blit = dirty->cmd;

	blit += dirty->num_hits;
	blit->header = SVGA_CMD_BLIT_SCREEN_TO_GMRFB;
	blit->body.srcScreenId = dirty->unit->unit;
	blit->body.destOrigin.x = dirty->fb_x;
	blit->body.destOrigin.y = dirty->fb_y;
	blit->body.srcRect.left = dirty->unit_x1;
	blit->body.srcRect.top = dirty->unit_y1;
	blit->body.srcRect.right = dirty->unit_x2;
	blit->body.srcRect.bottom = dirty->unit_y2;
	dirty->num_hits++;
पूर्ण

/**
 * vmw_kms_sou_पढ़ोback - Perक्रमm a पढ़ोback from the screen object प्रणाली to
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
 * @crtc: If crtc is passed, पढ़ोback on that crtc only.
 *
 * Returns 0 on success, negative error code on failure. -ERESTARTSYS अगर
 * पूर्णांकerrupted.
 */
पूर्णांक vmw_kms_sou_पढ़ोback(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा drm_file *file_priv,
			 काष्ठा vmw_framebuffer *vfb,
			 काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
			 काष्ठा drm_vmw_rect *vclips,
			 uपूर्णांक32_t num_clips,
			 काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vmw_buffer_object *buf =
		container_of(vfb, काष्ठा vmw_framebuffer_bo, base)->buffer;
	काष्ठा vmw_kms_dirty dirty;
	DECLARE_VAL_CONTEXT(val_ctx, शून्य, 0);
	पूर्णांक ret;

	ret = vmw_validation_add_bo(&val_ctx, buf, false, false);
	अगर (ret)
		वापस ret;

	ret = vmw_validation_prepare(&val_ctx, शून्य, true);
	अगर (ret)
		जाओ out_unref;

	ret = करो_bo_define_gmrfb(dev_priv, vfb);
	अगर (unlikely(ret != 0))
		जाओ out_revert;

	dirty.crtc = crtc;
	dirty.fअगरo_commit = vmw_sou_पढ़ोback_fअगरo_commit;
	dirty.clip = vmw_sou_पढ़ोback_clip;
	dirty.fअगरo_reserve_size = माप(काष्ठा vmw_kms_sou_पढ़ोback_blit) *
		num_clips;
	ret = vmw_kms_helper_dirty(dev_priv, vfb, शून्य, vclips,
				   0, 0, num_clips, 1, &dirty);
	vmw_kms_helper_validation_finish(dev_priv, file_priv, &val_ctx, शून्य,
					 user_fence_rep);

	वापस ret;

out_revert:
	vmw_validation_revert(&val_ctx);
out_unref:
	vmw_validation_unref_lists(&val_ctx);
	
	वापस ret;
पूर्ण
