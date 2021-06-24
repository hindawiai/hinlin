<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_CURRENT_H
#घोषणा _ASM_POWERPC_CURRENT_H
#अगर_घोषित __KERNEL__

/*
 */

काष्ठा task_काष्ठा;

#अगर_घोषित __घातerpc64__
#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/paca.h>

अटल अंतरभूत काष्ठा task_काष्ठा *get_current(व्योम)
अणु
	काष्ठा task_काष्ठा *task;

	/* get_current can be cached by the compiler, so no अस्थिर */
	यंत्र ("ld %0,%1(13)"
	: "=r" (task)
	: "i" (दुरत्व(काष्ठा paca_काष्ठा, __current)));

	वापस task;
पूर्ण
#घोषणा current	get_current()

#अन्यथा

/*
 * We keep `current' in r2 क्रम speed.
 */
रेजिस्टर काष्ठा task_काष्ठा *current यंत्र ("r2");

#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_CURRENT_H */
