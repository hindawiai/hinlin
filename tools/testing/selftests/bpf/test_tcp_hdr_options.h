<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020 Facebook */

#अगर_अघोषित _TEST_TCP_HDR_OPTIONS_H
#घोषणा _TEST_TCP_HDR_OPTIONS_H

काष्ठा bpf_test_option अणु
	__u8 flags;
	__u8 max_delack_ms;
	__u8 अक्रम;
पूर्ण __attribute__((packed));

क्रमागत अणु
	OPTION_RESEND,
	OPTION_MAX_DELACK_MS,
	OPTION_RAND,
	__NR_OPTION_FLAGS,
पूर्ण;

#घोषणा OPTION_F_RESEND		(1 << OPTION_RESEND)
#घोषणा OPTION_F_MAX_DELACK_MS	(1 << OPTION_MAX_DELACK_MS)
#घोषणा OPTION_F_RAND		(1 << OPTION_RAND)
#घोषणा OPTION_MASK		((1 << __NR_OPTION_FLAGS) - 1)

#घोषणा TEST_OPTION_FLAGS(flags, option) (1 & ((flags) >> (option)))
#घोषणा SET_OPTION_FLAGS(flags, option)	((flags) |= (1 << (option)))

/* Store in bpf_sk_storage */
काष्ठा hdr_stg अणु
	bool active;
	bool resend_syn; /* active side only */
	bool syncookie;  /* passive side only */
	bool fastखोलो;	/* passive side only */
पूर्ण;

काष्ठा linum_err अणु
	अचिन्हित पूर्णांक linum;
	पूर्णांक err;
पूर्ण;

#घोषणा TCPHDR_FIN 0x01
#घोषणा TCPHDR_SYN 0x02
#घोषणा TCPHDR_RST 0x04
#घोषणा TCPHDR_PSH 0x08
#घोषणा TCPHDR_ACK 0x10
#घोषणा TCPHDR_URG 0x20
#घोषणा TCPHDR_ECE 0x40
#घोषणा TCPHDR_CWR 0x80
#घोषणा TCPHDR_SYNACK (TCPHDR_SYN | TCPHDR_ACK)

#घोषणा TCPOPT_EOL		0
#घोषणा TCPOPT_NOP		1
#घोषणा TCPOPT_WINDOW		3
#घोषणा TCPOPT_EXP		254

#घोषणा TCP_BPF_EXPOPT_BASE_LEN 4
#घोषणा MAX_TCP_HDR_LEN		60
#घोषणा MAX_TCP_OPTION_SPACE	40

#अगर_घोषित BPF_PROG_TEST_TCP_HDR_OPTIONS

#घोषणा CG_OK	1
#घोषणा CG_ERR	0

#अगर_अघोषित SOL_TCP
#घोषणा SOL_TCP 6
#पूर्ण_अगर

काष्ठा tcp_exprm_opt अणु
	__u8 kind;
	__u8 len;
	__u16 magic;
	जोड़ अणु
		__u8 data[4];
		__u32 data32;
	पूर्ण;
पूर्ण __attribute__((packed));

काष्ठा tcp_opt अणु
	__u8 kind;
	__u8 len;
	जोड़ अणु
		__u8 data[4];
		__u32 data32;
	पूर्ण;
पूर्ण __attribute__((packed));

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(max_entries, 2);
	__type(key, पूर्णांक);
	__type(value, काष्ठा linum_err);
पूर्ण lport_linum_map SEC(".maps");

अटल अंतरभूत अचिन्हित पूर्णांक tcp_hdrlen(स्थिर काष्ठा tcphdr *th)
अणु
	वापस th->करोff << 2;
पूर्ण

अटल अंतरभूत __u8 skops_tcp_flags(स्थिर काष्ठा bpf_sock_ops *skops)
अणु
	वापस skops->skb_tcp_flags;
पूर्ण

अटल अंतरभूत व्योम clear_hdr_cb_flags(काष्ठा bpf_sock_ops *skops)
अणु
	bpf_sock_ops_cb_flags_set(skops,
				  skops->bpf_sock_ops_cb_flags &
				  ~(BPF_SOCK_OPS_PARSE_UNKNOWN_HDR_OPT_CB_FLAG |
				    BPF_SOCK_OPS_WRITE_HDR_OPT_CB_FLAG));
पूर्ण

अटल अंतरभूत व्योम set_hdr_cb_flags(काष्ठा bpf_sock_ops *skops, __u32 extra)
अणु
	bpf_sock_ops_cb_flags_set(skops,
				  skops->bpf_sock_ops_cb_flags |
				  BPF_SOCK_OPS_PARSE_UNKNOWN_HDR_OPT_CB_FLAG |
				  BPF_SOCK_OPS_WRITE_HDR_OPT_CB_FLAG |
				  extra);
पूर्ण
अटल अंतरभूत व्योम
clear_parse_all_hdr_cb_flags(काष्ठा bpf_sock_ops *skops)
अणु
	bpf_sock_ops_cb_flags_set(skops,
				  skops->bpf_sock_ops_cb_flags &
				  ~BPF_SOCK_OPS_PARSE_ALL_HDR_OPT_CB_FLAG);
पूर्ण

अटल अंतरभूत व्योम
set_parse_all_hdr_cb_flags(काष्ठा bpf_sock_ops *skops)
अणु
	bpf_sock_ops_cb_flags_set(skops,
				  skops->bpf_sock_ops_cb_flags |
				  BPF_SOCK_OPS_PARSE_ALL_HDR_OPT_CB_FLAG);
पूर्ण

#घोषणा RET_CG_ERR(__err) (अणु			\
	काष्ठा linum_err __linum_err;		\
	पूर्णांक __lport;				\
						\
	__linum_err.linum = __LINE__;		\
	__linum_err.err = __err;		\
	__lport = skops->local_port;		\
	bpf_map_update_elem(&lport_linum_map, &__lport, &__linum_err, BPF_NOEXIST); \
	clear_hdr_cb_flags(skops);					\
	clear_parse_all_hdr_cb_flags(skops);				\
	वापस CG_ERR;							\
पूर्ण)

#पूर्ण_अगर /* BPF_PROG_TEST_TCP_HDR_OPTIONS */

#पूर्ण_अगर /* _TEST_TCP_HDR_OPTIONS_H */
