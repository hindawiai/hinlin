<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_IPCBUF_H
#घोषणा __ASM_GENERIC_IPCBUF_H

#समावेश <linux/posix_types.h>

/*
 * The generic ipc64_perm काष्ठाure:
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * ipc64_perm was originally meant to be architecture specअगरic, but
 * everyone just ended up making identical copies without specअगरic
 * optimizations, so we may just as well all use the same one.
 *
 * Pad space is left क्रम:
 * - 32-bit mode_t on architectures that only had 16 bit
 * - 32-bit seq
 * - 2 miscellaneous 32-bit values
 */

काष्ठा ipc64_perm अणु
	__kernel_key_t		key;
	__kernel_uid32_t	uid;
	__kernel_gid32_t	gid;
	__kernel_uid32_t	cuid;
	__kernel_gid32_t	cgid;
	__kernel_mode_t		mode;
				/* pad अगर mode_t is u16: */
	अचिन्हित अक्षर		__pad1[4 - माप(__kernel_mode_t)];
	अचिन्हित लघु		seq;
	अचिन्हित लघु		__pad2;
	__kernel_uदीर्घ_t	__unused1;
	__kernel_uदीर्घ_t	__unused2;
पूर्ण;

#पूर्ण_अगर /* __ASM_GENERIC_IPCBUF_H */
