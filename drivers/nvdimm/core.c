<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/libnvdimm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ndctl.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश "nd-core.h"
#समावेश "nd.h"

LIST_HEAD(nvdimm_bus_list);
DEFINE_MUTEX(nvdimm_bus_list_mutex);

व्योम nvdimm_bus_lock(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	अगर (!nvdimm_bus)
		वापस;
	mutex_lock(&nvdimm_bus->reconfig_mutex);
पूर्ण
EXPORT_SYMBOL(nvdimm_bus_lock);

व्योम nvdimm_bus_unlock(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	अगर (!nvdimm_bus)
		वापस;
	mutex_unlock(&nvdimm_bus->reconfig_mutex);
पूर्ण
EXPORT_SYMBOL(nvdimm_bus_unlock);

bool is_nvdimm_bus_locked(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	अगर (!nvdimm_bus)
		वापस false;
	वापस mutex_is_locked(&nvdimm_bus->reconfig_mutex);
पूर्ण
EXPORT_SYMBOL(is_nvdimm_bus_locked);

काष्ठा nvdimm_map अणु
	काष्ठा nvdimm_bus *nvdimm_bus;
	काष्ठा list_head list;
	resource_माप_प्रकार offset;
	अचिन्हित दीर्घ flags;
	माप_प्रकार size;
	जोड़ अणु
		व्योम *mem;
		व्योम __iomem *iomem;
	पूर्ण;
	काष्ठा kref kref;
पूर्ण;

अटल काष्ठा nvdimm_map *find_nvdimm_map(काष्ठा device *dev,
		resource_माप_प्रकार offset)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा nvdimm_map *nvdimm_map;

	list_क्रम_each_entry(nvdimm_map, &nvdimm_bus->mapping_list, list)
		अगर (nvdimm_map->offset == offset)
			वापस nvdimm_map;
	वापस शून्य;
पूर्ण

अटल काष्ठा nvdimm_map *alloc_nvdimm_map(काष्ठा device *dev,
		resource_माप_प्रकार offset, माप_प्रकार size, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा nvdimm_map *nvdimm_map;

	nvdimm_map = kzalloc(माप(*nvdimm_map), GFP_KERNEL);
	अगर (!nvdimm_map)
		वापस शून्य;

	INIT_LIST_HEAD(&nvdimm_map->list);
	nvdimm_map->nvdimm_bus = nvdimm_bus;
	nvdimm_map->offset = offset;
	nvdimm_map->flags = flags;
	nvdimm_map->size = size;
	kref_init(&nvdimm_map->kref);

	अगर (!request_mem_region(offset, size, dev_name(&nvdimm_bus->dev))) अणु
		dev_err(&nvdimm_bus->dev, "failed to request %pa + %zd for %s\n",
				&offset, size, dev_name(dev));
		जाओ err_request_region;
	पूर्ण

	अगर (flags)
		nvdimm_map->mem = memremap(offset, size, flags);
	अन्यथा
		nvdimm_map->iomem = ioremap(offset, size);

	अगर (!nvdimm_map->mem)
		जाओ err_map;

	dev_WARN_ONCE(dev, !is_nvdimm_bus_locked(dev), "%s: bus unlocked!",
			__func__);
	list_add(&nvdimm_map->list, &nvdimm_bus->mapping_list);

	वापस nvdimm_map;

 err_map:
	release_mem_region(offset, size);
 err_request_region:
	kमुक्त(nvdimm_map);
	वापस शून्य;
पूर्ण

अटल व्योम nvdimm_map_release(काष्ठा kref *kref)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus;
	काष्ठा nvdimm_map *nvdimm_map;

	nvdimm_map = container_of(kref, काष्ठा nvdimm_map, kref);
	nvdimm_bus = nvdimm_map->nvdimm_bus;

	dev_dbg(&nvdimm_bus->dev, "%pa\n", &nvdimm_map->offset);
	list_del(&nvdimm_map->list);
	अगर (nvdimm_map->flags)
		memunmap(nvdimm_map->mem);
	अन्यथा
		iounmap(nvdimm_map->iomem);
	release_mem_region(nvdimm_map->offset, nvdimm_map->size);
	kमुक्त(nvdimm_map);
पूर्ण

अटल व्योम nvdimm_map_put(व्योम *data)
अणु
	काष्ठा nvdimm_map *nvdimm_map = data;
	काष्ठा nvdimm_bus *nvdimm_bus = nvdimm_map->nvdimm_bus;

	nvdimm_bus_lock(&nvdimm_bus->dev);
	kref_put(&nvdimm_map->kref, nvdimm_map_release);
	nvdimm_bus_unlock(&nvdimm_bus->dev);
पूर्ण

/**
 * devm_nvdimm_memremap - map a resource that is shared across regions
 * @dev: device that will own a reference to the shared mapping
 * @offset: physical base address of the mapping
 * @size: mapping size
 * @flags: memremap flags, or, अगर zero, perक्रमm an ioremap instead
 */
व्योम *devm_nvdimm_memremap(काष्ठा device *dev, resource_माप_प्रकार offset,
		माप_प्रकार size, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nvdimm_map *nvdimm_map;

	nvdimm_bus_lock(dev);
	nvdimm_map = find_nvdimm_map(dev, offset);
	अगर (!nvdimm_map)
		nvdimm_map = alloc_nvdimm_map(dev, offset, size, flags);
	अन्यथा
		kref_get(&nvdimm_map->kref);
	nvdimm_bus_unlock(dev);

	अगर (!nvdimm_map)
		वापस शून्य;

	अगर (devm_add_action_or_reset(dev, nvdimm_map_put, nvdimm_map))
		वापस शून्य;

	वापस nvdimm_map->mem;
पूर्ण
EXPORT_SYMBOL_GPL(devm_nvdimm_memremap);

u64 nd_fletcher64(व्योम *addr, माप_प्रकार len, bool le)
अणु
	u32 *buf = addr;
	u32 lo32 = 0;
	u64 hi32 = 0;
	पूर्णांक i;

	क्रम (i = 0; i < len / माप(u32); i++) अणु
		lo32 += le ? le32_to_cpu((__le32) buf[i]) : buf[i];
		hi32 += lo32;
	पूर्ण

	वापस hi32 << 32 | lo32;
पूर्ण
EXPORT_SYMBOL_GPL(nd_fletcher64);

काष्ठा nvdimm_bus_descriptor *to_nd_desc(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	/* काष्ठा nvdimm_bus definition is निजी to libnvdimm */
	वापस nvdimm_bus->nd_desc;
पूर्ण
EXPORT_SYMBOL_GPL(to_nd_desc);

काष्ठा device *to_nvdimm_bus_dev(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	/* काष्ठा nvdimm_bus definition is निजी to libnvdimm */
	वापस &nvdimm_bus->dev;
पूर्ण
EXPORT_SYMBOL_GPL(to_nvdimm_bus_dev);

अटल bool is_uuid_sep(अक्षर sep)
अणु
	अगर (sep == '\n' || sep == '-' || sep == ':' || sep == '\0')
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक nd_uuid_parse(काष्ठा device *dev, u8 *uuid_out, स्थिर अक्षर *buf,
		माप_प्रकार len)
अणु
	स्थिर अक्षर *str = buf;
	u8 uuid[16];
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		अगर (!है_षष्ठादशक(str[0]) || !है_षष्ठादशक(str[1])) अणु
			dev_dbg(dev, "pos: %d buf[%zd]: %c buf[%zd]: %c\n",
					i, str - buf, str[0],
					str + 1 - buf, str[1]);
			वापस -EINVAL;
		पूर्ण

		uuid[i] = (hex_to_bin(str[0]) << 4) | hex_to_bin(str[1]);
		str += 2;
		अगर (is_uuid_sep(*str))
			str++;
	पूर्ण

	स_नकल(uuid_out, uuid, माप(uuid));
	वापस 0;
पूर्ण

/**
 * nd_uuid_store: common implementation क्रम writing 'uuid' sysfs attributes
 * @dev: container device क्रम the uuid property
 * @uuid_out: uuid buffer to replace
 * @buf: raw sysfs buffer to parse
 *
 * Enक्रमce that uuids can only be changed जबतक the device is disabled
 * (driver detached)
 * LOCKING: expects nd_device_lock() is held on entry
 */
पूर्णांक nd_uuid_store(काष्ठा device *dev, u8 **uuid_out, स्थिर अक्षर *buf,
		माप_प्रकार len)
अणु
	u8 uuid[16];
	पूर्णांक rc;

	अगर (dev->driver)
		वापस -EBUSY;

	rc = nd_uuid_parse(dev, uuid, buf, len);
	अगर (rc)
		वापस rc;

	kमुक्त(*uuid_out);
	*uuid_out = kmemdup(uuid, माप(uuid), GFP_KERNEL);
	अगर (!(*uuid_out))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

sमाप_प्रकार nd_size_select_show(अचिन्हित दीर्घ current_size,
		स्थिर अचिन्हित दीर्घ *supported, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; supported[i]; i++)
		अगर (current_size == supported[i])
			len += प्र_लिखो(buf + len, "[%ld] ", supported[i]);
		अन्यथा
			len += प्र_लिखो(buf + len, "%ld ", supported[i]);
	len += प्र_लिखो(buf + len, "\n");
	वापस len;
पूर्ण

sमाप_प्रकार nd_size_select_store(काष्ठा device *dev, स्थिर अक्षर *buf,
		अचिन्हित दीर्घ *current_size, स्थिर अचिन्हित दीर्घ *supported)
अणु
	अचिन्हित दीर्घ lbasize;
	पूर्णांक rc, i;

	अगर (dev->driver)
		वापस -EBUSY;

	rc = kम_से_अदीर्घ(buf, 0, &lbasize);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; supported[i]; i++)
		अगर (lbasize == supported[i])
			अवरोध;

	अगर (supported[i]) अणु
		*current_size = lbasize;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार commands_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक cmd, len = 0;
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;

	क्रम_each_set_bit(cmd, &nd_desc->cmd_mask, BITS_PER_LONG)
		len += प्र_लिखो(buf + len, "%s ", nvdimm_bus_cmd_name(cmd));
	len += प्र_लिखो(buf + len, "\n");
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RO(commands);

अटल स्थिर अक्षर *nvdimm_bus_provider(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	काष्ठा device *parent = nvdimm_bus->dev.parent;

	अगर (nd_desc->provider_name)
		वापस nd_desc->provider_name;
	अन्यथा अगर (parent)
		वापस dev_name(parent);
	अन्यथा
		वापस "unknown";
पूर्ण

अटल sमाप_प्रकार provider_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);

	वापस प्र_लिखो(buf, "%s\n", nvdimm_bus_provider(nvdimm_bus));
पूर्ण
अटल DEVICE_ATTR_RO(provider);

अटल पूर्णांक flush_namespaces(काष्ठा device *dev, व्योम *data)
अणु
	nd_device_lock(dev);
	nd_device_unlock(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक flush_regions_dimms(काष्ठा device *dev, व्योम *data)
अणु
	nd_device_lock(dev);
	nd_device_unlock(dev);
	device_क्रम_each_child(dev, शून्य, flush_namespaces);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार रुको_probe_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	पूर्णांक rc;

	अगर (nd_desc->flush_probe) अणु
		rc = nd_desc->flush_probe(nd_desc);
		अगर (rc)
			वापस rc;
	पूर्ण
	nd_synchronize();
	device_क्रम_each_child(dev, शून्य, flush_regions_dimms);
	वापस प्र_लिखो(buf, "1\n");
पूर्ण
अटल DEVICE_ATTR_RO(रुको_probe);

अटल काष्ठा attribute *nvdimm_bus_attributes[] = अणु
	&dev_attr_commands.attr,
	&dev_attr_रुको_probe.attr,
	&dev_attr_provider.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nvdimm_bus_attribute_group = अणु
	.attrs = nvdimm_bus_attributes,
पूर्ण;

अटल sमाप_प्रकार capability_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	क्रमागत nvdimm_fwa_capability cap;

	अगर (!nd_desc->fw_ops)
		वापस -EOPNOTSUPP;

	nvdimm_bus_lock(dev);
	cap = nd_desc->fw_ops->capability(nd_desc);
	nvdimm_bus_unlock(dev);

	चयन (cap) अणु
	हाल NVDIMM_FWA_CAP_QUIESCE:
		वापस प्र_लिखो(buf, "quiesce\n");
	हाल NVDIMM_FWA_CAP_LIVE:
		वापस प्र_लिखो(buf, "live\n");
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल DEVICE_ATTR_RO(capability);

अटल sमाप_प्रकार activate_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	क्रमागत nvdimm_fwa_capability cap;
	क्रमागत nvdimm_fwa_state state;

	अगर (!nd_desc->fw_ops)
		वापस -EOPNOTSUPP;

	nvdimm_bus_lock(dev);
	cap = nd_desc->fw_ops->capability(nd_desc);
	state = nd_desc->fw_ops->activate_state(nd_desc);
	nvdimm_bus_unlock(dev);

	अगर (cap < NVDIMM_FWA_CAP_QUIESCE)
		वापस -EOPNOTSUPP;

	चयन (state) अणु
	हाल NVDIMM_FWA_IDLE:
		वापस प्र_लिखो(buf, "idle\n");
	हाल NVDIMM_FWA_BUSY:
		वापस प्र_लिखो(buf, "busy\n");
	हाल NVDIMM_FWA_ARMED:
		वापस प्र_लिखो(buf, "armed\n");
	हाल NVDIMM_FWA_ARM_OVERFLOW:
		वापस प्र_लिखो(buf, "overflow\n");
	शेष:
		वापस -ENXIO;
	पूर्ण
पूर्ण

अटल पूर्णांक exec_firmware_activate(व्योम *data)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = data;

	वापस nd_desc->fw_ops->activate(nd_desc);
पूर्ण

अटल sमाप_प्रकार activate_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	क्रमागत nvdimm_fwa_state state;
	bool quiesce;
	sमाप_प्रकार rc;

	अगर (!nd_desc->fw_ops)
		वापस -EOPNOTSUPP;

	अगर (sysfs_streq(buf, "live"))
		quiesce = false;
	अन्यथा अगर (sysfs_streq(buf, "quiesce"))
		quiesce = true;
	अन्यथा
		वापस -EINVAL;

	nvdimm_bus_lock(dev);
	state = nd_desc->fw_ops->activate_state(nd_desc);

	चयन (state) अणु
	हाल NVDIMM_FWA_BUSY:
		rc = -EBUSY;
		अवरोध;
	हाल NVDIMM_FWA_ARMED:
	हाल NVDIMM_FWA_ARM_OVERFLOW:
		अगर (quiesce)
			rc = hibernate_quiet_exec(exec_firmware_activate, nd_desc);
		अन्यथा
			rc = nd_desc->fw_ops->activate(nd_desc);
		अवरोध;
	हाल NVDIMM_FWA_IDLE:
	शेष:
		rc = -ENXIO;
	पूर्ण
	nvdimm_bus_unlock(dev);

	अगर (rc == 0)
		rc = len;
	वापस rc;
पूर्ण

अटल DEVICE_ATTR_ADMIN_RW(activate);

अटल umode_t nvdimm_bus_firmware_visible(काष्ठा kobject *kobj, काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	क्रमागत nvdimm_fwa_capability cap;

	/*
	 * Both 'activate' and 'capability' disappear when no ops
	 * detected, or a negative capability is indicated.
	 */
	अगर (!nd_desc->fw_ops)
		वापस 0;

	nvdimm_bus_lock(dev);
	cap = nd_desc->fw_ops->capability(nd_desc);
	nvdimm_bus_unlock(dev);

	अगर (cap < NVDIMM_FWA_CAP_QUIESCE)
		वापस 0;

	वापस a->mode;
पूर्ण
अटल काष्ठा attribute *nvdimm_bus_firmware_attributes[] = अणु
	&dev_attr_activate.attr,
	&dev_attr_capability.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nvdimm_bus_firmware_attribute_group = अणु
	.name = "firmware",
	.attrs = nvdimm_bus_firmware_attributes,
	.is_visible = nvdimm_bus_firmware_visible,
पूर्ण;

स्थिर काष्ठा attribute_group *nvdimm_bus_attribute_groups[] = अणु
	&nvdimm_bus_attribute_group,
	&nvdimm_bus_firmware_attribute_group,
	शून्य,
पूर्ण;

पूर्णांक nvdimm_bus_add_badrange(काष्ठा nvdimm_bus *nvdimm_bus, u64 addr, u64 length)
अणु
	वापस badrange_add(&nvdimm_bus->badrange, addr, length);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_bus_add_badrange);

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
पूर्णांक nd_पूर्णांकegrity_init(काष्ठा gendisk *disk, अचिन्हित दीर्घ meta_size)
अणु
	काष्ठा blk_पूर्णांकegrity bi;

	अगर (meta_size == 0)
		वापस 0;

	स_रखो(&bi, 0, माप(bi));

	bi.tuple_size = meta_size;
	bi.tag_size = meta_size;

	blk_पूर्णांकegrity_रेजिस्टर(disk, &bi);
	blk_queue_max_पूर्णांकegrity_segments(disk->queue, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nd_पूर्णांकegrity_init);

#अन्यथा /* CONFIG_BLK_DEV_INTEGRITY */
पूर्णांक nd_पूर्णांकegrity_init(काष्ठा gendisk *disk, अचिन्हित दीर्घ meta_size)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nd_पूर्णांकegrity_init);

#पूर्ण_अगर

अटल __init पूर्णांक libnvdimm_init(व्योम)
अणु
	पूर्णांक rc;

	rc = nvdimm_bus_init();
	अगर (rc)
		वापस rc;
	rc = nvdimm_init();
	अगर (rc)
		जाओ err_dimm;
	rc = nd_region_init();
	अगर (rc)
		जाओ err_region;

	nd_label_init();

	वापस 0;
 err_region:
	nvdimm_निकास();
 err_dimm:
	nvdimm_bus_निकास();
	वापस rc;
पूर्ण

अटल __निकास व्योम libnvdimm_निकास(व्योम)
अणु
	WARN_ON(!list_empty(&nvdimm_bus_list));
	nd_region_निकास();
	nvdimm_निकास();
	nvdimm_bus_निकास();
	nvdimm_devs_निकास();
पूर्ण

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
subsys_initcall(libnvdimm_init);
module_निकास(libnvdimm_निकास);
