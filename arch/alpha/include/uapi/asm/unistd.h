<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ALPHA_UNISTD_H
#घोषणा _UAPI_ALPHA_UNISTD_H

/* These are traditionally the names linux-alpha uses क्रम
 * the two otherwise generic प्रणाली calls */
#घोषणा __NR_umount	__NR_umount2
#घोषणा __NR_osf_shmat	__NR_shmat

/* These वापस an extra value but can be used as aliases */
#घोषणा __NR_getpid	__NR_getxpid
#घोषणा __NR_getuid	__NR_getxuid
#घोषणा __NR_getgid	__NR_getxgid

#समावेश <यंत्र/unistd_32.h>

#पूर्ण_अगर /* _UAPI_ALPHA_UNISTD_H */
