<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CXL Flash Device Driver
 *
 * Written by: Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *             Uma Krishnan <ukrishn@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2018 IBM Corporation
 */

#अगर_अघोषित _CXLFLASH_BACKEND_H
#घोषणा _CXLFLASH_BACKEND_H

बाह्य स्थिर काष्ठा cxlflash_backend_ops cxlflash_cxl_ops;
बाह्य स्थिर काष्ठा cxlflash_backend_ops cxlflash_ocxl_ops;

काष्ठा cxlflash_backend_ops अणु
	काष्ठा module *module;
	व्योम __iomem * (*psa_map)(व्योम *ctx_cookie);
	व्योम (*psa_unmap)(व्योम __iomem *addr);
	पूर्णांक (*process_element)(व्योम *ctx_cookie);
	पूर्णांक (*map_afu_irq)(व्योम *ctx_cookie, पूर्णांक num, irq_handler_t handler,
			   व्योम *cookie, अक्षर *name);
	व्योम (*unmap_afu_irq)(व्योम *ctx_cookie, पूर्णांक num, व्योम *cookie);
	u64 (*get_irq_objhndl)(व्योम *ctx_cookie, पूर्णांक irq);
	पूर्णांक (*start_context)(व्योम *ctx_cookie);
	पूर्णांक (*stop_context)(व्योम *ctx_cookie);
	पूर्णांक (*afu_reset)(व्योम *ctx_cookie);
	व्योम (*set_master)(व्योम *ctx_cookie);
	व्योम * (*get_context)(काष्ठा pci_dev *dev, व्योम *afu_cookie);
	व्योम * (*dev_context_init)(काष्ठा pci_dev *dev, व्योम *afu_cookie);
	पूर्णांक (*release_context)(व्योम *ctx_cookie);
	व्योम (*perst_reloads_same_image)(व्योम *afu_cookie, bool image);
	sमाप_प्रकार (*पढ़ो_adapter_vpd)(काष्ठा pci_dev *dev, व्योम *buf,
				    माप_प्रकार count);
	पूर्णांक (*allocate_afu_irqs)(व्योम *ctx_cookie, पूर्णांक num);
	व्योम (*मुक्त_afu_irqs)(व्योम *ctx_cookie);
	व्योम * (*create_afu)(काष्ठा pci_dev *dev);
	व्योम (*destroy_afu)(व्योम *afu_cookie);
	काष्ठा file * (*get_fd)(व्योम *ctx_cookie, काष्ठा file_operations *fops,
				पूर्णांक *fd);
	व्योम * (*fops_get_context)(काष्ठा file *file);
	पूर्णांक (*start_work)(व्योम *ctx_cookie, u64 irqs);
	पूर्णांक (*fd_mmap)(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vm);
	पूर्णांक (*fd_release)(काष्ठा inode *inode, काष्ठा file *file);
पूर्ण;

#पूर्ण_अगर /* _CXLFLASH_BACKEND_H */
