<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश "adf_cfg.h"
#समावेश "adf_common_drv.h"

अटल LIST_HEAD(accel_table);
अटल LIST_HEAD(vfs_table);
अटल DEFINE_MUTEX(table_lock);
अटल u32 num_devices;
अटल u8 id_map[ADF_MAX_DEVICES];

काष्ठा vf_id_map अणु
	u32 bdf;
	u32 id;
	u32 fake_id;
	bool attached;
	काष्ठा list_head list;
पूर्ण;

अटल पूर्णांक adf_get_vf_id(काष्ठा adf_accel_dev *vf)
अणु
	वापस ((7 * (PCI_SLOT(accel_to_pci_dev(vf)->devfn) - 1)) +
		PCI_FUNC(accel_to_pci_dev(vf)->devfn) +
		(PCI_SLOT(accel_to_pci_dev(vf)->devfn) - 1));
पूर्ण

अटल पूर्णांक adf_get_vf_num(काष्ठा adf_accel_dev *vf)
अणु
	वापस (accel_to_pci_dev(vf)->bus->number << 8) | adf_get_vf_id(vf);
पूर्ण

अटल काष्ठा vf_id_map *adf_find_vf(u32 bdf)
अणु
	काष्ठा list_head *itr;

	list_क्रम_each(itr, &vfs_table) अणु
		काष्ठा vf_id_map *ptr =
			list_entry(itr, काष्ठा vf_id_map, list);

		अगर (ptr->bdf == bdf)
			वापस ptr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक adf_get_vf_real_id(u32 fake)
अणु
	काष्ठा list_head *itr;

	list_क्रम_each(itr, &vfs_table) अणु
		काष्ठा vf_id_map *ptr =
			list_entry(itr, काष्ठा vf_id_map, list);
		अगर (ptr->fake_id == fake)
			वापस ptr->id;
	पूर्ण
	वापस -1;
पूर्ण

/**
 * adf_clean_vf_map() - Cleans VF id mapings
 *
 * Function cleans पूर्णांकernal ids क्रम भव functions.
 * @vf: flag indicating whether mappings is cleaned
 *	क्रम vfs only or क्रम vfs and pfs
 */
व्योम adf_clean_vf_map(bool vf)
अणु
	काष्ठा vf_id_map *map;
	काष्ठा list_head *ptr, *पंचांगp;

	mutex_lock(&table_lock);
	list_क्रम_each_safe(ptr, पंचांगp, &vfs_table) अणु
		map = list_entry(ptr, काष्ठा vf_id_map, list);
		अगर (map->bdf != -1) अणु
			id_map[map->id] = 0;
			num_devices--;
		पूर्ण

		अगर (vf && map->bdf == -1)
			जारी;

		list_del(ptr);
		kमुक्त(map);
	पूर्ण
	mutex_unlock(&table_lock);
पूर्ण
EXPORT_SYMBOL_GPL(adf_clean_vf_map);

/**
 * adf_devmgr_update_class_index() - Update पूर्णांकernal index
 * @hw_data:  Poपूर्णांकer to पूर्णांकernal device data.
 *
 * Function updates पूर्णांकernal dev index क्रम VFs
 */
व्योम adf_devmgr_update_class_index(काष्ठा adf_hw_device_data *hw_data)
अणु
	काष्ठा adf_hw_device_class *class = hw_data->dev_class;
	काष्ठा list_head *itr;
	पूर्णांक i = 0;

	list_क्रम_each(itr, &accel_table) अणु
		काष्ठा adf_accel_dev *ptr =
				list_entry(itr, काष्ठा adf_accel_dev, list);

		अगर (ptr->hw_device->dev_class == class)
			ptr->hw_device->instance_id = i++;

		अगर (i == class->instances)
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(adf_devmgr_update_class_index);

अटल अचिन्हित पूर्णांक adf_find_मुक्त_id(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ADF_MAX_DEVICES; i++) अणु
		अगर (!id_map[i]) अणु
			id_map[i] = 1;
			वापस i;
		पूर्ण
	पूर्ण
	वापस ADF_MAX_DEVICES + 1;
पूर्ण

/**
 * adf_devmgr_add_dev() - Add accel_dev to the acceleration framework
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 * @pf:		Corresponding PF अगर the accel_dev is a VF
 *
 * Function adds acceleration device to the acceleration framework.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 on success, error code otherwise.
 */
पूर्णांक adf_devmgr_add_dev(काष्ठा adf_accel_dev *accel_dev,
		       काष्ठा adf_accel_dev *pf)
अणु
	काष्ठा list_head *itr;
	पूर्णांक ret = 0;

	अगर (num_devices == ADF_MAX_DEVICES) अणु
		dev_err(&GET_DEV(accel_dev), "Only support up to %d devices\n",
			ADF_MAX_DEVICES);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&table_lock);
	atomic_set(&accel_dev->ref_count, 0);

	/* PF on host or VF on guest - optimized to हटाओ redundant is_vf */
	अगर (!accel_dev->is_vf || !pf) अणु
		काष्ठा vf_id_map *map;

		list_क्रम_each(itr, &accel_table) अणु
			काष्ठा adf_accel_dev *ptr =
				list_entry(itr, काष्ठा adf_accel_dev, list);

			अगर (ptr == accel_dev) अणु
				ret = -EEXIST;
				जाओ unlock;
			पूर्ण
		पूर्ण

		list_add_tail(&accel_dev->list, &accel_table);
		accel_dev->accel_id = adf_find_मुक्त_id();
		अगर (accel_dev->accel_id > ADF_MAX_DEVICES) अणु
			ret = -EFAULT;
			जाओ unlock;
		पूर्ण
		num_devices++;
		map = kzalloc(माप(*map), GFP_KERNEL);
		अगर (!map) अणु
			ret = -ENOMEM;
			जाओ unlock;
		पूर्ण
		map->bdf = ~0;
		map->id = accel_dev->accel_id;
		map->fake_id = map->id;
		map->attached = true;
		list_add_tail(&map->list, &vfs_table);
	पूर्ण अन्यथा अगर (accel_dev->is_vf && pf) अणु
		/* VF on host */
		काष्ठा vf_id_map *map;

		map = adf_find_vf(adf_get_vf_num(accel_dev));
		अगर (map) अणु
			काष्ठा vf_id_map *next;

			accel_dev->accel_id = map->id;
			list_add_tail(&accel_dev->list, &accel_table);
			map->fake_id++;
			map->attached = true;
			next = list_next_entry(map, list);
			जबतक (next && &next->list != &vfs_table) अणु
				next->fake_id++;
				next = list_next_entry(next, list);
			पूर्ण

			ret = 0;
			जाओ unlock;
		पूर्ण

		map = kzalloc(माप(*map), GFP_KERNEL);
		अगर (!map) अणु
			ret = -ENOMEM;
			जाओ unlock;
		पूर्ण
		accel_dev->accel_id = adf_find_मुक्त_id();
		अगर (accel_dev->accel_id > ADF_MAX_DEVICES) अणु
			kमुक्त(map);
			ret = -EFAULT;
			जाओ unlock;
		पूर्ण
		num_devices++;
		list_add_tail(&accel_dev->list, &accel_table);
		map->bdf = adf_get_vf_num(accel_dev);
		map->id = accel_dev->accel_id;
		map->fake_id = map->id;
		map->attached = true;
		list_add_tail(&map->list, &vfs_table);
	पूर्ण
unlock:
	mutex_unlock(&table_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adf_devmgr_add_dev);

काष्ठा list_head *adf_devmgr_get_head(व्योम)
अणु
	वापस &accel_table;
पूर्ण

/**
 * adf_devmgr_rm_dev() - Remove accel_dev from the acceleration framework.
 * @accel_dev:  Poपूर्णांकer to acceleration device.
 * @pf:		Corresponding PF अगर the accel_dev is a VF
 *
 * Function हटाओs acceleration device from the acceleration framework.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम adf_devmgr_rm_dev(काष्ठा adf_accel_dev *accel_dev,
		       काष्ठा adf_accel_dev *pf)
अणु
	mutex_lock(&table_lock);
	/* PF on host or VF on guest - optimized to हटाओ redundant is_vf */
	अगर (!accel_dev->is_vf || !pf) अणु
		id_map[accel_dev->accel_id] = 0;
		num_devices--;
	पूर्ण अन्यथा अगर (accel_dev->is_vf && pf) अणु
		काष्ठा vf_id_map *map, *next;

		map = adf_find_vf(adf_get_vf_num(accel_dev));
		अगर (!map) अणु
			dev_err(&GET_DEV(accel_dev), "Failed to find VF map\n");
			जाओ unlock;
		पूर्ण
		map->fake_id--;
		map->attached = false;
		next = list_next_entry(map, list);
		जबतक (next && &next->list != &vfs_table) अणु
			next->fake_id--;
			next = list_next_entry(next, list);
		पूर्ण
	पूर्ण
unlock:
	list_del(&accel_dev->list);
	mutex_unlock(&table_lock);
पूर्ण
EXPORT_SYMBOL_GPL(adf_devmgr_rm_dev);

काष्ठा adf_accel_dev *adf_devmgr_get_first(व्योम)
अणु
	काष्ठा adf_accel_dev *dev = शून्य;

	अगर (!list_empty(&accel_table))
		dev = list_first_entry(&accel_table, काष्ठा adf_accel_dev,
				       list);
	वापस dev;
पूर्ण

/**
 * adf_devmgr_pci_to_accel_dev() - Get accel_dev associated with the pci_dev.
 * @pci_dev:  Poपूर्णांकer to PCI device.
 *
 * Function वापसs acceleration device associated with the given PCI device.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: poपूर्णांकer to accel_dev or शून्य अगर not found.
 */
काष्ठा adf_accel_dev *adf_devmgr_pci_to_accel_dev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा list_head *itr;

	mutex_lock(&table_lock);
	list_क्रम_each(itr, &accel_table) अणु
		काष्ठा adf_accel_dev *ptr =
				list_entry(itr, काष्ठा adf_accel_dev, list);

		अगर (ptr->accel_pci_dev.pci_dev == pci_dev) अणु
			mutex_unlock(&table_lock);
			वापस ptr;
		पूर्ण
	पूर्ण
	mutex_unlock(&table_lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(adf_devmgr_pci_to_accel_dev);

काष्ठा adf_accel_dev *adf_devmgr_get_dev_by_id(u32 id)
अणु
	काष्ठा list_head *itr;
	पूर्णांक real_id;

	mutex_lock(&table_lock);
	real_id = adf_get_vf_real_id(id);
	अगर (real_id < 0)
		जाओ unlock;

	id = real_id;

	list_क्रम_each(itr, &accel_table) अणु
		काष्ठा adf_accel_dev *ptr =
				list_entry(itr, काष्ठा adf_accel_dev, list);
		अगर (ptr->accel_id == id) अणु
			mutex_unlock(&table_lock);
			वापस ptr;
		पूर्ण
	पूर्ण
unlock:
	mutex_unlock(&table_lock);
	वापस शून्य;
पूर्ण

पूर्णांक adf_devmgr_verअगरy_id(u32 id)
अणु
	अगर (id == ADF_CFG_ALL_DEVICES)
		वापस 0;

	अगर (adf_devmgr_get_dev_by_id(id))
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक adf_get_num_dettached_vfs(व्योम)
अणु
	काष्ठा list_head *itr;
	पूर्णांक vfs = 0;

	mutex_lock(&table_lock);
	list_क्रम_each(itr, &vfs_table) अणु
		काष्ठा vf_id_map *ptr =
			list_entry(itr, काष्ठा vf_id_map, list);
		अगर (ptr->bdf != ~0 && !ptr->attached)
			vfs++;
	पूर्ण
	mutex_unlock(&table_lock);
	वापस vfs;
पूर्ण

व्योम adf_devmgr_get_num_dev(u32 *num)
अणु
	*num = num_devices - adf_get_num_dettached_vfs();
पूर्ण

/**
 * adf_dev_in_use() - Check whether accel_dev is currently in use
 * @accel_dev: Poपूर्णांकer to acceleration device.
 *
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 1 when device is in use, 0 otherwise.
 */
पूर्णांक adf_dev_in_use(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस atomic_पढ़ो(&accel_dev->ref_count) != 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_in_use);

/**
 * adf_dev_get() - Increment accel_dev reference count
 * @accel_dev: Poपूर्णांकer to acceleration device.
 *
 * Increment the accel_dev refcount and अगर this is the first समय
 * incrementing it during this period the accel_dev is in use,
 * increment the module refcount too.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 0 when successful, EFAULT when fail to bump module refcount
 */
पूर्णांक adf_dev_get(काष्ठा adf_accel_dev *accel_dev)
अणु
	अगर (atomic_add_वापस(1, &accel_dev->ref_count) == 1)
		अगर (!try_module_get(accel_dev->owner))
			वापस -EFAULT;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_get);

/**
 * adf_dev_put() - Decrement accel_dev reference count
 * @accel_dev: Poपूर्णांकer to acceleration device.
 *
 * Decrement the accel_dev refcount and अगर this is the last समय
 * decrementing it during this period the accel_dev is in use,
 * decrement the module refcount too.
 * To be used by QAT device specअगरic drivers.
 *
 * Return: व्योम
 */
व्योम adf_dev_put(काष्ठा adf_accel_dev *accel_dev)
अणु
	अगर (atomic_sub_वापस(1, &accel_dev->ref_count) == 0)
		module_put(accel_dev->owner);
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_put);

/**
 * adf_devmgr_in_reset() - Check whether device is in reset
 * @accel_dev: Poपूर्णांकer to acceleration device.
 *
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 1 when the device is being reset, 0 otherwise.
 */
पूर्णांक adf_devmgr_in_reset(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस test_bit(ADF_STATUS_RESTARTING, &accel_dev->status);
पूर्ण
EXPORT_SYMBOL_GPL(adf_devmgr_in_reset);

/**
 * adf_dev_started() - Check whether device has started
 * @accel_dev: Poपूर्णांकer to acceleration device.
 *
 * To be used by QAT device specअगरic drivers.
 *
 * Return: 1 when the device has started, 0 otherwise
 */
पूर्णांक adf_dev_started(काष्ठा adf_accel_dev *accel_dev)
अणु
	वापस test_bit(ADF_STATUS_STARTED, &accel_dev->status);
पूर्ण
EXPORT_SYMBOL_GPL(adf_dev_started);
