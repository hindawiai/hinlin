<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_SEMBUF_H
#घोषणा _ASM_X86_SEMBUF_H

#समावेश <यंत्र/ipcbuf.h>

/*
 * The semid64_ds काष्ठाure क्रम x86 architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 *
 * x86_64 and x32 incorrectly added padding here, so the काष्ठाures
 * are still incompatible with the padding on x86.
 */
काष्ठा semid64_ds अणु
	काष्ठा ipc64_perm sem_perm;	/* permissions .. see ipc.h */
#अगर_घोषित __i386__
	अचिन्हित दीर्घ	sem_oसमय;	/* last semop समय */
	अचिन्हित दीर्घ	sem_oसमय_high;
	अचिन्हित दीर्घ	sem_स_समय;	/* last change समय */
	अचिन्हित दीर्घ	sem_स_समय_high;
#अन्यथा
	__kernel_दीर्घ_t sem_oसमय;	/* last semop समय */
	__kernel_uदीर्घ_t __unused1;
	__kernel_दीर्घ_t sem_स_समय;	/* last change समय */
	__kernel_uदीर्घ_t __unused2;
#पूर्ण_अगर
	__kernel_uदीर्घ_t sem_nsems;	/* no. of semaphores in array */
	__kernel_uदीर्घ_t __unused3;
	__kernel_uदीर्घ_t __unused4;
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_SEMBUF_H */
