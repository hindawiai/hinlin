<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2015, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_TM_TM_H
#घोषणा _SELFTESTS_POWERPC_TM_TM_H

#समावेश <stdbool.h>
#समावेश <यंत्र/पंचांग.h>

#समावेश "utils.h"

अटल अंतरभूत bool have_hपंचांग(व्योम)
अणु
#अगर_घोषित PPC_FEATURE2_HTM
	वापस have_hwcap2(PPC_FEATURE2_HTM);
#अन्यथा
	म_लिखो("PPC_FEATURE2_HTM not defined, can't check AT_HWCAP2\n");
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत bool have_hपंचांग_nosc(व्योम)
अणु
#अगर_घोषित PPC_FEATURE2_HTM_NOSC
	वापस have_hwcap2(PPC_FEATURE2_HTM_NOSC);
#अन्यथा
	म_लिखो("PPC_FEATURE2_HTM_NOSC not defined, can't check AT_HWCAP2\n");
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत दीर्घ failure_code(व्योम)
अणु
	वापस __builtin_get_texasru() >> 24;
पूर्ण

अटल अंतरभूत bool failure_is_persistent(व्योम)
अणु
	वापस (failure_code() & TM_CAUSE_PERSISTENT) == TM_CAUSE_PERSISTENT;
पूर्ण

अटल अंतरभूत bool failure_is_syscall(व्योम)
अणु
	वापस (failure_code() & TM_CAUSE_SYSCALL) == TM_CAUSE_SYSCALL;
पूर्ण

अटल अंतरभूत bool failure_is_unavailable(व्योम)
अणु
	वापस (failure_code() & TM_CAUSE_FAC_UNAV) == TM_CAUSE_FAC_UNAV;
पूर्ण

अटल अंतरभूत bool failure_is_reschedule(व्योम)
अणु
	अगर ((failure_code() & TM_CAUSE_RESCHED) == TM_CAUSE_RESCHED ||
	    (failure_code() & TM_CAUSE_KVM_RESCHED) == TM_CAUSE_KVM_RESCHED ||
	    (failure_code() & TM_CAUSE_KVM_FAC_UNAV) == TM_CAUSE_KVM_FAC_UNAV)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool failure_is_nesting(व्योम)
अणु
	वापस (__builtin_get_texasru() & 0x400000);
पूर्ण

अटल अंतरभूत पूर्णांक tcheck(व्योम)
अणु
	दीर्घ cr;
	यंत्र अस्थिर ("tcheck 0" : "=r"(cr) : : "cr0");
	वापस (cr >> 28) & 4;
पूर्ण

अटल अंतरभूत bool tcheck_करोomed(व्योम)
अणु
	वापस tcheck() & 8;
पूर्ण

अटल अंतरभूत bool tcheck_active(व्योम)
अणु
	वापस tcheck() & 4;
पूर्ण

अटल अंतरभूत bool tcheck_suspended(व्योम)
अणु
	वापस tcheck() & 2;
पूर्ण

अटल अंतरभूत bool tcheck_transactional(व्योम)
अणु
	वापस tcheck() & 6;
पूर्ण

#पूर्ण_अगर /* _SELFTESTS_POWERPC_TM_TM_H */
