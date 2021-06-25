<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* AF_VSOCK sock_diag(7) पूर्णांकerface क्रम querying खोलो sockets */

#अगर_अघोषित _UAPI__VM_SOCKETS_DIAG_H__
#घोषणा _UAPI__VM_SOCKETS_DIAG_H__

#समावेश <linux/types.h>

/* Request */
काष्ठा vsock_diag_req अणु
	__u8	sdiag_family;	/* must be AF_VSOCK */
	__u8	sdiag_protocol;	/* must be 0 */
	__u16	pad;		/* must be 0 */
	__u32	vdiag_states;	/* query biपंचांगap (e.g. 1 << TCP_LISTEN) */
	__u32	vdiag_ino;	/* must be 0 (reserved) */
	__u32	vdiag_show;	/* must be 0 (reserved) */
	__u32	vdiag_cookie[2];
पूर्ण;

/* Response */
काष्ठा vsock_diag_msg अणु
	__u8	vdiag_family;	/* AF_VSOCK */
	__u8	vdiag_type;	/* SOCK_STREAM or SOCK_DGRAM */
	__u8	vdiag_state;	/* sk_state (e.g. TCP_LISTEN) */
	__u8	vdiag_shutकरोwn; /* local RCV_SHUTDOWN | SEND_SHUTDOWN */
	__u32   vdiag_src_cid;
	__u32   vdiag_src_port;
	__u32   vdiag_dst_cid;
	__u32   vdiag_dst_port;
	__u32	vdiag_ino;
	__u32	vdiag_cookie[2];
पूर्ण;

#पूर्ण_अगर /* _UAPI__VM_SOCKETS_DIAG_H__ */
