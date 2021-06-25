<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _H8300_PGTABLE_H
#घोषणा _H8300_PGTABLE_H
#समावेश <यंत्र-generic/pgtable-nopud.h>
बाह्य व्योम paging_init(व्योम);
#घोषणा PAGE_NONE		__pgprot(0)    /* these mean nothing to NO_MM */
#घोषणा PAGE_SHARED		__pgprot(0)    /* these mean nothing to NO_MM */
#घोषणा PAGE_COPY		__pgprot(0)    /* these mean nothing to NO_MM */
#घोषणा PAGE_READONLY	__pgprot(0)    /* these mean nothing to NO_MM */
#घोषणा PAGE_KERNEL		__pgprot(0)    /* these mean nothing to NO_MM */
#घोषणा __swp_type(x)		(0)
#घोषणा __swp_offset(x)		(0)
#घोषणा __swp_entry(typ, off)	((swp_entry_t) अणु ((typ) | ((off) << 7)) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)
#घोषणा kern_addr_valid(addr)	(1)
#घोषणा pgprot_ग_लिखोcombine(prot)  (prot)
#घोषणा pgprot_noncached pgprot_ग_लिखोcombine

अटल अंतरभूत पूर्णांक pte_file(pte_t pte) अणु वापस 0; पूर्ण
#घोषणा swapper_pg_dir ((pgd_t *) 0)
/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(0))

/*
 * These would be in other places but having them here reduces the dअगरfs.
 */
बाह्य अचिन्हित पूर्णांक kobjsize(स्थिर व्योम *objp);
बाह्य पूर्णांक is_in_rom(अचिन्हित दीर्घ);

/*
 * All 32bit addresses are effectively valid क्रम vदो_स्मृति...
 * Sort of meaningless क्रम non-VM tarमाला_लो.
 */
#घोषणा	VMALLOC_START	0
#घोषणा	VMALLOC_END	0xffffffff

#घोषणा arch_enter_lazy_cpu_mode()    करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर /* _H8300_PGTABLE_H */
