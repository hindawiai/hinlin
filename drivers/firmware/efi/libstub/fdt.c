<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FDT related Helper functions used by the EFI stub on multiple
 * architectures. This should be #समावेशd by the EFI stub
 * implementation files.
 *
 * Copyright 2013 Linaro Limited; author Roy Franz
 */

#समावेश <linux/efi.h>
#समावेश <linux/libfdt.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

#घोषणा EFI_DT_ADDR_CELLS_DEFAULT 2
#घोषणा EFI_DT_SIZE_CELLS_DEFAULT 2

अटल व्योम fdt_update_cell_size(व्योम *fdt)
अणु
	पूर्णांक offset;

	offset = fdt_path_offset(fdt, "/");
	/* Set the #address-cells and #size-cells values क्रम an empty tree */

	fdt_setprop_u32(fdt, offset, "#address-cells", EFI_DT_ADDR_CELLS_DEFAULT);
	fdt_setprop_u32(fdt, offset, "#size-cells",    EFI_DT_SIZE_CELLS_DEFAULT);
पूर्ण

अटल efi_status_t update_fdt(व्योम *orig_fdt, अचिन्हित दीर्घ orig_fdt_size,
			       व्योम *fdt, पूर्णांक new_fdt_size, अक्षर *cmdline_ptr,
			       u64 initrd_addr, u64 initrd_size)
अणु
	पूर्णांक node, num_rsv;
	पूर्णांक status;
	u32 fdt_val32;
	u64 fdt_val64;

	/* Do some checks on provided FDT, अगर it exists: */
	अगर (orig_fdt) अणु
		अगर (fdt_check_header(orig_fdt)) अणु
			efi_err("Device Tree header not valid!\n");
			वापस EFI_LOAD_ERROR;
		पूर्ण
		/*
		 * We करोn't get the size of the FDT अगर we get अगर from a
		 * configuration table:
		 */
		अगर (orig_fdt_size && fdt_totalsize(orig_fdt) > orig_fdt_size) अणु
			efi_err("Truncated device tree! foo!\n");
			वापस EFI_LOAD_ERROR;
		पूर्ण
	पूर्ण

	अगर (orig_fdt) अणु
		status = fdt_खोलो_पूर्णांकo(orig_fdt, fdt, new_fdt_size);
	पूर्ण अन्यथा अणु
		status = fdt_create_empty_tree(fdt, new_fdt_size);
		अगर (status == 0) अणु
			/*
			 * Any failure from the following function is
			 * non-critical:
			 */
			fdt_update_cell_size(fdt);
		पूर्ण
	पूर्ण

	अगर (status != 0)
		जाओ fdt_set_fail;

	/*
	 * Delete all memory reserve map entries. When booting via UEFI,
	 * kernel will use the UEFI memory map to find reserved regions.
	 */
	num_rsv = fdt_num_mem_rsv(fdt);
	जबतक (num_rsv-- > 0)
		fdt_del_mem_rsv(fdt, num_rsv);

	node = fdt_subnode_offset(fdt, 0, "chosen");
	अगर (node < 0) अणु
		node = fdt_add_subnode(fdt, 0, "chosen");
		अगर (node < 0) अणु
			/* 'node' is an error code when negative: */
			status = node;
			जाओ fdt_set_fail;
		पूर्ण
	पूर्ण

	अगर (cmdline_ptr != शून्य && म_माप(cmdline_ptr) > 0) अणु
		status = fdt_setprop(fdt, node, "bootargs", cmdline_ptr,
				     म_माप(cmdline_ptr) + 1);
		अगर (status)
			जाओ fdt_set_fail;
	पूर्ण

	/* Set initrd address/end in device tree, अगर present */
	अगर (initrd_size != 0) अणु
		u64 initrd_image_end;
		u64 initrd_image_start = cpu_to_fdt64(initrd_addr);

		status = fdt_setprop_var(fdt, node, "linux,initrd-start", initrd_image_start);
		अगर (status)
			जाओ fdt_set_fail;

		initrd_image_end = cpu_to_fdt64(initrd_addr + initrd_size);
		status = fdt_setprop_var(fdt, node, "linux,initrd-end", initrd_image_end);
		अगर (status)
			जाओ fdt_set_fail;
	पूर्ण

	/* Add FDT entries क्रम EFI runसमय services in chosen node. */
	node = fdt_subnode_offset(fdt, 0, "chosen");
	fdt_val64 = cpu_to_fdt64((u64)(अचिन्हित दीर्घ)efi_प्रणाली_table);

	status = fdt_setprop_var(fdt, node, "linux,uefi-system-table", fdt_val64);
	अगर (status)
		जाओ fdt_set_fail;

	fdt_val64 = U64_MAX; /* placeholder */

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-start", fdt_val64);
	अगर (status)
		जाओ fdt_set_fail;

	fdt_val32 = U32_MAX; /* placeholder */

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-size", fdt_val32);
	अगर (status)
		जाओ fdt_set_fail;

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-desc-size", fdt_val32);
	अगर (status)
		जाओ fdt_set_fail;

	status = fdt_setprop_var(fdt, node, "linux,uefi-mmap-desc-ver", fdt_val32);
	अगर (status)
		जाओ fdt_set_fail;

	अगर (IS_ENABLED(CONFIG_RANDOMIZE_BASE) && !efi_nokaslr) अणु
		efi_status_t efi_status;

		efi_status = efi_get_अक्रमom_bytes(माप(fdt_val64),
						  (u8 *)&fdt_val64);
		अगर (efi_status == EFI_SUCCESS) अणु
			status = fdt_setprop_var(fdt, node, "kaslr-seed", fdt_val64);
			अगर (status)
				जाओ fdt_set_fail;
		पूर्ण
	पूर्ण

	/* Shrink the FDT back to its minimum size: */
	fdt_pack(fdt);

	वापस EFI_SUCCESS;

fdt_set_fail:
	अगर (status == -FDT_ERR_NOSPACE)
		वापस EFI_BUFFER_TOO_SMALL;

	वापस EFI_LOAD_ERROR;
पूर्ण

अटल efi_status_t update_fdt_memmap(व्योम *fdt, काष्ठा efi_boot_memmap *map)
अणु
	पूर्णांक node = fdt_path_offset(fdt, "/chosen");
	u64 fdt_val64;
	u32 fdt_val32;
	पूर्णांक err;

	अगर (node < 0)
		वापस EFI_LOAD_ERROR;

	fdt_val64 = cpu_to_fdt64((अचिन्हित दीर्घ)*map->map);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-start", fdt_val64);
	अगर (err)
		वापस EFI_LOAD_ERROR;

	fdt_val32 = cpu_to_fdt32(*map->map_size);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-size", fdt_val32);
	अगर (err)
		वापस EFI_LOAD_ERROR;

	fdt_val32 = cpu_to_fdt32(*map->desc_size);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-desc-size", fdt_val32);
	अगर (err)
		वापस EFI_LOAD_ERROR;

	fdt_val32 = cpu_to_fdt32(*map->desc_ver);

	err = fdt_setprop_inplace_var(fdt, node, "linux,uefi-mmap-desc-ver", fdt_val32);
	अगर (err)
		वापस EFI_LOAD_ERROR;

	वापस EFI_SUCCESS;
पूर्ण

काष्ठा निकास_boot_काष्ठा अणु
	efi_memory_desc_t	*runसमय_map;
	पूर्णांक			*runसमय_entry_count;
	व्योम			*new_fdt_addr;
पूर्ण;

अटल efi_status_t निकास_boot_func(काष्ठा efi_boot_memmap *map,
				   व्योम *priv)
अणु
	काष्ठा निकास_boot_काष्ठा *p = priv;
	/*
	 * Update the memory map with भव addresses. The function will also
	 * populate @runसमय_map with copies of just the EFI_MEMORY_RUNTIME
	 * entries so that we can pass it straight to SetVirtualAddressMap()
	 */
	efi_get_virपंचांगap(*map->map, *map->map_size, *map->desc_size,
			p->runसमय_map, p->runसमय_entry_count);

	वापस update_fdt_memmap(p->new_fdt_addr, map);
पूर्ण

#अगर_अघोषित MAX_FDT_SIZE
# define MAX_FDT_SIZE SZ_2M
#पूर्ण_अगर

/*
 * Allocate memory क्रम a new FDT, then add EFI, commandline, and
 * initrd related fields to the FDT.  This routine increases the
 * FDT allocation size until the allocated memory is large
 * enough.  EFI allocations are in EFI_PAGE_SIZE granules,
 * which are fixed at 4K bytes, so in most हालs the first
 * allocation should succeed.
 * EFI boot services are निकासed at the end of this function.
 * There must be no allocations between the get_memory_map()
 * call and the निकास_boot_services() call, so the निकासing of
 * boot services is very tightly tied to the creation of the FDT
 * with the final memory map in it.
 */

efi_status_t allocate_new_fdt_and_निकास_boot(व्योम *handle,
					    अचिन्हित दीर्घ *new_fdt_addr,
					    u64 initrd_addr, u64 initrd_size,
					    अक्षर *cmdline_ptr,
					    अचिन्हित दीर्घ fdt_addr,
					    अचिन्हित दीर्घ fdt_size)
अणु
	अचिन्हित दीर्घ map_size, desc_size, buff_size;
	u32 desc_ver;
	अचिन्हित दीर्घ mmap_key;
	efi_memory_desc_t *memory_map, *runसमय_map;
	efi_status_t status;
	पूर्णांक runसमय_entry_count;
	काष्ठा efi_boot_memmap map;
	काष्ठा निकास_boot_काष्ठा priv;

	map.map		= &runसमय_map;
	map.map_size	= &map_size;
	map.desc_size	= &desc_size;
	map.desc_ver	= &desc_ver;
	map.key_ptr	= &mmap_key;
	map.buff_size	= &buff_size;

	/*
	 * Get a copy of the current memory map that we will use to prepare
	 * the input क्रम SetVirtualAddressMap(). We करोn't have to worry about
	 * subsequent allocations adding entries, since they could not affect
	 * the number of EFI_MEMORY_RUNTIME regions.
	 */
	status = efi_get_memory_map(&map);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Unable to retrieve UEFI memory map.\n");
		वापस status;
	पूर्ण

	efi_info("Exiting boot services and installing virtual address map...\n");

	map.map = &memory_map;
	status = efi_allocate_pages(MAX_FDT_SIZE, new_fdt_addr, अच_दीर्घ_उच्च);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Unable to allocate memory for new device tree.\n");
		जाओ fail;
	पूर्ण

	/*
	 * Now that we have करोne our final memory allocation (and मुक्त)
	 * we can get the memory map key needed क्रम निकास_boot_services().
	 */
	status = efi_get_memory_map(&map);
	अगर (status != EFI_SUCCESS)
		जाओ fail_मुक्त_new_fdt;

	status = update_fdt((व्योम *)fdt_addr, fdt_size,
			    (व्योम *)*new_fdt_addr, MAX_FDT_SIZE, cmdline_ptr,
			    initrd_addr, initrd_size);

	अगर (status != EFI_SUCCESS) अणु
		efi_err("Unable to construct new device tree.\n");
		जाओ fail_मुक्त_new_fdt;
	पूर्ण

	runसमय_entry_count		= 0;
	priv.runसमय_map		= runसमय_map;
	priv.runसमय_entry_count	= &runसमय_entry_count;
	priv.new_fdt_addr		= (व्योम *)*new_fdt_addr;

	status = efi_निकास_boot_services(handle, &map, &priv, निकास_boot_func);

	अगर (status == EFI_SUCCESS) अणु
		efi_set_भव_address_map_t *svam;

		अगर (efi_novamap)
			वापस EFI_SUCCESS;

		/* Install the new भव address map */
		svam = efi_प्रणाली_table->runसमय->set_भव_address_map;
		status = svam(runसमय_entry_count * desc_size, desc_size,
			      desc_ver, runसमय_map);

		/*
		 * We are beyond the poपूर्णांक of no वापस here, so अगर the call to
		 * SetVirtualAddressMap() failed, we need to संकेत that to the
		 * incoming kernel but proceed normally otherwise.
		 */
		अगर (status != EFI_SUCCESS) अणु
			पूर्णांक l;

			/*
			 * Set the भव address field of all
			 * EFI_MEMORY_RUNTIME entries to 0. This will संकेत
			 * the incoming kernel that no भव translation has
			 * been installed.
			 */
			क्रम (l = 0; l < map_size; l += desc_size) अणु
				efi_memory_desc_t *p = (व्योम *)memory_map + l;

				अगर (p->attribute & EFI_MEMORY_RUNTIME)
					p->virt_addr = 0;
			पूर्ण
		पूर्ण
		वापस EFI_SUCCESS;
	पूर्ण

	efi_err("Exit boot services failed.\n");

fail_मुक्त_new_fdt:
	efi_मुक्त(MAX_FDT_SIZE, *new_fdt_addr);

fail:
	efi_प्रणाली_table->bootसमय->मुक्त_pool(runसमय_map);

	वापस EFI_LOAD_ERROR;
पूर्ण

व्योम *get_fdt(अचिन्हित दीर्घ *fdt_size)
अणु
	व्योम *fdt;

	fdt = get_efi_config_table(DEVICE_TREE_GUID);

	अगर (!fdt)
		वापस शून्य;

	अगर (fdt_check_header(fdt) != 0) अणु
		efi_err("Invalid header detected on UEFI supplied FDT, ignoring ...\n");
		वापस शून्य;
	पूर्ण
	*fdt_size = fdt_totalsize(fdt);
	वापस fdt;
पूर्ण
