<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/iommu.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "dc.h"
#समावेश "plane.h"

अटल व्योम tegra_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा tegra_plane *p = to_tegra_plane(plane);

	drm_plane_cleanup(plane);
	kमुक्त(p);
पूर्ण

अटल व्योम tegra_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा tegra_plane *p = to_tegra_plane(plane);
	काष्ठा tegra_plane_state *state;
	अचिन्हित पूर्णांक i;

	अगर (plane->state)
		__drm_atomic_helper_plane_destroy_state(plane->state);

	kमुक्त(plane->state);
	plane->state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state) अणु
		plane->state = &state->base;
		plane->state->plane = plane;
		plane->state->zpos = p->index;
		plane->state->normalized_zpos = p->index;

		क्रम (i = 0; i < 3; i++)
			state->iova[i] = DMA_MAPPING_ERROR;
	पूर्ण
पूर्ण

अटल काष्ठा drm_plane_state *
tegra_plane_atomic_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा tegra_plane_state *state = to_tegra_plane_state(plane->state);
	काष्ठा tegra_plane_state *copy;
	अचिन्हित पूर्णांक i;

	copy = kदो_स्मृति(माप(*copy), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &copy->base);
	copy->tiling = state->tiling;
	copy->क्रमmat = state->क्रमmat;
	copy->swap = state->swap;
	copy->reflect_x = state->reflect_x;
	copy->reflect_y = state->reflect_y;
	copy->opaque = state->opaque;

	क्रम (i = 0; i < 2; i++)
		copy->blending[i] = state->blending[i];

	क्रम (i = 0; i < 3; i++) अणु
		copy->iova[i] = DMA_MAPPING_ERROR;
		copy->sgt[i] = शून्य;
	पूर्ण

	वापस &copy->base;
पूर्ण

अटल व्योम tegra_plane_atomic_destroy_state(काष्ठा drm_plane *plane,
					     काष्ठा drm_plane_state *state)
अणु
	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(state);
पूर्ण

अटल bool tegra_plane_supports_sector_layout(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_crtc *crtc;

	drm_क्रम_each_crtc(crtc, plane->dev) अणु
		अगर (plane->possible_crtcs & drm_crtc_mask(crtc)) अणु
			काष्ठा tegra_dc *dc = to_tegra_dc(crtc);

			अगर (!dc->soc->supports_sector_layout)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool tegra_plane_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
					     uपूर्णांक32_t क्रमmat,
					     uपूर्णांक64_t modअगरier)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info = drm_क्रमmat_info(क्रमmat);

	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR)
		वापस true;

	/* check क्रम the sector layout bit */
	अगर ((modअगरier >> 56) == DRM_FORMAT_MOD_VENDOR_NVIDIA) अणु
		अगर (modअगरier & DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT) अणु
			अगर (!tegra_plane_supports_sector_layout(plane))
				वापस false;
		पूर्ण
	पूर्ण

	अगर (info->num_planes == 1)
		वापस true;

	वापस false;
पूर्ण

स्थिर काष्ठा drm_plane_funcs tegra_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = tegra_plane_destroy,
	.reset = tegra_plane_reset,
	.atomic_duplicate_state = tegra_plane_atomic_duplicate_state,
	.atomic_destroy_state = tegra_plane_atomic_destroy_state,
	.क्रमmat_mod_supported = tegra_plane_क्रमmat_mod_supported,
पूर्ण;

अटल पूर्णांक tegra_dc_pin(काष्ठा tegra_dc *dc, काष्ठा tegra_plane_state *state)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dc->dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < state->base.fb->क्रमmat->num_planes; i++) अणु
		काष्ठा tegra_bo *bo = tegra_fb_get_plane(state->base.fb, i);
		dma_addr_t phys_addr, *phys;
		काष्ठा sg_table *sgt;

		/*
		 * If we're not attached to a करोमुख्य, we alपढ़ोy stored the
		 * physical address when the buffer was allocated. If we're
		 * part of a group that's shared between all display
		 * controllers, we've also alपढ़ोy mapped the framebuffer
		 * through the SMMU. In both हालs we can लघु-circuit the
		 * code below and retrieve the stored IOV address.
		 */
		अगर (!करोमुख्य || dc->client.group)
			phys = &phys_addr;
		अन्यथा
			phys = शून्य;

		sgt = host1x_bo_pin(dc->dev, &bo->base, phys);
		अगर (IS_ERR(sgt)) अणु
			err = PTR_ERR(sgt);
			जाओ unpin;
		पूर्ण

		अगर (sgt) अणु
			err = dma_map_sgtable(dc->dev, sgt, DMA_TO_DEVICE, 0);
			अगर (err)
				जाओ unpin;

			/*
			 * The display controller needs contiguous memory, so
			 * fail अगर the buffer is discontiguous and we fail to
			 * map its SG table to a single contiguous chunk of
			 * I/O भव memory.
			 */
			अगर (sgt->nents > 1) अणु
				err = -EINVAL;
				जाओ unpin;
			पूर्ण

			state->iova[i] = sg_dma_address(sgt->sgl);
			state->sgt[i] = sgt;
		पूर्ण अन्यथा अणु
			state->iova[i] = phys_addr;
		पूर्ण
	पूर्ण

	वापस 0;

unpin:
	dev_err(dc->dev, "failed to map plane %u: %d\n", i, err);

	जबतक (i--) अणु
		काष्ठा tegra_bo *bo = tegra_fb_get_plane(state->base.fb, i);
		काष्ठा sg_table *sgt = state->sgt[i];

		अगर (sgt)
			dma_unmap_sgtable(dc->dev, sgt, DMA_TO_DEVICE, 0);

		host1x_bo_unpin(dc->dev, &bo->base, sgt);
		state->iova[i] = DMA_MAPPING_ERROR;
		state->sgt[i] = शून्य;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम tegra_dc_unpin(काष्ठा tegra_dc *dc, काष्ठा tegra_plane_state *state)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < state->base.fb->क्रमmat->num_planes; i++) अणु
		काष्ठा tegra_bo *bo = tegra_fb_get_plane(state->base.fb, i);
		काष्ठा sg_table *sgt = state->sgt[i];

		अगर (sgt)
			dma_unmap_sgtable(dc->dev, sgt, DMA_TO_DEVICE, 0);

		host1x_bo_unpin(dc->dev, &bo->base, sgt);
		state->iova[i] = DMA_MAPPING_ERROR;
		state->sgt[i] = शून्य;
	पूर्ण
पूर्ण

पूर्णांक tegra_plane_prepare_fb(काष्ठा drm_plane *plane,
			   काष्ठा drm_plane_state *state)
अणु
	काष्ठा tegra_dc *dc = to_tegra_dc(state->crtc);

	अगर (!state->fb)
		वापस 0;

	drm_gem_plane_helper_prepare_fb(plane, state);

	वापस tegra_dc_pin(dc, to_tegra_plane_state(state));
पूर्ण

व्योम tegra_plane_cleanup_fb(काष्ठा drm_plane *plane,
			    काष्ठा drm_plane_state *state)
अणु
	काष्ठा tegra_dc *dc = to_tegra_dc(state->crtc);

	अगर (dc)
		tegra_dc_unpin(dc, to_tegra_plane_state(state));
पूर्ण

पूर्णांक tegra_plane_state_add(काष्ठा tegra_plane *plane,
			  काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा tegra_dc_state *tegra;
	पूर्णांक err;

	/* Propagate errors from allocation or locking failures. */
	crtc_state = drm_atomic_get_crtc_state(state->state, state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	/* Check plane state क्रम visibility and calculate clipping bounds */
	err = drm_atomic_helper_check_plane_state(state, crtc_state,
						  0, पूर्णांक_उच्च, true, true);
	अगर (err < 0)
		वापस err;

	tegra = to_dc_state(crtc_state);

	tegra->planes |= WIN_A_ACT_REQ << plane->index;

	वापस 0;
पूर्ण

पूर्णांक tegra_plane_क्रमmat(u32 fourcc, u32 *क्रमmat, u32 *swap)
अणु
	/* assume no swapping of fetched data */
	अगर (swap)
		*swap = BYTE_SWAP_NOSWAP;

	चयन (fourcc) अणु
	हाल DRM_FORMAT_ARGB4444:
		*क्रमmat = WIN_COLOR_DEPTH_B4G4R4A4;
		अवरोध;

	हाल DRM_FORMAT_ARGB1555:
		*क्रमmat = WIN_COLOR_DEPTH_B5G5R5A1;
		अवरोध;

	हाल DRM_FORMAT_RGB565:
		*क्रमmat = WIN_COLOR_DEPTH_B5G6R5;
		अवरोध;

	हाल DRM_FORMAT_RGBA5551:
		*क्रमmat = WIN_COLOR_DEPTH_A1B5G5R5;
		अवरोध;

	हाल DRM_FORMAT_ARGB8888:
		*क्रमmat = WIN_COLOR_DEPTH_B8G8R8A8;
		अवरोध;

	हाल DRM_FORMAT_ABGR8888:
		*क्रमmat = WIN_COLOR_DEPTH_R8G8B8A8;
		अवरोध;

	हाल DRM_FORMAT_ABGR4444:
		*क्रमmat = WIN_COLOR_DEPTH_R4G4B4A4;
		अवरोध;

	हाल DRM_FORMAT_ABGR1555:
		*क्रमmat = WIN_COLOR_DEPTH_R5G5B5A;
		अवरोध;

	हाल DRM_FORMAT_BGRA5551:
		*क्रमmat = WIN_COLOR_DEPTH_AR5G5B5;
		अवरोध;

	हाल DRM_FORMAT_XRGB1555:
		*क्रमmat = WIN_COLOR_DEPTH_B5G5R5X1;
		अवरोध;

	हाल DRM_FORMAT_RGBX5551:
		*क्रमmat = WIN_COLOR_DEPTH_X1B5G5R5;
		अवरोध;

	हाल DRM_FORMAT_XBGR1555:
		*क्रमmat = WIN_COLOR_DEPTH_R5G5B5X1;
		अवरोध;

	हाल DRM_FORMAT_BGRX5551:
		*क्रमmat = WIN_COLOR_DEPTH_X1R5G5B5;
		अवरोध;

	हाल DRM_FORMAT_BGR565:
		*क्रमmat = WIN_COLOR_DEPTH_R5G6B5;
		अवरोध;

	हाल DRM_FORMAT_BGRA8888:
		*क्रमmat = WIN_COLOR_DEPTH_A8R8G8B8;
		अवरोध;

	हाल DRM_FORMAT_RGBA8888:
		*क्रमmat = WIN_COLOR_DEPTH_A8B8G8R8;
		अवरोध;

	हाल DRM_FORMAT_XRGB8888:
		*क्रमmat = WIN_COLOR_DEPTH_B8G8R8X8;
		अवरोध;

	हाल DRM_FORMAT_XBGR8888:
		*क्रमmat = WIN_COLOR_DEPTH_R8G8B8X8;
		अवरोध;

	हाल DRM_FORMAT_UYVY:
		*क्रमmat = WIN_COLOR_DEPTH_YCbCr422;
		अवरोध;

	हाल DRM_FORMAT_YUYV:
		अगर (!swap)
			वापस -EINVAL;

		*क्रमmat = WIN_COLOR_DEPTH_YCbCr422;
		*swap = BYTE_SWAP_SWAP2;
		अवरोध;

	हाल DRM_FORMAT_YUV420:
		*क्रमmat = WIN_COLOR_DEPTH_YCbCr420P;
		अवरोध;

	हाल DRM_FORMAT_YUV422:
		*क्रमmat = WIN_COLOR_DEPTH_YCbCr422P;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

bool tegra_plane_क्रमmat_is_yuv(अचिन्हित पूर्णांक क्रमmat, bool *planar)
अणु
	चयन (क्रमmat) अणु
	हाल WIN_COLOR_DEPTH_YCbCr422:
	हाल WIN_COLOR_DEPTH_YUV422:
		अगर (planar)
			*planar = false;

		वापस true;

	हाल WIN_COLOR_DEPTH_YCbCr420P:
	हाल WIN_COLOR_DEPTH_YUV420P:
	हाल WIN_COLOR_DEPTH_YCbCr422P:
	हाल WIN_COLOR_DEPTH_YUV422P:
	हाल WIN_COLOR_DEPTH_YCbCr422R:
	हाल WIN_COLOR_DEPTH_YUV422R:
	हाल WIN_COLOR_DEPTH_YCbCr422RA:
	हाल WIN_COLOR_DEPTH_YUV422RA:
		अगर (planar)
			*planar = true;

		वापस true;
	पूर्ण

	अगर (planar)
		*planar = false;

	वापस false;
पूर्ण

अटल bool __drm_क्रमmat_has_alpha(u32 क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_RGBA5551:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_ARGB8888:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक tegra_plane_क्रमmat_get_alpha(अचिन्हित पूर्णांक opaque,
					अचिन्हित पूर्णांक *alpha)
अणु
	अगर (tegra_plane_क्रमmat_is_yuv(opaque, शून्य)) अणु
		*alpha = opaque;
		वापस 0;
	पूर्ण

	चयन (opaque) अणु
	हाल WIN_COLOR_DEPTH_B5G5R5X1:
		*alpha = WIN_COLOR_DEPTH_B5G5R5A1;
		वापस 0;

	हाल WIN_COLOR_DEPTH_X1B5G5R5:
		*alpha = WIN_COLOR_DEPTH_A1B5G5R5;
		वापस 0;

	हाल WIN_COLOR_DEPTH_R8G8B8X8:
		*alpha = WIN_COLOR_DEPTH_R8G8B8A8;
		वापस 0;

	हाल WIN_COLOR_DEPTH_B8G8R8X8:
		*alpha = WIN_COLOR_DEPTH_B8G8R8A8;
		वापस 0;

	हाल WIN_COLOR_DEPTH_B5G6R5:
		*alpha = opaque;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * This is applicable to Tegra20 and Tegra30 only where the opaque क्रमmats can
 * be emulated using the alpha क्रमmats and alpha blending disabled.
 */
अटल पूर्णांक tegra_plane_setup_opacity(काष्ठा tegra_plane *tegra,
				     काष्ठा tegra_plane_state *state)
अणु
	अचिन्हित पूर्णांक क्रमmat;
	पूर्णांक err;

	चयन (state->क्रमmat) अणु
	हाल WIN_COLOR_DEPTH_B5G5R5A1:
	हाल WIN_COLOR_DEPTH_A1B5G5R5:
	हाल WIN_COLOR_DEPTH_R8G8B8A8:
	हाल WIN_COLOR_DEPTH_B8G8R8A8:
		state->opaque = false;
		अवरोध;

	शेष:
		err = tegra_plane_क्रमmat_get_alpha(state->क्रमmat, &क्रमmat);
		अगर (err < 0)
			वापस err;

		state->क्रमmat = क्रमmat;
		state->opaque = true;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_plane_check_transparency(काष्ठा tegra_plane *tegra,
					  काष्ठा tegra_plane_state *state)
अणु
	काष्ठा drm_plane_state *old, *plane_state;
	काष्ठा drm_plane *plane;

	old = drm_atomic_get_old_plane_state(state->base.state, &tegra->base);

	/* check अगर zpos / transparency changed */
	अगर (old->normalized_zpos == state->base.normalized_zpos &&
	    to_tegra_plane_state(old)->opaque == state->opaque)
		वापस 0;

	/* include all sibling planes पूर्णांकo this commit */
	drm_क्रम_each_plane(plane, tegra->base.dev) अणु
		काष्ठा tegra_plane *p = to_tegra_plane(plane);

		/* skip this plane and planes on dअगरferent CRTCs */
		अगर (p == tegra || p->dc != tegra->dc)
			जारी;

		plane_state = drm_atomic_get_plane_state(state->base.state,
							 plane);
		अगर (IS_ERR(plane_state))
			वापस PTR_ERR(plane_state);
	पूर्ण

	वापस 1;
पूर्ण

अटल अचिन्हित पूर्णांक tegra_plane_get_overlap_index(काष्ठा tegra_plane *plane,
						  काष्ठा tegra_plane *other)
अणु
	अचिन्हित पूर्णांक index = 0, i;

	WARN_ON(plane == other);

	क्रम (i = 0; i < 3; i++) अणु
		अगर (i == plane->index)
			जारी;

		अगर (i == other->index)
			अवरोध;

		index++;
	पूर्ण

	वापस index;
पूर्ण

अटल व्योम tegra_plane_update_transparency(काष्ठा tegra_plane *tegra,
					    काष्ठा tegra_plane_state *state)
अणु
	काष्ठा drm_plane_state *new;
	काष्ठा drm_plane *plane;
	अचिन्हित पूर्णांक i;

	क्रम_each_new_plane_in_state(state->base.state, plane, new, i) अणु
		काष्ठा tegra_plane *p = to_tegra_plane(plane);
		अचिन्हित index;

		/* skip this plane and planes on dअगरferent CRTCs */
		अगर (p == tegra || p->dc != tegra->dc)
			जारी;

		index = tegra_plane_get_overlap_index(tegra, p);

		अगर (new->fb && __drm_क्रमmat_has_alpha(new->fb->क्रमmat->क्रमmat))
			state->blending[index].alpha = true;
		अन्यथा
			state->blending[index].alpha = false;

		अगर (new->normalized_zpos > state->base.normalized_zpos)
			state->blending[index].top = true;
		अन्यथा
			state->blending[index].top = false;

		/*
		 * Missing framebuffer means that plane is disabled, in this
		 * हाल mark B / C winकरोw as top to be able to dअगरferentiate
		 * winकरोws indices order in regards to zPos क्रम the middle
		 * winकरोw X / Y रेजिस्टरs programming.
		 */
		अगर (!new->fb)
			state->blending[index].top = (index == 1);
	पूर्ण
पूर्ण

अटल पूर्णांक tegra_plane_setup_transparency(काष्ठा tegra_plane *tegra,
					  काष्ठा tegra_plane_state *state)
अणु
	काष्ठा tegra_plane_state *tegra_state;
	काष्ठा drm_plane_state *new;
	काष्ठा drm_plane *plane;
	पूर्णांक err;

	/*
	 * If planes zpos / transparency changed, sibling planes blending
	 * state may require adjusपंचांगent and in this हाल they will be included
	 * पूर्णांकo this atom commit, otherwise blending state is unchanged.
	 */
	err = tegra_plane_check_transparency(tegra, state);
	अगर (err <= 0)
		वापस err;

	/*
	 * All planes are now in the atomic state, walk them up and update
	 * transparency state क्रम each plane.
	 */
	drm_क्रम_each_plane(plane, tegra->base.dev) अणु
		काष्ठा tegra_plane *p = to_tegra_plane(plane);

		/* skip planes on dअगरferent CRTCs */
		अगर (p->dc != tegra->dc)
			जारी;

		new = drm_atomic_get_new_plane_state(state->base.state, plane);
		tegra_state = to_tegra_plane_state(new);

		/*
		 * There is no need to update blending state क्रम the disabled
		 * plane.
		 */
		अगर (new->fb)
			tegra_plane_update_transparency(p, tegra_state);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tegra_plane_setup_legacy_state(काष्ठा tegra_plane *tegra,
				   काष्ठा tegra_plane_state *state)
अणु
	पूर्णांक err;

	err = tegra_plane_setup_opacity(tegra, state);
	अगर (err < 0)
		वापस err;

	err = tegra_plane_setup_transparency(tegra, state);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
