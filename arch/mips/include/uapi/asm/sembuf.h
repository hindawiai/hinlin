<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_SEMBUF_H
#घोषणा _ASM_SEMBUF_H

#समावेश <यंत्र/ipcbuf.h>

/*
 * The semid64_ds काष्ठाure क्रम the MIPS architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम 2 miscellaneous 64-bit values on mips64,
 * but used क्रम the upper 32 bit of the समय values on mips32.
 */

#अगर_घोषित __mips64
काष्ठा semid64_ds अणु
	काष्ठा ipc64_perm sem_perm;		/* permissions .. see ipc.h */
	दीर्घ		 sem_oसमय;		/* last semop समय */
	दीर्घ		 sem_स_समय;		/* last change समय */
	अचिन्हित दीर्घ	sem_nsems;		/* no. of semaphores in array */
	अचिन्हित दीर्घ	__unused1;
	अचिन्हित दीर्घ	__unused2;
पूर्ण;
#अन्यथा
काष्ठा semid64_ds अणु
	काष्ठा ipc64_perm sem_perm;		/* permissions .. see ipc.h */
	अचिन्हित दीर्घ   sem_oसमय;		/* last semop समय */
	अचिन्हित दीर्घ   sem_स_समय;		/* last change समय */
	अचिन्हित दीर्घ	sem_nsems;		/* no. of semaphores in array */
	अचिन्हित दीर्घ	sem_oसमय_high;
	अचिन्हित दीर्घ	sem_स_समय_high;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SEMBUF_H */
