<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Mediated device definition
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 */

#अगर_अघोषित MDEV_H
#घोषणा MDEV_H

काष्ठा mdev_type;

काष्ठा mdev_device अणु
	काष्ठा device dev;
	guid_t uuid;
	व्योम *driver_data;
	काष्ठा list_head next;
	काष्ठा mdev_type *type;
	काष्ठा device *iommu_device;
	bool active;
पूर्ण;

अटल अंतरभूत काष्ठा mdev_device *to_mdev_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा mdev_device, dev);
पूर्ण

/*
 * Called by the parent device driver to set the device which represents
 * this mdev in iommu protection scope. By शेष, the iommu device is
 * शून्य, that indicates using venकरोr defined isolation.
 *
 * @dev: the mediated device that iommu will isolate.
 * @iommu_device: a pci device which represents the iommu क्रम @dev.
 */
अटल अंतरभूत व्योम mdev_set_iommu_device(काष्ठा mdev_device *mdev,
					 काष्ठा device *iommu_device)
अणु
	mdev->iommu_device = iommu_device;
पूर्ण

अटल अंतरभूत काष्ठा device *mdev_get_iommu_device(काष्ठा mdev_device *mdev)
अणु
	वापस mdev->iommu_device;
पूर्ण

अचिन्हित पूर्णांक mdev_get_type_group_id(काष्ठा mdev_device *mdev);
अचिन्हित पूर्णांक mtype_get_type_group_id(काष्ठा mdev_type *mtype);
काष्ठा device *mtype_get_parent_dev(काष्ठा mdev_type *mtype);

/**
 * काष्ठा mdev_parent_ops - Structure to be रेजिस्टरed क्रम each parent device to
 * रेजिस्टर the device to mdev module.
 *
 * @owner:		The module owner.
 * @dev_attr_groups:	Attributes of the parent device.
 * @mdev_attr_groups:	Attributes of the mediated device.
 * @supported_type_groups: Attributes to define supported types. It is mandatory
 *			to provide supported types.
 * @create:		Called to allocate basic resources in parent device's
 *			driver क्रम a particular mediated device. It is
 *			mandatory to provide create ops.
 *			@mdev: mdev_device काष्ठाure on of mediated device
 *			      that is being created
 *			Returns पूर्णांकeger: success (0) or error (< 0)
 * @हटाओ:		Called to मुक्त resources in parent device's driver क्रम
 *			a mediated device. It is mandatory to provide 'remove'
 *			ops.
 *			@mdev: mdev_device device काष्ठाure which is being
 *			       destroyed
 *			Returns पूर्णांकeger: success (0) or error (< 0)
 * @खोलो:		Open mediated device.
 *			@mdev: mediated device.
 *			Returns पूर्णांकeger: success (0) or error (< 0)
 * @release:		release mediated device
 *			@mdev: mediated device.
 * @पढ़ो:		Read emulation callback
 *			@mdev: mediated device काष्ठाure
 *			@buf: पढ़ो buffer
 *			@count: number of bytes to पढ़ो
 *			@ppos: address.
 *			Retuns number on bytes पढ़ो on success or error.
 * @ग_लिखो:		Write emulation callback
 *			@mdev: mediated device काष्ठाure
 *			@buf: ग_लिखो buffer
 *			@count: number of bytes to be written
 *			@ppos: address.
 *			Retuns number on bytes written on success or error.
 * @ioctl:		IOCTL callback
 *			@mdev: mediated device काष्ठाure
 *			@cmd: ioctl command
 *			@arg: arguments to ioctl
 * @mmap:		mmap callback
 *			@mdev: mediated device काष्ठाure
 *			@vma: vma काष्ठाure
 * @request:		request callback to release device
 *			@mdev: mediated device काष्ठाure
 *			@count: request sequence number
 * Parent device that support mediated device should be रेजिस्टरed with mdev
 * module with mdev_parent_ops काष्ठाure.
 **/
काष्ठा mdev_parent_ops अणु
	काष्ठा module   *owner;
	स्थिर काष्ठा attribute_group **dev_attr_groups;
	स्थिर काष्ठा attribute_group **mdev_attr_groups;
	काष्ठा attribute_group **supported_type_groups;

	पूर्णांक     (*create)(काष्ठा mdev_device *mdev);
	पूर्णांक     (*हटाओ)(काष्ठा mdev_device *mdev);
	पूर्णांक     (*खोलो)(काष्ठा mdev_device *mdev);
	व्योम    (*release)(काष्ठा mdev_device *mdev);
	sमाप_प्रकार (*पढ़ो)(काष्ठा mdev_device *mdev, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos);
	sमाप_प्रकार (*ग_लिखो)(काष्ठा mdev_device *mdev, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos);
	दीर्घ	(*ioctl)(काष्ठा mdev_device *mdev, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg);
	पूर्णांक	(*mmap)(काष्ठा mdev_device *mdev, काष्ठा vm_area_काष्ठा *vma);
	व्योम	(*request)(काष्ठा mdev_device *mdev, अचिन्हित पूर्णांक count);
पूर्ण;

/* पूर्णांकerface क्रम exporting mdev supported type attributes */
काष्ठा mdev_type_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा mdev_type *mtype,
			काष्ठा mdev_type_attribute *attr, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा mdev_type *mtype,
			 काष्ठा mdev_type_attribute *attr, स्थिर अक्षर *buf,
			 माप_प्रकार count);
पूर्ण;

#घोषणा MDEV_TYPE_ATTR(_name, _mode, _show, _store)		\
काष्ठा mdev_type_attribute mdev_type_attr_##_name =		\
	__ATTR(_name, _mode, _show, _store)
#घोषणा MDEV_TYPE_ATTR_RW(_name) \
	काष्ठा mdev_type_attribute mdev_type_attr_##_name = __ATTR_RW(_name)
#घोषणा MDEV_TYPE_ATTR_RO(_name) \
	काष्ठा mdev_type_attribute mdev_type_attr_##_name = __ATTR_RO(_name)
#घोषणा MDEV_TYPE_ATTR_WO(_name) \
	काष्ठा mdev_type_attribute mdev_type_attr_##_name = __ATTR_WO(_name)

/**
 * काष्ठा mdev_driver - Mediated device driver
 * @probe: called when new device created
 * @हटाओ: called when device हटाओd
 * @driver: device driver काष्ठाure
 *
 **/
काष्ठा mdev_driver अणु
	पूर्णांक (*probe)(काष्ठा mdev_device *dev);
	व्योम (*हटाओ)(काष्ठा mdev_device *dev);
	काष्ठा device_driver driver;
पूर्ण;

अटल अंतरभूत व्योम *mdev_get_drvdata(काष्ठा mdev_device *mdev)
अणु
	वापस mdev->driver_data;
पूर्ण
अटल अंतरभूत व्योम mdev_set_drvdata(काष्ठा mdev_device *mdev, व्योम *data)
अणु
	mdev->driver_data = data;
पूर्ण
अटल अंतरभूत स्थिर guid_t *mdev_uuid(काष्ठा mdev_device *mdev)
अणु
	वापस &mdev->uuid;
पूर्ण

बाह्य काष्ठा bus_type mdev_bus_type;

पूर्णांक mdev_रेजिस्टर_device(काष्ठा device *dev, स्थिर काष्ठा mdev_parent_ops *ops);
व्योम mdev_unरेजिस्टर_device(काष्ठा device *dev);

पूर्णांक mdev_रेजिस्टर_driver(काष्ठा mdev_driver *drv);
व्योम mdev_unरेजिस्टर_driver(काष्ठा mdev_driver *drv);

काष्ठा device *mdev_parent_dev(काष्ठा mdev_device *mdev);
अटल अंतरभूत काष्ठा device *mdev_dev(काष्ठा mdev_device *mdev)
अणु
	वापस &mdev->dev;
पूर्ण
अटल अंतरभूत काष्ठा mdev_device *mdev_from_dev(काष्ठा device *dev)
अणु
	वापस dev->bus == &mdev_bus_type ? to_mdev_device(dev) : शून्य;
पूर्ण

#पूर्ण_अगर /* MDEV_H */
