<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */
#समावेश "amdgpu.h"
#समावेश "amdgpu_mode.h"
#समावेश "amdgpu_dm.h"
#समावेश "dc.h"
#समावेश "modules/color/color_gamma.h"
#समावेश "basics/conversion.h"

/*
 * The DC पूर्णांकerface to HW gives us the following color management blocks
 * per pipe (surface):
 *
 * - Input gamma LUT (de-normalized)
 * - Input CSC (normalized)
 * - Surface degamma LUT (normalized)
 * - Surface CSC (normalized)
 * - Surface regamma LUT (normalized)
 * - Output CSC (normalized)
 *
 * But these aren't a direct mapping to DRM color properties. The current DRM
 * पूर्णांकerface exposes CRTC degamma, CRTC CTM and CRTC regamma जबतक our hardware
 * is essentially giving:
 *
 * Plane CTM -> Plane degamma -> Plane CTM -> Plane regamma -> Plane CTM
 *
 * The input gamma LUT block isn't really applicable here since it operates
 * on the actual input data itself rather than the HW fp representation. The
 * input and output CSC blocks are technically available to use as part of
 * the DC पूर्णांकerface but are typically used पूर्णांकernally by DC क्रम conversions
 * between color spaces. These could be blended together with user
 * adjusपंचांगents in the future but क्रम now these should reमुख्य untouched.
 *
 * The pipe blending also happens after these blocks so we करोn't actually
 * support any CRTC props with correct blending with multiple planes - but we
 * can still support CRTC color management properties in DM in most single
 * plane हालs correctly with clever management of the DC पूर्णांकerface in DM.
 *
 * As per DRM करोcumentation, blocks should be in hardware bypass when their
 * respective property is set to शून्य. A linear DGM/RGM LUT should also
 * considered as putting the respective block पूर्णांकo bypass mode.
 *
 * This means that the following
 * configuration is assumed to be the शेष:
 *
 * Plane DGM Bypass -> Plane CTM Bypass -> Plane RGM Bypass -> ...
 * CRTC DGM Bypass -> CRTC CTM Bypass -> CRTC RGM Bypass
 */

#घोषणा MAX_DRM_LUT_VALUE 0xFFFF

/*
 * Initialize the color module.
 *
 * We're not using the full color module, only certain components.
 * Only call setup functions क्रम components that we need.
 */
व्योम amdgpu_dm_init_color_mod(व्योम)
अणु
	setup_x_poपूर्णांकs_distribution();
पूर्ण

/* Extracts the DRM lut and lut size from a blob. */
अटल स्थिर काष्ठा drm_color_lut *
__extract_blob_lut(स्थिर काष्ठा drm_property_blob *blob, uपूर्णांक32_t *size)
अणु
	*size = blob ? drm_color_lut_size(blob) : 0;
	वापस blob ? (काष्ठा drm_color_lut *)blob->data : शून्य;
पूर्ण

/*
 * Return true अगर the given lut is a linear mapping of values, i.e. it acts
 * like a bypass LUT.
 *
 * It is considered linear अगर the lut represents:
 * f(a) = (0xFF00/MAX_COLOR_LUT_ENTRIES-1)a; क्रम पूर्णांकeger a in
 *                                           [0, MAX_COLOR_LUT_ENTRIES)
 */
अटल bool __is_lut_linear(स्थिर काष्ठा drm_color_lut *lut, uपूर्णांक32_t size)
अणु
	पूर्णांक i;
	uपूर्णांक32_t expected;
	पूर्णांक delta;

	क्रम (i = 0; i < size; i++) अणु
		/* All color values should equal */
		अगर ((lut[i].red != lut[i].green) || (lut[i].green != lut[i].blue))
			वापस false;

		expected = i * MAX_DRM_LUT_VALUE / (size-1);

		/* Allow a +/-1 error. */
		delta = lut[i].red - expected;
		अगर (delta < -1 || 1 < delta)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Convert the drm_color_lut to dc_gamma. The conversion depends on the size
 * of the lut - whether or not it's legacy.
 */
अटल व्योम __drm_lut_to_dc_gamma(स्थिर काष्ठा drm_color_lut *lut,
				  काष्ठा dc_gamma *gamma, bool is_legacy)
अणु
	uपूर्णांक32_t r, g, b;
	पूर्णांक i;

	अगर (is_legacy) अणु
		क्रम (i = 0; i < MAX_COLOR_LEGACY_LUT_ENTRIES; i++) अणु
			r = drm_color_lut_extract(lut[i].red, 16);
			g = drm_color_lut_extract(lut[i].green, 16);
			b = drm_color_lut_extract(lut[i].blue, 16);

			gamma->entries.red[i] = dc_fixpt_from_पूर्णांक(r);
			gamma->entries.green[i] = dc_fixpt_from_पूर्णांक(g);
			gamma->entries.blue[i] = dc_fixpt_from_पूर्णांक(b);
		पूर्ण
		वापस;
	पूर्ण

	/* अन्यथा */
	क्रम (i = 0; i < MAX_COLOR_LUT_ENTRIES; i++) अणु
		r = drm_color_lut_extract(lut[i].red, 16);
		g = drm_color_lut_extract(lut[i].green, 16);
		b = drm_color_lut_extract(lut[i].blue, 16);

		gamma->entries.red[i] = dc_fixpt_from_fraction(r, MAX_DRM_LUT_VALUE);
		gamma->entries.green[i] = dc_fixpt_from_fraction(g, MAX_DRM_LUT_VALUE);
		gamma->entries.blue[i] = dc_fixpt_from_fraction(b, MAX_DRM_LUT_VALUE);
	पूर्ण
पूर्ण

/*
 * Converts a DRM CTM to a DC CSC भग्न matrix.
 * The matrix needs to be a 3x4 (12 entry) matrix.
 */
अटल व्योम __drm_cपंचांग_to_dc_matrix(स्थिर काष्ठा drm_color_cपंचांग *cपंचांग,
				   काष्ठा fixed31_32 *matrix)
अणु
	पूर्णांक64_t val;
	पूर्णांक i;

	/*
	 * DRM gives a 3x3 matrix, but DC wants 3x4. Assuming we're operating
	 * with homogeneous coordinates, augment the matrix with 0's.
	 *
	 * The क्रमmat provided is S31.32, using चिन्हित-magnitude representation.
	 * Our fixed31_32 is also S31.32, but is using 2's complement. We have
	 * to convert from चिन्हित-magnitude to 2's complement.
	 */
	क्रम (i = 0; i < 12; i++) अणु
		/* Skip 4th element */
		अगर (i % 4 == 3) अणु
			matrix[i] = dc_fixpt_zero;
			जारी;
		पूर्ण

		/* gamut_remap_matrix[i] = cपंचांग[i - न्यूनमान(i/4)] */
		val = cपंचांग->matrix[i - (i / 4)];
		/* If negative, convert to 2's complement. */
		अगर (val & (1ULL << 63))
			val = -(val & ~(1ULL << 63));

		matrix[i].value = val;
	पूर्ण
पूर्ण

/* Calculates the legacy transfer function - only क्रम sRGB input space. */
अटल पूर्णांक __set_legacy_tf(काष्ठा dc_transfer_func *func,
			   स्थिर काष्ठा drm_color_lut *lut, uपूर्णांक32_t lut_size,
			   bool has_rom)
अणु
	काष्ठा dc_gamma *gamma = शून्य;
	काष्ठा calculate_buffer cal_buffer = अणु0पूर्ण;
	bool res;

	ASSERT(lut && lut_size == MAX_COLOR_LEGACY_LUT_ENTRIES);

	cal_buffer.buffer_index = -1;

	gamma = dc_create_gamma();
	अगर (!gamma)
		वापस -ENOMEM;

	gamma->type = GAMMA_RGB_256;
	gamma->num_entries = lut_size;
	__drm_lut_to_dc_gamma(lut, gamma, true);

	res = mod_color_calculate_regamma_params(func, gamma, true, has_rom,
						 शून्य, &cal_buffer);

	dc_gamma_release(&gamma);

	वापस res ? 0 : -ENOMEM;
पूर्ण

/* Calculates the output transfer function based on expected input space. */
अटल पूर्णांक __set_output_tf(काष्ठा dc_transfer_func *func,
			   स्थिर काष्ठा drm_color_lut *lut, uपूर्णांक32_t lut_size,
			   bool has_rom)
अणु
	काष्ठा dc_gamma *gamma = शून्य;
	काष्ठा calculate_buffer cal_buffer = अणु0पूर्ण;
	bool res;

	ASSERT(lut && lut_size == MAX_COLOR_LUT_ENTRIES);

	cal_buffer.buffer_index = -1;

	gamma = dc_create_gamma();
	अगर (!gamma)
		वापस -ENOMEM;

	gamma->num_entries = lut_size;
	__drm_lut_to_dc_gamma(lut, gamma, false);

	अगर (func->tf == TRANSFER_FUNCTION_LINEAR) अणु
		/*
		 * Color module करोesn't like calculating regamma params
		 * on top of a linear input. But degamma params can be used
		 * instead to simulate this.
		 */
		gamma->type = GAMMA_CUSTOM;
		res = mod_color_calculate_degamma_params(शून्य, func,
							gamma, true);
	पूर्ण अन्यथा अणु
		/*
		 * Assume sRGB. The actual mapping will depend on whether the
		 * input was legacy or not.
		 */
		gamma->type = GAMMA_CS_TFM_1D;
		res = mod_color_calculate_regamma_params(func, gamma, false,
							 has_rom, शून्य, &cal_buffer);
	पूर्ण

	dc_gamma_release(&gamma);

	वापस res ? 0 : -ENOMEM;
पूर्ण

/* Caculates the input transfer function based on expected input space. */
अटल पूर्णांक __set_input_tf(काष्ठा dc_transfer_func *func,
			  स्थिर काष्ठा drm_color_lut *lut, uपूर्णांक32_t lut_size)
अणु
	काष्ठा dc_gamma *gamma = शून्य;
	bool res;

	gamma = dc_create_gamma();
	अगर (!gamma)
		वापस -ENOMEM;

	gamma->type = GAMMA_CUSTOM;
	gamma->num_entries = lut_size;

	__drm_lut_to_dc_gamma(lut, gamma, false);

	res = mod_color_calculate_degamma_params(शून्य, func, gamma, true);
	dc_gamma_release(&gamma);

	वापस res ? 0 : -ENOMEM;
पूर्ण

/**
 * amdgpu_dm_update_crtc_color_mgmt: Maps DRM color management to DC stream.
 * @crtc: amdgpu_dm crtc state
 *
 * With no plane level color management properties we're मुक्त to use any
 * of the HW blocks as दीर्घ as the CRTC CTM always comes beक्रमe the
 * CRTC RGM and after the CRTC DGM.
 *
 * The CRTC RGM block will be placed in the RGM LUT block अगर it is non-linear.
 * The CRTC DGM block will be placed in the DGM LUT block अगर it is non-linear.
 * The CRTC CTM will be placed in the gamut remap block अगर it is non-linear.
 *
 * The RGM block is typically more fully featured and accurate across
 * all ASICs - DCE can't support a custom non-linear CRTC DGM.
 *
 * For supporting both plane level color management and CRTC level color
 * management at once we have to either restrict the usage of CRTC properties
 * or blend adjusपंचांगents together.
 *
 * Returns 0 on success.
 */
पूर्णांक amdgpu_dm_update_crtc_color_mgmt(काष्ठा dm_crtc_state *crtc)
अणु
	काष्ठा dc_stream_state *stream = crtc->stream;
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->base.state->dev);
	bool has_rom = adev->asic_type <= CHIP_RAVEN;
	काष्ठा drm_color_cपंचांग *cपंचांग = शून्य;
	स्थिर काष्ठा drm_color_lut *degamma_lut, *regamma_lut;
	uपूर्णांक32_t degamma_size, regamma_size;
	bool has_regamma, has_degamma;
	bool is_legacy;
	पूर्णांक r;

	degamma_lut = __extract_blob_lut(crtc->base.degamma_lut, &degamma_size);
	अगर (degamma_lut && degamma_size != MAX_COLOR_LUT_ENTRIES)
		वापस -EINVAL;

	regamma_lut = __extract_blob_lut(crtc->base.gamma_lut, &regamma_size);
	अगर (regamma_lut && regamma_size != MAX_COLOR_LUT_ENTRIES &&
	    regamma_size != MAX_COLOR_LEGACY_LUT_ENTRIES)
		वापस -EINVAL;

	has_degamma =
		degamma_lut && !__is_lut_linear(degamma_lut, degamma_size);

	has_regamma =
		regamma_lut && !__is_lut_linear(regamma_lut, regamma_size);

	is_legacy = regamma_size == MAX_COLOR_LEGACY_LUT_ENTRIES;

	/* Reset all adjusपंचांगents. */
	crtc->cm_has_degamma = false;
	crtc->cm_is_degamma_srgb = false;

	/* Setup regamma and degamma. */
	अगर (is_legacy) अणु
		/*
		 * Legacy regamma क्रमces us to use the sRGB RGM as a base.
		 * This also means we can't use linear DGM since DGM needs
		 * to use sRGB as a base as well, resulting in incorrect CRTC
		 * DGM and CRTC CTM.
		 *
		 * TODO: Just map this to the standard regamma पूर्णांकerface
		 * instead since this isn't really right. One of the हालs
		 * where this setup currently fails is trying to करो an
		 * inverse color ramp in legacy userspace.
		 */
		crtc->cm_is_degamma_srgb = true;
		stream->out_transfer_func->type = TF_TYPE_DISTRIBUTED_POINTS;
		stream->out_transfer_func->tf = TRANSFER_FUNCTION_SRGB;

		r = __set_legacy_tf(stream->out_transfer_func, regamma_lut,
				    regamma_size, has_rom);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (has_regamma) अणु
		/* CRTC RGM goes पूर्णांकo RGM LUT. */
		stream->out_transfer_func->type = TF_TYPE_DISTRIBUTED_POINTS;
		stream->out_transfer_func->tf = TRANSFER_FUNCTION_LINEAR;

		r = __set_output_tf(stream->out_transfer_func, regamma_lut,
				    regamma_size, has_rom);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अणु
		/*
		 * No CRTC RGM means we can just put the block पूर्णांकo bypass
		 * since we करोn't have any plane level adjusपंचांगents using it.
		 */
		stream->out_transfer_func->type = TF_TYPE_BYPASS;
		stream->out_transfer_func->tf = TRANSFER_FUNCTION_LINEAR;
	पूर्ण

	/*
	 * CRTC DGM goes पूर्णांकo DGM LUT. It would be nice to place it
	 * पूर्णांकo the RGM since it's a more featured block but we'd
	 * have to place the CTM in the OCSC in that हाल.
	 */
	crtc->cm_has_degamma = has_degamma;

	/* Setup CRTC CTM. */
	अगर (crtc->base.cपंचांग) अणु
		cपंचांग = (काष्ठा drm_color_cपंचांग *)crtc->base.cपंचांग->data;

		/*
		 * Gamut remapping must be used क्रम gamma correction
		 * since it comes beक्रमe the regamma correction.
		 *
		 * OCSC could be used क्रम gamma correction, but we'd need to
		 * blend the adjusपंचांगents together with the required output
		 * conversion matrix - so just use the gamut remap block
		 * क्रम now.
		 */
		__drm_cपंचांग_to_dc_matrix(cपंचांग, stream->gamut_remap_matrix.matrix);

		stream->gamut_remap_matrix.enable_remap = true;
		stream->csc_color_matrix.enable_adjusपंचांगent = false;
	पूर्ण अन्यथा अणु
		/* Bypass CTM. */
		stream->gamut_remap_matrix.enable_remap = false;
		stream->csc_color_matrix.enable_adjusपंचांगent = false;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_dm_update_plane_color_mgmt: Maps DRM color management to DC plane.
 * @crtc: amdgpu_dm crtc state
 * @dc_plane_state: target DC surface
 *
 * Update the underlying dc_stream_state's input transfer function (ITF) in
 * preparation क्रम hardware commit. The transfer function used depends on
 * the prepartion करोne on the stream क्रम color management.
 *
 * Returns 0 on success.
 */
पूर्णांक amdgpu_dm_update_plane_color_mgmt(काष्ठा dm_crtc_state *crtc,
				      काष्ठा dc_plane_state *dc_plane_state)
अणु
	स्थिर काष्ठा drm_color_lut *degamma_lut;
	क्रमागत dc_transfer_func_predefined tf = TRANSFER_FUNCTION_SRGB;
	uपूर्णांक32_t degamma_size;
	पूर्णांक r;

	/* Get the correct base transfer function क्रम implicit degamma. */
	चयन (dc_plane_state->क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		/* DC करोesn't have a transfer function क्रम BT601 specअगरically. */
		tf = TRANSFER_FUNCTION_BT709;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (crtc->cm_has_degamma) अणु
		degamma_lut = __extract_blob_lut(crtc->base.degamma_lut,
						 &degamma_size);
		ASSERT(degamma_size == MAX_COLOR_LUT_ENTRIES);

		dc_plane_state->in_transfer_func->type =
			TF_TYPE_DISTRIBUTED_POINTS;

		/*
		 * This हाल isn't fully correct, but also fairly
		 * uncommon. This is userspace trying to use a
		 * legacy gamma LUT + atomic degamma LUT
		 * at the same समय.
		 *
		 * Legacy gamma requires the input to be in linear
		 * space, so that means we need to apply an sRGB
		 * degamma. But color module also करोesn't support
		 * a user ramp in this हाल so the degamma will
		 * be lost.
		 *
		 * Even अगर we did support it, it's still not right:
		 *
		 * Input -> CRTC DGM -> sRGB DGM -> CRTC CTM ->
		 * sRGB RGM -> CRTC RGM -> Output
		 *
		 * The CSC will be करोne in the wrong space since
		 * we're applying an sRGB DGM on top of the CRTC
		 * DGM.
		 *
		 * TODO: Don't use the legacy gamma पूर्णांकerface and just
		 * map these to the atomic one instead.
		 */
		अगर (crtc->cm_is_degamma_srgb)
			dc_plane_state->in_transfer_func->tf = tf;
		अन्यथा
			dc_plane_state->in_transfer_func->tf =
				TRANSFER_FUNCTION_LINEAR;

		r = __set_input_tf(dc_plane_state->in_transfer_func,
				   degamma_lut, degamma_size);
		अगर (r)
			वापस r;
	पूर्ण अन्यथा अगर (crtc->cm_is_degamma_srgb) अणु
		/*
		 * For legacy gamma support we need the regamma input
		 * in linear space. Assume that the input is sRGB.
		 */
		dc_plane_state->in_transfer_func->type = TF_TYPE_PREDEFINED;
		dc_plane_state->in_transfer_func->tf = tf;

		अगर (tf != TRANSFER_FUNCTION_SRGB &&
		    !mod_color_calculate_degamma_params(शून्य,
			    dc_plane_state->in_transfer_func, शून्य, false))
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		/* ...Otherwise we can just bypass the DGM block. */
		dc_plane_state->in_transfer_func->type = TF_TYPE_BYPASS;
		dc_plane_state->in_transfer_func->tf = TRANSFER_FUNCTION_LINEAR;
	पूर्ण

	वापस 0;
पूर्ण
