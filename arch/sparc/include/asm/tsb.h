<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_TSB_H
#घोषणा _SPARC64_TSB_H

/* The sparc64 TSB is similar to the घातerpc hashtables.  It's a
 * घातer-of-2 sized table of TAG/PTE pairs.  The cpu precomputes
 * poपूर्णांकers पूर्णांकo this table क्रम 8K and 64K page sizes, and also a
 * comparison TAG based upon the भव address and context which
 * faults.
 *
 * TLB miss trap handler software करोes the actual lookup via something
 * of the क्रमm:
 *
 * 	ldxa		[%g0] ASI_अणुD,Iपूर्णMMU_TSB_8KB_PTR, %g1
 * 	ldxa		[%g0] ASI_अणुD,Iपूर्णMMU, %g6
 *	sllx		%g6, 22, %g6
 *	srlx		%g6, 22, %g6
 * 	ldda		[%g1] ASI_NUCLEUS_QUAD_LDD, %g4
 * 	cmp		%g4, %g6
 * 	bne,pn	%xcc, tsb_miss_अणुd,iपूर्णtlb
 * 	 mov		FAULT_CODE_अणुD,Iपूर्णTLB, %g3
 * 	stxa		%g5, [%g0] ASI_अणुD,Iपूर्णTLB_DATA_IN
 * 	retry
 *
 *
 * Each 16-byte slot of the TSB is the 8-byte tag and then the 8-byte
 * PTE.  The TAG is of the same layout as the TLB TAG TARGET mmu
 * रेजिस्टर which is:
 *
 * -------------------------------------------------
 * |  -  |  CONTEXT |  -  |    VADDR bits 63:22    |
 * -------------------------------------------------
 *  63 61 60      48 47 42 41                     0
 *
 * But actually, since we use per-mm TSB's, we zero out the CONTEXT
 * field.
 *
 * Like the घातerpc hashtables we need to use locking in order to
 * synchronize जबतक we update the entries.  PTE updates need locking
 * as well.
 *
 * We need to carefully choose a lock bits क्रम the TSB entry.  We
 * choose to use bit 47 in the tag.  Also, since we never map anything
 * at page zero in context zero, we use zero as an invalid tag entry.
 * When the lock bit is set, this क्रमces a tag comparison failure.
 */

#घोषणा TSB_TAG_LOCK_BIT	47
#घोषणा TSB_TAG_LOCK_HIGH	(1 << (TSB_TAG_LOCK_BIT - 32))

#घोषणा TSB_TAG_INVALID_BIT	46
#घोषणा TSB_TAG_INVALID_HIGH	(1 << (TSB_TAG_INVALID_BIT - 32))

/* Some cpus support physical address quad loads.  We want to use
 * those अगर possible so we करोn't need to hard-lock the TSB mapping
 * पूर्णांकo the TLB.  We encode some inकाष्ठाion patching in order to
 * support this.
 *
 * The kernel TSB is locked पूर्णांकo the TLB by virtue of being in the
 * kernel image, so we करोn't play these games क्रम swapper_tsb access.
 */
#अगर_अघोषित __ASSEMBLY__
काष्ठा tsb_ldquad_phys_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	sun4u_insn;
	अचिन्हित पूर्णांक	sun4v_insn;
पूर्ण;
बाह्य काष्ठा tsb_ldquad_phys_patch_entry __tsb_ldquad_phys_patch,
	__tsb_ldquad_phys_patch_end;

काष्ठा tsb_phys_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	insn;
पूर्ण;
बाह्य काष्ठा tsb_phys_patch_entry __tsb_phys_patch, __tsb_phys_patch_end;
#पूर्ण_अगर
#घोषणा TSB_LOAD_QUAD(TSB, REG)	\
661:	ldda		[TSB] ASI_NUCLEUS_QUAD_LDD, REG; \
	.section	.tsb_ldquad_phys_patch, "ax"; \
	.word		661b; \
	ldda		[TSB] ASI_QUAD_LDD_PHYS, REG; \
	ldda		[TSB] ASI_QUAD_LDD_PHYS_4V, REG; \
	.previous

#घोषणा TSB_LOAD_TAG_HIGH(TSB, REG) \
661:	lduwa		[TSB] ASI_N, REG; \
	.section	.tsb_phys_patch, "ax"; \
	.word		661b; \
	lduwa		[TSB] ASI_PHYS_USE_EC, REG; \
	.previous

#घोषणा TSB_LOAD_TAG(TSB, REG) \
661:	ldxa		[TSB] ASI_N, REG; \
	.section	.tsb_phys_patch, "ax"; \
	.word		661b; \
	ldxa		[TSB] ASI_PHYS_USE_EC, REG; \
	.previous

#घोषणा TSB_CAS_TAG_HIGH(TSB, REG1, REG2) \
661:	casa		[TSB] ASI_N, REG1, REG2; \
	.section	.tsb_phys_patch, "ax"; \
	.word		661b; \
	casa		[TSB] ASI_PHYS_USE_EC, REG1, REG2; \
	.previous

#घोषणा TSB_CAS_TAG(TSB, REG1, REG2) \
661:	casxa		[TSB] ASI_N, REG1, REG2; \
	.section	.tsb_phys_patch, "ax"; \
	.word		661b; \
	casxa		[TSB] ASI_PHYS_USE_EC, REG1, REG2; \
	.previous

#घोषणा TSB_STORE(ADDR, VAL) \
661:	stxa		VAL, [ADDR] ASI_N; \
	.section	.tsb_phys_patch, "ax"; \
	.word		661b; \
	stxa		VAL, [ADDR] ASI_PHYS_USE_EC; \
	.previous

#घोषणा TSB_LOCK_TAG(TSB, REG1, REG2)	\
99:	TSB_LOAD_TAG_HIGH(TSB, REG1);	\
	sethi	%hi(TSB_TAG_LOCK_HIGH), REG2;\
	andcc	REG1, REG2, %g0;	\
	bne,pn	%icc, 99b;		\
	 nop;				\
	TSB_CAS_TAG_HIGH(TSB, REG1, REG2);	\
	cmp	REG1, REG2;		\
	bne,pn	%icc, 99b;		\
	 nop;				\

#घोषणा TSB_WRITE(TSB, TTE, TAG) \
	add	TSB, 0x8, TSB;   \
	TSB_STORE(TSB, TTE);     \
	sub	TSB, 0x8, TSB;   \
	TSB_STORE(TSB, TAG);

	/* Do a kernel page table walk.  Leaves valid PTE value in
	 * REG1.  Jumps to FAIL_LABEL on early page table walk
	 * termination.  VADDR will not be clobbered, but REG2 will.
	 *
	 * There are two masks we must apply to propagate bits from
	 * the भव address पूर्णांकo the PTE physical address field
	 * when dealing with huge pages.  This is because the page
	 * table boundaries करो not match the huge page size(s) the
	 * hardware supports.
	 *
	 * In these हालs we propagate the bits that are below the
	 * page table level where we saw the huge page mapping, but
	 * are still within the relevant physical bits क्रम the huge
	 * page size in question.  So क्रम PMD mappings (which fall on
	 * bit 23, क्रम 8MB per PMD) we must propagate bit 22 क्रम a
	 * 4MB huge page.  For huge PUDs (which fall on bit 33, क्रम
	 * 8GB per PUD), we have to accommodate 256MB and 2GB huge
	 * pages.  So क्रम those we propagate bits 32 to 28.
	 */
#घोषणा KERN_PGTABLE_WALK(VADDR, REG1, REG2, FAIL_LABEL)	\
	sethi		%hi(swapper_pg_dir), REG1; \
	or		REG1, %lo(swapper_pg_dir), REG1; \
	sllx		VADDR, 64 - (PGसूची_SHIFT + PGसूची_BITS), REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	ldx		[REG1 + REG2], REG1; \
	brz,pn		REG1, FAIL_LABEL; \
	 sllx		VADDR, 64 - (PUD_SHIFT + PUD_BITS), REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	ldxa		[REG1 + REG2] ASI_PHYS_USE_EC, REG1; \
	brz,pn		REG1, FAIL_LABEL; \
	sethi		%uhi(_PAGE_PUD_HUGE), REG2; \
	brz,pn		REG1, FAIL_LABEL; \
	 sllx		REG2, 32, REG2; \
	andcc		REG1, REG2, %g0; \
	sethi		%hi(0xf8000000), REG2; \
	bne,pt		%xcc, 697f; \
	 sllx		REG2, 1, REG2; \
	sllx		VADDR, 64 - (PMD_SHIFT + PMD_BITS), REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	ldxa		[REG1 + REG2] ASI_PHYS_USE_EC, REG1; \
	sethi		%uhi(_PAGE_PMD_HUGE), REG2; \
	brz,pn		REG1, FAIL_LABEL; \
	 sllx		REG2, 32, REG2; \
	andcc		REG1, REG2, %g0; \
	be,pn		%xcc, 698f; \
	 sethi		%hi(0x400000), REG2; \
697:	brgez,pn	REG1, FAIL_LABEL; \
	 andn		REG1, REG2, REG1; \
	and		VADDR, REG2, REG2; \
	ba,pt		%xcc, 699f; \
	 or		REG1, REG2, REG1; \
698:	sllx		VADDR, 64 - PMD_SHIFT, REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	ldxa		[REG1 + REG2] ASI_PHYS_USE_EC, REG1; \
	brgez,pn	REG1, FAIL_LABEL; \
	 nop; \
699:

	/* PUD has been loaded पूर्णांकo REG1, पूर्णांकerpret the value, seeing
	 * अगर it is a HUGE PUD or a normal one.  If it is not valid
	 * then jump to FAIL_LABEL.  If it is a HUGE PUD, and it
	 * translates to a valid PTE, branch to PTE_LABEL.
	 *
	 * We have to propagate bits [32:22] from the भव address
	 * to resolve at 4M granularity.
	 */
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
#घोषणा USER_PGTABLE_CHECK_PUD_HUGE(VADDR, REG1, REG2, FAIL_LABEL, PTE_LABEL) \
700:	ba 700f;					\
	 nop;						\
	.section	.pud_huge_patch, "ax";		\
	.word		700b;				\
	nop;						\
	.previous;					\
	brz,pn		REG1, FAIL_LABEL;		\
	 sethi		%uhi(_PAGE_PUD_HUGE), REG2;	\
	sllx		REG2, 32, REG2;			\
	andcc		REG1, REG2, %g0;		\
	be,pt		%xcc, 700f;			\
	 sethi		%hi(0xffe00000), REG2;		\
	sllx		REG2, 1, REG2;			\
	brgez,pn	REG1, FAIL_LABEL;		\
	 andn		REG1, REG2, REG1;		\
	and		VADDR, REG2, REG2;		\
	brlz,pt		REG1, PTE_LABEL;		\
	 or		REG1, REG2, REG1;		\
700:
#अन्यथा
#घोषणा USER_PGTABLE_CHECK_PUD_HUGE(VADDR, REG1, REG2, FAIL_LABEL, PTE_LABEL) \
	brz,pn		REG1, FAIL_LABEL; \
	 nop;
#पूर्ण_अगर

	/* PMD has been loaded पूर्णांकo REG1, पूर्णांकerpret the value, seeing
	 * अगर it is a HUGE PMD or a normal one.  If it is not valid
	 * then jump to FAIL_LABEL.  If it is a HUGE PMD, and it
	 * translates to a valid PTE, branch to PTE_LABEL.
	 *
	 * We have to propagate the 4MB bit of the भव address
	 * because we are fabricating 8MB pages using 4MB hw pages.
	 */
#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
#घोषणा USER_PGTABLE_CHECK_PMD_HUGE(VADDR, REG1, REG2, FAIL_LABEL, PTE_LABEL) \
	brz,pn		REG1, FAIL_LABEL;		\
	 sethi		%uhi(_PAGE_PMD_HUGE), REG2;	\
	sllx		REG2, 32, REG2;			\
	andcc		REG1, REG2, %g0;		\
	be,pt		%xcc, 700f;			\
	 sethi		%hi(4 * 1024 * 1024), REG2;	\
	brgez,pn	REG1, FAIL_LABEL;		\
	 andn		REG1, REG2, REG1;		\
	and		VADDR, REG2, REG2;		\
	brlz,pt		REG1, PTE_LABEL;		\
	 or		REG1, REG2, REG1;		\
700:
#अन्यथा
#घोषणा USER_PGTABLE_CHECK_PMD_HUGE(VADDR, REG1, REG2, FAIL_LABEL, PTE_LABEL) \
	brz,pn		REG1, FAIL_LABEL; \
	 nop;
#पूर्ण_अगर

	/* Do a user page table walk in MMU globals.  Leaves final,
	 * valid, PTE value in REG1.  Jumps to FAIL_LABEL on early
	 * page table walk termination or अगर the PTE is not valid.
	 *
	 * Physical base of page tables is in PHYS_PGD which will not
	 * be modअगरied.
	 *
	 * VADDR will not be clobbered, but REG1 and REG2 will.
	 */
#घोषणा USER_PGTABLE_WALK_TL1(VADDR, PHYS_PGD, REG1, REG2, FAIL_LABEL)	\
	sllx		VADDR, 64 - (PGसूची_SHIFT + PGसूची_BITS), REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	ldxa		[PHYS_PGD + REG2] ASI_PHYS_USE_EC, REG1; \
	brz,pn		REG1, FAIL_LABEL; \
	 sllx		VADDR, 64 - (PUD_SHIFT + PUD_BITS), REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	ldxa		[REG1 + REG2] ASI_PHYS_USE_EC, REG1; \
	USER_PGTABLE_CHECK_PUD_HUGE(VADDR, REG1, REG2, FAIL_LABEL, 800f) \
	brz,pn		REG1, FAIL_LABEL; \
	 sllx		VADDR, 64 - (PMD_SHIFT + PMD_BITS), REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	ldxa		[REG1 + REG2] ASI_PHYS_USE_EC, REG1; \
	USER_PGTABLE_CHECK_PMD_HUGE(VADDR, REG1, REG2, FAIL_LABEL, 800f) \
	sllx		VADDR, 64 - PMD_SHIFT, REG2; \
	srlx		REG2, 64 - PAGE_SHIFT, REG2; \
	andn		REG2, 0x7, REG2; \
	add		REG1, REG2, REG1; \
	ldxa		[REG1] ASI_PHYS_USE_EC, REG1; \
	brgez,pn	REG1, FAIL_LABEL; \
	 nop; \
800:

/* Lookup a OBP mapping on VADDR in the prom_trans[] table at TL>0.
 * If no entry is found, FAIL_LABEL will be branched to.  On success
 * the resulting PTE value will be left in REG1.  VADDR is preserved
 * by this routine.
 */
#घोषणा OBP_TRANS_LOOKUP(VADDR, REG1, REG2, REG3, FAIL_LABEL) \
	sethi		%hi(prom_trans), REG1; \
	or		REG1, %lo(prom_trans), REG1; \
97:	ldx		[REG1 + 0x00], REG2; \
	brz,pn		REG2, FAIL_LABEL; \
	 nop; \
	ldx		[REG1 + 0x08], REG3; \
	add		REG2, REG3, REG3; \
	cmp		REG2, VADDR; \
	bgu,pt		%xcc, 98f; \
	 cmp		VADDR, REG3; \
	bgeu,pt		%xcc, 98f; \
	 ldx		[REG1 + 0x10], REG3; \
	sub		VADDR, REG2, REG2; \
	ba,pt		%xcc, 99f; \
	 add		REG3, REG2, REG1; \
98:	ba,pt		%xcc, 97b; \
	 add		REG1, (3 * 8), REG1; \
99:

	/* We use a 32K TSB क्रम the whole kernel, this allows to
	 * handle about 16MB of modules and vदो_स्मृति mappings without
	 * incurring many hash conflicts.
	 */
#घोषणा KERNEL_TSB_SIZE_BYTES	(32 * 1024)
#घोषणा KERNEL_TSB_NENTRIES	\
	(KERNEL_TSB_SIZE_BYTES / 16)
#घोषणा KERNEL_TSB4M_NENTRIES	4096

	/* Do a kernel TSB lookup at tl>0 on VADDR+TAG, branch to OK_LABEL
	 * on TSB hit.  REG1, REG2, REG3, and REG4 are used as temporaries
	 * and the found TTE will be left in REG1.  REG3 and REG4 must
	 * be an even/odd pair of रेजिस्टरs.
	 *
	 * VADDR and TAG will be preserved and not clobbered by this macro.
	 */
#घोषणा KERN_TSB_LOOKUP_TL1(VADDR, TAG, REG1, REG2, REG3, REG4, OK_LABEL) \
661:	sethi		%uhi(swapper_tsb), REG1; \
	sethi		%hi(swapper_tsb), REG2; \
	or		REG1, %ulo(swapper_tsb), REG1; \
	or		REG2, %lo(swapper_tsb), REG2; \
	.section	.swapper_tsb_phys_patch, "ax"; \
	.word		661b; \
	.previous; \
	sllx		REG1, 32, REG1; \
	or		REG1, REG2, REG1; \
	srlx		VADDR, PAGE_SHIFT, REG2; \
	and		REG2, (KERNEL_TSB_NENTRIES - 1), REG2; \
	sllx		REG2, 4, REG2; \
	add		REG1, REG2, REG2; \
	TSB_LOAD_QUAD(REG2, REG3); \
	cmp		REG3, TAG; \
	be,a,pt		%xcc, OK_LABEL; \
	 mov		REG4, REG1;

#अगर_अघोषित CONFIG_DEBUG_PAGEALLOC
	/* This version uses a trick, the TAG is alपढ़ोy (VADDR >> 22) so
	 * we can make use of that क्रम the index computation.
	 */
#घोषणा KERN_TSB4M_LOOKUP_TL1(TAG, REG1, REG2, REG3, REG4, OK_LABEL) \
661:	sethi		%uhi(swapper_4m_tsb), REG1; \
	sethi		%hi(swapper_4m_tsb), REG2; \
	or		REG1, %ulo(swapper_4m_tsb), REG1; \
	or		REG2, %lo(swapper_4m_tsb), REG2; \
	.section	.swapper_4m_tsb_phys_patch, "ax"; \
	.word		661b; \
	.previous; \
	sllx		REG1, 32, REG1; \
	or		REG1, REG2, REG1; \
	and		TAG, (KERNEL_TSB4M_NENTRIES - 1), REG2; \
	sllx		REG2, 4, REG2; \
	add		REG1, REG2, REG2; \
	TSB_LOAD_QUAD(REG2, REG3); \
	cmp		REG3, TAG; \
	be,a,pt		%xcc, OK_LABEL; \
	 mov		REG4, REG1;
#पूर्ण_अगर

#पूर्ण_अगर /* !(_SPARC64_TSB_H) */
