<शैली गुरु>
#घोषणा pr_fmt(fmt) "SVM: " fmt

#समावेश <linux/kvm_host.h>

#समावेश "irq.h"
#समावेश "mmu.h"
#समावेश "kvm_cache_regs.h"
#समावेश "x86.h"
#समावेश "cpuid.h"
#समावेश "pmu.h"

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/amd-iommu.h>
#समावेश <linux/sched.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/slab.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/objtool.h>
#समावेश <linux/psp-sev.h>
#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/rwsem.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/kvm_para.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/spec-ctrl.h>
#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/traps.h>

#समावेश <यंत्र/virtext.h>
#समावेश "trace.h"

#समावेश "svm.h"
#समावेश "svm_ops.h"

#घोषणा __ex(x) __kvm_handle_fault_on_reboot(x)

MODULE_AUTHOR("Qumranet");
MODULE_LICENSE("GPL");

#अगर_घोषित MODULE
अटल स्थिर काष्ठा x86_cpu_id svm_cpu_id[] = अणु
	X86_MATCH_FEATURE(X86_FEATURE_SVM, शून्य),
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(x86cpu, svm_cpu_id);
#पूर्ण_अगर

#घोषणा SEG_TYPE_LDT 2
#घोषणा SEG_TYPE_BUSY_TSS16 3

#घोषणा SVM_FEATURE_LBRV           (1 <<  1)
#घोषणा SVM_FEATURE_SVML           (1 <<  2)
#घोषणा SVM_FEATURE_TSC_RATE       (1 <<  4)
#घोषणा SVM_FEATURE_VMCB_CLEAN     (1 <<  5)
#घोषणा SVM_FEATURE_FLUSH_ASID     (1 <<  6)
#घोषणा SVM_FEATURE_DECODE_ASSIST  (1 <<  7)
#घोषणा SVM_FEATURE_PAUSE_FILTER   (1 << 10)

#घोषणा DEBUGCTL_RESERVED_BITS (~(0x3fULL))

#घोषणा TSC_RATIO_RSVD          0xffffff0000000000ULL
#घोषणा TSC_RATIO_MIN		0x0000000000000001ULL
#घोषणा TSC_RATIO_MAX		0x000000ffffffffffULL

अटल bool erratum_383_found __पढ़ो_mostly;

u32 msrpm_offsets[MSRPM_OFFSETS] __पढ़ो_mostly;

/*
 * Set osvw_len to higher value when updated Revision Guides
 * are published and we know what the new status bits are
 */
अटल uपूर्णांक64_t osvw_len = 4, osvw_status;

अटल DEFINE_PER_CPU(u64, current_tsc_ratio);
#घोषणा TSC_RATIO_DEFAULT	0x0100000000ULL

अटल स्थिर काष्ठा svm_direct_access_msrs अणु
	u32 index;   /* Index of the MSR */
	bool always; /* True अगर पूर्णांकercept is initially cleared */
पूर्ण direct_access_msrs[MAX_सूचीECT_ACCESS_MSRS] = अणु
	अणु .index = MSR_STAR,				.always = true  पूर्ण,
	अणु .index = MSR_IA32_SYSENTER_CS,		.always = true  पूर्ण,
	अणु .index = MSR_IA32_SYSENTER_EIP,		.always = false पूर्ण,
	अणु .index = MSR_IA32_SYSENTER_ESP,		.always = false पूर्ण,
#अगर_घोषित CONFIG_X86_64
	अणु .index = MSR_GS_BASE,				.always = true  पूर्ण,
	अणु .index = MSR_FS_BASE,				.always = true  पूर्ण,
	अणु .index = MSR_KERNEL_GS_BASE,			.always = true  पूर्ण,
	अणु .index = MSR_LSTAR,				.always = true  पूर्ण,
	अणु .index = MSR_CSTAR,				.always = true  पूर्ण,
	अणु .index = MSR_SYSCALL_MASK,			.always = true  पूर्ण,
#पूर्ण_अगर
	अणु .index = MSR_IA32_SPEC_CTRL,			.always = false पूर्ण,
	अणु .index = MSR_IA32_PRED_CMD,			.always = false पूर्ण,
	अणु .index = MSR_IA32_LASTBRANCHFROMIP,		.always = false पूर्ण,
	अणु .index = MSR_IA32_LASTBRANCHTOIP,		.always = false पूर्ण,
	अणु .index = MSR_IA32_LASTINTFROMIP,		.always = false पूर्ण,
	अणु .index = MSR_IA32_LASTINTTOIP,		.always = false पूर्ण,
	अणु .index = MSR_EFER,				.always = false पूर्ण,
	अणु .index = MSR_IA32_CR_PAT,			.always = false पूर्ण,
	अणु .index = MSR_AMD64_SEV_ES_GHCB,		.always = true  पूर्ण,
	अणु .index = MSR_INVALID,				.always = false पूर्ण,
पूर्ण;

/*
 * These 2 parameters are used to config the controls क्रम Pause-Loop Exiting:
 * छोड़ो_filter_count: On processors that support Pause filtering(indicated
 *	by CPUID Fn8000_000A_EDX), the VMCB provides a 16 bit छोड़ो filter
 *	count value. On VMRUN this value is loaded पूर्णांकo an पूर्णांकernal counter.
 *	Each समय a छोड़ो inकाष्ठाion is executed, this counter is decremented
 *	until it reaches zero at which समय a #VMEXIT is generated अगर छोड़ो
 *	पूर्णांकercept is enabled. Refer to  AMD APM Vol 2 Section 15.14.4 Pause
 *	Intercept Filtering क्रम more details.
 *	This also indicate अगर ple logic enabled.
 *
 * छोड़ो_filter_thresh: In addition, some processor families support advanced
 *	छोड़ो filtering (indicated by CPUID Fn8000_000A_EDX) upper bound on
 *	the amount of समय a guest is allowed to execute in a छोड़ो loop.
 *	In this mode, a 16-bit छोड़ो filter threshold field is added in the
 *	VMCB. The threshold value is a cycle count that is used to reset the
 *	छोड़ो counter. As with simple छोड़ो filtering, VMRUN loads the छोड़ो
 *	count value from VMCB पूर्णांकo an पूर्णांकernal counter. Then, on each छोड़ो
 *	inकाष्ठाion the hardware checks the elapsed number of cycles since
 *	the most recent छोड़ो inकाष्ठाion against the छोड़ो filter threshold.
 *	If the elapsed cycle count is greater than the छोड़ो filter threshold,
 *	then the पूर्णांकernal छोड़ो count is reloaded from the VMCB and execution
 *	जारीs. If the elapsed cycle count is less than the छोड़ो filter
 *	threshold, then the पूर्णांकernal छोड़ो count is decremented. If the count
 *	value is less than zero and PAUSE पूर्णांकercept is enabled, a #VMEXIT is
 *	triggered. If advanced छोड़ो filtering is supported and छोड़ो filter
 *	threshold field is set to zero, the filter will operate in the simpler,
 *	count only mode.
 */

अटल अचिन्हित लघु छोड़ो_filter_thresh = KVM_DEFAULT_PLE_GAP;
module_param(छोड़ो_filter_thresh, uलघु, 0444);

अटल अचिन्हित लघु छोड़ो_filter_count = KVM_SVM_DEFAULT_PLE_WINDOW;
module_param(छोड़ो_filter_count, uलघु, 0444);

/* Default द्विगुनs per-vcpu winकरोw every निकास. */
अटल अचिन्हित लघु छोड़ो_filter_count_grow = KVM_DEFAULT_PLE_WINDOW_GROW;
module_param(छोड़ो_filter_count_grow, uलघु, 0444);

/* Default resets per-vcpu winकरोw every निकास to छोड़ो_filter_count. */
अटल अचिन्हित लघु छोड़ो_filter_count_shrink = KVM_DEFAULT_PLE_WINDOW_SHRINK;
module_param(छोड़ो_filter_count_shrink, uलघु, 0444);

/* Default is to compute the maximum so we can never overflow. */
अटल अचिन्हित लघु छोड़ो_filter_count_max = KVM_SVM_DEFAULT_PLE_WINDOW_MAX;
module_param(छोड़ो_filter_count_max, uलघु, 0444);

/*
 * Use nested page tables by शेष.  Note, NPT may get क्रमced off by
 * svm_hardware_setup() अगर it's unsupported by hardware or the host kernel.
 */
bool npt_enabled = true;
module_param_named(npt, npt_enabled, bool, 0444);

/* allow nested भवization in KVM/SVM */
अटल पूर्णांक nested = true;
module_param(nested, पूर्णांक, S_IRUGO);

/* enable/disable Next RIP Save */
अटल पूर्णांक nrips = true;
module_param(nrips, पूर्णांक, 0444);

/* enable/disable Virtual VMLOAD VMSAVE */
अटल पूर्णांक vls = true;
module_param(vls, पूर्णांक, 0444);

/* enable/disable Virtual GIF */
अटल पूर्णांक vgअगर = true;
module_param(vgअगर, पूर्णांक, 0444);

bool __पढ़ो_mostly dump_invalid_vmcb;
module_param(dump_invalid_vmcb, bool, 0644);

अटल bool svm_gp_erratum_पूर्णांकercept = true;

अटल u8 rsm_ins_bytes[] = "\x0f\xaa";

अटल अचिन्हित दीर्घ iopm_base;

काष्ठा kvm_ldttss_desc अणु
	u16 limit0;
	u16 base0;
	अचिन्हित base1:8, type:5, dpl:2, p:1;
	अचिन्हित limit1:4, zero0:3, g:1, base2:8;
	u32 base3;
	u32 zero1;
पूर्ण __attribute__((packed));

DEFINE_PER_CPU(काष्ठा svm_cpu_data *, svm_data);

/*
 * Only MSR_TSC_AUX is चयनed via the user वापस hook.  EFER is चयनed via
 * the VMCB, and the SYSCALL/SYSENTER MSRs are handled by VMLOAD/VMSAVE.
 *
 * RDTSCP and RDPID are not used in the kernel, specअगरically to allow KVM to
 * defer the restoration of TSC_AUX until the CPU वापसs to userspace.
 */
अटल पूर्णांक tsc_aux_uret_slot __पढ़ो_mostly = -1;

अटल स्थिर u32 msrpm_ranges[] = अणु0, 0xc0000000, 0xc0010000पूर्ण;

#घोषणा NUM_MSR_MAPS ARRAY_SIZE(msrpm_ranges)
#घोषणा MSRS_RANGE_SIZE 2048
#घोषणा MSRS_IN_RANGE (MSRS_RANGE_SIZE * 8 / 2)

u32 svm_msrpm_offset(u32 msr)
अणु
	u32 offset;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_MSR_MAPS; i++) अणु
		अगर (msr < msrpm_ranges[i] ||
		    msr >= msrpm_ranges[i] + MSRS_IN_RANGE)
			जारी;

		offset  = (msr - msrpm_ranges[i]) / 4; /* 4 msrs per u8 */
		offset += (i * MSRS_RANGE_SIZE);       /* add range offset */

		/* Now we have the u8 offset - but need the u32 offset */
		वापस offset / 4;
	पूर्ण

	/* MSR not in any range */
	वापस MSR_INVALID;
पूर्ण

#घोषणा MAX_INST_SIZE 15

अटल पूर्णांक get_max_npt_level(व्योम)
अणु
#अगर_घोषित CONFIG_X86_64
	वापस PT64_ROOT_4LEVEL;
#अन्यथा
	वापस PT32E_ROOT_LEVEL;
#पूर्ण_अगर
पूर्ण

पूर्णांक svm_set_efer(काष्ठा kvm_vcpu *vcpu, u64 efer)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u64 old_efer = vcpu->arch.efer;
	vcpu->arch.efer = efer;

	अगर (!npt_enabled) अणु
		/* Shaकरोw paging assumes NX to be available.  */
		efer |= EFER_NX;

		अगर (!(efer & EFER_LMA))
			efer &= ~EFER_LME;
	पूर्ण

	अगर ((old_efer & EFER_SVME) != (efer & EFER_SVME)) अणु
		अगर (!(efer & EFER_SVME)) अणु
			svm_leave_nested(svm);
			svm_set_gअगर(svm, true);
			/* #GP पूर्णांकercept is still needed क्रम vmware backकरोor */
			अगर (!enable_vmware_backकरोor)
				clr_exception_पूर्णांकercept(svm, GP_VECTOR);

			/*
			 * Free the nested guest state, unless we are in SMM.
			 * In this हाल we will वापस to the nested guest
			 * as soon as we leave SMM.
			 */
			अगर (!is_smm(vcpu))
				svm_मुक्त_nested(svm);

		पूर्ण अन्यथा अणु
			पूर्णांक ret = svm_allocate_nested(svm);

			अगर (ret) अणु
				vcpu->arch.efer = old_efer;
				वापस ret;
			पूर्ण

			अगर (svm_gp_erratum_पूर्णांकercept)
				set_exception_पूर्णांकercept(svm, GP_VECTOR);
		पूर्ण
	पूर्ण

	svm->vmcb->save.efer = efer | EFER_SVME;
	vmcb_mark_dirty(svm->vmcb, VMCB_CR);
	वापस 0;
पूर्ण

अटल पूर्णांक is_बाह्यal_पूर्णांकerrupt(u32 info)
अणु
	info &= SVM_EVTINJ_TYPE_MASK | SVM_EVTINJ_VALID;
	वापस info == (SVM_EVTINJ_VALID | SVM_EVTINJ_TYPE_INTR);
पूर्ण

अटल u32 svm_get_पूर्णांकerrupt_shaकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 ret = 0;

	अगर (svm->vmcb->control.पूर्णांक_state & SVM_INTERRUPT_SHADOW_MASK)
		ret = KVM_X86_SHADOW_INT_STI | KVM_X86_SHADOW_INT_MOV_SS;
	वापस ret;
पूर्ण

अटल व्योम svm_set_पूर्णांकerrupt_shaकरोw(काष्ठा kvm_vcpu *vcpu, पूर्णांक mask)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (mask == 0)
		svm->vmcb->control.पूर्णांक_state &= ~SVM_INTERRUPT_SHADOW_MASK;
	अन्यथा
		svm->vmcb->control.पूर्णांक_state |= SVM_INTERRUPT_SHADOW_MASK;

पूर्ण

अटल पूर्णांक skip_emulated_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * SEV-ES करोes not expose the next RIP. The RIP update is controlled by
	 * the type of निकास and the #VC handler in the guest.
	 */
	अगर (sev_es_guest(vcpu->kvm))
		जाओ करोne;

	अगर (nrips && svm->vmcb->control.next_rip != 0) अणु
		WARN_ON_ONCE(!अटल_cpu_has(X86_FEATURE_NRIPS));
		svm->next_rip = svm->vmcb->control.next_rip;
	पूर्ण

	अगर (!svm->next_rip) अणु
		अगर (!kvm_emulate_inकाष्ठाion(vcpu, EMULTYPE_SKIP))
			वापस 0;
	पूर्ण अन्यथा अणु
		kvm_rip_ग_लिखो(vcpu, svm->next_rip);
	पूर्ण

करोne:
	svm_set_पूर्णांकerrupt_shaकरोw(vcpu, 0);

	वापस 1;
पूर्ण

अटल व्योम svm_queue_exception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अचिन्हित nr = vcpu->arch.exception.nr;
	bool has_error_code = vcpu->arch.exception.has_error_code;
	u32 error_code = vcpu->arch.exception.error_code;

	kvm_deliver_exception_payload(vcpu);

	अगर (nr == BP_VECTOR && !nrips) अणु
		अचिन्हित दीर्घ rip, old_rip = kvm_rip_पढ़ो(vcpu);

		/*
		 * For guest debugging where we have to reinject #BP अगर some
		 * INT3 is guest-owned:
		 * Emulate nRIP by moving RIP क्रमward. Will fail अगर injection
		 * उठाओs a fault that is not पूर्णांकercepted. Still better than
		 * failing in all हालs.
		 */
		(व्योम)skip_emulated_inकाष्ठाion(vcpu);
		rip = kvm_rip_पढ़ो(vcpu);
		svm->पूर्णांक3_rip = rip + svm->vmcb->save.cs.base;
		svm->पूर्णांक3_injected = rip - old_rip;
	पूर्ण

	svm->vmcb->control.event_inj = nr
		| SVM_EVTINJ_VALID
		| (has_error_code ? SVM_EVTINJ_VALID_ERR : 0)
		| SVM_EVTINJ_TYPE_EXEPT;
	svm->vmcb->control.event_inj_err = error_code;
पूर्ण

अटल व्योम svm_init_erratum_383(व्योम)
अणु
	u32 low, high;
	पूर्णांक err;
	u64 val;

	अगर (!अटल_cpu_has_bug(X86_BUG_AMD_TLB_MMATCH))
		वापस;

	/* Use _safe variants to not अवरोध nested भवization */
	val = native_पढ़ो_msr_safe(MSR_AMD64_DC_CFG, &err);
	अगर (err)
		वापस;

	val |= (1ULL << 47);

	low  = lower_32_bits(val);
	high = upper_32_bits(val);

	native_ग_लिखो_msr_safe(MSR_AMD64_DC_CFG, low, high);

	erratum_383_found = true;
पूर्ण

अटल व्योम svm_init_osvw(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * Guests should see errata 400 and 415 as fixed (assuming that
	 * HLT and IO inकाष्ठाions are पूर्णांकercepted).
	 */
	vcpu->arch.osvw.length = (osvw_len >= 3) ? (osvw_len) : 3;
	vcpu->arch.osvw.status = osvw_status & ~(6ULL);

	/*
	 * By increasing VCPU's osvw.length to 3 we are telling the guest that
	 * all osvw.status bits inside that length, including bit 0 (which is
	 * reserved क्रम erratum 298), are valid. However, अगर host processor's
	 * osvw_len is 0 then osvw_status[0] carries no inक्रमmation. We need to
	 * be conservative here and thereक्रमe we tell the guest that erratum 298
	 * is present (because we really करोn't know).
	 */
	अगर (osvw_len == 0 && boot_cpu_data.x86 == 0x10)
		vcpu->arch.osvw.status |= 1;
पूर्ण

अटल पूर्णांक has_svm(व्योम)
अणु
	स्थिर अक्षर *msg;

	अगर (!cpu_has_svm(&msg)) अणु
		prपूर्णांकk(KERN_INFO "has_svm: %s\n", msg);
		वापस 0;
	पूर्ण

	अगर (sev_active()) अणु
		pr_info("KVM is unsupported when running as an SEV guest\n");
		वापस 0;
	पूर्ण

	अगर (pgtable_l5_enabled()) अणु
		pr_info("KVM doesn't yet support 5-level paging on AMD SVM\n");
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम svm_hardware_disable(व्योम)
अणु
	/* Make sure we clean up behind us */
	अगर (अटल_cpu_has(X86_FEATURE_TSCRATEMSR))
		wrmsrl(MSR_AMD64_TSC_RATIO, TSC_RATIO_DEFAULT);

	cpu_svm_disable();

	amd_pmu_disable_virt();
पूर्ण

अटल पूर्णांक svm_hardware_enable(व्योम)
अणु

	काष्ठा svm_cpu_data *sd;
	uपूर्णांक64_t efer;
	काष्ठा desc_काष्ठा *gdt;
	पूर्णांक me = raw_smp_processor_id();

	rdmsrl(MSR_EFER, efer);
	अगर (efer & EFER_SVME)
		वापस -EBUSY;

	अगर (!has_svm()) अणु
		pr_err("%s: err EOPNOTSUPP on %d\n", __func__, me);
		वापस -EINVAL;
	पूर्ण
	sd = per_cpu(svm_data, me);
	अगर (!sd) अणु
		pr_err("%s: svm_data is NULL on %d\n", __func__, me);
		वापस -EINVAL;
	पूर्ण

	sd->asid_generation = 1;
	sd->max_asid = cpuid_ebx(SVM_CPUID_FUNC) - 1;
	sd->next_asid = sd->max_asid + 1;
	sd->min_asid = max_sev_asid + 1;

	gdt = get_current_gdt_rw();
	sd->tss_desc = (काष्ठा kvm_ldttss_desc *)(gdt + GDT_ENTRY_TSS);

	wrmsrl(MSR_EFER, efer | EFER_SVME);

	wrmsrl(MSR_VM_HSAVE_PA, __sme_page_pa(sd->save_area));

	अगर (अटल_cpu_has(X86_FEATURE_TSCRATEMSR)) अणु
		wrmsrl(MSR_AMD64_TSC_RATIO, TSC_RATIO_DEFAULT);
		__this_cpu_ग_लिखो(current_tsc_ratio, TSC_RATIO_DEFAULT);
	पूर्ण


	/*
	 * Get OSVW bits.
	 *
	 * Note that it is possible to have a प्रणाली with mixed processor
	 * revisions and thereक्रमe dअगरferent OSVW bits. If bits are not the same
	 * on dअगरferent processors then choose the worst हाल (i.e. अगर erratum
	 * is present on one processor and not on another then assume that the
	 * erratum is present everywhere).
	 */
	अगर (cpu_has(&boot_cpu_data, X86_FEATURE_OSVW)) अणु
		uपूर्णांक64_t len, status = 0;
		पूर्णांक err;

		len = native_पढ़ो_msr_safe(MSR_AMD64_OSVW_ID_LENGTH, &err);
		अगर (!err)
			status = native_पढ़ो_msr_safe(MSR_AMD64_OSVW_STATUS,
						      &err);

		अगर (err)
			osvw_status = osvw_len = 0;
		अन्यथा अणु
			अगर (len < osvw_len)
				osvw_len = len;
			osvw_status |= status;
			osvw_status &= (1ULL << osvw_len) - 1;
		पूर्ण
	पूर्ण अन्यथा
		osvw_status = osvw_len = 0;

	svm_init_erratum_383();

	amd_pmu_enable_virt();

	वापस 0;
पूर्ण

अटल व्योम svm_cpu_uninit(पूर्णांक cpu)
अणु
	काष्ठा svm_cpu_data *sd = per_cpu(svm_data, cpu);

	अगर (!sd)
		वापस;

	per_cpu(svm_data, cpu) = शून्य;
	kमुक्त(sd->sev_vmcbs);
	__मुक्त_page(sd->save_area);
	kमुक्त(sd);
पूर्ण

अटल पूर्णांक svm_cpu_init(पूर्णांक cpu)
अणु
	काष्ठा svm_cpu_data *sd;
	पूर्णांक ret = -ENOMEM;

	sd = kzalloc(माप(काष्ठा svm_cpu_data), GFP_KERNEL);
	अगर (!sd)
		वापस ret;
	sd->cpu = cpu;
	sd->save_area = alloc_page(GFP_KERNEL);
	अगर (!sd->save_area)
		जाओ मुक्त_cpu_data;

	clear_page(page_address(sd->save_area));

	ret = sev_cpu_init(sd);
	अगर (ret)
		जाओ मुक्त_save_area;

	per_cpu(svm_data, cpu) = sd;

	वापस 0;

मुक्त_save_area:
	__मुक्त_page(sd->save_area);
मुक्त_cpu_data:
	kमुक्त(sd);
	वापस ret;

पूर्ण

अटल पूर्णांक direct_access_msr_slot(u32 msr)
अणु
	u32 i;

	क्रम (i = 0; direct_access_msrs[i].index != MSR_INVALID; i++)
		अगर (direct_access_msrs[i].index == msr)
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल व्योम set_shaकरोw_msr_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu, u32 msr, पूर्णांक पढ़ो,
				     पूर्णांक ग_लिखो)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक slot = direct_access_msr_slot(msr);

	अगर (slot == -ENOENT)
		वापस;

	/* Set the shaकरोw biपंचांगaps to the desired पूर्णांकercept states */
	अगर (पढ़ो)
		set_bit(slot, svm->shaकरोw_msr_पूर्णांकercept.पढ़ो);
	अन्यथा
		clear_bit(slot, svm->shaकरोw_msr_पूर्णांकercept.पढ़ो);

	अगर (ग_लिखो)
		set_bit(slot, svm->shaकरोw_msr_पूर्णांकercept.ग_लिखो);
	अन्यथा
		clear_bit(slot, svm->shaकरोw_msr_पूर्णांकercept.ग_लिखो);
पूर्ण

अटल bool valid_msr_पूर्णांकercept(u32 index)
अणु
	वापस direct_access_msr_slot(index) != -ENOENT;
पूर्ण

अटल bool msr_ग_लिखो_पूर्णांकercepted(काष्ठा kvm_vcpu *vcpu, u32 msr)
अणु
	u8 bit_ग_लिखो;
	अचिन्हित दीर्घ पंचांगp;
	u32 offset;
	u32 *msrpm;

	msrpm = is_guest_mode(vcpu) ? to_svm(vcpu)->nested.msrpm:
				      to_svm(vcpu)->msrpm;

	offset    = svm_msrpm_offset(msr);
	bit_ग_लिखो = 2 * (msr & 0x0f) + 1;
	पंचांगp       = msrpm[offset];

	BUG_ON(offset == MSR_INVALID);

	वापस !!test_bit(bit_ग_लिखो,  &पंचांगp);
पूर्ण

अटल व्योम set_msr_पूर्णांकerception_biपंचांगap(काष्ठा kvm_vcpu *vcpu, u32 *msrpm,
					u32 msr, पूर्णांक पढ़ो, पूर्णांक ग_लिखो)
अणु
	u8 bit_पढ़ो, bit_ग_लिखो;
	अचिन्हित दीर्घ पंचांगp;
	u32 offset;

	/*
	 * If this warning triggers extend the direct_access_msrs list at the
	 * beginning of the file
	 */
	WARN_ON(!valid_msr_पूर्णांकercept(msr));

	/* Enक्रमce non allowed MSRs to trap */
	अगर (पढ़ो && !kvm_msr_allowed(vcpu, msr, KVM_MSR_FILTER_READ))
		पढ़ो = 0;

	अगर (ग_लिखो && !kvm_msr_allowed(vcpu, msr, KVM_MSR_FILTER_WRITE))
		ग_लिखो = 0;

	offset    = svm_msrpm_offset(msr);
	bit_पढ़ो  = 2 * (msr & 0x0f);
	bit_ग_लिखो = 2 * (msr & 0x0f) + 1;
	पंचांगp       = msrpm[offset];

	BUG_ON(offset == MSR_INVALID);

	पढ़ो  ? clear_bit(bit_पढ़ो,  &पंचांगp) : set_bit(bit_पढ़ो,  &पंचांगp);
	ग_लिखो ? clear_bit(bit_ग_लिखो, &पंचांगp) : set_bit(bit_ग_लिखो, &पंचांगp);

	msrpm[offset] = पंचांगp;
पूर्ण

व्योम set_msr_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu, u32 *msrpm, u32 msr,
			  पूर्णांक पढ़ो, पूर्णांक ग_लिखो)
अणु
	set_shaकरोw_msr_पूर्णांकercept(vcpu, msr, पढ़ो, ग_लिखो);
	set_msr_पूर्णांकerception_biपंचांगap(vcpu, msrpm, msr, पढ़ो, ग_लिखो);
पूर्ण

u32 *svm_vcpu_alloc_msrpm(व्योम)
अणु
	अचिन्हित पूर्णांक order = get_order(MSRPM_SIZE);
	काष्ठा page *pages = alloc_pages(GFP_KERNEL_ACCOUNT, order);
	u32 *msrpm;

	अगर (!pages)
		वापस शून्य;

	msrpm = page_address(pages);
	स_रखो(msrpm, 0xff, PAGE_SIZE * (1 << order));

	वापस msrpm;
पूर्ण

व्योम svm_vcpu_init_msrpm(काष्ठा kvm_vcpu *vcpu, u32 *msrpm)
अणु
	पूर्णांक i;

	क्रम (i = 0; direct_access_msrs[i].index != MSR_INVALID; i++) अणु
		अगर (!direct_access_msrs[i].always)
			जारी;
		set_msr_पूर्णांकerception(vcpu, msrpm, direct_access_msrs[i].index, 1, 1);
	पूर्ण
पूर्ण


व्योम svm_vcpu_मुक्त_msrpm(u32 *msrpm)
अणु
	__मुक्त_pages(virt_to_page(msrpm), get_order(MSRPM_SIZE));
पूर्ण

अटल व्योम svm_msr_filter_changed(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 i;

	/*
	 * Set पूर्णांकercept permissions क्रम all direct access MSRs again. They
	 * will स्वतःmatically get filtered through the MSR filter, so we are
	 * back in sync after this.
	 */
	क्रम (i = 0; direct_access_msrs[i].index != MSR_INVALID; i++) अणु
		u32 msr = direct_access_msrs[i].index;
		u32 पढ़ो = test_bit(i, svm->shaकरोw_msr_पूर्णांकercept.पढ़ो);
		u32 ग_लिखो = test_bit(i, svm->shaकरोw_msr_पूर्णांकercept.ग_लिखो);

		set_msr_पूर्णांकerception_biपंचांगap(vcpu, svm->msrpm, msr, पढ़ो, ग_लिखो);
	पूर्ण
पूर्ण

अटल व्योम add_msr_offset(u32 offset)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MSRPM_OFFSETS; ++i) अणु

		/* Offset alपढ़ोy in list? */
		अगर (msrpm_offsets[i] == offset)
			वापस;

		/* Slot used by another offset? */
		अगर (msrpm_offsets[i] != MSR_INVALID)
			जारी;

		/* Add offset to list */
		msrpm_offsets[i] = offset;

		वापस;
	पूर्ण

	/*
	 * If this BUG triggers the msrpm_offsets table has an overflow. Just
	 * increase MSRPM_OFFSETS in this हाल.
	 */
	BUG();
पूर्ण

अटल व्योम init_msrpm_offsets(व्योम)
अणु
	पूर्णांक i;

	स_रखो(msrpm_offsets, 0xff, माप(msrpm_offsets));

	क्रम (i = 0; direct_access_msrs[i].index != MSR_INVALID; i++) अणु
		u32 offset;

		offset = svm_msrpm_offset(direct_access_msrs[i].index);
		BUG_ON(offset == MSR_INVALID);

		add_msr_offset(offset);
	पूर्ण
पूर्ण

अटल व्योम svm_enable_lbrv(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->control.virt_ext |= LBR_CTL_ENABLE_MASK;
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTBRANCHFROMIP, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTBRANCHTOIP, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTINTFROMIP, 1, 1);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTINTTOIP, 1, 1);
पूर्ण

अटल व्योम svm_disable_lbrv(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->control.virt_ext &= ~LBR_CTL_ENABLE_MASK;
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTBRANCHFROMIP, 0, 0);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTBRANCHTOIP, 0, 0);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTINTFROMIP, 0, 0);
	set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_LASTINTTOIP, 0, 0);
पूर्ण

व्योम disable_nmi_singlestep(काष्ठा vcpu_svm *svm)
अणु
	svm->nmi_singlestep = false;

	अगर (!(svm->vcpu.guest_debug & KVM_GUESTDBG_SINGLESTEP)) अणु
		/* Clear our flags अगर they were not set by the guest */
		अगर (!(svm->nmi_singlestep_guest_rflags & X86_EFLAGS_TF))
			svm->vmcb->save.rflags &= ~X86_EFLAGS_TF;
		अगर (!(svm->nmi_singlestep_guest_rflags & X86_EFLAGS_RF))
			svm->vmcb->save.rflags &= ~X86_EFLAGS_RF;
	पूर्ण
पूर्ण

अटल व्योम grow_ple_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	पूर्णांक old = control->छोड़ो_filter_count;

	control->छोड़ो_filter_count = __grow_ple_winकरोw(old,
							छोड़ो_filter_count,
							छोड़ो_filter_count_grow,
							छोड़ो_filter_count_max);

	अगर (control->छोड़ो_filter_count != old) अणु
		vmcb_mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
		trace_kvm_ple_winकरोw_update(vcpu->vcpu_id,
					    control->छोड़ो_filter_count, old);
	पूर्ण
पूर्ण

अटल व्योम shrink_ple_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	पूर्णांक old = control->छोड़ो_filter_count;

	control->छोड़ो_filter_count =
				__shrink_ple_winकरोw(old,
						    छोड़ो_filter_count,
						    छोड़ो_filter_count_shrink,
						    छोड़ो_filter_count);
	अगर (control->छोड़ो_filter_count != old) अणु
		vmcb_mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
		trace_kvm_ple_winकरोw_update(vcpu->vcpu_id,
					    control->छोड़ो_filter_count, old);
	पूर्ण
पूर्ण

/*
 * The शेष MMIO mask is a single bit (excluding the present bit),
 * which could conflict with the memory encryption bit. Check क्रम
 * memory encryption support and override the शेष MMIO mask अगर
 * memory encryption is enabled.
 */
अटल __init व्योम svm_adjust_mmio_mask(व्योम)
अणु
	अचिन्हित पूर्णांक enc_bit, mask_bit;
	u64 msr, mask;

	/* If there is no memory encryption support, use existing mask */
	अगर (cpuid_eax(0x80000000) < 0x8000001f)
		वापस;

	/* If memory encryption is not enabled, use existing mask */
	rdmsrl(MSR_AMD64_SYSCFG, msr);
	अगर (!(msr & MSR_AMD64_SYSCFG_MEM_ENCRYPT))
		वापस;

	enc_bit = cpuid_ebx(0x8000001f) & 0x3f;
	mask_bit = boot_cpu_data.x86_phys_bits;

	/* Increment the mask bit अगर it is the same as the encryption bit */
	अगर (enc_bit == mask_bit)
		mask_bit++;

	/*
	 * If the mask bit location is below 52, then some bits above the
	 * physical addressing limit will always be reserved, so use the
	 * rsvd_bits() function to generate the mask. This mask, aदीर्घ with
	 * the present bit, will be used to generate a page fault with
	 * PFER.RSV = 1.
	 *
	 * If the mask bit location is 52 (or above), then clear the mask.
	 */
	mask = (mask_bit < 52) ? rsvd_bits(mask_bit, 51) | PT_PRESENT_MASK : 0;

	kvm_mmu_set_mmio_spte_mask(mask, mask, PT_WRITABLE_MASK | PT_USER_MASK);
पूर्ण

अटल व्योम svm_hardware_tearकरोwn(व्योम)
अणु
	पूर्णांक cpu;

	sev_hardware_tearकरोwn();

	क्रम_each_possible_cpu(cpu)
		svm_cpu_uninit(cpu);

	__मुक्त_pages(pfn_to_page(iopm_base >> PAGE_SHIFT),
	get_order(IOPM_SIZE));
	iopm_base = 0;
पूर्ण

अटल __init व्योम svm_set_cpu_caps(व्योम)
अणु
	kvm_set_cpu_caps();

	supported_xss = 0;

	/* CPUID 0x80000001 and 0x8000000A (SVM features) */
	अगर (nested) अणु
		kvm_cpu_cap_set(X86_FEATURE_SVM);

		अगर (nrips)
			kvm_cpu_cap_set(X86_FEATURE_NRIPS);

		अगर (npt_enabled)
			kvm_cpu_cap_set(X86_FEATURE_NPT);

		/* Nested VM can receive #VMEXIT instead of triggering #GP */
		kvm_cpu_cap_set(X86_FEATURE_SVME_ADDR_CHK);
	पूर्ण

	/* CPUID 0x80000008 */
	अगर (boot_cpu_has(X86_FEATURE_LS_CFG_SSBD) ||
	    boot_cpu_has(X86_FEATURE_AMD_SSBD))
		kvm_cpu_cap_set(X86_FEATURE_VIRT_SSBD);

	/* CPUID 0x8000001F (SME/SEV features) */
	sev_set_cpu_caps();
पूर्ण

अटल __init पूर्णांक svm_hardware_setup(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा page *iopm_pages;
	व्योम *iopm_va;
	पूर्णांक r;
	अचिन्हित पूर्णांक order = get_order(IOPM_SIZE);

	iopm_pages = alloc_pages(GFP_KERNEL, order);

	अगर (!iopm_pages)
		वापस -ENOMEM;

	iopm_va = page_address(iopm_pages);
	स_रखो(iopm_va, 0xff, PAGE_SIZE * (1 << order));
	iopm_base = page_to_pfn(iopm_pages) << PAGE_SHIFT;

	init_msrpm_offsets();

	supported_xcr0 &= ~(XFEATURE_MASK_BNDREGS | XFEATURE_MASK_BNDCSR);

	अगर (boot_cpu_has(X86_FEATURE_NX))
		kvm_enable_efer_bits(EFER_NX);

	अगर (boot_cpu_has(X86_FEATURE_FXSR_OPT))
		kvm_enable_efer_bits(EFER_FFXSR);

	अगर (boot_cpu_has(X86_FEATURE_TSCRATEMSR)) अणु
		kvm_has_tsc_control = true;
		kvm_max_tsc_scaling_ratio = TSC_RATIO_MAX;
		kvm_tsc_scaling_ratio_frac_bits = 32;
	पूर्ण

	tsc_aux_uret_slot = kvm_add_user_वापस_msr(MSR_TSC_AUX);

	/* Check क्रम छोड़ो filtering support */
	अगर (!boot_cpu_has(X86_FEATURE_PAUSEFILTER)) अणु
		छोड़ो_filter_count = 0;
		छोड़ो_filter_thresh = 0;
	पूर्ण अन्यथा अगर (!boot_cpu_has(X86_FEATURE_PFTHRESHOLD)) अणु
		छोड़ो_filter_thresh = 0;
	पूर्ण

	अगर (nested) अणु
		prपूर्णांकk(KERN_INFO "kvm: Nested Virtualization enabled\n");
		kvm_enable_efer_bits(EFER_SVME | EFER_LMSLE);
	पूर्ण

	/*
	 * KVM's MMU doesn't support using 2-level paging क्रम itself, and thus
	 * NPT isn't supported अगर the host is using 2-level paging since host
	 * CR4 is unchanged on VMRUN.
	 */
	अगर (!IS_ENABLED(CONFIG_X86_64) && !IS_ENABLED(CONFIG_X86_PAE))
		npt_enabled = false;

	अगर (!boot_cpu_has(X86_FEATURE_NPT))
		npt_enabled = false;

	kvm_configure_mmu(npt_enabled, get_max_npt_level(), PG_LEVEL_1G);
	pr_info("kvm: Nested Paging %sabled\n", npt_enabled ? "en" : "dis");

	/* Note, SEV setup consumes npt_enabled. */
	sev_hardware_setup();

	svm_adjust_mmio_mask();

	क्रम_each_possible_cpu(cpu) अणु
		r = svm_cpu_init(cpu);
		अगर (r)
			जाओ err;
	पूर्ण

	अगर (nrips) अणु
		अगर (!boot_cpu_has(X86_FEATURE_NRIPS))
			nrips = false;
	पूर्ण

	अगर (avic) अणु
		अगर (!npt_enabled || !boot_cpu_has(X86_FEATURE_AVIC)) अणु
			avic = false;
		पूर्ण अन्यथा अणु
			pr_info("AVIC enabled\n");

			amd_iommu_रेजिस्टर_ga_log_notअगरier(&avic_ga_log_notअगरier);
		पूर्ण
	पूर्ण

	अगर (vls) अणु
		अगर (!npt_enabled ||
		    !boot_cpu_has(X86_FEATURE_V_VMSAVE_VMLOAD) ||
		    !IS_ENABLED(CONFIG_X86_64)) अणु
			vls = false;
		पूर्ण अन्यथा अणु
			pr_info("Virtual VMLOAD VMSAVE supported\n");
		पूर्ण
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_SVME_ADDR_CHK))
		svm_gp_erratum_पूर्णांकercept = false;

	अगर (vgअगर) अणु
		अगर (!boot_cpu_has(X86_FEATURE_VGIF))
			vgअगर = false;
		अन्यथा
			pr_info("Virtual GIF supported\n");
	पूर्ण

	svm_set_cpu_caps();

	/*
	 * It seems that on AMD processors PTE's accessed bit is
	 * being set by the CPU hardware beक्रमe the NPF vmनिकास.
	 * This is not expected behaviour and our tests fail because
	 * of it.
	 * A workaround here is to disable support क्रम
	 * GUEST_MAXPHYADDR < HOST_MAXPHYADDR अगर NPT is enabled.
	 * In this हाल userspace can know अगर there is support using
	 * KVM_CAP_SMALLER_MAXPHYADDR extension and decide how to handle
	 * it
	 * If future AMD CPU models change the behaviour described above,
	 * this variable can be changed accordingly
	 */
	allow_smaller_maxphyaddr = !npt_enabled;

	वापस 0;

err:
	svm_hardware_tearकरोwn();
	वापस r;
पूर्ण

अटल व्योम init_seg(काष्ठा vmcb_seg *seg)
अणु
	seg->selector = 0;
	seg->attrib = SVM_SELECTOR_P_MASK | SVM_SELECTOR_S_MASK |
		      SVM_SELECTOR_WRITE_MASK; /* Read/Write Data Segment */
	seg->limit = 0xffff;
	seg->base = 0;
पूर्ण

अटल व्योम init_sys_seg(काष्ठा vmcb_seg *seg, uपूर्णांक32_t type)
अणु
	seg->selector = 0;
	seg->attrib = SVM_SELECTOR_P_MASK | type;
	seg->limit = 0xffff;
	seg->base = 0;
पूर्ण

अटल u64 svm_ग_लिखो_l1_tsc_offset(काष्ठा kvm_vcpu *vcpu, u64 offset)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u64 g_tsc_offset = 0;

	अगर (is_guest_mode(vcpu)) अणु
		/* Write L1's TSC offset.  */
		g_tsc_offset = svm->vmcb->control.tsc_offset -
			       svm->vmcb01.ptr->control.tsc_offset;
		svm->vmcb01.ptr->control.tsc_offset = offset;
	पूर्ण

	trace_kvm_ग_लिखो_tsc_offset(vcpu->vcpu_id,
				   svm->vmcb->control.tsc_offset - g_tsc_offset,
				   offset);

	svm->vmcb->control.tsc_offset = offset + g_tsc_offset;

	vmcb_mark_dirty(svm->vmcb, VMCB_INTERCEPTS);
	वापस svm->vmcb->control.tsc_offset;
पूर्ण

/* Evaluate inकाष्ठाion पूर्णांकercepts that depend on guest CPUID features. */
अटल व्योम svm_recalc_inकाष्ठाion_पूर्णांकercepts(काष्ठा kvm_vcpu *vcpu,
					      काष्ठा vcpu_svm *svm)
अणु
	/*
	 * Intercept INVPCID अगर shaकरोw paging is enabled to sync/मुक्त shaकरोw
	 * roots, or अगर INVPCID is disabled in the guest to inject #UD.
	 */
	अगर (kvm_cpu_cap_has(X86_FEATURE_INVPCID)) अणु
		अगर (!npt_enabled ||
		    !guest_cpuid_has(&svm->vcpu, X86_FEATURE_INVPCID))
			svm_set_पूर्णांकercept(svm, INTERCEPT_INVPCID);
		अन्यथा
			svm_clr_पूर्णांकercept(svm, INTERCEPT_INVPCID);
	पूर्ण

	अगर (kvm_cpu_cap_has(X86_FEATURE_RDTSCP)) अणु
		अगर (guest_cpuid_has(vcpu, X86_FEATURE_RDTSCP))
			svm_clr_पूर्णांकercept(svm, INTERCEPT_RDTSCP);
		अन्यथा
			svm_set_पूर्णांकercept(svm, INTERCEPT_RDTSCP);
	पूर्ण
पूर्ण

अटल व्योम init_vmcb(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	काष्ठा vmcb_save_area *save = &svm->vmcb->save;

	vcpu->arch.hflags = 0;

	svm_set_पूर्णांकercept(svm, INTERCEPT_CR0_READ);
	svm_set_पूर्णांकercept(svm, INTERCEPT_CR3_READ);
	svm_set_पूर्णांकercept(svm, INTERCEPT_CR4_READ);
	svm_set_पूर्णांकercept(svm, INTERCEPT_CR0_WRITE);
	svm_set_पूर्णांकercept(svm, INTERCEPT_CR3_WRITE);
	svm_set_पूर्णांकercept(svm, INTERCEPT_CR4_WRITE);
	अगर (!kvm_vcpu_apicv_active(vcpu))
		svm_set_पूर्णांकercept(svm, INTERCEPT_CR8_WRITE);

	set_dr_पूर्णांकercepts(svm);

	set_exception_पूर्णांकercept(svm, PF_VECTOR);
	set_exception_पूर्णांकercept(svm, UD_VECTOR);
	set_exception_पूर्णांकercept(svm, MC_VECTOR);
	set_exception_पूर्णांकercept(svm, AC_VECTOR);
	set_exception_पूर्णांकercept(svm, DB_VECTOR);
	/*
	 * Guest access to VMware backकरोor ports could legitimately
	 * trigger #GP because of TSS I/O permission biपंचांगap.
	 * We पूर्णांकercept those #GP and allow access to them anyway
	 * as VMware करोes.
	 */
	अगर (enable_vmware_backकरोor)
		set_exception_पूर्णांकercept(svm, GP_VECTOR);

	svm_set_पूर्णांकercept(svm, INTERCEPT_INTR);
	svm_set_पूर्णांकercept(svm, INTERCEPT_NMI);
	svm_set_पूर्णांकercept(svm, INTERCEPT_SMI);
	svm_set_पूर्णांकercept(svm, INTERCEPT_SELECTIVE_CR0);
	svm_set_पूर्णांकercept(svm, INTERCEPT_RDPMC);
	svm_set_पूर्णांकercept(svm, INTERCEPT_CPUID);
	svm_set_पूर्णांकercept(svm, INTERCEPT_INVD);
	svm_set_पूर्णांकercept(svm, INTERCEPT_INVLPG);
	svm_set_पूर्णांकercept(svm, INTERCEPT_INVLPGA);
	svm_set_पूर्णांकercept(svm, INTERCEPT_IOIO_PROT);
	svm_set_पूर्णांकercept(svm, INTERCEPT_MSR_PROT);
	svm_set_पूर्णांकercept(svm, INTERCEPT_TASK_SWITCH);
	svm_set_पूर्णांकercept(svm, INTERCEPT_SHUTDOWN);
	svm_set_पूर्णांकercept(svm, INTERCEPT_VMRUN);
	svm_set_पूर्णांकercept(svm, INTERCEPT_VMMCALL);
	svm_set_पूर्णांकercept(svm, INTERCEPT_VMLOAD);
	svm_set_पूर्णांकercept(svm, INTERCEPT_VMSAVE);
	svm_set_पूर्णांकercept(svm, INTERCEPT_STGI);
	svm_set_पूर्णांकercept(svm, INTERCEPT_CLGI);
	svm_set_पूर्णांकercept(svm, INTERCEPT_SKINIT);
	svm_set_पूर्णांकercept(svm, INTERCEPT_WBINVD);
	svm_set_पूर्णांकercept(svm, INTERCEPT_XSETBV);
	svm_set_पूर्णांकercept(svm, INTERCEPT_RDPRU);
	svm_set_पूर्णांकercept(svm, INTERCEPT_RSM);

	अगर (!kvm_mरुको_in_guest(vcpu->kvm)) अणु
		svm_set_पूर्णांकercept(svm, INTERCEPT_MONITOR);
		svm_set_पूर्णांकercept(svm, INTERCEPT_MWAIT);
	पूर्ण

	अगर (!kvm_hlt_in_guest(vcpu->kvm))
		svm_set_पूर्णांकercept(svm, INTERCEPT_HLT);

	control->iopm_base_pa = __sme_set(iopm_base);
	control->msrpm_base_pa = __sme_set(__pa(svm->msrpm));
	control->पूर्णांक_ctl = V_INTR_MASKING_MASK;

	init_seg(&save->es);
	init_seg(&save->ss);
	init_seg(&save->ds);
	init_seg(&save->fs);
	init_seg(&save->gs);

	save->cs.selector = 0xf000;
	save->cs.base = 0xffff0000;
	/* Executable/Readable Code Segment */
	save->cs.attrib = SVM_SELECTOR_READ_MASK | SVM_SELECTOR_P_MASK |
		SVM_SELECTOR_S_MASK | SVM_SELECTOR_CODE_MASK;
	save->cs.limit = 0xffff;

	save->gdtr.limit = 0xffff;
	save->idtr.limit = 0xffff;

	init_sys_seg(&save->ldtr, SEG_TYPE_LDT);
	init_sys_seg(&save->tr, SEG_TYPE_BUSY_TSS16);

	svm_set_cr4(vcpu, 0);
	svm_set_efer(vcpu, 0);
	save->dr6 = 0xffff0ff0;
	kvm_set_rflags(vcpu, X86_EFLAGS_FIXED);
	save->rip = 0x0000fff0;
	vcpu->arch.regs[VCPU_REGS_RIP] = save->rip;

	/*
	 * svm_set_cr0() sets PG and WP and clears NW and CD on save->cr0.
	 * It also updates the guest-visible cr0 value.
	 */
	svm_set_cr0(vcpu, X86_CR0_NW | X86_CR0_CD | X86_CR0_ET);
	kvm_mmu_reset_context(vcpu);

	save->cr4 = X86_CR4_PAE;
	/* rdx = ?? */

	अगर (npt_enabled) अणु
		/* Setup VMCB क्रम Nested Paging */
		control->nested_ctl |= SVM_NESTED_CTL_NP_ENABLE;
		svm_clr_पूर्णांकercept(svm, INTERCEPT_INVLPG);
		clr_exception_पूर्णांकercept(svm, PF_VECTOR);
		svm_clr_पूर्णांकercept(svm, INTERCEPT_CR3_READ);
		svm_clr_पूर्णांकercept(svm, INTERCEPT_CR3_WRITE);
		save->g_pat = vcpu->arch.pat;
		save->cr3 = 0;
		save->cr4 = 0;
	पूर्ण
	svm->current_vmcb->asid_generation = 0;
	svm->asid = 0;

	svm->nested.vmcb12_gpa = INVALID_GPA;
	svm->nested.last_vmcb12_gpa = INVALID_GPA;
	vcpu->arch.hflags = 0;

	अगर (!kvm_छोड़ो_in_guest(vcpu->kvm)) अणु
		control->छोड़ो_filter_count = छोड़ो_filter_count;
		अगर (छोड़ो_filter_thresh)
			control->छोड़ो_filter_thresh = छोड़ो_filter_thresh;
		svm_set_पूर्णांकercept(svm, INTERCEPT_PAUSE);
	पूर्ण अन्यथा अणु
		svm_clr_पूर्णांकercept(svm, INTERCEPT_PAUSE);
	पूर्ण

	svm_recalc_inकाष्ठाion_पूर्णांकercepts(vcpu, svm);

	/*
	 * If the host supports V_SPEC_CTRL then disable the पूर्णांकerception
	 * of MSR_IA32_SPEC_CTRL.
	 */
	अगर (boot_cpu_has(X86_FEATURE_V_SPEC_CTRL))
		set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_SPEC_CTRL, 1, 1);

	अगर (kvm_vcpu_apicv_active(vcpu))
		avic_init_vmcb(svm);

	अगर (vgअगर) अणु
		svm_clr_पूर्णांकercept(svm, INTERCEPT_STGI);
		svm_clr_पूर्णांकercept(svm, INTERCEPT_CLGI);
		svm->vmcb->control.पूर्णांक_ctl |= V_GIF_ENABLE_MASK;
	पूर्ण

	अगर (sev_guest(vcpu->kvm)) अणु
		svm->vmcb->control.nested_ctl |= SVM_NESTED_CTL_SEV_ENABLE;
		clr_exception_पूर्णांकercept(svm, UD_VECTOR);

		अगर (sev_es_guest(vcpu->kvm)) अणु
			/* Perक्रमm SEV-ES specअगरic VMCB updates */
			sev_es_init_vmcb(svm);
		पूर्ण
	पूर्ण

	vmcb_mark_all_dirty(svm->vmcb);

	enable_gअगर(svm);

पूर्ण

अटल व्योम svm_vcpu_reset(काष्ठा kvm_vcpu *vcpu, bool init_event)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 dummy;
	u32 eax = 1;

	svm->spec_ctrl = 0;
	svm->virt_spec_ctrl = 0;

	अगर (!init_event) अणु
		vcpu->arch.apic_base = APIC_DEFAULT_PHYS_BASE |
				       MSR_IA32_APICBASE_ENABLE;
		अगर (kvm_vcpu_is_reset_bsp(vcpu))
			vcpu->arch.apic_base |= MSR_IA32_APICBASE_BSP;
	पूर्ण
	init_vmcb(vcpu);

	kvm_cpuid(vcpu, &eax, &dummy, &dummy, &dummy, false);
	kvm_rdx_ग_लिखो(vcpu, eax);

	अगर (kvm_vcpu_apicv_active(vcpu) && !init_event)
		avic_update_vapic_bar(svm, APIC_DEFAULT_PHYS_BASE);
पूर्ण

व्योम svm_चयन_vmcb(काष्ठा vcpu_svm *svm, काष्ठा kvm_vmcb_info *target_vmcb)
अणु
	svm->current_vmcb = target_vmcb;
	svm->vmcb = target_vmcb->ptr;
पूर्ण

अटल पूर्णांक svm_create_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm;
	काष्ठा page *vmcb01_page;
	काष्ठा page *vmsa_page = शून्य;
	पूर्णांक err;

	BUILD_BUG_ON(दुरत्व(काष्ठा vcpu_svm, vcpu) != 0);
	svm = to_svm(vcpu);

	err = -ENOMEM;
	vmcb01_page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!vmcb01_page)
		जाओ out;

	अगर (sev_es_guest(vcpu->kvm)) अणु
		/*
		 * SEV-ES guests require a separate VMSA page used to contain
		 * the encrypted रेजिस्टर state of the guest.
		 */
		vmsa_page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
		अगर (!vmsa_page)
			जाओ error_मुक्त_vmcb_page;

		/*
		 * SEV-ES guests मुख्यtain an encrypted version of their FPU
		 * state which is restored and saved on VMRUN and VMEXIT.
		 * Free the fpu काष्ठाure to prevent KVM from attempting to
		 * access the FPU state.
		 */
		kvm_मुक्त_guest_fpu(vcpu);
	पूर्ण

	err = avic_init_vcpu(svm);
	अगर (err)
		जाओ error_मुक्त_vmsa_page;

	/* We initialize this flag to true to make sure that the is_running
	 * bit would be set the first समय the vcpu is loaded.
	 */
	अगर (irqchip_in_kernel(vcpu->kvm) && kvm_apicv_activated(vcpu->kvm))
		svm->avic_is_running = true;

	svm->msrpm = svm_vcpu_alloc_msrpm();
	अगर (!svm->msrpm) अणु
		err = -ENOMEM;
		जाओ error_मुक्त_vmsa_page;
	पूर्ण

	svm_vcpu_init_msrpm(vcpu, svm->msrpm);

	svm->vmcb01.ptr = page_address(vmcb01_page);
	svm->vmcb01.pa = __sme_set(page_to_pfn(vmcb01_page) << PAGE_SHIFT);

	अगर (vmsa_page)
		svm->vmsa = page_address(vmsa_page);

	svm->guest_state_loaded = false;

	svm_चयन_vmcb(svm, &svm->vmcb01);
	init_vmcb(vcpu);

	svm_init_osvw(vcpu);
	vcpu->arch.microcode_version = 0x01000065;

	अगर (sev_es_guest(vcpu->kvm))
		/* Perक्रमm SEV-ES specअगरic VMCB creation updates */
		sev_es_create_vcpu(svm);

	वापस 0;

error_मुक्त_vmsa_page:
	अगर (vmsa_page)
		__मुक्त_page(vmsa_page);
error_मुक्त_vmcb_page:
	__मुक्त_page(vmcb01_page);
out:
	वापस err;
पूर्ण

अटल व्योम svm_clear_current_vmcb(काष्ठा vmcb *vmcb)
अणु
	पूर्णांक i;

	क्रम_each_online_cpu(i)
		cmpxchg(&per_cpu(svm_data, i)->current_vmcb, vmcb, शून्य);
पूर्ण

अटल व्योम svm_मुक्त_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * The vmcb page can be recycled, causing a false negative in
	 * svm_vcpu_load(). So, ensure that no logical CPU has this
	 * vmcb page recorded as its current vmcb.
	 */
	svm_clear_current_vmcb(svm->vmcb);

	svm_मुक्त_nested(svm);

	sev_मुक्त_vcpu(vcpu);

	__मुक्त_page(pfn_to_page(__sme_clr(svm->vmcb01.pa) >> PAGE_SHIFT));
	__मुक्त_pages(virt_to_page(svm->msrpm), get_order(MSRPM_SIZE));
पूर्ण

अटल व्योम svm_prepare_guest_चयन(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा svm_cpu_data *sd = per_cpu(svm_data, vcpu->cpu);

	अगर (sev_es_guest(vcpu->kvm))
		sev_es_unmap_ghcb(svm);

	अगर (svm->guest_state_loaded)
		वापस;

	/*
	 * Save additional host state that will be restored on VMEXIT (sev-es)
	 * or subsequent vmload of host save area.
	 */
	अगर (sev_es_guest(vcpu->kvm)) अणु
		sev_es_prepare_guest_चयन(svm, vcpu->cpu);
	पूर्ण अन्यथा अणु
		vmsave(__sme_page_pa(sd->save_area));
	पूर्ण

	अगर (अटल_cpu_has(X86_FEATURE_TSCRATEMSR)) अणु
		u64 tsc_ratio = vcpu->arch.tsc_scaling_ratio;
		अगर (tsc_ratio != __this_cpu_पढ़ो(current_tsc_ratio)) अणु
			__this_cpu_ग_लिखो(current_tsc_ratio, tsc_ratio);
			wrmsrl(MSR_AMD64_TSC_RATIO, tsc_ratio);
		पूर्ण
	पूर्ण

	अगर (likely(tsc_aux_uret_slot >= 0))
		kvm_set_user_वापस_msr(tsc_aux_uret_slot, svm->tsc_aux, -1ull);

	svm->guest_state_loaded = true;
पूर्ण

अटल व्योम svm_prepare_host_चयन(काष्ठा kvm_vcpu *vcpu)
अणु
	to_svm(vcpu)->guest_state_loaded = false;
पूर्ण

अटल व्योम svm_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा svm_cpu_data *sd = per_cpu(svm_data, cpu);

	अगर (sd->current_vmcb != svm->vmcb) अणु
		sd->current_vmcb = svm->vmcb;
		indirect_branch_prediction_barrier();
	पूर्ण
	avic_vcpu_load(vcpu, cpu);
पूर्ण

अटल व्योम svm_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	avic_vcpu_put(vcpu);
	svm_prepare_host_चयन(vcpu);

	++vcpu->स्थिति.सost_state_reload;
पूर्ण

अटल अचिन्हित दीर्घ svm_get_rflags(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अचिन्हित दीर्घ rflags = svm->vmcb->save.rflags;

	अगर (svm->nmi_singlestep) अणु
		/* Hide our flags अगर they were not set by the guest */
		अगर (!(svm->nmi_singlestep_guest_rflags & X86_EFLAGS_TF))
			rflags &= ~X86_EFLAGS_TF;
		अगर (!(svm->nmi_singlestep_guest_rflags & X86_EFLAGS_RF))
			rflags &= ~X86_EFLAGS_RF;
	पूर्ण
	वापस rflags;
पूर्ण

अटल व्योम svm_set_rflags(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ rflags)
अणु
	अगर (to_svm(vcpu)->nmi_singlestep)
		rflags |= (X86_EFLAGS_TF | X86_EFLAGS_RF);

       /*
        * Any change of EFLAGS.VM is accompanied by a reload of SS
        * (caused by either a task चयन or an पूर्णांकer-privilege IRET),
        * so we करो not need to update the CPL here.
        */
	to_svm(vcpu)->vmcb->save.rflags = rflags;
पूर्ण

अटल व्योम svm_cache_reg(काष्ठा kvm_vcpu *vcpu, क्रमागत kvm_reg reg)
अणु
	चयन (reg) अणु
	हाल VCPU_EXREG_PDPTR:
		BUG_ON(!npt_enabled);
		load_pdptrs(vcpu, vcpu->arch.walk_mmu, kvm_पढ़ो_cr3(vcpu));
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल व्योम svm_set_vपूर्णांकr(काष्ठा vcpu_svm *svm)
अणु
	काष्ठा vmcb_control_area *control;

	/* The following fields are ignored when AVIC is enabled */
	WARN_ON(kvm_vcpu_apicv_active(&svm->vcpu));
	svm_set_पूर्णांकercept(svm, INTERCEPT_VINTR);

	/*
	 * This is just a dummy VINTR to actually cause a vmनिकास to happen.
	 * Actual injection of भव पूर्णांकerrupts happens through EVENTINJ.
	 */
	control = &svm->vmcb->control;
	control->पूर्णांक_vector = 0x0;
	control->पूर्णांक_ctl &= ~V_INTR_PRIO_MASK;
	control->पूर्णांक_ctl |= V_IRQ_MASK |
		((/*control->पूर्णांक_vector >> 4*/ 0xf) << V_INTR_PRIO_SHIFT);
	vmcb_mark_dirty(svm->vmcb, VMCB_INTR);
पूर्ण

अटल व्योम svm_clear_vपूर्णांकr(काष्ठा vcpu_svm *svm)
अणु
	स्थिर u32 mask = V_TPR_MASK | V_GIF_ENABLE_MASK | V_GIF_MASK | V_INTR_MASKING_MASK;
	svm_clr_पूर्णांकercept(svm, INTERCEPT_VINTR);

	/* Drop पूर्णांक_ctl fields related to VINTR injection.  */
	svm->vmcb->control.पूर्णांक_ctl &= mask;
	अगर (is_guest_mode(&svm->vcpu)) अणु
		svm->vmcb01.ptr->control.पूर्णांक_ctl &= mask;

		WARN_ON((svm->vmcb->control.पूर्णांक_ctl & V_TPR_MASK) !=
			(svm->nested.ctl.पूर्णांक_ctl & V_TPR_MASK));
		svm->vmcb->control.पूर्णांक_ctl |= svm->nested.ctl.पूर्णांक_ctl & ~mask;
	पूर्ण

	vmcb_mark_dirty(svm->vmcb, VMCB_INTR);
पूर्ण

अटल काष्ठा vmcb_seg *svm_seg(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg)
अणु
	काष्ठा vmcb_save_area *save = &to_svm(vcpu)->vmcb->save;
	काष्ठा vmcb_save_area *save01 = &to_svm(vcpu)->vmcb01.ptr->save;

	चयन (seg) अणु
	हाल VCPU_SREG_CS: वापस &save->cs;
	हाल VCPU_SREG_DS: वापस &save->ds;
	हाल VCPU_SREG_ES: वापस &save->es;
	हाल VCPU_SREG_FS: वापस &save01->fs;
	हाल VCPU_SREG_GS: वापस &save01->gs;
	हाल VCPU_SREG_SS: वापस &save->ss;
	हाल VCPU_SREG_TR: वापस &save01->tr;
	हाल VCPU_SREG_LDTR: वापस &save01->ldtr;
	पूर्ण
	BUG();
	वापस शून्य;
पूर्ण

अटल u64 svm_get_segment_base(काष्ठा kvm_vcpu *vcpu, पूर्णांक seg)
अणु
	काष्ठा vmcb_seg *s = svm_seg(vcpu, seg);

	वापस s->base;
पूर्ण

अटल व्योम svm_get_segment(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_segment *var, पूर्णांक seg)
अणु
	काष्ठा vmcb_seg *s = svm_seg(vcpu, seg);

	var->base = s->base;
	var->limit = s->limit;
	var->selector = s->selector;
	var->type = s->attrib & SVM_SELECTOR_TYPE_MASK;
	var->s = (s->attrib >> SVM_SELECTOR_S_SHIFT) & 1;
	var->dpl = (s->attrib >> SVM_SELECTOR_DPL_SHIFT) & 3;
	var->present = (s->attrib >> SVM_SELECTOR_P_SHIFT) & 1;
	var->avl = (s->attrib >> SVM_SELECTOR_AVL_SHIFT) & 1;
	var->l = (s->attrib >> SVM_SELECTOR_L_SHIFT) & 1;
	var->db = (s->attrib >> SVM_SELECTOR_DB_SHIFT) & 1;

	/*
	 * AMD CPUs circa 2014 track the G bit क्रम all segments except CS.
	 * However, the SVM spec states that the G bit is not observed by the
	 * CPU, and some VMware भव CPUs drop the G bit क्रम all segments.
	 * So let's synthesize a legal G bit क्रम all segments, this helps
	 * running KVM nested. It also helps cross-venकरोr migration, because
	 * Intel's vmentry has a check on the 'G' bit.
	 */
	var->g = s->limit > 0xfffff;

	/*
	 * AMD's VMCB करोes not have an explicit unusable field, so emulate it
	 * क्रम cross venकरोr migration purposes by "not present"
	 */
	var->unusable = !var->present;

	चयन (seg) अणु
	हाल VCPU_SREG_TR:
		/*
		 * Work around a bug where the busy flag in the tr selector
		 * isn't exposed
		 */
		var->type |= 0x2;
		अवरोध;
	हाल VCPU_SREG_DS:
	हाल VCPU_SREG_ES:
	हाल VCPU_SREG_FS:
	हाल VCPU_SREG_GS:
		/*
		 * The accessed bit must always be set in the segment
		 * descriptor cache, although it can be cleared in the
		 * descriptor, the cached bit always reमुख्यs at 1. Since
		 * Intel has a check on this, set it here to support
		 * cross-venकरोr migration.
		 */
		अगर (!var->unusable)
			var->type |= 0x1;
		अवरोध;
	हाल VCPU_SREG_SS:
		/*
		 * On AMD CPUs someबार the DB bit in the segment
		 * descriptor is left as 1, although the whole segment has
		 * been made unusable. Clear it here to pass an Intel VMX
		 * entry check when cross venकरोr migrating.
		 */
		अगर (var->unusable)
			var->db = 0;
		/* This is symmetric with svm_set_segment() */
		var->dpl = to_svm(vcpu)->vmcb->save.cpl;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक svm_get_cpl(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vmcb_save_area *save = &to_svm(vcpu)->vmcb->save;

	वापस save->cpl;
पूर्ण

अटल व्योम svm_get_idt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	dt->size = svm->vmcb->save.idtr.limit;
	dt->address = svm->vmcb->save.idtr.base;
पूर्ण

अटल व्योम svm_set_idt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->save.idtr.limit = dt->size;
	svm->vmcb->save.idtr.base = dt->address ;
	vmcb_mark_dirty(svm->vmcb, VMCB_DT);
पूर्ण

अटल व्योम svm_get_gdt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	dt->size = svm->vmcb->save.gdtr.limit;
	dt->address = svm->vmcb->save.gdtr.base;
पूर्ण

अटल व्योम svm_set_gdt(काष्ठा kvm_vcpu *vcpu, काष्ठा desc_ptr *dt)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->save.gdtr.limit = dt->size;
	svm->vmcb->save.gdtr.base = dt->address ;
	vmcb_mark_dirty(svm->vmcb, VMCB_DT);
पूर्ण

व्योम svm_set_cr0(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr0)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u64 hcr0 = cr0;

#अगर_घोषित CONFIG_X86_64
	अगर (vcpu->arch.efer & EFER_LME && !vcpu->arch.guest_state_रक्षित) अणु
		अगर (!is_paging(vcpu) && (cr0 & X86_CR0_PG)) अणु
			vcpu->arch.efer |= EFER_LMA;
			svm->vmcb->save.efer |= EFER_LMA | EFER_LME;
		पूर्ण

		अगर (is_paging(vcpu) && !(cr0 & X86_CR0_PG)) अणु
			vcpu->arch.efer &= ~EFER_LMA;
			svm->vmcb->save.efer &= ~(EFER_LMA | EFER_LME);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	vcpu->arch.cr0 = cr0;

	अगर (!npt_enabled)
		hcr0 |= X86_CR0_PG | X86_CR0_WP;

	/*
	 * re-enable caching here because the QEMU bios
	 * करोes not करो it - this results in some delay at
	 * reboot
	 */
	अगर (kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_CD_NW_CLEARED))
		hcr0 &= ~(X86_CR0_CD | X86_CR0_NW);

	svm->vmcb->save.cr0 = hcr0;
	vmcb_mark_dirty(svm->vmcb, VMCB_CR);

	/*
	 * SEV-ES guests must always keep the CR पूर्णांकercepts cleared. CR
	 * tracking is करोne using the CR ग_लिखो traps.
	 */
	अगर (sev_es_guest(vcpu->kvm))
		वापस;

	अगर (hcr0 == cr0) अणु
		/* Selective CR0 ग_लिखो reमुख्यs on.  */
		svm_clr_पूर्णांकercept(svm, INTERCEPT_CR0_READ);
		svm_clr_पूर्णांकercept(svm, INTERCEPT_CR0_WRITE);
	पूर्ण अन्यथा अणु
		svm_set_पूर्णांकercept(svm, INTERCEPT_CR0_READ);
		svm_set_पूर्णांकercept(svm, INTERCEPT_CR0_WRITE);
	पूर्ण
पूर्ण

अटल bool svm_is_valid_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4)
अणु
	वापस true;
पूर्ण

व्योम svm_set_cr4(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cr4)
अणु
	अचिन्हित दीर्घ host_cr4_mce = cr4_पढ़ो_shaकरोw() & X86_CR4_MCE;
	अचिन्हित दीर्घ old_cr4 = vcpu->arch.cr4;

	अगर (npt_enabled && ((old_cr4 ^ cr4) & X86_CR4_PGE))
		svm_flush_tlb(vcpu);

	vcpu->arch.cr4 = cr4;
	अगर (!npt_enabled)
		cr4 |= X86_CR4_PAE;
	cr4 |= host_cr4_mce;
	to_svm(vcpu)->vmcb->save.cr4 = cr4;
	vmcb_mark_dirty(to_svm(vcpu)->vmcb, VMCB_CR);

	अगर ((cr4 ^ old_cr4) & (X86_CR4_OSXSAVE | X86_CR4_PKE))
		kvm_update_cpuid_runसमय(vcpu);
पूर्ण

अटल व्योम svm_set_segment(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_segment *var, पूर्णांक seg)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb_seg *s = svm_seg(vcpu, seg);

	s->base = var->base;
	s->limit = var->limit;
	s->selector = var->selector;
	s->attrib = (var->type & SVM_SELECTOR_TYPE_MASK);
	s->attrib |= (var->s & 1) << SVM_SELECTOR_S_SHIFT;
	s->attrib |= (var->dpl & 3) << SVM_SELECTOR_DPL_SHIFT;
	s->attrib |= ((var->present & 1) && !var->unusable) << SVM_SELECTOR_P_SHIFT;
	s->attrib |= (var->avl & 1) << SVM_SELECTOR_AVL_SHIFT;
	s->attrib |= (var->l & 1) << SVM_SELECTOR_L_SHIFT;
	s->attrib |= (var->db & 1) << SVM_SELECTOR_DB_SHIFT;
	s->attrib |= (var->g & 1) << SVM_SELECTOR_G_SHIFT;

	/*
	 * This is always accurate, except अगर SYSRET वापसed to a segment
	 * with SS.DPL != 3.  Intel करोes not have this quirk, and always
	 * क्रमces SS.DPL to 3 on sysret, so we ignore that हाल; fixing it
	 * would entail passing the CPL to userspace and back.
	 */
	अगर (seg == VCPU_SREG_SS)
		/* This is symmetric with svm_get_segment() */
		svm->vmcb->save.cpl = (var->dpl & 3);

	vmcb_mark_dirty(svm->vmcb, VMCB_SEG);
पूर्ण

अटल व्योम svm_update_exception_biपंचांगap(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	clr_exception_पूर्णांकercept(svm, BP_VECTOR);

	अगर (vcpu->guest_debug & KVM_GUESTDBG_ENABLE) अणु
		अगर (vcpu->guest_debug & KVM_GUESTDBG_USE_SW_BP)
			set_exception_पूर्णांकercept(svm, BP_VECTOR);
	पूर्ण
पूर्ण

अटल व्योम new_asid(काष्ठा vcpu_svm *svm, काष्ठा svm_cpu_data *sd)
अणु
	अगर (sd->next_asid > sd->max_asid) अणु
		++sd->asid_generation;
		sd->next_asid = sd->min_asid;
		svm->vmcb->control.tlb_ctl = TLB_CONTROL_FLUSH_ALL_ASID;
		vmcb_mark_dirty(svm->vmcb, VMCB_ASID);
	पूर्ण

	svm->current_vmcb->asid_generation = sd->asid_generation;
	svm->asid = sd->next_asid++;
पूर्ण

अटल व्योम svm_set_dr6(काष्ठा vcpu_svm *svm, अचिन्हित दीर्घ value)
अणु
	काष्ठा vmcb *vmcb = svm->vmcb;

	अगर (svm->vcpu.arch.guest_state_रक्षित)
		वापस;

	अगर (unlikely(value != vmcb->save.dr6)) अणु
		vmcb->save.dr6 = value;
		vmcb_mark_dirty(vmcb, VMCB_DR);
	पूर्ण
पूर्ण

अटल व्योम svm_sync_dirty_debug_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (vcpu->arch.guest_state_रक्षित)
		वापस;

	get_debugreg(vcpu->arch.db[0], 0);
	get_debugreg(vcpu->arch.db[1], 1);
	get_debugreg(vcpu->arch.db[2], 2);
	get_debugreg(vcpu->arch.db[3], 3);
	/*
	 * We cannot reset svm->vmcb->save.dr6 to DR6_ACTIVE_LOW here,
	 * because db_पूर्णांकerception might need it.  We can करो it beक्रमe vmentry.
	 */
	vcpu->arch.dr6 = svm->vmcb->save.dr6;
	vcpu->arch.dr7 = svm->vmcb->save.dr7;
	vcpu->arch.चयन_db_regs &= ~KVM_DEBUGREG_WONT_EXIT;
	set_dr_पूर्णांकercepts(svm);
पूर्ण

अटल व्योम svm_set_dr7(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ value)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (vcpu->arch.guest_state_रक्षित)
		वापस;

	svm->vmcb->save.dr7 = value;
	vmcb_mark_dirty(svm->vmcb, VMCB_DR);
पूर्ण

अटल पूर्णांक pf_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	u64 fault_address = svm->vmcb->control.निकास_info_2;
	u64 error_code = svm->vmcb->control.निकास_info_1;

	वापस kvm_handle_page_fault(vcpu, error_code, fault_address,
			अटल_cpu_has(X86_FEATURE_DECODEASSISTS) ?
			svm->vmcb->control.insn_bytes : शून्य,
			svm->vmcb->control.insn_len);
पूर्ण

अटल पूर्णांक npf_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	u64 fault_address = __sme_clr(svm->vmcb->control.निकास_info_2);
	u64 error_code = svm->vmcb->control.निकास_info_1;

	trace_kvm_page_fault(fault_address, error_code);
	वापस kvm_mmu_page_fault(vcpu, fault_address, error_code,
			अटल_cpu_has(X86_FEATURE_DECODEASSISTS) ?
			svm->vmcb->control.insn_bytes : शून्य,
			svm->vmcb->control.insn_len);
पूर्ण

अटल पूर्णांक db_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (!(vcpu->guest_debug &
	      (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP)) &&
		!svm->nmi_singlestep) अणु
		u32 payload = svm->vmcb->save.dr6 ^ DR6_ACTIVE_LOW;
		kvm_queue_exception_p(vcpu, DB_VECTOR, payload);
		वापस 1;
	पूर्ण

	अगर (svm->nmi_singlestep) अणु
		disable_nmi_singlestep(svm);
		/* Make sure we check क्रम pending NMIs upon entry */
		kvm_make_request(KVM_REQ_EVENT, vcpu);
	पूर्ण

	अगर (vcpu->guest_debug &
	    (KVM_GUESTDBG_SINGLESTEP | KVM_GUESTDBG_USE_HW_BP)) अणु
		kvm_run->निकास_reason = KVM_EXIT_DEBUG;
		kvm_run->debug.arch.dr6 = svm->vmcb->save.dr6;
		kvm_run->debug.arch.dr7 = svm->vmcb->save.dr7;
		kvm_run->debug.arch.pc =
			svm->vmcb->save.cs.base + svm->vmcb->save.rip;
		kvm_run->debug.arch.exception = DB_VECTOR;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक bp_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा kvm_run *kvm_run = vcpu->run;

	kvm_run->निकास_reason = KVM_EXIT_DEBUG;
	kvm_run->debug.arch.pc = svm->vmcb->save.cs.base + svm->vmcb->save.rip;
	kvm_run->debug.arch.exception = BP_VECTOR;
	वापस 0;
पूर्ण

अटल पूर्णांक ud_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस handle_ud(vcpu);
पूर्ण

अटल पूर्णांक ac_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_queue_exception_e(vcpu, AC_VECTOR, 0);
	वापस 1;
पूर्ण

अटल bool is_erratum_383(व्योम)
अणु
	पूर्णांक err, i;
	u64 value;

	अगर (!erratum_383_found)
		वापस false;

	value = native_पढ़ो_msr_safe(MSR_IA32_MC0_STATUS, &err);
	अगर (err)
		वापस false;

	/* Bit 62 may or may not be set क्रम this mce */
	value &= ~(1ULL << 62);

	अगर (value != 0xb600000000010015ULL)
		वापस false;

	/* Clear MCi_STATUS रेजिस्टरs */
	क्रम (i = 0; i < 6; ++i)
		native_ग_लिखो_msr_safe(MSR_IA32_MCx_STATUS(i), 0, 0);

	value = native_पढ़ो_msr_safe(MSR_IA32_MCG_STATUS, &err);
	अगर (!err) अणु
		u32 low, high;

		value &= ~(1ULL << 2);
		low    = lower_32_bits(value);
		high   = upper_32_bits(value);

		native_ग_लिखो_msr_safe(MSR_IA32_MCG_STATUS, low, high);
	पूर्ण

	/* Flush tlb to evict multi-match entries */
	__flush_tlb_all();

	वापस true;
पूर्ण

अटल व्योम svm_handle_mce(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (is_erratum_383()) अणु
		/*
		 * Erratum 383 triggered. Guest state is corrupt so समाप्त the
		 * guest.
		 */
		pr_err("KVM: Guest triggered AMD Erratum 383\n");

		kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);

		वापस;
	पूर्ण

	/*
	 * On an #MC पूर्णांकercept the MCE handler is not called स्वतःmatically in
	 * the host. So करो it by hand here.
	 */
	kvm_machine_check();
पूर्ण

अटल पूर्णांक mc_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक shutकरोwn_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *kvm_run = vcpu->run;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * The VM save area has alपढ़ोy been encrypted so it
	 * cannot be reinitialized - just terminate.
	 */
	अगर (sev_es_guest(vcpu->kvm))
		वापस -EINVAL;

	/*
	 * VMCB is undefined after a SHUTDOWN पूर्णांकercept
	 * so reinitialize it.
	 */
	clear_page(svm->vmcb);
	init_vmcb(vcpu);

	kvm_run->निकास_reason = KVM_EXIT_SHUTDOWN;
	वापस 0;
पूर्ण

अटल पूर्णांक io_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 io_info = svm->vmcb->control.निकास_info_1; /* address size bug? */
	पूर्णांक size, in, string;
	अचिन्हित port;

	++vcpu->stat.io_निकासs;
	string = (io_info & SVM_IOIO_STR_MASK) != 0;
	in = (io_info & SVM_IOIO_TYPE_MASK) != 0;
	port = io_info >> 16;
	size = (io_info & SVM_IOIO_SIZE_MASK) >> SVM_IOIO_SIZE_SHIFT;

	अगर (string) अणु
		अगर (sev_es_guest(vcpu->kvm))
			वापस sev_es_string_io(svm, size, port, in);
		अन्यथा
			वापस kvm_emulate_inकाष्ठाion(vcpu, 0);
	पूर्ण

	svm->next_rip = svm->vmcb->control.निकास_info_2;

	वापस kvm_fast_pio(vcpu, size, port, in);
पूर्ण

अटल पूर्णांक nmi_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक पूर्णांकr_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	++vcpu->stat.irq_निकासs;
	वापस 1;
पूर्ण

अटल पूर्णांक vmload_vmsave_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu, bool vmload)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb *vmcb12;
	काष्ठा kvm_host_map map;
	पूर्णांक ret;

	अगर (nested_svm_check_permissions(vcpu))
		वापस 1;

	ret = kvm_vcpu_map(vcpu, gpa_to_gfn(svm->vmcb->save.rax), &map);
	अगर (ret) अणु
		अगर (ret == -EINVAL)
			kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	vmcb12 = map.hva;

	ret = kvm_skip_emulated_inकाष्ठाion(vcpu);

	अगर (vmload) अणु
		nested_svm_vmloadsave(vmcb12, svm->vmcb);
		svm->sysenter_eip_hi = 0;
		svm->sysenter_esp_hi = 0;
	पूर्ण अन्यथा
		nested_svm_vmloadsave(svm->vmcb, vmcb12);

	kvm_vcpu_unmap(vcpu, &map, true);

	वापस ret;
पूर्ण

अटल पूर्णांक vmload_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vmload_vmsave_पूर्णांकerception(vcpu, true);
पूर्ण

अटल पूर्णांक vmsave_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vmload_vmsave_पूर्णांकerception(vcpu, false);
पूर्ण

अटल पूर्णांक vmrun_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (nested_svm_check_permissions(vcpu))
		वापस 1;

	वापस nested_svm_vmrun(vcpu);
पूर्ण

क्रमागत अणु
	NONE_SVM_INSTR,
	SVM_INSTR_VMRUN,
	SVM_INSTR_VMLOAD,
	SVM_INSTR_VMSAVE,
पूर्ण;

/* Return NONE_SVM_INSTR अगर not SVM instrs, otherwise वापस decode result */
अटल पूर्णांक svm_instr_opcode(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा x86_emulate_ctxt *ctxt = vcpu->arch.emulate_ctxt;

	अगर (ctxt->b != 0x1 || ctxt->opcode_len != 2)
		वापस NONE_SVM_INSTR;

	चयन (ctxt->modrm) अणु
	हाल 0xd8: /* VMRUN */
		वापस SVM_INSTR_VMRUN;
	हाल 0xda: /* VMLOAD */
		वापस SVM_INSTR_VMLOAD;
	हाल 0xdb: /* VMSAVE */
		वापस SVM_INSTR_VMSAVE;
	शेष:
		अवरोध;
	पूर्ण

	वापस NONE_SVM_INSTR;
पूर्ण

अटल पूर्णांक emulate_svm_instr(काष्ठा kvm_vcpu *vcpu, पूर्णांक opcode)
अणु
	स्थिर पूर्णांक guest_mode_निकास_codes[] = अणु
		[SVM_INSTR_VMRUN] = SVM_EXIT_VMRUN,
		[SVM_INSTR_VMLOAD] = SVM_EXIT_VMLOAD,
		[SVM_INSTR_VMSAVE] = SVM_EXIT_VMSAVE,
	पूर्ण;
	पूर्णांक (*स्थिर svm_instr_handlers[])(काष्ठा kvm_vcpu *vcpu) = अणु
		[SVM_INSTR_VMRUN] = vmrun_पूर्णांकerception,
		[SVM_INSTR_VMLOAD] = vmload_पूर्णांकerception,
		[SVM_INSTR_VMSAVE] = vmsave_पूर्णांकerception,
	पूर्ण;
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक ret;

	अगर (is_guest_mode(vcpu)) अणु
		/* Returns '1' or -errno on failure, '0' on success. */
		ret = nested_svm_simple_vmनिकास(svm, guest_mode_निकास_codes[opcode]);
		अगर (ret)
			वापस ret;
		वापस 1;
	पूर्ण
	वापस svm_instr_handlers[opcode](vcpu);
पूर्ण

/*
 * #GP handling code. Note that #GP can be triggered under the following two
 * हालs:
 *   1) SVM VM-related inकाष्ठाions (VMRUN/VMSAVE/VMLOAD) that trigger #GP on
 *      some AMD CPUs when EAX of these inकाष्ठाions are in the reserved memory
 *      regions (e.g. SMM memory on host).
 *   2) VMware backकरोor
 */
अटल पूर्णांक gp_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u32 error_code = svm->vmcb->control.निकास_info_1;
	पूर्णांक opcode;

	/* Both #GP हालs have zero error_code */
	अगर (error_code)
		जाओ reinject;

	/* Decode the inकाष्ठाion क्रम usage later */
	अगर (x86_decode_emulated_inकाष्ठाion(vcpu, 0, शून्य, 0) != EMULATION_OK)
		जाओ reinject;

	opcode = svm_instr_opcode(vcpu);

	अगर (opcode == NONE_SVM_INSTR) अणु
		अगर (!enable_vmware_backकरोor)
			जाओ reinject;

		/*
		 * VMware backकरोor emulation on #GP पूर्णांकerception only handles
		 * INअणुSपूर्ण, OUTअणुSपूर्ण, and RDPMC.
		 */
		अगर (!is_guest_mode(vcpu))
			वापस kvm_emulate_inकाष्ठाion(vcpu,
				EMULTYPE_VMWARE_GP | EMULTYPE_NO_DECODE);
	पूर्ण अन्यथा
		वापस emulate_svm_instr(vcpu, opcode);

reinject:
	kvm_queue_exception_e(vcpu, GP_VECTOR, error_code);
	वापस 1;
पूर्ण

व्योम svm_set_gअगर(काष्ठा vcpu_svm *svm, bool value)
अणु
	अगर (value) अणु
		/*
		 * If VGIF is enabled, the STGI पूर्णांकercept is only added to
		 * detect the खोलोing of the SMI/NMI winकरोw; हटाओ it now.
		 * Likewise, clear the VINTR पूर्णांकercept, we will set it
		 * again जबतक processing KVM_REQ_EVENT अगर needed.
		 */
		अगर (vgअगर_enabled(svm))
			svm_clr_पूर्णांकercept(svm, INTERCEPT_STGI);
		अगर (svm_is_पूर्णांकercept(svm, INTERCEPT_VINTR))
			svm_clear_vपूर्णांकr(svm);

		enable_gअगर(svm);
		अगर (svm->vcpu.arch.smi_pending ||
		    svm->vcpu.arch.nmi_pending ||
		    kvm_cpu_has_injectable_पूर्णांकr(&svm->vcpu))
			kvm_make_request(KVM_REQ_EVENT, &svm->vcpu);
	पूर्ण अन्यथा अणु
		disable_gअगर(svm);

		/*
		 * After a CLGI no पूर्णांकerrupts should come.  But अगर vGIF is
		 * in use, we still rely on the VINTR पूर्णांकercept (rather than
		 * STGI) to detect an खोलो पूर्णांकerrupt winकरोw.
		*/
		अगर (!vgअगर_enabled(svm))
			svm_clear_vपूर्णांकr(svm);
	पूर्ण
पूर्ण

अटल पूर्णांक stgi_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;

	अगर (nested_svm_check_permissions(vcpu))
		वापस 1;

	ret = kvm_skip_emulated_inकाष्ठाion(vcpu);
	svm_set_gअगर(to_svm(vcpu), true);
	वापस ret;
पूर्ण

अटल पूर्णांक clgi_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;

	अगर (nested_svm_check_permissions(vcpu))
		वापस 1;

	ret = kvm_skip_emulated_inकाष्ठाion(vcpu);
	svm_set_gअगर(to_svm(vcpu), false);
	वापस ret;
पूर्ण

अटल पूर्णांक invlpga_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	gva_t gva = kvm_rax_पढ़ो(vcpu);
	u32 asid = kvm_rcx_पढ़ो(vcpu);

	/* FIXME: Handle an address size prefix. */
	अगर (!is_दीर्घ_mode(vcpu))
		gva = (u32)gva;

	trace_kvm_invlpga(to_svm(vcpu)->vmcb->save.rip, asid, gva);

	/* Let's treat INVLPGA the same as INVLPG (can be optimized!) */
	kvm_mmu_invlpg(vcpu, gva);

	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक skinit_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	trace_kvm_skinit(to_svm(vcpu)->vmcb->save.rip, kvm_rax_पढ़ो(vcpu));

	kvm_queue_exception(vcpu, UD_VECTOR);
	वापस 1;
पूर्ण

अटल पूर्णांक task_चयन_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u16 tss_selector;
	पूर्णांक reason;
	पूर्णांक पूर्णांक_type = svm->vmcb->control.निकास_पूर्णांक_info &
		SVM_EXITINTINFO_TYPE_MASK;
	पूर्णांक पूर्णांक_vec = svm->vmcb->control.निकास_पूर्णांक_info & SVM_EVTINJ_VEC_MASK;
	uपूर्णांक32_t type =
		svm->vmcb->control.निकास_पूर्णांक_info & SVM_EXITINTINFO_TYPE_MASK;
	uपूर्णांक32_t idt_v =
		svm->vmcb->control.निकास_पूर्णांक_info & SVM_EXITINTINFO_VALID;
	bool has_error_code = false;
	u32 error_code = 0;

	tss_selector = (u16)svm->vmcb->control.निकास_info_1;

	अगर (svm->vmcb->control.निकास_info_2 &
	    (1ULL << SVM_EXITINFOSHIFT_TS_REASON_IRET))
		reason = TASK_SWITCH_IRET;
	अन्यथा अगर (svm->vmcb->control.निकास_info_2 &
		 (1ULL << SVM_EXITINFOSHIFT_TS_REASON_JMP))
		reason = TASK_SWITCH_JMP;
	अन्यथा अगर (idt_v)
		reason = TASK_SWITCH_GATE;
	अन्यथा
		reason = TASK_SWITCH_CALL;

	अगर (reason == TASK_SWITCH_GATE) अणु
		चयन (type) अणु
		हाल SVM_EXITINTINFO_TYPE_NMI:
			vcpu->arch.nmi_injected = false;
			अवरोध;
		हाल SVM_EXITINTINFO_TYPE_EXEPT:
			अगर (svm->vmcb->control.निकास_info_2 &
			    (1ULL << SVM_EXITINFOSHIFT_TS_HAS_ERROR_CODE)) अणु
				has_error_code = true;
				error_code =
					(u32)svm->vmcb->control.निकास_info_2;
			पूर्ण
			kvm_clear_exception_queue(vcpu);
			अवरोध;
		हाल SVM_EXITINTINFO_TYPE_INTR:
			kvm_clear_पूर्णांकerrupt_queue(vcpu);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (reason != TASK_SWITCH_GATE ||
	    पूर्णांक_type == SVM_EXITINTINFO_TYPE_SOFT ||
	    (पूर्णांक_type == SVM_EXITINTINFO_TYPE_EXEPT &&
	     (पूर्णांक_vec == OF_VECTOR || पूर्णांक_vec == BP_VECTOR))) अणु
		अगर (!skip_emulated_inकाष्ठाion(vcpu))
			वापस 0;
	पूर्ण

	अगर (पूर्णांक_type != SVM_EXITINTINFO_TYPE_SOFT)
		पूर्णांक_vec = -1;

	वापस kvm_task_चयन(vcpu, tss_selector, पूर्णांक_vec, reason,
			       has_error_code, error_code);
पूर्ण

अटल पूर्णांक iret_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	++vcpu->stat.nmi_winकरोw_निकासs;
	vcpu->arch.hflags |= HF_IRET_MASK;
	अगर (!sev_es_guest(vcpu->kvm)) अणु
		svm_clr_पूर्णांकercept(svm, INTERCEPT_IRET);
		svm->nmi_iret_rip = kvm_rip_पढ़ो(vcpu);
	पूर्ण
	kvm_make_request(KVM_REQ_EVENT, vcpu);
	वापस 1;
पूर्ण

अटल पूर्णांक invlpg_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!अटल_cpu_has(X86_FEATURE_DECODEASSISTS))
		वापस kvm_emulate_inकाष्ठाion(vcpu, 0);

	kvm_mmu_invlpg(vcpu, to_svm(vcpu)->vmcb->control.निकास_info_1);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक emulate_on_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_emulate_inकाष्ठाion(vcpu, 0);
पूर्ण

अटल पूर्णांक rsm_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_emulate_inकाष्ठाion_from_buffer(vcpu, rsm_ins_bytes, 2);
पूर्ण

अटल bool check_selective_cr0_पूर्णांकercepted(काष्ठा kvm_vcpu *vcpu,
					    अचिन्हित दीर्घ val)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अचिन्हित दीर्घ cr0 = vcpu->arch.cr0;
	bool ret = false;

	अगर (!is_guest_mode(vcpu) ||
	    (!(vmcb_is_पूर्णांकercept(&svm->nested.ctl, INTERCEPT_SELECTIVE_CR0))))
		वापस false;

	cr0 &= ~SVM_CR0_SELECTIVE_MASK;
	val &= ~SVM_CR0_SELECTIVE_MASK;

	अगर (cr0 ^ val) अणु
		svm->vmcb->control.निकास_code = SVM_EXIT_CR0_SEL_WRITE;
		ret = (nested_svm_निकास_handled(svm) == NESTED_EXIT_DONE);
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा CR_VALID (1ULL << 63)

अटल पूर्णांक cr_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक reg, cr;
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	अगर (!अटल_cpu_has(X86_FEATURE_DECODEASSISTS))
		वापस emulate_on_पूर्णांकerception(vcpu);

	अगर (unlikely((svm->vmcb->control.निकास_info_1 & CR_VALID) == 0))
		वापस emulate_on_पूर्णांकerception(vcpu);

	reg = svm->vmcb->control.निकास_info_1 & SVM_EXITINFO_REG_MASK;
	अगर (svm->vmcb->control.निकास_code == SVM_EXIT_CR0_SEL_WRITE)
		cr = SVM_EXIT_WRITE_CR0 - SVM_EXIT_READ_CR0;
	अन्यथा
		cr = svm->vmcb->control.निकास_code - SVM_EXIT_READ_CR0;

	err = 0;
	अगर (cr >= 16) अणु /* mov to cr */
		cr -= 16;
		val = kvm_रेजिस्टर_पढ़ो(vcpu, reg);
		trace_kvm_cr_ग_लिखो(cr, val);
		चयन (cr) अणु
		हाल 0:
			अगर (!check_selective_cr0_पूर्णांकercepted(vcpu, val))
				err = kvm_set_cr0(vcpu, val);
			अन्यथा
				वापस 1;

			अवरोध;
		हाल 3:
			err = kvm_set_cr3(vcpu, val);
			अवरोध;
		हाल 4:
			err = kvm_set_cr4(vcpu, val);
			अवरोध;
		हाल 8:
			err = kvm_set_cr8(vcpu, val);
			अवरोध;
		शेष:
			WARN(1, "unhandled write to CR%d", cr);
			kvm_queue_exception(vcpu, UD_VECTOR);
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा अणु /* mov from cr */
		चयन (cr) अणु
		हाल 0:
			val = kvm_पढ़ो_cr0(vcpu);
			अवरोध;
		हाल 2:
			val = vcpu->arch.cr2;
			अवरोध;
		हाल 3:
			val = kvm_पढ़ो_cr3(vcpu);
			अवरोध;
		हाल 4:
			val = kvm_पढ़ो_cr4(vcpu);
			अवरोध;
		हाल 8:
			val = kvm_get_cr8(vcpu);
			अवरोध;
		शेष:
			WARN(1, "unhandled read from CR%d", cr);
			kvm_queue_exception(vcpu, UD_VECTOR);
			वापस 1;
		पूर्ण
		kvm_रेजिस्टर_ग_लिखो(vcpu, reg, val);
		trace_kvm_cr_पढ़ो(cr, val);
	पूर्ण
	वापस kvm_complete_insn_gp(vcpu, err);
पूर्ण

अटल पूर्णांक cr_trap(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अचिन्हित दीर्घ old_value, new_value;
	अचिन्हित पूर्णांक cr;
	पूर्णांक ret = 0;

	new_value = (अचिन्हित दीर्घ)svm->vmcb->control.निकास_info_1;

	cr = svm->vmcb->control.निकास_code - SVM_EXIT_CR0_WRITE_TRAP;
	चयन (cr) अणु
	हाल 0:
		old_value = kvm_पढ़ो_cr0(vcpu);
		svm_set_cr0(vcpu, new_value);

		kvm_post_set_cr0(vcpu, old_value, new_value);
		अवरोध;
	हाल 4:
		old_value = kvm_पढ़ो_cr4(vcpu);
		svm_set_cr4(vcpu, new_value);

		kvm_post_set_cr4(vcpu, old_value, new_value);
		अवरोध;
	हाल 8:
		ret = kvm_set_cr8(vcpu, new_value);
		अवरोध;
	शेष:
		WARN(1, "unhandled CR%d write trap", cr);
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	वापस kvm_complete_insn_gp(vcpu, ret);
पूर्ण

अटल पूर्णांक dr_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक reg, dr;
	अचिन्हित दीर्घ val;
	पूर्णांक err = 0;

	अगर (vcpu->guest_debug == 0) अणु
		/*
		 * No more DR vmनिकासs; क्रमce a reload of the debug रेजिस्टरs
		 * and reenter on this inकाष्ठाion.  The next vmनिकास will
		 * retrieve the full state of the debug रेजिस्टरs.
		 */
		clr_dr_पूर्णांकercepts(svm);
		vcpu->arch.चयन_db_regs |= KVM_DEBUGREG_WONT_EXIT;
		वापस 1;
	पूर्ण

	अगर (!boot_cpu_has(X86_FEATURE_DECODEASSISTS))
		वापस emulate_on_पूर्णांकerception(vcpu);

	reg = svm->vmcb->control.निकास_info_1 & SVM_EXITINFO_REG_MASK;
	dr = svm->vmcb->control.निकास_code - SVM_EXIT_READ_DR0;
	अगर (dr >= 16) अणु /* mov to DRn  */
		dr -= 16;
		val = kvm_रेजिस्टर_पढ़ो(vcpu, reg);
		err = kvm_set_dr(vcpu, dr, val);
	पूर्ण अन्यथा अणु
		kvm_get_dr(vcpu, dr, &val);
		kvm_रेजिस्टर_ग_लिखो(vcpu, reg, val);
	पूर्ण

	वापस kvm_complete_insn_gp(vcpu, err);
पूर्ण

अटल पूर्णांक cr8_ग_लिखो_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;

	u8 cr8_prev = kvm_get_cr8(vcpu);
	/* inकाष्ठाion emulation calls kvm_set_cr8() */
	r = cr_पूर्णांकerception(vcpu);
	अगर (lapic_in_kernel(vcpu))
		वापस r;
	अगर (cr8_prev <= kvm_get_cr8(vcpu))
		वापस r;
	vcpu->run->निकास_reason = KVM_EXIT_SET_TPR;
	वापस 0;
पूर्ण

अटल पूर्णांक efer_trap(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा msr_data msr_info;
	पूर्णांक ret;

	/*
	 * Clear the EFER_SVME bit from EFER. The SVM code always sets this
	 * bit in svm_set_efer(), but __kvm_valid_efer() checks it against
	 * whether the guest has X86_FEATURE_SVM - this aव्योमs a failure अगर
	 * the guest करोesn't have X86_FEATURE_SVM.
	 */
	msr_info.host_initiated = false;
	msr_info.index = MSR_EFER;
	msr_info.data = to_svm(vcpu)->vmcb->control.निकास_info_1 & ~EFER_SVME;
	ret = kvm_set_msr_common(vcpu, &msr_info);

	वापस kvm_complete_insn_gp(vcpu, ret);
पूर्ण

अटल पूर्णांक svm_get_msr_feature(काष्ठा kvm_msr_entry *msr)
अणु
	msr->data = 0;

	चयन (msr->index) अणु
	हाल MSR_F10H_DECFG:
		अगर (boot_cpu_has(X86_FEATURE_LFENCE_RDTSC))
			msr->data |= MSR_F10H_DECFG_LFENCE_SERIALIZE;
		अवरोध;
	हाल MSR_IA32_PERF_CAPABILITIES:
		वापस 0;
	शेष:
		वापस KVM_MSR_RET_INVALID;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक svm_get_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr_info)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	चयन (msr_info->index) अणु
	हाल MSR_STAR:
		msr_info->data = svm->vmcb01.ptr->save.star;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल MSR_LSTAR:
		msr_info->data = svm->vmcb01.ptr->save.lstar;
		अवरोध;
	हाल MSR_CSTAR:
		msr_info->data = svm->vmcb01.ptr->save.cstar;
		अवरोध;
	हाल MSR_KERNEL_GS_BASE:
		msr_info->data = svm->vmcb01.ptr->save.kernel_gs_base;
		अवरोध;
	हाल MSR_SYSCALL_MASK:
		msr_info->data = svm->vmcb01.ptr->save.sfmask;
		अवरोध;
#पूर्ण_अगर
	हाल MSR_IA32_SYSENTER_CS:
		msr_info->data = svm->vmcb01.ptr->save.sysenter_cs;
		अवरोध;
	हाल MSR_IA32_SYSENTER_EIP:
		msr_info->data = (u32)svm->vmcb01.ptr->save.sysenter_eip;
		अगर (guest_cpuid_is_पूर्णांकel(vcpu))
			msr_info->data |= (u64)svm->sysenter_eip_hi << 32;
		अवरोध;
	हाल MSR_IA32_SYSENTER_ESP:
		msr_info->data = svm->vmcb01.ptr->save.sysenter_esp;
		अगर (guest_cpuid_is_पूर्णांकel(vcpu))
			msr_info->data |= (u64)svm->sysenter_esp_hi << 32;
		अवरोध;
	हाल MSR_TSC_AUX:
		msr_info->data = svm->tsc_aux;
		अवरोध;
	/*
	 * Nobody will change the following 5 values in the VMCB so we can
	 * safely वापस them on rdmsr. They will always be 0 until LBRV is
	 * implemented.
	 */
	हाल MSR_IA32_DEBUGCTLMSR:
		msr_info->data = svm->vmcb->save.dbgctl;
		अवरोध;
	हाल MSR_IA32_LASTBRANCHFROMIP:
		msr_info->data = svm->vmcb->save.br_from;
		अवरोध;
	हाल MSR_IA32_LASTBRANCHTOIP:
		msr_info->data = svm->vmcb->save.br_to;
		अवरोध;
	हाल MSR_IA32_LASTINTFROMIP:
		msr_info->data = svm->vmcb->save.last_excp_from;
		अवरोध;
	हाल MSR_IA32_LASTINTTOIP:
		msr_info->data = svm->vmcb->save.last_excp_to;
		अवरोध;
	हाल MSR_VM_HSAVE_PA:
		msr_info->data = svm->nested.hsave_msr;
		अवरोध;
	हाल MSR_VM_CR:
		msr_info->data = svm->nested.vm_cr_msr;
		अवरोध;
	हाल MSR_IA32_SPEC_CTRL:
		अगर (!msr_info->host_initiated &&
		    !guest_has_spec_ctrl_msr(vcpu))
			वापस 1;

		अगर (boot_cpu_has(X86_FEATURE_V_SPEC_CTRL))
			msr_info->data = svm->vmcb->save.spec_ctrl;
		अन्यथा
			msr_info->data = svm->spec_ctrl;
		अवरोध;
	हाल MSR_AMD64_VIRT_SPEC_CTRL:
		अगर (!msr_info->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_VIRT_SSBD))
			वापस 1;

		msr_info->data = svm->virt_spec_ctrl;
		अवरोध;
	हाल MSR_F15H_IC_CFG: अणु

		पूर्णांक family, model;

		family = guest_cpuid_family(vcpu);
		model  = guest_cpuid_model(vcpu);

		अगर (family < 0 || model < 0)
			वापस kvm_get_msr_common(vcpu, msr_info);

		msr_info->data = 0;

		अगर (family == 0x15 &&
		    (model >= 0x2 && model < 0x20))
			msr_info->data = 0x1E;
		पूर्ण
		अवरोध;
	हाल MSR_F10H_DECFG:
		msr_info->data = svm->msr_decfg;
		अवरोध;
	शेष:
		वापस kvm_get_msr_common(vcpu, msr_info);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक svm_complete_emulated_msr(काष्ठा kvm_vcpu *vcpu, पूर्णांक err)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अगर (!err || !sev_es_guest(vcpu->kvm) || WARN_ON_ONCE(!svm->ghcb))
		वापस kvm_complete_insn_gp(vcpu, err);

	ghcb_set_sw_निकास_info_1(svm->ghcb, 1);
	ghcb_set_sw_निकास_info_2(svm->ghcb,
				X86_TRAP_GP |
				SVM_EVTINJ_TYPE_EXEPT |
				SVM_EVTINJ_VALID);
	वापस 1;
पूर्ण

अटल पूर्णांक svm_set_vm_cr(काष्ठा kvm_vcpu *vcpu, u64 data)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक svm_dis, chg_mask;

	अगर (data & ~SVM_VM_CR_VALID_MASK)
		वापस 1;

	chg_mask = SVM_VM_CR_VALID_MASK;

	अगर (svm->nested.vm_cr_msr & SVM_VM_CR_SVM_DIS_MASK)
		chg_mask &= ~(SVM_VM_CR_SVM_LOCK_MASK | SVM_VM_CR_SVM_DIS_MASK);

	svm->nested.vm_cr_msr &= ~chg_mask;
	svm->nested.vm_cr_msr |= (data & chg_mask);

	svm_dis = svm->nested.vm_cr_msr & SVM_VM_CR_SVM_DIS_MASK;

	/* check क्रम svm_disable जबतक efer.svme is set */
	अगर (svm_dis && (vcpu->arch.efer & EFER_SVME))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक svm_set_msr(काष्ठा kvm_vcpu *vcpu, काष्ठा msr_data *msr)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक r;

	u32 ecx = msr->index;
	u64 data = msr->data;
	चयन (ecx) अणु
	हाल MSR_IA32_CR_PAT:
		अगर (!kvm_mtrr_valid(vcpu, MSR_IA32_CR_PAT, data))
			वापस 1;
		vcpu->arch.pat = data;
		svm->vmcb01.ptr->save.g_pat = data;
		अगर (is_guest_mode(vcpu))
			nested_vmcb02_compute_g_pat(svm);
		vmcb_mark_dirty(svm->vmcb, VMCB_NPT);
		अवरोध;
	हाल MSR_IA32_SPEC_CTRL:
		अगर (!msr->host_initiated &&
		    !guest_has_spec_ctrl_msr(vcpu))
			वापस 1;

		अगर (kvm_spec_ctrl_test_value(data))
			वापस 1;

		अगर (boot_cpu_has(X86_FEATURE_V_SPEC_CTRL))
			svm->vmcb->save.spec_ctrl = data;
		अन्यथा
			svm->spec_ctrl = data;
		अगर (!data)
			अवरोध;

		/*
		 * For non-nested:
		 * When it's written (to non-zero) क्रम the first समय, pass
		 * it through.
		 *
		 * For nested:
		 * The handling of the MSR biपंचांगap क्रम L2 guests is करोne in
		 * nested_svm_vmrun_msrpm.
		 * We update the L1 MSR bit as well since it will end up
		 * touching the MSR anyway now.
		 */
		set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_SPEC_CTRL, 1, 1);
		अवरोध;
	हाल MSR_IA32_PRED_CMD:
		अगर (!msr->host_initiated &&
		    !guest_has_pred_cmd_msr(vcpu))
			वापस 1;

		अगर (data & ~PRED_CMD_IBPB)
			वापस 1;
		अगर (!boot_cpu_has(X86_FEATURE_IBPB))
			वापस 1;
		अगर (!data)
			अवरोध;

		wrmsrl(MSR_IA32_PRED_CMD, PRED_CMD_IBPB);
		set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_PRED_CMD, 0, 1);
		अवरोध;
	हाल MSR_AMD64_VIRT_SPEC_CTRL:
		अगर (!msr->host_initiated &&
		    !guest_cpuid_has(vcpu, X86_FEATURE_VIRT_SSBD))
			वापस 1;

		अगर (data & ~SPEC_CTRL_SSBD)
			वापस 1;

		svm->virt_spec_ctrl = data;
		अवरोध;
	हाल MSR_STAR:
		svm->vmcb01.ptr->save.star = data;
		अवरोध;
#अगर_घोषित CONFIG_X86_64
	हाल MSR_LSTAR:
		svm->vmcb01.ptr->save.lstar = data;
		अवरोध;
	हाल MSR_CSTAR:
		svm->vmcb01.ptr->save.cstar = data;
		अवरोध;
	हाल MSR_KERNEL_GS_BASE:
		svm->vmcb01.ptr->save.kernel_gs_base = data;
		अवरोध;
	हाल MSR_SYSCALL_MASK:
		svm->vmcb01.ptr->save.sfmask = data;
		अवरोध;
#पूर्ण_अगर
	हाल MSR_IA32_SYSENTER_CS:
		svm->vmcb01.ptr->save.sysenter_cs = data;
		अवरोध;
	हाल MSR_IA32_SYSENTER_EIP:
		svm->vmcb01.ptr->save.sysenter_eip = (u32)data;
		/*
		 * We only पूर्णांकercept the MSR_IA32_SYSENTER_अणुEIP|ESPपूर्ण msrs
		 * when we spoof an Intel venकरोr ID (क्रम cross venकरोr migration).
		 * In this हाल we use this पूर्णांकercept to track the high
		 * 32 bit part of these msrs to support Intel's
		 * implementation of SYSENTER/SYSEXIT.
		 */
		svm->sysenter_eip_hi = guest_cpuid_is_पूर्णांकel(vcpu) ? (data >> 32) : 0;
		अवरोध;
	हाल MSR_IA32_SYSENTER_ESP:
		svm->vmcb01.ptr->save.sysenter_esp = (u32)data;
		svm->sysenter_esp_hi = guest_cpuid_is_पूर्णांकel(vcpu) ? (data >> 32) : 0;
		अवरोध;
	हाल MSR_TSC_AUX:
		/*
		 * TSC_AUX is usually changed only during boot and never पढ़ो
		 * directly.  Intercept TSC_AUX instead of exposing it to the
		 * guest via direct_access_msrs, and चयन it via user वापस.
		 */
		preempt_disable();
		r = kvm_set_user_वापस_msr(tsc_aux_uret_slot, data, -1ull);
		preempt_enable();
		अगर (r)
			वापस 1;

		svm->tsc_aux = data;
		अवरोध;
	हाल MSR_IA32_DEBUGCTLMSR:
		अगर (!boot_cpu_has(X86_FEATURE_LBRV)) अणु
			vcpu_unimpl(vcpu, "%s: MSR_IA32_DEBUGCTL 0x%llx, nop\n",
				    __func__, data);
			अवरोध;
		पूर्ण
		अगर (data & DEBUGCTL_RESERVED_BITS)
			वापस 1;

		svm->vmcb->save.dbgctl = data;
		vmcb_mark_dirty(svm->vmcb, VMCB_LBR);
		अगर (data & (1ULL<<0))
			svm_enable_lbrv(vcpu);
		अन्यथा
			svm_disable_lbrv(vcpu);
		अवरोध;
	हाल MSR_VM_HSAVE_PA:
		svm->nested.hsave_msr = data;
		अवरोध;
	हाल MSR_VM_CR:
		वापस svm_set_vm_cr(vcpu, data);
	हाल MSR_VM_IGNNE:
		vcpu_unimpl(vcpu, "unimplemented wrmsr: 0x%x data 0x%llx\n", ecx, data);
		अवरोध;
	हाल MSR_F10H_DECFG: अणु
		काष्ठा kvm_msr_entry msr_entry;

		msr_entry.index = msr->index;
		अगर (svm_get_msr_feature(&msr_entry))
			वापस 1;

		/* Check the supported bits */
		अगर (data & ~msr_entry.data)
			वापस 1;

		/* Don't allow the guest to change a bit, #GP */
		अगर (!msr->host_initiated && (data ^ msr_entry.data))
			वापस 1;

		svm->msr_decfg = data;
		अवरोध;
	पूर्ण
	हाल MSR_IA32_APICBASE:
		अगर (kvm_vcpu_apicv_active(vcpu))
			avic_update_vapic_bar(to_svm(vcpu), data);
		fallthrough;
	शेष:
		वापस kvm_set_msr_common(vcpu, msr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msr_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (to_svm(vcpu)->vmcb->control.निकास_info_1)
		वापस kvm_emulate_wrmsr(vcpu);
	अन्यथा
		वापस kvm_emulate_rdmsr(vcpu);
पूर्ण

अटल पूर्णांक पूर्णांकerrupt_winकरोw_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_make_request(KVM_REQ_EVENT, vcpu);
	svm_clear_vपूर्णांकr(to_svm(vcpu));

	/*
	 * For AVIC, the only reason to end up here is ExtINTs.
	 * In this हाल AVIC was temporarily disabled क्रम
	 * requesting the IRQ winकरोw and we have to re-enable it.
	 */
	svm_toggle_avic_क्रम_irq_winकरोw(vcpu, true);

	++vcpu->stat.irq_winकरोw_निकासs;
	वापस 1;
पूर्ण

अटल पूर्णांक छोड़ो_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	bool in_kernel;

	/*
	 * CPL is not made available क्रम an SEV-ES guest, thereक्रमe
	 * vcpu->arch.preempted_in_kernel can never be true.  Just
	 * set in_kernel to false as well.
	 */
	in_kernel = !sev_es_guest(vcpu->kvm) && svm_get_cpl(vcpu) == 0;

	अगर (!kvm_छोड़ो_in_guest(vcpu->kvm))
		grow_ple_winकरोw(vcpu);

	kvm_vcpu_on_spin(vcpu, in_kernel);
	वापस kvm_skip_emulated_inकाष्ठाion(vcpu);
पूर्ण

अटल पूर्णांक invpcid_पूर्णांकerception(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अचिन्हित दीर्घ type;
	gva_t gva;

	अगर (!guest_cpuid_has(vcpu, X86_FEATURE_INVPCID)) अणु
		kvm_queue_exception(vcpu, UD_VECTOR);
		वापस 1;
	पूर्ण

	/*
	 * For an INVPCID पूर्णांकercept:
	 * EXITINFO1 provides the linear address of the memory opeअक्रम.
	 * EXITINFO2 provides the contents of the रेजिस्टर opeअक्रम.
	 */
	type = svm->vmcb->control.निकास_info_2;
	gva = svm->vmcb->control.निकास_info_1;

	अगर (type > 3) अणु
		kvm_inject_gp(vcpu, 0);
		वापस 1;
	पूर्ण

	वापस kvm_handle_invpcid(vcpu, type, gva);
पूर्ण

अटल पूर्णांक (*स्थिर svm_निकास_handlers[])(काष्ठा kvm_vcpu *vcpu) = अणु
	[SVM_EXIT_READ_CR0]			= cr_पूर्णांकerception,
	[SVM_EXIT_READ_CR3]			= cr_पूर्णांकerception,
	[SVM_EXIT_READ_CR4]			= cr_पूर्णांकerception,
	[SVM_EXIT_READ_CR8]			= cr_पूर्णांकerception,
	[SVM_EXIT_CR0_SEL_WRITE]		= cr_पूर्णांकerception,
	[SVM_EXIT_WRITE_CR0]			= cr_पूर्णांकerception,
	[SVM_EXIT_WRITE_CR3]			= cr_पूर्णांकerception,
	[SVM_EXIT_WRITE_CR4]			= cr_पूर्णांकerception,
	[SVM_EXIT_WRITE_CR8]			= cr8_ग_लिखो_पूर्णांकerception,
	[SVM_EXIT_READ_DR0]			= dr_पूर्णांकerception,
	[SVM_EXIT_READ_DR1]			= dr_पूर्णांकerception,
	[SVM_EXIT_READ_DR2]			= dr_पूर्णांकerception,
	[SVM_EXIT_READ_DR3]			= dr_पूर्णांकerception,
	[SVM_EXIT_READ_DR4]			= dr_पूर्णांकerception,
	[SVM_EXIT_READ_DR5]			= dr_पूर्णांकerception,
	[SVM_EXIT_READ_DR6]			= dr_पूर्णांकerception,
	[SVM_EXIT_READ_DR7]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR0]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR1]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR2]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR3]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR4]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR5]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR6]			= dr_पूर्णांकerception,
	[SVM_EXIT_WRITE_DR7]			= dr_पूर्णांकerception,
	[SVM_EXIT_EXCP_BASE + DB_VECTOR]	= db_पूर्णांकerception,
	[SVM_EXIT_EXCP_BASE + BP_VECTOR]	= bp_पूर्णांकerception,
	[SVM_EXIT_EXCP_BASE + UD_VECTOR]	= ud_पूर्णांकerception,
	[SVM_EXIT_EXCP_BASE + PF_VECTOR]	= pf_पूर्णांकerception,
	[SVM_EXIT_EXCP_BASE + MC_VECTOR]	= mc_पूर्णांकerception,
	[SVM_EXIT_EXCP_BASE + AC_VECTOR]	= ac_पूर्णांकerception,
	[SVM_EXIT_EXCP_BASE + GP_VECTOR]	= gp_पूर्णांकerception,
	[SVM_EXIT_INTR]				= पूर्णांकr_पूर्णांकerception,
	[SVM_EXIT_NMI]				= nmi_पूर्णांकerception,
	[SVM_EXIT_SMI]				= kvm_emulate_as_nop,
	[SVM_EXIT_INIT]				= kvm_emulate_as_nop,
	[SVM_EXIT_VINTR]			= पूर्णांकerrupt_winकरोw_पूर्णांकerception,
	[SVM_EXIT_RDPMC]			= kvm_emulate_rdpmc,
	[SVM_EXIT_CPUID]			= kvm_emulate_cpuid,
	[SVM_EXIT_IRET]                         = iret_पूर्णांकerception,
	[SVM_EXIT_INVD]                         = kvm_emulate_invd,
	[SVM_EXIT_PAUSE]			= छोड़ो_पूर्णांकerception,
	[SVM_EXIT_HLT]				= kvm_emulate_halt,
	[SVM_EXIT_INVLPG]			= invlpg_पूर्णांकerception,
	[SVM_EXIT_INVLPGA]			= invlpga_पूर्णांकerception,
	[SVM_EXIT_IOIO]				= io_पूर्णांकerception,
	[SVM_EXIT_MSR]				= msr_पूर्णांकerception,
	[SVM_EXIT_TASK_SWITCH]			= task_चयन_पूर्णांकerception,
	[SVM_EXIT_SHUTDOWN]			= shutकरोwn_पूर्णांकerception,
	[SVM_EXIT_VMRUN]			= vmrun_पूर्णांकerception,
	[SVM_EXIT_VMMCALL]			= kvm_emulate_hypercall,
	[SVM_EXIT_VMLOAD]			= vmload_पूर्णांकerception,
	[SVM_EXIT_VMSAVE]			= vmsave_पूर्णांकerception,
	[SVM_EXIT_STGI]				= stgi_पूर्णांकerception,
	[SVM_EXIT_CLGI]				= clgi_पूर्णांकerception,
	[SVM_EXIT_SKINIT]			= skinit_पूर्णांकerception,
	[SVM_EXIT_RDTSCP]			= kvm_handle_invalid_op,
	[SVM_EXIT_WBINVD]                       = kvm_emulate_wbinvd,
	[SVM_EXIT_MONITOR]			= kvm_emulate_monitor,
	[SVM_EXIT_MWAIT]			= kvm_emulate_mरुको,
	[SVM_EXIT_XSETBV]			= kvm_emulate_xsetbv,
	[SVM_EXIT_RDPRU]			= kvm_handle_invalid_op,
	[SVM_EXIT_EFER_WRITE_TRAP]		= efer_trap,
	[SVM_EXIT_CR0_WRITE_TRAP]		= cr_trap,
	[SVM_EXIT_CR4_WRITE_TRAP]		= cr_trap,
	[SVM_EXIT_CR8_WRITE_TRAP]		= cr_trap,
	[SVM_EXIT_INVPCID]                      = invpcid_पूर्णांकerception,
	[SVM_EXIT_NPF]				= npf_पूर्णांकerception,
	[SVM_EXIT_RSM]                          = rsm_पूर्णांकerception,
	[SVM_EXIT_AVIC_INCOMPLETE_IPI]		= avic_incomplete_ipi_पूर्णांकerception,
	[SVM_EXIT_AVIC_UNACCELERATED_ACCESS]	= avic_unaccelerated_access_पूर्णांकerception,
	[SVM_EXIT_VMGEXIT]			= sev_handle_vmgनिकास,
पूर्ण;

अटल व्योम dump_vmcb(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;
	काष्ठा vmcb_save_area *save = &svm->vmcb->save;
	काष्ठा vmcb_save_area *save01 = &svm->vmcb01.ptr->save;

	अगर (!dump_invalid_vmcb) अणु
		pr_warn_ratelimited("set kvm_amd.dump_invalid_vmcb=1 to dump internal KVM state.\n");
		वापस;
	पूर्ण

	pr_err("VMCB Control Area:\n");
	pr_err("%-20s%04x\n", "cr_read:", control->पूर्णांकercepts[INTERCEPT_CR] & 0xffff);
	pr_err("%-20s%04x\n", "cr_write:", control->पूर्णांकercepts[INTERCEPT_CR] >> 16);
	pr_err("%-20s%04x\n", "dr_read:", control->पूर्णांकercepts[INTERCEPT_DR] & 0xffff);
	pr_err("%-20s%04x\n", "dr_write:", control->पूर्णांकercepts[INTERCEPT_DR] >> 16);
	pr_err("%-20s%08x\n", "exceptions:", control->पूर्णांकercepts[INTERCEPT_EXCEPTION]);
	pr_err("%-20s%08x %08x\n", "intercepts:",
              control->पूर्णांकercepts[INTERCEPT_WORD3],
	       control->पूर्णांकercepts[INTERCEPT_WORD4]);
	pr_err("%-20s%d\n", "pause filter count:", control->छोड़ो_filter_count);
	pr_err("%-20s%d\n", "pause filter threshold:",
	       control->छोड़ो_filter_thresh);
	pr_err("%-20s%016llx\n", "iopm_base_pa:", control->iopm_base_pa);
	pr_err("%-20s%016llx\n", "msrpm_base_pa:", control->msrpm_base_pa);
	pr_err("%-20s%016llx\n", "tsc_offset:", control->tsc_offset);
	pr_err("%-20s%d\n", "asid:", control->asid);
	pr_err("%-20s%d\n", "tlb_ctl:", control->tlb_ctl);
	pr_err("%-20s%08x\n", "int_ctl:", control->पूर्णांक_ctl);
	pr_err("%-20s%08x\n", "int_vector:", control->पूर्णांक_vector);
	pr_err("%-20s%08x\n", "int_state:", control->पूर्णांक_state);
	pr_err("%-20s%08x\n", "exit_code:", control->निकास_code);
	pr_err("%-20s%016llx\n", "exit_info1:", control->निकास_info_1);
	pr_err("%-20s%016llx\n", "exit_info2:", control->निकास_info_2);
	pr_err("%-20s%08x\n", "exit_int_info:", control->निकास_पूर्णांक_info);
	pr_err("%-20s%08x\n", "exit_int_info_err:", control->निकास_पूर्णांक_info_err);
	pr_err("%-20s%lld\n", "nested_ctl:", control->nested_ctl);
	pr_err("%-20s%016llx\n", "nested_cr3:", control->nested_cr3);
	pr_err("%-20s%016llx\n", "avic_vapic_bar:", control->avic_vapic_bar);
	pr_err("%-20s%016llx\n", "ghcb:", control->ghcb_gpa);
	pr_err("%-20s%08x\n", "event_inj:", control->event_inj);
	pr_err("%-20s%08x\n", "event_inj_err:", control->event_inj_err);
	pr_err("%-20s%lld\n", "virt_ext:", control->virt_ext);
	pr_err("%-20s%016llx\n", "next_rip:", control->next_rip);
	pr_err("%-20s%016llx\n", "avic_backing_page:", control->avic_backing_page);
	pr_err("%-20s%016llx\n", "avic_logical_id:", control->avic_logical_id);
	pr_err("%-20s%016llx\n", "avic_physical_id:", control->avic_physical_id);
	pr_err("%-20s%016llx\n", "vmsa_pa:", control->vmsa_pa);
	pr_err("VMCB State Save Area:\n");
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "es:",
	       save->es.selector, save->es.attrib,
	       save->es.limit, save->es.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "cs:",
	       save->cs.selector, save->cs.attrib,
	       save->cs.limit, save->cs.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "ss:",
	       save->ss.selector, save->ss.attrib,
	       save->ss.limit, save->ss.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "ds:",
	       save->ds.selector, save->ds.attrib,
	       save->ds.limit, save->ds.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "fs:",
	       save01->fs.selector, save01->fs.attrib,
	       save01->fs.limit, save01->fs.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "gs:",
	       save01->gs.selector, save01->gs.attrib,
	       save01->gs.limit, save01->gs.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "gdtr:",
	       save->gdtr.selector, save->gdtr.attrib,
	       save->gdtr.limit, save->gdtr.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "ldtr:",
	       save01->ldtr.selector, save01->ldtr.attrib,
	       save01->ldtr.limit, save01->ldtr.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "idtr:",
	       save->idtr.selector, save->idtr.attrib,
	       save->idtr.limit, save->idtr.base);
	pr_err("%-5s s: %04x a: %04x l: %08x b: %016llx\n",
	       "tr:",
	       save01->tr.selector, save01->tr.attrib,
	       save01->tr.limit, save01->tr.base);
	pr_err("cpl:            %d                efer:         %016llx\n",
		save->cpl, save->efer);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "cr0:", save->cr0, "cr2:", save->cr2);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "cr3:", save->cr3, "cr4:", save->cr4);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "dr6:", save->dr6, "dr7:", save->dr7);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "rip:", save->rip, "rflags:", save->rflags);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "rsp:", save->rsp, "rax:", save->rax);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "star:", save01->star, "lstar:", save01->lstar);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "cstar:", save01->cstar, "sfmask:", save01->sfmask);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "kernel_gs_base:", save01->kernel_gs_base,
	       "sysenter_cs:", save01->sysenter_cs);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "sysenter_esp:", save01->sysenter_esp,
	       "sysenter_eip:", save01->sysenter_eip);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "gpat:", save->g_pat, "dbgctl:", save->dbgctl);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "br_from:", save->br_from, "br_to:", save->br_to);
	pr_err("%-15s %016llx %-13s %016llx\n",
	       "excp_from:", save->last_excp_from,
	       "excp_to:", save->last_excp_to);
पूर्ण

अटल पूर्णांक svm_handle_invalid_निकास(काष्ठा kvm_vcpu *vcpu, u64 निकास_code)
अणु
	अगर (निकास_code < ARRAY_SIZE(svm_निकास_handlers) &&
	    svm_निकास_handlers[निकास_code])
		वापस 0;

	vcpu_unimpl(vcpu, "svm: unexpected exit reason 0x%llx\n", निकास_code);
	dump_vmcb(vcpu);
	vcpu->run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
	vcpu->run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_UNEXPECTED_EXIT_REASON;
	vcpu->run->पूर्णांकernal.ndata = 2;
	vcpu->run->पूर्णांकernal.data[0] = निकास_code;
	vcpu->run->पूर्णांकernal.data[1] = vcpu->arch.last_vmentry_cpu;

	वापस -EINVAL;
पूर्ण

पूर्णांक svm_invoke_निकास_handler(काष्ठा kvm_vcpu *vcpu, u64 निकास_code)
अणु
	अगर (svm_handle_invalid_निकास(vcpu, निकास_code))
		वापस 0;

#अगर_घोषित CONFIG_RETPOLINE
	अगर (निकास_code == SVM_EXIT_MSR)
		वापस msr_पूर्णांकerception(vcpu);
	अन्यथा अगर (निकास_code == SVM_EXIT_VINTR)
		वापस पूर्णांकerrupt_winकरोw_पूर्णांकerception(vcpu);
	अन्यथा अगर (निकास_code == SVM_EXIT_INTR)
		वापस पूर्णांकr_पूर्णांकerception(vcpu);
	अन्यथा अगर (निकास_code == SVM_EXIT_HLT)
		वापस kvm_emulate_halt(vcpu);
	अन्यथा अगर (निकास_code == SVM_EXIT_NPF)
		वापस npf_पूर्णांकerception(vcpu);
#पूर्ण_अगर
	वापस svm_निकास_handlers[निकास_code](vcpu);
पूर्ण

अटल व्योम svm_get_निकास_info(काष्ठा kvm_vcpu *vcpu, u64 *info1, u64 *info2,
			      u32 *पूर्णांकr_info, u32 *error_code)
अणु
	काष्ठा vmcb_control_area *control = &to_svm(vcpu)->vmcb->control;

	*info1 = control->निकास_info_1;
	*info2 = control->निकास_info_2;
	*पूर्णांकr_info = control->निकास_पूर्णांक_info;
	अगर ((*पूर्णांकr_info & SVM_EXITINTINFO_VALID) &&
	    (*पूर्णांकr_info & SVM_EXITINTINFO_VALID_ERR))
		*error_code = control->निकास_पूर्णांक_info_err;
	अन्यथा
		*error_code = 0;
पूर्ण

अटल पूर्णांक handle_निकास(काष्ठा kvm_vcpu *vcpu, fastpath_t निकास_fastpath)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा kvm_run *kvm_run = vcpu->run;
	u32 निकास_code = svm->vmcb->control.निकास_code;

	trace_kvm_निकास(निकास_code, vcpu, KVM_ISA_SVM);

	/* SEV-ES guests must use the CR ग_लिखो traps to track CR रेजिस्टरs. */
	अगर (!sev_es_guest(vcpu->kvm)) अणु
		अगर (!svm_is_पूर्णांकercept(svm, INTERCEPT_CR0_WRITE))
			vcpu->arch.cr0 = svm->vmcb->save.cr0;
		अगर (npt_enabled)
			vcpu->arch.cr3 = svm->vmcb->save.cr3;
	पूर्ण

	अगर (is_guest_mode(vcpu)) अणु
		पूर्णांक vmनिकास;

		trace_kvm_nested_vmनिकास(निकास_code, vcpu, KVM_ISA_SVM);

		vmनिकास = nested_svm_निकास_special(svm);

		अगर (vmनिकास == NESTED_EXIT_CONTINUE)
			vmनिकास = nested_svm_निकास_handled(svm);

		अगर (vmनिकास == NESTED_EXIT_DONE)
			वापस 1;
	पूर्ण

	अगर (svm->vmcb->control.निकास_code == SVM_EXIT_ERR) अणु
		kvm_run->निकास_reason = KVM_EXIT_FAIL_ENTRY;
		kvm_run->fail_entry.hardware_entry_failure_reason
			= svm->vmcb->control.निकास_code;
		kvm_run->fail_entry.cpu = vcpu->arch.last_vmentry_cpu;
		dump_vmcb(vcpu);
		वापस 0;
	पूर्ण

	अगर (is_बाह्यal_पूर्णांकerrupt(svm->vmcb->control.निकास_पूर्णांक_info) &&
	    निकास_code != SVM_EXIT_EXCP_BASE + PF_VECTOR &&
	    निकास_code != SVM_EXIT_NPF && निकास_code != SVM_EXIT_TASK_SWITCH &&
	    निकास_code != SVM_EXIT_INTR && निकास_code != SVM_EXIT_NMI)
		prपूर्णांकk(KERN_ERR "%s: unexpected exit_int_info 0x%x "
		       "exit_code 0x%x\n",
		       __func__, svm->vmcb->control.निकास_पूर्णांक_info,
		       निकास_code);

	अगर (निकास_fastpath != EXIT_FASTPATH_NONE)
		वापस 1;

	वापस svm_invoke_निकास_handler(vcpu, निकास_code);
पूर्ण

अटल व्योम reload_tss(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा svm_cpu_data *sd = per_cpu(svm_data, vcpu->cpu);

	sd->tss_desc->type = 9; /* available 32/64-bit TSS */
	load_TR_desc();
पूर्ण

अटल व्योम pre_svm_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा svm_cpu_data *sd = per_cpu(svm_data, vcpu->cpu);
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * If the previous vmrun of the vmcb occurred on a dअगरferent physical
	 * cpu, then mark the vmcb dirty and assign a new asid.  Hardware's
	 * vmcb clean bits are per logical CPU, as are KVM's asid assignments.
	 */
	अगर (unlikely(svm->current_vmcb->cpu != vcpu->cpu)) अणु
		svm->current_vmcb->asid_generation = 0;
		vmcb_mark_all_dirty(svm->vmcb);
		svm->current_vmcb->cpu = vcpu->cpu;
        पूर्ण

	अगर (sev_guest(vcpu->kvm))
		वापस pre_sev_run(svm, vcpu->cpu);

	/* FIXME: handle wraparound of asid_generation */
	अगर (svm->current_vmcb->asid_generation != sd->asid_generation)
		new_asid(svm, sd);
पूर्ण

अटल व्योम svm_inject_nmi(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	svm->vmcb->control.event_inj = SVM_EVTINJ_VALID | SVM_EVTINJ_TYPE_NMI;
	vcpu->arch.hflags |= HF_NMI_MASK;
	अगर (!sev_es_guest(vcpu->kvm))
		svm_set_पूर्णांकercept(svm, INTERCEPT_IRET);
	++vcpu->stat.nmi_injections;
पूर्ण

अटल व्योम svm_set_irq(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	BUG_ON(!(gअगर_set(svm)));

	trace_kvm_inj_virq(vcpu->arch.पूर्णांकerrupt.nr);
	++vcpu->stat.irq_injections;

	svm->vmcb->control.event_inj = vcpu->arch.पूर्णांकerrupt.nr |
		SVM_EVTINJ_VALID | SVM_EVTINJ_TYPE_INTR;
पूर्ण

अटल व्योम svm_update_cr8_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu, पूर्णांक tpr, पूर्णांक irr)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * SEV-ES guests must always keep the CR पूर्णांकercepts cleared. CR
	 * tracking is करोne using the CR ग_लिखो traps.
	 */
	अगर (sev_es_guest(vcpu->kvm))
		वापस;

	अगर (nested_svm_भवize_tpr(vcpu))
		वापस;

	svm_clr_पूर्णांकercept(svm, INTERCEPT_CR8_WRITE);

	अगर (irr == -1)
		वापस;

	अगर (tpr >= irr)
		svm_set_पूर्णांकercept(svm, INTERCEPT_CR8_WRITE);
पूर्ण

bool svm_nmi_blocked(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb *vmcb = svm->vmcb;
	bool ret;

	अगर (!gअगर_set(svm))
		वापस true;

	अगर (is_guest_mode(vcpu) && nested_निकास_on_nmi(svm))
		वापस false;

	ret = (vmcb->control.पूर्णांक_state & SVM_INTERRUPT_SHADOW_MASK) ||
	      (vcpu->arch.hflags & HF_NMI_MASK);

	वापस ret;
पूर्ण

अटल पूर्णांक svm_nmi_allowed(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अगर (svm->nested.nested_run_pending)
		वापस -EBUSY;

	/* An NMI must not be injected पूर्णांकo L2 अगर it's supposed to VM-Exit.  */
	अगर (क्रम_injection && is_guest_mode(vcpu) && nested_निकास_on_nmi(svm))
		वापस -EBUSY;

	वापस !svm_nmi_blocked(vcpu);
पूर्ण

अटल bool svm_get_nmi_mask(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस !!(vcpu->arch.hflags & HF_NMI_MASK);
पूर्ण

अटल व्योम svm_set_nmi_mask(काष्ठा kvm_vcpu *vcpu, bool masked)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (masked) अणु
		vcpu->arch.hflags |= HF_NMI_MASK;
		अगर (!sev_es_guest(vcpu->kvm))
			svm_set_पूर्णांकercept(svm, INTERCEPT_IRET);
	पूर्ण अन्यथा अणु
		vcpu->arch.hflags &= ~HF_NMI_MASK;
		अगर (!sev_es_guest(vcpu->kvm))
			svm_clr_पूर्णांकercept(svm, INTERCEPT_IRET);
	पूर्ण
पूर्ण

bool svm_पूर्णांकerrupt_blocked(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb *vmcb = svm->vmcb;

	अगर (!gअगर_set(svm))
		वापस true;

	अगर (sev_es_guest(vcpu->kvm)) अणु
		/*
		 * SEV-ES guests to not expose RFLAGS. Use the VMCB पूर्णांकerrupt mask
		 * bit to determine the state of the IF flag.
		 */
		अगर (!(vmcb->control.पूर्णांक_state & SVM_GUEST_INTERRUPT_MASK))
			वापस true;
	पूर्ण अन्यथा अगर (is_guest_mode(vcpu)) अणु
		/* As दीर्घ as पूर्णांकerrupts are being delivered...  */
		अगर ((svm->nested.ctl.पूर्णांक_ctl & V_INTR_MASKING_MASK)
		    ? !(svm->vmcb01.ptr->save.rflags & X86_EFLAGS_IF)
		    : !(kvm_get_rflags(vcpu) & X86_EFLAGS_IF))
			वापस true;

		/* ... vmनिकासs aren't blocked by the पूर्णांकerrupt shaकरोw  */
		अगर (nested_निकास_on_पूर्णांकr(svm))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (!(kvm_get_rflags(vcpu) & X86_EFLAGS_IF))
			वापस true;
	पूर्ण

	वापस (vmcb->control.पूर्णांक_state & SVM_INTERRUPT_SHADOW_MASK);
पूर्ण

अटल पूर्णांक svm_पूर्णांकerrupt_allowed(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अगर (svm->nested.nested_run_pending)
		वापस -EBUSY;

	/*
	 * An IRQ must not be injected पूर्णांकo L2 अगर it's supposed to VM-Exit,
	 * e.g. अगर the IRQ arrived asynchronously after checking nested events.
	 */
	अगर (क्रम_injection && is_guest_mode(vcpu) && nested_निकास_on_पूर्णांकr(svm))
		वापस -EBUSY;

	वापस !svm_पूर्णांकerrupt_blocked(vcpu);
पूर्ण

अटल व्योम svm_enable_irq_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * In हाल GIF=0 we can't rely on the CPU to tell us when GIF becomes
	 * 1, because that's a separate STGI/VMRUN पूर्णांकercept.  The next समय we
	 * get that पूर्णांकercept, this function will be called again though and
	 * we'll get the vपूर्णांकr पूर्णांकercept. However, अगर the vGIF feature is
	 * enabled, the STGI पूर्णांकerception will not occur. Enable the irq
	 * winकरोw under the assumption that the hardware will set the GIF.
	 */
	अगर (vgअगर_enabled(svm) || gअगर_set(svm)) अणु
		/*
		 * IRQ winकरोw is not needed when AVIC is enabled,
		 * unless we have pending ExtINT since it cannot be injected
		 * via AVIC. In such हाल, we need to temporarily disable AVIC,
		 * and fallback to injecting IRQ via V_IRQ.
		 */
		svm_toggle_avic_क्रम_irq_winकरोw(vcpu, false);
		svm_set_vपूर्णांकr(svm);
	पूर्ण
पूर्ण

अटल व्योम svm_enable_nmi_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर ((vcpu->arch.hflags & (HF_NMI_MASK | HF_IRET_MASK)) == HF_NMI_MASK)
		वापस; /* IRET will cause a vm निकास */

	अगर (!gअगर_set(svm)) अणु
		अगर (vgअगर_enabled(svm))
			svm_set_पूर्णांकercept(svm, INTERCEPT_STGI);
		वापस; /* STGI will cause a vm निकास */
	पूर्ण

	/*
	 * Something prevents NMI from been injected. Single step over possible
	 * problem (IRET or exception injection or पूर्णांकerrupt shaकरोw)
	 */
	svm->nmi_singlestep_guest_rflags = svm_get_rflags(vcpu);
	svm->nmi_singlestep = true;
	svm->vmcb->save.rflags |= (X86_EFLAGS_TF | X86_EFLAGS_RF);
पूर्ण

अटल पूर्णांक svm_set_tss_addr(काष्ठा kvm *kvm, अचिन्हित पूर्णांक addr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक svm_set_identity_map_addr(काष्ठा kvm *kvm, u64 ident_addr)
अणु
	वापस 0;
पूर्ण

व्योम svm_flush_tlb(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * Flush only the current ASID even अगर the TLB flush was invoked via
	 * kvm_flush_remote_tlbs().  Although flushing remote TLBs requires all
	 * ASIDs to be flushed, KVM uses a single ASID क्रम L1 and L2, and
	 * unconditionally करोes a TLB flush on both nested VM-Enter and nested
	 * VM-Exit (via kvm_mmu_reset_context()).
	 */
	अगर (अटल_cpu_has(X86_FEATURE_FLUSHBYASID))
		svm->vmcb->control.tlb_ctl = TLB_CONTROL_FLUSH_ASID;
	अन्यथा
		svm->current_vmcb->asid_generation--;
पूर्ण

अटल व्योम svm_flush_tlb_gva(काष्ठा kvm_vcpu *vcpu, gva_t gva)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	invlpga(gva, svm->vmcb->control.asid);
पूर्ण

अटल अंतरभूत व्योम sync_cr8_to_lapic(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (nested_svm_भवize_tpr(vcpu))
		वापस;

	अगर (!svm_is_पूर्णांकercept(svm, INTERCEPT_CR8_WRITE)) अणु
		पूर्णांक cr8 = svm->vmcb->control.पूर्णांक_ctl & V_TPR_MASK;
		kvm_set_cr8(vcpu, cr8);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sync_lapic_to_cr8(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u64 cr8;

	अगर (nested_svm_भवize_tpr(vcpu) ||
	    kvm_vcpu_apicv_active(vcpu))
		वापस;

	cr8 = kvm_get_cr8(vcpu);
	svm->vmcb->control.पूर्णांक_ctl &= ~V_TPR_MASK;
	svm->vmcb->control.पूर्णांक_ctl |= cr8 & V_TPR_MASK;
पूर्ण

अटल व्योम svm_complete_पूर्णांकerrupts(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	u8 vector;
	पूर्णांक type;
	u32 निकासपूर्णांकinfo = svm->vmcb->control.निकास_पूर्णांक_info;
	अचिन्हित पूर्णांक3_injected = svm->पूर्णांक3_injected;

	svm->पूर्णांक3_injected = 0;

	/*
	 * If we've made progress since setting HF_IRET_MASK, we've
	 * executed an IRET and can allow NMI injection.
	 */
	अगर ((vcpu->arch.hflags & HF_IRET_MASK) &&
	    (sev_es_guest(vcpu->kvm) ||
	     kvm_rip_पढ़ो(vcpu) != svm->nmi_iret_rip)) अणु
		vcpu->arch.hflags &= ~(HF_NMI_MASK | HF_IRET_MASK);
		kvm_make_request(KVM_REQ_EVENT, vcpu);
	पूर्ण

	vcpu->arch.nmi_injected = false;
	kvm_clear_exception_queue(vcpu);
	kvm_clear_पूर्णांकerrupt_queue(vcpu);

	अगर (!(निकासपूर्णांकinfo & SVM_EXITINTINFO_VALID))
		वापस;

	kvm_make_request(KVM_REQ_EVENT, vcpu);

	vector = निकासपूर्णांकinfo & SVM_EXITINTINFO_VEC_MASK;
	type = निकासपूर्णांकinfo & SVM_EXITINTINFO_TYPE_MASK;

	चयन (type) अणु
	हाल SVM_EXITINTINFO_TYPE_NMI:
		vcpu->arch.nmi_injected = true;
		अवरोध;
	हाल SVM_EXITINTINFO_TYPE_EXEPT:
		/*
		 * Never re-inject a #VC exception.
		 */
		अगर (vector == X86_TRAP_VC)
			अवरोध;

		/*
		 * In हाल of software exceptions, करो not reinject the vector,
		 * but re-execute the inकाष्ठाion instead. Rewind RIP first
		 * अगर we emulated INT3 beक्रमe.
		 */
		अगर (kvm_exception_is_soft(vector)) अणु
			अगर (vector == BP_VECTOR && पूर्णांक3_injected &&
			    kvm_is_linear_rip(vcpu, svm->पूर्णांक3_rip))
				kvm_rip_ग_लिखो(vcpu,
					      kvm_rip_पढ़ो(vcpu) - पूर्णांक3_injected);
			अवरोध;
		पूर्ण
		अगर (निकासपूर्णांकinfo & SVM_EXITINTINFO_VALID_ERR) अणु
			u32 err = svm->vmcb->control.निकास_पूर्णांक_info_err;
			kvm_requeue_exception_e(vcpu, vector, err);

		पूर्ण अन्यथा
			kvm_requeue_exception(vcpu, vector);
		अवरोध;
	हाल SVM_EXITINTINFO_TYPE_INTR:
		kvm_queue_पूर्णांकerrupt(vcpu, vector, false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम svm_cancel_injection(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा vmcb_control_area *control = &svm->vmcb->control;

	control->निकास_पूर्णांक_info = control->event_inj;
	control->निकास_पूर्णांक_info_err = control->event_inj_err;
	control->event_inj = 0;
	svm_complete_पूर्णांकerrupts(vcpu);
पूर्ण

अटल fastpath_t svm_निकास_handlers_fastpath(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (to_svm(vcpu)->vmcb->control.निकास_code == SVM_EXIT_MSR &&
	    to_svm(vcpu)->vmcb->control.निकास_info_1)
		वापस handle_fastpath_set_msr_irqoff(vcpu);

	वापस EXIT_FASTPATH_NONE;
पूर्ण

अटल noinstr व्योम svm_vcpu_enter_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अचिन्हित दीर्घ vmcb_pa = svm->current_vmcb->pa;

	kvm_guest_enter_irqoff();

	अगर (sev_es_guest(vcpu->kvm)) अणु
		__svm_sev_es_vcpu_run(vmcb_pa);
	पूर्ण अन्यथा अणु
		काष्ठा svm_cpu_data *sd = per_cpu(svm_data, vcpu->cpu);

		/*
		 * Use a single vmcb (vmcb01 because it's always valid) क्रम
		 * context चयनing guest state via VMLOAD/VMSAVE, that way
		 * the state करोesn't need to be copied between vmcb01 and
		 * vmcb02 when चयनing vmcbs क्रम nested भवization.
		 */
		vmload(svm->vmcb01.pa);
		__svm_vcpu_run(vmcb_pa, (अचिन्हित दीर्घ *)&vcpu->arch.regs);
		vmsave(svm->vmcb01.pa);

		vmload(__sme_page_pa(sd->save_area));
	पूर्ण

	kvm_guest_निकास_irqoff();
पूर्ण

अटल __no_kcsan fastpath_t svm_vcpu_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	trace_kvm_entry(vcpu);

	svm->vmcb->save.rax = vcpu->arch.regs[VCPU_REGS_RAX];
	svm->vmcb->save.rsp = vcpu->arch.regs[VCPU_REGS_RSP];
	svm->vmcb->save.rip = vcpu->arch.regs[VCPU_REGS_RIP];

	/*
	 * Disable singlestep अगर we're injecting an पूर्णांकerrupt/exception.
	 * We करोn't want our modअगरied rflags to be pushed on the stack where
	 * we might not be able to easily reset them अगर we disabled NMI
	 * singlestep later.
	 */
	अगर (svm->nmi_singlestep && svm->vmcb->control.event_inj) अणु
		/*
		 * Event injection happens beक्रमe बाह्यal पूर्णांकerrupts cause a
		 * vmनिकास and पूर्णांकerrupts are disabled here, so smp_send_reschedule
		 * is enough to क्रमce an immediate vmनिकास.
		 */
		disable_nmi_singlestep(svm);
		smp_send_reschedule(vcpu->cpu);
	पूर्ण

	pre_svm_run(vcpu);

	sync_lapic_to_cr8(vcpu);

	अगर (unlikely(svm->asid != svm->vmcb->control.asid)) अणु
		svm->vmcb->control.asid = svm->asid;
		vmcb_mark_dirty(svm->vmcb, VMCB_ASID);
	पूर्ण
	svm->vmcb->save.cr2 = vcpu->arch.cr2;

	/*
	 * Run with all-zero DR6 unless needed, so that we can get the exact cause
	 * of a #DB.
	 */
	अगर (unlikely(vcpu->arch.चयन_db_regs & KVM_DEBUGREG_WONT_EXIT))
		svm_set_dr6(svm, vcpu->arch.dr6);
	अन्यथा
		svm_set_dr6(svm, DR6_ACTIVE_LOW);

	clgi();
	kvm_load_guest_xsave_state(vcpu);

	kvm_रुको_lapic_expire(vcpu);

	/*
	 * If this vCPU has touched SPEC_CTRL, restore the guest's value अगर
	 * it's non-zero. Since vmentry is serialising on affected CPUs, there
	 * is no need to worry about the conditional branch over the wrmsr
	 * being speculatively taken.
	 */
	अगर (!अटल_cpu_has(X86_FEATURE_V_SPEC_CTRL))
		x86_spec_ctrl_set_guest(svm->spec_ctrl, svm->virt_spec_ctrl);

	svm_vcpu_enter_निकास(vcpu);

	/*
	 * We करो not use IBRS in the kernel. If this vCPU has used the
	 * SPEC_CTRL MSR it may have left it on; save the value and
	 * turn it off. This is much more efficient than blindly adding
	 * it to the atomic save/restore list. Especially as the क्रमmer
	 * (Saving guest MSRs on vmनिकास) करोesn't even exist in KVM.
	 *
	 * For non-nested हाल:
	 * If the L01 MSR biपंचांगap करोes not पूर्णांकercept the MSR, then we need to
	 * save it.
	 *
	 * For nested हाल:
	 * If the L02 MSR biपंचांगap करोes not पूर्णांकercept the MSR, then we need to
	 * save it.
	 */
	अगर (!अटल_cpu_has(X86_FEATURE_V_SPEC_CTRL) &&
	    unlikely(!msr_ग_लिखो_पूर्णांकercepted(vcpu, MSR_IA32_SPEC_CTRL)))
		svm->spec_ctrl = native_पढ़ो_msr(MSR_IA32_SPEC_CTRL);

	अगर (!sev_es_guest(vcpu->kvm))
		reload_tss(vcpu);

	अगर (!अटल_cpu_has(X86_FEATURE_V_SPEC_CTRL))
		x86_spec_ctrl_restore_host(svm->spec_ctrl, svm->virt_spec_ctrl);

	अगर (!sev_es_guest(vcpu->kvm)) अणु
		vcpu->arch.cr2 = svm->vmcb->save.cr2;
		vcpu->arch.regs[VCPU_REGS_RAX] = svm->vmcb->save.rax;
		vcpu->arch.regs[VCPU_REGS_RSP] = svm->vmcb->save.rsp;
		vcpu->arch.regs[VCPU_REGS_RIP] = svm->vmcb->save.rip;
	पूर्ण

	अगर (unlikely(svm->vmcb->control.निकास_code == SVM_EXIT_NMI))
		kvm_beक्रमe_पूर्णांकerrupt(vcpu);

	kvm_load_host_xsave_state(vcpu);
	stgi();

	/* Any pending NMI will happen here */

	अगर (unlikely(svm->vmcb->control.निकास_code == SVM_EXIT_NMI))
		kvm_after_पूर्णांकerrupt(vcpu);

	sync_cr8_to_lapic(vcpu);

	svm->next_rip = 0;
	अगर (is_guest_mode(vcpu)) अणु
		nested_sync_control_from_vmcb02(svm);
		svm->nested.nested_run_pending = 0;
	पूर्ण

	svm->vmcb->control.tlb_ctl = TLB_CONTROL_DO_NOTHING;
	vmcb_mark_all_clean(svm->vmcb);

	/* अगर निकास due to PF check क्रम async PF */
	अगर (svm->vmcb->control.निकास_code == SVM_EXIT_EXCP_BASE + PF_VECTOR)
		vcpu->arch.apf.host_apf_flags =
			kvm_पढ़ो_and_reset_apf_flags();

	अगर (npt_enabled) अणु
		vcpu->arch.regs_avail &= ~(1 << VCPU_EXREG_PDPTR);
		vcpu->arch.regs_dirty &= ~(1 << VCPU_EXREG_PDPTR);
	पूर्ण

	/*
	 * We need to handle MC पूर्णांकercepts here beक्रमe the vcpu has a chance to
	 * change the physical cpu
	 */
	अगर (unlikely(svm->vmcb->control.निकास_code ==
		     SVM_EXIT_EXCP_BASE + MC_VECTOR))
		svm_handle_mce(vcpu);

	svm_complete_पूर्णांकerrupts(vcpu);

	अगर (is_guest_mode(vcpu))
		वापस EXIT_FASTPATH_NONE;

	वापस svm_निकास_handlers_fastpath(vcpu);
पूर्ण

अटल व्योम svm_load_mmu_pgd(काष्ठा kvm_vcpu *vcpu, hpa_t root_hpa,
			     पूर्णांक root_level)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अचिन्हित दीर्घ cr3;

	अगर (npt_enabled) अणु
		svm->vmcb->control.nested_cr3 = __sme_set(root_hpa);
		vmcb_mark_dirty(svm->vmcb, VMCB_NPT);

		/* Loading L2's CR3 is handled by enter_svm_guest_mode.  */
		अगर (!test_bit(VCPU_EXREG_CR3, (uदीर्घ *)&vcpu->arch.regs_avail))
			वापस;
		cr3 = vcpu->arch.cr3;
	पूर्ण अन्यथा अगर (vcpu->arch.mmu->shaकरोw_root_level >= PT64_ROOT_4LEVEL) अणु
		cr3 = __sme_set(root_hpa) | kvm_get_active_pcid(vcpu);
	पूर्ण अन्यथा अणु
		/* PCID in the guest should be impossible with a 32-bit MMU. */
		WARN_ON_ONCE(kvm_get_active_pcid(vcpu));
		cr3 = root_hpa;
	पूर्ण

	svm->vmcb->save.cr3 = cr3;
	vmcb_mark_dirty(svm->vmcb, VMCB_CR);
पूर्ण

अटल पूर्णांक is_disabled(व्योम)
अणु
	u64 vm_cr;

	rdmsrl(MSR_VM_CR, vm_cr);
	अगर (vm_cr & (1 << SVM_VM_CR_SVM_DISABLE))
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम
svm_patch_hypercall(काष्ठा kvm_vcpu *vcpu, अचिन्हित अक्षर *hypercall)
अणु
	/*
	 * Patch in the VMMCALL inकाष्ठाion:
	 */
	hypercall[0] = 0x0f;
	hypercall[1] = 0x01;
	hypercall[2] = 0xd9;
पूर्ण

अटल पूर्णांक __init svm_check_processor_compat(व्योम)
अणु
	वापस 0;
पूर्ण

अटल bool svm_cpu_has_accelerated_tpr(व्योम)
अणु
	वापस false;
पूर्ण

/*
 * The kvm parameter can be शून्य (module initialization, or invocation beक्रमe
 * VM creation). Be sure to check the kvm parameter beक्रमe using it.
 */
अटल bool svm_has_emulated_msr(काष्ठा kvm *kvm, u32 index)
अणु
	चयन (index) अणु
	हाल MSR_IA32_MCG_EXT_CTL:
	हाल MSR_IA32_VMX_BASIC ... MSR_IA32_VMX_VMFUNC:
		वापस false;
	हाल MSR_IA32_SMBASE:
		/* SEV-ES guests करो not support SMM, so report false */
		अगर (kvm && sev_es_guest(kvm))
			वापस false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल u64 svm_get_mt_mask(काष्ठा kvm_vcpu *vcpu, gfn_t gfn, bool is_mmio)
अणु
	वापस 0;
पूर्ण

अटल व्योम svm_vcpu_after_set_cpuid(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा kvm_cpuid_entry2 *best;

	vcpu->arch.xsaves_enabled = guest_cpuid_has(vcpu, X86_FEATURE_XSAVE) &&
				    boot_cpu_has(X86_FEATURE_XSAVE) &&
				    boot_cpu_has(X86_FEATURE_XSAVES);

	/* Update nrips enabled cache */
	svm->nrips_enabled = kvm_cpu_cap_has(X86_FEATURE_NRIPS) &&
			     guest_cpuid_has(vcpu, X86_FEATURE_NRIPS);

	svm_recalc_inकाष्ठाion_पूर्णांकercepts(vcpu, svm);

	/* For sev guests, the memory encryption bit is not reserved in CR3.  */
	अगर (sev_guest(vcpu->kvm)) अणु
		best = kvm_find_cpuid_entry(vcpu, 0x8000001F, 0);
		अगर (best)
			vcpu->arch.reserved_gpa_bits &= ~(1UL << (best->ebx & 0x3f));
	पूर्ण

	अगर (kvm_vcpu_apicv_active(vcpu)) अणु
		/*
		 * AVIC करोes not work with an x2APIC mode guest. If the X2APIC feature
		 * is exposed to the guest, disable AVIC.
		 */
		अगर (guest_cpuid_has(vcpu, X86_FEATURE_X2APIC))
			kvm_request_apicv_update(vcpu->kvm, false,
						 APICV_INHIBIT_REASON_X2APIC);

		/*
		 * Currently, AVIC करोes not work with nested भवization.
		 * So, we disable AVIC when cpuid क्रम SVM is set in the L1 guest.
		 */
		अगर (nested && guest_cpuid_has(vcpu, X86_FEATURE_SVM))
			kvm_request_apicv_update(vcpu->kvm, false,
						 APICV_INHIBIT_REASON_NESTED);
	पूर्ण

	अगर (guest_cpuid_is_पूर्णांकel(vcpu)) अणु
		/*
		 * We must पूर्णांकercept SYSENTER_EIP and SYSENTER_ESP
		 * accesses because the processor only stores 32 bits.
		 * For the same reason we cannot use भव VMLOAD/VMSAVE.
		 */
		svm_set_पूर्णांकercept(svm, INTERCEPT_VMLOAD);
		svm_set_पूर्णांकercept(svm, INTERCEPT_VMSAVE);
		svm->vmcb->control.virt_ext &= ~VIRTUAL_VMLOAD_VMSAVE_ENABLE_MASK;

		set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_SYSENTER_EIP, 0, 0);
		set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_SYSENTER_ESP, 0, 0);
	पूर्ण अन्यथा अणु
		/*
		 * If hardware supports Virtual VMLOAD VMSAVE then enable it
		 * in VMCB and clear पूर्णांकercepts to aव्योम #VMEXIT.
		 */
		अगर (vls) अणु
			svm_clr_पूर्णांकercept(svm, INTERCEPT_VMLOAD);
			svm_clr_पूर्णांकercept(svm, INTERCEPT_VMSAVE);
			svm->vmcb->control.virt_ext |= VIRTUAL_VMLOAD_VMSAVE_ENABLE_MASK;
		पूर्ण
		/* No need to पूर्णांकercept these MSRs */
		set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_SYSENTER_EIP, 1, 1);
		set_msr_पूर्णांकerception(vcpu, svm->msrpm, MSR_IA32_SYSENTER_ESP, 1, 1);
	पूर्ण
पूर्ण

अटल bool svm_has_wbinvd_निकास(व्योम)
अणु
	वापस true;
पूर्ण

#घोषणा PRE_EX(निकास)  अणु .निकास_code = (निकास), \
			.stage = X86_ICPT_PRE_EXCEPT, पूर्ण
#घोषणा POST_EX(निकास) अणु .निकास_code = (निकास), \
			.stage = X86_ICPT_POST_EXCEPT, पूर्ण
#घोषणा POST_MEM(निकास) अणु .निकास_code = (निकास), \
			.stage = X86_ICPT_POST_MEMACCESS, पूर्ण

अटल स्थिर काष्ठा __x86_पूर्णांकercept अणु
	u32 निकास_code;
	क्रमागत x86_पूर्णांकercept_stage stage;
पूर्ण x86_पूर्णांकercept_map[] = अणु
	[x86_पूर्णांकercept_cr_पढ़ो]		= POST_EX(SVM_EXIT_READ_CR0),
	[x86_पूर्णांकercept_cr_ग_लिखो]	= POST_EX(SVM_EXIT_WRITE_CR0),
	[x86_पूर्णांकercept_clts]		= POST_EX(SVM_EXIT_WRITE_CR0),
	[x86_पूर्णांकercept_lmsw]		= POST_EX(SVM_EXIT_WRITE_CR0),
	[x86_पूर्णांकercept_smsw]		= POST_EX(SVM_EXIT_READ_CR0),
	[x86_पूर्णांकercept_dr_पढ़ो]		= POST_EX(SVM_EXIT_READ_DR0),
	[x86_पूर्णांकercept_dr_ग_लिखो]	= POST_EX(SVM_EXIT_WRITE_DR0),
	[x86_पूर्णांकercept_sldt]		= POST_EX(SVM_EXIT_LDTR_READ),
	[x86_पूर्णांकercept_str]		= POST_EX(SVM_EXIT_TR_READ),
	[x86_पूर्णांकercept_lldt]		= POST_EX(SVM_EXIT_LDTR_WRITE),
	[x86_पूर्णांकercept_ltr]		= POST_EX(SVM_EXIT_TR_WRITE),
	[x86_पूर्णांकercept_sgdt]		= POST_EX(SVM_EXIT_GDTR_READ),
	[x86_पूर्णांकercept_sidt]		= POST_EX(SVM_EXIT_IDTR_READ),
	[x86_पूर्णांकercept_lgdt]		= POST_EX(SVM_EXIT_GDTR_WRITE),
	[x86_पूर्णांकercept_lidt]		= POST_EX(SVM_EXIT_IDTR_WRITE),
	[x86_पूर्णांकercept_vmrun]		= POST_EX(SVM_EXIT_VMRUN),
	[x86_पूर्णांकercept_vmmcall]		= POST_EX(SVM_EXIT_VMMCALL),
	[x86_पूर्णांकercept_vmload]		= POST_EX(SVM_EXIT_VMLOAD),
	[x86_पूर्णांकercept_vmsave]		= POST_EX(SVM_EXIT_VMSAVE),
	[x86_पूर्णांकercept_stgi]		= POST_EX(SVM_EXIT_STGI),
	[x86_पूर्णांकercept_clgi]		= POST_EX(SVM_EXIT_CLGI),
	[x86_पूर्णांकercept_skinit]		= POST_EX(SVM_EXIT_SKINIT),
	[x86_पूर्णांकercept_invlpga]		= POST_EX(SVM_EXIT_INVLPGA),
	[x86_पूर्णांकercept_rdtscp]		= POST_EX(SVM_EXIT_RDTSCP),
	[x86_पूर्णांकercept_monitor]		= POST_MEM(SVM_EXIT_MONITOR),
	[x86_पूर्णांकercept_mरुको]		= POST_EX(SVM_EXIT_MWAIT),
	[x86_पूर्णांकercept_invlpg]		= POST_EX(SVM_EXIT_INVLPG),
	[x86_पूर्णांकercept_invd]		= POST_EX(SVM_EXIT_INVD),
	[x86_पूर्णांकercept_wbinvd]		= POST_EX(SVM_EXIT_WBINVD),
	[x86_पूर्णांकercept_wrmsr]		= POST_EX(SVM_EXIT_MSR),
	[x86_पूर्णांकercept_rdtsc]		= POST_EX(SVM_EXIT_RDTSC),
	[x86_पूर्णांकercept_rdmsr]		= POST_EX(SVM_EXIT_MSR),
	[x86_पूर्णांकercept_rdpmc]		= POST_EX(SVM_EXIT_RDPMC),
	[x86_पूर्णांकercept_cpuid]		= PRE_EX(SVM_EXIT_CPUID),
	[x86_पूर्णांकercept_rsm]		= PRE_EX(SVM_EXIT_RSM),
	[x86_पूर्णांकercept_छोड़ो]		= PRE_EX(SVM_EXIT_PAUSE),
	[x86_पूर्णांकercept_pushf]		= PRE_EX(SVM_EXIT_PUSHF),
	[x86_पूर्णांकercept_popf]		= PRE_EX(SVM_EXIT_POPF),
	[x86_पूर्णांकercept_पूर्णांकn]		= PRE_EX(SVM_EXIT_SWINT),
	[x86_पूर्णांकercept_iret]		= PRE_EX(SVM_EXIT_IRET),
	[x86_पूर्णांकercept_icebp]		= PRE_EX(SVM_EXIT_ICEBP),
	[x86_पूर्णांकercept_hlt]		= POST_EX(SVM_EXIT_HLT),
	[x86_पूर्णांकercept_in]		= POST_EX(SVM_EXIT_IOIO),
	[x86_पूर्णांकercept_ins]		= POST_EX(SVM_EXIT_IOIO),
	[x86_पूर्णांकercept_out]		= POST_EX(SVM_EXIT_IOIO),
	[x86_पूर्णांकercept_outs]		= POST_EX(SVM_EXIT_IOIO),
	[x86_पूर्णांकercept_xsetbv]		= PRE_EX(SVM_EXIT_XSETBV),
पूर्ण;

#अघोषित PRE_EX
#अघोषित POST_EX
#अघोषित POST_MEM

अटल पूर्णांक svm_check_पूर्णांकercept(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा x86_inकाष्ठाion_info *info,
			       क्रमागत x86_पूर्णांकercept_stage stage,
			       काष्ठा x86_exception *exception)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक vmनिकास, ret = X86EMUL_CONTINUE;
	काष्ठा __x86_पूर्णांकercept icpt_info;
	काष्ठा vmcb *vmcb = svm->vmcb;

	अगर (info->पूर्णांकercept >= ARRAY_SIZE(x86_पूर्णांकercept_map))
		जाओ out;

	icpt_info = x86_पूर्णांकercept_map[info->पूर्णांकercept];

	अगर (stage != icpt_info.stage)
		जाओ out;

	चयन (icpt_info.निकास_code) अणु
	हाल SVM_EXIT_READ_CR0:
		अगर (info->पूर्णांकercept == x86_पूर्णांकercept_cr_पढ़ो)
			icpt_info.निकास_code += info->modrm_reg;
		अवरोध;
	हाल SVM_EXIT_WRITE_CR0: अणु
		अचिन्हित दीर्घ cr0, val;

		अगर (info->पूर्णांकercept == x86_पूर्णांकercept_cr_ग_लिखो)
			icpt_info.निकास_code += info->modrm_reg;

		अगर (icpt_info.निकास_code != SVM_EXIT_WRITE_CR0 ||
		    info->पूर्णांकercept == x86_पूर्णांकercept_clts)
			अवरोध;

		अगर (!(vmcb_is_पूर्णांकercept(&svm->nested.ctl,
					INTERCEPT_SELECTIVE_CR0)))
			अवरोध;

		cr0 = vcpu->arch.cr0 & ~SVM_CR0_SELECTIVE_MASK;
		val = info->src_val  & ~SVM_CR0_SELECTIVE_MASK;

		अगर (info->पूर्णांकercept == x86_पूर्णांकercept_lmsw) अणु
			cr0 &= 0xfUL;
			val &= 0xfUL;
			/* lmsw can't clear PE - catch this here */
			अगर (cr0 & X86_CR0_PE)
				val |= X86_CR0_PE;
		पूर्ण

		अगर (cr0 ^ val)
			icpt_info.निकास_code = SVM_EXIT_CR0_SEL_WRITE;

		अवरोध;
	पूर्ण
	हाल SVM_EXIT_READ_DR0:
	हाल SVM_EXIT_WRITE_DR0:
		icpt_info.निकास_code += info->modrm_reg;
		अवरोध;
	हाल SVM_EXIT_MSR:
		अगर (info->पूर्णांकercept == x86_पूर्णांकercept_wrmsr)
			vmcb->control.निकास_info_1 = 1;
		अन्यथा
			vmcb->control.निकास_info_1 = 0;
		अवरोध;
	हाल SVM_EXIT_PAUSE:
		/*
		 * We get this क्रम NOP only, but छोड़ो
		 * is rep not, check this here
		 */
		अगर (info->rep_prefix != REPE_PREFIX)
			जाओ out;
		अवरोध;
	हाल SVM_EXIT_IOIO: अणु
		u64 निकास_info;
		u32 bytes;

		अगर (info->पूर्णांकercept == x86_पूर्णांकercept_in ||
		    info->पूर्णांकercept == x86_पूर्णांकercept_ins) अणु
			निकास_info = ((info->src_val & 0xffff) << 16) |
				SVM_IOIO_TYPE_MASK;
			bytes = info->dst_bytes;
		पूर्ण अन्यथा अणु
			निकास_info = (info->dst_val & 0xffff) << 16;
			bytes = info->src_bytes;
		पूर्ण

		अगर (info->पूर्णांकercept == x86_पूर्णांकercept_outs ||
		    info->पूर्णांकercept == x86_पूर्णांकercept_ins)
			निकास_info |= SVM_IOIO_STR_MASK;

		अगर (info->rep_prefix)
			निकास_info |= SVM_IOIO_REP_MASK;

		bytes = min(bytes, 4u);

		निकास_info |= bytes << SVM_IOIO_SIZE_SHIFT;

		निकास_info |= (u32)info->ad_bytes << (SVM_IOIO_ASIZE_SHIFT - 1);

		vmcb->control.निकास_info_1 = निकास_info;
		vmcb->control.निकास_info_2 = info->next_rip;

		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	/* TODO: Advertise NRIPS to guest hypervisor unconditionally */
	अगर (अटल_cpu_has(X86_FEATURE_NRIPS))
		vmcb->control.next_rip  = info->next_rip;
	vmcb->control.निकास_code = icpt_info.निकास_code;
	vmनिकास = nested_svm_निकास_handled(svm);

	ret = (vmनिकास == NESTED_EXIT_DONE) ? X86EMUL_INTERCEPTED
					   : X86EMUL_CONTINUE;

out:
	वापस ret;
पूर्ण

अटल व्योम svm_handle_निकास_irqoff(काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण

अटल व्योम svm_sched_in(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	अगर (!kvm_छोड़ो_in_guest(vcpu->kvm))
		shrink_ple_winकरोw(vcpu);
पूर्ण

अटल व्योम svm_setup_mce(काष्ठा kvm_vcpu *vcpu)
अणु
	/* [63:9] are reserved. */
	vcpu->arch.mcg_cap &= 0x1ff;
पूर्ण

bool svm_smi_blocked(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/* Per APM Vol.2 15.22.2 "Response to SMI" */
	अगर (!gअगर_set(svm))
		वापस true;

	वापस is_smm(vcpu);
पूर्ण

अटल पूर्णांक svm_smi_allowed(काष्ठा kvm_vcpu *vcpu, bool क्रम_injection)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	अगर (svm->nested.nested_run_pending)
		वापस -EBUSY;

	/* An SMI must not be injected पूर्णांकo L2 अगर it's supposed to VM-Exit.  */
	अगर (क्रम_injection && is_guest_mode(vcpu) && nested_निकास_on_smi(svm))
		वापस -EBUSY;

	वापस !svm_smi_blocked(vcpu);
पूर्ण

अटल पूर्णांक svm_pre_enter_smm(काष्ठा kvm_vcpu *vcpu, अक्षर *smstate)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	पूर्णांक ret;

	अगर (is_guest_mode(vcpu)) अणु
		/* FED8h - SVM Guest */
		put_smstate(u64, smstate, 0x7ed8, 1);
		/* FEE0h - SVM Guest VMCB Physical Address */
		put_smstate(u64, smstate, 0x7ee0, svm->nested.vmcb12_gpa);

		svm->vmcb->save.rax = vcpu->arch.regs[VCPU_REGS_RAX];
		svm->vmcb->save.rsp = vcpu->arch.regs[VCPU_REGS_RSP];
		svm->vmcb->save.rip = vcpu->arch.regs[VCPU_REGS_RIP];

		ret = nested_svm_vmनिकास(svm);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक svm_pre_leave_smm(काष्ठा kvm_vcpu *vcpu, स्थिर अक्षर *smstate)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);
	काष्ठा kvm_host_map map;
	पूर्णांक ret = 0;

	अगर (guest_cpuid_has(vcpu, X86_FEATURE_LM)) अणु
		u64 saved_efer = GET_SMSTATE(u64, smstate, 0x7ed0);
		u64 guest = GET_SMSTATE(u64, smstate, 0x7ed8);
		u64 vmcb12_gpa = GET_SMSTATE(u64, smstate, 0x7ee0);

		अगर (guest) अणु
			अगर (!guest_cpuid_has(vcpu, X86_FEATURE_SVM))
				वापस 1;

			अगर (!(saved_efer & EFER_SVME))
				वापस 1;

			अगर (kvm_vcpu_map(vcpu,
					 gpa_to_gfn(vmcb12_gpa), &map) == -EINVAL)
				वापस 1;

			अगर (svm_allocate_nested(svm))
				वापस 1;

			ret = enter_svm_guest_mode(vcpu, vmcb12_gpa, map.hva);
			kvm_vcpu_unmap(vcpu, &map, true);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम svm_enable_smi_winकरोw(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	अगर (!gअगर_set(svm)) अणु
		अगर (vgअगर_enabled(svm))
			svm_set_पूर्णांकercept(svm, INTERCEPT_STGI);
		/* STGI will cause a vm निकास */
	पूर्ण अन्यथा अणु
		/* We must be in SMM; RSM will cause a vmनिकास anyway.  */
	पूर्ण
पूर्ण

अटल bool svm_can_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu, व्योम *insn, पूर्णांक insn_len)
अणु
	bool smep, smap, is_user;
	अचिन्हित दीर्घ cr4;

	/*
	 * When the guest is an SEV-ES guest, emulation is not possible.
	 */
	अगर (sev_es_guest(vcpu->kvm))
		वापस false;

	/*
	 * Detect and workaround Errata 1096 Fam_17h_00_0Fh.
	 *
	 * Errata:
	 * When CPU उठाओ #NPF on guest data access and vCPU CR4.SMAP=1, it is
	 * possible that CPU microcode implementing DecodeAssist will fail
	 * to पढ़ो bytes of inकाष्ठाion which caused #NPF. In this हाल,
	 * GuestIntrBytes field of the VMCB on a VMEXIT will incorrectly
	 * वापस 0 instead of the correct guest inकाष्ठाion bytes.
	 *
	 * This happens because CPU microcode पढ़ोing inकाष्ठाion bytes
	 * uses a special opcode which attempts to पढ़ो data using CPL=0
	 * privileges. The microcode पढ़ोs CS:RIP and अगर it hits a SMAP
	 * fault, it gives up and वापसs no inकाष्ठाion bytes.
	 *
	 * Detection:
	 * We reach here in हाल CPU supports DecodeAssist, उठाओd #NPF and
	 * वापसed 0 in GuestIntrBytes field of the VMCB.
	 * First, errata can only be triggered in हाल vCPU CR4.SMAP=1.
	 * Second, अगर vCPU CR4.SMEP=1, errata could only be triggered
	 * in हाल vCPU CPL==3 (Because otherwise guest would have triggered
	 * a SMEP fault instead of #NPF).
	 * Otherwise, vCPU CR4.SMEP=0, errata could be triggered by any vCPU CPL.
	 * As most guests enable SMAP अगर they have also enabled SMEP, use above
	 * logic in order to attempt minimize false-positive of detecting errata
	 * जबतक still preserving all हालs semantic correctness.
	 *
	 * Workaround:
	 * To determine what inकाष्ठाion the guest was executing, the hypervisor
	 * will have to decode the inकाष्ठाion at the inकाष्ठाion poपूर्णांकer.
	 *
	 * In non SEV guest, hypervisor will be able to पढ़ो the guest
	 * memory to decode the inकाष्ठाion poपूर्णांकer when insn_len is zero
	 * so we वापस true to indicate that decoding is possible.
	 *
	 * But in the SEV guest, the guest memory is encrypted with the
	 * guest specअगरic key and hypervisor will not be able to decode the
	 * inकाष्ठाion poपूर्णांकer so we will not able to workaround it. Lets
	 * prपूर्णांक the error and request to समाप्त the guest.
	 */
	अगर (likely(!insn || insn_len))
		वापस true;

	/*
	 * If RIP is invalid, go ahead with emulation which will cause an
	 * पूर्णांकernal error निकास.
	 */
	अगर (!kvm_vcpu_gfn_to_memslot(vcpu, kvm_rip_पढ़ो(vcpu) >> PAGE_SHIFT))
		वापस true;

	cr4 = kvm_पढ़ो_cr4(vcpu);
	smep = cr4 & X86_CR4_SMEP;
	smap = cr4 & X86_CR4_SMAP;
	is_user = svm_get_cpl(vcpu) == 3;
	अगर (smap && (!smep || is_user)) अणु
		अगर (!sev_guest(vcpu->kvm))
			वापस true;

		pr_err_ratelimited("KVM: SEV Guest triggered AMD Erratum 1096\n");
		kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
	पूर्ण

	वापस false;
पूर्ण

अटल bool svm_apic_init_संकेत_blocked(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vcpu_svm *svm = to_svm(vcpu);

	/*
	 * TODO: Last condition latch INIT संकेतs on vCPU when
	 * vCPU is in guest-mode and vmcb12 defines पूर्णांकercept on INIT.
	 * To properly emulate the INIT पूर्णांकercept,
	 * svm_check_nested_events() should call nested_svm_vmनिकास()
	 * अगर an INIT संकेत is pending.
	 */
	वापस !gअगर_set(svm) ||
		   (vmcb_is_पूर्णांकercept(&svm->vmcb->control, INTERCEPT_INIT));
पूर्ण

अटल व्योम svm_vcpu_deliver_sipi_vector(काष्ठा kvm_vcpu *vcpu, u8 vector)
अणु
	अगर (!sev_es_guest(vcpu->kvm))
		वापस kvm_vcpu_deliver_sipi_vector(vcpu, vector);

	sev_vcpu_deliver_sipi_vector(vcpu, vector);
पूर्ण

अटल व्योम svm_vm_destroy(काष्ठा kvm *kvm)
अणु
	avic_vm_destroy(kvm);
	sev_vm_destroy(kvm);
पूर्ण

अटल पूर्णांक svm_vm_init(काष्ठा kvm *kvm)
अणु
	अगर (!छोड़ो_filter_count || !छोड़ो_filter_thresh)
		kvm->arch.छोड़ो_in_guest = true;

	अगर (avic) अणु
		पूर्णांक ret = avic_vm_init(kvm);
		अगर (ret)
			वापस ret;
	पूर्ण

	kvm_apicv_init(kvm, avic);
	वापस 0;
पूर्ण

अटल काष्ठा kvm_x86_ops svm_x86_ops __initdata = अणु
	.hardware_unsetup = svm_hardware_tearकरोwn,
	.hardware_enable = svm_hardware_enable,
	.hardware_disable = svm_hardware_disable,
	.cpu_has_accelerated_tpr = svm_cpu_has_accelerated_tpr,
	.has_emulated_msr = svm_has_emulated_msr,

	.vcpu_create = svm_create_vcpu,
	.vcpu_मुक्त = svm_मुक्त_vcpu,
	.vcpu_reset = svm_vcpu_reset,

	.vm_size = माप(काष्ठा kvm_svm),
	.vm_init = svm_vm_init,
	.vm_destroy = svm_vm_destroy,

	.prepare_guest_चयन = svm_prepare_guest_चयन,
	.vcpu_load = svm_vcpu_load,
	.vcpu_put = svm_vcpu_put,
	.vcpu_blocking = svm_vcpu_blocking,
	.vcpu_unblocking = svm_vcpu_unblocking,

	.update_exception_biपंचांगap = svm_update_exception_biपंचांगap,
	.get_msr_feature = svm_get_msr_feature,
	.get_msr = svm_get_msr,
	.set_msr = svm_set_msr,
	.get_segment_base = svm_get_segment_base,
	.get_segment = svm_get_segment,
	.set_segment = svm_set_segment,
	.get_cpl = svm_get_cpl,
	.get_cs_db_l_bits = kvm_get_cs_db_l_bits,
	.set_cr0 = svm_set_cr0,
	.is_valid_cr4 = svm_is_valid_cr4,
	.set_cr4 = svm_set_cr4,
	.set_efer = svm_set_efer,
	.get_idt = svm_get_idt,
	.set_idt = svm_set_idt,
	.get_gdt = svm_get_gdt,
	.set_gdt = svm_set_gdt,
	.set_dr7 = svm_set_dr7,
	.sync_dirty_debug_regs = svm_sync_dirty_debug_regs,
	.cache_reg = svm_cache_reg,
	.get_rflags = svm_get_rflags,
	.set_rflags = svm_set_rflags,

	.tlb_flush_all = svm_flush_tlb,
	.tlb_flush_current = svm_flush_tlb,
	.tlb_flush_gva = svm_flush_tlb_gva,
	.tlb_flush_guest = svm_flush_tlb,

	.run = svm_vcpu_run,
	.handle_निकास = handle_निकास,
	.skip_emulated_inकाष्ठाion = skip_emulated_inकाष्ठाion,
	.update_emulated_inकाष्ठाion = शून्य,
	.set_पूर्णांकerrupt_shaकरोw = svm_set_पूर्णांकerrupt_shaकरोw,
	.get_पूर्णांकerrupt_shaकरोw = svm_get_पूर्णांकerrupt_shaकरोw,
	.patch_hypercall = svm_patch_hypercall,
	.set_irq = svm_set_irq,
	.set_nmi = svm_inject_nmi,
	.queue_exception = svm_queue_exception,
	.cancel_injection = svm_cancel_injection,
	.पूर्णांकerrupt_allowed = svm_पूर्णांकerrupt_allowed,
	.nmi_allowed = svm_nmi_allowed,
	.get_nmi_mask = svm_get_nmi_mask,
	.set_nmi_mask = svm_set_nmi_mask,
	.enable_nmi_winकरोw = svm_enable_nmi_winकरोw,
	.enable_irq_winकरोw = svm_enable_irq_winकरोw,
	.update_cr8_पूर्णांकercept = svm_update_cr8_पूर्णांकercept,
	.set_भव_apic_mode = svm_set_भव_apic_mode,
	.refresh_apicv_exec_ctrl = svm_refresh_apicv_exec_ctrl,
	.check_apicv_inhibit_reasons = svm_check_apicv_inhibit_reasons,
	.pre_update_apicv_exec_ctrl = svm_pre_update_apicv_exec_ctrl,
	.load_eoi_निकासmap = svm_load_eoi_निकासmap,
	.hwapic_irr_update = svm_hwapic_irr_update,
	.hwapic_isr_update = svm_hwapic_isr_update,
	.sync_pir_to_irr = kvm_lapic_find_highest_irr,
	.apicv_post_state_restore = avic_post_state_restore,

	.set_tss_addr = svm_set_tss_addr,
	.set_identity_map_addr = svm_set_identity_map_addr,
	.get_mt_mask = svm_get_mt_mask,

	.get_निकास_info = svm_get_निकास_info,

	.vcpu_after_set_cpuid = svm_vcpu_after_set_cpuid,

	.has_wbinvd_निकास = svm_has_wbinvd_निकास,

	.ग_लिखो_l1_tsc_offset = svm_ग_लिखो_l1_tsc_offset,

	.load_mmu_pgd = svm_load_mmu_pgd,

	.check_पूर्णांकercept = svm_check_पूर्णांकercept,
	.handle_निकास_irqoff = svm_handle_निकास_irqoff,

	.request_immediate_निकास = __kvm_request_immediate_निकास,

	.sched_in = svm_sched_in,

	.pmu_ops = &amd_pmu_ops,
	.nested_ops = &svm_nested_ops,

	.deliver_posted_पूर्णांकerrupt = svm_deliver_avic_पूर्णांकr,
	.dy_apicv_has_pending_पूर्णांकerrupt = svm_dy_apicv_has_pending_पूर्णांकerrupt,
	.update_pi_irte = svm_update_pi_irte,
	.setup_mce = svm_setup_mce,

	.smi_allowed = svm_smi_allowed,
	.pre_enter_smm = svm_pre_enter_smm,
	.pre_leave_smm = svm_pre_leave_smm,
	.enable_smi_winकरोw = svm_enable_smi_winकरोw,

	.mem_enc_op = svm_mem_enc_op,
	.mem_enc_reg_region = svm_रेजिस्टर_enc_region,
	.mem_enc_unreg_region = svm_unरेजिस्टर_enc_region,

	.vm_copy_enc_context_from = svm_vm_copy_asid_from,

	.can_emulate_inकाष्ठाion = svm_can_emulate_inकाष्ठाion,

	.apic_init_संकेत_blocked = svm_apic_init_संकेत_blocked,

	.msr_filter_changed = svm_msr_filter_changed,
	.complete_emulated_msr = svm_complete_emulated_msr,

	.vcpu_deliver_sipi_vector = svm_vcpu_deliver_sipi_vector,
पूर्ण;

अटल काष्ठा kvm_x86_init_ops svm_init_ops __initdata = अणु
	.cpu_has_kvm_support = has_svm,
	.disabled_by_bios = is_disabled,
	.hardware_setup = svm_hardware_setup,
	.check_processor_compatibility = svm_check_processor_compat,

	.runसमय_ops = &svm_x86_ops,
पूर्ण;

अटल पूर्णांक __init svm_init(व्योम)
अणु
	__unused_size_checks();

	वापस kvm_init(&svm_init_ops, माप(काष्ठा vcpu_svm),
			__alignof__(काष्ठा vcpu_svm), THIS_MODULE);
पूर्ण

अटल व्योम __निकास svm_निकास(व्योम)
अणु
	kvm_निकास();
पूर्ण

module_init(svm_init)
module_निकास(svm_निकास)
