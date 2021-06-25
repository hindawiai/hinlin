<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/msgbuf.h
 *
 * The msqid64_ds काष्ठाure क्रम the Xtensa architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Pad space is left क्रम:
 * - 2 miscellaneous 32-bit values
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 */

#अगर_अघोषित _XTENSA_MSGBUF_H
#घोषणा _XTENSA_MSGBUF_H

#समावेश <यंत्र/ipcbuf.h>

काष्ठा msqid64_ds अणु
	काष्ठा ipc64_perm msg_perm;
#अगर_घोषित __XTENSA_EB__
	अचिन्हित दीर्घ  msg_sसमय_high;
	अचिन्हित दीर्घ  msg_sसमय;	/* last msgsnd समय */
	अचिन्हित दीर्घ  msg_rसमय_high;
	अचिन्हित दीर्घ  msg_rसमय;	/* last msgrcv समय */
	अचिन्हित दीर्घ  msg_स_समय_high;
	अचिन्हित दीर्घ  msg_स_समय;	/* last change समय */
#या_अगर defined(__XTENSA_EL__)
	अचिन्हित दीर्घ  msg_sसमय;	/* last msgsnd समय */
	अचिन्हित दीर्घ  msg_sसमय_high;
	अचिन्हित दीर्घ  msg_rसमय;	/* last msgrcv समय */
	अचिन्हित दीर्घ  msg_rसमय_high;
	अचिन्हित दीर्घ  msg_स_समय;	/* last change समय */
	अचिन्हित दीर्घ  msg_स_समय_high;
#अन्यथा
# error processor byte order undefined!
#पूर्ण_अगर
	अचिन्हित दीर्घ  msg_cbytes;	/* current number of bytes on queue */
	अचिन्हित दीर्घ  msg_qnum;	/* number of messages in queue */
	अचिन्हित दीर्घ  msg_qbytes;	/* max number of bytes on queue */
	__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__kernel_pid_t msg_lrpid;	/* last receive pid */
	अचिन्हित दीर्घ  __unused4;
	अचिन्हित दीर्घ  __unused5;
पूर्ण;

#पूर्ण_अगर	/* _XTENSA_MSGBUF_H */
