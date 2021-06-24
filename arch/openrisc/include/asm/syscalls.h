<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_SYSCALLS_H
#घोषणा __ASM_OPENRISC_SYSCALLS_H

यंत्रlinkage दीर्घ sys_or1k_atomic(अचिन्हित दीर्घ type, अचिन्हित दीर्घ *v1,
				अचिन्हित दीर्घ *v2);

#समावेश <यंत्र-generic/syscalls.h>

यंत्रlinkage दीर्घ __sys_clone(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ newsp,
			व्योम __user *parent_tid, व्योम __user *child_tid, पूर्णांक tls);
यंत्रlinkage दीर्घ __sys_विभाजन(व्योम);

#घोषणा sys_clone __sys_clone
#घोषणा sys_विभाजन __sys_विभाजन

#पूर्ण_अगर /* __ASM_OPENRISC_SYSCALLS_H */
