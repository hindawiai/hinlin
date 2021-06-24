<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_VMXFEATURES_H
#घोषणा _ASM_X86_VMXFEATURES_H

/*
 * Defines VMX CPU feature bits
 */
#घोषणा NVMXINTS			3 /* N 32-bit words worth of info */

/*
 * Note: If the comment begins with a quoted string, that string is used
 * in /proc/cpuinfo instead of the macro name.  If the string is "",
 * this feature bit is not displayed in /proc/cpuinfo at all.
 */

/* Pin-Based VM-Execution Controls, EPT/VPID, APIC and VM-Functions, word 0 */
#घोषणा VMX_FEATURE_INTR_EXITING	( 0*32+  0) /* "" VM-Exit on vectored पूर्णांकerrupts */
#घोषणा VMX_FEATURE_NMI_EXITING		( 0*32+  3) /* "" VM-Exit on NMIs */
#घोषणा VMX_FEATURE_VIRTUAL_NMIS	( 0*32+  5) /* "vnmi" NMI भवization */
#घोषणा VMX_FEATURE_PREEMPTION_TIMER	( 0*32+  6) /* VMX Preemption Timer */
#घोषणा VMX_FEATURE_POSTED_INTR		( 0*32+  7) /* Posted Interrupts */

/* EPT/VPID features, scattered to bits 16-23 */
#घोषणा VMX_FEATURE_INVVPID		( 0*32+ 16) /* INVVPID is supported */
#घोषणा VMX_FEATURE_EPT_EXECUTE_ONLY	( 0*32+ 17) /* "ept_x_only" EPT entries can be execute only */
#घोषणा VMX_FEATURE_EPT_AD		( 0*32+ 18) /* EPT Accessed/Dirty bits */
#घोषणा VMX_FEATURE_EPT_1GB		( 0*32+ 19) /* 1GB EPT pages */

/* Aggregated APIC features 24-27 */
#घोषणा VMX_FEATURE_FLEXPRIORITY	( 0*32+ 24) /* TPR shaकरोw + virt APIC */
#घोषणा VMX_FEATURE_APICV	        ( 0*32+ 25) /* TPR shaकरोw + APIC reg virt + virt पूर्णांकr delivery + posted पूर्णांकerrupts */

/* VM-Functions, shअगरted to bits 28-31 */
#घोषणा VMX_FEATURE_EPTP_SWITCHING	( 0*32+ 28) /* EPTP चयनing (in guest) */

/* Primary Processor-Based VM-Execution Controls, word 1 */
#घोषणा VMX_FEATURE_INTR_WINDOW_EXITING ( 1*32+  2) /* "" VM-Exit अगर INTRs are unblocked in guest */
#घोषणा VMX_FEATURE_USE_TSC_OFFSETTING	( 1*32+  3) /* "tsc_offset" Offset hardware TSC when पढ़ो in guest */
#घोषणा VMX_FEATURE_HLT_EXITING		( 1*32+  7) /* "" VM-Exit on HLT */
#घोषणा VMX_FEATURE_INVLPG_EXITING	( 1*32+  9) /* "" VM-Exit on INVLPG */
#घोषणा VMX_FEATURE_MWAIT_EXITING	( 1*32+ 10) /* "" VM-Exit on MWAIT */
#घोषणा VMX_FEATURE_RDPMC_EXITING	( 1*32+ 11) /* "" VM-Exit on RDPMC */
#घोषणा VMX_FEATURE_RDTSC_EXITING	( 1*32+ 12) /* "" VM-Exit on RDTSC */
#घोषणा VMX_FEATURE_CR3_LOAD_EXITING	( 1*32+ 15) /* "" VM-Exit on ग_लिखोs to CR3 */
#घोषणा VMX_FEATURE_CR3_STORE_EXITING	( 1*32+ 16) /* "" VM-Exit on पढ़ोs from CR3 */
#घोषणा VMX_FEATURE_CR8_LOAD_EXITING	( 1*32+ 19) /* "" VM-Exit on ग_लिखोs to CR8 */
#घोषणा VMX_FEATURE_CR8_STORE_EXITING	( 1*32+ 20) /* "" VM-Exit on पढ़ोs from CR8 */
#घोषणा VMX_FEATURE_VIRTUAL_TPR		( 1*32+ 21) /* "vtpr" TPR भवization, a.k.a. TPR shaकरोw */
#घोषणा VMX_FEATURE_NMI_WINDOW_EXITING	( 1*32+ 22) /* "" VM-Exit अगर NMIs are unblocked in guest */
#घोषणा VMX_FEATURE_MOV_DR_EXITING	( 1*32+ 23) /* "" VM-Exit on accesses to debug रेजिस्टरs */
#घोषणा VMX_FEATURE_UNCOND_IO_EXITING	( 1*32+ 24) /* "" VM-Exit on *all* INअणुSपूर्ण and OUTअणुSपूर्ण*/
#घोषणा VMX_FEATURE_USE_IO_BITMAPS	( 1*32+ 25) /* "" VM-Exit based on I/O port */
#घोषणा VMX_FEATURE_MONITOR_TRAP_FLAG	( 1*32+ 27) /* "mtf" VMX single-step VM-Exits */
#घोषणा VMX_FEATURE_USE_MSR_BITMAPS	( 1*32+ 28) /* "" VM-Exit based on MSR index */
#घोषणा VMX_FEATURE_MONITOR_EXITING	( 1*32+ 29) /* "" VM-Exit on MONITOR (MWAIT's accomplice) */
#घोषणा VMX_FEATURE_PAUSE_EXITING	( 1*32+ 30) /* "" VM-Exit on PAUSE (unconditionally) */
#घोषणा VMX_FEATURE_SEC_CONTROLS	( 1*32+ 31) /* "" Enable Secondary VM-Execution Controls */

/* Secondary Processor-Based VM-Execution Controls, word 2 */
#घोषणा VMX_FEATURE_VIRT_APIC_ACCESSES	( 2*32+  0) /* "vapic" Virtualize memory mapped APIC accesses */
#घोषणा VMX_FEATURE_EPT			( 2*32+  1) /* Extended Page Tables, a.k.a. Two-Dimensional Paging */
#घोषणा VMX_FEATURE_DESC_EXITING	( 2*32+  2) /* "" VM-Exit on अणुS,Lपूर्ण*DT inकाष्ठाions */
#घोषणा VMX_FEATURE_RDTSCP		( 2*32+  3) /* "" Enable RDTSCP in guest */
#घोषणा VMX_FEATURE_VIRTUAL_X2APIC	( 2*32+  4) /* "" Virtualize X2APIC क्रम the guest */
#घोषणा VMX_FEATURE_VPID		( 2*32+  5) /* Virtual Processor ID (TLB ASID modअगरier) */
#घोषणा VMX_FEATURE_WBINVD_EXITING	( 2*32+  6) /* "" VM-Exit on WBINVD */
#घोषणा VMX_FEATURE_UNRESTRICTED_GUEST	( 2*32+  7) /* Allow Big Real Mode and other "invalid" states */
#घोषणा VMX_FEATURE_APIC_REGISTER_VIRT	( 2*32+  8) /* "vapic_reg" Hardware emulation of पढ़ोs to the भव-APIC */
#घोषणा VMX_FEATURE_VIRT_INTR_DELIVERY	( 2*32+  9) /* "vid" Evaluation and delivery of pending भव पूर्णांकerrupts */
#घोषणा VMX_FEATURE_PAUSE_LOOP_EXITING	( 2*32+ 10) /* "ple" Conditionally VM-Exit on PAUSE at CPL0 */
#घोषणा VMX_FEATURE_RDRAND_EXITING	( 2*32+ 11) /* "" VM-Exit on RDRAND*/
#घोषणा VMX_FEATURE_INVPCID		( 2*32+ 12) /* "" Enable INVPCID in guest */
#घोषणा VMX_FEATURE_VMFUNC		( 2*32+ 13) /* "" Enable VM-Functions (leaf dependent) */
#घोषणा VMX_FEATURE_SHADOW_VMCS		( 2*32+ 14) /* VMREAD/VMWRITE in guest can access shaकरोw VMCS */
#घोषणा VMX_FEATURE_ENCLS_EXITING	( 2*32+ 15) /* "" VM-Exit on ENCLS (leaf dependent) */
#घोषणा VMX_FEATURE_RDSEED_EXITING	( 2*32+ 16) /* "" VM-Exit on RDSEED */
#घोषणा VMX_FEATURE_PAGE_MOD_LOGGING	( 2*32+ 17) /* "pml" Log dirty pages पूर्णांकo buffer */
#घोषणा VMX_FEATURE_EPT_VIOLATION_VE	( 2*32+ 18) /* "" Conditionally reflect EPT violations as #VE exceptions */
#घोषणा VMX_FEATURE_PT_CONCEAL_VMX	( 2*32+ 19) /* "" Suppress VMX indicators in Processor Trace */
#घोषणा VMX_FEATURE_XSAVES		( 2*32+ 20) /* "" Enable XSAVES and XRSTORS in guest */
#घोषणा VMX_FEATURE_MODE_BASED_EPT_EXEC	( 2*32+ 22) /* "ept_mode_based_exec" Enable separate EPT EXEC bits क्रम supervisor vs. user */
#घोषणा VMX_FEATURE_PT_USE_GPA		( 2*32+ 24) /* "" Processor Trace logs GPAs */
#घोषणा VMX_FEATURE_TSC_SCALING		( 2*32+ 25) /* Scale hardware TSC when पढ़ो in guest */
#घोषणा VMX_FEATURE_USR_WAIT_PAUSE	( 2*32+ 26) /* Enable TPAUSE, UMONITOR, UMWAIT in guest */
#घोषणा VMX_FEATURE_ENCLV_EXITING	( 2*32+ 28) /* "" VM-Exit on ENCLV (leaf dependent) */
#घोषणा VMX_FEATURE_BUS_LOCK_DETECTION	( 2*32+ 30) /* "" VM-Exit when bus lock caused */

#पूर्ण_अगर /* _ASM_X86_VMXFEATURES_H */
