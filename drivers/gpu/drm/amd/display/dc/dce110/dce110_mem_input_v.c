<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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
#समावेश "dm_services.h"

#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"
/* TODO: this needs to be looked at, used by Stella's workaround*/
#समावेश "gmc/gmc_8_2_d.h"
#समावेश "gmc/gmc_8_2_sh_mask.h"

#समावेश "include/logger_interface.h"
#समावेश "inc/dce_calcs.h"

#समावेश "dce/dce_mem_input.h"
#समावेश "dce110_mem_input_v.h"

अटल व्योम set_flip_control(
	काष्ठा dce_mem_input *mem_input110,
	bool immediate)
अणु
	uपूर्णांक32_t value = 0;

	value = dm_पढ़ो_reg(
			mem_input110->base.ctx,
			mmUNP_FLIP_CONTROL);

	set_reg_field_value(value, 1,
			UNP_FLIP_CONTROL,
			GRPH_SURFACE_UPDATE_PENDING_MODE);

	dm_ग_लिखो_reg(
			mem_input110->base.ctx,
			mmUNP_FLIP_CONTROL,
			value);
पूर्ण

/* chroma part */
अटल व्योम program_pri_addr_c(
	काष्ठा dce_mem_input *mem_input110,
	PHYSICAL_ADDRESS_LOC address)
अणु
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t temp = 0;
	/*high रेजिस्टर MUST be programmed first*/
	temp = address.high_part &
UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_C__GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_C_MASK;

	set_reg_field_value(value, temp,
		UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_C,
		GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_C);

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_C,
		value);

	temp = 0;
	value = 0;
	temp = address.low_part >>
	UNP_GRPH_PRIMARY_SURFACE_ADDRESS_C__GRPH_PRIMARY_SURFACE_ADDRESS_C__SHIFT;

	set_reg_field_value(value, temp,
		UNP_GRPH_PRIMARY_SURFACE_ADDRESS_C,
		GRPH_PRIMARY_SURFACE_ADDRESS_C);

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_C,
		value);
पूर्ण

/* luma part */
अटल व्योम program_pri_addr_l(
	काष्ठा dce_mem_input *mem_input110,
	PHYSICAL_ADDRESS_LOC address)
अणु
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t temp = 0;

	/*high रेजिस्टर MUST be programmed first*/
	temp = address.high_part &
UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L__GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L_MASK;

	set_reg_field_value(value, temp,
		UNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L,
		GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L);

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH_L,
		value);

	temp = 0;
	value = 0;
	temp = address.low_part >>
	UNP_GRPH_PRIMARY_SURFACE_ADDRESS_L__GRPH_PRIMARY_SURFACE_ADDRESS_L__SHIFT;

	set_reg_field_value(value, temp,
		UNP_GRPH_PRIMARY_SURFACE_ADDRESS_L,
		GRPH_PRIMARY_SURFACE_ADDRESS_L);

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PRIMARY_SURFACE_ADDRESS_L,
		value);
पूर्ण

अटल व्योम program_addr(
	काष्ठा dce_mem_input *mem_input110,
	स्थिर काष्ठा dc_plane_address *addr)
अणु
	चयन (addr->type) अणु
	हाल PLN_ADDR_TYPE_GRAPHICS:
		program_pri_addr_l(
			mem_input110,
			addr->grph.addr);
		अवरोध;
	हाल PLN_ADDR_TYPE_VIDEO_PROGRESSIVE:
		program_pri_addr_c(
			mem_input110,
			addr->video_progressive.chroma_addr);
		program_pri_addr_l(
			mem_input110,
			addr->video_progressive.luma_addr);
		अवरोध;
	शेष:
		/* not supported */
		BREAK_TO_DEBUGGER();
	पूर्ण
पूर्ण

अटल व्योम enable(काष्ठा dce_mem_input *mem_input110)
अणु
	uपूर्णांक32_t value = 0;

	value = dm_पढ़ो_reg(mem_input110->base.ctx, mmUNP_GRPH_ENABLE);
	set_reg_field_value(value, 1, UNP_GRPH_ENABLE, GRPH_ENABLE);
	dm_ग_लिखो_reg(mem_input110->base.ctx,
		mmUNP_GRPH_ENABLE,
		value);
पूर्ण

अटल व्योम program_tiling(
	काष्ठा dce_mem_input *mem_input110,
	स्थिर जोड़ dc_tiling_info *info,
	स्थिर क्रमागत surface_pixel_क्रमmat pixel_क्रमmat)
अणु
	uपूर्णांक32_t value = 0;

	set_reg_field_value(value, info->gfx8.num_banks,
		UNP_GRPH_CONTROL, GRPH_NUM_BANKS);

	set_reg_field_value(value, info->gfx8.bank_width,
		UNP_GRPH_CONTROL, GRPH_BANK_WIDTH_L);

	set_reg_field_value(value, info->gfx8.bank_height,
		UNP_GRPH_CONTROL, GRPH_BANK_HEIGHT_L);

	set_reg_field_value(value, info->gfx8.tile_aspect,
		UNP_GRPH_CONTROL, GRPH_MACRO_TILE_ASPECT_L);

	set_reg_field_value(value, info->gfx8.tile_split,
		UNP_GRPH_CONTROL, GRPH_TILE_SPLIT_L);

	set_reg_field_value(value, info->gfx8.tile_mode,
		UNP_GRPH_CONTROL, GRPH_MICRO_TILE_MODE_L);

	set_reg_field_value(value, info->gfx8.pipe_config,
		UNP_GRPH_CONTROL, GRPH_PIPE_CONFIG);

	set_reg_field_value(value, info->gfx8.array_mode,
		UNP_GRPH_CONTROL, GRPH_ARRAY_MODE);

	set_reg_field_value(value, 1,
		UNP_GRPH_CONTROL, GRPH_COLOR_EXPANSION_MODE);

	set_reg_field_value(value, 0,
		UNP_GRPH_CONTROL, GRPH_Z);

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_CONTROL,
		value);

	value = 0;

	set_reg_field_value(value, info->gfx8.bank_width_c,
		UNP_GRPH_CONTROL_C, GRPH_BANK_WIDTH_C);

	set_reg_field_value(value, info->gfx8.bank_height_c,
		UNP_GRPH_CONTROL_C, GRPH_BANK_HEIGHT_C);

	set_reg_field_value(value, info->gfx8.tile_aspect_c,
		UNP_GRPH_CONTROL_C, GRPH_MACRO_TILE_ASPECT_C);

	set_reg_field_value(value, info->gfx8.tile_split_c,
		UNP_GRPH_CONTROL_C, GRPH_TILE_SPLIT_C);

	set_reg_field_value(value, info->gfx8.tile_mode_c,
		UNP_GRPH_CONTROL_C, GRPH_MICRO_TILE_MODE_C);

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_CONTROL_C,
		value);
पूर्ण

अटल व्योम program_size_and_rotation(
	काष्ठा dce_mem_input *mem_input110,
	क्रमागत dc_rotation_angle rotation,
	स्थिर काष्ठा plane_size *plane_size)
अणु
	uपूर्णांक32_t value = 0;
	काष्ठा plane_size local_size = *plane_size;

	अगर (rotation == ROTATION_ANGLE_90 ||
		rotation == ROTATION_ANGLE_270) अणु

		swap(local_size.surface_size.x,
		     local_size.surface_size.y);
		swap(local_size.surface_size.width,
		     local_size.surface_size.height);
		swap(local_size.chroma_size.x,
		     local_size.chroma_size.y);
		swap(local_size.chroma_size.width,
		     local_size.chroma_size.height);
	पूर्ण

	value = 0;
	set_reg_field_value(value, local_size.surface_pitch,
			UNP_GRPH_PITCH_L, GRPH_PITCH_L);

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PITCH_L,
		value);

	value = 0;
	set_reg_field_value(value, local_size.chroma_pitch,
			UNP_GRPH_PITCH_C, GRPH_PITCH_C);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_PITCH_C,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_X_START_L, GRPH_X_START_L);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_START_L,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_X_START_C, GRPH_X_START_C);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_START_C,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_Y_START_L, GRPH_Y_START_L);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_START_L,
		value);

	value = 0;
	set_reg_field_value(value, 0,
			UNP_GRPH_Y_START_C, GRPH_Y_START_C);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_START_C,
		value);

	value = 0;
	set_reg_field_value(value, local_size.surface_size.x +
			local_size.surface_size.width,
			UNP_GRPH_X_END_L, GRPH_X_END_L);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_END_L,
		value);

	value = 0;
	set_reg_field_value(value, local_size.chroma_size.x +
			local_size.chroma_size.width,
			UNP_GRPH_X_END_C, GRPH_X_END_C);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_X_END_C,
		value);

	value = 0;
	set_reg_field_value(value, local_size.surface_size.y +
			local_size.surface_size.height,
			UNP_GRPH_Y_END_L, GRPH_Y_END_L);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_END_L,
		value);

	value = 0;
	set_reg_field_value(value, local_size.chroma_size.y +
			local_size.chroma_size.height,
			UNP_GRPH_Y_END_C, GRPH_Y_END_C);
	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_GRPH_Y_END_C,
		value);

	value = 0;
	चयन (rotation) अणु
	हाल ROTATION_ANGLE_90:
		set_reg_field_value(value, 3,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		अवरोध;
	हाल ROTATION_ANGLE_180:
		set_reg_field_value(value, 2,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		अवरोध;
	हाल ROTATION_ANGLE_270:
		set_reg_field_value(value, 1,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		अवरोध;
	शेष:
		set_reg_field_value(value, 0,
			UNP_HW_ROTATION, ROTATION_ANGLE);
		अवरोध;
	पूर्ण

	dm_ग_लिखो_reg(
		mem_input110->base.ctx,
		mmUNP_HW_ROTATION,
		value);
पूर्ण

अटल व्योम program_pixel_क्रमmat(
	काष्ठा dce_mem_input *mem_input110,
	क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	अगर (क्रमmat < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) अणु
		uपूर्णांक32_t value;
		uपूर्णांक8_t grph_depth;
		uपूर्णांक8_t grph_क्रमmat;

		value =	dm_पढ़ो_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL);

		चयन (क्रमmat) अणु
		हाल SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
			grph_depth = 0;
			grph_क्रमmat = 0;
			अवरोध;
		हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
			grph_depth = 1;
			grph_क्रमmat = 1;
			अवरोध;
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
			grph_depth = 2;
			grph_क्रमmat = 0;
			अवरोध;
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
			grph_depth = 2;
			grph_क्रमmat = 1;
			अवरोध;
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
			grph_depth = 3;
			grph_क्रमmat = 0;
			अवरोध;
		शेष:
			grph_depth = 2;
			grph_क्रमmat = 0;
			अवरोध;
		पूर्ण

		set_reg_field_value(
				value,
				grph_depth,
				UNP_GRPH_CONTROL,
				GRPH_DEPTH);
		set_reg_field_value(
				value,
				grph_क्रमmat,
				UNP_GRPH_CONTROL,
				GRPH_FORMAT);

		dm_ग_लिखो_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL,
				value);

		value =	dm_पढ़ो_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL_EXP);

		/* VIDEO FORMAT 0 */
		set_reg_field_value(
				value,
				0,
				UNP_GRPH_CONTROL_EXP,
				VIDEO_FORMAT);
		dm_ग_लिखो_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL_EXP,
				value);

	पूर्ण अन्यथा अणु
		/* Video 422 and 420 needs UNP_GRPH_CONTROL_EXP programmed */
		uपूर्णांक32_t value;
		uपूर्णांक8_t video_क्रमmat;

		value =	dm_पढ़ो_reg(
				mem_input110->base.ctx,
				mmUNP_GRPH_CONTROL_EXP);

		चयन (क्रमmat) अणु
		हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
			video_क्रमmat = 2;
			अवरोध;
		हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
			video_क्रमmat = 3;
			अवरोध;
		शेष:
			video_क्रमmat = 0;
			अवरोध;
		पूर्ण

		set_reg_field_value(
			value,
			video_क्रमmat,
			UNP_GRPH_CONTROL_EXP,
			VIDEO_FORMAT);

		dm_ग_लिखो_reg(
			mem_input110->base.ctx,
			mmUNP_GRPH_CONTROL_EXP,
			value);
	पूर्ण
पूर्ण

अटल bool dce_mem_input_v_is_surface_pending(काष्ठा mem_input *mem_input)
अणु
	काष्ठा dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);
	uपूर्णांक32_t value;

	value = dm_पढ़ो_reg(mem_input110->base.ctx, mmUNP_GRPH_UPDATE);

	अगर (get_reg_field_value(value, UNP_GRPH_UPDATE,
			GRPH_SURFACE_UPDATE_PENDING))
		वापस true;

	mem_input->current_address = mem_input->request_address;
	वापस false;
पूर्ण

अटल bool dce_mem_input_v_program_surface_flip_and_addr(
	काष्ठा mem_input *mem_input,
	स्थिर काष्ठा dc_plane_address *address,
	bool flip_immediate)
अणु
	काष्ठा dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);

	set_flip_control(mem_input110, flip_immediate);
	program_addr(mem_input110,
		address);

	mem_input->request_address = *address;

	वापस true;
पूर्ण

/* Scatter Gather param tables */
अटल स्थिर अचिन्हित पूर्णांक dvmm_Hw_Setting_2DTiling[4][9] = अणु
		अणु  8, 64, 64,  8,  8, 1, 4, 0, 0पूर्ण,
		अणु 16, 64, 32,  8, 16, 1, 8, 0, 0पूर्ण,
		अणु 32, 32, 32, 16, 16, 1, 8, 0, 0पूर्ण,
		अणु 64,  8, 32, 16, 16, 1, 8, 0, 0पूर्ण, /* fake */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक dvmm_Hw_Setting_1DTiling[4][9] = अणु
		अणु  8, 512, 8, 1, 0, 1, 0, 0, 0पूर्ण,  /* 0 क्रम invalid */
		अणु 16, 256, 8, 2, 0, 1, 0, 0, 0पूर्ण,
		अणु 32, 128, 8, 4, 0, 1, 0, 0, 0पूर्ण,
		अणु 64,  64, 8, 4, 0, 1, 0, 0, 0पूर्ण, /* fake */
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक dvmm_Hw_Setting_Linear[4][9] = अणु
		अणु  8, 4096, 1, 8, 0, 1, 0, 0, 0पूर्ण,
		अणु 16, 2048, 1, 8, 0, 1, 0, 0, 0पूर्ण,
		अणु 32, 1024, 1, 8, 0, 1, 0, 0, 0पूर्ण,
		अणु 64,  512, 1, 8, 0, 1, 0, 0, 0पूर्ण, /* new क्रम 64bpp from HW */
पूर्ण;

/* Helper to get table entry from surface info */
अटल स्थिर अचिन्हित पूर्णांक *get_dvmm_hw_setting(
		जोड़ dc_tiling_info *tiling_info,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		bool chroma)
अणु
	क्रमागत bits_per_pixel अणु
		bpp_8 = 0,
		bpp_16,
		bpp_32,
		bpp_64
	पूर्ण bpp;

	अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_INVALID)
		bpp = bpp_32;
	अन्यथा अगर (क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		bpp = chroma ? bpp_16 : bpp_8;
	अन्यथा
		bpp = bpp_8;

	चयन (tiling_info->gfx8.array_mode) अणु
	हाल DC_ARRAY_1D_TILED_THIN1:
	हाल DC_ARRAY_1D_TILED_THICK:
	हाल DC_ARRAY_PRT_TILED_THIN1:
		वापस dvmm_Hw_Setting_1DTiling[bpp];
	हाल DC_ARRAY_2D_TILED_THIN1:
	हाल DC_ARRAY_2D_TILED_THICK:
	हाल DC_ARRAY_2D_TILED_X_THICK:
	हाल DC_ARRAY_PRT_2D_TILED_THIN1:
	हाल DC_ARRAY_PRT_2D_TILED_THICK:
		वापस dvmm_Hw_Setting_2DTiling[bpp];
	हाल DC_ARRAY_LINEAR_GENERAL:
	हाल DC_ARRAY_LINEAR_ALLIGNED:
		वापस dvmm_Hw_Setting_Linear[bpp];
	शेष:
		वापस dvmm_Hw_Setting_2DTiling[bpp];
	पूर्ण
पूर्ण

अटल व्योम dce_mem_input_v_program_pte_vm(
		काष्ठा mem_input *mem_input,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		जोड़ dc_tiling_info *tiling_info,
		क्रमागत dc_rotation_angle rotation)
अणु
	काष्ठा dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);
	स्थिर अचिन्हित पूर्णांक *pte = get_dvmm_hw_setting(tiling_info, क्रमmat, false);
	स्थिर अचिन्हित पूर्णांक *pte_chroma = get_dvmm_hw_setting(tiling_info, क्रमmat, true);

	अचिन्हित पूर्णांक page_width = 0;
	अचिन्हित पूर्णांक page_height = 0;
	अचिन्हित पूर्णांक page_width_chroma = 0;
	अचिन्हित पूर्णांक page_height_chroma = 0;
	अचिन्हित पूर्णांक temp_page_width = pte[1];
	अचिन्हित पूर्णांक temp_page_height = pte[2];
	अचिन्हित पूर्णांक min_pte_beक्रमe_flip = 0;
	अचिन्हित पूर्णांक min_pte_beक्रमe_flip_chroma = 0;
	uपूर्णांक32_t value = 0;

	जबतक ((temp_page_width >>= 1) != 0)
		page_width++;
	जबतक ((temp_page_height >>= 1) != 0)
		page_height++;

	temp_page_width = pte_chroma[1];
	temp_page_height = pte_chroma[2];
	जबतक ((temp_page_width >>= 1) != 0)
		page_width_chroma++;
	जबतक ((temp_page_height >>= 1) != 0)
		page_height_chroma++;

	चयन (rotation) अणु
	हाल ROTATION_ANGLE_90:
	हाल ROTATION_ANGLE_270:
		min_pte_beक्रमe_flip = pte[4];
		min_pte_beक्रमe_flip_chroma = pte_chroma[4];
		अवरोध;
	शेष:
		min_pte_beक्रमe_flip = pte[3];
		min_pte_beक्रमe_flip_chroma = pte_chroma[3];
		अवरोध;
	पूर्ण

	value = dm_पढ़ो_reg(mem_input110->base.ctx, mmUNP_PIPE_OUTSTANDING_REQUEST_LIMIT);
	/* TODO: un-hardcode requestlimit */
	set_reg_field_value(value, 0xff, UNP_PIPE_OUTSTANDING_REQUEST_LIMIT, UNP_PIPE_OUTSTANDING_REQUEST_LIMIT_L);
	set_reg_field_value(value, 0xff, UNP_PIPE_OUTSTANDING_REQUEST_LIMIT, UNP_PIPE_OUTSTANDING_REQUEST_LIMIT_C);
	dm_ग_लिखो_reg(mem_input110->base.ctx, mmUNP_PIPE_OUTSTANDING_REQUEST_LIMIT, value);

	value = dm_पढ़ो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTROL);
	set_reg_field_value(value, page_width, UNP_DVMM_PTE_CONTROL, DVMM_PAGE_WIDTH);
	set_reg_field_value(value, page_height, UNP_DVMM_PTE_CONTROL, DVMM_PAGE_HEIGHT);
	set_reg_field_value(value, min_pte_beक्रमe_flip, UNP_DVMM_PTE_CONTROL, DVMM_MIN_PTE_BEFORE_FLIP);
	dm_ग_लिखो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTROL, value);

	value = dm_पढ़ो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_ARB_CONTROL);
	set_reg_field_value(value, pte[5], UNP_DVMM_PTE_ARB_CONTROL, DVMM_PTE_REQ_PER_CHUNK);
	set_reg_field_value(value, 0xff, UNP_DVMM_PTE_ARB_CONTROL, DVMM_MAX_PTE_REQ_OUTSTANDING);
	dm_ग_लिखो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_ARB_CONTROL, value);

	value = dm_पढ़ो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTROL_C);
	set_reg_field_value(value, page_width_chroma, UNP_DVMM_PTE_CONTROL_C, DVMM_PAGE_WIDTH_C);
	set_reg_field_value(value, page_height_chroma, UNP_DVMM_PTE_CONTROL_C, DVMM_PAGE_HEIGHT_C);
	set_reg_field_value(value, min_pte_beक्रमe_flip_chroma, UNP_DVMM_PTE_CONTROL_C, DVMM_MIN_PTE_BEFORE_FLIP_C);
	dm_ग_लिखो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_CONTROL_C, value);

	value = dm_पढ़ो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_ARB_CONTROL_C);
	set_reg_field_value(value, pte_chroma[5], UNP_DVMM_PTE_ARB_CONTROL_C, DVMM_PTE_REQ_PER_CHUNK_C);
	set_reg_field_value(value, 0xff, UNP_DVMM_PTE_ARB_CONTROL_C, DVMM_MAX_PTE_REQ_OUTSTANDING_C);
	dm_ग_लिखो_reg(mem_input110->base.ctx, mmUNP_DVMM_PTE_ARB_CONTROL_C, value);
पूर्ण

अटल व्योम dce_mem_input_v_program_surface_config(
	काष्ठा mem_input *mem_input,
	क्रमागत surface_pixel_क्रमmat क्रमmat,
	जोड़ dc_tiling_info *tiling_info,
	काष्ठा plane_size *plane_size,
	क्रमागत dc_rotation_angle rotation,
	काष्ठा dc_plane_dcc_param *dcc,
	bool horizotal_mirror)
अणु
	काष्ठा dce_mem_input *mem_input110 = TO_DCE_MEM_INPUT(mem_input);

	enable(mem_input110);
	program_tiling(mem_input110, tiling_info, क्रमmat);
	program_size_and_rotation(mem_input110, rotation, plane_size);
	program_pixel_क्रमmat(mem_input110, क्रमmat);
पूर्ण

अटल व्योम program_urgency_watermark(
	स्थिर काष्ठा dc_context *ctx,
	स्थिर uपूर्णांक32_t urgency_addr,
	स्थिर uपूर्णांक32_t wm_addr,
	काष्ठा dce_watermarks marks_low,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	/* रेजिस्टर value */
	uपूर्णांक32_t urgency_cntl = 0;
	uपूर्णांक32_t wm_mask_cntl = 0;

	/*Write mask to enable पढ़ोing/writing of watermark set A*/
	wm_mask_cntl = dm_पढ़ो_reg(ctx, wm_addr);
	set_reg_field_value(wm_mask_cntl,
			1,
			DPGV0_WATERMARK_MASK_CONTROL,
			URGENCY_WATERMARK_MASK);
	dm_ग_लिखो_reg(ctx, wm_addr, wm_mask_cntl);

	urgency_cntl = dm_पढ़ो_reg(ctx, urgency_addr);

	set_reg_field_value(
		urgency_cntl,
		marks_low.a_mark,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_LOW_WATERMARK);

	set_reg_field_value(
		urgency_cntl,
		total_dest_line_समय_ns,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_HIGH_WATERMARK);
	dm_ग_लिखो_reg(ctx, urgency_addr, urgency_cntl);

	/*Write mask to enable पढ़ोing/writing of watermark set B*/
	wm_mask_cntl = dm_पढ़ो_reg(ctx, wm_addr);
	set_reg_field_value(wm_mask_cntl,
			2,
			DPGV0_WATERMARK_MASK_CONTROL,
			URGENCY_WATERMARK_MASK);
	dm_ग_लिखो_reg(ctx, wm_addr, wm_mask_cntl);

	urgency_cntl = dm_पढ़ो_reg(ctx, urgency_addr);

	set_reg_field_value(urgency_cntl,
		marks_low.b_mark,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_LOW_WATERMARK);

	set_reg_field_value(urgency_cntl,
		total_dest_line_समय_ns,
		DPGV0_PIPE_URGENCY_CONTROL,
		URGENCY_HIGH_WATERMARK);

	dm_ग_लिखो_reg(ctx, urgency_addr, urgency_cntl);
पूर्ण

अटल व्योम program_urgency_watermark_l(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dce_watermarks marks_low,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	program_urgency_watermark(
		ctx,
		mmDPGV0_PIPE_URGENCY_CONTROL,
		mmDPGV0_WATERMARK_MASK_CONTROL,
		marks_low,
		total_dest_line_समय_ns);
पूर्ण

अटल व्योम program_urgency_watermark_c(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dce_watermarks marks_low,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	program_urgency_watermark(
		ctx,
		mmDPGV1_PIPE_URGENCY_CONTROL,
		mmDPGV1_WATERMARK_MASK_CONTROL,
		marks_low,
		total_dest_line_समय_ns);
पूर्ण

अटल व्योम program_stutter_watermark(
	स्थिर काष्ठा dc_context *ctx,
	स्थिर uपूर्णांक32_t stutter_addr,
	स्थिर uपूर्णांक32_t wm_addr,
	काष्ठा dce_watermarks marks)
अणु
	/* रेजिस्टर value */
	uपूर्णांक32_t stutter_cntl = 0;
	uपूर्णांक32_t wm_mask_cntl = 0;

	/*Write mask to enable पढ़ोing/writing of watermark set A*/

	wm_mask_cntl = dm_पढ़ो_reg(ctx, wm_addr);
	set_reg_field_value(wm_mask_cntl,
		1,
		DPGV0_WATERMARK_MASK_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK);
	dm_ग_लिखो_reg(ctx, wm_addr, wm_mask_cntl);

	stutter_cntl = dm_पढ़ो_reg(ctx, stutter_addr);

	अगर (ctx->dc->debug.disable_stutter) अणु
		set_reg_field_value(stutter_cntl,
			0,
			DPGV0_PIPE_STUTTER_CONTROL,
			STUTTER_ENABLE);
	पूर्ण अन्यथा अणु
		set_reg_field_value(stutter_cntl,
			1,
			DPGV0_PIPE_STUTTER_CONTROL,
			STUTTER_ENABLE);
	पूर्ण

	set_reg_field_value(stutter_cntl,
		1,
		DPGV0_PIPE_STUTTER_CONTROL,
		STUTTER_IGNORE_FBC);

	/*Write watermark set A*/
	set_reg_field_value(stutter_cntl,
		marks.a_mark,
		DPGV0_PIPE_STUTTER_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK);
	dm_ग_लिखो_reg(ctx, stutter_addr, stutter_cntl);

	/*Write mask to enable पढ़ोing/writing of watermark set B*/
	wm_mask_cntl = dm_पढ़ो_reg(ctx, wm_addr);
	set_reg_field_value(wm_mask_cntl,
		2,
		DPGV0_WATERMARK_MASK_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK_MASK);
	dm_ग_लिखो_reg(ctx, wm_addr, wm_mask_cntl);

	stutter_cntl = dm_पढ़ो_reg(ctx, stutter_addr);
	/*Write watermark set B*/
	set_reg_field_value(stutter_cntl,
		marks.b_mark,
		DPGV0_PIPE_STUTTER_CONTROL,
		STUTTER_EXIT_SELF_REFRESH_WATERMARK);
	dm_ग_लिखो_reg(ctx, stutter_addr, stutter_cntl);
पूर्ण

अटल व्योम program_stutter_watermark_l(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dce_watermarks marks)
अणु
	program_stutter_watermark(ctx,
			mmDPGV0_PIPE_STUTTER_CONTROL,
			mmDPGV0_WATERMARK_MASK_CONTROL,
			marks);
पूर्ण

अटल व्योम program_stutter_watermark_c(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dce_watermarks marks)
अणु
	program_stutter_watermark(ctx,
			mmDPGV1_PIPE_STUTTER_CONTROL,
			mmDPGV1_WATERMARK_MASK_CONTROL,
			marks);
पूर्ण

अटल व्योम program_nbp_watermark(
	स्थिर काष्ठा dc_context *ctx,
	स्थिर uपूर्णांक32_t wm_mask_ctrl_addr,
	स्थिर uपूर्णांक32_t nbp_pstate_ctrl_addr,
	काष्ठा dce_watermarks marks)
अणु
	uपूर्णांक32_t value;

	/* Write mask to enable पढ़ोing/writing of watermark set A */

	value = dm_पढ़ो_reg(ctx, wm_mask_ctrl_addr);

	set_reg_field_value(
		value,
		1,
		DPGV0_WATERMARK_MASK_CONTROL,
		NB_PSTATE_CHANGE_WATERMARK_MASK);
	dm_ग_लिखो_reg(ctx, wm_mask_ctrl_addr, value);

	value = dm_पढ़ो_reg(ctx, nbp_pstate_ctrl_addr);

	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_ENABLE);
	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_URGENT_DURING_REQUEST);
	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST);
	dm_ग_लिखो_reg(ctx, nbp_pstate_ctrl_addr, value);

	/* Write watermark set A */
	value = dm_पढ़ो_reg(ctx, nbp_pstate_ctrl_addr);
	set_reg_field_value(
		value,
		marks.a_mark,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_WATERMARK);
	dm_ग_लिखो_reg(ctx, nbp_pstate_ctrl_addr, value);

	/* Write mask to enable पढ़ोing/writing of watermark set B */
	value = dm_पढ़ो_reg(ctx, wm_mask_ctrl_addr);
	set_reg_field_value(
		value,
		2,
		DPGV0_WATERMARK_MASK_CONTROL,
		NB_PSTATE_CHANGE_WATERMARK_MASK);
	dm_ग_लिखो_reg(ctx, wm_mask_ctrl_addr, value);

	value = dm_पढ़ो_reg(ctx, nbp_pstate_ctrl_addr);
	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_ENABLE);
	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_URGENT_DURING_REQUEST);
	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_NOT_SELF_REFRESH_DURING_REQUEST);
	dm_ग_लिखो_reg(ctx, nbp_pstate_ctrl_addr, value);

	/* Write watermark set B */
	value = dm_पढ़ो_reg(ctx, nbp_pstate_ctrl_addr);
	set_reg_field_value(
		value,
		marks.b_mark,
		DPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
		NB_PSTATE_CHANGE_WATERMARK);
	dm_ग_लिखो_reg(ctx, nbp_pstate_ctrl_addr, value);
पूर्ण

अटल व्योम program_nbp_watermark_l(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dce_watermarks marks)
अणु
	program_nbp_watermark(ctx,
			mmDPGV0_WATERMARK_MASK_CONTROL,
			mmDPGV0_PIPE_NB_PSTATE_CHANGE_CONTROL,
			marks);
पूर्ण

अटल व्योम program_nbp_watermark_c(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dce_watermarks marks)
अणु
	program_nbp_watermark(ctx,
			mmDPGV1_WATERMARK_MASK_CONTROL,
			mmDPGV1_PIPE_NB_PSTATE_CHANGE_CONTROL,
			marks);
पूर्ण

अटल व्योम dce_mem_input_v_program_display_marks(
	काष्ठा mem_input *mem_input,
	काष्ठा dce_watermarks nbp,
	काष्ठा dce_watermarks stutter,
	काष्ठा dce_watermarks stutter_enter,
	काष्ठा dce_watermarks urgent,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	program_urgency_watermark_l(
		mem_input->ctx,
		urgent,
		total_dest_line_समय_ns);

	program_nbp_watermark_l(
		mem_input->ctx,
		nbp);

	program_stutter_watermark_l(
		mem_input->ctx,
		stutter);

पूर्ण

अटल व्योम dce_mem_input_program_chroma_display_marks(
	काष्ठा mem_input *mem_input,
	काष्ठा dce_watermarks nbp,
	काष्ठा dce_watermarks stutter,
	काष्ठा dce_watermarks urgent,
	uपूर्णांक32_t total_dest_line_समय_ns)
अणु
	program_urgency_watermark_c(
		mem_input->ctx,
		urgent,
		total_dest_line_समय_ns);

	program_nbp_watermark_c(
		mem_input->ctx,
		nbp);

	program_stutter_watermark_c(
		mem_input->ctx,
		stutter);
पूर्ण

अटल व्योम dce110_allocate_mem_input_v(
	काष्ठा mem_input *mi,
	uपूर्णांक32_t h_total,/* क्रम current stream */
	uपूर्णांक32_t v_total,/* क्रम current stream */
	uपूर्णांक32_t pix_clk_khz,/* क्रम current stream */
	uपूर्णांक32_t total_stream_num)
अणु
	uपूर्णांक32_t addr;
	uपूर्णांक32_t value;
	uपूर्णांक32_t pix_dur;
	अगर (pix_clk_khz != 0) अणु
		addr = mmDPGV0_PIPE_ARBITRATION_CONTROL1;
		value = dm_पढ़ो_reg(mi->ctx, addr);
		pix_dur = 1000000000ULL / pix_clk_khz;
		set_reg_field_value(
			value,
			pix_dur,
			DPGV0_PIPE_ARBITRATION_CONTROL1,
			PIXEL_DURATION);
		dm_ग_लिखो_reg(mi->ctx, addr, value);

		addr = mmDPGV1_PIPE_ARBITRATION_CONTROL1;
		value = dm_पढ़ो_reg(mi->ctx, addr);
		pix_dur = 1000000000ULL / pix_clk_khz;
		set_reg_field_value(
			value,
			pix_dur,
			DPGV1_PIPE_ARBITRATION_CONTROL1,
			PIXEL_DURATION);
		dm_ग_लिखो_reg(mi->ctx, addr, value);

		addr = mmDPGV0_PIPE_ARBITRATION_CONTROL2;
		value = 0x4000800;
		dm_ग_लिखो_reg(mi->ctx, addr, value);

		addr = mmDPGV1_PIPE_ARBITRATION_CONTROL2;
		value = 0x4000800;
		dm_ग_लिखो_reg(mi->ctx, addr, value);
	पूर्ण

पूर्ण

अटल व्योम dce110_मुक्त_mem_input_v(
	काष्ठा mem_input *mi,
	uपूर्णांक32_t total_stream_num)
अणु
पूर्ण

अटल स्थिर काष्ठा mem_input_funcs dce110_mem_input_v_funcs = अणु
	.mem_input_program_display_marks =
			dce_mem_input_v_program_display_marks,
	.mem_input_program_chroma_display_marks =
			dce_mem_input_program_chroma_display_marks,
	.allocate_mem_input = dce110_allocate_mem_input_v,
	.मुक्त_mem_input = dce110_मुक्त_mem_input_v,
	.mem_input_program_surface_flip_and_addr =
			dce_mem_input_v_program_surface_flip_and_addr,
	.mem_input_program_pte_vm =
			dce_mem_input_v_program_pte_vm,
	.mem_input_program_surface_config =
			dce_mem_input_v_program_surface_config,
	.mem_input_is_flip_pending =
			dce_mem_input_v_is_surface_pending
पूर्ण;
/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

व्योम dce110_mem_input_v_स्थिरruct(
	काष्ठा dce_mem_input *dce_mi,
	काष्ठा dc_context *ctx)
अणु
	dce_mi->base.funcs = &dce110_mem_input_v_funcs;
	dce_mi->base.ctx = ctx;
पूर्ण

