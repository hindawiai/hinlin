<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_CACHE_H
#घोषणा _ASM_POWERPC_CACHE_H

#अगर_घोषित __KERNEL__


/* bytes per L1 cache line */
#अगर defined(CONFIG_PPC_8xx)
#घोषणा L1_CACHE_SHIFT		4
#घोषणा MAX_COPY_PREFETCH	1
#घोषणा IFETCH_ALIGN_SHIFT	2
#या_अगर defined(CONFIG_PPC_E500MC)
#घोषणा L1_CACHE_SHIFT		6
#घोषणा MAX_COPY_PREFETCH	4
#घोषणा IFETCH_ALIGN_SHIFT	3
#या_अगर defined(CONFIG_PPC32)
#घोषणा MAX_COPY_PREFETCH	4
#घोषणा IFETCH_ALIGN_SHIFT	3	/* 603 fetches 2 insn at a समय */
#अगर defined(CONFIG_PPC_47x)
#घोषणा L1_CACHE_SHIFT		7
#अन्यथा
#घोषणा L1_CACHE_SHIFT		5
#पूर्ण_अगर
#अन्यथा /* CONFIG_PPC64 */
#घोषणा L1_CACHE_SHIFT		7
#घोषणा IFETCH_ALIGN_SHIFT	4 /* POWER8,9 */
#पूर्ण_अगर

#घोषणा	L1_CACHE_BYTES		(1 << L1_CACHE_SHIFT)

#घोषणा	SMP_CACHE_BYTES		L1_CACHE_BYTES

#घोषणा IFETCH_ALIGN_BYTES	(1 << IFETCH_ALIGN_SHIFT)

#अगर !defined(__ASSEMBLY__)
#अगर_घोषित CONFIG_PPC64

काष्ठा ppc_cache_info अणु
	u32 size;
	u32 line_size;
	u32 block_size;	/* L1 only */
	u32 log_block_size;
	u32 blocks_per_page;
	u32 sets;
	u32 assoc;
पूर्ण;

काष्ठा ppc64_caches अणु
	काष्ठा ppc_cache_info l1d;
	काष्ठा ppc_cache_info l1i;
	काष्ठा ppc_cache_info l2;
	काष्ठा ppc_cache_info l3;
पूर्ण;

बाह्य काष्ठा ppc64_caches ppc64_caches;

अटल अंतरभूत u32 l1_dcache_shअगरt(व्योम)
अणु
	वापस ppc64_caches.l1d.log_block_size;
पूर्ण

अटल अंतरभूत u32 l1_dcache_bytes(व्योम)
अणु
	वापस ppc64_caches.l1d.block_size;
पूर्ण

अटल अंतरभूत u32 l1_icache_shअगरt(व्योम)
अणु
	वापस ppc64_caches.l1i.log_block_size;
पूर्ण

अटल अंतरभूत u32 l1_icache_bytes(व्योम)
अणु
	वापस ppc64_caches.l1i.block_size;
पूर्ण
#अन्यथा
अटल अंतरभूत u32 l1_dcache_shअगरt(व्योम)
अणु
	वापस L1_CACHE_SHIFT;
पूर्ण

अटल अंतरभूत u32 l1_dcache_bytes(व्योम)
अणु
	वापस L1_CACHE_BYTES;
पूर्ण

अटल अंतरभूत u32 l1_icache_shअगरt(व्योम)
अणु
	वापस L1_CACHE_SHIFT;
पूर्ण

अटल अंतरभूत u32 l1_icache_bytes(व्योम)
अणु
	वापस L1_CACHE_BYTES;
पूर्ण

#पूर्ण_अगर

#घोषणा __पढ़ो_mostly __section(".data..read_mostly")

#अगर_घोषित CONFIG_PPC_BOOK3S_32
बाह्य दीर्घ _get_L2CR(व्योम);
बाह्य दीर्घ _get_L3CR(व्योम);
बाह्य व्योम _set_L2CR(अचिन्हित दीर्घ);
बाह्य व्योम _set_L3CR(अचिन्हित दीर्घ);
#अन्यथा
#घोषणा _get_L2CR()	0L
#घोषणा _get_L3CR()	0L
#घोषणा _set_L2CR(val)	करो अणु पूर्ण जबतक(0)
#घोषणा _set_L3CR(val)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल अंतरभूत व्योम dcbz(व्योम *addr)
अणु
	__यंत्र__ __अस्थिर__ ("dcbz 0, %0" : : "r"(addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम dcbi(व्योम *addr)
अणु
	__यंत्र__ __अस्थिर__ ("dcbi 0, %0" : : "r"(addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम dcbf(व्योम *addr)
अणु
	__यंत्र__ __अस्थिर__ ("dcbf 0, %0" : : "r"(addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम dcbst(व्योम *addr)
अणु
	__यंत्र__ __अस्थिर__ ("dcbst 0, %0" : : "r"(addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम icbi(व्योम *addr)
अणु
	यंत्र अस्थिर ("icbi 0, %0" : : "r"(addr) : "memory");
पूर्ण

अटल अंतरभूत व्योम iccci(व्योम *addr)
अणु
	यंत्र अस्थिर ("iccci 0, %0" : : "r"(addr) : "memory");
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_CACHE_H */
