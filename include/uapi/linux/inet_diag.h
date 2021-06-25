<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_INET_DIAG_H_
#घोषणा _UAPI_INET_DIAG_H_

#समावेश <linux/types.h>

/* Just some अक्रमom number */
#घोषणा TCPDIAG_GETSOCK 18
#घोषणा DCCPDIAG_GETSOCK 19

#घोषणा INET_DIAG_GETSOCK_MAX 24

/* Socket identity */
काष्ठा inet_diag_sockid अणु
	__be16	idiag_sport;
	__be16	idiag_dport;
	__be32	idiag_src[4];
	__be32	idiag_dst[4];
	__u32	idiag_अगर;
	__u32	idiag_cookie[2];
#घोषणा INET_DIAG_NOCOOKIE (~0U)
पूर्ण;

/* Request काष्ठाure */

काष्ठा inet_diag_req अणु
	__u8	idiag_family;		/* Family of addresses. */
	__u8	idiag_src_len;
	__u8	idiag_dst_len;
	__u8	idiag_ext;		/* Query extended inक्रमmation */

	काष्ठा inet_diag_sockid id;

	__u32	idiag_states;		/* States to dump */
	__u32	idiag_dbs;		/* Tables to dump (NI) */
पूर्ण;

काष्ठा inet_diag_req_v2 अणु
	__u8	sdiag_family;
	__u8	sdiag_protocol;
	__u8	idiag_ext;
	__u8	pad;
	__u32	idiag_states;
	काष्ठा inet_diag_sockid id;
पूर्ण;

/*
 * SOCK_RAW sockets require the underlied protocol to be
 * additionally specअगरied so we can use @pad member क्रम
 * this, but we can't नाम it because userspace programs
 * still may depend on this name. Instead lets use another
 * काष्ठाure definition as an alias क्रम काष्ठा
 * @inet_diag_req_v2.
 */
काष्ठा inet_diag_req_raw अणु
	__u8	sdiag_family;
	__u8	sdiag_protocol;
	__u8	idiag_ext;
	__u8	sdiag_raw_protocol;
	__u32	idiag_states;
	काष्ठा inet_diag_sockid id;
पूर्ण;

क्रमागत अणु
	INET_DIAG_REQ_NONE,
	INET_DIAG_REQ_BYTECODE,
	INET_DIAG_REQ_SK_BPF_STORAGES,
	INET_DIAG_REQ_PROTOCOL,
	__INET_DIAG_REQ_MAX,
पूर्ण;

#घोषणा INET_DIAG_REQ_MAX (__INET_DIAG_REQ_MAX - 1)

/* Bytecode is sequence of 4 byte commands followed by variable arguments.
 * All the commands identअगरied by "code" are conditional jumps क्रमward:
 * to offset cc+"yes" or to offset cc+"no". "yes" is supposed to be
 * length of the command and its arguments.
 */
 
काष्ठा inet_diag_bc_op अणु
	अचिन्हित अक्षर	code;
	अचिन्हित अक्षर	yes;
	अचिन्हित लघु	no;
पूर्ण;

क्रमागत अणु
	INET_DIAG_BC_NOP,
	INET_DIAG_BC_JMP,
	INET_DIAG_BC_S_GE,
	INET_DIAG_BC_S_LE,
	INET_DIAG_BC_D_GE,
	INET_DIAG_BC_D_LE,
	INET_DIAG_BC_AUTO,
	INET_DIAG_BC_S_COND,
	INET_DIAG_BC_D_COND,
	INET_DIAG_BC_DEV_COND,   /* u32 अगरindex */
	INET_DIAG_BC_MARK_COND,
	INET_DIAG_BC_S_EQ,
	INET_DIAG_BC_D_EQ,
	INET_DIAG_BC_CGROUP_COND,   /* u64 cgroup v2 ID */
पूर्ण;

काष्ठा inet_diag_hostcond अणु
	__u8	family;
	__u8	prefix_len;
	पूर्णांक	port;
	__be32	addr[0];
पूर्ण;

काष्ठा inet_diag_markcond अणु
	__u32 mark;
	__u32 mask;
पूर्ण;

/* Base info काष्ठाure. It contains socket identity (addrs/ports/cookie)
 * and, alas, the inक्रमmation shown by netstat. */
काष्ठा inet_diag_msg अणु
	__u8	idiag_family;
	__u8	idiag_state;
	__u8	idiag_समयr;
	__u8	idiag_retrans;

	काष्ठा inet_diag_sockid id;

	__u32	idiag_expires;
	__u32	idiag_rqueue;
	__u32	idiag_wqueue;
	__u32	idiag_uid;
	__u32	idiag_inode;
पूर्ण;

/* Extensions */

क्रमागत अणु
	INET_DIAG_NONE,
	INET_DIAG_MEMINFO,
	INET_DIAG_INFO,
	INET_DIAG_VEGASINFO,
	INET_DIAG_CONG,
	INET_DIAG_TOS,
	INET_DIAG_TCLASS,
	INET_DIAG_SKMEMINFO,
	INET_DIAG_SHUTDOWN,

	/*
	 * Next extenstions cannot be requested in काष्ठा inet_diag_req_v2:
	 * its field idiag_ext has only 8 bits.
	 */

	INET_DIAG_DCTCPINFO,	/* request as INET_DIAG_VEGASINFO */
	INET_DIAG_PROTOCOL,	/* response attribute only */
	INET_DIAG_SKV6ONLY,
	INET_DIAG_LOCALS,
	INET_DIAG_PEERS,
	INET_DIAG_PAD,
	INET_DIAG_MARK,		/* only with CAP_NET_ADMIN */
	INET_DIAG_BBRINFO,	/* request as INET_DIAG_VEGASINFO */
	INET_DIAG_CLASS_ID,	/* request as INET_DIAG_TCLASS */
	INET_DIAG_MD5SIG,
	INET_DIAG_ULP_INFO,
	INET_DIAG_SK_BPF_STORAGES,
	INET_DIAG_CGROUP_ID,
	INET_DIAG_SOCKOPT,
	__INET_DIAG_MAX,
पूर्ण;

#घोषणा INET_DIAG_MAX (__INET_DIAG_MAX - 1)

क्रमागत अणु
	INET_ULP_INFO_UNSPEC,
	INET_ULP_INFO_NAME,
	INET_ULP_INFO_TLS,
	INET_ULP_INFO_MPTCP,
	__INET_ULP_INFO_MAX,
पूर्ण;
#घोषणा INET_ULP_INFO_MAX (__INET_ULP_INFO_MAX - 1)

/* INET_DIAG_MEM */

काष्ठा inet_diag_meminfo अणु
	__u32	idiag_rmem;
	__u32	idiag_wmem;
	__u32	idiag_fmem;
	__u32	idiag_पंचांगem;
पूर्ण;

/* INET_DIAG_SOCKOPT */

काष्ठा inet_diag_sockopt अणु
	__u8	recverr:1,
		is_icsk:1,
		मुक्तbind:1,
		hdrincl:1,
		mc_loop:1,
		transparent:1,
		mc_all:1,
		nodefrag:1;
	__u8	bind_address_no_port:1,
		recverr_rfc4884:1,
		defer_connect:1,
		unused:5;
पूर्ण;

/* INET_DIAG_VEGASINFO */

काष्ठा tcpvegas_info अणु
	__u32	tcpv_enabled;
	__u32	tcpv_rttcnt;
	__u32	tcpv_rtt;
	__u32	tcpv_minrtt;
पूर्ण;

/* INET_DIAG_DCTCPINFO */

काष्ठा tcp_dctcp_info अणु
	__u16	dctcp_enabled;
	__u16	dctcp_ce_state;
	__u32	dctcp_alpha;
	__u32	dctcp_ab_ecn;
	__u32	dctcp_ab_tot;
पूर्ण;

/* INET_DIAG_BBRINFO */

काष्ठा tcp_bbr_info अणु
	/* u64 bw: max-filtered BW (app throughput) estimate in Byte per sec: */
	__u32	bbr_bw_lo;		/* lower 32 bits of bw */
	__u32	bbr_bw_hi;		/* upper 32 bits of bw */
	__u32	bbr_min_rtt;		/* min-filtered RTT in uSec */
	__u32	bbr_pacing_gain;	/* pacing gain shअगरted left 8 bits */
	__u32	bbr_cwnd_gain;		/* cwnd gain shअगरted left 8 bits */
पूर्ण;

जोड़ tcp_cc_info अणु
	काष्ठा tcpvegas_info	vegas;
	काष्ठा tcp_dctcp_info	dctcp;
	काष्ठा tcp_bbr_info	bbr;
पूर्ण;
#पूर्ण_अगर /* _UAPI_INET_DIAG_H_ */
