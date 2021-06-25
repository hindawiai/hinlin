<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __PARISC_IPCBUF_H__
#घोषणा __PARISC_IPCBUF_H__

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <linux/posix_types.h>

/*
 * The ipc64_perm काष्ठाure क्रम PA-RISC is almost identical to
 * kern_ipc_perm as we have always had 32-bit UIDs and GIDs in the kernel.
 * 'seq' has been changed from long to int so that it's the same size
 * on 64-bit kernels as on 32-bit ones.
 */

काष्ठा ipc64_perm
अणु
	__kernel_key_t		key;
	__kernel_uid_t		uid;
	__kernel_gid_t		gid;
	__kernel_uid_t		cuid;
	__kernel_gid_t		cgid;
#अगर __BITS_PER_LONG != 64
	अचिन्हित लघु पूर्णांक	__pad1;
#पूर्ण_अगर
	__kernel_mode_t		mode;
	अचिन्हित लघु पूर्णांक	__pad2;
	अचिन्हित लघु पूर्णांक	seq;
	अचिन्हित पूर्णांक		__pad3;
	अचिन्हित दीर्घ दीर्घ पूर्णांक __unused1;
	अचिन्हित दीर्घ दीर्घ पूर्णांक __unused2;
पूर्ण;

#पूर्ण_अगर /* __PARISC_IPCBUF_H__ */
