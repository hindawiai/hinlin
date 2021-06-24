<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Ptrace definitions क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA
 * 02110-1301, USA.
 */

#अगर_अघोषित _ASM_PTRACE_H
#घोषणा _ASM_PTRACE_H

#समावेश <यंत्र/रेजिस्टरs.h>

#घोषणा inकाष्ठाion_poपूर्णांकer(regs) pt_elr(regs)
#घोषणा user_stack_poपूर्णांकer(regs) ((regs)->r29)

#घोषणा profile_pc(regs) inकाष्ठाion_poपूर्णांकer(regs)

/* kprobe-based event tracer support */
बाह्य पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name);
बाह्य स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset);

#घोषणा current_pt_regs() \
	((काष्ठा pt_regs *) \
	 ((अचिन्हित दीर्घ)current_thपढ़ो_info() + THREAD_SIZE) - 1)

#अगर CONFIG_HEXAGON_ARCH_VERSION >= 4
#घोषणा arch_has_single_step()	(1)
#पूर्ण_अगर


#पूर्ण_अगर
