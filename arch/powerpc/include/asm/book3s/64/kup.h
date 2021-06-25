<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_KUP_H
#घोषणा _ASM_POWERPC_BOOK3S_64_KUP_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/reg.h>

#घोषणा AMR_KUAP_BLOCK_READ	UL(0x5455555555555555)
#घोषणा AMR_KUAP_BLOCK_WRITE	UL(0xa8aaaaaaaaaaaaaa)
#घोषणा AMR_KUEP_BLOCKED	UL(0x5455555555555555)
#घोषणा AMR_KUAP_BLOCKED	(AMR_KUAP_BLOCK_READ | AMR_KUAP_BLOCK_WRITE)

#अगर_घोषित __ASSEMBLY__

.macro kuap_user_restore gpr1, gpr2
#अगर defined(CONFIG_PPC_PKEY)
	BEGIN_MMU_FTR_SECTION_NESTED(67)
	b	100f  // skip_restore_amr
	END_MMU_FTR_SECTION_NESTED_IFCLR(MMU_FTR_PKEY, 67)
	/*
	 * AMR and IAMR are going to be dअगरferent when
	 * वापसing to userspace.
	 */
	ld	\gpr1, STACK_REGS_AMR(r1)

	/*
	 * If kuap feature is not enabled, करो the mtspr
	 * only अगर AMR value is dअगरferent.
	 */
	BEGIN_MMU_FTR_SECTION_NESTED(68)
	mfspr	\gpr2, SPRN_AMR
	cmpd	\gpr1, \gpr2
	beq	99f
	END_MMU_FTR_SECTION_NESTED_IFCLR(MMU_FTR_BOOK3S_KUAP, 68)

	isync
	mtspr	SPRN_AMR, \gpr1
99:
	/*
	 * Restore IAMR only when वापसing to userspace
	 */
	ld	\gpr1, STACK_REGS_IAMR(r1)

	/*
	 * If kuep feature is not enabled, करो the mtspr
	 * only अगर IAMR value is dअगरferent.
	 */
	BEGIN_MMU_FTR_SECTION_NESTED(69)
	mfspr	\gpr2, SPRN_IAMR
	cmpd	\gpr1, \gpr2
	beq	100f
	END_MMU_FTR_SECTION_NESTED_IFCLR(MMU_FTR_BOOK3S_KUEP, 69)

	isync
	mtspr	SPRN_IAMR, \gpr1

100: //skip_restore_amr
	/* No isync required, see kuap_user_restore() */
#पूर्ण_अगर
.endm

.macro kuap_kernel_restore gpr1, gpr2
#अगर defined(CONFIG_PPC_PKEY)

	BEGIN_MMU_FTR_SECTION_NESTED(67)
	/*
	 * AMR is going to be mostly the same since we are
	 * वापसing to the kernel. Compare and करो a mtspr.
	 */
	ld	\gpr2, STACK_REGS_AMR(r1)
	mfspr	\gpr1, SPRN_AMR
	cmpd	\gpr1, \gpr2
	beq	100f
	isync
	mtspr	SPRN_AMR, \gpr2
	/*
	 * No isync required, see kuap_restore_amr()
	 * No need to restore IAMR when वापसing to kernel space.
	 */
100:
	END_MMU_FTR_SECTION_NESTED_IFSET(MMU_FTR_BOOK3S_KUAP, 67)
#पूर्ण_अगर
.endm

#अगर_घोषित CONFIG_PPC_KUAP
.macro kuap_check_amr gpr1, gpr2
#अगर_घोषित CONFIG_PPC_KUAP_DEBUG
	BEGIN_MMU_FTR_SECTION_NESTED(67)
	mfspr	\gpr1, SPRN_AMR
	/* Prevent access to userspace using any key values */
	LOAD_REG_IMMEDIATE(\gpr2, AMR_KUAP_BLOCKED)
999:	tdne	\gpr1, \gpr2
	EMIT_BUG_ENTRY 999b, __खाता__, __LINE__, (BUGFLAG_WARNING | BUGFLAG_ONCE)
	END_MMU_FTR_SECTION_NESTED_IFSET(MMU_FTR_BOOK3S_KUAP, 67)
#पूर्ण_अगर
.endm
#पूर्ण_अगर

/*
 *	अगर (pkey) अणु
 *
 *		save AMR -> stack;
 *		अगर (kuap) अणु
 *			अगर (AMR != BLOCKED)
 *				KUAP_BLOCKED -> AMR;
 *		पूर्ण
 *		अगर (from_user) अणु
 *			save IAMR -> stack;
 *			अगर (kuep) अणु
 *				KUEP_BLOCKED ->IAMR
 *			पूर्ण
 *		पूर्ण
 *		वापस;
 *	पूर्ण
 *
 *	अगर (kuap) अणु
 *		अगर (from_kernel) अणु
 *			save AMR -> stack;
 *			अगर (AMR != BLOCKED)
 *				KUAP_BLOCKED -> AMR;
 *		पूर्ण
 *
 *	पूर्ण
 */
.macro kuap_save_amr_and_lock gpr1, gpr2, use_cr, msr_pr_cr
#अगर defined(CONFIG_PPC_PKEY)

	/*
	 * अगर both pkey and kuap is disabled, nothing to करो
	 */
	BEGIN_MMU_FTR_SECTION_NESTED(68)
	b	100f  // skip_save_amr
	END_MMU_FTR_SECTION_NESTED_IFCLR(MMU_FTR_PKEY | MMU_FTR_BOOK3S_KUAP, 68)

	/*
	 * अगर pkey is disabled and we are entering from userspace
	 * करोn't करो anything.
	 */
	BEGIN_MMU_FTR_SECTION_NESTED(67)
	.अगरnb \msr_pr_cr
	/*
	 * Without pkey we are not changing AMR outside the kernel
	 * hence skip this completely.
	 */
	bne	\msr_pr_cr, 100f  // from userspace
	.endअगर
        END_MMU_FTR_SECTION_NESTED_IFCLR(MMU_FTR_PKEY, 67)

	/*
	 * pkey is enabled or pkey is disabled but entering from kernel
	 */
	mfspr	\gpr1, SPRN_AMR
	std	\gpr1, STACK_REGS_AMR(r1)

	/*
	 * update kernel AMR with AMR_KUAP_BLOCKED only
	 * अगर KUAP feature is enabled
	 */
	BEGIN_MMU_FTR_SECTION_NESTED(69)
	LOAD_REG_IMMEDIATE(\gpr2, AMR_KUAP_BLOCKED)
	cmpd	\use_cr, \gpr1, \gpr2
	beq	\use_cr, 102f
	/*
	 * We करोn't isync here because we very recently entered via an पूर्णांकerrupt
	 */
	mtspr	SPRN_AMR, \gpr2
	isync
102:
	END_MMU_FTR_SECTION_NESTED_IFSET(MMU_FTR_BOOK3S_KUAP, 69)

	/*
	 * अगर entering from kernel we करोn't need save IAMR
	 */
	.अगरnb \msr_pr_cr
	beq	\msr_pr_cr, 100f // from kernel space
	mfspr	\gpr1, SPRN_IAMR
	std	\gpr1, STACK_REGS_IAMR(r1)

	/*
	 * update kernel IAMR with AMR_KUEP_BLOCKED only
	 * अगर KUEP feature is enabled
	 */
	BEGIN_MMU_FTR_SECTION_NESTED(70)
	LOAD_REG_IMMEDIATE(\gpr2, AMR_KUEP_BLOCKED)
	mtspr	SPRN_IAMR, \gpr2
	isync
	END_MMU_FTR_SECTION_NESTED_IFSET(MMU_FTR_BOOK3S_KUEP, 70)
	.endअगर

100: // skip_save_amr
#पूर्ण_अगर
.endm

#अन्यथा /* !__ASSEMBLY__ */

#समावेश <linux/jump_label.h>

DECLARE_STATIC_KEY_FALSE(uaccess_flush_key);

#अगर_घोषित CONFIG_PPC_PKEY

बाह्य u64 __ro_after_init शेष_uamor;
बाह्य u64 __ro_after_init शेष_amr;
बाह्य u64 __ro_after_init शेष_iamr;

#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/ptrace.h>

/* usage of kthपढ़ो_use_mm() should inherit the
 * AMR value of the operating address space. But, the AMR value is
 * thपढ़ो-specअगरic and we inherit the address space and not thपढ़ो
 * access restrictions. Because of this ignore AMR value when accessing
 * userspace via kernel thपढ़ो.
 */
अटल अंतरभूत u64 current_thपढ़ो_amr(व्योम)
अणु
	अगर (current->thपढ़ो.regs)
		वापस current->thपढ़ो.regs->amr;
	वापस शेष_amr;
पूर्ण

अटल अंतरभूत u64 current_thपढ़ो_iamr(व्योम)
अणु
	अगर (current->thपढ़ो.regs)
		वापस current->thपढ़ो.regs->iamr;
	वापस शेष_iamr;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PKEY */

#अगर_घोषित CONFIG_PPC_KUAP

अटल अंतरभूत व्योम kuap_user_restore(काष्ठा pt_regs *regs)
अणु
	bool restore_amr = false, restore_iamr = false;
	अचिन्हित दीर्घ amr, iamr;

	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस;

	अगर (!mmu_has_feature(MMU_FTR_BOOK3S_KUAP)) अणु
		amr = mfspr(SPRN_AMR);
		अगर (amr != regs->amr)
			restore_amr = true;
	पूर्ण अन्यथा अणु
		restore_amr = true;
	पूर्ण

	अगर (!mmu_has_feature(MMU_FTR_BOOK3S_KUEP)) अणु
		iamr = mfspr(SPRN_IAMR);
		अगर (iamr != regs->iamr)
			restore_iamr = true;
	पूर्ण अन्यथा अणु
		restore_iamr = true;
	पूर्ण


	अगर (restore_amr || restore_iamr) अणु
		isync();
		अगर (restore_amr)
			mtspr(SPRN_AMR, regs->amr);
		अगर (restore_iamr)
			mtspr(SPRN_IAMR, regs->iamr);
	पूर्ण
	/*
	 * No isync required here because we are about to rfi
	 * back to previous context beक्रमe any user accesses
	 * would be made, which is a CSI.
	 */
पूर्ण

अटल अंतरभूत व्योम kuap_kernel_restore(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ amr)
अणु
	अगर (mmu_has_feature(MMU_FTR_BOOK3S_KUAP)) अणु
		अगर (unlikely(regs->amr != amr)) अणु
			isync();
			mtspr(SPRN_AMR, regs->amr);
			/*
			 * No isync required here because we are about to rfi
			 * back to previous context beक्रमe any user accesses
			 * would be made, which is a CSI.
			 */
		पूर्ण
	पूर्ण
	/*
	 * No need to restore IAMR when वापसing to kernel space.
	 */
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kuap_get_and_निश्चित_locked(व्योम)
अणु
	अगर (mmu_has_feature(MMU_FTR_BOOK3S_KUAP)) अणु
		अचिन्हित दीर्घ amr = mfspr(SPRN_AMR);
		अगर (IS_ENABLED(CONFIG_PPC_KUAP_DEBUG)) /* kuap_check_amr() */
			WARN_ON_ONCE(amr != AMR_KUAP_BLOCKED);
		वापस amr;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kuap_निश्चित_locked(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_KUAP_DEBUG) && mmu_has_feature(MMU_FTR_BOOK3S_KUAP))
		WARN_ON_ONCE(mfspr(SPRN_AMR) != AMR_KUAP_BLOCKED);
पूर्ण

/*
 * We support inभागidually allowing पढ़ो or ग_लिखो, but we करोn't support nesting
 * because that would require an expensive पढ़ो/modअगरy ग_लिखो of the AMR.
 */

अटल अंतरभूत अचिन्हित दीर्घ get_kuap(व्योम)
अणु
	/*
	 * We वापस AMR_KUAP_BLOCKED when we करोn't support KUAP because
	 * prevent_user_access_वापस needs to वापस AMR_KUAP_BLOCKED to
	 * cause restore_user_access to करो a flush.
	 *
	 * This has no effect in terms of actually blocking things on hash,
	 * so it करोesn't अवरोध anything.
	 */
	अगर (!mmu_has_feature(MMU_FTR_BOOK3S_KUAP))
		वापस AMR_KUAP_BLOCKED;

	वापस mfspr(SPRN_AMR);
पूर्ण

अटल अंतरभूत व्योम set_kuap(अचिन्हित दीर्घ value)
अणु
	अगर (!mmu_has_feature(MMU_FTR_BOOK3S_KUAP))
		वापस;

	/*
	 * ISA v3.0B says we need a CSI (Context Synchronising Inकाष्ठाion) both
	 * beक्रमe and after the move to AMR. See table 6 on page 1134.
	 */
	isync();
	mtspr(SPRN_AMR, value);
	isync();
पूर्ण

अटल अंतरभूत bool bad_kuap_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
				  bool is_ग_लिखो)
अणु
	अगर (!mmu_has_feature(MMU_FTR_BOOK3S_KUAP))
		वापस false;
	/*
	 * For radix this will be a storage protection fault (DSISR_PROTFAULT).
	 * For hash this will be a key fault (DSISR_KEYFAULT)
	 */
	/*
	 * We करो have exception table entry, but accessing the
	 * userspace results in fault.  This could be because we
	 * didn't unlock the AMR or access is denied by userspace
	 * using a key value that blocks access. We are only पूर्णांकerested
	 * in catching the use हाल of accessing without unlocking
	 * the AMR. Hence check क्रम BLOCK_WRITE/READ against AMR.
	 */
	अगर (is_ग_लिखो) अणु
		वापस (regs->amr & AMR_KUAP_BLOCK_WRITE) == AMR_KUAP_BLOCK_WRITE;
	पूर्ण
	वापस (regs->amr & AMR_KUAP_BLOCK_READ) == AMR_KUAP_BLOCK_READ;
पूर्ण

अटल __always_अंतरभूत व्योम allow_user_access(व्योम __user *to, स्थिर व्योम __user *from,
					      अचिन्हित दीर्घ size, अचिन्हित दीर्घ dir)
अणु
	अचिन्हित दीर्घ thपढ़ो_amr = 0;

	// This is written so we can resolve to a single हाल at build समय
	BUILD_BUG_ON(!__builtin_स्थिरant_p(dir));

	अगर (mmu_has_feature(MMU_FTR_PKEY))
		thपढ़ो_amr = current_thपढ़ो_amr();

	अगर (dir == KUAP_READ)
		set_kuap(thपढ़ो_amr | AMR_KUAP_BLOCK_WRITE);
	अन्यथा अगर (dir == KUAP_WRITE)
		set_kuap(thपढ़ो_amr | AMR_KUAP_BLOCK_READ);
	अन्यथा अगर (dir == KUAP_READ_WRITE)
		set_kuap(thपढ़ो_amr);
	अन्यथा
		BUILD_BUG();
पूर्ण

#अन्यथा /* CONFIG_PPC_KUAP */

अटल अंतरभूत अचिन्हित दीर्घ get_kuap(व्योम)
अणु
	वापस AMR_KUAP_BLOCKED;
पूर्ण

अटल अंतरभूत व्योम set_kuap(अचिन्हित दीर्घ value) अणु पूर्ण

अटल __always_अंतरभूत व्योम allow_user_access(व्योम __user *to, स्थिर व्योम __user *from,
					      अचिन्हित दीर्घ size, अचिन्हित दीर्घ dir)
अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_PPC_KUAP */

अटल अंतरभूत व्योम prevent_user_access(व्योम __user *to, स्थिर व्योम __user *from,
				       अचिन्हित दीर्घ size, अचिन्हित दीर्घ dir)
अणु
	set_kuap(AMR_KUAP_BLOCKED);
	अगर (अटल_branch_unlikely(&uaccess_flush_key))
		करो_uaccess_flush();
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prevent_user_access_वापस(व्योम)
अणु
	अचिन्हित दीर्घ flags = get_kuap();

	set_kuap(AMR_KUAP_BLOCKED);
	अगर (अटल_branch_unlikely(&uaccess_flush_key))
		करो_uaccess_flush();

	वापस flags;
पूर्ण

अटल अंतरभूत व्योम restore_user_access(अचिन्हित दीर्घ flags)
अणु
	set_kuap(flags);
	अगर (अटल_branch_unlikely(&uaccess_flush_key) && flags == AMR_KUAP_BLOCKED)
		करो_uaccess_flush();
पूर्ण
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_KUP_H */
