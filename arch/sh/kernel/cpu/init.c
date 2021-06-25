<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/init.c
 *
 * CPU init code
 *
 * Copyright (C) 2002 - 2009  Paul Mundt
 * Copyright (C) 2003  Riअक्षरd Curnow
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/sh_मूलप्रण.स>
#समावेश <यंत्र/setup.h>

#अगर_घोषित CONFIG_SH_FPU
#घोषणा cpu_has_fpu	1
#अन्यथा
#घोषणा cpu_has_fpu	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_SH_DSP
#घोषणा cpu_has_dsp	1
#अन्यथा
#घोषणा cpu_has_dsp	0
#पूर्ण_अगर

/*
 * Generic wrapper क्रम command line arguments to disable on-chip
 * peripherals (nofpu, nodsp, and so क्रमth).
 */
#घोषणा onchip_setup(x)					\
अटल पूर्णांक x##_disabled = !cpu_has_##x;			\
							\
अटल पूर्णांक x##_setup(अक्षर *opts)			\
अणु							\
	x##_disabled = 1;				\
	वापस 1;					\
पूर्ण							\
__setup("no" __stringअगरy(x), x##_setup);

onchip_setup(fpu);
onchip_setup(dsp);

#अगर_घोषित CONFIG_SPECULATIVE_EXECUTION
#घोषणा CPUOPM		0xff2f0000
#घोषणा CPUOPM_RABD	(1 << 5)

अटल व्योम speculative_execution_init(व्योम)
अणु
	/* Clear RABD */
	__raw_ग_लिखोl(__raw_पढ़ोl(CPUOPM) & ~CPUOPM_RABD, CPUOPM);

	/* Flush the update */
	(व्योम)__raw_पढ़ोl(CPUOPM);
	ctrl_barrier();
पूर्ण
#अन्यथा
#घोषणा speculative_execution_init()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_SH4A
#घोषणा EXPMASK			0xff2f0004
#घोषणा EXPMASK_RTEDS		(1 << 0)
#घोषणा EXPMASK_BRDSSLP		(1 << 1)
#घोषणा EXPMASK_MMCAW		(1 << 4)

अटल व्योम expmask_init(व्योम)
अणु
	अचिन्हित दीर्घ expmask = __raw_पढ़ोl(EXPMASK);

	/*
	 * Future proofing.
	 *
	 * Disable support क्रम slottable sleep inकाष्ठाion, non-nop
	 * inकाष्ठाions in the rte delay slot, and associative ग_लिखोs to
	 * the memory-mapped cache array.
	 */
	expmask &= ~(EXPMASK_RTEDS | EXPMASK_BRDSSLP | EXPMASK_MMCAW);

	__raw_ग_लिखोl(expmask, EXPMASK);
	ctrl_barrier();
पूर्ण
#अन्यथा
#घोषणा expmask_init()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* 2nd-level cache init */
व्योम __attribute__ ((weak)) l2_cache_init(व्योम)
अणु
पूर्ण

/*
 * Generic first-level cache init
 */
#अगर !defined(CONFIG_CPU_J2)
अटल व्योम cache_init(व्योम)
अणु
	अचिन्हित दीर्घ ccr, flags;

	jump_to_uncached();
	ccr = __raw_पढ़ोl(SH_CCR);

	/*
	 * At this poपूर्णांक we करोn't know whether the cache is enabled or not - a
	 * bootloader may have enabled it.  There are at least 2 things that
	 * could be dirty in the cache at this poपूर्णांक:
	 * 1. kernel command line set up by boot loader
	 * 2. spilled रेजिस्टरs from the prolog of this function
	 * => beक्रमe re-initialising the cache, we must करो a purge of the whole
	 * cache out to memory क्रम safety.  As दीर्घ as nothing is spilled
	 * during the loop to lines that have alपढ़ोy been करोne, this is safe.
	 * - RPC
	 */
	अगर (ccr & CCR_CACHE_ENABLE) अणु
		अचिन्हित दीर्घ ways, waysize, addrstart;

		waysize = current_cpu_data.dcache.sets;

#अगर_घोषित CCR_CACHE_ORA
		/*
		 * If the OC is alपढ़ोy in RAM mode, we only have
		 * half of the entries to flush..
		 */
		अगर (ccr & CCR_CACHE_ORA)
			waysize >>= 1;
#पूर्ण_अगर

		waysize <<= current_cpu_data.dcache.entry_shअगरt;

#अगर_घोषित CCR_CACHE_EMODE
		/* If EMODE is not set, we only have 1 way to flush. */
		अगर (!(ccr & CCR_CACHE_EMODE))
			ways = 1;
		अन्यथा
#पूर्ण_अगर
			ways = current_cpu_data.dcache.ways;

		addrstart = CACHE_OC_ADDRESS_ARRAY;
		करो अणु
			अचिन्हित दीर्घ addr;

			क्रम (addr = addrstart;
			     addr < addrstart + waysize;
			     addr += current_cpu_data.dcache.linesz)
				__raw_ग_लिखोl(0, addr);

			addrstart += current_cpu_data.dcache.way_incr;
		पूर्ण जबतक (--ways);
	पूर्ण

	/*
	 * Default CCR values .. enable the caches
	 * and invalidate them immediately..
	 */
	flags = CCR_CACHE_ENABLE | CCR_CACHE_INVALIDATE;

#अगर_घोषित CCR_CACHE_EMODE
	/* Force EMODE अगर possible */
	अगर (current_cpu_data.dcache.ways > 1)
		flags |= CCR_CACHE_EMODE;
	अन्यथा
		flags &= ~CCR_CACHE_EMODE;
#पूर्ण_अगर

#अगर defined(CONFIG_CACHE_WRITETHROUGH)
	/* Write-through */
	flags |= CCR_CACHE_WT;
#या_अगर defined(CONFIG_CACHE_WRITEBACK)
	/* Write-back */
	flags |= CCR_CACHE_CB;
#अन्यथा
	/* Off */
	flags &= ~CCR_CACHE_ENABLE;
#पूर्ण_अगर

	l2_cache_init();

	__raw_ग_लिखोl(flags, SH_CCR);
	back_to_cached();
पूर्ण
#अन्यथा
#घोषणा cache_init()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा CSHAPE(totalsize, linesize, assoc) \
	((totalsize & ~0xff) | (linesize << 4) | assoc)

#घोषणा CACHE_DESC_SHAPE(desc)	\
	CSHAPE((desc).way_size * (desc).ways, ilog2((desc).linesz), (desc).ways)

अटल व्योम detect_cache_shape(व्योम)
अणु
	l1d_cache_shape = CACHE_DESC_SHAPE(current_cpu_data.dcache);

	अगर (current_cpu_data.dcache.flags & SH_CACHE_COMBINED)
		l1i_cache_shape = l1d_cache_shape;
	अन्यथा
		l1i_cache_shape = CACHE_DESC_SHAPE(current_cpu_data.icache);

	अगर (current_cpu_data.flags & CPU_HAS_L2_CACHE)
		l2_cache_shape = CACHE_DESC_SHAPE(current_cpu_data.scache);
	अन्यथा
		l2_cache_shape = -1; /* No S-cache */
पूर्ण

अटल व्योम fpu_init(व्योम)
अणु
	/* Disable the FPU */
	अगर (fpu_disabled && (current_cpu_data.flags & CPU_HAS_FPU)) अणु
		prपूर्णांकk("FPU Disabled\n");
		current_cpu_data.flags &= ~CPU_HAS_FPU;
	पूर्ण

	disable_fpu();
	clear_used_math();
पूर्ण

#अगर_घोषित CONFIG_SH_DSP
अटल व्योम release_dsp(व्योम)
अणु
	अचिन्हित दीर्घ sr;

	/* Clear SR.DSP bit */
	__यंत्र__ __अस्थिर__ (
		"stc\tsr, %0\n\t"
		"and\t%1, %0\n\t"
		"ldc\t%0, sr\n\t"
		: "=&r" (sr)
		: "r" (~SR_DSP)
	);
पूर्ण

अटल व्योम dsp_init(व्योम)
अणु
	अचिन्हित दीर्घ sr;

	/*
	 * Set the SR.DSP bit, रुको क्रम one inकाष्ठाion, and then पढ़ो
	 * back the SR value.
	 */
	__यंत्र__ __अस्थिर__ (
		"stc\tsr, %0\n\t"
		"or\t%1, %0\n\t"
		"ldc\t%0, sr\n\t"
		"nop\n\t"
		"stc\tsr, %0\n\t"
		: "=&r" (sr)
		: "r" (SR_DSP)
	);

	/* If the DSP bit is still set, this CPU has a DSP */
	अगर (sr & SR_DSP)
		current_cpu_data.flags |= CPU_HAS_DSP;

	/* Disable the DSP */
	अगर (dsp_disabled && (current_cpu_data.flags & CPU_HAS_DSP)) अणु
		prपूर्णांकk("DSP Disabled\n");
		current_cpu_data.flags &= ~CPU_HAS_DSP;
	पूर्ण

	/* Now that we've determined the DSP status, clear the DSP bit. */
	release_dsp();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dsp_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SH_DSP */

/**
 * cpu_init
 *
 * This is our initial entry poपूर्णांक क्रम each CPU, and is invoked on the
 * boot CPU prior to calling start_kernel(). For SMP, a combination of
 * this and start_secondary() will bring up each processor to a पढ़ोy
 * state prior to hand विभाजनing the idle loop.
 *
 * We करो all of the basic processor init here, including setting up
 * the caches, FPU, DSP, etc. By the समय start_kernel() is hit (and
 * subsequently platक्रमm_setup()) things like determining the CPU
 * subtype and initial configuration will all be करोne.
 *
 * Each processor family is still responsible क्रम करोing its own probing
 * and cache configuration in cpu_probe().
 */
यंत्रlinkage व्योम cpu_init(व्योम)
अणु
	current_thपढ़ो_info()->cpu = hard_smp_processor_id();

	/* First, probe the CPU */
	cpu_probe();

	अगर (current_cpu_data.type == CPU_SH_NONE)
		panic("Unknown CPU");

	/* First setup the rest of the I-cache info */
	current_cpu_data.icache.entry_mask = current_cpu_data.icache.way_incr -
				      current_cpu_data.icache.linesz;

	current_cpu_data.icache.way_size = current_cpu_data.icache.sets *
				    current_cpu_data.icache.linesz;

	/* And the D-cache too */
	current_cpu_data.dcache.entry_mask = current_cpu_data.dcache.way_incr -
				      current_cpu_data.dcache.linesz;

	current_cpu_data.dcache.way_size = current_cpu_data.dcache.sets *
				    current_cpu_data.dcache.linesz;

	/* Init the cache */
	cache_init();

	अगर (raw_smp_processor_id() == 0) अणु
#अगर_घोषित CONFIG_MMU
		shm_align_mask = max_t(अचिन्हित दीर्घ,
				       current_cpu_data.dcache.way_size - 1,
				       PAGE_SIZE - 1);
#अन्यथा
		shm_align_mask = PAGE_SIZE - 1;
#पूर्ण_अगर

		/* Boot CPU sets the cache shape */
		detect_cache_shape();
	पूर्ण

	fpu_init();
	dsp_init();

	/*
	 * Initialize the per-CPU ASID cache very early, since the
	 * TLB flushing routines depend on this being setup.
	 */
	current_cpu_data.asid_cache = NO_CONTEXT;

	current_cpu_data.phys_bits = __in_29bit_mode() ? 29 : 32;

	speculative_execution_init();
	expmask_init();

	/* Do the rest of the boot processor setup */
	अगर (raw_smp_processor_id() == 0) अणु
		/* Save off the BIOS VBR, अगर there is one */
		sh_bios_vbr_init();

		/*
		 * Setup VBR क्रम boot CPU. Secondary CPUs करो this through
		 * start_secondary().
		 */
		per_cpu_trap_init();

		/*
		 * Boot processor to setup the FP and extended state
		 * context info.
		 */
		init_thपढ़ो_xstate();
	पूर्ण
पूर्ण
