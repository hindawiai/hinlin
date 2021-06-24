<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* AF_TIPC sock_diag पूर्णांकerface क्रम querying खोलो sockets */

#अगर_अघोषित _UAPI__TIPC_SOCKETS_DIAG_H__
#घोषणा _UAPI__TIPC_SOCKETS_DIAG_H__

#समावेश <linux/types.h>
#समावेश <linux/sock_diag.h>

/* Request */
काष्ठा tipc_sock_diag_req अणु
	__u8	sdiag_family;	/* must be AF_TIPC */
	__u8	sdiag_protocol;	/* must be 0 */
	__u16	pad;		/* must be 0 */
	__u32	tidiag_states;	/* query*/
पूर्ण;
#पूर्ण_अगर /* _UAPI__TIPC_SOCKETS_DIAG_H__ */
