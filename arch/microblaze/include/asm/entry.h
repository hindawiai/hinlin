<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions used by low-level trap handlers
 *
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 */

#अगर_अघोषित _ASM_MICROBLAZE_ENTRY_H
#घोषणा _ASM_MICROBLAZE_ENTRY_H

#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <linux/linkage.h>

/*
 * These are per-cpu variables required in entry.S, among other
 * places
 */

#घोषणा PER_CPU(var) var

# अगरndef __ASSEMBLY__
DECLARE_PER_CPU(अचिन्हित पूर्णांक, KSP); /* Saved kernel stack poपूर्णांकer */
DECLARE_PER_CPU(अचिन्हित पूर्णांक, KM); /* Kernel/user mode */
DECLARE_PER_CPU(अचिन्हित पूर्णांक, ENTRY_SP); /* Saved SP on kernel entry */
DECLARE_PER_CPU(अचिन्हित पूर्णांक, R11_SAVE); /* Temp variable क्रम entry */
DECLARE_PER_CPU(अचिन्हित पूर्णांक, CURRENT_SAVE); /* Saved current poपूर्णांकer */

बाह्य यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, पूर्णांक in_syscall);
# endअगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_MICROBLAZE_ENTRY_H */
