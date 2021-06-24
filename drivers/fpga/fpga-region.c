<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Region - Support क्रम FPGA programming under Linux
 *
 *  Copyright (C) 2013-2016 Altera Corporation
 *  Copyright (C) 2017 Intel Corporation
 */
#समावेश <linux/fpga/fpga-bridge.h>
#समावेश <linux/fpga/fpga-mgr.h>
#समावेश <linux/fpga/fpga-region.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

अटल DEFINE_IDA(fpga_region_ida);
अटल काष्ठा class *fpga_region_class;

काष्ठा fpga_region *fpga_region_class_find(
	काष्ठा device *start, स्थिर व्योम *data,
	पूर्णांक (*match)(काष्ठा device *, स्थिर व्योम *))
अणु
	काष्ठा device *dev;

	dev = class_find_device(fpga_region_class, start, data, match);
	अगर (!dev)
		वापस शून्य;

	वापस to_fpga_region(dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_region_class_find);

/**
 * fpga_region_get - get an exclusive reference to a fpga region
 * @region: FPGA Region काष्ठा
 *
 * Caller should call fpga_region_put() when करोne with region.
 *
 * Return fpga_region काष्ठा अगर successful.
 * Return -EBUSY अगर someone alपढ़ोy has a reference to the region.
 * Return -ENODEV अगर @np is not a FPGA Region.
 */
अटल काष्ठा fpga_region *fpga_region_get(काष्ठा fpga_region *region)
अणु
	काष्ठा device *dev = &region->dev;

	अगर (!mutex_trylock(&region->mutex)) अणु
		dev_dbg(dev, "%s: FPGA Region already in use\n", __func__);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	get_device(dev);
	अगर (!try_module_get(dev->parent->driver->owner)) अणु
		put_device(dev);
		mutex_unlock(&region->mutex);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	dev_dbg(dev, "get\n");

	वापस region;
पूर्ण

/**
 * fpga_region_put - release a reference to a region
 *
 * @region: FPGA region
 */
अटल व्योम fpga_region_put(काष्ठा fpga_region *region)
अणु
	काष्ठा device *dev = &region->dev;

	dev_dbg(dev, "put\n");

	module_put(dev->parent->driver->owner);
	put_device(dev);
	mutex_unlock(&region->mutex);
पूर्ण

/**
 * fpga_region_program_fpga - program FPGA
 *
 * @region: FPGA region
 *
 * Program an FPGA using fpga image info (region->info).
 * If the region has a get_bridges function, the exclusive reference क्रम the
 * bridges will be held अगर programming succeeds.  This is पूर्णांकended to prevent
 * reprogramming the region until the caller considers it safe to करो so.
 * The caller will need to call fpga_bridges_put() beक्रमe attempting to
 * reprogram the region.
 *
 * Return 0 क्रम success or negative error code.
 */
पूर्णांक fpga_region_program_fpga(काष्ठा fpga_region *region)
अणु
	काष्ठा device *dev = &region->dev;
	काष्ठा fpga_image_info *info = region->info;
	पूर्णांक ret;

	region = fpga_region_get(region);
	अगर (IS_ERR(region)) अणु
		dev_err(dev, "failed to get FPGA region\n");
		वापस PTR_ERR(region);
	पूर्ण

	ret = fpga_mgr_lock(region->mgr);
	अगर (ret) अणु
		dev_err(dev, "FPGA manager is busy\n");
		जाओ err_put_region;
	पूर्ण

	/*
	 * In some हालs, we alपढ़ोy have a list of bridges in the
	 * fpga region काष्ठा.  Or we करोn't have any bridges.
	 */
	अगर (region->get_bridges) अणु
		ret = region->get_bridges(region);
		अगर (ret) अणु
			dev_err(dev, "failed to get fpga region bridges\n");
			जाओ err_unlock_mgr;
		पूर्ण
	पूर्ण

	ret = fpga_bridges_disable(&region->bridge_list);
	अगर (ret) अणु
		dev_err(dev, "failed to disable bridges\n");
		जाओ err_put_br;
	पूर्ण

	ret = fpga_mgr_load(region->mgr, info);
	अगर (ret) अणु
		dev_err(dev, "failed to load FPGA image\n");
		जाओ err_put_br;
	पूर्ण

	ret = fpga_bridges_enable(&region->bridge_list);
	अगर (ret) अणु
		dev_err(dev, "failed to enable region bridges\n");
		जाओ err_put_br;
	पूर्ण

	fpga_mgr_unlock(region->mgr);
	fpga_region_put(region);

	वापस 0;

err_put_br:
	अगर (region->get_bridges)
		fpga_bridges_put(&region->bridge_list);
err_unlock_mgr:
	fpga_mgr_unlock(region->mgr);
err_put_region:
	fpga_region_put(region);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_region_program_fpga);

अटल sमाप_प्रकार compat_id_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fpga_region *region = to_fpga_region(dev);

	अगर (!region->compat_id)
		वापस -ENOENT;

	वापस प्र_लिखो(buf, "%016llx%016llx\n",
		       (अचिन्हित दीर्घ दीर्घ)region->compat_id->id_h,
		       (अचिन्हित दीर्घ दीर्घ)region->compat_id->id_l);
पूर्ण

अटल DEVICE_ATTR_RO(compat_id);

अटल काष्ठा attribute *fpga_region_attrs[] = अणु
	&dev_attr_compat_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(fpga_region);

/**
 * fpga_region_create - alloc and init a काष्ठा fpga_region
 * @dev: device parent
 * @mgr: manager that programs this region
 * @get_bridges: optional function to get bridges to a list
 *
 * The caller of this function is responsible क्रम मुक्तing the resulting region
 * काष्ठा with fpga_region_मुक्त().  Using devm_fpga_region_create() instead is
 * recommended.
 *
 * Return: काष्ठा fpga_region or शून्य
 */
काष्ठा fpga_region
*fpga_region_create(काष्ठा device *dev,
		    काष्ठा fpga_manager *mgr,
		    पूर्णांक (*get_bridges)(काष्ठा fpga_region *))
अणु
	काष्ठा fpga_region *region;
	पूर्णांक id, ret = 0;

	region = kzalloc(माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस शून्य;

	id = ida_simple_get(&fpga_region_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		जाओ err_मुक्त;

	region->mgr = mgr;
	region->get_bridges = get_bridges;
	mutex_init(&region->mutex);
	INIT_LIST_HEAD(&region->bridge_list);

	device_initialize(&region->dev);
	region->dev.class = fpga_region_class;
	region->dev.parent = dev;
	region->dev.of_node = dev->of_node;
	region->dev.id = id;

	ret = dev_set_name(&region->dev, "region%d", id);
	अगर (ret)
		जाओ err_हटाओ;

	वापस region;

err_हटाओ:
	ida_simple_हटाओ(&fpga_region_ida, id);
err_मुक्त:
	kमुक्त(region);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_region_create);

/**
 * fpga_region_मुक्त - मुक्त a FPGA region created by fpga_region_create()
 * @region: FPGA region
 */
व्योम fpga_region_मुक्त(काष्ठा fpga_region *region)
अणु
	ida_simple_हटाओ(&fpga_region_ida, region->dev.id);
	kमुक्त(region);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_region_मुक्त);

अटल व्योम devm_fpga_region_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा fpga_region *region = *(काष्ठा fpga_region **)res;

	fpga_region_मुक्त(region);
पूर्ण

/**
 * devm_fpga_region_create - create and initialize a managed FPGA region काष्ठा
 * @dev: device parent
 * @mgr: manager that programs this region
 * @get_bridges: optional function to get bridges to a list
 *
 * This function is पूर्णांकended क्रम use in a FPGA region driver's probe function.
 * After the region driver creates the region काष्ठा with
 * devm_fpga_region_create(), it should रेजिस्टर it with fpga_region_रेजिस्टर().
 * The region driver's हटाओ function should call fpga_region_unरेजिस्टर().
 * The region काष्ठा allocated with this function will be मुक्तd स्वतःmatically on
 * driver detach.  This includes the हाल of a probe function वापसing error
 * beक्रमe calling fpga_region_रेजिस्टर(), the काष्ठा will still get cleaned up.
 *
 * Return: काष्ठा fpga_region or शून्य
 */
काष्ठा fpga_region
*devm_fpga_region_create(काष्ठा device *dev,
			 काष्ठा fpga_manager *mgr,
			 पूर्णांक (*get_bridges)(काष्ठा fpga_region *))
अणु
	काष्ठा fpga_region **ptr, *region;

	ptr = devres_alloc(devm_fpga_region_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	region = fpga_region_create(dev, mgr, get_bridges);
	अगर (!region) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = region;
		devres_add(dev, ptr);
	पूर्ण

	वापस region;
पूर्ण
EXPORT_SYMBOL_GPL(devm_fpga_region_create);

/**
 * fpga_region_रेजिस्टर - रेजिस्टर a FPGA region
 * @region: FPGA region
 *
 * Return: 0 or -त्रुटि_सं
 */
पूर्णांक fpga_region_रेजिस्टर(काष्ठा fpga_region *region)
अणु
	वापस device_add(&region->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_region_रेजिस्टर);

/**
 * fpga_region_unरेजिस्टर - unरेजिस्टर a FPGA region
 * @region: FPGA region
 *
 * This function is पूर्णांकended क्रम use in a FPGA region driver's हटाओ function.
 */
व्योम fpga_region_unरेजिस्टर(काष्ठा fpga_region *region)
अणु
	device_unरेजिस्टर(&region->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_region_unरेजिस्टर);

अटल व्योम fpga_region_dev_release(काष्ठा device *dev)
अणु
पूर्ण

/**
 * fpga_region_init - init function क्रम fpga_region class
 * Creates the fpga_region class and रेजिस्टरs a reconfig notअगरier.
 */
अटल पूर्णांक __init fpga_region_init(व्योम)
अणु
	fpga_region_class = class_create(THIS_MODULE, "fpga_region");
	अगर (IS_ERR(fpga_region_class))
		वापस PTR_ERR(fpga_region_class);

	fpga_region_class->dev_groups = fpga_region_groups;
	fpga_region_class->dev_release = fpga_region_dev_release;

	वापस 0;
पूर्ण

अटल व्योम __निकास fpga_region_निकास(व्योम)
अणु
	class_destroy(fpga_region_class);
	ida_destroy(&fpga_region_ida);
पूर्ण

subsys_initcall(fpga_region_init);
module_निकास(fpga_region_निकास);

MODULE_DESCRIPTION("FPGA Region");
MODULE_AUTHOR("Alan Tull <atull@kernel.org>");
MODULE_LICENSE("GPL v2");
