<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Process/processor support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2012, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_PROCESSOR_H
#घोषणा _ASM_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/mem-layout.h>
#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <यंत्र/hexagon_vm.h>

/*  task_काष्ठा, defined अन्यथाwhere, is the "process descriptor" */
काष्ठा task_काष्ठा;

बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs *, अचिन्हित दीर्घ, अचिन्हित दीर्घ);

/*
 * thपढ़ो_काष्ठा is supposed to be क्रम context चयन data.
 * Specअगरically, to hold the state necessary to perक्रमm चयन_to...
 */
काष्ठा thपढ़ो_काष्ठा अणु
	व्योम *चयन_sp;
पूर्ण;

/*
 * initializes thपढ़ो_काष्ठा
 * The only thing we have in there is चयन_sp
 * which करोesn't really need to be initialized.
 */

#घोषणा INIT_THREAD अणु \
पूर्ण

#घोषणा cpu_relax() __vmyield()

/*
 * Decides where the kernel will search क्रम a मुक्त chunk of vm space during
 * mmaps.
 * See also arch_get_unmapped_area.
 * Doesn't affect अगर you have MAX_FIXED in the page flags set though...
 *
 * Apparently the convention is that ld.so will ask क्रम "unmapped" निजी
 * memory to be allocated SOMEWHERE, but it also asks क्रम memory explicitly
 * via MAP_FIXED at the lower * addresses starting at VA=0x0.
 *
 * If the two requests collide, you get authentic segfaulting action, so
 * you have to kick the "unmapped" base requests higher up.
 */
#घोषणा TASK_UNMAPPED_BASE	(PAGE_ALIGN(TASK_SIZE/3))


#घोषणा task_pt_regs(task) \
	((काष्ठा pt_regs *)(task_stack_page(task) + THREAD_SIZE) - 1)

#घोषणा KSTK_EIP(tsk) (pt_elr(task_pt_regs(tsk)))
#घोषणा KSTK_ESP(tsk) (pt_psp(task_pt_regs(tsk)))

/*  Free all resources held by a thपढ़ो; defined in process.c  */
बाह्य व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task);

/* Get रुको channel क्रम task P.  */
बाह्य अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

/*  The following stuff is pretty HEXAGON specअगरic.  */

/*  This is really just here क्रम __चयन_to.
    Offsets are pulled via यंत्र-offsets.c  */

/*
 * No real reason why VM and native चयन stacks should be dअगरferent.
 * Ultimately this should merge.  Note that Rev C. ABI called out only
 * R24-27 as callee saved GPRs needing explicit attention (R29-31 being
 * dealt with स्वतःmagically by allocframe), but the current ABI has
 * more, R16-R27.  By saving more, the worst हाल is that we waste some
 * cycles अगर building with the old compilers.
 */

काष्ठा hexagon_चयन_stack अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r16;
			अचिन्हित दीर्घ r17;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ	r1716;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r18;
			अचिन्हित दीर्घ r19;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ	r1918;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r20;
			अचिन्हित दीर्घ r21;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ	r2120;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r22;
			अचिन्हित दीर्घ r23;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ	r2322;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r24;
			अचिन्हित दीर्घ r25;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ	r2524;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ r26;
			अचिन्हित दीर्घ r27;
		पूर्ण;
		अचिन्हित दीर्घ दीर्घ	r2726;
	पूर्ण;

	अचिन्हित दीर्घ		fp;
	अचिन्हित दीर्घ		lr;
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर
