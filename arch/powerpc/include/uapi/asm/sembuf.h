<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_SEMBUF_H
#घोषणा _ASM_POWERPC_SEMBUF_H

#समावेश <यंत्र/ipcbuf.h>

/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

/*
 * The semid64_ds काष्ठाure क्रम PPC architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32/64-bit values
 */

काष्ठा semid64_ds अणु
	काष्ठा ipc64_perm sem_perm;	/* permissions .. see ipc.h */
#अगर_अघोषित __घातerpc64__
	अचिन्हित दीर्घ	sem_oसमय_high;
	अचिन्हित दीर्घ	sem_oसमय;	/* last semop समय */
	अचिन्हित दीर्घ	sem_स_समय_high;
	अचिन्हित दीर्घ	sem_स_समय;	/* last change समय */
#अन्यथा
	दीर्घ		sem_oसमय;	/* last semop समय */
	दीर्घ		sem_स_समय;	/* last change समय */
#पूर्ण_अगर
	अचिन्हित दीर्घ	sem_nsems;	/* no. of semaphores in array */
	अचिन्हित दीर्घ	__unused3;
	अचिन्हित दीर्घ	__unused4;
पूर्ण;

#पूर्ण_अगर	/* _ASM_POWERPC_SEMBUF_H */
