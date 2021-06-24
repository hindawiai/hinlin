<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SEM_H
#घोषणा _UAPI_LINUX_SEM_H

#समावेश <linux/ipc.h>

/* semop flags */
#घोषणा SEM_UNDO        0x1000  /* unकरो the operation on निकास */

/* semctl Command Definitions. */
#घोषणा GETPID  11       /* get sempid */
#घोषणा GETVAL  12       /* get semval */
#घोषणा GETALL  13       /* get all semval's */
#घोषणा GETNCNT 14       /* get semncnt */
#घोषणा GETZCNT 15       /* get semzcnt */
#घोषणा SETVAL  16       /* set semval */
#घोषणा SETALL  17       /* set all semval's */

/* ipcs ctl cmds */
#घोषणा SEM_STAT 18
#घोषणा SEM_INFO 19
#घोषणा SEM_STAT_ANY 20

/* Obsolete, used only क्रम backwards compatibility and libc5 compiles */
काष्ठा semid_ds अणु
	काष्ठा ipc_perm	sem_perm;		/* permissions .. see ipc.h */
	__kernel_old_समय_प्रकार sem_oसमय;		/* last semop समय */
	__kernel_old_समय_प्रकार sem_स_समय;		/* create/last semctl() समय */
	काष्ठा sem	*sem_base;		/* ptr to first semaphore in array */
	काष्ठा sem_queue *sem_pending;		/* pending operations to be processed */
	काष्ठा sem_queue **sem_pending_last;	/* last pending operation */
	काष्ठा sem_unकरो	*unकरो;			/* unकरो requests on this array */
	अचिन्हित लघु	sem_nsems;		/* no. of semaphores in array */
पूर्ण;

/* Include the definition of semid64_ds */
#समावेश <यंत्र/sembuf.h>

/* semop प्रणाली calls takes an array of these. */
काष्ठा sembuf अणु
	अचिन्हित लघु  sem_num;	/* semaphore index in array */
	लघु		sem_op;		/* semaphore operation */
	लघु		sem_flg;	/* operation flags */
पूर्ण;

/* arg क्रम semctl प्रणाली calls. */
जोड़ semun अणु
	पूर्णांक val;			/* value क्रम SETVAL */
	काष्ठा semid_ds __user *buf;	/* buffer क्रम IPC_STAT & IPC_SET */
	अचिन्हित लघु __user *array;	/* array क्रम GETALL & SETALL */
	काष्ठा seminfo __user *__buf;	/* buffer क्रम IPC_INFO */
	व्योम __user *__pad;
पूर्ण;

काष्ठा  seminfo अणु
	पूर्णांक semmap;
	पूर्णांक semmni;
	पूर्णांक semmns;
	पूर्णांक semmnu;
	पूर्णांक semmsl;
	पूर्णांक semopm;
	पूर्णांक semume;
	पूर्णांक semusz;
	पूर्णांक semvmx;
	पूर्णांक semaem;
पूर्ण;

/*
 * SEMMNI, SEMMSL and SEMMNS are शेष values which can be
 * modअगरied by sysctl.
 * The values has been chosen to be larger than necessary क्रम any
 * known configuration.
 *
 * SEMOPM should not be increased beyond 1000, otherwise there is the
 * risk that semop()/semसमयकरोp() fails due to kernel memory fragmentation when
 * allocating the sop array.
 */


#घोषणा SEMMNI  32000           /* <= IPCMNI  max # of semaphore identअगरiers */
#घोषणा SEMMSL  32000           /* <= पूर्णांक_उच्च max num of semaphores per id */
#घोषणा SEMMNS  (SEMMNI*SEMMSL) /* <= पूर्णांक_उच्च max # of semaphores in प्रणाली */
#घोषणा SEMOPM  500	        /* <= 1 000 max num of ops per semop call */
#घोषणा SEMVMX  32767           /* <= 32767 semaphore maximum value */
#घोषणा SEMAEM  SEMVMX          /* adjust on निकास max value */

/* unused */
#घोषणा SEMUME  SEMOPM          /* max num of unकरो entries per process */
#घोषणा SEMMNU  SEMMNS          /* num of unकरो काष्ठाures प्रणाली wide */
#घोषणा SEMMAP  SEMMNS          /* # of entries in semaphore map */
#घोषणा SEMUSZ  20		/* माप काष्ठा sem_unकरो */


#पूर्ण_अगर /* _UAPI_LINUX_SEM_H */
