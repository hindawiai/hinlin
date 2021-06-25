<शैली गुरु>
#अगर_अघोषित __NVFW_PMU_H__
#घोषणा __NVFW_PMU_H__

काष्ठा nv_pmu_args अणु
	u32 reserved;
	u32 freq_hz;
	u32 trace_size;
	u32 trace_dma_base;
	u16 trace_dma_base1;
	u8 trace_dma_offset;
	u32 trace_dma_idx;
	bool secure_mode;
	bool उठाओ_priv_sec;
	काष्ठा अणु
		u32 dma_base;
		u16 dma_base1;
		u8 dma_offset;
		u16 fb_size;
		u8 dma_idx;
	पूर्ण gc6_ctx;
	u8 pad;
पूर्ण;

#घोषणा NV_PMU_UNIT_INIT                                                   0x07
#घोषणा NV_PMU_UNIT_ACR                                                    0x0a

काष्ठा nv_pmu_init_msg अणु
	काष्ठा nvfw_falcon_msg hdr;
#घोषणा NV_PMU_INIT_MSG_INIT                                               0x00
	u8 msg_type;

	u8 pad;
	u16 os_debug_entry_poपूर्णांक;

	काष्ठा अणु
		u16 size;
		u16 offset;
		u8 index;
		u8 pad;
	पूर्ण queue_info[5];

	u16 sw_managed_area_offset;
	u16 sw_managed_area_size;
पूर्ण;

काष्ठा nv_pmu_acr_cmd अणु
	काष्ठा nvfw_falcon_cmd hdr;
#घोषणा NV_PMU_ACR_CMD_INIT_WPR_REGION                                     0x00
#घोषणा NV_PMU_ACR_CMD_BOOTSTRAP_FALCON                                    0x01
#घोषणा NV_PMU_ACR_CMD_BOOTSTRAP_MULTIPLE_FALCONS                          0x03
	u8 cmd_type;
पूर्ण;

काष्ठा nv_pmu_acr_msg अणु
	काष्ठा nvfw_falcon_cmd hdr;
	u8 msg_type;
पूर्ण;

काष्ठा nv_pmu_acr_init_wpr_region_cmd अणु
	काष्ठा nv_pmu_acr_cmd cmd;
	u32 region_id;
	u32 wpr_offset;
पूर्ण;

काष्ठा nv_pmu_acr_init_wpr_region_msg अणु
	काष्ठा nv_pmu_acr_msg msg;
	u32 error_code;
पूर्ण;

काष्ठा nv_pmu_acr_bootstrap_falcon_cmd अणु
	काष्ठा nv_pmu_acr_cmd cmd;
#घोषणा NV_PMU_ACR_BOOTSTRAP_FALCON_FLAGS_RESET_YES                  0x00000000
#घोषणा NV_PMU_ACR_BOOTSTRAP_FALCON_FLAGS_RESET_NO                   0x00000001
	u32 flags;
	u32 falcon_id;
पूर्ण;

काष्ठा nv_pmu_acr_bootstrap_falcon_msg अणु
	काष्ठा nv_pmu_acr_msg msg;
	u32 falcon_id;
पूर्ण;

काष्ठा nv_pmu_acr_bootstrap_multiple_falcons_cmd अणु
	काष्ठा nv_pmu_acr_cmd cmd;
#घोषणा NV_PMU_ACR_BOOTSTRAP_MULTIPLE_FALCONS_FLAGS_RESET_YES        0x00000000
#घोषणा NV_PMU_ACR_BOOTSTRAP_MULTIPLE_FALCONS_FLAGS_RESET_NO         0x00000001
	u32 flags;
	u32 falcon_mask;
	u32 use_va_mask;
	u32 wpr_lo;
	u32 wpr_hi;
पूर्ण;

काष्ठा nv_pmu_acr_bootstrap_multiple_falcons_msg अणु
	काष्ठा nv_pmu_acr_msg msg;
	u32 falcon_mask;
पूर्ण;
#पूर्ण_अगर
