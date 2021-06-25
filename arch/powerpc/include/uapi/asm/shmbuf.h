<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_SHMBUF_H
#घोषणा _ASM_POWERPC_SHMBUF_H

/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

/*
 * The shmid64_ds काष्ठाure क्रम PPC architecture.
 *
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 */

काष्ठा shmid64_ds अणु
	काष्ठा ipc64_perm	shm_perm;	/* operation perms */
#अगर_घोषित __घातerpc64__
	दीर्घ		shm_aसमय;	/* last attach समय */
	दीर्घ		shm_dसमय;	/* last detach समय */
	दीर्घ		shm_स_समय;	/* last change समय */
#अन्यथा
	अचिन्हित दीर्घ		shm_aसमय_high;
	अचिन्हित दीर्घ		shm_aसमय;	/* last attach समय */
	अचिन्हित दीर्घ		shm_dसमय_high;
	अचिन्हित दीर्घ		shm_dसमय;	/* last detach समय */
	अचिन्हित दीर्घ		shm_स_समय_high;
	अचिन्हित दीर्घ		shm_स_समय;	/* last change समय */
	अचिन्हित दीर्घ		__unused4;
#पूर्ण_अगर
	माप_प्रकार			shm_segsz;	/* size of segment (bytes) */
	__kernel_pid_t		shm_cpid;	/* pid of creator */
	__kernel_pid_t		shm_lpid;	/* pid of last चालक */
	अचिन्हित दीर्घ		shm_nattch;	/* no. of current attaches */
	अचिन्हित दीर्घ		__unused5;
	अचिन्हित दीर्घ		__unused6;
पूर्ण;

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

#पूर्ण_अगर	/* _ASM_POWERPC_SHMBUF_H */
