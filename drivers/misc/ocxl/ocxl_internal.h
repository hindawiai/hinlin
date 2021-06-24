<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
// Copyright 2017 IBM Corp.
#अगर_अघोषित _OCXL_INTERNAL_H_
#घोषणा _OCXL_INTERNAL_H_

#समावेश <linux/pci.h>
#समावेश <linux/cdev.h>
#समावेश <linux/list.h>
#समावेश <misc/ocxl.h>

#घोषणा MAX_IRQ_PER_LINK	2000
#घोषणा MAX_IRQ_PER_CONTEXT	MAX_IRQ_PER_LINK

बाह्य काष्ठा pci_driver ocxl_pci_driver;

काष्ठा ocxl_fn अणु
	काष्ठा device dev;
	पूर्णांक bar_used[3];
	काष्ठा ocxl_fn_config config;
	काष्ठा list_head afu_list;
	पूर्णांक pasid_base;
	पूर्णांक actag_base;
	पूर्णांक actag_enabled;
	पूर्णांक actag_supported;
	काष्ठा list_head pasid_list;
	काष्ठा list_head actag_list;
	व्योम *link;
पूर्ण;

काष्ठा ocxl_file_info अणु
	काष्ठा ocxl_afu *afu;
	काष्ठा device dev;
	काष्ठा cdev cdev;
	काष्ठा bin_attribute attr_global_mmio;
पूर्ण;

काष्ठा ocxl_afu अणु
	काष्ठा kref kref;
	काष्ठा ocxl_fn *fn;
	काष्ठा list_head list;
	काष्ठा ocxl_afu_config config;
	पूर्णांक pasid_base;
	पूर्णांक pasid_count; /* खोलोed contexts */
	पूर्णांक pasid_max; /* maximum number of contexts */
	पूर्णांक actag_base;
	पूर्णांक actag_enabled;
	काष्ठा mutex contexts_lock;
	काष्ठा idr contexts_idr;
	काष्ठा mutex afu_control_lock;
	u64 global_mmio_start;
	u64 irq_base_offset;
	व्योम __iomem *global_mmio_ptr;
	u64 pp_mmio_start;
	व्योम *निजी;
पूर्ण;

क्रमागत ocxl_context_status अणु
	CLOSED,
	OPENED,
	ATTACHED,
पूर्ण;

// Contains metadata about a translation fault
काष्ठा ocxl_xsl_error अणु
	u64 addr; // The address that triggered the fault
	u64 dsisr; // the value of the dsisr रेजिस्टर
	u64 count; // The number of बार this fault has been triggered
पूर्ण;

काष्ठा ocxl_context अणु
	काष्ठा ocxl_afu *afu;
	पूर्णांक pasid;
	काष्ठा mutex status_mutex;
	क्रमागत ocxl_context_status status;
	काष्ठा address_space *mapping;
	काष्ठा mutex mapping_lock;
	रुको_queue_head_t events_wq;
	काष्ठा mutex xsl_error_lock;
	काष्ठा ocxl_xsl_error xsl_error;
	काष्ठा mutex irq_lock;
	काष्ठा idr irq_idr;
	u16 tidr; // Thपढ़ो ID used क्रम P9 रुको implementation
पूर्ण;

काष्ठा ocxl_process_element अणु
	__be64 config_state;
	__be32 pasid;
	__be16 bdf;
	__be16 reserved1;
	__be32 reserved2[9];
	__be32 lpid;
	__be32 tid;
	__be32 pid;
	__be32 reserved3[10];
	__be64 amr;
	__be32 reserved4[3];
	__be32 software_state;
पूर्ण;

पूर्णांक ocxl_create_cdev(काष्ठा ocxl_afu *afu);
व्योम ocxl_destroy_cdev(काष्ठा ocxl_afu *afu);
पूर्णांक ocxl_file_रेजिस्टर_afu(काष्ठा ocxl_afu *afu);
व्योम ocxl_file_unरेजिस्टर_afu(काष्ठा ocxl_afu *afu);

पूर्णांक ocxl_file_init(व्योम);
व्योम ocxl_file_निकास(व्योम);

पूर्णांक ocxl_pasid_afu_alloc(काष्ठा ocxl_fn *fn, u32 size);
व्योम ocxl_pasid_afu_मुक्त(काष्ठा ocxl_fn *fn, u32 start, u32 size);
पूर्णांक ocxl_actag_afu_alloc(काष्ठा ocxl_fn *fn, u32 size);
व्योम ocxl_actag_afu_मुक्त(काष्ठा ocxl_fn *fn, u32 start, u32 size);

/*
 * Get the max PASID value that can be used by the function
 */
पूर्णांक ocxl_config_get_pasid_info(काष्ठा pci_dev *dev, पूर्णांक *count);

/*
 * Control whether the FPGA is reloaded on a link reset
 */
पूर्णांक ocxl_config_get_reset_reload(काष्ठा pci_dev *dev, पूर्णांक *val);
पूर्णांक ocxl_config_set_reset_reload(काष्ठा pci_dev *dev, पूर्णांक val);

/*
 * Check अगर an AFU index is valid क्रम the given function.
 *
 * AFU indexes can be sparse, so a driver should check all indexes up
 * to the maximum found in the function description
 */
पूर्णांक ocxl_config_check_afu_index(काष्ठा pci_dev *dev,
				काष्ठा ocxl_fn_config *fn, पूर्णांक afu_idx);

/**
 * ocxl_link_update_pe() - Update values within a Process Element
 * @link_handle: the link handle associated with the process element
 * @pasid: the PASID क्रम the AFU context
 * @tid: the new thपढ़ो id क्रम the process element
 *
 * Returns 0 on success
 */
पूर्णांक ocxl_link_update_pe(व्योम *link_handle, पूर्णांक pasid, __u16 tid);

पूर्णांक ocxl_context_mmap(काष्ठा ocxl_context *ctx,
			काष्ठा vm_area_काष्ठा *vma);
व्योम ocxl_context_detach_all(काष्ठा ocxl_afu *afu);

पूर्णांक ocxl_sysfs_रेजिस्टर_afu(काष्ठा ocxl_file_info *info);
व्योम ocxl_sysfs_unरेजिस्टर_afu(काष्ठा ocxl_file_info *info);

पूर्णांक ocxl_irq_offset_to_id(काष्ठा ocxl_context *ctx, u64 offset);
u64 ocxl_irq_id_to_offset(काष्ठा ocxl_context *ctx, पूर्णांक irq_id);
व्योम ocxl_afu_irq_मुक्त_all(काष्ठा ocxl_context *ctx);

#पूर्ण_अगर /* _OCXL_INTERNAL_H_ */
