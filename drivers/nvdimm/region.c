<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2015 Intel Corporation. All rights reserved.
 */
#समावेश <linux/cpumask.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/nd.h>
#समावेश "nd-core.h"
#समावेश "nd.h"

अटल पूर्णांक nd_region_probe(काष्ठा device *dev)
अणु
	पूर्णांक err, rc;
	अटल अचिन्हित दीर्घ once;
	काष्ठा nd_region_data *ndrd;
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	अगर (nd_region->num_lanes > num_online_cpus()
			&& nd_region->num_lanes < num_possible_cpus()
			&& !test_and_set_bit(0, &once)) अणु
		dev_dbg(dev, "online cpus (%d) < concurrent i/o lanes (%d) < possible cpus (%d)\n",
				num_online_cpus(), nd_region->num_lanes,
				num_possible_cpus());
		dev_dbg(dev, "setting nr_cpus=%d may yield better libnvdimm device performance\n",
				nd_region->num_lanes);
	पूर्ण

	rc = nd_region_activate(nd_region);
	अगर (rc)
		वापस rc;

	rc = nd_blk_region_init(nd_region);
	अगर (rc)
		वापस rc;

	अगर (is_memory(&nd_region->dev)) अणु
		काष्ठा range range = अणु
			.start = nd_region->ndr_start,
			.end = nd_region->ndr_start + nd_region->ndr_size - 1,
		पूर्ण;

		अगर (devm_init_badblocks(dev, &nd_region->bb))
			वापस -ENODEV;
		nd_region->bb_state = sysfs_get_dirent(nd_region->dev.kobj.sd,
						       "badblocks");
		अगर (!nd_region->bb_state)
			dev_warn(&nd_region->dev,
					"'badblocks' notification disabled\n");
		nvdimm_badblocks_populate(nd_region, &nd_region->bb, &range);
	पूर्ण

	rc = nd_region_रेजिस्टर_namespaces(nd_region, &err);
	अगर (rc < 0)
		वापस rc;

	ndrd = dev_get_drvdata(dev);
	ndrd->ns_active = rc;
	ndrd->ns_count = rc + err;

	अगर (rc && err && rc == err)
		वापस -ENODEV;

	nd_region->btt_seed = nd_btt_create(nd_region);
	nd_region->pfn_seed = nd_pfn_create(nd_region);
	nd_region->dax_seed = nd_dax_create(nd_region);
	अगर (err == 0)
		वापस 0;

	/*
	 * Given multiple namespaces per region, we करो not want to
	 * disable all the successfully रेजिस्टरed peer namespaces upon
	 * a single registration failure.  If userspace is missing a
	 * namespace that it expects it can disable/re-enable the region
	 * to retry discovery after correcting the failure.
	 * <regionX>/namespaces वापसs the current
	 * "<async-registered>/<total>" namespace count.
	 */
	dev_err(dev, "failed to register %d namespace%s, continuing...\n",
			err, err == 1 ? "" : "s");
	वापस 0;
पूर्ण

अटल पूर्णांक child_unरेजिस्टर(काष्ठा device *dev, व्योम *data)
अणु
	nd_device_unरेजिस्टर(dev, ND_SYNC);
	वापस 0;
पूर्ण

अटल व्योम nd_region_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev);

	device_क्रम_each_child(dev, शून्य, child_unरेजिस्टर);

	/* flush attribute पढ़ोers and disable */
	nvdimm_bus_lock(dev);
	nd_region->ns_seed = शून्य;
	nd_region->btt_seed = शून्य;
	nd_region->pfn_seed = शून्य;
	nd_region->dax_seed = शून्य;
	dev_set_drvdata(dev, शून्य);
	nvdimm_bus_unlock(dev);

	/*
	 * Note, this assumes nd_device_lock() context to not race
	 * nd_region_notअगरy()
	 */
	sysfs_put(nd_region->bb_state);
	nd_region->bb_state = शून्य;
पूर्ण

अटल पूर्णांक child_notअगरy(काष्ठा device *dev, व्योम *data)
अणु
	nd_device_notअगरy(dev, *(क्रमागत nvdimm_event *) data);
	वापस 0;
पूर्ण

अटल व्योम nd_region_notअगरy(काष्ठा device *dev, क्रमागत nvdimm_event event)
अणु
	अगर (event == NVDIMM_REVALIDATE_POISON) अणु
		काष्ठा nd_region *nd_region = to_nd_region(dev);

		अगर (is_memory(&nd_region->dev)) अणु
			काष्ठा range range = अणु
				.start = nd_region->ndr_start,
				.end = nd_region->ndr_start +
					nd_region->ndr_size - 1,
			पूर्ण;

			nvdimm_badblocks_populate(nd_region,
					&nd_region->bb, &range);
			अगर (nd_region->bb_state)
				sysfs_notअगरy_dirent(nd_region->bb_state);
		पूर्ण
	पूर्ण
	device_क्रम_each_child(dev, &event, child_notअगरy);
पूर्ण

अटल काष्ठा nd_device_driver nd_region_driver = अणु
	.probe = nd_region_probe,
	.हटाओ = nd_region_हटाओ,
	.notअगरy = nd_region_notअगरy,
	.drv = अणु
		.name = "nd_region",
	पूर्ण,
	.type = ND_DRIVER_REGION_BLK | ND_DRIVER_REGION_PMEM,
पूर्ण;

पूर्णांक __init nd_region_init(व्योम)
अणु
	वापस nd_driver_रेजिस्टर(&nd_region_driver);
पूर्ण

व्योम nd_region_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&nd_region_driver.drv);
पूर्ण

MODULE_ALIAS_ND_DEVICE(ND_DEVICE_REGION_PMEM);
MODULE_ALIAS_ND_DEVICE(ND_DEVICE_REGION_BLK);
