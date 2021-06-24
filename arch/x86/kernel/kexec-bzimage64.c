<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kexec bzImage loader
 *
 * Copyright (C) 2014 Red Hat Inc.
 * Authors:
 *      Vivek Goyal <vgoyal@redhat.com>
 */

#घोषणा pr_fmt(fmt)	"kexec-bzImage64: " fmt

#समावेश <linux/माला.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/kexec.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/efi.h>
#समावेश <linux/verअगरication.h>

#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/crash.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/kexec-bzimage64.h>

#घोषणा MAX_ELFCOREHDR_STR_LEN	30	/* elfcorehdr=0x<64bit-value> */

/*
 * Defines lowest physical address क्रम various segments. Not sure where
 * exactly these limits came from. Current bzimage64 loader in kexec-tools
 * uses these so I am retaining it. It can be changed over समय as we gain
 * more insight.
 */
#घोषणा MIN_PURGATORY_ADDR	0x3000
#घोषणा MIN_BOOTPARAM_ADDR	0x3000
#घोषणा MIN_KERNEL_LOAD_ADDR	0x100000
#घोषणा MIN_INITRD_LOAD_ADDR	0x1000000

/*
 * This is a place holder क्रम all boot loader specअगरic data काष्ठाure which
 * माला_लो allocated in one call but माला_लो मुक्तd much later during cleanup
 * समय. Right now there is only one field but it can grow as need be.
 */
काष्ठा bzimage64_data अणु
	/*
	 * Temporary buffer to hold bootparams buffer. This should be
	 * मुक्तd once the bootparam segment has been loaded.
	 */
	व्योम *bootparams_buf;
पूर्ण;

अटल पूर्णांक setup_initrd(काष्ठा boot_params *params,
		अचिन्हित दीर्घ initrd_load_addr, अचिन्हित दीर्घ initrd_len)
अणु
	params->hdr.ramdisk_image = initrd_load_addr & 0xffffffffUL;
	params->hdr.ramdisk_size = initrd_len & 0xffffffffUL;

	params->ext_ramdisk_image = initrd_load_addr >> 32;
	params->ext_ramdisk_size = initrd_len >> 32;

	वापस 0;
पूर्ण

अटल पूर्णांक setup_cmdline(काष्ठा kimage *image, काष्ठा boot_params *params,
			 अचिन्हित दीर्घ bootparams_load_addr,
			 अचिन्हित दीर्घ cmdline_offset, अक्षर *cmdline,
			 अचिन्हित दीर्घ cmdline_len)
अणु
	अक्षर *cmdline_ptr = ((अक्षर *)params) + cmdline_offset;
	अचिन्हित दीर्घ cmdline_ptr_phys, len = 0;
	uपूर्णांक32_t cmdline_low_32, cmdline_ext_32;

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		len = प्र_लिखो(cmdline_ptr,
			"elfcorehdr=0x%lx ", image->elf_load_addr);
	पूर्ण
	स_नकल(cmdline_ptr + len, cmdline, cmdline_len);
	cmdline_len += len;

	cmdline_ptr[cmdline_len - 1] = '\0';

	pr_debug("Final command line is: %s\n", cmdline_ptr);
	cmdline_ptr_phys = bootparams_load_addr + cmdline_offset;
	cmdline_low_32 = cmdline_ptr_phys & 0xffffffffUL;
	cmdline_ext_32 = cmdline_ptr_phys >> 32;

	params->hdr.cmd_line_ptr = cmdline_low_32;
	अगर (cmdline_ext_32)
		params->ext_cmd_line_ptr = cmdline_ext_32;

	वापस 0;
पूर्ण

अटल पूर्णांक setup_e820_entries(काष्ठा boot_params *params)
अणु
	अचिन्हित पूर्णांक nr_e820_entries;

	nr_e820_entries = e820_table_kexec->nr_entries;

	/* TODO: Pass entries more than E820_MAX_ENTRIES_ZEROPAGE in bootparams setup data */
	अगर (nr_e820_entries > E820_MAX_ENTRIES_ZEROPAGE)
		nr_e820_entries = E820_MAX_ENTRIES_ZEROPAGE;

	params->e820_entries = nr_e820_entries;
	स_नकल(&params->e820_table, &e820_table_kexec->entries, nr_e820_entries*माप(काष्ठा e820_entry));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_EFI
अटल पूर्णांक setup_efi_info_memmap(काष्ठा boot_params *params,
				  अचिन्हित दीर्घ params_load_addr,
				  अचिन्हित पूर्णांक efi_map_offset,
				  अचिन्हित पूर्णांक efi_map_sz)
अणु
	व्योम *efi_map = (व्योम *)params + efi_map_offset;
	अचिन्हित दीर्घ efi_map_phys_addr = params_load_addr + efi_map_offset;
	काष्ठा efi_info *ei = &params->efi_info;

	अगर (!efi_map_sz)
		वापस 0;

	efi_runसमय_map_copy(efi_map, efi_map_sz);

	ei->efi_memmap = efi_map_phys_addr & 0xffffffff;
	ei->efi_memmap_hi = efi_map_phys_addr >> 32;
	ei->efi_memmap_size = efi_map_sz;

	वापस 0;
पूर्ण

अटल पूर्णांक
prepare_add_efi_setup_data(काष्ठा boot_params *params,
		       अचिन्हित दीर्घ params_load_addr,
		       अचिन्हित पूर्णांक efi_setup_data_offset)
अणु
	अचिन्हित दीर्घ setup_data_phys;
	काष्ठा setup_data *sd = (व्योम *)params + efi_setup_data_offset;
	काष्ठा efi_setup_data *esd = (व्योम *)sd + माप(काष्ठा setup_data);

	esd->fw_venकरोr = efi_fw_venकरोr;
	esd->tables = efi_config_table;
	esd->smbios = efi.smbios;

	sd->type = SETUP_EFI;
	sd->len = माप(काष्ठा efi_setup_data);

	/* Add setup data */
	setup_data_phys = params_load_addr + efi_setup_data_offset;
	sd->next = params->hdr.setup_data;
	params->hdr.setup_data = setup_data_phys;

	वापस 0;
पूर्ण

अटल पूर्णांक
setup_efi_state(काष्ठा boot_params *params, अचिन्हित दीर्घ params_load_addr,
		अचिन्हित पूर्णांक efi_map_offset, अचिन्हित पूर्णांक efi_map_sz,
		अचिन्हित पूर्णांक efi_setup_data_offset)
अणु
	काष्ठा efi_info *current_ei = &boot_params.efi_info;
	काष्ठा efi_info *ei = &params->efi_info;

	अगर (!efi_enabled(EFI_RUNTIME_SERVICES))
		वापस 0;

	अगर (!current_ei->efi_memmap_size)
		वापस 0;

	params->secure_boot = boot_params.secure_boot;
	ei->efi_loader_signature = current_ei->efi_loader_signature;
	ei->efi_systab = current_ei->efi_systab;
	ei->efi_systab_hi = current_ei->efi_systab_hi;

	ei->efi_memdesc_version = current_ei->efi_memdesc_version;
	ei->efi_memdesc_size = efi_get_runसमय_map_desc_size();

	setup_efi_info_memmap(params, params_load_addr, efi_map_offset,
			      efi_map_sz);
	prepare_add_efi_setup_data(params, params_load_addr,
				   efi_setup_data_offset);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_EFI */

अटल पूर्णांक
setup_boot_parameters(काष्ठा kimage *image, काष्ठा boot_params *params,
		      अचिन्हित दीर्घ params_load_addr,
		      अचिन्हित पूर्णांक efi_map_offset, अचिन्हित पूर्णांक efi_map_sz,
		      अचिन्हित पूर्णांक efi_setup_data_offset)
अणु
	अचिन्हित पूर्णांक nr_e820_entries;
	अचिन्हित दीर्घ दीर्घ mem_k, start, end;
	पूर्णांक i, ret = 0;

	/* Get subarch from existing bootparams */
	params->hdr.hardware_subarch = boot_params.hdr.hardware_subarch;

	/* Copying screen_info will करो? */
	स_नकल(&params->screen_info, &screen_info, माप(काष्ठा screen_info));

	/* Fill in memsize later */
	params->screen_info.ext_mem_k = 0;
	params->alt_mem_k = 0;

	/* Always fill in RSDP: it is either 0 or a valid value */
	params->acpi_rsdp_addr = boot_params.acpi_rsdp_addr;

	/* Default APM info */
	स_रखो(&params->apm_bios_info, 0, माप(params->apm_bios_info));

	/* Default drive info */
	स_रखो(&params->hd0_info, 0, माप(params->hd0_info));
	स_रखो(&params->hd1_info, 0, माप(params->hd1_info));

	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		ret = crash_setup_memmap_entries(image, params);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा
		setup_e820_entries(params);

	nr_e820_entries = params->e820_entries;

	क्रम (i = 0; i < nr_e820_entries; i++) अणु
		अगर (params->e820_table[i].type != E820_TYPE_RAM)
			जारी;
		start = params->e820_table[i].addr;
		end = params->e820_table[i].addr + params->e820_table[i].size - 1;

		अगर ((start <= 0x100000) && end > 0x100000) अणु
			mem_k = (end >> 10) - (0x100000 >> 10);
			params->screen_info.ext_mem_k = mem_k;
			params->alt_mem_k = mem_k;
			अगर (mem_k > 0xfc00)
				params->screen_info.ext_mem_k = 0xfc00; /* 64M*/
			अगर (mem_k > 0xffffffff)
				params->alt_mem_k = 0xffffffff;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_EFI
	/* Setup EFI state */
	setup_efi_state(params, params_load_addr, efi_map_offset, efi_map_sz,
			efi_setup_data_offset);
#पूर्ण_अगर
	/* Setup EDD info */
	स_नकल(params->eddbuf, boot_params.eddbuf,
				EDDMAXNR * माप(काष्ठा edd_info));
	params->eddbuf_entries = boot_params.eddbuf_entries;

	स_नकल(params->edd_mbr_sig_buffer, boot_params.edd_mbr_sig_buffer,
	       EDD_MBR_SIG_MAX * माप(अचिन्हित पूर्णांक));

	वापस ret;
पूर्ण

अटल पूर्णांक bzImage64_probe(स्थिर अक्षर *buf, अचिन्हित दीर्घ len)
अणु
	पूर्णांक ret = -ENOEXEC;
	काष्ठा setup_header *header;

	/* kernel should be at least two sectors दीर्घ */
	अगर (len < 2 * 512) अणु
		pr_err("File is too short to be a bzImage\n");
		वापस ret;
	पूर्ण

	header = (काष्ठा setup_header *)(buf + दुरत्व(काष्ठा boot_params, hdr));
	अगर (स_भेद((अक्षर *)&header->header, "HdrS", 4) != 0) अणु
		pr_err("Not a bzImage\n");
		वापस ret;
	पूर्ण

	अगर (header->boot_flag != 0xAA55) अणु
		pr_err("No x86 boot sector present\n");
		वापस ret;
	पूर्ण

	अगर (header->version < 0x020C) अणु
		pr_err("Must be at least protocol version 2.12\n");
		वापस ret;
	पूर्ण

	अगर (!(header->loadflags & LOADED_HIGH)) अणु
		pr_err("zImage not a bzImage\n");
		वापस ret;
	पूर्ण

	अगर (!(header->xloadflags & XLF_KERNEL_64)) अणु
		pr_err("Not a bzImage64. XLF_KERNEL_64 is not set.\n");
		वापस ret;
	पूर्ण

	अगर (!(header->xloadflags & XLF_CAN_BE_LOADED_ABOVE_4G)) अणु
		pr_err("XLF_CAN_BE_LOADED_ABOVE_4G is not set.\n");
		वापस ret;
	पूर्ण

	/*
	 * Can't handle 32bit EFI as it करोes not allow loading kernel
	 * above 4G. This should be handled by 32bit bzImage loader
	 */
	अगर (efi_enabled(EFI_RUNTIME_SERVICES) && !efi_enabled(EFI_64BIT)) अणु
		pr_debug("EFI is 32 bit. Can't load kernel above 4G.\n");
		वापस ret;
	पूर्ण

	अगर (!(header->xloadflags & XLF_5LEVEL) && pgtable_l5_enabled()) अणु
		pr_err("bzImage cannot handle 5-level paging mode.\n");
		वापस ret;
	पूर्ण

	/* I've got a bzImage */
	pr_debug("It's a relocatable bzImage64\n");
	ret = 0;

	वापस ret;
पूर्ण

अटल व्योम *bzImage64_load(काष्ठा kimage *image, अक्षर *kernel,
			    अचिन्हित दीर्घ kernel_len, अक्षर *initrd,
			    अचिन्हित दीर्घ initrd_len, अक्षर *cmdline,
			    अचिन्हित दीर्घ cmdline_len)
अणु

	काष्ठा setup_header *header;
	पूर्णांक setup_sects, kern16_size, ret = 0;
	अचिन्हित दीर्घ setup_header_size, params_cmdline_sz;
	काष्ठा boot_params *params;
	अचिन्हित दीर्घ bootparam_load_addr, kernel_load_addr, initrd_load_addr;
	काष्ठा bzimage64_data *ldata;
	काष्ठा kexec_entry64_regs regs64;
	व्योम *stack;
	अचिन्हित पूर्णांक setup_hdr_offset = दुरत्व(काष्ठा boot_params, hdr);
	अचिन्हित पूर्णांक efi_map_offset, efi_map_sz, efi_setup_data_offset;
	काष्ठा kexec_buf kbuf = अणु .image = image, .buf_max = अच_दीर्घ_उच्च,
				  .top_करोwn = true पूर्ण;
	काष्ठा kexec_buf pbuf = अणु .image = image, .buf_min = MIN_PURGATORY_ADDR,
				  .buf_max = अच_दीर्घ_उच्च, .top_करोwn = true पूर्ण;

	header = (काष्ठा setup_header *)(kernel + setup_hdr_offset);
	setup_sects = header->setup_sects;
	अगर (setup_sects == 0)
		setup_sects = 4;

	kern16_size = (setup_sects + 1) * 512;
	अगर (kernel_len < kern16_size) अणु
		pr_err("bzImage truncated\n");
		वापस ERR_PTR(-ENOEXEC);
	पूर्ण

	अगर (cmdline_len > header->cmdline_size) अणु
		pr_err("Kernel command line too long\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * In हाल of crash dump, we will append elfcorehdr=<addr> to
	 * command line. Make sure it करोes not overflow
	 */
	अगर (cmdline_len + MAX_ELFCOREHDR_STR_LEN > header->cmdline_size) अणु
		pr_debug("Appending elfcorehdr=<addr> to command line exceeds maximum allowed length\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* Allocate and load backup region */
	अगर (image->type == KEXEC_TYPE_CRASH) अणु
		ret = crash_load_segments(image);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	/*
	 * Load purgatory. For 64bit entry poपूर्णांक, purgatory  code can be
	 * anywhere.
	 */
	ret = kexec_load_purgatory(image, &pbuf);
	अगर (ret) अणु
		pr_err("Loading purgatory failed\n");
		वापस ERR_PTR(ret);
	पूर्ण

	pr_debug("Loaded purgatory at 0x%lx\n", pbuf.mem);


	/*
	 * Load Bootparams and cmdline and space क्रम efi stuff.
	 *
	 * Allocate memory together क्रम multiple data काष्ठाures so
	 * that they all can go in single area/segment and we करोn't
	 * have to create separate segment क्रम each. Keeps things
	 * little bit simple
	 */
	efi_map_sz = efi_get_runसमय_map_size();
	params_cmdline_sz = माप(काष्ठा boot_params) + cmdline_len +
				MAX_ELFCOREHDR_STR_LEN;
	params_cmdline_sz = ALIGN(params_cmdline_sz, 16);
	kbuf.bufsz = params_cmdline_sz + ALIGN(efi_map_sz, 16) +
				माप(काष्ठा setup_data) +
				माप(काष्ठा efi_setup_data);

	params = kzalloc(kbuf.bufsz, GFP_KERNEL);
	अगर (!params)
		वापस ERR_PTR(-ENOMEM);
	efi_map_offset = params_cmdline_sz;
	efi_setup_data_offset = efi_map_offset + ALIGN(efi_map_sz, 16);

	/* Copy setup header onto bootparams. Documentation/x86/boot.rst */
	setup_header_size = 0x0202 + kernel[0x0201] - setup_hdr_offset;

	/* Is there a limit on setup header size? */
	स_नकल(&params->hdr, (kernel + setup_hdr_offset), setup_header_size);

	kbuf.buffer = params;
	kbuf.memsz = kbuf.bufsz;
	kbuf.buf_align = 16;
	kbuf.buf_min = MIN_BOOTPARAM_ADDR;
	ret = kexec_add_buffer(&kbuf);
	अगर (ret)
		जाओ out_मुक्त_params;
	bootparam_load_addr = kbuf.mem;
	pr_debug("Loaded boot_param, command line and misc at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
		 bootparam_load_addr, kbuf.bufsz, kbuf.bufsz);

	/* Load kernel */
	kbuf.buffer = kernel + kern16_size;
	kbuf.bufsz =  kernel_len - kern16_size;
	kbuf.memsz = PAGE_ALIGN(header->init_size);
	kbuf.buf_align = header->kernel_alignment;
	kbuf.buf_min = MIN_KERNEL_LOAD_ADDR;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	ret = kexec_add_buffer(&kbuf);
	अगर (ret)
		जाओ out_मुक्त_params;
	kernel_load_addr = kbuf.mem;

	pr_debug("Loaded 64bit kernel at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
		 kernel_load_addr, kbuf.bufsz, kbuf.memsz);

	/* Load initrd high */
	अगर (initrd) अणु
		kbuf.buffer = initrd;
		kbuf.bufsz = kbuf.memsz = initrd_len;
		kbuf.buf_align = PAGE_SIZE;
		kbuf.buf_min = MIN_INITRD_LOAD_ADDR;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		ret = kexec_add_buffer(&kbuf);
		अगर (ret)
			जाओ out_मुक्त_params;
		initrd_load_addr = kbuf.mem;

		pr_debug("Loaded initrd at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
				initrd_load_addr, initrd_len, initrd_len);

		setup_initrd(params, initrd_load_addr, initrd_len);
	पूर्ण

	setup_cmdline(image, params, bootparam_load_addr,
		      माप(काष्ठा boot_params), cmdline, cmdline_len);

	/* bootloader info. Do we need a separate ID क्रम kexec kernel loader? */
	params->hdr.type_of_loader = 0x0D << 4;
	params->hdr.loadflags = 0;

	/* Setup purgatory regs क्रम entry */
	ret = kexec_purgatory_get_set_symbol(image, "entry64_regs", &regs64,
					     माप(regs64), 1);
	अगर (ret)
		जाओ out_मुक्त_params;

	regs64.rbx = 0; /* Bootstrap Processor */
	regs64.rsi = bootparam_load_addr;
	regs64.rip = kernel_load_addr + 0x200;
	stack = kexec_purgatory_get_symbol_addr(image, "stack_end");
	अगर (IS_ERR(stack)) अणु
		pr_err("Could not find address of symbol stack_end\n");
		ret = -EINVAL;
		जाओ out_मुक्त_params;
	पूर्ण

	regs64.rsp = (अचिन्हित दीर्घ)stack;
	ret = kexec_purgatory_get_set_symbol(image, "entry64_regs", &regs64,
					     माप(regs64), 0);
	अगर (ret)
		जाओ out_मुक्त_params;

	ret = setup_boot_parameters(image, params, bootparam_load_addr,
				    efi_map_offset, efi_map_sz,
				    efi_setup_data_offset);
	अगर (ret)
		जाओ out_मुक्त_params;

	/* Allocate loader specअगरic data */
	ldata = kzalloc(माप(काष्ठा bzimage64_data), GFP_KERNEL);
	अगर (!ldata) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_params;
	पूर्ण

	/*
	 * Store poपूर्णांकer to params so that it could be मुक्तd after loading
	 * params segment has been loaded and contents have been copied
	 * somewhere अन्यथा.
	 */
	ldata->bootparams_buf = params;
	वापस ldata;

out_मुक्त_params:
	kमुक्त(params);
	वापस ERR_PTR(ret);
पूर्ण

/* This cleanup function is called after various segments have been loaded */
अटल पूर्णांक bzImage64_cleanup(व्योम *loader_data)
अणु
	काष्ठा bzimage64_data *ldata = loader_data;

	अगर (!ldata)
		वापस 0;

	kमुक्त(ldata->bootparams_buf);
	ldata->bootparams_buf = शून्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_KEXEC_BZIMAGE_VERIFY_SIG
अटल पूर्णांक bzImage64_verअगरy_sig(स्थिर अक्षर *kernel, अचिन्हित दीर्घ kernel_len)
अणु
	पूर्णांक ret;

	ret = verअगरy_pefile_signature(kernel, kernel_len,
				      VERIFY_USE_SECONDARY_KEYRING,
				      VERIFYING_KEXEC_PE_SIGNATURE);
	अगर (ret == -ENOKEY && IS_ENABLED(CONFIG_INTEGRITY_PLATFORM_KEYRING)) अणु
		ret = verअगरy_pefile_signature(kernel, kernel_len,
					      VERIFY_USE_PLATFORM_KEYRING,
					      VERIFYING_KEXEC_PE_SIGNATURE);
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा kexec_file_ops kexec_bzImage64_ops = अणु
	.probe = bzImage64_probe,
	.load = bzImage64_load,
	.cleanup = bzImage64_cleanup,
#अगर_घोषित CONFIG_KEXEC_BZIMAGE_VERIFY_SIG
	.verअगरy_sig = bzImage64_verअगरy_sig,
#पूर्ण_अगर
पूर्ण;
