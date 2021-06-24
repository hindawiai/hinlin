<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "sun4i_backend.h"
#समावेश "sun4i_frontend.h"
#समावेश "sun4i_layer.h"
#समावेश "sunxi_engine.h"

अटल व्योम sun4i_backend_layer_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा sun4i_layer *layer = plane_to_sun4i_layer(plane);
	काष्ठा sun4i_layer_state *state;

	अगर (plane->state) अणु
		state = state_to_sun4i_layer_state(plane->state);

		__drm_atomic_helper_plane_destroy_state(&state->state);

		kमुक्त(state);
		plane->state = शून्य;
	पूर्ण

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state) अणु
		__drm_atomic_helper_plane_reset(plane, &state->state);
		plane->state->zpos = layer->id;
	पूर्ण
पूर्ण

अटल काष्ठा drm_plane_state *
sun4i_backend_layer_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा sun4i_layer_state *orig = state_to_sun4i_layer_state(plane->state);
	काष्ठा sun4i_layer_state *copy;

	copy = kzalloc(माप(*copy), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &copy->state);
	copy->uses_frontend = orig->uses_frontend;

	वापस &copy->state;
पूर्ण

अटल व्योम sun4i_backend_layer_destroy_state(काष्ठा drm_plane *plane,
					      काष्ठा drm_plane_state *state)
अणु
	काष्ठा sun4i_layer_state *s_state = state_to_sun4i_layer_state(state);

	__drm_atomic_helper_plane_destroy_state(state);

	kमुक्त(s_state);
पूर्ण

अटल व्योम sun4i_backend_layer_atomic_disable(काष्ठा drm_plane *plane,
					       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा sun4i_layer_state *layer_state = state_to_sun4i_layer_state(old_state);
	काष्ठा sun4i_layer *layer = plane_to_sun4i_layer(plane);
	काष्ठा sun4i_backend *backend = layer->backend;

	sun4i_backend_layer_enable(backend, layer->id, false);

	अगर (layer_state->uses_frontend) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&backend->frontend_lock, flags);
		backend->frontend_tearकरोwn = true;
		spin_unlock_irqrestore(&backend->frontend_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम sun4i_backend_layer_atomic_update(काष्ठा drm_plane *plane,
					      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा sun4i_layer_state *layer_state = state_to_sun4i_layer_state(new_state);
	काष्ठा sun4i_layer *layer = plane_to_sun4i_layer(plane);
	काष्ठा sun4i_backend *backend = layer->backend;
	काष्ठा sun4i_frontend *frontend = backend->frontend;

	sun4i_backend_cleanup_layer(backend, layer->id);

	अगर (layer_state->uses_frontend) अणु
		sun4i_frontend_init(frontend);
		sun4i_frontend_update_coord(frontend, plane);
		sun4i_frontend_update_buffer(frontend, plane);
		sun4i_frontend_update_क्रमmats(frontend, plane,
					      DRM_FORMAT_XRGB8888);
		sun4i_backend_update_layer_frontend(backend, layer->id,
						    DRM_FORMAT_XRGB8888);
		sun4i_frontend_enable(frontend);
	पूर्ण अन्यथा अणु
		sun4i_backend_update_layer_क्रमmats(backend, layer->id, plane);
		sun4i_backend_update_layer_buffer(backend, layer->id, plane);
	पूर्ण

	sun4i_backend_update_layer_coord(backend, layer->id, plane);
	sun4i_backend_update_layer_zpos(backend, layer->id, plane);
	sun4i_backend_layer_enable(backend, layer->id, true);
पूर्ण

अटल bool sun4i_layer_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					     uपूर्णांक32_t क्रमmat, uपूर्णांक64_t modअगरier)
अणु
	काष्ठा sun4i_layer *layer = plane_to_sun4i_layer(plane);

	अगर (IS_ERR_OR_शून्य(layer->backend->frontend))
		sun4i_backend_क्रमmat_is_supported(क्रमmat, modअगरier);

	वापस sun4i_backend_क्रमmat_is_supported(क्रमmat, modअगरier) ||
	       sun4i_frontend_क्रमmat_is_supported(क्रमmat, modअगरier);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs sun4i_backend_layer_helper_funcs = अणु
	.prepare_fb	= drm_gem_plane_helper_prepare_fb,
	.atomic_disable	= sun4i_backend_layer_atomic_disable,
	.atomic_update	= sun4i_backend_layer_atomic_update,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs sun4i_backend_layer_funcs = अणु
	.atomic_destroy_state	= sun4i_backend_layer_destroy_state,
	.atomic_duplicate_state	= sun4i_backend_layer_duplicate_state,
	.destroy		= drm_plane_cleanup,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.reset			= sun4i_backend_layer_reset,
	.update_plane		= drm_atomic_helper_update_plane,
	.क्रमmat_mod_supported	= sun4i_layer_क्रमmat_mod_supported,
पूर्ण;

अटल स्थिर uपूर्णांक32_t sun4i_layer_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_RGBA4444,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV16,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV61,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_YUV411,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YUV444,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVU411,
	DRM_FORMAT_YVU420,
	DRM_FORMAT_YVU422,
	DRM_FORMAT_YVU444,
	DRM_FORMAT_YVYU,
पूर्ण;

अटल स्थिर uपूर्णांक32_t sun4i_backend_layer_क्रमmats[] = अणु
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGBA5551,
	DRM_FORMAT_RGBA4444,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_VYUY,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
पूर्ण;

अटल स्थिर uपूर्णांक64_t sun4i_layer_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_ALLWINNER_TILED,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

अटल काष्ठा sun4i_layer *sun4i_layer_init_one(काष्ठा drm_device *drm,
						काष्ठा sun4i_backend *backend,
						क्रमागत drm_plane_type type)
अणु
	स्थिर uपूर्णांक64_t *modअगरiers = sun4i_layer_modअगरiers;
	स्थिर uपूर्णांक32_t *क्रमmats = sun4i_layer_क्रमmats;
	अचिन्हित पूर्णांक क्रमmats_len = ARRAY_SIZE(sun4i_layer_क्रमmats);
	काष्ठा sun4i_layer *layer;
	पूर्णांक ret;

	layer = devm_kzalloc(drm->dev, माप(*layer), GFP_KERNEL);
	अगर (!layer)
		वापस ERR_PTR(-ENOMEM);

	layer->backend = backend;

	अगर (IS_ERR_OR_शून्य(backend->frontend)) अणु
		क्रमmats = sun4i_backend_layer_क्रमmats;
		क्रमmats_len = ARRAY_SIZE(sun4i_backend_layer_क्रमmats);
		modअगरiers = शून्य;
	पूर्ण

	/* possible crtcs are set later */
	ret = drm_universal_plane_init(drm, &layer->plane, 0,
				       &sun4i_backend_layer_funcs,
				       क्रमmats, क्रमmats_len,
				       modअगरiers, type, शून्य);
	अगर (ret) अणु
		dev_err(drm->dev, "Couldn't initialize layer\n");
		वापस ERR_PTR(ret);
	पूर्ण

	drm_plane_helper_add(&layer->plane,
			     &sun4i_backend_layer_helper_funcs);

	drm_plane_create_alpha_property(&layer->plane);
	drm_plane_create_zpos_property(&layer->plane, 0, 0,
				       SUN4I_BACKEND_NUM_LAYERS - 1);

	वापस layer;
पूर्ण

काष्ठा drm_plane **sun4i_layers_init(काष्ठा drm_device *drm,
				     काष्ठा sunxi_engine *engine)
अणु
	काष्ठा drm_plane **planes;
	काष्ठा sun4i_backend *backend = engine_to_sun4i_backend(engine);
	पूर्णांक i;

	/* We need to have a sentinel at the need, hence the overallocation */
	planes = devm_kसुस्मृति(drm->dev, SUN4I_BACKEND_NUM_LAYERS + 1,
			      माप(*planes), GFP_KERNEL);
	अगर (!planes)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < SUN4I_BACKEND_NUM_LAYERS; i++) अणु
		क्रमागत drm_plane_type type = i ? DRM_PLANE_TYPE_OVERLAY : DRM_PLANE_TYPE_PRIMARY;
		काष्ठा sun4i_layer *layer;

		layer = sun4i_layer_init_one(drm, backend, type);
		अगर (IS_ERR(layer)) अणु
			dev_err(drm->dev, "Couldn't initialize %s plane\n",
				i ? "overlay" : "primary");
			वापस ERR_CAST(layer);
		पूर्ण

		layer->id = i;
		planes[i] = &layer->plane;
	पूर्ण

	वापस planes;
पूर्ण
