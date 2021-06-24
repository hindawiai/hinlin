<शैली गुरु>
#घोषणा KBUILD_MODNAME "foo"
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/ip.h>
#समावेश <uapi/linux/in.h>
#समावेश <uapi/linux/tcp.h>
#समावेश <uapi/linux/filter.h>
#समावेश <uapi/linux/pkt_cls.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_legacy.h"

/* compiler workaround */
#घोषणा _htonl __builtin_bswap32

अटल अंतरभूत व्योम set_dst_mac(काष्ठा __sk_buff *skb, अक्षर *mac)
अणु
	bpf_skb_store_bytes(skb, 0, mac, ETH_ALEN, 1);
पूर्ण

#घोषणा IP_CSUM_OFF (ETH_HLEN + दुरत्व(काष्ठा iphdr, check))
#घोषणा TOS_OFF (ETH_HLEN + दुरत्व(काष्ठा iphdr, tos))

अटल अंतरभूत व्योम set_ip_tos(काष्ठा __sk_buff *skb, __u8 new_tos)
अणु
	__u8 old_tos = load_byte(skb, TOS_OFF);

	bpf_l3_csum_replace(skb, IP_CSUM_OFF, htons(old_tos), htons(new_tos), 2);
	bpf_skb_store_bytes(skb, TOS_OFF, &new_tos, माप(new_tos), 0);
पूर्ण

#घोषणा TCP_CSUM_OFF (ETH_HLEN + माप(काष्ठा iphdr) + दुरत्व(काष्ठा tcphdr, check))
#घोषणा IP_SRC_OFF (ETH_HLEN + दुरत्व(काष्ठा iphdr, saddr))

#घोषणा IS_PSEUDO 0x10

अटल अंतरभूत व्योम set_tcp_ip_src(काष्ठा __sk_buff *skb, __u32 new_ip)
अणु
	__u32 old_ip = _htonl(load_word(skb, IP_SRC_OFF));

	bpf_l4_csum_replace(skb, TCP_CSUM_OFF, old_ip, new_ip, IS_PSEUDO | माप(new_ip));
	bpf_l3_csum_replace(skb, IP_CSUM_OFF, old_ip, new_ip, माप(new_ip));
	bpf_skb_store_bytes(skb, IP_SRC_OFF, &new_ip, माप(new_ip), 0);
पूर्ण

#घोषणा TCP_DPORT_OFF (ETH_HLEN + माप(काष्ठा iphdr) + दुरत्व(काष्ठा tcphdr, dest))
अटल अंतरभूत व्योम set_tcp_dest_port(काष्ठा __sk_buff *skb, __u16 new_port)
अणु
	__u16 old_port = htons(load_half(skb, TCP_DPORT_OFF));

	bpf_l4_csum_replace(skb, TCP_CSUM_OFF, old_port, new_port, माप(new_port));
	bpf_skb_store_bytes(skb, TCP_DPORT_OFF, &new_port, माप(new_port), 0);
पूर्ण

SEC("classifier")
पूर्णांक bpf_prog1(काष्ठा __sk_buff *skb)
अणु
	__u8 proto = load_byte(skb, ETH_HLEN + दुरत्व(काष्ठा iphdr, protocol));
	दीर्घ *value;

	अगर (proto == IPPROTO_TCP) अणु
		set_ip_tos(skb, 8);
		set_tcp_ip_src(skb, 0xA010101);
		set_tcp_dest_port(skb, 5001);
	पूर्ण

	वापस 0;
पूर्ण
SEC("redirect_xmit")
पूर्णांक _redirect_xmit(काष्ठा __sk_buff *skb)
अणु
	वापस bpf_redirect(skb->अगरindex + 1, 0);
पूर्ण
SEC("redirect_recv")
पूर्णांक _redirect_recv(काष्ठा __sk_buff *skb)
अणु
	वापस bpf_redirect(skb->अगरindex + 1, 1);
पूर्ण
SEC("clone_redirect_xmit")
पूर्णांक _clone_redirect_xmit(काष्ठा __sk_buff *skb)
अणु
	bpf_clone_redirect(skb, skb->अगरindex + 1, 0);
	वापस TC_ACT_SHOT;
पूर्ण
SEC("clone_redirect_recv")
पूर्णांक _clone_redirect_recv(काष्ठा __sk_buff *skb)
अणु
	bpf_clone_redirect(skb, skb->अगरindex + 1, 1);
	वापस TC_ACT_SHOT;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
