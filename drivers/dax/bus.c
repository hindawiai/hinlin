<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017-2018 Intel Corporation. All rights reserved. */
#समावेश <linux/memremap.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/dax.h>
#समावेश <linux/पन.स>
#समावेश "dax-private.h"
#समावेश "bus.h"

अटल काष्ठा class *dax_class;

अटल DEFINE_MUTEX(dax_bus_lock);

#घोषणा DAX_NAME_LEN 30
काष्ठा dax_id अणु
	काष्ठा list_head list;
	अक्षर dev_name[DAX_NAME_LEN];
पूर्ण;

अटल पूर्णांक dax_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	/*
	 * We only ever expect to handle device-dax instances, i.e. the
	 * @type argument to MODULE_ALIAS_DAX_DEVICE() is always zero
	 */
	वापस add_uevent_var(env, "MODALIAS=" DAX_DEVICE_MODALIAS_FMT, 0);
पूर्ण

अटल काष्ठा dax_device_driver *to_dax_drv(काष्ठा device_driver *drv)
अणु
	वापस container_of(drv, काष्ठा dax_device_driver, drv);
पूर्ण

अटल काष्ठा dax_id *__dax_match_id(काष्ठा dax_device_driver *dax_drv,
		स्थिर अक्षर *dev_name)
अणु
	काष्ठा dax_id *dax_id;

	lockdep_निश्चित_held(&dax_bus_lock);

	list_क्रम_each_entry(dax_id, &dax_drv->ids, list)
		अगर (sysfs_streq(dax_id->dev_name, dev_name))
			वापस dax_id;
	वापस शून्य;
पूर्ण

अटल पूर्णांक dax_match_id(काष्ठा dax_device_driver *dax_drv, काष्ठा device *dev)
अणु
	पूर्णांक match;

	mutex_lock(&dax_bus_lock);
	match = !!__dax_match_id(dax_drv, dev_name(dev));
	mutex_unlock(&dax_bus_lock);

	वापस match;
पूर्ण

क्रमागत id_action अणु
	ID_REMOVE,
	ID_ADD,
पूर्ण;

अटल sमाप_प्रकार करो_id_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
		माप_प्रकार count, क्रमागत id_action action)
अणु
	काष्ठा dax_device_driver *dax_drv = to_dax_drv(drv);
	अचिन्हित पूर्णांक region_id, id;
	अक्षर devname[DAX_NAME_LEN];
	काष्ठा dax_id *dax_id;
	sमाप_प्रकार rc = count;
	पूर्णांक fields;

	fields = माला_पूछो(buf, "dax%d.%d", &region_id, &id);
	अगर (fields != 2)
		वापस -EINVAL;
	प्र_लिखो(devname, "dax%d.%d", region_id, id);
	अगर (!sysfs_streq(buf, devname))
		वापस -EINVAL;

	mutex_lock(&dax_bus_lock);
	dax_id = __dax_match_id(dax_drv, buf);
	अगर (!dax_id) अणु
		अगर (action == ID_ADD) अणु
			dax_id = kzalloc(माप(*dax_id), GFP_KERNEL);
			अगर (dax_id) अणु
				म_नकलन(dax_id->dev_name, buf, DAX_NAME_LEN);
				list_add(&dax_id->list, &dax_drv->ids);
			पूर्ण अन्यथा
				rc = -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अगर (action == ID_REMOVE) अणु
		list_del(&dax_id->list);
		kमुक्त(dax_id);
	पूर्ण
	mutex_unlock(&dax_bus_lock);

	अगर (rc < 0)
		वापस rc;
	अगर (action == ID_ADD)
		rc = driver_attach(drv);
	अगर (rc)
		वापस rc;
	वापस count;
पूर्ण

अटल sमाप_प्रकार new_id_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस करो_id_store(drv, buf, count, ID_ADD);
पूर्ण
अटल DRIVER_ATTR_WO(new_id);

अटल sमाप_प्रकार हटाओ_id_store(काष्ठा device_driver *drv, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस करो_id_store(drv, buf, count, ID_REMOVE);
पूर्ण
अटल DRIVER_ATTR_WO(हटाओ_id);

अटल काष्ठा attribute *dax_drv_attrs[] = अणु
	&driver_attr_new_id.attr,
	&driver_attr_हटाओ_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(dax_drv);

अटल पूर्णांक dax_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv);

अटल bool is_अटल(काष्ठा dax_region *dax_region)
अणु
	वापस (dax_region->res.flags & IORESOURCE_DAX_STATIC) != 0;
पूर्ण

अटल u64 dev_dax_size(काष्ठा dev_dax *dev_dax)
अणु
	u64 size = 0;
	पूर्णांक i;

	device_lock_निश्चित(&dev_dax->dev);

	क्रम (i = 0; i < dev_dax->nr_range; i++)
		size += range_len(&dev_dax->ranges[i].range);

	वापस size;
पूर्ण

अटल पूर्णांक dax_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा dax_device_driver *dax_drv = to_dax_drv(dev->driver);
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	काष्ठा dax_region *dax_region = dev_dax->region;
	पूर्णांक rc;

	अगर (dev_dax_size(dev_dax) == 0 || dev_dax->id < 0)
		वापस -ENXIO;

	rc = dax_drv->probe(dev_dax);

	अगर (rc || is_अटल(dax_region))
		वापस rc;

	/*
	 * Track new seed creation only after successful probe of the
	 * previous seed.
	 */
	अगर (dax_region->seed == dev)
		dax_region->seed = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक dax_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा dax_device_driver *dax_drv = to_dax_drv(dev->driver);
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);

	अगर (dax_drv->हटाओ)
		dax_drv->हटाओ(dev_dax);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type dax_bus_type = अणु
	.name = "dax",
	.uevent = dax_bus_uevent,
	.match = dax_bus_match,
	.probe = dax_bus_probe,
	.हटाओ = dax_bus_हटाओ,
	.drv_groups = dax_drv_groups,
पूर्ण;

अटल पूर्णांक dax_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा dax_device_driver *dax_drv = to_dax_drv(drv);

	/*
	 * All but the 'device-dax' driver, which has 'match_always'
	 * set, requires an exact id match.
	 */
	अगर (dax_drv->match_always)
		वापस 1;

	वापस dax_match_id(dax_drv, dev);
पूर्ण

/*
 * Rely on the fact that drvdata is set beक्रमe the attributes are
 * रेजिस्टरed, and that the attributes are unरेजिस्टरed beक्रमe drvdata
 * is cleared to assume that drvdata is always valid.
 */
अटल sमाप_प्रकार id_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", dax_region->id);
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल sमाप_प्रकार region_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%llu\n", (अचिन्हित दीर्घ दीर्घ)
			resource_size(&dax_region->res));
पूर्ण
अटल काष्ठा device_attribute dev_attr_region_size = __ATTR(size, 0444,
		region_size_show, शून्य);

अटल sमाप_प्रकार region_align_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", dax_region->align);
पूर्ण
अटल काष्ठा device_attribute dev_attr_region_align =
		__ATTR(align, 0400, region_align_show, शून्य);

#घोषणा क्रम_each_dax_region_resource(dax_region, res) \
	क्रम (res = (dax_region)->res.child; res; res = res->sibling)

अटल अचिन्हित दीर्घ दीर्घ dax_region_avail_size(काष्ठा dax_region *dax_region)
अणु
	resource_माप_प्रकार size = resource_size(&dax_region->res);
	काष्ठा resource *res;

	device_lock_निश्चित(dax_region->dev);

	क्रम_each_dax_region_resource(dax_region, res)
		size -= resource_size(res);
	वापस size;
पूर्ण

अटल sमाप_प्रकार available_size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);
	अचिन्हित दीर्घ दीर्घ size;

	device_lock(dev);
	size = dax_region_avail_size(dax_region);
	device_unlock(dev);

	वापस प्र_लिखो(buf, "%llu\n", size);
पूर्ण
अटल DEVICE_ATTR_RO(available_size);

अटल sमाप_प्रकार seed_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);
	काष्ठा device *seed;
	sमाप_प्रकार rc;

	अगर (is_अटल(dax_region))
		वापस -EINVAL;

	device_lock(dev);
	seed = dax_region->seed;
	rc = प्र_लिखो(buf, "%s\n", seed ? dev_name(seed) : "");
	device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RO(seed);

अटल sमाप_प्रकार create_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);
	काष्ठा device *youngest;
	sमाप_प्रकार rc;

	अगर (is_अटल(dax_region))
		वापस -EINVAL;

	device_lock(dev);
	youngest = dax_region->youngest;
	rc = प्र_लिखो(buf, "%s\n", youngest ? dev_name(youngest) : "");
	device_unlock(dev);

	वापस rc;
पूर्ण

अटल sमाप_प्रकार create_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);
	अचिन्हित दीर्घ दीर्घ avail;
	sमाप_प्रकार rc;
	पूर्णांक val;

	अगर (is_अटल(dax_region))
		वापस -EINVAL;

	rc = kstrtoपूर्णांक(buf, 0, &val);
	अगर (rc)
		वापस rc;
	अगर (val != 1)
		वापस -EINVAL;

	device_lock(dev);
	avail = dax_region_avail_size(dax_region);
	अगर (avail == 0)
		rc = -ENOSPC;
	अन्यथा अणु
		काष्ठा dev_dax_data data = अणु
			.dax_region = dax_region,
			.size = 0,
			.id = -1,
		पूर्ण;
		काष्ठा dev_dax *dev_dax = devm_create_dev_dax(&data);

		अगर (IS_ERR(dev_dax))
			rc = PTR_ERR(dev_dax);
		अन्यथा अणु
			/*
			 * In support of crafting multiple new devices
			 * simultaneously multiple seeds can be created,
			 * but only the first one that has not been
			 * successfully bound is tracked as the region
			 * seed.
			 */
			अगर (!dax_region->seed)
				dax_region->seed = &dev_dax->dev;
			dax_region->youngest = &dev_dax->dev;
			rc = len;
		पूर्ण
	पूर्ण
	device_unlock(dev);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_RW(create);

व्योम समाप्त_dev_dax(काष्ठा dev_dax *dev_dax)
अणु
	काष्ठा dax_device *dax_dev = dev_dax->dax_dev;
	काष्ठा inode *inode = dax_inode(dax_dev);

	समाप्त_dax(dax_dev);
	unmap_mapping_range(inode->i_mapping, 0, 0, 1);
पूर्ण
EXPORT_SYMBOL_GPL(समाप्त_dev_dax);

अटल व्योम trim_dev_dax_range(काष्ठा dev_dax *dev_dax)
अणु
	पूर्णांक i = dev_dax->nr_range - 1;
	काष्ठा range *range = &dev_dax->ranges[i].range;
	काष्ठा dax_region *dax_region = dev_dax->region;

	device_lock_निश्चित(dax_region->dev);
	dev_dbg(&dev_dax->dev, "delete range[%d]: %#llx:%#llx\n", i,
		(अचिन्हित दीर्घ दीर्घ)range->start,
		(अचिन्हित दीर्घ दीर्घ)range->end);

	__release_region(&dax_region->res, range->start, range_len(range));
	अगर (--dev_dax->nr_range == 0) अणु
		kमुक्त(dev_dax->ranges);
		dev_dax->ranges = शून्य;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_dev_dax_ranges(काष्ठा dev_dax *dev_dax)
अणु
	जबतक (dev_dax->nr_range)
		trim_dev_dax_range(dev_dax);
पूर्ण

अटल व्योम unरेजिस्टर_dev_dax(व्योम *dev)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);

	dev_dbg(dev, "%s\n", __func__);

	समाप्त_dev_dax(dev_dax);
	मुक्त_dev_dax_ranges(dev_dax);
	device_del(dev);
	put_device(dev);
पूर्ण

/* a वापस value >= 0 indicates this invocation invalidated the id */
अटल पूर्णांक __मुक्त_dev_dax_id(काष्ठा dev_dax *dev_dax)
अणु
	काष्ठा dax_region *dax_region = dev_dax->region;
	काष्ठा device *dev = &dev_dax->dev;
	पूर्णांक rc = dev_dax->id;

	device_lock_निश्चित(dev);

	अगर (is_अटल(dax_region) || dev_dax->id < 0)
		वापस -1;
	ida_मुक्त(&dax_region->ida, dev_dax->id);
	dev_dax->id = -1;
	वापस rc;
पूर्ण

अटल पूर्णांक मुक्त_dev_dax_id(काष्ठा dev_dax *dev_dax)
अणु
	काष्ठा device *dev = &dev_dax->dev;
	पूर्णांक rc;

	device_lock(dev);
	rc = __मुक्त_dev_dax_id(dev_dax);
	device_unlock(dev);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार delete_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);
	काष्ठा dev_dax *dev_dax;
	काष्ठा device *victim;
	bool करो_del = false;
	पूर्णांक rc;

	अगर (is_अटल(dax_region))
		वापस -EINVAL;

	victim = device_find_child_by_name(dax_region->dev, buf);
	अगर (!victim)
		वापस -ENXIO;

	device_lock(dev);
	device_lock(victim);
	dev_dax = to_dev_dax(victim);
	अगर (victim->driver || dev_dax_size(dev_dax))
		rc = -EBUSY;
	अन्यथा अणु
		/*
		 * Invalidate the device so it करोes not become active
		 * again, but always preserve device-id-0 so that
		 * /sys/bus/dax/ is guaranteed to be populated जबतक any
		 * dax_region is रेजिस्टरed.
		 */
		अगर (dev_dax->id > 0) अणु
			करो_del = __मुक्त_dev_dax_id(dev_dax) >= 0;
			rc = len;
			अगर (dax_region->seed == victim)
				dax_region->seed = शून्य;
			अगर (dax_region->youngest == victim)
				dax_region->youngest = शून्य;
		पूर्ण अन्यथा
			rc = -EBUSY;
	पूर्ण
	device_unlock(victim);

	/* won the race to invalidate the device, clean it up */
	अगर (करो_del)
		devm_release_action(dev, unरेजिस्टर_dev_dax, victim);
	device_unlock(dev);
	put_device(victim);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR_WO(delete);

अटल umode_t dax_region_visible(काष्ठा kobject *kobj, काष्ठा attribute *a,
		पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा dax_region *dax_region = dev_get_drvdata(dev);

	अगर (is_अटल(dax_region))
		अगर (a == &dev_attr_available_size.attr
				|| a == &dev_attr_create.attr
				|| a == &dev_attr_seed.attr
				|| a == &dev_attr_delete.attr)
			वापस 0;
	वापस a->mode;
पूर्ण

अटल काष्ठा attribute *dax_region_attributes[] = अणु
	&dev_attr_available_size.attr,
	&dev_attr_region_size.attr,
	&dev_attr_region_align.attr,
	&dev_attr_create.attr,
	&dev_attr_seed.attr,
	&dev_attr_delete.attr,
	&dev_attr_id.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dax_region_attribute_group = अणु
	.name = "dax_region",
	.attrs = dax_region_attributes,
	.is_visible = dax_region_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dax_region_attribute_groups[] = अणु
	&dax_region_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम dax_region_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dax_region *dax_region;

	dax_region = container_of(kref, काष्ठा dax_region, kref);
	kमुक्त(dax_region);
पूर्ण

व्योम dax_region_put(काष्ठा dax_region *dax_region)
अणु
	kref_put(&dax_region->kref, dax_region_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(dax_region_put);

अटल व्योम dax_region_unरेजिस्टर(व्योम *region)
अणु
	काष्ठा dax_region *dax_region = region;

	sysfs_हटाओ_groups(&dax_region->dev->kobj,
			dax_region_attribute_groups);
	dax_region_put(dax_region);
पूर्ण

काष्ठा dax_region *alloc_dax_region(काष्ठा device *parent, पूर्णांक region_id,
		काष्ठा range *range, पूर्णांक target_node, अचिन्हित पूर्णांक align,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा dax_region *dax_region;

	/*
	 * The DAX core assumes that it can store its निजी data in
	 * parent->driver_data. This WARN is a reminder / safeguard क्रम
	 * developers of device-dax drivers.
	 */
	अगर (dev_get_drvdata(parent)) अणु
		dev_WARN(parent, "dax core failed to setup private data\n");
		वापस शून्य;
	पूर्ण

	अगर (!IS_ALIGNED(range->start, align)
			|| !IS_ALIGNED(range_len(range), align))
		वापस शून्य;

	dax_region = kzalloc(माप(*dax_region), GFP_KERNEL);
	अगर (!dax_region)
		वापस शून्य;

	dev_set_drvdata(parent, dax_region);
	kref_init(&dax_region->kref);
	dax_region->id = region_id;
	dax_region->align = align;
	dax_region->dev = parent;
	dax_region->target_node = target_node;
	ida_init(&dax_region->ida);
	dax_region->res = (काष्ठा resource) अणु
		.start = range->start,
		.end = range->end,
		.flags = IORESOURCE_MEM | flags,
	पूर्ण;

	अगर (sysfs_create_groups(&parent->kobj, dax_region_attribute_groups)) अणु
		kमुक्त(dax_region);
		वापस शून्य;
	पूर्ण

	kref_get(&dax_region->kref);
	अगर (devm_add_action_or_reset(parent, dax_region_unरेजिस्टर, dax_region))
		वापस शून्य;
	वापस dax_region;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_dax_region);

अटल व्योम dax_mapping_release(काष्ठा device *dev)
अणु
	काष्ठा dax_mapping *mapping = to_dax_mapping(dev);
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev->parent);

	ida_मुक्त(&dev_dax->ida, mapping->id);
	kमुक्त(mapping);
पूर्ण

अटल व्योम unरेजिस्टर_dax_mapping(व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा dax_mapping *mapping = to_dax_mapping(dev);
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev->parent);
	काष्ठा dax_region *dax_region = dev_dax->region;

	dev_dbg(dev, "%s\n", __func__);

	device_lock_निश्चित(dax_region->dev);

	dev_dax->ranges[mapping->range_id].mapping = शून्य;
	mapping->range_id = -1;

	device_del(dev);
	put_device(dev);
पूर्ण

अटल काष्ठा dev_dax_range *get_dax_range(काष्ठा device *dev)
अणु
	काष्ठा dax_mapping *mapping = to_dax_mapping(dev);
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev->parent);
	काष्ठा dax_region *dax_region = dev_dax->region;

	device_lock(dax_region->dev);
	अगर (mapping->range_id < 0) अणु
		device_unlock(dax_region->dev);
		वापस शून्य;
	पूर्ण

	वापस &dev_dax->ranges[mapping->range_id];
पूर्ण

अटल व्योम put_dax_range(काष्ठा dev_dax_range *dax_range)
अणु
	काष्ठा dax_mapping *mapping = dax_range->mapping;
	काष्ठा dev_dax *dev_dax = to_dev_dax(mapping->dev.parent);
	काष्ठा dax_region *dax_region = dev_dax->region;

	device_unlock(dax_region->dev);
पूर्ण

अटल sमाप_प्रकार start_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_dax_range *dax_range;
	sमाप_प्रकार rc;

	dax_range = get_dax_range(dev);
	अगर (!dax_range)
		वापस -ENXIO;
	rc = प्र_लिखो(buf, "%#llx\n", dax_range->range.start);
	put_dax_range(dax_range);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(start, 0400, start_show, शून्य);

अटल sमाप_प्रकार end_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_dax_range *dax_range;
	sमाप_प्रकार rc;

	dax_range = get_dax_range(dev);
	अगर (!dax_range)
		वापस -ENXIO;
	rc = प्र_लिखो(buf, "%#llx\n", dax_range->range.end);
	put_dax_range(dax_range);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(end, 0400, end_show, शून्य);

अटल sमाप_प्रकार pgoff_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_dax_range *dax_range;
	sमाप_प्रकार rc;

	dax_range = get_dax_range(dev);
	अगर (!dax_range)
		वापस -ENXIO;
	rc = प्र_लिखो(buf, "%#lx\n", dax_range->pgoff);
	put_dax_range(dax_range);

	वापस rc;
पूर्ण
अटल DEVICE_ATTR(page_offset, 0400, pgoff_show, शून्य);

अटल काष्ठा attribute *dax_mapping_attributes[] = अणु
	&dev_attr_start.attr,
	&dev_attr_end.attr,
	&dev_attr_page_offset.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dax_mapping_attribute_group = अणु
	.attrs = dax_mapping_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dax_mapping_attribute_groups[] = अणु
	&dax_mapping_attribute_group,
	शून्य,
पूर्ण;

अटल काष्ठा device_type dax_mapping_type = अणु
	.release = dax_mapping_release,
	.groups = dax_mapping_attribute_groups,
पूर्ण;

अटल पूर्णांक devm_रेजिस्टर_dax_mapping(काष्ठा dev_dax *dev_dax, पूर्णांक range_id)
अणु
	काष्ठा dax_region *dax_region = dev_dax->region;
	काष्ठा dax_mapping *mapping;
	काष्ठा device *dev;
	पूर्णांक rc;

	device_lock_निश्चित(dax_region->dev);

	अगर (dev_WARN_ONCE(&dev_dax->dev, !dax_region->dev->driver,
				"region disabled\n"))
		वापस -ENXIO;

	mapping = kzalloc(माप(*mapping), GFP_KERNEL);
	अगर (!mapping)
		वापस -ENOMEM;
	mapping->range_id = range_id;
	mapping->id = ida_alloc(&dev_dax->ida, GFP_KERNEL);
	अगर (mapping->id < 0) अणु
		kमुक्त(mapping);
		वापस -ENOMEM;
	पूर्ण
	dev_dax->ranges[range_id].mapping = mapping;
	dev = &mapping->dev;
	device_initialize(dev);
	dev->parent = &dev_dax->dev;
	dev->type = &dax_mapping_type;
	dev_set_name(dev, "mapping%d", mapping->id);
	rc = device_add(dev);
	अगर (rc) अणु
		put_device(dev);
		वापस rc;
	पूर्ण

	rc = devm_add_action_or_reset(dax_region->dev, unरेजिस्टर_dax_mapping,
			dev);
	अगर (rc)
		वापस rc;
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_dev_dax_range(काष्ठा dev_dax *dev_dax, u64 start,
		resource_माप_प्रकार size)
अणु
	काष्ठा dax_region *dax_region = dev_dax->region;
	काष्ठा resource *res = &dax_region->res;
	काष्ठा device *dev = &dev_dax->dev;
	काष्ठा dev_dax_range *ranges;
	अचिन्हित दीर्घ pgoff = 0;
	काष्ठा resource *alloc;
	पूर्णांक i, rc;

	device_lock_निश्चित(dax_region->dev);

	/* handle the seed alloc special हाल */
	अगर (!size) अणु
		अगर (dev_WARN_ONCE(dev, dev_dax->nr_range,
					"0-size allocation must be first\n"))
			वापस -EBUSY;
		/* nr_range == 0 is अन्यथाwhere special हालd as 0-size device */
		वापस 0;
	पूर्ण

	alloc = __request_region(res, start, size, dev_name(dev), 0);
	अगर (!alloc)
		वापस -ENOMEM;

	ranges = kपुनः_स्मृति(dev_dax->ranges, माप(*ranges)
			* (dev_dax->nr_range + 1), GFP_KERNEL);
	अगर (!ranges) अणु
		__release_region(res, alloc->start, resource_size(alloc));
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < dev_dax->nr_range; i++)
		pgoff += PHYS_PFN(range_len(&ranges[i].range));
	dev_dax->ranges = ranges;
	ranges[dev_dax->nr_range++] = (काष्ठा dev_dax_range) अणु
		.pgoff = pgoff,
		.range = अणु
			.start = alloc->start,
			.end = alloc->end,
		पूर्ण,
	पूर्ण;

	dev_dbg(dev, "alloc range[%d]: %pa:%pa\n", dev_dax->nr_range - 1,
			&alloc->start, &alloc->end);
	/*
	 * A dev_dax instance must be रेजिस्टरed beक्रमe mapping device
	 * children can be added. Defer to devm_create_dev_dax() to add
	 * the initial mapping device.
	 */
	अगर (!device_is_रेजिस्टरed(&dev_dax->dev))
		वापस 0;

	rc = devm_रेजिस्टर_dax_mapping(dev_dax, dev_dax->nr_range - 1);
	अगर (rc)
		trim_dev_dax_range(dev_dax);

	वापस rc;
पूर्ण

अटल पूर्णांक adjust_dev_dax_range(काष्ठा dev_dax *dev_dax, काष्ठा resource *res, resource_माप_प्रकार size)
अणु
	पूर्णांक last_range = dev_dax->nr_range - 1;
	काष्ठा dev_dax_range *dax_range = &dev_dax->ranges[last_range];
	काष्ठा dax_region *dax_region = dev_dax->region;
	bool is_shrink = resource_size(res) > size;
	काष्ठा range *range = &dax_range->range;
	काष्ठा device *dev = &dev_dax->dev;
	पूर्णांक rc;

	device_lock_निश्चित(dax_region->dev);

	अगर (dev_WARN_ONCE(dev, !size, "deletion is handled by dev_dax_shrink\n"))
		वापस -EINVAL;

	rc = adjust_resource(res, range->start, size);
	अगर (rc)
		वापस rc;

	*range = (काष्ठा range) अणु
		.start = range->start,
		.end = range->start + size - 1,
	पूर्ण;

	dev_dbg(dev, "%s range[%d]: %#llx:%#llx\n", is_shrink ? "shrink" : "extend",
			last_range, (अचिन्हित दीर्घ दीर्घ) range->start,
			(अचिन्हित दीर्घ दीर्घ) range->end);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार size_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	अचिन्हित दीर्घ दीर्घ size;

	device_lock(dev);
	size = dev_dax_size(dev_dax);
	device_unlock(dev);

	वापस प्र_लिखो(buf, "%llu\n", size);
पूर्ण

अटल bool alloc_is_aligned(काष्ठा dev_dax *dev_dax, resource_माप_प्रकार size)
अणु
	/*
	 * The minimum mapping granularity क्रम a device instance is a
	 * single subsection, unless the arch says otherwise.
	 */
	वापस IS_ALIGNED(size, max_t(अचिन्हित दीर्घ, dev_dax->align, memremap_compat_align()));
पूर्ण

अटल पूर्णांक dev_dax_shrink(काष्ठा dev_dax *dev_dax, resource_माप_प्रकार size)
अणु
	resource_माप_प्रकार to_shrink = dev_dax_size(dev_dax) - size;
	काष्ठा dax_region *dax_region = dev_dax->region;
	काष्ठा device *dev = &dev_dax->dev;
	पूर्णांक i;

	क्रम (i = dev_dax->nr_range - 1; i >= 0; i--) अणु
		काष्ठा range *range = &dev_dax->ranges[i].range;
		काष्ठा dax_mapping *mapping = dev_dax->ranges[i].mapping;
		काष्ठा resource *adjust = शून्य, *res;
		resource_माप_प्रकार shrink;

		shrink = min_t(u64, to_shrink, range_len(range));
		अगर (shrink >= range_len(range)) अणु
			devm_release_action(dax_region->dev,
					unरेजिस्टर_dax_mapping, &mapping->dev);
			trim_dev_dax_range(dev_dax);
			to_shrink -= shrink;
			अगर (!to_shrink)
				अवरोध;
			जारी;
		पूर्ण

		क्रम_each_dax_region_resource(dax_region, res)
			अगर (म_भेद(res->name, dev_name(dev)) == 0
					&& res->start == range->start) अणु
				adjust = res;
				अवरोध;
			पूर्ण

		अगर (dev_WARN_ONCE(dev, !adjust || i != dev_dax->nr_range - 1,
					"failed to find matching resource\n"))
			वापस -ENXIO;
		वापस adjust_dev_dax_range(dev_dax, adjust, range_len(range)
				- shrink);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Only allow adjusपंचांगents that preserve the relative pgoff of existing
 * allocations. I.e. the dev_dax->ranges array is ordered by increasing pgoff.
 */
अटल bool adjust_ok(काष्ठा dev_dax *dev_dax, काष्ठा resource *res)
अणु
	काष्ठा dev_dax_range *last;
	पूर्णांक i;

	अगर (dev_dax->nr_range == 0)
		वापस false;
	अगर (म_भेद(res->name, dev_name(&dev_dax->dev)) != 0)
		वापस false;
	last = &dev_dax->ranges[dev_dax->nr_range - 1];
	अगर (last->range.start != res->start || last->range.end != res->end)
		वापस false;
	क्रम (i = 0; i < dev_dax->nr_range - 1; i++) अणु
		काष्ठा dev_dax_range *dax_range = &dev_dax->ranges[i];

		अगर (dax_range->pgoff > last->pgoff)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल sमाप_प्रकार dev_dax_resize(काष्ठा dax_region *dax_region,
		काष्ठा dev_dax *dev_dax, resource_माप_प्रकार size)
अणु
	resource_माप_प्रकार avail = dax_region_avail_size(dax_region), to_alloc;
	resource_माप_प्रकार dev_size = dev_dax_size(dev_dax);
	काष्ठा resource *region_res = &dax_region->res;
	काष्ठा device *dev = &dev_dax->dev;
	काष्ठा resource *res, *first;
	resource_माप_प्रकार alloc = 0;
	पूर्णांक rc;

	अगर (dev->driver)
		वापस -EBUSY;
	अगर (size == dev_size)
		वापस 0;
	अगर (size > dev_size && size - dev_size > avail)
		वापस -ENOSPC;
	अगर (size < dev_size)
		वापस dev_dax_shrink(dev_dax, size);

	to_alloc = size - dev_size;
	अगर (dev_WARN_ONCE(dev, !alloc_is_aligned(dev_dax, to_alloc),
			"resize of %pa misaligned\n", &to_alloc))
		वापस -ENXIO;

	/*
	 * Expand the device पूर्णांकo the unused portion of the region. This
	 * may involve adjusting the end of an existing resource, or
	 * allocating a new resource.
	 */
retry:
	first = region_res->child;
	अगर (!first)
		वापस alloc_dev_dax_range(dev_dax, dax_region->res.start, to_alloc);

	rc = -ENOSPC;
	क्रम (res = first; res; res = res->sibling) अणु
		काष्ठा resource *next = res->sibling;

		/* space at the beginning of the region */
		अगर (res == first && res->start > dax_region->res.start) अणु
			alloc = min(res->start - dax_region->res.start, to_alloc);
			rc = alloc_dev_dax_range(dev_dax, dax_region->res.start, alloc);
			अवरोध;
		पूर्ण

		alloc = 0;
		/* space between allocations */
		अगर (next && next->start > res->end + 1)
			alloc = min(next->start - (res->end + 1), to_alloc);

		/* space at the end of the region */
		अगर (!alloc && !next && res->end < region_res->end)
			alloc = min(region_res->end - res->end, to_alloc);

		अगर (!alloc)
			जारी;

		अगर (adjust_ok(dev_dax, res)) अणु
			rc = adjust_dev_dax_range(dev_dax, res, resource_size(res) + alloc);
			अवरोध;
		पूर्ण
		rc = alloc_dev_dax_range(dev_dax, res->end + 1, alloc);
		अवरोध;
	पूर्ण
	अगर (rc)
		वापस rc;
	to_alloc -= alloc;
	अगर (to_alloc)
		जाओ retry;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार size_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	sमाप_प्रकार rc;
	अचिन्हित दीर्घ दीर्घ val;
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	काष्ठा dax_region *dax_region = dev_dax->region;

	rc = kम_से_अदीर्घl(buf, 0, &val);
	अगर (rc)
		वापस rc;

	अगर (!alloc_is_aligned(dev_dax, val)) अणु
		dev_dbg(dev, "%s: size: %lld misaligned\n", __func__, val);
		वापस -EINVAL;
	पूर्ण

	device_lock(dax_region->dev);
	अगर (!dax_region->dev->driver) अणु
		device_unlock(dax_region->dev);
		वापस -ENXIO;
	पूर्ण
	device_lock(dev);
	rc = dev_dax_resize(dax_region, dev_dax, val);
	device_unlock(dev);
	device_unlock(dax_region->dev);

	वापस rc == 0 ? len : rc;
पूर्ण
अटल DEVICE_ATTR_RW(size);

अटल sमाप_प्रकार range_parse(स्थिर अक्षर *opt, माप_प्रकार len, काष्ठा range *range)
अणु
	अचिन्हित दीर्घ दीर्घ addr = 0;
	अक्षर *start, *end, *str;
	sमाप_प्रकार rc = -EINVAL;

	str = kstrdup(opt, GFP_KERNEL);
	अगर (!str)
		वापस rc;

	end = str;
	start = strsep(&end, "-");
	अगर (!start || !end)
		जाओ err;

	rc = kम_से_अदीर्घl(start, 16, &addr);
	अगर (rc)
		जाओ err;
	range->start = addr;

	rc = kम_से_अदीर्घl(end, 16, &addr);
	अगर (rc)
		जाओ err;
	range->end = addr;

err:
	kमुक्त(str);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार mapping_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	काष्ठा dax_region *dax_region = dev_dax->region;
	माप_प्रकार to_alloc;
	काष्ठा range r;
	sमाप_प्रकार rc;

	rc = range_parse(buf, len, &r);
	अगर (rc)
		वापस rc;

	rc = -ENXIO;
	device_lock(dax_region->dev);
	अगर (!dax_region->dev->driver) अणु
		device_unlock(dax_region->dev);
		वापस rc;
	पूर्ण
	device_lock(dev);

	to_alloc = range_len(&r);
	अगर (alloc_is_aligned(dev_dax, to_alloc))
		rc = alloc_dev_dax_range(dev_dax, r.start, to_alloc);
	device_unlock(dev);
	device_unlock(dax_region->dev);

	वापस rc == 0 ? len : rc;
पूर्ण
अटल DEVICE_ATTR_WO(mapping);

अटल sमाप_प्रकार align_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);

	वापस प्र_लिखो(buf, "%d\n", dev_dax->align);
पूर्ण

अटल sमाप_प्रकार dev_dax_validate_align(काष्ठा dev_dax *dev_dax)
अणु
	काष्ठा device *dev = &dev_dax->dev;
	पूर्णांक i;

	क्रम (i = 0; i < dev_dax->nr_range; i++) अणु
		माप_प्रकार len = range_len(&dev_dax->ranges[i].range);

		अगर (!alloc_is_aligned(dev_dax, len)) अणु
			dev_dbg(dev, "%s: align %u invalid for range %d\n",
				__func__, dev_dax->align, i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार align_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	काष्ठा dax_region *dax_region = dev_dax->region;
	अचिन्हित दीर्घ val, align_save;
	sमाप_प्रकार rc;

	rc = kम_से_अदीर्घ(buf, 0, &val);
	अगर (rc)
		वापस -ENXIO;

	अगर (!dax_align_valid(val))
		वापस -EINVAL;

	device_lock(dax_region->dev);
	अगर (!dax_region->dev->driver) अणु
		device_unlock(dax_region->dev);
		वापस -ENXIO;
	पूर्ण

	device_lock(dev);
	अगर (dev->driver) अणु
		rc = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	align_save = dev_dax->align;
	dev_dax->align = val;
	rc = dev_dax_validate_align(dev_dax);
	अगर (rc)
		dev_dax->align = align_save;
out_unlock:
	device_unlock(dev);
	device_unlock(dax_region->dev);
	वापस rc == 0 ? len : rc;
पूर्ण
अटल DEVICE_ATTR_RW(align);

अटल पूर्णांक dev_dax_target_node(काष्ठा dev_dax *dev_dax)
अणु
	काष्ठा dax_region *dax_region = dev_dax->region;

	वापस dax_region->target_node;
पूर्ण

अटल sमाप_प्रकार target_node_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);

	वापस प्र_लिखो(buf, "%d\n", dev_dax_target_node(dev_dax));
पूर्ण
अटल DEVICE_ATTR_RO(target_node);

अटल sमाप_प्रकार resource_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	काष्ठा dax_region *dax_region = dev_dax->region;
	अचिन्हित दीर्घ दीर्घ start;

	अगर (dev_dax->nr_range < 1)
		start = dax_region->res.start;
	अन्यथा
		start = dev_dax->ranges[0].range.start;

	वापस प्र_लिखो(buf, "%#llx\n", start);
पूर्ण
अटल DEVICE_ATTR(resource, 0400, resource_show, शून्य);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	/*
	 * We only ever expect to handle device-dax instances, i.e. the
	 * @type argument to MODULE_ALIAS_DAX_DEVICE() is always zero
	 */
	वापस प्र_लिखो(buf, DAX_DEVICE_MODALIAS_FMT "\n", 0);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार numa_node_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", dev_to_node(dev));
पूर्ण
अटल DEVICE_ATTR_RO(numa_node);

अटल umode_t dev_dax_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, काष्ठा device, kobj);
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	काष्ठा dax_region *dax_region = dev_dax->region;

	अगर (a == &dev_attr_target_node.attr && dev_dax_target_node(dev_dax) < 0)
		वापस 0;
	अगर (a == &dev_attr_numa_node.attr && !IS_ENABLED(CONFIG_NUMA))
		वापस 0;
	अगर (a == &dev_attr_mapping.attr && is_अटल(dax_region))
		वापस 0;
	अगर ((a == &dev_attr_align.attr ||
	     a == &dev_attr_size.attr) && is_अटल(dax_region))
		वापस 0444;
	वापस a->mode;
पूर्ण

अटल काष्ठा attribute *dev_dax_attributes[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_size.attr,
	&dev_attr_mapping.attr,
	&dev_attr_target_node.attr,
	&dev_attr_align.attr,
	&dev_attr_resource.attr,
	&dev_attr_numa_node.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group dev_dax_attribute_group = अणु
	.attrs = dev_dax_attributes,
	.is_visible = dev_dax_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *dax_attribute_groups[] = अणु
	&dev_dax_attribute_group,
	शून्य,
पूर्ण;

अटल व्योम dev_dax_release(काष्ठा device *dev)
अणु
	काष्ठा dev_dax *dev_dax = to_dev_dax(dev);
	काष्ठा dax_region *dax_region = dev_dax->region;
	काष्ठा dax_device *dax_dev = dev_dax->dax_dev;

	put_dax(dax_dev);
	मुक्त_dev_dax_id(dev_dax);
	dax_region_put(dax_region);
	kमुक्त(dev_dax->pgmap);
	kमुक्त(dev_dax);
पूर्ण

अटल स्थिर काष्ठा device_type dev_dax_type = अणु
	.release = dev_dax_release,
	.groups = dax_attribute_groups,
पूर्ण;

काष्ठा dev_dax *devm_create_dev_dax(काष्ठा dev_dax_data *data)
अणु
	काष्ठा dax_region *dax_region = data->dax_region;
	काष्ठा device *parent = dax_region->dev;
	काष्ठा dax_device *dax_dev;
	काष्ठा dev_dax *dev_dax;
	काष्ठा inode *inode;
	काष्ठा device *dev;
	पूर्णांक rc;

	dev_dax = kzalloc(माप(*dev_dax), GFP_KERNEL);
	अगर (!dev_dax)
		वापस ERR_PTR(-ENOMEM);

	अगर (is_अटल(dax_region)) अणु
		अगर (dev_WARN_ONCE(parent, data->id < 0,
				"dynamic id specified to static region\n")) अणु
			rc = -EINVAL;
			जाओ err_id;
		पूर्ण

		dev_dax->id = data->id;
	पूर्ण अन्यथा अणु
		अगर (dev_WARN_ONCE(parent, data->id >= 0,
				"static id specified to dynamic region\n")) अणु
			rc = -EINVAL;
			जाओ err_id;
		पूर्ण

		rc = ida_alloc(&dax_region->ida, GFP_KERNEL);
		अगर (rc < 0)
			जाओ err_id;
		dev_dax->id = rc;
	पूर्ण

	dev_dax->region = dax_region;
	dev = &dev_dax->dev;
	device_initialize(dev);
	dev_set_name(dev, "dax%d.%d", dax_region->id, dev_dax->id);

	rc = alloc_dev_dax_range(dev_dax, dax_region->res.start, data->size);
	अगर (rc)
		जाओ err_range;

	अगर (data->pgmap) अणु
		dev_WARN_ONCE(parent, !is_अटल(dax_region),
			"custom dev_pagemap requires a static dax_region\n");

		dev_dax->pgmap = kmemdup(data->pgmap,
				माप(काष्ठा dev_pagemap), GFP_KERNEL);
		अगर (!dev_dax->pgmap) अणु
			rc = -ENOMEM;
			जाओ err_pgmap;
		पूर्ण
	पूर्ण

	/*
	 * No 'host' or dax_operations since there is no access to this
	 * device outside of mmap of the resulting अक्षरacter device.
	 */
	dax_dev = alloc_dax(dev_dax, शून्य, शून्य, DAXDEV_F_SYNC);
	अगर (IS_ERR(dax_dev)) अणु
		rc = PTR_ERR(dax_dev);
		जाओ err_alloc_dax;
	पूर्ण

	/* a device_dax instance is dead जबतक the driver is not attached */
	समाप्त_dax(dax_dev);

	dev_dax->dax_dev = dax_dev;
	dev_dax->target_node = dax_region->target_node;
	dev_dax->align = dax_region->align;
	ida_init(&dev_dax->ida);
	kref_get(&dax_region->kref);

	inode = dax_inode(dax_dev);
	dev->devt = inode->i_rdev;
	अगर (data->subsys == DEV_DAX_BUS)
		dev->bus = &dax_bus_type;
	अन्यथा
		dev->class = dax_class;
	dev->parent = parent;
	dev->type = &dev_dax_type;

	rc = device_add(dev);
	अगर (rc) अणु
		समाप्त_dev_dax(dev_dax);
		put_device(dev);
		वापस ERR_PTR(rc);
	पूर्ण

	rc = devm_add_action_or_reset(dax_region->dev, unरेजिस्टर_dev_dax, dev);
	अगर (rc)
		वापस ERR_PTR(rc);

	/* रेजिस्टर mapping device क्रम the initial allocation range */
	अगर (dev_dax->nr_range && range_len(&dev_dax->ranges[0].range)) अणु
		rc = devm_रेजिस्टर_dax_mapping(dev_dax, 0);
		अगर (rc)
			वापस ERR_PTR(rc);
	पूर्ण

	वापस dev_dax;

err_alloc_dax:
	kमुक्त(dev_dax->pgmap);
err_pgmap:
	मुक्त_dev_dax_ranges(dev_dax);
err_range:
	मुक्त_dev_dax_id(dev_dax);
err_id:
	kमुक्त(dev_dax);

	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_create_dev_dax);

अटल पूर्णांक match_always_count;

पूर्णांक __dax_driver_रेजिस्टर(काष्ठा dax_device_driver *dax_drv,
		काष्ठा module *module, स्थिर अक्षर *mod_name)
अणु
	काष्ठा device_driver *drv = &dax_drv->drv;
	पूर्णांक rc = 0;

	/*
	 * dax_bus_probe() calls dax_drv->probe() unconditionally.
	 * So better be safe than sorry and ensure it is provided.
	 */
	अगर (!dax_drv->probe)
		वापस -EINVAL;

	INIT_LIST_HEAD(&dax_drv->ids);
	drv->owner = module;
	drv->name = mod_name;
	drv->mod_name = mod_name;
	drv->bus = &dax_bus_type;

	/* there can only be one शेष driver */
	mutex_lock(&dax_bus_lock);
	match_always_count += dax_drv->match_always;
	अगर (match_always_count > 1) अणु
		match_always_count--;
		WARN_ON(1);
		rc = -EINVAL;
	पूर्ण
	mutex_unlock(&dax_bus_lock);
	अगर (rc)
		वापस rc;

	rc = driver_रेजिस्टर(drv);
	अगर (rc && dax_drv->match_always) अणु
		mutex_lock(&dax_bus_lock);
		match_always_count -= dax_drv->match_always;
		mutex_unlock(&dax_bus_lock);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(__dax_driver_रेजिस्टर);

व्योम dax_driver_unरेजिस्टर(काष्ठा dax_device_driver *dax_drv)
अणु
	काष्ठा device_driver *drv = &dax_drv->drv;
	काष्ठा dax_id *dax_id, *_id;

	mutex_lock(&dax_bus_lock);
	match_always_count -= dax_drv->match_always;
	list_क्रम_each_entry_safe(dax_id, _id, &dax_drv->ids, list) अणु
		list_del(&dax_id->list);
		kमुक्त(dax_id);
	पूर्ण
	mutex_unlock(&dax_bus_lock);
	driver_unरेजिस्टर(drv);
पूर्ण
EXPORT_SYMBOL_GPL(dax_driver_unरेजिस्टर);

पूर्णांक __init dax_bus_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (IS_ENABLED(CONFIG_DEV_DAX_PMEM_COMPAT)) अणु
		dax_class = class_create(THIS_MODULE, "dax");
		अगर (IS_ERR(dax_class))
			वापस PTR_ERR(dax_class);
	पूर्ण

	rc = bus_रेजिस्टर(&dax_bus_type);
	अगर (rc)
		class_destroy(dax_class);
	वापस rc;
पूर्ण

व्योम __निकास dax_bus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&dax_bus_type);
	class_destroy(dax_class);
पूर्ण
