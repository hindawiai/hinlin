<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/******************************************************************************
 *
 * COPYRIGHT (C) 2014-2015 VMware, Inc., Palo Alto, CA., USA
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
 ******************************************************************************/

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vmwgfx_kms.h"
#समावेश "device_include/svga3d_surfacedefs.h"

#घोषणा vmw_crtc_to_stdu(x) \
	container_of(x, काष्ठा vmw_screen_target_display_unit, base.crtc)
#घोषणा vmw_encoder_to_stdu(x) \
	container_of(x, काष्ठा vmw_screen_target_display_unit, base.encoder)
#घोषणा vmw_connector_to_stdu(x) \
	container_of(x, काष्ठा vmw_screen_target_display_unit, base.connector)



क्रमागत stdu_content_type अणु
	SAME_AS_DISPLAY = 0,
	SEPARATE_SURFACE,
	SEPARATE_BO
पूर्ण;

/**
 * काष्ठा vmw_stdu_dirty - closure काष्ठाure क्रम the update functions
 *
 * @base: The base type we derive from. Used by vmw_kms_helper_dirty().
 * @transfer: Transfer direction क्रम DMA command.
 * @left: Left side of bounding box.
 * @right: Right side of bounding box.
 * @top: Top side of bounding box.
 * @bottom: Bottom side of bounding box.
 * @fb_left: Left side of the framebuffer/content bounding box
 * @fb_top: Top of the framebuffer/content bounding box
 * @pitch: framebuffer pitch (stride)
 * @buf: buffer object when DMA-ing between buffer and screen tarमाला_लो.
 * @sid: Surface ID when copying between surface and screen tarमाला_लो.
 */
काष्ठा vmw_stdu_dirty अणु
	काष्ठा vmw_kms_dirty base;
	SVGA3dTransferType  transfer;
	s32 left, right, top, bottom;
	s32 fb_left, fb_top;
	u32 pitch;
	जोड़ अणु
		काष्ठा vmw_buffer_object *buf;
		u32 sid;
	पूर्ण;
पूर्ण;

/*
 * SVGA commands that are used by this code. Please see the device headers
 * क्रम explanation.
 */
काष्ठा vmw_stdu_update अणु
	SVGA3dCmdHeader header;
	SVGA3dCmdUpdateGBScreenTarget body;
पूर्ण;

काष्ठा vmw_stdu_dma अणु
	SVGA3dCmdHeader     header;
	SVGA3dCmdSurfaceDMA body;
पूर्ण;

काष्ठा vmw_stdu_surface_copy अणु
	SVGA3dCmdHeader      header;
	SVGA3dCmdSurfaceCopy body;
पूर्ण;

काष्ठा vmw_stdu_update_gb_image अणु
	SVGA3dCmdHeader header;
	SVGA3dCmdUpdateGBImage body;
पूर्ण;

/**
 * काष्ठा vmw_screen_target_display_unit
 *
 * @base: VMW specअगरic DU काष्ठाure
 * @display_srf: surface to be displayed.  The dimension of this will always
 *               match the display mode.  If the display mode matches
 *               content_vfbs dimensions, then this is a poपूर्णांकer पूर्णांकo the
 *               corresponding field in content_vfbs.  If not, then this
 *               is a separate buffer to which content_vfbs will blit to.
 * @content_fb_type: content_fb type
 * @display_width:  display width
 * @display_height: display height
 * @defined:     true अगर the current display unit has been initialized
 * @cpp:         Bytes per pixel
 */
काष्ठा vmw_screen_target_display_unit अणु
	काष्ठा vmw_display_unit base;
	काष्ठा vmw_surface *display_srf;
	क्रमागत stdu_content_type content_fb_type;
	s32 display_width, display_height;

	bool defined;

	/* For CPU Blit */
	अचिन्हित पूर्णांक cpp;
पूर्ण;



अटल व्योम vmw_stdu_destroy(काष्ठा vmw_screen_target_display_unit *stdu);



/******************************************************************************
 * Screen Target Display Unit CRTC Functions
 *****************************************************************************/


/**
 * vmw_stdu_crtc_destroy - cleans up the STDU
 *
 * @crtc: used to get a reference to the containing STDU
 */
अटल व्योम vmw_stdu_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	vmw_stdu_destroy(vmw_crtc_to_stdu(crtc));
पूर्ण

/**
 * vmw_stdu_define_st - Defines a Screen Target
 *
 * @dev_priv:  VMW DRM device
 * @stdu: display unit to create a Screen Target क्रम
 * @mode: The mode to set.
 * @crtc_x: X coordinate of screen target relative to framebuffer origin.
 * @crtc_y: Y coordinate of screen target relative to framebuffer origin.
 *
 * Creates a STDU that we can used later.  This function is called whenever the
 * framebuffer size changes.
 *
 * RETURNs:
 * 0 on success, error code on failure
 */
अटल पूर्णांक vmw_stdu_define_st(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_screen_target_display_unit *stdu,
			      काष्ठा drm_display_mode *mode,
			      पूर्णांक crtc_x, पूर्णांक crtc_y)
अणु
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDefineGBScreenTarget body;
	पूर्ण *cmd;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id   = SVGA_3D_CMD_DEFINE_GB_SCREENTARGET;
	cmd->header.size = माप(cmd->body);

	cmd->body.stid   = stdu->base.unit;
	cmd->body.width  = mode->hdisplay;
	cmd->body.height = mode->vdisplay;
	cmd->body.flags  = (0 == cmd->body.stid) ? SVGA_STFLAG_PRIMARY : 0;
	cmd->body.dpi    = 0;
	cmd->body.xRoot  = crtc_x;
	cmd->body.yRoot  = crtc_y;

	stdu->base.set_gui_x = cmd->body.xRoot;
	stdu->base.set_gui_y = cmd->body.yRoot;

	vmw_cmd_commit(dev_priv, माप(*cmd));

	stdu->defined = true;
	stdu->display_width  = mode->hdisplay;
	stdu->display_height = mode->vdisplay;

	वापस 0;
पूर्ण



/**
 * vmw_stdu_bind_st - Binds a surface to a Screen Target
 *
 * @dev_priv: VMW DRM device
 * @stdu: display unit affected
 * @res: Buffer to bind to the screen target.  Set to शून्य to blank screen.
 *
 * Binding a surface to a Screen Target the same as flipping
 */
अटल पूर्णांक vmw_stdu_bind_st(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_screen_target_display_unit *stdu,
			    स्थिर काष्ठा vmw_resource *res)
अणु
	SVGA3dSurfaceImageId image;

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdBindGBScreenTarget body;
	पूर्ण *cmd;


	अगर (!stdu->defined) अणु
		DRM_ERROR("No screen target defined\n");
		वापस -EINVAL;
	पूर्ण

	/* Set up image using inक्रमmation in vfb */
	स_रखो(&image, 0, माप(image));
	image.sid = res ? res->id : SVGA3D_INVALID_ID;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id   = SVGA_3D_CMD_BIND_GB_SCREENTARGET;
	cmd->header.size = माप(cmd->body);

	cmd->body.stid   = stdu->base.unit;
	cmd->body.image  = image;

	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_stdu_populate_update - populate an UPDATE_GB_SCREENTARGET command with a
 * bounding box.
 *
 * @cmd: Poपूर्णांकer to command stream.
 * @unit: Screen target unit.
 * @left: Left side of bounding box.
 * @right: Right side of bounding box.
 * @top: Top side of bounding box.
 * @bottom: Bottom side of bounding box.
 */
अटल व्योम vmw_stdu_populate_update(व्योम *cmd, पूर्णांक unit,
				     s32 left, s32 right, s32 top, s32 bottom)
अणु
	काष्ठा vmw_stdu_update *update = cmd;

	update->header.id   = SVGA_3D_CMD_UPDATE_GB_SCREENTARGET;
	update->header.size = माप(update->body);

	update->body.stid   = unit;
	update->body.rect.x = left;
	update->body.rect.y = top;
	update->body.rect.w = right - left;
	update->body.rect.h = bottom - top;
पूर्ण

/**
 * vmw_stdu_update_st - Full update of a Screen Target
 *
 * @dev_priv: VMW DRM device
 * @stdu: display unit affected
 *
 * This function needs to be called whenever the content of a screen
 * target has changed completely. Typically as a result of a backing
 * surface change.
 *
 * RETURNS:
 * 0 on success, error code on failure
 */
अटल पूर्णांक vmw_stdu_update_st(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_screen_target_display_unit *stdu)
अणु
	काष्ठा vmw_stdu_update *cmd;

	अगर (!stdu->defined) अणु
		DRM_ERROR("No screen target defined");
		वापस -EINVAL;
	पूर्ण

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	vmw_stdu_populate_update(cmd, stdu->base.unit,
				 0, stdu->display_width,
				 0, stdu->display_height);

	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण



/**
 * vmw_stdu_destroy_st - Destroy a Screen Target
 *
 * @dev_priv:  VMW DRM device
 * @stdu: display unit to destroy
 */
अटल पूर्णांक vmw_stdu_destroy_st(काष्ठा vmw_निजी *dev_priv,
			       काष्ठा vmw_screen_target_display_unit *stdu)
अणु
	पूर्णांक    ret;

	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdDestroyGBScreenTarget body;
	पूर्ण *cmd;


	/* Nothing to करो अगर not successfully defined */
	अगर (unlikely(!stdu->defined))
		वापस 0;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id   = SVGA_3D_CMD_DESTROY_GB_SCREENTARGET;
	cmd->header.size = माप(cmd->body);

	cmd->body.stid   = stdu->base.unit;

	vmw_cmd_commit(dev_priv, माप(*cmd));

	/* Force sync */
	ret = vmw_fallback_रुको(dev_priv, false, true, 0, false, 3*HZ);
	अगर (unlikely(ret != 0))
		DRM_ERROR("Failed to sync with HW");

	stdu->defined = false;
	stdu->display_width  = 0;
	stdu->display_height = 0;

	वापस ret;
पूर्ण


/**
 * vmw_stdu_crtc_mode_set_nofb - Updates screen target size
 *
 * @crtc: CRTC associated with the screen target
 *
 * This function defines/destroys a screen target
 *
 */
अटल व्योम vmw_stdu_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा vmw_connector_state *vmw_conn_state;
	पूर्णांक x, y, ret;

	stdu = vmw_crtc_to_stdu(crtc);
	dev_priv = vmw_priv(crtc->dev);
	conn_state = stdu->base.connector.state;
	vmw_conn_state = vmw_connector_state_to_vcs(conn_state);

	अगर (stdu->defined) अणु
		ret = vmw_stdu_bind_st(dev_priv, stdu, शून्य);
		अगर (ret)
			DRM_ERROR("Failed to blank CRTC\n");

		(व्योम) vmw_stdu_update_st(dev_priv, stdu);

		ret = vmw_stdu_destroy_st(dev_priv, stdu);
		अगर (ret)
			DRM_ERROR("Failed to destroy Screen Target\n");

		stdu->content_fb_type = SAME_AS_DISPLAY;
	पूर्ण

	अगर (!crtc->state->enable)
		वापस;

	x = vmw_conn_state->gui_x;
	y = vmw_conn_state->gui_y;

	vmw_svga_enable(dev_priv);
	ret = vmw_stdu_define_st(dev_priv, stdu, &crtc->mode, x, y);

	अगर (ret)
		DRM_ERROR("Failed to define Screen Target of size %dx%d\n",
			  crtc->x, crtc->y);
पूर्ण


अटल व्योम vmw_stdu_crtc_helper_prepare(काष्ठा drm_crtc *crtc)
अणु
पूर्ण

अटल व्योम vmw_stdu_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल व्योम vmw_stdu_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_screen_target_display_unit *stdu;
	पूर्णांक ret;


	अगर (!crtc) अणु
		DRM_ERROR("CRTC is NULL\n");
		वापस;
	पूर्ण

	stdu     = vmw_crtc_to_stdu(crtc);
	dev_priv = vmw_priv(crtc->dev);

	अगर (stdu->defined) अणु
		ret = vmw_stdu_bind_st(dev_priv, stdu, शून्य);
		अगर (ret)
			DRM_ERROR("Failed to blank CRTC\n");

		(व्योम) vmw_stdu_update_st(dev_priv, stdu);

		ret = vmw_stdu_destroy_st(dev_priv, stdu);
		अगर (ret)
			DRM_ERROR("Failed to destroy Screen Target\n");

		stdu->content_fb_type = SAME_AS_DISPLAY;
	पूर्ण
पूर्ण

/**
 * vmw_stdu_bo_clip - Callback to encode a suface DMA command cliprect
 *
 * @dirty: The closure काष्ठाure.
 *
 * Encodes a surface DMA command cliprect and updates the bounding box
 * क्रम the DMA.
 */
अटल व्योम vmw_stdu_bo_clip(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_stdu_dirty *ddirty =
		container_of(dirty, काष्ठा vmw_stdu_dirty, base);
	काष्ठा vmw_stdu_dma *cmd = dirty->cmd;
	काष्ठा SVGA3dCopyBox *blit = (काष्ठा SVGA3dCopyBox *) &cmd[1];

	blit += dirty->num_hits;
	blit->srcx = dirty->fb_x;
	blit->srcy = dirty->fb_y;
	blit->x = dirty->unit_x1;
	blit->y = dirty->unit_y1;
	blit->d = 1;
	blit->w = dirty->unit_x2 - dirty->unit_x1;
	blit->h = dirty->unit_y2 - dirty->unit_y1;
	dirty->num_hits++;

	अगर (ddirty->transfer != SVGA3D_WRITE_HOST_VRAM)
		वापस;

	/* Destination bounding box */
	ddirty->left = min_t(s32, ddirty->left, dirty->unit_x1);
	ddirty->top = min_t(s32, ddirty->top, dirty->unit_y1);
	ddirty->right = max_t(s32, ddirty->right, dirty->unit_x2);
	ddirty->bottom = max_t(s32, ddirty->bottom, dirty->unit_y2);
पूर्ण

/**
 * vmw_stdu_bo_fअगरo_commit - Callback to fill in and submit a DMA command.
 *
 * @dirty: The closure काष्ठाure.
 *
 * Fills in the missing fields in a DMA command, and optionally encodes
 * a screen target update command, depending on transfer direction.
 */
अटल व्योम vmw_stdu_bo_fअगरo_commit(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_stdu_dirty *ddirty =
		container_of(dirty, काष्ठा vmw_stdu_dirty, base);
	काष्ठा vmw_screen_target_display_unit *stdu =
		container_of(dirty->unit, typeof(*stdu), base);
	काष्ठा vmw_stdu_dma *cmd = dirty->cmd;
	काष्ठा SVGA3dCopyBox *blit = (काष्ठा SVGA3dCopyBox *) &cmd[1];
	SVGA3dCmdSurfaceDMASuffix *suffix =
		(SVGA3dCmdSurfaceDMASuffix *) &blit[dirty->num_hits];
	माप_प्रकार blit_size = माप(*blit) * dirty->num_hits + माप(*suffix);

	अगर (!dirty->num_hits) अणु
		vmw_cmd_commit(dirty->dev_priv, 0);
		वापस;
	पूर्ण

	cmd->header.id = SVGA_3D_CMD_SURFACE_DMA;
	cmd->header.size = माप(cmd->body) + blit_size;
	vmw_bo_get_guest_ptr(&ddirty->buf->base, &cmd->body.guest.ptr);
	cmd->body.guest.pitch = ddirty->pitch;
	cmd->body.host.sid = stdu->display_srf->res.id;
	cmd->body.host.face = 0;
	cmd->body.host.mipmap = 0;
	cmd->body.transfer = ddirty->transfer;
	suffix->suffixSize = माप(*suffix);
	suffix->maximumOffset = ddirty->buf->base.base.size;

	अगर (ddirty->transfer == SVGA3D_WRITE_HOST_VRAM) अणु
		blit_size += माप(काष्ठा vmw_stdu_update);

		vmw_stdu_populate_update(&suffix[1], stdu->base.unit,
					 ddirty->left, ddirty->right,
					 ddirty->top, ddirty->bottom);
	पूर्ण

	vmw_cmd_commit(dirty->dev_priv, माप(*cmd) + blit_size);

	stdu->display_srf->res.res_dirty = true;
	ddirty->left = ddirty->top = S32_MAX;
	ddirty->right = ddirty->bottom = S32_MIN;
पूर्ण


/**
 * vmw_stdu_bo_cpu_clip - Callback to encode a CPU blit
 *
 * @dirty: The closure काष्ठाure.
 *
 * This function calculates the bounding box क्रम all the incoming clips.
 */
अटल व्योम vmw_stdu_bo_cpu_clip(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_stdu_dirty *ddirty =
		container_of(dirty, काष्ठा vmw_stdu_dirty, base);

	dirty->num_hits = 1;

	/* Calculate destination bounding box */
	ddirty->left = min_t(s32, ddirty->left, dirty->unit_x1);
	ddirty->top = min_t(s32, ddirty->top, dirty->unit_y1);
	ddirty->right = max_t(s32, ddirty->right, dirty->unit_x2);
	ddirty->bottom = max_t(s32, ddirty->bottom, dirty->unit_y2);

	/*
	 * Calculate content bounding box.  We only need the top-left
	 * coordinate because width and height will be the same as the
	 * destination bounding box above
	 */
	ddirty->fb_left = min_t(s32, ddirty->fb_left, dirty->fb_x);
	ddirty->fb_top  = min_t(s32, ddirty->fb_top, dirty->fb_y);
पूर्ण


/**
 * vmw_stdu_bo_cpu_commit - Callback to करो a CPU blit from buffer object
 *
 * @dirty: The closure काष्ठाure.
 *
 * For the special हाल when we cannot create a proxy surface in a
 * 2D VM, we have to करो a CPU blit ourselves.
 */
अटल व्योम vmw_stdu_bo_cpu_commit(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_stdu_dirty *ddirty =
		container_of(dirty, काष्ठा vmw_stdu_dirty, base);
	काष्ठा vmw_screen_target_display_unit *stdu =
		container_of(dirty->unit, typeof(*stdu), base);
	s32 width, height;
	s32 src_pitch, dst_pitch;
	काष्ठा tपंचांग_buffer_object *src_bo, *dst_bo;
	u32 src_offset, dst_offset;
	काष्ठा vmw_dअगरf_cpy dअगरf = VMW_CPU_BLIT_DIFF_INITIALIZER(stdu->cpp);

	अगर (!dirty->num_hits)
		वापस;

	width = ddirty->right - ddirty->left;
	height = ddirty->bottom - ddirty->top;

	अगर (width == 0 || height == 0)
		वापस;

	/* Assume we are blitting from Guest (bo) to Host (display_srf) */
	dst_pitch = stdu->display_srf->metadata.base_size.width * stdu->cpp;
	dst_bo = &stdu->display_srf->res.backup->base;
	dst_offset = ddirty->top * dst_pitch + ddirty->left * stdu->cpp;

	src_pitch = ddirty->pitch;
	src_bo = &ddirty->buf->base;
	src_offset = ddirty->fb_top * src_pitch + ddirty->fb_left * stdu->cpp;

	/* Swap src and dst अगर the assumption was wrong. */
	अगर (ddirty->transfer != SVGA3D_WRITE_HOST_VRAM) अणु
		swap(dst_pitch, src_pitch);
		swap(dst_bo, src_bo);
		swap(src_offset, dst_offset);
	पूर्ण

	(व्योम) vmw_bo_cpu_blit(dst_bo, dst_offset, dst_pitch,
			       src_bo, src_offset, src_pitch,
			       width * stdu->cpp, height, &dअगरf);

	अगर (ddirty->transfer == SVGA3D_WRITE_HOST_VRAM &&
	    drm_rect_visible(&dअगरf.rect)) अणु
		काष्ठा vmw_निजी *dev_priv;
		काष्ठा vmw_stdu_update *cmd;
		काष्ठा drm_clip_rect region;
		पूर्णांक ret;

		/* We are updating the actual surface, not a proxy */
		region.x1 = dअगरf.rect.x1;
		region.x2 = dअगरf.rect.x2;
		region.y1 = dअगरf.rect.y1;
		region.y2 = dअगरf.rect.y2;
		ret = vmw_kms_update_proxy(&stdu->display_srf->res, &region,
					   1, 1);
		अगर (ret)
			जाओ out_cleanup;


		dev_priv = vmw_priv(stdu->base.crtc.dev);
		cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
		अगर (!cmd)
			जाओ out_cleanup;

		vmw_stdu_populate_update(cmd, stdu->base.unit,
					 region.x1, region.x2,
					 region.y1, region.y2);

		vmw_cmd_commit(dev_priv, माप(*cmd));
	पूर्ण

out_cleanup:
	ddirty->left = ddirty->top = ddirty->fb_left = ddirty->fb_top = S32_MAX;
	ddirty->right = ddirty->bottom = S32_MIN;
पूर्ण

/**
 * vmw_kms_stdu_dma - Perक्रमm a DMA transfer between a buffer-object backed
 * framebuffer and the screen target प्रणाली.
 *
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठाure.
 * @file_priv: Poपूर्णांकer to a काष्ठा drm-file identअगरying the caller. May be
 * set to शून्य, but then @user_fence_rep must also be set to शून्य.
 * @vfb: Poपूर्णांकer to the buffer-object backed framebuffer.
 * @user_fence_rep: User-space provided काष्ठाure क्रम fence inक्रमmation.
 * @clips: Array of clip rects. Either @clips or @vclips must be शून्य.
 * @vclips: Alternate array of clip rects. Either @clips or @vclips must
 * be शून्य.
 * @num_clips: Number of clip rects in @clips or @vclips.
 * @increment: Increment to use when looping over @clips or @vclips.
 * @to_surface: Whether to DMA to the screen target प्रणाली as opposed to
 * from the screen target प्रणाली.
 * @पूर्णांकerruptible: Whether to perक्रमm रुकोs पूर्णांकerruptible अगर possible.
 * @crtc: If crtc is passed, perक्रमm stdu dma on that crtc only.
 *
 * If DMA-ing till the screen target प्रणाली, the function will also notअगरy
 * the screen target प्रणाली that a bounding box of the cliprects has been
 * updated.
 * Returns 0 on success, negative error code on failure. -ERESTARTSYS अगर
 * पूर्णांकerrupted.
 */
पूर्णांक vmw_kms_stdu_dma(काष्ठा vmw_निजी *dev_priv,
		     काष्ठा drm_file *file_priv,
		     काष्ठा vmw_framebuffer *vfb,
		     काष्ठा drm_vmw_fence_rep __user *user_fence_rep,
		     काष्ठा drm_clip_rect *clips,
		     काष्ठा drm_vmw_rect *vclips,
		     uपूर्णांक32_t num_clips,
		     पूर्णांक increment,
		     bool to_surface,
		     bool पूर्णांकerruptible,
		     काष्ठा drm_crtc *crtc)
अणु
	काष्ठा vmw_buffer_object *buf =
		container_of(vfb, काष्ठा vmw_framebuffer_bo, base)->buffer;
	काष्ठा vmw_stdu_dirty ddirty;
	पूर्णांक ret;
	bool cpu_blit = !(dev_priv->capabilities & SVGA_CAP_3D);
	DECLARE_VAL_CONTEXT(val_ctx, शून्य, 0);

	/*
	 * VMs without 3D support करोn't have the surface DMA command and
	 * we'll be using a CPU blit, and the framebuffer should be moved out
	 * of VRAM.
	 */
	ret = vmw_validation_add_bo(&val_ctx, buf, false, cpu_blit);
	अगर (ret)
		वापस ret;

	ret = vmw_validation_prepare(&val_ctx, शून्य, पूर्णांकerruptible);
	अगर (ret)
		जाओ out_unref;

	ddirty.transfer = (to_surface) ? SVGA3D_WRITE_HOST_VRAM :
		SVGA3D_READ_HOST_VRAM;
	ddirty.left = ddirty.top = S32_MAX;
	ddirty.right = ddirty.bottom = S32_MIN;
	ddirty.fb_left = ddirty.fb_top = S32_MAX;
	ddirty.pitch = vfb->base.pitches[0];
	ddirty.buf = buf;
	ddirty.base.fअगरo_commit = vmw_stdu_bo_fअगरo_commit;
	ddirty.base.clip = vmw_stdu_bo_clip;
	ddirty.base.fअगरo_reserve_size = माप(काष्ठा vmw_stdu_dma) +
		num_clips * माप(SVGA3dCopyBox) +
		माप(SVGA3dCmdSurfaceDMASuffix);
	अगर (to_surface)
		ddirty.base.fअगरo_reserve_size += माप(काष्ठा vmw_stdu_update);


	अगर (cpu_blit) अणु
		ddirty.base.fअगरo_commit = vmw_stdu_bo_cpu_commit;
		ddirty.base.clip = vmw_stdu_bo_cpu_clip;
		ddirty.base.fअगरo_reserve_size = 0;
	पूर्ण

	ddirty.base.crtc = crtc;

	ret = vmw_kms_helper_dirty(dev_priv, vfb, clips, vclips,
				   0, 0, num_clips, increment, &ddirty.base);

	vmw_kms_helper_validation_finish(dev_priv, file_priv, &val_ctx, शून्य,
					 user_fence_rep);
	वापस ret;

out_unref:
	vmw_validation_unref_lists(&val_ctx);
	वापस ret;
पूर्ण

/**
 * vmw_stdu_surface_clip - Callback to encode a surface copy command cliprect
 *
 * @dirty: The closure काष्ठाure.
 *
 * Encodes a surface copy command cliprect and updates the bounding box
 * क्रम the copy.
 */
अटल व्योम vmw_kms_stdu_surface_clip(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_stdu_dirty *sdirty =
		container_of(dirty, काष्ठा vmw_stdu_dirty, base);
	काष्ठा vmw_stdu_surface_copy *cmd = dirty->cmd;
	काष्ठा vmw_screen_target_display_unit *stdu =
		container_of(dirty->unit, typeof(*stdu), base);

	अगर (sdirty->sid != stdu->display_srf->res.id) अणु
		काष्ठा SVGA3dCopyBox *blit = (काष्ठा SVGA3dCopyBox *) &cmd[1];

		blit += dirty->num_hits;
		blit->srcx = dirty->fb_x;
		blit->srcy = dirty->fb_y;
		blit->x = dirty->unit_x1;
		blit->y = dirty->unit_y1;
		blit->d = 1;
		blit->w = dirty->unit_x2 - dirty->unit_x1;
		blit->h = dirty->unit_y2 - dirty->unit_y1;
	पूर्ण

	dirty->num_hits++;

	/* Destination bounding box */
	sdirty->left = min_t(s32, sdirty->left, dirty->unit_x1);
	sdirty->top = min_t(s32, sdirty->top, dirty->unit_y1);
	sdirty->right = max_t(s32, sdirty->right, dirty->unit_x2);
	sdirty->bottom = max_t(s32, sdirty->bottom, dirty->unit_y2);
पूर्ण

/**
 * vmw_stdu_surface_fअगरo_commit - Callback to fill in and submit a surface
 * copy command.
 *
 * @dirty: The closure काष्ठाure.
 *
 * Fills in the missing fields in a surface copy command, and encodes a screen
 * target update command.
 */
अटल व्योम vmw_kms_stdu_surface_fअगरo_commit(काष्ठा vmw_kms_dirty *dirty)
अणु
	काष्ठा vmw_stdu_dirty *sdirty =
		container_of(dirty, काष्ठा vmw_stdu_dirty, base);
	काष्ठा vmw_screen_target_display_unit *stdu =
		container_of(dirty->unit, typeof(*stdu), base);
	काष्ठा vmw_stdu_surface_copy *cmd = dirty->cmd;
	काष्ठा vmw_stdu_update *update;
	माप_प्रकार blit_size = माप(SVGA3dCopyBox) * dirty->num_hits;
	माप_प्रकार commit_size;

	अगर (!dirty->num_hits) अणु
		vmw_cmd_commit(dirty->dev_priv, 0);
		वापस;
	पूर्ण

	अगर (sdirty->sid != stdu->display_srf->res.id) अणु
		काष्ठा SVGA3dCopyBox *blit = (काष्ठा SVGA3dCopyBox *) &cmd[1];

		cmd->header.id = SVGA_3D_CMD_SURFACE_COPY;
		cmd->header.size = माप(cmd->body) + blit_size;
		cmd->body.src.sid = sdirty->sid;
		cmd->body.dest.sid = stdu->display_srf->res.id;
		update = (काष्ठा vmw_stdu_update *) &blit[dirty->num_hits];
		commit_size = माप(*cmd) + blit_size + माप(*update);
		stdu->display_srf->res.res_dirty = true;
	पूर्ण अन्यथा अणु
		update = dirty->cmd;
		commit_size = माप(*update);
	पूर्ण

	vmw_stdu_populate_update(update, stdu->base.unit, sdirty->left,
				 sdirty->right, sdirty->top, sdirty->bottom);

	vmw_cmd_commit(dirty->dev_priv, commit_size);

	sdirty->left = sdirty->top = S32_MAX;
	sdirty->right = sdirty->bottom = S32_MIN;
पूर्ण

/**
 * vmw_kms_stdu_surface_dirty - Dirty part of a surface backed framebuffer
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
पूर्णांक vmw_kms_stdu_surface_dirty(काष्ठा vmw_निजी *dev_priv,
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
	काष्ठा vmw_stdu_dirty sdirty;
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

	अगर (vfbs->is_bo_proxy) अणु
		ret = vmw_kms_update_proxy(srf, clips, num_clips, inc);
		अगर (ret)
			जाओ out_finish;
	पूर्ण

	sdirty.base.fअगरo_commit = vmw_kms_stdu_surface_fअगरo_commit;
	sdirty.base.clip = vmw_kms_stdu_surface_clip;
	sdirty.base.fअगरo_reserve_size = माप(काष्ठा vmw_stdu_surface_copy) +
		माप(SVGA3dCopyBox) * num_clips +
		माप(काष्ठा vmw_stdu_update);
	sdirty.base.crtc = crtc;
	sdirty.sid = srf->id;
	sdirty.left = sdirty.top = S32_MAX;
	sdirty.right = sdirty.bottom = S32_MIN;

	ret = vmw_kms_helper_dirty(dev_priv, framebuffer, clips, vclips,
				   dest_x, dest_y, num_clips, inc,
				   &sdirty.base);
out_finish:
	vmw_kms_helper_validation_finish(dev_priv, शून्य, &val_ctx, out_fence,
					 शून्य);

	वापस ret;

out_unref:
	vmw_validation_unref_lists(&val_ctx);
	वापस ret;
पूर्ण


/*
 *  Screen Target CRTC dispatch table
 */
अटल स्थिर काष्ठा drm_crtc_funcs vmw_stdu_crtc_funcs = अणु
	.gamma_set = vmw_du_crtc_gamma_set,
	.destroy = vmw_stdu_crtc_destroy,
	.reset = vmw_du_crtc_reset,
	.atomic_duplicate_state = vmw_du_crtc_duplicate_state,
	.atomic_destroy_state = vmw_du_crtc_destroy_state,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.get_vblank_counter = vmw_get_vblank_counter,
	.enable_vblank = vmw_enable_vblank,
	.disable_vblank = vmw_disable_vblank,
पूर्ण;



/******************************************************************************
 * Screen Target Display Unit Encoder Functions
 *****************************************************************************/

/**
 * vmw_stdu_encoder_destroy - cleans up the STDU
 *
 * @encoder: used the get the containing STDU
 *
 * vmwgfx cleans up crtc/encoder/connector all at the same समय so technically
 * this can be a no-op.  Nevertheless, it करोesn't hurt of have this in हाल
 * the common KMS code changes and somehow vmw_stdu_crtc_destroy() करोesn't
 * get called.
 */
अटल व्योम vmw_stdu_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	vmw_stdu_destroy(vmw_encoder_to_stdu(encoder));
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs vmw_stdu_encoder_funcs = अणु
	.destroy = vmw_stdu_encoder_destroy,
पूर्ण;



/******************************************************************************
 * Screen Target Display Unit Connector Functions
 *****************************************************************************/

/**
 * vmw_stdu_connector_destroy - cleans up the STDU
 *
 * @connector: used to get the containing STDU
 *
 * vmwgfx cleans up crtc/encoder/connector all at the same समय so technically
 * this can be a no-op.  Nevertheless, it करोesn't hurt of have this in हाल
 * the common KMS code changes and somehow vmw_stdu_crtc_destroy() करोesn't
 * get called.
 */
अटल व्योम vmw_stdu_connector_destroy(काष्ठा drm_connector *connector)
अणु
	vmw_stdu_destroy(vmw_connector_to_stdu(connector));
पूर्ण



अटल स्थिर काष्ठा drm_connector_funcs vmw_stdu_connector_funcs = अणु
	.dpms = vmw_du_connector_dpms,
	.detect = vmw_du_connector_detect,
	.fill_modes = vmw_du_connector_fill_modes,
	.destroy = vmw_stdu_connector_destroy,
	.reset = vmw_du_connector_reset,
	.atomic_duplicate_state = vmw_du_connector_duplicate_state,
	.atomic_destroy_state = vmw_du_connector_destroy_state,
पूर्ण;


अटल स्थिर काष्ठा
drm_connector_helper_funcs vmw_stdu_connector_helper_funcs = अणु
पूर्ण;



/******************************************************************************
 * Screen Target Display Plane Functions
 *****************************************************************************/



/**
 * vmw_stdu_primary_plane_cleanup_fb - Unpins the display surface
 *
 * @plane:  display plane
 * @old_state: Contains the FB to clean up
 *
 * Unpins the display surface
 *
 * Returns 0 on success
 */
अटल व्योम
vmw_stdu_primary_plane_cleanup_fb(काष्ठा drm_plane *plane,
				  काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(old_state);

	अगर (vps->surf)
		WARN_ON(!vps->pinned);

	vmw_du_plane_cleanup_fb(plane, old_state);

	vps->content_fb_type = SAME_AS_DISPLAY;
	vps->cpp = 0;
पूर्ण



/**
 * vmw_stdu_primary_plane_prepare_fb - Readies the display surface
 *
 * @plane:  display plane
 * @new_state: info on the new plane state, including the FB
 *
 * This function allocates a new display surface अगर the content is
 * backed by a buffer object.  The display surface is pinned here, and it'll
 * be unpinned in .cleanup_fb()
 *
 * Returns 0 on success
 */
अटल पूर्णांक
vmw_stdu_primary_plane_prepare_fb(काष्ठा drm_plane *plane,
				  काष्ठा drm_plane_state *new_state)
अणु
	काष्ठा vmw_निजी *dev_priv = vmw_priv(plane->dev);
	काष्ठा drm_framebuffer *new_fb = new_state->fb;
	काष्ठा vmw_framebuffer *vfb;
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(new_state);
	क्रमागत stdu_content_type new_content_type;
	काष्ठा vmw_framebuffer_surface *new_vfbs;
	uपूर्णांक32_t hdisplay = new_state->crtc_w, vdisplay = new_state->crtc_h;
	पूर्णांक ret;

	/* No FB to prepare */
	अगर (!new_fb) अणु
		अगर (vps->surf) अणु
			WARN_ON(vps->pinned != 0);
			vmw_surface_unreference(&vps->surf);
		पूर्ण

		वापस 0;
	पूर्ण

	vfb = vmw_framebuffer_to_vfb(new_fb);
	new_vfbs = (vfb->bo) ? शून्य : vmw_framebuffer_to_vfbs(new_fb);

	अगर (new_vfbs &&
	    new_vfbs->surface->metadata.base_size.width == hdisplay &&
	    new_vfbs->surface->metadata.base_size.height == vdisplay)
		new_content_type = SAME_AS_DISPLAY;
	अन्यथा अगर (vfb->bo)
		new_content_type = SEPARATE_BO;
	अन्यथा
		new_content_type = SEPARATE_SURFACE;

	अगर (new_content_type != SAME_AS_DISPLAY) अणु
		काष्ठा vmw_surface_metadata metadata = अणु0पूर्ण;

		/*
		 * If content buffer is a buffer object, then we have to
		 * स्थिरruct surface info
		 */
		अगर (new_content_type == SEPARATE_BO) अणु

			चयन (new_fb->क्रमmat->cpp[0]*8) अणु
			हाल 32:
				metadata.क्रमmat = SVGA3D_X8R8G8B8;
				अवरोध;

			हाल 16:
				metadata.क्रमmat = SVGA3D_R5G6B5;
				अवरोध;

			हाल 8:
				metadata.क्रमmat = SVGA3D_P8;
				अवरोध;

			शेष:
				DRM_ERROR("Invalid format\n");
				वापस -EINVAL;
			पूर्ण

			metadata.mip_levels[0] = 1;
			metadata.num_sizes = 1;
			metadata.scanout = true;
		पूर्ण अन्यथा अणु
			metadata = new_vfbs->surface->metadata;
		पूर्ण

		metadata.base_size.width = hdisplay;
		metadata.base_size.height = vdisplay;
		metadata.base_size.depth = 1;

		अगर (vps->surf) अणु
			काष्ठा drm_vmw_size cur_base_size =
				vps->surf->metadata.base_size;

			अगर (cur_base_size.width != metadata.base_size.width ||
			    cur_base_size.height != metadata.base_size.height ||
			    vps->surf->metadata.क्रमmat != metadata.क्रमmat) अणु
				WARN_ON(vps->pinned != 0);
				vmw_surface_unreference(&vps->surf);
			पूर्ण

		पूर्ण

		अगर (!vps->surf) अणु
			ret = vmw_gb_surface_define(dev_priv, 0, &metadata,
						    &vps->surf);
			अगर (ret != 0) अणु
				DRM_ERROR("Couldn't allocate STDU surface.\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * prepare_fb and clean_fb should only take care of pinning
		 * and unpinning.  References are tracked by state objects.
		 * The only समय we add a reference in prepare_fb is अगर the
		 * state object करोesn't have a reference to begin with
		 */
		अगर (vps->surf) अणु
			WARN_ON(vps->pinned != 0);
			vmw_surface_unreference(&vps->surf);
		पूर्ण

		vps->surf = vmw_surface_reference(new_vfbs->surface);
	पूर्ण

	अगर (vps->surf) अणु

		/* Pin new surface beक्रमe flipping */
		ret = vmw_resource_pin(&vps->surf->res, false);
		अगर (ret)
			जाओ out_srf_unref;

		vps->pinned++;
	पूर्ण

	vps->content_fb_type = new_content_type;

	/*
	 * This should only happen अगर the buffer object is too large to create a
	 * proxy surface क्रम.
	 * If we are a 2D VM with a buffer object then we have to use CPU blit
	 * so cache these mappings
	 */
	अगर (vps->content_fb_type == SEPARATE_BO &&
	    !(dev_priv->capabilities & SVGA_CAP_3D))
		vps->cpp = new_fb->pitches[0] / new_fb->width;

	वापस 0;

out_srf_unref:
	vmw_surface_unreference(&vps->surf);
	वापस ret;
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_bo_fअगरo_size(काष्ठा vmw_du_update_plane *update,
				      uपूर्णांक32_t num_hits)
अणु
	वापस माप(काष्ठा vmw_stdu_dma) + माप(SVGA3dCopyBox) * num_hits +
		माप(SVGA3dCmdSurfaceDMASuffix) +
		माप(काष्ठा vmw_stdu_update);
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_bo_fअगरo_size_cpu(काष्ठा vmw_du_update_plane *update,
					  uपूर्णांक32_t num_hits)
अणु
	वापस माप(काष्ठा vmw_stdu_update_gb_image) +
		माप(काष्ठा vmw_stdu_update);
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_bo_populate_dma(काष्ठा vmw_du_update_plane  *update,
					 व्योम *cmd, uपूर्णांक32_t num_hits)
अणु
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा vmw_framebuffer_bo *vfbbo;
	काष्ठा vmw_stdu_dma *cmd_dma = cmd;

	stdu = container_of(update->du, typeof(*stdu), base);
	vfbbo = container_of(update->vfb, typeof(*vfbbo), base);

	cmd_dma->header.id = SVGA_3D_CMD_SURFACE_DMA;
	cmd_dma->header.size = माप(cmd_dma->body) +
		माप(काष्ठा SVGA3dCopyBox) * num_hits +
		माप(SVGA3dCmdSurfaceDMASuffix);
	vmw_bo_get_guest_ptr(&vfbbo->buffer->base, &cmd_dma->body.guest.ptr);
	cmd_dma->body.guest.pitch = update->vfb->base.pitches[0];
	cmd_dma->body.host.sid = stdu->display_srf->res.id;
	cmd_dma->body.host.face = 0;
	cmd_dma->body.host.mipmap = 0;
	cmd_dma->body.transfer = SVGA3D_WRITE_HOST_VRAM;

	वापस माप(*cmd_dma);
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_bo_populate_clip(काष्ठा vmw_du_update_plane  *update,
					  व्योम *cmd, काष्ठा drm_rect *clip,
					  uपूर्णांक32_t fb_x, uपूर्णांक32_t fb_y)
अणु
	काष्ठा SVGA3dCopyBox *box = cmd;

	box->srcx = fb_x;
	box->srcy = fb_y;
	box->srcz = 0;
	box->x = clip->x1;
	box->y = clip->y1;
	box->z = 0;
	box->w = drm_rect_width(clip);
	box->h = drm_rect_height(clip);
	box->d = 1;

	वापस माप(*box);
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_bo_populate_update(काष्ठा vmw_du_update_plane  *update,
					    व्योम *cmd, काष्ठा drm_rect *bb)
अणु
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा vmw_framebuffer_bo *vfbbo;
	SVGA3dCmdSurfaceDMASuffix *suffix = cmd;

	stdu = container_of(update->du, typeof(*stdu), base);
	vfbbo = container_of(update->vfb, typeof(*vfbbo), base);

	suffix->suffixSize = माप(*suffix);
	suffix->maximumOffset = vfbbo->buffer->base.base.size;

	vmw_stdu_populate_update(&suffix[1], stdu->base.unit, bb->x1, bb->x2,
				 bb->y1, bb->y2);

	वापस माप(*suffix) + माप(काष्ठा vmw_stdu_update);
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_bo_pre_clip_cpu(काष्ठा vmw_du_update_plane  *update,
					 व्योम *cmd, uपूर्णांक32_t num_hits)
अणु
	काष्ठा vmw_du_update_plane_buffer *bo_update =
		container_of(update, typeof(*bo_update), base);

	bo_update->fb_left = पूर्णांक_उच्च;
	bo_update->fb_top = पूर्णांक_उच्च;

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_bo_clip_cpu(काष्ठा vmw_du_update_plane  *update,
				     व्योम *cmd, काष्ठा drm_rect *clip,
				     uपूर्णांक32_t fb_x, uपूर्णांक32_t fb_y)
अणु
	काष्ठा vmw_du_update_plane_buffer *bo_update =
		container_of(update, typeof(*bo_update), base);

	bo_update->fb_left = min_t(पूर्णांक, bo_update->fb_left, fb_x);
	bo_update->fb_top = min_t(पूर्णांक, bo_update->fb_top, fb_y);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t
vmw_stdu_bo_populate_update_cpu(काष्ठा vmw_du_update_plane  *update, व्योम *cmd,
				काष्ठा drm_rect *bb)
अणु
	काष्ठा vmw_du_update_plane_buffer *bo_update;
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा vmw_framebuffer_bo *vfbbo;
	काष्ठा vmw_dअगरf_cpy dअगरf = VMW_CPU_BLIT_DIFF_INITIALIZER(0);
	काष्ठा vmw_stdu_update_gb_image *cmd_img = cmd;
	काष्ठा vmw_stdu_update *cmd_update;
	काष्ठा tपंचांग_buffer_object *src_bo, *dst_bo;
	u32 src_offset, dst_offset;
	s32 src_pitch, dst_pitch;
	s32 width, height;

	bo_update = container_of(update, typeof(*bo_update), base);
	stdu = container_of(update->du, typeof(*stdu), base);
	vfbbo = container_of(update->vfb, typeof(*vfbbo), base);

	width = bb->x2 - bb->x1;
	height = bb->y2 - bb->y1;

	dअगरf.cpp = stdu->cpp;

	dst_bo = &stdu->display_srf->res.backup->base;
	dst_pitch = stdu->display_srf->metadata.base_size.width * stdu->cpp;
	dst_offset = bb->y1 * dst_pitch + bb->x1 * stdu->cpp;

	src_bo = &vfbbo->buffer->base;
	src_pitch = update->vfb->base.pitches[0];
	src_offset = bo_update->fb_top * src_pitch + bo_update->fb_left *
		stdu->cpp;

	(व्योम) vmw_bo_cpu_blit(dst_bo, dst_offset, dst_pitch, src_bo,
			       src_offset, src_pitch, width * stdu->cpp, height,
			       &dअगरf);

	अगर (drm_rect_visible(&dअगरf.rect)) अणु
		SVGA3dBox *box = &cmd_img->body.box;

		cmd_img->header.id = SVGA_3D_CMD_UPDATE_GB_IMAGE;
		cmd_img->header.size = माप(cmd_img->body);
		cmd_img->body.image.sid = stdu->display_srf->res.id;
		cmd_img->body.image.face = 0;
		cmd_img->body.image.mipmap = 0;

		box->x = dअगरf.rect.x1;
		box->y = dअगरf.rect.y1;
		box->z = 0;
		box->w = drm_rect_width(&dअगरf.rect);
		box->h = drm_rect_height(&dअगरf.rect);
		box->d = 1;

		cmd_update = (काष्ठा vmw_stdu_update *)&cmd_img[1];
		vmw_stdu_populate_update(cmd_update, stdu->base.unit,
					 dअगरf.rect.x1, dअगरf.rect.x2,
					 dअगरf.rect.y1, dअगरf.rect.y2);

		वापस माप(*cmd_img) + माप(*cmd_update);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_stdu_plane_update_bo - Update display unit क्रम bo backed fb.
 * @dev_priv: device निजी.
 * @plane: plane state.
 * @old_state: old plane state.
 * @vfb: framebuffer which is blitted to display unit.
 * @out_fence: If non-शून्य, will वापस a ref-counted poपूर्णांकer to vmw_fence_obj.
 *             The वापसed fence poपूर्णांकer may be शून्य in which हाल the device
 *             has alपढ़ोy synchronized.
 *
 * Return: 0 on success or a negative error code on failure.
 */
अटल पूर्णांक vmw_stdu_plane_update_bo(काष्ठा vmw_निजी *dev_priv,
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
	bo_update.base.cpu_blit = !(dev_priv->capabilities & SVGA_CAP_3D);
	bo_update.base.पूर्णांकr = false;

	/*
	 * VM without 3D support करोn't have surface DMA command and framebuffer
	 * should be moved out of VRAM.
	 */
	अगर (bo_update.base.cpu_blit) अणु
		bo_update.base.calc_fअगरo_size = vmw_stdu_bo_fअगरo_size_cpu;
		bo_update.base.pre_clip = vmw_stdu_bo_pre_clip_cpu;
		bo_update.base.clip = vmw_stdu_bo_clip_cpu;
		bo_update.base.post_clip = vmw_stdu_bo_populate_update_cpu;
	पूर्ण अन्यथा अणु
		bo_update.base.calc_fअगरo_size = vmw_stdu_bo_fअगरo_size;
		bo_update.base.pre_clip = vmw_stdu_bo_populate_dma;
		bo_update.base.clip = vmw_stdu_bo_populate_clip;
		bo_update.base.post_clip = vmw_stdu_bo_populate_update;
	पूर्ण

	वापस vmw_du_helper_plane_update(&bo_update.base);
पूर्ण

अटल uपूर्णांक32_t
vmw_stdu_surface_fअगरo_size_same_display(काष्ठा vmw_du_update_plane *update,
					uपूर्णांक32_t num_hits)
अणु
	काष्ठा vmw_framebuffer_surface *vfbs;
	uपूर्णांक32_t size = 0;

	vfbs = container_of(update->vfb, typeof(*vfbs), base);

	अगर (vfbs->is_bo_proxy)
		size += माप(काष्ठा vmw_stdu_update_gb_image) * num_hits;

	size += माप(काष्ठा vmw_stdu_update);

	वापस size;
पूर्ण

अटल uपूर्णांक32_t vmw_stdu_surface_fअगरo_size(काष्ठा vmw_du_update_plane *update,
					   uपूर्णांक32_t num_hits)
अणु
	काष्ठा vmw_framebuffer_surface *vfbs;
	uपूर्णांक32_t size = 0;

	vfbs = container_of(update->vfb, typeof(*vfbs), base);

	अगर (vfbs->is_bo_proxy)
		size += माप(काष्ठा vmw_stdu_update_gb_image) * num_hits;

	size += माप(काष्ठा vmw_stdu_surface_copy) + माप(SVGA3dCopyBox) *
		num_hits + माप(काष्ठा vmw_stdu_update);

	वापस size;
पूर्ण

अटल uपूर्णांक32_t
vmw_stdu_surface_update_proxy(काष्ठा vmw_du_update_plane *update, व्योम *cmd)
अणु
	काष्ठा vmw_framebuffer_surface *vfbs;
	काष्ठा drm_plane_state *state = update->plane->state;
	काष्ठा drm_plane_state *old_state = update->old_state;
	काष्ठा vmw_stdu_update_gb_image *cmd_update = cmd;
	काष्ठा drm_atomic_helper_damage_iter iter;
	काष्ठा drm_rect clip;
	uपूर्णांक32_t copy_size = 0;

	vfbs = container_of(update->vfb, typeof(*vfbs), base);

	/*
	 * proxy surface is special where a buffer object type fb is wrapped
	 * in a surface and need an update gb image command to sync with device.
	 */
	drm_atomic_helper_damage_iter_init(&iter, old_state, state);
	drm_atomic_क्रम_each_plane_damage(&iter, &clip) अणु
		SVGA3dBox *box = &cmd_update->body.box;

		cmd_update->header.id = SVGA_3D_CMD_UPDATE_GB_IMAGE;
		cmd_update->header.size = माप(cmd_update->body);
		cmd_update->body.image.sid = vfbs->surface->res.id;
		cmd_update->body.image.face = 0;
		cmd_update->body.image.mipmap = 0;

		box->x = clip.x1;
		box->y = clip.y1;
		box->z = 0;
		box->w = drm_rect_width(&clip);
		box->h = drm_rect_height(&clip);
		box->d = 1;

		copy_size += माप(*cmd_update);
		cmd_update++;
	पूर्ण

	वापस copy_size;
पूर्ण

अटल uपूर्णांक32_t
vmw_stdu_surface_populate_copy(काष्ठा vmw_du_update_plane  *update, व्योम *cmd,
			       uपूर्णांक32_t num_hits)
अणु
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा vmw_framebuffer_surface *vfbs;
	काष्ठा vmw_stdu_surface_copy *cmd_copy = cmd;

	stdu = container_of(update->du, typeof(*stdu), base);
	vfbs = container_of(update->vfb, typeof(*vfbs), base);

	cmd_copy->header.id = SVGA_3D_CMD_SURFACE_COPY;
	cmd_copy->header.size = माप(cmd_copy->body) + माप(SVGA3dCopyBox) *
		num_hits;
	cmd_copy->body.src.sid = vfbs->surface->res.id;
	cmd_copy->body.dest.sid = stdu->display_srf->res.id;

	वापस माप(*cmd_copy);
पूर्ण

अटल uपूर्णांक32_t
vmw_stdu_surface_populate_clip(काष्ठा vmw_du_update_plane  *update, व्योम *cmd,
			       काष्ठा drm_rect *clip, uपूर्णांक32_t fb_x,
			       uपूर्णांक32_t fb_y)
अणु
	काष्ठा SVGA3dCopyBox *box = cmd;

	box->srcx = fb_x;
	box->srcy = fb_y;
	box->srcz = 0;
	box->x = clip->x1;
	box->y = clip->y1;
	box->z = 0;
	box->w = drm_rect_width(clip);
	box->h = drm_rect_height(clip);
	box->d = 1;

	वापस माप(*box);
पूर्ण

अटल uपूर्णांक32_t
vmw_stdu_surface_populate_update(काष्ठा vmw_du_update_plane  *update, व्योम *cmd,
				 काष्ठा drm_rect *bb)
अणु
	vmw_stdu_populate_update(cmd, update->du->unit, bb->x1, bb->x2, bb->y1,
				 bb->y2);

	वापस माप(काष्ठा vmw_stdu_update);
पूर्ण

/**
 * vmw_stdu_plane_update_surface - Update display unit क्रम surface backed fb
 * @dev_priv: Device निजी
 * @plane: Plane state
 * @old_state: Old plane state
 * @vfb: Framebuffer which is blitted to display unit
 * @out_fence: If non-शून्य, will वापस a ref-counted poपूर्णांकer to vmw_fence_obj.
 *             The वापसed fence poपूर्णांकer may be शून्य in which हाल the device
 *             has alपढ़ोy synchronized.
 *
 * Return: 0 on success or a negative error code on failure.
 */
अटल पूर्णांक vmw_stdu_plane_update_surface(काष्ठा vmw_निजी *dev_priv,
					 काष्ठा drm_plane *plane,
					 काष्ठा drm_plane_state *old_state,
					 काष्ठा vmw_framebuffer *vfb,
					 काष्ठा vmw_fence_obj **out_fence)
अणु
	काष्ठा vmw_du_update_plane srf_update;
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा vmw_framebuffer_surface *vfbs;

	stdu = vmw_crtc_to_stdu(plane->state->crtc);
	vfbs = container_of(vfb, typeof(*vfbs), base);

	स_रखो(&srf_update, 0, माप(काष्ठा vmw_du_update_plane));
	srf_update.plane = plane;
	srf_update.old_state = old_state;
	srf_update.dev_priv = dev_priv;
	srf_update.du = vmw_crtc_to_du(plane->state->crtc);
	srf_update.vfb = vfb;
	srf_update.out_fence = out_fence;
	srf_update.mutex = &dev_priv->cmdbuf_mutex;
	srf_update.cpu_blit = false;
	srf_update.पूर्णांकr = true;

	अगर (vfbs->is_bo_proxy)
		srf_update.post_prepare = vmw_stdu_surface_update_proxy;

	अगर (vfbs->surface->res.id != stdu->display_srf->res.id) अणु
		srf_update.calc_fअगरo_size = vmw_stdu_surface_fअगरo_size;
		srf_update.pre_clip = vmw_stdu_surface_populate_copy;
		srf_update.clip = vmw_stdu_surface_populate_clip;
	पूर्ण अन्यथा अणु
		srf_update.calc_fअगरo_size =
			vmw_stdu_surface_fअगरo_size_same_display;
	पूर्ण

	srf_update.post_clip = vmw_stdu_surface_populate_update;

	वापस vmw_du_helper_plane_update(&srf_update);
पूर्ण

/**
 * vmw_stdu_primary_plane_atomic_update - क्रमmally चयनes STDU to new plane
 * @plane: display plane
 * @old_state: Only used to get crtc info
 *
 * Formally update stdu->display_srf to the new plane, and bind the new
 * plane STDU.  This function is called during the commit phase when
 * all the preparation have been करोne and all the configurations have
 * been checked.
 */
अटल व्योम
vmw_stdu_primary_plane_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state, plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state, plane);
	काष्ठा vmw_plane_state *vps = vmw_plane_state_to_vps(new_state);
	काष्ठा drm_crtc *crtc = new_state->crtc;
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा vmw_fence_obj *fence = शून्य;
	काष्ठा vmw_निजी *dev_priv;
	पूर्णांक ret;

	/* If हाल of device error, मुख्यtain consistent atomic state */
	अगर (crtc && new_state->fb) अणु
		काष्ठा vmw_framebuffer *vfb =
			vmw_framebuffer_to_vfb(new_state->fb);
		stdu = vmw_crtc_to_stdu(crtc);
		dev_priv = vmw_priv(crtc->dev);

		stdu->display_srf = vps->surf;
		stdu->content_fb_type = vps->content_fb_type;
		stdu->cpp = vps->cpp;

		ret = vmw_stdu_bind_st(dev_priv, stdu, &stdu->display_srf->res);
		अगर (ret)
			DRM_ERROR("Failed to bind surface to STDU.\n");

		अगर (vfb->bo)
			ret = vmw_stdu_plane_update_bo(dev_priv, plane,
						       old_state, vfb, &fence);
		अन्यथा
			ret = vmw_stdu_plane_update_surface(dev_priv, plane,
							    old_state, vfb,
							    &fence);
		अगर (ret)
			DRM_ERROR("Failed to update STDU.\n");
	पूर्ण अन्यथा अणु
		crtc = old_state->crtc;
		stdu = vmw_crtc_to_stdu(crtc);
		dev_priv = vmw_priv(crtc->dev);

		/* Blank STDU when fb and crtc are शून्य */
		अगर (!stdu->defined)
			वापस;

		ret = vmw_stdu_bind_st(dev_priv, stdu, शून्य);
		अगर (ret)
			DRM_ERROR("Failed to blank STDU\n");

		ret = vmw_stdu_update_st(dev_priv, stdu);
		अगर (ret)
			DRM_ERROR("Failed to update STDU.\n");

		वापस;
	पूर्ण

	/* In हाल of error, vblank event is send in vmw_du_crtc_atomic_flush */
	event = crtc->state->event;
	अगर (event && fence) अणु
		काष्ठा drm_file *file_priv = event->base.file_priv;

		ret = vmw_event_fence_action_queue(file_priv,
						   fence,
						   &event->base,
						   &event->event.vbl.tv_sec,
						   &event->event.vbl.tv_usec,
						   true);
		अगर (ret)
			DRM_ERROR("Failed to queue event on fence.\n");
		अन्यथा
			crtc->state->event = शून्य;
	पूर्ण

	अगर (fence)
		vmw_fence_obj_unreference(&fence);
पूर्ण


अटल स्थिर काष्ठा drm_plane_funcs vmw_stdu_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = vmw_du_primary_plane_destroy,
	.reset = vmw_du_plane_reset,
	.atomic_duplicate_state = vmw_du_plane_duplicate_state,
	.atomic_destroy_state = vmw_du_plane_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs vmw_stdu_cursor_funcs = अणु
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
drm_plane_helper_funcs vmw_stdu_cursor_plane_helper_funcs = अणु
	.atomic_check = vmw_du_cursor_plane_atomic_check,
	.atomic_update = vmw_du_cursor_plane_atomic_update,
	.prepare_fb = vmw_du_cursor_plane_prepare_fb,
	.cleanup_fb = vmw_du_plane_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा
drm_plane_helper_funcs vmw_stdu_primary_plane_helper_funcs = अणु
	.atomic_check = vmw_du_primary_plane_atomic_check,
	.atomic_update = vmw_stdu_primary_plane_atomic_update,
	.prepare_fb = vmw_stdu_primary_plane_prepare_fb,
	.cleanup_fb = vmw_stdu_primary_plane_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs vmw_stdu_crtc_helper_funcs = अणु
	.prepare = vmw_stdu_crtc_helper_prepare,
	.mode_set_nofb = vmw_stdu_crtc_mode_set_nofb,
	.atomic_check = vmw_du_crtc_atomic_check,
	.atomic_begin = vmw_du_crtc_atomic_begin,
	.atomic_flush = vmw_du_crtc_atomic_flush,
	.atomic_enable = vmw_stdu_crtc_atomic_enable,
	.atomic_disable = vmw_stdu_crtc_atomic_disable,
पूर्ण;


/**
 * vmw_stdu_init - Sets up a Screen Target Display Unit
 *
 * @dev_priv: VMW DRM device
 * @unit: unit number range from 0 to VMWGFX_NUM_DISPLAY_UNITS
 *
 * This function is called once per CRTC, and allocates one Screen Target
 * display unit to represent that CRTC.  Since the SVGA device करोes not separate
 * out encoder and connector, they are represented as part of the STDU as well.
 */
अटल पूर्णांक vmw_stdu_init(काष्ठा vmw_निजी *dev_priv, अचिन्हित unit)
अणु
	काष्ठा vmw_screen_target_display_unit *stdu;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_plane *primary, *cursor;
	काष्ठा drm_crtc *crtc;
	पूर्णांक    ret;


	stdu = kzalloc(माप(*stdu), GFP_KERNEL);
	अगर (!stdu)
		वापस -ENOMEM;

	stdu->base.unit = unit;
	crtc = &stdu->base.crtc;
	encoder = &stdu->base.encoder;
	connector = &stdu->base.connector;
	primary = &stdu->base.primary;
	cursor = &stdu->base.cursor;

	stdu->base.pref_active = (unit == 0);
	stdu->base.pref_width  = dev_priv->initial_width;
	stdu->base.pref_height = dev_priv->initial_height;
	stdu->base.is_implicit = false;

	/* Initialize primary plane */
	ret = drm_universal_plane_init(dev, primary,
				       0, &vmw_stdu_plane_funcs,
				       vmw_primary_plane_क्रमmats,
				       ARRAY_SIZE(vmw_primary_plane_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize primary plane");
		जाओ err_मुक्त;
	पूर्ण

	drm_plane_helper_add(primary, &vmw_stdu_primary_plane_helper_funcs);
	drm_plane_enable_fb_damage_clips(primary);

	/* Initialize cursor plane */
	ret = drm_universal_plane_init(dev, cursor,
			0, &vmw_stdu_cursor_funcs,
			vmw_cursor_plane_क्रमmats,
			ARRAY_SIZE(vmw_cursor_plane_क्रमmats),
			शून्य, DRM_PLANE_TYPE_CURSOR, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize cursor plane");
		drm_plane_cleanup(&stdu->base.primary);
		जाओ err_मुक्त;
	पूर्ण

	drm_plane_helper_add(cursor, &vmw_stdu_cursor_plane_helper_funcs);

	ret = drm_connector_init(dev, connector, &vmw_stdu_connector_funcs,
				 DRM_MODE_CONNECTOR_VIRTUAL);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector\n");
		जाओ err_मुक्त;
	पूर्ण

	drm_connector_helper_add(connector, &vmw_stdu_connector_helper_funcs);
	connector->status = vmw_du_connector_detect(connector, false);

	ret = drm_encoder_init(dev, encoder, &vmw_stdu_encoder_funcs,
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

	ret = drm_crtc_init_with_planes(dev, crtc, &stdu->base.primary,
					&stdu->base.cursor,
					&vmw_stdu_crtc_funcs, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize CRTC\n");
		जाओ err_मुक्त_unरेजिस्टर;
	पूर्ण

	drm_crtc_helper_add(crtc, &vmw_stdu_crtc_helper_funcs);

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
	kमुक्त(stdu);
	वापस ret;
पूर्ण



/**
 *  vmw_stdu_destroy - Cleans up a vmw_screen_target_display_unit
 *
 *  @stdu:  Screen Target Display Unit to be destroyed
 *
 *  Clean up after vmw_stdu_init
 */
अटल व्योम vmw_stdu_destroy(काष्ठा vmw_screen_target_display_unit *stdu)
अणु
	vmw_du_cleanup(&stdu->base);
	kमुक्त(stdu);
पूर्ण



/******************************************************************************
 * Screen Target Display KMS Functions
 *
 * These functions are called by the common KMS code in vmwgfx_kms.c
 *****************************************************************************/

/**
 * vmw_kms_stdu_init_display - Initializes a Screen Target based display
 *
 * @dev_priv: VMW DRM device
 *
 * This function initialize a Screen Target based display device.  It checks
 * the capability bits to make sure the underlying hardware can support
 * screen tarमाला_लो, and then creates the maximum number of CRTCs, a.k.a Display
 * Units, as supported by the display hardware.
 *
 * RETURNS:
 * 0 on success, error code otherwise
 */
पूर्णांक vmw_kms_stdu_init_display(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक i, ret;


	/* Do nothing अगर Screen Target support is turned off */
	अगर (!VMWGFX_ENABLE_SCREEN_TARGET_OTABLE || !dev_priv->has_mob)
		वापस -ENOSYS;

	अगर (!(dev_priv->capabilities & SVGA_CAP_GBOBJECTS))
		वापस -ENOSYS;

	ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	अगर (unlikely(ret != 0))
		वापस ret;

	dev_priv->active_display_unit = vmw_du_screen_target;

	क्रम (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i) अणु
		ret = vmw_stdu_init(dev_priv, i);

		अगर (unlikely(ret != 0)) अणु
			DRM_ERROR("Failed to initialize STDU %d", i);
			वापस ret;
		पूर्ण
	पूर्ण

	drm_mode_config_reset(dev);

	DRM_INFO("Screen Target Display device initialized\n");

	वापस 0;
पूर्ण
