<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IOMMU sysfs class support
 *
 * Copyright (C) 2014 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/iommu.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

/*
 * We provide a common class "devices" group which initially has no attributes.
 * As devices are added to the IOMMU, we'll add links to the group.
 */
अटल काष्ठा attribute *devices_attr[] = अणु
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group devices_attr_group = अणु
	.name = "devices",
	.attrs = devices_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dev_groups[] = अणु
	&devices_attr_group,
	शून्य,
पूर्ण;

अटल व्योम release_device(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल काष्ठा class iommu_class = अणु
	.name = "iommu",
	.dev_release = release_device,
	.dev_groups = dev_groups,
पूर्ण;

अटल पूर्णांक __init iommu_dev_init(व्योम)
अणु
	वापस class_रेजिस्टर(&iommu_class);
पूर्ण
postcore_initcall(iommu_dev_init);

/*
 * Init the काष्ठा device क्रम the IOMMU. IOMMU specअगरic attributes can
 * be provided as an attribute group, allowing a unique namespace per
 * IOMMU type.
 */
पूर्णांक iommu_device_sysfs_add(काष्ठा iommu_device *iommu,
			   काष्ठा device *parent,
			   स्थिर काष्ठा attribute_group **groups,
			   स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची vargs;
	पूर्णांक ret;

	iommu->dev = kzalloc(माप(*iommu->dev), GFP_KERNEL);
	अगर (!iommu->dev)
		वापस -ENOMEM;

	device_initialize(iommu->dev);

	iommu->dev->class = &iommu_class;
	iommu->dev->parent = parent;
	iommu->dev->groups = groups;

	बहु_शुरू(vargs, fmt);
	ret = kobject_set_name_vargs(&iommu->dev->kobj, fmt, vargs);
	बहु_पूर्ण(vargs);
	अगर (ret)
		जाओ error;

	ret = device_add(iommu->dev);
	अगर (ret)
		जाओ error;

	dev_set_drvdata(iommu->dev, iommu);

	वापस 0;

error:
	put_device(iommu->dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_device_sysfs_add);

व्योम iommu_device_sysfs_हटाओ(काष्ठा iommu_device *iommu)
अणु
	dev_set_drvdata(iommu->dev, शून्य);
	device_unरेजिस्टर(iommu->dev);
	iommu->dev = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_device_sysfs_हटाओ);

/*
 * IOMMU drivers can indicate a device is managed by a given IOMMU using
 * this पूर्णांकerface.  A link to the device will be created in the "devices"
 * directory of the IOMMU device in sysfs and an "iommu" link will be
 * created under the linked device, poपूर्णांकing back at the IOMMU device.
 */
पूर्णांक iommu_device_link(काष्ठा iommu_device *iommu, काष्ठा device *link)
अणु
	पूर्णांक ret;

	अगर (!iommu || IS_ERR(iommu))
		वापस -ENODEV;

	ret = sysfs_add_link_to_group(&iommu->dev->kobj, "devices",
				      &link->kobj, dev_name(link));
	अगर (ret)
		वापस ret;

	ret = sysfs_create_link_nowarn(&link->kobj, &iommu->dev->kobj, "iommu");
	अगर (ret)
		sysfs_हटाओ_link_from_group(&iommu->dev->kobj, "devices",
					     dev_name(link));

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_device_link);

व्योम iommu_device_unlink(काष्ठा iommu_device *iommu, काष्ठा device *link)
अणु
	अगर (!iommu || IS_ERR(iommu))
		वापस;

	sysfs_हटाओ_link(&link->kobj, "iommu");
	sysfs_हटाओ_link_from_group(&iommu->dev->kobj, "devices", dev_name(link));
पूर्ण
EXPORT_SYMBOL_GPL(iommu_device_unlink);
