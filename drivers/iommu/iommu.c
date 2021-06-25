<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2008 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <jroedel@suse.de>
 */

#घोषणा pr_fmt(fmt)    "iommu: " fmt

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/iommu.h>
#समावेश <linux/idr.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/err.h>
#समावेश <linux/pci.h>
#समावेश <linux/bitops.h>
#समावेश <linux/property.h>
#समावेश <linux/fsl/mc.h>
#समावेश <linux/module.h>
#समावेश <trace/events/iommu.h>

अटल काष्ठा kset *iommu_group_kset;
अटल DEFINE_IDA(iommu_group_ida);

अटल अचिन्हित पूर्णांक iommu_def_करोमुख्य_type __पढ़ो_mostly;
अटल bool iommu_dma_strict __पढ़ो_mostly = true;
अटल u32 iommu_cmd_line __पढ़ो_mostly;

काष्ठा iommu_group अणु
	काष्ठा kobject kobj;
	काष्ठा kobject *devices_kobj;
	काष्ठा list_head devices;
	काष्ठा mutex mutex;
	काष्ठा blocking_notअगरier_head notअगरier;
	व्योम *iommu_data;
	व्योम (*iommu_data_release)(व्योम *iommu_data);
	अक्षर *name;
	पूर्णांक id;
	काष्ठा iommu_करोमुख्य *शेष_करोमुख्य;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा list_head entry;
पूर्ण;

काष्ठा group_device अणु
	काष्ठा list_head list;
	काष्ठा device *dev;
	अक्षर *name;
पूर्ण;

काष्ठा iommu_group_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा iommu_group *group, अक्षर *buf);
	sमाप_प्रकार (*store)(काष्ठा iommu_group *group,
			 स्थिर अक्षर *buf, माप_प्रकार count);
पूर्ण;

अटल स्थिर अक्षर * स्थिर iommu_group_resv_type_string[] = अणु
	[IOMMU_RESV_सूचीECT]			= "direct",
	[IOMMU_RESV_सूचीECT_RELAXABLE]		= "direct-relaxable",
	[IOMMU_RESV_RESERVED]			= "reserved",
	[IOMMU_RESV_MSI]			= "msi",
	[IOMMU_RESV_SW_MSI]			= "msi",
पूर्ण;

#घोषणा IOMMU_CMD_LINE_DMA_API		BIT(0)
#घोषणा IOMMU_CMD_LINE_STRICT		BIT(1)

अटल पूर्णांक iommu_alloc_शेष_करोमुख्य(काष्ठा iommu_group *group,
				      काष्ठा device *dev);
अटल काष्ठा iommu_करोमुख्य *__iommu_करोमुख्य_alloc(काष्ठा bus_type *bus,
						 अचिन्हित type);
अटल पूर्णांक __iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा device *dev);
अटल पूर्णांक __iommu_attach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
				काष्ठा iommu_group *group);
अटल व्योम __iommu_detach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा iommu_group *group);
अटल पूर्णांक iommu_create_device_direct_mappings(काष्ठा iommu_group *group,
					       काष्ठा device *dev);
अटल काष्ठा iommu_group *iommu_group_get_क्रम_dev(काष्ठा device *dev);
अटल sमाप_प्रकार iommu_group_store_type(काष्ठा iommu_group *group,
				      स्थिर अक्षर *buf, माप_प्रकार count);

#घोषणा IOMMU_GROUP_ATTR(_name, _mode, _show, _store)		\
काष्ठा iommu_group_attribute iommu_group_attr_##_name =		\
	__ATTR(_name, _mode, _show, _store)

#घोषणा to_iommu_group_attr(_attr)	\
	container_of(_attr, काष्ठा iommu_group_attribute, attr)
#घोषणा to_iommu_group(_kobj)		\
	container_of(_kobj, काष्ठा iommu_group, kobj)

अटल LIST_HEAD(iommu_device_list);
अटल DEFINE_SPINLOCK(iommu_device_lock);

/*
 * Use a function instead of an array here because the करोमुख्य-type is a
 * bit-field, so an array would waste memory.
 */
अटल स्थिर अक्षर *iommu_करोमुख्य_type_str(अचिन्हित पूर्णांक t)
अणु
	चयन (t) अणु
	हाल IOMMU_DOMAIN_BLOCKED:
		वापस "Blocked";
	हाल IOMMU_DOMAIN_IDENTITY:
		वापस "Passthrough";
	हाल IOMMU_DOMAIN_UNMANAGED:
		वापस "Unmanaged";
	हाल IOMMU_DOMAIN_DMA:
		वापस "Translated";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक __init iommu_subsys_init(व्योम)
अणु
	अगर (!(iommu_cmd_line & IOMMU_CMD_LINE_DMA_API)) अणु
		अगर (IS_ENABLED(CONFIG_IOMMU_DEFAULT_PASSTHROUGH))
			iommu_set_शेष_passthrough(false);
		अन्यथा
			iommu_set_शेष_translated(false);

		अगर (iommu_शेष_passthrough() && mem_encrypt_active()) अणु
			pr_info("Memory encryption detected - Disabling default IOMMU Passthrough\n");
			iommu_set_शेष_translated(false);
		पूर्ण
	पूर्ण

	pr_info("Default domain type: %s %s\n",
		iommu_करोमुख्य_type_str(iommu_def_करोमुख्य_type),
		(iommu_cmd_line & IOMMU_CMD_LINE_DMA_API) ?
			"(set via kernel command line)" : "");

	वापस 0;
पूर्ण
subsys_initcall(iommu_subsys_init);

/**
 * iommu_device_रेजिस्टर() - Register an IOMMU hardware instance
 * @iommu: IOMMU handle क्रम the instance
 * @ops:   IOMMU ops to associate with the instance
 * @hwdev: (optional) actual instance device, used क्रम fwnode lookup
 *
 * Return: 0 on success, or an error.
 */
पूर्णांक iommu_device_रेजिस्टर(काष्ठा iommu_device *iommu,
			  स्थिर काष्ठा iommu_ops *ops, काष्ठा device *hwdev)
अणु
	/* We need to be able to take module references appropriately */
	अगर (WARN_ON(is_module_address((अचिन्हित दीर्घ)ops) && !ops->owner))
		वापस -EINVAL;

	iommu->ops = ops;
	अगर (hwdev)
		iommu->fwnode = hwdev->fwnode;

	spin_lock(&iommu_device_lock);
	list_add_tail(&iommu->list, &iommu_device_list);
	spin_unlock(&iommu_device_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_device_रेजिस्टर);

व्योम iommu_device_unरेजिस्टर(काष्ठा iommu_device *iommu)
अणु
	spin_lock(&iommu_device_lock);
	list_del(&iommu->list);
	spin_unlock(&iommu_device_lock);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_device_unरेजिस्टर);

अटल काष्ठा dev_iommu *dev_iommu_get(काष्ठा device *dev)
अणु
	काष्ठा dev_iommu *param = dev->iommu;

	अगर (param)
		वापस param;

	param = kzalloc(माप(*param), GFP_KERNEL);
	अगर (!param)
		वापस शून्य;

	mutex_init(&param->lock);
	dev->iommu = param;
	वापस param;
पूर्ण

अटल व्योम dev_iommu_मुक्त(काष्ठा device *dev)
अणु
	iommu_fwspec_मुक्त(dev);
	kमुक्त(dev->iommu);
	dev->iommu = शून्य;
पूर्ण

अटल पूर्णांक __iommu_probe_device(काष्ठा device *dev, काष्ठा list_head *group_list)
अणु
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;
	काष्ठा iommu_device *iommu_dev;
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	अगर (!ops)
		वापस -ENODEV;

	अगर (!dev_iommu_get(dev))
		वापस -ENOMEM;

	अगर (!try_module_get(ops->owner)) अणु
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	iommu_dev = ops->probe_device(dev);
	अगर (IS_ERR(iommu_dev)) अणु
		ret = PTR_ERR(iommu_dev);
		जाओ out_module_put;
	पूर्ण

	dev->iommu->iommu_dev = iommu_dev;

	group = iommu_group_get_क्रम_dev(dev);
	अगर (IS_ERR(group)) अणु
		ret = PTR_ERR(group);
		जाओ out_release;
	पूर्ण
	iommu_group_put(group);

	अगर (group_list && !group->शेष_करोमुख्य && list_empty(&group->entry))
		list_add_tail(&group->entry, group_list);

	iommu_device_link(iommu_dev, dev);

	वापस 0;

out_release:
	ops->release_device(dev);

out_module_put:
	module_put(ops->owner);

err_मुक्त:
	dev_iommu_मुक्त(dev);

	वापस ret;
पूर्ण

पूर्णांक iommu_probe_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	ret = __iommu_probe_device(dev, शून्य);
	अगर (ret)
		जाओ err_out;

	group = iommu_group_get(dev);
	अगर (!group) अणु
		ret = -ENODEV;
		जाओ err_release;
	पूर्ण

	/*
	 * Try to allocate a शेष करोमुख्य - needs support from the
	 * IOMMU driver. There are still some drivers which करोn't
	 * support शेष करोमुख्यs, so the वापस value is not yet
	 * checked.
	 */
	iommu_alloc_शेष_करोमुख्य(group, dev);

	अगर (group->शेष_करोमुख्य) अणु
		ret = __iommu_attach_device(group->शेष_करोमुख्य, dev);
		अगर (ret) अणु
			iommu_group_put(group);
			जाओ err_release;
		पूर्ण
	पूर्ण

	iommu_create_device_direct_mappings(group, dev);

	iommu_group_put(group);

	अगर (ops->probe_finalize)
		ops->probe_finalize(dev);

	वापस 0;

err_release:
	iommu_release_device(dev);

err_out:
	वापस ret;

पूर्ण

व्योम iommu_release_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;

	अगर (!dev->iommu)
		वापस;

	iommu_device_unlink(dev->iommu->iommu_dev, dev);

	ops->release_device(dev);

	iommu_group_हटाओ_device(dev);
	module_put(ops->owner);
	dev_iommu_मुक्त(dev);
पूर्ण

अटल पूर्णांक __init iommu_set_def_करोमुख्य_type(अक्षर *str)
अणु
	bool pt;
	पूर्णांक ret;

	ret = kstrtobool(str, &pt);
	अगर (ret)
		वापस ret;

	अगर (pt)
		iommu_set_शेष_passthrough(true);
	अन्यथा
		iommu_set_शेष_translated(true);

	वापस 0;
पूर्ण
early_param("iommu.passthrough", iommu_set_def_करोमुख्य_type);

अटल पूर्णांक __init iommu_dma_setup(अक्षर *str)
अणु
	पूर्णांक ret = kstrtobool(str, &iommu_dma_strict);

	अगर (!ret)
		iommu_cmd_line |= IOMMU_CMD_LINE_STRICT;
	वापस ret;
पूर्ण
early_param("iommu.strict", iommu_dma_setup);

व्योम iommu_set_dma_strict(bool strict)
अणु
	अगर (strict || !(iommu_cmd_line & IOMMU_CMD_LINE_STRICT))
		iommu_dma_strict = strict;
पूर्ण

bool iommu_get_dma_strict(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	/* only allow lazy flushing क्रम DMA करोमुख्यs */
	अगर (करोमुख्य->type == IOMMU_DOMAIN_DMA)
		वापस iommu_dma_strict;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_get_dma_strict);

अटल sमाप_प्रकार iommu_group_attr_show(काष्ठा kobject *kobj,
				     काष्ठा attribute *__attr, अक्षर *buf)
अणु
	काष्ठा iommu_group_attribute *attr = to_iommu_group_attr(__attr);
	काष्ठा iommu_group *group = to_iommu_group(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (attr->show)
		ret = attr->show(group, buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार iommu_group_attr_store(काष्ठा kobject *kobj,
				      काष्ठा attribute *__attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा iommu_group_attribute *attr = to_iommu_group_attr(__attr);
	काष्ठा iommu_group *group = to_iommu_group(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (attr->store)
		ret = attr->store(group, buf, count);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops iommu_group_sysfs_ops = अणु
	.show = iommu_group_attr_show,
	.store = iommu_group_attr_store,
पूर्ण;

अटल पूर्णांक iommu_group_create_file(काष्ठा iommu_group *group,
				   काष्ठा iommu_group_attribute *attr)
अणु
	वापस sysfs_create_file(&group->kobj, &attr->attr);
पूर्ण

अटल व्योम iommu_group_हटाओ_file(काष्ठा iommu_group *group,
				    काष्ठा iommu_group_attribute *attr)
अणु
	sysfs_हटाओ_file(&group->kobj, &attr->attr);
पूर्ण

अटल sमाप_प्रकार iommu_group_show_name(काष्ठा iommu_group *group, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", group->name);
पूर्ण

/**
 * iommu_insert_resv_region - Insert a new region in the
 * list of reserved regions.
 * @new: new region to insert
 * @regions: list of regions
 *
 * Elements are sorted by start address and overlapping segments
 * of the same type are merged.
 */
अटल पूर्णांक iommu_insert_resv_region(काष्ठा iommu_resv_region *new,
				    काष्ठा list_head *regions)
अणु
	काष्ठा iommu_resv_region *iter, *पंचांगp, *nr, *top;
	LIST_HEAD(stack);

	nr = iommu_alloc_resv_region(new->start, new->length,
				     new->prot, new->type);
	अगर (!nr)
		वापस -ENOMEM;

	/* First add the new element based on start address sorting */
	list_क्रम_each_entry(iter, regions, list) अणु
		अगर (nr->start < iter->start ||
		    (nr->start == iter->start && nr->type <= iter->type))
			अवरोध;
	पूर्ण
	list_add_tail(&nr->list, &iter->list);

	/* Merge overlapping segments of type nr->type in @regions, अगर any */
	list_क्रम_each_entry_safe(iter, पंचांगp, regions, list) अणु
		phys_addr_t top_end, iter_end = iter->start + iter->length - 1;

		/* no merge needed on elements of dअगरferent types than @new */
		अगर (iter->type != new->type) अणु
			list_move_tail(&iter->list, &stack);
			जारी;
		पूर्ण

		/* look क्रम the last stack element of same type as @iter */
		list_क्रम_each_entry_reverse(top, &stack, list)
			अगर (top->type == iter->type)
				जाओ check_overlap;

		list_move_tail(&iter->list, &stack);
		जारी;

check_overlap:
		top_end = top->start + top->length - 1;

		अगर (iter->start > top_end + 1) अणु
			list_move_tail(&iter->list, &stack);
		पूर्ण अन्यथा अणु
			top->length = max(top_end, iter_end) - top->start + 1;
			list_del(&iter->list);
			kमुक्त(iter);
		पूर्ण
	पूर्ण
	list_splice(&stack, regions);
	वापस 0;
पूर्ण

अटल पूर्णांक
iommu_insert_device_resv_regions(काष्ठा list_head *dev_resv_regions,
				 काष्ठा list_head *group_resv_regions)
अणु
	काष्ठा iommu_resv_region *entry;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(entry, dev_resv_regions, list) अणु
		ret = iommu_insert_resv_region(entry, group_resv_regions);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक iommu_get_group_resv_regions(काष्ठा iommu_group *group,
				 काष्ठा list_head *head)
अणु
	काष्ठा group_device *device;
	पूर्णांक ret = 0;

	mutex_lock(&group->mutex);
	list_क्रम_each_entry(device, &group->devices, list) अणु
		काष्ठा list_head dev_resv_regions;

		INIT_LIST_HEAD(&dev_resv_regions);
		iommu_get_resv_regions(device->dev, &dev_resv_regions);
		ret = iommu_insert_device_resv_regions(&dev_resv_regions, head);
		iommu_put_resv_regions(device->dev, &dev_resv_regions);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&group->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_get_group_resv_regions);

अटल sमाप_प्रकार iommu_group_show_resv_regions(काष्ठा iommu_group *group,
					     अक्षर *buf)
अणु
	काष्ठा iommu_resv_region *region, *next;
	काष्ठा list_head group_resv_regions;
	अक्षर *str = buf;

	INIT_LIST_HEAD(&group_resv_regions);
	iommu_get_group_resv_regions(group, &group_resv_regions);

	list_क्रम_each_entry_safe(region, next, &group_resv_regions, list) अणु
		str += प्र_लिखो(str, "0x%016llx 0x%016llx %s\n",
			       (दीर्घ दीर्घ पूर्णांक)region->start,
			       (दीर्घ दीर्घ पूर्णांक)(region->start +
						region->length - 1),
			       iommu_group_resv_type_string[region->type]);
		kमुक्त(region);
	पूर्ण

	वापस (str - buf);
पूर्ण

अटल sमाप_प्रकार iommu_group_show_type(काष्ठा iommu_group *group,
				     अक्षर *buf)
अणु
	अक्षर *type = "unknown\n";

	mutex_lock(&group->mutex);
	अगर (group->शेष_करोमुख्य) अणु
		चयन (group->शेष_करोमुख्य->type) अणु
		हाल IOMMU_DOMAIN_BLOCKED:
			type = "blocked\n";
			अवरोध;
		हाल IOMMU_DOMAIN_IDENTITY:
			type = "identity\n";
			अवरोध;
		हाल IOMMU_DOMAIN_UNMANAGED:
			type = "unmanaged\n";
			अवरोध;
		हाल IOMMU_DOMAIN_DMA:
			type = "DMA\n";
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&group->mutex);
	म_नकल(buf, type);

	वापस म_माप(type);
पूर्ण

अटल IOMMU_GROUP_ATTR(name, S_IRUGO, iommu_group_show_name, शून्य);

अटल IOMMU_GROUP_ATTR(reserved_regions, 0444,
			iommu_group_show_resv_regions, शून्य);

अटल IOMMU_GROUP_ATTR(type, 0644, iommu_group_show_type,
			iommu_group_store_type);

अटल व्योम iommu_group_release(काष्ठा kobject *kobj)
अणु
	काष्ठा iommu_group *group = to_iommu_group(kobj);

	pr_debug("Releasing group %d\n", group->id);

	अगर (group->iommu_data_release)
		group->iommu_data_release(group->iommu_data);

	ida_simple_हटाओ(&iommu_group_ida, group->id);

	अगर (group->शेष_करोमुख्य)
		iommu_करोमुख्य_मुक्त(group->शेष_करोमुख्य);

	kमुक्त(group->name);
	kमुक्त(group);
पूर्ण

अटल काष्ठा kobj_type iommu_group_ktype = अणु
	.sysfs_ops = &iommu_group_sysfs_ops,
	.release = iommu_group_release,
पूर्ण;

/**
 * iommu_group_alloc - Allocate a new group
 *
 * This function is called by an iommu driver to allocate a new iommu
 * group.  The iommu group represents the minimum granularity of the iommu.
 * Upon successful वापस, the caller holds a reference to the supplied
 * group in order to hold the group until devices are added.  Use
 * iommu_group_put() to release this extra reference count, allowing the
 * group to be स्वतःmatically reclaimed once it has no devices or बाह्यal
 * references.
 */
काष्ठा iommu_group *iommu_group_alloc(व्योम)
अणु
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	group = kzalloc(माप(*group), GFP_KERNEL);
	अगर (!group)
		वापस ERR_PTR(-ENOMEM);

	group->kobj.kset = iommu_group_kset;
	mutex_init(&group->mutex);
	INIT_LIST_HEAD(&group->devices);
	INIT_LIST_HEAD(&group->entry);
	BLOCKING_INIT_NOTIFIER_HEAD(&group->notअगरier);

	ret = ida_simple_get(&iommu_group_ida, 0, 0, GFP_KERNEL);
	अगर (ret < 0) अणु
		kमुक्त(group);
		वापस ERR_PTR(ret);
	पूर्ण
	group->id = ret;

	ret = kobject_init_and_add(&group->kobj, &iommu_group_ktype,
				   शून्य, "%d", group->id);
	अगर (ret) अणु
		ida_simple_हटाओ(&iommu_group_ida, group->id);
		kobject_put(&group->kobj);
		वापस ERR_PTR(ret);
	पूर्ण

	group->devices_kobj = kobject_create_and_add("devices", &group->kobj);
	अगर (!group->devices_kobj) अणु
		kobject_put(&group->kobj); /* triggers .release & मुक्त */
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/*
	 * The devices_kobj holds a reference on the group kobject, so
	 * as दीर्घ as that exists so will the group.  We can thereक्रमe
	 * use the devices_kobj क्रम reference counting.
	 */
	kobject_put(&group->kobj);

	ret = iommu_group_create_file(group,
				      &iommu_group_attr_reserved_regions);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = iommu_group_create_file(group, &iommu_group_attr_type);
	अगर (ret)
		वापस ERR_PTR(ret);

	pr_debug("Allocated group %d\n", group->id);

	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_alloc);

काष्ठा iommu_group *iommu_group_get_by_id(पूर्णांक id)
अणु
	काष्ठा kobject *group_kobj;
	काष्ठा iommu_group *group;
	स्थिर अक्षर *name;

	अगर (!iommu_group_kset)
		वापस शून्य;

	name = kaप्र_लिखो(GFP_KERNEL, "%d", id);
	अगर (!name)
		वापस शून्य;

	group_kobj = kset_find_obj(iommu_group_kset, name);
	kमुक्त(name);

	अगर (!group_kobj)
		वापस शून्य;

	group = container_of(group_kobj, काष्ठा iommu_group, kobj);
	BUG_ON(group->id != id);

	kobject_get(group->devices_kobj);
	kobject_put(&group->kobj);

	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_get_by_id);

/**
 * iommu_group_get_iommudata - retrieve iommu_data रेजिस्टरed क्रम a group
 * @group: the group
 *
 * iommu drivers can store data in the group क्रम use when करोing iommu
 * operations.  This function provides a way to retrieve it.  Caller
 * should hold a group reference.
 */
व्योम *iommu_group_get_iommudata(काष्ठा iommu_group *group)
अणु
	वापस group->iommu_data;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_get_iommudata);

/**
 * iommu_group_set_iommudata - set iommu_data क्रम a group
 * @group: the group
 * @iommu_data: new data
 * @release: release function क्रम iommu_data
 *
 * iommu drivers can store data in the group क्रम use when करोing iommu
 * operations.  This function provides a way to set the data after
 * the group has been allocated.  Caller should hold a group reference.
 */
व्योम iommu_group_set_iommudata(काष्ठा iommu_group *group, व्योम *iommu_data,
			       व्योम (*release)(व्योम *iommu_data))
अणु
	group->iommu_data = iommu_data;
	group->iommu_data_release = release;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_set_iommudata);

/**
 * iommu_group_set_name - set name क्रम a group
 * @group: the group
 * @name: name
 *
 * Allow iommu driver to set a name क्रम a group.  When set it will
 * appear in a name attribute file under the group in sysfs.
 */
पूर्णांक iommu_group_set_name(काष्ठा iommu_group *group, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	अगर (group->name) अणु
		iommu_group_हटाओ_file(group, &iommu_group_attr_name);
		kमुक्त(group->name);
		group->name = शून्य;
		अगर (!name)
			वापस 0;
	पूर्ण

	group->name = kstrdup(name, GFP_KERNEL);
	अगर (!group->name)
		वापस -ENOMEM;

	ret = iommu_group_create_file(group, &iommu_group_attr_name);
	अगर (ret) अणु
		kमुक्त(group->name);
		group->name = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_set_name);

अटल पूर्णांक iommu_create_device_direct_mappings(काष्ठा iommu_group *group,
					       काष्ठा device *dev)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = group->शेष_करोमुख्य;
	काष्ठा iommu_resv_region *entry;
	काष्ठा list_head mappings;
	अचिन्हित दीर्घ pg_size;
	पूर्णांक ret = 0;

	अगर (!करोमुख्य || करोमुख्य->type != IOMMU_DOMAIN_DMA)
		वापस 0;

	BUG_ON(!करोमुख्य->pgsize_biपंचांगap);

	pg_size = 1UL << __ffs(करोमुख्य->pgsize_biपंचांगap);
	INIT_LIST_HEAD(&mappings);

	iommu_get_resv_regions(dev, &mappings);

	/* We need to consider overlapping regions क्रम dअगरferent devices */
	list_क्रम_each_entry(entry, &mappings, list) अणु
		dma_addr_t start, end, addr;
		माप_प्रकार map_size = 0;

		अगर (करोमुख्य->ops->apply_resv_region)
			करोमुख्य->ops->apply_resv_region(dev, करोमुख्य, entry);

		start = ALIGN(entry->start, pg_size);
		end   = ALIGN(entry->start + entry->length, pg_size);

		अगर (entry->type != IOMMU_RESV_सूचीECT &&
		    entry->type != IOMMU_RESV_सूचीECT_RELAXABLE)
			जारी;

		क्रम (addr = start; addr <= end; addr += pg_size) अणु
			phys_addr_t phys_addr;

			अगर (addr == end)
				जाओ map_end;

			phys_addr = iommu_iova_to_phys(करोमुख्य, addr);
			अगर (!phys_addr) अणु
				map_size += pg_size;
				जारी;
			पूर्ण

map_end:
			अगर (map_size) अणु
				ret = iommu_map(करोमुख्य, addr - map_size,
						addr - map_size, map_size,
						entry->prot);
				अगर (ret)
					जाओ out;
				map_size = 0;
			पूर्ण
		पूर्ण

	पूर्ण

	iommu_flush_iotlb_all(करोमुख्य);

out:
	iommu_put_resv_regions(dev, &mappings);

	वापस ret;
पूर्ण

अटल bool iommu_is_attach_deferred(काष्ठा iommu_करोमुख्य *करोमुख्य,
				     काष्ठा device *dev)
अणु
	अगर (करोमुख्य->ops->is_attach_deferred)
		वापस करोमुख्य->ops->is_attach_deferred(करोमुख्य, dev);

	वापस false;
पूर्ण

/**
 * iommu_group_add_device - add a device to an iommu group
 * @group: the group पूर्णांकo which to add the device (reference should be held)
 * @dev: the device
 *
 * This function is called by an iommu driver to add a device पूर्णांकo a
 * group.  Adding a device increments the group reference count.
 */
पूर्णांक iommu_group_add_device(काष्ठा iommu_group *group, काष्ठा device *dev)
अणु
	पूर्णांक ret, i = 0;
	काष्ठा group_device *device;

	device = kzalloc(माप(*device), GFP_KERNEL);
	अगर (!device)
		वापस -ENOMEM;

	device->dev = dev;

	ret = sysfs_create_link(&dev->kobj, &group->kobj, "iommu_group");
	अगर (ret)
		जाओ err_मुक्त_device;

	device->name = kaप्र_लिखो(GFP_KERNEL, "%s", kobject_name(&dev->kobj));
नाम:
	अगर (!device->name) अणु
		ret = -ENOMEM;
		जाओ err_हटाओ_link;
	पूर्ण

	ret = sysfs_create_link_nowarn(group->devices_kobj,
				       &dev->kobj, device->name);
	अगर (ret) अणु
		अगर (ret == -EEXIST && i >= 0) अणु
			/*
			 * Account क्रम the slim chance of collision
			 * and append an instance to the name.
			 */
			kमुक्त(device->name);
			device->name = kaप्र_लिखो(GFP_KERNEL, "%s.%d",
						 kobject_name(&dev->kobj), i++);
			जाओ नाम;
		पूर्ण
		जाओ err_मुक्त_name;
	पूर्ण

	kobject_get(group->devices_kobj);

	dev->iommu_group = group;

	mutex_lock(&group->mutex);
	list_add_tail(&device->list, &group->devices);
	अगर (group->करोमुख्य  && !iommu_is_attach_deferred(group->करोमुख्य, dev))
		ret = __iommu_attach_device(group->करोमुख्य, dev);
	mutex_unlock(&group->mutex);
	अगर (ret)
		जाओ err_put_group;

	/* Notअगरy any listeners about change to group. */
	blocking_notअगरier_call_chain(&group->notअगरier,
				     IOMMU_GROUP_NOTIFY_ADD_DEVICE, dev);

	trace_add_device_to_group(group->id, dev);

	dev_info(dev, "Adding to iommu group %d\n", group->id);

	वापस 0;

err_put_group:
	mutex_lock(&group->mutex);
	list_del(&device->list);
	mutex_unlock(&group->mutex);
	dev->iommu_group = शून्य;
	kobject_put(group->devices_kobj);
	sysfs_हटाओ_link(group->devices_kobj, device->name);
err_मुक्त_name:
	kमुक्त(device->name);
err_हटाओ_link:
	sysfs_हटाओ_link(&dev->kobj, "iommu_group");
err_मुक्त_device:
	kमुक्त(device);
	dev_err(dev, "Failed to add to iommu group %d: %d\n", group->id, ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_add_device);

/**
 * iommu_group_हटाओ_device - हटाओ a device from it's current group
 * @dev: device to be हटाओd
 *
 * This function is called by an iommu driver to हटाओ the device from
 * it's current group.  This decrements the iommu group reference count.
 */
व्योम iommu_group_हटाओ_device(काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group = dev->iommu_group;
	काष्ठा group_device *पंचांगp_device, *device = शून्य;

	dev_info(dev, "Removing from iommu group %d\n", group->id);

	/* Pre-notअगरy listeners that a device is being हटाओd. */
	blocking_notअगरier_call_chain(&group->notअगरier,
				     IOMMU_GROUP_NOTIFY_DEL_DEVICE, dev);

	mutex_lock(&group->mutex);
	list_क्रम_each_entry(पंचांगp_device, &group->devices, list) अणु
		अगर (पंचांगp_device->dev == dev) अणु
			device = पंचांगp_device;
			list_del(&device->list);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&group->mutex);

	अगर (!device)
		वापस;

	sysfs_हटाओ_link(group->devices_kobj, device->name);
	sysfs_हटाओ_link(&dev->kobj, "iommu_group");

	trace_हटाओ_device_from_group(group->id, dev);

	kमुक्त(device->name);
	kमुक्त(device);
	dev->iommu_group = शून्य;
	kobject_put(group->devices_kobj);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_हटाओ_device);

अटल पूर्णांक iommu_group_device_count(काष्ठा iommu_group *group)
अणु
	काष्ठा group_device *entry;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(entry, &group->devices, list)
		ret++;

	वापस ret;
पूर्ण

/**
 * iommu_group_क्रम_each_dev - iterate over each device in the group
 * @group: the group
 * @data: caller opaque data to be passed to callback function
 * @fn: caller supplied callback function
 *
 * This function is called by group users to iterate over group devices.
 * Callers should hold a reference count to the group during callback.
 * The group->mutex is held across callbacks, which will block calls to
 * iommu_group_add/हटाओ_device.
 */
अटल पूर्णांक __iommu_group_क्रम_each_dev(काष्ठा iommu_group *group, व्योम *data,
				      पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	काष्ठा group_device *device;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(device, &group->devices, list) अणु
		ret = fn(device->dev, data);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण


पूर्णांक iommu_group_क्रम_each_dev(काष्ठा iommu_group *group, व्योम *data,
			     पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	पूर्णांक ret;

	mutex_lock(&group->mutex);
	ret = __iommu_group_क्रम_each_dev(group, data, fn);
	mutex_unlock(&group->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_क्रम_each_dev);

/**
 * iommu_group_get - Return the group क्रम a device and increment reference
 * @dev: get the group that this device beदीर्घs to
 *
 * This function is called by iommu drivers and users to get the group
 * क्रम the specअगरied device.  If found, the group is वापसed and the group
 * reference in incremented, अन्यथा शून्य.
 */
काष्ठा iommu_group *iommu_group_get(काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group = dev->iommu_group;

	अगर (group)
		kobject_get(group->devices_kobj);

	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_get);

/**
 * iommu_group_ref_get - Increment reference on a group
 * @group: the group to use, must not be शून्य
 *
 * This function is called by iommu drivers to take additional references on an
 * existing group.  Returns the given group क्रम convenience.
 */
काष्ठा iommu_group *iommu_group_ref_get(काष्ठा iommu_group *group)
अणु
	kobject_get(group->devices_kobj);
	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_ref_get);

/**
 * iommu_group_put - Decrement group reference
 * @group: the group to use
 *
 * This function is called by iommu drivers and users to release the
 * iommu group.  Once the reference count is zero, the group is released.
 */
व्योम iommu_group_put(काष्ठा iommu_group *group)
अणु
	अगर (group)
		kobject_put(group->devices_kobj);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_put);

/**
 * iommu_group_रेजिस्टर_notअगरier - Register a notअगरier क्रम group changes
 * @group: the group to watch
 * @nb: notअगरier block to संकेत
 *
 * This function allows iommu group users to track changes in a group.
 * See include/linux/iommu.h क्रम actions sent via this notअगरier.  Caller
 * should hold a reference to the group throughout notअगरier registration.
 */
पूर्णांक iommu_group_रेजिस्टर_notअगरier(काष्ठा iommu_group *group,
				  काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&group->notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_रेजिस्टर_notअगरier);

/**
 * iommu_group_unरेजिस्टर_notअगरier - Unरेजिस्टर a notअगरier
 * @group: the group to watch
 * @nb: notअगरier block to संकेत
 *
 * Unरेजिस्टर a previously रेजिस्टरed group notअगरier block.
 */
पूर्णांक iommu_group_unरेजिस्टर_notअगरier(काष्ठा iommu_group *group,
				    काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&group->notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_unरेजिस्टर_notअगरier);

/**
 * iommu_रेजिस्टर_device_fault_handler() - Register a device fault handler
 * @dev: the device
 * @handler: the fault handler
 * @data: निजी data passed as argument to the handler
 *
 * When an IOMMU fault event is received, this handler माला_लो called with the
 * fault event and data as argument. The handler should वापस 0 on success. If
 * the fault is recoverable (IOMMU_FAULT_PAGE_REQ), the consumer should also
 * complete the fault by calling iommu_page_response() with one of the following
 * response code:
 * - IOMMU_PAGE_RESP_SUCCESS: retry the translation
 * - IOMMU_PAGE_RESP_INVALID: terminate the fault
 * - IOMMU_PAGE_RESP_FAILURE: terminate the fault and stop reporting
 *   page faults अगर possible.
 *
 * Return 0 अगर the fault handler was installed successfully, or an error.
 */
पूर्णांक iommu_रेजिस्टर_device_fault_handler(काष्ठा device *dev,
					iommu_dev_fault_handler_t handler,
					व्योम *data)
अणु
	काष्ठा dev_iommu *param = dev->iommu;
	पूर्णांक ret = 0;

	अगर (!param)
		वापस -EINVAL;

	mutex_lock(&param->lock);
	/* Only allow one fault handler रेजिस्टरed क्रम each device */
	अगर (param->fault_param) अणु
		ret = -EBUSY;
		जाओ करोne_unlock;
	पूर्ण

	get_device(dev);
	param->fault_param = kzalloc(माप(*param->fault_param), GFP_KERNEL);
	अगर (!param->fault_param) अणु
		put_device(dev);
		ret = -ENOMEM;
		जाओ करोne_unlock;
	पूर्ण
	param->fault_param->handler = handler;
	param->fault_param->data = data;
	mutex_init(&param->fault_param->lock);
	INIT_LIST_HEAD(&param->fault_param->faults);

करोne_unlock:
	mutex_unlock(&param->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_रेजिस्टर_device_fault_handler);

/**
 * iommu_unरेजिस्टर_device_fault_handler() - Unरेजिस्टर the device fault handler
 * @dev: the device
 *
 * Remove the device fault handler installed with
 * iommu_रेजिस्टर_device_fault_handler().
 *
 * Return 0 on success, or an error.
 */
पूर्णांक iommu_unरेजिस्टर_device_fault_handler(काष्ठा device *dev)
अणु
	काष्ठा dev_iommu *param = dev->iommu;
	पूर्णांक ret = 0;

	अगर (!param)
		वापस -EINVAL;

	mutex_lock(&param->lock);

	अगर (!param->fault_param)
		जाओ unlock;

	/* we cannot unरेजिस्टर handler अगर there are pending faults */
	अगर (!list_empty(&param->fault_param->faults)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	kमुक्त(param->fault_param);
	param->fault_param = शून्य;
	put_device(dev);
unlock:
	mutex_unlock(&param->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_unरेजिस्टर_device_fault_handler);

/**
 * iommu_report_device_fault() - Report fault event to device driver
 * @dev: the device
 * @evt: fault event data
 *
 * Called by IOMMU drivers when a fault is detected, typically in a thपढ़ोed IRQ
 * handler. When this function fails and the fault is recoverable, it is the
 * caller's responsibility to complete the fault.
 *
 * Return 0 on success, or an error.
 */
पूर्णांक iommu_report_device_fault(काष्ठा device *dev, काष्ठा iommu_fault_event *evt)
अणु
	काष्ठा dev_iommu *param = dev->iommu;
	काष्ठा iommu_fault_event *evt_pending = शून्य;
	काष्ठा iommu_fault_param *fparam;
	पूर्णांक ret = 0;

	अगर (!param || !evt)
		वापस -EINVAL;

	/* we only report device fault अगर there is a handler रेजिस्टरed */
	mutex_lock(&param->lock);
	fparam = param->fault_param;
	अगर (!fparam || !fparam->handler) अणु
		ret = -EINVAL;
		जाओ करोne_unlock;
	पूर्ण

	अगर (evt->fault.type == IOMMU_FAULT_PAGE_REQ &&
	    (evt->fault.prm.flags & IOMMU_FAULT_PAGE_REQUEST_LAST_PAGE)) अणु
		evt_pending = kmemdup(evt, माप(काष्ठा iommu_fault_event),
				      GFP_KERNEL);
		अगर (!evt_pending) अणु
			ret = -ENOMEM;
			जाओ करोne_unlock;
		पूर्ण
		mutex_lock(&fparam->lock);
		list_add_tail(&evt_pending->list, &fparam->faults);
		mutex_unlock(&fparam->lock);
	पूर्ण

	ret = fparam->handler(&evt->fault, fparam->data);
	अगर (ret && evt_pending) अणु
		mutex_lock(&fparam->lock);
		list_del(&evt_pending->list);
		mutex_unlock(&fparam->lock);
		kमुक्त(evt_pending);
	पूर्ण
करोne_unlock:
	mutex_unlock(&param->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_report_device_fault);

पूर्णांक iommu_page_response(काष्ठा device *dev,
			काष्ठा iommu_page_response *msg)
अणु
	bool needs_pasid;
	पूर्णांक ret = -EINVAL;
	काष्ठा iommu_fault_event *evt;
	काष्ठा iommu_fault_page_request *prm;
	काष्ठा dev_iommu *param = dev->iommu;
	bool has_pasid = msg->flags & IOMMU_PAGE_RESP_PASID_VALID;
	काष्ठा iommu_करोमुख्य *करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);

	अगर (!करोमुख्य || !करोमुख्य->ops->page_response)
		वापस -ENODEV;

	अगर (!param || !param->fault_param)
		वापस -EINVAL;

	अगर (msg->version != IOMMU_PAGE_RESP_VERSION_1 ||
	    msg->flags & ~IOMMU_PAGE_RESP_PASID_VALID)
		वापस -EINVAL;

	/* Only send response अगर there is a fault report pending */
	mutex_lock(&param->fault_param->lock);
	अगर (list_empty(&param->fault_param->faults)) अणु
		dev_warn_ratelimited(dev, "no pending PRQ, drop response\n");
		जाओ करोne_unlock;
	पूर्ण
	/*
	 * Check अगर we have a matching page request pending to respond,
	 * otherwise वापस -EINVAL
	 */
	list_क्रम_each_entry(evt, &param->fault_param->faults, list) अणु
		prm = &evt->fault.prm;
		अगर (prm->grpid != msg->grpid)
			जारी;

		/*
		 * If the PASID is required, the corresponding request is
		 * matched using the group ID, the PASID valid bit and the PASID
		 * value. Otherwise only the group ID matches request and
		 * response.
		 */
		needs_pasid = prm->flags & IOMMU_FAULT_PAGE_RESPONSE_NEEDS_PASID;
		अगर (needs_pasid && (!has_pasid || msg->pasid != prm->pasid))
			जारी;

		अगर (!needs_pasid && has_pasid) अणु
			/* No big deal, just clear it. */
			msg->flags &= ~IOMMU_PAGE_RESP_PASID_VALID;
			msg->pasid = 0;
		पूर्ण

		ret = करोमुख्य->ops->page_response(dev, evt, msg);
		list_del(&evt->list);
		kमुक्त(evt);
		अवरोध;
	पूर्ण

करोne_unlock:
	mutex_unlock(&param->fault_param->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_page_response);

/**
 * iommu_group_id - Return ID क्रम a group
 * @group: the group to ID
 *
 * Return the unique ID क्रम the group matching the sysfs group number.
 */
पूर्णांक iommu_group_id(काष्ठा iommu_group *group)
अणु
	वापस group->id;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_group_id);

अटल काष्ठा iommu_group *get_pci_alias_group(काष्ठा pci_dev *pdev,
					       अचिन्हित दीर्घ *devfns);

/*
 * To consider a PCI device isolated, we require ACS to support Source
 * Validation, Request Redirection, Completer Redirection, and Upstream
 * Forwarding.  This effectively means that devices cannot spoof their
 * requester ID, requests and completions cannot be redirected, and all
 * transactions are क्रमwarded upstream, even as it passes through a
 * bridge where the target device is करोwnstream.
 */
#घोषणा REQ_ACS_FLAGS   (PCI_ACS_SV | PCI_ACS_RR | PCI_ACS_CR | PCI_ACS_UF)

/*
 * For multअगरunction devices which are not isolated from each other, find
 * all the other non-isolated functions and look क्रम existing groups.  For
 * each function, we also need to look क्रम aliases to or from other devices
 * that may alपढ़ोy have a group.
 */
अटल काष्ठा iommu_group *get_pci_function_alias_group(काष्ठा pci_dev *pdev,
							अचिन्हित दीर्घ *devfns)
अणु
	काष्ठा pci_dev *पंचांगp = शून्य;
	काष्ठा iommu_group *group;

	अगर (!pdev->multअगरunction || pci_acs_enabled(pdev, REQ_ACS_FLAGS))
		वापस शून्य;

	क्रम_each_pci_dev(पंचांगp) अणु
		अगर (पंचांगp == pdev || पंचांगp->bus != pdev->bus ||
		    PCI_SLOT(पंचांगp->devfn) != PCI_SLOT(pdev->devfn) ||
		    pci_acs_enabled(पंचांगp, REQ_ACS_FLAGS))
			जारी;

		group = get_pci_alias_group(पंचांगp, devfns);
		अगर (group) अणु
			pci_dev_put(पंचांगp);
			वापस group;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Look क्रम aliases to or from the given device क्रम existing groups. DMA
 * aliases are only supported on the same bus, thereक्रमe the search
 * space is quite small (especially since we're really only looking at pcie
 * device, and thereक्रमe only expect multiple slots on the root complex or
 * करोwnstream चयन ports).  It's conceivable though that a pair of
 * multअगरunction devices could have aliases between them that would cause a
 * loop.  To prevent this, we use a biपंचांगap to track where we've been.
 */
अटल काष्ठा iommu_group *get_pci_alias_group(काष्ठा pci_dev *pdev,
					       अचिन्हित दीर्घ *devfns)
अणु
	काष्ठा pci_dev *पंचांगp = शून्य;
	काष्ठा iommu_group *group;

	अगर (test_and_set_bit(pdev->devfn & 0xff, devfns))
		वापस शून्य;

	group = iommu_group_get(&pdev->dev);
	अगर (group)
		वापस group;

	क्रम_each_pci_dev(पंचांगp) अणु
		अगर (पंचांगp == pdev || पंचांगp->bus != pdev->bus)
			जारी;

		/* We alias them or they alias us */
		अगर (pci_devs_are_dma_aliases(pdev, पंचांगp)) अणु
			group = get_pci_alias_group(पंचांगp, devfns);
			अगर (group) अणु
				pci_dev_put(पंचांगp);
				वापस group;
			पूर्ण

			group = get_pci_function_alias_group(पंचांगp, devfns);
			अगर (group) अणु
				pci_dev_put(पंचांगp);
				वापस group;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा group_क्रम_pci_data अणु
	काष्ठा pci_dev *pdev;
	काष्ठा iommu_group *group;
पूर्ण;

/*
 * DMA alias iterator callback, वापस the last seen device.  Stop and वापस
 * the IOMMU group अगर we find one aदीर्घ the way.
 */
अटल पूर्णांक get_pci_alias_or_group(काष्ठा pci_dev *pdev, u16 alias, व्योम *opaque)
अणु
	काष्ठा group_क्रम_pci_data *data = opaque;

	data->pdev = pdev;
	data->group = iommu_group_get(&pdev->dev);

	वापस data->group != शून्य;
पूर्ण

/*
 * Generic device_group call-back function. It just allocates one
 * iommu-group per device.
 */
काष्ठा iommu_group *generic_device_group(काष्ठा device *dev)
अणु
	वापस iommu_group_alloc();
पूर्ण
EXPORT_SYMBOL_GPL(generic_device_group);

/*
 * Use standard PCI bus topology, isolation features, and DMA alias quirks
 * to find or create an IOMMU group क्रम a device.
 */
काष्ठा iommu_group *pci_device_group(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा group_क्रम_pci_data data;
	काष्ठा pci_bus *bus;
	काष्ठा iommu_group *group = शून्य;
	u64 devfns[4] = अणु 0 पूर्ण;

	अगर (WARN_ON(!dev_is_pci(dev)))
		वापस ERR_PTR(-EINVAL);

	/*
	 * Find the upstream DMA alias क्रम the device.  A device must not
	 * be aliased due to topology in order to have its own IOMMU group.
	 * If we find an alias aदीर्घ the way that alपढ़ोy beदीर्घs to a
	 * group, use it.
	 */
	अगर (pci_क्रम_each_dma_alias(pdev, get_pci_alias_or_group, &data))
		वापस data.group;

	pdev = data.pdev;

	/*
	 * Continue upstream from the poपूर्णांक of minimum IOMMU granularity
	 * due to aliases to the poपूर्णांक where devices are रक्षित from
	 * peer-to-peer DMA by PCI ACS.  Again, अगर we find an existing
	 * group, use it.
	 */
	क्रम (bus = pdev->bus; !pci_is_root_bus(bus); bus = bus->parent) अणु
		अगर (!bus->self)
			जारी;

		अगर (pci_acs_path_enabled(bus->self, शून्य, REQ_ACS_FLAGS))
			अवरोध;

		pdev = bus->self;

		group = iommu_group_get(&pdev->dev);
		अगर (group)
			वापस group;
	पूर्ण

	/*
	 * Look क्रम existing groups on device aliases.  If we alias another
	 * device or another device aliases us, use the same group.
	 */
	group = get_pci_alias_group(pdev, (अचिन्हित दीर्घ *)devfns);
	अगर (group)
		वापस group;

	/*
	 * Look क्रम existing groups on non-isolated functions on the same
	 * slot and aliases of those funcions, अगर any.  No need to clear
	 * the search biपंचांगap, the tested devfns are still valid.
	 */
	group = get_pci_function_alias_group(pdev, (अचिन्हित दीर्घ *)devfns);
	अगर (group)
		वापस group;

	/* No shared group found, allocate new */
	वापस iommu_group_alloc();
पूर्ण
EXPORT_SYMBOL_GPL(pci_device_group);

/* Get the IOMMU group क्रम device on fsl-mc bus */
काष्ठा iommu_group *fsl_mc_device_group(काष्ठा device *dev)
अणु
	काष्ठा device *cont_dev = fsl_mc_cont_dev(dev);
	काष्ठा iommu_group *group;

	group = iommu_group_get(cont_dev);
	अगर (!group)
		group = iommu_group_alloc();
	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(fsl_mc_device_group);

अटल पूर्णांक iommu_get_def_करोमुख्य_type(काष्ठा device *dev)
अणु
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;

	अगर (dev_is_pci(dev) && to_pci_dev(dev)->untrusted)
		वापस IOMMU_DOMAIN_DMA;

	अगर (ops->def_करोमुख्य_type)
		वापस ops->def_करोमुख्य_type(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक iommu_group_alloc_शेष_करोमुख्य(काष्ठा bus_type *bus,
					    काष्ठा iommu_group *group,
					    अचिन्हित पूर्णांक type)
अणु
	काष्ठा iommu_करोमुख्य *करोm;

	करोm = __iommu_करोमुख्य_alloc(bus, type);
	अगर (!करोm && type != IOMMU_DOMAIN_DMA) अणु
		करोm = __iommu_करोमुख्य_alloc(bus, IOMMU_DOMAIN_DMA);
		अगर (करोm)
			pr_warn("Failed to allocate default IOMMU domain of type %u for group %s - Falling back to IOMMU_DOMAIN_DMA",
				type, group->name);
	पूर्ण

	अगर (!करोm)
		वापस -ENOMEM;

	group->शेष_करोमुख्य = करोm;
	अगर (!group->करोमुख्य)
		group->करोमुख्य = करोm;
	वापस 0;
पूर्ण

अटल पूर्णांक iommu_alloc_शेष_करोमुख्य(काष्ठा iommu_group *group,
				      काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक type;

	अगर (group->शेष_करोमुख्य)
		वापस 0;

	type = iommu_get_def_करोमुख्य_type(dev) ? : iommu_def_करोमुख्य_type;

	वापस iommu_group_alloc_शेष_करोमुख्य(dev->bus, group, type);
पूर्ण

/**
 * iommu_group_get_क्रम_dev - Find or create the IOMMU group क्रम a device
 * @dev: target device
 *
 * This function is पूर्णांकended to be called by IOMMU drivers and extended to
 * support common, bus-defined algorithms when determining or creating the
 * IOMMU group क्रम a device.  On success, the caller will hold a reference
 * to the वापसed IOMMU group, which will alपढ़ोy include the provided
 * device.  The reference should be released with iommu_group_put().
 */
अटल काष्ठा iommu_group *iommu_group_get_क्रम_dev(काष्ठा device *dev)
अणु
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	group = iommu_group_get(dev);
	अगर (group)
		वापस group;

	अगर (!ops)
		वापस ERR_PTR(-EINVAL);

	group = ops->device_group(dev);
	अगर (WARN_ON_ONCE(group == शून्य))
		वापस ERR_PTR(-EINVAL);

	अगर (IS_ERR(group))
		वापस group;

	ret = iommu_group_add_device(group, dev);
	अगर (ret)
		जाओ out_put_group;

	वापस group;

out_put_group:
	iommu_group_put(group);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा iommu_करोमुख्य *iommu_group_शेष_करोमुख्य(काष्ठा iommu_group *group)
अणु
	वापस group->शेष_करोमुख्य;
पूर्ण

अटल पूर्णांक probe_iommu_group(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा list_head *group_list = data;
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	/* Device is probed alपढ़ोy अगर in a group */
	group = iommu_group_get(dev);
	अगर (group) अणु
		iommu_group_put(group);
		वापस 0;
	पूर्ण

	ret = __iommu_probe_device(dev, group_list);
	अगर (ret == -ENODEV)
		ret = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक हटाओ_iommu_group(काष्ठा device *dev, व्योम *data)
अणु
	iommu_release_device(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक iommu_bus_notअगरier(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ action, व्योम *data)
अणु
	अचिन्हित दीर्घ group_action = 0;
	काष्ठा device *dev = data;
	काष्ठा iommu_group *group;

	/*
	 * ADD/DEL call पूर्णांकo iommu driver ops अगर provided, which may
	 * result in ADD/DEL notअगरiers to group->notअगरier
	 */
	अगर (action == BUS_NOTIFY_ADD_DEVICE) अणु
		पूर्णांक ret;

		ret = iommu_probe_device(dev);
		वापस (ret) ? NOTIFY_DONE : NOTIFY_OK;
	पूर्ण अन्यथा अगर (action == BUS_NOTIFY_REMOVED_DEVICE) अणु
		iommu_release_device(dev);
		वापस NOTIFY_OK;
	पूर्ण

	/*
	 * Reमुख्यing BUS_NOTIFYs get filtered and republished to the
	 * group, अगर anyone is listening
	 */
	group = iommu_group_get(dev);
	अगर (!group)
		वापस 0;

	चयन (action) अणु
	हाल BUS_NOTIFY_BIND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_BIND_DRIVER;
		अवरोध;
	हाल BUS_NOTIFY_BOUND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_BOUND_DRIVER;
		अवरोध;
	हाल BUS_NOTIFY_UNBIND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_UNBIND_DRIVER;
		अवरोध;
	हाल BUS_NOTIFY_UNBOUND_DRIVER:
		group_action = IOMMU_GROUP_NOTIFY_UNBOUND_DRIVER;
		अवरोध;
	पूर्ण

	अगर (group_action)
		blocking_notअगरier_call_chain(&group->notअगरier,
					     group_action, dev);

	iommu_group_put(group);
	वापस 0;
पूर्ण

काष्ठा __group_करोमुख्य_type अणु
	काष्ठा device *dev;
	अचिन्हित पूर्णांक type;
पूर्ण;

अटल पूर्णांक probe_get_शेष_करोमुख्य_type(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा __group_करोमुख्य_type *gtype = data;
	अचिन्हित पूर्णांक type = iommu_get_def_करोमुख्य_type(dev);

	अगर (type) अणु
		अगर (gtype->type && gtype->type != type) अणु
			dev_warn(dev, "Device needs domain type %s, but device %s in the same iommu group requires type %s - using default\n",
				 iommu_करोमुख्य_type_str(type),
				 dev_name(gtype->dev),
				 iommu_करोमुख्य_type_str(gtype->type));
			gtype->type = 0;
		पूर्ण

		अगर (!gtype->dev) अणु
			gtype->dev  = dev;
			gtype->type = type;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम probe_alloc_शेष_करोमुख्य(काष्ठा bus_type *bus,
				       काष्ठा iommu_group *group)
अणु
	काष्ठा __group_करोमुख्य_type gtype;

	स_रखो(&gtype, 0, माप(gtype));

	/* Ask क्रम शेष करोमुख्य requirements of all devices in the group */
	__iommu_group_क्रम_each_dev(group, &gtype,
				   probe_get_शेष_करोमुख्य_type);

	अगर (!gtype.type)
		gtype.type = iommu_def_करोमुख्य_type;

	iommu_group_alloc_शेष_करोमुख्य(bus, group, gtype.type);

पूर्ण

अटल पूर्णांक iommu_group_करो_dma_attach(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = data;
	पूर्णांक ret = 0;

	अगर (!iommu_is_attach_deferred(करोमुख्य, dev))
		ret = __iommu_attach_device(करोमुख्य, dev);

	वापस ret;
पूर्ण

अटल पूर्णांक __iommu_group_dma_attach(काष्ठा iommu_group *group)
अणु
	वापस __iommu_group_क्रम_each_dev(group, group->शेष_करोमुख्य,
					  iommu_group_करो_dma_attach);
पूर्ण

अटल पूर्णांक iommu_group_करो_probe_finalize(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = data;

	अगर (करोमुख्य->ops->probe_finalize)
		करोमुख्य->ops->probe_finalize(dev);

	वापस 0;
पूर्ण

अटल व्योम __iommu_group_dma_finalize(काष्ठा iommu_group *group)
अणु
	__iommu_group_क्रम_each_dev(group, group->शेष_करोमुख्य,
				   iommu_group_करो_probe_finalize);
पूर्ण

अटल पूर्णांक iommu_करो_create_direct_mappings(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iommu_group *group = data;

	iommu_create_device_direct_mappings(group, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक iommu_group_create_direct_mappings(काष्ठा iommu_group *group)
अणु
	वापस __iommu_group_क्रम_each_dev(group, group,
					  iommu_करो_create_direct_mappings);
पूर्ण

पूर्णांक bus_iommu_probe(काष्ठा bus_type *bus)
अणु
	काष्ठा iommu_group *group, *next;
	LIST_HEAD(group_list);
	पूर्णांक ret;

	/*
	 * This code-path करोes not allocate the शेष करोमुख्य when
	 * creating the iommu group, so करो it after the groups are
	 * created.
	 */
	ret = bus_क्रम_each_dev(bus, शून्य, &group_list, probe_iommu_group);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry_safe(group, next, &group_list, entry) अणु
		/* Remove item from the list */
		list_del_init(&group->entry);

		mutex_lock(&group->mutex);

		/* Try to allocate शेष करोमुख्य */
		probe_alloc_शेष_करोमुख्य(bus, group);

		अगर (!group->शेष_करोमुख्य) अणु
			mutex_unlock(&group->mutex);
			जारी;
		पूर्ण

		iommu_group_create_direct_mappings(group);

		ret = __iommu_group_dma_attach(group);

		mutex_unlock(&group->mutex);

		अगर (ret)
			अवरोध;

		__iommu_group_dma_finalize(group);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iommu_bus_init(काष्ठा bus_type *bus, स्थिर काष्ठा iommu_ops *ops)
अणु
	काष्ठा notअगरier_block *nb;
	पूर्णांक err;

	nb = kzalloc(माप(काष्ठा notअगरier_block), GFP_KERNEL);
	अगर (!nb)
		वापस -ENOMEM;

	nb->notअगरier_call = iommu_bus_notअगरier;

	err = bus_रेजिस्टर_notअगरier(bus, nb);
	अगर (err)
		जाओ out_मुक्त;

	err = bus_iommu_probe(bus);
	अगर (err)
		जाओ out_err;


	वापस 0;

out_err:
	/* Clean up */
	bus_क्रम_each_dev(bus, शून्य, शून्य, हटाओ_iommu_group);
	bus_unरेजिस्टर_notअगरier(bus, nb);

out_मुक्त:
	kमुक्त(nb);

	वापस err;
पूर्ण

/**
 * bus_set_iommu - set iommu-callbacks क्रम the bus
 * @bus: bus.
 * @ops: the callbacks provided by the iommu-driver
 *
 * This function is called by an iommu driver to set the iommu methods
 * used क्रम a particular bus. Drivers क्रम devices on that bus can use
 * the iommu-api after these ops are रेजिस्टरed.
 * This special function is needed because IOMMUs are usually devices on
 * the bus itself, so the iommu drivers are not initialized when the bus
 * is set up. With this function the iommu-driver can set the iommu-ops
 * afterwards.
 */
पूर्णांक bus_set_iommu(काष्ठा bus_type *bus, स्थिर काष्ठा iommu_ops *ops)
अणु
	पूर्णांक err;

	अगर (ops == शून्य) अणु
		bus->iommu_ops = शून्य;
		वापस 0;
	पूर्ण

	अगर (bus->iommu_ops != शून्य)
		वापस -EBUSY;

	bus->iommu_ops = ops;

	/* Do IOMMU specअगरic setup क्रम this bus-type */
	err = iommu_bus_init(bus, ops);
	अगर (err)
		bus->iommu_ops = शून्य;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(bus_set_iommu);

bool iommu_present(काष्ठा bus_type *bus)
अणु
	वापस bus->iommu_ops != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_present);

bool iommu_capable(काष्ठा bus_type *bus, क्रमागत iommu_cap cap)
अणु
	अगर (!bus->iommu_ops || !bus->iommu_ops->capable)
		वापस false;

	वापस bus->iommu_ops->capable(cap);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_capable);

/**
 * iommu_set_fault_handler() - set a fault handler क्रम an iommu करोमुख्य
 * @करोमुख्य: iommu करोमुख्य
 * @handler: fault handler
 * @token: user data, will be passed back to the fault handler
 *
 * This function should be used by IOMMU users which want to be notअगरied
 * whenever an IOMMU fault happens.
 *
 * The fault handler itself should वापस 0 on success, and an appropriate
 * error code otherwise.
 */
व्योम iommu_set_fault_handler(काष्ठा iommu_करोमुख्य *करोमुख्य,
					iommu_fault_handler_t handler,
					व्योम *token)
अणु
	BUG_ON(!करोमुख्य);

	करोमुख्य->handler = handler;
	करोमुख्य->handler_token = token;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_set_fault_handler);

अटल काष्ठा iommu_करोमुख्य *__iommu_करोमुख्य_alloc(काष्ठा bus_type *bus,
						 अचिन्हित type)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;

	अगर (bus == शून्य || bus->iommu_ops == शून्य)
		वापस शून्य;

	करोमुख्य = bus->iommu_ops->करोमुख्य_alloc(type);
	अगर (!करोमुख्य)
		वापस शून्य;

	करोमुख्य->ops  = bus->iommu_ops;
	करोमुख्य->type = type;
	/* Assume all sizes by शेष; the driver may override this later */
	करोमुख्य->pgsize_biपंचांगap  = bus->iommu_ops->pgsize_biपंचांगap;

	वापस करोमुख्य;
पूर्ण

काष्ठा iommu_करोमुख्य *iommu_करोमुख्य_alloc(काष्ठा bus_type *bus)
अणु
	वापस __iommu_करोमुख्य_alloc(bus, IOMMU_DOMAIN_UNMANAGED);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_करोमुख्य_alloc);

व्योम iommu_करोमुख्य_मुक्त(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	करोमुख्य->ops->करोमुख्य_मुक्त(करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_करोमुख्य_मुक्त);

अटल पूर्णांक __iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (unlikely(करोमुख्य->ops->attach_dev == शून्य))
		वापस -ENODEV;

	ret = करोमुख्य->ops->attach_dev(करोमुख्य, dev);
	अगर (!ret)
		trace_attach_device_to_करोमुख्य(dev);
	वापस ret;
पूर्ण

पूर्णांक iommu_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group;
	पूर्णांक ret;

	group = iommu_group_get(dev);
	अगर (!group)
		वापस -ENODEV;

	/*
	 * Lock the group to make sure the device-count करोesn't
	 * change जबतक we are attaching
	 */
	mutex_lock(&group->mutex);
	ret = -EINVAL;
	अगर (iommu_group_device_count(group) != 1)
		जाओ out_unlock;

	ret = __iommu_attach_group(करोमुख्य, group);

out_unlock:
	mutex_unlock(&group->mutex);
	iommu_group_put(group);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_attach_device);

पूर्णांक iommu_deferred_attach(काष्ठा device *dev, काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	स्थिर काष्ठा iommu_ops *ops = करोमुख्य->ops;

	अगर (ops->is_attach_deferred && ops->is_attach_deferred(करोमुख्य, dev))
		वापस __iommu_attach_device(करोमुख्य, dev);

	वापस 0;
पूर्ण

/*
 * Check flags and other user provided data क्रम valid combinations. We also
 * make sure no reserved fields or unused flags are set. This is to ensure
 * not अवरोधing userspace in the future when these fields or flags are used.
 */
अटल पूर्णांक iommu_check_cache_invl_data(काष्ठा iommu_cache_invalidate_info *info)
अणु
	u32 mask;
	पूर्णांक i;

	अगर (info->version != IOMMU_CACHE_INVALIDATE_INFO_VERSION_1)
		वापस -EINVAL;

	mask = (1 << IOMMU_CACHE_INV_TYPE_NR) - 1;
	अगर (info->cache & ~mask)
		वापस -EINVAL;

	अगर (info->granularity >= IOMMU_INV_GRANU_NR)
		वापस -EINVAL;

	चयन (info->granularity) अणु
	हाल IOMMU_INV_GRANU_ADDR:
		अगर (info->cache & IOMMU_CACHE_INV_TYPE_PASID)
			वापस -EINVAL;

		mask = IOMMU_INV_ADDR_FLAGS_PASID |
			IOMMU_INV_ADDR_FLAGS_ARCHID |
			IOMMU_INV_ADDR_FLAGS_LEAF;

		अगर (info->granu.addr_info.flags & ~mask)
			वापस -EINVAL;
		अवरोध;
	हाल IOMMU_INV_GRANU_PASID:
		mask = IOMMU_INV_PASID_FLAGS_PASID |
			IOMMU_INV_PASID_FLAGS_ARCHID;
		अगर (info->granu.pasid_info.flags & ~mask)
			वापस -EINVAL;

		अवरोध;
	हाल IOMMU_INV_GRANU_DOMAIN:
		अगर (info->cache & IOMMU_CACHE_INV_TYPE_DEV_IOTLB)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Check reserved padding fields */
	क्रम (i = 0; i < माप(info->padding); i++) अणु
		अगर (info->padding[i])
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iommu_uapi_cache_invalidate(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
				व्योम __user *uinfo)
अणु
	काष्ठा iommu_cache_invalidate_info inv_info = अणु 0 पूर्ण;
	u32 minsz;
	पूर्णांक ret;

	अगर (unlikely(!करोमुख्य->ops->cache_invalidate))
		वापस -ENODEV;

	/*
	 * No new spaces can be added beक्रमe the variable sized जोड़, the
	 * minimum size is the offset to the जोड़.
	 */
	minsz = दुरत्व(काष्ठा iommu_cache_invalidate_info, granu);

	/* Copy minsz from user to get flags and argsz */
	अगर (copy_from_user(&inv_info, uinfo, minsz))
		वापस -EFAULT;

	/* Fields beक्रमe the variable size जोड़ are mandatory */
	अगर (inv_info.argsz < minsz)
		वापस -EINVAL;

	/* PASID and address granu require additional info beyond minsz */
	अगर (inv_info.granularity == IOMMU_INV_GRANU_PASID &&
	    inv_info.argsz < दुरत्वend(काष्ठा iommu_cache_invalidate_info, granu.pasid_info))
		वापस -EINVAL;

	अगर (inv_info.granularity == IOMMU_INV_GRANU_ADDR &&
	    inv_info.argsz < दुरत्वend(काष्ठा iommu_cache_invalidate_info, granu.addr_info))
		वापस -EINVAL;

	/*
	 * User might be using a newer UAPI header which has a larger data
	 * size, we shall support the existing flags within the current
	 * size. Copy the reमुख्यing user data _after_ minsz but not more
	 * than the current kernel supported size.
	 */
	अगर (copy_from_user((व्योम *)&inv_info + minsz, uinfo + minsz,
			   min_t(u32, inv_info.argsz, माप(inv_info)) - minsz))
		वापस -EFAULT;

	/* Now the argsz is validated, check the content */
	ret = iommu_check_cache_invl_data(&inv_info);
	अगर (ret)
		वापस ret;

	वापस करोमुख्य->ops->cache_invalidate(करोमुख्य, dev, &inv_info);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_uapi_cache_invalidate);

अटल पूर्णांक iommu_check_bind_data(काष्ठा iommu_gpasid_bind_data *data)
अणु
	u64 mask;
	पूर्णांक i;

	अगर (data->version != IOMMU_GPASID_BIND_VERSION_1)
		वापस -EINVAL;

	/* Check the range of supported क्रमmats */
	अगर (data->क्रमmat >= IOMMU_PASID_FORMAT_LAST)
		वापस -EINVAL;

	/* Check all flags */
	mask = IOMMU_SVA_GPASID_VAL;
	अगर (data->flags & ~mask)
		वापस -EINVAL;

	/* Check reserved padding fields */
	क्रम (i = 0; i < माप(data->padding); i++) अणु
		अगर (data->padding[i])
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iommu_sva_prepare_bind_data(व्योम __user *udata,
				       काष्ठा iommu_gpasid_bind_data *data)
अणु
	u32 minsz;

	/*
	 * No new spaces can be added beक्रमe the variable sized जोड़, the
	 * minimum size is the offset to the जोड़.
	 */
	minsz = दुरत्व(काष्ठा iommu_gpasid_bind_data, venकरोr);

	/* Copy minsz from user to get flags and argsz */
	अगर (copy_from_user(data, udata, minsz))
		वापस -EFAULT;

	/* Fields beक्रमe the variable size जोड़ are mandatory */
	अगर (data->argsz < minsz)
		वापस -EINVAL;
	/*
	 * User might be using a newer UAPI header, we shall let IOMMU venकरोr
	 * driver decide on what size it needs. Since the guest PASID bind data
	 * can be venकरोr specअगरic, larger argsz could be the result of extension
	 * क्रम one venकरोr but it should not affect another venकरोr.
	 * Copy the reमुख्यing user data _after_ minsz
	 */
	अगर (copy_from_user((व्योम *)data + minsz, udata + minsz,
			   min_t(u32, data->argsz, माप(*data)) - minsz))
		वापस -EFAULT;

	वापस iommu_check_bind_data(data);
पूर्ण

पूर्णांक iommu_uapi_sva_bind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			       व्योम __user *udata)
अणु
	काष्ठा iommu_gpasid_bind_data data = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (unlikely(!करोमुख्य->ops->sva_bind_gpasid))
		वापस -ENODEV;

	ret = iommu_sva_prepare_bind_data(udata, &data);
	अगर (ret)
		वापस ret;

	वापस करोमुख्य->ops->sva_bind_gpasid(करोमुख्य, dev, &data);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_uapi_sva_bind_gpasid);

पूर्णांक iommu_sva_unbind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
			     ioasid_t pasid)
अणु
	अगर (unlikely(!करोमुख्य->ops->sva_unbind_gpasid))
		वापस -ENODEV;

	वापस करोमुख्य->ops->sva_unbind_gpasid(dev, pasid);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_sva_unbind_gpasid);

पूर्णांक iommu_uapi_sva_unbind_gpasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
				 व्योम __user *udata)
अणु
	काष्ठा iommu_gpasid_bind_data data = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (unlikely(!करोमुख्य->ops->sva_bind_gpasid))
		वापस -ENODEV;

	ret = iommu_sva_prepare_bind_data(udata, &data);
	अगर (ret)
		वापस ret;

	वापस iommu_sva_unbind_gpasid(करोमुख्य, dev, data.hpasid);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_uapi_sva_unbind_gpasid);

अटल व्योम __iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य,
				  काष्ठा device *dev)
अणु
	अगर (iommu_is_attach_deferred(करोमुख्य, dev))
		वापस;

	अगर (unlikely(करोमुख्य->ops->detach_dev == शून्य))
		वापस;

	करोमुख्य->ops->detach_dev(करोमुख्य, dev);
	trace_detach_device_from_करोमुख्य(dev);
पूर्ण

व्योम iommu_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group;

	group = iommu_group_get(dev);
	अगर (!group)
		वापस;

	mutex_lock(&group->mutex);
	अगर (iommu_group_device_count(group) != 1) अणु
		WARN_ON(1);
		जाओ out_unlock;
	पूर्ण

	__iommu_detach_group(करोमुख्य, group);

out_unlock:
	mutex_unlock(&group->mutex);
	iommu_group_put(group);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_detach_device);

काष्ठा iommu_करोमुख्य *iommu_get_करोमुख्य_क्रम_dev(काष्ठा device *dev)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा iommu_group *group;

	group = iommu_group_get(dev);
	अगर (!group)
		वापस शून्य;

	करोमुख्य = group->करोमुख्य;

	iommu_group_put(group);

	वापस करोमुख्य;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_get_करोमुख्य_क्रम_dev);

/*
 * For IOMMU_DOMAIN_DMA implementations which alपढ़ोy provide their own
 * guarantees that the group and its शेष करोमुख्य are valid and correct.
 */
काष्ठा iommu_करोमुख्य *iommu_get_dma_करोमुख्य(काष्ठा device *dev)
अणु
	वापस dev->iommu_group->शेष_करोमुख्य;
पूर्ण

/*
 * IOMMU groups are really the natural working unit of the IOMMU, but
 * the IOMMU API works on करोमुख्यs and devices.  Bridge that gap by
 * iterating over the devices in a group.  Ideally we'd have a single
 * device which represents the requestor ID of the group, but we also
 * allow IOMMU drivers to create policy defined minimum sets, where
 * the physical hardware may be able to distiguish members, but we
 * wish to group them at a higher level (ex. untrusted multi-function
 * PCI devices).  Thus we attach each device.
 */
अटल पूर्णांक iommu_group_करो_attach_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = data;

	वापस __iommu_attach_device(करोमुख्य, dev);
पूर्ण

अटल पूर्णांक __iommu_attach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
				काष्ठा iommu_group *group)
अणु
	पूर्णांक ret;

	अगर (group->शेष_करोमुख्य && group->करोमुख्य != group->शेष_करोमुख्य)
		वापस -EBUSY;

	ret = __iommu_group_क्रम_each_dev(group, करोमुख्य,
					 iommu_group_करो_attach_device);
	अगर (ret == 0)
		group->करोमुख्य = करोमुख्य;

	वापस ret;
पूर्ण

पूर्णांक iommu_attach_group(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा iommu_group *group)
अणु
	पूर्णांक ret;

	mutex_lock(&group->mutex);
	ret = __iommu_attach_group(करोमुख्य, group);
	mutex_unlock(&group->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_attach_group);

अटल पूर्णांक iommu_group_करो_detach_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = data;

	__iommu_detach_device(करोमुख्य, dev);

	वापस 0;
पूर्ण

अटल व्योम __iommu_detach_group(काष्ठा iommu_करोमुख्य *करोमुख्य,
				 काष्ठा iommu_group *group)
अणु
	पूर्णांक ret;

	अगर (!group->शेष_करोमुख्य) अणु
		__iommu_group_क्रम_each_dev(group, करोमुख्य,
					   iommu_group_करो_detach_device);
		group->करोमुख्य = शून्य;
		वापस;
	पूर्ण

	अगर (group->करोमुख्य == group->शेष_करोमुख्य)
		वापस;

	/* Detach by re-attaching to the शेष करोमुख्य */
	ret = __iommu_group_क्रम_each_dev(group, group->शेष_करोमुख्य,
					 iommu_group_करो_attach_device);
	अगर (ret != 0)
		WARN_ON(1);
	अन्यथा
		group->करोमुख्य = group->शेष_करोमुख्य;
पूर्ण

व्योम iommu_detach_group(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा iommu_group *group)
अणु
	mutex_lock(&group->mutex);
	__iommu_detach_group(करोमुख्य, group);
	mutex_unlock(&group->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_detach_group);

phys_addr_t iommu_iova_to_phys(काष्ठा iommu_करोमुख्य *करोमुख्य, dma_addr_t iova)
अणु
	अगर (unlikely(करोमुख्य->ops->iova_to_phys == शून्य))
		वापस 0;

	वापस करोमुख्य->ops->iova_to_phys(करोमुख्य, iova);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_iova_to_phys);

अटल माप_प्रकार iommu_pgsize(काष्ठा iommu_करोमुख्य *करोमुख्य,
			   अचिन्हित दीर्घ addr_merge, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक pgsize_idx;
	माप_प्रकार pgsize;

	/* Max page size that still fits पूर्णांकo 'size' */
	pgsize_idx = __fls(size);

	/* need to consider alignment requirements ? */
	अगर (likely(addr_merge)) अणु
		/* Max page size allowed by address */
		अचिन्हित पूर्णांक align_pgsize_idx = __ffs(addr_merge);
		pgsize_idx = min(pgsize_idx, align_pgsize_idx);
	पूर्ण

	/* build a mask of acceptable page sizes */
	pgsize = (1UL << (pgsize_idx + 1)) - 1;

	/* throw away page sizes not supported by the hardware */
	pgsize &= करोमुख्य->pgsize_biपंचांगap;

	/* make sure we're still sane */
	BUG_ON(!pgsize);

	/* pick the biggest page */
	pgsize_idx = __fls(pgsize);
	pgsize = 1UL << pgsize_idx;

	वापस pgsize;
पूर्ण

अटल पूर्णांक __iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		       phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	स्थिर काष्ठा iommu_ops *ops = करोमुख्य->ops;
	अचिन्हित दीर्घ orig_iova = iova;
	अचिन्हित पूर्णांक min_pagesz;
	माप_प्रकार orig_size = size;
	phys_addr_t orig_paddr = paddr;
	पूर्णांक ret = 0;

	अगर (unlikely(ops->map == शून्य ||
		     करोमुख्य->pgsize_biपंचांगap == 0UL))
		वापस -ENODEV;

	अगर (unlikely(!(करोमुख्य->type & __IOMMU_DOMAIN_PAGING)))
		वापस -EINVAL;

	/* find out the minimum page size supported */
	min_pagesz = 1 << __ffs(करोमुख्य->pgsize_biपंचांगap);

	/*
	 * both the भव address and the physical one, as well as
	 * the size of the mapping, must be aligned (at least) to the
	 * size of the smallest page supported by the hardware
	 */
	अगर (!IS_ALIGNED(iova | paddr | size, min_pagesz)) अणु
		pr_err("unaligned: iova 0x%lx pa %pa size 0x%zx min_pagesz 0x%x\n",
		       iova, &paddr, size, min_pagesz);
		वापस -EINVAL;
	पूर्ण

	pr_debug("map: iova 0x%lx pa %pa size 0x%zx\n", iova, &paddr, size);

	जबतक (size) अणु
		माप_प्रकार pgsize = iommu_pgsize(करोमुख्य, iova | paddr, size);

		pr_debug("mapping: iova 0x%lx pa %pa pgsize 0x%zx\n",
			 iova, &paddr, pgsize);
		ret = ops->map(करोमुख्य, iova, paddr, pgsize, prot, gfp);

		अगर (ret)
			अवरोध;

		iova += pgsize;
		paddr += pgsize;
		size -= pgsize;
	पूर्ण

	/* unroll mapping in हाल something went wrong */
	अगर (ret)
		iommu_unmap(करोमुख्य, orig_iova, orig_size - size);
	अन्यथा
		trace_map(orig_iova, orig_paddr, orig_size);

	वापस ret;
पूर्ण

अटल पूर्णांक _iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		      phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot, gfp_t gfp)
अणु
	स्थिर काष्ठा iommu_ops *ops = करोमुख्य->ops;
	पूर्णांक ret;

	ret = __iommu_map(करोमुख्य, iova, paddr, size, prot, gfp);
	अगर (ret == 0 && ops->iotlb_sync_map)
		ops->iotlb_sync_map(करोमुख्य, iova, size);

	वापस ret;
पूर्ण

पूर्णांक iommu_map(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
	      phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot)
अणु
	might_sleep();
	वापस _iommu_map(करोमुख्य, iova, paddr, size, prot, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_map);

पूर्णांक iommu_map_atomic(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
	      phys_addr_t paddr, माप_प्रकार size, पूर्णांक prot)
अणु
	वापस _iommu_map(करोमुख्य, iova, paddr, size, prot, GFP_ATOMIC);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_map_atomic);

अटल माप_प्रकार __iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य,
			    अचिन्हित दीर्घ iova, माप_प्रकार size,
			    काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	स्थिर काष्ठा iommu_ops *ops = करोमुख्य->ops;
	माप_प्रकार unmapped_page, unmapped = 0;
	अचिन्हित दीर्घ orig_iova = iova;
	अचिन्हित पूर्णांक min_pagesz;

	अगर (unlikely(ops->unmap == शून्य ||
		     करोमुख्य->pgsize_biपंचांगap == 0UL))
		वापस 0;

	अगर (unlikely(!(करोमुख्य->type & __IOMMU_DOMAIN_PAGING)))
		वापस 0;

	/* find out the minimum page size supported */
	min_pagesz = 1 << __ffs(करोमुख्य->pgsize_biपंचांगap);

	/*
	 * The भव address, as well as the size of the mapping, must be
	 * aligned (at least) to the size of the smallest page supported
	 * by the hardware
	 */
	अगर (!IS_ALIGNED(iova | size, min_pagesz)) अणु
		pr_err("unaligned: iova 0x%lx size 0x%zx min_pagesz 0x%x\n",
		       iova, size, min_pagesz);
		वापस 0;
	पूर्ण

	pr_debug("unmap this: iova 0x%lx size 0x%zx\n", iova, size);

	/*
	 * Keep iterating until we either unmap 'size' bytes (or more)
	 * or we hit an area that isn't mapped.
	 */
	जबतक (unmapped < size) अणु
		माप_प्रकार pgsize = iommu_pgsize(करोमुख्य, iova, size - unmapped);

		unmapped_page = ops->unmap(करोमुख्य, iova, pgsize, iotlb_gather);
		अगर (!unmapped_page)
			अवरोध;

		pr_debug("unmapped: iova 0x%lx size 0x%zx\n",
			 iova, unmapped_page);

		iova += unmapped_page;
		unmapped += unmapped_page;
	पूर्ण

	trace_unmap(orig_iova, size, unmapped);
	वापस unmapped;
पूर्ण

माप_प्रकार iommu_unmap(काष्ठा iommu_करोमुख्य *करोमुख्य,
		   अचिन्हित दीर्घ iova, माप_प्रकार size)
अणु
	काष्ठा iommu_iotlb_gather iotlb_gather;
	माप_प्रकार ret;

	iommu_iotlb_gather_init(&iotlb_gather);
	ret = __iommu_unmap(करोमुख्य, iova, size, &iotlb_gather);
	iommu_iotlb_sync(करोमुख्य, &iotlb_gather);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_unmap);

माप_प्रकार iommu_unmap_fast(काष्ठा iommu_करोमुख्य *करोमुख्य,
			अचिन्हित दीर्घ iova, माप_प्रकार size,
			काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	वापस __iommu_unmap(करोमुख्य, iova, size, iotlb_gather);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_unmap_fast);

अटल माप_प्रकार __iommu_map_sg(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
			     काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents, पूर्णांक prot,
			     gfp_t gfp)
अणु
	स्थिर काष्ठा iommu_ops *ops = करोमुख्य->ops;
	माप_प्रकार len = 0, mapped = 0;
	phys_addr_t start;
	अचिन्हित पूर्णांक i = 0;
	पूर्णांक ret;

	जबतक (i <= nents) अणु
		phys_addr_t s_phys = sg_phys(sg);

		अगर (len && s_phys != start + len) अणु
			ret = __iommu_map(करोमुख्य, iova + mapped, start,
					len, prot, gfp);

			अगर (ret)
				जाओ out_err;

			mapped += len;
			len = 0;
		पूर्ण

		अगर (len) अणु
			len += sg->length;
		पूर्ण अन्यथा अणु
			len = sg->length;
			start = s_phys;
		पूर्ण

		अगर (++i < nents)
			sg = sg_next(sg);
	पूर्ण

	अगर (ops->iotlb_sync_map)
		ops->iotlb_sync_map(करोमुख्य, iova, mapped);
	वापस mapped;

out_err:
	/* unकरो mappings alपढ़ोy करोne */
	iommu_unmap(करोमुख्य, iova, mapped);

	वापस 0;

पूर्ण

माप_प्रकार iommu_map_sg(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		    काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents, पूर्णांक prot)
अणु
	might_sleep();
	वापस __iommu_map_sg(करोमुख्य, iova, sg, nents, prot, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_map_sg);

माप_प्रकार iommu_map_sg_atomic(काष्ठा iommu_करोमुख्य *करोमुख्य, अचिन्हित दीर्घ iova,
		    काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nents, पूर्णांक prot)
अणु
	वापस __iommu_map_sg(करोमुख्य, iova, sg, nents, prot, GFP_ATOMIC);
पूर्ण

/**
 * report_iommu_fault() - report about an IOMMU fault to the IOMMU framework
 * @करोमुख्य: the iommu करोमुख्य where the fault has happened
 * @dev: the device where the fault has happened
 * @iova: the faulting address
 * @flags: mmu fault flags (e.g. IOMMU_FAULT_READ/IOMMU_FAULT_WRITE/...)
 *
 * This function should be called by the low-level IOMMU implementations
 * whenever IOMMU faults happen, to allow high-level users, that are
 * पूर्णांकerested in such events, to know about them.
 *
 * This event may be useful क्रम several possible use हालs:
 * - mere logging of the event
 * - dynamic TLB/PTE loading
 * - अगर restarting of the faulting device is required
 *
 * Returns 0 on success and an appropriate error code otherwise (अगर dynamic
 * PTE/TLB loading will one day be supported, implementations will be able
 * to tell whether it succeeded or not according to this वापस value).
 *
 * Specअगरically, -ENOSYS is वापसed अगर a fault handler isn't installed
 * (though fault handlers can also वापस -ENOSYS, in हाल they want to
 * elicit the शेष behavior of the IOMMU drivers).
 */
पूर्णांक report_iommu_fault(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev,
		       अचिन्हित दीर्घ iova, पूर्णांक flags)
अणु
	पूर्णांक ret = -ENOSYS;

	/*
	 * अगर upper layers showed पूर्णांकerest and installed a fault handler,
	 * invoke it.
	 */
	अगर (करोमुख्य->handler)
		ret = करोमुख्य->handler(करोमुख्य, dev, iova, flags,
						करोमुख्य->handler_token);

	trace_io_page_fault(dev, iova, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(report_iommu_fault);

अटल पूर्णांक __init iommu_init(व्योम)
अणु
	iommu_group_kset = kset_create_and_add("iommu_groups",
					       शून्य, kernel_kobj);
	BUG_ON(!iommu_group_kset);

	iommu_debugfs_setup();

	वापस 0;
पूर्ण
core_initcall(iommu_init);

पूर्णांक iommu_enable_nesting(काष्ठा iommu_करोमुख्य *करोमुख्य)
अणु
	अगर (करोमुख्य->type != IOMMU_DOMAIN_UNMANAGED)
		वापस -EINVAL;
	अगर (!करोमुख्य->ops->enable_nesting)
		वापस -EINVAL;
	वापस करोमुख्य->ops->enable_nesting(करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_enable_nesting);

पूर्णांक iommu_set_pgtable_quirks(काष्ठा iommu_करोमुख्य *करोमुख्य,
		अचिन्हित दीर्घ quirk)
अणु
	अगर (करोमुख्य->type != IOMMU_DOMAIN_UNMANAGED)
		वापस -EINVAL;
	अगर (!करोमुख्य->ops->set_pgtable_quirks)
		वापस -EINVAL;
	वापस करोमुख्य->ops->set_pgtable_quirks(करोमुख्य, quirk);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_set_pgtable_quirks);

व्योम iommu_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *list)
अणु
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;

	अगर (ops && ops->get_resv_regions)
		ops->get_resv_regions(dev, list);
पूर्ण

व्योम iommu_put_resv_regions(काष्ठा device *dev, काष्ठा list_head *list)
अणु
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;

	अगर (ops && ops->put_resv_regions)
		ops->put_resv_regions(dev, list);
पूर्ण

/**
 * generic_iommu_put_resv_regions - Reserved region driver helper
 * @dev: device क्रम which to मुक्त reserved regions
 * @list: reserved region list क्रम device
 *
 * IOMMU drivers can use this to implement their .put_resv_regions() callback
 * क्रम simple reservations. Memory allocated क्रम each reserved region will be
 * मुक्तd. If an IOMMU driver allocates additional resources per region, it is
 * going to have to implement a custom callback.
 */
व्योम generic_iommu_put_resv_regions(काष्ठा device *dev, काष्ठा list_head *list)
अणु
	काष्ठा iommu_resv_region *entry, *next;

	list_क्रम_each_entry_safe(entry, next, list, list)
		kमुक्त(entry);
पूर्ण
EXPORT_SYMBOL(generic_iommu_put_resv_regions);

काष्ठा iommu_resv_region *iommu_alloc_resv_region(phys_addr_t start,
						  माप_प्रकार length, पूर्णांक prot,
						  क्रमागत iommu_resv_type type)
अणु
	काष्ठा iommu_resv_region *region;

	region = kzalloc(माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस शून्य;

	INIT_LIST_HEAD(&region->list);
	region->start = start;
	region->length = length;
	region->prot = prot;
	region->type = type;
	वापस region;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_alloc_resv_region);

व्योम iommu_set_शेष_passthrough(bool cmd_line)
अणु
	अगर (cmd_line)
		iommu_cmd_line |= IOMMU_CMD_LINE_DMA_API;
	iommu_def_करोमुख्य_type = IOMMU_DOMAIN_IDENTITY;
पूर्ण

व्योम iommu_set_शेष_translated(bool cmd_line)
अणु
	अगर (cmd_line)
		iommu_cmd_line |= IOMMU_CMD_LINE_DMA_API;
	iommu_def_करोमुख्य_type = IOMMU_DOMAIN_DMA;
पूर्ण

bool iommu_शेष_passthrough(व्योम)
अणु
	वापस iommu_def_करोमुख्य_type == IOMMU_DOMAIN_IDENTITY;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_शेष_passthrough);

स्थिर काष्ठा iommu_ops *iommu_ops_from_fwnode(काष्ठा fwnode_handle *fwnode)
अणु
	स्थिर काष्ठा iommu_ops *ops = शून्य;
	काष्ठा iommu_device *iommu;

	spin_lock(&iommu_device_lock);
	list_क्रम_each_entry(iommu, &iommu_device_list, list)
		अगर (iommu->fwnode == fwnode) अणु
			ops = iommu->ops;
			अवरोध;
		पूर्ण
	spin_unlock(&iommu_device_lock);
	वापस ops;
पूर्ण

पूर्णांक iommu_fwspec_init(काष्ठा device *dev, काष्ठा fwnode_handle *iommu_fwnode,
		      स्थिर काष्ठा iommu_ops *ops)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (fwspec)
		वापस ops == fwspec->ops ? 0 : -EINVAL;

	अगर (!dev_iommu_get(dev))
		वापस -ENOMEM;

	/* Pपुनः_स्मृतिate क्रम the overwhelmingly common हाल of 1 ID */
	fwspec = kzalloc(काष्ठा_size(fwspec, ids, 1), GFP_KERNEL);
	अगर (!fwspec)
		वापस -ENOMEM;

	of_node_get(to_of_node(iommu_fwnode));
	fwspec->iommu_fwnode = iommu_fwnode;
	fwspec->ops = ops;
	dev_iommu_fwspec_set(dev, fwspec);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_fwspec_init);

व्योम iommu_fwspec_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	अगर (fwspec) अणु
		fwnode_handle_put(fwspec->iommu_fwnode);
		kमुक्त(fwspec);
		dev_iommu_fwspec_set(dev, शून्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iommu_fwspec_मुक्त);

पूर्णांक iommu_fwspec_add_ids(काष्ठा device *dev, u32 *ids, पूर्णांक num_ids)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	पूर्णांक i, new_num;

	अगर (!fwspec)
		वापस -EINVAL;

	new_num = fwspec->num_ids + num_ids;
	अगर (new_num > 1) अणु
		fwspec = kपुनः_स्मृति(fwspec, काष्ठा_size(fwspec, ids, new_num),
				  GFP_KERNEL);
		अगर (!fwspec)
			वापस -ENOMEM;

		dev_iommu_fwspec_set(dev, fwspec);
	पूर्ण

	क्रम (i = 0; i < num_ids; i++)
		fwspec->ids[fwspec->num_ids + i] = ids[i];

	fwspec->num_ids = new_num;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_fwspec_add_ids);

/*
 * Per device IOMMU features.
 */
पूर्णांक iommu_dev_enable_feature(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	अगर (dev->iommu && dev->iommu->iommu_dev) अणु
		स्थिर काष्ठा iommu_ops *ops = dev->iommu->iommu_dev->ops;

		अगर (ops->dev_enable_feat)
			वापस ops->dev_enable_feat(dev, feat);
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_dev_enable_feature);

/*
 * The device drivers should करो the necessary cleanups beक्रमe calling this.
 * For example, beक्रमe disabling the aux-करोमुख्य feature, the device driver
 * should detach all aux-करोमुख्यs. Otherwise, this will वापस -EBUSY.
 */
पूर्णांक iommu_dev_disable_feature(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	अगर (dev->iommu && dev->iommu->iommu_dev) अणु
		स्थिर काष्ठा iommu_ops *ops = dev->iommu->iommu_dev->ops;

		अगर (ops->dev_disable_feat)
			वापस ops->dev_disable_feat(dev, feat);
	पूर्ण

	वापस -EBUSY;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_dev_disable_feature);

bool iommu_dev_feature_enabled(काष्ठा device *dev, क्रमागत iommu_dev_features feat)
अणु
	अगर (dev->iommu && dev->iommu->iommu_dev) अणु
		स्थिर काष्ठा iommu_ops *ops = dev->iommu->iommu_dev->ops;

		अगर (ops->dev_feat_enabled)
			वापस ops->dev_feat_enabled(dev, feat);
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_dev_feature_enabled);

/*
 * Aux-करोमुख्य specअगरic attach/detach.
 *
 * Only works अगर iommu_dev_feature_enabled(dev, IOMMU_DEV_FEAT_AUX) वापसs
 * true. Also, as दीर्घ as करोमुख्यs are attached to a device through this
 * पूर्णांकerface, any tries to call iommu_attach_device() should fail
 * (iommu_detach_device() can't fail, so we fail when trying to re-attach).
 * This should make us safe against a device being attached to a guest as a
 * whole जबतक there are still pasid users on it (aux and sva).
 */
पूर्णांक iommu_aux_attach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (करोमुख्य->ops->aux_attach_dev)
		ret = करोमुख्य->ops->aux_attach_dev(करोमुख्य, dev);

	अगर (!ret)
		trace_attach_device_to_करोमुख्य(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_aux_attach_device);

व्योम iommu_aux_detach_device(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	अगर (करोमुख्य->ops->aux_detach_dev) अणु
		करोमुख्य->ops->aux_detach_dev(करोमुख्य, dev);
		trace_detach_device_from_करोमुख्य(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(iommu_aux_detach_device);

पूर्णांक iommu_aux_get_pasid(काष्ठा iommu_करोमुख्य *करोमुख्य, काष्ठा device *dev)
अणु
	पूर्णांक ret = -ENODEV;

	अगर (करोमुख्य->ops->aux_get_pasid)
		ret = करोमुख्य->ops->aux_get_pasid(करोमुख्य, dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_aux_get_pasid);

/**
 * iommu_sva_bind_device() - Bind a process address space to a device
 * @dev: the device
 * @mm: the mm to bind, caller must hold a reference to it
 *
 * Create a bond between device and address space, allowing the device to access
 * the mm using the वापसed PASID. If a bond alपढ़ोy exists between @device and
 * @mm, it is वापसed and an additional reference is taken. Caller must call
 * iommu_sva_unbind_device() to release each reference.
 *
 * iommu_dev_enable_feature(dev, IOMMU_DEV_FEAT_SVA) must be called first, to
 * initialize the required SVA features.
 *
 * On error, वापसs an ERR_PTR value.
 */
काष्ठा iommu_sva *
iommu_sva_bind_device(काष्ठा device *dev, काष्ठा mm_काष्ठा *mm, व्योम *drvdata)
अणु
	काष्ठा iommu_group *group;
	काष्ठा iommu_sva *handle = ERR_PTR(-EINVAL);
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;

	अगर (!ops || !ops->sva_bind)
		वापस ERR_PTR(-ENODEV);

	group = iommu_group_get(dev);
	अगर (!group)
		वापस ERR_PTR(-ENODEV);

	/* Ensure device count and करोमुख्य करोn't change while we're binding */
	mutex_lock(&group->mutex);

	/*
	 * To keep things simple, SVA currently करोesn't support IOMMU groups
	 * with more than one device. Existing SVA-capable प्रणालीs are not
	 * affected by the problems that required IOMMU groups (lack of ACS
	 * isolation, device ID aliasing and other hardware issues).
	 */
	अगर (iommu_group_device_count(group) != 1)
		जाओ out_unlock;

	handle = ops->sva_bind(dev, mm, drvdata);

out_unlock:
	mutex_unlock(&group->mutex);
	iommu_group_put(group);

	वापस handle;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_sva_bind_device);

/**
 * iommu_sva_unbind_device() - Remove a bond created with iommu_sva_bind_device
 * @handle: the handle वापसed by iommu_sva_bind_device()
 *
 * Put reference to a bond between device and address space. The device should
 * not be issuing any more transaction क्रम this PASID. All outstanding page
 * requests क्रम this PASID must have been flushed to the IOMMU.
 */
व्योम iommu_sva_unbind_device(काष्ठा iommu_sva *handle)
अणु
	काष्ठा iommu_group *group;
	काष्ठा device *dev = handle->dev;
	स्थिर काष्ठा iommu_ops *ops = dev->bus->iommu_ops;

	अगर (!ops || !ops->sva_unbind)
		वापस;

	group = iommu_group_get(dev);
	अगर (!group)
		वापस;

	mutex_lock(&group->mutex);
	ops->sva_unbind(handle);
	mutex_unlock(&group->mutex);

	iommu_group_put(group);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_sva_unbind_device);

u32 iommu_sva_get_pasid(काष्ठा iommu_sva *handle)
अणु
	स्थिर काष्ठा iommu_ops *ops = handle->dev->bus->iommu_ops;

	अगर (!ops || !ops->sva_get_pasid)
		वापस IOMMU_PASID_INVALID;

	वापस ops->sva_get_pasid(handle);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_sva_get_pasid);

/*
 * Changes the शेष करोमुख्य of an iommu group that has *only* one device
 *
 * @group: The group क्रम which the शेष करोमुख्य should be changed
 * @prev_dev: The device in the group (this is used to make sure that the device
 *	 hasn't changed after the caller has called this function)
 * @type: The type of the new शेष करोमुख्य that माला_लो associated with the group
 *
 * Returns 0 on success and error code on failure
 *
 * Note:
 * 1. Presently, this function is called only when user requests to change the
 *    group's शेष करोमुख्य type through /sys/kernel/iommu_groups/<grp_id>/type
 *    Please take a बंदr look अगर पूर्णांकended to use क्रम other purposes.
 */
अटल पूर्णांक iommu_change_dev_def_करोमुख्य(काष्ठा iommu_group *group,
				       काष्ठा device *prev_dev, पूर्णांक type)
अणु
	काष्ठा iommu_करोमुख्य *prev_करोm;
	काष्ठा group_device *grp_dev;
	पूर्णांक ret, dev_def_करोm;
	काष्ठा device *dev;

	अगर (!group)
		वापस -EINVAL;

	mutex_lock(&group->mutex);

	अगर (group->शेष_करोमुख्य != group->करोमुख्य) अणु
		dev_err_ratelimited(prev_dev, "Group not assigned to default domain\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * iommu group wasn't locked जबतक acquiring device lock in
	 * iommu_group_store_type(). So, make sure that the device count hasn't
	 * changed जबतक acquiring device lock.
	 *
	 * Changing शेष करोमुख्य of an iommu group with two or more devices
	 * isn't supported because there could be a potential deadlock. Consider
	 * the following scenario. T1 is trying to acquire device locks of all
	 * the devices in the group and beक्रमe it could acquire all of them,
	 * there could be another thपढ़ो T2 (from dअगरferent sub-प्रणाली and use
	 * हाल) that has alपढ़ोy acquired some of the device locks and might be
	 * रुकोing क्रम T1 to release other device locks.
	 */
	अगर (iommu_group_device_count(group) != 1) अणु
		dev_err_ratelimited(prev_dev, "Cannot change default domain: Group has more than one device\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Since group has only one device */
	grp_dev = list_first_entry(&group->devices, काष्ठा group_device, list);
	dev = grp_dev->dev;

	अगर (prev_dev != dev) अणु
		dev_err_ratelimited(prev_dev, "Cannot change default domain: Device has been changed\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	prev_करोm = group->शेष_करोमुख्य;
	अगर (!prev_करोm) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	dev_def_करोm = iommu_get_def_करोमुख्य_type(dev);
	अगर (!type) अणु
		/*
		 * If the user hasn't requested any specअगरic type of करोमुख्य and
		 * अगर the device supports both the करोमुख्यs, then शेष to the
		 * करोमुख्य the device was booted with
		 */
		type = dev_def_करोm ? : iommu_def_करोमुख्य_type;
	पूर्ण अन्यथा अगर (dev_def_करोm && type != dev_def_करोm) अणु
		dev_err_ratelimited(prev_dev, "Device cannot be in %s domain\n",
				    iommu_करोमुख्य_type_str(type));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Switch to a new करोमुख्य only अगर the requested करोमुख्य type is dअगरferent
	 * from the existing शेष करोमुख्य type
	 */
	अगर (prev_करोm->type == type) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/* Sets group->शेष_करोमुख्य to the newly allocated करोमुख्य */
	ret = iommu_group_alloc_शेष_करोमुख्य(dev->bus, group, type);
	अगर (ret)
		जाओ out;

	ret = iommu_create_device_direct_mappings(group, dev);
	अगर (ret)
		जाओ मुक्त_new_करोमुख्य;

	ret = __iommu_attach_device(group->शेष_करोमुख्य, dev);
	अगर (ret)
		जाओ मुक्त_new_करोमुख्य;

	group->करोमुख्य = group->शेष_करोमुख्य;

	/*
	 * Release the mutex here because ops->probe_finalize() call-back of
	 * some venकरोr IOMMU drivers calls arm_iommu_attach_device() which
	 * in-turn might call back पूर्णांकo IOMMU core code, where it tries to take
	 * group->mutex, resulting in a deadlock.
	 */
	mutex_unlock(&group->mutex);

	/* Make sure dma_ops is appropriatley set */
	iommu_group_करो_probe_finalize(dev, group->शेष_करोमुख्य);
	iommu_करोमुख्य_मुक्त(prev_करोm);
	वापस 0;

मुक्त_new_करोमुख्य:
	iommu_करोमुख्य_मुक्त(group->शेष_करोमुख्य);
	group->शेष_करोमुख्य = prev_करोm;
	group->करोमुख्य = prev_करोm;

out:
	mutex_unlock(&group->mutex);

	वापस ret;
पूर्ण

/*
 * Changing the शेष करोमुख्य through sysfs requires the users to ubind the
 * drivers from the devices in the iommu group. Return failure अगर this करोesn't
 * meet.
 *
 * We need to consider the race between this and the device release path.
 * device_lock(dev) is used here to guarantee that the device release path
 * will not be entered at the same समय.
 */
अटल sमाप_प्रकार iommu_group_store_type(काष्ठा iommu_group *group,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा group_device *grp_dev;
	काष्ठा device *dev;
	पूर्णांक ret, req_type;

	अगर (!capable(CAP_SYS_ADMIN) || !capable(CAP_SYS_RAWIO))
		वापस -EACCES;

	अगर (WARN_ON(!group))
		वापस -EINVAL;

	अगर (sysfs_streq(buf, "identity"))
		req_type = IOMMU_DOMAIN_IDENTITY;
	अन्यथा अगर (sysfs_streq(buf, "DMA"))
		req_type = IOMMU_DOMAIN_DMA;
	अन्यथा अगर (sysfs_streq(buf, "auto"))
		req_type = 0;
	अन्यथा
		वापस -EINVAL;

	/*
	 * Lock/Unlock the group mutex here beक्रमe device lock to
	 * 1. Make sure that the iommu group has only one device (this is a
	 *    prerequisite क्रम step 2)
	 * 2. Get काष्ठा *dev which is needed to lock device
	 */
	mutex_lock(&group->mutex);
	अगर (iommu_group_device_count(group) != 1) अणु
		mutex_unlock(&group->mutex);
		pr_err_ratelimited("Cannot change default domain: Group has more than one device\n");
		वापस -EINVAL;
	पूर्ण

	/* Since group has only one device */
	grp_dev = list_first_entry(&group->devices, काष्ठा group_device, list);
	dev = grp_dev->dev;
	get_device(dev);

	/*
	 * Don't hold the group mutex because taking group mutex first and then
	 * the device lock could potentially cause a deadlock as below. Assume
	 * two thपढ़ोs T1 and T2. T1 is trying to change शेष करोमुख्य of an
	 * iommu group and T2 is trying to hot unplug a device or release [1] VF
	 * of a PCIe device which is in the same iommu group. T1 takes group
	 * mutex and beक्रमe it could take device lock assume T2 has taken device
	 * lock and is yet to take group mutex. Now, both the thपढ़ोs will be
	 * रुकोing क्रम the other thपढ़ो to release lock. Below, lock order was
	 * suggested.
	 * device_lock(dev);
	 *	mutex_lock(&group->mutex);
	 *		iommu_change_dev_def_करोमुख्य();
	 *	mutex_unlock(&group->mutex);
	 * device_unlock(dev);
	 *
	 * [1] Typical device release path
	 * device_lock() from device/driver core code
	 *  -> bus_notअगरier()
	 *   -> iommu_bus_notअगरier()
	 *    -> iommu_release_device()
	 *     -> ops->release_device() venकरोr driver calls back iommu core code
	 *      -> mutex_lock() from iommu core code
	 */
	mutex_unlock(&group->mutex);

	/* Check अगर the device in the group still has a driver bound to it */
	device_lock(dev);
	अगर (device_is_bound(dev)) अणु
		pr_err_ratelimited("Device is still bound to driver\n");
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = iommu_change_dev_def_करोमुख्य(group, dev, req_type);
	ret = ret ?: count;

out:
	device_unlock(dev);
	put_device(dev);

	वापस ret;
पूर्ण
