<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ELFCORE_COMPAT_H
#घोषणा _LINUX_ELFCORE_COMPAT_H

#समावेश <linux/elf.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/compat.h>

/*
 * Make sure these layouts match the linux/elfcore.h native definitions.
 */

काष्ठा compat_elf_siginfo
अणु
	compat_पूर्णांक_t			si_signo;
	compat_पूर्णांक_t			si_code;
	compat_पूर्णांक_t			si_त्रुटि_सं;
पूर्ण;

काष्ठा compat_elf_prstatus_common
अणु
	काष्ठा compat_elf_siginfo	pr_info;
	लघु				pr_cursig;
	compat_uदीर्घ_t			pr_sigpend;
	compat_uदीर्घ_t			pr_sighold;
	compat_pid_t			pr_pid;
	compat_pid_t			pr_ppid;
	compat_pid_t			pr_pgrp;
	compat_pid_t			pr_sid;
	काष्ठा old_समयval32		pr_uसमय;
	काष्ठा old_समयval32		pr_sसमय;
	काष्ठा old_समयval32		pr_cuसमय;
	काष्ठा old_समयval32		pr_csसमय;
पूर्ण;

काष्ठा compat_elf_prpsinfo
अणु
	अक्षर				pr_state;
	अक्षर				pr_sname;
	अक्षर				pr_zomb;
	अक्षर				pr_nice;
	compat_uदीर्घ_t			pr_flag;
	__compat_uid_t			pr_uid;
	__compat_gid_t			pr_gid;
	compat_pid_t			pr_pid, pr_ppid, pr_pgrp, pr_sid;
	अक्षर				pr_fname[16];
	अक्षर				pr_psargs[ELF_PRARGSZ];
पूर्ण;

#अगर_घोषित CONFIG_ARCH_HAS_ELFCORE_COMPAT
#समावेश <यंत्र/elfcore-compat.h>
#पूर्ण_अगर

काष्ठा compat_elf_prstatus
अणु
	काष्ठा compat_elf_prstatus_common	common;
	compat_elf_gregset_t		pr_reg;
	compat_पूर्णांक_t			pr_fpvalid;
पूर्ण;

#पूर्ण_अगर /* _LINUX_ELFCORE_COMPAT_H */
