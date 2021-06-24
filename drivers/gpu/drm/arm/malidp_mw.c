<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Brian Starkey <brian.starkey@arm.com>
 *
 * ARM Mali DP Writeback connector implementation
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_ग_लिखोback.h>

#समावेश "malidp_drv.h"
#समावेश "malidp_hw.h"
#समावेश "malidp_mw.h"

#घोषणा to_mw_state(_state) (काष्ठा malidp_mw_connector_state *)(_state)

काष्ठा malidp_mw_connector_state अणु
	काष्ठा drm_connector_state base;
	dma_addr_t addrs[2];
	s32 pitches[2];
	u8 क्रमmat;
	u8 n_planes;
	bool rgb2yuv_initialized;
	स्थिर s16 *rgb2yuv_coeffs;
पूर्ण;

अटल पूर्णांक malidp_mw_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	वापस drm_add_modes_noedid(connector, dev->mode_config.max_width,
				    dev->mode_config.max_height);
पूर्ण

अटल क्रमागत drm_mode_status
malidp_mw_connector_mode_valid(काष्ठा drm_connector *connector,
			       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	पूर्णांक w = mode->hdisplay, h = mode->vdisplay;

	अगर ((w < mode_config->min_width) || (w > mode_config->max_width))
		वापस MODE_BAD_HVALUE;

	अगर ((h < mode_config->min_height) || (h > mode_config->max_height))
		वापस MODE_BAD_VVALUE;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs malidp_mw_connector_helper_funcs = अणु
	.get_modes = malidp_mw_connector_get_modes,
	.mode_valid = malidp_mw_connector_mode_valid,
पूर्ण;

अटल व्योम malidp_mw_connector_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा malidp_mw_connector_state *mw_state =
		kzalloc(माप(*mw_state), GFP_KERNEL);

	अगर (connector->state)
		__drm_atomic_helper_connector_destroy_state(connector->state);

	kमुक्त(connector->state);
	__drm_atomic_helper_connector_reset(connector, &mw_state->base);
पूर्ण

अटल क्रमागत drm_connector_status
malidp_mw_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	वापस connector_status_connected;
पूर्ण

अटल व्योम malidp_mw_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल काष्ठा drm_connector_state *
malidp_mw_connector_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा malidp_mw_connector_state *mw_state, *mw_current_state;

	अगर (WARN_ON(!connector->state))
		वापस शून्य;

	mw_state = kzalloc(माप(*mw_state), GFP_KERNEL);
	अगर (!mw_state)
		वापस शून्य;

	mw_current_state = to_mw_state(connector->state);
	mw_state->rgb2yuv_coeffs = mw_current_state->rgb2yuv_coeffs;
	mw_state->rgb2yuv_initialized = mw_current_state->rgb2yuv_initialized;

	__drm_atomic_helper_connector_duplicate_state(connector, &mw_state->base);

	वापस &mw_state->base;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs malidp_mw_connector_funcs = अणु
	.reset = malidp_mw_connector_reset,
	.detect = malidp_mw_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = malidp_mw_connector_destroy,
	.atomic_duplicate_state = malidp_mw_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर s16 rgb2yuv_coeffs_bt709_limited[MALIDP_COLORADJ_NUM_COEFFS] = अणु
	47,  157,   16,
	-26,  -87,  112,
	112, -102,  -10,
	16,  128,  128
पूर्ण;

अटल पूर्णांक
malidp_mw_encoder_atomic_check(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा malidp_mw_connector_state *mw_state = to_mw_state(conn_state);
	काष्ठा malidp_drm *malidp = encoder->dev->dev_निजी;
	काष्ठा drm_framebuffer *fb;
	पूर्णांक i, n_planes;

	अगर (!conn_state->ग_लिखोback_job)
		वापस 0;

	fb = conn_state->ग_लिखोback_job->fb;
	अगर ((fb->width != crtc_state->mode.hdisplay) ||
	    (fb->height != crtc_state->mode.vdisplay)) अणु
		DRM_DEBUG_KMS("Invalid framebuffer size %ux%u\n",
				fb->width, fb->height);
		वापस -EINVAL;
	पूर्ण

	अगर (fb->modअगरier) अणु
		DRM_DEBUG_KMS("Writeback framebuffer does not support modifiers\n");
		वापस -EINVAL;
	पूर्ण

	mw_state->क्रमmat =
		malidp_hw_get_क्रमmat_id(&malidp->dev->hw->map, SE_MEMWRITE,
					fb->क्रमmat->क्रमmat, !!fb->modअगरier);
	अगर (mw_state->क्रमmat == MALIDP_INVALID_FORMAT_ID) अणु
		DRM_DEBUG_KMS("Invalid pixel format %p4cc\n",
			      &fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	n_planes = fb->क्रमmat->num_planes;
	क्रम (i = 0; i < n_planes; i++) अणु
		काष्ठा drm_gem_cma_object *obj = drm_fb_cma_get_gem_obj(fb, i);
		/* memory ग_लिखो buffers are never rotated */
		u8 alignment = malidp_hw_get_pitch_align(malidp->dev, 0);

		अगर (fb->pitches[i] & (alignment - 1)) अणु
			DRM_DEBUG_KMS("Invalid pitch %u for plane %d\n",
				      fb->pitches[i], i);
			वापस -EINVAL;
		पूर्ण
		mw_state->pitches[i] = fb->pitches[i];
		mw_state->addrs[i] = obj->paddr + fb->offsets[i];
	पूर्ण
	mw_state->n_planes = n_planes;

	अगर (fb->क्रमmat->is_yuv)
		mw_state->rgb2yuv_coeffs = rgb2yuv_coeffs_bt709_limited;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs malidp_mw_encoder_helper_funcs = अणु
	.atomic_check = malidp_mw_encoder_atomic_check,
पूर्ण;

अटल u32 *get_ग_लिखोback_क्रमmats(काष्ठा malidp_drm *malidp, पूर्णांक *n_क्रमmats)
अणु
	स्थिर काष्ठा malidp_hw_regmap *map = &malidp->dev->hw->map;
	u32 *क्रमmats;
	पूर्णांक n, i;

	क्रमmats = kसुस्मृति(map->n_pixel_क्रमmats, माप(*क्रमmats),
			  GFP_KERNEL);
	अगर (!क्रमmats)
		वापस शून्य;

	क्रम (n = 0, i = 0;  i < map->n_pixel_क्रमmats; i++) अणु
		अगर (map->pixel_क्रमmats[i].layer & SE_MEMWRITE)
			क्रमmats[n++] = map->pixel_क्रमmats[i].क्रमmat;
	पूर्ण

	*n_क्रमmats = n;

	वापस क्रमmats;
पूर्ण

पूर्णांक malidp_mw_connector_init(काष्ठा drm_device *drm)
अणु
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	u32 *क्रमmats;
	पूर्णांक ret, n_क्रमmats;

	अगर (!malidp->dev->hw->enable_memग_लिखो)
		वापस 0;

	malidp->mw_connector.encoder.possible_crtcs = 1 << drm_crtc_index(&malidp->crtc);
	drm_connector_helper_add(&malidp->mw_connector.base,
				 &malidp_mw_connector_helper_funcs);

	क्रमmats = get_ग_लिखोback_क्रमmats(malidp, &n_क्रमmats);
	अगर (!क्रमmats)
		वापस -ENOMEM;

	ret = drm_ग_लिखोback_connector_init(drm, &malidp->mw_connector,
					   &malidp_mw_connector_funcs,
					   &malidp_mw_encoder_helper_funcs,
					   क्रमmats, n_क्रमmats);
	kमुक्त(क्रमmats);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

व्योम malidp_mw_atomic_commit(काष्ठा drm_device *drm,
			     काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा drm_ग_लिखोback_connector *mw_conn = &malidp->mw_connector;
	काष्ठा drm_connector_state *conn_state = mw_conn->base.state;
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	काष्ठा malidp_mw_connector_state *mw_state;

	अगर (!conn_state)
		वापस;

	mw_state = to_mw_state(conn_state);

	अगर (conn_state->ग_लिखोback_job) अणु
		काष्ठा drm_framebuffer *fb = conn_state->ग_लिखोback_job->fb;

		DRM_DEV_DEBUG_DRIVER(drm->dev,
				     "Enable memwrite %ux%u:%d %pad fmt: %u\n",
				     fb->width, fb->height,
				     mw_state->pitches[0],
				     &mw_state->addrs[0],
				     mw_state->क्रमmat);

		drm_ग_लिखोback_queue_job(mw_conn, conn_state);
		hwdev->hw->enable_memग_लिखो(hwdev, mw_state->addrs,
					   mw_state->pitches, mw_state->n_planes,
					   fb->width, fb->height, mw_state->क्रमmat,
					   !mw_state->rgb2yuv_initialized ?
					   mw_state->rgb2yuv_coeffs : शून्य);
		mw_state->rgb2yuv_initialized = !!mw_state->rgb2yuv_coeffs;
	पूर्ण अन्यथा अणु
		DRM_DEV_DEBUG_DRIVER(drm->dev, "Disable memwrite\n");
		hwdev->hw->disable_memग_लिखो(hwdev);
	पूर्ण
पूर्ण
