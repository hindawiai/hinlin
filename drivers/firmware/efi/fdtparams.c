<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#घोषणा pr_fmt(fmt) "efi: " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/efi.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/of_fdt.h>

#समावेश <यंत्र/unaligned.h>

क्रमागत अणु
	SYSTAB,
	MMBASE,
	MMSIZE,
	DCSIZE,
	DCVERS,

	PARAMCOUNT
पूर्ण;

अटल __initस्थिर स्थिर अक्षर name[][22] = अणु
	[SYSTAB] = "System Table         ",
	[MMBASE] = "MemMap Address       ",
	[MMSIZE] = "MemMap Size          ",
	[DCSIZE] = "MemMap Desc. Size    ",
	[DCVERS] = "MemMap Desc. Version ",
पूर्ण;

अटल __initस्थिर स्थिर काष्ठा अणु
	स्थिर अक्षर	path[17];
	स्थिर अक्षर	params[PARAMCOUNT][26];
पूर्ण dt_params[] = अणु
	अणु
#अगर_घोषित CONFIG_XEN    //  <-------17------>
		.path = "/hypervisor/uefi",
		.params = अणु
			[SYSTAB] = "xen,uefi-system-table",
			[MMBASE] = "xen,uefi-mmap-start",
			[MMSIZE] = "xen,uefi-mmap-size",
			[DCSIZE] = "xen,uefi-mmap-desc-size",
			[DCVERS] = "xen,uefi-mmap-desc-ver",
		पूर्ण
	पूर्ण, अणु
#पूर्ण_अगर
		.path = "/chosen",
		.params = अणु	//  <-----------26----------->
			[SYSTAB] = "linux,uefi-system-table",
			[MMBASE] = "linux,uefi-mmap-start",
			[MMSIZE] = "linux,uefi-mmap-size",
			[DCSIZE] = "linux,uefi-mmap-desc-size",
			[DCVERS] = "linux,uefi-mmap-desc-ver",
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक __init efi_get_fdt_prop(स्थिर व्योम *fdt, पूर्णांक node, स्थिर अक्षर *pname,
				   स्थिर अक्षर *rname, व्योम *var, पूर्णांक size)
अणु
	स्थिर व्योम *prop;
	पूर्णांक len;
	u64 val;

	prop = fdt_getprop(fdt, node, pname, &len);
	अगर (!prop)
		वापस 1;

	val = (len == 4) ? (u64)be32_to_cpup(prop) : get_unaligned_be64(prop);

	अगर (size == 8)
		*(u64 *)var = val;
	अन्यथा
		*(u32 *)var = (val < U32_MAX) ? val : U32_MAX; // saturate

	अगर (efi_enabled(EFI_DBG))
		pr_info("  %s: 0x%0*llx\n", rname, size * 2, val);

	वापस 0;
पूर्ण

u64 __init efi_get_fdt_params(काष्ठा efi_memory_map_data *mm)
अणु
	स्थिर व्योम *fdt = initial_boot_params;
	अचिन्हित दीर्घ systab;
	पूर्णांक i, j, node;
	काष्ठा अणु
		व्योम	*var;
		पूर्णांक	size;
	पूर्ण target[] = अणु
		[SYSTAB] = अणु &systab,		माप(systab) पूर्ण,
		[MMBASE] = अणु &mm->phys_map,	माप(mm->phys_map) पूर्ण,
		[MMSIZE] = अणु &mm->size,		माप(mm->size) पूर्ण,
		[DCSIZE] = अणु &mm->desc_size,	माप(mm->desc_size) पूर्ण,
		[DCVERS] = अणु &mm->desc_version,	माप(mm->desc_version) पूर्ण,
	पूर्ण;

	BUILD_BUG_ON(ARRAY_SIZE(target) != ARRAY_SIZE(name));
	BUILD_BUG_ON(ARRAY_SIZE(target) != ARRAY_SIZE(dt_params[0].params));

	अगर (!fdt)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(dt_params); i++) अणु
		node = fdt_path_offset(fdt, dt_params[i].path);
		अगर (node < 0)
			जारी;

		अगर (efi_enabled(EFI_DBG))
			pr_info("Getting UEFI parameters from %s in DT:\n",
				dt_params[i].path);

		क्रम (j = 0; j < ARRAY_SIZE(target); j++) अणु
			स्थिर अक्षर *pname = dt_params[i].params[j];

			अगर (!efi_get_fdt_prop(fdt, node, pname, name[j],
					      target[j].var, target[j].size))
				जारी;
			अगर (!j)
				जाओ notfound;
			pr_err("Can't find property '%s' in DT!\n", pname);
			वापस 0;
		पूर्ण
		वापस systab;
	पूर्ण
notfound:
	pr_info("UEFI not found.\n");
	वापस 0;
पूर्ण
