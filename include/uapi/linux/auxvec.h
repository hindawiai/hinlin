<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_AUXVEC_H
#घोषणा _UAPI_LINUX_AUXVEC_H

#समावेश <यंत्र/auxvec.h>

/* Symbolic values क्रम the entries in the auxiliary table
   put on the initial stack */
#घोषणा AT_शून्य   0	/* end of vector */
#घोषणा AT_IGNORE 1	/* entry should be ignored */
#घोषणा AT_EXECFD 2	/* file descriptor of program */
#घोषणा AT_PHDR   3	/* program headers क्रम program */
#घोषणा AT_PHENT  4	/* size of program header entry */
#घोषणा AT_PHNUM  5	/* number of program headers */
#घोषणा AT_PAGESZ 6	/* प्रणाली page size */
#घोषणा AT_BASE   7	/* base address of पूर्णांकerpreter */
#घोषणा AT_FLAGS  8	/* flags */
#घोषणा AT_ENTRY  9	/* entry poपूर्णांक of program */
#घोषणा AT_NOTELF 10	/* program is not ELF */
#घोषणा AT_UID    11	/* real uid */
#घोषणा AT_EUID   12	/* effective uid */
#घोषणा AT_GID    13	/* real gid */
#घोषणा AT_EGID   14	/* effective gid */
#घोषणा AT_PLATFORM 15  /* string identअगरying CPU क्रम optimizations */
#घोषणा AT_HWCAP  16    /* arch dependent hपूर्णांकs at CPU capabilities */
#घोषणा AT_CLKTCK 17	/* frequency at which बार() increments */
/* AT_* values 18 through 22 are reserved */
#घोषणा AT_SECURE 23   /* secure mode boolean */
#घोषणा AT_BASE_PLATFORM 24	/* string identअगरying real platक्रमm, may
				 * dअगरfer from AT_PLATFORM. */
#घोषणा AT_RANDOM 25	/* address of 16 अक्रमom bytes */
#घोषणा AT_HWCAP2 26	/* extension of AT_HWCAP */

#घोषणा AT_EXECFN  31	/* filename of program */


#पूर्ण_अगर /* _UAPI_LINUX_AUXVEC_H */
