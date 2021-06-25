<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/libnvdimm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/async.h>
#समावेश <linux/genhd.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/nd.h>
#समावेश "nd-core.h"
#समावेश "nd.h"
#समावेश "pfn.h"

पूर्णांक nvdimm_major;
अटल पूर्णांक nvdimm_bus_major;
काष्ठा class *nd_class;
अटल DEFINE_IDA(nd_ida);

अटल पूर्णांक to_nd_device_type(काष्ठा device *dev)
अणु
	अगर (is_nvdimm(dev))
		वापस ND_DEVICE_DIMM;
	अन्यथा अगर (is_memory(dev))
		वापस ND_DEVICE_REGION_PMEM;
	अन्यथा अगर (is_nd_blk(dev))
		वापस ND_DEVICE_REGION_BLK;
	अन्यथा अगर (is_nd_dax(dev))
		वापस ND_DEVICE_DAX_PMEM;
	अन्यथा अगर (is_nd_region(dev->parent))
		वापस nd_region_to_nstype(to_nd_region(dev->parent));

	वापस 0;
पूर्ण

अटल पूर्णांक nvdimm_bus_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	वापस add_uevent_var(env, "MODALIAS=" ND_DEVICE_MODALIAS_FMT,
			to_nd_device_type(dev));
पूर्ण

अटल काष्ठा module *to_bus_provider(काष्ठा device *dev)
अणु
	/* pin bus providers जबतक regions are enabled */
	अगर (is_nd_region(dev)) अणु
		काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

		वापस nvdimm_bus->nd_desc->module;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम nvdimm_bus_probe_start(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	nvdimm_bus_lock(&nvdimm_bus->dev);
	nvdimm_bus->probe_active++;
	nvdimm_bus_unlock(&nvdimm_bus->dev);
पूर्ण

अटल व्योम nvdimm_bus_probe_end(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	nvdimm_bus_lock(&nvdimm_bus->dev);
	अगर (--nvdimm_bus->probe_active == 0)
		wake_up(&nvdimm_bus->रुको);
	nvdimm_bus_unlock(&nvdimm_bus->dev);
पूर्ण

अटल पूर्णांक nvdimm_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा nd_device_driver *nd_drv = to_nd_device_driver(dev->driver);
	काष्ठा module *provider = to_bus_provider(dev);
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	पूर्णांक rc;

	अगर (!try_module_get(provider))
		वापस -ENXIO;

	dev_dbg(&nvdimm_bus->dev, "START: %s.probe(%s)\n",
			dev->driver->name, dev_name(dev));

	nvdimm_bus_probe_start(nvdimm_bus);
	debug_nvdimm_lock(dev);
	rc = nd_drv->probe(dev);
	debug_nvdimm_unlock(dev);

	अगर ((rc == 0 || rc == -EOPNOTSUPP) &&
			dev->parent && is_nd_region(dev->parent))
		nd_region_advance_seeds(to_nd_region(dev->parent), dev);
	nvdimm_bus_probe_end(nvdimm_bus);

	dev_dbg(&nvdimm_bus->dev, "END: %s.probe(%s) = %d\n", dev->driver->name,
			dev_name(dev), rc);

	अगर (rc != 0)
		module_put(provider);
	वापस rc;
पूर्ण

अटल पूर्णांक nvdimm_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा nd_device_driver *nd_drv = to_nd_device_driver(dev->driver);
	काष्ठा module *provider = to_bus_provider(dev);
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	अगर (nd_drv->हटाओ) अणु
		debug_nvdimm_lock(dev);
		nd_drv->हटाओ(dev);
		debug_nvdimm_unlock(dev);
	पूर्ण

	dev_dbg(&nvdimm_bus->dev, "%s.remove(%s)\n", dev->driver->name,
			dev_name(dev));
	module_put(provider);
	वापस 0;
पूर्ण

अटल व्योम nvdimm_bus_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा nd_device_driver *nd_drv = शून्य;

	अगर (dev->driver)
		nd_drv = to_nd_device_driver(dev->driver);

	अगर (nd_drv && nd_drv->shutकरोwn) अणु
		nd_drv->shutकरोwn(dev);
		dev_dbg(&nvdimm_bus->dev, "%s.shutdown(%s)\n",
				dev->driver->name, dev_name(dev));
	पूर्ण
पूर्ण

व्योम nd_device_notअगरy(काष्ठा device *dev, क्रमागत nvdimm_event event)
अणु
	nd_device_lock(dev);
	अगर (dev->driver) अणु
		काष्ठा nd_device_driver *nd_drv;

		nd_drv = to_nd_device_driver(dev->driver);
		अगर (nd_drv->notअगरy)
			nd_drv->notअगरy(dev, event);
	पूर्ण
	nd_device_unlock(dev);
पूर्ण
EXPORT_SYMBOL(nd_device_notअगरy);

व्योम nvdimm_region_notअगरy(काष्ठा nd_region *nd_region, क्रमागत nvdimm_event event)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);

	अगर (!nvdimm_bus)
		वापस;

	/* caller is responsible क्रम holding a reference on the device */
	nd_device_notअगरy(&nd_region->dev, event);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_region_notअगरy);

काष्ठा clear_badblocks_context अणु
	resource_माप_प्रकार phys, cleared;
पूर्ण;

अटल पूर्णांक nvdimm_clear_badblocks_region(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा clear_badblocks_context *ctx = data;
	काष्ठा nd_region *nd_region;
	resource_माप_प्रकार ndr_end;
	sector_t sector;

	/* make sure device is a region */
	अगर (!is_memory(dev))
		वापस 0;

	nd_region = to_nd_region(dev);
	ndr_end = nd_region->ndr_start + nd_region->ndr_size - 1;

	/* make sure we are in the region */
	अगर (ctx->phys < nd_region->ndr_start
			|| (ctx->phys + ctx->cleared) > ndr_end)
		वापस 0;

	sector = (ctx->phys - nd_region->ndr_start) / 512;
	badblocks_clear(&nd_region->bb, sector, ctx->cleared / 512);

	अगर (nd_region->bb_state)
		sysfs_notअगरy_dirent(nd_region->bb_state);

	वापस 0;
पूर्ण

अटल व्योम nvdimm_clear_badblocks_regions(काष्ठा nvdimm_bus *nvdimm_bus,
		phys_addr_t phys, u64 cleared)
अणु
	काष्ठा clear_badblocks_context ctx = अणु
		.phys = phys,
		.cleared = cleared,
	पूर्ण;

	device_क्रम_each_child(&nvdimm_bus->dev, &ctx,
			nvdimm_clear_badblocks_region);
पूर्ण

अटल व्योम nvdimm_account_cleared_poison(काष्ठा nvdimm_bus *nvdimm_bus,
		phys_addr_t phys, u64 cleared)
अणु
	अगर (cleared > 0)
		badrange_क्रमget(&nvdimm_bus->badrange, phys, cleared);

	अगर (cleared > 0 && cleared / 512)
		nvdimm_clear_badblocks_regions(nvdimm_bus, phys, cleared);
पूर्ण

दीर्घ nvdimm_clear_poison(काष्ठा device *dev, phys_addr_t phys,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	काष्ठा nvdimm_bus_descriptor *nd_desc;
	काष्ठा nd_cmd_clear_error clear_err;
	काष्ठा nd_cmd_ars_cap ars_cap;
	u32 clear_err_unit, mask;
	अचिन्हित पूर्णांक noio_flag;
	पूर्णांक cmd_rc, rc;

	अगर (!nvdimm_bus)
		वापस -ENXIO;

	nd_desc = nvdimm_bus->nd_desc;
	/*
	 * अगर ndctl करोes not exist, it's PMEM_LEGACY and
	 * we want to just pretend everything is handled.
	 */
	अगर (!nd_desc->ndctl)
		वापस len;

	स_रखो(&ars_cap, 0, माप(ars_cap));
	ars_cap.address = phys;
	ars_cap.length = len;
	noio_flag = meदो_स्मृति_noio_save();
	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_ARS_CAP, &ars_cap,
			माप(ars_cap), &cmd_rc);
	meदो_स्मृति_noio_restore(noio_flag);
	अगर (rc < 0)
		वापस rc;
	अगर (cmd_rc < 0)
		वापस cmd_rc;
	clear_err_unit = ars_cap.clear_err_unit;
	अगर (!clear_err_unit || !is_घातer_of_2(clear_err_unit))
		वापस -ENXIO;

	mask = clear_err_unit - 1;
	अगर ((phys | len) & mask)
		वापस -ENXIO;
	स_रखो(&clear_err, 0, माप(clear_err));
	clear_err.address = phys;
	clear_err.length = len;
	noio_flag = meदो_स्मृति_noio_save();
	rc = nd_desc->ndctl(nd_desc, शून्य, ND_CMD_CLEAR_ERROR, &clear_err,
			माप(clear_err), &cmd_rc);
	meदो_स्मृति_noio_restore(noio_flag);
	अगर (rc < 0)
		वापस rc;
	अगर (cmd_rc < 0)
		वापस cmd_rc;

	nvdimm_account_cleared_poison(nvdimm_bus, phys, clear_err.cleared);

	वापस clear_err.cleared;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_clear_poison);

अटल पूर्णांक nvdimm_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv);

अटल काष्ठा bus_type nvdimm_bus_type = अणु
	.name = "nd",
	.uevent = nvdimm_bus_uevent,
	.match = nvdimm_bus_match,
	.probe = nvdimm_bus_probe,
	.हटाओ = nvdimm_bus_हटाओ,
	.shutकरोwn = nvdimm_bus_shutकरोwn,
पूर्ण;

अटल व्योम nvdimm_bus_release(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus;

	nvdimm_bus = container_of(dev, काष्ठा nvdimm_bus, dev);
	ida_simple_हटाओ(&nd_ida, nvdimm_bus->id);
	kमुक्त(nvdimm_bus);
पूर्ण

अटल स्थिर काष्ठा device_type nvdimm_bus_dev_type = अणु
	.release = nvdimm_bus_release,
	.groups = nvdimm_bus_attribute_groups,
पूर्ण;

bool is_nvdimm_bus(काष्ठा device *dev)
अणु
	वापस dev->type == &nvdimm_bus_dev_type;
पूर्ण

काष्ठा nvdimm_bus *walk_to_nvdimm_bus(काष्ठा device *nd_dev)
अणु
	काष्ठा device *dev;

	क्रम (dev = nd_dev; dev; dev = dev->parent)
		अगर (is_nvdimm_bus(dev))
			अवरोध;
	dev_WARN_ONCE(nd_dev, !dev, "invalid dev, not on nd bus\n");
	अगर (dev)
		वापस to_nvdimm_bus(dev);
	वापस शून्य;
पूर्ण

काष्ठा nvdimm_bus *to_nvdimm_bus(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus;

	nvdimm_bus = container_of(dev, काष्ठा nvdimm_bus, dev);
	WARN_ON(!is_nvdimm_bus(dev));
	वापस nvdimm_bus;
पूर्ण
EXPORT_SYMBOL_GPL(to_nvdimm_bus);

काष्ठा nvdimm_bus *nvdimm_to_bus(काष्ठा nvdimm *nvdimm)
अणु
	वापस to_nvdimm_bus(nvdimm->dev.parent);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_to_bus);

काष्ठा nvdimm_bus *nvdimm_bus_रेजिस्टर(काष्ठा device *parent,
		काष्ठा nvdimm_bus_descriptor *nd_desc)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus;
	पूर्णांक rc;

	nvdimm_bus = kzalloc(माप(*nvdimm_bus), GFP_KERNEL);
	अगर (!nvdimm_bus)
		वापस शून्य;
	INIT_LIST_HEAD(&nvdimm_bus->list);
	INIT_LIST_HEAD(&nvdimm_bus->mapping_list);
	init_रुकोqueue_head(&nvdimm_bus->रुको);
	nvdimm_bus->id = ida_simple_get(&nd_ida, 0, 0, GFP_KERNEL);
	अगर (nvdimm_bus->id < 0) अणु
		kमुक्त(nvdimm_bus);
		वापस शून्य;
	पूर्ण
	mutex_init(&nvdimm_bus->reconfig_mutex);
	badrange_init(&nvdimm_bus->badrange);
	nvdimm_bus->nd_desc = nd_desc;
	nvdimm_bus->dev.parent = parent;
	nvdimm_bus->dev.type = &nvdimm_bus_dev_type;
	nvdimm_bus->dev.groups = nd_desc->attr_groups;
	nvdimm_bus->dev.bus = &nvdimm_bus_type;
	nvdimm_bus->dev.of_node = nd_desc->of_node;
	dev_set_name(&nvdimm_bus->dev, "ndbus%d", nvdimm_bus->id);
	rc = device_रेजिस्टर(&nvdimm_bus->dev);
	अगर (rc) अणु
		dev_dbg(&nvdimm_bus->dev, "registration failed: %d\n", rc);
		जाओ err;
	पूर्ण

	वापस nvdimm_bus;
 err:
	put_device(&nvdimm_bus->dev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_bus_रेजिस्टर);

व्योम nvdimm_bus_unरेजिस्टर(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	अगर (!nvdimm_bus)
		वापस;
	device_unरेजिस्टर(&nvdimm_bus->dev);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_bus_unरेजिस्टर);

अटल पूर्णांक child_unरेजिस्टर(काष्ठा device *dev, व्योम *data)
अणु
	/*
	 * the singular ndctl class device per bus needs to be
	 * "device_destroy"ed, so skip it here
	 *
	 * i.e. हटाओ classless children
	 */
	अगर (dev->class)
		वापस 0;

	अगर (is_nvdimm(dev)) अणु
		काष्ठा nvdimm *nvdimm = to_nvdimm(dev);
		bool dev_put = false;

		/* We are shutting करोwn. Make state frozen artअगरicially. */
		nvdimm_bus_lock(dev);
		set_bit(NVDIMM_SECURITY_FROZEN, &nvdimm->sec.flags);
		अगर (test_and_clear_bit(NDD_WORK_PENDING, &nvdimm->flags))
			dev_put = true;
		nvdimm_bus_unlock(dev);
		cancel_delayed_work_sync(&nvdimm->dwork);
		अगर (dev_put)
			put_device(dev);
	पूर्ण
	nd_device_unरेजिस्टर(dev, ND_SYNC);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_badrange_list(काष्ठा list_head *badrange_list)
अणु
	काष्ठा badrange_entry *bre, *next;

	list_क्रम_each_entry_safe(bre, next, badrange_list, list) अणु
		list_del(&bre->list);
		kमुक्त(bre);
	पूर्ण
	list_del_init(badrange_list);
पूर्ण

अटल व्योम nd_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);

	mutex_lock(&nvdimm_bus_list_mutex);
	list_del_init(&nvdimm_bus->list);
	mutex_unlock(&nvdimm_bus_list_mutex);

	रुको_event(nvdimm_bus->रुको,
			atomic_पढ़ो(&nvdimm_bus->ioctl_active) == 0);

	nd_synchronize();
	device_क्रम_each_child(&nvdimm_bus->dev, शून्य, child_unरेजिस्टर);

	spin_lock(&nvdimm_bus->badrange.lock);
	मुक्त_badrange_list(&nvdimm_bus->badrange.list);
	spin_unlock(&nvdimm_bus->badrange.lock);

	nvdimm_bus_destroy_ndctl(nvdimm_bus);
पूर्ण

अटल पूर्णांक nd_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	पूर्णांक rc;

	rc = nvdimm_bus_create_ndctl(nvdimm_bus);
	अगर (rc)
		वापस rc;

	mutex_lock(&nvdimm_bus_list_mutex);
	list_add_tail(&nvdimm_bus->list, &nvdimm_bus_list);
	mutex_unlock(&nvdimm_bus_list_mutex);

	/* enable bus provider attributes to look up their local context */
	dev_set_drvdata(dev, nvdimm_bus->nd_desc);

	वापस 0;
पूर्ण

अटल काष्ठा nd_device_driver nd_bus_driver = अणु
	.probe = nd_bus_probe,
	.हटाओ = nd_bus_हटाओ,
	.drv = अणु
		.name = "nd_bus",
		.suppress_bind_attrs = true,
		.bus = &nvdimm_bus_type,
		.owner = THIS_MODULE,
		.mod_name = KBUILD_MODNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक nvdimm_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा nd_device_driver *nd_drv = to_nd_device_driver(drv);

	अगर (is_nvdimm_bus(dev) && nd_drv == &nd_bus_driver)
		वापस true;

	वापस !!test_bit(to_nd_device_type(dev), &nd_drv->type);
पूर्ण

अटल ASYNC_DOMAIN_EXCLUSIVE(nd_async_करोमुख्य);

व्योम nd_synchronize(व्योम)
अणु
	async_synchronize_full_करोमुख्य(&nd_async_करोमुख्य);
पूर्ण
EXPORT_SYMBOL_GPL(nd_synchronize);

अटल व्योम nd_async_device_रेजिस्टर(व्योम *d, async_cookie_t cookie)
अणु
	काष्ठा device *dev = d;

	अगर (device_add(dev) != 0) अणु
		dev_err(dev, "%s: failed\n", __func__);
		put_device(dev);
	पूर्ण
	put_device(dev);
	अगर (dev->parent)
		put_device(dev->parent);
पूर्ण

अटल व्योम nd_async_device_unरेजिस्टर(व्योम *d, async_cookie_t cookie)
अणु
	काष्ठा device *dev = d;

	/* flush bus operations beक्रमe delete */
	nvdimm_bus_lock(dev);
	nvdimm_bus_unlock(dev);

	device_unरेजिस्टर(dev);
	put_device(dev);
पूर्ण

व्योम __nd_device_रेजिस्टर(काष्ठा device *dev)
अणु
	अगर (!dev)
		वापस;

	/*
	 * Ensure that region devices always have their NUMA node set as
	 * early as possible. This way we are able to make certain that
	 * any memory associated with the creation and the creation
	 * itself of the region is associated with the correct node.
	 */
	अगर (is_nd_region(dev))
		set_dev_node(dev, to_nd_region(dev)->numa_node);

	dev->bus = &nvdimm_bus_type;
	अगर (dev->parent) अणु
		get_device(dev->parent);
		अगर (dev_to_node(dev) == NUMA_NO_NODE)
			set_dev_node(dev, dev_to_node(dev->parent));
	पूर्ण
	get_device(dev);

	async_schedule_dev_करोमुख्य(nd_async_device_रेजिस्टर, dev,
				  &nd_async_करोमुख्य);
पूर्ण

व्योम nd_device_रेजिस्टर(काष्ठा device *dev)
अणु
	device_initialize(dev);
	__nd_device_रेजिस्टर(dev);
पूर्ण
EXPORT_SYMBOL(nd_device_रेजिस्टर);

व्योम nd_device_unरेजिस्टर(काष्ठा device *dev, क्रमागत nd_async_mode mode)
अणु
	bool समाप्तed;

	चयन (mode) अणु
	हाल ND_ASYNC:
		/*
		 * In the async हाल this is being triggered with the
		 * device lock held and the unregistration work needs to
		 * be moved out of line अगरf this is thपढ़ो has won the
		 * race to schedule the deletion.
		 */
		अगर (!समाप्त_device(dev))
			वापस;

		get_device(dev);
		async_schedule_करोमुख्य(nd_async_device_unरेजिस्टर, dev,
				&nd_async_करोमुख्य);
		अवरोध;
	हाल ND_SYNC:
		/*
		 * In the sync हाल the device is being unरेजिस्टरed due
		 * to a state change of the parent. Claim the समाप्त state
		 * to synchronize against other unregistration requests,
		 * or otherwise let the async path handle it अगर the
		 * unregistration was alपढ़ोy queued.
		 */
		nd_device_lock(dev);
		समाप्तed = समाप्त_device(dev);
		nd_device_unlock(dev);

		अगर (!समाप्तed)
			वापस;

		nd_synchronize();
		device_unरेजिस्टर(dev);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nd_device_unरेजिस्टर);

/**
 * __nd_driver_रेजिस्टर() - रेजिस्टर a region or a namespace driver
 * @nd_drv: driver to रेजिस्टर
 * @owner: स्वतःmatically set by nd_driver_रेजिस्टर() macro
 * @mod_name: स्वतःmatically set by nd_driver_रेजिस्टर() macro
 */
पूर्णांक __nd_driver_रेजिस्टर(काष्ठा nd_device_driver *nd_drv, काष्ठा module *owner,
		स्थिर अक्षर *mod_name)
अणु
	काष्ठा device_driver *drv = &nd_drv->drv;

	अगर (!nd_drv->type) अणु
		pr_debug("driver type bitmask not set (%ps)\n",
				__builtin_वापस_address(0));
		वापस -EINVAL;
	पूर्ण

	अगर (!nd_drv->probe) अणु
		pr_debug("%s ->probe() must be specified\n", mod_name);
		वापस -EINVAL;
	पूर्ण

	drv->bus = &nvdimm_bus_type;
	drv->owner = owner;
	drv->mod_name = mod_name;

	वापस driver_रेजिस्टर(drv);
पूर्ण
EXPORT_SYMBOL(__nd_driver_रेजिस्टर);

व्योम nvdimm_check_and_set_ro(काष्ठा gendisk *disk)
अणु
	काष्ठा device *dev = disk_to_dev(disk)->parent;
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	पूर्णांक disk_ro = get_disk_ro(disk);

	/* catch the disk up with the region ro state */
	अगर (disk_ro == nd_region->ro)
		वापस;

	dev_info(dev, "%s read-%s, marking %s read-%s\n",
		 dev_name(&nd_region->dev), nd_region->ro ? "only" : "write",
		 disk->disk_name, nd_region->ro ? "only" : "write");
	set_disk_ro(disk, nd_region->ro);
पूर्ण
EXPORT_SYMBOL(nvdimm_check_and_set_ro);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, ND_DEVICE_MODALIAS_FMT "\n",
			to_nd_device_type(dev));
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार devtype_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", dev->type->name);
पूर्ण
अटल DEVICE_ATTR_RO(devtype);

अटल काष्ठा attribute *nd_device_attributes[] = अणु
	&dev_attr_modalias.attr,
	&dev_attr_devtype.attr,
	शून्य,
पूर्ण;

/*
 * nd_device_attribute_group - generic attributes क्रम all devices on an nd bus
 */
स्थिर काष्ठा attribute_group nd_device_attribute_group = अणु
	.attrs = nd_device_attributes,
पूर्ण;

अटल sमाप_प्रकार numa_node_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", dev_to_node(dev));
पूर्ण
अटल DEVICE_ATTR_RO(numa_node);

अटल पूर्णांक nvdimm_dev_to_target_node(काष्ठा device *dev)
अणु
	काष्ठा device *parent = dev->parent;
	काष्ठा nd_region *nd_region = शून्य;

	अगर (is_nd_region(dev))
		nd_region = to_nd_region(dev);
	अन्यथा अगर (parent && is_nd_region(parent))
		nd_region = to_nd_region(parent);

	अगर (!nd_region)
		वापस NUMA_NO_NODE;
	वापस nd_region->target_node;
पूर्ण

अटल sमाप_प्रकार target_node_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", nvdimm_dev_to_target_node(dev));
पूर्ण
अटल DEVICE_ATTR_RO(target_node);

अटल काष्ठा attribute *nd_numa_attributes[] = अणु
	&dev_attr_numa_node.attr,
	&dev_attr_target_node.attr,
	शून्य,
पूर्ण;

अटल umode_t nd_numa_attr_visible(काष्ठा kobject *kobj, काष्ठा attribute *a,
		पूर्णांक n)
अणु
	काष्ठा device *dev = container_of(kobj, typeof(*dev), kobj);

	अगर (!IS_ENABLED(CONFIG_NUMA))
		वापस 0;

	अगर (a == &dev_attr_target_node.attr &&
			nvdimm_dev_to_target_node(dev) == NUMA_NO_NODE)
		वापस 0;

	वापस a->mode;
पूर्ण

/*
 * nd_numa_attribute_group - NUMA attributes क्रम all devices on an nd bus
 */
स्थिर काष्ठा attribute_group nd_numa_attribute_group = अणु
	.attrs = nd_numa_attributes,
	.is_visible = nd_numa_attr_visible,
पूर्ण;

पूर्णांक nvdimm_bus_create_ndctl(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	dev_t devt = MKDEV(nvdimm_bus_major, nvdimm_bus->id);
	काष्ठा device *dev;

	dev = device_create(nd_class, &nvdimm_bus->dev, devt, nvdimm_bus,
			"ndctl%d", nvdimm_bus->id);

	अगर (IS_ERR(dev))
		dev_dbg(&nvdimm_bus->dev, "failed to register ndctl%d: %ld\n",
				nvdimm_bus->id, PTR_ERR(dev));
	वापस PTR_ERR_OR_ZERO(dev);
पूर्ण

व्योम nvdimm_bus_destroy_ndctl(काष्ठा nvdimm_bus *nvdimm_bus)
अणु
	device_destroy(nd_class, MKDEV(nvdimm_bus_major, nvdimm_bus->id));
पूर्ण

अटल स्थिर काष्ठा nd_cmd_desc __nd_cmd_dimm_descs[] = अणु
	[ND_CMD_IMPLEMENTED] = अणु पूर्ण,
	[ND_CMD_SMART] = अणु
		.out_num = 2,
		.out_sizes = अणु 4, 128, पूर्ण,
	पूर्ण,
	[ND_CMD_SMART_THRESHOLD] = अणु
		.out_num = 2,
		.out_sizes = अणु 4, 8, पूर्ण,
	पूर्ण,
	[ND_CMD_DIMM_FLAGS] = अणु
		.out_num = 2,
		.out_sizes = अणु 4, 4 पूर्ण,
	पूर्ण,
	[ND_CMD_GET_CONFIG_SIZE] = अणु
		.out_num = 3,
		.out_sizes = अणु 4, 4, 4, पूर्ण,
	पूर्ण,
	[ND_CMD_GET_CONFIG_DATA] = अणु
		.in_num = 2,
		.in_sizes = अणु 4, 4, पूर्ण,
		.out_num = 2,
		.out_sizes = अणु 4, अच_पूर्णांक_उच्च, पूर्ण,
	पूर्ण,
	[ND_CMD_SET_CONFIG_DATA] = अणु
		.in_num = 3,
		.in_sizes = अणु 4, 4, अच_पूर्णांक_उच्च, पूर्ण,
		.out_num = 1,
		.out_sizes = अणु 4, पूर्ण,
	पूर्ण,
	[ND_CMD_VENDOR] = अणु
		.in_num = 3,
		.in_sizes = अणु 4, 4, अच_पूर्णांक_उच्च, पूर्ण,
		.out_num = 3,
		.out_sizes = अणु 4, 4, अच_पूर्णांक_उच्च, पूर्ण,
	पूर्ण,
	[ND_CMD_CALL] = अणु
		.in_num = 2,
		.in_sizes = अणु माप(काष्ठा nd_cmd_pkg), अच_पूर्णांक_उच्च, पूर्ण,
		.out_num = 1,
		.out_sizes = अणु अच_पूर्णांक_उच्च, पूर्ण,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा nd_cmd_desc *nd_cmd_dimm_desc(पूर्णांक cmd)
अणु
	अगर (cmd < ARRAY_SIZE(__nd_cmd_dimm_descs))
		वापस &__nd_cmd_dimm_descs[cmd];
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nd_cmd_dimm_desc);

अटल स्थिर काष्ठा nd_cmd_desc __nd_cmd_bus_descs[] = अणु
	[ND_CMD_IMPLEMENTED] = अणु पूर्ण,
	[ND_CMD_ARS_CAP] = अणु
		.in_num = 2,
		.in_sizes = अणु 8, 8, पूर्ण,
		.out_num = 4,
		.out_sizes = अणु 4, 4, 4, 4, पूर्ण,
	पूर्ण,
	[ND_CMD_ARS_START] = अणु
		.in_num = 5,
		.in_sizes = अणु 8, 8, 2, 1, 5, पूर्ण,
		.out_num = 2,
		.out_sizes = अणु 4, 4, पूर्ण,
	पूर्ण,
	[ND_CMD_ARS_STATUS] = अणु
		.out_num = 3,
		.out_sizes = अणु 4, 4, अच_पूर्णांक_उच्च, पूर्ण,
	पूर्ण,
	[ND_CMD_CLEAR_ERROR] = अणु
		.in_num = 2,
		.in_sizes = अणु 8, 8, पूर्ण,
		.out_num = 3,
		.out_sizes = अणु 4, 4, 8, पूर्ण,
	पूर्ण,
	[ND_CMD_CALL] = अणु
		.in_num = 2,
		.in_sizes = अणु माप(काष्ठा nd_cmd_pkg), अच_पूर्णांक_उच्च, पूर्ण,
		.out_num = 1,
		.out_sizes = अणु अच_पूर्णांक_उच्च, पूर्ण,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा nd_cmd_desc *nd_cmd_bus_desc(पूर्णांक cmd)
अणु
	अगर (cmd < ARRAY_SIZE(__nd_cmd_bus_descs))
		वापस &__nd_cmd_bus_descs[cmd];
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nd_cmd_bus_desc);

u32 nd_cmd_in_size(काष्ठा nvdimm *nvdimm, पूर्णांक cmd,
		स्थिर काष्ठा nd_cmd_desc *desc, पूर्णांक idx, व्योम *buf)
अणु
	अगर (idx >= desc->in_num)
		वापस अच_पूर्णांक_उच्च;

	अगर (desc->in_sizes[idx] < अच_पूर्णांक_उच्च)
		वापस desc->in_sizes[idx];

	अगर (nvdimm && cmd == ND_CMD_SET_CONFIG_DATA && idx == 2) अणु
		काष्ठा nd_cmd_set_config_hdr *hdr = buf;

		वापस hdr->in_length;
	पूर्ण अन्यथा अगर (nvdimm && cmd == ND_CMD_VENDOR && idx == 2) अणु
		काष्ठा nd_cmd_venकरोr_hdr *hdr = buf;

		वापस hdr->in_length;
	पूर्ण अन्यथा अगर (cmd == ND_CMD_CALL) अणु
		काष्ठा nd_cmd_pkg *pkg = buf;

		वापस pkg->nd_size_in;
	पूर्ण

	वापस अच_पूर्णांक_उच्च;
पूर्ण
EXPORT_SYMBOL_GPL(nd_cmd_in_size);

u32 nd_cmd_out_size(काष्ठा nvdimm *nvdimm, पूर्णांक cmd,
		स्थिर काष्ठा nd_cmd_desc *desc, पूर्णांक idx, स्थिर u32 *in_field,
		स्थिर u32 *out_field, अचिन्हित दीर्घ reमुख्यder)
अणु
	अगर (idx >= desc->out_num)
		वापस अच_पूर्णांक_उच्च;

	अगर (desc->out_sizes[idx] < अच_पूर्णांक_उच्च)
		वापस desc->out_sizes[idx];

	अगर (nvdimm && cmd == ND_CMD_GET_CONFIG_DATA && idx == 1)
		वापस in_field[1];
	अन्यथा अगर (nvdimm && cmd == ND_CMD_VENDOR && idx == 2)
		वापस out_field[1];
	अन्यथा अगर (!nvdimm && cmd == ND_CMD_ARS_STATUS && idx == 2) अणु
		/*
		 * Per table 9-276 ARS Data in ACPI 6.1, out_field[1] is
		 * "Size of Output Buffer in bytes, including this
		 * field."
		 */
		अगर (out_field[1] < 4)
			वापस 0;
		/*
		 * ACPI 6.1 is ambiguous अगर 'status' is included in the
		 * output size. If we encounter an output size that
		 * overshoots the reमुख्यder by 4 bytes, assume it was
		 * including 'status'.
		 */
		अगर (out_field[1] - 4 == reमुख्यder)
			वापस reमुख्यder;
		वापस out_field[1] - 8;
	पूर्ण अन्यथा अगर (cmd == ND_CMD_CALL) अणु
		काष्ठा nd_cmd_pkg *pkg = (काष्ठा nd_cmd_pkg *) in_field;

		वापस pkg->nd_size_out;
	पूर्ण


	वापस अच_पूर्णांक_उच्च;
पूर्ण
EXPORT_SYMBOL_GPL(nd_cmd_out_size);

व्योम रुको_nvdimm_bus_probe_idle(काष्ठा device *dev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

	करो अणु
		अगर (nvdimm_bus->probe_active == 0)
			अवरोध;
		nvdimm_bus_unlock(dev);
		nd_device_unlock(dev);
		रुको_event(nvdimm_bus->रुको,
				nvdimm_bus->probe_active == 0);
		nd_device_lock(dev);
		nvdimm_bus_lock(dev);
	पूर्ण जबतक (true);
पूर्ण

अटल पूर्णांक nd_pmem_क्रमget_poison_check(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा nd_cmd_clear_error *clear_err =
		(काष्ठा nd_cmd_clear_error *)data;
	काष्ठा nd_btt *nd_btt = is_nd_btt(dev) ? to_nd_btt(dev) : शून्य;
	काष्ठा nd_pfn *nd_pfn = is_nd_pfn(dev) ? to_nd_pfn(dev) : शून्य;
	काष्ठा nd_dax *nd_dax = is_nd_dax(dev) ? to_nd_dax(dev) : शून्य;
	काष्ठा nd_namespace_common *ndns = शून्य;
	काष्ठा nd_namespace_io *nsio;
	resource_माप_प्रकार offset = 0, end_trunc = 0, start, end, pstart, pend;

	अगर (nd_dax || !dev->driver)
		वापस 0;

	start = clear_err->address;
	end = clear_err->address + clear_err->cleared - 1;

	अगर (nd_btt || nd_pfn || nd_dax) अणु
		अगर (nd_btt)
			ndns = nd_btt->ndns;
		अन्यथा अगर (nd_pfn)
			ndns = nd_pfn->ndns;
		अन्यथा अगर (nd_dax)
			ndns = nd_dax->nd_pfn.ndns;

		अगर (!ndns)
			वापस 0;
	पूर्ण अन्यथा
		ndns = to_ndns(dev);

	nsio = to_nd_namespace_io(&ndns->dev);
	pstart = nsio->res.start + offset;
	pend = nsio->res.end - end_trunc;

	अगर ((pstart >= start) && (pend <= end))
		वापस -EBUSY;

	वापस 0;

पूर्ण

अटल पूर्णांक nd_ns_क्रमget_poison_check(काष्ठा device *dev, व्योम *data)
अणु
	वापस device_क्रम_each_child(dev, data, nd_pmem_क्रमget_poison_check);
पूर्ण

/* set_config requires an idle पूर्णांकerleave set */
अटल पूर्णांक nd_cmd_clear_to_send(काष्ठा nvdimm_bus *nvdimm_bus,
		काष्ठा nvdimm *nvdimm, अचिन्हित पूर्णांक cmd, व्योम *data)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;

	/* ask the bus provider अगर it would like to block this request */
	अगर (nd_desc->clear_to_send) अणु
		पूर्णांक rc = nd_desc->clear_to_send(nd_desc, nvdimm, cmd, data);

		अगर (rc)
			वापस rc;
	पूर्ण

	/* require clear error to go through the pmem driver */
	अगर (!nvdimm && cmd == ND_CMD_CLEAR_ERROR)
		वापस device_क्रम_each_child(&nvdimm_bus->dev, data,
				nd_ns_क्रमget_poison_check);

	अगर (!nvdimm || cmd != ND_CMD_SET_CONFIG_DATA)
		वापस 0;

	/* prevent label manipulation जबतक the kernel owns label updates */
	रुको_nvdimm_bus_probe_idle(&nvdimm_bus->dev);
	अगर (atomic_पढ़ो(&nvdimm->busy))
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक __nd_ioctl(काष्ठा nvdimm_bus *nvdimm_bus, काष्ठा nvdimm *nvdimm,
		पूर्णांक पढ़ो_only, अचिन्हित पूर्णांक ioctl_cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा nvdimm_bus_descriptor *nd_desc = nvdimm_bus->nd_desc;
	स्थिर काष्ठा nd_cmd_desc *desc = शून्य;
	अचिन्हित पूर्णांक cmd = _IOC_NR(ioctl_cmd);
	काष्ठा device *dev = &nvdimm_bus->dev;
	व्योम __user *p = (व्योम __user *) arg;
	अक्षर *out_env = शून्य, *in_env = शून्य;
	स्थिर अक्षर *cmd_name, *dimm_name;
	u32 in_len = 0, out_len = 0;
	अचिन्हित पूर्णांक func = cmd;
	अचिन्हित दीर्घ cmd_mask;
	काष्ठा nd_cmd_pkg pkg;
	पूर्णांक rc, i, cmd_rc;
	व्योम *buf = शून्य;
	u64 buf_len = 0;

	अगर (nvdimm) अणु
		desc = nd_cmd_dimm_desc(cmd);
		cmd_name = nvdimm_cmd_name(cmd);
		cmd_mask = nvdimm->cmd_mask;
		dimm_name = dev_name(&nvdimm->dev);
	पूर्ण अन्यथा अणु
		desc = nd_cmd_bus_desc(cmd);
		cmd_name = nvdimm_bus_cmd_name(cmd);
		cmd_mask = nd_desc->cmd_mask;
		dimm_name = "bus";
	पूर्ण

	/* Validate command family support against bus declared support */
	अगर (cmd == ND_CMD_CALL) अणु
		अचिन्हित दीर्घ *mask;

		अगर (copy_from_user(&pkg, p, माप(pkg)))
			वापस -EFAULT;

		अगर (nvdimm) अणु
			अगर (pkg.nd_family > NVDIMM_FAMILY_MAX)
				वापस -EINVAL;
			mask = &nd_desc->dimm_family_mask;
		पूर्ण अन्यथा अणु
			अगर (pkg.nd_family > NVDIMM_BUS_FAMILY_MAX)
				वापस -EINVAL;
			mask = &nd_desc->bus_family_mask;
		पूर्ण

		अगर (!test_bit(pkg.nd_family, mask))
			वापस -EINVAL;
	पूर्ण

	अगर (!desc ||
	    (desc->out_num + desc->in_num == 0) ||
	    cmd > ND_CMD_CALL ||
	    !test_bit(cmd, &cmd_mask))
		वापस -ENOTTY;

	/* fail ग_लिखो commands (when पढ़ो-only) */
	अगर (पढ़ो_only)
		चयन (cmd) अणु
		हाल ND_CMD_VENDOR:
		हाल ND_CMD_SET_CONFIG_DATA:
		हाल ND_CMD_ARS_START:
		हाल ND_CMD_CLEAR_ERROR:
		हाल ND_CMD_CALL:
			dev_dbg(dev, "'%s' command while read-only.\n",
					nvdimm ? nvdimm_cmd_name(cmd)
					: nvdimm_bus_cmd_name(cmd));
			वापस -EPERM;
		शेष:
			अवरोध;
		पूर्ण

	/* process an input envelope */
	in_env = kzalloc(ND_CMD_MAX_ENVELOPE, GFP_KERNEL);
	अगर (!in_env)
		वापस -ENOMEM;
	क्रम (i = 0; i < desc->in_num; i++) अणु
		u32 in_size, copy;

		in_size = nd_cmd_in_size(nvdimm, cmd, desc, i, in_env);
		अगर (in_size == अच_पूर्णांक_उच्च) अणु
			dev_err(dev, "%s:%s unknown input size cmd: %s field: %d\n",
					__func__, dimm_name, cmd_name, i);
			rc = -ENXIO;
			जाओ out;
		पूर्ण
		अगर (in_len < ND_CMD_MAX_ENVELOPE)
			copy = min_t(u32, ND_CMD_MAX_ENVELOPE - in_len, in_size);
		अन्यथा
			copy = 0;
		अगर (copy && copy_from_user(&in_env[in_len], p + in_len, copy)) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण
		in_len += in_size;
	पूर्ण

	अगर (cmd == ND_CMD_CALL) अणु
		func = pkg.nd_command;
		dev_dbg(dev, "%s, idx: %llu, in: %u, out: %u, len %llu\n",
				dimm_name, pkg.nd_command,
				in_len, out_len, buf_len);
	पूर्ण

	/* process an output envelope */
	out_env = kzalloc(ND_CMD_MAX_ENVELOPE, GFP_KERNEL);
	अगर (!out_env) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < desc->out_num; i++) अणु
		u32 out_size = nd_cmd_out_size(nvdimm, cmd, desc, i,
				(u32 *) in_env, (u32 *) out_env, 0);
		u32 copy;

		अगर (out_size == अच_पूर्णांक_उच्च) अणु
			dev_dbg(dev, "%s unknown output size cmd: %s field: %d\n",
					dimm_name, cmd_name, i);
			rc = -EFAULT;
			जाओ out;
		पूर्ण
		अगर (out_len < ND_CMD_MAX_ENVELOPE)
			copy = min_t(u32, ND_CMD_MAX_ENVELOPE - out_len, out_size);
		अन्यथा
			copy = 0;
		अगर (copy && copy_from_user(&out_env[out_len],
					p + in_len + out_len, copy)) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण
		out_len += out_size;
	पूर्ण

	buf_len = (u64) out_len + (u64) in_len;
	अगर (buf_len > ND_IOCTL_MAX_BUFLEN) अणु
		dev_dbg(dev, "%s cmd: %s buf_len: %llu > %d\n", dimm_name,
				cmd_name, buf_len, ND_IOCTL_MAX_BUFLEN);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	buf = vदो_स्मृति(buf_len);
	अगर (!buf) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(buf, p, buf_len)) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	nd_device_lock(dev);
	nvdimm_bus_lock(dev);
	rc = nd_cmd_clear_to_send(nvdimm_bus, nvdimm, func, buf);
	अगर (rc)
		जाओ out_unlock;

	rc = nd_desc->ndctl(nd_desc, nvdimm, cmd, buf, buf_len, &cmd_rc);
	अगर (rc < 0)
		जाओ out_unlock;

	अगर (!nvdimm && cmd == ND_CMD_CLEAR_ERROR && cmd_rc >= 0) अणु
		काष्ठा nd_cmd_clear_error *clear_err = buf;

		nvdimm_account_cleared_poison(nvdimm_bus, clear_err->address,
				clear_err->cleared);
	पूर्ण

	अगर (copy_to_user(p, buf, buf_len))
		rc = -EFAULT;

out_unlock:
	nvdimm_bus_unlock(dev);
	nd_device_unlock(dev);
out:
	kमुक्त(in_env);
	kमुक्त(out_env);
	vमुक्त(buf);
	वापस rc;
पूर्ण

क्रमागत nd_ioctl_mode अणु
	BUS_IOCTL,
	DIMM_IOCTL,
पूर्ण;

अटल पूर्णांक match_dimm(काष्ठा device *dev, व्योम *data)
अणु
	दीर्घ id = (दीर्घ) data;

	अगर (is_nvdimm(dev)) अणु
		काष्ठा nvdimm *nvdimm = to_nvdimm(dev);

		वापस nvdimm->id == id;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ nd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
		क्रमागत nd_ioctl_mode mode)

अणु
	काष्ठा nvdimm_bus *nvdimm_bus, *found = शून्य;
	दीर्घ id = (दीर्घ) file->निजी_data;
	काष्ठा nvdimm *nvdimm = शून्य;
	पूर्णांक rc, ro;

	ro = ((file->f_flags & O_ACCMODE) == O_RDONLY);
	mutex_lock(&nvdimm_bus_list_mutex);
	list_क्रम_each_entry(nvdimm_bus, &nvdimm_bus_list, list) अणु
		अगर (mode == DIMM_IOCTL) अणु
			काष्ठा device *dev;

			dev = device_find_child(&nvdimm_bus->dev,
					file->निजी_data, match_dimm);
			अगर (!dev)
				जारी;
			nvdimm = to_nvdimm(dev);
			found = nvdimm_bus;
		पूर्ण अन्यथा अगर (nvdimm_bus->id == id) अणु
			found = nvdimm_bus;
		पूर्ण

		अगर (found) अणु
			atomic_inc(&nvdimm_bus->ioctl_active);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&nvdimm_bus_list_mutex);

	अगर (!found)
		वापस -ENXIO;

	nvdimm_bus = found;
	rc = __nd_ioctl(nvdimm_bus, nvdimm, ro, cmd, arg);

	अगर (nvdimm)
		put_device(&nvdimm->dev);
	अगर (atomic_dec_and_test(&nvdimm_bus->ioctl_active))
		wake_up(&nvdimm_bus->रुको);

	वापस rc;
पूर्ण

अटल दीर्घ bus_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस nd_ioctl(file, cmd, arg, BUS_IOCTL);
पूर्ण

अटल दीर्घ dimm_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस nd_ioctl(file, cmd, arg, DIMM_IOCTL);
पूर्ण

अटल पूर्णांक nd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	दीर्घ minor = iminor(inode);

	file->निजी_data = (व्योम *) minor;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations nvdimm_bus_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = nd_खोलो,
	.unlocked_ioctl = bus_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations nvdimm_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = nd_खोलो,
	.unlocked_ioctl = dimm_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.llseek = noop_llseek,
पूर्ण;

पूर्णांक __init nvdimm_bus_init(व्योम)
अणु
	पूर्णांक rc;

	rc = bus_रेजिस्टर(&nvdimm_bus_type);
	अगर (rc)
		वापस rc;

	rc = रेजिस्टर_chrdev(0, "ndctl", &nvdimm_bus_fops);
	अगर (rc < 0)
		जाओ err_bus_chrdev;
	nvdimm_bus_major = rc;

	rc = रेजिस्टर_chrdev(0, "dimmctl", &nvdimm_fops);
	अगर (rc < 0)
		जाओ err_dimm_chrdev;
	nvdimm_major = rc;

	nd_class = class_create(THIS_MODULE, "nd");
	अगर (IS_ERR(nd_class)) अणु
		rc = PTR_ERR(nd_class);
		जाओ err_class;
	पूर्ण

	rc = driver_रेजिस्टर(&nd_bus_driver.drv);
	अगर (rc)
		जाओ err_nd_bus;

	वापस 0;

 err_nd_bus:
	class_destroy(nd_class);
 err_class:
	unरेजिस्टर_chrdev(nvdimm_major, "dimmctl");
 err_dimm_chrdev:
	unरेजिस्टर_chrdev(nvdimm_bus_major, "ndctl");
 err_bus_chrdev:
	bus_unरेजिस्टर(&nvdimm_bus_type);

	वापस rc;
पूर्ण

व्योम nvdimm_bus_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&nd_bus_driver.drv);
	class_destroy(nd_class);
	unरेजिस्टर_chrdev(nvdimm_bus_major, "ndctl");
	unरेजिस्टर_chrdev(nvdimm_major, "dimmctl");
	bus_unरेजिस्टर(&nvdimm_bus_type);
	ida_destroy(&nd_ida);
पूर्ण
