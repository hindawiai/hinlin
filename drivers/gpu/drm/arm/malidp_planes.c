<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Liviu Dudau <Liviu.Dudau@arm.com>
 *
 * ARM Mali DP plane manipulation routines.
 */

#समावेश <linux/iommu.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "malidp_hw.h"
#समावेश "malidp_drv.h"

/* Layer specअगरic रेजिस्टर offsets */
#घोषणा MALIDP_LAYER_FORMAT		0x000
#घोषणा   LAYER_FORMAT_MASK		0x3f
#घोषणा MALIDP_LAYER_CONTROL		0x004
#घोषणा   LAYER_ENABLE			(1 << 0)
#घोषणा   LAYER_FLOWCFG_MASK		7
#घोषणा   LAYER_FLOWCFG(x)		(((x) & LAYER_FLOWCFG_MASK) << 1)
#घोषणा     LAYER_FLOWCFG_SCALE_SE	3
#घोषणा   LAYER_ROT_OFFSET		8
#घोषणा   LAYER_H_FLIP			(1 << 10)
#घोषणा   LAYER_V_FLIP			(1 << 11)
#घोषणा   LAYER_ROT_MASK		(0xf << 8)
#घोषणा   LAYER_COMP_MASK		(0x3 << 12)
#घोषणा   LAYER_COMP_PIXEL		(0x3 << 12)
#घोषणा   LAYER_COMP_PLANE		(0x2 << 12)
#घोषणा   LAYER_PMUL_ENABLE		(0x1 << 14)
#घोषणा   LAYER_ALPHA_OFFSET		(16)
#घोषणा   LAYER_ALPHA_MASK		(0xff)
#घोषणा   LAYER_ALPHA(x)		(((x) & LAYER_ALPHA_MASK) << LAYER_ALPHA_OFFSET)
#घोषणा MALIDP_LAYER_COMPOSE		0x008
#घोषणा MALIDP_LAYER_SIZE		0x00c
#घोषणा   LAYER_H_VAL(x)		(((x) & 0x1fff) << 0)
#घोषणा   LAYER_V_VAL(x)		(((x) & 0x1fff) << 16)
#घोषणा MALIDP_LAYER_COMP_SIZE		0x010
#घोषणा MALIDP_LAYER_OFFSET		0x014
#घोषणा MALIDP550_LS_ENABLE		0x01c
#घोषणा MALIDP550_LS_R1_IN_SIZE		0x020

#घोषणा MODIFIERS_COUNT_MAX		15

/*
 * This 4-entry look-up-table is used to determine the full 8-bit alpha value
 * क्रम क्रमmats with 1- or 2-bit alpha channels.
 * We set it to give 100%/0% opacity क्रम 1-bit क्रमmats and 100%/66%/33%/0%
 * opacity क्रम 2-bit क्रमmats.
 */
#घोषणा MALIDP_ALPHA_LUT 0xffaa5500

/* page sizes the MMU prefetcher can support */
#घोषणा MALIDP_MMU_PREFETCH_PARTIAL_PGSIZES	(SZ_4K | SZ_64K)
#घोषणा MALIDP_MMU_PREFETCH_FULL_PGSIZES	(SZ_1M | SZ_2M)

/* पढ़ोahead क्रम partial-frame prefetch */
#घोषणा MALIDP_MMU_PREFETCH_READAHEAD		8

अटल व्योम malidp_de_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा malidp_plane *mp = to_malidp_plane(plane);

	drm_plane_cleanup(plane);
	kमुक्त(mp);
पूर्ण

/*
 * Replicate what the शेष ->reset hook करोes: मुक्त the state poपूर्णांकer and
 * allocate a new empty object. We just need enough space to store
 * a malidp_plane_state instead of a drm_plane_state.
 */
अटल व्योम malidp_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा malidp_plane_state *state = to_malidp_plane_state(plane->state);

	अगर (state)
		__drm_atomic_helper_plane_destroy_state(&state->base);
	kमुक्त(state);
	plane->state = शून्य;
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_plane_reset(plane, &state->base);
पूर्ण

अटल काष्ठा
drm_plane_state *malidp_duplicate_plane_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा malidp_plane_state *state, *m_state;

	अगर (!plane->state)
		वापस शून्य;

	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	m_state = to_malidp_plane_state(plane->state);
	__drm_atomic_helper_plane_duplicate_state(plane, &state->base);
	state->roपंचांगem_size = m_state->roपंचांगem_size;
	state->क्रमmat = m_state->क्रमmat;
	state->n_planes = m_state->n_planes;

	state->mmu_prefetch_mode = m_state->mmu_prefetch_mode;
	state->mmu_prefetch_pgsize = m_state->mmu_prefetch_pgsize;

	वापस &state->base;
पूर्ण

अटल व्योम malidp_destroy_plane_state(काष्ठा drm_plane *plane,
				       काष्ठा drm_plane_state *state)
अणु
	काष्ठा malidp_plane_state *m_state = to_malidp_plane_state(state);

	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(m_state);
पूर्ण

अटल स्थिर अक्षर * स्थिर prefetch_mode_names[] = अणु
	[MALIDP_PREFETCH_MODE_NONE] = "MMU_PREFETCH_NONE",
	[MALIDP_PREFETCH_MODE_PARTIAL] = "MMU_PREFETCH_PARTIAL",
	[MALIDP_PREFETCH_MODE_FULL] = "MMU_PREFETCH_FULL",
पूर्ण;

अटल व्योम malidp_plane_atomic_prपूर्णांक_state(काष्ठा drm_prपूर्णांकer *p,
					    स्थिर काष्ठा drm_plane_state *state)
अणु
	काष्ठा malidp_plane_state *ms = to_malidp_plane_state(state);

	drm_म_लिखो(p, "\trotmem_size=%u\n", ms->roपंचांगem_size);
	drm_म_लिखो(p, "\tformat_id=%u\n", ms->क्रमmat);
	drm_म_लिखो(p, "\tn_planes=%u\n", ms->n_planes);
	drm_म_लिखो(p, "\tmmu_prefetch_mode=%s\n",
		   prefetch_mode_names[ms->mmu_prefetch_mode]);
	drm_म_लिखो(p, "\tmmu_prefetch_pgsize=%d\n", ms->mmu_prefetch_pgsize);
पूर्ण

bool malidp_क्रमmat_mod_supported(काष्ठा drm_device *drm,
				 u32 क्रमmat, u64 modअगरier)
अणु
	स्थिर काष्ठा drm_क्रमmat_info *info;
	स्थिर u64 *modअगरiers;
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	स्थिर काष्ठा malidp_hw_regmap *map = &malidp->dev->hw->map;

	अगर (WARN_ON(modअगरier == DRM_FORMAT_MOD_INVALID))
		वापस false;

	/* Some pixel क्रमmats are supported without any modअगरier */
	अगर (modअगरier == DRM_FORMAT_MOD_LINEAR) अणु
		/*
		 * However these pixel क्रमmats need to be supported with
		 * modअगरiers only
		 */
		वापस !malidp_hw_क्रमmat_is_afbc_only(क्रमmat);
	पूर्ण

	अगर ((modअगरier >> 56) != DRM_FORMAT_MOD_VENDOR_ARM) अणु
		DRM_ERROR("Unknown modifier (not Arm)\n");
		वापस false;
	पूर्ण

	अगर (modअगरier &
	    ~DRM_FORMAT_MOD_ARM_AFBC(AFBC_MOD_VALID_BITS)) अणु
		DRM_DEBUG_KMS("Unsupported modifiers\n");
		वापस false;
	पूर्ण

	modअगरiers = malidp_क्रमmat_modअगरiers;

	/* SPLIT buffers must use SPARSE layout */
	अगर (WARN_ON_ONCE((modअगरier & AFBC_SPLIT) && !(modअगरier & AFBC_SPARSE)))
		वापस false;

	/* CBR only applies to YUV क्रमmats, where YTR should be always 0 */
	अगर (WARN_ON_ONCE((modअगरier & AFBC_CBR) && (modअगरier & AFBC_YTR)))
		वापस false;

	जबतक (*modअगरiers != DRM_FORMAT_MOD_INVALID) अणु
		अगर (*modअगरiers == modअगरier)
			अवरोध;

		modअगरiers++;
	पूर्ण

	/* वापस false, अगर the modअगरier was not found */
	अगर (*modअगरiers == DRM_FORMAT_MOD_INVALID) अणु
		DRM_DEBUG_KMS("Unsupported modifier\n");
		वापस false;
	पूर्ण

	info = drm_क्रमmat_info(क्रमmat);

	अगर (info->num_planes != 1) अणु
		DRM_DEBUG_KMS("AFBC buffers expect one plane\n");
		वापस false;
	पूर्ण

	अगर (malidp_hw_क्रमmat_is_linear_only(क्रमmat) == true) अणु
		DRM_DEBUG_KMS("Given format (0x%x) is supported is linear mode only\n",
			      क्रमmat);
		वापस false;
	पूर्ण

	/*
	 * RGB क्रमmats need to provide YTR modअगरier and YUV क्रमmats should not
	 * provide YTR modअगरier.
	 */
	अगर (!(info->is_yuv) != !!(modअगरier & AFBC_FORMAT_MOD_YTR)) अणु
		DRM_DEBUG_KMS("AFBC_FORMAT_MOD_YTR is %s for %s formats\n",
			      info->is_yuv ? "disallowed" : "mandatory",
			      info->is_yuv ? "YUV" : "RGB");
		वापस false;
	पूर्ण

	अगर (modअगरier & AFBC_SPLIT) अणु
		अगर (!info->is_yuv) अणु
			अगर (info->cpp[0] <= 2) अणु
				DRM_DEBUG_KMS("RGB formats <= 16bpp are not supported with SPLIT\n");
				वापस false;
			पूर्ण
		पूर्ण

		अगर ((info->hsub != 1) || (info->vsub != 1)) अणु
			अगर (!(क्रमmat == DRM_FORMAT_YUV420_10BIT &&
			      (map->features & MALIDP_DEVICE_AFBC_YUV_420_10_SUPPORT_SPLIT))) अणु
				DRM_DEBUG_KMS("Formats which are sub-sampled should never be split\n");
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (modअगरier & AFBC_CBR) अणु
		अगर ((info->hsub == 1) || (info->vsub == 1)) अणु
			DRM_DEBUG_KMS("Formats which are not sub-sampled should not have CBR set\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool malidp_क्रमmat_mod_supported_per_plane(काष्ठा drm_plane *plane,
						  u32 क्रमmat, u64 modअगरier)
अणु
	वापस malidp_क्रमmat_mod_supported(plane->dev, क्रमmat, modअगरier);
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs malidp_de_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = malidp_de_plane_destroy,
	.reset = malidp_plane_reset,
	.atomic_duplicate_state = malidp_duplicate_plane_state,
	.atomic_destroy_state = malidp_destroy_plane_state,
	.atomic_prपूर्णांक_state = malidp_plane_atomic_prपूर्णांक_state,
	.क्रमmat_mod_supported = malidp_क्रमmat_mod_supported_per_plane,
पूर्ण;

अटल पूर्णांक malidp_se_check_scaling(काष्ठा malidp_plane *mp,
				   काष्ठा drm_plane_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state =
		drm_atomic_get_existing_crtc_state(state->state, state->crtc);
	काष्ठा malidp_crtc_state *mc;
	u32 src_w, src_h;
	पूर्णांक ret;

	अगर (!crtc_state)
		वापस -EINVAL;

	mc = to_malidp_crtc_state(crtc_state);

	ret = drm_atomic_helper_check_plane_state(state, crtc_state,
						  0, पूर्णांक_उच्च, true, true);
	अगर (ret)
		वापस ret;

	अगर (state->rotation & MALIDP_ROTATED_MASK) अणु
		src_w = state->src_h >> 16;
		src_h = state->src_w >> 16;
	पूर्ण अन्यथा अणु
		src_w = state->src_w >> 16;
		src_h = state->src_h >> 16;
	पूर्ण

	अगर ((state->crtc_w == src_w) && (state->crtc_h == src_h)) अणु
		/* Scaling not necessary क्रम this plane. */
		mc->scaled_planes_mask &= ~(mp->layer->id);
		वापस 0;
	पूर्ण

	अगर (mp->layer->id & (DE_SMART | DE_GRAPHICS2))
		वापस -EINVAL;

	mc->scaled_planes_mask |= mp->layer->id;
	/* Defer scaling requirements calculation to the crtc check. */
	वापस 0;
पूर्ण

अटल u32 malidp_get_pgsize_biपंचांगap(काष्ठा malidp_plane *mp)
अणु
	u32 pgsize_biपंचांगap = 0;

	अगर (iommu_present(&platक्रमm_bus_type)) अणु
		काष्ठा iommu_करोमुख्य *mmu_करोm =
			iommu_get_करोमुख्य_क्रम_dev(mp->base.dev->dev);

		अगर (mmu_करोm)
			pgsize_biपंचांगap = mmu_करोm->pgsize_biपंचांगap;
	पूर्ण

	वापस pgsize_biपंचांगap;
पूर्ण

/*
 * Check अगर the framebuffer is entirely made up of pages at least pgsize in
 * size. Only a heuristic: assumes that each scatterlist entry has been aligned
 * to the largest page size smaller than its length and that the MMU maps to
 * the largest page size possible.
 */
अटल bool malidp_check_pages_threshold(काष्ठा malidp_plane_state *ms,
					 u32 pgsize)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ms->n_planes; i++) अणु
		काष्ठा drm_gem_object *obj;
		काष्ठा drm_gem_cma_object *cma_obj;
		काष्ठा sg_table *sgt;
		काष्ठा scatterlist *sgl;

		obj = drm_gem_fb_get_obj(ms->base.fb, i);
		cma_obj = to_drm_gem_cma_obj(obj);

		अगर (cma_obj->sgt)
			sgt = cma_obj->sgt;
		अन्यथा
			sgt = obj->funcs->get_sg_table(obj);

		अगर (!sgt)
			वापस false;

		sgl = sgt->sgl;

		जबतक (sgl) अणु
			अगर (sgl->length < pgsize) अणु
				अगर (!cma_obj->sgt)
					kमुक्त(sgt);
				वापस false;
			पूर्ण

			sgl = sg_next(sgl);
		पूर्ण
		अगर (!cma_obj->sgt)
			kमुक्त(sgt);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Check अगर it is possible to enable partial-frame MMU prefetch given the
 * current क्रमmat, AFBC state and rotation.
 */
अटल bool malidp_partial_prefetch_supported(u32 क्रमmat, u64 modअगरier,
					      अचिन्हित पूर्णांक rotation)
अणु
	bool afbc, sparse;

	/* rotation and horizontal flip not supported क्रम partial prefetch */
	अगर (rotation & (DRM_MODE_ROTATE_90 | DRM_MODE_ROTATE_180 |
			DRM_MODE_ROTATE_270 | DRM_MODE_REFLECT_X))
		वापस false;

	afbc = modअगरier & DRM_FORMAT_MOD_ARM_AFBC(0);
	sparse = modअगरier & AFBC_FORMAT_MOD_SPARSE;

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_ARGB2101010:
	हाल DRM_FORMAT_RGBA1010102:
	हाल DRM_FORMAT_BGRA1010102:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_RGBA8888:
	हाल DRM_FORMAT_BGRA8888:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_RGBX8888:
	हाल DRM_FORMAT_BGRX8888:
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_RGBA5551:
	हाल DRM_FORMAT_RGB565:
		/* always supported */
		वापस true;

	हाल DRM_FORMAT_ABGR2101010:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_ABGR1555:
	हाल DRM_FORMAT_BGR565:
		/* supported, but अगर AFBC then must be sparse mode */
		वापस (!afbc) || (afbc && sparse);

	हाल DRM_FORMAT_BGR888:
		/* supported, but not क्रम AFBC */
		वापस !afbc;

	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_YUV420:
		/* not supported */
		वापस false;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * Select the preferred MMU prefetch mode. Full-frame prefetch is preferred as
 * दीर्घ as the framebuffer is all large pages. Otherwise partial-frame prefetch
 * is selected as दीर्घ as it is supported क्रम the current क्रमmat. The selected
 * page size क्रम prefetch is वापसed in pgsize_biपंचांगap.
 */
अटल क्रमागत mmu_prefetch_mode malidp_mmu_prefetch_select_mode
		(काष्ठा malidp_plane_state *ms,	u32 *pgsize_biपंचांगap)
अणु
	u32 pgsizes;

	/* get the full-frame prefetch page size(s) supported by the MMU */
	pgsizes = *pgsize_biपंचांगap & MALIDP_MMU_PREFETCH_FULL_PGSIZES;

	जबतक (pgsizes) अणु
		u32 largest_pgsize = 1 << __fls(pgsizes);

		अगर (malidp_check_pages_threshold(ms, largest_pgsize)) अणु
			*pgsize_biपंचांगap = largest_pgsize;
			वापस MALIDP_PREFETCH_MODE_FULL;
		पूर्ण

		pgsizes -= largest_pgsize;
	पूर्ण

	/* get the partial-frame prefetch page size(s) supported by the MMU */
	pgsizes = *pgsize_biपंचांगap & MALIDP_MMU_PREFETCH_PARTIAL_PGSIZES;

	अगर (malidp_partial_prefetch_supported(ms->base.fb->क्रमmat->क्रमmat,
					      ms->base.fb->modअगरier,
					      ms->base.rotation)) अणु
		/* partial prefetch using the smallest page size */
		*pgsize_biपंचांगap = 1 << __ffs(pgsizes);
		वापस MALIDP_PREFETCH_MODE_PARTIAL;
	पूर्ण
	*pgsize_biपंचांगap = 0;
	वापस MALIDP_PREFETCH_MODE_NONE;
पूर्ण

अटल u32 malidp_calc_mmu_control_value(क्रमागत mmu_prefetch_mode mode,
					 u8 पढ़ोahead, u8 n_planes, u32 pgsize)
अणु
	u32 mmu_ctrl = 0;

	अगर (mode != MALIDP_PREFETCH_MODE_NONE) अणु
		mmu_ctrl |= MALIDP_MMU_CTRL_EN;

		अगर (mode == MALIDP_PREFETCH_MODE_PARTIAL) अणु
			mmu_ctrl |= MALIDP_MMU_CTRL_MODE;
			mmu_ctrl |= MALIDP_MMU_CTRL_PP_NUM_REQ(पढ़ोahead);
		पूर्ण

		अगर (pgsize == SZ_64K || pgsize == SZ_2M) अणु
			पूर्णांक i;

			क्रम (i = 0; i < n_planes; i++)
				mmu_ctrl |= MALIDP_MMU_CTRL_PX_PS(i);
		पूर्ण
	पूर्ण

	वापस mmu_ctrl;
पूर्ण

अटल व्योम malidp_de_prefetch_settings(काष्ठा malidp_plane *mp,
					काष्ठा malidp_plane_state *ms)
अणु
	अगर (!mp->layer->mmu_ctrl_offset)
		वापस;

	/* get the page sizes supported by the MMU */
	ms->mmu_prefetch_pgsize = malidp_get_pgsize_biपंचांगap(mp);
	ms->mmu_prefetch_mode  =
		malidp_mmu_prefetch_select_mode(ms, &ms->mmu_prefetch_pgsize);
पूर्ण

अटल पूर्णांक malidp_de_plane_check(काष्ठा drm_plane *plane,
				 काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा malidp_plane *mp = to_malidp_plane(plane);
	काष्ठा malidp_plane_state *ms = to_malidp_plane_state(new_plane_state);
	bool rotated = new_plane_state->rotation & MALIDP_ROTATED_MASK;
	काष्ठा drm_framebuffer *fb;
	u16 pixel_alpha = new_plane_state->pixel_blend_mode;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक block_w, block_h;

	अगर (!new_plane_state->crtc || WARN_ON(!new_plane_state->fb))
		वापस 0;

	fb = new_plane_state->fb;

	ms->क्रमmat = malidp_hw_get_क्रमmat_id(&mp->hwdev->hw->map,
					     mp->layer->id, fb->क्रमmat->क्रमmat,
					     !!fb->modअगरier);
	अगर (ms->क्रमmat == MALIDP_INVALID_FORMAT_ID)
		वापस -EINVAL;

	ms->n_planes = fb->क्रमmat->num_planes;
	क्रम (i = 0; i < ms->n_planes; i++) अणु
		u8 alignment = malidp_hw_get_pitch_align(mp->hwdev, rotated);

		अगर (((fb->pitches[i] * drm_क्रमmat_info_block_height(fb->क्रमmat, i))
				& (alignment - 1)) && !(fb->modअगरier)) अणु
			DRM_DEBUG_KMS("Invalid pitch %u for plane %d\n",
				      fb->pitches[i], i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	block_w = drm_क्रमmat_info_block_width(fb->क्रमmat, 0);
	block_h = drm_क्रमmat_info_block_height(fb->क्रमmat, 0);
	अगर (fb->width % block_w || fb->height % block_h) अणु
		DRM_DEBUG_KMS("Buffer width/height needs to be a multiple of tile sizes");
		वापस -EINVAL;
	पूर्ण
	अगर ((new_plane_state->src_x >> 16) % block_w || (new_plane_state->src_y >> 16) % block_h) अणु
		DRM_DEBUG_KMS("Plane src_x/src_y needs to be a multiple of tile sizes");
		वापस -EINVAL;
	पूर्ण

	अगर ((new_plane_state->crtc_w > mp->hwdev->max_line_size) ||
	    (new_plane_state->crtc_h > mp->hwdev->max_line_size) ||
	    (new_plane_state->crtc_w < mp->hwdev->min_line_size) ||
	    (new_plane_state->crtc_h < mp->hwdev->min_line_size))
		वापस -EINVAL;

	/*
	 * DP550/650 video layers can accept 3 plane क्रमmats only अगर
	 * fb->pitches[1] == fb->pitches[2] since they करोn't have a
	 * third plane stride रेजिस्टर.
	 */
	अगर (ms->n_planes == 3 &&
	    !(mp->hwdev->hw->features & MALIDP_DEVICE_LV_HAS_3_STRIDES) &&
	    (new_plane_state->fb->pitches[1] != new_plane_state->fb->pitches[2]))
		वापस -EINVAL;

	ret = malidp_se_check_scaling(mp, new_plane_state);
	अगर (ret)
		वापस ret;

	/* validate the rotation स्थिरraपूर्णांकs क्रम each layer */
	अगर (new_plane_state->rotation != DRM_MODE_ROTATE_0) अणु
		अगर (mp->layer->rot == ROTATE_NONE)
			वापस -EINVAL;
		अगर ((mp->layer->rot == ROTATE_COMPRESSED) && !(fb->modअगरier))
			वापस -EINVAL;
		/*
		 * packed RGB888 / BGR888 can't be rotated or flipped
		 * unless they are stored in a compressed way
		 */
		अगर ((fb->क्रमmat->क्रमmat == DRM_FORMAT_RGB888 ||
		     fb->क्रमmat->क्रमmat == DRM_FORMAT_BGR888) && !(fb->modअगरier))
			वापस -EINVAL;
	पूर्ण

	/* SMART layer करोes not support AFBC */
	अगर (mp->layer->id == DE_SMART && fb->modअगरier) अणु
		DRM_ERROR("AFBC framebuffer not supported in SMART layer");
		वापस -EINVAL;
	पूर्ण

	ms->roपंचांगem_size = 0;
	अगर (new_plane_state->rotation & MALIDP_ROTATED_MASK) अणु
		पूर्णांक val;

		val = mp->hwdev->hw->roपंचांगem_required(mp->hwdev, new_plane_state->crtc_w,
						     new_plane_state->crtc_h,
						     fb->क्रमmat->क्रमmat,
						     !!(fb->modअगरier));
		अगर (val < 0)
			वापस val;

		ms->roपंचांगem_size = val;
	पूर्ण

	/* HW can't support plane + pixel blending */
	अगर ((new_plane_state->alpha != DRM_BLEND_ALPHA_OPAQUE) &&
	    (pixel_alpha != DRM_MODE_BLEND_PIXEL_NONE) &&
	    fb->क्रमmat->has_alpha)
		वापस -EINVAL;

	malidp_de_prefetch_settings(mp, ms);

	वापस 0;
पूर्ण

अटल व्योम malidp_de_set_plane_pitches(काष्ठा malidp_plane *mp,
					पूर्णांक num_planes, अचिन्हित पूर्णांक pitches[3])
अणु
	पूर्णांक i;
	पूर्णांक num_strides = num_planes;

	अगर (!mp->layer->stride_offset)
		वापस;

	अगर (num_planes == 3)
		num_strides = (mp->hwdev->hw->features &
			       MALIDP_DEVICE_LV_HAS_3_STRIDES) ? 3 : 2;

	/*
	 * The drm convention क्रम pitch is that it needs to cover width * cpp,
	 * but our hardware wants the pitch/stride to cover all rows included
	 * in a tile.
	 */
	क्रम (i = 0; i < num_strides; ++i) अणु
		अचिन्हित पूर्णांक block_h = drm_क्रमmat_info_block_height(mp->base.state->fb->क्रमmat, i);

		malidp_hw_ग_लिखो(mp->hwdev, pitches[i] * block_h,
				mp->layer->base +
				mp->layer->stride_offset + i * 4);
	पूर्ण
पूर्ण

अटल स्थिर s16
malidp_yuv2rgb_coeffs[][DRM_COLOR_RANGE_MAX][MALIDP_COLORADJ_NUM_COEFFS] = अणु
	[DRM_COLOR_YCBCR_BT601][DRM_COLOR_YCBCR_LIMITED_RANGE] = अणु
		1192,    0, 1634,
		1192, -401, -832,
		1192, 2066,    0,
		  64,  512,  512
	पूर्ण,
	[DRM_COLOR_YCBCR_BT601][DRM_COLOR_YCBCR_FULL_RANGE] = अणु
		1024,    0, 1436,
		1024, -352, -731,
		1024, 1815,    0,
		   0,  512,  512
	पूर्ण,
	[DRM_COLOR_YCBCR_BT709][DRM_COLOR_YCBCR_LIMITED_RANGE] = अणु
		1192,    0, 1836,
		1192, -218, -546,
		1192, 2163,    0,
		  64,  512,  512
	पूर्ण,
	[DRM_COLOR_YCBCR_BT709][DRM_COLOR_YCBCR_FULL_RANGE] = अणु
		1024,    0, 1613,
		1024, -192, -479,
		1024, 1900,    0,
		   0,  512,  512
	पूर्ण,
	[DRM_COLOR_YCBCR_BT2020][DRM_COLOR_YCBCR_LIMITED_RANGE] = अणु
		1024,    0, 1476,
		1024, -165, -572,
		1024, 1884,    0,
		   0,  512,  512
	पूर्ण,
	[DRM_COLOR_YCBCR_BT2020][DRM_COLOR_YCBCR_FULL_RANGE] = अणु
		1024,    0, 1510,
		1024, -168, -585,
		1024, 1927,    0,
		   0,  512,  512
	पूर्ण
पूर्ण;

अटल व्योम malidp_de_set_color_encoding(काष्ठा malidp_plane *plane,
					 क्रमागत drm_color_encoding enc,
					 क्रमागत drm_color_range range)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MALIDP_COLORADJ_NUM_COEFFS; i++) अणु
		/* coefficients are चिन्हित, two's complement values */
		malidp_hw_ग_लिखो(plane->hwdev, malidp_yuv2rgb_coeffs[enc][range][i],
				plane->layer->base + plane->layer->yuv2rgb_offset +
				i * 4);
	पूर्ण
पूर्ण

अटल व्योम malidp_de_set_mmu_control(काष्ठा malidp_plane *mp,
				      काष्ठा malidp_plane_state *ms)
अणु
	u32 mmu_ctrl;

	/* check hardware supports MMU prefetch */
	अगर (!mp->layer->mmu_ctrl_offset)
		वापस;

	mmu_ctrl = malidp_calc_mmu_control_value(ms->mmu_prefetch_mode,
						 MALIDP_MMU_PREFETCH_READAHEAD,
						 ms->n_planes,
						 ms->mmu_prefetch_pgsize);

	malidp_hw_ग_लिखो(mp->hwdev, mmu_ctrl,
			mp->layer->base + mp->layer->mmu_ctrl_offset);
पूर्ण

अटल व्योम malidp_set_plane_base_addr(काष्ठा drm_framebuffer *fb,
				       काष्ठा malidp_plane *mp,
				       पूर्णांक plane_index)
अणु
	dma_addr_t paddr;
	u16 ptr;
	काष्ठा drm_plane *plane = &mp->base;
	bool afbc = fb->modअगरier ? true : false;

	ptr = mp->layer->ptr + (plane_index << 4);

	/*
	 * drm_fb_cma_get_gem_addr() alters the physical base address of the
	 * framebuffer as per the plane's src_x, src_y co-ordinates (ie to
	 * take care of source cropping).
	 * For AFBC, this is not needed as the cropping is handled by _AD_CROP_H
	 * and _AD_CROP_V रेजिस्टरs.
	 */
	अगर (!afbc) अणु
		paddr = drm_fb_cma_get_gem_addr(fb, plane->state,
						plane_index);
	पूर्ण अन्यथा अणु
		काष्ठा drm_gem_cma_object *obj;

		obj = drm_fb_cma_get_gem_obj(fb, plane_index);

		अगर (WARN_ON(!obj))
			वापस;
		paddr = obj->paddr;
	पूर्ण

	malidp_hw_ग_लिखो(mp->hwdev, lower_32_bits(paddr), ptr);
	malidp_hw_ग_लिखो(mp->hwdev, upper_32_bits(paddr), ptr + 4);
पूर्ण

अटल व्योम malidp_de_set_plane_afbc(काष्ठा drm_plane *plane)
अणु
	काष्ठा malidp_plane *mp;
	u32 src_w, src_h, val = 0, src_x, src_y;
	काष्ठा drm_framebuffer *fb = plane->state->fb;

	mp = to_malidp_plane(plane);

	/* no afbc_decoder_offset means AFBC is not supported on this plane */
	अगर (!mp->layer->afbc_decoder_offset)
		वापस;

	अगर (!fb->modअगरier) अणु
		malidp_hw_ग_लिखो(mp->hwdev, 0, mp->layer->afbc_decoder_offset);
		वापस;
	पूर्ण

	/* convert src values from Q16 fixed poपूर्णांक to पूर्णांकeger */
	src_w = plane->state->src_w >> 16;
	src_h = plane->state->src_h >> 16;
	src_x = plane->state->src_x >> 16;
	src_y = plane->state->src_y >> 16;

	val = ((fb->width - (src_x + src_w)) << MALIDP_AD_CROP_RIGHT_OFFSET) |
		   src_x;
	malidp_hw_ग_लिखो(mp->hwdev, val,
			mp->layer->afbc_decoder_offset + MALIDP_AD_CROP_H);

	val = ((fb->height - (src_y + src_h)) << MALIDP_AD_CROP_BOTTOM_OFFSET) |
		   src_y;
	malidp_hw_ग_लिखो(mp->hwdev, val,
			mp->layer->afbc_decoder_offset + MALIDP_AD_CROP_V);

	val = MALIDP_AD_EN;
	अगर (fb->modअगरier & AFBC_FORMAT_MOD_SPLIT)
		val |= MALIDP_AD_BS;
	अगर (fb->modअगरier & AFBC_FORMAT_MOD_YTR)
		val |= MALIDP_AD_YTR;

	malidp_hw_ग_लिखो(mp->hwdev, val, mp->layer->afbc_decoder_offset);
पूर्ण

अटल व्योम malidp_de_plane_update(काष्ठा drm_plane *plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	काष्ठा malidp_plane *mp;
	काष्ठा malidp_plane_state *ms = to_malidp_plane_state(plane->state);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	u16 pixel_alpha = new_state->pixel_blend_mode;
	u8 plane_alpha = new_state->alpha >> 8;
	u32 src_w, src_h, dest_w, dest_h, val;
	पूर्णांक i;
	काष्ठा drm_framebuffer *fb = plane->state->fb;

	mp = to_malidp_plane(plane);

	/*
	 * For AFBC framebuffer, use the framebuffer width and height क्रम
	 * configuring layer input size रेजिस्टर.
	 */
	अगर (fb->modअगरier) अणु
		src_w = fb->width;
		src_h = fb->height;
	पूर्ण अन्यथा अणु
		/* convert src values from Q16 fixed poपूर्णांक to पूर्णांकeger */
		src_w = new_state->src_w >> 16;
		src_h = new_state->src_h >> 16;
	पूर्ण

	dest_w = new_state->crtc_w;
	dest_h = new_state->crtc_h;

	val = malidp_hw_पढ़ो(mp->hwdev, mp->layer->base);
	val = (val & ~LAYER_FORMAT_MASK) | ms->क्रमmat;
	malidp_hw_ग_लिखो(mp->hwdev, val, mp->layer->base);

	क्रम (i = 0; i < ms->n_planes; i++)
		malidp_set_plane_base_addr(fb, mp, i);

	malidp_de_set_mmu_control(mp, ms);

	malidp_de_set_plane_pitches(mp, ms->n_planes,
				    new_state->fb->pitches);

	अगर ((plane->state->color_encoding != old_state->color_encoding) ||
	    (plane->state->color_range != old_state->color_range))
		malidp_de_set_color_encoding(mp, plane->state->color_encoding,
					     plane->state->color_range);

	malidp_hw_ग_लिखो(mp->hwdev, LAYER_H_VAL(src_w) | LAYER_V_VAL(src_h),
			mp->layer->base + MALIDP_LAYER_SIZE);

	malidp_hw_ग_लिखो(mp->hwdev, LAYER_H_VAL(dest_w) | LAYER_V_VAL(dest_h),
			mp->layer->base + MALIDP_LAYER_COMP_SIZE);

	malidp_hw_ग_लिखो(mp->hwdev, LAYER_H_VAL(new_state->crtc_x) |
			LAYER_V_VAL(new_state->crtc_y),
			mp->layer->base + MALIDP_LAYER_OFFSET);

	अगर (mp->layer->id == DE_SMART) अणु
		/*
		 * Enable the first rectangle in the SMART layer to be
		 * able to use it as a drm plane.
		 */
		malidp_hw_ग_लिखो(mp->hwdev, 1,
				mp->layer->base + MALIDP550_LS_ENABLE);
		malidp_hw_ग_लिखो(mp->hwdev,
				LAYER_H_VAL(src_w) | LAYER_V_VAL(src_h),
				mp->layer->base + MALIDP550_LS_R1_IN_SIZE);
	पूर्ण

	malidp_de_set_plane_afbc(plane);

	/* first clear the rotation bits */
	val = malidp_hw_पढ़ो(mp->hwdev, mp->layer->base + MALIDP_LAYER_CONTROL);
	val &= ~LAYER_ROT_MASK;

	/* setup the rotation and axis flip bits */
	अगर (new_state->rotation & DRM_MODE_ROTATE_MASK)
		val |= ilog2(plane->state->rotation & DRM_MODE_ROTATE_MASK) <<
		       LAYER_ROT_OFFSET;
	अगर (new_state->rotation & DRM_MODE_REFLECT_X)
		val |= LAYER_H_FLIP;
	अगर (new_state->rotation & DRM_MODE_REFLECT_Y)
		val |= LAYER_V_FLIP;

	val &= ~(LAYER_COMP_MASK | LAYER_PMUL_ENABLE | LAYER_ALPHA(0xff));

	अगर (new_state->alpha != DRM_BLEND_ALPHA_OPAQUE) अणु
		val |= LAYER_COMP_PLANE;
	पूर्ण अन्यथा अगर (new_state->fb->क्रमmat->has_alpha) अणु
		/* We only care about blend mode अगर the क्रमmat has alpha */
		चयन (pixel_alpha) अणु
		हाल DRM_MODE_BLEND_PREMULTI:
			val |= LAYER_COMP_PIXEL | LAYER_PMUL_ENABLE;
			अवरोध;
		हाल DRM_MODE_BLEND_COVERAGE:
			val |= LAYER_COMP_PIXEL;
			अवरोध;
		पूर्ण
	पूर्ण
	val |= LAYER_ALPHA(plane_alpha);

	val &= ~LAYER_FLOWCFG(LAYER_FLOWCFG_MASK);
	अगर (new_state->crtc) अणु
		काष्ठा malidp_crtc_state *m =
			to_malidp_crtc_state(new_state->crtc->state);

		अगर (m->scaler_config.scale_enable &&
		    m->scaler_config.plane_src_id == mp->layer->id)
			val |= LAYER_FLOWCFG(LAYER_FLOWCFG_SCALE_SE);
	पूर्ण

	/* set the 'enable layer' bit */
	val |= LAYER_ENABLE;

	malidp_hw_ग_लिखो(mp->hwdev, val,
			mp->layer->base + MALIDP_LAYER_CONTROL);
पूर्ण

अटल व्योम malidp_de_plane_disable(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा malidp_plane *mp = to_malidp_plane(plane);

	malidp_hw_clearbits(mp->hwdev,
			    LAYER_ENABLE | LAYER_FLOWCFG(LAYER_FLOWCFG_MASK),
			    mp->layer->base + MALIDP_LAYER_CONTROL);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs malidp_de_plane_helper_funcs = अणु
	.atomic_check = malidp_de_plane_check,
	.atomic_update = malidp_de_plane_update,
	.atomic_disable = malidp_de_plane_disable,
पूर्ण;

पूर्णांक malidp_de_planes_init(काष्ठा drm_device *drm)
अणु
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	स्थिर काष्ठा malidp_hw_regmap *map = &malidp->dev->hw->map;
	काष्ठा malidp_plane *plane = शून्य;
	क्रमागत drm_plane_type plane_type;
	अचिन्हित दीर्घ crtcs = BIT(drm->mode_config.num_crtc);
	अचिन्हित दीर्घ flags = DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 | DRM_MODE_ROTATE_180 |
			      DRM_MODE_ROTATE_270 | DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y;
	अचिन्हित पूर्णांक blend_caps = BIT(DRM_MODE_BLEND_PIXEL_NONE) |
				  BIT(DRM_MODE_BLEND_PREMULTI)   |
				  BIT(DRM_MODE_BLEND_COVERAGE);
	u32 *क्रमmats;
	पूर्णांक ret, i = 0, j = 0, n;
	u64 supported_modअगरiers[MODIFIERS_COUNT_MAX];
	स्थिर u64 *modअगरiers;

	modअगरiers = malidp_क्रमmat_modअगरiers;

	अगर (!(map->features & MALIDP_DEVICE_AFBC_SUPPORT_SPLIT)) अणु
		/*
		 * Since our hardware करोes not support SPLIT, so build the list
		 * of supported modअगरiers excluding SPLIT ones.
		 */
		जबतक (*modअगरiers != DRM_FORMAT_MOD_INVALID) अणु
			अगर (!(*modअगरiers & AFBC_SPLIT))
				supported_modअगरiers[j++] = *modअगरiers;

			modअगरiers++;
		पूर्ण
		supported_modअगरiers[j++] = DRM_FORMAT_MOD_INVALID;
		modअगरiers = supported_modअगरiers;
	पूर्ण

	क्रमmats = kसुस्मृति(map->n_pixel_क्रमmats, माप(*क्रमmats), GFP_KERNEL);
	अगर (!क्रमmats) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	क्रम (i = 0; i < map->n_layers; i++) अणु
		u8 id = map->layers[i].id;

		plane = kzalloc(माप(*plane), GFP_KERNEL);
		अगर (!plane) अणु
			ret = -ENOMEM;
			जाओ cleanup;
		पूर्ण

		/* build the list of DRM supported क्रमmats based on the map */
		क्रम (n = 0, j = 0;  j < map->n_pixel_क्रमmats; j++) अणु
			अगर ((map->pixel_क्रमmats[j].layer & id) == id)
				क्रमmats[n++] = map->pixel_क्रमmats[j].क्रमmat;
		पूर्ण

		plane_type = (i == 0) ? DRM_PLANE_TYPE_PRIMARY :
					DRM_PLANE_TYPE_OVERLAY;

		/*
		 * All the layers except smart layer supports AFBC modअगरiers.
		 */
		ret = drm_universal_plane_init(drm, &plane->base, crtcs,
				&malidp_de_plane_funcs, क्रमmats, n,
				(id == DE_SMART) ? शून्य : modअगरiers, plane_type,
				शून्य);

		अगर (ret < 0)
			जाओ cleanup;

		drm_plane_helper_add(&plane->base,
				     &malidp_de_plane_helper_funcs);
		plane->hwdev = malidp->dev;
		plane->layer = &map->layers[i];

		drm_plane_create_alpha_property(&plane->base);
		drm_plane_create_blend_mode_property(&plane->base, blend_caps);

		अगर (id == DE_SMART) अणु
			/* Skip the features which the SMART layer करोesn't have. */
			जारी;
		पूर्ण

		drm_plane_create_rotation_property(&plane->base, DRM_MODE_ROTATE_0, flags);
		malidp_hw_ग_लिखो(malidp->dev, MALIDP_ALPHA_LUT,
				plane->layer->base + MALIDP_LAYER_COMPOSE);

		/* Attach the YUV->RGB property only to video layers */
		अगर (id & (DE_VIDEO1 | DE_VIDEO2)) अणु
			/* शेष encoding क्रम YUV->RGB is BT601 NARROW */
			क्रमागत drm_color_encoding enc = DRM_COLOR_YCBCR_BT601;
			क्रमागत drm_color_range range = DRM_COLOR_YCBCR_LIMITED_RANGE;

			ret = drm_plane_create_color_properties(&plane->base,
					BIT(DRM_COLOR_YCBCR_BT601) | \
					BIT(DRM_COLOR_YCBCR_BT709) | \
					BIT(DRM_COLOR_YCBCR_BT2020),
					BIT(DRM_COLOR_YCBCR_LIMITED_RANGE) | \
					BIT(DRM_COLOR_YCBCR_FULL_RANGE),
					enc, range);
			अगर (!ret)
				/* program the HW रेजिस्टरs */
				malidp_de_set_color_encoding(plane, enc, range);
			अन्यथा
				DRM_WARN("Failed to create video layer %d color properties\n", id);
		पूर्ण
	पूर्ण

	kमुक्त(क्रमmats);

	वापस 0;

cleanup:
	kमुक्त(क्रमmats);

	वापस ret;
पूर्ण
