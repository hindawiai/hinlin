<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memregion.h>
#समावेश <linux/module.h>
#समावेश <linux/dax.h>
#समावेश <linux/mm.h>

अटल bool nohmem;
module_param_named(disable, nohmem, bool, 0444);

व्योम hmem_रेजिस्टर_device(पूर्णांक target_nid, काष्ठा resource *r)
अणु
	/* define a clean / non-busy resource क्रम the platक्रमm device */
	काष्ठा resource res = अणु
		.start = r->start,
		.end = r->end,
		.flags = IORESOURCE_MEM,
	पूर्ण;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा memregion_info info;
	पूर्णांक rc, id;

	अगर (nohmem)
		वापस;

	rc = region_पूर्णांकersects(res.start, resource_size(&res), IORESOURCE_MEM,
			IORES_DESC_SOFT_RESERVED);
	अगर (rc != REGION_INTERSECTS)
		वापस;

	id = memregion_alloc(GFP_KERNEL);
	अगर (id < 0) अणु
		pr_err("memregion allocation failure for %pr\n", &res);
		वापस;
	पूर्ण

	pdev = platक्रमm_device_alloc("hmem", id);
	अगर (!pdev) अणु
		pr_err("hmem device allocation failure for %pr\n", &res);
		जाओ out_pdev;
	पूर्ण

	pdev->dev.numa_node = numa_map_to_online_node(target_nid);
	info = (काष्ठा memregion_info) अणु
		.target_node = target_nid,
	पूर्ण;
	rc = platक्रमm_device_add_data(pdev, &info, माप(info));
	अगर (rc < 0) अणु
		pr_err("hmem memregion_info allocation failure for %pr\n", &res);
		जाओ out_pdev;
	पूर्ण

	rc = platक्रमm_device_add_resources(pdev, &res, 1);
	अगर (rc < 0) अणु
		pr_err("hmem resource allocation failure for %pr\n", &res);
		जाओ out_resource;
	पूर्ण

	rc = platक्रमm_device_add(pdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "device add failed for %pr\n", &res);
		जाओ out_resource;
	पूर्ण

	वापस;

out_resource:
	put_device(&pdev->dev);
out_pdev:
	memregion_मुक्त(id);
पूर्ण

अटल __init पूर्णांक hmem_रेजिस्टर_one(काष्ठा resource *res, व्योम *data)
अणु
	/*
	 * If the resource is not a top-level resource it was alपढ़ोy
	 * asचिन्हित to a device by the HMAT parsing.
	 */
	अगर (res->parent != &iomem_resource) अणु
		pr_info("HMEM: skip %pr, already claimed\n", res);
		वापस 0;
	पूर्ण

	hmem_रेजिस्टर_device(phys_to_target_node(res->start), res);

	वापस 0;
पूर्ण

अटल __init पूर्णांक hmem_init(व्योम)
अणु
	walk_iomem_res_desc(IORES_DESC_SOFT_RESERVED,
			IORESOURCE_MEM, 0, -1, शून्य, hmem_रेजिस्टर_one);
	वापस 0;
पूर्ण

/*
 * As this is a fallback क्रम address ranges unclaimed by the ACPI HMAT
 * parsing it must be at an initcall level greater than hmat_init().
 */
late_initcall(hmem_init);
