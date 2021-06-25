<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_MSGBUF_H
#घोषणा __ASM_GENERIC_MSGBUF_H

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <यंत्र/ipcbuf.h>

/*
 * generic msqid64_ds काष्ठाure.
 *
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * msqid64_ds was originally meant to be architecture specअगरic, but
 * everyone just ended up making identical copies without specअगरic
 * optimizations, so we may just as well all use the same one.
 *
 * 64 bit architectures use a 64-bit दीर्घ समय field here, जबतक
 * 32 bit architectures have a pair of अचिन्हित दीर्घ values.
 * On big-endian प्रणालीs, the lower half is in the wrong place.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 */

काष्ठा msqid64_ds अणु
	काष्ठा ipc64_perm msg_perm;
#अगर __BITS_PER_LONG == 64
	दीर्घ		 msg_sसमय;	/* last msgsnd समय */
	दीर्घ		 msg_rसमय;	/* last msgrcv समय */
	दीर्घ		 msg_स_समय;	/* last change समय */
#अन्यथा
	अचिन्हित दीर्घ	msg_sसमय;	/* last msgsnd समय */
	अचिन्हित दीर्घ	msg_sसमय_high;
	अचिन्हित दीर्घ	msg_rसमय;	/* last msgrcv समय */
	अचिन्हित दीर्घ	msg_rसमय_high;
	अचिन्हित दीर्घ	msg_स_समय;	/* last change समय */
	अचिन्हित दीर्घ	msg_स_समय_high;
#पूर्ण_अगर
	अचिन्हित दीर्घ	msg_cbytes;	/* current number of bytes on queue */
	अचिन्हित दीर्घ	msg_qnum;	/* number of messages in queue */
	अचिन्हित दीर्घ	 msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	अचिन्हित दीर्घ	 __unused4;
	अचिन्हित दीर्घ	 __unused5;
पूर्ण;

#पूर्ण_अगर /* __ASM_GENERIC_MSGBUF_H */
