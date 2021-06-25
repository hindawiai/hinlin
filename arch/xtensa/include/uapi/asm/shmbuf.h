<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/shmbuf.h
 *
 * The shmid64_ds काष्ठाure क्रम Xtensa architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space, but the padding is on the wrong
 * side क्रम big-endian xtensa, क्रम historic reasons.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_SHMBUF_H
#घोषणा _XTENSA_SHMBUF_H

काष्ठा shmid64_ds अणु
	काष्ठा ipc64_perm	shm_perm;	/* operation perms */
	माप_प्रकार			shm_segsz;	/* size of segment (bytes) */
	अचिन्हित दीर्घ		shm_aसमय;	/* last attach समय */
	अचिन्हित दीर्घ		shm_aसमय_high;
	अचिन्हित दीर्घ		shm_dसमय;	/* last detach समय */
	अचिन्हित दीर्घ		shm_dसमय_high;
	अचिन्हित दीर्घ		shm_स_समय;	/* last change समय */
	अचिन्हित दीर्घ		shm_स_समय_high;
	__kernel_pid_t		shm_cpid;	/* pid of creator */
	__kernel_pid_t		shm_lpid;	/* pid of last चालक */
	अचिन्हित दीर्घ		shm_nattch;	/* no. of current attaches */
	अचिन्हित दीर्घ		__unused4;
	अचिन्हित दीर्घ		__unused5;
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

#पूर्ण_अगर	/* _XTENSA_SHMBUF_H */
