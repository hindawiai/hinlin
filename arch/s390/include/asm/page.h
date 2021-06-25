<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com)
 */

#अगर_अघोषित _S390_PAGE_H
#घोषणा _S390_PAGE_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/types.h>

#घोषणा _PAGE_SHIFT	12
#घोषणा _PAGE_SIZE	(_AC(1, UL) << _PAGE_SHIFT)
#घोषणा _PAGE_MASK	(~(_PAGE_SIZE - 1))

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT	_PAGE_SHIFT
#घोषणा PAGE_SIZE	_PAGE_SIZE
#घोषणा PAGE_MASK	_PAGE_MASK
#घोषणा PAGE_DEFAULT_ACC	0
#घोषणा PAGE_DEFAULT_KEY	(PAGE_DEFAULT_ACC << 4)

#घोषणा HPAGE_SHIFT	20
#घोषणा HPAGE_SIZE	(1UL << HPAGE_SHIFT)
#घोषणा HPAGE_MASK	(~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)
#घोषणा HUGE_MAX_HSTATE		2

#घोषणा ARCH_HAS_SETCLEAR_HUGE_PTE
#घोषणा ARCH_HAS_HUGE_PTE_TYPE
#घोषणा ARCH_HAS_PREPARE_HUGEPAGE
#घोषणा ARCH_HAS_HUGEPAGE_CLEAR_FLUSH

#घोषणा HAVE_ARCH_HUGETLB_UNMAPPED_AREA

#समावेश <यंत्र/setup.h>
#अगर_अघोषित __ASSEMBLY__

व्योम __storage_key_init_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

अटल अंतरभूत व्योम storage_key_init_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (PAGE_DEFAULT_KEY != 0)
		__storage_key_init_range(start, end);
पूर्ण

#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)

/*
 * copy_page uses the mvcl inकाष्ठाion with 0xb0 padding byte in order to
 * bypass caches when copying a page. Especially when copying huge pages
 * this keeps L1 and L2 data caches alive.
 */
अटल अंतरभूत व्योम copy_page(व्योम *to, व्योम *from)
अणु
	रेजिस्टर व्योम *reg2 यंत्र ("2") = to;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र ("3") = 0x1000;
	रेजिस्टर व्योम *reg4 यंत्र ("4") = from;
	रेजिस्टर अचिन्हित दीर्घ reg5 यंत्र ("5") = 0xb0001000;
	यंत्र अस्थिर(
		"	mvcl	2,4"
		: "+d" (reg2), "+d" (reg3), "+d" (reg4), "+d" (reg5)
		: : "memory", "cc");
पूर्ण

#घोषणा clear_user_page(page, vaddr, pg)	clear_page(page)
#घोषणा copy_user_page(to, from, vaddr, pg)	copy_page(to, from)

#घोषणा __alloc_zeroed_user_highpage(movableflags, vma, vaddr) \
	alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO | movableflags, vma, vaddr)
#घोषणा __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE

/*
 * These are used to make use of C type-checking..
 */

प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgste; पूर्ण pgste_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pmd; पूर्ण pmd_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pud; पूर्ण pud_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ p4d; पूर्ण p4d_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
प्रकार pte_t *pgtable_t;

#घोषणा pgprot_val(x)	((x).pgprot)
#घोषणा pgste_val(x)	((x).pgste)
#घोषणा pte_val(x)	((x).pte)
#घोषणा pmd_val(x)	((x).pmd)
#घोषणा pud_val(x)	((x).pud)
#घोषणा p4d_val(x)	((x).p4d)
#घोषणा pgd_val(x)      ((x).pgd)

#घोषणा __pgste(x)	((pgste_t) अणु (x) पूर्ण )
#घोषणा __pte(x)        ((pte_t) अणु (x) पूर्ण )
#घोषणा __pmd(x)        ((pmd_t) अणु (x) पूर्ण )
#घोषणा __pud(x)	((pud_t) अणु (x) पूर्ण )
#घोषणा __p4d(x)	((p4d_t) अणु (x) पूर्ण )
#घोषणा __pgd(x)        ((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)     ((pgprot_t) अणु (x) पूर्ण )

अटल अंतरभूत व्योम page_set_storage_key(अचिन्हित दीर्घ addr,
					अचिन्हित अक्षर skey, पूर्णांक mapped)
अणु
	अगर (!mapped)
		यंत्र अस्थिर(".insn rrf,0xb22b0000,%0,%1,8,0"
			     : : "d" (skey), "a" (addr));
	अन्यथा
		यंत्र अस्थिर("sske %0,%1" : : "d" (skey), "a" (addr));
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर page_get_storage_key(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर skey;

	यंत्र अस्थिर("iske %0,%1" : "=d" (skey) : "a" (addr));
	वापस skey;
पूर्ण

अटल अंतरभूत पूर्णांक page_reset_referenced(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक cc;

	यंत्र अस्थिर(
		"	rrbe	0,%1\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc) : "a" (addr) : "cc");
	वापस cc;
पूर्ण

/* Bits पूर्णांक the storage key */
#घोषणा _PAGE_CHANGED		0x02	/* HW changed bit		*/
#घोषणा _PAGE_REFERENCED	0x04	/* HW referenced bit		*/
#घोषणा _PAGE_FP_BIT		0x08	/* HW fetch protection bit	*/
#घोषणा _PAGE_ACC_BITS		0xf0	/* HW access control bits	*/

काष्ठा page;
व्योम arch_मुक्त_page(काष्ठा page *page, पूर्णांक order);
व्योम arch_alloc_page(काष्ठा page *page, पूर्णांक order);
व्योम arch_set_page_dat(काष्ठा page *page, पूर्णांक order);
व्योम arch_set_page_nodat(काष्ठा page *page, पूर्णांक order);
पूर्णांक arch_test_page_nodat(काष्ठा page *page);
व्योम arch_set_page_states(पूर्णांक make_stable);

अटल अंतरभूत पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pfn)
अणु
	वापस 0;
पूर्ण

#घोषणा HAVE_ARCH_FREE_PAGE
#घोषणा HAVE_ARCH_ALLOC_PAGE

#अगर IS_ENABLED(CONFIG_PGSTE)
पूर्णांक arch_make_page_accessible(काष्ठा page *page);
#घोषणा HAVE_ARCH_MAKE_PAGE_ACCESSIBLE
#पूर्ण_अगर

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा __PAGE_OFFSET		0x0UL
#घोषणा PAGE_OFFSET		0x0UL

#घोषणा __pa(x)			((अचिन्हित दीर्घ)(x))
#घोषणा __va(x)			((व्योम *)(अचिन्हित दीर्घ)(x))

#घोषणा phys_to_pfn(phys)	((phys) >> PAGE_SHIFT)
#घोषणा pfn_to_phys(pfn)	((pfn) << PAGE_SHIFT)

#घोषणा phys_to_page(phys)	pfn_to_page(phys_to_pfn(phys))
#घोषणा page_to_phys(page)	pfn_to_phys(page_to_pfn(page))

#घोषणा pfn_to_virt(pfn)	__va(pfn_to_phys(pfn))
#घोषणा virt_to_pfn(kaddr)	(phys_to_pfn(__pa(kaddr)))
#घोषणा pfn_to_kaddr(pfn)	pfn_to_virt(pfn)

#घोषणा virt_to_page(kaddr)	pfn_to_page(virt_to_pfn(kaddr))
#घोषणा page_to_virt(page)	pfn_to_virt(page_to_pfn(page))

#घोषणा virt_addr_valid(kaddr)	pfn_valid(virt_to_pfn(kaddr))

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_NON_EXEC

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _S390_PAGE_H */
