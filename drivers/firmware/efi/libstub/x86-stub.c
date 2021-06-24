<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/* -----------------------------------------------------------------------
 *
 *   Copyright 2011 Intel Corporation; author Matt Fleming
 *
 * ----------------------------------------------------------------------- */

#समावेश <linux/efi.h>
#समावेश <linux/pci.h>
#समावेश <linux/मानकघोष.स>

#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/e820/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/boot.h>

#समावेश "efistub.h"

/* Maximum physical address क्रम 64-bit kernel with 4-level paging */
#घोषणा MAXMEM_X86_64_4LEVEL (1ull << 46)

स्थिर efi_प्रणाली_table_t *efi_प्रणाली_table;
बाह्य u32 image_offset;
अटल efi_loaded_image_t *image = शून्य;

अटल efi_status_t
preserve_pci_rom_image(efi_pci_io_protocol_t *pci, काष्ठा pci_setup_rom **__rom)
अणु
	काष्ठा pci_setup_rom *rom = शून्य;
	efi_status_t status;
	अचिन्हित दीर्घ size;
	uपूर्णांक64_t romsize;
	व्योम *romimage;

	/*
	 * Some firmware images contain EFI function poपूर्णांकers at the place where
	 * the romimage and romsize fields are supposed to be. Typically the EFI
	 * code is mapped at high addresses, translating to an unrealistically
	 * large romsize. The UEFI spec limits the size of option ROMs to 16
	 * MiB so we reject any ROMs over 16 MiB in size to catch this.
	 */
	romimage = efi_table_attr(pci, romimage);
	romsize = efi_table_attr(pci, romsize);
	अगर (!romimage || !romsize || romsize > SZ_16M)
		वापस EFI_INVALID_PARAMETER;

	size = romsize + माप(*rom);

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, size,
			     (व्योम **)&rom);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to allocate memory for 'rom'\n");
		वापस status;
	पूर्ण

	स_रखो(rom, 0, माप(*rom));

	rom->data.type	= SETUP_PCI;
	rom->data.len	= size - माप(काष्ठा setup_data);
	rom->data.next	= 0;
	rom->pcilen	= pci->romsize;
	*__rom = rom;

	status = efi_call_proto(pci, pci.पढ़ो, EfiPciIoWidthUपूर्णांक16,
				PCI_VENDOR_ID, 1, &rom->venकरोr);

	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to read rom->vendor\n");
		जाओ मुक्त_काष्ठा;
	पूर्ण

	status = efi_call_proto(pci, pci.पढ़ो, EfiPciIoWidthUपूर्णांक16,
				PCI_DEVICE_ID, 1, &rom->devid);

	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to read rom->devid\n");
		जाओ मुक्त_काष्ठा;
	पूर्ण

	status = efi_call_proto(pci, get_location, &rom->segment, &rom->bus,
				&rom->device, &rom->function);

	अगर (status != EFI_SUCCESS)
		जाओ मुक्त_काष्ठा;

	स_नकल(rom->romdata, romimage, romsize);
	वापस status;

मुक्त_काष्ठा:
	efi_bs_call(मुक्त_pool, rom);
	वापस status;
पूर्ण

/*
 * There's no way to वापस an inक्रमmative status from this function,
 * because any analysis (and prपूर्णांकing of error messages) needs to be
 * करोne directly at the EFI function call-site.
 *
 * For example, EFI_INVALID_PARAMETER could indicate a bug or maybe we
 * just didn't find any PCI devices, but there's no way to tell outside
 * the context of the call.
 */
अटल व्योम setup_efi_pci(काष्ठा boot_params *params)
अणु
	efi_status_t status;
	व्योम **pci_handle = शून्य;
	efi_guid_t pci_proto = EFI_PCI_IO_PROTOCOL_GUID;
	अचिन्हित दीर्घ size = 0;
	काष्ठा setup_data *data;
	efi_handle_t h;
	पूर्णांक i;

	status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL,
			     &pci_proto, शून्य, &size, pci_handle);

	अगर (status == EFI_BUFFER_TOO_SMALL) अणु
		status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, size,
				     (व्योम **)&pci_handle);

		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to allocate memory for 'pci_handle'\n");
			वापस;
		पूर्ण

		status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL,
				     &pci_proto, शून्य, &size, pci_handle);
	पूर्ण

	अगर (status != EFI_SUCCESS)
		जाओ मुक्त_handle;

	data = (काष्ठा setup_data *)(अचिन्हित दीर्घ)params->hdr.setup_data;

	जबतक (data && data->next)
		data = (काष्ठा setup_data *)(अचिन्हित दीर्घ)data->next;

	क्रम_each_efi_handle(h, pci_handle, size, i) अणु
		efi_pci_io_protocol_t *pci = शून्य;
		काष्ठा pci_setup_rom *rom;

		status = efi_bs_call(handle_protocol, h, &pci_proto,
				     (व्योम **)&pci);
		अगर (status != EFI_SUCCESS || !pci)
			जारी;

		status = preserve_pci_rom_image(pci, &rom);
		अगर (status != EFI_SUCCESS)
			जारी;

		अगर (data)
			data->next = (अचिन्हित दीर्घ)rom;
		अन्यथा
			params->hdr.setup_data = (अचिन्हित दीर्घ)rom;

		data = (काष्ठा setup_data *)rom;
	पूर्ण

मुक्त_handle:
	efi_bs_call(मुक्त_pool, pci_handle);
पूर्ण

अटल व्योम retrieve_apple_device_properties(काष्ठा boot_params *boot_params)
अणु
	efi_guid_t guid = APPLE_PROPERTIES_PROTOCOL_GUID;
	काष्ठा setup_data *data, *new;
	efi_status_t status;
	u32 size = 0;
	apple_properties_protocol_t *p;

	status = efi_bs_call(locate_protocol, &guid, शून्य, (व्योम **)&p);
	अगर (status != EFI_SUCCESS)
		वापस;

	अगर (efi_table_attr(p, version) != 0x10000) अणु
		efi_err("Unsupported properties proto version\n");
		वापस;
	पूर्ण

	efi_call_proto(p, get_all, शून्य, &size);
	अगर (!size)
		वापस;

	करो अणु
		status = efi_bs_call(allocate_pool, EFI_LOADER_DATA,
				     size + माप(काष्ठा setup_data),
				     (व्योम **)&new);
		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to allocate memory for 'properties'\n");
			वापस;
		पूर्ण

		status = efi_call_proto(p, get_all, new->data, &size);

		अगर (status == EFI_BUFFER_TOO_SMALL)
			efi_bs_call(मुक्त_pool, new);
	पूर्ण जबतक (status == EFI_BUFFER_TOO_SMALL);

	new->type = SETUP_APPLE_PROPERTIES;
	new->len  = size;
	new->next = 0;

	data = (काष्ठा setup_data *)(अचिन्हित दीर्घ)boot_params->hdr.setup_data;
	अगर (!data) अणु
		boot_params->hdr.setup_data = (अचिन्हित दीर्घ)new;
	पूर्ण अन्यथा अणु
		जबतक (data->next)
			data = (काष्ठा setup_data *)(अचिन्हित दीर्घ)data->next;
		data->next = (अचिन्हित दीर्घ)new;
	पूर्ण
पूर्ण

अटल स्थिर efi_अक्षर16_t apple[] = L"Apple";

अटल व्योम setup_quirks(काष्ठा boot_params *boot_params)
अणु
	efi_अक्षर16_t *fw_venकरोr = (efi_अक्षर16_t *)(अचिन्हित दीर्घ)
		efi_table_attr(efi_प्रणाली_table, fw_venकरोr);

	अगर (!स_भेद(fw_venकरोr, apple, माप(apple))) अणु
		अगर (IS_ENABLED(CONFIG_APPLE_PROPERTIES))
			retrieve_apple_device_properties(boot_params);
	पूर्ण
पूर्ण

/*
 * See अगर we have Universal Graphics Adapter (UGA) protocol
 */
अटल efi_status_t
setup_uga(काष्ठा screen_info *si, efi_guid_t *uga_proto, अचिन्हित दीर्घ size)
अणु
	efi_status_t status;
	u32 width, height;
	व्योम **uga_handle = शून्य;
	efi_uga_draw_protocol_t *uga = शून्य, *first_uga;
	efi_handle_t handle;
	पूर्णांक i;

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, size,
			     (व्योम **)&uga_handle);
	अगर (status != EFI_SUCCESS)
		वापस status;

	status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL,
			     uga_proto, शून्य, &size, uga_handle);
	अगर (status != EFI_SUCCESS)
		जाओ मुक्त_handle;

	height = 0;
	width = 0;

	first_uga = शून्य;
	क्रम_each_efi_handle(handle, uga_handle, size, i) अणु
		efi_guid_t pciio_proto = EFI_PCI_IO_PROTOCOL_GUID;
		u32 w, h, depth, refresh;
		व्योम *pciio;

		status = efi_bs_call(handle_protocol, handle, uga_proto,
				     (व्योम **)&uga);
		अगर (status != EFI_SUCCESS)
			जारी;

		pciio = शून्य;
		efi_bs_call(handle_protocol, handle, &pciio_proto, &pciio);

		status = efi_call_proto(uga, get_mode, &w, &h, &depth, &refresh);
		अगर (status == EFI_SUCCESS && (!first_uga || pciio)) अणु
			width = w;
			height = h;

			/*
			 * Once we've found a UGA supporting PCIIO,
			 * करोn't bother looking any further.
			 */
			अगर (pciio)
				अवरोध;

			first_uga = uga;
		पूर्ण
	पूर्ण

	अगर (!width && !height)
		जाओ मुक्त_handle;

	/* EFI framebuffer */
	si->orig_video_isVGA	= VIDEO_TYPE_EFI;

	si->lfb_depth		= 32;
	si->lfb_width		= width;
	si->lfb_height		= height;

	si->red_size		= 8;
	si->red_pos		= 16;
	si->green_size		= 8;
	si->green_pos		= 8;
	si->blue_size		= 8;
	si->blue_pos		= 0;
	si->rsvd_size		= 8;
	si->rsvd_pos		= 24;

मुक्त_handle:
	efi_bs_call(मुक्त_pool, uga_handle);

	वापस status;
पूर्ण

अटल व्योम setup_graphics(काष्ठा boot_params *boot_params)
अणु
	efi_guid_t graphics_proto = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	काष्ठा screen_info *si;
	efi_guid_t uga_proto = EFI_UGA_PROTOCOL_GUID;
	efi_status_t status;
	अचिन्हित दीर्घ size;
	व्योम **gop_handle = शून्य;
	व्योम **uga_handle = शून्य;

	si = &boot_params->screen_info;
	स_रखो(si, 0, माप(*si));

	size = 0;
	status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL,
			     &graphics_proto, शून्य, &size, gop_handle);
	अगर (status == EFI_BUFFER_TOO_SMALL)
		status = efi_setup_gop(si, &graphics_proto, size);

	अगर (status != EFI_SUCCESS) अणु
		size = 0;
		status = efi_bs_call(locate_handle, EFI_LOCATE_BY_PROTOCOL,
				     &uga_proto, शून्य, &size, uga_handle);
		अगर (status == EFI_BUFFER_TOO_SMALL)
			setup_uga(si, &uga_proto, size);
	पूर्ण
पूर्ण


अटल व्योम __noवापस efi_निकास(efi_handle_t handle, efi_status_t status)
अणु
	efi_bs_call(निकास, handle, status, 0, शून्य);
	क्रम(;;)
		यंत्र("hlt");
पूर्ण

व्योम startup_32(काष्ठा boot_params *boot_params);

व्योम __noवापस efi_stub_entry(efi_handle_t handle,
			       efi_प्रणाली_table_t *sys_table_arg,
			       काष्ठा boot_params *boot_params);

/*
 * Because the x86 boot code expects to be passed a boot_params we
 * need to create one ourselves (usually the bootloader would create
 * one क्रम us).
 */
efi_status_t __efiapi efi_pe_entry(efi_handle_t handle,
				   efi_प्रणाली_table_t *sys_table_arg)
अणु
	काष्ठा boot_params *boot_params;
	काष्ठा setup_header *hdr;
	व्योम *image_base;
	efi_guid_t proto = LOADED_IMAGE_PROTOCOL_GUID;
	पूर्णांक options_size = 0;
	efi_status_t status;
	अक्षर *cmdline_ptr;

	efi_प्रणाली_table = sys_table_arg;

	/* Check अगर we were booted by the EFI firmware */
	अगर (efi_प्रणाली_table->hdr.signature != EFI_SYSTEM_TABLE_SIGNATURE)
		efi_निकास(handle, EFI_INVALID_PARAMETER);

	status = efi_bs_call(handle_protocol, handle, &proto, (व्योम **)&image);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to get handle for LOADED_IMAGE_PROTOCOL\n");
		efi_निकास(handle, status);
	पूर्ण

	image_base = efi_table_attr(image, image_base);
	image_offset = (व्योम *)startup_32 - image_base;

	status = efi_allocate_pages(माप(काष्ठा boot_params),
				    (अचिन्हित दीर्घ *)&boot_params, अच_दीर्घ_उच्च);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to allocate lowmem for boot params\n");
		efi_निकास(handle, status);
	पूर्ण

	स_रखो(boot_params, 0x0, माप(काष्ठा boot_params));

	hdr = &boot_params->hdr;

	/* Copy the setup header from the second sector to boot_params */
	स_नकल(&hdr->jump, image_base + 512,
	       माप(काष्ठा setup_header) - दुरत्व(काष्ठा setup_header, jump));

	/*
	 * Fill out some of the header fields ourselves because the
	 * EFI firmware loader करोesn't load the first sector.
	 */
	hdr->root_flags	= 1;
	hdr->vid_mode	= 0xffff;
	hdr->boot_flag	= 0xAA55;

	hdr->type_of_loader = 0x21;

	/* Convert unicode cmdline to ascii */
	cmdline_ptr = efi_convert_cmdline(image, &options_size);
	अगर (!cmdline_ptr)
		जाओ fail;

	efi_set_u64_split((अचिन्हित दीर्घ)cmdline_ptr,
			  &hdr->cmd_line_ptr, &boot_params->ext_cmd_line_ptr);

	hdr->ramdisk_image = 0;
	hdr->ramdisk_size = 0;

	efi_stub_entry(handle, sys_table_arg, boot_params);
	/* not reached */

fail:
	efi_मुक्त(माप(काष्ठा boot_params), (अचिन्हित दीर्घ)boot_params);

	efi_निकास(handle, status);
पूर्ण

अटल व्योम add_e820ext(काष्ठा boot_params *params,
			काष्ठा setup_data *e820ext, u32 nr_entries)
अणु
	काष्ठा setup_data *data;

	e820ext->type = SETUP_E820_EXT;
	e820ext->len  = nr_entries * माप(काष्ठा boot_e820_entry);
	e820ext->next = 0;

	data = (काष्ठा setup_data *)(अचिन्हित दीर्घ)params->hdr.setup_data;

	जबतक (data && data->next)
		data = (काष्ठा setup_data *)(अचिन्हित दीर्घ)data->next;

	अगर (data)
		data->next = (अचिन्हित दीर्घ)e820ext;
	अन्यथा
		params->hdr.setup_data = (अचिन्हित दीर्घ)e820ext;
पूर्ण

अटल efi_status_t
setup_e820(काष्ठा boot_params *params, काष्ठा setup_data *e820ext, u32 e820ext_size)
अणु
	काष्ठा boot_e820_entry *entry = params->e820_table;
	काष्ठा efi_info *efi = &params->efi_info;
	काष्ठा boot_e820_entry *prev = शून्य;
	u32 nr_entries;
	u32 nr_desc;
	पूर्णांक i;

	nr_entries = 0;
	nr_desc = efi->efi_memmap_size / efi->efi_memdesc_size;

	क्रम (i = 0; i < nr_desc; i++) अणु
		efi_memory_desc_t *d;
		अचिन्हित पूर्णांक e820_type = 0;
		अचिन्हित दीर्घ m = efi->efi_memmap;

#अगर_घोषित CONFIG_X86_64
		m |= (u64)efi->efi_memmap_hi << 32;
#पूर्ण_अगर

		d = efi_early_memdesc_ptr(m, efi->efi_memdesc_size, i);
		चयन (d->type) अणु
		हाल EFI_RESERVED_TYPE:
		हाल EFI_RUNTIME_SERVICES_CODE:
		हाल EFI_RUNTIME_SERVICES_DATA:
		हाल EFI_MEMORY_MAPPED_IO:
		हाल EFI_MEMORY_MAPPED_IO_PORT_SPACE:
		हाल EFI_PAL_CODE:
			e820_type = E820_TYPE_RESERVED;
			अवरोध;

		हाल EFI_UNUSABLE_MEMORY:
			e820_type = E820_TYPE_UNUSABLE;
			अवरोध;

		हाल EFI_ACPI_RECLAIM_MEMORY:
			e820_type = E820_TYPE_ACPI;
			अवरोध;

		हाल EFI_LOADER_CODE:
		हाल EFI_LOADER_DATA:
		हाल EFI_BOOT_SERVICES_CODE:
		हाल EFI_BOOT_SERVICES_DATA:
		हाल EFI_CONVENTIONAL_MEMORY:
			अगर (efi_soft_reserve_enabled() &&
			    (d->attribute & EFI_MEMORY_SP))
				e820_type = E820_TYPE_SOFT_RESERVED;
			अन्यथा
				e820_type = E820_TYPE_RAM;
			अवरोध;

		हाल EFI_ACPI_MEMORY_NVS:
			e820_type = E820_TYPE_NVS;
			अवरोध;

		हाल EFI_PERSISTENT_MEMORY:
			e820_type = E820_TYPE_PMEM;
			अवरोध;

		शेष:
			जारी;
		पूर्ण

		/* Merge adjacent mappings */
		अगर (prev && prev->type == e820_type &&
		    (prev->addr + prev->size) == d->phys_addr) अणु
			prev->size += d->num_pages << 12;
			जारी;
		पूर्ण

		अगर (nr_entries == ARRAY_SIZE(params->e820_table)) अणु
			u32 need = (nr_desc - i) * माप(काष्ठा e820_entry) +
				   माप(काष्ठा setup_data);

			अगर (!e820ext || e820ext_size < need)
				वापस EFI_BUFFER_TOO_SMALL;

			/* boot_params map full, चयन to e820 extended */
			entry = (काष्ठा boot_e820_entry *)e820ext->data;
		पूर्ण

		entry->addr = d->phys_addr;
		entry->size = d->num_pages << PAGE_SHIFT;
		entry->type = e820_type;
		prev = entry++;
		nr_entries++;
	पूर्ण

	अगर (nr_entries > ARRAY_SIZE(params->e820_table)) अणु
		u32 nr_e820ext = nr_entries - ARRAY_SIZE(params->e820_table);

		add_e820ext(params, e820ext, nr_e820ext);
		nr_entries -= nr_e820ext;
	पूर्ण

	params->e820_entries = (u8)nr_entries;

	वापस EFI_SUCCESS;
पूर्ण

अटल efi_status_t alloc_e820ext(u32 nr_desc, काष्ठा setup_data **e820ext,
				  u32 *e820ext_size)
अणु
	efi_status_t status;
	अचिन्हित दीर्घ size;

	size = माप(काष्ठा setup_data) +
		माप(काष्ठा e820_entry) * nr_desc;

	अगर (*e820ext) अणु
		efi_bs_call(मुक्त_pool, *e820ext);
		*e820ext = शून्य;
		*e820ext_size = 0;
	पूर्ण

	status = efi_bs_call(allocate_pool, EFI_LOADER_DATA, size,
			     (व्योम **)e820ext);
	अगर (status == EFI_SUCCESS)
		*e820ext_size = size;

	वापस status;
पूर्ण

अटल efi_status_t allocate_e820(काष्ठा boot_params *params,
				  काष्ठा setup_data **e820ext,
				  u32 *e820ext_size)
अणु
	अचिन्हित दीर्घ map_size, desc_size, map_key;
	efi_status_t status;
	__u32 nr_desc, desc_version;

	/* Only need the size of the mem map and size of each mem descriptor */
	map_size = 0;
	status = efi_bs_call(get_memory_map, &map_size, शून्य, &map_key,
			     &desc_size, &desc_version);
	अगर (status != EFI_BUFFER_TOO_SMALL)
		वापस (status != EFI_SUCCESS) ? status : EFI_UNSUPPORTED;

	nr_desc = map_size / desc_size + EFI_MMAP_NR_SLACK_SLOTS;

	अगर (nr_desc > ARRAY_SIZE(params->e820_table)) अणु
		u32 nr_e820ext = nr_desc - ARRAY_SIZE(params->e820_table);

		status = alloc_e820ext(nr_e820ext, e820ext, e820ext_size);
		अगर (status != EFI_SUCCESS)
			वापस status;
	पूर्ण

	वापस EFI_SUCCESS;
पूर्ण

काष्ठा निकास_boot_काष्ठा अणु
	काष्ठा boot_params	*boot_params;
	काष्ठा efi_info		*efi;
पूर्ण;

अटल efi_status_t निकास_boot_func(काष्ठा efi_boot_memmap *map,
				   व्योम *priv)
अणु
	स्थिर अक्षर *signature;
	काष्ठा निकास_boot_काष्ठा *p = priv;

	signature = efi_is_64bit() ? EFI64_LOADER_SIGNATURE
				   : EFI32_LOADER_SIGNATURE;
	स_नकल(&p->efi->efi_loader_signature, signature, माप(__u32));

	efi_set_u64_split((अचिन्हित दीर्घ)efi_प्रणाली_table,
			  &p->efi->efi_systab, &p->efi->efi_systab_hi);
	p->efi->efi_memdesc_size	= *map->desc_size;
	p->efi->efi_memdesc_version	= *map->desc_ver;
	efi_set_u64_split((अचिन्हित दीर्घ)*map->map,
			  &p->efi->efi_memmap, &p->efi->efi_memmap_hi);
	p->efi->efi_memmap_size		= *map->map_size;

	वापस EFI_SUCCESS;
पूर्ण

अटल efi_status_t निकास_boot(काष्ठा boot_params *boot_params, व्योम *handle)
अणु
	अचिन्हित दीर्घ map_sz, key, desc_size, buff_size;
	efi_memory_desc_t *mem_map;
	काष्ठा setup_data *e820ext = शून्य;
	__u32 e820ext_size = 0;
	efi_status_t status;
	__u32 desc_version;
	काष्ठा efi_boot_memmap map;
	काष्ठा निकास_boot_काष्ठा priv;

	map.map			= &mem_map;
	map.map_size		= &map_sz;
	map.desc_size		= &desc_size;
	map.desc_ver		= &desc_version;
	map.key_ptr		= &key;
	map.buff_size		= &buff_size;
	priv.boot_params	= boot_params;
	priv.efi		= &boot_params->efi_info;

	status = allocate_e820(boot_params, &e820ext, &e820ext_size);
	अगर (status != EFI_SUCCESS)
		वापस status;

	/* Might as well निकास boot services now */
	status = efi_निकास_boot_services(handle, &map, &priv, निकास_boot_func);
	अगर (status != EFI_SUCCESS)
		वापस status;

	/* Historic? */
	boot_params->alt_mem_k	= 32 * 1024;

	status = setup_e820(boot_params, e820ext, e820ext_size);
	अगर (status != EFI_SUCCESS)
		वापस status;

	वापस EFI_SUCCESS;
पूर्ण

/*
 * On success, we वापस the address of startup_32, which has potentially been
 * relocated by efi_relocate_kernel.
 * On failure, we निकास to the firmware via efi_निकास instead of वापसing.
 */
अचिन्हित दीर्घ efi_मुख्य(efi_handle_t handle,
			     efi_प्रणाली_table_t *sys_table_arg,
			     काष्ठा boot_params *boot_params)
अणु
	अचिन्हित दीर्घ bzimage_addr = (अचिन्हित दीर्घ)startup_32;
	अचिन्हित दीर्घ buffer_start, buffer_end;
	काष्ठा setup_header *hdr = &boot_params->hdr;
	efi_status_t status;

	efi_प्रणाली_table = sys_table_arg;

	/* Check अगर we were booted by the EFI firmware */
	अगर (efi_प्रणाली_table->hdr.signature != EFI_SYSTEM_TABLE_SIGNATURE)
		efi_निकास(handle, EFI_INVALID_PARAMETER);

	/*
	 * If the kernel isn't alपढ़ोy loaded at a suitable address,
	 * relocate it.
	 *
	 * It must be loaded above LOAD_PHYSICAL_ADDR.
	 *
	 * The maximum address क्रम 64-bit is 1 << 46 क्रम 4-level paging. This
	 * is defined as the macro MAXMEM, but unक्रमtunately that is not a
	 * compile-समय स्थिरant अगर 5-level paging is configured, so we instead
	 * define our own macro क्रम use here.
	 *
	 * For 32-bit, the maximum address is complicated to figure out, क्रम
	 * now use KERNEL_IMAGE_SIZE, which will be 512MiB, the same as what
	 * KASLR uses.
	 *
	 * Also relocate it अगर image_offset is zero, i.e. the kernel wasn't
	 * loaded by LoadImage, but rather by a bootloader that called the
	 * hanकरोver entry. The reason we must always relocate in this हाल is
	 * to handle the हाल of प्रणालीd-boot booting a unअगरied kernel image,
	 * which is a PE executable that contains the bzImage and an initrd as
	 * COFF sections. The initrd section is placed after the bzImage
	 * without ensuring that there are at least init_size bytes available
	 * क्रम the bzImage, and thus the compressed kernel's startup code may
	 * overग_लिखो the initrd unless it is moved out of the way.
	 */

	buffer_start = ALIGN(bzimage_addr - image_offset,
			     hdr->kernel_alignment);
	buffer_end = buffer_start + hdr->init_size;

	अगर ((buffer_start < LOAD_PHYSICAL_ADDR)				     ||
	    (IS_ENABLED(CONFIG_X86_32) && buffer_end > KERNEL_IMAGE_SIZE)    ||
	    (IS_ENABLED(CONFIG_X86_64) && buffer_end > MAXMEM_X86_64_4LEVEL) ||
	    (image_offset == 0)) अणु
		बाह्य अक्षर _bss[];

		status = efi_relocate_kernel(&bzimage_addr,
					     (अचिन्हित दीर्घ)_bss - bzimage_addr,
					     hdr->init_size,
					     hdr->pref_address,
					     hdr->kernel_alignment,
					     LOAD_PHYSICAL_ADDR);
		अगर (status != EFI_SUCCESS) अणु
			efi_err("efi_relocate_kernel() failed!\n");
			जाओ fail;
		पूर्ण
		/*
		 * Now that we've copied the kernel अन्यथाwhere, we no दीर्घer
		 * have a set up block beक्रमe startup_32(), so reset image_offset
		 * to zero in हाल it was set earlier.
		 */
		image_offset = 0;
	पूर्ण

#अगर_घोषित CONFIG_CMDLINE_BOOL
	status = efi_parse_options(CONFIG_CMDLINE);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("Failed to parse options\n");
		जाओ fail;
	पूर्ण
#पूर्ण_अगर
	अगर (!IS_ENABLED(CONFIG_CMDLINE_OVERRIDE)) अणु
		अचिन्हित दीर्घ cmdline_paddr = ((u64)hdr->cmd_line_ptr |
					       ((u64)boot_params->ext_cmd_line_ptr << 32));
		status = efi_parse_options((अक्षर *)cmdline_paddr);
		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to parse options\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	/*
	 * At this poपूर्णांक, an initrd may alपढ़ोy have been loaded by the
	 * bootloader and passed via bootparams. We permit an initrd loaded
	 * from the LINUX_EFI_INITRD_MEDIA_GUID device path to supersede it.
	 *
	 * If the device path is not present, any command-line initrd=
	 * arguments will be processed only अगर image is not शून्य, which will be
	 * the हाल only अगर we were loaded via the PE entry poपूर्णांक.
	 */
	अगर (!efi_noinitrd) अणु
		अचिन्हित दीर्घ addr, size;

		status = efi_load_initrd(image, &addr, &size,
					 hdr->initrd_addr_max, अच_दीर्घ_उच्च);

		अगर (status != EFI_SUCCESS) अणु
			efi_err("Failed to load initrd!\n");
			जाओ fail;
		पूर्ण
		अगर (size > 0) अणु
			efi_set_u64_split(addr, &hdr->ramdisk_image,
					  &boot_params->ext_ramdisk_image);
			efi_set_u64_split(size, &hdr->ramdisk_size,
					  &boot_params->ext_ramdisk_size);
		पूर्ण
	पूर्ण

	/*
	 * If the boot loader gave us a value क्रम secure_boot then we use that,
	 * otherwise we ask the BIOS.
	 */
	अगर (boot_params->secure_boot == efi_secureboot_mode_unset)
		boot_params->secure_boot = efi_get_secureboot();

	/* Ask the firmware to clear memory on unclean shutकरोwn */
	efi_enable_reset_attack_mitigation();

	efi_अक्रमom_get_seed();

	efi_retrieve_tpm2_eventlog();

	setup_graphics(boot_params);

	setup_efi_pci(boot_params);

	setup_quirks(boot_params);

	status = निकास_boot(boot_params, handle);
	अगर (status != EFI_SUCCESS) अणु
		efi_err("exit_boot() failed!\n");
		जाओ fail;
	पूर्ण

	वापस bzimage_addr;
fail:
	efi_err("efi_main() failed!\n");

	efi_निकास(handle, status);
पूर्ण
