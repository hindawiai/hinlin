<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _PARISC_SEMBUF_H
#घोषणा _PARISC_SEMBUF_H

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <यंत्र/ipcbuf.h>

/* 
 * The semid64_ds काष्ठाure क्रम parisc architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 */

काष्ठा semid64_ds अणु
	काष्ठा ipc64_perm sem_perm;		/* permissions .. see ipc.h */
#अगर __BITS_PER_LONG == 64
	दीर्घ		sem_oसमय;		/* last semop समय */
	दीर्घ		sem_स_समय;		/* last change समय */
#अन्यथा
	अचिन्हित दीर्घ	sem_oसमय_high;
	अचिन्हित दीर्घ	sem_oसमय;		/* last semop समय */
	अचिन्हित दीर्घ	sem_स_समय_high;
	अचिन्हित दीर्घ	sem_स_समय;		/* last change समय */
#पूर्ण_अगर
	अचिन्हित दीर्घ	sem_nsems;		/* no. of semaphores in array */
	अचिन्हित दीर्घ	__unused1;
	अचिन्हित दीर्घ	__unused2;
पूर्ण;

#पूर्ण_अगर /* _PARISC_SEMBUF_H */
