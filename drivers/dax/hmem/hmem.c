<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memregion.h>
#समावेश <linux/module.h>
#समावेश <linux/pfn_t.h>
#समावेश "../bus.h"

अटल bool region_idle;
module_param_named(region_idle, region_idle, bool, 0644);

अटल पूर्णांक dax_hmem_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dax_region *dax_region;
	काष्ठा memregion_info *mri;
	काष्ठा dev_dax_data data;
	काष्ठा dev_dax *dev_dax;
	काष्ठा resource *res;
	काष्ठा range range;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOMEM;

	mri = dev->platक्रमm_data;
	range.start = res->start;
	range.end = res->end;
	dax_region = alloc_dax_region(dev, pdev->id, &range, mri->target_node,
			PMD_SIZE, 0);
	अगर (!dax_region)
		वापस -ENOMEM;

	data = (काष्ठा dev_dax_data) अणु
		.dax_region = dax_region,
		.id = -1,
		.size = region_idle ? 0 : resource_size(res),
	पूर्ण;
	dev_dax = devm_create_dev_dax(&data);
	अगर (IS_ERR(dev_dax))
		वापस PTR_ERR(dev_dax);

	/* child dev_dax instances now own the lअगरeसमय of the dax_region */
	dax_region_put(dax_region);
	वापस 0;
पूर्ण

अटल पूर्णांक dax_hmem_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	/* devm handles tearकरोwn */
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dax_hmem_driver = अणु
	.probe = dax_hmem_probe,
	.हटाओ = dax_hmem_हटाओ,
	.driver = अणु
		.name = "hmem",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dax_hmem_driver);

MODULE_ALIAS("platform:hmem*");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Intel Corporation");
