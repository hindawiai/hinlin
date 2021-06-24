<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/sembuf.h
 *
 * The semid64_ds काष्ठाure क्रम Xtensa architecture.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 *
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 *
 */

#अगर_अघोषित _XTENSA_SEMBUF_H
#घोषणा _XTENSA_SEMBUF_H

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/ipcbuf.h>

काष्ठा semid64_ds अणु
	काष्ठा ipc64_perm sem_perm;		/* permissions .. see ipc.h */
#अगर_घोषित __XTENSA_EL__
	अचिन्हित दीर्घ	sem_oसमय;		/* last semop समय */
	अचिन्हित दीर्घ	sem_oसमय_high;
	अचिन्हित दीर्घ	sem_स_समय;		/* last change समय */
	अचिन्हित दीर्घ	sem_स_समय_high;
#अन्यथा
	अचिन्हित दीर्घ	sem_oसमय_high;
	अचिन्हित दीर्घ	sem_oसमय;		/* last semop समय */
	अचिन्हित दीर्घ	sem_स_समय_high;
	अचिन्हित दीर्घ	sem_स_समय;		/* last change समय */
#पूर्ण_अगर
	अचिन्हित दीर्घ	sem_nsems;		/* no. of semaphores in array */
	अचिन्हित दीर्घ	__unused3;
	अचिन्हित दीर्घ	__unused4;
पूर्ण;

#पूर्ण_अगर /* __ASM_XTENSA_SEMBUF_H */
