<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/setup.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 */

/* 2.3.x booपंचांगem, 1999 Andrea Arcangeli <andrea@suse.de> */

/*
 * Bootup setup stuff.
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/user.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/delay.h>
#समावेश <linux/mc146818rtc.h>
#समावेश <linux/console.h>
#समावेश <linux/cpu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/initrd.h>
#समावेश <linux/eisa.h>
#समावेश <linux/pfn.h>
#अगर_घोषित CONFIG_MAGIC_SYSRQ
#समावेश <linux/sysrq.h>
#समावेश <linux/reboot.h>
#पूर्ण_अगर
#समावेश <linux/notअगरier.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/export.h>

बाह्य काष्ठा atomic_notअगरier_head panic_notअगरier_list;
अटल पूर्णांक alpha_panic_event(काष्ठा notअगरier_block *, अचिन्हित दीर्घ, व्योम *);
अटल काष्ठा notअगरier_block alpha_panic_block = अणु
	alpha_panic_event,
        शून्य,
        पूर्णांक_उच्च /* try to करो it first */
पूर्ण;

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/console.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"


काष्ठा hwrpb_काष्ठा *hwrpb;
EXPORT_SYMBOL(hwrpb);
अचिन्हित दीर्घ srm_hae;

पूर्णांक alpha_l1i_cacheshape;
पूर्णांक alpha_l1d_cacheshape;
पूर्णांक alpha_l2_cacheshape;
पूर्णांक alpha_l3_cacheshape;

#अगर_घोषित CONFIG_VERBOSE_MCHECK
/* 0=minimum, 1=verbose, 2=all */
/* These can be overridden via the command line, ie "verbose_mcheck=2") */
अचिन्हित दीर्घ alpha_verbose_mcheck = CONFIG_VERBOSE_MCHECK_ON;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
काष्ठा cpumask node_to_cpumask_map[MAX_NUMNODES] __पढ़ो_mostly;
EXPORT_SYMBOL(node_to_cpumask_map);
#पूर्ण_अगर

/* Which processor we booted from.  */
पूर्णांक boot_cpuid;

/*
 * Using SRM callbacks क्रम initial console output. This works from
 * setup_arch() समय through the end of समय_init(), as those places
 * are under our (Alpha) control.

 * "srmcons" specअगरied in the boot command arguments allows us to
 * see kernel messages during the period of समय beक्रमe the true
 * console device is "registered" during console_init(). 
 * As of this version (2.5.59), console_init() will call
 * disable_early_prपूर्णांकk() as the last action beक्रमe initializing
 * the console drivers. That's the last possible समय srmcons can be 
 * unरेजिस्टरed without पूर्णांकerfering with console behavior.
 *
 * By शेष, OFF; set it with a bootcommand arg of "srmcons" or 
 * "console=srm". The meaning of these two args is:
 *     "srmcons"     - early callback prपूर्णांकs 
 *     "console=srm" - full callback based console, including early prपूर्णांकs
 */
पूर्णांक srmcons_output = 0;

/* Enक्रमce a memory size limit; useful क्रम testing. By शेष, none. */
अचिन्हित दीर्घ mem_size_limit = 0;

/* Set AGP GART winकरोw size (0 means disabled). */
अचिन्हित दीर्घ alpha_agpgart_size = DEFAULT_AGP_APER_SIZE;

#अगर_घोषित CONFIG_ALPHA_GENERIC
काष्ठा alpha_machine_vector alpha_mv;
EXPORT_SYMBOL(alpha_mv);
#पूर्ण_अगर

#अगर_अघोषित alpha_using_srm
पूर्णांक alpha_using_srm;
EXPORT_SYMBOL(alpha_using_srm);
#पूर्ण_अगर

#अगर_अघोषित alpha_using_qemu
पूर्णांक alpha_using_qemu;
#पूर्ण_अगर

अटल काष्ठा alpha_machine_vector *get_sysvec(अचिन्हित दीर्घ, अचिन्हित दीर्घ,
					       अचिन्हित दीर्घ);
अटल काष्ठा alpha_machine_vector *get_sysvec_byname(स्थिर अक्षर *);
अटल व्योम get_sysnames(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
			 अक्षर **, अक्षर **);
अटल व्योम determine_cpu_caches (अचिन्हित पूर्णांक);

अटल अक्षर __initdata command_line[COMMAND_LINE_SIZE];

/*
 * The क्रमmat of "screen_info" is strange, and due to early
 * i386-setup code. This is just enough to make the console
 * code think we're on a VGA color display.
 */

काष्ठा screen_info screen_info = अणु
	.orig_x = 0,
	.orig_y = 25,
	.orig_video_cols = 80,
	.orig_video_lines = 25,
	.orig_video_isVGA = 1,
	.orig_video_poपूर्णांकs = 16
पूर्ण;

EXPORT_SYMBOL(screen_info);

/*
 * The direct map I/O winकरोw, अगर any.  This should be the same
 * क्रम all busses, since it's used by virt_to_bus.
 */

अचिन्हित दीर्घ __direct_map_base;
अचिन्हित दीर्घ __direct_map_size;
EXPORT_SYMBOL(__direct_map_base);
EXPORT_SYMBOL(__direct_map_size);

/*
 * Declare all of the machine vectors.
 */

/* GCC 2.7.2 (on alpha at least) is lame.  It करोes not support either 
   __attribute__((weak)) or #आशय weak.  Bypass it and talk directly
   to the assembler.  */

#घोषणा WEAK(X) \
	बाह्य काष्ठा alpha_machine_vector X; \
	यंत्र(".weak "#X)

WEAK(alcor_mv);
WEAK(alphabook1_mv);
WEAK(avanti_mv);
WEAK(cabriolet_mv);
WEAK(clipper_mv);
WEAK(dp264_mv);
WEAK(eb164_mv);
WEAK(eb64p_mv);
WEAK(eb66_mv);
WEAK(eb66p_mv);
WEAK(eiger_mv);
WEAK(jensen_mv);
WEAK(lx164_mv);
WEAK(lynx_mv);
WEAK(marvel_ev7_mv);
WEAK(miata_mv);
WEAK(mikasa_mv);
WEAK(mikasa_primo_mv);
WEAK(monet_mv);
WEAK(nautilus_mv);
WEAK(noname_mv);
WEAK(noritake_mv);
WEAK(noritake_primo_mv);
WEAK(p2k_mv);
WEAK(pc164_mv);
WEAK(निजीer_mv);
WEAK(rawhide_mv);
WEAK(ruffian_mv);
WEAK(rx164_mv);
WEAK(sable_mv);
WEAK(sable_gamma_mv);
WEAK(shark_mv);
WEAK(sx164_mv);
WEAK(takara_mv);
WEAK(titan_mv);
WEAK(webbrick_mv);
WEAK(wildfire_mv);
WEAK(xl_mv);
WEAK(xlt_mv);

#अघोषित WEAK

/*
 * I/O resources inherited from PeeCees.  Except क्रम perhaps the
 * turbochannel alphas, everyone has these on some sort of SuperIO chip.
 *
 * ??? If this becomes less standard, move the काष्ठा out पूर्णांकo the
 * machine vector.
 */

अटल व्योम __init
reserve_std_resources(व्योम)
अणु
	अटल काष्ठा resource standard_io_resources[] = अणु
		अणु .name = "rtc", .start = -1, .end = -1 पूर्ण,
        	अणु .name = "dma1", .start = 0x00, .end = 0x1f पूर्ण,
        	अणु .name = "pic1", .start = 0x20, .end = 0x3f पूर्ण,
        	अणु .name = "timer", .start = 0x40, .end = 0x5f पूर्ण,
        	अणु .name = "keyboard", .start = 0x60, .end = 0x6f पूर्ण,
        	अणु .name = "dma page reg", .start = 0x80, .end = 0x8f पूर्ण,
        	अणु .name = "pic2", .start = 0xa0, .end = 0xbf पूर्ण,
        	अणु .name = "dma2", .start = 0xc0, .end = 0xdf पूर्ण,
	पूर्ण;

	काष्ठा resource *io = &ioport_resource;
	माप_प्रकार i;

	अगर (hose_head) अणु
		काष्ठा pci_controller *hose;
		क्रम (hose = hose_head; hose; hose = hose->next)
			अगर (hose->index == 0) अणु
				io = hose->io_space;
				अवरोध;
			पूर्ण
	पूर्ण

	/* Fix up क्रम the Jensen's queer RTC placement.  */
	standard_io_resources[0].start = RTC_PORT(0);
	standard_io_resources[0].end = RTC_PORT(0) + 0x0f;

	क्रम (i = 0; i < ARRAY_SIZE(standard_io_resources); ++i)
		request_resource(io, standard_io_resources+i);
पूर्ण

#घोषणा PFN_MAX		PFN_DOWN(0x80000000)
#घोषणा क्रम_each_mem_cluster(memdesc, _cluster, i)		\
	क्रम ((_cluster) = (memdesc)->cluster, (i) = 0;		\
	     (i) < (memdesc)->numclusters; (i)++, (_cluster)++)

अटल अचिन्हित दीर्घ __init
get_mem_size_limit(अक्षर *s)
अणु
        अचिन्हित दीर्घ end = 0;
        अक्षर *from = s;

        end = simple_म_से_अदीर्घ(from, &from, 0);
        अगर ( *from == 'K' || *from == 'k' ) अणु
                end = end << 10;
                from++;
        पूर्ण अन्यथा अगर ( *from == 'M' || *from == 'm' ) अणु
                end = end << 20;
                from++;
        पूर्ण अन्यथा अगर ( *from == 'G' || *from == 'g' ) अणु
                end = end << 30;
                from++;
        पूर्ण
        वापस end >> PAGE_SHIFT; /* Return the PFN of the limit. */
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INITRD
व्योम * __init
move_initrd(अचिन्हित दीर्घ mem_limit)
अणु
	व्योम *start;
	अचिन्हित दीर्घ size;

	size = initrd_end - initrd_start;
	start = memblock_alloc(PAGE_ALIGN(size), PAGE_SIZE);
	अगर (!start || __pa(start) + size > mem_limit) अणु
		initrd_start = initrd_end = 0;
		वापस शून्य;
	पूर्ण
	स_हटाओ(start, (व्योम *)initrd_start, size);
	initrd_start = (अचिन्हित दीर्घ)start;
	initrd_end = initrd_start + size;
	prपूर्णांकk("initrd moved to %p\n", start);
	वापस start;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_DISCONTIGMEM
अटल व्योम __init
setup_memory(व्योम *kernel_end)
अणु
	काष्ठा memclust_काष्ठा * cluster;
	काष्ठा memdesc_काष्ठा * memdesc;
	अचिन्हित दीर्घ kernel_size;
	अचिन्हित दीर्घ i;

	/* Find मुक्त clusters, and init and मुक्त the booपंचांगem accordingly.  */
	memdesc = (काष्ठा memdesc_काष्ठा *)
	  (hwrpb->mddt_offset + (अचिन्हित दीर्घ) hwrpb);

	क्रम_each_mem_cluster(memdesc, cluster, i) अणु
		अचिन्हित दीर्घ end;

		prपूर्णांकk("memcluster %lu, usage %01lx, start %8lu, end %8lu\n",
		       i, cluster->usage, cluster->start_pfn,
		       cluster->start_pfn + cluster->numpages);

		/* Bit 0 is console/PALcode reserved.  Bit 1 is
		   non-अस्थिर memory -- we might want to mark
		   this क्रम later.  */
		अगर (cluster->usage & 3)
			जारी;

		end = cluster->start_pfn + cluster->numpages;
		अगर (end > max_low_pfn)
			max_low_pfn = end;

		memblock_add(PFN_PHYS(cluster->start_pfn),
			     cluster->numpages << PAGE_SHIFT);
	पूर्ण

	/*
	 * Except क्रम the NUMA प्रणालीs (wildfire, marvel) all of the 
	 * Alpha प्रणालीs we run on support 32GB of memory or less.
	 * Since the NUMA प्रणालीs पूर्णांकroduce large holes in memory addressing,
	 * we can get पूर्णांकo a situation where there is not enough contiguous
	 * memory क्रम the memory map. 
	 *
	 * Limit memory to the first 32GB to limit the NUMA प्रणालीs to 
	 * memory on their first node (wildfire) or 2 (marvel) to aव्योम 
	 * not being able to produce the memory map. In order to access 
	 * all of the memory on the NUMA प्रणालीs, build with discontiguous
	 * memory support.
	 *
	 * If the user specअगरied a memory limit, let that memory limit stand.
	 */
	अगर (!mem_size_limit) 
		mem_size_limit = (32ul * 1024 * 1024 * 1024) >> PAGE_SHIFT;

	अगर (mem_size_limit && max_low_pfn >= mem_size_limit)
	अणु
		prपूर्णांकk("setup: forcing memory size to %ldK (from %ldK).\n",
		       mem_size_limit << (PAGE_SHIFT - 10),
		       max_low_pfn    << (PAGE_SHIFT - 10));
		max_low_pfn = mem_size_limit;
	पूर्ण

	/* Reserve the kernel memory. */
	kernel_size = virt_to_phys(kernel_end) - KERNEL_START_PHYS;
	memblock_reserve(KERNEL_START_PHYS, kernel_size);

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	initrd_start = INITRD_START;
	अगर (initrd_start) अणु
		initrd_end = initrd_start+INITRD_SIZE;
		prपूर्णांकk("Initial ramdisk at: 0x%p (%lu bytes)\n",
		       (व्योम *) initrd_start, INITRD_SIZE);

		अगर ((व्योम *)initrd_end > phys_to_virt(PFN_PHYS(max_low_pfn))) अणु
			अगर (!move_initrd(PFN_PHYS(max_low_pfn)))
				prपूर्णांकk("initrd extends beyond end of memory "
				       "(0x%08lx > 0x%p)\ndisabling initrd\n",
				       initrd_end,
				       phys_to_virt(PFN_PHYS(max_low_pfn)));
		पूर्ण अन्यथा अणु
			memblock_reserve(virt_to_phys((व्योम *)initrd_start),
					INITRD_SIZE);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */
पूर्ण
#अन्यथा
बाह्य व्योम setup_memory(व्योम *);
#पूर्ण_अगर /* !CONFIG_DISCONTIGMEM */

पूर्णांक __init
page_is_ram(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा memclust_काष्ठा * cluster;
	काष्ठा memdesc_काष्ठा * memdesc;
	अचिन्हित दीर्घ i;

	memdesc = (काष्ठा memdesc_काष्ठा *)
		(hwrpb->mddt_offset + (अचिन्हित दीर्घ) hwrpb);
	क्रम_each_mem_cluster(memdesc, cluster, i)
	अणु
		अगर (pfn >= cluster->start_pfn  &&
		    pfn < cluster->start_pfn + cluster->numpages) अणु
			वापस (cluster->usage & 3) ? 0 : 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init
रेजिस्टर_cpus(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा cpu *p = kzalloc(माप(*p), GFP_KERNEL);
		अगर (!p)
			वापस -ENOMEM;
		रेजिस्टर_cpu(p, i);
	पूर्ण
	वापस 0;
पूर्ण

arch_initcall(रेजिस्टर_cpus);

#अगर_घोषित CONFIG_MAGIC_SYSRQ
अटल व्योम sysrq_reboot_handler(पूर्णांक unused)
अणु
	machine_halt();
पूर्ण

अटल स्थिर काष्ठा sysrq_key_op srm_sysrq_reboot_op = अणु
	.handler	= sysrq_reboot_handler,
	.help_msg       = "reboot(b)",
	.action_msg     = "Resetting",
	.enable_mask    = SYSRQ_ENABLE_BOOT,
पूर्ण;
#पूर्ण_अगर

व्योम __init
setup_arch(अक्षर **cmdline_p)
अणु
	बाह्य अक्षर _end[];

	काष्ठा alpha_machine_vector *vec = शून्य;
	काष्ठा percpu_काष्ठा *cpu;
	अक्षर *type_name, *var_name, *p;
	व्योम *kernel_end = _end; /* end of kernel */
	अक्षर *args = command_line;

	hwrpb = (काष्ठा hwrpb_काष्ठा*) __va(INIT_HWRPB->phys_addr);
	boot_cpuid = hard_smp_processor_id();

        /*
	 * Pre-process the प्रणाली type to make sure it will be valid.
	 *
	 * This may restore real CABRIO and EB66+ family names, ie
	 * EB64+ and EB66.
	 *
	 * Oh, and "white box" AS800 (aka DIGITAL Server 3000 series)
	 * and AS1200 (DIGITAL Server 5000 series) have the type as
	 * the negative of the real one.
	 */
        अगर ((दीर्घ)hwrpb->sys_type < 0) अणु
		hwrpb->sys_type = -((दीर्घ)hwrpb->sys_type);
		hwrpb_update_checksum(hwrpb);
	पूर्ण

	/* Register a call क्रम panic conditions. */
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
			&alpha_panic_block);

#अगर_अघोषित alpha_using_srm
	/* Assume that we've booted from SRM if we haven't booted from MILO.
	   Detect the later by looking क्रम "MILO" in the प्रणाली serial nr.  */
	alpha_using_srm = !str_has_prefix((स्थिर अक्षर *)hwrpb->ssn, "MILO");
#पूर्ण_अगर
#अगर_अघोषित alpha_using_qemu
	/* Similarly, look क्रम QEMU.  */
	alpha_using_qemu = म_माला((स्थिर अक्षर *)hwrpb->ssn, "QEMU") != 0;
#पूर्ण_अगर

	/* If we are using SRM, we want to allow callbacks
	   as early as possible, so करो this NOW, and then
	   they should work immediately thereafter.
	*/
	kernel_end = callback_init(kernel_end);

	/* 
	 * Locate the command line.
	 */
	/* Hack क्रम Jensen... since we're restricted to 8 or 16 अक्षरs क्रम
	   boot flags depending on the boot mode, we need some लघुhand.
	   This should करो क्रम installation.  */
	अगर (म_भेद(COMMAND_LINE, "INSTALL") == 0) अणु
		strlcpy(command_line, "root=/dev/fd0 load_ramdisk=1", माप command_line);
	पूर्ण अन्यथा अणु
		strlcpy(command_line, COMMAND_LINE, माप command_line);
	पूर्ण
	म_नकल(boot_command_line, command_line);
	*cmdline_p = command_line;

	/* 
	 * Process command-line arguments.
	 */
	जबतक ((p = strsep(&args, " \t")) != शून्य) अणु
		अगर (!*p) जारी;
		अगर (म_भेदन(p, "alpha_mv=", 9) == 0) अणु
			vec = get_sysvec_byname(p+9);
			जारी;
		पूर्ण
		अगर (म_भेदन(p, "cycle=", 6) == 0) अणु
			est_cycle_freq = simple_म_से_दीर्घ(p+6, शून्य, 0);
			जारी;
		पूर्ण
		अगर (म_भेदन(p, "mem=", 4) == 0) अणु
			mem_size_limit = get_mem_size_limit(p+4);
			जारी;
		पूर्ण
		अगर (म_भेदन(p, "srmcons", 7) == 0) अणु
			srmcons_output |= 1;
			जारी;
		पूर्ण
		अगर (म_भेदन(p, "console=srm", 11) == 0) अणु
			srmcons_output |= 2;
			जारी;
		पूर्ण
		अगर (म_भेदन(p, "gartsize=", 9) == 0) अणु
			alpha_agpgart_size =
				get_mem_size_limit(p+9) << PAGE_SHIFT;
			जारी;
		पूर्ण
#अगर_घोषित CONFIG_VERBOSE_MCHECK
		अगर (म_भेदन(p, "verbose_mcheck=", 15) == 0) अणु
			alpha_verbose_mcheck = simple_म_से_दीर्घ(p+15, शून्य, 0);
			जारी;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Replace the command line, now that we've समाप्तed it with strsep.  */
	म_नकल(command_line, boot_command_line);

	/* If we want SRM console prपूर्णांकk echoing early, करो it now. */
	अगर (alpha_using_srm && srmcons_output) अणु
		रेजिस्टर_srm_console();

		/*
		 * If "console=srm" was specअगरied, clear the srmcons_output
		 * flag now so that समय.c won't unरेजिस्टर_srm_console
		 */
		अगर (srmcons_output & 2)
			srmcons_output = 0;
	पूर्ण

#अगर_घोषित CONFIG_MAGIC_SYSRQ
	/* If we're using SRM, make sysrq-b halt back to the prom,
	   not स्वतः-reboot.  */
	अगर (alpha_using_srm) अणु
		unरेजिस्टर_sysrq_key('b', __sysrq_reboot_op);
		रेजिस्टर_sysrq_key('b', &srm_sysrq_reboot_op);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Identअगरy and reconfigure क्रम the current प्रणाली.
	 */
	cpu = (काष्ठा percpu_काष्ठा*)((अक्षर*)hwrpb + hwrpb->processor_offset);

	get_sysnames(hwrpb->sys_type, hwrpb->sys_variation,
		     cpu->type, &type_name, &var_name);
	अगर (*var_name == '0')
		var_name = "";

	अगर (!vec) अणु
		vec = get_sysvec(hwrpb->sys_type, hwrpb->sys_variation,
				 cpu->type);
	पूर्ण

	अगर (!vec) अणु
		panic("Unsupported system type: %s%s%s (%ld %ld)\n",
		      type_name, (*var_name ? " variation " : ""), var_name,
		      hwrpb->sys_type, hwrpb->sys_variation);
	पूर्ण
	अगर (vec != &alpha_mv) अणु
		alpha_mv = *vec;
	पूर्ण
	
	prपूर्णांकk("Booting "
#अगर_घोषित CONFIG_ALPHA_GENERIC
	       "GENERIC "
#पूर्ण_अगर
	       "on %s%s%s using machine vector %s from %s\n",
	       type_name, (*var_name ? " variation " : ""),
	       var_name, alpha_mv.vector_name,
	       (alpha_using_srm ? "SRM" : "MILO"));

	prपूर्णांकk("Major Options: "
#अगर_घोषित CONFIG_SMP
	       "SMP "
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALPHA_EV56
	       "EV56 "
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALPHA_EV67
	       "EV67 "
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALPHA_LEGACY_START_ADDRESS
	       "LEGACY_START "
#पूर्ण_अगर
#अगर_घोषित CONFIG_VERBOSE_MCHECK
	       "VERBOSE_MCHECK "
#पूर्ण_अगर

#अगर_घोषित CONFIG_DISCONTIGMEM
	       "DISCONTIGMEM "
#अगर_घोषित CONFIG_NUMA
	       "NUMA "
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	       "DEBUG_SPINLOCK "
#पूर्ण_अगर
#अगर_घोषित CONFIG_MAGIC_SYSRQ
	       "MAGIC_SYSRQ "
#पूर्ण_अगर
	       "\n");

	prपूर्णांकk("Command line: %s\n", command_line);

	/* 
	 * Sync up the HAE.
	 * Save the SRM's current value क्रम restoration.
	 */
	srm_hae = *alpha_mv.hae_रेजिस्टर;
	__set_hae(alpha_mv.hae_cache);

	/* Reset enable correctable error reports.  */
	wrmces(0x7);

	/* Find our memory.  */
	setup_memory(kernel_end);
	memblock_set_bottom_up(true);
	sparse_init();

	/* First guess at cpu cache sizes.  Do this beक्रमe init_arch.  */
	determine_cpu_caches(cpu->type);

	/* Initialize the machine.  Usually has to करो with setting up
	   DMA winकरोws and the like.  */
	अगर (alpha_mv.init_arch)
		alpha_mv.init_arch();

	/* Reserve standard resources.  */
	reserve_std_resources();

	/* 
	 * Give us a शेष console.  TGA users will see nothing until
	 * chr_dev_init is called, rather late in the boot sequence.
	 */

#अगर_घोषित CONFIG_VT
#अगर defined(CONFIG_VGA_CONSOLE)
	conचयनp = &vga_con;
#पूर्ण_अगर
#पूर्ण_अगर

	/* Default root fileप्रणाली to sda2.  */
	ROOT_DEV = Root_SDA2;

#अगर_घोषित CONFIG_EISA
	/* FIXME:  only set this when we actually have EISA in this box? */
	EISA_bus = 1;
#पूर्ण_अगर

 	/*
	 * Check ASN in HWRPB क्रम validity, report अगर bad.
	 * FIXME: how was this failing?  Should we trust it instead,
	 * and copy the value पूर्णांकo alpha_mv.max_asn?
 	 */

 	अगर (hwrpb->max_asn != MAX_ASN) अणु
		prपूर्णांकk("Max ASN from HWRPB is bad (0x%lx)\n", hwrpb->max_asn);
 	पूर्ण

	/*
	 * Identअगरy the flock of penguins.
	 */

#अगर_घोषित CONFIG_SMP
	setup_smp();
#पूर्ण_अगर
	paging_init();
पूर्ण

अटल अक्षर sys_unknown[] = "Unknown";
अटल अक्षर systype_names[][16] = अणु
	"0",
	"ADU", "Cobra", "Ruby", "Flamingo", "Mannequin", "Jensen",
	"Pelican", "Morgan", "Sable", "Medulla", "Noname",
	"Turbolaser", "Avanti", "Mustang", "Alcor", "Tradewind",
	"Mikasa", "EB64", "EB66", "EB64+", "AlphaBook1",
	"Rawhide", "K2", "Lynx", "XL", "EB164", "Noritake",
	"Cortex", "29", "Miata", "XXM", "Takara", "Yukon",
	"Tsunami", "Wildfire", "CUSCO", "Eiger", "Titan", "Marvel"
पूर्ण;

अटल अक्षर unofficial_names[][8] = अणु"100", "Ruffian"पूर्ण;

अटल अक्षर api_names[][16] = अणु"200", "Nautilus"पूर्ण;

अटल अक्षर eb164_names[][8] = अणु"EB164", "PC164", "LX164", "SX164", "RX164"पूर्ण;
अटल पूर्णांक eb164_indices[] = अणु0,0,0,1,1,1,1,1,2,2,2,2,3,3,3,3,4पूर्ण;

अटल अक्षर alcor_names[][16] = अणु"Alcor", "Maverick", "Bret"पूर्ण;
अटल पूर्णांक alcor_indices[] = अणु0,0,0,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2पूर्ण;

अटल अक्षर eb64p_names[][16] = अणु"EB64+", "Cabriolet", "AlphaPCI64"पूर्ण;
अटल पूर्णांक eb64p_indices[] = अणु0,0,1,2पूर्ण;

अटल अक्षर eb66_names[][8] = अणु"EB66", "EB66+"पूर्ण;
अटल पूर्णांक eb66_indices[] = अणु0,0,1पूर्ण;

अटल अक्षर marvel_names[][16] = अणु
	"Marvel/EV7"
पूर्ण;
अटल पूर्णांक marvel_indices[] = अणु 0 पूर्ण;

अटल अक्षर rawhide_names[][16] = अणु
	"Dodge", "Wrangler", "Durango", "Tincup", "DaVinci"
पूर्ण;
अटल पूर्णांक rawhide_indices[] = अणु0,0,0,1,1,2,2,3,3,4,4पूर्ण;

अटल अक्षर titan_names[][16] = अणु
	"DEFAULT", "Privateer", "Falcon", "Granite"
पूर्ण;
अटल पूर्णांक titan_indices[] = अणु0,1,2,2,3पूर्ण;

अटल अक्षर tsunami_names[][16] = अणु
	"0", "DP264", "Warhol", "Windjammer", "Monet", "Clipper",
	"Goldrush", "Webbrick", "Catamaran", "Brisbane", "Melbourne",
	"Flying Clipper", "Shark"
पूर्ण;
अटल पूर्णांक tsunami_indices[] = अणु0,1,2,3,4,5,6,7,8,9,10,11,12पूर्ण;

अटल काष्ठा alpha_machine_vector * __init
get_sysvec(अचिन्हित दीर्घ type, अचिन्हित दीर्घ variation, अचिन्हित दीर्घ cpu)
अणु
	अटल काष्ठा alpha_machine_vector *systype_vecs[] __initdata =
	अणु
		शून्य,		/* 0 */
		शून्य,		/* ADU */
		शून्य,		/* Cobra */
		शून्य,		/* Ruby */
		शून्य,		/* Flamingo */
		शून्य,		/* Mannequin */
		&jensen_mv,
		शून्य, 		/* Pelican */
		शून्य,		/* Morgan */
		शून्य,		/* Sable -- see below.  */
		शून्य,		/* Medulla */
		&noname_mv,
		शून्य,		/* Turbolaser */
		&avanti_mv,
		शून्य,		/* Mustang */
		शून्य,		/* Alcor, Bret, Maverick. HWRPB inaccurate? */
		शून्य,		/* Tradewind */
		शून्य,		/* Mikasa -- see below.  */
		शून्य,		/* EB64 */
		शून्य,		/* EB66 -- see variation.  */
		शून्य,		/* EB64+ -- see variation.  */
		&alphabook1_mv,
		&rawhide_mv,
		शून्य,		/* K2 */
		&lynx_mv,	/* Lynx */
		&xl_mv,
		शून्य,		/* EB164 -- see variation.  */
		शून्य,		/* Noritake -- see below.  */
		शून्य,		/* Cortex */
		शून्य,		/* 29 */
		&miata_mv,
		शून्य,		/* XXM */
		&takara_mv,
		शून्य,		/* Yukon */
		शून्य,		/* Tsunami -- see variation.  */
		&wildfire_mv,	/* Wildfire */
		शून्य,		/* CUSCO */
		&eiger_mv,	/* Eiger */
		शून्य,		/* Titan */
		शून्य,		/* Marvel */
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *unofficial_vecs[] __initdata =
	अणु
		शून्य,		/* 100 */
		&ruffian_mv,
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *api_vecs[] __initdata =
	अणु
		शून्य,		/* 200 */
		&nautilus_mv,
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *alcor_vecs[] __initdata = 
	अणु
		&alcor_mv, &xlt_mv, &xlt_mv
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *eb164_vecs[] __initdata =
	अणु
		&eb164_mv, &pc164_mv, &lx164_mv, &sx164_mv, &rx164_mv
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *eb64p_vecs[] __initdata =
	अणु
		&eb64p_mv,
		&cabriolet_mv,
		&cabriolet_mv		/* AlphaPCI64 */
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *eb66_vecs[] __initdata =
	अणु
		&eb66_mv,
		&eb66p_mv
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *marvel_vecs[] __initdata =
	अणु
		&marvel_ev7_mv,
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *titan_vecs[] __initdata =
	अणु
		&titan_mv,		/* शेष   */
		&निजीer_mv,		/* निजीer */
		&titan_mv,		/* falcon    */
		&निजीer_mv,		/* granite   */
	पूर्ण;

	अटल काष्ठा alpha_machine_vector *tsunami_vecs[]  __initdata =
	अणु
		शून्य,
		&dp264_mv,		/* dp264 */
		&dp264_mv,		/* warhol */
		&dp264_mv,		/* windjammer */
		&monet_mv,		/* monet */
		&clipper_mv,		/* clipper */
		&dp264_mv,		/* goldrush */
		&webbrick_mv,		/* webbrick */
		&dp264_mv,		/* catamaran */
		शून्य,			/* brisbane? */
		शून्य,			/* melbourne? */
		शून्य,			/* flying clipper? */
		&shark_mv,		/* shark */
	पूर्ण;

	/* ??? Do we need to distinguish between Rawhides?  */

	काष्ठा alpha_machine_vector *vec;

	/* Search the प्रणाली tables first... */
	vec = शून्य;
	अगर (type < ARRAY_SIZE(systype_vecs)) अणु
		vec = systype_vecs[type];
	पूर्ण अन्यथा अगर ((type > ST_API_BIAS) &&
		   (type - ST_API_BIAS) < ARRAY_SIZE(api_vecs)) अणु
		vec = api_vecs[type - ST_API_BIAS];
	पूर्ण अन्यथा अगर ((type > ST_UNOFFICIAL_BIAS) &&
		   (type - ST_UNOFFICIAL_BIAS) < ARRAY_SIZE(unofficial_vecs)) अणु
		vec = unofficial_vecs[type - ST_UNOFFICIAL_BIAS];
	पूर्ण

	/* If we've not found one, try क्रम a variation.  */

	अगर (!vec) अणु
		/* Member ID is a bit-field. */
		अचिन्हित दीर्घ member = (variation >> 10) & 0x3f;

		cpu &= 0xffffffff; /* make it usable */

		चयन (type) अणु
		हाल ST_DEC_ALCOR:
			अगर (member < ARRAY_SIZE(alcor_indices))
				vec = alcor_vecs[alcor_indices[member]];
			अवरोध;
		हाल ST_DEC_EB164:
			अगर (member < ARRAY_SIZE(eb164_indices))
				vec = eb164_vecs[eb164_indices[member]];
			/* PC164 may show as EB164 variation with EV56 CPU,
			   but, since no true EB164 had anything but EV5... */
			अगर (vec == &eb164_mv && cpu == EV56_CPU)
				vec = &pc164_mv;
			अवरोध;
		हाल ST_DEC_EB64P:
			अगर (member < ARRAY_SIZE(eb64p_indices))
				vec = eb64p_vecs[eb64p_indices[member]];
			अवरोध;
		हाल ST_DEC_EB66:
			अगर (member < ARRAY_SIZE(eb66_indices))
				vec = eb66_vecs[eb66_indices[member]];
			अवरोध;
		हाल ST_DEC_MARVEL:
			अगर (member < ARRAY_SIZE(marvel_indices))
				vec = marvel_vecs[marvel_indices[member]];
			अवरोध;
		हाल ST_DEC_TITAN:
			vec = titan_vecs[0];	/* शेष */
			अगर (member < ARRAY_SIZE(titan_indices))
				vec = titan_vecs[titan_indices[member]];
			अवरोध;
		हाल ST_DEC_TSUNAMI:
			अगर (member < ARRAY_SIZE(tsunami_indices))
				vec = tsunami_vecs[tsunami_indices[member]];
			अवरोध;
		हाल ST_DEC_1000:
			अगर (cpu == EV5_CPU || cpu == EV56_CPU)
				vec = &mikasa_primo_mv;
			अन्यथा
				vec = &mikasa_mv;
			अवरोध;
		हाल ST_DEC_NORITAKE:
			अगर (cpu == EV5_CPU || cpu == EV56_CPU)
				vec = &noritake_primo_mv;
			अन्यथा
				vec = &noritake_mv;
			अवरोध;
		हाल ST_DEC_2100_A500:
			अगर (cpu == EV5_CPU || cpu == EV56_CPU)
				vec = &sable_gamma_mv;
			अन्यथा
				vec = &sable_mv;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस vec;
पूर्ण

अटल काष्ठा alpha_machine_vector * __init
get_sysvec_byname(स्थिर अक्षर *name)
अणु
	अटल काष्ठा alpha_machine_vector *all_vecs[] __initdata =
	अणु
		&alcor_mv,
		&alphabook1_mv,
		&avanti_mv,
		&cabriolet_mv,
		&clipper_mv,
		&dp264_mv,
		&eb164_mv,
		&eb64p_mv,
		&eb66_mv,
		&eb66p_mv,
		&eiger_mv,
		&jensen_mv,
		&lx164_mv,
		&lynx_mv,
		&miata_mv,
		&mikasa_mv,
		&mikasa_primo_mv,
		&monet_mv,
		&nautilus_mv,
		&noname_mv,
		&noritake_mv,
		&noritake_primo_mv,
		&p2k_mv,
		&pc164_mv,
		&निजीer_mv,
		&rawhide_mv,
		&ruffian_mv,
		&rx164_mv,
		&sable_mv,
		&sable_gamma_mv,
		&shark_mv,
		&sx164_mv,
		&takara_mv,
		&webbrick_mv,
		&wildfire_mv,
		&xl_mv,
		&xlt_mv
	पूर्ण;

	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(all_vecs); ++i) अणु
		काष्ठा alpha_machine_vector *mv = all_vecs[i];
		अगर (strहालcmp(mv->vector_name, name) == 0)
			वापस mv;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
get_sysnames(अचिन्हित दीर्घ type, अचिन्हित दीर्घ variation, अचिन्हित दीर्घ cpu,
	     अक्षर **type_name, अक्षर **variation_name)
अणु
	अचिन्हित दीर्घ member;

	/* If not in the tables, make it UNKNOWN,
	   अन्यथा set type name to family */
	अगर (type < ARRAY_SIZE(systype_names)) अणु
		*type_name = systype_names[type];
	पूर्ण अन्यथा अगर ((type > ST_API_BIAS) &&
		   (type - ST_API_BIAS) < ARRAY_SIZE(api_names)) अणु
		*type_name = api_names[type - ST_API_BIAS];
	पूर्ण अन्यथा अगर ((type > ST_UNOFFICIAL_BIAS) &&
		   (type - ST_UNOFFICIAL_BIAS) < ARRAY_SIZE(unofficial_names)) अणु
		*type_name = unofficial_names[type - ST_UNOFFICIAL_BIAS];
	पूर्ण अन्यथा अणु
		*type_name = sys_unknown;
		*variation_name = sys_unknown;
		वापस;
	पूर्ण

	/* Set variation to "0"; अगर variation is zero, करोne.  */
	*variation_name = systype_names[0];
	अगर (variation == 0) अणु
		वापस;
	पूर्ण

	member = (variation >> 10) & 0x3f; /* member ID is a bit-field */

	cpu &= 0xffffffff; /* make it usable */

	चयन (type) अणु /* select by family */
	शेष: /* शेष to variation "0" क्रम now */
		अवरोध;
	हाल ST_DEC_EB164:
		अगर (member >= ARRAY_SIZE(eb164_indices))
			अवरोध;
		*variation_name = eb164_names[eb164_indices[member]];
		/* PC164 may show as EB164 variation, but with EV56 CPU,
		   so, since no true EB164 had anything but EV5... */
		अगर (eb164_indices[member] == 0 && cpu == EV56_CPU)
			*variation_name = eb164_names[1]; /* make it PC164 */
		अवरोध;
	हाल ST_DEC_ALCOR:
		अगर (member < ARRAY_SIZE(alcor_indices))
			*variation_name = alcor_names[alcor_indices[member]];
		अवरोध;
	हाल ST_DEC_EB64P:
		अगर (member < ARRAY_SIZE(eb64p_indices))
			*variation_name = eb64p_names[eb64p_indices[member]];
		अवरोध;
	हाल ST_DEC_EB66:
		अगर (member < ARRAY_SIZE(eb66_indices))
			*variation_name = eb66_names[eb66_indices[member]];
		अवरोध;
	हाल ST_DEC_MARVEL:
		अगर (member < ARRAY_SIZE(marvel_indices))
			*variation_name = marvel_names[marvel_indices[member]];
		अवरोध;
	हाल ST_DEC_RAWHIDE:
		अगर (member < ARRAY_SIZE(rawhide_indices))
			*variation_name = rawhide_names[rawhide_indices[member]];
		अवरोध;
	हाल ST_DEC_TITAN:
		*variation_name = titan_names[0];	/* शेष */
		अगर (member < ARRAY_SIZE(titan_indices))
			*variation_name = titan_names[titan_indices[member]];
		अवरोध;
	हाल ST_DEC_TSUNAMI:
		अगर (member < ARRAY_SIZE(tsunami_indices))
			*variation_name = tsunami_names[tsunami_indices[member]];
		अवरोध;
	पूर्ण
पूर्ण

/*
 * A change was made to the HWRPB via an ECO and the following code
 * tracks a part of the ECO.  In HWRPB versions less than 5, the ECO
 * was not implemented in the console firmware.  If it's revision 5 or
 * greater we can get the name of the platक्रमm as an ASCII string from
 * the HWRPB.  That's what this function करोes.  It checks the revision
 * level and अगर the string is in the HWRPB it वापसs the address of
 * the string--a poपूर्णांकer to the name of the platक्रमm.
 *
 * Returns:
 *      - Poपूर्णांकer to a ASCII string अगर it's in the HWRPB
 *      - Poपूर्णांकer to a blank string अगर the data is not in the HWRPB.
 */

अटल अक्षर *
platक्रमm_string(व्योम)
अणु
	काष्ठा dsr_काष्ठा *dsr;
	अटल अक्षर unk_प्रणाली_string[] = "N/A";

	/* Go to the console क्रम the string poपूर्णांकer.
	 * If the rpb_vers is not 5 or greater the rpb
	 * is old and करोes not have this data in it.
	 */
	अगर (hwrpb->revision < 5)
		वापस (unk_प्रणाली_string);
	अन्यथा अणु
		/* The Dynamic System Recognition काष्ठा
		 * has the प्रणाली platक्रमm name starting
		 * after the अक्षरacter count of the string.
		 */
		dsr =  ((काष्ठा dsr_काष्ठा *)
			((अक्षर *)hwrpb + hwrpb->dsr_offset));
		वापस ((अक्षर *)dsr + (dsr->sysname_off +
				       माप(दीर्घ)));
	पूर्ण
पूर्ण

अटल पूर्णांक
get_nr_processors(काष्ठा percpu_काष्ठा *cpubase, अचिन्हित दीर्घ num)
अणु
	काष्ठा percpu_काष्ठा *cpu;
	अचिन्हित दीर्घ i;
	पूर्णांक count = 0;

	क्रम (i = 0; i < num; i++) अणु
		cpu = (काष्ठा percpu_काष्ठा *)
			((अक्षर *)cpubase + i*hwrpb->processor_size);
		अगर ((cpu->flags & 0x1cc) == 0x1cc)
			count++;
	पूर्ण
	वापस count;
पूर्ण

अटल व्योम
show_cache_size (काष्ठा seq_file *f, स्थिर अक्षर *which, पूर्णांक shape)
अणु
	अगर (shape == -1)
		seq_म_लिखो (f, "%s\t\t: n/a\n", which);
	अन्यथा अगर (shape == 0)
		seq_म_लिखो (f, "%s\t\t: unknown\n", which);
	अन्यथा
		seq_म_लिखो (f, "%s\t\t: %dK, %d-way, %db line\n",
			    which, shape >> 10, shape & 15,
			    1 << ((shape >> 4) & 15));
पूर्ण

अटल पूर्णांक
show_cpuinfo(काष्ठा seq_file *f, व्योम *slot)
अणु
	बाह्य काष्ठा unaligned_stat अणु
		अचिन्हित दीर्घ count, va, pc;
	पूर्ण unaligned[2];

	अटल अक्षर cpu_names[][8] = अणु
		"EV3", "EV4", "Simulate", "LCA4", "EV5", "EV45", "EV56",
		"EV6", "PCA56", "PCA57", "EV67", "EV68CB", "EV68AL",
		"EV68CX", "EV7", "EV79", "EV69"
	पूर्ण;

	काष्ठा percpu_काष्ठा *cpu = slot;
	अचिन्हित पूर्णांक cpu_index;
	अक्षर *cpu_name;
	अक्षर *systype_name;
	अक्षर *sysvariation_name;
	पूर्णांक nr_processors;
	अचिन्हित दीर्घ समयr_freq;

	cpu_index = (अचिन्हित) (cpu->type - 1);
	cpu_name = "Unknown";
	अगर (cpu_index < ARRAY_SIZE(cpu_names))
		cpu_name = cpu_names[cpu_index];

	get_sysnames(hwrpb->sys_type, hwrpb->sys_variation,
		     cpu->type, &systype_name, &sysvariation_name);

	nr_processors = get_nr_processors(cpu, hwrpb->nr_processors);

#अगर CONFIG_HZ == 1024 || CONFIG_HZ == 1200
	समयr_freq = (100UL * hwrpb->पूर्णांकr_freq) / 4096;
#अन्यथा
	समयr_freq = 100UL * CONFIG_HZ;
#पूर्ण_अगर

	seq_म_लिखो(f, "cpu\t\t\t: Alpha\n"
		      "cpu model\t\t: %s\n"
		      "cpu variation\t\t: %ld\n"
		      "cpu revision\t\t: %ld\n"
		      "cpu serial number\t: %s\n"
		      "system type\t\t: %s\n"
		      "system variation\t: %s\n"
		      "system revision\t\t: %ld\n"
		      "system serial number\t: %s\n"
		      "cycle frequency [Hz]\t: %lu %s\n"
		      "timer frequency [Hz]\t: %lu.%02lu\n"
		      "page size [bytes]\t: %ld\n"
		      "phys. address bits\t: %ld\n"
		      "max. addr. space #\t: %ld\n"
		      "BogoMIPS\t\t: %lu.%02lu\n"
		      "kernel unaligned acc\t: %ld (pc=%lx,va=%lx)\n"
		      "user unaligned acc\t: %ld (pc=%lx,va=%lx)\n"
		      "platform string\t\t: %s\n"
		      "cpus detected\t\t: %d\n",
		       cpu_name, cpu->variation, cpu->revision,
		       (अक्षर*)cpu->serial_no,
		       systype_name, sysvariation_name, hwrpb->sys_revision,
		       (अक्षर*)hwrpb->ssn,
		       est_cycle_freq ? : hwrpb->cycle_freq,
		       est_cycle_freq ? "est." : "",
		       समयr_freq / 100, समयr_freq % 100,
		       hwrpb->pagesize,
		       hwrpb->pa_bits,
		       hwrpb->max_asn,
		       loops_per_jअगरfy / (500000/HZ),
		       (loops_per_jअगरfy / (5000/HZ)) % 100,
		       unaligned[0].count, unaligned[0].pc, unaligned[0].va,
		       unaligned[1].count, unaligned[1].pc, unaligned[1].va,
		       platक्रमm_string(), nr_processors);

#अगर_घोषित CONFIG_SMP
	seq_म_लिखो(f, "cpus active\t\t: %u\n"
		      "cpu active mask\t\t: %016lx\n",
		       num_online_cpus(), cpumask_bits(cpu_possible_mask)[0]);
#पूर्ण_अगर

	show_cache_size (f, "L1 Icache", alpha_l1i_cacheshape);
	show_cache_size (f, "L1 Dcache", alpha_l1d_cacheshape);
	show_cache_size (f, "L2 cache", alpha_l2_cacheshape);
	show_cache_size (f, "L3 cache", alpha_l3_cacheshape);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
पढ़ो_mem_block(पूर्णांक *addr, पूर्णांक stride, पूर्णांक size)
अणु
	दीर्घ nloads = size / stride, cnt, पंचांगp;

	__यंत्र__ __अस्थिर__(
	"	rpcc    %0\n"
	"1:	ldl	%3,0(%2)\n"
	"	subq	%1,1,%1\n"
	/* Next two XORs पूर्णांकroduce an explicit data dependency between
	   consecutive loads in the loop, which will give us true load
	   latency. */
	"	xor	%3,%2,%2\n"
	"	xor	%3,%2,%2\n"
	"	addq	%2,%4,%2\n"
	"	bne	%1,1b\n"
	"	rpcc	%3\n"
	"	subl	%3,%0,%0\n"
	: "=&r" (cnt), "=&r" (nloads), "=&r" (addr), "=&r" (पंचांगp)
	: "r" (stride), "1" (nloads), "2" (addr));

	वापस cnt / (size / stride);
पूर्ण

#घोषणा CSHAPE(totalsize, linesize, assoc) \
  ((totalsize & ~0xff) | (linesize << 4) | assoc)

/* ??? EV5 supports up to 64M, but did the प्रणालीs with more than
   16M of BCACHE ever exist? */
#घोषणा MAX_BCACHE_SIZE	16*1024*1024

/* Note that the offchip caches are direct mapped on all Alphas. */
अटल पूर्णांक __init
बाह्यal_cache_probe(पूर्णांक minsize, पूर्णांक width)
अणु
	पूर्णांक cycles, prev_cycles = 1000000;
	पूर्णांक stride = 1 << width;
	दीर्घ size = minsize, maxsize = MAX_BCACHE_SIZE * 2;

	अगर (maxsize > (max_low_pfn + 1) << PAGE_SHIFT)
		maxsize = 1 << (ilog2(max_low_pfn + 1) + PAGE_SHIFT);

	/* Get the first block cached. */
	पढ़ो_mem_block(__va(0), stride, size);

	जबतक (size < maxsize) अणु
		/* Get an average load latency in cycles. */
		cycles = पढ़ो_mem_block(__va(0), stride, size);
		अगर (cycles > prev_cycles * 2) अणु
			/* Fine, we exceed the cache. */
			prपूर्णांकk("%ldK Bcache detected; load hit latency %d "
			       "cycles, load miss latency %d cycles\n",
			       size >> 11, prev_cycles, cycles);
			वापस CSHAPE(size >> 1, width, 1);
		पूर्ण
		/* Try to get the next block cached. */
		पढ़ो_mem_block(__va(size), stride, size);
		prev_cycles = cycles;
		size <<= 1;
	पूर्ण
	वापस -1;	/* No BCACHE found. */
पूर्ण

अटल व्योम __init
determine_cpu_caches (अचिन्हित पूर्णांक cpu_type)
अणु
	पूर्णांक L1I, L1D, L2, L3;

	चयन (cpu_type) अणु
	हाल EV4_CPU:
	हाल EV45_CPU:
	  अणु
		अगर (cpu_type == EV4_CPU)
			L1I = CSHAPE(8*1024, 5, 1);
		अन्यथा
			L1I = CSHAPE(16*1024, 5, 1);
		L1D = L1I;
		L3 = -1;
	
		/* BIU_CTL is a ग_लिखो-only Abox रेजिस्टर.  PALcode has a
		   shaकरोw copy, and may be available from some versions
		   of the CSERVE PALcall.  If we can get it, then

			अचिन्हित दीर्घ biu_ctl, size;
			size = 128*1024 * (1 << ((biu_ctl >> 28) & 7));
			L2 = CSHAPE (size, 5, 1);

		   Unक्रमtunately, we can't rely on that.
		*/
		L2 = बाह्यal_cache_probe(128*1024, 5);
		अवरोध;
	  पूर्ण

	हाल LCA4_CPU:
	  अणु
		अचिन्हित दीर्घ car, size;

		L1I = L1D = CSHAPE(8*1024, 5, 1);
		L3 = -1;

		car = *(vuip) phys_to_virt (0x120000078UL);
		size = 64*1024 * (1 << ((car >> 5) & 7));
		/* No typo -- 8 byte cacheline size.  Whodathunk.  */
		L2 = (car & 1 ? CSHAPE (size, 3, 1) : -1);
		अवरोध;
	  पूर्ण

	हाल EV5_CPU:
	हाल EV56_CPU:
	  अणु
		अचिन्हित दीर्घ sc_ctl, width;

		L1I = L1D = CSHAPE(8*1024, 5, 1);

		/* Check the line size of the Scache.  */
		sc_ctl = *(vulp) phys_to_virt (0xfffff000a8UL);
		width = sc_ctl & 0x1000 ? 6 : 5;
		L2 = CSHAPE (96*1024, width, 3);

		/* BC_CONTROL and BC_CONFIG are ग_लिखो-only IPRs.  PALcode
		   has a shaकरोw copy, and may be available from some versions
		   of the CSERVE PALcall.  If we can get it, then

			अचिन्हित दीर्घ bc_control, bc_config, size;
			size = 1024*1024 * (1 << ((bc_config & 7) - 1));
			L3 = (bc_control & 1 ? CSHAPE (size, width, 1) : -1);

		   Unक्रमtunately, we can't rely on that.
		*/
		L3 = बाह्यal_cache_probe(1024*1024, width);
		अवरोध;
	  पूर्ण

	हाल PCA56_CPU:
	हाल PCA57_CPU:
	  अणु
		अगर (cpu_type == PCA56_CPU) अणु
			L1I = CSHAPE(16*1024, 6, 1);
			L1D = CSHAPE(8*1024, 5, 1);
		पूर्ण अन्यथा अणु
			L1I = CSHAPE(32*1024, 6, 2);
			L1D = CSHAPE(16*1024, 5, 1);
		पूर्ण
		L3 = -1;

#अगर 0
		अचिन्हित दीर्घ cbox_config, size;

		cbox_config = *(vulp) phys_to_virt (0xfffff00008UL);
		size = 512*1024 * (1 << ((cbox_config >> 12) & 3));

		L2 = ((cbox_config >> 31) & 1 ? CSHAPE (size, 6, 1) : -1);
#अन्यथा
		L2 = बाह्यal_cache_probe(512*1024, 6);
#पूर्ण_अगर
		अवरोध;
	  पूर्ण

	हाल EV6_CPU:
	हाल EV67_CPU:
	हाल EV68CB_CPU:
	हाल EV68AL_CPU:
	हाल EV68CX_CPU:
	हाल EV69_CPU:
		L1I = L1D = CSHAPE(64*1024, 6, 2);
		L2 = बाह्यal_cache_probe(1024*1024, 6);
		L3 = -1;
		अवरोध;

	हाल EV7_CPU:
	हाल EV79_CPU:
		L1I = L1D = CSHAPE(64*1024, 6, 2);
		L2 = CSHAPE(7*1024*1024/4, 6, 7);
		L3 = -1;
		अवरोध;

	शेष:
		/* Nothing known about this cpu type.  */
		L1I = L1D = L2 = L3 = 0;
		अवरोध;
	पूर्ण

	alpha_l1i_cacheshape = L1I;
	alpha_l1d_cacheshape = L1D;
	alpha_l2_cacheshape = L2;
	alpha_l3_cacheshape = L3;
पूर्ण

/*
 * We show only CPU #0 info.
 */
अटल व्योम *
c_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	वापस *pos ? शून्य : (अक्षर *)hwrpb + hwrpb->processor_offset;
पूर्ण

अटल व्योम *
c_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल व्योम
c_stop(काष्ठा seq_file *f, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;


अटल पूर्णांक
alpha_panic_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
#अगर 1
	/* FIXME FIXME FIXME */
	/* If we are using SRM and serial console, just hard halt here. */
	अगर (alpha_using_srm && srmcons_output)
		__halt();
#पूर्ण_अगर
        वापस NOTIFY_DONE;
पूर्ण

अटल __init पूर्णांक add_pcspkr(व्योम)
अणु
	काष्ठा platक्रमm_device *pd;
	पूर्णांक ret;

	pd = platक्रमm_device_alloc("pcspkr", -1);
	अगर (!pd)
		वापस -ENOMEM;

	ret = platक्रमm_device_add(pd);
	अगर (ret)
		platक्रमm_device_put(pd);

	वापस ret;
पूर्ण
device_initcall(add_pcspkr);
