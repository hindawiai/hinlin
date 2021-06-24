<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_SMC_DIAG_H_
#घोषणा _UAPI_SMC_DIAG_H_

#समावेश <linux/types.h>
#समावेश <linux/inet_diag.h>
#समावेश <rdma/ib_user_verbs.h>

/* Request काष्ठाure */
काष्ठा smc_diag_req अणु
	__u8	diag_family;
	__u8	pad[2];
	__u8	diag_ext;		/* Query extended inक्रमmation */
	काष्ठा inet_diag_sockid	id;
पूर्ण;

/* Base info काष्ठाure. It contains socket identity (addrs/ports/cookie) based
 * on the पूर्णांकernal clcsock, and more SMC-related socket data
 */
काष्ठा smc_diag_msg अणु
	__u8		diag_family;
	__u8		diag_state;
	जोड़ अणु
		__u8	diag_mode;
		__u8	diag_fallback; /* the old name of the field */
	पूर्ण;
	__u8		diag_shutकरोwn;
	काष्ठा inet_diag_sockid id;

	__u32		diag_uid;
	__aligned_u64	diag_inode;
पूर्ण;

/* Mode of a connection */
क्रमागत अणु
	SMC_DIAG_MODE_SMCR,
	SMC_DIAG_MODE_FALLBACK_TCP,
	SMC_DIAG_MODE_SMCD,
पूर्ण;

/* Extensions */

क्रमागत अणु
	SMC_DIAG_NONE,
	SMC_DIAG_CONNINFO,
	SMC_DIAG_LGRINFO,
	SMC_DIAG_SHUTDOWN,
	SMC_DIAG_DMBINFO,
	SMC_DIAG_FALLBACK,
	__SMC_DIAG_MAX,
पूर्ण;

#घोषणा SMC_DIAG_MAX (__SMC_DIAG_MAX - 1)

/* SMC_DIAG_CONNINFO */

काष्ठा smc_diag_cursor अणु
	__u16	reserved;
	__u16	wrap;
	__u32	count;
पूर्ण;

काष्ठा smc_diag_conninfo अणु
	__u32			token;		/* unique connection id */
	__u32			sndbuf_size;	/* size of send buffer */
	__u32			rmbe_size;	/* size of RMB element */
	__u32			peer_rmbe_size;	/* size of peer RMB element */
	/* local RMB element cursors */
	काष्ठा smc_diag_cursor	rx_prod;	/* received producer cursor */
	काष्ठा smc_diag_cursor	rx_cons;	/* received consumer cursor */
	/* peer RMB element cursors */
	काष्ठा smc_diag_cursor	tx_prod;	/* sent producer cursor */
	काष्ठा smc_diag_cursor	tx_cons;	/* sent consumer cursor */
	__u8			rx_prod_flags;	/* received producer flags */
	__u8			rx_conn_state_flags; /* recvd connection flags*/
	__u8			tx_prod_flags;	/* sent producer flags */
	__u8			tx_conn_state_flags; /* sent connection flags*/
	/* send buffer cursors */
	काष्ठा smc_diag_cursor	tx_prep;	/* prepared to be sent cursor */
	काष्ठा smc_diag_cursor	tx_sent;	/* sent cursor */
	काष्ठा smc_diag_cursor	tx_fin;		/* confirmed sent cursor */
पूर्ण;

/* SMC_DIAG_LINKINFO */

काष्ठा smc_diag_linkinfo अणु
	__u8 link_id;			/* link identअगरier */
	__u8 ibname[IB_DEVICE_NAME_MAX]; /* name of the RDMA device */
	__u8 ibport;			/* RDMA device port number */
	__u8 gid[40];			/* local GID */
	__u8 peer_gid[40];		/* peer GID */
पूर्ण;

काष्ठा smc_diag_lgrinfo अणु
	काष्ठा smc_diag_linkinfo	lnk[1];
	__u8				role;
पूर्ण;

काष्ठा smc_diag_fallback अणु
	__u32 reason;
	__u32 peer_diagnosis;
पूर्ण;

काष्ठा smcd_diag_dmbinfo अणु		/* SMC-D Socket पूर्णांकernals */
	__u32		linkid;		/* Link identअगरier */
	__aligned_u64	peer_gid;	/* Peer GID */
	__aligned_u64	my_gid;		/* My GID */
	__aligned_u64	token;		/* Token of DMB */
	__aligned_u64	peer_token;	/* Token of remote DMBE */
पूर्ण;

#पूर्ण_अगर /* _UAPI_SMC_DIAG_H_ */
