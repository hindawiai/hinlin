<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_REBOOT_H
#घोषणा __ASM_SH_REBOOT_H

#समावेश <linux/kdebug.h>

काष्ठा pt_regs;

काष्ठा machine_ops अणु
	व्योम (*restart)(अक्षर *cmd);
	व्योम (*halt)(व्योम);
	व्योम (*घातer_off)(व्योम);
	व्योम (*shutकरोwn)(व्योम);
	व्योम (*crash_shutकरोwn)(काष्ठा pt_regs *);
पूर्ण;

बाह्य काष्ठा machine_ops machine_ops;

/* arch/sh/kernel/machine_kexec.c */
व्योम native_machine_crash_shutकरोwn(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASM_SH_REBOOT_H */
