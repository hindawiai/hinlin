<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>

#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "sun4i_backend.h"
#समावेश "sun4i_crtc.h"
#समावेश "sun4i_drv.h"
#समावेश "sunxi_engine.h"
#समावेश "sun4i_tcon.h"

/*
 * While this isn't really working in the DRM theory, in practice we
 * can only ever have one encoder per TCON since we have a mux in our
 * TCON.
 */
अटल काष्ठा drm_encoder *sun4i_crtc_get_encoder(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;

	drm_क्रम_each_encoder(encoder, crtc->dev)
		अगर (encoder->crtc == crtc)
			वापस encoder;

	वापस शून्य;
पूर्ण

अटल पूर्णांक sun4i_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);
	काष्ठा sunxi_engine *engine = scrtc->engine;
	पूर्णांक ret = 0;

	अगर (engine && engine->ops && engine->ops->atomic_check)
		ret = engine->ops->atomic_check(engine, crtc_state);

	वापस ret;
पूर्ण

अटल व्योम sun4i_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा sunxi_engine *engine = scrtc->engine;
	अचिन्हित दीर्घ flags;

	अगर (crtc->state->event) अणु
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irqsave(&dev->event_lock, flags);
		scrtc->event = crtc->state->event;
		spin_unlock_irqrestore(&dev->event_lock, flags);
		crtc->state->event = शून्य;
	पूर्ण

	अगर (engine->ops->atomic_begin)
		engine->ops->atomic_begin(engine, old_state);
पूर्ण

अटल व्योम sun4i_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;

	DRM_DEBUG_DRIVER("Committing plane changes\n");

	sunxi_engine_commit(scrtc->engine);

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल व्योम sun4i_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_encoder *encoder = sun4i_crtc_get_encoder(crtc);
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);

	DRM_DEBUG_DRIVER("Disabling the CRTC\n");

	drm_crtc_vblank_off(crtc);

	sun4i_tcon_set_status(scrtc->tcon, encoder, false);

	अगर (crtc->state->event && !crtc->state->active) अणु
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);

		crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम sun4i_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_encoder *encoder = sun4i_crtc_get_encoder(crtc);
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);

	DRM_DEBUG_DRIVER("Enabling the CRTC\n");

	sun4i_tcon_set_status(scrtc->tcon, encoder, true);

	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम sun4i_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	काष्ठा drm_encoder *encoder = sun4i_crtc_get_encoder(crtc);
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);

	sun4i_tcon_mode_set(scrtc->tcon, encoder, mode);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs sun4i_crtc_helper_funcs = अणु
	.atomic_check	= sun4i_crtc_atomic_check,
	.atomic_begin	= sun4i_crtc_atomic_begin,
	.atomic_flush	= sun4i_crtc_atomic_flush,
	.atomic_enable	= sun4i_crtc_atomic_enable,
	.atomic_disable	= sun4i_crtc_atomic_disable,
	.mode_set_nofb	= sun4i_crtc_mode_set_nofb,
पूर्ण;

अटल पूर्णांक sun4i_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);

	DRM_DEBUG_DRIVER("Enabling VBLANK on crtc %p\n", crtc);

	sun4i_tcon_enable_vblank(scrtc->tcon, true);

	वापस 0;
पूर्ण

अटल व्योम sun4i_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);

	DRM_DEBUG_DRIVER("Disabling VBLANK on crtc %p\n", crtc);

	sun4i_tcon_enable_vblank(scrtc->tcon, false);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs sun4i_crtc_funcs = अणु
	.atomic_destroy_state	= drm_atomic_helper_crtc_destroy_state,
	.atomic_duplicate_state	= drm_atomic_helper_crtc_duplicate_state,
	.destroy		= drm_crtc_cleanup,
	.page_flip		= drm_atomic_helper_page_flip,
	.reset			= drm_atomic_helper_crtc_reset,
	.set_config		= drm_atomic_helper_set_config,
	.enable_vblank		= sun4i_crtc_enable_vblank,
	.disable_vblank		= sun4i_crtc_disable_vblank,
पूर्ण;

काष्ठा sun4i_crtc *sun4i_crtc_init(काष्ठा drm_device *drm,
				   काष्ठा sunxi_engine *engine,
				   काष्ठा sun4i_tcon *tcon)
अणु
	काष्ठा sun4i_crtc *scrtc;
	काष्ठा drm_plane **planes;
	काष्ठा drm_plane *primary = शून्य, *cursor = शून्य;
	पूर्णांक ret, i;

	scrtc = devm_kzalloc(drm->dev, माप(*scrtc), GFP_KERNEL);
	अगर (!scrtc)
		वापस ERR_PTR(-ENOMEM);
	scrtc->engine = engine;
	scrtc->tcon = tcon;

	/* Create our layers */
	planes = sunxi_engine_layers_init(drm, engine);
	अगर (IS_ERR(planes)) अणु
		dev_err(drm->dev, "Couldn't create the planes\n");
		वापस शून्य;
	पूर्ण

	/* find primary and cursor planes क्रम drm_crtc_init_with_planes */
	क्रम (i = 0; planes[i]; i++) अणु
		काष्ठा drm_plane *plane = planes[i];

		चयन (plane->type) अणु
		हाल DRM_PLANE_TYPE_PRIMARY:
			primary = plane;
			अवरोध;
		हाल DRM_PLANE_TYPE_CURSOR:
			cursor = plane;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ret = drm_crtc_init_with_planes(drm, &scrtc->crtc,
					primary,
					cursor,
					&sun4i_crtc_funcs,
					शून्य);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't init DRM CRTC\n");
		वापस ERR_PTR(ret);
	पूर्ण

	drm_crtc_helper_add(&scrtc->crtc, &sun4i_crtc_helper_funcs);

	/* Set crtc.port to output port node of the tcon */
	scrtc->crtc.port = of_graph_get_port_by_id(scrtc->tcon->dev->of_node,
						   1);

	/* Set possible_crtcs to this crtc क्रम overlay planes */
	क्रम (i = 0; planes[i]; i++) अणु
		uपूर्णांक32_t possible_crtcs = drm_crtc_mask(&scrtc->crtc);
		काष्ठा drm_plane *plane = planes[i];

		अगर (plane->type == DRM_PLANE_TYPE_OVERLAY)
			plane->possible_crtcs = possible_crtcs;
	पूर्ण

	वापस scrtc;
पूर्ण
