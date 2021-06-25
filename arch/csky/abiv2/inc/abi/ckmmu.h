<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_CKMMUV2_H
#घोषणा __ASM_CSKY_CKMMUV2_H

#समावेश <abi/reg_ops.h>
#समावेश <यंत्र/barrier.h>

अटल अंतरभूत पूर्णांक पढ़ो_mmu_index(व्योम)
अणु
	वापस mfcr("cr<0, 15>");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_index(पूर्णांक value)
अणु
	mtcr("cr<0, 15>", value);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_mmu_entrylo0(व्योम)
अणु
	वापस mfcr("cr<2, 15>");
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_mmu_entrylo1(व्योम)
अणु
	वापस mfcr("cr<3, 15>");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_pagemask(पूर्णांक value)
अणु
	mtcr("cr<6, 15>", value);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_mmu_entryhi(व्योम)
अणु
	वापस mfcr("cr<4, 15>");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_entryhi(पूर्णांक value)
अणु
	mtcr("cr<4, 15>", value);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_mmu_msa0(व्योम)
अणु
	वापस mfcr("cr<30, 15>");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_msa0(अचिन्हित दीर्घ value)
अणु
	mtcr("cr<30, 15>", value);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_mmu_msa1(व्योम)
अणु
	वापस mfcr("cr<31, 15>");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_msa1(अचिन्हित दीर्घ value)
अणु
	mtcr("cr<31, 15>", value);
पूर्ण

/*
 * TLB operations.
 */
अटल अंतरभूत व्योम tlb_probe(व्योम)
अणु
	mtcr("cr<8, 15>", 0x80000000);
पूर्ण

अटल अंतरभूत व्योम tlb_पढ़ो(व्योम)
अणु
	mtcr("cr<8, 15>", 0x40000000);
पूर्ण

अटल अंतरभूत व्योम tlb_invalid_all(व्योम)
अणु
#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
	यंत्र अस्थिर(
		"tlbi.alls	\n"
		"sync.i		\n"
		:
		:
		: "memory");
#अन्यथा
	mtcr("cr<8, 15>", 0x04000000);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम local_tlb_invalid_all(व्योम)
अणु
#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
	यंत्र अस्थिर(
		"tlbi.all	\n"
		"sync.i		\n"
		:
		:
		: "memory");
#अन्यथा
	tlb_invalid_all();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम tlb_invalid_indexed(व्योम)
अणु
	mtcr("cr<8, 15>", 0x02000000);
पूर्ण

#घोषणा NOP32 ".long 0x4820c400\n"

अटल अंतरभूत व्योम setup_pgd(pgd_t *pgd, पूर्णांक asid)
अणु
#अगर_घोषित CONFIG_CPU_HAS_TLBI
	sync_is();
#अन्यथा
	mb();
#पूर्ण_अगर
	यंत्र अस्थिर(
#अगर_घोषित CONFIG_CPU_HAS_TLBI
		"mtcr %1, cr<28, 15>	\n"
#पूर्ण_अगर
		"mtcr %1, cr<29, 15>	\n"
		"mtcr %0, cr< 4, 15>	\n"
		".rept 64		\n"
		NOP32
		".endr			\n"
		:
		:"r"(asid), "r"(__pa(pgd) | BIT(0))
		:"memory");
पूर्ण

अटल अंतरभूत pgd_t *get_pgd(व्योम)
अणु
	वापस __va(mfcr("cr<29, 15>") & ~BIT(0));
पूर्ण
#पूर्ण_अगर /* __ASM_CSKY_CKMMUV2_H */
