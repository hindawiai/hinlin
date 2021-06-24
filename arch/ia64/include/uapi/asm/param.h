<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Fundamental kernel parameters.
 *
 * Based on <यंत्र-i386/param.h>.
 *
 * Modअगरied 1998, 1999, 2002-2003
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */
#अगर_अघोषित _UAPI_ASM_IA64_PARAM_H
#घोषणा _UAPI_ASM_IA64_PARAM_H


#घोषणा EXEC_PAGESIZE	65536

#अगर_अघोषित NOGROUP
# define NOGROUP	(-1)
#पूर्ण_अगर

#घोषणा MAXHOSTNAMELEN	64	/* max length of hostname */

#अगर_अघोषित __KERNEL__
   /*
    * Technically, this is wrong, but some old apps still refer to it.  The proper way to
    * get the HZ value is via sysconf(_SC_घड़ी_टिक).
    */
# define HZ 1024
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_ASM_IA64_PARAM_H */
