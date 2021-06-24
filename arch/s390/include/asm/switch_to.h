<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 1999, 2009
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित __ASM_SWITCH_TO_H
#घोषणा __ASM_SWITCH_TO_H

#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/guarded_storage.h>

बाह्य काष्ठा task_काष्ठा *__चयन_to(व्योम *, व्योम *);
बाह्य व्योम update_cr_regs(काष्ठा task_काष्ठा *task);

अटल अंतरभूत व्योम save_access_regs(अचिन्हित पूर्णांक *acrs)
अणु
	प्रकार काष्ठा अणु पूर्णांक _[NUM_ACRS]; पूर्ण acrstype;

	यंत्र अस्थिर("stam 0,15,%0" : "=Q" (*(acrstype *)acrs));
पूर्ण

अटल अंतरभूत व्योम restore_access_regs(अचिन्हित पूर्णांक *acrs)
अणु
	प्रकार काष्ठा अणु पूर्णांक _[NUM_ACRS]; पूर्ण acrstype;

	यंत्र अस्थिर("lam 0,15,%0" : : "Q" (*(acrstype *)acrs));
पूर्ण

#घोषणा चयन_to(prev, next, last) करो अणु				\
	/* save_fpu_regs() sets the CIF_FPU flag, which enक्रमces	\
	 * a restore of the भग्नing poपूर्णांक / vector रेजिस्टरs as	\
	 * soon as the next task वापसs to user space			\
	 */								\
	save_fpu_regs();						\
	save_access_regs(&prev->thपढ़ो.acrs[0]);			\
	save_ri_cb(prev->thपढ़ो.ri_cb);					\
	save_gs_cb(prev->thपढ़ो.gs_cb);					\
	update_cr_regs(next);						\
	restore_access_regs(&next->thपढ़ो.acrs[0]);			\
	restore_ri_cb(next->thपढ़ो.ri_cb, prev->thपढ़ो.ri_cb);		\
	restore_gs_cb(next->thपढ़ो.gs_cb);				\
	prev = __चयन_to(prev, next);					\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_SWITCH_TO_H */
