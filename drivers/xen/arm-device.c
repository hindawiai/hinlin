<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, Linaro Limited, Shannon Zhao
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <xen/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

अटल पूर्णांक xen_unmap_device_mmio(स्थिर काष्ठा resource *resources,
				 अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i, j, nr;
	पूर्णांक rc = 0;
	स्थिर काष्ठा resource *r;
	काष्ठा xen_हटाओ_from_physmap xrp;

	क्रम (i = 0; i < count; i++) अणु
		r = &resources[i];
		nr = DIV_ROUND_UP(resource_size(r), XEN_PAGE_SIZE);
		अगर ((resource_type(r) != IORESOURCE_MEM) || (nr == 0))
			जारी;

		क्रम (j = 0; j < nr; j++) अणु
			xrp.करोmid = DOMID_SELF;
			xrp.gpfn = XEN_PFN_DOWN(r->start) + j;
			rc = HYPERVISOR_memory_op(XENMEM_हटाओ_from_physmap,
						  &xrp);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक xen_map_device_mmio(स्थिर काष्ठा resource *resources,
			       अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i, j, nr;
	पूर्णांक rc = 0;
	स्थिर काष्ठा resource *r;
	xen_pfn_t *gpfns;
	xen_uदीर्घ_t *idxs;
	पूर्णांक *errs;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा xen_add_to_physmap_range xatp = अणु
			.करोmid = DOMID_SELF,
			.space = XENMAPSPACE_dev_mmio
		पूर्ण;

		r = &resources[i];
		nr = DIV_ROUND_UP(resource_size(r), XEN_PAGE_SIZE);
		अगर ((resource_type(r) != IORESOURCE_MEM) || (nr == 0))
			जारी;

		gpfns = kसुस्मृति(nr, माप(xen_pfn_t), GFP_KERNEL);
		idxs = kसुस्मृति(nr, माप(xen_uदीर्घ_t), GFP_KERNEL);
		errs = kसुस्मृति(nr, माप(पूर्णांक), GFP_KERNEL);
		अगर (!gpfns || !idxs || !errs) अणु
			kमुक्त(gpfns);
			kमुक्त(idxs);
			kमुक्त(errs);
			rc = -ENOMEM;
			जाओ unmap;
		पूर्ण

		क्रम (j = 0; j < nr; j++) अणु
			/*
			 * The regions are always mapped 1:1 to DOM0 and this is
			 * fine because the memory map क्रम DOM0 is the same as
			 * the host (except क्रम the RAM).
			 */
			gpfns[j] = XEN_PFN_DOWN(r->start) + j;
			idxs[j] = XEN_PFN_DOWN(r->start) + j;
		पूर्ण

		xatp.size = nr;

		set_xen_guest_handle(xatp.gpfns, gpfns);
		set_xen_guest_handle(xatp.idxs, idxs);
		set_xen_guest_handle(xatp.errs, errs);

		rc = HYPERVISOR_memory_op(XENMEM_add_to_physmap_range, &xatp);
		kमुक्त(gpfns);
		kमुक्त(idxs);
		kमुक्त(errs);
		अगर (rc)
			जाओ unmap;
	पूर्ण

	वापस rc;

unmap:
	xen_unmap_device_mmio(resources, i);
	वापस rc;
पूर्ण

अटल पूर्णांक xen_platक्रमm_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(data);
	पूर्णांक r = 0;

	अगर (pdev->num_resources == 0 || pdev->resource == शून्य)
		वापस NOTIFY_OK;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		r = xen_map_device_mmio(pdev->resource, pdev->num_resources);
		अवरोध;
	हाल BUS_NOTIFY_DEL_DEVICE:
		r = xen_unmap_device_mmio(pdev->resource, pdev->num_resources);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
	अगर (r)
		dev_err(&pdev->dev, "Platform: Failed to %s device %s MMIO!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "map" :
			(action == BUS_NOTIFY_DEL_DEVICE ? "unmap" : "?"),
			pdev->name);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block platक्रमm_device_nb = अणु
	.notअगरier_call = xen_platक्रमm_notअगरier,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_xen_platक्रमm_notअगरier(व्योम)
अणु
	अगर (!xen_initial_करोमुख्य() || acpi_disabled)
		वापस 0;

	वापस bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &platक्रमm_device_nb);
पूर्ण

arch_initcall(रेजिस्टर_xen_platक्रमm_notअगरier);

#अगर_घोषित CONFIG_ARM_AMBA
#समावेश <linux/amba/bus.h>

अटल पूर्णांक xen_amba_notअगरier(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा amba_device *adev = to_amba_device(data);
	पूर्णांक r = 0;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		r = xen_map_device_mmio(&adev->res, 1);
		अवरोध;
	हाल BUS_NOTIFY_DEL_DEVICE:
		r = xen_unmap_device_mmio(&adev->res, 1);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
	अगर (r)
		dev_err(&adev->dev, "AMBA: Failed to %s device %s MMIO!\n",
			action == BUS_NOTIFY_ADD_DEVICE ? "map" :
			(action == BUS_NOTIFY_DEL_DEVICE ? "unmap" : "?"),
			adev->dev.init_name);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block amba_device_nb = अणु
	.notअगरier_call = xen_amba_notअगरier,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_xen_amba_notअगरier(व्योम)
अणु
	अगर (!xen_initial_करोमुख्य() || acpi_disabled)
		वापस 0;

	वापस bus_रेजिस्टर_notअगरier(&amba_bustype, &amba_device_nb);
पूर्ण

arch_initcall(रेजिस्टर_xen_amba_notअगरier);
#पूर्ण_अगर
