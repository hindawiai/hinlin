<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drm kms/fb cma (contiguous memory allocator) helper functions
 *
 * Copyright (C) 2012 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 *
 * Based on udl_fbdev.c
 *  Copyright (C) 2012 Red Hat
 */

#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane.h>
#समावेश <linux/module.h>

/**
 * DOC: framebuffer cma helper functions
 *
 * Provides helper functions क्रम creating a cma (contiguous memory allocator)
 * backed framebuffer.
 *
 * drm_gem_fb_create() is used in the &drm_mode_config_funcs.fb_create
 * callback function to create a cma backed framebuffer.
 */

/**
 * drm_fb_cma_get_gem_obj() - Get CMA GEM object क्रम framebuffer
 * @fb: The framebuffer
 * @plane: Which plane
 *
 * Return the CMA GEM object क्रम given framebuffer.
 *
 * This function will usually be called from the CRTC callback functions.
 */
काष्ठा drm_gem_cma_object *drm_fb_cma_get_gem_obj(काष्ठा drm_framebuffer *fb,
						  अचिन्हित पूर्णांक plane)
अणु
	काष्ठा drm_gem_object *gem;

	gem = drm_gem_fb_get_obj(fb, plane);
	अगर (!gem)
		वापस शून्य;

	वापस to_drm_gem_cma_obj(gem);
पूर्ण
EXPORT_SYMBOL_GPL(drm_fb_cma_get_gem_obj);

/**
 * drm_fb_cma_get_gem_addr() - Get physical address क्रम framebuffer, क्रम pixel
 * क्रमmats where values are grouped in blocks this will get you the beginning of
 * the block
 * @fb: The framebuffer
 * @state: Which state of drm plane
 * @plane: Which plane
 * Return the CMA GEM address क्रम given framebuffer.
 *
 * This function will usually be called from the PLANE callback functions.
 */
dma_addr_t drm_fb_cma_get_gem_addr(काष्ठा drm_framebuffer *fb,
				   काष्ठा drm_plane_state *state,
				   अचिन्हित पूर्णांक plane)
अणु
	काष्ठा drm_gem_cma_object *obj;
	dma_addr_t paddr;
	u8 h_भाग = 1, v_भाग = 1;
	u32 block_w = drm_क्रमmat_info_block_width(fb->क्रमmat, plane);
	u32 block_h = drm_क्रमmat_info_block_height(fb->क्रमmat, plane);
	u32 block_size = fb->क्रमmat->अक्षर_per_block[plane];
	u32 sample_x;
	u32 sample_y;
	u32 block_start_y;
	u32 num_hblocks;

	obj = drm_fb_cma_get_gem_obj(fb, plane);
	अगर (!obj)
		वापस 0;

	paddr = obj->paddr + fb->offsets[plane];

	अगर (plane > 0) अणु
		h_भाग = fb->क्रमmat->hsub;
		v_भाग = fb->क्रमmat->vsub;
	पूर्ण

	sample_x = (state->src_x >> 16) / h_भाग;
	sample_y = (state->src_y >> 16) / v_भाग;
	block_start_y = (sample_y / block_h) * block_h;
	num_hblocks = sample_x / block_w;

	paddr += fb->pitches[plane] * block_start_y;
	paddr += block_size * num_hblocks;

	वापस paddr;
पूर्ण
EXPORT_SYMBOL_GPL(drm_fb_cma_get_gem_addr);
