<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015  ARM Limited
 * Author: Dave Martin <Dave.Martin@arm.com>
 */

#अगर_अघोषित _ARCH_ARM64_ASM_BUG_H
#घोषणा _ARCH_ARM64_ASM_BUG_H

#समावेश <linux/stringअगरy.h>

#समावेश <यंत्र/यंत्र-bug.h>

#घोषणा __BUG_FLAGS(flags)				\
	यंत्र अस्थिर (__stringअगरy(ASM_BUG_FLAGS(flags)));

#घोषणा BUG() करो अणु					\
	__BUG_FLAGS(0);					\
	unreachable();					\
पूर्ण जबतक (0)

#घोषणा __WARN_FLAGS(flags) __BUG_FLAGS(BUGFLAG_WARNING|(flags))

#घोषणा HAVE_ARCH_BUG

#समावेश <यंत्र-generic/bug.h>

#पूर्ण_अगर /* ! _ARCH_ARM64_ASM_BUG_H */
