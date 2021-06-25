<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_IPC_H
#घोषणा _UAPI_LINUX_IPC_H

#समावेश <linux/types.h>

#घोषणा IPC_PRIVATE ((__kernel_key_t) 0)  

/* Obsolete, used only क्रम backwards compatibility and libc5 compiles */
काष्ठा ipc_perm
अणु
	__kernel_key_t	key;
	__kernel_uid_t	uid;
	__kernel_gid_t	gid;
	__kernel_uid_t	cuid;
	__kernel_gid_t	cgid;
	__kernel_mode_t	mode; 
	अचिन्हित लघु	seq;
पूर्ण;

/* Include the definition of ipc64_perm */
#समावेश <यंत्र/ipcbuf.h>

/* resource get request flags */
#घोषणा IPC_CREAT  00001000   /* create अगर key is nonexistent */
#घोषणा IPC_EXCL   00002000   /* fail अगर key exists */
#घोषणा IPC_NOWAIT 00004000   /* वापस error on रुको */

/* these fields are used by the DIPC package so the kernel as standard
   should aव्योम using them अगर possible */
   
#घोषणा IPC_DIPC 00010000  /* make it distributed */
#घोषणा IPC_OWN  00020000  /* this machine is the DIPC owner */

/* 
 * Control commands used with semctl, msgctl and shmctl 
 * see also specअगरic commands in sem.h, msg.h and shm.h
 */
#घोषणा IPC_RMID 0     /* हटाओ resource */
#घोषणा IPC_SET  1     /* set ipc_perm options */
#घोषणा IPC_STAT 2     /* get ipc_perm options */
#घोषणा IPC_INFO 3     /* see ipcs */

/*
 * Version flags क्रम semctl, msgctl, and shmctl commands
 * These are passed as bitflags or-ed with the actual command
 */
#घोषणा IPC_OLD 0	/* Old version (no 32-bit UID support on many
			   architectures) */
#घोषणा IPC_64  0x0100  /* New version (support 32-bit UIDs, bigger
			   message sizes, etc. */

/*
 * These are used to wrap प्रणाली calls.
 *
 * See architecture code क्रम ugly details..
 */
काष्ठा ipc_kludge अणु
	काष्ठा msgbuf __user *msgp;
	दीर्घ msgtyp;
पूर्ण;

#घोषणा SEMOP		 1
#घोषणा SEMGET		 2
#घोषणा SEMCTL		 3
#घोषणा SEMTIMEDOP	 4
#घोषणा MSGSND		11
#घोषणा MSGRCV		12
#घोषणा MSGGET		13
#घोषणा MSGCTL		14
#घोषणा SHMAT		21
#घोषणा SHMDT		22
#घोषणा SHMGET		23
#घोषणा SHMCTL		24

/* Used by the DIPC package, try and aव्योम reusing it */
#घोषणा DIPC            25

#घोषणा IPCCALL(version,op)	((version)<<16 | (op))


#पूर्ण_अगर /* _UAPI_LINUX_IPC_H */
