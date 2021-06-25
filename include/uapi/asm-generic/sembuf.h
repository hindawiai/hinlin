<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_SEMBUF_H
#घोषणा __ASM_GENERIC_SEMBUF_H

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <यंत्र/ipcbuf.h>

/*
 * The semid64_ds काष्ठाure क्रम most architectures (though it came from x86_32
 * originally). Note extra padding because this काष्ठाure is passed back and
 * क्रमth between kernel and user space.
 *
 * semid64_ds was originally meant to be architecture specअगरic, but
 * everyone just ended up making identical copies without specअगरic
 * optimizations, so we may just as well all use the same one.
 *
 * 64 bit architectures use a 64-bit दीर्घ समय field here, जबतक
 * 32 bit architectures have a pair of अचिन्हित दीर्घ values.
 *
 * On big-endian प्रणालीs, the padding is in the wrong place क्रम
 * historic reasons, so user space has to reस्थिरruct a समय_प्रकार
 * value using
 *
 * user_semid_ds.sem_oसमय = kernel_semid64_ds.sem_oसमय +
 *		((दीर्घ दीर्घ)kernel_semid64_ds.sem_oसमय_high << 32)
 *
 * Pad space is left क्रम 2 miscellaneous 32-bit values
 */
काष्ठा semid64_ds अणु
	काष्ठा ipc64_perm sem_perm;	/* permissions .. see ipc.h */
#अगर __BITS_PER_LONG == 64
	दीर्घ		sem_oसमय;	/* last semop समय */
	दीर्घ		sem_स_समय;	/* last change समय */
#अन्यथा
	अचिन्हित दीर्घ	sem_oसमय;	/* last semop समय */
	अचिन्हित दीर्घ	sem_oसमय_high;
	अचिन्हित दीर्घ	sem_स_समय;	/* last change समय */
	अचिन्हित दीर्घ	sem_स_समय_high;
#पूर्ण_अगर
	अचिन्हित दीर्घ	sem_nsems;	/* no. of semaphores in array */
	अचिन्हित दीर्घ	__unused3;
	अचिन्हित दीर्घ	__unused4;
पूर्ण;

#पूर्ण_अगर /* __ASM_GENERIC_SEMBUF_H */
