<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2013-2016 Intel Corporation. All rights reserved.
 */
#समावेश <linux/device.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश "nd-core.h"
#समावेश "pfn.h"
#समावेश "nd.h"

अटल व्योम nd_dax_release(काष्ठा device *dev)
अणु
	काष्ठा nd_region *nd_region = to_nd_region(dev->parent);
	काष्ठा nd_dax *nd_dax = to_nd_dax(dev);
	काष्ठा nd_pfn *nd_pfn = &nd_dax->nd_pfn;

	dev_dbg(dev, "trace\n");
	nd_detach_ndns(dev, &nd_pfn->ndns);
	ida_simple_हटाओ(&nd_region->dax_ida, nd_pfn->id);
	kमुक्त(nd_pfn->uuid);
	kमुक्त(nd_dax);
पूर्ण

काष्ठा nd_dax *to_nd_dax(काष्ठा device *dev)
अणु
	काष्ठा nd_dax *nd_dax = container_of(dev, काष्ठा nd_dax, nd_pfn.dev);

	WARN_ON(!is_nd_dax(dev));
	वापस nd_dax;
पूर्ण
EXPORT_SYMBOL(to_nd_dax);

अटल स्थिर काष्ठा device_type nd_dax_device_type = अणु
	.name = "nd_dax",
	.release = nd_dax_release,
	.groups = nd_pfn_attribute_groups,
पूर्ण;

bool is_nd_dax(काष्ठा device *dev)
अणु
	वापस dev ? dev->type == &nd_dax_device_type : false;
पूर्ण
EXPORT_SYMBOL(is_nd_dax);

अटल काष्ठा nd_dax *nd_dax_alloc(काष्ठा nd_region *nd_region)
अणु
	काष्ठा nd_pfn *nd_pfn;
	काष्ठा nd_dax *nd_dax;
	काष्ठा device *dev;

	nd_dax = kzalloc(माप(*nd_dax), GFP_KERNEL);
	अगर (!nd_dax)
		वापस शून्य;

	nd_pfn = &nd_dax->nd_pfn;
	nd_pfn->id = ida_simple_get(&nd_region->dax_ida, 0, 0, GFP_KERNEL);
	अगर (nd_pfn->id < 0) अणु
		kमुक्त(nd_dax);
		वापस शून्य;
	पूर्ण

	dev = &nd_pfn->dev;
	dev_set_name(dev, "dax%d.%d", nd_region->id, nd_pfn->id);
	dev->type = &nd_dax_device_type;
	dev->parent = &nd_region->dev;

	वापस nd_dax;
पूर्ण

काष्ठा device *nd_dax_create(काष्ठा nd_region *nd_region)
अणु
	काष्ठा device *dev = शून्य;
	काष्ठा nd_dax *nd_dax;

	अगर (!is_memory(&nd_region->dev))
		वापस शून्य;

	nd_dax = nd_dax_alloc(nd_region);
	अगर (nd_dax)
		dev = nd_pfn_devinit(&nd_dax->nd_pfn, शून्य);
	__nd_device_रेजिस्टर(dev);
	वापस dev;
पूर्ण

पूर्णांक nd_dax_probe(काष्ठा device *dev, काष्ठा nd_namespace_common *ndns)
अणु
	पूर्णांक rc;
	काष्ठा nd_dax *nd_dax;
	काष्ठा device *dax_dev;
	काष्ठा nd_pfn *nd_pfn;
	काष्ठा nd_pfn_sb *pfn_sb;
	काष्ठा nd_region *nd_region = to_nd_region(ndns->dev.parent);

	अगर (ndns->क्रमce_raw)
		वापस -ENODEV;

	चयन (ndns->claim_class) अणु
	हाल NVDIMM_CCLASS_NONE:
	हाल NVDIMM_CCLASS_DAX:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	nvdimm_bus_lock(&ndns->dev);
	nd_dax = nd_dax_alloc(nd_region);
	nd_pfn = &nd_dax->nd_pfn;
	dax_dev = nd_pfn_devinit(nd_pfn, ndns);
	nvdimm_bus_unlock(&ndns->dev);
	अगर (!dax_dev)
		वापस -ENOMEM;
	pfn_sb = devm_kदो_स्मृति(dev, माप(*pfn_sb), GFP_KERNEL);
	nd_pfn->pfn_sb = pfn_sb;
	rc = nd_pfn_validate(nd_pfn, DAX_SIG);
	dev_dbg(dev, "dax: %s\n", rc == 0 ? dev_name(dax_dev) : "<none>");
	अगर (rc < 0) अणु
		nd_detach_ndns(dax_dev, &nd_pfn->ndns);
		put_device(dax_dev);
	पूर्ण अन्यथा
		__nd_device_रेजिस्टर(dax_dev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(nd_dax_probe);
