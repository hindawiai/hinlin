<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Ltd */

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/device.h>
#समावेश "mlx5_core.h"
#समावेश "dev.h"
#समावेश "sf/vhca_event.h"
#समावेश "sf/sf.h"
#समावेश "sf/mlx5_ifc_vhca_event.h"
#समावेश "ecpf.h"

काष्ठा mlx5_sf_dev_table अणु
	काष्ठा xarray devices;
	अचिन्हित पूर्णांक max_sfs;
	phys_addr_t base_address;
	u64 sf_bar_length;
	काष्ठा notअगरier_block nb;
	काष्ठा mlx5_core_dev *dev;
पूर्ण;

अटल bool mlx5_sf_dev_supported(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_CAP_GEN(dev, sf) && mlx5_vhca_event_supported(dev);
पूर्ण

bool mlx5_sf_dev_allocated(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_dev_table *table = dev->priv.sf_dev_table;

	अगर (!mlx5_sf_dev_supported(dev))
		वापस false;

	वापस !xa_empty(&table->devices);
पूर्ण

अटल sमाप_प्रकार sfnum_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा auxiliary_device *adev = container_of(dev, काष्ठा auxiliary_device, dev);
	काष्ठा mlx5_sf_dev *sf_dev = container_of(adev, काष्ठा mlx5_sf_dev, adev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", sf_dev->sfnum);
पूर्ण
अटल DEVICE_ATTR_RO(sfnum);

अटल काष्ठा attribute *sf_device_attrs[] = अणु
	&dev_attr_sfnum.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sf_attr_group = अणु
	.attrs = sf_device_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *sf_attr_groups[2] = अणु
	&sf_attr_group,
	शून्य
पूर्ण;

अटल व्योम mlx5_sf_dev_release(काष्ठा device *device)
अणु
	काष्ठा auxiliary_device *adev = container_of(device, काष्ठा auxiliary_device, dev);
	काष्ठा mlx5_sf_dev *sf_dev = container_of(adev, काष्ठा mlx5_sf_dev, adev);

	mlx5_adev_idx_मुक्त(adev->id);
	kमुक्त(sf_dev);
पूर्ण

अटल व्योम mlx5_sf_dev_हटाओ(काष्ठा mlx5_sf_dev *sf_dev)
अणु
	auxiliary_device_delete(&sf_dev->adev);
	auxiliary_device_uninit(&sf_dev->adev);
पूर्ण

अटल व्योम mlx5_sf_dev_add(काष्ठा mlx5_core_dev *dev, u16 sf_index, u32 sfnum)
अणु
	काष्ठा mlx5_sf_dev_table *table = dev->priv.sf_dev_table;
	काष्ठा mlx5_sf_dev *sf_dev;
	काष्ठा pci_dev *pdev;
	पूर्णांक err;
	पूर्णांक id;

	id = mlx5_adev_idx_alloc();
	अगर (id < 0) अणु
		err = id;
		जाओ add_err;
	पूर्ण

	sf_dev = kzalloc(माप(*sf_dev), GFP_KERNEL);
	अगर (!sf_dev) अणु
		mlx5_adev_idx_मुक्त(id);
		err = -ENOMEM;
		जाओ add_err;
	पूर्ण
	pdev = dev->pdev;
	sf_dev->adev.id = id;
	sf_dev->adev.name = MLX5_SF_DEV_ID_NAME;
	sf_dev->adev.dev.release = mlx5_sf_dev_release;
	sf_dev->adev.dev.parent = &pdev->dev;
	sf_dev->adev.dev.groups = sf_attr_groups;
	sf_dev->sfnum = sfnum;
	sf_dev->parent_mdev = dev;

	अगर (!table->max_sfs) अणु
		mlx5_adev_idx_मुक्त(id);
		kमुक्त(sf_dev);
		err = -EOPNOTSUPP;
		जाओ add_err;
	पूर्ण
	sf_dev->bar_base_addr = table->base_address + (sf_index * table->sf_bar_length);

	err = auxiliary_device_init(&sf_dev->adev);
	अगर (err) अणु
		mlx5_adev_idx_मुक्त(id);
		kमुक्त(sf_dev);
		जाओ add_err;
	पूर्ण

	err = auxiliary_device_add(&sf_dev->adev);
	अगर (err) अणु
		put_device(&sf_dev->adev.dev);
		जाओ add_err;
	पूर्ण

	err = xa_insert(&table->devices, sf_index, sf_dev, GFP_KERNEL);
	अगर (err)
		जाओ xa_err;
	वापस;

xa_err:
	mlx5_sf_dev_हटाओ(sf_dev);
add_err:
	mlx5_core_err(dev, "SF DEV: fail device add for index=%d sfnum=%d err=%d\n",
		      sf_index, sfnum, err);
पूर्ण

अटल व्योम mlx5_sf_dev_del(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_sf_dev *sf_dev, u16 sf_index)
अणु
	काष्ठा mlx5_sf_dev_table *table = dev->priv.sf_dev_table;

	xa_erase(&table->devices, sf_index);
	mlx5_sf_dev_हटाओ(sf_dev);
पूर्ण

अटल पूर्णांक
mlx5_sf_dev_state_change_handler(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event_code, व्योम *data)
अणु
	काष्ठा mlx5_sf_dev_table *table = container_of(nb, काष्ठा mlx5_sf_dev_table, nb);
	स्थिर काष्ठा mlx5_vhca_state_event *event = data;
	काष्ठा mlx5_sf_dev *sf_dev;
	u16 max_functions;
	u16 sf_index;
	u16 base_id;

	max_functions = mlx5_sf_max_functions(table->dev);
	अगर (!max_functions)
		वापस 0;

	base_id = MLX5_CAP_GEN(table->dev, sf_base_id);
	अगर (event->function_id < base_id || event->function_id >= (base_id + max_functions))
		वापस 0;

	sf_index = event->function_id - base_id;
	sf_dev = xa_load(&table->devices, sf_index);
	चयन (event->new_vhca_state) अणु
	हाल MLX5_VHCA_STATE_INVALID:
	हाल MLX5_VHCA_STATE_ALLOCATED:
		अगर (sf_dev)
			mlx5_sf_dev_del(table->dev, sf_dev, sf_index);
		अवरोध;
	हाल MLX5_VHCA_STATE_TEARDOWN_REQUEST:
		अगर (sf_dev)
			mlx5_sf_dev_del(table->dev, sf_dev, sf_index);
		अन्यथा
			mlx5_core_err(table->dev,
				      "SF DEV: teardown state for invalid dev index=%d fn_id=0x%x\n",
				      sf_index, event->sw_function_id);
		अवरोध;
	हाल MLX5_VHCA_STATE_ACTIVE:
		अगर (!sf_dev)
			mlx5_sf_dev_add(table->dev, sf_index, event->sw_function_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_sf_dev_vhca_arm_all(काष्ठा mlx5_sf_dev_table *table)
अणु
	काष्ठा mlx5_core_dev *dev = table->dev;
	u16 max_functions;
	u16 function_id;
	पूर्णांक err = 0;
	पूर्णांक i;

	max_functions = mlx5_sf_max_functions(dev);
	function_id = MLX5_CAP_GEN(dev, sf_base_id);
	/* Arm the vhca context as the vhca event notअगरier */
	क्रम (i = 0; i < max_functions; i++) अणु
		err = mlx5_vhca_event_arm(dev, function_id);
		अगर (err)
			वापस err;

		function_id++;
	पूर्ण
	वापस 0;
पूर्ण

व्योम mlx5_sf_dev_table_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_dev_table *table;
	अचिन्हित पूर्णांक max_sfs;
	पूर्णांक err;

	अगर (!mlx5_sf_dev_supported(dev) || !mlx5_vhca_event_supported(dev))
		वापस;

	table = kzalloc(माप(*table), GFP_KERNEL);
	अगर (!table) अणु
		err = -ENOMEM;
		जाओ table_err;
	पूर्ण

	table->nb.notअगरier_call = mlx5_sf_dev_state_change_handler;
	table->dev = dev;
	अगर (MLX5_CAP_GEN(dev, max_num_sf))
		max_sfs = MLX5_CAP_GEN(dev, max_num_sf);
	अन्यथा
		max_sfs = 1 << MLX5_CAP_GEN(dev, log_max_sf);
	table->sf_bar_length = 1 << (MLX5_CAP_GEN(dev, log_min_sf_size) + 12);
	table->base_address = pci_resource_start(dev->pdev, 2);
	table->max_sfs = max_sfs;
	xa_init(&table->devices);
	dev->priv.sf_dev_table = table;

	err = mlx5_vhca_event_notअगरier_रेजिस्टर(dev, &table->nb);
	अगर (err)
		जाओ vhca_err;
	err = mlx5_sf_dev_vhca_arm_all(table);
	अगर (err)
		जाओ arm_err;
	mlx5_core_dbg(dev, "SF DEV: max sf devices=%d\n", max_sfs);
	वापस;

arm_err:
	mlx5_vhca_event_notअगरier_unरेजिस्टर(dev, &table->nb);
vhca_err:
	table->max_sfs = 0;
	kमुक्त(table);
	dev->priv.sf_dev_table = शून्य;
table_err:
	mlx5_core_err(dev, "SF DEV table create err = %d\n", err);
पूर्ण

अटल व्योम mlx5_sf_dev_destroy_all(काष्ठा mlx5_sf_dev_table *table)
अणु
	काष्ठा mlx5_sf_dev *sf_dev;
	अचिन्हित दीर्घ index;

	xa_क्रम_each(&table->devices, index, sf_dev) अणु
		xa_erase(&table->devices, index);
		mlx5_sf_dev_हटाओ(sf_dev);
	पूर्ण
पूर्ण

व्योम mlx5_sf_dev_table_destroy(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_sf_dev_table *table = dev->priv.sf_dev_table;

	अगर (!table)
		वापस;

	mlx5_vhca_event_notअगरier_unरेजिस्टर(dev, &table->nb);

	/* Now that event handler is not running, it is safe to destroy
	 * the sf device without race.
	 */
	mlx5_sf_dev_destroy_all(table);

	WARN_ON(!xa_empty(&table->devices));
	kमुक्त(table);
	dev->priv.sf_dev_table = शून्य;
पूर्ण
