<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_XTENSA_UNISTD_H
#घोषणा _UAPI_XTENSA_UNISTD_H

#समावेश <यंत्र/unistd_32.h>

#घोषणा __ARCH_WANT_SYS_OLDUMOUNT

/*
 * sysxtensa syscall handler
 *
 * पूर्णांक sysxtensa (SYS_XTENSA_ATOMIC_SET,     ptr, val,    unused);
 * पूर्णांक sysxtensa (SYS_XTENSA_ATOMIC_ADD,     ptr, val,    unused);
 * पूर्णांक sysxtensa (SYS_XTENSA_ATOMIC_EXG_ADD, ptr, val,    unused);
 * पूर्णांक sysxtensa (SYS_XTENSA_ATOMIC_CMP_SWP, ptr, oldval, newval);
 *        a2            a6                   a3    a4      a5
 */

#घोषणा SYS_XTENSA_RESERVED               0     /* करोn't use this */
#घोषणा SYS_XTENSA_ATOMIC_SET             1     /* set variable */
#घोषणा SYS_XTENSA_ATOMIC_EXG_ADD         2     /* exchange memory and add */
#घोषणा SYS_XTENSA_ATOMIC_ADD             3     /* add to memory */
#घोषणा SYS_XTENSA_ATOMIC_CMP_SWP         4     /* compare and swap */
#घोषणा SYS_XTENSA_COUNT                  5     /* count */

#पूर्ण_अगर /* _UAPI_XTENSA_UNISTD_H */
