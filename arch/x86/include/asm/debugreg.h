<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_DEBUGREG_H
#घोषणा _ASM_X86_DEBUGREG_H


#समावेश <linux/bug.h>
#समावेश <uapi/यंत्र/debugreg.h>

DECLARE_PER_CPU(अचिन्हित दीर्घ, cpu_dr7);

#अगर_अघोषित CONFIG_PARAVIRT_XXL
/*
 * These special macros can be used to get or set a debugging रेजिस्टर
 */
#घोषणा get_debugreg(var, रेजिस्टर)				\
	(var) = native_get_debugreg(रेजिस्टर)
#घोषणा set_debugreg(value, रेजिस्टर)				\
	native_set_debugreg(रेजिस्टर, value)
#पूर्ण_अगर

अटल __always_अंतरभूत अचिन्हित दीर्घ native_get_debugreg(पूर्णांक regno)
अणु
	अचिन्हित दीर्घ val = 0;	/* Damn you, gcc! */

	चयन (regno) अणु
	हाल 0:
		यंत्र("mov %%db0, %0" :"=r" (val));
		अवरोध;
	हाल 1:
		यंत्र("mov %%db1, %0" :"=r" (val));
		अवरोध;
	हाल 2:
		यंत्र("mov %%db2, %0" :"=r" (val));
		अवरोध;
	हाल 3:
		यंत्र("mov %%db3, %0" :"=r" (val));
		अवरोध;
	हाल 6:
		यंत्र("mov %%db6, %0" :"=r" (val));
		अवरोध;
	हाल 7:
		यंत्र("mov %%db7, %0" :"=r" (val));
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	वापस val;
पूर्ण

अटल __always_अंतरभूत व्योम native_set_debugreg(पूर्णांक regno, अचिन्हित दीर्घ value)
अणु
	चयन (regno) अणु
	हाल 0:
		यंत्र("mov %0, %%db0"	::"r" (value));
		अवरोध;
	हाल 1:
		यंत्र("mov %0, %%db1"	::"r" (value));
		अवरोध;
	हाल 2:
		यंत्र("mov %0, %%db2"	::"r" (value));
		अवरोध;
	हाल 3:
		यंत्र("mov %0, %%db3"	::"r" (value));
		अवरोध;
	हाल 6:
		यंत्र("mov %0, %%db6"	::"r" (value));
		अवरोध;
	हाल 7:
		यंत्र("mov %0, %%db7"	::"r" (value));
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hw_अवरोधpoपूर्णांक_disable(व्योम)
अणु
	/* Zero the control रेजिस्टर क्रम HW Breakpoपूर्णांक */
	set_debugreg(0UL, 7);

	/* Zero-out the inभागidual HW अवरोधpoपूर्णांक address रेजिस्टरs */
	set_debugreg(0UL, 0);
	set_debugreg(0UL, 1);
	set_debugreg(0UL, 2);
	set_debugreg(0UL, 3);
पूर्ण

अटल __always_अंतरभूत bool hw_अवरोधpoपूर्णांक_active(व्योम)
अणु
	वापस __this_cpu_पढ़ो(cpu_dr7) & DR_GLOBAL_ENABLE_MASK;
पूर्ण

बाह्य व्योम hw_अवरोधpoपूर्णांक_restore(व्योम);

अटल __always_अंतरभूत अचिन्हित दीर्घ local_db_save(व्योम)
अणु
	अचिन्हित दीर्घ dr7;

	अगर (अटल_cpu_has(X86_FEATURE_HYPERVISOR) && !hw_अवरोधpoपूर्णांक_active())
		वापस 0;

	get_debugreg(dr7, 7);
	dr7 &= ~0x400; /* architecturally set bit */
	अगर (dr7)
		set_debugreg(0, 7);
	/*
	 * Ensure the compiler करोesn't lower the above statements पूर्णांकo
	 * the critical section; disabling अवरोधpoपूर्णांकs late would not
	 * be good.
	 */
	barrier();

	वापस dr7;
पूर्ण

अटल __always_अंतरभूत व्योम local_db_restore(अचिन्हित दीर्घ dr7)
अणु
	/*
	 * Ensure the compiler करोesn't उठाओ this statement पूर्णांकo
	 * the critical section; enabling अवरोधpoपूर्णांकs early would
	 * not be good.
	 */
	barrier();
	अगर (dr7)
		set_debugreg(dr7, 7);
पूर्ण

#अगर_घोषित CONFIG_CPU_SUP_AMD
बाह्य व्योम set_dr_addr_mask(अचिन्हित दीर्घ mask, पूर्णांक dr);
#अन्यथा
अटल अंतरभूत व्योम set_dr_addr_mask(अचिन्हित दीर्घ mask, पूर्णांक dr) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_DEBUGREG_H */
