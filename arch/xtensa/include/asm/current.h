<शैली गुरु>
/*
 * include/यंत्र-xtensa/current.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CURRENT_H
#घोषणा _XTENSA_CURRENT_H

#समावेश <यंत्र/thपढ़ो_info.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/thपढ़ो_info.h>

काष्ठा task_काष्ठा;

अटल अंतरभूत काष्ठा task_काष्ठा *get_current(व्योम)
अणु
	वापस current_thपढ़ो_info()->task;
पूर्ण

#घोषणा current get_current()

#अन्यथा

#घोषणा GET_CURRENT(reg,sp)		\
	GET_THREAD_INFO(reg,sp);	\
	l32i reg, reg, TI_TASK		\

#पूर्ण_अगर


#पूर्ण_अगर /* XTENSA_CURRENT_H */
