<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_ASM_PROTOTYPES_H
#घोषणा _ASM_POWERPC_ASM_PROTOTYPES_H
/*
 * This file is क्रम prototypes of C functions that are only called
 * from यंत्र, and any associated variables.
 *
 * Copyright 2016, Daniel Axtens, IBM Corporation.
 */

#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/checksum.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/epapr_hcalls.h>
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/ultravisor-api.h>

#समावेश <uapi/यंत्र/ucontext.h>

/* SMP */
बाह्य काष्ठा task_काष्ठा *current_set[NR_CPUS];
बाह्य काष्ठा task_काष्ठा *secondary_current;
व्योम start_secondary(व्योम *unused);

/* kexec */
काष्ठा paca_काष्ठा;
काष्ठा kimage;
बाह्य काष्ठा paca_काष्ठा kexec_paca;
व्योम kexec_copy_flush(काष्ठा kimage *image);

/* pseries hcall tracing */
बाह्य काष्ठा अटल_key hcall_tracepoपूर्णांक_key;
व्योम __trace_hcall_entry(अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *args);
व्योम __trace_hcall_निकास(दीर्घ opcode, दीर्घ retval, अचिन्हित दीर्घ *retbuf);

/* Ultravisor */
#अगर defined(CONFIG_PPC_POWERNV) || defined(CONFIG_PPC_SVM)
दीर्घ ucall_norets(अचिन्हित दीर्घ opcode, ...);
#अन्यथा
अटल अंतरभूत दीर्घ ucall_norets(अचिन्हित दीर्घ opcode, ...)
अणु
	वापस U_NOT_AVAILABLE;
पूर्ण
#पूर्ण_अगर

/* OPAL */
पूर्णांक64_t __opal_call(पूर्णांक64_t a0, पूर्णांक64_t a1, पूर्णांक64_t a2, पूर्णांक64_t a3,
		    पूर्णांक64_t a4, पूर्णांक64_t a5, पूर्णांक64_t a6, पूर्णांक64_t a7,
		    पूर्णांक64_t opcode, uपूर्णांक64_t msr);

/* VMX copying */
पूर्णांक enter_vmx_usercopy(व्योम);
पूर्णांक निकास_vmx_usercopy(व्योम);
पूर्णांक enter_vmx_ops(व्योम);
व्योम *निकास_vmx_ops(व्योम *dest);

/* संकेतs, syscalls and पूर्णांकerrupts */
दीर्घ sys_swapcontext(काष्ठा ucontext __user *old_ctx,
		    काष्ठा ucontext __user *new_ctx,
		    दीर्घ ctx_size);
#अगर_घोषित CONFIG_PPC32
दीर्घ sys_debug_setcontext(काष्ठा ucontext __user *ctx,
			  पूर्णांक ndbg, काष्ठा sig_dbg_op __user *dbg);
पूर्णांक
ppc_select(पूर्णांक n, fd_set __user *inp, fd_set __user *outp, fd_set __user *exp,
	   काष्ठा __kernel_old_समयval __user *tvp);
अचिन्हित दीर्घ __init early_init(अचिन्हित दीर्घ dt_ptr);
व्योम __init machine_init(u64 dt_ptr);
#पूर्ण_अगर
दीर्घ प्रणाली_call_exception(दीर्घ r3, दीर्घ r4, दीर्घ r5, दीर्घ r6, दीर्घ r7, दीर्घ r8, अचिन्हित दीर्घ r0, काष्ठा pt_regs *regs);
notrace अचिन्हित दीर्घ syscall_निकास_prepare(अचिन्हित दीर्घ r3, काष्ठा pt_regs *regs, दीर्घ scv);
notrace अचिन्हित दीर्घ पूर्णांकerrupt_निकास_user_prepare(काष्ठा pt_regs *regs, अचिन्हित दीर्घ msr);
notrace अचिन्हित दीर्घ पूर्णांकerrupt_निकास_kernel_prepare(काष्ठा pt_regs *regs, अचिन्हित दीर्घ msr);

दीर्घ ppc_fadvise64_64(पूर्णांक fd, पूर्णांक advice, u32 offset_high, u32 offset_low,
		      u32 len_high, u32 len_low);
दीर्घ sys_चयन_endian(व्योम);

/* prom_init (OpenFirmware) */
अचिन्हित दीर्घ __init prom_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4,
			       अचिन्हित दीर्घ pp,
			       अचिन्हित दीर्घ r6, अचिन्हित दीर्घ r7,
			       अचिन्हित दीर्घ kbase);

/* setup */
व्योम __init early_setup(अचिन्हित दीर्घ dt_ptr);
व्योम early_setup_secondary(व्योम);

/* misc runसमय */
बाह्य u64 __bswapdi2(u64);
बाह्य s64 __lshrdi3(s64, पूर्णांक);
बाह्य s64 __ashldi3(s64, पूर्णांक);
बाह्य s64 __ashrdi3(s64, पूर्णांक);
बाह्य पूर्णांक __cmpdi2(s64, s64);
बाह्य पूर्णांक __ucmpdi2(u64, u64);

/* tracing */
व्योम _mcount(व्योम);
अचिन्हित दीर्घ prepare_ftrace_वापस(अचिन्हित दीर्घ parent, अचिन्हित दीर्घ ip,
						अचिन्हित दीर्घ sp);

व्योम pnv_घातer9_क्रमce_smt4_catch(व्योम);
व्योम pnv_घातer9_क्रमce_smt4_release(व्योम);

/* Transaction memory related */
व्योम पंचांग_enable(व्योम);
व्योम पंचांग_disable(व्योम);
व्योम पंचांग_पात(uपूर्णांक8_t cause);

काष्ठा kvm_vcpu;
व्योम _kvmppc_restore_पंचांग_pr(काष्ठा kvm_vcpu *vcpu, u64 guest_msr);
व्योम _kvmppc_save_पंचांग_pr(काष्ठा kvm_vcpu *vcpu, u64 guest_msr);

/* Patch sites */
बाह्य s32 patch__call_flush_branch_caches1;
बाह्य s32 patch__call_flush_branch_caches2;
बाह्य s32 patch__call_flush_branch_caches3;
बाह्य s32 patch__flush_count_cache_वापस;
बाह्य s32 patch__flush_link_stack_वापस;
बाह्य s32 patch__call_kvm_flush_link_stack;
बाह्य s32 patch__स_रखो_nocache, patch__स_नकल_nocache;

बाह्य दीर्घ flush_branch_caches;
बाह्य दीर्घ kvm_flush_link_stack;

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
व्योम kvmppc_save_पंचांग_hv(काष्ठा kvm_vcpu *vcpu, u64 msr, bool preserve_nv);
व्योम kvmppc_restore_पंचांग_hv(काष्ठा kvm_vcpu *vcpu, u64 msr, bool preserve_nv);
#अन्यथा
अटल अंतरभूत व्योम kvmppc_save_पंचांग_hv(काष्ठा kvm_vcpu *vcpu, u64 msr,
				     bool preserve_nv) अणु पूर्ण
अटल अंतरभूत व्योम kvmppc_restore_पंचांग_hv(काष्ठा kvm_vcpu *vcpu, u64 msr,
					bool preserve_nv) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

व्योम kvmhv_save_host_pmu(व्योम);
व्योम kvmhv_load_host_pmu(व्योम);
व्योम kvmhv_save_guest_pmu(काष्ठा kvm_vcpu *vcpu, bool pmu_in_use);
व्योम kvmhv_load_guest_pmu(काष्ठा kvm_vcpu *vcpu);

पूर्णांक __kvmhv_vcpu_entry_p9(काष्ठा kvm_vcpu *vcpu);

दीर्घ kvmppc_h_set_dabr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ dabr);
दीर्घ kvmppc_h_set_xdabr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ dabr,
			अचिन्हित दीर्घ dabrx);

#पूर्ण_अगर /* _ASM_POWERPC_ASM_PROTOTYPES_H */
