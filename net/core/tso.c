<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ip.h>
#समावेश <net/tso.h>
#समावेश <यंत्र/unaligned.h>

/* Calculate expected number of TX descriptors */
पूर्णांक tso_count_descs(स्थिर काष्ठा sk_buff *skb)
अणु
	/* The Marvell Way */
	वापस skb_shinfo(skb)->gso_segs * 2 + skb_shinfo(skb)->nr_frags;
पूर्ण
EXPORT_SYMBOL(tso_count_descs);

व्योम tso_build_hdr(स्थिर काष्ठा sk_buff *skb, अक्षर *hdr, काष्ठा tso_t *tso,
		   पूर्णांक size, bool is_last)
अणु
	पूर्णांक hdr_len = skb_transport_offset(skb) + tso->tlen;
	पूर्णांक mac_hdr_len = skb_network_offset(skb);

	स_नकल(hdr, skb->data, hdr_len);
	अगर (!tso->ipv6) अणु
		काष्ठा iphdr *iph = (व्योम *)(hdr + mac_hdr_len);

		iph->id = htons(tso->ip_id);
		iph->tot_len = htons(size + hdr_len - mac_hdr_len);
		tso->ip_id++;
	पूर्ण अन्यथा अणु
		काष्ठा ipv6hdr *iph = (व्योम *)(hdr + mac_hdr_len);

		iph->payload_len = htons(size + tso->tlen);
	पूर्ण
	hdr += skb_transport_offset(skb);
	अगर (tso->tlen != माप(काष्ठा udphdr)) अणु
		काष्ठा tcphdr *tcph = (काष्ठा tcphdr *)hdr;

		put_unaligned_be32(tso->tcp_seq, &tcph->seq);

		अगर (!is_last) अणु
			/* Clear all special flags क्रम not last packet */
			tcph->psh = 0;
			tcph->fin = 0;
			tcph->rst = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा udphdr *uh = (काष्ठा udphdr *)hdr;

		uh->len = htons(माप(*uh) + size);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tso_build_hdr);

व्योम tso_build_data(स्थिर काष्ठा sk_buff *skb, काष्ठा tso_t *tso, पूर्णांक size)
अणु
	tso->tcp_seq += size; /* not worth aव्योमing this operation क्रम UDP */
	tso->size -= size;
	tso->data += size;

	अगर ((tso->size == 0) &&
	    (tso->next_frag_idx < skb_shinfo(skb)->nr_frags)) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[tso->next_frag_idx];

		/* Move to next segment */
		tso->size = skb_frag_size(frag);
		tso->data = skb_frag_address(frag);
		tso->next_frag_idx++;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tso_build_data);

पूर्णांक tso_start(काष्ठा sk_buff *skb, काष्ठा tso_t *tso)
अणु
	पूर्णांक tlen = skb_is_gso_tcp(skb) ? tcp_hdrlen(skb) : माप(काष्ठा udphdr);
	पूर्णांक hdr_len = skb_transport_offset(skb) + tlen;

	tso->tlen = tlen;
	tso->ip_id = ntohs(ip_hdr(skb)->id);
	tso->tcp_seq = (tlen != माप(काष्ठा udphdr)) ? ntohl(tcp_hdr(skb)->seq) : 0;
	tso->next_frag_idx = 0;
	tso->ipv6 = vlan_get_protocol(skb) == htons(ETH_P_IPV6);

	/* Build first data */
	tso->size = skb_headlen(skb) - hdr_len;
	tso->data = skb->data + hdr_len;
	अगर ((tso->size == 0) &&
	    (tso->next_frag_idx < skb_shinfo(skb)->nr_frags)) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[tso->next_frag_idx];

		/* Move to next segment */
		tso->size = skb_frag_size(frag);
		tso->data = skb_frag_address(frag);
		tso->next_frag_idx++;
	पूर्ण
	वापस hdr_len;
पूर्ण
EXPORT_SYMBOL(tso_start);
