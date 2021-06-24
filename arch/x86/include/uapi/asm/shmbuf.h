<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_X86_SHMBUF_H
#घोषणा __ASM_X86_SHMBUF_H

#अगर !defined(__x86_64__) || !defined(__ILP32__)
#समावेश <यंत्र-generic/shmbuf.h>
#अन्यथा
/*
 * The shmid64_ds काष्ठाure क्रम x86 architecture with x32 ABI.
 *
 * On x86-32 and x86-64 we can just use the generic definition, but
 * x32 uses the same binary layout as x86_64, which is dअगरferent
 * from other 32-bit architectures.
 */

काष्ठा shmid64_ds अणु
	काष्ठा ipc64_perm	shm_perm;	/* operation perms */
	माप_प्रकार			shm_segsz;	/* size of segment (bytes) */
	__kernel_दीर्घ_t		shm_aसमय;	/* last attach समय */
	__kernel_दीर्घ_t		shm_dसमय;	/* last detach समय */
	__kernel_दीर्घ_t		shm_स_समय;	/* last change समय */
	__kernel_pid_t		shm_cpid;	/* pid of creator */
	__kernel_pid_t		shm_lpid;	/* pid of last चालक */
	__kernel_uदीर्घ_t	shm_nattch;	/* no. of current attaches */
	__kernel_uदीर्घ_t	__unused4;
	__kernel_uदीर्घ_t	__unused5;
पूर्ण;

काष्ठा shminfo64 अणु
	__kernel_uदीर्घ_t	shmmax;
	__kernel_uदीर्घ_t	shmmin;
	__kernel_uदीर्घ_t	shmmni;
	__kernel_uदीर्घ_t	shmseg;
	__kernel_uदीर्घ_t	shmall;
	__kernel_uदीर्घ_t	__unused1;
	__kernel_uदीर्घ_t	__unused2;
	__kernel_uदीर्घ_t	__unused3;
	__kernel_uदीर्घ_t	__unused4;
पूर्ण;

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_X86_SHMBUF_H */
