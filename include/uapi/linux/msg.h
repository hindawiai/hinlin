<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_MSG_H
#घोषणा _UAPI_LINUX_MSG_H

#समावेश <linux/ipc.h>

/* ipcs ctl commands */
#घोषणा MSG_STAT 11
#घोषणा MSG_INFO 12
#घोषणा MSG_STAT_ANY 13

/* msgrcv options */
#घोषणा MSG_NOERROR     010000  /* no error अगर message is too big */
#घोषणा MSG_EXCEPT      020000  /* recv any msg except of specअगरied type.*/
#घोषणा MSG_COPY        040000  /* copy (not हटाओ) all queue messages */

/* Obsolete, used only क्रम backwards compatibility and libc5 compiles */
काष्ठा msqid_ds अणु
	काष्ठा ipc_perm msg_perm;
	काष्ठा msg *msg_first;		/* first message on queue,unused  */
	काष्ठा msg *msg_last;		/* last message in queue,unused */
	__kernel_old_समय_प्रकार msg_sसमय;	/* last msgsnd समय */
	__kernel_old_समय_प्रकार msg_rसमय;	/* last msgrcv समय */
	__kernel_old_समय_प्रकार msg_स_समय;	/* last change समय */
	अचिन्हित दीर्घ  msg_lcbytes;	/* Reuse junk fields क्रम 32 bit */
	अचिन्हित दीर्घ  msg_lqbytes;	/* ditto */
	अचिन्हित लघु msg_cbytes;	/* current number of bytes on queue */
	अचिन्हित लघु msg_qnum;	/* number of messages in queue */
	अचिन्हित लघु msg_qbytes;	/* max number of bytes on queue */
	__kernel_ipc_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_ipc_pid_t msg_lrpid;	/* last receive pid */
पूर्ण;

/* Include the definition of msqid64_ds */
#समावेश <यंत्र/msgbuf.h>

/* message buffer क्रम msgsnd and msgrcv calls */
काष्ठा msgbuf अणु
	__kernel_दीर्घ_t mtype;          /* type of message */
	अक्षर mtext[1];                  /* message text */
पूर्ण;

/* buffer क्रम msgctl calls IPC_INFO, MSG_INFO */
काष्ठा msginfo अणु
	पूर्णांक msgpool;
	पूर्णांक msgmap; 
	पूर्णांक msgmax; 
	पूर्णांक msgmnb; 
	पूर्णांक msgmni; 
	पूर्णांक msgssz; 
	पूर्णांक msgtql; 
	अचिन्हित लघु  msgseg; 
पूर्ण;

/*
 * MSGMNI, MSGMAX and MSGMNB are शेष values which can be
 * modअगरied by sysctl.
 *
 * MSGMNI is the upper limit क्रम the number of messages queues per
 * namespace.
 * It has been chosen to be as large possible without facilitating
 * scenarios where userspace causes overflows when adjusting the limits via
 * operations of the क्रमm retrieve current limit; add X; update limit".
 *
 * MSGMNB is the शेष size of a new message queue. Non-root tasks can
 * decrease the size with msgctl(IPC_SET), root tasks
 * (actually: CAP_SYS_RESOURCE) can both increase and decrease the queue
 * size. The optimal value is application dependent.
 * 16384 is used because it was always used (since 0.99.10)
 *
 * MAXMAX is the maximum size of an inभागidual message, it's a global
 * (per-namespace) limit that applies क्रम all message queues.
 * It's set to 1/2 of MSGMNB, to ensure that at least two messages fit पूर्णांकo
 * the queue. This is also an arbitrary choice (since 2.6.0).
 */

#घोषणा MSGMNI 32000   /* <= IPCMNI */     /* max # of msg queue identअगरiers */
#घोषणा MSGMAX  8192   /* <= पूर्णांक_उच्च */   /* max size of message (bytes) */
#घोषणा MSGMNB 16384   /* <= पूर्णांक_उच्च */   /* शेष max size of a message queue */

/* unused */
#घोषणा MSGPOOL (MSGMNI * MSGMNB / 1024) /* size in kbytes of message pool */
#घोषणा MSGTQL  MSGMNB            /* number of प्रणाली message headers */
#घोषणा MSGMAP  MSGMNB            /* number of entries in message map */
#घोषणा MSGSSZ  16                /* message segment size */
#घोषणा __MSGSEG ((MSGPOOL * 1024) / MSGSSZ) /* max no. of segments */
#घोषणा MSGSEG (__MSGSEG <= 0xffff ? __MSGSEG : 0xffff)


#पूर्ण_अगर /* _UAPI_LINUX_MSG_H */
