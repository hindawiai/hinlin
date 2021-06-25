<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Device Feature List (DFL) Support
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Zhang Yi <yi.z.zhang@पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 */
#समावेश <linux/dfl.h>
#समावेश <linux/fpga-dfl.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

#समावेश "dfl.h"

अटल DEFINE_MUTEX(dfl_id_mutex);

/*
 * when adding a new feature dev support in DFL framework, it's required to
 * add a new item in क्रमागत dfl_id_type and provide related inक्रमmation in below
 * dfl_devs table which is indexed by dfl_id_type, e.g. name string used क्रम
 * platक्रमm device creation (define name strings in dfl.h, as they could be
 * reused by platक्रमm device drivers).
 *
 * अगर the new feature dev needs अक्षरdev support, then it's required to add
 * a new item in dfl_अक्षरdevs table and configure dfl_devs[i].devt_type as
 * index to dfl_अक्षरdevs table. If no अक्षरdev support just set devt_type
 * as one invalid index (DFL_FPGA_DEVT_MAX).
 */
क्रमागत dfl_fpga_devt_type अणु
	DFL_FPGA_DEVT_FME,
	DFL_FPGA_DEVT_PORT,
	DFL_FPGA_DEVT_MAX,
पूर्ण;

अटल काष्ठा lock_class_key dfl_pdata_keys[DFL_ID_MAX];

अटल स्थिर अक्षर *dfl_pdata_key_strings[DFL_ID_MAX] = अणु
	"dfl-fme-pdata",
	"dfl-port-pdata",
पूर्ण;

/**
 * dfl_dev_info - dfl feature device inक्रमmation.
 * @name: name string of the feature platक्रमm device.
 * @dfh_id: id value in Device Feature Header (DFH) रेजिस्टर by DFL spec.
 * @id: idr id of the feature dev.
 * @devt_type: index to dfl_chrdevs[].
 */
काष्ठा dfl_dev_info अणु
	स्थिर अक्षर *name;
	u16 dfh_id;
	काष्ठा idr id;
	क्रमागत dfl_fpga_devt_type devt_type;
पूर्ण;

/* it is indexed by dfl_id_type */
अटल काष्ठा dfl_dev_info dfl_devs[] = अणु
	अणु.name = DFL_FPGA_FEATURE_DEV_FME, .dfh_id = DFH_ID_FIU_FME,
	 .devt_type = DFL_FPGA_DEVT_FMEपूर्ण,
	अणु.name = DFL_FPGA_FEATURE_DEV_PORT, .dfh_id = DFH_ID_FIU_PORT,
	 .devt_type = DFL_FPGA_DEVT_PORTपूर्ण,
पूर्ण;

/**
 * dfl_अक्षरdev_info - अक्षरdev inक्रमmation of dfl feature device
 * @name: nmae string of the अक्षर device.
 * @devt: devt of the अक्षर device.
 */
काष्ठा dfl_अक्षरdev_info अणु
	स्थिर अक्षर *name;
	dev_t devt;
पूर्ण;

/* indexed by क्रमागत dfl_fpga_devt_type */
अटल काष्ठा dfl_अक्षरdev_info dfl_chrdevs[] = अणु
	अणु.name = DFL_FPGA_FEATURE_DEV_FMEपूर्ण,
	अणु.name = DFL_FPGA_FEATURE_DEV_PORTपूर्ण,
पूर्ण;

अटल व्योम dfl_ids_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dfl_devs); i++)
		idr_init(&dfl_devs[i].id);
पूर्ण

अटल व्योम dfl_ids_destroy(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dfl_devs); i++)
		idr_destroy(&dfl_devs[i].id);
पूर्ण

अटल पूर्णांक dfl_id_alloc(क्रमागत dfl_id_type type, काष्ठा device *dev)
अणु
	पूर्णांक id;

	WARN_ON(type >= DFL_ID_MAX);
	mutex_lock(&dfl_id_mutex);
	id = idr_alloc(&dfl_devs[type].id, dev, 0, 0, GFP_KERNEL);
	mutex_unlock(&dfl_id_mutex);

	वापस id;
पूर्ण

अटल व्योम dfl_id_मुक्त(क्रमागत dfl_id_type type, पूर्णांक id)
अणु
	WARN_ON(type >= DFL_ID_MAX);
	mutex_lock(&dfl_id_mutex);
	idr_हटाओ(&dfl_devs[type].id, id);
	mutex_unlock(&dfl_id_mutex);
पूर्ण

अटल क्रमागत dfl_id_type feature_dev_id_type(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dfl_devs); i++)
		अगर (!म_भेद(dfl_devs[i].name, pdev->name))
			वापस i;

	वापस DFL_ID_MAX;
पूर्ण

अटल क्रमागत dfl_id_type dfh_id_to_type(u16 id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dfl_devs); i++)
		अगर (dfl_devs[i].dfh_id == id)
			वापस i;

	वापस DFL_ID_MAX;
पूर्ण

/*
 * पूर्णांकroduce a global port_ops list, it allows port drivers to रेजिस्टर ops
 * in such list, then other feature devices (e.g. FME), could use the port
 * functions even related port platक्रमm device is hidden. Below is one example,
 * in भवization हाल of PCIe-based FPGA DFL device, when SRIOV is
 * enabled, port (and it's AFU) is turned पूर्णांकo VF and port platक्रमm device
 * is hidden from प्रणाली but it's still required to access port to finish FPGA
 * reconfiguration function in FME.
 */

अटल DEFINE_MUTEX(dfl_port_ops_mutex);
अटल LIST_HEAD(dfl_port_ops_list);

/**
 * dfl_fpga_port_ops_get - get matched port ops from the global list
 * @pdev: platक्रमm device to match with associated port ops.
 * Return: matched port ops on success, शून्य otherwise.
 *
 * Please note that must dfl_fpga_port_ops_put after use the port_ops.
 */
काष्ठा dfl_fpga_port_ops *dfl_fpga_port_ops_get(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_fpga_port_ops *ops = शून्य;

	mutex_lock(&dfl_port_ops_mutex);
	अगर (list_empty(&dfl_port_ops_list))
		जाओ करोne;

	list_क्रम_each_entry(ops, &dfl_port_ops_list, node) अणु
		/* match port_ops using the name of platक्रमm device */
		अगर (!म_भेद(pdev->name, ops->name)) अणु
			अगर (!try_module_get(ops->owner))
				ops = शून्य;
			जाओ करोne;
		पूर्ण
	पूर्ण

	ops = शून्य;
करोne:
	mutex_unlock(&dfl_port_ops_mutex);
	वापस ops;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_port_ops_get);

/**
 * dfl_fpga_port_ops_put - put port ops
 * @ops: port ops.
 */
व्योम dfl_fpga_port_ops_put(काष्ठा dfl_fpga_port_ops *ops)
अणु
	अगर (ops && ops->owner)
		module_put(ops->owner);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_port_ops_put);

/**
 * dfl_fpga_port_ops_add - add port_ops to global list
 * @ops: port ops to add.
 */
व्योम dfl_fpga_port_ops_add(काष्ठा dfl_fpga_port_ops *ops)
अणु
	mutex_lock(&dfl_port_ops_mutex);
	list_add_tail(&ops->node, &dfl_port_ops_list);
	mutex_unlock(&dfl_port_ops_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_port_ops_add);

/**
 * dfl_fpga_port_ops_del - हटाओ port_ops from global list
 * @ops: port ops to del.
 */
व्योम dfl_fpga_port_ops_del(काष्ठा dfl_fpga_port_ops *ops)
अणु
	mutex_lock(&dfl_port_ops_mutex);
	list_del(&ops->node);
	mutex_unlock(&dfl_port_ops_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_port_ops_del);

/**
 * dfl_fpga_check_port_id - check the port id
 * @pdev: port platक्रमm device.
 * @pport_id: port id to compare.
 *
 * Return: 1 अगर port device matches with given port id, otherwise 0.
 */
पूर्णांक dfl_fpga_check_port_id(काष्ठा platक्रमm_device *pdev, व्योम *pport_id)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dfl_fpga_port_ops *port_ops;

	अगर (pdata->id != FEATURE_DEV_ID_UNUSED)
		वापस pdata->id == *(पूर्णांक *)pport_id;

	port_ops = dfl_fpga_port_ops_get(pdev);
	अगर (!port_ops || !port_ops->get_id)
		वापस 0;

	pdata->id = port_ops->get_id(pdev);
	dfl_fpga_port_ops_put(port_ops);

	वापस pdata->id == *(पूर्णांक *)pport_id;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_check_port_id);

अटल DEFINE_IDA(dfl_device_ida);

अटल स्थिर काष्ठा dfl_device_id *
dfl_match_one_device(स्थिर काष्ठा dfl_device_id *id, काष्ठा dfl_device *ddev)
अणु
	अगर (id->type == ddev->type && id->feature_id == ddev->feature_id)
		वापस id;

	वापस शून्य;
पूर्ण

अटल पूर्णांक dfl_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा dfl_device *ddev = to_dfl_dev(dev);
	काष्ठा dfl_driver *ddrv = to_dfl_drv(drv);
	स्थिर काष्ठा dfl_device_id *id_entry;

	id_entry = ddrv->id_table;
	अगर (id_entry) अणु
		जबतक (id_entry->feature_id) अणु
			अगर (dfl_match_one_device(id_entry, ddev)) अणु
				ddev->id_entry = id_entry;
				वापस 1;
			पूर्ण
			id_entry++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dfl_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा dfl_driver *ddrv = to_dfl_drv(dev->driver);
	काष्ठा dfl_device *ddev = to_dfl_dev(dev);

	वापस ddrv->probe(ddev);
पूर्ण

अटल पूर्णांक dfl_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा dfl_driver *ddrv = to_dfl_drv(dev->driver);
	काष्ठा dfl_device *ddev = to_dfl_dev(dev);

	अगर (ddrv->हटाओ)
		ddrv->हटाओ(ddev);

	वापस 0;
पूर्ण

अटल पूर्णांक dfl_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा dfl_device *ddev = to_dfl_dev(dev);

	वापस add_uevent_var(env, "MODALIAS=dfl:t%04Xf%04X",
			      ddev->type, ddev->feature_id);
पूर्ण

अटल sमाप_प्रकार
type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_device *ddev = to_dfl_dev(dev);

	वापस प्र_लिखो(buf, "0x%x\n", ddev->type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार
feature_id_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dfl_device *ddev = to_dfl_dev(dev);

	वापस प्र_लिखो(buf, "0x%x\n", ddev->feature_id);
पूर्ण
अटल DEVICE_ATTR_RO(feature_id);

अटल काष्ठा attribute *dfl_dev_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_feature_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(dfl_dev);

अटल काष्ठा bus_type dfl_bus_type = अणु
	.name		= "dfl",
	.match		= dfl_bus_match,
	.probe		= dfl_bus_probe,
	.हटाओ		= dfl_bus_हटाओ,
	.uevent		= dfl_bus_uevent,
	.dev_groups	= dfl_dev_groups,
पूर्ण;

अटल व्योम release_dfl_dev(काष्ठा device *dev)
अणु
	काष्ठा dfl_device *ddev = to_dfl_dev(dev);

	अगर (ddev->mmio_res.parent)
		release_resource(&ddev->mmio_res);

	ida_simple_हटाओ(&dfl_device_ida, ddev->id);
	kमुक्त(ddev->irqs);
	kमुक्त(ddev);
पूर्ण

अटल काष्ठा dfl_device *
dfl_dev_add(काष्ठा dfl_feature_platक्रमm_data *pdata,
	    काष्ठा dfl_feature *feature)
अणु
	काष्ठा platक्रमm_device *pdev = pdata->dev;
	काष्ठा resource *parent_res;
	काष्ठा dfl_device *ddev;
	पूर्णांक id, i, ret;

	ddev = kzalloc(माप(*ddev), GFP_KERNEL);
	अगर (!ddev)
		वापस ERR_PTR(-ENOMEM);

	id = ida_simple_get(&dfl_device_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		dev_err(&pdev->dev, "unable to get id\n");
		kमुक्त(ddev);
		वापस ERR_PTR(id);
	पूर्ण

	/* मुक्तing resources by put_device() after device_initialize() */
	device_initialize(&ddev->dev);
	ddev->dev.parent = &pdev->dev;
	ddev->dev.bus = &dfl_bus_type;
	ddev->dev.release = release_dfl_dev;
	ddev->id = id;
	ret = dev_set_name(&ddev->dev, "dfl_dev.%d", id);
	अगर (ret)
		जाओ put_dev;

	ddev->type = feature_dev_id_type(pdev);
	ddev->feature_id = feature->id;
	ddev->cdev = pdata->dfl_cdev;

	/* add mmio resource */
	parent_res = &pdev->resource[feature->resource_index];
	ddev->mmio_res.flags = IORESOURCE_MEM;
	ddev->mmio_res.start = parent_res->start;
	ddev->mmio_res.end = parent_res->end;
	ddev->mmio_res.name = dev_name(&ddev->dev);
	ret = insert_resource(parent_res, &ddev->mmio_res);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s failed to claim resource: %pR\n",
			dev_name(&ddev->dev), &ddev->mmio_res);
		जाओ put_dev;
	पूर्ण

	/* then add irq resource */
	अगर (feature->nr_irqs) अणु
		ddev->irqs = kसुस्मृति(feature->nr_irqs,
				     माप(*ddev->irqs), GFP_KERNEL);
		अगर (!ddev->irqs) अणु
			ret = -ENOMEM;
			जाओ put_dev;
		पूर्ण

		क्रम (i = 0; i < feature->nr_irqs; i++)
			ddev->irqs[i] = feature->irq_ctx[i].irq;

		ddev->num_irqs = feature->nr_irqs;
	पूर्ण

	ret = device_add(&ddev->dev);
	अगर (ret)
		जाओ put_dev;

	dev_dbg(&pdev->dev, "add dfl_dev: %s\n", dev_name(&ddev->dev));
	वापस ddev;

put_dev:
	/* calls release_dfl_dev() which करोes the clean up  */
	put_device(&ddev->dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम dfl_devs_हटाओ(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_feature *feature;

	dfl_fpga_dev_क्रम_each_feature(pdata, feature) अणु
		अगर (feature->ddev) अणु
			device_unरेजिस्टर(&feature->ddev->dev);
			feature->ddev = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dfl_devs_add(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_feature *feature;
	काष्ठा dfl_device *ddev;
	पूर्णांक ret;

	dfl_fpga_dev_क्रम_each_feature(pdata, feature) अणु
		अगर (feature->ioaddr)
			जारी;

		अगर (feature->ddev) अणु
			ret = -EEXIST;
			जाओ err;
		पूर्ण

		ddev = dfl_dev_add(pdata, feature);
		अगर (IS_ERR(ddev)) अणु
			ret = PTR_ERR(ddev);
			जाओ err;
		पूर्ण

		feature->ddev = ddev;
	पूर्ण

	वापस 0;

err:
	dfl_devs_हटाओ(pdata);
	वापस ret;
पूर्ण

पूर्णांक __dfl_driver_रेजिस्टर(काष्ठा dfl_driver *dfl_drv, काष्ठा module *owner)
अणु
	अगर (!dfl_drv || !dfl_drv->probe || !dfl_drv->id_table)
		वापस -EINVAL;

	dfl_drv->drv.owner = owner;
	dfl_drv->drv.bus = &dfl_bus_type;

	वापस driver_रेजिस्टर(&dfl_drv->drv);
पूर्ण
EXPORT_SYMBOL(__dfl_driver_रेजिस्टर);

व्योम dfl_driver_unरेजिस्टर(काष्ठा dfl_driver *dfl_drv)
अणु
	driver_unरेजिस्टर(&dfl_drv->drv);
पूर्ण
EXPORT_SYMBOL(dfl_driver_unरेजिस्टर);

#घोषणा is_header_feature(feature) ((feature)->id == FEATURE_ID_FIU_HEADER)

/**
 * dfl_fpga_dev_feature_uinit - uinit क्रम sub features of dfl feature device
 * @pdev: feature device.
 */
व्योम dfl_fpga_dev_feature_uinit(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dfl_feature *feature;

	dfl_devs_हटाओ(pdata);

	dfl_fpga_dev_क्रम_each_feature(pdata, feature) अणु
		अगर (feature->ops) अणु
			अगर (feature->ops->uinit)
				feature->ops->uinit(pdev, feature);
			feature->ops = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_dev_feature_uinit);

अटल पूर्णांक dfl_feature_instance_init(काष्ठा platक्रमm_device *pdev,
				     काष्ठा dfl_feature_platक्रमm_data *pdata,
				     काष्ठा dfl_feature *feature,
				     काष्ठा dfl_feature_driver *drv)
अणु
	व्योम __iomem *base;
	पूर्णांक ret = 0;

	अगर (!is_header_feature(feature)) अणु
		base = devm_platक्रमm_ioremap_resource(pdev,
						      feature->resource_index);
		अगर (IS_ERR(base)) अणु
			dev_err(&pdev->dev,
				"ioremap failed for feature 0x%x!\n",
				feature->id);
			वापस PTR_ERR(base);
		पूर्ण

		feature->ioaddr = base;
	पूर्ण

	अगर (drv->ops->init) अणु
		ret = drv->ops->init(pdev, feature);
		अगर (ret)
			वापस ret;
	पूर्ण

	feature->ops = drv->ops;

	वापस ret;
पूर्ण

अटल bool dfl_feature_drv_match(काष्ठा dfl_feature *feature,
				  काष्ठा dfl_feature_driver *driver)
अणु
	स्थिर काष्ठा dfl_feature_id *ids = driver->id_table;

	अगर (ids) अणु
		जबतक (ids->id) अणु
			अगर (ids->id == feature->id)
				वापस true;
			ids++;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * dfl_fpga_dev_feature_init - init क्रम sub features of dfl feature device
 * @pdev: feature device.
 * @feature_drvs: drvs क्रम sub features.
 *
 * This function will match sub features with given feature drvs list and
 * use matched drv to init related sub feature.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_dev_feature_init(काष्ठा platक्रमm_device *pdev,
			      काष्ठा dfl_feature_driver *feature_drvs)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dfl_feature_driver *drv = feature_drvs;
	काष्ठा dfl_feature *feature;
	पूर्णांक ret;

	जबतक (drv->ops) अणु
		dfl_fpga_dev_क्रम_each_feature(pdata, feature) अणु
			अगर (dfl_feature_drv_match(feature, drv)) अणु
				ret = dfl_feature_instance_init(pdev, pdata,
								feature, drv);
				अगर (ret)
					जाओ निकास;
			पूर्ण
		पूर्ण
		drv++;
	पूर्ण

	ret = dfl_devs_add(pdata);
	अगर (ret)
		जाओ निकास;

	वापस 0;
निकास:
	dfl_fpga_dev_feature_uinit(pdev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_dev_feature_init);

अटल व्योम dfl_अक्षरdev_uinit(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < DFL_FPGA_DEVT_MAX; i++)
		अगर (MAJOR(dfl_chrdevs[i].devt)) अणु
			unरेजिस्टर_chrdev_region(dfl_chrdevs[i].devt,
						 MINORMASK + 1);
			dfl_chrdevs[i].devt = MKDEV(0, 0);
		पूर्ण
पूर्ण

अटल पूर्णांक dfl_अक्षरdev_init(व्योम)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < DFL_FPGA_DEVT_MAX; i++) अणु
		ret = alloc_chrdev_region(&dfl_chrdevs[i].devt, 0,
					  MINORMASK + 1, dfl_chrdevs[i].name);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	वापस 0;

निकास:
	dfl_अक्षरdev_uinit();
	वापस ret;
पूर्ण

अटल dev_t dfl_get_devt(क्रमागत dfl_fpga_devt_type type, पूर्णांक id)
अणु
	अगर (type >= DFL_FPGA_DEVT_MAX)
		वापस 0;

	वापस MKDEV(MAJOR(dfl_chrdevs[type].devt), id);
पूर्ण

/**
 * dfl_fpga_dev_ops_रेजिस्टर - रेजिस्टर cdev ops क्रम feature dev
 *
 * @pdev: feature dev.
 * @fops: file operations क्रम feature dev's cdev.
 * @owner: owning module/driver.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_dev_ops_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			      स्थिर काष्ठा file_operations *fops,
			      काष्ठा module *owner)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	cdev_init(&pdata->cdev, fops);
	pdata->cdev.owner = owner;

	/*
	 * set parent to the feature device so that its refcount is
	 * decreased after the last refcount of cdev is gone, that
	 * makes sure the feature device is valid during device
	 * file's lअगरe-cycle.
	 */
	pdata->cdev.kobj.parent = &pdev->dev.kobj;

	वापस cdev_add(&pdata->cdev, pdev->dev.devt, 1);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_dev_ops_रेजिस्टर);

/**
 * dfl_fpga_dev_ops_unरेजिस्टर - unरेजिस्टर cdev ops क्रम feature dev
 * @pdev: feature dev.
 */
व्योम dfl_fpga_dev_ops_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);

	cdev_del(&pdata->cdev);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_dev_ops_unरेजिस्टर);

/**
 * काष्ठा build_feature_devs_info - info collected during feature dev build.
 *
 * @dev: device to क्रमागतerate.
 * @cdev: the container device क्रम all feature devices.
 * @nr_irqs: number of irqs क्रम all feature devices.
 * @irq_table: Linux IRQ numbers क्रम all irqs, indexed by local irq index of
 *	       this device.
 * @feature_dev: current feature device.
 * @ioaddr: header रेजिस्टर region address of current FIU in क्रमागतeration.
 * @start: रेजिस्टर resource start of current FIU.
 * @len: max रेजिस्टर resource length of current FIU.
 * @sub_features: a sub features linked list क्रम feature device in क्रमागतeration.
 * @feature_num: number of sub features क्रम feature device in क्रमागतeration.
 */
काष्ठा build_feature_devs_info अणु
	काष्ठा device *dev;
	काष्ठा dfl_fpga_cdev *cdev;
	अचिन्हित पूर्णांक nr_irqs;
	पूर्णांक *irq_table;

	काष्ठा platक्रमm_device *feature_dev;
	व्योम __iomem *ioaddr;
	resource_माप_प्रकार start;
	resource_माप_प्रकार len;
	काष्ठा list_head sub_features;
	पूर्णांक feature_num;
पूर्ण;

/**
 * काष्ठा dfl_feature_info - sub feature info collected during feature dev build
 *
 * @fid: id of this sub feature.
 * @mmio_res: mmio resource of this sub feature.
 * @ioaddr: mapped base address of mmio resource.
 * @node: node in sub_features linked list.
 * @irq_base: start of irq index in this sub feature.
 * @nr_irqs: number of irqs of this sub feature.
 */
काष्ठा dfl_feature_info अणु
	u16 fid;
	काष्ठा resource mmio_res;
	व्योम __iomem *ioaddr;
	काष्ठा list_head node;
	अचिन्हित पूर्णांक irq_base;
	अचिन्हित पूर्णांक nr_irqs;
पूर्ण;

अटल व्योम dfl_fpga_cdev_add_port_dev(काष्ठा dfl_fpga_cdev *cdev,
				       काष्ठा platक्रमm_device *port)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&port->dev);

	mutex_lock(&cdev->lock);
	list_add(&pdata->node, &cdev->port_dev_list);
	get_device(&pdata->dev->dev);
	mutex_unlock(&cdev->lock);
पूर्ण

/*
 * रेजिस्टर current feature device, it is called when we need to चयन to
 * another feature parsing or we have parsed all features on given device
 * feature list.
 */
अटल पूर्णांक build_info_commit_dev(काष्ठा build_feature_devs_info *binfo)
अणु
	काष्ठा platक्रमm_device *fdev = binfo->feature_dev;
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	काष्ठा dfl_feature_info *finfo, *p;
	क्रमागत dfl_id_type type;
	पूर्णांक ret, index = 0, res_idx = 0;

	type = feature_dev_id_type(fdev);
	अगर (WARN_ON_ONCE(type >= DFL_ID_MAX))
		वापस -EINVAL;

	/*
	 * we करो not need to care क्रम the memory which is associated with
	 * the platक्रमm device. After calling platक्रमm_device_unरेजिस्टर(),
	 * it will be स्वतःmatically मुक्तd by device's release() callback,
	 * platक्रमm_device_release().
	 */
	pdata = kzalloc(काष्ठा_size(pdata, features, binfo->feature_num), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->dev = fdev;
	pdata->num = binfo->feature_num;
	pdata->dfl_cdev = binfo->cdev;
	pdata->id = FEATURE_DEV_ID_UNUSED;
	mutex_init(&pdata->lock);
	lockdep_set_class_and_name(&pdata->lock, &dfl_pdata_keys[type],
				   dfl_pdata_key_strings[type]);

	/*
	 * the count should be initialized to 0 to make sure
	 *__fpga_port_enable() following __fpga_port_disable()
	 * works properly क्रम port device.
	 * and it should always be 0 क्रम fme device.
	 */
	WARN_ON(pdata->disable_count);

	fdev->dev.platक्रमm_data = pdata;

	/* each sub feature has one MMIO resource */
	fdev->num_resources = binfo->feature_num;
	fdev->resource = kसुस्मृति(binfo->feature_num, माप(*fdev->resource),
				 GFP_KERNEL);
	अगर (!fdev->resource)
		वापस -ENOMEM;

	/* fill features and resource inक्रमmation क्रम feature dev */
	list_क्रम_each_entry_safe(finfo, p, &binfo->sub_features, node) अणु
		काष्ठा dfl_feature *feature = &pdata->features[index++];
		काष्ठा dfl_feature_irq_ctx *ctx;
		अचिन्हित पूर्णांक i;

		/* save resource inक्रमmation क्रम each feature */
		feature->dev = fdev;
		feature->id = finfo->fid;

		/*
		 * the FIU header feature has some fundamental functions (sriov
		 * set, port enable/disable) needed क्रम the dfl bus device and
		 * other sub features. So its mmio resource should be mapped by
		 * DFL bus device. And we should not assign it to feature
		 * devices (dfl-fme/afu) again.
		 */
		अगर (is_header_feature(feature)) अणु
			feature->resource_index = -1;
			feature->ioaddr =
				devm_ioremap_resource(binfo->dev,
						      &finfo->mmio_res);
			अगर (IS_ERR(feature->ioaddr))
				वापस PTR_ERR(feature->ioaddr);
		पूर्ण अन्यथा अणु
			feature->resource_index = res_idx;
			fdev->resource[res_idx++] = finfo->mmio_res;
		पूर्ण

		अगर (finfo->nr_irqs) अणु
			ctx = devm_kसुस्मृति(binfo->dev, finfo->nr_irqs,
					   माप(*ctx), GFP_KERNEL);
			अगर (!ctx)
				वापस -ENOMEM;

			क्रम (i = 0; i < finfo->nr_irqs; i++)
				ctx[i].irq =
					binfo->irq_table[finfo->irq_base + i];

			feature->irq_ctx = ctx;
			feature->nr_irqs = finfo->nr_irqs;
		पूर्ण

		list_del(&finfo->node);
		kमुक्त(finfo);
	पूर्ण

	ret = platक्रमm_device_add(binfo->feature_dev);
	अगर (!ret) अणु
		अगर (type == PORT_ID)
			dfl_fpga_cdev_add_port_dev(binfo->cdev,
						   binfo->feature_dev);
		अन्यथा
			binfo->cdev->fme_dev =
					get_device(&binfo->feature_dev->dev);
		/*
		 * reset it to aव्योम build_info_मुक्त() मुक्तing their resource.
		 *
		 * The resource of successfully रेजिस्टरed feature devices
		 * will be मुक्तd by platक्रमm_device_unरेजिस्टर(). See the
		 * comments in build_info_create_dev().
		 */
		binfo->feature_dev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
build_info_create_dev(काष्ठा build_feature_devs_info *binfo,
		      क्रमागत dfl_id_type type)
अणु
	काष्ठा platक्रमm_device *fdev;

	अगर (type >= DFL_ID_MAX)
		वापस -EINVAL;

	/*
	 * we use -ENODEV as the initialization indicator which indicates
	 * whether the id need to be reclaimed
	 */
	fdev = platक्रमm_device_alloc(dfl_devs[type].name, -ENODEV);
	अगर (!fdev)
		वापस -ENOMEM;

	binfo->feature_dev = fdev;
	binfo->feature_num = 0;

	INIT_LIST_HEAD(&binfo->sub_features);

	fdev->id = dfl_id_alloc(type, &fdev->dev);
	अगर (fdev->id < 0)
		वापस fdev->id;

	fdev->dev.parent = &binfo->cdev->region->dev;
	fdev->dev.devt = dfl_get_devt(dfl_devs[type].devt_type, fdev->id);

	वापस 0;
पूर्ण

अटल व्योम build_info_मुक्त(काष्ठा build_feature_devs_info *binfo)
अणु
	काष्ठा dfl_feature_info *finfo, *p;

	/*
	 * it is a valid id, मुक्त it. See comments in
	 * build_info_create_dev()
	 */
	अगर (binfo->feature_dev && binfo->feature_dev->id >= 0) अणु
		dfl_id_मुक्त(feature_dev_id_type(binfo->feature_dev),
			    binfo->feature_dev->id);

		list_क्रम_each_entry_safe(finfo, p, &binfo->sub_features, node) अणु
			list_del(&finfo->node);
			kमुक्त(finfo);
		पूर्ण
	पूर्ण

	platक्रमm_device_put(binfo->feature_dev);

	devm_kमुक्त(binfo->dev, binfo);
पूर्ण

अटल अंतरभूत u32 feature_size(व्योम __iomem *start)
अणु
	u64 v = पढ़ोq(start + DFH);
	u32 ofst = FIELD_GET(DFH_NEXT_HDR_OFST, v);
	/* workaround क्रम निजी features with invalid size, use 4K instead */
	वापस ofst ? ofst : 4096;
पूर्ण

अटल u16 feature_id(व्योम __iomem *start)
अणु
	u64 v = पढ़ोq(start + DFH);
	u16 id = FIELD_GET(DFH_ID, v);
	u8 type = FIELD_GET(DFH_TYPE, v);

	अगर (type == DFH_TYPE_FIU)
		वापस FEATURE_ID_FIU_HEADER;
	अन्यथा अगर (type == DFH_TYPE_PRIVATE)
		वापस id;
	अन्यथा अगर (type == DFH_TYPE_AFU)
		वापस FEATURE_ID_AFU;

	WARN_ON(1);
	वापस 0;
पूर्ण

अटल पूर्णांक parse_feature_irqs(काष्ठा build_feature_devs_info *binfo,
			      resource_माप_प्रकार ofst, u16 fid,
			      अचिन्हित पूर्णांक *irq_base, अचिन्हित पूर्णांक *nr_irqs)
अणु
	व्योम __iomem *base = binfo->ioaddr + ofst;
	अचिन्हित पूर्णांक i, ibase, inr = 0;
	पूर्णांक virq;
	u64 v;

	/*
	 * Ideally DFL framework should only पढ़ो info from DFL header, but
	 * current version DFL only provides mmio resources inक्रमmation क्रम
	 * each feature in DFL Header, no field क्रम पूर्णांकerrupt resources.
	 * Interrupt resource inक्रमmation is provided by specअगरic mmio
	 * रेजिस्टरs of each निजी feature which supports पूर्णांकerrupt. So in
	 * order to parse and assign irq resources, DFL framework has to look
	 * पूर्णांकo specअगरic capability रेजिस्टरs of these निजी features.
	 *
	 * Once future DFL version supports generic पूर्णांकerrupt resource
	 * inक्रमmation in common DFL headers, the generic पूर्णांकerrupt parsing
	 * code will be added. But in order to be compatible to old version
	 * DFL, the driver may still fall back to these quirks.
	 */
	चयन (fid) अणु
	हाल PORT_FEATURE_ID_UINT:
		v = पढ़ोq(base + PORT_UINT_CAP);
		ibase = FIELD_GET(PORT_UINT_CAP_FST_VECT, v);
		inr = FIELD_GET(PORT_UINT_CAP_INT_NUM, v);
		अवरोध;
	हाल PORT_FEATURE_ID_ERROR:
		v = पढ़ोq(base + PORT_ERROR_CAP);
		ibase = FIELD_GET(PORT_ERROR_CAP_INT_VECT, v);
		inr = FIELD_GET(PORT_ERROR_CAP_SUPP_INT, v);
		अवरोध;
	हाल FME_FEATURE_ID_GLOBAL_ERR:
		v = पढ़ोq(base + FME_ERROR_CAP);
		ibase = FIELD_GET(FME_ERROR_CAP_INT_VECT, v);
		inr = FIELD_GET(FME_ERROR_CAP_SUPP_INT, v);
		अवरोध;
	पूर्ण

	अगर (!inr) अणु
		*irq_base = 0;
		*nr_irqs = 0;
		वापस 0;
	पूर्ण

	dev_dbg(binfo->dev, "feature: 0x%x, irq_base: %u, nr_irqs: %u\n",
		fid, ibase, inr);

	अगर (ibase + inr > binfo->nr_irqs) अणु
		dev_err(binfo->dev,
			"Invalid interrupt number in feature 0x%x\n", fid);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < inr; i++) अणु
		virq = binfo->irq_table[ibase + i];
		अगर (virq < 0 || virq > NR_IRQS) अणु
			dev_err(binfo->dev,
				"Invalid irq table entry for feature 0x%x\n",
				fid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	*irq_base = ibase;
	*nr_irqs = inr;

	वापस 0;
पूर्ण

/*
 * when create sub feature instances, क्रम निजी features, it करोesn't need
 * to provide resource size and feature id as they could be पढ़ो from DFH
 * रेजिस्टर. For afu sub feature, its रेजिस्टर region only contains user
 * defined रेजिस्टरs, so never trust any inक्रमmation from it, just use the
 * resource size inक्रमmation provided by its parent FIU.
 */
अटल पूर्णांक
create_feature_instance(काष्ठा build_feature_devs_info *binfo,
			resource_माप_प्रकार ofst, resource_माप_प्रकार size, u16 fid)
अणु
	अचिन्हित पूर्णांक irq_base, nr_irqs;
	काष्ठा dfl_feature_info *finfo;
	पूर्णांक ret;

	/* पढ़ो feature size and id अगर inमाला_दो are invalid */
	size = size ? size : feature_size(binfo->ioaddr + ofst);
	fid = fid ? fid : feature_id(binfo->ioaddr + ofst);

	अगर (binfo->len - ofst < size)
		वापस -EINVAL;

	ret = parse_feature_irqs(binfo, ofst, fid, &irq_base, &nr_irqs);
	अगर (ret)
		वापस ret;

	finfo = kzalloc(माप(*finfo), GFP_KERNEL);
	अगर (!finfo)
		वापस -ENOMEM;

	finfo->fid = fid;
	finfo->mmio_res.start = binfo->start + ofst;
	finfo->mmio_res.end = finfo->mmio_res.start + size - 1;
	finfo->mmio_res.flags = IORESOURCE_MEM;
	finfo->irq_base = irq_base;
	finfo->nr_irqs = nr_irqs;

	list_add_tail(&finfo->node, &binfo->sub_features);
	binfo->feature_num++;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_feature_port_afu(काष्ठा build_feature_devs_info *binfo,
				  resource_माप_प्रकार ofst)
अणु
	u64 v = पढ़ोq(binfo->ioaddr + PORT_HDR_CAP);
	u32 size = FIELD_GET(PORT_CAP_MMIO_SIZE, v) << 10;

	WARN_ON(!size);

	वापस create_feature_instance(binfo, ofst, size, FEATURE_ID_AFU);
पूर्ण

#घोषणा is_feature_dev_detected(binfo) (!!(binfo)->feature_dev)

अटल पूर्णांक parse_feature_afu(काष्ठा build_feature_devs_info *binfo,
			     resource_माप_प्रकार ofst)
अणु
	अगर (!is_feature_dev_detected(binfo)) अणु
		dev_err(binfo->dev, "this AFU does not belong to any FIU.\n");
		वापस -EINVAL;
	पूर्ण

	चयन (feature_dev_id_type(binfo->feature_dev)) अणु
	हाल PORT_ID:
		वापस parse_feature_port_afu(binfo, ofst);
	शेष:
		dev_info(binfo->dev, "AFU belonging to FIU %s is not supported yet.\n",
			 binfo->feature_dev->name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक build_info_prepare(काष्ठा build_feature_devs_info *binfo,
			      resource_माप_प्रकार start, resource_माप_प्रकार len)
अणु
	काष्ठा device *dev = binfo->dev;
	व्योम __iomem *ioaddr;

	अगर (!devm_request_mem_region(dev, start, len, dev_name(dev))) अणु
		dev_err(dev, "request region fail, start:%pa, len:%pa\n",
			&start, &len);
		वापस -EBUSY;
	पूर्ण

	ioaddr = devm_ioremap(dev, start, len);
	अगर (!ioaddr) अणु
		dev_err(dev, "ioremap region fail, start:%pa, len:%pa\n",
			&start, &len);
		वापस -ENOMEM;
	पूर्ण

	binfo->start = start;
	binfo->len = len;
	binfo->ioaddr = ioaddr;

	वापस 0;
पूर्ण

अटल व्योम build_info_complete(काष्ठा build_feature_devs_info *binfo)
अणु
	devm_iounmap(binfo->dev, binfo->ioaddr);
	devm_release_mem_region(binfo->dev, binfo->start, binfo->len);
पूर्ण

अटल पूर्णांक parse_feature_fiu(काष्ठा build_feature_devs_info *binfo,
			     resource_माप_प्रकार ofst)
अणु
	पूर्णांक ret = 0;
	u32 offset;
	u16 id;
	u64 v;

	अगर (is_feature_dev_detected(binfo)) अणु
		build_info_complete(binfo);

		ret = build_info_commit_dev(binfo);
		अगर (ret)
			वापस ret;

		ret = build_info_prepare(binfo, binfo->start + ofst,
					 binfo->len - ofst);
		अगर (ret)
			वापस ret;
	पूर्ण

	v = पढ़ोq(binfo->ioaddr + DFH);
	id = FIELD_GET(DFH_ID, v);

	/* create platक्रमm device क्रम dfl feature dev */
	ret = build_info_create_dev(binfo, dfh_id_to_type(id));
	अगर (ret)
		वापस ret;

	ret = create_feature_instance(binfo, 0, 0, 0);
	अगर (ret)
		वापस ret;
	/*
	 * find and parse FIU's child AFU via its NEXT_AFU रेजिस्टर.
	 * please note that only Port has valid NEXT_AFU poपूर्णांकer per spec.
	 */
	v = पढ़ोq(binfo->ioaddr + NEXT_AFU);

	offset = FIELD_GET(NEXT_AFU_NEXT_DFH_OFST, v);
	अगर (offset)
		वापस parse_feature_afu(binfo, offset);

	dev_dbg(binfo->dev, "No AFUs detected on FIU %d\n", id);

	वापस ret;
पूर्ण

अटल पूर्णांक parse_feature_निजी(काष्ठा build_feature_devs_info *binfo,
				 resource_माप_प्रकार ofst)
अणु
	अगर (!is_feature_dev_detected(binfo)) अणु
		dev_err(binfo->dev, "the private feature 0x%x does not belong to any AFU.\n",
			feature_id(binfo->ioaddr + ofst));
		वापस -EINVAL;
	पूर्ण

	वापस create_feature_instance(binfo, ofst, 0, 0);
पूर्ण

/**
 * parse_feature - parse a feature on given device feature list
 *
 * @binfo: build feature devices inक्रमmation.
 * @ofst: offset to current FIU header
 */
अटल पूर्णांक parse_feature(काष्ठा build_feature_devs_info *binfo,
			 resource_माप_प्रकार ofst)
अणु
	u64 v;
	u32 type;

	v = पढ़ोq(binfo->ioaddr + ofst + DFH);
	type = FIELD_GET(DFH_TYPE, v);

	चयन (type) अणु
	हाल DFH_TYPE_AFU:
		वापस parse_feature_afu(binfo, ofst);
	हाल DFH_TYPE_PRIVATE:
		वापस parse_feature_निजी(binfo, ofst);
	हाल DFH_TYPE_FIU:
		वापस parse_feature_fiu(binfo, ofst);
	शेष:
		dev_info(binfo->dev,
			 "Feature Type %x is not supported.\n", type);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक parse_feature_list(काष्ठा build_feature_devs_info *binfo,
			      resource_माप_प्रकार start, resource_माप_प्रकार len)
अणु
	resource_माप_प्रकार end = start + len;
	पूर्णांक ret = 0;
	u32 ofst = 0;
	u64 v;

	ret = build_info_prepare(binfo, start, len);
	अगर (ret)
		वापस ret;

	/* walk through the device feature list via DFH's next DFH poपूर्णांकer. */
	क्रम (; start < end; start += ofst) अणु
		अगर (end - start < DFH_SIZE) अणु
			dev_err(binfo->dev, "The region is too small to contain a feature.\n");
			वापस -EINVAL;
		पूर्ण

		ret = parse_feature(binfo, start - binfo->start);
		अगर (ret)
			वापस ret;

		v = पढ़ोq(binfo->ioaddr + start - binfo->start + DFH);
		ofst = FIELD_GET(DFH_NEXT_HDR_OFST, v);

		/* stop parsing अगर EOL(End of List) is set or offset is 0 */
		अगर ((v & DFH_EOL) || !ofst)
			अवरोध;
	पूर्ण

	/* commit current feature device when reach the end of list */
	build_info_complete(binfo);

	अगर (is_feature_dev_detected(binfo))
		ret = build_info_commit_dev(binfo);

	वापस ret;
पूर्ण

काष्ठा dfl_fpga_क्रमागत_info *dfl_fpga_क्रमागत_info_alloc(काष्ठा device *dev)
अणु
	काष्ठा dfl_fpga_क्रमागत_info *info;

	get_device(dev);

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		put_device(dev);
		वापस शून्य;
	पूर्ण

	info->dev = dev;
	INIT_LIST_HEAD(&info->dfls);

	वापस info;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_क्रमागत_info_alloc);

व्योम dfl_fpga_क्रमागत_info_मुक्त(काष्ठा dfl_fpga_क्रमागत_info *info)
अणु
	काष्ठा dfl_fpga_क्रमागत_dfl *पंचांगp, *dfl;
	काष्ठा device *dev;

	अगर (!info)
		वापस;

	dev = info->dev;

	/* हटाओ all device feature lists in the list. */
	list_क्रम_each_entry_safe(dfl, पंचांगp, &info->dfls, node) अणु
		list_del(&dfl->node);
		devm_kमुक्त(dev, dfl);
	पूर्ण

	/* हटाओ irq table */
	अगर (info->irq_table)
		devm_kमुक्त(dev, info->irq_table);

	devm_kमुक्त(dev, info);
	put_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_क्रमागत_info_मुक्त);

/**
 * dfl_fpga_क्रमागत_info_add_dfl - add info of a device feature list to क्रमागत info
 *
 * @info: ptr to dfl_fpga_क्रमागत_info
 * @start: mmio resource address of the device feature list.
 * @len: mmio resource length of the device feature list.
 *
 * One FPGA device may have one or more Device Feature Lists (DFLs), use this
 * function to add inक्रमmation of each DFL to common data काष्ठाure क्रम next
 * step क्रमागतeration.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_क्रमागत_info_add_dfl(काष्ठा dfl_fpga_क्रमागत_info *info,
			       resource_माप_प्रकार start, resource_माप_प्रकार len)
अणु
	काष्ठा dfl_fpga_क्रमागत_dfl *dfl;

	dfl = devm_kzalloc(info->dev, माप(*dfl), GFP_KERNEL);
	अगर (!dfl)
		वापस -ENOMEM;

	dfl->start = start;
	dfl->len = len;

	list_add_tail(&dfl->node, &info->dfls);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_क्रमागत_info_add_dfl);

/**
 * dfl_fpga_क्रमागत_info_add_irq - add irq table to क्रमागत info
 *
 * @info: ptr to dfl_fpga_क्रमागत_info
 * @nr_irqs: number of irqs of the DFL fpga device to be क्रमागतerated.
 * @irq_table: Linux IRQ numbers क्रम all irqs, indexed by local irq index of
 *	       this device.
 *
 * One FPGA device may have several पूर्णांकerrupts. This function adds irq
 * inक्रमmation of the DFL fpga device to क्रमागत info क्रम next step क्रमागतeration.
 * This function should be called beक्रमe dfl_fpga_feature_devs_क्रमागतerate().
 * As we only support one irq करोमुख्य क्रम all DFLs in the same क्रमागत info, adding
 * irq table a second समय क्रम the same क्रमागत info will वापस error.
 *
 * If we need to क्रमागतerate DFLs which beदीर्घ to dअगरferent irq करोमुख्यs, we
 * should fill more क्रमागत info and क्रमागतerate them one by one.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_क्रमागत_info_add_irq(काष्ठा dfl_fpga_क्रमागत_info *info,
			       अचिन्हित पूर्णांक nr_irqs, पूर्णांक *irq_table)
अणु
	अगर (!nr_irqs || !irq_table)
		वापस -EINVAL;

	अगर (info->irq_table)
		वापस -EEXIST;

	info->irq_table = devm_kmemdup(info->dev, irq_table,
				       माप(पूर्णांक) * nr_irqs, GFP_KERNEL);
	अगर (!info->irq_table)
		वापस -ENOMEM;

	info->nr_irqs = nr_irqs;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_क्रमागत_info_add_irq);

अटल पूर्णांक हटाओ_feature_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	क्रमागत dfl_id_type type = feature_dev_id_type(pdev);
	पूर्णांक id = pdev->id;

	platक्रमm_device_unरेजिस्टर(pdev);

	dfl_id_मुक्त(type, id);

	वापस 0;
पूर्ण

अटल व्योम हटाओ_feature_devs(काष्ठा dfl_fpga_cdev *cdev)
अणु
	device_क्रम_each_child(&cdev->region->dev, शून्य, हटाओ_feature_dev);
पूर्ण

/**
 * dfl_fpga_feature_devs_क्रमागतerate - क्रमागतerate feature devices
 * @info: inक्रमmation क्रम क्रमागतeration.
 *
 * This function creates a container device (base FPGA region), क्रमागतerates
 * feature devices based on the क्रमागतeration info and creates platक्रमm devices
 * under the container device.
 *
 * Return: dfl_fpga_cdev काष्ठा on success, -त्रुटि_सं on failure
 */
काष्ठा dfl_fpga_cdev *
dfl_fpga_feature_devs_क्रमागतerate(काष्ठा dfl_fpga_क्रमागत_info *info)
अणु
	काष्ठा build_feature_devs_info *binfo;
	काष्ठा dfl_fpga_क्रमागत_dfl *dfl;
	काष्ठा dfl_fpga_cdev *cdev;
	पूर्णांक ret = 0;

	अगर (!info->dev)
		वापस ERR_PTR(-ENODEV);

	cdev = devm_kzalloc(info->dev, माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस ERR_PTR(-ENOMEM);

	cdev->region = devm_fpga_region_create(info->dev, शून्य, शून्य);
	अगर (!cdev->region) अणु
		ret = -ENOMEM;
		जाओ मुक्त_cdev_निकास;
	पूर्ण

	cdev->parent = info->dev;
	mutex_init(&cdev->lock);
	INIT_LIST_HEAD(&cdev->port_dev_list);

	ret = fpga_region_रेजिस्टर(cdev->region);
	अगर (ret)
		जाओ मुक्त_cdev_निकास;

	/* create and init build info क्रम क्रमागतeration */
	binfo = devm_kzalloc(info->dev, माप(*binfo), GFP_KERNEL);
	अगर (!binfo) अणु
		ret = -ENOMEM;
		जाओ unरेजिस्टर_region_निकास;
	पूर्ण

	binfo->dev = info->dev;
	binfo->cdev = cdev;

	binfo->nr_irqs = info->nr_irqs;
	अगर (info->nr_irqs)
		binfo->irq_table = info->irq_table;

	/*
	 * start क्रमागतeration क्रम all feature devices based on Device Feature
	 * Lists.
	 */
	list_क्रम_each_entry(dfl, &info->dfls, node) अणु
		ret = parse_feature_list(binfo, dfl->start, dfl->len);
		अगर (ret) अणु
			हटाओ_feature_devs(cdev);
			build_info_मुक्त(binfo);
			जाओ unरेजिस्टर_region_निकास;
		पूर्ण
	पूर्ण

	build_info_मुक्त(binfo);

	वापस cdev;

unरेजिस्टर_region_निकास:
	fpga_region_unरेजिस्टर(cdev->region);
मुक्त_cdev_निकास:
	devm_kमुक्त(info->dev, cdev);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_feature_devs_क्रमागतerate);

/**
 * dfl_fpga_feature_devs_हटाओ - हटाओ all feature devices
 * @cdev: fpga container device.
 *
 * Remove the container device and all feature devices under given container
 * devices.
 */
व्योम dfl_fpga_feature_devs_हटाओ(काष्ठा dfl_fpga_cdev *cdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata, *pपंचांगp;

	mutex_lock(&cdev->lock);
	अगर (cdev->fme_dev)
		put_device(cdev->fme_dev);

	list_क्रम_each_entry_safe(pdata, pपंचांगp, &cdev->port_dev_list, node) अणु
		काष्ठा platक्रमm_device *port_dev = pdata->dev;

		/* हटाओ released ports */
		अगर (!device_is_रेजिस्टरed(&port_dev->dev)) अणु
			dfl_id_मुक्त(feature_dev_id_type(port_dev),
				    port_dev->id);
			platक्रमm_device_put(port_dev);
		पूर्ण

		list_del(&pdata->node);
		put_device(&port_dev->dev);
	पूर्ण
	mutex_unlock(&cdev->lock);

	हटाओ_feature_devs(cdev);

	fpga_region_unरेजिस्टर(cdev->region);
	devm_kमुक्त(cdev->parent, cdev);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_feature_devs_हटाओ);

/**
 * __dfl_fpga_cdev_find_port - find a port under given container device
 *
 * @cdev: container device
 * @data: data passed to match function
 * @match: match function used to find specअगरic port from the port device list
 *
 * Find a port device under container device. This function needs to be
 * invoked with lock held.
 *
 * Return: poपूर्णांकer to port's platक्रमm device अगर successful, शून्य otherwise.
 *
 * NOTE: you will need to drop the device reference with put_device() after use.
 */
काष्ठा platक्रमm_device *
__dfl_fpga_cdev_find_port(काष्ठा dfl_fpga_cdev *cdev, व्योम *data,
			  पूर्णांक (*match)(काष्ठा platक्रमm_device *, व्योम *))
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	काष्ठा platक्रमm_device *port_dev;

	list_क्रम_each_entry(pdata, &cdev->port_dev_list, node) अणु
		port_dev = pdata->dev;

		अगर (match(port_dev, data) && get_device(&port_dev->dev))
			वापस port_dev;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(__dfl_fpga_cdev_find_port);

अटल पूर्णांक __init dfl_fpga_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&dfl_bus_type);
	अगर (ret)
		वापस ret;

	dfl_ids_init();

	ret = dfl_अक्षरdev_init();
	अगर (ret) अणु
		dfl_ids_destroy();
		bus_unरेजिस्टर(&dfl_bus_type);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dfl_fpga_cdev_release_port - release a port platक्रमm device
 *
 * @cdev: parent container device.
 * @port_id: id of the port platक्रमm device.
 *
 * This function allows user to release a port platक्रमm device. This is a
 * mandatory step beक्रमe turn a port from PF पूर्णांकo VF क्रम SRIOV support.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_cdev_release_port(काष्ठा dfl_fpga_cdev *cdev, पूर्णांक port_id)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	काष्ठा platक्रमm_device *port_pdev;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&cdev->lock);
	port_pdev = __dfl_fpga_cdev_find_port(cdev, &port_id,
					      dfl_fpga_check_port_id);
	अगर (!port_pdev)
		जाओ unlock_निकास;

	अगर (!device_is_रेजिस्टरed(&port_pdev->dev)) अणु
		ret = -EBUSY;
		जाओ put_dev_निकास;
	पूर्ण

	pdata = dev_get_platdata(&port_pdev->dev);

	mutex_lock(&pdata->lock);
	ret = dfl_feature_dev_use_begin(pdata, true);
	mutex_unlock(&pdata->lock);
	अगर (ret)
		जाओ put_dev_निकास;

	platक्रमm_device_del(port_pdev);
	cdev->released_port_num++;
put_dev_निकास:
	put_device(&port_pdev->dev);
unlock_निकास:
	mutex_unlock(&cdev->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_cdev_release_port);

/**
 * dfl_fpga_cdev_assign_port - assign a port platक्रमm device back
 *
 * @cdev: parent container device.
 * @port_id: id of the port platक्रमm device.
 *
 * This function allows user to assign a port platक्रमm device back. This is
 * a mandatory step after disable SRIOV support.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_cdev_assign_port(काष्ठा dfl_fpga_cdev *cdev, पूर्णांक port_id)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	काष्ठा platक्रमm_device *port_pdev;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&cdev->lock);
	port_pdev = __dfl_fpga_cdev_find_port(cdev, &port_id,
					      dfl_fpga_check_port_id);
	अगर (!port_pdev)
		जाओ unlock_निकास;

	अगर (device_is_रेजिस्टरed(&port_pdev->dev)) अणु
		ret = -EBUSY;
		जाओ put_dev_निकास;
	पूर्ण

	ret = platक्रमm_device_add(port_pdev);
	अगर (ret)
		जाओ put_dev_निकास;

	pdata = dev_get_platdata(&port_pdev->dev);

	mutex_lock(&pdata->lock);
	dfl_feature_dev_use_end(pdata);
	mutex_unlock(&pdata->lock);

	cdev->released_port_num--;
put_dev_निकास:
	put_device(&port_pdev->dev);
unlock_निकास:
	mutex_unlock(&cdev->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_cdev_assign_port);

अटल व्योम config_port_access_mode(काष्ठा device *fme_dev, पूर्णांक port_id,
				    bool is_vf)
अणु
	व्योम __iomem *base;
	u64 v;

	base = dfl_get_feature_ioaddr_by_id(fme_dev, FME_FEATURE_ID_HEADER);

	v = पढ़ोq(base + FME_HDR_PORT_OFST(port_id));

	v &= ~FME_PORT_OFST_ACC_CTRL;
	v |= FIELD_PREP(FME_PORT_OFST_ACC_CTRL,
			is_vf ? FME_PORT_OFST_ACC_VF : FME_PORT_OFST_ACC_PF);

	ग_लिखोq(v, base + FME_HDR_PORT_OFST(port_id));
पूर्ण

#घोषणा config_port_vf_mode(dev, id) config_port_access_mode(dev, id, true)
#घोषणा config_port_pf_mode(dev, id) config_port_access_mode(dev, id, false)

/**
 * dfl_fpga_cdev_config_ports_pf - configure ports to PF access mode
 *
 * @cdev: parent container device.
 *
 * This function is needed in sriov configuration routine. It could be used to
 * configure the all released ports from VF access mode to PF.
 */
व्योम dfl_fpga_cdev_config_ports_pf(काष्ठा dfl_fpga_cdev *cdev)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata;

	mutex_lock(&cdev->lock);
	list_क्रम_each_entry(pdata, &cdev->port_dev_list, node) अणु
		अगर (device_is_रेजिस्टरed(&pdata->dev->dev))
			जारी;

		config_port_pf_mode(cdev->fme_dev, pdata->id);
	पूर्ण
	mutex_unlock(&cdev->lock);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_cdev_config_ports_pf);

/**
 * dfl_fpga_cdev_config_ports_vf - configure ports to VF access mode
 *
 * @cdev: parent container device.
 * @num_vfs: VF device number.
 *
 * This function is needed in sriov configuration routine. It could be used to
 * configure the released ports from PF access mode to VF.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_cdev_config_ports_vf(काष्ठा dfl_fpga_cdev *cdev, पूर्णांक num_vfs)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata;
	पूर्णांक ret = 0;

	mutex_lock(&cdev->lock);
	/*
	 * can't turn multiple ports पूर्णांकo 1 VF device, only 1 port क्रम 1 VF
	 * device, so अगर released port number करोesn't match VF device number,
	 * then reject the request with -EINVAL error code.
	 */
	अगर (cdev->released_port_num != num_vfs) अणु
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	list_क्रम_each_entry(pdata, &cdev->port_dev_list, node) अणु
		अगर (device_is_रेजिस्टरed(&pdata->dev->dev))
			जारी;

		config_port_vf_mode(cdev->fme_dev, pdata->id);
	पूर्ण
करोne:
	mutex_unlock(&cdev->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_cdev_config_ports_vf);

अटल irqवापस_t dfl_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा eventfd_ctx *trigger = arg;

	eventfd_संकेत(trigger, 1);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक करो_set_irq_trigger(काष्ठा dfl_feature *feature, अचिन्हित पूर्णांक idx,
			      पूर्णांक fd)
अणु
	काष्ठा platक्रमm_device *pdev = feature->dev;
	काष्ठा eventfd_ctx *trigger;
	पूर्णांक irq, ret;

	irq = feature->irq_ctx[idx].irq;

	अगर (feature->irq_ctx[idx].trigger) अणु
		मुक्त_irq(irq, feature->irq_ctx[idx].trigger);
		kमुक्त(feature->irq_ctx[idx].name);
		eventfd_ctx_put(feature->irq_ctx[idx].trigger);
		feature->irq_ctx[idx].trigger = शून्य;
	पूर्ण

	अगर (fd < 0)
		वापस 0;

	feature->irq_ctx[idx].name =
		kaप्र_लिखो(GFP_KERNEL, "fpga-irq[%u](%s-%x)", idx,
			  dev_name(&pdev->dev), feature->id);
	अगर (!feature->irq_ctx[idx].name)
		वापस -ENOMEM;

	trigger = eventfd_ctx_fdget(fd);
	अगर (IS_ERR(trigger)) अणु
		ret = PTR_ERR(trigger);
		जाओ मुक्त_name;
	पूर्ण

	ret = request_irq(irq, dfl_irq_handler, 0,
			  feature->irq_ctx[idx].name, trigger);
	अगर (!ret) अणु
		feature->irq_ctx[idx].trigger = trigger;
		वापस ret;
	पूर्ण

	eventfd_ctx_put(trigger);
मुक्त_name:
	kमुक्त(feature->irq_ctx[idx].name);

	वापस ret;
पूर्ण

/**
 * dfl_fpga_set_irq_triggers - set eventfd triggers क्रम dfl feature पूर्णांकerrupts
 *
 * @feature: dfl sub feature.
 * @start: start of irq index in this dfl sub feature.
 * @count: number of irqs.
 * @fds: eventfds to bind with irqs. unbind related irq अगर fds[n] is negative.
 *	 unbind "count" specअगरied number of irqs अगर fds ptr is शून्य.
 *
 * Bind given eventfds with irqs in this dfl sub feature. Unbind related irq अगर
 * fds[n] is negative. Unbind "count" specअगरied number of irqs अगर fds ptr is
 * शून्य.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक dfl_fpga_set_irq_triggers(काष्ठा dfl_feature *feature, अचिन्हित पूर्णांक start,
			      अचिन्हित पूर्णांक count, पूर्णांक32_t *fds)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	/* overflow */
	अगर (unlikely(start + count < start))
		वापस -EINVAL;

	/* exceeds nr_irqs */
	अगर (start + count > feature->nr_irqs)
		वापस -EINVAL;

	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक fd = fds ? fds[i] : -1;

		ret = करो_set_irq_trigger(feature, start + i, fd);
		अगर (ret) अणु
			जबतक (i--)
				करो_set_irq_trigger(feature, start + i, -1);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_fpga_set_irq_triggers);

/**
 * dfl_feature_ioctl_get_num_irqs - dfl feature _GET_IRQ_NUM ioctl पूर्णांकerface.
 * @pdev: the feature device which has the sub feature
 * @feature: the dfl sub feature
 * @arg: ioctl argument
 *
 * Return: 0 on success, negative error code otherwise.
 */
दीर्घ dfl_feature_ioctl_get_num_irqs(काष्ठा platक्रमm_device *pdev,
				    काष्ठा dfl_feature *feature,
				    अचिन्हित दीर्घ arg)
अणु
	वापस put_user(feature->nr_irqs, (__u32 __user *)arg);
पूर्ण
EXPORT_SYMBOL_GPL(dfl_feature_ioctl_get_num_irqs);

/**
 * dfl_feature_ioctl_set_irq - dfl feature _SET_IRQ ioctl पूर्णांकerface.
 * @pdev: the feature device which has the sub feature
 * @feature: the dfl sub feature
 * @arg: ioctl argument
 *
 * Return: 0 on success, negative error code otherwise.
 */
दीर्घ dfl_feature_ioctl_set_irq(काष्ठा platक्रमm_device *pdev,
			       काष्ठा dfl_feature *feature,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा dfl_feature_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dfl_fpga_irq_set hdr;
	s32 *fds;
	दीर्घ ret;

	अगर (!feature->nr_irqs)
		वापस -ENOENT;

	अगर (copy_from_user(&hdr, (व्योम __user *)arg, माप(hdr)))
		वापस -EFAULT;

	अगर (!hdr.count || (hdr.start + hdr.count > feature->nr_irqs) ||
	    (hdr.start + hdr.count < hdr.start))
		वापस -EINVAL;

	fds = memdup_user((व्योम __user *)(arg + माप(hdr)),
			  hdr.count * माप(s32));
	अगर (IS_ERR(fds))
		वापस PTR_ERR(fds);

	mutex_lock(&pdata->lock);
	ret = dfl_fpga_set_irq_triggers(feature, hdr.start, hdr.count, fds);
	mutex_unlock(&pdata->lock);

	kमुक्त(fds);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dfl_feature_ioctl_set_irq);

अटल व्योम __निकास dfl_fpga_निकास(व्योम)
अणु
	dfl_अक्षरdev_uinit();
	dfl_ids_destroy();
	bus_unरेजिस्टर(&dfl_bus_type);
पूर्ण

module_init(dfl_fpga_init);
module_निकास(dfl_fpga_निकास);

MODULE_DESCRIPTION("FPGA Device Feature List (DFL) Support");
MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
