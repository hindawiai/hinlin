<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __S390_IPCBUF_H__
#घोषणा __S390_IPCBUF_H__

#समावेश <linux/posix_types.h>

/*
 * The user_ipc_perm काष्ठाure क्रम S/390 architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 32-bit mode_t and seq
 * - 2 miscellaneous 32-bit values
 */

काष्ठा ipc64_perm
अणु
	__kernel_key_t		key;
	__kernel_uid32_t	uid;
	__kernel_gid32_t	gid;
	__kernel_uid32_t	cuid;
	__kernel_gid32_t	cgid;
	__kernel_mode_t		mode;
	अचिन्हित लघु		__pad1;
	अचिन्हित लघु		seq;
#अगर_अघोषित __s390x__
	अचिन्हित लघु		__pad2;
#पूर्ण_अगर /* ! __s390x__ */
	अचिन्हित दीर्घ		__unused1;
	अचिन्हित दीर्घ		__unused2;
पूर्ण;

#पूर्ण_अगर /* __S390_IPCBUF_H__ */
