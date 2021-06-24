<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_X64_MSGBUF_H
#घोषणा __ASM_X64_MSGBUF_H

#अगर !defined(__x86_64__) || !defined(__ILP32__)
#समावेश <यंत्र-generic/msgbuf.h>
#अन्यथा

#समावेश <यंत्र/ipcbuf.h>

/*
 * The msqid64_ds काष्ठाure क्रम x86 architecture with x32 ABI.
 *
 * On x86-32 and x86-64 we can just use the generic definition, but
 * x32 uses the same binary layout as x86_64, which is dअगरferent
 * from other 32-bit architectures.
 */

काष्ठा msqid64_ds अणु
	काष्ठा ipc64_perm msg_perm;
	__kernel_दीर्घ_t msg_sसमय;	/* last msgsnd समय */
	__kernel_दीर्घ_t msg_rसमय;	/* last msgrcv समय */
	__kernel_दीर्घ_t msg_स_समय;	/* last change समय */
	__kernel_uदीर्घ_t msg_cbytes;	/* current number of bytes on queue */
	__kernel_uदीर्घ_t msg_qnum;	/* number of messages in queue */
	__kernel_uदीर्घ_t msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	__kernel_uदीर्घ_t __unused4;
	__kernel_uदीर्घ_t __unused5;
पूर्ण;

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_MSGBUF_H */
