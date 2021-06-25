<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generate definitions needed by assembly language modules.
 * This code generates raw यंत्र output which is post-processed to extract
 * and क्रमmat the required data.
 */
#घोषणा COMPILE_OFFSETS

#समावेश <linux/crypto.h>
#समावेश <linux/sched.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/suspend.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/sigframe.h>
#समावेश <यंत्र/bootparam.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/tlbflush.h>

#अगर_घोषित CONFIG_XEN
#समावेश <xen/पूर्णांकerface/xen.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_32
# include "asm-offsets_32.c"
#अन्यथा
# include "asm-offsets_64.c"
#पूर्ण_अगर

अटल व्योम __used common(व्योम)
अणु
	BLANK();
	OFFSET(TASK_thपढ़ोsp, task_काष्ठा, thपढ़ो.sp);
#अगर_घोषित CONFIG_STACKPROTECTOR
	OFFSET(TASK_stack_canary, task_काष्ठा, stack_canary);
#पूर्ण_अगर

	BLANK();
	OFFSET(crypto_tfm_ctx_offset, crypto_tfm, __crt_ctx);

	BLANK();
	OFFSET(pbe_address, pbe, address);
	OFFSET(pbe_orig_address, pbe, orig_address);
	OFFSET(pbe_next, pbe, next);

#अगर defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMULATION)
	BLANK();
	OFFSET(IA32_SIGCONTEXT_ax, sigcontext_32, ax);
	OFFSET(IA32_SIGCONTEXT_bx, sigcontext_32, bx);
	OFFSET(IA32_SIGCONTEXT_cx, sigcontext_32, cx);
	OFFSET(IA32_SIGCONTEXT_dx, sigcontext_32, dx);
	OFFSET(IA32_SIGCONTEXT_si, sigcontext_32, si);
	OFFSET(IA32_SIGCONTEXT_di, sigcontext_32, di);
	OFFSET(IA32_SIGCONTEXT_bp, sigcontext_32, bp);
	OFFSET(IA32_SIGCONTEXT_sp, sigcontext_32, sp);
	OFFSET(IA32_SIGCONTEXT_ip, sigcontext_32, ip);

	BLANK();
	OFFSET(IA32_RT_SIGFRAME_sigcontext, rt_sigframe_ia32, uc.uc_mcontext);
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN
	BLANK();
	OFFSET(XEN_vcpu_info_mask, vcpu_info, evtchn_upcall_mask);
	OFFSET(XEN_vcpu_info_pending, vcpu_info, evtchn_upcall_pending);
	OFFSET(XEN_vcpu_info_arch_cr2, vcpu_info, arch.cr2);
#पूर्ण_अगर

	BLANK();
	OFFSET(BP_scratch, boot_params, scratch);
	OFFSET(BP_secure_boot, boot_params, secure_boot);
	OFFSET(BP_loadflags, boot_params, hdr.loadflags);
	OFFSET(BP_hardware_subarch, boot_params, hdr.hardware_subarch);
	OFFSET(BP_version, boot_params, hdr.version);
	OFFSET(BP_kernel_alignment, boot_params, hdr.kernel_alignment);
	OFFSET(BP_init_size, boot_params, hdr.init_size);
	OFFSET(BP_pref_address, boot_params, hdr.pref_address);

	BLANK();
	DEFINE(PTREGS_SIZE, माप(काष्ठा pt_regs));

	/* TLB state क्रम the entry code */
	OFFSET(TLB_STATE_user_pcid_flush_mask, tlb_state, user_pcid_flush_mask);

	/* Layout info क्रम cpu_entry_area */
	OFFSET(CPU_ENTRY_AREA_entry_stack, cpu_entry_area, entry_stack_page);
	DEFINE(SIZखातापूर्ण_entry_stack, माप(काष्ठा entry_stack));
	DEFINE(MASK_entry_stack, (~(माप(काष्ठा entry_stack) - 1)));

	/* Offset क्रम fields in tss_काष्ठा */
	OFFSET(TSS_sp0, tss_काष्ठा, x86_tss.sp0);
	OFFSET(TSS_sp1, tss_काष्ठा, x86_tss.sp1);
	OFFSET(TSS_sp2, tss_काष्ठा, x86_tss.sp2);
पूर्ण
