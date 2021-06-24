<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generate definitions needed by assembly language modules.
 * This code generates raw यंत्र output which is post-processed
 * to extract and क्रमmat the required data.
 */

#घोषणा ASM_OFFSETS_C 1

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/pid.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/kbuild.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/mca.h>

#समावेश "../kernel/sigframe.h"
#समावेश "../kernel/fsyscall_gtod_data.h"

व्योम foo(व्योम)
अणु
	DEFINE(IA64_TASK_SIZE, माप (काष्ठा task_काष्ठा));
	DEFINE(IA64_THREAD_INFO_SIZE, माप (काष्ठा thपढ़ो_info));
	DEFINE(IA64_PT_REGS_SIZE, माप (काष्ठा pt_regs));
	DEFINE(IA64_SWITCH_STACK_SIZE, माप (काष्ठा चयन_stack));
	DEFINE(IA64_SIGINFO_SIZE, माप (काष्ठा siginfo));
	DEFINE(IA64_CPU_SIZE, माप (काष्ठा cpuinfo_ia64));
	DEFINE(SIGFRAME_SIZE, माप (काष्ठा sigframe));
	DEFINE(UNW_FRAME_INFO_SIZE, माप (काष्ठा unw_frame_info));

	BUILD_BUG_ON(माप(काष्ठा upid) != 16);
	DEFINE(IA64_UPID_SHIFT, 4);

	BLANK();

	DEFINE(TI_FLAGS, दुरत्व(काष्ठा thपढ़ो_info, flags));
	DEFINE(TI_CPU, दुरत्व(काष्ठा thपढ़ो_info, cpu));
	DEFINE(TI_PRE_COUNT, दुरत्व(काष्ठा thपढ़ो_info, preempt_count));
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	DEFINE(TI_AC_STAMP, दुरत्व(काष्ठा thपढ़ो_info, ac_stamp));
	DEFINE(TI_AC_LEAVE, दुरत्व(काष्ठा thपढ़ो_info, ac_leave));
	DEFINE(TI_AC_STIME, दुरत्व(काष्ठा thपढ़ो_info, ac_sसमय));
	DEFINE(TI_AC_UTIME, दुरत्व(काष्ठा thपढ़ो_info, ac_uसमय));
#पूर्ण_अगर

	BLANK();

	DEFINE(IA64_TASK_BLOCKED_OFFSET,दुरत्व (काष्ठा task_काष्ठा, blocked));
	DEFINE(IA64_TASK_CLEAR_CHILD_TID_OFFSET,दुरत्व (काष्ठा task_काष्ठा, clear_child_tid));
	DEFINE(IA64_TASK_THREAD_PID_OFFSET,दुरत्व (काष्ठा task_काष्ठा, thपढ़ो_pid));
	DEFINE(IA64_PID_LEVEL_OFFSET, दुरत्व (काष्ठा pid, level));
	DEFINE(IA64_PID_UPID_OFFSET, दुरत्व (काष्ठा pid, numbers[0]));
	DEFINE(IA64_TASK_PENDING_OFFSET,दुरत्व (काष्ठा task_काष्ठा, pending));
	DEFINE(IA64_TASK_PID_OFFSET, दुरत्व (काष्ठा task_काष्ठा, pid));
	DEFINE(IA64_TASK_REAL_PARENT_OFFSET, दुरत्व (काष्ठा task_काष्ठा, real_parent));
	DEFINE(IA64_TASK_SIGNAL_OFFSET,दुरत्व (काष्ठा task_काष्ठा, संकेत));
	DEFINE(IA64_TASK_TGID_OFFSET, दुरत्व (काष्ठा task_काष्ठा, tgid));
	DEFINE(IA64_TASK_THREAD_KSP_OFFSET, दुरत्व (काष्ठा task_काष्ठा, thपढ़ो.ksp));
	DEFINE(IA64_TASK_THREAD_ON_USTACK_OFFSET, दुरत्व (काष्ठा task_काष्ठा, thपढ़ो.on_ustack));

	BLANK();


	DEFINE(IA64_SIGNAL_GROUP_STOP_COUNT_OFFSET,दुरत्व (काष्ठा संकेत_काष्ठा,
							     group_stop_count));
	DEFINE(IA64_SIGNAL_SHARED_PENDING_OFFSET,दुरत्व (काष्ठा संकेत_काष्ठा, shared_pending));
	DEFINE(IA64_SIGNAL_PIDS_TGID_OFFSET, दुरत्व (काष्ठा संकेत_काष्ठा, pids[PIDTYPE_TGID]));

	BLANK();

	DEFINE(IA64_PT_REGS_B6_OFFSET, दुरत्व (काष्ठा pt_regs, b6));
	DEFINE(IA64_PT_REGS_B7_OFFSET, दुरत्व (काष्ठा pt_regs, b7));
	DEFINE(IA64_PT_REGS_AR_CSD_OFFSET, दुरत्व (काष्ठा pt_regs, ar_csd));
	DEFINE(IA64_PT_REGS_AR_SSD_OFFSET, दुरत्व (काष्ठा pt_regs, ar_ssd));
	DEFINE(IA64_PT_REGS_R8_OFFSET, दुरत्व (काष्ठा pt_regs, r8));
	DEFINE(IA64_PT_REGS_R9_OFFSET, दुरत्व (काष्ठा pt_regs, r9));
	DEFINE(IA64_PT_REGS_R10_OFFSET, दुरत्व (काष्ठा pt_regs, r10));
	DEFINE(IA64_PT_REGS_R11_OFFSET, दुरत्व (काष्ठा pt_regs, r11));
	DEFINE(IA64_PT_REGS_CR_IPSR_OFFSET, दुरत्व (काष्ठा pt_regs, cr_ipsr));
	DEFINE(IA64_PT_REGS_CR_IIP_OFFSET, दुरत्व (काष्ठा pt_regs, cr_iip));
	DEFINE(IA64_PT_REGS_CR_IFS_OFFSET, दुरत्व (काष्ठा pt_regs, cr_अगरs));
	DEFINE(IA64_PT_REGS_AR_UNAT_OFFSET, दुरत्व (काष्ठा pt_regs, ar_unat));
	DEFINE(IA64_PT_REGS_AR_PFS_OFFSET, दुरत्व (काष्ठा pt_regs, ar_pfs));
	DEFINE(IA64_PT_REGS_AR_RSC_OFFSET, दुरत्व (काष्ठा pt_regs, ar_rsc));
	DEFINE(IA64_PT_REGS_AR_RNAT_OFFSET, दुरत्व (काष्ठा pt_regs, ar_rnat));

	DEFINE(IA64_PT_REGS_AR_BSPSTORE_OFFSET, दुरत्व (काष्ठा pt_regs, ar_bspstore));
	DEFINE(IA64_PT_REGS_PR_OFFSET, दुरत्व (काष्ठा pt_regs, pr));
	DEFINE(IA64_PT_REGS_B0_OFFSET, दुरत्व (काष्ठा pt_regs, b0));
	DEFINE(IA64_PT_REGS_LOADRS_OFFSET, दुरत्व (काष्ठा pt_regs, loadrs));
	DEFINE(IA64_PT_REGS_R1_OFFSET, दुरत्व (काष्ठा pt_regs, r1));
	DEFINE(IA64_PT_REGS_R12_OFFSET, दुरत्व (काष्ठा pt_regs, r12));
	DEFINE(IA64_PT_REGS_R13_OFFSET, दुरत्व (काष्ठा pt_regs, r13));
	DEFINE(IA64_PT_REGS_AR_FPSR_OFFSET, दुरत्व (काष्ठा pt_regs, ar_fpsr));
	DEFINE(IA64_PT_REGS_R15_OFFSET, दुरत्व (काष्ठा pt_regs, r15));
	DEFINE(IA64_PT_REGS_R14_OFFSET, दुरत्व (काष्ठा pt_regs, r14));
	DEFINE(IA64_PT_REGS_R2_OFFSET, दुरत्व (काष्ठा pt_regs, r2));
	DEFINE(IA64_PT_REGS_R3_OFFSET, दुरत्व (काष्ठा pt_regs, r3));
	DEFINE(IA64_PT_REGS_R16_OFFSET, दुरत्व (काष्ठा pt_regs, r16));
	DEFINE(IA64_PT_REGS_R17_OFFSET, दुरत्व (काष्ठा pt_regs, r17));
	DEFINE(IA64_PT_REGS_R18_OFFSET, दुरत्व (काष्ठा pt_regs, r18));
	DEFINE(IA64_PT_REGS_R19_OFFSET, दुरत्व (काष्ठा pt_regs, r19));
	DEFINE(IA64_PT_REGS_R20_OFFSET, दुरत्व (काष्ठा pt_regs, r20));
	DEFINE(IA64_PT_REGS_R21_OFFSET, दुरत्व (काष्ठा pt_regs, r21));
	DEFINE(IA64_PT_REGS_R22_OFFSET, दुरत्व (काष्ठा pt_regs, r22));
	DEFINE(IA64_PT_REGS_R23_OFFSET, दुरत्व (काष्ठा pt_regs, r23));
	DEFINE(IA64_PT_REGS_R24_OFFSET, दुरत्व (काष्ठा pt_regs, r24));
	DEFINE(IA64_PT_REGS_R25_OFFSET, दुरत्व (काष्ठा pt_regs, r25));
	DEFINE(IA64_PT_REGS_R26_OFFSET, दुरत्व (काष्ठा pt_regs, r26));
	DEFINE(IA64_PT_REGS_R27_OFFSET, दुरत्व (काष्ठा pt_regs, r27));
	DEFINE(IA64_PT_REGS_R28_OFFSET, दुरत्व (काष्ठा pt_regs, r28));
	DEFINE(IA64_PT_REGS_R29_OFFSET, दुरत्व (काष्ठा pt_regs, r29));
	DEFINE(IA64_PT_REGS_R30_OFFSET, दुरत्व (काष्ठा pt_regs, r30));
	DEFINE(IA64_PT_REGS_R31_OFFSET, दुरत्व (काष्ठा pt_regs, r31));
	DEFINE(IA64_PT_REGS_AR_CCV_OFFSET, दुरत्व (काष्ठा pt_regs, ar_ccv));
	DEFINE(IA64_PT_REGS_F6_OFFSET, दुरत्व (काष्ठा pt_regs, f6));
	DEFINE(IA64_PT_REGS_F7_OFFSET, दुरत्व (काष्ठा pt_regs, f7));
	DEFINE(IA64_PT_REGS_F8_OFFSET, दुरत्व (काष्ठा pt_regs, f8));
	DEFINE(IA64_PT_REGS_F9_OFFSET, दुरत्व (काष्ठा pt_regs, f9));
	DEFINE(IA64_PT_REGS_F10_OFFSET, दुरत्व (काष्ठा pt_regs, f10));
	DEFINE(IA64_PT_REGS_F11_OFFSET, दुरत्व (काष्ठा pt_regs, f11));

	BLANK();

	DEFINE(IA64_SWITCH_STACK_CALLER_UNAT_OFFSET, दुरत्व (काष्ठा चयन_stack, caller_unat));
	DEFINE(IA64_SWITCH_STACK_AR_FPSR_OFFSET, दुरत्व (काष्ठा चयन_stack, ar_fpsr));
	DEFINE(IA64_SWITCH_STACK_F2_OFFSET, दुरत्व (काष्ठा चयन_stack, f2));
	DEFINE(IA64_SWITCH_STACK_F3_OFFSET, दुरत्व (काष्ठा चयन_stack, f3));
	DEFINE(IA64_SWITCH_STACK_F4_OFFSET, दुरत्व (काष्ठा चयन_stack, f4));
	DEFINE(IA64_SWITCH_STACK_F5_OFFSET, दुरत्व (काष्ठा चयन_stack, f5));
	DEFINE(IA64_SWITCH_STACK_F12_OFFSET, दुरत्व (काष्ठा चयन_stack, f12));
	DEFINE(IA64_SWITCH_STACK_F13_OFFSET, दुरत्व (काष्ठा चयन_stack, f13));
	DEFINE(IA64_SWITCH_STACK_F14_OFFSET, दुरत्व (काष्ठा चयन_stack, f14));
	DEFINE(IA64_SWITCH_STACK_F15_OFFSET, दुरत्व (काष्ठा चयन_stack, f15));
	DEFINE(IA64_SWITCH_STACK_F16_OFFSET, दुरत्व (काष्ठा चयन_stack, f16));
	DEFINE(IA64_SWITCH_STACK_F17_OFFSET, दुरत्व (काष्ठा चयन_stack, f17));
	DEFINE(IA64_SWITCH_STACK_F18_OFFSET, दुरत्व (काष्ठा चयन_stack, f18));
	DEFINE(IA64_SWITCH_STACK_F19_OFFSET, दुरत्व (काष्ठा चयन_stack, f19));
	DEFINE(IA64_SWITCH_STACK_F20_OFFSET, दुरत्व (काष्ठा चयन_stack, f20));
	DEFINE(IA64_SWITCH_STACK_F21_OFFSET, दुरत्व (काष्ठा चयन_stack, f21));
	DEFINE(IA64_SWITCH_STACK_F22_OFFSET, दुरत्व (काष्ठा चयन_stack, f22));
	DEFINE(IA64_SWITCH_STACK_F23_OFFSET, दुरत्व (काष्ठा चयन_stack, f23));
	DEFINE(IA64_SWITCH_STACK_F24_OFFSET, दुरत्व (काष्ठा चयन_stack, f24));
	DEFINE(IA64_SWITCH_STACK_F25_OFFSET, दुरत्व (काष्ठा चयन_stack, f25));
	DEFINE(IA64_SWITCH_STACK_F26_OFFSET, दुरत्व (काष्ठा चयन_stack, f26));
	DEFINE(IA64_SWITCH_STACK_F27_OFFSET, दुरत्व (काष्ठा चयन_stack, f27));
	DEFINE(IA64_SWITCH_STACK_F28_OFFSET, दुरत्व (काष्ठा चयन_stack, f28));
	DEFINE(IA64_SWITCH_STACK_F29_OFFSET, दुरत्व (काष्ठा चयन_stack, f29));
	DEFINE(IA64_SWITCH_STACK_F30_OFFSET, दुरत्व (काष्ठा चयन_stack, f30));
	DEFINE(IA64_SWITCH_STACK_F31_OFFSET, दुरत्व (काष्ठा चयन_stack, f31));
	DEFINE(IA64_SWITCH_STACK_R4_OFFSET, दुरत्व (काष्ठा चयन_stack, r4));
	DEFINE(IA64_SWITCH_STACK_R5_OFFSET, दुरत्व (काष्ठा चयन_stack, r5));
	DEFINE(IA64_SWITCH_STACK_R6_OFFSET, दुरत्व (काष्ठा चयन_stack, r6));
	DEFINE(IA64_SWITCH_STACK_R7_OFFSET, दुरत्व (काष्ठा चयन_stack, r7));
	DEFINE(IA64_SWITCH_STACK_B0_OFFSET, दुरत्व (काष्ठा चयन_stack, b0));
	DEFINE(IA64_SWITCH_STACK_B1_OFFSET, दुरत्व (काष्ठा चयन_stack, b1));
	DEFINE(IA64_SWITCH_STACK_B2_OFFSET, दुरत्व (काष्ठा चयन_stack, b2));
	DEFINE(IA64_SWITCH_STACK_B3_OFFSET, दुरत्व (काष्ठा चयन_stack, b3));
	DEFINE(IA64_SWITCH_STACK_B4_OFFSET, दुरत्व (काष्ठा चयन_stack, b4));
	DEFINE(IA64_SWITCH_STACK_B5_OFFSET, दुरत्व (काष्ठा चयन_stack, b5));
	DEFINE(IA64_SWITCH_STACK_AR_PFS_OFFSET, दुरत्व (काष्ठा चयन_stack, ar_pfs));
	DEFINE(IA64_SWITCH_STACK_AR_LC_OFFSET, दुरत्व (काष्ठा चयन_stack, ar_lc));
	DEFINE(IA64_SWITCH_STACK_AR_UNAT_OFFSET, दुरत्व (काष्ठा चयन_stack, ar_unat));
	DEFINE(IA64_SWITCH_STACK_AR_RNAT_OFFSET, दुरत्व (काष्ठा चयन_stack, ar_rnat));
	DEFINE(IA64_SWITCH_STACK_AR_BSPSTORE_OFFSET, दुरत्व (काष्ठा चयन_stack, ar_bspstore));
	DEFINE(IA64_SWITCH_STACK_PR_OFFSET, दुरत्व (काष्ठा चयन_stack, pr));

	BLANK();

	DEFINE(IA64_SIGCONTEXT_IP_OFFSET, दुरत्व (काष्ठा sigcontext, sc_ip));
	DEFINE(IA64_SIGCONTEXT_AR_BSP_OFFSET, दुरत्व (काष्ठा sigcontext, sc_ar_bsp));
	DEFINE(IA64_SIGCONTEXT_AR_FPSR_OFFSET, दुरत्व (काष्ठा sigcontext, sc_ar_fpsr));
	DEFINE(IA64_SIGCONTEXT_AR_RNAT_OFFSET, दुरत्व (काष्ठा sigcontext, sc_ar_rnat));
	DEFINE(IA64_SIGCONTEXT_AR_UNAT_OFFSET, दुरत्व (काष्ठा sigcontext, sc_ar_unat));
	DEFINE(IA64_SIGCONTEXT_B0_OFFSET, दुरत्व (काष्ठा sigcontext, sc_br[0]));
	DEFINE(IA64_SIGCONTEXT_CFM_OFFSET, दुरत्व (काष्ठा sigcontext, sc_cfm));
	DEFINE(IA64_SIGCONTEXT_FLAGS_OFFSET, दुरत्व (काष्ठा sigcontext, sc_flags));
	DEFINE(IA64_SIGCONTEXT_FR6_OFFSET, दुरत्व (काष्ठा sigcontext, sc_fr[6]));
	DEFINE(IA64_SIGCONTEXT_PR_OFFSET, दुरत्व (काष्ठा sigcontext, sc_pr));
	DEFINE(IA64_SIGCONTEXT_R12_OFFSET, दुरत्व (काष्ठा sigcontext, sc_gr[12]));
	DEFINE(IA64_SIGCONTEXT_RBS_BASE_OFFSET,दुरत्व (काष्ठा sigcontext, sc_rbs_base));
	DEFINE(IA64_SIGCONTEXT_LOADRS_OFFSET, दुरत्व (काष्ठा sigcontext, sc_loadrs));

	BLANK();

	DEFINE(IA64_SIGPENDING_SIGNAL_OFFSET, दुरत्व (काष्ठा संक_बाकी, संकेत));

	BLANK();

	DEFINE(IA64_SIGFRAME_ARG0_OFFSET, दुरत्व (काष्ठा sigframe, arg0));
	DEFINE(IA64_SIGFRAME_ARG1_OFFSET, दुरत्व (काष्ठा sigframe, arg1));
	DEFINE(IA64_SIGFRAME_ARG2_OFFSET, दुरत्व (काष्ठा sigframe, arg2));
	DEFINE(IA64_SIGFRAME_HANDLER_OFFSET, दुरत्व (काष्ठा sigframe, handler));
	DEFINE(IA64_SIGFRAME_SIGCONTEXT_OFFSET, दुरत्व (काष्ठा sigframe, sc));
	BLANK();
    /* क्रम assembly files which can't include sched.h: */
	DEFINE(IA64_CLONE_VFORK, CLONE_VFORK);
	DEFINE(IA64_CLONE_VM, CLONE_VM);

	BLANK();
	DEFINE(IA64_CPUINFO_NSEC_PER_CYC_OFFSET,
	       दुरत्व (काष्ठा cpuinfo_ia64, nsec_per_cyc));
	DEFINE(IA64_CPUINFO_PTCE_BASE_OFFSET,
	       दुरत्व (काष्ठा cpuinfo_ia64, ptce_base));
	DEFINE(IA64_CPUINFO_PTCE_COUNT_OFFSET,
	       दुरत्व (काष्ठा cpuinfo_ia64, ptce_count));
	DEFINE(IA64_CPUINFO_PTCE_STRIDE_OFFSET,
	       दुरत्व (काष्ठा cpuinfo_ia64, ptce_stride));
	BLANK();
	DEFINE(IA64_TIMESPEC_TV_NSEC_OFFSET,
	       दुरत्व (काष्ठा __kernel_old_बारpec, tv_nsec));
	DEFINE(IA64_TIME_SN_SPEC_SNSEC_OFFSET,
	       दुरत्व (काष्ठा समय_sn_spec, snsec));

	DEFINE(CLONE_SETTLS_BIT, 19);
#अगर CLONE_SETTLS != (1<<19)
# error "CLONE_SETTLS_BIT incorrect, please fix"
#पूर्ण_अगर

	BLANK();
	DEFINE(IA64_MCA_CPU_MCA_STACK_OFFSET,
	       दुरत्व (काष्ठा ia64_mca_cpu, mca_stack));
	DEFINE(IA64_MCA_CPU_INIT_STACK_OFFSET,
	       दुरत्व (काष्ठा ia64_mca_cpu, init_stack));
	BLANK();
	DEFINE(IA64_SAL_OS_STATE_OS_GP_OFFSET,
	       दुरत्व (काष्ठा ia64_sal_os_state, os_gp));
	DEFINE(IA64_SAL_OS_STATE_PROC_STATE_PARAM_OFFSET,
	       दुरत्व (काष्ठा ia64_sal_os_state, proc_state_param));
	DEFINE(IA64_SAL_OS_STATE_SAL_RA_OFFSET,
	       दुरत्व (काष्ठा ia64_sal_os_state, sal_ra));
	DEFINE(IA64_SAL_OS_STATE_SAL_GP_OFFSET,
	       दुरत्व (काष्ठा ia64_sal_os_state, sal_gp));
	DEFINE(IA64_SAL_OS_STATE_PAL_MIN_STATE_OFFSET,
	       दुरत्व (काष्ठा ia64_sal_os_state, pal_min_state));
	DEFINE(IA64_SAL_OS_STATE_OS_STATUS_OFFSET,
	       दुरत्व (काष्ठा ia64_sal_os_state, os_status));
	DEFINE(IA64_SAL_OS_STATE_CONTEXT_OFFSET,
	       दुरत्व (काष्ठा ia64_sal_os_state, context));
	DEFINE(IA64_SAL_OS_STATE_SIZE,
	       माप (काष्ठा ia64_sal_os_state));
	BLANK();

	DEFINE(IA64_PMSA_GR_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_gr));
	DEFINE(IA64_PMSA_BANK1_GR_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_bank1_gr));
	DEFINE(IA64_PMSA_PR_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_pr));
	DEFINE(IA64_PMSA_BR0_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_br0));
	DEFINE(IA64_PMSA_RSC_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_rsc));
	DEFINE(IA64_PMSA_IIP_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_iip));
	DEFINE(IA64_PMSA_IPSR_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_ipsr));
	DEFINE(IA64_PMSA_IFS_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_अगरs));
	DEFINE(IA64_PMSA_XIP_OFFSET,
	       दुरत्व(काष्ठा pal_min_state_area, pmsa_xip));
	BLANK();

	/* used by fsys_समय_लोofday in arch/ia64/kernel/fsys.S */
	DEFINE(IA64_GTOD_SEQ_OFFSET,
	       दुरत्व (काष्ठा fsyscall_gtod_data_t, seq));
	DEFINE(IA64_GTOD_WALL_TIME_OFFSET,
		दुरत्व (काष्ठा fsyscall_gtod_data_t, wall_समय));
	DEFINE(IA64_GTOD_MONO_TIME_OFFSET,
		दुरत्व (काष्ठा fsyscall_gtod_data_t, monotonic_समय));
	DEFINE(IA64_CLKSRC_MASK_OFFSET,
		दुरत्व (काष्ठा fsyscall_gtod_data_t, clk_mask));
	DEFINE(IA64_CLKSRC_MULT_OFFSET,
		दुरत्व (काष्ठा fsyscall_gtod_data_t, clk_mult));
	DEFINE(IA64_CLKSRC_SHIFT_OFFSET,
		दुरत्व (काष्ठा fsyscall_gtod_data_t, clk_shअगरt));
	DEFINE(IA64_CLKSRC_MMIO_OFFSET,
		दुरत्व (काष्ठा fsyscall_gtod_data_t, clk_fsys_mmio));
	DEFINE(IA64_CLKSRC_CYCLE_LAST_OFFSET,
		दुरत्व (काष्ठा fsyscall_gtod_data_t, clk_cycle_last));
	DEFINE(IA64_ITC_JITTER_OFFSET,
		दुरत्व (काष्ठा itc_jitter_data_t, itc_jitter));
	DEFINE(IA64_ITC_LASTCYCLE_OFFSET,
		दुरत्व (काष्ठा itc_jitter_data_t, itc_lastcycle));

पूर्ण
