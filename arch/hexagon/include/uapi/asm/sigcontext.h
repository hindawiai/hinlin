<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
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

#अगर_अघोषित _ASM_SIGCONTEXT_H
#घोषणा _ASM_SIGCONTEXT_H

#समावेश <यंत्र/user.h>

/*
 * Signal context काष्ठाure - contains all info to करो with the state
 * beक्रमe the संकेत handler was invoked.  Note: only add new entries
 * to the end of the काष्ठाure.
 */
काष्ठा sigcontext अणु
	काष्ठा user_regs_काष्ठा sc_regs;
पूर्ण __aligned(8);

#पूर्ण_अगर
