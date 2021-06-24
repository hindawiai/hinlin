<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_32_PTE_8xx_H
#घोषणा _ASM_POWERPC_NOHASH_32_PTE_8xx_H
#अगर_घोषित __KERNEL__

/*
 * The PowerPC MPC8xx uses a TLB with hardware assisted, software tablewalk.
 * We also use the two level tables, but we can put the real bits in them
 * needed क्रम the TLB and tablewalk.  These definitions require Mx_CTR.PPM = 0,
 * Mx_CTR.PPCS = 0, and MD_CTR.TWAM = 1.  The level 2 descriptor has
 * additional page protection (when Mx_CTR.PPCS = 1) that allows TLB hit
 * based upon user/super access.  The TLB करोes not have accessed nor ग_लिखो
 * protect.  We assume that अगर the TLB get loaded with an entry it is
 * accessed, and overload the changed bit क्रम ग_लिखो protect.  We use
 * two bits in the software pte that are supposed to be set to zero in
 * the TLB entry (24 and 25) क्रम these indicators.  Although the level 1
 * descriptor contains the guarded and ग_लिखोthrough/copyback bits, we can
 * set these at the page level since they get copied from the Mx_TWC
 * रेजिस्टर when the TLB entry is loaded.  We will use bit 27 क्रम guard, since
 * that is where it exists in the MD_TWC, and bit 26 क्रम ग_लिखोthrough.
 * These will get masked from the level 2 descriptor at TLB load समय, and
 * copied to the MD_TWC beक्रमe it माला_लो loaded.
 * Large page sizes added.  We currently support two sizes, 4K and 8M.
 * This also allows a TLB hander optimization because we can directly
 * load the PMD पूर्णांकo MD_TWC.  The 8M pages are only used क्रम kernel
 * mapping of well known areas.  The PMD (PGD) entries contain control
 * flags in addition to the address, so care must be taken that the
 * software no दीर्घer assumes these are only poपूर्णांकers.
 */

/* Definitions क्रम 8xx embedded chips. */
#घोषणा _PAGE_PRESENT	0x0001	/* V: Page is valid */
#घोषणा _PAGE_NO_CACHE	0x0002	/* CI: cache inhibit */
#घोषणा _PAGE_SH	0x0004	/* SH: No ASID (context) compare */
#घोषणा _PAGE_SPS	0x0008	/* SPS: Small Page Size (1 अगर 16k, 512k or 8M)*/
#घोषणा _PAGE_सूचीTY	0x0100	/* C: page changed */

/* These 4 software bits must be masked out when the L2 entry is loaded
 * पूर्णांकo the TLB.
 */
#घोषणा _PAGE_GUARDED	0x0010	/* Copied to L1 G entry in DTLB */
#घोषणा _PAGE_ACCESSED	0x0020	/* Copied to L1 APG 1 entry in I/DTLB */
#घोषणा _PAGE_EXEC	0x0040	/* Copied to PP (bit 21) in ITLB */
#घोषणा _PAGE_SPECIAL	0x0080	/* SW entry */

#घोषणा _PAGE_NA	0x0200	/* Supervisor NA, User no access */
#घोषणा _PAGE_RO	0x0600	/* Supervisor RO, User no access */

#घोषणा _PAGE_HUGE	0x0800	/* Copied to L1 PS bit 29 */

/* cache related flags non existing on 8xx */
#घोषणा _PAGE_COHERENT	0
#घोषणा _PAGE_WRITETHRU	0

#घोषणा _PAGE_KERNEL_RO		(_PAGE_SH | _PAGE_RO)
#घोषणा _PAGE_KERNEL_ROX	(_PAGE_SH | _PAGE_RO | _PAGE_EXEC)
#घोषणा _PAGE_KERNEL_RW		(_PAGE_SH | _PAGE_सूचीTY)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_SH | _PAGE_सूचीTY | _PAGE_EXEC)

#घोषणा _PMD_PRESENT	0x0001
#घोषणा _PMD_PRESENT_MASK	_PMD_PRESENT
#घोषणा _PMD_BAD	0x0f90
#घोषणा _PMD_PAGE_MASK	0x000c
#घोषणा _PMD_PAGE_8M	0x000c
#घोषणा _PMD_PAGE_512K	0x0004
#घोषणा _PMD_ACCESSED	0x0020	/* APG 1 */
#घोषणा _PMD_USER	0x0040	/* APG 2 */

#घोषणा _PTE_NONE_MASK	0

#अगर_घोषित CONFIG_PPC_16K_PAGES
#घोषणा _PAGE_PSIZE	_PAGE_SPS
#अन्यथा
#घोषणा _PAGE_PSIZE		0
#पूर्ण_अगर

#घोषणा _PAGE_BASE_NC	(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_PSIZE)
#घोषणा _PAGE_BASE	(_PAGE_BASE_NC)

/* Permission masks used to generate the __P and __S table */
#घोषणा PAGE_NONE	__pgprot(_PAGE_BASE | _PAGE_NA)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_BASE)
#घोषणा PAGE_SHARED_X	__pgprot(_PAGE_BASE | _PAGE_EXEC)
#घोषणा PAGE_COPY	__pgprot(_PAGE_BASE | _PAGE_RO)
#घोषणा PAGE_COPY_X	__pgprot(_PAGE_BASE | _PAGE_RO | _PAGE_EXEC)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_BASE | _PAGE_RO)
#घोषणा PAGE_READONLY_X	__pgprot(_PAGE_BASE | _PAGE_RO | _PAGE_EXEC)

#अगर_अघोषित __ASSEMBLY__
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_RO);
पूर्ण

#घोषणा pte_wrprotect pte_wrprotect

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस !(pte_val(pte) & _PAGE_RO);
पूर्ण

#घोषणा pte_ग_लिखो pte_ग_लिखो

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_RO);
पूर्ण

#घोषणा pte_mkग_लिखो pte_mkग_लिखो

अटल अंतरभूत bool pte_user(pte_t pte)
अणु
	वापस !(pte_val(pte) & _PAGE_SH);
पूर्ण

#घोषणा pte_user pte_user

अटल अंतरभूत pte_t pte_mkprivileged(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_SH);
पूर्ण

#घोषणा pte_mkprivileged pte_mkprivileged

अटल अंतरभूत pte_t pte_mkuser(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~_PAGE_SH);
पूर्ण

#घोषणा pte_mkuser pte_mkuser

अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_SPS | _PAGE_HUGE);
पूर्ण

#घोषणा pte_mkhuge pte_mkhuge

अटल अंतरभूत अचिन्हित दीर्घ pgd_leaf_size(pgd_t pgd)
अणु
	अगर (pgd_val(pgd) & _PMD_PAGE_8M)
		वापस SZ_8M;
	वापस SZ_4M;
पूर्ण

#घोषणा pgd_leaf_size pgd_leaf_size

अटल अंतरभूत अचिन्हित दीर्घ pte_leaf_size(pte_t pte)
अणु
	pte_basic_t val = pte_val(pte);

	अगर (val & _PAGE_HUGE)
		वापस SZ_512K;
	अगर (val & _PAGE_SPS)
		वापस SZ_16K;
	वापस SZ_4K;
पूर्ण

#घोषणा pte_leaf_size pte_leaf_size

#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /*  _ASM_POWERPC_NOHASH_32_PTE_8xx_H */
