<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_SHMBUF_H
#घोषणा __ASM_GENERIC_SHMBUF_H

#समावेश <यंत्र/bitsperदीर्घ.h>

/*
 * The shmid64_ds काष्ठाure क्रम x86 architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * shmid64_ds was originally meant to be architecture specअगरic, but
 * everyone just ended up making identical copies without specअगरic
 * optimizations, so we may just as well all use the same one.
 *
 * 64 bit architectures use a 64-bit दीर्घ समय field here, जबतक
 * 32 bit architectures have a pair of अचिन्हित दीर्घ values.
 * On big-endian प्रणालीs, the lower half is in the wrong place.
 *
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 */

काष्ठा shmid64_ds अणु
	काष्ठा ipc64_perm	shm_perm;	/* operation perms */
	माप_प्रकार			shm_segsz;	/* size of segment (bytes) */
#अगर __BITS_PER_LONG == 64
	दीर्घ			shm_aसमय;	/* last attach समय */
	दीर्घ			shm_dसमय;	/* last detach समय */
	दीर्घ			shm_स_समय;	/* last change समय */
#अन्यथा
	अचिन्हित दीर्घ		shm_aसमय;	/* last attach समय */
	अचिन्हित दीर्घ		shm_aसमय_high;
	अचिन्हित दीर्घ		shm_dसमय;	/* last detach समय */
	अचिन्हित दीर्घ		shm_dसमय_high;
	अचिन्हित दीर्घ		shm_स_समय;	/* last change समय */
	अचिन्हित दीर्घ		shm_स_समय_high;
#पूर्ण_अगर
	__kernel_pid_t		shm_cpid;	/* pid of creator */
	__kernel_pid_t		shm_lpid;	/* pid of last चालक */
	अचिन्हित दीर्घ		shm_nattch;	/* no. of current attaches */
	अचिन्हित दीर्घ		__unused4;
	अचिन्हित दीर्घ		__unused5;
पूर्ण;

काष्ठा shminfo64 अणु
	अचिन्हित दीर्घ		shmmax;
	अचिन्हित दीर्घ		shmmin;
	अचिन्हित दीर्घ		shmmni;
	अचिन्हित दीर्घ		shmseg;
	अचिन्हित दीर्घ		shmall;
	अचिन्हित दीर्घ		__unused1;
	अचिन्हित दीर्घ		__unused2;
	अचिन्हित दीर्घ		__unused3;
	अचिन्हित दीर्घ		__unused4;
पूर्ण;

#पूर्ण_अगर /* __ASM_GENERIC_SHMBUF_H */
