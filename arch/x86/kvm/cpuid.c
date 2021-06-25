<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 * cpuid support routines
 *
 * derived from arch/x86/kvm/x86.c
 *
 * Copyright 2011 Red Hat, Inc. and/or its affiliates.
 * Copyright IBM Corporation, 2008
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/export.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/स्थिति.स>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/user.h>
#समावेश <यंत्र/fpu/xstate.h>
#समावेश <यंत्र/sgx.h>
#समावेश "cpuid.h"
#समावेश "lapic.h"
#समावेश "mmu.h"
#समावेश "trace.h"
#समावेश "pmu.h"

/*
 * Unlike "struct cpuinfo_x86.x86_capability", kvm_cpu_caps करोesn't need to be
 * aligned to माप(अचिन्हित दीर्घ) because it's not accessed via bitops.
 */
u32 kvm_cpu_caps[NR_KVM_CPU_CAPS] __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(kvm_cpu_caps);

अटल u32 xstate_required_size(u64 xstate_bv, bool compacted)
अणु
	पूर्णांक feature_bit = 0;
	u32 ret = XSAVE_HDR_SIZE + XSAVE_HDR_OFFSET;

	xstate_bv &= XFEATURE_MASK_EXTEND;
	जबतक (xstate_bv) अणु
		अगर (xstate_bv & 0x1) अणु
		        u32 eax, ebx, ecx, edx, offset;
		        cpuid_count(0xD, feature_bit, &eax, &ebx, &ecx, &edx);
			offset = compacted ? ret : ebx;
			ret = max(ret, offset + eax);
		पूर्ण

		xstate_bv >>= 1;
		feature_bit++;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा F feature_bit
#घोषणा SF(name) (boot_cpu_has(X86_FEATURE_##name) ? F(name) : 0)

अटल अंतरभूत काष्ठा kvm_cpuid_entry2 *cpuid_entry2_find(
	काष्ठा kvm_cpuid_entry2 *entries, पूर्णांक nent, u32 function, u32 index)
अणु
	काष्ठा kvm_cpuid_entry2 *e;
	पूर्णांक i;

	क्रम (i = 0; i < nent; i++) अणु
		e = &entries[i];

		अगर (e->function == function && (e->index == index ||
		    !(e->flags & KVM_CPUID_FLAG_SIGNIFCANT_INDEX)))
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक kvm_check_cpuid(काष्ठा kvm_cpuid_entry2 *entries, पूर्णांक nent)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	/*
	 * The existing code assumes भव address is 48-bit or 57-bit in the
	 * canonical address checks; निकास अगर it is ever changed.
	 */
	best = cpuid_entry2_find(entries, nent, 0x80000008, 0);
	अगर (best) अणु
		पूर्णांक vaddr_bits = (best->eax & 0xff00) >> 8;

		अगर (vaddr_bits != 48 && vaddr_bits != 57 && vaddr_bits != 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम kvm_update_pv_runसमय(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, KVM_CPUID_FEATURES, 0);

	/*
	 * save the feature biपंचांगap to aव्योम cpuid lookup क्रम every PV
	 * operation
	 */
	अगर (best)
		vcpu->arch.pv_cpuid.features = best->eax;
पूर्ण

व्योम kvm_update_cpuid_runसमय(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 1, 0);
	अगर (best) अणु
		/* Update OSXSAVE bit */
		अगर (boot_cpu_has(X86_FEATURE_XSAVE))
			cpuid_entry_change(best, X86_FEATURE_OSXSAVE,
				   kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_OSXSAVE));

		cpuid_entry_change(best, X86_FEATURE_APIC,
			   vcpu->arch.apic_base & MSR_IA32_APICBASE_ENABLE);
	पूर्ण

	best = kvm_find_cpuid_entry(vcpu, 7, 0);
	अगर (best && boot_cpu_has(X86_FEATURE_PKU) && best->function == 0x7)
		cpuid_entry_change(best, X86_FEATURE_OSPKE,
				   kvm_पढ़ो_cr4_bits(vcpu, X86_CR4_PKE));

	best = kvm_find_cpuid_entry(vcpu, 0xD, 0);
	अगर (best)
		best->ebx = xstate_required_size(vcpu->arch.xcr0, false);

	best = kvm_find_cpuid_entry(vcpu, 0xD, 1);
	अगर (best && (cpuid_entry_has(best, X86_FEATURE_XSAVES) ||
		     cpuid_entry_has(best, X86_FEATURE_XSAVEC)))
		best->ebx = xstate_required_size(vcpu->arch.xcr0, true);

	best = kvm_find_cpuid_entry(vcpu, KVM_CPUID_FEATURES, 0);
	अगर (kvm_hlt_in_guest(vcpu->kvm) && best &&
		(best->eax & (1 << KVM_FEATURE_PV_UNHALT)))
		best->eax &= ~(1 << KVM_FEATURE_PV_UNHALT);

	अगर (!kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_MISC_ENABLE_NO_MWAIT)) अणु
		best = kvm_find_cpuid_entry(vcpu, 0x1, 0);
		अगर (best)
			cpuid_entry_change(best, X86_FEATURE_MWAIT,
					   vcpu->arch.ia32_misc_enable_msr &
					   MSR_IA32_MISC_ENABLE_MWAIT);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_update_cpuid_runसमय);

अटल व्योम kvm_vcpu_after_set_cpuid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_lapic *apic = vcpu->arch.apic;
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 1, 0);
	अगर (best && apic) अणु
		अगर (cpuid_entry_has(best, X86_FEATURE_TSC_DEADLINE_TIMER))
			apic->lapic_समयr.समयr_mode_mask = 3 << 17;
		अन्यथा
			apic->lapic_समयr.समयr_mode_mask = 1 << 17;

		kvm_apic_set_version(vcpu);
	पूर्ण

	best = kvm_find_cpuid_entry(vcpu, 0xD, 0);
	अगर (!best)
		vcpu->arch.guest_supported_xcr0 = 0;
	अन्यथा
		vcpu->arch.guest_supported_xcr0 =
			(best->eax | ((u64)best->edx << 32)) & supported_xcr0;

	/*
	 * Bits 127:0 of the allowed SECS.ATTRIBUTES (CPUID.0x12.0x1) क्रमागतerate
	 * the supported XSAVE Feature Request Mask (XFRM), i.e. the enclave's
	 * requested XCR0 value.  The enclave's XFRM must be a subset of XCRO
	 * at the समय of EENTER, thus adjust the allowed XFRM by the guest's
	 * supported XCR0.  Similar to XCR0 handling, FP and SSE are क्रमced to
	 * '1' even on CPUs that don't support XSAVE.
	 */
	best = kvm_find_cpuid_entry(vcpu, 0x12, 0x1);
	अगर (best) अणु
		best->ecx &= vcpu->arch.guest_supported_xcr0 & 0xffffffff;
		best->edx &= vcpu->arch.guest_supported_xcr0 >> 32;
		best->ecx |= XFEATURE_MASK_FPSSE;
	पूर्ण

	kvm_update_pv_runसमय(vcpu);

	vcpu->arch.maxphyaddr = cpuid_query_maxphyaddr(vcpu);
	vcpu->arch.reserved_gpa_bits = kvm_vcpu_reserved_gpa_bits_raw(vcpu);

	kvm_pmu_refresh(vcpu);
	vcpu->arch.cr4_guest_rsvd_bits =
	    __cr4_reserved_bits(guest_cpuid_has, vcpu);

	kvm_hv_set_cpuid(vcpu);

	/* Invoke the venकरोr callback only after the above state is updated. */
	अटल_call(kvm_x86_vcpu_after_set_cpuid)(vcpu);

	/*
	 * Except क्रम the MMU, which needs to be reset after any venकरोr
	 * specअगरic adjusपंचांगents to the reserved GPA bits.
	 */
	kvm_mmu_reset_context(vcpu);
पूर्ण

अटल पूर्णांक is_efer_nx(व्योम)
अणु
	वापस host_efer & EFER_NX;
पूर्ण

अटल व्योम cpuid_fix_nx_cap(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा kvm_cpuid_entry2 *e, *entry;

	entry = शून्य;
	क्रम (i = 0; i < vcpu->arch.cpuid_nent; ++i) अणु
		e = &vcpu->arch.cpuid_entries[i];
		अगर (e->function == 0x80000001) अणु
			entry = e;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (entry && cpuid_entry_has(entry, X86_FEATURE_NX) && !is_efer_nx()) अणु
		cpuid_entry_clear(entry, X86_FEATURE_NX);
		prपूर्णांकk(KERN_INFO "kvm: guest NX capability removed\n");
	पूर्ण
पूर्ण

पूर्णांक cpuid_query_maxphyaddr(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_cpuid_entry2 *best;

	best = kvm_find_cpuid_entry(vcpu, 0x80000000, 0);
	अगर (!best || best->eax < 0x80000008)
		जाओ not_found;
	best = kvm_find_cpuid_entry(vcpu, 0x80000008, 0);
	अगर (best)
		वापस best->eax & 0xff;
not_found:
	वापस 36;
पूर्ण

/*
 * This "raw" version वापसs the reserved GPA bits without any adjusपंचांगents क्रम
 * encryption technologies that usurp bits.  The raw mask should be used अगर and
 * only अगर hardware करोes _not_ strip the usurped bits, e.g. in भव MTRRs.
 */
u64 kvm_vcpu_reserved_gpa_bits_raw(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस rsvd_bits(cpuid_maxphyaddr(vcpu), 63);
पूर्ण

/* when an old userspace process fills a new kernel module */
पूर्णांक kvm_vcpu_ioctl_set_cpuid(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा kvm_cpuid *cpuid,
			     काष्ठा kvm_cpuid_entry __user *entries)
अणु
	पूर्णांक r, i;
	काष्ठा kvm_cpuid_entry *e = शून्य;
	काष्ठा kvm_cpuid_entry2 *e2 = शून्य;

	अगर (cpuid->nent > KVM_MAX_CPUID_ENTRIES)
		वापस -E2BIG;

	अगर (cpuid->nent) अणु
		e = vmemdup_user(entries, array_size(माप(*e), cpuid->nent));
		अगर (IS_ERR(e))
			वापस PTR_ERR(e);

		e2 = kvदो_स्मृति_array(cpuid->nent, माप(*e2), GFP_KERNEL_ACCOUNT);
		अगर (!e2) अणु
			r = -ENOMEM;
			जाओ out_मुक्त_cpuid;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < cpuid->nent; i++) अणु
		e2[i].function = e[i].function;
		e2[i].eax = e[i].eax;
		e2[i].ebx = e[i].ebx;
		e2[i].ecx = e[i].ecx;
		e2[i].edx = e[i].edx;
		e2[i].index = 0;
		e2[i].flags = 0;
		e2[i].padding[0] = 0;
		e2[i].padding[1] = 0;
		e2[i].padding[2] = 0;
	पूर्ण

	r = kvm_check_cpuid(e2, cpuid->nent);
	अगर (r) अणु
		kvमुक्त(e2);
		जाओ out_मुक्त_cpuid;
	पूर्ण

	kvमुक्त(vcpu->arch.cpuid_entries);
	vcpu->arch.cpuid_entries = e2;
	vcpu->arch.cpuid_nent = cpuid->nent;

	cpuid_fix_nx_cap(vcpu);
	kvm_update_cpuid_runसमय(vcpu);
	kvm_vcpu_after_set_cpuid(vcpu);

out_मुक्त_cpuid:
	kvमुक्त(e);

	वापस r;
पूर्ण

पूर्णांक kvm_vcpu_ioctl_set_cpuid2(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_cpuid2 *cpuid,
			      काष्ठा kvm_cpuid_entry2 __user *entries)
अणु
	काष्ठा kvm_cpuid_entry2 *e2 = शून्य;
	पूर्णांक r;

	अगर (cpuid->nent > KVM_MAX_CPUID_ENTRIES)
		वापस -E2BIG;

	अगर (cpuid->nent) अणु
		e2 = vmemdup_user(entries, array_size(माप(*e2), cpuid->nent));
		अगर (IS_ERR(e2))
			वापस PTR_ERR(e2);
	पूर्ण

	r = kvm_check_cpuid(e2, cpuid->nent);
	अगर (r) अणु
		kvमुक्त(e2);
		वापस r;
	पूर्ण

	kvमुक्त(vcpu->arch.cpuid_entries);
	vcpu->arch.cpuid_entries = e2;
	vcpu->arch.cpuid_nent = cpuid->nent;

	kvm_update_cpuid_runसमय(vcpu);
	kvm_vcpu_after_set_cpuid(vcpu);

	वापस 0;
पूर्ण

पूर्णांक kvm_vcpu_ioctl_get_cpuid2(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_cpuid2 *cpuid,
			      काष्ठा kvm_cpuid_entry2 __user *entries)
अणु
	पूर्णांक r;

	r = -E2BIG;
	अगर (cpuid->nent < vcpu->arch.cpuid_nent)
		जाओ out;
	r = -EFAULT;
	अगर (copy_to_user(entries, vcpu->arch.cpuid_entries,
			 vcpu->arch.cpuid_nent * माप(काष्ठा kvm_cpuid_entry2)))
		जाओ out;
	वापस 0;

out:
	cpuid->nent = vcpu->arch.cpuid_nent;
	वापस r;
पूर्ण

/* Mask kvm_cpu_caps क्रम @leaf with the raw CPUID capabilities of this CPU. */
अटल __always_अंतरभूत व्योम __kvm_cpu_cap_mask(अचिन्हित पूर्णांक leaf)
अणु
	स्थिर काष्ठा cpuid_reg cpuid = x86_feature_cpuid(leaf * 32);
	काष्ठा kvm_cpuid_entry2 entry;

	reverse_cpuid_check(leaf);

	cpuid_count(cpuid.function, cpuid.index,
		    &entry.eax, &entry.ebx, &entry.ecx, &entry.edx);

	kvm_cpu_caps[leaf] &= *__cpuid_entry_get_reg(&entry, cpuid.reg);
पूर्ण

अटल __always_अंतरभूत
व्योम kvm_cpu_cap_init_scattered(क्रमागत kvm_only_cpuid_leafs leaf, u32 mask)
अणु
	/* Use kvm_cpu_cap_mask क्रम non-scattered leafs. */
	BUILD_BUG_ON(leaf < NCAPINTS);

	kvm_cpu_caps[leaf] = mask;

	__kvm_cpu_cap_mask(leaf);
पूर्ण

अटल __always_अंतरभूत व्योम kvm_cpu_cap_mask(क्रमागत cpuid_leafs leaf, u32 mask)
अणु
	/* Use kvm_cpu_cap_init_scattered क्रम scattered leafs. */
	BUILD_BUG_ON(leaf >= NCAPINTS);

	kvm_cpu_caps[leaf] &= mask;

	__kvm_cpu_cap_mask(leaf);
पूर्ण

व्योम kvm_set_cpu_caps(व्योम)
अणु
	अचिन्हित पूर्णांक f_nx = is_efer_nx() ? F(NX) : 0;
#अगर_घोषित CONFIG_X86_64
	अचिन्हित पूर्णांक f_gbpages = F(GBPAGES);
	अचिन्हित पूर्णांक f_lm = F(LM);
#अन्यथा
	अचिन्हित पूर्णांक f_gbpages = 0;
	अचिन्हित पूर्णांक f_lm = 0;
#पूर्ण_अगर
	स_रखो(kvm_cpu_caps, 0, माप(kvm_cpu_caps));

	BUILD_BUG_ON(माप(kvm_cpu_caps) - (NKVMCAPINTS * माप(*kvm_cpu_caps)) >
		     माप(boot_cpu_data.x86_capability));

	स_नकल(&kvm_cpu_caps, &boot_cpu_data.x86_capability,
	       माप(kvm_cpu_caps) - (NKVMCAPINTS * माप(*kvm_cpu_caps)));

	kvm_cpu_cap_mask(CPUID_1_ECX,
		/*
		 * NOTE: MONITOR (and MWAIT) are emulated as NOP, but *not*
		 * advertised to guests via CPUID!
		 */
		F(XMM3) | F(PCLMULQDQ) | 0 /* DTES64, MONITOR */ |
		0 /* DS-CPL, VMX, SMX, EST */ |
		0 /* TM2 */ | F(SSSE3) | 0 /* CNXT-ID */ | 0 /* Reserved */ |
		F(FMA) | F(CX16) | 0 /* xTPR Update */ | F(PDCM) |
		F(PCID) | 0 /* Reserved, DCA */ | F(XMM4_1) |
		F(XMM4_2) | F(X2APIC) | F(MOVBE) | F(POPCNT) |
		0 /* Reserved*/ | F(AES) | F(XSAVE) | 0 /* OSXSAVE */ | F(AVX) |
		F(F16C) | F(RDRAND)
	);
	/* KVM emulates x2apic in software irrespective of host support. */
	kvm_cpu_cap_set(X86_FEATURE_X2APIC);

	kvm_cpu_cap_mask(CPUID_1_EDX,
		F(FPU) | F(VME) | F(DE) | F(PSE) |
		F(TSC) | F(MSR) | F(PAE) | F(MCE) |
		F(CX8) | F(APIC) | 0 /* Reserved */ | F(SEP) |
		F(MTRR) | F(PGE) | F(MCA) | F(CMOV) |
		F(PAT) | F(PSE36) | 0 /* PSN */ | F(CLFLUSH) |
		0 /* Reserved, DS, ACPI */ | F(MMX) |
		F(FXSR) | F(XMM) | F(XMM2) | F(SELFSNOOP) |
		0 /* HTT, TM, Reserved, PBE */
	);

	kvm_cpu_cap_mask(CPUID_7_0_EBX,
		F(FSGSBASE) | F(SGX) | F(BMI1) | F(HLE) | F(AVX2) | F(SMEP) |
		F(BMI2) | F(ERMS) | F(INVPCID) | F(RTM) | 0 /*MPX*/ | F(RDSEED) |
		F(ADX) | F(SMAP) | F(AVX512IFMA) | F(AVX512F) | F(AVX512PF) |
		F(AVX512ER) | F(AVX512CD) | F(CLFLUSHOPT) | F(CLWB) | F(AVX512DQ) |
		F(SHA_NI) | F(AVX512BW) | F(AVX512VL) | 0 /*INTEL_PT*/
	);

	kvm_cpu_cap_mask(CPUID_7_ECX,
		F(AVX512VBMI) | F(LA57) | F(PKU) | 0 /*OSPKE*/ | F(RDPID) |
		F(AVX512_VPOPCNTDQ) | F(UMIP) | F(AVX512_VBMI2) | F(GFNI) |
		F(VAES) | F(VPCLMULQDQ) | F(AVX512_VNNI) | F(AVX512_BITALG) |
		F(CLDEMOTE) | F(MOVसूचीI) | F(MOVसूची64B) | 0 /*WAITPKG*/ |
		F(SGX_LC) | F(BUS_LOCK_DETECT)
	);
	/* Set LA57 based on hardware capability. */
	अगर (cpuid_ecx(7) & F(LA57))
		kvm_cpu_cap_set(X86_FEATURE_LA57);

	/*
	 * PKU not yet implemented क्रम shaकरोw paging and requires OSPKE
	 * to be set on the host. Clear it अगर that is not the हाल
	 */
	अगर (!tdp_enabled || !boot_cpu_has(X86_FEATURE_OSPKE))
		kvm_cpu_cap_clear(X86_FEATURE_PKU);

	kvm_cpu_cap_mask(CPUID_7_EDX,
		F(AVX512_4VNNIW) | F(AVX512_4FMAPS) | F(SPEC_CTRL) |
		F(SPEC_CTRL_SSBD) | F(ARCH_CAPABILITIES) | F(INTEL_STIBP) |
		F(MD_CLEAR) | F(AVX512_VP2INTERSECT) | F(FSRM) |
		F(SERIALIZE) | F(TSXLDTRK) | F(AVX512_FP16)
	);

	/* TSC_ADJUST and ARCH_CAPABILITIES are emulated in software. */
	kvm_cpu_cap_set(X86_FEATURE_TSC_ADJUST);
	kvm_cpu_cap_set(X86_FEATURE_ARCH_CAPABILITIES);

	अगर (boot_cpu_has(X86_FEATURE_IBPB) && boot_cpu_has(X86_FEATURE_IBRS))
		kvm_cpu_cap_set(X86_FEATURE_SPEC_CTRL);
	अगर (boot_cpu_has(X86_FEATURE_STIBP))
		kvm_cpu_cap_set(X86_FEATURE_INTEL_STIBP);
	अगर (boot_cpu_has(X86_FEATURE_AMD_SSBD))
		kvm_cpu_cap_set(X86_FEATURE_SPEC_CTRL_SSBD);

	kvm_cpu_cap_mask(CPUID_7_1_EAX,
		F(AVX_VNNI) | F(AVX512_BF16)
	);

	kvm_cpu_cap_mask(CPUID_D_1_EAX,
		F(XSAVEOPT) | F(XSAVEC) | F(XGETBV1) | F(XSAVES)
	);

	kvm_cpu_cap_init_scattered(CPUID_12_EAX,
		SF(SGX1) | SF(SGX2)
	);

	kvm_cpu_cap_mask(CPUID_8000_0001_ECX,
		F(LAHF_LM) | F(CMP_LEGACY) | 0 /*SVM*/ | 0 /* ExtApicSpace */ |
		F(CR8_LEGACY) | F(ABM) | F(SSE4A) | F(MISALIGNSSE) |
		F(3DNOWPREFETCH) | F(OSVW) | 0 /* IBS */ | F(XOP) |
		0 /* SKINIT, WDT, LWP */ | F(FMA4) | F(TBM) |
		F(TOPOEXT) | F(PERFCTR_CORE)
	);

	kvm_cpu_cap_mask(CPUID_8000_0001_EDX,
		F(FPU) | F(VME) | F(DE) | F(PSE) |
		F(TSC) | F(MSR) | F(PAE) | F(MCE) |
		F(CX8) | F(APIC) | 0 /* Reserved */ | F(SYSCALL) |
		F(MTRR) | F(PGE) | F(MCA) | F(CMOV) |
		F(PAT) | F(PSE36) | 0 /* Reserved */ |
		f_nx | 0 /* Reserved */ | F(MMXEXT) | F(MMX) |
		F(FXSR) | F(FXSR_OPT) | f_gbpages | F(RDTSCP) |
		0 /* Reserved */ | f_lm | F(3DNOWEXT) | F(3DNOW)
	);

	अगर (!tdp_enabled && IS_ENABLED(CONFIG_X86_64))
		kvm_cpu_cap_set(X86_FEATURE_GBPAGES);

	kvm_cpu_cap_mask(CPUID_8000_0008_EBX,
		F(CLZERO) | F(XSAVEERPTR) |
		F(WBNOINVD) | F(AMD_IBPB) | F(AMD_IBRS) | F(AMD_SSBD) | F(VIRT_SSBD) |
		F(AMD_SSB_NO) | F(AMD_STIBP) | F(AMD_STIBP_ALWAYS_ON)
	);

	/*
	 * AMD has separate bits क्रम each SPEC_CTRL bit.
	 * arch/x86/kernel/cpu/bugs.c is kind enough to
	 * record that in cpufeatures so use them.
	 */
	अगर (boot_cpu_has(X86_FEATURE_IBPB))
		kvm_cpu_cap_set(X86_FEATURE_AMD_IBPB);
	अगर (boot_cpu_has(X86_FEATURE_IBRS))
		kvm_cpu_cap_set(X86_FEATURE_AMD_IBRS);
	अगर (boot_cpu_has(X86_FEATURE_STIBP))
		kvm_cpu_cap_set(X86_FEATURE_AMD_STIBP);
	अगर (boot_cpu_has(X86_FEATURE_SPEC_CTRL_SSBD))
		kvm_cpu_cap_set(X86_FEATURE_AMD_SSBD);
	अगर (!boot_cpu_has_bug(X86_BUG_SPEC_STORE_BYPASS))
		kvm_cpu_cap_set(X86_FEATURE_AMD_SSB_NO);
	/*
	 * The preference is to use SPEC CTRL MSR instead of the
	 * VIRT_SPEC MSR.
	 */
	अगर (boot_cpu_has(X86_FEATURE_LS_CFG_SSBD) &&
	    !boot_cpu_has(X86_FEATURE_AMD_SSBD))
		kvm_cpu_cap_set(X86_FEATURE_VIRT_SSBD);

	/*
	 * Hide all SVM features by शेष, SVM will set the cap bits क्रम
	 * features it emulates and/or exposes क्रम L1.
	 */
	kvm_cpu_cap_mask(CPUID_8000_000A_EDX, 0);

	kvm_cpu_cap_mask(CPUID_8000_001F_EAX,
		0 /* SME */ | F(SEV) | 0 /* VM_PAGE_FLUSH */ | F(SEV_ES) |
		F(SME_COHERENT));

	kvm_cpu_cap_mask(CPUID_C000_0001_EDX,
		F(XSTORE) | F(XSTORE_EN) | F(XCRYPT) | F(XCRYPT_EN) |
		F(ACE2) | F(ACE2_EN) | F(PHE) | F(PHE_EN) |
		F(PMM) | F(PMM_EN)
	);

	/*
	 * Hide RDTSCP and RDPID अगर either feature is reported as supported but
	 * probing MSR_TSC_AUX failed.  This is purely a sanity check and
	 * should never happen, but the guest will likely crash अगर RDTSCP or
	 * RDPID is misreported, and KVM has botched MSR_TSC_AUX emulation in
	 * the past.  For example, the sanity check may fire अगर this instance of
	 * KVM is running as L1 on top of an older, broken KVM.
	 */
	अगर (WARN_ON((kvm_cpu_cap_has(X86_FEATURE_RDTSCP) ||
		     kvm_cpu_cap_has(X86_FEATURE_RDPID)) &&
		     !kvm_is_supported_user_वापस_msr(MSR_TSC_AUX))) अणु
		kvm_cpu_cap_clear(X86_FEATURE_RDTSCP);
		kvm_cpu_cap_clear(X86_FEATURE_RDPID);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kvm_set_cpu_caps);

काष्ठा kvm_cpuid_array अणु
	काष्ठा kvm_cpuid_entry2 *entries;
	पूर्णांक maxnent;
	पूर्णांक nent;
पूर्ण;

अटल काष्ठा kvm_cpuid_entry2 *करो_host_cpuid(काष्ठा kvm_cpuid_array *array,
					      u32 function, u32 index)
अणु
	काष्ठा kvm_cpuid_entry2 *entry;

	अगर (array->nent >= array->maxnent)
		वापस शून्य;

	entry = &array->entries[array->nent++];

	entry->function = function;
	entry->index = index;
	entry->flags = 0;

	cpuid_count(entry->function, entry->index,
		    &entry->eax, &entry->ebx, &entry->ecx, &entry->edx);

	चयन (function) अणु
	हाल 4:
	हाल 7:
	हाल 0xb:
	हाल 0xd:
	हाल 0xf:
	हाल 0x10:
	हाल 0x12:
	हाल 0x14:
	हाल 0x17:
	हाल 0x18:
	हाल 0x1f:
	हाल 0x8000001d:
		entry->flags |= KVM_CPUID_FLAG_SIGNIFCANT_INDEX;
		अवरोध;
	पूर्ण

	वापस entry;
पूर्ण

अटल पूर्णांक __करो_cpuid_func_emulated(काष्ठा kvm_cpuid_array *array, u32 func)
अणु
	काष्ठा kvm_cpuid_entry2 *entry;

	अगर (array->nent >= array->maxnent)
		वापस -E2BIG;

	entry = &array->entries[array->nent];
	entry->function = func;
	entry->index = 0;
	entry->flags = 0;

	चयन (func) अणु
	हाल 0:
		entry->eax = 7;
		++array->nent;
		अवरोध;
	हाल 1:
		entry->ecx = F(MOVBE);
		++array->nent;
		अवरोध;
	हाल 7:
		entry->flags |= KVM_CPUID_FLAG_SIGNIFCANT_INDEX;
		entry->eax = 0;
		अगर (kvm_cpu_cap_has(X86_FEATURE_RDTSCP))
			entry->ecx = F(RDPID);
		++array->nent;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __करो_cpuid_func(काष्ठा kvm_cpuid_array *array, u32 function)
अणु
	काष्ठा kvm_cpuid_entry2 *entry;
	पूर्णांक r, i, max_idx;

	/* all calls to cpuid_count() should be made on the same cpu */
	get_cpu();

	r = -E2BIG;

	entry = करो_host_cpuid(array, function, 0);
	अगर (!entry)
		जाओ out;

	चयन (function) अणु
	हाल 0:
		/* Limited to the highest leaf implemented in KVM. */
		entry->eax = min(entry->eax, 0x1fU);
		अवरोध;
	हाल 1:
		cpuid_entry_override(entry, CPUID_1_EDX);
		cpuid_entry_override(entry, CPUID_1_ECX);
		अवरोध;
	हाल 2:
		/*
		 * On ancient CPUs, function 2 entries are STATEFUL.  That is,
		 * CPUID(function=2, index=0) may वापस dअगरferent results each
		 * समय, with the least-signअगरicant byte in EAX क्रमागतerating the
		 * number of बार software should करो CPUID(2, 0).
		 *
		 * Modern CPUs, i.e. every CPU KVM has *ever* run on are less
		 * idiotic.  Intel's SDM states that EAX & 0xff "will always
		 * वापस 01H. Software should ignore this value and not
		 * पूर्णांकerpret it as an inक्रमmational descriptor", जबतक AMD's
		 * APM states that CPUID(2) is reserved.
		 *
		 * WARN अगर a frankenstein CPU that supports भवization and
		 * a stateful CPUID.0x2 is encountered.
		 */
		WARN_ON_ONCE((entry->eax & 0xff) > 1);
		अवरोध;
	/* functions 4 and 0x8000001d have additional index. */
	हाल 4:
	हाल 0x8000001d:
		/*
		 * Read entries until the cache type in the previous entry is
		 * zero, i.e. indicates an invalid entry.
		 */
		क्रम (i = 1; entry->eax & 0x1f; ++i) अणु
			entry = करो_host_cpuid(array, function, i);
			अगर (!entry)
				जाओ out;
		पूर्ण
		अवरोध;
	हाल 6: /* Thermal management */
		entry->eax = 0x4; /* allow ARAT */
		entry->ebx = 0;
		entry->ecx = 0;
		entry->edx = 0;
		अवरोध;
	/* function 7 has additional index. */
	हाल 7:
		entry->eax = min(entry->eax, 1u);
		cpuid_entry_override(entry, CPUID_7_0_EBX);
		cpuid_entry_override(entry, CPUID_7_ECX);
		cpuid_entry_override(entry, CPUID_7_EDX);

		/* KVM only supports 0x7.0 and 0x7.1, capped above via min(). */
		अगर (entry->eax == 1) अणु
			entry = करो_host_cpuid(array, function, 1);
			अगर (!entry)
				जाओ out;

			cpuid_entry_override(entry, CPUID_7_1_EAX);
			entry->ebx = 0;
			entry->ecx = 0;
			entry->edx = 0;
		पूर्ण
		अवरोध;
	हाल 9:
		अवरोध;
	हाल 0xa: अणु /* Architectural Perक्रमmance Monitoring */
		काष्ठा x86_pmu_capability cap;
		जोड़ cpuid10_eax eax;
		जोड़ cpuid10_edx edx;

		perf_get_x86_pmu_capability(&cap);

		/*
		 * Only support guest architectural pmu on a host
		 * with architectural pmu.
		 */
		अगर (!cap.version)
			स_रखो(&cap, 0, माप(cap));

		eax.split.version_id = min(cap.version, 2);
		eax.split.num_counters = cap.num_counters_gp;
		eax.split.bit_width = cap.bit_width_gp;
		eax.split.mask_length = cap.events_mask_len;

		edx.split.num_counters_fixed = min(cap.num_counters_fixed, MAX_FIXED_COUNTERS);
		edx.split.bit_width_fixed = cap.bit_width_fixed;
		edx.split.anythपढ़ो_deprecated = 1;
		edx.split.reserved1 = 0;
		edx.split.reserved2 = 0;

		entry->eax = eax.full;
		entry->ebx = cap.events_mask;
		entry->ecx = 0;
		entry->edx = edx.full;
		अवरोध;
	पूर्ण
	/*
	 * Per Intel's SDM, the 0x1f is a superset of 0xb,
	 * thus they can be handled by common code.
	 */
	हाल 0x1f:
	हाल 0xb:
		/*
		 * Populate entries until the level type (ECX[15:8]) of the
		 * previous entry is zero.  Note, CPUID EAX.अणु0x1f,0xbपूर्ण.0 is
		 * the starting entry, filled by the primary करो_host_cpuid().
		 */
		क्रम (i = 1; entry->ecx & 0xff00; ++i) अणु
			entry = करो_host_cpuid(array, function, i);
			अगर (!entry)
				जाओ out;
		पूर्ण
		अवरोध;
	हाल 0xd:
		entry->eax &= supported_xcr0;
		entry->ebx = xstate_required_size(supported_xcr0, false);
		entry->ecx = entry->ebx;
		entry->edx &= supported_xcr0 >> 32;
		अगर (!supported_xcr0)
			अवरोध;

		entry = करो_host_cpuid(array, function, 1);
		अगर (!entry)
			जाओ out;

		cpuid_entry_override(entry, CPUID_D_1_EAX);
		अगर (entry->eax & (F(XSAVES)|F(XSAVEC)))
			entry->ebx = xstate_required_size(supported_xcr0 | supported_xss,
							  true);
		अन्यथा अणु
			WARN_ON_ONCE(supported_xss != 0);
			entry->ebx = 0;
		पूर्ण
		entry->ecx &= supported_xss;
		entry->edx &= supported_xss >> 32;

		क्रम (i = 2; i < 64; ++i) अणु
			bool s_state;
			अगर (supported_xcr0 & BIT_ULL(i))
				s_state = false;
			अन्यथा अगर (supported_xss & BIT_ULL(i))
				s_state = true;
			अन्यथा
				जारी;

			entry = करो_host_cpuid(array, function, i);
			अगर (!entry)
				जाओ out;

			/*
			 * The supported check above should have filtered out
			 * invalid sub-leafs.  Only valid sub-leafs should
			 * reach this poपूर्णांक, and they should have a non-zero
			 * save state size.  Furthermore, check whether the
			 * processor agrees with supported_xcr0/supported_xss
			 * on whether this is an XCR0- or IA32_XSS-managed area.
			 */
			अगर (WARN_ON_ONCE(!entry->eax || (entry->ecx & 0x1) != s_state)) अणु
				--array->nent;
				जारी;
			पूर्ण
			entry->edx = 0;
		पूर्ण
		अवरोध;
	हाल 0x12:
		/* Intel SGX */
		अगर (!kvm_cpu_cap_has(X86_FEATURE_SGX)) अणु
			entry->eax = entry->ebx = entry->ecx = entry->edx = 0;
			अवरोध;
		पूर्ण

		/*
		 * Index 0: Sub-features, MISCSELECT (a.k.a extended features)
		 * and max enclave sizes.   The SGX sub-features and MISCSELECT
		 * are restricted by kernel and KVM capabilities (like most
		 * feature flags), जबतक enclave size is unrestricted.
		 */
		cpuid_entry_override(entry, CPUID_12_EAX);
		entry->ebx &= SGX_MISC_EXINFO;

		entry = करो_host_cpuid(array, function, 1);
		अगर (!entry)
			जाओ out;

		/*
		 * Index 1: SECS.ATTRIBUTES.  ATTRIBUTES are restricted a la
		 * feature flags.  Advertise all supported flags, including
		 * privileged attributes that require explicit opt-in from
		 * userspace.  ATTRIBUTES.XFRM is not adjusted as userspace is
		 * expected to derive it from supported XCR0.
		 */
		entry->eax &= SGX_ATTR_DEBUG | SGX_ATTR_MODE64BIT |
			      SGX_ATTR_PROVISIONKEY | SGX_ATTR_EINITTOKENKEY |
			      SGX_ATTR_KSS;
		entry->ebx &= 0;
		अवरोध;
	/* Intel PT */
	हाल 0x14:
		अगर (!kvm_cpu_cap_has(X86_FEATURE_INTEL_PT)) अणु
			entry->eax = entry->ebx = entry->ecx = entry->edx = 0;
			अवरोध;
		पूर्ण

		क्रम (i = 1, max_idx = entry->eax; i <= max_idx; ++i) अणु
			अगर (!करो_host_cpuid(array, function, i))
				जाओ out;
		पूर्ण
		अवरोध;
	हाल KVM_CPUID_SIGNATURE: अणु
		अटल स्थिर अक्षर signature[12] = "KVMKVMKVM\0\0";
		स्थिर u32 *sigptr = (स्थिर u32 *)signature;
		entry->eax = KVM_CPUID_FEATURES;
		entry->ebx = sigptr[0];
		entry->ecx = sigptr[1];
		entry->edx = sigptr[2];
		अवरोध;
	पूर्ण
	हाल KVM_CPUID_FEATURES:
		entry->eax = (1 << KVM_FEATURE_CLOCKSOURCE) |
			     (1 << KVM_FEATURE_NOP_IO_DELAY) |
			     (1 << KVM_FEATURE_CLOCKSOURCE2) |
			     (1 << KVM_FEATURE_ASYNC_PF) |
			     (1 << KVM_FEATURE_PV_EOI) |
			     (1 << KVM_FEATURE_CLOCKSOURCE_STABLE_BIT) |
			     (1 << KVM_FEATURE_PV_UNHALT) |
			     (1 << KVM_FEATURE_PV_TLB_FLUSH) |
			     (1 << KVM_FEATURE_ASYNC_PF_VMEXIT) |
			     (1 << KVM_FEATURE_PV_SEND_IPI) |
			     (1 << KVM_FEATURE_POLL_CONTROL) |
			     (1 << KVM_FEATURE_PV_SCHED_YIELD) |
			     (1 << KVM_FEATURE_ASYNC_PF_INT);

		अगर (sched_info_on())
			entry->eax |= (1 << KVM_FEATURE_STEAL_TIME);

		entry->ebx = 0;
		entry->ecx = 0;
		entry->edx = 0;
		अवरोध;
	हाल 0x80000000:
		entry->eax = min(entry->eax, 0x8000001f);
		अवरोध;
	हाल 0x80000001:
		cpuid_entry_override(entry, CPUID_8000_0001_EDX);
		cpuid_entry_override(entry, CPUID_8000_0001_ECX);
		अवरोध;
	हाल 0x80000006:
		/* L2 cache and TLB: pass through host info. */
		अवरोध;
	हाल 0x80000007: /* Advanced घातer management */
		/* invariant TSC is CPUID.80000007H:EDX[8] */
		entry->edx &= (1 << 8);
		/* mask against host */
		entry->edx &= boot_cpu_data.x86_घातer;
		entry->eax = entry->ebx = entry->ecx = 0;
		अवरोध;
	हाल 0x80000008: अणु
		अचिन्हित g_phys_as = (entry->eax >> 16) & 0xff;
		अचिन्हित virt_as = max((entry->eax >> 8) & 0xff, 48U);
		अचिन्हित phys_as = entry->eax & 0xff;

		अगर (!g_phys_as)
			g_phys_as = phys_as;
		entry->eax = g_phys_as | (virt_as << 8);
		entry->edx = 0;
		cpuid_entry_override(entry, CPUID_8000_0008_EBX);
		अवरोध;
	पूर्ण
	हाल 0x8000000A:
		अगर (!kvm_cpu_cap_has(X86_FEATURE_SVM)) अणु
			entry->eax = entry->ebx = entry->ecx = entry->edx = 0;
			अवरोध;
		पूर्ण
		entry->eax = 1; /* SVM revision 1 */
		entry->ebx = 8; /* Lets support 8 ASIDs in हाल we add proper
				   ASID emulation to nested SVM */
		entry->ecx = 0; /* Reserved */
		cpuid_entry_override(entry, CPUID_8000_000A_EDX);
		अवरोध;
	हाल 0x80000019:
		entry->ecx = entry->edx = 0;
		अवरोध;
	हाल 0x8000001a:
	हाल 0x8000001e:
		अवरोध;
	/* Support memory encryption cpuid अगर host supports it */
	हाल 0x8000001F:
		अगर (!kvm_cpu_cap_has(X86_FEATURE_SEV))
			entry->eax = entry->ebx = entry->ecx = entry->edx = 0;
		अन्यथा
			cpuid_entry_override(entry, CPUID_8000_001F_EAX);
		अवरोध;
	/*Add support क्रम Centaur's CPUID inकाष्ठाion*/
	हाल 0xC0000000:
		/*Just support up to 0xC0000004 now*/
		entry->eax = min(entry->eax, 0xC0000004);
		अवरोध;
	हाल 0xC0000001:
		cpuid_entry_override(entry, CPUID_C000_0001_EDX);
		अवरोध;
	हाल 3: /* Processor serial number */
	हाल 5: /* MONITOR/MWAIT */
	हाल 0xC0000002:
	हाल 0xC0000003:
	हाल 0xC0000004:
	शेष:
		entry->eax = entry->ebx = entry->ecx = entry->edx = 0;
		अवरोध;
	पूर्ण

	r = 0;

out:
	put_cpu();

	वापस r;
पूर्ण

अटल पूर्णांक करो_cpuid_func(काष्ठा kvm_cpuid_array *array, u32 func,
			 अचिन्हित पूर्णांक type)
अणु
	अगर (type == KVM_GET_EMULATED_CPUID)
		वापस __करो_cpuid_func_emulated(array, func);

	वापस __करो_cpuid_func(array, func);
पूर्ण

#घोषणा CENTAUR_CPUID_SIGNATURE 0xC0000000

अटल पूर्णांक get_cpuid_func(काष्ठा kvm_cpuid_array *array, u32 func,
			  अचिन्हित पूर्णांक type)
अणु
	u32 limit;
	पूर्णांक r;

	अगर (func == CENTAUR_CPUID_SIGNATURE &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_CENTAUR)
		वापस 0;

	r = करो_cpuid_func(array, func, type);
	अगर (r)
		वापस r;

	limit = array->entries[array->nent - 1].eax;
	क्रम (func = func + 1; func <= limit; ++func) अणु
		r = करो_cpuid_func(array, func, type);
		अगर (r)
			अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल bool sanity_check_entries(काष्ठा kvm_cpuid_entry2 __user *entries,
				 __u32 num_entries, अचिन्हित पूर्णांक ioctl_type)
अणु
	पूर्णांक i;
	__u32 pad[3];

	अगर (ioctl_type != KVM_GET_EMULATED_CPUID)
		वापस false;

	/*
	 * We want to make sure that ->padding is being passed clean from
	 * userspace in हाल we want to use it क्रम something in the future.
	 *
	 * Sadly, this wasn't enक्रमced क्रम KVM_GET_SUPPORTED_CPUID and so we
	 * have to give ourselves satisfied only with the emulated side. /me
	 * sheds a tear.
	 */
	क्रम (i = 0; i < num_entries; i++) अणु
		अगर (copy_from_user(pad, entries[i].padding, माप(pad)))
			वापस true;

		अगर (pad[0] || pad[1] || pad[2])
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक kvm_dev_ioctl_get_cpuid(काष्ठा kvm_cpuid2 *cpuid,
			    काष्ठा kvm_cpuid_entry2 __user *entries,
			    अचिन्हित पूर्णांक type)
अणु
	अटल स्थिर u32 funcs[] = अणु
		0, 0x80000000, CENTAUR_CPUID_SIGNATURE, KVM_CPUID_SIGNATURE,
	पूर्ण;

	काष्ठा kvm_cpuid_array array = अणु
		.nent = 0,
	पूर्ण;
	पूर्णांक r, i;

	अगर (cpuid->nent < 1)
		वापस -E2BIG;
	अगर (cpuid->nent > KVM_MAX_CPUID_ENTRIES)
		cpuid->nent = KVM_MAX_CPUID_ENTRIES;

	अगर (sanity_check_entries(entries, cpuid->nent, type))
		वापस -EINVAL;

	array.entries = vzalloc(array_size(माप(काष्ठा kvm_cpuid_entry2),
					   cpuid->nent));
	अगर (!array.entries)
		वापस -ENOMEM;

	array.maxnent = cpuid->nent;

	क्रम (i = 0; i < ARRAY_SIZE(funcs); i++) अणु
		r = get_cpuid_func(&array, funcs[i], type);
		अगर (r)
			जाओ out_मुक्त;
	पूर्ण
	cpuid->nent = array.nent;

	अगर (copy_to_user(entries, array.entries,
			 array.nent * माप(काष्ठा kvm_cpuid_entry2)))
		r = -EFAULT;

out_मुक्त:
	vमुक्त(array.entries);
	वापस r;
पूर्ण

काष्ठा kvm_cpuid_entry2 *kvm_find_cpuid_entry(काष्ठा kvm_vcpu *vcpu,
					      u32 function, u32 index)
अणु
	वापस cpuid_entry2_find(vcpu->arch.cpuid_entries, vcpu->arch.cpuid_nent,
				 function, index);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_find_cpuid_entry);

/*
 * Intel CPUID semantics treats any query क्रम an out-of-range leaf as अगर the
 * highest basic leaf (i.e. CPUID.0H:EAX) were requested.  AMD CPUID semantics
 * वापसs all zeroes क्रम any undefined leaf, whether or not the leaf is in
 * range.  Centaur/VIA follows Intel semantics.
 *
 * A leaf is considered out-of-range अगर its function is higher than the maximum
 * supported leaf of its associated class or अगर its associated class करोes not
 * exist.
 *
 * There are three primary classes to be considered, with their respective
 * ranges described as "<base> - <top>[,<base2> - <top2>] inclusive.  A primary
 * class exists अगर a guest CPUID entry क्रम its <base> leaf exists.  For a given
 * class, CPUID.<base>.EAX contains the max supported leaf क्रम the class.
 *
 *  - Basic:      0x00000000 - 0x3fffffff, 0x50000000 - 0x7fffffff
 *  - Hypervisor: 0x40000000 - 0x4fffffff
 *  - Extended:   0x80000000 - 0xbfffffff
 *  - Centaur:    0xc0000000 - 0xcfffffff
 *
 * The Hypervisor class is further subभागided पूर्णांकo sub-classes that each act as
 * their own independent class associated with a 0x100 byte range.  E.g. अगर Qemu
 * is advertising support क्रम both HyperV and KVM, the resulting Hypervisor
 * CPUID sub-classes are:
 *
 *  - HyperV:     0x40000000 - 0x400000ff
 *  - KVM:        0x40000100 - 0x400001ff
 */
अटल काष्ठा kvm_cpuid_entry2 *
get_out_of_range_cpuid_entry(काष्ठा kvm_vcpu *vcpu, u32 *fn_ptr, u32 index)
अणु
	काष्ठा kvm_cpuid_entry2 *basic, *class;
	u32 function = *fn_ptr;

	basic = kvm_find_cpuid_entry(vcpu, 0, 0);
	अगर (!basic)
		वापस शून्य;

	अगर (is_guest_venकरोr_amd(basic->ebx, basic->ecx, basic->edx) ||
	    is_guest_venकरोr_hygon(basic->ebx, basic->ecx, basic->edx))
		वापस शून्य;

	अगर (function >= 0x40000000 && function <= 0x4fffffff)
		class = kvm_find_cpuid_entry(vcpu, function & 0xffffff00, 0);
	अन्यथा अगर (function >= 0xc0000000)
		class = kvm_find_cpuid_entry(vcpu, 0xc0000000, 0);
	अन्यथा
		class = kvm_find_cpuid_entry(vcpu, function & 0x80000000, 0);

	अगर (class && function <= class->eax)
		वापस शून्य;

	/*
	 * Leaf specअगरic adjusपंचांगents are also applied when redirecting to the
	 * max basic entry, e.g. अगर the max basic leaf is 0xb but there is no
	 * entry क्रम CPUID.0xb.index (see below), then the output value क्रम EDX
	 * needs to be pulled from CPUID.0xb.1.
	 */
	*fn_ptr = basic->eax;

	/*
	 * The class करोes not exist or the requested function is out of range;
	 * the effective CPUID entry is the max basic leaf.  Note, the index of
	 * the original requested leaf is observed!
	 */
	वापस kvm_find_cpuid_entry(vcpu, basic->eax, index);
पूर्ण

bool kvm_cpuid(काष्ठा kvm_vcpu *vcpu, u32 *eax, u32 *ebx,
	       u32 *ecx, u32 *edx, bool exact_only)
अणु
	u32 orig_function = *eax, function = *eax, index = *ecx;
	काष्ठा kvm_cpuid_entry2 *entry;
	bool exact, used_max_basic = false;

	entry = kvm_find_cpuid_entry(vcpu, function, index);
	exact = !!entry;

	अगर (!entry && !exact_only) अणु
		entry = get_out_of_range_cpuid_entry(vcpu, &function, index);
		used_max_basic = !!entry;
	पूर्ण

	अगर (entry) अणु
		*eax = entry->eax;
		*ebx = entry->ebx;
		*ecx = entry->ecx;
		*edx = entry->edx;
		अगर (function == 7 && index == 0) अणु
			u64 data;
		        अगर (!__kvm_get_msr(vcpu, MSR_IA32_TSX_CTRL, &data, true) &&
			    (data & TSX_CTRL_CPUID_CLEAR))
				*ebx &= ~(F(RTM) | F(HLE));
		पूर्ण
	पूर्ण अन्यथा अणु
		*eax = *ebx = *ecx = *edx = 0;
		/*
		 * When leaf 0BH or 1FH is defined, CL is pass-through
		 * and EDX is always the x2APIC ID, even क्रम undefined
		 * subleaves. Index 1 will exist अगरf the leaf is
		 * implemented, so we pass through CL अगरf leaf 1
		 * exists. EDX can be copied from any existing index.
		 */
		अगर (function == 0xb || function == 0x1f) अणु
			entry = kvm_find_cpuid_entry(vcpu, function, 1);
			अगर (entry) अणु
				*ecx = index & 0xff;
				*edx = entry->edx;
			पूर्ण
		पूर्ण
	पूर्ण
	trace_kvm_cpuid(orig_function, index, *eax, *ebx, *ecx, *edx, exact,
			used_max_basic);
	वापस exact;
पूर्ण
EXPORT_SYMBOL_GPL(kvm_cpuid);

पूर्णांक kvm_emulate_cpuid(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 eax, ebx, ecx, edx;

	अगर (cpuid_fault_enabled(vcpu) && !kvm_require_cpl(vcpu, 0))
		वापस 1;

	eax = kvm_rax_पढ़ो(vcpu);
	ecx = kvm_rcx_पढ़ो(vcpu);
	kvm_cpuid(vcpu, &eax, &ebx, &ecx, &edx, false);
	kvm_rax_ग_लिखो(vcpu, eax);
	kvm_rbx_ग_लिखो(vcpu, ebx);
	kvm_rcx_ग_लिखो(vcpu, ecx);
	kvm_rdx_ग_लिखो(vcpu, edx);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण
EXPORT_SYMBOL_GPL(kvm_emulate_cpuid);
