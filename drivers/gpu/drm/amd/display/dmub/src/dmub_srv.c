<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#समावेश "../dmub_srv.h"
#समावेश "dmub_dcn20.h"
#समावेश "dmub_dcn21.h"
#समावेश "dmub_cmd.h"
#समावेश "dmub_dcn30.h"
#समावेश "dmub_dcn301.h"
#समावेश "dmub_dcn302.h"
#समावेश "os_types.h"
/*
 * Note: the DMUB service is standalone. No additional headers should be
 * added below or above this line unless they reside within the DMUB
 * folder.
 */

/* Alignment क्रम framebuffer memory. */
#घोषणा DMUB_FB_ALIGNMENT (1024 * 1024)

/* Stack size. */
#घोषणा DMUB_STACK_SIZE (128 * 1024)

/* Context size. */
#घोषणा DMUB_CONTEXT_SIZE (512 * 1024)

/* Mailbox size : Ring buffers are required क्रम both inbox and outbox */
#घोषणा DMUB_MAILBOX_SIZE ((2 * DMUB_RB_SIZE))

/* Default state size अगर meta is असलent. */
#घोषणा DMUB_FW_STATE_SIZE (64 * 1024)

/* Default tracebuffer size अगर meta is असलent. */
#घोषणा DMUB_TRACE_BUFFER_SIZE (64 * 1024)


/* Default scratch mem size. */
#घोषणा DMUB_SCRATCH_MEM_SIZE (256)

/* Number of winकरोws in use. */
#घोषणा DMUB_NUM_WINDOWS (DMUB_WINDOW_TOTAL)
/* Base addresses. */

#घोषणा DMUB_CW0_BASE (0x60000000)
#घोषणा DMUB_CW1_BASE (0x61000000)
#घोषणा DMUB_CW3_BASE (0x63000000)
#घोषणा DMUB_CW4_BASE (0x64000000)
#घोषणा DMUB_CW5_BASE (0x65000000)
#घोषणा DMUB_CW6_BASE (0x66000000)

#घोषणा DMUB_REGION5_BASE (0xA0000000)

अटल अंतरभूत uपूर्णांक32_t dmub_align(uपूर्णांक32_t val, uपूर्णांक32_t factor)
अणु
	वापस (val + factor - 1) / factor * factor;
पूर्ण

व्योम dmub_flush_buffer_mem(स्थिर काष्ठा dmub_fb *fb)
अणु
	स्थिर uपूर्णांक8_t *base = (स्थिर uपूर्णांक8_t *)fb->cpu_addr;
	uपूर्णांक8_t buf[64];
	uपूर्णांक32_t pos, end;

	/**
	 * Read 64-byte chunks since we करोn't want to store a
	 * large temporary buffer क्रम this purpose.
	 */
	end = fb->size / माप(buf) * माप(buf);

	क्रम (pos = 0; pos < end; pos += माप(buf))
		dmub_स_नकल(buf, base + pos, माप(buf));

	/* Read anything leftover पूर्णांकo the buffer. */
	अगर (end < fb->size)
		dmub_स_नकल(buf, base + pos, fb->size - end);
पूर्ण

अटल स्थिर काष्ठा dmub_fw_meta_info *
dmub_get_fw_meta_info(स्थिर काष्ठा dmub_srv_region_params *params)
अणु
	स्थिर जोड़ dmub_fw_meta *meta;
	स्थिर uपूर्णांक8_t *blob = शून्य;
	uपूर्णांक32_t blob_size = 0;
	uपूर्णांक32_t meta_offset = 0;

	अगर (params->fw_bss_data && params->bss_data_size) अणु
		/* Legacy metadata region. */
		blob = params->fw_bss_data;
		blob_size = params->bss_data_size;
		meta_offset = DMUB_FW_META_OFFSET;
	पूर्ण अन्यथा अगर (params->fw_inst_स्थिर && params->inst_स्थिर_size) अणु
		/* Combined metadata region. */
		blob = params->fw_inst_स्थिर;
		blob_size = params->inst_स्थिर_size;
		meta_offset = 0;
	पूर्ण

	अगर (!blob || !blob_size)
		वापस शून्य;

	अगर (blob_size < माप(जोड़ dmub_fw_meta) + meta_offset)
		वापस शून्य;

	meta = (स्थिर जोड़ dmub_fw_meta *)(blob + blob_size - meta_offset -
					    माप(जोड़ dmub_fw_meta));

	अगर (meta->info.magic_value != DMUB_FW_META_MAGIC)
		वापस शून्य;

	वापस &meta->info;
पूर्ण

अटल bool dmub_srv_hw_setup(काष्ठा dmub_srv *dmub, क्रमागत dmub_asic asic)
अणु
	काष्ठा dmub_srv_hw_funcs *funcs = &dmub->hw_funcs;

	चयन (asic) अणु
	हाल DMUB_ASIC_DCN20:
	हाल DMUB_ASIC_DCN21:
	हाल DMUB_ASIC_DCN30:
	हाल DMUB_ASIC_DCN301:
	हाल DMUB_ASIC_DCN302:
		dmub->regs = &dmub_srv_dcn20_regs;

		funcs->reset = dmub_dcn20_reset;
		funcs->reset_release = dmub_dcn20_reset_release;
		funcs->backकरोor_load = dmub_dcn20_backकरोor_load;
		funcs->setup_winकरोws = dmub_dcn20_setup_winकरोws;
		funcs->setup_mailbox = dmub_dcn20_setup_mailbox;
		funcs->get_inbox1_rptr = dmub_dcn20_get_inbox1_rptr;
		funcs->set_inbox1_wptr = dmub_dcn20_set_inbox1_wptr;
		funcs->is_supported = dmub_dcn20_is_supported;
		funcs->is_hw_init = dmub_dcn20_is_hw_init;
		funcs->set_gpपूर्णांक = dmub_dcn20_set_gpपूर्णांक;
		funcs->is_gpपूर्णांक_acked = dmub_dcn20_is_gpपूर्णांक_acked;
		funcs->get_gpपूर्णांक_response = dmub_dcn20_get_gpपूर्णांक_response;
		funcs->get_fw_status = dmub_dcn20_get_fw_boot_status;
		funcs->enable_dmub_boot_options = dmub_dcn20_enable_dmub_boot_options;
		funcs->skip_dmub_panel_घातer_sequence = dmub_dcn20_skip_dmub_panel_घातer_sequence;

		// Out mailbox रेजिस्टर access functions क्रम RN and above
		funcs->setup_out_mailbox = dmub_dcn20_setup_out_mailbox;
		funcs->get_outbox1_wptr = dmub_dcn20_get_outbox1_wptr;
		funcs->set_outbox1_rptr = dmub_dcn20_set_outbox1_rptr;

		//outbox0 call stacks
		funcs->setup_outbox0 = dmub_dcn20_setup_outbox0;
		funcs->get_outbox0_wptr = dmub_dcn20_get_outbox0_wptr;
		funcs->set_outbox0_rptr = dmub_dcn20_set_outbox0_rptr;

		अगर (asic == DMUB_ASIC_DCN21) अणु
			dmub->regs = &dmub_srv_dcn21_regs;

			funcs->is_phy_init = dmub_dcn21_is_phy_init;
		पूर्ण
		अगर (asic == DMUB_ASIC_DCN30) अणु
			dmub->regs = &dmub_srv_dcn30_regs;

			funcs->backकरोor_load = dmub_dcn30_backकरोor_load;
			funcs->setup_winकरोws = dmub_dcn30_setup_winकरोws;
		पूर्ण
		अगर (asic == DMUB_ASIC_DCN301) अणु
			dmub->regs = &dmub_srv_dcn301_regs;

			funcs->backकरोor_load = dmub_dcn30_backकरोor_load;
			funcs->setup_winकरोws = dmub_dcn30_setup_winकरोws;
		पूर्ण
		अगर (asic == DMUB_ASIC_DCN302) अणु
			dmub->regs = &dmub_srv_dcn302_regs;

			funcs->backकरोor_load = dmub_dcn30_backकरोor_load;
			funcs->setup_winकरोws = dmub_dcn30_setup_winकरोws;
		पूर्ण
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

क्रमागत dmub_status dmub_srv_create(काष्ठा dmub_srv *dmub,
				 स्थिर काष्ठा dmub_srv_create_params *params)
अणु
	क्रमागत dmub_status status = DMUB_STATUS_OK;

	dmub_स_रखो(dmub, 0, माप(*dmub));

	dmub->funcs = params->funcs;
	dmub->user_ctx = params->user_ctx;
	dmub->asic = params->asic;
	dmub->fw_version = params->fw_version;
	dmub->is_भव = params->is_भव;

	/* Setup asic dependent hardware funcs. */
	अगर (!dmub_srv_hw_setup(dmub, params->asic)) अणु
		status = DMUB_STATUS_INVALID;
		जाओ cleanup;
	पूर्ण

	/* Override (some) hardware funcs based on user params. */
	अगर (params->hw_funcs) अणु
		अगर (params->hw_funcs->emul_get_inbox1_rptr)
			dmub->hw_funcs.emul_get_inbox1_rptr =
				params->hw_funcs->emul_get_inbox1_rptr;

		अगर (params->hw_funcs->emul_set_inbox1_wptr)
			dmub->hw_funcs.emul_set_inbox1_wptr =
				params->hw_funcs->emul_set_inbox1_wptr;

		अगर (params->hw_funcs->is_supported)
			dmub->hw_funcs.is_supported =
				params->hw_funcs->is_supported;
	पूर्ण

	/* Sanity checks क्रम required hw func poपूर्णांकers. */
	अगर (!dmub->hw_funcs.get_inbox1_rptr ||
	    !dmub->hw_funcs.set_inbox1_wptr) अणु
		status = DMUB_STATUS_INVALID;
		जाओ cleanup;
	पूर्ण

cleanup:
	अगर (status == DMUB_STATUS_OK)
		dmub->sw_init = true;
	अन्यथा
		dmub_srv_destroy(dmub);

	वापस status;
पूर्ण

व्योम dmub_srv_destroy(काष्ठा dmub_srv *dmub)
अणु
	dmub_स_रखो(dmub, 0, माप(*dmub));
पूर्ण

क्रमागत dmub_status
dmub_srv_calc_region_info(काष्ठा dmub_srv *dmub,
			  स्थिर काष्ठा dmub_srv_region_params *params,
			  काष्ठा dmub_srv_region_info *out)
अणु
	काष्ठा dmub_region *inst = &out->regions[DMUB_WINDOW_0_INST_CONST];
	काष्ठा dmub_region *stack = &out->regions[DMUB_WINDOW_1_STACK];
	काष्ठा dmub_region *data = &out->regions[DMUB_WINDOW_2_BSS_DATA];
	काष्ठा dmub_region *bios = &out->regions[DMUB_WINDOW_3_VBIOS];
	काष्ठा dmub_region *mail = &out->regions[DMUB_WINDOW_4_MAILBOX];
	काष्ठा dmub_region *trace_buff = &out->regions[DMUB_WINDOW_5_TRACEBUFF];
	काष्ठा dmub_region *fw_state = &out->regions[DMUB_WINDOW_6_FW_STATE];
	काष्ठा dmub_region *scratch_mem = &out->regions[DMUB_WINDOW_7_SCRATCH_MEM];
	स्थिर काष्ठा dmub_fw_meta_info *fw_info;
	uपूर्णांक32_t fw_state_size = DMUB_FW_STATE_SIZE;
	uपूर्णांक32_t trace_buffer_size = DMUB_TRACE_BUFFER_SIZE;
	uपूर्णांक32_t scratch_mem_size = DMUB_SCRATCH_MEM_SIZE;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	स_रखो(out, 0, माप(*out));

	out->num_regions = DMUB_NUM_WINDOWS;

	inst->base = 0x0;
	inst->top = inst->base + params->inst_स्थिर_size;

	data->base = dmub_align(inst->top, 256);
	data->top = data->base + params->bss_data_size;

	/*
	 * All cache winकरोws below should be aligned to the size
	 * of the DMCUB cache line, 64 bytes.
	 */

	stack->base = dmub_align(data->top, 256);
	stack->top = stack->base + DMUB_STACK_SIZE + DMUB_CONTEXT_SIZE;

	bios->base = dmub_align(stack->top, 256);
	bios->top = bios->base + params->vbios_size;

	mail->base = dmub_align(bios->top, 256);
	mail->top = mail->base + DMUB_MAILBOX_SIZE;

	fw_info = dmub_get_fw_meta_info(params);

	अगर (fw_info) अणु
		fw_state_size = fw_info->fw_region_size;
		trace_buffer_size = fw_info->trace_buffer_size;

		/**
		 * If DM didn't fill in a version, then fill it in based on
		 * the firmware meta now that we have it.
		 *
		 * TODO: Make it easier क्रम driver to extract this out to
		 * pass during creation.
		 */
		अगर (dmub->fw_version == 0)
			dmub->fw_version = fw_info->fw_version;
	पूर्ण

	trace_buff->base = dmub_align(mail->top, 256);
	trace_buff->top = trace_buff->base + dmub_align(trace_buffer_size, 64);

	fw_state->base = dmub_align(trace_buff->top, 256);
	fw_state->top = fw_state->base + dmub_align(fw_state_size, 64);

	scratch_mem->base = dmub_align(fw_state->top, 256);
	scratch_mem->top = scratch_mem->base + dmub_align(scratch_mem_size, 64);

	out->fb_size = dmub_align(scratch_mem->top, 4096);

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_calc_fb_info(काष्ठा dmub_srv *dmub,
				       स्थिर काष्ठा dmub_srv_fb_params *params,
				       काष्ठा dmub_srv_fb_info *out)
अणु
	uपूर्णांक8_t *cpu_base;
	uपूर्णांक64_t gpu_base;
	uपूर्णांक32_t i;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	स_रखो(out, 0, माप(*out));

	अगर (params->region_info->num_regions != DMUB_NUM_WINDOWS)
		वापस DMUB_STATUS_INVALID;

	cpu_base = (uपूर्णांक8_t *)params->cpu_addr;
	gpu_base = params->gpu_addr;

	क्रम (i = 0; i < DMUB_NUM_WINDOWS; ++i) अणु
		स्थिर काष्ठा dmub_region *reg =
			&params->region_info->regions[i];

		out->fb[i].cpu_addr = cpu_base + reg->base;
		out->fb[i].gpu_addr = gpu_base + reg->base;
		out->fb[i].size = reg->top - reg->base;
	पूर्ण

	out->num_fb = DMUB_NUM_WINDOWS;

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_has_hw_support(काष्ठा dmub_srv *dmub,
					 bool *is_supported)
अणु
	*is_supported = false;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (dmub->hw_funcs.is_supported)
		*is_supported = dmub->hw_funcs.is_supported(dmub);

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_is_hw_init(काष्ठा dmub_srv *dmub, bool *is_hw_init)
अणु
	*is_hw_init = false;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (!dmub->hw_init)
		वापस DMUB_STATUS_OK;

	अगर (dmub->hw_funcs.is_hw_init)
		*is_hw_init = dmub->hw_funcs.is_hw_init(dmub);

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_hw_init(काष्ठा dmub_srv *dmub,
				  स्थिर काष्ठा dmub_srv_hw_params *params)
अणु
	काष्ठा dmub_fb *inst_fb = params->fb[DMUB_WINDOW_0_INST_CONST];
	काष्ठा dmub_fb *stack_fb = params->fb[DMUB_WINDOW_1_STACK];
	काष्ठा dmub_fb *data_fb = params->fb[DMUB_WINDOW_2_BSS_DATA];
	काष्ठा dmub_fb *bios_fb = params->fb[DMUB_WINDOW_3_VBIOS];
	काष्ठा dmub_fb *mail_fb = params->fb[DMUB_WINDOW_4_MAILBOX];
	काष्ठा dmub_fb *tracebuff_fb = params->fb[DMUB_WINDOW_5_TRACEBUFF];
	काष्ठा dmub_fb *fw_state_fb = params->fb[DMUB_WINDOW_6_FW_STATE];
	काष्ठा dmub_fb *scratch_mem_fb = params->fb[DMUB_WINDOW_7_SCRATCH_MEM];

	काष्ठा dmub_rb_init_params rb_params, outbox0_rb_params;
	काष्ठा dmub_winकरोw cw0, cw1, cw2, cw3, cw4, cw5, cw6;
	काष्ठा dmub_region inbox1, outbox1, outbox0;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (!inst_fb || !stack_fb || !data_fb || !bios_fb || !mail_fb ||
		!tracebuff_fb || !fw_state_fb || !scratch_mem_fb) अणु
		ASSERT(0);
		वापस DMUB_STATUS_INVALID;
	पूर्ण

	dmub->fb_base = params->fb_base;
	dmub->fb_offset = params->fb_offset;
	dmub->psp_version = params->psp_version;

	अगर (dmub->hw_funcs.reset)
		dmub->hw_funcs.reset(dmub);

	cw0.offset.quad_part = inst_fb->gpu_addr;
	cw0.region.base = DMUB_CW0_BASE;
	cw0.region.top = cw0.region.base + inst_fb->size - 1;

	cw1.offset.quad_part = stack_fb->gpu_addr;
	cw1.region.base = DMUB_CW1_BASE;
	cw1.region.top = cw1.region.base + stack_fb->size - 1;

	अगर (params->load_inst_स्थिर && dmub->hw_funcs.backकरोor_load) अणु
		/**
		 * Read back all the inकाष्ठाion memory so we करोn't hang the
		 * DMCUB when backकरोor loading अगर the ग_लिखो from x86 hasn't been
		 * flushed yet. This only occurs in backकरोor loading.
		 */
		dmub_flush_buffer_mem(inst_fb);
		dmub->hw_funcs.backकरोor_load(dmub, &cw0, &cw1);
	पूर्ण

	cw2.offset.quad_part = data_fb->gpu_addr;
	cw2.region.base = DMUB_CW0_BASE + inst_fb->size;
	cw2.region.top = cw2.region.base + data_fb->size;

	cw3.offset.quad_part = bios_fb->gpu_addr;
	cw3.region.base = DMUB_CW3_BASE;
	cw3.region.top = cw3.region.base + bios_fb->size;

	cw4.offset.quad_part = mail_fb->gpu_addr;
	cw4.region.base = DMUB_CW4_BASE;
	cw4.region.top = cw4.region.base + mail_fb->size;

	/**
	 * Doubled the mailbox region to accomodate inbox and outbox.
	 * Note: Currently, currently total mailbox size is 16KB. It is split
	 * equally पूर्णांकo 8KB between inbox and outbox. If this config is
	 * changed, then uncached base address configuration of outbox1
	 * has to be updated in funcs->setup_out_mailbox.
	 */
	inbox1.base = cw4.region.base;
	inbox1.top = cw4.region.base + DMUB_RB_SIZE;
	outbox1.base = inbox1.top;
	outbox1.top = cw4.region.top;

	cw5.offset.quad_part = tracebuff_fb->gpu_addr;
	cw5.region.base = DMUB_CW5_BASE;
	cw5.region.top = cw5.region.base + tracebuff_fb->size;

	outbox0.base = DMUB_REGION5_BASE + TRACE_BUFFER_ENTRY_OFFSET;
	outbox0.top = outbox0.base + tracebuff_fb->size - TRACE_BUFFER_ENTRY_OFFSET;

	cw6.offset.quad_part = fw_state_fb->gpu_addr;
	cw6.region.base = DMUB_CW6_BASE;
	cw6.region.top = cw6.region.base + fw_state_fb->size;

	dmub->fw_state = fw_state_fb->cpu_addr;

	dmub->scratch_mem_fb = *scratch_mem_fb;

	अगर (dmub->hw_funcs.setup_winकरोws)
		dmub->hw_funcs.setup_winकरोws(dmub, &cw2, &cw3, &cw4, &cw5, &cw6);

	अगर (dmub->hw_funcs.setup_outbox0)
		dmub->hw_funcs.setup_outbox0(dmub, &outbox0);

	अगर (dmub->hw_funcs.setup_mailbox)
		dmub->hw_funcs.setup_mailbox(dmub, &inbox1);
	अगर (dmub->hw_funcs.setup_out_mailbox)
		dmub->hw_funcs.setup_out_mailbox(dmub, &outbox1);

	dmub_स_रखो(&rb_params, 0, माप(rb_params));
	rb_params.ctx = dmub;
	rb_params.base_address = mail_fb->cpu_addr;
	rb_params.capacity = DMUB_RB_SIZE;
	dmub_rb_init(&dmub->inbox1_rb, &rb_params);

	// Initialize outbox1 ring buffer
	rb_params.ctx = dmub;
	rb_params.base_address = (व्योम *) ((uपूर्णांक8_t *) (mail_fb->cpu_addr) + DMUB_RB_SIZE);
	rb_params.capacity = DMUB_RB_SIZE;
	dmub_rb_init(&dmub->outbox1_rb, &rb_params);

	dmub_स_रखो(&outbox0_rb_params, 0, माप(outbox0_rb_params));
	outbox0_rb_params.ctx = dmub;
	outbox0_rb_params.base_address = (व्योम *)((uपूर्णांकptr_t)(tracebuff_fb->cpu_addr) + TRACE_BUFFER_ENTRY_OFFSET);
	outbox0_rb_params.capacity = tracebuff_fb->size - dmub_align(TRACE_BUFFER_ENTRY_OFFSET, 64);
	dmub_rb_init(&dmub->outbox0_rb, &outbox0_rb_params);

	अगर (dmub->hw_funcs.reset_release)
		dmub->hw_funcs.reset_release(dmub);

	dmub->hw_init = true;

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_hw_reset(काष्ठा dmub_srv *dmub)
अणु
	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (dmub->hw_funcs.reset)
		dmub->hw_funcs.reset(dmub);

	dmub->hw_init = false;

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_cmd_queue(काष्ठा dmub_srv *dmub,
				    स्थिर जोड़ dmub_rb_cmd *cmd)
अणु
	अगर (!dmub->hw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (dmub_rb_push_front(&dmub->inbox1_rb, cmd))
		वापस DMUB_STATUS_OK;

	वापस DMUB_STATUS_QUEUE_FULL;
पूर्ण

क्रमागत dmub_status dmub_srv_cmd_execute(काष्ठा dmub_srv *dmub)
अणु
	अगर (!dmub->hw_init)
		वापस DMUB_STATUS_INVALID;

	/**
	 * Read back all the queued commands to ensure that they've
	 * been flushed to framebuffer memory. Otherwise DMCUB might
	 * पढ़ो back stale, fully invalid or partially invalid data.
	 */
	dmub_rb_flush_pending(&dmub->inbox1_rb);

		dmub->hw_funcs.set_inbox1_wptr(dmub, dmub->inbox1_rb.wrpt);
	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_रुको_क्रम_स्वतः_load(काष्ठा dmub_srv *dmub,
					     uपूर्णांक32_t समयout_us)
अणु
	uपूर्णांक32_t i;

	अगर (!dmub->hw_init)
		वापस DMUB_STATUS_INVALID;

	क्रम (i = 0; i <= समयout_us; i += 100) अणु
		जोड़ dmub_fw_boot_status status = dmub->hw_funcs.get_fw_status(dmub);

		अगर (status.bits.dal_fw && status.bits.mailbox_rdy)
			वापस DMUB_STATUS_OK;

		udelay(100);
	पूर्ण

	वापस DMUB_STATUS_TIMEOUT;
पूर्ण

क्रमागत dmub_status dmub_srv_रुको_क्रम_phy_init(काष्ठा dmub_srv *dmub,
					    uपूर्णांक32_t समयout_us)
अणु
	uपूर्णांक32_t i = 0;

	अगर (!dmub->hw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (!dmub->hw_funcs.is_phy_init)
		वापस DMUB_STATUS_OK;

	क्रम (i = 0; i <= समयout_us; i += 10) अणु
		अगर (dmub->hw_funcs.is_phy_init(dmub))
			वापस DMUB_STATUS_OK;

		udelay(10);
	पूर्ण

	वापस DMUB_STATUS_TIMEOUT;
पूर्ण

क्रमागत dmub_status dmub_srv_रुको_क्रम_idle(काष्ठा dmub_srv *dmub,
					uपूर्णांक32_t समयout_us)
अणु
	uपूर्णांक32_t i;

	अगर (!dmub->hw_init)
		वापस DMUB_STATUS_INVALID;

	क्रम (i = 0; i <= समयout_us; ++i) अणु
			dmub->inbox1_rb.rptr = dmub->hw_funcs.get_inbox1_rptr(dmub);
		अगर (dmub_rb_empty(&dmub->inbox1_rb))
			वापस DMUB_STATUS_OK;

		udelay(1);
	पूर्ण

	वापस DMUB_STATUS_TIMEOUT;
पूर्ण

क्रमागत dmub_status
dmub_srv_send_gpपूर्णांक_command(काष्ठा dmub_srv *dmub,
			    क्रमागत dmub_gpपूर्णांक_command command_code,
			    uपूर्णांक16_t param, uपूर्णांक32_t समयout_us)
अणु
	जोड़ dmub_gpपूर्णांक_data_रेजिस्टर reg;
	uपूर्णांक32_t i;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (!dmub->hw_funcs.set_gpपूर्णांक)
		वापस DMUB_STATUS_INVALID;

	अगर (!dmub->hw_funcs.is_gpपूर्णांक_acked)
		वापस DMUB_STATUS_INVALID;

	reg.bits.status = 1;
	reg.bits.command_code = command_code;
	reg.bits.param = param;

	dmub->hw_funcs.set_gpपूर्णांक(dmub, reg);

	क्रम (i = 0; i < समयout_us; ++i) अणु
		udelay(1);

		अगर (dmub->hw_funcs.is_gpपूर्णांक_acked(dmub, reg))
			वापस DMUB_STATUS_OK;
	पूर्ण

	वापस DMUB_STATUS_TIMEOUT;
पूर्ण

क्रमागत dmub_status dmub_srv_get_gpपूर्णांक_response(काष्ठा dmub_srv *dmub,
					     uपूर्णांक32_t *response)
अणु
	*response = 0;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (!dmub->hw_funcs.get_gpपूर्णांक_response)
		वापस DMUB_STATUS_INVALID;

	*response = dmub->hw_funcs.get_gpपूर्णांक_response(dmub);

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_get_fw_boot_status(काष्ठा dmub_srv *dmub,
					     जोड़ dmub_fw_boot_status *status)
अणु
	status->all = 0;

	अगर (!dmub->sw_init)
		वापस DMUB_STATUS_INVALID;

	अगर (dmub->hw_funcs.get_fw_status)
		*status = dmub->hw_funcs.get_fw_status(dmub);

	वापस DMUB_STATUS_OK;
पूर्ण

क्रमागत dmub_status dmub_srv_cmd_with_reply_data(काष्ठा dmub_srv *dmub,
					      जोड़ dmub_rb_cmd *cmd)
अणु
	क्रमागत dmub_status status = DMUB_STATUS_OK;

	// Queue command
	status = dmub_srv_cmd_queue(dmub, cmd);

	अगर (status != DMUB_STATUS_OK)
		वापस status;

	// Execute command
	status = dmub_srv_cmd_execute(dmub);

	अगर (status != DMUB_STATUS_OK)
		वापस status;

	// Wait क्रम DMUB to process command
	status = dmub_srv_रुको_क्रम_idle(dmub, 100000);

	अगर (status != DMUB_STATUS_OK)
		वापस status;

	// Copy data back from ring buffer पूर्णांकo command
	dmub_rb_get_वापस_data(&dmub->inbox1_rb, cmd);

	वापस status;
पूर्ण

अटल अंतरभूत bool dmub_rb_out_trace_buffer_front(काष्ठा dmub_rb *rb,
				 व्योम *entry)
अणु
	स्थिर uपूर्णांक64_t *src = (स्थिर uपूर्णांक64_t *)(rb->base_address) + rb->rptr / माप(uपूर्णांक64_t);
	uपूर्णांक64_t *dst = (uपूर्णांक64_t *)entry;
	uपूर्णांक8_t i;
	uपूर्णांक8_t loop_count;

	अगर (rb->rptr == rb->wrpt)
		वापस false;

	loop_count = माप(काष्ठा dmcub_trace_buf_entry) / माप(uपूर्णांक64_t);
	// copying data
	क्रम (i = 0; i < loop_count; i++)
		*dst++ = *src++;

	rb->rptr += माप(काष्ठा dmcub_trace_buf_entry);

	rb->rptr %= rb->capacity;

	वापस true;
पूर्ण

bool dmub_srv_get_outbox0_msg(काष्ठा dmub_srv *dmub, काष्ठा dmcub_trace_buf_entry *entry)
अणु
	dmub->outbox0_rb.wrpt = dmub->hw_funcs.get_outbox0_wptr(dmub);

	वापस dmub_rb_out_trace_buffer_front(&dmub->outbox0_rb, (व्योम *)entry);
पूर्ण
