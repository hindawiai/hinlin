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

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "dm_services.h"

#समावेश "dce/dce_11_2_d.h"
#समावेश "dce/dce_11_2_sh_mask.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"
#समावेश "gmc/gmc_8_1_d.h"

#समावेश "include/logger_interface.h"

#समावेश "dce112_compressor.h"
#घोषणा DC_LOGGER \
		cp110->base.ctx->logger
#घोषणा DCP_REG(reg)\
	(reg + cp110->offsets.dcp_offset)
#घोषणा DMIF_REG(reg)\
	(reg + cp110->offsets.dmअगर_offset)

अटल स्थिर काष्ठा dce112_compressor_reg_offsets reg_offsets[] = अणु
अणु
	.dcp_offset = (mmDCP0_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
	.dmअगर_offset =
		(mmDMIF_PG0_DPG_PIPE_DPM_CONTROL
			- mmDMIF_PG0_DPG_PIPE_DPM_CONTROL),
पूर्ण,
अणु
	.dcp_offset = (mmDCP1_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
	.dmअगर_offset =
		(mmDMIF_PG1_DPG_PIPE_DPM_CONTROL
			- mmDMIF_PG0_DPG_PIPE_DPM_CONTROL),
पूर्ण,
अणु
	.dcp_offset = (mmDCP2_GRPH_CONTROL - mmDCP0_GRPH_CONTROL),
	.dmअगर_offset =
		(mmDMIF_PG2_DPG_PIPE_DPM_CONTROL
			- mmDMIF_PG0_DPG_PIPE_DPM_CONTROL),
पूर्ण
पूर्ण;

अटल स्थिर uपूर्णांक32_t dce11_one_lpt_channel_max_resolution = 2560 * 1600;

क्रमागत fbc_idle_क्रमce अणु
	/* Bit 0 - Display रेजिस्टरs updated */
	FBC_IDLE_FORCE_DISPLAY_REGISTER_UPDATE = 0x00000001,

	/* Bit 2 - FBC_GRPH_COMP_EN रेजिस्टर updated */
	FBC_IDLE_FORCE_GRPH_COMP_EN = 0x00000002,
	/* Bit 3 - FBC_SRC_SEL रेजिस्टर updated */
	FBC_IDLE_FORCE_SRC_SEL_CHANGE = 0x00000004,
	/* Bit 4 - FBC_MIN_COMPRESSION रेजिस्टर updated */
	FBC_IDLE_FORCE_MIN_COMPRESSION_CHANGE = 0x00000008,
	/* Bit 5 - FBC_ALPHA_COMP_EN रेजिस्टर updated */
	FBC_IDLE_FORCE_ALPHA_COMP_EN = 0x00000010,
	/* Bit 6 - FBC_ZERO_ALPHA_CHUNK_SKIP_EN रेजिस्टर updated */
	FBC_IDLE_FORCE_ZERO_ALPHA_CHUNK_SKIP_EN = 0x00000020,
	/* Bit 7 - FBC_FORCE_COPY_TO_COMP_BUF रेजिस्टर updated */
	FBC_IDLE_FORCE_FORCE_COPY_TO_COMP_BUF = 0x00000040,

	/* Bit 24 - Memory ग_लिखो to region 0 defined by MC रेजिस्टरs. */
	FBC_IDLE_FORCE_MEMORY_WRITE_TO_REGION0 = 0x01000000,
	/* Bit 25 - Memory ग_लिखो to region 1 defined by MC रेजिस्टरs */
	FBC_IDLE_FORCE_MEMORY_WRITE_TO_REGION1 = 0x02000000,
	/* Bit 26 - Memory ग_लिखो to region 2 defined by MC रेजिस्टरs */
	FBC_IDLE_FORCE_MEMORY_WRITE_TO_REGION2 = 0x04000000,
	/* Bit 27 - Memory ग_लिखो to region 3 defined by MC रेजिस्टरs. */
	FBC_IDLE_FORCE_MEMORY_WRITE_TO_REGION3 = 0x08000000,

	/* Bit 28 - Memory ग_लिखो from any client other than MCIF */
	FBC_IDLE_FORCE_MEMORY_WRITE_OTHER_THAN_MCIF = 0x10000000,
	/* Bit 29 - CG अटलs screen संकेत is inactive */
	FBC_IDLE_FORCE_CG_STATIC_SCREEN_IS_INACTIVE = 0x20000000,
पूर्ण;

अटल uपूर्णांक32_t lpt_size_alignment(काष्ठा dce112_compressor *cp110)
अणु
	/*LPT_ALIGNMENT (in bytes) = ROW_SIZE * #BANKS * # DRAM CHANNELS. */
	वापस cp110->base.raw_size * cp110->base.banks_num *
		cp110->base.dram_channels_num;
पूर्ण

अटल uपूर्णांक32_t lpt_memory_control_config(काष्ठा dce112_compressor *cp110,
	uपूर्णांक32_t lpt_control)
अणु
	/*LPT MC Config */
	अगर (cp110->base.options.bits.LPT_MC_CONFIG == 1) अणु
		/* POSSIBLE VALUES क्रम LPT NUM_PIPES (DRAM CHANNELS):
		 * 00 - 1 CHANNEL
		 * 01 - 2 CHANNELS
		 * 02 - 4 OR 6 CHANNELS
		 * (Only क्रम discrete GPU, N/A क्रम CZ)
		 * 03 - 8 OR 12 CHANNELS
		 * (Only क्रम discrete GPU, N/A क्रम CZ) */
		चयन (cp110->base.dram_channels_num) अणु
		हाल 2:
			set_reg_field_value(
				lpt_control,
				1,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_NUM_PIPES);
			अवरोध;
		हाल 1:
			set_reg_field_value(
				lpt_control,
				0,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_NUM_PIPES);
			अवरोध;
		शेष:
			DC_LOG_WARNING(
				"%s: Invalid LPT NUM_PIPES!!!",
				__func__);
			अवरोध;
		पूर्ण

		/* The mapping क्रम LPT NUM_BANKS is in
		 * GRPH_CONTROL.GRPH_NUM_BANKS रेजिस्टर field
		 * Specअगरies the number of memory banks क्रम tiling
		 * purposes. Only applies to 2D and 3D tiling modes.
		 * POSSIBLE VALUES:
		 * 00 - DCP_GRPH_NUM_BANKS_2BANK: ADDR_SURF_2_BANK
		 * 01 - DCP_GRPH_NUM_BANKS_4BANK: ADDR_SURF_4_BANK
		 * 02 - DCP_GRPH_NUM_BANKS_8BANK: ADDR_SURF_8_BANK
		 * 03 - DCP_GRPH_NUM_BANKS_16BANK: ADDR_SURF_16_BANK */
		चयन (cp110->base.banks_num) अणु
		हाल 16:
			set_reg_field_value(
				lpt_control,
				3,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_NUM_BANKS);
			अवरोध;
		हाल 8:
			set_reg_field_value(
				lpt_control,
				2,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_NUM_BANKS);
			अवरोध;
		हाल 4:
			set_reg_field_value(
				lpt_control,
				1,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_NUM_BANKS);
			अवरोध;
		हाल 2:
			set_reg_field_value(
				lpt_control,
				0,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_NUM_BANKS);
			अवरोध;
		शेष:
			DC_LOG_WARNING(
				"%s: Invalid LPT NUM_BANKS!!!",
				__func__);
			अवरोध;
		पूर्ण

		/* The mapping is in DMIF_ADDR_CALC.
		 * ADDR_CONFIG_PIPE_INTERLEAVE_SIZE रेजिस्टर field क्रम
		 * Carrizo specअगरies the memory पूर्णांकerleave per pipe.
		 * It effectively specअगरies the location of pipe bits in
		 * the memory address.
		 * POSSIBLE VALUES:
		 * 00 - ADDR_CONFIG_PIPE_INTERLEAVE_256B: 256 byte
		 * पूर्णांकerleave
		 * 01 - ADDR_CONFIG_PIPE_INTERLEAVE_512B: 512 byte
		 * पूर्णांकerleave
		 */
		चयन (cp110->base.channel_पूर्णांकerleave_size) अणु
		हाल 256: /*256B */
			set_reg_field_value(
				lpt_control,
				0,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_PIPE_INTERLEAVE_SIZE);
			अवरोध;
		हाल 512: /*512B */
			set_reg_field_value(
				lpt_control,
				1,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_PIPE_INTERLEAVE_SIZE);
			अवरोध;
		शेष:
			DC_LOG_WARNING(
				"%s: Invalid LPT INTERLEAVE_SIZE!!!",
				__func__);
			अवरोध;
		पूर्ण

		/* The mapping क्रम LOW_POWER_TILING_ROW_SIZE is in
		 * DMIF_ADDR_CALC.ADDR_CONFIG_ROW_SIZE रेजिस्टर field
		 * क्रम Carrizo. Specअगरies the size of dram row in bytes.
		 * This should match up with NOOFCOLS field in
		 * MC_ARB_RAMCFG (ROW_SIZE = 4 * 2 ^^ columns).
		 * This रेजिस्टर DMIF_ADDR_CALC is not used by the
		 * hardware as it is only used क्रम addrlib निश्चितions.
		 * POSSIBLE VALUES:
		 * 00 - ADDR_CONFIG_1KB_ROW: Treat 1KB as DRAM row
		 * boundary
		 * 01 - ADDR_CONFIG_2KB_ROW: Treat 2KB as DRAM row
		 * boundary
		 * 02 - ADDR_CONFIG_4KB_ROW: Treat 4KB as DRAM row
		 * boundary */
		चयन (cp110->base.raw_size) अणु
		हाल 4096: /*4 KB */
			set_reg_field_value(
				lpt_control,
				2,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_ROW_SIZE);
			अवरोध;
		हाल 2048:
			set_reg_field_value(
				lpt_control,
				1,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_ROW_SIZE);
			अवरोध;
		हाल 1024:
			set_reg_field_value(
				lpt_control,
				0,
				LOW_POWER_TILING_CONTROL,
				LOW_POWER_TILING_ROW_SIZE);
			अवरोध;
		शेष:
			DC_LOG_WARNING(
				"%s: Invalid LPT ROW_SIZE!!!",
				__func__);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		DC_LOG_WARNING(
			"%s: LPT MC Configuration is not provided",
			__func__);
	पूर्ण

	वापस lpt_control;
पूर्ण

अटल bool is_source_bigger_than_epanel_size(
	काष्ठा dce112_compressor *cp110,
	uपूर्णांक32_t source_view_width,
	uपूर्णांक32_t source_view_height)
अणु
	अगर (cp110->base.embedded_panel_h_size != 0 &&
		cp110->base.embedded_panel_v_size != 0 &&
		((source_view_width * source_view_height) >
		(cp110->base.embedded_panel_h_size *
			cp110->base.embedded_panel_v_size)))
		वापस true;

	वापस false;
पूर्ण

अटल uपूर्णांक32_t align_to_chunks_number_per_line(
	काष्ठा dce112_compressor *cp110,
	uपूर्णांक32_t pixels)
अणु
	वापस 256 * ((pixels + 255) / 256);
पूर्ण

अटल व्योम रुको_क्रम_fbc_state_changed(
	काष्ठा dce112_compressor *cp110,
	bool enabled)
अणु
	uपूर्णांक8_t counter = 0;
	uपूर्णांक32_t addr = mmFBC_STATUS;
	uपूर्णांक32_t value;

	जबतक (counter < 10) अणु
		value = dm_पढ़ो_reg(cp110->base.ctx, addr);
		अगर (get_reg_field_value(
			value,
			FBC_STATUS,
			FBC_ENABLE_STATUS) == enabled)
			अवरोध;
		udelay(10);
		counter++;
	पूर्ण

	अगर (counter == 10) अणु
		DC_LOG_WARNING(
			"%s: wait counter exceeded, changes to HW not applied",
			__func__);
	पूर्ण
पूर्ण

व्योम dce112_compressor_घातer_up_fbc(काष्ठा compressor *compressor)
अणु
	uपूर्णांक32_t value;
	uपूर्णांक32_t addr;

	addr = mmFBC_CNTL;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(value, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
	set_reg_field_value(value, 1, FBC_CNTL, FBC_EN);
	set_reg_field_value(value, 2, FBC_CNTL, FBC_COHERENCY_MODE);
	अगर (compressor->options.bits.CLK_GATING_DISABLED == 1) अणु
		/* HW needs to करो घातer measurement comparison. */
		set_reg_field_value(
			value,
			0,
			FBC_CNTL,
			FBC_COMP_CLK_GATE_EN);
	पूर्ण
	dm_ग_लिखो_reg(compressor->ctx, addr, value);

	addr = mmFBC_COMP_MODE;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(value, 1, FBC_COMP_MODE, FBC_RLE_EN);
	set_reg_field_value(value, 1, FBC_COMP_MODE, FBC_DPCM4_RGB_EN);
	set_reg_field_value(value, 1, FBC_COMP_MODE, FBC_IND_EN);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);

	addr = mmFBC_COMP_CNTL;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(value, 1, FBC_COMP_CNTL, FBC_DEPTH_RGB08_EN);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);
	/*FBC_MIN_COMPRESSION 0 ==> 2:1 */
	/*                    1 ==> 4:1 */
	/*                    2 ==> 8:1 */
	/*                  0xF ==> 1:1 */
	set_reg_field_value(value, 0xF, FBC_COMP_CNTL, FBC_MIN_COMPRESSION);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);
	compressor->min_compress_ratio = FBC_COMPRESS_RATIO_1TO1;

	value = 0;
	dm_ग_लिखो_reg(compressor->ctx, mmFBC_IND_LUT0, value);

	value = 0xFFFFFF;
	dm_ग_लिखो_reg(compressor->ctx, mmFBC_IND_LUT1, value);
पूर्ण

व्योम dce112_compressor_enable_fbc(
	काष्ठा compressor *compressor,
	uपूर्णांक32_t paths_num,
	काष्ठा compr_addr_and_pitch_params *params)
अणु
	काष्ठा dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);

	अगर (compressor->options.bits.FBC_SUPPORT &&
		(compressor->options.bits.DUMMY_BACKEND == 0) &&
		(!dce112_compressor_is_fbc_enabled_in_hw(compressor, शून्य)) &&
		(!is_source_bigger_than_epanel_size(
			cp110,
			params->source_view_width,
			params->source_view_height))) अणु

		uपूर्णांक32_t addr;
		uपूर्णांक32_t value;

		/* Beक्रमe enabling FBC first need to enable LPT अगर applicable
		 * LPT state should always be changed (enable/disable) जबतक FBC
		 * is disabled */
		अगर (compressor->options.bits.LPT_SUPPORT && (paths_num < 2) &&
			(params->source_view_width *
				params->source_view_height <=
				dce11_one_lpt_channel_max_resolution)) अणु
			dce112_compressor_enable_lpt(compressor);
		पूर्ण

		addr = mmFBC_CNTL;
		value = dm_पढ़ो_reg(compressor->ctx, addr);
		set_reg_field_value(value, 1, FBC_CNTL, FBC_GRPH_COMP_EN);
		set_reg_field_value(
			value,
			params->inst,
			FBC_CNTL, FBC_SRC_SEL);
		dm_ग_लिखो_reg(compressor->ctx, addr, value);

		/* Keep track of क्रमागत controller_id FBC is attached to */
		compressor->is_enabled = true;
		compressor->attached_inst = params->inst;
		cp110->offsets = reg_offsets[params->inst];

		/*Toggle it as there is bug in HW */
		set_reg_field_value(value, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
		dm_ग_लिखो_reg(compressor->ctx, addr, value);
		set_reg_field_value(value, 1, FBC_CNTL, FBC_GRPH_COMP_EN);
		dm_ग_लिखो_reg(compressor->ctx, addr, value);

		रुको_क्रम_fbc_state_changed(cp110, true);
	पूर्ण
पूर्ण

व्योम dce112_compressor_disable_fbc(काष्ठा compressor *compressor)
अणु
	काष्ठा dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);

	अगर (compressor->options.bits.FBC_SUPPORT &&
		dce112_compressor_is_fbc_enabled_in_hw(compressor, शून्य)) अणु
		uपूर्णांक32_t reg_data;
		/* Turn off compression */
		reg_data = dm_पढ़ो_reg(compressor->ctx, mmFBC_CNTL);
		set_reg_field_value(reg_data, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
		dm_ग_लिखो_reg(compressor->ctx, mmFBC_CNTL, reg_data);

		/* Reset क्रमागत controller_id to undefined */
		compressor->attached_inst = 0;
		compressor->is_enabled = false;

		/* Whenever disabling FBC make sure LPT is disabled अगर LPT
		 * supported */
		अगर (compressor->options.bits.LPT_SUPPORT)
			dce112_compressor_disable_lpt(compressor);

		रुको_क्रम_fbc_state_changed(cp110, false);
	पूर्ण
पूर्ण

bool dce112_compressor_is_fbc_enabled_in_hw(
	काष्ठा compressor *compressor,
	uपूर्णांक32_t *inst)
अणु
	/* Check the hardware रेजिस्टर */
	uपूर्णांक32_t value;

	value = dm_पढ़ो_reg(compressor->ctx, mmFBC_STATUS);
	अगर (get_reg_field_value(value, FBC_STATUS, FBC_ENABLE_STATUS)) अणु
		अगर (inst != शून्य)
			*inst = compressor->attached_inst;
		वापस true;
	पूर्ण

	value = dm_पढ़ो_reg(compressor->ctx, mmFBC_MISC);
	अगर (get_reg_field_value(value, FBC_MISC, FBC_STOP_ON_HFLIP_EVENT)) अणु
		value = dm_पढ़ो_reg(compressor->ctx, mmFBC_CNTL);

		अगर (get_reg_field_value(value, FBC_CNTL, FBC_GRPH_COMP_EN)) अणु
			अगर (inst != शून्य)
				*inst =
					compressor->attached_inst;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

bool dce112_compressor_is_lpt_enabled_in_hw(काष्ठा compressor *compressor)
अणु
	/* Check the hardware रेजिस्टर */
	uपूर्णांक32_t value = dm_पढ़ो_reg(compressor->ctx,
		mmLOW_POWER_TILING_CONTROL);

	वापस get_reg_field_value(
		value,
		LOW_POWER_TILING_CONTROL,
		LOW_POWER_TILING_ENABLE);
पूर्ण

व्योम dce112_compressor_program_compressed_surface_address_and_pitch(
	काष्ठा compressor *compressor,
	काष्ठा compr_addr_and_pitch_params *params)
अणु
	काष्ठा dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t fbc_pitch = 0;
	uपूर्णांक32_t compressed_surf_address_low_part =
		compressor->compr_surface_address.addr.low_part;

	/* Clear content first. */
	dm_ग_लिखो_reg(
		compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS_HIGH),
		0);
	dm_ग_लिखो_reg(compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS), 0);

	अगर (compressor->options.bits.LPT_SUPPORT) अणु
		uपूर्णांक32_t lpt_alignment = lpt_size_alignment(cp110);

		अगर (lpt_alignment != 0) अणु
			compressed_surf_address_low_part =
				((compressed_surf_address_low_part
					+ (lpt_alignment - 1)) / lpt_alignment)
					* lpt_alignment;
		पूर्ण
	पूर्ण

	/* Write address, HIGH has to be first. */
	dm_ग_लिखो_reg(compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS_HIGH),
		compressor->compr_surface_address.addr.high_part);
	dm_ग_लिखो_reg(compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS),
		compressed_surf_address_low_part);

	fbc_pitch = align_to_chunks_number_per_line(
		cp110,
		params->source_view_width);

	अगर (compressor->min_compress_ratio == FBC_COMPRESS_RATIO_1TO1)
		fbc_pitch = fbc_pitch / 8;
	अन्यथा
		DC_LOG_WARNING(
			"%s: Unexpected DCE11 compression ratio",
			__func__);

	/* Clear content first. */
	dm_ग_लिखो_reg(compressor->ctx, DCP_REG(mmGRPH_COMPRESS_PITCH), 0);

	/* Write FBC Pitch. */
	set_reg_field_value(
		value,
		fbc_pitch,
		GRPH_COMPRESS_PITCH,
		GRPH_COMPRESS_PITCH);
	dm_ग_लिखो_reg(compressor->ctx, DCP_REG(mmGRPH_COMPRESS_PITCH), value);

पूर्ण

व्योम dce112_compressor_disable_lpt(काष्ठा compressor *compressor)
अणु
	काष्ठा dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);
	uपूर्णांक32_t value;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t inx;

	/* Disable all pipes LPT Stutter */
	क्रम (inx = 0; inx < 3; inx++) अणु
		value =
			dm_पढ़ो_reg(
				compressor->ctx,
				DMIF_REG(mmDPG_PIPE_STUTTER_CONTROL_NONLPTCH));
		set_reg_field_value(
			value,
			0,
			DPG_PIPE_STUTTER_CONTROL_NONLPTCH,
			STUTTER_ENABLE_NONLPTCH);
		dm_ग_लिखो_reg(
			compressor->ctx,
			DMIF_REG(mmDPG_PIPE_STUTTER_CONTROL_NONLPTCH),
			value);
	पूर्ण
	/* Disable Underlay pipe LPT Stutter */
	addr = mmDPGV0_PIPE_STUTTER_CONTROL_NONLPTCH;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		0,
		DPGV0_PIPE_STUTTER_CONTROL_NONLPTCH,
		STUTTER_ENABLE_NONLPTCH);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);

	/* Disable LPT */
	addr = mmLOW_POWER_TILING_CONTROL;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		0,
		LOW_POWER_TILING_CONTROL,
		LOW_POWER_TILING_ENABLE);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);

	/* Clear selection of Channel(s) containing Compressed Surface */
	addr = mmGMCON_LPT_TARGET;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		0xFFFFFFFF,
		GMCON_LPT_TARGET,
		STCTRL_LPT_TARGET);
	dm_ग_लिखो_reg(compressor->ctx, mmGMCON_LPT_TARGET, value);
पूर्ण

व्योम dce112_compressor_enable_lpt(काष्ठा compressor *compressor)
अणु
	काष्ठा dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);
	uपूर्णांक32_t value;
	uपूर्णांक32_t addr;
	uपूर्णांक32_t value_control;
	uपूर्णांक32_t channels;

	/* Enable LPT Stutter from Display pipe */
	value = dm_पढ़ो_reg(compressor->ctx,
		DMIF_REG(mmDPG_PIPE_STUTTER_CONTROL_NONLPTCH));
	set_reg_field_value(
		value,
		1,
		DPG_PIPE_STUTTER_CONTROL_NONLPTCH,
		STUTTER_ENABLE_NONLPTCH);
	dm_ग_लिखो_reg(compressor->ctx,
		DMIF_REG(mmDPG_PIPE_STUTTER_CONTROL_NONLPTCH), value);

	/* Enable Underlay pipe LPT Stutter */
	addr = mmDPGV0_PIPE_STUTTER_CONTROL_NONLPTCH;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		1,
		DPGV0_PIPE_STUTTER_CONTROL_NONLPTCH,
		STUTTER_ENABLE_NONLPTCH);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);

	/* Selection of Channel(s) containing Compressed Surface: 0xfffffff
	 * will disable LPT.
	 * STCTRL_LPT_TARGETn corresponds to channel n. */
	addr = mmLOW_POWER_TILING_CONTROL;
	value_control = dm_पढ़ो_reg(compressor->ctx, addr);
	channels = get_reg_field_value(value_control,
			LOW_POWER_TILING_CONTROL,
			LOW_POWER_TILING_MODE);

	addr = mmGMCON_LPT_TARGET;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		channels + 1, /* not mentioned in programming guide,
				but follow DCE8.1 */
		GMCON_LPT_TARGET,
		STCTRL_LPT_TARGET);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);

	/* Enable LPT */
	addr = mmLOW_POWER_TILING_CONTROL;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		1,
		LOW_POWER_TILING_CONTROL,
		LOW_POWER_TILING_ENABLE);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);
पूर्ण

व्योम dce112_compressor_program_lpt_control(
	काष्ठा compressor *compressor,
	काष्ठा compr_addr_and_pitch_params *params)
अणु
	काष्ठा dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);
	uपूर्णांक32_t rows_per_channel;
	uपूर्णांक32_t lpt_alignment;
	uपूर्णांक32_t source_view_width;
	uपूर्णांक32_t source_view_height;
	uपूर्णांक32_t lpt_control = 0;

	अगर (!compressor->options.bits.LPT_SUPPORT)
		वापस;

	lpt_control = dm_पढ़ो_reg(compressor->ctx,
		mmLOW_POWER_TILING_CONTROL);

	/* POSSIBLE VALUES क्रम Low Power Tiling Mode:
	 * 00 - Use channel 0
	 * 01 - Use Channel 0 and 1
	 * 02 - Use Channel 0,1,2,3
	 * 03 - reserved */
	चयन (compressor->lpt_channels_num) अणु
	/* हाल 2:
	 * Use Channel 0 & 1 / Not used क्रम DCE 11 */
	हाल 1:
		/*Use Channel 0 क्रम LPT क्रम DCE 11 */
		set_reg_field_value(
			lpt_control,
			0,
			LOW_POWER_TILING_CONTROL,
			LOW_POWER_TILING_MODE);
		अवरोध;
	शेष:
		DC_LOG_WARNING(
			"%s: Invalid selected DRAM channels for LPT!!!",
			__func__);
		अवरोध;
	पूर्ण

	lpt_control = lpt_memory_control_config(cp110, lpt_control);

	/* Program LOW_POWER_TILING_ROWS_PER_CHAN field which depends on
	 * FBC compressed surface pitch.
	 * LOW_POWER_TILING_ROWS_PER_CHAN = Roundup ((Surface Height *
	 * Surface Pitch) / (Row Size * Number of Channels *
	 * Number of Banks)). */
	rows_per_channel = 0;
	lpt_alignment = lpt_size_alignment(cp110);
	source_view_width =
		align_to_chunks_number_per_line(
			cp110,
			params->source_view_width);
	source_view_height = (params->source_view_height + 1) & (~0x1);

	अगर (lpt_alignment != 0) अणु
		rows_per_channel = source_view_width * source_view_height * 4;
		rows_per_channel =
			(rows_per_channel % lpt_alignment) ?
				(rows_per_channel / lpt_alignment + 1) :
				rows_per_channel / lpt_alignment;
	पूर्ण

	set_reg_field_value(
		lpt_control,
		rows_per_channel,
		LOW_POWER_TILING_CONTROL,
		LOW_POWER_TILING_ROWS_PER_CHAN);

	dm_ग_लिखो_reg(compressor->ctx,
		mmLOW_POWER_TILING_CONTROL, lpt_control);
पूर्ण

/*
 * DCE 11 Frame Buffer Compression Implementation
 */

व्योम dce112_compressor_set_fbc_invalidation_triggers(
	काष्ठा compressor *compressor,
	uपूर्णांक32_t fbc_trigger)
अणु
	/* Disable region hit event, FBC_MEMORY_REGION_MASK = 0 (bits 16-19)
	 * क्रम DCE 11 regions cannot be used - करोes not work with S/G
	 */
	uपूर्णांक32_t addr = mmFBC_CLIENT_REGION_MASK;
	uपूर्णांक32_t value = dm_पढ़ो_reg(compressor->ctx, addr);

	set_reg_field_value(
		value,
		0,
		FBC_CLIENT_REGION_MASK,
		FBC_MEMORY_REGION_MASK);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);

	/* Setup events when to clear all CSM entries (effectively marking
	 * current compressed data invalid)
	 * For DCE 11 CSM metadata 11111 means - "Not Compressed"
	 * Used as the initial value of the metadata sent to the compressor
	 * after invalidation, to indicate that the compressor should attempt
	 * to compress all chunks on the current pass.  Also used when the chunk
	 * is not successfully written to memory.
	 * When this CSM value is detected, FBC पढ़ोs from the uncompressed
	 * buffer. Set events according to passed in value, these events are
	 * valid क्रम DCE11:
	 *     - bit  0 - display रेजिस्टर updated
	 *     - bit 28 - memory ग_लिखो from any client except from MCIF
	 *     - bit 29 - CG अटल screen संकेत is inactive
	 * In addition, DCE11.1 also needs to set new DCE11.1 specअगरic events
	 * that are used to trigger invalidation on certain रेजिस्टर changes,
	 * क्रम example enabling of Alpha Compression may trigger invalidation of
	 * FBC once bit is set. These events are as follows:
	 *      - Bit 2 - FBC_GRPH_COMP_EN रेजिस्टर updated
	 *      - Bit 3 - FBC_SRC_SEL रेजिस्टर updated
	 *      - Bit 4 - FBC_MIN_COMPRESSION रेजिस्टर updated
	 *      - Bit 5 - FBC_ALPHA_COMP_EN रेजिस्टर updated
	 *      - Bit 6 - FBC_ZERO_ALPHA_CHUNK_SKIP_EN रेजिस्टर updated
	 *      - Bit 7 - FBC_FORCE_COPY_TO_COMP_BUF रेजिस्टर updated
	 */
	addr = mmFBC_IDLE_FORCE_CLEAR_MASK;
	value = dm_पढ़ो_reg(compressor->ctx, addr);
	set_reg_field_value(
		value,
		fbc_trigger |
		FBC_IDLE_FORCE_GRPH_COMP_EN |
		FBC_IDLE_FORCE_SRC_SEL_CHANGE |
		FBC_IDLE_FORCE_MIN_COMPRESSION_CHANGE |
		FBC_IDLE_FORCE_ALPHA_COMP_EN |
		FBC_IDLE_FORCE_ZERO_ALPHA_CHUNK_SKIP_EN |
		FBC_IDLE_FORCE_FORCE_COPY_TO_COMP_BUF,
		FBC_IDLE_FORCE_CLEAR_MASK,
		FBC_IDLE_FORCE_CLEAR_MASK);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);
पूर्ण

व्योम dce112_compressor_स्थिरruct(काष्ठा dce112_compressor *compressor,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dc_bios *bp = ctx->dc_bios;
	काष्ठा embedded_panel_info panel_info;

	compressor->base.options.raw = 0;
	compressor->base.options.bits.FBC_SUPPORT = true;
	compressor->base.options.bits.LPT_SUPPORT = true;
	 /* For DCE 11 always use one DRAM channel क्रम LPT */
	compressor->base.lpt_channels_num = 1;
	compressor->base.options.bits.DUMMY_BACKEND = false;

	/* Check अगर this प्रणाली has more than 1 DRAM channel; अगर only 1 then LPT
	 * should not be supported */
	अगर (compressor->base.memory_bus_width == 64)
		compressor->base.options.bits.LPT_SUPPORT = false;

	compressor->base.options.bits.CLK_GATING_DISABLED = false;

	compressor->base.ctx = ctx;
	compressor->base.embedded_panel_h_size = 0;
	compressor->base.embedded_panel_v_size = 0;
	compressor->base.memory_bus_width = ctx->asic_id.vram_width;
	compressor->base.allocated_size = 0;
	compressor->base.preferred_requested_size = 0;
	compressor->base.min_compress_ratio = FBC_COMPRESS_RATIO_INVALID;
	compressor->base.banks_num = 0;
	compressor->base.raw_size = 0;
	compressor->base.channel_पूर्णांकerleave_size = 0;
	compressor->base.dram_channels_num = 0;
	compressor->base.lpt_channels_num = 0;
	compressor->base.attached_inst = 0;
	compressor->base.is_enabled = false;

	अगर (BP_RESULT_OK ==
			bp->funcs->get_embedded_panel_info(bp, &panel_info)) अणु
		compressor->base.embedded_panel_h_size =
			panel_info.lcd_timing.horizontal_addressable;
		compressor->base.embedded_panel_v_size =
			panel_info.lcd_timing.vertical_addressable;
	पूर्ण
पूर्ण

काष्ठा compressor *dce112_compressor_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dce112_compressor *cp110 =
		kzalloc(माप(काष्ठा dce112_compressor), GFP_KERNEL);

	अगर (!cp110)
		वापस शून्य;

	dce112_compressor_स्थिरruct(cp110, ctx);
	वापस &cp110->base;
पूर्ण

व्योम dce112_compressor_destroy(काष्ठा compressor **compressor)
अणु
	kमुक्त(TO_DCE112_COMPRESSOR(*compressor));
	*compressor = शून्य;
पूर्ण
