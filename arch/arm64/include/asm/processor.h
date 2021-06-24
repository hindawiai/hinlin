<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/processor.h
 *
 * Copyright (C) 1995-1999 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_PROCESSOR_H
#घोषणा __ASM_PROCESSOR_H

/*
 * On arm64 प्रणालीs, unaligned accesses by the CPU are cheap, and so there is
 * no poपूर्णांक in shअगरting all network buffers by 2 bytes just to make some IP
 * header fields appear aligned in memory, potentially sacrअगरicing some DMA
 * perक्रमmance on some platक्रमms.
 */
#घोषणा NET_IP_ALIGN	0

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/build_bug.h>
#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <vdso/processor.h>

#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/lse.h>
#समावेश <यंत्र/pgtable-hwdef.h>
#समावेश <यंत्र/poपूर्णांकer_auth.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/spectre.h>
#समावेश <यंत्र/types.h>

/*
 * TASK_SIZE - the maximum size of a user space task.
 * TASK_UNMAPPED_BASE - the lower boundary of the mmap VM area.
 */

#घोषणा DEFAULT_MAP_WINDOW_64	(UL(1) << VA_BITS_MIN)
#घोषणा TASK_SIZE_64		(UL(1) << vabits_actual)
#घोषणा TASK_SIZE_MAX		(UL(1) << VA_BITS)

#अगर_घोषित CONFIG_COMPAT
#अगर defined(CONFIG_ARM64_64K_PAGES) && defined(CONFIG_KUSER_HELPERS)
/*
 * With CONFIG_ARM64_64K_PAGES enabled, the last page is occupied
 * by the compat vectors page.
 */
#घोषणा TASK_SIZE_32		UL(0x100000000)
#अन्यथा
#घोषणा TASK_SIZE_32		(UL(0x100000000) - PAGE_SIZE)
#पूर्ण_अगर /* CONFIG_ARM64_64K_PAGES */
#घोषणा TASK_SIZE		(test_thपढ़ो_flag(TIF_32BIT) ? \
				TASK_SIZE_32 : TASK_SIZE_64)
#घोषणा TASK_SIZE_OF(tsk)	(test_tsk_thपढ़ो_flag(tsk, TIF_32BIT) ? \
				TASK_SIZE_32 : TASK_SIZE_64)
#घोषणा DEFAULT_MAP_WINDOW	(test_thपढ़ो_flag(TIF_32BIT) ? \
				TASK_SIZE_32 : DEFAULT_MAP_WINDOW_64)
#अन्यथा
#घोषणा TASK_SIZE		TASK_SIZE_64
#घोषणा DEFAULT_MAP_WINDOW	DEFAULT_MAP_WINDOW_64
#पूर्ण_अगर /* CONFIG_COMPAT */

#अगर_घोषित CONFIG_ARM64_FORCE_52BIT
#घोषणा STACK_TOP_MAX		TASK_SIZE_64
#घोषणा TASK_UNMAPPED_BASE	(PAGE_ALIGN(TASK_SIZE / 4))
#अन्यथा
#घोषणा STACK_TOP_MAX		DEFAULT_MAP_WINDOW_64
#घोषणा TASK_UNMAPPED_BASE	(PAGE_ALIGN(DEFAULT_MAP_WINDOW / 4))
#पूर्ण_अगर /* CONFIG_ARM64_FORCE_52BIT */

#अगर_घोषित CONFIG_COMPAT
#घोषणा AARCH32_VECTORS_BASE	0xffff0000
#घोषणा STACK_TOP		(test_thपढ़ो_flag(TIF_32BIT) ? \
				AARCH32_VECTORS_BASE : STACK_TOP_MAX)
#अन्यथा
#घोषणा STACK_TOP		STACK_TOP_MAX
#पूर्ण_अगर /* CONFIG_COMPAT */

#अगर_अघोषित CONFIG_ARM64_FORCE_52BIT
#घोषणा arch_get_mmap_end(addr) ((addr > DEFAULT_MAP_WINDOW) ? TASK_SIZE :\
				DEFAULT_MAP_WINDOW)

#घोषणा arch_get_mmap_base(addr, base) ((addr > DEFAULT_MAP_WINDOW) ? \
					base + TASK_SIZE - DEFAULT_MAP_WINDOW :\
					base)
#पूर्ण_अगर /* CONFIG_ARM64_FORCE_52BIT */

बाह्य phys_addr_t arm64_dma_phys_limit;
#घोषणा ARCH_LOW_ADDRESS_LIMIT	(arm64_dma_phys_limit - 1)

काष्ठा debug_info अणु
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	/* Have we suspended stepping by a debugger? */
	पूर्णांक			suspended_step;
	/* Allow अवरोधpoपूर्णांकs and watchpoपूर्णांकs to be disabled क्रम this thपढ़ो. */
	पूर्णांक			bps_disabled;
	पूर्णांक			wps_disabled;
	/* Hardware अवरोधpoपूर्णांकs pinned to this task. */
	काष्ठा perf_event	*hbp_अवरोध[ARM_MAX_BRP];
	काष्ठा perf_event	*hbp_watch[ARM_MAX_WRP];
#पूर्ण_अगर
पूर्ण;

काष्ठा cpu_context अणु
	अचिन्हित दीर्घ x19;
	अचिन्हित दीर्घ x20;
	अचिन्हित दीर्घ x21;
	अचिन्हित दीर्घ x22;
	अचिन्हित दीर्घ x23;
	अचिन्हित दीर्घ x24;
	अचिन्हित दीर्घ x25;
	अचिन्हित दीर्घ x26;
	अचिन्हित दीर्घ x27;
	अचिन्हित दीर्घ x28;
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ sp;
	अचिन्हित दीर्घ pc;
पूर्ण;

काष्ठा thपढ़ो_काष्ठा अणु
	काष्ठा cpu_context	cpu_context;	/* cpu context */

	/*
	 * Whitelisted fields क्रम hardened usercopy:
	 * Maपूर्णांकainers must ensure manually that this contains no
	 * implicit padding.
	 */
	काष्ठा अणु
		अचिन्हित दीर्घ	tp_value;	/* TLS रेजिस्टर */
		अचिन्हित दीर्घ	tp2_value;
		काष्ठा user_fpsimd_state fpsimd_state;
	पूर्ण uw;

	अचिन्हित पूर्णांक		fpsimd_cpu;
	व्योम			*sve_state;	/* SVE रेजिस्टरs, अगर any */
	अचिन्हित पूर्णांक		sve_vl;		/* SVE vector length */
	अचिन्हित पूर्णांक		sve_vl_onexec;	/* SVE vl after next exec */
	अचिन्हित दीर्घ		fault_address;	/* fault info */
	अचिन्हित दीर्घ		fault_code;	/* ESR_EL1 value */
	काष्ठा debug_info	debug;		/* debugging */
#अगर_घोषित CONFIG_ARM64_PTR_AUTH
	काष्ठा ptrauth_keys_user	keys_user;
	काष्ठा ptrauth_keys_kernel	keys_kernel;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ARM64_MTE
	u64			gcr_user_excl;
#पूर्ण_अगर
	u64			sctlr_user;
पूर्ण;

#घोषणा SCTLR_USER_MASK                                                        \
	(SCTLR_ELx_ENIA | SCTLR_ELx_ENIB | SCTLR_ELx_ENDA | SCTLR_ELx_ENDB |   \
	 SCTLR_EL1_TCF0_MASK)

अटल अंतरभूत व्योम arch_thपढ़ो_काष्ठा_whitelist(अचिन्हित दीर्घ *offset,
						अचिन्हित दीर्घ *size)
अणु
	/* Verअगरy that there is no padding among the whitelisted fields: */
	BUILD_BUG_ON(माप_field(काष्ठा thपढ़ो_काष्ठा, uw) !=
		     माप_field(काष्ठा thपढ़ो_काष्ठा, uw.tp_value) +
		     माप_field(काष्ठा thपढ़ो_काष्ठा, uw.tp2_value) +
		     माप_field(काष्ठा thपढ़ो_काष्ठा, uw.fpsimd_state));

	*offset = दुरत्व(काष्ठा thपढ़ो_काष्ठा, uw);
	*size = माप_field(काष्ठा thपढ़ो_काष्ठा, uw);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#घोषणा task_user_tls(t)						\
(अणु									\
	अचिन्हित दीर्घ *__tls;						\
	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(t)))			\
		__tls = &(t)->thपढ़ो.uw.tp2_value;			\
	अन्यथा								\
		__tls = &(t)->thपढ़ो.uw.tp_value;			\
	__tls;								\
 पूर्ण)
#अन्यथा
#घोषणा task_user_tls(t)	(&(t)->thपढ़ो.uw.tp_value)
#पूर्ण_अगर

/* Sync TPIDR_EL0 back to thपढ़ो_काष्ठा क्रम current */
व्योम tls_preserve_current_state(व्योम);

#घोषणा INIT_THREAD अणु				\
	.fpsimd_cpu = NR_CPUS,			\
पूर्ण

अटल अंतरभूत व्योम start_thपढ़ो_common(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc)
अणु
	स_रखो(regs, 0, माप(*regs));
	क्रमget_syscall(regs);
	regs->pc = pc;

	अगर (प्रणाली_uses_irq_prio_masking())
		regs->pmr_save = GIC_PRIO_IRQON;
पूर्ण

अटल अंतरभूत व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
				अचिन्हित दीर्घ sp)
अणु
	start_thपढ़ो_common(regs, pc);
	regs->pstate = PSR_MODE_EL0t;
	spectre_v4_enable_task_mitigation(current);
	regs->sp = sp;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल अंतरभूत व्योम compat_start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc,
				       अचिन्हित दीर्घ sp)
अणु
	start_thपढ़ो_common(regs, pc);
	regs->pstate = PSR_AA32_MODE_USR;
	अगर (pc & 1)
		regs->pstate |= PSR_AA32_T_BIT;

#अगर_घोषित __AARCH64EB__
	regs->pstate |= PSR_AA32_E_BIT;
#पूर्ण_अगर

	spectre_v4_enable_task_mitigation(current);
	regs->compat_sp = sp;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool is_ttbr0_addr(अचिन्हित दीर्घ addr)
अणु
	/* entry assembly clears tags क्रम TTBR0 addrs */
	वापस addr < TASK_SIZE;
पूर्ण

अटल अंतरभूत bool is_ttbr1_addr(अचिन्हित दीर्घ addr)
अणु
	/* TTBR1 addresses may have a tag अगर KASAN_SW_TAGS is in use */
	वापस arch_kasan_reset_tag(addr) >= PAGE_OFFSET;
पूर्ण

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
बाह्य व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

व्योम set_task_sctlr_el1(u64 sctlr);

/* Thपढ़ो चयनing */
बाह्य काष्ठा task_काष्ठा *cpu_चयन_to(काष्ठा task_काष्ठा *prev,
					 काष्ठा task_काष्ठा *next);

यंत्रlinkage व्योम arm64_preempt_schedule_irq(व्योम);

#घोषणा task_pt_regs(p) \
	((काष्ठा pt_regs *)(THREAD_SIZE + task_stack_page(p)) - 1)

#घोषणा KSTK_EIP(tsk)	((अचिन्हित दीर्घ)task_pt_regs(tsk)->pc)
#घोषणा KSTK_ESP(tsk)	user_stack_poपूर्णांकer(task_pt_regs(tsk))

/*
 * Prefetching support
 */
#घोषणा ARCH_HAS_PREFETCH
अटल अंतरभूत व्योम prefetch(स्थिर व्योम *ptr)
अणु
	यंत्र अस्थिर("prfm pldl1keep, %a0\n" : : "p" (ptr));
पूर्ण

#घोषणा ARCH_HAS_PREFETCHW
अटल अंतरभूत व्योम prefetchw(स्थिर व्योम *ptr)
अणु
	यंत्र अस्थिर("prfm pstl1keep, %a0\n" : : "p" (ptr));
पूर्ण

#घोषणा ARCH_HAS_SPINLOCK_PREFETCH
अटल अंतरभूत व्योम spin_lock_prefetch(स्थिर व्योम *ptr)
अणु
	यंत्र अस्थिर(ARM64_LSE_ATOMIC_INSN(
		     "prfm pstl1strm, %a0",
		     "nop") : : "p" (ptr));
पूर्ण

बाह्य अचिन्हित दीर्घ __ro_after_init संकेत_minsigstksz; /* sigframe size */
बाह्य व्योम __init minsigstksz_setup(व्योम);

/*
 * Not at the top of the file due to a direct #समावेश cycle between
 * <यंत्र/fpsimd.h> and <यंत्र/processor.h>.  Deferring this #समावेश
 * ensures that contents of processor.h are visible to fpsimd.h even अगर
 * processor.h is included first.
 *
 * These prctl helpers are the only things in this file that require
 * fpsimd.h.  The core code expects them to be in this header.
 */
#समावेश <यंत्र/fpsimd.h>

/* Userspace पूर्णांकerface क्रम PR_SVE_अणुSET,GETपूर्ण_VL prctl()s: */
#घोषणा SVE_SET_VL(arg)	sve_set_current_vl(arg)
#घोषणा SVE_GET_VL()	sve_get_current_vl()

/* PR_PAC_RESET_KEYS prctl */
#घोषणा PAC_RESET_KEYS(tsk, arg)	ptrauth_prctl_reset_keys(tsk, arg)

/* PR_PAC_अणुSET,GETपूर्ण_ENABLED_KEYS prctl */
#घोषणा PAC_SET_ENABLED_KEYS(tsk, keys, enabled)				\
	ptrauth_set_enabled_keys(tsk, keys, enabled)
#घोषणा PAC_GET_ENABLED_KEYS(tsk) ptrauth_get_enabled_keys(tsk)

#अगर_घोषित CONFIG_ARM64_TAGGED_ADDR_ABI
/* PR_अणुSET,GETपूर्ण_TAGGED_ADDR_CTRL prctl */
दीर्घ set_tagged_addr_ctrl(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ arg);
दीर्घ get_tagged_addr_ctrl(काष्ठा task_काष्ठा *task);
#घोषणा SET_TAGGED_ADDR_CTRL(arg)	set_tagged_addr_ctrl(current, arg)
#घोषणा GET_TAGGED_ADDR_CTRL()		get_tagged_addr_ctrl(current)
#पूर्ण_अगर

/*
 * For CONFIG_GCC_PLUGIN_STACKLEAK
 *
 * These need to be macros because otherwise we get stuck in a nighपंचांगare
 * of header definitions क्रम the use of task_stack_page.
 */

#घोषणा current_top_of_stack()							\
(अणु										\
	काष्ठा stack_info _info;						\
	BUG_ON(!on_accessible_stack(current, current_stack_poपूर्णांकer, &_info));	\
	_info.high;								\
पूर्ण)
#घोषणा on_thपढ़ो_stack()	(on_task_stack(current, current_stack_poपूर्णांकer, शून्य))

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_PROCESSOR_H */
