<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2009 Freescale Semiconductor, Inc.
 *
 * provides masks and opcode images क्रम use by code generation, emulation
 * and क्रम inकाष्ठाions that older assemblers might not know about
 */
#अगर_अघोषित _ASM_POWERPC_DBELL_H
#घोषणा _ASM_POWERPC_DBELL_H

#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/feature-fixups.h>
#समावेश <यंत्र/kvm_ppc.h>

#घोषणा PPC_DBELL_MSG_BRDCAST	(0x04000000)
#घोषणा PPC_DBELL_TYPE(x)	(((x) & 0xf) << (63-36))
#घोषणा PPC_DBELL_TYPE_MASK	PPC_DBELL_TYPE(0xf)
#घोषणा PPC_DBELL_LPID(x)	((x) << (63 - 49))
#घोषणा PPC_DBELL_PIR_MASK	0x3fff
क्रमागत ppc_dbell अणु
	PPC_DBELL = 0,		/* करोorbell */
	PPC_DBELL_CRIT = 1,	/* critical करोorbell */
	PPC_G_DBELL = 2,	/* guest करोorbell */
	PPC_G_DBELL_CRIT = 3,	/* guest critical करोorbell */
	PPC_G_DBELL_MC = 4,	/* guest mcheck करोorbell */
	PPC_DBELL_SERVER = 5,	/* करोorbell on server */
पूर्ण;

#अगर_घोषित CONFIG_PPC_BOOK3S

#घोषणा PPC_DBELL_MSGTYPE		PPC_DBELL_SERVER

अटल अंतरभूत व्योम _ppc_msgsnd(u32 msg)
अणु
	__यंत्र__ __अस्थिर__ (ASM_FTR_IFSET(PPC_MSGSND(%1), PPC_MSGSNDP(%1), %0)
				: : "i" (CPU_FTR_HVMODE), "r" (msg));
पूर्ण

/* sync beक्रमe sending message */
अटल अंतरभूत व्योम ppc_msgsnd_sync(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
पूर्ण

/* sync after taking message पूर्णांकerrupt */
अटल अंतरभूत व्योम ppc_msgsync(व्योम)
अणु
	/* sync is not required when taking messages from the same core */
	__यंत्र__ __अस्थिर__ (ASM_FTR_IFSET(PPC_MSGSYNC " ; lwsync", "", %0)
				: : "i" (CPU_FTR_HVMODE|CPU_FTR_ARCH_300));
पूर्ण

अटल अंतरभूत व्योम _ppc_msgclr(u32 msg)
अणु
	__यंत्र__ __अस्थिर__ (ASM_FTR_IFSET(PPC_MSGCLR(%1), PPC_MSGCLRP(%1), %0)
				: : "i" (CPU_FTR_HVMODE), "r" (msg));
पूर्ण

अटल अंतरभूत व्योम ppc_msgclr(क्रमागत ppc_dbell type)
अणु
	u32 msg = PPC_DBELL_TYPE(type);

	_ppc_msgclr(msg);
पूर्ण

#अन्यथा /* CONFIG_PPC_BOOK3S */

#घोषणा PPC_DBELL_MSGTYPE		PPC_DBELL

अटल अंतरभूत व्योम _ppc_msgsnd(u32 msg)
अणु
	__यंत्र__ __अस्थिर__ (PPC_MSGSND(%0) : : "r" (msg));
पूर्ण

/* sync beक्रमe sending message */
अटल अंतरभूत व्योम ppc_msgsnd_sync(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
पूर्ण

/* sync after taking message पूर्णांकerrupt */
अटल अंतरभूत व्योम ppc_msgsync(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_BOOK3S */

बाह्य व्योम करोorbell_exception(काष्ठा pt_regs *regs);

अटल अंतरभूत व्योम ppc_msgsnd(क्रमागत ppc_dbell type, u32 flags, u32 tag)
अणु
	u32 msg = PPC_DBELL_TYPE(type) | (flags & PPC_DBELL_MSG_BRDCAST) |
			(tag & 0x07ffffff);

	_ppc_msgsnd(msg);
पूर्ण

#अगर_घोषित CONFIG_SMP

/*
 * Doorbells must only be used अगर CPU_FTR_DBELL is available.
 * msgsnd is used in HV, and msgsndp is used in !HV.
 *
 * These should be used by platक्रमm code that is aware of restrictions.
 * Other arch code should use ->cause_ipi.
 *
 * करोorbell_global_ipi() sends a dbell to any target CPU.
 * Must be used only by architectures that address msgsnd target
 * by PIR/get_hard_smp_processor_id.
 */
अटल अंतरभूत व्योम करोorbell_global_ipi(पूर्णांक cpu)
अणु
	u32 tag = get_hard_smp_processor_id(cpu);

	kvmppc_set_host_ipi(cpu);
	/* Order previous accesses vs. msgsnd, which is treated as a store */
	ppc_msgsnd_sync();
	ppc_msgsnd(PPC_DBELL_MSGTYPE, 0, tag);
पूर्ण

/*
 * करोorbell_core_ipi() sends a dbell to a target CPU in the same core.
 * Must be used only by architectures that address msgsnd target
 * by TIR/cpu_thपढ़ो_in_core.
 */
अटल अंतरभूत व्योम करोorbell_core_ipi(पूर्णांक cpu)
अणु
	u32 tag = cpu_thपढ़ो_in_core(cpu);

	kvmppc_set_host_ipi(cpu);
	/* Order previous accesses vs. msgsnd, which is treated as a store */
	ppc_msgsnd_sync();
	ppc_msgsnd(PPC_DBELL_MSGTYPE, 0, tag);
पूर्ण

/*
 * Attempt to cause a core करोorbell अगर destination is on the same core.
 * Returns 1 on success, 0 on failure.
 */
अटल अंतरभूत पूर्णांक करोorbell_try_core_ipi(पूर्णांक cpu)
अणु
	पूर्णांक this_cpu = get_cpu();
	पूर्णांक ret = 0;

	अगर (cpumask_test_cpu(cpu, cpu_sibling_mask(this_cpu))) अणु
		करोorbell_core_ipi(cpu);
		ret = 1;
	पूर्ण

	put_cpu();

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#पूर्ण_अगर /* _ASM_POWERPC_DBELL_H */
