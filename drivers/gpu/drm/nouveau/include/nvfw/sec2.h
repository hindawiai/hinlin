<शैली गुरु>
#अगर_अघोषित __NVFW_SEC2_H__
#घोषणा __NVFW_SEC2_H__

काष्ठा nv_sec2_args अणु
	u32 freq_hz;
	u32 falc_trace_size;
	u32 falc_trace_dma_base;
	u32 falc_trace_dma_idx;
	bool secure_mode;
पूर्ण;

#घोषणा NV_SEC2_UNIT_INIT                                                  0x01
#घोषणा NV_SEC2_UNIT_ACR                                                   0x08

काष्ठा nv_sec2_init_msg अणु
	काष्ठा nvfw_falcon_msg hdr;
#घोषणा NV_SEC2_INIT_MSG_INIT                                              0x00
	u8 msg_type;

	u8 num_queues;
	u16 os_debug_entry_poपूर्णांक;

	काष्ठा अणु
		u32 offset;
		u16 size;
		u8 index;
#घोषणा NV_SEC2_INIT_MSG_QUEUE_ID_CMDQ                                     0x00
#घोषणा NV_SEC2_INIT_MSG_QUEUE_ID_MSGQ                                     0x01
		u8 id;
	पूर्ण queue_info[2];

	u32 sw_managed_area_offset;
	u16 sw_managed_area_size;
पूर्ण;

काष्ठा nv_sec2_acr_cmd अणु
	काष्ठा nvfw_falcon_cmd hdr;
#घोषणा NV_SEC2_ACR_CMD_BOOTSTRAP_FALCON                                   0x00
	u8 cmd_type;
पूर्ण;

काष्ठा nv_sec2_acr_msg अणु
	काष्ठा nvfw_falcon_cmd hdr;
	u8 msg_type;
पूर्ण;

काष्ठा nv_sec2_acr_bootstrap_falcon_cmd अणु
	काष्ठा nv_sec2_acr_cmd cmd;
#घोषणा NV_SEC2_ACR_BOOTSTRAP_FALCON_FLAGS_RESET_YES                 0x00000000
#घोषणा NV_SEC2_ACR_BOOTSTRAP_FALCON_FLAGS_RESET_NO                  0x00000001
	u32 flags;
	u32 falcon_id;
पूर्ण;

काष्ठा nv_sec2_acr_bootstrap_falcon_msg अणु
	काष्ठा nv_sec2_acr_msg msg;
	u32 error_code;
	u32 falcon_id;
पूर्ण;
#पूर्ण_अगर
