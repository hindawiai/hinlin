<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * EFI stub implementation that is shared by arm and arm64 architectures.
 * This should be #समावेशd by the EFI stub implementation files.
 *
 * Copyright (C) 2013,2014 Linaro Limited
 *     Roy Franz <roy.franz@linaro.org
 * Copyright (C) 2013 Red Hat, Inc.
 *     Mark Salter <msalter@redhat.com>
 */

#समावेश <linux/efi.h>
#समावेश <linux/libfdt.h>
#समावेश <यंत्र/efi.h>

#समावेश "efistub.h"

/*
 * This is the base address at which to start allocating भव memory ranges
 * क्रम UEFI Runसमय Services.
 *
 * For ARM/ARM64:
 * This is in the low TTBR0 range so that we can use
 * any allocation we choose, and eliminate the risk of a conflict after kexec.
 * The value chosen is the largest non-zero घातer of 2 suitable क्रम this purpose
 * both on 32-bit and 64-bit ARM CPUs, to maximize the likelihood that it can
 * be mapped efficiently.
 * Since 32-bit ARM could potentially execute with a 1G/3G user/kernel split,
 * map everything below 1 GB. (512 MB is a reasonable upper bound क्रम the
 * entire footprपूर्णांक of the UEFI runसमय services memory regions)
 *
 * For RISC-V:
 * There is no specअगरic reason क्रम which, this address (512MB) can't be used
 * EFI runसमय भव address क्रम RISC-V. It also helps to use EFI runसमय
 * services on both RV32/RV64. Keep the same runसमय भव address क्रम RISC-V
 * as well to minimize the code churn.
 */
#घोषणा EFI_RT_VIRTUAL_BASE	SZ_512M
#घोषणा EFI_RT_VIRTUAL_SIZE	SZ_512M

#अगर_घोषित CONFIG_ARM64
# define EFI_RT_VIRTUAL_LIMIT	DEFAULT_MAP_WINDOW_64
#अन्यथा
# define EFI_RT_VIRTUAL_LIMIT	TASK_SIZE
#पूर्ण_अगर

अटल u64 virपंचांगap_base = EFI_RT_VIRTUAL_BASE;
अटल bool flat_va_mapping;

स्थिर efi_प्रणाली_table_t *efi_प्रणाली_table;

अटल काष्ठा screen_info *setup_graphics(व्योम)
अणु
	efi_guid_t gop_proto = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	efi_status_t status;
	अचिन्हित दीर्घ size;
	व्योम **gop_handle = शून्य;
	काष्ठा screen_info *si = शून्य;

	size = 0;
	status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL,
			     &gop_proto, शून्य, &size, gop_handle);
	अगर (status == EFI_BUFFER_TOO_SMALL) अणु
		si = alloc_screen_info();
		अगर (!si)
			वापस शून्य;
		status = efi_setup_gop(si, &gop_proto, size);
		अगर (status != EFI_SUCCESS) अणु
			मुक्त_screen_info(si);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस si;
पूर्ण

अटल व्योम install_memreserve_table(व्योम)
अणु
	काष्ठा linux_efi_memreserve *rsv;
	efi_guid_t memreserve_table_guid = LINUX_EFI_MEMRESERVE_TABLE_GUID;
	efi_status_t status;

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, माप(*rsv),
			     (व्योम **)&rsv);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to allocate memreserve entry!\n");
		वापस;
	पूर्ण

	rsv->next = 0;
	rsv->size = 0;
	atomic_set(&rsv->count, 0);

	status = efi_bs_call(install_configuration_table,
			     &memreserve_table_guid, rsv);
	अगर (status != EFI_SUCCESS)
		efi_err("Failed to install memreserve config table!\n");
पूर्ण

अटल u32 get_supported_rt_services(व्योम)
अणु
	स्थिर efi_rt_properties_table_t *rt_prop_table;
	u32 supported = EFI_RT_SUPPORTED_ALL;

	rt_prop_table = get_efi_config_table(EFI_RT_PROPERTIES_TABLE_GUID);
	अगर (rt_prop_table)
		supported &= rt_prop_table->runसमय_services_supported;

	वापस supported;
पूर्ण

/*
 * EFI entry poपूर्णांक क्रम the arm/arm64 EFI stubs.  This is the entrypoपूर्णांक
 * that is described in the PE/COFF header.  Most of the code is the same
 * क्रम both archictectures, with the arch-specअगरic code provided in the
 * handle_kernel_image() function.
 */
efi_status_t __efiapi efi_pe_entry(efi_handle_t handle,
				   efi_प्रणाली_table_t *sys_table_arg)
अणु
	efi_loaded_image_t *image;
	efi_status_t status;
	अचिन्हित दीर्घ image_addr;
	अचिन्हित दीर्घ image_size = 0;
	/* addr/poपूर्णांक and size pairs क्रम memory management*/
	अचिन्हित दीर्घ initrd_addr = 0;
	अचिन्हित दीर्घ initrd_size = 0;
	अचिन्हित दीर्घ fdt_addr = 0;  /* Original DTB */
	अचिन्हित दीर्घ fdt_size = 0;
	अक्षर *cmdline_ptr = शून्य;
	पूर्णांक cmdline_size = 0;
	efi_guid_t loaded_image_proto = LOADED_IMAGE_PROTOCOL_GUID;
	अचिन्हित दीर्घ reserve_addr = 0;
	अचिन्हित दीर्घ reserve_size = 0;
	क्रमागत efi_secureboot_mode secure_boot;
	काष्ठा screen_info *si;
	efi_properties_table_t *prop_tbl;
	अचिन्हित दीर्घ max_addr;

	efi_प्रणाली_table = sys_table_arg;

	/* Check अगर we were booted by the EFI firmware */
	अगर (efi_प्रणाली_table->hdr.signature != EFI_SYSTEM_TABLE_SIGNATURE) अणु
		status = EFI_INVALID_PARAMETER;
		जाओ fail;
	पूर्ण

	status = check_platक्रमm_features();
	अगर (status != EFI_SUCCESS)
		जाओ fail;

	/*
	 * Get a handle to the loaded image protocol.  This is used to get
	 * inक्रमmation about the running image, such as size and the command
	 * line.
	 */
	status = efi_प्रणाली_table->bootसमय->handle_protocol(handle,
					&loaded_image_proto, (व्योम *)&image);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to get loaded image protocol\n");
		जाओ fail;
	पूर्ण

	/*
	 * Get the command line from EFI, using the LOADED_IMAGE
	 * protocol. We are going to copy the command line पूर्णांकo the
	 * device tree, so this can be allocated anywhere.
	 */
	cmdline_ptr = efi_convert_cmdline(image, &cmdline_size);
	अगर (!cmdline_ptr) अणु
		efi_err("getting command line via LOADED_IMAGE_PROTOCOL\n");
		status = EFI_OUT_OF_RESOURCES;
		जाओ fail;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_CMDLINE_EXTEND) ||
	    IS_ENABLED(CONFIG_CMDLINE_FORCE) ||
	    cmdline_size == 0) अणु
		status = efi_parse_options(CONFIG_CMDLINE);
		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to parse options\n");
			जाओ fail_मुक्त_cmdline;
		पूर्ण
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_CMDLINE_FORCE) && cmdline_size > 0) अणु
		status = efi_parse_options(cmdline_ptr);
		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to parse options\n");
			जाओ fail_मुक्त_cmdline;
		पूर्ण
	पूर्ण

	efi_info("Booting Linux Kernel...\n");

	si = setup_graphics();

	status = handle_kernel_image(&image_addr, &image_size,
				     &reserve_addr,
				     &reserve_size,
				     image);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to relocate kernel\n");
		जाओ fail_मुक्त_screeninfo;
	पूर्ण

	efi_retrieve_tpm2_eventlog();

	/* Ask the firmware to clear memory on unclean shutकरोwn */
	efi_enable_reset_attack_mitigation();

	secure_boot = efi_get_secureboot();

	/*
	 * Unauthenticated device tree data is a security hazard, so ignore
	 * 'dtb=' unless UEFI Secure Boot is disabled.  We assume that secure
	 * boot is enabled अगर we can't determine its state.
	 */
	अगर (!IS_ENABLED(CONFIG_EFI_ARMSTUB_DTB_LOADER) ||
	     secure_boot != efi_secureboot_mode_disabled) अणु
		अगर (म_माला(cmdline_ptr, "dtb="))
			efi_err("Ignoring DTB from command line.\n");
	पूर्ण अन्यथा अणु
		status = efi_load_dtb(image, &fdt_addr, &fdt_size);

		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to load device tree!\n");
			जाओ fail_मुक्त_image;
		पूर्ण
	पूर्ण

	अगर (fdt_addr) अणु
		efi_info("Using DTB from command line\n");
	पूर्ण अन्यथा अणु
		/* Look क्रम a device tree configuration table entry. */
		fdt_addr = (uपूर्णांकptr_t)get_fdt(&fdt_size);
		अगर (fdt_addr)
			efi_info("Using DTB from configuration table\n");
	पूर्ण

	अगर (!fdt_addr)
		efi_info("Generating empty DTB\n");

	अगर (!efi_noinitrd) अणु
		max_addr = efi_get_max_initrd_addr(image_addr);
		status = efi_load_initrd(image, &initrd_addr, &initrd_size,
					 अच_दीर्घ_उच्च, max_addr);
		अगर (status != EFI_SUCCESS)
			efi_err("Failed to load initrd!\n");
	पूर्ण

	efi_अक्रमom_get_seed();

	/*
	 * If the NX PE data feature is enabled in the properties table, we
	 * should take care not to create a भव mapping that changes the
	 * relative placement of runसमय services code and data regions, as
	 * they may beदीर्घ to the same PE/COFF executable image in memory.
	 * The easiest way to achieve that is to simply use a 1:1 mapping.
	 */
	prop_tbl = get_efi_config_table(EFI_PROPERTIES_TABLE_GUID);
	flat_va_mapping = prop_tbl &&
			  (prop_tbl->memory_protection_attribute &
			   EFI_PROPERTIES_RUNTIME_MEMORY_PROTECTION_NON_EXECUTABLE_PE_DATA);

	/* क्रमce efi_novamap अगर SetVirtualAddressMap() is unsupported */
	efi_novamap |= !(get_supported_rt_services() &
			 EFI_RT_SUPPORTED_SET_VIRTUAL_ADDRESS_MAP);

	/* hibernation expects the runसमय regions to stay in the same place */
	अगर (!IS_ENABLED(CONFIG_HIBERNATION) && !efi_nokaslr && !flat_va_mapping) अणु
		/*
		 * Ranकरोmize the base of the UEFI runसमय services region.
		 * Preserve the 2 MB alignment of the region by taking a
		 * shअगरt of 21 bit positions पूर्णांकo account when scaling
		 * the headroom value using a 32-bit अक्रमom value.
		 */
		अटल स्थिर u64 headroom = EFI_RT_VIRTUAL_LIMIT -
					    EFI_RT_VIRTUAL_BASE -
					    EFI_RT_VIRTUAL_SIZE;
		u32 rnd;

		status = efi_get_अक्रमom_bytes(माप(rnd), (u8 *)&rnd);
		अगर (status == EFI_SUCCESS) अणु
			virपंचांगap_base = EFI_RT_VIRTUAL_BASE +
				       (((headroom >> 21) * rnd) >> (32 - 21));
		पूर्ण
	पूर्ण

	install_memreserve_table();

	status = allocate_new_fdt_and_निकास_boot(handle, &fdt_addr,
						initrd_addr, initrd_size,
						cmdline_ptr, fdt_addr, fdt_size);
	अगर (status != EFI_SUCCESS)
		जाओ fail_मुक्त_initrd;

	अगर (IS_ENABLED(CONFIG_ARM))
		efi_handle_post_ebs_state();

	efi_enter_kernel(image_addr, fdt_addr, fdt_totalsize((व्योम *)fdt_addr));
	/* not reached */

fail_मुक्त_initrd:
	efi_err("Failed to update FDT and exit boot services\n");

	efi_मुक्त(initrd_size, initrd_addr);
	efi_मुक्त(fdt_size, fdt_addr);

fail_मुक्त_image:
	efi_मुक्त(image_size, image_addr);
	efi_मुक्त(reserve_size, reserve_addr);
fail_मुक्त_screeninfo:
	मुक्त_screen_info(si);
fail_मुक्त_cmdline:
	efi_bs_call(मुक्त_pool, cmdline_ptr);
fail:
	वापस status;
पूर्ण

/*
 * efi_get_virपंचांगap() - create a भव mapping क्रम the EFI memory map
 *
 * This function populates the virt_addr fields of all memory region descriptors
 * in @memory_map whose EFI_MEMORY_RUNTIME attribute is set. Those descriptors
 * are also copied to @runसमय_map, and their total count is वापसed in @count.
 */
व्योम efi_get_virपंचांगap(efi_memory_desc_t *memory_map, अचिन्हित दीर्घ map_size,
		     अचिन्हित दीर्घ desc_size, efi_memory_desc_t *runसमय_map,
		     पूर्णांक *count)
अणु
	u64 efi_virt_base = virपंचांगap_base;
	efi_memory_desc_t *in, *out = runसमय_map;
	पूर्णांक l;

	क्रम (l = 0; l < map_size; l += desc_size) अणु
		u64 paddr, size;

		in = (व्योम *)memory_map + l;
		अगर (!(in->attribute & EFI_MEMORY_RUNTIME))
			जारी;

		paddr = in->phys_addr;
		size = in->num_pages * EFI_PAGE_SIZE;

		in->virt_addr = in->phys_addr;
		अगर (efi_novamap) अणु
			जारी;
		पूर्ण

		/*
		 * Make the mapping compatible with 64k pages: this allows
		 * a 4k page size kernel to kexec a 64k page size kernel and
		 * vice versa.
		 */
		अगर (!flat_va_mapping) अणु

			paddr = round_करोwn(in->phys_addr, SZ_64K);
			size += in->phys_addr - paddr;

			/*
			 * Aव्योम wasting memory on PTEs by choosing a भव
			 * base that is compatible with section mappings अगर this
			 * region has the appropriate size and physical
			 * alignment. (Sections are 2 MB on 4k granule kernels)
			 */
			अगर (IS_ALIGNED(in->phys_addr, SZ_2M) && size >= SZ_2M)
				efi_virt_base = round_up(efi_virt_base, SZ_2M);
			अन्यथा
				efi_virt_base = round_up(efi_virt_base, SZ_64K);

			in->virt_addr += efi_virt_base - paddr;
			efi_virt_base += size;
		पूर्ण

		स_नकल(out, in, desc_size);
		out = (व्योम *)out + desc_size;
		++*count;
	पूर्ण
पूर्ण
