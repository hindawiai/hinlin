<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 */

#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/irqbypass.h>
#समावेश <linux/types.h>
#समावेश <linux/uuid.h>
#समावेश <linux/notअगरier.h>

#अगर_अघोषित VFIO_PCI_PRIVATE_H
#घोषणा VFIO_PCI_PRIVATE_H

#घोषणा VFIO_PCI_OFFSET_SHIFT   40

#घोषणा VFIO_PCI_OFFSET_TO_INDEX(off)	(off >> VFIO_PCI_OFFSET_SHIFT)
#घोषणा VFIO_PCI_INDEX_TO_OFFSET(index)	((u64)(index) << VFIO_PCI_OFFSET_SHIFT)
#घोषणा VFIO_PCI_OFFSET_MASK	(((u64)(1) << VFIO_PCI_OFFSET_SHIFT) - 1)

/* Special capability IDs predefined access */
#घोषणा PCI_CAP_ID_INVALID		0xFF	/* शेष raw access */
#घोषणा PCI_CAP_ID_INVALID_VIRT		0xFE	/* शेष virt access */

/* Cap maximum number of ioeventfds per device (arbitrary) */
#घोषणा VFIO_PCI_IOEVENTFD_MAX		1000

काष्ठा vfio_pci_ioeventfd अणु
	काष्ठा list_head	next;
	काष्ठा vfio_pci_device	*vdev;
	काष्ठा virqfd		*virqfd;
	व्योम __iomem		*addr;
	uपूर्णांक64_t		data;
	loff_t			pos;
	पूर्णांक			bar;
	पूर्णांक			count;
	bool			test_mem;
पूर्ण;

काष्ठा vfio_pci_irq_ctx अणु
	काष्ठा eventfd_ctx	*trigger;
	काष्ठा virqfd		*unmask;
	काष्ठा virqfd		*mask;
	अक्षर			*name;
	bool			masked;
	काष्ठा irq_bypass_producer	producer;
पूर्ण;

काष्ठा vfio_pci_device;
काष्ठा vfio_pci_region;

काष्ठा vfio_pci_regops अणु
	माप_प्रकार	(*rw)(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
		      माप_प्रकार count, loff_t *ppos, bool isग_लिखो);
	व्योम	(*release)(काष्ठा vfio_pci_device *vdev,
			   काष्ठा vfio_pci_region *region);
	पूर्णांक	(*mmap)(काष्ठा vfio_pci_device *vdev,
			काष्ठा vfio_pci_region *region,
			काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक	(*add_capability)(काष्ठा vfio_pci_device *vdev,
				  काष्ठा vfio_pci_region *region,
				  काष्ठा vfio_info_cap *caps);
पूर्ण;

काष्ठा vfio_pci_region अणु
	u32				type;
	u32				subtype;
	स्थिर काष्ठा vfio_pci_regops	*ops;
	व्योम				*data;
	माप_प्रकार				size;
	u32				flags;
पूर्ण;

काष्ठा vfio_pci_dummy_resource अणु
	काष्ठा resource		resource;
	पूर्णांक			index;
	काष्ठा list_head	res_next;
पूर्ण;

काष्ठा vfio_pci_reflck अणु
	काष्ठा kref		kref;
	काष्ठा mutex		lock;
पूर्ण;

काष्ठा vfio_pci_vf_token अणु
	काष्ठा mutex		lock;
	uuid_t			uuid;
	पूर्णांक			users;
पूर्ण;

काष्ठा vfio_pci_mmap_vma अणु
	काष्ठा vm_area_काष्ठा	*vma;
	काष्ठा list_head	vma_next;
पूर्ण;

काष्ठा vfio_pci_device अणु
	काष्ठा vfio_device	vdev;
	काष्ठा pci_dev		*pdev;
	व्योम __iomem		*barmap[PCI_STD_NUM_BARS];
	bool			bar_mmap_supported[PCI_STD_NUM_BARS];
	u8			*pci_config_map;
	u8			*vconfig;
	काष्ठा perm_bits	*msi_perm;
	spinlock_t		irqlock;
	काष्ठा mutex		igate;
	काष्ठा vfio_pci_irq_ctx	*ctx;
	पूर्णांक			num_ctx;
	पूर्णांक			irq_type;
	पूर्णांक			num_regions;
	काष्ठा vfio_pci_region	*region;
	u8			msi_qmax;
	u8			msix_bar;
	u16			msix_size;
	u32			msix_offset;
	u32			rbar[7];
	bool			pci_2_3;
	bool			virq_disabled;
	bool			reset_works;
	bool			extended_caps;
	bool			bardirty;
	bool			has_vga;
	bool			needs_reset;
	bool			noपूर्णांकx;
	bool			needs_pm_restore;
	काष्ठा pci_saved_state	*pci_saved_state;
	काष्ठा pci_saved_state	*pm_save;
	काष्ठा vfio_pci_reflck	*reflck;
	पूर्णांक			refcnt;
	पूर्णांक			ioeventfds_nr;
	काष्ठा eventfd_ctx	*err_trigger;
	काष्ठा eventfd_ctx	*req_trigger;
	काष्ठा list_head	dummy_resources_list;
	काष्ठा mutex		ioeventfds_lock;
	काष्ठा list_head	ioeventfds_list;
	काष्ठा vfio_pci_vf_token	*vf_token;
	काष्ठा notअगरier_block	nb;
	काष्ठा mutex		vma_lock;
	काष्ठा list_head	vma_list;
	काष्ठा rw_semaphore	memory_lock;
पूर्ण;

#घोषणा is_पूर्णांकx(vdev) (vdev->irq_type == VFIO_PCI_INTX_IRQ_INDEX)
#घोषणा is_msi(vdev) (vdev->irq_type == VFIO_PCI_MSI_IRQ_INDEX)
#घोषणा is_msix(vdev) (vdev->irq_type == VFIO_PCI_MSIX_IRQ_INDEX)
#घोषणा is_irq_none(vdev) (!(is_पूर्णांकx(vdev) || is_msi(vdev) || is_msix(vdev)))
#घोषणा irq_is(vdev, type) (vdev->irq_type == type)

बाह्य व्योम vfio_pci_पूर्णांकx_mask(काष्ठा vfio_pci_device *vdev);
बाह्य व्योम vfio_pci_पूर्णांकx_unmask(काष्ठा vfio_pci_device *vdev);

बाह्य पूर्णांक vfio_pci_set_irqs_ioctl(काष्ठा vfio_pci_device *vdev,
				   uपूर्णांक32_t flags, अचिन्हित index,
				   अचिन्हित start, अचिन्हित count, व्योम *data);

बाह्य sमाप_प्रकार vfio_pci_config_rw(काष्ठा vfio_pci_device *vdev,
				  अक्षर __user *buf, माप_प्रकार count,
				  loff_t *ppos, bool isग_लिखो);

बाह्य sमाप_प्रकार vfio_pci_bar_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos, bool isग_लिखो);

बाह्य sमाप_प्रकार vfio_pci_vga_rw(काष्ठा vfio_pci_device *vdev, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos, bool isग_लिखो);

बाह्य दीर्घ vfio_pci_ioeventfd(काष्ठा vfio_pci_device *vdev, loff_t offset,
			       uपूर्णांक64_t data, पूर्णांक count, पूर्णांक fd);

बाह्य पूर्णांक vfio_pci_init_perm_bits(व्योम);
बाह्य व्योम vfio_pci_uninit_perm_bits(व्योम);

बाह्य पूर्णांक vfio_config_init(काष्ठा vfio_pci_device *vdev);
बाह्य व्योम vfio_config_मुक्त(काष्ठा vfio_pci_device *vdev);

बाह्य पूर्णांक vfio_pci_रेजिस्टर_dev_region(काष्ठा vfio_pci_device *vdev,
					अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक subtype,
					स्थिर काष्ठा vfio_pci_regops *ops,
					माप_प्रकार size, u32 flags, व्योम *data);

बाह्य पूर्णांक vfio_pci_set_घातer_state(काष्ठा vfio_pci_device *vdev,
				    pci_घातer_t state);

बाह्य bool __vfio_pci_memory_enabled(काष्ठा vfio_pci_device *vdev);
बाह्य व्योम vfio_pci_zap_and_करोwn_ग_लिखो_memory_lock(काष्ठा vfio_pci_device
						    *vdev);
बाह्य u16 vfio_pci_memory_lock_and_enable(काष्ठा vfio_pci_device *vdev);
बाह्य व्योम vfio_pci_memory_unlock_and_restore(काष्ठा vfio_pci_device *vdev,
					       u16 cmd);

#अगर_घोषित CONFIG_VFIO_PCI_IGD
बाह्य पूर्णांक vfio_pci_igd_init(काष्ठा vfio_pci_device *vdev);
#अन्यथा
अटल अंतरभूत पूर्णांक vfio_pci_igd_init(काष्ठा vfio_pci_device *vdev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_S390
बाह्य पूर्णांक vfio_pci_info_zdev_add_caps(काष्ठा vfio_pci_device *vdev,
				       काष्ठा vfio_info_cap *caps);
#अन्यथा
अटल अंतरभूत पूर्णांक vfio_pci_info_zdev_add_caps(काष्ठा vfio_pci_device *vdev,
					      काष्ठा vfio_info_cap *caps)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* VFIO_PCI_PRIVATE_H */
