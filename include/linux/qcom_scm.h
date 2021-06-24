<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2010-2015, 2018-2019 The Linux Foundation. All rights reserved.
 * Copyright (C) 2015 Linaro Ltd.
 */
#अगर_अघोषित __QCOM_SCM_H
#घोषणा __QCOM_SCM_H

#समावेश <linux/err.h>
#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>

#घोषणा QCOM_SCM_VERSION(major, minor)	(((major) << 16) | ((minor) & 0xFF))
#घोषणा QCOM_SCM_CPU_PWR_DOWN_L2_ON	0x0
#घोषणा QCOM_SCM_CPU_PWR_DOWN_L2_OFF	0x1
#घोषणा QCOM_SCM_HDCP_MAX_REQ_CNT	5

काष्ठा qcom_scm_hdcp_req अणु
	u32 addr;
	u32 val;
पूर्ण;

काष्ठा qcom_scm_vmperm अणु
	पूर्णांक vmid;
	पूर्णांक perm;
पूर्ण;

क्रमागत qcom_scm_ocmem_client अणु
	QCOM_SCM_OCMEM_UNUSED_ID = 0x0,
	QCOM_SCM_OCMEM_GRAPHICS_ID,
	QCOM_SCM_OCMEM_VIDEO_ID,
	QCOM_SCM_OCMEM_LP_AUDIO_ID,
	QCOM_SCM_OCMEM_SENSORS_ID,
	QCOM_SCM_OCMEM_OTHER_OS_ID,
	QCOM_SCM_OCMEM_DEBUG_ID,
पूर्ण;

क्रमागत qcom_scm_sec_dev_id अणु
	QCOM_SCM_MDSS_DEV_ID    = 1,
	QCOM_SCM_OCMEM_DEV_ID   = 5,
	QCOM_SCM_PCIE0_DEV_ID   = 11,
	QCOM_SCM_PCIE1_DEV_ID   = 12,
	QCOM_SCM_GFX_DEV_ID     = 18,
	QCOM_SCM_UFS_DEV_ID     = 19,
	QCOM_SCM_ICE_DEV_ID     = 20,
पूर्ण;

क्रमागत qcom_scm_ice_cipher अणु
	QCOM_SCM_ICE_CIPHER_AES_128_XTS = 0,
	QCOM_SCM_ICE_CIPHER_AES_128_CBC = 1,
	QCOM_SCM_ICE_CIPHER_AES_256_XTS = 3,
	QCOM_SCM_ICE_CIPHER_AES_256_CBC = 4,
पूर्ण;

#घोषणा QCOM_SCM_VMID_HLOS       0x3
#घोषणा QCOM_SCM_VMID_MSS_MSA    0xF
#घोषणा QCOM_SCM_VMID_WLAN       0x18
#घोषणा QCOM_SCM_VMID_WLAN_CE    0x19
#घोषणा QCOM_SCM_PERM_READ       0x4
#घोषणा QCOM_SCM_PERM_WRITE      0x2
#घोषणा QCOM_SCM_PERM_EXEC       0x1
#घोषणा QCOM_SCM_PERM_RW (QCOM_SCM_PERM_READ | QCOM_SCM_PERM_WRITE)
#घोषणा QCOM_SCM_PERM_RWX (QCOM_SCM_PERM_RW | QCOM_SCM_PERM_EXEC)

#अगर IS_ENABLED(CONFIG_QCOM_SCM)
बाह्य bool qcom_scm_is_available(व्योम);

बाह्य पूर्णांक qcom_scm_set_cold_boot_addr(व्योम *entry, स्थिर cpumask_t *cpus);
बाह्य पूर्णांक qcom_scm_set_warm_boot_addr(व्योम *entry, स्थिर cpumask_t *cpus);
बाह्य व्योम qcom_scm_cpu_घातer_करोwn(u32 flags);
बाह्य पूर्णांक qcom_scm_set_remote_state(u32 state, u32 id);

बाह्य पूर्णांक qcom_scm_pas_init_image(u32 peripheral, स्थिर व्योम *metadata,
				   माप_प्रकार size);
बाह्य पूर्णांक qcom_scm_pas_mem_setup(u32 peripheral, phys_addr_t addr,
				  phys_addr_t size);
बाह्य पूर्णांक qcom_scm_pas_auth_and_reset(u32 peripheral);
बाह्य पूर्णांक qcom_scm_pas_shutकरोwn(u32 peripheral);
बाह्य bool qcom_scm_pas_supported(u32 peripheral);

बाह्य पूर्णांक qcom_scm_io_पढ़ोl(phys_addr_t addr, अचिन्हित पूर्णांक *val);
बाह्य पूर्णांक qcom_scm_io_ग_लिखोl(phys_addr_t addr, अचिन्हित पूर्णांक val);

बाह्य bool qcom_scm_restore_sec_cfg_available(व्योम);
बाह्य पूर्णांक qcom_scm_restore_sec_cfg(u32 device_id, u32 spare);
बाह्य पूर्णांक qcom_scm_iommu_secure_ptbl_size(u32 spare, माप_प्रकार *size);
बाह्य पूर्णांक qcom_scm_iommu_secure_ptbl_init(u64 addr, u32 size, u32 spare);
बाह्य पूर्णांक qcom_scm_mem_protect_video_var(u32 cp_start, u32 cp_size,
					  u32 cp_nonpixel_start,
					  u32 cp_nonpixel_size);
बाह्य पूर्णांक qcom_scm_assign_mem(phys_addr_t mem_addr, माप_प्रकार mem_sz,
			       अचिन्हित पूर्णांक *src,
			       स्थिर काष्ठा qcom_scm_vmperm *newvm,
			       अचिन्हित पूर्णांक dest_cnt);

बाह्य bool qcom_scm_ocmem_lock_available(व्योम);
बाह्य पूर्णांक qcom_scm_ocmem_lock(क्रमागत qcom_scm_ocmem_client id, u32 offset,
			       u32 size, u32 mode);
बाह्य पूर्णांक qcom_scm_ocmem_unlock(क्रमागत qcom_scm_ocmem_client id, u32 offset,
				 u32 size);

बाह्य bool qcom_scm_ice_available(व्योम);
बाह्य पूर्णांक qcom_scm_ice_invalidate_key(u32 index);
बाह्य पूर्णांक qcom_scm_ice_set_key(u32 index, स्थिर u8 *key, u32 key_size,
				क्रमागत qcom_scm_ice_cipher cipher,
				u32 data_unit_size);

बाह्य bool qcom_scm_hdcp_available(व्योम);
बाह्य पूर्णांक qcom_scm_hdcp_req(काष्ठा qcom_scm_hdcp_req *req, u32 req_cnt,
			     u32 *resp);

बाह्य पूर्णांक qcom_scm_qsmmu500_रुको_safe_toggle(bool en);
#अन्यथा

#समावेश <linux/त्रुटिसं.स>

अटल अंतरभूत bool qcom_scm_is_available(व्योम) अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक qcom_scm_set_cold_boot_addr(व्योम *entry,
		स्थिर cpumask_t *cpus) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_set_warm_boot_addr(व्योम *entry,
		स्थिर cpumask_t *cpus) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम qcom_scm_cpu_घातer_करोwn(u32 flags) अणुपूर्ण
अटल अंतरभूत u32 qcom_scm_set_remote_state(u32 state,u32 id)
		अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक qcom_scm_pas_init_image(u32 peripheral, स्थिर व्योम *metadata,
		माप_प्रकार size) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_pas_mem_setup(u32 peripheral, phys_addr_t addr,
		phys_addr_t size) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_pas_auth_and_reset(u32 peripheral)
		अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_pas_shutकरोwn(u32 peripheral) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत bool qcom_scm_pas_supported(u32 peripheral) अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक qcom_scm_io_पढ़ोl(phys_addr_t addr, अचिन्हित पूर्णांक *val)
		अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_io_ग_लिखोl(phys_addr_t addr, अचिन्हित पूर्णांक val)
		अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत bool qcom_scm_restore_sec_cfg_available(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_restore_sec_cfg(u32 device_id, u32 spare)
		अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_iommu_secure_ptbl_size(u32 spare, माप_प्रकार *size)
		अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_iommu_secure_ptbl_init(u64 addr, u32 size, u32 spare)
		अणु वापस -ENODEV; पूर्ण
बाह्य अंतरभूत पूर्णांक qcom_scm_mem_protect_video_var(u32 cp_start, u32 cp_size,
						 u32 cp_nonpixel_start,
						 u32 cp_nonpixel_size)
		अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_assign_mem(phys_addr_t mem_addr, माप_प्रकार mem_sz,
		अचिन्हित पूर्णांक *src, स्थिर काष्ठा qcom_scm_vmperm *newvm,
		अचिन्हित पूर्णांक dest_cnt) अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत bool qcom_scm_ocmem_lock_available(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_ocmem_lock(क्रमागत qcom_scm_ocmem_client id, u32 offset,
		u32 size, u32 mode) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_ocmem_unlock(क्रमागत qcom_scm_ocmem_client id,
		u32 offset, u32 size) अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत bool qcom_scm_ice_available(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_ice_invalidate_key(u32 index) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_ice_set_key(u32 index, स्थिर u8 *key, u32 key_size,
				       क्रमागत qcom_scm_ice_cipher cipher,
				       u32 data_unit_size) अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत bool qcom_scm_hdcp_available(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक qcom_scm_hdcp_req(काष्ठा qcom_scm_hdcp_req *req, u32 req_cnt,
		u32 *resp) अणु वापस -ENODEV; पूर्ण

अटल अंतरभूत पूर्णांक qcom_scm_qsmmu500_रुको_safe_toggle(bool en)
		अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
