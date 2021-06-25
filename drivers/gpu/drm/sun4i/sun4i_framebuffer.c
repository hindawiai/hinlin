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
#समावेश <drm/drm_gem_framebuffer_helper.h>

#समावेश "sun4i_drv.h"
#समावेश "sun4i_framebuffer.h"

अटल पूर्णांक sun4i_de_atomic_check(काष्ठा drm_device *dev,
				 काष्ठा drm_atomic_state *state)
अणु
	पूर्णांक ret;

	ret = drm_atomic_helper_check_modeset(dev, state);
	अगर (ret)
		वापस ret;

	ret = drm_atomic_normalize_zpos(dev, state);
	अगर (ret)
		वापस ret;

	वापस drm_atomic_helper_check_planes(dev, state);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs sun4i_de_mode_config_funcs = अणु
	.atomic_check		= sun4i_de_atomic_check,
	.atomic_commit		= drm_atomic_helper_commit,
	.fb_create		= drm_gem_fb_create,
पूर्ण;

अटल स्थिर काष्ठा drm_mode_config_helper_funcs sun4i_de_mode_config_helpers = अणु
	.atomic_commit_tail	= drm_atomic_helper_commit_tail_rpm,
पूर्ण;

व्योम sun4i_framebuffer_init(काष्ठा drm_device *drm)
अणु
	drm_mode_config_reset(drm);

	drm->mode_config.max_width = 8192;
	drm->mode_config.max_height = 8192;

	drm->mode_config.funcs = &sun4i_de_mode_config_funcs;
	drm->mode_config.helper_निजी = &sun4i_de_mode_config_helpers;
पूर्ण
