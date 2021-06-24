<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/प्रणाली_misc.h
 *
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_SYSTEM_MISC_H
#घोषणा __ASM_SYSTEM_MISC_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/ratelimit.h>
#समावेश <linux/reboot.h>

काष्ठा pt_regs;

व्योम die(स्थिर अक्षर *msg, काष्ठा pt_regs *regs, पूर्णांक err);

काष्ठा siginfo;
व्योम arm64_notअगरy_die(स्थिर अक्षर *str, काष्ठा pt_regs *regs,
		      पूर्णांक signo, पूर्णांक sicode, अचिन्हित दीर्घ far,
		      पूर्णांक err);

व्योम hook_debug_fault_code(पूर्णांक nr, पूर्णांक (*fn)(अचिन्हित दीर्घ, अचिन्हित पूर्णांक,
					     काष्ठा pt_regs *),
			   पूर्णांक sig, पूर्णांक code, स्थिर अक्षर *name);

काष्ठा mm_काष्ठा;
बाह्य व्योम __show_regs(काष्ठा pt_regs *);

बाह्य व्योम (*arm_pm_restart)(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *cmd);

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* __ASM_SYSTEM_MISC_H */
