<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ICMPV6_H
#घोषणा _LINUX_ICMPV6_H

#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <uapi/linux/icmpv6.h>

अटल अंतरभूत काष्ठा icmp6hdr *icmp6_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा icmp6hdr *)skb_transport_header(skb);
पूर्ण

#समावेश <linux/netdevice.h>

#अगर IS_ENABLED(CONFIG_IPV6)

प्रकार व्योम ip6_icmp_send_t(काष्ठा sk_buff *skb, u8 type, u8 code, __u32 info,
			     स्थिर काष्ठा in6_addr *क्रमce_saddr,
			     स्थिर काष्ठा inet6_skb_parm *parm);
व्योम icmp6_send(काष्ठा sk_buff *skb, u8 type, u8 code, __u32 info,
		स्थिर काष्ठा in6_addr *क्रमce_saddr,
		स्थिर काष्ठा inet6_skb_parm *parm);
#अगर IS_BUILTIN(CONFIG_IPV6)
अटल अंतरभूत व्योम __icmpv6_send(काष्ठा sk_buff *skb, u8 type, u8 code, __u32 info,
				 स्थिर काष्ठा inet6_skb_parm *parm)
अणु
	icmp6_send(skb, type, code, info, शून्य, parm);
पूर्ण
अटल अंतरभूत पूर्णांक inet6_रेजिस्टर_icmp_sender(ip6_icmp_send_t *fn)
अणु
	BUILD_BUG_ON(fn != icmp6_send);
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक inet6_unरेजिस्टर_icmp_sender(ip6_icmp_send_t *fn)
अणु
	BUILD_BUG_ON(fn != icmp6_send);
	वापस 0;
पूर्ण
#अन्यथा
बाह्य व्योम __icmpv6_send(काष्ठा sk_buff *skb, u8 type, u8 code, __u32 info,
			  स्थिर काष्ठा inet6_skb_parm *parm);
बाह्य पूर्णांक inet6_रेजिस्टर_icmp_sender(ip6_icmp_send_t *fn);
बाह्य पूर्णांक inet6_unरेजिस्टर_icmp_sender(ip6_icmp_send_t *fn);
#पूर्ण_अगर

अटल अंतरभूत व्योम icmpv6_send(काष्ठा sk_buff *skb, u8 type, u8 code, __u32 info)
अणु
	__icmpv6_send(skb, type, code, info, IP6CB(skb));
पूर्ण

पूर्णांक ip6_err_gen_icmpv6_unreach(काष्ठा sk_buff *skb, पूर्णांक nhs, पूर्णांक type,
			       अचिन्हित पूर्णांक data_len);

#अगर IS_ENABLED(CONFIG_NF_NAT)
व्योम icmpv6_nकरो_send(काष्ठा sk_buff *skb_in, u8 type, u8 code, __u32 info);
#अन्यथा
अटल अंतरभूत व्योम icmpv6_nकरो_send(काष्ठा sk_buff *skb_in, u8 type, u8 code, __u32 info)
अणु
	काष्ठा inet6_skb_parm parm = अणु 0 पूर्ण;
	__icmpv6_send(skb_in, type, code, info, &parm);
पूर्ण
#पूर्ण_अगर

#अन्यथा

अटल अंतरभूत व्योम icmpv6_send(काष्ठा sk_buff *skb,
			       u8 type, u8 code, __u32 info)
अणु
पूर्ण

अटल अंतरभूत व्योम icmpv6_nकरो_send(काष्ठा sk_buff *skb,
				   u8 type, u8 code, __u32 info)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक				icmpv6_init(व्योम);
बाह्य पूर्णांक				icmpv6_err_convert(u8 type, u8 code,
							   पूर्णांक *err);
बाह्य व्योम				icmpv6_cleanup(व्योम);
बाह्य व्योम				icmpv6_param_prob(काष्ठा sk_buff *skb,
							  u8 code, पूर्णांक pos);

काष्ठा flowi6;
काष्ठा in6_addr;
बाह्य व्योम				icmpv6_flow_init(काष्ठा sock *sk,
							 काष्ठा flowi6 *fl6,
							 u8 type,
							 स्थिर काष्ठा in6_addr *saddr,
							 स्थिर काष्ठा in6_addr *daddr,
							 पूर्णांक oअगर);

अटल अंतरभूत bool icmpv6_is_err(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल ICMPV6_DEST_UNREACH:
	हाल ICMPV6_PKT_TOOBIG:
	हाल ICMPV6_TIME_EXCEED:
	हाल ICMPV6_PARAMPROB:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#पूर्ण_अगर
