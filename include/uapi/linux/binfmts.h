<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_BINFMTS_H
#घोषणा _UAPI_LINUX_BINFMTS_H

#समावेश <linux/capability.h>

काष्ठा pt_regs;

/*
 * These are the maximum length and maximum number of strings passed to the
 * execve() प्रणाली call.  MAX_ARG_STRLEN is essentially अक्रमom but serves to
 * prevent the kernel from being unduly impacted by misaddressed poपूर्णांकers.
 * MAX_ARG_STRINGS is chosen to fit in a चिन्हित 32-bit पूर्णांकeger.
 */
#घोषणा MAX_ARG_STRLEN (PAGE_SIZE * 32)
#घोषणा MAX_ARG_STRINGS 0x7FFFFFFF

/* माप(linux_binprm->buf) */
#घोषणा BINPRM_BUF_SIZE 256

/* preserve argv0 क्रम the पूर्णांकerpreter  */
#घोषणा AT_FLAGS_PRESERVE_ARGV0_BIT 0
#घोषणा AT_FLAGS_PRESERVE_ARGV0 (1 << AT_FLAGS_PRESERVE_ARGV0_BIT)

#पूर्ण_अगर /* _UAPI_LINUX_BINFMTS_H */
