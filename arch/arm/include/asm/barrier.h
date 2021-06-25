<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_BARRIER_H
#घोषणा __ASM_BARRIER_H

#अगर_अघोषित __ASSEMBLY__

#घोषणा nop() __यंत्र__ __अस्थिर__("mov\tr0,r0\t@ nop\n\t");

#अगर __LINUX_ARM_ARCH__ >= 7 ||		\
	(__LINUX_ARM_ARCH__ == 6 && defined(CONFIG_CPU_32v6K))
#घोषणा sev()	__यंत्र__ __अस्थिर__ ("sev" : : : "memory")
#घोषणा wfe()	__यंत्र__ __अस्थिर__ ("wfe" : : : "memory")
#घोषणा wfi()	__यंत्र__ __अस्थिर__ ("wfi" : : : "memory")
#अन्यथा
#घोषणा wfe()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर __LINUX_ARM_ARCH__ >= 7
#घोषणा isb(option) __यंत्र__ __अस्थिर__ ("isb " #option : : : "memory")
#घोषणा dsb(option) __यंत्र__ __अस्थिर__ ("dsb " #option : : : "memory")
#घोषणा dmb(option) __यंत्र__ __अस्थिर__ ("dmb " #option : : : "memory")
#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा CSDB	".inst.w 0xf3af8014"
#अन्यथा
#घोषणा CSDB	".inst	0xe320f014"
#पूर्ण_अगर
#घोषणा csdb() __यंत्र__ __अस्थिर__(CSDB : : : "memory")
#या_अगर defined(CONFIG_CPU_XSC3) || __LINUX_ARM_ARCH__ == 6
#घोषणा isb(x) __यंत्र__ __अस्थिर__ ("mcr p15, 0, %0, c7, c5, 4" \
				    : : "r" (0) : "memory")
#घोषणा dsb(x) __यंत्र__ __अस्थिर__ ("mcr p15, 0, %0, c7, c10, 4" \
				    : : "r" (0) : "memory")
#घोषणा dmb(x) __यंत्र__ __अस्थिर__ ("mcr p15, 0, %0, c7, c10, 5" \
				    : : "r" (0) : "memory")
#या_अगर defined(CONFIG_CPU_FA526)
#घोषणा isb(x) __यंत्र__ __अस्थिर__ ("mcr p15, 0, %0, c7, c5, 4" \
				    : : "r" (0) : "memory")
#घोषणा dsb(x) __यंत्र__ __अस्थिर__ ("mcr p15, 0, %0, c7, c10, 4" \
				    : : "r" (0) : "memory")
#घोषणा dmb(x) __यंत्र__ __अस्थिर__ ("" : : : "memory")
#अन्यथा
#घोषणा isb(x) __यंत्र__ __अस्थिर__ ("" : : : "memory")
#घोषणा dsb(x) __यंत्र__ __अस्थिर__ ("mcr p15, 0, %0, c7, c10, 4" \
				    : : "r" (0) : "memory")
#घोषणा dmb(x) __यंत्र__ __अस्थिर__ ("" : : : "memory")
#पूर्ण_अगर

#अगर_अघोषित CSDB
#घोषणा CSDB
#पूर्ण_अगर
#अगर_अघोषित csdb
#घोषणा csdb()
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARM_HEAVY_MB
बाह्य व्योम (*soc_mb)(व्योम);
बाह्य व्योम arm_heavy_mb(व्योम);
#घोषणा __arm_heavy_mb(x...) करो अणु dsb(x); arm_heavy_mb(); पूर्ण जबतक (0)
#अन्यथा
#घोषणा __arm_heavy_mb(x...) dsb(x)
#पूर्ण_अगर

#अगर defined(CONFIG_ARM_DMA_MEM_BUFFERABLE) || defined(CONFIG_SMP)
#घोषणा mb()		__arm_heavy_mb()
#घोषणा rmb()		dsb()
#घोषणा wmb()		__arm_heavy_mb(st)
#घोषणा dma_rmb()	dmb(osh)
#घोषणा dma_wmb()	dmb(oshst)
#अन्यथा
#घोषणा mb()		barrier()
#घोषणा rmb()		barrier()
#घोषणा wmb()		barrier()
#घोषणा dma_rmb()	barrier()
#घोषणा dma_wmb()	barrier()
#पूर्ण_अगर

#घोषणा __smp_mb()	dmb(ish)
#घोषणा __smp_rmb()	__smp_mb()
#घोषणा __smp_wmb()	dmb(ishst)

#अगर_घोषित CONFIG_CPU_SPECTRE
अटल अंतरभूत अचिन्हित दीर्घ array_index_mask_nospec(अचिन्हित दीर्घ idx,
						    अचिन्हित दीर्घ sz)
अणु
	अचिन्हित दीर्घ mask;

	यंत्र अस्थिर(
		"cmp	%1, %2\n"
	"	sbc	%0, %1, %1\n"
	CSDB
	: "=r" (mask)
	: "r" (idx), "Ir" (sz)
	: "cc");

	वापस mask;
पूर्ण
#घोषणा array_index_mask_nospec array_index_mask_nospec
#पूर्ण_अगर

#समावेश <यंत्र-generic/barrier.h>

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __ASM_BARRIER_H */
