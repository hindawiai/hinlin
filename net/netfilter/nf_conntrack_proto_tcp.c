<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2002-2013 Jozsef Kadlecsik <kadlec@netfilter.org>
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/tcp.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_seqadj.h>
#समावेश <net/netfilter/nf_conntrack_synproxy.h>
#समावेश <net/netfilter/nf_conntrack_समयout.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <net/netfilter/ipv4/nf_conntrack_ipv4.h>
#समावेश <net/netfilter/ipv6/nf_conntrack_ipv6.h>

  /* FIXME: Examine ipfilter's समयouts and conntrack transitions more
     बंदly.  They're more complex. --RR */

अटल स्थिर अक्षर *स्थिर tcp_conntrack_names[] = अणु
	"NONE",
	"SYN_SENT",
	"SYN_RECV",
	"ESTABLISHED",
	"FIN_WAIT",
	"CLOSE_WAIT",
	"LAST_ACK",
	"TIME_WAIT",
	"CLOSE",
	"SYN_SENT2",
पूर्ण;

#घोषणा SECS * HZ
#घोषणा MINS * 60 SECS
#घोषणा HOURS * 60 MINS
#घोषणा DAYS * 24 HOURS

अटल स्थिर अचिन्हित पूर्णांक tcp_समयouts[TCP_CONNTRACK_TIMEOUT_MAX] = अणु
	[TCP_CONNTRACK_SYN_SENT]	= 2 MINS,
	[TCP_CONNTRACK_SYN_RECV]	= 60 SECS,
	[TCP_CONNTRACK_ESTABLISHED]	= 5 DAYS,
	[TCP_CONNTRACK_FIN_WAIT]	= 2 MINS,
	[TCP_CONNTRACK_CLOSE_WAIT]	= 60 SECS,
	[TCP_CONNTRACK_LAST_ACK]	= 30 SECS,
	[TCP_CONNTRACK_TIME_WAIT]	= 2 MINS,
	[TCP_CONNTRACK_CLOSE]		= 10 SECS,
	[TCP_CONNTRACK_SYN_SENT2]	= 2 MINS,
/* RFC1122 says the R2 limit should be at least 100 seconds.
   Linux uses 15 packets as limit, which corresponds
   to ~13-30min depending on RTO. */
	[TCP_CONNTRACK_RETRANS]		= 5 MINS,
	[TCP_CONNTRACK_UNACK]		= 5 MINS,
पूर्ण;

#घोषणा sNO TCP_CONNTRACK_NONE
#घोषणा sSS TCP_CONNTRACK_SYN_SENT
#घोषणा sSR TCP_CONNTRACK_SYN_RECV
#घोषणा sES TCP_CONNTRACK_ESTABLISHED
#घोषणा sFW TCP_CONNTRACK_FIN_WAIT
#घोषणा sCW TCP_CONNTRACK_CLOSE_WAIT
#घोषणा sLA TCP_CONNTRACK_LAST_ACK
#घोषणा sTW TCP_CONNTRACK_TIME_WAIT
#घोषणा sCL TCP_CONNTRACK_CLOSE
#घोषणा sS2 TCP_CONNTRACK_SYN_SENT2
#घोषणा sIV TCP_CONNTRACK_MAX
#घोषणा sIG TCP_CONNTRACK_IGNORE

/* What TCP flags are set from RST/SYN/FIN/ACK. */
क्रमागत tcp_bit_set अणु
	TCP_SYN_SET,
	TCP_SYNACK_SET,
	TCP_FIN_SET,
	TCP_ACK_SET,
	TCP_RST_SET,
	TCP_NONE_SET,
पूर्ण;

/*
 * The TCP state transition table needs a few words...
 *
 * We are the man in the middle. All the packets go through us
 * but might get lost in transit to the destination.
 * It is assumed that the destinations can't receive segments
 * we haven't seen.
 *
 * The checked segment is in winकरोw, but our winकरोws are *not*
 * equivalent with the ones of the sender/receiver. We always
 * try to guess the state of the current sender.
 *
 * The meaning of the states are:
 *
 * NONE:	initial state
 * SYN_SENT:	SYN-only packet seen
 * SYN_SENT2:	SYN-only packet seen from reply dir, simultaneous खोलो
 * SYN_RECV:	SYN-ACK packet seen
 * ESTABLISHED:	ACK packet seen
 * FIN_WAIT:	FIN packet seen
 * CLOSE_WAIT:	ACK seen (after FIN)
 * LAST_ACK:	FIN seen (after FIN)
 * TIME_WAIT:	last ACK seen
 * CLOSE:	बंदd connection (RST)
 *
 * Packets marked as IGNORED (sIG):
 *	अगर they may be either invalid or valid
 *	and the receiver may send back a connection
 *	closing RST or a SYN/ACK.
 *
 * Packets marked as INVALID (sIV):
 *	अगर we regard them as truly invalid packets
 */
अटल स्थिर u8 tcp_conntracks[2][6][TCP_CONNTRACK_MAX] = अणु
	अणु
/* ORIGINAL */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*syn*/	   अणु sSS, sSS, sIG, sIG, sIG, sIG, sIG, sSS, sSS, sS2 पूर्ण,
/*
 *	sNO -> sSS	Initialize a new connection
 *	sSS -> sSS	Retransmitted SYN
 *	sS2 -> sS2	Late retransmitted SYN
 *	sSR -> sIG
 *	sES -> sIG	Error: SYNs in winकरोw outside the SYN_SENT state
 *			are errors. Receiver will reply with RST
 *			and बंद the connection.
 *			Or we are not in sync and hold a dead connection.
 *	sFW -> sIG
 *	sCW -> sIG
 *	sLA -> sIG
 *	sTW -> sSS	Reखोलोed connection (RFC 1122).
 *	sCL -> sSS
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*synack*/ अणु sIV, sIV, sSR, sIV, sIV, sIV, sIV, sIV, sIV, sSR पूर्ण,
/*
 *	sNO -> sIV	Too late and no reason to करो anything
 *	sSS -> sIV	Client can't send SYN and then SYN/ACK
 *	sS2 -> sSR	SYN/ACK sent to SYN2 in simultaneous खोलो
 *	sSR -> sSR	Late retransmitted SYN/ACK in simultaneous खोलो
 *	sES -> sIV	Invalid SYN/ACK packets sent by the client
 *	sFW -> sIV
 *	sCW -> sIV
 *	sLA -> sIV
 *	sTW -> sIV
 *	sCL -> sIV
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*fin*/    अणु sIV, sIV, sFW, sFW, sLA, sLA, sLA, sTW, sCL, sIV पूर्ण,
/*
 *	sNO -> sIV	Too late and no reason to करो anything...
 *	sSS -> sIV	Client migth not send FIN in this state:
 *			we enक्रमce रुकोing क्रम a SYN/ACK reply first.
 *	sS2 -> sIV
 *	sSR -> sFW	Close started.
 *	sES -> sFW
 *	sFW -> sLA	FIN seen in both directions, रुकोing क्रम
 *			the last ACK.
 *			Migth be a retransmitted FIN as well...
 *	sCW -> sLA
 *	sLA -> sLA	Retransmitted FIN. Reमुख्य in the same state.
 *	sTW -> sTW
 *	sCL -> sCL
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*ack*/	   अणु sES, sIV, sES, sES, sCW, sCW, sTW, sTW, sCL, sIV पूर्ण,
/*
 *	sNO -> sES	Assumed.
 *	sSS -> sIV	ACK is invalid: we haven't seen a SYN/ACK yet.
 *	sS2 -> sIV
 *	sSR -> sES	Established state is reached.
 *	sES -> sES	:-)
 *	sFW -> sCW	Normal बंद request answered by ACK.
 *	sCW -> sCW
 *	sLA -> sTW	Last ACK detected (RFC5961 challenged)
 *	sTW -> sTW	Retransmitted last ACK. Reमुख्य in the same state.
 *	sCL -> sCL
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*rst*/    अणु sIV, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL पूर्ण,
/*none*/   अणु sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV पूर्ण
	पूर्ण,
	अणु
/* REPLY */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*syn*/	   अणु sIV, sS2, sIV, sIV, sIV, sIV, sIV, sSS, sIV, sS2 पूर्ण,
/*
 *	sNO -> sIV	Never reached.
 *	sSS -> sS2	Simultaneous खोलो
 *	sS2 -> sS2	Retransmitted simultaneous SYN
 *	sSR -> sIV	Invalid SYN packets sent by the server
 *	sES -> sIV
 *	sFW -> sIV
 *	sCW -> sIV
 *	sLA -> sIV
 *	sTW -> sSS	Reखोलोed connection, but server may have चयनed role
 *	sCL -> sIV
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*synack*/ अणु sIV, sSR, sIG, sIG, sIG, sIG, sIG, sIG, sIG, sSR पूर्ण,
/*
 *	sSS -> sSR	Standard खोलो.
 *	sS2 -> sSR	Simultaneous खोलो
 *	sSR -> sIG	Retransmitted SYN/ACK, ignore it.
 *	sES -> sIG	Late retransmitted SYN/ACK?
 *	sFW -> sIG	Might be SYN/ACK answering ignored SYN
 *	sCW -> sIG
 *	sLA -> sIG
 *	sTW -> sIG
 *	sCL -> sIG
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*fin*/    अणु sIV, sIV, sFW, sFW, sLA, sLA, sLA, sTW, sCL, sIV पूर्ण,
/*
 *	sSS -> sIV	Server might not send FIN in this state.
 *	sS2 -> sIV
 *	sSR -> sFW	Close started.
 *	sES -> sFW
 *	sFW -> sLA	FIN seen in both directions.
 *	sCW -> sLA
 *	sLA -> sLA	Retransmitted FIN.
 *	sTW -> sTW
 *	sCL -> sCL
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*ack*/	   अणु sIV, sIG, sSR, sES, sCW, sCW, sTW, sTW, sCL, sIG पूर्ण,
/*
 *	sSS -> sIG	Might be a half-खोलो connection.
 *	sS2 -> sIG
 *	sSR -> sSR	Might answer late resent SYN.
 *	sES -> sES	:-)
 *	sFW -> sCW	Normal बंद request answered by ACK.
 *	sCW -> sCW
 *	sLA -> sTW	Last ACK detected (RFC5961 challenged)
 *	sTW -> sTW	Retransmitted last ACK.
 *	sCL -> sCL
 */
/* 	     sNO, sSS, sSR, sES, sFW, sCW, sLA, sTW, sCL, sS2	*/
/*rst*/    अणु sIV, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL, sCL पूर्ण,
/*none*/   अणु sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV, sIV पूर्ण
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
/* Prपूर्णांक out the निजी part of the conntrack. */
अटल व्योम tcp_prपूर्णांक_conntrack(काष्ठा seq_file *s, काष्ठा nf_conn *ct)
अणु
	अगर (test_bit(IPS_OFFLOAD_BIT, &ct->status))
		वापस;

	seq_म_लिखो(s, "%s ", tcp_conntrack_names[ct->proto.tcp.state]);
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक get_conntrack_index(स्थिर काष्ठा tcphdr *tcph)
अणु
	अगर (tcph->rst) वापस TCP_RST_SET;
	अन्यथा अगर (tcph->syn) वापस (tcph->ack ? TCP_SYNACK_SET : TCP_SYN_SET);
	अन्यथा अगर (tcph->fin) वापस TCP_FIN_SET;
	अन्यथा अगर (tcph->ack) वापस TCP_ACK_SET;
	अन्यथा वापस TCP_NONE_SET;
पूर्ण

/* TCP connection tracking based on 'Real Stateful TCP Packet Filtering
   in IP Filter' by Guiकरो van Rooij.

   http://www.sane.nl/events/sane2000/papers.hपंचांगl
   http://www.darkart.com/mirrors/www.obfuscation.org/ipf/

   The boundaries and the conditions are changed according to RFC793:
   the packet must पूर्णांकersect the winकरोw (i.e. segments may be
   after the right or beक्रमe the left edge) and thus receivers may ACK
   segments after the right edge of the winकरोw.

	td_maxend = max(sack + max(win,1)) seen in reply packets
	td_maxwin = max(max(win, 1)) + (sack - ack) seen in sent packets
	td_maxwin += seq + len - sender.td_maxend
			अगर seq + len > sender.td_maxend
	td_end    = max(seq + len) seen in sent packets

   I.   Upper bound क्रम valid data:	seq <= sender.td_maxend
   II.  Lower bound क्रम valid data:	seq + len >= sender.td_end - receiver.td_maxwin
   III.	Upper bound क्रम valid (s)ack:   sack <= receiver.td_end
   IV.	Lower bound क्रम valid (s)ack:	sack >= receiver.td_end - MAXACKWINDOW

   where sack is the highest right edge of sack block found in the packet
   or ack in the हाल of packet without SACK option.

   The upper bound limit क्रम a valid (s)ack is not ignored -
   we करोesn't have to deal with fragments.
*/

अटल अंतरभूत __u32 segment_seq_plus_len(__u32 seq,
					 माप_प्रकार len,
					 अचिन्हित पूर्णांक dataoff,
					 स्थिर काष्ठा tcphdr *tcph)
अणु
	/* XXX Should I use payload length field in IP/IPv6 header ?
	 * - YK */
	वापस (seq + len - dataoff - tcph->करोff*4
		+ (tcph->syn ? 1 : 0) + (tcph->fin ? 1 : 0));
पूर्ण

/* Fixme: what about big packets? */
#घोषणा MAXACKWINCONST			66000
#घोषणा MAXACKWINDOW(sender)						\
	((sender)->td_maxwin > MAXACKWINCONST ? (sender)->td_maxwin	\
					      : MAXACKWINCONST)

/*
 * Simplअगरied tcp_parse_options routine from tcp_input.c
 */
अटल व्योम tcp_options(स्थिर काष्ठा sk_buff *skb,
			अचिन्हित पूर्णांक dataoff,
			स्थिर काष्ठा tcphdr *tcph,
			काष्ठा ip_ct_tcp_state *state)
अणु
	अचिन्हित अक्षर buff[(15 * 4) - माप(काष्ठा tcphdr)];
	स्थिर अचिन्हित अक्षर *ptr;
	पूर्णांक length = (tcph->करोff*4) - माप(काष्ठा tcphdr);

	अगर (!length)
		वापस;

	ptr = skb_header_poपूर्णांकer(skb, dataoff + माप(काष्ठा tcphdr),
				 length, buff);
	अगर (!ptr)
		वापस;

	state->td_scale =
	state->flags = 0;

	जबतक (length > 0) अणु
		पूर्णांक opcode=*ptr++;
		पूर्णांक opsize;

		चयन (opcode) अणु
		हाल TCPOPT_EOL:
			वापस;
		हाल TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			जारी;
		शेष:
			अगर (length < 2)
				वापस;
			opsize=*ptr++;
			अगर (opsize < 2) /* "silly options" */
				वापस;
			अगर (opsize > length)
				वापस;	/* करोn't parse partial options */

			अगर (opcode == TCPOPT_SACK_PERM
			    && opsize == TCPOLEN_SACK_PERM)
				state->flags |= IP_CT_TCP_FLAG_SACK_PERM;
			अन्यथा अगर (opcode == TCPOPT_WINDOW
				 && opsize == TCPOLEN_WINDOW) अणु
				state->td_scale = *(u_पूर्णांक8_t *)ptr;

				अगर (state->td_scale > TCP_MAX_WSCALE)
					state->td_scale = TCP_MAX_WSCALE;

				state->flags |=
					IP_CT_TCP_FLAG_WINDOW_SCALE;
			पूर्ण
			ptr += opsize - 2;
			length -= opsize;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tcp_sack(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक dataoff,
                     स्थिर काष्ठा tcphdr *tcph, __u32 *sack)
अणु
	अचिन्हित अक्षर buff[(15 * 4) - माप(काष्ठा tcphdr)];
	स्थिर अचिन्हित अक्षर *ptr;
	पूर्णांक length = (tcph->करोff*4) - माप(काष्ठा tcphdr);
	__u32 पंचांगp;

	अगर (!length)
		वापस;

	ptr = skb_header_poपूर्णांकer(skb, dataoff + माप(काष्ठा tcphdr),
				 length, buff);
	अगर (!ptr)
		वापस;

	/* Fast path क्रम बारtamp-only option */
	अगर (length == TCPOLEN_TSTAMP_ALIGNED
	    && *(__be32 *)ptr == htonl((TCPOPT_NOP << 24)
				       | (TCPOPT_NOP << 16)
				       | (TCPOPT_TIMESTAMP << 8)
				       | TCPOLEN_TIMESTAMP))
		वापस;

	जबतक (length > 0) अणु
		पूर्णांक opcode = *ptr++;
		पूर्णांक opsize, i;

		चयन (opcode) अणु
		हाल TCPOPT_EOL:
			वापस;
		हाल TCPOPT_NOP:	/* Ref: RFC 793 section 3.1 */
			length--;
			जारी;
		शेष:
			अगर (length < 2)
				वापस;
			opsize = *ptr++;
			अगर (opsize < 2) /* "silly options" */
				वापस;
			अगर (opsize > length)
				वापस;	/* करोn't parse partial options */

			अगर (opcode == TCPOPT_SACK
			    && opsize >= (TCPOLEN_SACK_BASE
					  + TCPOLEN_SACK_PERBLOCK)
			    && !((opsize - TCPOLEN_SACK_BASE)
				 % TCPOLEN_SACK_PERBLOCK)) अणु
				क्रम (i = 0;
				     i < (opsize - TCPOLEN_SACK_BASE);
				     i += TCPOLEN_SACK_PERBLOCK) अणु
					पंचांगp = get_unaligned_be32((__be32 *)(ptr+i)+1);

					अगर (after(पंचांगp, *sack))
						*sack = पंचांगp;
				पूर्ण
				वापस;
			पूर्ण
			ptr += opsize - 2;
			length -= opsize;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool tcp_in_winकरोw(स्थिर काष्ठा nf_conn *ct,
			  काष्ठा ip_ct_tcp *state,
			  क्रमागत ip_conntrack_dir dir,
			  अचिन्हित पूर्णांक index,
			  स्थिर काष्ठा sk_buff *skb,
			  अचिन्हित पूर्णांक dataoff,
			  स्थिर काष्ठा tcphdr *tcph)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_tcp_net *tn = nf_tcp_pernet(net);
	काष्ठा ip_ct_tcp_state *sender = &state->seen[dir];
	काष्ठा ip_ct_tcp_state *receiver = &state->seen[!dir];
	स्थिर काष्ठा nf_conntrack_tuple *tuple = &ct->tuplehash[dir].tuple;
	__u32 seq, ack, sack, end, win, swin;
	u16 win_raw;
	s32 receiver_offset;
	bool res, in_recv_win;

	/*
	 * Get the required data from the packet.
	 */
	seq = ntohl(tcph->seq);
	ack = sack = ntohl(tcph->ack_seq);
	win_raw = ntohs(tcph->winकरोw);
	win = win_raw;
	end = segment_seq_plus_len(seq, skb->len, dataoff, tcph);

	अगर (receiver->flags & IP_CT_TCP_FLAG_SACK_PERM)
		tcp_sack(skb, dataoff, tcph, &sack);

	/* Take पूर्णांकo account NAT sequence number mangling */
	receiver_offset = nf_ct_seq_offset(ct, !dir, ack - 1);
	ack -= receiver_offset;
	sack -= receiver_offset;

	pr_debug("tcp_in_window: START\n");
	pr_debug("tcp_in_window: ");
	nf_ct_dump_tuple(tuple);
	pr_debug("seq=%u ack=%u+(%d) sack=%u+(%d) win=%u end=%u\n",
		 seq, ack, receiver_offset, sack, receiver_offset, win, end);
	pr_debug("tcp_in_window: sender end=%u maxend=%u maxwin=%u scale=%i "
		 "receiver end=%u maxend=%u maxwin=%u scale=%i\n",
		 sender->td_end, sender->td_maxend, sender->td_maxwin,
		 sender->td_scale,
		 receiver->td_end, receiver->td_maxend, receiver->td_maxwin,
		 receiver->td_scale);

	अगर (sender->td_maxwin == 0) अणु
		/*
		 * Initialize sender data.
		 */
		अगर (tcph->syn) अणु
			/*
			 * SYN-ACK in reply to a SYN
			 * or SYN from reply direction in simultaneous खोलो.
			 */
			sender->td_end =
			sender->td_maxend = end;
			sender->td_maxwin = (win == 0 ? 1 : win);

			tcp_options(skb, dataoff, tcph, sender);
			/*
			 * RFC 1323:
			 * Both sides must send the Winकरोw Scale option
			 * to enable winकरोw scaling in either direction.
			 */
			अगर (!(sender->flags & IP_CT_TCP_FLAG_WINDOW_SCALE
			      && receiver->flags & IP_CT_TCP_FLAG_WINDOW_SCALE))
				sender->td_scale =
				receiver->td_scale = 0;
			अगर (!tcph->ack)
				/* Simultaneous खोलो */
				वापस true;
		पूर्ण अन्यथा अणु
			/*
			 * We are in the middle of a connection,
			 * its history is lost क्रम us.
			 * Let's try to use the data from the packet.
			 */
			sender->td_end = end;
			swin = win << sender->td_scale;
			sender->td_maxwin = (swin == 0 ? 1 : swin);
			sender->td_maxend = end + sender->td_maxwin;
			अगर (receiver->td_maxwin == 0) अणु
				/* We haven't seen traffic in the other
				 * direction yet but we have to tweak winकरोw
				 * tracking to pass III and IV until that
				 * happens.
				 */
				receiver->td_end = receiver->td_maxend = sack;
			पूर्ण अन्यथा अगर (sack == receiver->td_end + 1) अणु
				/* Likely a reply to a keepalive.
				 * Needed क्रम III.
				 */
				receiver->td_end++;
			पूर्ण

		पूर्ण
	पूर्ण अन्यथा अगर (((state->state == TCP_CONNTRACK_SYN_SENT
		     && dir == IP_CT_सूची_ORIGINAL)
		   || (state->state == TCP_CONNTRACK_SYN_RECV
		     && dir == IP_CT_सूची_REPLY))
		   && after(end, sender->td_end)) अणु
		/*
		 * RFC 793: "अगर a TCP is reinitialized ... then it need
		 * not रुको at all; it must only be sure to use sequence
		 * numbers larger than those recently used."
		 */
		sender->td_end =
		sender->td_maxend = end;
		sender->td_maxwin = (win == 0 ? 1 : win);

		tcp_options(skb, dataoff, tcph, sender);
	पूर्ण

	अगर (!(tcph->ack)) अणु
		/*
		 * If there is no ACK, just pretend it was set and OK.
		 */
		ack = sack = receiver->td_end;
	पूर्ण अन्यथा अगर (((tcp_flag_word(tcph) & (TCP_FLAG_ACK|TCP_FLAG_RST)) ==
		    (TCP_FLAG_ACK|TCP_FLAG_RST))
		   && (ack == 0)) अणु
		/*
		 * Broken TCP stacks, that set ACK in RST packets as well
		 * with zero ack value.
		 */
		ack = sack = receiver->td_end;
	पूर्ण

	अगर (tcph->rst && seq == 0 && state->state == TCP_CONNTRACK_SYN_SENT)
		/*
		 * RST sent answering SYN.
		 */
		seq = end = sender->td_end;

	pr_debug("tcp_in_window: ");
	nf_ct_dump_tuple(tuple);
	pr_debug("seq=%u ack=%u+(%d) sack=%u+(%d) win=%u end=%u\n",
		 seq, ack, receiver_offset, sack, receiver_offset, win, end);
	pr_debug("tcp_in_window: sender end=%u maxend=%u maxwin=%u scale=%i "
		 "receiver end=%u maxend=%u maxwin=%u scale=%i\n",
		 sender->td_end, sender->td_maxend, sender->td_maxwin,
		 sender->td_scale,
		 receiver->td_end, receiver->td_maxend, receiver->td_maxwin,
		 receiver->td_scale);

	/* Is the ending sequence in the receive winकरोw (अगर available)? */
	in_recv_win = !receiver->td_maxwin ||
		      after(end, sender->td_end - receiver->td_maxwin - 1);

	pr_debug("tcp_in_window: I=%i II=%i III=%i IV=%i\n",
		 beक्रमe(seq, sender->td_maxend + 1),
		 (in_recv_win ? 1 : 0),
		 beक्रमe(sack, receiver->td_end + 1),
		 after(sack, receiver->td_end - MAXACKWINDOW(sender) - 1));

	अगर (beक्रमe(seq, sender->td_maxend + 1) &&
	    in_recv_win &&
	    beक्रमe(sack, receiver->td_end + 1) &&
	    after(sack, receiver->td_end - MAXACKWINDOW(sender) - 1)) अणु
		/*
		 * Take पूर्णांकo account winकरोw scaling (RFC 1323).
		 */
		अगर (!tcph->syn)
			win <<= sender->td_scale;

		/*
		 * Update sender data.
		 */
		swin = win + (sack - ack);
		अगर (sender->td_maxwin < swin)
			sender->td_maxwin = swin;
		अगर (after(end, sender->td_end)) अणु
			sender->td_end = end;
			sender->flags |= IP_CT_TCP_FLAG_DATA_UNACKNOWLEDGED;
		पूर्ण
		अगर (tcph->ack) अणु
			अगर (!(sender->flags & IP_CT_TCP_FLAG_MAXACK_SET)) अणु
				sender->td_maxack = ack;
				sender->flags |= IP_CT_TCP_FLAG_MAXACK_SET;
			पूर्ण अन्यथा अगर (after(ack, sender->td_maxack))
				sender->td_maxack = ack;
		पूर्ण

		/*
		 * Update receiver data.
		 */
		अगर (receiver->td_maxwin != 0 && after(end, sender->td_maxend))
			receiver->td_maxwin += end - sender->td_maxend;
		अगर (after(sack + win, receiver->td_maxend - 1)) अणु
			receiver->td_maxend = sack + win;
			अगर (win == 0)
				receiver->td_maxend++;
		पूर्ण
		अगर (ack == receiver->td_end)
			receiver->flags &= ~IP_CT_TCP_FLAG_DATA_UNACKNOWLEDGED;

		/*
		 * Check retransmissions.
		 */
		अगर (index == TCP_ACK_SET) अणु
			अगर (state->last_dir == dir
			    && state->last_seq == seq
			    && state->last_ack == ack
			    && state->last_end == end
			    && state->last_win == win_raw)
				state->retrans++;
			अन्यथा अणु
				state->last_dir = dir;
				state->last_seq = seq;
				state->last_ack = ack;
				state->last_end = end;
				state->last_win = win_raw;
				state->retrans = 0;
			पूर्ण
		पूर्ण
		res = true;
	पूर्ण अन्यथा अणु
		res = false;
		अगर (sender->flags & IP_CT_TCP_FLAG_BE_LIBERAL ||
		    tn->tcp_be_liberal)
			res = true;
		अगर (!res) अणु
			nf_ct_l4proto_log_invalid(skb, ct,
			"%s",
			beक्रमe(seq, sender->td_maxend + 1) ?
			in_recv_win ?
			beक्रमe(sack, receiver->td_end + 1) ?
			after(sack, receiver->td_end - MAXACKWINDOW(sender) - 1) ? "BUG"
			: "ACK is under the lower bound (possible overly delayed ACK)"
			: "ACK is over the upper bound (ACKed data not seen yet)"
			: "SEQ is under the lower bound (already ACKed data retransmitted)"
			: "SEQ is over the upper bound (over the window of the receiver)");
		पूर्ण
	पूर्ण

	pr_debug("tcp_in_window: res=%u sender end=%u maxend=%u maxwin=%u "
		 "receiver end=%u maxend=%u maxwin=%u\n",
		 res, sender->td_end, sender->td_maxend, sender->td_maxwin,
		 receiver->td_end, receiver->td_maxend, receiver->td_maxwin);

	वापस res;
पूर्ण

/* table of valid flag combinations - PUSH, ECE and CWR are always valid */
अटल स्थिर u8 tcp_valid_flags[(TCPHDR_FIN|TCPHDR_SYN|TCPHDR_RST|TCPHDR_ACK|
				 TCPHDR_URG) + 1] =
अणु
	[TCPHDR_SYN]				= 1,
	[TCPHDR_SYN|TCPHDR_URG]			= 1,
	[TCPHDR_SYN|TCPHDR_ACK]			= 1,
	[TCPHDR_RST]				= 1,
	[TCPHDR_RST|TCPHDR_ACK]			= 1,
	[TCPHDR_FIN|TCPHDR_ACK]			= 1,
	[TCPHDR_FIN|TCPHDR_ACK|TCPHDR_URG]	= 1,
	[TCPHDR_ACK]				= 1,
	[TCPHDR_ACK|TCPHDR_URG]			= 1,
पूर्ण;

अटल व्योम tcp_error_log(स्थिर काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nf_hook_state *state,
			  स्थिर अक्षर *msg)
अणु
	nf_l4proto_log_invalid(skb, state->net, state->pf, IPPROTO_TCP, "%s", msg);
पूर्ण

/* Protect conntrack agaist broken packets. Code taken from ipt_unclean.c.  */
अटल bool tcp_error(स्थिर काष्ठा tcphdr *th,
		      काष्ठा sk_buff *skb,
		      अचिन्हित पूर्णांक dataoff,
		      स्थिर काष्ठा nf_hook_state *state)
अणु
	अचिन्हित पूर्णांक tcplen = skb->len - dataoff;
	u8 tcpflags;

	/* Not whole TCP header or malक्रमmed packet */
	अगर (th->करोff*4 < माप(काष्ठा tcphdr) || tcplen < th->करोff*4) अणु
		tcp_error_log(skb, state, "truncated packet");
		वापस true;
	पूर्ण

	/* Checksum invalid? Ignore.
	 * We skip checking packets on the outgoing path
	 * because the checksum is assumed to be correct.
	 */
	/* FIXME: Source route IP option packets --RR */
	अगर (state->net->ct.sysctl_checksum &&
	    state->hook == NF_INET_PRE_ROUTING &&
	    nf_checksum(skb, state->hook, dataoff, IPPROTO_TCP, state->pf)) अणु
		tcp_error_log(skb, state, "bad checksum");
		वापस true;
	पूर्ण

	/* Check TCP flags. */
	tcpflags = (tcp_flag_byte(th) & ~(TCPHDR_ECE|TCPHDR_CWR|TCPHDR_PSH));
	अगर (!tcp_valid_flags[tcpflags]) अणु
		tcp_error_log(skb, state, "invalid tcp flag combination");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल noअंतरभूत bool tcp_new(काष्ठा nf_conn *ct, स्थिर काष्ठा sk_buff *skb,
			     अचिन्हित पूर्णांक dataoff,
			     स्थिर काष्ठा tcphdr *th)
अणु
	क्रमागत tcp_conntrack new_state;
	काष्ठा net *net = nf_ct_net(ct);
	स्थिर काष्ठा nf_tcp_net *tn = nf_tcp_pernet(net);
	स्थिर काष्ठा ip_ct_tcp_state *sender = &ct->proto.tcp.seen[0];
	स्थिर काष्ठा ip_ct_tcp_state *receiver = &ct->proto.tcp.seen[1];

	/* Don't need lock here: this conntrack not in circulation yet */
	new_state = tcp_conntracks[0][get_conntrack_index(th)][TCP_CONNTRACK_NONE];

	/* Invalid: delete conntrack */
	अगर (new_state >= TCP_CONNTRACK_MAX) अणु
		pr_debug("nf_ct_tcp: invalid new deleting.\n");
		वापस false;
	पूर्ण

	अगर (new_state == TCP_CONNTRACK_SYN_SENT) अणु
		स_रखो(&ct->proto.tcp, 0, माप(ct->proto.tcp));
		/* SYN packet */
		ct->proto.tcp.seen[0].td_end =
			segment_seq_plus_len(ntohl(th->seq), skb->len,
					     dataoff, th);
		ct->proto.tcp.seen[0].td_maxwin = ntohs(th->winकरोw);
		अगर (ct->proto.tcp.seen[0].td_maxwin == 0)
			ct->proto.tcp.seen[0].td_maxwin = 1;
		ct->proto.tcp.seen[0].td_maxend =
			ct->proto.tcp.seen[0].td_end;

		tcp_options(skb, dataoff, th, &ct->proto.tcp.seen[0]);
	पूर्ण अन्यथा अगर (tn->tcp_loose == 0) अणु
		/* Don't try to pick up connections. */
		वापस false;
	पूर्ण अन्यथा अणु
		स_रखो(&ct->proto.tcp, 0, माप(ct->proto.tcp));
		/*
		 * We are in the middle of a connection,
		 * its history is lost क्रम us.
		 * Let's try to use the data from the packet.
		 */
		ct->proto.tcp.seen[0].td_end =
			segment_seq_plus_len(ntohl(th->seq), skb->len,
					     dataoff, th);
		ct->proto.tcp.seen[0].td_maxwin = ntohs(th->winकरोw);
		अगर (ct->proto.tcp.seen[0].td_maxwin == 0)
			ct->proto.tcp.seen[0].td_maxwin = 1;
		ct->proto.tcp.seen[0].td_maxend =
			ct->proto.tcp.seen[0].td_end +
			ct->proto.tcp.seen[0].td_maxwin;

		/* We assume SACK and liberal winकरोw checking to handle
		 * winकरोw scaling */
		ct->proto.tcp.seen[0].flags =
		ct->proto.tcp.seen[1].flags = IP_CT_TCP_FLAG_SACK_PERM |
					      IP_CT_TCP_FLAG_BE_LIBERAL;
	पूर्ण

	/* tcp_packet will set them */
	ct->proto.tcp.last_index = TCP_NONE_SET;

	pr_debug("%s: sender end=%u maxend=%u maxwin=%u scale=%i "
		 "receiver end=%u maxend=%u maxwin=%u scale=%i\n",
		 __func__,
		 sender->td_end, sender->td_maxend, sender->td_maxwin,
		 sender->td_scale,
		 receiver->td_end, receiver->td_maxend, receiver->td_maxwin,
		 receiver->td_scale);
	वापस true;
पूर्ण

/* Returns verdict क्रम packet, or -1 क्रम invalid. */
पूर्णांक nf_conntrack_tcp_packet(काष्ठा nf_conn *ct,
			    काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक dataoff,
			    क्रमागत ip_conntrack_info ctinfo,
			    स्थिर काष्ठा nf_hook_state *state)
अणु
	काष्ठा net *net = nf_ct_net(ct);
	काष्ठा nf_tcp_net *tn = nf_tcp_pernet(net);
	काष्ठा nf_conntrack_tuple *tuple;
	क्रमागत tcp_conntrack new_state, old_state;
	अचिन्हित पूर्णांक index, *समयouts;
	क्रमागत ip_conntrack_dir dir;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;
	अचिन्हित दीर्घ समयout;

	th = skb_header_poपूर्णांकer(skb, dataoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस -NF_ACCEPT;

	अगर (tcp_error(th, skb, dataoff, state))
		वापस -NF_ACCEPT;

	अगर (!nf_ct_is_confirmed(ct) && !tcp_new(ct, skb, dataoff, th))
		वापस -NF_ACCEPT;

	spin_lock_bh(&ct->lock);
	old_state = ct->proto.tcp.state;
	dir = CTINFO2सूची(ctinfo);
	index = get_conntrack_index(th);
	new_state = tcp_conntracks[dir][index][old_state];
	tuple = &ct->tuplehash[dir].tuple;

	चयन (new_state) अणु
	हाल TCP_CONNTRACK_SYN_SENT:
		अगर (old_state < TCP_CONNTRACK_TIME_WAIT)
			अवरोध;
		/* RFC 1122: "When a connection is बंदd actively,
		 * it MUST linger in TIME-WAIT state क्रम a समय 2xMSL
		 * (Maximum Segment Lअगरeसमय). However, it MAY accept
		 * a new SYN from the remote TCP to reखोलो the connection
		 * directly from TIME-WAIT state, अगर..."
		 * We ignore the conditions because we are in the
		 * TIME-WAIT state anyway.
		 *
		 * Handle पातed connections: we and the server
		 * think there is an existing connection but the client
		 * पातs it and starts a new one.
		 */
		अगर (((ct->proto.tcp.seen[dir].flags
		      | ct->proto.tcp.seen[!dir].flags)
		     & IP_CT_TCP_FLAG_CLOSE_INIT)
		    || (ct->proto.tcp.last_dir == dir
		        && ct->proto.tcp.last_index == TCP_RST_SET)) अणु
			/* Attempt to reखोलो a बंदd/पातed connection.
			 * Delete this connection and look up again. */
			spin_unlock_bh(&ct->lock);

			/* Only repeat अगर we can actually हटाओ the समयr.
			 * Deकाष्ठाion may alपढ़ोy be in progress in process
			 * context and we must give it a chance to terminate.
			 */
			अगर (nf_ct_समाप्त(ct))
				वापस -NF_REPEAT;
			वापस NF_DROP;
		पूर्ण
		fallthrough;
	हाल TCP_CONNTRACK_IGNORE:
		/* Ignored packets:
		 *
		 * Our connection entry may be out of sync, so ignore
		 * packets which may संकेत the real connection between
		 * the client and the server.
		 *
		 * a) SYN in ORIGINAL
		 * b) SYN/ACK in REPLY
		 * c) ACK in reply direction after initial SYN in original.
		 *
		 * If the ignored packet is invalid, the receiver will send
		 * a RST we'll catch below.
		 */
		अगर (index == TCP_SYNACK_SET
		    && ct->proto.tcp.last_index == TCP_SYN_SET
		    && ct->proto.tcp.last_dir != dir
		    && ntohl(th->ack_seq) == ct->proto.tcp.last_end) अणु
			/* b) This SYN/ACK acknowledges a SYN that we earlier
			 * ignored as invalid. This means that the client and
			 * the server are both in sync, जबतक the firewall is
			 * not. We get in sync from the previously annotated
			 * values.
			 */
			old_state = TCP_CONNTRACK_SYN_SENT;
			new_state = TCP_CONNTRACK_SYN_RECV;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_end =
				ct->proto.tcp.last_end;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_maxend =
				ct->proto.tcp.last_end;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_maxwin =
				ct->proto.tcp.last_win == 0 ?
					1 : ct->proto.tcp.last_win;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].td_scale =
				ct->proto.tcp.last_wscale;
			ct->proto.tcp.last_flags &= ~IP_CT_EXP_CHALLENGE_ACK;
			ct->proto.tcp.seen[ct->proto.tcp.last_dir].flags =
				ct->proto.tcp.last_flags;
			स_रखो(&ct->proto.tcp.seen[dir], 0,
			       माप(काष्ठा ip_ct_tcp_state));
			अवरोध;
		पूर्ण
		ct->proto.tcp.last_index = index;
		ct->proto.tcp.last_dir = dir;
		ct->proto.tcp.last_seq = ntohl(th->seq);
		ct->proto.tcp.last_end =
		    segment_seq_plus_len(ntohl(th->seq), skb->len, dataoff, th);
		ct->proto.tcp.last_win = ntohs(th->winकरोw);

		/* a) This is a SYN in ORIGINAL. The client and the server
		 * may be in sync but we are not. In that हाल, we annotate
		 * the TCP options and let the packet go through. If it is a
		 * valid SYN packet, the server will reply with a SYN/ACK, and
		 * then we'll get in sync. Otherwise, the server potentially
		 * responds with a challenge ACK अगर implementing RFC5961.
		 */
		अगर (index == TCP_SYN_SET && dir == IP_CT_सूची_ORIGINAL) अणु
			काष्ठा ip_ct_tcp_state seen = अणुपूर्ण;

			ct->proto.tcp.last_flags =
			ct->proto.tcp.last_wscale = 0;
			tcp_options(skb, dataoff, th, &seen);
			अगर (seen.flags & IP_CT_TCP_FLAG_WINDOW_SCALE) अणु
				ct->proto.tcp.last_flags |=
					IP_CT_TCP_FLAG_WINDOW_SCALE;
				ct->proto.tcp.last_wscale = seen.td_scale;
			पूर्ण
			अगर (seen.flags & IP_CT_TCP_FLAG_SACK_PERM) अणु
				ct->proto.tcp.last_flags |=
					IP_CT_TCP_FLAG_SACK_PERM;
			पूर्ण
			/* Mark the potential क्रम RFC5961 challenge ACK,
			 * this pose a special problem क्रम LAST_ACK state
			 * as ACK is पूर्णांकrepretated as ACKing last FIN.
			 */
			अगर (old_state == TCP_CONNTRACK_LAST_ACK)
				ct->proto.tcp.last_flags |=
					IP_CT_EXP_CHALLENGE_ACK;
		पूर्ण
		spin_unlock_bh(&ct->lock);
		nf_ct_l4proto_log_invalid(skb, ct,
					  "packet (index %d) in dir %d ignored, state %s",
					  index, dir,
					  tcp_conntrack_names[old_state]);
		वापस NF_ACCEPT;
	हाल TCP_CONNTRACK_MAX:
		/* Special हाल क्रम SYN proxy: when the SYN to the server or
		 * the SYN/ACK from the server is lost, the client may transmit
		 * a keep-alive packet जबतक in SYN_SENT state. This needs to
		 * be associated with the original conntrack entry in order to
		 * generate a new SYN with the correct sequence number.
		 */
		अगर (nfct_synproxy(ct) && old_state == TCP_CONNTRACK_SYN_SENT &&
		    index == TCP_ACK_SET && dir == IP_CT_सूची_ORIGINAL &&
		    ct->proto.tcp.last_dir == IP_CT_सूची_ORIGINAL &&
		    ct->proto.tcp.seen[dir].td_end - 1 == ntohl(th->seq)) अणु
			pr_debug("nf_ct_tcp: SYN proxy client keep alive\n");
			spin_unlock_bh(&ct->lock);
			वापस NF_ACCEPT;
		पूर्ण

		/* Invalid packet */
		pr_debug("nf_ct_tcp: Invalid dir=%i index=%u ostate=%u\n",
			 dir, get_conntrack_index(th), old_state);
		spin_unlock_bh(&ct->lock);
		nf_ct_l4proto_log_invalid(skb, ct, "invalid state");
		वापस -NF_ACCEPT;
	हाल TCP_CONNTRACK_TIME_WAIT:
		/* RFC5961 compliance cause stack to send "challenge-ACK"
		 * e.g. in response to spurious SYNs.  Conntrack MUST
		 * not believe this ACK is acking last FIN.
		 */
		अगर (old_state == TCP_CONNTRACK_LAST_ACK &&
		    index == TCP_ACK_SET &&
		    ct->proto.tcp.last_dir != dir &&
		    ct->proto.tcp.last_index == TCP_SYN_SET &&
		    (ct->proto.tcp.last_flags & IP_CT_EXP_CHALLENGE_ACK)) अणु
			/* Detected RFC5961 challenge ACK */
			ct->proto.tcp.last_flags &= ~IP_CT_EXP_CHALLENGE_ACK;
			spin_unlock_bh(&ct->lock);
			nf_ct_l4proto_log_invalid(skb, ct, "challenge-ack ignored");
			वापस NF_ACCEPT; /* Don't change state */
		पूर्ण
		अवरोध;
	हाल TCP_CONNTRACK_SYN_SENT2:
		/* tcp_conntracks table is not smart enough to handle
		 * simultaneous खोलो.
		 */
		ct->proto.tcp.last_flags |= IP_CT_TCP_SIMULTANEOUS_OPEN;
		अवरोध;
	हाल TCP_CONNTRACK_SYN_RECV:
		अगर (dir == IP_CT_सूची_REPLY && index == TCP_ACK_SET &&
		    ct->proto.tcp.last_flags & IP_CT_TCP_SIMULTANEOUS_OPEN)
			new_state = TCP_CONNTRACK_ESTABLISHED;
		अवरोध;
	हाल TCP_CONNTRACK_CLOSE:
		अगर (index != TCP_RST_SET)
			अवरोध;

		अगर (ct->proto.tcp.seen[!dir].flags & IP_CT_TCP_FLAG_MAXACK_SET) अणु
			u32 seq = ntohl(th->seq);

			अगर (beक्रमe(seq, ct->proto.tcp.seen[!dir].td_maxack)) अणु
				/* Invalid RST  */
				spin_unlock_bh(&ct->lock);
				nf_ct_l4proto_log_invalid(skb, ct, "invalid rst");
				वापस -NF_ACCEPT;
			पूर्ण

			अगर (!nf_conntrack_tcp_established(ct) ||
			    seq == ct->proto.tcp.seen[!dir].td_maxack)
				अवरोध;

			/* Check अगर rst is part of train, such as
			 *   foo:80 > bar:4379: P, 235946583:235946602(19) ack 42
			 *   foo:80 > bar:4379: R, 235946602:235946602(0)  ack 42
			 */
			अगर (ct->proto.tcp.last_index == TCP_ACK_SET &&
			    ct->proto.tcp.last_dir == dir &&
			    seq == ct->proto.tcp.last_end)
				अवरोध;

			/* ... RST sequence number करोesn't match exactly, keep
			 * established state to allow a possible challenge ACK.
			 */
			new_state = old_state;
		पूर्ण
		अगर (((test_bit(IPS_SEEN_REPLY_BIT, &ct->status)
			 && ct->proto.tcp.last_index == TCP_SYN_SET)
			|| (!test_bit(IPS_ASSURED_BIT, &ct->status)
			    && ct->proto.tcp.last_index == TCP_ACK_SET))
		    && ntohl(th->ack_seq) == ct->proto.tcp.last_end) अणु
			/* RST sent to invalid SYN or ACK we had let through
			 * at a) and c) above:
			 *
			 * a) SYN was in winकरोw then
			 * c) we hold a half-खोलो connection.
			 *
			 * Delete our connection entry.
			 * We skip winकरोw checking, because packet might ACK
			 * segments we ignored. */
			जाओ in_winकरोw;
		पूर्ण
		अवरोध;
	शेष:
		/* Keep compilers happy. */
		अवरोध;
	पूर्ण

	अगर (!tcp_in_winकरोw(ct, &ct->proto.tcp, dir, index,
			   skb, dataoff, th)) अणु
		spin_unlock_bh(&ct->lock);
		वापस -NF_ACCEPT;
	पूर्ण
     in_winकरोw:
	/* From now on we have got in-winकरोw packets */
	ct->proto.tcp.last_index = index;
	ct->proto.tcp.last_dir = dir;

	pr_debug("tcp_conntracks: ");
	nf_ct_dump_tuple(tuple);
	pr_debug("syn=%i ack=%i fin=%i rst=%i old=%i new=%i\n",
		 (th->syn ? 1 : 0), (th->ack ? 1 : 0),
		 (th->fin ? 1 : 0), (th->rst ? 1 : 0),
		 old_state, new_state);

	ct->proto.tcp.state = new_state;
	अगर (old_state != new_state
	    && new_state == TCP_CONNTRACK_FIN_WAIT)
		ct->proto.tcp.seen[dir].flags |= IP_CT_TCP_FLAG_CLOSE_INIT;

	समयouts = nf_ct_समयout_lookup(ct);
	अगर (!समयouts)
		समयouts = tn->समयouts;

	अगर (ct->proto.tcp.retrans >= tn->tcp_max_retrans &&
	    समयouts[new_state] > समयouts[TCP_CONNTRACK_RETRANS])
		समयout = समयouts[TCP_CONNTRACK_RETRANS];
	अन्यथा अगर (unlikely(index == TCP_RST_SET))
		समयout = समयouts[TCP_CONNTRACK_CLOSE];
	अन्यथा अगर ((ct->proto.tcp.seen[0].flags | ct->proto.tcp.seen[1].flags) &
		 IP_CT_TCP_FLAG_DATA_UNACKNOWLEDGED &&
		 समयouts[new_state] > समयouts[TCP_CONNTRACK_UNACK])
		समयout = समयouts[TCP_CONNTRACK_UNACK];
	अन्यथा अगर (ct->proto.tcp.last_win == 0 &&
		 समयouts[new_state] > समयouts[TCP_CONNTRACK_RETRANS])
		समयout = समयouts[TCP_CONNTRACK_RETRANS];
	अन्यथा
		समयout = समयouts[new_state];
	spin_unlock_bh(&ct->lock);

	अगर (new_state != old_state)
		nf_conntrack_event_cache(IPCT_PROTOINFO, ct);

	अगर (!test_bit(IPS_SEEN_REPLY_BIT, &ct->status)) अणु
		/* If only reply is a RST, we can consider ourselves not to
		   have an established connection: this is a fairly common
		   problem हाल, so we can delete the conntrack
		   immediately.  --RR */
		अगर (th->rst) अणु
			nf_ct_समाप्त_acct(ct, ctinfo, skb);
			वापस NF_ACCEPT;
		पूर्ण
		/* ESTABLISHED without SEEN_REPLY, i.e. mid-connection
		 * pickup with loose=1. Aव्योम large ESTABLISHED समयout.
		 */
		अगर (new_state == TCP_CONNTRACK_ESTABLISHED &&
		    समयout > समयouts[TCP_CONNTRACK_UNACK])
			समयout = समयouts[TCP_CONNTRACK_UNACK];
	पूर्ण अन्यथा अगर (!test_bit(IPS_ASSURED_BIT, &ct->status)
		   && (old_state == TCP_CONNTRACK_SYN_RECV
		       || old_state == TCP_CONNTRACK_ESTABLISHED)
		   && new_state == TCP_CONNTRACK_ESTABLISHED) अणु
		/* Set ASSURED अगर we see valid ack in ESTABLISHED
		   after SYN_RECV or a valid answer क्रम a picked up
		   connection. */
		set_bit(IPS_ASSURED_BIT, &ct->status);
		nf_conntrack_event_cache(IPCT_ASSURED, ct);
	पूर्ण
	nf_ct_refresh_acct(ct, ctinfo, skb, समयout);

	वापस NF_ACCEPT;
पूर्ण

अटल bool tcp_can_early_drop(स्थिर काष्ठा nf_conn *ct)
अणु
	चयन (ct->proto.tcp.state) अणु
	हाल TCP_CONNTRACK_FIN_WAIT:
	हाल TCP_CONNTRACK_LAST_ACK:
	हाल TCP_CONNTRACK_TIME_WAIT:
	हाल TCP_CONNTRACK_CLOSE:
	हाल TCP_CONNTRACK_CLOSE_WAIT:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_conntrack.h>

अटल पूर्णांक tcp_to_nlattr(काष्ठा sk_buff *skb, काष्ठा nlattr *nla,
			 काष्ठा nf_conn *ct, bool destroy)
अणु
	काष्ठा nlattr *nest_parms;
	काष्ठा nf_ct_tcp_flags पंचांगp = अणुपूर्ण;

	spin_lock_bh(&ct->lock);
	nest_parms = nla_nest_start(skb, CTA_PROTOINFO_TCP);
	अगर (!nest_parms)
		जाओ nla_put_failure;

	अगर (nla_put_u8(skb, CTA_PROTOINFO_TCP_STATE, ct->proto.tcp.state))
		जाओ nla_put_failure;

	अगर (destroy)
		जाओ skip_state;

	अगर (nla_put_u8(skb, CTA_PROTOINFO_TCP_WSCALE_ORIGINAL,
		       ct->proto.tcp.seen[0].td_scale) ||
	    nla_put_u8(skb, CTA_PROTOINFO_TCP_WSCALE_REPLY,
		       ct->proto.tcp.seen[1].td_scale))
		जाओ nla_put_failure;

	पंचांगp.flags = ct->proto.tcp.seen[0].flags;
	अगर (nla_put(skb, CTA_PROTOINFO_TCP_FLAGS_ORIGINAL,
		    माप(काष्ठा nf_ct_tcp_flags), &पंचांगp))
		जाओ nla_put_failure;

	पंचांगp.flags = ct->proto.tcp.seen[1].flags;
	अगर (nla_put(skb, CTA_PROTOINFO_TCP_FLAGS_REPLY,
		    माप(काष्ठा nf_ct_tcp_flags), &पंचांगp))
		जाओ nla_put_failure;
skip_state:
	spin_unlock_bh(&ct->lock);
	nla_nest_end(skb, nest_parms);

	वापस 0;

nla_put_failure:
	spin_unlock_bh(&ct->lock);
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nla_policy tcp_nla_policy[CTA_PROTOINFO_TCP_MAX+1] = अणु
	[CTA_PROTOINFO_TCP_STATE]	    = अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTOINFO_TCP_WSCALE_ORIGINAL] = अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTOINFO_TCP_WSCALE_REPLY]    = अणु .type = NLA_U8 पूर्ण,
	[CTA_PROTOINFO_TCP_FLAGS_ORIGINAL]  = अणु .len = माप(काष्ठा nf_ct_tcp_flags) पूर्ण,
	[CTA_PROTOINFO_TCP_FLAGS_REPLY]	    = अणु .len = माप(काष्ठा nf_ct_tcp_flags) पूर्ण,
पूर्ण;

#घोषणा TCP_NLATTR_SIZE	( \
	NLA_ALIGN(NLA_HDRLEN + 1) + \
	NLA_ALIGN(NLA_HDRLEN + 1) + \
	NLA_ALIGN(NLA_HDRLEN + माप(काष्ठा nf_ct_tcp_flags)) + \
	NLA_ALIGN(NLA_HDRLEN + माप(काष्ठा nf_ct_tcp_flags)))

अटल पूर्णांक nlattr_to_tcp(काष्ठा nlattr *cda[], काष्ठा nf_conn *ct)
अणु
	काष्ठा nlattr *pattr = cda[CTA_PROTOINFO_TCP];
	काष्ठा nlattr *tb[CTA_PROTOINFO_TCP_MAX+1];
	पूर्णांक err;

	/* updates could not contain anything about the निजी
	 * protocol info, in that हाल skip the parsing */
	अगर (!pattr)
		वापस 0;

	err = nla_parse_nested_deprecated(tb, CTA_PROTOINFO_TCP_MAX, pattr,
					  tcp_nla_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[CTA_PROTOINFO_TCP_STATE] &&
	    nla_get_u8(tb[CTA_PROTOINFO_TCP_STATE]) >= TCP_CONNTRACK_MAX)
		वापस -EINVAL;

	spin_lock_bh(&ct->lock);
	अगर (tb[CTA_PROTOINFO_TCP_STATE])
		ct->proto.tcp.state = nla_get_u8(tb[CTA_PROTOINFO_TCP_STATE]);

	अगर (tb[CTA_PROTOINFO_TCP_FLAGS_ORIGINAL]) अणु
		काष्ठा nf_ct_tcp_flags *attr =
			nla_data(tb[CTA_PROTOINFO_TCP_FLAGS_ORIGINAL]);
		ct->proto.tcp.seen[0].flags &= ~attr->mask;
		ct->proto.tcp.seen[0].flags |= attr->flags & attr->mask;
	पूर्ण

	अगर (tb[CTA_PROTOINFO_TCP_FLAGS_REPLY]) अणु
		काष्ठा nf_ct_tcp_flags *attr =
			nla_data(tb[CTA_PROTOINFO_TCP_FLAGS_REPLY]);
		ct->proto.tcp.seen[1].flags &= ~attr->mask;
		ct->proto.tcp.seen[1].flags |= attr->flags & attr->mask;
	पूर्ण

	अगर (tb[CTA_PROTOINFO_TCP_WSCALE_ORIGINAL] &&
	    tb[CTA_PROTOINFO_TCP_WSCALE_REPLY] &&
	    ct->proto.tcp.seen[0].flags & IP_CT_TCP_FLAG_WINDOW_SCALE &&
	    ct->proto.tcp.seen[1].flags & IP_CT_TCP_FLAG_WINDOW_SCALE) अणु
		ct->proto.tcp.seen[0].td_scale =
			nla_get_u8(tb[CTA_PROTOINFO_TCP_WSCALE_ORIGINAL]);
		ct->proto.tcp.seen[1].td_scale =
			nla_get_u8(tb[CTA_PROTOINFO_TCP_WSCALE_REPLY]);
	पूर्ण
	spin_unlock_bh(&ct->lock);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक tcp_nlattr_tuple_size(व्योम)
अणु
	अटल अचिन्हित पूर्णांक size __पढ़ो_mostly;

	अगर (!size)
		size = nla_policy_len(nf_ct_port_nla_policy, CTA_PROTO_MAX + 1);

	वापस size;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT

#समावेश <linux/netfilter/nfnetlink.h>
#समावेश <linux/netfilter/nfnetlink_ctसमयout.h>

अटल पूर्णांक tcp_समयout_nlattr_to_obj(काष्ठा nlattr *tb[],
				     काष्ठा net *net, व्योम *data)
अणु
	काष्ठा nf_tcp_net *tn = nf_tcp_pernet(net);
	अचिन्हित पूर्णांक *समयouts = data;
	पूर्णांक i;

	अगर (!समयouts)
		समयouts = tn->समयouts;
	/* set शेष TCP समयouts. */
	क्रम (i=0; i<TCP_CONNTRACK_TIMEOUT_MAX; i++)
		समयouts[i] = tn->समयouts[i];

	अगर (tb[CTA_TIMEOUT_TCP_SYN_SENT]) अणु
		समयouts[TCP_CONNTRACK_SYN_SENT] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_SYN_SENT]))*HZ;
	पूर्ण

	अगर (tb[CTA_TIMEOUT_TCP_SYN_RECV]) अणु
		समयouts[TCP_CONNTRACK_SYN_RECV] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_SYN_RECV]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_ESTABLISHED]) अणु
		समयouts[TCP_CONNTRACK_ESTABLISHED] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_ESTABLISHED]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_FIN_WAIT]) अणु
		समयouts[TCP_CONNTRACK_FIN_WAIT] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_FIN_WAIT]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_CLOSE_WAIT]) अणु
		समयouts[TCP_CONNTRACK_CLOSE_WAIT] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_CLOSE_WAIT]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_LAST_ACK]) अणु
		समयouts[TCP_CONNTRACK_LAST_ACK] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_LAST_ACK]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_TIME_WAIT]) अणु
		समयouts[TCP_CONNTRACK_TIME_WAIT] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_TIME_WAIT]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_CLOSE]) अणु
		समयouts[TCP_CONNTRACK_CLOSE] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_CLOSE]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_SYN_SENT2]) अणु
		समयouts[TCP_CONNTRACK_SYN_SENT2] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_SYN_SENT2]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_RETRANS]) अणु
		समयouts[TCP_CONNTRACK_RETRANS] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_RETRANS]))*HZ;
	पूर्ण
	अगर (tb[CTA_TIMEOUT_TCP_UNACK]) अणु
		समयouts[TCP_CONNTRACK_UNACK] =
			ntohl(nla_get_be32(tb[CTA_TIMEOUT_TCP_UNACK]))*HZ;
	पूर्ण

	समयouts[CTA_TIMEOUT_TCP_UNSPEC] = समयouts[CTA_TIMEOUT_TCP_SYN_SENT];
	वापस 0;
पूर्ण

अटल पूर्णांक
tcp_समयout_obj_to_nlattr(काष्ठा sk_buff *skb, स्थिर व्योम *data)
अणु
	स्थिर अचिन्हित पूर्णांक *समयouts = data;

	अगर (nla_put_be32(skb, CTA_TIMEOUT_TCP_SYN_SENT,
			htonl(समयouts[TCP_CONNTRACK_SYN_SENT] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_SYN_RECV,
			 htonl(समयouts[TCP_CONNTRACK_SYN_RECV] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_ESTABLISHED,
			 htonl(समयouts[TCP_CONNTRACK_ESTABLISHED] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_FIN_WAIT,
			 htonl(समयouts[TCP_CONNTRACK_FIN_WAIT] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_CLOSE_WAIT,
			 htonl(समयouts[TCP_CONNTRACK_CLOSE_WAIT] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_LAST_ACK,
			 htonl(समयouts[TCP_CONNTRACK_LAST_ACK] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_TIME_WAIT,
			 htonl(समयouts[TCP_CONNTRACK_TIME_WAIT] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_CLOSE,
			 htonl(समयouts[TCP_CONNTRACK_CLOSE] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_SYN_SENT2,
			 htonl(समयouts[TCP_CONNTRACK_SYN_SENT2] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_RETRANS,
			 htonl(समयouts[TCP_CONNTRACK_RETRANS] / HZ)) ||
	    nla_put_be32(skb, CTA_TIMEOUT_TCP_UNACK,
			 htonl(समयouts[TCP_CONNTRACK_UNACK] / HZ)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -ENOSPC;
पूर्ण

अटल स्थिर काष्ठा nla_policy tcp_समयout_nla_policy[CTA_TIMEOUT_TCP_MAX+1] = अणु
	[CTA_TIMEOUT_TCP_SYN_SENT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_SYN_RECV]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_ESTABLISHED]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_FIN_WAIT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_CLOSE_WAIT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_LAST_ACK]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_TIME_WAIT]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_CLOSE]		= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_SYN_SENT2]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_RETRANS]	= अणु .type = NLA_U32 पूर्ण,
	[CTA_TIMEOUT_TCP_UNACK]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

व्योम nf_conntrack_tcp_init_net(काष्ठा net *net)
अणु
	काष्ठा nf_tcp_net *tn = nf_tcp_pernet(net);
	पूर्णांक i;

	क्रम (i = 0; i < TCP_CONNTRACK_TIMEOUT_MAX; i++)
		tn->समयouts[i] = tcp_समयouts[i];

	/* समयouts[0] is unused, make it same as SYN_SENT so
	 * ->समयouts[0] contains 'new' समयout, like udp or icmp.
	 */
	tn->समयouts[0] = tcp_समयouts[TCP_CONNTRACK_SYN_SENT];

	/* If it is set to zero, we disable picking up alपढ़ोy established
	 * connections.
	 */
	tn->tcp_loose = 1;

	/* "Be conservative in what you करो,
	 *  be liberal in what you accept from others."
	 * If it's non-zero, we mark only out of winकरोw RST segments as INVALID.
	 */
	tn->tcp_be_liberal = 0;

	/* Max number of the retransmitted packets without receiving an (acceptable)
	 * ACK from the destination. If this number is reached, a लघुer समयr
	 * will be started.
	 */
	tn->tcp_max_retrans = 3;
पूर्ण

स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_tcp =
अणु
	.l4proto 		= IPPROTO_TCP,
#अगर_घोषित CONFIG_NF_CONNTRACK_PROCFS
	.prपूर्णांक_conntrack 	= tcp_prपूर्णांक_conntrack,
#पूर्ण_अगर
	.can_early_drop		= tcp_can_early_drop,
#अगर IS_ENABLED(CONFIG_NF_CT_NETLINK)
	.to_nlattr		= tcp_to_nlattr,
	.from_nlattr		= nlattr_to_tcp,
	.tuple_to_nlattr	= nf_ct_port_tuple_to_nlattr,
	.nlattr_to_tuple	= nf_ct_port_nlattr_to_tuple,
	.nlattr_tuple_size	= tcp_nlattr_tuple_size,
	.nlattr_size		= TCP_NLATTR_SIZE,
	.nla_policy		= nf_ct_port_nla_policy,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	.ctnl_समयout		= अणु
		.nlattr_to_obj	= tcp_समयout_nlattr_to_obj,
		.obj_to_nlattr	= tcp_समयout_obj_to_nlattr,
		.nlattr_max	= CTA_TIMEOUT_TCP_MAX,
		.obj_size	= माप(अचिन्हित पूर्णांक) *
					TCP_CONNTRACK_TIMEOUT_MAX,
		.nla_policy	= tcp_समयout_nla_policy,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */
पूर्ण;
