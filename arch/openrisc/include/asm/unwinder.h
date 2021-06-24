<शैली गुरु>
/*
 * OpenRISC unwinder.h
 *
 * Architecture API क्रम unwinding stacks.
 *
 * Copyright (C) 2017 Stafक्रमd Horne <shorne@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __ASM_OPENRISC_UNWINDER_H
#घोषणा __ASM_OPENRISC_UNWINDER_H

व्योम unwind_stack(व्योम *data, अचिन्हित दीर्घ *stack,
		  व्योम (*trace)(व्योम *data, अचिन्हित दीर्घ addr,
				पूर्णांक reliable));

#पूर्ण_अगर /* __ASM_OPENRISC_UNWINDER_H */
