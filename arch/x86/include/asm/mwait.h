<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_MWAIT_H
#घोषणा _ASM_X86_MWAIT_H

#समावेश <linux/sched.h>
#समावेश <linux/sched/idle.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/nospec-branch.h>

#घोषणा MWAIT_SUBSTATE_MASK		0xf
#घोषणा MWAIT_CSTATE_MASK		0xf
#घोषणा MWAIT_SUBSTATE_SIZE		4
#घोषणा MWAIT_HINT2CSTATE(hपूर्णांक)		(((hपूर्णांक) >> MWAIT_SUBSTATE_SIZE) & MWAIT_CSTATE_MASK)
#घोषणा MWAIT_HINT2SUBSTATE(hपूर्णांक)	((hपूर्णांक) & MWAIT_CSTATE_MASK)

#घोषणा CPUID_MWAIT_LEAF		5
#घोषणा CPUID5_ECX_EXTENSIONS_SUPPORTED 0x1
#घोषणा CPUID5_ECX_INTERRUPT_BREAK	0x2

#घोषणा MWAIT_ECX_INTERRUPT_BREAK	0x1
#घोषणा MWAITX_ECX_TIMER_ENABLE		BIT(1)
#घोषणा MWAITX_MAX_WAIT_CYCLES		अच_पूर्णांक_उच्च
#घोषणा MWAITX_DISABLE_CSTATES		0xf0
#घोषणा TPAUSE_C01_STATE		1
#घोषणा TPAUSE_C02_STATE		0

अटल अंतरभूत व्योम __monitor(स्थिर व्योम *eax, अचिन्हित दीर्घ ecx,
			     अचिन्हित दीर्घ edx)
अणु
	/* "monitor %eax, %ecx, %edx;" */
	यंत्र अस्थिर(".byte 0x0f, 0x01, 0xc8;"
		     :: "a" (eax), "c" (ecx), "d"(edx));
पूर्ण

अटल अंतरभूत व्योम __monitorx(स्थिर व्योम *eax, अचिन्हित दीर्घ ecx,
			      अचिन्हित दीर्घ edx)
अणु
	/* "monitorx %eax, %ecx, %edx;" */
	यंत्र अस्थिर(".byte 0x0f, 0x01, 0xfa;"
		     :: "a" (eax), "c" (ecx), "d"(edx));
पूर्ण

अटल अंतरभूत व्योम __mरुको(अचिन्हित दीर्घ eax, अचिन्हित दीर्घ ecx)
अणु
	mds_idle_clear_cpu_buffers();

	/* "mwait %eax, %ecx;" */
	यंत्र अस्थिर(".byte 0x0f, 0x01, 0xc9;"
		     :: "a" (eax), "c" (ecx));
पूर्ण

/*
 * MWAITX allows क्रम a समयr expiration to get the core out a रुको state in
 * addition to the शेष MWAIT निकास condition of a store appearing at a
 * monitored भव address.
 *
 * Registers:
 *
 * MWAITX ECX[1]: enable समयr अगर set
 * MWAITX EBX[31:0]: max रुको समय expressed in SW P0 घड़ीs. The software P0
 * frequency is the same as the TSC frequency.
 *
 * Below is a comparison between MWAIT and MWAITX on AMD processors:
 *
 *                 MWAIT                           MWAITX
 * opcode          0f 01 c9           |            0f 01 fb
 * ECX[0]                  value of RFLAGS.IF seen by inकाष्ठाion
 * ECX[1]          unused/#GP अगर set  |            enable समयr अगर set
 * ECX[31:2]                     unused/#GP अगर set
 * EAX                           unused (reserve क्रम hपूर्णांक)
 * EBX[31:0]       unused             |            max रुको समय (P0 घड़ीs)
 *
 *                 MONITOR                         MONITORX
 * opcode          0f 01 c8           |            0f 01 fa
 * EAX                     (logical) address to monitor
 * ECX                     #GP अगर not zero
 */
अटल अंतरभूत व्योम __mरुकोx(अचिन्हित दीर्घ eax, अचिन्हित दीर्घ ebx,
			    अचिन्हित दीर्घ ecx)
अणु
	/* No MDS buffer clear as this is AMD/HYGON only */

	/* "mwaitx %eax, %ebx, %ecx;" */
	यंत्र अस्थिर(".byte 0x0f, 0x01, 0xfb;"
		     :: "a" (eax), "b" (ebx), "c" (ecx));
पूर्ण

अटल अंतरभूत व्योम __sti_mरुको(अचिन्हित दीर्घ eax, अचिन्हित दीर्घ ecx)
अणु
	mds_idle_clear_cpu_buffers();
	/* "mwait %eax, %ecx;" */
	यंत्र अस्थिर("sti; .byte 0x0f, 0x01, 0xc9;"
		     :: "a" (eax), "c" (ecx));
पूर्ण

/*
 * This uses new MONITOR/MWAIT inकाष्ठाions on P4 processors with PNI,
 * which can obviate IPI to trigger checking of need_resched.
 * We execute MONITOR against need_resched and enter optimized रुको state
 * through MWAIT. Whenever someone changes need_resched, we would be woken
 * up from MWAIT (without an IPI).
 *
 * New with Core Duo processors, MWAIT can take some hपूर्णांकs based on CPU
 * capability.
 */
अटल अंतरभूत व्योम mरुको_idle_with_hपूर्णांकs(अचिन्हित दीर्घ eax, अचिन्हित दीर्घ ecx)
अणु
	अगर (अटल_cpu_has_bug(X86_BUG_MONITOR) || !current_set_polling_and_test()) अणु
		अगर (अटल_cpu_has_bug(X86_BUG_CLFLUSH_MONITOR)) अणु
			mb();
			clflush((व्योम *)&current_thपढ़ो_info()->flags);
			mb();
		पूर्ण

		__monitor((व्योम *)&current_thपढ़ो_info()->flags, 0, 0);
		अगर (!need_resched())
			__mरुको(eax, ecx);
	पूर्ण
	current_clr_polling();
पूर्ण

/*
 * Caller can specअगरy whether to enter C0.1 (low latency, less
 * घातer saving) or C0.2 state (saves more घातer, but दीर्घer wakeup
 * latency). This may be overridden by the IA32_UMWAIT_CONTROL MSR
 * which can क्रमce requests क्रम C0.2 to be करोwngraded to C0.1.
 */
अटल अंतरभूत व्योम __tछोड़ो(u32 ecx, u32 edx, u32 eax)
अणु
	/* "tpause %ecx, %edx, %eax;" */
	#अगर_घोषित CONFIG_AS_TPAUSE
	यंत्र अस्थिर("tpause %%ecx\n"
		     :
		     : "c"(ecx), "d"(edx), "a"(eax));
	#अन्यथा
	यंत्र अस्थिर(".byte 0x66, 0x0f, 0xae, 0xf1\t\n"
		     :
		     : "c"(ecx), "d"(edx), "a"(eax));
	#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_X86_MWAIT_H */
