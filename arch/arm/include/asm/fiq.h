<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  arch/arm/include/यंत्र/fiq.h
 *
 * Support क्रम FIQ on ARM architectures.
 * Written by Philip Blundell <philb@gnu.org>, 1998
 * Re-written by Russell King
 *
 * NOTE: The FIQ mode रेजिस्टरs are not magically preserved across
 * suspend/resume.
 *
 * Drivers which require these रेजिस्टरs to be preserved across घातer
 * management operations must implement appropriate suspend/resume handlers to
 * save and restore them.
 */

#अगर_अघोषित __ASM_FIQ_H
#घोषणा __ASM_FIQ_H

#समावेश <यंत्र/ptrace.h>

काष्ठा fiq_handler अणु
	काष्ठा fiq_handler *next;
	/* Name
	 */
	स्थिर अक्षर *name;
	/* Called to ask driver to relinquish/
	 * reacquire FIQ
	 * वापस zero to accept, or -<त्रुटि_सं>
	 */
	पूर्णांक (*fiq_op)(व्योम *, पूर्णांक relinquish);
	/* data क्रम the relinquish/reacquire functions
	 */
	व्योम *dev_id;
पूर्ण;

बाह्य पूर्णांक claim_fiq(काष्ठा fiq_handler *f);
बाह्य व्योम release_fiq(काष्ठा fiq_handler *f);
बाह्य व्योम set_fiq_handler(व्योम *start, अचिन्हित पूर्णांक length);
बाह्य व्योम enable_fiq(पूर्णांक fiq);
बाह्य व्योम disable_fiq(पूर्णांक fiq);

/* helpers defined in fiqयंत्र.S: */
बाह्य व्योम __set_fiq_regs(अचिन्हित दीर्घ स्थिर *regs);
बाह्य व्योम __get_fiq_regs(अचिन्हित दीर्घ *regs);

अटल अंतरभूत व्योम set_fiq_regs(काष्ठा pt_regs स्थिर *regs)
अणु
	__set_fiq_regs(&regs->ARM_r8);
पूर्ण

अटल अंतरभूत व्योम get_fiq_regs(काष्ठा pt_regs *regs)
अणु
	__get_fiq_regs(&regs->ARM_r8);
पूर्ण

#पूर्ण_अगर
