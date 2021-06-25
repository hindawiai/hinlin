<शैली गुरु>
#अगर_अघोषित __NET_TUN_PROTO_H
#घोषणा __NET_TUN_PROTO_H

#समावेश <linux/kernel.h>

/* One byte protocol values as defined by VXLAN-GPE and NSH. These will
 * hopefully get a shared IANA registry.
 */
#घोषणा TUN_P_IPV4      0x01
#घोषणा TUN_P_IPV6      0x02
#घोषणा TUN_P_ETHERNET  0x03
#घोषणा TUN_P_NSH       0x04
#घोषणा TUN_P_MPLS_UC   0x05

अटल अंतरभूत __be16 tun_p_to_eth_p(u8 proto)
अणु
	चयन (proto) अणु
	हाल TUN_P_IPV4:
		वापस htons(ETH_P_IP);
	हाल TUN_P_IPV6:
		वापस htons(ETH_P_IPV6);
	हाल TUN_P_ETHERNET:
		वापस htons(ETH_P_TEB);
	हाल TUN_P_NSH:
		वापस htons(ETH_P_NSH);
	हाल TUN_P_MPLS_UC:
		वापस htons(ETH_P_MPLS_UC);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u8 tun_p_from_eth_p(__be16 proto)
अणु
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		वापस TUN_P_IPV4;
	हाल htons(ETH_P_IPV6):
		वापस TUN_P_IPV6;
	हाल htons(ETH_P_TEB):
		वापस TUN_P_ETHERNET;
	हाल htons(ETH_P_NSH):
		वापस TUN_P_NSH;
	हाल htons(ETH_P_MPLS_UC):
		वापस TUN_P_MPLS_UC;
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर
