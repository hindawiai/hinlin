<शैली गुरु>
/* IPv4-specअगरic defines क्रम netfilter. 
 * (C)1998 Rusty Russell -- This code is GPL.
 */
#अगर_अघोषित __LINUX_IP_NETFILTER_H
#घोषणा __LINUX_IP_NETFILTER_H

#समावेश <uapi/linux/netfilter_ipv4.h>

/* Extra routing may needed on local out, as the QUEUE target never वापसs
 * control to the table.
 */
काष्ठा ip_rt_info अणु
	__be32 daddr;
	__be32 saddr;
	u_पूर्णांक8_t tos;
	u_पूर्णांक32_t mark;
पूर्ण;

पूर्णांक ip_route_me_harder(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित addr_type);

काष्ठा nf_queue_entry;

#अगर_घोषित CONFIG_INET
__sum16 nf_ip_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
		       अचिन्हित पूर्णांक dataoff, u_पूर्णांक8_t protocol);
पूर्णांक nf_ip_route(काष्ठा net *net, काष्ठा dst_entry **dst, काष्ठा flowi *fl,
		bool strict);
#अन्यथा
अटल अंतरभूत __sum16 nf_ip_checksum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक hook,
				     अचिन्हित पूर्णांक dataoff, u_पूर्णांक8_t protocol)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक nf_ip_route(काष्ठा net *net, काष्ठा dst_entry **dst,
			      काष्ठा flowi *fl, bool strict)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_INET */

#पूर्ण_अगर /*__LINUX_IP_NETFILTER_H*/
