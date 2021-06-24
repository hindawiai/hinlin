<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "sti_compositor.h"
#समावेश "sti_crtc.h"
#समावेश "sti_drv.h"
#समावेश "sti_vid.h"
#समावेश "sti_vtg.h"

अटल व्योम sti_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);

	DRM_DEBUG_DRIVER("\n");

	mixer->status = STI_MIXER_READY;

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम sti_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);

	DRM_DEBUG_DRIVER("\n");

	mixer->status = STI_MIXER_DISABLING;

	drm_crtc_रुको_one_vblank(crtc);
पूर्ण

अटल पूर्णांक
sti_crtc_mode_set(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);
	काष्ठा device *dev = mixer->dev;
	काष्ठा sti_compositor *compo = dev_get_drvdata(dev);
	काष्ठा clk *compo_clk, *pix_clk;
	पूर्णांक rate = mode->घड़ी * 1000;

	DRM_DEBUG_KMS("CRTC:%d (%s) mode: (%s)\n",
		      crtc->base.id, sti_mixer_to_str(mixer), mode->name);

	DRM_DEBUG_KMS(DRM_MODE_FMT "\n", DRM_MODE_ARG(mode));

	अगर (mixer->id == STI_MIXER_MAIN) अणु
		compo_clk = compo->clk_compo_मुख्य;
		pix_clk = compo->clk_pix_मुख्य;
	पूर्ण अन्यथा अणु
		compo_clk = compo->clk_compo_aux;
		pix_clk = compo->clk_pix_aux;
	पूर्ण

	/* Prepare and enable the compo IP घड़ी */
	अगर (clk_prepare_enable(compo_clk)) अणु
		DRM_INFO("Failed to prepare/enable compositor clk\n");
		जाओ compo_error;
	पूर्ण

	/* Set rate and prepare/enable pixel घड़ी */
	अगर (clk_set_rate(pix_clk, rate) < 0) अणु
		DRM_ERROR("Cannot set rate (%dHz) for pix clk\n", rate);
		जाओ pix_error;
	पूर्ण
	अगर (clk_prepare_enable(pix_clk)) अणु
		DRM_ERROR("Failed to prepare/enable pix clk\n");
		जाओ pix_error;
	पूर्ण

	sti_vtg_set_config(compo->vtg[mixer->id], &crtc->mode);

	अगर (sti_mixer_active_video_area(mixer, &crtc->mode)) अणु
		DRM_ERROR("Can't set active video area\n");
		जाओ mixer_error;
	पूर्ण

	वापस 0;

mixer_error:
	clk_disable_unprepare(pix_clk);
pix_error:
	clk_disable_unprepare(compo_clk);
compo_error:
	वापस -EINVAL;
पूर्ण

अटल व्योम sti_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);
	काष्ठा device *dev = mixer->dev;
	काष्ठा sti_compositor *compo = dev_get_drvdata(dev);

	DRM_DEBUG_KMS("CRTC:%d (%s)\n", crtc->base.id, sti_mixer_to_str(mixer));

	/* Disable Background */
	sti_mixer_set_background_status(mixer, false);

	drm_crtc_vblank_off(crtc);

	/* Disable pixel घड़ी and compo IP घड़ीs */
	अगर (mixer->id == STI_MIXER_MAIN) अणु
		clk_disable_unprepare(compo->clk_pix_मुख्य);
		clk_disable_unprepare(compo->clk_compo_मुख्य);
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(compo->clk_pix_aux);
		clk_disable_unprepare(compo->clk_compo_aux);
	पूर्ण

	mixer->status = STI_MIXER_DISABLED;
पूर्ण

अटल व्योम
sti_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	sti_crtc_mode_set(crtc, &crtc->state->adjusted_mode);
पूर्ण

अटल व्योम sti_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);
	काष्ठा sti_compositor *compo = dev_get_drvdata(mixer->dev);
	काष्ठा drm_plane *p;
	काष्ठा drm_pending_vblank_event *event;
	अचिन्हित दीर्घ flags;

	DRM_DEBUG_DRIVER("\n");

	/* perक्रमm plane actions */
	list_क्रम_each_entry(p, &drm_dev->mode_config.plane_list, head) अणु
		काष्ठा sti_plane *plane = to_sti_plane(p);

		चयन (plane->status) अणु
		हाल STI_PLANE_UPDATED:
			/* ignore update क्रम other CRTC */
			अगर (p->state->crtc != crtc)
				जारी;

			/* update planes tag as updated */
			DRM_DEBUG_DRIVER("update plane %s\n",
					 sti_plane_to_str(plane));

			अगर (sti_mixer_set_plane_depth(mixer, plane)) अणु
				DRM_ERROR("Cannot set plane %s depth\n",
					  sti_plane_to_str(plane));
				अवरोध;
			पूर्ण

			अगर (sti_mixer_set_plane_status(mixer, plane, true)) अणु
				DRM_ERROR("Cannot enable plane %s at mixer\n",
					  sti_plane_to_str(plane));
				अवरोध;
			पूर्ण

			/* अगर plane is HQVDP_0 then commit the vid[0] */
			अगर (plane->desc == STI_HQVDP_0)
				sti_vid_commit(compo->vid[0], p->state);

			plane->status = STI_PLANE_READY;

			अवरोध;
		हाल STI_PLANE_DISABLING:
			/* disabling sequence क्रम planes tag as disabling */
			DRM_DEBUG_DRIVER("disable plane %s from mixer\n",
					 sti_plane_to_str(plane));

			अगर (sti_mixer_set_plane_status(mixer, plane, false)) अणु
				DRM_ERROR("Cannot disable plane %s at mixer\n",
					  sti_plane_to_str(plane));
				जारी;
			पूर्ण

			अगर (plane->desc == STI_CURSOR)
				/* tag plane status क्रम disabled */
				plane->status = STI_PLANE_DISABLED;
			अन्यथा
				/* tag plane status क्रम flushing */
				plane->status = STI_PLANE_FLUSHING;

			/* अगर plane is HQVDP_0 then disable the vid[0] */
			अगर (plane->desc == STI_HQVDP_0)
				sti_vid_disable(compo->vid[0]);

			अवरोध;
		शेष:
			/* Other status हाल are not handled */
			अवरोध;
		पूर्ण
	पूर्ण

	event = crtc->state->event;
	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irqsave(&crtc->dev->event_lock, flags);
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs sti_crtc_helper_funcs = अणु
	.mode_set_nofb = sti_crtc_mode_set_nofb,
	.atomic_flush = sti_crtc_atomic_flush,
	.atomic_enable = sti_crtc_atomic_enable,
	.atomic_disable = sti_crtc_atomic_disable,
पूर्ण;

अटल व्योम sti_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	DRM_DEBUG_KMS("\n");
	drm_crtc_cleanup(crtc);
पूर्ण

अटल पूर्णांक sti_crtc_set_property(काष्ठा drm_crtc *crtc,
				 काष्ठा drm_property *property,
				 uपूर्णांक64_t val)
अणु
	DRM_DEBUG_KMS("\n");
	वापस 0;
पूर्ण

पूर्णांक sti_crtc_vblank_cb(काष्ठा notअगरier_block *nb,
		       अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा sti_compositor *compo;
	काष्ठा drm_crtc *crtc = data;
	काष्ठा sti_mixer *mixer;
	अचिन्हित पूर्णांक pipe;

	pipe = drm_crtc_index(crtc);
	compo = container_of(nb, काष्ठा sti_compositor, vtg_vblank_nb[pipe]);
	mixer = compo->mixer[pipe];

	अगर ((event != VTG_TOP_FIELD_EVENT) &&
	    (event != VTG_BOTTOM_FIELD_EVENT)) अणु
		DRM_ERROR("unknown event: %lu\n", event);
		वापस -EINVAL;
	पूर्ण

	drm_crtc_handle_vblank(crtc);

	अगर (mixer->status == STI_MIXER_DISABLING) अणु
		काष्ठा drm_plane *p;

		/* Disable mixer only अगर all overlay planes (GDP and VDP)
		 * are disabled */
		list_क्रम_each_entry(p, &crtc->dev->mode_config.plane_list,
				    head) अणु
			काष्ठा sti_plane *plane = to_sti_plane(p);

			अगर ((plane->desc & STI_PLANE_TYPE_MASK) <= STI_VDP)
				अगर (plane->status != STI_PLANE_DISABLED)
					वापस 0;
		पूर्ण
		sti_crtc_disable(crtc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sti_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा sti_निजी *dev_priv = dev->dev_निजी;
	काष्ठा sti_compositor *compo = dev_priv->compo;
	काष्ठा notअगरier_block *vtg_vblank_nb = &compo->vtg_vblank_nb[pipe];
	काष्ठा sti_vtg *vtg = compo->vtg[pipe];

	DRM_DEBUG_DRIVER("\n");

	अगर (sti_vtg_रेजिस्टर_client(vtg, vtg_vblank_nb, crtc)) अणु
		DRM_ERROR("Cannot register VTG notifier\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sti_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *drm_dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा sti_निजी *priv = drm_dev->dev_निजी;
	काष्ठा sti_compositor *compo = priv->compo;
	काष्ठा notअगरier_block *vtg_vblank_nb = &compo->vtg_vblank_nb[pipe];
	काष्ठा sti_vtg *vtg = compo->vtg[pipe];

	DRM_DEBUG_DRIVER("\n");

	अगर (sti_vtg_unरेजिस्टर_client(vtg, vtg_vblank_nb))
		DRM_DEBUG_DRIVER("Warning: cannot unregister VTG notifier\n");
पूर्ण

अटल पूर्णांक sti_crtc_late_रेजिस्टर(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);
	काष्ठा sti_compositor *compo = dev_get_drvdata(mixer->dev);

	अगर (drm_crtc_index(crtc) == 0)
		sti_compositor_debugfs_init(compo, crtc->dev->primary);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs sti_crtc_funcs = अणु
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.destroy = sti_crtc_destroy,
	.set_property = sti_crtc_set_property,
	.reset = drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.late_रेजिस्टर = sti_crtc_late_रेजिस्टर,
	.enable_vblank = sti_crtc_enable_vblank,
	.disable_vblank = sti_crtc_disable_vblank,
पूर्ण;

bool sti_crtc_is_मुख्य(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा sti_mixer *mixer = to_sti_mixer(crtc);

	अगर (mixer->id == STI_MIXER_MAIN)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक sti_crtc_init(काष्ठा drm_device *drm_dev, काष्ठा sti_mixer *mixer,
		  काष्ठा drm_plane *primary, काष्ठा drm_plane *cursor)
अणु
	काष्ठा drm_crtc *crtc = &mixer->drm_crtc;
	पूर्णांक res;

	res = drm_crtc_init_with_planes(drm_dev, crtc, primary, cursor,
					&sti_crtc_funcs, शून्य);
	अगर (res) अणु
		DRM_ERROR("Can't initialize CRTC\n");
		वापस -EINVAL;
	पूर्ण

	drm_crtc_helper_add(crtc, &sti_crtc_helper_funcs);

	DRM_DEBUG_DRIVER("drm CRTC:%d mapped to %s\n",
			 crtc->base.id, sti_mixer_to_str(mixer));

	वापस 0;
पूर्ण
