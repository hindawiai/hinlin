<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_CURRENT_H
#घोषणा _ASM_IA64_CURRENT_H

/*
 * Modअगरied 1998-2000
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */

#समावेश <यंत्र/पूर्णांकrinsics.h>

/*
 * In kernel mode, thपढ़ो poपूर्णांकer (r13) is used to poपूर्णांक to the current task
 * काष्ठाure.
 */
#घोषणा current	((काष्ठा task_काष्ठा *) ia64_getreg(_IA64_REG_TP))

#पूर्ण_अगर /* _ASM_IA64_CURRENT_H */
