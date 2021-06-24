<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_SWITCH_TO_H
#घोषणा __ASM_CSKY_SWITCH_TO_H

#समावेश <linux/thपढ़ो_info.h>
#अगर_घोषित CONFIG_CPU_HAS_FPU
#समावेश <abi/fpu.h>
अटल अंतरभूत व्योम __चयन_to_fpu(काष्ठा task_काष्ठा *prev,
				   काष्ठा task_काष्ठा *next)
अणु
	save_to_user_fp(&prev->thपढ़ो.user_fp);
	restore_from_user_fp(&next->thपढ़ो.user_fp);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम __चयन_to_fpu(काष्ठा task_काष्ठा *prev,
				   काष्ठा task_काष्ठा *next)
अणुपूर्ण
#पूर्ण_अगर

/*
 * Context चयनing is now perक्रमmed out-of-line in चयन_to.S
 */
बाह्य काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *,
				       काष्ठा task_काष्ठा *);

#घोषणा चयन_to(prev, next, last)					\
	करो अणु								\
		काष्ठा task_काष्ठा *__prev = (prev);			\
		काष्ठा task_काष्ठा *__next = (next);			\
		__चयन_to_fpu(__prev, __next);			\
		((last) = __चयन_to((prev), (next)));			\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* __ASM_CSKY_SWITCH_TO_H */
