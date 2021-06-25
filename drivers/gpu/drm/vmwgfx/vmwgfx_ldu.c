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
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "vmwgfx_kms.h"

#घोषणा vmw_crtc_to_ldu(x) \
	container_of(x, काष्ठा vmw_legacy_display_unit, base.crtc)
#घोषणा vmw_encoder_to_ldu(x) \
	container_of(x, काष्ठा vmw_legacy_display_unit, base.encoder)
#घोषणा vmw_connector_to_ldu(x) \
	container_of(x, काष्ठा vmw_legacy_display_unit, base.connector)

काष्ठा vmw_legacy_display अणु
	काष्ठा list_head active;

	अचिन्हित num_active;
	अचिन्हित last_num_active;

	काष्ठा vmw_framebuffer *fb;
पूर्ण;

/*
 * Display unit using the legacy रेजिस्टर पूर्णांकerface.
 */
काष्ठा vmw_legacy_display_unit अणु
	काष्ठा vmw_display_unit base;

	काष्ठा list_head active;
पूर्ण;

अटल व्योम vmw_ldu_destroy(काष्ठा vmw_legacy_display_unit *ldu)
अणु
	list_del_init(&ldu->active);
	vmw_du_cleanup(&ldu->base);
	kमुक्त(ldu);
पूर्ण


/*
 * Legacy Display Unit CRTC functions
 */

अटल व्योम vmw_ldu_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	vmw_ldu_destroy(vmw_crtc_to_ldu(crtc));
पूर्ण

अटल पूर्णांक vmw_ldu_commit_list(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_legacy_display *lds = dev_priv->ldu_priv;
	काष्ठा vmw_legacy_display_unit *entry;
	काष्ठा drm_framebuffer *fb = शून्य;
	काष्ठा drm_crtc *crtc = शून्य;
	पूर्णांक i;

	/* If there is no display topology the host just assumes
	 * that the guest will set the same layout as the host.
	 */
	अगर (!(dev_priv->capabilities & SVGA_CAP_DISPLAY_TOPOLOGY)) अणु
		पूर्णांक w = 0, h = 0;
		list_क्रम_each_entry(entry, &lds->active, active) अणु
			crtc = &entry->base.crtc;
			w = max(w, crtc->x + crtc->mode.hdisplay);
			h = max(h, crtc->y + crtc->mode.vdisplay);
		पूर्ण

		अगर (crtc == शून्य)
			वापस 0;
		fb = crtc->primary->state->fb;

		वापस vmw_kms_ग_लिखो_svga(dev_priv, w, h, fb->pitches[0],
					  fb->क्रमmat->cpp[0] * 8,
					  fb->क्रमmat->depth);
	पूर्ण

	अगर (!list_empty(&lds->active)) अणु
		entry = list_entry(lds->active.next, typeof(*entry), active);
		fb = entry->base.crtc.primary->state->fb;

		vmw_kms_ग_लिखो_svga(dev_priv, fb->width, fb->height, fb->pitches[0],
				   fb->क्रमmat->cpp[0] * 8, fb->क्रमmat->depth);
	पूर्ण

	/* Make sure we always show something. */
	vmw_ग_लिखो(dev_priv, SVGA_REG_NUM_GUEST_DISPLAYS,
		  lds->num_active ? lds->num_active : 1);

	i = 0;
	list_क्रम_each_entry(entry, &lds->active, active) अणु
		crtc = &entry->base.crtc;

		vmw_ग_लिखो(dev_priv, SVGA_REG_DISPLAY_ID, i);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DISPLAY_IS_PRIMARY, !i);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DISPLAY_POSITION_X, crtc->x);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DISPLAY_POSITION_Y, crtc->y);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DISPLAY_WIDTH, crtc->mode.hdisplay);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DISPLAY_HEIGHT, crtc->mode.vdisplay);

		i++;
	पूर्ण

	BUG_ON(i != lds->num_active);

	lds->last_num_active = lds->num_active;

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_ldu_del_active(काष्ठा vmw_निजी *vmw_priv,
			      काष्ठा vmw_legacy_display_unit *ldu)
अणु
	काष्ठा vmw_legacy_display *ld = vmw_priv->ldu_priv;
	अगर (list_empty(&ldu->active))
		वापस 0;

	/* Must init otherwise list_empty(&ldu->active) will not work. */
	list_del_init(&ldu->active);
	अगर (--(ld->num_active) == 0) अणु
		BUG_ON(!ld->fb);
		अगर (ld->fb->unpin)
			ld->fb->unpin(ld->fb);
		ld->fb = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vmw_ldu_add_active(काष्ठा vmw_निजी *vmw_priv,
			      काष्ठा vmw_legacy_display_unit *ldu,
			      काष्ठा vmw_framebuffer *vfb)
अणु
	काष्ठा vmw_legacy_display *ld = vmw_priv->ldu_priv;
	काष्ठा vmw_legacy_display_unit *entry;
	काष्ठा list_head *at;

	BUG_ON(!ld->num_active && ld->fb);
	अगर (vfb != ld->fb) अणु
		अगर (ld->fb && ld->fb->unpin)
			ld->fb->unpin(ld->fb);
		vmw_svga_enable(vmw_priv);
		अगर (vfb->pin)
			vfb->pin(vfb);
		ld->fb = vfb;
	पूर्ण

	अगर (!list_empty(&ldu->active))
		वापस 0;

	at = &ld->active;
	list_क्रम_each_entry(entry, &ld->active, active) अणु
		अगर (entry->base.unit > ldu->base.unit)
			अवरोध;

		at = &entry->active;
	पूर्ण

	list_add(&ldu->active, at);

	ld->num_active++;

	वापस 0;
पूर्ण

/**
 * vmw_ldu_crtc_mode_set_nofb - Enable svga
 *
 * @crtc: CRTC associated with the new screen
 *
 * For LDU, just enable the svga
 */
अटल व्योम vmw_ldu_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
पूर्ण

/**
 * vmw_ldu_crtc_atomic_enable - Noop
 *
 * @crtc: CRTC associated with the new screen
 * @state: Unused
 *
 * This is called after a mode set has been completed.  Here's
 * usually a good place to call vmw_ldu_add_active/vmw_ldu_del_active
 * but since क्रम LDU the display plane is बंदly tied to the
 * CRTC, it makes more sense to करो those at plane update समय.
 */
अटल व्योम vmw_ldu_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
पूर्ण

/**
 * vmw_ldu_crtc_atomic_disable - Turns off CRTC
 *
 * @crtc: CRTC to be turned off
 * @state: Unused
 */
अटल व्योम vmw_ldu_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs vmw_legacy_crtc_funcs = अणु
	.gamma_set = vmw_du_crtc_gamma_set,
	.destroy = vmw_ldu_crtc_destroy,
	.reset = vmw_du_crtc_reset,
	.atomic_duplicate_state = vmw_du_crtc_duplicate_state,
	.atomic_destroy_state = vmw_du_crtc_destroy_state,
	.set_config = drm_atomic_helper_set_config,
	.get_vblank_counter = vmw_get_vblank_counter,
	.enable_vblank = vmw_enable_vblank,
	.disable_vblank = vmw_disable_vblank,
पूर्ण;


/*
 * Legacy Display Unit encoder functions
 */

अटल व्योम vmw_ldu_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	vmw_ldu_destroy(vmw_encoder_to_ldu(encoder));
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs vmw_legacy_encoder_funcs = अणु
	.destroy = vmw_ldu_encoder_destroy,
पूर्ण;

/*
 * Legacy Display Unit connector functions
 */

अटल व्योम vmw_ldu_connector_destroy(काष्ठा drm_connector *connector)
अणु
	vmw_ldu_destroy(vmw_connector_to_ldu(connector));
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs vmw_legacy_connector_funcs = अणु
	.dpms = vmw_du_connector_dpms,
	.detect = vmw_du_connector_detect,
	.fill_modes = vmw_du_connector_fill_modes,
	.destroy = vmw_ldu_connector_destroy,
	.reset = vmw_du_connector_reset,
	.atomic_duplicate_state = vmw_du_connector_duplicate_state,
	.atomic_destroy_state = vmw_du_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा
drm_connector_helper_funcs vmw_ldu_connector_helper_funcs = अणु
पूर्ण;

/*
 * Legacy Display Plane Functions
 */

अटल व्योम
vmw_ldu_primary_plane_atomic_update(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_legacy_display_unit *ldu;
	काष्ठा vmw_framebuffer *vfb;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_crtc *crtc = new_state->crtc ?: old_state->crtc;


	ldu = vmw_crtc_to_ldu(crtc);
	dev_priv = vmw_priv(plane->dev);
	fb       = new_state->fb;

	vfb = (fb) ? vmw_framebuffer_to_vfb(fb) : शून्य;

	अगर (vfb)
		vmw_ldu_add_active(dev_priv, ldu, vfb);
	अन्यथा
		vmw_ldu_del_active(dev_priv, ldu);

	vmw_ldu_commit_list(dev_priv);
पूर्ण


अटल स्थिर काष्ठा drm_plane_funcs vmw_ldu_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = vmw_du_primary_plane_destroy,
	.reset = vmw_du_plane_reset,
	.atomic_duplicate_state = vmw_du_plane_duplicate_state,
	.atomic_destroy_state = vmw_du_plane_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs vmw_ldu_cursor_funcs = अणु
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
drm_plane_helper_funcs vmw_ldu_cursor_plane_helper_funcs = अणु
	.atomic_check = vmw_du_cursor_plane_atomic_check,
	.atomic_update = vmw_du_cursor_plane_atomic_update,
	.prepare_fb = vmw_du_cursor_plane_prepare_fb,
	.cleanup_fb = vmw_du_plane_cleanup_fb,
पूर्ण;

अटल स्थिर काष्ठा
drm_plane_helper_funcs vmw_ldu_primary_plane_helper_funcs = अणु
	.atomic_check = vmw_du_primary_plane_atomic_check,
	.atomic_update = vmw_ldu_primary_plane_atomic_update,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs vmw_ldu_crtc_helper_funcs = अणु
	.mode_set_nofb = vmw_ldu_crtc_mode_set_nofb,
	.atomic_check = vmw_du_crtc_atomic_check,
	.atomic_begin = vmw_du_crtc_atomic_begin,
	.atomic_flush = vmw_du_crtc_atomic_flush,
	.atomic_enable = vmw_ldu_crtc_atomic_enable,
	.atomic_disable = vmw_ldu_crtc_atomic_disable,
पूर्ण;


अटल पूर्णांक vmw_ldu_init(काष्ठा vmw_निजी *dev_priv, अचिन्हित unit)
अणु
	काष्ठा vmw_legacy_display_unit *ldu;
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_plane *primary, *cursor;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret;

	ldu = kzalloc(माप(*ldu), GFP_KERNEL);
	अगर (!ldu)
		वापस -ENOMEM;

	ldu->base.unit = unit;
	crtc = &ldu->base.crtc;
	encoder = &ldu->base.encoder;
	connector = &ldu->base.connector;
	primary = &ldu->base.primary;
	cursor = &ldu->base.cursor;

	INIT_LIST_HEAD(&ldu->active);

	ldu->base.pref_active = (unit == 0);
	ldu->base.pref_width = dev_priv->initial_width;
	ldu->base.pref_height = dev_priv->initial_height;
	ldu->base.pref_mode = शून्य;

	/*
	 * Remove this after enabling atomic because property values can
	 * only exist in a state object
	 */
	ldu->base.is_implicit = true;

	/* Initialize primary plane */
	ret = drm_universal_plane_init(dev, &ldu->base.primary,
				       0, &vmw_ldu_plane_funcs,
				       vmw_primary_plane_क्रमmats,
				       ARRAY_SIZE(vmw_primary_plane_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_PRIMARY, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize primary plane");
		जाओ err_मुक्त;
	पूर्ण

	drm_plane_helper_add(primary, &vmw_ldu_primary_plane_helper_funcs);

	/* Initialize cursor plane */
	ret = drm_universal_plane_init(dev, &ldu->base.cursor,
			0, &vmw_ldu_cursor_funcs,
			vmw_cursor_plane_क्रमmats,
			ARRAY_SIZE(vmw_cursor_plane_क्रमmats),
			शून्य, DRM_PLANE_TYPE_CURSOR, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize cursor plane");
		drm_plane_cleanup(&ldu->base.primary);
		जाओ err_मुक्त;
	पूर्ण

	drm_plane_helper_add(cursor, &vmw_ldu_cursor_plane_helper_funcs);

	ret = drm_connector_init(dev, connector, &vmw_legacy_connector_funcs,
				 DRM_MODE_CONNECTOR_VIRTUAL);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector\n");
		जाओ err_मुक्त;
	पूर्ण

	drm_connector_helper_add(connector, &vmw_ldu_connector_helper_funcs);
	connector->status = vmw_du_connector_detect(connector, true);

	ret = drm_encoder_init(dev, encoder, &vmw_legacy_encoder_funcs,
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

	ret = drm_crtc_init_with_planes(dev, crtc, &ldu->base.primary,
					&ldu->base.cursor,
					&vmw_legacy_crtc_funcs, शून्य);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize CRTC\n");
		जाओ err_मुक्त_unरेजिस्टर;
	पूर्ण

	drm_crtc_helper_add(crtc, &vmw_ldu_crtc_helper_funcs);

	drm_mode_crtc_set_gamma_size(crtc, 256);

	drm_object_attach_property(&connector->base,
				   dev_priv->hotplug_mode_update_property, 1);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_x_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_y_property, 0);
	अगर (dev_priv->implicit_placement_property)
		drm_object_attach_property
			(&connector->base,
			 dev_priv->implicit_placement_property,
			 1);

	वापस 0;

err_मुक्त_unरेजिस्टर:
	drm_connector_unरेजिस्टर(connector);
err_मुक्त_encoder:
	drm_encoder_cleanup(encoder);
err_मुक्त_connector:
	drm_connector_cleanup(connector);
err_मुक्त:
	kमुक्त(ldu);
	वापस ret;
पूर्ण

पूर्णांक vmw_kms_ldu_init_display(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	पूर्णांक i, ret;

	अगर (dev_priv->ldu_priv) अणु
		DRM_INFO("ldu system already on\n");
		वापस -EINVAL;
	पूर्ण

	dev_priv->ldu_priv = kदो_स्मृति(माप(*dev_priv->ldu_priv), GFP_KERNEL);
	अगर (!dev_priv->ldu_priv)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&dev_priv->ldu_priv->active);
	dev_priv->ldu_priv->num_active = 0;
	dev_priv->ldu_priv->last_num_active = 0;
	dev_priv->ldu_priv->fb = शून्य;

	/* क्रम old hardware without multimon only enable one display */
	अगर (dev_priv->capabilities & SVGA_CAP_MULTIMON)
		ret = drm_vblank_init(dev, VMWGFX_NUM_DISPLAY_UNITS);
	अन्यथा
		ret = drm_vblank_init(dev, 1);
	अगर (ret != 0)
		जाओ err_मुक्त;

	vmw_kms_create_implicit_placement_property(dev_priv);

	अगर (dev_priv->capabilities & SVGA_CAP_MULTIMON)
		क्रम (i = 0; i < VMWGFX_NUM_DISPLAY_UNITS; ++i)
			vmw_ldu_init(dev_priv, i);
	अन्यथा
		vmw_ldu_init(dev_priv, 0);

	dev_priv->active_display_unit = vmw_du_legacy;

	drm_mode_config_reset(dev);

	DRM_INFO("Legacy Display Unit initialized\n");

	वापस 0;

err_मुक्त:
	kमुक्त(dev_priv->ldu_priv);
	dev_priv->ldu_priv = शून्य;
	वापस ret;
पूर्ण

पूर्णांक vmw_kms_ldu_बंद_display(काष्ठा vmw_निजी *dev_priv)
अणु
	अगर (!dev_priv->ldu_priv)
		वापस -ENOSYS;

	BUG_ON(!list_empty(&dev_priv->ldu_priv->active));

	kमुक्त(dev_priv->ldu_priv);

	वापस 0;
पूर्ण


पूर्णांक vmw_kms_ldu_करो_bo_dirty(काष्ठा vmw_निजी *dev_priv,
			    काष्ठा vmw_framebuffer *framebuffer,
			    अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक color,
			    काष्ठा drm_clip_rect *clips,
			    अचिन्हित पूर्णांक num_clips, पूर्णांक increment)
अणु
	माप_प्रकार fअगरo_size;
	पूर्णांक i;

	काष्ठा अणु
		uपूर्णांक32_t header;
		SVGAFअगरoCmdUpdate body;
	पूर्ण *cmd;

	fअगरo_size = माप(*cmd) * num_clips;
	cmd = VMW_CMD_RESERVE(dev_priv, fअगरo_size);
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	स_रखो(cmd, 0, fअगरo_size);
	क्रम (i = 0; i < num_clips; i++, clips += increment) अणु
		cmd[i].header = SVGA_CMD_UPDATE;
		cmd[i].body.x = clips->x1;
		cmd[i].body.y = clips->y1;
		cmd[i].body.width = clips->x2 - clips->x1;
		cmd[i].body.height = clips->y2 - clips->y1;
	पूर्ण

	vmw_cmd_commit(dev_priv, fअगरo_size);
	वापस 0;
पूर्ण
