<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MSR_H
#घोषणा _ASM_X86_MSR_H

#समावेश "msr-index.h"

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/cpumask.h>
#समावेश <uapi/यंत्र/msr.h>

काष्ठा msr अणु
	जोड़ अणु
		काष्ठा अणु
			u32 l;
			u32 h;
		पूर्ण;
		u64 q;
	पूर्ण;
पूर्ण;

काष्ठा msr_info अणु
	u32 msr_no;
	काष्ठा msr reg;
	काष्ठा msr *msrs;
	पूर्णांक err;
पूर्ण;

काष्ठा msr_regs_info अणु
	u32 *regs;
	पूर्णांक err;
पूर्ण;

काष्ठा saved_msr अणु
	bool valid;
	काष्ठा msr_info info;
पूर्ण;

काष्ठा saved_msrs अणु
	अचिन्हित पूर्णांक num;
	काष्ठा saved_msr *array;
पूर्ण;

/*
 * both i386 and x86_64 वापसs 64-bit value in edx:eax, but gcc's "A"
 * स्थिरraपूर्णांक has dअगरferent meanings. For i386, "A" means exactly
 * edx:eax, जबतक क्रम x86_64 it करोesn't mean rdx:rax or edx:eax. Instead,
 * it means rax *or* rdx.
 */
#अगर_घोषित CONFIG_X86_64
/* Using 64-bit values saves one inकाष्ठाion clearing the high half of low */
#घोषणा DECLARE_ARGS(val, low, high)	अचिन्हित दीर्घ low, high
#घोषणा EAX_EDX_VAL(val, low, high)	((low) | (high) << 32)
#घोषणा EAX_EDX_RET(val, low, high)	"=a" (low), "=d" (high)
#अन्यथा
#घोषणा DECLARE_ARGS(val, low, high)	अचिन्हित दीर्घ दीर्घ val
#घोषणा EAX_EDX_VAL(val, low, high)	(val)
#घोषणा EAX_EDX_RET(val, low, high)	"=A" (val)
#पूर्ण_अगर

/*
 * Be very careful with includes. This header is prone to include loops.
 */
#समावेश <यंत्र/atomic.h>
#समावेश <linux/tracepoपूर्णांक-defs.h>

#अगर_घोषित CONFIG_TRACEPOINTS
DECLARE_TRACEPOINT(पढ़ो_msr);
DECLARE_TRACEPOINT(ग_लिखो_msr);
DECLARE_TRACEPOINT(rdpmc);
बाह्य व्योम करो_trace_ग_लिखो_msr(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed);
बाह्य व्योम करो_trace_पढ़ो_msr(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed);
बाह्य व्योम करो_trace_rdpmc(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed);
#अन्यथा
अटल अंतरभूत व्योम करो_trace_ग_लिखो_msr(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed) अणुपूर्ण
अटल अंतरभूत व्योम करो_trace_पढ़ो_msr(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed) अणुपूर्ण
अटल अंतरभूत व्योम करो_trace_rdpmc(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed) अणुपूर्ण
#पूर्ण_अगर

/*
 * __rdmsr() and __wrmsr() are the two primitives which are the bare minimum MSR
 * accessors and should not have any tracing or other functionality piggybacking
 * on them - those are *purely* क्रम accessing MSRs and nothing more. So करोn't even
 * think of extending them - you will be slapped with a stinking trout or a frozen
 * shark will reach you, wherever you are! You've been warned.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ दीर्घ __rdmsr(अचिन्हित पूर्णांक msr)
अणु
	DECLARE_ARGS(val, low, high);

	यंत्र अस्थिर("1: rdmsr\n"
		     "2:\n"
		     _ASM_EXTABLE_HANDLE(1b, 2b, ex_handler_rdmsr_unsafe)
		     : EAX_EDX_RET(val, low, high) : "c" (msr));

	वापस EAX_EDX_VAL(val, low, high);
पूर्ण

अटल __always_अंतरभूत व्योम __wrmsr(अचिन्हित पूर्णांक msr, u32 low, u32 high)
अणु
	यंत्र अस्थिर("1: wrmsr\n"
		     "2:\n"
		     _ASM_EXTABLE_HANDLE(1b, 2b, ex_handler_wrmsr_unsafe)
		     : : "c" (msr), "a"(low), "d" (high) : "memory");
पूर्ण

#घोषणा native_rdmsr(msr, val1, val2)			\
करो अणु							\
	u64 __val = __rdmsr((msr));			\
	(व्योम)((val1) = (u32)__val);			\
	(व्योम)((val2) = (u32)(__val >> 32));		\
पूर्ण जबतक (0)

#घोषणा native_wrmsr(msr, low, high)			\
	__wrmsr(msr, low, high)

#घोषणा native_wrmsrl(msr, val)				\
	__wrmsr((msr), (u32)((u64)(val)),		\
		       (u32)((u64)(val) >> 32))

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ native_पढ़ो_msr(अचिन्हित पूर्णांक msr)
अणु
	अचिन्हित दीर्घ दीर्घ val;

	val = __rdmsr(msr);

	अगर (tracepoपूर्णांक_enabled(पढ़ो_msr))
		करो_trace_पढ़ो_msr(msr, val, 0);

	वापस val;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ native_पढ़ो_msr_safe(अचिन्हित पूर्णांक msr,
						      पूर्णांक *err)
अणु
	DECLARE_ARGS(val, low, high);

	यंत्र अस्थिर("2: rdmsr ; xor %[err],%[err]\n"
		     "1:\n\t"
		     ".section .fixup,\"ax\"\n\t"
		     "3: mov %[fault],%[err]\n\t"
		     "xorl %%eax, %%eax\n\t"
		     "xorl %%edx, %%edx\n\t"
		     "jmp 1b\n\t"
		     ".previous\n\t"
		     _ASM_EXTABLE(2b, 3b)
		     : [err] "=r" (*err), EAX_EDX_RET(val, low, high)
		     : "c" (msr), [fault] "i" (-EIO));
	अगर (tracepoपूर्णांक_enabled(पढ़ो_msr))
		करो_trace_पढ़ो_msr(msr, EAX_EDX_VAL(val, low, high), *err);
	वापस EAX_EDX_VAL(val, low, high);
पूर्ण

/* Can be unअंतरभूतd because referenced by paravirt */
अटल अंतरभूत व्योम notrace
native_ग_लिखो_msr(अचिन्हित पूर्णांक msr, u32 low, u32 high)
अणु
	__wrmsr(msr, low, high);

	अगर (tracepoपूर्णांक_enabled(ग_लिखो_msr))
		करो_trace_ग_लिखो_msr(msr, ((u64)high << 32 | low), 0);
पूर्ण

/* Can be unअंतरभूतd because referenced by paravirt */
अटल अंतरभूत पूर्णांक notrace
native_ग_लिखो_msr_safe(अचिन्हित पूर्णांक msr, u32 low, u32 high)
अणु
	पूर्णांक err;

	यंत्र अस्थिर("2: wrmsr ; xor %[err],%[err]\n"
		     "1:\n\t"
		     ".section .fixup,\"ax\"\n\t"
		     "3:  mov %[fault],%[err] ; jmp 1b\n\t"
		     ".previous\n\t"
		     _ASM_EXTABLE(2b, 3b)
		     : [err] "=a" (err)
		     : "c" (msr), "0" (low), "d" (high),
		       [fault] "i" (-EIO)
		     : "memory");
	अगर (tracepoपूर्णांक_enabled(ग_लिखो_msr))
		करो_trace_ग_लिखो_msr(msr, ((u64)high << 32 | low), err);
	वापस err;
पूर्ण

बाह्य पूर्णांक rdmsr_safe_regs(u32 regs[8]);
बाह्य पूर्णांक wrmsr_safe_regs(u32 regs[8]);

/**
 * rdtsc() - वापसs the current TSC without ordering स्थिरraपूर्णांकs
 *
 * rdtsc() वापसs the result of RDTSC as a 64-bit पूर्णांकeger.  The
 * only ordering स्थिरraपूर्णांक it supplies is the ordering implied by
 * "asm volatile": it will put the RDTSC in the place you expect.  The
 * CPU can and will speculatively execute that RDTSC, though, so the
 * results can be non-monotonic अगर compared on dअगरferent CPUs.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ दीर्घ rdtsc(व्योम)
अणु
	DECLARE_ARGS(val, low, high);

	यंत्र अस्थिर("rdtsc" : EAX_EDX_RET(val, low, high));

	वापस EAX_EDX_VAL(val, low, high);
पूर्ण

/**
 * rdtsc_ordered() - पढ़ो the current TSC in program order
 *
 * rdtsc_ordered() वापसs the result of RDTSC as a 64-bit पूर्णांकeger.
 * It is ordered like a load to a global in-memory counter.  It should
 * be impossible to observe non-monotonic rdtsc_unordered() behavior
 * across multiple CPUs as दीर्घ as the TSC is synced.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ दीर्घ rdtsc_ordered(व्योम)
अणु
	DECLARE_ARGS(val, low, high);

	/*
	 * The RDTSC inकाष्ठाion is not ordered relative to memory
	 * access.  The Intel SDM and the AMD APM are both vague on this
	 * poपूर्णांक, but empirically an RDTSC inकाष्ठाion can be
	 * speculatively executed beक्रमe prior loads.  An RDTSC
	 * immediately after an appropriate barrier appears to be
	 * ordered as a normal load, that is, it provides the same
	 * ordering guarantees as पढ़ोing from a global memory location
	 * that some other imaginary CPU is updating continuously with a
	 * समय stamp.
	 *
	 * Thus, use the preferred barrier on the respective CPU, aiming क्रम
	 * RDTSCP as the शेष.
	 */
	यंत्र अस्थिर(ALTERNATIVE_2("rdtsc",
				   "lfence; rdtsc", X86_FEATURE_LFENCE_RDTSC,
				   "rdtscp", X86_FEATURE_RDTSCP)
			: EAX_EDX_RET(val, low, high)
			/* RDTSCP clobbers ECX with MSR_TSC_AUX. */
			:: "ecx");

	वापस EAX_EDX_VAL(val, low, high);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ native_पढ़ो_pmc(पूर्णांक counter)
अणु
	DECLARE_ARGS(val, low, high);

	यंत्र अस्थिर("rdpmc" : EAX_EDX_RET(val, low, high) : "c" (counter));
	अगर (tracepoपूर्णांक_enabled(rdpmc))
		करो_trace_rdpmc(counter, EAX_EDX_VAL(val, low, high), 0);
	वापस EAX_EDX_VAL(val, low, high);
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा
#समावेश <linux/त्रुटिसं.स>
/*
 * Access to machine-specअगरic रेजिस्टरs (available on 586 and better only)
 * Note: the rd* operations modअगरy the parameters directly (without using
 * poपूर्णांकer indirection), this allows gcc to optimize better
 */

#घोषणा rdmsr(msr, low, high)					\
करो अणु								\
	u64 __val = native_पढ़ो_msr((msr));			\
	(व्योम)((low) = (u32)__val);				\
	(व्योम)((high) = (u32)(__val >> 32));			\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम wrmsr(अचिन्हित पूर्णांक msr, u32 low, u32 high)
अणु
	native_ग_लिखो_msr(msr, low, high);
पूर्ण

#घोषणा rdmsrl(msr, val)			\
	((val) = native_पढ़ो_msr((msr)))

अटल अंतरभूत व्योम wrmsrl(अचिन्हित पूर्णांक msr, u64 val)
अणु
	native_ग_लिखो_msr(msr, (u32)(val & 0xffffffffULL), (u32)(val >> 32));
पूर्ण

/* wrmsr with exception handling */
अटल अंतरभूत पूर्णांक wrmsr_safe(अचिन्हित पूर्णांक msr, u32 low, u32 high)
अणु
	वापस native_ग_लिखो_msr_safe(msr, low, high);
पूर्ण

/* rdmsr with exception handling */
#घोषणा rdmsr_safe(msr, low, high)				\
(अणु								\
	पूर्णांक __err;						\
	u64 __val = native_पढ़ो_msr_safe((msr), &__err);	\
	(*low) = (u32)__val;					\
	(*high) = (u32)(__val >> 32);				\
	__err;							\
पूर्ण)

अटल अंतरभूत पूर्णांक rdmsrl_safe(अचिन्हित पूर्णांक msr, अचिन्हित दीर्घ दीर्घ *p)
अणु
	पूर्णांक err;

	*p = native_पढ़ो_msr_safe(msr, &err);
	वापस err;
पूर्ण

#घोषणा rdpmc(counter, low, high)			\
करो अणु							\
	u64 _l = native_पढ़ो_pmc((counter));		\
	(low)  = (u32)_l;				\
	(high) = (u32)(_l >> 32);			\
पूर्ण जबतक (0)

#घोषणा rdpmcl(counter, val) ((val) = native_पढ़ो_pmc(counter))

#पूर्ण_अगर	/* !CONFIG_PARAVIRT_XXL */

/*
 * 64-bit version of wrmsr_safe():
 */
अटल अंतरभूत पूर्णांक wrmsrl_safe(u32 msr, u64 val)
अणु
	वापस wrmsr_safe(msr, (u32)val,  (u32)(val >> 32));
पूर्ण

काष्ठा msr *msrs_alloc(व्योम);
व्योम msrs_मुक्त(काष्ठा msr *msrs);
पूर्णांक msr_set_bit(u32 msr, u8 bit);
पूर्णांक msr_clear_bit(u32 msr, u8 bit);

#अगर_घोषित CONFIG_SMP
पूर्णांक rdmsr_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 *l, u32 *h);
पूर्णांक wrmsr_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 l, u32 h);
पूर्णांक rdmsrl_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 *q);
पूर्णांक wrmsrl_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 q);
व्योम rdmsr_on_cpus(स्थिर काष्ठा cpumask *mask, u32 msr_no, काष्ठा msr *msrs);
व्योम wrmsr_on_cpus(स्थिर काष्ठा cpumask *mask, u32 msr_no, काष्ठा msr *msrs);
पूर्णांक rdmsr_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 *l, u32 *h);
पूर्णांक wrmsr_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 l, u32 h);
पूर्णांक rdmsrl_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 *q);
पूर्णांक wrmsrl_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 q);
पूर्णांक rdmsr_safe_regs_on_cpu(अचिन्हित पूर्णांक cpu, u32 regs[8]);
पूर्णांक wrmsr_safe_regs_on_cpu(अचिन्हित पूर्णांक cpu, u32 regs[8]);
#अन्यथा  /*  CONFIG_SMP  */
अटल अंतरभूत पूर्णांक rdmsr_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 *l, u32 *h)
अणु
	rdmsr(msr_no, *l, *h);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक wrmsr_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 l, u32 h)
अणु
	wrmsr(msr_no, l, h);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक rdmsrl_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 *q)
अणु
	rdmsrl(msr_no, *q);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक wrmsrl_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 q)
अणु
	wrmsrl(msr_no, q);
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम rdmsr_on_cpus(स्थिर काष्ठा cpumask *m, u32 msr_no,
				काष्ठा msr *msrs)
अणु
	rdmsr_on_cpu(0, msr_no, &(msrs[0].l), &(msrs[0].h));
पूर्ण
अटल अंतरभूत व्योम wrmsr_on_cpus(स्थिर काष्ठा cpumask *m, u32 msr_no,
				काष्ठा msr *msrs)
अणु
	wrmsr_on_cpu(0, msr_no, msrs[0].l, msrs[0].h);
पूर्ण
अटल अंतरभूत पूर्णांक rdmsr_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no,
				    u32 *l, u32 *h)
अणु
	वापस rdmsr_safe(msr_no, l, h);
पूर्ण
अटल अंतरभूत पूर्णांक wrmsr_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u32 l, u32 h)
अणु
	वापस wrmsr_safe(msr_no, l, h);
पूर्ण
अटल अंतरभूत पूर्णांक rdmsrl_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 *q)
अणु
	वापस rdmsrl_safe(msr_no, q);
पूर्ण
अटल अंतरभूत पूर्णांक wrmsrl_safe_on_cpu(अचिन्हित पूर्णांक cpu, u32 msr_no, u64 q)
अणु
	वापस wrmsrl_safe(msr_no, q);
पूर्ण
अटल अंतरभूत पूर्णांक rdmsr_safe_regs_on_cpu(अचिन्हित पूर्णांक cpu, u32 regs[8])
अणु
	वापस rdmsr_safe_regs(regs);
पूर्ण
अटल अंतरभूत पूर्णांक wrmsr_safe_regs_on_cpu(अचिन्हित पूर्णांक cpu, u32 regs[8])
अणु
	वापस wrmsr_safe_regs(regs);
पूर्ण
#पूर्ण_अगर  /* CONFIG_SMP */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_MSR_H */
