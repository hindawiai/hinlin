<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_TLBFLUSH_H
#घोषणा _XTENSA_TLBFLUSH_H

#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/processor.h>

#घोषणा DTLB_WAY_PGD	7

#घोषणा ITLB_ARF_WAYS	4
#घोषणा DTLB_ARF_WAYS	4

#घोषणा ITLB_HIT_BIT	3
#घोषणा DTLB_HIT_BIT	4

#अगर_अघोषित __ASSEMBLY__

/* TLB flushing:
 *
 *  - flush_tlb_all() flushes all processes TLB entries
 *  - flush_tlb_mm(mm) flushes the specअगरied mm context TLB entries
 *  - flush_tlb_page(mm, vmaddr) flushes a single page
 *  - flush_tlb_range(mm, start, end) flushes a range of pages
 */

व्योम local_flush_tlb_all(व्योम);
व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ page);
व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#अगर_घोषित CONFIG_SMP

व्योम flush_tlb_all(व्योम);
व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *);
व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ);
व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ,
		अचिन्हित दीर्घ);
व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#अन्यथा /* !CONFIG_SMP */

#घोषणा flush_tlb_all()			   local_flush_tlb_all()
#घोषणा flush_tlb_mm(mm)		   local_flush_tlb_mm(mm)
#घोषणा flush_tlb_page(vma, page)	   local_flush_tlb_page(vma, page)
#घोषणा flush_tlb_range(vma, vmaddr, end)  local_flush_tlb_range(vma, vmaddr, \
								 end)
#घोषणा flush_tlb_kernel_range(start, end) local_flush_tlb_kernel_range(start, \
									end)

#पूर्ण_अगर /* CONFIG_SMP */

/* TLB operations. */

अटल अंतरभूत अचिन्हित दीर्घ itlb_probe(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__("pitlb  %0, %1\n\t" : "=a" (पंचांगp) : "a" (addr));
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dtlb_probe(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__("pdtlb  %0, %1\n\t" : "=a" (पंचांगp) : "a" (addr));
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम invalidate_itlb_entry (अचिन्हित दीर्घ probe)
अणु
	__यंत्र__ __अस्थिर__("iitlb  %0; isync\n\t" : : "a" (probe));
पूर्ण

अटल अंतरभूत व्योम invalidate_dtlb_entry (अचिन्हित दीर्घ probe)
अणु
	__यंत्र__ __अस्थिर__("idtlb  %0; dsync\n\t" : : "a" (probe));
पूर्ण

/* Use the .._no_isync functions with caution.  Generally, these are
 * handy क्रम bulk invalidates followed by a single 'isync'.  The
 * caller must follow up with an 'isync', which can be relatively
 * expensive on some Xtensa implementations.
 */
अटल अंतरभूत व्योम invalidate_itlb_entry_no_isync (अचिन्हित entry)
अणु
	/* Caller must follow up with 'isync'. */
	__यंत्र__ __अस्थिर__ ("iitlb  %0\n" : : "a" (entry) );
पूर्ण

अटल अंतरभूत व्योम invalidate_dtlb_entry_no_isync (अचिन्हित entry)
अणु
	/* Caller must follow up with 'isync'. */
	__यंत्र__ __अस्थिर__ ("idtlb  %0\n" : : "a" (entry) );
पूर्ण

अटल अंतरभूत व्योम set_itlbcfg_रेजिस्टर (अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__("wsr  %0, itlbcfg\n\t" "isync\n\t"
			     : : "a" (val));
पूर्ण

अटल अंतरभूत व्योम set_dtlbcfg_रेजिस्टर (अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__("wsr  %0, dtlbcfg; dsync\n\t"
	    		     : : "a" (val));
पूर्ण

अटल अंतरभूत व्योम set_ptevaddr_रेजिस्टर (अचिन्हित दीर्घ val)
अणु
	__यंत्र__ __अस्थिर__(" wsr  %0, ptevaddr; isync\n"
			     : : "a" (val));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_ptevaddr_रेजिस्टर (व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__("rsr  %0, ptevaddr\n\t" : "=a" (पंचांगp));
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_dtlb_entry (pte_t entry, पूर्णांक way)
अणु
	__यंत्र__ __अस्थिर__("wdtlb  %1, %0; dsync\n\t"
			     : : "r" (way), "r" (entry) );
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_itlb_entry (pte_t entry, पूर्णांक way)
अणु
	__यंत्र__ __अस्थिर__("witlb  %1, %0; isync\n\t"
	                     : : "r" (way), "r" (entry) );
पूर्ण

अटल अंतरभूत व्योम invalidate_page_directory (व्योम)
अणु
	invalidate_dtlb_entry (DTLB_WAY_PGD);
	invalidate_dtlb_entry (DTLB_WAY_PGD+1);
	invalidate_dtlb_entry (DTLB_WAY_PGD+2);
पूर्ण

अटल अंतरभूत व्योम invalidate_itlb_mapping (अचिन्हित address)
अणु
	अचिन्हित दीर्घ tlb_entry;
	अगर (((tlb_entry = itlb_probe(address)) & (1 << ITLB_HIT_BIT)) != 0)
		invalidate_itlb_entry(tlb_entry);
पूर्ण

अटल अंतरभूत व्योम invalidate_dtlb_mapping (अचिन्हित address)
अणु
	अचिन्हित दीर्घ tlb_entry;
	अगर (((tlb_entry = dtlb_probe(address)) & (1 << DTLB_HIT_BIT)) != 0)
		invalidate_dtlb_entry(tlb_entry);
पूर्ण

/*
 * DO NOT USE THESE FUNCTIONS.  These inकाष्ठाions aren't part of the Xtensa
 * ISA and exist only क्रम test purposes..
 * You may find it helpful क्रम MMU debugging, however.
 *
 * 'at' is the unmodअगरied input रेजिस्टर
 * 'as' is the output रेजिस्टर, as follows (specअगरic to the Linux config):
 *
 *      as[31..12] contain the भव address
 *      as[11..08] are meaningless
 *      as[07..00] contain the asid
 */

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_dtlb_भव (पूर्णांक way)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__("rdtlb0  %0, %1\n\t" : "=a" (पंचांगp), "+a" (way));
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_dtlb_translation (पूर्णांक way)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__("rdtlb1  %0, %1\n\t" : "=a" (पंचांगp), "+a" (way));
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_itlb_भव (पूर्णांक way)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__("ritlb0  %0, %1\n\t" : "=a" (पंचांगp), "+a" (way));
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_itlb_translation (पूर्णांक way)
अणु
	अचिन्हित दीर्घ पंचांगp;
	__यंत्र__ __अस्थिर__("ritlb1  %0, %1\n\t" : "=a" (पंचांगp), "+a" (way));
	वापस पंचांगp;
पूर्ण

#पूर्ण_अगर	/* __ASSEMBLY__ */
#पूर्ण_अगर	/* _XTENSA_TLBFLUSH_H */
