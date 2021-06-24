<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Definitions क्रम the UDP-Lite (RFC 3828) code.
 */
#अगर_अघोषित _UDPLITE_H
#घोषणा _UDPLITE_H

#समावेश <net/ip6_checksum.h>

/* UDP-Lite socket options */
#घोषणा UDPLITE_SEND_CSCOV   10 /* sender partial coverage (as sent)      */
#घोषणा UDPLITE_RECV_CSCOV   11 /* receiver partial coverage (threshold ) */

बाह्य काष्ठा proto 		udplite_prot;
बाह्य काष्ठा udp_table		udplite_table;

/*
 *	Checksum computation is all in software, hence simpler getfrag.
 */
अटल __अंतरभूत__ पूर्णांक udplite_getfrag(व्योम *from, अक्षर *to, पूर्णांक  offset,
				      पूर्णांक len, पूर्णांक odd, काष्ठा sk_buff *skb)
अणु
	काष्ठा msghdr *msg = from;
	वापस copy_from_iter_full(to, len, &msg->msg_iter) ? 0 : -EFAULT;
पूर्ण

/* Designate sk as UDP-Lite socket */
अटल अंतरभूत पूर्णांक udplite_sk_init(काष्ठा sock *sk)
अणु
	udp_init_sock(sk);
	udp_sk(sk)->pcflag = UDPLITE_BIT;
	वापस 0;
पूर्ण

/*
 * 	Checksumming routines
 */
अटल अंतरभूत पूर्णांक udplite_checksum_init(काष्ठा sk_buff *skb, काष्ठा udphdr *uh)
अणु
	u16 cscov;

        /* In UDPv4 a zero checksum means that the transmitter generated no
         * checksum. UDP-Lite (like IPv6) mandates checksums, hence packets
         * with a zero checksum field are illegal.                            */
	अगर (uh->check == 0) अणु
		net_dbg_ratelimited("UDPLite: zeroed checksum field\n");
		वापस 1;
	पूर्ण

	cscov = ntohs(uh->len);

	अगर (cscov == 0)		 /* Indicates that full coverage is required. */
		;
	अन्यथा अगर (cscov < 8  || cscov > skb->len) अणु
		/*
		 * Coverage length violates RFC 3828: log and discard silently.
		 */
		net_dbg_ratelimited("UDPLite: bad csum coverage %d/%d\n",
				    cscov, skb->len);
		वापस 1;

	पूर्ण अन्यथा अगर (cscov < skb->len) अणु
        	UDP_SKB_CB(skb)->partial_cov = 1;
		UDP_SKB_CB(skb)->cscov = cscov;
		अगर (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->ip_summed = CHECKSUM_NONE;
		skb->csum_valid = 0;
        पूर्ण

	वापस 0;
पूर्ण

/* Slow-path computation of checksum. Socket is locked. */
अटल अंतरभूत __wsum udplite_csum_outgoing(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा udp_sock *up = udp_sk(skb->sk);
	पूर्णांक cscov = up->len;
	__wsum csum = 0;

	अगर (up->pcflag & UDPLITE_SEND_CC) अणु
		/*
		 * Sender has set `partial coverage' option on UDP-Lite socket.
		 * The special हाल "up->pcslen == 0" signअगरies full coverage.
		 */
		अगर (up->pcslen < up->len) अणु
			अगर (0 < up->pcslen)
				cscov = up->pcslen;
			udp_hdr(skb)->len = htons(up->pcslen);
		पूर्ण
		/*
		 * NOTE: Causes क्रम the error हाल  `up->pcslen > up->len':
		 *        (i)  Application error (will not be penalized).
		 *       (ii)  Payload too big क्रम send buffer: data is split
		 *             पूर्णांकo several packets, each with its own header.
		 *             In this हाल (e.g. last segment), coverage may
		 *             exceed packet length.
		 *       Since packets with coverage length > packet length are
		 *       illegal, we fall back to the शेषs here.
		 */
	पूर्ण

	skb->ip_summed = CHECKSUM_NONE;     /* no HW support क्रम checksumming */

	skb_queue_walk(&sk->sk_ग_लिखो_queue, skb) अणु
		स्थिर पूर्णांक off = skb_transport_offset(skb);
		स्थिर पूर्णांक len = skb->len - off;

		csum = skb_checksum(skb, off, (cscov > len)? len : cscov, csum);

		अगर ((cscov -= len) <= 0)
			अवरोध;
	पूर्ण
	वापस csum;
पूर्ण

/* Fast-path computation of checksum. Socket may not be locked. */
अटल अंतरभूत __wsum udplite_csum(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा udp_sock *up = udp_sk(skb->sk);
	स्थिर पूर्णांक off = skb_transport_offset(skb);
	पूर्णांक len = skb->len - off;

	अगर ((up->pcflag & UDPLITE_SEND_CC) && up->pcslen < len) अणु
		अगर (0 < up->pcslen)
			len = up->pcslen;
		udp_hdr(skb)->len = htons(up->pcslen);
	पूर्ण
	skb->ip_summed = CHECKSUM_NONE;     /* no HW support क्रम checksumming */

	वापस skb_checksum(skb, off, len, 0);
पूर्ण

व्योम udplite4_रेजिस्टर(व्योम);
पूर्णांक udplite_get_port(काष्ठा sock *sk, अचिन्हित लघु snum,
		     पूर्णांक (*scmp)(स्थिर काष्ठा sock *, स्थिर काष्ठा sock *));
#पूर्ण_अगर	/* _UDPLITE_H */
