<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 * Freescale DCU drm device driver
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "fsl_dcu_drm_crtc.h"
#समावेश "fsl_dcu_drm_drv.h"

अटल स्थिर काष्ठा drm_mode_config_funcs fsl_dcu_drm_mode_config_funcs = अणु
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
	.fb_create = drm_gem_fb_create,
पूर्ण;

पूर्णांक fsl_dcu_drm_modeset_init(काष्ठा fsl_dcu_drm_device *fsl_dev)
अणु
	पूर्णांक ret;

	drm_mode_config_init(fsl_dev->drm);

	fsl_dev->drm->mode_config.min_width = 0;
	fsl_dev->drm->mode_config.min_height = 0;
	fsl_dev->drm->mode_config.max_width = 2031;
	fsl_dev->drm->mode_config.max_height = 2047;
	fsl_dev->drm->mode_config.funcs = &fsl_dcu_drm_mode_config_funcs;

	ret = fsl_dcu_drm_crtc_create(fsl_dev);
	अगर (ret)
		जाओ err;

	ret = fsl_dcu_drm_encoder_create(fsl_dev, &fsl_dev->crtc);
	अगर (ret)
		जाओ err;

	ret = fsl_dcu_create_outमाला_दो(fsl_dev);
	अगर (ret)
		जाओ err;

	drm_mode_config_reset(fsl_dev->drm);
	drm_kms_helper_poll_init(fsl_dev->drm);

	वापस 0;

err:
	drm_mode_config_cleanup(fsl_dev->drm);
	वापस ret;
पूर्ण
