<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Extensible Firmware Interface
 *
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 *
 * Based on Extensible Firmware Interface Specअगरication version 2.4
 * Adapted from drivers/firmware/efi/arm-runसमय.c
 *
 */

#समावेश <linux/dmi.h>
#समावेश <linux/efi.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/preempt.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/pgभाग.स>

अटल bool __init efi_virपंचांगap_init(व्योम)
अणु
	efi_memory_desc_t *md;

	efi_mm.pgd = pgd_alloc(&efi_mm);
	mm_init_cpumask(&efi_mm);
	init_new_context(शून्य, &efi_mm);

	क्रम_each_efi_memory_desc(md) अणु
		phys_addr_t phys = md->phys_addr;
		पूर्णांक ret;

		अगर (!(md->attribute & EFI_MEMORY_RUNTIME))
			जारी;
		अगर (md->virt_addr == 0)
			वापस false;

		ret = efi_create_mapping(&efi_mm, md);
		अगर (ret) अणु
			pr_warn("  EFI remap %pa: failed to create mapping (%d)\n",
				&phys, ret);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (efi_memattr_apply_permissions(&efi_mm, efi_set_mapping_permissions))
		वापस false;

	वापस true;
पूर्ण

/*
 * Enable the UEFI Runसमय Services अगर all prerequisites are in place, i.e.,
 * non-early mapping of the UEFI प्रणाली table and भव mappings क्रम all
 * EFI_MEMORY_RUNTIME regions.
 */
अटल पूर्णांक __init riscv_enable_runसमय_services(व्योम)
अणु
	u64 mapsize;

	अगर (!efi_enabled(EFI_BOOT)) अणु
		pr_info("EFI services will not be available.\n");
		वापस 0;
	पूर्ण

	efi_memmap_unmap();

	mapsize = efi.memmap.desc_size * efi.memmap.nr_map;

	अगर (efi_memmap_init_late(efi.memmap.phys_map, mapsize)) अणु
		pr_err("Failed to remap EFI memory map\n");
		वापस 0;
	पूर्ण

	अगर (efi_soft_reserve_enabled()) अणु
		efi_memory_desc_t *md;

		क्रम_each_efi_memory_desc(md) अणु
			पूर्णांक md_size = md->num_pages << EFI_PAGE_SHIFT;
			काष्ठा resource *res;

			अगर (!(md->attribute & EFI_MEMORY_SP))
				जारी;

			res = kzalloc(माप(*res), GFP_KERNEL);
			अगर (WARN_ON(!res))
				अवरोध;

			res->start	= md->phys_addr;
			res->end	= md->phys_addr + md_size - 1;
			res->name	= "Soft Reserved";
			res->flags	= IORESOURCE_MEM;
			res->desc	= IORES_DESC_SOFT_RESERVED;

			insert_resource(&iomem_resource, res);
		पूर्ण
	पूर्ण

	अगर (efi_runसमय_disabled()) अणु
		pr_info("EFI runtime services will be disabled.\n");
		वापस 0;
	पूर्ण

	अगर (efi_enabled(EFI_RUNTIME_SERVICES)) अणु
		pr_info("EFI runtime services access via paravirt.\n");
		वापस 0;
	पूर्ण

	pr_info("Remapping and enabling EFI services.\n");

	अगर (!efi_virपंचांगap_init()) अणु
		pr_err("UEFI virtual mapping missing or invalid -- runtime services will not be available\n");
		वापस -ENOMEM;
	पूर्ण

	/* Set up runसमय services function poपूर्णांकers */
	efi_native_runसमय_setup();
	set_bit(EFI_RUNTIME_SERVICES, &efi.flags);

	वापस 0;
पूर्ण
early_initcall(riscv_enable_runसमय_services);

व्योम efi_virपंचांगap_load(व्योम)
अणु
	preempt_disable();
	चयन_mm(current->active_mm, &efi_mm, शून्य);
पूर्ण

व्योम efi_virपंचांगap_unload(व्योम)
अणु
	चयन_mm(&efi_mm, current->active_mm, शून्य);
	preempt_enable();
पूर्ण
