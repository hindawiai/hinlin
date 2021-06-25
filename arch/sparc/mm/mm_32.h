<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* fault_32.c - visible as they are called from assembler */
यंत्रlinkage व्योम करो_sparc_fault(काष्ठा pt_regs *regs, पूर्णांक text_fault, पूर्णांक ग_लिखो,
                               अचिन्हित दीर्घ address);

व्योम winकरोw_overflow_fault(व्योम);
व्योम winकरोw_underflow_fault(अचिन्हित दीर्घ sp);
व्योम winकरोw_ret_fault(काष्ठा pt_regs *regs);

/* srmmu.c */
बाह्य अक्षर *srmmu_name;
बाह्य पूर्णांक viking_mxcc_present;
बाह्य पूर्णांक flush_page_क्रम_dma_global;

बाह्य व्योम (*poke_srmmu)(व्योम);

व्योम __init srmmu_paging_init(व्योम);

/* iommu.c */
व्योम ld_mmu_iommu(व्योम);
