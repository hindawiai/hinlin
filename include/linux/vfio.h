<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VFIO API definition
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 */
#अगर_अघोषित VFIO_H
#घोषणा VFIO_H


#समावेश <linux/iommu.h>
#समावेश <linux/mm.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/poll.h>
#समावेश <uapi/linux/vfपन.स>

काष्ठा vfio_device अणु
	काष्ठा device *dev;
	स्थिर काष्ठा vfio_device_ops *ops;
	काष्ठा vfio_group *group;

	/* Members below here are निजी, not क्रम driver use */
	refcount_t refcount;
	काष्ठा completion comp;
	काष्ठा list_head group_next;
पूर्ण;

/**
 * काष्ठा vfio_device_ops - VFIO bus driver device callbacks
 *
 * @खोलो: Called when userspace creates new file descriptor क्रम device
 * @release: Called when userspace releases file descriptor क्रम device
 * @पढ़ो: Perक्रमm पढ़ो(2) on device file descriptor
 * @ग_लिखो: Perक्रमm ग_लिखो(2) on device file descriptor
 * @ioctl: Perक्रमm ioctl(2) on device file descriptor, supporting VFIO_DEVICE_*
 *         operations करोcumented below
 * @mmap: Perक्रमm mmap(2) on a region of the device file descriptor
 * @request: Request क्रम the bus driver to release the device
 * @match: Optional device name match callback (वापस: 0 क्रम no-match, >0 क्रम
 *         match, -त्रुटि_सं क्रम पात (ex. match with insufficient or incorrect
 *         additional args)
 */
काष्ठा vfio_device_ops अणु
	अक्षर	*name;
	पूर्णांक	(*खोलो)(काष्ठा vfio_device *vdev);
	व्योम	(*release)(काष्ठा vfio_device *vdev);
	sमाप_प्रकार	(*पढ़ो)(काष्ठा vfio_device *vdev, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos);
	sमाप_प्रकार	(*ग_लिखो)(काष्ठा vfio_device *vdev, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *size);
	दीर्घ	(*ioctl)(काष्ठा vfio_device *vdev, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg);
	पूर्णांक	(*mmap)(काष्ठा vfio_device *vdev, काष्ठा vm_area_काष्ठा *vma);
	व्योम	(*request)(काष्ठा vfio_device *vdev, अचिन्हित पूर्णांक count);
	पूर्णांक	(*match)(काष्ठा vfio_device *vdev, अक्षर *buf);
पूर्ण;

बाह्य काष्ठा iommu_group *vfio_iommu_group_get(काष्ठा device *dev);
बाह्य व्योम vfio_iommu_group_put(काष्ठा iommu_group *group, काष्ठा device *dev);

व्योम vfio_init_group_dev(काष्ठा vfio_device *device, काष्ठा device *dev,
			 स्थिर काष्ठा vfio_device_ops *ops);
पूर्णांक vfio_रेजिस्टर_group_dev(काष्ठा vfio_device *device);
व्योम vfio_unरेजिस्टर_group_dev(काष्ठा vfio_device *device);
बाह्य काष्ठा vfio_device *vfio_device_get_from_dev(काष्ठा device *dev);
बाह्य व्योम vfio_device_put(काष्ठा vfio_device *device);

/* events क्रम the backend driver notअगरy callback */
क्रमागत vfio_iommu_notअगरy_type अणु
	VFIO_IOMMU_CONTAINER_CLOSE = 0,
पूर्ण;

/**
 * काष्ठा vfio_iommu_driver_ops - VFIO IOMMU driver callbacks
 */
काष्ठा vfio_iommu_driver_ops अणु
	अक्षर		*name;
	काष्ठा module	*owner;
	व्योम		*(*खोलो)(अचिन्हित दीर्घ arg);
	व्योम		(*release)(व्योम *iommu_data);
	sमाप_प्रकार		(*पढ़ो)(व्योम *iommu_data, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos);
	sमाप_प्रकार		(*ग_लिखो)(व्योम *iommu_data, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *size);
	दीर्घ		(*ioctl)(व्योम *iommu_data, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg);
	पूर्णांक		(*mmap)(व्योम *iommu_data, काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक		(*attach_group)(व्योम *iommu_data,
					काष्ठा iommu_group *group);
	व्योम		(*detach_group)(व्योम *iommu_data,
					काष्ठा iommu_group *group);
	पूर्णांक		(*pin_pages)(व्योम *iommu_data,
				     काष्ठा iommu_group *group,
				     अचिन्हित दीर्घ *user_pfn,
				     पूर्णांक npage, पूर्णांक prot,
				     अचिन्हित दीर्घ *phys_pfn);
	पूर्णांक		(*unpin_pages)(व्योम *iommu_data,
				       अचिन्हित दीर्घ *user_pfn, पूर्णांक npage);
	पूर्णांक		(*रेजिस्टर_notअगरier)(व्योम *iommu_data,
					     अचिन्हित दीर्घ *events,
					     काष्ठा notअगरier_block *nb);
	पूर्णांक		(*unरेजिस्टर_notअगरier)(व्योम *iommu_data,
					       काष्ठा notअगरier_block *nb);
	पूर्णांक		(*dma_rw)(व्योम *iommu_data, dma_addr_t user_iova,
				  व्योम *data, माप_प्रकार count, bool ग_लिखो);
	काष्ठा iommu_करोमुख्य *(*group_iommu_करोमुख्य)(व्योम *iommu_data,
						   काष्ठा iommu_group *group);
	व्योम		(*notअगरy)(व्योम *iommu_data,
				  क्रमागत vfio_iommu_notअगरy_type event);
पूर्ण;

बाह्य पूर्णांक vfio_रेजिस्टर_iommu_driver(स्थिर काष्ठा vfio_iommu_driver_ops *ops);

बाह्य व्योम vfio_unरेजिस्टर_iommu_driver(
				स्थिर काष्ठा vfio_iommu_driver_ops *ops);

/*
 * External user API
 */
बाह्य काष्ठा vfio_group *vfio_group_get_बाह्यal_user(काष्ठा file *filep);
बाह्य व्योम vfio_group_put_बाह्यal_user(काष्ठा vfio_group *group);
बाह्य काष्ठा vfio_group *vfio_group_get_बाह्यal_user_from_dev(काष्ठा device
								*dev);
बाह्य bool vfio_बाह्यal_group_match_file(काष्ठा vfio_group *group,
					   काष्ठा file *filep);
बाह्य पूर्णांक vfio_बाह्यal_user_iommu_id(काष्ठा vfio_group *group);
बाह्य दीर्घ vfio_बाह्यal_check_extension(काष्ठा vfio_group *group,
					  अचिन्हित दीर्घ arg);

#घोषणा VFIO_PIN_PAGES_MAX_ENTRIES	(PAGE_SIZE/माप(अचिन्हित दीर्घ))

बाह्य पूर्णांक vfio_pin_pages(काष्ठा device *dev, अचिन्हित दीर्घ *user_pfn,
			  पूर्णांक npage, पूर्णांक prot, अचिन्हित दीर्घ *phys_pfn);
बाह्य पूर्णांक vfio_unpin_pages(काष्ठा device *dev, अचिन्हित दीर्घ *user_pfn,
			    पूर्णांक npage);

बाह्य पूर्णांक vfio_group_pin_pages(काष्ठा vfio_group *group,
				अचिन्हित दीर्घ *user_iova_pfn, पूर्णांक npage,
				पूर्णांक prot, अचिन्हित दीर्घ *phys_pfn);
बाह्य पूर्णांक vfio_group_unpin_pages(काष्ठा vfio_group *group,
				  अचिन्हित दीर्घ *user_iova_pfn, पूर्णांक npage);

बाह्य पूर्णांक vfio_dma_rw(काष्ठा vfio_group *group, dma_addr_t user_iova,
		       व्योम *data, माप_प्रकार len, bool ग_लिखो);

बाह्य काष्ठा iommu_करोमुख्य *vfio_group_iommu_करोमुख्य(काष्ठा vfio_group *group);

/* each type has independent events */
क्रमागत vfio_notअगरy_type अणु
	VFIO_IOMMU_NOTIFY = 0,
	VFIO_GROUP_NOTIFY = 1,
पूर्ण;

/* events क्रम VFIO_IOMMU_NOTIFY */
#घोषणा VFIO_IOMMU_NOTIFY_DMA_UNMAP	BIT(0)

/* events क्रम VFIO_GROUP_NOTIFY */
#घोषणा VFIO_GROUP_NOTIFY_SET_KVM	BIT(0)

बाह्य पूर्णांक vfio_रेजिस्टर_notअगरier(काष्ठा device *dev,
				  क्रमागत vfio_notअगरy_type type,
				  अचिन्हित दीर्घ *required_events,
				  काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक vfio_unरेजिस्टर_notअगरier(काष्ठा device *dev,
				    क्रमागत vfio_notअगरy_type type,
				    काष्ठा notअगरier_block *nb);

काष्ठा kvm;
बाह्य व्योम vfio_group_set_kvm(काष्ठा vfio_group *group, काष्ठा kvm *kvm);

/*
 * Sub-module helpers
 */
काष्ठा vfio_info_cap अणु
	काष्ठा vfio_info_cap_header *buf;
	माप_प्रकार size;
पूर्ण;
बाह्य काष्ठा vfio_info_cap_header *vfio_info_cap_add(
		काष्ठा vfio_info_cap *caps, माप_प्रकार size, u16 id, u16 version);
बाह्य व्योम vfio_info_cap_shअगरt(काष्ठा vfio_info_cap *caps, माप_प्रकार offset);

बाह्य पूर्णांक vfio_info_add_capability(काष्ठा vfio_info_cap *caps,
				    काष्ठा vfio_info_cap_header *cap,
				    माप_प्रकार size);

बाह्य पूर्णांक vfio_set_irqs_validate_and_prepare(काष्ठा vfio_irq_set *hdr,
					      पूर्णांक num_irqs, पूर्णांक max_irq_type,
					      माप_प्रकार *data_size);

काष्ठा pci_dev;
#अगर IS_ENABLED(CONFIG_VFIO_SPAPR_EEH)
बाह्य व्योम vfio_spapr_pci_eeh_खोलो(काष्ठा pci_dev *pdev);
बाह्य व्योम vfio_spapr_pci_eeh_release(काष्ठा pci_dev *pdev);
बाह्य दीर्घ vfio_spapr_iommu_eeh_ioctl(काष्ठा iommu_group *group,
				       अचिन्हित पूर्णांक cmd,
				       अचिन्हित दीर्घ arg);
#अन्यथा
अटल अंतरभूत व्योम vfio_spapr_pci_eeh_खोलो(काष्ठा pci_dev *pdev)
अणु
पूर्ण

अटल अंतरभूत व्योम vfio_spapr_pci_eeh_release(काष्ठा pci_dev *pdev)
अणु
पूर्ण

अटल अंतरभूत दीर्घ vfio_spapr_iommu_eeh_ioctl(काष्ठा iommu_group *group,
					      अचिन्हित पूर्णांक cmd,
					      अचिन्हित दीर्घ arg)
अणु
	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर /* CONFIG_VFIO_SPAPR_EEH */

/*
 * IRQfd - generic
 */
काष्ठा virqfd अणु
	व्योम			*opaque;
	काष्ठा eventfd_ctx	*eventfd;
	पूर्णांक			(*handler)(व्योम *, व्योम *);
	व्योम			(*thपढ़ो)(व्योम *, व्योम *);
	व्योम			*data;
	काष्ठा work_काष्ठा	inject;
	रुको_queue_entry_t		रुको;
	poll_table		pt;
	काष्ठा work_काष्ठा	shutकरोwn;
	काष्ठा virqfd		**pvirqfd;
पूर्ण;

बाह्य पूर्णांक vfio_virqfd_enable(व्योम *opaque,
			      पूर्णांक (*handler)(व्योम *, व्योम *),
			      व्योम (*thपढ़ो)(व्योम *, व्योम *),
			      व्योम *data, काष्ठा virqfd **pvirqfd, पूर्णांक fd);
बाह्य व्योम vfio_virqfd_disable(काष्ठा virqfd **pvirqfd);

#पूर्ण_अगर /* VFIO_H */
