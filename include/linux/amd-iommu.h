<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007-2010 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <joerg.roedel@amd.com>
 *         Leo Duran <leo.duran@amd.com>
 */

#अगर_अघोषित _ASM_X86_AMD_IOMMU_H
#घोषणा _ASM_X86_AMD_IOMMU_H

#समावेश <linux/types.h>

काष्ठा amd_iommu;

/*
 * This is मुख्यly used to communicate inक्रमmation back-and-क्रमth
 * between SVM and IOMMU क्रम setting up and tearing करोwn posted
 * पूर्णांकerrupt
 */
काष्ठा amd_iommu_pi_data अणु
	u32 ga_tag;
	u32 prev_ga_tag;
	u64 base;
	bool is_guest_mode;
	काष्ठा vcpu_data *vcpu_data;
	व्योम *ir_data;
पूर्ण;

#अगर_घोषित CONFIG_AMD_IOMMU

काष्ठा task_काष्ठा;
काष्ठा pci_dev;

बाह्य पूर्णांक amd_iommu_detect(व्योम);
बाह्य पूर्णांक amd_iommu_init_hardware(व्योम);

/**
 * amd_iommu_init_device() - Init device क्रम use with IOMMUv2 driver
 * @pdev: The PCI device to initialize
 * @pasids: Number of PASIDs to support क्रम this device
 *
 * This function करोes all setup क्रम the device pdev so that it can be
 * used with IOMMUv2.
 * Returns 0 on success or negative value on error.
 */
बाह्य पूर्णांक amd_iommu_init_device(काष्ठा pci_dev *pdev, पूर्णांक pasids);

/**
 * amd_iommu_मुक्त_device() - Free all IOMMUv2 related device resources
 *			     and disable IOMMUv2 usage क्रम this device
 * @pdev: The PCI device to disable IOMMUv2 usage क्रम'
 */
बाह्य व्योम amd_iommu_मुक्त_device(काष्ठा pci_dev *pdev);

/**
 * amd_iommu_bind_pasid() - Bind a given task to a PASID on a device
 * @pdev: The PCI device to bind the task to
 * @pasid: The PASID on the device the task should be bound to
 * @task: the task to bind
 *
 * The function वापसs 0 on success or a negative value on error.
 */
बाह्य पूर्णांक amd_iommu_bind_pasid(काष्ठा pci_dev *pdev, u32 pasid,
				काष्ठा task_काष्ठा *task);

/**
 * amd_iommu_unbind_pasid() - Unbind a PASID from its task on
 *			      a device
 * @pdev: The device of the PASID
 * @pasid: The PASID to unbind
 *
 * When this function वापसs the device is no दीर्घer using the PASID
 * and the PASID is no दीर्घer bound to its task.
 */
बाह्य व्योम amd_iommu_unbind_pasid(काष्ठा pci_dev *pdev, u32 pasid);

/**
 * amd_iommu_set_invalid_ppr_cb() - Register a call-back क्रम failed
 *				    PRI requests
 * @pdev: The PCI device the call-back should be रेजिस्टरed क्रम
 * @cb: The call-back function
 *
 * The IOMMUv2 driver invokes this call-back when it is unable to
 * successfully handle a PRI request. The device driver can then decide
 * which PRI response the device should see. Possible वापस values क्रम
 * the call-back are:
 *
 * - AMD_IOMMU_INV_PRI_RSP_SUCCESS - Send SUCCESS back to the device
 * - AMD_IOMMU_INV_PRI_RSP_INVALID - Send INVALID back to the device
 * - AMD_IOMMU_INV_PRI_RSP_FAIL    - Send Failure back to the device,
 *				     the device is required to disable
 *				     PRI when it receives this response
 *
 * The function वापसs 0 on success or negative value on error.
 */
#घोषणा AMD_IOMMU_INV_PRI_RSP_SUCCESS	0
#घोषणा AMD_IOMMU_INV_PRI_RSP_INVALID	1
#घोषणा AMD_IOMMU_INV_PRI_RSP_FAIL	2

प्रकार पूर्णांक (*amd_iommu_invalid_ppr_cb)(काष्ठा pci_dev *pdev,
					u32 pasid,
					अचिन्हित दीर्घ address,
					u16);

बाह्य पूर्णांक amd_iommu_set_invalid_ppr_cb(काष्ठा pci_dev *pdev,
					amd_iommu_invalid_ppr_cb cb);

#घोषणा PPR_FAULT_EXEC	(1 << 1)
#घोषणा PPR_FAULT_READ  (1 << 2)
#घोषणा PPR_FAULT_WRITE (1 << 5)
#घोषणा PPR_FAULT_USER  (1 << 6)
#घोषणा PPR_FAULT_RSVD  (1 << 7)
#घोषणा PPR_FAULT_GN    (1 << 8)

/**
 * amd_iommu_device_info() - Get inक्रमmation about IOMMUv2 support of a
 *			     PCI device
 * @pdev: PCI device to query inक्रमmation from
 * @info: A poपूर्णांकer to an amd_iommu_device_info काष्ठाure which will contain
 *	  the inक्रमmation about the PCI device
 *
 * Returns 0 on success, negative value on error
 */

#घोषणा AMD_IOMMU_DEVICE_FLAG_ATS_SUP     0x1    /* ATS feature supported */
#घोषणा AMD_IOMMU_DEVICE_FLAG_PRI_SUP     0x2    /* PRI feature supported */
#घोषणा AMD_IOMMU_DEVICE_FLAG_PASID_SUP   0x4    /* PASID context supported */
#घोषणा AMD_IOMMU_DEVICE_FLAG_EXEC_SUP    0x8    /* Device may request execution
						    on memory pages */
#घोषणा AMD_IOMMU_DEVICE_FLAG_PRIV_SUP   0x10    /* Device may request
						    super-user privileges */

काष्ठा amd_iommu_device_info अणु
	पूर्णांक max_pasids;
	u32 flags;
पूर्ण;

बाह्य पूर्णांक amd_iommu_device_info(काष्ठा pci_dev *pdev,
				 काष्ठा amd_iommu_device_info *info);

/**
 * amd_iommu_set_invalidate_ctx_cb() - Register a call-back क्रम invalidating
 *				       a pasid context. This call-back is
 *				       invoked when the IOMMUv2 driver needs to
 *				       invalidate a PASID context, क्रम example
 *				       because the task that is bound to that
 *				       context is about to निकास.
 *
 * @pdev: The PCI device the call-back should be रेजिस्टरed क्रम
 * @cb: The call-back function
 */

प्रकार व्योम (*amd_iommu_invalidate_ctx)(काष्ठा pci_dev *pdev, u32 pasid);

बाह्य पूर्णांक amd_iommu_set_invalidate_ctx_cb(काष्ठा pci_dev *pdev,
					   amd_iommu_invalidate_ctx cb);
#अन्यथा /* CONFIG_AMD_IOMMU */

अटल अंतरभूत पूर्णांक amd_iommu_detect(व्योम) अणु वापस -ENODEV; पूर्ण

#पूर्ण_अगर /* CONFIG_AMD_IOMMU */

#अगर defined(CONFIG_AMD_IOMMU) && defined(CONFIG_IRQ_REMAP)

/* IOMMU AVIC Function */
बाह्य पूर्णांक amd_iommu_रेजिस्टर_ga_log_notअगरier(पूर्णांक (*notअगरier)(u32));

बाह्य पूर्णांक
amd_iommu_update_ga(पूर्णांक cpu, bool is_run, व्योम *data);

बाह्य पूर्णांक amd_iommu_activate_guest_mode(व्योम *data);
बाह्य पूर्णांक amd_iommu_deactivate_guest_mode(व्योम *data);

#अन्यथा /* defined(CONFIG_AMD_IOMMU) && defined(CONFIG_IRQ_REMAP) */

अटल अंतरभूत पूर्णांक
amd_iommu_रेजिस्टर_ga_log_notअगरier(पूर्णांक (*notअगरier)(u32))
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
amd_iommu_update_ga(पूर्णांक cpu, bool is_run, व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक amd_iommu_activate_guest_mode(व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक amd_iommu_deactivate_guest_mode(व्योम *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_AMD_IOMMU) && defined(CONFIG_IRQ_REMAP) */

पूर्णांक amd_iommu_get_num_iommus(व्योम);
bool amd_iommu_pc_supported(व्योम);
u8 amd_iommu_pc_get_max_banks(अचिन्हित पूर्णांक idx);
u8 amd_iommu_pc_get_max_counters(अचिन्हित पूर्णांक idx);
पूर्णांक amd_iommu_pc_set_reg(काष्ठा amd_iommu *iommu, u8 bank, u8 cntr, u8 fxn,
		u64 *value);
पूर्णांक amd_iommu_pc_get_reg(काष्ठा amd_iommu *iommu, u8 bank, u8 cntr, u8 fxn,
		u64 *value);
काष्ठा amd_iommu *get_amd_iommu(अचिन्हित पूर्णांक idx);

#पूर्ण_अगर /* _ASM_X86_AMD_IOMMU_H */
