<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SPECIAL_INSNS_H
#घोषणा _ASM_X86_SPECIAL_INSNS_H


#अगर_घोषित __KERNEL__

#समावेश <यंत्र/nops.h>
#समावेश <यंत्र/processor-flags.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/jump_label.h>

/*
 * The compiler should not reorder अस्थिर यंत्र statements with respect to each
 * other: they should execute in program order. However GCC 4.9.x and 5.x have
 * a bug (which was fixed in 8.1, 7.3 and 6.5) where they might reorder
 * अस्थिर यंत्र. The ग_लिखो functions are not affected since they have memory
 * clobbers preventing reordering. To prevent पढ़ोs from being reordered with
 * respect to ग_लिखोs, use a dummy memory opeअक्रम.
 */

#घोषणा __FORCE_ORDER "m"(*(अचिन्हित पूर्णांक *)0x1000UL)

व्योम native_ग_लिखो_cr0(अचिन्हित दीर्घ val);

अटल अंतरभूत अचिन्हित दीर्घ native_पढ़ो_cr0(व्योम)
अणु
	अचिन्हित दीर्घ val;
	यंत्र अस्थिर("mov %%cr0,%0\n\t" : "=r" (val) : __FORCE_ORDER);
	वापस val;
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ native_पढ़ो_cr2(व्योम)
अणु
	अचिन्हित दीर्घ val;
	यंत्र अस्थिर("mov %%cr2,%0\n\t" : "=r" (val) : __FORCE_ORDER);
	वापस val;
पूर्ण

अटल __always_अंतरभूत व्योम native_ग_लिखो_cr2(अचिन्हित दीर्घ val)
अणु
	यंत्र अस्थिर("mov %0,%%cr2": : "r" (val) : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __native_पढ़ो_cr3(व्योम)
अणु
	अचिन्हित दीर्घ val;
	यंत्र अस्थिर("mov %%cr3,%0\n\t" : "=r" (val) : __FORCE_ORDER);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम native_ग_लिखो_cr3(अचिन्हित दीर्घ val)
अणु
	यंत्र अस्थिर("mov %0,%%cr3": : "r" (val) : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ native_पढ़ो_cr4(व्योम)
अणु
	अचिन्हित दीर्घ val;
#अगर_घोषित CONFIG_X86_32
	/*
	 * This could fault अगर CR4 करोes not exist.  Non-existent CR4
	 * is functionally equivalent to CR4 == 0.  Keep it simple and pretend
	 * that CR4 == 0 on CPUs that करोn't have CR4.
	 */
	यंत्र अस्थिर("1: mov %%cr4, %0\n"
		     "2:\n"
		     _ASM_EXTABLE(1b, 2b)
		     : "=r" (val) : "0" (0), __FORCE_ORDER);
#अन्यथा
	/* CR4 always exists on x86_64. */
	यंत्र अस्थिर("mov %%cr4,%0\n\t" : "=r" (val) : __FORCE_ORDER);
#पूर्ण_अगर
	वापस val;
पूर्ण

व्योम native_ग_लिखो_cr4(अचिन्हित दीर्घ val);

#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
अटल अंतरभूत u32 rdpkru(व्योम)
अणु
	u32 ecx = 0;
	u32 edx, pkru;

	/*
	 * "rdpkru" inकाष्ठाion.  Places PKRU contents in to EAX,
	 * clears EDX and requires that ecx=0.
	 */
	यंत्र अस्थिर(".byte 0x0f,0x01,0xee\n\t"
		     : "=a" (pkru), "=d" (edx)
		     : "c" (ecx));
	वापस pkru;
पूर्ण

अटल अंतरभूत व्योम wrpkru(u32 pkru)
अणु
	u32 ecx = 0, edx = 0;

	/*
	 * "wrpkru" inकाष्ठाion.  Loads contents in EAX to PKRU,
	 * requires that ecx = edx = 0.
	 */
	यंत्र अस्थिर(".byte 0x0f,0x01,0xef\n\t"
		     : : "a" (pkru), "c"(ecx), "d"(edx));
पूर्ण

अटल अंतरभूत व्योम __ग_लिखो_pkru(u32 pkru)
अणु
	/*
	 * WRPKRU is relatively expensive compared to RDPKRU.
	 * Aव्योम WRPKRU when it would not change the value.
	 */
	अगर (pkru == rdpkru())
		वापस;

	wrpkru(pkru);
पूर्ण

#अन्यथा
अटल अंतरभूत u32 rdpkru(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __ग_लिखो_pkru(u32 pkru)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम native_wbinvd(व्योम)
अणु
	यंत्र अस्थिर("wbinvd": : :"memory");
पूर्ण

बाह्य यंत्रlinkage व्योम यंत्र_load_gs_index(अचिन्हित पूर्णांक selector);

अटल अंतरभूत व्योम native_load_gs_index(अचिन्हित पूर्णांक selector)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	यंत्र_load_gs_index(selector);
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __पढ़ो_cr4(व्योम)
अणु
	वापस native_पढ़ो_cr4();
पूर्ण

#अगर_घोषित CONFIG_PARAVIRT_XXL
#समावेश <यंत्र/paravirt.h>
#अन्यथा

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_cr0(व्योम)
अणु
	वापस native_पढ़ो_cr0();
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cr0(अचिन्हित दीर्घ x)
अणु
	native_ग_लिखो_cr0(x);
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ पढ़ो_cr2(व्योम)
अणु
	वापस native_पढ़ो_cr2();
पूर्ण

अटल __always_अंतरभूत व्योम ग_लिखो_cr2(अचिन्हित दीर्घ x)
अणु
	native_ग_लिखो_cr2(x);
पूर्ण

/*
 * Careful!  CR3 contains more than just an address.  You probably want
 * पढ़ो_cr3_pa() instead.
 */
अटल अंतरभूत अचिन्हित दीर्घ __पढ़ो_cr3(व्योम)
अणु
	वापस __native_पढ़ो_cr3();
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_cr3(अचिन्हित दीर्घ x)
अणु
	native_ग_लिखो_cr3(x);
पूर्ण

अटल अंतरभूत व्योम __ग_लिखो_cr4(अचिन्हित दीर्घ x)
अणु
	native_ग_लिखो_cr4(x);
पूर्ण

अटल अंतरभूत व्योम wbinvd(व्योम)
अणु
	native_wbinvd();
पूर्ण

#अगर_घोषित CONFIG_X86_64

अटल अंतरभूत व्योम load_gs_index(अचिन्हित पूर्णांक selector)
अणु
	native_load_gs_index(selector);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PARAVIRT_XXL */

अटल अंतरभूत व्योम clflush(अस्थिर व्योम *__p)
अणु
	यंत्र अस्थिर("clflush %0" : "+m" (*(अस्थिर अक्षर __क्रमce *)__p));
पूर्ण

अटल अंतरभूत व्योम clflushopt(अस्थिर व्योम *__p)
अणु
	alternative_io(".byte 0x3e; clflush %P0",
		       ".byte 0x66; clflush %P0",
		       X86_FEATURE_CLFLUSHOPT,
		       "+m" (*(अस्थिर अक्षर __क्रमce *)__p));
पूर्ण

अटल अंतरभूत व्योम clwb(अस्थिर व्योम *__p)
अणु
	अस्थिर काष्ठा अणु अक्षर x[64]; पूर्ण *p = __p;

	यंत्र अस्थिर(ALTERNATIVE_2(
		".byte 0x3e; clflush (%[pax])",
		".byte 0x66; clflush (%[pax])", /* clflushopt (%%rax) */
		X86_FEATURE_CLFLUSHOPT,
		".byte 0x66, 0x0f, 0xae, 0x30",  /* clwb (%%rax) */
		X86_FEATURE_CLWB)
		: [p] "+m" (*p)
		: [pax] "a" (p));
पूर्ण

#घोषणा nop() यंत्र अस्थिर ("nop")

अटल अंतरभूत व्योम serialize(व्योम)
अणु
	/* Inकाष्ठाion opcode क्रम SERIALIZE; supported in binutils >= 2.35. */
	यंत्र अस्थिर(".byte 0xf, 0x1, 0xe8" ::: "memory");
पूर्ण

/* The dst parameter must be 64-bytes aligned */
अटल अंतरभूत व्योम movdir64b(व्योम __iomem *dst, स्थिर व्योम *src)
अणु
	स्थिर काष्ठा अणु अक्षर _[64]; पूर्ण *__src = src;
	काष्ठा अणु अक्षर _[64]; पूर्ण __iomem *__dst = dst;

	/*
	 * MOVसूची64B %(rdx), rax.
	 *
	 * Both __src and __dst must be memory स्थिरraपूर्णांकs in order to tell the
	 * compiler that no other memory accesses should be reordered around
	 * this one.
	 *
	 * Also, both must be supplied as lvalues because this tells
	 * the compiler what the object is (its size) the inकाष्ठाion accesses.
	 * I.e., not the poपूर्णांकers but what they poपूर्णांक to, thus the deref'ing '*'.
	 */
	यंत्र अस्थिर(".byte 0x66, 0x0f, 0x38, 0xf8, 0x02"
		     : "+m" (*__dst)
		     :  "m" (*__src), "a" (__dst), "d" (__src));
पूर्ण

/**
 * enqcmds - Enqueue a command in supervisor (CPL0) mode
 * @dst: destination, in MMIO space (must be 512-bit aligned)
 * @src: 512 bits memory opeअक्रम
 *
 * The ENQCMDS inकाष्ठाion allows software to ग_लिखो a 512-bit command to
 * a 512-bit-aligned special MMIO region that supports the inकाष्ठाion.
 * A वापस status is loaded पूर्णांकo the ZF flag in the RFLAGS रेजिस्टर.
 * ZF = 0 equates to success, and ZF = 1 indicates retry or error.
 *
 * This function issues the ENQCMDS inकाष्ठाion to submit data from
 * kernel space to MMIO space, in a unit of 512 bits. Order of data access
 * is not guaranteed, nor is a memory barrier perक्रमmed afterwards. It
 * वापसs 0 on success and -EAGAIN on failure.
 *
 * Warning: Do not use this helper unless your driver has checked that the
 * ENQCMDS inकाष्ठाion is supported on the platक्रमm and the device accepts
 * ENQCMDS.
 */
अटल अंतरभूत पूर्णांक enqcmds(व्योम __iomem *dst, स्थिर व्योम *src)
अणु
	स्थिर काष्ठा अणु अक्षर _[64]; पूर्ण *__src = src;
	काष्ठा अणु अक्षर _[64]; पूर्ण __iomem *__dst = dst;
	पूर्णांक zf;

	/*
	 * ENQCMDS %(rdx), rax
	 *
	 * See movdir64b()'s comment on opeअक्रम specअगरication.
	 */
	यंत्र अस्थिर(".byte 0xf3, 0x0f, 0x38, 0xf8, 0x02, 0x66, 0x90"
		     CC_SET(z)
		     : CC_OUT(z) (zf), "+m" (*__dst)
		     : "m" (*__src), "a" (__dst), "d" (__src));

	/* Submission failure is indicated via EFLAGS.ZF=1 */
	अगर (zf)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_X86_SPECIAL_INSNS_H */
