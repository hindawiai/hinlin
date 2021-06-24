<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _PARISC_MSGBUF_H
#घोषणा _PARISC_MSGBUF_H

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <यंत्र/ipcbuf.h>

/* 
 * The msqid64_ds काष्ठाure क्रम parisc architecture, copied from sparc.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
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
	अचिन्हित दीर्घ	msg_sसमय_high;
	अचिन्हित दीर्घ	msg_sसमय;	/* last msgsnd समय */
	अचिन्हित दीर्घ	msg_rसमय_high;
	अचिन्हित दीर्घ	msg_rसमय;	/* last msgrcv समय */
	अचिन्हित दीर्घ	msg_स_समय_high;
	अचिन्हित दीर्घ	msg_स_समय;	/* last change समय */
#पूर्ण_अगर
	अचिन्हित दीर्घ	msg_cbytes;	/* current number of bytes on queue */
	अचिन्हित दीर्घ	msg_qnum;	/* number of messages in queue */
	अचिन्हित दीर्घ	msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t	msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t	msg_lrpid;	/* last receive pid */
	अचिन्हित दीर्घ	__unused1;
	अचिन्हित दीर्घ	__unused2;
पूर्ण;

#पूर्ण_अगर /* _PARISC_MSGBUF_H */
