<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Generation of मुख्य entry poपूर्णांक क्रम the guest, exception handling.
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 *
 * Copyright (C) 2016 Imagination Technologies Ltd.
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/log2.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/msa.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/tlbex.h>
#समावेश <यंत्र/uयंत्र.h>

/* Register names */
#घोषणा ZERO		0
#घोषणा AT		1
#घोषणा V0		2
#घोषणा V1		3
#घोषणा A0		4
#घोषणा A1		5

#अगर _MIPS_SIM == _MIPS_SIM_ABI32
#घोषणा T0		8
#घोषणा T1		9
#घोषणा T2		10
#घोषणा T3		11
#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#अगर _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32
#घोषणा T0		12
#घोषणा T1		13
#घोषणा T2		14
#घोषणा T3		15
#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */

#घोषणा S0		16
#घोषणा S1		17
#घोषणा T9		25
#घोषणा K0		26
#घोषणा K1		27
#घोषणा GP		28
#घोषणा SP		29
#घोषणा RA		31

/* Some CP0 रेजिस्टरs */
#घोषणा C0_PWBASE	5, 5
#घोषणा C0_HWRENA	7, 0
#घोषणा C0_BADVADDR	8, 0
#घोषणा C0_BADINSTR	8, 1
#घोषणा C0_BADINSTRP	8, 2
#घोषणा C0_PGD		9, 7
#घोषणा C0_ENTRYHI	10, 0
#घोषणा C0_GUESTCTL1	10, 4
#घोषणा C0_STATUS	12, 0
#घोषणा C0_GUESTCTL0	12, 6
#घोषणा C0_CAUSE	13, 0
#घोषणा C0_EPC		14, 0
#घोषणा C0_EBASE	15, 1
#घोषणा C0_CONFIG5	16, 5
#घोषणा C0_DDATA_LO	28, 3
#घोषणा C0_ERROREPC	30, 0

#घोषणा CALLFRAME_SIZ   32

#अगर_घोषित CONFIG_64BIT
#घोषणा ST0_KX_IF_64	ST0_KX
#अन्यथा
#घोषणा ST0_KX_IF_64	0
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक scratch_vcpu[2] = अणु C0_DDATA_LO पूर्ण;
अटल अचिन्हित पूर्णांक scratch_पंचांगp[2] = अणु C0_ERROREPC पूर्ण;

क्रमागत label_id अणु
	label_fpu_1 = 1,
	label_msa_1,
	label_वापस_to_host,
	label_kernel_asid,
	label_निकास_common,
पूर्ण;

UASM_L_LA(_fpu_1)
UASM_L_LA(_msa_1)
UASM_L_LA(_वापस_to_host)
UASM_L_LA(_kernel_asid)
UASM_L_LA(_निकास_common)

अटल व्योम *kvm_mips_build_enter_guest(व्योम *addr);
अटल व्योम *kvm_mips_build_ret_from_निकास(व्योम *addr);
अटल व्योम *kvm_mips_build_ret_to_guest(व्योम *addr);
अटल व्योम *kvm_mips_build_ret_to_host(व्योम *addr);

/*
 * The version of this function in tlbex.c uses current_cpu_type(), but क्रम KVM
 * we assume symmetry.
 */
अटल पूर्णांक c0_kscratch(व्योम)
अणु
	चयन (boot_cpu_type()) अणु
	हाल CPU_XLP:
	हाल CPU_XLR:
		वापस 22;
	शेष:
		वापस 31;
	पूर्ण
पूर्ण

/**
 * kvm_mips_entry_setup() - Perक्रमm global setup क्रम entry code.
 *
 * Perक्रमm global setup क्रम entry code, such as choosing a scratch रेजिस्टर.
 *
 * Returns:	0 on success.
 *		-त्रुटि_सं on failure.
 */
पूर्णांक kvm_mips_entry_setup(व्योम)
अणु
	/*
	 * We prefer to use KScratchN रेजिस्टरs अगर they are available over the
	 * शेषs above, which may not work on all cores.
	 */
	अचिन्हित पूर्णांक kscratch_mask = cpu_data[0].kscratch_mask;

	अगर (pgd_reg != -1)
		kscratch_mask &= ~BIT(pgd_reg);

	/* Pick a scratch रेजिस्टर क्रम storing VCPU */
	अगर (kscratch_mask) अणु
		scratch_vcpu[0] = c0_kscratch();
		scratch_vcpu[1] = ffs(kscratch_mask) - 1;
		kscratch_mask &= ~BIT(scratch_vcpu[1]);
	पूर्ण

	/* Pick a scratch रेजिस्टर to use as a temp क्रम saving state */
	अगर (kscratch_mask) अणु
		scratch_पंचांगp[0] = c0_kscratch();
		scratch_पंचांगp[1] = ffs(kscratch_mask) - 1;
		kscratch_mask &= ~BIT(scratch_पंचांगp[1]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kvm_mips_build_save_scratch(u32 **p, अचिन्हित पूर्णांक पंचांगp,
					अचिन्हित पूर्णांक frame)
अणु
	/* Save the VCPU scratch रेजिस्टर value in cp0_epc of the stack frame */
	UASM_i_MFC0(p, पंचांगp, scratch_vcpu[0], scratch_vcpu[1]);
	UASM_i_SW(p, पंचांगp, दुरत्व(काष्ठा pt_regs, cp0_epc), frame);

	/* Save the temp scratch रेजिस्टर value in cp0_cause of stack frame */
	अगर (scratch_पंचांगp[0] == c0_kscratch()) अणु
		UASM_i_MFC0(p, पंचांगp, scratch_पंचांगp[0], scratch_पंचांगp[1]);
		UASM_i_SW(p, पंचांगp, दुरत्व(काष्ठा pt_regs, cp0_cause), frame);
	पूर्ण
पूर्ण

अटल व्योम kvm_mips_build_restore_scratch(u32 **p, अचिन्हित पूर्णांक पंचांगp,
					   अचिन्हित पूर्णांक frame)
अणु
	/*
	 * Restore host scratch रेजिस्टर values saved by
	 * kvm_mips_build_save_scratch().
	 */
	UASM_i_LW(p, पंचांगp, दुरत्व(काष्ठा pt_regs, cp0_epc), frame);
	UASM_i_MTC0(p, पंचांगp, scratch_vcpu[0], scratch_vcpu[1]);

	अगर (scratch_पंचांगp[0] == c0_kscratch()) अणु
		UASM_i_LW(p, पंचांगp, दुरत्व(काष्ठा pt_regs, cp0_cause), frame);
		UASM_i_MTC0(p, पंचांगp, scratch_पंचांगp[0], scratch_पंचांगp[1]);
	पूर्ण
पूर्ण

/**
 * build_set_exc_base() - Assemble code to ग_लिखो exception base address.
 * @p:		Code buffer poपूर्णांकer.
 * @reg:	Source रेजिस्टर (generated code may set WG bit in @reg).
 *
 * Assemble code to modअगरy the exception base address in the EBase रेजिस्टर,
 * using the appropriately sized access and setting the WG bit अगर necessary.
 */
अटल अंतरभूत व्योम build_set_exc_base(u32 **p, अचिन्हित पूर्णांक reg)
अणु
	अगर (cpu_has_ebase_wg) अणु
		/* Set WG so that all the bits get written */
		uयंत्र_i_ori(p, reg, reg, MIPS_EBASE_WG);
		UASM_i_MTC0(p, reg, C0_EBASE);
	पूर्ण अन्यथा अणु
		uयंत्र_i_mtc0(p, reg, C0_EBASE);
	पूर्ण
पूर्ण

/**
 * kvm_mips_build_vcpu_run() - Assemble function to start running a guest VCPU.
 * @addr:	Address to start writing code.
 *
 * Assemble the start of the vcpu_run function to run a guest VCPU. The function
 * conक्रमms to the following prototype:
 *
 * पूर्णांक vcpu_run(काष्ठा kvm_vcpu *vcpu);
 *
 * The निकास from the guest and वापस to the caller is handled by the code
 * generated by kvm_mips_build_ret_to_host().
 *
 * Returns:	Next address after end of written function.
 */
व्योम *kvm_mips_build_vcpu_run(व्योम *addr)
अणु
	u32 *p = addr;
	अचिन्हित पूर्णांक i;

	/*
	 * A0: vcpu
	 */

	/* k0/k1 not being used in host kernel context */
	UASM_i_ADDIU(&p, K1, SP, -(पूर्णांक)माप(काष्ठा pt_regs));
	क्रम (i = 16; i < 32; ++i) अणु
		अगर (i == 24)
			i = 28;
		UASM_i_SW(&p, i, दुरत्व(काष्ठा pt_regs, regs[i]), K1);
	पूर्ण

	/* Save host status */
	uयंत्र_i_mfc0(&p, V0, C0_STATUS);
	UASM_i_SW(&p, V0, दुरत्व(काष्ठा pt_regs, cp0_status), K1);

	/* Save scratch रेजिस्टरs, will be used to store poपूर्णांकer to vcpu etc */
	kvm_mips_build_save_scratch(&p, V1, K1);

	/* VCPU scratch रेजिस्टर has poपूर्णांकer to vcpu */
	UASM_i_MTC0(&p, A0, scratch_vcpu[0], scratch_vcpu[1]);

	/* Offset पूर्णांकo vcpu->arch */
	UASM_i_ADDIU(&p, K1, A0, दुरत्व(काष्ठा kvm_vcpu, arch));

	/*
	 * Save the host stack to VCPU, used क्रम exception processing
	 * when we निकास from the Guest
	 */
	UASM_i_SW(&p, SP, दुरत्व(काष्ठा kvm_vcpu_arch, host_stack), K1);

	/* Save the kernel gp as well */
	UASM_i_SW(&p, GP, दुरत्व(काष्ठा kvm_vcpu_arch, host_gp), K1);

	/*
	 * Setup status रेजिस्टर क्रम running the guest in UM, पूर्णांकerrupts
	 * are disabled
	 */
	UASM_i_LA(&p, K0, ST0_EXL | KSU_USER | ST0_BEV | ST0_KX_IF_64);
	uयंत्र_i_mtc0(&p, K0, C0_STATUS);
	uयंत्र_i_ehb(&p);

	/* load up the new EBASE */
	UASM_i_LW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, guest_ebase), K1);
	build_set_exc_base(&p, K0);

	/*
	 * Now that the new EBASE has been loaded, unset BEV, set
	 * पूर्णांकerrupt mask as it was but make sure that समयr पूर्णांकerrupts
	 * are enabled
	 */
	uयंत्र_i_addiu(&p, K0, ZERO, ST0_EXL | KSU_USER | ST0_IE | ST0_KX_IF_64);
	uयंत्र_i_andi(&p, V0, V0, ST0_IM);
	uयंत्र_i_or(&p, K0, K0, V0);
	uयंत्र_i_mtc0(&p, K0, C0_STATUS);
	uयंत्र_i_ehb(&p);

	p = kvm_mips_build_enter_guest(p);

	वापस p;
पूर्ण

/**
 * kvm_mips_build_enter_guest() - Assemble code to resume guest execution.
 * @addr:	Address to start writing code.
 *
 * Assemble the code to resume guest execution. This code is common between the
 * initial entry पूर्णांकo the guest from the host, and वापसing from the निकास
 * handler back to the guest.
 *
 * Returns:	Next address after end of written function.
 */
अटल व्योम *kvm_mips_build_enter_guest(व्योम *addr)
अणु
	u32 *p = addr;
	अचिन्हित पूर्णांक i;
	काष्ठा uयंत्र_label labels[2];
	काष्ठा uयंत्र_reloc relocs[2];
	काष्ठा uयंत्र_label __maybe_unused *l = labels;
	काष्ठा uयंत्र_reloc __maybe_unused *r = relocs;

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	/* Set Guest EPC */
	UASM_i_LW(&p, T0, दुरत्व(काष्ठा kvm_vcpu_arch, pc), K1);
	UASM_i_MTC0(&p, T0, C0_EPC);

	/* Save normal linux process pgd (VZ guarantees pgd_reg is set) */
	अगर (cpu_has_ldpte)
		UASM_i_MFC0(&p, K0, C0_PWBASE);
	अन्यथा
		UASM_i_MFC0(&p, K0, c0_kscratch(), pgd_reg);
	UASM_i_SW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, host_pgd), K1);

	/*
	 * Set up KVM GPA pgd.
	 * This करोes roughly the same as TLBMISS_HANDLER_SETUP_PGD():
	 * - call tlbmiss_handler_setup_pgd(mm->pgd)
	 * - ग_लिखो mm->pgd पूर्णांकo CP0_PWBase
	 *
	 * We keep S0 poपूर्णांकing at काष्ठा kvm so we can load the ASID below.
	 */
	UASM_i_LW(&p, S0, (पूर्णांक)दुरत्व(काष्ठा kvm_vcpu, kvm) -
			  (पूर्णांक)दुरत्व(काष्ठा kvm_vcpu, arch), K1);
	UASM_i_LW(&p, A0, दुरत्व(काष्ठा kvm, arch.gpa_mm.pgd), S0);
	UASM_i_LA(&p, T9, (अचिन्हित दीर्घ)tlbmiss_handler_setup_pgd);
	uयंत्र_i_jalr(&p, RA, T9);
	/* delay slot */
	अगर (cpu_has_htw)
		UASM_i_MTC0(&p, A0, C0_PWBASE);
	अन्यथा
		uयंत्र_i_nop(&p);

	/* Set GM bit to setup eret to VZ guest context */
	uयंत्र_i_addiu(&p, V1, ZERO, 1);
	uयंत्र_i_mfc0(&p, K0, C0_GUESTCTL0);
	uयंत्र_i_ins(&p, K0, V1, MIPS_GCTL0_GM_SHIFT, 1);
	uयंत्र_i_mtc0(&p, K0, C0_GUESTCTL0);

	अगर (cpu_has_guestid) अणु
		/*
		 * Set root mode GuestID, so that root TLB refill handler can
		 * use the correct GuestID in the root TLB.
		 */

		/* Get current GuestID */
		uयंत्र_i_mfc0(&p, T0, C0_GUESTCTL1);
		/* Set GuestCtl1.RID = GuestCtl1.ID */
		uयंत्र_i_ext(&p, T1, T0, MIPS_GCTL1_ID_SHIFT,
			   MIPS_GCTL1_ID_WIDTH);
		uयंत्र_i_ins(&p, T0, T1, MIPS_GCTL1_RID_SHIFT,
			   MIPS_GCTL1_RID_WIDTH);
		uयंत्र_i_mtc0(&p, T0, C0_GUESTCTL1);

		/* GuestID handles dealiasing so we करोn't need to touch ASID */
		जाओ skip_asid_restore;
	पूर्ण

	/* Root ASID Dealias (RAD) */

	/* Save host ASID */
	UASM_i_MFC0(&p, K0, C0_ENTRYHI);
	UASM_i_SW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, host_entryhi),
		  K1);

	/* Set the root ASID क्रम the Guest */
	UASM_i_ADDIU(&p, T1, S0,
		     दुरत्व(काष्ठा kvm, arch.gpa_mm.context.asid));

	/* t1: contains the base of the ASID array, need to get the cpu id  */
	/* smp_processor_id */
	uयंत्र_i_lw(&p, T2, दुरत्व(काष्ठा thपढ़ो_info, cpu), GP);
	/* index the ASID array */
	uयंत्र_i_sll(&p, T2, T2, ilog2(माप(दीर्घ)));
	UASM_i_ADDU(&p, T3, T1, T2);
	UASM_i_LW(&p, K0, 0, T3);
#अगर_घोषित CONFIG_MIPS_ASID_BITS_VARIABLE
	/*
	 * reuse ASID array offset
	 * cpuinfo_mips is a multiple of माप(दीर्घ)
	 */
	uयंत्र_i_addiu(&p, T3, ZERO, माप(काष्ठा cpuinfo_mips)/माप(दीर्घ));
	uयंत्र_i_mul(&p, T2, T2, T3);

	UASM_i_LA_mostly(&p, AT, (दीर्घ)&cpu_data[0].asid_mask);
	UASM_i_ADDU(&p, AT, AT, T2);
	UASM_i_LW(&p, T2, uयंत्र_rel_lo((दीर्घ)&cpu_data[0].asid_mask), AT);
	uयंत्र_i_and(&p, K0, K0, T2);
#अन्यथा
	uयंत्र_i_andi(&p, K0, K0, MIPS_ENTRYHI_ASID);
#पूर्ण_अगर

	/* Set up KVM VZ root ASID (!guestid) */
	uयंत्र_i_mtc0(&p, K0, C0_ENTRYHI);
skip_asid_restore:
	uयंत्र_i_ehb(&p);

	/* Disable RDHWR access */
	uयंत्र_i_mtc0(&p, ZERO, C0_HWRENA);

	/* load the guest context from VCPU and वापस */
	क्रम (i = 1; i < 32; ++i) अणु
		/* Guest k0/k1 loaded later */
		अगर (i == K0 || i == K1)
			जारी;
		UASM_i_LW(&p, i, दुरत्व(काष्ठा kvm_vcpu_arch, gprs[i]), K1);
	पूर्ण

#अगर_अघोषित CONFIG_CPU_MIPSR6
	/* Restore hi/lo */
	UASM_i_LW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, hi), K1);
	uयंत्र_i_mthi(&p, K0);

	UASM_i_LW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, lo), K1);
	uयंत्र_i_mtlo(&p, K0);
#पूर्ण_अगर

	/* Restore the guest's k0/k1 रेजिस्टरs */
	UASM_i_LW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, gprs[K0]), K1);
	UASM_i_LW(&p, K1, दुरत्व(काष्ठा kvm_vcpu_arch, gprs[K1]), K1);

	/* Jump to guest */
	uयंत्र_i_eret(&p);

	uयंत्र_resolve_relocs(relocs, labels);

	वापस p;
पूर्ण

/**
 * kvm_mips_build_tlb_refill_exception() - Assemble TLB refill handler.
 * @addr:	Address to start writing code.
 * @handler:	Address of common handler (within range of @addr).
 *
 * Assemble TLB refill exception fast path handler क्रम guest execution.
 *
 * Returns:	Next address after end of written function.
 */
व्योम *kvm_mips_build_tlb_refill_exception(व्योम *addr, व्योम *handler)
अणु
	u32 *p = addr;
	काष्ठा uयंत्र_label labels[2];
	काष्ठा uयंत्र_reloc relocs[2];
#अगर_अघोषित CONFIG_CPU_LOONGSON64
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
#पूर्ण_अगर

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	/* Save guest k1 पूर्णांकo scratch रेजिस्टर */
	UASM_i_MTC0(&p, K1, scratch_पंचांगp[0], scratch_पंचांगp[1]);

	/* Get the VCPU poपूर्णांकer from the VCPU scratch रेजिस्टर */
	UASM_i_MFC0(&p, K1, scratch_vcpu[0], scratch_vcpu[1]);

	/* Save guest k0 पूर्णांकo VCPU काष्ठाure */
	UASM_i_SW(&p, K0, दुरत्व(काष्ठा kvm_vcpu, arch.gprs[K0]), K1);

	/*
	 * Some of the common tlbex code uses current_cpu_type(). For KVM we
	 * assume symmetry and just disable preemption to silence the warning.
	 */
	preempt_disable();

#अगर_घोषित CONFIG_CPU_LOONGSON64
	UASM_i_MFC0(&p, K1, C0_PGD);
	uयंत्र_i_lddir(&p, K0, K1, 3);  /* global page dir */
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	uयंत्र_i_lddir(&p, K1, K0, 1);  /* middle page dir */
#पूर्ण_अगर
	uयंत्र_i_ldpte(&p, K1, 0);      /* even */
	uयंत्र_i_ldpte(&p, K1, 1);      /* odd */
	uयंत्र_i_tlbwr(&p);
#अन्यथा
	/*
	 * Now क्रम the actual refill bit. A lot of this can be common with the
	 * Linux TLB refill handler, however we करोn't need to handle so many
	 * हालs. We only need to handle user mode refills, and user mode runs
	 * with 32-bit addressing.
	 *
	 * Thereक्रमe the branch to label_vदो_स्मृति generated by build_get_pmde64()
	 * that isn't resolved should never actually get taken and is harmless
	 * to leave in place क्रम now.
	 */

#अगर_घोषित CONFIG_64BIT
	build_get_pmde64(&p, &l, &r, K0, K1); /* get pmd in K1 */
#अन्यथा
	build_get_pgde32(&p, K0, K1); /* get pgd in K1 */
#पूर्ण_अगर

	/* we करोn't support huge pages yet */

	build_get_ptep(&p, K0, K1);
	build_update_entries(&p, K0, K1);
	build_tlb_ग_लिखो_entry(&p, &l, &r, tlb_अक्रमom);
#पूर्ण_अगर

	preempt_enable();

	/* Get the VCPU poपूर्णांकer from the VCPU scratch रेजिस्टर again */
	UASM_i_MFC0(&p, K1, scratch_vcpu[0], scratch_vcpu[1]);

	/* Restore the guest's k0/k1 रेजिस्टरs */
	UASM_i_LW(&p, K0, दुरत्व(काष्ठा kvm_vcpu, arch.gprs[K0]), K1);
	uयंत्र_i_ehb(&p);
	UASM_i_MFC0(&p, K1, scratch_पंचांगp[0], scratch_पंचांगp[1]);

	/* Jump to guest */
	uयंत्र_i_eret(&p);

	वापस p;
पूर्ण

/**
 * kvm_mips_build_exception() - Assemble first level guest exception handler.
 * @addr:	Address to start writing code.
 * @handler:	Address of common handler (within range of @addr).
 *
 * Assemble exception vector code क्रम guest execution. The generated vector will
 * branch to the common exception handler generated by kvm_mips_build_निकास().
 *
 * Returns:	Next address after end of written function.
 */
व्योम *kvm_mips_build_exception(व्योम *addr, व्योम *handler)
अणु
	u32 *p = addr;
	काष्ठा uयंत्र_label labels[2];
	काष्ठा uयंत्र_reloc relocs[2];
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	/* Save guest k1 पूर्णांकo scratch रेजिस्टर */
	UASM_i_MTC0(&p, K1, scratch_पंचांगp[0], scratch_पंचांगp[1]);

	/* Get the VCPU poपूर्णांकer from the VCPU scratch रेजिस्टर */
	UASM_i_MFC0(&p, K1, scratch_vcpu[0], scratch_vcpu[1]);
	UASM_i_ADDIU(&p, K1, K1, दुरत्व(काष्ठा kvm_vcpu, arch));

	/* Save guest k0 पूर्णांकo VCPU काष्ठाure */
	UASM_i_SW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, gprs[K0]), K1);

	/* Branch to the common handler */
	uयंत्र_il_b(&p, &r, label_निकास_common);
	 uयंत्र_i_nop(&p);

	uयंत्र_l_निकास_common(&l, handler);
	uयंत्र_resolve_relocs(relocs, labels);

	वापस p;
पूर्ण

/**
 * kvm_mips_build_निकास() - Assemble common guest निकास handler.
 * @addr:	Address to start writing code.
 *
 * Assemble the generic guest निकास handling code. This is called by the
 * exception vectors (generated by kvm_mips_build_exception()), and calls
 * kvm_mips_handle_निकास(), then either resumes the guest or वापसs to the host
 * depending on the वापस value.
 *
 * Returns:	Next address after end of written function.
 */
व्योम *kvm_mips_build_निकास(व्योम *addr)
अणु
	u32 *p = addr;
	अचिन्हित पूर्णांक i;
	काष्ठा uयंत्र_label labels[3];
	काष्ठा uयंत्र_reloc relocs[3];
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	/*
	 * Generic Guest exception handler. We end up here when the guest
	 * करोes something that causes a trap to kernel mode.
	 *
	 * Both k0/k1 रेजिस्टरs will have alपढ़ोy been saved (k0 पूर्णांकo the vcpu
	 * काष्ठाure, and k1 पूर्णांकo the scratch_पंचांगp रेजिस्टर).
	 *
	 * The k1 रेजिस्टर will alपढ़ोy contain the kvm_vcpu_arch poपूर्णांकer.
	 */

	/* Start saving Guest context to VCPU */
	क्रम (i = 0; i < 32; ++i) अणु
		/* Guest k0/k1 saved later */
		अगर (i == K0 || i == K1)
			जारी;
		UASM_i_SW(&p, i, दुरत्व(काष्ठा kvm_vcpu_arch, gprs[i]), K1);
	पूर्ण

#अगर_अघोषित CONFIG_CPU_MIPSR6
	/* We need to save hi/lo and restore them on the way out */
	uयंत्र_i_mfhi(&p, T0);
	UASM_i_SW(&p, T0, दुरत्व(काष्ठा kvm_vcpu_arch, hi), K1);

	uयंत्र_i_mflo(&p, T0);
	UASM_i_SW(&p, T0, दुरत्व(काष्ठा kvm_vcpu_arch, lo), K1);
#पूर्ण_अगर

	/* Finally save guest k1 to VCPU */
	uयंत्र_i_ehb(&p);
	UASM_i_MFC0(&p, T0, scratch_पंचांगp[0], scratch_पंचांगp[1]);
	UASM_i_SW(&p, T0, दुरत्व(काष्ठा kvm_vcpu_arch, gprs[K1]), K1);

	/* Now that context has been saved, we can use other रेजिस्टरs */

	/* Restore vcpu */
	UASM_i_MFC0(&p, S0, scratch_vcpu[0], scratch_vcpu[1]);

	/*
	 * Save Host level EPC, BadVaddr and Cause to VCPU, useful to process
	 * the exception
	 */
	UASM_i_MFC0(&p, K0, C0_EPC);
	UASM_i_SW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, pc), K1);

	UASM_i_MFC0(&p, K0, C0_BADVADDR);
	UASM_i_SW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, host_cp0_badvaddr),
		  K1);

	uयंत्र_i_mfc0(&p, K0, C0_CAUSE);
	uयंत्र_i_sw(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, host_cp0_cause), K1);

	अगर (cpu_has_badinstr) अणु
		uयंत्र_i_mfc0(&p, K0, C0_BADINSTR);
		uयंत्र_i_sw(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch,
					   host_cp0_badinstr), K1);
	पूर्ण

	अगर (cpu_has_badinstrp) अणु
		uयंत्र_i_mfc0(&p, K0, C0_BADINSTRP);
		uयंत्र_i_sw(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch,
					   host_cp0_badinstrp), K1);
	पूर्ण

	/* Now restore the host state just enough to run the handlers */

	/* Switch EBASE to the one used by Linux */
	/* load up the host EBASE */
	uयंत्र_i_mfc0(&p, V0, C0_STATUS);

	uयंत्र_i_lui(&p, AT, ST0_BEV >> 16);
	uयंत्र_i_or(&p, K0, V0, AT);

	uयंत्र_i_mtc0(&p, K0, C0_STATUS);
	uयंत्र_i_ehb(&p);

	UASM_i_LA_mostly(&p, K0, (दीर्घ)&ebase);
	UASM_i_LW(&p, K0, uयंत्र_rel_lo((दीर्घ)&ebase), K0);
	build_set_exc_base(&p, K0);

	अगर (raw_cpu_has_fpu) अणु
		/*
		 * If FPU is enabled, save FCR31 and clear it so that later
		 * ctc1's don't trigger FPE क्रम pending exceptions.
		 */
		uयंत्र_i_lui(&p, AT, ST0_CU1 >> 16);
		uयंत्र_i_and(&p, V1, V0, AT);
		uयंत्र_il_beqz(&p, &r, V1, label_fpu_1);
		 uयंत्र_i_nop(&p);
		uयंत्र_i_cfc1(&p, T0, 31);
		uयंत्र_i_sw(&p, T0, दुरत्व(काष्ठा kvm_vcpu_arch, fpu.fcr31),
			  K1);
		uयंत्र_i_ctc1(&p, ZERO, 31);
		uयंत्र_l_fpu_1(&l, p);
	पूर्ण

	अगर (cpu_has_msa) अणु
		/*
		 * If MSA is enabled, save MSACSR and clear it so that later
		 * inकाष्ठाions करोn't trigger MSAFPE क्रम pending exceptions.
		 */
		uयंत्र_i_mfc0(&p, T0, C0_CONFIG5);
		uयंत्र_i_ext(&p, T0, T0, 27, 1); /* MIPS_CONF5_MSAEN */
		uयंत्र_il_beqz(&p, &r, T0, label_msa_1);
		 uयंत्र_i_nop(&p);
		uयंत्र_i_cfcmsa(&p, T0, MSA_CSR);
		uयंत्र_i_sw(&p, T0, दुरत्व(काष्ठा kvm_vcpu_arch, fpu.msacsr),
			  K1);
		uयंत्र_i_ctcmsa(&p, MSA_CSR, ZERO);
		uयंत्र_l_msa_1(&l, p);
	पूर्ण

	/* Restore host ASID */
	अगर (!cpu_has_guestid) अणु
		UASM_i_LW(&p, K0, दुरत्व(काष्ठा kvm_vcpu_arch, host_entryhi),
			  K1);
		UASM_i_MTC0(&p, K0, C0_ENTRYHI);
	पूर्ण

	/*
	 * Set up normal Linux process pgd.
	 * This करोes roughly the same as TLBMISS_HANDLER_SETUP_PGD():
	 * - call tlbmiss_handler_setup_pgd(mm->pgd)
	 * - ग_लिखो mm->pgd पूर्णांकo CP0_PWBase
	 */
	UASM_i_LW(&p, A0,
		  दुरत्व(काष्ठा kvm_vcpu_arch, host_pgd), K1);
	UASM_i_LA(&p, T9, (अचिन्हित दीर्घ)tlbmiss_handler_setup_pgd);
	uयंत्र_i_jalr(&p, RA, T9);
	/* delay slot */
	अगर (cpu_has_htw)
		UASM_i_MTC0(&p, A0, C0_PWBASE);
	अन्यथा
		uयंत्र_i_nop(&p);

	/* Clear GM bit so we करोn't enter guest mode when EXL is cleared */
	uयंत्र_i_mfc0(&p, K0, C0_GUESTCTL0);
	uयंत्र_i_ins(&p, K0, ZERO, MIPS_GCTL0_GM_SHIFT, 1);
	uयंत्र_i_mtc0(&p, K0, C0_GUESTCTL0);

	/* Save GuestCtl0 so we can access GExcCode after CPU migration */
	uयंत्र_i_sw(&p, K0,
		  दुरत्व(काष्ठा kvm_vcpu_arch, host_cp0_guestctl0), K1);

	अगर (cpu_has_guestid) अणु
		/*
		 * Clear root mode GuestID, so that root TLB operations use the
		 * root GuestID in the root TLB.
		 */
		uयंत्र_i_mfc0(&p, T0, C0_GUESTCTL1);
		/* Set GuestCtl1.RID = MIPS_GCTL1_ROOT_GUESTID (i.e. 0) */
		uयंत्र_i_ins(&p, T0, ZERO, MIPS_GCTL1_RID_SHIFT,
			   MIPS_GCTL1_RID_WIDTH);
		uयंत्र_i_mtc0(&p, T0, C0_GUESTCTL1);
	पूर्ण

	/* Now that the new EBASE has been loaded, unset BEV and KSU_USER */
	uयंत्र_i_addiu(&p, AT, ZERO, ~(ST0_EXL | KSU_USER | ST0_IE));
	uयंत्र_i_and(&p, V0, V0, AT);
	uयंत्र_i_lui(&p, AT, ST0_CU0 >> 16);
	uयंत्र_i_or(&p, V0, V0, AT);
#अगर_घोषित CONFIG_64BIT
	uयंत्र_i_ori(&p, V0, V0, ST0_SX | ST0_UX);
#पूर्ण_अगर
	uयंत्र_i_mtc0(&p, V0, C0_STATUS);
	uयंत्र_i_ehb(&p);

	/* Load up host GP */
	UASM_i_LW(&p, GP, दुरत्व(काष्ठा kvm_vcpu_arch, host_gp), K1);

	/* Need a stack beक्रमe we can jump to "C" */
	UASM_i_LW(&p, SP, दुरत्व(काष्ठा kvm_vcpu_arch, host_stack), K1);

	/* Saved host state */
	UASM_i_ADDIU(&p, SP, SP, -(पूर्णांक)माप(काष्ठा pt_regs));

	/*
	 * XXXKYMA करो we need to load the host ASID, maybe not because the
	 * kernel entries are marked GLOBAL, need to verअगरy
	 */

	/* Restore host scratch रेजिस्टरs, as we'll have clobbered them */
	kvm_mips_build_restore_scratch(&p, K0, SP);

	/* Restore RDHWR access */
	UASM_i_LA_mostly(&p, K0, (दीर्घ)&hwrena);
	uयंत्र_i_lw(&p, K0, uयंत्र_rel_lo((दीर्घ)&hwrena), K0);
	uयंत्र_i_mtc0(&p, K0, C0_HWRENA);

	/* Jump to handler */
	/*
	 * XXXKYMA: not sure अगर this is safe, how large is the stack??
	 * Now jump to the kvm_mips_handle_निकास() to see अगर we can deal
	 * with this in the kernel
	 */
	uयंत्र_i_move(&p, A0, S0);
	UASM_i_LA(&p, T9, (अचिन्हित दीर्घ)kvm_mips_handle_निकास);
	uयंत्र_i_jalr(&p, RA, T9);
	 UASM_i_ADDIU(&p, SP, SP, -CALLFRAME_SIZ);

	uयंत्र_resolve_relocs(relocs, labels);

	p = kvm_mips_build_ret_from_निकास(p);

	वापस p;
पूर्ण

/**
 * kvm_mips_build_ret_from_निकास() - Assemble guest निकास वापस handler.
 * @addr:	Address to start writing code.
 *
 * Assemble the code to handle the वापस from kvm_mips_handle_निकास(), either
 * resuming the guest or वापसing to the host depending on the वापस value.
 *
 * Returns:	Next address after end of written function.
 */
अटल व्योम *kvm_mips_build_ret_from_निकास(व्योम *addr)
अणु
	u32 *p = addr;
	काष्ठा uयंत्र_label labels[2];
	काष्ठा uयंत्र_reloc relocs[2];
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	/* Return from handler Make sure पूर्णांकerrupts are disabled */
	uयंत्र_i_di(&p, ZERO);
	uयंत्र_i_ehb(&p);

	/*
	 * XXXKYMA: k0/k1 could have been blown away अगर we processed
	 * an exception जबतक we were handling the exception from the
	 * guest, reload k1
	 */

	uयंत्र_i_move(&p, K1, S0);
	UASM_i_ADDIU(&p, K1, K1, दुरत्व(काष्ठा kvm_vcpu, arch));

	/*
	 * Check वापस value, should tell us अगर we are वापसing to the
	 * host (handle I/O etc)or resuming the guest
	 */
	uयंत्र_i_andi(&p, T0, V0, RESUME_HOST);
	uयंत्र_il_bnez(&p, &r, T0, label_वापस_to_host);
	 uयंत्र_i_nop(&p);

	p = kvm_mips_build_ret_to_guest(p);

	uयंत्र_l_वापस_to_host(&l, p);
	p = kvm_mips_build_ret_to_host(p);

	uयंत्र_resolve_relocs(relocs, labels);

	वापस p;
पूर्ण

/**
 * kvm_mips_build_ret_to_guest() - Assemble code to वापस to the guest.
 * @addr:	Address to start writing code.
 *
 * Assemble the code to handle वापस from the guest निकास handler
 * (kvm_mips_handle_निकास()) back to the guest.
 *
 * Returns:	Next address after end of written function.
 */
अटल व्योम *kvm_mips_build_ret_to_guest(व्योम *addr)
अणु
	u32 *p = addr;

	/* Put the saved poपूर्णांकer to vcpu (s0) back पूर्णांकo the scratch रेजिस्टर */
	UASM_i_MTC0(&p, S0, scratch_vcpu[0], scratch_vcpu[1]);

	/* Load up the Guest EBASE to minimize the winकरोw where BEV is set */
	UASM_i_LW(&p, T0, दुरत्व(काष्ठा kvm_vcpu_arch, guest_ebase), K1);

	/* Switch EBASE back to the one used by KVM */
	uयंत्र_i_mfc0(&p, V1, C0_STATUS);
	uयंत्र_i_lui(&p, AT, ST0_BEV >> 16);
	uयंत्र_i_or(&p, K0, V1, AT);
	uयंत्र_i_mtc0(&p, K0, C0_STATUS);
	uयंत्र_i_ehb(&p);
	build_set_exc_base(&p, T0);

	/* Setup status रेजिस्टर क्रम running guest in UM */
	uयंत्र_i_ori(&p, V1, V1, ST0_EXL | KSU_USER | ST0_IE);
	UASM_i_LA(&p, AT, ~(ST0_CU0 | ST0_MX | ST0_SX | ST0_UX));
	uयंत्र_i_and(&p, V1, V1, AT);
	uयंत्र_i_mtc0(&p, V1, C0_STATUS);
	uयंत्र_i_ehb(&p);

	p = kvm_mips_build_enter_guest(p);

	वापस p;
पूर्ण

/**
 * kvm_mips_build_ret_to_host() - Assemble code to वापस to the host.
 * @addr:	Address to start writing code.
 *
 * Assemble the code to handle वापस from the guest निकास handler
 * (kvm_mips_handle_निकास()) back to the host, i.e. to the caller of the vcpu_run
 * function generated by kvm_mips_build_vcpu_run().
 *
 * Returns:	Next address after end of written function.
 */
अटल व्योम *kvm_mips_build_ret_to_host(व्योम *addr)
अणु
	u32 *p = addr;
	अचिन्हित पूर्णांक i;

	/* EBASE is alपढ़ोy poपूर्णांकing to Linux */
	UASM_i_LW(&p, K1, दुरत्व(काष्ठा kvm_vcpu_arch, host_stack), K1);
	UASM_i_ADDIU(&p, K1, K1, -(पूर्णांक)माप(काष्ठा pt_regs));

	/*
	 * r2/v0 is the वापस code, shअगरt it करोwn by 2 (arithmetic)
	 * to recover the err code
	 */
	uयंत्र_i_sra(&p, K0, V0, 2);
	uयंत्र_i_move(&p, V0, K0);

	/* Load context saved on the host stack */
	क्रम (i = 16; i < 31; ++i) अणु
		अगर (i == 24)
			i = 28;
		UASM_i_LW(&p, i, दुरत्व(काष्ठा pt_regs, regs[i]), K1);
	पूर्ण

	/* Restore RDHWR access */
	UASM_i_LA_mostly(&p, K0, (दीर्घ)&hwrena);
	uयंत्र_i_lw(&p, K0, uयंत्र_rel_lo((दीर्घ)&hwrena), K0);
	uयंत्र_i_mtc0(&p, K0, C0_HWRENA);

	/* Restore RA, which is the address we will वापस to */
	UASM_i_LW(&p, RA, दुरत्व(काष्ठा pt_regs, regs[RA]), K1);
	uयंत्र_i_jr(&p, RA);
	 uयंत्र_i_nop(&p);

	वापस p;
पूर्ण

