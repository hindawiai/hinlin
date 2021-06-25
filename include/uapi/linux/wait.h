<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_WAIT_H
#घोषणा _UAPI_LINUX_WAIT_H

#घोषणा WNOHANG		0x00000001
#घोषणा WUNTRACED	0x00000002
#घोषणा WSTOPPED	WUNTRACED
#घोषणा WEXITED		0x00000004
#घोषणा WCONTINUED	0x00000008
#घोषणा WNOWAIT		0x01000000	/* Don't reap, just poll status.  */

#घोषणा __WNOTHREAD	0x20000000	/* Don't रुको on children of other thपढ़ोs in this group */
#घोषणा __WALL		0x40000000	/* Wait on all children, regardless of type */
#घोषणा __WCLONE	0x80000000	/* Wait only on non-SIGCHLD children */

/* First argument to रुकोid: */
#घोषणा P_ALL		0
#घोषणा P_PID		1
#घोषणा P_PGID		2
#घोषणा P_PIDFD		3


#पूर्ण_अगर /* _UAPI_LINUX_WAIT_H */
