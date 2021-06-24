<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_CKMMUV1_H
#घोषणा __ASM_CSKY_CKMMUV1_H
#समावेश <abi/reg_ops.h>

अटल अंतरभूत पूर्णांक पढ़ो_mmu_index(व्योम)
अणु
	वापस cprcr("cpcr0");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_index(पूर्णांक value)
अणु
	cpwcr("cpcr0", value);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_mmu_entrylo0(व्योम)
अणु
	वापस cprcr("cpcr2") << 6;
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_mmu_entrylo1(व्योम)
अणु
	वापस cprcr("cpcr3") << 6;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_pagemask(पूर्णांक value)
अणु
	cpwcr("cpcr6", value);
पूर्ण

अटल अंतरभूत पूर्णांक पढ़ो_mmu_entryhi(व्योम)
अणु
	वापस cprcr("cpcr4");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_entryhi(पूर्णांक value)
अणु
	cpwcr("cpcr4", value);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_mmu_msa0(व्योम)
अणु
	वापस cprcr("cpcr30");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_msa0(अचिन्हित दीर्घ value)
अणु
	cpwcr("cpcr30", value);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_mmu_msa1(व्योम)
अणु
	वापस cprcr("cpcr31");
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_mmu_msa1(अचिन्हित दीर्घ value)
अणु
	cpwcr("cpcr31", value);
पूर्ण

/*
 * TLB operations.
 */
अटल अंतरभूत व्योम tlb_probe(व्योम)
अणु
	cpwcr("cpcr8", 0x80000000);
पूर्ण

अटल अंतरभूत व्योम tlb_पढ़ो(व्योम)
अणु
	cpwcr("cpcr8", 0x40000000);
पूर्ण

अटल अंतरभूत व्योम tlb_invalid_all(व्योम)
अणु
	cpwcr("cpcr8", 0x04000000);
पूर्ण


अटल अंतरभूत व्योम local_tlb_invalid_all(व्योम)
अणु
	tlb_invalid_all();
पूर्ण

अटल अंतरभूत व्योम tlb_invalid_indexed(व्योम)
अणु
	cpwcr("cpcr8", 0x02000000);
पूर्ण

अटल अंतरभूत व्योम setup_pgd(pgd_t *pgd, पूर्णांक asid)
अणु
	cpwcr("cpcr29", __pa(pgd) | BIT(0));
	ग_लिखो_mmu_entryhi(asid);
पूर्ण

अटल अंतरभूत pgd_t *get_pgd(व्योम)
अणु
	वापस __va(cprcr("cpcr29") & ~BIT(0));
पूर्ण
#पूर्ण_अगर /* __ASM_CSKY_CKMMUV1_H */
