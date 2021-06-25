<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __SPARC_IPCBUF_H
#घोषणा __SPARC_IPCBUF_H

#समावेश <linux/posix_types.h>

/*
 * The ipc64_perm काष्ठाure क्रम sparc/sparc64 architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 32-bit seq
 * - on sparc क्रम 32 bit mode (it is 32 bit on sparc64)
 * - 2 miscellaneous 64-bit values
 */

काष्ठा ipc64_perm
अणु
	__kernel_key_t		key;
	__kernel_uid32_t	uid;
	__kernel_gid32_t	gid;
	__kernel_uid32_t	cuid;
	__kernel_gid32_t	cgid;
#अगर_अघोषित __arch64__
	अचिन्हित लघु		__pad0;
#पूर्ण_अगर
	__kernel_mode_t		mode;
	अचिन्हित लघु		__pad1;
	अचिन्हित लघु		seq;
	अचिन्हित दीर्घ दीर्घ	__unused1;
	अचिन्हित दीर्घ दीर्घ	__unused2;
पूर्ण;

#पूर्ण_अगर /* __SPARC_IPCBUF_H */
