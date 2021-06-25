<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_POSIX_TYPES_H
#घोषणा _LINUX_POSIX_TYPES_H

#समावेश <linux/मानकघोष.स>

/*
 * This allows क्रम 1024 file descriptors: अगर NR_OPEN is ever grown
 * beyond that you'll have to change this too. But 1024 fd's seem to be
 * enough even क्रम such "real" unices like OSF/1, so hopefully this is
 * one limit that करोesn't have to be changed [again].
 *
 * Note that POSIX wants the FD_CLEAR(fd,fdsetp) defines to be in
 * <sys/समय.स> (and thus <linux/समय.स>) - but this is a more logical
 * place क्रम them. Solved by having dummy defines in <sys/समय.स>.
 */

/*
 * This macro may have been defined in <gnu/types.h>. But we always
 * use the one here.
 */
#अघोषित __FD_SETSIZE
#घोषणा __FD_SETSIZE	1024

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ fds_bits[__FD_SETSIZE / (8 * माप(दीर्घ))];
पूर्ण __kernel_fd_set;

/* Type of a संकेत handler.  */
प्रकार व्योम (*__kernel_sighandler_t)(पूर्णांक);

/* Type of a SYSV IPC key.  */
प्रकार पूर्णांक __kernel_key_t;
प्रकार पूर्णांक __kernel_mqd_t;

#समावेश <यंत्र/posix_types.h>

#पूर्ण_अगर /* _LINUX_POSIX_TYPES_H */
