<शैली गुरु>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/agp_backend.h>
#समावेश "../../../arch/alpha/kernel/pci_impl.h"

#समावेश "agp.h"

अटल vm_fault_t alpha_core_agp_vm_fault(काष्ठा vm_fault *vmf)
अणु
	alpha_agp_info *agp = agp_bridge->dev_निजी_data;
	dma_addr_t dma_addr;
	अचिन्हित दीर्घ pa;
	काष्ठा page *page;

	dma_addr = vmf->address - vmf->vma->vm_start + agp->aperture.bus_base;
	pa = agp->ops->translate(agp, dma_addr);

	अगर (pa == (अचिन्हित दीर्घ)-EINVAL)
		वापस VM_FAULT_SIGBUS;	/* no translation */

	/*
	 * Get the page, inc the use count, and वापस it
	 */
	page = virt_to_page(__va(pa));
	get_page(page);
	vmf->page = page;
	वापस 0;
पूर्ण

अटल काष्ठा aper_size_info_fixed alpha_core_agp_sizes[] =
अणु
	अणु 0, 0, 0 पूर्ण, /* filled in by alpha_core_agp_setup */
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा alpha_core_agp_vm_ops = अणु
	.fault = alpha_core_agp_vm_fault,
पूर्ण;


अटल पूर्णांक alpha_core_agp_fetch_size(व्योम)
अणु
	वापस alpha_core_agp_sizes[0].size;
पूर्ण

अटल पूर्णांक alpha_core_agp_configure(व्योम)
अणु
	alpha_agp_info *agp = agp_bridge->dev_निजी_data;
	agp_bridge->gart_bus_addr = agp->aperture.bus_base;
	वापस 0;
पूर्ण

अटल व्योम alpha_core_agp_cleanup(व्योम)
अणु
	alpha_agp_info *agp = agp_bridge->dev_निजी_data;

	agp->ops->cleanup(agp);
पूर्ण

अटल व्योम alpha_core_agp_tlbflush(काष्ठा agp_memory *mem)
अणु
	alpha_agp_info *agp = agp_bridge->dev_निजी_data;
	alpha_mv.mv_pci_tbi(agp->hose, 0, -1);
पूर्ण

अटल व्योम alpha_core_agp_enable(काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	alpha_agp_info *agp = bridge->dev_निजी_data;

	agp->mode.lw = agp_collect_device_status(bridge, mode,
					agp->capability.lw);

	agp->mode.bits.enable = 1;
	agp->ops->configure(agp);

	agp_device_command(agp->mode.lw, false);
पूर्ण

अटल पूर्णांक alpha_core_agp_insert_memory(काष्ठा agp_memory *mem, off_t pg_start,
					पूर्णांक type)
अणु
	alpha_agp_info *agp = agp_bridge->dev_निजी_data;
	पूर्णांक num_entries, status;
	व्योम *temp;

	अगर (type >= AGP_USER_TYPES || mem->type >= AGP_USER_TYPES)
		वापस -EINVAL;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_FIX(temp)->num_entries;
	अगर ((pg_start + mem->page_count) > num_entries)
		वापस -EINVAL;

	status = agp->ops->bind(agp, pg_start, mem);
	mb();
	alpha_core_agp_tlbflush(mem);

	वापस status;
पूर्ण

अटल पूर्णांक alpha_core_agp_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start,
					पूर्णांक type)
अणु
	alpha_agp_info *agp = agp_bridge->dev_निजी_data;
	पूर्णांक status;

	status = agp->ops->unbind(agp, pg_start, mem);
	alpha_core_agp_tlbflush(mem);
	वापस status;
पूर्ण

अटल पूर्णांक alpha_core_agp_create_मुक्त_gatt_table(काष्ठा agp_bridge_data *a)
अणु
	वापस 0;
पूर्ण

काष्ठा agp_bridge_driver alpha_core_agp_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= alpha_core_agp_sizes,
	.num_aperture_sizes	= 1,
	.माप_प्रकारype		= FIXED_APER_SIZE,
	.cant_use_aperture	= true,
	.masks			= शून्य,

	.fetch_size		= alpha_core_agp_fetch_size,
	.configure		= alpha_core_agp_configure,
	.agp_enable		= alpha_core_agp_enable,
	.cleanup		= alpha_core_agp_cleanup,
	.tlb_flush		= alpha_core_agp_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= alpha_core_agp_create_मुक्त_gatt_table,
	.मुक्त_gatt_table	= alpha_core_agp_create_मुक्त_gatt_table,
	.insert_memory		= alpha_core_agp_insert_memory,
	.हटाओ_memory		= alpha_core_agp_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

काष्ठा agp_bridge_data *alpha_bridge;

पूर्णांक __init
alpha_core_agp_setup(व्योम)
अणु
	alpha_agp_info *agp = alpha_mv.agp_info();
	काष्ठा pci_dev *pdev;	/* faked */
	काष्ठा aper_size_info_fixed *aper_size;

	अगर (!agp)
		वापस -ENODEV;
	अगर (agp->ops->setup(agp))
		वापस -ENODEV;

	/*
	 * Build the aperture size descriptor
	 */
	aper_size = alpha_core_agp_sizes;
	aper_size->size = agp->aperture.size / (1024 * 1024);
	aper_size->num_entries = agp->aperture.size / PAGE_SIZE;
	aper_size->page_order = __ffs(aper_size->num_entries / 1024);

	/*
	 * Build a fake pci_dev काष्ठा
	 */
	pdev = pci_alloc_dev(शून्य);
	अगर (!pdev)
		वापस -ENOMEM;
	pdev->venकरोr = 0xffff;
	pdev->device = 0xffff;
	pdev->sysdata = agp->hose;

	alpha_bridge = agp_alloc_bridge();
	अगर (!alpha_bridge)
		जाओ fail;

	alpha_bridge->driver = &alpha_core_agp_driver;
	alpha_bridge->vm_ops = &alpha_core_agp_vm_ops;
	alpha_bridge->current_size = aper_size; /* only 1 size */
	alpha_bridge->dev_निजी_data = agp;
	alpha_bridge->dev = pdev;
	alpha_bridge->mode = agp->capability.lw;

	prपूर्णांकk(KERN_INFO PFX "Detected AGP on hose %d\n", agp->hose->index);
	वापस agp_add_bridge(alpha_bridge);

 fail:
	kमुक्त(pdev);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __init agp_alpha_core_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	अगर (alpha_mv.agp_info)
		वापस alpha_core_agp_setup();
	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास agp_alpha_core_cleanup(व्योम)
अणु
	agp_हटाओ_bridge(alpha_bridge);
	agp_put_bridge(alpha_bridge);
पूर्ण

module_init(agp_alpha_core_init);
module_निकास(agp_alpha_core_cleanup);

MODULE_AUTHOR("Jeff Wiedemeier <Jeff.Wiedemeier@hp.com>");
MODULE_LICENSE("GPL and additional rights");
