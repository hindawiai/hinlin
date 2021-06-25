<शैली गुरु>
/* 
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#अगर_अघोषित __SYS_SIGCONTEXT_X86_H
#घोषणा __SYS_SIGCONTEXT_X86_H

बाह्य व्योम get_regs_from_mc(काष्ठा uml_pt_regs *, mcontext_t *);

#अगर_घोषित __i386__

#घोषणा GET_FAULTINFO_FROM_MC(fi, mc) \
	अणु \
		(fi).cr2 = (mc)->cr2; \
		(fi).error_code = (mc)->gregs[REG_ERR]; \
		(fi).trap_no = (mc)->gregs[REG_TRAPNO]; \
	पूर्ण

#अन्यथा

#घोषणा GET_FAULTINFO_FROM_MC(fi, mc) \
	अणु \
		(fi).cr2 = (mc)->gregs[REG_CR2]; \
		(fi).error_code = (mc)->gregs[REG_ERR]; \
		(fi).trap_no = (mc)->gregs[REG_TRAPNO]; \
	पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
