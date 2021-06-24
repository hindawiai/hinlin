<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित __AMDGPU_GFX_H__
#घोषणा __AMDGPU_GFX_H__

/*
 * GFX stuff
 */
#समावेश "clearstate_defs.h"
#समावेश "amdgpu_ring.h"
#समावेश "amdgpu_rlc.h"
#समावेश "soc15.h"

/* GFX current status */
#घोषणा AMDGPU_GFX_NORMAL_MODE			0x00000000L
#घोषणा AMDGPU_GFX_SAFE_MODE			0x00000001L
#घोषणा AMDGPU_GFX_PG_DISABLED_MODE		0x00000002L
#घोषणा AMDGPU_GFX_CG_DISABLED_MODE		0x00000004L
#घोषणा AMDGPU_GFX_LBPW_DISABLED_MODE		0x00000008L

#घोषणा AMDGPU_MAX_GFX_QUEUES KGD_MAX_QUEUES
#घोषणा AMDGPU_MAX_COMPUTE_QUEUES KGD_MAX_QUEUES

क्रमागत gfx_pipe_priority अणु
	AMDGPU_GFX_PIPE_PRIO_NORMAL = 1,
	AMDGPU_GFX_PIPE_PRIO_HIGH,
	AMDGPU_GFX_PIPE_PRIO_MAX
पूर्ण;

/* Argument क्रम PPSMC_MSG_GpuChangeState */
क्रमागत gfx_change_state अणु
	sGpuChangeState_D0Entry = 1,
	sGpuChangeState_D3Entry,
पूर्ण;

#घोषणा AMDGPU_GFX_QUEUE_PRIORITY_MINIMUM  0
#घोषणा AMDGPU_GFX_QUEUE_PRIORITY_MAXIMUM  15

काष्ठा amdgpu_mec अणु
	काष्ठा amdgpu_bo	*hpd_eop_obj;
	u64			hpd_eop_gpu_addr;
	काष्ठा amdgpu_bo	*mec_fw_obj;
	u64			mec_fw_gpu_addr;
	u32 num_mec;
	u32 num_pipe_per_mec;
	u32 num_queue_per_pipe;
	व्योम			*mqd_backup[AMDGPU_MAX_COMPUTE_RINGS + 1];

	/* These are the resources क्रम which amdgpu takes ownership */
	DECLARE_BITMAP(queue_biपंचांगap, AMDGPU_MAX_COMPUTE_QUEUES);
पूर्ण;

क्रमागत amdgpu_unmap_queues_action अणु
	PREEMPT_QUEUES = 0,
	RESET_QUEUES,
	DISABLE_PROCESS_QUEUES,
	PREEMPT_QUEUES_NO_UNMAP,
पूर्ण;

काष्ठा kiq_pm4_funcs अणु
	/* Support ASIC-specअगरic kiq pm4 packets*/
	व्योम (*kiq_set_resources)(काष्ठा amdgpu_ring *kiq_ring,
					uपूर्णांक64_t queue_mask);
	व्योम (*kiq_map_queues)(काष्ठा amdgpu_ring *kiq_ring,
					काष्ठा amdgpu_ring *ring);
	व्योम (*kiq_unmap_queues)(काष्ठा amdgpu_ring *kiq_ring,
				 काष्ठा amdgpu_ring *ring,
				 क्रमागत amdgpu_unmap_queues_action action,
				 u64 gpu_addr, u64 seq);
	व्योम (*kiq_query_status)(काष्ठा amdgpu_ring *kiq_ring,
					काष्ठा amdgpu_ring *ring,
					u64 addr,
					u64 seq);
	व्योम (*kiq_invalidate_tlbs)(काष्ठा amdgpu_ring *kiq_ring,
				uपूर्णांक16_t pasid, uपूर्णांक32_t flush_type,
				bool all_hub);
	/* Packet sizes */
	पूर्णांक set_resources_size;
	पूर्णांक map_queues_size;
	पूर्णांक unmap_queues_size;
	पूर्णांक query_status_size;
	पूर्णांक invalidate_tlbs_size;
पूर्ण;

काष्ठा amdgpu_kiq अणु
	u64			eop_gpu_addr;
	काष्ठा amdgpu_bo	*eop_obj;
	spinlock_t              ring_lock;
	काष्ठा amdgpu_ring	ring;
	काष्ठा amdgpu_irq_src	irq;
	स्थिर काष्ठा kiq_pm4_funcs *pmf;
पूर्ण;

/*
 * GPU scratch रेजिस्टरs काष्ठाures, functions & helpers
 */
काष्ठा amdgpu_scratch अणु
	अचिन्हित		num_reg;
	uपूर्णांक32_t                reg_base;
	uपूर्णांक32_t		मुक्त_mask;
पूर्ण;

/*
 * GFX configurations
 */
#घोषणा AMDGPU_GFX_MAX_SE 4
#घोषणा AMDGPU_GFX_MAX_SH_PER_SE 2

काष्ठा amdgpu_rb_config अणु
	uपूर्णांक32_t rb_backend_disable;
	uपूर्णांक32_t user_rb_backend_disable;
	uपूर्णांक32_t raster_config;
	uपूर्णांक32_t raster_config_1;
पूर्ण;

काष्ठा gb_addr_config अणु
	uपूर्णांक16_t pipe_पूर्णांकerleave_size;
	uपूर्णांक8_t num_pipes;
	uपूर्णांक8_t max_compress_frags;
	uपूर्णांक8_t num_banks;
	uपूर्णांक8_t num_se;
	uपूर्णांक8_t num_rb_per_se;
	uपूर्णांक8_t num_pkrs;
पूर्ण;

काष्ठा amdgpu_gfx_config अणु
	अचिन्हित max_shader_engines;
	अचिन्हित max_tile_pipes;
	अचिन्हित max_cu_per_sh;
	अचिन्हित max_sh_per_se;
	अचिन्हित max_backends_per_se;
	अचिन्हित max_texture_channel_caches;
	अचिन्हित max_gprs;
	अचिन्हित max_gs_thपढ़ोs;
	अचिन्हित max_hw_contexts;
	अचिन्हित sc_prim_fअगरo_size_frontend;
	अचिन्हित sc_prim_fअगरo_size_backend;
	अचिन्हित sc_hiz_tile_fअगरo_size;
	अचिन्हित sc_earlyz_tile_fअगरo_size;

	अचिन्हित num_tile_pipes;
	अचिन्हित backend_enable_mask;
	अचिन्हित mem_max_burst_length_bytes;
	अचिन्हित mem_row_size_in_kb;
	अचिन्हित shader_engine_tile_size;
	अचिन्हित num_gpus;
	अचिन्हित multi_gpu_tile_size;
	अचिन्हित mc_arb_ramcfg;
	अचिन्हित num_banks;
	अचिन्हित num_ranks;
	अचिन्हित gb_addr_config;
	अचिन्हित num_rbs;
	अचिन्हित gs_vgt_table_depth;
	अचिन्हित gs_prim_buffer_depth;

	uपूर्णांक32_t tile_mode_array[32];
	uपूर्णांक32_t macrotile_mode_array[16];

	काष्ठा gb_addr_config gb_addr_config_fields;
	काष्ठा amdgpu_rb_config rb_config[AMDGPU_GFX_MAX_SE][AMDGPU_GFX_MAX_SH_PER_SE];

	/* gfx configure feature */
	uपूर्णांक32_t द्विगुन_offchip_lds_buf;
	/* cached value of DB_DEBUG2 */
	uपूर्णांक32_t db_debug2;
	/* gfx10 specअगरic config */
	uपूर्णांक32_t num_sc_per_sh;
	uपूर्णांक32_t num_packer_per_sc;
	uपूर्णांक32_t pa_sc_tile_steering_override;
	uपूर्णांक64_t tcc_disabled_mask;
पूर्ण;

काष्ठा amdgpu_cu_info अणु
	uपूर्णांक32_t simd_per_cu;
	uपूर्णांक32_t max_waves_per_simd;
	uपूर्णांक32_t wave_front_size;
	uपूर्णांक32_t max_scratch_slots_per_cu;
	uपूर्णांक32_t lds_size;

	/* total active CU number */
	uपूर्णांक32_t number;
	uपूर्णांक32_t ao_cu_mask;
	uपूर्णांक32_t ao_cu_biपंचांगap[4][4];
	uपूर्णांक32_t biपंचांगap[4][4];
पूर्ण;

काष्ठा amdgpu_gfx_ras_funcs अणु
	पूर्णांक (*ras_late_init)(काष्ठा amdgpu_device *adev);
	व्योम (*ras_fini)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*ras_error_inject)(काष्ठा amdgpu_device *adev,
				व्योम *inject_अगर);
	पूर्णांक (*query_ras_error_count)(काष्ठा amdgpu_device *adev,
				     व्योम *ras_error_status);
	व्योम (*reset_ras_error_count)(काष्ठा amdgpu_device *adev);
	व्योम (*query_ras_error_status)(काष्ठा amdgpu_device *adev);
	व्योम (*reset_ras_error_status)(काष्ठा amdgpu_device *adev);
	व्योम (*enable_watchकरोg_समयr)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_gfx_funcs अणु
	/* get the gpu घड़ी counter */
	uपूर्णांक64_t (*get_gpu_घड़ी_counter)(काष्ठा amdgpu_device *adev);
	व्योम (*select_se_sh)(काष्ठा amdgpu_device *adev, u32 se_num,
			     u32 sh_num, u32 instance);
	व्योम (*पढ़ो_wave_data)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd,
			       uपूर्णांक32_t wave, uपूर्णांक32_t *dst, पूर्णांक *no_fields);
	व्योम (*पढ़ो_wave_vgprs)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd,
				uपूर्णांक32_t wave, uपूर्णांक32_t thपढ़ो, uपूर्णांक32_t start,
				uपूर्णांक32_t size, uपूर्णांक32_t *dst);
	व्योम (*पढ़ो_wave_sgprs)(काष्ठा amdgpu_device *adev, uपूर्णांक32_t simd,
				uपूर्णांक32_t wave, uपूर्णांक32_t start, uपूर्णांक32_t size,
				uपूर्णांक32_t *dst);
	व्योम (*select_me_pipe_q)(काष्ठा amdgpu_device *adev, u32 me, u32 pipe,
				 u32 queue, u32 vmid);
	व्योम (*init_spm_golden)(काष्ठा amdgpu_device *adev);
	व्योम (*update_perfmon_mgcg)(काष्ठा amdgpu_device *adev, bool enable);
पूर्ण;

काष्ठा sq_work अणु
	काष्ठा work_काष्ठा	work;
	अचिन्हित ih_data;
पूर्ण;

काष्ठा amdgpu_pfp अणु
	काष्ठा amdgpu_bo		*pfp_fw_obj;
	uपूर्णांक64_t			pfp_fw_gpu_addr;
	uपूर्णांक32_t			*pfp_fw_ptr;
पूर्ण;

काष्ठा amdgpu_ce अणु
	काष्ठा amdgpu_bo		*ce_fw_obj;
	uपूर्णांक64_t			ce_fw_gpu_addr;
	uपूर्णांक32_t			*ce_fw_ptr;
पूर्ण;

काष्ठा amdgpu_me अणु
	काष्ठा amdgpu_bo		*me_fw_obj;
	uपूर्णांक64_t			me_fw_gpu_addr;
	uपूर्णांक32_t			*me_fw_ptr;
	uपूर्णांक32_t			num_me;
	uपूर्णांक32_t			num_pipe_per_me;
	uपूर्णांक32_t			num_queue_per_pipe;
	व्योम				*mqd_backup[AMDGPU_MAX_GFX_RINGS];

	/* These are the resources क्रम which amdgpu takes ownership */
	DECLARE_BITMAP(queue_biपंचांगap, AMDGPU_MAX_GFX_QUEUES);
पूर्ण;

काष्ठा amdgpu_gfx अणु
	काष्ठा mutex			gpu_घड़ी_mutex;
	काष्ठा amdgpu_gfx_config	config;
	काष्ठा amdgpu_rlc		rlc;
	काष्ठा amdgpu_pfp		pfp;
	काष्ठा amdgpu_ce		ce;
	काष्ठा amdgpu_me		me;
	काष्ठा amdgpu_mec		mec;
	काष्ठा amdgpu_kiq		kiq;
	काष्ठा amdgpu_scratch		scratch;
	स्थिर काष्ठा firmware		*me_fw;	/* ME firmware */
	uपूर्णांक32_t			me_fw_version;
	स्थिर काष्ठा firmware		*pfp_fw; /* PFP firmware */
	uपूर्णांक32_t			pfp_fw_version;
	स्थिर काष्ठा firmware		*ce_fw;	/* CE firmware */
	uपूर्णांक32_t			ce_fw_version;
	स्थिर काष्ठा firmware		*rlc_fw; /* RLC firmware */
	uपूर्णांक32_t			rlc_fw_version;
	स्थिर काष्ठा firmware		*mec_fw; /* MEC firmware */
	uपूर्णांक32_t			mec_fw_version;
	स्थिर काष्ठा firmware		*mec2_fw; /* MEC2 firmware */
	uपूर्णांक32_t			mec2_fw_version;
	uपूर्णांक32_t			me_feature_version;
	uपूर्णांक32_t			ce_feature_version;
	uपूर्णांक32_t			pfp_feature_version;
	uपूर्णांक32_t			rlc_feature_version;
	uपूर्णांक32_t			rlc_srlc_fw_version;
	uपूर्णांक32_t			rlc_srlc_feature_version;
	uपूर्णांक32_t			rlc_srlg_fw_version;
	uपूर्णांक32_t			rlc_srlg_feature_version;
	uपूर्णांक32_t			rlc_srls_fw_version;
	uपूर्णांक32_t			rlc_srls_feature_version;
	uपूर्णांक32_t			mec_feature_version;
	uपूर्णांक32_t			mec2_feature_version;
	bool				mec_fw_ग_लिखो_रुको;
	bool				me_fw_ग_लिखो_रुको;
	bool				cp_fw_ग_लिखो_रुको;
	काष्ठा amdgpu_ring		gfx_ring[AMDGPU_MAX_GFX_RINGS];
	अचिन्हित			num_gfx_rings;
	काष्ठा amdgpu_ring		compute_ring[AMDGPU_MAX_COMPUTE_RINGS];
	अचिन्हित			num_compute_rings;
	काष्ठा amdgpu_irq_src		eop_irq;
	काष्ठा amdgpu_irq_src		priv_reg_irq;
	काष्ठा amdgpu_irq_src		priv_inst_irq;
	काष्ठा amdgpu_irq_src		cp_ecc_error_irq;
	काष्ठा amdgpu_irq_src		sq_irq;
	काष्ठा sq_work			sq_work;

	/* gfx status */
	uपूर्णांक32_t			gfx_current_status;
	/* ce ram size*/
	अचिन्हित			ce_ram_size;
	काष्ठा amdgpu_cu_info		cu_info;
	स्थिर काष्ठा amdgpu_gfx_funcs	*funcs;

	/* reset mask */
	uपूर्णांक32_t                        grbm_soft_reset;
	uपूर्णांक32_t                        srbm_soft_reset;

	/* gfx off */
	bool                            gfx_off_state; /* true: enabled, false: disabled */
	काष्ठा mutex                    gfx_off_mutex;
	uपूर्णांक32_t                        gfx_off_req_count; /* शेष 1, enable gfx off: dec 1, disable gfx off: add 1 */
	काष्ठा delayed_work             gfx_off_delay_work;

	/* pipe reservation */
	काष्ठा mutex			pipe_reserve_mutex;
	DECLARE_BITMAP			(pipe_reserve_biपंचांगap, AMDGPU_MAX_COMPUTE_QUEUES);

	/*ras */
	काष्ठा ras_common_अगर			*ras_अगर;
	स्थिर काष्ठा amdgpu_gfx_ras_funcs	*ras_funcs;
पूर्ण;

#घोषणा amdgpu_gfx_get_gpu_घड़ी_counter(adev) (adev)->gfx.funcs->get_gpu_घड़ी_counter((adev))
#घोषणा amdgpu_gfx_select_se_sh(adev, se, sh, instance) (adev)->gfx.funcs->select_se_sh((adev), (se), (sh), (instance))
#घोषणा amdgpu_gfx_select_me_pipe_q(adev, me, pipe, q, vmid) (adev)->gfx.funcs->select_me_pipe_q((adev), (me), (pipe), (q), (vmid))
#घोषणा amdgpu_gfx_init_spm_golden(adev) (adev)->gfx.funcs->init_spm_golden((adev))

/**
 * amdgpu_gfx_create_biपंचांगask - create a biपंचांगask
 *
 * @bit_width: length of the mask
 *
 * create a variable length bit mask.
 * Returns the biपंचांगask.
 */
अटल अंतरभूत u32 amdgpu_gfx_create_biपंचांगask(u32 bit_width)
अणु
	वापस (u32)((1ULL << bit_width) - 1);
पूर्ण

पूर्णांक amdgpu_gfx_scratch_get(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *reg);
व्योम amdgpu_gfx_scratch_मुक्त(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg);

व्योम amdgpu_gfx_parse_disable_cu(अचिन्हित *mask, अचिन्हित max_se,
				 अचिन्हित max_sh);

पूर्णांक amdgpu_gfx_kiq_init_ring(काष्ठा amdgpu_device *adev,
			     काष्ठा amdgpu_ring *ring,
			     काष्ठा amdgpu_irq_src *irq);

व्योम amdgpu_gfx_kiq_मुक्त_ring(काष्ठा amdgpu_ring *ring);

व्योम amdgpu_gfx_kiq_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gfx_kiq_init(काष्ठा amdgpu_device *adev,
			अचिन्हित hpd_size);

पूर्णांक amdgpu_gfx_mqd_sw_init(काष्ठा amdgpu_device *adev,
			   अचिन्हित mqd_size);
व्योम amdgpu_gfx_mqd_sw_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gfx_disable_kcq(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gfx_enable_kcq(काष्ठा amdgpu_device *adev);

व्योम amdgpu_gfx_compute_queue_acquire(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gfx_graphics_queue_acquire(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_gfx_mec_queue_to_bit(काष्ठा amdgpu_device *adev, पूर्णांक mec,
				पूर्णांक pipe, पूर्णांक queue);
व्योम amdgpu_queue_mask_bit_to_mec_queue(काष्ठा amdgpu_device *adev, पूर्णांक bit,
				 पूर्णांक *mec, पूर्णांक *pipe, पूर्णांक *queue);
bool amdgpu_gfx_is_mec_queue_enabled(काष्ठा amdgpu_device *adev, पूर्णांक mec,
				     पूर्णांक pipe, पूर्णांक queue);
bool amdgpu_gfx_is_high_priority_compute_queue(काष्ठा amdgpu_device *adev,
					       काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_gfx_me_queue_to_bit(काष्ठा amdgpu_device *adev, पूर्णांक me,
			       पूर्णांक pipe, पूर्णांक queue);
व्योम amdgpu_gfx_bit_to_me_queue(काष्ठा amdgpu_device *adev, पूर्णांक bit,
				पूर्णांक *me, पूर्णांक *pipe, पूर्णांक *queue);
bool amdgpu_gfx_is_me_queue_enabled(काष्ठा amdgpu_device *adev, पूर्णांक me,
				    पूर्णांक pipe, पूर्णांक queue);
व्योम amdgpu_gfx_off_ctrl(काष्ठा amdgpu_device *adev, bool enable);
पूर्णांक amdgpu_get_gfx_off_status(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *value);
पूर्णांक amdgpu_gfx_ras_late_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gfx_ras_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gfx_process_ras_data_cb(काष्ठा amdgpu_device *adev,
		व्योम *err_data,
		काष्ठा amdgpu_iv_entry *entry);
पूर्णांक amdgpu_gfx_cp_ecc_error_irq(काष्ठा amdgpu_device *adev,
				  काष्ठा amdgpu_irq_src *source,
				  काष्ठा amdgpu_iv_entry *entry);
uपूर्णांक32_t amdgpu_kiq_rreg(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg);
व्योम amdgpu_kiq_wreg(काष्ठा amdgpu_device *adev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
पूर्णांक amdgpu_gfx_get_num_kcq(काष्ठा amdgpu_device *adev);
व्योम amdgpu_gfx_state_change_set(काष्ठा amdgpu_device *adev, क्रमागत gfx_change_state state);
#पूर्ण_अगर
