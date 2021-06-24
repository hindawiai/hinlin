<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1995  Linus Torvalds
 *
 * This file contains the setup_arch() code, which handles the architecture-dependent
 * parts of early kernel initialization.
 */
#समावेश <linux/console.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dmi.h>
#समावेश <linux/efi.h>
#समावेश <linux/init_ohci1394_dma.h>
#समावेश <linux/initrd.h>
#समावेश <linux/iscsi_ibft.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pci.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/tboot.h>
#समावेश <linux/usb/xhci-dbgp.h>
#समावेश <linux/अटल_call.h>
#समावेश <linux/swiotlb.h>

#समावेश <uapi/linux/mount.h>

#समावेश <xen/xen.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/gart.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/kaslr.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/olpc_ofw.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/thermal.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/vsyscall.h>
#समावेश <linux/vदो_स्मृति.h>

/*
 * max_low_pfn_mapped: highest directly mapped pfn < 4 GB
 * max_pfn_mapped:     highest directly mapped pfn > 4 GB
 *
 * The direct mapping only covers E820_TYPE_RAM regions, so the ranges and gaps are
 * represented by pfn_mapped[].
 */
अचिन्हित दीर्घ max_low_pfn_mapped;
अचिन्हित दीर्घ max_pfn_mapped;

#अगर_घोषित CONFIG_DMI
RESERVE_BRK(dmi_alloc, 65536);
#पूर्ण_अगर


/*
 * Range of the BSS area. The size of the BSS area is determined
 * at link समय, with RESERVE_BRK() facility reserving additional
 * chunks.
 */
अचिन्हित दीर्घ _brk_start = (अचिन्हित दीर्घ)__brk_base;
अचिन्हित दीर्घ _brk_end   = (अचिन्हित दीर्घ)__brk_base;

काष्ठा boot_params boot_params;

/*
 * These are the four मुख्य kernel memory regions, we put them पूर्णांकo
 * the resource tree so that kdump tools and other debugging tools
 * recover it:
 */

अटल काष्ठा resource rodata_resource = अणु
	.name	= "Kernel rodata",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल काष्ठा resource data_resource = अणु
	.name	= "Kernel data",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल काष्ठा resource code_resource = अणु
	.name	= "Kernel code",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;

अटल काष्ठा resource bss_resource = अणु
	.name	= "Kernel bss",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_SYSTEM_RAM
पूर्ण;


#अगर_घोषित CONFIG_X86_32
/* CPU data as detected by the assembly code in head_32.S */
काष्ठा cpuinfo_x86 new_cpu_data;

/* Common CPU data क्रम all CPUs */
काष्ठा cpuinfo_x86 boot_cpu_data __पढ़ो_mostly;
EXPORT_SYMBOL(boot_cpu_data);

अचिन्हित पूर्णांक def_to_bigsmp;

काष्ठा apm_info apm_info;
EXPORT_SYMBOL(apm_info);

#अगर defined(CONFIG_X86_SPEEDSTEP_SMI) || \
	defined(CONFIG_X86_SPEEDSTEP_SMI_MODULE)
काष्ठा ist_info ist_info;
EXPORT_SYMBOL(ist_info);
#अन्यथा
काष्ठा ist_info ist_info;
#पूर्ण_अगर

#अन्यथा
काष्ठा cpuinfo_x86 boot_cpu_data __पढ़ो_mostly;
EXPORT_SYMBOL(boot_cpu_data);
#पूर्ण_अगर


#अगर !defined(CONFIG_X86_PAE) || defined(CONFIG_X86_64)
__visible अचिन्हित दीर्घ mmu_cr4_features __ro_after_init;
#अन्यथा
__visible अचिन्हित दीर्घ mmu_cr4_features __ro_after_init = X86_CR4_PAE;
#पूर्ण_अगर

/* Boot loader ID and version as पूर्णांकegers, क्रम the benefit of proc_करोपूर्णांकvec */
पूर्णांक bootloader_type, bootloader_version;

/*
 * Setup options
 */
काष्ठा screen_info screen_info;
EXPORT_SYMBOL(screen_info);
काष्ठा edid_info edid_info;
EXPORT_SYMBOL_GPL(edid_info);

बाह्य पूर्णांक root_mountflags;

अचिन्हित दीर्घ saved_video_mode;

#घोषणा RAMDISK_IMAGE_START_MASK	0x07FF
#घोषणा RAMDISK_PROMPT_FLAG		0x8000
#घोषणा RAMDISK_LOAD_FLAG		0x4000

अटल अक्षर __initdata command_line[COMMAND_LINE_SIZE];
#अगर_घोषित CONFIG_CMDLINE_BOOL
अटल अक्षर __initdata builtin_cmdline[COMMAND_LINE_SIZE] = CONFIG_CMDLINE;
#पूर्ण_अगर

#अगर defined(CONFIG_EDD) || defined(CONFIG_EDD_MODULE)
काष्ठा edd edd;
#अगर_घोषित CONFIG_EDD_MODULE
EXPORT_SYMBOL(edd);
#पूर्ण_अगर
/**
 * copy_edd() - Copy the BIOS EDD inक्रमmation
 *              from boot_params पूर्णांकo a safe place.
 *
 */
अटल अंतरभूत व्योम __init copy_edd(व्योम)
अणु
     स_नकल(edd.mbr_signature, boot_params.edd_mbr_sig_buffer,
	    माप(edd.mbr_signature));
     स_नकल(edd.edd_info, boot_params.eddbuf, माप(edd.edd_info));
     edd.mbr_signature_nr = boot_params.edd_mbr_sig_buf_entries;
     edd.edd_info_nr = boot_params.eddbuf_entries;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __init copy_edd(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

व्योम * __init extend_brk(माप_प्रकार size, माप_प्रकार align)
अणु
	माप_प्रकार mask = align - 1;
	व्योम *ret;

	BUG_ON(_brk_start == 0);
	BUG_ON(align & mask);

	_brk_end = (_brk_end + mask) & ~mask;
	BUG_ON((अक्षर *)(_brk_end + size) > __brk_limit);

	ret = (व्योम *)_brk_end;
	_brk_end += size;

	स_रखो(ret, 0, size);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_X86_32
अटल व्योम __init cleanup_highmap(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __init reserve_brk(व्योम)
अणु
	अगर (_brk_end > _brk_start)
		memblock_reserve(__pa_symbol(_brk_start),
				 _brk_end - _brk_start);

	/* Mark brk area as locked करोwn and no दीर्घer taking any
	   new allocations */
	_brk_start = 0;
पूर्ण

u64 relocated_ramdisk;

#अगर_घोषित CONFIG_BLK_DEV_INITRD

अटल u64 __init get_ramdisk_image(व्योम)
अणु
	u64 ramdisk_image = boot_params.hdr.ramdisk_image;

	ramdisk_image |= (u64)boot_params.ext_ramdisk_image << 32;

	अगर (ramdisk_image == 0)
		ramdisk_image = phys_initrd_start;

	वापस ramdisk_image;
पूर्ण
अटल u64 __init get_ramdisk_size(व्योम)
अणु
	u64 ramdisk_size = boot_params.hdr.ramdisk_size;

	ramdisk_size |= (u64)boot_params.ext_ramdisk_size << 32;

	अगर (ramdisk_size == 0)
		ramdisk_size = phys_initrd_size;

	वापस ramdisk_size;
पूर्ण

अटल व्योम __init relocate_initrd(व्योम)
अणु
	/* Assume only end is not page aligned */
	u64 ramdisk_image = get_ramdisk_image();
	u64 ramdisk_size  = get_ramdisk_size();
	u64 area_size     = PAGE_ALIGN(ramdisk_size);

	/* We need to move the initrd करोwn पूर्णांकo directly mapped mem */
	relocated_ramdisk = memblock_phys_alloc_range(area_size, PAGE_SIZE, 0,
						      PFN_PHYS(max_pfn_mapped));
	अगर (!relocated_ramdisk)
		panic("Cannot find place for new RAMDISK of size %lld\n",
		      ramdisk_size);

	initrd_start = relocated_ramdisk + PAGE_OFFSET;
	initrd_end   = initrd_start + ramdisk_size;
	prपूर्णांकk(KERN_INFO "Allocated new RAMDISK: [mem %#010llx-%#010llx]\n",
	       relocated_ramdisk, relocated_ramdisk + ramdisk_size - 1);

	copy_from_early_mem((व्योम *)initrd_start, ramdisk_image, ramdisk_size);

	prपूर्णांकk(KERN_INFO "Move RAMDISK from [mem %#010llx-%#010llx] to"
		" [mem %#010llx-%#010llx]\n",
		ramdisk_image, ramdisk_image + ramdisk_size - 1,
		relocated_ramdisk, relocated_ramdisk + ramdisk_size - 1);
पूर्ण

अटल व्योम __init early_reserve_initrd(व्योम)
अणु
	/* Assume only end is not page aligned */
	u64 ramdisk_image = get_ramdisk_image();
	u64 ramdisk_size  = get_ramdisk_size();
	u64 ramdisk_end   = PAGE_ALIGN(ramdisk_image + ramdisk_size);

	अगर (!boot_params.hdr.type_of_loader ||
	    !ramdisk_image || !ramdisk_size)
		वापस;		/* No initrd provided by bootloader */

	memblock_reserve(ramdisk_image, ramdisk_end - ramdisk_image);
पूर्ण

अटल व्योम __init reserve_initrd(व्योम)
अणु
	/* Assume only end is not page aligned */
	u64 ramdisk_image = get_ramdisk_image();
	u64 ramdisk_size  = get_ramdisk_size();
	u64 ramdisk_end   = PAGE_ALIGN(ramdisk_image + ramdisk_size);

	अगर (!boot_params.hdr.type_of_loader ||
	    !ramdisk_image || !ramdisk_size)
		वापस;		/* No initrd provided by bootloader */

	initrd_start = 0;

	prपूर्णांकk(KERN_INFO "RAMDISK: [mem %#010llx-%#010llx]\n", ramdisk_image,
			ramdisk_end - 1);

	अगर (pfn_range_is_mapped(PFN_DOWN(ramdisk_image),
				PFN_DOWN(ramdisk_end))) अणु
		/* All are mapped, easy हाल */
		initrd_start = ramdisk_image + PAGE_OFFSET;
		initrd_end = initrd_start + ramdisk_size;
		वापस;
	पूर्ण

	relocate_initrd();

	memblock_मुक्त(ramdisk_image, ramdisk_end - ramdisk_image);
पूर्ण

#अन्यथा
अटल व्योम __init early_reserve_initrd(व्योम)
अणु
पूर्ण
अटल व्योम __init reserve_initrd(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

अटल व्योम __init parse_setup_data(व्योम)
अणु
	काष्ठा setup_data *data;
	u64 pa_data, pa_next;

	pa_data = boot_params.hdr.setup_data;
	जबतक (pa_data) अणु
		u32 data_len, data_type;

		data = early_memremap(pa_data, माप(*data));
		data_len = data->len + माप(काष्ठा setup_data);
		data_type = data->type;
		pa_next = data->next;
		early_memunmap(data, माप(*data));

		चयन (data_type) अणु
		हाल SETUP_E820_EXT:
			e820__memory_setup_extended(pa_data, data_len);
			अवरोध;
		हाल SETUP_DTB:
			add_dtb(pa_data);
			अवरोध;
		हाल SETUP_EFI:
			parse_efi_setup(pa_data, data_len);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		pa_data = pa_next;
	पूर्ण
पूर्ण

अटल व्योम __init memblock_x86_reserve_range_setup_data(व्योम)
अणु
	काष्ठा setup_data *data;
	u64 pa_data;

	pa_data = boot_params.hdr.setup_data;
	जबतक (pa_data) अणु
		data = early_memremap(pa_data, माप(*data));
		memblock_reserve(pa_data, माप(*data) + data->len);

		अगर (data->type == SETUP_INसूचीECT &&
		    ((काष्ठा setup_indirect *)data->data)->type != SETUP_INसूचीECT)
			memblock_reserve(((काष्ठा setup_indirect *)data->data)->addr,
					 ((काष्ठा setup_indirect *)data->data)->len);

		pa_data = data->next;
		early_memunmap(data, माप(*data));
	पूर्ण
पूर्ण

/*
 * --------- Crashkernel reservation ------------------------------
 */

#अगर_घोषित CONFIG_KEXEC_CORE

/* 16M alignment क्रम crash kernel regions */
#घोषणा CRASH_ALIGN		SZ_16M

/*
 * Keep the crash kernel below this limit.
 *
 * Earlier 32-bits kernels would limit the kernel to the low 512 MB range
 * due to mapping restrictions.
 *
 * 64-bit kdump kernels need to be restricted to be under 64 TB, which is
 * the upper limit of प्रणाली RAM in 4-level paging mode. Since the kdump
 * jump could be from 5-level paging to 4-level paging, the jump will fail अगर
 * the kernel is put above 64 TB, and during the 1st kernel bootup there's
 * no good way to detect the paging mode of the target kernel which will be
 * loaded क्रम dumping.
 */
#अगर_घोषित CONFIG_X86_32
# define CRASH_ADDR_LOW_MAX	SZ_512M
# define CRASH_ADDR_HIGH_MAX	SZ_512M
#अन्यथा
# define CRASH_ADDR_LOW_MAX	SZ_4G
# define CRASH_ADDR_HIGH_MAX	SZ_64T
#पूर्ण_अगर

अटल पूर्णांक __init reserve_crashkernel_low(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	अचिन्हित दीर्घ दीर्घ base, low_base = 0, low_size = 0;
	अचिन्हित दीर्घ low_mem_limit;
	पूर्णांक ret;

	low_mem_limit = min(memblock_phys_mem_size(), CRASH_ADDR_LOW_MAX);

	/* crashkernel=Y,low */
	ret = parse_crashkernel_low(boot_command_line, low_mem_limit, &low_size, &base);
	अगर (ret) अणु
		/*
		 * two parts from kernel/dma/swiotlb.c:
		 * -swiotlb size: user-specअगरied with swiotlb= or शेष.
		 *
		 * -swiotlb overflow buffer: now hardcoded to 32k. We round it
		 * to 8M क्रम other buffers that may need to stay low too. Also
		 * make sure we allocate enough extra low memory so that we
		 * करोn't run out of DMA buffers क्रम 32-bit devices.
		 */
		low_size = max(swiotlb_size_or_शेष() + (8UL << 20), 256UL << 20);
	पूर्ण अन्यथा अणु
		/* passed with crashkernel=0,low ? */
		अगर (!low_size)
			वापस 0;
	पूर्ण

	low_base = memblock_phys_alloc_range(low_size, CRASH_ALIGN, 0, CRASH_ADDR_LOW_MAX);
	अगर (!low_base) अणु
		pr_err("Cannot reserve %ldMB crashkernel low memory, please try smaller size.\n",
		       (अचिन्हित दीर्घ)(low_size >> 20));
		वापस -ENOMEM;
	पूर्ण

	pr_info("Reserving %ldMB of low memory at %ldMB for crashkernel (low RAM limit: %ldMB)\n",
		(अचिन्हित दीर्घ)(low_size >> 20),
		(अचिन्हित दीर्घ)(low_base >> 20),
		(अचिन्हित दीर्घ)(low_mem_limit >> 20));

	crashk_low_res.start = low_base;
	crashk_low_res.end   = low_base + low_size - 1;
	insert_resource(&iomem_resource, &crashk_low_res);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __init reserve_crashkernel(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ crash_size, crash_base, total_mem;
	bool high = false;
	पूर्णांक ret;

	total_mem = memblock_phys_mem_size();

	/* crashkernel=XM */
	ret = parse_crashkernel(boot_command_line, total_mem, &crash_size, &crash_base);
	अगर (ret != 0 || crash_size <= 0) अणु
		/* crashkernel=X,high */
		ret = parse_crashkernel_high(boot_command_line, total_mem,
					     &crash_size, &crash_base);
		अगर (ret != 0 || crash_size <= 0)
			वापस;
		high = true;
	पूर्ण

	अगर (xen_pv_करोमुख्य()) अणु
		pr_info("Ignoring crashkernel for a Xen PV domain\n");
		वापस;
	पूर्ण

	/* 0 means: find the address स्वतःmatically */
	अगर (!crash_base) अणु
		/*
		 * Set CRASH_ADDR_LOW_MAX upper bound क्रम crash memory,
		 * crashkernel=x,high reserves memory over 4G, also allocates
		 * 256M extra low memory क्रम DMA buffers and swiotlb.
		 * But the extra memory is not required क्रम all machines.
		 * So try low memory first and fall back to high memory
		 * unless "crashkernel=size[KMG],high" is specअगरied.
		 */
		अगर (!high)
			crash_base = memblock_phys_alloc_range(crash_size,
						CRASH_ALIGN, CRASH_ALIGN,
						CRASH_ADDR_LOW_MAX);
		अगर (!crash_base)
			crash_base = memblock_phys_alloc_range(crash_size,
						CRASH_ALIGN, CRASH_ALIGN,
						CRASH_ADDR_HIGH_MAX);
		अगर (!crash_base) अणु
			pr_info("crashkernel reservation failed - No suitable area found.\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ दीर्घ start;

		start = memblock_phys_alloc_range(crash_size, SZ_1M, crash_base,
						  crash_base + crash_size);
		अगर (start != crash_base) अणु
			pr_info("crashkernel reservation failed - memory is in use.\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (crash_base >= (1ULL << 32) && reserve_crashkernel_low()) अणु
		memblock_मुक्त(crash_base, crash_size);
		वापस;
	पूर्ण

	pr_info("Reserving %ldMB of memory at %ldMB for crashkernel (System RAM: %ldMB)\n",
		(अचिन्हित दीर्घ)(crash_size >> 20),
		(अचिन्हित दीर्घ)(crash_base >> 20),
		(अचिन्हित दीर्घ)(total_mem >> 20));

	crashk_res.start = crash_base;
	crashk_res.end   = crash_base + crash_size - 1;
	insert_resource(&iomem_resource, &crashk_res);
पूर्ण
#अन्यथा
अटल व्योम __init reserve_crashkernel(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल काष्ठा resource standard_io_resources[] = अणु
	अणु .name = "dma1", .start = 0x00, .end = 0x1f,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "pic1", .start = 0x20, .end = 0x21,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "timer0", .start = 0x40, .end = 0x43,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "timer1", .start = 0x50, .end = 0x53,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "keyboard", .start = 0x60, .end = 0x60,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "keyboard", .start = 0x64, .end = 0x64,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "dma page reg", .start = 0x80, .end = 0x8f,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "pic2", .start = 0xa0, .end = 0xa1,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "dma2", .start = 0xc0, .end = 0xdf,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण,
	अणु .name = "fpu", .start = 0xf0, .end = 0xff,
		.flags = IORESOURCE_BUSY | IORESOURCE_IO पूर्ण
पूर्ण;

व्योम __init reserve_standard_io_resources(व्योम)
अणु
	पूर्णांक i;

	/* request I/O space क्रम devices used on all i[345]86 PCs */
	क्रम (i = 0; i < ARRAY_SIZE(standard_io_resources); i++)
		request_resource(&ioport_resource, &standard_io_resources[i]);

पूर्ण

अटल __init व्योम reserve_ibft_region(व्योम)
अणु
	अचिन्हित दीर्घ addr, size = 0;

	addr = find_ibft_region(&size);

	अगर (size)
		memblock_reserve(addr, size);
पूर्ण

अटल bool __init snb_gfx_workaround_needed(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	पूर्णांक i;
	u16 venकरोr, devid;
	अटल स्थिर __initस्थिर u16 snb_ids[] = अणु
		0x0102,
		0x0112,
		0x0122,
		0x0106,
		0x0116,
		0x0126,
		0x010a,
	पूर्ण;

	/* Assume no अगर something weird is going on with PCI */
	अगर (!early_pci_allowed())
		वापस false;

	venकरोr = पढ़ो_pci_config_16(0, 2, 0, PCI_VENDOR_ID);
	अगर (venकरोr != 0x8086)
		वापस false;

	devid = पढ़ो_pci_config_16(0, 2, 0, PCI_DEVICE_ID);
	क्रम (i = 0; i < ARRAY_SIZE(snb_ids); i++)
		अगर (devid == snb_ids[i])
			वापस true;
#पूर्ण_अगर

	वापस false;
पूर्ण

/*
 * Sandy Bridge graphics has trouble with certain ranges, exclude
 * them from allocation.
 */
अटल व्योम __init trim_snb_memory(व्योम)
अणु
	अटल स्थिर __initस्थिर अचिन्हित दीर्घ bad_pages[] = अणु
		0x20050000,
		0x20110000,
		0x20130000,
		0x20138000,
		0x40004000,
	पूर्ण;
	पूर्णांक i;

	अगर (!snb_gfx_workaround_needed())
		वापस;

	prपूर्णांकk(KERN_DEBUG "reserving inaccessible SNB gfx pages\n");

	/*
	 * SandyBridge पूर्णांकegrated graphics devices have a bug that prevents
	 * them from accessing certain memory ranges, namely anything below
	 * 1M and in the pages listed in bad_pages[] above.
	 *
	 * To aव्योम these pages being ever accessed by SNB gfx devices reserve
	 * bad_pages that have not alपढ़ोy been reserved at boot समय.
	 * All memory below the 1 MB mark is anyway reserved later during
	 * setup_arch(), so there is no need to reserve it here.
	 */

	क्रम (i = 0; i < ARRAY_SIZE(bad_pages); i++) अणु
		अगर (memblock_reserve(bad_pages[i], PAGE_SIZE))
			prपूर्णांकk(KERN_WARNING "failed to reserve 0x%08lx\n",
			       bad_pages[i]);
	पूर्ण
पूर्ण

अटल व्योम __init trim_bios_range(व्योम)
अणु
	/*
	 * A special हाल is the first 4Kb of memory;
	 * This is a BIOS owned area, not kernel ram, but generally
	 * not listed as such in the E820 table.
	 *
	 * This typically reserves additional memory (64KiB by शेष)
	 * since some BIOSes are known to corrupt low memory.  See the
	 * Kconfig help text क्रम X86_RESERVE_LOW.
	 */
	e820__range_update(0, PAGE_SIZE, E820_TYPE_RAM, E820_TYPE_RESERVED);

	/*
	 * special हाल: Some BIOSes report the PC BIOS
	 * area (640Kb -> 1Mb) as RAM even though it is not.
	 * take them out.
	 */
	e820__range_हटाओ(BIOS_BEGIN, BIOS_END - BIOS_BEGIN, E820_TYPE_RAM, 1);

	e820__update_table(e820_table);
पूर्ण

/* called beक्रमe trim_bios_range() to spare extra sanitize */
अटल व्योम __init e820_add_kernel_range(व्योम)
अणु
	u64 start = __pa_symbol(_text);
	u64 size = __pa_symbol(_end) - start;

	/*
	 * Complain अगर .text .data and .bss are not marked as E820_TYPE_RAM and
	 * attempt to fix it by adding the range. We may have a confused BIOS,
	 * or the user may have used memmap=exacपंचांगap or memmap=xxM$yyM to
	 * exclude kernel range. If we really are running on top non-RAM,
	 * we will crash later anyways.
	 */
	अगर (e820__mapped_all(start, start + size, E820_TYPE_RAM))
		वापस;

	pr_warn(".text .data .bss are not marked as E820_TYPE_RAM!\n");
	e820__range_हटाओ(start, size, E820_TYPE_RAM, 0);
	e820__range_add(start, size, E820_TYPE_RAM);
पूर्ण

अटल अचिन्हित reserve_low = CONFIG_X86_RESERVE_LOW << 10;

अटल पूर्णांक __init parse_reservelow(अक्षर *p)
अणु
	अचिन्हित दीर्घ दीर्घ size;

	अगर (!p)
		वापस -EINVAL;

	size = memparse(p, &p);

	अगर (size < 4096)
		size = 4096;

	अगर (size > 640*1024)
		size = 640*1024;

	reserve_low = size;

	वापस 0;
पूर्ण

early_param("reservelow", parse_reservelow);

अटल व्योम __init early_reserve_memory(व्योम)
अणु
	/*
	 * Reserve the memory occupied by the kernel between _text and
	 * __end_of_kernel_reserve symbols. Any kernel sections after the
	 * __end_of_kernel_reserve symbol must be explicitly reserved with a
	 * separate memblock_reserve() or they will be discarded.
	 */
	memblock_reserve(__pa_symbol(_text),
			 (अचिन्हित दीर्घ)__end_of_kernel_reserve - (अचिन्हित दीर्घ)_text);

	/*
	 * The first 4Kb of memory is a BIOS owned area, but generally it is
	 * not listed as such in the E820 table.
	 *
	 * Reserve the first 64K of memory since some BIOSes are known to
	 * corrupt low memory. After the real mode trampoline is allocated the
	 * rest of the memory below 640k is reserved.
	 *
	 * In addition, make sure page 0 is always reserved because on
	 * प्रणालीs with L1TF its contents can be leaked to user processes.
	 */
	memblock_reserve(0, SZ_64K);

	early_reserve_initrd();

	अगर (efi_enabled(EFI_BOOT))
		efi_memblock_x86_reserve_range();

	memblock_x86_reserve_range_setup_data();

	reserve_ibft_region();
	reserve_bios_regions();
	trim_snb_memory();
पूर्ण

/*
 * Dump out kernel offset inक्रमmation on panic.
 */
अटल पूर्णांक
dump_kernel_offset(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ v, व्योम *p)
अणु
	अगर (kaslr_enabled()) अणु
		pr_emerg("Kernel Offset: 0x%lx from 0x%lx (relocation range: 0x%lx-0x%lx)\n",
			 kaslr_offset(),
			 __START_KERNEL,
			 __START_KERNEL_map,
			 MODULES_VADDR-1);
	पूर्ण अन्यथा अणु
		pr_emerg("Kernel Offset: disabled\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Determine अगर we were loaded by an EFI loader.  If so, then we have also been
 * passed the efi memmap, systab, etc., so we should use these data काष्ठाures
 * क्रम initialization.  Note, the efi init code path is determined by the
 * global efi_enabled. This allows the same kernel image to be used on existing
 * प्रणालीs (with a traditional BIOS) as well as on EFI प्रणालीs.
 */
/*
 * setup_arch - architecture-specअगरic boot-समय initializations
 *
 * Note: On x86_64, fixmaps are पढ़ोy क्रम use even beक्रमe this is called.
 */

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
#अगर_घोषित CONFIG_X86_32
	स_नकल(&boot_cpu_data, &new_cpu_data, माप(new_cpu_data));

	/*
	 * copy kernel address range established so far and चयन
	 * to the proper swapper page table
	 */
	clone_pgd_range(swapper_pg_dir     + KERNEL_PGD_BOUNDARY,
			initial_page_table + KERNEL_PGD_BOUNDARY,
			KERNEL_PGD_PTRS);

	load_cr3(swapper_pg_dir);
	/*
	 * Note: Quark X1000 CPUs advertise PGE incorrectly and require
	 * a cr3 based tlb flush, so the following __flush_tlb_all()
	 * will not flush anything because the CPU quirk which clears
	 * X86_FEATURE_PGE has not been invoked yet. Though due to the
	 * load_cr3() above the TLB has been flushed alपढ़ोy. The
	 * quirk is invoked beक्रमe subsequent calls to __flush_tlb_all()
	 * so proper operation is guaranteed.
	 */
	__flush_tlb_all();
#अन्यथा
	prपूर्णांकk(KERN_INFO "Command line: %s\n", boot_command_line);
	boot_cpu_data.x86_phys_bits = MAX_PHYSMEM_BITS;
#पूर्ण_अगर

	/*
	 * If we have OLPC OFW, we might end up relocating the fixmap due to
	 * reserve_top(), so करो this beक्रमe touching the ioremap area.
	 */
	olpc_ofw_detect();

	idt_setup_early_traps();
	early_cpu_init();
	jump_label_init();
	अटल_call_init();
	early_ioremap_init();

	setup_olpc_ofw_pgd();

	ROOT_DEV = old_decode_dev(boot_params.hdr.root_dev);
	screen_info = boot_params.screen_info;
	edid_info = boot_params.edid_info;
#अगर_घोषित CONFIG_X86_32
	apm_info.bios = boot_params.apm_bios_info;
	ist_info = boot_params.ist_info;
#पूर्ण_अगर
	saved_video_mode = boot_params.hdr.vid_mode;
	bootloader_type = boot_params.hdr.type_of_loader;
	अगर ((bootloader_type >> 4) == 0xe) अणु
		bootloader_type &= 0xf;
		bootloader_type |= (boot_params.hdr.ext_loader_type+0x10) << 4;
	पूर्ण
	bootloader_version  = bootloader_type & 0xf;
	bootloader_version |= boot_params.hdr.ext_loader_ver << 4;

#अगर_घोषित CONFIG_BLK_DEV_RAM
	rd_image_start = boot_params.hdr.ram_size & RAMDISK_IMAGE_START_MASK;
#पूर्ण_अगर
#अगर_घोषित CONFIG_EFI
	अगर (!म_भेदन((अक्षर *)&boot_params.efi_info.efi_loader_signature,
		     EFI32_LOADER_SIGNATURE, 4)) अणु
		set_bit(EFI_BOOT, &efi.flags);
	पूर्ण अन्यथा अगर (!म_भेदन((अक्षर *)&boot_params.efi_info.efi_loader_signature,
		     EFI64_LOADER_SIGNATURE, 4)) अणु
		set_bit(EFI_BOOT, &efi.flags);
		set_bit(EFI_64BIT, &efi.flags);
	पूर्ण
#पूर्ण_अगर

	x86_init.oem.arch_setup();

	iomem_resource.end = (1ULL << boot_cpu_data.x86_phys_bits) - 1;
	e820__memory_setup();
	parse_setup_data();

	copy_edd();

	अगर (!boot_params.hdr.root_flags)
		root_mountflags &= ~MS_RDONLY;
	init_mm.start_code = (अचिन्हित दीर्घ) _text;
	init_mm.end_code = (अचिन्हित दीर्घ) _etext;
	init_mm.end_data = (अचिन्हित दीर्घ) _edata;
	init_mm.brk = _brk_end;

	code_resource.start = __pa_symbol(_text);
	code_resource.end = __pa_symbol(_etext)-1;
	rodata_resource.start = __pa_symbol(__start_rodata);
	rodata_resource.end = __pa_symbol(__end_rodata)-1;
	data_resource.start = __pa_symbol(_sdata);
	data_resource.end = __pa_symbol(_edata)-1;
	bss_resource.start = __pa_symbol(__bss_start);
	bss_resource.end = __pa_symbol(__bss_stop)-1;

#अगर_घोषित CONFIG_CMDLINE_BOOL
#अगर_घोषित CONFIG_CMDLINE_OVERRIDE
	strlcpy(boot_command_line, builtin_cmdline, COMMAND_LINE_SIZE);
#अन्यथा
	अगर (builtin_cmdline[0]) अणु
		/* append boot loader cmdline to builtin */
		strlcat(builtin_cmdline, " ", COMMAND_LINE_SIZE);
		strlcat(builtin_cmdline, boot_command_line, COMMAND_LINE_SIZE);
		strlcpy(boot_command_line, builtin_cmdline, COMMAND_LINE_SIZE);
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

	strlcpy(command_line, boot_command_line, COMMAND_LINE_SIZE);
	*cmdline_p = command_line;

	/*
	 * x86_configure_nx() is called beक्रमe parse_early_param() to detect
	 * whether hardware करोesn't support NX (so that the early EHCI debug
	 * console setup can safely call set_fixmap()). It may then be called
	 * again from within noexec_setup() during parsing early parameters
	 * to honor the respective command line option.
	 */
	x86_configure_nx();

	parse_early_param();

	/*
	 * Do some memory reservations *beक्रमe* memory is added to
	 * memblock, so memblock allocations won't overग_लिखो it.
	 * Do it after early param, so we could get (unlikely) panic from
	 * serial.
	 *
	 * After this poपूर्णांक everything still needed from the boot loader or
	 * firmware or kernel text should be early reserved or marked not
	 * RAM in e820. All other memory is मुक्त game.
	 */
	early_reserve_memory();

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
	/*
	 * Memory used by the kernel cannot be hot-हटाओd because Linux
	 * cannot migrate the kernel pages. When memory hotplug is
	 * enabled, we should prevent memblock from allocating memory
	 * क्रम the kernel.
	 *
	 * ACPI SRAT records all hotpluggable memory ranges. But beक्रमe
	 * SRAT is parsed, we करोn't know about it.
	 *
	 * The kernel image is loaded पूर्णांकo memory at very early समय. We
	 * cannot prevent this anyway. So on NUMA प्रणाली, we set any
	 * node the kernel resides in as un-hotpluggable.
	 *
	 * Since on modern servers, one node could have द्विगुन-digit
	 * gigabytes memory, we can assume the memory around the kernel
	 * image is also un-hotpluggable. So beक्रमe SRAT is parsed, just
	 * allocate memory near the kernel image to try the best to keep
	 * the kernel away from hotpluggable memory.
	 */
	अगर (movable_node_is_enabled())
		memblock_set_bottom_up(true);
#पूर्ण_अगर

	x86_report_nx();

	अगर (acpi_mps_check()) अणु
#अगर_घोषित CONFIG_X86_LOCAL_APIC
		disable_apic = 1;
#पूर्ण_अगर
		setup_clear_cpu_cap(X86_FEATURE_APIC);
	पूर्ण

	e820__reserve_setup_data();
	e820__finish_early_params();

	अगर (efi_enabled(EFI_BOOT))
		efi_init();

	dmi_setup();

	/*
	 * VMware detection requires dmi to be available, so this
	 * needs to be करोne after dmi_setup(), क्रम the boot CPU.
	 */
	init_hypervisor_platक्रमm();

	tsc_early_init();
	x86_init.resources.probe_roms();

	/* after parse_early_param, so could debug it */
	insert_resource(&iomem_resource, &code_resource);
	insert_resource(&iomem_resource, &rodata_resource);
	insert_resource(&iomem_resource, &data_resource);
	insert_resource(&iomem_resource, &bss_resource);

	e820_add_kernel_range();
	trim_bios_range();
#अगर_घोषित CONFIG_X86_32
	अगर (ppro_with_ram_bug()) अणु
		e820__range_update(0x70000000ULL, 0x40000ULL, E820_TYPE_RAM,
				  E820_TYPE_RESERVED);
		e820__update_table(e820_table);
		prपूर्णांकk(KERN_INFO "fixed physical RAM map:\n");
		e820__prपूर्णांक_table("bad_ppro");
	पूर्ण
#अन्यथा
	early_gart_iommu_check();
#पूर्ण_अगर

	/*
	 * partially used pages are not usable - thus
	 * we are rounding upwards:
	 */
	max_pfn = e820__end_of_ram_pfn();

	/* update e820 क्रम memory not covered by WB MTRRs */
	mtrr_bp_init();
	अगर (mtrr_trim_uncached_memory(max_pfn))
		max_pfn = e820__end_of_ram_pfn();

	max_possible_pfn = max_pfn;

	/*
	 * This call is required when the CPU करोes not support PAT. If
	 * mtrr_bp_init() invoked it alपढ़ोy via pat_init() the call has no
	 * effect.
	 */
	init_cache_modes();

	/*
	 * Define अक्रमom base addresses क्रम memory sections after max_pfn is
	 * defined and beक्रमe each memory section base is used.
	 */
	kernel_अक्रमomize_memory();

#अगर_घोषित CONFIG_X86_32
	/* max_low_pfn get updated here */
	find_low_pfn_range();
#अन्यथा
	check_x2apic();

	/* How many end-of-memory variables you have, gअक्रमma! */
	/* need this beक्रमe calling reserve_initrd */
	अगर (max_pfn > (1UL<<(32 - PAGE_SHIFT)))
		max_low_pfn = e820__end_of_low_ram_pfn();
	अन्यथा
		max_low_pfn = max_pfn;

	high_memory = (व्योम *)__va(max_pfn * PAGE_SIZE - 1) + 1;
#पूर्ण_अगर

	/*
	 * Find and reserve possible boot-समय SMP configuration:
	 */
	find_smp_config();

	early_alloc_pgt_buf();

	/*
	 * Need to conclude brk, beक्रमe e820__memblock_setup()
	 * it could use memblock_find_in_range, could overlap with
	 * brk area.
	 */
	reserve_brk();

	cleanup_highmap();

	memblock_set_current_limit(ISA_END_ADDRESS);
	e820__memblock_setup();

	/*
	 * Needs to run after memblock setup because it needs the physical
	 * memory size.
	 */
	sev_setup_arch();

	efi_fake_memmap();
	efi_find_mirror();
	efi_esrt_init();
	efi_mokvar_table_init();

	/*
	 * The EFI specअगरication says that boot service code won't be
	 * called after ExitBootServices(). This is, in fact, a lie.
	 */
	efi_reserve_boot_services();

	/* pपुनः_स्मृतिate 4k क्रम mptable mpc */
	e820__memblock_alloc_reserved_mpc_new();

#अगर_घोषित CONFIG_X86_CHECK_BIOS_CORRUPTION
	setup_bios_corruption_check();
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
	prपूर्णांकk(KERN_DEBUG "initial memory mapped: [mem 0x00000000-%#010lx]\n",
			(max_pfn_mapped<<PAGE_SHIFT) - 1);
#पूर्ण_अगर

	/*
	 * Find मुक्त memory क्रम the real mode trampoline and place it
	 * there.
	 * If there is not enough मुक्त memory under 1M, on EFI-enabled
	 * प्रणालीs there will be additional attempt to reclaim the memory
	 * क्रम the real mode trampoline at efi_मुक्त_boot_services().
	 *
	 * Unconditionally reserve the entire first 1M of RAM because
	 * BIOSes are know to corrupt low memory and several
	 * hundred kilobytes are not worth complex detection what memory माला_लो
	 * clobbered. Moreover, on machines with SandyBridge graphics or in
	 * setups that use crashkernel the entire 1M is reserved anyway.
	 */
	reserve_real_mode();

	init_mem_mapping();

	idt_setup_early_pf();

	/*
	 * Update mmu_cr4_features (and, indirectly, trampoline_cr4_features)
	 * with the current CR4 value.  This may not be necessary, but
	 * auditing all the early-boot CR4 manipulation would be needed to
	 * rule it out.
	 *
	 * Mask off features that करोn't work outside दीर्घ mode (just
	 * PCIDE क्रम now).
	 */
	mmu_cr4_features = __पढ़ो_cr4() & ~X86_CR4_PCIDE;

	memblock_set_current_limit(get_max_mapped());

	/*
	 * NOTE: On x86-32, only from this poपूर्णांक on, fixmaps are पढ़ोy क्रम use.
	 */

#अगर_घोषित CONFIG_PROVIDE_OHCI1394_DMA_INIT
	अगर (init_ohci1394_dma_early)
		init_ohci1394_dma_on_all_controllers();
#पूर्ण_अगर
	/* Allocate bigger log buffer */
	setup_log_buf(1);

	अगर (efi_enabled(EFI_BOOT)) अणु
		चयन (boot_params.secure_boot) अणु
		हाल efi_secureboot_mode_disabled:
			pr_info("Secure boot disabled\n");
			अवरोध;
		हाल efi_secureboot_mode_enabled:
			pr_info("Secure boot enabled\n");
			अवरोध;
		शेष:
			pr_info("Secure boot could not be determined\n");
			अवरोध;
		पूर्ण
	पूर्ण

	reserve_initrd();

	acpi_table_upgrade();
	/* Look क्रम ACPI tables and reserve memory occupied by them. */
	acpi_boot_table_init();

	vsmp_init();

	io_delay_init();

	early_platक्रमm_quirks();

	early_acpi_boot_init();

	iniपंचांगem_init();
	dma_contiguous_reserve(max_pfn_mapped << PAGE_SHIFT);

	अगर (boot_cpu_has(X86_FEATURE_GBPAGES))
		hugetlb_cma_reserve(PUD_SHIFT - PAGE_SHIFT);

	/*
	 * Reserve memory क्रम crash kernel after SRAT is parsed so that it
	 * won't consume hotpluggable memory.
	 */
	reserve_crashkernel();

	memblock_find_dma_reserve();

	अगर (!early_xdbc_setup_hardware())
		early_xdbc_रेजिस्टर_console();

	x86_init.paging.pagetable_init();

	kasan_init();

	/*
	 * Sync back kernel address range.
	 *
	 * FIXME: Can the later sync in setup_cpu_entry_areas() replace
	 * this call?
	 */
	sync_initial_page_table();

	tboot_probe();

	map_vsyscall();

	generic_apic_probe();

	early_quirks();

	/*
	 * Read APIC and some other early inक्रमmation from ACPI tables.
	 */
	acpi_boot_init();
	x86_dtb_init();

	/*
	 * get boot-समय SMP configuration:
	 */
	get_smp_config();

	/*
	 * Systems w/o ACPI and mptables might not have it mapped the local
	 * APIC yet, but prefill_possible_map() might need to access it.
	 */
	init_apic_mappings();

	prefill_possible_map();

	init_cpu_to_node();
	init_gi_nodes();

	io_apic_init_mappings();

	x86_init.hyper.guest_late_init();

	e820__reserve_resources();
	e820__रेजिस्टर_nosave_regions(max_pfn);

	x86_init.resources.reserve_resources();

	e820__setup_pci_gap();

#अगर_घोषित CONFIG_VT
#अगर defined(CONFIG_VGA_CONSOLE)
	अगर (!efi_enabled(EFI_BOOT) || (efi_mem_type(0xa0000) != EFI_CONVENTIONAL_MEMORY))
		conचयनp = &vga_con;
#पूर्ण_अगर
#पूर्ण_अगर
	x86_init.oem.banner();

	x86_init.समयrs.wallघड़ी_init();

	/*
	 * This needs to run beक्रमe setup_local_APIC() which soft-disables the
	 * local APIC temporarily and that masks the thermal LVT पूर्णांकerrupt,
	 * leading to softlockups on machines which have configured SMI
	 * पूर्णांकerrupt delivery.
	 */
	therm_lvt_init();

	mcheck_init();

	रेजिस्टर_refined_jअगरfies(CLOCK_TICK_RATE);

#अगर_घोषित CONFIG_EFI
	अगर (efi_enabled(EFI_BOOT))
		efi_apply_memmap_quirks();
#पूर्ण_अगर

	unwind_init();
पूर्ण

#अगर_घोषित CONFIG_X86_32

अटल काष्ठा resource video_ram_resource = अणु
	.name	= "Video RAM area",
	.start	= 0xa0000,
	.end	= 0xbffff,
	.flags	= IORESOURCE_BUSY | IORESOURCE_MEM
पूर्ण;

व्योम __init i386_reserve_resources(व्योम)
अणु
	request_resource(&iomem_resource, &video_ram_resource);
	reserve_standard_io_resources();
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_32 */

अटल काष्ठा notअगरier_block kernel_offset_notअगरier = अणु
	.notअगरier_call = dump_kernel_offset
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_kernel_offset_dumper(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					&kernel_offset_notअगरier);
	वापस 0;
पूर्ण
__initcall(रेजिस्टर_kernel_offset_dumper);
