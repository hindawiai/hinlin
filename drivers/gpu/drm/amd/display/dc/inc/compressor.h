<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_COMPRESSOR_H__
#घोषणा __DAL_COMPRESSOR_H__

#समावेश "include/grph_object_id.h"
#समावेश "bios_parser_interface.h"

क्रमागत fbc_compress_ratio अणु
	FBC_COMPRESS_RATIO_INVALID = 0,
	FBC_COMPRESS_RATIO_1TO1 = 1,
	FBC_COMPRESS_RATIO_2TO1 = 2,
	FBC_COMPRESS_RATIO_4TO1 = 4,
	FBC_COMPRESS_RATIO_8TO1 = 8,
पूर्ण;

जोड़ fbc_physical_address अणु
	काष्ठा अणु
		uपूर्णांक32_t low_part;
		पूर्णांक32_t high_part;
	पूर्ण addr;
	uपूर्णांक64_t quad_part;
पूर्ण;

काष्ठा compr_addr_and_pitch_params अणु
	/* क्रमागत controller_id controller_id; */
	uपूर्णांक32_t inst;
	uपूर्णांक32_t source_view_width;
	uपूर्णांक32_t source_view_height;
पूर्ण;

क्रमागत fbc_hw_max_resolution_supported अणु
	FBC_MAX_X = 3840,
	FBC_MAX_Y = 2400,
	FBC_MAX_X_SG = 1920,
	FBC_MAX_Y_SG = 1080,
पूर्ण;

काष्ठा compressor;

काष्ठा compressor_funcs अणु

	व्योम (*घातer_up_fbc)(काष्ठा compressor *cp);
	व्योम (*enable_fbc)(काष्ठा compressor *cp,
		काष्ठा compr_addr_and_pitch_params *params);
	व्योम (*disable_fbc)(काष्ठा compressor *cp);
	व्योम (*set_fbc_invalidation_triggers)(काष्ठा compressor *cp,
		uपूर्णांक32_t fbc_trigger);
	व्योम (*surface_address_and_pitch)(
		काष्ठा compressor *cp,
		काष्ठा compr_addr_and_pitch_params *params);
	bool (*is_fbc_enabled_in_hw)(काष्ठा compressor *cp,
		uपूर्णांक32_t *fbc_mapped_crtc_id);
पूर्ण;
काष्ठा compressor अणु
	काष्ठा dc_context *ctx;
	/* CONTROLLER_ID_D0 + instance, CONTROLLER_ID_UNDEFINED = 0 */
	uपूर्णांक32_t attached_inst;
	bool is_enabled;
	स्थिर काष्ठा compressor_funcs *funcs;
	जोड़ अणु
		uपूर्णांक32_t raw;
		काष्ठा अणु
			uपूर्णांक32_t FBC_SUPPORT:1;
			uपूर्णांक32_t FB_POOL:1;
			uपूर्णांक32_t DYNAMIC_ALLOC:1;
			uपूर्णांक32_t LPT_SUPPORT:1;
			uपूर्णांक32_t LPT_MC_CONFIG:1;
			uपूर्णांक32_t DUMMY_BACKEND:1;
			uपूर्णांक32_t CLK_GATING_DISABLED:1;

		पूर्ण bits;
	पूर्ण options;

	जोड़ fbc_physical_address compr_surface_address;

	uपूर्णांक32_t embedded_panel_h_size;
	uपूर्णांक32_t embedded_panel_v_size;
	uपूर्णांक32_t memory_bus_width;
	uपूर्णांक32_t banks_num;
	uपूर्णांक32_t raw_size;
	uपूर्णांक32_t channel_पूर्णांकerleave_size;
	uपूर्णांक32_t dram_channels_num;

	uपूर्णांक32_t allocated_size;
	uपूर्णांक32_t preferred_requested_size;
	uपूर्णांक32_t lpt_channels_num;
	क्रमागत fbc_compress_ratio min_compress_ratio;
पूर्ण;

काष्ठा fbc_input_info अणु
	bool           dynamic_fbc_buffer_alloc;
	अचिन्हित पूर्णांक   source_view_width;
	अचिन्हित पूर्णांक   source_view_height;
	अचिन्हित पूर्णांक   num_of_active_tarमाला_लो;
पूर्ण;


काष्ठा fbc_requested_compressed_size अणु
	अचिन्हित पूर्णांक   preferred_size;
	अचिन्हित पूर्णांक   preferred_size_alignment;
	अचिन्हित पूर्णांक   min_size;
	अचिन्हित पूर्णांक   min_size_alignment;
	जोड़ अणु
		काष्ठा अणु
			/* Above preferedSize must be allocated in FB pool */
			अचिन्हित पूर्णांक preferred_must_be_framebuffer_pool : 1;
			/* Above minSize must be allocated in FB pool */
			अचिन्हित पूर्णांक min_must_be_framebuffer_pool : 1;
		पूर्ण bits;
		अचिन्हित पूर्णांक flags;
	पूर्ण;
पूर्ण;
#पूर्ण_अगर
