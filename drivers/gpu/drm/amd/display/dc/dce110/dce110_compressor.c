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

#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"
#समावेश "gmc/gmc_8_2_sh_mask.h"
#समावेश "gmc/gmc_8_2_d.h"

#समावेश "include/logger_interface.h"

#समावेश "dce110_compressor.h"

#घोषणा DC_LOGGER \
		cp110->base.ctx->logger
#घोषणा DCP_REG(reg)\
	(reg + cp110->offsets.dcp_offset)
#घोषणा DMIF_REG(reg)\
	(reg + cp110->offsets.dmअगर_offset)

अटल स्थिर काष्ठा dce110_compressor_reg_offsets reg_offsets[] = अणु
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

अटल uपूर्णांक32_t align_to_chunks_number_per_line(uपूर्णांक32_t pixels)
अणु
	वापस 256 * ((pixels + 255) / 256);
पूर्ण

अटल व्योम reset_lb_on_vblank(काष्ठा compressor *compressor, uपूर्णांक32_t crtc_inst)
अणु
	uपूर्णांक32_t value;
	uपूर्णांक32_t frame_count;
	uपूर्णांक32_t status_pos;
	uपूर्णांक32_t retry = 0;
	काष्ठा dce110_compressor *cp110 = TO_DCE110_COMPRESSOR(compressor);

	cp110->offsets = reg_offsets[crtc_inst];

	status_pos = dm_पढ़ो_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_POSITION));


	/* Only अगर CRTC is enabled and counter is moving we रुको क्रम one frame. */
	अगर (status_pos != dm_पढ़ो_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_POSITION))) अणु
		/* Resetting LB on VBlank */
		value = dm_पढ़ो_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL));
		set_reg_field_value(value, 3, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL);
		set_reg_field_value(value, 1, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL2);
		dm_ग_लिखो_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL), value);

		frame_count = dm_पढ़ो_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_FRAME_COUNT));


		क्रम (retry = 10000; retry > 0; retry--) अणु
			अगर (frame_count != dm_पढ़ो_reg(compressor->ctx, DCP_REG(mmCRTC_STATUS_FRAME_COUNT)))
				अवरोध;
			udelay(10);
		पूर्ण
		अगर (!retry)
			dm_error("Frame count did not increase for 100ms.\n");

		/* Resetting LB on VBlank */
		value = dm_पढ़ो_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL));
		set_reg_field_value(value, 2, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL);
		set_reg_field_value(value, 0, LB_SYNC_RESET_SEL, LB_SYNC_RESET_SEL2);
		dm_ग_लिखो_reg(compressor->ctx, DCP_REG(mmLB_SYNC_RESET_SEL), value);
	पूर्ण
पूर्ण

अटल व्योम रुको_क्रम_fbc_state_changed(
	काष्ठा dce110_compressor *cp110,
	bool enabled)
अणु
	uपूर्णांक32_t counter = 0;
	uपूर्णांक32_t addr = mmFBC_STATUS;
	uपूर्णांक32_t value;

	जबतक (counter < 1000) अणु
		value = dm_पढ़ो_reg(cp110->base.ctx, addr);
		अगर (get_reg_field_value(
			value,
			FBC_STATUS,
			FBC_ENABLE_STATUS) == enabled)
			अवरोध;
		udelay(100);
		counter++;
	पूर्ण

	अगर (counter == 1000) अणु
		DC_LOG_WARNING("%s: wait counter exceeded, changes to HW not applied",
			__func__);
	पूर्ण अन्यथा अणु
		DC_LOG_SYNC("FBC status changed to %d", enabled);
	पूर्ण


पूर्ण

व्योम dce110_compressor_घातer_up_fbc(काष्ठा compressor *compressor)
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

व्योम dce110_compressor_enable_fbc(
	काष्ठा compressor *compressor,
	काष्ठा compr_addr_and_pitch_params *params)
अणु
	काष्ठा dce110_compressor *cp110 = TO_DCE110_COMPRESSOR(compressor);

	अगर (compressor->options.bits.FBC_SUPPORT &&
		(!dce110_compressor_is_fbc_enabled_in_hw(compressor, शून्य))) अणु

		uपूर्णांक32_t addr;
		uपूर्णांक32_t value, misc_value;

		addr = mmFBC_CNTL;
		value = dm_पढ़ो_reg(compressor->ctx, addr);
		set_reg_field_value(value, 1, FBC_CNTL, FBC_GRPH_COMP_EN);
		/* params->inst is valid HW CRTC instance start from 0 */
		set_reg_field_value(
			value,
			params->inst,
			FBC_CNTL, FBC_SRC_SEL);
		dm_ग_लिखो_reg(compressor->ctx, addr, value);

		/* Keep track of क्रमागत controller_id FBC is attached to */
		compressor->is_enabled = true;
		/* attached_inst is SW CRTC instance start from 1
		 * 0 = CONTROLLER_ID_UNDEFINED means not attached crtc
		 */
		compressor->attached_inst = params->inst + CONTROLLER_ID_D0;

		/* Toggle it as there is bug in HW */
		set_reg_field_value(value, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
		dm_ग_लिखो_reg(compressor->ctx, addr, value);

		/* FBC usage with scatter & gather क्रम dce110 */
		misc_value = dm_पढ़ो_reg(compressor->ctx, mmFBC_MISC);

		set_reg_field_value(misc_value, 1,
				FBC_MISC, FBC_INVALIDATE_ON_ERROR);
		set_reg_field_value(misc_value, 1,
				FBC_MISC, FBC_DECOMPRESS_ERROR_CLEAR);
		set_reg_field_value(misc_value, 0x14,
				FBC_MISC, FBC_SLOW_REQ_INTERVAL);

		dm_ग_लिखो_reg(compressor->ctx, mmFBC_MISC, misc_value);

		/* Enable FBC */
		set_reg_field_value(value, 1, FBC_CNTL, FBC_GRPH_COMP_EN);
		dm_ग_लिखो_reg(compressor->ctx, addr, value);

		रुको_क्रम_fbc_state_changed(cp110, true);
	पूर्ण
पूर्ण

व्योम dce110_compressor_disable_fbc(काष्ठा compressor *compressor)
अणु
	काष्ठा dce110_compressor *cp110 = TO_DCE110_COMPRESSOR(compressor);
	uपूर्णांक32_t crtc_inst = 0;

	अगर (compressor->options.bits.FBC_SUPPORT) अणु
		अगर (dce110_compressor_is_fbc_enabled_in_hw(compressor, &crtc_inst)) अणु
			uपूर्णांक32_t reg_data;
			/* Turn off compression */
			reg_data = dm_पढ़ो_reg(compressor->ctx, mmFBC_CNTL);
			set_reg_field_value(reg_data, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
			dm_ग_लिखो_reg(compressor->ctx, mmFBC_CNTL, reg_data);

			/* Reset क्रमागत controller_id to undefined */
			compressor->attached_inst = 0;
			compressor->is_enabled = false;

			रुको_क्रम_fbc_state_changed(cp110, false);
		पूर्ण

		/* Sync line buffer which fbc was attached to dce100/110 only */
		अगर (crtc_inst > CONTROLLER_ID_UNDEFINED && crtc_inst < CONTROLLER_ID_D3)
			reset_lb_on_vblank(compressor,
					crtc_inst - CONTROLLER_ID_D0);
	पूर्ण
पूर्ण

bool dce110_compressor_is_fbc_enabled_in_hw(
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


व्योम dce110_compressor_program_compressed_surface_address_and_pitch(
	काष्ठा compressor *compressor,
	काष्ठा compr_addr_and_pitch_params *params)
अणु
	काष्ठा dce110_compressor *cp110 = TO_DCE110_COMPRESSOR(compressor);
	uपूर्णांक32_t value = 0;
	uपूर्णांक32_t fbc_pitch = 0;
	uपूर्णांक32_t compressed_surf_address_low_part =
		compressor->compr_surface_address.addr.low_part;

	cp110->offsets = reg_offsets[params->inst];

	/* Clear content first. */
	dm_ग_लिखो_reg(
		compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS_HIGH),
		0);
	dm_ग_लिखो_reg(compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS), 0);

	/* Write address, HIGH has to be first. */
	dm_ग_लिखो_reg(compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS_HIGH),
		compressor->compr_surface_address.addr.high_part);
	dm_ग_लिखो_reg(compressor->ctx,
		DCP_REG(mmGRPH_COMPRESS_SURFACE_ADDRESS),
		compressed_surf_address_low_part);

	fbc_pitch = align_to_chunks_number_per_line(params->source_view_width);

	अगर (compressor->min_compress_ratio == FBC_COMPRESS_RATIO_1TO1)
		fbc_pitch = fbc_pitch / 8;
	अन्यथा
		DC_LOG_WARNING("%s: Unexpected DCE11 compression ratio",
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

व्योम dce110_compressor_set_fbc_invalidation_triggers(
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
		fbc_trigger,
		FBC_IDLE_FORCE_CLEAR_MASK,
		FBC_IDLE_FORCE_CLEAR_MASK);
	dm_ग_लिखो_reg(compressor->ctx, addr, value);
पूर्ण

काष्ठा compressor *dce110_compressor_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dce110_compressor *cp110 =
		kzalloc(माप(काष्ठा dce110_compressor), GFP_KERNEL);

	अगर (!cp110)
		वापस शून्य;

	dce110_compressor_स्थिरruct(cp110, ctx);
	वापस &cp110->base;
पूर्ण

व्योम dce110_compressor_destroy(काष्ठा compressor **compressor)
अणु
	kमुक्त(TO_DCE110_COMPRESSOR(*compressor));
	*compressor = शून्य;
पूर्ण

व्योम get_max_support_fbc_buffersize(अचिन्हित पूर्णांक *max_x, अचिन्हित पूर्णांक *max_y)
अणु
	*max_x = FBC_MAX_X;
	*max_y = FBC_MAX_Y;

	/* अगर (m_smallLocalFrameBufferMemory == 1)
	 * अणु
	 *	*max_x = FBC_MAX_X_SG;
	 *	*max_y = FBC_MAX_Y_SG;
	 * पूर्ण
	 */
पूर्ण

अटल स्थिर काष्ठा compressor_funcs dce110_compressor_funcs = अणु
	.घातer_up_fbc = dce110_compressor_घातer_up_fbc,
	.enable_fbc = dce110_compressor_enable_fbc,
	.disable_fbc = dce110_compressor_disable_fbc,
	.set_fbc_invalidation_triggers = dce110_compressor_set_fbc_invalidation_triggers,
	.surface_address_and_pitch = dce110_compressor_program_compressed_surface_address_and_pitch,
	.is_fbc_enabled_in_hw = dce110_compressor_is_fbc_enabled_in_hw
पूर्ण;


व्योम dce110_compressor_स्थिरruct(काष्ठा dce110_compressor *compressor,
	काष्ठा dc_context *ctx)
अणु

	compressor->base.options.raw = 0;
	compressor->base.options.bits.FBC_SUPPORT = true;

	/* क्रम dce 11 always use one dram channel क्रम lpt */
	compressor->base.lpt_channels_num = 1;
	compressor->base.options.bits.DUMMY_BACKEND = false;

	/*
	 * check अगर this प्रणाली has more than 1 dram channel; अगर only 1 then lpt
	 * should not be supported
	 */


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
	compressor->base.attached_inst = CONTROLLER_ID_UNDEFINED;
	compressor->base.is_enabled = false;
	compressor->base.funcs = &dce110_compressor_funcs;

पूर्ण

