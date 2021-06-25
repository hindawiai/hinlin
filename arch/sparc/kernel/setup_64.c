<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/sparc64/kernel/setup.c
 *
 *  Copyright (C) 1995,1996  David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1997       Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/smp.h>
#समावेश <linux/user.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/inet.h>
#समावेश <linux/console.h>
#समावेश <linux/root_dev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpu.h>
#समावेश <linux/initrd.h>
#समावेश <linux/module.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/memblock.h>
#समावेश <uapi/linux/mount.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/starfire.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/ns87303.h>
#समावेश <यंत्र/btext.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/irq.h>

#अगर_घोषित CONFIG_IP_PNP
#समावेश <net/ipconfig.h>
#पूर्ण_अगर

#समावेश "entry.h"
#समावेश "kernel.h"

/* Used to synchronize accesses to NatSemi SUPER I/O chip configure
 * operations in यंत्र/ns87303.h
 */
DEFINE_SPINLOCK(ns87303_lock);
EXPORT_SYMBOL(ns87303_lock);

काष्ठा screen_info screen_info = अणु
	0, 0,			/* orig-x, orig-y */
	0,			/* unused */
	0,			/* orig-video-page */
	0,			/* orig-video-mode */
	128,			/* orig-video-cols */
	0, 0, 0,		/* unused, ega_bx, unused */
	54,			/* orig-video-lines */
	0,                      /* orig-video-isVGA */
	16                      /* orig-video-poपूर्णांकs */
पूर्ण;

अटल व्योम
prom_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित पूर्णांक n)
अणु
	prom_ग_लिखो(s, n);
पूर्ण

/* Exported क्रम mm/init.c:paging_init. */
अचिन्हित दीर्घ cmdline_memory_size = 0;

अटल काष्ठा console prom_early_console = अणु
	.name =		"earlyprom",
	.ग_लिखो =	prom_console_ग_लिखो,
	.flags =	CON_PRINTBUFFER | CON_BOOT | CON_ANYTIME,
	.index =	-1,
पूर्ण;

/*
 * Process kernel command line चयनes that are specअगरic to the
 * SPARC or that require special low-level processing.
 */
अटल व्योम __init process_चयन(अक्षर c)
अणु
	चयन (c) अणु
	हाल 'd':
	हाल 's':
		अवरोध;
	हाल 'h':
		prom_म_लिखो("boot_flags_init: Halt!\n");
		prom_halt();
		अवरोध;
	हाल 'p':
		prom_early_console.flags &= ~CON_BOOT;
		अवरोध;
	हाल 'P':
		/* Force UltraSPARC-III P-Cache on. */
		अगर (tlb_type != cheetah) अणु
			prपूर्णांकk("BOOT: Ignoring P-Cache force option.\n");
			अवरोध;
		पूर्ण
		cheetah_pcache_क्रमced_on = 1;
		add_taपूर्णांक(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);
		cheetah_enable_pcache();
		अवरोध;

	शेष:
		prपूर्णांकk("Unknown boot switch (-%c)\n", c);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __init boot_flags_init(अक्षर *commands)
अणु
	जबतक (*commands) अणु
		/* Move to the start of the next "argument". */
		जबतक (*commands == ' ')
			commands++;

		/* Process any command चयनes, otherwise skip it. */
		अगर (*commands == '\0')
			अवरोध;
		अगर (*commands == '-') अणु
			commands++;
			जबतक (*commands && *commands != ' ')
				process_चयन(*commands++);
			जारी;
		पूर्ण
		अगर (!म_भेदन(commands, "mem=", 4))
			cmdline_memory_size = memparse(commands + 4, &commands);

		जबतक (*commands && *commands != ' ')
			commands++;
	पूर्ण
पूर्ण

बाह्य अचिन्हित लघु root_flags;
बाह्य अचिन्हित लघु root_dev;
बाह्य अचिन्हित लघु ram_flags;
#घोषणा RAMDISK_IMAGE_START_MASK	0x07FF
#घोषणा RAMDISK_PROMPT_FLAG		0x8000
#घोषणा RAMDISK_LOAD_FLAG		0x4000

बाह्य पूर्णांक root_mountflags;

अक्षर reboot_command[COMMAND_LINE_SIZE];

अटल व्योम __init per_cpu_patch(व्योम)
अणु
	काष्ठा cpuid_patch_entry *p;
	अचिन्हित दीर्घ ver;
	पूर्णांक is_jbus;

	अगर (tlb_type == spitfire && !this_is_starfire)
		वापस;

	is_jbus = 0;
	अगर (tlb_type != hypervisor) अणु
		__यंत्र__ ("rdpr %%ver, %0" : "=r" (ver));
		is_jbus = ((ver >> 32UL) == __JALAPENO_ID ||
			   (ver >> 32UL) == __SERRANO_ID);
	पूर्ण

	p = &__cpuid_patch;
	जबतक (p < &__cpuid_patch_end) अणु
		अचिन्हित दीर्घ addr = p->addr;
		अचिन्हित पूर्णांक *insns;

		चयन (tlb_type) अणु
		हाल spitfire:
			insns = &p->starfire[0];
			अवरोध;
		हाल cheetah:
		हाल cheetah_plus:
			अगर (is_jbus)
				insns = &p->cheetah_jbus[0];
			अन्यथा
				insns = &p->cheetah_safari[0];
			अवरोध;
		हाल hypervisor:
			insns = &p->sun4v[0];
			अवरोध;
		शेष:
			prom_म_लिखो("Unknown cpu type, halting.\n");
			prom_halt();
		पूर्ण

		*(अचिन्हित पूर्णांक *) (addr +  0) = insns[0];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  0));

		*(अचिन्हित पूर्णांक *) (addr +  4) = insns[1];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  4));

		*(अचिन्हित पूर्णांक *) (addr +  8) = insns[2];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  8));

		*(अचिन्हित पूर्णांक *) (addr + 12) = insns[3];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr + 12));

		p++;
	पूर्ण
पूर्ण

व्योम sun4v_patch_1insn_range(काष्ठा sun4v_1insn_patch_entry *start,
			     काष्ठा sun4v_1insn_patch_entry *end)
अणु
	जबतक (start < end) अणु
		अचिन्हित दीर्घ addr = start->addr;

		*(अचिन्हित पूर्णांक *) (addr +  0) = start->insn;
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  0));

		start++;
	पूर्ण
पूर्ण

व्योम sun4v_patch_2insn_range(काष्ठा sun4v_2insn_patch_entry *start,
			     काष्ठा sun4v_2insn_patch_entry *end)
अणु
	जबतक (start < end) अणु
		अचिन्हित दीर्घ addr = start->addr;

		*(अचिन्हित पूर्णांक *) (addr +  0) = start->insns[0];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  0));

		*(अचिन्हित पूर्णांक *) (addr +  4) = start->insns[1];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  4));

		start++;
	पूर्ण
पूर्ण

व्योम sun_m7_patch_2insn_range(काष्ठा sun4v_2insn_patch_entry *start,
			     काष्ठा sun4v_2insn_patch_entry *end)
अणु
	जबतक (start < end) अणु
		अचिन्हित दीर्घ addr = start->addr;

		*(अचिन्हित पूर्णांक *) (addr +  0) = start->insns[0];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  0));

		*(अचिन्हित पूर्णांक *) (addr +  4) = start->insns[1];
		wmb();
		__यंत्र__ __अस्थिर__("flush	%0" : : "r" (addr +  4));

		start++;
	पूर्ण
पूर्ण

अटल व्योम __init sun4v_patch(व्योम)
अणु
	बाह्य व्योम sun4v_hvapi_init(व्योम);

	अगर (tlb_type != hypervisor)
		वापस;

	sun4v_patch_1insn_range(&__sun4v_1insn_patch,
				&__sun4v_1insn_patch_end);

	sun4v_patch_2insn_range(&__sun4v_2insn_patch,
				&__sun4v_2insn_patch_end);

	चयन (sun4v_chip_type) अणु
	हाल SUN4V_CHIP_SPARC_M7:
	हाल SUN4V_CHIP_SPARC_M8:
	हाल SUN4V_CHIP_SPARC_SN:
		sun4v_patch_1insn_range(&__sun_m7_1insn_patch,
					&__sun_m7_1insn_patch_end);
		sun_m7_patch_2insn_range(&__sun_m7_2insn_patch,
					 &__sun_m7_2insn_patch_end);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (sun4v_chip_type != SUN4V_CHIP_NIAGARA1) अणु
		sun4v_patch_1insn_range(&__fast_win_ctrl_1insn_patch,
					&__fast_win_ctrl_1insn_patch_end);
	पूर्ण

	sun4v_hvapi_init();
पूर्ण

अटल व्योम __init popc_patch(व्योम)
अणु
	काष्ठा popc_3insn_patch_entry *p3;
	काष्ठा popc_6insn_patch_entry *p6;

	p3 = &__popc_3insn_patch;
	जबतक (p3 < &__popc_3insn_patch_end) अणु
		अचिन्हित दीर्घ i, addr = p3->addr;

		क्रम (i = 0; i < 3; i++) अणु
			*(अचिन्हित पूर्णांक *) (addr +  (i * 4)) = p3->insns[i];
			wmb();
			__यंत्र__ __अस्थिर__("flush	%0"
					     : : "r" (addr +  (i * 4)));
		पूर्ण

		p3++;
	पूर्ण

	p6 = &__popc_6insn_patch;
	जबतक (p6 < &__popc_6insn_patch_end) अणु
		अचिन्हित दीर्घ i, addr = p6->addr;

		क्रम (i = 0; i < 6; i++) अणु
			*(अचिन्हित पूर्णांक *) (addr +  (i * 4)) = p6->insns[i];
			wmb();
			__यंत्र__ __अस्थिर__("flush	%0"
					     : : "r" (addr +  (i * 4)));
		पूर्ण

		p6++;
	पूर्ण
पूर्ण

अटल व्योम __init छोड़ो_patch(व्योम)
अणु
	काष्ठा छोड़ो_patch_entry *p;

	p = &__छोड़ो_3insn_patch;
	जबतक (p < &__छोड़ो_3insn_patch_end) अणु
		अचिन्हित दीर्घ i, addr = p->addr;

		क्रम (i = 0; i < 3; i++) अणु
			*(अचिन्हित पूर्णांक *) (addr +  (i * 4)) = p->insns[i];
			wmb();
			__यंत्र__ __अस्थिर__("flush	%0"
					     : : "r" (addr +  (i * 4)));
		पूर्ण

		p++;
	पूर्ण
पूर्ण

व्योम __init start_early_boot(व्योम)
अणु
	पूर्णांक cpu;

	check_अगर_starfire();
	per_cpu_patch();
	sun4v_patch();
	smp_init_cpu_poke();

	cpu = hard_smp_processor_id();
	अगर (cpu >= NR_CPUS) अणु
		prom_म_लिखो("Serious problem, boot cpu id (%d) >= NR_CPUS (%d)\n",
			    cpu, NR_CPUS);
		prom_halt();
	पूर्ण
	current_thपढ़ो_info()->cpu = cpu;

	समय_init_early();
	prom_init_report();
	start_kernel();
पूर्ण

/* On Ultra, we support all of the v8 capabilities. */
अचिन्हित दीर्घ sparc64_elf_hwcap = (HWCAP_SPARC_FLUSH | HWCAP_SPARC_STBAR |
				   HWCAP_SPARC_SWAP | HWCAP_SPARC_MULDIV |
				   HWCAP_SPARC_V9);
EXPORT_SYMBOL(sparc64_elf_hwcap);

अटल स्थिर अक्षर *hwcaps[] = अणु
	"flush", "stbar", "swap", "muldiv", "v9",
	"ultra3", "blkinit", "n2",

	/* These strings are as they appear in the machine description
	 * 'hwcap-list' property क्रम cpu nodes.
	 */
	"mul32", "div32", "fsmuld", "v8plus", "popc", "vis", "vis2",
	"ASIBlkInit", "fmaf", "vis3", "hpc", "random", "trans", "fjfmau",
	"ima", "cspare", "pause", "cbcond", शून्य /*reserved क्रम crypto */,
	"adp",
पूर्ण;

अटल स्थिर अक्षर *crypto_hwcaps[] = अणु
	"aes", "des", "kasumi", "camellia", "md5", "sha1", "sha256",
	"sha512", "mpmul", "montmul", "montsqr", "crc32c",
पूर्ण;

व्योम cpucap_info(काष्ठा seq_file *m)
अणु
	अचिन्हित दीर्घ caps = sparc64_elf_hwcap;
	पूर्णांक i, prपूर्णांकed = 0;

	seq_माला_दो(m, "cpucaps\t\t: ");
	क्रम (i = 0; i < ARRAY_SIZE(hwcaps); i++) अणु
		अचिन्हित दीर्घ bit = 1UL << i;
		अगर (hwcaps[i] && (caps & bit)) अणु
			seq_म_लिखो(m, "%s%s",
				   prपूर्णांकed ? "," : "", hwcaps[i]);
			prपूर्णांकed++;
		पूर्ण
	पूर्ण
	अगर (caps & HWCAP_SPARC_CRYPTO) अणु
		अचिन्हित दीर्घ cfr;

		__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));
		क्रम (i = 0; i < ARRAY_SIZE(crypto_hwcaps); i++) अणु
			अचिन्हित दीर्घ bit = 1UL << i;
			अगर (cfr & bit) अणु
				seq_म_लिखो(m, "%s%s",
					   prपूर्णांकed ? "," : "", crypto_hwcaps[i]);
				prपूर्णांकed++;
			पूर्ण
		पूर्ण
	पूर्ण
	seq_अ_दो(m, '\n');
पूर्ण

अटल व्योम __init report_one_hwcap(पूर्णांक *prपूर्णांकed, स्थिर अक्षर *name)
अणु
	अगर ((*prपूर्णांकed) == 0)
		prपूर्णांकk(KERN_INFO "CPU CAPS: [");
	prपूर्णांकk(KERN_CONT "%s%s",
	       (*prपूर्णांकed) ? "," : "", name);
	अगर (++(*prपूर्णांकed) == 8) अणु
		prपूर्णांकk(KERN_CONT "]\n");
		*prपूर्णांकed = 0;
	पूर्ण
पूर्ण

अटल व्योम __init report_crypto_hwcaps(पूर्णांक *prपूर्णांकed)
अणु
	अचिन्हित दीर्घ cfr;
	पूर्णांक i;

	__यंत्र__ __अस्थिर__("rd %%asr26, %0" : "=r" (cfr));

	क्रम (i = 0; i < ARRAY_SIZE(crypto_hwcaps); i++) अणु
		अचिन्हित दीर्घ bit = 1UL << i;
		अगर (cfr & bit)
			report_one_hwcap(prपूर्णांकed, crypto_hwcaps[i]);
	पूर्ण
पूर्ण

अटल व्योम __init report_hwcaps(अचिन्हित दीर्घ caps)
अणु
	पूर्णांक i, prपूर्णांकed = 0;

	क्रम (i = 0; i < ARRAY_SIZE(hwcaps); i++) अणु
		अचिन्हित दीर्घ bit = 1UL << i;
		अगर (hwcaps[i] && (caps & bit))
			report_one_hwcap(&prपूर्णांकed, hwcaps[i]);
	पूर्ण
	अगर (caps & HWCAP_SPARC_CRYPTO)
		report_crypto_hwcaps(&prपूर्णांकed);
	अगर (prपूर्णांकed != 0)
		prपूर्णांकk(KERN_CONT "]\n");
पूर्ण

अटल अचिन्हित दीर्घ __init mdesc_cpu_hwcap_list(व्योम)
अणु
	काष्ठा mdesc_handle *hp;
	अचिन्हित दीर्घ caps = 0;
	स्थिर अक्षर *prop;
	पूर्णांक len;
	u64 pn;

	hp = mdesc_grab();
	अगर (!hp)
		वापस 0;

	pn = mdesc_node_by_name(hp, MDESC_NODE_शून्य, "cpu");
	अगर (pn == MDESC_NODE_शून्य)
		जाओ out;

	prop = mdesc_get_property(hp, pn, "hwcap-list", &len);
	अगर (!prop)
		जाओ out;

	जबतक (len) अणु
		पूर्णांक i, plen;

		क्रम (i = 0; i < ARRAY_SIZE(hwcaps); i++) अणु
			अचिन्हित दीर्घ bit = 1UL << i;

			अगर (hwcaps[i] && !म_भेद(prop, hwcaps[i])) अणु
				caps |= bit;
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(crypto_hwcaps); i++) अणु
			अगर (!म_भेद(prop, crypto_hwcaps[i]))
				caps |= HWCAP_SPARC_CRYPTO;
		पूर्ण

		plen = म_माप(prop) + 1;
		prop += plen;
		len -= plen;
	पूर्ण

out:
	mdesc_release(hp);
	वापस caps;
पूर्ण

/* This yields a mask that user programs can use to figure out what
 * inकाष्ठाion set this cpu supports.
 */
अटल व्योम __init init_sparc64_elf_hwcap(व्योम)
अणु
	अचिन्हित दीर्घ cap = sparc64_elf_hwcap;
	अचिन्हित दीर्घ mdesc_caps;

	अगर (tlb_type == cheetah || tlb_type == cheetah_plus)
		cap |= HWCAP_SPARC_ULTRA3;
	अन्यथा अगर (tlb_type == hypervisor) अणु
		अगर (sun4v_chip_type == SUN4V_CHIP_NIAGARA1 ||
		    sun4v_chip_type == SUN4V_CHIP_NIAGARA2 ||
		    sun4v_chip_type == SUN4V_CHIP_NIAGARA3 ||
		    sun4v_chip_type == SUN4V_CHIP_NIAGARA4 ||
		    sun4v_chip_type == SUN4V_CHIP_NIAGARA5 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_M6 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_M7 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_M8 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_SN ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC64X)
			cap |= HWCAP_SPARC_BLKINIT;
		अगर (sun4v_chip_type == SUN4V_CHIP_NIAGARA2 ||
		    sun4v_chip_type == SUN4V_CHIP_NIAGARA3 ||
		    sun4v_chip_type == SUN4V_CHIP_NIAGARA4 ||
		    sun4v_chip_type == SUN4V_CHIP_NIAGARA5 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_M6 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_M7 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_M8 ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC_SN ||
		    sun4v_chip_type == SUN4V_CHIP_SPARC64X)
			cap |= HWCAP_SPARC_N2;
	पूर्ण

	cap |= (AV_SPARC_MUL32 | AV_SPARC_DIV32 | AV_SPARC_V8PLUS);

	mdesc_caps = mdesc_cpu_hwcap_list();
	अगर (!mdesc_caps) अणु
		अगर (tlb_type == spitfire)
			cap |= AV_SPARC_VIS;
		अगर (tlb_type == cheetah || tlb_type == cheetah_plus)
			cap |= AV_SPARC_VIS | AV_SPARC_VIS2;
		अगर (tlb_type == cheetah_plus) अणु
			अचिन्हित दीर्घ impl, ver;

			__यंत्र__ __अस्थिर__("rdpr %%ver, %0" : "=r" (ver));
			impl = ((ver >> 32) & 0xffff);
			अगर (impl == PANTHER_IMPL)
				cap |= AV_SPARC_POPC;
		पूर्ण
		अगर (tlb_type == hypervisor) अणु
			अगर (sun4v_chip_type == SUN4V_CHIP_NIAGARA1)
				cap |= AV_SPARC_ASI_BLK_INIT;
			अगर (sun4v_chip_type == SUN4V_CHIP_NIAGARA2 ||
			    sun4v_chip_type == SUN4V_CHIP_NIAGARA3 ||
			    sun4v_chip_type == SUN4V_CHIP_NIAGARA4 ||
			    sun4v_chip_type == SUN4V_CHIP_NIAGARA5 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_M6 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_M7 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_M8 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_SN ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC64X)
				cap |= (AV_SPARC_VIS | AV_SPARC_VIS2 |
					AV_SPARC_ASI_BLK_INIT |
					AV_SPARC_POPC);
			अगर (sun4v_chip_type == SUN4V_CHIP_NIAGARA3 ||
			    sun4v_chip_type == SUN4V_CHIP_NIAGARA4 ||
			    sun4v_chip_type == SUN4V_CHIP_NIAGARA5 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_M6 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_M7 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_M8 ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC_SN ||
			    sun4v_chip_type == SUN4V_CHIP_SPARC64X)
				cap |= (AV_SPARC_VIS3 | AV_SPARC_HPC |
					AV_SPARC_FMAF);
		पूर्ण
	पूर्ण
	sparc64_elf_hwcap = cap | mdesc_caps;

	report_hwcaps(sparc64_elf_hwcap);

	अगर (sparc64_elf_hwcap & AV_SPARC_POPC)
		popc_patch();
	अगर (sparc64_elf_hwcap & AV_SPARC_PAUSE)
		छोड़ो_patch();
पूर्ण

व्योम __init alloc_irqstack_booपंचांगem(व्योम)
अणु
	अचिन्हित पूर्णांक i, node;

	क्रम_each_possible_cpu(i) अणु
		node = cpu_to_node(i);

		softirq_stack[i] = memblock_alloc_node(THREAD_SIZE,
						       THREAD_SIZE, node);
		अगर (!softirq_stack[i])
			panic("%s: Failed to allocate %lu bytes align=%lx nid=%d\n",
			      __func__, THREAD_SIZE, THREAD_SIZE, node);
		hardirq_stack[i] = memblock_alloc_node(THREAD_SIZE,
						       THREAD_SIZE, node);
		अगर (!hardirq_stack[i])
			panic("%s: Failed to allocate %lu bytes align=%lx nid=%d\n",
			      __func__, THREAD_SIZE, THREAD_SIZE, node);
	पूर्ण
पूर्ण

व्योम __init setup_arch(अक्षर **cmdline_p)
अणु
	/* Initialize PROM console and command line. */
	*cmdline_p = prom_getbootargs();
	strlcpy(boot_command_line, *cmdline_p, COMMAND_LINE_SIZE);
	parse_early_param();

	boot_flags_init(*cmdline_p);
#अगर_घोषित CONFIG_EARLYFB
	अगर (btext_find_display())
#पूर्ण_अगर
		रेजिस्टर_console(&prom_early_console);

	अगर (tlb_type == hypervisor)
		pr_info("ARCH: SUN4V\n");
	अन्यथा
		pr_info("ARCH: SUN4U\n");

	idprom_init();

	अगर (!root_flags)
		root_mountflags &= ~MS_RDONLY;
	ROOT_DEV = old_decode_dev(root_dev);
#अगर_घोषित CONFIG_BLK_DEV_RAM
	rd_image_start = ram_flags & RAMDISK_IMAGE_START_MASK;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IP_PNP
	अगर (!ic_set_manually) अणु
		phandle chosen = prom_finddevice("/chosen");
		u32 cl, sv, gw;

		cl = prom_getपूर्णांकशेष (chosen, "client-ip", 0);
		sv = prom_getपूर्णांकशेष (chosen, "server-ip", 0);
		gw = prom_getपूर्णांकशेष (chosen, "gateway-ip", 0);
		अगर (cl && sv) अणु
			ic_myaddr = cl;
			ic_servaddr = sv;
			अगर (gw)
				ic_gateway = gw;
#अगर defined(CONFIG_IP_PNP_BOOTP) || defined(CONFIG_IP_PNP_RARP)
			ic_proto_enabled = 0;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Get boot processor trap_block[] setup.  */
	init_cur_cpu_trap(current_thपढ़ो_info());

	paging_init();
	init_sparc64_elf_hwcap();
	smp_fill_in_cpu_possible_map();
	/*
	 * Once the OF device tree and MDESC have been setup and nr_cpus has
	 * been parsed, we know the list of possible cpus.  Thereक्रमe we can
	 * allocate the IRQ stacks.
	 */
	alloc_irqstack_booपंचांगem();
पूर्ण

बाह्य पूर्णांक stop_a_enabled;

व्योम sun_करो_अवरोध(व्योम)
अणु
	अगर (!stop_a_enabled)
		वापस;

	prom_म_लिखो("\n");
	flush_user_winकरोws();

	prom_cmdline();
पूर्ण
EXPORT_SYMBOL(sun_करो_अवरोध);

पूर्णांक stop_a_enabled = 1;
EXPORT_SYMBOL(stop_a_enabled);
