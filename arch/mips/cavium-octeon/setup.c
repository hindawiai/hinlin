<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2007 Cavium Networks
 * Copyright (C) 2008, 2009 Wind River Systems
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/compiler.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/serial.h>
#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>	/* क्रम स_रखो */
#समावेश <linux/tty.h>
#समावेश <linux/समय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/kexec.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/octeon/pci-octeon.h>
#समावेश <यंत्र/octeon/cvmx-rst-defs.h>

/*
 * TRUE क्रम devices having रेजिस्टरs with little-endian byte
 * order, FALSE क्रम रेजिस्टरs with native-endian byte order.
 * PCI mandates little-endian, USB and SATA are configuraable,
 * but we chose little-endian क्रम these.
 */
स्थिर bool octeon_should_swizzle_table[256] = अणु
	[0x00] = true,	/* bootbus/CF */
	[0x1b] = true,	/* PCI mmio winकरोw */
	[0x1c] = true,	/* PCI mmio winकरोw */
	[0x1d] = true,	/* PCI mmio winकरोw */
	[0x1e] = true,	/* PCI mmio winकरोw */
	[0x68] = true,	/* OCTEON III USB */
	[0x69] = true,	/* OCTEON III USB */
	[0x6c] = true,	/* OCTEON III SATA */
	[0x6f] = true,	/* OCTEON II USB */
पूर्ण;
EXPORT_SYMBOL(octeon_should_swizzle_table);

#अगर_घोषित CONFIG_PCI
बाह्य व्योम pci_console_init(स्थिर अक्षर *arg);
#पूर्ण_अगर

अटल अचिन्हित दीर्घ दीर्घ max_memory = ULदीर्घ_उच्च;
अटल अचिन्हित दीर्घ दीर्घ reserve_low_mem;

DEFINE_SEMAPHORE(octeon_bootbus_sem);
EXPORT_SYMBOL(octeon_bootbus_sem);

अटल काष्ठा octeon_boot_descriptor *octeon_boot_desc_ptr;

काष्ठा cvmx_bootinfo *octeon_bootinfo;
EXPORT_SYMBOL(octeon_bootinfo);

#अगर_घोषित CONFIG_KEXEC
#अगर_घोषित CONFIG_SMP
/*
 * Wait क्रम relocation code is prepared and send
 * secondary CPUs to spin until kernel is relocated.
 */
अटल व्योम octeon_kexec_smp_करोwn(व्योम *ignored)
अणु
	पूर्णांक cpu = smp_processor_id();

	local_irq_disable();
	set_cpu_online(cpu, false);
	जबतक (!atomic_पढ़ो(&kexec_पढ़ोy_to_reboot))
		cpu_relax();

	यंत्र अस्थिर (
	"	sync						\n"
	"	synci	($0)					\n");

	kexec_reboot();
पूर्ण
#पूर्ण_अगर

#घोषणा OCTEON_DDR0_BASE    (0x0ULL)
#घोषणा OCTEON_DDR0_SIZE    (0x010000000ULL)
#घोषणा OCTEON_DDR1_BASE    (0x410000000ULL)
#घोषणा OCTEON_DDR1_SIZE    (0x010000000ULL)
#घोषणा OCTEON_DDR2_BASE    (0x020000000ULL)
#घोषणा OCTEON_DDR2_SIZE    (0x3e0000000ULL)
#घोषणा OCTEON_MAX_PHY_MEM_SIZE (16*1024*1024*1024ULL)

अटल काष्ठा kimage *kimage_ptr;

अटल व्योम kexec_booपंचांगem_init(uपूर्णांक64_t mem_size, uपूर्णांक32_t low_reserved_bytes)
अणु
	पूर्णांक64_t addr;
	काष्ठा cvmx_booपंचांगem_desc *booपंचांगem_desc;

	booपंचांगem_desc = cvmx_booपंचांगem_get_desc();

	अगर (mem_size > OCTEON_MAX_PHY_MEM_SIZE) अणु
		mem_size = OCTEON_MAX_PHY_MEM_SIZE;
		pr_err("Error: requested memory too large,"
		       "truncating to maximum size\n");
	पूर्ण

	booपंचांगem_desc->major_version = CVMX_BOOTMEM_DESC_MAJ_VER;
	booपंचांगem_desc->minor_version = CVMX_BOOTMEM_DESC_MIN_VER;

	addr = (OCTEON_DDR0_BASE + reserve_low_mem + low_reserved_bytes);
	booपंचांगem_desc->head_addr = 0;

	अगर (mem_size <= OCTEON_DDR0_SIZE) अणु
		__cvmx_booपंचांगem_phy_मुक्त(addr,
				mem_size - reserve_low_mem -
				low_reserved_bytes, 0);
		वापस;
	पूर्ण

	__cvmx_booपंचांगem_phy_मुक्त(addr,
			OCTEON_DDR0_SIZE - reserve_low_mem -
			low_reserved_bytes, 0);

	mem_size -= OCTEON_DDR0_SIZE;

	अगर (mem_size > OCTEON_DDR1_SIZE) अणु
		__cvmx_booपंचांगem_phy_मुक्त(OCTEON_DDR1_BASE, OCTEON_DDR1_SIZE, 0);
		__cvmx_booपंचांगem_phy_मुक्त(OCTEON_DDR2_BASE,
				mem_size - OCTEON_DDR1_SIZE, 0);
	पूर्ण अन्यथा
		__cvmx_booपंचांगem_phy_मुक्त(OCTEON_DDR1_BASE, mem_size, 0);
पूर्ण

अटल पूर्णांक octeon_kexec_prepare(काष्ठा kimage *image)
अणु
	पूर्णांक i;
	अक्षर *bootloader = "kexec";

	octeon_boot_desc_ptr->argc = 0;
	क्रम (i = 0; i < image->nr_segments; i++) अणु
		अगर (!म_भेदन(bootloader, (अक्षर *)image->segment[i].buf,
				म_माप(bootloader))) अणु
			/*
			 * convert command line string to array
			 * of parameters (as bootloader करोes).
			 */
			पूर्णांक argc = 0, offt;
			अक्षर *str = (अक्षर *)image->segment[i].buf;
			अक्षर *ptr = म_अक्षर(str, ' ');
			जबतक (ptr && (OCTEON_ARGV_MAX_ARGS > argc)) अणु
				*ptr = '\0';
				अगर (ptr[1] != ' ') अणु
					offt = (पूर्णांक)(ptr - str + 1);
					octeon_boot_desc_ptr->argv[argc] =
						image->segment[i].mem + offt;
					argc++;
				पूर्ण
				ptr = म_अक्षर(ptr + 1, ' ');
			पूर्ण
			octeon_boot_desc_ptr->argc = argc;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Inक्रमmation about segments will be needed during pre-boot memory
	 * initialization.
	 */
	kimage_ptr = image;
	वापस 0;
पूर्ण

अटल व्योम octeon_generic_shutकरोwn(व्योम)
अणु
	पूर्णांक i;
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;
#पूर्ण_अगर
	काष्ठा cvmx_booपंचांगem_desc *booपंचांगem_desc;
	व्योम *named_block_array_ptr;

	booपंचांगem_desc = cvmx_booपंचांगem_get_desc();
	named_block_array_ptr =
		cvmx_phys_to_ptr(booपंचांगem_desc->named_block_array_addr);

#अगर_घोषित CONFIG_SMP
	/* disable watchकरोgs */
	क्रम_each_online_cpu(cpu)
		cvmx_ग_लिखो_csr(CVMX_CIU_WDOGX(cpu_logical_map(cpu)), 0);
#अन्यथा
	cvmx_ग_लिखो_csr(CVMX_CIU_WDOGX(cvmx_get_core_num()), 0);
#पूर्ण_अगर
	अगर (kimage_ptr != kexec_crash_image) अणु
		स_रखो(named_block_array_ptr,
			0x0,
			CVMX_BOOTMEM_NUM_NAMED_BLOCKS *
			माप(काष्ठा cvmx_booपंचांगem_named_block_desc));
		/*
		 * Mark all memory (except low 0x100000 bytes) as मुक्त.
		 * It is the same thing that bootloader करोes.
		 */
		kexec_booपंचांगem_init(octeon_bootinfo->dram_size*1024ULL*1024ULL,
				0x100000);
		/*
		 * Allocate all segments to aव्योम their corruption during boot.
		 */
		क्रम (i = 0; i < kimage_ptr->nr_segments; i++)
			cvmx_booपंचांगem_alloc_address(
				kimage_ptr->segment[i].memsz + 2*PAGE_SIZE,
				kimage_ptr->segment[i].mem - PAGE_SIZE,
				PAGE_SIZE);
	पूर्ण अन्यथा अणु
		/*
		 * Do not mark all memory as मुक्त. Free only named sections
		 * leaving the rest of memory unchanged.
		 */
		काष्ठा cvmx_booपंचांगem_named_block_desc *ptr =
			(काष्ठा cvmx_booपंचांगem_named_block_desc *)
			named_block_array_ptr;

		क्रम (i = 0; i < booपंचांगem_desc->named_block_num_blocks; i++)
			अगर (ptr[i].size)
				cvmx_booपंचांगem_मुक्त_named(ptr[i].name);
	पूर्ण
	kexec_args[2] = 1UL; /* running on octeon_मुख्य_processor */
	kexec_args[3] = (अचिन्हित दीर्घ)octeon_boot_desc_ptr;
#अगर_घोषित CONFIG_SMP
	secondary_kexec_args[2] = 0UL; /* running on secondary cpu */
	secondary_kexec_args[3] = (अचिन्हित दीर्घ)octeon_boot_desc_ptr;
#पूर्ण_अगर
पूर्ण

अटल व्योम octeon_shutकरोwn(व्योम)
अणु
	octeon_generic_shutकरोwn();
#अगर_घोषित CONFIG_SMP
	smp_call_function(octeon_kexec_smp_करोwn, शून्य, 0);
	smp_wmb();
	जबतक (num_online_cpus() > 1) अणु
		cpu_relax();
		mdelay(1);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम octeon_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	octeon_generic_shutकरोwn();
	शेष_machine_crash_shutकरोwn(regs);
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम octeon_crash_smp_send_stop(व्योम)
अणु
	पूर्णांक cpu;

	/* disable watchकरोgs */
	क्रम_each_online_cpu(cpu)
		cvmx_ग_लिखो_csr(CVMX_CIU_WDOGX(cpu_logical_map(cpu)), 0);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_KEXEC */

#अगर_घोषित CONFIG_CAVIUM_RESERVE32
uपूर्णांक64_t octeon_reserve32_memory;
EXPORT_SYMBOL(octeon_reserve32_memory);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC
/* crashkernel cmdline parameter is parsed _after_ memory setup
 * we also parse it here (workaround क्रम EHB5200) */
अटल uपूर्णांक64_t crashk_size, crashk_base;
#पूर्ण_अगर

अटल पूर्णांक octeon_uart;

बाह्य यंत्रlinkage व्योम handle_पूर्णांक(व्योम);

/**
 * Return non zero अगर we are currently running in the Octeon simulator
 *
 * Returns
 */
पूर्णांक octeon_is_simulation(व्योम)
अणु
	वापस octeon_bootinfo->board_type == CVMX_BOARD_TYPE_SIM;
पूर्ण
EXPORT_SYMBOL(octeon_is_simulation);

/**
 * Return true अगर Octeon is in PCI Host mode. This means
 * Linux can control the PCI bus.
 *
 * Returns Non zero अगर Octeon in host mode.
 */
पूर्णांक octeon_is_pci_host(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	वापस octeon_bootinfo->config_flags & CVMX_BOOTINFO_CFG_FLAG_PCI_HOST;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * Get the घड़ी rate of Octeon
 *
 * Returns Clock rate in HZ
 */
uपूर्णांक64_t octeon_get_घड़ी_rate(व्योम)
अणु
	काष्ठा cvmx_sysinfo *sysinfo = cvmx_sysinfo_get();

	वापस sysinfo->cpu_घड़ी_hz;
पूर्ण
EXPORT_SYMBOL(octeon_get_घड़ी_rate);

अटल u64 octeon_io_घड़ी_rate;

u64 octeon_get_io_घड़ी_rate(व्योम)
अणु
	वापस octeon_io_घड़ी_rate;
पूर्ण
EXPORT_SYMBOL(octeon_get_io_घड़ी_rate);


/**
 * Write to the LCD display connected to the bootbus. This display
 * exists on most Cavium evaluation boards. If it करोesn't exist, then
 * this function करोesn't करो anything.
 *
 * @s:	    String to ग_लिखो
 */
अटल व्योम octeon_ग_लिखो_lcd(स्थिर अक्षर *s)
अणु
	अगर (octeon_bootinfo->led_display_base_addr) अणु
		व्योम __iomem *lcd_address =
			ioremap(octeon_bootinfo->led_display_base_addr,
					8);
		पूर्णांक i;
		क्रम (i = 0; i < 8; i++, s++) अणु
			अगर (*s)
				ioग_लिखो8(*s, lcd_address + i);
			अन्यथा
				ioग_लिखो8(' ', lcd_address + i);
		पूर्ण
		iounmap(lcd_address);
	पूर्ण
पूर्ण

/**
 * Return the console uart passed by the bootloader
 *
 * Returns uart	  (0 or 1)
 */
अटल पूर्णांक octeon_get_boot_uart(व्योम)
अणु
	वापस (octeon_boot_desc_ptr->flags & OCTEON_BL_FLAG_CONSOLE_UART1) ?
		1 : 0;
पूर्ण

/**
 * Get the coremask Linux was booted on.
 *
 * Returns Core mask
 */
पूर्णांक octeon_get_boot_coremask(व्योम)
अणु
	वापस octeon_boot_desc_ptr->core_mask;
पूर्ण

/**
 * Check the hardware BIST results क्रम a CPU
 */
व्योम octeon_check_cpu_bist(व्योम)
अणु
	स्थिर पूर्णांक coreid = cvmx_get_core_num();
	अचिन्हित दीर्घ दीर्घ mask;
	अचिन्हित दीर्घ दीर्घ bist_val;

	/* Check BIST results क्रम COP0 रेजिस्टरs */
	mask = 0x1f00000000ull;
	bist_val = पढ़ो_octeon_c0_icacheerr();
	अगर (bist_val & mask)
		pr_err("Core%d BIST Failure: CacheErr(icache) = 0x%llx\n",
		       coreid, bist_val);

	bist_val = पढ़ो_octeon_c0_dcacheerr();
	अगर (bist_val & 1)
		pr_err("Core%d L1 Dcache parity error: "
		       "CacheErr(dcache) = 0x%llx\n",
		       coreid, bist_val);

	mask = 0xfc00000000000000ull;
	bist_val = पढ़ो_c0_cvmmemctl();
	अगर (bist_val & mask)
		pr_err("Core%d BIST Failure: COP0_CVM_MEM_CTL = 0x%llx\n",
		       coreid, bist_val);

	ग_लिखो_octeon_c0_dcacheerr(0);
पूर्ण

/**
 * Reboot Octeon
 *
 * @command: Command to pass to the bootloader. Currently ignored.
 */
अटल व्योम octeon_restart(अक्षर *command)
अणु
	/* Disable all watchकरोgs beक्रमe soft reset. They करोn't get cleared */
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;
	क्रम_each_online_cpu(cpu)
		cvmx_ग_लिखो_csr(CVMX_CIU_WDOGX(cpu_logical_map(cpu)), 0);
#अन्यथा
	cvmx_ग_लिखो_csr(CVMX_CIU_WDOGX(cvmx_get_core_num()), 0);
#पूर्ण_अगर

	mb();
	जबतक (1)
		अगर (OCTEON_IS_OCTEON3())
			cvmx_ग_लिखो_csr(CVMX_RST_SOFT_RST, 1);
		अन्यथा
			cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_RST, 1);
पूर्ण


/**
 * Permanently stop a core.
 *
 * @arg: Ignored.
 */
अटल व्योम octeon_समाप्त_core(व्योम *arg)
अणु
	अगर (octeon_is_simulation())
		/* A अवरोध inकाष्ठाion causes the simulator stop a core */
		यंत्र अस्थिर ("break" ::: "memory");

	local_irq_disable();
	/* Disable watchकरोg on this core. */
	cvmx_ग_लिखो_csr(CVMX_CIU_WDOGX(cvmx_get_core_num()), 0);
	/* Spin in a low घातer mode. */
	जबतक (true)
		यंत्र अस्थिर ("wait" ::: "memory");
पूर्ण


/**
 * Halt the प्रणाली
 */
अटल व्योम octeon_halt(व्योम)
अणु
	smp_call_function(octeon_समाप्त_core, शून्य, 0);

	चयन (octeon_bootinfo->board_type) अणु
	हाल CVMX_BOARD_TYPE_NAO38:
		/* Driving a 1 to GPIO 12 shuts off this board */
		cvmx_ग_लिखो_csr(CVMX_GPIO_BIT_CFGX(12), 1);
		cvmx_ग_लिखो_csr(CVMX_GPIO_TX_SET, 0x1000);
		अवरोध;
	शेष:
		octeon_ग_लिखो_lcd("PowerOff");
		अवरोध;
	पूर्ण

	octeon_समाप्त_core(शून्य);
पूर्ण

अटल अक्षर __पढ़ो_mostly octeon_प्रणाली_type[80];

अटल व्योम __init init_octeon_प्रणाली_type(व्योम)
अणु
	अक्षर स्थिर *board_type;

	board_type = cvmx_board_type_to_string(octeon_bootinfo->board_type);
	अगर (board_type == शून्य) अणु
		काष्ठा device_node *root;
		पूर्णांक ret;

		root = of_find_node_by_path("/");
		ret = of_property_पढ़ो_string(root, "model", &board_type);
		of_node_put(root);
		अगर (ret)
			board_type = "Unsupported Board";
	पूर्ण

	snम_लिखो(octeon_प्रणाली_type, माप(octeon_प्रणाली_type), "%s (%s)",
		 board_type, octeon_model_get_string(पढ़ो_c0_prid()));
पूर्ण

/**
 * Return a string representing the प्रणाली type
 *
 * Returns
 */
स्थिर अक्षर *octeon_board_type_string(व्योम)
अणु
	वापस octeon_प्रणाली_type;
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
	__attribute__ ((alias("octeon_board_type_string")));

व्योम octeon_user_io_init(व्योम)
अणु
	जोड़ octeon_cvmemctl cvmmemctl;

	/* Get the current settings क्रम CP0_CVMMEMCTL_REG */
	cvmmemctl.u64 = पढ़ो_c0_cvmmemctl();
	/* R/W If set, marked ग_लिखो-buffer entries समय out the same
	 * as as other entries; अगर clear, marked ग_लिखो-buffer entries
	 * use the maximum समयout. */
	cvmmemctl.s.dismarkwbदीर्घto = 1;
	/* R/W If set, a merged store करोes not clear the ग_लिखो-buffer
	 * entry समयout state. */
	cvmmemctl.s.dismrgclrwbto = 0;
	/* R/W Two bits that are the MSBs of the resultant CVMSEG LM
	 * word location क्रम an IOBDMA. The other 8 bits come from the
	 * SCRADDR field of the IOBDMA. */
	cvmmemctl.s.iobdmascrmsb = 0;
	/* R/W If set, SYNCWS and SYNCS only order marked stores; अगर
	 * clear, SYNCWS and SYNCS only order unmarked
	 * stores. SYNCWSMARKED has no effect when DISSYNCWS is
	 * set. */
	cvmmemctl.s.syncwsmarked = 0;
	/* R/W If set, SYNCWS acts as SYNCW and SYNCS acts as SYNC. */
	cvmmemctl.s.dissyncws = 0;
	/* R/W If set, no stall happens on ग_लिखो buffer full. */
	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2))
		cvmmemctl.s.diswbfst = 1;
	अन्यथा
		cvmmemctl.s.diswbfst = 0;
	/* R/W If set (and SX set), supervisor-level loads/stores can
	 * use XKPHYS addresses with <48>==0 */
	cvmmemctl.s.xkmemenas = 0;

	/* R/W If set (and UX set), user-level loads/stores can use
	 * XKPHYS addresses with VA<48>==0 */
	cvmmemctl.s.xkmemenau = 0;

	/* R/W If set (and SX set), supervisor-level loads/stores can
	 * use XKPHYS addresses with VA<48>==1 */
	cvmmemctl.s.xkioenas = 0;

	/* R/W If set (and UX set), user-level loads/stores can use
	 * XKPHYS addresses with VA<48>==1 */
	cvmmemctl.s.xkioenau = 0;

	/* R/W If set, all stores act as SYNCW (NOMERGE must be set
	 * when this is set) RW, reset to 0. */
	cvmmemctl.s.allsyncw = 0;

	/* R/W If set, no stores merge, and all stores reach the
	 * coherent bus in order. */
	cvmmemctl.s.nomerge = 0;
	/* R/W Selects the bit in the counter used क्रम DID समय-outs 0
	 * = 231, 1 = 230, 2 = 229, 3 = 214. Actual समय-out is
	 * between 1x and 2x this पूर्णांकerval. For example, with
	 * DIDTTO=3, expiration पूर्णांकerval is between 16K and 32K. */
	cvmmemctl.s.didtto = 0;
	/* R/W If set, the (mem) CSR घड़ी never turns off. */
	cvmmemctl.s.csrckalwys = 0;
	/* R/W If set, mclk never turns off. */
	cvmmemctl.s.mclkalwys = 0;
	/* R/W Selects the bit in the counter used क्रम ग_लिखो buffer
	 * flush समय-outs (WBFLT+11) is the bit position in an
	 * पूर्णांकernal counter used to determine expiration. The ग_लिखो
	 * buffer expires between 1x and 2x this पूर्णांकerval. For
	 * example, with WBFLT = 0, a ग_लिखो buffer expires between 2K
	 * and 4K cycles after the ग_लिखो buffer entry is allocated. */
	cvmmemctl.s.wbflसमय = 0;
	/* R/W If set, करो not put Istream in the L2 cache. */
	cvmmemctl.s.istrnol2 = 0;

	/*
	 * R/W The ग_लिखो buffer threshold. As per erratum Core-14752
	 * क्रम CN63XX, a sc/scd might fail अगर the ग_लिखो buffer is
	 * full.  Lowering WBTHRESH greatly lowers the chances of the
	 * ग_लिखो buffer ever being full and triggering the erratum.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X))
		cvmmemctl.s.wbthresh = 4;
	अन्यथा
		cvmmemctl.s.wbthresh = 10;

	/* R/W If set, CVMSEG is available क्रम loads/stores in
	 * kernel/debug mode. */
#अगर CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0
	cvmmemctl.s.cvmsegenak = 1;
#अन्यथा
	cvmmemctl.s.cvmsegenak = 0;
#पूर्ण_अगर
	/* R/W If set, CVMSEG is available क्रम loads/stores in
	 * supervisor mode. */
	cvmmemctl.s.cvmsegenas = 0;
	/* R/W If set, CVMSEG is available क्रम loads/stores in user
	 * mode. */
	cvmmemctl.s.cvmsegenau = 0;

	ग_लिखो_c0_cvmmemctl(cvmmemctl.u64);

	/* Setup of CVMSEG is करोne in kernel-entry-init.h */
	अगर (smp_processor_id() == 0)
		pr_notice("CVMSEG size: %d cache lines (%d bytes)\n",
			  CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE,
			  CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE * 128);

	अगर (octeon_has_feature(OCTEON_FEATURE_FAU)) अणु
		जोड़ cvmx_iob_fau_समयout fau_समयout;

		/* Set a शेष क्रम the hardware समयouts */
		fau_समयout.u64 = 0;
		fau_समयout.s.tout_val = 0xfff;
		/* Disable tagरुको FAU समयout */
		fau_समयout.s.tout_enb = 0;
		cvmx_ग_लिखो_csr(CVMX_IOB_FAU_TIMEOUT, fau_समयout.u64);
	पूर्ण

	अगर ((!OCTEON_IS_MODEL(OCTEON_CN68XX) &&
	     !OCTEON_IS_MODEL(OCTEON_CN7XXX)) ||
	    OCTEON_IS_MODEL(OCTEON_CN70XX)) अणु
		जोड़ cvmx_घात_nw_tim nm_tim;

		nm_tim.u64 = 0;
		/* 4096 cycles */
		nm_tim.s.nw_tim = 3;
		cvmx_ग_लिखो_csr(CVMX_POW_NW_TIM, nm_tim.u64);
	पूर्ण

	ग_लिखो_octeon_c0_icacheerr(0);
	ग_लिखो_c0_derraddr1(0);
पूर्ण

/**
 * Early entry poपूर्णांक क्रम arch setup
 */
व्योम __init prom_init(व्योम)
अणु
	काष्ठा cvmx_sysinfo *sysinfo;
	स्थिर अक्षर *arg;
	अक्षर *p;
	पूर्णांक i;
	u64 t;
	पूर्णांक argc;
#अगर_घोषित CONFIG_CAVIUM_RESERVE32
	पूर्णांक64_t addr = -1;
#पूर्ण_अगर
	/*
	 * The bootloader passes a poपूर्णांकer to the boot descriptor in
	 * $a3, this is available as fw_arg3.
	 */
	octeon_boot_desc_ptr = (काष्ठा octeon_boot_descriptor *)fw_arg3;
	octeon_bootinfo =
		cvmx_phys_to_ptr(octeon_boot_desc_ptr->cvmx_desc_vaddr);
	cvmx_booपंचांगem_init(cvmx_phys_to_ptr(octeon_bootinfo->phy_mem_desc_addr));

	sysinfo = cvmx_sysinfo_get();
	स_रखो(sysinfo, 0, माप(*sysinfo));
	sysinfo->प्रणाली_dram_size = octeon_bootinfo->dram_size << 20;
	sysinfo->phy_mem_desc_addr = (u64)phys_to_virt(octeon_bootinfo->phy_mem_desc_addr);

	अगर ((octeon_bootinfo->major_version > 1) ||
	    (octeon_bootinfo->major_version == 1 &&
	     octeon_bootinfo->minor_version >= 4))
		cvmx_coremask_copy(&sysinfo->core_mask,
				   &octeon_bootinfo->ext_core_mask);
	अन्यथा
		cvmx_coremask_set64(&sysinfo->core_mask,
				    octeon_bootinfo->core_mask);

	/* Some broken u-boot pass garbage in upper bits, clear them out */
	अगर (!OCTEON_IS_MODEL(OCTEON_CN78XX))
		क्रम (i = 512; i < 1024; i++)
			cvmx_coremask_clear_core(&sysinfo->core_mask, i);

	sysinfo->exception_base_addr = octeon_bootinfo->exception_base_addr;
	sysinfo->cpu_घड़ी_hz = octeon_bootinfo->eघड़ी_hz;
	sysinfo->dram_data_rate_hz = octeon_bootinfo->dघड़ी_hz * 2;
	sysinfo->board_type = octeon_bootinfo->board_type;
	sysinfo->board_rev_major = octeon_bootinfo->board_rev_major;
	sysinfo->board_rev_minor = octeon_bootinfo->board_rev_minor;
	स_नकल(sysinfo->mac_addr_base, octeon_bootinfo->mac_addr_base,
	       माप(sysinfo->mac_addr_base));
	sysinfo->mac_addr_count = octeon_bootinfo->mac_addr_count;
	स_नकल(sysinfo->board_serial_number,
	       octeon_bootinfo->board_serial_number,
	       माप(sysinfo->board_serial_number));
	sysinfo->compact_flash_common_base_addr =
		octeon_bootinfo->compact_flash_common_base_addr;
	sysinfo->compact_flash_attribute_base_addr =
		octeon_bootinfo->compact_flash_attribute_base_addr;
	sysinfo->led_display_base_addr = octeon_bootinfo->led_display_base_addr;
	sysinfo->dfa_ref_घड़ी_hz = octeon_bootinfo->dfa_ref_घड़ी_hz;
	sysinfo->bootloader_config_flags = octeon_bootinfo->config_flags;

	अगर (OCTEON_IS_OCTEON2()) अणु
		/* I/O घड़ी runs at a dअगरferent rate than the CPU. */
		जोड़ cvmx_mio_rst_boot rst_boot;
		rst_boot.u64 = cvmx_पढ़ो_csr(CVMX_MIO_RST_BOOT);
		octeon_io_घड़ी_rate = 50000000 * rst_boot.s.pnr_mul;
	पूर्ण अन्यथा अगर (OCTEON_IS_OCTEON3()) अणु
		/* I/O घड़ी runs at a dअगरferent rate than the CPU. */
		जोड़ cvmx_rst_boot rst_boot;
		rst_boot.u64 = cvmx_पढ़ो_csr(CVMX_RST_BOOT);
		octeon_io_घड़ी_rate = 50000000 * rst_boot.s.pnr_mul;
	पूर्ण अन्यथा अणु
		octeon_io_घड़ी_rate = sysinfo->cpu_घड़ी_hz;
	पूर्ण

	t = पढ़ो_c0_cvmctl();
	अगर ((t & (1ull << 27)) == 0) अणु
		/*
		 * Setup the multiplier save/restore code अगर
		 * CvmCtl[NOMUL] clear.
		 */
		व्योम *save;
		व्योम *save_end;
		व्योम *restore;
		व्योम *restore_end;
		पूर्णांक save_len;
		पूर्णांक restore_len;
		पूर्णांक save_max = (अक्षर *)octeon_mult_save_end -
			(अक्षर *)octeon_mult_save;
		पूर्णांक restore_max = (अक्षर *)octeon_mult_restore_end -
			(अक्षर *)octeon_mult_restore;
		अगर (current_cpu_data.cputype == CPU_CAVIUM_OCTEON3) अणु
			save = octeon_mult_save3;
			save_end = octeon_mult_save3_end;
			restore = octeon_mult_restore3;
			restore_end = octeon_mult_restore3_end;
		पूर्ण अन्यथा अणु
			save = octeon_mult_save2;
			save_end = octeon_mult_save2_end;
			restore = octeon_mult_restore2;
			restore_end = octeon_mult_restore2_end;
		पूर्ण
		save_len = (अक्षर *)save_end - (अक्षर *)save;
		restore_len = (अक्षर *)restore_end - (अक्षर *)restore;
		अगर (!WARN_ON(save_len > save_max ||
				restore_len > restore_max)) अणु
			स_नकल(octeon_mult_save, save, save_len);
			स_नकल(octeon_mult_restore, restore, restore_len);
		पूर्ण
	पूर्ण

	/*
	 * Only enable the LED controller अगर we're running on a CN38XX, CN58XX,
	 * or CN56XX. The CN30XX and CN31XX करोn't have an LED controller.
	 */
	अगर (!octeon_is_simulation() &&
	    octeon_has_feature(OCTEON_FEATURE_LED_CONTROLLER)) अणु
		cvmx_ग_लिखो_csr(CVMX_LED_EN, 0);
		cvmx_ग_लिखो_csr(CVMX_LED_PRT, 0);
		cvmx_ग_लिखो_csr(CVMX_LED_DBG, 0);
		cvmx_ग_लिखो_csr(CVMX_LED_PRT_FMT, 0);
		cvmx_ग_लिखो_csr(CVMX_LED_UDD_CNTX(0), 32);
		cvmx_ग_लिखो_csr(CVMX_LED_UDD_CNTX(1), 32);
		cvmx_ग_लिखो_csr(CVMX_LED_UDD_DATX(0), 0);
		cvmx_ग_लिखो_csr(CVMX_LED_UDD_DATX(1), 0);
		cvmx_ग_लिखो_csr(CVMX_LED_EN, 1);
	पूर्ण
#अगर_घोषित CONFIG_CAVIUM_RESERVE32
	/*
	 * We need to temporarily allocate all memory in the reserve32
	 * region. This makes sure the kernel करोesn't allocate this
	 * memory when it is getting memory from the
	 * bootloader. Later, after the memory allocations are
	 * complete, the reserve32 will be मुक्तd.
	 *
	 * Allocate memory क्रम RESERVED32 aligned on 2MB boundary. This
	 * is in हाल we later use hugetlb entries with it.
	 */
	addr = cvmx_booपंचांगem_phy_named_block_alloc(CONFIG_CAVIUM_RESERVE32 << 20,
						0, 0, 2 << 20,
						"CAVIUM_RESERVE32", 0);
	अगर (addr < 0)
		pr_err("Failed to allocate CAVIUM_RESERVE32 memory area\n");
	अन्यथा
		octeon_reserve32_memory = addr;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CAVIUM_OCTEON_LOCK_L2
	अगर (cvmx_पढ़ो_csr(CVMX_L2D_FUS3) & (3ull << 34)) अणु
		pr_info("Skipping L2 locking due to reduced L2 cache size\n");
	पूर्ण अन्यथा अणु
		uपूर्णांक32_t __maybe_unused ebase = पढ़ो_c0_ebase() & 0x3ffff000;
#अगर_घोषित CONFIG_CAVIUM_OCTEON_LOCK_L2_TLB
		/* TLB refill */
		cvmx_l2c_lock_mem_region(ebase, 0x100);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_OCTEON_LOCK_L2_EXCEPTION
		/* General exception */
		cvmx_l2c_lock_mem_region(ebase + 0x180, 0x80);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_OCTEON_LOCK_L2_LOW_LEVEL_INTERRUPT
		/* Interrupt handler */
		cvmx_l2c_lock_mem_region(ebase + 0x200, 0x80);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_OCTEON_LOCK_L2_INTERRUPT
		cvmx_l2c_lock_mem_region(__pa_symbol(handle_पूर्णांक), 0x100);
		cvmx_l2c_lock_mem_region(__pa_symbol(plat_irq_dispatch), 0x80);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CAVIUM_OCTEON_LOCK_L2_MEMCPY
		cvmx_l2c_lock_mem_region(__pa_symbol(स_नकल), 0x480);
#पूर्ण_अगर
	पूर्ण
#पूर्ण_अगर

	octeon_check_cpu_bist();

	octeon_uart = octeon_get_boot_uart();

#अगर_घोषित CONFIG_SMP
	octeon_ग_लिखो_lcd("LinuxSMP");
#अन्यथा
	octeon_ग_लिखो_lcd("Linux");
#पूर्ण_अगर

	octeon_setup_delays();

	/*
	 * BIST should always be enabled when करोing a soft reset. L2
	 * Cache locking क्रम instance is not cleared unless BIST is
	 * enabled.  Unक्रमtunately due to a chip errata G-200 क्रम
	 * Cn38XX and CN31XX, BIST must be disabled on these parts.
	 */
	अगर (OCTEON_IS_MODEL(OCTEON_CN38XX_PASS2) ||
	    OCTEON_IS_MODEL(OCTEON_CN31XX))
		cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_BIST, 0);
	अन्यथा
		cvmx_ग_लिखो_csr(CVMX_CIU_SOFT_BIST, 1);

	/* Default to 64MB in the simulator to speed things up */
	अगर (octeon_is_simulation())
		max_memory = 64ull << 20;

	arg = म_माला(arcs_cmdline, "mem=");
	अगर (arg) अणु
		max_memory = memparse(arg + 4, &p);
		अगर (max_memory == 0)
			max_memory = 32ull << 30;
		अगर (*p == '@')
			reserve_low_mem = memparse(p + 1, &p);
	पूर्ण

	arcs_cmdline[0] = 0;
	argc = octeon_boot_desc_ptr->argc;
	क्रम (i = 0; i < argc; i++) अणु
		स्थिर अक्षर *arg =
			cvmx_phys_to_ptr(octeon_boot_desc_ptr->argv[i]);
		अगर ((म_भेदन(arg, "MEM=", 4) == 0) ||
		    (म_भेदन(arg, "mem=", 4) == 0)) अणु
			max_memory = memparse(arg + 4, &p);
			अगर (max_memory == 0)
				max_memory = 32ull << 30;
			अगर (*p == '@')
				reserve_low_mem = memparse(p + 1, &p);
#अगर_घोषित CONFIG_KEXEC
		पूर्ण अन्यथा अगर (म_भेदन(arg, "crashkernel=", 12) == 0) अणु
			crashk_size = memparse(arg+12, &p);
			अगर (*p == '@')
				crashk_base = memparse(p+1, &p);
			म_जोड़ो(arcs_cmdline, " ");
			म_जोड़ो(arcs_cmdline, arg);
			/*
			 * To करो: चयन parsing to new style, something like:
			 * parse_crashkernel(arg, sysinfo->प्रणाली_dram_size,
			 *		  &crashk_size, &crashk_base);
			 */
#पूर्ण_अगर
		पूर्ण अन्यथा अगर (म_माप(arcs_cmdline) + म_माप(arg) + 1 <
			   माप(arcs_cmdline) - 1) अणु
			म_जोड़ो(arcs_cmdline, " ");
			म_जोड़ो(arcs_cmdline, arg);
		पूर्ण
	पूर्ण

	अगर (म_माला(arcs_cmdline, "console=") == शून्य) अणु
		अगर (octeon_uart == 1)
			म_जोड़ो(arcs_cmdline, " console=ttyS1,115200");
		अन्यथा
			म_जोड़ो(arcs_cmdline, " console=ttyS0,115200");
	पूर्ण

	mips_hpt_frequency = octeon_get_घड़ी_rate();

	octeon_init_cvmcount();

	_machine_restart = octeon_restart;
	_machine_halt = octeon_halt;

#अगर_घोषित CONFIG_KEXEC
	_machine_kexec_shutकरोwn = octeon_shutकरोwn;
	_machine_crash_shutकरोwn = octeon_crash_shutकरोwn;
	_machine_kexec_prepare = octeon_kexec_prepare;
#अगर_घोषित CONFIG_SMP
	_crash_smp_send_stop = octeon_crash_smp_send_stop;
#पूर्ण_अगर
#पूर्ण_अगर

	octeon_user_io_init();
	octeon_setup_smp();
पूर्ण

/* Exclude a single page from the regions obtained in plat_mem_setup. */
#अगर_अघोषित CONFIG_CRASH_DUMP
अटल __init व्योम memory_exclude_page(u64 addr, u64 *mem, u64 *size)
अणु
	अगर (addr > *mem && addr < *mem + *size) अणु
		u64 inc = addr - *mem;
		memblock_add(*mem, inc);
		*mem += inc;
		*size -= inc;
	पूर्ण

	अगर (addr == *mem && *size > PAGE_SIZE) अणु
		*mem += PAGE_SIZE;
		*size -= PAGE_SIZE;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

व्योम __init fw_init_cmdline(व्योम)
अणु
	पूर्णांक i;

	octeon_boot_desc_ptr = (काष्ठा octeon_boot_descriptor *)fw_arg3;
	क्रम (i = 0; i < octeon_boot_desc_ptr->argc; i++) अणु
		स्थिर अक्षर *arg =
			cvmx_phys_to_ptr(octeon_boot_desc_ptr->argv[i]);
		अगर (म_माप(arcs_cmdline) + म_माप(arg) + 1 <
			   माप(arcs_cmdline) - 1) अणु
			म_जोड़ो(arcs_cmdline, " ");
			म_जोड़ो(arcs_cmdline, arg);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init *plat_get_fdt(व्योम)
अणु
	octeon_bootinfo =
		cvmx_phys_to_ptr(octeon_boot_desc_ptr->cvmx_desc_vaddr);
	वापस phys_to_virt(octeon_bootinfo->fdt_addr);
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	uपूर्णांक64_t mem_alloc_size;
	uपूर्णांक64_t total;
	uपूर्णांक64_t crashk_end;
#अगर_अघोषित CONFIG_CRASH_DUMP
	पूर्णांक64_t memory;
#पूर्ण_अगर

	total = 0;
	crashk_end = 0;

	/*
	 * The Mips memory init uses the first memory location क्रम
	 * some memory vectors. When SPARSEMEM is in use, it करोesn't
	 * verअगरy that the size is big enough क्रम the final
	 * vectors. Making the smallest chuck 4MB seems to be enough
	 * to consistently work.
	 */
	mem_alloc_size = 4 << 20;
	अगर (mem_alloc_size > max_memory)
		mem_alloc_size = max_memory;

/* Crashkernel ignores booपंचांगem list. It relies on mem=X@Y option */
#अगर_घोषित CONFIG_CRASH_DUMP
	memblock_add(reserve_low_mem, max_memory);
	total += max_memory;
#अन्यथा
#अगर_घोषित CONFIG_KEXEC
	अगर (crashk_size > 0) अणु
		memblock_add(crashk_base, crashk_size);
		crashk_end = crashk_base + crashk_size;
	पूर्ण
#पूर्ण_अगर
	/*
	 * When allocating memory, we want incrementing addresses,
	 * which is handled by memblock
	 */
	cvmx_booपंचांगem_lock();
	जबतक (total < max_memory) अणु
		memory = cvmx_booपंचांगem_phy_alloc(mem_alloc_size,
						__pa_symbol(&_end), -1,
						0x100000,
						CVMX_BOOTMEM_FLAG_NO_LOCKING);
		अगर (memory >= 0) अणु
			u64 size = mem_alloc_size;
#अगर_घोषित CONFIG_KEXEC
			uपूर्णांक64_t end;
#पूर्ण_अगर

			/*
			 * exclude a page at the beginning and end of
			 * the 256MB PCIe 'hole' so the kernel will not
			 * try to allocate multi-page buffers that
			 * span the discontinuity.
			 */
			memory_exclude_page(CVMX_PCIE_BAR1_PHYS_BASE,
					    &memory, &size);
			memory_exclude_page(CVMX_PCIE_BAR1_PHYS_BASE +
					    CVMX_PCIE_BAR1_PHYS_SIZE,
					    &memory, &size);
#अगर_घोषित CONFIG_KEXEC
			end = memory + mem_alloc_size;

			/*
			 * This function स्वतःmatically merges address regions
			 * next to each other अगर they are received in
			 * incrementing order
			 */
			अगर (memory < crashk_base && end >  crashk_end) अणु
				/* region is fully in */
				memblock_add(memory, crashk_base - memory);
				total += crashk_base - memory;
				memblock_add(crashk_end, end - crashk_end);
				total += end - crashk_end;
				जारी;
			पूर्ण

			अगर (memory >= crashk_base && end <= crashk_end)
				/*
				 * Entire memory region is within the new
				 *  kernel's memory, ignore it.
				 */
				जारी;

			अगर (memory > crashk_base && memory < crashk_end &&
			    end > crashk_end) अणु
				/*
				 * Overlap with the beginning of the region,
				 * reserve the beginning.
				  */
				mem_alloc_size -= crashk_end - memory;
				memory = crashk_end;
			पूर्ण अन्यथा अगर (memory < crashk_base && end > crashk_base &&
				   end < crashk_end)
				/*
				 * Overlap with the beginning of the region,
				 * chop of end.
				 */
				mem_alloc_size -= end - crashk_base;
#पूर्ण_अगर
			memblock_add(memory, mem_alloc_size);
			total += mem_alloc_size;
			/* Recovering mem_alloc_size */
			mem_alloc_size = 4 << 20;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	cvmx_booपंचांगem_unlock();
#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

#अगर_घोषित CONFIG_CAVIUM_RESERVE32
	/*
	 * Now that we've allocated the kernel memory it is safe to
	 * मुक्त the reserved region. We मुक्त it here so that builtin
	 * drivers can use the memory.
	 */
	अगर (octeon_reserve32_memory)
		cvmx_booपंचांगem_मुक्त_named("CAVIUM_RESERVE32");
#पूर्ण_अगर /* CONFIG_CAVIUM_RESERVE32 */

	अगर (total == 0)
		panic("Unable to allocate memory from "
		      "cvmx_bootmem_phy_alloc");
पूर्ण

/*
 * Emit one अक्षरacter to the boot UART.	 Exported क्रम use by the
 * watchकरोg समयr.
 */
व्योम prom_अक्षर_दो(अक्षर c)
अणु
	uपूर्णांक64_t lsrval;

	/* Spin until there is room */
	करो अणु
		lsrval = cvmx_पढ़ो_csr(CVMX_MIO_UARTX_LSR(octeon_uart));
	पूर्ण जबतक ((lsrval & 0x20) == 0);

	/* Write the byte */
	cvmx_ग_लिखो_csr(CVMX_MIO_UARTX_THR(octeon_uart), c & 0xffull);
पूर्ण
EXPORT_SYMBOL(prom_अक्षर_दो);

व्योम __init prom_मुक्त_prom_memory(व्योम)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX)) अणु
		/* Check क्रम presence of Core-14449 fix.  */
		u32 insn;
		u32 *foo;

		foo = &insn;

		यंत्र अस्थिर("# before" : : : "memory");
		prefetch(foo);
		यंत्र अस्थिर(
			".set push\n\t"
			".set noreorder\n\t"
			"bal 1f\n\t"
			"nop\n"
			"1:\tlw %0,-12($31)\n\t"
			".set pop\n\t"
			: "=r" (insn) : : "$31", "memory");

		अगर ((insn >> 26) != 0x33)
			panic("No PREF instruction at Core-14449 probe point.");

		अगर (((insn >> 16) & 0x1f) != 28)
			panic("OCTEON II DCache prefetch workaround not in place (%04x).\n"
			      "Please build kernel with proper options (CONFIG_CAVIUM_CN63XXP1).",
			      insn);
	पूर्ण
पूर्ण

व्योम __init octeon_fill_mac_addresses(व्योम);

व्योम __init device_tree_init(व्योम)
अणु
	स्थिर व्योम *fdt;
	bool करो_prune;
	bool fill_mac;

#अगर_घोषित CONFIG_MIPS_ELF_APPENDED_DTB
	अगर (!fdt_check_header(&__appended_dtb)) अणु
		fdt = &__appended_dtb;
		करो_prune = false;
		fill_mac = true;
		pr_info("Using appended Device Tree.\n");
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (octeon_bootinfo->minor_version >= 3 && octeon_bootinfo->fdt_addr) अणु
		fdt = phys_to_virt(octeon_bootinfo->fdt_addr);
		अगर (fdt_check_header(fdt))
			panic("Corrupt Device Tree passed to kernel.");
		करो_prune = false;
		fill_mac = false;
		pr_info("Using passed Device Tree.\n");
	पूर्ण अन्यथा अगर (OCTEON_IS_MODEL(OCTEON_CN68XX)) अणु
		fdt = &__dtb_octeon_68xx_begin;
		करो_prune = true;
		fill_mac = true;
	पूर्ण अन्यथा अणु
		fdt = &__dtb_octeon_3xxx_begin;
		करो_prune = true;
		fill_mac = true;
	पूर्ण

	initial_boot_params = (व्योम *)fdt;

	अगर (करो_prune) अणु
		octeon_prune_device_tree();
		pr_info("Using internal Device Tree.\n");
	पूर्ण
	अगर (fill_mac)
		octeon_fill_mac_addresses();
	unflatten_and_copy_device_tree();
	init_octeon_प्रणाली_type();
पूर्ण

अटल पूर्णांक __initdata disable_octeon_edac_p;

अटल पूर्णांक __init disable_octeon_edac(अक्षर *str)
अणु
	disable_octeon_edac_p = 1;
	वापस 0;
पूर्ण
early_param("disable_octeon_edac", disable_octeon_edac);

अटल अक्षर *edac_device_names[] = अणु
	"octeon_l2c_edac",
	"octeon_pc_edac",
पूर्ण;

अटल पूर्णांक __init edac_devinit(व्योम)
अणु
	काष्ठा platक्रमm_device *dev;
	पूर्णांक i, err = 0;
	पूर्णांक num_lmc;
	अक्षर *name;

	अगर (disable_octeon_edac_p)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(edac_device_names); i++) अणु
		name = edac_device_names[i];
		dev = platक्रमm_device_रेजिस्टर_simple(name, -1, शून्य, 0);
		अगर (IS_ERR(dev)) अणु
			pr_err("Registration of %s failed!\n", name);
			err = PTR_ERR(dev);
		पूर्ण
	पूर्ण

	num_lmc = OCTEON_IS_MODEL(OCTEON_CN68XX) ? 4 :
		(OCTEON_IS_MODEL(OCTEON_CN56XX) ? 2 : 1);
	क्रम (i = 0; i < num_lmc; i++) अणु
		dev = platक्रमm_device_रेजिस्टर_simple("octeon_lmc_edac",
						      i, शून्य, 0);
		अगर (IS_ERR(dev)) अणु
			pr_err("Registration of octeon_lmc_edac %d failed!\n", i);
			err = PTR_ERR(dev);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
device_initcall(edac_devinit);

अटल व्योम __initdata *octeon_dummy_iospace;

अटल पूर्णांक __init octeon_no_pci_init(व्योम)
अणु
	/*
	 * Initially assume there is no PCI. The PCI/PCIe platक्रमm code will
	 * later re-initialize these to correct values अगर they are present.
	 */
	octeon_dummy_iospace = vzalloc(IO_SPACE_LIMIT);
	set_io_port_base((अचिन्हित दीर्घ)octeon_dummy_iospace);
	ioport_resource.start = MAX_RESOURCE;
	ioport_resource.end = 0;
	वापस 0;
पूर्ण
core_initcall(octeon_no_pci_init);

अटल पूर्णांक __init octeon_no_pci_release(व्योम)
अणु
	/*
	 * Release the allocated memory अगर a real IO space is there.
	 */
	अगर ((अचिन्हित दीर्घ)octeon_dummy_iospace != mips_io_port_base)
		vमुक्त(octeon_dummy_iospace);
	वापस 0;
पूर्ण
late_initcall(octeon_no_pci_release);
