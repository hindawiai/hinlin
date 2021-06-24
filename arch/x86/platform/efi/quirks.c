<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) "efi: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>
#समावेश <linux/efi.h>
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/reboot.h>

#घोषणा EFI_MIN_RESERVE 5120

#घोषणा EFI_DUMMY_GUID \
	EFI_GUID(0x4424ac57, 0xbe4b, 0x47dd, 0x9e, 0x97, 0xed, 0x50, 0xf0, 0x9f, 0x92, 0xa9)

#घोषणा QUARK_CSH_SIGNATURE		0x5f435348	/* _CSH */
#घोषणा QUARK_SECURITY_HEADER_SIZE	0x400

/*
 * Header prepended to the standard EFI capsule on Quark प्रणालीs the are based
 * on Intel firmware BSP.
 * @csh_signature:	Unique identअगरier to sanity check चिन्हित module
 * 			presence ("_CSH").
 * @version:		Current version of CSH used. Should be one क्रम Quark A0.
 * @modulesize:		Size of the entire module including the module header
 * 			and payload.
 * @security_version_number_index: Index of SVN to use क्रम validation of चिन्हित
 * 			module.
 * @security_version_number: Used to prevent against roll back of modules.
 * @rsvd_module_id:	Currently unused क्रम Clanton (Quark).
 * @rsvd_module_venकरोr:	Venकरोr Identअगरier. For Intel products value is
 * 			0x00008086.
 * @rsvd_date:		BCD representation of build date as yyyymmdd, where
 * 			yyyy=4 digit year, mm=1-12, dd=1-31.
 * @headersize:		Total length of the header including including any
 * 			padding optionally added by the signing tool.
 * @hash_algo:		What Hash is used in the module signing.
 * @cryp_algo:		What Crypto is used in the module signing.
 * @keysize:		Total length of the key data including including any
 * 			padding optionally added by the signing tool.
 * @signaturesize:	Total length of the signature including including any
 * 			padding optionally added by the signing tool.
 * @rsvd_next_header:	32-bit poपूर्णांकer to the next Secure Boot Module in the
 * 			chain, अगर there is a next header.
 * @rsvd:		Reserved, padding काष्ठाure to required size.
 *
 * See also QuartSecurityHeader_t in
 * Quark_EDKII_v1.2.1.1/QuarkPlatक्रमmPkg/Include/QuarkBootRom.h
 * from https://करोwnloadcenter.पूर्णांकel.com/करोwnload/23197/Intel-Quark-SoC-X1000-Board-Support-Package-BSP
 */
काष्ठा quark_security_header अणु
	u32 csh_signature;
	u32 version;
	u32 modulesize;
	u32 security_version_number_index;
	u32 security_version_number;
	u32 rsvd_module_id;
	u32 rsvd_module_venकरोr;
	u32 rsvd_date;
	u32 headersize;
	u32 hash_algo;
	u32 cryp_algo;
	u32 keysize;
	u32 signaturesize;
	u32 rsvd_next_header;
	u32 rsvd[2];
पूर्ण;

अटल स्थिर efi_अक्षर16_t efi_dummy_name[] = L"DUMMY";

अटल bool efi_no_storage_paranoia;

/*
 * Some firmware implementations refuse to boot अगर there's insufficient
 * space in the variable store. The implementation of garbage collection
 * in some FW versions causes stale (deleted) variables to take up space
 * दीर्घer than पूर्णांकended and space is only मुक्तd once the store becomes
 * almost completely full.
 *
 * Enabling this option disables the space checks in
 * efi_query_variable_store() and क्रमces garbage collection.
 *
 * Only enable this option अगर deleting EFI variables करोes not मुक्त up
 * space in your variable store, e.g. अगर despite deleting variables
 * you're unable to create new ones.
 */
अटल पूर्णांक __init setup_storage_paranoia(अक्षर *arg)
अणु
	efi_no_storage_paranoia = true;
	वापस 0;
पूर्ण
early_param("efi_no_storage_paranoia", setup_storage_paranoia);

/*
 * Deleting the dummy variable which kicks off garbage collection
*/
व्योम efi_delete_dummy_variable(व्योम)
अणु
	efi.set_variable_nonblocking((efi_अक्षर16_t *)efi_dummy_name,
				     &EFI_DUMMY_GUID,
				     EFI_VARIABLE_NON_VOLATILE |
				     EFI_VARIABLE_BOOTSERVICE_ACCESS |
				     EFI_VARIABLE_RUNTIME_ACCESS, 0, शून्य);
पूर्ण

/*
 * In the nonblocking हाल we करो not attempt to perक्रमm garbage
 * collection अगर we करो not have enough मुक्त space. Rather, we करो the
 * bare minimum check and give up immediately अगर the available space
 * is below EFI_MIN_RESERVE.
 *
 * This function is पूर्णांकended to be small and simple because it is
 * invoked from crash handler paths.
 */
अटल efi_status_t
query_variable_store_nonblocking(u32 attributes, अचिन्हित दीर्घ size)
अणु
	efi_status_t status;
	u64 storage_size, reमुख्यing_size, max_size;

	status = efi.query_variable_info_nonblocking(attributes, &storage_size,
						     &reमुख्यing_size,
						     &max_size);
	अगर (status != EFI_SUCCESS)
		वापस status;

	अगर (reमुख्यing_size - size < EFI_MIN_RESERVE)
		वापस EFI_OUT_OF_RESOURCES;

	वापस EFI_SUCCESS;
पूर्ण

/*
 * Some firmware implementations refuse to boot अगर there's insufficient space
 * in the variable store. Ensure that we never use more than a safe limit.
 *
 * Return EFI_SUCCESS अगर it is safe to ग_लिखो 'size' bytes to the variable
 * store.
 */
efi_status_t efi_query_variable_store(u32 attributes, अचिन्हित दीर्घ size,
				      bool nonblocking)
अणु
	efi_status_t status;
	u64 storage_size, reमुख्यing_size, max_size;

	अगर (!(attributes & EFI_VARIABLE_NON_VOLATILE))
		वापस 0;

	अगर (nonblocking)
		वापस query_variable_store_nonblocking(attributes, size);

	status = efi.query_variable_info(attributes, &storage_size,
					 &reमुख्यing_size, &max_size);
	अगर (status != EFI_SUCCESS)
		वापस status;

	/*
	 * We account क्रम that by refusing the ग_लिखो अगर permitting it would
	 * reduce the available space to under 5KB. This figure was provided by
	 * Samsung, so should be safe.
	 */
	अगर ((reमुख्यing_size - size < EFI_MIN_RESERVE) &&
		!efi_no_storage_paranoia) अणु

		/*
		 * Triggering garbage collection may require that the firmware
		 * generate a real EFI_OUT_OF_RESOURCES error. We can क्रमce
		 * that by attempting to use more space than is available.
		 */
		अचिन्हित दीर्घ dummy_size = reमुख्यing_size + 1024;
		व्योम *dummy = kzalloc(dummy_size, GFP_KERNEL);

		अगर (!dummy)
			वापस EFI_OUT_OF_RESOURCES;

		status = efi.set_variable((efi_अक्षर16_t *)efi_dummy_name,
					  &EFI_DUMMY_GUID,
					  EFI_VARIABLE_NON_VOLATILE |
					  EFI_VARIABLE_BOOTSERVICE_ACCESS |
					  EFI_VARIABLE_RUNTIME_ACCESS,
					  dummy_size, dummy);

		अगर (status == EFI_SUCCESS) अणु
			/*
			 * This should have failed, so अगर it didn't make sure
			 * that we delete it...
			 */
			efi_delete_dummy_variable();
		पूर्ण

		kमुक्त(dummy);

		/*
		 * The runसमय code may now have triggered a garbage collection
		 * run, so check the variable info again
		 */
		status = efi.query_variable_info(attributes, &storage_size,
						 &reमुख्यing_size, &max_size);

		अगर (status != EFI_SUCCESS)
			वापस status;

		/*
		 * There still isn't enough room, so वापस an error
		 */
		अगर (reमुख्यing_size - size < EFI_MIN_RESERVE)
			वापस EFI_OUT_OF_RESOURCES;
	पूर्ण

	वापस EFI_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(efi_query_variable_store);

/*
 * The UEFI specअगरication makes it clear that the operating प्रणाली is
 * मुक्त to करो whatever it wants with boot services code after
 * ExitBootServices() has been called. Ignoring this recommendation a
 * signअगरicant bunch of EFI implementations जारी calling पूर्णांकo boot
 * services code (SetVirtualAddressMap). In order to work around such
 * buggy implementations we reserve boot services region during EFI
 * init and make sure it stays executable. Then, after
 * SetVirtualAddressMap(), it is discarded.
 *
 * However, some boot services regions contain data that is required
 * by drivers, so we need to track which memory ranges can never be
 * मुक्तd. This is करोne by tagging those regions with the
 * EFI_MEMORY_RUNTIME attribute.
 *
 * Any driver that wants to mark a region as reserved must use
 * efi_mem_reserve() which will insert a new EFI memory descriptor
 * पूर्णांकo efi.memmap (splitting existing regions अगर necessary) and tag
 * it with EFI_MEMORY_RUNTIME.
 */
व्योम __init efi_arch_mem_reserve(phys_addr_t addr, u64 size)
अणु
	काष्ठा efi_memory_map_data data = अणु 0 पूर्ण;
	काष्ठा efi_mem_range mr;
	efi_memory_desc_t md;
	पूर्णांक num_entries;
	व्योम *new;

	अगर (efi_mem_desc_lookup(addr, &md) ||
	    md.type != EFI_BOOT_SERVICES_DATA) अणु
		pr_err("Failed to lookup EFI memory descriptor for %pa\n", &addr);
		वापस;
	पूर्ण

	अगर (addr + size > md.phys_addr + (md.num_pages << EFI_PAGE_SHIFT)) अणु
		pr_err("Region spans EFI memory descriptors, %pa\n", &addr);
		वापस;
	पूर्ण

	size += addr % EFI_PAGE_SIZE;
	size = round_up(size, EFI_PAGE_SIZE);
	addr = round_करोwn(addr, EFI_PAGE_SIZE);

	mr.range.start = addr;
	mr.range.end = addr + size - 1;
	mr.attribute = md.attribute | EFI_MEMORY_RUNTIME;

	num_entries = efi_memmap_split_count(&md, &mr.range);
	num_entries += efi.memmap.nr_map;

	अगर (efi_memmap_alloc(num_entries, &data) != 0) अणु
		pr_err("Could not allocate boot services memmap\n");
		वापस;
	पूर्ण

	new = early_memremap(data.phys_map, data.size);
	अगर (!new) अणु
		pr_err("Failed to map new boot services memmap\n");
		वापस;
	पूर्ण

	efi_memmap_insert(&efi.memmap, new, &mr);
	early_memunmap(new, data.size);

	efi_memmap_install(&data);
	e820__range_update(addr, size, E820_TYPE_RAM, E820_TYPE_RESERVED);
	e820__update_table(e820_table);
पूर्ण

/*
 * Helper function क्रम efi_reserve_boot_services() to figure out अगर we
 * can मुक्त regions in efi_मुक्त_boot_services().
 *
 * Use this function to ensure we करो not मुक्त regions owned by somebody
 * अन्यथा. We must only reserve (and then मुक्त) regions:
 *
 * - Not within any part of the kernel
 * - Not the BIOS reserved area (E820_TYPE_RESERVED, E820_TYPE_NVS, etc)
 */
अटल __init bool can_मुक्त_region(u64 start, u64 size)
अणु
	अगर (start + size > __pa_symbol(_text) && start <= __pa_symbol(_end))
		वापस false;

	अगर (!e820__mapped_all(start, start+size, E820_TYPE_RAM))
		वापस false;

	वापस true;
पूर्ण

व्योम __init efi_reserve_boot_services(व्योम)
अणु
	efi_memory_desc_t *md;

	अगर (!efi_enabled(EFI_MEMMAP))
		वापस;

	क्रम_each_efi_memory_desc(md) अणु
		u64 start = md->phys_addr;
		u64 size = md->num_pages << EFI_PAGE_SHIFT;
		bool alपढ़ोy_reserved;

		अगर (md->type != EFI_BOOT_SERVICES_CODE &&
		    md->type != EFI_BOOT_SERVICES_DATA)
			जारी;

		alपढ़ोy_reserved = memblock_is_region_reserved(start, size);

		/*
		 * Because the following memblock_reserve() is paired
		 * with memblock_मुक्त_late() क्रम this region in
		 * efi_मुक्त_boot_services(), we must be extremely
		 * careful not to reserve, and subsequently मुक्त,
		 * critical regions of memory (like the kernel image) or
		 * those regions that somebody अन्यथा has alपढ़ोy
		 * reserved.
		 *
		 * A good example of a critical region that must not be
		 * मुक्तd is page zero (first 4Kb of memory), which may
		 * contain boot services code/data but is marked
		 * E820_TYPE_RESERVED by trim_bios_range().
		 */
		अगर (!alपढ़ोy_reserved) अणु
			memblock_reserve(start, size);

			/*
			 * If we are the first to reserve the region, no
			 * one अन्यथा cares about it. We own it and can
			 * मुक्त it later.
			 */
			अगर (can_मुक्त_region(start, size))
				जारी;
		पूर्ण

		/*
		 * We करोn't own the region. We must not मुक्त it.
		 *
		 * Setting this bit क्रम a boot services region really
		 * करोesn't make sense as far as the firmware is
		 * concerned, but it करोes provide us with a way to tag
		 * those regions that must not be paired with
		 * memblock_मुक्त_late().
		 */
		md->attribute |= EFI_MEMORY_RUNTIME;
	पूर्ण
पूर्ण

/*
 * Apart from having VA mappings क्रम EFI boot services code/data regions,
 * (duplicate) 1:1 mappings were also created as a quirk क्रम buggy firmware. So,
 * unmap both 1:1 and VA mappings.
 */
अटल व्योम __init efi_unmap_pages(efi_memory_desc_t *md)
अणु
	pgd_t *pgd = efi_mm.pgd;
	u64 pa = md->phys_addr;
	u64 va = md->virt_addr;

	/*
	 * EFI mixed mode has all RAM mapped to access arguments जबतक making
	 * EFI runसमय calls, hence करोn't unmap EFI boot services code/data
	 * regions.
	 */
	अगर (efi_is_mixed())
		वापस;

	अगर (kernel_unmap_pages_in_pgd(pgd, pa, md->num_pages))
		pr_err("Failed to unmap 1:1 mapping for 0x%llx\n", pa);

	अगर (kernel_unmap_pages_in_pgd(pgd, va, md->num_pages))
		pr_err("Failed to unmap VA mapping for 0x%llx\n", va);
पूर्ण

व्योम __init efi_मुक्त_boot_services(व्योम)
अणु
	काष्ठा efi_memory_map_data data = अणु 0 पूर्ण;
	efi_memory_desc_t *md;
	पूर्णांक num_entries = 0;
	व्योम *new, *new_md;

	/* Keep all regions क्रम /sys/kernel/debug/efi */
	अगर (efi_enabled(EFI_DBG))
		वापस;

	क्रम_each_efi_memory_desc(md) अणु
		अचिन्हित दीर्घ दीर्घ start = md->phys_addr;
		अचिन्हित दीर्घ दीर्घ size = md->num_pages << EFI_PAGE_SHIFT;
		माप_प्रकार rm_size;

		अगर (md->type != EFI_BOOT_SERVICES_CODE &&
		    md->type != EFI_BOOT_SERVICES_DATA) अणु
			num_entries++;
			जारी;
		पूर्ण

		/* Do not मुक्त, someone अन्यथा owns it: */
		अगर (md->attribute & EFI_MEMORY_RUNTIME) अणु
			num_entries++;
			जारी;
		पूर्ण

		/*
		 * Beक्रमe calling set_भव_address_map(), EFI boot services
		 * code/data regions were mapped as a quirk क्रम buggy firmware.
		 * Unmap them from efi_pgd beक्रमe मुक्तing them up.
		 */
		efi_unmap_pages(md);

		/*
		 * Nasty quirk: अगर all sub-1MB memory is used क्रम boot
		 * services, we can get here without having allocated the
		 * real mode trampoline.  It's too late to hand boot services
		 * memory back to the memblock allocator, so instead
		 * try to manually allocate the trampoline अगर needed.
		 *
		 * I've seen this on a Dell XPS 13 9350 with firmware
		 * 1.4.4 with SGX enabled booting Linux via Feकरोra 24's
		 * grub2-efi on a hard disk.  (And no, I करोn't know why
		 * this happened, but Linux should still try to boot rather
		 * panicking early.)
		 */
		rm_size = real_mode_size_needed();
		अगर (rm_size && (start + rm_size) < (1<<20) && size >= rm_size) अणु
			set_real_mode_mem(start);
			start += rm_size;
			size -= rm_size;
		पूर्ण

		/*
		 * Don't मुक्त memory under 1M क्रम two reasons:
		 * - BIOS might clobber it
		 * - Crash kernel needs it to be reserved
		 */
		अगर (start + size < SZ_1M)
			जारी;
		अगर (start < SZ_1M) अणु
			size -= (SZ_1M - start);
			start = SZ_1M;
		पूर्ण

		memblock_मुक्त_late(start, size);
	पूर्ण

	अगर (!num_entries)
		वापस;

	अगर (efi_memmap_alloc(num_entries, &data) != 0) अणु
		pr_err("Failed to allocate new EFI memmap\n");
		वापस;
	पूर्ण

	new = memremap(data.phys_map, data.size, MEMREMAP_WB);
	अगर (!new) अणु
		pr_err("Failed to map new EFI memmap\n");
		वापस;
	पूर्ण

	/*
	 * Build a new EFI memmap that excludes any boot services
	 * regions that are not tagged EFI_MEMORY_RUNTIME, since those
	 * regions have now been मुक्तd.
	 */
	new_md = new;
	क्रम_each_efi_memory_desc(md) अणु
		अगर (!(md->attribute & EFI_MEMORY_RUNTIME) &&
		    (md->type == EFI_BOOT_SERVICES_CODE ||
		     md->type == EFI_BOOT_SERVICES_DATA))
			जारी;

		स_नकल(new_md, md, efi.memmap.desc_size);
		new_md += efi.memmap.desc_size;
	पूर्ण

	memunmap(new);

	अगर (efi_memmap_install(&data) != 0) अणु
		pr_err("Could not install new EFI memmap\n");
		वापस;
	पूर्ण
पूर्ण

/*
 * A number of config table entries get remapped to भव addresses
 * after entering EFI भव mode. However, the kexec kernel requires
 * their physical addresses thereक्रमe we pass them via setup_data and
 * correct those entries to their respective physical addresses here.
 *
 * Currently only handles smbios which is necessary क्रम some firmware
 * implementation.
 */
पूर्णांक __init efi_reuse_config(u64 tables, पूर्णांक nr_tables)
अणु
	पूर्णांक i, sz, ret = 0;
	व्योम *p, *tablep;
	काष्ठा efi_setup_data *data;

	अगर (nr_tables == 0)
		वापस 0;

	अगर (!efi_setup)
		वापस 0;

	अगर (!efi_enabled(EFI_64BIT))
		वापस 0;

	data = early_memremap(efi_setup, माप(*data));
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!data->smbios)
		जाओ out_memremap;

	sz = माप(efi_config_table_64_t);

	p = tablep = early_memremap(tables, nr_tables * sz);
	अगर (!p) अणु
		pr_err("Could not map Configuration table!\n");
		ret = -ENOMEM;
		जाओ out_memremap;
	पूर्ण

	क्रम (i = 0; i < nr_tables; i++) अणु
		efi_guid_t guid;

		guid = ((efi_config_table_64_t *)p)->guid;

		अगर (!efi_guidcmp(guid, SMBIOS_TABLE_GUID))
			((efi_config_table_64_t *)p)->table = data->smbios;
		p += sz;
	पूर्ण
	early_memunmap(tablep, nr_tables * sz);

out_memremap:
	early_memunmap(data, माप(*data));
out:
	वापस ret;
पूर्ण

व्योम __init efi_apply_memmap_quirks(व्योम)
अणु
	/*
	 * Once setup is करोne earlier, unmap the EFI memory map on mismatched
	 * firmware/kernel architectures since there is no support क्रम runसमय
	 * services.
	 */
	अगर (!efi_runसमय_supported()) अणु
		pr_info("Setup done, disabling due to 32/64-bit mismatch\n");
		efi_memmap_unmap();
	पूर्ण
पूर्ण

/*
 * For most modern platक्रमms the preferred method of घातering off is via
 * ACPI. However, there are some that are known to require the use of
 * EFI runसमय services and क्रम which ACPI करोes not work at all.
 *
 * Using EFI is a last resort, to be used only अगर no other option
 * exists.
 */
bool efi_reboot_required(व्योम)
अणु
	अगर (!acpi_gbl_reduced_hardware)
		वापस false;

	efi_reboot_quirk_mode = EFI_RESET_WARM;
	वापस true;
पूर्ण

bool efi_घातeroff_required(व्योम)
अणु
	वापस acpi_gbl_reduced_hardware || acpi_no_s5;
पूर्ण

#अगर_घोषित CONFIG_EFI_CAPSULE_QUIRK_QUARK_CSH

अटल पूर्णांक qrk_capsule_setup_info(काष्ठा capsule_info *cap_info, व्योम **pkbuff,
				  माप_प्रकार hdr_bytes)
अणु
	काष्ठा quark_security_header *csh = *pkbuff;

	/* Only process data block that is larger than the security header */
	अगर (hdr_bytes < माप(काष्ठा quark_security_header))
		वापस 0;

	अगर (csh->csh_signature != QUARK_CSH_SIGNATURE ||
	    csh->headersize != QUARK_SECURITY_HEADER_SIZE)
		वापस 1;

	/* Only process data block अगर EFI header is included */
	अगर (hdr_bytes < QUARK_SECURITY_HEADER_SIZE +
			माप(efi_capsule_header_t))
		वापस 0;

	pr_debug("Quark security header detected\n");

	अगर (csh->rsvd_next_header != 0) अणु
		pr_err("multiple Quark security headers not supported\n");
		वापस -EINVAL;
	पूर्ण

	*pkbuff += csh->headersize;
	cap_info->total_size = csh->headersize;

	/*
	 * Update the first page poपूर्णांकer to skip over the CSH header.
	 */
	cap_info->phys[0] += csh->headersize;

	/*
	 * cap_info->capsule should poपूर्णांक at a भव mapping of the entire
	 * capsule, starting at the capsule header. Our image has the Quark
	 * security header prepended, so we cannot rely on the शेष vmap()
	 * mapping created by the generic capsule code.
	 * Given that the Quark firmware करोes not appear to care about the
	 * भव mapping, let's just poपूर्णांक cap_info->capsule at our copy
	 * of the capsule header.
	 */
	cap_info->capsule = &cap_info->header;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id efi_capsule_quirk_ids[] = अणु
	X86_MATCH_VENDOR_FAM_MODEL(INTEL, 5, INTEL_FAM5_QUARK_X1000,
				   &qrk_capsule_setup_info),
	अणु पूर्ण
पूर्ण;

पूर्णांक efi_capsule_setup_info(काष्ठा capsule_info *cap_info, व्योम *kbuff,
			   माप_प्रकार hdr_bytes)
अणु
	पूर्णांक (*quirk_handler)(काष्ठा capsule_info *, व्योम **, माप_प्रकार);
	स्थिर काष्ठा x86_cpu_id *id;
	पूर्णांक ret;

	अगर (hdr_bytes < माप(efi_capsule_header_t))
		वापस 0;

	cap_info->total_size = 0;

	id = x86_match_cpu(efi_capsule_quirk_ids);
	अगर (id) अणु
		/*
		 * The quirk handler is supposed to वापस
		 *  - a value > 0 अगर the setup should जारी, after advancing
		 *    kbuff as needed
		 *  - 0 अगर not enough hdr_bytes are available yet
		 *  - a negative error code otherwise
		 */
		quirk_handler = (typeof(quirk_handler))id->driver_data;
		ret = quirk_handler(cap_info, &kbuff, hdr_bytes);
		अगर (ret <= 0)
			वापस ret;
	पूर्ण

	स_नकल(&cap_info->header, kbuff, माप(cap_info->header));

	cap_info->total_size += cap_info->header.imagesize;

	वापस __efi_capsule_setup_info(cap_info);
पूर्ण

#पूर्ण_अगर

/*
 * If any access by any efi runसमय service causes a page fault, then,
 * 1. If it's efi_reset_प्रणाली(), reboot through BIOS.
 * 2. If any other efi runसमय service, then
 *    a. Return error status to the efi caller process.
 *    b. Disable EFI Runसमय Services क्रमever and
 *    c. Freeze efi_rts_wq and schedule new process.
 *
 * @वापस: Returns, अगर the page fault is not handled. This function
 * will never वापस अगर the page fault is handled successfully.
 */
व्योम efi_crash_gracefully_on_page_fault(अचिन्हित दीर्घ phys_addr)
अणु
	अगर (!IS_ENABLED(CONFIG_X86_64))
		वापस;

	/*
	 * If we get an पूर्णांकerrupt/NMI जबतक processing an EFI runसमय service
	 * then this is a regular OOPS, not an EFI failure.
	 */
	अगर (in_पूर्णांकerrupt())
		वापस;

	/*
	 * Make sure that an efi runसमय service caused the page fault.
	 * READ_ONCE() because we might be OOPSing in a dअगरferent thपढ़ो,
	 * and we करोn't want to trip KTSAN जबतक trying to OOPS.
	 */
	अगर (READ_ONCE(efi_rts_work.efi_rts_id) == EFI_NONE ||
	    current_work() != &efi_rts_work.work)
		वापस;

	/*
	 * Address range 0x0000 - 0x0fff is always mapped in the efi_pgd, so
	 * page faulting on these addresses isn't expected.
	 */
	अगर (phys_addr <= 0x0fff)
		वापस;

	/*
	 * Prपूर्णांक stack trace as it might be useful to know which EFI Runसमय
	 * Service is buggy.
	 */
	WARN(1, FW_BUG "Page fault caused by firmware at PA: 0x%lx\n",
	     phys_addr);

	/*
	 * Buggy efi_reset_प्रणाली() is handled dअगरferently from other EFI
	 * Runसमय Services as it करोesn't use efi_rts_wq. Although,
	 * native_machine_emergency_restart() says that machine_real_restart()
	 * could fail, it's better not to complicate this fault handler
	 * because this हाल occurs *very* rarely and hence could be improved
	 * on a need by basis.
	 */
	अगर (efi_rts_work.efi_rts_id == EFI_RESET_SYSTEM) अणु
		pr_info("efi_reset_system() buggy! Reboot through BIOS\n");
		machine_real_restart(MRR_BIOS);
		वापस;
	पूर्ण

	/*
	 * Beक्रमe calling EFI Runसमय Service, the kernel has चयनed the
	 * calling process to efi_mm. Hence, चयन back to task_mm.
	 */
	arch_efi_call_virt_tearकरोwn();

	/* Signal error status to the efi caller process */
	efi_rts_work.status = EFI_ABORTED;
	complete(&efi_rts_work.efi_rts_comp);

	clear_bit(EFI_RUNTIME_SERVICES, &efi.flags);
	pr_info("Froze efi_rts_wq and disabled EFI Runtime Services\n");

	/*
	 * Call schedule() in an infinite loop, so that any spurious wake ups
	 * will never run efi_rts_wq again.
	 */
	क्रम (;;) अणु
		set_current_state(TASK_IDLE);
		schedule();
	पूर्ण
पूर्ण
