<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Christoph Hellwig.
 * Copyright (c) 2015, Intel Corporation.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/module.h>
#समावेश <linux/numa.h>

अटल पूर्णांक e820_pmem_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus = platक्रमm_get_drvdata(pdev);

	nvdimm_bus_unरेजिस्टर(nvdimm_bus);
	वापस 0;
पूर्ण

अटल पूर्णांक e820_रेजिस्टर_one(काष्ठा resource *res, व्योम *data)
अणु
	काष्ठा nd_region_desc ndr_desc;
	काष्ठा nvdimm_bus *nvdimm_bus = data;
	पूर्णांक nid = phys_to_target_node(res->start);

	स_रखो(&ndr_desc, 0, माप(ndr_desc));
	ndr_desc.res = res;
	ndr_desc.numa_node = numa_map_to_online_node(nid);
	ndr_desc.target_node = nid;
	set_bit(ND_REGION_PAGEMAP, &ndr_desc.flags);
	अगर (!nvdimm_pmem_region_create(nvdimm_bus, &ndr_desc))
		वापस -ENXIO;
	वापस 0;
पूर्ण

अटल पूर्णांक e820_pmem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल काष्ठा nvdimm_bus_descriptor nd_desc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nvdimm_bus *nvdimm_bus;
	पूर्णांक rc = -ENXIO;

	nd_desc.provider_name = "e820";
	nd_desc.module = THIS_MODULE;
	nvdimm_bus = nvdimm_bus_रेजिस्टर(dev, &nd_desc);
	अगर (!nvdimm_bus)
		जाओ err;
	platक्रमm_set_drvdata(pdev, nvdimm_bus);

	rc = walk_iomem_res_desc(IORES_DESC_PERSISTENT_MEMORY_LEGACY,
			IORESOURCE_MEM, 0, -1, nvdimm_bus, e820_रेजिस्टर_one);
	अगर (rc)
		जाओ err;
	वापस 0;
err:
	nvdimm_bus_unरेजिस्टर(nvdimm_bus);
	dev_err(dev, "failed to register legacy persistent memory ranges\n");
	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver e820_pmem_driver = अणु
	.probe = e820_pmem_probe,
	.हटाओ = e820_pmem_हटाओ,
	.driver = अणु
		.name = "e820_pmem",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(e820_pmem_driver);

MODULE_ALIAS("platform:e820_pmem*");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
