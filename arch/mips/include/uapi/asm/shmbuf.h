<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_SHMBUF_H
#घोषणा _ASM_SHMBUF_H

/*
 * The shmid64_ds काष्ठाure क्रम the MIPS architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * As MIPS was lacking proper padding after shm_?समय, we use 48 bits
 * of the padding at the end to store a few additional bits of the समय.
 * libc implementations need to take care to convert this पूर्णांकo a proper
 * data काष्ठाure when moving to 64-bit समय_प्रकार.
 */

#अगर_घोषित __mips64
काष्ठा shmid64_ds अणु
	काष्ठा ipc64_perm	shm_perm;	/* operation perms */
	माप_प्रकार			shm_segsz;	/* size of segment (bytes) */
	दीर्घ			shm_aसमय;	/* last attach समय */
	दीर्घ			shm_dसमय;	/* last detach समय */
	दीर्घ			shm_स_समय;	/* last change समय */
	__kernel_pid_t		shm_cpid;	/* pid of creator */
	__kernel_pid_t		shm_lpid;	/* pid of last चालक */
	अचिन्हित दीर्घ		shm_nattch;	/* no. of current attaches */
	अचिन्हित दीर्घ		__unused1;
	अचिन्हित दीर्घ		__unused2;
पूर्ण;
#अन्यथा
काष्ठा shmid64_ds अणु
	काष्ठा ipc64_perm	shm_perm;	/* operation perms */
	माप_प्रकार			shm_segsz;	/* size of segment (bytes) */
	अचिन्हित दीर्घ		shm_aसमय;	/* last attach समय */
	अचिन्हित दीर्घ		shm_dसमय;	/* last detach समय */
	अचिन्हित दीर्घ		shm_स_समय;	/* last change समय */
	__kernel_pid_t		shm_cpid;	/* pid of creator */
	__kernel_pid_t		shm_lpid;	/* pid of last चालक */
	अचिन्हित दीर्घ		shm_nattch;	/* no. of current attaches */
	अचिन्हित लघु		shm_aसमय_high;
	अचिन्हित लघु		shm_dसमय_high;
	अचिन्हित लघु		shm_स_समय_high;
	अचिन्हित लघु		__unused1;
पूर्ण;
#पूर्ण_अगर

काष्ठा shminfo64 अणु
	अचिन्हित दीर्घ	shmmax;
	अचिन्हित दीर्घ	shmmin;
	अचिन्हित दीर्घ	shmmni;
	अचिन्हित दीर्घ	shmseg;
	अचिन्हित दीर्घ	shmall;
	अचिन्हित दीर्घ	__unused1;
	अचिन्हित दीर्घ	__unused2;
	अचिन्हित दीर्घ	__unused3;
	अचिन्हित दीर्घ	__unused4;
पूर्ण;

#पूर्ण_अगर /* _ASM_SHMBUF_H */
