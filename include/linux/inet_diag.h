<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INET_DIAG_H_
#घोषणा _INET_DIAG_H_ 1

#समावेश <net/netlink.h>
#समावेश <uapi/linux/inet_diag.h>

काष्ठा inet_hashinfo;

काष्ठा inet_diag_handler अणु
	व्योम		(*dump)(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb,
				स्थिर काष्ठा inet_diag_req_v2 *r);

	पूर्णांक		(*dump_one)(काष्ठा netlink_callback *cb,
				    स्थिर काष्ठा inet_diag_req_v2 *req);

	व्योम		(*idiag_get_info)(काष्ठा sock *sk,
					  काष्ठा inet_diag_msg *r,
					  व्योम *info);

	पूर्णांक		(*idiag_get_aux)(काष्ठा sock *sk,
					 bool net_admin,
					 काष्ठा sk_buff *skb);

	माप_प्रकार		(*idiag_get_aux_size)(काष्ठा sock *sk,
					      bool net_admin);

	पूर्णांक		(*destroy)(काष्ठा sk_buff *in_skb,
				   स्थिर काष्ठा inet_diag_req_v2 *req);

	__u16		idiag_type;
	__u16		idiag_info_size;
पूर्ण;

काष्ठा bpf_sk_storage_diag;
काष्ठा inet_diag_dump_data अणु
	काष्ठा nlattr *req_nlas[__INET_DIAG_REQ_MAX];
#घोषणा inet_diag_nla_bc req_nlas[INET_DIAG_REQ_BYTECODE]
#घोषणा inet_diag_nla_bpf_stgs req_nlas[INET_DIAG_REQ_SK_BPF_STORAGES]

	काष्ठा bpf_sk_storage_diag *bpf_stg_diag;
पूर्ण;

काष्ठा inet_connection_sock;
पूर्णांक inet_sk_diag_fill(काष्ठा sock *sk, काष्ठा inet_connection_sock *icsk,
		      काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		      स्थिर काष्ठा inet_diag_req_v2 *req,
		      u16 nlmsg_flags, bool net_admin);
व्योम inet_diag_dump_icsk(काष्ठा inet_hashinfo *h, काष्ठा sk_buff *skb,
			 काष्ठा netlink_callback *cb,
			 स्थिर काष्ठा inet_diag_req_v2 *r);
पूर्णांक inet_diag_dump_one_icsk(काष्ठा inet_hashinfo *hashinfo,
			    काष्ठा netlink_callback *cb,
			    स्थिर काष्ठा inet_diag_req_v2 *req);

काष्ठा sock *inet_diag_find_one_icsk(काष्ठा net *net,
				     काष्ठा inet_hashinfo *hashinfo,
				     स्थिर काष्ठा inet_diag_req_v2 *req);

पूर्णांक inet_diag_bc_sk(स्थिर काष्ठा nlattr *_bc, काष्ठा sock *sk);

व्योम inet_diag_msg_common_fill(काष्ठा inet_diag_msg *r, काष्ठा sock *sk);

अटल अंतरभूत माप_प्रकार inet_diag_msg_attrs_size(व्योम)
अणु
	वापस	  nla_total_size(1)  /* INET_DIAG_SHUTDOWN */
		+ nla_total_size(1)  /* INET_DIAG_TOS */
#अगर IS_ENABLED(CONFIG_IPV6)
		+ nla_total_size(1)  /* INET_DIAG_TCLASS */
		+ nla_total_size(1)  /* INET_DIAG_SKV6ONLY */
#पूर्ण_अगर
		+ nla_total_size(4)  /* INET_DIAG_MARK */
		+ nla_total_size(4)  /* INET_DIAG_CLASS_ID */
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
		+ nla_total_size_64bit(माप(u64))  /* INET_DIAG_CGROUP_ID */
#पूर्ण_अगर
		+ nla_total_size(माप(काष्ठा inet_diag_sockopt))
						     /* INET_DIAG_SOCKOPT */
		;
पूर्ण
पूर्णांक inet_diag_msg_attrs_fill(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			     काष्ठा inet_diag_msg *r, पूर्णांक ext,
			     काष्ठा user_namespace *user_ns, bool net_admin);

बाह्य पूर्णांक  inet_diag_रेजिस्टर(स्थिर काष्ठा inet_diag_handler *handler);
बाह्य व्योम inet_diag_unरेजिस्टर(स्थिर काष्ठा inet_diag_handler *handler);
#पूर्ण_अगर /* _INET_DIAG_H_ */
