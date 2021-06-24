<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_SUSPEND_H
#घोषणा __ASM_ARM_SUSPEND_H

#समावेश <linux/types.h>

काष्ठा sleep_save_sp अणु
	u32 *save_ptr_stash;
	u32 save_ptr_stash_phys;
पूर्ण;

बाह्य व्योम cpu_resume(व्योम);
बाह्य व्योम cpu_resume_no_hyp(व्योम);
बाह्य व्योम cpu_resume_arm(व्योम);
बाह्य पूर्णांक cpu_suspend(अचिन्हित दीर्घ, पूर्णांक (*)(अचिन्हित दीर्घ));

#पूर्ण_अगर
