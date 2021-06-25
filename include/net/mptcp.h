<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Multipath TCP
 *
 * Copyright (c) 2017 - 2019, Intel Corporation.
 */

#अगर_अघोषित __NET_MPTCP_H
#घोषणा __NET_MPTCP_H

#समावेश <linux/skbuff.h>
#समावेश <linux/tcp.h>
#समावेश <linux/types.h>

काष्ठा seq_file;

/* MPTCP sk_buff extension data */
काष्ठा mptcp_ext अणु
	जोड़ अणु
		u64	data_ack;
		u32	data_ack32;
	पूर्ण;
	u64		data_seq;
	u32		subflow_seq;
	u16		data_len;
	u8		use_map:1,
			dsn64:1,
			data_fin:1,
			use_ack:1,
			ack64:1,
			mpc_map:1,
			frozen:1,
			reset_transient:1;
	u8		reset_reason:4;
पूर्ण;

#घोषणा MPTCP_RM_IDS_MAX	8

काष्ठा mptcp_rm_list अणु
	u8 ids[MPTCP_RM_IDS_MAX];
	u8 nr;
पूर्ण;

काष्ठा mptcp_addr_info अणु
	u8			id;
	sa_family_t		family;
	__be16			port;
	जोड़ अणु
		काष्ठा in_addr	addr;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
		काष्ठा in6_addr	addr6;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

काष्ठा mptcp_out_options अणु
#अगर IS_ENABLED(CONFIG_MPTCP)
	u16 suboptions;
	u64 sndr_key;
	u64 rcvr_key;
	u64 ahmac;
	काष्ठा mptcp_addr_info addr;
	काष्ठा mptcp_rm_list rm_list;
	u8 join_id;
	u8 backup;
	u8 reset_reason:4;
	u8 reset_transient:1;
	u32 nonce;
	u64 thmac;
	u32 token;
	u8 hmac[20];
	काष्ठा mptcp_ext ext_copy;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_MPTCP
बाह्य काष्ठा request_sock_ops mptcp_subflow_request_sock_ops;

व्योम mptcp_init(व्योम);

अटल अंतरभूत bool sk_is_mptcp(स्थिर काष्ठा sock *sk)
अणु
	वापस tcp_sk(sk)->is_mptcp;
पूर्ण

अटल अंतरभूत bool rsk_is_mptcp(स्थिर काष्ठा request_sock *req)
अणु
	वापस tcp_rsk(req)->is_mptcp;
पूर्ण

अटल अंतरभूत bool rsk_drop_req(स्थिर काष्ठा request_sock *req)
अणु
	वापस tcp_rsk(req)->is_mptcp && tcp_rsk(req)->drop_req;
पूर्ण

व्योम mptcp_space(स्थिर काष्ठा sock *ssk, पूर्णांक *space, पूर्णांक *full_space);
bool mptcp_syn_options(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक *size, काष्ठा mptcp_out_options *opts);
bool mptcp_synack_options(स्थिर काष्ठा request_sock *req, अचिन्हित पूर्णांक *size,
			  काष्ठा mptcp_out_options *opts);
bool mptcp_established_options(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक *size, अचिन्हित पूर्णांक reमुख्यing,
			       काष्ठा mptcp_out_options *opts);
व्योम mptcp_incoming_options(काष्ठा sock *sk, काष्ठा sk_buff *skb);

व्योम mptcp_ग_लिखो_options(__be32 *ptr, स्थिर काष्ठा tcp_sock *tp,
			 काष्ठा mptcp_out_options *opts);

/* move the skb extension owership, with the assumption that 'to' is
 * newly allocated
 */
अटल अंतरभूत व्योम mptcp_skb_ext_move(काष्ठा sk_buff *to,
				      काष्ठा sk_buff *from)
अणु
	अगर (!skb_ext_exist(from, SKB_EXT_MPTCP))
		वापस;

	अगर (WARN_ON_ONCE(to->active_extensions))
		skb_ext_put(to);

	to->active_extensions = from->active_extensions;
	to->extensions = from->extensions;
	from->active_extensions = 0;
पूर्ण

अटल अंतरभूत व्योम mptcp_skb_ext_copy(काष्ठा sk_buff *to,
				      काष्ठा sk_buff *from)
अणु
	काष्ठा mptcp_ext *from_ext;

	from_ext = skb_ext_find(from, SKB_EXT_MPTCP);
	अगर (!from_ext)
		वापस;

	from_ext->frozen = 1;
	skb_ext_copy(to, from);
पूर्ण

अटल अंतरभूत bool mptcp_ext_matches(स्थिर काष्ठा mptcp_ext *to_ext,
				     स्थिर काष्ठा mptcp_ext *from_ext)
अणु
	/* MPTCP always clears the ext when adding it to the skb, so
	 * holes करो not bother us here
	 */
	वापस !from_ext ||
	       (to_ext && from_ext &&
	        !स_भेद(from_ext, to_ext, माप(काष्ठा mptcp_ext)));
पूर्ण

/* check अगर skbs can be collapsed.
 * MPTCP collapse is allowed अगर neither @to or @from carry an mptcp data
 * mapping, or अगर the extension of @to is the same as @from.
 * Collapsing is not possible अगर @to lacks an extension, but @from carries one.
 */
अटल अंतरभूत bool mptcp_skb_can_collapse(स्थिर काष्ठा sk_buff *to,
					  स्थिर काष्ठा sk_buff *from)
अणु
	वापस mptcp_ext_matches(skb_ext_find(to, SKB_EXT_MPTCP),
				 skb_ext_find(from, SKB_EXT_MPTCP));
पूर्ण

व्योम mptcp_seq_show(काष्ठा seq_file *seq);
पूर्णांक mptcp_subflow_init_cookie_req(काष्ठा request_sock *req,
				  स्थिर काष्ठा sock *sk_listener,
				  काष्ठा sk_buff *skb);

__be32 mptcp_get_reset_option(स्थिर काष्ठा sk_buff *skb);

अटल अंतरभूत __be32 mptcp_reset_option(स्थिर काष्ठा sk_buff *skb)
अणु
	अगर (skb_ext_exist(skb, SKB_EXT_MPTCP))
		वापस mptcp_get_reset_option(skb);

	वापस htonl(0u);
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम mptcp_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool sk_is_mptcp(स्थिर काष्ठा sock *sk)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool rsk_is_mptcp(स्थिर काष्ठा request_sock *req)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool rsk_drop_req(स्थिर काष्ठा request_sock *req)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम mptcp_parse_option(स्थिर काष्ठा sk_buff *skb,
				      स्थिर अचिन्हित अक्षर *ptr, पूर्णांक opsize,
				      काष्ठा tcp_options_received *opt_rx)
अणु
पूर्ण

अटल अंतरभूत bool mptcp_syn_options(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb,
				     अचिन्हित पूर्णांक *size,
				     काष्ठा mptcp_out_options *opts)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool mptcp_synack_options(स्थिर काष्ठा request_sock *req,
					अचिन्हित पूर्णांक *size,
					काष्ठा mptcp_out_options *opts)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool mptcp_established_options(काष्ठा sock *sk,
					     काष्ठा sk_buff *skb,
					     अचिन्हित पूर्णांक *size,
					     अचिन्हित पूर्णांक reमुख्यing,
					     काष्ठा mptcp_out_options *opts)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम mptcp_incoming_options(काष्ठा sock *sk,
					  काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत व्योम mptcp_skb_ext_move(काष्ठा sk_buff *to,
				      स्थिर काष्ठा sk_buff *from)
अणु
पूर्ण

अटल अंतरभूत व्योम mptcp_skb_ext_copy(काष्ठा sk_buff *to,
				      काष्ठा sk_buff *from)
अणु
पूर्ण

अटल अंतरभूत bool mptcp_skb_can_collapse(स्थिर काष्ठा sk_buff *to,
					  स्थिर काष्ठा sk_buff *from)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम mptcp_space(स्थिर काष्ठा sock *ssk, पूर्णांक *s, पूर्णांक *fs) अणु पूर्ण
अटल अंतरभूत व्योम mptcp_seq_show(काष्ठा seq_file *seq) अणु पूर्ण

अटल अंतरभूत पूर्णांक mptcp_subflow_init_cookie_req(काष्ठा request_sock *req,
						स्थिर काष्ठा sock *sk_listener,
						काष्ठा sk_buff *skb)
अणु
	वापस 0; /* TCP fallback */
पूर्ण

अटल अंतरभूत __be32 mptcp_reset_option(स्थिर काष्ठा sk_buff *skb)  अणु वापस htonl(0u); पूर्ण
#पूर्ण_अगर /* CONFIG_MPTCP */

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
पूर्णांक mptcpv6_init(व्योम);
व्योम mptcpv6_handle_mapped(काष्ठा sock *sk, bool mapped);
#या_अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत पूर्णांक mptcpv6_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम mptcpv6_handle_mapped(काष्ठा sock *sk, bool mapped) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __NET_MPTCP_H */
