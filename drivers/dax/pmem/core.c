<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2016 - 2018 Intel Corporation. All rights reserved. */
#समावेश <linux/memremap.h>
#समावेश <linux/module.h>
#समावेश <linux/pfn_t.h>
#समावेश "../../nvdimm/pfn.h"
#समावेश "../../nvdimm/nd.h"
#समावेश "../bus.h"

काष्ठा dev_dax *__dax_pmem_probe(काष्ठा device *dev, क्रमागत dev_dax_subsys subsys)
अणु
	काष्ठा range range;
	पूर्णांक rc, id, region_id;
	resource_माप_प्रकार offset;
	काष्ठा nd_pfn_sb *pfn_sb;
	काष्ठा dev_dax *dev_dax;
	काष्ठा dev_dax_data data;
	काष्ठा nd_namespace_io *nsio;
	काष्ठा dax_region *dax_region;
	काष्ठा dev_pagemap pgmap = अणु पूर्ण;
	काष्ठा nd_namespace_common *ndns;
	काष्ठा nd_dax *nd_dax = to_nd_dax(dev);
	काष्ठा nd_pfn *nd_pfn = &nd_dax->nd_pfn;
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);

	ndns = nvdimm_namespace_common_probe(dev);
	अगर (IS_ERR(ndns))
		वापस ERR_CAST(ndns);

	/* parse the 'pfn' info block via ->rw_bytes */
	rc = devm_namespace_enable(dev, ndns, nd_info_block_reserve());
	अगर (rc)
		वापस ERR_PTR(rc);
	rc = nvdimm_setup_pfn(nd_pfn, &pgmap);
	अगर (rc)
		वापस ERR_PTR(rc);
	devm_namespace_disable(dev, ndns);

	/* reserve the metadata area, device-dax will reserve the data */
	pfn_sb = nd_pfn->pfn_sb;
	offset = le64_to_cpu(pfn_sb->dataoff);
	nsio = to_nd_namespace_io(&ndns->dev);
	अगर (!devm_request_mem_region(dev, nsio->res.start, offset,
				dev_name(&ndns->dev))) अणु
		dev_warn(dev, "could not reserve metadata\n");
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	rc = माला_पूछो(dev_name(&ndns->dev), "namespace%d.%d", &region_id, &id);
	अगर (rc != 2)
		वापस ERR_PTR(-EINVAL);

	/* adjust the dax_region range to the start of data */
	range = pgmap.range;
	range.start += offset;
	dax_region = alloc_dax_region(dev, region_id, &range,
			nd_region->target_node, le32_to_cpu(pfn_sb->align),
			IORESOURCE_DAX_STATIC);
	अगर (!dax_region)
		वापस ERR_PTR(-ENOMEM);

	data = (काष्ठा dev_dax_data) अणु
		.dax_region = dax_region,
		.id = id,
		.pgmap = &pgmap,
		.subsys = subsys,
		.size = range_len(&range),
	पूर्ण;
	dev_dax = devm_create_dev_dax(&data);

	/* child dev_dax instances now own the lअगरeसमय of the dax_region */
	dax_region_put(dax_region);

	वापस dev_dax;
पूर्ण
EXPORT_SYMBOL_GPL(__dax_pmem_probe);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
