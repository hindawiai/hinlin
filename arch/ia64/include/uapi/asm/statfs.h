<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_STATFS_H
#घोषणा _ASM_IA64_STATFS_H

/*
 * Based on <यंत्र-i386/statfs.h>.
 *
 * Modअगरied 1998, 1999, 2003
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */

/*
 * We need compat_statfs64 to be packed, because the i386 ABI won't
 * add padding at the end to bring it to a multiple of 8 bytes, but
 * the IA64 ABI will.
 */
#घोषणा ARCH_PACK_COMPAT_STATFS64 __attribute__((packed,aligned(4)))

#समावेश <यंत्र-generic/statfs.h>

#पूर्ण_अगर /* _ASM_IA64_STATFS_H */
