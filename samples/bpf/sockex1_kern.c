<शैली गुरु>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/अगर_packet.h>
#समावेश <uapi/linux/ip.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "bpf_legacy.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, 256);
पूर्ण my_map SEC(".maps");

SEC("socket1")
पूर्णांक bpf_prog1(काष्ठा __sk_buff *skb)
अणु
	पूर्णांक index = load_byte(skb, ETH_HLEN + दुरत्व(काष्ठा iphdr, protocol));
	दीर्घ *value;

	अगर (skb->pkt_type != PACKET_OUTGOING)
		वापस 0;

	value = bpf_map_lookup_elem(&my_map, &index);
	अगर (value)
		__sync_fetch_and_add(value, skb->len);

	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
