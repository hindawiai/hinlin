<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* winकरोws.c: Routines to deal with रेजिस्टर winकरोw management
 *            at the C-code level.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>

#समावेश "kernel.h"

/* Do save's until all user रेजिस्टर winकरोws are out of the cpu. */
व्योम flush_user_winकरोws(व्योम)
अणु
	रेजिस्टर पूर्णांक ctr यंत्र("g5");

	ctr = 0;
	__यंत्र__ __अस्थिर__(
		"\n1:\n\t"
		"ld	[%%g6 + %2], %%g4\n\t"
		"orcc	%%g0, %%g4, %%g0\n\t"
		"add	%0, 1, %0\n\t"
		"bne	1b\n\t"
		" save	%%sp, -64, %%sp\n"
		"2:\n\t"
		"subcc	%0, 1, %0\n\t"
		"bne	2b\n\t"
		" restore %%g0, %%g0, %%g0\n"
	: "=&r" (ctr)
	: "0" (ctr),
	  "i" ((स्थिर अचिन्हित दीर्घ)TI_UWINMASK)
	: "g4", "cc");
पूर्ण

अटल अंतरभूत व्योम shअगरt_winकरोw_buffer(पूर्णांक first_win, पूर्णांक last_win, काष्ठा thपढ़ो_info *tp)
अणु
	पूर्णांक i;

	क्रम(i = first_win; i < last_win; i++) अणु
		tp->rwbuf_stkptrs[i] = tp->rwbuf_stkptrs[i+1];
		स_नकल(&tp->reg_winकरोw[i], &tp->reg_winकरोw[i+1], माप(काष्ठा reg_winकरोw32));
	पूर्ण
पूर्ण

/* Place as many of the user's current रेजिस्टर winकरोws 
 * on the stack that we can.  Even अगर the %sp is unaligned
 * we still copy the winकरोw there, the only हाल that we करोn't
 * succeed is अगर the %sp poपूर्णांकs to a bum mapping altogether.
 * setup_frame() and करो_sigवापस() use this beक्रमe shअगरting
 * the user stack around.  Future inकाष्ठाion and hardware
 * bug workaround routines will need this functionality as
 * well.
 */
व्योम synchronize_user_stack(व्योम)
अणु
	काष्ठा thपढ़ो_info *tp = current_thपढ़ो_info();
	पूर्णांक winकरोw;

	flush_user_winकरोws();
	अगर(!tp->w_saved)
		वापस;

	/* Ok, there is some dirty work to करो. */
	क्रम(winकरोw = tp->w_saved - 1; winकरोw >= 0; winकरोw--) अणु
		अचिन्हित दीर्घ sp = tp->rwbuf_stkptrs[winकरोw];

		/* Ok, let it rip. */
		अगर (copy_to_user((अक्षर __user *) sp, &tp->reg_winकरोw[winकरोw],
				 माप(काष्ठा reg_winकरोw32)))
			जारी;

		shअगरt_winकरोw_buffer(winकरोw, tp->w_saved - 1, tp);
		tp->w_saved--;
	पूर्ण
पूर्ण

#अगर 0
/* An optimization. */
अटल अंतरभूत व्योम copy_aligned_winकरोw(व्योम *dest, स्थिर व्योम *src)
अणु
	__यंत्र__ __अस्थिर__("ldd [%1], %%g2\n\t"
			     "ldd [%1 + 0x8], %%g4\n\t"
			     "std %%g2, [%0]\n\t"
			     "std %%g4, [%0 + 0x8]\n\t"
			     "ldd [%1 + 0x10], %%g2\n\t"
			     "ldd [%1 + 0x18], %%g4\n\t"
			     "std %%g2, [%0 + 0x10]\n\t"
			     "std %%g4, [%0 + 0x18]\n\t"
			     "ldd [%1 + 0x20], %%g2\n\t"
			     "ldd [%1 + 0x28], %%g4\n\t"
			     "std %%g2, [%0 + 0x20]\n\t"
			     "std %%g4, [%0 + 0x28]\n\t"
			     "ldd [%1 + 0x30], %%g2\n\t"
			     "ldd [%1 + 0x38], %%g4\n\t"
			     "std %%g2, [%0 + 0x30]\n\t"
			     "std %%g4, [%0 + 0x38]\n\t" : :
			     "r" (dest), "r" (src) :
			     "g2", "g3", "g4", "g5");
पूर्ण
#पूर्ण_अगर

/* Try to push the winकरोws in a thपढ़ोs winकरोw buffer to the
 * user stack.  Unaligned %sp's are not allowed here.
 */

व्योम try_to_clear_winकरोw_buffer(काष्ठा pt_regs *regs, पूर्णांक who)
अणु
	काष्ठा thपढ़ो_info *tp = current_thपढ़ो_info();
	पूर्णांक winकरोw;

	flush_user_winकरोws();
	क्रम(winकरोw = 0; winकरोw < tp->w_saved; winकरोw++) अणु
		अचिन्हित दीर्घ sp = tp->rwbuf_stkptrs[winकरोw];

		अगर ((sp & 7) ||
		    copy_to_user((अक्षर __user *) sp, &tp->reg_winकरोw[winकरोw],
				 माप(काष्ठा reg_winकरोw32)))
			करो_निकास(संक_अवैध);
	पूर्ण
	tp->w_saved = 0;
पूर्ण
