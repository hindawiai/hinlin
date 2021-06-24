<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_DEFS_H
#घोषणा _ASM_X86_PGTABLE_DEFS_H

#समावेश <linux/स्थिर.h>
#समावेश <linux/mem_encrypt.h>

#समावेश <यंत्र/page_types.h>

#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा _PAGE_BIT_PRESENT	0	/* is present */
#घोषणा _PAGE_BIT_RW		1	/* ग_लिखोable */
#घोषणा _PAGE_BIT_USER		2	/* userspace addressable */
#घोषणा _PAGE_BIT_PWT		3	/* page ग_लिखो through */
#घोषणा _PAGE_BIT_PCD		4	/* page cache disabled */
#घोषणा _PAGE_BIT_ACCESSED	5	/* was accessed (उठाओd by CPU) */
#घोषणा _PAGE_BIT_सूचीTY		6	/* was written to (उठाओd by CPU) */
#घोषणा _PAGE_BIT_PSE		7	/* 4 MB (or 2MB) page */
#घोषणा _PAGE_BIT_PAT		7	/* on 4KB pages */
#घोषणा _PAGE_BIT_GLOBAL	8	/* Global TLB entry PPro+ */
#घोषणा _PAGE_BIT_SOFTW1	9	/* available क्रम programmer */
#घोषणा _PAGE_BIT_SOFTW2	10	/* " */
#घोषणा _PAGE_BIT_SOFTW3	11	/* " */
#घोषणा _PAGE_BIT_PAT_LARGE	12	/* On 2MB or 1GB pages */
#घोषणा _PAGE_BIT_SOFTW4	58	/* available क्रम programmer */
#घोषणा _PAGE_BIT_PKEY_BIT0	59	/* Protection Keys, bit 1/4 */
#घोषणा _PAGE_BIT_PKEY_BIT1	60	/* Protection Keys, bit 2/4 */
#घोषणा _PAGE_BIT_PKEY_BIT2	61	/* Protection Keys, bit 3/4 */
#घोषणा _PAGE_BIT_PKEY_BIT3	62	/* Protection Keys, bit 4/4 */
#घोषणा _PAGE_BIT_NX		63	/* No execute: only valid after cpuid check */

#घोषणा _PAGE_BIT_SPECIAL	_PAGE_BIT_SOFTW1
#घोषणा _PAGE_BIT_CPA_TEST	_PAGE_BIT_SOFTW1
#घोषणा _PAGE_BIT_UFFD_WP	_PAGE_BIT_SOFTW2 /* userfaultfd wrरक्षित */
#घोषणा _PAGE_BIT_SOFT_सूचीTY	_PAGE_BIT_SOFTW3 /* software dirty tracking */
#घोषणा _PAGE_BIT_DEVMAP	_PAGE_BIT_SOFTW4

/* If _PAGE_BIT_PRESENT is clear, we use these: */
/* - अगर the user mapped it with PROT_NONE; pte_present gives true */
#घोषणा _PAGE_BIT_PROTNONE	_PAGE_BIT_GLOBAL

#घोषणा _PAGE_PRESENT	(_AT(pteval_t, 1) << _PAGE_BIT_PRESENT)
#घोषणा _PAGE_RW	(_AT(pteval_t, 1) << _PAGE_BIT_RW)
#घोषणा _PAGE_USER	(_AT(pteval_t, 1) << _PAGE_BIT_USER)
#घोषणा _PAGE_PWT	(_AT(pteval_t, 1) << _PAGE_BIT_PWT)
#घोषणा _PAGE_PCD	(_AT(pteval_t, 1) << _PAGE_BIT_PCD)
#घोषणा _PAGE_ACCESSED	(_AT(pteval_t, 1) << _PAGE_BIT_ACCESSED)
#घोषणा _PAGE_सूचीTY	(_AT(pteval_t, 1) << _PAGE_BIT_सूचीTY)
#घोषणा _PAGE_PSE	(_AT(pteval_t, 1) << _PAGE_BIT_PSE)
#घोषणा _PAGE_GLOBAL	(_AT(pteval_t, 1) << _PAGE_BIT_GLOBAL)
#घोषणा _PAGE_SOFTW1	(_AT(pteval_t, 1) << _PAGE_BIT_SOFTW1)
#घोषणा _PAGE_SOFTW2	(_AT(pteval_t, 1) << _PAGE_BIT_SOFTW2)
#घोषणा _PAGE_SOFTW3	(_AT(pteval_t, 1) << _PAGE_BIT_SOFTW3)
#घोषणा _PAGE_PAT	(_AT(pteval_t, 1) << _PAGE_BIT_PAT)
#घोषणा _PAGE_PAT_LARGE (_AT(pteval_t, 1) << _PAGE_BIT_PAT_LARGE)
#घोषणा _PAGE_SPECIAL	(_AT(pteval_t, 1) << _PAGE_BIT_SPECIAL)
#घोषणा _PAGE_CPA_TEST	(_AT(pteval_t, 1) << _PAGE_BIT_CPA_TEST)
#अगर_घोषित CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS
#घोषणा _PAGE_PKEY_BIT0	(_AT(pteval_t, 1) << _PAGE_BIT_PKEY_BIT0)
#घोषणा _PAGE_PKEY_BIT1	(_AT(pteval_t, 1) << _PAGE_BIT_PKEY_BIT1)
#घोषणा _PAGE_PKEY_BIT2	(_AT(pteval_t, 1) << _PAGE_BIT_PKEY_BIT2)
#घोषणा _PAGE_PKEY_BIT3	(_AT(pteval_t, 1) << _PAGE_BIT_PKEY_BIT3)
#अन्यथा
#घोषणा _PAGE_PKEY_BIT0	(_AT(pteval_t, 0))
#घोषणा _PAGE_PKEY_BIT1	(_AT(pteval_t, 0))
#घोषणा _PAGE_PKEY_BIT2	(_AT(pteval_t, 0))
#घोषणा _PAGE_PKEY_BIT3	(_AT(pteval_t, 0))
#पूर्ण_अगर

#घोषणा _PAGE_PKEY_MASK (_PAGE_PKEY_BIT0 | \
			 _PAGE_PKEY_BIT1 | \
			 _PAGE_PKEY_BIT2 | \
			 _PAGE_PKEY_BIT3)

#अगर defined(CONFIG_X86_64) || defined(CONFIG_X86_PAE)
#घोषणा _PAGE_KNL_ERRATUM_MASK (_PAGE_सूचीTY | _PAGE_ACCESSED)
#अन्यथा
#घोषणा _PAGE_KNL_ERRATUM_MASK 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
#घोषणा _PAGE_SOFT_सूचीTY	(_AT(pteval_t, 1) << _PAGE_BIT_SOFT_सूचीTY)
#अन्यथा
#घोषणा _PAGE_SOFT_सूचीTY	(_AT(pteval_t, 0))
#पूर्ण_अगर

/*
 * Tracking soft dirty bit when a page goes to a swap is tricky.
 * We need a bit which can be stored in pte _and_ not conflict
 * with swap entry क्रमmat. On x86 bits 1-4 are *not* involved
 * पूर्णांकo swap entry computation, but bit 7 is used क्रम thp migration,
 * so we borrow bit 1 क्रम soft dirty tracking.
 *
 * Please note that this bit must be treated as swap dirty page
 * mark अगर and only अगर the PTE/PMD has present bit clear!
 */
#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
#घोषणा _PAGE_SWP_SOFT_सूचीTY	_PAGE_RW
#अन्यथा
#घोषणा _PAGE_SWP_SOFT_सूचीTY	(_AT(pteval_t, 0))
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_ARCH_USERFAULTFD_WP
#घोषणा _PAGE_UFFD_WP		(_AT(pteval_t, 1) << _PAGE_BIT_UFFD_WP)
#घोषणा _PAGE_SWP_UFFD_WP	_PAGE_USER
#अन्यथा
#घोषणा _PAGE_UFFD_WP		(_AT(pteval_t, 0))
#घोषणा _PAGE_SWP_UFFD_WP	(_AT(pteval_t, 0))
#पूर्ण_अगर

#अगर defined(CONFIG_X86_64) || defined(CONFIG_X86_PAE)
#घोषणा _PAGE_NX	(_AT(pteval_t, 1) << _PAGE_BIT_NX)
#घोषणा _PAGE_DEVMAP	(_AT(u64, 1) << _PAGE_BIT_DEVMAP)
#अन्यथा
#घोषणा _PAGE_NX	(_AT(pteval_t, 0))
#घोषणा _PAGE_DEVMAP	(_AT(pteval_t, 0))
#पूर्ण_अगर

#घोषणा _PAGE_PROTNONE	(_AT(pteval_t, 1) << _PAGE_BIT_PROTNONE)

/*
 * Set of bits not changed in pte_modअगरy.  The pte's
 * protection key is treated like _PAGE_RW, क्रम
 * instance, and is *not* included in this mask since
 * pte_modअगरy() करोes modअगरy it.
 */
#घोषणा _PAGE_CHG_MASK	(PTE_PFN_MASK | _PAGE_PCD | _PAGE_PWT |		\
			 _PAGE_SPECIAL | _PAGE_ACCESSED | _PAGE_सूचीTY |	\
			 _PAGE_SOFT_सूचीTY | _PAGE_DEVMAP | _PAGE_ENC |  \
			 _PAGE_UFFD_WP)
#घोषणा _HPAGE_CHG_MASK (_PAGE_CHG_MASK | _PAGE_PSE)

/*
 * The cache modes defined here are used to translate between pure SW usage
 * and the HW defined cache mode bits and/or PAT entries.
 *
 * The resulting bits क्रम PWT, PCD and PAT should be chosen in a way
 * to have the WB mode at index 0 (all bits clear). This is the शेष
 * right now and likely would अवरोध too much अगर changed.
 */
#अगर_अघोषित __ASSEMBLY__
क्रमागत page_cache_mode अणु
	_PAGE_CACHE_MODE_WB       = 0,
	_PAGE_CACHE_MODE_WC       = 1,
	_PAGE_CACHE_MODE_UC_MINUS = 2,
	_PAGE_CACHE_MODE_UC       = 3,
	_PAGE_CACHE_MODE_WT       = 4,
	_PAGE_CACHE_MODE_WP       = 5,

	_PAGE_CACHE_MODE_NUM      = 8
पूर्ण;
#पूर्ण_अगर

#घोषणा _PAGE_ENC		(_AT(pteval_t, sme_me_mask))

#घोषणा _PAGE_CACHE_MASK	(_PAGE_PWT | _PAGE_PCD | _PAGE_PAT)
#घोषणा _PAGE_LARGE_CACHE_MASK	(_PAGE_PWT | _PAGE_PCD | _PAGE_PAT_LARGE)

#घोषणा _PAGE_NOCACHE		(cachemode2protval(_PAGE_CACHE_MODE_UC))
#घोषणा _PAGE_CACHE_WP		(cachemode2protval(_PAGE_CACHE_MODE_WP))

#घोषणा __PP _PAGE_PRESENT
#घोषणा __RW _PAGE_RW
#घोषणा _USR _PAGE_USER
#घोषणा ___A _PAGE_ACCESSED
#घोषणा ___D _PAGE_सूचीTY
#घोषणा ___G _PAGE_GLOBAL
#घोषणा __NX _PAGE_NX

#घोषणा _ENC _PAGE_ENC
#घोषणा __WP _PAGE_CACHE_WP
#घोषणा __NC _PAGE_NOCACHE
#घोषणा _PSE _PAGE_PSE

#घोषणा pgprot_val(x)		((x).pgprot)
#घोषणा __pgprot(x)		((pgprot_t) अणु (x) पूर्ण )
#घोषणा __pg(x)			__pgprot(x)

#घोषणा PAGE_NONE	     __pg(   0|   0|   0|___A|   0|   0|   0|___G)
#घोषणा PAGE_SHARED	     __pg(__PP|__RW|_USR|___A|__NX|   0|   0|   0)
#घोषणा PAGE_SHARED_EXEC     __pg(__PP|__RW|_USR|___A|   0|   0|   0|   0)
#घोषणा PAGE_COPY_NOEXEC     __pg(__PP|   0|_USR|___A|__NX|   0|   0|   0)
#घोषणा PAGE_COPY_EXEC	     __pg(__PP|   0|_USR|___A|   0|   0|   0|   0)
#घोषणा PAGE_COPY	     __pg(__PP|   0|_USR|___A|__NX|   0|   0|   0)
#घोषणा PAGE_READONLY	     __pg(__PP|   0|_USR|___A|__NX|   0|   0|   0)
#घोषणा PAGE_READONLY_EXEC   __pg(__PP|   0|_USR|___A|   0|   0|   0|   0)

#घोषणा __PAGE_KERNEL		 (__PP|__RW|   0|___A|__NX|___D|   0|___G)
#घोषणा __PAGE_KERNEL_EXEC	 (__PP|__RW|   0|___A|   0|___D|   0|___G)
#घोषणा _KERNPG_TABLE_NOENC	 (__PP|__RW|   0|___A|   0|___D|   0|   0)
#घोषणा _KERNPG_TABLE		 (__PP|__RW|   0|___A|   0|___D|   0|   0| _ENC)
#घोषणा _PAGE_TABLE_NOENC	 (__PP|__RW|_USR|___A|   0|___D|   0|   0)
#घोषणा _PAGE_TABLE		 (__PP|__RW|_USR|___A|   0|___D|   0|   0| _ENC)
#घोषणा __PAGE_KERNEL_RO	 (__PP|   0|   0|___A|__NX|___D|   0|___G)
#घोषणा __PAGE_KERNEL_ROX	 (__PP|   0|   0|___A|   0|___D|   0|___G)
#घोषणा __PAGE_KERNEL_NOCACHE	 (__PP|__RW|   0|___A|__NX|___D|   0|___G| __NC)
#घोषणा __PAGE_KERNEL_VVAR	 (__PP|   0|_USR|___A|__NX|___D|   0|___G)
#घोषणा __PAGE_KERNEL_LARGE	 (__PP|__RW|   0|___A|__NX|___D|_PSE|___G)
#घोषणा __PAGE_KERNEL_LARGE_EXEC (__PP|__RW|   0|___A|   0|___D|_PSE|___G)
#घोषणा __PAGE_KERNEL_WP	 (__PP|__RW|   0|___A|__NX|___D|   0|___G| __WP)


#घोषणा __PAGE_KERNEL_IO		__PAGE_KERNEL
#घोषणा __PAGE_KERNEL_IO_NOCACHE	__PAGE_KERNEL_NOCACHE


#अगर_अघोषित __ASSEMBLY__

#घोषणा __PAGE_KERNEL_ENC	(__PAGE_KERNEL    | _ENC)
#घोषणा __PAGE_KERNEL_ENC_WP	(__PAGE_KERNEL_WP | _ENC)
#घोषणा __PAGE_KERNEL_NOENC	(__PAGE_KERNEL    |    0)
#घोषणा __PAGE_KERNEL_NOENC_WP	(__PAGE_KERNEL_WP |    0)

#घोषणा __pgprot_mask(x)	__pgprot((x) & __शेष_kernel_pte_mask)

#घोषणा PAGE_KERNEL		__pgprot_mask(__PAGE_KERNEL            | _ENC)
#घोषणा PAGE_KERNEL_NOENC	__pgprot_mask(__PAGE_KERNEL            |    0)
#घोषणा PAGE_KERNEL_RO		__pgprot_mask(__PAGE_KERNEL_RO         | _ENC)
#घोषणा PAGE_KERNEL_EXEC	__pgprot_mask(__PAGE_KERNEL_EXEC       | _ENC)
#घोषणा PAGE_KERNEL_EXEC_NOENC	__pgprot_mask(__PAGE_KERNEL_EXEC       |    0)
#घोषणा PAGE_KERNEL_ROX		__pgprot_mask(__PAGE_KERNEL_ROX        | _ENC)
#घोषणा PAGE_KERNEL_NOCACHE	__pgprot_mask(__PAGE_KERNEL_NOCACHE    | _ENC)
#घोषणा PAGE_KERNEL_LARGE	__pgprot_mask(__PAGE_KERNEL_LARGE      | _ENC)
#घोषणा PAGE_KERNEL_LARGE_EXEC	__pgprot_mask(__PAGE_KERNEL_LARGE_EXEC | _ENC)
#घोषणा PAGE_KERNEL_VVAR	__pgprot_mask(__PAGE_KERNEL_VVAR       | _ENC)

#घोषणा PAGE_KERNEL_IO		__pgprot_mask(__PAGE_KERNEL_IO)
#घोषणा PAGE_KERNEL_IO_NOCACHE	__pgprot_mask(__PAGE_KERNEL_IO_NOCACHE)

#पूर्ण_अगर	/* __ASSEMBLY__ */

/*         xwr */
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY
#घोषणा __P100	PAGE_READONLY_EXEC
#घोषणा __P101	PAGE_READONLY_EXEC
#घोषणा __P110	PAGE_COPY_EXEC
#घोषणा __P111	PAGE_COPY_EXEC

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	PAGE_READONLY_EXEC
#घोषणा __S101	PAGE_READONLY_EXEC
#घोषणा __S110	PAGE_SHARED_EXEC
#घोषणा __S111	PAGE_SHARED_EXEC

/*
 * early identity mapping  pte attrib macros.
 */
#अगर_घोषित CONFIG_X86_64
#घोषणा __PAGE_KERNEL_IDENT_LARGE_EXEC	__PAGE_KERNEL_LARGE_EXEC
#अन्यथा
#घोषणा PTE_IDENT_ATTR	 0x003		/* PRESENT+RW */
#घोषणा PDE_IDENT_ATTR	 0x063		/* PRESENT+RW+सूचीTY+ACCESSED */
#घोषणा PGD_IDENT_ATTR	 0x001		/* PRESENT (no other attributes) */
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/pgtable_32_types.h>
#अन्यथा
# include <यंत्र/pgtable_64_types.h>
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>

/* Extracts the PFN from a (pte|pmd|pud|pgd)val_t of a 4KB page */
#घोषणा PTE_PFN_MASK		((pteval_t)PHYSICAL_PAGE_MASK)

/*
 *  Extracts the flags from a (pte|pmd|pud|pgd)val_t
 *  This includes the protection key value.
 */
#घोषणा PTE_FLAGS_MASK		(~PTE_PFN_MASK)

प्रकार काष्ठा pgprot अणु pgprotval_t pgprot; पूर्ण pgprot_t;

प्रकार काष्ठा अणु pgdval_t pgd; पूर्ण pgd_t;

अटल अंतरभूत pgprot_t pgprot_nx(pgprot_t prot)
अणु
	वापस __pgprot(pgprot_val(prot) | _PAGE_NX);
पूर्ण
#घोषणा pgprot_nx pgprot_nx

#अगर_घोषित CONFIG_X86_PAE

/*
 * PHYSICAL_PAGE_MASK might be non-स्थिरant when SME is compiled in, so we can't
 * use it here.
 */

#घोषणा PGD_PAE_PAGE_MASK	((चिन्हित दीर्घ)PAGE_MASK)
#घोषणा PGD_PAE_PHYS_MASK	(((1ULL << __PHYSICAL_MASK_SHIFT)-1) & PGD_PAE_PAGE_MASK)

/*
 * PAE allows Base Address, P, PWT, PCD and AVL bits to be set in PGD entries.
 * All other bits are Reserved MBZ
 */
#घोषणा PGD_ALLOWED_BITS	(PGD_PAE_PHYS_MASK | _PAGE_PRESENT | \
				 _PAGE_PWT | _PAGE_PCD | \
				 _PAGE_SOFTW1 | _PAGE_SOFTW2 | _PAGE_SOFTW3)

#अन्यथा
/* No need to mask any bits क्रम !PAE */
#घोषणा PGD_ALLOWED_BITS	(~0ULL)
#पूर्ण_अगर

अटल अंतरभूत pgd_t native_make_pgd(pgdval_t val)
अणु
	वापस (pgd_t) अणु val & PGD_ALLOWED_BITS पूर्ण;
पूर्ण

अटल अंतरभूत pgdval_t native_pgd_val(pgd_t pgd)
अणु
	वापस pgd.pgd & PGD_ALLOWED_BITS;
पूर्ण

अटल अंतरभूत pgdval_t pgd_flags(pgd_t pgd)
अणु
	वापस native_pgd_val(pgd) & PTE_FLAGS_MASK;
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 4
प्रकार काष्ठा अणु p4dval_t p4d; पूर्ण p4d_t;

अटल अंतरभूत p4d_t native_make_p4d(pudval_t val)
अणु
	वापस (p4d_t) अणु val पूर्ण;
पूर्ण

अटल अंतरभूत p4dval_t native_p4d_val(p4d_t p4d)
अणु
	वापस p4d.p4d;
पूर्ण
#अन्यथा
#समावेश <यंत्र-generic/pgtable-nop4d.h>

अटल अंतरभूत p4d_t native_make_p4d(pudval_t val)
अणु
	वापस (p4d_t) अणु .pgd = native_make_pgd((pgdval_t)val) पूर्ण;
पूर्ण

अटल अंतरभूत p4dval_t native_p4d_val(p4d_t p4d)
अणु
	वापस native_pgd_val(p4d.pgd);
पूर्ण
#पूर्ण_अगर

#अगर CONFIG_PGTABLE_LEVELS > 3
प्रकार काष्ठा अणु pudval_t pud; पूर्ण pud_t;

अटल अंतरभूत pud_t native_make_pud(pmdval_t val)
अणु
	वापस (pud_t) अणु val पूर्ण;
पूर्ण

अटल अंतरभूत pudval_t native_pud_val(pud_t pud)
अणु
	वापस pud.pud;
पूर्ण
#अन्यथा
#समावेश <यंत्र-generic/pgtable-nopud.h>

अटल अंतरभूत pud_t native_make_pud(pudval_t val)
अणु
	वापस (pud_t) अणु .p4d.pgd = native_make_pgd(val) पूर्ण;
पूर्ण

अटल अंतरभूत pudval_t native_pud_val(pud_t pud)
अणु
	वापस native_pgd_val(pud.p4d.pgd);
पूर्ण
#पूर्ण_अगर

#अगर CONFIG_PGTABLE_LEVELS > 2
प्रकार काष्ठा अणु pmdval_t pmd; पूर्ण pmd_t;

अटल अंतरभूत pmd_t native_make_pmd(pmdval_t val)
अणु
	वापस (pmd_t) अणु val पूर्ण;
पूर्ण

अटल अंतरभूत pmdval_t native_pmd_val(pmd_t pmd)
अणु
	वापस pmd.pmd;
पूर्ण
#अन्यथा
#समावेश <यंत्र-generic/pgtable-nopmd.h>

अटल अंतरभूत pmd_t native_make_pmd(pmdval_t val)
अणु
	वापस (pmd_t) अणु .pud.p4d.pgd = native_make_pgd(val) पूर्ण;
पूर्ण

अटल अंतरभूत pmdval_t native_pmd_val(pmd_t pmd)
अणु
	वापस native_pgd_val(pmd.pud.p4d.pgd);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत p4dval_t p4d_pfn_mask(p4d_t p4d)
अणु
	/* No 512 GiB huge pages yet */
	वापस PTE_PFN_MASK;
पूर्ण

अटल अंतरभूत p4dval_t p4d_flags_mask(p4d_t p4d)
अणु
	वापस ~p4d_pfn_mask(p4d);
पूर्ण

अटल अंतरभूत p4dval_t p4d_flags(p4d_t p4d)
अणु
	वापस native_p4d_val(p4d) & p4d_flags_mask(p4d);
पूर्ण

अटल अंतरभूत pudval_t pud_pfn_mask(pud_t pud)
अणु
	अगर (native_pud_val(pud) & _PAGE_PSE)
		वापस PHYSICAL_PUD_PAGE_MASK;
	अन्यथा
		वापस PTE_PFN_MASK;
पूर्ण

अटल अंतरभूत pudval_t pud_flags_mask(pud_t pud)
अणु
	वापस ~pud_pfn_mask(pud);
पूर्ण

अटल अंतरभूत pudval_t pud_flags(pud_t pud)
अणु
	वापस native_pud_val(pud) & pud_flags_mask(pud);
पूर्ण

अटल अंतरभूत pmdval_t pmd_pfn_mask(pmd_t pmd)
अणु
	अगर (native_pmd_val(pmd) & _PAGE_PSE)
		वापस PHYSICAL_PMD_PAGE_MASK;
	अन्यथा
		वापस PTE_PFN_MASK;
पूर्ण

अटल अंतरभूत pmdval_t pmd_flags_mask(pmd_t pmd)
अणु
	वापस ~pmd_pfn_mask(pmd);
पूर्ण

अटल अंतरभूत pmdval_t pmd_flags(pmd_t pmd)
अणु
	वापस native_pmd_val(pmd) & pmd_flags_mask(pmd);
पूर्ण

अटल अंतरभूत pte_t native_make_pte(pteval_t val)
अणु
	वापस (pte_t) अणु .pte = val पूर्ण;
पूर्ण

अटल अंतरभूत pteval_t native_pte_val(pte_t pte)
अणु
	वापस pte.pte;
पूर्ण

अटल अंतरभूत pteval_t pte_flags(pte_t pte)
अणु
	वापस native_pte_val(pte) & PTE_FLAGS_MASK;
पूर्ण

#घोषणा __pte2cm_idx(cb)				\
	((((cb) >> (_PAGE_BIT_PAT - 2)) & 4) |		\
	 (((cb) >> (_PAGE_BIT_PCD - 1)) & 2) |		\
	 (((cb) >> _PAGE_BIT_PWT) & 1))
#घोषणा __cm_idx2pte(i)					\
	((((i) & 4) << (_PAGE_BIT_PAT - 2)) |		\
	 (((i) & 2) << (_PAGE_BIT_PCD - 1)) |		\
	 (((i) & 1) << _PAGE_BIT_PWT))

अचिन्हित दीर्घ cachemode2protval(क्रमागत page_cache_mode pcm);

अटल अंतरभूत pgprotval_t protval_4k_2_large(pgprotval_t val)
अणु
	वापस (val & ~(_PAGE_PAT | _PAGE_PAT_LARGE)) |
		((val & _PAGE_PAT) << (_PAGE_BIT_PAT_LARGE - _PAGE_BIT_PAT));
पूर्ण
अटल अंतरभूत pgprot_t pgprot_4k_2_large(pgprot_t pgprot)
अणु
	वापस __pgprot(protval_4k_2_large(pgprot_val(pgprot)));
पूर्ण
अटल अंतरभूत pgprotval_t protval_large_2_4k(pgprotval_t val)
अणु
	वापस (val & ~(_PAGE_PAT | _PAGE_PAT_LARGE)) |
		((val & _PAGE_PAT_LARGE) >>
		 (_PAGE_BIT_PAT_LARGE - _PAGE_BIT_PAT));
पूर्ण
अटल अंतरभूत pgprot_t pgprot_large_2_4k(pgprot_t pgprot)
अणु
	वापस __pgprot(protval_large_2_4k(pgprot_val(pgprot)));
पूर्ण


प्रकार काष्ठा page *pgtable_t;

बाह्य pteval_t __supported_pte_mask;
बाह्य pteval_t __शेष_kernel_pte_mask;
बाह्य व्योम set_nx(व्योम);
बाह्य पूर्णांक nx_enabled;

#घोषणा pgprot_ग_लिखोcombine	pgprot_ग_लिखोcombine
बाह्य pgprot_t pgprot_ग_लिखोcombine(pgprot_t prot);

#घोषणा pgprot_ग_लिखोthrough	pgprot_ग_लिखोthrough
बाह्य pgprot_t pgprot_ग_लिखोthrough(pgprot_t prot);

/* Indicate that x86 has its own track and untrack pfn vma functions */
#घोषणा __HAVE_PFNMAP_TRACKING

#घोषणा __HAVE_PHYS_MEM_ACCESS_PROT
काष्ठा file;
pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
                              अचिन्हित दीर्घ size, pgprot_t vma_prot);

/* Install a pte क्रम a particular vaddr in kernel space. */
व्योम set_pte_vaddr(अचिन्हित दीर्घ vaddr, pte_t pte);

#अगर_घोषित CONFIG_X86_32
बाह्य व्योम native_pagetable_init(व्योम);
#अन्यथा
#घोषणा native_pagetable_init        paging_init
#पूर्ण_अगर

काष्ठा seq_file;
बाह्य व्योम arch_report_meminfo(काष्ठा seq_file *m);

क्रमागत pg_level अणु
	PG_LEVEL_NONE,
	PG_LEVEL_4K,
	PG_LEVEL_2M,
	PG_LEVEL_1G,
	PG_LEVEL_512G,
	PG_LEVEL_NUM
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
बाह्य व्योम update_page_count(पूर्णांक level, अचिन्हित दीर्घ pages);
#अन्यथा
अटल अंतरभूत व्योम update_page_count(पूर्णांक level, अचिन्हित दीर्घ pages) अणु पूर्ण
#पूर्ण_अगर

/*
 * Helper function that वापसs the kernel pagetable entry controlling
 * the भव address 'address'. शून्य means no pagetable entry present.
 * NOTE: the वापस type is pte_t but अगर the pmd is PSE then we वापस it
 * as a pte too.
 */
बाह्य pte_t *lookup_address(अचिन्हित दीर्घ address, अचिन्हित पूर्णांक *level);
बाह्य pte_t *lookup_address_in_pgd(pgd_t *pgd, अचिन्हित दीर्घ address,
				    अचिन्हित पूर्णांक *level);

काष्ठा mm_काष्ठा;
बाह्य pte_t *lookup_address_in_mm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
				   अचिन्हित पूर्णांक *level);
बाह्य pmd_t *lookup_pmd_address(अचिन्हित दीर्घ address);
बाह्य phys_addr_t slow_virt_to_phys(व्योम *__address);
बाह्य पूर्णांक __init kernel_map_pages_in_pgd(pgd_t *pgd, u64 pfn,
					  अचिन्हित दीर्घ address,
					  अचिन्हित numpages,
					  अचिन्हित दीर्घ page_flags);
बाह्य पूर्णांक __init kernel_unmap_pages_in_pgd(pgd_t *pgd, अचिन्हित दीर्घ address,
					    अचिन्हित दीर्घ numpages);
#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_PGTABLE_DEFS_H */
