<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-parisc/cache.h
 */

#अगर_अघोषित __ARCH_PARISC_CACHE_H
#घोषणा __ARCH_PARISC_CACHE_H

#समावेश <यंत्र/alternative.h>

/*
 * PA 2.0 processors have 64 and 128-byte L2 cachelines; PA 1.1 processors
 * have 32-byte cachelines.  The L1 length appears to be 16 bytes but this
 * is not clearly करोcumented.
 */
#घोषणा L1_CACHE_BYTES 16
#घोषणा L1_CACHE_SHIFT 4

#अगर_अघोषित __ASSEMBLY__

#घोषणा SMP_CACHE_BYTES L1_CACHE_BYTES

#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

व्योम parisc_cache_init(व्योम);	/* initializes cache-flushing */
व्योम disable_sr_hashing_यंत्र(पूर्णांक); /* low level support क्रम above */
व्योम disable_sr_hashing(व्योम);   /* turns off space रेजिस्टर hashing */
व्योम मुक्त_sid(अचिन्हित दीर्घ);
अचिन्हित दीर्घ alloc_sid(व्योम);

काष्ठा seq_file;
बाह्य व्योम show_cache_info(काष्ठा seq_file *m);

बाह्य पूर्णांक split_tlb;
बाह्य पूर्णांक dcache_stride;
बाह्य पूर्णांक icache_stride;
बाह्य काष्ठा pdc_cache_info cache_info;
व्योम parisc_setup_cache_timing(व्योम);

#घोषणा pdtlb(addr)	यंत्र अस्थिर("pdtlb 0(%%sr1,%0)" \
			ALTERNATIVE(ALT_COND_NO_SMP, INSN_PxTLB) \
			: : "r" (addr) : "memory")
#घोषणा pitlb(addr)	यंत्र अस्थिर("pitlb 0(%%sr1,%0)" \
			ALTERNATIVE(ALT_COND_NO_SMP, INSN_PxTLB) \
			ALTERNATIVE(ALT_COND_NO_SPLIT_TLB, INSN_NOP) \
			: : "r" (addr) : "memory")
#घोषणा pdtlb_kernel(addr)  यंत्र अस्थिर("pdtlb 0(%0)"   \
			ALTERNATIVE(ALT_COND_NO_SMP, INSN_PxTLB) \
			: : "r" (addr) : "memory")

#घोषणा यंत्र_io_fdc(addr) यंत्र अस्थिर("fdc %%r0(%0)" \
			ALTERNATIVE(ALT_COND_NO_DCACHE, INSN_NOP) \
			ALTERNATIVE(ALT_COND_NO_IOC_FDC, INSN_NOP) \
			: : "r" (addr) : "memory")
#घोषणा यंत्र_io_sync()	यंत्र अस्थिर("sync" \
			ALTERNATIVE(ALT_COND_NO_DCACHE, INSN_NOP) \
			ALTERNATIVE(ALT_COND_NO_IOC_FDC, INSN_NOP) :::"memory")

#पूर्ण_अगर /* ! __ASSEMBLY__ */

/* Classes of processor wrt: disabling space रेजिस्टर hashing */

#घोषणा SRHASH_PCXST    0   /* pcxs, pcxt, pcxt_ */
#घोषणा SRHASH_PCXL     1   /* pcxl */
#घोषणा SRHASH_PA20     2   /* pcxu, pcxu_, pcxw, pcxw_ */

#पूर्ण_अगर
