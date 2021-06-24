<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश "bitops.h"

#समावेश <यंत्र/processor-flags.h>
#समावेश <यंत्र/required-features.h>
#समावेश <यंत्र/msr-index.h>
#समावेश "cpuflags.h"

काष्ठा cpu_features cpu;
u32 cpu_venकरोr[3];

अटल bool loaded_flags;

अटल पूर्णांक has_fpu(व्योम)
अणु
	u16 fcw = -1, fsw = -1;
	अचिन्हित दीर्घ cr0;

	यंत्र अस्थिर("mov %%cr0,%0" : "=r" (cr0));
	अगर (cr0 & (X86_CR0_EM|X86_CR0_TS)) अणु
		cr0 &= ~(X86_CR0_EM|X86_CR0_TS);
		यंत्र अस्थिर("mov %0,%%cr0" : : "r" (cr0));
	पूर्ण

	यंत्र अस्थिर("fninit ; fnstsw %0 ; fnstcw %1"
		     : "+m" (fsw), "+m" (fcw));

	वापस fsw == 0 && (fcw & 0x103f) == 0x003f;
पूर्ण

/*
 * For building the 16-bit code we want to explicitly specअगरy 32-bit
 * push/pop operations, rather than just saying 'pushf' or 'popf' and
 * letting the compiler choose. But this is also included from the
 * compressed/ directory where it may be 64-bit code, and thus needs
 * to be 'pushfq' or 'popfq' in that हाल.
 */
#अगर_घोषित __x86_64__
#घोषणा PUSHF "pushfq"
#घोषणा POPF "popfq"
#अन्यथा
#घोषणा PUSHF "pushfl"
#घोषणा POPF "popfl"
#पूर्ण_अगर

पूर्णांक has_eflag(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ f0, f1;

	यंत्र अस्थिर(PUSHF "	\n\t"
		     PUSHF "	\n\t"
		     "pop %0	\n\t"
		     "mov %0,%1	\n\t"
		     "xor %2,%1	\n\t"
		     "push %1	\n\t"
		     POPF "	\n\t"
		     PUSHF "	\n\t"
		     "pop %1	\n\t"
		     POPF
		     : "=&r" (f0), "=&r" (f1)
		     : "ri" (mask));

	वापस !!((f0^f1) & mask);
पूर्ण

/* Handle x86_32 PIC using ebx. */
#अगर defined(__i386__) && defined(__PIC__)
# define EBX_REG "=r"
#अन्यथा
# define EBX_REG "=b"
#पूर्ण_अगर

अटल अंतरभूत व्योम cpuid_count(u32 id, u32 count,
		u32 *a, u32 *b, u32 *c, u32 *d)
अणु
	यंत्र अस्थिर(".ifnc %%ebx,%3 ; movl  %%ebx,%3 ; .endif	\n\t"
		     "cpuid					\n\t"
		     ".ifnc %%ebx,%3 ; xchgl %%ebx,%3 ; .endif	\n\t"
		    : "=a" (*a), "=c" (*c), "=d" (*d), EBX_REG (*b)
		    : "a" (id), "c" (count)
	);
पूर्ण

#घोषणा cpuid(id, a, b, c, d) cpuid_count(id, 0, a, b, c, d)

व्योम get_cpuflags(व्योम)
अणु
	u32 max_पूर्णांकel_level, max_amd_level;
	u32 tfms;
	u32 ignored;

	अगर (loaded_flags)
		वापस;
	loaded_flags = true;

	अगर (has_fpu())
		set_bit(X86_FEATURE_FPU, cpu.flags);

	अगर (has_eflag(X86_EFLAGS_ID)) अणु
		cpuid(0x0, &max_पूर्णांकel_level, &cpu_venकरोr[0], &cpu_venकरोr[2],
		      &cpu_venकरोr[1]);

		अगर (max_पूर्णांकel_level >= 0x00000001 &&
		    max_पूर्णांकel_level <= 0x0000ffff) अणु
			cpuid(0x1, &tfms, &ignored, &cpu.flags[4],
			      &cpu.flags[0]);
			cpu.level = (tfms >> 8) & 15;
			cpu.family = cpu.level;
			cpu.model = (tfms >> 4) & 15;
			अगर (cpu.level >= 6)
				cpu.model += ((tfms >> 16) & 0xf) << 4;
		पूर्ण

		अगर (max_पूर्णांकel_level >= 0x00000007) अणु
			cpuid_count(0x00000007, 0, &ignored, &ignored,
					&cpu.flags[16], &ignored);
		पूर्ण

		cpuid(0x80000000, &max_amd_level, &ignored, &ignored,
		      &ignored);

		अगर (max_amd_level >= 0x80000001 &&
		    max_amd_level <= 0x8000ffff) अणु
			cpuid(0x80000001, &ignored, &ignored, &cpu.flags[6],
			      &cpu.flags[1]);
		पूर्ण
	पूर्ण
पूर्ण
