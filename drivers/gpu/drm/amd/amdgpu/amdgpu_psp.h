<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * Author: Huang Rui
 *
 */
#अगर_अघोषित __AMDGPU_PSP_H__
#घोषणा __AMDGPU_PSP_H__

#समावेश "amdgpu.h"
#समावेश "psp_gfx_if.h"
#समावेश "ta_xgmi_if.h"
#समावेश "ta_ras_if.h"
#समावेश "ta_rap_if.h"
#समावेश "ta_secureDisplay_if.h"

#घोषणा PSP_FENCE_BUFFER_SIZE	0x1000
#घोषणा PSP_CMD_BUFFER_SIZE	0x1000
#घोषणा PSP_XGMI_SHARED_MEM_SIZE 0x4000
#घोषणा PSP_RAS_SHARED_MEM_SIZE 0x4000
#घोषणा PSP_1_MEG		0x100000
#घोषणा PSP_TMR_SIZE(adev)	((adev)->asic_type == CHIP_ALDEBARAN ? 0x800000 : 0x400000)
#घोषणा PSP_HDCP_SHARED_MEM_SIZE	0x4000
#घोषणा PSP_DTM_SHARED_MEM_SIZE	0x4000
#घोषणा PSP_RAP_SHARED_MEM_SIZE	0x4000
#घोषणा PSP_SECUREDISPLAY_SHARED_MEM_SIZE	0x4000
#घोषणा PSP_SHARED_MEM_SIZE		0x4000
#घोषणा PSP_FW_NAME_LEN		0x24

काष्ठा psp_context;
काष्ठा psp_xgmi_node_info;
काष्ठा psp_xgmi_topology_info;

क्रमागत psp_bootloader_cmd अणु
	PSP_BL__LOAD_SYSDRV		= 0x10000,
	PSP_BL__LOAD_SOSDRV		= 0x20000,
	PSP_BL__LOAD_KEY_DATABASE	= 0x80000,
	PSP_BL__DRAM_LONG_TRAIN		= 0x100000,
	PSP_BL__DRAM_SHORT_TRAIN	= 0x200000,
	PSP_BL__LOAD_TOS_SPL_TABLE	= 0x10000000,
पूर्ण;

क्रमागत psp_ring_type
अणु
	PSP_RING_TYPE__INVALID = 0,
	/*
	 * These values map to the way the PSP kernel identअगरies the
	 * rings.
	 */
	PSP_RING_TYPE__UM = 1, /* User mode ring (क्रमmerly called RBI) */
	PSP_RING_TYPE__KM = 2  /* Kernel mode ring (क्रमmerly called GPCOM) */
पूर्ण;

काष्ठा psp_ring
अणु
	क्रमागत psp_ring_type		ring_type;
	काष्ठा psp_gfx_rb_frame		*ring_mem;
	uपूर्णांक64_t			ring_mem_mc_addr;
	व्योम				*ring_mem_handle;
	uपूर्णांक32_t			ring_size;
	uपूर्णांक32_t			ring_wptr;
पूर्ण;

/* More रेजिस्टरs may will be supported */
क्रमागत psp_reg_prog_id अणु
	PSP_REG_IH_RB_CNTL        = 0,  /* रेजिस्टर IH_RB_CNTL */
	PSP_REG_IH_RB_CNTL_RING1  = 1,  /* रेजिस्टर IH_RB_CNTL_RING1 */
	PSP_REG_IH_RB_CNTL_RING2  = 2,  /* रेजिस्टर IH_RB_CNTL_RING2 */
	PSP_REG_LAST
पूर्ण;

काष्ठा psp_funcs
अणु
	पूर्णांक (*init_microcode)(काष्ठा psp_context *psp);
	पूर्णांक (*bootloader_load_kdb)(काष्ठा psp_context *psp);
	पूर्णांक (*bootloader_load_spl)(काष्ठा psp_context *psp);
	पूर्णांक (*bootloader_load_sysdrv)(काष्ठा psp_context *psp);
	पूर्णांक (*bootloader_load_sos)(काष्ठा psp_context *psp);
	पूर्णांक (*ring_init)(काष्ठा psp_context *psp, क्रमागत psp_ring_type ring_type);
	पूर्णांक (*ring_create)(काष्ठा psp_context *psp,
			   क्रमागत psp_ring_type ring_type);
	पूर्णांक (*ring_stop)(काष्ठा psp_context *psp,
			    क्रमागत psp_ring_type ring_type);
	पूर्णांक (*ring_destroy)(काष्ठा psp_context *psp,
			    क्रमागत psp_ring_type ring_type);
	bool (*smu_reload_quirk)(काष्ठा psp_context *psp);
	पूर्णांक (*mode1_reset)(काष्ठा psp_context *psp);
	पूर्णांक (*mem_training)(काष्ठा psp_context *psp, uपूर्णांक32_t ops);
	uपूर्णांक32_t (*ring_get_wptr)(काष्ठा psp_context *psp);
	व्योम (*ring_set_wptr)(काष्ठा psp_context *psp, uपूर्णांक32_t value);
	पूर्णांक (*load_usbc_pd_fw)(काष्ठा psp_context *psp, dma_addr_t dma_addr);
	पूर्णांक (*पढ़ो_usbc_pd_fw)(काष्ठा psp_context *psp, uपूर्णांक32_t *fw_ver);
पूर्ण;

#घोषणा AMDGPU_XGMI_MAX_CONNECTED_NODES		64
काष्ठा psp_xgmi_node_info अणु
	uपूर्णांक64_t				node_id;
	uपूर्णांक8_t					num_hops;
	uपूर्णांक8_t					is_sharing_enabled;
	क्रमागत ta_xgmi_asचिन्हित_sdma_engine	sdma_engine;
पूर्ण;

काष्ठा psp_xgmi_topology_info अणु
	uपूर्णांक32_t			num_nodes;
	काष्ठा psp_xgmi_node_info	nodes[AMDGPU_XGMI_MAX_CONNECTED_NODES];
पूर्ण;

काष्ठा psp_asd_context अणु
	bool			asd_initialized;
	uपूर्णांक32_t		session_id;
पूर्ण;

काष्ठा psp_xgmi_context अणु
	uपूर्णांक8_t				initialized;
	uपूर्णांक32_t			session_id;
	काष्ठा amdgpu_bo                *xgmi_shared_bo;
	uपूर्णांक64_t                        xgmi_shared_mc_addr;
	व्योम                            *xgmi_shared_buf;
	काष्ठा psp_xgmi_topology_info	top_info;
पूर्ण;

काष्ठा psp_ras_context अणु
	/*ras fw*/
	bool			ras_initialized;
	uपूर्णांक32_t		session_id;
	काष्ठा amdgpu_bo	*ras_shared_bo;
	uपूर्णांक64_t		ras_shared_mc_addr;
	व्योम			*ras_shared_buf;
	काष्ठा amdgpu_ras	*ras;
पूर्ण;

काष्ठा psp_hdcp_context अणु
	bool			hdcp_initialized;
	uपूर्णांक32_t		session_id;
	काष्ठा amdgpu_bo	*hdcp_shared_bo;
	uपूर्णांक64_t		hdcp_shared_mc_addr;
	व्योम			*hdcp_shared_buf;
	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा psp_dपंचांग_context अणु
	bool			dपंचांग_initialized;
	uपूर्णांक32_t		session_id;
	काष्ठा amdgpu_bo	*dपंचांग_shared_bo;
	uपूर्णांक64_t		dपंचांग_shared_mc_addr;
	व्योम			*dपंचांग_shared_buf;
	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा psp_rap_context अणु
	bool			rap_initialized;
	uपूर्णांक32_t		session_id;
	काष्ठा amdgpu_bo	*rap_shared_bo;
	uपूर्णांक64_t		rap_shared_mc_addr;
	व्योम			*rap_shared_buf;
	काष्ठा mutex		mutex;
पूर्ण;

काष्ठा psp_securedisplay_context अणु
	bool			securedisplay_initialized;
	uपूर्णांक32_t		session_id;
	काष्ठा amdgpu_bo	*securedisplay_shared_bo;
	uपूर्णांक64_t		securedisplay_shared_mc_addr;
	व्योम			*securedisplay_shared_buf;
	काष्ठा mutex		mutex;
पूर्ण;

#घोषणा MEM_TRAIN_SYSTEM_SIGNATURE		0x54534942
#घोषणा GDDR6_MEM_TRAINING_DATA_SIZE_IN_BYTES	0x1000
#घोषणा GDDR6_MEM_TRAINING_OFFSET		0x8000
/*Define the VRAM size that will be encroached by BIST training.*/
#घोषणा GDDR6_MEM_TRAINING_ENCROACHED_SIZE	0x2000000

क्रमागत psp_memory_training_init_flag अणु
	PSP_MEM_TRAIN_NOT_SUPPORT	= 0x0,
	PSP_MEM_TRAIN_SUPPORT		= 0x1,
	PSP_MEM_TRAIN_INIT_FAILED	= 0x2,
	PSP_MEM_TRAIN_RESERVE_SUCCESS	= 0x4,
	PSP_MEM_TRAIN_INIT_SUCCESS	= 0x8,
पूर्ण;

क्रमागत psp_memory_training_ops अणु
	PSP_MEM_TRAIN_SEND_LONG_MSG	= 0x1,
	PSP_MEM_TRAIN_SAVE		= 0x2,
	PSP_MEM_TRAIN_RESTORE		= 0x4,
	PSP_MEM_TRAIN_SEND_SHORT_MSG	= 0x8,
	PSP_MEM_TRAIN_COLD_BOOT		= PSP_MEM_TRAIN_SEND_LONG_MSG,
	PSP_MEM_TRAIN_RESUME		= PSP_MEM_TRAIN_SEND_SHORT_MSG,
पूर्ण;

काष्ठा psp_memory_training_context अणु
	/*training data size*/
	u64 train_data_size;
	/*
	 * sys_cache
	 * cpu भव address
	 * प्रणाली memory buffer that used to store the training data.
	 */
	व्योम *sys_cache;

	/*vram offset of the p2c training data*/
	u64 p2c_train_data_offset;

	/*vram offset of the c2p training data*/
	u64 c2p_train_data_offset;
	काष्ठा amdgpu_bo *c2p_bo;

	क्रमागत psp_memory_training_init_flag init;
	u32 training_cnt;
पूर्ण;

काष्ठा psp_context
अणु
	काष्ठा amdgpu_device            *adev;
	काष्ठा psp_ring                 km_ring;
	काष्ठा psp_gfx_cmd_resp		*cmd;

	स्थिर काष्ठा psp_funcs		*funcs;

	/* firmware buffer */
	काष्ठा amdgpu_bo		*fw_pri_bo;
	uपूर्णांक64_t			fw_pri_mc_addr;
	व्योम				*fw_pri_buf;

	/* sos firmware */
	स्थिर काष्ठा firmware		*sos_fw;
	uपूर्णांक32_t			sos_fw_version;
	uपूर्णांक32_t			sos_feature_version;
	uपूर्णांक32_t			sys_bin_size;
	uपूर्णांक32_t			sos_bin_size;
	uपूर्णांक32_t			toc_bin_size;
	uपूर्णांक32_t			kdb_bin_size;
	uपूर्णांक32_t			spl_bin_size;
	uपूर्णांक32_t			rl_bin_size;
	uपूर्णांक8_t				*sys_start_addr;
	uपूर्णांक8_t				*sos_start_addr;
	uपूर्णांक8_t				*toc_start_addr;
	uपूर्णांक8_t				*kdb_start_addr;
	uपूर्णांक8_t				*spl_start_addr;
	uपूर्णांक8_t				*rl_start_addr;

	/* पंचांगr buffer */
	काष्ठा amdgpu_bo		*पंचांगr_bo;
	uपूर्णांक64_t			पंचांगr_mc_addr;

	/* asd firmware */
	स्थिर काष्ठा firmware		*asd_fw;
	uपूर्णांक32_t			asd_fw_version;
	uपूर्णांक32_t			asd_feature_version;
	uपूर्णांक32_t			asd_ucode_size;
	uपूर्णांक8_t				*asd_start_addr;

	/* toc firmware */
	स्थिर काष्ठा firmware		*toc_fw;
	uपूर्णांक32_t			toc_fw_version;
	uपूर्णांक32_t			toc_feature_version;

	/* fence buffer */
	काष्ठा amdgpu_bo		*fence_buf_bo;
	uपूर्णांक64_t			fence_buf_mc_addr;
	व्योम				*fence_buf;

	/* cmd buffer */
	काष्ठा amdgpu_bo		*cmd_buf_bo;
	uपूर्णांक64_t			cmd_buf_mc_addr;
	काष्ठा psp_gfx_cmd_resp		*cmd_buf_mem;

	/* fence value associated with cmd buffer */
	atomic_t			fence_value;
	/* flag to mark whether gfx fw स्वतःload is supported or not */
	bool				स्वतःload_supported;
	/* flag to mark whether df cstate management centralized to PMFW */
	bool				pmfw_centralized_cstate_management;

	/* xgmi ta firmware and buffer */
	स्थिर काष्ठा firmware		*ta_fw;
	uपूर्णांक32_t			ta_fw_version;
	uपूर्णांक32_t			ta_xgmi_ucode_version;
	uपूर्णांक32_t			ta_xgmi_ucode_size;
	uपूर्णांक8_t				*ta_xgmi_start_addr;
	uपूर्णांक32_t			ta_ras_ucode_version;
	uपूर्णांक32_t			ta_ras_ucode_size;
	uपूर्णांक8_t				*ta_ras_start_addr;

	uपूर्णांक32_t			ta_hdcp_ucode_version;
	uपूर्णांक32_t			ta_hdcp_ucode_size;
	uपूर्णांक8_t				*ta_hdcp_start_addr;

	uपूर्णांक32_t			ta_dपंचांग_ucode_version;
	uपूर्णांक32_t			ta_dपंचांग_ucode_size;
	uपूर्णांक8_t				*ta_dपंचांग_start_addr;

	uपूर्णांक32_t			ta_rap_ucode_version;
	uपूर्णांक32_t			ta_rap_ucode_size;
	uपूर्णांक8_t				*ta_rap_start_addr;

	uपूर्णांक32_t			ta_securedisplay_ucode_version;
	uपूर्णांक32_t			ta_securedisplay_ucode_size;
	uपूर्णांक8_t				*ta_securedisplay_start_addr;

	काष्ठा psp_asd_context		asd_context;
	काष्ठा psp_xgmi_context		xgmi_context;
	काष्ठा psp_ras_context		ras;
	काष्ठा psp_hdcp_context 	hdcp_context;
	काष्ठा psp_dपंचांग_context		dपंचांग_context;
	काष्ठा psp_rap_context		rap_context;
	काष्ठा psp_securedisplay_context	securedisplay_context;
	काष्ठा mutex			mutex;
	काष्ठा psp_memory_training_context mem_train_ctx;
पूर्ण;

काष्ठा amdgpu_psp_funcs अणु
	bool (*check_fw_loading_status)(काष्ठा amdgpu_device *adev,
					क्रमागत AMDGPU_UCODE_ID);
पूर्ण;


#घोषणा psp_ring_init(psp, type) (psp)->funcs->ring_init((psp), (type))
#घोषणा psp_ring_create(psp, type) (psp)->funcs->ring_create((psp), (type))
#घोषणा psp_ring_stop(psp, type) (psp)->funcs->ring_stop((psp), (type))
#घोषणा psp_ring_destroy(psp, type) ((psp)->funcs->ring_destroy((psp), (type)))
#घोषणा psp_init_microcode(psp) \
		((psp)->funcs->init_microcode ? (psp)->funcs->init_microcode((psp)) : 0)
#घोषणा psp_bootloader_load_kdb(psp) \
		((psp)->funcs->bootloader_load_kdb ? (psp)->funcs->bootloader_load_kdb((psp)) : 0)
#घोषणा psp_bootloader_load_spl(psp) \
		((psp)->funcs->bootloader_load_spl ? (psp)->funcs->bootloader_load_spl((psp)) : 0)
#घोषणा psp_bootloader_load_sysdrv(psp) \
		((psp)->funcs->bootloader_load_sysdrv ? (psp)->funcs->bootloader_load_sysdrv((psp)) : 0)
#घोषणा psp_bootloader_load_sos(psp) \
		((psp)->funcs->bootloader_load_sos ? (psp)->funcs->bootloader_load_sos((psp)) : 0)
#घोषणा psp_smu_reload_quirk(psp) \
		((psp)->funcs->smu_reload_quirk ? (psp)->funcs->smu_reload_quirk((psp)) : false)
#घोषणा psp_mode1_reset(psp) \
		((psp)->funcs->mode1_reset ? (psp)->funcs->mode1_reset((psp)) : false)
#घोषणा psp_mem_training(psp, ops) \
	((psp)->funcs->mem_training ? (psp)->funcs->mem_training((psp), (ops)) : 0)

#घोषणा psp_ring_get_wptr(psp) (psp)->funcs->ring_get_wptr((psp))
#घोषणा psp_ring_set_wptr(psp, value) (psp)->funcs->ring_set_wptr((psp), (value))

#घोषणा psp_load_usbc_pd_fw(psp, dma_addr) \
	((psp)->funcs->load_usbc_pd_fw ? \
	(psp)->funcs->load_usbc_pd_fw((psp), (dma_addr)) : -EINVAL)

#घोषणा psp_पढ़ो_usbc_pd_fw(psp, fw_ver) \
	((psp)->funcs->पढ़ो_usbc_pd_fw ? \
	(psp)->funcs->पढ़ो_usbc_pd_fw((psp), fw_ver) : -EINVAL)

बाह्य स्थिर काष्ठा amd_ip_funcs psp_ip_funcs;

बाह्य स्थिर काष्ठा amdgpu_ip_block_version psp_v3_1_ip_block;
बाह्य स्थिर काष्ठा amdgpu_ip_block_version psp_v10_0_ip_block;
बाह्य स्थिर काष्ठा amdgpu_ip_block_version psp_v11_0_ip_block;
बाह्य स्थिर काष्ठा amdgpu_ip_block_version psp_v12_0_ip_block;
बाह्य स्थिर काष्ठा amdgpu_ip_block_version psp_v13_0_ip_block;

बाह्य पूर्णांक psp_रुको_क्रम(काष्ठा psp_context *psp, uपूर्णांक32_t reg_index,
			uपूर्णांक32_t field_val, uपूर्णांक32_t mask, bool check_changed);

पूर्णांक psp_gpu_reset(काष्ठा amdgpu_device *adev);
पूर्णांक psp_update_vcn_sram(काष्ठा amdgpu_device *adev, पूर्णांक inst_idx,
			uपूर्णांक64_t cmd_gpu_addr, पूर्णांक cmd_size);

पूर्णांक psp_xgmi_initialize(काष्ठा psp_context *psp);
पूर्णांक psp_xgmi_terminate(काष्ठा psp_context *psp);
पूर्णांक psp_xgmi_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id);
पूर्णांक psp_xgmi_get_hive_id(काष्ठा psp_context *psp, uपूर्णांक64_t *hive_id);
पूर्णांक psp_xgmi_get_node_id(काष्ठा psp_context *psp, uपूर्णांक64_t *node_id);
पूर्णांक psp_xgmi_get_topology_info(काष्ठा psp_context *psp,
			       पूर्णांक number_devices,
			       काष्ठा psp_xgmi_topology_info *topology);
पूर्णांक psp_xgmi_set_topology_info(काष्ठा psp_context *psp,
			       पूर्णांक number_devices,
			       काष्ठा psp_xgmi_topology_info *topology);

पूर्णांक psp_ras_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id);
पूर्णांक psp_ras_enable_features(काष्ठा psp_context *psp,
		जोड़ ta_ras_cmd_input *info, bool enable);
पूर्णांक psp_ras_trigger_error(काष्ठा psp_context *psp,
			  काष्ठा ta_ras_trigger_error_input *info);

पूर्णांक psp_hdcp_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id);
पूर्णांक psp_dपंचांग_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id);
पूर्णांक psp_rap_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id, क्रमागत ta_rap_status *status);
पूर्णांक psp_securedisplay_invoke(काष्ठा psp_context *psp, uपूर्णांक32_t ta_cmd_id);

पूर्णांक psp_rlc_स्वतःload_start(काष्ठा psp_context *psp);

पूर्णांक psp_reg_program(काष्ठा psp_context *psp, क्रमागत psp_reg_prog_id reg,
		uपूर्णांक32_t value);
पूर्णांक psp_ring_cmd_submit(काष्ठा psp_context *psp,
			uपूर्णांक64_t cmd_buf_mc_addr,
			uपूर्णांक64_t fence_mc_addr,
			पूर्णांक index);
पूर्णांक psp_init_asd_microcode(काष्ठा psp_context *psp,
			   स्थिर अक्षर *chip_name);
पूर्णांक psp_init_toc_microcode(काष्ठा psp_context *psp,
			   स्थिर अक्षर *chip_name);
पूर्णांक psp_init_sos_microcode(काष्ठा psp_context *psp,
			   स्थिर अक्षर *chip_name);
पूर्णांक psp_init_ta_microcode(काष्ठा psp_context *psp,
			  स्थिर अक्षर *chip_name);
पूर्णांक psp_get_fw_attestation_records_addr(काष्ठा psp_context *psp,
					uपूर्णांक64_t *output_ptr);

पूर्णांक psp_load_fw_list(काष्ठा psp_context *psp,
		     काष्ठा amdgpu_firmware_info **ucode_list, पूर्णांक ucode_count);
#पूर्ण_अगर
