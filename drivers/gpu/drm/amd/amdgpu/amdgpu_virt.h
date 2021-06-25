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
 * Author: Monk.liu@amd.com
 */
#अगर_अघोषित AMDGPU_VIRT_H
#घोषणा AMDGPU_VIRT_H

#समावेश "amdgv_sriovmsg.h"

#घोषणा AMDGPU_SRIOV_CAPS_SRIOV_VBIOS  (1 << 0) /* vBIOS is sr-iov पढ़ोy */
#घोषणा AMDGPU_SRIOV_CAPS_ENABLE_IOV   (1 << 1) /* sr-iov is enabled on this GPU */
#घोषणा AMDGPU_SRIOV_CAPS_IS_VF        (1 << 2) /* this GPU is a भव function */
#घोषणा AMDGPU_PASSTHROUGH_MODE        (1 << 3) /* thw whole GPU is pass through क्रम VM */
#घोषणा AMDGPU_SRIOV_CAPS_RUNTIME      (1 << 4) /* is out of full access mode */

/* all asic after AI use this offset */
#घोषणा mmRCC_IOV_FUNC_IDENTIFIER 0xDE5
/* tonga/fiji use this offset */
#घोषणा mmBIF_IOV_FUNC_IDENTIFIER 0x1503

क्रमागत amdgpu_sriov_vf_mode अणु
	SRIOV_VF_MODE_BARE_METAL = 0,
	SRIOV_VF_MODE_ONE_VF,
	SRIOV_VF_MODE_MULTI_VF,
पूर्ण;

काष्ठा amdgpu_mm_table अणु
	काष्ठा amdgpu_bo	*bo;
	uपूर्णांक32_t		*cpu_addr;
	uपूर्णांक64_t		gpu_addr;
पूर्ण;

#घोषणा AMDGPU_VF_ERROR_ENTRY_SIZE    16

/* काष्ठा error_entry - amdgpu VF error inक्रमmation. */
काष्ठा amdgpu_vf_error_buffer अणु
	काष्ठा mutex lock;
	पूर्णांक पढ़ो_count;
	पूर्णांक ग_लिखो_count;
	uपूर्णांक16_t code[AMDGPU_VF_ERROR_ENTRY_SIZE];
	uपूर्णांक16_t flags[AMDGPU_VF_ERROR_ENTRY_SIZE];
	uपूर्णांक64_t data[AMDGPU_VF_ERROR_ENTRY_SIZE];
पूर्ण;

/**
 * काष्ठा amdgpu_virt_ops - amdgpu device virt operations
 */
काष्ठा amdgpu_virt_ops अणु
	पूर्णांक (*req_full_gpu)(काष्ठा amdgpu_device *adev, bool init);
	पूर्णांक (*rel_full_gpu)(काष्ठा amdgpu_device *adev, bool init);
	पूर्णांक (*req_init_data)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*reset_gpu)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*रुको_reset)(काष्ठा amdgpu_device *adev);
	व्योम (*trans_msg)(काष्ठा amdgpu_device *adev, u32 req, u32 data1, u32 data2, u32 data3);
पूर्ण;

/*
 * Firmware Reserve Frame buffer
 */
काष्ठा amdgpu_virt_fw_reserve अणु
	काष्ठा amd_sriov_msg_pf2vf_info_header *p_pf2vf;
	काष्ठा amd_sriov_msg_vf2pf_info_header *p_vf2pf;
	अचिन्हित पूर्णांक checksum_key;
पूर्ण;

/*
 * Legacy GIM header
 *
 * Defination between PF and VF
 * Structures क्रमcibly aligned to 4 to keep the same style as PF.
 */
#घोषणा AMDGIM_DATAEXCHANGE_OFFSET		(64 * 1024)

#घोषणा AMDGIM_GET_STRUCTURE_RESERVED_SIZE(total, u8, u16, u32, u64) \
		(total - (((u8)+3) / 4 + ((u16)+1) / 2 + (u32) + (u64)*2))

क्रमागत AMDGIM_FEATURE_FLAG अणु
	/* GIM supports feature of Error log collecting */
	AMDGIM_FEATURE_ERROR_LOG_COLLECT = 0x1,
	/* GIM supports feature of loading uCodes */
	AMDGIM_FEATURE_GIM_LOAD_UCODES   = 0x2,
	/* VRAM LOST by GIM */
	AMDGIM_FEATURE_GIM_FLR_VRAMLOST = 0x4,
	/* MM bandwidth */
	AMDGIM_FEATURE_GIM_MM_BW_MGR = 0x8,
	/* PP ONE VF MODE in GIM */
	AMDGIM_FEATURE_PP_ONE_VF = (1 << 4),
	/* Indirect Reg Access enabled */
	AMDGIM_FEATURE_INसूचीECT_REG_ACCESS = (1 << 5),
पूर्ण;

क्रमागत AMDGIM_REG_ACCESS_FLAG अणु
	/* Use PSP to program IH_RB_CNTL */
	AMDGIM_FEATURE_IH_REG_PSP_EN     = (1 << 0),
	/* Use RLC to program MMHUB regs */
	AMDGIM_FEATURE_MMHUB_REG_RLC_EN  = (1 << 1),
	/* Use RLC to program GC regs */
	AMDGIM_FEATURE_GC_REG_RLC_EN     = (1 << 2),
पूर्ण;

काष्ठा amdgim_pf2vf_info_v1 अणु
	/* header contains size and version */
	काष्ठा amd_sriov_msg_pf2vf_info_header header;
	/* max_width * max_height */
	अचिन्हित पूर्णांक uvd_enc_max_pixels_count;
	/* 16x16 pixels/sec, codec independent */
	अचिन्हित पूर्णांक uvd_enc_max_bandwidth;
	/* max_width * max_height */
	अचिन्हित पूर्णांक vce_enc_max_pixels_count;
	/* 16x16 pixels/sec, codec independent */
	अचिन्हित पूर्णांक vce_enc_max_bandwidth;
	/* MEC FW position in kb from the start of visible frame buffer */
	अचिन्हित पूर्णांक mecfw_kboffset;
	/* The features flags of the GIM driver supports. */
	अचिन्हित पूर्णांक feature_flags;
	/* use निजी key from mailbox 2 to create chueksum */
	अचिन्हित पूर्णांक checksum;
पूर्ण __aligned(4);

काष्ठा amdgim_vf2pf_info_v1 अणु
	/* header contains size and version */
	काष्ठा amd_sriov_msg_vf2pf_info_header header;
	/* driver version */
	अक्षर driver_version[64];
	/* driver certअगरication, 1=WHQL, 0=None */
	अचिन्हित पूर्णांक driver_cert;
	/* guest OS type and version: need a define */
	अचिन्हित पूर्णांक os_info;
	/* in the unit of 1M */
	अचिन्हित पूर्णांक fb_usage;
	/* guest gfx engine usage percentage */
	अचिन्हित पूर्णांक gfx_usage;
	/* guest gfx engine health percentage */
	अचिन्हित पूर्णांक gfx_health;
	/* guest compute engine usage percentage */
	अचिन्हित पूर्णांक compute_usage;
	/* guest compute engine health percentage */
	अचिन्हित पूर्णांक compute_health;
	/* guest vce engine usage percentage. 0xffff means N/A. */
	अचिन्हित पूर्णांक vce_enc_usage;
	/* guest vce engine health percentage. 0xffff means N/A. */
	अचिन्हित पूर्णांक vce_enc_health;
	/* guest uvd engine usage percentage. 0xffff means N/A. */
	अचिन्हित पूर्णांक uvd_enc_usage;
	/* guest uvd engine usage percentage. 0xffff means N/A. */
	अचिन्हित पूर्णांक uvd_enc_health;
	अचिन्हित पूर्णांक checksum;
पूर्ण __aligned(4);

काष्ठा amdgim_vf2pf_info_v2 अणु
	/* header contains size and version */
	काष्ठा amd_sriov_msg_vf2pf_info_header header;
	uपूर्णांक32_t checksum;
	/* driver version */
	uपूर्णांक8_t driver_version[64];
	/* driver certअगरication, 1=WHQL, 0=None */
	uपूर्णांक32_t driver_cert;
	/* guest OS type and version: need a define */
	uपूर्णांक32_t os_info;
	/* in the unit of 1M */
	uपूर्णांक32_t fb_usage;
	/* guest gfx engine usage percentage */
	uपूर्णांक32_t gfx_usage;
	/* guest gfx engine health percentage */
	uपूर्णांक32_t gfx_health;
	/* guest compute engine usage percentage */
	uपूर्णांक32_t compute_usage;
	/* guest compute engine health percentage */
	uपूर्णांक32_t compute_health;
	/* guest vce engine usage percentage. 0xffff means N/A. */
	uपूर्णांक32_t vce_enc_usage;
	/* guest vce engine health percentage. 0xffff means N/A. */
	uपूर्णांक32_t vce_enc_health;
	/* guest uvd engine usage percentage. 0xffff means N/A. */
	uपूर्णांक32_t uvd_enc_usage;
	/* guest uvd engine usage percentage. 0xffff means N/A. */
	uपूर्णांक32_t uvd_enc_health;
	uपूर्णांक32_t reserved[AMDGIM_GET_STRUCTURE_RESERVED_SIZE(256, 64, 0, (12 + माप(काष्ठा amd_sriov_msg_vf2pf_info_header)/माप(uपूर्णांक32_t)), 0)];
पूर्ण __aligned(4);

काष्ठा amdgpu_virt_ras_err_handler_data अणु
	/* poपूर्णांक to bad page records array */
	काष्ठा eeprom_table_record *bps;
	/* poपूर्णांक to reserved bo array */
	काष्ठा amdgpu_bo **bps_bo;
	/* the count of entries */
	पूर्णांक count;
	/* last reserved entry's index + 1 */
	पूर्णांक last_reserved;
पूर्ण;

/* GPU भवization */
काष्ठा amdgpu_virt अणु
	uपूर्णांक32_t			caps;
	काष्ठा amdgpu_bo		*csa_obj;
	व्योम				*csa_cpu_addr;
	bool chained_ib_support;
	uपूर्णांक32_t			reg_val_offs;
	काष्ठा amdgpu_irq_src		ack_irq;
	काष्ठा amdgpu_irq_src		rcv_irq;
	काष्ठा work_काष्ठा		flr_work;
	काष्ठा amdgpu_mm_table		mm_table;
	स्थिर काष्ठा amdgpu_virt_ops	*ops;
	काष्ठा amdgpu_vf_error_buffer	vf_errors;
	काष्ठा amdgpu_virt_fw_reserve	fw_reserve;
	uपूर्णांक32_t gim_feature;
	uपूर्णांक32_t reg_access_mode;
	पूर्णांक req_init_data_ver;
	bool tdr_debug;
	काष्ठा amdgpu_virt_ras_err_handler_data *virt_eh_data;
	bool ras_init_करोne;
	uपूर्णांक32_t reg_access;

	/* vf2pf message */
	काष्ठा delayed_work vf2pf_work;
	uपूर्णांक32_t vf2pf_update_पूर्णांकerval_ms;
पूर्ण;

#घोषणा amdgpu_sriov_enabled(adev) \
((adev)->virt.caps & AMDGPU_SRIOV_CAPS_ENABLE_IOV)

#घोषणा amdgpu_sriov_vf(adev) \
((adev)->virt.caps & AMDGPU_SRIOV_CAPS_IS_VF)

#घोषणा amdgpu_sriov_bios(adev) \
((adev)->virt.caps & AMDGPU_SRIOV_CAPS_SRIOV_VBIOS)

#घोषणा amdgpu_sriov_runसमय(adev) \
((adev)->virt.caps & AMDGPU_SRIOV_CAPS_RUNTIME)

#घोषणा amdgpu_sriov_fullaccess(adev) \
(amdgpu_sriov_vf((adev)) && !amdgpu_sriov_runसमय((adev)))

#घोषणा amdgpu_sriov_reg_indirect_en(adev) \
(amdgpu_sriov_vf((adev)) && \
	((adev)->virt.gim_feature & (AMDGIM_FEATURE_INसूचीECT_REG_ACCESS)))

#घोषणा amdgpu_sriov_reg_indirect_ih(adev) \
(amdgpu_sriov_vf((adev)) && \
	((adev)->virt.reg_access & (AMDGIM_FEATURE_IH_REG_PSP_EN)))

#घोषणा amdgpu_sriov_reg_indirect_mmhub(adev) \
(amdgpu_sriov_vf((adev)) && \
	((adev)->virt.reg_access & (AMDGIM_FEATURE_MMHUB_REG_RLC_EN)))

#घोषणा amdgpu_sriov_reg_indirect_gc(adev) \
(amdgpu_sriov_vf((adev)) && \
	((adev)->virt.reg_access & (AMDGIM_FEATURE_GC_REG_RLC_EN)))

#घोषणा amdgpu_passthrough(adev) \
((adev)->virt.caps & AMDGPU_PASSTHROUGH_MODE)

अटल अंतरभूत bool is_भव_machine(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	वापस boot_cpu_has(X86_FEATURE_HYPERVISOR);
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#घोषणा amdgpu_sriov_is_pp_one_vf(adev) \
	((adev)->virt.gim_feature & AMDGIM_FEATURE_PP_ONE_VF)
#घोषणा amdgpu_sriov_is_debug(adev) \
	((!amdgpu_in_reset(adev)) && adev->virt.tdr_debug)
#घोषणा amdgpu_sriov_is_normal(adev) \
	((!amdgpu_in_reset(adev)) && (!adev->virt.tdr_debug))

bool amdgpu_virt_mmio_blocked(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_init_setting(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_kiq_reg_ग_लिखो_reg_रुको(काष्ठा amdgpu_device *adev,
					uपूर्णांक32_t reg0, uपूर्णांक32_t rreg1,
					uपूर्णांक32_t ref, uपूर्णांक32_t mask);
पूर्णांक amdgpu_virt_request_full_gpu(काष्ठा amdgpu_device *adev, bool init);
पूर्णांक amdgpu_virt_release_full_gpu(काष्ठा amdgpu_device *adev, bool init);
पूर्णांक amdgpu_virt_reset_gpu(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_request_init_data(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_virt_रुको_reset(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_virt_alloc_mm_table(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_मुक्त_mm_table(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_release_ras_err_handler_data(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_init_data_exchange(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_fini_data_exchange(काष्ठा amdgpu_device *adev);
व्योम amdgpu_detect_भवization(काष्ठा amdgpu_device *adev);

bool amdgpu_virt_can_access_debugfs(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_virt_enable_access_debugfs(काष्ठा amdgpu_device *adev);
व्योम amdgpu_virt_disable_access_debugfs(काष्ठा amdgpu_device *adev);

क्रमागत amdgpu_sriov_vf_mode amdgpu_virt_get_sriov_vf_mode(काष्ठा amdgpu_device *adev);
#पूर्ण_अगर
