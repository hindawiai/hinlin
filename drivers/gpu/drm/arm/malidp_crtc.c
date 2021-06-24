<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) COPYRIGHT 2016 ARM Limited. All rights reserved.
 * Author: Liviu Dudau <Liviu.Dudau@arm.com>
 *
 * ARM Mali DP500/DP550/DP650 driver (crtc operations)
 */

#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <video/videomode.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "malidp_drv.h"
#समावेश "malidp_hw.h"

अटल क्रमागत drm_mode_status malidp_crtc_mode_valid(काष्ठा drm_crtc *crtc,
						   स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	/*
	 * check that the hardware can drive the required घड़ी rate,
	 * but skip the check अगर the घड़ी is meant to be disabled (req_rate = 0)
	 */
	दीर्घ rate, req_rate = mode->crtc_घड़ी * 1000;

	अगर (req_rate) अणु
		rate = clk_round_rate(hwdev->pxlclk, req_rate);
		अगर (rate != req_rate) अणु
			DRM_DEBUG_DRIVER("pxlclk doesn't support %ld Hz\n",
					 req_rate);
			वापस MODE_NOCLOCK;
		पूर्ण
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल व्योम malidp_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	काष्ठा videomode vm;
	पूर्णांक err = pm_runसमय_get_sync(crtc->dev->dev);

	अगर (err < 0) अणु
		DRM_DEBUG_DRIVER("Failed to enable runtime power management: %d\n", err);
		वापस;
	पूर्ण

	drm_display_mode_to_videomode(&crtc->state->adjusted_mode, &vm);
	clk_prepare_enable(hwdev->pxlclk);

	/* We rely on firmware to set mclk to a sensible level. */
	clk_set_rate(hwdev->pxlclk, crtc->state->adjusted_mode.crtc_घड़ी * 1000);

	hwdev->hw->modeset(hwdev, &vm);
	hwdev->hw->leave_config_mode(hwdev);
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम malidp_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *old_state = drm_atomic_get_old_crtc_state(state,
									 crtc);
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	पूर्णांक err;

	/* always disable planes on the CRTC that is being turned off */
	drm_atomic_helper_disable_planes_on_crtc(old_state, false);

	drm_crtc_vblank_off(crtc);
	hwdev->hw->enter_config_mode(hwdev);

	clk_disable_unprepare(hwdev->pxlclk);

	err = pm_runसमय_put(crtc->dev->dev);
	अगर (err < 0) अणु
		DRM_DEBUG_DRIVER("Failed to disable runtime power management: %d\n", err);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा gamma_curve_segment अणु
	u16 start;
	u16 end;
पूर्ण segments[MALIDP_COEFFTAB_NUM_COEFFS] = अणु
	/* sector 0 */
	अणु    0,    0 पूर्ण, अणु    1,    1 पूर्ण, अणु    2,    2 पूर्ण, अणु    3,    3 पूर्ण,
	अणु    4,    4 पूर्ण, अणु    5,    5 पूर्ण, अणु    6,    6 पूर्ण, अणु    7,    7 पूर्ण,
	अणु    8,    8 पूर्ण, अणु    9,    9 पूर्ण, अणु   10,   10 पूर्ण, अणु   11,   11 पूर्ण,
	अणु   12,   12 पूर्ण, अणु   13,   13 पूर्ण, अणु   14,   14 पूर्ण, अणु   15,   15 पूर्ण,
	/* sector 1 */
	अणु   16,   19 पूर्ण, अणु   20,   23 पूर्ण, अणु   24,   27 पूर्ण, अणु   28,   31 पूर्ण,
	/* sector 2 */
	अणु   32,   39 पूर्ण, अणु   40,   47 पूर्ण, अणु   48,   55 पूर्ण, अणु   56,   63 पूर्ण,
	/* sector 3 */
	अणु   64,   79 पूर्ण, अणु   80,   95 पूर्ण, अणु   96,  111 पूर्ण, अणु  112,  127 पूर्ण,
	/* sector 4 */
	अणु  128,  159 पूर्ण, अणु  160,  191 पूर्ण, अणु  192,  223 पूर्ण, अणु  224,  255 पूर्ण,
	/* sector 5 */
	अणु  256,  319 पूर्ण, अणु  320,  383 पूर्ण, अणु  384,  447 पूर्ण, अणु  448,  511 पूर्ण,
	/* sector 6 */
	अणु  512,  639 पूर्ण, अणु  640,  767 पूर्ण, अणु  768,  895 पूर्ण, अणु  896, 1023 पूर्ण,
	अणु 1024, 1151 पूर्ण, अणु 1152, 1279 पूर्ण, अणु 1280, 1407 पूर्ण, अणु 1408, 1535 पूर्ण,
	अणु 1536, 1663 पूर्ण, अणु 1664, 1791 पूर्ण, अणु 1792, 1919 पूर्ण, अणु 1920, 2047 पूर्ण,
	अणु 2048, 2175 पूर्ण, अणु 2176, 2303 पूर्ण, अणु 2304, 2431 पूर्ण, अणु 2432, 2559 पूर्ण,
	अणु 2560, 2687 पूर्ण, अणु 2688, 2815 पूर्ण, अणु 2816, 2943 पूर्ण, अणु 2944, 3071 पूर्ण,
	अणु 3072, 3199 पूर्ण, अणु 3200, 3327 पूर्ण, अणु 3328, 3455 पूर्ण, अणु 3456, 3583 पूर्ण,
	अणु 3584, 3711 पूर्ण, अणु 3712, 3839 पूर्ण, अणु 3840, 3967 पूर्ण, अणु 3968, 4095 पूर्ण,
पूर्ण;

#घोषणा DE_COEFTAB_DATA(a, b) ((((a) & 0xfff) << 16) | (((b) & 0xfff)))

अटल व्योम malidp_generate_gamma_table(काष्ठा drm_property_blob *lut_blob,
					u32 coeffs[MALIDP_COEFFTAB_NUM_COEFFS])
अणु
	काष्ठा drm_color_lut *lut = (काष्ठा drm_color_lut *)lut_blob->data;
	पूर्णांक i;

	क्रम (i = 0; i < MALIDP_COEFFTAB_NUM_COEFFS; ++i) अणु
		u32 a, b, delta_in, out_start, out_end;

		delta_in = segments[i].end - segments[i].start;
		/* DP has 12-bit पूर्णांकernal precision क्रम its LUTs. */
		out_start = drm_color_lut_extract(lut[segments[i].start].green,
						  12);
		out_end = drm_color_lut_extract(lut[segments[i].end].green, 12);
		a = (delta_in == 0) ? 0 : ((out_end - out_start) * 256) / delta_in;
		b = out_start;
		coeffs[i] = DE_COEFTAB_DATA(a, b);
	पूर्ण
पूर्ण

/*
 * Check अगर there is a new gamma LUT and अगर it is of an acceptable size. Also,
 * reject any LUTs that use distinct red, green, and blue curves.
 */
अटल पूर्णांक malidp_crtc_atomic_check_gamma(काष्ठा drm_crtc *crtc,
					  काष्ठा drm_crtc_state *state)
अणु
	काष्ठा malidp_crtc_state *mc = to_malidp_crtc_state(state);
	काष्ठा drm_color_lut *lut;
	माप_प्रकार lut_size;
	पूर्णांक i;

	अगर (!state->color_mgmt_changed || !state->gamma_lut)
		वापस 0;

	अगर (crtc->state->gamma_lut &&
	    (crtc->state->gamma_lut->base.id == state->gamma_lut->base.id))
		वापस 0;

	अगर (state->gamma_lut->length % माप(काष्ठा drm_color_lut))
		वापस -EINVAL;

	lut_size = state->gamma_lut->length / माप(काष्ठा drm_color_lut);
	अगर (lut_size != MALIDP_GAMMA_LUT_SIZE)
		वापस -EINVAL;

	lut = (काष्ठा drm_color_lut *)state->gamma_lut->data;
	क्रम (i = 0; i < lut_size; ++i)
		अगर (!((lut[i].red == lut[i].green) &&
		      (lut[i].red == lut[i].blue)))
			वापस -EINVAL;

	अगर (!state->mode_changed) अणु
		पूर्णांक ret;

		state->mode_changed = true;
		/*
		 * Kernelकरोc क्रम drm_atomic_helper_check_modeset mandates that
		 * it be invoked when the driver sets ->mode_changed. Since
		 * changing the gamma LUT करोesn't depend on any बाह्यal
		 * resources, it is safe to call it only once.
		 */
		ret = drm_atomic_helper_check_modeset(crtc->dev, state->state);
		अगर (ret)
			वापस ret;
	पूर्ण

	malidp_generate_gamma_table(state->gamma_lut, mc->gamma_coeffs);
	वापस 0;
पूर्ण

/*
 * Check अगर there is a new CTM and अगर it contains valid input. Valid here means
 * that the number is inside the representable range क्रम a Q3.12 number,
 * excluding truncating the fractional part of the input data.
 *
 * The COLORADJ रेजिस्टरs can be changed atomically.
 */
अटल पूर्णांक malidp_crtc_atomic_check_cपंचांग(काष्ठा drm_crtc *crtc,
					काष्ठा drm_crtc_state *state)
अणु
	काष्ठा malidp_crtc_state *mc = to_malidp_crtc_state(state);
	काष्ठा drm_color_cपंचांग *cपंचांग;
	पूर्णांक i;

	अगर (!state->color_mgmt_changed)
		वापस 0;

	अगर (!state->cपंचांग)
		वापस 0;

	अगर (crtc->state->cपंचांग && (crtc->state->cपंचांग->base.id ==
				 state->cपंचांग->base.id))
		वापस 0;

	/*
	 * The size of the cपंचांग is checked in
	 * drm_atomic_replace_property_blob_from_id.
	 */
	cपंचांग = (काष्ठा drm_color_cपंचांग *)state->cपंचांग->data;
	क्रम (i = 0; i < ARRAY_SIZE(cपंचांग->matrix); ++i) अणु
		/* Convert from S31.32 to Q3.12. */
		s64 val = cपंचांग->matrix[i];
		u32 mag = ((((u64)val) & ~BIT_ULL(63)) >> 20) &
			  GENMASK_ULL(14, 0);

		/*
		 * Convert to 2s complement and check the destination's top bit
		 * क्रम overflow. NB: Can't check before converting or it'd
		 * incorrectly reject the हाल:
		 * sign == 1
		 * mag == 0x2000
		 */
		अगर (val & BIT_ULL(63))
			mag = ~mag + 1;
		अगर (!!(val & BIT_ULL(63)) != !!(mag & BIT(14)))
			वापस -EINVAL;
		mc->coloradj_coeffs[i] = mag;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक malidp_crtc_atomic_check_scaling(काष्ठा drm_crtc *crtc,
					    काष्ठा drm_crtc_state *state)
अणु
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	काष्ठा malidp_crtc_state *cs = to_malidp_crtc_state(state);
	काष्ठा malidp_se_config *s = &cs->scaler_config;
	काष्ठा drm_plane *plane;
	काष्ठा videomode vm;
	स्थिर काष्ठा drm_plane_state *pstate;
	u32 h_upscale_factor = 0; /* U16.16 */
	u32 v_upscale_factor = 0; /* U16.16 */
	u8 scaling = cs->scaled_planes_mask;
	पूर्णांक ret;

	अगर (!scaling) अणु
		s->scale_enable = false;
		जाओ mclk_calc;
	पूर्ण

	/* The scaling engine can only handle one plane at a समय. */
	अगर (scaling & (scaling - 1))
		वापस -EINVAL;

	drm_atomic_crtc_state_क्रम_each_plane_state(plane, pstate, state) अणु
		काष्ठा malidp_plane *mp = to_malidp_plane(plane);
		u32 phase;

		अगर (!(mp->layer->id & scaling))
			जारी;

		/*
		 * Convert crtc_[w|h] to U32.32, then भागide by U16.16 src_[w|h]
		 * to get the U16.16 result.
		 */
		h_upscale_factor = भाग_u64((u64)pstate->crtc_w << 32,
					   pstate->src_w);
		v_upscale_factor = भाग_u64((u64)pstate->crtc_h << 32,
					   pstate->src_h);

		s->enhancer_enable = ((h_upscale_factor >> 16) >= 2 ||
				      (v_upscale_factor >> 16) >= 2);

		अगर (pstate->rotation & MALIDP_ROTATED_MASK) अणु
			s->input_w = pstate->src_h >> 16;
			s->input_h = pstate->src_w >> 16;
		पूर्ण अन्यथा अणु
			s->input_w = pstate->src_w >> 16;
			s->input_h = pstate->src_h >> 16;
		पूर्ण

		s->output_w = pstate->crtc_w;
		s->output_h = pstate->crtc_h;

#घोषणा SE_N_PHASE 4
#घोषणा SE_SHIFT_N_PHASE 12
		/* Calculate initial_phase and delta_phase क्रम horizontal. */
		phase = s->input_w;
		s->h_init_phase =
				((phase << SE_N_PHASE) / s->output_w + 1) / 2;

		phase = s->input_w;
		phase <<= (SE_SHIFT_N_PHASE + SE_N_PHASE);
		s->h_delta_phase = phase / s->output_w;

		/* Same क्रम vertical. */
		phase = s->input_h;
		s->v_init_phase =
				((phase << SE_N_PHASE) / s->output_h + 1) / 2;

		phase = s->input_h;
		phase <<= (SE_SHIFT_N_PHASE + SE_N_PHASE);
		s->v_delta_phase = phase / s->output_h;
#अघोषित SE_N_PHASE
#अघोषित SE_SHIFT_N_PHASE
		s->plane_src_id = mp->layer->id;
	पूर्ण

	s->scale_enable = true;
	s->hcoeff = malidp_se_select_coeffs(h_upscale_factor);
	s->vcoeff = malidp_se_select_coeffs(v_upscale_factor);

mclk_calc:
	drm_display_mode_to_videomode(&state->adjusted_mode, &vm);
	ret = hwdev->hw->se_calc_mclk(hwdev, s, &vm);
	अगर (ret < 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक malidp_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;
	काष्ठा drm_plane *plane;
	स्थिर काष्ठा drm_plane_state *pstate;
	u32 rot_mem_मुक्त, rot_mem_usable;
	पूर्णांक rotated_planes = 0;
	पूर्णांक ret;

	/*
	 * check अगर there is enough rotation memory available क्रम planes
	 * that need 90तओ and 270तओ rotion or planes that are compressed.
	 * Each plane has set its required memory size in the ->plane_check()
	 * callback, here we only make sure that the sums are less that the
	 * total usable memory.
	 *
	 * The rotation memory allocation algorithm (क्रम each plane):
	 *  a. If no more rotated or compressed planes exist, all reमुख्यing
	 *     rotate memory in the bank is available क्रम use by the plane.
	 *  b. If other rotated or compressed planes exist, and plane's
	 *     layer ID is DE_VIDEO1, it can use all the memory from first bank
	 *     अगर secondary rotation memory bank is available, otherwise it can
	 *     use up to half the bank's memory.
	 *  c. If other rotated or compressed planes exist, and plane's layer ID
	 *     is not DE_VIDEO1, it can use half of the available memory.
	 *
	 * Note: this algorithm assumes that the order in which the planes are
	 * checked always has DE_VIDEO1 plane first in the list अगर it is
	 * rotated. Because that is how we create the planes in the first
	 * place, under current DRM version things work, but अगर ever the order
	 * in which drm_atomic_crtc_state_क्रम_each_plane() iterates over planes
	 * changes, we need to pre-sort the planes beक्रमe validation.
	 */

	/* first count the number of rotated planes */
	drm_atomic_crtc_state_क्रम_each_plane_state(plane, pstate, crtc_state) अणु
		काष्ठा drm_framebuffer *fb = pstate->fb;

		अगर ((pstate->rotation & MALIDP_ROTATED_MASK) || fb->modअगरier)
			rotated_planes++;
	पूर्ण

	rot_mem_मुक्त = hwdev->rotation_memory[0];
	/*
	 * अगर we have more than 1 plane using rotation memory, use the second
	 * block of rotation memory as well
	 */
	अगर (rotated_planes > 1)
		rot_mem_मुक्त += hwdev->rotation_memory[1];

	/* now validate the rotation memory requirements */
	drm_atomic_crtc_state_क्रम_each_plane_state(plane, pstate, crtc_state) अणु
		काष्ठा malidp_plane *mp = to_malidp_plane(plane);
		काष्ठा malidp_plane_state *ms = to_malidp_plane_state(pstate);
		काष्ठा drm_framebuffer *fb = pstate->fb;

		अगर ((pstate->rotation & MALIDP_ROTATED_MASK) || fb->modअगरier) अणु
			/* process current plane */
			rotated_planes--;

			अगर (!rotated_planes) अणु
				/* no more rotated planes, we can use what's left */
				rot_mem_usable = rot_mem_मुक्त;
			पूर्ण अन्यथा अणु
				अगर ((mp->layer->id != DE_VIDEO1) ||
				    (hwdev->rotation_memory[1] == 0))
					rot_mem_usable = rot_mem_मुक्त / 2;
				अन्यथा
					rot_mem_usable = hwdev->rotation_memory[0];
			पूर्ण

			rot_mem_मुक्त -= rot_mem_usable;

			अगर (ms->roपंचांगem_size > rot_mem_usable)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* If only the ग_लिखोback routing has changed, we करोn't need a modeset */
	अगर (crtc_state->connectors_changed) अणु
		u32 old_mask = crtc->state->connector_mask;
		u32 new_mask = crtc_state->connector_mask;

		अगर ((old_mask ^ new_mask) ==
		    (1 << drm_connector_index(&malidp->mw_connector.base)))
			crtc_state->connectors_changed = false;
	पूर्ण

	ret = malidp_crtc_atomic_check_gamma(crtc, crtc_state);
	ret = ret ? ret : malidp_crtc_atomic_check_cपंचांग(crtc, crtc_state);
	ret = ret ? ret : malidp_crtc_atomic_check_scaling(crtc, crtc_state);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs malidp_crtc_helper_funcs = अणु
	.mode_valid = malidp_crtc_mode_valid,
	.atomic_check = malidp_crtc_atomic_check,
	.atomic_enable = malidp_crtc_atomic_enable,
	.atomic_disable = malidp_crtc_atomic_disable,
पूर्ण;

अटल काष्ठा drm_crtc_state *malidp_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा malidp_crtc_state *state, *old_state;

	अगर (WARN_ON(!crtc->state))
		वापस शून्य;

	old_state = to_malidp_crtc_state(crtc->state);
	state = kदो_स्मृति(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);
	स_नकल(state->gamma_coeffs, old_state->gamma_coeffs,
	       माप(state->gamma_coeffs));
	स_नकल(state->coloradj_coeffs, old_state->coloradj_coeffs,
	       माप(state->coloradj_coeffs));
	स_नकल(&state->scaler_config, &old_state->scaler_config,
	       माप(state->scaler_config));
	state->scaled_planes_mask = 0;

	वापस &state->base;
पूर्ण

अटल व्योम malidp_crtc_destroy_state(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_crtc_state *state)
अणु
	काष्ठा malidp_crtc_state *mali_state = शून्य;

	अगर (state) अणु
		mali_state = to_malidp_crtc_state(state);
		__drm_atomic_helper_crtc_destroy_state(state);
	पूर्ण

	kमुक्त(mali_state);
पूर्ण

अटल व्योम malidp_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा malidp_crtc_state *state =
		kzalloc(माप(*state), GFP_KERNEL);

	अगर (crtc->state)
		malidp_crtc_destroy_state(crtc, crtc->state);

	__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल पूर्णांक malidp_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	malidp_hw_enable_irq(hwdev, MALIDP_DE_BLOCK,
			     hwdev->hw->map.de_irq_map.vsync_irq);
	वापस 0;
पूर्ण

अटल व्योम malidp_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा malidp_drm *malidp = crtc_to_malidp_device(crtc);
	काष्ठा malidp_hw_device *hwdev = malidp->dev;

	malidp_hw_disable_irq(hwdev, MALIDP_DE_BLOCK,
			      hwdev->hw->map.de_irq_map.vsync_irq);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs malidp_crtc_funcs = अणु
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.reset = malidp_crtc_reset,
	.atomic_duplicate_state = malidp_crtc_duplicate_state,
	.atomic_destroy_state = malidp_crtc_destroy_state,
	.enable_vblank = malidp_crtc_enable_vblank,
	.disable_vblank = malidp_crtc_disable_vblank,
पूर्ण;

पूर्णांक malidp_crtc_init(काष्ठा drm_device *drm)
अणु
	काष्ठा malidp_drm *malidp = drm->dev_निजी;
	काष्ठा drm_plane *primary = शून्य, *plane;
	पूर्णांक ret;

	ret = malidp_de_planes_init(drm);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to initialise planes\n");
		वापस ret;
	पूर्ण

	drm_क्रम_each_plane(plane, drm) अणु
		अगर (plane->type == DRM_PLANE_TYPE_PRIMARY) अणु
			primary = plane;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!primary) अणु
		DRM_ERROR("no primary plane found\n");
		वापस -EINVAL;
	पूर्ण

	ret = drm_crtc_init_with_planes(drm, &malidp->crtc, primary, शून्य,
					&malidp_crtc_funcs, शून्य);
	अगर (ret)
		वापस ret;

	drm_crtc_helper_add(&malidp->crtc, &malidp_crtc_helper_funcs);
	drm_mode_crtc_set_gamma_size(&malidp->crtc, MALIDP_GAMMA_LUT_SIZE);
	/* No inverse-gamma: it is per-plane. */
	drm_crtc_enable_color_mgmt(&malidp->crtc, 0, true, MALIDP_GAMMA_LUT_SIZE);

	malidp_se_set_enh_coeffs(malidp->dev);

	वापस 0;
पूर्ण
