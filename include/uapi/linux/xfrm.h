<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_XFRM_H
#घोषणा _LINUX_XFRM_H

#समावेश <linux/in6.h>
#समावेश <linux/types.h>

/* All of the काष्ठाures in this file may not change size as they are
 * passed पूर्णांकo the kernel from userspace via netlink sockets.
 */

/* Structure to encapsulate addresses. I करो not want to use
 * "standard" काष्ठाure. My apologies.
 */
प्रकार जोड़ अणु
	__be32		a4;
	__be32		a6[4];
	काष्ठा in6_addr	in6;
पूर्ण xfrm_address_t;

/* Ident of a specअगरic xfrm_state. It is used on input to lookup
 * the state by (spi,daddr,ah/esp) or to store inक्रमmation about
 * spi, protocol and tunnel address on output.
 */
काष्ठा xfrm_id अणु
	xfrm_address_t	daddr;
	__be32		spi;
	__u8		proto;
पूर्ण;

काष्ठा xfrm_sec_ctx अणु
	__u8	ctx_करोi;
	__u8	ctx_alg;
	__u16	ctx_len;
	__u32	ctx_sid;
	अक्षर	ctx_str[0];
पूर्ण;

/* Security Context Doमुख्यs of Interpretation */
#घोषणा XFRM_SC_DOI_RESERVED 0
#घोषणा XFRM_SC_DOI_LSM 1

/* Security Context Algorithms */
#घोषणा XFRM_SC_ALG_RESERVED 0
#घोषणा XFRM_SC_ALG_SELINUX 1

/* Selector, used as selector both on policy rules (SPD) and SAs. */

काष्ठा xfrm_selector अणु
	xfrm_address_t	daddr;
	xfrm_address_t	saddr;
	__be16	dport;
	__be16	dport_mask;
	__be16	sport;
	__be16	sport_mask;
	__u16	family;
	__u8	prefixlen_d;
	__u8	prefixlen_s;
	__u8	proto;
	पूर्णांक	अगरindex;
	__kernel_uid32_t	user;
पूर्ण;

#घोषणा XFRM_INF (~(__u64)0)

काष्ठा xfrm_lअगरeसमय_cfg अणु
	__u64	soft_byte_limit;
	__u64	hard_byte_limit;
	__u64	soft_packet_limit;
	__u64	hard_packet_limit;
	__u64	soft_add_expires_seconds;
	__u64	hard_add_expires_seconds;
	__u64	soft_use_expires_seconds;
	__u64	hard_use_expires_seconds;
पूर्ण;

काष्ठा xfrm_lअगरeसमय_cur अणु
	__u64	bytes;
	__u64	packets;
	__u64	add_समय;
	__u64	use_समय;
पूर्ण;

काष्ठा xfrm_replay_state अणु
	__u32	oseq;
	__u32	seq;
	__u32	biपंचांगap;
पूर्ण;

#घोषणा XFRMA_REPLAY_ESN_MAX	4096

काष्ठा xfrm_replay_state_esn अणु
	अचिन्हित पूर्णांक	bmp_len;
	__u32		oseq;
	__u32		seq;
	__u32		oseq_hi;
	__u32		seq_hi;
	__u32		replay_winकरोw;
	__u32		bmp[0];
पूर्ण;

काष्ठा xfrm_algo अणु
	अक्षर		alg_name[64];
	अचिन्हित पूर्णांक	alg_key_len;    /* in bits */
	अक्षर		alg_key[0];
पूर्ण;

काष्ठा xfrm_algo_auth अणु
	अक्षर		alg_name[64];
	अचिन्हित पूर्णांक	alg_key_len;    /* in bits */
	अचिन्हित पूर्णांक	alg_trunc_len;  /* in bits */
	अक्षर		alg_key[0];
पूर्ण;

काष्ठा xfrm_algo_aead अणु
	अक्षर		alg_name[64];
	अचिन्हित पूर्णांक	alg_key_len;	/* in bits */
	अचिन्हित पूर्णांक	alg_icv_len;	/* in bits */
	अक्षर		alg_key[0];
पूर्ण;

काष्ठा xfrm_stats अणु
	__u32	replay_winकरोw;
	__u32	replay;
	__u32	पूर्णांकegrity_failed;
पूर्ण;

क्रमागत अणु
	XFRM_POLICY_TYPE_MAIN	= 0,
	XFRM_POLICY_TYPE_SUB	= 1,
	XFRM_POLICY_TYPE_MAX	= 2,
	XFRM_POLICY_TYPE_ANY	= 255
पूर्ण;

क्रमागत अणु
	XFRM_POLICY_IN	= 0,
	XFRM_POLICY_OUT	= 1,
	XFRM_POLICY_FWD	= 2,
	XFRM_POLICY_MASK = 3,
	XFRM_POLICY_MAX	= 3
पूर्ण;

क्रमागत अणु
	XFRM_SHARE_ANY,		/* No limitations */
	XFRM_SHARE_SESSION,	/* For this session only */
	XFRM_SHARE_USER,	/* For this user only */
	XFRM_SHARE_UNIQUE	/* Use once */
पूर्ण;

#घोषणा XFRM_MODE_TRANSPORT 0
#घोषणा XFRM_MODE_TUNNEL 1
#घोषणा XFRM_MODE_ROUTEOPTIMIZATION 2
#घोषणा XFRM_MODE_IN_TRIGGER 3
#घोषणा XFRM_MODE_BEET 4
#घोषणा XFRM_MODE_MAX 5

/* Netlink configuration messages.  */
क्रमागत अणु
	XFRM_MSG_BASE = 0x10,

	XFRM_MSG_NEWSA = 0x10,
#घोषणा XFRM_MSG_NEWSA XFRM_MSG_NEWSA
	XFRM_MSG_DELSA,
#घोषणा XFRM_MSG_DELSA XFRM_MSG_DELSA
	XFRM_MSG_GETSA,
#घोषणा XFRM_MSG_GETSA XFRM_MSG_GETSA

	XFRM_MSG_NEWPOLICY,
#घोषणा XFRM_MSG_NEWPOLICY XFRM_MSG_NEWPOLICY
	XFRM_MSG_DELPOLICY,
#घोषणा XFRM_MSG_DELPOLICY XFRM_MSG_DELPOLICY
	XFRM_MSG_GETPOLICY,
#घोषणा XFRM_MSG_GETPOLICY XFRM_MSG_GETPOLICY

	XFRM_MSG_ALLOCSPI,
#घोषणा XFRM_MSG_ALLOCSPI XFRM_MSG_ALLOCSPI
	XFRM_MSG_ACQUIRE,
#घोषणा XFRM_MSG_ACQUIRE XFRM_MSG_ACQUIRE
	XFRM_MSG_EXPIRE,
#घोषणा XFRM_MSG_EXPIRE XFRM_MSG_EXPIRE

	XFRM_MSG_UPDPOLICY,
#घोषणा XFRM_MSG_UPDPOLICY XFRM_MSG_UPDPOLICY
	XFRM_MSG_UPDSA,
#घोषणा XFRM_MSG_UPDSA XFRM_MSG_UPDSA

	XFRM_MSG_POLEXPIRE,
#घोषणा XFRM_MSG_POLEXPIRE XFRM_MSG_POLEXPIRE

	XFRM_MSG_FLUSHSA,
#घोषणा XFRM_MSG_FLUSHSA XFRM_MSG_FLUSHSA
	XFRM_MSG_FLUSHPOLICY,
#घोषणा XFRM_MSG_FLUSHPOLICY XFRM_MSG_FLUSHPOLICY

	XFRM_MSG_NEWAE,
#घोषणा XFRM_MSG_NEWAE XFRM_MSG_NEWAE
	XFRM_MSG_GETAE,
#घोषणा XFRM_MSG_GETAE XFRM_MSG_GETAE

	XFRM_MSG_REPORT,
#घोषणा XFRM_MSG_REPORT XFRM_MSG_REPORT

	XFRM_MSG_MIGRATE,
#घोषणा XFRM_MSG_MIGRATE XFRM_MSG_MIGRATE

	XFRM_MSG_NEWSADINFO,
#घोषणा XFRM_MSG_NEWSADINFO XFRM_MSG_NEWSADINFO
	XFRM_MSG_GETSADINFO,
#घोषणा XFRM_MSG_GETSADINFO XFRM_MSG_GETSADINFO

	XFRM_MSG_NEWSPDINFO,
#घोषणा XFRM_MSG_NEWSPDINFO XFRM_MSG_NEWSPDINFO
	XFRM_MSG_GETSPDINFO,
#घोषणा XFRM_MSG_GETSPDINFO XFRM_MSG_GETSPDINFO

	XFRM_MSG_MAPPING,
#घोषणा XFRM_MSG_MAPPING XFRM_MSG_MAPPING
	__XFRM_MSG_MAX
पूर्ण;
#घोषणा XFRM_MSG_MAX (__XFRM_MSG_MAX - 1)

#घोषणा XFRM_NR_MSGTYPES (XFRM_MSG_MAX + 1 - XFRM_MSG_BASE)

/*
 * Generic LSM security context क्रम comunicating to user space
 * NOTE: Same क्रमmat as sadb_x_sec_ctx
 */
काष्ठा xfrm_user_sec_ctx अणु
	__u16			len;
	__u16			exttype;
	__u8			ctx_alg;  /* LSMs: e.g., selinux == 1 */
	__u8			ctx_करोi;
	__u16			ctx_len;
पूर्ण;

काष्ठा xfrm_user_पंचांगpl अणु
	काष्ठा xfrm_id		id;
	__u16			family;
	xfrm_address_t		saddr;
	__u32			reqid;
	__u8			mode;
	__u8			share;
	__u8			optional;
	__u32			aalgos;
	__u32			ealgos;
	__u32			calgos;
पूर्ण;

काष्ठा xfrm_encap_पंचांगpl अणु
	__u16		encap_type;
	__be16		encap_sport;
	__be16		encap_dport;
	xfrm_address_t	encap_oa;
पूर्ण;

/* AEVENT flags  */
क्रमागत xfrm_ae_ftype_t अणु
	XFRM_AE_UNSPEC,
	XFRM_AE_RTHR=1,	/* replay threshold*/
	XFRM_AE_RVAL=2, /* replay value */
	XFRM_AE_LVAL=4, /* lअगरeसमय value */
	XFRM_AE_ETHR=8, /* expiry समयr threshold */
	XFRM_AE_CR=16, /* Event cause is replay update */
	XFRM_AE_CE=32, /* Event cause is समयr expiry */
	XFRM_AE_CU=64, /* Event cause is policy update */
	__XFRM_AE_MAX

#घोषणा XFRM_AE_MAX (__XFRM_AE_MAX - 1)
पूर्ण;

काष्ठा xfrm_userpolicy_type अणु
	__u8		type;
	__u16		reserved1;
	__u8		reserved2;
पूर्ण;

/* Netlink message attributes.  */
क्रमागत xfrm_attr_type_t अणु
	XFRMA_UNSPEC,
	XFRMA_ALG_AUTH,		/* काष्ठा xfrm_algo */
	XFRMA_ALG_CRYPT,	/* काष्ठा xfrm_algo */
	XFRMA_ALG_COMP,		/* काष्ठा xfrm_algo */
	XFRMA_ENCAP,		/* काष्ठा xfrm_algo + काष्ठा xfrm_encap_पंचांगpl */
	XFRMA_TMPL,		/* 1 or more काष्ठा xfrm_user_पंचांगpl */
	XFRMA_SA,		/* काष्ठा xfrm_usersa_info  */
	XFRMA_POLICY,		/*काष्ठा xfrm_userpolicy_info */
	XFRMA_SEC_CTX,		/* काष्ठा xfrm_sec_ctx */
	XFRMA_LTIME_VAL,
	XFRMA_REPLAY_VAL,
	XFRMA_REPLAY_THRESH,
	XFRMA_ETIMER_THRESH,
	XFRMA_SRCADDR,		/* xfrm_address_t */
	XFRMA_COADDR,		/* xfrm_address_t */
	XFRMA_LASTUSED,		/* अचिन्हित दीर्घ  */
	XFRMA_POLICY_TYPE,	/* काष्ठा xfrm_userpolicy_type */
	XFRMA_MIGRATE,
	XFRMA_ALG_AEAD,		/* काष्ठा xfrm_algo_aead */
	XFRMA_KMADDRESS,        /* काष्ठा xfrm_user_kmaddress */
	XFRMA_ALG_AUTH_TRUNC,	/* काष्ठा xfrm_algo_auth */
	XFRMA_MARK,		/* काष्ठा xfrm_mark */
	XFRMA_TFCPAD,		/* __u32 */
	XFRMA_REPLAY_ESN_VAL,	/* काष्ठा xfrm_replay_state_esn */
	XFRMA_SA_EXTRA_FLAGS,	/* __u32 */
	XFRMA_PROTO,		/* __u8 */
	XFRMA_ADDRESS_FILTER,	/* काष्ठा xfrm_address_filter */
	XFRMA_PAD,
	XFRMA_OFFLOAD_DEV,	/* काष्ठा xfrm_user_offload */
	XFRMA_SET_MARK,		/* __u32 */
	XFRMA_SET_MARK_MASK,	/* __u32 */
	XFRMA_IF_ID,		/* __u32 */
	__XFRMA_MAX

#घोषणा XFRMA_OUTPUT_MARK XFRMA_SET_MARK	/* Compatibility */
#घोषणा XFRMA_MAX (__XFRMA_MAX - 1)
पूर्ण;

काष्ठा xfrm_mark अणु
	__u32           v; /* value */
	__u32           m; /* mask */
पूर्ण;

क्रमागत xfrm_sadattr_type_t अणु
	XFRMA_SAD_UNSPEC,
	XFRMA_SAD_CNT,
	XFRMA_SAD_HINFO,
	__XFRMA_SAD_MAX

#घोषणा XFRMA_SAD_MAX (__XFRMA_SAD_MAX - 1)
पूर्ण;

काष्ठा xfrmu_sadhinfo अणु
	__u32 sadhcnt; /* current hash bkts */
	__u32 sadhmcnt; /* max allowed hash bkts */
पूर्ण;

क्रमागत xfrm_spdattr_type_t अणु
	XFRMA_SPD_UNSPEC,
	XFRMA_SPD_INFO,
	XFRMA_SPD_HINFO,
	XFRMA_SPD_IPV4_HTHRESH,
	XFRMA_SPD_IPV6_HTHRESH,
	__XFRMA_SPD_MAX

#घोषणा XFRMA_SPD_MAX (__XFRMA_SPD_MAX - 1)
पूर्ण;

काष्ठा xfrmu_spdinfo अणु
	__u32 incnt;
	__u32 outcnt;
	__u32 fwdcnt;
	__u32 inscnt;
	__u32 outscnt;
	__u32 fwdscnt;
पूर्ण;

काष्ठा xfrmu_spdhinfo अणु
	__u32 spdhcnt;
	__u32 spdhmcnt;
पूर्ण;

काष्ठा xfrmu_spdhthresh अणु
	__u8 lbits;
	__u8 rbits;
पूर्ण;

काष्ठा xfrm_usersa_info अणु
	काष्ठा xfrm_selector		sel;
	काष्ठा xfrm_id			id;
	xfrm_address_t			saddr;
	काष्ठा xfrm_lअगरeसमय_cfg	lft;
	काष्ठा xfrm_lअगरeसमय_cur	curlft;
	काष्ठा xfrm_stats		stats;
	__u32				seq;
	__u32				reqid;
	__u16				family;
	__u8				mode;		/* XFRM_MODE_xxx */
	__u8				replay_winकरोw;
	__u8				flags;
#घोषणा XFRM_STATE_NOECN	1
#घोषणा XFRM_STATE_DECAP_DSCP	2
#घोषणा XFRM_STATE_NOPMTUDISC	4
#घोषणा XFRM_STATE_WILDRECV	8
#घोषणा XFRM_STATE_ICMP		16
#घोषणा XFRM_STATE_AF_UNSPEC	32
#घोषणा XFRM_STATE_ALIGN4	64
#घोषणा XFRM_STATE_ESN		128
पूर्ण;

#घोषणा XFRM_SA_XFLAG_DONT_ENCAP_DSCP	1
#घोषणा XFRM_SA_XFLAG_OSEQ_MAY_WRAP	2

काष्ठा xfrm_usersa_id अणु
	xfrm_address_t			daddr;
	__be32				spi;
	__u16				family;
	__u8				proto;
पूर्ण;

काष्ठा xfrm_aevent_id अणु
	काष्ठा xfrm_usersa_id		sa_id;
	xfrm_address_t			saddr;
	__u32				flags;
	__u32				reqid;
पूर्ण;

काष्ठा xfrm_userspi_info अणु
	काष्ठा xfrm_usersa_info		info;
	__u32				min;
	__u32				max;
पूर्ण;

काष्ठा xfrm_userpolicy_info अणु
	काष्ठा xfrm_selector		sel;
	काष्ठा xfrm_lअगरeसमय_cfg	lft;
	काष्ठा xfrm_lअगरeसमय_cur	curlft;
	__u32				priority;
	__u32				index;
	__u8				dir;
	__u8				action;
#घोषणा XFRM_POLICY_ALLOW	0
#घोषणा XFRM_POLICY_BLOCK	1
	__u8				flags;
#घोषणा XFRM_POLICY_LOCALOK	1	/* Allow user to override global policy */
	/* Automatically expand selector to include matching ICMP payloads. */
#घोषणा XFRM_POLICY_ICMP	2
	__u8				share;
पूर्ण;

काष्ठा xfrm_userpolicy_id अणु
	काष्ठा xfrm_selector		sel;
	__u32				index;
	__u8				dir;
पूर्ण;

काष्ठा xfrm_user_acquire अणु
	काष्ठा xfrm_id			id;
	xfrm_address_t			saddr;
	काष्ठा xfrm_selector		sel;
	काष्ठा xfrm_userpolicy_info	policy;
	__u32				aalgos;
	__u32				ealgos;
	__u32				calgos;
	__u32				seq;
पूर्ण;

काष्ठा xfrm_user_expire अणु
	काष्ठा xfrm_usersa_info		state;
	__u8				hard;
पूर्ण;

काष्ठा xfrm_user_polexpire अणु
	काष्ठा xfrm_userpolicy_info	pol;
	__u8				hard;
पूर्ण;

काष्ठा xfrm_usersa_flush अणु
	__u8				proto;
पूर्ण;

काष्ठा xfrm_user_report अणु
	__u8				proto;
	काष्ठा xfrm_selector		sel;
पूर्ण;

/* Used by MIGRATE to pass addresses IKE should use to perक्रमm
 * SA negotiation with the peer */
काष्ठा xfrm_user_kmaddress अणु
	xfrm_address_t                  local;
	xfrm_address_t                  remote;
	__u32				reserved;
	__u16				family;
पूर्ण;

काष्ठा xfrm_user_migrate अणु
	xfrm_address_t			old_daddr;
	xfrm_address_t			old_saddr;
	xfrm_address_t			new_daddr;
	xfrm_address_t			new_saddr;
	__u8				proto;
	__u8				mode;
	__u16				reserved;
	__u32				reqid;
	__u16				old_family;
	__u16				new_family;
पूर्ण;

काष्ठा xfrm_user_mapping अणु
	काष्ठा xfrm_usersa_id		id;
	__u32				reqid;
	xfrm_address_t			old_saddr;
	xfrm_address_t			new_saddr;
	__be16				old_sport;
	__be16				new_sport;
पूर्ण;

काष्ठा xfrm_address_filter अणु
	xfrm_address_t			saddr;
	xfrm_address_t			daddr;
	__u16				family;
	__u8				splen;
	__u8				dplen;
पूर्ण;

काष्ठा xfrm_user_offload अणु
	पूर्णांक				अगरindex;
	__u8				flags;
पूर्ण;
#घोषणा XFRM_OFFLOAD_IPV6	1
#घोषणा XFRM_OFFLOAD_INBOUND	2

#अगर_अघोषित __KERNEL__
/* backwards compatibility क्रम userspace */
#घोषणा XFRMGRP_ACQUIRE		1
#घोषणा XFRMGRP_EXPIRE		2
#घोषणा XFRMGRP_SA		4
#घोषणा XFRMGRP_POLICY		8
#घोषणा XFRMGRP_REPORT		0x20
#पूर्ण_अगर

क्रमागत xfrm_nlgroups अणु
	XFRMNLGRP_NONE,
#घोषणा XFRMNLGRP_NONE		XFRMNLGRP_NONE
	XFRMNLGRP_ACQUIRE,
#घोषणा XFRMNLGRP_ACQUIRE	XFRMNLGRP_ACQUIRE
	XFRMNLGRP_EXPIRE,
#घोषणा XFRMNLGRP_EXPIRE	XFRMNLGRP_EXPIRE
	XFRMNLGRP_SA,
#घोषणा XFRMNLGRP_SA		XFRMNLGRP_SA
	XFRMNLGRP_POLICY,
#घोषणा XFRMNLGRP_POLICY	XFRMNLGRP_POLICY
	XFRMNLGRP_AEVENTS,
#घोषणा XFRMNLGRP_AEVENTS	XFRMNLGRP_AEVENTS
	XFRMNLGRP_REPORT,
#घोषणा XFRMNLGRP_REPORT	XFRMNLGRP_REPORT
	XFRMNLGRP_MIGRATE,
#घोषणा XFRMNLGRP_MIGRATE	XFRMNLGRP_MIGRATE
	XFRMNLGRP_MAPPING,
#घोषणा XFRMNLGRP_MAPPING	XFRMNLGRP_MAPPING
	__XFRMNLGRP_MAX
पूर्ण;
#घोषणा XFRMNLGRP_MAX	(__XFRMNLGRP_MAX - 1)

#पूर्ण_अगर /* _LINUX_XFRM_H */
