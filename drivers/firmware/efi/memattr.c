<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#घोषणा pr_fmt(fmt)	"efi: memattr: " fmt

#समावेश <linux/efi.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/early_ioremap.h>

अटल पूर्णांक __initdata tbl_size;
अचिन्हित दीर्घ __ro_after_init efi_mem_attr_table = EFI_INVALID_TABLE_ADDR;

/*
 * Reserve the memory associated with the Memory Attributes configuration
 * table, अगर it exists.
 */
पूर्णांक __init efi_memattr_init(व्योम)
अणु
	efi_memory_attributes_table_t *tbl;

	अगर (efi_mem_attr_table == EFI_INVALID_TABLE_ADDR)
		वापस 0;

	tbl = early_memremap(efi_mem_attr_table, माप(*tbl));
	अगर (!tbl) अणु
		pr_err("Failed to map EFI Memory Attributes table @ 0x%lx\n",
		       efi_mem_attr_table);
		वापस -ENOMEM;
	पूर्ण

	अगर (tbl->version > 1) अणु
		pr_warn("Unexpected EFI Memory Attributes table version %d\n",
			tbl->version);
		जाओ unmap;
	पूर्ण

	tbl_size = माप(*tbl) + tbl->num_entries * tbl->desc_size;
	memblock_reserve(efi_mem_attr_table, tbl_size);
	set_bit(EFI_MEM_ATTR, &efi.flags);

unmap:
	early_memunmap(tbl, माप(*tbl));
	वापस 0;
पूर्ण

/*
 * Returns a copy @out of the UEFI memory descriptor @in अगर it is covered
 * entirely by a UEFI memory map entry with matching attributes. The भव
 * address of @out is set according to the matching entry that was found.
 */
अटल bool entry_is_valid(स्थिर efi_memory_desc_t *in, efi_memory_desc_t *out)
अणु
	u64 in_paddr = in->phys_addr;
	u64 in_size = in->num_pages << EFI_PAGE_SHIFT;
	efi_memory_desc_t *md;

	*out = *in;

	अगर (in->type != EFI_RUNTIME_SERVICES_CODE &&
	    in->type != EFI_RUNTIME_SERVICES_DATA) अणु
		pr_warn("Entry type should be RuntimeServiceCode/Data\n");
		वापस false;
	पूर्ण

	अगर (PAGE_SIZE > EFI_PAGE_SIZE &&
	    (!PAGE_ALIGNED(in->phys_addr) ||
	     !PAGE_ALIGNED(in->num_pages << EFI_PAGE_SHIFT))) अणु
		/*
		 * Since arm64 may execute with page sizes of up to 64 KB, the
		 * UEFI spec mandates that RunसमयServices memory regions must
		 * be 64 KB aligned. We need to validate this here since we will
		 * not be able to tighten permissions on such regions without
		 * affecting adjacent regions.
		 */
		pr_warn("Entry address region misaligned\n");
		वापस false;
	पूर्ण

	क्रम_each_efi_memory_desc(md) अणु
		u64 md_paddr = md->phys_addr;
		u64 md_size = md->num_pages << EFI_PAGE_SHIFT;

		अगर (!(md->attribute & EFI_MEMORY_RUNTIME))
			जारी;
		अगर (md->virt_addr == 0 && md->phys_addr != 0) अणु
			/* no भव mapping has been installed by the stub */
			अवरोध;
		पूर्ण

		अगर (md_paddr > in_paddr || (in_paddr - md_paddr) >= md_size)
			जारी;

		/*
		 * This entry covers the start of @in, check whether
		 * it covers the end as well.
		 */
		अगर (md_paddr + md_size < in_paddr + in_size) अणु
			pr_warn("Entry covers multiple EFI memory map regions\n");
			वापस false;
		पूर्ण

		अगर (md->type != in->type) अणु
			pr_warn("Entry type deviates from EFI memory map region type\n");
			वापस false;
		पूर्ण

		out->virt_addr = in_paddr + (md->virt_addr - md_paddr);

		वापस true;
	पूर्ण

	pr_warn("No matching entry found in the EFI memory map\n");
	वापस false;
पूर्ण

/*
 * To be called after the EFI page tables have been populated. If a memory
 * attributes table is available, its contents will be used to update the
 * mappings with tightened permissions as described by the table.
 * This requires the UEFI memory map to have alपढ़ोy been populated with
 * भव addresses.
 */
पूर्णांक __init efi_memattr_apply_permissions(काष्ठा mm_काष्ठा *mm,
					 efi_memattr_perm_setter fn)
अणु
	efi_memory_attributes_table_t *tbl;
	पूर्णांक i, ret;

	अगर (tbl_size <= माप(*tbl))
		वापस 0;

	/*
	 * We need the EFI memory map to be setup so we can use it to
	 * lookup the भव addresses of all entries in the  of EFI
	 * Memory Attributes table. If it isn't available, this
	 * function should not be called.
	 */
	अगर (WARN_ON(!efi_enabled(EFI_MEMMAP)))
		वापस 0;

	tbl = memremap(efi_mem_attr_table, tbl_size, MEMREMAP_WB);
	अगर (!tbl) अणु
		pr_err("Failed to map EFI Memory Attributes table @ 0x%lx\n",
		       efi_mem_attr_table);
		वापस -ENOMEM;
	पूर्ण

	अगर (efi_enabled(EFI_DBG))
		pr_info("Processing EFI Memory Attributes table:\n");

	क्रम (i = ret = 0; ret == 0 && i < tbl->num_entries; i++) अणु
		efi_memory_desc_t md;
		अचिन्हित दीर्घ size;
		bool valid;
		अक्षर buf[64];

		valid = entry_is_valid((व्योम *)tbl->entry + i * tbl->desc_size,
				       &md);
		size = md.num_pages << EFI_PAGE_SHIFT;
		अगर (efi_enabled(EFI_DBG) || !valid)
			pr_info("%s 0x%012llx-0x%012llx %s\n",
				valid ? "" : "!", md.phys_addr,
				md.phys_addr + size - 1,
				efi_md_typeattr_क्रमmat(buf, माप(buf), &md));

		अगर (valid) अणु
			ret = fn(mm, &md);
			अगर (ret)
				pr_err("Error updating mappings, skipping subsequent md's\n");
		पूर्ण
	पूर्ण
	memunmap(tbl);
	वापस ret;
पूर्ण
